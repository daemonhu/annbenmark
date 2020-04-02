#!/bin/bash


echo "compiling precision example..."
cmd="g++ -ggdb -mavx -msse -msse2 -msse3 -mavx2 precision_test.cpp -o precision_test -O2 -std=c++11"
eval $cmd
echo "Done"
