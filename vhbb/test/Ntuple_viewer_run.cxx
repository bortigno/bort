// This is to see the results of the ZH_channel.cxx in version 7 analyzer v17
// ZH    : N processed events: 153252   ; L = 5964.8
// ZZ    : N processed events: 1960000  ; L = 498.3
// TTbar : N processed events: 27632867 ; L = 323.2
// ZJets : N processed events: 7854056  ; L = 305.2
// March 2011
// Bortignon Pierluigi


#include <TSystem.h>
#include <iostream>
#include "TCanvas.h"
#include "Ntuple_viewer.C"
#include "TH1.h"
#include "TH2.h"
#include <THStack.h>
#include "TMath.h"
#include <TPad.h>
#include <TLegend.h>


int Ntuple_viewer_run( void ){

  Double_t mass_window_lower = 100;
  Double_t mass_window_higher = 140;

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);

  TCanvas * c1 = new TCanvas("c1","c1",600,600);
  TCanvas * c2 = new TCanvas("c2","c2",600,600);
  TCanvas * c3 = new TCanvas("c3","c3",600,600);
  TCanvas * c4 = new TCanvas("c4","c4",600,600);
  TCanvas * c5 = new TCanvas("c5","c5",600,600);
  TCanvas * c6 = new TCanvas("c6","c6",600,600);
  TCanvas * c7 = new TCanvas("c7","c7",600,600);
  TCanvas * c8 = new TCanvas("c8","c8",600,600);
  TCanvas * c9 = new TCanvas("c9","c9",600,600);
  TCanvas * c10 = new TCanvas("c10","c10",600,600);
  TCanvas * c11 = new TCanvas("c11","c11",600,600);


  Double_t Zcandidate_ptCut_lower = 120;
  Double_t higgsCandidate_ptCut_lower = 110;
  Double_t Zcandidate_ptCut_higher = 10000;
  Double_t higgsCandidate_ptCut_higher = 10000;
  Double_t helicityCut = 1;
  Double_t leadingDeltaThetaCut = 1000;
  Double_t jetPtAsymmetryCut = 1;
  Double_t higgsLowerMassCut = 0;
  Double_t higgsHigherMassCut = 500;

  Long64_t entries = 0;

  Double_t VH_counter = 0;
  Double_t VV_counter = 0;
  Double_t TTbar_counter = 0;
  Double_t VJ_counter = 0;

  Double_t Integrated_luminosity = 30.;
  Double_t VJ_normalisation = 305.2;
  Double_t VH_normalisation = 5964.8;
  Double_t VV_normalisation = 498.3;
  Double_t TTbar_normalisation = 323.2;

  Int_t bin_mass = 600;
  Double_t min_mass = 0;
  Double_t max_mass = 200;

  Int_t bin_pull = 30;
  Double_t min_pull = 0;
  Double_t max_pull = 3.14;

  Int_t bin_hel = 20;
  Double_t min_hel = -1;
  Double_t max_hel = 1;

  Int_t bin_dR = 50;
  Double_t min_dR = 0;
  Double_t max_dR = 5;

  TH1D * VHpull = new TH1D("VHpull","VH dijet pull",bin_pull, min_pull, max_pull);
  TH1D * TTbarPull = new TH1D("TTbarPull","TTbar dijet pull",bin_pull, min_pull, max_pull);
  TH1D * VJpull = new TH1D("VJpull","VJ dijet pull",bin_pull, min_pull, max_pull);
  TH1D * VVpull = new TH1D("VVpull","VV dijet pull",bin_pull, min_pull, max_pull);

  TH1D * VHzHel = new TH1D("VHzHel","VH zHel",bin_hel, min_hel, max_hel);
  TH1D * TTbarZHel = new TH1D("TTbarZHel","TTbar zHel",bin_hel, min_hel, max_hel);
  TH1D * VJzHel = new TH1D("VJzHel","VJ zHel",bin_hel, min_hel, max_hel);
  TH1D * VVzHel = new TH1D("VVzHel","VV zHel",bin_hel, min_hel, max_hel);

  TH1D * VHhel = new TH1D("VHhel","VH hel",bin_hel, min_hel, max_hel);
  TH1D * TTbarHel = new TH1D("TTbarHel","TTbar hel",bin_hel, min_hel, max_hel);
  TH1D * VJhel = new TH1D("VJhel","VJ hel",bin_hel, min_hel, max_hel);
  TH1D * VVhel = new TH1D("VVhel","VV hel",bin_hel, min_hel, max_hel);

  TH1D * VHmass = new TH1D("VHmass","VH dijet mass",bin_mass, min_mass, max_mass);
  TH1D * TTbarMass = new TH1D("TTbarMass","TTbar dijet mass",bin_mass, min_mass, max_mass);
  TH1D * VJmass = new TH1D("VJmass","VJ dijet mass",bin_mass, min_mass, max_mass);
  TH1D * VVmass = new TH1D("VVmass","VV dijet mass",bin_mass, min_mass, max_mass);

  THStack *hCand = new THStack("hCand","higgs candidate");
  THStack *hHel = new THStack("hHel","Helicity");
  THStack *hPull = new THStack("hPull","Pull angle");

  TH2D * VHhel_ptA = new TH2D("VHhel_ptA","VH hel vs ptAs",bin_hel, min_hel, max_hel, bin_hel, min_hel, max_hel);
  TH2D * VJhel_ptA = new TH2D("VJhel_ptA","VJ hel vs ptAs",bin_hel, min_hel, max_hel, bin_hel, min_hel, max_hel);

  TH2D * VHdR_pull = new TH2D("VHdR_pull","VH dR vs pulls",bin_dR, min_dR, max_dR, bin_pull, min_pull, max_pull);
  TH2D * VJdR_pull = new TH2D("VJdR_pull","VJ dR vs pulls",bin_dR, min_dR, max_dR, bin_pull, min_pull, max_pull);

  TH2D * VHdR_hel = new TH2D("VHdR_hel","VH dR vs hel",bin_dR, min_dR, max_dR, bin_hel, min_hel, max_hel);
  TH2D * VJdR_hel = new TH2D("VJdR_hel","VJ dR vs hel",bin_dR, min_dR, max_dR, bin_hel, min_hel, max_hel);

  //  THStack *hCandHelicityCut = new THStack("hCandHelicityCut","higgs candidate helicity cut");
  //  gSystem->CompileMacro("Ntuple_viewer.C");



  Ntuple_viewer VH("ZH_channel_v7/ZH_channel_ZH/ZMuMu_channel_v17_ZH.root");

  entries  = VH.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    VH.GetEntry(i);

    VHzHel->Fill(VH.Zhelicity);

    if( VH.leading_higgsHelicity > helicityCut 
	or VH.leadingDeltaTheta > leadingDeltaThetaCut 
	or VH.jetPtAsymmetry > jetPtAsymmetryCut
	or VH.higgsCandidate_mass < higgsLowerMassCut 
	or VH.higgsCandidate_mass > higgsHigherMassCut 
	or VH.higgsCandidate_pt < higgsCandidate_ptCut_lower 
	or VH.higgsCandidate_pt > higgsCandidate_ptCut_higher 
	or VH.Zcandidate_pt < Zcandidate_ptCut_lower 	
	or VH.Zcandidate_pt > Zcandidate_ptCut_higher )

      continue;

    if( VH.higgsCandidate_mass > mass_window_lower 
	and VH.higgsCandidate_mass < mass_window_higher )
      VH_counter++;

    VHmass->Fill(VH.higgsCandidate_mass);
    VHpull->Fill(TMath::Abs(VH.leadingDeltaTheta));
    VHhel->Fill(TMath::Abs(VH.leading_higgsHelicity));
    VHhel_ptA->Fill( VH.leading_higgsHelicity, VH.jetPtAsymmetry);
    VHdR_pull->Fill( VH.jetDeltaR, VH.leadingDeltaTheta);
    VHdR_hel->Fill( VH.jetDeltaR, VH.leading_higgsHelicity);

  }

  //mass
  VHmass->SetTitle("Jet mass ZH");
  VHmass->Rebin(24);
  VHmass->GetXaxis()->SetTitle("mass");
  VHmass->GetYaxis()->SetLabelSize(0.03);
  VHmass->GetXaxis()->SetLabelSize(0.03);
  VHmass->SetFillColor(kRed);
  VHmass->SetFillStyle(3002);
  VHmass->DrawNormalized();
  VHmass->Scale(Integrated_luminosity/VH_normalisation);

  //pull
  VHpull->SetTitle("Leading jet pull ZH");
  VHpull->GetXaxis()->SetTitle("pull");
  VHpull->GetYaxis()->SetLabelSize(0.03);
  VHpull->GetXaxis()->SetLabelSize(0.03);
  VHpull->SetFillColor(kRed);
  VHpull->SetFillStyle(3002);
  VHpull->DrawNormalized();
  VHpull->Scale(Integrated_luminosity/VH_normalisation);
  hPull->Add(VHpull);

  //hel
  VHhel->SetTitle("Leading jet hel ZH");
  VHhel->GetXaxis()->SetTitle("hel");
  VHhel->GetYaxis()->SetLabelSize(0.03);
  VHhel->GetXaxis()->SetLabelSize(0.03);
  VHhel->SetFillColor(kRed);
  VHhel->SetFillStyle(3002);
  VHhel->DrawNormalized();
  VHhel->Scale(Integrated_luminosity/VH_normalisation);
  hHel->Add(VHhel);


  Ntuple_viewer VJ("ZH_channel_v7/ZH_channel_ZJets/ZMuMu_channel_v17_ZJets.root");

  entries  = VJ.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    VJ.GetEntry(i);

    VJzHel->Fill(VJ.Zhelicity);

    if( VJ.leading_higgsHelicity > helicityCut 
	or VJ.leadingDeltaTheta > leadingDeltaThetaCut 
	or VJ.jetPtAsymmetry > jetPtAsymmetryCut
	or VJ.higgsCandidate_mass < higgsLowerMassCut 
	or VJ.higgsCandidate_mass > higgsHigherMassCut 
	or VJ.higgsCandidate_pt < higgsCandidate_ptCut_lower 
	or VJ.higgsCandidate_pt > higgsCandidate_ptCut_higher
	or VJ.Zcandidate_pt < Zcandidate_ptCut_lower 
	or VJ.Zcandidate_pt > Zcandidate_ptCut_higher )
      continue;

    if( VJ.higgsCandidate_mass > mass_window_lower 
	and VJ.higgsCandidate_mass < mass_window_higher )
      VJ_counter++;
    VJmass->Fill(VJ.higgsCandidate_mass);
    VJpull->Fill(TMath::Abs(VJ.leadingDeltaTheta));
    VJhel->Fill(TMath::Abs(VJ.leading_higgsHelicity));
    VJhel_ptA->Fill( VJ.leading_higgsHelicity, VJ.jetPtAsymmetry);
    VJdR_pull->Fill( VJ.jetDeltaR, VJ.leadingDeltaTheta);
    VJdR_hel->Fill( VJ.jetDeltaR, VJ.leading_higgsHelicity);

  }
  //mass
  VJmass->SetTitle("Jet mass ZJets");
  VJmass->Rebin(24);
  VJmass->GetXaxis()->SetTitle("mass");
  VJmass->GetYaxis()->SetLabelSize(0.03);
  VJmass->GetXaxis()->SetLabelSize(0.03);
  VJmass->SetFillColor(kGreen+2);
  VJmass->SetFillStyle(3002);
  VJmass->DrawNormalized("same");
  VJmass->Scale(Integrated_luminosity/VJ_normalisation);

  //pull
  VJpull->SetTitle("Leading jet pull ZJets");
  VJpull->GetXaxis()->SetTitle("pull");
  VJpull->GetYaxis()->SetLabelSize(0.03);
  VJpull->GetXaxis()->SetLabelSize(0.03);
  VJpull->SetFillColor(kGreen+2);
  VJpull->SetFillStyle(3002);
  VJpull->DrawNormalized("same");
  VJpull->Scale(Integrated_luminosity/VJ_normalisation);
  hPull->Add(VJpull);

  //hel
  VJhel->SetTitle("Leading jet hel ZJets");
  VJhel->GetXaxis()->SetTitle("hel");
  VJhel->GetYaxis()->SetLabelSize(0.03);
  VJhel->GetXaxis()->SetLabelSize(0.03);
  VJhel->SetFillColor(kGreen+2);
  VJhel->SetFillStyle(3002);
  VJhel->DrawNormalized("same");
  VJhel->Scale(Integrated_luminosity/VJ_normalisation);
  hHel->Add(VJhel);


  Ntuple_viewer TTbar("ZH_channel_v7/ZH_channel_TTbar/ZMuMu_channel_v17_TTbar.root");

  entries  = TTbar.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    TTbar.GetEntry(i);

    TTbarZHel->Fill(TTbar.Zhelicity);

    if( TTbar.leading_higgsHelicity > helicityCut 
	or TTbar.leadingDeltaTheta > leadingDeltaThetaCut 
	or TTbar.jetPtAsymmetry > jetPtAsymmetryCut
	or TTbar.higgsCandidate_mass < higgsLowerMassCut 
	or TTbar.higgsCandidate_mass > higgsHigherMassCut 
	or TTbar.higgsCandidate_pt < higgsCandidate_ptCut_lower 
	or TTbar.higgsCandidate_pt > higgsCandidate_ptCut_higher
	or TTbar.Zcandidate_pt < Zcandidate_ptCut_lower 
	or TTbar.Zcandidate_pt > Zcandidate_ptCut_higher )
      continue;

    if( TTbar.higgsCandidate_mass > mass_window_lower 
	and TTbar.higgsCandidate_mass < mass_window_higher )
      TTbar_counter++;

    TTbarMass->Fill(TTbar.higgsCandidate_mass);
    TTbarPull->Fill(TMath::Abs(TTbar.leadingDeltaTheta));
    TTbarHel->Fill(TMath::Abs(TTbar.leading_higgsHelicity));

  }

  //mass
  TTbarMass->SetTitle("Jet mass TTbar");
  TTbarMass->Rebin(24);
  TTbarMass->GetXaxis()->SetTitle("mass");
  TTbarMass->GetYaxis()->SetLabelSize(0.03);
  TTbarMass->GetXaxis()->SetLabelSize(0.03);
  TTbarMass->SetFillColor(kBlue);
  TTbarMass->SetFillStyle(3002);
  TTbarMass->DrawNormalized("same");
  TTbarMass->Scale(Integrated_luminosity/TTbar_normalisation);

  //pull
  TTbarPull->SetTitle("Leading jet pull TTbar");
  TTbarPull->GetXaxis()->SetTitle("pull");
  TTbarPull->GetYaxis()->SetLabelSize(0.03);
  TTbarPull->GetXaxis()->SetLabelSize(0.03);
  TTbarPull->SetFillColor(kBlue);
  TTbarPull->SetFillStyle(3002);
  TTbarPull->DrawNormalized("same");
  TTbarPull->Scale(Integrated_luminosity/TTbar_normalisation);
  hPull->Add(TTbarPull);

  //hel
  TTbarHel->SetTitle("Leading jet hel TTbar");
  TTbarHel->GetXaxis()->SetTitle("hel");
  TTbarHel->GetYaxis()->SetLabelSize(0.03);
  TTbarHel->GetXaxis()->SetLabelSize(0.03);
  TTbarHel->SetFillColor(kBlue);
  TTbarHel->SetFillStyle(3002);
  TTbarHel->DrawNormalized("same");
  TTbarHel->Scale(Integrated_luminosity/TTbar_normalisation);
  hHel->Add(TTbarHel);


  Ntuple_viewer VV("ZH_channel_v7/ZH_channel_ZZ/ZMuMu_channel_v17_ZZ.root");

  entries  = VV.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    VV.GetEntry(i);

    VVzHel->Fill(VV.Zhelicity);

    if( VV.leading_higgsHelicity > helicityCut 
	or VV.leadingDeltaTheta > leadingDeltaThetaCut 
	or VV.jetPtAsymmetry > jetPtAsymmetryCut
	or VV.higgsCandidate_mass < higgsLowerMassCut 
	or VV.higgsCandidate_mass > higgsHigherMassCut 
	or VV.higgsCandidate_pt < higgsCandidate_ptCut_lower 
	or VV.higgsCandidate_pt > higgsCandidate_ptCut_higher
	or VV.Zcandidate_pt < Zcandidate_ptCut_lower
	or VV.Zcandidate_pt > Zcandidate_ptCut_higher )
      continue;

    if( VV.higgsCandidate_mass > mass_window_lower 
	and VV.higgsCandidate_mass < mass_window_higher )
      VV_counter++;
    VVmass->Fill(VV.higgsCandidate_mass);
    VVpull->Fill(TMath::Abs(VV.leadingDeltaTheta));
    VVhel->Fill(TMath::Abs(VV.leading_higgsHelicity));

  }
  // mass
  VVmass->SetTitle("Jet mass ZZ");
  VVmass->Rebin(24);
  VVmass->GetXaxis()->SetTitle("mass");
  VVmass->GetYaxis()->SetLabelSize(0.03);
  VVmass->GetXaxis()->SetLabelSize(0.03);
  VVmass->SetFillColor(kOrange+3);
  VVmass->SetFillStyle(3002);
  VVmass->DrawNormalized("same");
  VVmass->Scale(Integrated_luminosity/VV_normalisation);

  // pull 
  VVpull->SetTitle("Leading jet pull ZZ");
  VVpull->GetXaxis()->SetTitle("pull");
  VVpull->GetYaxis()->SetLabelSize(0.03);
  VVpull->GetXaxis()->SetLabelSize(0.03);
  VVpull->SetFillColor(kOrange+3);
  VVpull->SetFillStyle(3002);
  VVpull->DrawNormalized("same");
  VVpull->Scale(Integrated_luminosity/VV_normalisation);
  hPull->Add(VVpull);

  // hel 
  VVhel->SetTitle("Leading jet hel ZZ");
  VVhel->GetXaxis()->SetTitle("hel");
  VVhel->GetYaxis()->SetLabelSize(0.03);
  VVhel->GetXaxis()->SetLabelSize(0.03);
  VVhel->SetFillColor(kOrange+3);
  VVhel->SetFillStyle(3002);
  VVhel->DrawNormalized("same");
  VVhel->Scale(Integrated_luminosity/VV_normalisation);
  hHel->Add(VVhel);







  hCand->Add(VJmass);
  hCand->Add(TTbarMass);
  hCand->Add(VVmass);
  hCand->Add(VHmass);
  c1->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  hCand->Draw();
  hCand->GetXaxis()->SetTitle("M_{jj}");
  hCand->GetXaxis()->SetLabelSize(0.03);
  TLegend* CandLegend = new TLegend( 0.55, 0.65, 0.88, 0.88 );
  CandLegend->AddEntry(VHmass,"VH mass");
  CandLegend->AddEntry(VVmass,"VV mass");
  CandLegend->AddEntry(TTbarMass,"TTbar mass");
  CandLegend->AddEntry(VJmass,"VJ mass");
  CandLegend->SetFillColor(kRed);
  CandLegend->SetFillStyle(3002);
  CandLegend->Draw("same");

  c2->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  hPull->Draw();
  hPull->GetXaxis()->SetTitle("#Delta#theta_{t}");
  hPull->GetXaxis()->SetLabelSize(0.03);
  TLegend* PullLegend = new TLegend( 0.55, 0.65, 0.88, 0.88 );
  PullLegend->AddEntry(VHpull,"VH pull");
  PullLegend->AddEntry(VVpull,"VV pull");
  PullLegend->AddEntry(TTbarPull,"TTbar pull");
  PullLegend->AddEntry(VJpull,"VJ pull");
  PullLegend->SetFillColor(kRed);
  PullLegend->SetFillStyle(3002);
  PullLegend->Draw("same");

  c3->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  hHel->Draw();
  hHel->GetXaxis()->SetTitle("cos#theta^{*}");
  hHel->GetXaxis()->SetLabelSize(0.03);
  TLegend* HelLegend = new TLegend( 0.15, 0.65, 0.48, 0.88 );
  HelLegend->AddEntry(VHhel,"VH hel");
  HelLegend->AddEntry(VVhel,"VV hel");
  HelLegend->AddEntry(TTbarHel,"TTbar hel");
  HelLegend->AddEntry(VJhel,"VJ hel");
  HelLegend->SetFillColor(kRed);
  HelLegend->SetFillStyle(3002);
  HelLegend->Draw("same");

  c4->cd();
  gPad->SetGridy();
  gPad->SetGridx();
//   VHzHel->DrawNormalized();
//   VJzHel->DrawNormalized("same");
  VHhel->DrawNormalized();
  VJhel->DrawNormalized("same");
//   VVhel->DrawNormalized("same");

  c5->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  VHpull->DrawNormalized();
  VJpull->DrawNormalized("same");
//   VVpull->DrawNormalized("same");

  c6->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  VJhel_ptA->DrawNormalized("COLZ");

  c7->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  VHhel_ptA->DrawNormalized("COLZ");

  c8->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  VJdR_pull->DrawNormalized("COLZ");

  c9->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  VHdR_pull->DrawNormalized("COLZ");

  c10->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  VJdR_hel->DrawNormalized("COLZ");

  c11->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  VHdR_hel->DrawNormalized("COLZ");


  VH_counter *= (Integrated_luminosity/VH_normalisation);
  VV_counter *= (Integrated_luminosity/VV_normalisation);
  TTbar_counter *= (Integrated_luminosity/TTbar_normalisation);
  VJ_counter *= (Integrated_luminosity/VJ_normalisation);

  std::cout << "VH = " << VH_counter << std::endl;
  std::cout << "VV = " << VV_counter << std::endl;
  std::cout << "VJ = " << VJ_counter << std::endl;
  std::cout << "TTbar = " << TTbar_counter << std::endl;
  std::cout << "Total background = " << VV_counter+TTbar_counter+VJ_counter << std::endl;
  std::cout << "Significance = " << VH_counter/TMath::Sqrt(VV_counter+TTbar_counter+VJ_counter) << std::endl;
  std::cout << "S/B = " << VH_counter/(VV_counter+TTbar_counter+VJ_counter) << std::endl;

  return 0;

}
