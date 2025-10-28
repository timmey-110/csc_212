# Lab 5 - Priority Queues, Heaps, and Heapsort

# Overview

In this lab, you will implement priority queues with binary heaps, analyze their time complexity and implement heapsort.

## Learning Objectives

By the end of this lab, you should be able to:

1. Implement the priority queue abstract data type with a binary heap.
2. Implement heapsort with a binary heap.
3. Evaluate the performance characteristics of priority queue implementations.
4. Design efficient solutions to computational problems with priority queues.

Certain problems can be solved by **greedy algorithms**, or algorithms that always select the "best" possible option
given some local information. A fantastic variety of real-world algorithms are greedy, including GPS routing, data
compression, VLSI design, and genome assembly. Greedy algorithms often maintain all possible options in a priority
queue, allowing efficient access to the "best" option. Binary heaps provide an efficient implementation of the priority
queue interface.

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

1. Create a new project called `csc212-lab-05` in your IDE.
2. Download all files from [the lab handout folder](handout) into the `csc212-lab-05` project.

> [!NOTE]
> To download all files from the repository, navigate to the root of the repository, click on the green **Code** button
> and select **Download Zip**.`

## Max-Priority Queue

Max-priority queues provide three main operations:

1. `push` which adds an element into the max-priority queue.
2. `pop` which removes the element with the maximum priority value from the max-priority queue.
3. `top` which returns the element with the maximum priority value in the max-priority queue.

### Implementation

In this section, you will implement a max-priority queue.

1. Complete `max_priority_queue.cpp`.
2. Build `test_max_priority_queue` from `max_priority_queue.cpp`, and `test_max_priority_queue.cpp`.
3. Run `test_max_priority_queue`. All tests should pass.

> [!IMPORTANT]
> Submit `max_priority_queue.cpp` to Gradescope.

### Theoretical Analysis

In this section, you will analyze the time complexity of your max-priority queue implementation. If you spend more than
5-10 minutes on this section, look at the solution provided below and move on.

1. Give a bound on $S(n)$ for the worst-case number of swaps performed when calling `heapify_down` on the root of a
   max-heap containing $n$ nodes. Record your answer under **Heapify Down Analysis** in `max_priority_queue.md`.
2. Give a bound on $T(n)$ for the worst-case number of swaps performed when calling the max-priority queue
   vector constructor (AKA `build_heap`) on a vector of $n$ elements. Give a $\mathcal{O}$ bound on $T(n)$. Record your
   answer under **Build Heap Analysis** in `max_priority_queue.md`.

<details>
<summary>Solution</summary>

1. A max-heap containing $n$ nodes has height at most $\lg n$. In the worst case, we swap a height $\lg n$ node with
   a height $\lg n - 1$ node, and a height $\lg n - 1$ node with a height $\lg n - 2$ node, and so on down to swapping a
   height $1$ node with a height $0$ node, for maximum of $\lg n$ swaps. Hence, $S(n) \leq \lg n$.
2. Instead of analyzing $T(n)$, we will analyze $T(2^{h+1} - 1)$ where $h = \lceil \lg n \rceil$.
   Since $n \leq 2^{\lceil \lg n \rceil + 1} - 1$, $T(n) \leq T(2^{h+1} - 1)$. This choice of $h$ yields a perfect (all
   levels contain the maximum number of nodes) binary tree of height $h$, which simplifies the analysis. There
   are $2^{h-k}$ nodes with height $k$. By the previous analysis, calling `heapify_down` on a node of height $k$
   performs at most $k$ swaps. Therefore, by summing over all heights (values
   of $k$), $T(n) \leq \sum\limits_{k=0}^{h} k 2^{h - k} = 2^{h + 1} - h - 2 = \mathcal{O}(n)$.

</details>

> [!IMPORTANT]
> Submit `max_priority_queue.md` to Gradescope.

## Heapsort

Heapsort is a simple priority queue-based sorting algorithm:

1. Insert the elements into a max-heap.
2. Remove the maximum element until all elements are in sorted order.

Different priority queue implementations yield different sorting algorithms. For example, replacing the max-heap with an
unsorted array yields selection sort.

### Implementation

In this section, you will implement heapsort.

1. Complete `heapsort.cpp`.
2. Build `test_heapsort` from `heapsort.cpp`, and `test_heapsort.cpp`.
3. Run `test_heapsort`. All tests should pass.

### Theoretical Analysis

In this section, you will analyze the time complexity of your heapsort implementation. If you spend more than
5-10 minutes on this section, look at the solution provided below and move on.

1. Give a bound on $T(n)$ for the worst-case number of swaps performed when calling `heapsort` on a vector of $n$
   elements. Give a $\mathcal{O}$ bound on $T(n)$. Record your answer under **Heapsort Analysis** in `heapsort.md`.

<details>
<summary>Solution</summary>

1. First, we build a max-heap using $\mathcal{O}(n)$ swaps. Then, we call `pop` on heaps of size $n$, $n-1$, $n-2$, and
   so on, down to $1$. A call to `pop` on a max-heap of size $k$ requires at most $\lg k$ swaps. Therefore, by summing
   over the cost of each call to `pop`, we
   find $T(n) = \mathcal{O}(n) + \sum\limits_{k=1}^{n} \lg k \leq \mathcal{O}(n) + \sum\limits_{k=1}^{n} \lg n = \mathcal{O}(n \lg n)$.
   Can you show that $T(n) = \Omega(n \lg n)$, assuming the input vector contains distinct integers?

</details>

# Extra Practice

## Min-Priority Queue

Min-priority queues provide three main operations:

1. `push` which adds an element into the min-priority queue.
2. `pop` which removes the element with the minimum priority value from the min-priority queue.
3. `top` which returns the element with the minimum priority value in the min-priority queue.

### Implementation

In this section, you will implement a min-priority queue.

1. Complete `min_priority_queue.cpp`.
2. Build `test_min_priority_queue` from `min_priority_queue.cpp`, and `test_min_priority_queue.cpp`.
3. Run `test_min_priority_queue`. All tests should pass.

> [!IMPORTANT]
> Submit `min_priority_queue.cpp` to Gradescope.

### Theoretical Analysis

In this section, you will analyze the time complexity of your min-priority queue implementation. If you spend more than
5-10 minutes on this section, look at the solution provided below and move on.

1. Give a bound on $S(n)$ for the worst-case number of swaps performed when calling `heapify_down` on the root of a
   min-heap containing $n$ nodes. Record your answer under **Heapify Down Analysis** in `min_priority_queue.md`.
2. Give a bound on $T(n)$ for the worst-case number of swaps performed when calling the min-priority queue
   vector constructor (AKA `build_heap`) on a vector of $n$ elements. Give a $\mathcal{O}$ bound on $T(n)$. Record your
   answer under **Build Heap Analysis** in `min_priority_queue.md`.

<details>
<summary>Solution</summary>

1. The analysis is the same as the max-priority queue.
2. The analysis is the same as the max-priority queue.

</details>

> [!IMPORTANT]
> Submit `min_priority_queue.md` to Gradescope.

# Optional Advanced Topics

## Online Task Scheduling

Operating systems, cloud computing systems and high-performance compute clusters receive programs (tasks) to execute.
**Schedulers** determine when and how many resources to allocate to each task. Schedulers balance multiple tradeoffs to 
attain near-optimal resource allocation. 

### Implementation

In this section, you will implement an online algorithm to schedule tasks. You will receive tasks one-by-one, and at 
each timestep, must decide which task to execute. Your objective is to minimize the **total weighted delay**. Let $p_i$ 
be the priority of the $i$-th task and $d_i$ be the delay (time from arrival to completion) of the $i$-th task. Then, 
the total weighted delay is 

$$\sum\limits_{i = 1}^n p_i \cdot d_i$$

1. Complete `scheduler.h` and `scheduler.cpp`. Ensure `push` and `pop_next` run in $\mathcal{O}(\lg n)$ time.

> [!IMPORTANT]
> Submit `scheduler.h` and `scheduler.cpp` to Gradescope.

### Empirical Analysis

In this section, you will empirically analyze the performance of your online scheduling algorithm. 

1. Build `bench_scheduler` from `scheduler.cpp`, `tracer.cpp` and `bench_scheduler.cpp`.
2. Run `bench_scheduler`. What is total weighted delay? Describe your algorithm and record the total weighted delay 
   under **Initial Scheduler** in `scheduler.md`.
3. Revise your algorithm to decrease the total weighted delay. Describe your new algorithm and record the new total 
   weighted delay under **Final Scheduler** in `scheduler.md`.

> [!IMPORTANT]
> Submit `scheduler.h`, `scheduler.cpp` and `scheduler.md` to Gradescope.
