#ifndef NOVOCIRCUITO_H
#define NOVOCIRCUITO_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class novoCircuito;
}

class novoCircuito : public QDialog
{
    Q_OBJECT

public:
    explicit novoCircuito(QWidget *parent = 0);
    ~novoCircuito();

private slots:

    void on_in_spinBox_valueChanged(int arg1);

    void on_out_spinBox_valueChanged(int arg1);

    void on_portas_spinBox_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::novoCircuito *ui;
    unsigned Nin;
    unsigned Nout;
    unsigned Nportas;
};

#endif // NOVOCIRCUITO_H
