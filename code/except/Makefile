# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2024 Victor Eijkhout
####
################################################################

PROGRAMS = except1 except2 exceptroot exceptfp \
    exceptconstruct boundthrow catchbounds what \
    errno
WRONGS = location

LANGUAGE = CXX
MODULES = catch2
INCLUDES = -I${TACC_CATCH2_INC}
EXTRALIBS = -L${TACC_CATCH2_LIB} -lCatch2Main -lCatch2
RPATH = ${TACC_CATCH2_LIB}

include ../Make.inc

.PHONY: noerrno
noerrno :
	@rm -f errno errno.o
	@make --no-print-directory errno \
	    OPTIONS="-fno-math-errno -ffast-math"

RUNS =

RUNS += run_boundthrow
run_boundthrow : boundthrow
	@./boundthrow 2>&1 | grep -v make

RUNS += run_catchbounds
run_catchbounds : catchbounds
	@./catchbounds

RUNS += run_tdd
run_tdd : tdd
	@./tdd

RUNS += run_what
run_what : what
	@./what

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
