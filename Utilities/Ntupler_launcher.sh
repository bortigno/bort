#dummy launcher
#set your working dir
my_wrkdir=/shome/bortigno/ProdV11Again/CMSSW_4_2_8_patch3/src/VHbbAnalysis/VHbbDataFormats/
cd ${my_wrkdir}
source $VO_CMS_SW_DIR/cmsset_default.sh
eval `scramv1 runtime -sh`
unset TMP
unset TMPDIR
cd bin
Ntupler $1
