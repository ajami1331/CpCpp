#!/bin/bash
set -e
echo "Starting formatting"
find . -iname '*.cpp' -o -iname '*.h' -o -iname '*.h.in' | xargs clang-format -i --style=file
echo "Formatting completed"