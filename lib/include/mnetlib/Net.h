/**
*  Net.h
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

#ifndef NET_H
#define NET_H

#include <math.h>
#include <iostream>
#include <vector>
#include "Layer.h"
#include "Synapse.h"
#include "Exception.h"

namespace Mnetlib{

  typedef boost::shared_ptr<Layer> LayerSPtr;
  typedef boost::shared_ptr<Synapse> SynapseSPtr;
	class Net
	{
	public:
		
		/*
		 * Costruttore di default
		 */
		Net(){};
		
		/*
		 * Distruttore di default
		 */
		virtual ~Net(){};
		
		/*
		 * Routine per l'apprendimento della rete in modalita' online.
		 */
		virtual void trainNet(){throw new NotImplementedException("trainNet");};
		
		/*
		 * Routine che effettua il test della rete.
		 */
		virtual void testNet(){throw new NotImplementedException("testNet");};
		
		/*
		 * Routine che restituisce le uscite della rete
		 */
		virtual doubleMat getNetOut(){throw new NotImplementedException("getNetOut");}
		/*
		 * Setta i parametri necessari per l'apprendimento della rete
		 * 
		 * @param n	 Learning rate.
		 * @param m	 Momento.
		 * @param c	 Cicli d'apprendimento.
		 */
		void set_parameter(double n,double m, int c){_learning_rate=n; _momentum=m; train_cicles=c;};
		
		/*
		 * Setta i pattern d'ingresso e gli esempi in uscita necessari per la fase d'apprendimento.
		 */
		virtual void setPattern(doubleMat inp, doubleMat ex, int lenght, int out){throw new NotImplementedException("setPattern");};

		virtual void connect() const=0 ;
		
		double getGlobalError(){return _global_error;};
		
		double getRMSE(){return _rmse;};
		
		void setLayer(vector<LayerSPtr>& l){_layer=l;};
		
		void setSynapse(vector<SynapseSPtr>& s){_synapse=s;};

		void pushLayer(LayerSPtr& l){_layer.push_back(l);};

		void pushSynapse(SynapseSPtr& s){_synapse.push_back(s);};

		virtual std::string toString(){throw new NotImplementedException("toString");};
	protected:
		vector<LayerSPtr> _layer;
		vector<SynapseSPtr> _synapse;
		double _global_error;
		double _rmse;
		double _learning_rate;
		double _momentum;
		int train_cicles;//memorizza il numero massimo di cicli d'apprendimento
		int _out;	
		/* Indice che memorizza la lunghezza delle linee d'ingresso*/
		int inlenght;
		
			
	};

	typedef boost::shared_ptr<Net> NetSPtr;
}

#endif
