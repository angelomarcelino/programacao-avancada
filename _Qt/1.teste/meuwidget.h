#ifndef MEUWIDGET_H
#define MEUWIDGET_H

#include <QWidget>

namespace Ui {
class MeuWidget;
}

class MeuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MeuWidget(QWidget *parent = 0);
    ~MeuWidget();

private:
    Ui::MeuWidget *ui;
};

#endif // MEUWIDGET_H
