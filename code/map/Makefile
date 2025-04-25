# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2018-2025 Victor Eijkhout
####
#### map exercises
####
################################################################

PROGRAMS = countint

LANGUAGE = CXX
include ../Make.inc
CPPSTANDARD = 23

RUNS =

RUNS += run_countint
run_countint : countint
	@./countint

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
