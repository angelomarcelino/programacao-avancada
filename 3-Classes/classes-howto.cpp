#include <iostream>
using namespace std;

struct toto ///Default de struct eh um dado publico
{
private: ///Sendo privado, x somente pode ser acessado
         /// por outro membro da classe.
    double x;
};


class teste  ///Default de classe eh um dado privado
{
private:    ///Sendo privado, y somente pode ser acessado
            /// por outro membro da classe.

    int i;
    float x;
    /* void f(int i); */  /// y pode ser acessado por funcoes
                          /// dentro da classe

public:
    ///sintaxe de fz construtora, quase sempre sao publicos.

    inline teste(): i(0), x(0.0) {}                  ///construtor default (SEMPRE CRIE ESSA MERDA)
    inline teste(teste &T): i(T.i), x(T.x) {}        ///construtor por copia (SEMPRE EXISTE)
    inline teste(int Valor): i(Valor), x(0.0) {}
    inline teste(int VI, float VF): i(VI), x(VF) {}  ///chama a fz somente na linha

    void imprimir();
    ~teste();   ///destrutora
};


/* teste::teste() ///fz construtora (caso codigo seja necessario)
{
    cout << "Construtor \n";
    //i=0;
}; */


/* teste::teste(int Valor) ///fz construtora 1 (caso codigo seja necessario)
{
    cout << "Construtor 1 \n";
    //i=Valor;
}; */


teste::~teste() ///fz destrutora
{
    cout << "Destrutor \n";
}


void teste::imprimir(void)     ///sintaxe de implementacao
{
    cout << i << '\t' << x << endl;
}


int main()
{
    teste x;     ///equivalente a chamar X.construtor();
    teste y(37); ///chama a fz constr que recebe o parametro int 37;
    teste z(-12, 3.14159265359);
    teste w(z);

    x.imprimir();
    y.imprimir();
    z.imprimir();
    w.imprimir();
    return 0;
}               ///ao encerrar o scopo de main(),
                ///chama-se a funcao X.destrutor(), para liberar
                ///a memoria de X.
