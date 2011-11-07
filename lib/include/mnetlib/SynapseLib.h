/**
 *  SynapseLib.h
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

#ifndef SYNAPSELIB_H_
#define SYNAPSELIB_H_
#include <string>
#include "Synapse.h"


namespace Mnetlib
{
  typedef boost::shared_ptr<Synapse> SynapseSPtr;

  class InputSynapse: public Synapse
  {
  public:
    InputSynapse(int iIn, int iOut);

    virtual ~InputSynapse();

    static InputSynapse* create(const int n, const int l){ return new InputSynapse(n,l);};

    static std::string name(){ return "inputSynapse";};

    void inizialize_weight();

    void set_pattern_input(doubleMat p){in_pattern=p;};

    double get_input(int i);

    void set_index(int i){_index=i;};

    ublas::matrix<double> get_weight(){return weight;};

    void set_weight(ublas::matrix<double> w){weight=w;};

    std::string toString();
  protected:
    ublas::matrix<double> weight;
    doubleMat in_pattern;
  };

  class OutputSynapse: public Synapse
  {
  public:
    OutputSynapse(int iIn, int iOut);

    virtual ~OutputSynapse();

    static OutputSynapse* create(const int n, const int l){ return new OutputSynapse(n,l);};

    static std::string name(){ return "outputSynapse";};

    void inizialize_weight();

    void set_index(int i){_index=i;};

    void set_example(doubleMat ex){example=ex;};

    double get_input(int i);

    double get_error(int i);

    void set_out(int i, double value);

    ublas::matrix<double> get_weight(){return weight;};

    void set_weight(ublas::matrix<double> w){weight=w;};

    std::string toString();
  protected:
    ublas::matrix<double> weight;
    ublas::vector<double> in_vect,error;
    doubleMat example;
  };

  class HiddenSynapse: public Synapse
  {
  public:
    HiddenSynapse(int iIn, int iOut);

    virtual ~HiddenSynapse();

    static HiddenSynapse* create(const int n, const int l){ return new HiddenSynapse(n,l);};

    static std::string name(){ return "hiddenSynapse";};

    void inizialize_weight();

    void set_index(int i){_index=i;};

    double get_input(int i);

    double get_out(int i);

    double get_error(int i);

    void set_out(int i, double value);

    void set_gradient(int i, double value);

    void adjuste_weight(double rate, int cicle, double momentum);

    ublas::matrix<double> get_weight(){return _weight;};

    void set_weight(ublas::matrix<double> w){_weight=w;};

    std::string toString();
  protected:
    ublas::matrix<double> _weight,oldweight,_previousDelta;
    ublas::vector<double> in_vect,error,_gradient;

  };
}
#endif /*SYNAPSELIB_H_*/
