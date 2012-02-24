#ifndef CUTSSYS_H
#define CUTSSYS_H
#include "CutsAndHistos.h"
#include "ntupleReader.h"
#include <TH1F.h>
#include <sstream>
#include "samples.h"
#include "TKey.h"

#define CSVM 0.679
#define CSVL 0.244
#define CSVT 0.898
#define fA 0.46502
#define fB 0.53498

//SYSTEMATICS

class BDTSystJecUPRegionHZee: public CutSample{
  std::string name() {return "BDTSystJecUPRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } // systematics without sample info have no meaning
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_pt_0, hJet_pt_1;
    if(sample.data == true){
      hJet_pt_0 = p.hJet_pt[0];
      hJet_pt_1 = p.hJet_pt[1];
    }
    else{
      hJet_pt_0 = p.hJet_pt_jecUP(0);
      hJet_pt_1 = p.hJet_pt_jecUP(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && hJet_pt_0 > 20. 
	     && hJet_pt_1 > 20.
	     && p.hJet_csv[0] > 0.244 
	     && p.hJet_csv[1] > 0.244 
	     && p.H_jecUP().Pt() > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_jecUP().M() < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystJecUPZbbControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystJecUPZbbControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } //need sample info for systematics
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_pt_0, hJet_pt_1;
    if(sample.data == true){
      hJet_pt_0 = p.hJet_pt[0];
      hJet_pt_1 = p.hJet_pt[1];
    }
    else{
      hJet_pt_0 = p.hJet_pt_jecUP(0);
      hJet_pt_1 = p.hJet_pt_jecUP(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && hJet_pt_0 > 20. 
	     && hJet_pt_1 > 20. 
	     && p.hJet_csv[0] > CSVL
	     && p.hJet_csv[1] > CSVL
	     && p.V_pt < 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_jecUP().M() < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystJecUPZlightControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystJecUPZlightControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_pt_0, hJet_pt_1;
    if(sample.data == true){
      hJet_pt_0 = p.hJet_pt[0];
      hJet_pt_1 = p.hJet_pt[1];
    }
    else{
      hJet_pt_0 = p.hJet_pt_jecUP(0);
      hJet_pt_1 = p.hJet_pt_jecUP(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && hJet_pt_0 > 20. 
	     && hJet_pt_1 > 20.
	     && p.hJet_csv[0] < CSVL
	     && p.hJet_csv[1] < CSVL
	     && p.V_pt > 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_jecUP().M() < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystJecUPTTbarControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystJecUPTTbarControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_pt_0, hJet_pt_1;
    if(sample.data == true){
      hJet_pt_0 = p.hJet_pt[0];
      hJet_pt_1 = p.hJet_pt[1];
    }
    else{
      hJet_pt_0 = p.hJet_pt_jecUP(0);
      hJet_pt_1 = p.hJet_pt_jecUP(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && hJet_pt_0 > 20. 
	     && hJet_pt_1 > 20.
	     && p.hJet_csv[0] > CSVL 
	     && p.hJet_csv[1] > CSVL 
	     && p.H_jecUP().Pt() > 100. 
	     //	     && p.V_pt > 100. 
	     && p.V_mass > 50.
 	     && ( p.V_mass > 105.
 		  || p.V_mass < 75. )
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};




class BDTSystJecDOWNRegionHZee: public CutSample{
  std::string name() {return "BDTSystJecDOWNRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } // systematics without sample info have no meaning
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_pt_0, hJet_pt_1;
    if(sample.data == true){
      hJet_pt_0 = p.hJet_pt[0];
      hJet_pt_1 = p.hJet_pt[1];
    }
    else{
      hJet_pt_0 = p.hJet_pt_jecDOWN(0);
      hJet_pt_1 = p.hJet_pt_jecDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && hJet_pt_0 > 20. 
	     && hJet_pt_1 > 20.
	     && p.hJet_csv[0] > 0.244
	     && p.hJet_csv[1] > 0.244
	     && p.H_jecDOWN().Pt() > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_jecDOWN().M() < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};


class BDTSystJecDOWNZbbControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystJecDOWNZbbControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } //need sample info for systematics
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_pt_0, hJet_pt_1;
    if(sample.data == true){
      hJet_pt_0 = p.hJet_pt[0];
      hJet_pt_1 = p.hJet_pt[1];
    }
    else{
      hJet_pt_0 = p.hJet_pt_jecDOWN(0);
      hJet_pt_1 = p.hJet_pt_jecDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && hJet_pt_0 > 20. 
	     && hJet_pt_1 > 20. 
	     && p.hJet_csv[0] > CSVL
	     && p.hJet_csv[1] > CSVL
	     && p.V_pt < 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_jecDOWN().M() < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystJecDOWNZlightControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystJecDOWNZlightControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_pt_0, hJet_pt_1;
    if(sample.data == true){
      hJet_pt_0 = p.hJet_pt[0];
      hJet_pt_1 = p.hJet_pt[1];
    }
    else{
      hJet_pt_0 = p.hJet_pt_jecDOWN(0);
      hJet_pt_1 = p.hJet_pt_jecDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && hJet_pt_0 > 20. 
	     && hJet_pt_1 > 20.
	     && p.hJet_csv[0] < CSVL
	     && p.hJet_csv[1] < CSVL
	     && p.V_pt > 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_jecDOWN().M() < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystJecDOWNTTbarControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystJecDOWNTTbarControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_pt_0, hJet_pt_1;
    if(sample.data == true){
      hJet_pt_0 = p.hJet_pt[0];
      hJet_pt_1 = p.hJet_pt[1];
    }
    else{
      hJet_pt_0 = p.hJet_pt_jecDOWN(0);
      hJet_pt_1 = p.hJet_pt_jecDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && hJet_pt_0 > 20. 
	     && hJet_pt_1 > 20. 
	     && p.hJet_csv[0] > CSVL 
	     && p.hJet_csv[1] > CSVL 
	     && p.H_jecDOWN().Pt() > 100. 
	     //	     && p.V_pt > 100. 
	     && p.V_mass > 50.
 	     && ( p.V_mass > 105.
 		  || p.V_mass < 75. )
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};



//BTAG Systematics

class BDTSystBtagUPRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagUPRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } // systematics without sample info have no meaning
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data){
      hJet_csv_0 = p.hJet_csv[0]; 
      hJet_csv_1 = p.hJet_csv[1];
    }else{
      hJet_csv_0 = p.hJet_csvUp[0]; 
      hJet_csv_1 = p.hJet_csvUp[1];
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 > 0.244 
	     && hJet_csv_1 > 0.244 
	     && p.H_pt > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystBtagUPZbbControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagUPZbbControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } //need sample info for systematics
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cUP(0);
      hJet_csv_1 = p.hJet_csv_cUP(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && hJet_csv_0 > CSVL 
	     && hJet_csv_1 > CSVL
	     && p.V_pt < 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystBtagUPZlightControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagUPZlightControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cUP(0);
      hJet_csv_1 = p.hJet_csv_cUP(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 < CSVL
	     && hJet_csv_1 < CSVL
	     && p.V_pt > 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystBtagUPTTbarControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagUPTTbarControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cUP(0);
      hJet_csv_1 = p.hJet_csv_cUP(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 > CSVL 
	     && hJet_csv_1 > CSVL 
	     && p.H_pt > 100. 
	     //	     && p.V_pt > 100. 
	     && p.V_mass > 50.
 	     && ( p.V_mass > 105.
 		  || p.V_mass < 75. )
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};




class BDTSystBtagDOWNRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagDOWNRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } // systematics without sample info have no meaning
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cDOWN(0);
      hJet_csv_1 = p.hJet_csv_cDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 > 0.244 
	     && hJet_csv_1 > 0.244 
	     && p.H_pt > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};


class BDTSystBtagDOWNZbbControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagDOWNZbbControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } //need sample info for systematics
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cDOWN(0);
      hJet_csv_1 = p.hJet_csv_cDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && hJet_csv_0 > CSVL
	     && hJet_csv_1 > CSVL
	     && p.V_pt < 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystBtagDOWNZlightControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagDOWNZlightControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cDOWN(0);
      hJet_csv_1 = p.hJet_csv_cDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 < CSVL
	     && hJet_csv_1 < CSVL
	     && p.V_pt > 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystBtagDOWNTTbarControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagDOWNTTbarControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cDOWN(0);
      hJet_csv_1 = p.hJet_csv_cDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 > CSVL 
	     && hJet_csv_1 > CSVL 
	     && p.H_pt > 100. 
	     //	     && p.V_pt > 100. 
	     && p.V_mass > 50.
 	     && ( p.V_mass > 105.
 		  || p.V_mass < 75. )
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

//BTAG Systematics

class BDTSystBtagFUPRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagFUPRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } // systematics without sample info have no meaning
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data){
      hJet_csv_0 = p.hJet_csv[0]; 
      hJet_csv_1 = p.hJet_csv[1];
    }else{
      hJet_csv_0 = p.hJet_csv_cFUP(0); 
      hJet_csv_1 = p.hJet_csv_cFUP(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 > 0.244 
	     && hJet_csv_1 > 0.244 
	     && p.H_pt > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystBtagFUPZbbControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagFUPZbbControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } //need sample info for systematics
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cFUP(0);
      hJet_csv_1 = p.hJet_csv_cFUP(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && hJet_csv_0 > CSVL
	     && hJet_csv_1 > CSVL
	     && p.V_pt < 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystBtagFUPZlightControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagFUPZlightControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cFUP(0);
      hJet_csv_1 = p.hJet_csv_cFUP(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 < CSVL
	     && hJet_csv_1 < CSVL
	     && p.V_pt > 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystBtagFUPTTbarControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagFUPTTbarControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cFUP(0);
      hJet_csv_1 = p.hJet_csv_cFUP(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 > CSVL 
	     && hJet_csv_1 > CSVL 
	     && p.H_pt > 100. 
	     //	     && p.V_pt > 100. 
	     && p.V_mass > 50.
 	     && ( p.V_mass > 105.
 		  || p.V_mass < 75. )
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};




class BDTSystBtagFDOWNRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagFDOWNRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } // systematics without sample info have no meaning
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cFDOWN(0);
      hJet_csv_1 = p.hJet_csv_cFDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 > 0.244 
	     && hJet_csv_1 > 0.244 
	     && p.H_pt > 100. 
	     && p.V_pt > 100. 
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};


class BDTSystBtagFDOWNZbbControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagFDOWNZbbControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; } //need sample info for systematics
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cFDOWN(0);
      hJet_csv_1 = p.hJet_csv_cFDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && hJet_csv_0 > CSVL 
	     && hJet_csv_1 > CSVL
	     && p.V_pt < 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystBtagFDOWNZlightControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagFDOWNZlightControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cFDOWN(0);
      hJet_csv_1 = p.hJet_csv_cFDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 < CSVL
	     && hJet_csv_1 < CSVL
	     && p.V_pt > 100.
	     && p.V_mass > 75. 
	     && p.V_mass < 105 && p.H_mass < 250 
	     //	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

class BDTSystBtagFDOWNTTbarControlRegionHZee: public CutSample{
  std::string name() {return "BDTSystBtagFDOWNTTbarControlRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){ return false; }
  Bool_t pass(ntupleReader &p, Sample &sample){
    bool sampleCut = false;
    bool boost = false;
    bool isB = false;
    if(p.genZpt >= 120)
      boost = true;
    if(p.eventFlav == 5)
      isB = true;
    std::string DY("DY");
    std::string DYBOOSTED("DYBOOSTED");
    if( sample.name == DY && !boost )
      sampleCut = true;
    else if( sample.name == DYBOOSTED && boost )
      sampleCut = true;
    else if( sample.name != DY && sample.name != DYBOOSTED )
      sampleCut = true;
    else sampleCut=false;
    double hJet_csv_0, hJet_csv_1;
    if(sample.data == true){
      hJet_csv_0 = p.hJet_csv[0];
      hJet_csv_1 = p.hJet_csv[1];
    }
    else{
      hJet_csv_0 = p.hJet_csv_cFDOWN(0);
      hJet_csv_1 = p.hJet_csv_cFDOWN(1);
    }
    return ( sampleCut == true
	     && p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20.
	     && hJet_csv_0 > CSVL 
	     && hJet_csv_1 > CSVL 
	     && p.H_pt > 100. 
	     //	     && p.V_pt > 100. 
	     && p.V_mass > 50.
 	     && ( p.V_mass > 105.
 		  || p.V_mass < 75. )
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};


#endif
