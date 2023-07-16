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
//    AVLTree(std::initializer_list<int> const &items);
//    AVLTree(const AVLTree &tree);
//    AVLTree(AVLTree &&tree);
//
//    AVLTree& operator=(AVLTree &&tree);

    ~AVLTree();

    void Insert(int key, int value);
    Node* Delete(int key);

    void PrintBinaryTree();
    void PrintTree(Node* root, const std::string& prefix, bool isLeft);

private:
    Node* root_;
    size_t tree_size_;

    // Support
    Node* GetMin(Node* node);
    Node* GetMax(Node* node);

    void Swap(Node* a, Node* b); // swap only key and value

    void FreeNode(Node* node);

    // Rotation
    void RightRotate(Node* node);
    void LeftRotate(Node* node);
    void Balance(Node* node);
    int GetBalance(Node* node);
    int GetHeight(Node* node);
    void SetHeight(Node* node);

    // Insert && Delete
    void RecursiveInsert(Node* node, int key, int value);
    Node* RecursiveDelete(Node* node, int key);
};

#endif //CONTAINERS_AVLTREE_H
