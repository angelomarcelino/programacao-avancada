#include <iostream>
 using namespace std;

 int contador(int d, int m, int a)
 {
    int total = 0;

    for (int i=1; i<m; i++)
    {
        if (i<=7)
        {
            if(i%2==0)
            {
               if(i==2)
               {
                    if ((a%400==0) || ((a%4==0) && (a%100!=0)))
                        total += 29;
                    else
                        total += 28;
                }
                else
                    total += 30;
            }
            else
                total += 31;
        }
        else
        {
            if(i%2==0)
                total += 31;
            else
                total += 30;
        }
        /// cout << total << " ";
    }
    total += d;

    return total;
 }


 int main()
 {
    int dia, mes, ano;
    dia=0;
    while (dia != -1)
    {
        cout<<"\n Entre com a data: ";
        cin>>dia>>mes>>ano;
        cout<<endl<<"Total de dias: "<<contador(dia,mes,ano)<<endl;
    }
    return 0;
 }
