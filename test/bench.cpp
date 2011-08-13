/**
*  bench.cpp
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
*  Copyright (C) 2007 by neoairus
*   neoairus@gmail.com
*
*/

#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/resource.h>

#include "Learner.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <iostream>
#include <string>

using namespace Mnetlib;
using namespace std;
using std::cout;


int main(){
	struct timeb t1,t2;
	
	ftime(&t1);
	try{
	Learner* l=new Learner();
	l->buildTrainPattern("data/building.train");
	l->buildTestPattern("data/building.test");
	//Setto parametri: learning rate, momento, numero cicli, Hidden Min (neuroni interni), Hidden Max, numero thread
	l->set_parameter(0.15,0.4,150,4,10,2);
	//Lancio la creazione delle reti per torvare quella migliore
	
	l->findBestNet();
	delete l;		
	ftime(&t2);
	//Trovo la differenza di tempo tra start progetto e fine
	double sec=difftime(t2.time,t1.time);
	double ms=t2.millitm - t1.millitm;
	float elapsed = (float)( sec + ms / 1000.0 );
	cout<<" Real elapsed time: "<<elapsed<<"\n";
 
	
//		Registry reg;
//		Net* net=reg.getNewNet("ffonlineNet",14,3);
//		//f->trainI.putvalue();
//		//train net	
//		net->setPattern(f->trainI,f->trainO,f->trainLng,f->trainNo);
//		net->set_parameter(0.15,0.4,50);
//		net->trainNet();
//		//test net	
//		net->setPattern(f->testI,f->testO,f->testLng,f->trainNo);
//		net->testNet();
//		double ret=net->getGlobalError();
//		double mse=net->getRMSE();
//		//Salvo nella struttura dati l'errore globale della rete appena creata
//		f->err=ret;
//		cout<<"GLOBERR--> "<< ret<<" con nodi: "<< f->n <<"\n";
//		f->rmse=mse;
//		cout<<"RMSE--> "<< mse<<" con nodi: "<< f->n <<"\n";
//		delete net;
	}catch (exception* e) { cout << e->what()<<"\n"; }
	return(0);
}
