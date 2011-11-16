#ifndef CONTROLREGION_H
#define CONTROLREGION_H

#include "samples.h"
#include "ntupleReader.h"
#include "CutsLP.h"
#include <string>

class controlRegion{

 public:
  controlRegion();
 controlRegion( double lumi_, double f_a, double f_b )
   :lumi(lumi_), fa(f_a), fb(f_b){};
  ~controlRegion() {};

  double sqrtSum( double ex, double ey ){
    if(ex != 0 && ey != 0)
      return sqrt(ex*ex + ey*ey) ;
    else 
      return 0;
  }

  double cData(){return data;}  
  double cSignal(){return signal;}
  double cDYL(){return dyl;}
  double cDYB(){return dyb;}
  double cTTbar(){return ttbar;}
  double cVV(){return vv;}
  double cST(){return st;}
  double cWJETS(){return wjets;}
  double cOthers(){return others;}
  double cRest(){ return ( data-(vv+st+wjets+others) );}
  double cTotal(){return dyl+dyb+ttbar+vv+st+wjets+others;}

  double eData(){if(data>0) err_data = sqrt(data); return err_data;}  
  double eSignal(){if(bcsignal>0) err_signal = signal/sqrt(bcsignal); return err_signal;}
  double eDYL(){if(bcdyl>0) err_dyl = dyl/sqrt(bcdyl); return err_dyl;}
  double eDYB(){if(bcdyb>0) err_dyb = dyb/sqrt(bcdyb); return err_dyb;}
  double eTTbar(){if(bcttbar>0) err_ttbar = ttbar/sqrt(bcttbar); return err_ttbar;}
  double eVV(){if(bcvv>0) err_vv = vv/sqrt(bcvv); return err_vv;}
  double eST(){if(bcst>0) err_st = st/sqrt(bcst); return err_st;}
  double eWJETS(){if(bcwjets>0) err_wjets = wjets/sqrt(bcwjets); return err_wjets;}
  double eOthers(){if(bcothers>0) err_others = cOthers()/sqrt(bcothers); return err_others;}
  double eRest(){ return sqrt( eData()*eData() + eVV()*eVV() + eST()*eST() + eWJETS()*eWJETS() + eOthers()*eOthers() );}
  double eTotal(){ return sqrt( eDYL()*eDYL() + eDYB()*eDYB() + eTTbar()*eTTbar() + eVV()*eVV() + eST()*eST() + eWJETS()*eWJETS() + eOthers()*eOthers() );}

  void fill( Sample &sample, CutSample &cut,  ntupleReader &ev){
    bool ok = cut.pass( ev, sample );
    double scale = sample.scale(lumi,fa,fb);
    double weight = sample.scale(lumi,fa,fb) * cut.weight( ev , sample );
    if(!ok)
      return;
    else{
      if(sample.data)
	data++;
      else{
	if(sample.name == Signal_s){
	  signal += weight;
	  bcsignal++;
	}
	else if(sample.name == DY_s || sample.name == DYBOOSTED_s){
	  if( TMath::Abs(ev.eventFlav) != 5){
	    dyl += weight;
	    bcdyl++;
	  }
	  else if( TMath::Abs(ev.eventFlav) == 5){
	    dyb += weight;
	    bcdyb++;
	  }
	}
	else if(sample.name == TTbar_s){
	  ttbar += weight;
	  bcttbar++;
	}
	else if(sample.name == VV_s){
	  vv += weight;
	  bcvv++;
	}
	else if(sample.name == ST_s){
	  st += weight;
	  bcst++;
	}
	else if(sample.name == WJETS_s){
	  wjets += weight;
	  bcwjets++;
	}
	else{
	  std::cout << "WARNING: Others counter non zero!" << std::endl;
	  others += weight;
	  bcothers++;
	}
      }
    }
  }


  void init(){

   data=0;  
   signal=0;
   dyl=0;
   dyb=0;
   ttbar=0;
   vv=0;
   st=0;
   wjets=0;
   others=0;

   bcdata=0;  
   bcsignal=0;
   bcdyl=0;
   bcdyb=0;
   bcttbar=0;
   bcvv=0;
   bcst=0;
   bcwjets=0;
   bcothers=0;

   err_data=0;  
   err_signal=0;
   err_dyl=0;
   err_dyb=0;
   err_ttbar=0;
   err_vv=0;
   err_st=0;
   err_wjets=0;
   err_others=0;

   Run2011A_s = "Run2011A";
   Run2011B_s = "Run2011B";
   Signal_s = "ZH";
   DY_s = "DY";
   DYBOOSTED_s = "DYBOOSTED";
   TTbar_s = "TTbar";
   VV_s = "VV";
   ST_s = "ST";
   WJETS_s = "WJ";

  }
  
 private:

  double lumi;
  double fa;
  double fb;

  std::string Run2011A_s;
  std::string Run2011B_s;
  std::string Signal_s;
  std::string DY_s;
  std::string DYBOOSTED_s;
  std::string TTbar_s;
  std::string VV_s;
  std::string ST_s;
  std::string WJETS_s;

  double data;  
  double signal;
  double dyl;
  double dyb;
  double ttbar;
  double vv;
  double st;
  double wjets;
  double others;

  double bcdata;  
  double bcsignal;
  double bcdyl;
  double bcdyb;
  double bcttbar;
  double bcvv;
  double bcst;
  double bcwjets;
  double bcothers;


  double err_data;  
  double err_signal;
  double err_dyl;
  double err_dyb;
  double err_ttbar;
  double err_vv;
  double err_st;
  double err_wjets;
  double err_others;


};

#endif
