#include <TROOT.h>
#include <TApplication.h>
#include <TH1.h>
#include <iostream>
#include "CutsAndHistos.h"
#include "Histos.h"
//#include "Cuts200X.h"
#include "CutsLP.h"
#include "ntupleReader.h"

void prepareAllZHistos(std::vector<CutsAndHistos *> & allHistosZ,TFile *fout  )
{
  std::string Zee110("ZH110");
  std::cout << "Book Z" << std::endl;
  allHistosZ.push_back(new CutsAndHistos(new VlightRegionHZee,new StandardHistos));
  //  allHistosZ.push_back(new CutsAndHistos(new VlightRegionHZee,new MVAHistos(Zee110)));
  allHistosZ.push_back(new CutsAndHistos(new VbbRegionHZee,new StandardHistos));
  //  allHistosZ.push_back(new CutsAndHistos(new VbbRegionHZee,new MVAHistos(Zee110)));
  allHistosZ.push_back(new CutsAndHistos(new TTbarRegionHZee,new StandardHistos));
  //  allHistosZ.push_back(new CutsAndHistos(new TTbarRegionHZee,new MVAHistos(Zee110)));
  allHistosZ.push_back(new CutsAndHistos(new SignalRegionHZee,new StandardHistos));
  //  allHistosZ.push_back(new CutsAndHistos(new SignalRegionHZee,new MVAHistos(Zee110)));
  for(size_t a=0;a < allHistosZ.size(); a++)
    {
      allHistosZ[a]->book(*fout);
    }
}


int main(int argc, char **argv)
{
  std::cout << "Hello word" << std::endl;

  bool verbose_ = true;

  Double_t eventWeight=0;
  int event_all=0;
  int event_all_b=0;
  int event_all_c=0;
  int event_all_l=0;
  int s=0;
  int b=0;
  int c=0;

  std::string name(argv[2]);
  std::cout << name << std::endl;
  std::string procType(argv[3]);

  if(argc < 4)
    {
      std::cout << "Usage:\n   make_histos inputFileList outputPrefix [mc|mcSpli|data]" << std::endl;
      exit(1);
    }

  bool splitBCLIGHT=true;
  bool data=true;

  if(procType == "data") { data=true; splitBCLIGHT=false;}
  if(procType == "mc") { data=false; splitBCLIGHT=false;}
  if(procType == "mcSplit") { data=false; splitBCLIGHT=true;}
  
  //  mkdir("./Histograms",755);

  if(verbose_)
    std::cout << "opening the output file" << std::endl;
  //TFile f("../test/PAT.edm.root");
  //  TFile f("../test/VHbbPAT.edm_6_0_HAB.root");
  //ddTFile &f =* TFile::Open("/scratch/arizzi/VHbbPAT.edm_9_0_tPZ.root");
  TFile *fout = new TFile((name+"_histos.root").c_str(),"RECREATE");
  if(verbose_)
    std::cout << "Creating the histograms" << std::endl;
  TH1F * countAll = new TH1F("Count","Count",1,0,2);
  TH1F * countAllWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);

  if(verbose_)
    std::cout << "Preparing the Z histos" << std::endl;
  std::vector<CutsAndHistos *> allHistosZ;
  prepareAllZHistos(allHistosZ,fout);

  if(verbose_)
    std::cout << "Preparing the plitted histos" << std::endl;
  std::vector<CutsAndHistos *> allHistosBZ;
  std::vector<CutsAndHistos *> allHistosCZ;
  std::vector<CutsAndHistos *> allHistosLZ;
  TFile *foutB,*foutC,*foutL;
  TH1F *countB, *countBWithPU,*countC, *countCWithPU,*countL, *countLWithPU;
  if(splitBCLIGHT)
    {
      std::cout << "Enabling split" << std::endl;
      foutB = new TFile((name+"_histosB.root").c_str(),"RECREATE");
      countB = new TH1F("Count","Count",1,0,2);
      countBWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);
      foutC = new TFile((name+"_histosC.root").c_str(),"RECREATE");
      countC = new TH1F("Count","Count",1,0,2);
      countCWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);
      foutL = new TFile((name+"_histosL.root").c_str(),"RECREATE");
      countL = new TH1F("Count","Count",1,0,2);
      countLWithPU =  new TH1F("CountWithPU","CountWithPU",1,0,2);
      prepareAllZHistos(allHistosBZ,foutB);
      prepareAllZHistos(allHistosCZ,foutC);
      prepareAllZHistos(allHistosLZ,foutL);

    }

  std::string inputFile(argv[1]);
  std::cout << "Start processing " << inputFile  << " files" << std::endl;

  // open input file (can be located on castor)
  TFile* f = TFile::Open(inputFile.c_str());
  if(f==0){
    std::cerr << "File not found " << std::endl;
    std::cerr << "Please check the path of this file " << inputFile << std::endl;
    return -1;
  }

  countAll->Add((TH1F*)f->Get("Count"));
  countAllWithPU->Add((TH1F*)f->Get("CountWithPU"));
  countB->Add((TH1F*)f->Get("Count"));
  countBWithPU->Add((TH1F*)f->Get("CountWithPU"));
  countC->Add((TH1F*)f->Get("Count"));
  countCWithPU->Add((TH1F*)f->Get("CountWithPU"));
  countL->Add((TH1F*)f->Get("Count"));
  countLWithPU->Add((TH1F*)f->Get("CountWithPU"));

  ntupleReader event(inputFile.c_str());
  bool trigger = true;
  Long64_t  entries  = event.fChain->GetEntriesFast();
  //Loop on all events of this file
  for (unsigned int iEvent = 0; iEvent < entries; ++iEvent){
    event.GetEntry(iEvent);
    event_all++;
    if(data == false)
      eventWeight = event.PUweight*event.weightTrig;
    else{
      eventWeight = 1;
      trigger = false;
      if( ( event.triggerFlags[5] 
	    || event.triggerFlags[6] ) )
	trigger = true;
    }
    if(trigger == false)
      continue;

    if(splitBCLIGHT){
      if( TMath::Abs(event.eventFlav) == 5 ){
	event_all_b++;
	for(size_t a=0;a < allHistosBZ.size(); a++) 
	  allHistosBZ[a]->process(event,eventWeight);
      }
      else if( TMath::Abs(event.eventFlav) == 4 ){
	event_all_c++;
	for(size_t a=0;a < allHistosCZ.size(); a++)   
	  allHistosCZ[a]->process(event,eventWeight);
      } else {
	event_all_l++;
	for(size_t a=0;a < allHistosLZ.size(); a++)    
	  allHistosLZ[a]->process(event,eventWeight);
      }
    }
      
    for(size_t a=0;a < allHistosZ.size(); a++)
      {
	allHistosZ[a]->process(event,eventWeight);
      }
      
  }
    
  fout->Write();
  fout->Close();
  
  if(splitBCLIGHT){
    foutB->Write();
    foutB->Close();
    
    foutC->Write();
    foutC->Close();
    
    foutL->Write();
    foutL->Close();   
  }

  f->Close();
  std::cout << "TOT: " << event_all << " b: " << event_all_b << " c: "<<  event_all_c <<" l: " << event_all_l <<  std::endl;

  
  return 0;
}
