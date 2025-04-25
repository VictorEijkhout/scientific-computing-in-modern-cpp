# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2021-2023 Victor Eijkhout
####
#### makefile for commandline arg parsing
####
################################################################

PROGRAMS = argcv cxxopts cxxn

LANGUAGE = CXX
INCLUDES = $(shell pkg-config --cflags cxxopts )
EXTRALIBS = 
include ../Make.inc
CPPSTANDARD = 17
MODULES = cxxopts

RUNS =

RUNS += run_argcv
run_argcv : argcv
	./argcv 5 12
	./argcv abc 3.14 foo

RUNS += run_cxxopts
run_cxxopts : cxxopts
	./cxxopts -h
	./cxxopts -n 5 foo

RUNS += run_cxxn
run_cxxn : cxxn
	./cxxn -h
	./cxxn -n 5 foo

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
