#!/bin/bash


echo "compiling precision example..."
cmd="g++ -ggdb precision_test.cpp -o precision_test_nosimd -O2 -std=c++11"
eval $cmd
echo "Done"
