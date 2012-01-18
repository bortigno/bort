#include <sampleCollection.h>
#include <iostream> 
#include <TCanvas.h>
#include <TLine.h>
#include <TRegexp.h>
#include <TLegend.h>
#include <THStack.h>
#include "setTDRStyle.C"
#include <TROOT.h>
#include "customize.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include <TH1.h>
#include <TFractionFitter.h>
#include <TFile.h>
#include "TObjArray.h"
#include "RooRealVar.h"
#include "RooArgList.h"
#include "RooFitResult.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"

using namespace RooFit;

int fittingMacroRooFit(){

  double fa = 0.46502;
  double fb = 0.53498;
  bool debug_=true;

  if(debug_)
    std::cout << "Init the sample" << std::endl;
  //  std::vector<Sample> s = Nov10thDiJetPtUpdatedSlimHistos();
  //  std::vector<Sample> s = Nov10Fall1160MTopSlimHistos();
  std::vector<Sample> s = Nov10Fall1160MTopIVFHistos();
  Sample data(1,"fake data","S1.root",0,true,1000);

  if(debug_)
    std::cout << "Init the data sample" << std::endl;
  for(size_t i=0;i< s.size();i++) if(s[i].data) {data=s[i];break;}

  if(debug_)
    std::cout << "Ls data sample" << std::endl;
  data.file()->ls(); 

  if(debug_)
    std::cout << "Init the mc sample" << std::endl;
  for(size_t i=0;i< s.size();i++) s[i].dump(1,fa,fb);

  std::vector<std::string> names;

  if(debug_)
    std::cout << "Get List of Keys" << std::endl;
  TList * subs = data.file()->GetListOfKeys();
  for(size_t i=0;i< subs->GetSize();i++)
    {
      TString nn = subs->At(i)->GetName();
      if( nn.Contains(TRegexp("Count*")) )
	continue;
      if(debug_)
	std::cout << "Get List of Keys in subdirs" << std::endl;
      TList * objs = ((TDirectoryFile *)data.file()->Get(subs->At(i)->GetName()))->GetListOfKeys();
      for(size_t j=0;j< objs->GetSize();j++)
	{
	  if(debug_)
	    std::cout << "Name = " << subs->At(i)->GetName()+std::string("/")  + objs->At(j)->GetName() << std::endl;
	  names.push_back(subs->At(i)->GetName()+std::string("/")  + objs->At(j)->GetName());
	 
	}
    }
  
  TObjArray * allMC = new TObjArray(2);
  TObjArray * allMC_MET = new TObjArray(2);
  TObjArray * allMC_MET_sig = new TObjArray(2);
  TObjArray * allMC_NumOfJets = new TObjArray(2);
  TObjArray * allMC_ZH_dPhi = new TObjArray(2);
  TObjArray * allMC_ZMass = new TObjArray(2);
  TObjArray * allMC_Jet1Pt = new TObjArray(2);
  TObjArray * allMC_HiggsPt = new TObjArray(2);
  TH1F * hd;
  TH1F * hd_MET;
  TH1F * hd_MET_sig;
  TH1F * hd_NumOfJets;
  TH1F * hd_ZH_dPhi;
  TH1F * hd_ZMass;
  TH1F * hd_Jet1Pt;
  TH1F * hd_HiggsPt;

  Options o;
  double nbin, min_bin, max_bin;
	
  for(size_t i = 0 ; i < names.size() ; i++) 
    {
      
      TString n=names[i];
      if( (!n.Contains(TRegexp("ZSVRegionHZee/SimpleJet1_ptZSVRegionHZee"))) 
	  and (!n.Contains(TRegexp("ZSVRegionHZee/MET_etZSVRegionHZee")))
	  and (!n.Contains(TRegexp("ZSVRegionHZee/MET_sigZSVRegionHZee")))
	  and (!n.Contains(TRegexp("ZSVRegionHZee/NumOfJetsZSVRegionHZee")))
	  and (!n.Contains(TRegexp("ZSVRegionHZee/ZH_dPhiZSVRegionHZee")))
	  and (!n.Contains(TRegexp("ZSVRegionHZee/ZMassZSVRegionHZee")))
	  and (!n.Contains(TRegexp("ZSVRegionHZee/HiggsPtZSVRegionHZee")))    ) continue;

      if(n.Contains(TRegexp("ZSVRegionHZee/ZMassZSVRegionHZee")))
	hd_ZMass = ((TH1F*)data.file()->Get(names[i].c_str()));
      else if(n.Contains(TRegexp("ZSVRegionHZee/ZH_dPhiZSVRegionHZee")))
	hd_ZH_dPhi = ((TH1F*)data.file()->Get(names[i].c_str()));
      else if(n.Contains(TRegexp("ZSVRegionHZee/NumOfJetsZSVRegionHZee")))
	hd_NumOfJets = ((TH1F*)data.file()->Get(names[i].c_str()));
      else if(n.Contains(TRegexp("ZSVRegionHZee/HiggsPtZSVRegionHZee")))
	hd_HiggsPt = ((TH1F*)data.file()->Get(names[i].c_str()));
      else if(n.Contains(TRegexp("ZSVRegionHZee/SimpleJet1_ptZSVRegionHZee")))
	hd_Jet1Pt = ((TH1F*)data.file()->Get(names[i].c_str()));
      else if(n.Contains(TRegexp("ZSVRegionHZee/MET_sigZSVRegionHZee")))
	hd_MET_sig = ((TH1F*)data.file()->Get(names[i].c_str()));
      else if(n.Contains(TRegexp("ZSVRegionHZee/MET_etZSVRegionHZee"))){
	hd_MET = ((TH1F*)data.file()->Get(names[i].c_str()));
	hd = ((TH1F*)data.file()->Get(names[i].c_str()));
	hd->Sumw2();
	o=options[names[i]];
	hd->SetMarkerStyle(20);
	hd->GetXaxis()->SetLabelOffset(99);
	hd->SetYTitle(o.yaxis.c_str());
	hd->Draw();
	nbin = hd->GetNbinsX();
	min_bin = hd->GetXaxis()->GetXmin();
	max_bin = hd->GetXaxis()->GetXmax();

      }

      TLegend * l = new TLegend(o.legendx1,o.legendy1,o.legendx2,o.legendy2); //0.7,0.1,0.9,0.6);
      l->SetFillColor(kWhite);
      l->SetBorderSize(0);
      l->SetTextFont(62);
      l->SetTextSize(0.03);
      if(debug_)
	std::cout << "Adding data to the legend" << std::endl;  
      l->AddEntry(hd, "Data","P");
      if(debug_)
	std::cout << "Adding MC to the THStack" << std::endl;  

      //with the proper trigger eff
      double SF[] = {1.03,1.054,1.032};
            
      for(size_t j=0;j< s.size() ;j++) 
	{ 
	  TString sampleName=s[j].name;
	  if((!sampleName.Contains(TRegexp("DYB"))) and (!sampleName.Contains(TRegexp("TTbar")))) continue;

	  if(!s[j].data) 
	    {
	      if(debug_)
		std::cout << "Creating TH1F from file " << s[j].name << std::endl;  
	      TH1F * h = ((TH1F*)s[j].file()->Get(names[i].c_str()));
	      h->Sumw2();
	      if(debug_){
		std::cout << "TH1F created from file " << s[j].name << std::endl;  
		std::cout << "Scaling : " << s[j].scale(data.lumi(),fa,fb) << std::endl;  
		std::cout << "Scaling with SF : " << s[j].scale(data.lumi(),fa,fb,SF) << std::endl;  
		std::cout << "Histo integral before scaling = " << h->Integral() << std::endl;
	      }
	      h->Scale(s[j].scale(data.lumi(),fa,fb,SF));
	      if(debug_){
		std::cout << "Histo integral after scaling = " << h->Integral() << std::endl;
		std::cout << "Managing style... " << std::endl;  
	      }
	      h->SetLineWidth(1.);
	      h->SetFillColor(s[j].color);
	      h->SetLineColor(s[j].color);

	      std::cout << "Sample : " << s[j].name << " - Integral for plot " << names[i] << " = " << h->Integral(-10000,10000) << std::endl;

	      //for the fit
	      if(n.Contains(TRegexp("ZSVRegionHZee/ZMassZSVRegionHZee")))
		allMC_ZMass->Add(h);
	      if(n.Contains(TRegexp("ZSVRegionHZee/ZH_dPhiZSVRegionHZee")))
		allMC_ZH_dPhi->Add(h);
	      if(n.Contains(TRegexp("ZSVRegionHZee/NumOfJetsZSVRegionHZee")))
		allMC_NumOfJets->Add(h);
	      if(n.Contains(TRegexp("ZSVRegionHZee/HiggsPtZSVRegionHZee")))
		allMC_HiggsPt->Add(h);
	      if(n.Contains(TRegexp("ZSVRegionHZee/SimpleJet1_ptZSVRegionHZee")))
		allMC_Jet1Pt->Add(h);
	      if(n.Contains(TRegexp("ZSVRegionHZee/MET_sigZSVRegionHZee")))
		allMC_MET_sig->Add(h);
	      if(n.Contains(TRegexp("ZSVRegionHZee/MET_etZSVRegionHZee"))){
		allMC->Add(h);
		allMC_MET->Add(h);
	      }

	    }
	}

    }

  TFractionFitter * fit = new TFractionFitter(hd, allMC);
  fit->Constrain(1,0.,1.);
  fit->Constrain(2,0.,1.);
  fit->SetRangeX(1,100);
  Int_t status = fit->Fit();
  cout << "fit status: " << status << endl;
  if (status == 0) {                       // check on fit status
    TH1F* result = (TH1F*) fit->GetPlot();
    TH1F* component1 = (TH1F*) fit->GetMCPrediction(0);
    component1->SetFillColor(kWhite);
    TH1F* component2 = (TH1F*) fit->GetMCPrediction(1);
    component2->SetFillColor(kWhite);
    hd->Draw("Ep");
    result->Draw("same");
    TPaveText *pave = new TPaveText(0.60,0.50,0.77,0.70,"brNDC");
    pave->SetTextAlign(12);
    pave->SetLineColor(0);
    pave->SetFillColor(0);
    pave->SetShadowColor(0);
    //TText *text = pave->AddText(Form("#chi_{#nu}^{2} = %.3f, K_{s} = %.3f",histDt->Chi2Test(histCopyMC5,"UWCHI2/NDF"),histDt->KolmogorovTest(histCopyMC5))); // stat + sys
    TText *text = pave->AddText(Form("#chi_{#nu}^{2} = %.3f, K_{s} = %.3f",hd->Chi2Test(result,"UWCHI2/NDF"),hd->KolmogorovTest(result))); // stat only
    text->SetTextFont(62);
    text->SetTextSize(0.03);
    double value1,error1;
    double value2,error2;
    fit->GetResult(0, value1, error1);
    fit->GetResult(1, value2, error2);
    double chi2 = fit->GetChisquare();
    Int_t ndf = fit->GetNDF();
    double normchi2 = chi2/ndf;
    TText *textpar1 = pave->AddText(Form("Par_{1} = %.3f #pm %.3f",value1,error1)); // stat only
    textpar1->SetTextFont(62);
    textpar1->SetTextSize(0.03);
    TText *textpar2 = pave->AddText(Form("Par_{2} = %.3f #pm %.3f",value2,error2)); // stat only
    textpar2->SetTextFont(62);
    textpar2->SetTextSize(0.03);
    TText *textFit = pave->AddText(Form("#chi^{2}_{FIT}/NDF = %.3f/%i = %.3f",chi2,ndf,normchi2)); // stat only
    textFit->SetTextFont(62);
    textFit->SetTextSize(0.03);
    pave->Draw();
    component1->Draw("same HIST");
    component2->Draw("same HIST");
  }

//   //example from http://root.cern.ch/phpBB3/viewtopic.php?f=3&t=3871
  RooRealVar x2("x2","x2",0,200);
  RooDataHist dataHist("data","dataset",x2,hd);
  RooDataHist dyb("dyb","dyb",x2,(TH1F*)allMC->At(0));
  RooDataHist ttbar("ttbar","ttbar",x2,(TH1F*)allMC->At(1));
  RooRealVar c1("c1","c1",500,0,1000); //initial value and range
  RooRealVar c2("c2","c2",500,0,1000); //initial value and range

  std::cout << "RooHistPdf" << std::endl;
  //  RooHistPdf model("model","model",x2, dyb ,2);
  RooHistPdf dyb2 ("xx2","xx2",RooArgList(x2),dyb);
  RooHistPdf ttbar2 ("xxx2","xxx2",RooArgList(x2),ttbar);
  RooAddPdf model("model","model",RooArgList(dyb2,ttbar2),RooArgList(c1,c2));
  RooFitResult * r =  model.fitTo(dataHist,Save()); 
  r->Print("v");

  // Plot data and PDF overlaid
  RooPlot* xframe = x2.frame(Title("Example of composite pdf=(sig1+sig2)+bkg")) ;
  dataHist.plotOn(xframe) ;
  model.plotOn(xframe) ;
  // Overlay the background component of model with a dashed line
  //  model.plotOn(xframe,Components(bkg),LineStyle(kDashed)) ;
  // Overlay the background+sig2 components of model with a dotted line
  //  model.plotOn(xframe,Components(RooArgSet(dyb2,ttbar2)),LineStyle(kDotted)) ;
  model.plotOn(xframe,Components(dyb2),LineColor(kRed),LineStyle(kDotted)) ;
  model.plotOn(xframe,Components(ttbar2),LineColor(kGreen),LineStyle(kDotted)) ;
  new TCanvas("rf201_composite","rf201_composite",600,600) ;
  gPad->SetLeftMargin(0.15) ; xframe->GetYaxis()->SetTitleOffset(1.4) ; xframe->Draw() ;


  //Simultaneous fit 
  RooRealVar f_dyb("f_dyb","f_dyb",500,0,1000); //initial value and range
  RooRealVar f_ttbar("f_ttbar","f_ttbar",500,0,1000); //initial value and range
  //MET
  RooRealVar MET("MET","MET",0,200);
  RooDataHist data_MET("data_MET","data_MET",MET,hd_MET);
  RooDataHist dyb_MET("dyb_MET","dyb_MET",MET,(TH1F*)allMC_MET->At(0));
  RooDataHist ttbar_MET("ttbar_MET","ttbar_MET",MET,(TH1F*)allMC_MET->At(1));
  RooHistPdf pdf_dyb_MET ("pdf_dyb_MET","pdf_dyb_MET",RooArgList(MET),dyb_MET);
  RooHistPdf pdf_ttbar_MET ("pdf_ttbar_MET","pdf_ttbar_MET",RooArgList(MET),ttbar_MET);
  RooAddPdf model_MET("model_MET","model_MET",RooArgList(pdf_dyb_MET,pdf_ttbar_MET),RooArgList(f_dyb,f_ttbar));
  //MET_sig
  RooRealVar MET_sig("MET_sig","MET_sig",0,50);
  RooDataHist data_MET_sig("data_MET_sig","data_MET_sig",MET_sig,hd_MET_sig);
  RooDataHist dyb_MET_sig("dyb_MET_sig","dyb_MET_sig",MET_sig,(TH1F*)allMC_MET_sig->At(0));
  RooDataHist ttbar_MET_sig("ttbar_MET_sig","ttbar_MET_sig",MET_sig,(TH1F*)allMC_MET_sig->At(1));
  RooHistPdf pdf_dyb_MET_sig ("pdf_dyb_MET_sig","pdf_dyb_MET_sig",RooArgList(MET_sig),dyb_MET_sig);
  RooHistPdf pdf_ttbar_MET_sig ("pdf_ttbar_MET_sig","pdf_ttbar_MET_sig",RooArgList(MET_sig),ttbar_MET_sig);
  RooAddPdf model_MET_sig("model_MET_sig","model_MET_sig",RooArgList(pdf_dyb_MET_sig,pdf_ttbar_MET_sig),RooArgList(f_dyb,f_ttbar));
  //Jet1Pt
  RooRealVar Jet1Pt("Jet1Pt","Jet1Pt",0,300);
  RooDataHist data_Jet1Pt("data_Jet1Pt","data_Jet1Pt",Jet1Pt,hd_Jet1Pt);
  RooDataHist dyb_Jet1Pt("dyb_Jet1Pt","dyb_Jet1Pt",Jet1Pt,(TH1F*)allMC_Jet1Pt->At(0));
  RooDataHist ttbar_Jet1Pt("ttbar_Jet1Pt","ttbar_Jet1Pt",Jet1Pt,(TH1F*)allMC_Jet1Pt->At(1));
  RooHistPdf pdf_dyb_Jet1Pt ("pdf_dyb_Jet1Pt","pdf_dyb_Jet1Pt",RooArgList(Jet1Pt),dyb_Jet1Pt);
  RooHistPdf pdf_ttbar_Jet1Pt ("pdf_ttbar_Jet1Pt","pdf_ttbar_Jet1Pt",RooArgList(Jet1Pt),ttbar_Jet1Pt);
  RooAddPdf model_Jet1Pt("model_Jet1Pt","model_Jet1Pt",RooArgList(pdf_dyb_Jet1Pt,pdf_ttbar_Jet1Pt),RooArgList(f_dyb,f_ttbar));
  //HiggsPt
  RooRealVar HiggsPt("HiggsPt","HiggsPt",0,400);
  RooDataHist data_HiggsPt("data_HiggsPt","data_HiggsPt",HiggsPt,hd_HiggsPt);
  RooDataHist dyb_HiggsPt("dyb_HiggsPt","dyb_HiggsPt",HiggsPt,(TH1F*)allMC_HiggsPt->At(0));
  RooDataHist ttbar_HiggsPt("ttbar_HiggsPt","ttbar_HiggsPt",HiggsPt,(TH1F*)allMC_HiggsPt->At(1));
  RooHistPdf pdf_dyb_HiggsPt ("pdf_dyb_HiggsPt","pdf_dyb_HiggsPt",RooArgList(HiggsPt),dyb_HiggsPt);
  RooHistPdf pdf_ttbar_HiggsPt ("pdf_ttbar_HiggsPt","pdf_ttbar_HiggsPt",RooArgList(HiggsPt),ttbar_HiggsPt);
  RooAddPdf model_HiggsPt("model_HiggsPt","model_HiggsPt",RooArgList(pdf_dyb_HiggsPt,pdf_ttbar_HiggsPt),RooArgList(f_dyb,f_ttbar));
  //NumOfJets
  RooRealVar NumOfJets("NumOfJets","NumOfJets",0,10);
  RooDataHist data_NumOfJets("data_NumOfJets","data_NumOfJets",NumOfJets,hd_NumOfJets);
  RooDataHist dyb_NumOfJets("dyb_NumOfJets","dyb_NumOfJets",NumOfJets,(TH1F*)allMC_NumOfJets->At(0));
  RooDataHist ttbar_NumOfJets("ttbar_NumOfJets","ttbar_NumOfJets",NumOfJets,(TH1F*)allMC_NumOfJets->At(1));
  RooHistPdf pdf_dyb_NumOfJets ("pdf_dyb_NumOfJets","pdf_dyb_NumOfJets",RooArgList(NumOfJets),dyb_NumOfJets);
  RooHistPdf pdf_ttbar_NumOfJets ("pdf_ttbar_NumOfJets","pdf_ttbar_NumOfJets",RooArgList(NumOfJets),ttbar_NumOfJets);
  RooAddPdf model_NumOfJets("model_NumOfJets","model_NumOfJets",RooArgList(pdf_dyb_NumOfJets,pdf_ttbar_NumOfJets),RooArgList(f_dyb,f_ttbar));
  //ZH_dPhi
  RooRealVar ZH_dPhi("ZH_dPhi","ZH_dPhi",0,3.2);
  RooDataHist data_ZH_dPhi("data_ZH_dPhi","data_ZH_dPhi",ZH_dPhi,hd_ZH_dPhi);
  RooDataHist dyb_ZH_dPhi("dyb_ZH_dPhi","dyb_ZH_dPhi",ZH_dPhi,(TH1F*)allMC_ZH_dPhi->At(0));
  RooDataHist ttbar_ZH_dPhi("ttbar_ZH_dPhi","ttbar_ZH_dPhi",ZH_dPhi,(TH1F*)allMC_ZH_dPhi->At(1));
  RooHistPdf pdf_dyb_ZH_dPhi ("pdf_dyb_ZH_dPhi","pdf_dyb_ZH_dPhi",RooArgList(ZH_dPhi),dyb_ZH_dPhi);
  RooHistPdf pdf_ttbar_ZH_dPhi ("pdf_ttbar_ZH_dPhi","pdf_ttbar_ZH_dPhi",RooArgList(ZH_dPhi),ttbar_ZH_dPhi);
  RooAddPdf model_ZH_dPhi("model_ZH_dPhi","model_ZH_dPhi",RooArgList(pdf_dyb_ZH_dPhi,pdf_ttbar_ZH_dPhi),RooArgList(f_dyb,f_ttbar));
  //ZMass
  RooRealVar ZMass("ZMass","ZMass",75,105);
  RooDataHist data_ZMass("data_ZMass","data_ZMass",ZMass,hd_ZMass);
  RooDataHist dyb_ZMass("dyb_ZMass","dyb_ZMass",ZMass,(TH1F*)allMC_ZMass->At(0));
  RooDataHist ttbar_ZMass("ttbar_ZMass","ttbar_ZMass",ZMass,(TH1F*)allMC_ZMass->At(1));
  RooHistPdf pdf_dyb_ZMass ("pdf_dyb_ZMass","pdf_dyb_ZMass",RooArgList(ZMass),dyb_ZMass);
  RooHistPdf pdf_ttbar_ZMass ("pdf_ttbar_ZMass","pdf_ttbar_ZMass",RooArgList(ZMass),ttbar_ZMass);
  RooAddPdf model_ZMass("model_ZMass","model_ZMass",RooArgList(pdf_dyb_ZMass,pdf_ttbar_ZMass),RooArgList(f_dyb,f_ttbar));


  RooCategory varToFit("varToFit","varToFit");
  varToFit.defineType("MET");
  //  varToFit.defineType("MET_sig");
  //  varToFit.defineType("Jet1Pt");
  varToFit.defineType("HiggsPt");
  varToFit.defineType("NumOfJets");
  //  varToFit.defineType("ZH_dPhi");
  //  varToFit.defineType("ZMass");
  //   RooDataSet dataCat("dataCat","dataCat",RooArgSet(x2,tp));
  //   RooDataHist combData("combData","combined data",RooArgSet(MET,Jet1Pt),Index(varToFit),Import("MET",data_MET),Import("Jet1Pt",data_Jet1Pt)) ;
  //  RooDataHist combData("combData","combined data",RooArgSet(MET,Jet1Pt,HiggsPt),Index(varToFit),Import("MET",data_MET),Import("Jet1Pt",data_Jet1Pt),Import("HiggsPt",data_HiggsPt)) ;
  RooDataHist combData("combData","combined data",
		       RooArgSet(MET,NumOfJets,HiggsPt),
		       Index(varToFit),
		       Import("MET",data_MET),
 		       Import("HiggsPt",data_HiggsPt),
		       Import("NumOfJets",data_NumOfJets));
		       //		       Import("ZH_dPhi",data_ZH_dPhi));
//   RooDataHist combData("combData","combined data",
// 		       RooArgSet(MET,MET_sig,Jet1Pt,HiggsPt,NumOfJets,ZH_dPhi,ZMass),
// 		       Index(varToFit),
// 		       Import("MET",data_MET),
// 		       Import("MET_sig",data_MET_sig),
// 		       Import("Jet1Pt",data_Jet1Pt),
// 		       Import("HiggsPt",data_HiggsPt),
// 		       Import("NumOfJets",data_NumOfJets),
// 		       Import("ZH_dPhi",data_ZH_dPhi),
// 		       Import("ZMass",data_ZMass) ) ;
  RooSimultaneous simPdf("simPdf","simPdf",varToFit);
  simPdf.addPdf(model_MET,"MET"); 
  //  simPdf.addPdf(model_MET_sig,"MET_sig"); 
//   simPdf.addPdf(model_Jet1Pt,"Jet1Pt"); 
  simPdf.addPdf(model_HiggsPt,"HiggsPt"); 
  simPdf.addPdf(model_NumOfJets,"NumOfJets"); 
  //  simPdf.addPdf(model_ZH_dPhi,"ZH_dPhi"); 
  //  simPdf.addPdf(model_ZMass,"ZMass"); 
  RooFitResult * fitRes = simPdf.fitTo(combData);


  // Plot data and PDF overlaid
  RooPlot* MET_frame = MET.frame(Title("Missing Et")) ;
  data_MET.plotOn(MET_frame) ;
  model_MET.plotOn(MET_frame) ;
  model_MET.plotOn(MET_frame,Components(pdf_dyb_MET),LineColor(kRed),LineStyle(kDotted)) ;
  model_MET.plotOn(MET_frame,Components(pdf_ttbar_MET),LineColor(kGreen),LineStyle(kDotted)) ;
  new TCanvas("MET fit","MET_fit",600,600) ;
  gPad->SetLeftMargin(0.15) ; MET_frame->GetYaxis()->SetTitleOffset(1.4) ; MET_frame->Draw() ;

//   // Plot data and PDF overlaid
//   RooPlot* MET_sig_frame = MET_sig.frame(Title("Missing Et")) ;
//   data_MET_sig.plotOn(MET_sig_frame) ;
//   model_MET_sig.plotOn(MET_sig_frame) ;
//   model_MET_sig.plotOn(MET_sig_frame,Components(pdf_dyb_MET_sig),LineColor(kRed),LineStyle(kDotted)) ;
//   model_MET_sig.plotOn(MET_sig_frame,Components(pdf_ttbar_MET_sig),LineColor(kGreen),LineStyle(kDotted)) ;
//   new TCanvas("MET_sig fit","MET_sig_fit",600,600) ;
//   gPad->SetLeftMargin(0.15) ; MET_sig_frame->GetYaxis()->SetTitleOffset(1.4) ; MET_sig_frame->Draw() ;

//   // Plot data and PDF overlaid
//   RooPlot* Jet1Pt_frame = Jet1Pt.frame(Title("Leading Jet Pt")) ;
//   data_Jet1Pt.plotOn(Jet1Pt_frame) ;
//   model_Jet1Pt.plotOn(Jet1Pt_frame) ;
//   model_Jet1Pt.plotOn(Jet1Pt_frame,Components(pdf_dyb_Jet1Pt),LineColor(kRed),LineStyle(kDotted)) ;
//   model_Jet1Pt.plotOn(Jet1Pt_frame,Components(pdf_ttbar_Jet1Pt),LineColor(kGreen),LineStyle(kDotted)) ;
//   new TCanvas("Jet1Pt fit","Jet1Pt_fit",600,600) ;
//   gPad->SetLeftMargin(0.15) ; Jet1Pt_frame->GetYaxis()->SetTitleOffset(1.4) ; Jet1Pt_frame->Draw() ;

  // Plot data and PDF overlaid
  RooPlot* HiggsPt_frame = HiggsPt.frame(Title("Higgs Pt")) ;
  data_HiggsPt.plotOn(HiggsPt_frame) ;
  model_HiggsPt.plotOn(HiggsPt_frame) ;
  model_HiggsPt.plotOn(HiggsPt_frame,Components(pdf_dyb_HiggsPt),LineColor(kRed),LineStyle(kDotted)) ;
  model_HiggsPt.plotOn(HiggsPt_frame,Components(pdf_ttbar_HiggsPt),LineColor(kGreen),LineStyle(kDotted)) ;
  new TCanvas("HiggsPt fit","HiggsPt_fit",600,600) ;
  gPad->SetLeftMargin(0.15) ; HiggsPt_frame->GetYaxis()->SetTitleOffset(1.4) ; HiggsPt_frame->Draw() ;

  // Plot data and PDF overlaid
  RooPlot* NumOfJets_frame = NumOfJets.frame(Title("Missing Et")) ;
  data_NumOfJets.plotOn(NumOfJets_frame) ;
  model_NumOfJets.plotOn(NumOfJets_frame) ;
  model_NumOfJets.plotOn(NumOfJets_frame,Components(pdf_dyb_NumOfJets),LineColor(kRed),LineStyle(kDotted)) ;
  model_NumOfJets.plotOn(NumOfJets_frame,Components(pdf_ttbar_NumOfJets),LineColor(kGreen),LineStyle(kDotted)) ;
  new TCanvas("NumOfJets fit","NumOfJets_fit",600,600) ;
  gPad->SetLeftMargin(0.15) ; NumOfJets_frame->GetYaxis()->SetTitleOffset(1.4) ; NumOfJets_frame->Draw() ;

//   // Plot data and PDF overlaid
//   RooPlot* ZH_dPhi_frame = ZH_dPhi.frame(Title("Missing Et")) ;
//   data_ZH_dPhi.plotOn(ZH_dPhi_frame) ;
//   model_ZH_dPhi.plotOn(ZH_dPhi_frame) ;
//   model_ZH_dPhi.plotOn(ZH_dPhi_frame,Components(pdf_dyb_ZH_dPhi),LineColor(kRed),LineStyle(kDotted)) ;
//   model_ZH_dPhi.plotOn(ZH_dPhi_frame,Components(pdf_ttbar_ZH_dPhi),LineColor(kGreen),LineStyle(kDotted)) ;
//   new TCanvas("ZH_dPhi fit","ZH_dPhi_fit",600,600) ;
//   gPad->SetLeftMargin(0.15) ; ZH_dPhi_frame->GetYaxis()->SetTitleOffset(1.4) ; ZH_dPhi_frame->Draw() ;

//   // Plot data and PDF overlaid
//   RooPlot* ZMass_frame = ZMass.frame(Title("Missing Et")) ;
//   data_ZMass.plotOn(ZMass_frame) ;
//   model_ZMass.plotOn(ZMass_frame) ;
//   model_ZMass.plotOn(ZMass_frame,Components(pdf_dyb_ZMass),LineColor(kRed),LineStyle(kDotted)) ;
//   model_ZMass.plotOn(ZMass_frame,Components(pdf_ttbar_ZMass),LineColor(kGreen),LineStyle(kDotted)) ;
//   new TCanvas("ZMass fit","ZMass_fit",600,600) ;
//   gPad->SetLeftMargin(0.15) ; ZMass_frame->GetYaxis()->SetTitleOffset(1.4) ; ZMass_frame->Draw() ;



  //  fitRes->Print();
  //  fitRes->Print("v");

  return 0;
}
