#include "pilha.h"

using namespace std;

bool verificaChaves(string trecho_programa) {
    bool resposta = true;
    int  tamanho  = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);
    
    for (int i = 0; i < tamanho; i++) {
        // condições de parada dor 'for' podem ser adicionadas...

        if (trecho_programa[i] == '{')    // se encontrar { adiciona na pilha
            pilha.push(trecho_programa[i]);

        if (trecho_programa[i] == '}') {    //se encontrar } remove da pilha
            if (pilha.empty()) {     // caso encontre } sem antes ter um {
                resposta = false;
                break;
            }
            pilha.pop();
        }
    }
    if (!pilha.empty())
        resposta = false;

    return resposta;
}
    