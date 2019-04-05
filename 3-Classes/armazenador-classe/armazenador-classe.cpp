#include <iostream>
#include "armazenador-classe.h"
///inclui tudo em "armazenador-classe.h"
///por isso é necessario #ifndenf #define #endif
using namespace std;

///Construtor que cria listas de tamanho Num
lista_valor::lista_valor(unsigned int Num): N(Num)
{
  x = (N==0 ? NULL : new valor[N]);
}

///Desaloca a memoria
lista_valor::~lista_valor(void)
{
  if (x!=NULL) delete[] x;
}

///Construtor por copia
lista_valor::lista_valor(const lista_valor &L): N(L.N)
{
    x = (N==0 ? NULL : new valor[N]);
    for (unsigned int i=0; i<N; i++) x[i] = L.x[i];
}

///Metodo de atribuicao
void lista_valor::operator=(const lista_valor &L)
{
    if (this!=&L) /// if usuario nao for idiota (this é o endereco do obj)
    {
        if (x!=NULL) delete[] x;
        N = L.N;
        x = (N==0 ? NULL : new valor[N]);
        for (unsigned int i=0; i<N; i++) x[i] = L.x[i];
    }
}

///Insere valores
void lista_valor::inserir(valor V)
{
  valor *prov = new valor[N+1];
  for (unsigned i=0; i<N; i++) prov[i] = x[i];
  prov[N] = V;
  if (x!=NULL) delete[] x;
  x = prov;
  N++;
}

///Remove o primeiro da lista
void lista_valor::remover(void)
{
  if (N==0)
  {
    cerr << "Lista vazia. Nao ha o que remover\n";
    return;
  }
  N--;
  valor *prov = new valor[N];
  for (unsigned i=0; i<N; i++) prov[i] = x[i+1];
  delete[] x;
  x = prov;
}

///Diz o primeiro valor
valor lista_valor::operator[](unsigned i) const
{
  if (i >= N)
  {
    cerr << "Indice invalido";
    return 0; ///NOT A NUMBER
  }
  return x[i];
}

///Imprime a lista
ostream &operator<<(ostream &X, const lista_valor &L)
{
  for (unsigned i=0; i<L.N; i++) X << L.x[i] << ' ';
  return X;
}
