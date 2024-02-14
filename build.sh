#!/bin/bash

set -xe

FFLAGS="-cpp -Wall -Wno-tabs -fno-range-check"
#FFLAGS="-O3 -Wall -Wno-tabs"

# Build unit test exe
gfortran -o rfng rfng.f90 $FFLAGS -DRNG_FORT_TEST
./rfng  # run test

# Build lib
gfortran -c rfng.f90 $FFLAGS
ar -crs librfng.a rfng.o

# Build C++ demo
g++ -o demo demo.cpp -W librfng.a -lgfortran
#g++ -o demo demo.cpp -std=c++20 -W librfng.a -lgfortran
## `-std=c++20` requires g++ version ~12-ish
./demo

