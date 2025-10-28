# Debugger

### Exercise `step.cpp`

If you haven't used a debugger before and are using VSCode watch 
[this video](https://www.youtube.com/watch?v=G9gnSGKYIg4), otherwise if you are using CLion or another IDE watch 
[this video](https://www.youtube.com/watch?v=5wGsRdumueU) to get an introduction. 

1. Create a new file called `step.cpp` and copy the following program into it:
```cpp
#include <iostream>

class Counter {
private:
    int total;

public:
    Counter(int start) {
        total = start;                          // !!!
    }

    void add_up_to(int n) {
        for (int i = 1; i <= n; i++) {          // !!!
            total += i;                         // !!!
        }
    }

    int get_total() {
        return total;                           // !!!
    }
};

int adjust(int value) {
    if (value % 2 == 0) {                       // !!!
        return value / 2;                   
    } else {                                    // !!!
        return value * 3 + 1;                   // !!!
    }
}

int main() {
    Counter c(5);                               // !!!

    c.add_up_to(3);                             // !!!

    int result = adjust(c.get_total());         // !!!

    std::cout << "Result: " << result << "\n";  // !!!
    return 0;                                   // !!!
}
```
2. Set a breakpoint on the first line of `main`.
3. Start the debugger. It should pause on the first line of `main`.
4. Step through the program using step-over and step-into, making sure you can reach every line marked with `// !!!`.

> [!IMPORTANT]
> You do not need to submit anything to Gradescope for this exercise.

## Debugging Unittests

### Exercise `debug.cpp`

1. Create a new file called `debug.cpp` and copy the following program into it:

```cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

int sum_of_squares(int n) {
    int total = 0;
    for (int i = 1; i < n; i++) {
        total += i * i;
    }
    return total;
}

TEST_CASE("sum_of_squares computes correctly") {
    REQUIRE(sum_of_squares(1) == 1);
    REQUIRE(sum_of_squares(2) == 5);
    REQUIRE(sum_of_squares(3) == 14);
    REQUIRE(sum_of_squares(0) == 0);
    REQUIRE(sum_of_squares(5) == 54);
}
```
1. This program uses the Catch2 testing framework to verify the correctness of the `sum_of_squares` function. You will 
need to add [the Catch2 library](catch.hpp) to your project to compile the program. Ensure you can compile the program.
2. The program currently has two bugs. Use a debugger to find the bugs.
3. Once you locate the bugs, fix them and re-run all tests to make sure they pass. The program should compile and run
   without errors.

> [!IMPORTANT]
> You do not need to submit anything to Gradescope for this exercise.