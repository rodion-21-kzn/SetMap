//
// Created by Oznak Banshee on 7/28/23.
//


#include "Set.h"
#include <list>


int main () {
    Set<int> test1 = {5,6};
    Set<int> test2 = {1,2,3};
    Set<int>::iterator it;
    it = test1.Find(5);
    std::cout << test2.Contains(4);
}

template<typename Key>
Set<Key>::Set(const std::initializer_list<value_type> &items) {
    for (auto i = items.begin(); i != items.end(); ++i) {
        AVLTree<Key, Key>::Insert(*i);
    }
}

template<typename Key>
Set<Key> &Set<Key>::operator=(Set &&other) noexcept {
    if (this != &other) {
        AVLTree<Key, Key>::operator=(std::move(other));
    }
    return *this;
}

template<typename Key>
Set<Key> &Set<Key>::operator=(const Set &other) {
    if (this != &other) {
        AVLTree<Key, Key>::operator=(other);
    }
    return *this;
}

