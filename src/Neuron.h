/**
*  Neuron.h
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

#ifndef NEURON_H
#define NEURON_H
#include <math.h>
namespace Mnetlib
{
class Neuron
{
	public:
		/**
		 * Distruttore.
		 */
		virtual ~Neuron(){};
		
		/**
		 * Funzione principale del neurone.
		 * Implementa la funzione di trasferimento del neurone.
		 * @param arg  Prende in ingresso un argomento di qualsiasi tipo che verra' usato come dato di input.
		 */
		virtual double Run(double arg)=0;
		
		/**
		 * Funzione che computa il gradiente
		 * @param o Valore di uscita
		 * @param e Errore 
		 */
		virtual double RunBack(double o,double e)=0;
	protected:
		double _outvalue;
		double _input;	
		
};
}
#endif // NEURON_H
