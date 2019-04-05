#ifndef _LISTA_VOO_PONTO_H_
#define _LISTA_VOO_PONTO_H_

#include <iostream>
#include <string>
#include "voo.h"

using namespace std;

class ListaVoos
{
private:
    unsigned N;
    Voo *x;
    void criar(const unsigned &Num);
    void copiar(const ListaVoos &LV);
    void limpar();
public:
    inline ListaVoos(): N(0), x(NULL) {}
    ListaVoos(const ListaVoos &LV): N(0), x(NULL) {copiar(LV);}
    explicit ListaVoos(const unsigned &Num) {criar(Num);}
    ~ListaVoos() {limpar();}
    void operator=(const ListaVoos &LV) {if(this!=&LV){limpar(); copiar(LV);}}

    void inserir(const Voo &V);
    void imprimir() const;
    void imprimir(const string &codigo) const;

};

#endif // _LISTA_VOO_PONTO_H_
