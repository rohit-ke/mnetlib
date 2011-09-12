

SUFFIXES	= .cpp .hpp .idl .c .h .f .F .o .moc .cc
CXX = colorgcc
CPPFLAGS = -j4 -pipe -Wall
lib_LTLIBRARIES	= libmnetlib.la

libmnetlib_la_SOURCES	= NetLib.cpp Layer.cpp LayerLib.cpp Pattern.cpp NeuronLib.cpp Learner.cpp \
			  			  Registry.cpp doubleMat.cpp StringTokenizer.cpp SynapseLib.cpp

headerDir = ../include/mnetlib/				

include_HEADERS =../include/mnetlib/doubleMat.h ../include/mnetlib/Exception.h ../include/mnetlib/Factory.h ../include/mnetlib/Layer.h \
				 ../include/mnetlib/LayerLib.h ../include/mnetlib/Learner.h ../include/mnetlib/Net.h ../include/mnetlib/NetLib.h \
				 ../include/mnetlib/Neuron.h ../include/mnetlib/NeuronLib.h ../include/mnetlib/Pattern.h ../include/mnetlib/Registry.h \
				 ../include/mnetlib/StringTokenizer.h ../include/mnetlib/Synapse.h ../include/mnetlib/SynapseLib.h
				 
INCLUDES = -I ../include/mnetlib/
libmnetlib_la_LIBADD = -lpthread