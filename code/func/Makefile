# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2025 Victor Eijkhout
####
#### Makefile for code directory "func"
####
################################################################

PROGRAMS = twicein localparm newton passvalue passvaluelocal rhsref recur \
    swap divisible mult trail polyfun \
    bisect1 bisect2 bisect3

WRONGS = iterate

include ../Make.inc
LANGUAGE = CXX
CPPSTANDARD = 23

RUNS =

RUNS += run_localparm
run_localparm : localparm
	@./localparm

RUNS += run_twicein
run_twicein : twicein
	@./twicein

RUNS += run_passvalue run_passvaluelocal
run_passvalue : passvalue
	@./passvalue
run_passvaluelocal : passvaluelocal
	@./passvaluelocal

RUNS += run_rhsref
run_rhsref : rhsref
	@./rhsref

RUNS += run_swap
run_swap : swap
	@./swap

RUNS += run_divisible
run_divisible : divisible
	@for pair in 8,3 8,4 ; do \
	  echo $$pair | awk ' BEGIN{ FS="," } { print $$1 ; print $$2 } ' \
	 | ./divisible \
	 ; done

RUNS += run_recur
run_recur : recur
	@./recur

RUNS += run_mult
run_mult : mult
	@( echo 7 ; echo 5 ) | ./mult

RUNS += run_bisect1 run_bisect2 run_bisect3
run_bisect1 : bisect1
	@./bisect1
run_bisect2 : bisect2
	@./bisect2
run_bisect3 : bisect3
	@./bisect3

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
