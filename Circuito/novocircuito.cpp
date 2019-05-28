#include "novocircuito.h"
#include "ui_novocircuito.h"
#include "circuito.h"
#include "maincircuito.h"

extern Circuito C;
extern MainCircuito *pt_w;

novoCircuito::novoCircuito(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::novoCircuito),
    Nin(0),
    Nout(0),
    Nportas(0)
{
    ui->setupUi(this);
}

novoCircuito::~novoCircuito()
{
    delete ui;
}

void novoCircuito::on_in_spinBox_valueChanged(int arg1)
{
    Nin = arg1;
}

void novoCircuito::on_out_spinBox_valueChanged(int arg1)
{
    Nout = arg1;
}

void novoCircuito::on_portas_spinBox_valueChanged(int arg1)
{
    Nportas = arg1;
}

void novoCircuito::on_buttonBox_accepted()
{
    C.redimensionar(Nin,Nout,Nportas);
    pt_w->redimensionar_tabelas();
}
