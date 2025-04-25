# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2021-2024 Victor Eijkhout
####
#### makefile for Catch2 unit testing
####
################################################################

PROGRAMS = require false sqrt tdd

LANGUAGE = CXX
INCLUDES = -I${TACC_CATCH2_INC}
EXTRALIBS = -L${TACC_CATCH2_LIB} -lCatch2Main -lCatch2
RPATH = ${TACC_CATCH2_LIB}
MODULES = catch2
include ../Make.inc

RUNS =

RUNS += run_false
run_false : false
	@./false | grep -v "make\["

RUNS += run_require
run_require : require
	@./require [1]

RUNS += run_requirerr
run_requirerr : require
	@./require [2] \
	| awk '/FAILED/ {p=1} p==1 {print}'

RUNS += run_requireven
run_requireven : require
	@./require [3]

RUNS += run_requirgen
run_requirgen : require
	@./require [4]

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
