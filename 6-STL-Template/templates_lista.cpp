#include <iostream>

using namespace std;

template <class DADO>
class noh;

template <class DADO>
class apont;

template <class DADO>
class Lista;

/// Classe que soh tem construtor privado, para ser usada unicamente pela classe Lista
template <class DADO>
class noh
{
private:
    DADO dado;
    noh *next;
    noh *prev;
    inline noh(const DADO &F): dado(F), next(NULL), prev(NULL) {}
public:
    friend class apont<DADO>;
    friend class Lista<DADO>;
};

template <class DADO>
class apont
{
private:
    noh<DADO> *x;
    inline apont(noh<DADO> *N): x(N) {}
public:
    inline apont(): x(NULL) {}
    inline bool operator==(apont<DADO> A) const {return x==A.x;}
    inline bool operator!=(apont<DADO> A) const {return x!=A.x;}
    inline void operator++() {if (x!=NULL) x=x->next;}
    inline void operator++(int i) {if (x!=NULL) x=x->next;}
    inline const DADO &operator*() const {return x->dado;}
    friend class Lista<DADO>;
};

template <class DADO>
class Lista
{
private:
    unsigned N;
    noh<DADO> *first;
    noh<DADO> *last;
    void copy(const Lista &L);
public:
    void clear();
    inline Lista(): N(0), first(NULL), last(NULL) {}
    inline Lista(const Lista &L) {copy(L);}
    inline ~Lista() {clear();}
    inline void operator=(const Lista &L) {clear();copy(L);}

    inline unsigned size() const {return N;}
    inline apont<DADO> begin() const {return apont<DADO>(first);}
    inline apont<DADO> end() const {return apont<DADO>(NULL);}  /// Retorna um apontador para depois do ultimo

    void insert(const DADO &Valor, apont<DADO> pos);
    inline void push_front(const DADO &Valor) {insert(Valor, begin());}
    inline void push_back(const DADO &Valor) {insert(Valor, end());}
    void erase(apont<DADO> pos);
    inline void pop_front() {erase(begin());}
    inline void pop_back() {erase(apont<DADO>(last));}
};

template <class DADO>
void Lista<DADO>::copy(const Lista<DADO> &L)
{
    apont<DADO> prov = L.begin();

    N = 0;
    first = last = NULL;
    while (prov != L.end())
    {
        push_back(*prov);
        prov++;
    }
}

template <class DADO>
void Lista<DADO>::clear()
{
    noh<DADO> *prov(first), *prov2;
    while (prov != NULL)
    {
        prov2 = prov->next;
        delete prov;
        prov = prov2;
    }
    N = 0;
    first = last = NULL;
}

/// pos.x aponta para o noh da lista na frente do qual o novo noh deve ser inserido;
/// NULL se deve ser inserido no fim da lista
template <class DADO>
void Lista<DADO>::insert(const DADO &Valor, apont<DADO> pos)
{
    noh<DADO> *novo = new noh<DADO>(Valor);

    novo->next = pos.x;
    if (pos.x != NULL) novo->prev = pos.x->prev;
    else novo->prev = last;

    if (novo->next != NULL) novo->next->prev = novo;
    else last = novo;
    if (novo->prev != NULL) novo->prev->next = novo;
    else first = novo;

    N++;
}

/// pos.x aponta para o elemento a ser removido
template <class DADO>
void Lista<DADO>::erase(apont<DADO> pos)
{
    if (N>0 && pos.x!=NULL)
    {
        if (pos.x->next != NULL) pos.x->next->prev = pos.x->prev;
        else last = pos.x->prev;
        if (pos.x->prev != NULL) pos.x->prev->next = pos.x->next;
        else first = pos.x->next;

        delete pos.x;
        N--;
    }
}

int main()
{
    Lista<float> Z;
    apont<float> it;
    float X;

    cout << "Digite valores a serem inseridos (0 p/ terminar):\n";
    do
    {
        cout << "Valor: ";
        cin >> X;
        if (X != 0.0) Z.push_back(X);
    } while (X != 0.0);

    Lista<float> Y(Z);
    Z.pop_back();
    Z.pop_front();

    for (it=Z.begin(); it!=Z.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
    for (it=Y.begin(); it!=Y.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
}
