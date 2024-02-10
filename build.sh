#!/bin/bash

FFLAGS="-cpp -Wall -Wno-tabs -fno-range-check"
#FFLAGS="-O3 -Wall -Wno-tabs"

gfortran -o rng rng.f90 $FFLAGS

