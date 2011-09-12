/**
*  Registry.h
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

#ifndef REGISTRY_H_
#define REGISTRY_H_

#include "NeuronLib.h"
#include "SynapseLib.h"
#include "LayerLib.h"
#include "NetLib.h"
#include "Factory.h"
#include <map>
namespace Mnetlib
{
	
	
	class Registry
	{
	public:
		Registry();
		~Registry();
		void registerNeuronFactory( NeuronClassFactory* factory)
		{
			_neuronRegistry[factory->name()]=factory;
		}
		void registerLayerFactory( LayerClassFactory* factory)
		{
			_layerRegistry[factory->name()]=factory;
		}
		void registerSynapseFactory( SynapseClassFactory* factory)
		{
			_synapseRegistry[factory->name()]=factory;
		}
		void registerNetFactory( NetClassFactory* factory)
		{
			_netRegistry[factory->name()]=factory;
		}
		NeuronSPtr getNewNeuron(const std::string& name);
		SynapseSPtr getNewSynapse(const std::string& name, const int n, const int l);
		LayerSPtr getNewLayer (const std::string& lName, const std::string& nName, const int n);
		Net* getNewNet(const std::string& name,const int ni, const int nh, const int no);
		Net* getNewNet(const std::string& path);
	protected:
			std::map<std::string, NeuronClassFactory*> _neuronRegistry;
			std::map<std::string, SynapseClassFactory*> _synapseRegistry;
			std::map<std::string, LayerClassFactory*> _layerRegistry;
			std::map<std::string, NetClassFactory*> _netRegistry;
			NeuronFactoryWrapper<SigmoidNeuron> sigmoidFactory;
			NeuronFactoryWrapper<LinearNeuron> linearFactory;
			LayerFactoryWrapper<InputLayer> inputFactory;
			LayerFactoryWrapper<HiddenLayer> hiddenFactory;
			LayerFactoryWrapper<OutputLayer> outputFactory;
			SynapseFactoryWrapper<InputSynapse> insinFactory;
			SynapseFactoryWrapper<HiddenSynapse> hiddensinFactory;
			SynapseFactoryWrapper<OutputSynapse> outsinFactory;
			NetFactoryWrapper<FFOnLineBackNet> ffonlineFactory;
	};

}
#endif /*REGISTRY_H_*/
