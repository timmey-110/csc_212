#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "network.h"
#include <fstream>

TEST_CASE("Constructor and getters") {
    Network net("facebook-small.txt");
    
    CHECK(net.get_num_users() == 10);
    CHECK(net.get_num_connections() == 21);
}

TEST_CASE("is_friend correctness") {
    Network net("facebook-small.txt");
    
    // Test some known friendships from the data
    CHECK(net.is_friend(0, 1) == true);
    CHECK(net.is_friend(0, 3) == true);
    CHECK(net.is_friend(0, 7) == true);
    CHECK(net.is_friend(0, 8) == true);
    
    CHECK(net.is_friend(1, 2) == true);
    CHECK(net.is_friend(1, 4) == true);
    CHECK(net.is_friend(1, 6) == true);
    
    CHECK(net.is_friend(5, 9) == true);
    CHECK(net.is_friend(8, 9) == true);
    
    // Test symmetry
    CHECK(net.is_friend(1, 0) == true);
    CHECK(net.is_friend(3, 0) == true);
    CHECK(net.is_friend(9, 8) == true);
    
    // Test some non-friendships
    CHECK(net.is_friend(0, 2) == false);
    CHECK(net.is_friend(0, 4) == false);
    CHECK(net.is_friend(0, 5) == false);
    CHECK(net.is_friend(1, 3) == false);
    CHECK(net.is_friend(2, 3) == false);
    
    // Test self-friendship (should be false)
    for(int i = 0; i < 10; i++) {
        CHECK(net.is_friend(i, i) == false);
    }
}

TEST_CASE("Memory management") {
    // Test multiple allocations and deallocations
    for(int i = 0; i < 100; i++) {
        Network* net = new Network("facebook-small.txt");
        CHECK(net->get_num_users() == 10);
        CHECK(net->get_num_connections() == 21);
        // Test a few connections to ensure arrays are properly allocated
        CHECK(net->is_friend(0, 1) == true);
        CHECK(net->is_friend(5, 9) == true);
        delete net;
    }
}

TEST_CASE("Exception handling for invalid indices") {
    Network net("facebook-small.txt");
    
    // Test negative indices - should throw exception
    CHECK_THROWS_AS(net.is_friend(-1, 0), std::out_of_range);
    CHECK_THROWS_AS(net.is_friend(0, -1), std::out_of_range);
    CHECK_THROWS_AS(net.is_friend(-1, -1), std::out_of_range);
    CHECK_THROWS_AS(net.is_friend(-5, 3), std::out_of_range);
    
    // Test indices >= num_users - should throw exception
    CHECK_THROWS_AS(net.is_friend(10, 0), std::out_of_range);
    CHECK_THROWS_AS(net.is_friend(0, 10), std::out_of_range);
    CHECK_THROWS_AS(net.is_friend(10, 10), std::out_of_range);
    CHECK_THROWS_AS(net.is_friend(15, 20), std::out_of_range);
    CHECK_THROWS_AS(net.is_friend(100, 5), std::out_of_range);
    
    // Test valid boundary indices (0 and 9) - should NOT throw
    CHECK_NOTHROW(net.is_friend(0, 9));
    CHECK_NOTHROW(net.is_friend(9, 0));
    CHECK_NOTHROW(net.is_friend(0, 0));
    CHECK_NOTHROW(net.is_friend(9, 9));
}

TEST_CASE("Complete friendship verification") {
    Network net("facebook-small.txt");
    
    // Verify ALL friendships from your input data
    int expected_friendships[][2] = {
        {0,1}, {0,3}, {0,7}, {0,8},
        {1,2}, {1,4}, {1,6},
        {2,5}, {2,9},
        {3,4}, {3,6}, {3,9},
        {4,5}, {4,7}, {4,8},
        {5,6}, {5,9},
        {6,7}, {6,8},
        {7,9},
        {8,9}
    };
    
    // Test all expected connections exist and are symmetric
    for(auto& pair : expected_friendships) {
        CHECK(net.is_friend(pair[0], pair[1]) == true);
        CHECK(net.is_friend(pair[1], pair[0]) == true);
    }
}