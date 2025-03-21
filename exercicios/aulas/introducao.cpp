#include <iostream>

#define mensagem cout << "Bem-vindo!" << endl;
using namespace std;

int main () {
    int valor;
    char teste = 'a';
    double a1; //4.9999999 (maior precisão) - ocupa 8 bytes de memória (64 bits)
    float a2; //5 (menor precisão) - ocupa 4 bytes de memória (32 bits)

    a1 = 4.21;
    a2 = 7.12;

    mensagem
    cout << "Digite o valor:" << endl;
    cin >> valor;
    cout << "Valor inserido: " << valor << endl;
    cout << a1 << endl;
    cout << a2 << endl;

    return 0;

}
