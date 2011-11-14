#include <TROOT.h>
#include <TApplication.h>
#include <TH1.h>
#include <iostream>
#include "CutsAndHistos.h"
#include "Histos.h"
//#include "Cuts200X.h"
#include "CutsLP.h"
#include "CutsLP_addJetRelaxed.h"
#include "CutsLP_ptRelaxed.h"
#include "CutsLP_HmassRelaxed.h"
#include "CutsLP_VmassRelaxed.h"
#include "CutsLP_HVdPhiRelaxed.h"

#include "samples.h"
#include "ntupleReader.h"
#include "sampleCollection.h"
#include "Riostream.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompChol.h"
#include "TDecompSVD.h"

// struct counters{
//   counters( std::vector<int>& nSteps_, std::vector< std::vector<double> >& counterCollection_ )
//     : nSteps(nSteps_), counterCollection(counterCollection_) {};
//   void init() {
//     for(int i = 0; i < nSteps.size(); ++i ){
//       pt().assign(nSteps.at(i), 0);
//       addJets().assign(nSteps.at(i), 0);
//     }
//   }
//   std::vector<double> pt() {return counterCollection.at(0);}
//   std::vector<double> addJets() {return counterCollection.at(1);}
//   std::vector<int> nSteps;
//   std::vector< std::vector<double> > counterCollection;

// };

#define ZeeL 3523.64
#define fA 0.614603
#define fB 0.385397

void LightPtSys( double minPt, double maxPt ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  VlightRegionPtRelaxedHZee nominalLight;
  double bin = (maxPt - minPt) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominalLight.pass(event, sample) ){ // nominalLight cuts except the syst
      if( event.H_pt > (minPt + bin*k) && event.V_pt > (minPt +bin*k) ){ // syst cuts
	if(sample.data)
	  counts[k]++;
	else
	  counts[k] +=  sample.scale(ZeeL,fA,fB)*nominalLight.weight(event, sample);
      }
    }
}

void TTbarPtSys( double minPt, double maxPt ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  TTbarRegionHZee nominalTTbar;
  double bin = (maxPt - minPt) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominalTTbar.pass( event, sample ) ){ // nominalTTbar cuts except the syst
      //      if( event.H_pt > (minPt + bin*k) && event.V_pt > (minPt +bin*k) ){ // syst cuts
      if(sample.data)
	counts[k]++;
      else
	counts[k] += sample.scale(ZeeL,fA,fB)*nominalTTbar.weight(event, sample);
    }
}

void HeavyPtSys( double minPt, double maxPt ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  VbbRegionHZee nominalHeavy;
  double bin = (maxPt - minPt) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominalHeavy.pass(event, sample) ){ // nominalHeavy cuts except the syst
      //      if( event.H_pt > (minPt + bin*k) && event.V_pt > (minPt +bin*k) ){ // syst cuts
      if(sample.data)
	counts[k]++;
      else
	counts[k] += sample.scale(ZeeL,fA,fB)*nominalHeavy.weight(event, sample);
    }
}

void LightAddJetSys( double minAddJet, double maxAddJet ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  //  VlightRegionAddJetRelaxedHZee nominal;
  VlightRegionAddJetRelaxedHZee nominal;
  double bin = (maxAddJet - minAddJet) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ) // nominal cuts except the syst
      if( event.CountAddJets() <= (minAddJet + bin*k) ){ // syst cuts
	if(sample.data)
	  counts[k]++;
	else
	  counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
      }
}


void TTbarAddJetSys( double minAddJet, double maxAddJet ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  TTbarRegionHZee nominal;
  double bin = (maxAddJet - minAddJet) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ){ // nominal cuts except the syst
      //      if( event.CountAddJets() < (minAddJet + bin*k) ) // syst cuts
      if(sample.data)
	counts[k]++;
      else     
	counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
    }
}

void HeavyAddJetSys( double minAddJet, double maxAddJet ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  VbbRegionHZee nominal;
  double bin = (maxAddJet - minAddJet) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ){ // nominal cuts except the syst
      //      if( event.CountAddJets() < (minAddJet + bin*k) ) // syst cuts
      if(sample.data)
	counts[k]++;
      else
	counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
    }
}

void LightHVdPhiSys( double minHVdPhi, double maxHVdPhi ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  VlightRegionHVdPhiRelaxedHZee nominal;
  double bin = (maxHVdPhi - minHVdPhi) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ) // nominal cuts except the syst
      if( TMath::Abs(event.HVdPhi) > (minHVdPhi + bin*k) ){ // syst cuts
	if(sample.data)
	  counts[k]++;
	else
	  counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
      }
}

void TTbarHVdPhiSys( double minHVdPhi, double maxHVdPhi ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  TTbarRegionHZee nominal;
  double bin = (maxHVdPhi - minHVdPhi) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ){ // nominal cuts except the syst
      //      if( TMath::Abs(event.HVdPhi) > (minHVdPhi + bin*k) ) // syst cuts
      if(sample.data)
	counts[k]++;
      else 
	counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
    }
}

void HeavyHVdPhiSys( double minHVdPhi, double maxHVdPhi ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  VbbRegionHZee nominal;
  double bin = (maxHVdPhi - minHVdPhi) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ){ // nominal cuts except the syst
      //      if( TMath::Abs(event.HVdPhi) > (minHVdPhi + bin*k) ) // syst cuts
      if(sample.data)
	counts[k]++;
      else
	counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
    }
}

void LightHmassSys( double minHmass, double maxHmass ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  VlightRegionHmassRelaxedHZee nominal;
  double bin = (maxHmass - minHmass) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ) // nominal cuts except the syst
      if( event.H_mass < (minHmass + bin*k) ){ // syst cuts
	if(sample.data)
	  counts[k]++;
	else
	  counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
      }
}

void TTbarHmassSys( double minHmass, double maxHmass ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  TTbarRegionHZee nominal;
  double bin = (maxHmass - minHmass) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ){ // nominal cuts except the syst
      //      if( event.H_mass > (minHmass + bin*k) ) // syst cuts
      if(sample.data)
	counts[k]++;
      else 
	counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
    }
}

void HeavyHmassSys( double minHmass, double maxHmass ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  VbbRegionHZee nominal;
  double bin = (maxHmass - minHmass) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ){ // nominal cuts except the syst
      //      if( event.H_mass > (minHmass + bin*k) ) // syst cuts
      if(sample.data)
	counts[k]++;
      else 
	counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
    }
}


void LightVmassSys( double minVmass, double maxVmass ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  VlightRegionVmassRelaxedHZee nominal;
  double bin = (maxVmass - minVmass) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ) // nominal cut except the syst
      if( event.V_mass > (minVmass + bin*k) && event.V_mass < ((minVmass + bin*k)+30) ){ // syst cuts 30GeV sliding windows
	if(sample.data)
	  counts[k]++;
	else
	  counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
      }
}

void TTbarVmassSys( double minVmass, double maxVmass ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  TTbarRegionHZee nominal;
  double bin = (maxVmass - minVmass) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ){ // nominal cut except the syst
      //      if( event.V_mass > (minVmass + bin*k) ) // syst cuts
      if(sample.data)
	counts[k]++;
      else
	counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
    }
}

void HeavyVmassSys( double minVmass, double maxVmass ,int nSteps, ntupleReader &event, Sample &sample, std::vector<double>& counts ){
  VbbRegionHZee nominal;
  double bin = (maxVmass - minVmass) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( nominal.pass(event, sample) ){ // nominal cut except the syst
      //      if( event.V_mass > (minVmass + bin*k) ) // syst cuts
      if(sample.data)
	counts[k]++;
      else 
	counts[k] +=  sample.scale(ZeeL,fA,fB)*nominal.weight(event, sample);
    }
}


int main(int argc, char **argv)
{
  bool verbose_ = true;
  std::vector<double> countsLightCR, countsBLightCR;
  std::vector<double> countsTTbarCR, countsBTTbarCR;
  std::vector<double> countsHeavyCR, countsBHeavyCR;

  std::vector< std::vector<double> > countsLightCRCollection;
  std::vector< std::vector<double> > countsLightCRCollectionB;
  std::vector< std::vector<double> > countsTTbarCRCollection;
  std::vector< std::vector<double> > countsTTbarCRCollectionB;
  std::vector< std::vector<double> > countsHeavyCRCollection;
  std::vector< std::vector<double> > countsHeavyCRCollectionB;

  int nSteps=5;

  bool ptSys=false;
  bool addJetSys=true;
  bool HVdPhiSys=false;
  bool HmassSys=false;
  bool VmassSys=false;

  std::vector<Sample> nov1st = Nov1stDiJetPtUpdated();
  std::string Signal("ZH");

  for(size_t iS = 0; iS < nov1st.size(); ++iS ){

    nov1st.at(iS).dump(1);

    TFile* f = nov1st.at(iS).file();
    if(f==0){
      std::cerr << "File not found " << std::endl;
      std::cerr << "Please check the path of this file " << nov1st.at(iS).filename << std::endl;
      return -1;
    }

    countsLightCR.assign(nSteps,0);
    countsBLightCR.assign(nSteps,0);
    countsTTbarCR.assign(nSteps,0);
    countsBTTbarCR.assign(nSteps,0);
    countsHeavyCR.assign(nSteps,0);
    countsBHeavyCR.assign(nSteps,0);

    ntupleReader event(nov1st.at(iS).filename.c_str());
    bool trigger = true;
    Long64_t  entries  = event.fChain->GetEntriesFast();
    //Loop on all events of this file
    for (unsigned int iEvent = 0; iEvent < entries; ++iEvent){
      event.GetEntry(iEvent);

      if(event.EVENT_run > 178078)
	continue;
      if(ptSys){      
	if(event.eventFlav != 5){
	  LightPtSys( 50, 150, nSteps, event, nov1st.at(iS), countsLightCR );
	  TTbarPtSys( 50, 150, nSteps, event, nov1st.at(iS), countsTTbarCR );
	  HeavyPtSys( 50, 150, nSteps, event, nov1st.at(iS), countsHeavyCR );
	}
	else{
	  LightPtSys( 50, 150, nSteps, event, nov1st.at(iS), countsBLightCR );
	  TTbarPtSys( 50, 150, nSteps, event, nov1st.at(iS), countsBTTbarCR );
	  HeavyPtSys( 50, 150, nSteps, event, nov1st.at(iS), countsBHeavyCR );
	}
      }

      if(addJetSys){
	if(event.eventFlav != 5){
	  LightAddJetSys( 0, 5, nSteps, event, nov1st.at(iS), countsLightCR );
	  TTbarAddJetSys( 0, 5, nSteps, event, nov1st.at(iS), countsTTbarCR );
	  HeavyAddJetSys( 0, 5, nSteps, event, nov1st.at(iS), countsHeavyCR );
	}
	else{
	  LightAddJetSys( 0, 5, nSteps, event, nov1st.at(iS), countsBLightCR );
	  TTbarAddJetSys( 0, 5, nSteps, event, nov1st.at(iS), countsBTTbarCR );
	  HeavyAddJetSys( 0, 5, nSteps, event, nov1st.at(iS), countsBHeavyCR );
	}
      }

      if(HVdPhiSys){
	if(event.eventFlav != 5){
	  LightHVdPhiSys( 2.8, 3.1, nSteps, event, nov1st.at(iS), countsLightCR );
	  TTbarHVdPhiSys( 2.8, 3.1, nSteps, event, nov1st.at(iS), countsTTbarCR );
	  HeavyHVdPhiSys( 2.8, 3.1, nSteps, event, nov1st.at(iS), countsHeavyCR );
	}
	else{
	  LightHVdPhiSys( 2.8, 3.1, nSteps, event, nov1st.at(iS), countsBLightCR );
	  TTbarHVdPhiSys( 2.8, 3.1, nSteps, event, nov1st.at(iS), countsBTTbarCR );
	  HeavyHVdPhiSys( 2.8, 3.1, nSteps, event, nov1st.at(iS), countsBHeavyCR );
	}
      }

      if(HmassSys){
	if(event.eventFlav != 5){
	  LightHmassSys( 200, 300, nSteps, event, nov1st.at(iS), countsLightCR );
	  TTbarHmassSys( 200, 300, nSteps, event, nov1st.at(iS), countsTTbarCR );
	  HeavyHmassSys( 200, 300, nSteps, event, nov1st.at(iS), countsHeavyCR );
	}
	else{
	  LightHmassSys( 200, 300, nSteps, event, nov1st.at(iS), countsBLightCR );
	  TTbarHmassSys( 200, 300, nSteps, event, nov1st.at(iS), countsBTTbarCR );
	  HeavyHmassSys( 200, 300, nSteps, event, nov1st.at(iS), countsBHeavyCR );
	}
      }

      if(VmassSys){
	if(event.eventFlav != 5){
	  LightVmassSys( 70, 80, nSteps, event, nov1st.at(iS), countsLightCR );
	  TTbarVmassSys( 70, 80, nSteps, event, nov1st.at(iS), countsTTbarCR );
	  HeavyVmassSys( 70, 80, nSteps, event, nov1st.at(iS), countsHeavyCR );
	}
	else{
	  LightVmassSys( 70, 80, nSteps, event, nov1st.at(iS), countsBLightCR );
	  TTbarVmassSys( 70, 80, nSteps, event, nov1st.at(iS), countsBTTbarCR );
	  HeavyVmassSys( 70, 80, nSteps, event, nov1st.at(iS), countsBHeavyCR );
	}
      }
    }
    
    countsLightCRCollection.push_back(countsLightCR);
    countsLightCRCollectionB.push_back(countsBLightCR);
    countsTTbarCRCollection.push_back(countsTTbarCR);
    countsTTbarCRCollectionB.push_back(countsBTTbarCR);
    countsHeavyCRCollection.push_back(countsHeavyCR);
    countsHeavyCRCollectionB.push_back(countsBHeavyCR);

    std::cout << "Counts LightCR = " << countsLightCR.at(0)+countsBLightCR.at(0) << ".  light = " << countsLightCR.at(0) << " bottom = " << countsBLightCR.at(0)<< std::endl;
    std::cout << "Counts TTbarCR = " << countsTTbarCR.at(0)+countsBTTbarCR.at(0) << ".  light = " << countsTTbarCR.at(0) << " bottom = " << countsBTTbarCR.at(0)<< std::endl;
    std::cout << "Counts HeavyCR = " << countsHeavyCR.at(0)+countsBHeavyCR.at(0) << ".  light = " << countsHeavyCR.at(0) << " bottom = " << countsBHeavyCR.at(0)<< std::endl;
    
  }



  for(unsigned int step = 0; step < nSteps; ++step){
    
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    std::string TTbar("TTbar");      
    Double_t d_light[]={0,0,0};
    Double_t d_ttbar[]={0,0,0};
    Double_t d_heavy[]={0,0,0};
    Double_t d_rest[]={0,0,0};

    for(unsigned int iS=0; iS < nov1st.size(); ++iS){
      if(nov1st.at(iS).name == "DY" || nov1st.at(iS).name == "DYBOOSTED"){
	d_light[0] += countsLightCRCollection.at(iS).at(step);
	d_light[1] += countsTTbarCRCollection.at(iS).at(step);
	d_light[2] += countsHeavyCRCollection.at(iS).at(step);
	d_heavy[0] += countsLightCRCollectionB.at(iS).at(step);
	d_heavy[1] += countsTTbarCRCollectionB.at(iS).at(step);
	d_heavy[2] += countsHeavyCRCollectionB.at(iS).at(step);
      }
      else if(nov1st.at(iS).name == "TTbar"){
	d_ttbar[0] += countsLightCRCollection.at(iS).at(step);
	d_ttbar[1] += countsTTbarCRCollection.at(iS).at(step);
	d_ttbar[2] += countsHeavyCRCollection.at(iS).at(step);
	d_ttbar[0] += countsLightCRCollectionB.at(iS).at(step);
	d_ttbar[1] += countsTTbarCRCollectionB.at(iS).at(step);
	d_ttbar[2] += countsHeavyCRCollectionB.at(iS).at(step);
      }
      else if(nov1st.at(iS).data){
	d_rest[0] += countsLightCRCollection.at(iS).at(step);
	d_rest[1] += countsTTbarCRCollection.at(iS).at(step);
	d_rest[2] += countsHeavyCRCollection.at(iS).at(step);
	d_rest[0] += countsLightCRCollectionB.at(iS).at(step);
	d_rest[1] += countsTTbarCRCollectionB.at(iS).at(step);
	d_rest[2] += countsHeavyCRCollectionB.at(iS).at(step);
      }
      else if(!(nov1st.at(iS).name == Signal)){
	d_rest[0] -= countsLightCRCollection.at(iS).at(step);
	d_rest[1] -= countsTTbarCRCollection.at(iS).at(step);
	d_rest[2] -= countsHeavyCRCollection.at(iS).at(step);
	d_rest[0] -= countsLightCRCollectionB.at(iS).at(step);
	d_rest[1] -= countsTTbarCRCollectionB.at(iS).at(step);
	d_rest[2] -= countsHeavyCRCollectionB.at(iS).at(step);
      }
      
 
    }

    TVectorD v_light; v_light.Use(3,d_light);
    TVectorD v_ttbar; v_ttbar.Use(3,d_ttbar);
    TVectorD v_heavy; v_heavy.Use(3,d_heavy);
    TVectorD v_rest; v_rest.Use(3,d_rest);
    TMatrixD M_A(3,3);
    TMatrixDColumn(M_A,0) = v_light;
    TMatrixDColumn(M_A,1) = v_ttbar;
    TMatrixDColumn(M_A,2) = v_heavy;
    //    TVectorD v_SF = NormalEqn(M_A,v_rest);
    bool ok = true;
    TDecompSVD svd(M_A);
    TVectorD v_SF = svd.Solve(v_rest, ok);
    std::cout << "system results" << std::endl;
    std::cout << "Light SF = " << (double)v_SF[0] <<  std::endl;
    std::cout << "TTbar SF = " << (double)v_SF[1] <<  std::endl;
    std::cout << "Heavy SF = " << (double)v_SF[2] << std::endl;
    
  }

  //   for(unsigned int step = 0; step < nSteps; ++step){
  //     std::cout << "Name\t\t" << "lightL\t\t" << "beautyL\t\t" << "lightT\t\t" << "beautyT\t\t" << "lightH\t\t" << "beautyH\t\t" << std::endl;  
  //     for(unsigned int iS=0; iS < nov1st.size(); iS++){
  //       std::cout << nov1st.at(iS).name << 
  // 	"\t\t" << countsLightCRCollection.at(iS).at(step)  << 
  // 	"\t\t" << countsLightCRCollectionB.at(iS).at(step) <<
  // 	"\t\t" << countsTTbarCRCollection.at(iS).at(step)  << 
  // 	"\t\t" << countsTTbarCRCollectionB.at(iS).at(step) <<
  // 	"\t\t" << countsHeavyCRCollection.at(iS).at(step)  << 
  // 	"\t\t" << countsHeavyCRCollectionB.at(iS).at(step) <<  std::endl; 
  //     }
  //   }

  return 0;
}
