/**
*  Pattern.cpp
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

#include "Pattern.h"

using std::cout;

namespace Mnetlib{
	
	Pattern::Pattern(){
	}
	
	Pattern::~Pattern()
	{
		//delete normalizer;
	}
	
	void Pattern::loadPatternFile(string filename)
	{
		fstream tmpFile(filename.c_str());
 		string line;
		getline(tmpFile, line);
		getparam(line);
		dataIn=doubleMat(nRow,nCol);
		dataOut=doubleMat(nRow,nColOut);
		int n=0;
		cout<<nRow<<","<<nCol<<","<<nColOut<<"\n";
		while(!tmpFile.eof() && n<nRow)
		{
			/*Leggo una linea dal file*/
			getline(tmpFile, line);
			/*Costruisco una riga di input*/
			buildIn(line,n);
			/*Leggo una linea dal file*/
			getline(tmpFile, line);
			/*Costruisco una riga di output*/
			buildOut(line,n);
			/*Incremento l'indice*/
			n++;
		}
		tmpFile.close();
	}
	
	void Pattern::buildIn(string line, int index)
	{
	  //TODO Unsafe!!! Add try/catch check nextFloatToken out!
	  StringTokenizer strtok= StringTokenizer(line," ");
		for(int i=0;i<nCol;i++)
		{
			if(!strtok.hasMoreTokens()){break;}
			dataIn(index,i)=(double)strtok.nextFloatToken();
		}
		
	}
	
	void Pattern::buildOut(string line, int index)
	{
          //TODO Unsafe!!! Add try/catch check nextFloatToken out!
		StringTokenizer strtok= StringTokenizer(line," ");
		for(int i=0;i<nColOut;i++)
		{
			dataOut(index,i)=(double)strtok.nextFloatToken();
		}
	}
	
	void Pattern::getparam(string line)
	{
		StringTokenizer strtok= StringTokenizer(line," ");
		nRow=strtok.nextIntToken();
		nCol=strtok.nextIntToken();
		nColOut=strtok.nextIntToken();
	}
		
	
	double Pattern::min(ublas::vector<double> in_array,int length)
	{
		double tmp=0;
		for(int index=0;index<length;index++)
		{
			if(index==0)
			{
				tmp=in_array(index);
			}
			else
			{
				if(tmp>in_array(index))
					tmp=in_array(index);
			}
		}
		return tmp;
	}
	
	double Pattern::max(ublas::vector<double> in_array,int length)
	{
		double tmp=0;
		for(int index=0;index<length;index++)
		{
			if(index==0)
			{
				tmp=in_array(index);
			}
			else
			{
				if(tmp<in_array(index))
				{
					tmp=in_array(index);
				}
			}
		}
		return tmp;
		
	}
	
	ublas::matrix<double> Pattern::normalize(ublas::matrix<double> nor)
	{
		int pri_index=0;
		int sec_index=0;
		ublas::matrix<double> normalizzato(nRow,nCol);
		//Devo normalizzare per colonna
		while(sec_index<nCol)
		{
			ublas::vector<double> support (nRow);
			//Costruisco un array di supporto
			for(pri_index=0;pri_index<nRow;pri_index++)
			{
				support(pri_index)=nor(pri_index,sec_index);
			}
			double tmp_min=min(support,nRow);
			double tmp_max=max(support,nRow);
			for(pri_index=0;pri_index<nRow;pri_index++){
				normalizzato(pri_index,sec_index)=(nor(pri_index,sec_index)-tmp_min)/(tmp_max-tmp_min);
			}
			sec_index++;
			//delete[] support;
		}
		//this->normalizer=normalizzato;
		return normalizzato;
	}
		
	
}
