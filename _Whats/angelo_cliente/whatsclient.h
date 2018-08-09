#ifndef WHATSCLIENT_H
#define WHATSCLIENT_H

#include <QMainWindow>
#include <QObject>
#include <QFrame>
#include <QLabel>
#include "connectserver.h"
#include "novaconversa.h"

namespace Ui {
class WhatsClient;
}

class WhatsClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit WhatsClient(QWidget *parent = 0);
    ~WhatsClient();

signals:
    void interfaceConectada();
    void interfaceDesconectada();
    void RedesenhaConversas();
    void RedesenhaMsgs();
    void MsgErro(QString S);

public slots:
    void slotinterfaceDesconectada();
    void slotinterfaceConectada();
    void slotRedesenhaConversas();
    void slotRedesenhaMsgs();
    void slotMsgErro(QString S);

private slots:
    void on_actionConectar_triggered();

    void on_actionNovaConv_triggered();

    void on_actionDesconectar_triggered();

    void on_actionSair_triggered();

    void on_enviarButton_clicked();

    void on_conversasTable_cellClicked(int row, int column);

    void on_msgEdit_returnPressed();

    void on_actionApagar_triggered();

private:
    Ui::WhatsClient *ui;
    connectServer telaConnect;
    novaconversa telaConversa;

    QLabel* ipServidor;
    QLabel* Login;
    QLabel* Corresp;
    bool connected;
};

#endif // WHATSCLIENT_H
