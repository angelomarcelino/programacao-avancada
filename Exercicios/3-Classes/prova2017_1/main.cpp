#include <iostream>
#include <string>
#include "voo.h"
#include "lista_voo.h"
using namespace std;

int main(void)
{
     ListaVoos LV;
     Voo V;
     string codigo;
     int opcao;
     cout << "PROGRAMA PARA IMPLEMENTAR UMA LISTA DE VOOS\n";
     do
     {
         do
         {
             cout << "1 - Inserir um novo voo na lista\n";
             cout << "2 - Imprimir todos os voos da lista\n";
             cout << "3 - Procurar um voo a partir da origem\n";
             cout << "0 - Terminar o programa\n";
             cin >> opcao;
         } while (opcao<0 || opcao>3);
         switch (opcao)
         {
             case 1:
                 cout << "Voo a ser inserido:\n";
                 cin >> V;
                 LV.inserir(V);
             break;
             case 2:
                LV.imprimir();
             break;
             case 3:
                 cout << "Aeroporto de origem a pesquisar:\n";
                 cin >> codigo;
                 LV.imprimir(codigo);
             break;
             default:
             break;
         }
     } while (opcao!=0);
     return 0;
}
