#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEffect>

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
    connect(board_, &GameBoard::mouseClicked, this, &MainWindow::handleMouseClick);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetButtonPress);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board_;
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

// Perform actions with the mouse click
void MainWindow::handleMouseClick(QPointF point)
{
    if (point.isNull())
    {
        std::cout << point.x() << point.y() << std::endl;
        return;
    }

    int x = static_cast<int>(point.x());
    int y = static_cast<int>(point.y());

    int row = ((x - BORDER_OFFSET) / MARGIN) + 0;
    int column = ((y - BORDER_OFFSET) / MARGIN) + 0;

    if (board_->is_valid_point({column, row}))
    {
        std::cout << "Clicked circle at row: " << row << ", column: " << column << std::endl;
        // Perform actions with the clicked circle
        if (selected_.y == 0 and selected_.x == 0)
        {
            selected_.x = row;
            selected_.y = column;
        } else
        {
            target_.x = row;
            target_.y = column;
            board_->move(selected_, target_);

            board_->print();
            std::cout << "Source XY: " << selected_.x + 1 <<  selected_.y + 1 << std::endl;
            std::cout << "Target XY: " << target_.x + 1 <<  target_.y + 1 << std::endl;
            board_->print();
            target_ = {0, 0};
            selected_ = {0, 0};
            QPen normal_border(Qt::black);
            normal_border.setWidth(0);
            drawBoard();
            std::cout << board_->get_total_moves() << std::endl;
        }
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
    ui->lcdNumberSeconds->display(0);
    timer_->stop();
    InitBoard();
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
