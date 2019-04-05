/*
    O objetivo eh fazer um programa que solicite ao usuario que
    digite uma sequencia de numeros reais nao nulos. Quando o
    usuario digitar zero, entende-se que ele concluiu a entrada
    dos dados.
    Apos a entrada dos dados, o programa deve calcular e imprimir
    as seguintes informacoes:
    1) A media aritmetica dos numeros digitados (sem incluir o
    zero final).
    2) Quantos dos numeros estao acima e abaixo da media (sem
    contar com o zero final.
*/

#include <iostream>

using namespace std;

int main()
{
    float Num;
    unsigned N = 0;
    float *arr = NULL;
    unsigned i = 0;

    do
    {
        cout << "Digite um numero [0.0 para parar]: ";
        cin >> Num;
        if (Num != 0.0)
        {
            float *prov = new float[N+1]; ///Faz o ponteiro ter N+1 elementos (equivale: float i[n+1])
            ///prov so existe nesse if
            for (i=0; i<N ; i++) prov[i] = arr[i];
            prov[N] = Num;

            if (arr != NULL) delete[] arr; ///deleta o arr antigo
            arr = prov; /// arr armazena o endereço que prov aponta
            N++;
        }
    } while (Num != 0.0);

    if (N==0)
    {
        cout << "Voce nao digitou nenhum numero!!!\n";
    }
    else
    {
        float soma(0.0); ///Equevalente a float soma = 0.0
        for(i=0; i<N; i++) soma = soma + arr[i];

        float media = soma/N;
        unsigned num_abaixo(0), num_acima(0);

        for(i=0; i<N; i++)
        {
            if(arr[i]>media) num_acima++;
            if(arr[i]<media) num_abaixo++;
        }

        cout << "Numeros digitados:";
        for(i=0; i<N; i++) cout << ' ' << arr[i];
        cout << endl;
        cout << "A media eh: " << media << endl;
        cout << "Acima da media: " << num_acima << endl;
        cout << "Abaixo da media: " << num_abaixo << endl;
    }

    if (arr != NULL) delete[] arr;
    return 0;
}
