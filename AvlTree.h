//
// Created by Oznak Banshee on 7/14/23.
//

#ifndef CONTAINERS_AVLTREE_H
#define CONTAINERS_AVLTREE_H

#include <iostream>

class AVLTree {

public:
    struct Node {
        int key_;
        int value_;
        Node* left_ = nullptr;
        Node* right_ = nullptr;
        int height_ = 0;

        Node(int key, int value);
    };

    AVLTree();
    void Insert(int key, int value);

private:
    Node* root_;
    size_t tree_size_;

    // Support
    int GetHeight(Node* node);
    void SetHeight(Node* node);
    int GetBalance(Node* node);
    void Swap(Node* a, Node* b);

    // Rotation
    void RightRotate(Node* node);
    void LeftRotate(Node* node);
    void Balance(Node* node);

    //
    void RecursiveInsert(Node* node, int key, int value);
};

#endif //CONTAINERS_AVLTREE_H
