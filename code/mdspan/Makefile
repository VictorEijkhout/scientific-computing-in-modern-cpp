# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2019-2024 Victor Eijkhout
####
#### C++23 mdspan tests
####
################################################################

PROGRAMS = index2 index2std diff1d diff2d \
    midpoint transpose
WRONGS = spanclass spanconst

LANGUAGE = CXX
MODULES = mdspan rangev3
# rangev3
INCLUDES = -I${TACC_MDSPAN_INC} -I${TACC_RANGEV3_INC}
OPTIONS = -Wno-comma-subscript
include ../Make.inc
CPPSTANDARD = 23

RUNS =

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
