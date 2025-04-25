# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2019-2025 Victor Eijkhout
####
#### C++20 span & C++23 mdspan tests
####
################################################################

PROGRAMS = spanpass subspan const

LANGUAGE = CXX
include ../Make.inc
CPPSTANDARD = 23

RUNS =

RUNS += run_subspan1 run_subspan2
run_subspan1 run_subspan2 : subspan
run_subspan1 :
	@./subspan \
	| awk '/span1/ {p=0} p==1 {print} /SPAN1/ {p=1}'
run_subspan2 :
	@./subspan \
	| awk '/span2/ {p=0} p==1 {print} /SPAN2/ {p=1}'

RUNS += run_spanpass
run_spanpass : spanpass
	@./spanpass

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
