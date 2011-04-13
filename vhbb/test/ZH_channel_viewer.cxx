// This is to see the results of the ZH_channel.cxx in version 6 analyzer v14
// ZH    : N processed events: 210562   ; L = 8193.1
// ZZ    : N processed events: 2000000  ; L = 634.9
// TTbar : N processed events: 26952028 ; L = 315.2
// ZJets : N processed events: 3986492  ; L = 104.0
// March 2011
// Bortignon Pierluigi

#include <iostream>
#include <string.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
//#include <TPad.h>

int ZH_channel_viewer( void ){

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);


  Double_t Integrated_luminosity = 30.;
  Double_t VJ_normalisation = 104.0;
  Double_t VH_normalisation = 8193.1;
  Double_t VV_normalisation = 634.9;
  Double_t TTbar_normalisation = 315.2;

  Int_t minBinMass = 14;
  Int_t maxBinMass = 17;
  std::vector<Double_t> VH_nEvents;
  std::vector<Double_t> VV_nEvents;
  std::vector<Double_t> VJ_nEvents;
  std::vector<Double_t> TTbar_nEvents;

  THStack *hCand = new THStack("hCand","higgs candidate");
  THStack *hCandHelicityCut = new THStack("hCandHelicityCut","higgs candidate helicity cut");

  THStack *hCandDthetaCut = new THStack("hCandDthetaCut","higgs candidate dtheta cut");
  THStack *hCandptAsymmCut = new THStack("hCandptAsymmCut","higgs candidate ptAsymm cut");
  THStack *hCandTOTCut = new THStack("hCandTOTCut","higgs candidate all cuts");

  THStack *hCandDthetaCut_leading = new THStack("hCandDthetaCut_leading","higgs candidate dtheta cut");
  THStack *hCandptAsymmCut_leading = new THStack("hCandptAsymmCut_leading","higgs candidate ptAsymm cut");
  THStack *hCandTOTCut_leading = new THStack("hCandTOTCut_leading","higgs candidate all cuts");

  THStack *hCandDthetaCut_secondLeading = new THStack("hCandDthetaCut_secondLeading","higgs candidate dtheta cut");
  THStack *hCandptAsymmCut_secondLeading = new THStack("hCandptAsymmCut_secondLeading","higgs candidate ptAsymm cut");
  THStack *hCandTOTCut_secondLeading = new THStack("hCandTOTCut_secondLeading","higgs candidate all cuts");


  TCanvas * c0 = new TCanvas("c0","c0", 600, 600);
  TCanvas * c1 = new TCanvas("c1","c1", 600, 600);
  TCanvas * c2 = new TCanvas("c2","c2", 600, 600);
  TCanvas * c3 = new TCanvas("c3","c3", 600, 600);
  TCanvas * c4 = new TCanvas("c4","c4", 600, 600);
  TCanvas * c5 = new TCanvas("c5","c5", 600, 600);
  TCanvas * c6 = new TCanvas("c6","c6", 600, 600);
  TCanvas * c7 = new TCanvas("c7","c7", 600, 600);
  TCanvas * c8 = new TCanvas("c8","c8", 600, 600);
  TCanvas * c9 = new TCanvas("c9","c9", 600, 600);
  TCanvas * c10 = new TCanvas("c10","c10", 600, 600);
  TCanvas * c11 = new TCanvas("c11","c11", 600, 600);
  TCanvas * c12 = new TCanvas("c12","c12", 600, 600);
  TCanvas * c13 = new TCanvas("c13","c13", 600, 600);
  TCanvas * c14 = new TCanvas("c14","c14", 600, 600);
  TCanvas * c15 = new TCanvas("c15","c15", 600, 600);
  TCanvas * c16 = new TCanvas("c16","c16", 600, 600);
//   TCanvas * c17 = new TCanvas("c17","c17", 600, 600);
//   TCanvas * c18 = new TCanvas("c18","c18", 600, 600);
//   TCanvas * c19 = new TCanvas("c19","c19", 600, 600);

//   TCanvas * c111 = new TCanvas("c111","c111", 600, 600);
//   TCanvas * c112 = new TCanvas("c112","c112", 600, 600);
//   TCanvas * c113 = new TCanvas("c113","c113", 600, 600);
//   TCanvas * c114 = new TCanvas("c114","c114", 600, 600);
//   TCanvas * c115 = new TCanvas("c115","c115", 600, 600);
//   TCanvas * c116 = new TCanvas("c116","c116", 600, 600);
//   TCanvas * c117 = new TCanvas("c117","c117", 600, 600);
//   TCanvas * c118 = new TCanvas("c118","c118", 600, 600);

//   TCanvas * c120 = new TCanvas("c120","c120", 600, 600);
//   TCanvas * c121 = new TCanvas("c121","c121", 600, 600);
//   TCanvas * c122 = new TCanvas("c122","c122", 600, 600);
//   TCanvas * c123 = new TCanvas("c123","c123", 600, 600);
//   TCanvas * c124 = new TCanvas("c124","c124", 600, 600);
//   TCanvas * c125 = new TCanvas("c125","c125", 600, 600);
//   TCanvas * c126 = new TCanvas("c126","c126", 600, 600);
//   TCanvas * c127 = new TCanvas("c127","c127", 600, 600);
//   TCanvas * c128 = new TCanvas("c128","c128", 600, 600);
//   TCanvas * c129 = new TCanvas("c129","c129", 600, 600);
//   TCanvas * c130 = new TCanvas("c130","c130", 600, 600);
//   TCanvas * c131 = new TCanvas("c131","c131", 600, 600);
//   TCanvas * c132 = new TCanvas("c132","c132", 600, 600);

// //Bidimensional histograms

  TCanvas * c20 = new TCanvas("c20","c20", 600, 600);
  TCanvas * c21 = new TCanvas("c21","c21", 600, 600);
  TCanvas * c22 = new TCanvas("c22","c22", 600, 600);
//   TCanvas * c23 = new TCanvas("c23","c23", 600, 600);
  TCanvas * c24 = new TCanvas("c24","c24", 600, 600);
// //   TCanvas * c25 = new TCanvas("c25","c25", 600, 600);
// //   TCanvas * c26 = new TCanvas("c26","c26", 600, 600);
// //   TCanvas * c27 = new TCanvas("c27","c27", 600, 600);
// //   TCanvas * c28 = new TCanvas("c28","c28", 600, 600);
// // //   TCanvas * c29 = new TCanvas("c29","c29", 600, 600);


  TCanvas * c30 = new TCanvas("c30","c30", 600, 600);
  TCanvas * c31 = new TCanvas("c31","c31", 600, 600);
  TCanvas * c32 = new TCanvas("c32","c32", 600, 600);
//   TCanvas * c33 = new TCanvas("c33","c33", 600, 600);
  TCanvas * c34 = new TCanvas("c34","c34", 600, 600);
//   TCanvas * c35 = new TCanvas("c35","c35", 600, 600);
//   TCanvas * c36 = new TCanvas("c36","c36", 600, 600);
//   TCanvas * c37 = new TCanvas("c37","c37", 600, 600);
//   TCanvas * c38 = new TCanvas("c38","c38", 600, 600);
//   TCanvas * c39 = new TCanvas("c39","c39", 600, 600);

//   TCanvas * c40 = new TCanvas("c40","c40", 600, 600);
//   TCanvas * c41 = new TCanvas("c41","c41", 600, 600);
//   TCanvas * c42 = new TCanvas("c42","c42", 600, 600);
//   TCanvas * c43 = new TCanvas("c43","c43", 600, 600);
//   TCanvas * c44 = new TCanvas("c44","c44", 600, 600);
//   TCanvas * c45 = new TCanvas("c45","c45", 600, 600);
//   TCanvas * c46 = new TCanvas("c46","c46", 600, 600);
//   TCanvas * c47 = new TCanvas("c47","c47", 600, 600);
//   TCanvas * c48 = new TCanvas("c48","c48", 600, 600);
//   TCanvas * c49 = new TCanvas("c49","c49", 600, 600);

//   TCanvas * c50 = new TCanvas("c50","c50", 600, 600);
//   TCanvas * c51 = new TCanvas("c51","c51", 600, 600);
//   TCanvas * c52 = new TCanvas("c52","c52", 600, 600);
//   TCanvas * c53 = new TCanvas("c53","c53", 600, 600);
//   TCanvas * c54 = new TCanvas("c54","c54", 600, 600);
//   TCanvas * c55 = new TCanvas("c55","c55", 600, 600);
//   TCanvas * c56 = new TCanvas("c56","c56", 600, 600);
//   TCanvas * c57 = new TCanvas("c57","c57", 600, 600);
//   TCanvas * c58 = new TCanvas("c58","c58", 600, 600);
//   TCanvas * c59 = new TCanvas("c59","c59", 600, 600);


  std::string path = "./ZH_channel_v6";
  std::string subDir = "ZHchannel";
  std::string additional = "";

  Double_t min_ptAsymm = 100; // 0.
  Double_t max_ptAsymm = 175; // 0.75
  Double_t min_invmass = 300; // 100
  Double_t max_invmass = 420; // 140
  Double_t min_dtheta = 0;
  Double_t max_dtheta = 188; // 1.57
  Int_t min_helicity = 0; // -1
  Int_t max_helicity = 180; // 0.8
  // TTbar

  std::string signal = path+"/ZH_channel_TTbar"+additional.c_str()+"/ZMuMu_channel_v14_TTbar"+additional.c_str()+".root";
  TFile::Open(signal.c_str());
  gDirectory->cd(subDir.c_str());

  c0->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_Zcandidate_mass->SetTitle("Z candidate mass TTbar");
  h_Zcandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_Zcandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_Zcandidate_mass->GetXaxis()->SetRangeUser(70,110);
  h_Zcandidate_mass->SetFillColor(kBlue);
  h_Zcandidate_mass->SetFillStyle(3002);
  h_Zcandidate_mass->DrawNormalized();

  c1->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_invmassJet_general->SetTitle("higgs candidate mass TTbar");
  h_invmassJet_general->GetYaxis()->SetLabelSize(0.03);
  h_invmassJet_general->GetXaxis()->SetLabelSize(0.03);
  h_invmassJet_general->Rebin(8);
  h_invmassJet_general->SetFillColor(kBlue);
  h_invmassJet_general->SetFillStyle(3002);
  h_invmassJet_general->DrawNormalized();

  c2->cd();
  //  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_deltaTheta->SetTitle("Pull angle TTbar");
  h_deltaTheta->Rebin(10);
  h_deltaTheta->GetXaxis()->SetTitle("#Delta #theta_{t}");
  h_deltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_deltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_deltaTheta->GetXaxis()->SetRangeUser(-4,4);
  h_deltaTheta->SetFillColor(kBlue);
  h_deltaTheta->SetFillStyle(3002);
  h_deltaTheta->DrawNormalized();

  c3->cd();
  //  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_HigherDeltaTheta->SetTitle("Pull angle leading jet TTbar");
  h_HigherDeltaTheta->Rebin(10);
  h_HigherDeltaTheta->GetXaxis()->SetTitle("#Delta #theta_{t}");
  h_HigherDeltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_HigherDeltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_HigherDeltaTheta->GetXaxis()->SetRangeUser(-4,4);
  h_HigherDeltaTheta->SetFillColor(kBlue);
  h_HigherDeltaTheta->SetFillStyle(3002);
  h_HigherDeltaTheta->DrawNormalized();
 
  c4->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_LowerDeltaTheta->SetTitle("Pull angle second leading let TTbar");
  h_LowerDeltaTheta->Rebin(10);
  h_LowerDeltaTheta->GetXaxis()->SetTitle("#Delta #theta_{t}");
  h_LowerDeltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_LowerDeltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_LowerDeltaTheta->GetXaxis()->SetRangeUser(-4,4);
  h_LowerDeltaTheta->SetFillColor(kBlue);
  h_LowerDeltaTheta->SetFillStyle(3002);
  h_LowerDeltaTheta->DrawNormalized();

  c5->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaEtaGeneral->SetTitle("Jet #Delta #eta TTbar");
  h_jetDeltaEtaGeneral->Rebin(4);
  h_jetDeltaEtaGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->GetXaxis()->SetRangeUser(-0.1,3);
  h_jetDeltaEtaGeneral->SetFillColor(kBlue);
  h_jetDeltaEtaGeneral->SetFillStyle(3002);
  h_jetDeltaEtaGeneral->DrawNormalized();

  c6->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaR_general->SetTitle("Jet #Delta R TTbar");
  h_jetDeltaR_general->Rebin(8);
  h_jetDeltaR_general->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->GetXaxis()->SetRangeUser(0,5);
  h_jetDeltaR_general->SetFillColor(kBlue);
  h_jetDeltaR_general->SetFillStyle(3002);
  h_jetDeltaR_general->DrawNormalized();

  c7->cd();
  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_higgsCandidate_mass->SetTitle("Jet mass TTbar");
  h_higgsCandidate_mass->Rebin(24);
  h_higgsCandidate_mass->GetXaxis()->SetTitle("mass");
  h_higgsCandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->SetFillColor(kBlue);
  h_higgsCandidate_mass->SetFillStyle(3002);
  h_higgsCandidate_mass->DrawNormalized();
  h_higgsCandidate_mass->Scale(Integrated_luminosity/TTbar_normalisation);
  TTbar_nEvents.push_back( h_higgsCandidate_mass->Integral(minBinMass,maxBinMass) );
  hCand->Add(h_higgsCandidate_mass);

  c8->cd();
  //  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetPtAsymmetryGeneral->SetTitle("Pt Asymmetry TTbar");
  h_jetPtAsymmetryGeneral->Rebin(8);
  h_jetPtAsymmetryGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetPtAsymmetryGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetPtAsymmetryGeneral->GetXaxis()->SetTitle("jet p_{t} asymm");
  h_jetPtAsymmetryGeneral->SetFillColor(kBlue);
  h_jetPtAsymmetryGeneral->SetFillStyle(3002);
  h_jetPtAsymmetryGeneral->DrawNormalized();

  c10->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("TTbar_x");
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_x->SetTitle("dTheta mass windows TTbar");
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_x->SetFillColor(kBlue);
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_x->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_x->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_x->Rebin(10);
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_x->Draw();
  //  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c11->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  //  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("TTbar_y");
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_y->SetTitle("ptAsymm mass windows TTbar");
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_y->SetFillColor(kBlue);
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_y->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_y->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_y->Rebin(10);
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_y->Draw();
  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c12->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("TTbar_z");
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_z->SetTitle("Mjj dthetaCut TTbar");
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_z->SetFillColor(kBlue);
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_z->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_TTbar_z->Rebin(24);
  hCandDthetaCut->Add(h3_deltaTheta_ptAsymm_invmassJet_TTbar_z);
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();

  c13->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("TTbarptAs_z");
  h3_deltaTheta_ptAsymm_invmassJet_TTbarptAs_z->SetTitle("Mjj ptAsymmCut TTbar");
  h3_deltaTheta_ptAsymm_invmassJet_TTbarptAs_z->SetFillColor(kBlue);
  h3_deltaTheta_ptAsymm_invmassJet_TTbarptAs_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_TTbarptAs_z->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_TTbarptAs_z->Rebin(24);
  hCandptAsymmCut->Add(h3_deltaTheta_ptAsymm_invmassJet_TTbarptAs_z);
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();

  c14->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("TTbarTOT_z");
  h3_deltaTheta_ptAsymm_invmassJet_TTbarTOT_z->SetTitle("Mjj allCut TTbar");
  h3_deltaTheta_ptAsymm_invmassJet_TTbarTOT_z->SetFillColor(kBlue);
  h3_deltaTheta_ptAsymm_invmassJet_TTbarTOT_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_TTbarTOT_z->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_TTbarTOT_z->Rebin(24);
  TTbar_nEvents.push_back( h3_deltaTheta_ptAsymm_invmassJet_TTbarTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut->Add(h3_deltaTheta_ptAsymm_invmassJet_TTbarTOT_z);

  c15->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_helicity_ptAsymm_invmassJet->GetXaxis()->SetRange(min_helicity,max_helicity);
  h3_helicity_ptAsymm_invmassJet->Project3D("TTbarHl_z");
  h3_helicity_ptAsymm_invmassJet_TTbarHl_z->SetTitle("Mjj Helicity Cut TTbar");
  h3_helicity_ptAsymm_invmassJet_TTbarHl_z->SetFillColor(kBlue);
  h3_helicity_ptAsymm_invmassJet_TTbarHl_z->SetFillStyle(3002);
  h3_helicity_ptAsymm_invmassJet_TTbarHl_z->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_helicity_ptAsymm_invmassJet_TTbarHl_z->Rebin(24);
  double TT = h3_helicity_ptAsymm_invmassJet_TTbarHl_z->Integral(minBinMass,maxBinMass);
  TTbar_nEvents.push_back( h3_helicity_ptAsymm_invmassJet_TTbarHl_z->Integral(minBinMass,maxBinMass) );
  hCandHelicityCut->Add(h3_helicity_ptAsymm_invmassJet_TTbarHl_z);
  h3_helicity_ptAsymm_invmassJet->GetXaxis()->UnZoom();;

  c16->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_helicity_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_helicity_ptAsymm_invmassJet->Project3D("TTbar_x");
  h3_helicity_ptAsymm_invmassJet_TTbar_x->SetTitle("helicity mass windows TTbar");
  h3_helicity_ptAsymm_invmassJet_TTbar_x->SetFillColor(kBlue);
  h3_helicity_ptAsymm_invmassJet_TTbar_x->SetFillStyle(3002);
  h3_helicity_ptAsymm_invmassJet_TTbar_x->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_helicity_ptAsymm_invmassJet_TTbar_x->Rebin(10);
  h3_helicity_ptAsymm_invmassJet_TTbar_x->GetYaxis()->SetRangeUser(0,3);
  h3_helicity_ptAsymm_invmassJet_TTbar_x->Draw();
  h3_helicity_ptAsymm_invmassJet->GetZaxis()->UnZoom();


  c20->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("TTbar_x");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->SetTitle("dTheta mass windows TTbar");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->SetFillColor(kBlue);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->Rebin(10);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->Draw();
  //  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c21->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  //  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("TTbar_y");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->SetTitle("ptAsymm mass windows TTbar");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->SetFillColor(kBlue);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->Rebin(10);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->Draw();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c22->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("TTbar_z");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_z->SetTitle("Mjj dthetaCut TTbar");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_z->SetFillColor(kBlue);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_z->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_z->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_z->Rebin(24);
  hCandDthetaCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbar_z);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();

//   c23->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("TTbarptAs_z");
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z->SetTitle("Mjj ptAsymmCut TTbar");
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z->SetFillColor(kBlue);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z->SetFillStyle(3002);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z->Scale(Integrated_luminosity/TTbar_normalisation);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z->Rebin(24);
//   hCandptAsymmCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();

  c24->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("TTbarTOT_z");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->SetTitle("Mjj allCut TTbar");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->SetFillColor(kBlue);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->Rebin(24);
  TTbar_nEvents.push_back( h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z);



  c30->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("TTbar_x");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->SetTitle("dTheta mass windows TTbar");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->SetFillColor(kBlue);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->Rebin(10);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_x->Draw();
  //  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c31->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  //  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("TTbar_y");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->SetTitle("ptAsymm mass windows TTbar");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->SetFillColor(kBlue);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->Rebin(10);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_y->Draw();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c32->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("TTbar_z");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_z->SetTitle("Mjj dthetaCut TTbar");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_z->SetFillColor(kBlue);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_z->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_z->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_z->Rebin(24);
  hCandDthetaCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbar_z);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();

//   c33->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("TTbarptAs_z");
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z->SetTitle("Mjj ptAsymmCut TTbar");
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z->SetFillColor(kBlue);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z->SetFillStyle(3002);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z->Scale(Integrated_luminosity/TTbar_normalisation);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z->Rebin(24);
//   hCandptAsymmCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarptAs_z);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();

  c34->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("TTbarTOT_z");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->SetTitle("Mjj allCut TTbar");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->SetFillColor(kBlue);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->Scale(Integrated_luminosity/TTbar_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->Rebin(24);
  TTbar_nEvents.push_back( h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_TTbarTOT_z);



  /****************/
  /* ZJets Herwig */
  /****************/

  std::string ZH_channel_ZJetsHerwig = path+"/ZH_channel_ZJets_herwig"+additional.c_str()+"/ZMuMu_channel_v14_ZJetsHerwig"+additional.c_str()+".root";
  TFile::Open(ZH_channel_ZJetsHerwig.c_str());
  gDirectory->cd(subDir.c_str());


  c0->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_Zcandidate_mass->SetTitle("Z candidate mass ZJets");
  h_Zcandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_Zcandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_Zcandidate_mass->GetXaxis()->SetRangeUser(70,110);
  h_Zcandidate_mass->SetFillColor(kGreen+2);
  h_Zcandidate_mass->SetFillStyle(3002);
  h_Zcandidate_mass->DrawNormalized("same");

  c1->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_invmassJet_general->SetTitle("higgs candidate mass ZJets");
  h_invmassJet_general->GetYaxis()->SetLabelSize(0.03);
  h_invmassJet_general->GetXaxis()->SetLabelSize(0.03);
  h_invmassJet_general->Rebin(8);
  h_invmassJet_general->SetFillColor(kGreen+2);
  h_invmassJet_general->SetFillStyle(3002);
  h_invmassJet_general->DrawNormalized("same");

  c2->cd();
  //  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_deltaTheta->SetTitle("Pull angle ZJets");
  h_deltaTheta->Rebin(10);
  h_deltaTheta->GetYaxis()->SetTitle("#Delta #theta_{t}");
  h_deltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_deltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_deltaTheta->GetXaxis()->SetRangeUser(-4,4);
  h_deltaTheta->SetFillColor(kGreen+2);
  h_deltaTheta->SetFillStyle(3002);
  h_deltaTheta->DrawNormalized("same");

  c3->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_HigherDeltaTheta->SetTitle("Pull angle leading jet ZJets");
  h_HigherDeltaTheta->Rebin(10);
  h_HigherDeltaTheta->GetYaxis()->SetTitle("#Delta #theta_{t}");
  h_HigherDeltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_HigherDeltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_HigherDeltaTheta->GetXaxis()->SetRangeUser(-4,4);
  h_HigherDeltaTheta->SetFillColor(kGreen+2);
  h_HigherDeltaTheta->SetFillStyle(3002);
  h_HigherDeltaTheta->DrawNormalized("same");

  c4->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_LowerDeltaTheta->SetTitle("Pull angle second leading jet ZJets");
  h_LowerDeltaTheta->Rebin(10);
  h_LowerDeltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_LowerDeltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_LowerDeltaTheta->GetXaxis()->SetRangeUser(-4,4);
  h_LowerDeltaTheta->SetFillColor(kGreen+2);
  h_LowerDeltaTheta->SetFillStyle(3002);
  h_LowerDeltaTheta->DrawNormalized("same");

  c5->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaEtaGeneral->SetTitle("Jet #Delta #eta general ZJets");
  h_jetDeltaEtaGeneral->Rebin(4);
  h_jetDeltaEtaGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->GetXaxis()->SetRangeUser(-0.1,3);
  h_jetDeltaEtaGeneral->SetFillColor(kGreen+2);
  h_jetDeltaEtaGeneral->SetFillStyle(3002);
  h_jetDeltaEtaGeneral->DrawNormalized("same");

  c6->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaR_general->SetTitle("Jet #Delta R general ZJets");
  h_jetDeltaR_general->Rebin(8);
  h_jetDeltaR_general->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->GetXaxis()->SetRangeUser(0,5);
  h_jetDeltaR_general->SetFillColor(kGreen+2);
  h_jetDeltaR_general->SetFillStyle(3002);
  h_jetDeltaR_general->DrawNormalized("same");

  c7->cd();
  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_higgsCandidate_mass->SetTitle("Jet mass ZJets");
  h_higgsCandidate_mass->Rebin(24);
  h_higgsCandidate_mass->GetYaxis()->SetTitle("mass");
  h_higgsCandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->SetFillColor(kGreen+2);
  h_higgsCandidate_mass->SetFillStyle(3002);
  h_higgsCandidate_mass->DrawNormalized("same");
  h_higgsCandidate_mass->Scale(Integrated_luminosity/VJ_normalisation);
  VJ_nEvents.push_back( h_higgsCandidate_mass->Integral(minBinMass,maxBinMass) );
  hCand->Add(h_higgsCandidate_mass);

  c8->cd();
  //  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetPtAsymmetryGeneral->SetTitle("Pt Asymmetry ZJets");
  h_jetPtAsymmetryGeneral->Rebin(8);
  h_jetPtAsymmetryGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetPtAsymmetryGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetPtAsymmetryGeneral->SetFillColor(kGreen+2);
  h_jetPtAsymmetryGeneral->SetFillStyle(3002);
  h_jetPtAsymmetryGeneral->DrawNormalized("same");


  c10->cd();
  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VJ_x");
  h3_deltaTheta_ptAsymm_invmassJet_VJ_x->SetTitle("dTheta mass windows ZJets");
  h3_deltaTheta_ptAsymm_invmassJet_VJ_x->SetFillColor(kGreen+2);
  h3_deltaTheta_ptAsymm_invmassJet_VJ_x->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VJ_x->Scale(Integrated_luminosity/VJ_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VJ_x->Rebin(10);
  h3_deltaTheta_ptAsymm_invmassJet_VJ_x->Draw("same");
  //  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c11->cd();
  //  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VJ_y");
  h3_deltaTheta_ptAsymm_invmassJet_VJ_y->SetTitle("ptAsymm mass windows ZJets");
  h3_deltaTheta_ptAsymm_invmassJet_VJ_y->SetFillColor(kGreen+2);
  h3_deltaTheta_ptAsymm_invmassJet_VJ_y->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VJ_y->Scale(Integrated_luminosity/VJ_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VJ_y->Rebin(10);
  h3_deltaTheta_ptAsymm_invmassJet_VJ_y->Draw("same");
  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c12->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VJ_z");
  h3_deltaTheta_ptAsymm_invmassJet_VJ_z->SetTitle("Mjj dthetaCut VJ");
  h3_deltaTheta_ptAsymm_invmassJet_VJ_z->SetFillColor(kGreen+2);
  h3_deltaTheta_ptAsymm_invmassJet_VJ_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VJ_z->Scale(Integrated_luminosity/VJ_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VJ_z->Rebin(24);
  hCandDthetaCut->Add(h3_deltaTheta_ptAsymm_invmassJet_VJ_z);
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();

  c13->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VJptAs_z");
  h3_deltaTheta_ptAsymm_invmassJet_VJptAs_z->SetTitle("Mjj ptAsymmCut VJ");
  h3_deltaTheta_ptAsymm_invmassJet_VJptAs_z->SetFillColor(kGreen+2);
  h3_deltaTheta_ptAsymm_invmassJet_VJptAs_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VJptAs_z->Scale(Integrated_luminosity/VJ_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VJptAs_z->Rebin(24);
  hCandptAsymmCut->Add(h3_deltaTheta_ptAsymm_invmassJet_VJptAs_z);
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();

  c14->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VJTOT_z");
  h3_deltaTheta_ptAsymm_invmassJet_VJTOT_z->SetTitle("Mjj allCut VJ");
  h3_deltaTheta_ptAsymm_invmassJet_VJTOT_z->SetFillColor(kGreen+2);
  h3_deltaTheta_ptAsymm_invmassJet_VJTOT_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VJTOT_z->Scale(Integrated_luminosity/VJ_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VJTOT_z->Rebin(24);
  VJ_nEvents.push_back( h3_deltaTheta_ptAsymm_invmassJet_VJTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut->Add(h3_deltaTheta_ptAsymm_invmassJet_VJTOT_z);

  c15->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_helicity_ptAsymm_invmassJet->GetXaxis()->SetRange(min_helicity,max_helicity);
  h3_helicity_ptAsymm_invmassJet->Project3D("VJHl_z");
  h3_helicity_ptAsymm_invmassJet_VJHl_z->SetTitle("Mjj Helicity Cut VJ");
  h3_helicity_ptAsymm_invmassJet_VJHl_z->SetFillColor(kGreen+2);
  h3_helicity_ptAsymm_invmassJet_VJHl_z->SetFillStyle(3002);
  h3_helicity_ptAsymm_invmassJet_VJHl_z->Scale(Integrated_luminosity/VJ_normalisation);
  h3_helicity_ptAsymm_invmassJet_VJHl_z->Rebin(24);
  double VJ = h3_helicity_ptAsymm_invmassJet_VJHl_z->Integral(minBinMass,maxBinMass);
  VJ_nEvents.push_back( h3_helicity_ptAsymm_invmassJet_VJHl_z->Integral(minBinMass,maxBinMass) );
  hCandHelicityCut->Add(h3_helicity_ptAsymm_invmassJet_VJHl_z);
  h3_helicity_ptAsymm_invmassJet->GetXaxis()->UnZoom();

  c16->cd();
  gPad->SetGridy();
  gPad->SetGridx();
   h3_helicity_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_helicity_ptAsymm_invmassJet->Project3D("VJ_x");
  h3_helicity_ptAsymm_invmassJet_VJ_x->SetTitle("helicity mass windows VJ");
  h3_helicity_ptAsymm_invmassJet_VJ_x->SetFillColor(kGreen+2);
  h3_helicity_ptAsymm_invmassJet_VJ_x->SetFillStyle(3002);
  h3_helicity_ptAsymm_invmassJet_VJ_x->Scale(Integrated_luminosity/VJ_normalisation);
  h3_helicity_ptAsymm_invmassJet_VJ_x->Rebin(10);
  h3_helicity_ptAsymm_invmassJet_VJ_x->Draw("same");
  h3_helicity_ptAsymm_invmassJet->GetZaxis()->UnZoom();


  c20->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VJ_x");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_x->SetTitle("dTheta mass windows VJ");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_x->SetFillColor(kGreen+2);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_x->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_x->Scale(Integrated_luminosity/VJ_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_x->Rebin(10);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_x->Draw("same");
  //  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c21->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  //  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VJ_y");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_y->SetTitle("ptAsymm mass windows VJ");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_y->SetFillColor(kGreen+2);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_y->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_y->Scale(Integrated_luminosity/VJ_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_y->Rebin(10);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_y->Draw("same");
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c22->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VJ_z");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_z->SetTitle("Mjj dthetaCut VJ");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_z->SetFillColor(kGreen+2);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_z->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_z->Scale(Integrated_luminosity/VJ_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_z->Rebin(24);
  hCandDthetaCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_VJ_z);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();

//   c23->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VJptAs_z");
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z->SetTitle("Mjj ptAsymmCut VJ");
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z->SetFillColor(kGreen+2);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z->SetFillStyle(3002);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z->Scale(Integrated_luminosity/VJ_normalisation);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z->Rebin(24);
//   hCandptAsymmCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();

  c24->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VJTOT_z");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->SetTitle("Mjj allCut VJ");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->SetFillColor(kGreen+2);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->Scale(Integrated_luminosity/VJ_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->Rebin(24);
  VJ_nEvents.push_back( h3_leadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z);



  c30->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VJ_x");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_x->SetTitle("dTheta mass windows VJ");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_x->SetFillColor(kGreen+2);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_x->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_x->Scale(Integrated_luminosity/VJ_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_x->Rebin(10);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_x->Draw("same");
  //  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c31->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  //  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VJ_y");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_y->SetTitle("ptAsymm mass windows VJ");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_y->SetFillColor(kGreen+2);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_y->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_y->Scale(Integrated_luminosity/VJ_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_y->Rebin(10);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_y->Draw("same");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c32->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VJ_z");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_z->SetTitle("Mjj dthetaCut VJ");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_z->SetFillColor(kGreen+2);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_z->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_z->Scale(Integrated_luminosity/VJ_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_z->Rebin(24);
  hCandDthetaCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJ_z);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();

//   c33->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VJptAs_z");
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z->SetTitle("Mjj ptAsymmCut VJ");
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z->SetFillColor(kGreen+2);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z->SetFillStyle(3002);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z->Scale(Integrated_luminosity/VJ_normalisation);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z->Rebin(24);
//   hCandptAsymmCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJptAs_z);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();

  c34->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VJTOT_z");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->SetTitle("Mjj allCut VJ");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->SetFillColor(kGreen+2);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->Scale(Integrated_luminosity/VJ_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->Rebin(24);
  VJ_nEvents.push_back( h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VJTOT_z);


//   c22->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetDeltaR_higgsCandidateMass->SetTitle("dR vs Mjj ZJets");
//   h2_jetDeltaR_higgsCandidateMass->GetYaxis()->SetTitle("M_{jj}");
//   h2_jetDeltaR_higgsCandidateMass->GetYaxis()->SetTitle("#Delta R");
//   h2_jetDeltaR_higgsCandidateMass->RebinX(2);
//   h2_jetDeltaR_higgsCandidateMass->RebinY(16);
//   h2_jetDeltaR_higgsCandidateMass->GetYaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_higgsCandidateMass->GetYaxis()->SetRangeUser(60,160);
//   h2_jetDeltaR_higgsCandidateMass->GetXaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_higgsCandidateMass->GetXaxis()->SetRangeUser(0,4);
//   h2_jetDeltaR_higgsCandidateMass->SetFillColor(kYellow);
//   h2_jetDeltaR_higgsCandidateMass->SetFillStyle(3002);
//   h2_jetDeltaR_higgsCandidateMass->DrawNormalized("COLZ");
//   c22->Print("ZH_channel/plots/c22.png");

//   c25->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetDeltaR_jetPtAsymmetry->SetTitle("deltaR vs ptAsymmetry ZJets");
//   h2_jetDeltaR_jetPtAsymmetry->GetYaxis()->SetTitle("p_{t} Asymmetry");
//   h2_jetDeltaR_jetPtAsymmetry->GetXaxis()->SetTitle("#Delta R");
//   h2_jetDeltaR_jetPtAsymmetry->GetYaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_jetPtAsymmetry->GetYaxis()->SetRangeUser(60,160);
//   h2_jetDeltaR_jetPtAsymmetry->GetXaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_jetPtAsymmetry->GetXaxis()->SetRangeUser(0,4);
//   h2_jetDeltaR_jetPtAsymmetry->SetFillColor(kCyan);
//   h2_jetDeltaR_jetPtAsymmetry->SetFillStyle(3002);
//   h2_jetDeltaR_jetPtAsymmetry->DrawNormalized("COLZ");
//   c25->Print("ZH_channel/plots/c25.png");

//   c28->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetDeltaEta_jetDeltaR->SetTitle("dR vs dEta ZJets");
//   h2_jetDeltaEta_jetDeltaR->GetYaxis()->SetTitle("#Delta R");
//   h2_jetDeltaEta_jetDeltaR->GetXaxis()->SetTitle("#Delta #eta");
//   h2_jetDeltaEta_jetDeltaR->GetYaxis()->SetLabelSize(0.03);
//   h2_jetDeltaEta_jetDeltaR->GetYaxis()->SetRangeUser(60,160);
//   h2_jetDeltaEta_jetDeltaR->GetXaxis()->SetLabelSize(0.03);
//   h2_jetDeltaEta_jetDeltaR->GetXaxis()->SetRangeUser(0,4);
//   h2_jetDeltaEta_jetDeltaR->SetFillColor(kCyan);
//   h2_jetDeltaEta_jetDeltaR->SetFillStyle(3002);
//   h2_jetDeltaEta_jetDeltaR->DrawNormalized("COLZ");
//   c28->Print("ZH_channel/plots/c28.png");

//   c32->cd();
//   //  gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_invmassJet->SetTitle("Pull angle vs Mjj ZJets");
//   h2_deltaTheta_invmassJet->GetXaxis()->SetTitle("#Delta #theta_{t}");
//   h2_deltaTheta_invmassJet->GetYaxis()->SetTitle("M_{jj}");
//   h2_deltaTheta_invmassJet->RebinY(10);
//   h2_deltaTheta_invmassJet->RebinX(10);
//   h2_deltaTheta_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_invmassJet->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_invmassJet->GetXaxis()->SetRangeUser(-4,4);
//   h2_deltaTheta_invmassJet->SetFillColor(kCyan);
//   h2_deltaTheta_invmassJet->SetFillStyle(3202);
//   h2_deltaTheta_invmassJet->DrawNormalized("COLZ");
//   c32->Print("ZH_channel/plots/c32.png");


//   c35->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_JetDeltaR->SetTitle("Pull angle vs dR ZJets");
//   h2_deltaTheta_JetDeltaR->RebinX(10);
//   h2_deltaTheta_JetDeltaR->RebinY(10);
//   h2_deltaTheta_JetDeltaR->GetYaxis()->SetTitle("M_{jj}");
//   h2_deltaTheta_JetDeltaR->GetXaxis()->SetTitle("#Delta #theta_{t}");
//   h2_deltaTheta_JetDeltaR->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaR->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaR->GetXaxis()->SetRangeUser(-1,2);

//   h2_deltaTheta_JetDeltaR->SetFillColor(kCyan);
//   h2_deltaTheta_JetDeltaR->SetFillStyle(3002);

//   h2_deltaTheta_JetDeltaR->DrawNormalized("COLZ");
//   c35->Print("ZH_channel/plots/c35.png");

 
//   c38->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_JetDeltaEta->SetTitle("Pull angle vs dEta ZJets");
//   h2_deltaTheta_JetDeltaEta->RebinX(10);
//   h2_deltaTheta_JetDeltaEta->RebinY(10);
//   h2_deltaTheta_JetDeltaEta->GetXaxis()->SetTitle("#Delta #theta_{t}");
//   h2_deltaTheta_JetDeltaEta->GetYaxis()->SetTitle("#Delta #eta");
//   h2_deltaTheta_JetDeltaEta->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaEta->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaEta->GetXaxis()->SetRangeUser(-4,4);

//   h2_deltaTheta_JetDeltaEta->SetFillColor(kCyan);
//   h2_deltaTheta_JetDeltaEta->SetFillStyle(3002);

//   h2_deltaTheta_JetDeltaEta->DrawNormalized("COLZ");
//   c38->Print("ZH_channel/plots/c38.png");

//   c41->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_JetDeltaPhi->SetTitle("Pull angle vs dPhi ZJets");
//   h2_deltaTheta_JetDeltaPhi->RebinX(10);
//   h2_deltaTheta_JetDeltaPhi->RebinY(10);
//   h2_deltaTheta_JetDeltaPhi->GetXaxis()->SetTitle("#Delta #theta_{t}");
//   h2_deltaTheta_JetDeltaPhi->GetYaxis()->SetTitle("#Delta #phi");
//   h2_deltaTheta_JetDeltaPhi->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaPhi->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaPhi->GetXaxis()->SetRangeUser(-4,4);

//   h2_deltaTheta_JetDeltaPhi->SetFillColor(kCyan);
//   h2_deltaTheta_JetDeltaPhi->SetFillStyle(3002);

//   h2_deltaTheta_JetDeltaPhi->DrawNormalized("COLZ");
//   c41->Print("ZH_channel/plots/c41.png");

//   c50->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_JetDeltaEta_invmassJet->SetTitle("Jet #Delta #eta general ZJets");
//   h2_JetDeltaEta_invmassJet->RebinX(4);
//   h2_JetDeltaEta_invmassJet->RebinY(10);
//   h2_JetDeltaEta_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_JetDeltaEta_invmassJet->GetXaxis()->SetLabelSize(0.03);
//   h2_JetDeltaEta_invmassJet->GetXaxis()->SetRangeUser(-0.1,3);

//   h2_JetDeltaEta_invmassJet->SetFillColor(kCyan);
//   h2_JetDeltaEta_invmassJet->SetFillStyle(3002);

//   h2_JetDeltaEta_invmassJet->DrawNormalized("COLZ");
//   c50->Print("ZH_channel/plots/c50.png");

//   c53->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_JetDeltaR_invmassJet->SetTitle("Jet #Delta R general ZJets");
//   h2_JetDeltaR_invmassJet->RebinX(4);
//   h2_JetDeltaR_invmassJet->RebinY(10);
//   h2_JetDeltaR_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_JetDeltaR_invmassJet->GetXaxis()->SetLabelSize(0.03);
//   h2_JetDeltaR_invmassJet->GetXaxis()->SetRangeUser(0,5);

//   h2_JetDeltaR_invmassJet->SetFillColor(kCyan);
//   h2_JetDeltaR_invmassJet->SetFillStyle(3002);

//   h2_JetDeltaR_invmassJet->DrawNormalized("COLZ");
//   c53->Print("ZH_channel/plots/c53.png");

//   c59->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetPtAsymmetry_invmassJet->RebinX(8);
//   h2_jetPtAsymmetry_invmassJet->RebinY(10);
//   h2_jetPtAsymmetry_invmassJet->SetTitle("pt_asymmetry_invmass ZJets");
//   h2_jetPtAsymmetry_invmassJet->GetYaxis()->SetTitle("inv_mass");
//   h2_jetPtAsymmetry_invmassJet->GetXaxis()->SetTitle("jet pt asymmetry");
//   h2_jetPtAsymmetry_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_jetPtAsymmetry_invmassJet->GetXaxis()->SetLabelSize(0.03);

//   h2_jetPtAsymmetry_invmassJet->SetFillColor(kCyan);
//   h2_jetPtAsymmetry_invmassJet->SetFillStyle(3002);

//   h2_jetPtAsymmetry_invmassJet->DrawNormalized("COLZ");
//   c59->Print("ZH_channel/plots/c59.png");


 
  /******/
  /* ZZ */
  /******/

  std::string ZH_channel_ZZ = path+"/ZH_channel_ZZ"+additional.c_str()+"/ZMuMu_channel_v14_ZZ"+additional.c_str()+".root";
  TFile::Open(ZH_channel_ZZ.c_str());
  gDirectory->cd(subDir.c_str());

  c0->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_Zcandidate_mass->SetTitle("Z candidate mass ZZ");
  h_Zcandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_Zcandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_Zcandidate_mass->GetXaxis()->SetRangeUser(70,110);
  h_Zcandidate_mass->SetFillColor(kOrange+3);
  h_Zcandidate_mass->SetFillStyle(3002);
  h_Zcandidate_mass->DrawNormalized("same");

  c1->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_invmassJet_general->SetTitle("higgs candidate mass ZZ");
  h_invmassJet_general->GetYaxis()->SetLabelSize(0.03);
  h_invmassJet_general->GetXaxis()->SetLabelSize(0.03);
  h_invmassJet_general->Rebin(8);
  h_invmassJet_general->SetFillColor(kOrange+3);
  h_invmassJet_general->SetFillStyle(3002);
  h_invmassJet_general->DrawNormalized("same");

  c2->cd();
  //  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_deltaTheta->SetTitle("Pull angle ZZ");
  h_deltaTheta->Rebin(10);
  h_deltaTheta->GetYaxis()->SetTitle("#Delta #theta_{t}");
  h_deltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_deltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_deltaTheta->GetXaxis()->SetRangeUser(-4,4);
  h_deltaTheta->SetFillColor(kOrange+3);
  h_deltaTheta->SetFillStyle(3002);
  h_deltaTheta->DrawNormalized("same");

  c3->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_HigherDeltaTheta->SetTitle("Pull angle leading jet ZZ");
  h_HigherDeltaTheta->Rebin(10);
  h_HigherDeltaTheta->GetYaxis()->SetTitle("#Delta #theta_{t}");
  h_HigherDeltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_HigherDeltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_HigherDeltaTheta->GetXaxis()->SetRangeUser(-4,4);
  h_HigherDeltaTheta->SetFillColor(kOrange+3);
  h_HigherDeltaTheta->SetFillStyle(3002);
  h_HigherDeltaTheta->DrawNormalized("same");

  c4->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_LowerDeltaTheta->SetTitle("Pull angle second leading jet ZZ");
  h_LowerDeltaTheta->Rebin(10);
  h_LowerDeltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_LowerDeltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_LowerDeltaTheta->GetXaxis()->SetRangeUser(-4,4);
  h_LowerDeltaTheta->SetFillColor(kOrange+3);
  h_LowerDeltaTheta->SetFillStyle(3002);
  h_LowerDeltaTheta->DrawNormalized("same");

  c5->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaEtaGeneral->SetTitle("Jet #Delta #eta general ZZ");
  h_jetDeltaEtaGeneral->Rebin(4);
  h_jetDeltaEtaGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->GetXaxis()->SetRangeUser(-0.1,3);
  h_jetDeltaEtaGeneral->SetFillColor(kOrange+3);
  h_jetDeltaEtaGeneral->SetFillStyle(3002);
  h_jetDeltaEtaGeneral->DrawNormalized("same");

  c6->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaR_general->SetTitle("Jet #Delta R general ZZ");
  h_jetDeltaR_general->Rebin(8);
  h_jetDeltaR_general->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->GetXaxis()->SetRangeUser(0,5);
  h_jetDeltaR_general->SetFillColor(kOrange+3);
  h_jetDeltaR_general->SetFillStyle(3002);
  h_jetDeltaR_general->DrawNormalized("same");

  c7->cd();
  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_higgsCandidate_mass->SetTitle("Jet mass ZZ");
  h_higgsCandidate_mass->Rebin(24);
  h_higgsCandidate_mass->GetYaxis()->SetTitle("mass");
  h_higgsCandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->SetFillColor(kOrange+3);
  h_higgsCandidate_mass->SetFillStyle(3002);
  h_higgsCandidate_mass->DrawNormalized("same");
  h_higgsCandidate_mass->Scale(Integrated_luminosity/VV_normalisation);
  VV_nEvents.push_back( h_higgsCandidate_mass->Integral(minBinMass,maxBinMass) );
  hCand->Add(h_higgsCandidate_mass);

  c8->cd();
  //  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetPtAsymmetryGeneral->SetTitle("Pt Asymmetry ZZ");
  h_jetPtAsymmetryGeneral->Rebin(8);
  h_jetPtAsymmetryGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetPtAsymmetryGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetPtAsymmetryGeneral->SetFillColor(kOrange+3);
  h_jetPtAsymmetryGeneral->SetFillStyle(3002);
  h_jetPtAsymmetryGeneral->DrawNormalized("same");

  c10->cd();
  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VV_x");
  h3_deltaTheta_ptAsymm_invmassJet_VV_x->SetTitle("dTheta mass windows ZZ");
  h3_deltaTheta_ptAsymm_invmassJet_VV_x->SetFillColor(kOrange+3);
  h3_deltaTheta_ptAsymm_invmassJet_VV_x->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VV_x->Scale(Integrated_luminosity/VV_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VV_x->Rebin(10);
  h3_deltaTheta_ptAsymm_invmassJet_VV_x->Draw("same");
  //  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c11->cd();
  //  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VV_y");
  h3_deltaTheta_ptAsymm_invmassJet_VV_y->SetTitle("ptAsymm mass windows ZZ");
  h3_deltaTheta_ptAsymm_invmassJet_VV_y->SetFillColor(kOrange+3);
  h3_deltaTheta_ptAsymm_invmassJet_VV_y->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VV_y->Scale(Integrated_luminosity/VV_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VV_y->Rebin(10);
  h3_deltaTheta_ptAsymm_invmassJet_VV_y->Draw("same");
  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c12->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VV_z");
  h3_deltaTheta_ptAsymm_invmassJet_VV_z->SetTitle("Mjj dthetaCut VV");
  h3_deltaTheta_ptAsymm_invmassJet_VV_z->SetFillColor(kOrange+3);
  h3_deltaTheta_ptAsymm_invmassJet_VV_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VV_z->Scale(Integrated_luminosity/VV_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VV_z->Rebin(24);
  hCandDthetaCut->Add(h3_deltaTheta_ptAsymm_invmassJet_VV_z);
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();

  c13->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VVptAs_z");
  h3_deltaTheta_ptAsymm_invmassJet_VVptAs_z->SetTitle("Mjj ptAsymmCut VV");
  h3_deltaTheta_ptAsymm_invmassJet_VVptAs_z->SetFillColor(kOrange+3);
  h3_deltaTheta_ptAsymm_invmassJet_VVptAs_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VVptAs_z->Scale(Integrated_luminosity/VV_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VVptAs_z->Rebin(24);
  hCandptAsymmCut->Add(h3_deltaTheta_ptAsymm_invmassJet_VVptAs_z);
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();

  c14->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VVTOT_z");
  h3_deltaTheta_ptAsymm_invmassJet_VVTOT_z->SetTitle("Mjj allCut VV");
  h3_deltaTheta_ptAsymm_invmassJet_VVTOT_z->SetFillColor(kOrange+3);
  h3_deltaTheta_ptAsymm_invmassJet_VVTOT_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VVTOT_z->Scale(Integrated_luminosity/VV_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VVTOT_z->Rebin(24);
  VV_nEvents.push_back( h3_deltaTheta_ptAsymm_invmassJet_VVTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut->Add(h3_deltaTheta_ptAsymm_invmassJet_VVTOT_z);

  c15->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_helicity_ptAsymm_invmassJet->GetXaxis()->SetRange(min_helicity,max_helicity);
  h3_helicity_ptAsymm_invmassJet->Project3D("VVHl_z");
  h3_helicity_ptAsymm_invmassJet_VVHl_z->SetTitle("Mjj Helicity Cut VV");
  h3_helicity_ptAsymm_invmassJet_VVHl_z->SetFillColor(kOrange+3);
  h3_helicity_ptAsymm_invmassJet_VVHl_z->SetFillStyle(3002);
  h3_helicity_ptAsymm_invmassJet_VVHl_z->Scale(Integrated_luminosity/VV_normalisation);
  h3_helicity_ptAsymm_invmassJet_VVHl_z->Rebin(24);
  double VV = h3_helicity_ptAsymm_invmassJet_VVHl_z->Integral(minBinMass,maxBinMass);
  VV_nEvents.push_back( h3_helicity_ptAsymm_invmassJet_VVHl_z->Integral(minBinMass,maxBinMass) );
  hCandHelicityCut->Add(h3_helicity_ptAsymm_invmassJet_VVHl_z);
  h3_helicity_ptAsymm_invmassJet->GetXaxis()->UnZoom();

  c16->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_helicity_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_helicity_ptAsymm_invmassJet->Project3D("VV_x");
  h3_helicity_ptAsymm_invmassJet_VV_x->SetTitle("helicity mass windows VV");
  h3_helicity_ptAsymm_invmassJet_VV_x->SetFillColor(kOrange+3);
  h3_helicity_ptAsymm_invmassJet_VV_x->SetFillStyle(3002);
  h3_helicity_ptAsymm_invmassJet_VV_x->Scale(Integrated_luminosity/VV_normalisation);
  h3_helicity_ptAsymm_invmassJet_VV_x->Rebin(10);
  h3_helicity_ptAsymm_invmassJet_VV_x->Draw("same");
  h3_helicity_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c20->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VV_x");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_x->SetTitle("dTheta mass windows VV");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_x->SetFillColor(kOrange+3);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_x->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_x->Scale(Integrated_luminosity/VV_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_x->Rebin(10);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_x->Draw("same");
  //  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c21->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  //  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VV_y");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_y->SetTitle("ptAsymm mass windows VV");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_y->SetFillColor(kOrange+3);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_y->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_y->Scale(Integrated_luminosity/VV_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_y->Rebin(10);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_y->Draw("same");
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c22->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VV_z");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_z->SetTitle("Mjj dthetaCut VV");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_z->SetFillColor(kOrange+3);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_z->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_z->Scale(Integrated_luminosity/VV_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_z->Rebin(24);
  hCandDthetaCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_VV_z);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();

//   c23->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VVptAs_z");
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z->SetTitle("Mjj ptAsymmCut VV");
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z->SetFillColor(kOrange+3);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z->SetFillStyle(3002);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z->Scale(Integrated_luminosity/VV_normalisation);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z->Rebin(24);
//   hCandptAsymmCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();

  c24->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VVTOT_z");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->SetTitle("Mjj allCut VV");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->SetFillColor(kOrange+3);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->Scale(Integrated_luminosity/VV_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->Rebin(24);
  VV_nEvents.push_back( h3_leadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z);



  c30->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VV_x");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_x->SetTitle("dTheta mass windows VV");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_x->SetFillColor(kOrange+3);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_x->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_x->Scale(Integrated_luminosity/VV_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_x->Rebin(10);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_x->Draw("same");
  //  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c31->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  //  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VV_y");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_y->SetTitle("ptAsymm mass windows VV");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_y->SetFillColor(kOrange+3);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_y->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_y->Scale(Integrated_luminosity/VV_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_y->Rebin(10);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_y->Draw("same");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c32->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VV_z");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_z->SetTitle("Mjj dthetaCut VV");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_z->SetFillColor(kOrange+3);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_z->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_z->Scale(Integrated_luminosity/VV_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_z->Rebin(24);
  hCandDthetaCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VV_z);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();

//   c33->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VVptAs_z");
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z->SetTitle("Mjj ptAsymmCut VV");
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z->SetFillColor(kOrange+3);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z->SetFillStyle(3002);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z->Scale(Integrated_luminosity/VV_normalisation);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z->Rebin(24);
//   hCandptAsymmCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVptAs_z);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();

  c34->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VVTOT_z");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->SetTitle("Mjj allCut VV");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->SetFillColor(kOrange+3);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->Scale(Integrated_luminosity/VV_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->Rebin(24);
  VV_nEvents.push_back( h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VVTOT_z);



//   c21->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetDeltaR_higgsCandidateMass->SetTitle("deltaR vs higgsMass ZZ");
//   h2_jetDeltaR_higgsCandidateMass->GetYaxis()->SetTitle("higgsMass");
//   h2_jetDeltaR_higgsCandidateMass->GetYaxis()->SetTitle("deltaR");
//   h2_jetDeltaR_higgsCandidateMass->RebinX(2);
//   h2_jetDeltaR_higgsCandidateMass->RebinY(16);
//   h2_jetDeltaR_higgsCandidateMass->GetYaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_higgsCandidateMass->GetYaxis()->SetRangeUser(60,160);
//   h2_jetDeltaR_higgsCandidateMass->GetXaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_higgsCandidateMass->GetXaxis()->SetRangeUser(0,4);

//   h2_jetDeltaR_higgsCandidateMass->SetFillColor(kOrange+3);
//   h2_jetDeltaR_higgsCandidateMass->SetFillStyle(3002);

//   h2_jetDeltaR_higgsCandidateMass->DrawNormalized("COLZ");
//   c21->Print("ZH_channel/plots/c21.png");


//   c24->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetDeltaR_jetPtAsymmetry->SetTitle("deltaR vs ptAsymmetry ZZ");
//   h2_jetDeltaR_jetPtAsymmetry->GetYaxis()->SetTitle("ptAsymmetry");
//   h2_jetDeltaR_jetPtAsymmetry->GetXaxis()->SetTitle("deltaR");
//   h2_jetDeltaR_jetPtAsymmetry->GetYaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_jetPtAsymmetry->GetYaxis()->SetRangeUser(60,160);
//   h2_jetDeltaR_jetPtAsymmetry->GetXaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_jetPtAsymmetry->GetXaxis()->SetRangeUser(0,4);

//   h2_jetDeltaR_jetPtAsymmetry->SetFillColor(kCyan);
//   h2_jetDeltaR_jetPtAsymmetry->SetFillStyle(3002);

//   h2_jetDeltaR_jetPtAsymmetry->DrawNormalized("COLZ");
//   c24->Print("ZH_channel/plots/c24.png");

//   c27->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetDeltaEta_jetDeltaR->SetTitle("deltaR vs ptasymmetry signal ZZ");
//   h2_jetDeltaEta_jetDeltaR->GetYaxis()->SetTitle("#Delta R");
//   h2_jetDeltaEta_jetDeltaR->GetXaxis()->SetTitle("#Delta #eta");
//   h2_jetDeltaEta_jetDeltaR->GetYaxis()->SetLabelSize(0.03);
//   h2_jetDeltaEta_jetDeltaR->GetYaxis()->SetRangeUser(60,160);
//   h2_jetDeltaEta_jetDeltaR->GetXaxis()->SetLabelSize(0.03);
//   h2_jetDeltaEta_jetDeltaR->GetXaxis()->SetRangeUser(0,4);

//   h2_jetDeltaEta_jetDeltaR->SetFillColor(kCyan);
//   h2_jetDeltaEta_jetDeltaR->SetFillStyle(3002);

//   h2_jetDeltaEta_jetDeltaR->DrawNormalized("COLZ");
//   c27->Print("ZH_channel/plots/c27.png");

//   c31->cd();
//   //  gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_invmassJet->SetTitle("Pull angle vs invmass ZZ");
//   h2_deltaTheta_invmassJet->GetXaxis()->SetTitle("#Delta #theta_{t}");
//   h2_deltaTheta_invmassJet->GetYaxis()->SetTitle("M_{jj}");
//   h2_deltaTheta_invmassJet->RebinY(10);
//   h2_deltaTheta_invmassJet->RebinX(10);
//   h2_deltaTheta_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_invmassJet->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_invmassJet->GetXaxis()->SetRangeUser(-4,4);

//   h2_deltaTheta_invmassJet->SetFillColor(kCyan);
//   h2_deltaTheta_invmassJet->SetFillStyle(3102);

//   h2_deltaTheta_invmassJet->DrawNormalized("COLZ");
//   c31->Print("ZH_channel/plots/c31.png");

//   c34->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_JetDeltaR->SetTitle("Pull angle vs dR ZZ");
//   h2_deltaTheta_JetDeltaR->RebinX(10);
//   h2_deltaTheta_JetDeltaR->RebinY(10);
//   h2_deltaTheta_JetDeltaR->GetYaxis()->SetTitle("#Delta R");
//   h2_deltaTheta_JetDeltaR->GetXaxis()->SetTitle("#Delta #theta_{t}");
//   h2_deltaTheta_JetDeltaR->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaR->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaR->GetXaxis()->SetRangeUser(-4,4);

//   h2_deltaTheta_JetDeltaR->SetFillColor(kCyan);
//   h2_deltaTheta_JetDeltaR->SetFillStyle(3002);

//   h2_deltaTheta_JetDeltaR->DrawNormalized("COLZ");
//   c34->Print("ZH_channel/plots/c34.png");
 
//   c37->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_JetDeltaEta->SetTitle("Pull angle vs dEta VJet herwig");
//   h2_deltaTheta_JetDeltaEta->RebinX(10);
//   h2_deltaTheta_JetDeltaEta->RebinY(10);
//   h2_deltaTheta_JetDeltaEta->GetXaxis()->SetTitle("#Delta #theta_{t}");
//   h2_deltaTheta_JetDeltaEta->GetYaxis()->SetTitle("#Delta #eta");
//   h2_deltaTheta_JetDeltaEta->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaEta->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaEta->GetXaxis()->SetRangeUser(-4,4);

//   h2_deltaTheta_JetDeltaEta->SetFillColor(kCyan);
//   h2_deltaTheta_JetDeltaEta->SetFillStyle(3002);

//   h2_deltaTheta_JetDeltaEta->DrawNormalized("COLZ");
//   c37->Print("ZH_channel/plots/c37.png");

//   c40->cd();
//   //  gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_JetDeltaPhi->SetTitle("Pull angle vs dPhi ZZ"); 
//   h2_deltaTheta_JetDeltaPhi->RebinY(10); 
//   h2_deltaTheta_JetDeltaPhi->RebinX(10);
//   h2_deltaTheta_JetDeltaPhi->GetXaxis()->SetTitle("#Delta #theta_{t}"); 
//   h2_deltaTheta_JetDeltaPhi->GetYaxis()->SetTitle("#Delta #phi"); 
//   h2_deltaTheta_JetDeltaPhi->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaPhi->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaPhi->GetXaxis()->SetRangeUser(-4,4);

//   h2_deltaTheta_JetDeltaPhi->SetFillColor(kCyan);
//   h2_deltaTheta_JetDeltaPhi->SetFillStyle(3002);

//   h2_deltaTheta_JetDeltaPhi->DrawNormalized("COLZ");
//   c40->Print("ZH_channel/plots/c40.png");

//   c49->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_JetDeltaEta_invmassJet->SetTitle("Jet #Delta #eta general ZZ");
//   h2_JetDeltaEta_invmassJet->RebinX(4);
//   h2_JetDeltaEta_invmassJet->RebinY(10);
//   h2_JetDeltaEta_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_JetDeltaEta_invmassJet->GetXaxis()->SetLabelSize(0.03);
//   h2_JetDeltaEta_invmassJet->GetXaxis()->SetRangeUser(-0.1,3);

//   h2_JetDeltaEta_invmassJet->SetFillColor(kCyan);
//   h2_JetDeltaEta_invmassJet->SetFillStyle(3002);

//   h2_JetDeltaEta_invmassJet->DrawNormalized("COLZ");
//   c49->Print("ZH_channel/plots/c49.png");

//   c52->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_JetDeltaR_invmassJet->SetTitle("Jet #Delta R general ZZ");
//   h2_JetDeltaR_invmassJet->RebinX(4);
//   h2_JetDeltaR_invmassJet->RebinY(10);
//   h2_JetDeltaR_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_JetDeltaR_invmassJet->GetXaxis()->SetLabelSize(0.03);
//   h2_JetDeltaR_invmassJet->GetXaxis()->SetRangeUser(0,5);

//   h2_JetDeltaR_invmassJet->SetFillColor(kCyan);
//   h2_JetDeltaR_invmassJet->SetFillStyle(3002);

//   h2_JetDeltaR_invmassJet->DrawNormalized("COLZ");
//   c52->Print("ZH_channel/plots/c52.png");

//   c58->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetPtAsymmetry_invmassJet->RebinX(8);
//   h2_jetPtAsymmetry_invmassJet->RebinY(10);
//   h2_jetPtAsymmetry_invmassJet->SetTitle("pt_asymmetry_invmass");
//   h2_jetPtAsymmetry_invmassJet->GetYaxis()->SetTitle("inv_mass");
//   h2_jetPtAsymmetry_invmassJet->GetXaxis()->SetTitle("jet pt asymmetry");
//   h2_jetPtAsymmetry_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_jetPtAsymmetry_invmassJet->GetXaxis()->SetLabelSize(0.03);

//   h2_jetPtAsymmetry_invmassJet->SetFillColor(kCyan);
//   h2_jetPtAsymmetry_invmassJet->SetFillStyle(3002);

//   h2_jetPtAsymmetry_invmassJet->DrawNormalized("COLZ");
//   c58->Print("ZH_channel/plots/c58.png");

  /*********/
  /* ZH */
  /*********/

  std::string ZH_channel_ZH = path+"/ZH_channel_ZH"+additional.c_str()+"/ZMuMu_channel_v14_ZH"+additional.c_str()+".root";
  TFile::Open(ZH_channel_ZH.c_str());
  gDirectory->cd(subDir.c_str());

  c0->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_Zcandidate_mass->SetTitle("Z candidate mass ZH");
  h_Zcandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_Zcandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_Zcandidate_mass->SetFillColor(kRed);
  h_Zcandidate_mass->SetFillStyle(3002);
  h_Zcandidate_mass->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.15, 0.67, 0.48, 0.88);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);

  c1->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_invmassJet_general->Rebin(8);
  h_invmassJet_general->SetTitle("higgs candidate mass ZH");
  h_invmassJet_general->GetYaxis()->SetLabelSize(0.03);
  h_invmassJet_general->GetXaxis()->SetLabelSize(0.03);
  h_invmassJet_general->SetFillColor(kRed);
  h_invmassJet_general->SetFillStyle(3002);
  h_invmassJet_general->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.15, 0.67, 0.48, 0.88);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c1->Print("ZH_channel/plots/c1.png");

  c2->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h_deltaTheta->SetTitle("Pull angle ZH");
  h_deltaTheta->Rebin(10);
  h_deltaTheta->GetYaxis()->SetTitle("#Delta #theta_{t}");
  h_deltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_deltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_deltaTheta->SetFillColor(kRed);
  h_deltaTheta->SetFillStyle(3002);
  h_deltaTheta->DrawNormalized("same");
//   TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.15, 0.27, 0.48, 0.48);
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c2->Print("ZH_channel/plots/c2.png");

  c3->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_HigherDeltaTheta->SetTitle("Pull angle leading jet ZH");
  h_HigherDeltaTheta->Rebin(10);
  h_HigherDeltaTheta->GetYaxis()->SetTitle("#Delta #theta_{t}");
  h_HigherDeltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_HigherDeltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_HigherDeltaTheta->SetFillColor(kRed);
  h_HigherDeltaTheta->SetFillStyle(3002);
  h_HigherDeltaTheta->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c3->Print("ZH_channel/plots/c3.png");

  c4->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_LowerDeltaTheta->SetTitle("Pull angle second leading jet ZH");
  h_LowerDeltaTheta->Rebin(10);
  h_LowerDeltaTheta->GetYaxis()->SetLabelSize(0.03);
  h_LowerDeltaTheta->GetXaxis()->SetLabelSize(0.03);
  h_LowerDeltaTheta->SetFillColor(kRed);
  h_LowerDeltaTheta->SetFillStyle(3002);
  h_LowerDeltaTheta->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.45, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c4->Print("ZH_channel/plots/c4.png");

  c5->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaEtaGeneral->SetTitle("jet #Delta #eta general ZH");
  h_jetDeltaEtaGeneral->Rebin(4);
  h_jetDeltaEtaGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->GetYaxis()->SetRangeUser(0,0.5);
  h_jetDeltaEtaGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->SetFillColor(kRed);
  h_jetDeltaEtaGeneral->SetFillStyle(3002);
  h_jetDeltaEtaGeneral->DrawNormalized("same");
//   TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.15, 0.67, 0.48, 0.88);
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c5->Print("ZH_channel/plots/c5.png");

  c6->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaR_general->SetTitle("jet #Delta R general ZH");
  h_jetDeltaR_general->Rebin(8);
  h_jetDeltaR_general->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->SetFillColor(kRed);
  h_jetDeltaR_general->SetFillStyle(3002);
  h_jetDeltaR_general->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.67, 0.98, 0.88);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c6->Print("ZH_channel/plots/c6.png");

  c7->cd();
  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_higgsCandidate_mass->SetTitle("diJet mass ZH");
  h_higgsCandidate_mass->Rebin(24);
  h_higgsCandidate_mass->GetYaxis()->SetTitle("mass");
  h_higgsCandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->SetFillColor(kRed);
  h_higgsCandidate_mass->SetFillStyle(3002);
  h_higgsCandidate_mass->DrawNormalized("same");
  h_higgsCandidate_mass->Scale(Integrated_luminosity/VH_normalisation);
  VH_nEvents.push_back( h_higgsCandidate_mass->Integral(minBinMass,maxBinMass) );
  hCand->Add(h_higgsCandidate_mass);
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c7->Print("ZH_channel/plots/c7.png");

  c8->cd();
  //  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetPtAsymmetryGeneral->SetTitle("Pt asymmetry ZH");
  h_jetPtAsymmetryGeneral->Rebin(8);
  h_jetPtAsymmetryGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetPtAsymmetryGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetPtAsymmetryGeneral->SetFillColor(kRed);
  h_jetPtAsymmetryGeneral->SetFillStyle(3002);
  h_jetPtAsymmetryGeneral->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c8->Print("ZH_channel/plots/c8.png");


  c9->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  hCand->Draw();
  hCand->GetXaxis()->SetTitle("M_{jj}");
  hCand->GetXaxis()->SetLabelSize(0.03);
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c9->Print("ZH_channel/plots/c9.png");


//   c9->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_AbsDeltatheta_invmassJet->ProjectionX("h_deltaTheta_signal_central",300, 420);
//   TH1D * h_integral_signal = new TH1D("h_integral_signal","h_integral_signal", 30, 0, 30);
//   h_deltaTheta_signal_central->Rebin(10);
//   h_deltaTheta_signal_central->Sumw2();
//   double integral_tmp = h_deltaTheta_signal_central->Integral();
//   h_deltaTheta_signal_central->Scale( (double)1/integral_tmp );
//   for(int i = 0; i < 30; i++) {
//     std::cout <<  h_deltaTheta_signal_central->Integral(0+15,i+15) << std::endl;
//     h_integral_signal->SetBinContent( i, h_deltaTheta_signal_central->Integral(0+15,i+15) );
//   }
//   h_integral_signal->GetXaxis()->SetTitle("h_integral");
//   h_integral_signal->GetXaxis()->SetLabelSize(0.03);
//   h_integral_signal->SetFillColor(kRed);
//   h_integral_signal->SetFillStyle(3002);
//   h_integral_signal->Draw();


  c10->cd();
  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VH_x");
  h3_deltaTheta_ptAsymm_invmassJet_VH_x->SetTitle("dTheta mass ZH");
  h3_deltaTheta_ptAsymm_invmassJet_VH_x->SetFillColor(kRed);
  h3_deltaTheta_ptAsymm_invmassJet_VH_x->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VH_x->Scale(Integrated_luminosity/VH_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VH_x->Rebin(10);
  h3_deltaTheta_ptAsymm_invmassJet_VH_x->Draw("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c10->Print("ZH_channel/plots/c10.png");


  c11->cd();
  //  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VH_y");
  h3_deltaTheta_ptAsymm_invmassJet_VH_y->SetTitle("ptAsymm mass ZH");
  h3_deltaTheta_ptAsymm_invmassJet_VH_y->SetFillColor(kRed);
  h3_deltaTheta_ptAsymm_invmassJet_VH_y->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VH_y->Scale(Integrated_luminosity/VH_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VH_y->Rebin(10);
  h3_deltaTheta_ptAsymm_invmassJet_VH_y->Draw("same");
  h3_deltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c11->Print("ZH_channel/plots/c11.png");

  c12->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VH_z");
  h3_deltaTheta_ptAsymm_invmassJet_VH_z->SetTitle("Mjj dthetaCut VH");
  h3_deltaTheta_ptAsymm_invmassJet_VH_z->SetFillColor(kRed);
  h3_deltaTheta_ptAsymm_invmassJet_VH_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VH_z->Scale(Integrated_luminosity/VH_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VH_z->Rebin(24);
  hCandDthetaCut->Add(h3_deltaTheta_ptAsymm_invmassJet_VH_z);
  hCandDthetaCut->Draw();
  hCandDthetaCut->GetXaxis()->SetTitle("M_{jj}");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c12->Print("ZH_channel/plots/c12.png");
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();

  c13->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VHptAs_z");
  h3_deltaTheta_ptAsymm_invmassJet_VHptAs_z->SetTitle("Mjj ptAsymmCut VH");
  h3_deltaTheta_ptAsymm_invmassJet_VHptAs_z->SetFillColor(kRed);
  h3_deltaTheta_ptAsymm_invmassJet_VHptAs_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VHptAs_z->Scale(Integrated_luminosity/VH_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VHptAs_z->Rebin(24);
  hCandptAsymmCut->Add(h3_deltaTheta_ptAsymm_invmassJet_VHptAs_z);
  hCandptAsymmCut->Draw();
  hCandptAsymmCut->GetXaxis()->SetTitle("M_{jj}");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c13->Print("ZH_channel/plots/c13.png");
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();

  c14->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_deltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_deltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_deltaTheta_ptAsymm_invmassJet->Project3D("VHTOT_z");
  h3_deltaTheta_ptAsymm_invmassJet_VHTOT_z->SetTitle("Mjj allCut VH");
  h3_deltaTheta_ptAsymm_invmassJet_VHTOT_z->SetFillColor(kRed);
  h3_deltaTheta_ptAsymm_invmassJet_VHTOT_z->SetFillStyle(3002);
  h3_deltaTheta_ptAsymm_invmassJet_VHTOT_z->Scale(Integrated_luminosity/VH_normalisation);
  h3_deltaTheta_ptAsymm_invmassJet_VHTOT_z->Rebin(24);
  VH_nEvents.push_back( h3_deltaTheta_ptAsymm_invmassJet_VHTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut->Add(h3_deltaTheta_ptAsymm_invmassJet_VHTOT_z);
  hCandTOTCut->Draw();
  hCandTOTCut->GetXaxis()->SetTitle("M_{jj}");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c14->Print("ZH_channel/plots/c14.png");

  c15->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_helicity_ptAsymm_invmassJet->GetXaxis()->SetRange(min_helicity,max_helicity);
  h3_helicity_ptAsymm_invmassJet->Project3D("VHHl_z");
  h3_helicity_ptAsymm_invmassJet_VHHl_z->SetTitle("Mjj Helicity Cut VH");
  h3_helicity_ptAsymm_invmassJet_VHHl_z->SetFillColor(kRed);
  h3_helicity_ptAsymm_invmassJet_VHHl_z->SetFillStyle(3002);
  h3_helicity_ptAsymm_invmassJet_VHHl_z->Scale(Integrated_luminosity/VH_normalisation);
  h3_helicity_ptAsymm_invmassJet_VHHl_z->Rebin(24);
  double VH = h3_helicity_ptAsymm_invmassJet_VHHl_z->Integral(minBinMass,maxBinMass);
  VH_nEvents.push_back( h3_helicity_ptAsymm_invmassJet_VHHl_z->Integral(minBinMass,maxBinMass) );
  hCandHelicityCut->Add(h3_helicity_ptAsymm_invmassJet_VHHl_z);
  hCandHelicityCut->Draw();
  hCandHelicityCut->GetXaxis()->SetTitle("M_{jj}");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c15->Print("ZH_channel/plots/c15.png");
  h3_helicity_ptAsymm_invmassJet->GetXaxis()->UnZoom();

  c16->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_helicity_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_helicity_ptAsymm_invmassJet->Project3D("VH_x");
  h3_helicity_ptAsymm_invmassJet_VH_x->SetTitle("helicity mass windows VH");
  h3_helicity_ptAsymm_invmassJet_VH_x->SetFillColor(kRed);
  h3_helicity_ptAsymm_invmassJet_VH_x->SetFillStyle(3002);
  h3_helicity_ptAsymm_invmassJet_VH_x->Scale(Integrated_luminosity/VH_normalisation);
  h3_helicity_ptAsymm_invmassJet_VH_x->Rebin(10);
  h3_helicity_ptAsymm_invmassJet_VH_x->GetYaxis()->SetRangeUser(0,3);
  h3_helicity_ptAsymm_invmassJet_VH_x->Draw("same");
  h3_helicity_ptAsymm_invmassJet->GetZaxis()->UnZoom();
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c16->Print("ZH_channel/plots/c16.png");


  c20->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VH_x");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_x->SetTitle("dTheta mass windows VH");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_x->SetFillColor(kRed);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_x->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_x->Scale(Integrated_luminosity/VH_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_x->Rebin(10);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_x->Draw("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c20->Print("ZH_channel/plots/c20.png");


  c21->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  //  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VH_y");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_y->SetTitle("ptAsymm mass windows VH");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_y->SetFillColor(kRed);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_y->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_y->Scale(Integrated_luminosity/VH_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_y->Rebin(10);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_y->Draw("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c21->Print("ZH_channel/plots/c21.png");
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();


  c22->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VH_z");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_z->SetTitle("Mjj dthetaCut VH");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_z->SetFillColor(kRed);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_z->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_z->Scale(Integrated_luminosity/VH_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_z->Rebin(24);
  hCandDthetaCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_VH_z);
  hCandDthetaCut_leading->Draw();
  hCandDthetaCut_leading->GetXaxis()->SetTitle("M_{jj}");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c22->Print("ZH_channel/plots/c22.png");
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();


//   c23->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VHptAs_z");
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z->SetTitle("Mjj ptAsymmCut VH");
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z->SetFillColor(kRed);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z->SetFillStyle(3002);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z->Scale(Integrated_luminosity/VH_normalisation);
//   h3_leadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z->Rebin(24);
//   hCandptAsymmCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z);
//   hCandptAsymmCut_leading->Draw();
//   hCandptAsymmCut_leading->GetXaxis()->SetTitle("M_{jj}");
//   TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
//   Legend->SetFillColor(kRed);
//   Legend->SetFillStyle(3002);
//   c23->Print("ZH_channel/plots/c23.png");
//   h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();


  c24->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_leadingdeltaTheta_ptAsymm_invmassJet->Project3D("VHTOT_z");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->SetTitle("Mjj allCut VH");
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->SetFillColor(kRed);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->SetFillStyle(3002);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->Scale(Integrated_luminosity/VH_normalisation);
  h3_leadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->Rebin(24);
  VH_nEvents.push_back( h3_leadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut_leading->Add(h3_leadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z);
  hCandTOTCut_leading->Draw();
  hCandTOTCut_leading->GetXaxis()->SetTitle("M_{jj}");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c24->Print("ZH_channel/plots/c24.png");


  c30->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VH_x");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_x->SetTitle("dTheta mass windows VH");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_x->SetFillColor(kRed);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_x->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_x->Scale(Integrated_luminosity/VH_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_x->Rebin(10);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_x->Draw("same");
  //  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c30->Print("ZH_channel/plots/c30.png");


  c31->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  //  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->SetRange(min_invmass,max_invmass);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VH_y");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_y->SetTitle("ptAsymm mass windows VH");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_y->SetFillColor(kRed);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_y->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_y->Scale(Integrated_luminosity/VH_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_y->Rebin(10);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_y->Draw("same");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c31->Print("ZH_channel/plots/c31.png");
  h3_leadingdeltaTheta_ptAsymm_invmassJet->GetZaxis()->UnZoom();

  c32->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VH_z");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_z->SetTitle("Mjj dthetaCut VH");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_z->SetFillColor(kRed);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_z->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_z->Scale(Integrated_luminosity/VH_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_z->Rebin(24);
  hCandDthetaCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VH_z);
  hCandDthetaCut_secondLeading->Draw();
  hCandDthetaCut_secondLeading->GetXaxis()->SetTitle("M_{jj}");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c32->Print("ZH_channel/plots/c32.png");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->UnZoom();


//   c33->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VHptAs_z");
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z->SetTitle("Mjj ptAsymmCut VH");
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z->SetFillColor(kRed);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z->SetFillStyle(3002);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z->Scale(Integrated_luminosity/VH_normalisation);
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z->Rebin(24);
//   hCandptAsymmCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHptAs_z);
//   hCandptAsymmCut_secondLeading->Draw();
//   hCandptAsymmCut_secondLeading->GetXaxis()->SetTitle("M_{jj}");
//   TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
//   Legend->SetFillColor(kRed);
//   Legend->SetFillStyle(3002);
//   c33->Print("ZH_channel/plots/c33.png");
//   h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->UnZoom();


  c34->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetYaxis()->SetRange(min_ptAsymm, max_ptAsymm);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->GetXaxis()->SetRange(min_dtheta,max_dtheta);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet->Project3D("VHTOT_z");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->SetTitle("Mjj allCut VH");
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->SetFillColor(kRed);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->SetFillStyle(3002);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->Scale(Integrated_luminosity/VH_normalisation);
  h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->Rebin(24);
  VH_nEvents.push_back( h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z->Integral(minBinMass,maxBinMass) );
  hCandTOTCut_secondLeading->Add(h3_secondLeadingdeltaTheta_ptAsymm_invmassJet_VHTOT_z);
  hCandTOTCut_secondLeading->Draw();
  hCandTOTCut_secondLeading->GetXaxis()->SetTitle("M_{jj}");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kRed);
  Legend->SetFillStyle(3002);
  c34->Print("ZH_channel/plots/c34.png");

  Double_t background_nEvents = 1e10;
  std::cout << "    ------ Significance ----      " << std::endl;
  std::cout << " # of signal events = " << VH_nEvents.at(0) << std::endl;
  std::cout << " # of ZZ events = " << VV_nEvents.at(0) << std::endl;
  std::cout << " # of ZJets events = " << VJ_nEvents.at(0) << std::endl;
  std::cout << " # of TTbar events = " << TTbar_nEvents.at(0) << std::endl;
  background_nEvents = VV_nEvents.at(0) + VJ_nEvents.at(0) + TTbar_nEvents.at(0);
  std::cout << " # of background events = " << background_nEvents << std::endl;
  std::cout << " Significance = " << VH_nEvents.at(0)/TMath::Sqrt(background_nEvents) << std::endl;
  std::cout << " Signal/background = " << VH_nEvents.at(0)/background_nEvents << std::endl;

  std::cout << "    ------ Significance after cut on the leadingJet----      " << std::endl;
  std::cout << " # of signal events = " << VH_nEvents.at(1) << std::endl;
  std::cout << " # of ZZ events = " << VV_nEvents.at(1) << std::endl;
  std::cout << " # of ZJets events = " << VJ_nEvents.at(1) << std::endl;
  std::cout << " # of TTbar events = " << TTbar_nEvents.at(1) << std::endl;
  background_nEvents = VV_nEvents.at(1) + VJ_nEvents.at(1) + TTbar_nEvents.at(1);
  std::cout << " # of background events = " << background_nEvents << std::endl;
  std::cout << " Significance = " << VH_nEvents.at(1)/TMath::Sqrt(background_nEvents) << std::endl;
  std::cout << " Signal/background = " << VH_nEvents.at(1)/background_nEvents << std::endl;

  std::cout << "    ------ Significance after cut on the second leadingJet----      " << std::endl;
  std::cout << " # of signal events = " << VH_nEvents.at(2) << std::endl;
  std::cout << " # of ZZ events = " << VV_nEvents.at(2) << std::endl;
  std::cout << " # of ZJets events = " << VJ_nEvents.at(2) << std::endl;
  std::cout << " # of TTbar events = " << TTbar_nEvents.at(2) << std::endl;
  background_nEvents = VV_nEvents.at(2) + VJ_nEvents.at(2) + TTbar_nEvents.at(2);
  std::cout << " # of background events = " << background_nEvents << std::endl;
  std::cout << " Significance = " << VH_nEvents.at(2)/TMath::Sqrt(background_nEvents) << std::endl;
  std::cout << " Signal/background = " << VH_nEvents.at(2)/background_nEvents << std::endl;

  std::cout << "    ------ Significance after cut on the closest to the beam Jet----      " << std::endl;
  std::cout << " # of signal events = " << VH_nEvents.at(3) << std::endl;
  std::cout << " # of ZZ events = " << VV_nEvents.at(3) << std::endl;
  std::cout << " # of ZJets events = " << VJ_nEvents.at(3) << std::endl;
  std::cout << " # of TTbar events = " << TTbar_nEvents.at(3) << std::endl;
  background_nEvents = VV_nEvents.at(3) + VJ_nEvents.at(3) + TTbar_nEvents.at(3);
  std::cout << " # of background events = " << background_nEvents << std::endl;
  std::cout << " Significance = " << VH_nEvents.at(3)/TMath::Sqrt(background_nEvents) << std::endl;
  std::cout << " Signal/background = " << VH_nEvents.at(3)/background_nEvents << std::endl;

  std::cout << "    ------ Significance after cut on the helicity ----      " << std::endl;
  std::cout << " # of signal events = " << VH_nEvents.at(4) << std::endl;
  std::cout << " # of ZZ events = " << VV_nEvents.at(4) << std::endl;
  std::cout << " # of ZJets events = " << VJ_nEvents.at(4) << std::endl;
  std::cout << " # of TTbar events = " << TTbar_nEvents.at(4) << std::endl;
  background_nEvents = VV_nEvents.at(4) + VJ_nEvents.at(4) + TTbar_nEvents.at(4);
  std::cout << " # of background events = " << background_nEvents << std::endl;
  std::cout << " Significance = " << VH_nEvents.at(4)/TMath::Sqrt(background_nEvents) << std::endl;
  std::cout << " Signal/background = " << VH_nEvents.at(4)/background_nEvents << std::endl;

  std::cout << "    ------ Significance after cut on the helicity ----      " << std::endl;
  std::cout << " # of signal events = " << VH << std::endl;
  std::cout << " # of ZZ events = " << VV << std::endl;
  std::cout << " # of ZJets events = " << VJ << std::endl;
  std::cout << " # of TTbar events = " << TT << std::endl;
  background_nEvents = VV + VJ + TT;
  std::cout << " # of background events = " << background_nEvents << std::endl;
  std::cout << " Significance = " << VH/TMath::Sqrt(background_nEvents) << std::endl;
  std::cout << " Signal/background = " << VH/background_nEvents << std::endl;


//   c20->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetDeltaR_higgsCandidateMass->SetTitle("deltaR vs higgsMass signal");
//   h2_jetDeltaR_higgsCandidateMass->GetYaxis()->SetTitle("higgsMass");
//   h2_jetDeltaR_higgsCandidateMass->GetXaxis()->SetTitle("deltaR");
//   h2_jetDeltaR_higgsCandidateMass->RebinX(2);
//   h2_jetDeltaR_higgsCandidateMass->RebinY(16);
//   h2_jetDeltaR_higgsCandidateMass->GetYaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_higgsCandidateMass->GetYaxis()->SetRangeUser(60,160);
//   h2_jetDeltaR_higgsCandidateMass->GetXaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_higgsCandidateMass->GetXaxis()->SetRangeUser(0,4);

//   h2_jetDeltaR_higgsCandidateMass->SetFillColor(kRed);
//   h2_jetDeltaR_higgsCandidateMass->SetFillStyle(3002);

//   h2_jetDeltaR_higgsCandidateMass->DrawNormalized("COLZ");
//   c20->Print("ZH_channel/plots/c20.png");

//   c23->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetDeltaR_jetPtAsymmetry->SetTitle("deltaR vs ptasymmetry signal");
//   h2_jetDeltaR_jetPtAsymmetry->GetYaxis()->SetTitle("ptAsymmetry");
//   h2_jetDeltaR_jetPtAsymmetry->GetXaxis()->SetTitle("deltaR");
//   h2_jetDeltaR_jetPtAsymmetry->GetYaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_jetPtAsymmetry->GetYaxis()->SetRangeUser(60,160);
//   h2_jetDeltaR_jetPtAsymmetry->GetXaxis()->SetLabelSize(0.03);
//   h2_jetDeltaR_jetPtAsymmetry->GetXaxis()->SetRangeUser(0,4);

//   h2_jetDeltaR_jetPtAsymmetry->SetFillColor(kRed);
//   h2_jetDeltaR_jetPtAsymmetry->SetFillStyle(3002);

//   h2_jetDeltaR_jetPtAsymmetry->DrawNormalized("COLZ");
//   c23->Print("ZH_channel/plots/c23.png");

//   c26->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetDeltaEta_jetDeltaR->SetTitle("deltaR vs ptasymmetry signal");
//   h2_jetDeltaEta_jetDeltaR->GetYaxis()->SetTitle("#Delta R");
//   h2_jetDeltaEta_jetDeltaR->GetXaxis()->SetTitle("#Delta #eta");
//   h2_jetDeltaEta_jetDeltaR->GetYaxis()->SetLabelSize(0.03);
//   h2_jetDeltaEta_jetDeltaR->GetYaxis()->SetRangeUser(60,160);
//   h2_jetDeltaEta_jetDeltaR->GetXaxis()->SetLabelSize(0.03);
//   h2_jetDeltaEta_jetDeltaR->GetXaxis()->SetRangeUser(0,4);

//   h2_jetDeltaEta_jetDeltaR->SetFillColor(kRed);
//   h2_jetDeltaEta_jetDeltaR->SetFillStyle(3002);

//   h2_jetDeltaEta_jetDeltaR->DrawNormalized("COLZ");
//   c26->Print("ZH_channel/plots/c26.png");

//   c30->cd();
//   //  gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_invmassJet->SetTitle("Pull angle vs invmass");
//   h2_deltaTheta_invmassJet->GetXaxis()->SetTitle("#Delta #theta_{t}");
//   h2_deltaTheta_invmassJet->GetYaxis()->SetTitle("M_{jj}");
//   h2_deltaTheta_invmassJet->RebinY(10);
//   h2_deltaTheta_invmassJet->RebinX(10);
//   h2_deltaTheta_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_invmassJet->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_invmassJet->GetXaxis()->SetRangeUser(-4,4);

//   h2_deltaTheta_invmassJet->SetFillColor(kRed);
//   h2_deltaTheta_invmassJet->SetFillStyle(3002);

//   h2_deltaTheta_invmassJet->DrawNormalized("COLZ");
//   c30->Print("ZH_channel/plots/c30.png");

//   c33->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_JetDeltaR->SetTitle("Pull angle vs jet dR");
//   h2_deltaTheta_JetDeltaR->RebinX(10);
//   h2_deltaTheta_JetDeltaR->RebinY(10);
//   h2_deltaTheta_JetDeltaR->GetYaxis()->SetTitle("M_{jj}");
//   h2_deltaTheta_JetDeltaR->GetXaxis()->SetTitle("#Delta #theta_{t}");
//   h2_deltaTheta_JetDeltaR->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaR->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaR->GetXaxis()->SetRangeUser(-4,4);

//   h2_deltaTheta_JetDeltaR->SetFillColor(kRed);
//   h2_deltaTheta_JetDeltaR->SetFillStyle(3002);

//   h2_deltaTheta_JetDeltaR->DrawNormalized("COLZ");
//   c33->Print("ZH_channel/plots/c33.png");
 
//   c36->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_JetDeltaEta->SetTitle("Pull angle vs dEta");
//   h2_deltaTheta_JetDeltaEta->RebinX(10);
//   h2_deltaTheta_JetDeltaEta->RebinY(10);
//   h2_deltaTheta_JetDeltaEta->GetXaxis()->SetTitle("#Delta #theta_{t}");
//   h2_deltaTheta_JetDeltaEta->GetYaxis()->SetTitle("M_{jj}");
//   h2_deltaTheta_JetDeltaEta->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaEta->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaEta->GetXaxis()->SetRangeUser(-4,4);

//   h2_deltaTheta_JetDeltaEta->SetFillColor(kRed);
//   h2_deltaTheta_JetDeltaEta->SetFillStyle(3002);

//   h2_deltaTheta_JetDeltaEta->DrawNormalized("COLZ");
//   c36->Print("ZH_channel/plots/c36.png");

//   c39->cd();
//   //  gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_deltaTheta_JetDeltaPhi->SetTitle("Pull angle vs dPhi"); 
//   h2_deltaTheta_JetDeltaPhi->RebinY(10);
//   h2_deltaTheta_JetDeltaPhi->RebinX(10);
//   h2_deltaTheta_JetDeltaPhi->GetXaxis()->SetTitle("#Delta #theta_{t}"); 
//   h2_deltaTheta_JetDeltaPhi->GetYaxis()->SetTitle("M_{jj}"); 
//   h2_deltaTheta_JetDeltaPhi->GetYaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaPhi->GetXaxis()->SetLabelSize(0.03);
//   h2_deltaTheta_JetDeltaPhi->GetXaxis()->SetRangeUser(-4,4);

//   h2_deltaTheta_JetDeltaPhi->SetFillColor(kRed);
//   h2_deltaTheta_JetDeltaPhi->SetFillStyle(3002);

//   h2_deltaTheta_JetDeltaPhi->DrawNormalized("COLZ");
//   c39->Print("ZH_channel/plots/c39.png");

//   c48->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_JetDeltaEta_invmassJet->SetTitle("Jet #Delta #eta general");
//   h2_JetDeltaEta_invmassJet->RebinX(4);
//   h2_JetDeltaEta_invmassJet->RebinY(10);
//   h2_JetDeltaEta_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_JetDeltaEta_invmassJet->GetXaxis()->SetLabelSize(0.03);
//   h2_JetDeltaEta_invmassJet->GetXaxis()->SetRangeUser(-0.1,3);

//   h2_JetDeltaEta_invmassJet->SetFillColor(kRed);
//   h2_JetDeltaEta_invmassJet->SetFillStyle(3002);

//   h2_JetDeltaEta_invmassJet->DrawNormalized("COLZ");
//   c48->Print("ZH_channel/plots/c48.png");

//   c51->cd();
// //   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_JetDeltaR_invmassJet->SetTitle("Jet #Delta R general");
//   h2_JetDeltaR_invmassJet->RebinX(4);
//   h2_JetDeltaR_invmassJet->RebinY(10);
//   h2_JetDeltaR_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_JetDeltaR_invmassJet->GetXaxis()->SetLabelSize(0.03);
//   h2_JetDeltaR_invmassJet->GetXaxis()->SetRangeUser(0,5);

//   h2_JetDeltaR_invmassJet->SetFillColor(kRed);
//   h2_JetDeltaR_invmassJet->SetFillStyle(3002);

//   h2_JetDeltaR_invmassJet->DrawNormalized("COLZ");
//   c51->Print("ZH_channel/plots/c51.png");

//   c57->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   h2_jetPtAsymmetry_invmassJet->RebinX(8);
//   h2_jetPtAsymmetry_invmassJet->RebinY(10);
//   h2_jetPtAsymmetry_invmassJet->SetTitle("pt_asymmetry_invmass");
//   h2_jetPtAsymmetry_invmassJet->GetYaxis()->SetTitle("inv_mass");
//   h2_jetPtAsymmetry_invmassJet->GetXaxis()->SetTitle("jet pt asymmetry");
//   h2_jetPtAsymmetry_invmassJet->GetYaxis()->SetLabelSize(0.03);
//   h2_jetPtAsymmetry_invmassJet->GetXaxis()->SetLabelSize(0.03);

//   h2_jetPtAsymmetry_invmassJet->SetFillColor(kRed);
//   h2_jetPtAsymmetry_invmassJet->SetFillStyle(3002);

//   h2_jetPtAsymmetry_invmassJet->DrawNormalized("COLZ");
//   c57->Print("ZH_channel/plots/c57.png");


  return 0;

}


//  LocalWords:  normalisation
