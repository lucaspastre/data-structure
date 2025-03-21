#include <cstdint>

namespace structures {

template<typename T>
class LinkedStack {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();   // limpa pilha

    void push(const T& data);   // empilha

    T pop();    // desempilha

    T& top() const;     // dado no topo

    bool empty() const;     // pilha vazia

    std::size_t size() const;   // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        T& data() {        // getter: info
            return data_;
        }
        const T& data() const {   // getter-constante: info
            return data_;
        }
        Node* next() {     // getter: próximo
            return next_;
        }
        const Node* next() const {      // getter-constante: próximo
            return next_;
        }
        void next(Node* next) {     // setter: próximo
            next_ = next;
        }

     private:
        T data_;        // elemento de pilha
        Node* next_;
    };

    Node* top_;     // nodo-topo        // cabeça de pilha
    std::size_t size_;  // tamanho
};

}  // namespace structures

template <typename T>
structures::LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template <typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template <typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template <typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node *novo = new Node(data, top_);
    top_ = novo;
    size_++;
}

template <typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Pilha Vazia");
    }
    Node *saiu;
    T volta;
    saiu = top_;
    volta = saiu->data();
    top_ = saiu->next();
    delete saiu;    // é preciso liberar a memória do nó que saiu
    size_--;
    return volta;
}

template <typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Pilha Vazia");
    } else {
        return top_->data();
    }
}

template <typename T>
bool structures::LinkedStack<T>::empty() const {
    return (size_ == 0);    // obs: full() não existe mais aqui
}                           // verificar se tem espaço será responsabilidade dos métodos de adição

template <typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
