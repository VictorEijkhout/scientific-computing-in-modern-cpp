# -*- makefile -*-
################################################################
####
#### This makefile is part of the course
#### Introduction to Scientific Programming in C++11 and Fortran2003
#### by Victor Eijkhout (eijkhout@tacc.utexas.edu)
#### copyright 2017-2025 Victor Eijkhout
####
#### using the format library
####
################################################################

PROGRAMS = hasformat io io16 iof fio fiobin fix align \
    cin cinfloat cunformat width formatpad formatleft format16 formatfloat \
    gettermline gettwoline \
    quasifix quickinput quickcount \
    fmtbasic fmtstd fmtfloat fmtio16 fmt256 fmtsci fmtfix fmtclass \
    bits iolib compare
WRONGS = \
    stdformat

LANGUAGE = CXX
include ../Make.inc
CPPSTANDARD = 23

MODULES =

RUNS = 

##
## whole bunch of i/o runs
##

RUNS += run_cin run_cinin run_cinfloat
run_cin : cin
	echo "Victor" | ./cin
run_cinin : cin
	echo "Victor Eijkhout" | ./cin
run_cinfloat : cinfloat
	for n in \
	    1.5  1.6  1.67  1.67e5  2.5.6  \
	    ; do \
	        echo $$n | ./cinfloat \
	; done

GETLINERUNS = run_gettermline run_gettwoline
RUNS += ${GETLINERUNS}
run_gettermline : gettermline
	echo "one line, !!" \
	| ./gettermline
run_gettwoline : gettwoline
	( echo "one line, !!" \
  && echo "2.line.2" ) \
	| ./gettwoline

RUNS += run_cunformat
run_cunformat : cunformat
	@./cunformat

RUNS += run_width
run_width : width
	@./width

RUNS += run_fix
run_fix : fix
	@./fix

RUNS += run_bits
run_bits : bits
	@./bits

RUNS += run_align
run_align : align
	@./align

RUNS += run_fio
run_fio : fio
	echo 24 | ./fio \
	 && cat fio_example.out

RUNS += run_binout run_binin
run_binout run_binin : fiobin
run_binout : 
	@./fiobin \
	 | awk '/binout/ {p=0} p==1 {print} /Binout/ {p=1}'
run_binin : 
	@./fiobin \
	 | awk '/binin/ {p=0} p==1 {print} /Binin/ {p=1}'

RUNS += run_formatpad
run_formatpad : formatpad
	@./formatpad

RUNS += run_formatleft
run_formatleft : formatleft
	@./formatleft

RUNS += run_formatfloat
run_formatfloat : formatfloat
	@./formatfloat

RUNS += run_format16
run_format16 : format16
	@./format16

RUNS += run_block16
run_block16 : io16
	@./io16 | awk '/Block16:/ {p=1} /block16:/ {p=0} p==1 {print}'

RUNS += run_quickcount
run_quickcount : quickcount
	@./quickcount

RUNS += run_quickinput
run_quickinput : quickinput
	@./quickinput

RUNS += run_quasifix
run_quasifix : quasifix
	@./quasifix

RUNS += run_iofsci
run_iofsci : iof
	@./iof \
	 | awk '/iofsci/ {p=0} p==1 {print} /IOFSCI/ {p=1}'

FMTRUNS = run_fmtbasic run_fmtwidth run_fmtleftpad run_fmtbase run_fmtstream 
## ${FMTRUNS} :: fmtstd
run_fmtbasic  :: fmtbasic
	@./fmtbasic
run_fmtwidth :: fmtstd
	@./fmtstd \
	| awk '/width/ {p=0} p==1 {print} /Width/ {p=1}'
run_fmtleftpad :: fmtstd
	@./fmtstd \
	| awk '/leftpad/ {p=0} p==1 {print} /Leftpad/ {p=1}'
run_fmtbase :: fmtstd
	@./fmtstd \
	| awk '/base/ {p=0} p==1 {print} /Base/ {p=1}'
run_fmtstream :: fmtstd
	@./fmtstd \
	| awk '/stream/ {p=0} p==1 {print} /Stream/ {p=1}'
run_fmtfloat : fmtfloat
	@./fmtfloat
FMTRUNS += run_fmtsci run_fmtfix
run_fmtsci : fmtsci
	@./fmtsci
run_fmtfix : fmtfix
	@./fmtfix

RUNS += ${FMTRUNS}
.PHONY: ${RUNS}

include ../../makefiles/Make.cmake
include ../../makefiles/Make.clean
clean ::
	@rm -f inout.dat # from iolib.cpp
