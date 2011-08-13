/**
*  Learner.cpp
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
//TODO Aggiungere supporto mpi mp pthread
#include "Learner.h"

namespace Mnetlib{
	
	Learner::Learner(){}
	
	Learner::~Learner()
	{
		delete trainPattern;
		delete testPattern;
	}
	
	void * Learner::trainNet(void * arg)
	{
		struct info* f=(struct info*)arg;
		try{
			Registry reg;
			Net* net=reg.getNewNet("ffonlineNet",f->trainNi,f->n,f->trainNo);
			//f->trainI.putvalue();
		//train net	
			net->setPattern(f->trainI,f->trainO,f->trainLng,f->trainNo);
			net->set_parameter(f->l,f->m,f->c);
			net->trainNet();
		//test net	
			net->setPattern(f->testI,f->testO,f->testLng,f->trainNo);
			net->testNet();
			double ret=net->getGlobalError();
			double mse=net->getRMSE();
		//Salvo nella struttura dati l'errore globale della rete appena creata
			f->err=ret;
			cout<<"GLOBERR--> "<< ret<<" con nodi: "<< f->n <<"\n";
			f->rmse=mse;
			cout<<"RMSE--> "<< mse<<" con nodi: "<< f->n <<"\n";
			delete net;
		}catch (exception* e) { cout << e->what()<<"\n"; }
		return 0;
	}
	
	int Learner::findBestNet()
	{
	
		info* fx;
		fx=(info*)malloc(sizeof(info)*Nthread);
		
		double err_min=1;
		int nodi=-1;
	
		for (int i=0; i<Nthread; i++)
		{
			fx[i].c=train_cicles;
			fx[i].trainI=trainPattern->dataIn;
			fx[i].trainO=trainPattern->dataOut;
			fx[i].trainLng=trainLenght;
			fx[i].testI=testPattern->dataIn;
			fx[i].testO=testPattern->dataOut;
			fx[i].testLng=testLenght;
			fx[i].l=learning_rate;
			fx[i].m=momentum;
			fx[i].trainNi=trainNcI;
			fx[i].trainNo=trainNcO;
			fx[i].testNi=testNcI;
			fx[i].testNo=testNcO;
		}

	//Creo thread che testano le reti neurali con numero diverso di nodi interni
		for(int i=minHidden;i<=maxHidden;i+=Nthread)
		{	int NumX;
			if ((i+Nthread)>maxHidden)
				{
					NumX=maxHidden - i +1;
				}
				else
					{
					 NumX=Nthread;
					}
			
			pthread_t* Threadx;
			Threadx=(pthread_t*)malloc(sizeof(pthread_t)*NumX);
			for (int j=0; j<NumX; j++)
			{
				//setto numero neuroni interni
				fx[j].n=i+j;
				cout<<"Nhidden = "<<fx[j].n<<"  ||  ";
				//creao istanze del thread
				int cd=pthread_create(&Threadx[j], NULL, Learner::trainNet, &fx[j]);
				if (cd!=0) 
				{
					cout<<"errore nella creazione thread \n\n";
					exit(1);
				}
			}
			cout<<"\n";
			
			for (int j=0; j<NumX; j++)
			{			
				pthread_join(Threadx[j],NULL);
				if (fx[j].err<err_min)	
				{
					err_min=fx[j].err;
					nodi=fx[j].n;
				}
			}
		}
		cout<<"\n\n"<<"Errore minimo ==> "<<err_min<<"  con Num nodi = "<<nodi<<"\n\n";
		delete fx;
		return nodi;
	}
	
	void Learner::buildTrainPattern(string datafile)
	{
		trainPattern=new Pattern();
		trainPattern->loadPatternFile(datafile);
		trainLenght=trainPattern->getLenght();
		trainNcI=trainPattern->getNin();
		trainNcO=trainPattern->getNout();
	}
	
	void Learner::buildTestPattern(string datafile)
	{
		testPattern=new Pattern();
		testPattern->loadPatternFile(datafile);
		testLenght=testPattern->getLenght();
		testNcI=testPattern->getNin();
		testNcO=testPattern->getNout();
	}
	
	void Learner::set_parameter(double n,double m, int c, int Hmin, int Hmax, int Nth)
	{
		learning_rate=n;
		momentum=m;
		train_cicles=c;
		minHidden=Hmin;
		maxHidden=Hmax;
		Nthread=Nth;
	}
}
