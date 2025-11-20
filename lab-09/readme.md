# Lab 9 - Binary Search Trees

# Overview

In this lab, you will design, implement and analyze binary search trees.

## Learning Objectives

By the end of this lab, you should be able to:

1. Implement abstract data types with binary search trees.
2. Evaluate the performance characteristics of binary search trees.

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

1. Create a new project called `csc212-lab-09` in your IDE.
2. Download all files from [the lab handout folder](handout) into the `csc212-lab-09` project.

> [!NOTE]
> To download all files from the repository, navigate to the root of the repository, click on the green **Code** button
> and select **Download Zip**.`

## Set

Sets provide three main operations:

1. `insert` which adds a value into the set.
2. `erase` which removes a value from the set.
3. `contains` which checks if a value is in the set.

### Implementation

In this section, you will design and implement a set using a binary search tree.

1. Complete `set.h` and `set.cpp`.
2. Build `test_set` from `set.cpp`, and `test_set.cpp`.
3. Run `test_set`. All tests should pass.

> [!IMPORTANT]
> Submit `set.h` and `set.cpp` to Gradescope.

### Theoretical Analysis

In this section, you will analyze the time complexity of your set implementation. If you spend more than 5-10 minutes on
this section, look at the solution provided below and move on.

1. Give tight bounds on the asymptotic complexity of `insert`, `erase` and `contains` on a size $n$ set in the
   best-case. Record your answer and your reasoning under **Best Case** in `set.md`.
2. Give tight bounds on the asymptotic complexity of `insert`, `erase` and `contains` on a size $n$ set in the
   worst-case. Record your answer and your reasoning under **Worst Case** in `set.md`.

<details>
<summary>Solution</summary>

1. In the best case, `insert`, `erase` and `contains` all take $\Theta(1)$ time. If the subtree to the left of the root
   is empty, inserting a node into that subtree takes constant time. Likewise, erasing a node (which does not exist)
   from that subtree also takes constant time. Calling `contains` with the value stored in the root takes constant time.
2. In the worst case, `insert`, `erase` and `contains` all take $\Theta(n)$ time. If every left pointer in the tree is
   `nullptr`, inserting, erasing and finding the deepest node takes linear time, since we must traverse a linear number
   of nodes.

</details>

> [!IMPORTANT]
> Submit `set.md` to Gradescope.

# Extra Practice

## Map

Maps provide two main operations:

1. `operator[]` which either (a) maps a key to a value or (b) returns the value associated with a given key.
2. `erase` which removes a key (and the corresponding value) from the map.

### Implementation

In this section, you will design and implement a map using a binary search tree.

1. Complete `map.h` and `map.cpp`.
2. Build `test_map` from `map.cpp`, and `test_map.cpp`.
3. Run `test_map`. All tests should pass.

> [!IMPORTANT]
> Submit `map.h` and `map.cpp` to Gradescope.

### Theoretical Analysis

In this section, you will analyze the time complexity of your map implementation. If you spend more than 5-10 minutes on
this section, look at the solution provided below and move on.

1. Give tight bounds on the asymptotic complexity of `operator[]` and `erase` on a size $n$ map in the best-case. Record
   your answer and your reasoning under **Best Case** in `map.md`.
2. Give tight bounds on the asymptotic complexity of `operator[]` and `erase` on a size $n$ map in the worst-case.
   Record your answer and your reasoning under **Worst Case** in `map.md`.

<details>
<summary>Solution</summary>

1. Both take $\Theta(1)$ time for the same reasons as the set.
2. Both take $\Theta(n)$ time for the same reasons as the set.

</details>

> [!IMPORTANT]
> Submit `map.md` to Gradescope.

# Optional Advanced Topics

## Sequence

Sequences provide three main operations:

1. `insert` which inserts a value at a given index in the sequence.
2. `erase` which removes a value at a given index in the sequence.
3. `operator[]` which returns the value at a given index in the sequence.

### Implementation

In this section, you will design and implement a sequence using a binary search tree.

1. Complete `sequence.h` and `sequence.cpp`.
2. Build `test_sequence` from `sequence.cpp`, and `test_sequence.cpp`.
3. Run `test_sequence`. All tests should pass.

> [!IMPORTANT]
> Submit `sequence.h` and `sequence.cpp` to Gradescope.

### Theoretical Analysis

In this section, you will analyze the time complexity of your sequence implementation.

1. Give tight bounds on the asymptotic complexity of `insert`, `erase` and `operator[]` on a size $n$ sequence in the
   best-case. Record your answer and your reasoning under **Best Case** in `sequence.md`.
2. Give tight bounds on the asymptotic complexity of `insert`, `erase` and `operator[]` on a size $n$ sequence in the
   worst-case. Record your answer and your reasoning under **Worst Case** in `sequence.md`.

> [!IMPORTANT]
> Submit `sequence.md` to Gradescope.
