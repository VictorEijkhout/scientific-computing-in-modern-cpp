# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2025 Victor Eijkhout
####
################################################################

PROGRAMS = bitset bcd endian pattern 
WRONGS = vecbool

LANGUAGE = CXX
CPPSTANDARD = 23
# MODULES = catch2

include ../Make.inc

OPTIONS = -fext-numeric-literals

RUNS =

RUNS += run_bitset
run_bitset : bitset
	@./bitset

RUNS += run_encode
run_encode : bcd
	@./bcd \
	 | awk '/encode/ {p=0} p==1 {print} /Encode/ {p=1}'

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
