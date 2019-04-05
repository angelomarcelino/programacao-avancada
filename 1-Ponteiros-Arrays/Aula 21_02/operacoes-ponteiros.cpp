#include <iostream>

/*
Neste programa, sao apresentadas algumas operacoes basicas envolvendo ponteiros.
Existem erros em 8 linhas do programa. Tente encontra-los antes de compilar.
Alem disso, apos eliminar os erros, tente prever o que serah impresso antes de executar.
*/

using namespace std;

int main(void)
{
  int v1;
  float v2;

  void *p1;
  int *p2;


  v1 = 666;
  v2 = 3.1416;

  p1 = &v1;
  ///p2 = &v2;
  ///p2 = p1;

  ///&v1 = p2; endereços de variaveis são constantes.

  ///*p1 = 777;
  ///*p2 = 888; erro lógico, o numero é armazenado

  p2 = &v1;
  *p2 = 999;
  v2 = 2*(*p2);


  cout << "=================\n";
  cout << p1 << endl;
  cout << &p1 << endl;
  cout << sizeof(p1) << endl;
///  cout << *p1 << endl;
  cout << "=================\n";

  cout << "=================\n";
  cout << p2 << endl;
  cout << &p2 << endl;
  cout << sizeof(p2) << endl;
  cout << *p2 << endl;
  cout << "=================\n";

  cout << "=================\n";
  cout << v1 << endl;
  cout << &v1 << endl;
  cout << sizeof(v1) << endl;
///  cout << *v1 << endl;
  cout << "=================\n";

  cout << "=================\n";
  cout << v2 << endl;
  cout << &v2 << endl;
  cout << sizeof(v2) << endl;
///  cout << *v2 << endl;
  cout << "=================\n";

  return 0;
}
