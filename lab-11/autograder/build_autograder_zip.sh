#!/bin/bash

rm -rf ./submission/ ./autograder.zip
mkdir -p ./submission/
zip -r autograder.zip .
rm -rf ./submission/