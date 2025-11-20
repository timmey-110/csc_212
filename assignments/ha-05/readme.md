# Homework Assignment 5 (due Nov 3rd 11:59pm)

In this assignment, we will explore and practice `recursive` algorithms. For each of the tasks below, you are required to formulate a **recursive solution**.  You may use helper functions as needed, but the main logic of each task must be implemented recursively, either directly within the function provided or in helper functions called by these functions. Iterative solutions will not receive credit.

> [!WARNING] 
> We strongly discourage the use of Large Language Models 
> (LLMs) to generate code or solutions for this assignment.
> The ability to independently think through and solve problems
> using recursion is crucial for your intellectual development.

The assignment is worth a total of 100 points.  If you have any questions or need assistance, please don't hesitate to reach out to us during office hours or post your questions on the `Ed Discussion` forum.

## Task 1: Warming-up (40 points)

In this task, you will solve a number of small problems to practice recursion.  Each problem is worth 10 points. For each problem you will create a function using the provided signatures below.  You may add helper functions as needed to support the recursive implementation.

All the functions should be implemented in a file named `functions.cpp` and all function signatures should be declared in a header file named `functions.h`. You should not put any implementation in the header file `functions.h`.  We are also providing a sample `test_recursion.cpp` that you can use as a starting unit test program.  The test program includes test cases to verify the functionality of each function.  You can modify the test cases or add new ones as needed to thoroughly test your implementation. 

To compile the test program, you can use the following command:

```bash
# compile the test program
g++ -std=c++11 -Wall -Werror -o test test_recursion.cpp functions.cpp
# run the test program
./test
```

### `palindrome`
Implement a function that checks if a given string `S` of length $$0 \leq n < 10^3$$ is a palindrome.  Assume that the empty string is a palindrome and a string constituted only by a single character is also a palindrome. For example, the strings `""`, `"a"`, `"racecar"`, and `"madam"` are palindromes, while the strings `"hello"` and `"world"` are not palindromes.

```cpp
bool palindrome(const std::string& S);
```

### `reverse`
Implement a function that reverses a given sequence of integers. The function takes a reference to a vector of integers and modifies it **in-place** to reverse the order of its elements. Your program should perform no more than $$\lfloor n/2 \rfloor$$ swaps, where $$n$$ is the length of the input array. For example, given the array `[1,2,3,4,5]`, the function should modify it to `[5,4,3,2,1]`.

```cpp
void reverse(std::vector<int>& arr);
```

### `bin_search`
Implement a function that performs a binary search on a sorted sequence of integers to find the index of a target value.  The function takes 3 parameters: a reference to a vector of integers representing the sorted array, the target value to search for, and an output parameter to store the index of the target if found. The function should return `true` if the target is found and `false` otherwise.  For example, given the array `[9,7,5,3,3]` and target `7`, the function should return `true` and set the output `index` to `1`.  Assume the input sequence is sorted in non-increasing order (from largest to smallest).

```cpp
bool bin_search(const std::vector<int>& arr, int target, size_t& index);
```

### `str2int`
Implement a function that converts a string representation of a number into its integer value.  The function takes a string as input and returns the corresponding integer.  The string is guaranteed to be a valid representation of an integer (i.e., it contains only digits and an optional leading `-` sign). For example, given the string `"-12345"`, the function should return the integer `-12345`.  The maximum input value is $$2^{31}-1$$ and the minimum input value is $$-2^{31}$$. For example, given the string `"67890"`, the function should return the integer `67890`.

```cpp
int str2int(const std::string& s);
```

## Task 2: Counting cells (21 points)

Consider a 2D grid of size `m x n` where each cell can be either `0` (empty) or `1` (filled).  A cell is considered connected to another cell if it is immediately adjacent horizontally, vertically, or diagonally. A *region* is defined as a group of connected filled cells. Implement a function that counts the number of cells in a region, given the grid and the coordinates of a starting cell.  If the starting cell is empty, the function should return `0`.  You may assume that the starting cell is always within the bounds of the grid.

### Input
The input to the function is a file name containing the grid of `0`s and `1`s, and the coordinates of the starting cell as two integers `x` and `y`.  The file format is as follows:

- The first line contains two integers $$2 \leq m, n \leq 500$$, representing
  the number of rows and columns in the grid, respectively.
- The next `m` lines each contain `n` integers (either `0` or `1`)
  separated by spaces, representing the grid.

### Output
The function should return the number of cells in the region connected to the starting cell `(x, y)`.

> [!NOTE]
> Assume that `x` is the row index and `y` is the column index, both starting from `0`.
> The origin `(0,0)` is at the top-left corner of the grid.

### Example
Given the following input file `grid.txt`:

```text
5 5
0 0 1 0 0
1 1 1 0 0
0 0 1 0 1 
0 0 0 1 1
1 1 0 0 0
```

The following calls should return `8`, `2`, `8`, and `0` respectively:

```cpp
count_cells("grid.txt", 1, 2)  // returns 8
count_cells("grid.txt", 4, 1)  // returns 2
count_cells("grid.txt", 3, 3)  // returns 8
count_cells("grid.txt", 0, 1)  // returns 0
```

### Function signature
This function should be implemented in `functions.cpp` and declared in `functions.h` as follows:

```cpp
unsigned int count_cells(const std::string& fname, unsigned int x, unsigned int y);
```

## Task 3: Multi-level linked lists (39 points)

A multi-level linked list is a data structure where each node contains a data value (a string in this case), a pointer to the next node in the list, and a pointer to a child node which represents the head of a sublist. The multi-level linked list can be visualized as a hierarchy of linked lists, where each node can potentially lead to another linked list. The following chart illustrates a multi-level linked list:

```
D -> M -> N -> O
     |         |
     M1 -> M2  O1 -> O2
           |
           M2A -> M2B
```

In this example, the top-level list contains nodes `D`, `M`, `N`, and `O`.  Node `M` has a child list containing nodes `M1` and `M2`, where `M2` further has a child list containing nodes `M2A` and `M2B`.  Node `O` has a child list containing nodes `O1` and `O2`.

> [!NOTE]
> For the purpose of this question, we will assume that the
> multi-level linked list only contains string values and 
> no repeated values are allowed.

You are required to design and implement a class `MultiLevelLinkedList` that supports at least the following `public methods`.  **You are required to implement these methods using recursion**.  Note that the methods below are only the minimum required methods.  You may need to add constructor, destructor, and any additional private helper functions as needed. The recursive logic must be implemented either in the methods below or in helper functions called by these methods.  

- `void insert_top_level(const std::string& key)`: [13 points] Performs a sorted insertion of a new node with the given `key` into the top-level linked list.  If the `key` already exists anywhere in the multi-level linked list, the function should ignore the insertion.  

- `void insert_child(const std::string& parent_key, const std::string& key)`: [13 points] Performs a sorted insertion of a new node with the given `key` into the child list of the node identified by `parent_key`. If the `parent_key` does not exist, or if the `key` already exists anywhere in the multi-level linked list, the function should ignore the insertion.

- `void destroy()`: [13 points] Destroys the entire multi-level linked list, freeing all allocated memory.  This function should be called once in the destructor of the class to ensure proper cleanup. 

- `void print() const`: Prints the multi-level linked list in a flattened format.

For example, consider the following sequence of operations:

```cpp
MultiLevelLinkedList mll; // constructor is called automatically here
mll.insert_top_level("M");
mll.insert_top_level("D");
mll.insert_child("M", "M2");
mll.insert_child("M", "M1");
mll.insert_child("M2", "M2A");
mll.insert_child("M2", "M2B");
mll.insert_top_level("N");
mll.insert_child("N", "O2");
mll.insert_child("N", "O1");
mll.print();
// destructor is called automatically here
```

The output should be:

```text
D M M1 M2 M2A M2B N O1 O2
```

Your class should be implemented in two files: `multilevel_list.h` (for the class declaration) and `multilevel_list.cpp` (for the class implementation). A `test_mll.cpp` file is provided to help you test your implementation. You can compile and run the test program using the following commands:

```bash
# compile the test program
g++ -std=c++11 -Wall -Werror -o test_mll test_mll.cpp multilevel_list.cpp
# run the test program
./test_mll
```

## Submission and grading

This assignment relies on automated evaluation. Once you are finished, you **must** submit ONLY the following source files via [Gradescope](https://www.gradescope.com/) to record your grade.

- `functions.h`
- `functions.cpp`
- `multilevel_list.h`
- `multilevel_list.cpp`
- `llm-usage.txt`

The `llm-usage.txt` file should contain: the name of the LLM, if you used one, and a copy of the prompts you entered and the responses you received.  If you did not use an LLM, simply write "No LLM used".

> [!CAUTION]
> Remember, academic integrity is of utmost importance.  Any attempts at
> cheating or plagiarism will result in a forfeiture of credit.  Potential
> further actions include failing the class or referring the case for
> disciplinary measures.
