#!/bin/bash

rm -rf submission
mkdir -p submission
cp ../handout/test_*.cpp ../handout/doctest.h ./submission/
zip -r autograder.zip .
rm -rf submission
