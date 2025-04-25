# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2019-2025 Victor Eijkhout
####
#### random number examples
####
################################################################

PROGRAMS = crand xrand seed intrange shuffle permute static uniform \
    randname nball nballtemp singleton poisson
WRONGS = walk_test woisson

LANGUAGE = CXX
CPPSTANDARD = 23
INCLUDES = -I${TACC_CATCH2_INC} $(shell pkg-config --cflags cxxopts )
EXTRALIBS = -L${TACC_CATCH2_LIB} -lCatch2Main -lCatch2
RPATH = ${TACC_CATCH2_LIB} 

MODULES = catch2 cxxopts
include ../Make.inc

RUNS =

RUNS += run_nonrandom
run_nonrandom : static
	@./static \
	| awk '/nonrandom/ {p=0} p==1 {print} /Nonrandom/ {p=1}'
RUNS += run_truerandom
run_truerandom : static
	@./static \
	| awk '/truerandom/ {p=0} p==1 {print} /Truerandom/ {p=1}'

RUNS += run_shuffle
run_shuffle : shuffle
	@./shuffle

RUNS += run_xrand
run_xrand : xrand
	@./xrand

RUNS += run_nball
run_nball :: nball
	@out=ball.runout \
	 && rm -f $$out \
	 && for d in 2 3 4 5 6 7 8 ; do \
	      make --no-print-directory clean nball ECHO=${ECHO} OPTIONS=-DDIM=$$d \
	       && echo "Run nball d=$$d" \
	       && time -f 'Elapsed: %E' ./nball 2>&1 \
	            | tee nball$$d.out \
	            | tail -n 2 \
	            | tee -a $$out \
	    ; done 
.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
