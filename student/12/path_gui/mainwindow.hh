#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setBackgroundColor();

    void InitBoard();

    // Draws the grid lines.
    void drawBackground(QPainter* painter, QRectF const& rect);

    // Handler for mouse click events.
    void handle_piece_click();

    //CHANGE DESCRIPTION
    void checkGameStatusAndPromptReset();

signals:
    // Emitted when user clicks a piece.
    void mouseClick(int x, int y);

private slots:
    void handleMouseClick(QPointF point);

    void resetButtonPress();

    void update();

    void drawBoard();

    void onColorChanged();

    void onBottomColorChanged();

    void onPauseButtonClick();

    void selectMoveTarget(int row, int column);

    void updateBoardAfterMove();

    void selectPiece(int row, int column);

    bool isInvalidOrPaused(QPointF point);

    void handleSceneItemsAtPos(QPointF point);

private:
    Ui::MainWindow *ui;

    GameBoard* board_;
    QGraphicsScene* scene_;         // a surface for
    const int PIECE_SIZE = 30;      // how large the game pieces appear
    const int MARGIN = 60;
    const int BORDER_OFFSET = 10;

    //Initializing both points with invalid coordinates at first
    //This is done to ease input checking later on
    Point selected_ = {-1, -1};
    Point target_ = {-1, -1};

    QTimer* timer_;
    // Vector containing game pieces
    std::vector<QGraphicsEllipseItem*> pieces_;

    unsigned int total_moves_ = 0;

    QColor background_colour = Qt::gray;
    QColor top_colour = Qt::green;
    QColor bottom_colour = Qt::red;

    //Colorpicker max
    const int RGB_VALUE_MAX = 255;

    bool paused_ = false;
    std::string pauseButtonIcon_ = ":/pause.png";

    void drawIcons();
};
#endif // MAINWINDOW_HH
