#include "loja_heranca.h"
#include <iostream>
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>

istream &Produto::digitar(istream &I)
{
    cout << "Nome: \n";
    I.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(I, nome, '\n');
    float price=0;
    cout << "preço: ";
    I >> price;
    price=price*100.00;
    preco = price+0.5;
    return I;
}

ostream &Produto::imprimir(ostream &O) const
{
    O << '"' << nome << '"' << ';' << '$' <<float (preco)/100.00 << ';';
    return O;
}

istream &Produto::ler(istream &I)
{
    I.ignore(numeric_limits<streamsize>::max(), '"');
    getline(I, nome, '"');
    I.ignore(numeric_limits<streamsize>::max(), '$');
    float price=0;
    I>> price;
    I.ignore(numeric_limits<streamsize>::max(), ';');

    preco = price*100;
    return I;
}

istream &Livro::digitar(istream &I)
{
    Produto::digitar(I);
    cout << "Autor: \n";
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

istream &CD::digitar(istream &I)
{
    Produto::digitar(I);
    cout << "Nº de faixas: \n";
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
    I>>faixas;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return I;
}

istream &DVD::digitar(istream &I)
{
    Produto::digitar(I);
    cout << "Duração: \n";
    I >> duracao;
    return I;
}

ostream &DVD::imprimir(ostream &O) const
{
    O << "D: ";
    Produto::imprimir(O);
    O << duracao << endl;
    return O;
}

istream &DVD::ler(istream &I)
{
    Produto::ler(I);
    I>>duracao;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return I;
}

void ListaLivro::incluir(const Livro &L)
{
    Livro *novoX = new Livro[N+1];
    for (unsigned i=0; i < N ; i++)
    {
        novoX[i] = x[i];
    }
    novoX[N]= L;
    if (x!=NULL)
    {
        delete[] x;
    }
    x=novoX;
    N++;
}

void ListaLivro::excluir(unsigned id)
{
    if (N==0 or id>=N)
    {
        cerr << "Indices Errados";
        return;
    }
    Livro *novoX = new Livro[N-1];
    for (unsigned i=0; i < id ; i++)
    {
        novoX[i] = x[i];
    }
    for (unsigned i=id; i < N-1 ; i++)
    {
        novoX[i] = x[i+1];
    }
    if (x!=NULL)
    {
        delete[] x;
    }
    x=novoX;
    N--;
}

void ListaLivro::imprimir() const
{
    cout << "ListaLIVROS " << N << endl;
    for (unsigned i=0; i < N ; i++)
    {
        cout << i << ") "<< x[i];
    }
}

void ListaLivro::ler(istream &I)
{
    I.ignore(numeric_limits<streamsize>::max(),' ');
    unsigned n=0;
    I >> n;
    Livro *novoX = new Livro[N+n];
    for (unsigned i=0; i < N ; i++)
    {
        novoX[i]=x[i];
    }
    for (unsigned i=N; i < N+n ; i++)
    {
        novoX[i].ler(I);
    }
    x=novoX;
    N+=n;
}

void ListaLivro::salvar(ostream &O) const
{
    O << "ListaLIVROS " << N << endl;
    for (unsigned i=0; i < N ; i++)
    {
        O<<x[i];
    }
}

void ListaCD::incluir(const CD &L)
{
    CD *novoX = new CD[N+1];
    for (unsigned i=0; i < N ; i++)
    {
        novoX[i] = x[i];
    }
    novoX[N]= L;
    if (x!=NULL)
    {
        delete[] x;
    }
    x=novoX;
    N++;
}

void ListaCD::excluir(unsigned id)
{
    if (N==0 or id>=N)
    {
        cerr << "Indices Errados";
        return;
    }
    CD *novoX = new CD[N-1];
    for (unsigned i=0; i < id ; i++)
    {
        novoX[i] = x[i];
    }
    for (unsigned i=id; i < N-1 ; i++)
    {
        novoX[i] = x[i+1];
    }
    if (x!=NULL)
    {
        delete[] x;
    }
    x=novoX;
    N--;
}

void ListaCD::imprimir() const
{
    cout << "ListaCDS " << N << endl;
    for (unsigned i=0; i < N ; i++)
    {
        cout << i << ") "<<  x[i];
    }
}

void ListaCD::ler(istream &I)
{
    I.ignore(numeric_limits<streamsize>::max(),' ');
    unsigned n=0;
    I >> n;
    CD *novoX = new CD[N+n];
    for (unsigned i=0; i < N ; i++)
    {
        novoX[i]=x[i];
    }
    for (unsigned i=N; i < N+n ; i++)
    {
        novoX[i].ler(I);
    }
    x=novoX;
    N+=n;
}
//
void ListaCD::salvar(ostream &O) const
{
    O << "ListaCD " << N << endl;
    for (unsigned i=0; i < N ; i++)
    {
        O<<x[i];
    }
}


void ListaDVD::incluir(const DVD &L)
{
    DVD *novoX = new DVD[N+1];
    for (unsigned i=0; i < N ; i++)
    {
        novoX[i] = x[i];
    }
    novoX[N]= L;
    if (x!=NULL)
    {
        delete[] x;
    }
    x=novoX;
    N++;
}

void ListaDVD::excluir(unsigned id)
{
    if (N==0 or id>=N)
    {
        cerr << "Indices Errados";
        return;
    }
    DVD *novoX = new DVD[N-1];
    for (unsigned i=0; i < id ; i++)
    {
        novoX[i] = x[i];
    }
    for (unsigned i=id; i < N-1 ; i++)
    {
        novoX[i] = x[i+1];
    }
    if (x!=NULL)
    {
        delete[] x;
    }
    x=novoX;
    N--;
}

void ListaDVD::imprimir() const
{
    cout << "ListaDVDS " << N << endl;
    for (unsigned i=0; i < N ; i++)
    {
        cout << i << ") "<<  x[i];
    }
}

void ListaDVD::ler(istream &I)
{
    I.ignore(numeric_limits<streamsize>::max(),' ');
    unsigned n=0;
    I >> n;
    DVD *novoX = new DVD[N+n];
    for (unsigned i=0; i < N ; i++)
    {
        novoX[i]=x[i];
    }
    for (unsigned i=N; i < N+n ; i++)
    {
        novoX[i].ler(I);
    }
    x=novoX;
    N+=n;
}

//
void ListaDVD::salvar(ostream &O) const
{
    O << "ListaDVDS " << N << endl;

    for (unsigned i=0; i < N ; i++)
    {
        O << x[i];
    }
}

void Loja::imprimir() const
{
//    cout << " LISTA LIVRO" << LL.getTam() << endl;
    LL.imprimir();
//    cout << " LISTA LIVRO" << LC.getTam() << "\n";
    LC.imprimir();
//    cout << " LISTA LIVRO" << LD.getTam() << "\n";
    LD.imprimir();

}

void Loja::ler(const char* arq)
{
    ifstream ifs(arq);
    LL.ler(ifs);
    LC.ler(ifs);
    LD.ler(ifs);
    ifs.close();
}

void Loja::salvar(const char* arq) const
{
    ofstream ofs (arq);
    LL.salvar(ofs);
    LC.salvar(ofs);
    LD.salvar(ofs);
    ofs.close();
}
