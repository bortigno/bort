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

void plottingmacro_IVF_WSV()
{


  double fa = 0.46502;
  double fb = 0.53498;
  bool debug_ = true;

  //  std::string path("Nov10thFall11Plots/");
  //  std::string path("Nov10Fall1160MTopSlimPlots/");
  std::string path("Nov10Fall1160MTopIVFPlotsWSV_b/");

  if(debug_)
    std::cout << "Init the style form setTDRStyle" << std::endl;
  setTDRStyle();
  gStyle->SetErrorX(0.5);
  gROOT->ForceStyle();
  initOptions();
  

  if(debug_)
    std::cout << "Init the sample" << std::endl;
  //  std::vector<Sample> s = Nov10thDiJetPtUpdatedSlimHistos();
  //std::vector<Sample> s = Nov10Fall1160MTopSlimHistos();
  std::vector<Sample> s = Nov10Fall1160MTopIVFWSVHistos();

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
	  //      std::cout << subs->At(i)->GetName() << "/"  << objs->At(j)->GetName() << std::endl;
	  //TODO: select plots via regexp
	}
    }


  if(debug_)
    std::cout << "Starting plotting" << std::endl;

  std::string process;

  for(size_t i = 0 ; i < names.size() ; i++) 
    {
      
      std::map<std::string,TH1F *> grouped;
      TString n=names[i];
      //      if(!n.Contains(TRegexp("VlightRegionHZee/HiggsPtVlightRegionHZee"))) continue;
      //      if(!n.Contains(TRegexp("VlightRegionHZee/ZPtVlightRegionHZee"))) continue;
      //      if(!n.Contains(TRegexp("VlightRegionHZee"))) continue;
      //      if(!n.Contains(TRegexp("ZSVRegionHZmm"))) continue;
      //      if(!n.Contains(TRegexp("ZSVRegionHZee"))) continue;
      //      if(!n.Contains(TRegexp("ZSVRegionHZcomb"))) continue;
      //      if(!n.Contains(TRegexp("ZSVPureRegionHZcomb"))) continue;
      //      if(!n.Contains(TRegexp("ZSVTTbarPureRegionHZcomb"))) continue;

      if(n.Contains(TRegexp("RegionHWcomb")))
	process = "Z(l#nu)H(b#bar{b})";
      if(n.Contains(TRegexp("RegionHWmnu")))
	process = "W(#mu#nu)H(b#bar{b})";
      if(n.Contains(TRegexp("RegionHWenu")))
	process = "W(e#nu)H(b#bar{b})";

      if(debug_)
	std::cout << "Creating the Canvas" << std::endl;

      TCanvas *c = new TCanvas();
      c->SetLogy(false);
      c->SetTitle(names[i].c_str());

      if(debug_)
	std::cout << "Creating histograms" << std::endl;
  
      TH1F *hd = ((TH1F*)data.file()->Get(names[i].c_str()));
      hd->Sumw2();
      Options o=options[names[i]];
      //      hd->Rebin(o.rebin);
      hd->SetMarkerStyle(20);
      hd->GetXaxis()->SetLabelOffset(99);
      hd->SetYTitle(o.yaxis.c_str());
      double nbin = hd->GetNbinsX();
      double min_bin = hd->GetXaxis()->GetXmin();
      double max_bin = hd->GetXaxis()->GetXmax();
      TH1F *hmc = new TH1F("hmc","hmc", nbin, min_bin, max_bin);
      hmc->SetFillColor(kWhite);
      hmc->Sumw2();
      //      hmc->Rebin(o.rebin);

      if(debug_)
	std::cout << "Creating the THStack and Legend" << std::endl;
      THStack * sta = new THStack("sta",hd->GetTitle());
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
      //      double SF[] = {1.01,1.03,1.00};
      //      double SF[] = {1.03,1.054,1.032};
      double SF[] = {1.0,1.0,1.0};

      if(debug_){
	for(int i = 0; i< 3; ++i)
	  std::cout << "SF [" << i << "] = " << SF[i] << std::endl;
      }

      double mcIntegral=0;
      for(size_t j=0;j< s.size() ;j++) 
	{ 
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
	      //	      h->Rebin(options[names[i]].rebin);
	      if(debug_)
		std::cout << "Cloning and update legend " << std::endl;  
	      if(grouped.find(s[j].name) == grouped.end()){
		l->AddEntry(h,s[j].name.c_str(),"F");
	      }
	      std::cout << "Sample : " << s[j].name << " - Integral for plot " << names[i] << " = " << h->Integral(-10000,10000) << std::endl;
	      mcIntegral += h->Integral();
	      sta->Add(h);
	      hmc->Add(h);	      
	      //TO FIX grouped map
	      // sovrascrive histo con lo stesso nome tipo VV o ST etc...
	      grouped[s[j].name]=(TH1F *)h->Clone(("_"+names[i]).c_str());
	    }
	}

      if(debug_){
	std::cout << "Data total = " << hd->Integral() << std::endl;
	std::cout << "MC = " << mcIntegral << std::endl;
	std::cout << "Data/MC = " << hd->Integral()/mcIntegral << std::endl;
      }

      TPad * TopPad = new TPad("TopPad","Top Pad",0.,0.3,1.,1. ) ;
      TPad * BtmPad = new TPad("BtmPad","Bottom Pad",0.,0.,1.,0.313 ) ;
      TopPad->SetBottomMargin(0.02);
      BtmPad->SetTopMargin(0.0);
      BtmPad->SetFillStyle(4000);
      TopPad->SetFillStyle(4000);
      BtmPad->SetFillColor(0);
      BtmPad->SetBottomMargin(0.35);
      TopPad->Draw() ;
      BtmPad->Draw() ;
      std::cout << "hd maximum = " << hd->GetMaximum() << "  sta maximum = " << sta->GetMaximum() << std::endl;
      double maxY;
      if(hd->GetMaximum() > sta->GetMaximum()) maxY = (hd->GetMaximum())*1.5;
      else maxY = (sta->GetMaximum())*1.5;
      TopPad->cd();
      hd->Draw("E1X0");
      sta->Draw("sameHIST");
      hmc->Draw("sameE2");
      hmc->SetFillColor(2);
      hmc->SetMarkerSize(0);
      hmc->SetFillStyle(3013);
      hd->Draw("E1X0same");
      l->Draw("same");
      std::cout << "Set Maximum to = " << maxY << std::endl;
      hd->GetYaxis()->SetRangeUser(0.,maxY);
      hd->GetXaxis()->SetRangeUser(options[names[i]].min,options[names[i]].max);

      BtmPad->cd();
      std::cout << "Division" << std::endl;

      TH1D * divisionErrorBand = (TH1D*)(hmc)->Clone("divisionErrorBand");
      divisionErrorBand->Sumw2();
      divisionErrorBand->Divide(hmc);
      divisionErrorBand->Draw("E2");      
      divisionErrorBand->SetMaximum(2.49);
      divisionErrorBand->SetMinimum(0);
      divisionErrorBand->SetMarkerStyle(20);
      divisionErrorBand->SetMarkerSize(0.55);
      divisionErrorBand->GetXaxis()->SetTitleOffset(1.12);
      divisionErrorBand->GetXaxis()->SetLabelSize(0.12);
      divisionErrorBand->GetXaxis()->SetTitleSize(0.5);
      divisionErrorBand->GetYaxis()->SetTitle("Data/MC");
      divisionErrorBand->GetYaxis()->SetLabelSize(0.12);
      divisionErrorBand->GetYaxis()->SetTitleSize(0.12);
      divisionErrorBand->GetYaxis()->SetTitleOffset(0.40);
      divisionErrorBand->GetYaxis()->SetNdivisions(505);
      //divisionErrorBand->UseCurrentStyle();
      divisionErrorBand->SetFillColor(2);
      divisionErrorBand->SetFillStyle(3001);
      divisionErrorBand->SetMarkerSize(0.);

      TH1D * division = (TH1D*)(hd)->Clone("division");
      division->Sumw2();
      division->Divide(hmc);
//       division->SetMaximum(2.5);
//       division->SetMinimum(0);
//       division->SetMarkerStyle(20);
//       division->SetMarkerSize(0.55);
//       division->GetXaxis()->SetLabelSize(0.12);
//       division->GetXaxis()->SetTitleSize(0.14);
//       division->GetYaxis()->SetLabelSize(0.10);
//       division->GetYaxis()->SetTitleSize(0.10);
//      division->GetYaxis()->SetTitle("Data/MC");
      Double_t min = division->GetXaxis()->GetXmin();
      Double_t max = division->GetXaxis()->GetXmax();
      division->Draw("E1X0same");

      TLine *line = new TLine(min, 1.0, max, 1.0);
      line->SetLineColor(kRed);
      line->Draw("same");
      
      TLegend * leg3 =new TLegend(0.50,0.86,0.69,0.96);
      leg3->AddEntry(divisionErrorBand,"MC uncert. (stat.)","f");
      leg3->SetFillColor(0);
      leg3->SetLineColor(0);
      leg3->SetShadowColor(0);
      leg3->SetTextFont(62);
      leg3->SetTextSize(0.06);
      leg3->Draw();

      TPaveText *pave = new TPaveText(0.15,0.85,0.32,0.96,"brNDC");
      pave->SetTextAlign(12);
      pave->SetLineColor(0);
      pave->SetFillColor(0);
      pave->SetShadowColor(0);
      //TText *text = pave->AddText(Form("#chi_{#nu}^{2} = %.3f, K_{s} = %.3f",histDt->Chi2Test(histCopyMC5,"UWCHI2/NDF"),histDt->KolmogorovTest(histCopyMC5))); // stat + sys
      TText *text = pave->AddText(Form("#chi_{#nu}^{2} = %.3f, K_{s} = %.3f",hd->Chi2Test(hmc,"UWCHI2/NDF"),hd->KolmogorovTest(hmc))); // stat only
      text->SetTextFont(62);
      text->SetTextSize(0.08);
      pave->Draw();

      TopPad->cd();
      TLatex latex;
      latex.SetNDC();
      latex.SetTextAlign(12);
      latex.SetTextSize(0.052);
      latex.DrawLatex(0.17,0.89,"CMS Preliminary");
      latex.SetTextSize(0.04);
      latex.DrawLatex(0.17,0.84,"#sqrt{s} = 7 TeV, L = 4.7 fb^{-1}");
      //      latex.DrawLatex(0.17,0.79,"Z(e^{+}e^{-})H(b#bar{b})");
      latex.DrawLatex(0.17,0.79,process.c_str());
      c->Update();
      std::string cName= hd->GetName();
      cName += "_bare.pdf";
      cName = path+cName;
      c->Print(cName.c_str(),"pdf");

//       std::cout << names[i] << " d: " <<  hd->Integral() << " ";
//       THStack * sta2 = new THStack("sta2",hd->GetTitle());
//       float tot=0;
//       float toterr2=0;

//       if(debug_)
// 	std::cout << "Putting the iterator in the for loop" << std::endl;
//       for(std::map<std::string,TH1F *>::reverse_iterator it=grouped.rbegin(); it!=grouped.rend();++it)
//  	{
// 	  if(debug_)
// 	    std::cout << "Using the iterator" << std::endl;
// 	  std::cout << (*it).first << " " << (*it).second->Integral() << " | " << std::endl ;
// 	  if((*it).second->GetEntries() > 0) {
// 	    float er=1.*sqrt((*it).second->GetEntries())/(*it).second->GetEntries()*(*it).second->Integral();
// 	    toterr2+=er*er;
// 	  }
// 	  tot+=(*it).second->Integral();
// 	  sta2->Add(it->second);
//  	}
//       std::cout << " Tot: " << tot << "+-" << sqrt(toterr2) <<  " SF: " << hd->Integral()/tot << std::endl;
//       TCanvas *c2 = new TCanvas();
//       c2->SetTitle(names[i].c_str());
//       std::cout << "hd maximum = " << hd->GetMaximum() << "  sta2 maximum = " << sta2->GetMaximum() << std::endl;
//       if(hd->GetMaximum() > sta2->GetMaximum()) maxY =  hd->GetBinContent(hd->GetMaximumBin()) * 1.5;
//       else maxY = ( sta2->GetMaximum())*1.5;
//       //      hd->Draw("E1"); 
//       sta2->Draw("PADSHIST");
//       //    hd->Draw("E1same");
//       //      l->Draw("same");
//       std::cout << "Set Maximum to = " << maxY << std::endl;
//       hd->GetYaxis()->SetRangeUser(0.,maxY);
//       hd->GetXaxis()->SetRangeUser(options[names[i]].min,options[names[i]].max);
//       c2->Update();

//       std::string c2Name = hd->GetName();
//       c2Name = path+c2Name;
//       c2Name += "_norm.pdf";
//       c2->Print(c2Name.c_str(),"pdf");  

    }

}
