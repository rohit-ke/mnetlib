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
//#define DEBUG

#include <NetLib.h>
#include <CommonMacro.h>
#include <boost/numeric/ublas/matrix.hpp>
using namespace boost::numeric::ublas;

namespace Mnetlib
{
  FFOnLineBackNet::FFOnLineBackNet():Net()
  {
  }

  FFOnLineBackNet::~FFOnLineBackNet()
  {
    /*for (unsigned int n = 0; n < _synapse.size(); ++n)
		{
			delete (_synapse[n]);
		}
		for (unsigned int i = 0; i < _layer.size(); ++i)
		 {
			delete (_layer[i]);
		}*/
  }

  void FFOnLineBackNet::connect() const
  {
    std::vector<SynapseSPtr>::const_iterator aSynapseIt=_synapse.begin();
    for (std::vector<LayerSPtr>::const_iterator aLayerIt=_layer.begin(); aLayerIt!=_layer.end(); aLayerIt++)
      {
        SynapseSPtr InSynapse=*aSynapseIt;
        aSynapseIt++;
        if(aSynapseIt==_synapse.end())
          {
            throw new Mnetlib::InstantiationException("Connecting Net: Synapse vector is too short.");
          }
        SynapseSPtr OutSynapse=*aSynapseIt;
        (*aLayerIt)->connectLayer(InSynapse,OutSynapse);
      }
  }

  void FFOnLineBackNet::set_index(int i)
  {
    try
    {
        DEBUG_MSG("Setting index: " <<i);
        for (unsigned int n = 0; n < _synapse.size(); ++n) {
            (_synapse[n])->set_index(i);
        }
    }
    catch (std::exception* e)
    {
        ERROR_MSG("Error durin net train.\n" << e->what());
    }
  }

  void FFOnLineBackNet::forward_input()
  {
    try
    {
        DEBUG_MSG("Forward input");
        DEBUG_MSG("Layer size: " << _layer.size());

        foreach(LayerSPtr aLayer,_layer)
              {
            aLayer->forward();
              }
    }
    catch (std::exception* e)
    {
        ERROR_MSG("Error while forwarding the input.\n" << e->what());
    }
    catch (boost::exception* e)
    {
            //ERROR_MSG("Error during net train.\n" << e->what());
        std::cout << e;
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
    try
    {
        DEBUG_MSG("training FFOnlineNet");
        for(int current_cicle=0;current_cicle<train_cicles;current_cicle++)
          {
            _global_error=0;
            _rmse=0;
            DEBUG_MSG("Cicle: "<<current_cicle);
            for(int l_index=0;l_index<inlenght;l_index++)
              {
                set_index(l_index);
                DEBUG_MSG("Forwarding the input: index - " << l_index << " on " <<inlenght );
                forward_input();
                DEBUG_MSG("back error");
                back_error();
                DEBUG_MSG("compute error");
                compute_error();
                DEBUG_MSG("update weight");
                update_weight(current_cicle);
              }

            _global_error/=inlenght;
            _rmse=sqrt(_global_error);

            if(!(current_cicle%1))
              {
                cout<<"Ciclo num: "<<current_cicle+1<<" ";
                cout<<" Errore: "<<_global_error<<" RMSE: "<<_rmse<<"\n";
              }
          }
    }
    catch (std::exception* e)
    {
        cout<< "Error during net train.\n" << e->what()<<"\n";
    }
  }

  void FFOnLineBackNet::testNet()
  {
    _global_error=0;
    for(int l_index=0;l_index<inlenght;l_index++)
      {
        set_index(l_index);
        DEBUG_MSG("Forwarding the input: index - " << l_index << " on " <<inlenght );
        forward_input();
        DEBUG_MSG("compute error");
        compute_error();
      }
    _global_error/=inlenght;
    cout<<"Global Error: "<<_global_error<<"\n";
    _rmse=sqrt(_global_error);
    cout<<"RMSE: "<<_rmse<<"\n";
  }

  matrix<double>& FFOnLineBackNet::getNetOut()
  {
    matrix<double> out_value = matrix<double>(inlenght,_out);
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

  void FFOnLineBackNet::setPattern(matrix<double>& inp, matrix<double>& ex, int lenght,int out)
  {
    //string ssz2((unsigned long int&)inp.size2);
    DEBUG_MSG("Setting Patter: " << lenght << " - " << out << " -inp- " << inp.size1() << " - " << inp.size2()<< " -ex- " << ex.size1() << " - " << ex.size2() );
    (_synapse[0])->set_pattern_input(inp);
    (_synapse[_synapse.size()-1])->set_example(ex);
    inlenght=lenght;
    _out=out;
  }

  std::string FFOnLineBackNet::toString()
	{
	  std::string ret;
	  ret.append(this->name());
	  ret.append("\n");
	  for (unsigned int n = 0; n < _synapse.size(); ++n)
	    {
	      ret.append((_synapse[n])->toString());
	    }
	  for (unsigned int i = 0; i < _layer.size(); ++i)
	    {
	      ret.append((_layer[i])->toString());
	    }
	  return ret;
	}
}
