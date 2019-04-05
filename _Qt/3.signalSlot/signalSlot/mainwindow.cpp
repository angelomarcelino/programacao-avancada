#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->meuSlider->setValue(50);
    ui->meuSlider->setMaximum(100);

    ui->meuProg->setValue(ui->meuSlider->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_meuSlider_valueChanged(int value)
{
    QString danger = "QProgressBar::chunk {background:red}";
    QString safe = "QProgressBar::chunk {background:green}";
    ui->meuProg->setValue(value);
    if(value>80) ui->meuProg->setStyleSheet(danger);
    else ui->meuProg->setStyleSheet(safe);
}
