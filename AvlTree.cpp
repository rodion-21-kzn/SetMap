//
// Created by Oznak Banshee on 7/14/23.
//

#include "AvlTree.h"

int main() {
    std::cout << 2;
}

Node::Node(int key, int value) {
    key_ = key;
    value_ = value;
}

int Node::GetHeight(Node* node) {
    return node == nullptr ? -1:node->height_;
}

void Node::UpdateHeight(Node *node) {
    node->height_ = std::max(GetHeight(node->left_), GetHeight(node->right_)) + 1;
}

int Node::GetBalance(Node *node) {
    return node == nullptr ? 0 : GetHeight(node->right_) - GetHeight(node->right_);
}

void Node::Swap(Node *a, Node *b) {
    std::swap(a->key_, b->key_);
    std::swap(a->value_, b->value_);
}

void Node::RightRotate(Node *node) {
    Swap(node, node->left_);
    Node temp = node->right_; // copy constructor or move;


}
