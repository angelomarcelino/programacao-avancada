#include "modificarsaida.h"
#include "ui_modificarsaida.h"
#include "circuito.h"
#include "maincircuito.h"

extern Circuito C;
extern MainCircuito *pt_w;

ModificarSaida::ModificarSaida(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModificarSaida),
    IdSaida(0),
    Id(0)
{
    ui->setupUi(this);
    ui->id_spinBox->setValue(0);
}

ModificarSaida::~ModificarSaida()
{
    delete ui;
}

void ModificarSaida::CarregarSaida(int i, int maxi, int mini)
{
    IdSaida=i;

    ui->label_saidaN->setNum(i+1);

    ui->id_spinBox->setMaximum(maxi);
    ui->id_spinBox->setMinimum(mini);
}

void ModificarSaida::on_id_spinBox_valueChanged(int arg1)
{
    Id=arg1;
}

void ModificarSaida::on_buttonBox_accepted()
{
    C.setIdOutput(IdSaida,Id);
    pt_w->redimensionar_tabelas();
}
