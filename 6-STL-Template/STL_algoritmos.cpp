#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Pessoa
{
private:
  string nome;
  int idade;
public:
  inline Pessoa(string no, int id): nome(no), idade(id) {}
  inline string getNome() const {return nome;}
  inline int getIdade() const {return idade;}
  /// Os operadores ==
  inline bool operator==(const Pessoa &P) const {return (nome==P.nome && idade==P.idade);}
  inline bool operator==(const string &S) const {return nome==S;}
  inline bool operator==(int I) const {return idade==I;}
  /// O operador <
  inline bool operator<(const Pessoa &P) const {return (idade<P.idade);}
};

ostream &operator<<(ostream &O, const Pessoa &P)
{
    O << P.getNome() << '|' << P.getIdade();
    return O;
}

inline void imprimir(const Pessoa &P)
{
  cout << P << endl;
}

inline bool ordena_por_nome(const Pessoa &A, const Pessoa &B)
{
  return (A.getNome() < B.getNome());
}

int main()
{
  vector<Pessoa> VP;
  vector<Pessoa>::iterator ptr;

  VP.push_back(Pessoa("Joao", 25));
  VP.push_back(Pessoa("Maria", 32));
  VP.push_back(Pessoa("Carla", 4));
  VP.push_back(Pessoa("Abel", 30));

  /// imprimindo a lista (sem algoritmo STL)
  for (ptr=VP.begin(); ptr!=VP.end(); ptr++)
  {
      cout << *ptr << endl;
  }
  cout << "================\n";

  /// imprimindo a lista (com algoritmo STL)
  for_each(VP.begin(), VP.end(), imprimir);
  cout << "================\n";

  /// Procurando Maria
  ptr = find(VP.begin(), VP.end(), "Maria");
  if (ptr == VP.end())
  {
      cout << "Nao existe nenhuma Maria!\n";
  }
  else
  {
      cout << "Maria encontrada:\n";
      cout << *ptr << endl;
  }
  cout << "================\n";

  /// Procurando alguem de idade 4
  ptr = find(VP.begin(), VP.end(), 4);
  if (ptr == VP.end())
  {
      cout << "Nao existe nenhuma pessoa de idade 4!\n";
  }
  else
  {
      cout << "Pessoa de idade 4 encontrada:\n";
      cout << *ptr << endl;
  }
  cout << "================\n";

  /// Procurando Joao de idade 30
  ptr = find(VP.begin(), VP.end(), Pessoa("Joao", 30));
  if (ptr == VP.end())
  {
      cout << "Nao existe nenhum Joao de idade 30!\n";
  }
  else
  {
      cout << "Joao de idade 30 encontrado:\n";
      cout << *ptr << endl;
  }
  cout << "================\n";

  /// Colocando em ordem de idade (usando operator<)
  sort(VP.begin(), VP.end());
  cout << "Imprimindo a lista ordenada por idade:\n";
  for_each(VP.begin(), VP.end(), imprimir);
  cout << "================\n";

  /// Colocando em ordem alfabetica de nome (usando funcao ordena_por_nome)
  sort(VP.begin(), VP.end(), ordena_por_nome);
  cout << "Imprimindo a lista ordenada por nome:\n";
  for_each(VP.begin(), VP.end(), imprimir);
  cout << "================\n";
}

