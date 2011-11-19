/*
 * CommonXMLNetConstant.h
 *
 *  Created on: 12/set/2011
 *      Author: totoro
 */

#ifndef COMMONXMLNETCONSTANT_H_
#define COMMONXMLNETCONSTANT_H_

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>


namespace Mnetlib
{
  const   XMLCh kNetNodeName[] =
      {
          xercesc::chLatin_N,
          xercesc::chLatin_e,
          xercesc::chLatin_t,
          xercesc::chNull
      };

  const XMLCh kLayerNodeName[] =
      {
          xercesc::chLatin_L,
          xercesc::chLatin_a,
          xercesc::chLatin_y,
          xercesc::chLatin_e,
          xercesc::chLatin_r,
          xercesc::chNull
      };

  const XMLCh kInputLayerNodeName[] =
      {
          xercesc::chLatin_I,
          xercesc::chLatin_n,
          xercesc::chLatin_p,
          xercesc::chLatin_u,
          xercesc::chLatin_t,
          xercesc::chLatin_L,
          xercesc::chLatin_a,
          xercesc::chLatin_y,
          xercesc::chLatin_e,
          xercesc::chLatin_r,
          xercesc::chNull
      };

  const XMLCh kOutputLayerNodeName[] =
      {
          xercesc::chLatin_O,
          xercesc::chLatin_u,
          xercesc::chLatin_t,
          xercesc::chLatin_p,
          xercesc::chLatin_u,
          xercesc::chLatin_t,
          xercesc::chLatin_L,
          xercesc::chLatin_a,
          xercesc::chLatin_y,
          xercesc::chLatin_e,
          xercesc::chLatin_r,
          xercesc::chNull
      };

  const XMLCh kSynapseNodeName[] =
      {
          xercesc::chLatin_S,
          xercesc::chLatin_y,
          xercesc::chLatin_n,
          xercesc::chLatin_a,
          xercesc::chLatin_p,
          xercesc::chLatin_s,
          xercesc::chLatin_e,
          xercesc::chNull
      };

  const XMLCh kInputSynapseNodeName[] =
      {
          xercesc::chLatin_I,
          xercesc::chLatin_n,
          xercesc::chLatin_p,
          xercesc::chLatin_u,
          xercesc::chLatin_t,
          xercesc::chLatin_S,
          xercesc::chLatin_y,
          xercesc::chLatin_n,
          xercesc::chLatin_a,
          xercesc::chLatin_p,
          xercesc::chLatin_s,
          xercesc::chLatin_e,
          xercesc::chNull
      };
  const XMLCh kOutputSynapseNodeName[] =
      {
          xercesc::chLatin_O,
          xercesc::chLatin_u,
          xercesc::chLatin_t,
          xercesc::chLatin_p,
          xercesc::chLatin_u,
          xercesc::chLatin_t,
          xercesc::chLatin_S,
          xercesc::chLatin_y,
          xercesc::chLatin_n,
          xercesc::chLatin_a,
          xercesc::chLatin_p,
          xercesc::chLatin_s,
          xercesc::chLatin_e,
          xercesc::chNull
      };

  static   const XMLCh kNetTypeKey[] =
      {
          xercesc::chLatin_n,
          xercesc::chLatin_e,
          xercesc::chLatin_t,
          xercesc::chLatin_T,
          xercesc::chLatin_y,
          xercesc::chLatin_p,
          xercesc::chLatin_e,
          xercesc::chNull
      };

  static const XMLCh kLayerIndKey[] =
      {
          xercesc::chLatin_i,
          xercesc::chLatin_n,
          xercesc::chLatin_d,
          xercesc::chNull
      };
  static const XMLCh kLayerTypeKey[] =
      {
          xercesc::chLatin_t,
          xercesc::chLatin_y,
          xercesc::chLatin_p,
          xercesc::chLatin_e,
          xercesc::chNull
      };

  static const XMLCh kLayerInLineKey[] =
      {
          xercesc::chLatin_i,
          xercesc::chLatin_n,
          xercesc::chLatin_L,
          xercesc::chLatin_i,
          xercesc::chLatin_n,
          xercesc::chLatin_e,
          xercesc::chNull
      };

  static const XMLCh kLayerOutLineKey[] =
      {
          xercesc::chLatin_o,
          xercesc::chLatin_u,
          xercesc::chLatin_t,
          xercesc::chLatin_L,
          xercesc::chLatin_i,
          xercesc::chLatin_n,
          xercesc::chLatin_e,
          xercesc::chNull
      };

  static const XMLCh kLayerNeuronNumKey[] =
        {
            xercesc::chLatin_n,
            xercesc::chLatin_e,
            xercesc::chLatin_u,
            xercesc::chLatin_r,
            xercesc::chLatin_o,
            xercesc::chLatin_n,
            xercesc::chLatin_N,
            xercesc::chLatin_u,
            xercesc::chLatin_m,
            xercesc::chNull
        };

  const XMLCh kLearnerNodeName[] =
        {
            xercesc::chLatin_L,
            xercesc::chLatin_e,
            xercesc::chLatin_a,
            xercesc::chLatin_r,
            xercesc::chLatin_n,
            xercesc::chLatin_e,
            xercesc::chLatin_r,
            xercesc::chNull
        };

  static const XMLCh kPatternKey[] =
          {
              xercesc::chLatin_P,
              xercesc::chLatin_a,
              xercesc::chLatin_t,
              xercesc::chLatin_t,
              xercesc::chLatin_e,
              xercesc::chLatin_r,
              xercesc::chLatin_n,
              xercesc::chNull
          };

  static const XMLCh kTypeKey[] =
        {
            xercesc::chLatin_t,
            xercesc::chLatin_y,
            xercesc::chLatin_p,
            xercesc::chLatin_e,
            xercesc::chNull
        };

  static const XMLCh kPathKey[] =
          {
              xercesc::chLatin_p,
              xercesc::chLatin_a,
              xercesc::chLatin_t,
              xercesc::chLatin_h,
              xercesc::chNull
          };

  static const XMLCh kMomentumKey[] =
        {
            xercesc::chLatin_m,
            xercesc::chLatin_o,
            xercesc::chLatin_m,
            xercesc::chLatin_e,
            xercesc::chLatin_n,
            xercesc::chLatin_t,
            xercesc::chLatin_u,
            xercesc::chLatin_m,
            xercesc::chNull
        };

  static const XMLCh kLearningRateKey[] =
          {
              xercesc::chLatin_l,
              xercesc::chLatin_e,
              xercesc::chLatin_a,
              xercesc::chLatin_r,
              xercesc::chLatin_n,
              xercesc::chLatin_i,
              xercesc::chLatin_n,
              xercesc::chLatin_g,
              xercesc::chLatin_R,
              xercesc::chLatin_a,
              xercesc::chLatin_t,
              xercesc::chLatin_e,
              xercesc::chNull
          };

  static const XMLCh kTrainigCyclesKey[] =
          {
              xercesc::chLatin_t,
              xercesc::chLatin_r,
              xercesc::chLatin_a,
              xercesc::chLatin_i,
              xercesc::chLatin_n,
              xercesc::chLatin_i,
              xercesc::chLatin_n,
              xercesc::chLatin_g,
              xercesc::chLatin_C,
              xercesc::chLatin_y,
              xercesc::chLatin_c,
              xercesc::chLatin_l,
              xercesc::chLatin_e,
              xercesc::chLatin_s,
              xercesc::chNull
          };

}
#endif /* COMMONXMLNETCONSTANT_H_ */
