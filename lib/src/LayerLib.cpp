/**
*  LayerLib.cpp
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

#include "LayerLib.h"

namespace Mnetlib
{
	void OffLineLayer::backprop()
	{}
	void OnLineLayer::backprop()
	{}
	
	void OutputLayer::backprop()
	{
		for(int i=0; i<_n;i++)
		{
			Neuron* aux;
			aux=(Neuron*)vect[i];
			double o=_outsin->get_input(i);
			double e=_outsin->get_error(i);
			//calcolo il gradiente		
			_insin->set_gradient(i,aux->RunBack(o,e));
		}
	}
	
	void HiddenLayer::backprop()
	{
		for(int i=0; i<_n;i++)
		{
			Neuron* aux;
			aux=(Neuron*)vect[i];
			double o=_outsin->get_out(i);
			double e=_outsin->get_error(i);
			//calcolo il gradiente		
			_insin->set_gradient(i,aux->RunBack(o,e));
		}
	}
	
}
