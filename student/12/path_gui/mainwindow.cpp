#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEffect>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , board_(new GameBoard)
{
    ui->setupUi(this);

    //board_ = GameBoard();
    // We need a graphics scene in which to draw the gameboard
    scene_ = board_;

    // The width  and height of the graphicsView
    ui->graphicsView->setGeometry(20, 50, 350, 350);
    ui->graphicsView->setScene(scene_);

    // The dimensions of the scene
    scene_->setSceneRect(0, 0, 240, 300);

    // Setting timer color
    ui->lcdNumberSeconds->setPalette(QColor(255, 255, 255));
    ui->lcdNumberSeconds->setAutoFillBackground(true);

    // Setting other variables for timer to update per second
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(update()));

    // Defining the color and outline of the circle
    InitBoard();
    setBackgroundColor();
    connect(board_, &GameBoard::mouseClicked, this, &MainWindow::handleMouseClick);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetButtonPress);

    ui->pauseNotificationLabel->setStyleSheet("color: red;");

//NOTE THIS IS COLORPICKER CODE:
    ui->horizontalSliderRed->setMinimum(0);
    ui->horizontalSliderRed->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderGreen->setMinimum(0);
    ui->horizontalSliderGreen->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderBlue->setMinimum(0);
    ui->horizontalSliderBlue->setMaximum(RGB_VALUE_MAX);

    connect(ui->horizontalSliderRed, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(ui->horizontalSliderGreen, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(ui->horizontalSliderBlue, &QSlider::valueChanged, this, &MainWindow::onColorChanged);

    ui->horizontalSliderGreen->setValue(RGB_VALUE_MAX);

    //This is for Bottom colour picker
    ui->horizontalSliderRedBottom->setMinimum(0);
    ui->horizontalSliderRedBottom->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderGreenBottom->setMinimum(0);
    ui->horizontalSliderGreenBottom->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderBlueBottom->setMinimum(0);
    ui->horizontalSliderBlueBottom->setMaximum(RGB_VALUE_MAX);

    connect(ui->horizontalSliderRedBottom, &QSlider::valueChanged, this, &MainWindow::onBottomColorChanged);
    connect(ui->horizontalSliderGreenBottom, &QSlider::valueChanged, this, &MainWindow::onBottomColorChanged);
    connect(ui->horizontalSliderBlueBottom, &QSlider::valueChanged, this, &MainWindow::onBottomColorChanged);

    ui->horizontalSliderRedBottom->setValue(RGB_VALUE_MAX);

    //Define Pause button
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseButtonClick);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board_;
}

void MainWindow::setBackgroundColor()
{
    QPalette pal = QPalette();

    // set black background gray if not won
    pal.setColor(QPalette::Window, background_colour);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void MainWindow::InitBoard()
{
    for(auto i = 0; i < 5; ++i)
    {
        for(auto j = 0; j < 5; ++j)
        {
            if (board_->is_valid_point({i,j}))
            {
                QBrush piece_color;
                QPen piece_border(Qt::black);
                piece_border.setWidth(0);
                switch(board_->which_slot({i, j}))
                {
                case GREEN: piece_color = (Qt::green); break;
                case RED: piece_color = (Qt::red); break;
                case EMPTY: piece_color = (Qt::gray); break;
                case UNUSED: ; continue;
                }

                // Drawing the pieces
                pieces_.push_back(scene_->addEllipse(i * MARGIN + BORDER_OFFSET,
                    j * MARGIN + BORDER_OFFSET, PIECE_SIZE, PIECE_SIZE,
                    piece_border, piece_color));
            }
        }
    }
}

void MainWindow::handleMouseClick(QPointF point)
{
    if (point.isNull())
    {
        std::cout << point.x() << point.y() << std::endl;
        return;
    }
    if (paused_)
    {
        std::cout << "Game is paused. Press continue to unpause" << std::endl;
        ui->pauseNotificationLabel->setText("Game is paused!");
        return;
    }

    int x = static_cast<int>(point.x());
    int y = static_cast<int>(point.y());

    int row = ((x - BORDER_OFFSET) / MARGIN) + 0;
    int column = ((y - BORDER_OFFSET) / MARGIN) + 0;

    if (board_->is_valid_point({row, column}))
    {
        //If nothing yet selected, pick a piece to move
        if (selected_.x == -1 && selected_.y == -1)
        {
            selected_.x = row;
            selected_.y = column;
            if (board_->which_slot({selected_.x, selected_.y}) == EMPTY or
                    board_->which_slot({selected_.x, selected_.y}) == UNUSED)
            {
                std::cout << "Unsuitable selection " << std::endl;
                selected_ = {-1, -1};
                return;
            }
        }
        //Otherwise pick a target for selection
        else
        {
            target_.x = row;
            target_.y = column;

            if (board_->which_slot({target_.x, target_.y}) == RED or
                    board_->which_slot({target_.x, target_.y}) == UNUSED)
            {
                std::cout << "Move not possible" << std::endl;
                target_ = {-1, -1};
                return;
            }
            else if (board_->move(selected_, target_))
            {
                board_->move(selected_, target_);

                board_->print();
                std::cout << "Source XY: " << selected_.x + 1 <<  selected_.y + 1 << std::endl;
                std::cout << "Target XY: " << target_.x + 1 <<  target_.y + 1 << std::endl;
                board_->print();
                QPen normal_border(Qt::black);
                normal_border.setWidth(0);
                drawBoard();
                std::cout << board_->get_total_moves() << std::endl;
                ui->clickCountLabel->setText(QString::number(board_->get_total_moves()));
            } else {
                std::cout << "Illegal move" << std::endl;
            }
            target_ = {-1, -1};
            selected_ = {-1, -1};
        }
    }
    else
    {
        std::cout << "Not a valid point" << std::endl;
    }
    // Get the list of items at the clicked scene position
    QList<QGraphicsItem*> itemsAtPos = scene_->items(point);

    // Iterate through the items and check if any of them are QGraphicsEllipseItem
    for (QGraphicsItem* item : itemsAtPos)
    {
        QGraphicsEllipseItem* circle = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
        if (circle)
        {
            QPen thick_border(Qt::black);
            thick_border.setWidth(3);
            circle->setPen(thick_border);
            if (not timer_->isActive())
            {
                timer_->start(1000);
            }
        }
    }
    if (board_->is_game_over())
    {
        background_colour = Qt::yellow;
        checkGameStatusAndPromptReset();
    }
}


void MainWindow::handle_piece_click()
{
    for (auto& piece : pieces_)
    {
        std::cout << piece << std::endl;
    }
}

// Checks if the coordinate has a useful piece
// and marks it as selected
void MainWindow::selectPiece(int row, int column)
{
    if (board_->which_slot({row, column}) )
    {

    }
}

void MainWindow::resetButtonPress()
{
    scene_->clear();
    delete board_;
    board_ = new GameBoard;
    // Update the scene_ pointer to point to the new board_ instance
    scene_ = board_;
    // Update the QGraphicsView to use the new scene_
    ui->graphicsView->setScene(scene_);
    ui->lcdNumberSeconds->display(0);
    ui->clickCountLabel->setText(QString::number(board_->get_total_moves()));
    timer_->stop();
    InitBoard();
    // Reconnect the handleMouseClick function to the new board_ instance
    connect(board_, &GameBoard::mouseClicked, this, &MainWindow::handleMouseClick);
}

void MainWindow::update()
{
    int seconds = ui->lcdNumberSeconds->intValue();
    ++seconds;
    ui->lcdNumberSeconds->display(seconds);
}

void MainWindow::drawBoard()
{
    scene_->clear();
    setBackgroundColor();

    drawIcons();

    for(auto i = 0; i < 5; ++i)
    {
        for(auto j = 0; j < 5; ++j)
        {
            if (board_->is_valid_point({i,j}))
            {
                QBrush piece_color;
                QPen piece_border(Qt::black);
                piece_border.setWidth(0);
                switch(board_->which_slot({i, j}))
                {
                case GREEN: piece_color = top_colour; break;
                case RED: piece_color = bottom_colour; break;
                case EMPTY: piece_color = (Qt::gray); break;
                case UNUSED: ; continue;
                }

                // Drawing the pieces
                pieces_.push_back(scene_->addEllipse(i * MARGIN + BORDER_OFFSET,
                    j * MARGIN + BORDER_OFFSET, PIECE_SIZE, PIECE_SIZE,
                    piece_border, piece_color));
            }
        }
    }
}

void MainWindow::checkGameStatusAndPromptReset()
{
    QMessageBox msgBox;
    msgBox.setText("Congratulations, you won!");
    msgBox.setInformativeText("Do you want to play again?");
    msgBox.setStandardButtons(QMessageBox::Reset | QMessageBox::Close | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Reset);
    msgBox.setWindowTitle("Game won");
    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Reset:
            resetButtonPress();
            break;
        case QMessageBox::Close:
            // Close the application
            QApplication::closeAllWindows();
            break;
        case QMessageBox::Cancel:
            // Do nothing
            break;
        default:
            // Should never be reached
            break;
    }
}

void MainWindow::onColorChanged()
{
    QColor selectedColor(ui->horizontalSliderRed->value(),
                         ui->horizontalSliderGreen->value(),
                         ui->horizontalSliderBlue->value());
    top_colour = selectedColor;
    drawBoard();
}

void MainWindow::onBottomColorChanged()
{
    QColor selectedColor(ui->horizontalSliderRedBottom->value(),
                         ui->horizontalSliderGreenBottom->value(),
                         ui->horizontalSliderBlueBottom->value());
    bottom_colour = selectedColor;
    drawBoard();
}

void MainWindow::drawIcons()
{
    QPixmap resetLogo(QString::fromStdString(":/reset.png"));
    QPixmap pauseLogo(QString::fromStdString(pauseButtonIcon_));
    QPixmap closeLogo(QString::fromStdString(":/close.png"));
    resetLogo = resetLogo.scaled(50, 50);
    pauseLogo = pauseLogo.scaled(50, 50);
    closeLogo = closeLogo.scaled(50, 50);

    ui->resetButton->setGeometry(20, 10, 90, 30);
    ui->resetButton->setIcon(resetLogo);

    ui->pauseButton->setGeometry(110, 10, 90, 30);
    ui->pauseButton->setIcon(pauseLogo);

    ui->closeButton->setGeometry(200, 10, 90, 30);
    ui->closeButton->setIcon(closeLogo);
}

void MainWindow::onPauseButtonClick()
{
    if (!paused_)
    {
        pauseButtonIcon_ = ":/play.png";
        ui->pauseButton->setText("Continue");
        timer_->stop();
        paused_ = true;
    } else
    {
        pauseButtonIcon_ = ":/pause.png";
        ui->pauseButton->setText("Pause");
        timer_->start(1000);
        paused_ = false;
        ui->pauseNotificationLabel->setText("");
    }
    drawIcons();
}
