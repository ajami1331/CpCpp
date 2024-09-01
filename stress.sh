#!/bin/bash

rm -rf stress_test
mkdir stress_test

g++ -std=c++17 -O2 -Wall submission.cpp -o stress_test/submission

g++ -std=c++17 -O2 -Wall brute.cpp -o stress_test/brute

g++ -std=c++17 -O2 -Wall gen.cpp -o stress_test/gen

for((i = 1; ; ++i)); do
    ./stress_test/gen $i > stress_test/input
    ./stress_test/submission < stress_test/input > stress_test/output
    ./stress_test/brute < stress_test/input > stress_test/correct
    if (! diff stress_test/output stress_test/correct); then
        echo "WA"
        cat stress_test/input
        break
    fi
    echo "Test $i passed"
done