#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_countButton_clicked();
    void print_weight_info(double bmi);

private:
    Ui::MainWindow *ui;

    double weight_;
    double height_;
    double bmi_;
};
#endif // MAINWINDOW_HH
