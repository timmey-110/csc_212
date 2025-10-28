#include "rna.h"

bool is_valid_rna_fold(const std::string &rna, const std::string &fold) {
    // TODO: Return `true` iff the fold `fold` given in dot-bracket notation is a valid fold for RNA base sequence
    // `rna`. A fold is valid iff the parentheses nesting is valid and all paired bases attract. The pairs ['A', 'U'],
    // ['G', 'C'] and ['G', 'U'] attract and all other pairs repel. Assume that `rna` is a valid RNA base sequence and
    // that `fold` is a sequence of '(', ')' and '.' of the same length as `rna`.
}
