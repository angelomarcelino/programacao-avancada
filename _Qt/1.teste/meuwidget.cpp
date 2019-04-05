#include "meuwidget.h"
#include "ui_meuwidget.h"

MeuWidget::MeuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeuWidget)
{
    ui->setupUi(this);
}

MeuWidget::~MeuWidget()
{
    delete ui;
}
