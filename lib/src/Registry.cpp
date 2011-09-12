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


#include "Registry.h"
#include "Synapse.h"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/SAXParseException.hpp>

using namespace xercesc;

namespace Mnetlib
{
  Registry::Registry()
  {
    registerNeuronFactory(&linearFactory);
    registerNeuronFactory(&sigmoidFactory);
    registerLayerFactory(&inputFactory);
    registerLayerFactory(&hiddenFactory);
    registerLayerFactory(&outputFactory);
    registerSynapseFactory(&insinFactory);
    registerSynapseFactory(&hiddensinFactory);
    registerSynapseFactory(&outsinFactory);
    registerNetFactory(&ffonlineFactory);
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

  Net* Registry::getNewNet(const std::string& name,const int ni, const int nh, const int no)
  {
    if ( _netRegistry[name] )
      {
        Net* net=_netRegistry[name]->create();
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
        return net;
      }

    return 0;
  }

  Net* Registry::getNewNet(const std::string& path)
  {
    //Open file

    //Parse

    //Create net
    cout << "getNewNet from xml file \n";
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n"
            << message << "\n";
        XMLString::release(&message);
        return 0;
    }

    XercesDOMParser* parser = new XercesDOMParser();
    //parser->setValidationScheme(XercesDOMParser::Val_Always);
    //parser->setDoNamespaces(true);    // optional

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    try {
        parser->parse(path.c_str());
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
    catch (const SAXParseException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n"
            << message << "\n";
        XMLString::release(&message);
        return 0;
    }
    catch (std::exception e) {
        cout << "Unexpected Exception \n" ;
        cout << e.what();
        return 0;
    }

    //static const XMLCh* kNetTypeKey;
    //XMLString::transcode("NetType",kNetTypeKey,99);
    static   const XMLCh kNetNodeName[] =
        {
            chLatin_N,
            chLatin_e,
            chLatin_t,
            chNull
        };

    static   const XMLCh kLayerNodeName[] =
        {
            chLatin_L,
            chLatin_a,
            chLatin_y,
            chLatin_e,
            chLatin_r,
            chNull
        };

    static   const XMLCh kNetTypeKey[] =
        {
            chLatin_n,
            chLatin_e,
            chLatin_t,
            chLatin_T,
            chLatin_y,
            chLatin_p,
            chLatin_e,
            chNull
        };

    static const XMLCh kLayerIndKey[] =
        {
            chLatin_i,
            chLatin_n,
            chLatin_d,
            chNull
        };
    static const XMLCh kLayerTypeKey[] =
        {
            chLatin_t,
            chLatin_y,
            chLatin_p,
            chLatin_e,
            chNull
        };

    static const XMLCh kLayerInLineKey[] =
        {
            chLatin_i,
            chLatin_n,
            chLatin_L,
            chLatin_i,
            chLatin_n,
            chLatin_e,
            chNull
        };

    static const XMLCh kLayerOutLineKey[] =
        {
            chLatin_o,
            chLatin_u,
            chLatin_t,
            chLatin_L,
            chLatin_i,
            chLatin_n,
            chLatin_e,
            chNull
        };

        std::string aNodeValue, aNetType,aLayerType;

    DOMDocument* pDoc = parser->getDocument();
    DOMNode* pCurrent = NULL;
    DOMElement *pRoot = pDoc->getDocumentElement();


    // create an iterator to visit all text nodes.
    DOMNodeIterator* iterator = pDoc->createNodeIterator(pRoot,
        DOMNodeFilter::SHOW_ALL, NULL, true);

    pCurrent = iterator->nextNode();
    if(XMLString::equals(pCurrent->getNodeName(),kNetNodeName))
      {
        cout << "Found Net Node\n";
        int ni,nh,no;
        ni=no=nh=2;
        DOMElement* aNetNode = dynamic_cast<DOMElement*>(pCurrent);
        const XMLCh* fNodeType = aNetNode->getAttribute(kNetTypeKey);
        aNetType=XMLString::transcode(fNodeType);
        cout << "Net type: " << aNetType << "\n";
        if ( _netRegistry[aNetType] )
          {
            cout << "valid net type\n";
            Net* net=_netRegistry[aNetType]->create();
            vector<SynapseSPtr> vs;
            vector<LayerSPtr> vl;
            for ( pCurrent = iterator->nextNode(); pCurrent != 0; pCurrent = iterator->nextNode() )
              {
                cout << "Actual node name: " << XMLString::transcode(pCurrent->getNodeName()) <<"\n";
                int aInLine, aOutLine;
                string aTmpString;
                SynapseSPtr s1,s2;
                LayerSPtr l1,l2;
                if(XMLString::equals(pCurrent->getNodeName(),kLayerNodeName))
                  {
                    DOMElement* aLayerNode = dynamic_cast<DOMElement*>(pCurrent);
                    cout << "Found Layer Node\n";
                    fNodeType = aLayerNode->getAttribute(kLayerTypeKey);
                    aLayerType=XMLString::transcode(fNodeType);
                    cout << "attribute :" << aLayerType << "\n";
                    fNodeType = aLayerNode->getAttribute(kLayerInLineKey);
                    aTmpString =XMLString::transcode(fNodeType);
                    cout << "attribute :" << aTmpString << "\n";
                    aInLine=atoi(aTmpString.c_str());
                    fNodeType = aLayerNode->getAttribute(kLayerOutLineKey);
                    aTmpString =XMLString::transcode(fNodeType);
                    cout << "attribute :" << aTmpString << "\n";
                    aOutLine=atoi(aTmpString.c_str());
                    cout << "Layer properties: \n";
                    cout << "Layer type: " << aLayerType <<"\n";
                    cout << "Input line: " << aInLine << "\n";
                    cout << "Output line: " << aOutLine << "\n";

                    if(vl.size()==0)
                      {
                        s1=getNewSynapse("inputSynapse",aOutLine,aInLine);
                        l1=getNewLayer("inputLayer",aLayerType,aOutLine);
                        vl.push_back(l1);
                        vs.push_back(s1);
                      }
                    else
                      {
                        l1=vl.back();
                        s1=vs.back();
                        s2=getNewSynapse("hiddenSynapse",aOutLine,aInLine);
                        l2=getNewLayer("hiddenLayer",aLayerType,aOutLine);
                        l1->connectLayer(s1,s2);
                        vl.push_back(l2);
                        vs.push_back(s2);
                      }

                    s2=getNewSynapse("outputSynapse",no,1);
                    /*SynapseSPtr s1=getNewSynapse("inputSynapse",ni,1);
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

                    l=getNewLayer("outputLayer","linear",no);
                    l->connectLayer(s1,s2);
                    vl.push_back(l);
                    vs.push_back(s1);
                    vs.push_back(s2);*/
                  }

              }
            net->setLayer(vl);
            net->setSynapse(vs);
            cout << "dumping net content\n";
            cout<< net->toString();
            cout<< "\n";
            return net;
          }
        else
          {
            throw InstantiationException();
          }
      }
    delete parser;
    delete errHandler;
    return 0;

  }
}
