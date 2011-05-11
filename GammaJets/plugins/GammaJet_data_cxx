/* Ntuplizer for the GammaJets */

/* Version 2                  */
/* April 2011                 */
/* Bortignon Pierluigi        */
/* With BTagging              */

#include "GammaJets/iCode/test/abis.cc"
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <Math/Functions.h>
#include <Math/SVector.h>
#include <Math/SMatrix.h>
#include "TH1F.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TVector3.h"
#include "time.h"
//#include "VHbb/iCode/interface/linked_ptr.h"

// per il BTag
#include "DataFormats/BTauReco/interface/JetTag.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"
#include "FWCore/Common/interface/TriggerNames.h"

//#include "DQMServices/Core/interface/DQMStore.h"
//#include "DQMServices/Core/interface/MonitorElement.h"

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
//#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h" 
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/Selector.h"

#include "PhysicsTools/SelectorUtils/interface/strbitset.h"

#include "DataFormats/GeometryVector/interface/VectorUtil.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h" 

#include "DataFormats/PatCandidates/interface/Photon.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

//
// class decleration
//
// using namespace reco;
using namespace std;
using namespace edm;

class GammaJet : public edm::EDAnalyzer
{
  
public:
  
  explicit GammaJet(const edm::ParameterSet&);

private:

  virtual void beginRun() ;
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) ;
  virtual void endJob() ;

  inline int getSign(double ); 
  bool jetMuonCleaning( std::vector<const pat::Jet*>, pat::Muon*, double );
  bool hasHiggsMother( const reco::Candidate* );
  bool hasBdaughters( const reco::Candidate * );
  double getAnglePhiEtaPlane(  pat::Jet* ,  pat::Jet* );
  double getAnglePhiEtaPlane( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR(  pat::Jet* ,  pat::Jet* );
  double getDeltaR( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR( TLorentzVector ,  pat::Jet* );
  double getDeltaEta(  pat::Jet* ,  pat::Jet* );
  double getDeltaEta( const reco::Candidate* , const reco::Candidate* );
  double getDeltaPhi(  pat::Jet*,  pat::Jet* );
  TVector2 getTvect(  pat::Jet*, TLorentzVector );
  TVector2 getTvect(  pat::Jet* );
  double getDeltaTheta(  pat::Jet*,  pat::Jet*, TLorentzVector, TLorentzVector );
  double getDeltaTheta(  pat::Jet*,  pat::Jet* );
  double getPtAsymmetry( pat::Jet*,  pat::Jet* );
  unsigned int getAssociatedB( std::vector<TLorentzVector> ,  pat::Jet* );

  TVector2 getBBdir(  pat::Jet*,  pat::Jet* );
  inline  pat::Jet* whichJet( pat::Jet*,  pat::Jet*);
  inline  pat::Jet* whichOtherJet( pat::Jet*,  pat::Jet*);

  double getHelicity( pat::Jet*, TVector3 );
  double getHelicity( const reco::GenJet*, TVector3 );
  double getHelicity( TLorentzVector, TVector3 );

  struct ComparePt {
    bool operator()( const pat::Muon t1, const pat::Muon t2 ) const {
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
  CompareBTag btagComparator;

  //per creare dei TH1 velocemente InputTag.label
  std::map<std::string,TTree*> tree_container;
  std::map<std::string,TH1D*> histocontainer_;
  std::map<std::string,TH2D*> histocontainer_2;
  std::map<std::string,TH3D*> histocontainer_3;

  edm::InputTag akt5pfJetsLabel_;
  edm::InputTag muonLabel_;
  edm::InputTag patJetLabel_;
  edm::InputTag ak7patJetLabel_;
  edm::InputTag patPhotonLabel_;
  edm::InputTag hltPathLabel_;
  edm::ParameterSet pfJetIdSelector_;

  std::vector<  pat::Jet* > v_akt5pfj;
  std::vector<  pat::Jet* > v_akt7pfj;

  // Member data
  Int_t n_event;  
  Int_t myEvents;

  // parameters set
  Double_t jetPtThreshold;
  Double_t minBTagging;
  Double_t maxBTagging;
  Double_t photon_ptCut;
  Double_t PG_deltaPhiCut;

  Double_t photonCandidate_pt;
  Double_t photonCandidate_mass;
  Double_t gluonCandidate_pt;
  Double_t gluonCandidate_mass;
  Double_t PG_deltaPhi   ;
  Double_t jetAnglePhiEtaPlane ;
  Double_t BanglePhiEtaPlane ;
  Double_t deltaR_signal ;
  Double_t invmass_signal ;
  Double_t deltaR_background ;
  Double_t invmass_background ;
  Double_t alphaAngle ;
  Double_t betaDistance ;
  Double_t deltaR_general ;
  Double_t invmass_general ;
  Double_t BdeltaEta;
  Double_t JetDeltaEta;
  Double_t epsilonDeltaEta;
  Double_t gammaDeltaR;
  Double_t BdeltaR;
  Double_t JetDeltaR;
  Double_t leadingBTag;
  Double_t secondLeadingBTag;
  Double_t iTheta;
  Double_t leading_gluonHelicity;
  Double_t leadingJetPt;
  Double_t leadingJetEta;
  Double_t leadingJetPhi;
  Double_t leadingJetEnergy;
  Double_t secondLeadingJetPt;
  Double_t secondLeadingJetEta;
  Double_t secondLeadingJetPhi;
  Double_t secondLeadingJetEnergy;
  Double_t jetVetoPt;
  Double_t jetVetoEta;
  Double_t jetVetoPhi;
  Double_t jetVetoEnergy;
  Double_t  photonTrackIso ;
  Double_t  photonEcalIso ;
  Double_t  photonHcalIso ;
  Double_t  photonCaloIso ;

  Double_t HT;

  Int_t nOfak5;
  Int_t nOfak7;
  bool jetVeto;
  bool itriggerResults;

  Int_t triggeridx;

  Double_t secondLeadingDeltaTheta;
  Double_t leadingDeltaTheta;
  Double_t AK7secondLeadingDeltaTheta;
  Double_t AK7leadingDeltaTheta;
  Double_t iDeltaTheta;
  Double_t otherDeltaTheta;

  Double_t JetDeltaPhi;
  Double_t jetPtAsymmetry;

};



GammaJet::GammaJet(const edm::ParameterSet& iConfig) : 

  tree_container(),
  histocontainer_(),
  histocontainer_2(),
  histocontainer_3(),

  //cuts
  jetPtThreshold(iConfig.getUntrackedParameter<double>("jetPtThreshold")),
  photon_ptCut(iConfig.getUntrackedParameter<double>("photon_ptCut")),
  PG_deltaPhiCut(iConfig.getUntrackedParameter<double>("PG_deltaPhiCut")),

  //edm collection
  patPhotonLabel_(iConfig.getUntrackedParameter<edm::InputTag>("patPhotons")),
  muonLabel_(iConfig.getUntrackedParameter<edm::InputTag>("muonCand")),
  //  akt5pfJetsLabel_(iConfig.getUntrackedParameter<edm::InputTag>("akt5pfJets")),
  patJetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("patJets")),
  ak7patJetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("ak7patJets")),
  hltPathLabel_(iConfig.getParameter<edm::InputTag>("hltPath")),
  pfJetIdSelector_(iConfig.getParameter<edm::ParameterSet>("pfJetIDSelector"))
{

  //Initialize counters
  n_event = 0;
  myEvents = 0;
  triggeridx = -1;

}   

void GammaJet::analyze(const edm::Event& iEvent, const edm::EventSetup& setup)
{

  ++n_event;

  //initialising each events
  iTheta = 1e10;
  iDeltaTheta = 1e10;
  HT = 0;

  std::cout << "*** Analyzing " << iEvent.id() << " n_event = " << n_event << std::endl << std::endl;


//   //JEC
//   string JEC_PATH("CondFormats/JetMETObjects/data/");
//   //edm::FileInPath fip(JEC_PATH+"Spring10_Uncertainty_AK5Calo.txt");
//   edm::FileInPath fip(JEC_PATH+"Spring10_Uncertainty_AK5PF.txt");
//   // edm::FileInPath fip(JEC_PATH+"Spring10_Uncertainty_AK5JPT.txt");
//   // JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty(fip.fullPath());
//   // jecUnc->setJetEta(eta); // Give rapidity of jet you want uncertainty on
//   // jecUnc->setJetPt(ptCor);// Also give the corrected pt of the jet you want the uncertainty on
//   // The following function gives the relative uncertainty in the jet Pt.
//   // i.e. ptCorSmeared = (1 +- uncer) * ptCor  
//   // uncer = jecUnc->getUncertainty(true); // In principle, boolean controls if uncertainty on +ve or -ve side is returned (asymmetric errors) but not yet implemented.


  //HLT
  edm::Handle< edm::TriggerResults > triggerResults;
  iEvent.getByLabel(hltPathLabel_, triggerResults);
  if(triggeridx == -1){
    edm::TriggerNames const& triggerNames = iEvent.triggerNames(*triggerResults);
    for ( unsigned i = 0; i < triggerNames.size(); ++i){
      for(int v = 1; v < 4; v++){
	ostringstream oss;
	oss << v;
	std::string HLTpath = "HLT_Photon75_CaloIdVL_IsoL_v"+oss.str();
	if( HLTpath == triggerNames.triggerName(i) ){
	  //       if( std::string("HLT_Photon40_Isol_Cleaned_L1R_v1") == triggerNames.triggerName(i) ){
	  triggeridx = i;
	  std::cout << triggerNames.triggerName(i) << " is bit  "  << i << std::endl;
	}
      }
    }
  }
  
  if( triggeridx == -1 
      or triggerResults->accept(triggeridx) == false )
    return void();

  //patJet
  edm::Handle< pat::JetCollection > patJetHandle;
  iEvent.getByLabel(patJetLabel_, patJetHandle);
  const  pat::JetCollection &patJet = *patJetHandle.product();
  //JetID. Siggested cuts for 7TeV analysis: LOOSE. https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID 
  //  JetIDSelectionFunctor jetIDFunctor( JetIDSelectionFunctor::PURE09, JetIDSelectionFunctor::LOOSE );
  PFJetIDSelectionFunctor pfJetIDFunctor( pfJetIdSelector_ );

  //ak7patJet
  edm::Handle< pat::JetCollection > ak7patJetHandle;
  iEvent.getByLabel(ak7patJetLabel_, ak7patJetHandle);
  const  pat::JetCollection &ak7patJet = *ak7patJetHandle.product();
  //JetID. Siggested cuts for 7TeV analysis: LOOSE. https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID 
  //  JetIDSelectionFunctor jetIDFunctor( JetIDSelectionFunctor::PURE09, JetIDSelectionFunctor::LOOSE );
  PFJetIDSelectionFunctor ak7pfJetIDFunctor( pfJetIdSelector_ );
  // needed for the jetId
  pat::strbitset ak7ret = ak7pfJetIDFunctor.getBitTemplate();

  //patPhotons
  edm::Handle< pat::PhotonCollection > patPhotonHandle;
  iEvent.getByLabel(patPhotonLabel_, patPhotonHandle);
  const  pat::PhotonCollection &patPhoton = *patPhotonHandle.product();

  //   // Get b tag information
  //   edm::Handle<reco::JetTagCollection> bTagHandle;
  //   //  iEvent.getByLabel("trackCountingHighEffBJetTags", bTagHandle);
  //   iEvent.getByLabel("simpleSecondaryVertexHighPurBJetTags", bTagHandle);
  //   const reco::JetTagCollection & bTags = *(bTagHandle.product());

  //pfJet
  //   edm::Handle<reco::PFJetCollection> recoAKT5PFJets;
  //   iEvent.getByLabel(akt5pfJetsLabel_, recoAKT5PFJets);
  //   const reco::PFJetCollection &akt5pfj = *recoAKT5PFJets.product();

  //muon handle
  //  edm::Handle< edm::View< pat::Muon > > muonHandle;
  edm::Handle< pat::MuonCollection > muonHandle;
  iEvent.getByLabel(muonLabel_,muonHandle);
  //  edm::View<pat::Muon> muons = *muonHandle;
  const pat::MuonCollection &UnsortedMuons = *muonHandle.product(); 
  pat::MuonCollection muons = UnsortedMuons;
  std::sort( muons.begin(), muons.end(), ptComparator);

  v_akt5pfj.clear();
  v_akt7pfj.clear();

  pat::Jet *leadingJet;
  pat::Jet *secondLeadingJet;
  pat::Jet *iJet;
  pat::Jet *otherJet;
  
  pat::Jet *AK7leadingJet;
  pat::Jet *AK7secondLeadingJet;

  // needed for the jetId
  pat::strbitset ret = pfJetIDFunctor.getBitTemplate();

  PFJetIDSelectionFunctor jetIDLoose( PFJetIDSelectionFunctor::FIRSTDATA, PFJetIDSelectionFunctor::LOOSE );
  pat::strbitset retLOOSE = jetIDLoose.getBitTemplate();
  

  // The jets are pt ordered
  for(size_t jetIdx = 0; jetIdx < patJet.size(); ++jetIdx){
    if( patJet.at(jetIdx).isPFJet() == true 
	and patJet.at(jetIdx).correctedJet("L3Absolute").pt() > jetPtThreshold
	and jetIDLoose( patJet.at(jetIdx), retLOOSE ) == true ){
      HT += patJet.at(jetIdx).correctedJet("L3Absolute").et();
      v_akt5pfj.push_back( new pat::Jet (patJet.at(jetIdx).correctedJet("L3Absolute")) );
    }
  }  
  

  // REAL BTAGGING
  //ordering jets using BTagging information
  std::sort(v_akt5pfj.begin(), v_akt5pfj.end(), btagComparator);    

  if( v_akt5pfj.size() < 2 )
    return void();

  

  //Associate the first two AKT5 and AK7PF
  for(size_t jetIdx = 0; jetIdx < ak7patJet.size(); ++jetIdx){
    if( ak7patJet.at(jetIdx).isPFJet() == true 
 	and pfJetIDFunctor( ak7patJet.at(jetIdx), retLOOSE ) == true 
	and ak7patJet.at(jetIdx).correctedJet("L3Absolute").pt() > jetPtThreshold ){
      for( size_t ak5 = 0; ak5 < 2; ak5++ ){
	if( getDeltaR( &(ak7patJet.at(jetIdx).correctedJet("L3Absolute")) , v_akt5pfj.at(ak5) ) < 0.5 )
	  v_akt7pfj.push_back( new pat::Jet (ak7patJet.at(jetIdx).correctedJet("L3Absolute")) );
      }
    }
  }

  

  if( v_akt7pfj.size() < 2 )
    return void();
  // fill the leading and second leading btagged jets
  if( v_akt7pfj.at(0)->p4().Pt() >  v_akt7pfj.at(1)->p4().Pt() ){
    AK7leadingJet = v_akt7pfj.at(0);
    AK7secondLeadingJet = v_akt7pfj.at(1);
  }
  else{
    AK7leadingJet = v_akt7pfj.at(1);
    AK7secondLeadingJet = v_akt7pfj.at(0);
  }

  nOfak5 = v_akt5pfj.size();
  nOfak7 = v_akt7pfj.size();

  // fill the leading and second leading btagged jets
  if( v_akt5pfj.at(0)->p4().Pt() >  v_akt5pfj.at(1)->p4().Pt() ){
    leadingJet = v_akt5pfj.at(0);
    secondLeadingJet = v_akt5pfj.at(1);
  }
  else{
    leadingJet = v_akt5pfj.at(1);
    secondLeadingJet = v_akt5pfj.at(0);
  }

  leadingJetPt = leadingJet->pt();
  leadingJetPt = leadingJet->eta();
  leadingJetPt = leadingJet->phi();
  leadingJetPt = leadingJet->energy();
  leadingBTag = leadingJet->bDiscriminator("combinedSecondaryVertexBJetTags");
  secondLeadingJetPt = secondLeadingJet->pt();
  secondLeadingJetPt = secondLeadingJet->eta();
  secondLeadingJetPt = secondLeadingJet->phi();
  secondLeadingJetPt = secondLeadingJet->energy();
  secondLeadingBTag = secondLeadingJet->bDiscriminator("combinedSecondaryVertexBJetTags");
  

  // order jet using pt for the jet veto
  v_akt5pfj.erase( v_akt5pfj.begin() );
  v_akt5pfj.erase( v_akt5pfj.begin() );
  if(v_akt5pfj.size() > 0){
    std::sort(v_akt5pfj.begin(), v_akt5pfj.end(), ptJetComparator);
    jetVetoPt = v_akt5pfj.at(0)->p4().pt();
    jetVetoPt = v_akt5pfj.at(0)->p4().eta();
    jetVetoPt = v_akt5pfj.at(0)->p4().phi();
    jetVetoPt = v_akt5pfj.at(0)->p4().energy();
    //JET VETO
    //no additional akt5pfjets with pt > XX GeV
    if( v_akt5pfj.at(0)->p4().pt() > jetPtThreshold )
      jetVeto = true;
  }
  

  //photon ID
  if( patPhoton.size() < 1
     or ( not patPhoton.at(0).photonID("PhotonCutBasedIDTight") ) )
    return void();

  photonTrackIso =  patPhoton.at(0).trackIso();  
  photonEcalIso =  patPhoton.at(0).ecalIso();  
  photonHcalIso =  patPhoton.at(0).hcalIso();
  photonCaloIso =  patPhoton.at(0).caloIso();  

  // gluon Candidate
  reco::CompositeCandidate gluonCandidate;
  gluonCandidate.addDaughter( *leadingJet );
  gluonCandidate.addDaughter( *secondLeadingJet );
  AddFourMomenta addp4;
  addp4.set(gluonCandidate);
  gluonCandidate_pt = gluonCandidate.p4().Pt();
  gluonCandidate_mass = gluonCandidate.p4().M();
  //helicity
  TLorentzVector gluonP4;
  gluonP4.SetPtEtaPhiE( gluonCandidate.pt() , 
			gluonCandidate.eta(),
			gluonCandidate.phi(),
			gluonCandidate.energy() );
  TVector3 gluonBoost;
  gluonBoost = gluonP4.BoostVector();
  leading_gluonHelicity = getHelicity( leadingJet, gluonBoost );

  

  // photon Candidate  
  reco::CompositeCandidate photonCandidate;
  photonCandidate.addDaughter( patPhoton.at(0) );
  AddFourMomenta addFatJetp4;
  addFatJetp4.set(photonCandidate);
  photonCandidate_pt = photonCandidate.p4().Pt();
  photonCandidate_mass = photonCandidate.p4().M();
  PG_deltaPhi = Geom::deltaPhi(gluonCandidate.p4(), photonCandidate.p4());

  

  // Event selection
  if( photonCandidate_pt < photon_ptCut
      or TMath::Abs(PG_deltaPhi) < PG_deltaPhiCut )
    return void();  

  myEvents++;    

  JetDeltaR = getDeltaR( secondLeadingJet, leadingJet );
  JetDeltaEta = TMath::Abs( getDeltaEta( secondLeadingJet, leadingJet ) );
  JetDeltaPhi = getDeltaPhi( secondLeadingJet, leadingJet );
  jetPtAsymmetry = getPtAsymmetry( leadingJet, secondLeadingJet );


//   std::vector<reco::PFCandidatePtr>
//     leadingPfc = leadingJet->getPFConstituents();
//   for(size_t idx = 0; idx < leadingPfc.size(); idx++){
//     if( leadingPfc.at(idx)->charge() != 0 ){
//       histocontainer_["h_pfcMass"]->Fill( leadingPfc.at(idx)->mass() );
//       histocontainer_["h_pfcEta"]->Fill( leadingPfc.at(idx)->eta() );
//       histocontainer_["h_pfcPhi"]->Fill( leadingPfc.at(idx)->phi() );
//       histocontainer_2["h2_pfcEtaPhi"]->Fill( leadingPfc.at(idx)->eta(), leadingPfc.at(idx)->phi() );
//     }
//   }
  
  //pull for AKT7PF jet
  TVector2 AK7secondLeadingT;
  TVector2 AK7leadingT;
  TVector2 AK7BBdir;  
  AK7leadingDeltaTheta = 1e10;
  AK7secondLeadingDeltaTheta = 1e10;
  AK7secondLeadingT = getTvect(AK7secondLeadingJet);
  AK7leadingT = getTvect(AK7leadingJet);
  if(AK7secondLeadingT.Mod() > 1e-7 
     and AK7leadingT.Mod() > 1e-7 ){
    AK7BBdir =  getBBdir( AK7secondLeadingJet, AK7leadingJet );
    AK7leadingDeltaTheta = getDeltaTheta( AK7leadingJet , AK7secondLeadingJet );
    AK7secondLeadingDeltaTheta = getDeltaTheta( AK7secondLeadingJet, AK7leadingJet );
  }

  

  //pull for AK5
  TVector2 secondLeadingT;
  TVector2 leadingT;
  secondLeadingT = getTvect(secondLeadingJet);
  leadingT = getTvect(leadingJet);
  if( secondLeadingT.Mod() < 1e-7 
      or leadingT.Mod() < 1e-7 )
    return void();
  
  secondLeadingT = getTvect(secondLeadingJet);
  leadingT = getTvect(leadingJet);
  secondLeadingDeltaTheta = getDeltaTheta( leadingJet , secondLeadingJet );
  leadingDeltaTheta = getDeltaTheta( secondLeadingJet, leadingJet );

  

  // plots only the closest to the beam
  iJet = whichJet(leadingJet, secondLeadingJet);  
  otherJet = whichOtherJet( leadingJet, secondLeadingJet);
  TVector2 iT;
  TVector2 otherT;
  iT = getTvect( iJet );
  otherT = getTvect( otherJet );
  iDeltaTheta = 1e10;
  otherDeltaTheta = 1e10;
  if( iT.Mod() > 1e-7
      and  otherT.Mod() > 1e-7 ){
    iDeltaTheta = getDeltaTheta( iJet, otherJet );
    otherDeltaTheta = getDeltaTheta( otherJet, iJet );
  }

  

  tree_container["GammaJet"]->Fill();

  

  v_akt5pfj.clear();
  v_akt7pfj.clear();
  
}//END EVENT LOOP


inline int GammaJet::getSign(double v) { return v > 0 ? 1 : (v < 0 ? -1 : 0); } 


//puliamo i muoni non isolati
// if it is true get rid of the muon
bool GammaJet::jetMuonCleaning( std::vector< const pat::Jet*> jetCol, pat::Muon* mu, double deltaRcut){
  bool clean = false;
  double deltaR = 1e10;
  for(size_t jetIdx = 0; jetIdx < jetCol.size(); ++jetIdx){
    deltaR = Geom::deltaR(jetCol.at(jetIdx)->p4().Vect(), mu->p4().Vect() );
    if( deltaR < deltaRcut )
      clean = true;
  }  
  return clean;
}


//metodo per guardare se ha un Higgs come antenato
bool GammaJet::hasHiggsMother( const reco::Candidate * particle ){
  bool hashiggsmother = false;
  while ( particle->numberOfMothers() != 0 ){
    if( particle->mother()->pdgId() == 25 )
      hashiggsmother = true;
    particle = particle->mother();
  }
  return hashiggsmother;
}

//check if there are dbflavoured daughters
bool GammaJet::hasBdaughters( const reco::Candidate * particle ){
  bool myDaughterHasBottom = false;
  for(size_t myDau = 0; myDau < particle->numberOfDaughters(); myDau++){
    HepPDT::ParticleID myDaughter( particle->daughter(myDau)->pdgId() ); 
    myDaughterHasBottom += myDaughter.hasBottom();
  }
  return myDaughterHasBottom;
}

// calcolo dell'angolo nel piano eta phi della retta conguingente due jet
double GammaJet::getAnglePhiEtaPlane(  pat::Jet *leadingJet ,  pat::Jet *secondLeadingJet ){
  double angle = 1e10;
  double deltaPhi = leadingJet->p4().Phi() - secondLeadingJet->p4().Phi();
  double deltaEta = leadingJet->p4().Eta() - secondLeadingJet->p4().Eta();
  angle = TMath::ATan2( deltaPhi, deltaEta );
  return angle;
}

// calcolo dell'angolo nel piano eta phi della retta conguingente due b hadron
double GammaJet::getAnglePhiEtaPlane( const reco::Candidate *firstB , const reco::Candidate *secondB ){
  double angle = 1e10;
  double deltaPhi = firstB->phi() - secondB->phi();
  double deltaEta = firstB->eta() - secondB->eta();
  angle = TMath::ATan2( deltaPhi, deltaEta );
  return angle;
}

double GammaJet::getDeltaR(  pat::Jet * leadingJet,  pat::Jet * secondLeadingJet ){
  double deltaR = 1e10;
  deltaR = Geom::deltaR( leadingJet->p4().Vect(), secondLeadingJet->p4().Vect() );
  return deltaR;
}

double GammaJet::getDeltaR( const reco::Candidate * firstB, const reco::Candidate * secondB ){
  double deltaR = 1e10;
  deltaR = Geom::deltaR( firstB->momentum(), secondB->momentum() );
  return deltaR;
}

double GammaJet::getDeltaR( TLorentzVector TLV,  pat::Jet * patJet ){
  double deltaR = 1e10;
  TVector3 JetVector;
  JetVector.SetXYZ( patJet->p4().Px(), patJet->p4().Py(), patJet->p4().Pz() );
  deltaR = JetVector.DeltaR( TLV.Vect() ) ;
  return deltaR;
}

double GammaJet::getDeltaEta(  pat::Jet * leadingJet,  pat::Jet * secondLeadingJet ){
  double deltaEta = 1e10;
  deltaEta = leadingJet->p4().Eta() - secondLeadingJet->p4().Eta() ;
  return deltaEta;
}

double GammaJet::getDeltaEta( const reco::Candidate * firstB, const reco::Candidate * secondB ){
  double deltaEta = 1e10;
  deltaEta = firstB->eta() - secondB->eta() ;
  return deltaEta;
}

double GammaJet::getDeltaPhi(  pat::Jet* leadingJet,  pat::Jet* secondLeadingJet){

  double deltaPhi = 1e10;
  deltaPhi = Geom::deltaPhi( leadingJet->p4().Vect(), secondLeadingJet->p4().Vect() ) ;
  return deltaPhi;

}

double GammaJet::getPtAsymmetry( pat::Jet* leadingJet,  pat::Jet* secondLeadingJet ){

  double asymmetry = 1e10;
  double ptDiff = leadingJet->p4().Pt() - secondLeadingJet->p4().Pt();
  double ptSum = leadingJet->p4().Pt() + secondLeadingJet->p4().Pt();
  asymmetry = ptDiff / ptSum;
  return asymmetry;
}

unsigned int GammaJet::getAssociatedB( std::vector<TLorentzVector> bHadron_vector,  pat::Jet* leadingJet){

  //association Bvertex - Jet
  double deltaMin = 1e10;
  unsigned int mypos = 1e2;
  for( size_t b = 0; b < bHadron_vector.size(); ++b){
    TVector3 leadingJetVector;
    leadingJetVector.SetXYZ( leadingJet->p4().Px(), leadingJet->p4().Py(), leadingJet->p4().Pz() );
    if( leadingJetVector.DeltaR( bHadron_vector.at(b).Vect() )  < deltaMin ){
      deltaMin = leadingJetVector.DeltaR( bHadron_vector.at(b).Vect() ) ;
      mypos = b;
    }
  }
  return mypos;
}

// FIXED variabile consigliata nell'articolo teorico sulla color reconnection
// with bvertex information
TVector2 GammaJet::getTvect( pat::Jet* patJet, TLorentzVector b ){

  TVector2 t_Vect(0,0);
  TVector2 ci(0,0);
  TVector2 r(0,0);
  TLorentzVector pi(0,0,0,0);
  TVector2 v_b( b.Eta(), b.Phi());
  double patJetpfcPt = 1e10;
  double r_mag = 1e10;

  std::vector<reco::PFCandidatePtr>
    patJetpfc = patJet->getPFConstituents();
  for(size_t idx = 0; idx < patJetpfc.size(); idx++){
    if( patJetpfc.at(idx)->charge() != 0 ){
      patJetpfcPt = patJetpfc.at(idx)->pt();
      pi.SetPtEtaPhiE( patJetpfc.at(idx)->pt(), patJetpfc.at(idx)->eta(), patJetpfc.at(idx)->phi(), patJetpfc.at(idx)->energy() );
      //      ci.Set( patJetpfc.at(idx)->eta(), patJetpfc.at(idx)->phi() );
      r.Set( pi.Rapidity() - b.Rapidity(), Geom::deltaPhi( patJetpfc.at(idx)->phi(), b.Phi() ) );
      r_mag = r.Mod();
      t_Vect += ( (patJetpfcPt * r_mag) / b.Pt() ) * r;
    }
  }

  return t_Vect;
  
}

// without b vertex information
TVector2 GammaJet::getTvect( pat::Jet* patJet ){

  TVector2 t_Vect(0,0);
  TVector2 null(0,0);
  TVector2 ci(0,0);
  TLorentzVector pi(0,0,0,0);
  TLorentzVector J(0,0,0,0);
  TVector2 r(0,0);
  double patJetpfcPt = 1e10;
  double r_mag = 1e10;
  unsigned int nOfconst = 0;

  std::vector<reco::PFCandidatePtr>
    patJetpfc = patJet->getPFConstituents();
  for(size_t idx = 0; idx < patJetpfc.size(); idx++){
    if( patJetpfc.at(idx)->charge() != 0 ){
//       if( patJetpfc.at(idx)->trackRef().isNull()){
// 	std::cout << "AIUTO!!!! pfc senza trackRef" << std::endl;
// 	std::cout << " PDG id = " << patJetpfc.at(idx)->pdgId() << std::endl;
//       }
      pi.SetPtEtaPhiE( patJetpfc.at(idx)->pt(), patJetpfc.at(idx)->eta(), patJetpfc.at(idx)->phi(), patJetpfc.at(idx)->energy() );
      J += pi;
      nOfconst++;
    }
  }

  if( nOfconst < 2 )
    return null;

  TVector2 v_J( J.Rapidity(), J.Phi() );

  for(size_t idx = 0; idx < patJetpfc.size(); idx++){
    if( patJetpfc.at(idx)->charge() != 0  ){
      patJetpfcPt = patJetpfc.at(idx)->pt();
      pi.SetPtEtaPhiE( patJetpfc.at(idx)->pt(), patJetpfc.at(idx)->eta(), patJetpfc.at(idx)->phi(), patJetpfc.at(idx)->energy() );
      //      ci.Set( patJetpfc.at(idx)->eta(), patJetpfc.at(idx)->phi() );
      r.Set( pi.Rapidity() - J.Rapidity(), Geom::deltaPhi( patJetpfc.at(idx)->phi(), J.Phi() ) );
      r_mag = r.Mod();
      t_Vect += ( patJetpfcPt / J.Pt() ) * r_mag * r;
    }
  }

  return t_Vect;
  
}

// with b vertex information
double GammaJet::getDeltaTheta( pat::Jet* j1, pat::Jet* j2, TLorentzVector b1, TLorentzVector b2 ){

  double deltaTheta = 1e10;
  TVector2 v_b1(b1.Eta(), b1.Phi());
  TVector2 v_b2(b2.Eta(), b2.Phi());

  TVector2 t = getTvect(j1, b1);

  if( t.Mod() == 0 )
    return deltaTheta = 1e10;

  deltaTheta = t.DeltaPhi(v_b2 - v_b1);

  return deltaTheta;

}

//without b vertex information
double GammaJet::getDeltaTheta( pat::Jet* j1, pat::Jet* j2 ){

  double deltaTheta = 1e10;
  TLorentzVector pi(0,0,0,0);
  TLorentzVector v_j1(0,0,0,0);
  TLorentzVector v_j2(0,0,0,0);

  std::vector<reco::PFCandidatePtr>
    j1pfc = j1->getPFConstituents();
  for(size_t idx = 0; idx < j1pfc.size(); idx++){
    if( j1pfc.at(idx)->charge() != 0 ){
      pi.SetPtEtaPhiE( j1pfc.at(idx)->pt(), j1pfc.at(idx)->eta(), j1pfc.at(idx)->phi(), j1pfc.at(idx)->energy() );
      v_j1 += pi;
    }
  }

  std::vector<reco::PFCandidatePtr>
    j2pfc = j2->getPFConstituents();
  for(size_t idx = 0; idx < j2pfc.size(); idx++){
    if( j2pfc.at(idx)->charge() != 0 ){
      pi.SetPtEtaPhiE( j2pfc.at(idx)->pt(), j2pfc.at(idx)->eta(), j2pfc.at(idx)->phi(), j2pfc.at(idx)->energy() );
      v_j2 += pi;
    }
  }

  if( v_j2.Mag() == 0 
      or v_j1.Mag() == 0 )
    return deltaTheta = 1e10;

  TVector2 v2_j1( v_j1.Rapidity(), v_j1.Phi());
  TVector2 v2_j2( v_j2.Rapidity(), v_j2.Phi());
  TVector2 t = getTvect(j1);

  if( t.Mod() == 0 )
    return deltaTheta = 1e10;

  TVector2 beam1(1,0);
  TVector2 beam2(-1,0);

  Double_t deltaphi = Geom::deltaPhi( v_j2.Phi(), v_j1.Phi() );
  Double_t deltaeta = v_j2.Rapidity() - v_j1.Rapidity();
  TVector2 BBdir( deltaeta, deltaphi );

  deltaTheta = t.DeltaPhi(BBdir);

  return deltaTheta;

}


TVector2 GammaJet::getBBdir( pat::Jet* j1, pat::Jet* j2 ){

  TVector2 BBdir(0,0);
  TLorentzVector pi(0,0,0,0);
  TLorentzVector v_j1(0,0,0,0);
  TLorentzVector v_j2(0,0,0,0);

  std::vector<reco::PFCandidatePtr>
    j1pfc = j1->getPFConstituents();
  for(size_t idx = 0; idx < j1pfc.size(); idx++){
    if( j1pfc.at(idx)->charge() != 0 ){
      pi.SetPtEtaPhiE( j1pfc.at(idx)->pt(), j1pfc.at(idx)->eta(), j1pfc.at(idx)->phi(), j1pfc.at(idx)->energy() );
      v_j1 += pi;
    }
  }

  std::vector<reco::PFCandidatePtr>
    j2pfc = j2->getPFConstituents();
  for(size_t idx = 0; idx < j2pfc.size(); idx++){
    if( j2pfc.at(idx)->charge() != 0 ){
      pi.SetPtEtaPhiE( j2pfc.at(idx)->pt(), j2pfc.at(idx)->eta(), j2pfc.at(idx)->phi(), j2pfc.at(idx)->energy() );
      v_j2 += pi;
    }
  }

  if( v_j2.Mag() == 0 
      or v_j1.Mag() == 0 )
    return BBdir;

  TVector2 v2_j1( v_j1.Rapidity(), v_j1.Phi());
  TVector2 v2_j2( v_j2.Rapidity(), v_j2.Phi());

  Double_t deltaphi = Geom::deltaPhi( v_j2.Phi(), v_j1.Phi() );
  Double_t deltaeta = v_j2.Rapidity() - v_j1.Rapidity();

  BBdir.Set( deltaeta, deltaphi );

  return BBdir;
}

// return the jet with the highest |eta|, i.e. the closest to the beam
inline  pat::Jet* GammaJet::whichJet( pat::Jet *j1,  pat::Jet *j2){

  if( TMath::Abs( j1->p4().Eta() ) - TMath::Abs( j2->p4().Eta() ) > 0 )
    return j1;
  else
    return j2;
}

// return the opposite of whichJet
inline  pat::Jet* GammaJet::whichOtherJet( pat::Jet *j1,  pat::Jet *j2){

  if( TMath::Abs( j1->p4().Eta() ) - TMath::Abs( j2->p4().Eta() ) < 0 )
    return j1;
  else
    return j2;
}


double GammaJet::getHelicity( pat::Jet* jet , TVector3 boost ){
  double hel = 1e10;
  TLorentzVector j;
  j.SetPtEtaPhiE( jet->pt(), jet->eta(), jet->phi(), jet->energy() );
  j.Boost( -boost );
  hel = TMath::Cos( j.Vect().Angle( boost ) );
  return hel;
}


double GammaJet::getHelicity( const reco::GenJet* jet , TVector3 boost ){
  double hel = 1e10;
  TLorentzVector j;
  j.SetPtEtaPhiE( jet->pt(), jet->eta(), jet->phi(), jet->energy() );
  j.Boost( -boost );
  hel = TMath::Cos( j.Vect().Angle( boost ) );
  return hel;
}

double GammaJet::getHelicity( TLorentzVector b , TVector3 boost ){
  double hel = 1e10;
  b.Boost( -boost );
  hel = TMath::Cos( b.Vect().Angle( boost ) );
  return hel;
}



void GammaJet::beginRun()
{
  triggeridx = -1;
}


void GammaJet::beginJob()
{
  
  using namespace std;
  edm::Service<TFileService> fs;
  tree_container["GammaJet"]=fs->make<TTree>("GammaJet","GammaJet");

  abis::make_branch(tree_container,"leading_gluonHelicity"         ,leading_gluonHelicity);
  abis::make_branch(tree_container,"jetPtAsymmetry"                ,jetPtAsymmetry);
  abis::make_branch(tree_container,"AK7leadingDeltaTheta"          ,AK7leadingDeltaTheta);
  abis::make_branch(tree_container,"AK7secondLeadingDeltaTheta"    ,AK7secondLeadingDeltaTheta);
  abis::make_branch(tree_container,"leadingDeltaTheta"             ,leadingDeltaTheta);
  abis::make_branch(tree_container,"secondLeadingDeltaTheta"       ,secondLeadingDeltaTheta);
  abis::make_branch(tree_container,"iDeltaTheta"                   ,iDeltaTheta);
  abis::make_branch(tree_container,"jetDeltaR"                     ,JetDeltaR);
  abis::make_branch(tree_container,"photonCandidate_mass"          ,photonCandidate_mass);
  abis::make_branch(tree_container,"gluonCandidate_mass"           ,gluonCandidate_mass);
  abis::make_branch(tree_container,"photonCandidate_pt"            ,photonCandidate_pt);
  abis::make_branch(tree_container,"photonTrackIso"            ,photonTrackIso);
  abis::make_branch(tree_container,"photonEcalIso"            ,photonEcalIso);
  abis::make_branch(tree_container,"photonHcalIso"            ,photonHcalIso);
  abis::make_branch(tree_container,"photonCaloIso"            ,photonCaloIso);
  abis::make_branch(tree_container,"gluonCandidate_pt"             ,gluonCandidate_pt);
  abis::make_branch(tree_container,"leadingBTag"                   ,leadingBTag);
  abis::make_branch(tree_container,"leadingJetPt"                   ,leadingJetPt);
  abis::make_branch(tree_container,"leadingJetEta"                   ,leadingJetEta);
  abis::make_branch(tree_container,"leadingJetPhi"                   ,leadingJetPhi);
  abis::make_branch(tree_container,"leadingJetEnergy"                   ,leadingJetEnergy);
 abis::make_branch(tree_container,"secondLeadingJetPt"                   ,secondLeadingJetPt);
  abis::make_branch(tree_container,"secondLeadingJetEta"                   ,secondLeadingJetEta);
  abis::make_branch(tree_container,"secondLeadingJetPhi"                   ,secondLeadingJetPhi);
  abis::make_branch(tree_container,"secondLeadingJetEnergy"                   ,secondLeadingJetEnergy);
  abis::make_branch(tree_container,"secondLeadingBTag"             ,secondLeadingBTag);
  abis::make_branch(tree_container,"jetVeto"                       ,jetVeto);
  abis::make_branch(tree_container,"jetVetoPt"                       ,jetVetoPt);
  abis::make_branch(tree_container,"jetVetoEta"                       ,jetVetoEta);
  abis::make_branch(tree_container,"jetVetoPhi"                       ,jetVetoPhi);
  abis::make_branch(tree_container,"jetVetoEnegry"                       ,jetVetoEnergy);
  abis::make_branch(tree_container,"HT"                        ,HT);
  abis::make_branch(tree_container,"nOfak5"                        ,nOfak5);

}

void GammaJet::endJob() {

  std::cout << "My events = " << myEvents << std::endl;
  std::cout << "JOB FINISHED" << std::endl;

}

DEFINE_FWK_MODULE(GammaJet);
