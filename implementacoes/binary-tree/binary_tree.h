// "Copyright [year] <Copyright Owner>"
#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
public:
    BinaryTree();

    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
            left = nullptr;
            right = nullptr;
        }

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_) {
            if (data > data_) {  // insere na esquerda
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left->insert(data_);
                }
            } else {  // insere na direita
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right->insert(data_);
                }
            }
        }

        Node* remove(Node* node, const T& data_) {
            //procurando o dado:
            if (node == nullptr) {
                return node;
            }
            if (data_ < node->data) {
                node->left = remove(node->left, data_);
            } else if (data_ > node->data) {
                node->right = remove(node->right, data_);
            } else {   // encontrou o dado, ou seja (data_ = node->data)
                if (node->left == nullptr) {  // CASO 1: filho a direita
                    Node* temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {    // CASO 1: filho a esquerda
                    Node* temp = node->left;
                    delete node;
                    return temp;
                } else {        // CASO 2: dois filhos
                    Node* sucessor = node->right->minimo();
                    node->data = sucessor->data;
                    node->right = remove(node->right, sucessor->data); // recursão para remover o nó do sucessor da subárvore a direita
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

//-------------------------------------

template<typename T>
structures::BinaryTree<T>::BinaryTree() {
    root = nullptr;
    size_ = 0;
}

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    if (root != nullptr) {
        structures::ArrayList<T> list_nodes = pre_order();
        while (!list_nodes.empty()) {
            remove(list_nodes.pop_back());
        }
    }
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    if (contains(data)) {
        throw std::out_of_range("Elemento já está presente.");
    }
    if (root == nullptr) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    Node* p = root;
    p = p->remove(p, data);
    if (p != nullptr) {
        size_--;
    }
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
    if (root != nullptr) {
        return root->contains(data);
    } else {
        return false;
    }
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> L;
	if (root != nullptr) {
		root->pre_order(L);
	}
	return L;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    structures::ArrayList<T> L;
	if (root != nullptr) {
		root->in_order(L);
	}
	return L;
}

template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    structures::ArrayList<T> L;
	if (root != nullptr) {
		root->post_order(L);
	}
	return L;
}