#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "loja_heranca.h"

///PRODUTO
istream &Produto::digitar(istream &I)
{
    float prv;
    cout << "Nome: ";
    I.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(I, nome, '\n');

    cout << "Preço: $";
    I >> prv;
    preco = prv*100;

    return I;
}

ostream &Produto::imprimir(ostream &O) const
{
    O << '"' << nome << '"' << ';' << '$' <<float (preco)/100.00 << ';';
    return O;
}

istream &Produto::ler(istream &I)
{
    float prv;
    I.ignore(numeric_limits<streamsize>::max(), '"');
    getline(I, nome, '"');

    I.ignore(numeric_limits<streamsize>::max(), '$');
    I >> prv;
    preco = prv*100;

    return I;
}

///LIVRO
istream &Livro::digitar(istream &I)
{
    Produto::digitar(I);
    cout << "Autor: ";
    I.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(I, autor, '\n');
    return I;
}

ostream &Livro::imprimir(ostream &O) const
{
    O << "L: ";
    Produto::imprimir(O);
    O << '"' << autor << '"' << endl;
    return O;
}

istream &Livro::ler(istream &I)
{
    Produto::ler(I);
    I.ignore(numeric_limits<streamsize>::max(), '"');
    getline(I, autor, '"');
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return I;
}

///CD
istream &CD::digitar(istream &I)
{
    Produto::digitar(I);
    cout << "Faixas: ";
    I >> faixas;
    return I;
}

ostream &CD::imprimir(ostream &O) const
{
    O << "C: ";
    Produto::imprimir(O);
    O << faixas << endl;
    return O;
}

istream &CD::ler(istream &I)
{
    Produto::ler(I);
    I.ignore(numeric_limits<streamsize>::max(), ';');
    I >> faixas;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return I;
}

///DVD
istream &DVD::digitar(istream &I)
{
    Produto::digitar(I);
    cout << "Duracao: ";
    I >> minutos;
    return I;
}

ostream &DVD::imprimir(ostream &O) const
{
    O << "D: ";
    Produto::imprimir(O);
    O << minutos << endl;
    return O;
}

istream &DVD::ler(istream &I)
{
    Produto::ler(I);
    I.ignore(numeric_limits<streamsize>::max(), ';');
    I >> minutos;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return I;
}

///LISTA LIVRO
void ListaLivro::criar(const unsigned &num)
{
    if (num==0)
    {
        x=NULL;
        return;
    }
    N=num;
    x = new Livro[N];
}

void ListaLivro::copiar(const ListaLivro &L)
{
    criar(L.N);
    for(unsigned i=0; i<N; i++) {x[i]=L.x[i];}
}

void ListaLivro::limpar()
{
    if(x!=NULL) {delete[] x;}
    N = 0;
    x = NULL;
}

void ListaLivro::incluir(const Livro &L)
{
    Livro *prov = new Livro[N+1];
    for (unsigned i=0; i<N ; i++){prov[i] = x[i];}
    prov[N]= L;
    if (x!=NULL){delete[] x;}
    x=prov;
    N++;
}

void ListaLivro::excluir(unsigned id)
{
    if (N==0 or id>=N)
    {
        cerr << "Indice Errado";
        return;
    }
    Livro *prov = new Livro[N-1];
    for (unsigned i=0; i<id ; i++){prov[i] = x[i];}
    for (unsigned i=id; i<N-1 ; i++){prov[i] = x[i+1];}
    if (x!=NULL){delete[] x;}
    x=prov;
    N--;
}

void ListaLivro::imprimir() const
{
    cout << "LIVROS: " << endl;
    for (unsigned i=0; i<N; i++)
    {
        cout << i << ')' <<' '<< x[i];
    }
}

void ListaLivro::ler(istream &I)
{
    string prov;
    I >> prov;
    if(prov != "LISTALIVRO")
    {
        cout << "Arquivo Corrompido!";
        return;
    }
    I.ignore(numeric_limits<streamsize>::max(),' ');
    unsigned n=0;
    I >> n;
    Livro *ptr = new Livro[N+n];
    for (unsigned i=0; i<N ; i++)
    {
        ptr[i]=x[i];
    }
    for (unsigned i=N; i < N+n ; i++)
    {
        ptr[i].ler(I);
    }
    x=ptr;
    N+=n;
}

void ListaLivro::salvar(ostream &O) const
{
    O << "LISTALIVRO " << N << endl;
    for (unsigned i=0; i<N ; i++)
    {
        O<<x[i];
    }
}

///LISTA CD
void ListaCD::criar(const unsigned &num)
{
    if (num==0)
    {
        x=NULL;
        return;
    }
    N=num;
    x = new CD[N];
}

void ListaCD::copiar(const ListaCD &L)
{
    criar(L.N);
    for(unsigned i=0; i<N; i++) {x[i]=L.x[i];}
}

void ListaCD::limpar()
{
    if(x!=NULL) {delete[] x;}
    N = 0;
    x = NULL;
}

void ListaCD::incluir(const CD &L)
{
    CD *prov = new CD[N+1];
    for (unsigned i=0; i<N ; i++){prov[i] = x[i];}
    prov[N]= L;
    if (x!=NULL){delete[] x;}
    x=prov;
    N++;
}

void ListaCD::excluir(unsigned id)
{
    if (N==0 or id>=N)
    {
        cerr << "Indice Errado";
        return;
    }
    CD *prov = new CD[N-1];
    for (unsigned i=0; i<id ; i++){prov[i] = x[i];}
    for (unsigned i=id; i<N-1 ; i++){prov[i] = x[i+1];}
    if (x!=NULL){delete[] x;}
    x=prov;
    N--;
}

void ListaCD::imprimir() const
{
    cout << "CDs: " << endl;
    for (unsigned i=0; i<N; i++)
    {
        cout << i << ')' <<' '<< x[i];
    }
}

void ListaCD::ler(istream &I)
{
    string prov;
    I >> prov;
    if(prov != "LISTACD")
    {
        cout << "Arquivo Corrompido!";
        return;
    }
    I.ignore(numeric_limits<streamsize>::max(),' ');
    unsigned n=0;
    I >> n;
    CD *ptr = new CD[N+n];
    for (unsigned i=0; i<N ; i++)
    {
        ptr[i]=x[i];
    }
    for (unsigned i=N; i < N+n ; i++)
    {
        ptr[i].ler(I);
    }
    x=ptr;
    N+=n;
}

void ListaCD::salvar(ostream &O) const
{
    O << "LISTACD " << N << endl;
    for (unsigned i=0; i<N ; i++)
    {
        O<<x[i];
    }
}

///LISTA DVD
void ListaDVD::criar(const unsigned &num)
{
    if (num==0)
    {
        x=NULL;
        return;
    }
    N=num;
    x = new DVD[N];
}

void ListaDVD::copiar(const ListaDVD &L)
{
    criar(L.N);
    for(unsigned i=0; i<N; i++) {x[i]=L.x[i];}
}

void ListaDVD::limpar()
{
    if(x!=NULL) {delete[] x;}
    N = 0;
    x = NULL;
}

void ListaDVD::incluir(const DVD &L)
{
    DVD *prov = new DVD[N+1];
    for (unsigned i=0; i<N ; i++){prov[i] = x[i];}
    prov[N]= L;
    if (x!=NULL){delete[] x;}
    x=prov;
    N++;
}

void ListaDVD::excluir(unsigned id)
{
    if (N==0 or id>=N)
    {
        cerr << "Indice Errado";
        return;
    }
    DVD *prov = new DVD[N-1];
    for (unsigned i=0; i<id ; i++){prov[i] = x[i];}
    for (unsigned i=id; i<N-1 ; i++){prov[i] = x[i+1];}
    if (x!=NULL){delete[] x;}
    x=prov;
    N--;
}

void ListaDVD::imprimir() const
{
    cout << "DVDs: " << endl;
    for (unsigned i=0; i<N; i++)
    {
        cout << i << ')' <<' '<< x[i];
    }
}

void ListaDVD::ler(istream &I)
{
    string prov;
    I >> prov;
    if(prov != "LISTADVD")
    {
        cout << "Arquivo Corrompido!";
        return;
    }
    I.ignore(numeric_limits<streamsize>::max(),' ');
    unsigned n=0;
    I >> n;
    DVD *ptr = new DVD[N+n];
    for (unsigned i=0; i<N ; i++)
    {
        ptr[i]=x[i];
    }
    for (unsigned i=N; i < N+n ; i++)
    {
        ptr[i].ler(I);
    }
    x=ptr;
    N+=n;
}

void ListaDVD::salvar(ostream &O) const
{
    O << "LISTADVD " << N << endl;
    for (unsigned i=0; i<N ; i++)
    {
        O<<x[i];
    }
}

///LOJA
void Loja::imprimir() const
{
    LL.imprimir();
    LC.imprimir();
    LD.imprimir();
}

void Loja::ler(const char* arq)
{
    ifstream zz(arq);
    LL.ler(zz);
    LC.ler(zz);
    LD.ler(zz);
    zz.close();
}

void Loja::salvar(const char* arq) const
{
    ofstream zz(arq);
    LL.salvar(zz);
    LC.salvar(zz);
    LD.salvar(zz);
    zz.close();
}
