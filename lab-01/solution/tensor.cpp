#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>
#include <vector>

class Tensor {
private:
    // TODO: You can use `int*`, `void*` or `Tensor*` as the type of `m_data`. Use whichever option you prefer.
    int* m_data;
    std::vector<int> m_shape;
    std::vector<int> m_perm;
    std::vector<int> m_inv_perm;

    std::vector<int> permute(std::vector<int> v, std::vector<int> perm) {
        std::vector<int> pv(v.size());
        for (size_t i = 0; i < v.size(); ++i) {
            pv[i] = v[perm[i]];
        }
        return pv;
    }

    int& at(const std::vector<int>& idx) {
        int j = 0;
        int stride = 1;
        for (size_t i = idx.size() - 1; i < idx.size(); --i) {
            j += idx[i] * stride;
            stride *= m_shape[i];
        }
        return m_data[j];
    }

public:
    Tensor(std::vector<int> shape, int default_value) {
        // TODO: Initialize the member variables of the `Tensor` object.
        int size = 1;
        for (size_t i = 0; i < shape.size(); ++i) {
            size *= shape[i];
        }
        m_data = new int[size];

        for (int i = 0; i < size; ++i) {
            m_data[i] = default_value;
        }

        m_shape = shape;
        for (int i = 0; i < static_cast<int>(shape.size()); ++i) {
            m_perm.push_back(i);
            m_inv_perm.push_back(i);
        }

    }

    ~Tensor() {
        // TODO: Deallocate any dynamically allocated memory.
        delete[] m_data;
    }

    // C++ magic. Feel free to ignore these two lines, or ask a staff member if you are curious.
    Tensor(const Tensor&) = delete;
    Tensor& operator=(const Tensor&) = delete;

    int get(std::vector<int> idx) {
        // TODO: Return the element at index `(idx[0], idx[1], ...)` in the tensor. If any component of `idx` is
        // out-of-bounds, throw an `std::out_of_range` exception. If `idx` is the wrong length, throw an
        // `std::invalid_argument` exception.
        if (idx.size() != m_shape.size()) {
            throw std::invalid_argument("incorrect dimension count");
        }
        idx = permute(idx, m_inv_perm);
        for (size_t i = 0; i < m_shape.size(); ++i) {
            if (idx[i] < 0 || idx[i] >= m_shape[i]) {
                throw std::out_of_range("index out-of-bounds");
            }
        }

        return at(idx);
    }

    void set(std::vector<int> idx, int value) {
        // TODO: Set the element at index `(idx[0], idx[1], ...)` in the tensor to `value`. If any component of `idx` is
        // out-of-bounds, throw an `std::out_of_range` exception. If `idx` is the wrong length, throw an
        // `std::invalid_argument` exception.
        if (idx.size() != m_shape.size()) {
            throw std::invalid_argument("incorrect dimension count");
        }
        idx = permute(idx, m_inv_perm);
        for (size_t i = 0; i < m_shape.size(); ++i) {
            if (idx[i] < 0 || idx[i] >= m_shape[i]) {
                throw std::out_of_range("index out-of-bounds");
            }
        }

        at(idx) = value;
    }

    void permute_dims(std::vector<int> dims) {
        // TODO: Permute the order of the tensor dimensions. If `B` is the tensor before the permutation and `A` is the
        // tensor after the permutation, then we should have
        // `A[idx[0], idx[1], ...] = B[idx[dims[0]], idx[dims[1]], ...]`. If the permutation is invalid, throw an
        // `std::invalid_argument` exception.
        std::vector<int> count(m_shape.size());
        for (size_t i = 0; i < dims.size(); ++i) {
            if (dims[i] < 0 || static_cast<size_t>(dims[i]) >= m_shape.size()) {
                throw std::invalid_argument("permutation dimension out-of-bounds");
            }
            count[dims[i]] += 1;
        }

        for (size_t i = 0; i < count.size(); ++i) {
            if (count[i] != 1) {
                throw std::invalid_argument("missing or repeated dimension");
            }
        }

        m_perm = permute(m_perm, dims);
        for (size_t i = 0; i < m_inv_perm.size(); ++i) {
            m_inv_perm[m_perm[i]] = i;
        }
    }

    std::vector<int> shape() {
        // TODO: Return the shape of the tensor.
        return permute(m_shape, m_perm);
    }
};

TEST_CASE("Tensor initializes with default value") {
    std::vector<int> shape = {2, 3};
    Tensor t(shape, 7);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            REQUIRE(t.get({i, j}) == 7);
}

TEST_CASE("Tensor set and get work correctly") {
    std::vector<int> shape = {2, 2};
    Tensor t(shape, 0);

    t.set({0, 0}, 10);
    t.set({1, 1}, 20);

    REQUIRE(t.get({0, 0}) == 10);
    REQUIRE(t.get({1, 1}) == 20);
    REQUIRE(t.get({0, 1}) == 0);
    REQUIRE(t.get({1, 0}) == 0);
}

TEST_CASE("Tensor throws on get out-of-bounds") {
    std::vector<int> shape = {2, 2};
    Tensor t(shape, 0);

    REQUIRE_THROWS_AS(t.get({-1, 0}), std::out_of_range);
    REQUIRE_THROWS_AS(t.get({0, -1}), std::out_of_range);
    REQUIRE_THROWS_AS(t.get({2, 0}), std::out_of_range);
    REQUIRE_THROWS_AS(t.get({0, 2}), std::out_of_range);
}

TEST_CASE("Tensor throws on get with wrong index length") {
    std::vector<int> shape = {2, 2};
    Tensor t(shape, 0);

    REQUIRE_THROWS_AS(t.get({0}), std::invalid_argument);
    REQUIRE_THROWS_AS(t.get({0, 1, 2}), std::invalid_argument);
}

TEST_CASE("Tensor throws on set out-of-bounds") {
    std::vector<int> shape = {2, 2};
    Tensor t(shape, 0);

    REQUIRE_THROWS_AS(t.set({-1, 0}, 1), std::out_of_range);
    REQUIRE_THROWS_AS(t.set({0, -1}, 1), std::out_of_range);
    REQUIRE_THROWS_AS(t.set({2, 0}, 1), std::out_of_range);
    REQUIRE_THROWS_AS(t.set({0, 2}, 1), std::out_of_range);
}

TEST_CASE("Tensor throws on set with wrong index length") {
    std::vector<int> shape = {2, 2};
    Tensor t(shape, 0);

    REQUIRE_THROWS_AS(t.set({0}, 1), std::invalid_argument);
    REQUIRE_THROWS_AS(t.set({0, 1, 2}, 1), std::invalid_argument);
}

TEST_CASE("Tensor permute_dims swaps 2D matrix") {
    std::vector<int> shape = {2, 3};
    Tensor t(shape, 0);

    int val = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            t.set({i, j}, val++);

    t.permute_dims({1, 0}); // transpose

    std::vector<int> s = t.shape();
    REQUIRE(s[0] == 3);
    REQUIRE(s[1] == 2);

    val = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            REQUIRE(t.get({j, i}) == val++);
}

TEST_CASE("Tensor permute_dims invalid permutation throws") {
    std::vector<int> shape = {2, 2};
    Tensor t(shape, 0);

    REQUIRE_THROWS_AS(t.permute_dims({0, 0}), std::invalid_argument);
    REQUIRE_THROWS_AS(t.permute_dims({1, 1}), std::invalid_argument);
    REQUIRE_THROWS_AS(t.permute_dims({0, 1, 2}), std::invalid_argument);
}

TEST_CASE("Tensor 3D get/set works correctly") {
    std::vector<int> shape = {2, 3, 4};
    Tensor t(shape, 0);

    int val = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 4; k++)
                t.set({i, j, k}, val++);

    val = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 4; k++)
                REQUIRE(t.get({i, j, k}) == val++);
}

TEST_CASE("Tensor 3D permute_dims") {
    std::vector<int> shape = {2, 3, 4};
    Tensor t(shape, 0);

    int val = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 4; k++)
                t.set({i, j, k}, val++);

    t.permute_dims({2, 0, 1}); // new shape should be {4,2,3}
    std::vector<int> s = t.shape();
    REQUIRE(s[0] == 4);
    REQUIRE(s[1] == 2);
    REQUIRE(s[2] == 3);

    val = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 4; k++)
                REQUIRE(t.get({k, i, j}) == val++);
}

TEST_CASE("Tensor 4D get/set works correctly") {
    std::vector<int> shape = {2, 2, 3, 2};
    Tensor t(shape, 0);

    int val = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 2; l++)
                    t.set({i, j, k, l}, val++);

    val = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 2; l++)
                    REQUIRE(t.get({i, j, k, l}) == val++);
}

TEST_CASE("Tensor 4D permute_dims") {
    std::vector<int> shape = {2, 2, 3, 2};
    Tensor t(shape, 0);

    int val = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 2; l++)
                    t.set({i, j, k, l}, val++);

    t.permute_dims({3, 2, 0, 1}); // new shape should be {2,3,2,2}
    std::vector<int> s = t.shape();
    REQUIRE(s[0] == 2);
    REQUIRE(s[1] == 3);
    REQUIRE(s[2] == 2);
    REQUIRE(s[3] == 2);

    val = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 2; l++)
                    REQUIRE(t.get({l, k, i, j}) == val++);
}