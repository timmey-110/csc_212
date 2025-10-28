#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>

class Matrix {
private:
    // TODO: You can use `int**`, `int*`, `Array*` or `Array` as the type of `m_data`. Use whichever option you prefer.
    // NOTE: If you use `Array*` or `Array`, note that `Array` does not support the `=` operator, so you will need to 
    // use `get` and `set` to copy elements to and from `Array`.
    int** m_data;
    int m_rows;
    int m_cols;

public:
    Matrix(int rows, int cols, int default_value) {
        // TODO: Initialize the member variables of the `Matrix` object. After dynamically allocating `m_data`, fill it 
        // with `default_value`.
        m_data = new int*[rows];
        for (int row = 0; row < rows; ++row) {
            m_data[row] = new int[cols];
            for (int col = 0; col < cols; ++col) {
                m_data[row][col] = default_value;
            }
        }
        m_rows = rows;
        m_cols = cols;
    }
    
    ~Matrix() {
        // TODO: Deallocate any dynamically allocated memory.
        for (int row = 0; row < m_rows; ++row) {
            delete[] m_data[row];
        }
        delete[] m_data;
    }
    
    // C++ magic. Feel free to ignore these two lines, or ask a staff member if you are curious.
    Matrix(const Matrix&) = delete;
    Matrix& operator=(const Matrix&) = delete;
    
    int get(int row, int col) {
        // TODO: Return the element at row `row` and column `col` in the matrix. If either `row` or `col` is 
        // out-of-bounds, throw an `std::out_of_range` exception.
        if (row < 0 || col < 0 || row >= m_rows || col >= m_cols) {
            throw std::out_of_range("get with out-of-bounds row or col");
        }
        return m_data[row][col];
    }
    
    void set(int row, int col, int value) {
        // TODO: Set the element at row `row` and column `col` in the matrix to `value`. If either `row` or `col` is 
        // out-of-bounds, throw an `std::out_of_range` exception.
        if (row < 0 || col < 0 || row >= m_rows || col >= m_cols) {
            throw std::out_of_range("set with out-of-bounds row or col");
        }
        m_data[row][col] = value;
    }
    
    void permute_dims(int dim0, int dim1) {
        // TODO: Permute the order of the matrix dimensions. If `dim0 == 0` and `dim1 == 1`, do nothing. If `dim0 == 1`
        // and `dim1 == 0`, exchange the rows and columns of the matrix. If `B` is the matrix before the permutation and
        // `A` is the matrix after the permutation, then we should have `A[row][col] = B[col][row]`. This is the same as
        // transposing the matrix. In all other cases, throw an `std::invalid_argument` exception.
        if ((dim0 != 0 && dim0 != 1) || (dim1 != 0 && dim1 != 1) || dim0 + dim1 != 1) {
            throw std::invalid_argument("invalid permutation dimensions");
        }

        if (dim0 == 0 && dim1 == 1) {
            return;
        }

        int new_rows = m_cols;
        int new_cols = m_rows;
        int ** new_data = new int*[m_cols];
        for (int row = 0; row < new_rows; ++row) {
            new_data[row] = new int[new_cols];
        }

        for (int row = 0; row < m_rows; ++row) {
            for (int col = 0; col < m_cols; ++col) {
                new_data[col][row] = m_data[row][col];
            }
        }

        for (int row = 0; row < m_rows; ++row) {
            delete[] m_data[row];
        }
        delete[] m_data;

        m_data = new_data;
        m_rows = new_rows;
        m_cols = new_cols;
    }
    
    int rows() {
        // TODO: Return the number of rows in the matrix.
        return m_rows;
    }
    
    int cols() {
        // TODO: Return the number of columns in the matrix.
        return m_cols;
    }
};

TEST_CASE("Matrix initializes with default value") {
    Matrix mat(2, 3, 5);

    REQUIRE(mat.rows() == 2);
    REQUIRE(mat.cols() == 3);

    for (int r = 0; r < mat.rows(); ++r)
        for (int c = 0; c < mat.cols(); ++c)
            REQUIRE(mat.get(r, c) == 5);
}

TEST_CASE("Matrix set and get work correctly") {
    Matrix mat(2, 2, 0);
    mat.set(0, 0, 10);
    mat.set(1, 1, 20);

    REQUIRE(mat.get(0, 0) == 10);
    REQUIRE(mat.get(1, 1) == 20);
    REQUIRE(mat.get(0, 1) == 0);
    REQUIRE(mat.get(1, 0) == 0);
}

TEST_CASE("Matrix permute_dims swaps rows and columns") {
    Matrix mat(2, 3, 0);

    // Set values to identify positions
    int val = 1;
    for (int r = 0; r < mat.rows(); ++r)
        for (int c = 0; c < mat.cols(); ++c)
            mat.set(r, c, val++);

    mat.permute_dims(1, 0);

    REQUIRE(mat.rows() == 3);
    REQUIRE(mat.cols() == 2);

    // After transpose, mat[row][col] == original mat[col][row]
    val = 1;
    for (int r = 0; r < 2; ++r)
        for (int c = 0; c < 3; ++c)
            REQUIRE(mat.get(c, r) == val++);
}

TEST_CASE("Matrix permute_dims with identity does nothing") {
    Matrix mat(2, 2, 7);
    mat.permute_dims(0, 1);

    REQUIRE(mat.rows() == 2);
    REQUIRE(mat.cols() == 2);
    for (int r = 0; r < 2; ++r)
        for (int c = 0; c < 2; ++c)
            REQUIRE(mat.get(r, c) == 7);
}

TEST_CASE("Matrix permute_dims invalid arguments throw") {
    Matrix mat(2, 2, 0);
    REQUIRE_THROWS_AS(mat.permute_dims(0, 0), std::invalid_argument);
    REQUIRE_THROWS_AS(mat.permute_dims(1, 1), std::invalid_argument);
    REQUIRE_THROWS_AS(mat.permute_dims(0, 2), std::invalid_argument);
    REQUIRE_THROWS_AS(mat.permute_dims(2, 1), std::invalid_argument);
}

TEST_CASE("Matrix throws on get/set out-of-bounds") {
    Matrix mat(2, 3, 0);
    REQUIRE_THROWS_AS(mat.get(-1, 0), std::out_of_range);
    REQUIRE_THROWS_AS(mat.get(0, -1), std::out_of_range);
    REQUIRE_THROWS_AS(mat.get(2, 0), std::out_of_range);
    REQUIRE_THROWS_AS(mat.get(0, 3), std::out_of_range);

    REQUIRE_THROWS_AS(mat.set(-1, 0, 1), std::out_of_range);
    REQUIRE_THROWS_AS(mat.set(0, -1, 1), std::out_of_range);
    REQUIRE_THROWS_AS(mat.set(2, 0, 1), std::out_of_range);
    REQUIRE_THROWS_AS(mat.set(0, 3, 1), std::out_of_range);
}