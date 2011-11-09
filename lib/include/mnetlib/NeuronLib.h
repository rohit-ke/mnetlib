/**
*  NeronLib.h
*  Mnetlib
*
*  This file is part of Mnetlib.
*
*  Mnetlib is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  Mnetlib is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with Mnetlib; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*
*  Copyright (C) 2007 by francesco.amenta
*   francesco.amenta@gmail.com
*
*/


#ifndef NEURONLIB_H_
#define NEURONLIB_H_

#include "Neuron.h"
#include <boost/shared_ptr.hpp>
#include <string>

namespace Mnetlib
{


class LinearNeuron: public Neuron
{
public:

	double Run(double arg);
	double RunBack(double o,double e);
	static LinearNeuron* create(){ return new LinearNeuron();};
	static std::string name(){ return "linear";} ;	
private:
	virtual ~LinearNeuron(){};
};

class SigmoidNeuron: public Neuron
{
public:
	double Run(double arg);
	double RunBack(double o,double e);
	static SigmoidNeuron* create(){ return new SigmoidNeuron();};
	static std::string name(){ return "sigmoid";} ;
private:
	virtual ~SigmoidNeuron(){};
};

class LogarithmicNeuron: public Neuron
{
public:
        double Run(double arg);
        double RunBack(double o,double e);
        static LogarithmicNeuron* create(){ return new LogarithmicNeuron();};
        static std::string name(){ return "logh";} ;
private:
        virtual ~LogarithmicNeuron(){};
};


class TanhNeuron: public Neuron
{
public:
        double Run(double arg);
        double RunBack(double o,double e);
        static TanhNeuron* create(){ return new TanhNeuron();};
        static std::string name(){ return "tanh";} ;
private:
        virtual ~TanhNeuron(){};
};

typedef boost::shared_ptr<Neuron> NeuronSPtr;
typedef boost::shared_ptr<SigmoidNeuron> SigmoidNeuronSPtr;
typedef boost::shared_ptr<LinearNeuron> LinearNeuronSPtr;
typedef boost::shared_ptr<LogarithmicNeuron> LogarithmicNeuronSPtr;
typedef boost::shared_ptr<TanhNeuron> TanhNeuronSPtr;

}
#endif /*NEURONLIB_H_*/
