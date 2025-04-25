# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2019-2024 Victor Eijkhout
####
#### makefile for random walks
####
################################################################

PROGRAMS = \
    walk_vec walk_arr walk_pass \
    variadic compare

LANGUAGE = CXX
MODE = seq
MODULES = 
ifeq "${TACC_FAMILY_COMPILER}" "gcc"
  OPTIONS = -Wno-psabi
endif
include ../Make.inc
CPPSTANDARD = 20

RUNS =

RUNS += run_vec run_arr run_pass
walk_vec.o walk_test.o : walk_lib_vec.cpp
walk_arr.o : walk_lib_arr.cpp
walk_pass.o : walk_lib_pass.cpp
run_vec : walk_vec
	@./walk_vec
run_arr : walk_arr
	@./walk_arr
run_pass : walk_pass
	@./walk_pass

RUNS += run_compare
run_compare : compare
	@./compare

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
