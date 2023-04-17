#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    board_ = GameBoard();
    // We need a graphics scene in which to draw a circle
    scene_ = new QGraphicsScene(this);

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(20, 50, 350, 350);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1,
    // because the circle is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, 240, 300);

    // Defining the color and outline of the circle
    InitBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitBoard()
{
    for(auto i = 0; i < 5; ++i)
    {
        for(auto j = 0; j < 5; ++j)
        {
            if (board_.is_valid_point({i,j}))
            {
                QBrush piece_color;
                QPen piece_border(Qt::black);
                piece_border.setWidth(0);
                switch(board_.which_slot({i, j}))
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

                //connect(circle_, &QPushButton::clicked,
                        //this, &MainWindow::handle_character_clicks);
            }
        }
    }
}
/*
void GameBoard::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);

    QPoint clickPosition = event->scenePos().toPoint();

    if (0 <= clickPosition.x() and clickPosition.x() <= GRID_SIDE * SIZE and
        0 <= clickPosition.y() and clickPosition.y() <= GRID_SIDE * SIZE) {
        // Only accept new mouse clicks when animations are not running.
        if (animations_.state() != QAbstractAnimation::Running) {
            emit mouseClick(clickPosition.x() / GRID_SIDE,
                            clickPosition.y() / GRID_SIDE);
        }
    }
}*/

void MainWindow::handle_character_clicks()
{
    for (auto& piece : pieces_)
    {/*
        if (piece == sender())
        {
            //handle piece click HERE
            return; // For efficiency reasons
                    // (only one button can be clicked at a time)
        }*/
    }
}
