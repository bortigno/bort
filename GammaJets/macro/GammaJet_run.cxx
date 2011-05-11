// This is to see the results of the GammaJet
// May 2011
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
  TCanvas * c3b = new TCanvas("c3b","c3b",600,600);
  TCanvas * c4 = new TCanvas("c4","c4",600,600);
  TCanvas * c5 = new TCanvas("c5","c5",600,600);
  TCanvas * c6 = new TCanvas("c6","c6",600,600);
  TCanvas * c7 = new TCanvas("c7","c7",600,600);

  Int_t nOfak5Cut = 222;
  Double_t photonCandidatePtCut = 90;
  Double_t gluonCandidatePtCut = 60;//photonCandidatePtCut-sqrt(photonCandidatePtCut);
  Double_t gluonCandidateMassCut = 0;
  Double_t gluonCandidateMassCut2 = 1400000;
  Double_t leadingBTagCut = -100000;
  Double_t secondLeadingBTagCut = -10000;
  Double_t leadingPullCut = 25555;
  Double_t AK7leadingPullCut = 25555;

  Long64_t entries = 0;

  Double_t Integrated_luminosity = 116.147;
  Double_t GJdata_normalisation = 116.147; 
//   Double_t Integrated_luminosity = 126.28;
//   Double_t GJdata_normalisation = 126.28; 
  Double_t GJdata10_normalisation = 18.3; 
  Double_t GJ40100_normalisation = 84.67;
  Double_t GJ100200_normalisation = 287.69;
  Double_t GJ200inf_normalisation = 2026.7;
  Double_t GZ_normalisation = 1894.0;

  Int_t bin_mass = 20;
  Double_t min_mass = 0;
  Double_t max_mass = 400;

  Int_t bin_pull = 6;
  Double_t min_pull = 0;
  Double_t max_pull = 3.14;

  Int_t bin_hel = 5;
  Double_t min_hel = 0;
  Double_t max_hel = 1;

  Int_t bin_deltaR = 10;
  Double_t min_deltaR = 0;
  Double_t max_deltaR = 5;

  Int_t bin_nOfak5 = 10;
  Double_t min_nOfak5 = 0;
  Double_t max_nOfak5 = 10;

  Int_t bin_photonPt = 30;
  Double_t min_photonPt = 0;
  Double_t max_photonPt = 300;

  Int_t bin_gluonPt = 30;
  Double_t min_gluonPt = 0;
  Double_t max_gluonPt = 300;

  TH1D * GJdatanOfak5 = new TH1D("GJdatanOfak5","GJdata nOfak5",bin_nOfak5, min_nOfak5, max_nOfak5);
  GJdatanOfak5->Sumw2();
  TH1D * GJdatadeltaR = new TH1D("GJdatadeltaR","GJdata deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJdatamass = new TH1D("GJdatamass","GJdata dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJdatapull = new TH1D("GJdatapull","GJdata dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJdataAK7pull = new TH1D("GJdataAK7pull","GJdata dijet AK7pull",bin_pull, min_pull, max_pull);
  TH1D * GJdatahel = new TH1D("GJdatahel","GJdata dijet hel",bin_hel, min_hel, max_hel);
  TH1D * GJdataphotonPt = new TH1D("GJdataphotonPt","GJdata dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  GJdataphotonPt->Sumw2();
  TH1D * GJdatagluonPt = new TH1D("GJdatagluonPt","GJdata dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);
  GJdatagluonPt->Sumw2();

  TH1D * GJdata10nOfak5 = new TH1D("GJdata10nOfak5","GJdata10 nOfak5",bin_nOfak5, min_nOfak5, max_nOfak5);
  GJdata10nOfak5->Sumw2();
  TH1D * GJdata10deltaR = new TH1D("GJdata10deltaR","GJdata10 deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJdata10mass = new TH1D("GJdata10mass","GJdata10 dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJdata10pull = new TH1D("GJdata10pull","GJdata10 dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJdata10AK7pull = new TH1D("GJdata10AK7pull","GJdata10 dijet AK7pull",bin_pull, min_pull, max_pull);
  TH1D * GJdata10hel = new TH1D("GJdata10hel","GJdata10 dijet hel",bin_hel, min_hel, max_hel);
  TH1D * GJdata10photonPt = new TH1D("GJdata10photonPt","GJdata10 dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  GJdata10photonPt->Sumw2();
  TH1D * GJdata10gluonPt = new TH1D("GJdata10gluonPt","GJdata10 dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);
  GJdata10gluonPt->Sumw2();

  TH1D * GJMCnOfak5 = new TH1D("GJMCnOfak5","GJMC nOfak5",bin_nOfak5, min_nOfak5, max_nOfak5);
  TH1D * GJMCdeltaR = new TH1D("GJMCdeltaR","GJMC deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJMCmass = new TH1D("GJMCmass","GJMC dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJMCpull = new TH1D("GJMCpull","GJMC dijet pull",bin_pull, min_pull, max_pull);
  GJMCpull->GetXaxis()->SetTitle("|#Delta#theta_{t}|_{AK5}");
  GJMCpull->GetYaxis()->SetTitle("Normalized entries");
  GJMCpull->GetYaxis()->SetLabelSize(0.03);
  GJMCpull->GetYaxis()->SetTitleOffset(1.3);
  GJMCpull->GetXaxis()->SetLabelSize(0.03);
  GJMCpull->SetFillColor(kAzure+7);
  GJMCpull->SetFillStyle(3002);
  GJMCpull->SetLineColor(kAzure+7);
  TH1D * GJMCAK7pull = new TH1D("GJMCAK7pull","GJMC dijet AK7pull",bin_pull, min_pull, max_pull);
  GJMCAK7pull->GetXaxis()->SetTitle("|#Delta#theta_{t}|_{AK7}");
  GJMCAK7pull->GetYaxis()->SetTitle("Normalized entries");
  GJMCAK7pull->GetYaxis()->SetLabelSize(0.03);
  GJMCAK7pull->GetYaxis()->SetTitleOffset(1.3);
  GJMCAK7pull->GetXaxis()->SetLabelSize(0.03);
  GJMCAK7pull->SetFillColor(kAzure+7);
  GJMCAK7pull->SetFillStyle(3002);
  GJMCAK7pull->SetLineColor(kAzure+7);
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

  TH1D * GJ40100nOfak5 = new TH1D("GJ40100nOfak5","GJ40100 nOfak5",bin_nOfak5, min_nOfak5, max_nOfak5);
  TH1D * GJ40100deltaR = new TH1D("GJ40100deltaR","GJ40100 deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJ40100mass = new TH1D("GJ40100mass","GJ40100 dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJ40100pull = new TH1D("GJ40100pull","GJ40100 dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJ40100AK7pull = new TH1D("GJ40100AK7pull","GJ40100 dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJ40100hel = new TH1D("GJ40100hel","GJ40100 dijet hel",bin_hel, min_hel, max_hel);
  TH1D * GJ40100photonPt = new TH1D("GJ40100photonPt","GJ40100 dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  TH1D * GJ40100gluonPt = new TH1D("GJ40100gluonPt","GJ40100 dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);

  TH1D * GJ100200nOfak5 = new TH1D("GJ100200nOfak5","GJ100200 nOfak5",bin_nOfak5, min_nOfak5, max_nOfak5);
  TH1D * GJ100200deltaR = new TH1D("GJ100200deltaR","GJ100200 deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJ100200mass = new TH1D("GJ100200mass","GJ100200 dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJ100200pull = new TH1D("GJ100200pull","GJ100200 dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJ100200AK7pull = new TH1D("GJ100200AK7pull","GJ100200 dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJ100200hel = new TH1D("GJ100200hel","GJ100200 dijet hel",bin_hel, min_hel, max_hel);
  TH1D * GJ100200photonPt = new TH1D("GJ100200photonPt","GJ100200 dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  TH1D * GJ100200gluonPt = new TH1D("GJ100200gluonPt","GJ100200 dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);

  TH1D * GJ200infnOfak5 = new TH1D("GJ200infnOfak5","GJ200inf nOfak5",bin_nOfak5, min_nOfak5, max_nOfak5);
  TH1D * GJ200infdeltaR = new TH1D("GJ200infdeltaR","GJ200inf deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GJ200infmass = new TH1D("GJ200infmass","GJ200inf dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GJ200infpull = new TH1D("GJ200infpull","GJ200inf dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJ200infAK7pull = new TH1D("GJ200infAK7pull","GJ200inf dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GJ200infhel = new TH1D("GJ200infhel","GJ200inf dijet hel",bin_hel, min_hel, max_hel);
  TH1D * GJ200infphotonPt = new TH1D("GJ200infphotonPt","GJ200inf dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  TH1D * GJ200infgluonPt = new TH1D("GJ200infgluonPt","GJ200inf dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);

  TH1D * GZnOfak5 = new TH1D("GZnOfak5","GZ nOfak5",bin_nOfak5, min_nOfak5, max_nOfak5);
  TH1D * GZdeltaR = new TH1D("GZdeltaR","GZ deltaR",bin_deltaR, min_deltaR, max_deltaR);
  TH1D * GZmass = new TH1D("GZmass","GZ dijet mass",bin_mass, min_mass, max_mass);
  TH1D * GZpull = new TH1D("GZpull","GZ dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GZAK7pull = new TH1D("GZAK7pull","GZ dijet pull",bin_pull, min_pull, max_pull);
  TH1D * GZhel = new TH1D("GZhel","GZ dijet hel",bin_hel, min_hel, max_hel);
  TH1D * GZphotonPt = new TH1D("GZphotonPt","GZ dijet photonPt",bin_photonPt, min_photonPt, max_photonPt);
  TH1D * GZgluonPt = new TH1D("GZgluonPt","GZ dijet gluonPt",bin_gluonPt, min_gluonPt, max_gluonPt);

  THStack *hCand = new THStack("hCand","gluon candidate");
//   hCand->GetXaxis()->SetTitle("M(j_{1},j_{2})");
//   hCand->GetYaxis()->SetLabelSize(0.03);
//   hCand->GetXaxis()->SetLabelSize(0.03);

  THStack *hHel = new THStack("hHel","Helicity");
  THStack *hPull = new THStack("hPull","Pull angle");

  TH2D * VHhel_ptA = new TH2D("VHhel_ptA","VH hel vs ptAs",bin_hel, min_hel, max_hel, bin_hel, min_hel, max_hel);
  TH2D * VJhel_ptA = new TH2D("VJhel_ptA","VJ hel vs ptAs",bin_hel, min_hel, max_hel, bin_hel, min_hel, max_hel);

  //  GammaJet GJdata("../GammaJet_data_v1/GammaJetHLT_data_v1.root");
  GammaJet GJdata("../GammaJet_data_v2/GammaJetHLT_data_v2.root");
  //  GammaJet GJdata("/shome/bortigno/test/CMSSW_3_8_7_patch2/src/VHbb/iCode/test/GammaJet_3/GammaJetHLT.root");

  entries  = GJdata.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    GJdata.GetEntry(i);
    
    //     GJdatazHel->Fill(GJdata.Zhelicity);
    
    if( ( GJdata.nOfak5 > nOfak5Cut ) 
	or ( GJdata.gluonCandidate_pt < gluonCandidatePtCut ) 
	or ( GJdata.photonCandidate_pt < photonCandidatePtCut ) 
	or ( std::min(GJdata.leadingBTag, GJdata.secondLeadingBTag) < secondLeadingBTagCut )
	or ( std::max(GJdata.leadingBTag, GJdata.secondLeadingBTag) < leadingBTagCut )
	or ( TMath::Abs(GJdata.leadingDeltaTheta) > leadingPullCut ) 
	or ( TMath::Abs(GJdata.AK7leadingDeltaTheta) > AK7leadingPullCut ) )
      continue;


    GJdatanOfak5->Fill(GJdata.nOfak5);
    GJdatadeltaR->Fill(GJdata.jetDeltaR);
    GJdatamass->Fill(GJdata.gluonCandidate_mass);
    GJdataphotonPt->Fill(GJdata.photonCandidate_pt);
    GJdatagluonPt->Fill(GJdata.gluonCandidate_pt);
    if( ( GJdata.gluonCandidate_mass > gluonCandidateMassCut )
	and ( GJdata.gluonCandidate_mass < gluonCandidateMassCut2 ) ){
      GJdatapull->Fill(TMath::Abs(GJdata.leadingDeltaTheta));
      GJdataAK7pull->Fill(TMath::Abs(GJdata.AK7leadingDeltaTheta));
      GJdatahel->Fill(TMath::Abs(GJdata.leading_gluonHelicity));
      //      GJdata->Fill(TMath::Abs(GJdata.leading_gluonHelicity));
    //     GJdatahel_ptA->Fill( GJdata.leading_gluonHelicity, GJdata.jetPtAsymmetry);
    }
  }

//   //mass
  c1->cd();
  GJdatamass->Sumw2();
  GJdatamass->SetTitle("Data 2011");
  GJdatamass->GetXaxis()->SetTitle("M(j_{1},j_{2})");
  GJdatamass->GetYaxis()->SetLabelSize(0.03);
  GJdatamass->GetXaxis()->SetLabelSize(0.03);
  GJdatamass->SetLineWidth(2);
  //  GJdatamass->SetFillColor(kGreen+2);
  //  GJdatamass->SetFillStyle(3002);
  GJdatamass->SetMarkerStyle(21);
  GJdatamass->SetMarkerSize(0.8);
  GJdatamass->Scale(Integrated_luminosity/GJdata_normalisation);
  //  GJdatamass->Draw("ep");
  //  hCand->Add(GJdatamass);

  //deltaR
  c2->cd();
  GJdatadeltaR->Sumw2();
  GJdatadeltaR->SetTitle("Data 2011");
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
  GJdatapull->SetTitle("Data 2011");
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

//   //pull
  c3b->cd();
  GJdataAK7pull->Sumw2();
  GJdataAK7pull->SetTitle("Data 2011");
  GJdataAK7pull->GetXaxis()->SetTitle("#Delta#theta_{t}");
  GJdataAK7pull->GetYaxis()->SetTitle("Normalized entries");
  GJdataAK7pull->GetYaxis()->SetLabelSize(0.03);
  GJdataAK7pull->GetXaxis()->SetLabelSize(0.03);
  GJdataAK7pull->SetLineWidth(2);
  //  GJdataAK7pull->SetFillColor(kGreen+2);
  //  GJdataAK7pull->SetFillStyle(3002);
  GJdataAK7pull->SetMarkerStyle(21);
  GJdataAK7pull->SetMarkerSize(0.8);
  //  GJdataAK7pull->DrawNormalized("same");
  GJdataAK7pull->Scale(Integrated_luminosity/GJdata_normalisation);
  //  GJdataAK7pull->Draw("ep");
  //  hAK7pull->Add(GJdataAK7pull);


  c4->cd();
//   //hel
  GJdatahel->Sumw2();
  GJdatahel->SetTitle("Data 2011");
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


  //  GammaJet GJdata10("../GammaJet_data10_v1/GammaJetHLT_data10_v1.root");
  GammaJet GJdata10("/shome/bortigno/test/CMSSW_3_8_7_patch2/src/VHbb/iCode/test/GammaJet_3/GammaJetHLT.root");
  //  GammaJet GJdata10("/shome/bortigno/test/CMSSW_3_8_7_patch2/src/VHbb/iCode/test/GammaJet_3/GammaJetHLT.root");

  entries  = GJdata10.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    GJdata10.GetEntry(i);
    
    //     GJdata10zHel->Fill(GJdata10.Zhelicity);
    
    if( ( GJdata10.nOfak5 > nOfak5Cut ) 
	or ( GJdata10.gluonCandidate_pt < gluonCandidatePtCut ) 
	or ( GJdata10.photonCandidate_pt < photonCandidatePtCut ) 
	or ( std::min(GJdata10.leadingBTag, GJdata10.secondLeadingBTag) < secondLeadingBTagCut )
	or ( std::max(GJdata10.leadingBTag, GJdata10.secondLeadingBTag) < leadingBTagCut )
	or ( TMath::Abs(GJdata10.leadingDeltaTheta) > leadingPullCut ) 
	or ( TMath::Abs(GJdata10.AK7leadingDeltaTheta) > AK7leadingPullCut ) )
      continue;


    GJdata10nOfak5->Fill(GJdata10.nOfak5);
    GJdata10deltaR->Fill(GJdata10.jetDeltaR);
    GJdata10mass->Fill(GJdata10.gluonCandidate_mass);
    GJdata10photonPt->Fill(GJdata10.photonCandidate_pt);
    GJdata10gluonPt->Fill(GJdata10.gluonCandidate_pt);
    if( ( GJdata10.gluonCandidate_mass > gluonCandidateMassCut )
	and ( GJdata10.gluonCandidate_mass < gluonCandidateMassCut2 ) ){
      GJdata10pull->Fill(TMath::Abs(GJdata10.leadingDeltaTheta));
      GJdata10AK7pull->Fill(TMath::Abs(GJdata10.AK7leadingDeltaTheta));
      GJdata10hel->Fill(TMath::Abs(GJdata10.leading_gluonHelicity));
      //      GJdata10->Fill(TMath::Abs(GJdata10.leading_gluonHelicity));
    //     GJdata10hel_ptA->Fill( GJdata10.leading_gluonHelicity, GJdata10.jetPtAsymmetry);
    }
  }

//   //mass
  c1->cd();
  GJdata10mass->Sumw2();
  GJdata10mass->SetTitle("Data10 2011");
  GJdata10mass->GetXaxis()->SetTitle("M(j_{1},j_{2})");
  GJdata10mass->GetYaxis()->SetLabelSize(0.03);
  GJdata10mass->GetXaxis()->SetLabelSize(0.03);
  GJdata10mass->SetLineWidth(2);
  //  GJdata10mass->SetFillColor(kGreen+2);
  //  GJdata10mass->SetFillStyle(3002);
  GJdata10mass->SetMarkerStyle(21);
  GJdata10mass->SetMarkerSize(0.8);
  GJdata10mass->Scale(Integrated_luminosity/GJdata10_normalisation);
  //  GJdata10mass->Draw("ep");
  //  hCand->Add(GJdata10mass);

  //deltaR
  c2->cd();
  GJdata10deltaR->Sumw2();
  GJdata10deltaR->SetTitle("Data10 2011");
  GJdata10deltaR->GetXaxis()->SetTitle("#DeltaR(j_{1},j_{2})");
  GJdata10deltaR->GetYaxis()->SetLabelSize(0.03);
  GJdata10deltaR->GetXaxis()->SetLabelSize(0.03);
  GJdata10deltaR->SetFillColor(kGreen+2);
  GJdata10deltaR->SetFillStyle(3002);
  GJdata10deltaR->Scale(Integrated_luminosity/GJdata10_normalisation);
  GJdata10deltaR->Draw("ep");
  //  hDeltaR->Add(GJdata10deltaR);

//   //pull
  c3->cd();
  GJdata10pull->Sumw2();
  GJdata10pull->SetTitle("Data10 2011");
  GJdata10pull->GetXaxis()->SetTitle("#Delta#theta_{t}");
  GJdata10pull->GetYaxis()->SetTitle("Normalized entries");
  GJdata10pull->GetYaxis()->SetLabelSize(0.03);
  GJdata10pull->GetXaxis()->SetLabelSize(0.03);
  GJdata10pull->SetLineWidth(2);
  //  GJdata10pull->SetFillColor(kGreen+2);
  //  GJdata10pull->SetFillStyle(3002);
  GJdata10pull->SetMarkerStyle(21);
  GJdata10pull->SetMarkerSize(0.8);
  //  GJdata10pull->DrawNormalized("same");
  GJdata10pull->Scale(Integrated_luminosity/GJdata10_normalisation);
  //  GJdata10pull->Draw("ep");
  //  hPull->Add(GJdata10pull);

//   //pull
  c3b->cd();
  GJdata10AK7pull->Sumw2();
  GJdata10AK7pull->SetTitle("Data10 2011");
  GJdata10AK7pull->GetXaxis()->SetTitle("#Delta#theta_{t}");
  GJdata10AK7pull->GetYaxis()->SetTitle("Normalized entries");
  GJdata10AK7pull->GetYaxis()->SetLabelSize(0.03);
  GJdata10AK7pull->GetXaxis()->SetLabelSize(0.03);
  GJdata10AK7pull->SetLineWidth(2);
  //  GJdata10AK7pull->SetFillColor(kGreen+2);
  //  GJdata10AK7pull->SetFillStyle(3002);
  GJdata10AK7pull->SetMarkerStyle(21);
  GJdata10AK7pull->SetMarkerSize(0.8);
  //  GJdata10AK7pull->DrawNormalized("same");
  GJdata10AK7pull->Scale(Integrated_luminosity/GJdata10_normalisation);
  //  GJdata10AK7pull->Draw("ep");
  //  hAK7pull->Add(GJdata10AK7pull);


  c4->cd();
//   //hel
  GJdata10hel->Sumw2();
  GJdata10hel->SetTitle("Data10 2011");
  GJdata10hel->GetXaxis()->SetTitle("cos#theta*");
  GJdata10hel->GetYaxis()->SetLabelSize(0.03);
  GJdata10hel->GetXaxis()->SetLabelSize(0.03);
  //  GJdata10hel->SetFillColor(kGreen+2);
  //  GJdata10hel->SetFillStyle(3002);
  GJdata10hel->SetLineWidth(2);
  GJdata10hel->SetMarkerStyle(21);
  GJdata10hel->SetMarkerSize(0.8);
  GJdata10hel->Scale(Integrated_luminosity/GJdata10_normalisation);
  GJdata10hel->DrawNormalized("ep");
  //  hHel->Add(GJdata10hel);


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
	or TMath::Abs(GJ40100.leadingDeltaTheta) > leadingPullCut 
	or TMath::Abs(GJ40100.AK7leadingDeltaTheta) > AK7leadingPullCut )
      continue;

    GJ40100nOfak5->Fill(GJ40100.nOfak5);
    GJ40100deltaR->Fill(GJ40100.jetDeltaR);
    GJ40100mass->Fill(GJ40100.gluonCandidate_mass);
    GJ40100photonPt->Fill(GJ40100.photonCandidate_pt);
    GJ40100gluonPt->Fill(GJ40100.gluonCandidate_pt);

    if( GJ40100.gluonCandidate_mass > gluonCandidateMassCut 
	and GJ40100.gluonCandidate_mass < gluonCandidateMassCut2 ){
      GJ40100pull->Fill(TMath::Abs(GJ40100.leadingDeltaTheta));
      GJ40100AK7pull->Fill(TMath::Abs(GJ40100.AK7leadingDeltaTheta));
      GJ40100hel->Fill(TMath::Abs(GJ40100.leading_gluonHelicity));
      //     GJ40100hel_ptA->Fill( GJ40100.leading_gluonHelicity, GJ40100.jetPtAsymmetry);
    }
  }

  GJ40100nOfak5->Scale(Integrated_luminosity/GJ40100_normalisation);
  GJMCnOfak5->Add(GJ40100nOfak5);
  GJ40100photonPt->Scale(Integrated_luminosity/GJ40100_normalisation);
  GJMCphotonPt->Add(GJ40100photonPt);
  GJ40100gluonPt->Scale(Integrated_luminosity/GJ40100_normalisation);
  GJMCgluonPt->Add(GJ40100gluonPt);

//   //mass
  c1->cd();
  GJ40100mass->SetTitle("#gamma jets HT 40-100");
  GJ40100mass->GetXaxis()->SetTitle("mass");
  GJ40100mass->GetYaxis()->SetLabelSize(0.03);
  GJ40100mass->GetXaxis()->SetLabelSize(0.03);
  GJ40100mass->SetFillColor(kAzure+4);
  GJ40100mass->SetFillStyle(3002);
  GJ40100mass->Scale(Integrated_luminosity/GJ40100_normalisation);
  //  GJ40100mass->Draw();
  GJMCmass->Add(GJ40100mass);
  hCand->Add(GJ40100mass);

  c2->cd();
  //deltaR
  GJ40100deltaR->SetTitle("Jet deltaR data");
  GJ40100deltaR->GetXaxis()->SetTitle("deltaR");
  GJ40100deltaR->GetYaxis()->SetLabelSize(0.03);
  GJ40100deltaR->GetXaxis()->SetLabelSize(0.03);
  GJ40100deltaR->SetFillColor(kAzure+7);
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
  GJ40100pull->SetFillColor(kAzure+7);
  GJ40100pull->SetFillStyle(3002);
  //  GJ40100pull->DrawNormalized("same");
  GJ40100pull->Scale(Integrated_luminosity/GJ40100_normalisation);
  GJMCpull->Add(GJ40100pull);


  c3b->cd();
  //AK7pull
  //  GJ40100AK7pull->Sumw2();;
  GJ40100AK7pull->SetTitle("Leading jet AK7pull ZJets");
  GJ40100AK7pull->GetXaxis()->SetTitle("AK7pull");
  GJ40100AK7pull->GetYaxis()->SetLabelSize(0.03);
  GJ40100AK7pull->GetXaxis()->SetLabelSize(0.03);
  GJ40100AK7pull->SetFillColor(kAzure+7);
  GJ40100AK7pull->SetFillStyle(3002);
  //  GJ40100AK7pull->DrawNormalized("same");
  GJ40100AK7pull->Scale(Integrated_luminosity/GJ40100_normalisation);
  GJMCAK7pull->Add(GJ40100AK7pull);

  c4->cd();
//   //hel
  GJ40100hel->SetTitle("Leading jet hel ZJets");
  GJ40100hel->GetXaxis()->SetTitle("hel");
  GJ40100hel->GetYaxis()->SetLabelSize(0.03);
  GJ40100hel->GetXaxis()->SetLabelSize(0.03);
  GJ40100hel->SetFillColor(kAzure+7);
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
	or TMath::Abs(GJ100200.leadingDeltaTheta) > leadingPullCut 
	or TMath::Abs(GJ100200.AK7leadingDeltaTheta) > AK7leadingPullCut )
      continue;

    GJ100200nOfak5->Fill(GJ100200.nOfak5);
    GJ100200deltaR->Fill(GJ100200.jetDeltaR);
    GJ100200mass->Fill(GJ100200.gluonCandidate_mass);
    GJ100200photonPt->Fill(GJ100200.photonCandidate_pt);
    GJ100200gluonPt->Fill(GJ100200.gluonCandidate_pt);

    if( GJ100200.gluonCandidate_mass > gluonCandidateMassCut 
	and GJ100200.gluonCandidate_mass < gluonCandidateMassCut2 ){
      GJ100200pull->Fill(TMath::Abs(GJ100200.leadingDeltaTheta));
      GJ100200AK7pull->Fill(TMath::Abs(GJ100200.AK7leadingDeltaTheta));
      GJ100200hel->Fill(TMath::Abs(GJ100200.leading_gluonHelicity));
    //     GJ100200hel_ptA->Fill( GJ100200.leading_gluonHelicity, GJ100200.jetPtAsymmetry);
    }
  }

  GJ100200nOfak5->Scale(Integrated_luminosity/GJ100200_normalisation);
  GJMCnOfak5->Add(GJ100200nOfak5);
  GJ100200photonPt->Scale(Integrated_luminosity/GJ100200_normalisation);
  GJMCphotonPt->Add(GJ100200photonPt);
  GJ100200gluonPt->Scale(Integrated_luminosity/GJ100200_normalisation);
  GJMCgluonPt->Add(GJ100200gluonPt);

//   //mass
  c1->cd();
  GJ100200mass->SetTitle("#gamma jets HT 100-200");
  GJ100200mass->GetXaxis()->SetTitle("mass");
  GJ100200mass->GetYaxis()->SetLabelSize(0.03);
  GJ100200mass->GetXaxis()->SetLabelSize(0.03);
  GJ100200mass->SetFillColor(kAzure+6);
  GJ100200mass->SetFillStyle(3002);
  GJ100200mass->Scale(Integrated_luminosity/GJ100200_normalisation);
  //  GJ100200mass->Draw("same");
  GJMCmass->Add(GJ100200mass);
  hCand->Add(GJ100200mass);

  c2->cd();
  //deltaR
  GJ100200deltaR->SetTitle("Jet deltaR data");
  GJ100200deltaR->GetXaxis()->SetTitle("deltaR");
  GJ100200deltaR->GetYaxis()->SetLabelSize(0.03);
  GJ100200deltaR->GetXaxis()->SetLabelSize(0.03);
  GJ100200deltaR->SetFillColor(kAzure+7);
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
  GJ100200pull->SetFillColor(kAzure+7);
  GJ100200pull->SetFillStyle(3002);
  //  GJ100200pull->DrawNormalized("same");
  GJ100200pull->Scale(Integrated_luminosity/GJ100200_normalisation);
  GJMCpull->Add(GJ100200pull);

  c3b->cd();
  //AK7pull
  //  GJ100200AK7pull->Sumw2();
  GJ100200AK7pull->SetTitle("Leading jet AK7pull ZJets");
  GJ100200AK7pull->GetXaxis()->SetTitle("AK7pull");
  GJ100200AK7pull->GetYaxis()->SetLabelSize(0.03);
  GJ100200AK7pull->GetXaxis()->SetLabelSize(0.03);
  GJ100200AK7pull->SetFillColor(kAzure+7);
  GJ100200AK7pull->SetFillStyle(3002);
  //  GJ100200AK7pull->DrawNormalized("same");
  GJ100200AK7pull->Scale(Integrated_luminosity/GJ100200_normalisation);
  GJMCAK7pull->Add(GJ100200AK7pull);

  c4->cd();
  //hel
  GJ100200hel->SetTitle("Leading jet hel ZJets");
  GJ100200hel->GetXaxis()->SetTitle("hel");
  GJ100200hel->GetYaxis()->SetLabelSize(0.03);
  GJ100200hel->GetXaxis()->SetLabelSize(0.03);
  GJ100200hel->SetFillColor(kAzure+7);
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
	or TMath::Abs(GJ200inf.leadingDeltaTheta) > leadingPullCut
	or TMath::Abs(GJ200inf.AK7leadingDeltaTheta) > AK7leadingPullCut )
      continue;

    GJ200infnOfak5->Fill(GJ200inf.nOfak5);
    GJ200infdeltaR->Fill(GJ200inf.jetDeltaR);
    GJ200infmass->Fill(GJ200inf.gluonCandidate_mass);
    GJ200infphotonPt->Fill(GJ200inf.photonCandidate_pt);
    GJ200infgluonPt->Fill(GJ200inf.gluonCandidate_pt);

    if( GJ200inf.gluonCandidate_mass > gluonCandidateMassCut 
	and GJ200inf.gluonCandidate_mass < gluonCandidateMassCut2 ){
      GJ200infpull->Fill(TMath::Abs(GJ200inf.leadingDeltaTheta));
      GJ200infAK7pull->Fill(TMath::Abs(GJ200inf.AK7leadingDeltaTheta));
      GJ200infhel->Fill(TMath::Abs(GJ200inf.leading_gluonHelicity));
//     GJ200infhel_ptA->Fill( GJ200inf.leading_gluonHelicity, GJ200inf.jetPtAsymmetry);
    }
  }

  GJ200infnOfak5->Scale(Integrated_luminosity/GJ200inf_normalisation);
  GJMCnOfak5->Add(GJ200infnOfak5);
  GJ200infphotonPt->Scale(Integrated_luminosity/GJ200inf_normalisation);
  GJMCphotonPt->Add(GJ200infphotonPt);
  GJ200infgluonPt->Scale(Integrated_luminosity/GJ200inf_normalisation);
  GJMCgluonPt->Add(GJ200infgluonPt);

//   //mass
  c1->cd();
  GJ200infmass->SetTitle("#gamma jets HT 200-#inf");
  GJ200infmass->GetXaxis()->SetTitle("mass");
  GJ200infmass->GetYaxis()->SetLabelSize(0.03);
  GJ200infmass->GetXaxis()->SetLabelSize(0.03);
  GJ200infmass->SetFillColor(kAzure+7);
  GJ200infmass->SetFillStyle(3002);
  GJ200infmass->Scale(Integrated_luminosity/GJ200inf_normalisation);
  //  GJ200infmass->Draw("same");
  GJMCmass->Add(GJ200infmass);
 hCand->Add(GJ200infmass);

  c2->cd();
  //deltaR
  GJ200infdeltaR->SetTitle("Jet deltaR data");
  GJ200infdeltaR->GetXaxis()->SetTitle("deltaR");
  GJ200infdeltaR->GetYaxis()->SetLabelSize(0.03);
  GJ200infdeltaR->GetXaxis()->SetLabelSize(0.03);
  GJ200infdeltaR->SetFillColor(kAzure+7);
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
  GJ200infpull->SetFillColor(kAzure+7);
  GJ200infpull->SetFillStyle(3002);
  //  GJ200infpull->DrawNormalized("same");
  GJ200infpull->Scale(Integrated_luminosity/GJ200inf_normalisation);
  GJ200infpull->Add(GJ200infpull);

  c3->cd();
//   //AK7pull
//  GJ200infAK7pull->Sumw2();
  GJ200infAK7pull->SetTitle("Leading jet AK7pull ZJets");
  GJ200infAK7pull->GetXaxis()->SetTitle("AK7pull");
  GJ200infAK7pull->GetYaxis()->SetLabelSize(0.03);
  GJ200infAK7pull->GetXaxis()->SetLabelSize(0.03);
  GJ200infAK7pull->SetFillColor(kAzure+7);
  GJ200infAK7pull->SetFillStyle(3002);
  //  GJ200infAK7pull->DrawNormalized("same");
  GJ200infAK7pull->Scale(Integrated_luminosity/GJ200inf_normalisation);
  GJ200infAK7pull->Add(GJ200infAK7pull);

  c4->cd();
  //hel
  GJ200infhel->SetTitle("Leading jet hel ZJets");
  GJ200infhel->GetXaxis()->SetTitle("hel");
  GJ200infhel->GetYaxis()->SetLabelSize(0.03);
  GJ200infhel->GetXaxis()->SetLabelSize(0.03);
  GJ200infhel->SetFillColor(kAzure+7);
  GJ200infhel->SetFillStyle(3002);
  GJ200infhel->Scale(Integrated_luminosity/GJ200inf_normalisation);
  //  GJ200infhel->DrawNormalized("same");
  GJMChel->Add(GJ200infhel);



 GammaJet GZ("./GammaZ/GammaZ.root");

  entries  = GZ.fChain->GetEntriesFast();
  for (unsigned int i = 0; i < entries; ++i){
    GZ.GetEntry(i);

//     GZzHel->Fill(GZ.Zhelicity);

    if( GZ.nOfak5 > nOfak5Cut 
	or GZ.gluonCandidate_pt < gluonCandidatePtCut 
	or GZ.photonCandidate_pt < photonCandidatePtCut 
	or GZ.leadingBTag < leadingBTagCut 
	or GZ.secondLeadingBTag < secondLeadingBTagCut
	or TMath::Abs(GZ.leadingDeltaTheta) > leadingPullCut 
	or TMath::Abs(GZ.AK7leadingDeltaTheta) > AK7leadingPullCut )
      continue;

    GZnOfak5->Fill(GZ.nOfak5);
    GZdeltaR->Fill(GZ.jetDeltaR);
    GZmass->Fill(GZ.gluonCandidate_mass);
    GZphotonPt->Fill(GZ.photonCandidate_pt);
    GZgluonPt->Fill(GZ.gluonCandidate_pt);

    if( GZ.gluonCandidate_mass > gluonCandidateMassCut 
	and GZ.gluonCandidate_mass < gluonCandidateMassCut2 ){
      GZpull->Fill(TMath::Abs(GZ.leadingDeltaTheta));
      GZAK7pull->Fill(TMath::Abs(GZ.AK7leadingDeltaTheta));
      GZhel->Fill(TMath::Abs(GZ.leading_gluonHelicity));
//     GZhel_ptA->Fill( GZ.leading_gluonHelicity, GZ.jetPtAsymmetry);
    }
  }

  GZnOfak5->Scale(Integrated_luminosity/GZ_normalisation);
  GZphotonPt->Scale(Integrated_luminosity/GZ_normalisation);
  GJMCphotonPt->Add(GZphotonPt);
  GZgluonPt->Scale(Integrated_luminosity/GZ_normalisation);
  GJMCgluonPt->Add(GZgluonPt);

//   //mass
  c1->cd();
  GZmass->SetTitle("#gamma Z");
  GZmass->GetXaxis()->SetTitle("mass");
  GZmass->GetYaxis()->SetLabelSize(0.03);
  GZmass->GetXaxis()->SetLabelSize(0.03);
  GZmass->SetFillColor(kOrange);
  GZmass->SetFillStyle(3002);
  GZmass->Scale(Integrated_luminosity/GZ_normalisation);
  //  GZmass->Draw("same");
  GJMCmass->Add(GZmass);
  hCand->Add(GZmass);

  c2->cd();
  //deltaR
  GZdeltaR->SetTitle("Jet deltaR data");
  GZdeltaR->GetXaxis()->SetTitle("deltaR");
  GZdeltaR->GetYaxis()->SetLabelSize(0.03);
  GZdeltaR->GetXaxis()->SetLabelSize(0.03);
  GZdeltaR->SetFillColor(kOrange);
  GZdeltaR->SetFillStyle(3002);
  GZdeltaR->Scale(Integrated_luminosity/GZ_normalisation);
  //  GZdeltaR->Draw("same");
  GJMCdeltaR->Add(GZdeltaR);
  //  hDeltaR->Add(GZdeltaR);

  c3->cd();
//   //pull
//  GZpull->Sumw2();
  GZpull->SetTitle("Leading jet pull ZJets");
  GZpull->GetXaxis()->SetTitle("pull");
  GZpull->GetYaxis()->SetLabelSize(0.03);
  GZpull->GetXaxis()->SetLabelSize(0.03);
  GZpull->SetFillColor(kOrange);
  GZpull->SetFillStyle(3002);
  //  GZpull->DrawNormalized("same");
  GZpull->Scale(Integrated_luminosity/GZ_normalisation);
  GZpull->Add(GZpull);

  c3b->cd();
//   //AK7pull
//  GZAK7pull->Sumw2();
  GZAK7pull->SetTitle("Leading jet AK7pull ZJets");
  GZAK7pull->GetXaxis()->SetTitle("AK7pull");
  GZAK7pull->GetYaxis()->SetLabelSize(0.03);
  GZAK7pull->GetXaxis()->SetLabelSize(0.03);
  GZAK7pull->SetFillColor(kOrange);
  GZAK7pull->SetFillStyle(3002);
  //  GZAK7pull->DrawNormalized("same");
  GZAK7pull->Scale(Integrated_luminosity/GZ_normalisation);
  GZAK7pull->Add(GZAK7pull);

  c4->cd();
  //hel
  GZhel->SetTitle("Leading jet hel ZJets");
  GZhel->GetXaxis()->SetTitle("hel");
  GZhel->GetYaxis()->SetLabelSize(0.03);
  GZhel->GetXaxis()->SetLabelSize(0.03);
  GZhel->SetFillColor(kOrange);
  GZhel->SetFillStyle(3002);
  GZhel->Scale(Integrated_luminosity/GZ_normalisation);
  //  GZhel->DrawNormalized("same");
  GJMChel->Add(GZhel);


  //////////
  //PLOTTING
  //////////

  c1->cd();
  //  GJdatamass->DrawNormalized("ep");
  //  GJMCmass->DrawNormalized("same");
  hCand->Draw();
  hCand->GetXaxis()->SetTitle("M_{j1,j2}");
  GJdatamass->Draw("ep same");

  c2->cd();
  GJdatadeltaR->DrawNormalized("ep");
  GJMCdeltaR->DrawNormalized("same");

  c3->cd();
  GJMCpull->GetYaxis()->SetRangeUser(0,0.5);
  GJMCpull->DrawNormalized();
  GJdatapull->DrawNormalized("same ep");
  TLegend* PullLegend = new TLegend( 0.55, 0.65, 0.88, 0.88 );
  PullLegend->AddEntry(GJdatapull,"Data 2011 126.28 pb^{-1}");
  PullLegend->AddEntry(GJMCpull,"#gammaJets MadGraph4");
  PullLegend->SetFillColor(kWhite);
  PullLegend->SetBorderSize(0);
  PullLegend->Draw("same");

  c3b->cd();
  GJMCAK7pull->GetYaxis()->SetRangeUser(0,0.5);
  GJMCAK7pull->DrawNormalized();
  GJdataAK7pull->DrawNormalized("same ep");
  TLegend* AK7pullLegend = new TLegend( 0.55, 0.65, 0.88, 0.88 );
  AK7pullLegend->AddEntry(GJdataAK7pull,"Data 2011 126.28 pb^{-1}");
  AK7pullLegend->AddEntry(GJMCAK7pull,"#gammaJets MadGraph4");
  AK7pullLegend->SetFillColor(kWhite);
  AK7pullLegend->SetBorderSize(0);
  AK7pullLegend->Draw("same");

  c4->cd();
  GJMChel->DrawNormalized();
  GJMChel->GetYaxis()->SetRangeUser(0,0.5);
  GJdatahel->DrawNormalized("same ep");
  TLegend* HelLegend = new TLegend( 0.55, 0.65, 0.88, 0.88 );
  HelLegend->AddEntry(GJdatapull,"Data 2011 126.28 pb^{-1}");
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

  c7->cd();
  GJdata10mass->Draw();
  GJdatamass->Draw("ep same");


//   GJdatanOfak5->Draw("ep");
//   GJMCnOfak5->Draw("same");
  //  GZmass->Draw();

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
