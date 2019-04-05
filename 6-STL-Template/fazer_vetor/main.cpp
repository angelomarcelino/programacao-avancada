#include <iostream>
#include "vetor_template.h"

using namespace std;




int main()
{
    vector<float> Z;

    Z.push_back(3.14);    // Z[0]
    Z.push_back(0.6667);  // Z[1]
    Z.push_back(-15);     // Z[2]

    Z[2] = -7.2;  // Usa o operator[] nao const
    Z[3] = 1;     // Gera erro
    for (unsigned i=0; i<Z.size(); i++) cout << Z[i] << ' ';  // Usa o operator[] const
    cout << endl;
}
