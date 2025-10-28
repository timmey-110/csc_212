#!/bin/bash

rm -rf ./submission/ ./autograder.zip
mkdir -p ./submission/
cp ../handout/playlist_period.h ./submission/
cp ../handout/test_playlist_period.cpp ./submission/
cp ../handout/doctest.h ./submission/
cp ../handout/bug_bisect.h ./submission/
cp ../handout/test_bug_bisect.cpp ./submission/
cp ../handout/doctest.h ./submission/
cp ../handout/perfect_plunder.h ./submission/
cp ../handout/test_perfect_plunder.cpp ./submission/
cp ../handout/doctest.h ./submission/
cp ../handout/genetic_gap.h ./submission/
cp ../handout/test_genetic_gap.cpp ./submission/
cp ../handout/doctest.h ./submission/
cp ../handout/strategic_silicon.h ./submission/
cp ../handout/test_strategic_silicon.cpp ./submission/
cp ../handout/doctest.h ./submission/
zip -r autograder.zip .
rm -rf ./submission/