#include "circuito.h"
#include "maincircuito.h"
#include "ui_maincircuito.h"

extern MainCircuito *pt_w;

void Circuito::imprimirEntradas(int i) const
{
    pt_w->imprimirEntradas(i);
}

void Circuito::imprimirSaidas(int i) const
{
    pt_w->imprimirSaidas(i);
}
