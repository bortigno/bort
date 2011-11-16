#include <TROOT.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
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

#include "controlRegions.h"

// #define ZeeL 3523.64
// #define fA 0.614603
// #define fB 0.385397

#define ZeeL 4683.5
#define fA 0.46502
#define fB 0.53498

TVectorD SF( controlRegion &light, controlRegion &ttbar, controlRegion &heavy ){

  bool debug=false;

  Double_t d_light[] = {light.cDYL()  , ttbar.cDYL()  , heavy.cDYL() };
  Double_t d_ttbar[] = {light.cTTbar(), ttbar.cTTbar(), heavy.cTTbar() };
  Double_t d_heavy[] = {light.cDYB()  , ttbar.cDYB()  , heavy.cDYB() };
  Double_t d_rest[]  = {light.cRest() , ttbar.cRest() , heavy.cRest() };

  if(debug){
    std::cout << "dlight = { " << light.cDYL() << ", " << light.cTTbar() << ", " << light.cDYB()  << " }" << std::endl;
    std::cout << "dttbar = { " << ttbar.cDYL() << ", " << ttbar.cTTbar() << ", " << ttbar.cDYB()  << " }" << std::endl;
    std::cout << "dheavy = { " << heavy.cDYL() << ", " << heavy.cTTbar() << ", " << heavy.cDYB()  << " }" << std::endl;
    std::cout << "drest  = { " << light.cRest() << ", " << ttbar.cRest() << ", " << heavy.cRest() << " }" << std::endl;
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

  if(debug){
    std::cout << "system results" << std::endl;
    std::cout << "Light SF = " << (double)v_SF[0] <<  std::endl;
    std::cout << "TTbar SF = " << (double)v_SF[1] <<  std::endl;
    std::cout << "Heavy SF = " << (double)v_SF[2] << std::endl;
  }

  return v_SF;

}

double eSF(controlRegion & cr){
  bool debug = true;
  double diff = TMath::Abs(cr.cData()-cr.cTotal());
  if(debug){
    std::cout << "diff = " << diff << std::endl;
    std::cout << "data = " << cr.cData() << " pm " << cr.eData() <<  std::endl;
    std::cout << "total mc  = " << cr.cTotal() << " pm " << cr.eTotal() <<  std::endl;
    std::cout << "diff = " << diff << std::endl;
  }
  return ( TMath::Sqrt(TMath::Power(cr.eData()/cr.cTotal(),2) + TMath::Power(cr.eTotal()*diff/(cr.cTotal()*cr.cTotal()),2)) );
}


void f_ptSys( double minPt, double maxPt ,int nSteps, ntupleReader &event, Sample &sample, std::vector<controlRegion> &cr, CutSample &relaxedCut ){
  double bin = (maxPt - minPt) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( event.H_pt > (minPt + bin*k) && event.V_pt > (minPt +bin*k) ) // syst cuts
      cr[k].fill(sample, relaxedCut, event);
}

void f_AddJetSys( double minAddJet, double maxAddJet ,int nSteps, ntupleReader &event, Sample &sample, std::vector<controlRegion> &cr, CutSample &relaxedCut ){
  double bin = (maxAddJet - minAddJet) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( event.CountAddJets() <= (minAddJet + bin*k) ) // syst cuts
      cr[k].fill(sample, relaxedCut, event);
}

void f_HVdPhiSys( double minHVdPhi, double maxHVdPhi ,int nSteps, ntupleReader &event, Sample &sample, std::vector<controlRegion> &cr, CutSample &relaxedCut ){
  double bin = (maxHVdPhi - minHVdPhi) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( TMath::Abs(event.HVdPhi) > (minHVdPhi + bin*k) ) // syst cuts
      cr[k].fill(sample, relaxedCut, event);
}

void f_HmassSys( double minHmass, double maxHmass ,int nSteps, ntupleReader &event, Sample &sample, std::vector<controlRegion> &cr, CutSample &relaxedCut ){
  double bin = (maxHmass - minHmass) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( event.H_mass < (minHmass + bin*k) ) // syst cuts
      cr[k].fill(sample, relaxedCut, event);
}

void f_VmassSys( double minVmass, double maxVmass ,int nSteps, ntupleReader &event, Sample &sample, std::vector<controlRegion> &cr, CutSample & relaxedCut ){
  double bin = (maxVmass - minVmass) / nSteps;
  for(int k = 0; k < nSteps; ++k )
    if( (event.V_mass > (minVmass + bin*k)) && (event.V_mass < ((minVmass + bin*k)+30) ) ) // syst cuts 30GeV sliding windows
      cr[k].fill(sample, relaxedCut, event);
}


int main(int argc, char **argv)
{

  int nSteps=10;

  bool debug=false;
  bool ptSys=true;
  bool addJetSys=true;
  bool HVdPhiSys=true;
  bool HmassSys=true;
  bool VmassSys=true;

  TCanvas * c1 = new TCanvas("c1","c1", 600,600);
  TCanvas * c2 = new TCanvas("c2","c2", 600,600);
  TCanvas * c3 = new TCanvas("c3","c3", 600,600);

  TCanvas * c1e = new TCanvas("c1e","c1e", 600,600);
  TCanvas * c2e = new TCanvas("c2e","c2e", 600,600);
  TCanvas * c3e = new TCanvas("c3e","c3e", 600,600);

  TGraph * g_lightPt = new TGraph(nSteps);
  TGraph * g_lightAddJet = new TGraph(nSteps);
  TGraph * g_lightHVdPhi = new TGraph(nSteps);
  TGraph * g_lightHmass = new TGraph(nSteps);
  TGraph * g_lightVmass = new TGraph(nSteps);

  TGraph * g_ttbarPt = new TGraph(nSteps);
  TGraph * g_ttbarAddJet = new TGraph(nSteps);
  TGraph * g_ttbarHVdPhi = new TGraph(nSteps);
  TGraph * g_ttbarHmass = new TGraph(nSteps);
  TGraph * g_ttbarVmass = new TGraph(nSteps);

  TGraph * g_heavyPt = new TGraph(nSteps);
  TGraph * g_heavyAddJet = new TGraph(nSteps);
  TGraph * g_heavyHVdPhi = new TGraph(nSteps);
  TGraph * g_heavyHmass = new TGraph(nSteps);
  TGraph * g_heavyVmass = new TGraph(nSteps);

  TGraphErrors * eg_lightPt = new TGraphErrors(nSteps);
  TGraphErrors * eg_lightAddJet = new TGraphErrors(nSteps);
  TGraphErrors * eg_lightHVdPhi = new TGraphErrors(nSteps);
  TGraphErrors * eg_lightHmass = new TGraphErrors(nSteps);
  TGraphErrors * eg_lightVmass = new TGraphErrors(nSteps);

  TGraphErrors * eg_ttbarPt = new TGraphErrors(nSteps);
  TGraphErrors * eg_ttbarAddJet = new TGraphErrors(nSteps);
  TGraphErrors * eg_ttbarHVdPhi = new TGraphErrors(nSteps);
  TGraphErrors * eg_ttbarHmass = new TGraphErrors(nSteps);
  TGraphErrors * eg_ttbarVmass = new TGraphErrors(nSteps);

  TGraphErrors * eg_heavyPt = new TGraphErrors(nSteps);
  TGraphErrors * eg_heavyAddJet = new TGraphErrors(nSteps);
  TGraphErrors * eg_heavyHVdPhi = new TGraphErrors(nSteps);
  TGraphErrors * eg_heavyHmass = new TGraphErrors(nSteps);
  TGraphErrors * eg_heavyVmass = new TGraphErrors(nSteps);


  std::vector< CutSample *> nominalCuts;
  std::vector< CutSample *> ptRelaxedCuts;
  std::vector< CutSample *> addJetsRelaxedCuts;
  std::vector< CutSample *> HVdPhiRelaxedCuts;
  std::vector< CutSample *> HmassRelaxedCuts;
  std::vector< CutSample *> VmassRelaxedCuts;

  nominalCuts.push_back( new VlightRegionHZee );
  nominalCuts.push_back( new TTbarRegionHZee );
  //  nominalCuts.push_back( new oldTTbarRegionHZee );
  nominalCuts.push_back( new VbbRegionHZee );

  ptRelaxedCuts.push_back( new VlightRegionPtRelaxedHZee );
  ptRelaxedCuts.push_back( new TTbarRegionPtRelaxedHZee );
  //ptRelaxedCuts.push_back( new oldTTbarRegionHZee );
  ptRelaxedCuts.push_back( new VbbRegionPtRelaxedHZee );

  addJetsRelaxedCuts.push_back( new VlightRegionAddJetRelaxedHZee );
  addJetsRelaxedCuts.push_back( new TTbarRegionAddJetRelaxedHZee );
  //addJetsRelaxedCuts.push_back( new oldTTbarRegionHZee );
  addJetsRelaxedCuts.push_back( new VbbRegionAddJetRelaxedHZee );

  HVdPhiRelaxedCuts.push_back( new VlightRegionHVdPhiRelaxedHZee );
  HVdPhiRelaxedCuts.push_back( new TTbarRegionHVdPhiRelaxedHZee );
  //HVdPhiRelaxedCuts.push_back( new oldTTbarRegionHZee );
  HVdPhiRelaxedCuts.push_back( new VbbRegionHVdPhiRelaxedHZee );

  HmassRelaxedCuts.push_back( new VlightRegionHmassRelaxedHZee );
  HmassRelaxedCuts.push_back( new TTbarRegionHmassRelaxedHZee );
  //HmassRelaxedCuts.push_back( new oldTTbarRegionHZee );
  HmassRelaxedCuts.push_back( new VbbRegionHmassRelaxedHZee );

  VmassRelaxedCuts.push_back( new VlightRegionVmassRelaxedHZee );
  VmassRelaxedCuts.push_back( new TTbarRegionVmassRelaxedHZee );
  //VmassRelaxedCuts.push_back( new oldTTbarRegionHZee );
  VmassRelaxedCuts.push_back( new VbbRegionVmassRelaxedHZee );


  bool verbose_ = true;
  //  vector of control region (0=light, 1=ttbar,2=heavy). I choose vector so it is open to generalisation
  std::vector<controlRegion> nominal;
  std::vector<controlRegion> ptCR;
  std::vector<controlRegion> addJetsCR;
  std::vector<controlRegion> HVdPhiCR;
  std::vector<controlRegion> HmassCR;
  std::vector<controlRegion> VmassCR;
  //collections
  std::vector< std::vector<controlRegion> > pt;
  std::vector< std::vector<controlRegion> > addJets;
  std::vector< std::vector<controlRegion> > HVdPhi;
  std::vector< std::vector<controlRegion> > Hmass;
  std::vector< std::vector<controlRegion> > Vmass;

  double pt_min[] = { 50, 50, 0};
  double pt_max[] = { 150, 150, 100};

  for(int i=0; i<nSteps; ++i){
    nominal.push_back( controlRegion(ZeeL,fA,fB) );
    nominal.at(i).init();
    ptCR.push_back( controlRegion(ZeeL,fA,fB) );
    ptCR.at(i).init();
    addJetsCR.push_back( controlRegion(ZeeL,fA,fB) );
    addJetsCR.at(i).init();
    HVdPhiCR.push_back( controlRegion(ZeeL,fA,fB) );
    HVdPhiCR.at(i).init();
    HmassCR.push_back( controlRegion(ZeeL,fA,fB) );
    HmassCR.at(i).init();
    VmassCR.push_back( controlRegion(ZeeL,fA,fB) );
    VmassCR.at(i).init(); 
  }
  
  for(int k=0; k<3;++k){
    pt.push_back( ptCR );
    addJets.push_back( addJetsCR );
    HVdPhi.push_back( HVdPhiCR );
    Hmass.push_back( HmassCR );
    Vmass.push_back( VmassCR );
  }
  
  //  std::vector<Sample> nov1st = Nov1stDiJetPtUpdated();
  std::vector<Sample> nov1st = Nov10thDiJetPtUpdated();
  //  std::vector<Sample> nov1st = testSample();
  
  for(size_t iS = 0; iS < nov1st.size(); ++iS ){
    
    nov1st.at(iS).dump(1);
    
    TFile* f = nov1st.at(iS).file();
    if(f==0){
      std::cerr << "File not found " << std::endl;
      std::cerr << "Please check the path of this file " << nov1st.at(iS).filename << std::endl;
      return -1;
    }
    
    ntupleReader event(nov1st.at(iS).filename.c_str());
    bool trigger = true;
    Long64_t  entries  = event.fChain->GetEntriesFast();
    //Loop on all events of this file
    for (unsigned int iEvent = 0; iEvent < entries; ++iEvent){
      event.GetEntry(iEvent);
      
      //       if(event.EVENT_run > 178078)
      // 	continue;

      //loop over control region light, ttbar, heavy
      for(int i =0; i<3; ++i){
	nominal.at(i).fill( nov1st.at(iS), *nominalCuts.at(i) , event );
	
	if(ptSys)
	  f_ptSys( pt_min[i], pt_max[i], nSteps, event, nov1st.at(iS), pt.at(i), *ptRelaxedCuts.at(i) );
	if(addJetSys)
	  f_AddJetSys( 0, 5, nSteps, event, nov1st.at(iS), addJets.at(i), *addJetsRelaxedCuts.at(i) );
	if(HVdPhiSys)
	  f_HVdPhiSys( 2.8, 3.1, nSteps, event, nov1st.at(iS), HVdPhi.at(i), *HVdPhiRelaxedCuts.at(i) );
	if(HmassSys)
	  f_HmassSys( 200, 300, nSteps, event, nov1st.at(iS), Hmass.at(i), *HmassRelaxedCuts.at(i) );
	if(VmassSys)
	  f_VmassSys( 70, 80, nSteps, event, nov1st.at(iS), Vmass.at(i), *VmassRelaxedCuts.at(i) );
      
      }


    }
        
  }

  if(debug){
    for(int i=0; i<3; ++i){
      std::cout << "nominal.at("<< i <<") DYL = " << nominal.at(i).cDYL() << std::endl;
      std::cout << "nominal.at("<< i <<") DYB = " << nominal.at(i).cDYB() << std::endl;
      std::cout << "nominal.at("<< i <<") ttbar = " << nominal.at(i).cTTbar() << std::endl;
      std::cout << "nominal.at("<< i <<") rest = " << nominal.at(i).cRest() << std::endl;
    }
  }
  

  std::vector<TVectorD> SFsLightVar;
  std::vector<TVectorD> SFsTTbarVar;
  std::vector<TVectorD> SFsHeavyVar;
  
  TVectorD SFsNominal = SF( nominal[0], nominal[1], nominal[2] );

  std::cout << "########### System results ###########" << std::endl;
  std::cout << "-------------- Nominal values ----------- " << std::endl;
  std::cout << "Light SF = " << (double)SFsNominal[0] <<  std::endl;
  std::cout << "TTbar SF = " << (double)SFsNominal[1] <<  std::endl;
  std::cout << "Heavy SF = " << (double)SFsNominal[2] << std::endl;

  for(int k=0; k<nSteps;++k){
    if(ptSys){
      SFsLightVar.push_back( SF( pt.at(0)[k], nominal[1], nominal[2]) );
      SFsTTbarVar.push_back( SF( nominal[0], pt.at(1)[k], nominal[2]) );   
      SFsHeavyVar.push_back( SF( nominal[0], nominal[1], pt.at(2)[k]) );
      g_lightPt->SetPoint(k, k, SF(pt.at(0)[k], nominal[1], nominal[2])[0] );
      g_ttbarPt->SetPoint(k, k, SF(nominal[0], pt.at(1)[k], nominal[2])[1] );
      g_heavyPt->SetPoint(k, k, SF(nominal[0], nominal[1], pt.at(2)[k])[2] );
      //with errors
      eg_lightPt->SetPoint(k, k, SF(pt.at(0)[k], nominal[1], nominal[2])[0]  );
      eg_ttbarPt->SetPoint(k, k, SF(nominal[0], pt.at(1)[k], nominal[2])[1]  );
      eg_heavyPt->SetPoint(k, k, SF(nominal[0], nominal[1], pt.at(2)[k])[2]  );
      eg_lightPt->SetPointError(k, 0, eSF(pt.at(0)[k])  );
      eg_ttbarPt->SetPointError(k, 0, eSF(pt.at(1)[k])  );
      eg_heavyPt->SetPointError(k, 0, eSF(pt.at(2)[k])  );
    }
    
    if(addJetSys){
      SFsLightVar.push_back( SF( addJets.at(0)[k], nominal[1], nominal[2]) );
      SFsTTbarVar.push_back( SF( nominal[0], addJets.at(1)[k], nominal[2]) );   
      SFsHeavyVar.push_back( SF( nominal[0], nominal[1], addJets.at(2)[k]) );
      g_lightAddJet->SetPoint(k, k, SF(addJets.at(0)[k], nominal[1], nominal[2])[0] );
      g_ttbarAddJet->SetPoint(k, k, SF(nominal[0], addJets.at(1)[k], nominal[2])[1] );
      g_heavyAddJet->SetPoint(k, k, SF(nominal[0], nominal[1], addJets.at(2)[k])[2] );
      //with errors
      eg_lightAddJet->SetPoint(k, k, SF(addJets.at(0)[k], nominal[1], nominal[2])[0] );
      eg_ttbarAddJet->SetPoint(k, k, SF(nominal[0], addJets.at(1)[k], nominal[2])[1] );
      eg_heavyAddJet->SetPoint(k, k, SF(nominal[0], nominal[1], addJets.at(2)[k])[2] );
      eg_lightAddJet->SetPointError(k, 0, eSF(addJets.at(0)[k])  );
      eg_ttbarAddJet->SetPointError(k, 0, eSF(addJets.at(1)[k])  );
      eg_heavyAddJet->SetPointError(k, 0, eSF(addJets.at(2)[k])  );
    }
    
    if(HVdPhiSys){
      SFsLightVar.push_back( SF( HVdPhi[0][k], nominal[1], nominal[2]) );
      SFsTTbarVar.push_back( SF( nominal[0], HVdPhi[1][k], nominal[2]) );
      SFsHeavyVar.push_back( SF( nominal[0], nominal[1], HVdPhi[2][k]) );
      g_lightHVdPhi->SetPoint(k, k, SF(HVdPhi[0][k], nominal[1], nominal[2])[0] );
      g_ttbarHVdPhi->SetPoint(k, k, SF(nominal[0], HVdPhi[1][k], nominal[2])[1] );
      g_heavyHVdPhi->SetPoint(k, k, SF(nominal[0], nominal[1], HVdPhi[2][k])[2] );
      //with errors
      eg_lightHVdPhi->SetPoint(k, k, SF(HVdPhi.at(0)[k], nominal[1], nominal[2])[0] );
      eg_ttbarHVdPhi->SetPoint(k, k, SF(nominal[0], HVdPhi.at(1)[k], nominal[2])[1] );
      eg_heavyHVdPhi->SetPoint(k, k, SF(nominal[0], nominal[1], HVdPhi.at(2)[k])[2] );
      eg_lightHVdPhi->SetPointError(k, 0, eSF(HVdPhi.at(0)[k])  );
      eg_ttbarHVdPhi->SetPointError(k, 0, eSF(HVdPhi.at(1)[k])  );
      eg_heavyHVdPhi->SetPointError(k, 0, eSF(HVdPhi.at(2)[k])  );
    }
    
    if(HmassSys){
      SFsLightVar.push_back( SF( Hmass[0][k], nominal[1], nominal[2]) );
      SFsTTbarVar.push_back( SF( nominal[0], Hmass[1][k], nominal[2]) );
      SFsHeavyVar.push_back( SF( nominal[0], nominal[1], Hmass[2][k]) );
      g_lightHmass->SetPoint(k, k, SF(Hmass[0][k], nominal[1], nominal[2])[0] );
      g_ttbarHmass->SetPoint(k, k, SF(nominal[0], Hmass[1][k], nominal[2])[1] );
      g_heavyHmass->SetPoint(k, k, SF(nominal[0], nominal[1], Hmass[2][k])[2] );
      //with errors
      eg_lightHmass->SetPoint(k, k, SF(Hmass.at(0)[k], nominal[1], nominal[2])[0] );
      eg_ttbarHmass->SetPoint(k, k, SF(nominal[0], Hmass.at(1)[k], nominal[2])[1] );
      eg_heavyHmass->SetPoint(k, k, SF(nominal[0], nominal[1], Hmass.at(2)[k])[2] );
      eg_lightHmass->SetPointError(k, 0, eSF(Hmass.at(0)[k])  );
      eg_ttbarHmass->SetPointError(k, 0, eSF(Hmass.at(1)[k])  );
      eg_heavyHmass->SetPointError(k, 0, eSF(Hmass.at(2)[k])  );
    }
    
    if(VmassSys){
      SFsLightVar.push_back( SF( Vmass[0][k], nominal[1], nominal[2]) );
      SFsTTbarVar.push_back( SF( nominal[0], Vmass[1][k], nominal[2]) );
      SFsHeavyVar.push_back( SF( nominal[0], nominal[1], Vmass[2][k]) );
      g_lightVmass->SetPoint(k, k, SF(Vmass[0][k], nominal[1], nominal[2])[0] );
      g_ttbarVmass->SetPoint(k, k, SF(nominal[0], Vmass[1][k], nominal[2])[1] );
      g_heavyVmass->SetPoint(k, k, SF(nominal[0], nominal[1], Vmass[2][k])[2] );
      //with errors
      eg_lightVmass->SetPoint(k, k, SF(Vmass.at(0)[k], nominal[1], nominal[2])[0] );
      eg_ttbarVmass->SetPoint(k, k, SF(nominal[0], Vmass.at(1)[k], nominal[2])[1] );
      eg_heavyVmass->SetPoint(k, k, SF(nominal[0], nominal[1], Vmass.at(2)[k])[2] );
      eg_lightVmass->SetPointError(k, 0, eSF(Vmass.at(0)[k])  );
      eg_ttbarVmass->SetPointError(k, 0, eSF(Vmass.at(1)[k])  );
      eg_heavyVmass->SetPointError(k, 0, eSF(Vmass.at(2)[k])  );
    }
  }
  
  
  //  plotting

  c1->cd();
  g_lightPt->SetTitle("Light control region DYL SF scan");
  g_lightPt->SetLineColor(2);
  g_lightAddJet->SetLineColor(3);
  g_lightHVdPhi->SetLineColor(4);
  g_lightHmass->SetLineColor(5);
  g_lightVmass->SetLineColor(6);
  g_lightPt->SetFillColor(kWhite);
  g_lightAddJet->SetFillColor(kWhite);
  g_lightHVdPhi->SetFillColor(kWhite);
  g_lightHmass->SetFillColor(kWhite);
  g_lightVmass->SetFillColor(kWhite);
  g_lightPt->GetYaxis()->SetRangeUser(0.5, 1.5);
  g_lightPt->Draw("AL");
  g_lightAddJet->Draw("L SAME");
  g_lightHVdPhi->Draw("L SAME");
  g_lightHmass->Draw("L SAME");
  g_lightVmass->Draw("L SAME");
  TLegend * leg_light = new TLegend(  0.55, 0.65, 0.88, 0.88 );
  leg_light->SetFillColor(kWhite);
  leg_light->SetBorderSize(0);
  leg_light->AddEntry(g_lightPt,"H_pt,V_pt 50 - 150");
  leg_light->AddEntry(g_lightAddJet,"AddJet 0 - 5");
  leg_light->AddEntry(g_lightHVdPhi,"HVdPhi 2.8 - 3.1");
  leg_light->AddEntry(g_lightHmass,"H_mass max 200 - 300");
  leg_light->AddEntry(g_lightVmass,"V_mass window 70-100 80-110");
  leg_light->Draw("SAME");
  c1->Print("lightFullScan.pdf","pdf");

 
  c2->cd();
  g_ttbarPt->SetTitle("TTbar control region TTbar SF scan");
  g_ttbarPt->SetLineColor(2);
  g_ttbarAddJet->SetLineColor(3);
  g_ttbarHVdPhi->SetLineColor(4);
  g_ttbarHmass->SetLineColor(5);
  g_ttbarVmass->SetLineColor(6);
  g_ttbarPt->SetFillColor(kWhite);
  g_ttbarAddJet->SetFillColor(kWhite);
  g_ttbarHVdPhi->SetFillColor(kWhite);
  g_ttbarHmass->SetFillColor(kWhite);
  g_ttbarVmass->SetFillColor(kWhite);
  g_ttbarPt->GetYaxis()->SetRangeUser(0.5, 1.5);
  g_ttbarPt->Draw("AL");
  g_ttbarAddJet->Draw("L SAME");
  g_ttbarHVdPhi->Draw("L SAME");
  g_ttbarHmass->Draw("L SAME");
  g_ttbarVmass->Draw("L SAME");
  TLegend * leg_ttbar = new TLegend(  0.25, 0.5, 0.58, 0.28 );
  leg_ttbar->SetFillColor(kWhite);
  leg_ttbar->SetBorderSize(0);
  leg_ttbar->AddEntry(g_ttbarPt,"H_pt,V_pt 50 - 150");
  leg_ttbar->AddEntry(g_ttbarAddJet,"AddJet 0 - 5");
  leg_ttbar->AddEntry(g_ttbarHVdPhi,"HVdPhi 2.8 - 3.1");
  leg_ttbar->AddEntry(g_ttbarHmass,"H_mass max 200 - 300");
  leg_ttbar->AddEntry(g_ttbarVmass,"V_mass window 70-100 80-110");
  leg_ttbar->Draw("SAME");
  c2->Print("ttbarFullScan.pdf","pdf");

  c3->cd();
  g_heavyPt->SetTitle("Heavy control region DYB SF scan");
  g_heavyPt->SetLineColor(2);
  g_heavyAddJet->SetLineColor(3);
  g_heavyHVdPhi->SetLineColor(4);
  g_heavyHmass->SetLineColor(5);
  g_heavyVmass->SetLineColor(6);
  g_heavyPt->SetFillColor(kWhite);
  g_heavyAddJet->SetFillColor(kWhite);
  g_heavyHVdPhi->SetFillColor(kWhite);
  g_heavyHmass->SetFillColor(kWhite);
  g_heavyVmass->SetFillColor(kWhite);
  g_heavyPt->GetYaxis()->SetRangeUser(0.5, 1.5);
  g_heavyPt->Draw("AL");
  g_heavyAddJet->Draw("L SAME");
  g_heavyHVdPhi->Draw("L SAME");
  g_heavyHmass->Draw("L SAME");
  g_heavyVmass->Draw("L SAME");
  TLegend * leg_heavy = new TLegend(  0.55, 0.65, 0.88, 0.88 );
  leg_heavy->SetFillColor(kWhite);
  leg_heavy->SetBorderSize(0);
  leg_heavy->AddEntry(g_heavyPt,"H_pt,V_pt 0 - 100");
  leg_heavy->AddEntry(g_heavyAddJet,"AddJet 0 - 5");
  leg_heavy->AddEntry(g_heavyHVdPhi,"HVdPhi 2.8 - 3.1");
  leg_heavy->AddEntry(g_heavyHmass,"H_mass max 200 - 300");
  leg_heavy->AddEntry(g_heavyVmass,"V_mass windows 70-100 80-110 ");
  leg_heavy->Draw("SAME");
  c3->Print("heavyFullScan.pdf","pdf");  



  c1e->cd();
  eg_lightPt->SetTitle("Light control region DYL SF scan");
  eg_lightPt->SetLineColor(2);
  eg_lightAddJet->SetLineColor(3);
  eg_lightHVdPhi->SetLineColor(4);
  eg_lightHmass->SetLineColor(5);
  eg_lightVmass->SetLineColor(6);
  eg_lightPt->SetFillColor(kWhite);
  eg_lightAddJet->SetFillColor(kWhite);
  eg_lightHVdPhi->SetFillColor(kWhite);
  eg_lightHmass->SetFillColor(kWhite);
  eg_lightVmass->SetFillColor(kWhite);
  eg_lightPt->GetYaxis()->SetRangeUser(0.5, 1.5);
  eg_lightPt->Draw("AL");
  eg_lightAddJet->Draw("L SAME");
  eg_lightHVdPhi->Draw("L SAME");
  eg_lightHmass->Draw("L SAME");
  eg_lightVmass->Draw("L SAME");
  TLegend * legE_light = new TLegend(  0.25, 0.5, 0.58, 0.28 );
  legE_light->SetFillColor(kWhite);
  legE_light->SetBorderSize(0);
  legE_light->AddEntry(eg_lightPt,"H_pt,V_pt 50 - 150");
  legE_light->AddEntry(eg_lightAddJet,"AddJet 0 - 5");
  legE_light->AddEntry(eg_lightHVdPhi,"HVdPhi 2.8 - 3.1");
  legE_light->AddEntry(eg_lightHmass,"H_mass max 200 - 300");
  legE_light->AddEntry(eg_lightVmass,"V_mass window 70-100 80-110");
  legE_light->Draw("SAME");
  c1e->Print("lightFullScanError.pdf","pdf");


  c2e->cd();
  eg_ttbarPt->SetTitle("TTbar control region TTbar SF scan");
  eg_ttbarPt->SetLineColor(2);
  eg_ttbarAddJet->SetLineColor(3);
  eg_ttbarHVdPhi->SetLineColor(4);
  eg_ttbarHmass->SetLineColor(5);
  eg_ttbarVmass->SetLineColor(6);
  eg_ttbarPt->SetFillColor(kWhite);
  eg_ttbarAddJet->SetFillColor(kWhite);
  eg_ttbarHVdPhi->SetFillColor(kWhite);
  eg_ttbarHmass->SetFillColor(kWhite);
  eg_ttbarVmass->SetFillColor(kWhite);
  eg_ttbarPt->GetYaxis()->SetRangeUser(0.5, 1.5);
  eg_ttbarPt->Draw("AL");
  eg_ttbarAddJet->Draw("L SAME");
  eg_ttbarHVdPhi->Draw("L SAME");
  eg_ttbarHmass->Draw("L SAME");
  eg_ttbarVmass->Draw("L SAME");
  TLegend * legE_ttbar = new TLegend(  0.25, 0.5, 0.58, 0.28 );
  legE_ttbar->SetFillColor(kWhite);
  legE_ttbar->SetBorderSize(0);
  legE_ttbar->AddEntry(eg_ttbarPt,"H_pt,V_pt 50 - 150");
  legE_ttbar->AddEntry(eg_ttbarAddJet,"AddJet 0 - 5");
  legE_ttbar->AddEntry(eg_ttbarHVdPhi,"HVdPhi 2.8 - 3.1");
  legE_ttbar->AddEntry(eg_ttbarHmass,"H_mass max 200 - 300");
  legE_ttbar->AddEntry(eg_ttbarVmass,"V_mass window 70-100 80-110");
  legE_ttbar->Draw("SAME");
  c2e->Print("ttbarFullScanError.pdf","pdf");  


  c3e->cd();
  eg_heavyPt->SetTitle("Heavy control region DYB SF scan");
  eg_heavyPt->SetLineColor(2);
  eg_heavyAddJet->SetLineColor(3);
  eg_heavyHVdPhi->SetLineColor(4);
  eg_heavyHmass->SetLineColor(5);
  eg_heavyVmass->SetLineColor(6);
  eg_heavyPt->SetFillColor(kWhite);
  eg_heavyAddJet->SetFillColor(kWhite);
  eg_heavyHVdPhi->SetFillColor(kWhite);
  eg_heavyHmass->SetFillColor(kWhite);
  eg_heavyVmass->SetFillColor(kWhite);
  eg_heavyPt->GetYaxis()->SetRangeUser(0.5, 1.5);
  eg_heavyPt->Draw("AL");
  eg_heavyAddJet->Draw("L SAME");
  eg_heavyHVdPhi->Draw("L SAME");
  eg_heavyHmass->Draw("L SAME");
  eg_heavyVmass->Draw("L SAME");
  TLegend * legE_heavy = new TLegend(  0.25, 0.5, 0.58, 0.28 );
  legE_heavy->SetFillColor(kWhite);
  legE_heavy->SetBorderSize(0);
  legE_heavy->AddEntry(eg_heavyPt,"H_pt,V_pt 50 - 150");
  legE_heavy->AddEntry(eg_heavyAddJet,"AddJet 0 - 5");
  legE_heavy->AddEntry(eg_heavyHVdPhi,"HVdPhi 2.8 - 3.1");
  legE_heavy->AddEntry(eg_heavyHmass,"H_mass max 200 - 300");
  legE_heavy->AddEntry(eg_heavyVmass,"V_mass window 70-100 80-110");
  legE_heavy->Draw("SAME");
  c3e->Print("heavyFullScanError.pdf","pdf");  


  for(int i = 0; i < SFsLightVar.size(); ++i ){
    std::cout << "-- Iteration " << i << " Ligth Variation \t TTbar Variation \t Heavy Variation ----------- " << std::endl;
    std::cout << "Light SF = " << (double)SFsLightVar.at(i)[0] << "\t" << (double)SFsTTbarVar.at(i)[0] << "\t" << (double)SFsHeavyVar.at(i)[0] <<  std::endl;
    std::cout << "TTbar SF = " << (double)SFsLightVar.at(i)[1] << "\t" << (double)SFsTTbarVar.at(i)[1] << "\t" << (double)SFsHeavyVar.at(i)[1] << std::endl;
    std::cout << "Heavy SF = " << (double)SFsLightVar.at(i)[2] << "\t" << (double)SFsTTbarVar.at(i)[2] << "\t" << (double)SFsHeavyVar.at(i)[2] << std::endl;
  }



//   //deleting the controlRegions
//   for(int i=0; i<3; ++i){
//     delete[] nominal.at(i);
//     for(int k=0; k<nSteps;++k){
//       delete[] pt.at(k).at(i);
//       delete[] addJets.at(k).at(i);
//       delete[] HVdPhi.at(k).at(i);
//       delete[] Hmass.at(k).at(i);
//       delete[] Vmass.at(k).at(i);
//     }
//   }

  return 0;
}
