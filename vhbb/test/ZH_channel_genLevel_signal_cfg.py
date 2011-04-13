import FWCore.ParameterSet.Config as cms

process = cms.Process("ZHchannelGenLevel")

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
    input = cms.untracked.int32(859)
    )


#input from cfi
#process.load('VHbb.iCode.ZH_channel_background_herwig_cfi')
#process.load('VHbb.iCode.ZH_channel_background_cfi')
process.load('VHbb.iCode.ZH_channel_signal_cfi')

process.source = cms.Source("PoolSource",
                            #run number event number
                            #c e anche lumi to process che alposto di run number prende lumi number
                            #                            eventsToProcess = cms.untracked.VEventRange('1:90520'),
                            fileNames = cms.untracked.vstring(
    #merged file v0
#    '/store/user/bortigno/ZH_channel/ZH_channel_signal/selectedEvents/merge-selected_signal_ZH.root'

    #merged file v1
#    'file:////scratch/bortigno/ZH_channel_v1_signal.root'
#    '/store/user/bortigno/ZH_channel_v1/ZH_channel_signal/selectedEvents/ZH_channel_signal.root'

    )
                            )


process.load("PhysicsTools.PatAlgos.patSequences_cff")
#from PhysicsTools.PatAlgos.patTemplate_cfg import *
from PhysicsTools.PatAlgos.tools.jetTools import *

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



process.ZHchannelGenLevel = cms.EDAnalyzer("ZH_channel_genLevel",
                                   jetDeltaRcut           = cms.untracked.double(1000),
                                   muonJetCleaningDRcut_  = cms.untracked.double(0.5),
                                   JetBassociationDRCut   = cms.untracked.double(0.5),
                                   hMassLowerCut          = cms.untracked.double(100),
                                   hMassHigherCut         = cms.untracked.double(140),
                                   jetPtAsymmetryHigherCut = cms.untracked.double(1),
                                   genPart                = cms.untracked.InputTag("genParticles"),
                                   muonCand               = cms.untracked.InputTag("muons"),
                                   akt5pfJets             = cms.untracked.InputTag("ak5PFJets"),
#                                   pfMetCand              = cms.untracked.InputTag("pfMet"),
                                   selectedPatJets_genJets = cms.untracked.InputTag("ak5GenJets"),
                                   pfJetIDSelector = cms.PSet(
    version = cms.string('FIRSTDATA'),
    quality = cms.string('LOOSE')
    )                                   
                                   )

process.TFileService = cms.Service("TFileService", fileName = cms.string('ZH_channel_genLevel_signal_middleMasses.root'))

process.p = cms.Path( process.patDefaultSequence
                      * process.impactParameterTagInfos
                      * process.secondaryVertexTagInfos
                      * process.simpleSecondaryVertexHighPurBJetTags
                      * process.ZHchannelGenLevel )
