#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H

#include <QDialog>

namespace Ui {
class connectServer;
}

class connectServer : public QDialog
{
    Q_OBJECT

public:
    explicit connectServer(QWidget *parent = 0);
    ~connectServer();

private slots:
    void on_buttonBox_accepted();

    void on_cadastrarButton_clicked();

private:
    Ui::connectServer *ui;
};

#endif // CONNECTSERVER_H
