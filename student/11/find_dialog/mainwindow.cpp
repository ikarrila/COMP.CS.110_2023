#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <fstream>
#include <QFile>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->findPushButton, &QPushButton::clicked, this, &MainWindow::onFindButtonClicked);
    connect(ui->closePushButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFindButtonClicked()
{
    tiedosto_ = ui->fileLineEdit->text();
    avain_ = ui->keyLineEdit->text();

    if (!(ui->matchCheckBox->isChecked()))
    {
        avain_ = avain_.toLower();
    }

    std::ifstream tiedostolio(tiedosto_.toStdString());
    int count = 0;
    if (not tiedostolio)
    {
        tulos = "File not found";
    }
    else
    {
        std::string rivi = "";
        while (tiedostolio >> rivi)
        {
            if (rivi == "")
            {
                break;
            }
            if (rivi.find(avain_.toStdString()) != std::string::npos)
            {
                tulos = "Word found";
                ++count;
            }
        }
        if (avain_.toStdString() == "")
        {
            tulos = "File found";
        }
        else if (count == 0)
        {
            tulos = "Word not found";
        }
        tiedostolio.close();
    }
    ui->textBrowser->setText(tulos);
    tulos = "";

}

void MainWindow::onCloseButtonClicked()
{
    close();
}
