#include <iostream>

using namespace std;

int INVERSA(unsigned int num)
{
    int inv(0),i(10),a;
    do{
        a = num%i;
        inv = inv + a;
        num = num - a;
        if(num>0)
        {
            num = num/10;
            inv *= 10;
        }
    }while(num>0);

    return inv;
}

int main()
{
    int a;
    cin>>a;
    cout<<endl<<INVERSA(a);

    return 0;
}
