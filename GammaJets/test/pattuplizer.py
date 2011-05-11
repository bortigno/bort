import FWCore.ParameterSet.Config as cms

#### V8
### using bcandproducer v1.3
### filtering at minVertices = 0


process = cms.Process("PAT")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.MessageLogger.cerr.threshold = "ERROR"

process.MessageLogger.cerr.limit =  cms.untracked.uint32(10)
process.MessageLogger.cout.limit =  cms.untracked.uint32(10)


#process.MessageLogger.suppressDebug = ["patTrigger"]
process.MessageLogger.suppressWarning = ['PATTriggerProducer:patTrigger','PATTriggerProducer','patTrigger','muonTriggerMatchHLTJets']
#process.MessageLogger.suppressError = ['PATTriggerProducer:patTrigger','HLTConfigData']


process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration/EventContent/EventContent_cff')

from Configuration.PyReleaseValidation.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )
#process.GlobalTag.globaltag = 'GR_P_V16::All'

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
    '/store/data/Run2011A/MuOnia/AOD/PromptReco-v1/000/161/312/EC4F121D-E257-E011-A167-0030487A18D8.root',
    '/store/data/Run2011A/MuOnia/AOD/PromptReco-v1/000/161/312/E89CCBE0-E957-E011-A53B-0019B9F709A4.root'
    
    )) 


## Standard PAT Configuration File
process.load("PhysicsTools.PatAlgos.patSequences_cff")
#from PhysicsTools.PatAlgos.tools.trigTools import *
### RBX noise filter
process.load('CommonTools/RecoAlgos/HBHENoiseFilter_cfi')


## Output Module Configuration (expects a path 'p')
#from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('reducedPAT.root'),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('filter') ),
                               outputCommands = cms.untracked.vstring('drop *' )
                               )

from PhysicsTools.PatAlgos.tools.coreTools import *
## remove MC matching from the default sequence
removeMCMatching(process, ['All'])

#from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
#from PhysicsTools.PatAlgos.tools.trigTools import *
#switchOnTrigger( process )

from PhysicsTools.PatAlgos.tools.metTools import *
addPfMET(process, 'PF')

from PhysicsTools.PatAlgos.tools.jetTools import *
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
process.ak5PFL1Fastjet.useCondDB = False
switchJetCollection(process,cms.InputTag('ak5PFJets'),
                    doJTA        = True,
                    doBTagging   = True,
                    jetCorrLabel = ('AK5PF', cms.vstring(['L1FastJet','L2Relative', 'L3Absolute','L2L3Residual'])),
                    doType1MET   = True,
                    #genJetCollection=cms.InputTag("ak5GenJets"),
                    doJetID      = True
                    )
process.selectedPatJets.cut = cms.string("pt>8.")
process.patJets.embedPFCandidates = cms.bool(True)
process.selectedPatJets.embedPFCandidates = cms.bool(True)

removeMCMatching(process, ['All'])

### PAT Muons
process.patMuons.embedTrack = True

###Trigger Matching
#process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )
#process.load("Pattuplizer.TriggerMatch.triggermatch_PF_cfi")
from PhysicsTools.PatAlgos.tools.coreTools import removeCleaning
removeCleaning( process )
## Switch on PAT trigger
#from PhysicsTools.PatAlgos.tools.trigTools import *
#process.muonTriggerMatchHLTJets = cms.EDProducer(
    # matching in DeltaR, sorting by best DeltaR
#    "PATTriggerMatcherDRLessByR"
    # matcher input collections
#    , src     = cms.InputTag( 'selectedPatJets' )
#    , matched = cms.InputTag( 'patTrigger' )
    # selections of trigger objects
#    , matchedCuts = cms.string( 'type( "TriggerJet" ) && ( path( "HLT_Jet*" )  )' )
    # selection of matches
#    , maxDPtRel   = cms.double( 0.5 ) # no effect here
#    , maxDeltaR   = cms.double( 0.5 )
#    , maxDeltaEta = cms.double( 0.2 ) # no effect here
    # definition of matcher output
#    , resolveAmbiguities    = cms.bool( True )
#    , resolveByMatchQuality = cms.bool( True )
#    )
#from PhysicsTools.PatAlgos.tools.trigTools import *
#switchOnTriggerMatching( process, triggerMatchers = [ 'muonTriggerMatchHLTJets' ], outputModule = '' )
# Switch to selected PAT objects in the trigger matching
#removeCleaningFromTriggerMatching( process, outputModule = '' )


### Event Filter
process.goodPFJets = cms.EDFilter("PtMinCandViewSelector",
                                  src = cms.InputTag("selectedPatJets"),
                                  ptMin = cms.double(30)
                                  )

process.EventPFJetFilter = cms.EDFilter("CandViewCountFilter",
                                        src = cms.InputTag("goodPFJets"),
                                        minNumber = cms.uint32(1),
                                        filter = cms.bool(True)   # otherwise it won't filter the events, just produce an empty vertex collection.
                            )
process.trackFilter = cms.EDFilter("TrackSelector",
                                   filter = cms.bool(False),
                                   src = cms.InputTag("generalTracks"),
                                   cut = cms.string("pt > 1.0")
                                 )


###Sec vertex
process.load('RecoVertex/AdaptiveVertexFinder/inclusiveVertexing_cff')
process.inclusiveMergedVertices = process.vertexMerger.clone()
process.inclusiveMergedVertices.secondaryVertices = cms.InputTag("inclusiveVertices")
process.inclusiveMergedVertices.maxFraction = 0.2
process.inclusiveMergedVertices.minSignificance = 10.

process.load("RecoBTag/SecondaryVertex/bVertexFilter_cfi")
process.selectedVertices = process.bVertexFilter.clone()
process.selectedVertices.secondaryVertices = cms.InputTag("inclusiveMergedVertices")
process.selectedVertices.minVertices = 0
process.selectedVertices.vertexFilter.multiplicityMin = 3

process.inclusiveVertexFinder.clusterScale = 1.
process.inclusiveVertexFinder.clusterMinAngleCosine = 0.5

process.bcandidates = cms.EDProducer('BCandidateProducer',
                                     src = cms.InputTag('selectedVertices','',''),
                                     primaryVertices =
                                     cms.InputTag('offlinePrimaryVerticesWithBS'),#,'',''),
                                     minDRUnique = cms.untracked.double(0.4),
                                     minvecSumIMifsmallDRUnique = cms.untracked.double(5.5),
                                     minCosPAtomerge = cms.untracked.double(0.99),
                                     maxPtreltomerge = cms.untracked.double(7777.0)
                                     )

####### Data cleaning
# require physics declared
#process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
#process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'

# require scraping filter
process.scrapingVeto = cms.EDFilter("FilterOutScraping",
                                    applyfilter = cms.untracked.bool(True),
                                    debugOn = cms.untracked.bool(False),
                                    numtrack = cms.untracked.uint32(10),
                                    thresh = cms.untracked.double(0.25)
                                    )

#process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
#from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import hltLevel1GTSeed
#Good Bunch Crossings
#process.bptxAnd = hltLevel1GTSeed.clone(L1TechTriggerSeeding = cms.bool(True), L1SeedsLogicalExpression = cms.string('0'))
#BSCNOBEAMHALO
#process.bit40 = hltLevel1GTSeed.clone(L1TechTriggerSeeding = cms.bool(True), L1SeedsLogicalExpression = cms.string('(40 OR 41) AND NOT (36 OR 37 OR 38 OR 39) AND NOT ((42 AND NOT 43) OR (43 AND NOT 42))'))


#Require a good vertex
process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
                                           src = cms.InputTag("offlinePrimaryVertices"),
                                           cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"),
                                           filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
                                           )

process.dump=cms.EDAnalyzer('EventContentAnalyzer')
### rerunning btag (for 35X samples)
#process.load("RecoBTag.SecondaryVertex.simpleSecondaryVertex3TrkES_cfi")
#process.load("RecoBTag.SecondaryVertex.simpleSecondaryVertexHighPurBJetTags_cfi")
#process.load("RecoBTag.SecondaryVertex.simpleSecondaryVertexHighEffBJetTags_cfi")

##-------------------- Import the Jet RECO modules -----------------------
process.load('RecoJets.Configuration.RecoPFJets_cff')
##-------------------- Turn-on the FastJet density calculation -----------------------
process.kt6PFJets.doRhoFastjet = True
##-------------------- Turn-on the FastJet jet area calculation for your favorite algorithm -----------------------
process.ak5PFJets.doAreaFastjet = True
process.kt6PFJets.Rho_EtaMax = cms.double(4.4)
process.fjSequence = cms.Sequence(process.kt6PFJets)
process.patJetCorrFactors.rho = cms.InputTag('kt6PFJets','rho')



process.filter = cms.Path(
    ##process.dump*
    ##    process.hltLevel1GTSeed *
    #process.bit40 *
    #process.bptxAnd *
    process.scrapingVeto *
    ##    process.hltPhysicsDeclared *
    process.oneGoodVertexFilter*
    process.HBHENoiseFilter*
    #process.simpleSecondaryVertexHighPurBJetTags*
    #process.simpleSecondaryVertexHighEffBJetTags*
    process.fjSequence *
    process.patDefaultSequence*
    #process.goodPFJets*
    #process.EventPFJetFilter*
    #process.trackFilter*
#    process.muonTriggerMatchHLTJets
    process.inclusiveVertexing
    *process.inclusiveMergedVertices*process.selectedVertices*process.bcandidates
    
    )

#process.schedule = cms.Schedule(process.filter, process.sv, process.pat)
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('reducedPAT.root'),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('filter') ),
                               outputCommands = cms.untracked.vstring('drop *',
                                                                      'keep *_selectedPatPhotons*_*_*',
                                                                      'keep *_selectedPatElectrons*_*_*',
                                                                      'keep *_selectedPatMuons*_*_*',
                                                                      'keep *_selectedPatTaus*_*_*',
                                                                      'keep *_selectedPatJets*_*_*',
                                                                      'drop *_selectedPatJets_pfCandidates_*', ## drop for default patJets which are CaloJets
                                                                      'drop *_*PF_caloTowers_*',
                                                                      'drop *_*JPT_pfCandidates_*',
                                                                      'drop *_*Calo_pfCandidates_*',
                                                                      'keep *_patMETs*_*_*',
                                                                      'keep *_selectedPatPFParticles*_*_*',
                                                                      'keep *_selectedPatTrackCands*_*_*',
                                                                      "keep *_impactParameterTagInfos*_*_*",
                                                                      "keep *_secondaryVertexTagInfos_*_*",
                                                                      # GEN
                                                                      'keep recoGenParticles_genParticles*_*_*',
                                                                      'keep GenEventInfoProduct_*_*_*',
                                                                      'keep GenRunInfoProduct_*_*_*',
                                                                      # RECO
                                                                      'keep recoTracks_generalTracks*_*_*',
                                                                      #'keep *_towerMaker_*_*',
                                                                      'keep *_offlineBeamSpot_*_*',
                                                                      'keep *_offlinePrimaryVertices*_*_*',
                                                                      # TRIGGER
                                                                      'keep *_TriggerResults*_*_*',
                                                                      'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
                                                                      'keep *_hltTriggerSummaryAOD_*_*',
                                                                      'keep patTriggerAlgorithms_patTrigger_*_*',
                                                                      'keep patTriggerObjects_patTrigger_*_*',
                                                                      'keep patTriggerFilters_patTrigger_*_*',
                                                                      'keep patTriggerPaths_patTrigger_*_*',
                                                                      'keep patTriggerEvent_patTriggerEvent_*_*',
                                                                      'keep patTriggerObjectStandAlones_patTrigger_*_*',
                                                                      'keep *_patTrigger*_*_*',
                                                                      'keep patTrigger*_patTrigger_*_*',
                                                                      'keep patTriggerObjectStandAlonesedmAssociation_*_*_*',
                                                                      'keep *_*TriggerMatch_*_*',
                                                                      #SV
                                                                      'keep *_bcandidates_*_*',
                                                                      'keep *_selectedVertices*_*_*'
                                                                      )
                               )

process.outpath = cms.EndPath(process.out)

