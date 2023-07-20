//
// Created by Oznak Banshee on 7/14/23.
//

#include "AvlTree.h"
#include <set>

int main() {

    AVLTree<char, char> new_tree;
    new_tree.Insert('a','a');
    new_tree.Insert('b','b');
    new_tree.Insert('c','c');

    AVLTree<char,char>::Iterator it;

    new_tree.size();

    it = new_tree.begin();
    std::cout << *it;
//
    std::cout << new_tree.size() << std::endl;
    new_tree.PrintBinaryTree();
}

// Contructors

template<typename Key, typename Value>
AVLTree<Key, Value>::AVLTree() : root_(nullptr) {}

template<typename Key, typename Value>
AVLTree<Key, Value>::AVLTree(const AVLTree &other) {
    root_ = CopyTree(other.root_);
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::CopyTree(AVLTree::Node *node) {
    if (node == nullptr) return nullptr;
    Node *new_node = new Node(node->key_, node->value_);
    new_node->left_ = CopyTree(node->left_);
    new_node->right_ = CopyTree(node->right_);
    return new_node;
}

template<typename Key, typename Value>
AVLTree<Key, Value>::AVLTree(AVLTree &&other) noexcept {
    root_ = other.root_;
    other.root_ = nullptr;
}

template<typename Key, typename Value>
AVLTree<Key, Value>::~AVLTree() {
    clear();
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::FreeNode(Node* node) {
    if (node == nullptr) return;

    FreeNode(node->left_);
    FreeNode(node->right_);

    delete node;

}

template<typename Key, typename Value>
AVLTree<Key, Value> &AVLTree<Key, Value>::operator=(AVLTree &&other) noexcept {
    if (this != &other) {
        root_ = other.root_;
        other.root_ = nullptr;
    }
    return *this;
}

template<typename Key, typename Value>
AVLTree<Key, Value> &AVLTree<Key, Value>::operator=(const AVLTree &other) {
    if (this != &other) {
        AVLTree temp(other);
        FreeNode(root_);
        *this = std::move(temp);
    }
    return *this;
}

template<typename Key, typename Value>
AVLTree<Key, Value>::Node::Node(Key key, Value value)  : key_(key), value_(value) {}

template<typename Key, typename Value>
AVLTree<Key, Value>::Node::Node(Key key, Value value, Node* node)   : key_(key), value_(value), parent_(node) {}
// Support For Balancing

template<typename Key, typename Value>
int AVLTree<Key, Value>::GetHeight(AVLTree::Node *node) {
    return node == nullptr ? -1 : node->height_;
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::GetBalance(AVLTree::Node *node) {
    return node == nullptr ? 0 : GetHeight(node->right_)  - GetHeight(node->left_);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::SetHeight(AVLTree::Node *node) {
    node->height_ = std::max(GetHeight(node->left_), GetHeight(node->right_)) + 1;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::Swap(AVLTree::Node *a, AVLTree::Node *b) {
    std::swap(a->key_, b->key_);
    std::swap(a->value_, b->value_);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::RightRotate(AVLTree::Node *node) {
    Node * new_left = node->left_->left_;
    Node * new_right_right = node->right_;
    Node * new_right_left = node->left_->right_;

    Swap(node, node->left_);
    node->right_ = node->left_;

    node->left_ = new_left;
    if (node->left_) {
        node->left_->parent_ = node;
    }

    node->right_->left_ = new_right_left;
    if (node->right_->left_) {
        node->right_->left_->parent_ = node->right_;
    }

    node->right_->right_ = new_right_right;
    if (node->right_->right_) {
        node->right_->right_->parent_ = node->right_;
    }

    SetHeight(node->right_);
    SetHeight(node);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::LeftRotate(AVLTree::Node *node) {
    Node * new_right = node->right_->right_;
    Node * new_left_left = node->left_;
    Node * new_left_right = node->right_->left_;

    Swap(node, node->right_);
    node->left_ = node->right_;

    node->right_ = new_right;
    if (node->right_) {
        node->right_->parent_ = node;
    }

    node->left_->right_ = new_left_right;
    if (node->left_->right_)  {
        node->left_->right_->parent_ = node->left_;
    }

    node->left_->left_ = new_left_left;
    if (node->left_->left_)  {
        node->left_->left_->parent_  = node->left_;
    }

    SetHeight(node->left_);
    SetHeight(node);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::Balance(Node *node) {
    int balance = GetBalance(node);
    if (balance == -2) {
        if(GetBalance(node->left_) == 1) LeftRotate(node->left_);
        RightRotate(node);
    } else if (balance == 2) {
        if(GetBalance(node->right_) == -1) RightRotate(node->right_);
        LeftRotate(node);
    }
}

// Insert and Delete

template<typename Key, typename Value>
void AVLTree<Key, Value>::Insert(Key key, Value value) {
    if (root_ == nullptr) {
        root_ = new Node(key, value);
    } else {
        RecursiveInsert(root_, key, value);
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::RecursiveInsert(AVLTree::Node *node, Key key, Value value) {
    if (key < node->key_) {
        if (node->left_ == nullptr) {
            node->left_ = new Node(key, value, node);
        } else {
            RecursiveInsert(node->left_, key, value);
        }
    } else if (key > node->key_) {
        if (node->right_ == nullptr) {
            node->right_ = new Node(key, value, node);
        } else {
            RecursiveInsert(node->right_, key, value);
        }
    }
    SetHeight(node);
    Balance(node);
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::Delete(Key key) {
    if (root_ == nullptr) return root_;
    return RecursiveDelete(root_, key);
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::RecursiveDelete(AVLTree::Node *node, Key key) {
    if (node == nullptr) return nullptr;
    if (key < node->key_) {
        node->left_ = RecursiveDelete(node->left_, key);
    } else if (key > node->key_) {
        node->right_ = RecursiveDelete(node->right_, key);
    } else {
        if (node->left_ == nullptr || node->right_ == nullptr) {
            Node* node_right = node->right_;
            Node* node_left = node->left_;
            Node* node_parent = node->parent_;
            delete node;
            if (node_left == nullptr) {
                node = node_right;
            } else {
                node = node_left;
            }
            if (node != nullptr) node->parent_ = node_parent;
        } else {
            Node* min_in_right = GetMin(node->right_);
            node->key_ = min_in_right->key_;
            node->value_ = min_in_right->value_;
            node->right_ = RecursiveDelete(node->right_, min_in_right->key_);
        }
    }
    if (node != nullptr) {
        SetHeight(node);
        Balance(node);
    }
    return node;
}


// Printing

template<typename Key, typename Value>
void AVLTree<Key, Value>::PrintBinaryTree() {
    PrintTree(root_, "", false);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::PrintTree(Node* node, const std::string& prefix, bool isLeft) {
    if (node == nullptr) {
        return;
    }

    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──");
    std::cout << node->key_ << std::endl;

    // Calculate the new prefix for child nodes
    std::string childPrefix = prefix + (isLeft ? "│   " : "    ");

    PrintTree(node->left_, childPrefix, true);
    PrintTree(node->right_, childPrefix, false);
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::GetMin(AVLTree::Node *node) {
    if (node == nullptr) return nullptr;
    if (node->left_ == nullptr) return node;
    return GetMin(node->left_);
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::GetMax(AVLTree::Node *node) {
    if (node == nullptr) return nullptr;
    if (node->right_ == nullptr) return node;
    return GetMax(node->right_);
}




////////////////////////////////////////////

template<typename Key, typename Value>
void AVLTree<Key, Value>::clear() {
    if (root_ != nullptr) FreeNode(root_);
    root_ = nullptr;
}

//void AVLTree::swap(AVLTree &other) {
//
//}
//
//void AVLTree::merge(AVLTree &other) {
//
//}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::begin() {
    return AVLTree::Iterator(GetMin(root_));
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::end() {
    Node* last_node = GetMax(root_);

    Iterator test(nullptr, last_node);
    return test;
}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::empty() {
    return root_ == nullptr;
}

template<typename Key, typename Value>
size_t AVLTree<Key, Value>::size() {
    return RecursiveSize(root_);
}

template<typename Key, typename Value>
size_t AVLTree<Key, Value>::RecursiveSize(AVLTree::Node *node) {
    if (node == nullptr) return 0;
    size_t left_size = RecursiveSize(node->left_);
    size_t right_size = RecursiveSize(node->right_);
    return 1 + left_size + right_size;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::Iterator::MoveForward(AVLTree::Node *node)  {
    if (node->right_ != nullptr) {
        return GetMin(node->right_);
    }
    Node* parent = node->parent_;
    while (parent != nullptr && node == parent->right_) {
        node = parent;
        parent = parent->parent_;
    }
    return parent;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::Iterator::MoveBack(AVLTree::Node *node)  {
    if (node->left_ != nullptr) {
        return GetMax(node->left_);
    }
    Node* parent = node->parent_;
    while (parent != nullptr && node == parent->left_) {
        node = parent;
        parent = node->parent_;
    }
    return parent;
}


template<typename Key, typename Value>
AVLTree<Key, Value>::Iterator::Iterator() : iter_node_(nullptr), iter_past_node_(nullptr) {}

template<typename Key, typename Value>
AVLTree<Key, Value>::Iterator::Iterator(AVLTree::Node *node, AVLTree::Node *past_node) : iter_node_(node), iter_past_node_(past_node) {}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::Iterator::operator++() {
    iter_node_ = MoveForward(iter_node_);
    return *this;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::Iterator::operator--() {
    if (iter_node_ == nullptr && iter_past_node_ != nullptr) {
        *this = iter_past_node_;
        return *this;
    }
    iter_node_ = MoveBack(iter_node_);
    return *this;
}

template<typename Key, typename Value>
Value AVLTree<Key, Value>::Iterator::operator*() {
    if (iter_node_ == nullptr) {
        return 0;
    }
    return iter_node_->value_;
}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::Iterator::operator==(const AVLTree::Iterator &it) {
    return iter_node_ == it.iter_node_;
}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::Iterator::operator!=(const AVLTree::Iterator &it) {
    return iter_node_ != it.iter_node_;
}


// OLD WORKING REALIZATION
//void AVLTree::RightRotate(AVLTree::Node *node) {
//    Swap(node, node->left_);
//    Node* tmp = node->right_;
//    node->right_ = node->left_;
//    node->left_ = node->right_->left_;
//    node->right_->left_ = node->right_->right_;
//    node->right_->right_ = tmp;
//    SetHeight(node->right_);
//    SetHeight(node);
//}
//
//void AVLTree::LeftRotate(AVLTree::Node *node) {
//    Swap(node, node->right_);
//    Node* tmp = node->left_;
//    node->left_ = node->right_;
//    node->right_ = node->left_->right_;
//    node->left_->right_ =  node->left_->left_;
//    node->left_->left_ = tmp;
//    SetHeight(node->left_);
//    SetHeight(node);
//}