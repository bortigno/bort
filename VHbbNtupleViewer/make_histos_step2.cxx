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
  std::cout << "Book Z" << std::endl;
  allHistosZ.push_back(new CutsAndHistos(new VlightRegionHZee,new StandardHistos));
  //   allHistosZ.push_back(new CutsAndHistos(new VlightRegionHZmumu,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new VbbRegionHZee,new StandardHistos));
  //   allHistosZ.push_back(new CutsAndHistos(new VbbRegionHZmumu,new StandardHistos));
  allHistosZ.push_back(new CutsAndHistos(new TTbarRegionHZee,new StandardHistos));
  //   allHistosZ.push_back(new CutsAndHistos(new TTbarRegionHZmumu,new StandardHistos));
  for(size_t a=0;a < allHistosZ.size(); a++)
    {
      allHistosZ[a]->book(*fout);
    }
}


int main(int argc, char **argv)
{
  std::cout << "Hello word" << std::endl;

  Double_t eventWeight=0;
  int event_all=0;
  int event_all_b=0;
  int event_all_c=0;
  int event_all_l=0;
  int s=0;
  int b=0;
  int c=0;

  std::string name(argv[2]);  
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

  //TFile f("../test/PAT.edm.root");
  //  TFile f("../test/VHbbPAT.edm_6_0_HAB.root");
  //ddTFile &f =* TFile::Open("/scratch/arizzi/VHbbPAT.edm_9_0_tPZ.root");
  TFile *fout = new TFile((name+"_histos.root").c_str(),"RECREATE");

  /*  std::vector<Histos *> histosForSignalRegions;
      histosForSignalRegions.push_back(new StandardHistos);
      histosForSignalRegions.push_back(new MCHistos);
  */

  CutsAndHistos norm(new NoCut,new CountHisto);
  std::vector<CutsAndHistos *> allHistosZ;
  prepareAllZHistos(allHistosZ,fout);

  norm.book(*fout);

  std::vector<CutsAndHistos *> allHistosBZ;
  std::vector<CutsAndHistos *> allHistosCZ;
  std::vector<CutsAndHistos *> allHistosLZ;
  CutsAndHistos normB(new NoCut,new CountHisto);
  CutsAndHistos normC(new NoCut,new CountHisto);
  CutsAndHistos normL(new NoCut,new CountHisto);
  TFile *foutB,*foutC,*foutL;
  if(splitBCLIGHT)
    {
      std::cout << "Enabling split" << std::endl;
      foutB = new TFile((name+"_histosB.root").c_str(),"RECREATE");
      foutC = new TFile((name+"_histosC.root").c_str(),"RECREATE");
      foutL = new TFile((name+"_histosL.root").c_str(),"RECREATE");
      normB.book(*foutB);
      normC.book(*foutC);
      normL.book(*foutL);
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
  
  ntupleReader event(inputFile.c_str());
  Long64_t  entries  = event.fChain->GetEntriesFast();
  //Loop on all events of this file
  for (unsigned int iEvent = 0; iEvent < entries; ++iEvent){
    event.GetEntry(iEvent);
    event_all++;   
    if(data == false)
      eventWeight = event.PUweight*event.weightTrig;
    else
      eventWeight = 1;

    norm.process(event,eventWeight);

    if(splitBCLIGHT){
      if( TMath::Abs(event.eventFlav) == 5 ){
	event_all_b++;
	normB.process(event,eventWeight);
	for(size_t a=0;a < allHistosBZ.size(); a++)         allHistosBZ[a]->process(event,eventWeight);
      }
      else if( TMath::Abs(event.eventFlav) == 4 ){
	event_all_c++;
	normC.process(event,eventWeight);
	for(size_t a=0;a < allHistosCZ.size(); a++)         allHistosCZ[a]->process(event,eventWeight);
	  
      } else {
	event_all_l++;
	normL.process(event,eventWeight);
	for(size_t a=0;a < allHistosLZ.size(); a++)         allHistosLZ[a]->process(event,eventWeight);
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
