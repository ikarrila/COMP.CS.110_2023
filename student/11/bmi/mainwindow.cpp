#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <cmath>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_countButton_clicked()
{
    weight_ = ui->weightLineEdit->text().toDouble();
    height_ = ui->heightLineEdit->text().toDouble();

    if ( height_ == 0 or ui->heightLineEdit->text().isEmpty())
    {
        ui->infoTextBrowser->setText("Cannot count.");
        ui->resultLabel->setText("Cannot count.");

        return;
    }
    bmi_ = weight_ / ( height_ * height_ ) * 10000;

    ui->resultLabel->setText(QString::number(bmi_));
    print_weight_info(bmi_);
}

void MainWindow::print_weight_info(double bmi)
{
    if (bmi > 25)
    {
        ui->infoTextBrowser->setText("You are overweight.");
    } else if (bmi < 18.5)
    {
        ui->infoTextBrowser->setText("You are underweight.");
    } else
    {
        ui->infoTextBrowser->setText("Your weight is normal.");
    }
}
