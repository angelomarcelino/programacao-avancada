#ifndef MODIFICARPORTA_H
#define MODIFICARPORTA_H

#include <QDialog>
#include <string>

namespace Ui {
class ModificarPorta;
}

class ModificarPorta : public QDialog
{
    Q_OBJECT

public:
    explicit ModificarPorta(QWidget *parent = 0);
    ~ModificarPorta();

    void CarregarPorta(int row, QString s);

    void setMaxMin(int max, int min);

private slots:
    void on_entrd_spinBox_valueChanged(int arg1);

    void on_tipo_comboBox_currentTextChanged(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::ModificarPorta *ui;
    unsigned IdPorta;
    QString Tipo;
    int Nin, id1, id2, id3, id4;
};

#endif // MODIFICARPORTA_H
