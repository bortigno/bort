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
#include <TCut.h>
#include "Riostream.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompChol.h"
#include "TDecompSVD.h"
#include "TGraph2DErrors.h"
#include "TF2.h"

#include "samples.h"

//#include "TMultiDimFit.h"

int scaleFactors( void ){

  Bool_t addSystematics = true;
  Bool_t systematicsFromPurity = false;

  Bool_t rizziSysTTbar = false;
  Bool_t rizziSysDYB = false;
  Double_t rizziSysErr;

  Double_t ZboostCut = 120;
  Bool_t systemMethod = true;

  Int_t entries=0;

  int candType = 1;

  Double_t countLightCCData = 0;
  Double_t countTTbarCCData = 0;
  Double_t countHeavyCCData = 0;
  Double_t countSignal115Data = 0;
  Double_t countLightCCDYL = 0;
  Double_t countTTbarCCDYL = 0;
  Double_t countHeavyCCDYL = 0;
  Double_t countSignal115DYL = 0;
  Double_t countLightCCDYB = 0;
  Double_t countTTbarCCDYB = 0;
  Double_t countHeavyCCDYB = 0;
  Double_t countSignal115DYB = 0;
  Double_t countLightCCTTbar = 0;
  Double_t countTTbarCCTTbar = 0;
  Double_t countHeavyCCTTbar = 0;
  Double_t countSignal115TTbar = 0;
  Double_t countLightCCMC = 0;
  Double_t countTTbarCCMC = 0;
  Double_t countHeavyCCMC = 0;
  Double_t countSignal115MC = 0;
  Double_t countLightCCRest = 0;
  Double_t countTTbarCCRest = 0;
  Double_t countHeavyCCRest = 0;
  Double_t countSignal115Rest = 0;

  std::vector<Sample> allSamples = Nov1stDiJetPt();

  //2011 LightCC
  TCut LightCC_weights("btagA0TSF*PUweight*weightTrig");
  TCut LightCC_cutString("hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & V.pt > 100. & H.pt > 100. & abs( HVdPhi ) > 2.9 & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & V.mass > 75. & V.mass < 105 & !(hJet_csv[0] > 0.898 | hJet_csv[1] > 0.898) & H.mass < 250. & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] )");

  //2011 TTbarCC
  TCut TTbarCC_weights("btag1T2CSF*PUweight*weightTrig");
  TCut TTbarCC_cutString("H.mass < 250 & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & H.pt > 100. & ((hJet_csv[0] > 0.898 & hJet_csv[1] > 0.5) | (hJet_csv[0] > 0.5 & hJet_csv[1] > 0.898)) & (V.mass > 105 | V.mass < 75.) & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] )");

  //2011 HeavyCC
  TCut HeavyCC_weights("btag1T2CSF*PUweight*weightTrig");
  TCut HeavyCC_cutString("H.mass < 250 & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & (H.mass < 90. | H.mass > 145.) & V.mass > 75. & V.mass < 105 & ((hJet_csv[0] > 0.898 & hJet_csv[1] > 0.5) | (hJet_csv[0] > 0.5 & hJet_csv[1] > 0.898)) & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & abs( HVdPhi ) > 2.9 & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] )");

  //2011 Signal
  TCut Signal115_weights("btag1T2CSF*PUweight*weightTrig");
  TCut Signal115_cutString("(hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & H.mass > 90. & H.mass < 125. & V.mass > 75. & V.mass < 105 & ((hJet_csv[0] > 0.898 & hJet_csv[1] > 0.5) | (hJet_csv[0] > 0.5 & hJet_csv[1] > 0.898)) & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & abs( HVdPhi ) > 2.9 & V.pt < 100. & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");

  //development cut string
  //  TCut TTbarCC_cutString("PUweight*weightTrig*(hbhe & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & V.mass > 120 & hJet_csv[0] > 0.898 & hJet_csv[1] > 0.898 & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");

  TCut boost("genZpt >120");
  TCut isB("eventFlav == 5");

  std::string Run2011A("Run2011A");
  std::string DY("DY");
  std::string DYBOOSTED("DYBOOSTED");
  std::string TTbar("TTbar");

  for(size_t i = 0; i<allSamples.size();++i){
    allSamples.at(i).dump(1);
    if(allSamples.at(i).name == Run2011A){
      countLightCCData += allSamples.at(i).count( (LightCC_cutString) );
      countTTbarCCData += allSamples.at(i).count( (TTbarCC_cutString) );
      countHeavyCCData += allSamples.at(i).count( (HeavyCC_cutString) );
      countSignal115Data += allSamples.at(i).count( (Signal115_cutString) );
    }
    else if( allSamples.at(i).name == DY ){
      countLightCCDYL += allSamples.at(i).count(LightCC_weights*(LightCC_cutString&&(!isB)&&(!boost)) );
      countLightCCDYB += allSamples.at(i).count(LightCC_weights*(LightCC_cutString&&isB&&(!boost)) );
      countTTbarCCDYL += allSamples.at(i).count(TTbarCC_weights*(TTbarCC_cutString&&(!isB)&&(!boost)) );
      countTTbarCCDYB += allSamples.at(i).count(TTbarCC_weights*(TTbarCC_cutString&&isB&&(!boost)) );
      countHeavyCCDYL += allSamples.at(i).count(HeavyCC_weights*(HeavyCC_cutString&&(!isB)&&(!boost)) );
      countHeavyCCDYB += allSamples.at(i).count(HeavyCC_weights*(HeavyCC_cutString&&isB&&(!boost)) );
      countSignal115DYL += allSamples.at(i).count(Signal115_weights*(Signal115_cutString&&(!isB)&&(!boost)) );
      countSignal115DYB += allSamples.at(i).count(Signal115_weights*(Signal115_cutString&&isB&&(!boost)) );

    }
    else if( allSamples.at(i).name == DYBOOSTED ){
      countLightCCDYL += allSamples.at(i).count(LightCC_weights*(LightCC_cutString&&(!isB)&&boost) );
      countLightCCDYB += allSamples.at(i).count(LightCC_weights*(LightCC_cutString&&isB&&boost) );
      countTTbarCCDYL += allSamples.at(i).count(TTbarCC_weights*(TTbarCC_cutString&&(!isB)&&boost) );
      countTTbarCCDYB += allSamples.at(i).count(TTbarCC_weights*(TTbarCC_cutString&&isB&&boost) );
      countHeavyCCDYL += allSamples.at(i).count(HeavyCC_weights*(HeavyCC_cutString&&(!isB)&&boost) );
      countHeavyCCDYB += allSamples.at(i).count(HeavyCC_weights*(HeavyCC_cutString&&isB&&boost) );
      countSignal115DYL += allSamples.at(i).count(Signal115_weights*(Signal115_cutString&&(!isB)&&boost) );
      countSignal115DYB += allSamples.at(i).count(Signal115_weights*(Signal115_cutString&&isB&&boost) );
    }
    else if(allSamples.at(i).name == TTbar){
      countLightCCTTbar += allSamples.at(i).count(LightCC_weights*(LightCC_cutString) );
      countTTbarCCTTbar += allSamples.at(i).count(TTbarCC_weights*(TTbarCC_cutString) );
      countHeavyCCTTbar += allSamples.at(i).count(HeavyCC_weights*(HeavyCC_cutString) );
      countSignal115TTbar += allSamples.at(i).count(Signal115_weights*(Signal115_cutString) );
    }
    else{
      countLightCCMC += allSamples.at(i).count(LightCC_weights*(LightCC_cutString) );
      countTTbarCCMC += allSamples.at(i).count(TTbarCC_weights*(TTbarCC_cutString) );
      countHeavyCCMC += allSamples.at(i).count(HeavyCC_weights*(HeavyCC_cutString) );
      countSignal115MC += allSamples.at(i).count(Signal115_weights*(Signal115_cutString) );
    }
  }

  countLightCCRest = countLightCCData - countLightCCMC;
  countTTbarCCRest = countTTbarCCData - countTTbarCCMC;
  countHeavyCCRest = countHeavyCCData - countHeavyCCMC;
  countSignal115Rest = countSignal115Data - countSignal115MC;

  //SYSTEM METHOD
  int nVars = 3;  
  
  Double_t d_light[] = { (double)(countLightCCDYL), (double)(countTTbarCCDYL), (double)(countHeavyCCDYL) };
  Double_t d_ttbar[] = { (double)(countLightCCTTbar), (double)(countTTbarCCTTbar), (double)(countHeavyCCTTbar) };
  Double_t d_heavy[] = { (double)(countLightCCDYB), (double)(countTTbarCCDYB), (double)(countHeavyCCDYB) };
  Double_t d_rest[] = { (double)(countLightCCRest), (double)(countTTbarCCRest), (double)(countHeavyCCRest) };
  
//   Double_t e_light[] = { (double)(errorLightCCDYL), (double)(errorTTbarCCDYL), (double)(errorHeavyCCDYL) };
//   Double_t e_ttbar[] = { (double)(errorLightCCTTbar), (double)(errorTTbarCCTTbar), (double)(errorHeavyCCTTbar) };
//   Double_t e_heavy[] = { (double)(errorLightCCDYB), (double)(errorTTbarCCDYB), (double)(errorHeavyCCDYB) };
//   Double_t e_rest[] = { (double)(errorLightCCRest), (double)(errorTTbarCCRest), (double)(errorHeavyCCRest) };
  
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
//   std::cout << "countSignal115VV  = " << (double)countSignal115VV << std::endl;
//   std::cout << "countSignal115ST  = " << (double)countSignal115SingleTop << std::endl;


  
//   std::cout << "Errors" << std::endl;
//   std::cout << "errorLightCCDYL = " << (double)e_light[0] <<  std::endl;
//   std::cout << "errorTTbarCCDYL = " << (double)e_light[1] <<  std::endl;
//   std::cout << "errorHeavyCCDYL = " << (double)e_light[2] <<  std::endl;
  
//   std::cout << "errorLightCCTTbar  = " << (double)e_ttbar[0] <<  std::endl;
//   std::cout << "errorTTbarCCTTbar  = " << (double)e_ttbar[1] <<  std::endl;
//   std::cout << "errorHeavyCCTTbar  = " << (double)e_ttbar[2] <<  std::endl;
  
//   std::cout << "errorLightCCDYB  = " << (double)e_heavy[0] << std::endl;
//   std::cout << "errorTTbarCCDYB  = " << (double)e_heavy[1] << std::endl;
//   std::cout << "errorHeavyCCDYB  = " << (double)e_heavy[2] << std::endl;
  
//   std::cout << "errorLightCCRest  = " << (double)e_rest[0] << std::endl;
//   std::cout << "errorTTbarCCRest  = " << (double)e_rest[1] << std::endl;
//   std::cout << "errorHeavyCCRest  = " << (double)e_rest[2] << std::endl;

//   std::cout << "errorSignal115DYL  = " << (double)errorSignal115DYL << std::endl;
//   std::cout << "errorSignal115TTbar  = " << (double)errorSignal115TTbar << std::endl;
//   std::cout << "errorSignal115DYB  = " << (double)errorSignal115DYB << std::endl;
//   std::cout << "errorSignal115VV  = " << (double)errorSignal115VV << std::endl;
//   std::cout << "errorSignal115ST  = " << (double)errorSignal115SingleTop << std::endl;

  
  
  //    TVectorD v_SF = NormalEqn(M_A,v_rest);
  
  bool ok = true;
  TDecompSVD svd(M_A);
  TVectorD v_SF = svd.Solve(v_rest, ok);
  
  std::cout << "system results" << std::endl;
  std::cout << "Light SF = " << (double)v_SF[0] <<  std::endl;
  std::cout << "TTbar SF = " << (double)v_SF[1] <<  std::endl;
  std::cout << "Heavy SF = " << (double)v_SF[2] << std::endl;
  

  return 0;
}


