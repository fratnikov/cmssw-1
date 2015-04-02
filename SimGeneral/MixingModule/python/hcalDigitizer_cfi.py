import FWCore.ParameterSet.Config as cms

from SimCalorimetry.HcalSimProducers.hcalUnsuppressedDigis_cfi import hcalSimBlock

hcalDigitizer = cms.PSet(
    hcalSimBlock,
    accumulatorType = cms.string("HcalDigiProducer"),
    makeDigiSimLinks = cms.untracked.bool(False))

#hcalDigiMixer = cms.PSet(
#    accumulatorType = cms.string("HcalDigiMixerHBHE"),
#    src = cms.InputTag("simHcalDigis"),
#    makeDigiSimLinks = cms.untracked.bool(False))

