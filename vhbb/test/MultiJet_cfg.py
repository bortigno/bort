import FWCore.ParameterSet.Config as cms

process = cms.Process("MultiJet")

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
#process.GlobalTag.globaltag = cms.string('START38_V12::All')
process.GlobalTag.globaltag = cms.string('GR_R_38X_V14::All')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )

process.source = cms.Source("PoolSource",
                            #run number event number
                            #c e anche lumi to process che alposto di run number prende lumi number
#                            eventsToProcess = cms.untracked.VEventRange('1:90520'),
                            fileNames = cms.untracked.vstring(

'file:////shome/bortigno/CMSSW_3_8_6/src/VHbb/iCode/test/MultiJet_test/res/MultiJet_selectedEvents_6_1_u5M.root'
#    '/store/mc/Fall10/WH_WToLNu_HToBB_M-120_7TeV-powheg-herwigpp/AODSIM//START38_V12-v1//0001//DA959ED3-07E9-DF11-8B82-00215E2216A4.root',
#    '/store/mc/Fall10/ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp/AODSIM/START38_V12-v1/0002/F06CDFED-B0E8-DF11-ADB2-003048C6B52A.root',


    )
                            )

process.load("PhysicsTools.PatAlgos.patSequences_cff")
#from PhysicsTools.PatAlgos.patTemplate_cfg import *
from PhysicsTools.PatAlgos.tools.jetTools import *

from PhysicsTools.PatAlgos.tools.coreTools import *
## remove MC matching from the default sequence
removeMCMatching(process, ['All'])

switchJetCollection(process,cms.InputTag('ak5PFJets'),
                    doJTA        = True,
                    doBTagging   = True,
                    jetCorrLabel = ('AK5', 'PF'),
                    doType1MET   = True,
                    genJetCollection=cms.InputTag("ak5GenJets"),
                    doJetID      = True
                    )

process.MultiJet = cms.EDAnalyzer("MultiJet",
                                   muonJetCleaningPtcut   = cms.untracked.double(0.1),
                                   minBTagging             = cms.untracked.double(0.44),
                                   maxBTagging             = cms.untracked.double(0.9),
                                   muonCand                = cms.untracked.InputTag("selectedPatMuons"),
                                   akt5pfJets              = cms.untracked.InputTag("ak5PFJets"),
#                                   pfMetCand              = cms.untracked.InputTag("pfMet"),
                                   patJets                 = cms.untracked.InputTag("selectedPatJets"),
                                   pfJetIDSelector = cms.PSet(
    version = cms.string('FIRSTDATA'),
    quality = cms.string('LOOSE')
    )                                   
                                   )

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
    )

process.TFileService = cms.Service("TFileService", fileName = cms.string('MultiJet.root'))

process.p = cms.Path( process.MultiJet )

