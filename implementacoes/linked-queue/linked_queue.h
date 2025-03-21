#include <cstdint>

namespace structures {

template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();

    ~LinkedQueue();

    void clear();   // limpar

    void enqueue(const T& data);    // enfilerar

    T dequeue();    // desenfilerar

    T& front() const;   // primeiro dado

    T& back() const;    // último dado

    bool empty() const;     // fila vazia

    std::size_t size() const;   // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data},
            next_{nullptr}
        {}
        Node(const T& data, Node *next):
            data_{data},
            next_{next}
        {}
        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }
        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }
        void next(Node* next) {
            next_ = next;
        }

     private:
        T data_;
        Node* next_;
    };

    Node* head;     // nodo-cabeça
    Node* tail;     // nodo-fim
    std::size_t size_;  // tamanho
};

}   // namespace structures

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (!empty()) {
        dequeue();
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node *novo = new Node(data);
    if (empty()) {
        head = novo;
    } else {
        tail->next(novo);
    }
    tail = novo;
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Fila Vazia");
    } else {
        Node* saiu;
        T aux;

        saiu = head;
        aux = saiu->data();
        head = head->next();

        delete(saiu);
        size_--;
        return aux;
    }
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Fila Vazia");
    } else {
        return head->data();
    }
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Fila Vazia");
    } else {
        return tail->data();
    }
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}
