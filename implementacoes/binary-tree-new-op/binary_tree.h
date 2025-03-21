//!  Copyright [2020] <Lucas Pastre de Souza>

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include "./array_list.h"

namespace structures {

//! Classe Árvore binária
template <typename T>
class BinaryTree {
 public:
    //! ...
    BinaryTree();
    //! ...
    ~BinaryTree();
    //! ...
    void insert(const T &data);
    //! ...
    void remove(const T &data);
    //! ...
    bool contains(const T &data) const;
    //! ...
    bool empty() const;
    //! ...
    std::size_t size() const;
    //! ...
    ArrayList<T> pre_order() const;
    //! ...
    ArrayList<T> in_order() const;
    //! ...
    ArrayList<T> post_order() const;

    //**********************
    // Prova prática - implementações necessárias:

    // (1) determinação da altura da árvore:
    int height();

    // (2) contagem do número de folhas:
    int leaves();

    // (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
    //     valor da árvore:
    ArrayList<T> limits();

    // (4) criação de uma duplicação, em memória, da árvore:
    BinaryTree<T> clone();

    // (5) remove nós pelo número de seus filhos:
    void filter(int n_child);

    // (6) criação de um nova árvore que tenha todos os valores e a
    //     menor altura possível, ou seja, balanceada com base apenas
    //     no estabelecimento de uma nova ordem de inserção:
    BinaryTree<T> balance();

    void balance_r(BinaryTree<T> &tree, ArrayList<T>&lista, int inicial, int final);

    //**********************

 private:
    struct Node {
        //! Construtor
        explicit Node(const T &data) : data_{data} {
        }

        //! Destrutor
        ~Node() {
            delete left_;
            delete right_;
        }

        size_t level_{0};
        T data_;
        Node *left_{nullptr};
        Node *right_{nullptr};

        //! Inserção
        void insert(const T &data) {
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            Node *aux = this;
            while (aux != nullptr) {
                if (data < aux->data_) {
                    if (aux->left_ == nullptr) {
                        aux->left_ = new Node(data);
                        aux->left_->level_ = aux->level_ + 1;
                        break;
                    }
                    aux = aux->left_;
                } else {
                    if (aux->right_ == nullptr) {
                        aux->right_ = new Node(data);
                        aux->right_->level_ = aux->level_ + 1;
                        break;
                    }
                    aux = aux->right_;
                }
            }
        }

        //! Remoção
        bool remove(const T &data, Node **root) {
            bool existe = false;
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            if ((*root)->contains(data)) {
                *root = (*root)->remove(data, *root, existe);
            }
            return existe;
        }

        //! Contém
        bool contains(const T &data) const {
            bool existe = false;
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            Node *aux = nullptr;
            if (this->data_ == data) {
                return true;
            } else if (data < this->data_) {
                aux = this->left_;
            } else {
                aux = this->right_;
            }

            while (aux != nullptr) {
                if (data < aux->data_) {
                    aux = aux->left_;
                } else if (data > aux->data_) {
                    aux = aux->right_;
                } else {
                    existe = true;
                    break;
                }
            }

            return existe;
        }

        //! Pré ordem
        void pre_order(ArrayList<T> &v) const {
            v.push_back(data_);
            if (left_ != nullptr)
                left_->pre_order(v);
            if (right_ != nullptr)
                right_->pre_order(v);
        }

        //! Em ordem
        void in_order(ArrayList<T> &v) const {
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            if (left_ != nullptr)
                left_->in_order(v);
            v.push_back(data_);
            if (right_ != nullptr)
                right_->in_order(v);
        }

        //! Pós ordem
        void post_order(ArrayList<T> &v) const {
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            if (left_ != nullptr)
                left_->post_order(v);
            if (right_ != nullptr)
                right_->post_order(v);
            v.push_back(data_);
        }

      private:
        //! Complemento da funcão de remoção
        Node *remove(const T &data, Node *arv, bool &deleted) {
            Node *temp = nullptr;
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            if (arv == nullptr) {
                deleted = false;
                return nullptr;
            }

            if (data < arv->data_) {
                deleted = false;
                arv->left_ = remove(data, arv->left_, deleted);
                return arv;
            }

            if (data > arv->data_) {
                deleted = false;
                arv->right_ = remove(data, arv->right_, deleted);
                return arv;
            }

            if (arv->left_ != nullptr && arv->right_ != nullptr) {
                Node *min = arv->right_->minimum();
                arv->data_ = min->data_;
                deleted = true;
                arv->right_ = remove(min->data_, arv->right_, deleted);
                return arv;
            }

            if (arv->left_ != nullptr) {
                temp = arv->left_;
                arv->left_ = nullptr;
                delete arv;
                deleted = true;
                return temp;
            }

            if (arv->right_ != nullptr) {
                temp = arv->right_;
                arv->right_ = nullptr;
                delete arv;
                deleted = true;
                return temp;
            }

            delete arv;
            deleted = true;

            return nullptr;
        }

        //! Encontrar o menor
        Node *minimum() {
            if (left_ == nullptr)
                return this;
            return left_->minimum();
        }
    };

    Node *root_{nullptr};
    std::size_t size_{0};
};

//**********************
// Prova prática - implementações necessárias:

template <typename T>
int BinaryTree<T>::height() {
    // recursão
    std::function<int(Node*)> altura = [&](Node* node) -> int {
        if (node == nullptr) {
            return -1;  // altura de árvore vazia é -1
        }
        int altura_esq = altura(node->left_);
        int altura_dir = altura(node->right_);
        if (altura_esq > altura_dir) {
            return altura_esq + 1;
        } else {
            return altura_dir + 1;
        }
    };
    return altura(root_);
}

//! (2) Contagem do número de folhas:
template <typename T>
int BinaryTree<T>::leaves() {
    std::function<int(Node*)> folha = [&](Node* node) -> int {
        if (node == nullptr) {
            return 0;
        }
        if (node->left_ == nullptr && node->right_ == nullptr) {
            return 1;
        }
        return folha(node->left_) + folha(node->right_);
    };
    return folha(root_);
}

//! (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
//!     valor da árvore:
template <typename T> ArrayList<T> BinaryTree<T>::limits() {
    ArrayList<T> L(2);
    if (empty()) {
        return L;
    }
    Node* min = root_;
    Node* max = root_;
    while (min->left_ != nullptr) {
        min = min->left_;
    }
    while (max->right_ != nullptr) {
        max = max->right_;
    }
    L.push_back(min->data_);
    L.push_back(max->data_);
    return L;
}

//! (4) criação de uma duplicação, em memória, da árvore:
template <typename T>
BinaryTree<T> BinaryTree<T>::clone() {
    BinaryTree<T> C;
    std::function<void(Node*)> copy_node = [&](Node* node) {
        if (node != nullptr) {
            C.insert(node->data_);
            copy_node(node->left_);
            copy_node(node->right_);
        }
    };
    copy_node(root_);
    return C;
}

//! (5) remove nós pelo número de seus filhos:
template <typename T>
void BinaryTree<T>::filter(int n_child) {
    std::function<Node*(Node*)> filtro = [&](Node* node) -> Node* {
        if (node == nullptr) {
            return nullptr;
        }

        // Calcula o número de filhos
        int cont = 0;
        if (node->left_ != nullptr) {
            cont++;
        }
        if (node->right_ != nullptr) {
            cont++;
        }

        // Filtra os nós recursivamente
        node->left_ = filtro(node->left_);
        node->right_ = filtro(node->right_);

        // Remove nó, se necessário
        if (cont == n_child) {
            Node* temp = (node->left_ != nullptr) ? node->left_ : node->right_;
            delete node;
            return temp;
        }
        return node;
    };

    root_ = filtro(root_);
}


//! (6) criação de um nova árvore que tenha todos os valores e a
//!     menor altura possível, ou seja, balanceada com base apenas
//!     no estabelecimento de uma nova ordem de inserção:
template <typename T> BinaryTree<T> BinaryTree<T>::balance() {
    BinaryTree<T> B;
    if (empty()) {
        return B;
    }
    ArrayList<T> Lista = in_order();  // Obtém os elementos em ordem crescente
    int tamanho_lista = Lista.size();
    balance_r(B, Lista, 0, tamanho_lista-1);
    return B;
}

template <typename T> void BinaryTree<T>::balance_r(BinaryTree<T> &tree, ArrayList<T> &lista, int inicial, int final) {
            if (inicial > final) {
                return;
            } else {
            int indice_central = (inicial+final)/2;
            tree.insert(lista[indice_central]);
            balance_r(tree, lista, inicial, indice_central-1);
            balance_r(tree, lista, indice_central+1, final);
            }
}

//***********************************************************

//! Construtor
template <typename T> BinaryTree<T>::BinaryTree() {
}

//! Destrutor
template <typename T> BinaryTree<T>::~BinaryTree() {
    delete root_;
}

//! Inserção
template <typename T> void BinaryTree<T>::insert(const T &data) {
    if (empty()) {
        root_ = new Node(data);
        if (root_ == nullptr)
            throw std::out_of_range("FUll tree!");
    } else {
        root_->insert(data);
    }
    ++size_;
}

// Remoção
template <typename T> void BinaryTree<T>::remove(const T &data) {
    if (empty())
        throw std::out_of_range("Empty tree");

    if (size() != 1u) {
        if (root_->remove(data, &root_))
            --size_;
    } else {
        if (root_->data_ == data) {
            delete root_;
            root_ = nullptr;
            --size_;
        }
    }
}

//! Contém
template <typename T> bool BinaryTree<T>::contains(const T &data) const {
    if (empty())
        return false;
    return root_->contains(data);
}

//! Vazio
template <typename T> bool BinaryTree<T>::empty() const {
    return size() == 0;
}

//! Tamanho
template <typename T> std::size_t BinaryTree<T>::size() const {
    return size_;
}

//! Pré ordem
template <typename T> ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->pre_order(v);
    return v;
}

//! Em ordem
template <typename T> ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->in_order(v);
    return v;
}

//! Pós ordem
template <typename T> ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(v);
    return v;
}

}  // namespace structures

#endif
