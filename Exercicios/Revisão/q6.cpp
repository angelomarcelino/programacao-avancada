#include <iostream>
using namespace std;

struct Notas{
    int n2=0,n5=0,n10=0,n20=0,n50=0,n100=0;
};

Notas separador(unsigned int A)
{
    int u,d,c;
    Notas N;

    u = A%10;
    if(u%2==0) N.n2 = u/2;
    if(u==5) N.n5 = 1;
    if(u==7)
    {
        N.n2 = 1;
        N.n5 = 1;
    }

    A = A/10;
    d = A%10;
    if(d<5)
    {
        N.n20 = d/2;
        N.n10 = d%2;
    }
    else
    {
        N.n50 = d/5;
        N.n20 = (d%5)/2;
        N.n10 = (d%5)%2;
    }

    A = A/10;
    N.n100 = A;
    return N;
}

int main()
{
    unsigned int valor;
    Notas nts;

    do{
        cout<<"Entre o valor: ";
        cin>>valor;
        if(valor>2)
        {
            nts = separador(valor);
            cout << "Notas de 2: " << nts.n2 << endl;
            cout << "Notas de 5: " << nts.n5 << endl;
            cout << "Notas de 10: " << nts.n10 << endl;
            cout << "Notas de 20: " << nts.n20 << endl;
            cout << "Notas de 50: " << nts.n50 << endl;
            cout << "Notas de 100: " << nts.n100 << endl;
        }
        else
        cout<<"\n Valor inválido."<<endl;
    }while(valor>2);

    return 0;
}
