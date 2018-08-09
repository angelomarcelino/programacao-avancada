#ifndef MENSAGEIRO2_CLIENTE_H
#define MENSAGEIRO2_CLIENTE_H

#include <QMainWindow>
#include <QLabel>

#include "connectserver.h"

namespace Ui {
  class Mensageiro2_Cliente;
}

class Mensageiro2_Cliente : public QMainWindow
{
  Q_OBJECT

public:
  explicit Mensageiro2_Cliente(QWidget *parent = 0);
  ~Mensageiro2_Cliente();

  void interface_conectado(QString servidor, QString login);
  void interface_desconectado();

  void adicionar_msg_enviada(QString dest, QString msg);
  void adicionar_msg_recebida(QString remet, QString msg);

private slots:
  void on_actionSair_triggered();

  void on_actionConectar_triggered();

  void on_actionApagar_triggered();

  void on_actionDesconectar_triggered();

  void on_enviarButton_clicked();

private:
  Ui::Mensageiro2_Cliente *ui;

  bool connected;
  QLabel ipServidor;
  QLabel myLogin;

  ConnectServer connectServer;
};

#endif // MENSAGEIRO2_CLIENTE_H
