# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2019-2025 Victor Eijkhout
####
#### range examples
####
################################################################

PROGRAMS = range filter iota of sort \
    norm norm2 
WRONGS = zip sumsquare
# fibs range : missing "recursive_range"

LANGUAGE = CXX
include ../Make.inc
CPPSTANDARD = 23

RUNS =

RUNS += run_count
run_count : range
	@./range \
	| awk '/count/ {p=0} p==1 {print} /Count/ {p=1}'

RUNS += run_cout
run_cout : range
	@./range \
	| awk '/cout/ {p=0} p==1 {print} /Cout/ {p=1}'

RUNS += run_drop
run_drop : range
	@./range \
	| awk '/drop/ {p=0} p==1 {print} /Drop/ {p=1}'

RUNS += run_transformi
run_transformi : range
	@./range \
	| awk '/transformi/ {p=0} p==1 {print} /Transformi/ {p=1}'
RUNS += run_transformr
run_transformr : range
	@./range \
	| awk '/transformr/ {p=0} p==1 {print} /Transformr/ {p=1}'

RUNS += run_iota
run_iota : iota
	@./iota

RUNS += run_any
run_any : of
	@./of \
	| awk '/any/ {p=0} p==1 {print} /Any/ {p=1}'

RUNS += run_filter
run_filter : filter
	@./filter \
	| awk '/filter/ {p=0} p==1 {print} /Filter/ {p=1}'

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
