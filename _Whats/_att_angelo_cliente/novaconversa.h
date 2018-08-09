#ifndef NOVACONVERSA_H
#define NOVACONVERSA_H

#include <QDialog>

namespace Ui {
class novaconversa;
}

class novaconversa : public QDialog
{
    Q_OBJECT

public:
    explicit novaconversa(QWidget *parent = 0);
    ~novaconversa();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::novaconversa *ui;
};

#endif // NOVACONVERSA_H
