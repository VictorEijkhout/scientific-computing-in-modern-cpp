# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2023 Victor Eijkhout
####
################################################################

PROGRAMS = readpoly findzero findzeroarray findzeroclass testzeroarray \
    zeroclasstest zeroclassmain

LANGUAGE = CXX
INCLUDES = -I${TACC_CATCH2_INC}
EXTRALIBS = -L${TACC_CATCH2_LIB} -lCatch2Main -lCatch2
MODULES = catch2
include ../Make.inc
RPATH = ${TACC_CATCH2_LIB}

readpoly findzero : poly.o
readpoly.o poly.o findzero.o : poly.hpp
readpoly_objects = poly.o
findzero_objects = poly.o

RUNS =

RUNS += run_findzero
run_findzero : findzero
	@( echo 5 ; for i in `seq 1 6` ; do echo $$(( 1+$$i )) ; done ) \
	| ./findzero

RUNS += run_findzeroarray
run_findzeroarray : findzeroarray
	@( echo 5 ; for i in `seq 1 6` ; do echo $$(( 1+$$i )) ; done ) \
	| ./findzeroarray
findzeroarray_objects = findzerolib.o
findzeroarray : findzerolib.o
findzeroarray.o findzerolib.o : findzerolib.hpp

RUNS += run_test
run_test : testzeroarray
	@( \
	  echo 5 ; for i in `seq 1 6` ; do echo $$(( 1+$$i )) ; done ; \
	  echo 5 ; for i in `seq 1 6` ; do echo $$(( 1+$$i )) ; done ; \
	  echo 5 ; for i in `seq 1 6` ; do echo $$(( 1+$$i )) ; done   \
	) \
	| ./testzeroarray
run_tests : testzeroarray
	@for i in `seq 1 5` ; do \
	    echo "Doing test [$$i]" \
	     && ( \
	          echo 5 ; for i in `seq 1 6` ; do echo $$(( 1+$$i )) ; done \
	        ) | ./testzeroarray "[$$i]" \
	    ; done

RUNS += run_zeroclassmain run_classtest
run_zeroclass : zeroclassmain
	@./zeroclassmain
run_classtest : zeroclasstest
	@./zeroclasstest
zeroclassmain zeroclasstest : zeroclasslib.o 
zeroclasslib.o zeroclassmain.o zeroclasstest.o : zeroclasslib.hpp

.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
.PHONY: zero_cmake
info ::
	@echo "make zero_cmake"
zero_cmake :
	@rm -rf src && mkdir src
	@echo "custom cmake build" \
	 && cp cmake_zeroclass.txt src/CMakeLists.txt \
	 && cp zeroclass{main,test}.cpp zeroclasslib.{cpp,hpp} src/ \
	 && rm -rf build && mkdir build && cd build \
	 && cmake -D CMAKE_VERBOSE_MAKEFILE=ON \
	      -D CMAKE_CXX_COMPILER=${TACC_CXX} \
	      ../src \
	 && make V=1

include ../../makefiles/Make.clean
