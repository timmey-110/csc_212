#!/bin/bash

rm -rf ./submission/ ./autograder.zip
mkdir -p ./submission/
cp ../handout/test_pseudoset.cpp ./submission/
cp ../handout/doctest.h ./submission/
cp ../handout/test_set.cpp ./submission/
cp ../handout/doctest.h ./submission/
zip -r autograder.zip .
rm -rf ./submission/