#!/bin/bash

rm -rf submission
mkdir -p submission
cp ../handout/test_*.cpp ../handout/doctest.h ../handout/*.h ./submission/
rm -f ./submission/dynamic_array_de.h
zip -r autograder.zip .
rm -rf submission
