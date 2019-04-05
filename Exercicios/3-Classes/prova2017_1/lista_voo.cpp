#include <iostream>
#include <string>
#include "voo.h"
#include "lista_voo.h"

using namespace std;

void ListaVoos::criar(const unsigned &Num)
{
    this->N = Num;
    this->x = new Voo[N];
}

void ListaVoos::copiar(const ListaVoos &LV)
{
    if(N==0 && x==NULL)
    {
        criar(LV.N);
        for(unsigned i=0; i<N; i++) x[i]=LV.x[i];
    }
    else cerr << "Erro inesperado";
}

void ListaVoos::limpar()
{
    if(x!=NULL) delete[] x;
    N = 0;
    x = NULL;
}

void ListaVoos::inserir(const Voo &V)
{
    Voo *prov = new Voo[N+1];
    for(unsigned i=0; i<N; i++) prov[i]=x[i];
    prov[N]=V;
    if(x!=NULL) delete[] x;
    N++;
    x = prov;
}

void ListaVoos::imprimir() const
{
    for(unsigned i=0; i<N; i++) cout << x[i] << endl;
}

void ListaVoos::imprimir(const string &codigo) const
{
    for(unsigned i=0; i<N; i++)
    {
        if (x[i].getFrom()==codigo) cout << x[i] << endl;
    }
}
