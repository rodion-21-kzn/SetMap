//
// Created by Oznak Banshee on 7/31/23.
//

#include "Set.h"
#include "Map.h"
#include <map>

namespace s21 {

    template<typename Key, typename T>
    map<Key, T>::map(const std::initializer_list<value_type> &items) {
        for (auto i = items.begin(); i != items.end(); ++i) {
            insert(*i);
        }
    }


    template<typename Key, typename T>
    map<Key, T> &map<Key, T>::operator=(map &&other) noexcept {
        if (this != &other) {
            AVLTree<Key, T>::operator=(std::move(other));
        }
        return *this;
    }

    template<typename Key, typename T>
    map<Key, T> &map<Key, T>::operator=(const map &other) {
        if (this != &other) {
            AVLTree<Key, T>::operator=(other);
        }
        return *this;
    }

    template<typename Key, typename T>
    std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(const value_type &value) {
        return insert(value.first, value.second);
    }


    template<typename Key, typename T>
    std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(const Key &key, const T &obj) {
        std::pair<iterator, bool> return_value;
        if (AVLTree<Key, T>::root_ == nullptr) {
            AVLTree<Key, T>::root_ = new typename AVLTree<Key, T>::Node(key, obj);
            return_value.first = iterator(AVLTree<Key, T>::root_);
            return_value.second = true;
        } else {
            bool check_insert = AVLTree<Key, T>::RecursiveInsert(AVLTree<Key, T>::root_, key, obj);
            return_value.first = find(key); // НАДО НАПИСАТЬ ФУНКЦИЮ FIND
            return_value.second = check_insert;
        }
        return return_value;
    }

    template<typename Key, typename T>
    typename map<Key, T>::value_type &map<Key, T>::MapIterator::operator*() {
        if (AVLTree<Key, T>::Iterator::iter_node_ == nullptr) {
            static value_type fake_value{};
            return fake_value;
        }
        static std::pair<const key_type, mapped_type> pr = std::make_pair(AVLTree<Key, T>::Iterator::iter_node_->key_,
                                                                          AVLTree<Key, T>::Iterator::iter_node_->value_);
        return pr;
    }

    template<typename Key, typename T>
    T &map<Key, T>::MapIterator::return_value() {
        if (AVLTree<Key, T>::Iterator::iter_node_ == nullptr) {
            static T fake_value{};
            return fake_value;
        }
        return AVLTree<Key, T>::Iterator::iter_node_->value_;
    }


    template<typename Key, typename T>
    typename map<Key, T>::iterator map<Key, T>::find(const Key &key) {
        typename AVLTree<Key, T>::Node *node = AVLTree<Key, T>::RecursiveFind(AVLTree<Key, T>::root_, key);
        return iterator(node);
    }

    template<typename Key, typename T>
    std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(const Key &key, const T &obj) {
        auto it = find(key);
        if (it != this->end()) AVLTree<Key, T>::erase(it);
        return insert(key, obj);
    }

    template<typename Key, typename T>
    T &map<Key, T>::at(const Key &key) {
        auto it = find(key);
        if (it == nullptr) throw std::out_of_range("Container does not have an element with the specified key");
        return it.return_value();
    }

    template<typename Key, typename T>
    T &map<Key, T>::operator[](const Key &key) {
        auto it = find(key);
        if (it == nullptr) {
            it = insert(std::make_pair(key, T()));
        }
        return it.return_value();
    }

//    template<typename Key, typename T>
//    typename map<Key, T>::iterator map<Key, T>::begin() {
//        return AVLTree<Key, T>::begin();
//    }
//
//    template<typename Key, typename T>
//    typename map<Key, T>::iterator map<Key, T>::end() {
//        return AVLTree<Key, T>::end();
//    }

}