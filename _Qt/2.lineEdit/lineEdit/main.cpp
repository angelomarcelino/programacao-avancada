#include "meuwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MeuWidget w;

    w.setName("Slim Shady");

    w.show();

    return a.exec();
}
