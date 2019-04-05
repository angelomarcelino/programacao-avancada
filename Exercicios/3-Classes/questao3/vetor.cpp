#include <iostream>
#include <cmath>
#include "vetor.h"

using namespace std;

vetor::vetor(const vetor &V)
{
    N=V.N;
    if (N>0)
    {
        x = new double[N];
        for(unsigned i=0; i<N; i++) x[i]=V.x[i];
    }
    else
    {
        x=NULL;
    }
}

vetor::vetor(int i)
{
    if(i>=0) N=i;
    else
    {
        cout << "Dimensão ivalida\n";
    }
    if (N>0)
    {
        x = new double[N];
        for(unsigned i=0; i<N; i++) x[i]=0;
    }
    else
    {
        x=NULL;
    }
}

vetor::~vetor()
{
    if(x!=NULL) delete[] x;
    x = NULL;
    N = 0;
    cout<<" deleted ";
}

void vetor::operator=(const vetor &V)
{
    if(this != &V)
    {
        if(N != V.N)
        {
            if(x != NULL) delete[] x;
            N = V.N;
            if(N>0) x = new double[N];
            else x = NULL;
        }
        for(unsigned i=0; i<N; i++) x[i] = V.x[i];
    }
}

double vetor::operator[](unsigned i) const
{
    if (i>=N)
    {
        cerr << "Indice invalido\n";
        return -0.0;
    }
    return x[i];
}

double &vetor::operator[](unsigned i)
{
  static double prov=0.0; ///O que ser isso?
  if (i>=N)
  {
    cerr << "Indice invalido\n";
    return prov;
  }
  return x[i];
}

ostream &operator<<(ostream &X, const vetor &V)
{
    X << '[';
    for(unsigned i=0; i<V.N; i++) X << V.x[i] << (i+1==V.N ? ']' : ';');
    return X;
}

istream &operator>>(istream &X, vetor &V)
{
    unsigned num;
    V.N=0;
    cout << "Digite 0.0 para terminar: ";
    do
    {
        X >> num;
        if (num !=0.0)
        {
            double *prov = new double[V.N+1]; ///Faz o ponteiro ter N+1 elementos (equivale: float i[n+1])
            ///prov so existe nesse if
            for (unsigned i=0; i<V.N ; i++) prov[i] = V.x[i];
            prov[V.N] = num;
            if (V.x != NULL) delete[] V.x; ///deleta o arr antigo
            V.x = prov; /// arr armazena o endereço que prov aponta
            V.N++;
        }
    }while(num!=0.0);
    return X;
}

double vetor::norma() const
{
    double nrm(0);
    for(unsigned i=0; i<N; i++) nrm = nrm + (x[i]*x[i]);
    return sqrt(nrm);
}

vetor vetor::operator+(const vetor &V) const
{
    if(V.N!=N)
    {
        cerr << "Dimensoes diferentes\n";
        return vetor();
    }
    if(N==0) return vetor();
    vetor prov(N);
    for(unsigned i=0; i<N; i++) prov.x[i]= V.x[i] + x[i];
    return prov;
}

vetor vetor::operator-(const vetor &V) const
{
    if(V.N!=N)
    {
        cerr << "Dimensoes diferentes\n";
        return vetor();
    }
    if(N==0) return vetor();
    vetor prov(N);
    for(unsigned i=0; i<N; i++) prov.x[i]= x[i] - V.x[i];
    return prov;
}

double vetor::operator*(const vetor &V) const
{
    if(V.N!=N)
    {
        cerr << "Dimensoes diferentes\n";
        return -0.0;
    }
    if(N==0) return 0.0;
    double soma(0.0);
    for(unsigned i=0; i<N; i++) soma+=(x[i]*V.x[i]);
    return soma;
}

vetor vetor::operator%(const vetor &V) const
{
    if(N!=3 || V.N!=3)
    {
        cerr << "Dimensoes invalidas\n";
        return vetor();
    }
    vetor prov(3);
    prov.x[0] = x[1]*V.x[2] - x[2]*V.x[1];
    prov.x[1] = x[2]*V.x[0] - x[0]*V.x[2];
    prov.x[2] = x[0]*V.x[1] - x[1]*V.x[0];
  return prov;
}
