# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2025 Victor Eijkhout
####
################################################################

PROGRAMS = example1 example2 func eps max cl3 \
    expression2 expression3 expression4 expression \
    fxpression2 fxpression3 fxpression4 fxpression \
    varindex varloop concept
WRONGS = 

LANGUAGE = CXX
include ../Make.inc
CPPSTANDARD = 23

RUNS =

RUNS += run_example1 run_example1i5 run_example1f314
run_example1 : example1
	@./example1
run_example1i5 : example1
	@./example1 \
	| awK '/storei5/ {p=0} p==1 {print} /StoreI5/ {p=1}'
run_example1f314 : example1
	@./example1 \
	| awK '/storef314/ {p=0} p==1 {print} /StoreF314/ {p=1}'

RUNS += run_example2
run_example2 : example2
	@./example2

RUNS += run_eps
run_eps : eps
	@./eps

RUNS += run_func
run_func : func
	@./func

RUNS += run_max
run_max : max
	@./max

RUNS += run_cl3
run_cl3 : cl3
	@./cl3

RUNS += run_concept
run_concept : concept
	@./concept

RUNS += run_add2
fxpression2.o : fxpression2.hpp
run_add2 : fxpression2
	@./fxpression2
RUNS += run_add3
run_add3 : fxpression3
	@./fxpression3
RUNS += run_add4
run_add4 : fxpression4
	@./fxpression4

.PHONY: ${RUNS}

sep : sep_main.o sep_impl.o
	${LINKER} -o $@ $^

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
