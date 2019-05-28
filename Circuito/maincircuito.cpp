#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <cmath>

#include "maincircuito.h"
#include "ui_maincircuito.h"


extern Circuito C;

MainCircuito::MainCircuito(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainCircuito),
    NovoCircuito(this),
    ModPorta(this),
    ModSaida(this)
{
    // SETUPS INICIAIS
    ui->setupUi(this);

    ui->statusBar->showMessage("Nº Entradas: "+QString::number(C.getNumInputs())+
                               "    Nº Saidas: "+QString::number(C.getNumOutputs())+
                               "    Nº Portas: "+QString::number(C.getNumPortas()));

    C.ler("arquivo.txt");
    redimensionar_tabelas();
}

// METODOS DE EXIBICAO
void MainCircuito::exibir_porta(unsigned i)
{
    if(i>C.getNumPortas()) return;

    QLabel *prova;
    int numImputsPorta(C.getNumInputsPorta(i));
    QString nomePorta(QString::fromStdString(C.getNomePorta(i)));

    // Coluna TIPO
    prova = new QLabel;
    prova->setText(nomePorta);
    prova->setAlignment(Qt::AlignCenter);
    ui->tab_port->setCellWidget(i,0,prova);

    // Coluna # IN
    prova = new QLabel;
    prova->setAlignment(Qt::AlignCenter);
    prova->setNum(numImputsPorta);
    ui->tab_port->setCellWidget(i,1,prova);

    // Colunas IN #j
    for(unsigned j=0; j<C.getNumInputsPorta(i); j++)
    {
        int IdInput(C.getId_inPorta(i+1, j));
        prova = new QLabel;
        prova->setAlignment(Qt::AlignCenter);
        prova->setNum(IdInput);
        ui->tab_port->setCellWidget(i,j+2,prova);
    }
}

void MainCircuito::exibir_saida(unsigned i)
{
    if (i>C.getNumOutputs()) return;

    QLabel *prov = new QLabel;
    int IdOut(C.getIdOutput(i+1));
    prov->setAlignment(Qt::AlignCenter);
    prov->setNum(IdOut);
    ui->tab_saidas->setCellWidget(i,0,prov);
}

void MainCircuito::exibir_tv()
{
    if(C.getNumInputs()==0 || C.getNumOutputs()==0) return;

    ui->tab_tv->setColumnCount((C.getNumInputs()+C.getNumOutputs()));
    int linhas(pow(3,C.getNumInputs()));
    ui->tab_tv->setRowCount(linhas+1);
    ui->tab_tv->setSpan(0,0,1,C.getNumInputs());
    ui->tab_tv->setSpan(0,C.getNumInputs(),1,C.getNumOutputs());

    QLabel *prov = new QLabel;
    prov->setText("Entradas");
    prov->setStyleSheet("font-weight: bold");
    prov->setAlignment(Qt::AlignCenter);
    ui->tab_tv->setCellWidget(0,0,prov);

    prov = new QLabel;
    prov->setText("Saidas");
    prov->setStyleSheet("font-weight: bold");
    prov->setAlignment(Qt::AlignCenter);
    ui->tab_tv->setCellWidget(0,C.getNumInputs(),prov);

}

void MainCircuito::imprimirEntradas(int i)
{
    QLabel *prov;
    for(unsigned j=0; j<C.getNumInputs(); j++)
    {
        prov = new QLabel;
        QChar teste(toChar(C.getEntrada(j)));
        prov->setText(QString(teste));
        prov->setAlignment(Qt::AlignCenter);
        ui->tab_tv->setCellWidget(i+1,j,prov);
    }
}

void MainCircuito::imprimirSaidas(int i)
{
    QLabel *prov;
    for(unsigned j=0; j<C.getNumOutputs(); j++)
    {
        prov = new QLabel;
        QChar teste(toChar(C.getSaida(j+1)));
        prov->setText(QString(teste));
        prov->setAlignment(Qt::AlignCenter);
        ui->tab_tv->setCellWidget(i+1,j+C.getNumInputs(),prov);
    }
}

void MainCircuito::exibir_erro(QString mensagem)
{
    QMessageBox erro;
    erro.critical(0,"Circuito",mensagem);
    erro.setFixedSize(500,700);
}

// METODO DE MODIFICAR AS TABELAS
void MainCircuito::redimensionar_tabelas()
{
    ui->tab_port->clearContents();
    ui->tab_port->setRowCount(C.getNumPortas());
    for(unsigned i=0; i<C.getNumPortas(); i++) exibir_porta(i);

    ui->tab_saidas->clearContents();
    ui->tab_saidas->setRowCount(C.getNumOutputs());
    for(unsigned i=0; i<C.getNumOutputs(); i++) exibir_saida(i);

    // EXIBINDO TV SEM NADA
    ui->tab_tv->clearContents();
    ui->tab_tv->clearSpans();
    exibir_tv();

    // EXIBINDO STATUS
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Nº Entradas: "+QString::number(C.getNumInputs())+
                               "    Nº Saidas: "+QString::number(C.getNumOutputs())+
                               "    Nº Portas: "+QString::number(C.getNumPortas()));
}

// DESTRUTOR
MainCircuito::~MainCircuito()
{
    delete ui;
}

// SLOTS
void MainCircuito::on_actionLer_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
            tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        file.close();
    }
    if(!C.ler(fileName.toStdString()))
    {
        exibir_erro("Erro ao ler arquivo: "+fileName);
    }
    else C.ler(fileName.toStdString());
    redimensionar_tabelas();
}

void MainCircuito::on_actionSalvar_triggered()
{
    if(!C.valido())
    {
        exibir_erro("Circuito incompleto\n"
                    "Não pode ser salvo");
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
            tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            if(!C.salvar(fileName.toStdString()))
            {
                exibir_erro("Erro ao salvar no arquivo: "+fileName);
            }
            else C.salvar(fileName.toStdString());
            file.close();
        }
    }
}

void MainCircuito::on_actionGerar_Tabela_triggered()
{
    if(!C.valido())
    {
        exibir_erro("Circuito incompleto\n"
                    "Não pode ser simulado");
        return;
    }
    redimensionar_tabelas();
    C.gerarTabela();
}

void MainCircuito::on_actionSair_triggered()
{
    QCoreApplication::quit();
}

void MainCircuito::on_actionNovo_triggered()
{
    NovoCircuito.show();
}

void MainCircuito::on_tab_port_cellDoubleClicked(int row, int column)
{
    ModPorta.CarregarPorta(row+1, QString::fromStdString(C.getNomePorta(row)));
    ModPorta.setMaxMin(C.getNumPortas(), (-1)*C.getNumInputs());
    ModPorta.show();
}

void MainCircuito::on_tab_saidas_cellDoubleClicked(int row, int column)
{
    ModSaida.CarregarSaida(row,C.getNumPortas(), (-1)*C.getNumInputs());
    ModSaida.show();
}

