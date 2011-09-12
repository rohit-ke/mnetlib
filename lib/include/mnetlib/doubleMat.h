/**
*  doubleMat.h
*  mnetlib
*
*  This file is part of mnetlib.
*
*  mnetlib is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  mnetlib is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with mnetlib; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*
*  Copyright (C) 2007 by francesco.amenta
*  francesco.amenta@gmail.com
*
*/
 
#ifndef DOUBLEMAT_H
#define DOUBLEMAT_H

#include <stdio.h>
#include <stdlib.h>

namespace Mnetlib
{

  class doubleMat
  {
  public:
    doubleMat();
    doubleMat(const doubleMat& m);
    doubleMat(int n, int m);
    doubleMat(int n);
    ~doubleMat();

    const doubleMat& operator=(const doubleMat& m);
    double* getData(){return _data;};

    double& operator() (int row, int col);
    double  operator() (int row, int col) const;

    double& operator() (int row);
    double  operator() (int row) const;
  private:
    double* _data;
    int _row, _col;


  };

}

#endif
