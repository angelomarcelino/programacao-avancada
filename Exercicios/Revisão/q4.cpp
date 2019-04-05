#include <iostream>
 using namespace std;

 int main() /// Tava como "void main()"
 {
     int x, y, p, a;
     cout << "Informe dois números: ";
     cin >> x;
     cin >> y;
     p = 0;
     a = y;
     while(a > 0) ///Essa função multiplica x * y
     {
         p += x;
         a--;
     }
     cout << "\nResultado: " << p << endl; ///Caso x = 3, y = 4, p=12;
     return 0;
 }
