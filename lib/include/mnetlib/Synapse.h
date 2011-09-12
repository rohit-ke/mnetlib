/**
*  Synapse.h
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

#ifndef SYNAPSE_H
#define SYNAPSE_H

#include "Exception.h"
#include "doubleMat.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/shared_ptr.hpp>
namespace ublas = boost::numeric::ublas; 


namespace Mnetlib
{


	class Synapse
	{
	public:

		/**
		 * Costruttore.
		 * Utilizza due parametri, n ed l. Solitamente n rappresenta il numero di neuroni presenti nel layer,
		 * mentre l e' variabile; nei layer interni e' il numero di neuroni del layer precedente, mentre nei 
		 * layer d'ingresso e d'uscita coincide con n (sinapsi lineare). 
		 * @param n Numero di neuroni a cui e' collegata la sinapsi.
		 * @param l Numero di linee d'ingresso.
		 */
		Synapse(int n, int l){_n=n; _l=l; _index=0;};
		
		
		virtual ~Synapse(){};
		
		/**
		 * Funzione che ritorna il vettore degli errori.
		 */
		virtual double get_input(int i){throw new NotImplementedException("get_input");};
		
		virtual double get_out(int i){throw new NotImplementedException("get_out");};
		
		virtual double get_error(int i){throw new NotImplementedException("get_error");};
		
		virtual ublas::matrix<double> get_weight(){throw new NotImplementedException("get_weight");};
		
		virtual void set_weight(ublas::matrix<double> w){throw new NotImplementedException("set_weight");};
		
		virtual void set_index(int i){throw new NotImplementedException("set_index");};
		
		//void set_error(int i, double value){throw new NotImplementedException();};
		
		virtual void set_gradient(int i, double value){throw new NotImplementedException("set_gradient");};
		
		virtual void set_out(int i, double value){throw new NotImplementedException("set_out");};
		
		virtual void inizialize_weight(){throw new NotImplementedException("inizialize_weight");};//genera numeri casuali per i pesi
		
		virtual void adjuste_weight(double rate, int cicle, double momentum){throw new NotImplementedException("adjuste_weight");};
		
		virtual void set_pattern_input(doubleMat p){throw new NotImplementedException("");};
		
		virtual void set_example(doubleMat ex){throw new NotImplementedException("set_example");};
		
		virtual std::string toString(){throw new NotImplementedException("toString");};

	protected:
		int _n;
		int _l;
		int _index;
	};
}
#endif
