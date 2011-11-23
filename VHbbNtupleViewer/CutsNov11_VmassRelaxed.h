#ifndef CUTSLPVMASSRELAXED_H
#define CUTSLPVMASSRELAXED_H
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

// New implementations of the control region
// The signal regions must be implemented incrementally since cutflow is needed

class VlightRegionVmassRelaxedHZee: public CutSample {

  std::string name() {return "VlightRegionVmassRelaxedHZee";};
 public: Bool_t pass(ntupleReader &p){ return true;}
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
    iType = (VType)p.Vtype;
    return ( sampleCut == true
	     && p.Vtype == 1 
	     && p.V_pt > 100.
	     && p.H_mass < 250
	     && p.H_pt > 100.
	     && p.hJet_pt[0] > 20.
	     && p.hJet_pt[1] > 20.
	     && p.EVENT_json == true
	     && p.hbhe == true
	     && TMath::Abs( p.HVdPhi ) > 2.9
	     && p.CountAddJets() < 2
	     && !(p.hJet_csv[0] > CSVT || p.hJet_csv[1] > CSVT ) 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};


class TTbarRegionVmassRelaxedHZee: public CutSample {
  std::string name() {return "TTbarRegionVmassRelaxedHZee";};
 public: Bool_t pass(ntupleReader &p){ return true;}
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
    else sampleCut = false;
    return( sampleCut == true 
	    && p.Vtype == 1 
	    && p.H_pt > 100.
	    && p.H_mass < 250
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && (p.hJet_csv[0] > 0.5 && p.hJet_csv[1] > 0.5)
	    && (p.hJet_csv[0] > 0.898 || p.hJet_csv[1] > 0.898)
	    && p.EVENT_json == true
	    && p.hbhe == true
	    && ( p.triggerFlags[5] || p.triggerFlags[6] )  );
  }
  double weight(ntupleReader &p, Sample &sample) {if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};

class oldTTbarRegionVmassRelaxedHZee: public CutSample {
  std::string name() {return "oldTTbarRegionHZee";};
 public:
  Bool_t pass(ntupleReader &p){
    return( p.Vtype == 1 
	    && p.MET_et > 50.
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && p.EVENT_json == true
	    && p.hbhe == true
	    && ( p.triggerFlags[5] || p.triggerFlags[6] )  );
  }
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
    else sampleCut = false;
    return( sampleCut == true 
	    && p.Vtype == 1 
	    && p.MET_et > 50.
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && p.EVENT_json == true
	    && p.hbhe == true
	    && ( p.triggerFlags[5] || p.triggerFlags[6] )  );
  }
  double weight(ntupleReader &p, Sample &sample) {if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};


class VbbRegionVmassRelaxedHZee: public CutSample {
  std::string name() {return "VbbRegionVmassRelaxedHZee";};
 public: Bool_t pass(ntupleReader &p){ return true;}
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
    else
      sampleCut=false;
    return( sampleCut == true 
	    && p.Vtype == 1
	    && p.V_pt > 0.
	    && p.H_pt > 0.
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && ( p.hJet_csv[0] > CSVT
		 || p.hJet_csv[1] > CSVT )
	    && p.hJet_csv[0] > 0.5
	    && p.hJet_csv[1] > 0.5
	    && p.EVENT_json == true
	    && p.hbhe == true
	    && p.CountAddJets() < 2
	    //      && p. MET_et < 30
	    && ( p.H_mass < 90
		 || p.H_mass > 145 )
	    && p.H_mass < 250
	    && TMath::Abs(p.HVdPhi) > 2.9  
	    && ( p.triggerFlags[5] || p.triggerFlags[6] ) );    
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};

class SignalRegionVmassRelaxedHZee: public CutSample{
  std::string name() {return "SignalRegionVmassRelaxedHZee";};
 public: Bool_t pass(ntupleReader &p){ return true;}
  Bool_t pass(ntupleReader &p, Sample & sample){
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
    return ( p.Vtype == 1
	     && p.V_pt > 100.
	     && p.H_pt > 100.
	     && ( p.hJet_csv[0] > CSVT
		  || p.hJet_csv[1] > CSVT )
	     && p.hJet_csv[0] > 0.5
	     && p.hJet_csv[1] > 0.5
	     && p.hJet_pt[0] > 20.
	     && p.hJet_pt[1] > 20.
	     && TMath::Abs(p.HVdPhi) > 2.9
	     && p.EVENT_json == true
	     && p.hbhe == true
	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }      
};

class BDTRegionVmassRelaxedHZee: public CutSample{
  std::string name() {return "BDTRegionVmassRelaxedHZee";};
 public: Bool_t pass(ntupleReader &p){ return true;}
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
    return ( p.Vtype == 1
	     && p.hJet_pt[0] > 20. 
	     && p.hJet_pt[1] > 20. 
	     && p.hJet_csv[0] > 0.244 
	     && p.hJet_csv[1] > 0.244 
	     && p.H_pt > 70. 
	     && p.V_pt > 70. 
	     && p.CountAddJets() < 2 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

#endif
