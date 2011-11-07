#include <TSystem.h>
#include <iostream>
#include <string>
#include <vector>
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include <THStack.h>
#include "TMath.h"
#include "TRegexp.h"
#include <TPad.h>
#include <TLegend.h>

#include "Riostream.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompChol.h"
#include "TDecompSVD.h"
#include "TGraph2DErrors.h"
#include "TF2.h"

//#include "TMultiDimFit.h"

int ntupleCounter( void ){

  Bool_t addSystematics = true;
  Bool_t systematicsFromPurity = false;

  Bool_t rizziSysTTbar = false;
  Bool_t rizziSysDYB = false;
  Double_t rizziSysErr;

  Double_t ZboostCut = 120;
  Bool_t systemMethod = true;

  Int_t entries=0;

  //countLightCC control region
  Double_t countLightCCDYL =0;
  Double_t countLightCCDYB =0;
  Double_t countLightCCDYBOOSTL =0;
  Double_t countLightCCDYBOOSTB =0;
  Double_t countLightCCWJETS =0;
  Double_t countLightCCTTbar =0;
  Double_t countLightCCZZ =0;
  Double_t countLightCCWZ =0;  
  Double_t countLightCCWW =0;
  Double_t countLightCCVV =0;
  Double_t countLightCCSignal =0;
  Double_t countLightCCData =0;
  Double_t countLightCCSingleTop =0;
  Double_t countLightCCRest =0;
  Double_t countLightCCTotal =0;

  //countTTbarCC ttbar control region
  Double_t countTTbarCCDYL =0;
  Double_t countTTbarCCDYB =0;
  Double_t countTTbarCCDYBOOSTL =0;
  Double_t countTTbarCCDYBOOSTB =0;
  Double_t countTTbarCCWJETS =0;
  Double_t countTTbarCCTTbar =0;
  Double_t countTTbarCCZZ =0;
  Double_t countTTbarCCWZ =0;  
  Double_t countTTbarCCWW =0;
  Double_t countTTbarCCVV =0;
  Double_t countTTbarCCSignal =0;
  Double_t countTTbarCCData =0;
  Double_t countTTbarCCSingleTop =0;
  Double_t countTTbarCCRest =0;
  Double_t countTTbarCCTotal =0;

  //countHeavyCC heavy control region
  Double_t countHeavyCCDYL =0;
  Double_t countHeavyCCDYB =0;
  Double_t countHeavyCCDYBOOSTL =0;
  Double_t countHeavyCCDYBOOSTB =0;
  Double_t countHeavyCCWJETS =0;
  Double_t countHeavyCCTTbar =0;
  Double_t countHeavyCCZZ =0;
  Double_t countHeavyCCWZ =0;  
  Double_t countHeavyCCWW =0;
  Double_t countHeavyCCVV =0;
  Double_t countHeavyCCSignal =0;
  Double_t countHeavyCCData =0;
  Double_t countHeavyCCSingleTop =0;
  Double_t countHeavyCCRest =0;
  Double_t countHeavyCCTotal =0;

  //signal region
  Double_t countSignal115Signal = 0;
  Double_t countSignal115DYL =0;
  Double_t countSignal115DYB =0;
  Double_t countSignal115DYBOOSTL =0;
  Double_t countSignal115DYBOOSTB =0;
  Double_t countSignal115WJETS =0;
  Double_t countSignal115TTbar =0;
  Double_t countSignal115ZZ =0;
  Double_t countSignal115WZ =0;  
  Double_t countSignal115WW =0;
  Double_t countSignal115VV =0;
  Double_t countSignal115Data =0;
  Double_t countSignal115SingleTop =0;
  Double_t countSignal115Rest =0;
  Double_t countSignal115Total =0;

  //bareCountLightCC control region
  Double_t bareCountLightCCDYL =0;
  Double_t bareCountLightCCDYB =0;
  Double_t bareCountLightCCDYBOOSTL =0;
  Double_t bareCountLightCCDYBOOSTB =0;
  Double_t bareCountLightCCWJETS =0;
  Double_t bareCountLightCCTTbar =0;
  Double_t bareCountLightCCZZ =0;
  Double_t bareCountLightCCWZ =0;  
  Double_t bareCountLightCCWW =0;
  Double_t bareCountLightCCVV =0;
  Double_t bareCountLightCCSignal =0;
  Double_t bareCountLightCCData =0;

  //bareCountTTbarCC ttbar control region
  Double_t bareCountTTbarCCDYL =0;
  Double_t bareCountTTbarCCDYB =0;
  Double_t bareCountTTbarCCDYBOOSTL =0;
  Double_t bareCountTTbarCCDYBOOSTB =0;
  Double_t bareCountTTbarCCWJETS =0;
  Double_t bareCountTTbarCCTTbar =0;
  Double_t bareCountTTbarCCZZ =0;
  Double_t bareCountTTbarCCWZ =0;  
  Double_t bareCountTTbarCCWW =0;
  Double_t bareCountTTbarCCVV =0;
  Double_t bareCountTTbarCCSignal =0;
  Double_t bareCountTTbarCCData =0;

  //bareCountHeavyCC heavy control region
  Double_t bareCountHeavyCCDYL =0;
  Double_t bareCountHeavyCCDYB =0;
  Double_t bareCountHeavyCCDYBOOSTL =0;
  Double_t bareCountHeavyCCDYBOOSTB =0;
  Double_t bareCountHeavyCCWJETS =0;
  Double_t bareCountHeavyCCTTbar =0;
  Double_t bareCountHeavyCCZZ =0;
  Double_t bareCountHeavyCCWZ =0;  
  Double_t bareCountHeavyCCWW =0;
  Double_t bareCountHeavyCCVV =0;
  Double_t bareCountHeavyCCSignal =0;
  Double_t bareCountHeavyCCData =0;

  //bareCountSignal115 region
  Double_t bareCountSignal115DYL =0;
  Double_t bareCountSignal115DYB =0;
  Double_t bareCountSignal115DYBOOSTL =0;
  Double_t bareCountSignal115DYBOOSTB =0;
  Double_t bareCountSignal115WJETS =0;
  Double_t bareCountSignal115TTbar =0;
  Double_t bareCountSignal115ZZ =0;
  Double_t bareCountSignal115WZ =0;  
  Double_t bareCountSignal115WW =0;
  Double_t bareCountSignal115VV =0;
  Double_t bareCountSignal115Signal =0;
  Double_t bareCountSignal115Data =0;

  //errorLightCC control region
  Double_t errorLightCCDYL =0;
  Double_t errorLightCCDYB =0;
  Double_t errorLightCCDYBOOSTL =0;
  Double_t errorLightCCDYBOOSTB =0;
  Double_t errorLightCCWJETS =0;
  Double_t errorLightCCTTbar =0;
  Double_t errorLightCCZZ =0;
  Double_t errorLightCCWZ =0;  
  Double_t errorLightCCWW =0;
  Double_t errorLightCCVV =0;
  Double_t errorLightCCSignal =0;
  Double_t errorLightCCData =0;
  Double_t errorLightCCSingleTop =0;
  Double_t errorLightCCRest =0;
  Double_t errorLightCCTotal =0;

  //errorTTbarCC ttbar control region
  Double_t errorTTbarCCDYL =0;
  Double_t errorTTbarCCDYB =0;
  Double_t errorTTbarCCDYBOOSTL =0;
  Double_t errorTTbarCCDYBOOSTB =0;
  Double_t errorTTbarCCWJETS =0;
  Double_t errorTTbarCCTTbar =0;
  Double_t errorTTbarCCZZ =0;
  Double_t errorTTbarCCWZ =0;  
  Double_t errorTTbarCCWW =0;
  Double_t errorTTbarCCVV =0;
  Double_t errorTTbarCCSignal =0;
  Double_t errorTTbarCCData =0;
  Double_t errorTTbarCCSingleTop =0;
  Double_t errorTTbarCCRest =0;
  Double_t errorTTbarCCTotal =0;

  //errorHeavyCC heavy control region
  Double_t errorHeavyCCDYL =0;
  Double_t errorHeavyCCDYB =0;
  Double_t errorHeavyCCDYBOOSTL =0;
  Double_t errorHeavyCCDYBOOSTB =0;
  Double_t errorHeavyCCWJETS =0;
  Double_t errorHeavyCCTTbar =0;
  Double_t errorHeavyCCZZ =0;
  Double_t errorHeavyCCWZ =0;  
  Double_t errorHeavyCCWW =0;
  Double_t errorHeavyCCVV =0;
  Double_t errorHeavyCCSignal =0;
  Double_t errorHeavyCCData =0;
  Double_t errorHeavyCCSingleTop =0;
  Double_t errorHeavyCCRest =0;
  Double_t errorHeavyCCTotal =0;


  //errorSignal115 signal region
  Double_t errorSignal115Signal = 0;
  Double_t errorSignal115DYL =0;
  Double_t errorSignal115DYB =0;
  Double_t errorSignal115DYBOOSTL =0;
  Double_t errorSignal115DYBOOSTB =0;
  Double_t errorSignal115WJETS =0;
  Double_t errorSignal115TTbar =0;
  Double_t errorSignal115ZZ =0;
  Double_t errorSignal115WZ =0;  
  Double_t errorSignal115WW =0; 
  Double_t errorSignal115VV =0;
  Double_t errorSignal115Data =0;
  Double_t errorSignal115SingleTop =0;
  Double_t errorSignal115Rest =0;
  Double_t errorSignal115Total =0;

  Double_t xsecDY=3048;
  Double_t xsecDYBOOST=30;
  //  Double_t xsecDYBOOST=24;
  Double_t xsecTTbar=165;
  Double_t xsecZZ=5.9;
  Double_t xsecWZ=18.2;
  Double_t xsecWW=43;
  Double_t xsecSignal=0.4107*0.704*0.03365*3;
  Double_t xsecWJETS=31314;

  Double_t xsecT_schannel=3.19;
  Double_t xsecTbar_schannel=1.44;
  Double_t xsecT_tchannel=41.92;
  Double_t xsecTbar_tchannel=22.65;
  Double_t xsecT_tWchannel=7.87;
  Double_t xsecTbar_tWchannel=7.87;


  int candType = 1;

  //sample6
  //  std::string path("/data2/nmohr/SUSY/PAT/Histos/");
  //sample7 in pceth116
  //  std::string path("/data1/VHbbAnalysis/EDMNtuple_step2/V9/sample7/");
  //  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V9/oct9Ntuple/");
  //  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V9/oct7Ntuple/");

  //V11    
//   std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Oct27th/");
//   std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Oct27th/");
  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov1st/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Oct27th/");

    
  //data
  std::vector<TFile*> dataFileList;
  std::string file_DoubleElePromptRecoV4(pathData+"BestCSV_DoubleElectron_Run2011A_PromptRecoV4.root");
  dataFileList.push_back(TFile::Open(file_DoubleElePromptRecoV4.c_str()));
  std::string file_DoubleEleMay(pathData+"BestCSV_DoubleElectron_Run2011_May10Rereco.root");
  dataFileList.push_back(TFile::Open(file_DoubleEleMay.c_str()));
  std::string file_DoubleEleAug(pathData+"BestCSV_DoubleElectron_Run2011A_Aug05ReReco.root");
  dataFileList.push_back(TFile::Open(file_DoubleEleAug.c_str()));
  std::string file_DoubleElePromptRecoV6(pathData+"BestCSV_DoubleElectron_Run2011A_PromptRecoV6.root");
  dataFileList.push_back(TFile::Open(file_DoubleElePromptRecoV6.c_str()));

  //for sample7
  //   //forZ
  //   std::string file_ZH110(path+"TestZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV9_ProcV1.root");
  //   std::string file_TTbar(path+"TestTTJets_TuneZ2_7TeV-madgraph-tauola_HBB_EDMNtupleV9_ProcV1.root");
  //   std::string file_DY(path+"TestDYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_HBB_EDMNtupleV9_ProcV1.root");
  //   std::string file_ZZ(path+"TestZZ_TuneZ2_7TeV_pythia6_tauola_HBB_EDMNtupleV9_ProcV1.root");
  //   std::string file_WZ(path+"TestWZ_TuneZ2_7TeV_pythia6_tauola_HBB_EDMNtupleV9_ProcV1.root");
  //   std::string file_WW(path+"TestWW_TuneZ2_7TeV_pythia6_tauola_HBB_EDMNtupleV9_ProcV1.root");
  //   //forW
  //   std::string file_WJETS(path+"TestWJetsToLNu_TuneZ2_7TeV-madgraph-tauola_HBB_EDMNtupleV9_ProcV1.root");
  //   //  std::string file_ST(path+"");

  //for oct5Ntuple
  std::string file_ZH115(path+"BestCSV_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root");
  std::string file_DY(path+"BestCSV_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root");
  std::string file_DYBOOST(path+"BestCSV_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root");
  std::string file_ZZ(path+"BestCSV_ZZ_TuneZ2_7TeV_pythia6_tauola.root");
  std::string file_WZ(path+"BestCSV_WZ_TuneZ2_7TeV_pythia6_tauola.root");
  std::string file_WW(path+"BestCSV_WW_TuneZ2_7TeV_pythia6_tauola.root");
  std::string file_TTbar(path+"BestCSV_TTJets_TuneZ2_7TeV-madgraph-tauola.root");
  std::string file_T_schannel (path+"BestCSV_T_TuneZ2_s-channel_7TeV-powheg-tauola.root");
  std::string file_T_tchannel (path+"BestCSV_T_TuneZ2_t-channel_7TeV-powheg-tauola.root");
  std::string file_T_tWchannel (path+"BestCSV_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root");
  std::string file_Tbar_schannel (path+"BestCSV_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root");
  std::string file_Tbar_tchannel (path+"BestCSV_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root");
  std::string file_Tbar_tWchannel (path+"BestCSV_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root");
  //forW
  std::string file_WJETS(path+"BestCSV_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root");
  //  std::string file_ST(path+"");

  std::vector<TFile *> signalFileList, bkgFileList, DYfileList;
  std::vector<double> signalxsec,bkgxsec,DYxsec;

  TFile * s = TFile::Open(file_ZH115.c_str());
  signalFileList.push_back(s);
  signalxsec.push_back(xsecSignal);
  Double_t SignalMC_normalisation=((double)(Count->GetBinContent(1))/xsecSignal);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << SignalMC_normalisation << std::endl;
  TFile * dy = TFile::Open(file_DY.c_str());
  DYfileList.push_back(dy);
  DYxsec.push_back(xsecDY);
  Double_t DYMC_normalisation=((double)(Count->GetBinContent(1))/xsecDY);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << DYMC_normalisation << std::endl;
  TFile * dyboost = TFile::Open(file_DYBOOST.c_str());
  DYfileList.push_back(dyboost);
  DYxsec.push_back(xsecDYBOOST);
  Double_t DYBOOSTMC_normalisation=((double)(Count->GetBinContent(1))/xsecDYBOOST);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << DYBOOSTMC_normalisation << std::endl;
  TFile * ttbar = TFile::Open(file_TTbar.c_str());
  bkgFileList.push_back(ttbar);
  bkgxsec.push_back(xsecTTbar);
  Double_t TTbarMC_normalisation=((double)(Count->GetBinContent(1))/xsecTTbar);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << TTbarMC_normalisation << std::endl;
  TFile * zz = TFile::Open(file_ZZ.c_str());
  bkgFileList.push_back(zz);
  bkgxsec.push_back(xsecZZ);
  Double_t ZZMC_normalisation=((double)(Count->GetBinContent(1))/xsecZZ);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << ZZMC_normalisation << std::endl;
  TFile * wz = TFile::Open(file_WZ.c_str());
  bkgFileList.push_back(wz);
  bkgxsec.push_back(xsecWZ);
  Double_t WZMC_normalisation=((double)(Count->GetBinContent(1))/xsecWZ);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << WZMC_normalisation << std::endl;
  TFile * ww = TFile::Open(file_WW.c_str());
  bkgFileList.push_back(ww);
  bkgxsec.push_back(xsecWW);
  Double_t WWMC_normalisation=((double)(Count->GetBinContent(1))/xsecWW);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << WWMC_normalisation << std::endl;
  TFile * wjets = TFile::Open(file_WJETS.c_str());
  bkgFileList.push_back(wjets);
  bkgxsec.push_back(xsecWJETS);
  Double_t WJETSMC_normalisation=((double)(Count->GetBinContent(1))/xsecWJETS);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << WJETSMC_normalisation << std::endl;

  TFile * T_schannel = TFile::Open(file_T_schannel.c_str());
  bkgFileList.push_back(T_schannel);
  bkgxsec.push_back(xsecT_schannel);
  Double_t T_schannelMC_normalisation=((double)(Count->GetBinContent(1))/xsecT_schannel);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << T_schannelMC_normalisation << std::endl;
  TFile * Tbar_schannel = TFile::Open(file_Tbar_schannel.c_str());
  bkgFileList.push_back(Tbar_schannel);
  bkgxsec.push_back(xsecTbar_schannel);
  Double_t Tbar_schannelMC_normalisation=((double)(Count->GetBinContent(1))/xsecTbar_schannel);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << Tbar_schannelMC_normalisation << std::endl;
  TFile * T_tchannel = TFile::Open(file_T_tchannel.c_str());
  bkgFileList.push_back(T_tchannel);
  bkgxsec.push_back(xsecT_tchannel);
  Double_t T_tchannelMC_normalisation=((double)(Count->GetBinContent(1))/xsecT_tchannel);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << T_tchannelMC_normalisation << std::endl;
  TFile * Tbar_tchannel = TFile::Open(file_Tbar_tchannel.c_str());
  bkgFileList.push_back(Tbar_tchannel);
  bkgxsec.push_back(xsecTbar_tchannel);
  Double_t Tbar_tchannelMC_normalisation=((double)(Count->GetBinContent(1))/xsecTbar_tchannel);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << Tbar_tchannelMC_normalisation << std::endl;
  TFile * T_tWchannel = TFile::Open(file_T_tWchannel.c_str());
  bkgFileList.push_back(T_tWchannel);
  bkgxsec.push_back(xsecT_tWchannel);
  Double_t T_tWchannelMC_normalisation=((double)(Count->GetBinContent(1))/xsecT_tWchannel);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << T_tWchannelMC_normalisation << std::endl;
  TFile * Tbar_tWchannel = TFile::Open(file_Tbar_tWchannel.c_str());
  bkgFileList.push_back(Tbar_tWchannel);
  bkgxsec.push_back(xsecTbar_tWchannel);
  Double_t Tbar_tWchannelMC_normalisation=((double)(Count->GetBinContent(1))/xsecTbar_tWchannel);
  std::cout << Count->GetBinContent(1) << std::endl;
  std::cout << Tbar_tWchannelMC_normalisation << std::endl;

  //for 0ct9
  Double_t ZeeL=215.094+930.228+370.915+662.967;
  Double_t ZmmL=215.094+930.228+370.915+662.967;
  //   ZeeL=215.094+930.228;
  //   ZmmL=215.094+930.228;

  //   ZeeL=1143;
  //   ZmmL=1143;

  std::vector<double> bareCountLightCC;
  std::vector<double> bareCountTTbarCC;
  std::vector<double> bareCountHeavyCC;
  std::vector<double> bareCountSignal115;

  std::vector<double> countLightCC;
  std::vector<double> countTTbarCC;
  std::vector<double> countHeavyCC;
  std::vector<double> countSignal115;

  std::vector<double> e_countLightCC;
  std::vector<double> e_countTTbarCC;
  std::vector<double> e_countHeavyCC;
  std::vector<double> e_countSignal115;

  //old control regions
  //   TCut HeavyCC_cutString("btag2TSF*PUweight*weightTrig*(hbhe & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & (H.mass < 90. | H.mass > 145.) & V.mass > 75. & V.mass < 105 & abs( HVdPhi ) > 2.9 & hJet_csv[0] > 0.898 & hJet_csv[1] > 0.898 & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ) )");
  //   TCut TTbarCC_cutString("PUweight*weightTrig*(hbhe & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & V.mass > 120 & MET.et > 50 & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");
  //   TCut LightCC_cutString("PUweight*weightTrig*(hbhe & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & H.pt > 100. & V.pt > 100. & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & V.mass > 75. & V.mass < 105 & hJet_csv[0] < 0.898 & hJet_csv[1] < 0.898 & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");

  //  new Control regions
  //   TCut HeavyCC_cutString("btag2TSF*PUweight*weightTrig*(hbhe & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & (H.mass < 90. | H.mass > 145.) & V.mass > 75. & V.mass < 105 & MET.et < 30 & hJet_csv[0] > 0.898 & hJet_csv[1] > 0.898 & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ) )");
  //   TCut TTbarCC_cutString("PUweight*weightTrig*(hbhe & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & V.mass > 120 & MET.et > 50 & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");
  //   TCut LightCC_cutString("PUweight*weightTrig*(hbhe & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & H.pt > 100. & V.pt > 100. & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & V.mass > 75. & V.mass < 105 & hJet_csv[0] < 0.898 & hJet_csv[1] < 0.898 & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");


//   //very new
//   //AddLightControl
//   TCut LightCC_weights("PUweight*weightTrig");
//   TCut LightCC_cutString("(hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & V.pt > 100. & H.pt > 100. & abs( HVdPhi ) > 2.9 & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & V.mass > 75. & V.mass < 105 & hJet_csv[0] < 0.898 & hJet_csv[1] < 0.898 & (hJet_csv[0] < 0.5 | hJet_csv[1] < 0.5) & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");

//   //AddTopControl
//   //"btag1T2CSF*
//   TCut TTbarCC_weights("btag1T2CSF*PUweight*weightTrig");
//   TCut TTbarCC_cutString("(hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & H.pt > 100. & ((hJet_csv[0] > 0.898 & hJet_csv[1] > 0.5) | (hJet_csv[0] > 0.5 & hJet_csv[1] > 0.898)) & (V.mass > 105 | V.mass < 75.) & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");

//   //AddbbControl
//   //"btag1T2CSF*
//   TCut HeavyCC_weights("btag1T2CSF*PUweight*weightTrig");
//   TCut HeavyCC_cutString("(hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & (H.mass < 90. | H.mass > 145.) & V.mass > 75. & V.mass < 105 & ((hJet_csv[0] > 0.898 & hJet_csv[1] > 0.5) | (hJet_csv[0] > 0.5 & hJet_csv[1] > 0.898)) & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & abs( HVdPhi ) > 2.9 & V.pt < 100. & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");

//2011 LightCC
  TCut LightCC_weights("btagA0TSF*PUweight*weightTrig");
  TCut LightCC_cutString("H.mass < 300. & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & V.pt > 100. & H.pt > 100. & abs( HVdPhi ) > 2.9 & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & V.mass > 75. & V.mass < 105 & !(hJet_csv[0] > 0.898 | hJet_csv[1] > 0.898) & H.mass < 300. & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] )");

  //2011 TTbarCC
  TCut TTbarCC_weights("btag1T2CSF*PUweight*weightTrig");
  TCut TTbarCC_cutString("H.mass < 300 & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & H.pt > 100. & ((hJet_csv[0] > 0.898 & hJet_csv[1] > 0.5) | (hJet_csv[0] > 0.5 & hJet_csv[1] > 0.898)) & (V.mass > 105 | V.mass < 75.) & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] )");

  //2011 HeavyCC
  TCut HeavyCC_weights("btag1T2CSF*PUweight*weightTrig");
  TCut HeavyCC_cutString("H.mass < 300 & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & (H.mass < 90. | H.mass > 145.) & V.mass > 75. & V.mass < 105 & ((hJet_csv[0] > 0.898 & hJet_csv[1] > 0.5) | (hJet_csv[0] > 0.5 & hJet_csv[1] > 0.898)) & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & abs( HVdPhi ) > 2.9 & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] )");

  //2011 Signal
  TCut Signal115_weights("btag1T2CSF*PUweight*weightTrig");
  TCut Signal115_cutString("(hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & H.mass > 90. & H.mass < 125. & V.mass > 75. & V.mass < 105 & ((hJet_csv[0] > 0.898 & hJet_csv[1] > 0.5) | (hJet_csv[0] > 0.5 & hJet_csv[1] > 0.898)) & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & abs( HVdPhi ) > 2.9 & V.pt < 100. & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");

  //development cut string
  //  TCut TTbarCC_cutString("PUweight*weightTrig*(hbhe & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & V.mass > 120 & hJet_csv[0] > 0.898 & hJet_csv[1] > 0.898 & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");


  TCut forDYstitching;
  TCut isB("eventFlav == 5");
  TCut isNotB("eventFlav != 5");

  TH1D *h_light,* h_ttbar, * h_heavy, *h_signal;
  TH1D *hl_light,* hl_ttbar,*hl_heavy, *hl_signal;

  //standard signal MC sample
  for(unsigned int iFile = 0; iFile<signalFileList.size();iFile++){
    signalFileList.at(iFile)->cd();
    std::cout << "Sample = " << signalFileList.at(iFile)->GetName() << std::endl;

    bareCountLightCC.push_back((tree->Draw("H.Pt>>h_light", LightCC_weights*LightCC_cutString, "goff")));
    bareCountTTbarCC.push_back((tree->Draw("H.Pt>>h_ttbar", TTbarCC_weights*TTbarCC_cutString, "goff")));
    bareCountHeavyCC.push_back((tree->Draw("H.Pt>>h_heavy", HeavyCC_weights*HeavyCC_cutString, "goff")));
    bareCountSignal115.push_back((tree->Draw("H.Pt>>h_signal", Signal115_weights*Signal115_cutString, "goff")));

    std::cout << "Entries from cut string light = " << bareCountLightCC.at(iFile) << std::endl;
    std::cout << "Entries from cut string ttbar = " << bareCountTTbarCC.at(iFile) << std::endl;
    std::cout << "Entries from cut string heavy = " << bareCountHeavyCC.at(iFile) << std::endl;
    std::cout << "Entries from cut string signal = " << bareCountSignal115.at(iFile) << std::endl;

    h_light = (TH1D*)gDirectory->Get("h_light");
    h_ttbar = (TH1D*)gDirectory->Get("h_ttbar");
    h_heavy = (TH1D*)gDirectory->Get("h_heavy");
    h_signal = (TH1D*)gDirectory->Get("h_signal");

    countLightCC.push_back(ZeeL*((double)(signalxsec.at(iFile)/Count->GetBinContent(1)))*(h_light->Integral()));
    countTTbarCC.push_back(ZeeL*((double)(signalxsec.at(iFile)/Count->GetBinContent(1)))*(h_ttbar->Integral()));
    countHeavyCC.push_back(ZeeL*((double)(signalxsec.at(iFile)/Count->GetBinContent(1)))*(h_heavy->Integral()));
    countSignal115.push_back(ZeeL*((double)(signalxsec.at(iFile)/Count->GetBinContent(1)))*(h_signal->Integral()));

    if(bareCountLightCC.at(iFile) > 0.) e_countLightCC.push_back(countLightCC.at(iFile)/TMath::Sqrt(bareCountLightCC.at(iFile)));
    else  e_countLightCC.push_back(0);
    if(bareCountTTbarCC.at(iFile) > 0.) e_countTTbarCC.push_back(countTTbarCC.at(iFile)/TMath::Sqrt(bareCountTTbarCC.at(iFile)));
    else  e_countTTbarCC.push_back(0);
    if(bareCountHeavyCC.at(iFile) > 0.) e_countHeavyCC.push_back(countHeavyCC.at(iFile)/TMath::Sqrt(bareCountHeavyCC.at(iFile)));
    else  e_countHeavyCC.push_back(0);
    if(bareCountSignal115.at(iFile) > 0.) e_countSignal115.push_back(countSignal115.at(iFile)/TMath::Sqrt(bareCountSignal115.at(iFile)));
    else  e_countSignal115.push_back(0);

    std::cout << "Integral light = " << countLightCC.at(iFile) << " +- " << e_countLightCC.at(iFile) << std::endl;
    std::cout << "Integral ttbar = " << countTTbarCC.at(iFile) << " +- " << e_countTTbarCC.at(iFile) << std::endl;
    std::cout << "Integral heavy = " << countHeavyCC.at(iFile) << " +- " << e_countHeavyCC.at(iFile) << std::endl;
    std::cout << "Integral signal = " << countSignal115.at(iFile) << " +- " << e_countSignal115.at(iFile) << std::endl;

  }

  //standard background MC sample
  for(unsigned int iFile = 0; iFile<bkgFileList.size();iFile++){
    bkgFileList.at(iFile)->cd();
    std::cout << "Sample = " << bkgFileList.at(iFile)->GetName() << std::endl;

    bareCountLightCC.push_back((tree->Draw("H.Pt>>h_light", LightCC_weights*LightCC_cutString, "goff")));
    bareCountTTbarCC.push_back((tree->Draw("H.Pt>>h_ttbar", TTbarCC_weights*TTbarCC_cutString, "goff")));
    bareCountHeavyCC.push_back((tree->Draw("H.Pt>>h_heavy", HeavyCC_weights*HeavyCC_cutString, "goff")));
    bareCountSignal115.push_back((tree->Draw("H.Pt>>h_signal", Signal115_weights*Signal115_cutString, "goff")));

    std::cout << "Entries from cut string light = " << bareCountLightCC.at(iFile+signalFileList.size()) << std::endl;
    std::cout << "Entries from cut string ttbar = " << bareCountTTbarCC.at(iFile+signalFileList.size()) << std::endl;
    std::cout << "Entries from cut string heavy = " << bareCountHeavyCC.at(iFile+signalFileList.size()) << std::endl;
    std::cout << "Entries from cut string signal = " << bareCountSignal115.at(iFile+signalFileList.size()) << std::endl;

    h_light = (TH1D*)gDirectory->Get("h_light");
    h_ttbar = (TH1D*)gDirectory->Get("h_ttbar");
    h_heavy = (TH1D*)gDirectory->Get("h_heavy");
    h_signal = (TH1D*)gDirectory->Get("h_signal");

    countLightCC.push_back(ZeeL*((double)(bkgxsec.at(iFile)/Count->GetBinContent(1)))*(h_light->Integral()));
    countTTbarCC.push_back(ZeeL*((double)(bkgxsec.at(iFile)/Count->GetBinContent(1)))*(h_ttbar->Integral()));
    countHeavyCC.push_back(ZeeL*((double)(bkgxsec.at(iFile)/Count->GetBinContent(1)))*(h_heavy->Integral()));
    countSignal115.push_back(ZeeL*((double)(bkgxsec.at(iFile)/Count->GetBinContent(1)))*(h_signal->Integral()));

    if(bareCountLightCC.at(iFile+signalFileList.size())>0)    e_countLightCC.push_back(countLightCC.at(iFile+signalFileList.size())/TMath::Sqrt(bareCountLightCC.at(iFile+signalFileList.size())));
    else  e_countLightCC.push_back(0);
    if(bareCountTTbarCC.at(iFile+signalFileList.size())>0)    e_countTTbarCC.push_back(countTTbarCC.at(iFile+signalFileList.size())/TMath::Sqrt(bareCountTTbarCC.at(iFile+signalFileList.size())));
    else  e_countTTbarCC.push_back(0);
    if(bareCountHeavyCC.at(iFile+signalFileList.size())>0)    e_countHeavyCC.push_back(countHeavyCC.at(iFile+signalFileList.size())/TMath::Sqrt(bareCountHeavyCC.at(iFile+signalFileList.size())));
    else  e_countHeavyCC.push_back(0);
    if(bareCountSignal115.at(iFile+signalFileList.size())>0)    e_countSignal115.push_back(countSignal115.at(iFile+signalFileList.size())/TMath::Sqrt(bareCountSignal115.at(iFile+signalFileList.size())));
    else  e_countSignal115.push_back(0);

    //only for TTbar
    if(rizziSysTTbar == true && iFile==0){
      std::cout << "is this ttbar??? = " << bkgFileList.at(iFile)->GetName() << std::endl;
      rizzySysErr=0.2;
      e_countLightCC.at(iFile+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countLightCC.at(iFile+signalFileList.size()),2) + TMath::Power( rizziSysErr*countLightCC.at(iFile+signalFileList.size()),2));
      e_countTTbarCC.at(iFile+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countTTbarCC.at(iFile+signalFileList.size()),2) + TMath::Power( rizziSysErr*countTTbarCC.at(iFile+signalFileList.size()),2));
      e_countHeavyCC.at(iFile+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countHeavyCC.at(iFile+signalFileList.size()),2) + TMath::Power( rizziSysErr*countHeavyCC.at(iFile+signalFileList.size()),2));
      e_countSignal115.at(iFile+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countSignal115.at(iFile+signalFileList.size()),2) + TMath::Power( rizziSysErr*countSignal115.at(iFile+signalFileList.size()),2));
    }

    std::cout << "Integral light = " << countLightCC.at(iFile+signalFileList.size()) << " +- " << e_countLightCC.at(iFile+signalFileList.size()) << std::endl;
    std::cout << "Integral ttbar = " << countTTbarCC.at(iFile+signalFileList.size()) << " +- " << e_countTTbarCC.at(iFile+signalFileList.size()) << std::endl;
    std::cout << "Integral heavy = " << countHeavyCC.at(iFile+signalFileList.size()) << " +- " << e_countHeavyCC.at(iFile+signalFileList.size()) << std::endl;
    std::cout << "Integral signal = " << countSignal115.at(iFile+signalFileList.size()) << " +- " << e_countSignal115.at(iFile+signalFileList.size()) << std::endl;

  }


  //DY MC sample
  for(unsigned int iFile = 0; iFile<DYfileList.size();iFile++){
    DYfileList.at(iFile)->cd();
    std::cout << "Sample = " << DYfileList.at(iFile)->GetName() << std::endl;
    std::string sampleName(DYfileList.at(iFile)->GetName());
    //     if(sampleName != file_DYBOOST)
    //       forDYstitching = "genZpt <= 120";
    //     else
    //       forDYstitching = "genZpt > 120";
    
    if(iFile == 0){
      forDYstitching = "genZpt <= 120";

      bareCountLightCC.push_back((tree->Draw("H.Pt>>h_light", LightCC_weights*(LightCC_cutString&&forDYstitching&&isNotB) , "goff")));
      bareCountTTbarCC.push_back((tree->Draw("H.Pt>>h_ttbar", TTbarCC_weights*(TTbarCC_cutString&&forDYstitching&&isNotB), "goff")));
      bareCountHeavyCC.push_back((tree->Draw("H.Pt>>h_heavy", HeavyCC_weights*(HeavyCC_cutString&&forDYstitching&&isNotB), "goff")));
      bareCountSignal115.push_back((tree->Draw("H.Pt>>h_signal", Signal115_weights*(Signal115_cutString&&forDYstitching&&isNotB), "goff")));
      
      std::cout << "Entries from cut string light l = " << bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+0) << std::endl;
      std::cout << "Entries from cut string ttbar l = " << bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+0) << std::endl;
      std::cout << "Entries from cut string heavy l = " << bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+0) << std::endl;
      std::cout << "Entries from cut string signal l = " << bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+0) << std::endl;

      h_light = (TH1D*)gDirectory->Get("h_light");
      h_ttbar = (TH1D*)gDirectory->Get("h_ttbar");
      h_heavy = (TH1D*)gDirectory->Get("h_heavy");
      h_signal = (TH1D*)gDirectory->Get("h_signal");
      
      countLightCC.push_back(ZeeL*((double)(DYxsec.at(0)/Count->GetBinContent(1)))*(h_light->Integral()));
      countTTbarCC.push_back(ZeeL*((double)(DYxsec.at(0)/Count->GetBinContent(1)))*(h_ttbar->Integral()));
      countHeavyCC.push_back(ZeeL*((double)(DYxsec.at(0)/Count->GetBinContent(1)))*(h_heavy->Integral()));
      countSignal115.push_back(ZeeL*((double)(DYxsec.at(0)/Count->GetBinContent(1)))*(h_signal->Integral()));
      
      if(bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+0)>0)      e_countLightCC.push_back(countLightCC.at(bkgFileList.size()+signalFileList.size()+0)/TMath::Sqrt(bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+0)));
      else  e_countLightCC.push_back(0);
      if(bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+0)>0)      e_countTTbarCC.push_back(countTTbarCC.at(bkgFileList.size()+signalFileList.size()+0)/TMath::Sqrt(bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+0)));
      else  e_countTTbarCC.push_back(0);
      if(bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+0)>0)      e_countHeavyCC.push_back(countHeavyCC.at(bkgFileList.size()+signalFileList.size()+0)/TMath::Sqrt(bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+0)));
      else  e_countHeavyCC.push_back(0);
      if(bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+0)>0)      e_countSignal115.push_back(countSignal115.at(bkgFileList.size()+signalFileList.size()+0)/TMath::Sqrt(bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+0)));
      else  e_countSignal115.push_back(0);

      std::cout << "Integral light = " << countLightCC.at(bkgFileList.size()+signalFileList.size()) << " +- " << e_countLightCC.at(0+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral ttbar = " << countTTbarCC.at(bkgFileList.size()+signalFileList.size()) << " +- " << e_countTTbarCC.at(0+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral heavy = " << countHeavyCC.at(bkgFileList.size()+signalFileList.size()) << " +- " << e_countHeavyCC.at(0+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral signal = " << countSignal115.at(bkgFileList.size()+signalFileList.size()) << " +- " << e_countSignal115.at(0+bkgFileList.size()+signalFileList.size()) << std::endl;
      
      bareCountLightCC.push_back((tree->Draw("H.Pt>>hl_light", LightCC_weights*(LightCC_cutString&&forDYstitching&&isB), "goff")));
      bareCountTTbarCC.push_back((tree->Draw("H.Pt>>hl_ttbar", TTbarCC_weights*(TTbarCC_cutString&&forDYstitching&&isB), "goff")));
      bareCountHeavyCC.push_back((tree->Draw("H.Pt>>hl_heavy", HeavyCC_weights*(HeavyCC_cutString&&forDYstitching&&isB), "goff"))); 
      bareCountSignal115.push_back((tree->Draw("H.Pt>>hl_signal", Signal115_weights*(Signal115_cutString&&forDYstitching&&isB), "goff"))); 
        
      std::cout << "Entries from cut string light b = " << bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+1) << std::endl;
      std::cout << "Entries from cut string ttbar b = " << bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+1) << std::endl;
      std::cout << "Entries from cut string heavy b = " << bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+1) << std::endl;
      std::cout << "Entries from cut string signal b = " << bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+1) << std::endl;

      hl_light = (TH1D*)gDirectory->Get("hl_light");
      hl_ttbar = (TH1D*)gDirectory->Get("hl_ttbar");
      hl_heavy = (TH1D*)gDirectory->Get("hl_heavy");
      hl_signal = (TH1D*)gDirectory->Get("hl_signal");

      countLightCC.push_back(ZeeL*((double)(DYxsec.at(0)/Count->GetBinContent(1)))*(hl_light->Integral()));
      countTTbarCC.push_back(ZeeL*((double)(DYxsec.at(0)/Count->GetBinContent(1)))*(hl_ttbar->Integral()));
      countHeavyCC.push_back(ZeeL*((double)(DYxsec.at(0)/Count->GetBinContent(1)))*(hl_heavy->Integral()));
      countSignal115.push_back(ZeeL*((double)(DYxsec.at(0)/Count->GetBinContent(1)))*(hl_signal->Integral()));
      
      if(bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+1)>0)      e_countLightCC.push_back(countLightCC.at(bkgFileList.size()+signalFileList.size()+1)/TMath::Sqrt(bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+1)));
      else  e_countLightCC.push_back(0);
      if(bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+1)>0)     e_countTTbarCC.push_back(countTTbarCC.at(bkgFileList.size()+signalFileList.size()+1)/TMath::Sqrt(bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+1)));
      else  e_countTTbarCC.push_back(0);
      if(bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+1)>0)      e_countHeavyCC.push_back(countHeavyCC.at(bkgFileList.size()+signalFileList.size()+1)/TMath::Sqrt(bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+1)));
      else  e_countHeavyCC.push_back(0);
      if(bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+1)>0)      e_countSignal115.push_back(countSignal115.at(bkgFileList.size()+signalFileList.size()+1)/TMath::Sqrt(bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+1)));
      else  e_countSignal115.push_back(0);


      if(rizziSysDYB){
	rizzySysErr=0.5;
	e_countLightCC.at(1+bkgFileList.size()+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countLightCC.at(1+bkgFileList.size()+signalFileList.size()),2) + TMath::Power( rizziSysErr*countLightCC.at(1+bkgFileList.size()+signalFileList.size()),2));
	e_countTTbarCC.at(1+bkgFileList.size()+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countTTbarCC.at(1+bkgFileList.size()+signalFileList.size()),2) + TMath::Power( rizziSysErr*countTTbarCC.at(1+bkgFileList.size()+signalFileList.size()),2));
	e_countHeavyCC.at(1+bkgFileList.size()+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countHeavyCC.at(1+bkgFileList.size()+signalFileList.size()),2) + TMath::Power( rizziSysErr*countHeavyCC.at(1+bkgFileList.size()+signalFileList.size()),2));
	e_countSignal115.at(1+bkgFileList.size()+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countSignal115.at(1+bkgFileList.size()+signalFileList.size()),2) + TMath::Power( rizziSysErr*countSignal115.at(1+bkgFileList.size()+signalFileList.size()),2));
      }

      std::cout << "Integral light = " << countLightCC.at(1+bkgFileList.size()+signalFileList.size()) << " +- " << e_countLightCC.at(1+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral ttbar = " << countTTbarCC.at(1+bkgFileList.size()+signalFileList.size()) << " +- " << e_countTTbarCC.at(1+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral heavy = " << countHeavyCC.at(1+bkgFileList.size()+signalFileList.size()) << " +- " << e_countHeavyCC.at(1+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral signal = " << countSignal115.at(1+bkgFileList.size()+signalFileList.size()) << " +- " << e_countSignal115.at(1+bkgFileList.size()+signalFileList.size()) << std::endl;
      
    }
    
    else if(iFile == 1){
      forDYstitching = "genZpt > 120";
      bareCountLightCC.push_back((tree->Draw("H.Pt>>h_light", LightCC_weights*(LightCC_cutString&&forDYstitching&&isNotB), "goff")));
      bareCountTTbarCC.push_back((tree->Draw("H.Pt>>h_ttbar", TTbarCC_weights*(TTbarCC_cutString&&forDYstitching&&isNotB), "goff")));
      bareCountHeavyCC.push_back((tree->Draw("H.Pt>>h_heavy", HeavyCC_weights*(HeavyCC_cutString&&forDYstitching&&isNotB), "goff")));
      bareCountSignal115.push_back((tree->Draw("H.Pt>>h_signal", Signal115_weights*(Signal115_cutString&&forDYstitching&&isNotB), "goff")));
      
      std::cout << "Entries from cut string light l = " << bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+2) << std::endl;
      std::cout << "Entries from cut string ttbar l = " << bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+2) << std::endl;
      std::cout << "Entries from cut string heavy l = " << bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+2) << std::endl;
      std::cout << "Entries from cut string signal l = " << bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+2) << std::endl;

      h_light = (TH1D*)gDirectory->Get("h_light");
      h_ttbar = (TH1D*)gDirectory->Get("h_ttbar");
      h_heavy = (TH1D*)gDirectory->Get("h_heavy");
      h_signal = (TH1D*)gDirectory->Get("h_signal");
      
      countLightCC.push_back(ZeeL*((double)(DYxsec.at(1)/Count->GetBinContent(1)))*(h_light->Integral()));
      countTTbarCC.push_back(ZeeL*((double)(DYxsec.at(1)/Count->GetBinContent(1)))*(h_ttbar->Integral()));
      countHeavyCC.push_back(ZeeL*((double)(DYxsec.at(1)/Count->GetBinContent(1)))*(h_heavy->Integral()));
      countSignal115.push_back(ZeeL*((double)(DYxsec.at(1)/Count->GetBinContent(1)))*(h_signal->Integral()));
      
      if(bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+2)>0)      e_countLightCC.push_back(countLightCC.at(bkgFileList.size()+signalFileList.size()+2)/TMath::Sqrt(bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+2)));
      else  e_countLightCC.push_back(0);
      if(bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+2)>0)      e_countTTbarCC.push_back(countTTbarCC.at(bkgFileList.size()+signalFileList.size()+2)/TMath::Sqrt(bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+2)));
      else  e_countTTbarCC.push_back(0);
      if(bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+2)>0)      e_countHeavyCC.push_back(countHeavyCC.at(bkgFileList.size()+signalFileList.size()+2)/TMath::Sqrt(bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+2)));
      else  e_countHeavyCC.push_back(0);
      if(bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+2)>0)      e_countSignal115.push_back(countSignal115.at(bkgFileList.size()+signalFileList.size()+2)/TMath::Sqrt(bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+2)));
      else  e_countSignal115.push_back(0);


      std::cout << "Integral light = " << countLightCC.at(2+bkgFileList.size()+signalFileList.size()) << " +- " << e_countLightCC.at(2+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral ttbar = " << countTTbarCC.at(2+bkgFileList.size()+signalFileList.size()) << " +- " << e_countTTbarCC.at(2+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral heavy = " << countHeavyCC.at(2+bkgFileList.size()+signalFileList.size()) << " +- " << e_countHeavyCC.at(2+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral signal = " << countSignal115.at(2+bkgFileList.size()+signalFileList.size()) << " +- " << e_countSignal115.at(2+bkgFileList.size()+signalFileList.size()) << std::endl;
      
      bareCountLightCC.push_back((tree->Draw("H.Pt>>hl_light", LightCC_weights*(LightCC_cutString&&forDYstitching&&isB), "goff")));
      bareCountTTbarCC.push_back((tree->Draw("H.Pt>>hl_ttbar", TTbarCC_weights*(TTbarCC_cutString&&forDYstitching&&isB), "goff")));
      bareCountHeavyCC.push_back((tree->Draw("H.Pt>>hl_heavy", HeavyCC_weights*(HeavyCC_cutString&&forDYstitching&&isB), "goff")));
      bareCountSignal115.push_back((tree->Draw("H.Pt>>hl_signal", Signal115_weights*(Signal115_cutString&&forDYstitching&&isB), "goff")));
      
      std::cout << "Entries from cut string light b = " << bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+3) << std::endl;
      std::cout << "Entries from cut string ttbar b = " << bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+3) << std::endl;
      std::cout << "Entries from cut string heavy b = " << bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+3) << std::endl;
      std::cout << "Entries from cut string signal b = " << bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+3) << std::endl;

      hl_light = (TH1D*)gDirectory->Get("hl_light");
      hl_ttbar = (TH1D*)gDirectory->Get("hl_ttbar");
      hl_heavy = (TH1D*)gDirectory->Get("hl_heavy");
      hl_signal = (TH1D*)gDirectory->Get("hl_signal");
      
      countLightCC.push_back(ZeeL*((double)(DYxsec.at(1)/Count->GetBinContent(1)))*(hl_light->Integral()));
      countTTbarCC.push_back(ZeeL*((double)(DYxsec.at(1)/Count->GetBinContent(1)))*(hl_ttbar->Integral()));
      countHeavyCC.push_back(ZeeL*((double)(DYxsec.at(1)/Count->GetBinContent(1)))*(hl_heavy->Integral()));
      countSignal115.push_back(ZeeL*((double)(DYxsec.at(1)/Count->GetBinContent(1)))*(hl_signal->Integral()));
      
      if(bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+3)>0)      e_countLightCC.push_back(countLightCC.at(bkgFileList.size()+signalFileList.size()+3)/TMath::Sqrt(bareCountLightCC.at(bkgFileList.size()+signalFileList.size()+3)));
      else  e_countLightCC.push_back(0);
      if(bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+3)>0)      e_countTTbarCC.push_back(countTTbarCC.at(bkgFileList.size()+signalFileList.size()+3)/TMath::Sqrt(bareCountTTbarCC.at(bkgFileList.size()+signalFileList.size()+3)));
      else  e_countTTbarCC.push_back(0);
      if(bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+3)>0)      e_countHeavyCC.push_back(countHeavyCC.at(bkgFileList.size()+signalFileList.size()+3)/TMath::Sqrt(bareCountHeavyCC.at(bkgFileList.size()+signalFileList.size()+3)));
      else  e_countHeavyCC.push_back(0);
      if(bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+3)>0)      e_countSignal115.push_back(countSignal115.at(bkgFileList.size()+signalFileList.size()+3)/TMath::Sqrt(bareCountSignal115.at(bkgFileList.size()+signalFileList.size()+3)));
      else  e_countSignal115.push_back(0);


      if(rizziSysDYB){
	rizzySysErr=0.5;
	e_countLightCC.at(3+bkgFileList.size()+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countLightCC.at(3+bkgFileList.size()+signalFileList.size()),2) + TMath::Power( rizziSysErr*countLightCC.at(3+bkgFileList.size()+signalFileList.size()),2));
	e_countTTbarCC.at(3+bkgFileList.size()+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countTTbarCC.at(3+bkgFileList.size()+signalFileList.size()),2) + TMath::Power( rizziSysErr*countTTbarCC.at(3+bkgFileList.size()+signalFileList.size()),2));
	e_countHeavyCC.at(3+bkgFileList.size()+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countHeavyCC.at(3+bkgFileList.size()+signalFileList.size()),2) + TMath::Power( rizziSysErr*countHeavyCC.at(3+bkgFileList.size()+signalFileList.size()),2));
	e_countSignal115.at(3+bkgFileList.size()+signalFileList.size()) = TMath::Sqrt( TMath::Power(e_countSignal115.at(3+bkgFileList.size()+signalFileList.size()),2) + TMath::Power( rizziSysErr*countSignal115.at(3+bkgFileList.size()+signalFileList.size()),2));
      }

      std::cout << "Integral light = " << countLightCC.at(3+bkgFileList.size()+signalFileList.size()) << " +- " << e_countLightCC.at(3+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral ttbar = " << countTTbarCC.at(3+bkgFileList.size()+signalFileList.size()) << " +- " << e_countTTbarCC.at(3+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral heavy = " << countHeavyCC.at(3+bkgFileList.size()+signalFileList.size()) << " +- " << e_countHeavyCC.at(3+bkgFileList.size()+signalFileList.size()) << std::endl;
      std::cout << "Integral signal = " << countSignal115.at(3+bkgFileList.size()+signalFileList.size()) << " +- " << e_countSignal115.at(3+bkgFileList.size()+signalFileList.size()) << std::endl;

    }

  }
  
  //Data
  for(unsigned int iFile = 0; iFile<dataFileList.size();iFile++){
    dataFileList.at(iFile)->cd();
    std::cout << "Sample = " << dataFileList.at(iFile)->GetName() << std::endl;

    bareCountLightCC.push_back((tree->Draw("H.Pt>>h_light", LightCC_cutString, "goff")));
    bareCountTTbarCC.push_back((tree->Draw("H.Pt>>h_ttbar", TTbarCC_cutString, "goff")));
    bareCountHeavyCC.push_back((tree->Draw("H.Pt>>h_heavy", HeavyCC_cutString, "goff")));
    bareCountSignal115.push_back((tree->Draw("H.Pt>>h_signal", Signal115_cutString, "goff")));

    h_light = (TH1D*)gDirectory->Get("h_light");
    h_ttbar = (TH1D*)gDirectory->Get("h_ttbar");
    h_heavy = (TH1D*)gDirectory->Get("h_heavy");
    h_signal = (TH1D*)gDirectory->Get("h_signal");

    e_countLightCC.push_back(TMath::Sqrt(bareCountLightCC.at(iFile+4+bkgFileList.size()+signalFileList.size())));
    e_countTTbarCC.push_back(TMath::Sqrt(bareCountTTbarCC.at(iFile+4+bkgFileList.size()+signalFileList.size())));
    e_countHeavyCC.push_back(TMath::Sqrt(bareCountHeavyCC.at(iFile+4+bkgFileList.size()+signalFileList.size())));
    e_countSignal115.push_back(TMath::Sqrt(bareCountSignal115.at(iFile+4+bkgFileList.size()+signalFileList.size())));

    std::cout << "Entries from cut string light = " << bareCountLightCC.at(iFile+4+bkgFileList.size()+signalFileList.size()) << " +- " << e_countLightCC.at(iFile+4+bkgFileList.size()+signalFileList.size())<< std::endl;
    std::cout << "Entries from cut string ttbar = " << bareCountTTbarCC.at(iFile+4+bkgFileList.size()+signalFileList.size()) << " +- " << e_countTTbarCC.at(iFile+4+bkgFileList.size()+signalFileList.size())<< std::endl;
    std::cout << "Entries from cut string heavy = " << bareCountHeavyCC.at(iFile+4+bkgFileList.size()+signalFileList.size()) << " +- " << e_countHeavyCC.at(iFile+4+bkgFileList.size()+signalFileList.size())<< std::endl;
    std::cout << "Entries from cut string signal = " << bareCountSignal115.at(iFile+4+bkgFileList.size()+signalFileList.size()) << " +- " << e_countSignal115.at(iFile+4+bkgFileList.size()+signalFileList.size())<< std::endl;

    countLightCCData += bareCountLightCC.at(iFile+4+bkgFileList.size()+signalFileList.size());
    countTTbarCCData += bareCountTTbarCC.at(iFile+4+bkgFileList.size()+signalFileList.size());
    countHeavyCCData += bareCountHeavyCC.at(iFile+4+bkgFileList.size()+signalFileList.size());
    countSignal115Data += bareCountSignal115.at(iFile+4+bkgFileList.size()+signalFileList.size());

  }

  std::vector<double> rel_countLightCC,rel_countTTbarCC,rel_countHeavyCC, rel_countSignal115;
  //create relative errors
  for( int i = 0; i < countLightCC.size() ;i++){
    if( countLightCC.at(i) > 0 )  rel_countLightCC.push_back( e_countLightCC.at(i)/countLightCC.at(i) );
    else  rel_countLightCC.push_back( 0 );
    if( countTTbarCC.at(i) > 0 )  rel_countTTbarCC.push_back( e_countTTbarCC.at(i)/countTTbarCC.at(i) );
    else  rel_countTTbarCC.push_back( 0 );
    if( countHeavyCC.at(i) > 0 )  rel_countHeavyCC.push_back( e_countHeavyCC.at(i)/countHeavyCC.at(i) );
    else  rel_countHeavyCC.push_back( 0 );
    if( countSignal115.at(i) > 0 )  rel_countSignal115.push_back( e_countSignal115.at(i)/countSignal115.at(i) );
    else  rel_countSignal115.push_back( 0 );

    //count the total MC
    countLightCCTotal += countLightCC.at(i);
    countTTbarCCTotal += countTTbarCC.at(i);
    countHeavyCCTotal += countHeavyCC.at(i);
    countSignal115Total += countSignal115.at(i);

    errorLightCCTotal += TMath::Power(e_countLightCC.at(i),2);
    errorTTbarCCTotal += TMath::Power(e_countTTbarCC.at(i),2);
    errorHeavyCCTotal += TMath::Power(e_countHeavyCC.at(i),2);
    errorSignal115Total += TMath::Power(e_countSignal115.at(i),2);
  }

  errorLightCCTotal = TMath::Sqrt(errorLightCCTotal);
  errorTTbarCCTotal = TMath::Sqrt(errorTTbarCCTotal);
  errorHeavyCCTotal = TMath::Sqrt(errorHeavyCCTotal);
  errorSignal115Total = TMath::Sqrt(errorSignal115Total);

  errorLightCCData = TMath::Sqrt(countLightCCData);
  errorTTbarCCData = TMath::Sqrt(countTTbarCCData);
  errorHeavyCCData = TMath::Sqrt(countHeavyCCData);
  errorSignal115Data = TMath::Sqrt(countSignal115Data);


  //countLightCC control region
  countLightCCDYL = countLightCC.at(signalFileList.size()+bkgFileList.size()) + countLightCC.at(signalFileList.size()+bkgFileList.size() + 2);
  countLightCCDYB = countLightCC.at(signalFileList.size()+bkgFileList.size() + 1) + countLightCC.at(signalFileList.size()+bkgFileList.size() + 3);
  countLightCCTTbar = countLightCC.at(signalFileList.size()); // ttbar is the first of bkgFileList
  countLightCCVV = countLightCC.at(signalFileList.size()+1) + countLightCC.at(signalFileList.size()+2) + countLightCC.at(signalFileList.size()+3); 
  countLightCCSignal = countLightCC.at(0); // signal is the first
  countLightCCWJETS = countLightCC.at(signalFileList.size()+4);
  for(int i = signalFileList.size()+5; i < signalFileList.size()+bkgFileList.size(); ++i)  countLightCCSingleTop += countLightCC.at(i);
  countLightCCRest = countLightCCData - countLightCCVV - countLightCCWJETS - countLightCCSingleTop;
  //errors
  errorLightCCDYL = TMath::Sqrt( TMath::Power(e_countLightCC.at(signalFileList.size()+bkgFileList.size()),2) 
				 + TMath::Power(e_countLightCC.at(signalFileList.size()+bkgFileList.size() + 2),2) );
  errorLightCCDYB = TMath::Sqrt( TMath::Power(e_countLightCC.at(signalFileList.size()+bkgFileList.size() + 1),2)
				 + TMath::Power(e_countLightCC.at(signalFileList.size()+bkgFileList.size() + 3),2));
  errorLightCCTTbar = e_countLightCC.at(signalFileList.size()); // ttbar is the first of bkgFileList
  errorLightCCVV = TMath::Sqrt( TMath::Power(e_countLightCC.at(signalFileList.size()+1),2)
				+ TMath::Power(e_countLightCC.at(signalFileList.size()+2),2) 
				+ TMath::Power(e_countLightCC.at(signalFileList.size()+3),2) ); 
  errorLightCCSignal = e_countLightCC.at(0); // signal is the first
  errorLightCCWJETS = e_countLightCC.at(signalFileList.size()+4);
  for(int i = signalFileList.size()+5; i < signalFileList.size()+bkgFileList.size(); ++i) errorLightCCSingleTop += TMath::Power(e_countLightCC.at(i),2);
  errorLightCCSingleTop = TMath::Sqrt(errorLightCCSingleTop);
  errorLightCCRest =  TMath::Sqrt(  TMath::Power( errorLightCCVV,2 ) 
				    + TMath::Power( errorLightCCData,2 ) 
				    + TMath::Power( errorLightCCSingleTop,2 ) 
				    + TMath::Power( errorLightCCWJETS,2 )  );
  //adding the systematics of 30% on singletop and VV
  if(addSystematics){
    errorLightCCVV = TMath::Sqrt(TMath::Power(errorLightCCVV,2)+TMath::Power(0.3*countLightCCVV,2));
    errorLightCCSingleTop = TMath::Sqrt(TMath::Power(errorLightCCSingleTop,2)+TMath::Power(0.3*countLightCCSingleTop,2));
  }



  //countTTbarCC control region
  countTTbarCCDYL = countTTbarCC.at(signalFileList.size()+bkgFileList.size()) + countTTbarCC.at(signalFileList.size()+bkgFileList.size() + 2);
  countTTbarCCDYB = countTTbarCC.at(signalFileList.size()+bkgFileList.size() + 1) + countTTbarCC.at(signalFileList.size()+bkgFileList.size() + 3);
  countTTbarCCTTbar = countTTbarCC.at(signalFileList.size()); // ttbar is the first of bkgFileList
  countTTbarCCVV = countTTbarCC.at(signalFileList.size()+1) + countTTbarCC.at(signalFileList.size()+2) + countTTbarCC.at(signalFileList.size()+3); 
  countTTbarCCSignal = countTTbarCC.at(0); // signal is the first
  countTTbarCCWJETS = countTTbarCC.at(signalFileList.size()+4);
  for(int i = signalFileList.size()+5; i < signalFileList.size()+bkgFileList.size(); ++i)  countTTbarCCSingleTop += countTTbarCC.at(i);
  countTTbarCCRest = countTTbarCCData - countTTbarCCVV - countTTbarCCWJETS - countTTbarCCSingleTop;
  //errors
  errorTTbarCCDYL = TMath::Sqrt( TMath::Power(e_countTTbarCC.at(signalFileList.size()+bkgFileList.size()),2) 
				 + TMath::Power(e_countTTbarCC.at(signalFileList.size()+bkgFileList.size() + 2),2) );
  errorTTbarCCDYB = TMath::Sqrt( TMath::Power(e_countTTbarCC.at(signalFileList.size()+bkgFileList.size() + 1),2)
				 + TMath::Power(e_countTTbarCC.at(signalFileList.size()+bkgFileList.size() + 3),2));
  errorTTbarCCTTbar = e_countTTbarCC.at(signalFileList.size()); // ttbar is the first of bkgFileList
  errorTTbarCCVV = TMath::Sqrt( TMath::Power(e_countTTbarCC.at(signalFileList.size()+1),2)
				+ TMath::Power(e_countTTbarCC.at(signalFileList.size()+2),2) 
				+ TMath::Power(e_countTTbarCC.at(signalFileList.size()+3),2) ); 
  errorTTbarCCSignal = e_countTTbarCC.at(0); // signal is the first
  errorTTbarCCWJETS = e_countTTbarCC.at(signalFileList.size()+4);
  for(int i = signalFileList.size()+5; i < signalFileList.size()+bkgFileList.size(); ++i)  errorTTbarCCSingleTop += TMath::Power(e_countTTbarCC.at(i),2);
  errorTTbarCCSingleTop = TMath::Sqrt(errorTTbarCCSingleTop);
  errorTTbarCCRest =  TMath::Sqrt(  TMath::Power( errorTTbarCCVV,2 ) 
				    + TMath::Power( errorTTbarCCData,2 ) 
				    + TMath::Power( errorTTbarCCSingleTop,2 ) 
				    + TMath::Power( errorTTbarCCWJETS,2 )  );
  //adding the systematics of 30% on singletop and VV
  if(addSystematics){
    errorTTbarCCVV = TMath::Sqrt(TMath::Power(errorTTbarCCVV,2)+TMath::Power(0.3*countTTbarCCVV,2));
    errorTTbarCCSingleTop = TMath::Sqrt(TMath::Power(errorTTbarCCSingleTop,2)+TMath::Power(0.3*countTTbarCCSingleTop,2));
  }


  //countHeavyCC control region
  countHeavyCCDYL = countHeavyCC.at(signalFileList.size()+bkgFileList.size()) + countHeavyCC.at(signalFileList.size()+bkgFileList.size() + 2);
  countHeavyCCDYB = countHeavyCC.at(signalFileList.size()+bkgFileList.size() + 1) + countHeavyCC.at(signalFileList.size()+bkgFileList.size() + 3);
  countHeavyCCTTbar = countHeavyCC.at(signalFileList.size()); // ttbar is the first of bkgFileList
  countHeavyCCVV = countHeavyCC.at(signalFileList.size()+1) + countHeavyCC.at(signalFileList.size()+2) + countHeavyCC.at(signalFileList.size()+3); 
  countHeavyCCSignal = countHeavyCC.at(0); // signal is the first
  countHeavyCCWJETS = countHeavyCC.at(signalFileList.size()+4);
  for(int i = signalFileList.size()+5; i < signalFileList.size()+bkgFileList.size(); ++i)  countHeavyCCSingleTop += countHeavyCC.at(i);
  countHeavyCCRest = countHeavyCCData - countHeavyCCVV - countHeavyCCWJETS - countHeavyCCSingleTop;
  //errors
  errorHeavyCCDYL = TMath::Sqrt( TMath::Power(e_countHeavyCC.at(signalFileList.size()+bkgFileList.size()),2) 
				 + TMath::Power(e_countHeavyCC.at(signalFileList.size()+bkgFileList.size() + 2),2) );
  errorHeavyCCDYB = TMath::Sqrt( TMath::Power(e_countHeavyCC.at(signalFileList.size()+bkgFileList.size() + 1),2)
				 + TMath::Power(e_countHeavyCC.at(signalFileList.size()+bkgFileList.size() + 3),2));
  errorHeavyCCTTbar = e_countHeavyCC.at(signalFileList.size()); // ttbar is the first of bkgFileList
  errorHeavyCCVV = TMath::Sqrt( TMath::Power(e_countHeavyCC.at(signalFileList.size()+1),2)
				+ TMath::Power(e_countHeavyCC.at(signalFileList.size()+2),2) 
				+ TMath::Power(e_countHeavyCC.at(signalFileList.size()+3),2) ); 
  errorHeavyCCSignal = e_countHeavyCC.at(0); // signal is the first
  errorHeavyCCWJETS = e_countHeavyCC.at(signalFileList.size()+4);
  for(int i = signalFileList.size()+5; i < signalFileList.size()+bkgFileList.size(); ++i)  errorHeavyCCSingleTop += TMath::Power(e_countHeavyCC.at(i),2);
  errorHeavyCCSingleTop = TMath::Sqrt(errorHeavyCCSingleTop);
  errorHeavyCCRest =  TMath::Sqrt(  TMath::Power( errorHeavyCCVV,2 ) 
				    + TMath::Power( errorHeavyCCData,2 ) 
				    + TMath::Power( errorHeavyCCSingleTop,2 ) 
				    + TMath::Power( errorHeavyCCWJETS,2 )  );
  //adding the systematics of 30% on singletop and VV
  if(addSystematics){
    errorHeavyCCVV = TMath::Sqrt(TMath::Power(errorHeavyCCVV,2)+TMath::Power(0.3*countHeavyCCVV,2));
    errorHeavyCCSingleTop = TMath::Sqrt(TMath::Power(errorHeavyCCSingleTop,2)+TMath::Power(0.3*countHeavyCCSingleTop,2));
  }



  //countSignal115 control region
  countSignal115DYL = countSignal115.at(signalFileList.size()+bkgFileList.size()) + countSignal115.at(signalFileList.size()+bkgFileList.size() + 2);
  countSignal115DYB = countSignal115.at(signalFileList.size()+bkgFileList.size() + 1) + countSignal115.at(signalFileList.size()+bkgFileList.size() + 3);
  countSignal115TTbar = countSignal115.at(signalFileList.size()); // ttbar is the first of bkgFileList
  countSignal115VV = countSignal115.at(signalFileList.size()+1) + countSignal115.at(signalFileList.size()+2) + countSignal115.at(signalFileList.size()+3); 
  countSignal115Signal = countSignal115.at(0); // signal is the first
  countSignal115WJETS = countSignal115.at(signalFileList.size()+4);
  for(int i = signalFileList.size()+5; i < signalFileList.size()+bkgFileList.size(); ++i)  countSignal115SingleTop += countSignal115.at(i);
  countSignal115Rest = countSignal115Data - countSignal115VV - countSignal115WJETS - countSignal115SingleTop;
  //errors
  errorSignal115DYL = TMath::Sqrt( TMath::Power(e_countSignal115.at(signalFileList.size()+bkgFileList.size()),2) 
				 + TMath::Power(e_countSignal115.at(signalFileList.size()+bkgFileList.size() + 2),2) );
  errorSignal115DYB = TMath::Sqrt( TMath::Power(e_countSignal115.at(signalFileList.size()+bkgFileList.size() + 1),2)
				 + TMath::Power(e_countSignal115.at(signalFileList.size()+bkgFileList.size() + 3),2));
  errorSignal115TTbar = e_countSignal115.at(signalFileList.size()); // ttbar is the first of bkgFileList
  errorSignal115VV = TMath::Sqrt( TMath::Power(e_countSignal115.at(signalFileList.size()+1),2)
				+ TMath::Power(e_countSignal115.at(signalFileList.size()+2),2) 
				+ TMath::Power(e_countSignal115.at(signalFileList.size()+3),2) ); 
  errorSignal115Signal = e_countSignal115.at(0); // signal is the first
  errorSignal115WJETS = e_countSignal115.at(signalFileList.size()+4);
  for(int i = signalFileList.size()+5; i < signalFileList.size()+bkgFileList.size(); ++i)  errorSignal115SingleTop += TMath::Power(e_countSignal115.at(i),2);
  errorSignal115SingleTop = TMath::Sqrt(errorSignal115SingleTop);
  errorSignal115Rest =  TMath::Sqrt(  TMath::Power( errorSignal115VV,2 ) 
				    + TMath::Power( errorSignal115Data,2 ) 
				    + TMath::Power( errorSignal115SingleTop,2 ) 
				    + TMath::Power( errorSignal115WJETS,2 )  );
  //adding the systematics of 30% on singletop and VV
  if(addSystematics){
    errorSignal115VV = TMath::Sqrt(TMath::Power(errorSignal115VV,2)+TMath::Power(0.3*countSignal115VV,2));
    errorSignal115SingleTop = TMath::Sqrt(TMath::Power(errorSignal115SingleTop,2)+TMath::Power(0.3*countSignal115SingleTop,2));
  }





  //SYSTEM METHOD
  int nVars = 3;  
  
  Double_t d_light[] = { (double)(countLightCCDYL), (double)(countTTbarCCDYL), (double)(countHeavyCCDYL) };
  Double_t d_ttbar[] = { (double)(countLightCCTTbar), (double)(countTTbarCCTTbar), (double)(countHeavyCCTTbar) };
  Double_t d_heavy[] = { (double)(countLightCCDYB), (double)(countTTbarCCDYB), (double)(countHeavyCCDYB) };
  Double_t d_rest[] = { (double)(countLightCCRest), (double)(countTTbarCCRest), (double)(countHeavyCCRest) };
  
  Double_t e_light[] = { (double)(errorLightCCDYL), (double)(errorTTbarCCDYL), (double)(errorHeavyCCDYL) };
  Double_t e_ttbar[] = { (double)(errorLightCCTTbar), (double)(errorTTbarCCTTbar), (double)(errorHeavyCCTTbar) };
  Double_t e_heavy[] = { (double)(errorLightCCDYB), (double)(errorTTbarCCDYB), (double)(errorHeavyCCDYB) };
  Double_t e_rest[] = { (double)(errorLightCCRest), (double)(errorTTbarCCRest), (double)(errorHeavyCCRest) };
  
  TVectorD v_light; v_light.Use(3,d_light);
  TVectorD v_ttbar; v_ttbar.Use(3,d_ttbar);
  TVectorD v_heavy; v_heavy.Use(3,d_heavy);
  TVectorD v_rest; v_rest.Use(3,d_rest);
  
  TMatrixD M_A(3,3);
  TMatrixDColumn(M_A,0) = v_light;
  TMatrixDColumn(M_A,1) = v_ttbar;
  TMatrixDColumn(M_A,2) = v_heavy;
  
  std::cout << "Matrix elements" << std::endl;
  std::cout << " | " << M_A(0,0) << " | " << M_A(1,0) << " | " << M_A(2,0) << " | " << std::endl;
  std::cout << " | " << M_A(0,1) << " | " << M_A(1,1) << " | " << M_A(2,1) << " | "<< std::endl;
  std::cout << " | " << M_A(0,2) << " | " << M_A(1,2) << " | " << M_A(2,2) << " | "<< std::endl;
  
  
  std::cout << "Counting" << std::endl;
  std::cout << "countLightCCDYL = " << (double)v_light[0] <<  std::endl;
  std::cout << "countTTbarCCDYL = " << (double)v_light[1] <<  std::endl;
  std::cout << "countHeavyCCDYL = " << (double)v_light[2] <<  std::endl;
  
  std::cout << "countLightCCTTbar  = " << (double)v_ttbar[0] <<  std::endl;
  std::cout << "countTTbarCCTTbar  = " << (double)v_ttbar[1] <<  std::endl;
  std::cout << "countHeavyCCTTbar  = " << (double)v_ttbar[2] <<  std::endl;
  
  std::cout << "countLightCCDYB  = " << (double)v_heavy[0] << std::endl;
  std::cout << "countTTbarCCDYB  = " << (double)v_heavy[1] << std::endl;
  std::cout << "countHeavyCCDYB  = " << (double)v_heavy[2] << std::endl;
  
  std::cout << "countLightCCRest  = " << (double)v_rest[0] << std::endl;
  std::cout << "countTTbarCCRest  = " << (double)v_rest[1] << std::endl;
  std::cout << "countHeavyCCRest  = " << (double)v_rest[2] << std::endl;
  
  std::cout << "countSignal115DYL  = " << (double)countSignal115DYL << std::endl;
  std::cout << "countSignal115TTbar  = " << (double)countSignal115TTbar << std::endl;
  std::cout << "countSignal115DYB  = " << (double)countSignal115DYB << std::endl;
  std::cout << "countSignal115VV  = " << (double)countSignal115VV << std::endl;
  std::cout << "countSignal115ST  = " << (double)countSignal115SingleTop << std::endl;


  
  std::cout << "Errors" << std::endl;
  std::cout << "errorLightCCDYL = " << (double)e_light[0] <<  std::endl;
  std::cout << "errorTTbarCCDYL = " << (double)e_light[1] <<  std::endl;
  std::cout << "errorHeavyCCDYL = " << (double)e_light[2] <<  std::endl;
  
  std::cout << "errorLightCCTTbar  = " << (double)e_ttbar[0] <<  std::endl;
  std::cout << "errorTTbarCCTTbar  = " << (double)e_ttbar[1] <<  std::endl;
  std::cout << "errorHeavyCCTTbar  = " << (double)e_ttbar[2] <<  std::endl;
  
  std::cout << "errorLightCCDYB  = " << (double)e_heavy[0] << std::endl;
  std::cout << "errorTTbarCCDYB  = " << (double)e_heavy[1] << std::endl;
  std::cout << "errorHeavyCCDYB  = " << (double)e_heavy[2] << std::endl;
  
  std::cout << "errorLightCCRest  = " << (double)e_rest[0] << std::endl;
  std::cout << "errorTTbarCCRest  = " << (double)e_rest[1] << std::endl;
  std::cout << "errorHeavyCCRest  = " << (double)e_rest[2] << std::endl;

  std::cout << "errorSignal115DYL  = " << (double)errorSignal115DYL << std::endl;
  std::cout << "errorSignal115TTbar  = " << (double)errorSignal115TTbar << std::endl;
  std::cout << "errorSignal115DYB  = " << (double)errorSignal115DYB << std::endl;
  std::cout << "errorSignal115VV  = " << (double)errorSignal115VV << std::endl;
  std::cout << "errorSignal115ST  = " << (double)errorSignal115SingleTop << std::endl;

  
  
  //    TVectorD v_SF = NormalEqn(M_A,v_rest);
  
  bool ok = true;
  TDecompSVD svd(M_A);
  TVectorD v_SF = svd.Solve(v_rest, ok);
  
  std::cout << "system results" << std::endl;
  std::cout << "Light SF = " << (double)v_SF[0] <<  std::endl;
  std::cout << "TTbar SF = " << (double)v_SF[1] <<  std::endl;
  std::cout << "Heavy SF = " << (double)v_SF[2] << std::endl;
  

  Double_t scaleFactorLight = 0;
  scaleFactorLight = 0.952465;
  Double_t eScaleFactorLight = 0;
  eScaleFactorLight = 0.;
  Double_t scaleFactorTTbar = 0;
  scaleFactorTTbar = 1.08814;
  Double_t eScaleFactorTTbar = 0;
  eScaleFactorTTbar = 0.0619997;
  Double_t scaleFactorHeavy = 0;
  scaleFactorHeavy = 1.30314;
  Double_t eScaleFactorHeavy = 0;
  eScaleFactorHeavy = 0.160399;

  Double_t scaleFactor = 0;
  Double_t diff = 0;
  Double_t ediff = 0;
  Double_t erdiff = 0;
  Double_t purity = 0;
  Double_t epurity = 0;

  std::cout << "For Light Region " << std::endl;
  diff = (countLightCCData - countLightCCTotal);
  ediff = TMath::Sqrt( TMath::Power(errorLightCCData,2) + TMath::Power(errorLightCCTotal,2) );
  std::cout << "Diff += ErDiff = " << diff << " += " << ediff << std::endl;
  if(TMath::Abs(diff) > 0)
    erdiff = ediff/diff;
  if( diff < 0 )
    scaleFactorLight = 1 - TMath::Abs(diff/countLightCCDYL);
  else
    scaleFactorLight = 1 + TMath::Abs(diff/countLightCCDYL);
  eScaleFactorLight = TMath::Sqrt(TMath::Power(errorLightCCData/countLightCCTotal,2) + TMath::Power(errorLightCCTotal*diff/(countLightCCTotal*countLightCCTotal),2));
  std::cout << "Scale factor light before systematics = " << scaleFactorLight << " pm " << eScaleFactorLight << std::endl;

  purity = countLightCCDYL/countLightCCTotal;
  ePurity = purity * TMath::Sqrt( TMath::Power(errorLightCCDYL/countLightCCDYL,2) + TMath::Power(errorLightCCTotal/countLightCCTotal,2) );

  if(systematicsFromPurity)  //systematics from purity
    eScaleFactorLight = TMath::Sqrt( TMath::Power(eScaleFactorLight,2) + TMath::Power((0.5*(1-purity)*scaleFactorLight),2) );
  std::cout << "Scale factor light = " << scaleFactorLight << " pm " << eScaleFactorLight << std::endl;

  std::cout << "  \\begin{table}[t]" << std::endl;
  std::cout << "	\\caption{LightControl\\label{tab:Cutflow}}" << std::endl;
  std::cout << "  \\vspace{0.4cm}" << std::endl;
  std::cout << "  \\begin{center}" << std::endl;
  std::cout << "  \\begin{tabular}{c|c} \\hline" << std::endl;
  std::cout << "	Dataset&Z(ee)H\\\\\\hline \\hline" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "  $W+\\textrm{jets}$&$"<< countLightCCWJETS<<" \\pm " << errorLightCCWJETS << "$\\\\" << std::endl;
  std::cout << "  WW, WZ, ZZ&$"<< countLightCCVV <<" \\pm "<< errorLightCCVV <<"$\\\\" << std::endl;
  std::cout << "	$t\\bar{t}$+jets&$"<< countLightCCTTbar <<" \\pm "<< errorLightCCTTbar <<"$\\\\" << std::endl;
  std::cout << "  $Z + udscg$&$"<< countLightCCDYL <<" \\pm "<< errorLightCCDYL <<"$\\\\" << std::endl;
  std::cout << "	$Z + b\\bar{b}$&$"<< countLightCCDYB <<" \\pm "<< errorLightCCDYB <<"$\\\\\\hline " << std::endl;
  std::cout << "  Sum MC&$" << countLightCCTotal <<" \\pm "<< errorLightCCTotal <<"$\\\\\\hline " << std::endl;
  std::cout << "  Data&$" << countLightCCData <<" \\pm "<< errorLightCCData <<"$\\\\\\hline " << std::endl;
  std::cout << "	ZH(115 GeV)&$"<< countLightCCSignal <<" \\pm "<< errorLightCCSignal <<"$\\\\\\hline " << std::endl;
  std::cout << "	Purity&$"<< purity <<" \\pm " << ePurity << " $\\\\\\hline " << std::endl;
  std::cout << "	Scale Factor&$"<< scaleFactorLight <<" \\pm "<< eScaleFactorLight <<" $\\\\\\hline " << std::endl;
  std::cout << "	\\end{tabular}" << std::endl;
  std::cout << "  \\end{center}" << std::endl;
  std::cout << "  \\end{table}" << std::endl;

  scaleFactor = 0;
  diff = 0;

  if( rizziSysTTbar == false ){
    scaleFactorLight = 0.994;
    eScaleFactorLght = 0.020;
  }

  std::cout << "For TTbar Region " << std::endl;
  countTTbarCCDYL *= scaleFactorLight;
  errorTTbarCCDYL = countTTbarCCDYL * TMath::Sqrt( TMath::Power( eScaleFactorLight/scaleFactorLight ,2) + TMath::Power( errorTTbarCCDYL/countTTbarCCDYL ,2) );

  diff = (countTTbarCCData - countTTbarCCTotal);
  ediff = TMath::Sqrt( TMath::Power(errorTTbarCCData,2) + TMath::Power(errorTTbarCCTotal,2) );
  if(TMath::Abs(diff) > 0)
    erdiff = ediff/diff;
  if( diff < 0 )
    scaleFactorTTbar = 1 - TMath::Abs(diff/countTTbarCCTTbar);
  else
    scaleFactorTTbar = 1 + TMath::Abs(diff/countTTbarCCTTbar);
  eScaleFactorTTbar = TMath::Sqrt(TMath::Power(errorTTbarCCData/countTTbarCCTotal,2) + TMath::Power(errorTTbarCCTotal*diff/(countTTbarCCTotal*countTTbarCCTotal),2));

  purity = countTTbarCCTTbar/countTTbarCCTotal;
  ePurity = purity * TMath::Sqrt( TMath::Power(errorTTbarCCTTbar/countTTbarCCTTbar,2) + TMath::Power(errorTTbarCCTotal/countTTbarCCTotal,2) );

  //systematics from purity
  if(systematicsFromPurity)  
    eScaleFactorTTbar = TMath::Sqrt( TMath::Power(eScaleFactorTTbar,2) + TMath::Power(0.5*(1-purity)*scaleFactorTTbar,2) );
  std::cout << "Scale factor ttbar = " << scaleFactorTTbar << " pm " << eScaleFactorTTbar<< std::endl;

  std::cout << "  \\begin{table}[t]" << std::endl;
  std::cout << "	\\caption{TTbarControl\\label{tab:Cutflow}}" << std::endl;
  std::cout << "  \\vspace{0.4cm}" << std::endl;
  std::cout << "  \\begin{center}" << std::endl;
  std::cout << "  \\begin{tabular}{c|c} \\hline" << std::endl;
  std::cout << "	Dataset&Z(ee)H\\\\\\hline \\hline" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "  $W+\\textrm{jets}$&$"<< countTTbarCCWJETS<<" \\pm " << errorTTbarCCWJETS << "$\\\\" << std::endl;
  std::cout << "  WW, WZ, ZZ&$"<< countTTbarCCVV <<" \\pm "<< errorTTbarCCVV <<"$\\\\" << std::endl;
  std::cout << "	$t\\bar{t}$+jets&$"<< countTTbarCCTTbar <<" \\pm "<< errorTTbarCCTTbar <<"$\\\\" << std::endl;
  std::cout << "  $Z + udscg$&$"<< countTTbarCCDYL <<" \\pm "<< errorTTbarCCDYL <<"$\\\\" << std::endl;
  std::cout << "	$Z + b\\bar{b}$&$"<< countTTbarCCDYB <<" \\pm "<< errorTTbarCCDYB <<"$\\\\\\hline " << std::endl;
  std::cout << "  Sum MC&$" << countTTbarCCTotal <<" \\pm "<< errorTTbarCCTotal <<"$\\\\\\hline " << std::endl;
  std::cout << "  Data&$" << countTTbarCCData <<" \\pm "<< errorTTbarCCData <<"$\\\\\\hline " << std::endl;
  std::cout << "	ZH(115 GeV)&$"<< countTTbarCCSignal <<" \\pm "<< errorTTbarCCSignal <<"$\\\\\\hline " << std::endl;
  std::cout << "	Purity&$"<< purity <<" \\pm " << ePurity << " $\\\\\\hline " << std::endl;
  std::cout << "	Scale Factor&$"<< scaleFactorTTbar <<" \\pm "<< eScaleFactorTTbar <<" $\\\\\\hline " << std::endl;
  std::cout << "	\\end{tabular}" << std::endl;
  std::cout << "  \\end{center}" << std::endl;
  std::cout << "  \\end{table}" << std::endl;

  if( rizziSysDYB == false ){
    scaleFactorTTbar = 1.071;
    eScaleFactorTTbar = 0.076;
  }

  scaleFactor = 0;
  diff = 0;
  std::cout << "For Heavy Flavour Region " << std::endl;
  countHeavyCCTTbar *= scaleFactorTTbar;
  errorHeavyCCTTbar = countHeavyCCTTbar * TMath::Sqrt( TMath::Power( eScaleFactorTTbar/scaleFactorTTbar ,2) + TMath::Power( errorHeavyCCTTbar/countHeavyCCTTbar ,2) );

  diff = (countHeavyCCData - countHeavyCCTotal);
  ediff = TMath::Sqrt( TMath::Power(errorHeavyCCData,2) + TMath::Power(errorHeavyCCTotal,2) );
  if(TMath::Abs(diff) > 0)
    erdiff = ediff/diff;
  if( diff < 0 )
    scaleFactorHeavy = 1 - TMath::Abs(diff/countHeavyCCDYB);
  else
    scaleFactorHeavy = 1 + TMath::Abs(diff/countHeavyCCDYB);
  eScaleFactorHeavy = TMath::Sqrt(TMath::Power(errorHeavyCCData/countHeavyCCTotal,2) + TMath::Power(errorHeavyCCTotal*diff/(countHeavyCCTotal*countHeavyCCTotal),2));

  purity = countHeavyCCDYB/countHeavyCCTotal;
  ePurity = purity * TMath::Sqrt( TMath::Power(errorHeavyCCDYB/countHeavyCCDYB,2) + TMath::Power(errorHeavyCCTotal/countHeavyCCTotal,2) );

  //systematics from purity
  if(systematicsFromPurity == true)
    eScaleFactorHeavy = TMath::Sqrt( TMath::Power(eScaleFactorHeavy,2) + TMath::Power(0.5*(1-purity)*scaleFactorHeavy,2) );
  std::cout << "Scale factor heavy = " << scaleFactorHeavy << " pm " << eScaleFactorHeavy << std::endl;

  std::cout << "  \\begin{table}[t]" << std::endl;
  std::cout << "	\\caption{TTbarControl\\label{tab:Cutflow}}" << std::endl;
  std::cout << "  \\vspace{0.4cm}" << std::endl;
  std::cout << "  \\begin{center}" << std::endl;
  std::cout << "  \\begin{tabular}{c|c} \\hline" << std::endl;
  std::cout << "	Dataset&Z(ee)H\\\\\\hline \\hline" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "  $W+\\textrm{jets}$&$"<< countHeavyCCWJETS<<" \\pm " << errorHeavyCCWJETS << "$\\\\" << std::endl;
  std::cout << "  WW, WZ, ZZ&$"<< countHeavyCCVV <<" \\pm "<< errorHeavyCCVV <<"$\\\\" << std::endl;
  std::cout << "	$t\\bar{t}$+jets&$"<< countHeavyCCTTbar <<" \\pm "<< errorHeavyCCTTbar <<"$\\\\" << std::endl;
  std::cout << "  $Z + udscg$&$"<< countHeavyCCDYL <<" \\pm "<< errorHeavyCCDYL <<"$\\\\" << std::endl;
  std::cout << "	$Z + b\\bar{b}$&$"<< countHeavyCCDYB <<" \\pm "<< errorHeavyCCDYB <<"$\\\\\\hline " << std::endl;
  std::cout << "  Sum MC&$" << countHeavyCCTotal <<" \\pm "<< errorHeavyCCTotal <<"$\\\\\\hline " << std::endl;
  std::cout << "  Data&$" << countHeavyCCData <<" \\pm "<< errorHeavyCCData <<"$\\\\\\hline " << std::endl;
  std::cout << "	ZH(115 GeV)&$"<< countHeavyCCSignal <<" \\pm "<< errorHeavyCCSignal <<"$\\\\\\hline " << std::endl;
  std::cout << "	Purity&$"<< purity <<" \\pm " << ePurity << " $\\\\\\hline " << std::endl;
  std::cout << "	Scale Factor&$"<< scaleFactorHeavy <<" \\pm "<< eScaleFactorHeavy <<" $\\\\\\hline " << std::endl;
  std::cout << "	\\end{tabular}" << std::endl;
  std::cout << "  \\end{center}" << std::endl;
  std::cout << "  \\end{table}" << std::endl;


  //   scaleFactor = 0;
  //   diff = 0;
  //   std::cout << "For Signal Region " << std::endl;
  //   countDYB *= scaleFactorHeavy;
  //   eDYB = countDYB * TMath::Sqrt( TMath::Power( eScaleFactorHeavy/scaleFactorHeavy ,2) + TMath::Power( erDYB ,2) );
  //   countTotal = countZZ+countWZ+countWW+countTTbar+countDYL+countDYB;
  //   diff = (countData - countTotal);
  //   ediff = TMath::Sqrt( TMath::Power(eData,2) + TMath::Power(eTotal,2) );
  //   if( diff < 0 )
  //     scaleFactor = 1 - TMath::Abs(diff/countDYB);
  //   else
  //     scaleFactor = 1 + TMath::Abs(diff/countDYB);

  //   purity = countSignal/countTotal;
  //   ePurity = purity * TMath::Sqrt( TMath::Power(erSignal,2) + TMath::Power(erTotal,2) );
  //   eScaleFactor = TMath::Sqrt(TMath::Power(eData/countTotal,2) + TMath::Power(eTotal*diff/(countTotal*countTotal),2));
  //   std::cout << "Scale factor heavy flavours = " << scaleFactor << std::endl;

  //   std::cout << "  \\begin{table}[t]" << std::endl;
  //   std::cout << "	\\caption{Signal\\label{tab:Cutflow}}" << std::endl;
  //   std::cout << "  \\vspace{0.4cm}" << std::endl;
  //   std::cout << "  \\begin{center}" << std::endl;
  //   std::cout << "  \\begin{tabular}{c|c} \\hline" << std::endl;
  //   std::cout << "	Dataset&Z(ee)H\\\\\\hline \\hline" << std::endl;
  //   std::cout << "" << std::endl;
  //   std::cout << "  $W+\\textrm{jets}$&$"<< countWJETS<<" \\pm " << eWJETS << "$\\\\" << std::endl;
  //   std::cout << "  WW, WZ, ZZ&$"<< countVV <<" \\pm "<< eVV <<"$\\\\" << std::endl;
  //   std::cout << "	$t\\bar{t}$+jets&$"<< countTTbar <<" \\pm "<< eTTbar <<"$\\\\" << std::endl;
  //   std::cout << "  $Z + udscg$&$"<< countDYL <<" \\pm "<< eDYL <<"$\\\\" << std::endl;
  //   std::cout << "	$Z + b\\bar{b}$&$"<< countDYB <<" \\pm "<< eDYB <<"$\\\\\\hline " << std::endl;
  //   std::cout << "  Sum MC&$" << countTotal <<" \\pm "<< eTotal <<"$\\\\\\hline " << std::endl;
  //   std::cout << "  Data&$" << countData <<" \\pm "<< eData <<"$\\\\\\hline " << std::endl;
  //   std::cout << "	ZH(115 GeV)&$"<< countSignal <<" \\pm "<< eSignal <<"$\\\\\\hline " << std::endl;
  //   std::cout << "	Purity&$"<< purity <<" \\pm " << ePurity << " $\\\\\\hline " << std::endl;
  //   std::cout << "	ScaleFactor&$"<< scaleFactor <<" \\pm "<< eScaleFactor <<" $\\\\\\hline " << std::endl;
  //   std::cout << "	\\end{tabular}" << std::endl;
  //   std::cout << "  \\end{center}" << std::endl;
  //   std::cout << "  \\end{table}" << std::endl;

  //   //signal region
  //   std::cout << " min_mass " << min_mass  << std::endl;
  //   std::cout << " max_mass " << max_mass  << std::endl;
  //   std::cout << " countSignal " << countSignal  << std::endl;
  //   std::cout << " countDYL with SF " << countDYL*scaleFactorLight  << std::endl;
  //   std::cout << " countDYB with SF" << countDYB*scaleFactorHeavy  << std::endl;
  //   std::cout << " countDYBOOSTL with SF" << countDYBOOSTL*scaleFactorLight  << std::endl;
  //   std::cout << " countDYBOOSTB with SF" << countDYBOOSTB*scaleFactorHeavy  << std::endl;
  //   std::cout << " countWJETS " << countWJETS  << std::endl;
  //   std::cout << " countTTbar with SF" << countTTbar*scaleFactorTTbar  << std::endl;
  //   std::cout << " countZZ " << countZZ  << std::endl;
  //   std::cout << " countWZ " << countWZ  << std::endl;
  //   std::cout << " countWW " << countWW  << std::endl;


  return 0;
}


