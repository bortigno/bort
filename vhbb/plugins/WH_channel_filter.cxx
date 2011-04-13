/* WH_channel_filter_cxx                                    */
/* Version 1   March 2011                                   */
/* Bortignon Pierluigi                                      */


#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <Math/Functions.h>
#include <Math/SVector.h>
#include <Math/SMatrix.h>
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TVector3.h"
#include "time.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

#include "SimTracker/TrackHistory/interface/VertexClassifierByProxy.h"
#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"
#include "DataFormats/Math/interface/Vector.h"
#include "TROOT.h"
#include "Math/VectorUtil.h"
#include <TVector3.h>
#include "TLorentzVector.h"

#include <Math/GenVector/PxPyPzE4D.h>
#include <Math/GenVector/PxPyPzM4D.h>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TrackingTools/IPTools/interface/IPTools.h"                                    
//#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h" 
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/Selector.h"

#include "PhysicsTools/SelectorUtils/interface/strbitset.h"

#include "DataFormats/GeometryVector/interface/VectorUtil.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
// #include "DataFormats/METReco/interface/PFMET.h"
// #include "DataFormats/METReco/interface/PFMETFwd.h"

// for the Wmunu
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "AnalysisDataFormats/EWK/interface/WMuNuCandidate.h"
// for the compositeCandidate
#include "CommonTools/CandUtils/interface/AddFourMomenta.h" 

#include "CommonTools/UtilAlgos/interface/TFileService.h"
//
// class decleration
//
// using namespace reco;
using namespace std;
using namespace edm;

class WH_channel_filter : public edm::EDFilter
{
  
public:
  
  explicit WH_channel_filter(const edm::ParameterSet&);

private:
  
  virtual bool filter(edm::Event&, const edm::EventSetup&) ;
  virtual void beginJob() ;
  virtual void endJob() ;

  bool muonJetCleaning( const pat::Jet&, const reco::Muon, double );

  struct ComparePt {
    bool operator()( const reco::Muon t1, const reco::Muon t2 ) const {
      return t1.p4().pt() > t2.p4().pt();
    }
  };

  struct CompareJetPt {
    bool operator()( pat::Jet* j1, pat::Jet* j2 ) const {
      return j1->p4().Pt() > j2->p4().Pt();
    }
  };

  struct CompareBTag {
    bool operator()( pat::Jet* j1, pat::Jet* j2 ) const {
      return j1->bDiscriminator("combinedSecondaryVertexBJetTags") > j2->bDiscriminator("combinedSecondaryVertexBJetTags");
    }
  };

  ComparePt ptComparator;
  CompareJetPt ptJetComparator;
  CompareBTag BTagComparator;

  //per creare dei TH1 velocemente InputTag.label
//   std::map<std::string,TH1D*> histocontainer_;
//   std::map<std::string,TH2D*> histocontainer_2;
//   std::map<std::string,TH3D*> histocontainer_3;

//   edm::InputTag akt5pfJetsLabel_;
  edm::InputTag muonLabel_;
  edm::InputTag patMetLabel_;
  edm::InputTag patJetLabel_;
  edm::InputTag WMuNuLabel_;
  edm::ParameterSet pfJetIdSelector_;

  std::vector<pat::Jet*> v_akt5pfj;

  // Member data
  Int_t n_event;  

  Double_t muonJetCleaningDRcut;
  Double_t higgsMassLowerCut;
  Double_t higgsMassHigherCut;
  bool bTagJetSorting;
  Double_t minBTagging;
  Double_t maxBTagging;
  Double_t WMassLowerCut;
  Double_t WMassHigherCut;
  Double_t WCandidatePtCut;
  Double_t higgsCandidatePtCut;
  Double_t WH_deltaPhiCut;
  Double_t jetPtThreshold;
  Double_t jetVetoPtCut;

  Double_t higgs_pt;
  Double_t vector_pt;
  Double_t higgsCandidate_pt;
  Double_t jetAnglePhiEtaPlane ;
  Double_t BanglePhiEtaPlane ;
  Double_t deltaR_signal ;
  Double_t invmass_signal ;
  Double_t deltaR_background ;
  Double_t invmass_background ;
  Double_t alphaAngle ;

};

WH_channel_filter::WH_channel_filter(const edm::ParameterSet& iConfig) : 

  //histocontainer_(),
  //histocontainer_2(),
  //histocontainer_3(),

  //cleaning cut
  muonJetCleaningDRcut(iConfig.getUntrackedParameter<double>("muonJetCleaningDRcut")),
  WMassLowerCut(iConfig.getUntrackedParameter<double>("WMassLowerCut")),
  WMassHigherCut(iConfig.getUntrackedParameter<double>("WMassHigherCut")),
  bTagJetSorting(iConfig.getUntrackedParameter<bool>("bTagJetSorting")),
  minBTagging(iConfig.getUntrackedParameter<double>("minBTagging")),
  maxBTagging(iConfig.getUntrackedParameter<double>("maxBTagging")),
  WCandidatePtCut(iConfig.getUntrackedParameter<double>("WCandidatePtCut")),
  higgsCandidatePtCut(iConfig.getUntrackedParameter<double>("higgsCandidatePtCut")),
  WH_deltaPhiCut(iConfig.getUntrackedParameter<double>("WH_deltaPhiCut")),
  jetVetoPtCut(iConfig.getUntrackedParameter<double>("jetVetoPtCut")),
  jetPtThreshold(iConfig.getUntrackedParameter<double>("jetPtThreshold")),

  //edm collections
  muonLabel_(iConfig.getUntrackedParameter<edm::InputTag>("muonCand")),
  patJetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("selectedPatJetsCand")),
  pfJetIdSelector_(iConfig.getParameter<edm::ParameterSet>("pfJetIDSelector")),
  patMetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("patMetsCand")),
  WMuNuLabel_(iConfig.getUntrackedParameter<edm::InputTag>("WMuNuCand"))
{

  //Initialize counters
  n_event = 0;

}   

bool WH_channel_filter::filter(edm::Event& iEvent, const edm::EventSetup& setup)
{
  ++n_event;

  //initialising each events
  higgs_pt = 0;
  vector_pt = 0;

  std::cout << "*** Analyzing " << iEvent.id() << " n_event = " << n_event << std::endl << std::endl;

  //patJet
  edm::Handle< pat::JetCollection > patJetHandle;
  iEvent.getByLabel(patJetLabel_, patJetHandle);
  const  pat::JetCollection &patJet = *patJetHandle.product();
  //JetID. Siggested cuts for 7TeV analysis: LOOSE. https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID 
  //  JetIDSelectionFunctor jetIDFunctor( JetIDSelectionFunctor::PURE09, JetIDSelectionFunctor::LOOSE );
  PFJetIDSelectionFunctor pfJetIDFunctor( pfJetIdSelector_ );

  //patMet
  edm::Handle< pat::METCollection > patMetHandle;
  iEvent.getByLabel(patMetLabel_, patMetHandle);
  const pat::METCollection v_patMet = *patMetHandle.product();

  //pfJet
//   edm::Handle<reco::PFJetCollection> recoAKT5PFJets;
//   iEvent.getByLabel(akt5pfJetsLabel_, recoAKT5PFJets);
//   const reco::PFJetCollection &akt5pfj = *recoAKT5PFJets.product();

  //muon handle
  edm::Handle< reco::MuonCollection > muonHandle;
  iEvent.getByLabel(muonLabel_,muonHandle);
  const reco::MuonCollection &UnsortedMuons = *muonHandle.product(); 
  reco::MuonCollection muons = UnsortedMuons;
  std::sort( muons.begin(), muons.end(), ptComparator);

//   // Generated particles handle
//   edm::Handle<reco::GenParticleCollection> genP;
//   iEvent.getByLabel(genpLabel_,genP);
//   const reco::GenParticleCollection &genParticles = *genP.product();

  //Wmunu
  edm::Handle< std::vector< reco::WMuNuCandidate > > WMuNuCollection;
  iEvent.getByLabel(WMuNuLabel_, WMuNuCollection);
  const reco::WMuNuCandidate& Wcandidate = WMuNuCollection->at(0);

  v_akt5pfj.clear();

  std::vector<const reco::Candidate*> v_muon;
  std::vector<const reco::Candidate*> v_met;

  // needed for the jetId
  pat::strbitset ret = pfJetIDFunctor.getBitTemplate();

  //jets are pt ordered
  for(size_t jetIdx = 0; jetIdx < patJet.size(); ++jetIdx){
    if( patJet.at(jetIdx).isPFJet() == true 
 	and pfJetIDFunctor( patJet.at(jetIdx), ret ) == true
	and muonJetCleaning( patJet.at(jetIdx), Wcandidate.getMuon(), muonJetCleaningDRcut ) == false 
	and patJet.at(jetIdx).correctedJet("abs").pt() > jetPtThreshold )
      v_akt5pfj.push_back( new pat::Jet (patJet.at(jetIdx).correctedJet("abs")) );
    }
 
  if( bTagJetSorting )
    std::sort(v_akt5pfj.begin(), v_akt5pfj.end(), BTagComparator);
      
  //Event selection: at least two jets one W
  if( v_akt5pfj.size() < 2
      or  WMuNuCollection->size() < 1 )
    return false;

  reco::CompositeCandidate higgsCandidate;
  higgsCandidate.addDaughter( *v_akt5pfj.at(0) );
  higgsCandidate.addDaughter( *v_akt5pfj.at(1) );
  AddFourMomenta addp4;
  addp4.set(higgsCandidate);
  higgsCandidate_pt = higgsCandidate.p4().Pt();
  double Wcandidate_pt = Wcandidate.p4().Pt();
  double WH_deltaPhi = Geom::deltaPhi(higgsCandidate.p4(), Wcandidate.p4());

  if( Wcandidate_pt < WCandidatePtCut
      or TMath::Abs(WH_deltaPhi) < WH_deltaPhiCut )
    return false;

  //W mass cut
  if( Wcandidate.p4().M() < WMassLowerCut
      or Wcandidate.p4().M() > WMassHigherCut )
    return false;  

  //Higgs pt cut
  if( higgsCandidate_pt < higgsCandidatePtCut )
    return false;

// taglio sulla finestra di massa dell'higgs
  if( higgsCandidate.p4().M() < higgsMassLowerCut or
      higgsCandidate.p4().M() > higgsMassHigherCut )
    return false;
  
  //cut on the looser btag
  if( ( v_akt5pfj.at(1)->bDiscriminator("combinedSecondaryVertexBJetTags") ) < minBTagging)
    return false;

  // order jet using pt for the jet veto
  v_akt5pfj.erase( v_akt5pfj.begin() );
  v_akt5pfj.erase( v_akt5pfj.begin() );
  if(v_akt5pfj.size() > 0){
    std::sort(v_akt5pfj.begin(), v_akt5pfj.end(), ptJetComparator);
    //JET VETO
    //no additional akt5pfjets with pt > 50 GeV
    if( v_akt5pfj.at(0)->p4().pt() > jetVetoPtCut ){
      return false;
    }
  }

  v_akt5pfj.clear();
  
  return true;
  
}//END EVENT LOOP

//puliamo i pfjet dai muoni con un deltaR
// if it is true get rid of the jet
bool WH_channel_filter::muonJetCleaning(const pat::Jet& tmpJet, const reco::Muon muon, double deltaRcut){
  bool clean = false;
  double deltaR = 1e10;
  deltaR = Geom::deltaR(tmpJet.p4().Vect(), muon.p4().Vect() );
  if( deltaR < deltaRcut )
    clean = true;
  
  return clean;
}



void WH_channel_filter::beginJob()
{
  using namespace std;
}

void WH_channel_filter::endJob() {

  std::cout << "JOB FINISHED" << std::endl;

}

DEFINE_FWK_MODULE(WH_channel_filter);
