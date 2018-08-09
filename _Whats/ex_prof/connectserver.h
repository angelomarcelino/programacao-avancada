#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H

#include <QDialog>

namespace Ui {
  class ConnectServer;
}

class ConnectServer : public QDialog
{
  Q_OBJECT

public:
  explicit ConnectServer(QWidget *parent = 0);
  ~ConnectServer();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::ConnectServer *ui;
};

#endif // CONNECTSERVER_H
