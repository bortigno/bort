import FWCore.ParameterSet.Config as cms

process = cms.Process("WHchannel")

# process.load('Configuration.StandardSequences.Services_cff')
# process.load('FWCore.MessageService.MessageLogger_cfi')
# process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
# process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
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
process.load('RecoVertex/AdaptiveVertexFinder/inclusiveVertexing_cff')
process.load('RecoBTag/SecondaryVertex/secondaryVertexTagInfos_cfi')
## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START38_V12::All')


#process.GlobalTag.globaltag = 'START38_V12::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )

#input from cfi
#process.load('VHbb.iCode.WH_channel_background_herwig_cfi)
process.load('VHbb.iCode.WH_channel_background_cfi')
#process.load('VHbb.iCode.WH_channel_signal_cfi')


## Standard PAT Configuration File
process.load("PhysicsTools.PatAlgos.patSequences_cff")
# from PhysicsTools.PatAlgos.tools.trigTools import *
# from PhysicsTools.PatAlgos.tools.coreTools import *
# remove MC matching from the default sequence
# removeMCMatching(process, ['All'])
# from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
# from PhysicsTools.PatAlgos.tools.trigTools import *
# switchOnTrigger( process )
# removeSpecificPATObjects(process, ['Electrons', 'Muons', 'Taus'])

#from PhysicsTools.PatAlgos.patTemplate_cfg import *
from PhysicsTools.PatAlgos.tools.jetTools import *
from PhysicsTools.PatAlgos.tools.metTools import *

addPfMET(process, 'PF')

process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

switchJetCollection(process,cms.InputTag('ak5PFJets'),
                    doJTA        = True,
                    doBTagging   = True,
                    jetCorrLabel = ('AK5', 'PF'),
                    doType1MET   = True,
                    genJetCollection=cms.InputTag("ak5GenJets"),
                    doJetID      = True
                    )

# process.selectedPatJets.cut = cms.string("pt>8.")
# process.patJets.embedPFCandidates = cms.bool(True)
# process.selectedPatJets.embedPFCandidates = cms.bool(True)

# W selection
process.load("ElectroWeakAnalysis.WMuNu.WMuNuSelection_cff")

process.WHchannel = cms.EDAnalyzer("WH_channel",
                                   muonJetCleaningDRcut_  = cms.untracked.double(0.5),
                                   JetBassociationDRCut   = cms.untracked.double(0.5),
                                   hMassLowerCut          = cms.untracked.double(80),
                                   hMassHigherCut          = cms.untracked.double(140),
                                   genPart     = cms.untracked.InputTag("genParticles"),
                                   muonCand       = cms.untracked.InputTag("muons"),
                                   WMuNuCand      = cms.untracked.InputTag("pfMetWMuNus"),
#                                   akt5pfJets  = cms.untracked.InputTag("ak5PFJets"),
#                                   pfMetCand   = cms.untracked.InputTag("pfMet"),
                                   selectedPatJetsCand  = cms.untracked.InputTag("selectedPatJets"),
                                   patMetsCand  = cms.untracked.InputTag("patMETs"),
                                   pfJetIDSelector = cms.PSet(
    version = cms.string('FIRSTDATA'),
    quality = cms.string('LOOSE')
    )
                                  
                                   )

process.TFileService = cms.Service("TFileService", fileName = cms.string('WH_channel_background.root'))

process.p = cms.Path( process.selectPfMetWMuNus
                      * process.patDefaultSequence
                      * process.WHchannel)


