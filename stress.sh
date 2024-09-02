#!/bin/bash

rm -rf random_tests
mkdir random_tests

g++ -std=c++17 -O2 -Wall submission.cpp -o random_tests/submission

g++ -std=c++17 -O2 -Wall brute.cpp -o random_tests/brute

g++ -std=c++17 -O2 -Wall gen.cpp -o random_tests/gen

for((i = 1; ; ++i)); do
    ./random_tests/gen $i > random_tests/input
    ./random_tests/submission < random_tests/input > random_tests/output
    ./random_tests/brute < random_tests/input > random_tests/correct
    if (! diff random_tests/output random_tests/correct); then
        echo "WA"
        cat random_tests/input
        break
    fi
    echo "Test $i passed"
done