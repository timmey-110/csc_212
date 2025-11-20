#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "rna.h"

TEST_CASE("Empty sequence") {
    CHECK(is_valid_rna_fold("", ""));
}

TEST_CASE("Single unpaired base") {
    CHECK(is_valid_rna_fold("A", "."));
    CHECK(is_valid_rna_fold("G", "."));
}

TEST_CASE("Simple valid pairs") {
    CHECK(is_valid_rna_fold("AU", "()"));
    CHECK(is_valid_rna_fold("UA", "()"));
    CHECK(is_valid_rna_fold("GC", "()"));
    CHECK(is_valid_rna_fold("CG", "()"));
    CHECK(is_valid_rna_fold("GU", "()"));
    CHECK(is_valid_rna_fold("UG", "()"));
}

TEST_CASE("Simple invalid pairs") {
    CHECK(!is_valid_rna_fold("AA", "()"));
    CHECK(!is_valid_rna_fold("AC", "()"));
    CHECK(!is_valid_rna_fold("GA", "()"));
}

TEST_CASE("Unpaired bases with valid pairs") {
    CHECK(is_valid_rna_fold("AUCG", "()()"));
}

TEST_CASE("Nested valid folds") {
    CHECK(is_valid_rna_fold("AUGC", "(())"));
    CHECK(is_valid_rna_fold("GCAU", "(())"));
    CHECK(is_valid_rna_fold("GUAU", "(())"));
    CHECK(is_valid_rna_fold("AUGCGU", "((()))"));
}

TEST_CASE("Invalid nested folds") {
    CHECK(!is_valid_rna_fold("AUGC", "(()("));
    CHECK(!is_valid_rna_fold("GCGA", "(())"));
    CHECK(!is_valid_rna_fold("GUGA", "(())"));
}

TEST_CASE("Long valid fold") {
    std::string rna = "GCGGAUUUAGCUCAGUUGGG";
    std::string fold = "(((((.....))))).....";
    CHECK(is_valid_rna_fold(rna, fold));
}

TEST_CASE("Long invalid fold") {
    std::string rna = "GCGGAUUUAGCUCAGUUGGG";
    std::string fold = "(((((.....)))))...()";
    CHECK(!is_valid_rna_fold(rna, fold));
}
