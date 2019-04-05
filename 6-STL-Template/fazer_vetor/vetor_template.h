#ifndef _VECTOR_PONTO_H_
#define _VECTOR_PONTO_H_

#include<iostream>

using namespace std;

template <class TT>
class vector
{
private:
    unsigned N;
    TT *x;
    void copy(const vector &V);
public:
    void clear();
    inline vector(): N(0), x(NULL) {};
    inline vector(const vector &V) {copy(V);}
    inline ~vector() {clear();}
    inline void operator=(const vector &V) {if(this!=&V){clear(); copy(V);}}

    inline unsigned size() const {return N;}
    TT operator[](unsigned i) const;
    TT &operator[](unsigned i);

    void push_back(TT valor);
    void erase(unsigned id);

};

#endif // _VECTOR_PONTO_H_
