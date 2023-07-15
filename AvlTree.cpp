//
// Created by Oznak Banshee on 7/14/23.
//

#include "AvlTree.h"

int main() {
    AVLTree new_tree;
    int key = 1, value = 1;
    for (int i = 0; i < 17; i++)
        new_tree.Insert(key++,value++);
    std::cout << 1;
}

// Contructors

AVLTree::AVLTree() : root_(nullptr) {}

AVLTree::Node::Node(int key, int value) : key_(key), value_(value) {}

// Support

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
    Swap(node, node->left_);
    Node* tmp = node->right_;
    node->right_ = node->left_;
    node->left_ = node->right_->left_;
    node->right_->left_ = node->right_->right_;
    node->right_->right_ = tmp;
    SetHeight(node->right_);
    SetHeight(node->left_);
}

void AVLTree::LeftRotate(AVLTree::Node *node) {
    Swap(node, node->right_);
    Node* tmp = node->left_;
    node->left_ = node->right_;
    node->right_ = node->left_->right_;
//    node->right_->left_ = node->right_->right_; // похоже лишнее
    node->left_->right_ =  node->left_->left_;
    node->left_->left_ = tmp;
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

void AVLTree::Insert(int key, int value) {
    if (root_ == nullptr) {
        root_ = new Node(key, value);
        tree_size_ = 1;
    } else {
        RecursiveInsert(root_, key, value);
    }
}

void AVLTree::RecursiveInsert(AVLTree::Node *node, int key, int value) {
    if (key < node->key_) {
        if (node->left_ == nullptr) {
            node->left_ = new Node(key,value);
        } else {
            RecursiveInsert(node->left_, key, value);
        }
    } else if (key > node->key_) {
        if (node->right_ == nullptr) {
            node->right_ = new Node(key,value);
        } else {
            RecursiveInsert(node->right_, key, value);
        }
    }
    SetHeight(node);
    Balance(node);
}



