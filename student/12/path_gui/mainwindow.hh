#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitBoard();

    // Draws the grid lines.
    void drawBackground(QPainter* painter, QRectF const& rect);

    // Handler for mouse click events.
    //void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void handle_character_clicks();

    //void mousePressEvent(QGraphicsSceneMouseEvent* event);

signals:
    // Emitted when user clicks a piece.
    void mouseClick(int x, int y);

private:
    Ui::MainWindow *ui;

    GameBoard board_;
    QGraphicsScene* scene_;         // a surface for
    const int PIECE_SIZE = 30;      // how large the game pieces appear
    const int MARGIN = 60;
    const int BORDER_OFFSET = 10;

    QTimer timer_;
    // Vector containing game pieces
    std::vector<QGraphicsEllipseItem*> pieces_;
};
#endif // MAINWINDOW_HH
