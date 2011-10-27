#include <samples.h>
#include <iostream> 
#include <TCanvas.h>
#include <TRegexp.h>
#include <TLegend.h>
#include <THStack.h>
#include "setTDRStyle.C"
#include <TROOT.h>
#include "customize.h"


void plottingmacro()
{

  bool debug_ = true;

  if(debug_)
    std::cout << "Init the style form setTDRStyle" << std::endl;
  setTDRStyle();
  gROOT->ForceStyle();
  initOptions();
  std::map<std::string,TH1F *> grouped;

  if(debug_)
    std::cout << "Init the sample" << std::endl;
  std::vector<Sample> s = samples();
  Sample data(1,"fake data","S1.root",0,true,1000);

  if(debug_)
    std::cout << "Init the data sample" << std::endl;
  for(size_t i=0;i< s.size();i++) if(s[i].data) {data=s[i];break;}

  if(debug_)
    std::cout << "Ls data sample" << std::endl;
  data.file()->ls(); 

  if(debug_)
    std::cout << "Init the mc sample" << std::endl;
  for(size_t i=0;i< s.size();i++) s[i].dump(data.lumi());

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
      TString n=names[i];
      //      if(!n.Contains(TRegexp(".*light.*"))) continue;

      if(debug_)
	std::cout << "Creating the Canvas" << std::endl;

      TCanvas *c = new TCanvas();
      c->SetLogy(true);
      c->SetTitle(names[i].c_str());

      if(debug_)
	std::cout << "Creating histograms" << std::endl;
  
      TH1F *hd = ((TH1F*)data.file()->Get(names[i].c_str()));
      Options o=options[names[i]];
      hd->Rebin(o.rebin);
      hd->SetMarkerStyle(20);
      hd->Draw("E1");
      hd->SetYTitle(o.yaxis.c_str());

      if(debug_)
	std::cout << "Creating the THStack and Legend" << std::endl;
      THStack * sta = new THStack("sta",hd->GetTitle());
      TLegend * l = new TLegend(o.legendx1,o.legendy1,o.legendx2,o.legendy2); //0.7,0.1,0.9,0.6);
      if(debug_)
	std::cout << "Adding entry to the THStack" << std::endl;  
      l->AddEntry(hd, "Data","LP");

      for(size_t j=0;j< s.size() ;j++) 
	{ 
	  if(!s[j].data) 
	    {
	      TH1F * h = ((TH1F*)s[j].file()->Get(names[i].c_str()));
	      h->Scale(s[j].scale(data.lumi()));
	      h->SetLineWidth(1.);
	      h->SetFillColor(s[j].color);
	      h->Rebin(options[names[i]].rebin);
	      if(grouped.find(s[j].name)!=grouped.end()) {
		grouped[s[j].name]=(TH1F *)h->Clone(("_"+names[i]).c_str());
		l->AddEntry(h,s[j].name.c_str(),"F");
	      }
	      else
		{
		  grouped[s[j].name]=(TH1F *)h->Clone(("_"+names[i]).c_str());
		}
	      sta->Add(h);
	      //     h->Draw("same");
	    }
	}
      sta->Draw("same");
      hd->Draw("E1same");
      hd->GetYaxis()->SetRangeUser(options[names[i]].min,options[names[i]].max);
      l->Draw();

      std::cout << names[i] << " d: " <<  hd->Integral() << " ";
      THStack * sta2 = new THStack("sta2",hd->GetTitle());
      float tot=0;
      float toterr2=0;


      if(debug_)
	std::cout << "Putting the iterator in the for loop" << std::endl;
      for(std::map<std::string,TH1F *>::iterator it=grouped.begin(); it!=grouped.end();++it)
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
      c = new TCanvas();
      if (hd->GetMaximum() > sta2->GetMaximum()) sta2->SetMaximum(hd->GetMaximum());
      else sta2->SetMaximum(sta2->GetMaximum());
      sta2->Draw();
      hd->Draw("E1,same");
      sta2->GetYaxis()->SetRangeUser(options[names[i]].min,options[names[i]].max);
      hd->GetYaxis()->SetRangeUser(options[names[i]].min,options[names[i]].max);
      l->Draw();


      

      c->Print("Test.pdf");
   
   

    }

}
