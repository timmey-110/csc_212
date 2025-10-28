# Lab 6 - Linked Lists

# Overview

In this lab, you will implement and analyze linked lists.

## Learning Objectives

By the end of this lab, you should be able to:

1. Implement linked list data structures (e.g. single, double, circular).
2. Evaluate the performance characteristics of various linked list implementations.

## Grading

To receive full credit, you should:

1. Attend, participate and collaborate.
2. Make at least one submission to Gradescope.

> [!IMPORTANT]
> Effort is enough to receive full credit. You do not need to successfully complete any activities.

## Milestones

To achieve the lab objectives, you should:

1. Complete all activities listed under **Core Content**.

> [!NOTE]
> If you do not complete all activities listed under **Core Content** during the lab period, we recommend finishing them
> on your own. Subsequent labs, assignments and lectures will assume you have completed this lab's **Core Content**
> activities.

To leave early, you should:

1. Complete all activities listed under **Core Content**.
2. Complete all activities listed under **Extra Practice** or **Optional Advanced Topics**.

To maximize your learning, you should:

1. Complete all activities listed under **Core Content**.
2. Complete all activities listed under **Extra Practice**.
3. Attempt some activities listed under **Optional Advanced Topics**.

# Core Content

## Project Setup

1. Create a new project called `csc212-lab-06` in your IDE.
2. Download all files from [the lab handout folder](handout) into the `csc212-lab06` project.

> [!NOTE]
> To download all files from the repository, navigate to the root of the repository, click on the green **Code** button
> and select **Download Zip**.`

## Singly Linked List

A singly linked list is a sequence of elements stored in nodes. The first node, known as the **head**, contains a
pointer to the second node, which contains a pointer to the third node, and so on, until the final node, known as the
**tail**.

### Implementation

In this section, you will design and implement a singly linked list.

1. Complete `singly_linked_list.h` and `singly_linked_list.cpp`.
2. Build `test_singly_linked_list` from `singly_linked_list.cpp`, and `test_singly_linked_list.cpp`.
3. Run `test_singly_linked_list`. All tests should pass.

> [!IMPORTANT]
> Submit `singly_linked_list.h` and `singly_linked_list.cpp` to Gradescope.

### Time Complexity Analysis

In this section, you will analyze the time complexity of your singly linked list implementation. If you spend more than
5-10 minutes on this section, look at the solution provided below and move on.

1. State the worst-case asymptotic time complexity of `push_front`, `pop_front`, `operator[]` and `size` in your
   implementation. Justify your reasoning. Record your answer under **Time Complexity** in `singly_linked_list.md`.
2. Build `bench_singly_linked_list` from `singly_linked_list.cpp` and `bench_singly_linked_list.cpp`. This program takes
   one command line argument, `n`, the number of calls to `push_front`, and outputs the runtime of your linked list and
   `std::vector`.
3. Predict the minimum value of `n` where your linked list outperforms `std::vector`. Justify your reasoning. Find the
   minimum value of `n` where your linked list is faster by running `bench_singly_linked_list` with different values of
   `n`. Was your prediction close? Record your prediction and results under **Time Complexity** in
   `singly_linked_list.md`.

<details>
<summary>Solution</summary>

1. To compute the asymptotic time complexity of linked list operations, we can count the number of linked list node
   accesses. In `push_front`, we access $1$ node, the new node, which takes $\Theta(1)$ time. In `pop_front`, we  
   access $1$ node, the head node, to get a pointer to the new head, which takes $\Theta(1)$ time. In `operator[]`, we
   might have to traverse all $n$ nodes of the linked list, which takes $\Theta(n)$ time. If `size` counts the number of
   nodes by traversing the linked list, it takes $\Theta(n)$ time. However, if the size is tracked with a member
   variable (e.g. `m_size`), `size` takes $\Theta(1)$ time.
2. N/a.
3. N/a.

</details>

> [!IMPORTANT]
> Submit `singly_linked_list.md` to Gradescope.

### Space Complexity Analysis

In this section, you will analyze the space complexity of your singly linked list implementation. If you spend more than
5-10 minutes on this section, look at the solution provided below and move on.

1. Give a formula for the worst-case size in bytes of an instance of your linked list containing $n$ elements. Assume
   each pointer takes $4$ bytes, and each integer takes $4$ bytes. Record your answer under **Space Complexity** in
   `singly_linked_list.md`.
2. Give a formula for the worst-case **percent memory overhead** of an instance of your linked list containing $n$
   elements. The percent memory overhead is percentage of bytes used to store non-element data. For example, if a data
   structure used $8$ bytes of non-element data to store $4$ bytes of elements, it would have a percent memory overhead of
   $\frac{8}{8 + 4} = \frac{2}{3}$ or approximately 66%. Record your answer under **Space Complexity** in
   `singly_linked_list.md`.
3. Compare the worst-case **percent memory overhead** of a grow-by-doubling dynamic array to your linked list. In the
   worst-case, a grow-by-doubling dynamic array containing $n$ elements requires $4n$ bytes for the $n$ elements, $4n$
   bytes for the excess capacity, and $3 \cdot 4 = 12$ bytes for the member variables `m_data`, `m_size` and
   `m_capacity`, for a total of $8n + 12$ bytes. Therefore, the worst-case percent memory overhead is
   $\frac{4n + 12}{8n + 12}$. Which data structure is more memory-efficient? Record your answer under
   **Space Complexity** in `singly_linked_list.md`

<details>
<summary>Solution</summary>

1. The exact formula depends on your linked list implementation. If the linked list stores a head pointer and the size,
   and each node stores a pointer and an element, then the total number of bytes is $(4 + 4)n + (4 + 4) = 8n + 8$.
2. The exact formula depends on your linked list implementation. Assuming the total number of bytes is $8n + 8$, the
   percent memory overhead is $\frac{4n + 8}{8n + 8}$ since $4n$ bytes are used to store elements.
3. As $n$ grows large, both the dynamic array and linked list percent memory overhead approach 50%. In the worst-case,
   they are equally efficient. However, on average and in the best case, the dynamic array has lower memory overhead.

</details>

> [!IMPORTANT]
> Submit `singly_linked_list.md` to Gradescope.

# Extra Practice

## Doubly Linked List

Like a singly linked list, a doubly linked list is a sequence of elements stored in nodes where each node contains a
pointer to the next node. Unlike a singly linked list, each node also contains a pointer to the previous node.

### Implementation

In this section, you will design and implement a doubly linked list.

1. Complete `doubly_linked_list.h` and `doubly_linked_list.cpp`.
2. Build `test_doubly_linked_list` from `doubly_linked_list.cpp`, and `test_doubly_linked_list.cpp`.
3. Run `test_doubly_linked_list`. All tests should pass.

> [!IMPORTANT]
> Submit `doubly_linked_list.h` and `doubly_linked_list.cpp` to Gradescope.

### Time Complexity Analysis

In this section, you will analyze the time complexity of your doubly linked list implementation. If you spend more than
5-10 minutes on this section, look at the solution provided below and move on.

1. State the worst-case asymptotic time complexity of `push_front`, `pop_front`, `push_back`, `pop_back`, `operator[]`
   and `size` in your implementation. Justify your reasoning. Record your answer under **Time Complexity** in
   `doubly_linked_list.md`.

<details>
<summary>Solution</summary>

1. To compute the asymptotic time complexity of linked list operations, we can count the number of linked list node
   accesses. The analysis of `push_front`, `pop_front`, `operator[]`, and `size` are the same as in a singly linked
   list. If there is a tail pointer (e.g. `m_tail`, or if circularly linked, `m_head->prev`), `push_back` and `pop_back`
   take $\Theta(1)$ time. However, if there isn't a tail pointer, both `push_back` and `pop_back` take $\Theta(n)$
   time to traverse the $n$ nodes of the list.

</details>

> [!IMPORTANT]
> Submit `doubly_linked_list.md` to Gradescope.

### Space Complexity Analysis

In this section, you will analyze the space complexity of your doubly linked list implementation. If you spend more than
5-10 minutes on this section, look at the solution provided below and move on.

1. Give a formula for the worst-case size in bytes of an instance of your linked list containing $n$ elements. Assume
   each pointer takes $4$ bytes, and each integer takes $4$ bytes. Record your answer under **Space Complexity** in
   `doubly_linked_list.md`.
2. Give a formula for the worst-case **percent memory overhead** of an instance of your linked list containing $n$
   elements. Record your answer under **Space Complexity** in `doubly_linked_list.md`.
3. Compare the worst-case **percent memory overhead** of a grow-by-doubling dynamic array to your linked list. Which
   data structure is more memory-efficient? Record your answer under **Space Complexity** in `doubly_linked_list.md`

<details>
<summary>Solution</summary>

1. The exact formula depends on your linked list implementation. If the linked list stores a head pointer, a tail
   pointer, and the size, and each node stores two pointers and an element, then the total number of bytes is
   $(4 + 4 + 4)n + (4 + 4 + 4) = 12n + 12$.
2. The exact formula depends on your linked list implementation. Assuming the total number of bytes is $12n + 12$, the
   percent memory overhead is $\frac{8n + 12}{12n + 12}$ since $4n$ bytes are used to store elements.
3. As $n$ grows large, the dynamic array percent memory overhead approaches 50%, but the linked list percent memory
   overhead approaches 66%. The dynamic array has lower memory overhead.

</details>

> [!IMPORTANT]
> Submit `doubly_linked_list.md` to Gradescope.

# Optional Advanced Topics

## Skiplist

A skiplist is a probabilistic data structure that extends linked lists with highly efficient search and update
operations. They are used by several major companies to search and update sets of elements. For example, Discord, a
social media platform that provides the ability to create large group chats (servers),
[stores the set of users in each group chat in a skiplist](https://discord.com/blog/using-rust-to-scale-elixir-for-11-million-concurrent-users).

There are several excellent explanations of skiplists available online,
including [the original paper](https://dl.acm.org/doi/pdf/10.1145/78973.78977)
and [a lecture from MIT's Design and Analysis of Algorithms course](https://www.youtube.com/watch?v=2g9OSRKJuzM) (their
CSC 440 equivalent).

### Implementation

In this section, you will design and implement a skiplist.

1. Complete `skiplist.h` and `skiplist.cpp`.
2. Build `test_skiplist` from `skiplist.cpp`, and `test_skiplist.cpp`.
3. Run `test_skiplist`. All tests should pass.

> [!IMPORTANT]
> Submit `skiplist.h` and `skiplist.cpp` to Gradescope.
