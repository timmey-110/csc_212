#!/bin/bash

rm -rf submission
mkdir -p submission
cp ../handout/test_*.cpp ../handout/*.h ./submission/
rm ./submission/deque.h
zip -r autograder.zip .
rm -rf submission
