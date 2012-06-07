/**
*  doubleMat.cpp
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

#include "doubleMat.h"
#include "Exception.h"
#include <sstream>

namespace Mnetlib{

	doubleMat::doubleMat(){
		_row=0;
		_col=0;
	}
	
	doubleMat::doubleMat(const doubleMat& m){
		_row=m._row;
		_col=m._col;
		_data=new double[_row*_col];
		for(int i=0; i<_row*_col; i++){
			_data[i]=m._data[i];
		}
		
	}
	
	doubleMat::doubleMat(int n, int m){
		_row=n;
		_col=m;
		_data=new double[_row*_col];
	}
	
	doubleMat::doubleMat(int n){
		_row=n;
		_col=1;
		_data=new double[_row*_col];
	}
	
	doubleMat::~doubleMat(){

		delete [] _data;
	}
	
	const doubleMat& doubleMat::operator=(const doubleMat& m){
		_row=m._row;
		_col=m._col;
		_data=new double[_row*_col];
		for(int i=0; i<_row*_col; i++){
			_data[i]=m._data[i];
		}
		
		return m;
	}
	
	double& doubleMat::operator() (int row, int col)
	{
	  std::stringstream aErrorString;
	  aErrorString << "Input value: " << row << " " << col << " Matrix index: " << _row << " " << _col;
	  if (row >= _row || col >= _col)
	    throw IndexOutOfBoundException(aErrorString.str().c_str());
	  return _data[_col*row + col];
	}

	double doubleMat::operator() (int row, int col) const
	{
	  std::stringstream aErrorString;
	            aErrorString << "Input value: " << row << " " << col << " Matrix index: " << _row << " " << _col;
	  if (row >= _row || col >= _col)
	    throw IndexOutOfBoundException(aErrorString.str().c_str());
	  return _data[_col*row + col];
	}

	double& doubleMat::operator() (int row)
{
		/*	if (row >= _row || col >= _col)
		return NULL;*/
		return _data[_col*row];
}

 double doubleMat::operator() (int row) const
{
	if (row >= _row)
		return 0;
	return _data[_col*row];
}

}
