# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### copyright 2020-2025 Victor Eijkhout
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
####
################################################################

PROGRAMS = denorm nan round underflow overflow

LANGUAGE = CXX
include ../Make.inc
CPPSTANDARD = 23

##
## regression runs
##
RUNS =

RUNS += run_underflow
run_underflow : underflow
	@./underflow

RUNS += run_overflow
run_overflow : overflow
	@./overflow

RUNS += run_denorm
run_denorm : denorm
	@./denorm

RUNS += run_nan
run_nan : nan
	@./nan

RUNS += run_round
run_round : round
	@( echo .7 && echo .7 ) | ./round

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
