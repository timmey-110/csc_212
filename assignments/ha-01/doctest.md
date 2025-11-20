# Unit testing with `doctest`

The [`doctest` framework](https://github.com/doctest/doctest) is a
lightweight and easy-to-use testing framework for C++.  It is a single
header file (`doctest.h`) that you can include in your test files.

For your current assignment you can compile the provided `main.cpp`
file along with your `network.cpp` implementation file to create a test
program.  The provided `main.cpp` file contains some example test cases
to get you started.  Note that it uses the `facebook-small.txt` dataset.

Follow the following steps to compile and run your program:

1. Ensure you have the `doctest.h` file in the same directory as your
   `main.cpp` and `network.cpp` files

2. Compile your program using `g++` with C++11 standard (or later):
```bash
$ g++ -std=c++11 -Wall -Werr main.cpp network.cpp -o prog
```

3. Ensure the dataset file (e.g., `facebook-small.txt`) is in the 
   same directory as your compiled program.

4. Run your program, and inspect the output for each of the test cases:
```bash
$ ./prog
```

Return to the [assignment description](./readme.md).
