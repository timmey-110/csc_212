#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "multilevel_list.h"
#include <sstream>
#include <string>

std::string capture_print(const MultiLevelLinkedList& mll) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    mll.print();
    std::cout.rdbuf(old);
    std::string result = buffer.str();
    auto start = std::find_if(result.begin(), result.end(), [](unsigned char c) { return !std::isspace(c); }); // ltrim
    auto end = std::find_if(result.rbegin(), result.rend(), [](unsigned char c) { return !std::isspace(c); }).base(); // rtrim
    return (start < end) ? std::string(start, end) : std::string();
}

TEST_CASE("InsertTopLevel") {
    MultiLevelLinkedList mll;
    mll.insert_top_level("M");
    CHECK(capture_print(mll) == "M");
    mll.insert_top_level("D");
    mll.insert_top_level("N");
    CHECK(capture_print(mll) == "D M N");
}

TEST_CASE("InsertChild") {
    MultiLevelLinkedList mll;
    mll.insert_top_level("M");
    mll.insert_child("M", "M1");
    CHECK(capture_print(mll) == "M M1");
    // handout example
    MultiLevelLinkedList mll23;
    mll23.insert_top_level("M");
    mll23.insert_top_level("D");
    mll23.insert_child("M", "M2");
    mll23.insert_child("M", "M1");
    mll23.insert_child("M2", "M2A");
    mll23.insert_child("M2", "M2B");
    mll23.insert_top_level("N");
    mll23.insert_child("N", "O2");
    mll23.insert_child("N", "O1");
    std::string output = capture_print(mll23);
    CHECK(output == "D M M1 M2 M2A M2B N O1 O2");
}

TEST_CASE("Destroy") {
    MultiLevelLinkedList mll;
    CHECK(capture_print(mll) == "");
    mll.destroy();
    MultiLevelLinkedList *mll23 = new MultiLevelLinkedList();
    mll23->insert_top_level("M");
    mll23->insert_top_level("D");
    mll23->insert_child("M", "M2");
    mll23->insert_child("M", "M1");
    mll23->insert_child("M2", "M2A");
    CHECK(capture_print(*mll23) == "D M M1 M2 M2A");
    mll23->destroy();
    CHECK(capture_print(*mll23) == "");
    mll23->destroy();
    CHECK(capture_print(*mll23) == "");
    delete mll23;
}