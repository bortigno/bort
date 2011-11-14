#include "samples.h"

std::vector<Sample> Nov1stDiJetPt(){
  std::vector<Sample> s;
  Double_t ZeeL=215.094+930.228+370.915+662.967;
  Double_t Run2011_May10Rereco_Lumi,Run2011A_PromptRecoV4_Lumi,Run2011A_Aug05ReReco_Lumi,Run2011A_PromptRecoV6_Lumi,Run2011B_PromptRecoV1_Lumi;
  Run2011_May10Rereco_Lumi = 215.094;
  Run2011A_PromptRecoV4_Lumi = 925.660;
  Run2011A_Aug05ReReco_Lumi = 370.915;
  Run2011A_PromptRecoV6_Lumi = 653.973;
  //before 178078
  Run2011B_PromptRecoV1_Lumi = 1358;
  //full range
  //Run2011B_PromptRecoV1_Lumi = 1755;

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov1st/DiJetPt/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Oct30th/DiJetPt/");
  

  s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp.root", kBlue , false ));
 
  s.push_back(Sample(3048,"DY",path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_Fall11.root",kYellow ,false ));
  s.push_back(Sample(30,"DYBOOSTED",path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola_Fall11.root",kYellow ,false ));

  s.push_back(Sample(165,"TTbar",path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola_Fall11.root", kBlue , false ));

  s.push_back(Sample(5.9,"VV",path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola_Fall11.root",kOrange+2 , false ));
  s.push_back(Sample(18.3,"VV",path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola_Fall11.root",kOrange+2 , false ));
  s.push_back(Sample(43,"VV",path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root",kOrange+2 , false ));

  s.push_back(Sample(3.19,"ST",path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola_Fall11.root", kBlue , false ));
  s.push_back(Sample(41.92,"ST",path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root", kBlue , false ));
  s.push_back(Sample(7.87,"ST",path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola_Fall11.root", kBlue , false ));
  
  s.push_back(Sample(1.44,"ST",path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola_Fall11.root", kBlue , false ));
  s.push_back(Sample(22.65,"ST",path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola_Fall11.root", kBlue , false ));
  s.push_back(Sample(7.87,"ST",path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root", kBlue , false ));
  
  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_Fall11.root", kGreen+3, false ));

  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011_May10Rereco.root",0 , true, Run2011_May10Rereco_Lumi ));
  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011A_PromptRecoV4.root",0 , true, Run2011A_PromptRecoV4_Lumi));
  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011A_Aug05ReReco.root",0 , true, Run2011A_Aug05ReReco_Lumi ));
  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011A_PromptRecoV6.root",0 , true, Run2011A_PromptRecoV6_Lumi ));

  s.push_back(Sample(1000,"Run2011B",pathData+"DiJetPt_DoubleElectron_Run2011B_PromptRecoV1.root",0 , true, Run2011B_PromptRecoV1_Lumi ));


  return s;
}

std::vector<Sample> Nov1stDiJetPtUpdated(){
  std::vector<Sample> s;
  Double_t ZeeL=215.094+930.228+370.915+662.967;
  Double_t Run2011_May10Rereco_Lumi,Run2011A_PromptRecoV4_Lumi,Run2011A_Aug05ReReco_Lumi,Run2011A_PromptRecoV6_Lumi,Run2011B_PromptRecoV1_Lumi;
  Run2011_May10Rereco_Lumi = 215.094;
  Run2011A_PromptRecoV4_Lumi = 925.660;
  Run2011A_Aug05ReReco_Lumi = 370.915;
  Run2011A_PromptRecoV6_Lumi = 653.973;
  //before 178078
  Run2011B_PromptRecoV1_Lumi = 1358;
  //full range
  //Run2011B_PromptRecoV1_Lumi = 1755;

  std::string path("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov1st/DiJetPt/");
  std::string pathData("~/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Oct30th/DiJetPt/");
  
/*   s.push_back(Sample(*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.4107*0.704*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
  s.push_back(Sample(0.3598*0.648*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false ));
/*   s.push_back(Sample(0.3158*0.577*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2778*0.493*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
/*   s.push_back(Sample(0.2453*0.403*0.03365*3,"ZH",path+"DiJetPt_ZH_ZToLL_HToBB_M-135_7TeV-powheg-herwigpp_HBB_EDMNtupleV11_1MSignal_ProcV4.root.updated", kBlue , false )); */
 
  s.push_back(Sample(3048,"DY",path+"DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root.updated",kYellow ,false ));
  s.push_back(Sample(30,"DYBOOSTED",path+"DiJetPt_DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola.root.updated",kYellow ,false ));

  s.push_back(Sample(165,"TTbar",path+"DiJetPt_TTJets_TuneZ2_7TeV-madgraph-tauola.root.updated", kBlue , false ));

  s.push_back(Sample(5.9,"VV",path+"DiJetPt_ZZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(18.3,"VV",path+"DiJetPt_WZ_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));
  s.push_back(Sample(43,"VV",path+"DiJetPt_WW_TuneZ2_7TeV_pythia6_tauola.root.updated",kOrange+2 , false ));

  s.push_back(Sample(3.19,"ST",path+"DiJetPt_T_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(41.92,"ST",path+"DiJetPt_T_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(7.87,"ST",path+"DiJetPt_T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  
  s.push_back(Sample(1.44,"ST",path+"DiJetPt_Tbar_TuneZ2_s-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(22.65,"ST",path+"DiJetPt_Tbar_TuneZ2_t-channel_7TeV-powheg-tauola.root.updated", kBlue , false ));
  s.push_back(Sample(7.87,"ST",path+"DiJetPt_Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola.root.updated", kBlue , false ));
  
  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011_May10Rereco.root",0 , true, Run2011_May10Rereco_Lumi ));
  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011A_PromptRecoV4.root",0 , true, Run2011A_PromptRecoV4_Lumi));
  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011A_Aug05ReReco.root",0 , true, Run2011A_Aug05ReReco_Lumi ));
  s.push_back(Sample(1000,"Run2011A",pathData+"DiJetPt_DoubleElectron_Run2011A_PromptRecoV6.root",0 , true, Run2011A_PromptRecoV6_Lumi ));

  s.push_back(Sample(1000,"Run2011B",pathData+"DiJetPt_DoubleElectron_Run2011B_PromptRecoV1.root",0 , true, Run2011B_PromptRecoV1_Lumi ));

  //  s.push_back(Sample(31314,"WJ",path+"DiJetPt_WJetsToLNu_TuneZ2_7TeV-madgraph-tauola.root.updated", kGreen+3, false ));

  return s;
}


std::vector<Sample> samples()
{
  std::vector<Sample> s;

  Double_t ZeeL=215.094+930.228+370.915+662.967;
  //  ZeeL=1143;

  std::string path("/data1/VHbbAnalysis/EDMNtuple_step2/V9/oct9Ntuple/histos/");
  std::string pathData("/data1/VHbbAnalysis/EDMNtuple_step2/V9/oct7Ntuple/histos/");
  // s.push_back(Sample(1000,"data","SingleMu_HBB_EDMNtupleV1_ProcV2_CandV1_may_histos.root",0 , true,219));
  // s.push_back(Sample(1000,"data","SingleMu_HBB_EDMNtupleV1_ProcV2_CandV1_prompt_histos.root",0 , true,789));
  s.push_back(Sample(1000,"data",pathData+"TestDoubleElectron_Run2010-2011A_merged_histos.root",0 , true,ZeeL ));
  // s.push_back(Sample(1000,"data",pathData+"TestDoubleElectron_Run2011A_PromptRecoV4_histos.root",0 , true,930.228 ));

  // s.push_back(Sample(1000,"data","DoubleElectron_HBB_EDMNtupleV1_ProcV2_CandV1_may_histos.root", 0, true ,235.22));
  // s.push_back(Sample(1000,"data","DoubleElectron_HBB_EDMNtupleV1_ProcV2_CandV1_prompt_histos.root",1 , true,814.5 ));
  // s.push_back(Sample(1000,"data","DoubleElectron_HBB_EDMNtupleV1_ProcV2_CandV1_merge_histos.root",1 , true,235.22 + 814.8));

  // s.push_back(Sample(1000,"data","DoubleMu_HBB_EDMNtupleV1_ProcV2_CandV1_prompt_histos.root", 1, true, 500.159));

  // s.push_back(Sample(1000,"data","METBTag_HBB_EDMNtupleV1_ProcV2_CandV1_may_histos.root", 1, true,235));
  // s.push_back(Sample(1000,"data","MET_HBB_EDMNtupleV1_ProcV2_CandV1_prompt_histos.root", 1, true,784.12));


  s.push_back(Sample(165,"TTbar",path+"TestTTJets_TuneZ2_7TeV-madgraph-tauola_histos.root", kBlue , false ));

  int stcolor=kTeal;

  /* // s.push_back(Sample(1.44,"Single Top","Tbar_TuneZ2_s-channel_7TeV-powheg-tauola_HBB_EDMNtupleV1_ProcV2_CandV1_histos.root", stcolor, false )); */
  /*  s.push_back(Sample(22.65,"Single Top",path+"TestTbar_TuneZ2_t-channel_7TeV-powheg-tauola_histos.root", stcolor, false )); */
  /*  s.push_back(Sample(7.87,"Single Top",path+"TestTbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola_histos.root", stcolor, false)); */
  /* //s.push_back(Sample(7.87,"Single Top",path+"TestTbar_TuneZ2_tW-channel-DS_7TeV-powheg-tauola_HBB_EDMNtupleV1_ProcV2_CandV1_histos.root", stcolor, false)); */
  /*  s.push_back(Sample(7.87,"Single Top",path+"TestT_TuneZ2_tW-channel-DR_7TeV-powheg-tauola_histos.root", stcolor, false)); */

  float wxsec= 31314.;
  float wxsec100= 31314./27770.*194.6;
  //TOT: 18904365 b: 363441 c: 6264682 l: 12276242
  float t=18904365;
  float b=363441;
  float c=6264682;
  float l=12276242;
 
  s.push_back(Sample(wxsec,"Wb",path+"TestWJetsToLNu_TuneZ2_7TeV-madgraph-tauola_histosB.root", kGreen+3, false ));
  s.push_back(Sample(wxsec,"Wc",path+"TestWJetsToLNu_TuneZ2_7TeV-madgraph-tauola_histosC.root", kGreen+3, false ));
  s.push_back(Sample(wxsec,"Wl",path+"TestWJetsToLNu_TuneZ2_7TeV-madgraph-tauola_histosL.root", kGreen+3, false ));


  float zxsecMG=2045;
  s.push_back(Sample(3048,"Zb",path+"TestDYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_histosB.root",kYellow ,false ));
  s.push_back(Sample(3048,"Zc",path+"TestDYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_histosC.root",kYellow-5 ,false ));
  s.push_back(Sample(3048,"Zl",path+"TestDYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_histosL.root",kYellow-6 ,false ));

  /*  s.push_back(Sample(24,"Zb",path+"TestDYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola_histosB.root",kYellow ,false )); */
  /*  s.push_back(Sample(24,"Zc",path+"TestDYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola_histosC.root",kYellow-5 ,false )); */
  /*  s.push_back(Sample(24,"Zl",path+"TestDYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola_histosL.root",kYellow-6 ,false )); */
 
  s.push_back(Sample(42.9,"VV",path+"TestWW_TuneZ2_7TeV_pythia6_tauola_histos.root",kOrange+2 , false ));
  s.push_back(Sample(18.3,"VV",path+"TestWZ_TuneZ2_7TeV_pythia6_tauola_histos.root",kOrange+2 , false ));
  s.push_back(Sample(5.9,"VV",path+"TestZZ_TuneZ2_7TeV_pythia6_tauola_histos.root",kOrange+2 , false ));

  // s.push_back(Sample((0.4107*0.704*0.03365*3),"ZH","TestZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp_histos.root",kAzure,false ));

  return s;
}
