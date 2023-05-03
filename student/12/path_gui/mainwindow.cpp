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

    // We need a graphics scene in which to draw the gameboard
    scene_ = board_;

    // Connecting buttons and formatting the elements
    setupUI();

    // Connecting graphicsView to the scene
    ui->graphicsView->setScene(scene_);

    // The dimensions of the scene
    scene_->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);

    // Defining the board and backgroundcolour
    InitBoard();
    setBackgroundColor();

    // Setting up UI elements
    setupColorSliders();
    setupTimers();

    ui->resetButton->setDisabled(true);
}

// Destructor to remove pointers for ui and gameboard
MainWindow::~MainWindow()
{
    delete ui;
    delete board_;
}

// This method sets up the UI elements, connecting buttons and formatting elements
void MainWindow::setupUI()
{
    // Setting timer color
    ui->graphicsView->setGeometry(20, 50, GRAPHICS_VIEW_SIZE, GRAPHICS_VIEW_SIZE);
    ui->lcdNumberSeconds->setPalette(QColor(RGB_MAX, RGB_MAX, RGB_MAX));
    ui->lcdNumberSeconds->setAutoFillBackground(true);
    ui->pauseNotificationLabel->setStyleSheet("color: red;");

    // Buttons setup
    connect(ui->resetButton, &QPushButton::clicked, this,
            &MainWindow::resetButtonPress);
    connect(ui->pauseButton, &QPushButton::clicked, this,
            &MainWindow::onPauseButtonClick);
    connect(ui->hintButton, &QPushButton::clicked, this,
            &MainWindow::animateSolution);

    // Mouse click connected to game pieces and gameboard.hh
    connect(board_, &GameBoard::mouseClicked, this,
            &MainWindow::handleMouseClick);
}

// This method sets up the color sliders for changing the colors of the game pieces
void MainWindow::setupColorSliders()
{
    ui->horizontalSliderRed->setRange(0, RGB_MAX);
    ui->horizontalSliderGreen->setRange(0, RGB_MAX);
    ui->horizontalSliderBlue->setRange(0, RGB_MAX);

    ui->horizontalSliderRedBottom->setRange(0, RGB_MAX);
    ui->horizontalSliderGreenBottom->setRange(0, RGB_MAX);
    ui->horizontalSliderBlueBottom->setRange(0, RGB_MAX);

    // Connecting top sliders to value onColorChanged method
    connect(ui->horizontalSliderRed, &QSlider::valueChanged, this,
            &MainWindow::onColorChanged);
    connect(ui->horizontalSliderGreen, &QSlider::valueChanged, this,
            &MainWindow::onColorChanged);
    connect(ui->horizontalSliderBlue, &QSlider::valueChanged, this,
            &MainWindow::onColorChanged);

    // Bottom sliders have onBottomColorChanged
    connect(ui->horizontalSliderRedBottom, &QSlider::valueChanged, this,
            &MainWindow::onBottomColorChanged);
    connect(ui->horizontalSliderGreenBottom, &QSlider::valueChanged, this,
            &MainWindow::onBottomColorChanged);
    connect(ui->horizontalSliderBlueBottom, &QSlider::valueChanged, this,
            &MainWindow::onBottomColorChanged);

    ui->horizontalSliderGreen->setValue(RGB_MAX);
    ui->horizontalSliderRedBottom->setValue(RGB_MAX);
}

// This method sets up the game timers
void MainWindow::setupTimers()
{
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(update()));

    animationTimer_ = new QTimer(this);
    connect(animationTimer_, SIGNAL(timeout()), this, SLOT(executeNextMove()));
}

// Sets the background color to whichever background_color points
// This will change once game has been won
void MainWindow::setBackgroundColor()
{
    QPalette pal = QPalette();

    // set black background gray if not won
    pal.setColor(QPalette::Window, background_colour);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

// InitBoard function initializes the game board, creating the pieces and
// setting their initial positions, colors, and visual representation.
void MainWindow::InitBoard()
{
    for(auto i = 0; i < BOARD_SIZE; ++i)
    {
        for(auto j = 0; j < BOARD_SIZE; ++j)
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

// handleMouseClick function is called when a mouse click occurs on the game board.
// It handles the game logic based on the current state of the game, such as
// selecting a piece, moving a piece, checking for the end of the game, and so on.
void MainWindow::handleMouseClick(QPointF point)
{
    if ( isInvalidOrPaused(point) )
    {
        return;
    }

    int x = static_cast<int>(point.x());
    int y = static_cast<int>(point.y());
    int row = ((x - BORDER_OFFSET) / MARGIN) + 0;
    int column = ((y - BORDER_OFFSET) / MARGIN) + 0;

    if ( board_->is_valid_point({row, column}) )
    {
        //If nothing yet selected, pick a piece to move
        if (selected_.x == -1 && selected_.y == -1)
        {
            selectPiece(row, column);
            handleSceneItemsAtPos(point);
        }
        //Otherwise pick a target for to move into
        else
        {
            selectMoveTarget(row, column);
        }
    }
    else
    {
        std::cout << "Not a valid point" << std::endl;
        return;
    }
    if ( board_->is_game_over() )
    {
        timer_->stop();
        victoryPromptWindow();
    }
}

// This function is called when the user clicks on a valid game piece to move.
// It assigns the piece's position to the selected_ member variable.
void MainWindow::selectPiece(int row, int column)
{
    selected_.x = row;
    selected_.y = column;
    //If the clicked position has an EMPTY or UNUSED slot, the function resets
    // the selected_ variable to an invalid position (-1, -1) and updates the
    // board after the move.
    if (board_->which_slot({selected_.x, selected_.y}) == EMPTY or
            board_->which_slot({selected_.x, selected_.y}) == UNUSED)
    {
        std::cout << "Unsuitable selection " << std::endl;
        selected_ = {-1, -1};
        updateBoardAfterMove();
        return;
    }
}

// This function is called when the user clicks on a valid target position for the selected
// game piece to move into. It assigns the target position to the target_ member variable
// and checks whether the move is valid. If the target position is not valid, the function
// resets the selected_ and target_ variables to an invalid position, and redraws the board.
void MainWindow::selectMoveTarget(int row, int column)
{
    target_.x = row;
    target_.y = column;

    if ( board_->which_slot({target_.x, target_.y}) == RED or
         board_->which_slot({target_.x, target_.y}) == UNUSED or
        ( target_.x == selected_.x and target_.y == selected_.y) )
    {
        std::cout << "Move not possible" << std::endl;
        selected_ = {-1, -1};
        target_ = {-1, -1};
        drawBoard();
        return;
    }
    // If the move is valid, it updates the board after the move and checks
    // if the game is over.
    else if ( board_->move(selected_, target_) )
    {
        ++total_moves_;
        ui->resetButton->setEnabled(true);
        if ( board_->is_game_over() and total_moves_ <= MIN_MOVE_COUNT )
        {
            background_colour = Qt::yellow;
        }
        updateBoardAfterMove();
    } else {
        std::cout << "Illegal move" << std::endl;
    }
    target_ = {-1, -1};
    selected_ = {-1, -1};
    drawBoard();
}

// Checks the validity of a point, and whether the game is paused
bool MainWindow::isInvalidOrPaused(QPointF point)
{
    if (point.isNull())
    {
        std::cout << point.x() << point.y() << std::endl;
        return true;
    }
    if (paused_)
    {
        std::cout << "Game is paused. Press continue to unpause" << std::endl;
        ui->pauseNotificationLabel->setText("Game is paused!");
        return true;
    }
    return false;
}

// Moves the pieces on gameboard and updates UI to reflect that
void MainWindow::updateBoardAfterMove()
{
    board_->move(selected_, target_);
    QPen normal_border(Qt::black);
    normal_border.setWidth(0);
    drawBoard();
    std::cout << total_moves_ << std::endl;
    ui->clickCountLabel->setText(QString::number(total_moves_));
}

// Highlights pieces that are selected. Starts the timer
void MainWindow::handleSceneItemsAtPos(QPointF point)
{
    QList<QGraphicsItem*> itemsAtPos = scene_->items(point);

    for (QGraphicsItem* item : itemsAtPos)
    {
        QGraphicsEllipseItem* circle =
                qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
        if (circle)
        {
            QPen thick_border(Qt::black);
            thick_border.setWidth(THICK_BORDER_WIDTH);
            circle->setPen(thick_border);
            if (!timer_->isActive())
            {
                timer_->start(TIMER_INTERVAL);
            }
        }
    }
}

// Resets the game back to normal once reset button is pressed
void MainWindow::resetButtonPress()
{
    scene_->clear();
    delete board_;
    board_ = new GameBoard;
    // Update the scene_ pointer to point to the new board_ instance
    scene_ = board_;
    // Update the QGraphicsView to use the new scene_
    ui->graphicsView->setScene(scene_);
    resetGameSettings();
    InitBoard();
    drawBoard();
    // Reconnect the handleMouseClick function to the new board_ instance
    connect(board_, &GameBoard::mouseClicked, this, &MainWindow::handleMouseClick);

    if( paused_ )
    {
        onPauseButtonClick();
    }
}

// Updates the game clock
void MainWindow::update()
{
    int seconds = ui->lcdNumberSeconds->intValue();
    ++seconds;
    ui->lcdNumberSeconds->display(seconds);
}

// Draws elements on the scene
void MainWindow::drawBoard()
{
    scene_->clear();
    setBackgroundColor();

    drawIcons();

    for(auto i = 0; i < BOARD_SIZE; ++i)
    {
        for(auto j = 0; j < BOARD_SIZE; ++j)
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

// Victory screen once game is complete
void MainWindow::victoryPromptWindow()
{
    QMessageBox msgBox;
    msgBox.setText("Congratulations, you won!");
    msgBox.setInformativeText("Do you want to play again?\n\nYou can also close "
    "the application or only this window by clicking 'Cancel'");
    msgBox.setStandardButtons(QMessageBox::Reset | QMessageBox::Close |
                              QMessageBox::Cancel);
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

// Function to change top piece colours with the slider
void MainWindow::onColorChanged()
{
    QColor selectedColor(ui->horizontalSliderRed->value(),
                         ui->horizontalSliderGreen->value(),
                         ui->horizontalSliderBlue->value());
    top_colour = selectedColor;
    drawBoard();
}

// Function to change bottom piece colours with the slider
void MainWindow::onBottomColorChanged()
{
    QColor selectedColor(ui->horizontalSliderRedBottom->value(),
                         ui->horizontalSliderGreenBottom->value(),
                         ui->horizontalSliderBlueBottom->value());
    bottom_colour = selectedColor;
    drawBoard();
}

// Drawing icons for the buttons
void MainWindow::drawIcons()
{
    QPixmap resetLogo(QString::fromStdString(resetButtonIcon_));
    QPixmap pauseLogo(QString::fromStdString(pauseButtonIcon_));
    QPixmap closeLogo(QString::fromStdString(closeButtonIcon_));
    resetLogo = resetLogo.scaled(ICON_SCALED_SIZE, ICON_SCALED_SIZE);
    pauseLogo = pauseLogo.scaled(ICON_SCALED_SIZE, ICON_SCALED_SIZE);
    closeLogo = closeLogo.scaled(50, 50);

    ui->resetButton->setGeometry(20, 10, 90, 30);
    ui->resetButton->setIcon(resetLogo);

    ui->pauseButton->setGeometry(110, 10, 90, 30);
    ui->pauseButton->setIcon(pauseLogo);

    ui->closeButton->setGeometry(200, 10, 90, 30);
    ui->closeButton->setIcon(closeLogo);
}

// Handles pauseButton presses. Changes the icon as well
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
        timer_->start(TIMER_INTERVAL);
        paused_ = false;
        ui->pauseNotificationLabel->setText("");
    }
    drawIcons();
}

// Resets game settings
void MainWindow::resetGameSettings()
{
    ui->lcdNumberSeconds->display(0);
    total_moves_ = 0;
    selected_ = {-1 , -1};
    target_ = {-1 , -1};
    background_colour = Qt::gray;
    ui->clickCountLabel->setText(QString::number(total_moves_));
    ui->resetButton->setDisabled(true);
    ui->pauseNotificationLabel->setText("");
    timer_->stop();
}

// Animates solution moves with a timer
void MainWindow::animateSolution()
{
    resetButtonPress();
    animationTimer_->start(ANIMATION_TIMER_INTERVAL);
    ui->pauseButton->setDisabled(true);
    paused_ = true;
}

// Conducts moves based on previously defined solution list
void MainWindow::executeNextMove()
{
    if (currentMoveIndex_ >= solutionMoves.size())
    {
        // All moves are done, stop the timer
        animationTimer_->stop();
        currentMoveIndex_ = 0;
        background_colour = Qt::yellow;
        ui->pauseButton->setEnabled(true);
        paused_ = false;
        updateBoardAfterMove();
        return;
    }

    // Get the next move from the predefined moves list
    Point selected = solutionMoves[currentMoveIndex_].first;
    Point target = solutionMoves[currentMoveIndex_].second;

    // Perform the move on the board
    if (board_->move(selected, target))
    {
        ++total_moves_;
        updateBoardAfterMove();
    }
    else
    {
        qDebug() << "Illegal move in predefined moves list";
    }

    // Increment the current move index
    currentMoveIndex_++;
}
