#include <iostream>
#include <stdlib.h> // para função malloc (memory allocation)

using namespace std;

int main() {
    char *name;
    name = (char *) malloc(sizeof(char)+1);
    // cast para converter o returno tipo void para tipo char
    // a função sizeof retorna o tamanho de determinado tipo
    // +1 para o caracter finalizador /0
    gets(name); // a função gets() contorna o problema do cin de entender o espaço como caractere finalizador
    cout << name << endl;

    free(name); //libera a memória (boa prática)

    return 0;
}
