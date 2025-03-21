#include <iostream>
#include <iomanip>

using namespace std;

struct Jogo {
    string nome;
    float preco;
    int horas;
    float custo;
};

Jogo adquirir(const string& titulo, float valor);
void atualizar(Jogo& jogo, float valor);
void jogar(Jogo& jogo, int tempo);
void exibir(const Jogo& jogo);

int main() {
    Jogo red_dead;
    red_dead = adquirir("Red Dead Redemption 2", 99.99);
    jogar(red_dead, 360);
    exibir(red_dead);

}

Jogo adquirir(const string& titulo, float valor) {
    Jogo novo_jogo;
    novo_jogo.nome = titulo;
    novo_jogo.preco = valor;
    novo_jogo.horas = 0;
    novo_jogo.custo = valor;

    return novo_jogo;
}

void atualizar(Jogo& jogo, float valor) {
    jogo.preco = valor;

    if (jogo.horas > 0) {
        jogo.custo = jogo.preco / jogo.horas;
    }
}

void jogar(Jogo& jogo, int tempo) {
    jogo.horas += tempo; 

    if (jogo.horas > 0) {
        jogo.custo = jogo.preco / jogo.horas;
    }
}

void exibir(const Jogo& jogo) {
    cout << fixed << setprecision(2);
    cout << "Nome do Jogo: " << jogo.nome << endl;
    cout << "Preco do jogo: R$" << jogo.preco << endl;
    cout << "Tempo de jogo: " << jogo.horas << "/h" << endl;
    cout << "Custo do jogo: R$" << jogo.custo << "/h" << endl;

}

