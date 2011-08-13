/**
*  NetLib.cpp
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

#include "NetLib.h"

namespace Mnetlib
{
	FFOnLineBackNet::FFOnLineBackNet():Net()
	{
	}
	
	FFOnLineBackNet::~FFOnLineBackNet()
	{
		for (unsigned int n = 0; n < _synapse.size(); ++n) 
		{
			delete (_synapse[n]);
		}
		for (unsigned int i = 0; i < _layer.size(); ++i)
		 {
			delete (_layer[i]);
		}
	}
	
	void FFOnLineBackNet::set_index(int i)
	{
		for (unsigned int n = 0; n < _synapse.size(); ++n) {
			(_synapse[n])->set_index(i);
		}
	}
		
	void FFOnLineBackNet::forward_input()
	{
		for (unsigned int i = 0; i < _layer.size(); ++i) {
			(_layer[i])->forward();
		}
	}
		
	void FFOnLineBackNet::back_error()
	{
		for (unsigned int i = _layer.size()-1; i >0 ; --i) {
			(_layer[i])->backprop();
		}
	}
		
	void FFOnLineBackNet::update_weight(int c)
	{
		for (unsigned int i = 1; i < _synapse.size()-1; ++i) {
			(_synapse[i])->adjuste_weight(_learning_rate,c,_momentum);
		}
	}
			
	void FFOnLineBackNet::compute_error()	
	{
		for(int i=0;i<_out; i++)
		{
			double e=(_synapse[_synapse.size()-1])->get_error(i);
			_global_error += (e*e)/2;
		}
	}
	
	void FFOnLineBackNet::trainNet()
	{
		for(int current_cicle=0;current_cicle<train_cicles;current_cicle++)
		{
			_global_error=0;
			_rmse=0;
			for(int l_index=0;l_index<inlenght;l_index++)
			{
				set_index(l_index);
				forward_input();
				back_error();
				compute_error();
				update_weight(current_cicle);
			}
			
			_global_error/=inlenght;
			_rmse=sqrt(_global_error);
			
			if(!(current_cicle%100))
			{
				cout<<"Ciclo num: "<<current_cicle+1<<" ";
				cout<<" Errore: "<<_global_error<<" RMSE: "<<_rmse<<"\n";
			}
		}
	}
	
	void FFOnLineBackNet::testNet()
	{
		_global_error=0;
		for(int l_index=0;l_index<inlenght;l_index++)
		{
			forward_input();
			compute_error();
		}
		_global_error/=inlenght;
		cout<<"Errore globale "<<_global_error<<"\n";
		_rmse=sqrt(_global_error);
		cout<<"RMSE "<<_rmse<<"\n";
	}
	
	doubleMat FFOnLineBackNet::getNetOut()
	{
		doubleMat out_value = doubleMat(inlenght,_out);
		for(int l_index=0;l_index<inlenght;l_index++)
		{
			forward_input();
			for(int i=0;i<_out; i++)
			{
				out_value(l_index,i)=(_synapse[_synapse.size()-1])->get_input(i);
				cout<<"Uscita n."<<i<<"=>"<<out_value(l_index,i)<<"\n";
			}
		}
		return out_value;
	}
	
	void FFOnLineBackNet::setPattern(doubleMat inp, doubleMat ex, int lenght,int out)
	{
		(_synapse[0])->set_pattern_input(inp);
		(_synapse[_synapse.size()-1])->set_example(ex);
		inlenght=lenght;
		_out=out;
	}
	
}
