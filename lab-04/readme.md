# Lab 4 - Stacks and Queues

# Overview

In this lab, you will design, implement and analyze stacks and queues, and apply them to computational problems.

## Learning Objectives

By the end of this lab, you should be able to:

1. Implement the stack and queue abstract data types.
2. Evaluate the performance characteristics of stack and queue implementations.
3. Design efficient solutions to computational problems with stacks and queues.

Stacks and queues are abstract data types that describe how elements can be added and removed in a specific order. They
appear in many real-world problems, from parsing expressions to managing tasks.

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

1. Create a new project called `csc212-lab-04` in your IDE.
2. Download all files from [the lab handout folder](handout) into the `csc212-lab-04` project.

> [!NOTE]
> To download all files from the repository, navigate to the root of the repository, click on the green **Code** button
> and select **Download Zip**.`

## Stack

Stacks provide three main operations:

1. `push` which places an element on top of the stack
3. `pop` which removes the element on top of the stack.
2. `top` which returns the element on top of the stack

Stacks are often used to validate pairings, evaluate expressions and implement undo functionality.

### Implementation

In this section, you will design and implement a stack.

1. Complete `stack.cpp`.
2. Build `test_stack` from `stack.cpp`, and `test_stack.cpp`.
3. Run `test_stack`. All tests should pass.

> [!IMPORTANT]
> Submit `stack.cpp` to Gradescope.

### Theoretical Analysis

In this section, you will analyze the time complexity of your stack implementation. If you spend more than 5-10 minutes
on this section, look at the solution provided below and move on.

1. Give a formula $T(n)$ for the number of array accesses performed when calling `top` on a stack containing $n$
   elements. Give a $\Theta$ bound on $T(n)$. Record your answer in `stack.md`.
2. Give a formula for the number of array accesses performed when calling `pop` on a stack containing $n$ elements. Give
   a $\Theta$ bound on $T(n)$. Record your answer in `stack.md`.
3. Give a formula $T(n)$ for the number of array accesses performed when calling `push` amortized over a sequence
   of $n$ calls to `push` on an initially empty stack. Give a $\Theta$ bound on $T(n)$ Record your answer in `stack.md`.

<details>
<summary>Solution</summary>

1. `top` perform one array access regardless of the stack's size. Therefore, $T(n) = 1$ and $T(n) = \Theta(1)$.
2. `pop` performs zero array accesses regardless of the stack's size. Therefore, $T(n) = 0$ and $T(n) = \Theta(0)$.
   There are two interesting points here. First, choosing to count the number of array accesses performed by `pop`
   does not yield a reasonable performance model, since `pop` never accesses the underlying array. In a reasonable
   model, we should expect `pop` to take $\Theta(1)$ time. Second, $\Theta(0) \neq \Theta(1)$. Doing no work is
   different from doing a constant amount of work. Try working with the definition of $\Theta$ to see why this is true.
3. The analysis of `push` is the same as the corresponding dynamic array implementation. If you used grow-by-one, `push`
   runs in $\Theta(n)$ and $\Theta(n)$ amortized time, while if you used grow-by-doubling, `push` runs in $\Theta(1)$
   amortized time. See the dynamic array lab for a detailed analysis.

</details>

> [!IMPORTANT]
> Submit `stack.md` to Gradescope.

## Queue

Queues provide three main operations:

1. `push` which adds an element to the back of the queue
3. `pop` which removes the element at the front of the queue.
2. `front` which returns the element at the front of the queue

### Implementation

In this section, you will design and implement a queue.

1. Complete `queue.cpp`.
2. Build `test_queue` from `queue.cpp`, and `test_queue.cpp`.
3. Run `test_queue`. All tests should pass.

> [!IMPORTANT]
> Submit `queue.cpp` to Gradescope.

### Theoretical Analysis

In this section, you will analyze the time complexity of your queue implementation. If you spend more than 5-10 minutes
on this section, look at the solution provided below and move on.

1. Give a formula $T(n)$ for the number of array accesses performed when calling `front` on a queue containing $n$
   elements. Give a $\Theta$ bound on $T(n)$. Record your answer in `queue.md`.
2. Give a formula $T(n)$ for the number of array accesses performed when calling `pop` amortized over a sequence
   of $n$ calls to `pop` on a queue initially containing $n$ elements. Give a $\Theta$ bound on $T(n)$ Record your
   answer in `queue.md`.
3. Give a formula $T(n)$ for the number of array accesses performed when calling `push` amortized over a sequence
   of $n$ calls to `push` on an initially empty queue. Give a $\Theta$ bound on $T(n)$ Record your answer in `queue.md`.

<details>
<summary>Solution</summary>

1. `front` perform one array access regardless of the queue's size. Therefore, $T(n) = 1$ and $T(n) = \Theta(1)$.
2. The analysis depends on your implementation. If you remove from the front of the underlying array, each call to pop
   costs $k - 1$ array accesses, where $k$ is the size of the queue. If we perform $n$ calls to `pop` on a queue of
   size $n$, we pop queues of size $1$, $2$, all the way up to $n$.
   Therefore,

   $$T(n) = \frac{1}{n} \sum\limits_{k=1}^{n} (k - 1) = \frac{n-1}{2}$$

   so $T(n) = \Theta(n)$. If you remove
   from the back of the underlying array, the analysis is the same as the stack's `pop`, so $T(n) = \Theta(0)$.
3. The analysis depends on your implementation. If you add to the front of the underlying array, the analysis is similar
   to `pop` on a queue that removes from the front of the underlying array. You should find that $T(n) = \Theta(n)$. If
   you add to the back of the underlying array, the analysis is the same as the corresponding dynamic array
   implementation. You should find that $T(n) = \Theta(n)$ or $T(n) = \Theta(1)$ amortized. See the dynamic array lab
   for a detailed analysis.

</details>

> [!IMPORTANT]
> Submit `queue.md` to Gradescope.

# Extra Practice

## Fully Parenthesized Infix Expression Evaluation

A fully parenthesized infix expression is an arithmetic expression in infix notation (operators are written between
operands) where every single operation is explicitly enclosed in parentheses, so the order of evaluation is unambiguous
without relying on operator precedence or associativity rules.

For example, `(1 + (2 * -3))` is a fully parenthesized infix expression while `(1 - 2) / 3` is not.

### Implementation

In this section, you will implement a two-stack algorithm to evaluate fully parenthesized infix expressions.

The two-stack algorithm consumes the input expression from left to right, maintaining a stack of operands and a stack of
operators. For each character in the expression, the algorithm performs the following steps:

* If the character is a left parenthesis or a whitespace, ignore it.
* If the character is an operand, push it to the operand stack.
* If the character is an operator, push it to the operator stack.
* If the character is a right parenthesis, pop an operator from the operator stack, pop the required number of operands
  from the operands stack, evaluate the operation, and push the result back onto the operand stack.

After processing the entire expression, the result should be the only element left on the operand stack. All input
expressions are valid and fully parenthesized, so there is no need to check for errors.

The input operands will be integers (possibly negative), and the operators will be `+`, `-`, `*` and `/`. Treat `/` as
C++ integer division.

1. Complete `eval.cpp`.
2. Build `test_eval` from `eval.cpp`, and `test_eval.cpp`.
3. Run `test_eval`. All tests should pass.

> [!IMPORTANT]
> Submit `eval.cpp` to Gradescope.

## RNA Secondary Structure Validation

RNA is a molecule made up of a sequence of four bases: Adenine (`A`), Uracil (`U`), Guanine (`G`), and Cytosine (`C`).
RNA is usually single-stranded, but it can fold back onto itself to form secondary structures, where certain bases pair
with each other. Biological scientists care about how RNA folds, since the folded structure determines how it functions
in biological systems.

To understand this, consider a rope with several strong magnets attached along its length. When the role is dropped into
a pile, the magnets attract or repel each other, causing the rope to fold and twist into a shape. Some magnets stick
together, forming a pair, while other magnets stay apart. RNA folds exactly like the rope: the magnets are the bases
that pair with each other and stick together.

The three pairs

* `A` and `U`
* `G` and `C`
* `G` and `U`

stick together. All other pairs of bases repel each other.

Dot-bracket notation is a way of describing which bases in an RNA base sequence are paired with each other with a
sequence of dots and nested parenthesis. Paired parenthesis represent paired bases, while dots represent unpaired
bases. For example, the following RNA sequence and dot-bracket fold indicates that the first `G` is paired with the last
`U` and that the first `C` is paired with the last `A`.

```
GCGGAU
((..))
```

Since `C` and `A` repel each other and the above fold pairs `C` and `A`, it is physically impossible. Parentheses must
be correctly nested. For example,

```
GCGGAU
)(....
```

is impossible since the parentheses are not correctly nested. The following two folds

```
GCGGAU
.().()
(....)
```

are possible since all the paired bases stick together and the parentheses are correctly nested. In RNA secondary
structure validation, you must determine whether an RNA fold (secondary structure) represented dot-bracket notation is
physically possible or not.

### Implementation

In this section, you will design and implement an algorithm to perform RNA secondary structure validation.

1. Complete `rna.cpp`.
2. Build `test_rna` from `rna.cpp`, and `test_rna.cpp`.
3. Run `test_rna`. All tests should pass.

> [!IMPORTANT]
> Submit `rna.cpp` to Gradescope.

# Optional Advanced Topics

## Deque

Deques (double-ended queues) generalize stacks and queues. Deques provide six main operations:

1. `push_front` which adds an element to the front of the deque
2. `push_back` which adds an element to the back of the deque
3. `pop_front` which removes the element at the front of the deque
4. `pop_back` which removes the element at the back of the deque
5. `front` which returns the element at the front of the deque
6. `back` which returns the element at the back of the deque

### Implementation

In this section, you will design and implement a deque.

1. Complete `deque.h` and `deque.cpp`. Your implementation should provide $\mathcal{O}(1)$ or $\mathcal{O}(1)$ amortized
   complexity for every deque operation over any sequence of $n$ deque operations.
2. Build `test_deque` from `deque.cpp`, and `test_deque.cpp`.
3. Run `test_deque`. All tests should pass.

> [!IMPORTANT]
> Submit `deque.h` and `deque.cpp` to Gradescope.

### Theoretical Analysis

In this section, you will analyze the time complexity of your deque implementation.

1. Prove that your implementation provides $\mathcal{O}(1)$ or $\mathcal{O}(1)$ amortized complexity for every deque
   operation over any sequence of $n$ operations. Record your answer in `deque.md`.

> [!IMPORTANT]
> Submit `deque.md` to Gradescope.
