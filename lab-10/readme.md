# Lab 10 - Balanced Binary Search Trees

# Overview

In this lab, you will design, implement and analyze balanced binary search trees.

## Learning Objectives

By the end of this lab, you should be able to:

1. Implement abstract data types with balanced binary search trees.
2. Evaluate the performance characteristics of balanced binary search trees.

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

1. Create a new project called `csc212-lab-10` in your IDE.
2. Download all files from [the lab handout folder](handout) into the `csc212-lab-10` project.

> [!NOTE]
> To download all files from the repository, navigate to the root of the repository, click on the green **Code** button
> and select **Download Zip**.`

## Pseudo-Set

Pseudo-sets provide two main operations:

1. `insert` which adds a value into the set.
2. `contains` which checks if a value is in the set.

Unlike sets, pseudo-sets do not have an `erase` operation to remove values from the set.

### Implementation

In this section, you will design and implement a pseudo-set using a balanced binary search tree.

1. Complete `pseudoset.h` and `pseudoset.cpp`.
2. Build `test_pseudoset` from `pseudoset.cpp`, and `test_pseudoset.cpp`.
3. Run `test_pseudoset`. All tests should pass.

> [!IMPORTANT]
> Submit `pseudoset.h` and `pseudoset.cpp` to Gradescope.

### Theoretical Analysis

In this section, you will analyze the time complexity of your pseudo-set implementation. If you spend more than 5-10
minutes on this section, look at the solution provided below and move on.

1. Give tight bounds on the worst-case time complexity of `insert` and `contains` on a pseudo-set of size $n$. Justify
   your answer. Record your answer and justification under **Analysis** in `pseudoset.md`.

<details>
<summary>Solution</summary>

1. The pseudo-set is implemented as a red-black tree. In the worst-case, `insert` and `contains` must traverse the
   longest path from the root to a leaf. Since the height of a tree is defined as the length of the longest path from
   the root to a leaf, the number of operations performed by `insert` and `contains` is proportional to the height of
   the tree. Therefore, it suffices to analyze the height of a red-black tree on $n$ nodes. For simplicity, we assume
   $n$ is one less than a power of two.

   Let $h$ be the height and let $b$ be the black height of the tree. Since every path from the root to a leaf must
   contain exactly $b$ black nodes, the height is at least the black height, i.e., $b \leq h$. Likewise, since red nodes
   cannot have red children, any root to leaf path contains at most $b$ red nodes. Therefore, the height is at most
   twice the black height, i.e. $h \leq 2b$, since the longest root to leaf path contains $b$ black nodes and at
   most $b$ red nodes. Now, it suffices to analyze the black height $b$ of a red-black tree on $n$ nodes.

   The black height of the tree is greatest when all nodes in the tree are black. Since there are $n$ nodes in the tree,
   the black height of the tree is at most $\lg (n+1)$, since $n \leq 2^{\lg (n+1)} - 1$. The black height of the tree
   is least when every other level contains only red nodes. For each black level, the red level below it has exactly
   twice the number of nodes. So, for every black node, there are at most two red nodes. Thus, at least one third of the
   nodes are black, so the black height is at least $\lg \left(\frac{n}{3} + 1\right) \approx \frac{1}{3} \lg n$. Hence,
   $b = \Theta(\lg n)$, so $h = \Theta(\lg n)$, so `insert` and `contains` take $\Theta(\lg n)$ time.

</details> 

> [!IMPORTANT]
> Submit `pseudoset.md` to Gradescope.

# Extra Practice

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

<details>
<summary>Solution</summary>

1. The analysis is the same as the pseudo-set. All methods take $\Theta(\lg n)$ time.

</details>

> [!IMPORTANT]
> Submit `set.md` to Gradescope.
