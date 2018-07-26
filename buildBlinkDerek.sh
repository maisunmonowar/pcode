#!/bin/bash

echo "Building the BlinkDerek"

g++ -O2 -Wall blinkDerek.cpp SimpleGPIO.cpp -o blinkDerek
