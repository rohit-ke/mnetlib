/**
*  Layer.cpp
*  mnetlib
*
*  This file is part of mnetlib.
*
*  mnetlib is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  mnetlib is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with mnetlib; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*
*  Copyright (C) 2007 by francesco.amenta
*  francesco.amenta@gmail.com
*
*/


#include "Layer.h"

namespace Mnetlib
{
	
	Layer::Layer(int n)
	{
		_n=n;
	}
	
	Layer::~Layer()
	{
		for(int i=0; i<_n;i++)
		{
			delete vect[i];
		}
	}
		
	void Layer::forward()
	{
		Neuron* aux;
		for(int i=0; i<_n;i++)
		{
			aux=(Neuron*)vect[i];
			double in=_insin->get_input(i);
			_outsin->set_out(i,aux->Run(in));
		}
	}
	
}
