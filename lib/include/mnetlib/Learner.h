/**
*  Learner.h
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

#ifndef LEARNER_H_
#define LEARNER_H_

#include "Pattern.h"
#include "Net.h"
#include "Registry.h"
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <iostream>
#include <string>

namespace Mnetlib
{

	class Learner
	{
	public:
		
		/*
		 * Costruttore di default
		 */
		Learner();
		
		/*
		 * Distruttore di default
		 */
		virtual ~Learner();
		
		/*Costruisce i pattern d'apprendimento*/
		void buildTrainPattern(string datafile);
		
		/*Costruisce i pattern d'apprendimento*/
		void buildTestPattern(string datafile);
		
		void buildKRandomTrainPattern(PatternSPtr iPattern, int k, PatternSPtr oTestPattern, PatternSPtr oValidatePattern);

                void buildKSequentialTrainPattern(PatternSPtr iPattern, int k, int seq, PatternSPtr& oTestPattern, PatternSPtr& oValidatePattern);

                /*Costruisce la rete e mostra i risultati del train*/
		static void * trainNet(void * arg);
		
                void trainNet(Net* ioNet);

                void trainNet();

                void kFoldTrainNet(int kValue);

                void setNet(NetSPtr iNet);

                NetSPtr getNet();

		int findBestNet();
		
		/* 
		 * Setta i parametri d'apprendimento della rete
		 * 
		 * @param n learning-rate
		 * @param m momento
		 * @param c cicli d'apprendimento 
		 */
		void set_parameter(double n,double m, int c, int Hmin, int Hmax, int Nth);
		
		void set_parameter(double n,double m, int c);
		
	private:
			PatternSPtr trainPattern;
			PatternSPtr testPattern;
			string patternFile;
			int maxHidden;
			int minHidden;
			int trainLenght;
			int trainNcI;
			int trainNcO;
			int testLenght;
			int testNcI;
			int testNcO;
			double error;//memorizza l'errore del ciclo corrente
			double learning_rate;
			double momentum;
			int mode;
			int train_cicles;//memorizza il numero massimo di cicli d'apprendimento
			int Nthread;
			NetSPtr _Net;
				struct info
				{
					int trainNi;
					int trainNo;
					ublas::matrix<double> trainI;
					ublas::matrix<double> trainO;
					int trainLng;
					int testNi;
					int testNo;
					ublas::matrix<double> testI;
					ublas::matrix<double> testO;
					int testLng;
					double l;
					double m;
					int mo;
					int c;
					int n;
					double err;
					double rmse;
				};
				

	};

	typedef boost::shared_ptr<Learner> LearnerSPtr;
}

#endif //LEARNER_H_
