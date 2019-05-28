#ifndef MODIFICARSAIDA_H
#define MODIFICARSAIDA_H

#include <QDialog>

namespace Ui {
class ModificarSaida;
}

class ModificarSaida : public QDialog
{
    Q_OBJECT

public:
    explicit ModificarSaida(QWidget *parent = 0);
    ~ModificarSaida();

    void CarregarSaida(int i, int maxi, int mini);

private slots:
    void on_id_spinBox_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::ModificarSaida *ui;
    int IdSaida, Id;
};

#endif // MODIFICARSAIDA_H
