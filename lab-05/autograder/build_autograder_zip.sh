#!/bin/bash

rm -rf submission
mkdir -p submission
cp ../handout/test_*.cpp ../handout/*.h ../handout/tracer.cpp ../bench_scheduler.cpp ./submission/
rm -f ./submission/scheduler.h
zip -r autograder.zip .
rm -rf submission
