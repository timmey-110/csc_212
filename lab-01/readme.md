# Lab 1 - C++ Review and The Debugger

# Overview

In this lab, we will review key C++ concepts from CSC 211, including **pointers**, **C-style arrays**, **dynamic memory 
allocation** and **classes**. Additionally, we will learn to use the **debugger**, a powerful tool that allows you to 
pause a program's execution and inspect variable values. 

## Learning Objectives

By the end of this lab, you should be able to:
1. Write C++ programs using pointers and C-style arrays
2. Allocate and deallocate memory in C++
3. Model fixed length data structures (including arrays, matrices and tensors) with classes.
4. Step through C++ code using a debugger

If you are not yet confident with one or more of these skills after completing the lab, ask a staff member for help. We 
can adjust the lab to address common difficulties and help you get back on track. Your success is our top priority!

## Grading

Full credit for this lab requires **attendance**, **collaboration with your group**, and **active participation**. 
Gradescope will provide a score out of 100, but this is not your lab grade. It’s feedback for you (and for us) about 
your progress. If you aren't happy with your score, please reach out to a staff member for assistance!

> [!IMPORTANT]
> Complete the exercises you believe will be most valuable for your learning first! If you already know how to complete
> an exercise, or you have no idea how to start, feel free to skip it. If you aren't sure, attempt the exercises in 
> order. We do not expect anyone to finish all exercises, but please try to surprise us!

You may leave early if you can demonstrate you have met the learning objectives to a staff member. For example, if you 
have completed the debugging activity `debug.cpp` (meeting objective 4), the tensor data structure `tensor.cpp` 
(meeting objectives 1, 2 and 3), and can clearly explain your code, a staff member may allow you to leave early. If you 
need to leave early for another reason, please talk to a staff member.

### Code that Works Locally but Fails in Gradescope

Gradescope runs your code with additional strict checks for compiler warnings, errors, and runtime memory violations. If
your code works locally, but fails on Gradescope, your code doesn't always work. You should try to fix the errors shown 
in the Gradescope output.

## Setup

We assume you have an IDE with a working 
1. Compiler (ideally `g++`)
2. Debugger
3. Formatter 

If you are unsure or are missing any of these features, please ask a group or staff member for help. We will check in
during the lab to confirm your IDE supports all these features.

> [!WARNING]
> For this lab, avoid using large language models (LLMs) like Copilot and ChatGPT when solving the programming 
> exercises. LLMs might limit your learning. If you have Copilot in your IDE, we suggest disabling it. 
> 
> However, we do recommend using LLMs to understand your IDE's and the debugger's capabilities.

### Unittests

This lab (and future labs) includes autograder test cases, also called unit tests. Unit tests are small programs that 
automatically check whether your code works correctly. They test individual parts of your program (like a function or 
class) to make sure each piece behaves as expected.

The tests in this lab use **Catch2**, a C++ testing framework. To use it, download [catch.hpp](catch.hpp) from the lab 
folder on GitHub and place it in the same directory as your program files.

You can run the tests locally to check your progress before submitting. Even after the Gradescope assignment has closed,
you can continue to work on the lab and still receive feedback by running the tests.

When you build and run the test executable, Catch2 will report which tests pass and which fail. If a test fails, it will
tell you exactly which part of your code needs fixing.

### Building Code with CLion

When working in CLion, create a new project for each lab or assignment.

For each project, you might need to build multiple programs. CLion uses **CMake**, an industry standard tool for
managing builds. To build and debug multiple programs in CLion, you will need to edit the `CMakeLists.txt` file. 

For example, if this lab includes two programs, `step.cpp` and `debug.cpp`, your `CMakeLists.txt` could look like this:

```cmake
cmake_minimum_required(VERSION 3.10)
project(csc212-lab-01)

set(CMAKE_CXX_STANDARD 17)

add_executable(step step.cpp)
add_executable(debug debug.cpp)
```

After editing `CMakeLists.txt`, click **"Reload CMake Project"** in CLion so the changes take effect.

Once reloaded, you can build and run either `step` or `debug` by selecting the desired target from CLion's run/debug 
configuration dropdown.

For additional guidance, see the [CLion CMake tutorial](https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html).

# Debugging

See [these instructions and exercises](debug.md) on debugging.

# Pointers

### Exercise `pointers.cpp`

1. Create a new file called `pointers.cpp` and copy the following program into it:
```cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstdint>

int get_pointed_value(int* pointer) {
    // TODO: Return the value pointed to by `pointer`.
}

void set_pointed_value(int* pointer, int value) {
    // TODO: Set the value pointed to by `pointer` to `value`.
}

uintptr_t get_pointer_address(int* pointer) {
    // TODO: Return the memory address of the value pointed to by `pointer`.
}

TEST_CASE("get_pointed_value returns value stored at pointer") {
    int x = 99;
    int* p = &x;

    REQUIRE(get_pointed_value(p) == 99);
}

TEST_CASE("set_pointed_value modifies the value at pointer") {
    int x = 0;
    int* p = &x;

    set_pointed_value(p, 123);

    REQUIRE(x == 123);
    REQUIRE(get_pointed_value(p) == 123);
}

TEST_CASE("get_pointer_address returns correct address") {
    int x = 42;
    int* p = &x;
    
    uintptr_t addr = get_pointer_address(p);
    
    REQUIRE(reinterpret_cast<int*>(addr) == p);
}
```
2. Complete the TODOs in each function.
3. Make sure the program compiles and runs without errors, and that all tests pass.

> [!IMPORTANT]
> You should submit `pointers.cpp` to Gradescope.

# C-Style Arrays

### Exercise `cstyle_arrays.cpp`

1. Create a new file called `cstyle_arrays.cpp` and copy the following program into it:
```cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <ostream>

void print_array(int* array, int n, std::ostream& os) {
    // TODO: Print each element of `array` to `os` separated by spaces. Do not include a trailing space.
    // NOTE: To print to `os` use the << operator. For example, `os << 5;` prints `5` to `os`. 
}

void print_string(char* string, std::ostream& os) {
    // TODO: Print each character in `string` to `os` separated by spaces. Do not include a trailing space.
    // NOTE: To print to `os` use the << operator. For example, `os << 5;` prints `5` to `os`. 
}

TEST_CASE("print_array prints integers separated by spaces") {
    int arr[] = {1, 2, 3, 4};
    std::ostringstream oss;

    print_array(arr, 4, oss);

    REQUIRE(oss.str() == "1 2 3 4");
}

TEST_CASE("print_array prints nothing for empty array") {
    int arr[] = {0};
    std::ostringstream oss;

    print_array(arr, 0, oss);

    REQUIRE(oss.str().empty());
}

TEST_CASE("print_string prints characters separated by spaces") {
    char str[] = "cat";
    std::ostringstream oss;

    print_string(str, oss);

    REQUIRE(oss.str() == "c a t");
}

TEST_CASE("print_string prints nothing for empty string") {
    char str[] = "";
    std::ostringstream oss;

    print_string(str, oss);

    REQUIRE(oss.str().empty());
}
```
2. Complete the TODOs in each function.
3. Make sure the program compiles and runs without errors, and that all tests pass.

> [!IMPORTANT]
> You should submit `cstyle_arrays.cpp` to Gradescope.

##  Modifying C-Style Arrays

### Exercise `reverse.cpp`

1. Create a new file called `reverse.cpp` and copy the following program into it:
```cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

void reverse_array(int *array, int n) {
    // TODO: Reverse the order of elements in `array`.
}

TEST_CASE("reverse_array reverses small arrays") {
    int arr[] = {1, 2, 3};
    reverse_array(arr, 3);

    REQUIRE(arr[0] == 3);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr[2] == 1);
}

TEST_CASE("reverse_array works on even-length arrays") {
    int arr[] = {10, 20, 30, 40};
    reverse_array(arr, 4);

    REQUIRE(arr[0] == 40);
    REQUIRE(arr[1] == 30);
    REQUIRE(arr[2] == 20);
    REQUIRE(arr[3] == 10);
}

TEST_CASE("reverse_array leaves single-element array unchanged") {
    int arr[] = {99};
    reverse_array(arr, 1);

    REQUIRE(arr[0] == 99);
}

TEST_CASE("reverse_array leaves empty array unchanged") {
    int arr[] = {0};
    reverse_array(arr, 0);

    // Nothing to check except that it compiles and runs without error
    REQUIRE(true);
}
```
2. Complete the TODOs in each function.
3. Make sure the program compiles and runs without errors, and that all tests pass.

> [!IMPORTANT]
> You should submit `reverse.cpp` to Gradescope.

## Arrays of Pointers

### Exercise `permute.cpp`

**Double pointers** are pointers that point to other pointers. They are useful when you need to store the address of a
pointer or when you want to create an array of pointers. Like regular pointers, double pointers store memory addresses,
namely, the addresses of other pointers.

1. Create a new file called `permute.cpp` and copy the following program into it:
```cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

void permute_pointers(int** array, int* permutation, int n) {
    // TODO: Permute `array` such that `array[i] = array[permutation[i]]`.
    // NOTE: Iterating over `i` and setting `array[i] = array[permutation[i]]` will not work. Why?
}

TEST_CASE("permute_pointers rearranges according to permutation array") {
    int a = 10, b = 20, c = 30;
    int* arr[] = {&a, &b, &c};

    // New order: arr[0] <- arr[2], arr[1] <- arr[0], arr[2] <- arr[1]
    int perm[] = {2, 0, 1};

    permute_pointers(arr, perm, 3);

    REQUIRE(*arr[0] == 30); // was c
    REQUIRE(*arr[1] == 10); // was a
    REQUIRE(*arr[2] == 20); // was b
}

TEST_CASE("permute_pointers works with identity permutation") {
    int x = 1, y = 2, z = 3;
    int* arr[] = {&x, &y, &z};
    int perm[] = {0, 1, 2};

    permute_pointers(arr, perm, 3);

    REQUIRE(*arr[0] == 1);
    REQUIRE(*arr[1] == 2);
    REQUIRE(*arr[2] == 3);
}

TEST_CASE("permute_pointers works with single element") {
    int x = 42;
    int* arr[] = {&x};
    int perm[] = {0};

    permute_pointers(arr, perm, 1);

    REQUIRE(*arr[0] == 42);
}

TEST_CASE("permute_pointers on empty array does nothing") {
    int** arr = nullptr;
    int* perm = nullptr;

    permute_pointers(arr, perm, 0);

    SUCCEED("No crash on empty array");
}
```
2. Complete the TODOs in each function.
3. Make sure the program compiles and runs without errors, and that all tests pass.

> [!IMPORTANT]
> You should submit `permute.cpp` to Gradescope.

# Dynamic Memory Allocation

**Dynamic memory allocation** in C++ allows you to allocate memory at runtime, which is useful when you don’t know the 
size of the data until the program is running. A key aspect of memory management in C++ is manual deallocation: whenever
you allocate memory with `new`, you are responsible for freeing it with `delete`. Failing to do so creates 
**memory leaks**, where allocated memory remains unavailable and can degrade system performance over time.

In C++, you can:
- Use `new` to allocate memory for a single variable.
- Use `new[]` to allocate memory for an array of variables.
- Use `delete` to free memory allocated for a single variable.
- Use `delete[]` to free memory allocated for an array.

## Allocation and Deallocation

### Exercise `allocate.cpp`

1. Create a new file called `allocate.cpp` and copy the following program into it:
```cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

int* allocate_one() {
    // TODO: Allocate a single integer with the `new` operator.
}

void deallocate_one(int* pointer) {
    // TODO: Allocate a single integer with the `delete` operator.
}

int* allocate_many(int n) {
    // TODO: Allocate an array of `n` integers with the `new[]` operator.
}

void deallocate_many(int* pointer) {
    // TODO: Deallocate an array of integers with the `delete[]` operator.
}

TEST_CASE("allocate_one allocates an integer") {
    int* p = allocate_one();

    REQUIRE(p != nullptr);

    *p = 42;
    REQUIRE(*p == 42);

    deallocate_one(p);
}

TEST_CASE("allocate_many allocates an array of n integers") {
    int n = 5;
    int* arr = allocate_many(n);

    REQUIRE(arr != nullptr);

    for (int i = 0; i < n; i++) {
        arr[i] = i * 10;
    }
    for (int i = 0; i < n; i++) {
        REQUIRE(arr[i] == i * 10);
    }

    deallocate_many(arr);
}
```
2. Complete the TODOs in each function.
3. Make sure the program compiles and runs without errors, and that all tests pass.

> [!IMPORTANT]
> You should submit `allocate.cpp` to Gradescope.

# Classes

## Array

### Exercise `array.cpp`

In this exercise, you will implement a **fixed-size dynamic array** in C++. This data structure efficiently models 
fixed-length sequences with two main operations:
- `get(idx)` returns the value at index `idx`
- `set(idx, value)` sets the value at index `idx` to `value`
These operations are similar to `std::array`. In a future lab, we will add automatic resizing like `std::vector`. 

1. Create a new file called `array.cpp` and copy the following program into it:
```cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>

class Array {
private:
    int* m_data;
    int m_size;

public:
    Array(int size, int default_value) {
        // TODO: Initialize the member variables of the `Array` object. After dynamically allocating `m_data`, fill it 
        // with `default_value`.
    }
    
    ~Array() {
        // TODO: Deallocate `m_data`.
    }
    
    // C++ magic. Feel free to ignore these two lines, or ask a staff member if you are curious.
    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;
    
    int get(int idx) {
        // TODO: Return the element at index `idx` in the array. If `idx` is out-of-bounds, throw an `std::out_of_range`
        // exception.
    }
    
    void set(int idx, int value) {
        // TODO: Set the element at index `idx` in the array to `value`. If `idx` is out-of-bounds, throw an 
        // `std::out_of_range` exception.
    }
    
    int size() {
        // TODO: Return the size of the array.
    }
};

TEST_CASE("Array initializes with default value") {
    Array arr(5, 42);
    REQUIRE(arr.size() == 5);

    for (int i = 0; i < arr.size(); i++) {
        REQUIRE(arr.get(i) == 42);
    }
}

TEST_CASE("Array set and get work correctly") {
    Array arr(3, 0);
    arr.set(0, 10);
    arr.set(1, 20);
    arr.set(2, 30);

    REQUIRE(arr.get(0) == 10);
    REQUIRE(arr.get(1) == 20);
    REQUIRE(arr.get(2) == 30);
}

TEST_CASE("Array overwriting values") {
    Array arr(2, 7);
    arr.set(0, 100);
    REQUIRE(arr.get(0) == 100);
}

TEST_CASE("Array throws on get out-of-bounds") {
    Array arr(3, 0);
    REQUIRE_THROWS_AS(arr.get(-1), std::out_of_range);
    REQUIRE_THROWS_AS(arr.get(3), std::out_of_range);
}

TEST_CASE("Array throws on set out-of-bounds") {
    Array arr(2, 0);
    REQUIRE_THROWS_AS(arr.set(-1, 10), std::out_of_range);
    REQUIRE_THROWS_AS(arr.set(2, 20), std::out_of_range);
}

TEST_CASE("Array size remains constant after set") {
    Array arr(4, 5);
    REQUIRE(arr.size() == 4);
    arr.set(1, 50);
    REQUIRE(arr.size() == 4);
}
```
2. Complete the TODOs in each function.
3. Make sure the program compiles and runs without errors, and that all tests pass.

> [!IMPORTANT]
> You should submit `array.cpp` to Gradescope.

## Matrix

### Exercise `matrix.cpp`

In this exercise, you will implement a **fixed-size dynamic matrix** in C++. A matrix is a two-dimensional fixed-length 
sequence that allows you to organize data in rows and columns. This data structure is widely used in scientific 
computing, graphics, simulations, and machine learning, where operations on grids or tables of numbers are common.

The matrix supports three main operations:
- `get(row, col)` returns the value at the specified row and column
- `set(row, col, value)` sets the value at the specified row and column
- `permute_dims(dim0, dim1)` which can swap the rows and columns 

1. Create a new file called `matrix.cpp` and copy the following program into it:
```cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>

class Matrix {
private:
    // TODO: You can use `int**` or `int*` as the type of `m_data`. Use whichever option you prefer.
    int** m_data;
    int m_rows;
    int m_cols;

public:
    Matrix(int rows, int cols, int default_value) {
        // TODO: Initialize the member variables of the `Matrix` object. After dynamically allocating `m_data`, fill it 
        // with `default_value`.
    }
    
    ~Matrix() {
        // TODO: Deallocate any dynamically allocated memory.
    }
    
    // C++ magic. Feel free to ignore these two lines, or ask a staff member if you are curious.
    Matrix(const Matrix&) = delete;
    Matrix& operator=(const Matrix&) = delete;
    
    int get(int row, int col) {
        // TODO: Return the element at row `row` and column `col` in the matrix. If either `row` or `col` is 
        // out-of-bounds, throw an `std::out_of_range` exception.
    }
    
    void set(int row, int col, int value) {
        // TODO: Set the element at row `row` and column `col` in the matrix to `value`. If either `row` or `col` is 
        // out-of-bounds, throw an `std::out_of_range` exception.
    }
    
    void permute_dims(int dim0, int dim1) {
        // TODO: Permute the order of the matrix dimensions. If `dim0 == 0` and `dim1 == 1`, do nothing. If `dim0 == 1`
        // and `dim1 == 0`, exchange the rows and columns of the matrix. If `B` is the matrix before the permutation and
        // `A` is the matrix after the permutation, then we should have `A[row][col] = B[col][row]`. This is the same as
        // transposing the matrix. In all other cases, throw an `std::invalid_argument` exception.
    }
    
    int rows() {
        // TODO: Return the number of rows in the matrix.
    }
    
    int cols() {
        // TODO: Return the number of columns in the matrix.
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
```
2. Complete the TODOs in each function.
3. Make sure the program compiles and runs without errors, and that all tests pass.

> [!IMPORTANT]
> You should submit `matrix.cpp` to Gradescope.

## Tensor

### Exercise `tensor.cpp`

In this exercise, you will implement a **fixed-size dynamic tensor** in C++. A tensor is a multi-dimensional 
fixed-length sequence that generalizes arrays and matrices to three or more dimensions. Tensors are widely used in 
scientific computing, graphics, simulations, and machine learning, where operations on multi-dimensional data are 
common.

The tensor supports three main operations:
- `get(indices)` returns the value at the specified indices
- `set(indices, value)` sets the value at the specified indices
- `permute_dims(dims)` swaps the order of the dimensions

1. Create a new file called `tensor.cpp` and copy the following program into it:
```cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>
#include <vector>

class Tensor {
private:
    // TODO: You can use `int*`, `void*` or `Tensor*` as the type of `m_data`. Use whichever option you prefer.
    int* m_data;
    std::vector<int> m_shape;

public:
    Tensor(std::vector<int> shape, int default_value) {
        // TODO: Initialize the member variables of the `Tensor` object.
    }
    
    ~Tensor() {
        // TODO: Deallocate any dynamically allocated memory.
    }
    
    // C++ magic. Feel free to ignore these two lines, or ask a staff member if you are curious.
    Tensor(const Tensor&) = delete;
    Tensor& operator=(const Tensor&) = delete;
    
    int get(std::vector<int> idx) {
        // TODO: Return the element at index `(idx[0], idx[1], ...)` in the tensor. If any component of `idx` is 
        // out-of-bounds, throw an `std::out_of_range` exception. If `idx` is the wrong length, throw an 
        // `std::invalid_argument` exception.
    }
    
    void set(std::vector<int> idx, int value) {
        // TODO: Set the element at index `(idx[0], idx[1], ...)` in the tensor to `value`. If any component of `idx` is 
        // out-of-bounds, throw an `std::out_of_range` exception. If `idx` is the wrong length, throw an 
        // `std::invalid_argument` exception.
    }
    
    void permute_dims(std::vector<int> dims) {
        // TODO: Permute the order of the tensor dimensions. If `B` is the tensor before the permutation and `A` is the 
        // tensor after the permutation, then we should have 
        // `A[idx[0], idx[1], ...] = B[idx[dims[0]], idx[dims[1]], ...]`. If the permutation is invalid, throw an 
        // `std::invalid_argument` exception.
    }
    
    std::vector<int> shape() {
        // TODO: Return the shape of the tensor.
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
```
2. Complete the TODOs in each function.
3. Make sure the program compiles and runs without errors, and that all tests pass.

> [!IMPORTANT]
> You should submit `tensor.cpp` to Gradescope.