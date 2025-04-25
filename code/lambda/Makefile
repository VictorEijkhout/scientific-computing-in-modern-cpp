# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2015-2025
####
#### Makefile for code directory "lambda"
####
################################################################

PROGRAMS = \
    lambdaex lambdait lambdafun lambdacapture newtonlambda mutable \
    lambdacptr lambdaexch lambdarecur invoke countif \
    capturethis mutableloop

WRONGS = 

include ../Make.inc
LANGUAGE = CXX
CPPSTANDARD = 23

RUNS =

RUNS += run_lambdadirect
run_lambdadirect : lambdaex
	@lambdaex \
	| awk '/direct/ {p=0} p==1 {print} /Direct/ {p=1}'
RUNS += run_lambdavar
run_lambdavar : lambdaex
	@lambdaex \
	| awk '/var/ {p=0} p==1 {print} /Var/ {p=1}'
RUNS += run_lambdapass
run_lambdapass : lambdaex
	@lambdaex \
	| awk '/pass/ {p=0} p==1 {print} /Pass/ {p=1}'

RUNS += run_lambdacptr
run_lambdacptr : lambdacptr
	@./lambdacptr

RUNS += run_lambdafun
run_lambdafun : lambdafun
	@echo 7 | ./lambdafun

RUNS += run_lambdait
run_lambdait : lambdait
	@./lambdait

RUNS += run_lambdaexch
run_lambdaexch : lambdaexch
	@./lambdaexch

RUNS += run_countif
run_countif : countif
	@countif

RUNS += run_lambdacapture run_lambdavalue run_lambdareference run_lambdaconstant
run_lambdacapture : lambdacapture
	@echo "(input value: 1)" && echo 
	@( echo 1 ; echo 1 ) | ./lambdacapture
run_lambdavalue : lambdacapture
	@echo "(input value: 1)" && echo 
	@( echo 1 ; echo 1 ) | ./lambdacapture \
	| awk '/value/ {p=0} p==1 {print} /Value/ {p=1}'
run_lambdareference : lambdacapture
	@echo "(input value: 1)" && echo 
	@( echo 1 ; echo 1 ) | ./lambdacapture \
	| awk '/reference/ {p=0} p==1 {print} /Reference/ {p=1}'
run_lambdaconstant : lambdacapture
	@( echo 1 ; echo 2 ) | ./lambdacapture \
	| awk '/constant/ {p=0} p==1 {print} /Constant/ {p=1}'

RUNS += run_newtonlambda
run_newtonlambda : newtonlambda
	echo 2 | ./newtonlambda

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

RUNS += run_nonmutable run_yesmutable
run_nonmutable : mutable
	@./mutable \
	| awk '/nonmutable/ {p=0} p==1 {print} /NonMutable/ {p=1}'
run_yesmutable : mutable
	@./mutable \
	| awk '/yesmutable/ {p=0} p==1 {print} /YesMutable/ {p=1}'

RUNS += run_capthisvalue run_capthisref
run_capthisvalue run_capthisref : capturethis
run_capthisvalue :
	@./capturethis \
	| awk '/capvalue/ {p=0} p==1 {print} /Capvalue/ {p=1}'
run_capthisref :
	@./capturethis \
	| awk '/capref/ {p=0} p==1 {print} /Capref/ {p=1}'


.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
