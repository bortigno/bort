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
    return( p.V_mass > 120.
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
    return( p.V_mass > 75.
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

/* class SignalPreSelectionZee : public Cut { */
/*   std::string name() {return "SignalPreSelZee";}; */
  
/*   Bool_t pass(ntupleReader &p){ */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   return (  iCand->at(0).candidateType == VHbbCandidate::Zee); */
/*   } */
/* }; */

/* class HPtCut : public PCut */
/* { */
/*  public: */
/*   HPtCut(double ptMin):PCut(ptMin){} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   return (  iCand->at(0).H.p4.Pt() > m_cut); */
/*   } */
/*   virtual std::string name()  {return "Higgs_Pt_Gt_"+cutValueString(); }  */
/* }; */

/* class VPtCut : public PCut */
/* { */
/*  public: */
/*   VPtCut(double ptMin):PCut(ptMin){} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   return (  iCand->at(0).V.p4.Pt() > m_cut); */
/*   } */
/*   virtual std::string name()  {return "Vector_Pt_Gt_"+cutValueString(); } */
/* }; */


/* class DoubleBTagCut : public PCut */
/* { */
/* public: */
/*   DoubleBTagCut(double csvMin):PCut(csvMin){} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   VHbbCandidate::HiggsCandidate  H = p.getVHbbCandidate()->at(0).H; */
/*   return (   */
/*         H.jets.size() >= 2 */
/*         && ( H.jets.at(0).csv > m_cut && H.jets.at(1).csv > m_cut) */
/*       ); */
/*   }  */
/*   virtual std::string name()  {return "DoubleCSV_"+cutValueString(); } */
/* }; */

/* class SingleBTagCut : public PCut */
/* { */
/* public: */
/*   SingleBTagCut(double csvMin):PCut(csvMin){} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   const VHbbCandidate::HiggsCandidate & H = p.getVHbbCandidate()->at(0).H; */
/*   return ( */
/*         H.jets.size() >= 2 */
/*         && ( H.jets.at(0).csv > m_cut || H.jets.at(1).csv > m_cut) */
/*       ); */
/*   } */
/*   virtual std::string name()  {return "SingleCSV_"+cutValueString(); } */

/* }; */

/* class VHDeltaPhiCut : public PCut */
/* { */
/* public: */
/*   VHDeltaPhiCut(double deltaPhiMin):PCut(deltaPhiMin){} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   const VHbbCandidate::HiggsCandidate & H = p.getVHbbCandidate()->at(0).H; */
/*   const VHbbCandidate::VectorCandidate & V = p.getVHbbCandidate()->at(0).V; */
 
/*  return (TMath::Abs( Geom::deltaPhi(H.p4.Phi(), V.p4.Phi()) ) > m_cut */
/*         ); */
/*   } */
/*   virtual std::string name()  {return "VHDeltaPhi_Gt_"+cutValueString(); } */
/* }; */


/* class AdditionalJetsCut : public PCut */
/* { */
/* public: */
/*  /// Filtering "< n" */
/*   AdditionalJetsCut(int n):PCut(n) {} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*  return (iCand->at(0).additionalJets.size() < m_cut); */
/*   } */
/*   virtual std::string name()  {return "NumAddJets_Lt_"+cutValueString(); } */
/* }; */

/* class AdditionalLeptonsCut : public PCut */
/* { */
/* public: */
/*  /// Filtering "< n" */
/*   AdditionalLeptonsCut(int n):PCut(n) {} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   const VHbbCandidate::VectorCandidate & V = p.getVHbbCandidate()->at(0).V; */
/*   int expectedLeptons = 0; */
/*   if(  iCand->at(0).candidateType == VHbbCandidate::Wmun ||  iCand->at(0).candidateType == VHbbCandidate::Wen) expectedLeptons =1; */
/*   if(  iCand->at(0).candidateType == VHbbCandidate::Zmumu ||  iCand->at(0).candidateType == VHbbCandidate::Zee) expectedLeptons =2; */
  
/*    return ( V.muons.size() + V.electrons.size() - expectedLeptons  < m_cut); */
/*   } */
/*   virtual std::string name()  {return "NumAddLeptons_Lt_"+cutValueString(); } */
/* }; */

/* class METCut : public PCut */
/* { */
/*  public: */
/*   METCut(double metMin):PCut(metMin){} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   return (  iCand->at(0).V.mets.at(0).p4.Pt() > m_cut); */
/*   } */
/*   virtual std::string name()  {return "MET_Gt_"+cutValueString(); } */
/* }; */

/* class METSignificanceCut : public PCut */
/* { */
/*  public: */
/*   METSignificanceCut(double metMin):PCut(metMin){} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   return (   iCand->at(0).V.mets[0].metSig  > m_cut); */
/*   } */
/*   virtual std::string name()  {return "METSig_Gt_"+cutValueString(); } */
/* }; */

/* class JetMETDeltaPhiCut : public PCut */
/* { */
/*  public: */
/*   JetMETDeltaPhiCut(double deltaPhiMin):PCut(deltaPhiMin){} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   const VHbbCandidate::VectorCandidate V = p.getVHbbCandidate()->at(0).V; */
/*   const VHbbCandidate::HiggsCandidate H = p.getVHbbCandidate()->at(0).H; */

/*   return ( TMath::Abs( Geom::deltaPhi( V.mets[0].p4.Phi(), H.jets.at(0).p4.Phi())) > m_cut */
/*             && TMath::Abs( Geom::deltaPhi(V.mets[0].p4.Phi(), H.jets.at(1).p4.Phi())) > m_cut  ); */
/* } */
/*   virtual std::string name()  {return "JetMETDeltaPhi_Gt_"+cutValueString(); } */
/* }; */
/* class DiJetMassMinCut : public PCut */
/* { */
/*  public: */
/*   DiJetMassMinCut(double mMin):PCut(mMin){} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   return (  iCand->at(0).H.p4.M() > m_cut); */
/*   } */
/*   virtual std::string name()  {return "Higgs_M_Gt_"+cutValueString(); } */
/* }; */


/* class DiJetMassMaxCut : public PCut */
/* { */
/*  public: */
/*   DiJetMassMaxCut(double mMax):PCut(mMax){} */
/*   bool pass(ntupleReader &p) { */
/*   const std::vector<VHbbCandidate> *iCand = p.getVHbbCandidate(); */
/*   if(iCand->size() < 1) return false; */
/*   return (  iCand->at(0).H.p4.M() <= m_cut); */
/*   } */
/*   virtual std::string name()  {return "Higgs_M_Lt_"+cutValueString(); } */
/* }; */

/* CutSet buildSignalSelectionZee(float mass); */
/* CutSet buildSignalSelectionZmumu(float mass); */
/* CutSet buildSignalSelectionWen(float mass); */
/* CutSet buildSignalSelectionWmun(float mass); */

#endif
