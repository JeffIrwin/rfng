#!/bin/bash

set -xe

FFLAGS="-cpp -Wall -Wno-tabs -fno-range-check"
#FFLAGS="-O3 -Wall -Wno-tabs"

# Build unit test exe
gfortran -o rng rng.f90 $FFLAGS -DRNG_FORT_TEST
./rng

# Build lib
gfortran -c rng.f90 $FFLAGS
ar -crs librng.a rng.o

