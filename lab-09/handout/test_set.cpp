#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "set.h"
#include <set>
#include <algorithm>
#include <random>
#include <numeric>

class SetTester {
public:
    using Node = Set::Node;

    [[nodiscard]] static Node *insert(Node *root, int value) { return Set::insert(root, value); }
    [[nodiscard]] static Node *erase(Node *root, int value) { return Set::erase(root, value); }
    [[nodiscard]] static const Node *find(const Node *root, int value) { return Set::find(root, value); }
};

using Node = SetTester::Node;

static bool is_same(const Node *a, const Node *b) {
    if (a == nullptr && b == nullptr) return true;
    if (a == nullptr || b == nullptr) return false;
    if (a->value != b->value) return false;
    return is_same(a->left, b->left) && is_same(a->right, b->right);
}

static Node *clone(const Node *src) {
    if (!src) return nullptr;
    return new Node(src->value, clone(src->left), clone(src->right));
}

static void destroy(Node *root) {
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

TEST_CASE("insert into empty tree") {
    auto root = SetTester::insert(nullptr, 0);
    auto expected = new Node(0);
    REQUIRE(is_same(root, expected));
    destroy(expected);
    destroy(root);
}

TEST_CASE("insert into single node tree") {
    auto root = new Node(0);

    root = SetTester::insert(root, 1); {
        auto expected = new Node(0, nullptr, new Node(1));
        REQUIRE(is_same(root, expected));
        destroy(expected);
    }

    root = SetTester::insert(root, -1); {
        auto expected = new Node(0, new Node(-1), new Node(1));
        REQUIRE(is_same(root, expected));
        destroy(expected);
    }

    destroy(root);
}

TEST_CASE("insert duplicate") {
    auto root = new Node(0);
    root = SetTester::insert(root, 0);
    auto expected = new Node(0);
    REQUIRE(is_same(root, expected));
    destroy(expected);
    destroy(root);
}

TEST_CASE("insert into tree") {
    auto root = new Node(3, new Node(1), new Node(5, nullptr, new Node(7)));

    root = SetTester::insert(root, 0); {
        auto expected = new Node(3,
                                 new Node(1, new Node(0), nullptr),
                                 new Node(5, nullptr, new Node(7)));
        REQUIRE(is_same(root, expected));
        destroy(expected);
    }

    root = SetTester::insert(root, 4); {
        auto expected = new Node(3,
                                 new Node(1, new Node(0), nullptr),
                                 new Node(5, new Node(4), new Node(7)));
        REQUIRE(is_same(root, expected));
        destroy(expected);
    }

    root = SetTester::insert(root, 8); {
        auto expected = new Node(3,
                                 new Node(1, new Node(0), nullptr),
                                 new Node(5, new Node(4), new Node(7, nullptr, new Node(8))));
        REQUIRE(is_same(root, expected));
        destroy(expected);
    }

    destroy(root);
}

TEST_CASE("erase from empty tree") {
    auto root = SetTester::erase(nullptr, 5);
    CHECK_EQ(root, nullptr);
}

TEST_CASE("erase from single node tree") {
    auto root = new Node(5);
    root = SetTester::erase(root, 5);
    CHECK_EQ(root, nullptr);
}

TEST_CASE("erase from tree") {
    auto root = new Node(4,
                         new Node(2, new Node(1), new Node(3)),
                         new Node(6, nullptr, new Node(7)));

    root = SetTester::erase(root, 3); {
        auto expected = new Node(4,
                                 new Node(2, new Node(1), nullptr),
                                 new Node(6, nullptr, new Node(7)));
        REQUIRE(is_same(root, expected));
        destroy(expected);
    }

    root = SetTester::erase(root, 6); {
        auto expected = new Node(4,
                                 new Node(2, new Node(1), nullptr),
                                 new Node(7));
        REQUIRE(is_same(root, expected));
        destroy(expected);
    }

    root = SetTester::erase(root, 4);
    auto expectedA = new Node(2, new Node(1), new Node(7));
    auto expectedB = new Node(7, new Node(2, new Node(1), nullptr), nullptr);
    auto same = is_same(root, expectedA) || is_same(root, expectedB);
    REQUIRE(same);

    destroy(expectedA);
    destroy(expectedB);
    destroy(root);
}

TEST_CASE("erase duplicate") {
    auto root = new Node(10);
    root = SetTester::erase(root, 20);
    auto expected = new Node(10);
    REQUIRE(is_same(root, expected));
    destroy(expected);
    destroy(root);
}

TEST_CASE("find in empty tree") {
    auto result = SetTester::find(nullptr, 42);
    CHECK_EQ(result, nullptr);
}

TEST_CASE("find in single node tree") {
    auto root = new Node(5);
    auto snapshot = clone(root);

    const Node *r1 = SetTester::find(root, 5);
    REQUIRE_NE(r1, nullptr);
    CHECK_EQ(r1->value, 5);
    REQUIRE(is_same(root, snapshot));

    const Node *r2 = SetTester::find(root, 6);
    CHECK_EQ(r2, nullptr);
    REQUIRE(is_same(root, snapshot));

    destroy(snapshot);
    destroy(root);
}

TEST_CASE("find in tree (exists)") {
    auto root = new Node(4,
                         new Node(2, new Node(1), new Node(3)),
                         new Node(6, new Node(5), new Node(7)));
    auto snapshot = clone(root);

    const Node *r1 = SetTester::find(root, 1);
    REQUIRE_NE(r1, nullptr);
    CHECK_EQ(r1->value, 1);
    REQUIRE(is_same(root, snapshot));

    const Node *r2 = SetTester::find(root, 5);
    REQUIRE_NE(r2, nullptr);
    CHECK_EQ(r2->value, 5);
    REQUIRE(is_same(root, snapshot));

    const Node *r3 = SetTester::find(root, 7);
    REQUIRE_NE(r3, nullptr);
    CHECK_EQ(r3->value, 7);
    REQUIRE(is_same(root, snapshot));

    destroy(snapshot);
    destroy(root);
}

TEST_CASE("find in tree (does not exist)") {
    auto root = new Node(4,
                         new Node(2, new Node(1), new Node(3)),
                         new Node(6, new Node(5), new Node(7)));
    auto snapshot = clone(root);

    CHECK_EQ(SetTester::find(root, 0), nullptr);
    REQUIRE(is_same(root, snapshot));

    CHECK_EQ(SetTester::find(root, 8), nullptr);
    REQUIRE(is_same(root, snapshot));

    CHECK_EQ(SetTester::find(root, 9), nullptr);
    REQUIRE(is_same(root, snapshot));

    destroy(snapshot);
    destroy(root);
}

TEST_CASE("empty set") {
    Set s;
    std::set<int> ref;

    CHECK_EQ(s.size(), ref.size());
    for (int i = -10; i <= 10; ++i)
        CHECK_EQ(s.contains(i), ref.count(i) != 0);
}

TEST_CASE("insert single element") {
    Set s;
    std::set<int> ref;

    s.insert(42);
    ref.insert(42);

    CHECK_EQ(s.size(), ref.size());
    CHECK_EQ(s.contains(42), ref.count(42) != 0);
}

TEST_CASE("insert multiple unique elements") {
    Set s;
    std::set<int> ref;

    std::vector<int> values = {5, 2, 8, 1, 3, 7, 9};
    for (int v: values) {
        s.insert(v);
        ref.insert(v);
    }

    CHECK_EQ(s.size(), ref.size());
    for (int v: values)
        CHECK_EQ(s.contains(v), ref.count(v) != 0);

    for (int i = -2; i <= 10; ++i)
        CHECK_EQ(s.contains(i), ref.count(i) != 0);
}

TEST_CASE("insert duplicates (no effect)") {
    Set s;
    std::set<int> ref;

    std::vector<int> values = {1, 1, 1, 2, 2, 3};
    for (int v: values) {
        s.insert(v);
        ref.insert(v);
    }

    CHECK_EQ(s.size(), ref.size());
    for (int i = 0; i <= 4; ++i)
        CHECK_EQ(s.contains(i), ref.count(i) != 0);
}

TEST_CASE("erase elements") {
    Set s;
    std::set<int> ref;

    std::vector<int> values = {5, 2, 8, 1, 3, 7, 9};
    for (int v: values) {
        s.insert(v);
        ref.insert(v);
    }

    std::vector<int> toErase = {3, 8, 1};
    for (int v: toErase) {
        s.erase(v);
        ref.erase(v);
    }

    CHECK_EQ(s.size(), ref.size());
    for (int i = 0; i <= 10; ++i)
        CHECK_EQ(s.contains(i), ref.count(i) != 0);
}

TEST_CASE("erase non-existing elements (no effect)") {
    Set s;
    std::set<int> ref;

    std::vector<int> values = {10, 20, 30};
    for (int v: values) {
        s.insert(v);
        ref.insert(v);
    }

    std::vector<int> toErase = {5, 15, 25, 35};
    for (int v: toErase) {
        s.erase(v);
        ref.erase(v);
    }

    CHECK_EQ(s.size(), ref.size());
    for (int i = 0; i <= 40; i += 5)
        CHECK_EQ(s.contains(i), ref.count(i) != 0);
}

TEST_CASE("randomized insert/erase consistency") {
    Set s;
    std::set<int> ref;
    std::vector<int> values(100);
    std::iota(values.begin(), values.end(), 0);

    std::mt19937 rng(12345);
    std::shuffle(values.begin(), values.end(), rng);

    for (int v: values) {
        s.insert(v);
        ref.insert(v);
    }

    CHECK_EQ(s.size(), ref.size());
    for (int v: values)
        CHECK_EQ(s.contains(v), ref.count(v) != 0);

    std::shuffle(values.begin(), values.end(), rng);
    for (int i = 0; i < 50; ++i) {
        s.erase(values[i]);
        ref.erase(values[i]);
    }

    CHECK_EQ(s.size(), ref.size());
    for (int v = 0; v < 100; ++v)
        CHECK_EQ(s.contains(v), ref.count(v) != 0);
}

TEST_CASE("interleaved insert/erase operations") {
    Set s;
    std::set<int> ref;

    for (int i = 0; i < 50; ++i) {
        if (i % 3 == 0) {
            s.insert(i);
            ref.insert(i);
        } else {
            s.erase(i - 1);
            ref.erase(i - 1);
        }
        CHECK_EQ(s.size(), ref.size());
        for (int j = 0; j < 50; ++j)
            CHECK_EQ(s.contains(j), ref.count(j) != 0);
    }
}

TEST_CASE("erase all elements to size 0 and reinsert") {
    Set s;
    std::set<int> ref;

    std::vector<int> values = {5, 3, 7, 2, 4, 6, 8};
    for (int v: values) {
        s.insert(v);
        ref.insert(v);
    }

    CHECK_EQ(s.size(), ref.size());

    for (int v: values) {
        s.erase(v);
        ref.erase(v);
        CHECK_EQ(s.size(), ref.size());
    }

    CHECK_EQ(s.size(), 0);
    CHECK_EQ(ref.size(), 0);

    for (int i = -3; i <= 3; ++i) {
        s.insert(i);
        ref.insert(i);
        CHECK_EQ(s.size(), ref.size());
        for (int j = -3; j <= 3; ++j)
            CHECK_EQ(s.contains(j), ref.count(j) != 0);
    }

    CHECK_EQ(s.size(), ref.size());
}
