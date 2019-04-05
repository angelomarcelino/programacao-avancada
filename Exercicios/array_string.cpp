#include <iostream>
using namespace std;

char* abrev(char x[])
{
    static char nome[80];
    unsigned int i(0);
    int cont(0);
    //int espc(0);
    for( i=0; x[i]!='0'; i++)
    {
        nome[i]=x[i];
        cont++;
    }
    nome[i]='0';
    cont++;

    for(int j=1; j<cont; j++)
    {
        if(nome[j-1]==' ')
        {
            while (nome[j+1]!=' ' || nome[j+1]!='0')
            {
                for(int k=j+1; k<cont; k++)
                {
                    nome[k]=nome[k+1];
                }
            }
        }
    }

    cout << endl << nome[i];
    cout << endl << cont;
    //cout << endl << espc;
    return nome;
}

int main ()
{
    char s1[80];
    cout << "Entre com seu nome completo, terminando com 0: ";
    cin.getline(s1,80);
    cout << endl << s1;
    cout << endl << abrev(s1);
    return 0;
}
