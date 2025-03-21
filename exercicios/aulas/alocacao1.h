#include <string>


class Aluno {
 public:
    Aluno() {}  // construtor
    ~Aluno() {}  // destrutor
    std::string devolveNome() {
        return nome;
    }
    int devolveMatricula() {
        return matricula;
    }
    void escreveNome(std::string nome_) {
        nome = nome_;
    }
    void escreveMatricula(int matricula_) {
        matricula = matricula_;
    }
 private:
    std::string nome;
    int matricula;
};

Aluno *turma_filtra(Aluno t[], int N, int menor_matr) {
    Aluno *tf;
    tf = nullptr;  // retirar e alocar (com new)
    tf = new Aluno[N];
    int j = 0;
    for (int i = 0; i < N; i++) {
        if (t[i].devolveMatricula() >= menor_matr) {
            tf[j] = t[i];
            j++;
        }
    }
    return tf;
}

int *turma_conta(Aluno t[], int N) {
    int *c;
    c = nullptr;  // retirar e alocar (com new)
    c = new int[26](); // uso de () para inicializar todos os elementos do array como 0
    for (int i = 0; i < N; i++) {
        std::string nome = t[i].devolveNome();
        char primeira_letra = nome[0];
        if (primeira_letra >= 'A' && primeira_letra <= 'Z') {
            int posicao = primeira_letra - 'A';
            c[posicao]++; // incrementa o elemento desejado para aquela letra
        }
    }
    return c;
}

/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
