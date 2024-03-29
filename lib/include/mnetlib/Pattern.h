/**
*  Pattern.h
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

#ifndef PATTERN_H
#define PATTERN_H

#include "StringTokenizer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
namespace ublas = boost::numeric::ublas; 

using namespace std;

namespace Mnetlib
{
	
	class Pattern
	{
	public:
		
		Pattern();
		
		~Pattern();
		//TODO move all logic to PatternUtil or facsimile
		void loadPatternFile(string filename);
		
		int getLenght(){return dataIn.size1();};
		
		ublas::matrix<double> normalize(ublas::matrix<double> nor);
		
		void buildIn(string line, int index);
		
		void buildOut(string line, int index);
		
		void getparam(string line);
		
		int getNin(){return dataIn.size2();};
		
		int getNout(){return dataOut.size2();};
		
		//TODO should be private, add getter, setter, evaluate change to boost:matrix
		//ublas::matrix<double> dataIn;
		ublas::matrix<double> dataIn;
		//ublas::matrix<double> dataOut;
		ublas::matrix<double> dataOut;
	private:
		ifstream* inFile;
		//double* data;
		int nCol;
		int nColOut;
		int nRow;
		double min(ublas::vector<double> in_array,int length);
		double max(ublas::vector<double> in_array,int length);
		//double* normalizer;
	};

	typedef boost::shared_ptr<Pattern> PatternSPtr;}

#endif
