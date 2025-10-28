# Lab 2 - Analysis of Algorithms

# Overview

In this lab, you will design and implement several brute-force algorithms, and then empirically analyze their
performance.

## Learning Objectives

By the end of this lab, you should be able to:

1. Design brute-force algorithms for combinatorial problems.
2. Implement brute-force algorithms for combinatorial problems.
3. Analyze the theoretical time complexity of algorithms for combinatorial problems.
4. Compare the empirical performance of algorithms.

When designing a fast algorithm to solve a challenging problem, it is often helpful to begin by designing a brute-force
algorithm. **Brute-force algorithms** try all possible solutions to a problem until a correct solution is found or there
are no solutions left to try. Sometimes brute-force algorithms are sufficient for realistic problem sizes. By analyzing
their time complexity and empirically measuring their runtime, we can decide whether designing a faster algorithm is
necessary.

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

1. Create a new project called `csc212-lab-02` in your IDE.
2. Download all files from [the lab handout folder](handout) into the `csc212-lab-02` project.

## Two Sum Problem (2SUM)

In the Two Sum Problem (2SUM), you are given some integers and a target value. You must determine if there is a pair of
distinct integers that sum to the target value. See `test_two_sum.cpp` for examples.

### Implementation

In this section, you will design and implement an algorithm to solve 2SUM.

1. Complete `two_sum.cpp`.
2. Build `test_two_sum` from `two_sum.cpp`, `two_sum_fast.cpp`, and `test_two_sum.cpp`.
3. Run `test_two_sum`. All tests should pass.

> [!IMPORTANT]
> Submit `two_sum.cpp` to Gradescope.

### Theoretical Analysis

In this section, you will analyze the time complexity of your 2SUM algorithm. If you spend more than 5-10 minutes on
this section, look at the solution provided below and move on.

1. Give a formula for the number of vector accesses performed by your algorithm on an input of size $n$. Assume that the
   target value is not in the input vector. Record your answer in `two_sum.md`.

<details>
<summary>Solution</summary>

1. If the target value is not in the input vector, the algorithm will check all pairs of indices $i, j$
   where $0 \leq j < i < n$. For each pair of indices, the algorithm performs $2$ array accesses: one to read $A[i]$ and
   one to read $A[j]$. Therefore, the total number of array access is

   $T(n) = \sum\limits_{i=0}^{n-1} \sum\limits_{j=0}^{i - 1} 2 = 2 \sum\limits_{i=0}^{n-1} i = n(n-1)$

   Depending on your implementation, the correct formula might vary.

</details>

### Empirical Analysis

In this section, you will benchmark the performance of your 2SUM algorithm against another 2SUM algorithm.

1. Read `two_sum_fast.cpp`.
2. Predict whether your `two_sum` function or the provided `two_sum_fast` function will be faster on inputs of size `1`,
   `10`, `100`, `1000` and `10000`. Consider the number of array accesses performed by both algorithms. Record your
   predictions in `two_sum.md`.
3. Build `bench_two_sum` from `two_sum.cpp`, `two_sum_fast.cpp`, and `bench_two_sum.cpp`. This program takes a single
   command line argument `n`, the size of the input array, and outputs the runtime of `two_sum` and `two_sum_fast`. If
   you aren't sure how to pass command line arguments to `bench_two_sum` with your IDE, Google your IDE documentation.
4. Run `bench_two_sum` with inputs of size `1`, `10`, `100`, `1000` and `10000`. Compare the results against your
   predictions. Record your findings in `two_sum.md`.
5. Decide whether you should use `two_sum` or `two_sum_fast` for each input size. Record your reasoning in
   `two_sum.md`.

> [!IMPORTANT]
> Submit `two_sum.md` to Gradescope.

# Extra Practice

## Three Sum Problem (3SUM)

In the Three Sum Problem (3SUM), you are given some integers and a target value. You must determine if there is a
triplet of distinct integers that sum to the target value. See `test_three_sum.cpp` for examples.

### Implementation

In this section, you will design and implement an algorithm to solve 3SUM.

1. Complete `three_sum.cpp`.
2. Build `test_three_sum` from `three_sum.cpp`, `three_sum_fast.cpp`, and `test_three_sum.cpp`.
3. Run `test_three_sum`. All tests should pass.

> [!IMPORTANT]
> Submit `three_sum.cpp` to Gradescope.

### Theoretical Analysis

In this section, you will analyze the time complexity of your 3SUM algorithm. If you spend more than 5-10 minutes on
this section, look at the solution provided below and move on.

1. Give a formula for the number of vector accesses performed by your algorithm on an input of size $n$. Assume that the
   target value is not in the input vector. Record your answer in `three_sum.md`.

<details>
<summary>Solution</summary>

1. If the target value is not in the input vector, the algorithm will check all triples of indices $i, j, k$
   where $0 \leq k < j < i < n$. For each triplet of indices, the algorithm performs $3$ array accesses: one to
   read $A[i]$ one to read $A[j]$, and one to read $A[k]$. Therefore, the total number of array access is

   $T(n) = \sum\limits_{i=0}^{n-1} \sum\limits_{j=0}^{i - 1} \sum\limits_{k=0}^{j - 1} 3 = 3 \sum\limits_{i=0}^{n-1} \sum\limits_{j=0}^{i - 1} j = 3 \sum\limits_{i=0}^{n-1} \frac{i(i-1)}{2} = \frac{3}{2} \left( \frac{n(n-1)(2n - 1)}{6} - \frac{n(n-1)}{2} \right) = \frac{n(n-1)(n-2)}{2}$

   Depending on your implementation, the correct formula might vary.

</details>

### Empirical Analysis

In this section, you will benchmark the performance of your 3SUM algorithm against another 3SUM algorithm.

1. Read `three_sum_fast.cpp`.
2. Predict whether your `three_sum` function or the provided `three_sum_fast` function will be faster on inputs of size
   `1`, `10`, `100` and `1000`. Consider the number of array accesses performed by both algorithms. Record your
   predictions in `three_sum.md`.
3. Build `bench_three_sum` from `three_sum.cpp`, `three_sum_fast.cpp`, and `bench_three_sum.cpp`. This program takes a
   single command line argument `n`, the size of the input array, and outputs the runtime of `three_sum` and
   `three_sum_fast`. If you aren't sure how to pass command line arguments to `bench_three_sum` with your IDE, Google
   your IDE documentation.
4. Run `bench_three_sum` with inputs of size `1`, `10`, `100` and `1000`. Compare the results against your predictions.
   Record your findings in `three_sum.md`.
5. Decide whether you should use `three_sum` or `three_sum_fast` for each input size. Record your reasoning in
   `three_sum.md`.

> [!IMPORTANT]
> Submit `three_sum.md` to Gradescope.

# Optional Advanced Topics

## Subset Sum Problem (SSP)

In the Subset Sum Problem (SSP), you are given some integers and a target value. You must determine if there is any
subset of integers that sums to the target value. See `test_subset_sum.cpp` for examples.

### Implementation

In this section, you will design and implement an algorithm to solve SSP.

1. Complete `subset_sum.cpp`.
2. Build `test_subset_sum` from `subset_sum.cpp` and `test_subset_sum.cpp`.
3. Run `test_subset_sum`. All tests should pass.

> [!IMPORTANT]
> Submit `subset_sum.cpp` to Gradescope.

### Empirical Analysis

In this section, you will benchmark the performance of your SSP algorithm and revise it to improve performance.

1. Read `bench_subset_sum.cpp`.
2. Build `bench_subset_sum` from `subset_sum.cpp` and `bench_subset_sum.cpp`. This program takes a single command line
   argument `n`, the size of the input array, and outputs the runtime of your `subset_sum` function.
3. Predict the largest input size your program can solve in under one second. Record your answer in
   `subset_sum.md`.
4. Run `bench_subset_sum` with varying values of `n` to find the largest input size your program can solve in under one
   second. Record your answer in `subset_sum.md`.
5. Decide whether your `subset_sum` function is fast enough or too slow. If you are familiar with $\mathcal{O}$
   -notation, provide an asymptotic bound on your algorithm's time complexity. Record your reasoning in
   `subset_sum.md`.
6. Revise your `subset_sum` function so it can solve even larger input sizes in under one second. Try to design an
   asymptotically faster algorithm. Explain your new algorithm in `subset_sum.md`.

> [!IMPORTANT]
> Submit `subset_sum.cpp` and `subset_sum.md` to Gradescope.