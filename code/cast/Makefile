# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2024 Victor Eijkhout
####
#### Examples of C++ casting
####
################################################################

PROGRAMS = longint intlong tobase toderived toderivedp opaque

LANGUAGE = CXX
include ../Make.inc

RUNS += longint
run_longint : longint
	@./longint

RUNS += intlong
run_intlong : intlong
	@./intlong

RUNS += toderived
run_toderived : toderived
	@./toderived

deriveright : toderived
RUNS += run_deriveright
run_deriveright : toderived
	@./toderived \
	| awk '/polymain/ {p=0} p==1 {print} /Polymain/ {p=1}'
derivewrong : toderived
RUNS += run_derivewrong
run_derivewrong : toderived
	@./toderived \
	| awk '/polybane/ {p=0} p==1 {print} /Polybane/ {p=1}'

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
