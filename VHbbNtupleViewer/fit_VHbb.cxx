#include "sampleCollection.h"
#include "controlRegions.h"
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
#include "RooAbsReal.h"
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



int main(int argc, char **argv){

  using namespace RooFit;

  double fa = 0.46502;
  double fb = 0.53498;
  bool debug_=false;

  if(debug_)
    std::cout << "Init the sample" << std::endl;
 
  std::vector<Sample> s = Nov10Fall1160MTopSlimHistos();

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
  
  TObjArray * allMC_TTbarVar = new TObjArray;
  TObjArray * allMC_ZbbVar = new TObjArray;
  TObjArray * allMC_ZbbVar2 = new TObjArray;
  TObjArray * allMC_LightVar = new TObjArray;
  TH1F * hd_TTbarVar;
  TH1F * hd_ZbbVar;
  TH1F * hd_ZbbVar2;
  TH1F * hd_LightVar;

  controlRegion BDT_signalRegion(4.6,fa,fb);
  BDT_signalRegion.init();
  controlRegion BDTZlight_cr(4.6,fa,fb);
  BDTZlight_cr.init();
  controlRegion BDTTTbar_cr(4.6,fa,fb);
  BDTTTbar_cr.init();
  controlRegion BDTZbb_cr(4.6,fa,fb);
  BDTZbb_cr.init();


  Options o;
  double nbin, min_bin, max_bin;

  double ZbbVar_min = 0;
  double ZbbVar_max = 200;
  double ZbbVar2_min = 0;
  double ZbbVar2_max = 1;
  double TTbarVar_min = 0;
  double TTbarVar_max = 5;
  double LightVar_min = 0;
  double LightVar_max = 500;


  std::string s_ZlightVar = "HiggsPt"; 
  std::string s_TTbarVar = "ZH_dPhi";
  std::string s_ZbbVar = "MET_et";
  std::string s_ZbbVar2 = "SimpleJet2_bTag";

  std::string ZlightString = "BDTZlightControlRegionHZee/"+s_ZlightVar+"BDTZlightControlRegionHZee";
  std::string TTbarString = "BDTTTbarControlRegionHZee/"+s_TTbarVar+"BDTTTbarControlRegionHZee";
  std::string ZbbString = "BDTZbbControlRegionHZee/"+s_ZbbVar+"BDTZbbControlRegionHZee";
  std::string ZbbString2 = "BDTZbbControlRegionHZee/"+s_ZbbVar2+"BDTZbbControlRegionHZee";

  for(size_t i = 0 ; i < names.size() ; i++) 
    {
      
      TString n=names[i];
      if( (!n.Contains(TRegexp(ZlightString.c_str()))) 
	  and (!n.Contains(TRegexp("BDTRegionHZee")))
	  and (!n.Contains(TRegexp(ZbbString.c_str())))
 	  and (!n.Contains(TRegexp(ZbbString2.c_str())))
	  and (!n.Contains(TRegexp(TTbarString.c_str())))    ) continue;

      if(n.Contains(TRegexp(ZlightString.c_str())))
	hd_LightVar = ((TH1F*)data.file()->Get(names[i].c_str()));
      else if(n.Contains(TRegexp(ZbbString.c_str())))
	hd_ZbbVar = ((TH1F*)data.file()->Get(names[i].c_str()));
      else if(n.Contains(TRegexp(ZbbString2.c_str())))
 	hd_ZbbVar2 = ((TH1F*)data.file()->Get(names[i].c_str()));
      else if(n.Contains(TRegexp(TTbarString.c_str())))
	hd_TTbarVar = ((TH1F*)data.file()->Get(names[i].c_str()));

      //with the proper trigger eff
      //      double SF[] = {1.03,1.054,1.032};
      double SF[] = {1.0,1.0,1.0};
            
      for(size_t j=0;j< s.size() ;j++) 
	{ 
	  TString sampleName=s[j].name;

	  //counting the events in the regions for data
	  if(s[j].data){ 
	    if((n.Contains(TRegexp("BDTRegionHZee/SimpleJet1_phiBDTRegionHZee"))))
	      BDT_signalRegion.fillFromHisto(s[j], *(TH1F*)s[j].file()->Get(names[i].c_str()) );
	    if((n.Contains(TRegexp(ZlightString.c_str()))))
	      BDTZlight_cr.fillFromHisto(s[j], *(TH1F*)s[j].file()->Get(names[i].c_str()) );
	    if((n.Contains(TRegexp(ZbbString.c_str()))))
	      BDTZbb_cr.fillFromHisto(s[j], *(TH1F*)s[j].file()->Get(names[i].c_str()) );
	    if((n.Contains(TRegexp(TTbarString.c_str()))))
	      BDTTTbar_cr.fillFromHisto(s[j], *(TH1F*)s[j].file()->Get(names[i].c_str()) );
	  }

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

	      //counting the events in the regions after MC rescaling
	      if((n.Contains(TRegexp("BDTRegionHZee/SimpleJet1_phiBDTRegionHZee"))))
		BDT_signalRegion.fillFromHisto(s[j], *h );
	      if((n.Contains(TRegexp(ZlightString.c_str()))))
		BDTZlight_cr.fillFromHisto(s[j], *h );
	      if((n.Contains(TRegexp(ZbbString.c_str()))))
		BDTZbb_cr.fillFromHisto(s[j], *h );
	      if((n.Contains(TRegexp(TTbarString.c_str()))))
		BDTTTbar_cr.fillFromHisto(s[j], *h );

	      if(debug_)
		std::cout << "Sample : " << s[j].name << " - Integral for plot " << names[i] << " = " << h->Integral(-10000,10000) << std::endl;

	      //for the fit
	      if(n.Contains(TRegexp(ZlightString.c_str())))
		allMC_LightVar->Add(h);
	      else if(n.Contains(TRegexp(ZbbString.c_str())))
		allMC_ZbbVar->Add(h);
 	      else if(n.Contains(TRegexp(ZbbString2.c_str())))
 		allMC_ZbbVar2->Add(h);
	      else if(n.Contains(TRegexp(TTbarString.c_str())))
		allMC_TTbarVar->Add(h);


	    }
	}
    }

  std::cout << " ------  Light Region yields  ------ " << std::endl;
  BDTZlight_cr.dump();
  std::cout << " ------  TTbar Region yields  ------ " << std::endl;
  BDTTTbar_cr.dump();  
  std::cout << " ------  Zbb Region yields  ------ " << std::endl;
  BDTZbb_cr.dump();
  std::cout << " ------  Signal Region yields  ------ " << std::endl;
  BDT_signalRegion.dump();

  //ROOT.WORKSPACE!!!
  //  RooWorkspace* wspace = new RooWorkspace();
  //change RooRealVar to RooFormulaVar. Put here the fraction between the yeld in the signal region and the background region

  //Simultaneous fit 
  //events
  RooRealVar f_dyl("f_dyl","f_dyl",200.,0.,600.); //initial value and range
  RooRealVar f_dyb("f_dyb","f_dyb",130.,0.,400.); //initial value and range
  RooRealVar f_ttbar("f_ttbar","f_ttbar",20.,0.,150.); //initial value and range
  RooRealVar f_st("f_st","f_st",BDT_signalRegion.cST()); //initial value and range
  RooRealVar f_vv("f_vv","f_vv",BDT_signalRegion.cVV()); //initial value and range

  RooRealVar tr_lightcr_dyl("tr_lightcr_dyl","tr_lightcr_dyl",BDTZlight_cr.cDYL()/BDT_signalRegion.cDYL()); //initial value and range
  RooRealVar tr_lightcr_dyb("tr_lightcr_dyb","tr_lightcr_dyb",BDTZlight_cr.cDYB()/BDT_signalRegion.cDYB()); //initial value and range
  RooRealVar tr_lightcr_ttbar("tr_lightcr_ttbar","tr_lightcr_ttbar",BDTZlight_cr.cTTbar()/BDT_signalRegion.cTTbar()); //initial value and range
  RooRealVar tr_lightcr_st("tr_lightcr_st","tr_lightcr_st",BDTZlight_cr.cST()/BDT_signalRegion.cST()); //initial value and range
  RooRealVar tr_lightcr_vv("tr_lightcr_vv","tr_lightcr_vv",BDTZlight_cr.cVV()/BDT_signalRegion.cVV()); //initial value and range

  RooRealVar tr_ttbarcr_dyl("tr_ttbarcr_dyl","tr_ttbarcr_dyl",BDTTTbar_cr.cDYL()/BDT_signalRegion.cDYL()); //initial value and range
  RooRealVar tr_ttbarcr_dyb("tr_ttbarcr_dyb","tr_ttbarcr_dyb",BDTTTbar_cr.cDYB()/BDT_signalRegion.cDYB()); //initial value and range
  RooRealVar tr_ttbarcr_ttbar("tr_ttbarcr_ttbar","tr_ttbarcr_ttbar",BDTTTbar_cr.cTTbar()/BDT_signalRegion.cTTbar()); //initial value and range
  RooRealVar tr_ttbarcr_st("tr_ttbarcr_st","tr_ttbarcr_st",BDTTTbar_cr.cST()/BDT_signalRegion.cST()); //initial value and range
  RooRealVar tr_ttbarcr_vv("tr_ttbarcr_vv","tr_ttbarcr_vv",BDTTTbar_cr.cVV()/BDT_signalRegion.cVV()); //initial value and range
  
  RooRealVar tr_heavycr_dyl("tr_heavycr_dyl","tr_heavycr_dyl",BDTZbb_cr.cDYL()/BDT_signalRegion.cDYL()); //initial value and range
  RooRealVar tr_heavycr_dyb("tr_heavycr_dyb","tr_heavycr_dyb",BDTZbb_cr.cDYB()/BDT_signalRegion.cDYB()); //initial value and range
  RooRealVar tr_heavycr_ttbar("tr_heavycr_ttbar","tr_heavycr_ttbar",BDTZbb_cr.cTTbar()/BDT_signalRegion.cTTbar()); //initial value and range
  RooRealVar tr_heavycr_st("tr_heavycr_st","tr_heavycr_st",BDTZbb_cr.cST()/BDT_signalRegion.cST()); //initial value and range
  RooRealVar tr_heavycr_vv("tr_heavycr_vv","tr_heavycr_vv",BDTZbb_cr.cVV()/BDT_signalRegion.cVV()); //initial value and range

  RooFormulaVar fit_lightcr_dyl("fit_lightcr_dyl","fit_lightcr_dyl","@0*@1",RooArgList(f_dyl,tr_lightcr_dyl));
  RooFormulaVar fit_lightcr_dyb("fit_lightcr_dyb","fit_lightcr_dyb","@0*@1",RooArgList(f_dyb,tr_lightcr_dyb));
  RooFormulaVar fit_lightcr_ttbar("fit_lightcr_ttbar","fit_lightcr_ttbar","@0*@1",RooArgList(f_ttbar,tr_lightcr_ttbar));
  RooFormulaVar fit_lightcr_st("fit_lightcr_st","fit_lightcr_st","@0*@1",RooArgList(f_st,tr_lightcr_st));
  RooFormulaVar fit_lightcr_vv("fit_lightcr_vv","fit_lightcr_vv","@0*@1",RooArgList(f_vv,tr_lightcr_vv));

  RooFormulaVar fit_ttbarcr_dyl("fit_ttbarcr_dyl","fit_ttbarcr_dyl","@0*@1",RooArgList(f_dyl,tr_ttbarcr_dyl));
  RooFormulaVar fit_ttbarcr_dyb("fit_ttbarcr_dyb","fit_ttbarcr_dyb","@0*@1",RooArgList(f_dyb,tr_ttbarcr_dyb));
  RooFormulaVar fit_ttbarcr_ttbar("fit_ttbarcr_ttbar","fit_ttbarcr_ttbar","@0*@1",RooArgList(f_ttbar,tr_ttbarcr_ttbar));
  RooFormulaVar fit_ttbarcr_st("fit_ttbarcr_st","fit_ttbarcr_st","@0*@1",RooArgList(f_st,tr_ttbarcr_st));
  RooFormulaVar fit_ttbarcr_vv("fit_ttbarcr_vv","fit_ttbarcr_vv","@0*@1",RooArgList(f_vv,tr_ttbarcr_vv));

  RooFormulaVar fit_heavycr_dyl("fit_heavycr_dyl","fit_heavycr_dyl","@0*@1",RooArgList(f_dyl,tr_heavycr_dyl));
  RooFormulaVar fit_heavycr_dyb("fit_heavycr_dyb","fit_heavycr_dyb","@0*@1",RooArgList(f_dyb,tr_heavycr_dyb));
  RooFormulaVar fit_heavycr_ttbar("fit_heavycr_ttbar","fit_heavycr_ttbar","@0*@1",RooArgList(f_ttbar,tr_heavycr_ttbar));
  RooFormulaVar fit_heavycr_st("fit_heavycr_st","fit_heavycr_st","@0*@1",RooArgList(f_st,tr_heavycr_st));
  RooFormulaVar fit_heavycr_vv("fit_heavycr_vv","fit_heavycr_vv","@0*@1",RooArgList(f_vv,tr_heavycr_vv));

  //the order depends on sampleCollection.h: zh, vv, st, ttbar, dyl (+boosted), dyb(+boosted)

  //ZbbVar1
  //dibosons 3 files
  ((TH1F*)allMC_ZbbVar->At(0))->Add((TH1F*)allMC_ZbbVar->At(1));
  ((TH1F*)allMC_ZbbVar->At(0))->Add((TH1F*)allMC_ZbbVar->At(2));
  //single top 6 files
  ((TH1F*)allMC_ZbbVar->At(3))->Add((TH1F*)allMC_ZbbVar->At(4));
  ((TH1F*)allMC_ZbbVar->At(3))->Add((TH1F*)allMC_ZbbVar->At(5));
  ((TH1F*)allMC_ZbbVar->At(3))->Add((TH1F*)allMC_ZbbVar->At(6));
  ((TH1F*)allMC_ZbbVar->At(3))->Add((TH1F*)allMC_ZbbVar->At(7));
  ((TH1F*)allMC_ZbbVar->At(3))->Add((TH1F*)allMC_ZbbVar->At(8));
  //dylight 4 files
  ((TH1F*)allMC_ZbbVar->At(10))->Add((TH1F*)allMC_ZbbVar->At(11));
  ((TH1F*)allMC_ZbbVar->At(10))->Add((TH1F*)allMC_ZbbVar->At(12));
  ((TH1F*)allMC_ZbbVar->At(10))->Add((TH1F*)allMC_ZbbVar->At(13));
  //dyb 2 files
  ((TH1F*)allMC_ZbbVar->At(14))->Add((TH1F*)allMC_ZbbVar->At(15));

  std::cout << "Generatign ZbbVar template ............ " << std::endl;
  RooRealVar ZbbVar("ZbbVar","ZbbVar",ZbbVar_min,ZbbVar_max);
  RooDataHist data_ZbbVar("data_ZbbVar","data_ZbbVar",ZbbVar,hd_ZbbVar);
  RooDataHist vv_ZbbVar("vv_ZbbVar","vv_ZbbVar",ZbbVar,(TH1F*)allMC_ZbbVar->At(0));
  RooDataHist st_ZbbVar("st_ZbbVar","st_ZbbVar",ZbbVar,(TH1F*)allMC_ZbbVar->At(3));
  RooDataHist ttbar_ZbbVar("ttbar_ZbbVar","ttbar_ZbbVar",ZbbVar,(TH1F*)allMC_ZbbVar->At(9));
  RooDataHist dyl_ZbbVar("dyl_ZbbVar","dyl_ZbbVar",ZbbVar,(TH1F*)(allMC_ZbbVar->At(10))); // charm and light together
  RooDataHist dyb_ZbbVar("dyb_ZbbVar","dyb_ZbbVar",ZbbVar,(TH1F*)allMC_ZbbVar->At(14));
  RooHistPdf pdf_vv_ZbbVar ("pdf_vv_ZbbVar","pdf_vv_ZbbVar",RooArgList(ZbbVar),vv_ZbbVar);
  RooHistPdf pdf_st_ZbbVar ("pdf_st_ZbbVar","pdf_st_ZbbVar",RooArgList(ZbbVar),st_ZbbVar);
  RooHistPdf pdf_ttbar_ZbbVar ("pdf_ttbar_ZbbVar","pdf_ttbar_ZbbVar",RooArgList(ZbbVar),ttbar_ZbbVar);
  RooHistPdf pdf_dyl_ZbbVar ("pdf_dyl_ZbbVar","pdf_dyl_ZbbVar",RooArgList(ZbbVar),dyl_ZbbVar);
  RooHistPdf pdf_dyb_ZbbVar ("pdf_dyb_ZbbVar","pdf_dyb_ZbbVar",RooArgList(ZbbVar),dyb_ZbbVar);
  RooAddPdf model_ZbbVar("model_ZbbVar",
				  "model_ZbbVar",
				  RooArgList(pdf_vv_ZbbVar,pdf_st_ZbbVar,pdf_ttbar_ZbbVar,pdf_dyl_ZbbVar,pdf_dyb_ZbbVar),
				  RooArgList(fit_heavycr_vv,fit_heavycr_st,fit_heavycr_ttbar,fit_heavycr_dyl,fit_heavycr_dyb),
				  kFALSE);
  //RooAddPdf model_ZbbVar("model_ZbbVar","model_ZbbVar",RooArgList(pdf_dyb_ZbbVar,pdf_ttbar_ZbbVar,pdf_dyl_ZbbVar),RooArgList(f_1,f_2),kFALSE);


  //ZbbVar2
  //dibosons 3 files
  ((TH1F*)allMC_ZbbVar2->At(0))->Add((TH1F*)allMC_ZbbVar2->At(1));
  ((TH1F*)allMC_ZbbVar2->At(0))->Add((TH1F*)allMC_ZbbVar2->At(2));
  //single top 6 files
  ((TH1F*)allMC_ZbbVar2->At(3))->Add((TH1F*)allMC_ZbbVar2->At(4));
  ((TH1F*)allMC_ZbbVar2->At(3))->Add((TH1F*)allMC_ZbbVar2->At(5));
  ((TH1F*)allMC_ZbbVar2->At(3))->Add((TH1F*)allMC_ZbbVar2->At(6));
  ((TH1F*)allMC_ZbbVar2->At(3))->Add((TH1F*)allMC_ZbbVar2->At(7));
  ((TH1F*)allMC_ZbbVar2->At(3))->Add((TH1F*)allMC_ZbbVar2->At(8));
  //dylight 4 files
  ((TH1F*)allMC_ZbbVar2->At(10))->Add((TH1F*)allMC_ZbbVar2->At(11));
  ((TH1F*)allMC_ZbbVar2->At(10))->Add((TH1F*)allMC_ZbbVar2->At(12));
  ((TH1F*)allMC_ZbbVar2->At(10))->Add((TH1F*)allMC_ZbbVar2->At(13));
  //dyb 2 files
  ((TH1F*)allMC_ZbbVar2->At(14))->Add((TH1F*)allMC_ZbbVar2->At(15));

  std::cout << "Generatign ZbbVar2 template ............ " << std::endl;
  RooRealVar ZbbVar2("ZbbVar2","ZbbVar2",ZbbVar2_min,ZbbVar2_max);
  RooDataHist data_ZbbVar2("data_ZbbVar2","data_ZbbVar2",ZbbVar2,hd_ZbbVar2);
  RooDataHist vv_ZbbVar2("vv_ZbbVar2","vv_ZbbVar2",ZbbVar2,(TH1F*)allMC_ZbbVar2->At(0));
  RooDataHist st_ZbbVar2("st_ZbbVar2","st_ZbbVar2",ZbbVar2,(TH1F*)allMC_ZbbVar2->At(3));
  RooDataHist ttbar_ZbbVar2("ttbar_ZbbVar2","ttbar_ZbbVar2",ZbbVar2,(TH1F*)allMC_ZbbVar2->At(9));
  RooDataHist dyl_ZbbVar2("dyl_ZbbVar2","dyl_ZbbVar2",ZbbVar2,(TH1F*)(allMC_ZbbVar2->At(10))); // charm and light together
  RooDataHist dyb_ZbbVar2("dyb_ZbbVar2","dyb_ZbbVar2",ZbbVar2,(TH1F*)allMC_ZbbVar2->At(14));
  RooHistPdf pdf_vv_ZbbVar2 ("pdf_vv_ZbbVar2","pdf_vv_ZbbVar2",RooArgList(ZbbVar2),vv_ZbbVar2);
  RooHistPdf pdf_st_ZbbVar2 ("pdf_st_ZbbVar2","pdf_st_ZbbVar2",RooArgList(ZbbVar2),st_ZbbVar2);
  RooHistPdf pdf_ttbar_ZbbVar2 ("pdf_ttbar_ZbbVar2","pdf_ttbar_ZbbVar2",RooArgList(ZbbVar2),ttbar_ZbbVar2);
  RooHistPdf pdf_dyl_ZbbVar2 ("pdf_dyl_ZbbVar2","pdf_dyl_ZbbVar2",RooArgList(ZbbVar2),dyl_ZbbVar2);
  RooHistPdf pdf_dyb_ZbbVar2 ("pdf_dyb_ZbbVar2","pdf_dyb_ZbbVar2",RooArgList(ZbbVar2),dyb_ZbbVar2);
  RooAddPdf model_ZbbVar2("model_ZbbVar2",
			  "model_ZbbVar2",
			  RooArgList(pdf_vv_ZbbVar2,pdf_st_ZbbVar2,pdf_ttbar_ZbbVar2,pdf_dyl_ZbbVar2,pdf_dyb_ZbbVar2),
			  RooArgList(fit_heavycr_vv,fit_heavycr_st,fit_heavycr_ttbar,fit_heavycr_dyl,fit_heavycr_dyb),
			  kFALSE);
//   //RooAddPdf model_ZbbVar2("model_ZbbVar2","model_ZbbVar2",RooArgList(pdf_dyb_ZbbVar2,pdf_ttbar_ZbbVar2,pdf_dyl_ZbbVar2),RooArgList(f_1,f_2),kFALSE);


  //TTbarVar

  //dibosons 3 files
  ((TH1F*)allMC_TTbarVar->At(0))->Add((TH1F*)allMC_TTbarVar->At(1));
  ((TH1F*)allMC_TTbarVar->At(0))->Add((TH1F*)allMC_TTbarVar->At(2));
  //single top 6 files
  ((TH1F*)allMC_TTbarVar->At(3))->Add((TH1F*)allMC_TTbarVar->At(4));
  ((TH1F*)allMC_TTbarVar->At(3))->Add((TH1F*)allMC_TTbarVar->At(5));
  ((TH1F*)allMC_TTbarVar->At(3))->Add((TH1F*)allMC_TTbarVar->At(6));
  ((TH1F*)allMC_TTbarVar->At(3))->Add((TH1F*)allMC_TTbarVar->At(7));
  ((TH1F*)allMC_TTbarVar->At(3))->Add((TH1F*)allMC_TTbarVar->At(8));
  //dylight 4 files
  ((TH1F*)allMC_TTbarVar->At(10))->Add((TH1F*)allMC_TTbarVar->At(11));
  ((TH1F*)allMC_TTbarVar->At(10))->Add((TH1F*)allMC_TTbarVar->At(12));
  ((TH1F*)allMC_TTbarVar->At(10))->Add((TH1F*)allMC_TTbarVar->At(13));
  //dyb 2 files
  ((TH1F*)allMC_TTbarVar->At(14))->Add((TH1F*)allMC_TTbarVar->At(15));

  std::cout << "Generatign TTbarVar template ............ " << std::endl;
  RooRealVar TTbarVar("TTbarVar","TTbarVar",TTbarVar_min,TTbarVar_max);
  RooDataHist data_TTbarVar("data_TTbarVar","data_TTbarVar",TTbarVar,hd_TTbarVar);
  RooDataHist vv_TTbarVar("vv_TTbarVar","vv_TTbarVar",TTbarVar,(TH1F*)allMC_TTbarVar->At(0));
  RooDataHist st_TTbarVar("st_TTbarVar","st_TTbarVar",TTbarVar,(TH1F*)allMC_TTbarVar->At(3));
  RooDataHist ttbar_TTbarVar("ttbar_TTbarVar","ttbar_TTbarVar",TTbarVar,(TH1F*)allMC_TTbarVar->At(9));
  RooDataHist dyl_TTbarVar("dyl_TTbarVar","dyl_TTbarVar",TTbarVar,(TH1F*)(allMC_TTbarVar->At(10))); // charm and light together
  RooDataHist dyb_TTbarVar("dyb_TTbarVar","dyb_TTbarVar",TTbarVar,(TH1F*)(allMC_TTbarVar->At(14)));
  RooHistPdf pdf_vv_TTbarVar ("pdf_vv_TTbarVar","pdf_vv_TTbarVar",RooArgList(TTbarVar),vv_TTbarVar);
  RooHistPdf pdf_st_TTbarVar ("pdf_st_TTbarVar","pdf_st_TTbarVar",RooArgList(TTbarVar),st_TTbarVar);
  RooHistPdf pdf_ttbar_TTbarVar ("pdf_ttbar_TTbarVar","pdf_ttbar_TTbarVar",RooArgList(TTbarVar),ttbar_TTbarVar);
  RooHistPdf pdf_dyl_TTbarVar ("pdf_dyl_TTbarVar","pdf_dyl_TTbarVar",RooArgList(TTbarVar),dyl_TTbarVar);
  RooHistPdf pdf_dyb_TTbarVar ("pdf_dyb_TTbarVar","pdf_dyb_TTbarVar",RooArgList(TTbarVar),dyb_TTbarVar);
  RooAddPdf model_TTbarVar("model_TTbarVar",
			  "model_TTbarVar",
			  RooArgList(pdf_vv_TTbarVar,pdf_st_TTbarVar,pdf_ttbar_TTbarVar,pdf_dyl_TTbarVar,pdf_dyb_TTbarVar),
			  RooArgList(fit_ttbarcr_vv,fit_ttbarcr_st,fit_ttbarcr_ttbar,fit_ttbarcr_dyl,fit_ttbarcr_dyb),
			  kFALSE);
  //RooAddPdf model_TTbarVar("model_TTbarVar","model_TTbarVar",RooArgList(pdf_dyb_TTbarVar,pdf_ttbar_TTbarVar,pdf_dyl_TTbarVar),RooArgList(f_1,f_2),kFALSE);
  
  //LightVar
  //dibosons 3 files
  ((TH1F*)allMC_LightVar->At(0))->Add((TH1F*)allMC_LightVar->At(1));
  ((TH1F*)allMC_LightVar->At(0))->Add((TH1F*)allMC_LightVar->At(2));
  //single top 6 files
  ((TH1F*)allMC_LightVar->At(3))->Add((TH1F*)allMC_LightVar->At(4));
  ((TH1F*)allMC_LightVar->At(3))->Add((TH1F*)allMC_LightVar->At(5));
  ((TH1F*)allMC_LightVar->At(3))->Add((TH1F*)allMC_LightVar->At(6));
  ((TH1F*)allMC_LightVar->At(3))->Add((TH1F*)allMC_LightVar->At(7));
  ((TH1F*)allMC_LightVar->At(3))->Add((TH1F*)allMC_LightVar->At(8));
  //dylight 4 files
  ((TH1F*)allMC_LightVar->At(10))->Add((TH1F*)allMC_LightVar->At(11));
  ((TH1F*)allMC_LightVar->At(10))->Add((TH1F*)allMC_LightVar->At(12));
  ((TH1F*)allMC_LightVar->At(10))->Add((TH1F*)allMC_LightVar->At(13));
  //dyb 2 files
  ((TH1F*)allMC_LightVar->At(14))->Add((TH1F*)allMC_LightVar->At(15));

  std::cout << "Generatign LightVar template ............ " << std::endl;
  RooRealVar LightVar("LightVar","LightVar",LightVar_min,LightVar_max);
  RooDataHist data_LightVar("data_LightVar","data_LightVar",LightVar,hd_LightVar);
  RooDataHist vv_LightVar("vv_LightVar","vv_LightVar",LightVar,(TH1F*)allMC_LightVar->At(0));
  RooDataHist st_LightVar("st_LightVar","st_LightVar",LightVar,(TH1F*)allMC_LightVar->At(3));
  RooDataHist ttbar_LightVar("ttbar_LightVar","ttbar_LightVar",LightVar,(TH1F*)allMC_LightVar->At(9));
  RooDataHist dyl_LightVar("dyl_LightVar","dyl_LightVar",LightVar,(TH1F*)(allMC_LightVar->At(10))); // charm and light together
  RooDataHist dyb_LightVar("dyb_LightVar","dyb_LightVar",LightVar,(TH1F*)allMC_LightVar->At(14));
  RooHistPdf pdf_vv_LightVar ("pdf_vv_LightVar","pdf_vv_LightVar",RooArgList(LightVar),vv_LightVar);
  RooHistPdf pdf_st_LightVar ("pdf_st_LightVar","pdf_st_LightVar",RooArgList(LightVar),st_LightVar);
  RooHistPdf pdf_ttbar_LightVar ("pdf_ttbar_LightVar","pdf_ttbar_LightVar",RooArgList(LightVar),ttbar_LightVar);
  RooHistPdf pdf_dyl_LightVar ("pdf_dyl_LightVar","pdf_dyl_LightVar",RooArgList(LightVar),dyl_LightVar);
  RooHistPdf pdf_dyb_LightVar ("pdf_dyb_LightVar","pdf_dyb_LightVar",RooArgList(LightVar),dyb_LightVar);
  RooAddPdf model_LightVar("model_LightVar",
				 "model_LightVar",
				 RooArgList(pdf_vv_LightVar,pdf_st_LightVar,pdf_ttbar_LightVar,pdf_dyl_LightVar,pdf_dyb_LightVar),
				 RooArgList(fit_lightcr_vv,fit_lightcr_st,fit_lightcr_ttbar,fit_lightcr_dyl,fit_lightcr_dyb),
				 kFALSE);
  //RooAddPdf model_LightVar("model_LightVar","model_LightVar",RooArgList(pdf_dyb_LightVar,pdf_ttbar_LightVar,pdf_dyl_LightVar),RooArgList(f_1,f_2),kFALSE);
  


  std::cout << "Generatign var To Fit ............ " << std::endl;
  RooCategory varToFit("varToFit","varToFit");
  varToFit.defineType("TTbarVar");
  varToFit.defineType("ZbbVar");
  varToFit.defineType("ZbbVar2");
  varToFit.defineType("LightVar");

  std::cout << "Generatign combData ............ " << std::endl;
  RooDataHist combData("combData","combined data",
		       RooArgSet(TTbarVar,ZbbVar,ZbbVar2,LightVar),
		       //RooArgSet(ZbbVar),
		       Index(varToFit),
		       Import("TTbarVar",data_TTbarVar),
 		       Import("ZbbVar",data_ZbbVar),
		       Import("ZbbVar2",data_ZbbVar2),
		       Import("LightVar",data_LightVar));
  
  std::cout << "Generatign RooSimultaneous ............ " << std::endl;
  RooSimultaneous simPdf("simPdf","simPdf",varToFit);
  simPdf.addPdf(model_TTbarVar,"TTbarVar"); 
  simPdf.addPdf(model_ZbbVar,"ZbbVar"); 
  simPdf.addPdf(model_ZbbVar2,"ZbbVar2"); 
  simPdf.addPdf(model_LightVar,"LightVar"); 
  std::cout << "FITTING  ............ " << std::endl;

  RooFitResult * fitRes = simPdf.fitTo(combData,SumW2Error(1));


  // Plot data and PDF overlaid
  RooPlot* ZbbVar_frame = ZbbVar.frame(Title("")) ;
  data_ZbbVar.plotOn(ZbbVar_frame) ;
  model_ZbbVar.plotOn(ZbbVar_frame) ;
  model_ZbbVar.plotOn(ZbbVar_frame,Components(pdf_vv_ZbbVar),LineColor(kGray),LineStyle(kDotted)) ;
  model_ZbbVar.plotOn(ZbbVar_frame,Components(pdf_st_ZbbVar),LineColor(kCyan),LineStyle(kDotted)) ;
  model_ZbbVar.plotOn(ZbbVar_frame,Components(pdf_dyb_ZbbVar),LineColor(kRed),LineStyle(kDotted)) ;
  model_ZbbVar.plotOn(ZbbVar_frame,Components(pdf_dyl_ZbbVar),LineColor(kBlack),LineStyle(kDotted)) ;
  model_ZbbVar.plotOn(ZbbVar_frame,Components(pdf_ttbar_ZbbVar),LineColor(kGreen),LineStyle(kDotted)) ;
  TCanvas * c_ZbbVar = new TCanvas("ZbbVar fit","ZbbVar_fit",600,600) ;
  gPad->SetLeftMargin(0.15) ; ZbbVar_frame->GetYaxis()->SetTitleOffset(1.4) ; ZbbVar_frame->Draw() ;
  c_ZbbVar->Print("fromFit_ZbbVar","pdf");

  // Plot data and PDF overlaid
  RooPlot* ZbbVar2_frame = ZbbVar2.frame(Title("")) ;
  data_ZbbVar2.plotOn(ZbbVar2_frame) ;
  model_ZbbVar2.plotOn(ZbbVar2_frame) ;
  model_ZbbVar2.plotOn(ZbbVar2_frame,Components(pdf_vv_ZbbVar2),LineColor(kGray),LineStyle(kDotted)) ;
  model_ZbbVar2.plotOn(ZbbVar2_frame,Components(pdf_st_ZbbVar2),LineColor(kCyan),LineStyle(kDotted)) ;
  model_ZbbVar2.plotOn(ZbbVar2_frame,Components(pdf_dyb_ZbbVar2),LineColor(kRed),LineStyle(kDotted)) ;
  model_ZbbVar2.plotOn(ZbbVar2_frame,Components(pdf_dyl_ZbbVar2),LineColor(kBlack),LineStyle(kDotted)) ;
  model_ZbbVar2.plotOn(ZbbVar2_frame,Components(pdf_ttbar_ZbbVar2),LineColor(kGreen),LineStyle(kDotted)) ;
  TCanvas * c_ZbbVar2 = new TCanvas("ZbbVar2 fit","ZbbVar2_fit",600,600) ;
  gPad->SetLeftMargin(0.15) ; ZbbVar2_frame->GetYaxis()->SetTitleOffset(1.4) ; ZbbVar2_frame->Draw() ;
  c_ZbbVar2->Print("fromFit_ZbbVar2","pdf");


  RooPlot* LightVar_frame = LightVar.frame(Title("")) ;
  data_LightVar.plotOn(LightVar_frame) ;
  model_LightVar.plotOn(LightVar_frame) ;
  model_LightVar.plotOn(LightVar_frame,Components(pdf_vv_LightVar),LineColor(kGray),LineStyle(kDotted)) ;
  model_LightVar.plotOn(LightVar_frame,Components(pdf_st_LightVar),LineColor(kCyan),LineStyle(kDotted)) ;
  model_LightVar.plotOn(LightVar_frame,Components(pdf_dyb_LightVar),LineColor(kRed),LineStyle(kDotted)) ;
  model_LightVar.plotOn(LightVar_frame,Components(pdf_dyl_LightVar),LineColor(kBlack),LineStyle(kDotted)) ;
  model_LightVar.plotOn(LightVar_frame,Components(pdf_ttbar_LightVar),LineColor(kGreen),LineStyle(kDotted)) ;
  TCanvas * c_LightVar = new TCanvas("LightVar fit","LightVar_fit",600,600) ;
  gPad->SetLeftMargin(0.15) ; LightVar_frame->GetYaxis()->SetTitleOffset(1.4) ; LightVar_frame->Draw() ;
  c_LightVar->Print("fromFit_LightVar","pdf");

  RooPlot* TTbarVar_frame = TTbarVar.frame(Title("")) ;
  data_TTbarVar.plotOn(TTbarVar_frame) ;
  model_TTbarVar.plotOn(TTbarVar_frame) ;
  model_TTbarVar.plotOn(TTbarVar_frame,Components(pdf_vv_TTbarVar),LineColor(kGray),LineStyle(kDotted)) ;
  model_TTbarVar.plotOn(TTbarVar_frame,Components(pdf_st_TTbarVar),LineColor(kCyan),LineStyle(kDotted)) ;
  model_TTbarVar.plotOn(TTbarVar_frame,Components(pdf_dyb_TTbarVar),LineColor(kRed),LineStyle(kDotted)) ;
  model_TTbarVar.plotOn(TTbarVar_frame,Components(pdf_dyl_TTbarVar),LineColor(kBlack),LineStyle(kDotted)) ;
  model_TTbarVar.plotOn(TTbarVar_frame,Components(pdf_ttbar_TTbarVar),LineColor(kGreen),LineStyle(kDotted)) ;
  TCanvas * c_TTbarVar = new TCanvas("TTbarVar fit","TTbarVar_fit",600,600) ;
  gPad->SetLeftMargin(0.15) ; TTbarVar_frame->GetYaxis()->SetTitleOffset(1.4) ; TTbarVar_frame->Draw() ;
  c_TTbarVar->Print("fromFit_TTbarVar","pdf");


  //  fitRes->Print();
  //  fitRes->Print("v");

  return 0;
}
