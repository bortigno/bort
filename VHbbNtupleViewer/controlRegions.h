#ifndef CONTROLREGION_H
#define CONTROLREGION_H

#include "samples.h"
#include "ntupleReader.h"
#include "CutsLP.h"

class controlRegion{

 public:
  controlRegion();
 controlRegion( double lumi_ )
   :lumi(lumi_){};

  double cData(){return data;};  
  double cSignal(){return signal;};
  double cDYL(){return dyl;};
  double cDYB(){return dyb;};
  double cTTbar(){return ttbar;};
  double cVV(){return vv;};
  double cST(){return st;};
  double cWJETS(){return  wjets;};
  double cOthers(){return  others;};

  void Fill( Sample &sample, CutSample &cut,  ntupleReader &ev){
    bool ok = cut.pass( ev, sample );
    double weight = cut.weight( ev, sample );
    if(sample.data)
      data++;
    else{
      if(sample.name == Signal_s)
	signal += lumi*weight;
      else if(sample.name == DY_s || sample.name == DYBOOSTED_s){
	if( TMath::Abs(ev.eventFalv) != 5)
	  dyl += lumi*weight;
	else if( TMath::Abs(ev.eventFlav) == 5)
	  dyb += lumi*weight;
      }
      else if(sample.name == TTbar_s)
	ttbar += lumi*weight;
      else if(sample.name == VV_s)
	vv += lumi*weight;
      else if(sample.name == ST_s)
	st += lumi*weight;
      else if(sample.name == WJETS)
	wjets += lumi*weight;
      else{
	std::cout << "WARNING: Others counter non zero!" << std::endl;
	others += lumi*weight;
      }
    }
  };
  
 private:

  double lumi=0;
  std::string Run2011A_s("Run2011A");
  std::string Run2011B_s("Run2011B");
  std::string Signal_s("ZH");
  std::string DY_s("DY");
  std::string DYBOOSTED_s("DYBOOSTED");
  std::string TTbar_s("TTbar");
  std::string VV_s("VV");
  std::string ST_s("ST");
  std::string WJETS_s("WJETS");

  double data=0;  
  double signal=0;
  double dyl=0;
  double dyb=0;
  double ttbar=0;
  double vv=0;
  double st=0;
  double wjets=0;
  double others=0;

};

#endif
