//
// Created by Oznak Banshee on 7/14/23.
//

#include "AvlTree.h"

int main() {
    AVLTree new_tree;

//    new_tree.Insert(2,2);
//    new_tree.Insert(3,3);
//    new_tree.Insert(4,4);
    new_tree.Insert(20,20);
    new_tree.Insert(29,29);
    new_tree.Insert(72,72);
    new_tree.Insert(11,11);
    new_tree.Insert(50,50);
    new_tree.Insert(65,65);
    new_tree.Insert(41,41);
    new_tree.Insert(33,33);

    new_tree.Insert(32,32);

    new_tree.Insert(99,99);
    new_tree.Insert(91,91);


    new_tree.PrintBinaryTree();
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
    Node * new_left = node->left_->left_;
    Node * new_right_right = node->right_;
    Node * new_right_left = node->left_->right_;
    Swap(node, node->left_);
    node->right_ = node->left_;
    node->left_ = new_left;
    node->right_->left_ = new_right_left;
    node->right_->right_ = new_right_right;
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
    node->left_->right_ = new_left_right;
    node->left_->left_ = new_left_left;
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