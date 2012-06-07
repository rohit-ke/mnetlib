/*
 * TestBasicLearner.cpp
 *
 *  Created on: 04/set/2011
 *      Author: totoro
 */

#define DEBUG


#include <mnetlib/CommonMacro.h>

#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/resource.h>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <mnetlib/Registry.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mnetlib/Learner.h>
#include <mnetlib/LearnerAdapter.h>
#include <iostream>
#include <string>

using namespace Mnetlib;
using namespace std;
using std::cout;
using namespace xercesc;

int main(){

  try{
      LearnerAdapter aAdapter;
      LearnerSPtr aLearner =aAdapter.getLearner("test/data/TestLearner_Learner.xml");
      aLearner->trainNet();
  }
  catch (exception* e)
  {
      cout << e->what()<<"\n";
      return -1;
  }
  catch (std::exception& e)
  {
      cout << "Unexpected Exception during test \n" ;
      cout<< e.what();
      return -1;
  }
  catch (const XMLException& toCatch)
  {
      char* message = XMLString::transcode(toCatch.getMessage());
      cout << "Exception message is: \n"
          << message << "\n";
      XMLString::release(&message);
      return -1;
  }
  catch (const DOMException& toCatch)
  {
      char* message = XMLString::transcode(toCatch.msg);
      cout << "Exception message is: \n"
          << message << "\n";
      XMLString::release(&message);
      return -1;
  }
  return(0);
}


