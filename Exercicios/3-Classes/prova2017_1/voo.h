#ifndef _VOO_PONTO_H_
#define _VOO_PONTO_H_

#include <iostream>
#include <string>
using namespace std;

class Voo
{
private:
    unsigned n_voo, h_dep, h_arrv;
    string from, to;
public:
    inline Voo(): n_voo(0), h_dep(0), h_arrv(0), from(""), to("") {}
    inline Voo(const Voo &V): n_voo(V.n_voo), h_dep(V.h_dep), h_arrv(V.h_arrv), from(V.from), to(V.to) {}
    inline ~Voo() {}
    void operator=(const Voo &V);

    inline unsigned getVoo() const {return n_voo;}
    inline unsigned getHS() const {return h_dep;}
    inline unsigned getHC() const {return h_arrv;}
    inline string getFrom() const {return from;}
    inline string getTo() const {return to;}

    friend ostream &operator<<(ostream &X, const Voo &V);
    friend istream &operator>>(istream &X, Voo &V);
};
#endif // _VOO_PONTO_H_
