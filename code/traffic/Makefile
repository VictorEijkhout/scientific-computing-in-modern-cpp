# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2019-2025 Victor Eijkhout
####
#### makefile for traffic simulation
####
################################################################

PROGRAMS = light street

LANGUAGE = CXX
MODULES = catch2 cxxopts
INCLUDES = \
    -I${TACC_CATCH2_INC} \
    $(shell pkg-config --cflags cxxopts )
#    $(shell pkg-config --cflags fmt )
EXTRALIBS = \
    -L${TACC_CATCH2_LIB} -lCatch2Main -lCatch2 -lffi 
#    $(shell pkg-config --libs fmt )
RPATH = ${TACC_CATCH2_LIB}
# ${TACC_FMTLIB_LIB}
ifeq "${TACC_FAMILY_COMPILER}" "gcc"
  OPTIONS = -Wno-psabi
endif
include ../Make.inc
CPPSTANDARD = 23

street : traffic_lib.o
CMAKE_EXTRA_SOURCES = traffic_lib.cpp
street.o traffic_lib.o : traffic_lib.hpp

RUNS =

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
