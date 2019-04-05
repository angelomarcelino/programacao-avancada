#include <iostream>
#include <string.h>
#include <stdio.h>
#include "voo.h"

using namespace std;

void Voo::operator=(const Voo &V)
{
    n_voo=V.n_voo; h_dep=V.h_dep; h_arrv=V.h_arrv; from=V.from; to=V.to;
}

ostream &operator<<(ostream &X, const Voo &V)
{
    X << "Dados do voo: \n"
      << "Numero do voo: " << V.n_voo << "\n"
      << "Hora de saida: " << V.h_dep << "\n"
      << "Hora de chegada: " << V.h_arrv << "\n"
      << "Aeroporto de saida: " << V.from << "\n"
      << "Aeroporto de cehgada: " << V.to << "\n";
    return X;
}

string ler_voo()
{
    string flight;
    bool nome_valido = true;
    do
    {
        if(!nome_valido) cout << "Entre com um codigo valido: \n";
        cin >> flight;
        nome_valido = (flight.size()==3);
        for(unsigned i=0; i<3; i++)
        {
            flight[i] = toupper(flight[i]);
            nome_valido = (flight[i]>='A' && flight[i]<='Z');
        }
    }while(!nome_valido);
    return flight;
}

unsigned ler_hora()
{
    unsigned valor, hr, minu;
    bool valor_valido=true;
    do
    {
        if(!valor_valido) cout << "Entre um valor valido: \n";
        cin >> valor;
        hr = valor/100;
        minu = valor%100;
        valor_valido = (hr<=23 && minu<=59);
    }while (!valor_valido);
    return valor;
}

istream &operator>>(istream &X, Voo &V)
{
    cout << "Entre com os dados do voo: \n";
    do
    {
        cout << "Numero do voo: ";
        X >> V.n_voo;
    } while (V.n_voo<1000 || V.n_voo>9999);
    cout << "Aeroporto de saida: ";
    V.from = ler_voo();
    cout << "Aeroporto de chegada: ";
    V.to = ler_voo();
    cout << "Horario de saida (0000 a 2359): ";
    V.h_dep = ler_hora();
    cout << "Horario de cehgada (0000 a 2359): ";
    V.h_arrv = ler_hora();
    return X;
}
