#!/bin/bash

# Compiling the C++ code
g++ -o sorting sorting.cpp

# Runnning the C++ code to generate results.dat
./sorting

# Executing the Gnuplot script
gnuplot linegraph.gnu
