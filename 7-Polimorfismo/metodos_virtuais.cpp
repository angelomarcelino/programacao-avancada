#include <iostream>

using namespace std;

// CLASSE BASE
class base {
public:
  virtual ~base();
  virtual void vfunc();
};

base::~base() {
  cout << "Destrutor de base\n";
}

void base::vfunc() {
  cout << "Esta eh vfunc() de base\n";
}

// CLASSE DERIVADA
class derived1 : public base {
public:
  ~derived1();
  void vfunc();
};

derived1::~derived1() {
  cout << "Destrutor de derived1\n";
}

void derived1::vfunc() {
  cout << "Esta eh vfunc() de derived1\n";
}

// CLASSE DERIVADA
class derived2 : public base {
public:
  ~derived2();
  void vfunc();
};

derived2::~derived2() {
  cout << "Destrutor de derived2\n";
}

void derived2::vfunc() {
  cout << "Esta e vfunc() de derived2\n";
}

// Criar um typedef para se referir a um ponteiro para uma classe
// Isso permite, embora sejam identicos, usar uma notacao diferente
// para simples ponteiros para 1 elemento e para arrays:
// pt_base x;  // x eh um ponteiro para base
// base *x;    // e eh um "array" de base's
// pt_base *x; // x eh um array de ponteiros para base
typedef base *pt_base;

int main(void)
{
  // A lista de elementos
  pt_base *x;
  // Numero de elementos
  int N;
  // Opcao
  int opcao;

  do
  {
    cout << "Quantos elementos (1 a 10)? ";
    cin >> N;
  } while (N<1 || N>10);

  // Cria um array de N ponteiros para base's
  x = new pt_base[N];

  // Criar os N elementos
  for (int i=0; i<N; i++)
  {
      do
      {
          cout << "Classe do elemento " << i << ":\n";
          cout << "0 - Base\n";
          cout << "1 - Derived 1\n";
          cout << "2 - Derived 2\n";
          cout << "Qual tipo? ";
          cin >> opcao;
      } while (opcao<0 || opcao>2);
      switch(opcao)
      {
      case 0:
        x[i] = new base;
        break;
      case 1:
        x[i] = new derived1;
        break;
      case 2:
        x[i] = new derived2;
        break;
      }
  }

  // Imprimir
  cout << "\nIMPRESSAO:\n";
  for (int i=0; i<N; i++)
  {
      x[i]->vfunc();
  }

  // Liberar as areas de memoria
  cout << "\nDESTRUICAO:\n";
  for (int i=0; i<N; i++)
  {
      // Libera cada um dos elementos
      // Atencao: criado com new, liberado com delete
      cout << "Liberando elemento " << i << ":\n";
      delete x[i];
  }
  // Libera o array
  // Atencao: criado com new[], liberado com delete[]
  cout << "Liberando o array:\n";
  delete[] x;

  return(0);
}
