import FWCore.ParameterSet.Config as cms

process = cms.Process("GenLooper")

# process.load('Configuration.StandardSequences.Services_cff')
# process.load('FWCore.MessageService.MessageLogger_cfi')
# process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
# process.load('Configuration.StandardSequences.GeometryDB_cff')
# process.load('Configuration.StandardSequences.MagneticField_38T_cff')
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


#process.GlobalTag.globaltag = 'START38_V12::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )


process.source = cms.Source("PoolSource",

                             fileNames = cms.untracked.vstring(
'file:/data2/bortigno/CMSSW_3_8_5/src/36CE2C04-45E0-DF11-AD80-001A648F131A.root'

    )
                            )


process.GenLooper = cms.EDAnalyzer("GenLooper",
                                        genPart     = cms.untracked.InputTag("genParticles"),
                                        )

process.TFileService = cms.Service("TFileService", fileName = cms.string('GenLooper.root'))

process.p = cms.Path(process.GenLooper)


