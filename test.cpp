#include <gtest/gtest.h>
#include <set>
#include <map>
#include "Set.h"
#include "Map.h"

class SetTest : public testing::Test {
protected:
    s21::set<int> *my_empty_set;
    s21::set<int> *my_int_set;
    s21::set<char> *my_char_set;
    s21::set<std::string> *my_string_set;

    void SetUp() {
//        s21::set<int> *my_int_set = new s21::set<int> {-1,0,1,2,3,4,5};
//        s21::set<char> *my_char_set = new s21::set<char>;
//        s21::set<std::string> *my_string_set = new s21::set<std::string>;

    }

    void TearDown() {
//        delete my_empty_set;
//        delete my_int_set;
//        delete my_char_set;
//        delete my_string_set;
    }
};

// SET

TEST_F(SetTest, ConstructorDefaultSet) {
    s21::set<char> my_empty_set;
    std::set<char> orig_empty_set;
    EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST_F(SetTest, ConstructorInitializerSet) {
    s21::set<char> my_set = {'x', 'b', 'z', 'y'};
    std::set<char> orig_set = {'x', 'b', 'z', 'y'};
    EXPECT_EQ(my_set.size(), orig_set.size());
    auto my_it = my_set.begin();
    auto orig_it = orig_set.begin();
    for (;my_it != my_set.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE(*orig_it == *my_it);
    }
}

TEST_F(SetTest, ConstructorInitializer2Set) {
    s21::set<char> my_set = {};
    std::set<char> orig_set = {};
    EXPECT_EQ(my_set.size(), orig_set.size());
    auto my_it = my_set.begin();
    auto orig_it = orig_set.begin();
    for (;my_it != my_set.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE(*orig_it == *my_it);
    }
}

TEST_F(SetTest, ConstructorCopySet) {
    s21::set<int> my_set = {1,2,3,4,5};
    std::set<int> orig_set = {1,2,3,4,5};
    s21::set<int> my_set_copy = my_set;
    std::set<int> orig_set_copy = orig_set;
    EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
    auto my_it = my_set_copy.begin();
    auto orig_it = orig_set_copy.begin();
    for (;my_it != my_set_copy.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE(*orig_it == *my_it);
    }
}

TEST_F(SetTest, ConstructorMoveSet) {
    s21::set<int> my_set = {1,2,3,4,5};
    std::set<int> orig_set = {1,2,3,4,5};
    s21::set<int> my_set_copy = std::move(my_set);
    std::set<int> orig_set_copy = std::move(orig_set);
    EXPECT_EQ(my_set.size(), orig_set.size());
    EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
    auto my_it = my_set_copy.begin();
    auto orig_it = orig_set_copy.begin();
    for (;my_it != my_set_copy.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE(*orig_it == *my_it);
    }
}

TEST_F(SetTest, SetIteratorsSet) {
    s21::set<std::string> my_set = {"This", "is", "my", "set"};
    std::set<std::string> orig_set = {"This", "is", "my", "set"};
    auto my_it = my_set.begin();
    auto orig_it = orig_set.begin();
    EXPECT_TRUE(*orig_it == *my_it);
    my_it = my_set.end();
    orig_it = orig_set.end();
    --my_it;
    --orig_it;
    EXPECT_TRUE(*orig_it == *my_it);
}

TEST_F(SetTest, CapacitySet) {
    s21::set<char> my_empty_set;
    std::set<char> orig_empty_set;
    EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
    EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
    my_empty_set.insert('b');
    orig_empty_set.insert('c');
    EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
    EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST_F(SetTest, ClearSet) {
    s21::set<char> my_empty_set;
    std::set<char> orig_empty_set;
    my_empty_set.clear();
    orig_empty_set.clear();
    EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
    EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
    my_empty_set.insert('a');
    orig_empty_set.insert('b');
    EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
    EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
    my_empty_set.clear();
    orig_empty_set.clear();
    EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
    EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST_F(SetTest, InsertSet) {
    s21::set<std::string> my_set = {"This", "is", "my", "set"};
    std::set<std::string> orig_set = {"This", "is", "my", "set"};
    auto my_pr = my_set.insert("best");
    auto orig_pr = orig_set.insert("best");
    EXPECT_TRUE(my_pr.second == orig_pr.second);
    EXPECT_TRUE(*my_pr.first == *orig_pr.first);
    my_pr = my_set.insert("is");
    orig_pr = orig_set.insert("is");
    EXPECT_TRUE(my_pr.second == orig_pr.second);
    EXPECT_TRUE(*my_pr.first == *orig_pr.first);
}

TEST_F(SetTest, EraseSet) {
    s21::set<int> my_set = {5,4,3,2,7,8,9};
    std::set<int> orig_set = {5,4,3,2,7,8,9};
    auto size = my_set.size();
    my_set.erase(my_set.end());
    auto new_size = my_set.size();
    EXPECT_EQ(size, new_size);
    my_set.erase(my_set.begin());
    orig_set.erase(orig_set.begin());
    auto my_it = my_set.begin();
    auto orig_it = orig_set.begin();
    for (;my_it != my_set.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE(*orig_it == *my_it);
    }
}

TEST_F(SetTest, SwapSet) {
    s21::set<int> my_set = {1};
    s21::set<int> my_swap_set = {3,4,5};

    my_set.swap(my_swap_set);
    EXPECT_EQ(my_set.size(), 3);
    EXPECT_EQ(my_swap_set.size(), 1);
    EXPECT_EQ(*my_set.begin(), 3);
    EXPECT_EQ(*my_swap_set.begin(), 1);
}

TEST_F(SetTest, MergeSet) {
    s21::set<int> my_set = {1};
    s21::set<int> my_merge_set = {3,4,5};
    my_set.merge(my_merge_set);

    std::set<int> orig_set = {1};
    std::set<int> orig_merge_set = {3,4,5};
    orig_set.merge(orig_merge_set);
    auto my_it = my_set.begin();
    auto orig_it = orig_set.begin();
    for (;my_it != my_set.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE(*orig_it == *my_it);
    }
    EXPECT_EQ(orig_set.size(), my_set.size());
    EXPECT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST_F(SetTest, FindSet) {
    s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
    s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
    auto my_it = my_set.find(2.4);
    auto orig_it = orig_set.find(2.4);
    EXPECT_TRUE(*orig_it == *my_it);
}

TEST_F(SetTest, ContainsSet) {
    s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
    s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
    EXPECT_EQ(my_set.contains(2), orig_set.contains(2));
    EXPECT_EQ(my_set.contains(2.1), orig_set.contains(2.1));
}

// MAP

TEST_F(SetTest, ConstructorDefaultMap) {
    s21::map<int, char> my_empty_map;
    std::map<int, char> orig_empty_map;
    EXPECT_EQ(my_empty_map.empty(), orig_empty_map.empty());
}


TEST_F(SetTest, ConstructorInitializerMap) {
    s21::map<int, char> my_map = {{1,'x'}, {2,'b'}, {3,'z'}, {4,'y'}};
    std::map<int, char> orig_map = {{1,'x'}, {2,'b'}, {3,'z'}, {4,'y'}};
    EXPECT_EQ(my_map.size(), orig_map.size());
    auto my_it = my_map.begin();
    auto orig_it = orig_map.begin();
    for (;my_it != my_map.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE((*my_it).first == (*orig_it).first);
        EXPECT_TRUE((*my_it).second == (*orig_it).second);
    }
}

TEST_F(SetTest, ConstructorInitializer2Map) {
    s21::map<int, char> my_map = {};
    std::map<int, char> orig_map = {};
    EXPECT_EQ(my_map.size(), orig_map.size());
    auto my_it = my_map.begin();
    auto orig_it = orig_map.begin();
    for (;my_it != my_map.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE((*my_it).first == (*orig_it).first);
        EXPECT_TRUE((*my_it).second == (*orig_it).second);
    }
}


TEST_F(SetTest, ConstructorCopyMap) {
    s21::map<int, int> my_map = {{1,2},{3,4},{5,6}};
    std::map<int, int> orig_map = {{1,2},{3,4},{5,6}};
    s21::map<int, int> my_map_copy = my_map;
    std::map<int, int> orig_map_copy = orig_map;
    EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
    auto my_it = my_map_copy.begin();
    auto orig_it = orig_map_copy.begin();
    for (;my_it != my_map_copy.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE((*my_it).first == (*orig_it).first);
        EXPECT_TRUE((*my_it).second == (*orig_it).second);
    }
}

TEST_F(SetTest, ConstructorMoveMap) {
    s21::map<int, int> my_map = {{1,2},{3,4},{5,6}};
    std::map<int, int> orig_map = {{1,2},{3,4},{5,6}};
    s21::map<int, int> my_map_copy = std::move(my_map);
    std::map<int, int> orig_map_copy = std::move(orig_map);
    EXPECT_EQ(my_map.size(), orig_map.size());
    EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
    auto my_it = my_map_copy.begin();
    auto orig_it = orig_map_copy.begin();
    for (;my_it != my_map_copy.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE((*my_it).first == (*orig_it).first);
        EXPECT_TRUE((*my_it).second == (*orig_it).second);
    }
}

TEST_F(SetTest, MapOperator) {
    s21::map<char, std::string> my_map = {{'a',"Alina"},{'b',"Boris"},{'c',"Chuck"}};
    std::map<char, std::string> orig_map = {{'a',"Alina"},{'b',"Boris"},{'c',"Chuck"}};
    my_map['a'] = "Alisa";
    orig_map['a'] = "Alisa";
    orig_map['b'] = "Ben";
    EXPECT_TRUE(my_map['a'] == orig_map['a']);
    EXPECT_FALSE(my_map['b'] == orig_map['b']);
    EXPECT_TRUE(my_map['c'] == orig_map['c']);
}

TEST_F(SetTest, MapAtOperatorException) {
    s21::map<char, std::string> my_map = {{'a',"Alina"},{'b',"Boris"},{'c',"Chuck"}};
    EXPECT_THROW(my_map.at('g') = "Alisa", std::out_of_range);
}

TEST_F(SetTest, MapAtOperator) {
    s21::map<char, std::string> my_map = {{'a',"Alina"},{'b',"Boris"},{'c',"Chuck"}};
    std::map<char, std::string> orig_map = {{'a',"Alina"},{'b',"Boris"},{'c',"Chuck"}};
    my_map.at('a') = "Alisa";
    orig_map.at('a') = "Alisa";
    orig_map.at('b') = "Ben";
    EXPECT_TRUE(my_map['a'] == orig_map['a']);
    EXPECT_FALSE(my_map['b'] == orig_map['b']);
    EXPECT_TRUE(my_map['c'] == orig_map['c']);
}

TEST_F(SetTest, MapCapacity) {
    s21::map<char, std::string> my_map;
    std::map<char, std::string> orig_map;
    EXPECT_TRUE(my_map.empty() == orig_map.empty());
    my_map.insert('z',"wow");
    EXPECT_FALSE(my_map.empty() == orig_map.empty());
    EXPECT_EQ(my_map.size(), 1);
}

TEST_F(SetTest, MapClear) {
    s21::map<int, int> my_map;
    std::map<int, int> orig_map;
    my_map.clear();
    orig_map.clear();
    EXPECT_EQ(my_map.empty(), orig_map.empty());
    my_map.insert(std::make_pair(1,1));
    orig_map.insert(std::make_pair(1,1));
    EXPECT_EQ(my_map.empty(), orig_map.empty());
    my_map.clear();
    orig_map.clear();
    EXPECT_EQ(my_map.empty(), orig_map.empty());
}

TEST_F(SetTest, MapInsert1) {
    s21::map<int, char> my_map;
    std::map<int, char> orig_map;
    my_map.insert(std::make_pair(1,'a'));
    my_map.insert(std::make_pair(2,'a'));
    my_map.insert(std::make_pair(3,'a'));
    orig_map.insert(std::make_pair(1,'a'));
    orig_map.insert(std::make_pair(2,'a'));
    orig_map.insert(std::make_pair(3,'a'));

    auto my_it = my_map.begin();
    auto orig_it = orig_map.begin();
    for (;my_it != my_map.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE((*my_it).first == (*orig_it).first);
        EXPECT_TRUE((*my_it).second == (*orig_it).second);
    }

    auto pr1 = my_map.insert(std::make_pair(1,'a'));
    auto pr2 = orig_map.insert(std::make_pair(1,'a'));
    EXPECT_TRUE(pr1.second == pr2.second);
}

TEST_F(SetTest, MapInsert2) {
    s21::map<int, char> my_map;
    std::map<int, char> orig_map;
    my_map.insert(1,'a');
    my_map.insert(2, 'a');
    my_map.insert(3, 'a');
    orig_map.insert(std::make_pair(1,'a'));
    orig_map.insert(std::make_pair(2,'a'));
    orig_map.insert(std::make_pair(3,'a'));

    auto my_it = my_map.begin();
    auto orig_it = orig_map.begin();
    for (;my_it != my_map.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE((*my_it).first == (*orig_it).first);
        EXPECT_TRUE((*my_it).second == (*orig_it).second);
    }

    auto pr1 = my_map.insert(1, 'a');
    auto pr2 = orig_map.insert(std::make_pair(1,'a'));
    EXPECT_TRUE(pr1.second == pr2.second);
}

TEST_F(SetTest, MapInsert3) {
    s21::map<int, char> my_map;
    std::map<int, char> orig_map;
    my_map.insert(1,'a');
    my_map.insert(2, 'a');
    my_map.insert(3, 'a');
    orig_map.insert(std::make_pair(1,'a'));
    orig_map.insert(std::make_pair(2,'a'));
    orig_map.insert(std::make_pair(3,'a'));

    auto my_it = my_map.begin();
    auto orig_it = orig_map.begin();
    for (;my_it != my_map.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE((*my_it).first == (*orig_it).first);
        EXPECT_TRUE((*my_it).second == (*orig_it).second);
    }

    auto pr1 = my_map.insert_or_assign(1, 'b');
    auto i = orig_map.begin();
    EXPECT_TRUE((*pr1.first).first == (*i).first);
    EXPECT_FALSE((*pr1.first).second == (*i).second);
}


TEST_F(SetTest, MapErase) {
    s21::map<int, char> my_map = {{1,'x'}, {2,'b'}, {3,'z'}, {4,'y'}};
    std::map<int, char> orig_map = {{1,'x'}, {2,'b'}, {3,'z'}, {4,'y'}};
    EXPECT_EQ(my_map.size(), orig_map.size());
    my_map.erase(my_map.begin());
    orig_map.erase(orig_map.begin());
    EXPECT_EQ(my_map.size(), orig_map.size());
    auto my_it = my_map.begin();
    auto orig_it = orig_map.begin();
    for (;my_it != my_map.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE((*my_it).first == (*orig_it).first);
        EXPECT_TRUE((*my_it).second == (*orig_it).second);
    }
}

TEST_F(SetTest, SwapMap) {
    s21::map<int, int> my_map = {{1,1}};
    s21::map<int, int> my_swap_map = {{3,3}, {4,4}};

    my_map.swap(my_swap_map);
    EXPECT_EQ(my_map.size(), 2);
    EXPECT_EQ(my_swap_map.size(), 1);
    auto x = (*(my_map.begin())).first;
    auto y = (*(my_swap_map.begin())).first;
    EXPECT_EQ(x, 3);
    EXPECT_EQ(y, 1);
}

TEST_F(SetTest, MergeMap) {
    s21::map<int, int> my_map = {{1,1}, {4,4}, {2,2}};
    s21::map<int, int> my_map_merge = {{3,3}, {4,4}};

    std::map<int, int> orig_map = {{1,1}, {4,4}, {2,2}};
    std::map<int, int> orig_map_merge = {{3,3}, {4,4}};

    my_map.merge(my_map_merge);
    orig_map.merge(orig_map_merge);

    auto my_it = my_map.begin();
    auto orig_it = orig_map.begin();
    for (;my_it != my_map.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE((*my_it).first == (*orig_it).first);
        EXPECT_TRUE((*my_it).second == (*orig_it).second);
    }
    EXPECT_EQ(my_map_merge.contains(4), orig_map_merge.contains(4));
    EXPECT_EQ(my_map_merge.contains(3), orig_map_merge.contains(3));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}