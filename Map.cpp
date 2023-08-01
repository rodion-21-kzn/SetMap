//
// Created by Oznak Banshee on 7/31/23.
//

#include "Map.h"
#include "Set.h"
#include <map>

int main() {
    Map<int, int> m;
    m.Insert(1,1);
    m.Insert(2,2);
    m.Insert(3,3);
    m.Insert_or_assign(1,2);
    m.at(1) = 11;
    m.PrintBinaryTree();
}


template<typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(Map &&other) noexcept {
    if (this != &other) {
        AVLTree<Key, T>::operator=(std::move(other));
    }
    return *this;
}

template<typename Key, typename T>
Map<Key, T> &Map<Key, T>::operator=(const Map &other) {
    if (this != &other) {
        AVLTree<Key, T>::operator=(other);
    }
    return *this;
}

template<typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert(const value_type &value) {
    return Insert(value.first, value.second);
}


template<typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert(const Key &key, const T& obj) {
    std::pair<iterator, bool> return_value;
    if (AVLTree<Key, T>::root_ == nullptr) {
        AVLTree<Key, T>::root_ = new typename AVLTree<Key, T>::Node(key, obj);
        return_value.first = iterator(AVLTree<Key, T>::root_);
        return_value.second = true;
    } else {
        bool check_insert = AVLTree<Key, T>::RecursiveInsert(AVLTree<Key, T>::root_, key, obj);
        return_value.first = Find(key); // НАДО НАПИСАТЬ ФУНКЦИЮ FIND
        return_value.second = check_insert;
    }
    return return_value;
}

template<typename Key, typename T>
typename Map<Key, T>::value_type &Map<Key, T>::MapIterator::operator*() {
    if (AVLTree<Key,T>::Iterator::iter_node_ == nullptr) {
        static value_type fake_value{};
        return fake_value;
    }
    static std::pair<const key_type, mapped_type> pr = std::make_pair(AVLTree<Key,T>::Iterator::iter_node_->key_, AVLTree<Key,T>::Iterator::iter_node_->value_);
    return pr;
}

template<typename Key, typename T>
T &Map<Key, T>::MapIterator::return_value() {
    if (AVLTree<Key,T>::Iterator::iter_node_ == nullptr) {
        static T fake_value{};
        return fake_value;
    }
    return AVLTree<Key,T>::Iterator::iter_node_->value_;
}



template<typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::Find(const Key &key) {
    typename AVLTree<Key, T>::Node* node = AVLTree<Key, T>::RecursiveFind(AVLTree<Key, T>::root_, key);
    return iterator(node);
}

template<typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert_or_assign(const Key &key, const T &obj) {
    auto it = Find(key);
    if (it != this->End()) AVLTree<Key, T>::Erase(it);
    return Insert(key, obj);
}

template<typename Key, typename T>
T &Map<Key, T>::at(const Key &key) {
    auto it = Find(key);
    if (it == nullptr) throw std::out_of_range("Container does not have an element with the specified key");
    return it.return_value();
}

template<typename Key, typename T>
T &Map<Key, T>::operator[](const Key &key) {
    auto it = Find(key);
    if (it == nullptr) {
        it = Insert(std::make_pair(key, T()));
    }
    return it.return_value();
}

