#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecalculator.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->calculatePushButton, &QPushButton::clicked, this, &MainWindow::on_calculatePushButton_clicked);

    ui->spinBoxN->setRange(0, MAX_N_POINTS);
    ui->spinBoxG->setRange(0, MAX_G_POINTS);
    ui->spinBoxP->setRange(0, MAX_P_POINTS);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calculatePushButton_clicked()
{
    n_ = ui->spinBoxN->value();
    g_ = ui->spinBoxG->value();
    p_ = ui->spinBoxP->value();
    e_ = ui->spinBoxE->value();

    tuloste = "W-Score: " + QString::number(score_from_weekly_exercises(n_, g_)) + "\n" +
              "P-Score: " + QString::number(score_from_projects(p_)) + "\n" +
              "Total grade: " + QString::number(calculate_total_grade(n_, g_, p_, e_));
    ui->textBrowser->setText(tuloste);
}
