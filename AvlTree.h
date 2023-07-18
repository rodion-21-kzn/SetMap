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
        Node* parent_ = nullptr;
        int height_ = 0;

        Node(int key, int value);
        Node(int key, int value, Node* parent);
    };

    AVLTree();
//    AVLTree(std::initializer_list<int> const &items);
    AVLTree(const AVLTree &other);
    AVLTree(AVLTree &&other) noexcept;
    ~AVLTree();
    AVLTree& operator=(AVLTree &&other) noexcept;
    AVLTree& operator=(const AVLTree &other);

    void Insert(int key, int value);
    Node* Delete(int key);

    void PrintBinaryTree();
    void PrintTree(Node* root, const std::string& prefix, bool isLeft);

private:
    Node* root_;

    // Support
    Node* GetMin(Node* node);
    Node* GetMax(Node* node);

    void Swap(Node* a, Node* b); // swap only key and value

    void FreeNode(Node* node);

    Node* CopyTree(Node* node);

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
