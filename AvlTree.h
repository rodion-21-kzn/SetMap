//
// Created by Oznak Banshee on 7/14/23.
//

#ifndef CONTAINERS_AVLTREE_H
#define CONTAINERS_AVLTREE_H

#include <iostream>

class Node {

public:
    Node(int key, int value);
    int GetHeight(Node* node);
    int GetBalance(Node* node);


private:
    int key_;
    int value_;
    Node* left_;
    Node* right_;
    int height_;

    void UpdateHeight(Node* node);
    void Swap(Node* a, Node* b);
    void RightRotate(Node *node);

};

#endif //CONTAINERS_AVLTREE_H
