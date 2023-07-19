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

    struct Iterator {
        Node* iter_node_; // посмотреть куда пихнуть. протектед или приват
        Node* iter_past_node_;
        Iterator();
        Iterator(Node* node, Node* past_node = nullptr);

//        Iterator()
    };

    AVLTree();
//    AVLTree(std::initializer_list<int> const &items);
    AVLTree(const AVLTree &other);
    AVLTree(AVLTree &&other) noexcept;
    ~AVLTree();
    AVLTree& operator=(AVLTree &&other) noexcept;
    AVLTree& operator=(const AVLTree &other);

     Iterator begin();
     Iterator end();

//    bool empty();
//    size_t size();
//    size_t max_size;

    void clear();
//    void PrintTree(Node* root, const std::string& prefix, bool isLeft);
//    void erase(iterator pos);
    void swap(AVLTree& other);
    void merge(AVLTree& other);

//    iterator find(const Key& key);
//    bool contains(const Key& key);






    void Insert(int key, int value);
    Node* Delete(int key);
    void PrintBinaryTree();


private:
    Node* root_;

    // Support
    Node* GetMin(Node* node);
    Node* GetMax(Node* node);

    void Swap(Node* a, Node* b); // swap only key and value

    void FreeNode(Node* node);

    Node* CopyTree(Node* node);

    void PrintTree(Node* root, const std::string& prefix, bool isLeft);

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
