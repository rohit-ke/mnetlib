

SUFFIXES	= .cpp .hpp .idl .c .h .f .F .o .moc .cc
CXX = colorgcc
CPPFLAGS = -pipe -Wall
lib_LTLIBRARIES	= libmnetlib.la

libmnetlib_la_SOURCES	= NetLib.cpp Layer.cpp LayerLib.cpp Pattern.cpp NeuronLib.cpp Learner.cpp \
			  			  Registry.cpp StringTokenizer.cpp SynapseLib.cpp LearnerAdapter.cpp

headerDir =  $(srcdir)/../include/mnetlib/				

include_HEADERS = ../include/mnetlib/Exception.h ../include/mnetlib/Factory.h ../include/mnetlib/Layer.h \
				 ../include/mnetlib/LayerLib.h ../include/mnetlib/Learner.h ../include/mnetlib/Net.h ../include/mnetlib/NetLib.h \
				 ../include/mnetlib/Neuron.h ../include/mnetlib/NeuronLib.h ../include/mnetlib/Pattern.h ../include/mnetlib/Registry.h \
				 ../include/mnetlib/StringTokenizer.h ../include/mnetlib/Synapse.h ../include/mnetlib/SynapseLib.h \
				 ../include/mnetlib/CommonXMLNetConstant.h ../include/mnetlib/CommonMacro.h ../include/mnetlib/LearnerAdapter.h
				 
INCLUDES = -I $(srcdir)/../include/mnetlib/
libmnetlib_la_LIBADD = -lpthread
