/**
*  Layer.h
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

#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <iostream>

#include "Neuron.h"
#include "Exception.h"
#include "Synapse.h"
#include <boost/shared_ptr.hpp>

namespace Mnetlib
{
	
typedef boost::shared_ptr<Neuron> NeuronSPtr;
typedef boost::shared_ptr<Synapse> SynapseSPtr;
	class Layer
	{
	public:
		
		/**
		 * Costruttore di base.
		 * @param n Numero di neuroni presenti nel layer.
		 */
		Layer(int n);
		
		virtual ~Layer();
		
		/**
		 * Funzione per il calcolo dei valori in uscita al layer.
		 */
		virtual void forward();
		
		virtual void backprop(){throw new NotImplementedException("backprop");};
		
		/**
		 * Funzione che si occupa di connettere il layer con le sinapsi in ingresso ed in uscita.
		 * @param insin Sinapsi in ingresso.
		 * @param outsin Sinapsi in uscita.
		 */
		void connectLayer(SynapseSPtr insin,SynapseSPtr outsin){_insin=insin; _outsin=outsin;};
		
		void setVector(vector<NeuronSPtr> v){vect=v;};

		virtual std::string toString(){throw new NotImplementedException("to_string");};
	
	protected:
		std::vector<NeuronSPtr> vect;
		int _n;
		SynapseSPtr _insin;
		SynapseSPtr _outsin;

	};
}
#endif
