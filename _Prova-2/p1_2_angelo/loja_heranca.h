#ifndef _LOJA_H_
#define _LOJA_H_

#include <iostream>
#include <string>

using namespace std;

///PRODUTO
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


///LIVRO
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

inline istream &operator>>(istream &I, Livro &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, Livro &X) {return X.imprimir(O);}


///CD
class CD: public Produto
{
private:
    int faixas;
public:
    inline CD(const char *N="", unsigned P=0, int f=0):Produto(N , P) , faixas(f) {}
    istream &digitar(istream &I);
    ostream &imprimir(ostream &O) const;
    istream &ler(istream &I);
    inline ostream &salvar(ostream &O) const {return imprimir(O);}
};

inline istream &operator>>(istream &I, CD &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, CD &X) {return X.imprimir(O);}


///DVD
class DVD: public Produto
{
private:
    int minutos;
public:
    inline DVD(const char *N="", unsigned P=0, int m=0):Produto(N , P) , minutos(m) {}
    istream &digitar(istream &I);
    ostream &imprimir(ostream &O) const;
    istream &ler(istream &I);
    inline ostream &salvar(ostream &O) const {return imprimir(O);}
};

inline istream &operator>>(istream &I, DVD &X) {return X.digitar(I);}
inline ostream &operator<<(ostream &O, DVD &X) {return X.imprimir(O);}

///LISTA LIVRO
class ListaLivro
{
private:
    Livro *x;
    unsigned N;
    void criar(const unsigned &num);
    void copiar(const ListaLivro &L);
    void limpar();
public:
    inline ListaLivro(): x(NULL), N(0) {};
    inline ListaLivro(const ListaLivro &L): x(NULL), N(0) {copiar(L);}
    explicit ListaLivro(const unsigned &nume) {criar(nume);}
    ~ListaLivro() {limpar();}
    void operator=(const ListaLivro &L) {if(this!=&L){limpar();copiar(L);}}

    void incluir(const Livro &L);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    void salvar(ostream &O) const;
};

///LISTA CD
class ListaCD
{
private:
    CD *x;
    unsigned N;
    void criar(const unsigned &num);
    void copiar(const ListaCD &L);
    void limpar();
public:
    inline ListaCD(): x(NULL), N(0) {};
    inline ListaCD(const ListaCD &L): x(NULL), N(0) {copiar(L);}
    explicit ListaCD(const unsigned &nume) {criar(nume);}
    ~ListaCD() {limpar();}
    void operator=(const ListaCD &L) {if(this!=&L){limpar();copiar(L);}}

    void incluir(const CD &L);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    void salvar(ostream &O) const;
};

///LISTA DVD
class ListaDVD
{
private:
    DVD *x;
    unsigned N;
    void criar(const unsigned &num);
    void copiar(const ListaDVD &L);
    void limpar();
public:
    inline ListaDVD(): x(NULL), N(0) {};
    inline ListaDVD(const ListaDVD &L): x(NULL), N(0) {copiar(L);}
    explicit ListaDVD(const unsigned &nume) {criar(nume);}
    ~ListaDVD() {limpar();}
    void operator=(const ListaDVD &L) {if(this!=&L){limpar();copiar(L);}}

    void incluir(const DVD &L);
    void excluir(unsigned id);
    void imprimir() const;
    void ler(istream &I);
    void salvar(ostream &O) const;
};

///LOJA
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
