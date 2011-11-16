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
#include "sampleCollection.h"

//#include "TMultiDimFit.h"

double sumError(double e1, double e2){
  return ( TMath::Sqrt(TMath::Power(e1,2) + TMath::Power(e2,2) ) );
}

int scaleFactors( void ){

  Bool_t debug_ = true;
  Bool_t addSystematics = true;

  Int_t entries=0;

  int candType = 1;

  Double_t fA,fB;

  Double_t d_data[] = {0,0,0,0};
  Double_t d_light[] = {0,0,0,0};
  Double_t d_ttbar[] = {0,0,0,0};
  Double_t d_heavy[] = {0,0,0,0};
  Double_t d_mc[] = {0,0,0,0};
  Double_t d_ST[] = {0,0,0,0};
  Double_t d_VV[] = {0,0,0,0};
  Double_t d_rest[] = {0,0,0,0};
  Double_t d_signal[] = {0,0,0,0};

  Double_t e_data[] = {0,0,0,0};
  Double_t e_light[] = {0,0,0,0};
  Double_t e_ttbar[] = {0,0,0,0};
  Double_t e_heavy[] = {0,0,0,0};
  Double_t e_mc[] = {0,0,0,0};
  Double_t e_ST[] = {0,0,0,0};
  Double_t e_VV[] = {0,0,0,0};
  Double_t e_rest[] = {0,0,0,0};
  Double_t e_signal[] = {0,0,0,0};

  Double_t ZeeL =0;
  Double_t ZeeLA=0;
  Double_t ZeeLB=0;


  //  std::vector<Sample> allSamples = Nov1stDiJetPt();
  //  std::vector<Sample> allSamples = Nov1stDiJetPtUpdated();
  std::vector<Sample> allSamples = Nov10thDiJetPtUpdated();

  //2011 LightCC
  //  TCut PUweight("(0.614603*PUweight+0.385397*PUweight2011B)");
  TCut PUweight("(0.46502*PUweight+0.53498*PUweight2011B)");
  //  TCut LightCC_weights("btagA0TSF*weightTrig");
  TCut LightCC_weights("weightTrig");
  LightCC_weights*=PUweight;
  TCut LightCC_cutString("hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & V.pt > 100. & H.pt > 100. & abs( HVdPhi ) > 2.9 & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & V.mass > 75. & V.mass < 105 & !(hJet_csv[0] > 0.898 | hJet_csv[1] > 0.898) & H.mass < 250. & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] )");

  //2011 TTbarCC
  //  TCut TTbarCC_weights("btag1T2CSF*weightTrig");
  TCut TTbarCC_weights("weightTrig");
  TTbarCC_weights *= PUweight;
  TCut TTbarCC_cutString("H.mass < 250 & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & H.pt > 100. & ((hJet_csv[0] > 0.898 & hJet_csv[1] > 0.5) | (hJet_csv[0] > 0.5 & hJet_csv[1] > 0.898)) & (V.mass > 105 | V.mass < 75.) & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] )");

  //2011 HeavyCC
  //  TCut HeavyCC_weights("btag1T2CSF*weightTrig");
  TCut HeavyCC_weights("weightTrig");
  HeavyCC_weights *= PUweight;
  TCut HeavyCC_cutString("H.mass < 250 & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & (H.mass < 90. | H.mass > 145.) & V.mass > 75. & V.mass < 105 & ((hJet_csv[0] > 0.898 & hJet_csv[1] > 0.5) | (hJet_csv[0] > 0.5 & hJet_csv[1] > 0.898)) & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & abs( HVdPhi ) > 2.9 & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] )");

  //2011 Signal
  //  TCut Signal115_weights("btag1T2CSF*weightTrig");
  TCut Signal115_weights("weightTrig");
  Signal115_weights *= PUweight;
  TCut Signal115_cutString("(hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & hbhe & H.mass > 90. & H.mass < 125. & V.mass > 75. & V.mass < 105 & ((hJet_csv[0] > 0.898 & hJet_csv[1] > 0.5) | (hJet_csv[0] > 0.5 & hJet_csv[1] > 0.898)) & Sum$(aJet_pt > 20 & abs(aJet_eta) < 2.4) < 2. & abs( HVdPhi ) > 2.9 & V.pt < 100. & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");

  //development cut string
  //  TCut TTbarCC_cutString("PUweight*weightTrig*(hbhe & hJet_pt[0] > 20. & hJet_pt[1] > 20. & EVENT.json & V.mass > 120 & hJet_csv[0] > 0.898 & hJet_csv[1] > 0.898 & Vtype == 1 & ( triggerFlags[5] | triggerFlags[6] ))");

  TCut boost("genZpt > 120");
  TCut isB("eventFlav == 5");
  //  TCut runRange("EVENT.run < 178078");
  TCut runRange("");

  std::string Run2011A("Run2011A");
  std::string Run2011B("Run2011B");
  std::string DY("DY");
  std::string DYBOOSTED("DYBOOSTED");
  std::string TTbar("TTbar");
  std::string Signal("ZH");
  std::string ST("ST");
  std::string VV("VV");

  //without cut range
  //   fA = 0.552369;
  //   fB = 0.447631;
  //with cut range
//   fA = 0.614603;
//   fB = 0.385397;
  //all dataset
  fA = 0.46502;
  fB = 0.53498;


  for(size_t i = 0; i<allSamples.size();++i){
    allSamples.at(i).dump(1,fA,fB );
    if(allSamples.at(i).name == Run2011A){
      ZeeL += allSamples.at(i).lumi();
      ZeeLA += allSamples.at(i).lumi();
      d_data[0] += allSamples.at(i).count( (LightCC_cutString) );
      d_data[1] += allSamples.at(i).count( (TTbarCC_cutString) );
      d_data[2] += allSamples.at(i).count( (HeavyCC_cutString) );
      d_data[3] += allSamples.at(i).count( (Signal115_cutString) );
      e_data[0] = sumError( e_data[0], allSamples.at(i).countError( (LightCC_cutString) ) );
      e_data[1] = sumError( e_data[1], allSamples.at(i).countError( (TTbarCC_cutString) ) );
      e_data[2] = sumError( e_data[2], allSamples.at(i).countError( (HeavyCC_cutString) ) );
      e_data[3] = sumError( e_data[3], allSamples.at(i).countError( (Signal115_cutString) ) );
      fA=ZeeLA/ZeeL;
      fB=ZeeLB/ZeeL;
    }
    else if(allSamples.at(i).name == Run2011B){
      ZeeL += allSamples.at(i).lumi();
      ZeeLB += allSamples.at(i).lumi();
      d_data[0] += allSamples.at(i).count( (LightCC_cutString&&runRange)  );
      d_data[1] += allSamples.at(i).count( (TTbarCC_cutString&&runRange)  );
      d_data[2] += allSamples.at(i).count( (HeavyCC_cutString&&runRange)  );
      d_data[3] += allSamples.at(i).count( (Signal115_cutString&&runRange)  );
      e_data[0] = sumError( e_data[0], allSamples.at(i).countError( (LightCC_cutString&&runRange) ) );
      e_data[1] = sumError( e_data[1], allSamples.at(i).countError( (TTbarCC_cutString&&runRange) ) );
      e_data[2] = sumError( e_data[2], allSamples.at(i).countError( (HeavyCC_cutString&&runRange) ) );
      e_data[3] = sumError( e_data[3], allSamples.at(i).countError( (Signal115_cutString&&runRange) ) );
      fA=ZeeLA/ZeeL;
      fB=ZeeLB/ZeeL;
    }
    else if( allSamples.at(i).name == DY ){
      d_light[0] += allSamples.at(i).count(LightCC_weights,(LightCC_cutString&&(!isB)&&(!boost)) , fA,fB );
      d_heavy[0] += allSamples.at(i).count(LightCC_weights,(LightCC_cutString&&isB&&(!boost)) , fA,fB );
      d_light[1] += allSamples.at(i).count(TTbarCC_weights,(TTbarCC_cutString&&(!isB)&&(!boost)) , fA,fB );
      d_heavy[1] += allSamples.at(i).count(TTbarCC_weights,(TTbarCC_cutString&&isB&&(!boost)) , fA,fB );
      d_light[2] += allSamples.at(i).count(HeavyCC_weights,(HeavyCC_cutString&&(!isB)&&(!boost)) , fA,fB );
      d_heavy[2] += allSamples.at(i).count(HeavyCC_weights,(HeavyCC_cutString&&isB&&(!boost)) , fA,fB );
      d_light[3] += allSamples.at(i).count(Signal115_weights,(Signal115_cutString&&(!isB)&&(!boost)) , fA,fB );
      d_heavy[3] += allSamples.at(i).count(Signal115_weights,(Signal115_cutString&&isB&&(!boost)) , fA,fB );
      e_light[0] = sumError( e_light[0], allSamples.at(i).countError(LightCC_weights,(LightCC_cutString&&(!isB)&&(!boost)) , fA,fB ) );
      e_heavy[0] = sumError( e_heavy[0], allSamples.at(i).countError(LightCC_weights,(LightCC_cutString&&isB&&(!boost)) , fA,fB ) );
      e_light[1] = sumError( e_light[1], allSamples.at(i).countError(TTbarCC_weights,(TTbarCC_cutString&&(!isB)&&(!boost)) , fA,fB ) );
      e_heavy[1] = sumError( e_heavy[1], allSamples.at(i).countError(TTbarCC_weights,(TTbarCC_cutString&&isB&&(!boost)) , fA,fB ) );
      e_light[2] = sumError( e_light[2], allSamples.at(i).countError(HeavyCC_weights,(HeavyCC_cutString&&(!isB)&&(!boost)) , fA,fB ) );
      e_heavy[2] = sumError( e_heavy[2], allSamples.at(i).countError(HeavyCC_weights,(HeavyCC_cutString&&isB&&(!boost)) , fA,fB ) );
      e_light[3] = sumError( e_light[3], allSamples.at(i).countError(Signal115_weights,(Signal115_cutString&&(!isB)&&(!boost)) , fA,fB ) );
      e_heavy[3] = sumError( e_heavy[3], allSamples.at(i).countError(Signal115_weights,(Signal115_cutString&&isB&&(!boost)) , fA,fB ) );
    }
    else if( allSamples.at(i).name == DYBOOSTED ){
      d_light[0] += allSamples.at(i).count(LightCC_weights,(LightCC_cutString&&(!isB)&&boost) , fA,fB );
      d_heavy[0] += allSamples.at(i).count(LightCC_weights,(LightCC_cutString&&isB&&boost) , fA,fB );
      d_light[1] += allSamples.at(i).count(TTbarCC_weights,(TTbarCC_cutString&&(!isB)&&boost) , fA,fB );
      d_heavy[1] += allSamples.at(i).count(TTbarCC_weights,(TTbarCC_cutString&&isB&&boost) , fA,fB );
      d_light[2] += allSamples.at(i).count(HeavyCC_weights,(HeavyCC_cutString&&(!isB)&&boost) , fA,fB );
      d_heavy[2] += allSamples.at(i).count(HeavyCC_weights,(HeavyCC_cutString&&isB&&boost) , fA,fB );
      d_light[3] += allSamples.at(i).count(Signal115_weights,(Signal115_cutString&&(!isB)&&boost) , fA,fB );
      d_heavy[3] += allSamples.at(i).count(Signal115_weights,(Signal115_cutString&&isB&&boost) , fA,fB );
      e_light[0] = sumError( e_light[0], allSamples.at(i).countError(LightCC_weights,(LightCC_cutString&&(!isB)&&(boost)) , fA,fB ) );
      e_heavy[0] = sumError( e_heavy[0], allSamples.at(i).countError(LightCC_weights,(LightCC_cutString&&isB&&(boost)) , fA,fB ) );
      e_light[1] = sumError( e_light[1], allSamples.at(i).countError(TTbarCC_weights,(TTbarCC_cutString&&(!isB)&&(boost)) , fA,fB ) );
      e_heavy[1] = sumError( e_heavy[1], allSamples.at(i).countError(TTbarCC_weights,(TTbarCC_cutString&&isB&&(boost)) , fA,fB ) );
      e_light[2] = sumError( e_light[2], allSamples.at(i).countError(HeavyCC_weights,(HeavyCC_cutString&&(!isB)&&(boost)) , fA,fB ) );
      e_heavy[2] = sumError( e_heavy[2], allSamples.at(i).countError(HeavyCC_weights,(HeavyCC_cutString&&isB&&(boost)) , fA,fB ) );
      e_light[3] = sumError( e_light[3], allSamples.at(i).countError(Signal115_weights,(Signal115_cutString&&(!isB)&&(boost)) , fA,fB ) );
      e_heavy[3] = sumError( e_heavy[3], allSamples.at(i).countError(Signal115_weights,(Signal115_cutString&&isB&&(boost)) , fA,fB ) );  
      if(debug_){
	std::cout << "DYL boosted " << allSamples.at(i).bareCount( LightCC_weights , (LightCC_cutString&&(!isB)&&(boost)) ) << std::endl;
	std::cout << "DYB boosted " << allSamples.at(i).bareCount( LightCC_weights , (LightCC_cutString&&(isB)&&(boost)) ) << std::endl;
	std::cout << "DYL boosted " << allSamples.at(i).bareCount( (LightCC_cutString&&(!isB)&&(boost)) ) << std::endl;
	std::cout << "DYB boosted " << allSamples.at(i).bareCount( (LightCC_cutString&&(isB)&&(boost)) ) << std::endl;

      }
    }
    else if(allSamples.at(i).name == TTbar){
      d_ttbar[0] += allSamples.at(i).count(LightCC_weights,(LightCC_cutString) , fA,fB );
      d_ttbar[1] += allSamples.at(i).count(TTbarCC_weights,(TTbarCC_cutString) , fA,fB );
      d_ttbar[2] += allSamples.at(i).count(HeavyCC_weights,(HeavyCC_cutString) , fA,fB );
      d_ttbar[3] += allSamples.at(i).count(Signal115_weights,(Signal115_cutString) , fA,fB );
      e_ttbar[0] = sumError( e_ttbar[0] , allSamples.at(i).countError(LightCC_weights,(LightCC_cutString) , fA,fB ) );
      e_ttbar[1] = sumError( e_ttbar[1] , allSamples.at(i).countError(TTbarCC_weights,(TTbarCC_cutString) , fA,fB ) );
      e_ttbar[2] = sumError( e_ttbar[2] , allSamples.at(i).countError(HeavyCC_weights,(HeavyCC_cutString) , fA,fB ) );
      e_ttbar[3] = sumError( e_ttbar[3] , allSamples.at(i).countError(Signal115_weights,(Signal115_cutString) , fA,fB ) );
    }
    else if( allSamples.at(i).name == ST ){
      d_ST[0] += allSamples.at(i).count(LightCC_weights,(LightCC_cutString) , fA,fB );
      d_ST[1] += allSamples.at(i).count(TTbarCC_weights,(TTbarCC_cutString) , fA,fB );
      d_ST[2] += allSamples.at(i).count(HeavyCC_weights,(HeavyCC_cutString) , fA,fB );
      d_ST[3] += allSamples.at(i).count(Signal115_weights,(Signal115_cutString) , fA,fB );
      e_ST[0] = sumError( e_ST[0] , allSamples.at(i).countError(LightCC_weights,(LightCC_cutString) , fA,fB ) );
      e_ST[1] = sumError( e_ST[1] , allSamples.at(i).countError(TTbarCC_weights,(TTbarCC_cutString) , fA,fB ) );
      e_ST[2] = sumError( e_ST[2] , allSamples.at(i).countError(HeavyCC_weights,(HeavyCC_cutString) , fA,fB ) );
      e_ST[3] = sumError( e_ST[3] , allSamples.at(i).countError(Signal115_weights,(Signal115_cutString) , fA,fB ) );
    }
    else if( allSamples.at(i).name == VV ){
      d_VV[0] += allSamples.at(i).count(LightCC_weights,(LightCC_cutString) , fA,fB );
      d_VV[1] += allSamples.at(i).count(TTbarCC_weights,(TTbarCC_cutString) , fA,fB );
      d_VV[2] += allSamples.at(i).count(HeavyCC_weights,(HeavyCC_cutString) , fA,fB );
      d_VV[3] += allSamples.at(i).count(Signal115_weights,(Signal115_cutString) , fA,fB );
      e_VV[0] = sumError( e_VV[0] , allSamples.at(i).countError(LightCC_weights,(LightCC_cutString) , fA,fB ) );
      e_VV[1] = sumError( e_VV[1] , allSamples.at(i).countError(TTbarCC_weights,(TTbarCC_cutString) , fA,fB ) );
      e_VV[2] = sumError( e_VV[2] , allSamples.at(i).countError(HeavyCC_weights,(HeavyCC_cutString) , fA,fB ) );
      e_VV[3] = sumError( e_VV[3] , allSamples.at(i).countError(Signal115_weights,(Signal115_cutString) , fA,fB ) );
    }
    else if( allSamples.at(i).name == Signal ){
      d_signal[0] += allSamples.at(i).count(LightCC_weights,(LightCC_cutString) , fA,fB );
      d_signal[1] += allSamples.at(i).count(TTbarCC_weights,(TTbarCC_cutString) , fA,fB );
      d_signal[2] += allSamples.at(i).count(HeavyCC_weights,(HeavyCC_cutString) , fA,fB );
      d_signal[3] += allSamples.at(i).count(Signal115_weights,(Signal115_cutString) , fA,fB );
      e_signal[0] = sumError( e_signal[0] , allSamples.at(i).countError(LightCC_weights,(LightCC_cutString) , fA,fB ) );
      e_signal[1] = sumError( e_signal[1] , allSamples.at(i).countError(TTbarCC_weights,(TTbarCC_cutString) , fA,fB ) );
      e_signal[2] = sumError( e_signal[2] , allSamples.at(i).countError(HeavyCC_weights,(HeavyCC_cutString) , fA,fB ) );
      e_signal[3] = sumError( e_signal[3] , allSamples.at(i).countError(Signal115_weights,(Signal115_cutString) , fA,fB ) );
    }
    else if( !(allSamples.at(i).name == Signal) ){
      d_mc[0] += allSamples.at(i).count(LightCC_weights,(LightCC_cutString) , fA,fB );
      d_mc[1] += allSamples.at(i).count(TTbarCC_weights,(TTbarCC_cutString) , fA,fB );
      d_mc[2] += allSamples.at(i).count(HeavyCC_weights,(HeavyCC_cutString) , fA,fB );
      d_mc[3] += allSamples.at(i).count(Signal115_weights,(Signal115_cutString) , fA,fB );
      e_mc[0] = sumError( e_mc[0] , allSamples.at(i).countError(LightCC_weights,(LightCC_cutString) , fA,fB ) );
      e_mc[1] = sumError( e_mc[1] , allSamples.at(i).countError(TTbarCC_weights,(TTbarCC_cutString) , fA,fB ) );
      e_mc[2] = sumError( e_mc[2] , allSamples.at(i).countError(HeavyCC_weights,(HeavyCC_cutString) , fA,fB ) );
      e_mc[3] = sumError( e_mc[3] , allSamples.at(i).countError(Signal115_weights,(Signal115_cutString) , fA,fB ) );
    }
  }

  //normalize to the data luminosity
  std::cout << "Total Luminosity = " << ZeeL << std::endl;
  for(int i = 0; i < 4; ++i){
    d_light[i] *= ZeeL;
    d_heavy[i] *= ZeeL;
    d_ttbar[i] *= ZeeL;
    d_mc[i] *= ZeeL;
    d_ST[i] *= ZeeL;
    d_VV[i] *= ZeeL;
    d_signal[i] *= ZeeL;
    e_light[i] *= ZeeL;
    e_heavy[i] *= ZeeL;
    e_ttbar[i] *= ZeeL;
    e_mc[i] *= ZeeL;
    e_ST[i] *= ZeeL;
    e_VV[i] *= ZeeL;
    e_signal[i] *= ZeeL;
  }

  for(int i = 0; i < 4; ++i){
    //adding syst
    if(addSystematics){
      e_ST[i] = sumError( e_ST[i], 0.3*d_ST[i] );
      e_VV[i] = sumError( e_VV[i], 0.3*d_VV[i] );
    }
    e_mc[i] = sumError( e_mc[i], e_ST[i] );
    e_mc[i] = sumError( e_mc[i], e_VV[i] );
    //putting everything together
    d_mc[i] += ( d_ST[i] + d_VV[i] );
    d_rest[i] = d_data[i] - d_mc[i] ;
    e_rest[i] = sumError( e_data[i] , e_mc[i] ) ;
  }

  //SYSTEM METHOD
  int nVars = 3;  
  
  TVectorD v_light; v_light.Use(3,d_light);
  TVectorD v_ttbar; v_ttbar.Use(3,d_ttbar);
  TVectorD v_heavy; v_heavy.Use(3,d_heavy);
  TVectorD v_data; v_data.Use(3,d_data);
  TVectorD v_mc; v_mc.Use(3,d_mc);
  TVectorD v_rest; v_rest.Use(3,d_rest);
  
  TMatrixD M_A(3,3);
  TMatrixDColumn(M_A,0) = v_light;
  TMatrixDColumn(M_A,1) = v_ttbar;
  TMatrixDColumn(M_A,2) = v_heavy;
  
  std::cout << "Matrix elements" << std::endl;
  std::cout << " | " << M_A(0,0) << " | " << M_A(1,0) << " | " << M_A(2,0) << " | " << std::endl;
  std::cout << " | " << M_A(0,1) << " | " << M_A(1,1) << " | " << M_A(2,1) << " | "<< std::endl;
  std::cout << " | " << M_A(0,2) << " | " << M_A(1,2) << " | " << M_A(2,2) << " | "<< std::endl;
  
  std::cout << "(* Counts *)" << std::endl;
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
 

  std::cout << "(* Errors *)" << std::endl;
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

  std::cout << "(* For signal region *)" << std::endl;
  std::cout << "countSignalCCDYL = " << (double)d_light[3] <<  std::endl;
  std::cout << "countSignalCCTTbar  = " << (double)d_ttbar[3] <<  std::endl;
  std::cout << "countSignalCCDYB  = " << (double)d_heavy[3] << std::endl;
  std::cout << "countSignalCCST  = " << (double)d_ST[3] << std::endl;
  std::cout << "countSignalCCVV  = " << (double)d_VV[3] << std::endl;
  //  std::cout << "countSignalCCWJ  = " << (double)d_heavy[3] << std::endl;

  std::cout << "errorSignalCCDYL = " << (double)e_light[3] <<  std::endl;
  std::cout << "errorSignalCCTTbar  = " << (double)e_ttbar[3] <<  std::endl;
  std::cout << "errorSignalCCDYB  = " << (double)e_heavy[3] << std::endl;
  std::cout << "errorSignalCCST  = " << (double)e_ST[3] << std::endl;
  std::cout << "errorSignalCCVV  = " << (double)e_VV[3] << std::endl;
  
  //    TVectorD v_SF = NormalEqn(M_A,v_rest);  
  bool ok = true;
  TDecompSVD svd(M_A);
  TVectorD v_SF = svd.Solve(v_rest, ok);
  
  std::cout << "system results" << std::endl;
  std::cout << "Light SF = " << (double)v_SF[0] <<  std::endl;
  std::cout << "TTbar SF = " << (double)v_SF[1] <<  std::endl;
  std::cout << "Heavy SF = " << (double)v_SF[2] << std::endl;

  for(int i = 0 ; i< 4 ; ++i){
    double d_totalMC = d_heavy[i]+d_light[i]+d_mc[i]+d_ttbar[i];
    double e_totalMC = TMath::Sqrt( TMath::Power(e_mc[i],2) + TMath::Power(e_ttbar[i],2) + TMath::Power(e_heavy[i],2) + TMath::Power(e_light[i],2));
    double d_purity[] = { d_light[0]/d_totalMC, d_ttbar[1]/d_totalMC, d_heavy[2]/d_totalMC };
    std::cout << "  \\begin{table}[t]" << std::endl;
    std::cout << "  \\caption{Control\\label{tab:Cutflow}}" << std::endl;
    std::cout << "  \\vspace{0.4cm}" << std::endl;
    std::cout << "  \\begin{center}" << std::endl;
    std::cout << "  \\begin{tabular}{c|c} \\hline" << std::endl;
    std::cout << "	Dataset&Z(ee)H\\\\\\hline \\hline" << std::endl;
    std::cout << "" << std::endl;
    //  std::cout << "  $W+\\textrm{jets}$&$"<< countTTbarCCWJETS <<" \\pm " << errorTTbarCCWJETS << "$\\\\" << std::endl;
    std::cout << "  WW, WZ, ZZ&$"       << d_VV[i]     <<" \\pm "<< e_VV[i]    << "$\\\\" << std::endl;
    std::cout << "  $t\\bar{t}$+jets&$" << d_ttbar[i]  <<" \\pm "<< e_ttbar[i] << "$\\\\" << std::endl;
    std::cout << "  $Z + udscg$&$"      << d_light[i]  <<" \\pm "<< e_light[i] << "$\\\\" << std::endl;
    std::cout << "  $Z + b\\bar{b}$&$"  << d_heavy[i]  <<" \\pm "<< e_heavy[i] << "$\\\\\\hline " << std::endl;
    std::cout << "  Sum MC&$"           << d_totalMC   <<" \\pm "<< e_totalMC  << "$\\\\\\hline " << std::endl;
    std::cout << "  Data&$"             << d_data[i]   <<" \\pm "<< e_data[i]  << "$\\\\\\hline " << std::endl;
    std::cout << "  ZH(115 GeV)&$"      << d_signal[i] <<" \\pm "<< e_signal[i]<< "$\\\\\\hline " << std::endl;
    std::cout << "  Purity&$"           << d_purity[i] <<" \\pm "<< "xxx"      << "$\\\\\\hline " << std::endl;
    if(i<3)
      std::cout << "  Scale Factor&$"     << v_SF[i]     <<" \\pm "<< "xxx"      << "$\\\\\\hline " << std::endl;
    std::cout << "	\\end{tabular}" << std::endl;
    std::cout << "  \\end{center}" << std::endl;
    std::cout << "  \\end{table}" << std::endl;
  }
  
  return 0;
}


