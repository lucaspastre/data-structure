#include <stdexcept> 

namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();  // construtor
    ~DoublyCircularList();  // destrutor

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data},
            prev_{nullptr},
            next_{nullptr}
        {}
        Node(const T& data, Node* next):
            data_{data},
            prev_{nullptr},
            next_{next}
        {}
        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}
        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };
    Node* head;
    std::size_t size_;
};

}  // namespace structures

// Implementação dos métodos da lista
template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() : head(nullptr), size_(0) {
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template <typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    Node* novo = new Node(data);
    if (empty()) {
        head = novo;
        head->next(head);
        head->prev(head);
    } else {
        Node* tail = head->prev();
        tail->next(novo);
        novo->prev(tail);
        novo->next(head);
        head->prev(novo);
    }
    size_++;    // incrementa o tamanho
}

template <typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* novo = new Node(data);
    if (empty()) {
        head = novo;
        head->next(head);
        head->prev(head);
    } else {
        Node* tail = head->prev();
        novo->next(head);
        novo->prev(tail);
        tail->next(novo);
        head->prev(novo);
        head = novo;
    }
    size_++;    // incrementa o tamanho
}

template <typename T>
void structures::DoublyCircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {  // Verificação de limite
        throw std::out_of_range("índice fora de alcance");
    }
    if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        Node* novo = new Node(data);
        Node* atual = head;
        for (std::size_t i=0; i < index; ++i) {
            atual = atual->next();
        }
        Node* anterior = atual->prev();
        anterior->next(novo);
        novo->prev(anterior);
        novo->next(atual);
        atual->prev(novo);
        size_++;
    }
}

template <typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty() || data <= head->data()) {
        push_front(data);
    } else {
        Node* atual = head->next();
        std::size_t index = 1;
        while (atual != head && data > atual->data()) {
            atual = atual->next();
            index++;
        }
        insert(data, index);
    }
}

template <typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("índice fora de alcance");
    }
    if (index == 0) {
        return pop_front();
    } else if (index == size_ - 1) {
        return pop_back();
    } else {
        Node* atual = head;
        for (std::size_t i = 0; i < index; ++i) {
            atual = atual->next();
        }
        T data = atual->data();
        Node* anterior = atual->prev();
        Node* proximo = atual->next();
        anterior->next(proximo);
        proximo->prev(anterior);
        delete atual;
        size_--;
        return data;
    }
}

template <typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    Node* tail = head->prev();
    T data = tail->data();
    if (size_ == 1) {
        head = nullptr;
    } else {
        Node* novo_tail = tail->prev();
        novo_tail->next(head);
        head->prev(novo_tail);
    }
    delete tail;
    size_--;
    return data;
}

template <typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    Node* antigo_head = head;
    T data = antigo_head->data();
    if (size_ == 1) {
        head = nullptr;
    } else {
        Node* novo_head = head->next();
        Node* tail = head->prev();
        tail->next(novo_head);
        novo_head->prev(tail);
        head = novo_head;
    }
    delete antigo_head;
    size_--;
    return data;
}

template <typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    std::size_t index = find(data);
    if (index != size_) {
        pop(index);
    }
}

template <typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return size_ == 0;
}

template <typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    return find(data) != size_;
}

template <typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("índice fora de alcance");
    }
    Node* atual = head;
    for (std::size_t i=0; i < index; ++i) {
        atual = atual->next();
    }
    return atual->data();
}

template <typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("índice fora de alcance");
    }
    Node* atual = head;
    for (std::size_t i = 0; i < index; ++i) {
        atual = atual->next();
    }
    return atual->data();
}

template <typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    Node* atual = head;
    for (std::size_t i = 0; i < size_; ++i) {
        if (atual->data() == data) {
            return i;
        }
        atual = atual->next();
    }
    return size_;
}

template <typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}