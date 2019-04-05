#ifndef _LOJA_H_
#define _LOJA_H_

#include <iostream>
#include <string>

using namespace std;

class Produto
{
private:
    string nome;
    unsigned preco;
public:
    inline Produto(const char *N="", unsigned P=0): nome(N), preco(P) {}
    istream &digitar(istream &I);
    ostream &imprimir(ostream &O) const;
    istream &ler(istream &I);
    inline ostream &salvar(ostream &O) const {return imprimir(O);}
};

inline istream &operator>>(istream &I, Produto &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, Produto &X) {return X.imprimir(O);}

class Livro: public Produto
{
private:
    string autor;
public:
    inline Livro(const char *N="", unsigned P=0,const char *A=""):Produto(N , P) , autor(A) {}
    istream &digitar(istream &I);
    ostream &imprimir(ostream &O) const;
    istream &ler(istream &I);
    inline ostream &salvar(ostream &O) const {return imprimir(O);}
};

inline istream &operator>>(istream &I, Livro &L) {return L.digitar(I);}
inline ostream &operator<<(ostream &O, Livro &L) {return L.imprimir(O);}

class CD: public Produto
{
private:
    unsigned faixas;
public:
    inline CD(const char *N="", unsigned P=0,const unsigned f=0):Produto(N , P) , faixas(f) {}
    istream &digitar(istream &I);
    ostream &imprimir(ostream &O) const;
    istream &ler(istream &I);
    inline ostream &salvar(ostream &O) const {return imprimir(O);}
};

inline istream &operator>>(istream &I, CD &C) {return C.digitar(I);}
inline ostream &operator<<(ostream &O, CD &C) {return C.imprimir(O);}

class DVD: public Produto
{
private:
    int duracao;
public:
    inline DVD(const char *N="", unsigned P=0,const int d=0):Produto(N , P) , duracao(d) {}
    istream &digitar(istream &I);
    ostream &imprimir(ostream &O) const;
    istream &ler(istream &I);
    inline ostream &salvar(ostream &O) const {return imprimir(O);}
};

inline istream &operator>>(istream &I, DVD &D) {return D.digitar(I);}
inline ostream &operator<<(ostream &O, DVD &D) {return D.imprimir(O);}

class ListaLivro
{
private:
    Livro *x;
    unsigned N;
public:
    inline ListaLivro(): x(NULL), N(0) {}
    // Inclua os construtores, destrutor e operadores necessarios
    void incluir(const Livro &L);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    void salvar(ostream &O) const;
};

class ListaCD
{
private:
    CD *x;
    unsigned N;
public:
    inline ListaCD(): x(NULL), N(0) {}
    // Inclua os construtores, destrutor e operadores necessarios
    void incluir(const CD &C);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    void salvar(ostream &O) const;
};

class ListaDVD
{
private:
    DVD *x;
    unsigned N;
public:
    inline ListaDVD(): x(NULL), N(0) {}
    // Inclua os construtores, destrutor e operadores necessarios
    void incluir(const DVD &D);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    void salvar(ostream &O) const;
};

class Loja
{
private:
    ListaLivro LL;
    ListaCD LC;
    ListaDVD LD;
public:
    inline Loja(): LL(), LC(), LD() {}
    inline void incluirLivro(const Livro &X) {LL.incluir(X);}
    inline void excluirLivro(unsigned id) {LL.excluir(id);}
    inline void incluirDVD(const DVD &X) {LD.incluir(X);}
    inline void excluirDVD(unsigned id) {LD.excluir(id);}
    inline void incluirCD(const CD &X) {LC.incluir(X);}
    inline void excluirCD(unsigned id) {LC.excluir(id);}
    void imprimir() const;
    void ler(const char* arq);
    void salvar(const char* arq) const;
};
#endif // _LOJA_H_
