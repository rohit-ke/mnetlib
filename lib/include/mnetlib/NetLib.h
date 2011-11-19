/**
*  NetLib.h
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

#ifndef NETLIB_H_
#define NETLIB_H_

#include "Net.h"

namespace Mnetlib
{
	
	class FFOnLineBackNet: public Net
	{
	public:
		FFOnLineBackNet();
		
		virtual ~FFOnLineBackNet();
		
		static NetSPtr create(){ return NetSPtr(new FFOnLineBackNet());};
		
		static std::string name(){ return "ffonlineNet";} ;	
		
		virtual void connect() const;

		void trainNet();
		
		void testNet();
		
		doubleMat getNetOut();
		
		void setPattern(doubleMat inp, doubleMat ex, int lenght, int out);

		std::string toString();
	
	private:
	
		void set_index(int i);
		
		void forward_input();
		
		void back_error();
		
		void update_weight(int c);
		
		void compute_error();	
	};
}
#endif /*LIBNET_H_*/
