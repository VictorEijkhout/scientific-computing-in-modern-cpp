################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2024 Victor Eijkhout
####
#### makefile for fenv
####
################################################################
################################################################

info ::
	@echo && echo "fenv demonstration projects" && echo 

PROGRAMS = divzero round
LANGUAGE = CXX
include ../../makefiles/Make.compile
include ../../makefiles/Make.run
CPPSTANDARD = 20

RUNS =
RUNS += run_divzero
run_divzero : divzero
	@echo 0 | divzero
RUNS += run_round
run_round : round
	@echo 1 | round

include ../../makefiles/Make.clean
