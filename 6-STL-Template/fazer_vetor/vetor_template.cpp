#include <iostream>
#include "vetor_template.h"

using namespace std;

template <class TT>
void vector<TT>::copy(const vector &V)
{
    N = V.N;
    x = (N==0 ? NULL : new TT[N]);
    for(unsigned i=0; i<N; i++) x[i] = V.x[i];
}

template <class TT>
void vector<TT>::clear()
{
    if (x!=NULL) delete[] x;
    x = NULL;
    N = 0;
}

template <class TT>
TT vector<TT>::operator[](unsigned i) const
{
    if(i>=N)
    {
        cerr<<"Indice invalido!"<<endl;
        return 0;
    }
    return x[i];
}

template <class TT>
TT &vector<TT>::operator[](unsigned i)
{
    static TT nada = 0;
    if(i>=N)
    {
        cerr<<"Indice invalido!"<<endl;
        return nada;
    }
    return x[i];
}

template <class TT>
void vector<TT>::push_back(TT valor)
{
    TT *prov = new TT[N+1];
    for(unsigned i=0; i<N; i++) prov[i] = x[i];
    prov[N] = valor;
    if(x!=NULL) delete[] x;
    x = prov;
    N++;
}

template <class TT>
void vector<TT>::erase(unsigned id)
{
    if (id>=N)
    {
        cerr << "indice invalido \n";
        return;
    }
    TT *prov= (N>1 ? new TT[N-1] : NULL);
    N--;
    for(unsigned i=0; i<N; i++) prov[i] = (i<id ? x[i] : x[i+1]);
    if(x!=NULL) delete[] x;
    x = prov;
}

