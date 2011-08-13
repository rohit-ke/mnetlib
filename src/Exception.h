/**
*  Exception.h
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

#ifndef L_EXCEPTION_H
#define L_EXCEPTION_H

#include <iostream>
#include <exception>
using namespace std;
namespace Mnetlib
{
	class InstantiationException: public exception
	{
	  virtual const char* what() const throw()
	  {
		return "You have wrong instantiate class. Look at registry usage";
	  }
	};
	
	class NotImplementedException: public exception
	{
	public:  
	  const char* error;
	  NotImplementedException(const char* arg) : error(arg){}
	  virtual const char* what() const throw()
	  {
			//return "You have call a method non implemented in this class. Look at registry usage";
			return error;
	  }
	};
}

#endif
