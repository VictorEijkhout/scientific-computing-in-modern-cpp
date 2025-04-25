# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2019-2025 Victor Eijkhout
####
#### sparse matrix examples
####
################################################################

PROGRAMS = dense linalgout stencil 
WRONGS = toeplitz

LANGUAGE = CXX
CPPSTANDARD = 23
include ../Make.inc

##
## crs programs
##
.PHONY: crsmat0 crsmat1
info ::
	@echo && echo "================ crs programs"
	@echo "make crsmat0 crsmat1"

crs.o crs_tests.o : crs_tests.hpp
crs.o crs_mat.o crs_mat0.o crs_mat1.o : crs_mat.hpp
INCLUDES = $(shell pkg-config --cflags cxxopts ) \
    $(shell pkg-config --cflags catch2 )
EXTRALIBS = \
    -L${TACC_CATCH2_LIB} -lCatch2Main -lCatch2
MODULES = catch2 cxxopts
RPATH = ${TACC_CATCH2_LIB}

crsmat0 :
	@if [ "${ECHO}" = "1" ] ; then \
	    echo "Making crs from crs_mat0" ; fi
	@make --no-print-directory crs PROGRAMS=crs ECHO=${ECHO} \
	    EXTRA_OBJS="crs_mat0.o crs_tests.o crs_mat.o" 
crsmat1 :
	@if [ "${ECHO}" = "1" ] ; then \
	    echo "Making crs from crs_mat1" ; fi
	@make --no-print-directory crs PROGRAMS=crs ECHO=${ECHO} \
	    EXTRA_OBJS="crs_mat1.o crs_tests.o crs_mat.o" 
clean ::
	@rm -f crs
RUNS =

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
clean ::
	@rm -f crs0 crs1

