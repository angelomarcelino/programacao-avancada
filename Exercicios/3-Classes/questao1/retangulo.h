#ifndef _RETANGULO_PONTO_H_
#define _RETANGULO_PONTO_H_

#include <iostream>
#include "ponto.h"

using namespace std;

class retangulo
{
private:
    ponto A, D;
public:
    ///Construtor
    retangulo(ponto SD=0.0, ponto IE=0.0): A(SD), D(IE) {}

    ///Metodo
    double area() const;
    bool operator<(const ponto &p) const;
    bool pontoInterno(const ponto &p, const retangulo &ret) {return ret<p;}
};

#endif // _RETANGULO_PONTO_H_
