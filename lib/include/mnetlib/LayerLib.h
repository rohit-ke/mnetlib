/**
 *  LayerLib.h
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

#ifndef LAYERLIB_H_
#define LAYERLIB_H_

#include <string>
#include "Layer.h"

namespace Mnetlib
{
  typedef boost::shared_ptr<Layer> LayerSPtr;

  class OnLineLayer : public Layer
  {
  public:
    OnLineLayer(int n):Layer(n){};
    virtual ~OnLineLayer(){};
    static OnLineLayer* create(const int n){ return new OnLineLayer(n);};
    static std::string name(){ return "online";} ;
    void backprop();
    std::string toString();
  };

  class OffLineLayer : public Layer
  {
  public:
    OffLineLayer(int n):Layer(n){};
    virtual ~OffLineLayer(){};
    static OffLineLayer* create(const int n){ return new OffLineLayer(n);};
    static std::string name(){ return "offline";} ;
    void backprop();
    std::string toString();
  };

  class InputLayer : public Layer
  {
  public:
    InputLayer(int n):Layer(n){};
    virtual ~InputLayer(){};
    static InputLayer* create(const int n){ return new InputLayer(n);};
    static std::string name(){ return "inputLayer";} ;
    //void forward();
    std::string toString();
  };

  class OutputLayer : public Layer
  {
  public:
    OutputLayer(int n):Layer(n){};
    virtual ~OutputLayer(){};
    static OutputLayer* create(const int n){ return new OutputLayer(n);};
    static std::string name(){ return "outputLayer";} ;
    void backprop();
    std::string toString();
  };

  class HiddenLayer : public Layer
  {
  public:
    HiddenLayer(int n):Layer(n){};
    virtual ~HiddenLayer(){};
    static HiddenLayer* create(const int n){ return new HiddenLayer(n);};
    static std::string name(){ return "hiddenLayer";} ;
    void backprop();
    std::string toString();
  };
}

#endif /*LAYERLIB_H_*/
