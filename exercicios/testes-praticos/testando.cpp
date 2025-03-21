#include <iostream>
#include "teste_pratico1.h"

using namespace std;

int main() {
    structures::LinkedList<char> lista_teste;
    lista_teste.push_back('A');
    lista_teste.push_back('B');
    lista_teste.push_back('C');
    lista_teste.push_back('D');
    lista_teste.push_back('E');    

    lista_teste.invert();

    for (size_t i=0; i < lista_teste.size(); i++) {
        cout << lista_teste.at(i) << endl;
    }

    auto lista_halve = lista_teste.halve();

    auto *lista_par = lista_halve.at(0);
    auto *lista_impar = lista_halve.at(1);

    for (size_t i = 0; i < lista_par->size(); i++) {
        cout << lista_par->at(i) << " ";
    }
    
    cout << endl;

    for (size_t i = 0; i < lista_impar->size(); i++) {
        cout << lista_impar->at(i) << " ";
    }
}
