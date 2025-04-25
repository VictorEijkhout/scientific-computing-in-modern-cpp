# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2025 Victor Eijkhout
####
#### makefile for geometry examples and exercises
####
################################################################

PROGRAMS = function linear rotate halfway \
    pointclass pointdist pointstruct pointconstruct pointinit pointinitxy pointprivate \
    pointfunc pointscale pointscaleby pointdefault pointtemplate \
    compare curlytest overload \
    rectangle rectcurly rectangle2 square set
#function
WRONGS = pointaggregate 

LANGUAGE = CXX
include ../Make.inc
CPPSTANDARD = 23

.PHONY: ${RUNS}
RUNS += run_pointinitxy
run_pointinitxy : pointinitxy
	@./pointinitxy
RUNS += run_pointstruct
run_pointstruct : pointstruct
	@./pointstruct
RUNS +=  run_pointconstruct 
run_pointconstruct : pointconstruct
	@./pointconstruct
RUNS += run_pointfunc run_pointfuncout
run_pointfunc : pointfunc
	@./pointfunc \
	| awk '/simple/ {p=0} p==1 {print} /Simple/ {p=1}'
run_pointfuncout : pointfunc
	@./pointfunc \
	| awk '/cout/ {p=0} p==1 {print} /Cout/ {p=1}'

RUNS += run_pointclass
run_pointclass : pointclass
	@./pointclass

RUNS += run_pointscale run_pointmult
run_pointscale : pointscale
	@./pointscale \
	| awk '/scale2/ {p=0} p==1 {print} /Scale2/ {p=1}'
run_pointmult : pointscale
	@./pointscale \
	| awk '/mult2/ {p=0} p==1 {print} /Mult2/ {p=1}'
RUNS += run_pointscaleby
run_pointscaleby : pointscaleby
	@./pointscaleby

RUNS += run_rectangle
run_rectangle : rectangle
	@./rectangle

RUNS += run_rectangle2
run_rectangle2 : rectangle2
	@./rectangle2

RUNS += run_translate
run_translate : halfway
	@./halfway \
	| awk '/translate/ {p=0} p==1 {print} /Translate/ {p=1}'

RUNS += run_rotate
run_rotate : rotate
	@./rotate

RUNS += run_linearnan
linearnan : linear
run_linearnan linearnan : linear
	@./linear \
	| awk '/defaultnan/ {p=0} p==1 {print} /DefaultNan/ {p=1}'

.PHONY: error_rectangle
error_rectangle : 
	@rm -f rectangle && \
	make rectangle EXTRA_FLAGS="-DWRONG"

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
