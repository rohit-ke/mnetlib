/**
 *  Registry.cpp
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
#define DEBUG

#include "Registry.h"
#include "Synapse.h"
#include "CommonXMLNetConstant.h"
#include "CommonMacro.h"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <boost/shared_ptr.hpp>



using namespace xercesc;

namespace Mnetlib
{
  Registry::Registry()
  {
    registerNeuronFactory(&linearFactory);
    registerNeuronFactory(&sigmoidFactory);
    registerNeuronFactory(&logarithmicFactory);
    registerNeuronFactory(&tanhFactory);
    registerLayerFactory(&inputFactory);
    registerLayerFactory(&hiddenFactory);
    registerLayerFactory(&outputFactory);
    registerSynapseFactory(&insinFactory);
    registerSynapseFactory(&hiddensinFactory);
    registerSynapseFactory(&outsinFactory);
    registerNetFactory(&ffonlineFactory);
    _nodeDecoderMap.insert(std::make_pair(kNetNodeName, &Registry::decodeNetNode));
    _nodeDecoderMap.insert(std::make_pair(kLayerNodeName, &Registry::decodeLayerNode));
    _nodeDecoderMap.insert(std::make_pair(kInputLayerNodeName, &Registry::decodeInputLayerNode));
    _nodeDecoderMap.insert(std::make_pair(kOutputLayerNodeName, &Registry::decodeOutputLayerNode));
    _nodeDecoderMap.insert(std::make_pair(kSynapseNodeName, &Registry::decodeSynapseNode));
    _nodeDecoderMap.insert(std::make_pair(kInputSynapseNodeName, &Registry::decodeInputSynapseNode));
    _nodeDecoderMap.insert(std::make_pair(kOutputSynapseNodeName, &Registry::decodeOutputSynapseNode));
  }

  Registry::~Registry()
  {

  }

  NeuronSPtr Registry::getNewNeuron(const std::string& name)
  {
    NeuronSPtr oNeuronSPtr;
    if ( _neuronRegistry[name] )
      {
        oNeuronSPtr= NeuronSPtr(_neuronRegistry[name]->create());
      }

    return oNeuronSPtr;
  }

  LayerSPtr Registry::getNewLayer (const std::string& lName, const std::string& nName , const int n)
  {
    LayerSPtr oLayerSPtr;
    if ( _layerRegistry[lName] )
      {
        oLayerSPtr= LayerSPtr(_layerRegistry[lName]->create(n));
        if ( _neuronRegistry[nName] )
          {
            vector<NeuronSPtr> v;
            for (int s = 0; s < n; ++s)
              {
                v.push_back(getNewNeuron(nName));
              }
            oLayerSPtr->setVector(v);
          }
        else
          {
              throw new Mnetlib::InstantiationException("Wrong layer type");
          }
      }
    return oLayerSPtr;
  }

  SynapseSPtr Registry::getNewSynapse(const std::string& name, const int n, const int l)
  {
    SynapseSPtr oSynapseSPtr;
    if (_synapseRegistry[name]) {
        oSynapseSPtr = SynapseSPtr(_synapseRegistry[name]->create(n,l));
    }
    return oSynapseSPtr;
  }

  NetSPtr Registry::getNewNet(const std::string& name,const int ni, const int nh, const int no)
  {
    NetSPtr net;

    if ( _netRegistry[name] )
      {
        net=_netRegistry[name]->create();
        vector<SynapseSPtr> vs;
        vector<LayerSPtr> vl;
        SynapseSPtr s1=getNewSynapse("inputSynapse",ni,1);
        SynapseSPtr s2=getNewSynapse("hiddenSynapse",nh,ni);
        LayerSPtr l=getNewLayer("inputLayer","linear",ni);
        l->connectLayer(s1,s2);
        vl.push_back(l);
        vs.push_back(s1);
        s1=getNewSynapse("hiddenSynapse",no,nh);
        l=getNewLayer("hiddenLayer","linear",nh);
        l->connectLayer(s2,s1);
        vl.push_back(l);
        vs.push_back(s2);
        s2=getNewSynapse("outputSynapse",no,1);
        l=getNewLayer("outputLayer","linear",no);
        l->connectLayer(s1,s2);
        vl.push_back(l);
        vs.push_back(s1);
        vs.push_back(s2);
        net->setLayer(vl);
        net->setSynapse(vs);

      }

    return net;
  }

  void Registry::decodeNetNode(DOMNode* ioNode)
  {
    DEBUG_MSG( "decodenet");
    DEBUG_MSG( XMLString::transcode(ioNode->getNodeName()));
    DEBUG_MSG( "Found Net Node");
    DOMElement* aNetNode = dynamic_cast<DOMElement*>(ioNode);
    const XMLCh* fNodeType = aNetNode->getAttribute(kNetTypeKey);
    std::string aNetType=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Net type: " << aNetType );
    if ( _netRegistry[aNetType] )
      {
        DEBUG_MSG( "valid net type");
        _net=_netRegistry[aNetType]->create();
      }
  }

  void Registry::decodeLayerNode(DOMNode* ioNode)
  {
    DEBUG_MSG( "decodelayer");
    DEBUG_MSG( XMLString::transcode(ioNode->getNodeName()));
    DEBUG_MSG( "Found Layer Node");
    DOMElement* aLayerNode = dynamic_cast<DOMElement*>(ioNode);
    const XMLCh* fNodeType = aLayerNode->getAttribute(kLayerTypeKey);
    std::string aLayerType=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Layer type: " << aLayerType );
    fNodeType = aLayerNode->getAttribute(kLayerNeuronNumKey);
    std::string aLayerNeruon=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Layer neuron: " << aLayerNeruon );
    fNodeType = aLayerNode->getAttribute(kLayerIndKey);
    std::string aLayerInd=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Layer ind: " << aLayerInd );
    LayerSPtr aLayer=getNewLayer("hiddenLayer",aLayerType,atoi(aLayerNeruon.c_str()));
    _net->pushLayer(aLayer);
    //_net->setLayer();
  }

  void Registry::decodeInputLayerNode(DOMNode* ioNode)
  {
    DEBUG_MSG( "decodeinputlayer");
    DEBUG_MSG( XMLString::transcode(ioNode->getNodeName()));
    DEBUG_MSG( "decodelayer");
    DEBUG_MSG( XMLString::transcode(ioNode->getNodeName()));
    DEBUG_MSG( "Found Layer Node");
    DOMElement* aLayerNode = dynamic_cast<DOMElement*>(ioNode);
    const XMLCh* fNodeType = aLayerNode->getAttribute(kLayerTypeKey);
    std::string aLayerType=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Layer type: " << aLayerType);
    fNodeType = aLayerNode->getAttribute(kLayerNeuronNumKey);
    std::string aLayerNeruon=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Layer neuron: " << aLayerNeruon );
    fNodeType = aLayerNode->getAttribute(kLayerIndKey);
    std::string aLayerInd=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Layer ind: " << aLayerInd );
    LayerSPtr aLayer=getNewLayer("inputLayer",aLayerType,atoi(aLayerNeruon.c_str()));
    _net->pushLayer(aLayer);
  }

  void Registry::decodeOutputLayerNode(DOMNode* ioNode)
  {
    DEBUG_MSG( "decodeoutputlayer");
    DEBUG_MSG( XMLString::transcode(ioNode->getNodeName()));
    DEBUG_MSG( "Found Layer Node");
    DOMElement* aLayerNode = dynamic_cast<DOMElement*>(ioNode);
    const XMLCh* fNodeType = aLayerNode->getAttribute(kLayerTypeKey);
    std::string aLayerType=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Layer type: " << aLayerType );
    fNodeType = aLayerNode->getAttribute(kLayerNeuronNumKey);
    std::string aLayerNeruon=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Layer neuron: " << aLayerNeruon );
    fNodeType = aLayerNode->getAttribute(kLayerIndKey);
    std::string aLayerInd=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Layer ind: " << aLayerInd );
    LayerSPtr aLayer=getNewLayer("outputLayer",aLayerType,atoi(aLayerNeruon.c_str()));
    _net->pushLayer(aLayer);
  }

  void Registry::decodeSynapseNode(DOMNode* ioNode)
  {
    DEBUG_MSG( "decodeSynapseNode");
    DEBUG_MSG( XMLString::transcode(ioNode->getNodeName()));
    DOMElement* aSynapseNode = dynamic_cast<DOMElement*>(ioNode);
    const XMLCh* fNodeType = aSynapseNode->getAttribute(kLayerInLineKey);
    std::string aSynapseInLine=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Layer type: " << aSynapseInLine );
    fNodeType = aSynapseNode->getAttribute(kLayerOutLineKey);
    std::string aSynapseOutLine=XMLString::transcode(fNodeType);
    DEBUG_MSG( "Layer neuron: " << aSynapseOutLine );
    SynapseSPtr aSynapse=getNewSynapse("hiddenSynapse",atoi(aSynapseInLine.c_str()),atoi(aSynapseOutLine.c_str()));
    _net->pushSynapse(aSynapse);
  }

  void Registry::decodeInputSynapseNode(DOMNode* ioNode)
    {
      DEBUG_MSG( "decodeInputSynapseNode");
      DEBUG_MSG( XMLString::transcode(ioNode->getNodeName()));
      DOMElement* aSynapseNode = dynamic_cast<DOMElement*>(ioNode);
      const XMLCh* fNodeType = aSynapseNode->getAttribute(kLayerInLineKey);
      std::string aSynapseInLine=XMLString::transcode(fNodeType);
      DEBUG_MSG( "Synapse in: " << aSynapseInLine );
      fNodeType = aSynapseNode->getAttribute(kLayerOutLineKey);
      std::string aSynapseOutLine=XMLString::transcode(fNodeType);
      DEBUG_MSG( "Synapse out: " << aSynapseOutLine );
      SynapseSPtr aSynapse=getNewSynapse("inputSynapse",atoi(aSynapseInLine.c_str()),atoi(aSynapseOutLine.c_str()));
      _net->pushSynapse(aSynapse);
    }

  void Registry::decodeOutputSynapseNode(DOMNode* ioNode)
    {
      DEBUG_MSG( "decodeOutputSynapseNode");
      DEBUG_MSG( XMLString::transcode(ioNode->getNodeName()));
      DOMElement* aSynapseNode = dynamic_cast<DOMElement*>(ioNode);
      const XMLCh* fNodeType = aSynapseNode->getAttribute(kLayerInLineKey);
      std::string aSynapseInLine=XMLString::transcode(fNodeType);
      DEBUG_MSG( "Synapse in: " << aSynapseInLine);
      fNodeType = aSynapseNode->getAttribute(kLayerOutLineKey);
      std::string aSynapseOutLine=XMLString::transcode(fNodeType);
      DEBUG_MSG( "Synapse out: " << aSynapseOutLine);
      SynapseSPtr aSynapse=getNewSynapse("outputSynapse",atoi(aSynapseInLine.c_str()),atoi(aSynapseOutLine.c_str()));
      _net->pushSynapse(aSynapse);
    }

  NetSPtr Registry::getNewNet(const std::string& path)
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
        return NetSPtr();
    }

    //Parse
    XercesDOMParser* parser = new XercesDOMParser();

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    try {
        parser->parse(path.c_str());
    }
    CATCH_XML(NetSPtr());


    std::string aNodeValue, aNetType,aLayerType;
    DOMDocument* pDoc=parser->getDocument();
    DOMNode* pCurrent = NULL;
    DOMElement* pRoot=pDoc->getDocumentElement();

    // create an iterator to visit all text nodes.
    DOMNodeIterator* iterator=pDoc->createNodeIterator(pRoot,
        DOMNodeFilter::SHOW_ALL, NULL, true);

    //Create net
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
    //Connect Layer and Synapse
    _net->connect();
    DEBUG_MSG( "dumping net content");
    DEBUG_MSG(_net->toString());
    delete parser;
    delete errHandler;
    return _net;

  }
}
