# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2023 Victor Eijkhout
####
#### namespace codes
####
################################################################

PROGRAMS = geomspace geo instant inline

LANGUAGE = CXX
include ../Make.inc
MODULES = fmtlib
INCLUDES = -I${TACC_FMTLIB_INC}
EXTRALIBS = -L${TACC_FMTLIB_LIB} -lfmt
RPATH = ${TACC_FMTLIB_LIB}

geo : geolib.o
geo.o geolib.o : geolib.hpp

instant : instantlib.o
instant.o instantlib.o : instantlib.h

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
