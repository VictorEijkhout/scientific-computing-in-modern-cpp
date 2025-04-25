# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2025 Victor Eijkhout
####
#### integer computations
####
################################################################

PROGRAMS = divzero overflow sizeof unsigned
WRONGS = suffix

LANGUAGE = CXX
CPPSTANDARD = 23
include ../Make.inc

RUNS =

RUNS += run_div
run_div : divzero
	@echo 0 | ./divzero

RUNS += run_cmp
run_cmp : unsigned
	@./unsigned \
	| awk '/cmp/ {p=0} p==1 {print} /Cmp/ {p=1}'

RUNS += run_limit
run_limit : unsigned
	@./unsigned \
	| awk '/limit/ {p=0} p==1 {print} /Limit/ {p=1}'

RUNS += run_sizeof
run_sizeof : sizeof
	@./sizeof

RUNS += run_unsigned
run_unsigned : overflow
	@./overflow \
	| awk '/unsigned/ {p=0} p==1 {print} /Unsigned/ {p=1}'

RUNS += run_signed
run_signed : overflow
	@./overflow \
	| awk '/dosigned/ {p=0} p==1 {print} /Dosigned/ {p=1}'

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
