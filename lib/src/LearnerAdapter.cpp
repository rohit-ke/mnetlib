/*
 * LearnerAdapter.cpp
 *
 *  Created on: 13/nov/2011
 *      Author: totoro
 */

#define DEBUG
#include <LearnerAdapter.h>
#include <CommonMacro.h>
#include <CommonXMLNetConstant.h>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/SAXParseException.hpp>

using namespace xercesc;

namespace Mnetlib
{
  LearnerAdapter::LearnerAdapter()
  {
    _nodeDecoderMap.insert(std::make_pair(kLearnerNodeName, &LearnerAdapter::decodeLearnerNode));
    _nodeDecoderMap.insert(std::make_pair(kNetNodeName, &LearnerAdapter::decodeNetNode));
    _nodeDecoderMap.insert(std::make_pair(kPatternKey, &LearnerAdapter::decodePatternNode));
  }

  LearnerSPtr LearnerAdapter::getLearner(const std::string& path)
  {
    //Open file
    INFO_MSG( "getNewNet from xml file");
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n"
            << message << "\n";
        XMLString::release(&message);
        return _learner;
    }

    //Parse
    XercesDOMParser* parser = new XercesDOMParser();

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    try {
        parser->parse(path.c_str());
    }
    CATCH_XML(_learner);

    std::string aNodeValue, aNetType,aLayerType;
    DOMDocument* pDoc=parser->getDocument();
    DOMNode* pCurrent = NULL;
    DOMElement* pRoot=pDoc->getDocumentElement();

    // create an iterator to visit all text nodes.
    DOMNodeIterator* iterator=pDoc->createNodeIterator(pRoot,
        DOMNodeFilter::SHOW_ALL, NULL, true);

    //Create Learner
    pCurrent = iterator->nextNode();
    while (pCurrent!=NULL)
      {
        decode_map::const_iterator aNodeDecoderIt = _nodeDecoderMap.find(pCurrent->getNodeName());
        if(aNodeDecoderIt!=_nodeDecoderMap.end())
          {
            (this->*(aNodeDecoderIt->second))(pCurrent);
          }
        pCurrent = iterator->nextNode();
      }
    delete parser;
    delete errHandler;
    return _learner;
  }

  void LearnerAdapter::decodeLearnerNode(xercesc::DOMNode* ioNode)
  {
    try{
    DEBUG_MSG( "decodelearner");
    DEBUG_MSG( XMLString::transcode(ioNode->getNodeName()));
    DEBUG_MSG( "Found Learner Node");
    DOMElement* aLearnerNode = dynamic_cast<DOMElement*>(ioNode);
    const XMLCh* fNodeAttribute = aLearnerNode->getAttribute(kLearningRateKey);
    std::string aLearningRate=XMLString::transcode(fNodeAttribute);
    DEBUG_MSG( "Learning rate: " << aLearningRate );
    fNodeAttribute = aLearnerNode->getAttribute(kMomentumKey);
    std::string aMomentum=XMLString::transcode(fNodeAttribute);
    DEBUG_MSG( "Momentum: " << aMomentum);
    fNodeAttribute = aLearnerNode->getAttribute(kTrainigCyclesKey);
    std::string aTrainigCycles=XMLString::transcode(fNodeAttribute);
    DEBUG_MSG( "Trainig Cycles: " << aTrainigCycles);
    _learner=LearnerSPtr(new Learner());
    _learner->set_parameter(atof(aLearningRate.c_str()),atof(aMomentum.c_str()),atoi(aTrainigCycles.c_str()));
    }catch (std::exception* e) { cout<< "Error occurred while decoding learner node.\n" << e->what()<<"\n"; }
  }

  void LearnerAdapter::decodeNetNode(xercesc::DOMNode* ioNode)
  {
    try{
    DEBUG_MSG( "decodeNet");
    DEBUG_MSG( XMLString::transcode(ioNode->getNodeName()));
    DEBUG_MSG( "Found Net Node");
    DOMElement* aNetNode = dynamic_cast<DOMElement*>(ioNode);
    const XMLCh* fNodeAttribute = aNetNode->getAttribute(kPathKey);
    std::string aNetPath=XMLString::transcode(fNodeAttribute);
    DEBUG_MSG( "Net path: " << aNetPath );
    Registry reg;
    NetSPtr net=reg.getNewNet(aNetPath);
    _learner->setNet(net);
    }catch (std::exception* e) { cout<< "Error occurred while decoding net node.\n" << e->what()<<"\n"; }
  }

  void LearnerAdapter::decodePatternNode(xercesc::DOMNode* ioNode)
    {
    try{
        DEBUG_MSG( "decodePattern");

    DEBUG_MSG( XMLString::transcode(ioNode->getNodeName()));
    DEBUG_MSG( "Found Pattern Node");
    DOMElement* aPatternNode = dynamic_cast<DOMElement*>(ioNode);
    const XMLCh* fNodeAttribute = aPatternNode->getAttribute(kPathKey);
    std::string aPatternPath=XMLString::transcode(fNodeAttribute);
    DEBUG_MSG( "Pattern path: " << aPatternPath );
    fNodeAttribute = aPatternNode->getAttribute(kTypeKey);
    std::string aPatternType=XMLString::transcode(fNodeAttribute);
    DEBUG_MSG( "Pattern type: " << aPatternType );
    //TODO Type as enum, build function as template
    if(aPatternType=="train")
      {
        _learner->buildTrainPattern(aPatternPath);
      }
    else if (aPatternType=="test")
      {
        _learner->buildTestPattern(aPatternPath);
      }
    else
      {
        ERROR_MSG("Pattern type not supported");
      }
    }catch (std::exception* e) { cout<< "Error occurred while decoding pattern node.\n" << e->what()<<"\n"; }
    }
}
