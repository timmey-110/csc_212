# Lab 3 - Dynamic Arrays

# Overview

In this lab, you will implement several dynamic arrays supporting append and automatic resizing, and evaluate the
tradeoffs of various dynamic array resizing policies.

## Learning Objectives

By the end of this lab, you should be able to:

1. Implement dynamic arrays with automatic resizing.
2. Evaluate the time and space tradeoffs of dynamic array capacity policies (e.g. initial capacity, resize factor,
   resize threshold).

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

1. Create a new project called `csc212-lab-03` in your IDE.
2. Download all files from [the lab handout folder](handout) into the `csc212-lab-03` project.

> [!NOTE]
> To download all files from the repository, navigate to the root of the repository, click on the green **Code** button
> and select **Download Zip**.`

# Core Content

## Dynamic Array: Grow By One

### Implementation

In this section, you will implement a dynamic array that increases the size of the underlying array by one for each
call to `push_back`.

1. Complete `dynamic_array_gbo.cpp`.
2. Build `test_dynamic_array_gbo` from `dynamic_array_gbo.cpp` and `test_dynamic_array_gbo.cpp`.
3. Run `test_dynamic_array_gbo`. All tests should pass.

> [!IMPORTANT]
> Submit `dynamic_array_gbo.cpp` to Gradescope.

### Time Complexity Analysis

In this section, you will analyze the time complexity of your grow by one dynamic array. If you spend more than 5-10
minutes on this section, look at the solution provided below and move on.

1. Give a formula for the total number of store operations (`m_data[i] = v`) performed over $n$ calls to `push_back` on
   an initially empty array. You should state an expression for $T(n)$ in terms of one or more summations and simplify.
   Record your answer and reasoning in `dynamic_array_gbo.md`.
2. Give a formula for the amortized time complexity (number of store operations) of `push_back` over $n$ calls on an
   initially empty array. That is, compute the average number of store operations per call to `push_back` across $n$
   total calls. Record your answer and reasoning in `dynamic_array_gbo.md`.

<details>
<summary>Solution</summary>

1. When `push_back` is called on an array of size $k$, we copy $k - 1$ elements from the old underlying array to the
   new underlying array. This requires $k - 1$ stores. Then, we store the new element in the new underlying array. This
   requires $1$ store. Therefore, calling `push_back` on an array of size $k$ requires $(k - 1) + 1 = k$ stores. To
   produce
   an array of size $n$, we must call `push_back` on array of size $0$, $1$, $2$, all the way up to $n - 1$. Thus, the
   total number of stores $T(n) = \sum\limits_{k = 0}^{n - 1} k = \frac{n(n-1)}{2}$.
2. If we perform $n$ calls to `push_back` on an initially empty array, we perform $\frac{n(n-1)}{2}$ stores. The average
   number of stores per call is $\frac{1}{n} \cdot \frac{n(n-1)}{2} = \frac{n - 1}{2} = \Theta(n)$. Therefore, the
   amortized complexity of `push_back` is $\Theta(n)$.

</details>

> [!IMPORTANT]
> Submit `dynamic_array_gbo.md` to Gradescope.

### Space Complexity Analysis

In this section, you will analyze the space requirements of your grow by one dynamic array. If you spend more than 5-10
minutes on this section, look at the solution provided below and move on.

1. Give a formula for the **percent memory overhead** for a size $n$ instance of your grow by one dynamic array.
   Assuming that all memory slots have the same size, the percent memory overhead of a dynamic array
   is $1 - \frac{n}{m + c}$ where $n$ is the size, $m$ is the capacity, and $c$ is the number of member variables. That
   is, the percent memory overhead is the fraction of space used to store non-element data. Record your answer and
   reasoning in `dynamic_array_gbo.md`.

<details>
<summary>Solution</summary>

1. If there are $n$ elements in the grow by one dynamic array, the size of the array is $n$. The capacity of the array
   is also $n$ because we only allocate enough space to store the elements. There are three member variables: the
   pointer `m_data`, the size `m_size` and the capacity `m_capacity`. Therefore, the percent memory overhead is
   $1 - \frac{n}{n + 3} = \frac{3}{n + 3}$. Taking the limit, we find
   that $\lim\limits_{n \rightarrow \infty} \frac{3}{n + 3} = 0$ so for large arrays, the memory overhead is effectively
   zero.

</details>

> [!IMPORTANT]
> Submit `dynamic_array_gbo.md` to Gradescope.

## Dynamic Array: Grow By Doubling

### Implementation

In this section, you will implement a dynamic array that doubles the size of the underlying array when there are
no empty slots available and `push_back` is called.

1. Complete `dynamic_array_gbd.cpp`.
2. Build `test_dynamic_array_gbd` from `dynamic_array_gbd.cpp` and `test_dynamic_array_gbd.cpp`.
3. Run `test_dynamic_array_gbd`. All tests should pass.

> [!IMPORTANT]
> Submit `dynamic_array_gbd.cpp` to Gradescope.

### Time Complexity Analysis

In this section, you will analyze the time complexity of your grow by doubling dynamic array. If you spend more than
5-10 minutes on this section, look at the solution provided below and move on.

1. Give a formula for the total number of store operations (`m_data[i] = v`) performed over $n$ calls to `push_back`.
   You should state an expression for $T(n)$ in terms of one or more summations and simplify. Record your answer and
   reasoning in `dynamic_array_gbd.md`.
2. Give a formula for the amortized time complexity (number of store operations) of `push_back` over $n$ calls.
   Record your answer and reasoning in `dynamic_array_gbd.md`.
3. Compare the amortized time complexity of `push_back` between the grow by one and the grow by doubling dynamic array.
   Which is better and why? Record your answer and reasoning in `dynamic_array_gbd.md`.

<details>
<summary>Solution</summary>

1. When `push_back` is called on an array of size $k$, there are two cases. When $k$ is not a power of two, there is
   still space in the underlying array. Therefore, we perform $1$ store to append the new element. When $k$ is a power
   of two, there is no space in the underlying array. We must copy $k$ elements from the old underlying array to the new
   underlying array. This requires $k$ stores. Then, we perform $1$ store to append the new element. To produce an array
   of size $n$ from an initially empty array, we must call `push_back` on an array of size $0$, $1$, $2$, all the way up
   to $n-1$. We can decompose the total number of stores into two summations. First, for each value of $k$, we always
   perform $1$ store to append the new element. Second, for each power of two value of $k$, we always perform $k$ stores
   to copy the old underlying array.
   Therefore, $T(n) = \sum\limits_{k=0}^{n - 1} 1 + \sum\limits_{i=0}^{\lfloor \lg (n - 1) \rfloor} 2^i = n + 2^{\lfloor \lg (n - 1) \rfloor + 1} = \Theta(n)$
2. If we perform $n$ calls to `push_back` on an initially empty array, we perform $\Theta(n)$ stores. The average
   number of stores per call is $\frac{1}{n} \cdot \Theta(n) = \Theta(1)$. Therefore, the
   amortized complexity of `push_back` is $\Theta(1)$.
3. The amortized complexity of the grow by doubling dynamic array is $\Theta(1)$ which is much faster than $\Theta(n)$.
   We should prefer the grow by doubling dynamic array.

</details>

> [!IMPORTANT]
> Submit `dynamic_array_gbd.md` to Gradescope.

### Space Complexity Analysis

In this section, you will analyze the space requirements of your grow by doubling dynamic array. If you spend more than
5-10 minutes on this section, look at the solution provided below and move on.

1. Give a formula for the worst-case percent memory overhead of a size $n$ instance of your grow by doubling dynamic
   array. Record your answer and reasoning in `dynamic_array_gbd.md`.
2. Give a formula for the best-case percent memory overhead of a size $n$ instance of your grow by doubling dynamic
   array. Record your answer and reasoning in `dynamic_array_gbd.md`.
3. Compare the percent memory overhead between the grow by one and the grow by doubling dynamic array. Which is better
   and why? Record your answer and reasoning in `dynamic_array_gbd.md`.

<details>
<summary>Solution</summary>

1. The worst-case percent memory overhead occurs just after resizing, that is, when $n = 2^k + 1$ for some $k \geq 0$.
   The capacity of the dynamic array is $2 \cdot 2^k$, and the size is $2^k + 1$. The dynamic array also contains three
   memory variables: the pointer `m_data`, the size `m_size` and the capacity `m_capacity`. The percent memory overhead
   is $1 - \frac{2^k + 1}{2 \cdot 2^k + 3} = 1 - \frac{n}{2 \cdot (n - 1) + 3} = \frac{n + 1}{2n + 1}$. Taking the
   limit, we find that $\lim\limits_{n \rightarrow \infty} \frac{n + 1}{2n + 1} = \frac{1}{2}$ so for large arrays, the
   worst-case memory overhead is 50%.

2. In the best-case, the dynamic array is completely full just before resizing. This is the same as with a grow by one
   dynamic array, so the percent memory overhead is $\frac{n}{n + 3}$, or zero for large arrays.

3. The memory overhead of the grow by one dynamic array is always better. In the best-case, the grow by doubling dynamic
   array matches the grow by one dynamic array, but in the worst case it uses twice the memory (50% overhead).

</details>

> [!IMPORTANT]
> Submit `dynamic_array_gbd.md` to Gradescope.

# Extra Practice

## Dynamic Array: Grow By Factor

Large companies, like Meta, employ algorithm engineers to optimize the performance of their standard library
implementation. At scale, making data structures like `std::vector` only 1-2% faster or more memory efficient can save
thousands or even millions of dollars per year. Possibly the most important factor influencing `std::vector`'s
performance is the resizing strategy. While doubling the size of the underlying array is far better than growing by
one, other resizing strategies are more efficient in practice.

### Reading

In this section, you will learn how Meta's algorithm engineers designed a custom dynamic array that is faster and more
memory efficient than `std::vector`.

1. Read up to (but not including) **Object Relocation**
   in [Meta's writeup on their custom dynamic array (vector) implementation](https://github.com/facebook/folly/blob/main/folly/docs/FBVector.md).

### Implementation

In this section, you will implement a dynamic array that grows the size of the underlying array by a given factor when
there are no empty slots available and `push_back` is called.

1. Complete `dynamic_array_gbf.cpp`.
2. Build `test_dynamic_array_gbf` from `dynamic_array_gbf.cpp` and `test_dynamic_array_gbf.cpp`.
3. Run `test_dynamic_array_gbf`. All tests should pass.

> [!IMPORTANT]
> Submit `dynamic_array_gbf.cpp` to Gradescope.

### Tuning

In this section, you will tune the implementation of your dynamic array to try to outperform `std::vector` on a simple
benchmark.

1. Read `bench_dynamic_array_gbf.cpp`.
2. Build `bench_dynamic_array_gbf` from `dynamic_array_gbf.cpp` and `bench_dynamic_array_gbf.cpp`. This program takes
   two command line arguments, `n`, the number of calls to `push_back`, and `growth_factor`, the resize factor, and
   outputs the runtime of your dynamic array and `std::vector`.
3. Experiment with different values of `n` and `growth_factor`. Can you outperform `std::vector`? Record your
   experiments in `dynamic_array_gbf.md`.

> [!IMPORTANT]
> Submit `dynamic_array_gbf.md` to Gradescope.

# Optional Advanced Topics

## Dynamic Array: Double-Ended

### Implementation

In this section, you will design and implement a dynamic array that supports $\mathcal{O}(1)$ amortized operations over
any sequence of calls to `push_front` and `push_back`.

1. Complete `dynamic_array_de.h` and `dynamic_array_de.cpp`.
2. Build `test_dynamic_array_de` from `dynamic_array_de.cpp` and `test_dynamic_array_de.cpp`.
3. Run `test_dynamic_array_de`. All tests should pass.

> [!IMPORTANT]
> Submit `dynamic_array_de.h` and `dynamic_array_de.cpp` to Gradescope.

### Time Complexity Analysis

In this section, you will analyze the amortized time complexity of your dynamic array.

1. Prove that the amortized time complexity of `push_front` and `push_back` is $\mathcal{O}(1)$ over any sequence of $n$
   array operations. Record your reasoning in `dynamic_array_de.md`.

> [!IMPORTANT]
> Submit `dynamic_array_de.md` to Gradescope.
