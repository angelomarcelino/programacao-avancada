#include <iostream>

using namespace std;


void ordena(float &A, float &B, float &C)
{
    float maior, menor, meio;
    maior = A;
    if (B>maior)
        maior = B;
    if (C>maior)
        maior = C;

    menor = A;
    if (B<menor)
        menor = B;
    if (C<menor)
        menor = C;

    meio = A;
    if (meio>B && meio>C)
    {
        if (B>C)
            meio = B;
        else
            meio = C;
    }
    if (meio<B && meio<C)
    {
        if (B<C)
            meio = B;
        else
            meio = C;
    }

    C = maior;
    B = meio;
    A = menor;
}


int main()
{
    float a,b,c;
    a=0;
    while (a != -1)
    {
        cout<<"\nEntre com os numeros: ";
        cin>>a>>b>>c;
        ordena(a,b,c);
        cout<<"\nNumeros ordenados: "<<c<<" "<<b<<" "<<a<<endl;
    }
    return 0;
}
