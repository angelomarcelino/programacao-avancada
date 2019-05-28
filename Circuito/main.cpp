#include "maincircuito.h"
#include <QApplication>
#include "circuito.h"

Circuito C;
MainCircuito *pt_w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainCircuito w;
    w.show();
    pt_w = &w;
    return a.exec();
}
