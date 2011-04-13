import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("Merge")

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.load('Configuration.StandardSequences.Services_cff')

process.load('VHbb.iCode.ZH_channel_signal_cfi')

# process.source = cms.Source("PoolSource",
# #   fileNames = cms.untracked.vstring(*[x.strip() for x in open("files_full.txt")])
#    fileNames = cms.untracked.vstring(
# )
# )

process.out = cms.OutputModule("PoolOutputModule",
   fileName = cms.untracked.string("/scratch/bortigno/ZH_channel_signal.root"),
   outputCommands = cms.untracked.vstring('keep *','drop *_MEtoEDMConverter_*_*')
)

process.endPath = cms.EndPath(process.out)

