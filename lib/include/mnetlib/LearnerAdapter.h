/*
 * LearnerAdapter.h
 *
 *  Created on: 13/nov/2011
 *      Author: totoro
 */

#ifndef LEARNERADAPTER_H_
#define LEARNERADAPTER_H_

#include "Learner.h"
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/util/XMLString.hpp>
#include <map>

namespace Mnetlib
{
  class LearnerAdapter {
  public:
    LearnerAdapter();
    virtual ~LearnerAdapter(){};
    LearnerSPtr getLearner(const std::string& path);

  private:



    void decodeLearnerNode(xercesc::DOMNode* ioNode);
    void decodeNetNode(xercesc::DOMNode* ioNode);
    void decodePatternNode(xercesc::DOMNode* ioNode);

    struct CompareXMLNodeName
    {
      bool operator()(const XMLCh* a,const XMLCh* b) const
      { return xercesc::XMLString::compareString(a,b)<0; };
    };

    typedef void (LearnerAdapter::*decodeFunction)(xercesc::DOMNode *); // function pointer type
    typedef std::map<const XMLCh*, decodeFunction, CompareXMLNodeName> decode_map;

    decode_map _nodeDecoderMap;
    LearnerSPtr _learner;
  };
}


#endif /* LEARNERADAPTER_H_ */
