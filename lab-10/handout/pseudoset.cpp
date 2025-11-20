#include "pseudoset.h"

// NOTE:
// 1. Red nodes are denoted with {x} where x is the value stored in the node.
// 2. Black nodes are denoted with [x] where x is the value stored in the node.
// 3. Subtrees are denoted with (A) where A is the name of the subtree.

PseudoSet::Node *PseudoSet::fix_red_left_left(Node *root) {
    // TODO: Fix red-child left-left violation.

    // Input:
    //            [z]
    //       {y}       (D)
    //   {x}     (C)
    // (A) (B)

    // Output:
    //            {y}
    //       [x]       [z]
    //    (A)   (B) (C)   (D)
}

PseudoSet::Node *PseudoSet::fix_red_left_right(Node *root) {
    // TODO: Fix red-child left-right violation.

    // Input:
    //            [z]
    //       {x}       (D)
    //   (A)     {y}
    //         (B) (C)

    // Output:
    //            {y}
    //       [x]       [z]
    //    (A)   (B) (C)   (D)
}

PseudoSet::Node *PseudoSet::fix_red_right_left(Node *root) {
    // TODO: Fix red-child right-left violation.

    // Input:
    //            [x]
    //       (A)       {z}
    //             {y}     (D)
    //           (B) (C)

    // Output:
    //            {y}
    //       [x]       [z]
    //    (A)   (B) (C)   (D)
}

PseudoSet::Node *PseudoSet::fix_red_right_right(Node *root) {
    // TODO: Fix red-child right-right violation.

    // Input:
    //            [x]
    //       (A)       {y}
    //             (B)     {z}
    //                   (C) (D)

    // Output:
    //            {y}
    //       [x]       [z]
    //    (A)   (B) (C)   (D)
}

PseudoSet::Node *PseudoSet::balance(Node *root) {
    // TODO: Ensure the red-black tree rooted by `root` is valid after insertion. Return the new root after balancing.

    // The possible red-child violations are:
    // 1. `root` has a red left child with a red left child.
    // 2. `root` has a red left child with a red right child.
    // 3. `root` has a red right child with a red left child.
    // 4. `root` has a red right child with a red right child.
    // At most one violation can occur for any given `root`. It's possible for no violations to occur.

    // Use `fix_red_left_left`, `fix_red_left_right`, `fix_red_right_left` and `fix_red_right_right`.
}

PseudoSet::Node *PseudoSet::insert(Node *root, int value) {
    // TODO: Insert `value` into the red-black tree rooted by `root`. If `value` already exists in the tree, do nothing.
    // Return the new root of the red-black tree after insertion. Use `balance` to fix any red-child violations.
}

PseudoSet::Node *PseudoSet::find(Node *root, int value) {
    // TODO: Return the node with `value` value in the red-black tree rooted by `root`. If `value` does not exist in the
    // tree, return `nullptr`.
}

void PseudoSet::destroy(Node *root) {
    // TODO: Deallocate the red-black tree rooted by `root`.
}

PseudoSet::PseudoSet() {
    // TODO: Initialize an empty red-black tree.
}

PseudoSet::~PseudoSet() {
    // TODO: Deallocate dynamically allocated memory. Use `destroy(Node*)`.
}

void PseudoSet::insert(int value) {
    // TODO: Insert `value` into the red-black tree. If `value` already exists in the tree, do nothing. Use
    // `insert(Node*, int)`
}

bool PseudoSet::contains(int value) const {
    // TODO: Return `true` iff `value` exists in the red-black tree. Use `find(Node*, int)`.
}

size_t PseudoSet::size() const {
    // TODO: Return the number of elements in the red-black tree.
}
