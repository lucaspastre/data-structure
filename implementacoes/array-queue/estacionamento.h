
#include "fila.h"

void retira_veiculo(structures::ArrayQueue<int> *f, int k) {
    int carro;
    for (int i = 0; i < (k-1); i++) {
        carro = f->dequeue();
        f->enqueue(carro);
    }
    f->dequeue();
}

void mantenha_veiculo(structures::ArrayQueue<int> *f, int k) {
    int carro;
    for (int i=0; i < (k-1); i++) {
        f->dequeue();
    }
    carro = f->dequeue();
    f->clear();
    f->enqueue(carro);
}

/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/