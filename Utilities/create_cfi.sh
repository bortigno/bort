#Input file:  should be a complete list of files you want to run on in the format "dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/....root', 
inputFileList=prova.fileList
splittedFile_prefix=`basename $inputFileList .fileList`_cfi
#split -a 3 -d -l 10 DoubleMuIVF.fileList DoubleMuIVF_cfi
#for file in ./*DoubleMuIVF_cfi*
split -a 3 -d -l 10 ${inputFileList} ${splittedFile_prefix}
for file in ./*${splittedFile_prefix}*
  do
#write on the first line
  sed -i  '1 i import FWCore.ParameterSet.Config as cms\nimport FWCore.PythonUtilities.LumiList as LumiList\nimport FWCore.ParameterSet.Types as CfgTypes\nfwliteInput = cms.PSet(\n    fileNames = cms.vstring(\n' $file
#append to the end of file
  sed -i '$a ),\n    PUmcfileName = cms.string(\"ttbarPU_35bins_fall11.root\"),\n    PUmcfileName2011B= cms.string("Fall11_Generated.root"),\n    PUdatafileName2011B = cms.string("Cert_175832-180252_PromptReco_JSON.pileupTruth_v2_finebin.root"),\n    PUdatafileName = cms.string("Pileup_2011_to_173692_LPLumiScale_68mb_35bins.root"),\n    Weight3DfileName = cms.string(""),\n    maxEvents   = cms.int32(-1),                             ## optional\n    runMin  = cms.int32(-1),\n    runMax  = cms.int32(-1),\n    skipEvents   = cms.int32(0),                             ## optional\n    outputEvery = cms.uint32(0),                            ## optional\n    lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange()),\n    )\n' $file;
  mv $file ${file/$file/$file.py}
done;
