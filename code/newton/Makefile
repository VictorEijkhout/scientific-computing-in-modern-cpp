# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2025 Victor Eijkhout
####
################################################################

PROGRAMS = newton  newton-fun newton-lambda \
	newton-double newton-complex lambda-complex \
	newton-template newton-templatefun newton-templatetf \
    newton-templatedouble newton-conceptreal
WRONGS = newton-conceptint newton-conceptcomplex

LANGUAGE = CXX
include ../Make.inc
# redefine cxx standard:
CPPSTANDARD = 20

RUNS = run_newton run_fun run_lambda
.PHONY: run_newton run_fun run_lambda
run_newton : newton
	@./newton
run_fun : newton-fun
	@./newton-fun
run_lambda : newton-lambda
	@./newton-lambda

.PHONY: templatetf
info ::
	@echo " .. templatetf : template mismatch code"
templatetf :
	@make --no-print-directory OPTIONS=-DMISMATCH \
	  newton-templatetf

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
