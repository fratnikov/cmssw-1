#ifndef SimCalorimetry_EcalSimProducers_EcalPhaseIIDigiProducer_h
#define SimCalorimetry_EcalSimProducers_EcalPhaseIIDigiProducer_h

#include "SimCalorimetry/EcalSimAlgos/interface/APDShape.h"
#include "SimCalorimetry/EcalSimAlgos/interface/EBShape.h"
#include "SimCalorimetry/EcalSimAlgos/interface/EEShape.h"
#include "SimCalorimetry/EcalSimAlgos/interface/EKShape.h"
#include "SimCalorimetry/EcalSimAlgos/interface/ESShape.h"
#include "DataFormats/Math/interface/Error.h"
#include "SimGeneral/NoiseGenerators/interface/CorrelatedNoisifier.h"
#include "SimCalorimetry/EcalSimAlgos/interface/EcalCorrelatedNoiseMatrix.h"
#include "SimCalorimetry/EcalSimAlgos/interface/ESElectronicsSim.h"

#include "SimCalorimetry/CaloSimAlgos/interface/CaloTDigitizer.h"
#include "SimCalorimetry/EcalSimAlgos/interface/EcalTDigitizer.h"
#include "SimCalorimetry/EcalSimAlgos/interface/EcalDigitizerTraits.h"
#include "SimGeneral/MixingModule/interface/DigiAccumulatorMixMod.h"

/** \todo 
 - Set the ES optional
*/


#include <vector>

typedef EcalTDigitizer<EBDigitizerTraits> EBDigitizer  ;
typedef EcalTDigitizer<EEDigitizerTraits> EEDigitizer  ;
typedef EcalTDigitizer<EKDigitizerTraits> EKDigitizer  ;
typedef CaloTDigitizer<ESOldDigitizerTraits> ESOldDigitizer  ;


class ESDigitizer ;

class APDSimParameters ;
class EBHitResponse ;
class EEHitResponse ;
class EKHitResponse ;
class ESHitResponse ;
class CaloHitResponse ;
class EcalSimParameterMap ;
class EcalCoder ;
class EcalElectronicsSim ;
class ESElectronicsSim ;
class ESElectronicsSimFast ;
class CaloGeometry ;
class EBDigiCollection ;
class EEDigiCollection ;
class EKDigiCollection ;
class ESDigiCollection ;
class PileUpEventPrincipal ;

namespace edm {
  class EDProducer;
  class Event;
  class EventSetup;
  template<typename T> class Handle;
  class ParameterSet;
}

class EcalPhaseIIDigiProducer : public DigiAccumulatorMixMod {
   public:

      EcalPhaseIIDigiProducer( const edm::ParameterSet& params , edm::EDProducer& mixMod);
      virtual ~EcalPhaseIIDigiProducer();

      virtual void initializeEvent(edm::Event const& e, edm::EventSetup const& c);
      virtual void accumulate(edm::Event const& e, edm::EventSetup const& c);
      virtual void accumulate(PileUpEventPrincipal const& e, edm::EventSetup const& c);
      virtual void finalizeEvent(edm::Event& e, edm::EventSetup const& c);

   private:

      virtual void cacheEBDigis( const EBDigiCollection* ebDigiPtr ) const { }
      virtual void cacheEEDigis( const EEDigiCollection* eeDigiPtr ) const { }
      virtual void cacheEKDigis( const EKDigiCollection* ekDigiPtr ) const { }

      typedef edm::Handle<std::vector<PCaloHit> > HitsHandle;
      void accumulateCaloHits(HitsHandle const& ebHandle,  HitsHandle const& eeHandle, HitsHandle const& ekHandle, HitsHandle const& esHandle,  int bunchCrossing);

      void checkGeometry(const edm::EventSetup& eventSetup) ;

      void updateGeometry() ;

      void checkCalibrations(const edm::Event& event, const edm::EventSetup& eventSetup) ;

      const APDShape m_APDShape ;
      const EBShape  m_EBShape  ;
      const EEShape  m_EEShape  ;
      const EKShape  m_EKShape  ;
      ESShape        m_ESShape  ; // no const because gain must be set

      const std::string m_EBdigiCollection ;
      const std::string m_EEdigiCollection ;
      const std::string m_EKdigiCollection ;
      const std::string m_ESdigiCollection ;
      const std::string m_hitsProducerTag  ;

      const std::string m_EBhitsProducerTag;
      const std::string m_EEhitsProducerTag;
      const std::string m_EKhitsProducerTag;
      const std::string m_EShitsProducerTag;

      bool  m_useLCcorrection;

      const bool m_apdSeparateDigi ;

      const double m_EBs25notCont ;
      const double m_EEs25notCont ;
      const double m_EKs25notCont ;

      const unsigned int         m_readoutFrameSize ;
   protected:
      const EcalSimParameterMap* m_ParameterMap  ;
   private:
      const std::string          m_apdDigiTag    ;
      const APDSimParameters*    m_apdParameters ;

      EBHitResponse* m_APDResponse ;
   protected:
      EBHitResponse* m_EBResponse ;
      EEHitResponse* m_EEResponse ;
      EKHitResponse* m_EKResponse ;
   private:
      ESHitResponse* m_ESResponse ;
      CaloHitResponse* m_ESOldResponse ;

      const bool m_addESNoise ;

      const bool m_doFastES   ;

      ESElectronicsSim*     m_ESElectronicsSim     ;
      ESOldDigitizer*       m_ESOldDigitizer       ;
      ESElectronicsSimFast* m_ESElectronicsSimFast ;
      ESDigitizer*          m_ESDigitizer          ;

      EBDigitizer*          m_APDDigitizer ;
      EBDigitizer*          m_BarrelDigitizer ;
      EEDigitizer*          m_EndcapDigitizer ;
      EKDigitizer*          m_ShashlikDigitizer ;

      EcalElectronicsSim*   m_ElectronicsSim ;
      EcalCoder*            m_Coder ;

      EcalElectronicsSim*   m_APDElectronicsSim ;
      EcalCoder*            m_APDCoder ;

      const CaloGeometry*   m_Geometry ;

      CorrelatedNoisifier<EcalCorrMatrix>* m_EBCorrNoise[3] ;
      CorrelatedNoisifier<EcalCorrMatrix>* m_EECorrNoise[3] ;
      CorrelatedNoisifier<EcalCorrMatrix>* m_EKCorrNoise[3] ;

      //Shervin temporary to remove detIds not conform to the geometry
      std::set<DetId>* theEKDets;
};

#endif 
