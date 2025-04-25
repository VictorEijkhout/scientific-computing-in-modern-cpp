# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2025 Victor Eijkhout
####
#### Examples of C++ enum
####
################################################################

PROGRAMS = enum enumclass spaced vnorm
WRONGS = enumnot

LANGUAGE = CXX
CPPSTANDARD = 23
include ../Make.inc
MODULES = rangev3
INCLUDES = -I${TACC_RANGEV3_INC}

RUNS = 

RUNS += run_enum
run_enum : enum
	@./enum

RUNS += run_spaced
run_spaced : spaced
	@./spaced

RUNS += run_vnorm
run_vnorm : vnorm
	@./vnorm

RUNS += run_enumclass
run_enumclass : enumclass
	@./enumclass

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
