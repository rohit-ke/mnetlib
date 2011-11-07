/**
 *  SynapseLib.cpp
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

#include "SynapseLib.h"
#include <boost/lexical_cast.hpp>
#include "CommonMacro.h"

//TODO passare da daubleMat a boost:matrix
//TODO verificare utilizzo indici nell'hidden sinapse

namespace Mnetlib
{

  InputSynapse::InputSynapse(int iIn, int iOut):Synapse(iIn,iOut),weight(iOut,iIn)
  {
    //TODO assert iIn=iOut
  }

  InputSynapse::~InputSynapse()
  {

  }

  void InputSynapse::inizialize_weight()
  {
    for(int i=0;i<_in;i++)
      {
        weight(1,i)=(double)(1);
      }
  }

  double InputSynapse::get_input(int i)
  {
    return in_pattern(_index,i);
  }

  /*------------------------------*/

  OutputSynapse::OutputSynapse(int iIn, int iOut):Synapse(iIn,iOut),weight(1,iIn),in_vect(iIn),error(iIn)
  {
    //TODO assert iIn=iOut
  }

  OutputSynapse::~OutputSynapse()
  {

  }

  void OutputSynapse::inizialize_weight()
  {
    for(int i=0;i<_in;i++)
      {
        weight(1,i)=(double)(1);
      }
  }

  double OutputSynapse::get_input(int i)
  {
    return in_vect(i);
  }

  double OutputSynapse::get_error(int i)
  {
    return error(i);
  }

  void OutputSynapse::set_out(int i, double value)
  {
    in_vect(i)=value;
    error(i)=in_vect(i)-example(_index,i);
  }

  /*------------------------------*/

  HiddenSynapse::HiddenSynapse(int iIn, int iOut):Synapse(iIn,iOut),_weight(iOut,iIn),oldweight(iOut,iIn),in_vect(iIn),error(iIn),_gradient(iOut)
  {
    inizialize_weight();

  }

  HiddenSynapse::~HiddenSynapse()
  {

  }

  void HiddenSynapse::inizialize_weight()
  {

    for(int i=0;i<_out;i++)
      {
        for(int s=0;s<_in;s++)
          {
            _weight(i,s)=((double)(rand())/(double)(RAND_MAX-1))-0.5;
            if(_weight(i,s)>0.5 || _weight(i,s)<-0.5)
              cout<<"Peso sballato: "<<_weight(i,s)<<" indice n: "<<i<<" indice l: "<<s<<"\n";
          }
      }
  }

  double HiddenSynapse::get_input(int i)
  {
    DEBUG_MSG("get_input - invect size: " << in_vect.size() << " get param: " <<i);
    DEBUG_MSG("get_input - weight size: " << _weight.size1() <<"," << _weight.size2()<< " l size: " <<_in);
    double inp=0;
    for (int j=0;j<_in;j++)
      {
        inp +=in_vect(j)*_weight(i,j);
      }
    return inp;
  }

  double HiddenSynapse::get_error(int i)
  {
    DEBUG_MSG("get_error - error size: " << error.size() << " get param: " <<i);
    return error(i);
  }

  double HiddenSynapse::get_out(int i)
  {
    DEBUG_MSG("get_out - invect size: " << in_vect.size() << " get param: " <<i);
    return in_vect(i);
  }

  void HiddenSynapse::set_out(int i, double value)
  {
    in_vect(i)=value;
  }

  void HiddenSynapse::set_gradient(int i, double value)
  {
    DEBUG_MSG("set_gradient - gradient size: " << _gradient.size() << " get param: " <<i);
    DEBUG_MSG("set_gradient - weight size: " << _weight.size1() <<"," << _weight.size2()<< " l size: " <<_in);
    _gradient(i)=value;
    //double err=0;
    for (int j=0;j<_in;j++)
      {
        error(j) +=_gradient(i)*_weight(i,j);
      }
    DEBUG_MSG("set_gradient - error size: " << error.size());
    //error(i)=err;
    DEBUG_MSG("set_gradient - end");
  }

  void HiddenSynapse::adjuste_weight(double rate, int cicle, double momentum)
  {
    for (int i=0;i<_out;i++)
      {
        for (int j=0;j<_in;j++)
          {
            if(cicle==0 && _index==0)
              oldweight(i,j)=_weight(i,j);
            double tmp=_weight(i,j);
            _weight(i,j) -=rate*_gradient(i)*in_vect(j)-momentum*(tmp-oldweight(i,j));
            oldweight(i,j)=tmp;

          }
      }
    for (int j=0;j<_in;j++)
      {
        error(j)=0;
      }
  }

  std::string InputSynapse::toString()
  {
    std::string ret; ret.append("Synapse type: ");
    ret.append(this->name());
    ret.append("\n");
    ret.append(" in: ");
    ret += boost::lexical_cast<std::string>(this->_in);
    ret.append(" out:");
    ret += boost::lexical_cast<std::string>(this->_out);
    ret +="\n";
    return ret;
  }

  std::string HiddenSynapse::toString()
  {
    std::string ret; ret.append("Synapse type: ");
    ret.append(this->name());
    ret.append("\n");
    ret.append(" in: ");
    ret += boost::lexical_cast<std::string>(this->_in);
    ret.append(" out:");
    ret += boost::lexical_cast<std::string>(this->_out);
    ret +="\n";
    return ret;
  }

  std::string OutputSynapse::toString()
  {
    std::string ret; ret.append("Synapse type: ");
    ret.append(this->name());
    ret.append("\n");
    ret.append(" in: ");
    ret += boost::lexical_cast<std::string>(this->_in);
    ret.append(" out:");
    ret += boost::lexical_cast<std::string>(this->_out);
    ret +="\n";
    return ret;
  }

}
