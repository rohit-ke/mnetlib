/**
*  Registry.cpp
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


#include "Registry.h"
namespace Mnetlib
{
		Registry::Registry()
		{
			registerNeuronFactory(&linearFactory);
			registerNeuronFactory(&sigmoidFactory);
			registerLayerFactory(&inputFactory);
			registerLayerFactory(&hiddenFactory);
			registerLayerFactory(&outputFactory);
			registerSynapseFactory(&insinFactory);
			registerSynapseFactory(&hiddensinFactory);
			registerSynapseFactory(&outsinFactory);
			registerNetFactory(&ffonlineFactory);
		}
		
		Registry::~Registry()
		{
			
		}
		
		Neuron* Registry::getNewNeuron(const std::string& name)
		{
			if ( _neuronRegistry[name] )
			{
				return _neuronRegistry[name]->create();
			}
			
			return 0;
		}
		
		Layer* Registry::getNewLayer (const std::string& lName, const std::string& nName , const int n)
		{
			if ( _layerRegistry[lName] )
			{
				Layer* l=_layerRegistry[lName]->create(n);
				if ( _neuronRegistry[nName] )
				{
					vector<Neuron*> v;
					for (int s = 0; s < n; ++s) 
					{
						v.push_back(getNewNeuron(nName));
					}
					l->setVector(v);
				}
				return l;
			}
			return 0;
		}
		
		Synapse* Registry::getNewSynapse(const std::string& name, const int n, const int l)
		{
			if (_synapseRegistry[name]) {
				return _synapseRegistry[name]->create(n,l);
			}
			return 0;
		}

		Net* Registry::getNewNet(const std::string& name,const int ni, const int nh, const int no)
		{
			if ( _netRegistry[name] )
			{
				Net* net=_netRegistry[name]->create();
				vector<Synapse*> vs;
				vector<Layer*> vl;
				Synapse* s1=getNewSynapse("inputSynapse",ni,1);
				Synapse* s2=getNewSynapse("hiddenSynapse",nh,ni);
				Layer* l=getNewLayer("inputLayer","linear",ni);
				l->connectLayer(s1,s2);
				vl.push_back(l);
				vs.push_back(s1);
				s1=getNewSynapse("hiddenSynapse",no,nh);
				l=getNewLayer("hiddenLayer","linear",nh);
				l->connectLayer(s2,s1);
				vl.push_back(l);
				vs.push_back(s2);
				s2=getNewSynapse("outputSynapse",no,1);
				l=getNewLayer("outputLayer","linear",no);
				l->connectLayer(s1,s2);
				vl.push_back(l);
				vs.push_back(s1);
				vs.push_back(s2);
				net->setLayer(vl);
				net->setSynapse(vs);
				return net;
			}
			
			return 0;
		}
}
