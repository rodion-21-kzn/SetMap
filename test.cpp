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

TEST_F(SetTest, ConstructorDefault) {
    s21::set<char> my_empty_set;
    std::set<char> orig_empty_set;
    EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST_F(SetTest, ConstructorInitializer) {
    s21::set<char> my_set = {'x', 'b', 'z', 'y'};
    std::set<char> orig_set = {'x', 'b', 'z', 'y'};
    EXPECT_EQ(my_set.size(), orig_set.size());
    auto my_it = my_set.begin();
    auto orig_it = orig_set.begin();
    for (;my_it != my_set.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE(*orig_it == *my_it);
    }
}

TEST_F(SetTest, ConstructorInitializer2) {
    s21::set<char> my_set = {};
    std::set<char> orig_set = {};
    EXPECT_EQ(my_set.size(), orig_set.size());
    auto my_it = my_set.begin();
    auto orig_it = orig_set.begin();
    for (;my_it != my_set.end(); ++my_it, ++orig_it ) {
        EXPECT_TRUE(*orig_it == *my_it);
    }
}

TEST_F(SetTest, ConstructorCopy) {
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

TEST_F(SetTest, ConstructorMove) {
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

TEST_F(SetTest, SetIterators) {
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

TEST_F(SetTest, Capacity) {
    s21::set<char> my_empty_set;
    std::set<char> orig_empty_set;
    EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
    EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
    my_empty_set.insert('b');
    orig_empty_set.insert('c');
    EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
    EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST_F(SetTest, Clear) {
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

TEST_F(SetTest, Insert) {
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

TEST_F(SetTest, Erase) {
    s21::set<int> my_set = {5,4,3,2,7,8,9};
    std::set<int> orig_set = {5,4,3,2,7,8,9};
//    my_set.erase(my_set.end());
//    orig_set.erase(orig_set.end());
//    EXPECT_EQ(my_set.size(), 7);
//    EXPECT_EQ(orig_set.size(), 7);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}