#include <string>
#include "fila.h"

using namespace std;

structures::ArrayQueue<char> editaTexto(string texto) {
    int tamanho = texto.length();
    structures::ArrayQueue<char> fila(500);

    for (int i=0; i < tamanho; i++) {
        if (texto[i] == '<') {
            fila.dequeue();
        } else if (texto[i] == '>') {
            char ultimo = fila.back();
            fila.enqueue(ultimo);
        } else {
            fila.enqueue(texto[i]);
        }
    }
    return fila;
}
