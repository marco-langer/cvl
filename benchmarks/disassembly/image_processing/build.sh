#!/bin/bash
g++ -std=c++20 -O3 -Wall -Wextra -Wpedantic -mavx2 -c threshold.cpp -I../../../include && objdump -d threshold.o > dump.txt
