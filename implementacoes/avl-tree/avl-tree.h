// Copyright [2024] Lucas Pastre de Souza

#include "array-list.h"

namespace structures {

template<typename T>
class AVLTree {
 public:
    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

 private:
    struct Node {
        explicit Node(const T& data_) : data{data_}, height_{0}, left{nullptr}, right{nullptr} {}

        T data;
        int height_;
        Node* left;
        Node* right;

        Node* insert(const T& data_, Node* arv, Node* pai) {
            if (arv == nullptr) {
                return new Node(data_);
            }
            if (data_ < arv->data) {
                arv->left = insert(data_, arv->left, arv);

                if (heightDiff(arv) > 1) {
                    if (data_ < arv->left->data) {
                        arv = simpleLeft(arv);
                    } else {
                        arv = doubleLeft(arv);
                    }
                }
            } else if (data_ > arv->data) {
                arv->right = insert(data_, arv->right, arv);

                if (heightDiff(arv) < -1) {
                    if (data_ > arv->right->data) {
                        arv = simpleRight(arv);
                    } else {
                        arv = doubleRight(arv);
                    }
                }
            }

            arv->updateHeight();
            return arv;
        }

        Node* remove(Node* node, const T& data_) {
            if (node == nullptr) {
                return node;
            }

            if (data_ < node->data) {
                node->left = remove(node->left, data_);
            } else if (data_ > node->data) {
                node->right = remove(node->right, data_);
            } else {  // Encontrou o dado
                if (node->left == nullptr) {  // Caso 1: apenas filho à direita
                    Node* temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {  // Caso 2: apenas filho à esquerda
                    Node* temp = node->left;
                    delete node;
                    return temp;
                } else {  // Caso 3: dois filhos
                    Node* sucessor = node->right->minimo();
                    node->data = sucessor->data;
                    node->right = remove(node->right, sucessor->data);
                }
            }

            node->updateHeight();

            if (heightDiff(node) > 1) {
                if (heightDiff(node->left) >= 0) {
                    node = simpleLeft(node);
                } else {
                    node = doubleLeft(node);
                }
            } else if (heightDiff(node) < -1) {
                if (heightDiff(node->right) <= 0) {
                    node = simpleRight(node);
                } else {
                    node = doubleRight(node);
                }
            }
            return node;
        }

        bool contains(const T& data_) const {
             if (data_ == data) {
                return true;
            } else if (data_ < data) {
                if (left != nullptr) {
                    return left->contains(data_);
                } else {
                    return false;
                }
            } else {  // data_ > data
                if (right != nullptr) {
                    return right->contains(data_);
                } else {
                    return false;
                }
            }
        }

        void updateHeight() {
            int altura_esq = -1;
            int altura_dir = -1;

            if (left != nullptr) {
                altura_esq = left->height_;
            }
            if (right != nullptr) {
                altura_dir = right->height_;
            }

            if (altura_esq > altura_dir) {
                height_ = altura_esq + 1;
            } else {
                height_ = altura_dir + 1;
            }
        }

        int heightDiff(Node* node) const {
            int altura_esq = -1;
            int altura_dir = -1;

            if (node->left != nullptr) {
                altura_esq = node->left->height_;
            }
            if (node->right != nullptr) {
                altura_dir = node->right->height_;
            }

            return altura_esq - altura_dir;
        }


        Node* simpleLeft(Node* px) {
            Node* py = px->left;
            px->left = py->right;
            py->right = px;
            px->updateHeight();
            py->updateHeight();
            return py;
        }

        Node* simpleRight(Node* px) {
            Node* py = px->right;
            px->right = py->left;
            py->left = px;
            px->updateHeight();
            py->updateHeight();
            return py;
        }

        Node* doubleLeft(Node* px) {
            px->left = simpleRight(px->left);
            return simpleLeft(px);
        }

        Node* doubleRight(Node* px) {
            px->right = simpleLeft(px->right);
            return simpleRight(px);
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr) {
                left -> pre_order(v);
            }
            if (right != nullptr) {
                right -> pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left -> in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right -> in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left -> post_order(v);
            }
            if (right != nullptr) {
                right -> post_order(v);
            }
            v.push_back(data);
        }

        Node* minimo() {
            if (left == nullptr) {
                return this;
            } else {
                return left->minimo();  // chamada recursiva para buscar o menor elemento
            }
        }
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    delete root;
}

template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
    if (contains(data)) {
        throw std::out_of_range("Elemento já está na árvore");
    }
    if (root == nullptr) {
        root = new Node(data);
    } else {
        root = root->insert(data, root, nullptr);
    }
    size_++;
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    if (!contains(data)) {
        throw std::out_of_range("Elemento não encontrado na árvore");
    }
    root = root->remove(root, data);
    size_--;
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    if (root != nullptr) {
        return root->contains(data);
    }
    return false;
}

template<typename T>
bool structures::AVLTree<T>::empty() const {
    return (size() == 0);
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template<typename T>
int structures::AVLTree<T>::height() const {
    if (root != nullptr) {
        return root->height_;
    }
    return -1;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    structures::ArrayList<T> lista;
    if (root != nullptr) {
        root->pre_order(lista);
    }
    return lista;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    structures::ArrayList<T> lista;
    if (root != nullptr) {
        root->in_order(lista);
    }
    return lista;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    structures::ArrayList<T> lista;
    if (root != nullptr) {
        root->post_order(lista);
    }
    return lista;
}