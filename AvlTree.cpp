//
// Created by Oznak Banshee on 7/14/23.
//

#include "AvlTree.h"
#include <set>

int main() {
    AVLTree new_tree;
    std::set<int> test_set{1,2,3};
    test_set.insert(7);
    std::set<int>::iterator it;
    it = test_set.begin();
    it++;
    test_set.insert(it, 0);

    for (it = test_set.begin(); it != test_set.end(); ++it) {
        std::cout << *it;
    }



//    new_tree.Insert(2,2);
//    new_tree.Insert(3,3);
//    new_tree.Insert(4,4);
//    new_tree.Insert(0,0);
//    new_tree.Insert(1,1);
//    new_tree.Insert(2,2);
//    new_tree.Insert(3,3);
//    new_tree.Insert(4,4);
//
//
//    new_tree.Delete(1);
//    new_tree.Delete(2);
//
//
//    new_tree.PrintBinaryTree();
}

// Contructors

AVLTree::AVLTree() : root_(nullptr), tree_size_(0) {}

AVLTree::Node::Node(int key, int value) : key_(key), value_(value) {}

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

// Insert and Delete

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
            node = (node->left_ == nullptr) ? node->right_ : node->left_;
        } else {
            Node* min_in_right = GetMin(node->right_);
            node->key_ = min_in_right->key_;
            node->value_ = min_in_right->value_;
            node->right_ = RecursiveDelete(node->right_, min_in_right->key_); // сомнительная строчка
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