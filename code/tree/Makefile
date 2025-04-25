# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### copyright 2017-2023 Victor Eijkhout (eijkhout@tacc.utexas.edu)
####
#### examples for tree structures including linked lists
####
################################################################

PROGRAMS = binary linksimple linkshared linkunique traverse \
    singlesource1 singlesource2 dijkstra1 dijkstra2 \
    queuelevel queuedijkstra graphmvp graphmvpdijkstra \
    bintree quadtree 
PROGRAM = linksimple
MODULES = fmtlib

LANGUAGE = CXX
include ../Make.inc
CPPSTANDARD = 17
INCLUDES = -I${TACC_FMTLIB_INC}
EXTRALIBS = -L${TACC_FMTLIB_LIB} -lfmt
RPATH = ${TACC_FMTLIB_LIB}

RUNS =

RUNS += run_link
run_link : link
	@./link

RUNS += run_linkunique
run_linkunique : linkunique
	@./linkunique

RUNS += run_linkshared
run_linkshared : linkshared
	@./linkshared

RUNS += run_append
run_append : linksimple
	@./linksimple \
	| awk '/append/ {p=0} p==1 {print} /Append/ {p=1}'

RUNS += run_insert
run_insert : linksimple
	@./linksimple \
	| awk '/insert/ {p=0} p==1 {print} /Insert/ {p=1}'

RUNS += run_traverse
run_traverse : traverse
	@./traverse

RUNS += run_dijkstra1
run_dijkstra1 : dijkstra1
	@./dijkstra1
dijkstra1.o dijkstra2.o : levelset.cpp

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
