/**
 *  LayerLib.cpp
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

#include "LayerLib.h"
#include <boost/lexical_cast.hpp>

namespace Mnetlib
{
  void OffLineLayer::backprop()
  {}
  void OnLineLayer::backprop()
  {}

  void OutputLayer::backprop()
  {
    for(int i=0; i<_n;i++)
      {
        NeuronSPtr aux;
        aux=vect.at(i);
        double o=_outsin->get_input(i);
        double e=_outsin->get_error(i);
        //calcolo il gradiente
        _insin->set_gradient(i,aux->RunBack(o,e));
      }
  }

  void HiddenLayer::backprop()
  {
    for(int i=0; i<_n;i++)
      {
        NeuronSPtr aux;
        aux=vect.at(i);
        double o=_outsin->get_out(i);
        double e=_outsin->get_error(i);
        //calcolo il gradiente
        _insin->set_gradient(i,aux->RunBack(o,e));
      }
  }

  std::string OffLineLayer::toString()
  {
    std::string ret; ret.append("Layer type: ");
    ret.append(this->name());
    ret.append(" n: ");
    ret += boost::lexical_cast<std::string>(this->_n);
    ret +="\n";
    return ret;
  }

  std::string OnLineLayer::toString()
  {
    std::string ret; ret.append("Layer type: ");
    ret.append(this->name());
    ret.append(" n: ");
    ret += boost::lexical_cast<std::string>(this->_n);
    ret +="\n";
    return ret;
  }

  std::string InputLayer::toString()
  {
    std::string ret; ret.append("Layer type: ");
    ret.append(this->name());
    ret.append(" n: ");
    ret += boost::lexical_cast<std::string>(this->_n);
    ret +="\n";
    return ret;
  }

  std::string HiddenLayer::toString()
  {
    std::string ret; ret.append("Layer type: ");
    ret.append(this->name());
    ret.append(" n: ");
    ret += boost::lexical_cast<std::string>(this->_n);
    ret +="\n";
    return ret;
  }

  std::string OutputLayer::toString()
  {
    std::string ret; ret.append("Layer type: ");
    ret.append(this->name());
    ret.append(" n: ");
    ret += boost::lexical_cast<std::string>(this->_n);
    ret +="\n";
    return ret;
  }
}
