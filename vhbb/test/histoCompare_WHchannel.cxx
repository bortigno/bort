#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
//#include <TPad.h>

int histoCompare_WHchannel( char * IVF_file ){

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);

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
//   TCanvas * c11 = new TCanvas("c11","c11", 600, 600);
//   TCanvas * c12 = new TCanvas("c12","c12", 600, 600);
//   TCanvas * c13 = new TCanvas("c13","c13", 600, 600);
//   TCanvas * c14 = new TCanvas("c14","c14", 600, 600);
//   TCanvas * c15 = new TCanvas("c15","c15", 600, 600);
//   TCanvas * c16 = new TCanvas("c16","c16", 600, 600);
//   TCanvas * c17 = new TCanvas("c17","c17", 600, 600);

//  TFile::Open("./WH_channel/WH_channel_signal/res/WH_channel_signal.root");
   TFile::Open("./WH_channel/WH_channel_signal/res/WH_channel_signal.root");

  //Tagger : combinedSecondaryVertexBJetTags

  gDirectory->cd("WHchannel");

  c0->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_Wcandidate_mass->SetTitle("Z candidate mass");
  h_Wcandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_Wcandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_Wcandidate_mass->GetXaxis()->SetRangeUser(70,110);
  h_Wcandidate_mass->SetMarkerStyle(21);
  h_Wcandidate_mass->SetFillColor(kCyan);
  h_Wcandidate_mass->SetFillStyle(3002);
  h_Wcandidate_mass->SetMarkerColor(kBlack);
  h_Wcandidate_mass->DrawNormalized();

  c1->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_higgsCandidate_mass->SetTitle("higgs candidate mass");
  h_higgsCandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->Rebin(8);
  h_higgsCandidate_mass->SetMarkerStyle(21);
  h_higgsCandidate_mass->SetFillColor(kCyan);
  h_higgsCandidate_mass->SetFillStyle(3002);
  h_higgsCandidate_mass->SetMarkerColor(kBlack);
  h_higgsCandidate_mass->DrawNormalized();

  c2->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h_alphaAngleGeneral->SetTitle("#alpha angle general");
  h_alphaAngleGeneral->GetYaxis()->SetTitle("#alpha angle");
  h_alphaAngleGeneral->GetYaxis()->SetLabelSize(0.03);
  h_alphaAngleGeneral->GetXaxis()->SetLabelSize(0.03);
  h_alphaAngleGeneral->GetXaxis()->SetRangeUser(-0.1,4);
  h_alphaAngleGeneral->SetMarkerStyle(21);
  h_alphaAngleGeneral->SetFillColor(kCyan);
  h_alphaAngleGeneral->SetFillStyle(3002);
  h_alphaAngleGeneral->SetMarkerColor(kBlack);
  h_alphaAngleGeneral->DrawNormalized();

  c3->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_betaDistanceGeneral->SetTitle("#beta distance general");
  h_betaDistanceGeneral->GetYaxis()->SetTitle("#beta distance");
  h_betaDistanceGeneral->GetYaxis()->SetLabelSize(0.03);
  h_betaDistanceGeneral->GetXaxis()->SetLabelSize(0.03);
  h_betaDistanceGeneral->GetXaxis()->SetRangeUser(-4,3);
  h_betaDistanceGeneral->SetMarkerStyle(21);
  h_betaDistanceGeneral->SetFillColor(kCyan);
  h_betaDistanceGeneral->SetFillStyle(3002);
  h_betaDistanceGeneral->SetMarkerColor(kBlack);
  h_betaDistanceGeneral->DrawNormalized();

 //  //Cambio Tagger: simpleSecondaryVertexHighEffBJetTags

//   gDirectory->cd("../JetTag_simpleSecondaryVertexHighEffBJetTags_GLOBAL");
 
  c4->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_gammaDeltaRGeneral->SetTitle("#gamma #Delta R general");
  h_gammaDeltaRGeneral->GetYaxis()->SetLabelSize(0.03);
  h_gammaDeltaRGeneral->GetXaxis()->SetLabelSize(0.03);
  h_gammaDeltaRGeneral->GetXaxis()->SetRangeUser(0,5);
  h_gammaDeltaRGeneral->SetMarkerStyle(21);
  h_gammaDeltaRGeneral->SetFillColor(kCyan);
  h_gammaDeltaRGeneral->SetFillStyle(3002);
  h_gammaDeltaRGeneral->SetMarkerColor(kBlack);
  h_gammaDeltaRGeneral->DrawNormalized();

  c5->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_deltaEtaBJetGeneral->SetTitle("#Delta #eta B jet general");
  h_deltaEtaBJetGeneral->GetYaxis()->SetLabelSize(0.03);
  h_deltaEtaBJetGeneral->GetXaxis()->SetLabelSize(0.03);
  h_deltaEtaBJetGeneral->GetXaxis()->SetRangeUser(-0.1,3);
  h_deltaEtaBJetGeneral->SetMarkerStyle(21);
  h_deltaEtaBJetGeneral->SetFillColor(kCyan);
  h_deltaEtaBJetGeneral->SetFillStyle(3002);
  h_deltaEtaBJetGeneral->SetMarkerColor(kBlack);
  h_deltaEtaBJetGeneral->DrawNormalized();

  c6->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h_epsilonDeltaEtaGeneral->SetTitle("#epsilon #Delta #eta general");
  h_epsilonDeltaEtaGeneral->GetYaxis()->SetTitle("#Delta #eta");
  h_epsilonDeltaEtaGeneral->GetYaxis()->SetLabelSize(0.03);
  h_epsilonDeltaEtaGeneral->GetXaxis()->SetLabelSize(0.03);
  h_epsilonDeltaEtaGeneral->SetMarkerStyle(21);
  h_epsilonDeltaEtaGeneral->SetFillColor(kCyan);
  h_epsilonDeltaEtaGeneral->SetFillStyle(3002);
  h_epsilonDeltaEtaGeneral->SetMarkerColor(kBlack);
  h_epsilonDeltaEtaGeneral->DrawNormalized();

  c7->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_digammaDeltaThetaGeneral->SetTitle("#digamma #Delta #theta general");
  h_digammaDeltaThetaGeneral->GetYaxis()->SetTitle("#Delta #theta");
  h_digammaDeltaThetaGeneral->GetYaxis()->SetLabelSize(0.03);
  h_digammaDeltaThetaGeneral->GetXaxis()->SetLabelSize(0.03);
  h_digammaDeltaThetaGeneral->SetMarkerStyle(21);
  h_digammaDeltaThetaGeneral->SetFillColor(kCyan);
  h_digammaDeltaThetaGeneral->SetFillStyle(3002);
  h_digammaDeltaThetaGeneral->SetMarkerColor(kBlack);
  h_digammaDeltaThetaGeneral->DrawNormalized();


//   //Tagger : combinedSecondaryVertexMVABJetTags
//   gDirectory->cd("../JetTag_combinedSecondaryVertexMVABJetTags_GLOBAL");

  c8->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaEtaGeneral->SetTitle("Jet #Delta #eta general");
  h_jetDeltaEtaGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->GetXaxis()->SetRangeUser(-0.1,3);
  h_jetDeltaEtaGeneral->SetMarkerStyle(21);
  h_jetDeltaEtaGeneral->SetFillColor(kCyan);
  h_jetDeltaEtaGeneral->SetFillStyle(3002);
  h_jetDeltaEtaGeneral->SetMarkerColor(kBlack);
  h_jetDeltaEtaGeneral->DrawNormalized();

  c9->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaR_general->SetTitle("Jet #Delta R general");
  h_jetDeltaR_general->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->GetXaxis()->SetRangeUser(0,5);
  h_jetDeltaR_general->SetMarkerStyle(21);
  h_jetDeltaR_general->SetFillColor(kCyan);
  h_jetDeltaR_general->SetFillStyle(3002);
  h_jetDeltaR_general->SetMarkerColor(kBlack);
  h_jetDeltaR_general->DrawNormalized();

  c10->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDistancePerpendicularLineGeneral->Rebin(4);
  h_jetDistancePerpendicularLineGeneral->SetTitle("jet dist PL general");
  h_jetDistancePerpendicularLineGeneral->GetYaxis()->SetTitle("PL dist");
  h_jetDistancePerpendicularLineGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetDistancePerpendicularLineGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetDistancePerpendicularLineGeneral->SetMarkerStyle(21);
  h_jetDistancePerpendicularLineGeneral->SetFillColor(kCyan);
  h_jetDistancePerpendicularLineGeneral->SetFillStyle(3002);
  h_jetDistancePerpendicularLineGeneral->SetMarkerColor(kBlack);
  h_jetDistancePerpendicularLineGeneral->DrawNormalized();

//   c11->cd();
//   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->SetTitle("Jet VF");
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->GetYaxis()->SetTitle("Efficiency");
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->GetYaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->GetXaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->SetMarkerStyle(21);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->SetFillColor(kYellow);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->SetFillStyle(3002);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->SetMarkerColor(kBlack);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->DrawNormalized();


//   //Tagger : simpleSecondaryVertexHighPurBJetTags

//   gDirectory->cd("../JetTag_simpleSecondaryVertexHighPurBJetTags_GLOBAL");

//   c12->cd();
//   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetTitle("Jet VF");
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->GetYaxis()->SetLabelSize(0.03);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->GetXaxis()->SetLabelSize(0.03);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetMarkerStyle(21);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetFillColor(kYellow);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetFillStyle(3002);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetMarkerColor(kBlack);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->DrawNormalized();

//   c13->cd();
//   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetTitle("Jet VF");
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->GetYaxis()->SetLabelSize(0.03);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->GetXaxis()->SetLabelSize(0.03);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetMarkerStyle(21);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetFillColor(kYellow);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetFillStyle(3002);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetMarkerColor(kBlack);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->DrawNormalized();

//   c14->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->SetTitle("Jet VF");
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->GetYaxis()->SetTitle("Efficiency");
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->GetYaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->GetXaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->SetMarkerStyle(21);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->SetFillColor(kYellow);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->SetFillStyle(3002);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->SetMarkerColor(kBlack);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->DrawNormalized();

//   c15->cd();
//   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->SetTitle("Jet VF");
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->GetYaxis()->SetTitle("Efficiency");
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->GetYaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->GetXaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->SetMarkerStyle(21);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->SetFillColor(kYellow);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->SetFillStyle(3002);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->SetMarkerColor(kBlack);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->DrawNormalized();


  //CAMBIO FILE IVF

  //  TFile::Open("./DQM_V0001_R000000001__POG__BTAG__IVF_BJET_TTbar.root");
  TFile::Open(IVF_file);
  // Tagger : combinedSecondaryVertexBJetTags

  gDirectory->cd("WHchannel");

  c0->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_Wcandidate_mass->SetTitle("Z candidate mass V+Jets");
  h_Wcandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_Wcandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_Wcandidate_mass->SetMarkerStyle(20);
  h_Wcandidate_mass->SetFillColor(kYellow);
  h_Wcandidate_mass->SetFillStyle(3002);
  h_Wcandidate_mass->SetMarkerColor(kRed);
  h_Wcandidate_mass->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.15, 0.67, 0.48, 0.88);
  Legend->SetFillColor(kYellow);
  Legend->SetFillStyle(3002);

  c1->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_higgsCandidate_mass->Rebin(8);
  h_higgsCandidate_mass->SetTitle("higgs candidate mass V+Jets");
  h_higgsCandidate_mass->GetYaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->GetXaxis()->SetLabelSize(0.03);
  h_higgsCandidate_mass->SetMarkerStyle(20);
  h_higgsCandidate_mass->SetFillColor(kYellow);
  h_higgsCandidate_mass->SetFillStyle(3002);
  h_higgsCandidate_mass->SetMarkerColor(kRed);
  h_higgsCandidate_mass->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.15, 0.67, 0.48, 0.88);
  Legend->SetFillColor(kYellow);
  Legend->SetFillStyle(3002);

  c2->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h_alphaAngleGeneral->SetTitle("#alpha angle general V+Jets");
  h_alphaAngleGeneral->GetYaxis()->SetTitle("#alpha angle");
  h_alphaAngleGeneral->GetYaxis()->SetLabelSize(0.03);
  h_alphaAngleGeneral->GetXaxis()->SetLabelSize(0.03);
  h_alphaAngleGeneral->SetMarkerStyle(20);
  h_alphaAngleGeneral->SetFillColor(kYellow);
  h_alphaAngleGeneral->SetFillStyle(3002);
  h_alphaAngleGeneral->SetMarkerColor(kRed);
  h_alphaAngleGeneral->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.15, 0.27, 0.48, 0.48);
  Legend->SetFillColor(kYellow);
  Legend->SetFillStyle(3002);

  c3->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_betaDistanceGeneral->SetTitle("#beta dist general V+Jets");
  h_betaDistanceGeneral->GetYaxis()->SetTitle("#beta distance");
  h_betaDistanceGeneral->GetYaxis()->SetLabelSize(0.03);
  h_betaDistanceGeneral->GetXaxis()->SetLabelSize(0.03);
  h_betaDistanceGeneral->SetMarkerStyle(20);
  h_betaDistanceGeneral->SetFillColor(kYellow);
  h_betaDistanceGeneral->SetFillStyle(3002);
  h_betaDistanceGeneral->SetMarkerColor(kRed);
  h_betaDistanceGeneral->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kYellow);
  Legend->SetFillStyle(3002);


//   //Cambio Tagger: simpleSecondaryVertexHighEffBJetTags

//   gDirectory->cd("../JetTag_simpleSecondaryVertexHighEffBJetTags_GLOBAL");

  c4->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_gammaDeltaRGeneral->SetTitle("#gamma #Delta R general V+Jets");
  h_gammaDeltaRGeneral->GetYaxis()->SetLabelSize(0.03);
  h_gammaDeltaRGeneral->GetXaxis()->SetLabelSize(0.03);
  h_gammaDeltaRGeneral->SetMarkerStyle(20);
  h_gammaDeltaRGeneral->SetFillColor(kYellow);
  h_gammaDeltaRGeneral->SetFillStyle(3002);
  h_gammaDeltaRGeneral->SetMarkerColor(kRed);
  h_gammaDeltaRGeneral->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.45, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kYellow);
  Legend->SetFillStyle(3002);

  c5->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_deltaEtaBJetGeneral->SetTitle("#Delta #eta B Jet general V+Jet");
  h_deltaEtaBJetGeneral->GetYaxis()->SetLabelSize(0.03);
  h_deltaEtaBJetGeneral->GetXaxis()->SetLabelSize(0.03);
  h_deltaEtaBJetGeneral->SetMarkerStyle(20);
  h_deltaEtaBJetGeneral->SetFillColor(kYellow);
  h_deltaEtaBJetGeneral->SetFillStyle(3002);
  h_deltaEtaBJetGeneral->SetMarkerColor(kRed);
  h_deltaEtaBJetGeneral->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.45, 0.27, 0.88, 0.48);
  Legend->SetFillColor(kYellow);
  Legend->SetFillStyle(3002);

  c6->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h_epsilonDeltaEtaGeneral->SetTitle("#epsilon #Delta #eta general V+Jets");
  h_epsilonDeltaEtaGeneral->GetYaxis()->SetTitle("#espilon #Delta Eta");
  h_epsilonDeltaEtaGeneral->GetYaxis()->SetLabelSize(0.03);
  h_epsilonDeltaEtaGeneral->GetXaxis()->SetLabelSize(0.03);
  h_epsilonDeltaEtaGeneral->SetMarkerStyle(20);
  h_epsilonDeltaEtaGeneral->SetFillColor(kYellow);
  h_epsilonDeltaEtaGeneral->SetFillStyle(3002);
  h_epsilonDeltaEtaGeneral->SetMarkerColor(kRed);
  h_epsilonDeltaEtaGeneral->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kYellow);
  Legend->SetFillStyle(3002);

  c7->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_digammaDeltaThetaGeneral->SetTitle("#digamma #Delta #theta general V+Jet");
  h_digammaDeltaThetaGeneral->GetYaxis()->SetTitle("#Delta #theta");
  h_digammaDeltaThetaGeneral->GetYaxis()->SetLabelSize(0.03);
  h_digammaDeltaThetaGeneral->GetXaxis()->SetLabelSize(0.03);
  h_digammaDeltaThetaGeneral->SetMarkerStyle(20);
  h_digammaDeltaThetaGeneral->SetFillColor(kYellow);
  h_digammaDeltaThetaGeneral->SetFillStyle(3002);
  h_digammaDeltaThetaGeneral->SetMarkerColor(kRed);
  h_digammaDeltaThetaGeneral->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kYellow);
  Legend->SetFillStyle(3002);

//   // Tagger : combinedSecondaryVertexMVABJetTags

//   gDirectory->cd("../JetTag_combinedSecondaryVertexMVABJetTags_GLOBAL");

  c8->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaEtaGeneral->SetTitle("jet #Delta #eta general V+Jets");
  h_jetDeltaEtaGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaEtaGeneral->SetMarkerStyle(20);
  h_jetDeltaEtaGeneral->SetFillColor(kYellow);
  h_jetDeltaEtaGeneral->SetFillStyle(3002);
  h_jetDeltaEtaGeneral->SetMarkerColor(kRed);
  h_jetDeltaEtaGeneral->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.15, 0.67, 0.48, 0.88);
  Legend->SetFillColor(kYellow);
  Legend->SetFillStyle(3002);

  c9->cd();
//   gPad->SetLogy();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDeltaR_general->SetTitle("jet #Delta R general V+Jets");
  h_jetDeltaR_general->GetYaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->GetXaxis()->SetLabelSize(0.03);
  h_jetDeltaR_general->SetMarkerStyle(20);
  h_jetDeltaR_general->SetFillColor(kYellow);
  h_jetDeltaR_general->SetFillStyle(3002);
  h_jetDeltaR_general->SetMarkerColor(kRed);
  h_jetDeltaR_general->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.15, 0.67, 0.48, 0.88);
  Legend->SetFillColor(kYellow);
  Legend->SetFillStyle(3002);

  c10->cd();
  gPad->SetGridy();
  gPad->SetGridx();
  h_jetDistancePerpendicularLineGeneral->Rebin(4);
  h_jetDistancePerpendicularLineGeneral->SetTitle("jet dist PL general V+Jets");
  h_jetDistancePerpendicularLineGeneral->GetYaxis()->SetTitle("PL dist");
  h_jetDistancePerpendicularLineGeneral->GetYaxis()->SetLabelSize(0.03);
  h_jetDistancePerpendicularLineGeneral->GetXaxis()->SetLabelSize(0.03);
  h_jetDistancePerpendicularLineGeneral->SetMarkerStyle(20);
  h_jetDistancePerpendicularLineGeneral->SetFillColor(kYellow);
  h_jetDistancePerpendicularLineGeneral->SetFillStyle(3002);
  h_jetDistancePerpendicularLineGeneral->SetMarkerColor(kRed);
  h_jetDistancePerpendicularLineGeneral->DrawNormalized("same");
  TLegend* Legend = (TLegend*)gPad->BuildLegend();
  Legend->SetFillColor(kYellow);
  Legend->SetFillStyle(3002);

//   c11->cd();
//   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->SetTitle("IVF VF");
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->GetYaxis()->SetTitle("Efficiency");
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->GetYaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->GetXaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->SetMarkerStyle(20);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->SetFillColor(kYellow);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->SetFillStyle(3002);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->SetMarkerColor(kRed);
//   effVsDiscrCut_discr_combinedSecondaryVertexMVABJetTags_GLOBALDUSG->DrawNormalized("same");
//   TLegend* Legend = (TLegend*)gPad->BuildLegend();
//   Legend->SetFillColor(kYellow);
//   Legend->SetFillStyle(3002);


//   // Tagger : simpleSecondaryVertexHighPurBJetTags

//   gDirectory->cd("../JetTag_simpleSecondaryVertexHighPurBJetTags_GLOBAL");

//   c12->cd();
//   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetTitle("IVF VF");
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->GetYaxis()->SetLabelSize(0.03);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->GetXaxis()->SetLabelSize(0.03);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetMarkerStyle(20);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetFillColor(kYellow);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetFillStyle(3002);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetMarkerColor(kRed);
//   FlavEffVsBEff_DUSG_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->DrawNormalized("same");
//   TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
//   Legend->SetFillColor(kYellow);
//   Legend->SetFillStyle(3002);

//   c13->cd();
//   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetTitle("IVF VF");
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->GetYaxis()->SetLabelSize(0.03);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->GetXaxis()->SetLabelSize(0.03);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetMarkerStyle(20);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetFillColor(kYellow);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetFillStyle(3002);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->SetMarkerColor(kRed);
//   FlavEffVsBEff_C_discr_simpleSecondaryVertexHighPurBJetTags_GLOBAL->DrawNormalized("same");
//   TLegend* Legend = (TLegend*)gPad->BuildLegend( 0.55, 0.27, 0.88, 0.48);
//   Legend->SetFillColor(kYellow);
//   Legend->SetFillStyle(3002);

//   c14->cd();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->SetTitle("IVF VF");
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->GetYaxis()->SetTitle("Efficiency");
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->GetYaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->GetXaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->SetMarkerStyle(20);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->SetFillColor(kYellow);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->SetFillStyle(3002);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->SetMarkerColor(kRed);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALB->DrawNormalized("same");
//   TLegend* Legend = (TLegend*)gPad->BuildLegend();
//   Legend->SetFillColor(kYellow);
//   Legend->SetFillStyle(3002);

//   c15->cd();
//   gPad->SetLogy();
//   gPad->SetGridy();
//   gPad->SetGridx();
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->SetTitle("IVF VF");
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->GetYaxis()->SetTitle("Efficiency");
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->GetYaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->GetXaxis()->SetLabelSize(0.03);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->SetMarkerStyle(20);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->SetFillColor(kYellow);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->SetFillStyle(3002);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->SetMarkerColor(kRed);
//   effVsDiscrCut_discr_simpleSecondaryVertexHighPurBJetTags_GLOBALDUSG->DrawNormalized("same");
//   TLegend* Legend = (TLegend*)gPad->BuildLegend();
//   Legend->SetFillColor(kYellow);
//   Legend->SetFillStyle(3002);


  return 0;

}
