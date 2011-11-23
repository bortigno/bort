#ifndef CUTSLPADDJETRELAXED_H
#define CUTSLPADDJETRELAXED_H
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

class VlightRegionAddJetRelaxedHZee: public CutSample {

  std::string name() {return "VlightRegionAddJetRelaxedHZee";};
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
	     && p.V_mass > 75.
	     && p.V_mass < 105.
	     && p.V_pt > 100.
	     && p.H_mass < 250
	     && p.H_pt > 100.
	     && p.hJet_pt[0] > 20.
	     && p.hJet_pt[1] > 20.
	     && p.EVENT_json == true
	     && p.hbhe == true
	     && TMath::Abs( p.HVdPhi ) > 2.9
	     && !(p.hJet_csv[0] > CSVT || p.hJet_csv[1] > CSVT ) 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample){ if( sample.data ) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};


class TTbarRegionAddJetRelaxedHZee: public CutSample {
  std::string name() {return "TTbarRegionAddJetRelaxedHZee";};
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
	    && ( p.V_mass > 105.
		 || p.V_mass < 75. )
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


class VbbRegionAddJetRelaxedHZee: public CutSample {
  std::string name() {return "VbbRegionAddJetRelaxedHZee";};
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
	    && p.V_mass > 75.
	    && p.V_mass < 105. 
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
	    //      && p. MET_et < 30
	    && ( p.H_mass < 90
		 || p.H_mass > 145 )
	    && p.H_mass < 250
	    && TMath::Abs(p.HVdPhi) > 2.9  
	    && ( p.triggerFlags[5] || p.triggerFlags[6] ) );    
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }
};

class SignalRegionAddJetRelaxedHZee: public CutSample{
  std::string name() {return "SignalRegionAddJetRelaxedHZee";};
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
	     && p.V_mass > 75.
	     && p.V_mass < 105.
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
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); }      
};

class BDTRegionAddJetRelaxedHZee: public CutSample{
  std::string name() {return "BDTRegionAddJetRelaxedHZee";};
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
	     && p.V_mass > 75. 
	     && p.V_mass < 105 
	     && ( p.triggerFlags[5] || p.triggerFlags[6] ) );
  }
  double weight(ntupleReader &p, Sample &sample) {if(sample.data) return 1; else return ((fA*p.PUweight+fB*p.PUweight2011B)*p.weightTrig); } 
};

#endif
