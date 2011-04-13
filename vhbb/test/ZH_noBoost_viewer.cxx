#include <iostream>
#include <string.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>


int ZH_noBoost_viewer( void ){

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

//   TFile *_file0 = TFile::Open("./ZH_noBoost/res/ZH_noBoost.root");
  //  TFile *_file0 = TFile::Open("./ZH_Boost55/res/ZH_Boost55.root");
//   TFile *_file0 = TFile::Open("./ZH_Boost120/res/ZH_Boost120.root");
//   TFile *_file0 = TFile::Open("./ZH_Boost120_test/res/ZH_Boost120_test.root");
  TFile *_file0 = TFile::Open("./ZH_Boost155_test/res/ZH_Boost155_test.root");
//  TFile *_file0 = TFile::Open("./ZH_Boost100/res/ZH_Boost100.root");
//   TFile *_file0 = TFile::Open("./ZH_noBoost_test/res/ZH_noBoost_test.root");
//   TFile *_file0 = TFile::Open("./ZH_noBoost_test2/res/ZH_noBoost_test2.root");
  //  ZHchannel.cd();
  gDirectory->cd("ZHchannel");

  c1->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_deltaTheta->SetTitle("ZH closestToBeam");
  h_deltaTheta->SetLineWidth(2);
  h_deltaTheta->SetLineColor(kBlue);
  h_deltaTheta->Rebin(10);
  h_deltaTheta->DrawNormalized();
  c2->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_HigherDeltaTheta->SetTitle("ZH leadingJet");
  h_HigherDeltaTheta->SetLineWidth(2);
  h_HigherDeltaTheta->SetLineColor(kBlue);
  h_HigherDeltaTheta->Rebin(10);
  h_HigherDeltaTheta->DrawNormalized();
  c3->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_LowerDeltaTheta->SetTitle("ZH secondLeadingJet");
  h_LowerDeltaTheta->SetLineWidth(2);
  h_LowerDeltaTheta->SetLineColor(kBlue);
  h_LowerDeltaTheta->Rebin(10);
  h_LowerDeltaTheta->DrawNormalized();

  c4->cd();
  //gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h2_AbsDeltatheta_invmassJet->ProjectionX("c4xS",300,420);
  c4xS->SetTitle("ZH closestToBeam HmassWindow");
  c4xS->SetLineColor(kBlue);
  c4xS->SetLineWidth(2);
  c4xS->Rebin(10);
  c4xS->DrawNormalized();
  c5->cd();
  //gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h2_HigherDeltaTheta_invmassJet->ProjectionX("c5xS",300,420);
  c5xS->SetTitle("ZH leadingJet HmassWindow");
  c5xS->SetLineColor(kBlue);
  c5xS->SetLineWidth(2);
  c5xS->Rebin(10);
  c5xS->DrawNormalized();
  c6->cd();
  //gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h2_LowerDeltaTheta_invmassJet->ProjectionX("c6xS",300,420);
  c6xS->SetTitle("ZH secondLeadingJet HmassWindow");
  c6xS->SetLineWidth(2);
  c6xS->SetLineColor(kBlue);
  c6xS->Rebin(10);
  c6xS->DrawNormalized();

  c7->cd();
  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetPtAsymmetryGeneral->Rebin(10);
  h_jetPtAsymmetryGeneral->SetTitle("ZH jetPtAsymmetry");
  h_jetPtAsymmetryGeneral->SetLineColor(kBlue);
  h_jetPtAsymmetryGeneral->SetLineWidth(2);
  h_jetPtAsymmetryGeneral->DrawNormalized();

  c8->cd();
  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h2_jetPtAsymmetry_invmassJet->ProjectionX("AsxS",300,420);
  AsxS->Rebin(10);
  AsxS->SetTitle("ZH jetPtAsymmetry HmassWindow");
  AsxS->SetLineColor(kBlue);
  AsxS->SetLineWidth(2);
  AsxS->DrawNormalized();


//   TFile *_file0 = TFile::Open("./ZH_channel/ZH_channel_Zbb/ZH_channel_v2_Zbb_noBoost.root");
//   TFile *_file0 = TFile::Open("./ZH_channel/ZH_channel_Zbb/ZH_channel_v2_Zbb_Boost55.root");
//   TFile *_file0 = TFile::Open("./ZH_channel/ZH_channel_Zbb/ZH_channel_v2_Zbb_Boost120.root");
//   TFile *_file0 = TFile::Open("./ZH_channel/ZH_channel_Zbb/ZH_channel_v2_Zbb_Boost120_test.root");
  TFile *_file0 = TFile::Open("./ZH_channel/ZH_channel_Zbb/ZH_channel_v9_Zbb_Boost155_test.root");
//   TFile *_file0 = TFile::Open("./ZH_channel/ZH_channel_Zbb/ZH_channel_v2_Zbb_Boost100.root");
//    TFile *_file0 = TFile::Open("./ZH_channel/ZH_channel_Zbb/ZH_channel_v2_Zbb_noBoost_test.root");
//   TFile *_file0 = TFile::Open("./ZH_channel/ZH_channel_Zbb/ZH_channel_v2_Zbb_noBoost_test2.root");
  //  ZHchannel.cd();
  gDirectory->cd("ZHchannel");
  c1->cd();
  h_deltaTheta->SetTitle("Zg closestToBeam");
  h_deltaTheta->SetLineWidth(2);
  h_deltaTheta->Rebin(10);
  h_deltaTheta->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kWhite);
  //  Legend->SetFillStyle(3002);
  c2->cd();
  h_HigherDeltaTheta->SetTitle("Zg leadingJet");
  h_HigherDeltaTheta->SetLineWidth(2);
  h_HigherDeltaTheta->Rebin(10);
  h_HigherDeltaTheta->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kWhite);
  //  Legend->SetFillStyle(3002);
  c3->cd();
  h_LowerDeltaTheta->SetTitle("Zg secondLeadingJet");
  h_LowerDeltaTheta->SetLineWidth(2);
  h_LowerDeltaTheta->Rebin(10);
  h_LowerDeltaTheta->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kWhite);
  //  Legend->SetFillStyle(3002);

  h2_AbsDeltatheta_invmassJet->ProjectionX("c4x",300,420);
  c4->cd();
  c4x->SetTitle("Zg closestToBeam HmassWindow");
  c4x->Rebin(10);
  c4x->SetLineWidth(2);
  c4x->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kWhite);
  //  Legend->SetFillStyle(3002);
  c5->cd();
  h2_HigherDeltaTheta_invmassJet->ProjectionX("c5x",300,420);
  c5x->SetTitle("Zg leadingJet HmassWindow");
  c5x->Rebin(10);
  c5x->SetLineWidth(2);
  c5x->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kWhite);
  //  Legend->SetFillStyle(3002);
  c6->cd();
  h2_LowerDeltaTheta_invmassJet->ProjectionX("c6x",300,420);
  c6x->SetTitle("Zg secondLeadingJet HmassWindow");
  c6x->Rebin(10);
  c6x->SetLineWidth(2);
  c6x->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kWhite);
  //  Legend->SetFillStyle(3002);

  c7->cd();
  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetPtAsymmetryGeneral->Rebin(10);
  h_jetPtAsymmetryGeneral->SetTitle("ZH jetPtAsymmetry");
  h_jetPtAsymmetryGeneral->SetLineWidth(2);
  h_jetPtAsymmetryGeneral->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kWhite);
  //  Legend->SetFillStyle(3002);

  c8->cd();
  gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h2_jetPtAsymmetry_invmassJet->ProjectionX("Asx",300,420);
  Asx->Rebin(10);
  Asx->SetLineWidth(2);
  Asx->SetTitle("ZH jetPtAsymmetry HmassWindow");
  Asx->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kWhite);
  //  Legend->SetFillStyle(3002);



//   TFile *_file0 = TFile::Open("ZH_noBoost.root");
//   ZHchannel.cd();
//   c1->cd();
//   h2_AbsDeltatheta_invmassJet->ProjectionX("c1xS",300,420);
//   c1xS->Rebin(10);
//   c1xS->DrawNormalized("same");
//   c2->cd();
//   h2_LowerDeltaTheta_invmassJet->ProjectionX("c2xS",300,420);
//   c2xS->Rebin(10);
//   c2xS->DrawNormalized("same");
//   c3->cd();
//   h2_HigherDeltaTheta_invmassJet->ProjectionX("c3xS",300,420);
//   c3xS->Rebin(10);
//   c3xS->DrawNormalized("same");

// h_jetPtAsymmetryGeneral->DrawNormalized();
//   TFile *_file0 = TFile::Open("ZH_noBoost.root");
//   ZHchannel.cd();
//   h_jetPtAsymmetryGeneral->DrawNormalized("same");
//   TFile *_file0 = TFile::Open("../../ZH_channel/ZH_channel_Zbb/ZH_channel_v2_Zbb.root");
//   ZHchannel.cd();
//   h_jetPtAsymmetryGeneral->DrawNormalized("same");
//   h2_jetPtAsymmetry_invmassJet->ProjectionX("Asx",300,420);
//   Asx->DrawNormalized();
//   TFile *_file0 = TFile::Open("ZH_noBoost.root");
//   ZHchannel.cd();
//   h2_jetPtAsymmetry_invmassJet->ProjectionX("AsxS",300,420);
//   AsxS->DrawNormalized("same");

// TFile *_file0 = TFile::Open("ZH_noBoost.root");
//   ZHchannel.cd();
//   h2_jetPtAsymmetry_invmassJet->ProjectionX("AsxS",300,420);
//   AsxS->DrawNormalized();

// h2_jetDeltaR_jetPtAsymmetry->Draw("COLZ");
//   gStyle->SetPalette(1);
//   h2_jetDeltaR_jetPtAsymmetry->Draw("COLZ");
//   TCanvas *c2 = new TCanvas("c2","c2",600,600);
//   TFile *_file0 = TFile::Open("../../ZH_channel/ZH_channel_Zbb/ZH_channel_v2_Zbb.root");
//   ZHchannel.cd();
//   c2->cd();
//   h2_jetDeltaR_jetPtAsymmetry->Draw("COLZ");

// TFile *_file0 = TFile::Open("ZH_channel/ZH_channel_Zbb/ZH_channel_v2_Zbb_Boost55.root");
//  ZHchannel.cd();

  return 0;
}
