//
// Created by Oznak Banshee on 8/1/23.
//

#include "Map.h"
#include "Set.h"
#include <map>
#include <set>

int main() {
    s21::map<int, std::string> new_map;

    s21::map<int, std::string> my_map{
            std::make_pair(42, "aaa"), std::make_pair(3, "bbb"),
            std::make_pair(33, "ccc"), std::make_pair(3, "ddd")};
    std::map<int, std::string> std_map{
            std::make_pair(42, "aaa"), std::make_pair(3, "bbb"),
            std::make_pair(33, "ccc"), std::make_pair(3, "ddd")};

    auto my_iter = my_map.begin();
    auto std_iter = std_map.begin();

    while (my_iter != my_map.end()) {
        auto a = (*my_iter).second;
        std::cout << a << " my" << std::endl;
        std::cout << (*std_iter).second << std::endl;
        ++my_iter;
        ++std_iter;
    }
}


