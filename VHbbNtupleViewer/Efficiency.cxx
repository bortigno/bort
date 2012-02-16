#include <TROOT.h>
#include <TApplication.h>
#include <TH1.h>
#include <TCanvas.h>
#include "TGraphAsymmErrors.h"
#include <iostream>
#include "CutsAndHistos.h"
#include "Histos.h"
//#include "Cuts200X.h"
#include "CutsNov11.h"
#include "ntupleReader.h"
#include "sampleCollection.h"

struct simB_c{
  TLorentzVector *simB;
  int simIdx;
  TLorentzVector *assSv;
  int svIdx;
  double assDeltaR(){ return simB->DeltaR(*assSv); };
};


void associator_DR(simB_c &tmpSimb, TLorentzVector & simB, std::vector<TLorentzVector> & svs, double maxDR=1e10 ){

  tmpSimb.svIdx=0;
  tmpSimb.simB=&simB;

  double min=1e10;
  int recob_idx = -1;
  for(int i=0; i<svs.size(); ++i){
    if( simB.DeltaR(svs.at(i)) < min ){
      min = simB.DeltaR(svs.at(i));
      recob_idx = i;
    }
  }
  if(min < maxDR){
    if(recob_idx > 0){
      tmpSimb.assSv = &(svs.at(recob_idx));
      tmpSimb.svIdx = recob_idx;
    }
  }

};

int main(int argc, char **argv){

  bool verbose_=true;

  double fa = 0.46502;
  double fb = 0.53498;
  double eventWeight=0.;

  TH1F* all = new TH1F("all","all",20,0,5);
  TH1F* pass = new TH1F("pass","pass",20,0,5);

  std::vector<Sample> samples =  Nov10Fall1160MTopIVF_forEff();
  
  //loop over all the samples
  for(unsigned int iS=0; iS<samples.size(); ++iS){
    
    std::string name = samples.at(iS).filename;
    samples.at(iS).dump(1,fa,fb);
    std::string inputFile = samples.at(iS).filename;
    
    TFile* f = TFile::Open(inputFile.c_str());
    if(f==0){
      std::cerr << "File not found " << std::endl;
      std::cerr << "Please check the path of this file " << inputFile << std::endl;
      return -1;
    }
    
    ntupleReader event(inputFile.c_str());
    Long64_t  entries  = event.fChain->GetEntriesFast();
    //Loop on all events of this file
    if(verbose_)
      std::cout << "Start looping" << std::endl;
    for (unsigned int iEvent = 0; iEvent < entries; ++iEvent){
      event.GetEntry(iEvent);
      eventWeight = (fa*event.PUweight+fb*event.PUweight2011B)*event.weightTrig;

      std::vector< TLorentzVector > svs;
      svs.clear();
      TLorentzVector sv;
      if(verbose_)
	std::cout << "number of vertices = " << event.nSvs << std::endl;
      for(int i=0; i<event.nSvs;++i){
	if(verbose_)
	  std::cout << "Svs["<<i<<"]" << event.Sv_pt[i]<< "  "<< event.Sv_eta[i] << "  " << event.Sv_phi[i] << "  " << event.Sv_massBCand[i] << std::endl;
	sv.SetPtEtaPhiM(event.Sv_pt[i],event.Sv_eta[i],event.Sv_phi[i],event.Sv_massBCand[i]);
	svs.push_back(sv);
      }
      
      if(verbose_)
	std::cout << "SV filled" << std::endl;

      std::vector<simB_c> AssiSimBs;
      std::vector<TLorentzVector> iSimBs;
      AssiSimBs.clear();
      iSimBs.clear();
      TLorentzVector simB;
      //here you get the simb collection directly from the ntpleReader
      //      std::vector<TLorentzVector> temp = event.SimBs();
      if(verbose_)
	std::cout << "number of sim vertices = " << event.nSimBs << std::endl;

      if(event.nSimBs < 2) continue;
      for(Int_t j=0; j<event.nSimBs; j++){
	if(verbose_)
	  std::cout << "Sim["<<j<<"] " << event.SimBs_pt[j] << "   " << event.SimBs_eta[j] << "  " << event.SimBs_phi[j] << "  " << event.SimBs_mass[j] << std::endl;
	simB.SetPtEtaPhiM(event.SimBs_pt[j],event.SimBs_eta[j],event.SimBs_phi[j],event.SimBs_mass[j]);
	iSimBs.push_back( simB );
	if(svs.size() < 1) continue;
	simB_c tmp;
	associator_DR(tmp,simB,svs);
	AssiSimBs.push_back( tmp );
	if(verbose_)
	  std::cout << "Sim index = "<< AssiSimBs.at(j).svIdx << " RecoSv index  " << event.nSvs << "  pt of the sv = " <<  AssiSimBs.at(j).assSv->Pt() << std::endl; 
	svs.erase(svs.begin()+AssiSimBs.at(j).svIdx);
      }
      if(verbose_){
	std::cout << "simBs1 pt = " << iSimBs.at(0).Pt() << std::endl;
	std::cout << "simBs2 pt = " << iSimBs.at(1).Pt() << std::endl;
	std::cout << "deltaR simBs = " << iSimBs.at(0).DeltaR(iSimBs.at(1)) << std::endl;
      }
      //      all->Fill( iSimBs.at(0).DeltaR(iSimBs.at(1)) );
      if( AssiSimBs.size() > 1 )
	std::cout <<  AssiSimBs.at(0).simB->DeltaR(*AssiSimBs.at(1).assSv) << std::endl;
// 	  && AssiSimBs.at(0).simB->DeltaR(*AssiSimBs.at(0).assSv) < 0.5 
// 	  && AssiSimBs.at(1).simB->DeltaR(*AssiSimBs.at(1).assSv) < 0.5 )
// // 	  && AssiSimBs.at(0).assDeltaR() < 0.5 
// // 	  && AssiSimBs.at(1).assDeltaR() < 0.5 )
// 	std::cout << "pass" << std::endl;
// 	//	pass->Fill( AssiSimBs.at(0).simB->DeltaR(*AssiSimBs.at(1).simB) );
      
    }
  }

  TGraphAsymmErrors * Eff = new TGraphAsymmErrors(pass,all);
  TCanvas *c1 = new TCanvas("c1","c1",600,600);
  Eff->Draw(); 

  c1->Print("IVF_Efficiency","pdf");
 
  return 0;
  
}
