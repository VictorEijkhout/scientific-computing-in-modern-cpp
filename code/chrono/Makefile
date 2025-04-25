# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2019-2024 Victor Eijkhout
####
#### time stuff
####
################################################################

PROGRAMS = second clock simple
# C++20 not fully implemented
WRONGS = datetime

LANGUAGE = CXX
MODULES = 
INCLUDES =
EXTRA_LIBS =
RPATH =
include ../Make.inc
CPPSTANDARD = 20

RUNS =

RUNS += run_basicsecond run_millisecond
run_basicsecond run_millisecond : second
run_basicsecond :
	@./second | \
	awk '/basicseconds/ {p=0} p==1 {print} /BasicSeconds/ {p=1}'
run_millisecond :
	@./second | \
	awk '/milliseconds/ {p=0} p==1 {print} /MilliSeconds/ {p=1}'

RUNS += run_clock
run_clock : clock
run_clock :
	@./clock

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
