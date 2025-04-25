# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2024 Victor Eijkhout
####
#### Makefile for union-like stuff: optional, variant
####
################################################################

PROGRAMS = intdoublestring matvisit visit \
    quadratic quadtest abctuple \
    optional optroot expected
WRONG =  poly

INCLUDES = -I${TACC_CATCH2_INC}
EXTRALIBS = -L${TACC_CATCH2_LIB} -lCatch2Main -lCatch2
RPATH = ${TACC_CATCH2_LIB}
include ../Make.inc
CPPSTANDARD = 23
LANGUAGE = CXX
MODULES = catch2

RUNS = 

RUNS += run_intdoublestring
run_intdoublestring : intdoublestring
	@./intdoublestring

RUNS += run_visit
run_visit : visit
	@./visit

RUNS += run_quadratic
run_quadratic : quadratic
	@./quadratic
quadratic.o :: quadlib.hpp

RUNS += run_quadtest
run_quadtest : quadtest
	@./quadtest
quadtest.o :: quadlib.hpp

RUNS += run_optional
run_optional : optional
	@./optional \
	| awk '/badvalue/ {p=0} p==1 {print} /BadValue/ {p=1}'

RUNS += run_optroot run_monroot
run_optroot : optroot
	@./optroot
run_monroot : optroot
	@./optroot \
	| awk '/monadic/ {p=0} p==1 {print} /Monadic/ {p=1}'

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
