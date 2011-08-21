#Makefile.am
#
# Created on: 20/ago/2011
#     Author: totoro
#

# Build the library in the hand subdirectory first.

SUFFIXES	= .cpp .hpp .idl .c .h .f .F .o .moc .cc

headerDir = ../lib/include/mnetlib/	
# Include hand's header when compiling this directory.
AM_CPPFLAGS = -I$(headerDir) -L ../lib/src/

 bin_PROGRAMS = bench
 bench_SOURCES = bench.cpp
 # link with the hand library.
 bench_LDADD = ../lib/src/libmnetlib.la -lpthread