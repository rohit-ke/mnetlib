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
//#define DEBUG
#include "Learner.h"
#include "CommonMacro.h"
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

namespace Mnetlib{
	
	Learner::Learner(){}
	
	Learner::~Learner()
	{}
	
	void Learner::setNet(NetSPtr iNet)
	{
	  DEBUG_MSG("Setting Net");
	  _Net=iNet;
	}

	NetSPtr Learner::getNet()
	{
	  return _Net;
	}

	void * Learner::trainNet(void * arg)
	{
	  struct info* f=(struct info*)arg;
	  try{
	      Registry reg;
	      NetSPtr net=reg.getNewNet("ffonlineNet",f->trainNi,f->n,f->trainNo);
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

	  }catch (exception* e) { cout << e->what()<<"\n"; }
	  return 0;
	}
	
	void Learner::trainNet(Net* ioNet)
	{
	  try{
	      INFO_MSG("Starting net train");
	      //f->trainI.putvalue();
	      //train net
	      DEBUG_MSG("Setting pattern");
	      ioNet->setPattern(trainPattern->dataIn,trainPattern->dataOut,trainLenght,testNcO);
	      DEBUG_MSG("Setting net parameter");
	      ioNet->set_parameter(learning_rate,momentum,train_cicles);
	      ioNet->trainNet();
	      //test net
	      ioNet->setPattern(testPattern->dataIn,testPattern->dataOut,testLenght,trainNcO);
	      ioNet->testNet();
	      double ret=ioNet->getGlobalError();
	      double mse=ioNet->getRMSE();
	      //Salvo nella struttura dati l'errore globale della rete appena creata
	      INFO_MSG("Testing Dataset: GLOBERR--> "<< ret);
	      INFO_MSG("Testing Dataset: RMSE--> "<< mse);

	  }
	  catch (std::exception* e) { cout<< "Error durin net train.\n" << e->what()<<"\n"; }
	}

	void Learner::kFoldTrainNet(int kValue)
	{
          try{
              INFO_MSG("Starting net train");
              DEBUG_MSG("Setting pattern");
              //_Net->setPattern(trainPattern->dataIn,trainPattern->dataOut,trainLenght,testNcO);
              DEBUG_MSG("Setting net parameter");
              _Net->set_parameter(learning_rate,momentum,train_cicles);
              PatternSPtr aTestPattern(new Pattern()),aValidatePattern(new Pattern());
              for(int run=0;run<kValue; run++ )
                {
                  DEBUG_MSG("Building the data set");
                  this->buildKSequentialTrainPattern(trainPattern,kValue,run,aTestPattern,aValidatePattern);
                  DEBUG_MSG("Setting parameter");
                  _Net->setPattern(aTestPattern->dataIn,aTestPattern->dataOut,aTestPattern->getLenght(),aTestPattern->getNout());
                  DEBUG_MSG("Training the net");
                  _Net->trainNet();
                  //test net
                  INFO_MSG("Setting test data set");
                  _Net->setPattern(aValidatePattern->dataIn,aValidatePattern->dataOut,aValidatePattern->getLenght(),aValidatePattern->getNout());
                  INFO_MSG("Testing the net");
                  _Net->testNet();
                  double ret=_Net->getGlobalError();
                  double mse=_Net->getRMSE();
                  //Salvo nella struttura dati l'errore globale della rete appena creata
                  INFO_MSG("Testing Dataset: GLOBERR--> "<< ret);
                  INFO_MSG("Testing Dataset: RMSE--> "<< mse);
                }
          }
          catch (std::exception* e) { cout<< "Error occurred while training the net.\n" << e->what()<<"\n"; }
          catch ( ... ) {cout << "kFoldTrainNet: Unknown exception while training the net\n";}

	}

	void Learner::trainNet()
	{
	  try{
	      INFO_MSG("Starting net train");
	      DEBUG_MSG("Setting pattern");
	      _Net->setPattern(trainPattern->dataIn,trainPattern->dataOut,trainLenght,trainNcO);
	      DEBUG_MSG("Setting net parameter");
	      _Net->set_parameter(learning_rate,momentum,train_cicles);
              INFO_MSG("Training the net");
	      _Net->trainNet();
	      //test net
	      INFO_MSG("Setting test data set");

	      _Net->setPattern(testPattern->dataIn,testPattern->dataOut,testLenght,testNcO);
              INFO_MSG("Testing the net");
	      _Net->testNet();
	      double ret=_Net->getGlobalError();
	      double mse=_Net->getRMSE();
	      //Salvo nella struttura dati l'errore globale della rete appena creata
	      INFO_MSG("Testing Dataset: GLOBERR--> "<< ret);
	      INFO_MSG("Testing Dataset: RMSE--> "<< mse);

	  }
	  catch (std::exception* e) { cout<< "Error occurred while training the net.\n" << e->what()<<"\n"; }
	  catch (boost::exception* e)
	      {
	              //ERROR_MSG("Error during net train.\n" << e->what());
	          std::cout << e;
	      }
	  catch ( ... ) {cout << "Unknown exception while training the net\n";}
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
		trainPattern=PatternSPtr(new Pattern());
		trainPattern->loadPatternFile(datafile);
		trainLenght=trainPattern->getLenght();
		trainNcI=trainPattern->getNin();
		trainNcO=trainPattern->getNout();
	}
	
	void Learner::buildTestPattern(string datafile)
	{
		testPattern=PatternSPtr(new Pattern());
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

	void Learner::set_parameter(double n,double m, int c)
	{
	  learning_rate=n;
	  momentum=m;
	  train_cicles=c;
	}

        void Learner::buildKRandomTrainPattern(PatternSPtr iPattern, int k, PatternSPtr oTestPattern, PatternSPtr oValidatePattern)
        {

        }

        void Learner::buildKSequentialTrainPattern(PatternSPtr iPattern, int k, int seq, PatternSPtr& oTestPattern, PatternSPtr& oValidatePattern)
        {
          try{
          int aValidateTestSize=iPattern->getLenght()/k +iPattern->getLenght()%k;
          INFO_MSG("Validate set size:" << aValidateTestSize);

          int aGenericTestSetSize = (iPattern->getLenght()-aValidateTestSize)/(k-1);
          INFO_MSG("Generic set size:" << aGenericTestSetSize);

          oValidatePattern->dataIn= matrix<double>(aValidateTestSize,iPattern->getNin());
          oValidatePattern->dataOut= matrix<double>(aValidateTestSize,iPattern->getNout());
          oTestPattern->dataIn= matrix<double>(aGenericTestSetSize*(k-1),iPattern->getNin());
          oTestPattern->dataOut= matrix<double>(aGenericTestSetSize*(k-1),iPattern->getNout());


          int index=0;
          INFO_MSG("Building Test set. Current index: " << index);
          for(int i=0; i<aGenericTestSetSize*seq; i++)
            {
              for(int z=0; z<iPattern->getNin();z++)
                {
                  oTestPattern->dataIn(i,z)=iPattern->dataIn(index,z);
                }
              for(int l=0; l<iPattern->getNout();l++)
                {
                  oTestPattern->dataOut(i,l)=iPattern->dataOut(index,l);
                }
              index++;
            }
          INFO_MSG("Building Validation set. Current index: " << index);
          for(int i=0; i<aValidateTestSize; i++)
            {
              for(int z=0; z<iPattern->getNin();z++)
                 {
                  oValidatePattern->dataIn(i,z)=iPattern->dataIn(index,z);
                 }
               for(int l=0; l<iPattern->getNout();l++)
                 {
                   oValidatePattern->dataOut(i,l)=iPattern->dataOut(index,l);
                 }
              //DEBUG_MSG("index: " << index);
              //DEBUG_MSG("In data: " << aValidateDataIn(i,1));
              //DEBUG_MSG("Out data: " << aValidateDataOut(i,1));
              index++;
            }

          INFO_MSG("Building Test set. Current index: " << index);
          for(int i=0; i<aGenericTestSetSize*(k-seq -1); i++)
            {
              //aTestDataIn.
              //aTestDataIn(i)=iPattern->dataIn(index);
              //aTestDataOut(i)=iPattern->dataOut(index);
              for(int z=0; z<iPattern->getNin();z++)
                {
                  oTestPattern->dataIn(i,z)=iPattern->dataIn(index,z);
                }
              for(int l=0; l<iPattern->getNout();l++)
                {
                  oTestPattern->dataOut(i,l)=iPattern->dataOut(index,l);
                }
              index++;
              //DEBUG_MSG("index: " << index);
              //DEBUG_MSG("In data: " << aTestDataIn(i,1));
              //DEBUG_MSG("Out data: " << aTestDataOut(i,1));
            }
          //oTestPattern->dataIn=aTestDataIn;
          //oTestPattern->dataOut=aTestDataOut;
          DEBUG_MSG("Dataset: Train in" <<  oTestPattern->dataIn.size1() << " - " << oTestPattern->dataIn.size2());
              DEBUG_MSG("Train Out " << oTestPattern->dataOut.size1() << " - " << oTestPattern->dataOut.size2() );

          }
                    catch (std::exception* e) { cout<< "Error occurred while training the net.\n" << e->what()<<"\n"; }
        }
}
