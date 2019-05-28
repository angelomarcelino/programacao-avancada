#include "modificarporta.h"
#include "ui_modificarporta.h"
#include "circuito.h"
#include "maincircuito.h"

extern Circuito C;
extern MainCircuito *pt_w;

ModificarPorta::ModificarPorta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModificarPorta),
    IdPorta(0),
    Tipo("??"),
    Nin(0),
    id1(0),
    id2(0),
    id3(0),
    id4(0)
{
    ui->setupUi(this);

    // Entrada Padrao
    ui->entrd_spinBox->setValue(2);


    // Spin boxes
    ui->id3_spinBox->setEnabled(false);
    ui->label_id3->setEnabled(false);
    ui->id4_spinBox->setEnabled(false);
    ui->label_id4->setEnabled(false);


    // Combo Box
    ui->tipo_comboBox->addItem("AN");
    ui->tipo_comboBox->addItem("NA");
    ui->tipo_comboBox->addItem("OR");
    ui->tipo_comboBox->addItem("NO");
    ui->tipo_comboBox->addItem("XO");
    ui->tipo_comboBox->addItem("NX");
    ui->tipo_comboBox->addItem("NT");
}

ModificarPorta::~ModificarPorta()
{
    delete ui;
}

void ModificarPorta::on_entrd_spinBox_valueChanged(int arg1)
{
    Nin = arg1;
    if(arg1>=1) {
        ui->id1_spinBox->setEnabled(true);
        ui->label_id1->setEnabled(true);
    }else {
        ui->id1_spinBox->setEnabled(false);
        ui->label_id1->setEnabled(false);
    }
    if(arg1>=2) {
        ui->id2_spinBox->setEnabled(true);
        ui->label_id2->setEnabled(true);
    }else {
        ui->id2_spinBox->setEnabled(false);
        ui->label_id2->setEnabled(false);
    }
    if(arg1>=3) {
        ui->id3_spinBox->setEnabled(true);
        ui->label_id3->setEnabled(true);
    }else {
        ui->id3_spinBox->setEnabled(false);
        ui->label_id3->setEnabled(false);
    }
    if(arg1>=4) {
        ui->id4_spinBox->setEnabled(true);
        ui->label_id4->setEnabled(true);
    }else {
        ui->id4_spinBox->setEnabled(false);
        ui->label_id4->setEnabled(false);
    }

    if(!ui->label_id1->isEnabled())ui->id1_spinBox->setValue(0);
    if(!ui->label_id2->isEnabled())ui->id2_spinBox->setValue(0);
    if(!ui->label_id3->isEnabled())ui->id3_spinBox->setValue(0);
    if(!ui->label_id4->isEnabled())ui->id4_spinBox->setValue(0);
}

void ModificarPorta::CarregarPorta(int row, QString s)
{
    IdPorta = row-1;
    ui->label_portaN->setNum(row);
    ui->tipo_comboBox->setCurrentText(s);
    if(s=="NT") {
        ui->entrd_spinBox->setMaximum(1);
        ui->entrd_spinBox->setEnabled(false);
        ui->label_entr->setEnabled(false);
    }
    else {
        ui->entrd_spinBox->setMinimum(2);
        ui->entrd_spinBox->setMaximum(4);
        ui->entrd_spinBox->setEnabled(true);
        ui->label_entr->setEnabled(true);
    }

    ui->id1_spinBox->setValue(C.getId_inPorta(row,0));
    ui->id2_spinBox->setValue(C.getId_inPorta(row,1));
    ui->id3_spinBox->setValue(C.getId_inPorta(row,2));
    ui->id4_spinBox->setValue(C.getId_inPorta(row,3));

    if(!ui->label_id1->isEnabled())ui->id1_spinBox->setValue(0);
    if(!ui->label_id2->isEnabled())ui->id2_spinBox->setValue(0);
    if(!ui->label_id3->isEnabled())ui->id3_spinBox->setValue(0);
    if(!ui->label_id4->isEnabled())ui->id4_spinBox->setValue(0);
}

void ModificarPorta::setMaxMin(int max, int min)
{
    ui->id1_spinBox->setMaximum(max);
    ui->id1_spinBox->setMinimum(min);

    ui->id2_spinBox->setMaximum(max);
    ui->id2_spinBox->setMinimum(min);

    ui->id3_spinBox->setMaximum(max);
    ui->id3_spinBox->setMinimum(min);

    ui->id4_spinBox->setMaximum(max);
    ui->id4_spinBox->setMinimum(min);
}

void ModificarPorta::on_tipo_comboBox_currentTextChanged(const QString &arg1)
{
    Tipo = arg1;
    if(arg1=="NT") {
        ui->entrd_spinBox->setMaximum(1);
        ui->entrd_spinBox->setEnabled(false);
        ui->label_entr->setEnabled(false);
    }
    else {
        ui->entrd_spinBox->setMinimum(2);
        ui->entrd_spinBox->setMaximum(4);
        ui->entrd_spinBox->setEnabled(true);
        ui->label_entr->setEnabled(true);
    }
}

void ModificarPorta::on_buttonBox_accepted()
{
    id1 = ui->id1_spinBox->value();
    id2 = ui->id2_spinBox->value();
    id3 = ui->id3_spinBox->value();
    id4 = ui->id4_spinBox->value();

    C.setPorta(IdPorta,Tipo.toStdString(),Nin);
    C.setId_inPorta(IdPorta,0,id1);
    C.setId_inPorta(IdPorta,1,id2);
    C.setId_inPorta(IdPorta,2,id3);
    C.setId_inPorta(IdPorta,3,id4);

    pt_w->redimensionar_tabelas();
}
