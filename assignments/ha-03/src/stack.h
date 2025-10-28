#pragma once
#include <cstddef>

class Stack {
    private:
        int* data;       // pointer to the array storing stack elements
        size_t capacity; // maximum capacity of the stack
        size_t n_elem;   // current number of elements in the stack

    public:
        Stack(size_t cap); // constructor with capacity
        ~Stack();          // destructor to free allocated memory          

        void push(int val);  // push an element onto the stack
        void pop();          // pop the top element from the stack
        int top() const;     // get the top element of the stack
        bool empty() const;  // check if the stack is empty
        size_t size() const; // get the current size of the stack
};