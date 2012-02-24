#include "fitInfo.hpp"
//#include "sampleCollection.h"
#include "controlRegions.h"
#include <iostream> 
#include <TCanvas.h>
#include <TLine.h>
#include <TRegexp.h>
#include <TLegend.h>
#include <THStack.h>
//#include "setTDRStyle.C"
#include <TROOT.h>
//#include "customize.h"
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
  bool debug_=true;

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

  std::vector<fitInfo *> fitInfos;
  std::vector<controlRegion*> crToFit;  
  crToFit.push_back( new controlRegion );
  crToFit.push_back( new controlRegion );
  crToFit.push_back( new controlRegion );


  std::string s_prefix = "BDT";
  //std::string s_sysprefix = "BDTSystBtagDOWN";
  std::string s_sysprefix = "";
  std::string s_suffix = "$";
  std::string s_region_light = "Zlight";
  std::string s_var_light = "HiggsPt";
  std::string s_region_ttbar = "TTbar";
  std::string s_var_ttbar = "ZH_dPhi";
  std::string s_region_zbb = "Zbb";
  std::string s_var_zbb = "SimpleJets_vtxMass";

  if(debug_)
    std::cout << " fillinf the fit info " << std::endl;

  fitInfos.push_back( new fitInfo(s_region_light,s_var_light,s_prefix,s_sysprefix,s_suffix,0,500) );
  fitInfos.push_back( new fitInfo(s_region_ttbar,s_var_ttbar,s_prefix,s_sysprefix,s_suffix,0,500) );
  fitInfos.push_back( new fitInfo(s_region_zbb,s_var_zbb,s_prefix,s_sysprefix,s_suffix,0,500) );

  if(debug_)
    std::cout << " filled the fit info " << std::endl;

  Options o;
  double SF[] = {1.0,1.0,1.0}; // SF for scaling
  TH1F * h = new TH1F;
  h->Sumw2();

  for(size_t i = 0 ; i < names.size() ; i++) 
    {
      TString n=names[i];
      for(size_t j=0;j< s.size() ;j++) 
	{ 
	  TString sampleName=s[j].name;
	  h = ((TH1F*)s[j].file()->Get(names[i].c_str()));
	  if(!s[j].data)
	    h->Scale(s[j].scale(data.lumi(),fa,fb,SF));
	  for( int r=0; r<fitInfos.size(); ++r ){
	    if( n.Contains(TRegexp((fitInfos.at(r)->s_regionForSyst).c_str())) )
		crToFit.at(r)->fillFromHisto(s[j], *h, 1 , h->GetNbinsX() );
	    if( n.Contains(TRegexp((fitInfos.at(r)->s_regionString).c_str())) 
		||  n.Contains(TRegexp((fitInfos.at(r)->s_signalRegion).c_str())) ){
	      if( n.Contains(TRegexp((fitInfos.at(r)->s_regionString).c_str())) ){
		// 	      if(s[j].data)
		// 		fitInfos.at(r)->fillHistoToFit(*(TH1F*)data.file()->Get(names[i].c_str()));
		fitInfos.at(r)->cr->fillFromHisto(s[j], *h, 1 , h->GetNbinsX() ); // no under/overflow considered
	      }
	      if( n.Contains(TRegexp((fitInfos.at(r)->s_signalRegion).c_str())) )
		fitInfos.at(r)->cr_signal->fillFromHisto(s[j], *h ,1 , h->GetNbinsX() ); // no under/overflow considered
	    }
	  } // fitinfo loop
	} // sample loop
    } //name loop


  //  delete h;

  fitInfos.at(0)->fillHistoToFit( *crToFit.at(0)->hTotal() );
  fitInfos.at(1)->fillHistoToFit( *crToFit.at(1)->hTotal() );
  fitInfos.at(2)->fillHistoToFit( *crToFit.at(2)->hTotal() );

  //to fit real data
//   fitInfos.at(0)->fillHistoToFit( *fitInfos.at(0)->cr->hTotal() );
//   fitInfos.at(1)->fillHistoToFit( *fitInfos.at(1)->cr->hTotal() );
//   fitInfos.at(2)->fillHistoToFit( *fitInfos.at(2)->cr->hTotal() );

  std::string zlightTemplate = "DYL";
  std::string ttbarTemplate = "TTbar";
  std::string zbbTemplate = "DYB";
  std::string stTemplate = "ST";
  std::string vvTemplate = "VV";

  std::vector<std::string> templateNames;
  std::vector<std::string> fixedTemplateNames;

  templateNames.push_back(zlightTemplate);
  templateNames.push_back(zbbTemplate);
  templateNames.push_back(ttbarTemplate);
  fixedTemplateNames.push_back(stTemplate);
  fixedTemplateNames.push_back(vvTemplate);

  std::vector<RooRealVar*> f_vars;
  for(int i=0; i<fixedTemplateNames.size(); ++i)
    f_vars.push_back( new RooRealVar(("f_"+fixedTemplateNames.at(i)).c_str(),("f_"+fixedTemplateNames.at(i)).c_str(), fitInfos.at(0)->cr_signal->count(fixedTemplateNames.at(i)) ) );
  for(int i=0; i<templateNames.size(); ++i)
    f_vars.push_back( new RooRealVar(("f_"+templateNames.at(i)).c_str(),("f_"+templateNames.at(i)).c_str(), fitInfos.at(0)->cr_signal->count(templateNames.at(i)), 0.5*fitInfos.at(0)->cr_signal->count(templateNames.at(i)) , 2.*fitInfos.at(0)->cr_signal->count(templateNames.at(i))) );

  for(int i=0; i<f_vars.size(); ++i)
    std::cout << "Var at " << i << " name = " << f_vars.at(i)->GetName() << std::endl;
 
  fitInfos.at(0)->create_variable(templateNames,fixedTemplateNames,f_vars,0,500);
  fitInfos.at(1)->create_variable(templateNames,fixedTemplateNames,f_vars,0,5);
  fitInfos.at(2)->create_variable(templateNames,fixedTemplateNames,f_vars,0,5);

  RooCategory varToFit("varToFit","varToFit");
  
  for( int r=0; r<fitInfos.size(); ++r ){
    std::cout << " ------  "<< fitInfos.at(r)->regionName() <<"  ------ " << std::endl;
    fitInfos.at(r)->cr->dump();
    varToFit.defineType(fitInfos.at(r)->var->GetName());
  }
  std::cout << " ------  "<< "Signal region" <<"  ------ " << std::endl;
  fitInfos.at(0)->cr_signal->dump();
  
   std::cout << "Generatign var To Fit ............ " << std::endl;
   
   if(debug_){
     for(int t = 0; t < templateNames.size() ; ++t){
       std::cout << "Couting region : " << fitInfos.at(0)->cr->count(templateNames.at(t)) << "  " << templateNames.at(t) << std::endl; 
       std::cout << "Couting signal region : " << fitInfos.at(0)->cr_signal->count(templateNames.at(t)) << "  " << templateNames.at(t) << std::endl; 
     }
     std::cout << "-------------------------------------------" << std::endl;
     for( int r=0; r<fitInfos.size(); ++r ){
       std::cout << "Error = " <<   (*fitInfos.at(r)->var).getError() << std::endl;
       std::cout << "Var to fit = " <<   fitInfos.at(r)->var->GetName() << std::endl;
       std::cout << "Template to fit name = " <<   (*fitInfos.at(r)->templates.at(fixedTemplateNames.size()+templateNames.size()-1)).GetName() << std::endl;
       std::cout << "Template to fit entries = " <<   (*fitInfos.at(r)->templates.at(fixedTemplateNames.size()+templateNames.size()-1)).sumEntries() << std::endl;
       std::cout << "Template to fit entries = " <<   (*fitInfos.at(r)->templates.at(fixedTemplateNames.size()+templateNames.size()-1)).sum(0) << std::endl;
       std::cout << "Data to fit entries = " <<   fitInfos.at(r)->cr->hTotal()->Integral(-1e10,1e10) << std::endl;
     }
   }

   std::cout << "Generatign combData ............ " << std::endl;

   RooDataHist combData("combData","combined data",
			RooArgSet( *fitInfos.at(0)->var ,
				   *fitInfos.at(1)->var ,
				   *fitInfos.at(2)->var ),
			Index(varToFit),
			Import(fitInfos.at(0)->var->GetName(),*fitInfos.at(0)->h_data),
			Import(fitInfos.at(1)->var->GetName(),*fitInfos.at(1)->h_data),
			Import(fitInfos.at(2)->var->GetName(),*fitInfos.at(2)->h_data));
// 		       //		       Import("ZbbVar2",data_ZbbVar2),

  
   std::cout << "Generatign RooSimultaneous ............ " << std::endl;
   RooSimultaneous simPdf("simPdf","simPdf",varToFit);
   simPdf.addPdf(*fitInfos.at(0)->model,fitInfos.at(0)->var->GetName());
   simPdf.addPdf(*fitInfos.at(1)->model,fitInfos.at(1)->var->GetName()); 
   simPdf.addPdf(*fitInfos.at(2)->model,fitInfos.at(2)->var->GetName()); 
//   //  simPdf.addPdf(model_ZbbVar2,"ZbbVar2"); 

   std::cout << "FITTING  ............ " << std::endl;

   RooFitResult * fitRes = simPdf.fitTo(combData,SumW2Error(1));

   // Plot data and PDF overlaid
   RooPlot* ZbbVar_frame = (*fitInfos.at(2)->var).frame(Title("")) ;
   (*fitInfos.at(2)->h_data).plotOn(ZbbVar_frame) ;
   (*fitInfos.at(2)->model).plotOn(ZbbVar_frame) ;
   for(int i = 0; i < templateNames.size(); ++i){
     (*fitInfos.at(2)->model).plotOn(ZbbVar_frame,Components( *fitInfos.at(2)->pdfs.at(i) ) ,LineColor(i+1),LineStyle(kDotted));
   }
   TCanvas * c_ZbbVar = new TCanvas("ZbbVar fit","ZbbVar_fit",600,600) ;
   gPad->SetLeftMargin(0.15) ; ZbbVar_frame->GetYaxis()->SetTitleOffset(1.4) ; ZbbVar_frame->Draw() ;
   c_ZbbVar->Print("fromFitdev_ZbbVar","pdf");

   //ttbar
   RooPlot* TTbarVar_frame = (*fitInfos.at(1)->var).frame(Title("")) ;
   (*fitInfos.at(1)->h_data).plotOn(TTbarVar_frame) ;
   (*fitInfos.at(1)->model).plotOn(TTbarVar_frame) ;
   for(int i = 0; i < templateNames.size(); ++i){
     (*fitInfos.at(1)->model).plotOn(TTbarVar_frame,Components( *fitInfos.at(1)->pdfs.at(i) ) ,LineColor(i+1),LineStyle(kDotted));
   }
   TCanvas * c_TTbarVar = new TCanvas("TTbarVar fit","TTbarVar_fit",600,600) ;
   gPad->SetLeftMargin(0.15) ; TTbarVar_frame->GetYaxis()->SetTitleOffset(1.4) ; TTbarVar_frame->Draw() ;
   c_TTbarVar->Print("fromFitdev_TTbarVar","pdf");

   //zlight
   RooPlot* ZlightVar_frame = (*fitInfos.at(0)->var).frame(Title("")) ;
   (*fitInfos.at(0)->h_data).plotOn(ZlightVar_frame) ;
   (*fitInfos.at(0)->model).plotOn(ZlightVar_frame) ;
   for(int i = 0; i < templateNames.size(); ++i){
     (*fitInfos.at(0)->model).plotOn(ZlightVar_frame,Components( *fitInfos.at(0)->pdfs.at(i) ) ,LineColor(i+1),LineStyle(kDotted));
   }
   TCanvas * c_ZlightVar = new TCanvas("ZlightVar fit","ZlightVar_fit",600,600) ;
   gPad->SetLeftMargin(0.15) ; ZlightVar_frame->GetYaxis()->SetTitleOffset(1.4) ; ZlightVar_frame->Draw() ;
   c_ZlightVar->Print("fromFitdev_ZlightVar","pdf");


//   // Plot data and PDF overlaid
//  RooPlot* ZbbVar_frame = ZbbVar.frame(Title("")) ;
//   data_ZbbVar.plotOn(ZbbVar_frame) ;
//   model_ZbbVar.plotOn(ZbbVar_frame) ;
//   model_ZbbVar.plotOn(ZbbVar_frame,Components(pdf_vv_ZbbVar),LineColor(kGray),LineStyle(kDotted)) ;
//   model_ZbbVar.plotOn(ZbbVar_frame,Components(pdf_st_ZbbVar),LineColor(kCyan),LineStyle(kDotted)) ;
//   model_ZbbVar.plotOn(ZbbVar_frame,Components(pdf_dyb_ZbbVar),LineColor(kRed),LineStyle(kDotted)) ;
//   model_ZbbVar.plotOn(ZbbVar_frame,Components(pdf_dyl_ZbbVar),LineColor(kBlack),LineStyle(kDotted)) ;
//   model_ZbbVar.plotOn(ZbbVar_frame,Components(pdf_ttbar_ZbbVar),LineColor(kGreen),LineStyle(kDotted)) ;
//   TCanvas * c_ZbbVar = new TCanvas("ZbbVar fit","ZbbVar_fit",600,600) ;
//   gPad->SetLeftMargin(0.15) ; ZbbVar_frame->GetYaxis()->SetTitleOffset(1.4) ; ZbbVar_frame->Draw() ;
//   c_ZbbVar->Print("fromFit_ZbbVar","pdf");

// //   // Plot data and PDF overlaid
// //   RooPlot* ZbbVar2_frame = ZbbVar2.frame(Title("")) ;
// //   data_ZbbVar2.plotOn(ZbbVar2_frame) ;
// //   model_ZbbVar2.plotOn(ZbbVar2_frame) ;
// //   model_ZbbVar2.plotOn(ZbbVar2_frame,Components(pdf_vv_ZbbVar2),LineColor(kGray),LineStyle(kDotted)) ;
// //   model_ZbbVar2.plotOn(ZbbVar2_frame,Components(pdf_st_ZbbVar2),LineColor(kCyan),LineStyle(kDotted)) ;
// //   model_ZbbVar2.plotOn(ZbbVar2_frame,Components(pdf_dyb_ZbbVar2),LineColor(kRed),LineStyle(kDotted)) ;
// //   model_ZbbVar2.plotOn(ZbbVar2_frame,Components(pdf_dyl_ZbbVar2),LineColor(kBlack),LineStyle(kDotted)) ;
// //   model_ZbbVar2.plotOn(ZbbVar2_frame,Components(pdf_ttbar_ZbbVar2),LineColor(kGreen),LineStyle(kDotted)) ;
// //   TCanvas * c_ZbbVar2 = new TCanvas("ZbbVar2 fit","ZbbVar2_fit",600,600) ;
// //   gPad->SetLeftMargin(0.15) ; ZbbVar2_frame->GetYaxis()->SetTitleOffset(1.4) ; ZbbVar2_frame->Draw() ;
// //   c_ZbbVar2->Print("fromFit_ZbbVar2","pdf");


//   RooPlot* LightVar_frame = LightVar.frame(Title("")) ;
//   data_LightVar.plotOn(LightVar_frame) ;
//   model_LightVar.plotOn(LightVar_frame) ;
//   model_LightVar.plotOn(LightVar_frame,Components(pdf_vv_LightVar),LineColor(kGray),LineStyle(kDotted)) ;
//   model_LightVar.plotOn(LightVar_frame,Components(pdf_st_LightVar),LineColor(kCyan),LineStyle(kDotted)) ;
//   model_LightVar.plotOn(LightVar_frame,Components(pdf_dyb_LightVar),LineColor(kRed),LineStyle(kDotted)) ;
//   model_LightVar.plotOn(LightVar_frame,Components(pdf_dyl_LightVar),LineColor(kBlack),LineStyle(kDotted)) ;
//   model_LightVar.plotOn(LightVar_frame,Components(pdf_ttbar_LightVar),LineColor(kGreen),LineStyle(kDotted)) ;
//   TCanvas * c_LightVar = new TCanvas("LightVar fit","LightVar_fit",600,600) ;
//   gPad->SetLeftMargin(0.15) ; LightVar_frame->GetYaxis()->SetTitleOffset(1.4) ; LightVar_frame->Draw() ;
//   c_LightVar->Print("fromFit_LightVar","pdf");

//   RooPlot* TTbarVar_frame = TTbarVar.frame(Title("")) ;
//   data_TTbarVar.plotOn(TTbarVar_frame) ;
//   model_TTbarVar.plotOn(TTbarVar_frame) ;
//   model_TTbarVar.plotOn(TTbarVar_frame,Components(pdf_vv_TTbarVar),LineColor(kGray),LineStyle(kDotted)) ;
//   model_TTbarVar.plotOn(TTbarVar_frame,Components(pdf_st_TTbarVar),LineColor(kCyan),LineStyle(kDotted)) ;
//   model_TTbarVar.plotOn(TTbarVar_frame,Components(pdf_dyb_TTbarVar),LineColor(kRed),LineStyle(kDotted)) ;
//   model_TTbarVar.plotOn(TTbarVar_frame,Components(pdf_dyl_TTbarVar),LineColor(kBlack),LineStyle(kDotted)) ;
//   model_TTbarVar.plotOn(TTbarVar_frame,Components(pdf_ttbar_TTbarVar),LineColor(kGreen),LineStyle(kDotted)) ;
//   TCanvas * c_TTbarVar = new TCanvas("TTbarVar fit","TTbarVar_fit",600,600) ;
//   gPad->SetLeftMargin(0.15) ; TTbarVar_frame->GetYaxis()->SetTitleOffset(1.4) ; TTbarVar_frame->Draw() ;
//   c_TTbarVar->Print("fromFit_TTbarVar","pdf");


  //  fitRes->Print();
  //  fitRes->Print("v");

  return 0;
}
