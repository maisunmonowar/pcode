#!/bin/bash

echo "Building the test"

g++ -O2 -Wall test.cpp SimpleGPIO.cpp -o test
