// This is to see the results of the GammaJet
// April 2011
// Bortignon Pierluigi


#include <TSystem.h>
#include <iostream>
#include "TCanvas.h"
#include "GammaJet.C"
#include "TH1.h"
#include "TH2.h"
#include <THStack.h>
#include "TMath.h"
#include <TPad.h>
#include <TLegend.h>


int GammaJet_run( void ){

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
//   TCanvas * c7 = new TCanvas("c7","c7",600,600);

  Int_t nOfak5Cut = 20000;
  Double_t photonCandidatePtCut = 55;
  Double_t gluonCandidatePtCut = 40;//photonCandidatePtCut-sqrt(photonCandidatePtCut);
  Double_t gluonCandidateMassCut = 0;
  Double_t gluonCandidateMassCut2 = 140000;
  Double_t leadingBTagCut = -1000000;
  Double_t secondLeadingBTagCut = -1000000;
  Double_t leadingPullCut = 500;

  Long64_t entries = 0;

  Double_t Integrated_luminosity = 18.26;
  Double_t GJdata_normalisation = 18.26; 
  Double_t GJ2040_normalisation = 135.60;
  Double_t GJ40100_normalisation = 6.84;
  Double_t GJ100200_normalisation = 21.72;
  Double_t GJ200inf_normalisation = 107.96;

  Int_t bin_mass = 20;
  Double_t min_mass = 0;
  Double_t max_mass = 400;

  Int_t bin_pull = 12;
  Double_t min_pull = 0;
  Double_t max_pull = 3.14;

  Int_t bin_hel = 10;
  Double_t min_hel = 0;
  Double_t max_hel = 1;

  Int_t bin_deltaR = 10;
  Double_t min_deltaR = 0;
  Double_t max_deltaR = 5;

  Int_t bin_photonPt = 30;
  Double_t min_photonPt = 0;
  Double_t max_photonPt = 300;

  Int_t bin_gluonPt = 30;
  Double_t min_gluonPt = 0;
  Double_t max_gluonPt = 300;


  TH1D * GJdatadeltaR = new TH1D("GJdatadeltaR","GJdata deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJdatamass = new TH1D("GJdatamass","GJdata dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJdatapull = new TH1D("GJdatapull","GJdata dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJdatahel = new TH1D("GJdatahel","GJdata dijet hel",bin_hel, min_hel, max_hel);
  TH1D * GJdataphotonPt = new TH1D("GJdataphotonPt","GJdata dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  GJdataphotonPt->Sumw2();
  TH1D * GJdatagluonPt = new TH1D("GJdatagluonPt","GJdata dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);
  GJdatagluonPt->Sumw2();

  TH1D * GJMCdeltaR = new TH1D("GJMCdeltaR","GJMC deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJMCmass = new TH1D("GJMCmass","GJMC dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJMCpull = new TH1D("GJMCpull","GJMC dijet pull",bin_pull, min_pull, max_pull);
  GJMCpull->GetXaxis()->SetTitle("|#Delta#theta_{t}|");
  GJMCpull->GetYaxis()->SetTitle("Normalized entries");
  GJMCpull->GetYaxis()->SetLabelSize(0.03);
  GJMCpull->GetYaxis()->SetTitleOffset(1.3);
  GJMCpull->GetXaxis()->SetLabelSize(0.03);
  GJMCpull->SetFillColor(kAzure+7);
  GJMCpull->SetFillStyle(3002);
  GJMCpull->SetLineColor(kAzure+7);
  TH1D * GJMChel = new TH1D("GJMChel","GJMC dijet hel",bin_hel, min_hel, max_hel);
  GJMChel->GetXaxis()->SetTitle("|cos#theta*|");
  GJMChel->GetYaxis()->SetTitle("Normalized entries");
  GJMChel->GetYaxis()->SetLabelSize(0.03);
  GJMChel->GetYaxis()->SetTitleOffset(1.3);
  GJMChel->GetXaxis()->SetLabelSize(0.03);
  GJMChel->SetFillColor(kAzure+7);
  GJMChel->SetFillStyle(3002);
  GJMChel->SetLineColor(kAzure+7);
  TH1D * GJMCphotonPt = new TH1D("GJMCphotonPt","GJMC dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  TH1D * GJMCgluonPt = new TH1D("GJMCgluonPt","GJMC dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);

  TH1D * GJ2040deltaR = new TH1D("GJ2040deltaR","GJ2040 deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJ2040mass = new TH1D("GJ2040mass","GJ2040 dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJ2040pull = new TH1D("GJ2040pull","GJ2040 dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJ2040hel = new TH1D("GJ2040hel","GJ2040 dijet hel",bin_hel, min_hel, max_hel);
  TH1D * GJ2040photonPt = new TH1D("GJ2040photonPt","GJ2040 dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  TH1D * GJ2040gluonPt = new TH1D("GJ2040gluonPt","GJ2040 dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);

  TH1D * GJ40100deltaR = new TH1D("GJ40100deltaR","GJ40100 deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJ40100mass = new TH1D("GJ40100mass","GJ40100 dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJ40100pull = new TH1D("GJ40100pull","GJ40100 dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJ40100hel = new TH1D("GJ40100hel","GJ40100 dijet hel",bin_hel, min_hel, max_hel);
  TH1D * GJ40100photonPt = new TH1D("GJ40100photonPt","GJ40100 dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  TH1D * GJ40100gluonPt = new TH1D("GJ40100gluonPt","GJ40100 dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);

  TH1D * GJ100200deltaR = new TH1D("GJ100200deltaR","GJ100200 deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJ100200mass = new TH1D("GJ100200mass","GJ100200 dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJ100200pull = new TH1D("GJ100200pull","GJ100200 dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJ100200hel = new TH1D("GJ100200hel","GJ100200 dijet hel",bin_hel, min_hel, max_hel);
  TH1D * GJ100200photonPt = new TH1D("GJ100200photonPt","GJ100200 dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  TH1D * GJ100200gluonPt = new TH1D("GJ100200gluonPt","GJ100200 dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);

  TH1D * GJ200infdeltaR = new TH1D("GJ200infdeltaR","GJ200inf deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJ200infmass = new TH1D("GJ200infmass","GJ200inf dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJ200infpull = new TH1D("GJ200infpull","GJ200inf dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJ200infhel = new TH1D("GJ200infhel","GJ200inf dijet hel",bin_hel, min_hel, max_hel);
  TH1D * GJ200infphotonPt = new TH1D("GJ200infphotonPt","GJ200inf dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  TH1D * GJ200infgluonPt = new TH1D("GJ200infgluonPt","GJ200inf dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);

  THStack *hCand = new THStack("hCand","gluon candidate");
  THStack *hHel = new THStack("hHel","Helicity");
  THStack *hPull = new THStack("hPull","Pull angle");

  TH2D * VHhel_ptA = new TH2D("VHhel_ptA","VH hel vs ptAs",bin_hel, min_hel, max_hel, bin_hel, min_hel, max_hel);
  TH2D * VJhel_ptA = new TH2D("VJhel_ptA","VJ hel vs ptAs",bin_hel, min_hel, max_hel, bin_hel, min_hel, max_hel);

  GammaJet GJdata("../GammaJet_3/GammaJetHLT.root");

  entries  = GJdata.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    GJdata.GetEntry(i);

//     GJdatazHel->Fill(GJdata.Zhelicity);

    if( GJdata.nOfak5 > nOfak5Cut 
	or GJdata.gluonCandidate_pt < gluonCandidatePtCut 
	or GJdata.photonCandidate_pt < photonCandidatePtCut 
	or std::min(GJdata.leadingBTag, GJdata.secondLeadingBTag) < secondLeadingBTagCut 
	or std::max(GJdata.leadingBTag, GJdata.secondLeadingBTag) < leadingBTagCut 
	or TMath::Abs(GJdata.leadingDeltaTheta) > leadingPullCut )
      continue;

    GJdatadeltaR->Fill(GJdata.jetDeltaR);
    GJdatamass->Fill(GJdata.gluonCandidate_mass);
    GJdataphotonPt->Fill(GJdata.photonCandidate_pt);
    GJdatagluonPt->Fill(GJdata.gluonCandidate_pt);
    if( GJdata.gluonCandidate_mass > gluonCandidateMassCut
	and GJdata.gluonCandidate_mass < gluonCandidateMassCut2 ){
      GJdatapull->Fill(TMath::Abs(GJdata.leadingDeltaTheta));
      GJdatahel->Fill(TMath::Abs(GJdata.leading_gluonHelicity));
      //      GJdata->Fill(TMath::Abs(GJdata.leading_gluonHelicity));
    //     GJdatahel_ptA->Fill( GJdata.leading_gluonHelicity, GJdata.jetPtAsymmetry);
    }
  }

//   //mass
  c1->cd();
  GJdatamass->Sumw2();
  GJdatamass->SetTitle("Data 2010");
  GJdatamass->GetXaxis()->SetTitle("M(j_{1},j_{2})");
  GJdatamass->GetYaxis()->SetLabelSize(0.03);
  GJdatamass->GetXaxis()->SetLabelSize(0.03);
  GJdatamass->SetFillColor(kGreen+2);
  GJdatamass->SetFillStyle(3002);
  GJdatamass->Scale(Integrated_luminosity/GJdata_normalisation);
  //  GJdatamass->Draw("ep");
//   hCand->Add(GJdatamass);

  //deltaR
  c2->cd();
  GJdatadeltaR->Sumw2();
  GJdatadeltaR->SetTitle("Data 2010");
  GJdatadeltaR->GetXaxis()->SetTitle("#DeltaR(j_{1},j_{2})");
  GJdatadeltaR->GetYaxis()->SetLabelSize(0.03);
  GJdatadeltaR->GetXaxis()->SetLabelSize(0.03);
  GJdatadeltaR->SetFillColor(kGreen+2);
  GJdatadeltaR->SetFillStyle(3002);
  GJdatadeltaR->Scale(Integrated_luminosity/GJdata_normalisation);
  GJdatadeltaR->Draw("ep");
  //  hDeltaR->Add(GJdatadeltaR);

//   //pull
  c3->cd();
  GJdatapull->Sumw2();
  GJdatapull->SetTitle("Data 2010");
  GJdatapull->GetXaxis()->SetTitle("#Delta#theta_{t}");
  GJdatapull->GetYaxis()->SetTitle("Normalized entries");
  GJdatapull->GetYaxis()->SetLabelSize(0.03);
  GJdatapull->GetXaxis()->SetLabelSize(0.03);
  GJdatapull->SetLineWidth(2);
  //  GJdatapull->SetFillColor(kGreen+2);
  //  GJdatapull->SetFillStyle(3002);
  GJdatapull->SetMarkerStyle(21);
  GJdatapull->SetMarkerSize(0.8);
  //  GJdatapull->DrawNormalized("same");
  GJdatapull->Scale(Integrated_luminosity/GJdata_normalisation);
  //  GJdatapull->Draw("ep");
  //  hPull->Add(GJdatapull);

  c4->cd();
//   //hel
  GJdatahel->Sumw2();
  GJdatahel->SetTitle("Data 2010");
  GJdatahel->GetXaxis()->SetTitle("cos#theta*");
  GJdatahel->GetYaxis()->SetLabelSize(0.03);
  GJdatahel->GetXaxis()->SetLabelSize(0.03);
  //  GJdatahel->SetFillColor(kGreen+2);
  //  GJdatahel->SetFillStyle(3002);
  GJdatahel->SetLineWidth(2);
  GJdatahel->SetMarkerStyle(21);
  GJdatahel->SetMarkerSize(0.8);
  GJdatahel->Scale(Integrated_luminosity/GJdata_normalisation);
  GJdatahel->DrawNormalized("ep");
  //  hHel->Add(GJdatahel);


 GammaJet GJ2040("./GammaJets20_40/GammaJets20-40.root");

  entries  = GJ2040.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    GJ2040.GetEntry(i);

//     GJ2040zHel->Fill(GJ2040.Zhelicity);

    if( GJ2040.nOfak5 > nOfak5Cut 
	or GJ2040.gluonCandidate_pt < gluonCandidatePtCut 
	or GJ2040.photonCandidate_pt < photonCandidatePtCut 
	or std::min(GJ2040.leadingBTag, GJ2040.secondLeadingBTag) < secondLeadingBTagCut 
	or std::max(GJ2040.leadingBTag, GJ2040.secondLeadingBTag) < leadingBTagCut 
	or TMath::Abs(GJ2040.leadingDeltaTheta) > leadingPullCut )
      continue;

    GJ2040deltaR->Fill(GJ2040.jetDeltaR);
    GJ2040mass->Fill(GJ2040.gluonCandidate_mass);
    GJ2040photonPt->Fill(GJ2040.photonCandidate_pt);
    GJ2040gluonPt->Fill(GJ2040.gluonCandidate_pt);

    if( GJ2040.gluonCandidate_mass > gluonCandidateMassCut 
	and GJ2040.gluonCandidate_mass < gluonCandidateMassCut2 ){
      GJ2040pull->Fill(TMath::Abs(GJ2040.leadingDeltaTheta));
      GJ2040hel->Fill(TMath::Abs(GJ2040.leading_gluonHelicity));
//     GJ2040hel_ptA->Fill( GJ2040.leading_gluonHelicity, GJ2040.jetPtAsymmetry);
    }
  }

  GJ2040photonPt->Scale(Integrated_luminosity/GJ2040_normalisation);
  GJMCphotonPt->Add(GJ2040photonPt);
  GJ2040gluonPt->Scale(Integrated_luminosity/GJ2040_normalisation);
  GJMCgluonPt->Add(GJ2040gluonPt);

//   //mass
  c1->cd();
  GJ2040mass->SetTitle("Jet mass data");

  GJ2040mass->GetXaxis()->SetTitle("mass");
  GJ2040mass->GetYaxis()->SetLabelSize(0.03);
  GJ2040mass->GetXaxis()->SetLabelSize(0.03);
  GJ2040mass->SetFillColor(kOrange);
  GJ2040mass->SetFillStyle(3002);
  GJ2040mass->Scale(Integrated_luminosity/GJ2040_normalisation);
  //  GJ2040mass->Draw();
  GJMCmass->Add(GJ2040mass);
  //  hCand->Add(GJ2040mass);

  c2->cd();
  //deltaR
  GJ2040deltaR->SetTitle("Jet deltaR data");
  GJ2040deltaR->GetXaxis()->SetTitle("deltaR");
  GJ2040deltaR->GetYaxis()->SetLabelSize(0.03);
  GJ2040deltaR->GetXaxis()->SetLabelSize(0.03);
  GJ2040deltaR->SetFillColor(kOrange);
  GJ2040deltaR->SetFillStyle(3002);
  GJ2040deltaR->Scale(Integrated_luminosity/GJ2040_normalisation);
  //  GJ2040deltaR->Draw();
  GJMCdeltaR->Add(GJ2040deltaR);
  //  hDeltaR->Add(GJ2040deltaR);

  c3->cd();
  //pull
  //  GJ2040pull->Sumw2();;
  GJ2040pull->SetTitle("Leading jet pull ZJets");
  GJ2040pull->GetXaxis()->SetTitle("pull");
  GJ2040pull->GetYaxis()->SetLabelSize(0.03);
  GJ2040pull->GetXaxis()->SetLabelSize(0.03);
  GJ2040pull->SetFillColor(kOrange);
  GJ2040pull->SetFillStyle(3002);
  //  GJ2040pull->DrawNormalized("same");
  GJ2040pull->Scale(Integrated_luminosity/GJ2040_normalisation);
  GJMCpull->Add(GJ2040pull);

  c4->cd();
//   //hel
  GJ2040hel->SetTitle("Leading jet hel ZJets");
  GJ2040hel->GetXaxis()->SetTitle("hel");
  GJ2040hel->GetYaxis()->SetLabelSize(0.03);
  GJ2040hel->GetXaxis()->SetLabelSize(0.03);
  GJ2040hel->SetFillColor(kOrange);
  GJ2040hel->SetFillStyle(3002);
  GJ2040hel->Scale(Integrated_luminosity/GJ2040_normalisation);
  //  GJ2040hel->DrawNormalized("same");
  GJMChel->Add(GJ2040hel);



 GammaJet GJ40100("./GammaJets40_100/GammaJets40-100.root");

  entries  = GJ40100.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    GJ40100.GetEntry(i);

//     GJ40100zHel->Fill(GJ40100.Zhelicity);

    if( GJ40100.nOfak5 > nOfak5Cut 
	or GJ40100.gluonCandidate_pt < gluonCandidatePtCut 
	or GJ40100.photonCandidate_pt < photonCandidatePtCut 
	or std::min(GJ40100.leadingBTag, GJ40100.secondLeadingBTag) < secondLeadingBTagCut 
	or std::max(GJ40100.leadingBTag, GJ40100.secondLeadingBTag) < leadingBTagCut 
	or TMath::Abs(GJ40100.leadingDeltaTheta) > leadingPullCut )
      continue;

    GJ40100deltaR->Fill(GJ40100.jetDeltaR);
    GJ40100mass->Fill(GJ40100.gluonCandidate_mass);
    GJ40100photonPt->Fill(GJ40100.photonCandidate_pt);
    GJ40100gluonPt->Fill(GJ40100.gluonCandidate_pt);

    if( GJ40100.gluonCandidate_mass > gluonCandidateMassCut 
	and GJ40100.gluonCandidate_mass < gluonCandidateMassCut2 ){
      GJ40100pull->Fill(TMath::Abs(GJ40100.leadingDeltaTheta));
      GJ40100hel->Fill(TMath::Abs(GJ40100.leading_gluonHelicity));
      //     GJ40100hel_ptA->Fill( GJ40100.leading_gluonHelicity, GJ40100.jetPtAsymmetry);
    }
  }

  GJ40100photonPt->Scale(Integrated_luminosity/GJ40100_normalisation);
  GJMCphotonPt->Add(GJ40100photonPt);
  GJ40100gluonPt->Scale(Integrated_luminosity/GJ40100_normalisation);
  GJMCgluonPt->Add(GJ40100gluonPt);

//   //mass
  c1->cd();
  GJ40100mass->SetTitle("Jet mass data");

  GJ40100mass->GetXaxis()->SetTitle("mass");
  GJ40100mass->GetYaxis()->SetLabelSize(0.03);
  GJ40100mass->GetXaxis()->SetLabelSize(0.03);
  GJ40100mass->SetFillColor(kOrange);
  GJ40100mass->SetFillStyle(3002);
  GJ40100mass->Scale(Integrated_luminosity/GJ40100_normalisation);
  //  GJ40100mass->Draw();
  GJMCmass->Add(GJ40100mass);
  //  hCand->Add(GJ40100mass);

  c2->cd();
  //deltaR
  GJ40100deltaR->SetTitle("Jet deltaR data");
  GJ40100deltaR->GetXaxis()->SetTitle("deltaR");
  GJ40100deltaR->GetYaxis()->SetLabelSize(0.03);
  GJ40100deltaR->GetXaxis()->SetLabelSize(0.03);
  GJ40100deltaR->SetFillColor(kOrange);
  GJ40100deltaR->SetFillStyle(3002);
  GJ40100deltaR->Scale(Integrated_luminosity/GJ40100_normalisation);
  //  GJ40100deltaR->Draw();
  GJMCdeltaR->Add(GJ40100deltaR);
  //  hDeltaR->Add(GJ40100deltaR);

  c3->cd();
  //pull
  //  GJ40100pull->Sumw2();;
  GJ40100pull->SetTitle("Leading jet pull ZJets");
  GJ40100pull->GetXaxis()->SetTitle("pull");
  GJ40100pull->GetYaxis()->SetLabelSize(0.03);
  GJ40100pull->GetXaxis()->SetLabelSize(0.03);
  GJ40100pull->SetFillColor(kOrange);
  GJ40100pull->SetFillStyle(3002);
  //  GJ40100pull->DrawNormalized("same");
  GJ40100pull->Scale(Integrated_luminosity/GJ40100_normalisation);
  GJMCpull->Add(GJ40100pull);

  c4->cd();
//   //hel
  GJ40100hel->SetTitle("Leading jet hel ZJets");
  GJ40100hel->GetXaxis()->SetTitle("hel");
  GJ40100hel->GetYaxis()->SetLabelSize(0.03);
  GJ40100hel->GetXaxis()->SetLabelSize(0.03);
  GJ40100hel->SetFillColor(kOrange);
  GJ40100hel->SetFillStyle(3002);
  GJ40100hel->Scale(Integrated_luminosity/GJ40100_normalisation);
  //  GJ40100hel->DrawNormalized("same");
  GJMChel->Add(GJ40100hel);


 GammaJet GJ100200("./GammaJets100_200/GammaJets100-200.root");

  entries  = GJ100200.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    GJ100200.GetEntry(i);

//     GJ100200zHel->Fill(GJ100200.Zhelicity);

    if( GJ100200.nOfak5 > nOfak5Cut 
	or GJ100200.gluonCandidate_pt < gluonCandidatePtCut 
	or GJ100200.photonCandidate_pt < photonCandidatePtCut 
	or GJ100200.leadingBTag < leadingBTagCut 
	or GJ100200.secondLeadingBTag < secondLeadingBTagCut
	or TMath::Abs(GJ100200.leadingDeltaTheta) > leadingPullCut )
      continue;

    GJ100200deltaR->Fill(GJ100200.jetDeltaR);
    GJ100200mass->Fill(GJ100200.gluonCandidate_mass);
    GJ100200photonPt->Fill(GJ100200.photonCandidate_pt);
    GJ100200gluonPt->Fill(GJ100200.gluonCandidate_pt);

    if( GJ100200.gluonCandidate_mass > gluonCandidateMassCut 
	and GJ100200.gluonCandidate_mass < gluonCandidateMassCut2 ){
      GJ100200pull->Fill(TMath::Abs(GJ100200.leadingDeltaTheta));
      GJ100200hel->Fill(TMath::Abs(GJ100200.leading_gluonHelicity));
    //     GJ100200hel_ptA->Fill( GJ100200.leading_gluonHelicity, GJ100200.jetPtAsymmetry);
    }
  }

  GJ100200photonPt->Scale(Integrated_luminosity/GJ100200_normalisation);
  GJMCphotonPt->Add(GJ100200photonPt);
  GJ100200gluonPt->Scale(Integrated_luminosity/GJ100200_normalisation);
  GJMCgluonPt->Add(GJ100200gluonPt);

//   //mass
  c1->cd();
  GJ100200mass->SetTitle("Jet mass data");

  GJ100200mass->GetXaxis()->SetTitle("mass");
  GJ100200mass->GetYaxis()->SetLabelSize(0.03);
  GJ100200mass->GetXaxis()->SetLabelSize(0.03);
  GJ100200mass->SetFillColor(kOrange);
  GJ100200mass->SetFillStyle(3002);
  GJ100200mass->Scale(Integrated_luminosity/GJ100200_normalisation);
  //  GJ100200mass->Draw("same");
  GJMCmass->Add(GJ100200mass);
  //  hCand->Add(GJ100200mass);

  c2->cd();
  //deltaR
  GJ100200deltaR->SetTitle("Jet deltaR data");
  GJ100200deltaR->GetXaxis()->SetTitle("deltaR");
  GJ100200deltaR->GetYaxis()->SetLabelSize(0.03);
  GJ100200deltaR->GetXaxis()->SetLabelSize(0.03);
  GJ100200deltaR->SetFillColor(kOrange);
  GJ100200deltaR->SetFillStyle(3002);
  GJ100200deltaR->Scale(Integrated_luminosity/GJ100200_normalisation);
  //  GJ100200deltaR->Draw("same");
  GJMCdeltaR->Add(GJ100200deltaR);
  //  hDeltaR->Add(GJ100200deltaR);

  c3->cd();
  //pull
  //  GJ100200pull->Sumw2();
  GJ100200pull->SetTitle("Leading jet pull ZJets");
  GJ100200pull->GetXaxis()->SetTitle("pull");
  GJ100200pull->GetYaxis()->SetLabelSize(0.03);
  GJ100200pull->GetXaxis()->SetLabelSize(0.03);
  GJ100200pull->SetFillColor(kOrange);
  GJ100200pull->SetFillStyle(3002);
  //  GJ100200pull->DrawNormalized("same");
  GJ100200pull->Scale(Integrated_luminosity/GJ100200_normalisation);
  GJMCpull->Add(GJ100200pull);

  //hel
  GJ100200hel->SetTitle("Leading jet hel ZJets");
  GJ100200hel->GetXaxis()->SetTitle("hel");
  GJ100200hel->GetYaxis()->SetLabelSize(0.03);
  GJ100200hel->GetXaxis()->SetLabelSize(0.03);
  GJ100200hel->SetFillColor(kOrange);
  GJ100200hel->SetFillStyle(3002);
  GJ100200hel->Scale(Integrated_luminosity/GJ100200_normalisation);
  //  GJ100200hel->DrawNormalized("same");
  GJMChel->Add(GJ100200hel);

 GammaJet GJ200inf("./GammaJets200_inf/GammaJets200-inf.root");

  entries  = GJ200inf.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    GJ200inf.GetEntry(i);

//     GJ200infzHel->Fill(GJ200inf.Zhelicity);

    if( GJ200inf.nOfak5 > nOfak5Cut 
	or GJ200inf.gluonCandidate_pt < gluonCandidatePtCut 
	or GJ200inf.photonCandidate_pt < photonCandidatePtCut 
	or GJ200inf.leadingBTag < leadingBTagCut 
	or GJ200inf.secondLeadingBTag < secondLeadingBTagCut
	or TMath::Abs(GJ200inf.leadingDeltaTheta) > leadingPullCut )
      continue;

    GJ200infdeltaR->Fill(GJ200inf.jetDeltaR);
    GJ200infmass->Fill(GJ200inf.gluonCandidate_mass);
    GJ200infphotonPt->Fill(GJ200inf.photonCandidate_pt);
    GJ200infgluonPt->Fill(GJ200inf.gluonCandidate_pt);

    if( GJ200inf.gluonCandidate_mass > gluonCandidateMassCut 
	and GJ200inf.gluonCandidate_mass < gluonCandidateMassCut2 ){
      GJ200infpull->Fill(TMath::Abs(GJ200inf.leadingDeltaTheta));
      GJ200infhel->Fill(TMath::Abs(GJ200inf.leading_gluonHelicity));
//     GJ200infhel_ptA->Fill( GJ200inf.leading_gluonHelicity, GJ200inf.jetPtAsymmetry);
    }
  }

  GJ200infphotonPt->Scale(Integrated_luminosity/GJ200inf_normalisation);
  GJMCphotonPt->Add(GJ200infphotonPt);
  GJ200infgluonPt->Scale(Integrated_luminosity/GJ200inf_normalisation);
  GJMCgluonPt->Add(GJ200infgluonPt);

//   //mass
  c1->cd();
  GJ200infmass->SetTitle("Jet mass data");
  GJ200infmass->GetXaxis()->SetTitle("mass");
  GJ200infmass->GetYaxis()->SetLabelSize(0.03);
  GJ200infmass->GetXaxis()->SetLabelSize(0.03);
  GJ200infmass->SetFillColor(kOrange);
  GJ200infmass->SetFillStyle(3002);
  GJ200infmass->Scale(Integrated_luminosity/GJ200inf_normalisation);
  //  GJ200infmass->Draw("same");
  GJMCmass->Add(GJ200infmass);
  //  hCand->Add(GJ200infmass);

  c2->cd();
  //deltaR
  GJ200infdeltaR->SetTitle("Jet deltaR data");
  GJ200infdeltaR->GetXaxis()->SetTitle("deltaR");
  GJ200infdeltaR->GetYaxis()->SetLabelSize(0.03);
  GJ200infdeltaR->GetXaxis()->SetLabelSize(0.03);
  GJ200infdeltaR->SetFillColor(kOrange);
  GJ200infdeltaR->SetFillStyle(3002);
  GJ200infdeltaR->Scale(Integrated_luminosity/GJ200inf_normalisation);
  //  GJ200infdeltaR->Draw("same");
  GJMCdeltaR->Add(GJ200infdeltaR);
  //  hDeltaR->Add(GJ200infdeltaR);

  c3->cd();
//   //pull
//  GJ200infpull->Sumw2();
  GJ200infpull->SetTitle("Leading jet pull ZJets");
  GJ200infpull->GetXaxis()->SetTitle("pull");
  GJ200infpull->GetYaxis()->SetLabelSize(0.03);
  GJ200infpull->GetXaxis()->SetLabelSize(0.03);
  GJ200infpull->SetFillColor(kOrange);
  GJ200infpull->SetFillStyle(3002);
  //  GJ200infpull->DrawNormalized("same");
  GJ200infpull->Scale(Integrated_luminosity/GJ200inf_normalisation);
  GJ200infpull->Add(GJ200infpull);

  //hel
  GJ200infhel->SetTitle("Leading jet hel ZJets");
  GJ200infhel->GetXaxis()->SetTitle("hel");
  GJ200infhel->GetYaxis()->SetLabelSize(0.03);
  GJ200infhel->GetXaxis()->SetLabelSize(0.03);
  GJ200infhel->SetFillColor(kOrange);
  GJ200infhel->SetFillStyle(3002);
  GJ200infhel->Scale(Integrated_luminosity/GJ200inf_normalisation);
  //  GJ200infhel->DrawNormalized("same");
  GJMChel->Add(GJ200infhel);



  c1->cd();
//   GJdatamass->DrawNormalized("ep");
//   GJMCmass->DrawNormalized("same");
  GJdatamass->Draw("ep");
  GJMCmass->Draw("same");
  c2->cd();
  GJdatadeltaR->DrawNormalized("ep");
  GJMCdeltaR->DrawNormalized("same");
  c3->cd();
  GJMCpull->DrawNormalized();
  GJdatapull->DrawNormalized("same ep");
  TLegend* PullLegend = new TLegend( 0.55, 0.65, 0.88, 0.88 );
  PullLegend->AddEntry(GJdatapull,"Data 2010 18.3 pb^{-1}");
  PullLegend->AddEntry(GJMCpull,"#gammaJets MadGraph4");
  PullLegend->SetFillColor(kWhite);
  PullLegend->SetBorderSize(0);
  PullLegend->Draw("same");

  c4->cd();
  GJMChel->DrawNormalized();
  GJdatahel->DrawNormalized("same ep");
  TLegend* HelLegend = new TLegend( 0.55, 0.65, 0.88, 0.88 );
  HelLegend->AddEntry(GJdatapull,"Data 2010 18.3 pb^{-1}");
  HelLegend->AddEntry(GJMCpull,"#gammaJets MadGraph4");
  HelLegend->SetFillColor(kWhite);
  HelLegend->SetBorderSize(0);
  HelLegend->Draw("same");
  c5->cd();
  GJdataphotonPt->DrawNormalized("ep");
  GJMCphotonPt->DrawNormalized("same");
  c6->cd();
  GJdatagluonPt->DrawNormalized("ep");
  GJMCgluonPt->DrawNormalized("same");


//   c1->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   hCand->Draw();
//   hCand->GetXaxis()->SetTitle("M_{jj}");
//   hCand->GetXaxis()->SetLabelSize(0.03);
//   TLegend* CandLegend = new TLegend( 0.55, 0.65, 0.88, 0.88 );
//   CandLegend->AddEntry(VHmass,"VH mass");
//   CandLegend->AddEntry(VVmass,"VV mass");
//   CandLegend->AddEntry(TTbarMass,"TTbar mass");
//   CandLegend->AddEntry(VJmass,"VJ mass");
//   CandLegend->SetFillColor(kRed);
//   CandLegend->SetFillStyle(3002);
//   CandLegend->Draw("same");

//   c2->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   hPull->Draw();
//   hPull->GetXaxis()->SetTitle("#Delta#theta_{t}");
//   hPull->GetXaxis()->SetLabelSize(0.03);
//   TLegend* PullLegend = new TLegend( 0.55, 0.65, 0.88, 0.88 );
//   PullLegend->AddEntry(VHpull,"VH pull");
//   PullLegend->AddEntry(VVpull,"VV pull");
//   PullLegend->AddEntry(TTbarPull,"TTbar pull");
//   PullLegend->AddEntry(VJpull,"VJ pull");
//   PullLegend->SetFillColor(kRed);
//   PullLegend->SetFillStyle(3002);
//   PullLegend->Draw("same");

//   c3->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   hHel->Draw();
//   hHel->GetXaxis()->SetTitle("cos#theta^{*}");
//   hHel->GetXaxis()->SetLabelSize(0.03);
//   TLegend* HelLegend = new TLegend( 0.15, 0.65, 0.48, 0.88 );
//   HelLegend->AddEntry(VHhel,"VH hel");
//   HelLegend->AddEntry(VVhel,"VV hel");
//   HelLegend->AddEntry(TTbarHel,"TTbar hel");
//   HelLegend->AddEntry(VJhel,"VJ hel");
//   HelLegend->SetFillColor(kRed);
//   HelLegend->SetFillStyle(3002);
//   HelLegend->Draw("same");

//   c4->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
// //   VHzHel->DrawNormalized();
// //   VJzHel->DrawNormalized("same");
//   VHhel->DrawNormalized();
//   VJhel->DrawNormalized("same");
// //   VVhel->DrawNormalized("same");

//   c5->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   VHpull->DrawNormalized();
//   VJpull->DrawNormalized("same");
// //   VVpull->DrawNormalized("same");

//   c6->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   VJhel_ptA->DrawNormalized("COLZ");

//   c7->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   VHhel_ptA->DrawNormalized("COLZ");


//   VH_counter *= (Integrated_luminosity/VH_normalisation);
//   VV_counter *= (Integrated_luminosity/VV_normalisation);
//   TTbar_counter *= (Integrated_luminosity/TTbar_normalisation);
//   VJ_counter *= (Integrated_luminosity/VJ_normalisation);

//   std::cout << "VH = " << VH_counter << std::endl;
//   std::cout << "VV = " << VV_counter << std::endl;
//   std::cout << "VJ = " << VJ_counter << std::endl;
//   std::cout << "TTbar = " << TTbar_counter << std::endl;
//   std::cout << "Significance = " << VH_counter/TMath::Sqrt(VV_counter+TTbar_counter+VJ_counter) << std::endl;
//   std::cout << "S/B = " << VH_counter/(VV_counter+TTbar_counter+VJ_counter) << std::endl;

  return 0;

}
