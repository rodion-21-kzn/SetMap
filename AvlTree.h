//
// Created by Oznak Banshee on 7/14/23.
//

#ifndef CONTAINERS_AVLTREE_H
#define CONTAINERS_AVLTREE_H

#include <iostream>

class AVLTree {

public:
    struct Node{
        int key_;
        int value_;
        Node* left_;
        Node* right_;
        int height_;
    };

    AVLTree();
    void Insert(int key, int value);

private:
    Node* root_;
    Node* CreateNode(int value, int key);

};

#endif //CONTAINERS_AVLTREE_H
