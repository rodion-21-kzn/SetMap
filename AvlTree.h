//
// Created by Oznak Banshee on 7/14/23.
//

#ifndef CONTAINERS_AVLTREE_H
#define CONTAINERS_AVLTREE_H

#include <iostream>


template<typename Key, typename Value>
class AVLTree {
public:
    class Iterator;
    struct Node;

    using key_type = Key;
    using value_type = Value;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = Iterator;
    using const_iterator = const Iterator;

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

    class Iterator {

    public:
        Iterator();
        Iterator(Node* node, Node* past_node = nullptr);
        Iterator operator++();
        Iterator operator--();
        int operator*();
        bool operator==(const Iterator& it);
        bool operator!=(const Iterator& it);
    private:
        Node* iter_node_; // посмотреть куда пихнуть. протектед или приват
        Node* iter_past_node_;
        Node* MoveForward(Node* node);
        Node* MoveBack(Node* node);
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

    bool empty();
    size_t size();
//    size_t max_size;

    void clear();
    void Insert(int key, int value);

//    void erase(iterator pos);
//    void swap(AVLTree& other);
//    void merge(AVLTree& other);

//    iterator find(const Key& key);
//    bool contains(const Key& key);







    Node* Delete(int key);
    void PrintBinaryTree();


private:
    Node* root_;

    // Support
    static Node* GetMin(Node* node);
    static Node* GetMax(Node* node);
    void Swap(Node* a, Node* b); // swap only key and value
    void FreeNode(Node* node);

    Node* CopyTree(Node* node);

    // Print
    void PrintTree(Node* root, const std::string& prefix, bool isLeft);

    // Rotation
    void RightRotate(Node* node);
    void LeftRotate(Node* node);
    void Balance(Node* node);
    int GetBalance(Node* node);
    int GetHeight(Node* node);
    void SetHeight(Node* node);

    // Insert && Delete && Size
    void RecursiveInsert(Node* node, int key, int value);
    Node* RecursiveDelete(Node* node, int key);
    size_t RecursiveSize(Node* node);
};

#endif //CONTAINERS_AVLTREE_H
