#ifndef CUTSLP_H
#define CUTSLP_H
#include "CutsAndHistos.h"
#include "ntupleReader.h"
#include <TH1F.h>
#include <sstream>
#include "TKey.h"

#define CSVM 0.679
#define CSVL 0.244
#define CSVT 0.898

// New implementations of the control region
// The signal regions must be implemented incrementally since cutflow is needed

class VlightRegionHZee: public Cut {
  std::string name() {return "VlightRegionHZee";};
  Bool_t pass(ntupleReader &p){
    iType = (VType)p.Vtype;
    return ( p.Vtype == 1 
	     && p.V_mass > 75.
	     && p.V_mass < 105.
	     && p.V_pt > 100.
	     && p.H_pt > 100.
	     && p.hJet_pt[0] > 20.
	     && p.hJet_pt[1] > 20.
	     && p.EVENT_json == true
	     && p.CountAddJets() < 2 );
  }
};


class TTbarRegionHZee: public Cut {
  std::string name() {return "TTbarRegionHZee";};
  Bool_t pass(ntupleReader &p){
    return( p.Vtype == 1 
	    && p.V_mass > 120.
	    && p.V_pt > 0.
	    && p.H_pt > 0.
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && p.EVENT_json == true
	    && p.MET_et > 50 );
      
  }
};


class VbbRegionHZee: public Cut {
  std::string name() {return "VbbRegionHZee";};
  Bool_t pass(ntupleReader &p){
    return( p.Vtype == 1
	    && p.V_mass > 75.
	    && p.V_mass < 105. 
	    && p.V_pt > 0.
	    && p.H_pt > 0.
	    && p.hJet_pt[0] > 20.
	    && p.hJet_pt[1] > 20.
	    && p.hJet_csv[0] > CSVT
	    && p.hJet_csv[1] > CSVT
	    && p.EVENT_json == true
	    && p.CountAddJets() < 2
	    //      && p. MET_et < 30
	    && ( p.H_mass < 90
		 || p.H_mass > 145 )
	    && TMath::Abs(p.HVdPhi) > 2.9  );
    
  }
};

class SignalRegionHZee: public Cut{
  std::string name() {return "SignalRegionHZee";};
  Bool_t pass(ntupleReader &p){
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
	     && p.CountAddJets() < 2 );
  }
};

#endif
