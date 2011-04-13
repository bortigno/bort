import FWCore.ParameterSet.Config as cms

process = cms.Process("ZHchannel")

# process.load('Configuration.StandardSequences.Services_cff')
# process.load('FWCore.MessageService.MessageLogger_cfi')
# process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
# process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
#questi due per i tagger
process.load('RecoBTag.Configuration.RecoBTag_cff')
process.load('Validation.RecoB.bTagAnalysis_cfi')
# process.load('Configuration.StandardSequences.Generator_cff')
# process.load('Configuration.StandardSequences.VtxSmearedRealistic7TeVCollision_cff')
# process.load('Configuration.StandardSequences.SimIdeal_cff')
# process.load('Configuration.StandardSequences.Digi_cff')
# process.load('Configuration.StandardSequences.SimL1Emulator_cff')
# process.load('Configuration.StandardSequences.DigiToRaw_cff')
# process.load('HLTrigger.Configuration.HLT_GRun_cff')
# process.load('Configuration.StandardSequences.EndOfProcess_cff')
# process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
# process.load('Configuration.EventContent.EventContent_cff')
# process.load("RecoBTag/SecondaryVertex/bVertexFilter_cfi")
process.load('RecoVertex/AdaptiveVertexFinder/inclusiveVertexing_cff')
process.load('RecoBTag/SecondaryVertex/secondaryVertexTagInfos_cfi')
## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START38_V12::All')


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )


#input from cfi
#process.load('VHbb.iCode.ZH_channel_background_herwig_cfi')
#process.load('VHbb.iCode.ZH_channel_background_cfi')
#process.load('VHbb.iCode.ZH_channel_signal_cfi')
process.load('VHbb.iCode.ZH_channel_ZH_v7_cfi')

# process.source = cms.Source("PoolSource",
#                             #run number event number
#                             #c e anche lumi to process che alposto di run number prende lumi number
#                             #                            eventsToProcess = cms.untracked.VEventRange('1:90520'),
#                             fileNames = cms.untracked.vstring(
#     #merged file v0
# #    '/store/user/bortigno/ZH_channel/ZH_channel_signal/selectedEvents/merge-selected_signal_ZH.root'

#     #merged file v1
# #    'file:////scratch/bortigno/ZH_channel_v1_signal.root'
# #    '/store/user/bortigno/ZH_channel_v1/ZH_channel_signal/selectedEvents/ZH_channel_signal.root'

#     #merged file v2
# #    'file:////scratch/bortigno/ZH_channel_v2_ZH.root'

#     #merged file v5
# #    'file:////scratch/bortigno/ZMuMu_channel_v5_ZH.root'

#     #merged file v6
#     'file:////scratch/bortigno/ZMuMu_channel_v6_ZH.root'


#     )
#                             )


process.load("PhysicsTools.PatAlgos.patSequences_cff")
#from PhysicsTools.PatAlgos.patTemplate_cfg import *
from PhysicsTools.PatAlgos.tools.jetTools import *

addJetCollection(process,
                 cms.InputTag('ak7PFJets'),
                 'AK7','PF',
                 doJTA=True,
                 doBTagging=True,
                 jetCorrLabel=('AK7',
                               'PF'),
                 # DATA:       cms.vstring(['L2Relative', 'L3Absolute','L2L3Residual'])),
                 doType1MET=False,
                 doL1Cleaning=False,
                 doL1Counters=False,
                 genJetCollection=cms.InputTag('ak7GenJets'),
                 doJetID=True
                 )

switchJetCollection(process,cms.InputTag('ak5PFJets'),
                    doJTA        = True,
                    doBTagging   = True,
                    jetCorrLabel = ('AK5', 'PF'),
                    doType1MET   = True,
                    genJetCollection=cms.InputTag("ak5GenJets"),
                    doJetID      = True
                    )


# goodJets   = selectedPatJets.clone(
#     src = 'cleanPatJetsAK5PF',
#     cut = 'abs(eta) < 3 & pt > 10.          &'
#     'chargedHadronEnergyFraction > 0.0  &'
#     'neutralHadronEnergyFraction/corrFactor("raw") < 0.99 &'
#     'chargedEmEnergyFraction/corrFactor("raw")     < 0.99 &'
#     'neutralEmEnergyFraction/corrFactor("raw")     < 0.99 &'
#     'chargedMultiplicity > 0            &'
#     'nConstituents > 0'
#     )

## Analyze jets
#from CMS.PhysicsTools.PatExamples.PatJetAnalyzer_cfi import analyzePatJets
#process.Uncorrected = analyzePatJets.clone(src = 'goodJets', corrLevel='raw')
#process.L2Relative  = analyzePatJets.clone(src = 'goodJets', corrLevel='rel')
#process.L3Absolute  = analyzePatJets.clone(src = 'goodJets', corrLevel='abs')



process.ZHchannel = cms.EDAnalyzer("ZH_channel",
                                   jetDeltaRcut           = cms.untracked.double(1000),
                                   muonJetCleaningDRcut  = cms.untracked.double(0.5),
                                   JetBassociationDRCut   = cms.untracked.double(0.5),
                                   hMassLowerCut          = cms.untracked.double(0),
                                   hMassHigherCut         = cms.untracked.double(500),
                                   jetPtAsymmetryHigherCut = cms.untracked.double(1),
                                   ZCandidatePtCut        = cms.untracked.double(120),
                                   HCandidatePtCut        = cms.untracked.double(115),
                                   ZH_deltaPhiCut         = cms.untracked.double(2.75),
                                   maxBTagging            = cms.untracked.double(0.8),
                                   minBTagging            = cms.untracked.double(0.6),
                                   helicityCut            = cms.untracked.double(1),
                                   genPart                = cms.untracked.InputTag("genParticles"),
                                   ak5GenJets             = cms.untracked.InputTag("ak5GenJets"),
                                   muonCand               = cms.untracked.InputTag("muons"),
#                                   electronCand           = cms.untracked.InputTag("selectedElectrons"),
#                                   akt5pfJets             = cms.untracked.InputTag("ak5PFJets"),
#                                   pfMetCand              = cms.untracked.InputTag("pfMet"),
                                   patJets                = cms.untracked.InputTag("selectedPatJets"),
                                   ak7patJets                = cms.untracked.InputTag("selectedPatJetsAK7PF"),
                                   pfJetIDSelector = cms.PSet(
    version = cms.string('FIRSTDATA'),
    quality = cms.string('LOOSE')
    )                                   
                                   )

process.TFileService = cms.Service("TFileService", fileName = cms.string('ZH_channel_v7/ZH_channel_ZH/ZMuMu_channel_v17_ZH.root'))

process.p = cms.Path( process.patDefaultSequence
#                       * process.impactParameterTagInfos
#                       * process.secondaryVertexTagInfos
#                       * process.simpleSecondaryVertexHighPurBJetTags
                      * process.ZHchannel )
