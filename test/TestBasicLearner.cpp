/*
 * TestBasicLearner.cpp
 *
 *  Created on: 04/set/2011
 *      Author: totoro
 */


#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/resource.h>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "mnetlib/Registry.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <iostream>
#include <string>

using namespace Mnetlib;
using namespace std;
using std::cout;
using namespace xercesc;

int main(){
//        struct timeb t1,t2;

//        ftime(&t1);
        try{
/*
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
*/


              Registry reg;
              Net* net=reg.getNewNet("/home/totoro/workspace/mnetlib1/test/data/TestBasicLearner.xml");
//              //f->trainI.putvalue();
//              //train net
//              net->setPattern(f->trainI,f->trainO,f->trainLng,f->trainNo);
//              net->set_parameter(0.15,0.4,50);
//              net->trainNet();
//              //test net
//              net->setPattern(f->testI,f->testO,f->testLng,f->trainNo);
//              net->testNet();
//              double ret=net->getGlobalError();
//              double mse=net->getRMSE();
//              //Salvo nella struttura dati l'errore globale della rete appena creata
//              f->err=ret;
//              cout<<"GLOBERR--> "<< ret<<" con nodi: "<< f->n <<"\n";
//              f->rmse=mse;
//              cout<<"RMSE--> "<< mse<<" con nodi: "<< f->n <<"\n";
//              delete net;
        }catch (exception* e) { cout << e->what()<<"\n"; }
        catch (std::exception e) {
                cout << "Unexpected Exception \n" ;
                cout<< e.what();
                return 0;
            }
        catch (const XMLException& toCatch) {
                char* message = XMLString::transcode(toCatch.getMessage());
                cout << "Exception message is: \n"
                    << message << "\n";
                XMLString::release(&message);
                return 0;
            }
            catch (const DOMException& toCatch) {
                char* message = XMLString::transcode(toCatch.msg);
                cout << "Exception message is: \n"
                    << message << "\n";
                XMLString::release(&message);
                return 0;
            }
        return(0);
}


