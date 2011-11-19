/**
*  Factory.h
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

#ifndef FACTORY_
#define FACTORY_
#include "Neuron.h"
#include "Layer.h"
#include "Synapse.h"
#include "Net.h"
namespace Mnetlib
{
	
	class NeuronClassFactory
	{
	public:
		virtual ~NeuronClassFactory(){};
		virtual Neuron* create()=0;
		virtual std::string name()=0;

	};

	template < class T >
	class NeuronFactoryWrapper : public NeuronClassFactory
	{
	public:
	virtual ~NeuronFactoryWrapper(){};
	virtual Neuron* create(){ return T::create();}
	virtual std::string name(){ return T::name();}
	};
	
	class LayerClassFactory
	{
	public:
		virtual ~LayerClassFactory(){};
		virtual Layer* create(const int n)=0;
		virtual std::string name()=0;

	};

	template < class T >
	class LayerFactoryWrapper : public LayerClassFactory
	{
	public:
	virtual ~LayerFactoryWrapper(){};
	virtual Layer* create(const int n){ return T::create(n);}
	virtual std::string name(){ return T::name();}
	};
	
	class SynapseClassFactory
	{
	public:
		virtual ~SynapseClassFactory(){};
		virtual Synapse* create(const int n, const int l)=0;
		virtual std::string name()=0;

	};

	template < class T >
	class SynapseFactoryWrapper : public SynapseClassFactory
	{
	public:
	virtual ~SynapseFactoryWrapper(){};
	virtual Synapse* create(const int n, const int l){ return T::create(n,l);}
	virtual std::string name(){ return T::name();}
	};
	
	class NetClassFactory
	{
	public:
		virtual ~NetClassFactory(){};
		virtual NetSPtr create()=0;
		virtual std::string name()=0;

	};

	template < class T >
	class NetFactoryWrapper : public NetClassFactory
	{
	public:
	virtual ~NetFactoryWrapper(){};
	virtual NetSPtr create(){ return T::create();}
	virtual std::string name(){ return T::name();}
	};
}	
#endif /*FACTORY_*/
