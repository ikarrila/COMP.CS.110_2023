/* -----------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -----------------
 * MainWindow is the window in which a simple Path game can be played on
 *
 * Desc:
 *   This code represents an UI implementation of the Path game, that is
 * implemented in already provided gameboard.hh/cpp -code. It uses functions
 * from that code as well as QT graphics to built an interface for playing the
 * game. There are also some additional features, which were not available for
 * the previous version such as timers, move counter, colour options, etc.
 *   For each move, the user can select a piece on the board by clicking it
 * and target to move it in by clicking an empty slot on the gameboard. Invalid
 * moves will be prohibited.´
 *  This class has various private methods and slots to handle different aspects
 * of the game, such as initializing the board, updating the board after a move,
 * drawing the board, handling mouse clicks, managing the timer, changing
 * colors, pausing the game, and animating the solution. The class also has
 * private member variables to store the game board, timer, and other g
 * ame-related properties.
 *
 * Name: Iivari Karrila
 * Student number: K437292
 * UserID: gdiika
 * E-Mail: iivari.karrila@tuni.fi
 * */


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

    // Constructor
    MainWindow(QWidget *parent = nullptr);

    // Destructor
    ~MainWindow();

private slots:
    /**
     * @brief Processes the mouse click events on the game board, handling piece
     * selection and moving them.
     */
    void handleMouseClick(QPointF point);

    /**
     * @brief Selects a game piece to be moved, based on the provided row and
     * column.
     */
    void selectPiece(int row, int column);

    /**
     * @brief Selects the target position for a selected game piece to move to,
     * based on the provided row and column.
     */
    void selectMoveTarget(int row, int column);

    /**
     * @brief Updates the game board after a move, redrawing the board, updating
     * the total moves count, and the moves label.
     */
    void updateBoardAfterMove();

    /**
     * @brief Sets the window's background color based on the background_colour
     * variable.
     */
    void setBackgroundColor();

    /**
     * @brief Initializes the game board, creating and adding the ellipse
     * items (game pieces) to the scene.
     */
    void InitBoard();

    /**
     * @brief Redraws the game board and its pieces, applying the selected
     * colors for the top and bottom pieces.
     */
    void drawBoard();

    /**
     * @brief Resets the game state and board when the reset button is clicked.
     */
    void resetButtonPress();

    /**
     * @brief Updates the timer display every second.
     */
    void update();

    /**
     * @brief Updates the top piece color when the color picker sliders change.
     */
    void onColorChanged();

    /**
     * @brief Updates the bottom piece color when the color picker sliders change.
     */
    void onBottomColorChanged();

    /**
     * @brief Pauses or resumes the game when the pause button is clicked,
     * updating the button's icon accordingly.
     */
    void onPauseButtonClick();

    /**
     * @brief Returns game settings back to the original setup
     */
    void resetGameSettings();

    /**
     * @brief Shows the solution by calling moves from a predefined list
     */
    void animateSolution();

    /**
     * @brief Executes the next move on the predefined solution move list
     */
    void executeNextMove();

    /**
     * @brief Displays a prompt window when the game is won, asking if
     *  the user wants to play again, close the application, or cancel.
     */
    void victoryPromptWindow();

    /**
     * @brief Draws the icons for the reset, pause, and close buttons.
     */
    void drawIcons();

private:
    Ui::MainWindow *ui;

    // Pointer to call the methods from gameboard.hh
    GameBoard *board_;
    // Scene is used to draw graphics on the GraphicsView
    QGraphicsScene *scene_;
    // Timer for game clock
    QTimer *timer_;
    // Timer to schedule solution moves one by one
    QTimer *animationTimer_;
    // Vector containing game pieces
    std::vector<QGraphicsEllipseItem*> pieces_;
    // To stay on track on all moves made
    unsigned int total_moves_ = 0;

    // Two points, one for a piece to move, and other for place to move into.
    // Initializing both points with invalid coordinates at first. This is
    // done to ease input checking later on.
    Point selected_ = {-1, -1};
    Point target_ = {-1, -1};

    // Initial colour for background and game pieces
    QColor background_colour = Qt::gray;
    QColor top_colour = Qt::green;
    QColor bottom_colour = Qt::red;

    // Game can be paused and unpaused
    // The pauseButtonIcon will change to reflect that
    bool paused_ = false;
    std::string pauseButtonIcon_ = ":/pause.png";

    //H ow large the game pieces appear
    const int PIECE_SIZE = 30;
    //M argins and offset to set pieces far enough from each other
    const int MARGIN = 60;
    const int BORDER_OFFSET = 10;

    // Colorpicker tops at 256 colours
    const int RGB_VALUE_MAX = 255;

    // Index for executing all solutionMoves below
    std::size_t currentMoveIndex_ = 0;

    // Checks both invalid input and pause
    bool isInvalidOrPaused(QPointF point);

    // Highlights a piece in the scene when selected
    void handleSceneItemsAtPos(QPointF point);

    // 31 moves to win the game efficiently
    // These are shown to the user by clicking "Show hint" button
    std::vector<std::pair<Point, Point>> solutionMoves = {
        {{1, 0}, {2 ,2}},
        {{1, 4}, {1, 0}},
        {{0, 4}, {1, 1}},
        {{2, 2}, {0, 4}},
        {{1, 1}, {1, 4}},
        {{1, 0}, {1, 3}},
        {{0, 0}, {2, 2}},
        {{1, 3}, {0, 0}},
        {{1, 4}, {1, 0}},
        {{2, 4}, {1, 1}},
        {{3, 4}, {1, 3}},
        {{0, 4}, {3, 4}},
        {{1, 3}, {0, 4}},
        {{2, 2}, {2, 4}},
        {{1, 1}, {1, 4}},
        {{1, 0}, {1, 3}},
        {{2, 0}, {2, 2}},
        {{3, 0}, {1, 2}},
        {{0, 0}, {3, 0}},
        {{1, 2}, {0, 0}},
        {{1, 3}, {2, 0}},
        {{1, 4}, {1, 0}},
        {{0, 4}, {1, 1}},
        {{2, 2}, {0, 4}},
        {{1, 1}, {2, 2}},
        {{1, 0}, {1, 4}},
        {{0, 0}, {1, 3}},
        {{2, 2}, {0, 0}},
        {{1, 3}, {2, 2}},
        {{1, 4}, {1, 0}},
        {{2, 2}, {1, 4}},
    };
};
#endif // MAINWINDOW_HH
