# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2021-2024 Victor Eijkhout
####
#### makefile for the Eigen library
####
################################################################

PROGRAMS = gemm matvec invert \
    penrose

LANGUAGE = CXX
INCLUDES = -I${TACC_EIGEN_INC}
EXTRALIBS =  
include ../Make.inc
CPPSTANDARD = 23
MODULES = eigen

RUNS =


.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
