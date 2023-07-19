//
// Created by Oznak Banshee on 7/14/23.
//

#include "AvlTree.h"
#include <set>

int main() {

    AVLTree new_tree;
    new_tree.Insert(1,1);
    new_tree.Insert(2,2);
    new_tree.Insert(-5,-5);
    AVLTree::Iterator it;
    it = new_tree.end();

    std::cout << *it;
    --it;
    std::cout << *it;
    --it;
    std::cout << *it;
    --it;
    std::cout << *it;
    --it;
    std::cout << *it;



//    new_tree.PrintBinaryTree();
}

// Contructors

AVLTree::AVLTree() : root_(nullptr) {}

AVLTree::AVLTree(const AVLTree &other) {
    root_ = CopyTree(other.root_);
}

AVLTree::Node *AVLTree::CopyTree(AVLTree::Node *node) {
    if (node == nullptr) return nullptr;
    Node *new_node = new Node(node->key_, node->value_);
    new_node->left_ = CopyTree(node->left_);
    new_node->right_ = CopyTree(node->right_);
    return new_node;
}

AVLTree::AVLTree(AVLTree &&other) noexcept {
    root_ = other.root_;
    other.root_ = nullptr;
}

AVLTree::~AVLTree() {
    clear();
}

void AVLTree::FreeNode(Node* node) {
    if (node == nullptr) return;

    FreeNode(node->left_);
    FreeNode(node->right_);

    delete node;

}

AVLTree &AVLTree::operator=(AVLTree &&other) noexcept {
    if (this != &other) {
        root_ = other.root_;
        other.root_ = nullptr;
    }
    return *this;
}

AVLTree &AVLTree::operator=(const AVLTree &other) {
    if (this != &other) {
        AVLTree temp(other);
        FreeNode(root_);
        *this = std::move(temp);
    }
    return *this;
}

AVLTree::Node::Node(int key, int value) : key_(key), value_(value) {}

AVLTree::Node::Node(int key, int value, Node* node) : key_(key), value_(value), parent_(node) {}
// Support For Balancing

int AVLTree::GetHeight(AVLTree::Node *node) {
    return node == nullptr ? -1 : node->height_;
}

int AVLTree::GetBalance(AVLTree::Node *node) {
    return node == nullptr ? 0 : GetHeight(node->right_)  - GetHeight(node->left_);
}

void AVLTree::SetHeight(AVLTree::Node *node) {
    node->height_ = std::max(GetHeight(node->left_), GetHeight(node->right_)) + 1;
}

void AVLTree::Swap(AVLTree::Node *a, AVLTree::Node *b) {
    std::swap(a->key_, b->key_);
    std::swap(a->value_, b->value_);
}

void AVLTree::RightRotate(AVLTree::Node *node) {
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

void AVLTree::LeftRotate(AVLTree::Node *node) {
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

void AVLTree::Balance(Node *node) {
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

void AVLTree::Insert(int key, int value) {
    if (root_ == nullptr) {
        root_ = new Node(key, value);
    } else {
        RecursiveInsert(root_, key, value);
    }
}

void AVLTree::RecursiveInsert(AVLTree::Node *node, int key, int value) {
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

AVLTree::Node* AVLTree::Delete(int key) {
    if (root_ == nullptr) return root_;
    return RecursiveDelete(root_, key);
}

AVLTree::Node* AVLTree::RecursiveDelete(AVLTree::Node *node, int key) {
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

void AVLTree::PrintBinaryTree() {
    PrintTree(root_, "", false);
}

void AVLTree::PrintTree(Node* node, const std::string& prefix, bool isLeft) {
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

AVLTree::Node *AVLTree::GetMin(AVLTree::Node *node) {
    if (node == nullptr) return nullptr;
    if (node->left_ == nullptr) return node;
    return GetMin(node->left_);
}

AVLTree::Node *AVLTree::GetMax(AVLTree::Node *node) {
    if (node == nullptr) return nullptr;
    if (node->right_ == nullptr) return node;
    return GetMax(node->right_);
}




////////////////////////////////////////////


void AVLTree::clear() {
    if (root_ != nullptr) FreeNode(root_);
    root_ = nullptr;
}

void AVLTree::swap(AVLTree &other) {

}

void AVLTree::merge(AVLTree &other) {

}

AVLTree::Iterator AVLTree::begin() {
    return AVLTree::Iterator(GetMin(root_));
}

AVLTree::Iterator AVLTree::end() {
    Node* last_node = GetMax(root_);

    Iterator test(nullptr, last_node);
    return test;
}

AVLTree::Node *AVLTree::MoveForward(Node* node) {
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

AVLTree::Node *AVLTree::MoveBack(AVLTree::Node *node) {
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
AVLTree::Iterator::Iterator() : iter_node_(nullptr), iter_past_node_(nullptr) {}

AVLTree::Iterator::Iterator(AVLTree::Node *node, AVLTree::Node *past_node) : iter_node_(node), iter_past_node_(past_node) {}

AVLTree::Iterator AVLTree::Iterator::operator++() {
    iter_node_ = MoveForward(iter_node_);
    return *this;
}

AVLTree::Iterator AVLTree::Iterator::operator--() {
    if (iter_node_ == nullptr && iter_past_node_ != nullptr) {
        *this = iter_past_node_;
        return *this;
    }
    iter_node_ = MoveBack(iter_node_);
    return *this;
}

int AVLTree::Iterator::operator*() {
    if (iter_node_ == nullptr) {
        return 0;
    }
    return iter_node_->value_;
}
