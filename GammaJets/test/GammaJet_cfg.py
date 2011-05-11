import FWCore.ParameterSet.Config as cms

process = cms.Process("GammaJet")

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
process.load('Configuration/EventContent/EventContent_cff')

#MC 3_8_X: MC_38Y_V14, START38_V14, DESIGN_38_V14
#process.GlobalTag.globaltag = cms.string('START38_V12::All')
#DATA 3_8_X: GR_R_38X_V15
#process.GlobalTag.globaltag = cms.string('GR_R_38X_V14::All')
process.GlobalTag.globaltag = cms.string('START311_V1G1::All')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
    )

#from PhysicsTools.PatAlgos.patTemplate_cfg import *

process.source = cms.Source("PoolSource",
                            #run number event number
                            #c e anche lumi to process che alposto di run number prende lumi number
#                            eventsToProcess = cms.untracked.VEventRange('1:90520'),
                            fileNames = cms.untracked.vstring(

#MC
#'file:///shome/bortigno/CMSSW_4_1_3_patch3/src/GammaJets/iCode/test/24A622BB-8950-E011-8D0C-00304867BFC6.root'
#NovReReco
#'file:///shome/bortigno/test/CMSSW_3_8_7_patch2/src/VHbb/iCode/test/3CF39F96-B2EC-DF11-B5DC-0025B3E01FC2.root'
#PromptReco
#'file:///shome/bortigno/CMSSW_3_8_7_patch2/src/VHbb/iCode/test/2E89DE77-4DE6-DF11-920B-0030487CD17C.root'

#    'file:////shome/bortigno/CMSSW_3_8_7_patch2/src/VHbb/iCode/test/MultiJet_test/res/MultiJet_selectedEvents_6_1_u5M.root'
#    '/store/mc/Fall10/WH_WToLNu_HToBB_M-120_7TeV-powheg-herwigpp/AODSIM//START38_V12-v1//0001//DA959ED3-07E9-DF11-8B82-00215E2216A4.root',
#    '/store/mc/Fall10/ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp/AODSIM/START38_V12-v1/0002/F06CDFED-B0E8-DF11-ADB2-003048C6B52A.root',


    )
                            )


#from PhysicsTools.PatAlgos.tools.trigTools import *
### RBX noise filter
#process.load('CommonTools/RecoAlgos/HBHENoiseFilter_cfi')
#switchOnTrigger( process )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('reducedPAT.root'),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('filter') ),
                               outputCommands = cms.untracked.vstring('drop *' )
                               )

# process.out = cms.OutputModule("PoolOutputModule",
#                                fileName = cms.untracked.string('patTuple.root'),
#                                # save only events passing the full path
#                                SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
#                                # save PAT Layer 1 output; you need a '*' to
#                                # unpack the list of commands 'patEventContent'
#                                outputCommands = cms.untracked.vstring('drop *', *patEventContent ) 
#                                )

process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.jetTools import *
from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
## remove MC matching from the default sequence
removeMCMatching(process, ['All'])
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

addJetCollection(process,
                 cms.InputTag('ak7PFJets'),
                 'AK7','PF',
                 doJTA=True,
                 doBTagging=True,
#                 jetCorrLabel=('AK7','PF'),
                 # DATA:
#                 jetCorrLabel=('AK7PF', 'L3Absolute'),
                 jetCorrLabel=('AK7PF', ['L2Relative','L3Absolute']),
                 doType1MET=False,
                 doL1Cleaning=False,
                 doL1Counters=False,
                 genJetCollection=cms.InputTag('ak7GenJets'),
                 doJetID=True
                 )


switchJetCollection(process,cms.InputTag('ak5PFJets'),
                    doJTA        = True,
                    doBTagging   = True,
                    #MonteCarlo:  jetCorrLabel = ('AK5', 'PF'),
                    # DATA:
#                    jetCorrLabel = ('AK5PF','L3Absolute'),
                    jetCorrLabel = ('AK5PF',['L2Relative','L3Absolute']),
                    doType1MET   = True,
                    genJetCollection=cms.InputTag("ak5GenJets"),
                    doJetID      = True
                    )

# https://twiki.cern.ch/twiki/bin/view/CMS/TriggerResultsFilter
# triggerSelection = cms.EDFilter( "TriggerResultsFilter",
#                                  triggerConditions = cms.vstring(
#     'HLT_Photon40_Isol_Cleaned_L1R_v1 / 1' ),
#                                  hltResults = cms.InputTag( "TriggerResults", "", "HLT" ),
#                                  l1tResults = cms.InputTag( "gtDigis" ),
#                                  l1tIgnoreMask = cms.bool( False ),
#                                  l1techIgnorePrescales = cms.bool( False ),
#                                  daqPartitions = cms.uint32( 1 ),
#                                  throw = cms.bool( True )
#                                  )


process.GammaJet = cms.EDAnalyzer("GammaJet",
                                  jetPtThreshold          = cms.untracked.double(20),
                                  photon_ptCut            = cms.untracked.double(20),
                                  PG_deltaPhiCut          = cms.untracked.double(2.75),
                                  #edm collection
                                  patPhotons              = cms.untracked.InputTag("cleanPatPhotons"),
                                  muonCand                = cms.untracked.InputTag("cleanPatMuons"),
                                  akt5pfJets              = cms.untracked.InputTag("ak5PFJets"),
#                                   pfMetCand              = cms.untracked.InputTag("pfMet"),
                                  patJets                 = cms.untracked.InputTag("cleanPatJets"),
                                  ak7patJets              = cms.untracked.InputTag("selectedPatJetsAK7PF"),
                                  hltPath                 = cms.InputTag("TriggerResults","","REDIGI311X"),
                                  pfJetIDSelector = cms.PSet(
    version = cms.string('FIRSTDATA'),
    quality = cms.string('LOOSE')
    )                                   
                                   )

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
    )

process.TFileService = cms.Service("TFileService", fileName = cms.string('GammaJetHLT.root'))
# process.ak5PFJetsL2L3 *
process.p = cms.Path( process.patDefaultSequence * process.GammaJet )

