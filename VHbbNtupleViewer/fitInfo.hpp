#ifndef FITINFO_H
#define FITINFO_H

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



class fitInfo{

 private:

  std::string s_prefix;
  std::string s_sysprefix;
  std::string s_suffix;
  std::string s_region;
  std::string s_var;

  double min;
  double max;
  double initial;

  TH1F * hd;  

 public:

  fitInfo():cr(new controlRegion), cr_signal( new controlRegion){
    cr->init();
    cr_signal->init();
    s_regionString = s_prefix+s_region+"ControlRegionHZee/"+s_var+s_prefix+s_region+"ControlRegionHZee$";
    s_regionForSyst = s_sysprefix+s_region+"ControlRegionHZee/"+s_var+s_sysprefix+s_region+"ControlRegionHZee"+s_suffix;
    if(s_sysprefix != "")
      s_signalRegion=s_sysprefix+"RegionHZee/SimpleJet1_phi"+s_sysprefix+"RegionHZee$";
    else
      s_signalRegion="BDTRegionHZee/SimpleJet1_phiBDTRegionHZee$";
  };
  fitInfo(std::string & region, std::string & var, std::string & prefix, std::string & sysprefix , std::string & suffix , double min_, double max_ )
    :s_region(region), s_var(var), s_prefix(prefix), s_sysprefix(sysprefix), s_suffix(suffix), min(min_), max(max_),cr(new controlRegion), cr_signal( new controlRegion) {
    cr->init();
    cr_signal->init();
    s_regionString = s_prefix+s_region+"ControlRegionHZee/"+s_var+s_prefix+s_region+"ControlRegionHZee$";
    s_regionForSyst = s_sysprefix+s_region+"ControlRegionHZee/"+s_var+s_sysprefix+s_region+"ControlRegionHZee"+s_suffix;
    if(s_sysprefix != "")
      s_signalRegion=s_sysprefix+"RegionHZee/SimpleJet1_phi"+s_sysprefix+"RegionHZee$";
    else
      s_signalRegion="BDTRegionHZee/SimpleJet1_phiBDTRegionHZee$";
  };
  ~fitInfo() {};

  std::string regionName(){return s_region;}

  std::string s_regionString;
  std::string s_regionForSyst;
  std::string s_signalRegion;
  controlRegion *cr;
  controlRegion *cr_signal;

  void fillHistoToFit( TH1F & data ){
    hd = new TH1F( data );
  }

  void init(){
    cr->init();
    cr_signal->init();
    s_regionString = s_prefix+s_region+"ControlRegionHZee/"+s_var+s_prefix+s_region+"ControlRegionHZee$";
    s_regionForSyst = s_sysprefix+s_region+"ControlRegionHZee/"+s_var+s_sysprefix+s_region+"ControlRegionHZee"+s_suffix;
    if(s_sysprefix != "")
      s_signalRegion=s_sysprefix+"RegionHZee/SimpleJet1_phi"+s_sysprefix+"RegionHZee$";
    else
      s_signalRegion="BDTRegionHZee/SimpleJet1_phiBDTRegionHZee$";
  }

  RooRealVar *var;
  std::vector<RooRealVar*> tr_vars;
  std::vector<RooFormulaVar*> fit_vars;
  std::vector<RooDataHist*> templates;
  std::vector<RooHistPdf*> pdfs;
  RooArgList *pdfList;
  RooArgList *varList;
  RooAddPdf *model;
  RooDataHist * h_data;

  void create_variable( std::vector<std::string> &templateNames, std::vector<std::string> &fixedTemplateNames, std::vector<RooRealVar*>& f_vars, double min, double max ){

    pdfList = new RooArgList;
    varList = new RooArgList;
    var = new RooRealVar(("var"+s_region).c_str(),("var"+s_region).c_str(), min, max);
    h_data = new RooDataHist(("data"+s_region).c_str(),("data"+s_region).c_str(), *var, hd );

    for(int i=0; i<fixedTemplateNames.size(); ++i){
      std::cout << fixedTemplateNames.at(i) << " count = " << cr->count(fixedTemplateNames.at(i)) << ", signal count = " << cr_signal->count(fixedTemplateNames.at(i)) << std::endl;
      templates.push_back( new RooDataHist((s_region+"cr_"+fixedTemplateNames.at(i)).c_str(),(s_region+"cr_"+fixedTemplateNames.at(i)).c_str(), RooArgList(*var), cr->histo(fixedTemplateNames.at(i) )));
      tr_vars.push_back( new RooRealVar(("tr_"+s_region+"cr_"+fixedTemplateNames.at(i)).c_str(),("tr_"+s_region+"cr_"+fixedTemplateNames.at(i)).c_str(), cr->count(fixedTemplateNames.at(i))/cr_signal->count(fixedTemplateNames.at(i))) );
      fit_vars.push_back( new RooFormulaVar(("fit_"+s_region+"cr_"+fixedTemplateNames.at(i)).c_str(),("fit_"+s_region+"cr_"+fixedTemplateNames.at(i)).c_str(),"@0*@1", RooArgList(*f_vars.at(i),*tr_vars.at(i) ) ) );
      pdfs.push_back( new RooHistPdf(  ("pdf_"+fixedTemplateNames.at(i)+"_"+s_region+"cr_"+fixedTemplateNames.at(i)).c_str(),("pdf_"+fixedTemplateNames.at(i)+"_"+s_region+"cr_"+fixedTemplateNames.at(i)).c_str(), RooArgList(*var), *templates.at(i) ) );
      pdfList->addOwned(*pdfs.at(i));
      varList->addOwned(*fit_vars.at(i));
    }
    std::cout << "creating varibles for variable template" << std::endl;
    for(int i=0; i<templateNames.size(); ++i){
      int j = i+fixedTemplateNames.size();
      std::cout << templateNames.at(i) << " count = " << cr->count(templateNames.at(i)) << ", signal count = " << cr_signal->count(templateNames.at(i)) << std::endl;
      templates.push_back( new RooDataHist((s_region+"cr_"+templateNames.at(i)).c_str(),(s_region+"cr_"+templateNames.at(i)).c_str(), RooArgList(*var), cr->histo(templateNames.at(i))));
      tr_vars.push_back( new RooRealVar(("tr_"+s_region+"cr_"+templateNames.at(i)).c_str(),("tr_"+s_region+"cr_"+templateNames.at(i)).c_str(), cr->count(templateNames.at(i))/cr_signal->count(templateNames.at(i))) );
      fit_vars.push_back( new RooFormulaVar(("fit_"+s_region+"cr_"+templateNames.at(i)).c_str(),("fit_"+s_region+"cr_"+templateNames.at(i)).c_str(),"@0*@1", RooArgList(*f_vars.at(j),*tr_vars.at(j) ) ) );
      pdfs.push_back( new RooHistPdf(  ("pdf_"+templateNames.at(i)+"_"+s_region+"cr_"+templateNames.at(i)).c_str(),("pdf_"+templateNames.at(i)+"_"+s_region+"cr_"+templateNames.at(i)).c_str(), RooArgList(*var), *templates.at(j) ) );
      pdfList->addOwned(*pdfs.at(j));
      varList->addOwned(*fit_vars.at(j));
    }

    pdfList->Print();
    varList->Print();
    model = new RooAddPdf( ("model_"+s_region).c_str(),("model_"+s_region).c_str(), *pdfList, *varList, kFALSE );
  }


};

#endif
