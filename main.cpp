//
// Created by Oznak Banshee on 8/1/23.
//

#include "Map.h"
#include "Set.h"
#include <map>

int main() {

    s21::map<int, int> map_int{{1, 2}, {2, 3}, {3, 4}, {4, 5},
                               {5, 6}, {6, 7}, {7, 8}, {8, 9}};

    std::map<int, int> map_int_orig{{1, 2}, {2, 3}, {3, 4}, {4, 5},
                                    {5, 6}, {6, 7}, {7, 8}, {8, 9}};

    s21::map<int, int> merged{{1, 1}, {50, 2}, {60, 3}};
    std::map<int, int> merged_orig{{1, 1}, {50, 2}, {60, 3}};

    map_int.merge(merged);
    map_int_orig.merge(merged_orig);

    auto it_orig = map_int_orig.begin();
    for (auto it = map_int.begin(); it != map_int.end(); ++it) {
        std::cout << ((*it).first == it_orig->first) << " ";
        std::cout << ((*it).second == it_orig->second) << std::endl;
        ++it_orig;
    }
}


