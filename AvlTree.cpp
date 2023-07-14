//
// Created by Oznak Banshee on 7/14/23.
//

#include "AvlTree.h"

// Constructor

AVLTree::AVLTree() : root_(nullptr) {}

// Creation

void AVLTree::Insert(int key, int value) {
    root_ = InsertNode(root_, key, value);
}

AVLTree::Node* AVLTree::CreateNode(int value, int key) {
    Node* new_node = new Node();
    new_node->key_ = key;
    new_node->value_ = value;
    new_node->left_ = nullptr;
    new_node->right_ = nullptr;
    new_node->height_ = 0;
}

//

int main() {
    std::cout << 2;
}