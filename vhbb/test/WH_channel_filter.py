import FWCore.ParameterSet.Config as cms

process = cms.Process("WHchannelFilter")

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
    input = cms.untracked.int32(10)
    )


# process.source.fileNames = []
# mf = open("file.list")
# for i in mf:
#          i = i.strip("\n")
#               process.source.fileNames.append(i)


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    #'file:////data2/bortigno/ZvvJets_GEN_FASTSIM_HLT_7TeV.root'
    #'file:////data2/bortigno/CMSSW_3_8_5/src/MyAnalysis/Analysis/test/WH_GEN_FASTSIM_HLT_PU.root'
#     'file:////shome/bortigno/CMSSW_3_8_6/src/MG4/7TeV/WJets/pt100/WJets_GEN_FASTSIM_PU_7TeV_preprod/res/WJets_GEN_FASTSIM_HLT_PU_7TeV_10_1_dfX.root',
#     'file:////shome/bortigno/CMSSW_3_8_6/src/MG4/7TeV/WJets/pt100/WJets_GEN_FASTSIM_PU_7TeV_preprod/res/WJets_GEN_FASTSIM_HLT_PU_7TeV_1_1_PQ0.root',
#     'file:////shome/bortigno/CMSSW_3_8_6/src/MG4/7TeV/WJets/pt100/WJets_GEN_FASTSIM_PU_7TeV_preprod/res/WJets_GEN_FASTSIM_HLT_PU_7TeV_2_1_UIb.root',
#     'file:////shome/bortigno/CMSSW_3_8_6/src/MG4/7TeV/WJets/pt100/WJets_GEN_FASTSIM_PU_7TeV_preprod/res/WJets_GEN_FASTSIM_HLT_PU_7TeV_3_1_9JY.root',
#     'file:////shome/bortigno/CMSSW_3_8_6/src/MG4/7TeV/WJets/pt100/WJets_GEN_FASTSIM_PU_7TeV_preprod/res/WJets_GEN_FASTSIM_HLT_PU_7TeV_4_1_Typ.root',
#     'file:////shome/bortigno/CMSSW_3_8_6/src/MG4/7TeV/WJets/pt100/WJets_GEN_FASTSIM_PU_7TeV_preprod/res/WJets_GEN_FASTSIM_HLT_PU_7TeV_5_1_d7m.root',
#     'file:////shome/bortigno/CMSSW_3_8_6/src/MG4/7TeV/WJets/pt100/WJets_GEN_FASTSIM_PU_7TeV_preprod/res/WJets_GEN_FASTSIM_HLT_PU_7TeV_6_1_Z5i.root',
#     'file:////shome/bortigno/CMSSW_3_8_6/src/MG4/7TeV/WJets/pt100/WJets_GEN_FASTSIM_PU_7TeV_preprod/res/WJets_GEN_FASTSIM_HLT_PU_7TeV_7_1_X08.root',
#     'file:////shome/bortigno/CMSSW_3_8_6/src/MG4/7TeV/WJets/pt100/WJets_GEN_FASTSIM_PU_7TeV_preprod/res/WJets_GEN_FASTSIM_HLT_PU_7TeV_8_1_R87.root',
#     'file:////shome/bortigno/CMSSW_3_8_6/src/MG4/7TeV/WJets/pt100/WJets_GEN_FASTSIM_PU_7TeV_preprod/res/WJets_GEN_FASTSIM_HLT_PU_7TeV_9_1_qeb.root'

    '/store/mc/Fall10/WH_WToLNu_HToBB_M-120_7TeV-powheg-herwigpp/AODSIM//START38_V12-v1//0001//DA959ED3-07E9-DF11-8B82-00215E2216A4.root'

    #WJets
    
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_24_1_e4F.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_114_1_1qU.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_196_1_ZLo.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_49_1_PZI.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_153_1_tuv.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_165_1_ZaI.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_12_1_eQj.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_18_1_r95.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_29_1_48p.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_109_1_Pw6.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_151_1_ILp.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_176_1_Uq0.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_71_1_bB1.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_188_1_K4l.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_48_1_Kgu.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_68_1_Wea.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_149_1_3dW.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_172_1_gIR.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_187_1_0CI.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_42_1_5cc.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_25_1_n1N.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_129_1_VlB.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_128_1_fP6.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_162_1_2m5.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_95_1_mG2.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_112_1_4wh.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_62_1_mVq.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_79_1_05S.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_135_1_NIN.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_134_1_EbJ.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_139_1_l3G.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_6_1_tTo.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_102_1_43i.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_77_1_LHz.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_98_1_dGF.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_57_1_Ge4.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_14_1_uXO.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_59_1_jIH.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_37_1_PIi.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_90_1_jRi.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_30_1_JGQ.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_106_1_2LB.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_111_1_RZV.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_54_1_Jle.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_158_1_T5G.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_4_1_ouO.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_21_1_5i9.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_72_1_P27.root',
#     '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_80_1_FIS.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_154_1_Vsj.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_155_1_RxH.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_186_1_tt0.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_118_1_mY8.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_194_1_7aF.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_47_1_fzJ.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_136_1_MGO.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_93_1_Utm.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_152_1_eml.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_82_1_WfW.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_170_1_VTv.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_3_1_V5U.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_13_1_HaV.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_96_1_Qts.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_195_1_Aw6.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_45_1_duT.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_78_1_v4g.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_89_1_AL1.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_184_1_KWn.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_115_1_hUF.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_143_1_NMO.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_2_1_O39.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_66_1_PLe.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_108_1_VGC.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_58_1_1kh.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_104_1_wuY.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_107_1_BRQ.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_180_1_NXX.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_35_1_lwu.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_33_1_nDT.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_52_1_dhc.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_130_1_zmu.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_10_1_kyz.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_16_1_A2Y.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_19_1_Hj6.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_92_1_dbS.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_87_1_hzq.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_120_1_hTe.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_169_1_pEO.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_41_1_7Lw.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_200_1_MxN.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_7_1_LZk.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_76_1_E33.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_101_1_sBS.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_15_1_OwA.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_51_1_OOQ.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_110_1_d9c.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_125_1_5T0.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_178_1_1sr.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_1_1_RcR.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_64_1_tZj.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_11_1_VuV.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_70_1_T2l.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_160_1_rYg.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_192_1_mCg.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_63_1_IwK.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_32_1_i9J.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_144_1_xnW.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_23_1_mLv.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_75_1_DkN.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_157_1_Lwh.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_5_1_pYx.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_44_1_HLR.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_150_1_dTl.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_177_1_TjC.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_185_1_yDH.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_74_1_BoD.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_132_1_6PM.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_56_1_Fqc.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_61_1_1bG.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_181_1_KYO.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_81_1_qaU.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_123_1_ZR8.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_137_1_NuZ.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_88_1_Nn3.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_131_1_KIh.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_127_1_9sL.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_189_1_P1y.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_126_1_gjQ.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_73_1_QCt.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_34_1_9HS.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_55_1_oeg.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_100_1_dZ8.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_168_1_AWh.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_67_1_DMT.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_147_1_RkK.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_99_1_0c8.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_193_1_mU0.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_175_1_pJU.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_140_1_Khv.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_124_1_YoF.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_26_1_Frj.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_141_1_r5E.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_97_1_Vxe.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_94_1_9cY.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_183_1_2xp.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_39_1_GIW.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_171_1_i0o.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_179_1_x0J.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_43_1_0FZ.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_164_1_JcF.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_22_1_vpU.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_31_1_Z7X.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_50_1_56E.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_65_1_qyM.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_182_1_OnX.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_146_1_fV8.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_103_1_0uK.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_9_1_zRp.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_46_1_L2G.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_17_1_4Ao.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_84_1_P64.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_191_1_2VU.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_166_1_vBF.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_167_1_ge8.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_174_1_Hqa.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_199_1_2PQ.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_20_1_tX1.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_83_1_QbI.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_8_1_XDh.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_91_1_K6k.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_86_1_adP.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_159_1_U5h.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_173_1_l0V.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_53_1_hzp.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_105_1_vmc.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_119_1_EeQ.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_133_1_iTL.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_85_1_oi2.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_69_1_YFL.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_198_1_8aV.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_38_1_n6m.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_40_1_PUz.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_156_1_YNl.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_28_1_RG7.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_122_1_mXs.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_117_1_3wG.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_145_1_XLB.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_163_1_zzN.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_36_1_p2F.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_113_1_hth.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_138_1_0kV.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_142_1_aRS.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_190_1_cUI.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_148_1_imQ.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_161_1_L2P.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_60_1_Tih.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_116_1_5nd.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_197_1_cX6.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_27_1_DXY.root',
# '/store/user/bortigno/WJets/FASTSIM/WJets_GEN_FASTSIM_HLT_PU_7TeV_121_1_TdR.root'

    )
                            )

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

process.WHchannelFilter = cms.EDFilter("WH_channel_filter",
                                   muonJetCleaningDRcut   = cms.untracked.double(0.5),
                                   WMassLowerCut          = cms.untracked.double(30),
                                   WMassHigherCut         = cms.untracked.double(500),
                                   bTagJetSorting         = cms.untracked.bool(False),
                                   minBTagging            = cms.untracked.double(-10000),
                                   maxBTagging            = cms.untracked.double(-10000),
                                   WCandidatePtCut        = cms.untracked.double(0),
                                   higgsCandidatePtCut    = cms.untracked.double(40),
                                   WH_deltaPhiCut         = cms.untracked.double(0),
                                   jetPtThreshold         = cms.untracked.double(30),
                                   jetVetoPtCut           = cms.untracked.double(30),

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

#process.TFileService = cms.Service("TFileService", fileName = cms.string('WH_channel.root'))

process.filter = cms.Path(process.selectPfMetWMuNus * process.patDefaultSequence * process.WHchannelFilter)

process.out = cms.OutputModule("PoolOutputModule",
                                       fileName = cms.untracked.string('WHchannel_selectedEvents.root'),
                                       SelectedEvents = cms.untracked.PSet( SelectedEvents = cms.vstring('filter') ),
                                       outputCommands = cms.untracked.vstring('keep *'
                                                                              )
                                       )

process.p = cms.Path( process.out )

