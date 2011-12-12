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


void plottingmacro()
{


  double fa = 0.46502;
  double fb = 0.53498;
  bool debug_ = true;

  //  std::string path("Nov10thFall11Plots/");
  std::string path("Nov10Fall1160MTopSlimPlots/");

  if(debug_)
    std::cout << "Init the style form setTDRStyle" << std::endl;
  setTDRStyle();
  gROOT->ForceStyle();
  initOptions();

  if(debug_)
    std::cout << "Init the sample" << std::endl;
  //  std::vector<Sample> s = Nov10thDiJetPtUpdatedSlimHistos();
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
	  //      std::cout << subs->At(i)->GetName() << "/"  << objs->At(j)->GetName() << std::endl;
	  //TODO: select plots via regexp
	}
    }


  if(debug_)
    std::cout << "Starting plotting" << std::endl;

  for(size_t i = 0 ; i < names.size() ; i++) 
    {
      
      std::map<std::string,TH1F *> grouped;
      TString n=names[i];
      //if(!n.Contains(TRegexp("VlightRegionHZee/HiggsPtVlightRegionHZee"))) continue;
      //      if(!n.Contains(TRegexp("VlightRegionHZee"))) continue;

      if(debug_)
	std::cout << "Creating the Canvas" << std::endl;

      TCanvas *c = new TCanvas();
      c->SetLogy(false);
      c->SetTitle(names[i].c_str());

      if(debug_)
	std::cout << "Creating histograms" << std::endl;
  
      TH1F *hd = ((TH1F*)data.file()->Get(names[i].c_str()));
      Options o=options[names[i]];
      hd->Rebin(o.rebin);
      hd->SetMarkerStyle(20);
      //      hd->Draw("E1");
      hd->SetYTitle(o.yaxis.c_str());
      double nbin = hd->GetNbinsX();
      double min_bin = hd->GetMinimumBin();
      double max_bin = hd->GetMaximumBin();
      TH1F *hmc = new TH1F("hmc","hmc", nbin, min_bin, max_bin);
      hmc->Rebin(o.rebin);

      if(debug_)
	std::cout << "Creating the THStack and Legend" << std::endl;
      THStack * sta = new THStack("sta",hd->GetTitle());
      TLegend * l = new TLegend(o.legendx1,o.legendy1,o.legendx2,o.legendy2); //0.7,0.1,0.9,0.6);
      l->SetFillColor(kWhite);
      l->SetBorderSize(0);
      if(debug_)
	std::cout << "Adding data to the legend" << std::endl;  
      l->AddEntry(hd, "Data","LP");
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
	      if(debug_)
		std::cout << "Created TH1F from file " << s[j].name << std::endl;  
	      if(debug_){
		std::cout << "Scaling : " << s[j].scale(data.lumi(),fa,fb) << std::endl;  
		std::cout << "Scaling with SF : " << s[j].scale(data.lumi(),fa,fb,SF) << std::endl;  
		std::cout << "Histo integral before scaling = " << h->Integral() << std::endl;
	      }
	      h->Scale(s[j].scale(data.lumi(),fa,fb,SF));
	      if(debug_){
		std::cout << "Managing style... " << std::endl;  
		std::cout << "Histo integral after scaling = " << h->Integral() << std::endl;
	      }
	      h->SetLineWidth(1.);
	      h->SetFillColor(s[j].color);
	      h->SetLineColor(s[j].color);
	      h->Rebin(options[names[i]].rebin);

	      if(grouped.find(s[j].name) == grouped.end()) {
		if(debug_)
		  std::cout << "Cloning and update legend " << std::endl;  
		grouped[s[j].name]=(TH1F *)h->Clone(("_"+names[i]).c_str());
		//		std::cout << "Sample : " << s[j].name << " - Integral for plot " << names[i] << " = " << h->Integral(h->GetXaxis()->GetFirst(),h->GetXaxis()->GetLast()) << std::endl;
		std::cout << "Sample : " << s[j].name << " - Integral for plot " << names[i] << " = " << h->Integral(-10000,10000) << std::endl;
		l->AddEntry(h,s[j].name.c_str(),"F");
		mcIntegral += h->Integral();
		sta->Add(h);
		hmc->Add(h);
	      }
// 	      else
// 		{
// 		  grouped[s[j].name]=(TH1F *)h->Clone(("_"+names[i]).c_str());
//	      l->AddEntry(h,s[j].name.c_str(),"F");
//	      grouped[s[j].name]->Add(h);
// 		}
	    }
	  //h->Draw("same");
	}

      if(debug_){
	std::cout << "Data total = " << hd->Integral() << std::endl;
	std::cout << "MC = " << mcIntegral << std::endl;
	std::cout << "Data/MC = " << hd->Integral()/mcIntegral << std::endl;
      }

      TPad * TopPad = new TPad("TopPad","Top Pad",0.01,0.3,0.99,1.00 ) ;
      TPad * BtmPad = new TPad("BtmPad","Bottom Pad",0.01,0.01,0.99,0.25 ) ;
      TopPad->SetBottomMargin(0.05) ;
      BtmPad->SetTopMargin(0.05) ;
      BtmPad->SetBottomMargin(0.15);
      TopPad->Draw() ;
      BtmPad->Draw() ;
      std::cout << "hd maximum = " << hd->GetMaximum() << "  sta maximum = " << sta->GetMaximum() << std::endl;
      double maxY;
      if(hd->GetMaximum() > sta->GetMaximum()) maxY = (hd->GetMaximum())*1.3;
      else maxY = (sta->GetMaximum())*1.3;
      TopPad->cd();
      hd->Draw("E1");
      sta->Draw("same");
      hd->Draw("E1same");
      l->Draw("same");
      std::cout << "Set Maximum to = " << maxY << std::endl;
      hd->GetYaxis()->SetRangeUser(0.,maxY);
      hd->GetXaxis()->SetRangeUser(options[names[i]].min,options[names[i]].max);

      BtmPad->cd();
      std::cout << "Division" << std::endl;
      TH1D * division = (TH1D*)(hd)->Clone("division");
      //TH1D * division = new TH1D();
      division->Sumw2();
      division->Divide(hmc);
      division->SetMaximum(2.);
      division->SetMinimum(0);
      division->SetMarkerStyle(20);
      division->GetXaxis()->SetLabelSize(0.06);
      division->GetXaxis()->SetTitleSize(0.06);
      division->GetYaxis()->SetLabelSize(0.06);
      division->GetYaxis()->SetTitle("Data/MC");
      Double_t min = division->GetXaxis()->GetXmin();
      Double_t max = division->GetXaxis()->GetXmax();
      division->Draw("E1");

      TLine *line = new TLine(min, 1.0, max, 1.0);
      line->SetLineColor(kRed);
      line->Draw("same");

      c->Update();
      std::string cName= hd->GetName();
      cName += "_bare.pdf";
      cName = path+cName;
      c->Print(cName.c_str(),"pdf");



      std::cout << names[i] << " d: " <<  hd->Integral() << " ";
      THStack * sta2 = new THStack("sta2",hd->GetTitle());
      float tot=0;
      float toterr2=0;


      if(debug_)
	std::cout << "Putting the iterator in the for loop" << std::endl;
      for(std::map<std::string,TH1F *>::reverse_iterator it=grouped.rbegin(); it!=grouped.rend();++it)
 	{
	  if(debug_)
	    std::cout << "Using the iterator" << std::endl;
	  std::cout << (*it).first << " " << (*it).second->Integral() << " | " << std::endl ;
	  if((*it).second->GetEntries() > 0) {
	    float er=1.*sqrt((*it).second->GetEntries())/(*it).second->GetEntries()*(*it).second->Integral();
	    toterr2+=er*er;
	  }
	  tot+=(*it).second->Integral();
	  sta2->Add(it->second);
 	}
      std::cout << " Tot: " << tot << "+-" << sqrt(toterr2) <<  " SF: " << hd->Integral()/tot << std::endl;
      TCanvas *c2 = new TCanvas();
      c2->SetTitle(names[i].c_str());
      std::cout << "hd maximum = " << hd->GetMaximum() << "  sta2 maximum = " << sta2->GetMaximum() << std::endl;
      if(hd->GetMaximum() > sta2->GetMaximum()) maxY =  hd->GetBinContent(hd->GetMaximumBin()) * 1.3;
      else maxY = ( sta2->GetMaximum())*1.3;
      //      hd->Draw("E1"); 
      sta2->Draw("PADS");
      //    hd->Draw("E1same");
      //      l->Draw("same");
      std::cout << "Set Maximum to = " << maxY << std::endl;
      hd->GetYaxis()->SetRangeUser(0.,maxY);
      hd->GetXaxis()->SetRangeUser(options[names[i]].min,options[names[i]].max);
      c2->Update();


      std::string c2Name = hd->GetName();
      c2Name = path+c2Name;
      c2Name += "_norm.pdf";
      c2->Print(c2Name.c_str(),"pdf");  

    }

}
