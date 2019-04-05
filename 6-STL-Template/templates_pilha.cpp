#include <iostream>

using namespace std;

template <class Dado>
class pilha;

template <class Dado>
class noh
{
private:
    noh *next;
    Dado x;
    friend class pilha<Dado>;
};

template <class Dado>
class pilha
{
private:
    unsigned N;
    noh<Dado> *inicio;
    void copiar(const pilha &P);
    void limpar();
public:
    inline pilha(): N(0), inicio(NULL) {}
    inline pilha(const pilha &P) {copiar(P);}
    inline void operator=(const pilha &P) {limpar(); copiar(P);}
    inline ~pilha() {limpar();}
    inline unsigned size() {return N;}
    void inserir(const Dado &X);
    Dado primeiro() const;
    void excluir();
};

template<class Dado>
void pilha<Dado>::limpar()
{
    while (N>0) {
        excluir();
    }
}

template <class Dado>
void pilha<Dado>::inserir(const Dado &X)
{
    noh<Dado> *prov = new noh<Dado>;
    prov->next = inicio;
    prov->x = X;
    inicio = prov;
    N++;
}

template <class Dado>
void pilha<Dado>::excluir()
{
    if (N>0) {
        noh<Dado> *prov = inicio;
        inicio = inicio->next;
        delete prov;
        N--;
    }
    else {
        cerr << "Exclusao em pilha vazia\n!";
    }
}

template <class Dado>
Dado pilha<Dado>::primeiro() const
{
    if (N>0) {
        return inicio->x;
    }
    cerr << "Consulta em pilha vazia\n";
    return Dado(0);
}

int main(void)
{
    pilha<int> P;
    int num;

    cout << "Digite  os numeros a serem armazenados na pilha (0 para terminar):\n";
    do {
        cout << "Numero: ";
        cin >> num;
        if (num!=0)
        {
            P.inserir(num);
        }
    } while (num != 0);
    cout << "Os numeros digitados foram:\n";
    while (P.size() > 0)
    {
        cout << P.primeiro() << ' ';
        P.excluir();
    }
    cout << endl;
}
