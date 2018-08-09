#include "novaconversa.h"
#include "ui_novaconversa.h"
#include <string>
#include "whatsclient.h"
#include "mysocket.h"
#include "dados_cliente.h"
#include "dados_whatsprog.h"
#include <QMessageBox>

extern tcp_mysocket sock;
extern HANDLE th_id;
extern WhatsClient* pt_w;
extern DadosCliente DC;

using namespace std;

novaconversa::novaconversa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::novaconversa)
{
    ui->setupUi(this);
}

novaconversa::~novaconversa()
{
    delete ui;
}

void novaconversa::on_buttonBox_accepted()
{
    QString dest = ui->CorrespEdit->text();
    if(dest.size()<TAM_MIN_NOME_USUARIO || dest.size()>TAM_MAX_NOME_USUARIO)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro");
        msgBox.setText("Nome de correspondente muito grande ou pequeno");
        msgBox.exec();
    }
    else
    {
        if (DC.insertConversa(dest.toStdString()))
        {
            emit pt_w->RedesenhaConversas();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Erro");
            msgBox.setText("Nao foi possivel inserir nova conversa");
            msgBox.exec();
        }
    }
}
