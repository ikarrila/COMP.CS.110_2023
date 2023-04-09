#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QFile>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <QString>

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
    void onFindButtonClicked();
    void onCloseButtonClicked();


private:
    Ui::MainWindow *ui;

    QString tiedosto_ = "";
    QString avain_ = "";
    QString tulos = "";
};
#endif // MAINWINDOW_HH
