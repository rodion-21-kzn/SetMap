#include <gtest/gtest.h>
#include <set>
#include <map>
#include <algorithm>
#include "Set.h"
#include "Map.h"

class MapTest {
public:
    s21::map<int, int> empty_map;
    s21::map<int, int> map_int{{1, 2}, {2, 3}, {3, 4}, {4, 5},
                               {5, 6}, {6, 7}, {7, 8}, {8, 9}};
    s21::map<std::string, std::string> map_string{
            {"baka", "mitai"}, {"obon", "katsurage"}, {"kokoro", "desu"}};
    s21::map<double, double> map_double{
            {1.2, 3.4}, {5.2, 1.1}, {-10.2, 1.123}, {0.02, 12.33}};

    std::map<int, int> empty_map_orig;
    std::map<int, int> map_int_orig{{1, 2}, {2, 3}, {3, 4}, {4, 5},
                                    {5, 6}, {6, 7}, {7, 8}, {8, 9}};
    std::map<std::string, std::string> map_string_orig{
            {"baka", "mitai"}, {"obon", "katsurage"}, {"kokoro", "desu"}};
    std::map<double, double> map_double_orig{
            {1.2, 3.4}, {5.2, 1.1}, {-10.2, 1.123}, {0.02, 12.33}};

    s21::map<int, int> swapped{{100, 0}, {101, 1}, {102, 2}};
    std::map<int, int> swapped_orig{{100, 0}, {101, 1}, {102, 2}};

    s21::map<int, int> merged{{1, 1}, {50, 2}, {60, 3}};
    std::map<int, int> merged_orig{{1, 1}, {50, 2}, {60, 3}};
};

TEST(map, Constructor) {
    MapTest tmp;
    EXPECT_EQ(*(tmp.empty_map.begin()) == *(tmp.empty_map_orig.begin()), true);
    EXPECT_EQ(*(tmp.empty_map.end()) == *(tmp.empty_map_orig.end()), true);
}

TEST(map, ConstructorList) {
    MapTest tmp;
    for (int i = 0; static_cast<size_t>(i) < tmp.map_int_orig.size(); ++i) {
        EXPECT_NEAR(tmp.map_int_orig[i], tmp.map_int[i], 0.001);
    }
}

TEST(map, ConstructorCopy) {
    MapTest tmp;
    s21::map<double, double> two{tmp.map_double};
    std::map<double, double> two_orig{tmp.map_double_orig};
    for (int i = 0; static_cast<size_t>(i) < two_orig.size(); ++i) {
        EXPECT_NEAR(two[i], tmp.map_double_orig[i], 0.001);
    }
    tmp.map_double.clear();
    EXPECT_TRUE(tmp.map_double.empty());
    EXPECT_TRUE(!two.empty());
}

TEST(map, ConstructorMove) {
    MapTest tmp;
    s21::map<double, double> two{std::move(tmp.map_double)};
    int size = static_cast<int>(two.size());
    for (int i = 0; i < size; ++i) {
        EXPECT_NEAR(two[i], tmp.map_double_orig[i], 0.001);
    }
    EXPECT_TRUE(tmp.map_double.empty());
    EXPECT_TRUE(!two.empty());
}

TEST(map, EmptyTest) {
    MapTest tmp;
    EXPECT_TRUE(tmp.map_int.empty() == tmp.map_int_orig.empty());
    EXPECT_TRUE(tmp.empty_map.empty() == tmp.empty_map_orig.empty());
    EXPECT_TRUE(tmp.map_string.empty() == tmp.map_string_orig.empty());
    EXPECT_TRUE(tmp.map_double.empty() == tmp.map_double.empty());
}

TEST(map, SizeTest) {
    MapTest tmp;
    EXPECT_TRUE(tmp.map_int.size() == tmp.map_int.size());
    EXPECT_TRUE(tmp.empty_map.size() == tmp.empty_map.size());
    EXPECT_TRUE(tmp.map_string.size() == tmp.map_string.size());
    EXPECT_TRUE(tmp.map_double.size() == tmp.map_double_orig.size());
}

//TEST(map, MaxSizeTest) {
//    MapTest tmp;
//    EXPECT_TRUE(tmp.map_int.max_size() == tmp.map_int.max_size());
//    EXPECT_TRUE(tmp.empty_map.max_size() == tmp.empty_map_orig.max_size());
//}

TEST(map, ClearTest) {
    MapTest tmp;
    tmp.map_int.clear();
    tmp.map_int_orig.clear();
    EXPECT_TRUE(tmp.map_int.empty() == tmp.map_int_orig.empty());
}

TEST(map, EraseTest) {
    MapTest tmp;
    tmp.map_int.erase(tmp.map_int.begin());
    tmp.map_int_orig.erase(tmp.map_int_orig.begin());
    EXPECT_TRUE(tmp.empty_map.size() == tmp.empty_map_orig.size());
    EXPECT_THROW(tmp.map_int.at(1), std::out_of_range);
    EXPECT_THROW(tmp.map_int.at(1), std::out_of_range);
}

TEST(map, InsertTest) {
    MapTest tmp;
    auto s21_pair = tmp.empty_map.insert({1, 2});
    auto std_pair = tmp.empty_map_orig.insert({1, 2});
    EXPECT_TRUE(tmp.empty_map[1] == tmp.empty_map_orig[1]);
    EXPECT_TRUE(s21_pair.second == std_pair.second);
    s21_pair = tmp.empty_map.insert(5, 3);
    EXPECT_TRUE(tmp.empty_map[5] == 3);
    EXPECT_TRUE(s21_pair.second);
    s21_pair = tmp.empty_map.insert_or_assign(5, 10);
    EXPECT_TRUE(tmp.empty_map[5] == 10);
    EXPECT_FALSE(s21_pair.second);
}

TEST(map, SwapTest) {
    MapTest tmp;
    tmp.map_int.swap(tmp.swapped);
    tmp.map_int_orig.swap(tmp.swapped_orig);
    EXPECT_TRUE(tmp.map_int.size() == tmp.map_int_orig.size());
    auto it_orig = tmp.map_int_orig.begin();
    for (auto it = tmp.map_int.begin(); it != tmp.map_int.end(); ++it) {
        EXPECT_TRUE(*it == *(it_orig++));
    }
}

TEST(map, ContainsTest) {
    MapTest tmp;
    for (auto it : tmp.map_int_orig) {
        EXPECT_TRUE(tmp.map_int.contains(it.first));
        EXPECT_FALSE(tmp.map_int.contains(it.first + 10));
    }
}

TEST(map, MergeTest) {
    MapTest tmp;
    tmp.map_int.merge(tmp.merged);
    tmp.map_int_orig.merge(tmp.merged_orig);
    EXPECT_EQ(tmp.map_int.size(), tmp.map_int_orig.size());
    EXPECT_EQ(tmp.merged.size(), tmp.merged_orig.size());
    auto it_orig = tmp.map_int_orig.begin();
    for (auto it = tmp.map_int.begin(); it != tmp.map_int.end(); ++it) {
        EXPECT_TRUE(*it == *(it_orig++));
    }
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}