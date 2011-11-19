#Makefile.am
#
# Created on: 20/ago/2011
#     Author: totoro
#

# Build the library in the hand subdirectory first.

SUFFIXES	= .cpp .hpp .idl .c .h .f .F .o .moc .cc
CXX = colorgcc

headerDir = $(srcdir)/../lib/include/
# Include hand's header when compiling this directory.
AM_CPPFLAGS = -I$(headerDir) -I -L $(srcdir)/../lib/src/

 bin_PROGRAMS = bench testbasiclearner
 bench_SOURCES = bench.cpp
 # link with the hand library.
 bench_LDADD = $(srcdir)/../lib/src/libmnetlib.la -lpthread -lxerces-c
 
 testbasiclearner_SOURCES = TestBasicLearner.cpp
 # link with the hand library.
 testbasiclearner_LDADD = $(srcdir)/../lib/src/libmnetlib.la -lpthread -lxerces-c
 