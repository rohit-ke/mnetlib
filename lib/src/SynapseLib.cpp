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

#include "SynapseLib.h"
#include <boost/lexical_cast.hpp>

//TODO passare da daubleMat a boost:matrix
//TODO verificare utilizzo indici nell'hidden sinapse

namespace Mnetlib
{

  InputSynapse::InputSynapse(int n, int l):Synapse(n,l),weight(1,n)
  {

  }

  InputSynapse::~InputSynapse()
  {

  }

  void InputSynapse::inizialize_weight()
  {
    for(int i=0;i<_n;i++)
      {
        weight(1,i)=(double)(1);
      }
  }

  double InputSynapse::get_input(int i)
  {
    return in_pattern(_index,i);
  }

  /*------------------------------*/

  OutputSynapse::OutputSynapse(int n, int l):Synapse(n,l),weight(1,n),in_vect(n),error(n)
  {

  }

  OutputSynapse::~OutputSynapse()
  {

  }

  void OutputSynapse::inizialize_weight()
  {
    for(int i=0;i<_n;i++)
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

  HiddenSynapse::HiddenSynapse(int n, int l):Synapse(n,l),weight(n,l),oldweight(n,l),in_vect(l),error(l),gradient(n)
  {
    inizialize_weight();

  }

  HiddenSynapse::~HiddenSynapse()
  {

  }

  void HiddenSynapse::inizialize_weight()
  {

    for(int i=0;i<_n;i++)
      {
        for(int s=0;s<_l;s++)
          {
            weight(i,s)=((double)(rand())/(double)(RAND_MAX-1))-0.5;
            if(weight(i,s)>0.5 || weight(i,s)<-0.5)
              cout<<"Peso sballato: "<<weight(i,s)<<" indice n: "<<i<<" indice l: "<<s<<"\n";
          }
      }
  }

  double HiddenSynapse::get_input(int i)
  {
    double inp=0;
    for (int j=0;j<_l;j++)
      {
        inp +=in_vect(j)*weight(i,j);
      }
    return inp;
  }

  double HiddenSynapse::get_error(int i)
  {
    return error(i);
  }

  double HiddenSynapse::get_out(int i)
  {
    return in_vect(i);
  }

  void HiddenSynapse::set_out(int i, double value)
  {
    in_vect(i)=value;
  }

  void HiddenSynapse::set_gradient(int i, double value)
  {
    gradient(i)=value;
    double err=0;
    for (int j=0;j<_n;j++)
      {
        err +=gradient(j)*weight(j,i);
      }
    error(i)=err;
  }

  void HiddenSynapse::adjuste_weight(double rate, int cicle, double momentum)
  {
    for (int i=0;i<_n;i++)
      {
        for (int j=0;j<_l;j++)
          {
            if(cicle==0 && _index==0)
              oldweight(i,j)=weight(i,j);
            double tmp=weight(i,j);
            weight(i,j) -=rate*gradient(i)*in_vect(j)-momentum*(tmp-oldweight(i,j));
            oldweight(i,j)=tmp;

          }
      }
  }

  std::string InputSynapse::toString()
  {
    std::string ret; ret.append("Synapse type: ");
    ret.append(this->name());
    ret.append("\n");
    ret.append(" l: ");
    ret += boost::lexical_cast<std::string>(this->_l);
    ret.append(" n:");
    ret += boost::lexical_cast<std::string>(this->_n);
    ret +="\n";
    return ret;
  }

  std::string HiddenSynapse::toString()
  {
    std::string ret; ret.append("Synapse type: ");
    ret.append(this->name());
    ret.append("\n");
    ret.append(" l: ");
    ret += boost::lexical_cast<std::string>(this->_l);
    ret.append(" n:");
    ret += boost::lexical_cast<std::string>(this->_n);
    ret +="\n";
    return ret;
  }

  std::string OutputSynapse::toString()
  {
    std::string ret; ret.append("Synapse type: ");
    ret.append(this->name());
    ret.append("\n");
    ret.append(" l: ");
    ret += boost::lexical_cast<std::string>(this->_l);
    ret.append(" n:");
    ret += boost::lexical_cast<std::string>(this->_n);
    ret +="\n";
    return ret;
  }

}
