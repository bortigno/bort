#ifndef HISTOS_H
#define HISTOS_H

#include <TH1F.h>
/* #include "DataFormats/GeometryVector/interface/VectorUtil.h" */
/* #include "DataFormats/Math/interface/deltaR.h" */
#include "CutsAndHistos.h"
#include "TLorentzVector.h"
#include <sstream>
#include "TKey.h"
#include "TMVA/Reader.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/MethodCuts.h"


class MCHistos : public Histos {
  
public:

  virtual void book(TFile &f, std::string suffix) {

    TDirectory *subDir;

    if( ! f.GetDirectory(suffix.c_str()) )
      subDir = f.mkdir(suffix.c_str());
    else 
      subDir = f.GetDirectory(suffix.c_str());

    subDir->cd();

    bin_mass = 500;
    min_mass = 0;
    max_mass = 300;
    
    bin_pt = 500;
    min_pt = 0;
    max_pt = 500;
    
    bin_hel = 50;
    min_hel = 0;
    max_hel = 1;

    //from MC
    McH_simHMass = new TH1F(("simHiggsMass"+suffix).c_str(),("Sim Higgs Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass );
    McH_simHPt = new TH1F(("simHiggsPt"+suffix).c_str(),("Sim Higgs Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );
    McH_simZMass = new TH1F(("simZMass"+suffix).c_str(),("Sim Z Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass );
    McH_simZPt = new TH1F(("simZPt"+suffix).c_str(),("Sim Z Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );
    McH_simWMass = new TH1F(("simWMass"+suffix).c_str(),("Sim W Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass );
    McH_simWPt = new TH1F(("simWPt"+suffix).c_str(),("Sim W Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );

  }
  
  virtual void fill(ntupleReader &iEvent,float w) {

    //     McH_simWPt->Fill(iAuxInfo->mcW[0].p4.Pt(), w); 

  }


  TH1F * McH_simHMass;
  TH1F * McH_simHPt;
  TH1F * McH_simWMass;
  TH1F * McH_simWPt;
  TH1F * McH_simZMass;
  TH1F * McH_simZPt;
 
private:

  Int_t bin_mass;
  Double_t min_mass;
  Double_t max_mass;

  Int_t bin_pt;
  Double_t min_pt;
  Double_t max_pt;

  Int_t bin_hel;
  Double_t min_hel;
  Double_t max_hel;


};


class BTagHistos : public Histos {

public:
  
  virtual void book(TFile &f, std::string suffix) {
    
    TDirectory *subDir;
    if( ! f.GetDirectory(suffix.c_str()) )
      subDir = f.mkdir(suffix.c_str());
    else 
      subDir = f.GetDirectory(suffix.c_str());
    subDir->cd();
    
    bin_btag_prob = 20;
    min_btag_prob = 0;
    max_btag_prob = 1;

    bin_btag_count = 10;
    min_btag_count = 0;
    max_btag_count = 10;

    //Candidates
    BTagH_bJet1_csv = new TH1F(("BJet1_CSV"+suffix).c_str(),("BJet1 CSV ("+suffix+")").c_str(), bin_btag_prob, min_btag_prob, max_btag_prob );
    BTagH_bJet2_csv = new TH1F(("BJet2_CSV"+suffix).c_str(),("BJet2 CSV ("+suffix+")").c_str(), bin_btag_prob, min_btag_prob, max_btag_prob );
/*     BTagH_bJet1_csvmva = new TH1F(("BJet1_CSVMVA"+suffix).c_str(),("BJet1 CSVMVA ("+suffix+")").c_str(), bin_btag_prob, min_btag_prob, max_btag_prob ); */
/*     BTagH_bJet2_csvmva = new TH1F(("BJet2_CSVMVA"+suffix).c_str(),("BJet2 CSVMVA ("+suffix+")").c_str(), bin_btag_prob, min_btag_prob, max_btag_prob ); */
/*     BTagH_bJet1_ssvhe = new TH1F(("BJet1_SSVHE"+suffix).c_str(),("BJet1 SSVHE ("+suffix+")").c_str(), bin_btag_prob, min_btag_prob, max_btag_prob ); */
/*     BTagH_bJet2_ssvhe = new TH1F(("BJet2_SSVHE"+suffix).c_str(),("BJet2 SSVHE ("+suffix+")").c_str(), bin_btag_prob, min_btag_prob, max_btag_prob ); */
/*     BTagH_bJet1_jpb = new TH1F(("BJet1_JPB"+suffix).c_str(),("BJet1 JPB ("+suffix+")").c_str(), bin_btag_prob, min_btag_prob, max_btag_prob ); */
/*     BTagH_bJet2_jpb = new TH1F(("BJet2_JPB"+suffix).c_str(),("BJet2 JPB ("+suffix+")").c_str(), bin_btag_prob, min_btag_prob, max_btag_prob ); */
/*     BTagH_bJet1_tche = new TH1F(("BJet1_TCHE"+suffix).c_str(),("BJet1 TCHE ("+suffix+")").c_str(), bin_btag_count, min_btag_count, max_btag_count ); */
/*     BTagH_bJet2_tche = new TH1F(("BJet2_TCHE"+suffix).c_str(),("BJet2 TCHE ("+suffix+")").c_str(), bin_btag_count, min_btag_count, max_btag_count ); */
/*     BTagH_bJet1_jp = new TH1F(("BJet1_JP"+suffix).c_str(),("BJet1 JP ("+suffix+")").c_str(), bin_btag_prob, min_btag_prob, max_btag_prob ); */
/*     BTagH_bJet2_jp = new TH1F(("BJet2_JP"+suffix).c_str(),("BJet2 JP ("+suffix+")").c_str(), bin_btag_prob, min_btag_prob, max_btag_prob ); */
/*     BTagH_bJet1_tchp = new TH1F(("BJet1_TCHP"+suffix).c_str(),("BJet1 TCHP ("+suffix+")").c_str(), bin_btag_count, min_btag_count, max_btag_count ); */
/*     BTagH_bJet2_tchp = new TH1F(("BJet2_TCHP"+suffix).c_str(),("BJet2 TCHP ("+suffix+")").c_str(), bin_btag_count, min_btag_count, max_btag_count ); */

  }
  
  virtual void fill(ntupleReader &iEvent,float w) {
      
      BTagH_bJet1_csv->Fill(iEvent.hJet_csv[0], w);
      BTagH_bJet2_csv->Fill(iEvent.hJet_csv[1], w);
/*       BTagH_bJet1_csvmva->Fill(iEvent.H.jets.at(0).csvmva, w); */
/*       BTagH_bJet2_csvmva->Fill(iEvent.H.jets.at(1).csvmva, w); */
/*       BTagH_bJet1_ssvhe->Fill(iEvent.H.jets.at(0).ssvhe, w); */
/*       BTagH_bJet2_ssvhe->Fill(iEvent.H.jets.at(1).ssvhe, w); */
/*       BTagH_bJet1_tche->Fill(iEvent.H.jets.at(0).tche, w); */
/*       BTagH_bJet2_tche->Fill(iEvent.H.jets.at(1).tche, w); */
/*       BTagH_bJet1_tchp->Fill(iEvent.H.jets.at(0).tchp, w); */
/*       BTagH_bJet2_tchp->Fill(iEvent.H.jets.at(1).tchp, w); */
/*       BTagH_bJet1_jpb->Fill(iEvent.H.jets.at(0).jpb, w); */
/*       BTagH_bJet2_jpb->Fill(iEvent.H.jets.at(1).jpb, w); */
/*       BTagH_bJet1_jp->Fill(iEvent.H.jets.at(0).jp, w); */
/*       BTagH_bJet2_jp->Fill(iEvent.H.jets.at(1).jp, w); */
      

  }
  
  TH1F * BTagH_bJet1_csv;
  TH1F * BTagH_bJet2_csv;
/*   TH1F * BTagH_bJet1_csvmva; */
/*   TH1F * BTagH_bJet2_csvmva; */
/*   TH1F * BTagH_bJet1_ssvhe; */
/*   TH1F * BTagH_bJet2_ssvhe; */
/*   TH1F * BTagH_bJet1_jpb; */
/*   TH1F * BTagH_bJet2_jpb; */
/*   TH1F * BTagH_bJet1_tche; */
/*   TH1F * BTagH_bJet2_tche; */
/*   TH1F * BTagH_bJet1_jp; */
/*   TH1F * BTagH_bJet2_jp; */
/*   TH1F * BTagH_bJet1_tchp; */
/*   TH1F * BTagH_bJet2_tchp; */
 
private:

  Int_t bin_btag_prob;
  Double_t min_btag_prob;
  Double_t max_btag_prob;
  
  Int_t bin_btag_count;
  Double_t min_btag_count;
  Double_t max_btag_count;
  
};
  

class CountHisto : public Histos {
  virtual void book(TFile &f, std::string suffix) { 
    
    TDirectory *subDir;
    if( ! f.GetDirectory(suffix.c_str()) )
      subDir = f.mkdir(suffix.c_str());
    else 
      subDir = f.GetDirectory(suffix.c_str());
    subDir->cd();
    count = new TH1F(("Count"+suffix).c_str(),("Count ("+suffix+")").c_str(), 1,0,2 );
  }
  virtual void fill( ntupleReader & event, float w){
    count->Fill(1, w);
  }
  
  TH1F * count;
};


class StandardHistos : public Histos {
    
public:

  virtual void book(TFile &f, std::string suffix) {

    TDirectory *subDir;
    if( ! f.GetDirectory(suffix.c_str()) )
      subDir = f.mkdir(suffix.c_str());
    else 
      subDir = f.GetDirectory(suffix.c_str());
    subDir->cd();

    bin_mass = 30;
    min_mass = 0;
    max_mass = 300;
    
    bin_SVmass = 50;
    min_SVmass = 0;
    max_SVmass = 10;

    bin_pt = 50;
    min_pt = 0;
    max_pt = 500;
    
    bin_hel = 10;
    min_hel = 0;
    max_hel = 1;

    bin_dxy = 20;
    min_dxy = -0.2;
    max_dxy = 0.2;

    bin_iso = 20;
    min_iso = 0;
    max_iso = 0.5;

    bin_btag = 20;
    min_btag = 0;
    max_btag = 1;

    bin_npvs = 30;
    min_npvs = 0;
    max_npvs = 30;

    bin_addJets = 10;
    min_addJets = 0;
    max_addJets = 10;

    bin_eta = bin_phi = 20;
    min_eta = min_phi = -5;
    max_eta = max_phi = 5;

    bin_deltaR = bin_deltaPhi = bin_deltaEta = 20;
    min_deltaR = min_deltaPhi = min_deltaEta = 0;
    max_deltaR = max_deltaPhi = max_deltaEta = 5;

    //Candidates
    StH_nPVs = new TH1F(("nPVs"+suffix).c_str(),("Number of reconstructed PV ("+suffix+")").c_str(), bin_npvs, min_npvs, max_npvs );
    StH_addJets = new TH1F(("addJets"+suffix).c_str(),("Number of additional AK5 ("+suffix+")").c_str(), bin_addJets, min_addJets, max_addJets );

    StH_met_et = new TH1F(("MET_et"+suffix).c_str(),("Missing transverse energy ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.5 );
    StH_met_sig = new TH1F(("MET_sig"+suffix).c_str(),("MET significance("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.1 );

    StH_vectorLepton1_pt = new TH1F(("vectorLepton1_pt"+suffix).c_str(),("Vector Lepton1 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    StH_vectorLepton2_pt = new TH1F(("vectorLepton2_pt"+suffix).c_str(),("Vector Lepton2 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    StH_vectorLepton1_phi = new TH1F(("vectorLepton1_phi"+suffix).c_str(),("Vector Lepton1 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    StH_vectorLepton2_phi = new TH1F(("vectorLepton2_phi"+suffix).c_str(),("Vector Lepton2 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    StH_vectorLepton1_eta = new TH1F(("vectorLepton1_eta"+suffix).c_str(),("Vector Lepton1 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    StH_vectorLepton2_eta = new TH1F(("vectorLepton2_eta"+suffix).c_str(),("Vector Lepton2 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    StH_vectorLepton1_pfCombRelIso = new TH1F(("vectorLepton1_pfCombRelIso"+suffix).c_str(),("Vector Lepton1 pfCombRelIso ("+suffix+")").c_str(), bin_iso, min_iso, max_iso );
    StH_vectorLepton2_pfCombRelIso = new TH1F(("vectorLepton2_pfCombRelIso"+suffix).c_str(),("Vector Lepton2 pfCombRelIso ("+suffix+")").c_str(), bin_iso, min_iso, max_iso );
    StH_vectorLepton1_dxy = new TH1F(("vectorLepton1_dxy"+suffix).c_str(),("Vector Lepton1 dxy ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    StH_vectorLepton2_dxy = new TH1F(("vectorLepton2_dxy"+suffix).c_str(),("Vector Lepton2 dxy ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    StH_vectorLepton1_dz = new TH1F(("vectorLepton1_dz"+suffix).c_str(),("Vector Lepton1 dz ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    StH_vectorLepton2_dz = new TH1F(("vectorLepton2_dz"+suffix).c_str(),("Vector Lepton2 dz ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );

    StH_simpleJet1_pt = new TH1F(("SimpleJet1_pt"+suffix).c_str(),("Simple Jet1 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    StH_simpleJet2_pt = new TH1F(("SimpleJet2_pt"+suffix).c_str(),("Simple Jet2 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    StH_simpleJet1_phi = new TH1F(("SimpleJet1_phi"+suffix).c_str(),("Simple Jet1 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    StH_simpleJet2_phi = new TH1F(("SimpleJet2_phi"+suffix).c_str(),("Simple Jet2 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    StH_simpleJet1_eta = new TH1F(("SimpleJet1_eta"+suffix).c_str(),("Simple Jet1 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    StH_simpleJet2_eta = new TH1F(("SimpleJet2_eta"+suffix).c_str(),("Simple Jet2 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    StH_simpleJet1_bTag = new TH1F(("SimpleJet1_bTag"+suffix).c_str(),("Simple Jet1 bTag ("+suffix+")").c_str(), bin_btag, min_btag, max_btag );
    StH_simpleJet2_bTag = new TH1F(("SimpleJet2_bTag"+suffix).c_str(),("Simple Jet2 bTag ("+suffix+")").c_str(), bin_btag, min_btag, max_btag );
    StH_simpleJet1_vtxMass = new TH1F(("SimpleJet1_vtxMass"+suffix).c_str(),("Simple Jet1 vtxMass ("+suffix+")").c_str(), bin_SVmass, min_SVmass, max_SVmass );
    StH_simpleJet2_vtxMass = new TH1F(("SimpleJet2_vtxMass"+suffix).c_str(),("Simple Jet2 vtxMass ("+suffix+")").c_str(), bin_SVmass, min_SVmass, max_SVmass );

    StH_simpleJets_bTag = new TH1F(("SimpleJets_bTag"+suffix).c_str(),("Simple Jets bTag ("+suffix+")").c_str(), bin_btag, min_btag, max_btag );
    StH_simpleJets_vtxMass = new TH1F(("SimpleJets_vtxMass"+suffix).c_str(),("Simple Jets vtxMass ("+suffix+")").c_str(), bin_SVmass, min_SVmass, max_SVmass );

    StH_HMass = new TH1F(("HiggsMass"+suffix).c_str(),(" Higgs Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass );
    StH_HPt = new TH1F(("HiggsPt"+suffix).c_str(),(" Higgs Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );
    StH_HdR = new TH1F(("HdR"+suffix).c_str(),("Higgs deltaR ("+suffix+")").c_str(), bin_deltaR, min_deltaR, max_deltaR );
    StH_HdPhi = new TH1F(("HdPhi"+suffix).c_str(),("Higgs deltaPhi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi );
    StH_HdEta = new TH1F(("HdEta"+suffix).c_str(),("Higgs deltaEta ("+suffix+")").c_str(), bin_deltaEta, min_deltaEta, max_deltaEta );
    StH_HHel = new TH1F(("HiggsHel"+suffix).c_str(),("Higgs helicity angle ("+suffix+")").c_str(), bin_hel, min_hel, max_hel );
    StH_HPullAngle = new TH1F(("HiggsPullAngle"+suffix).c_str(),("Higgs pull angle ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi );
    StH_HdR_addJets = new TH1F(("HdR_addJets"+suffix).c_str(),("Higgs deltaR addJets ("+suffix+")").c_str(), bin_deltaR, min_deltaR, max_deltaR );

    StH_ZMass = new TH1F(("ZMass"+suffix).c_str(),(" Z Mass ("+suffix+")").c_str(), 100, 50, 150 );
    StH_ZPt = new TH1F(("ZPt"+suffix).c_str(),(" Z Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );
    StH_ZH_dPhi = new TH1F(("ZH_dPhi"+suffix).c_str(),(" ZH delta Phi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi );
    StH_WMass = new TH1F(("WMass"+suffix).c_str(),(" W Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass );
    StH_WPt = new TH1F(("WPt"+suffix).c_str(),(" W Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );
    StH_WH_dPhi = new TH1F(("WH_dPhi"+suffix).c_str(),(" WH delta Phi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi );

  }
  
  virtual void fill(ntupleReader &iEvent,float w) {
      
    StH_nPVs->Fill(iEvent.nPVs, w);
    StH_addJets->Fill(iEvent.CountAddJets(), w);

    StH_met_et->Fill(iEvent.MET_et, w);
    StH_met_sig->Fill(iEvent.MET_sig, w);

    StH_vectorLepton1_pt->Fill(iEvent.vLepton_pt[0], w);
    StH_vectorLepton2_pt->Fill(iEvent.vLepton_pt[1], w);
    StH_vectorLepton1_phi->Fill(iEvent.vLepton_phi[0], w);
    StH_vectorLepton2_phi->Fill(iEvent.vLepton_phi[1], w);
    StH_vectorLepton1_eta->Fill(iEvent.vLepton_eta[0], w);
    StH_vectorLepton2_eta->Fill(iEvent.vLepton_eta[1], w);
    StH_vectorLepton1_pfCombRelIso->Fill(iEvent.vLepton_pfCombRelIso[0], w);
    StH_vectorLepton2_pfCombRelIso->Fill(iEvent.vLepton_pfCombRelIso[1], w);
    StH_vectorLepton1_dxy->Fill(iEvent.vLepton_dxy[0], w);
    StH_vectorLepton2_dxy->Fill(iEvent.vLepton_dxy[1], w);
    StH_vectorLepton1_dz->Fill(iEvent.vLepton_dz[0], w);
    StH_vectorLepton2_dz->Fill(iEvent.vLepton_dz[1], w);

    StH_simpleJet1_pt->Fill(iEvent.hJet_pt[0], w);
    StH_simpleJet2_pt->Fill(iEvent.hJet_pt[1], w);
    StH_simpleJet1_phi->Fill(iEvent.hJet_phi[0], w);
    StH_simpleJet2_phi->Fill(iEvent.hJet_phi[1], w);
    StH_simpleJet1_eta->Fill(iEvent.hJet_eta[0], w);
    StH_simpleJet2_eta->Fill(iEvent.hJet_eta[1], w);
    //vertex mas and btag sorted by btag
    if( iEvent.hJet_csv[0] > iEvent.hJet_csv[1] ){
      StH_simpleJet1_bTag->Fill(iEvent.hJet_csv[0], w);
      StH_simpleJet2_bTag->Fill(iEvent.hJet_csv[1], w);
      StH_simpleJet1_vtxMass->Fill(iEvent.hJet_vtxMass[0], w);
    }
    else{
      StH_simpleJet1_bTag->Fill(iEvent.hJet_csv[1], w);
      StH_simpleJet2_bTag->Fill(iEvent.hJet_csv[0], w);
      StH_simpleJet2_vtxMass->Fill(iEvent.hJet_vtxMass[1], w);
    }
    //here I fill both jets in one histo
    StH_simpleJets_bTag->Fill(iEvent.hJet_csv[0], w);
    StH_simpleJets_bTag->Fill(iEvent.hJet_csv[1], w);
    StH_simpleJets_vtxMass->Fill(iEvent.hJet_vtxMass[0], w);
    StH_simpleJets_vtxMass->Fill(iEvent.hJet_vtxMass[1], w);
    
    StH_HMass->Fill(iEvent.H_mass, w); 
    StH_HPt->Fill(iEvent.H_pt, w); 
    StH_HdR->Fill(iEvent.H_dR, w);
    StH_HdPhi->Fill(iEvent.H_dPhi, w);
    StH_HdEta->Fill(iEvent.H_dEta, w);

    StH_HHel->Fill(iEvent.hJet_cosTheta[0], w); 
    StH_HPullAngle->Fill(iEvent.deltaPullAngle, w); 

    TLorentzVector higgs, addJet;
    higgs.SetPtEtaPhiM(iEvent.H_pt,iEvent.H_eta,iEvent.H_phi,iEvent.H_mass);
    addJet.SetPtEtaPhiE(iEvent.aJet_pt[0],iEvent.aJet_eta[0],iEvent.aJet_phi[0],iEvent.aJet_e[0]);

    StH_HdR_addJets->Fill(higgs.DeltaR(addJet), w);
    
    iType = (VType)iEvent.Vtype;
    if( iType == Zmm || iType == Zee || iType == Znn ){
      StH_ZMass->Fill(iEvent.V_mass, w); 
      StH_ZPt->Fill(iEvent.V_pt, w);
      StH_ZH_dPhi->Fill(iEvent. HVdPhi, w); 
    }
    else{
      StH_WMass->Fill(iEvent.V_mass, w);
      StH_WPt->Fill(iEvent.V_pt, w); 
      StH_WH_dPhi->Fill(iEvent.HVdPhi, w); 
    }
    
  
  }

  TH1F * StH_nPVs;
  TH1F * StH_addJets;
  TH1F * StH_met_et;
  TH1F * StH_met_sig;

  TH1F * StH_vectorLepton1_pt;
  TH1F * StH_vectorLepton2_pt;
  TH1F * StH_vectorLepton1_phi;
  TH1F * StH_vectorLepton2_phi;
  TH1F * StH_vectorLepton1_eta;
  TH1F * StH_vectorLepton2_eta;
  TH1F * StH_vectorLepton1_pfCombRelIso;
  TH1F * StH_vectorLepton2_pfCombRelIso;
  TH1F * StH_vectorLepton1_dxy;
  TH1F * StH_vectorLepton2_dxy;
  TH1F * StH_vectorLepton1_dz;
  TH1F * StH_vectorLepton2_dz;
  
  TH1F * StH_simpleJet1_pt;
  TH1F * StH_simpleJet2_pt;
  TH1F * StH_simpleJet1_phi;
  TH1F * StH_simpleJet2_phi;
  TH1F * StH_simpleJet1_eta;
  TH1F * StH_simpleJet2_eta;
  TH1F * StH_simpleJet1_bTag;
  TH1F * StH_simpleJet2_bTag;
  TH1F * StH_simpleJet1_vtxMass;
  TH1F * StH_simpleJet2_vtxMass;

  TH1F * StH_simpleJets_bTag;
  TH1F * StH_simpleJets_vtxMass;

  TH1F * StH_HMass;
  TH1F * StH_HPt;
  TH1F * StH_HdR;
  TH1F * StH_HdPhi;
  TH1F * StH_HdEta;
  TH1F * StH_HHel;
  TH1F * StH_HPullAngle;
  TH1F * StH_HdR_addJets;

  TH1F * StH_WMass;
  TH1F * StH_WPt;
  TH1F * StH_WH_dPhi;

  TH1F * StH_ZMass;
  TH1F * StH_ZPt;
  TH1F * StH_ZH_dPhi;
 
private:

  Int_t bin_btag;
  Double_t min_btag;
  Double_t max_btag;

  Int_t  bin_SVmass;
  Double_t min_SVmass;
  Double_t max_SVmass;
  
  Int_t bin_eta;
  Double_t min_eta;
  Double_t max_eta;

  Int_t bin_phi;
  Double_t min_phi;
  Double_t max_phi;

  Int_t bin_deltaEta;
  Double_t min_deltaEta;
  Double_t max_deltaEta;

  Int_t bin_deltaPhi;
  Double_t min_deltaPhi;
  Double_t max_deltaPhi;

  Int_t bin_deltaR;
  Double_t min_deltaR;
  Double_t max_deltaR;

  Int_t bin_mass;
  Double_t min_mass;
  Double_t max_mass;

  Int_t bin_pt;
  Double_t min_pt;
  Double_t max_pt;

  Int_t bin_npvs;
  Double_t min_npvs;
  Double_t max_npvs;

  Int_t bin_addJets;
  Double_t min_addJets;
  Double_t max_addJets;

  Int_t bin_hel;
  Double_t min_hel;
  Double_t max_hel;

  Int_t bin_iso;
  Double_t min_iso;
  Double_t max_iso;

  Int_t bin_dxy;
  Double_t min_dxy;
  Double_t max_dxy;

};



class SystematicsHistos : public Histos {
    
public:

  virtual void book(TFile &f, std::string suffix) {

    TDirectory *subDir;
    if( ! f.GetDirectory(suffix.c_str()) )
      subDir = f.mkdir(suffix.c_str());
    else 
      subDir = f.GetDirectory(suffix.c_str());
    subDir->cd();

    bin_mass = 30;
    min_mass = 0;
    max_mass = 300;
    
    bin_SVmass = 50;
    min_SVmass = 0;
    max_SVmass = 10;

    bin_pt = 50;
    min_pt = 0;
    max_pt = 500;
    
    bin_hel = 10;
    min_hel = 0;
    max_hel = 1;

    bin_dxy = 20;
    min_dxy = -0.2;
    max_dxy = 0.2;

    bin_iso = 20;
    min_iso = 0;
    max_iso = 0.5;

    bin_btag = 20;
    min_btag = 0;
    max_btag = 1;

    bin_npvs = 30;
    min_npvs = 0;
    max_npvs = 30;

    bin_addJets = 10;
    min_addJets = 0;
    max_addJets = 10;

    bin_eta = bin_phi = 20;
    min_eta = min_phi = -5;
    max_eta = max_phi = 5;

    bin_deltaR = bin_deltaPhi = bin_deltaEta = 20;
    min_deltaR = min_deltaPhi = min_deltaEta = 0;
    max_deltaR = max_deltaPhi = max_deltaEta = 5;

    //Candidates

    SystUPH_addJets = new TH1F(("addJets"+suffix+"SystUP").c_str(),("Number of additional AK5 ("+suffix+"SystUP"+")").c_str(), bin_addJets, min_addJets, max_addJets );
    SystUPH_simpleJet1_pt = new TH1F(("SimpleJet1_pt"+suffix+"SystUP").c_str(),("Simple Jet1 pt ("+suffix+"SystUP"+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    SystUPH_simpleJet2_pt = new TH1F(("SimpleJet2_pt"+suffix+"SystUP").c_str(),("Simple Jet2 pt ("+suffix+"SystUP"+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    SystUPH_HMass = new TH1F(("HiggsMass"+suffix+"SystUP").c_str(),(" Higgs Mass ("+suffix+"SystUP"+")").c_str(), bin_mass, min_mass, max_mass );
    SystUPH_HPt = new TH1F(("HiggsPt"+suffix+"SystUP").c_str(),(" Higgs Pt ("+suffix+"SystUP"+")").c_str(), bin_pt, min_pt, max_pt );
    SystUPH_HdR_addJets = new TH1F(("HdR_addJets"+suffix+"SystUP").c_str(),("Higgs deltaR addJets ("+suffix+"SystUP"+")").c_str(), bin_deltaR, min_deltaR, max_deltaR );

    SystUPH_simpleJet1_bTag = new TH1F(("SimpleJet1_bTag"+suffix+"SystUP").c_str(),("Simple Jet1 bTag ("+suffix+"SystUP"+")").c_str(), bin_btag, min_btag, max_btag );
    SystUPH_simpleJet2_bTag = new TH1F(("SimpleJet2_bTag"+suffix+"SystUP").c_str(),("Simple Jet2 bTag ("+suffix+"SystUP"+")").c_str(), bin_btag, min_btag, max_btag );
    SystUPH_simpleJets_bTag = new TH1F(("SimpleJets_bTag"+suffix+"SystUP").c_str(),("Simple Jets bTag ("+suffix+"SystUP"+")").c_str(), bin_btag, min_btag, max_btag );

    SystDOWNH_addJets = new TH1F(("addJets"+suffix+"SystDOWN").c_str(),("Number of additional AK5 ("+suffix+"SystDOWN"+")").c_str(), bin_addJets, min_addJets, max_addJets );
    SystDOWNH_simpleJet1_pt = new TH1F(("SimpleJet1_pt"+suffix+"SystDOWN").c_str(),("Simple Jet1 pt ("+suffix+"SystDOWN"+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    SystDOWNH_simpleJet2_pt = new TH1F(("SimpleJet2_pt"+suffix+"SystDOWN").c_str(),("Simple Jet2 pt ("+suffix+"SystDOWN"+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    SystDOWNH_HMass = new TH1F(("HiggsMass"+suffix+"SystDOWN").c_str(),(" Higgs Mass ("+suffix+"SystDOWN"+")").c_str(), bin_mass, min_mass, max_mass );
    SystDOWNH_HPt = new TH1F(("HiggsPt"+suffix+"SystDOWN").c_str(),(" Higgs Pt ("+suffix+"SystDOWN"+")").c_str(), bin_pt, min_pt, max_pt );
    SystDOWNH_HdR_addJets = new TH1F(("HdR_addJets"+suffix+"SystDOWN").c_str(),("Higgs deltaR addJets ("+suffix+"SystDOWN"+")").c_str(), bin_deltaR, min_deltaR, max_deltaR );

    SystDOWNH_simpleJet1_bTag = new TH1F(("SimpleJet1_bTag"+suffix+"SystDOWN").c_str(),("Simple Jet1 bTag ("+suffix+"SystDOWN"+")").c_str(), bin_btag, min_btag, max_btag );
    SystDOWNH_simpleJet2_bTag = new TH1F(("SimpleJet2_bTag"+suffix+"SystDOWN").c_str(),("Simple Jet2 bTag ("+suffix+"SystDOWN"+")").c_str(), bin_btag, min_btag, max_btag );
    SystDOWNH_simpleJets_bTag = new TH1F(("SimpleJets_bTag"+suffix+"SystDOWN").c_str(),("Simple Jets bTag ("+suffix+"SystDOWN"+")").c_str(), bin_btag, min_btag, max_btag );


  }
  
  virtual void fill(ntupleReader &iEvent,float w) {

    TLorentzVector higgs, addJet;
      

    //UPSCALE
    SystUPH_addJets->Fill(iEvent.CountAddJets_jec(+1), w);
    SystUPH_simpleJet1_pt->Fill(iEvent.hJet_pt_jecUP(0), w); 
    SystUPH_simpleJet2_pt->Fill(iEvent.hJet_pt_jecUP(1), w); 
    //vertex mas and btag sorted by btag
    if( iEvent.hJet_csv_cUP(0) > iEvent.hJet_csv_cUP(1) ){
      SystUPH_simpleJet1_bTag->Fill(iEvent.hJet_csv_cUP(0), w);
      SystUPH_simpleJet2_bTag->Fill(iEvent.hJet_csv_cUP(1), w);
    }
    else{
      SystUPH_simpleJet1_bTag->Fill(iEvent.hJet_csv_cUP(1), w);
      SystUPH_simpleJet2_bTag->Fill(iEvent.hJet_csv_cUP(0), w);
    }
    //here I fill both jets in one histo
    SystUPH_simpleJets_bTag->Fill(iEvent.hJet_csv_cUP(0), w);
    SystUPH_simpleJets_bTag->Fill(iEvent.hJet_csv_cUP(1), w);
    SystUPH_HMass->Fill(iEvent.H_jecUP().M(), w); 
    SystUPH_HPt->Fill(iEvent.H_jecUP().Pt(), w); 
    higgs=iEvent.H_jecUP();
    addJet.SetPtEtaPhiE(iEvent.aJet_pt_jecUP(0),iEvent.aJet_eta[0],iEvent.aJet_phi[0],iEvent.aJet_e[0]);
    SystUPH_HdR_addJets->Fill(higgs.DeltaR(addJet), w);

    //DOWNSCALE
    SystDOWNH_addJets->Fill(iEvent.CountAddJets_jec(-1), w);
    SystDOWNH_simpleJet1_pt->Fill(iEvent.hJet_pt_jecDOWN(0), w); 
    SystDOWNH_simpleJet2_pt->Fill(iEvent.hJet_pt_jecDOWN(1), w); 
    //vertex mas and btag sorted by btag
    if( iEvent.hJet_csv_cDOWN(0) > iEvent.hJet_csv_cDOWN(1) ){
      SystDOWNH_simpleJet1_bTag->Fill(iEvent.hJet_csv_cDOWN(0), w);
      SystDOWNH_simpleJet2_bTag->Fill(iEvent.hJet_csv_cDOWN(1), w);
    }
    else{
      SystDOWNH_simpleJet1_bTag->Fill(iEvent.hJet_csv_cDOWN(1), w);
      SystDOWNH_simpleJet2_bTag->Fill(iEvent.hJet_csv_cDOWN(0), w);
    }
    //here I fill both jets in one histo
    SystDOWNH_simpleJets_bTag->Fill(iEvent.hJet_csv_cDOWN(0), w);
    SystDOWNH_simpleJets_bTag->Fill(iEvent.hJet_csv_cDOWN(1), w);
    SystDOWNH_HMass->Fill(iEvent.H_jecDOWN().M(), w); 
    SystDOWNH_HPt->Fill(iEvent.H_jecDOWN().Pt(), w); 
    higgs=iEvent.H_jecDOWN();
    addJet.SetPtEtaPhiE(iEvent.aJet_pt_jecDOWN(0),iEvent.aJet_eta[0],iEvent.aJet_phi[0],iEvent.aJet_e[0]);
    SystDOWNH_HdR_addJets->Fill(higgs.DeltaR(addJet), w);
         
  }

  TH1F * SystUPH_addJets;  
  TH1F * SystUPH_simpleJet1_pt;
  TH1F * SystUPH_simpleJet2_pt;
  TH1F * SystUPH_HMass;
  TH1F * SystUPH_HPt;
  TH1F * SystUPH_HdR_addJets;
  TH1F * SystUPH_simpleJet1_bTag;
  TH1F * SystUPH_simpleJet2_bTag;
  TH1F * SystUPH_simpleJets_bTag;

  TH1F * SystDOWNH_addJets;  
  TH1F * SystDOWNH_simpleJet1_pt;
  TH1F * SystDOWNH_simpleJet2_pt;
  TH1F * SystDOWNH_HMass;
  TH1F * SystDOWNH_HPt;
  TH1F * SystDOWNH_HdR_addJets;
  TH1F * SystDOWNH_simpleJet1_bTag;
  TH1F * SystDOWNH_simpleJet2_bTag;
  TH1F * SystDOWNH_simpleJets_bTag;

 
private:

  Int_t bin_btag;
  Double_t min_btag;
  Double_t max_btag;

  Int_t  bin_SVmass;
  Double_t min_SVmass;
  Double_t max_SVmass;
  
  Int_t bin_eta;
  Double_t min_eta;
  Double_t max_eta;

  Int_t bin_phi;
  Double_t min_phi;
  Double_t max_phi;

  Int_t bin_deltaEta;
  Double_t min_deltaEta;
  Double_t max_deltaEta;

  Int_t bin_deltaPhi;
  Double_t min_deltaPhi;
  Double_t max_deltaPhi;

  Int_t bin_deltaR;
  Double_t min_deltaR;
  Double_t max_deltaR;

  Int_t bin_mass;
  Double_t min_mass;
  Double_t max_mass;

  Int_t bin_pt;
  Double_t min_pt;
  Double_t max_pt;

  Int_t bin_npvs;
  Double_t min_npvs;
  Double_t max_npvs;

  Int_t bin_addJets;
  Double_t min_addJets;
  Double_t max_addJets;

  Int_t bin_hel;
  Double_t min_hel;
  Double_t max_hel;

  Int_t bin_iso;
  Double_t min_iso;
  Double_t max_iso;

  Int_t bin_dxy;
  Double_t min_dxy;
  Double_t max_dxy;

};


class MVAHistos : public Histos {

public:
  MVAHistos( const std::string &channel_):
    channel(channel_) {}

  virtual void book(TFile &f, std::string suffix) {

    suffix+=channel;
    //    std::clog << "Start booking" << std::endl;

    TDirectory *subDir;
    if( ! f.GetDirectory(suffix.c_str()) )
      subDir = f.mkdir(suffix.c_str());
    else 
      subDir = f.GetDirectory(suffix.c_str());
    subDir->cd();

    bin_BDT = 100;
    min_BDT = -0.8;
    max_BDT = 0.8;
    
    MVAH_BDT = new TH1F(("BDT"+suffix).c_str(),(" BDT output ("+suffix+")").c_str(), bin_BDT, min_BDT, max_BDT );

  }
  
  virtual void fill(ntupleReader &iEvent,float w) {

    TMVA::Reader * reader = new TMVA::Reader();
    
    float bbMass,bbPt,btag1,btag2,NaddJet,DeltaRbb,helicity,DeltaPhiVH,bPt1,bPt2,VMass,VPt,pullAngle,DeltaEtabb,deltaPhipfMETjet,pfMET,pfMETsig;
    std::string analysis("Zee");    

    if(analysis == "Zmm"){
      reader->AddVariable( "bbMass",            &bbMass    );
      reader->AddVariable( "VMass",             &VMass     );
      reader->AddVariable( "bbPt",              &bbPt      );
      reader->AddVariable( "VPt",               &VPt       );
      reader->AddVariable( "btag1",             &btag1     );
      reader->AddVariable( "btag2",             &btag2     );
      reader->AddVariable( "DeltaPhiVH",        &DeltaPhiVH);
      reader->AddVariable( "DeltaEtabb",        &DeltaEtabb);
    }
    else if(analysis == "Zee"){      
      reader->AddVariable( "H.mass",            &bbMass    );
      reader->AddVariable( "H.pt",              &bbPt      );
      reader->AddVariable( "H.dEta",            &DeltaEtabb);      
      reader->AddVariable( "HVdPhi",            &DeltaPhiVH);
      reader->AddVariable( "V.mass",            &VMass     );
      reader->AddVariable( "V.pt",              &VPt       );
      reader->AddVariable( "hJet_csv[0]",       &btag1     );
      reader->AddVariable( "hJet_csv[1]",       &btag2     );
    }
    else if(analysis == "Znn"){
      reader->AddVariable( "bbMass",            &bbMass    );
      reader->AddVariable( "bbPt",              &bbPt      );
      reader->AddVariable( "pfMET",             &pfMET     );
      reader->AddVariable( "btag1",             &btag1     );
      reader->AddVariable( "btag2",             &btag2     );
      reader->AddVariable( "DeltaPhiVH",        &DeltaPhiVH);
    }
    else if(analysis == "We"){
      reader->AddVariable( "bbMass",            &bbMass    );
      reader->AddVariable( "bbPt",              &bbPt      );
      reader->AddVariable( "VPt",               &VPt       );
      reader->AddVariable( "btag1",             &btag1     );
      reader->AddVariable( "btag2",             &btag2     );
      reader->AddVariable( "DeltaPhiVH",        &DeltaPhiVH);
      reader->AddVariable( "DeltaEtabb",        &DeltaEtabb);
    }
    else if(analysis == "Wm"){
      reader->AddVariable( "bbMass",            &bbMass    );
      reader->AddVariable( "bbPt",              &bbPt      );
      reader->AddVariable( "VPt",               &VPt       );
      reader->AddVariable( "btag1",             &btag1     );
      reader->AddVariable( "btag2",             &btag2     );
      reader->AddVariable( "DeltaPhiVH",        &DeltaPhiVH);
      reader->AddVariable( "DeltaEtabb",        &DeltaEtabb);
    }

    // --- Book the MVA methods

    std::vector<std::string> methods;
    methods.push_back("BDT");
    TString dir    = "weights/";
    TString prefix = "MVA";
    //    std::clog << "Booking MVA method..." << std::endl;
    for (size_t it = 0; it < methods.size(); ++it) {
      TString methodName = methods.at(it)+ " method";
      TString weightfile = dir + prefix + "_" + methods.at(it) + "_" + channel + TString(".weights.xml");
      reader->BookMVA( methodName, weightfile ); 
    }
        
    bbMass = iEvent.H_mass;
    bbPt = iEvent.H_pt;
    btag1 = iEvent.hJet_csv[0];
    btag2 = iEvent.hJet_csv[1];
    NaddJet = iEvent.naJets; // FIX ME
    DeltaRbb = iEvent.H_dR;
    helicity = iEvent.hJet_cosTheta[0];
    DeltaPhiVH = iEvent.HVdPhi;
    bPt1 = iEvent.hJet_pt[0];
    bPt2 = iEvent.hJet_pt[1];
    VMass = iEvent.V_mass; 
    VPt = iEvent.V_pt;
    pullAngle = iEvent.deltaPullAngle;
    DeltaEtabb = iEvent.H_dEta;
    deltaPhipfMETjet = iEvent.minDeltaPhijetMET;
    pfMET = iEvent.MET_et;
    pfMETsig = iEvent.MET_sig;

    MVAH_BDT->Fill( reader->EvaluateMVA( "BDT method" ) );      
      
  }
  
  TH1F * MVAH_BDT;
 
private:

  const std::string channel;
  Int_t bin_BDT;
  Double_t min_BDT;
  Double_t max_BDT;

};



class IVFHistos : public Histos {
    
public:

  virtual void book(TFile &f, std::string suffix) {

    TDirectory *subDir;
    if( ! f.GetDirectory(suffix.c_str()) )
      subDir = f.mkdir(suffix.c_str());
    else 
      subDir = f.GetDirectory(suffix.c_str());
    subDir->cd();

    bin_mass = 30;
    min_mass = 0;
    max_mass = 300;
    
    bin_SVmass = 50;
    min_SVmass = 0;
    max_SVmass = 10;

    bin_pt = 50;
    min_pt = 0;
    max_pt = 500;
    
    bin_SVpt = 50;
    min_SVpt = 0;
    max_SVpt = 100;

    bin_hel = 10;
    min_hel = 0;
    max_hel = 1;

    bin_dxy = 20;
    min_dxy = -0.2;
    max_dxy = 0.2;

    bin_iso = 20;
    min_iso = 0;
    max_iso = 0.5;

    bin_btag = 20;
    min_btag = 0;
    max_btag = 1;

    bin_npvs = 30;
    min_npvs = 0;
    max_npvs = 30;

    bin_jets = 10;
    min_jets = 0;
    max_jets = 10;

    bin_eta = bin_phi = 20;
    min_eta = min_phi = -5;
    max_eta = max_phi = 5;

    bin_deltaR = bin_deltaPhi = bin_deltaEta = 8;
    min_deltaR = min_deltaPhi = min_deltaEta = 0;
    max_deltaR = max_deltaPhi = max_deltaEta = 5;

    //Candidates
    IVFH_nPVs = new TH1F(("nPVs"+suffix).c_str(),("Number of reconstructed PV ("+suffix+")").c_str(), bin_npvs, min_npvs, max_npvs );
    IVFH_nSvs = new TH1F(("nSvs"+suffix).c_str(),("Number of reconstructed PV ("+suffix+")").c_str(), bin_npvs, min_npvs, max_npvs );
    IVFH_numOfJets = new TH1F(("NumOfJets"+suffix).c_str(),("Number of AK5 ("+suffix+")").c_str(), bin_jets, min_jets, max_jets );

    IVFH_met_et = new TH1F(("MET_et"+suffix).c_str(),("Missing transverse energy ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.5 );
    IVFH_met_sig = new TH1F(("MET_sig"+suffix).c_str(),("MET significance("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.1 );

    IVFH_vectorLepton1_pt = new TH1F(("vectorLepton1_pt"+suffix).c_str(),("Vector Lepton1 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    IVFH_vectorLepton2_pt = new TH1F(("vectorLepton2_pt"+suffix).c_str(),("Vector Lepton2 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    IVFH_vectorLepton1_phi = new TH1F(("vectorLepton1_phi"+suffix).c_str(),("Vector Lepton1 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    IVFH_vectorLepton2_phi = new TH1F(("vectorLepton2_phi"+suffix).c_str(),("Vector Lepton2 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    IVFH_vectorLepton1_eta = new TH1F(("vectorLepton1_eta"+suffix).c_str(),("Vector Lepton1 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    IVFH_vectorLepton2_eta = new TH1F(("vectorLepton2_eta"+suffix).c_str(),("Vector Lepton2 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    IVFH_vectorLepton1_pfCombRelIso = new TH1F(("vectorLepton1_pfCombRelIso"+suffix).c_str(),("Vector Lepton1 pfCombRelIso ("+suffix+")").c_str(), bin_iso, min_iso, max_iso );
    IVFH_vectorLepton2_pfCombRelIso = new TH1F(("vectorLepton2_pfCombRelIso"+suffix).c_str(),("Vector Lepton2 pfCombRelIso ("+suffix+")").c_str(), bin_iso, min_iso, max_iso );
    IVFH_vectorLepton1_dxy = new TH1F(("vectorLepton1_dxy"+suffix).c_str(),("Vector Lepton1 dxy ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    IVFH_vectorLepton2_dxy = new TH1F(("vectorLepton2_dxy"+suffix).c_str(),("Vector Lepton2 dxy ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    IVFH_vectorLepton1_dz = new TH1F(("vectorLepton1_dz"+suffix).c_str(),("Vector Lepton1 dz ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    IVFH_vectorLepton2_dz = new TH1F(("vectorLepton2_dz"+suffix).c_str(),("Vector Lepton2 dz ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );

    IVFH_simpleJet1_pt = new TH1F(("SimpleJet1_pt"+suffix).c_str(),("Simple Jet1 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    IVFH_simpleJet2_pt = new TH1F(("SimpleJet2_pt"+suffix).c_str(),("Simple Jet2 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    IVFH_simpleJet1_phi = new TH1F(("SimpleJet1_phi"+suffix).c_str(),("Simple Jet1 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    IVFH_simpleJet2_phi = new TH1F(("SimpleJet2_phi"+suffix).c_str(),("Simple Jet2 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    IVFH_simpleJet1_eta = new TH1F(("SimpleJet1_eta"+suffix).c_str(),("Simple Jet1 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    IVFH_simpleJet2_eta = new TH1F(("SimpleJet2_eta"+suffix).c_str(),("Simple Jet2 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    IVFH_simpleJet1_bTag = new TH1F(("SimpleJet1_bTag"+suffix).c_str(),("Simple Jet1 bTag ("+suffix+")").c_str(), bin_btag, min_btag, max_btag );
    IVFH_simpleJet2_bTag = new TH1F(("SimpleJet2_bTag"+suffix).c_str(),("Simple Jet2 bTag ("+suffix+")").c_str(), bin_btag, min_btag, max_btag );

    IVFH_SV1_pt = new TH1F(("SV1_pt"+suffix).c_str(),("SV 1 pt ("+suffix+")").c_str(), bin_SVpt, min_SVpt, max_SVpt );
    IVFH_SV2_pt = new TH1F(("SV2_pt"+suffix).c_str(),("SV 2 pt ("+suffix+")").c_str(), bin_SVpt, min_SVpt, max_SVpt );
    IVFH_SV1_eta = new TH1F(("SV1_eta"+suffix).c_str(),("SV 1 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    IVFH_SV2_eta = new TH1F(("SV2_eta"+suffix).c_str(),("SV 2 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    IVFH_SV1_phi = new TH1F(("SV1_phi"+suffix).c_str(),("SV 1 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    IVFH_SV2_phi = new TH1F(("SV2_phi"+suffix).c_str(),("SV 2 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    IVFH_SV1_massBCand = new TH1F(("SV1_massBCand"+suffix).c_str(),("SV 1 massBCand ("+suffix+")").c_str(), bin_SVmass, min_SVmass, max_SVmass );
    IVFH_SV2_massBCand = new TH1F(("SV2_massBCand"+suffix).c_str(),("SV 2 massBCand ("+suffix+")").c_str(), bin_SVmass, min_SVmass, max_SVmass );

    IVFH_SVHMass = new TH1F(("SVHMass"+suffix).c_str(),(" SVH Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass*0.5 );
    IVFH_SVHPt = new TH1F(("SVHPt"+suffix).c_str(),(" SVH Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.5 );
    IVFH_SVHdR = new TH1F(("SVHdR"+suffix).c_str(),("SVH deltaR ("+suffix+")").c_str(), bin_deltaR, min_deltaR, max_deltaR );
    IVFH_SVHdR->GetXaxis()->SetTitle("SV #DeltaR");
    IVFH_SVHdPhi = new TH1F(("SVHdPhi"+suffix).c_str(),("SVH deltaPhi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi );
    IVFH_SVHdPhi->GetXaxis()->SetTitle("SV #Delta #phi");
    IVFH_SVHdEta = new TH1F(("SVHdEta"+suffix).c_str(),("SVH deltaEta ("+suffix+")").c_str(), bin_deltaEta, min_deltaEta, max_deltaEta );
    IVFH_SVHdEta->GetXaxis()->SetTitle("SV #Delta #eta");

    IVFH_HMass = new TH1F(("HiggsMass"+suffix).c_str(),(" Higgs Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass );
    IVFH_HPt = new TH1F(("HiggsPt"+suffix).c_str(),(" Higgs Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );
    IVFH_HdR = new TH1F(("HiggsdR"+suffix).c_str(),("Higgs deltaR ("+suffix+")").c_str(), bin_deltaR, min_deltaR, max_deltaR );
    IVFH_HdPhi = new TH1F(("HiggsdPhi"+suffix).c_str(),("Higgs deltaPhi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi );
    IVFH_HdEta = new TH1F(("HiggsdEta"+suffix).c_str(),("Higgs deltaEta ("+suffix+")").c_str(), bin_deltaEta, min_deltaEta, max_deltaEta );

    IVFH_HHel = new TH1F(("HiggsHel"+suffix).c_str(),("Higgs helicity angle ("+suffix+")").c_str(), bin_hel, min_hel, max_hel );
    IVFH_HPullAngle = new TH1F(("HiggsPullAngle"+suffix).c_str(),("Higgs pull angle ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi );

    IVFH_ZMass = new TH1F(("ZMass"+suffix).c_str(),(" Z Mass ("+suffix+")").c_str(), 100, 50, 150 );
    IVFH_ZPt = new TH1F(("ZPt"+suffix).c_str(),(" Z Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );
    IVFH_ZH_dPhi = new TH1F(("ZH_dPhi"+suffix).c_str(),(" ZH delta Phi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi );
    IVFH_WMass = new TH1F(("WMass"+suffix).c_str(),(" W Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass );
    IVFH_WPt = new TH1F(("WPt"+suffix).c_str(),(" W Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );
    IVFH_WH_dPhi = new TH1F(("WH_dPhi"+suffix).c_str(),(" WH delta Phi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi );

  }
  
  virtual void fill(ntupleReader &iEvent,float w) {
      
    IVFH_nPVs->Fill(iEvent.nPVs, w);
    IVFH_nSvs->Fill(iEvent.nSvs, w);
    IVFH_numOfJets->Fill(iEvent.CountJets(), w);

    IVFH_met_et->Fill(iEvent.MET_et, w);
    IVFH_met_sig->Fill(iEvent.MET_sig, w);

    IVFH_vectorLepton1_pt->Fill(iEvent.vLepton_pt[0], w);
    IVFH_vectorLepton2_pt->Fill(iEvent.vLepton_pt[1], w);
    IVFH_vectorLepton1_phi->Fill(iEvent.vLepton_phi[0], w);
    IVFH_vectorLepton2_phi->Fill(iEvent.vLepton_phi[1], w);
    IVFH_vectorLepton1_eta->Fill(iEvent.vLepton_eta[0], w);
    IVFH_vectorLepton2_eta->Fill(iEvent.vLepton_eta[1], w);
    IVFH_vectorLepton1_pfCombRelIso->Fill(iEvent.vLepton_pfCombRelIso[0], w);
    IVFH_vectorLepton2_pfCombRelIso->Fill(iEvent.vLepton_pfCombRelIso[1], w);
    IVFH_vectorLepton1_dxy->Fill(iEvent.vLepton_dxy[0], w);
    IVFH_vectorLepton2_dxy->Fill(iEvent.vLepton_dxy[1], w);
    IVFH_vectorLepton1_dz->Fill(iEvent.vLepton_dz[0], w);
    IVFH_vectorLepton2_dz->Fill(iEvent.vLepton_dz[1], w);


    IVFH_simpleJet1_pt->Fill(iEvent.hJet_pt[0], w);
    IVFH_simpleJet2_pt->Fill(iEvent.hJet_pt[1], w);
    IVFH_simpleJet1_phi->Fill(iEvent.hJet_phi[0], w);
    IVFH_simpleJet2_phi->Fill(iEvent.hJet_phi[1], w);
    IVFH_simpleJet1_eta->Fill(iEvent.hJet_eta[0], w);
    IVFH_simpleJet2_eta->Fill(iEvent.hJet_eta[1], w);
    IVFH_simpleJet1_bTag->Fill(iEvent.hJet_csv[0], w);
    IVFH_simpleJet2_bTag->Fill(iEvent.hJet_csv[1], w);

    IVFH_SV1_pt->Fill(iEvent.Sv_pt[0], w);
    IVFH_SV2_pt->Fill(iEvent.Sv_pt[1], w);
    IVFH_SV1_eta->Fill(iEvent.Sv_eta[0], w);
    IVFH_SV2_eta->Fill(iEvent.Sv_eta[1], w);
    IVFH_SV1_phi->Fill(iEvent.Sv_phi[0], w);
    IVFH_SV2_phi->Fill(iEvent.Sv_phi[1], w);
    IVFH_SV1_massBCand->Fill(iEvent.Sv_massBCand[0], w);
    IVFH_SV2_massBCand->Fill(iEvent.Sv_massBCand[1], w);

    IVFH_SVHMass->Fill(iEvent.SVH_mass, w); 
    IVFH_SVHPt->Fill(iEvent.SVH_pt, w); 
    IVFH_SVHdR->Fill(iEvent.SVH_dR, w);
    IVFH_SVHdPhi->Fill(iEvent.SVH_dPhi, w);
    IVFH_SVHdEta->Fill(iEvent.SVH_dEta, w);

    IVFH_HMass->Fill(iEvent.H_mass, w); 
    IVFH_HPt->Fill(iEvent.H_pt, w); 
    IVFH_HdR->Fill(iEvent.H_dR, w);
    IVFH_HdPhi->Fill(iEvent.H_dPhi, w);
    IVFH_HdEta->Fill(iEvent.H_dEta, w);
    IVFH_HHel->Fill(iEvent.hJet_cosTheta[0], w); 
    IVFH_HPullAngle->Fill(iEvent.deltaPullAngle, w); 
    
    iType = (VType)iEvent.Vtype;
    if( iType == Zmm || iType == Zee || iType == Znn ){
      IVFH_ZMass->Fill(iEvent.V_mass, w); 
      IVFH_ZPt->Fill(iEvent.V_pt, w);
      IVFH_ZH_dPhi->Fill(iEvent. HVdPhi, w); 
    }
    else{
      IVFH_WMass->Fill(iEvent.V_mass, w);
      IVFH_WPt->Fill(iEvent.V_pt, w); 
      IVFH_WH_dPhi->Fill(iEvent.HVdPhi, w); 
    }
    
  
  }

  TH1F * IVFH_nPVs;
  TH1F * IVFH_nSvs;
  TH1F * IVFH_numOfJets;
  TH1F * IVFH_met_et;
  TH1F * IVFH_met_sig;

  TH1F * IVFH_vectorLepton1_pt;
  TH1F * IVFH_vectorLepton2_pt;
  TH1F * IVFH_vectorLepton1_phi;
  TH1F * IVFH_vectorLepton2_phi;
  TH1F * IVFH_vectorLepton1_eta;
  TH1F * IVFH_vectorLepton2_eta;
  TH1F * IVFH_vectorLepton1_pfCombRelIso;
  TH1F * IVFH_vectorLepton2_pfCombRelIso;
  TH1F * IVFH_vectorLepton1_dxy;
  TH1F * IVFH_vectorLepton2_dxy;
  TH1F * IVFH_vectorLepton1_dz;
  TH1F * IVFH_vectorLepton2_dz;

  TH1F * IVFH_simpleJet1_pt;
  TH1F * IVFH_simpleJet2_pt;
  TH1F * IVFH_simpleJet1_phi;
  TH1F * IVFH_simpleJet2_phi;
  TH1F * IVFH_simpleJet1_eta;
  TH1F * IVFH_simpleJet2_eta;
  TH1F * IVFH_simpleJet1_bTag;
  TH1F * IVFH_simpleJet2_bTag;

TH1F *    IVFH_SV1_pt;
TH1F *    IVFH_SV2_pt;
TH1F *    IVFH_SV1_eta;
TH1F *    IVFH_SV2_eta;
TH1F *    IVFH_SV1_phi;
TH1F *    IVFH_SV2_phi;
TH1F *    IVFH_SV1_massBCand;
TH1F *    IVFH_SV2_massBCand;

  TH1F * IVFH_SVHMass;
  TH1F * IVFH_SVHPt;
  TH1F * IVFH_SVHdR;
  TH1F * IVFH_SVHdPhi;
  TH1F * IVFH_SVHdEta;

  TH1F * IVFH_HMass;
  TH1F * IVFH_HPt;
  TH1F * IVFH_HdR;
  TH1F * IVFH_HdPhi;
  TH1F * IVFH_HdEta;
  TH1F * IVFH_HHel;
  TH1F * IVFH_HPullAngle;

  TH1F * IVFH_WMass;
  TH1F * IVFH_WPt;
  TH1F * IVFH_WH_dPhi;

  TH1F * IVFH_ZMass;
  TH1F * IVFH_ZPt;
  TH1F * IVFH_ZH_dPhi;
 
private:

  Int_t bin_btag;
  Double_t min_btag;
  Double_t max_btag;

  Int_t bin_deltaEta;
  Double_t min_deltaEta;
  Double_t max_deltaEta;

  Int_t bin_deltaPhi;
  Double_t min_deltaPhi;
  Double_t max_deltaPhi;

  Int_t bin_deltaR;
  Double_t min_deltaR;
  Double_t max_deltaR;

  Int_t bin_mass;
  Double_t min_mass;
  Double_t max_mass;

  Int_t bin_SVmass;
  Double_t min_SVmass;
  Double_t max_SVmass;

  Int_t bin_pt;
  Double_t min_pt;
  Double_t max_pt;

  Int_t bin_SVpt;
  Double_t min_SVpt;
  Double_t max_SVpt;

  Int_t bin_phi;
  Double_t min_phi;
  Double_t max_phi;

  Int_t bin_eta;
  Double_t min_eta;
  Double_t max_eta;

  Int_t bin_npvs;
  Double_t min_npvs;
  Double_t max_npvs;

  Int_t bin_jets;
  Double_t min_jets;
  Double_t max_jets;

  Int_t bin_hel;
  Double_t min_hel;
  Double_t max_hel;

  Int_t bin_iso;
  Double_t min_iso;
  Double_t max_iso;

  Int_t bin_dxy;
  Double_t min_dxy;
  Double_t max_dxy;


};



class ZZHistos : public Histos {
    
public:

  virtual void book(TFile &f, std::string suffix) {

    TDirectory *subDir;
    if( ! f.GetDirectory(suffix.c_str()) )
      subDir = f.mkdir(suffix.c_str());
    else 
      subDir = f.GetDirectory(suffix.c_str());
    subDir->cd();

    bin_mass = 30;
    min_mass = 0;
    max_mass = 300;
    
    bin_pt = 50;
    min_pt = 0;
    max_pt = 500;
    
    bin_hel = 10;
    min_hel = 0;
    max_hel = 1;

    bin_dxy = 20;
    min_dxy = -0.2;
    max_dxy = 0.2;

    bin_iso = 20;
    min_iso = 0;
    max_iso = 0.5;

    bin_btag = 20;
    min_btag = 0;
    max_btag = 1;

    bin_npvs = 30;
    min_npvs = 0;
    max_npvs = 30;

    bin_addJets = 10;
    min_addJets = 0;
    max_addJets = 10;

    bin_eta = bin_phi = 20;
    min_eta = min_phi = -5;
    max_eta = max_phi = 5;

    bin_deltaR = bin_deltaPhi = bin_deltaEta = 20;
    min_deltaR = min_deltaPhi = min_deltaEta = 0;
    max_deltaR = max_deltaPhi = max_deltaEta = 5;

    //Candidates
    ZZH_nPVs = new TH1F(("nPVs"+suffix).c_str(),("Number of reconstructed PV ("+suffix+")").c_str(), bin_npvs, min_npvs, max_npvs );
    ZZH_addJets = new TH1F(("addJets"+suffix).c_str(),("Number of additional AK5 ("+suffix+")").c_str(), bin_addJets, min_addJets, max_addJets );

    ZZH_met_et = new TH1F(("MET_et"+suffix).c_str(),("Missing transverse energy ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.5 );
    ZZH_met_sig = new TH1F(("MET_sig"+suffix).c_str(),("MET significance("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.1 );

    ZZH_vectorLepton1_pt = new TH1F(("vectorLepton1_pt"+suffix).c_str(),("Vector Lepton1 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    ZZH_vectorLepton2_pt = new TH1F(("vectorLepton2_pt"+suffix).c_str(),("Vector Lepton2 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    ZZH_vectorLepton1_phi = new TH1F(("vectorLepton1_phi"+suffix).c_str(),("Vector Lepton1 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    ZZH_vectorLepton2_phi = new TH1F(("vectorLepton2_phi"+suffix).c_str(),("Vector Lepton2 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    ZZH_vectorLepton1_eta = new TH1F(("vectorLepton1_eta"+suffix).c_str(),("Vector Lepton1 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    ZZH_vectorLepton2_eta = new TH1F(("vectorLepton2_eta"+suffix).c_str(),("Vector Lepton2 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    ZZH_vectorLepton1_pfCombRelIso = new TH1F(("vectorLepton1_pfCombRelIso"+suffix).c_str(),("Vector Lepton1 pfCombRelIso ("+suffix+")").c_str(), bin_iso, min_iso, max_iso );
    ZZH_vectorLepton2_pfCombRelIso = new TH1F(("vectorLepton2_pfCombRelIso"+suffix).c_str(),("Vector Lepton2 pfCombRelIso ("+suffix+")").c_str(), bin_iso, min_iso, max_iso );
    ZZH_vectorLepton1_dxy = new TH1F(("vectorLepton1_dxy"+suffix).c_str(),("Vector Lepton1 dxy ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    ZZH_vectorLepton2_dxy = new TH1F(("vectorLepton2_dxy"+suffix).c_str(),("Vector Lepton2 dxy ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    ZZH_vectorLepton1_dz = new TH1F(("vectorLepton1_dz"+suffix).c_str(),("Vector Lepton1 dz ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    ZZH_vectorLepton2_dz = new TH1F(("vectorLepton2_dz"+suffix).c_str(),("Vector Lepton2 dz ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );

    ZZH_additionalLepton1_pt = new TH1F(("additionalLepton1_pt"+suffix).c_str(),("Additional Lepton1 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    ZZH_additionalLepton2_pt = new TH1F(("additionalLepton2_pt"+suffix).c_str(),("Additional Lepton2 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt*0.8 );
    ZZH_additionalLepton1_phi = new TH1F(("additionalLepton1_phi"+suffix).c_str(),("Additional Lepton1 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    ZZH_additionalLepton2_phi = new TH1F(("additionalLepton2_phi"+suffix).c_str(),("Additional Lepton2 phi ("+suffix+")").c_str(), bin_phi, min_phi, max_phi );
    ZZH_additionalLepton1_eta = new TH1F(("additionalLepton1_eta"+suffix).c_str(),("Additional Lepton1 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    ZZH_additionalLepton2_eta = new TH1F(("additionalLepton2_eta"+suffix).c_str(),("Additional Lepton2 eta ("+suffix+")").c_str(), bin_eta, min_eta, max_eta );
    ZZH_additionalLepton1_pfCombRelIso = new TH1F(("additionalLepton1_pfCombRelIso"+suffix).c_str(),("Additional Lepton1 pfCombRelIso ("+suffix+")").c_str(), bin_iso, min_iso, max_iso );
    ZZH_additionalLepton2_pfCombRelIso = new TH1F(("additionalLepton2_pfCombRelIso"+suffix).c_str(),("Additional Lepton2 pfCombRelIso ("+suffix+")").c_str(), bin_iso, min_iso, max_iso );
    ZZH_additionalLepton1_dxy = new TH1F(("additionalLepton1_dxy"+suffix).c_str(),("Additional Lepton1 dxy ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    ZZH_additionalLepton2_dxy = new TH1F(("additionalLepton2_dxy"+suffix).c_str(),("Additional Lepton2 dxy ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    ZZH_additionalLepton1_dz = new TH1F(("additionalLepton1_dz"+suffix).c_str(),("Additional Lepton1 dz ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );
    ZZH_additionalLepton2_dz = new TH1F(("additionalLepton2_dz"+suffix).c_str(),("Additional Lepton2 dz ("+suffix+")").c_str(), bin_dxy, min_dxy, max_dxy );

    ZZH_ZMass = new TH1F(("ZMass"+suffix).c_str(),(" Z Mass ("+suffix+")").c_str(), 100, 50, 150 );
    ZZH_ZPt = new TH1F(("ZPt"+suffix).c_str(),(" Z Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );
    ZZH_WMass = new TH1F(("WMass"+suffix).c_str(),(" W Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass );
    ZZH_WPt = new TH1F(("WPt"+suffix).c_str(),(" W Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );

    ZZH_ZZMass = new TH1F(("ZZMass"+suffix).c_str(),(" ZZ Mass ("+suffix+")").c_str(), 100, 50, 150 );
    ZZH_ZZPt = new TH1F(("ZZPt"+suffix).c_str(),(" ZZ Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );
    ZZH_WZMass = new TH1F(("WZMass"+suffix).c_str(),(" WZ Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass );
    ZZH_WZPt = new TH1F(("WZPt"+suffix).c_str(),(" WZ Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt );

    ZZH_ZZ_dPhi = new TH1F(("ZZ_dPhi"+suffix).c_str(),(" ZZ delta Phi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi );
    ZZH_ZZ_dEta = new TH1F(("ZZ_dEta"+suffix).c_str(),(" ZZ delta Eta ("+suffix+")").c_str(), bin_deltaEta, min_deltaEta, max_deltaEta );
    ZZH_ZZ_dR = new TH1F(("ZZ_dR"+suffix).c_str(),(" ZZ delta R ("+suffix+")").c_str(), bin_deltaR, min_deltaR, max_deltaR );
    ZZH_WZ_dPhi = new TH1F(("WZ_dPhi"+suffix).c_str(),(" WZ delta Phi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi );
    ZZH_WZ_dEta = new TH1F(("WZ_dEta"+suffix).c_str(),(" WZ delta Eta ("+suffix+")").c_str(), bin_deltaEta, min_deltaEta, max_deltaEta );
    ZZH_WZ_dR = new TH1F(("WZ_dR"+suffix).c_str(),(" WZ delta R ("+suffix+")").c_str(), bin_deltaR, min_deltaR, max_deltaR );


  }
  
  virtual void fill(ntupleReader &iEvent,float w) {
      
    ZZH_nPVs->Fill(iEvent.nPVs, w);
    ZZH_addJets->Fill(iEvent.CountAddJets(), w);

    ZZH_met_et->Fill(iEvent.MET_et, w);
    ZZH_met_sig->Fill(iEvent.MET_sig, w);

    ZZH_vectorLepton1_pt->Fill(iEvent.vLepton_pt[0], w);
    ZZH_vectorLepton2_pt->Fill(iEvent.vLepton_pt[1], w);
    ZZH_vectorLepton1_phi->Fill(iEvent.vLepton_phi[0], w);
    ZZH_vectorLepton2_phi->Fill(iEvent.vLepton_phi[1], w);
    ZZH_vectorLepton1_eta->Fill(iEvent.vLepton_eta[0], w);
    ZZH_vectorLepton2_eta->Fill(iEvent.vLepton_eta[1], w);
    ZZH_vectorLepton1_pfCombRelIso->Fill(iEvent.vLepton_pfCombRelIso[0], w);
    ZZH_vectorLepton2_pfCombRelIso->Fill(iEvent.vLepton_pfCombRelIso[1], w);
    ZZH_vectorLepton1_dxy->Fill(iEvent.vLepton_dxy[0], w);
    ZZH_vectorLepton2_dxy->Fill(iEvent.vLepton_dxy[1], w);
    ZZH_vectorLepton1_dz->Fill(iEvent.vLepton_dz[0], w);
    ZZH_vectorLepton2_dz->Fill(iEvent.vLepton_dz[1], w);

    ZZH_additionalLepton1_pt->Fill(iEvent.aLepton_pt[0], w);
    ZZH_additionalLepton2_pt->Fill(iEvent.aLepton_pt[1], w);
    ZZH_additionalLepton1_phi->Fill(iEvent.aLepton_phi[0], w);
    ZZH_additionalLepton2_phi->Fill(iEvent.aLepton_phi[1], w);
    ZZH_additionalLepton1_eta->Fill(iEvent.aLepton_eta[0], w);
    ZZH_additionalLepton2_eta->Fill(iEvent.aLepton_eta[1], w);
    ZZH_additionalLepton1_pfCombRelIso->Fill(iEvent.aLepton_pfCombRelIso[0], w);
    ZZH_additionalLepton2_pfCombRelIso->Fill(iEvent.aLepton_pfCombRelIso[1], w);
    ZZH_additionalLepton1_dxy->Fill(iEvent.aLepton_dxy[0], w);
    ZZH_additionalLepton2_dxy->Fill(iEvent.aLepton_dxy[1], w);
    ZZH_additionalLepton1_dz->Fill(iEvent.aLepton_dz[0], w);
    ZZH_additionalLepton2_dz->Fill(iEvent.aLepton_dz[1], w);
    
    iType = (VType)iEvent.Vtype;

    V1.SetPtEtaPhiM( iEvent.V_pt,
			iEvent.V_eta,
			iEvent.V_phi,
			iEvent.V_mass );
    addLep1.SetPtEtaPhiM( iEvent.aLepton_pt[1],
			     iEvent.aLepton_eta[1],
			     iEvent.aLepton_phi[1],
			     iEvent.aLepton_mass[1] );
    addLep2.SetPtEtaPhiM( iEvent.aLepton_pt[2],
			     iEvent.aLepton_eta[2],
			     iEvent.aLepton_phi[2],
			     iEvent.aLepton_mass[2] );
    V2 = addLep1 + addLep2;

    if( iType == Zmm || iType == Zee || iType == Znn ){
      ZZH_ZMass->Fill(iEvent.V_mass, w); 
      ZZH_ZPt->Fill(iEvent.V_pt, w);
      ZZH_ZZMass->Fill(V2.M(), w); 
      ZZH_ZZPt->Fill(V2.Pt(), w);
      ZZH_ZZ_dPhi->Fill(V1.DeltaPhi(V2), w); 
      ZZH_ZZ_dEta->Fill(TMath::Abs(V1.Eta() - V2.Eta() ), w); 
      ZZH_ZZ_dR->Fill(V1.DeltaR(V2), w); 
    }
    else{
      ZZH_WMass->Fill(iEvent.V_mass, w);
      ZZH_WPt->Fill(iEvent.V_pt, w); 
      ZZH_WZMass->Fill(V2.M(), w);
      ZZH_WZPt->Fill(V2.Pt(), w); 
      ZZH_WZ_dPhi->Fill(V1.DeltaPhi(V2), w); 
      ZZH_WZ_dEta->Fill(TMath::Abs(V1.Eta() - V2.Eta() ), w); 
      ZZH_WZ_dR->Fill(V1.DeltaR(V2), w); 
    }
    
  
  }

  TLorentzVector addLep1,addLep2,V1,V2;

  TH1F * ZZH_nPVs;
  TH1F * ZZH_addJets;
  TH1F * ZZH_met_et;
  TH1F * ZZH_met_sig;

  TH1F * ZZH_vectorLepton1_pt;
  TH1F * ZZH_vectorLepton2_pt;
  TH1F * ZZH_vectorLepton1_phi;
  TH1F * ZZH_vectorLepton2_phi;
  TH1F * ZZH_vectorLepton1_eta;
  TH1F * ZZH_vectorLepton2_eta;
  TH1F * ZZH_vectorLepton1_pfCombRelIso;
  TH1F * ZZH_vectorLepton2_pfCombRelIso;
  TH1F * ZZH_vectorLepton1_dxy;
  TH1F * ZZH_vectorLepton2_dxy;
  TH1F * ZZH_vectorLepton1_dz;
  TH1F * ZZH_vectorLepton2_dz;
  
  TH1F * ZZH_additionalLepton1_pt;
  TH1F * ZZH_additionalLepton2_pt;
  TH1F * ZZH_additionalLepton1_phi;
  TH1F * ZZH_additionalLepton2_phi;
  TH1F * ZZH_additionalLepton1_eta;
  TH1F * ZZH_additionalLepton2_eta;
  TH1F * ZZH_additionalLepton1_pfCombRelIso;
  TH1F * ZZH_additionalLepton2_pfCombRelIso;
  TH1F * ZZH_additionalLepton1_dxy;
  TH1F * ZZH_additionalLepton2_dxy;
  TH1F * ZZH_additionalLepton1_dz;
  TH1F * ZZH_additionalLepton2_dz;

  TH1F * ZZH_WMass;
  TH1F * ZZH_WPt;
  TH1F * ZZH_WZMass;
  TH1F * ZZH_WZPt;
  TH1F * ZZH_ZMass;
  TH1F * ZZH_ZPt;
  TH1F * ZZH_ZZMass;
  TH1F * ZZH_ZZPt;

  TH1F * ZZH_ZZ_dPhi;
  TH1F * ZZH_ZZ_dEta;
  TH1F * ZZH_ZZ_dR;
  TH1F * ZZH_WZ_dPhi;
  TH1F * ZZH_WZ_dEta;
  TH1F * ZZH_WZ_dR;
 
private:

  Int_t bin_btag;
  Double_t min_btag;
  Double_t max_btag;

  Int_t bin_eta;
  Double_t min_eta;
  Double_t max_eta;

  Int_t bin_phi;
  Double_t min_phi;
  Double_t max_phi;

  Int_t bin_deltaEta;
  Double_t min_deltaEta;
  Double_t max_deltaEta;

  Int_t bin_deltaPhi;
  Double_t min_deltaPhi;
  Double_t max_deltaPhi;

  Int_t bin_deltaR;
  Double_t min_deltaR;
  Double_t max_deltaR;

  Int_t bin_mass;
  Double_t min_mass;
  Double_t max_mass;

  Int_t bin_pt;
  Double_t min_pt;
  Double_t max_pt;

  Int_t bin_npvs;
  Double_t min_npvs;
  Double_t max_npvs;

  Int_t bin_addJets;
  Double_t min_addJets;
  Double_t max_addJets;

  Int_t bin_hel;
  Double_t min_hel;
  Double_t max_hel;

  Int_t bin_iso;
  Double_t min_iso;
  Double_t max_iso;

  Int_t bin_dxy;
  Double_t min_dxy;
  Double_t max_dxy;

};


// FIX ME

/* class HardJetHistos : public Histos { */
    
/* public: */

/*   virtual void book(TFile &f, std::string suffix) { */

/*     TDirectory *subDir; */
/*     if( ! f.GetDirectory(suffix.c_str()) ) */
/*       subDir = f.mkdir(suffix.c_str()); */
/*     else  */
/*       subDir = f.GetDirectory(suffix.c_str()); */
/*     subDir->cd(); */

/*     bin_mass = 500; */
/*     min_mass = 0; */
/*     max_mass = 300; */
    
/*     bin_pt = 500; */
/*     min_pt = 0; */
/*     max_pt = 500; */
    
/*     bin_hel = 50; */
/*     min_hel = 0; */
/*     max_hel = 1; */

/*     bin_btag = 20; */
/*     min_btag = 0; */
/*     max_btag = 1; */

/*     bin_deltaR = bin_deltaPhi = bin_deltaEta = 20; */
/*     min_deltaR = min_deltaPhi = min_deltaEta = 0; */
/*     max_deltaR = max_deltaPhi = max_deltaEta = 5; */

/*     //Candidates */

/*     HardJetH_subJet1_pt = new TH1F(("SubJet1_pt"+suffix).c_str(),("Sub Jet1 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt ); */
/*     HardJetH_subJet2_pt = new TH1F(("SubJet2_pt"+suffix).c_str(),("Sub Jet2 pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt ); */
/*     HardJetH_subJet1_bTag = new TH1F(("SubJet1_bTag"+suffix).c_str(),("Sub Jet1 bTag ("+suffix+")").c_str(), bin_btag, min_btag, max_btag ); */
/*     HardJetH_subJet2_bTag = new TH1F(("SubJet2_bTag"+suffix).c_str(),("Sub Jet2 bTag ("+suffix+")").c_str(), bin_btag, min_btag, max_btag ); */
/*     HardJetH_subJets_dR = new TH1F(("SubJets_dR"+suffix).c_str(),("Sub Jets deltaR ("+suffix+")").c_str(), bin_deltaR, min_deltaR, max_deltaR ); */
/*     HardJetH_subJets_dPhi = new TH1F(("SubJets_dPhi"+suffix).c_str(),("Sub Jets deltaPhi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi ); */
/*     HardJetH_subJets_dEta = new TH1F(("SubJets_dEta"+suffix).c_str(),("Sub Jets deltaEta ("+suffix+")").c_str(), bin_deltaEta, min_deltaEta, max_deltaEta ); */

/*     HardJetH_HMass = new TH1F(("HiggsMass"+suffix).c_str(),(" Higgs Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass ); */
/*     HardJetH_HPt = new TH1F(("HiggsPt"+suffix).c_str(),(" Higgs Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt ); */
/*     HardJetH_HHel = new TH1F(("HiggsHel"+suffix).c_str(),("Higgs helicity angle ("+suffix+")").c_str(), bin_hel, min_hel, max_hel ); */

/*     HardJetH_ZMass = new TH1F(("ZMass"+suffix).c_str(),(" Z Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass ); */
/*     HardJetH_ZPt = new TH1F(("ZPt"+suffix).c_str(),(" Z Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt ); */
/*     HardJetH_ZH_dPhi = new TH1F(("ZH_dPhi"+suffix).c_str(),(" ZH delta Phi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi ); */

/*     HardJetH_WMass = new TH1F(("WMass"+suffix).c_str(),(" W Mass ("+suffix+")").c_str(), bin_mass, min_mass, max_mass ); */
/*     HardJetH_WPt = new TH1F(("WPt"+suffix).c_str(),(" W Pt ("+suffix+")").c_str(), bin_pt, min_pt, max_pt ); */
/*     HardJetH_WH_dPhi = new TH1F(("WH_dPhi"+suffix).c_str(),(" WH delta Phi ("+suffix+")").c_str(), bin_deltaPhi, min_deltaPhi, max_deltaPhi ); */

/*   } */
  
/*   virtual void fill(ntupleReader &iEvent,float w) { */

/*     const VHbbEvent *iEvent = entry.getVHbbEvent(); */
/* if(iEvent) */
/* {    const std::vector<VHbbCandidate> *iCand = entry.getVHbbCandidate(); */

/*     //Candidates */
/*     if(iCand->size() > 0){ */
/*       VHbbCandidate::CandidateType iCandType = candidateType; */
/*       VHbbCandidate::HiggsCandidate H = H; */
/*       VHbbCandidate::VectorCandidate V = V; */
/*       std::vector<VHbbEvent::HardJet> iHardJets = iEvent->hardJets; */
/*       VHbbEvent::HardJet iHardJet = iHardJets; */

/*       HardJetH_subJet1_pt->Fill(iEvent.iHardJet.subFourMomentum.at(0).Pt(), w); */
/*       HardJetH_subJet2_pt->Fill(iEvent.iHardJet.subFourMomentum.at(1).Pt(), w); */
/*       //SubJet information on btag missing */
/* //       HardJetH_subJet1_bTag->Fill(iEvent.iHardJet.at(0).csv, w); */
/* //       HardJetH_subJet2_bTag->Fill(iEvent.iHardJet.at(1).csv, w); */
/*       HardJetH_subJets_dR->Fill(iEvent.iHardJet.subFourMomentum.at(0).DeltaR(iHardJet.subFourMomentum.at(1)), w); */
/*       HardJetH_subJets_dPhi->Fill(iEvent.iHardJet.subFourMomentum.at(0).DeltaPhi(iHardJet.subFourMomentum.at(1)), w); */
/*       HardJetH_subJets_dEta->Fill(iEvent.TMath::Abs(iHardJet.subFourMomentum.at(0).Eta()-iHardJet.subFourMomentum.at(1).Eta()), w); */

/*       //Here there should be the higgs candidate from HardJet */
/* //       HardJetH_HMass->Fill(iEvent.H.p4.M(), w);  */
/* //       HardJetH_HPt->Fill(iEvent.H.p4.Pt(), w);  */
/* //      //    HardJetH_HHel->Fill(iEvent.H.hel(), w);  */
/* //       if( iCandType == VHbbCandidate::Zmumu || iCandType == VHbbCandidate::Zee || iCandType == VHbbCandidate::Znn ){ */
/* // 	HardJetH_ZMass->Fill(iEvent.V.p4.M(), w);  */
/* // 	HardJetH_ZPt->Fill(iEvent.V.p4.Pt(), w); */
/* // 	HardJetH_ZH_dPhi->Fill(iEvent.V.p4.DeltaPhi(H.p4.Phi()), w);  */
/* //       }  */
/* //       else if(iCandType == VHbbCandidate::Wen || iCandType == VHbbCandidate::Wmun){ */
/* // 	HardJetH_WMass->Fill(iEvent.V.p4.M(), w);  */
/* // 	HardJetH_WPt->Fill(iEvent.V.p4.Pt(), w);  */
/* // 	HardJetH_WH_dPhi->Fill(iEvent.V.p4.DeltaPhi(H.p4.Phi()), w);  */
/* //       } */
/*  } */
/*     } */
/*   } */
  
/*   TH1F * HardJetH_subJet1_pt; */
/*   TH1F * HardJetH_subJet2_pt; */
/*   TH1F * HardJetH_subJet1_bTag; */
/*   TH1F * HardJetH_subJet2_bTag; */
/*   TH1F * HardJetH_subJets_dR; */
/*   TH1F * HardJetH_subJets_dPhi; */
/*   TH1F * HardJetH_subJets_dEta; */

/*   TH1F * HardJetH_HMass; */
/*   TH1F * HardJetH_HPt; */
/*   TH1F * HardJetH_HHel; */
/*   TH1F * HardJetH_WMass; */
/*   TH1F * HardJetH_WPt; */
/*   TH1F * HardJetH_WH_dPhi; */
/*   TH1F * HardJetH_ZMass; */
/*   TH1F * HardJetH_ZPt; */
/*   TH1F * HardJetH_ZH_dPhi; */

/* private: */

/*   Int_t bin_btag; */
/*   Double_t min_btag; */
/*   Double_t max_btag; */

/*   Int_t bin_deltaEta; */
/*   Double_t min_deltaEta; */
/*   Double_t max_deltaEta; */

/*   Int_t bin_deltaPhi; */
/*   Double_t min_deltaPhi; */
/*   Double_t max_deltaPhi; */

/*   Int_t bin_deltaR; */
/*   Double_t min_deltaR; */
/*   Double_t max_deltaR; */

/*   Int_t bin_mass; */
/*   Double_t min_mass; */
/*   Double_t max_mass; */

/*   Int_t bin_pt; */
/*   Double_t min_pt; */
/*   Double_t max_pt; */

/*   Int_t bin_hel; */
/*   Double_t min_hel; */
/*   Double_t max_hel; */

/* }; */


#endif
