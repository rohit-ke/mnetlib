/**
*  NeuronLib.cpp
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

#include "NeuronLib.h"
namespace Mnetlib
{
	
	
	double LinearNeuron::Run(double arg)
	{
		
		_input=arg;
		
		_outvalue=_input;
		
		return _outvalue;
	}
	
	double LinearNeuron::RunBack(double o,double e)
	{
		double err=e;
		double out=o;
		double ret=0;
		
		ret=out*err;
			
		return ret;
	}
	
	double SigmoidNeuron::Run(double arg)
	{
		
		_input=arg;
		
		_outvalue=1/(1+exp(-_input));
		
		return _outvalue;
	}
	
	double SigmoidNeuron::RunBack(double o,double e)
	{
		double err=e;
		double out=o;
		double ret=0;
		
		ret=out*(1-out)*err;
			
		return ret;
	}

	double LogarithmicNeuron::Run(double arg)
	{

	  _input=arg;

	  _outvalue= log(_input);

	  return _outvalue;
	}

	double LogarithmicNeuron::RunBack(double o,double e)
	{
	  double err=e;
	  double out=o;
	  double ret=0;

	  ret=(1/exp(out))*err;

	  return ret;
	}

	double TanhNeuron::Run(double arg)
	{
		
		_input=arg;
		
		_outvalue=tanh(_input);
		
		return _outvalue;
	}
	
	double TanhNeuron::RunBack(double o,double e)
	{
		double err=e;
		double out=o;
		double ret=0;
		
		ret=(1-out)*(1+out)*err;
			
		return ret;
	}

	double GaussianNeuron::Run(double arg)
	{

	  _input=arg;

	  _outvalue=exp(-_input*_input);

	  return _outvalue;
	}

	double GaussianNeuron::RunBack(double o,double e)
	{
	  double err=e;
	  double out=o;
	  double ret=(-2.0 * out * _input)*err;
	  //ret=(1-out*out)*err;

	  return ret;
	}

}

