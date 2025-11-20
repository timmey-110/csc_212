#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <algorithm>
#include <numeric>
#include <random>
#include <unordered_set>
#include <vector>

#include "doctest.h"
#include "pseudoset.h"

class PseudoSetTester {
   public:
    using Node = PseudoSet::Node;
    using Color = PseudoSet::Color;

    [[nodiscard]] static Node *fix_red_left_left(Node *root) {
        return PseudoSet::fix_red_left_left(root);
    }

    [[nodiscard]] static Node *fix_red_left_right(Node *root) {
        return PseudoSet::fix_red_left_right(root);
    }

    [[nodiscard]] static Node *fix_red_right_left(Node *root) {
        return PseudoSet::fix_red_right_left(root);
    }

    [[nodiscard]] static Node *fix_red_right_right(Node *root) {
        return PseudoSet::fix_red_right_right(root);
    }

    [[nodiscard]] static Node *balance(Node *root) {
        return PseudoSet::balance(root);
    }

    [[nodiscard]] static Node *insert(Node *root, int value) {
        return PseudoSet::insert(root, value);
    }

    [[nodiscard]] static Node *find(Node *root, int value) {
        return PseudoSet::find(root, value);
    }

    static void destroy(Node *root) { PseudoSet::destroy(root); }
};

using Node = PseudoSetTester::Node;
using Color = PseudoSetTester::Color;

static bool is_red(const Node *n) { return n && n->color == Color::Red; }

static bool validate_black_height(const Node *node, int &black_height) {
    if (!node) {
        black_height = 0;
        return true;
    }

    int left_bh = 0, right_bh = 0;
    if (!validate_black_height(node->left, left_bh)) return false;
    if (!validate_black_height(node->right, right_bh)) return false;
    if (left_bh != right_bh) return false;

    black_height = left_bh + (node->color == Color::Black ? 1 : 0);
    return true;
}

static bool validate_subtree(const Node *node) {
    if (!node) return true;

    if (is_red(node)) {
        if (is_red(node->left) || is_red(node->right)) return false;
    }

    return validate_subtree(node->left) && validate_subtree(node->right);
}

static bool validate(const Node *root) {
    if (!root) return true;
    if (root->color != Color::Black) return false;
    if (!validate_subtree(root)) return false;

    int bh = 0;
    return validate_black_height(root, bh);
}

void collect_elements(const Node *node, std::unordered_set<int> &elems) {
    if (!node) return;
    collect_elements(node->left, elems);
    elems.insert(node->value);
    collect_elements(node->right, elems);
}

bool tree_equals_set(const Node *root,
                     const std::unordered_set<int> &expected) {
    std::unordered_set<int> tree_elems;
    collect_elements(root, tree_elems);
    return tree_elems == expected;
}

TEST_CASE("fix_red_left_left") {
    auto a = reinterpret_cast<Node *>(0x4);
    auto b = reinterpret_cast<Node *>(0x5);
    auto c = reinterpret_cast<Node *>(0x6);
    auto d = reinterpret_cast<Node *>(0x7);
    auto x = new Node('x', a, b, Color::Red);
    auto y = new Node('y', x, c, Color::Red);
    auto z = new Node('z', y, d, Color::Black);

    auto root = PseudoSetTester::fix_red_left_left(z);

    REQUIRE_NE(root, nullptr);
    CHECK_EQ(root->value, 'y');
    CHECK_EQ(root->color, Color::Red);

    REQUIRE_NE(root->left, nullptr);
    CHECK_EQ(root->left->value, 'x');
    CHECK_EQ(root->left->color, Color::Black);
    CHECK_EQ(root->left->left, a);
    CHECK_EQ(root->left->right, b);

    REQUIRE_NE(root->right, nullptr);
    CHECK_EQ(root->right->value, 'z');
    CHECK_EQ(root->right->color, Color::Black);
    CHECK_EQ(root->right->left, c);
    CHECK_EQ(root->right->right, d);

    delete root->left;
    delete root->right;
    delete root;
}

TEST_CASE("fix_red_left_right") {
    auto a = reinterpret_cast<Node *>(0x4);
    auto b = reinterpret_cast<Node *>(0x5);
    auto c = reinterpret_cast<Node *>(0x6);
    auto d = reinterpret_cast<Node *>(0x7);
    auto y = new Node('y', b, c, Color::Red);
    auto x = new Node('x', a, y, Color::Red);
    auto z = new Node('z', x, d, Color::Black);

    auto root = PseudoSetTester::fix_red_left_right(z);

    REQUIRE_NE(root, nullptr);
    CHECK_EQ(root->value, 'y');
    CHECK_EQ(root->color, Color::Red);

    REQUIRE_NE(root->left, nullptr);
    CHECK_EQ(root->left->value, 'x');
    CHECK_EQ(root->left->color, Color::Black);
    CHECK_EQ(root->left->left, a);
    CHECK_EQ(root->left->right, b);

    REQUIRE_NE(root->right, nullptr);
    CHECK_EQ(root->right->value, 'z');
    CHECK_EQ(root->right->color, Color::Black);
    CHECK_EQ(root->right->left, c);
    CHECK_EQ(root->right->right, d);

    delete root->left;
    delete root->right;
    delete root;
}

TEST_CASE("fix_red_right_left") {
    auto a = reinterpret_cast<Node *>(0x4);
    auto b = reinterpret_cast<Node *>(0x5);
    auto c = reinterpret_cast<Node *>(0x6);
    auto d = reinterpret_cast<Node *>(0x7);
    auto y = new Node('y', b, c, Color::Red);
    auto z = new Node('z', y, d, Color::Red);
    auto x = new Node('x', a, z, Color::Black);

    auto root = PseudoSetTester::fix_red_right_left(x);

    REQUIRE_NE(root, nullptr);
    CHECK_EQ(root->value, 'y');
    CHECK_EQ(root->color, Color::Red);

    REQUIRE_NE(root->left, nullptr);
    CHECK_EQ(root->left->value, 'x');
    CHECK_EQ(root->left->color, Color::Black);
    CHECK_EQ(root->left->left, a);
    CHECK_EQ(root->left->right, b);

    REQUIRE_NE(root->right, nullptr);
    CHECK_EQ(root->right->value, 'z');
    CHECK_EQ(root->right->color, Color::Black);
    CHECK_EQ(root->right->left, c);
    CHECK_EQ(root->right->right, d);

    delete root->left;
    delete root->right;
    delete root;
}

TEST_CASE("fix_red_right_right") {
    auto a = reinterpret_cast<Node *>(0x4);
    auto b = reinterpret_cast<Node *>(0x5);
    auto c = reinterpret_cast<Node *>(0x6);
    auto d = reinterpret_cast<Node *>(0x7);
    auto z = new Node('z', c, d, Color::Red);
    auto y = new Node('y', b, z, Color::Red);
    auto x = new Node('x', a, y, Color::Black);

    auto root = PseudoSetTester::fix_red_right_right(x);

    REQUIRE_NE(root, nullptr);
    CHECK_EQ(root->value, 'y');
    CHECK_EQ(root->color, Color::Red);

    REQUIRE_NE(root->left, nullptr);
    CHECK_EQ(root->left->value, 'x');
    CHECK_EQ(root->left->color, Color::Black);
    CHECK_EQ(root->left->left, a);
    CHECK_EQ(root->left->right, b);

    REQUIRE_NE(root->right, nullptr);
    CHECK_EQ(root->right->value, 'z');
    CHECK_EQ(root->right->color, Color::Black);
    CHECK_EQ(root->right->left, c);
    CHECK_EQ(root->right->right, d);

    delete root->left;
    delete root->right;
    delete root;
}

TEST_CASE("balance with empty tree") {
    auto root = PseudoSetTester::balance(nullptr);
    CHECK_EQ(root, nullptr);
}

TEST_CASE("balance with a single node") {
    auto node = new Node(0, nullptr, nullptr, Color::Black);
    auto root = PseudoSetTester::balance(node);

    REQUIRE_NE(root, nullptr);
    CHECK_EQ(root->value, 0);
    CHECK_EQ(root->color, Color::Black);
    CHECK_EQ(root->left, nullptr);
    CHECK_EQ(root->right, nullptr);

    delete root;
}

TEST_CASE("balance with three nodes") {
    auto node = new Node(0, new Node(1), new Node(2), Color::Black);
    auto root = PseudoSetTester::balance(node);

    REQUIRE_NE(root, nullptr);
    CHECK_EQ(root->value, 0);
    CHECK_EQ(root->color, Color::Black);

    REQUIRE_NE(root->left, nullptr);
    CHECK_EQ(root->left->value, 1);
    CHECK_EQ(root->left->color, Color::Red);

    REQUIRE_NE(root->right, nullptr);
    CHECK_EQ(root->right->value, 2);
    CHECK_EQ(root->right->color, Color::Red);

    delete root->left;
    delete root->right;
    delete root;
}

TEST_CASE("balance with no violation") {
    auto x = new Node('x', nullptr, nullptr, Color::Black);
    auto y = new Node('y', x, nullptr, Color::Red);
    auto z = new Node('z', y, nullptr, Color::Black);

    auto root = PseudoSetTester::balance(z);

    REQUIRE_NE(root, nullptr);
    CHECK_EQ(root->value, 'z');
    CHECK_EQ(root->color, Color::Black);
    CHECK_EQ(root->right, nullptr);

    REQUIRE_NE(root->left, nullptr);
    CHECK_EQ(root->left->value, 'y');
    CHECK_EQ(root->left->color, Color::Red);
    CHECK_EQ(root->left->right, nullptr);

    REQUIRE_NE(root->left->left, nullptr);
    CHECK_EQ(root->left->left->value, 'x');
    CHECK_EQ(root->left->left->color, Color::Black);
    CHECK_EQ(root->left->left->left, nullptr);
    CHECK_EQ(root->left->left->right, nullptr);

    delete root->left->left;
    delete root->left;
    delete root;
}

TEST_CASE("balance with red-child left-left violation") {
    auto x = new Node('x', nullptr, nullptr, Color::Red);
    auto y = new Node('y', x, nullptr, Color::Red);
    auto z = new Node('z', y, nullptr, Color::Black);

    auto root = PseudoSetTester::balance(z);

    REQUIRE_NE(root, nullptr);
    CHECK_EQ(root->value, 'y');
    CHECK_EQ(root->color, Color::Red);

    REQUIRE_NE(root->left, nullptr);
    CHECK_EQ(root->left->value, 'x');
    CHECK_EQ(root->left->color, Color::Black);
    CHECK_EQ(root->left->left, nullptr);
    CHECK_EQ(root->left->right, nullptr);

    REQUIRE_NE(root->right, nullptr);
    CHECK_EQ(root->right->value, 'z');
    CHECK_EQ(root->right->color, Color::Black);
    CHECK_EQ(root->right->left, nullptr);
    CHECK_EQ(root->right->right, nullptr);

    delete root->left;
    delete root->right;
    delete root;
}

TEST_CASE("balance with red-child left-right violation") {
    auto y = new Node('y', nullptr, nullptr, Color::Red);
    auto x = new Node('x', nullptr, y, Color::Red);
    auto z = new Node('z', x, nullptr, Color::Black);

    auto root = PseudoSetTester::balance(z);

    REQUIRE_NE(root, nullptr);
    CHECK_EQ(root->value, 'y');
    CHECK_EQ(root->color, Color::Red);

    REQUIRE_NE(root->left, nullptr);
    CHECK_EQ(root->left->value, 'x');
    CHECK_EQ(root->left->color, Color::Black);
    CHECK_EQ(root->left->left, nullptr);
    CHECK_EQ(root->left->right, nullptr);

    REQUIRE_NE(root->right, nullptr);
    CHECK_EQ(root->right->value, 'z');
    CHECK_EQ(root->right->color, Color::Black);
    CHECK_EQ(root->right->left, nullptr);
    CHECK_EQ(root->right->right, nullptr);

    delete root->left;
    delete root->right;
    delete root;
}

TEST_CASE("balance with red-child right-left violation") {
    auto y = new Node('y', nullptr, nullptr, Color::Red);
    auto z = new Node('z', y, nullptr, Color::Red);
    auto x = new Node('x', nullptr, z, Color::Black);

    auto root = PseudoSetTester::balance(x);

    REQUIRE_NE(root, nullptr);
    CHECK_EQ(root->value, 'y');
    CHECK_EQ(root->color, Color::Red);

    REQUIRE_NE(root->left, nullptr);
    CHECK_EQ(root->left->value, 'x');
    CHECK_EQ(root->left->color, Color::Black);
    CHECK_EQ(root->left->left, nullptr);
    CHECK_EQ(root->left->right, nullptr);

    REQUIRE_NE(root->right, nullptr);
    CHECK_EQ(root->right->value, 'z');
    CHECK_EQ(root->right->color, Color::Black);
    CHECK_EQ(root->right->left, nullptr);
    CHECK_EQ(root->right->right, nullptr);

    delete root->left;
    delete root->right;
    delete root;
}

TEST_CASE("balance with red-child right-right violation") {
    auto z = new Node('z', nullptr, nullptr, Color::Red);
    auto y = new Node('y', nullptr, z, Color::Red);
    auto x = new Node('x', nullptr, y, Color::Black);

    auto root = PseudoSetTester::balance(x);

    REQUIRE_NE(root, nullptr);
    CHECK_EQ(root->value, 'y');
    CHECK_EQ(root->color, Color::Red);

    REQUIRE_NE(root->left, nullptr);
    CHECK_EQ(root->left->value, 'x');
    CHECK_EQ(root->left->color, Color::Black);
    CHECK_EQ(root->left->left, nullptr);
    CHECK_EQ(root->left->right, nullptr);

    REQUIRE_NE(root->right, nullptr);
    CHECK_EQ(root->right->value, 'z');
    CHECK_EQ(root->right->color, Color::Black);
    CHECK_EQ(root->right->left, nullptr);
    CHECK_EQ(root->right->right, nullptr);

    delete root->left;
    delete root->right;
    delete root;
}

TEST_CASE("insert") {
    Node *root = nullptr;
    std::vector<int> elems(1000);
    std::iota(elems.begin(), elems.end(), 1);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(elems.begin(), elems.end(), g);

    std::unordered_set<int> expected;

    for (auto val : elems) {
        root = PseudoSetTester::insert(root, val);
        root->color = Color::Black;
        expected.insert(val);

        CHECK(validate(root));
        CHECK(tree_equals_set(root, expected));
    }

    PseudoSetTester::destroy(root);
}

TEST_CASE("find on empty tree") {
    Node *root = nullptr;
    CHECK_EQ(PseudoSetTester::find(root, 42), nullptr);
    CHECK_EQ(PseudoSetTester::find(root, 0), nullptr);
}

TEST_CASE("find on a tree") {
    auto n1 = new Node(1);
    auto n3 = new Node(3);
    auto n2 = new Node(2, n1, n3, Color::Black);

    auto n5 = new Node(5);
    auto n7 = new Node(7);
    auto n6 = new Node(6, n5, n7, Color::Black);

    auto root = new Node(4, n2, n6, Color::Black);

    CHECK_EQ(PseudoSetTester::find(root, 4), root);

    CHECK_EQ(PseudoSetTester::find(root, 2), n2);
    CHECK_EQ(PseudoSetTester::find(root, 6), n6);

    CHECK_EQ(PseudoSetTester::find(root, 1), n1);
    CHECK_EQ(PseudoSetTester::find(root, 3), n3);
    CHECK_EQ(PseudoSetTester::find(root, 5), n5);
    CHECK_EQ(PseudoSetTester::find(root, 7), n7);

    CHECK_EQ(PseudoSetTester::find(root, 0), nullptr);
    CHECK_EQ(PseudoSetTester::find(root, 8), nullptr);
    CHECK_EQ(PseudoSetTester::find(root, 9), nullptr);

    CHECK_NE(PseudoSetTester::find(root, 4), nullptr);
    CHECK_NE(PseudoSetTester::find(root, 1), nullptr);
    CHECK_NE(PseudoSetTester::find(root, 7), nullptr);

    delete n1;
    delete n3;
    delete n2;
    delete n5;
    delete n7;
    delete n6;
    delete root;
}

TEST_CASE("empty set") {
    PseudoSet s;
    std::set<int> ref;

    CHECK_EQ(s.size(), ref.size());
    for (int i = -10; i <= 10; ++i) CHECK_EQ(s.contains(i), ref.count(i) != 0);
}

TEST_CASE("insert single element") {
    PseudoSet s;
    std::set<int> ref;

    s.insert(42);
    ref.insert(42);

    CHECK_EQ(s.size(), ref.size());
    CHECK_EQ(s.contains(42), ref.count(42) != 0);
}

TEST_CASE("insert multiple unique elements") {
    PseudoSet s;
    std::set<int> ref;

    std::vector<int> values = {5, 2, 8, 1, 3, 7, 9};
    for (int v : values) {
        s.insert(v);
        ref.insert(v);
    }

    CHECK_EQ(s.size(), ref.size());
    for (int v : values) CHECK_EQ(s.contains(v), ref.count(v) != 0);

    for (int i = -2; i <= 10; ++i) CHECK_EQ(s.contains(i), ref.count(i) != 0);
}

TEST_CASE("insert duplicates (no effect)") {
    PseudoSet s;
    std::set<int> ref;

    std::vector<int> values = {1, 1, 1, 2, 2, 3};
    for (int v : values) {
        s.insert(v);
        ref.insert(v);
    }

    CHECK_EQ(s.size(), ref.size());
    for (int i = 0; i <= 4; ++i) CHECK_EQ(s.contains(i), ref.count(i) != 0);
}

TEST_CASE("insert many elements and check containment") {
    PseudoSet s;
    std::set<int> ref;

    for (int i = 0; i <= 20; i += 2) {
        s.insert(i);
        ref.insert(i);
    }

    CHECK_EQ(s.size(), ref.size());

    for (int i = 0; i <= 20; ++i) CHECK_EQ(s.contains(i), ref.count(i) != 0);
}

TEST_CASE("check non-inserted elements") {
    PseudoSet s;
    std::set<int> ref;

    s.insert(10);
    s.insert(20);
    ref.insert(10);
    ref.insert(20);

    for (int i = 0; i <= 25; ++i) {
        bool expected = ref.count(i) != 0;
        CHECK_EQ(s.contains(i), expected);
    }
}

TEST_CASE("stress test: randomized inserts with full verification") {
    PseudoSet s;
    std::set<int> ref;

    std::vector<int> values(1000);
    std::iota(values.begin(), values.end(), 1);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(values.begin(), values.end(), g);

    for (size_t i = 0; i < values.size(); ++i) {
        int val = values[i];
        s.insert(val);
        ref.insert(val);

        CHECK_EQ(s.size(), ref.size());

        // Check all inserted values are present
        for (int inserted : ref) {
            CHECK(s.contains(inserted));
        }

        // Check all non-inserted values are absent
        for (int j = 1; j <= 1000; ++j) {
            if (ref.count(j) == 0) CHECK(!s.contains(j));
        }
    }
}
