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
    void on_calculatePushButton_clicked();

private:
    Ui::MainWindow *ui;

    int n_ = 0;
    int g_ = 0;
    int p_ = 0;
    int e_ = 0;
    QString tulos = "";
    QString tuloste;

};
#endif // MAINWINDOW_HH
