# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++ and Fortran
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2024 Victor Eijkhout
####
#### header examples
####
################################################################

PROGRAMS = functmain classmain
WRONGS = 

LANGUAGE = CXX
include ../Make.inc
functmain : funct.o
functmain.o fun.o : functheader.hpp
classmain : classimpl.o
classmain.o class.o : classheader.hpp

info ::
	@echo "===== skeletons"
	@echo "make funct_skeleton funct_skeleton_build"
.PHONY: funct_skeleton funct_skeleton_build
include ../../makefiles/repos.inc
funct_skeleton :
	@mkdir -p $@
	@for f in funct*.{cpp,hpp} ; do \
	    cat $$f \
	    | grep -v snippet \
	    > $@/$$f \
	 ; done
	@cp -r $@ ../../skeletons/
	@cp -r $@ "${STUDENTREPO}/skeletons/"
	@echo "made ../../skeletons/$@ and ${STUDENTREPO}/skeletons/"
funct_skeleton_build :
	@rm -rf build && mkdir build && cd build \
	 && cmake ../funct_skeleton \
	 && make
clean ::
	@rm -rf funct_skeleton

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
