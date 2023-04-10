#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lcdNumberMin->setPalette(QColor(170, 255, 0));
    ui->lcdNumberSec->setPalette(QColor(0, 170, 255));
    ui->lcdNumberSec->setAutoFillBackground(true);
    ui->lcdNumberMin->setAutoFillBackground(true);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(1000);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stop);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::reset);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    int seconds = ui->lcdNumberSec->intValue();
    int minutes = ui->lcdNumberMin->intValue();

    ++seconds;
    if (seconds == 60)
    {
        seconds = 0;
        ++minutes;
    }
    ui->lcdNumberMin->display(minutes);
    ui->lcdNumberSec->display(seconds);
}

void MainWindow::start()
{
    timer->start(1000);
}

void MainWindow::stop()
{
    timer->stop();
}

void MainWindow::reset()
{
    ui->lcdNumberSec->display(0);
    ui->lcdNumberMin->display(0);
}
