/* ZeeH_channel.cxx analyzer         */
/* v1 March 2011                   */
/* Bortignon Pierluigi             */
/* Same as David :                 */
/* higgs with most btagged smart   */
/* Real Btagging                   */
/* Additional jets veto            */
/* Some improvement in the         */
/* jet-muon cleaning               */
/* Higgs pt cut at 150 added       */
/* Electrons added                  */

//#include "VHbb/iCode/test/abis.cc"
#include "VHbb/iCode/interface/abis_func.h"
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <Math/Functions.h>
#include <Math/SVector.h>
#include <Math/SMatrix.h>
#include "TTree.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TVector3.h"
#include "time.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"

// per il BTag
#include "DataFormats/BTauReco/interface/JetTag.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
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
#include "DataFormats/MuonReco/interface/MuonIsolation.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/Selector.h"

#include "PhysicsTools/SelectorUtils/interface/strbitset.h"

#include "DataFormats/GeometryVector/interface/VectorUtil.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h" 

#include "CommonTools/UtilAlgos/interface/TFileService.h"
//
// class decleration
//
// using namespace reco;
using namespace std;
using namespace edm;

class ZeeH_channel : public edm::EDAnalyzer
{
  
public:
  
  explicit ZeeH_channel(const edm::ParameterSet&);

private:
  
  virtual void analyze(const edm::Event&, const edm::EventSetup&) ;
  virtual void beginJob() ;
  virtual void endJob() ;

  inline int getSign(double ); 
  bool muonJetCleaning( const pat::Jet&, const std::vector<reco::Muon>& , double );
  bool eleJetCleaning( const pat::Jet&, const reco::Candidate*, double );
  bool hasHiggsMother( const reco::Candidate* );
  bool hasBdaughters( const reco::Candidate * );
  bool hasBMother( const reco::Candidate * );
  double getAnglePhiEtaPlane( pat::Jet* , pat::Jet* );
  double getAnglePhiEtaPlane( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR( pat::Jet* , pat::Jet* );
  double getDeltaR( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR( TLorentzVector , pat::Jet* );
  double getDeltaR( TVector3 , pat::Jet* );
  double getDeltaEta( pat::Jet* , pat::Jet* );
  double getDeltaEta( const reco::Candidate* , const reco::Candidate* );
  double getDeltaPhi( pat::Jet*, pat::Jet* );
  double getPtAsymmetry(pat::Jet*, pat::Jet* );
  unsigned int getAssociatedB( std::vector<TLorentzVector> , pat::Jet* );
  double getBBavProjection( pat::Jet*, pat::Jet* );
  TVector2 getTvect( pat::Jet*, TLorentzVector );
  TVector2 getTvect( pat::Jet* );
  double getDeltaTheta( pat::Jet*, pat::Jet*, TLorentzVector, TLorentzVector );
  double getDeltaTheta( pat::Jet*, pat::Jet* );
  double getDeltaX( pat::Jet*, pat::Jet*, TLorentzVector, TLorentzVector );
  double getDeltaY( pat::Jet*, pat::Jet*, TLorentzVector, TLorentzVector );

  double getMyVar_background( pat::Jet*, TVector3 );
  double getMyVar_signal( pat::Jet*, TVector3, double );

  TVector2 getBBdir( pat::Jet* , pat::Jet* );
  inline pat::Jet* whichJet(pat::Jet*, pat::Jet*);
  inline pat::Jet* whichOtherJet(pat::Jet*, pat::Jet*);

  double getHelicity( pat::Jet*, TVector3 );
  double getHelicity( const reco::GenJet*, TVector3 );
  double getHelicity( TLorentzVector, TVector3 );

  bool isInFiducial( double );

  struct ComparePt {
    bool operator()( const reco::Muon t1, const reco::Muon t2 ) const {
      return t1.p4().pt() > t2.p4().pt();
    }
  };

  struct CompareEt {
    bool operator()( const pat::Electron t1, const pat::Electron t2 ) const {
      double et1 = t1.caloEnergy()/cosh(t1.caloPosition().eta());
      double et2 = t2.caloEnergy()/cosh(t2.caloPosition().eta());
      return et1 > et2;
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
  CompareEt etComparator;
  CompareJetPt ptJetComparator;
  CompareBTag btagComparator;


  //per creare dei TH1 velocemente InputTag.label
  std::map<std::string,TTree*> tree_container;
  std::map<std::string,TH1D*> histocontainer_;
  std::map<std::string,TH2D*> histocontainer_2;
  std::map<std::string,TH3D*> histocontainer_3;

  edm::InputTag akt5pfJetsLabel_;
  edm::InputTag muonLabel_;
  edm::InputTag electronLabel_;
  edm::InputTag genpLabel_;
  edm::InputTag patJetLabel_;
  edm::InputTag ak7patJetLabel_;
  edm::ParameterSet pfJetIdSelector_;

  std::vector<int> v_motherId;
  std::vector<int> v_mother_status_background;

  std::vector<pat::Jet*> v_akt5pfj;
  std::vector<pat::Jet*> v_akt7pfj;

  TLorentzVector TLV_bHadron_general;
  TLorentzVector TLV_bHadron_signal;
  TLorentzVector TLV_bHadron_background;

  std::vector<TLorentzVector> bHadron_general;
  std::vector<TLorentzVector> bHadron_signal;
  std::vector<TLorentzVector> bHadron_background;


  // Member data
  unsigned int goodJetCounter;
  unsigned int badJetCounter;

  Int_t n_event;  
  Int_t myEvents;

  Double_t eleJetCleaningDRcut;
  Double_t JetBassociationCut;
  Double_t higgsMassLowerCut;
  Double_t higgsMassHigherCut;
  Double_t jetDRcut;
  Double_t jetPtAsymmetryHigherCut;
  Double_t ZCandidatePtCut;
  Double_t HCandidatePtCut;
  Double_t ZH_deltaPhiCut;
  Double_t minBTagging;
  Double_t maxBTagging;

  Double_t Zcandidate_pt;
  Double_t Zcandidate_mass;
  Double_t iDeltaTheta;
  Double_t higgsCandidate_mass;
  Double_t leading_higgsHelicity;
  Double_t secondLeading_higgsHelicity;
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
  Double_t betaDistance ;
  Double_t deltaR_general ;
  Double_t invmass_general ;
  Double_t BdeltaEta;
  Double_t JetDeltaEta;
  Double_t JetDeltaEtaSmart;
  Double_t epsilonDeltaEta;
  Double_t gammaDeltaR;
  Double_t BdeltaR;
  Double_t JetDeltaR;
  Double_t genbDeltaR;
  Double_t Zhelicity;

  Double_t leadingDeltaTheta;
  Double_t secondLeadingDeltaTheta;
  Double_t AK7leadingDeltaTheta;
  Double_t AK7secondLeadingDeltaTheta;


  Double_t jetDeltaPhi;
  Double_t jetPtAsymmetry;

  Double_t myVar_background;
  Double_t myVar_signal;

  bool bHadron;  

  unsigned int different_plane;
  unsigned int same_plane;

};

ZeeH_channel::ZeeH_channel(const edm::ParameterSet& iConfig) : 

  tree_container(),
  histocontainer_(),
  histocontainer_2(),
  histocontainer_3(),

  //cleaning cut
  jetDRcut(iConfig.getUntrackedParameter<double>("jetDeltaRcut")),
  eleJetCleaningDRcut(iConfig.getUntrackedParameter<double>("eleJetCleaningDRcut")),
  JetBassociationCut(iConfig.getUntrackedParameter<double>("JetBassociationDRCut")),
  higgsMassLowerCut(iConfig.getUntrackedParameter<double>("hMassLowerCut")),
  higgsMassHigherCut(iConfig.getUntrackedParameter<double>("hMassHigherCut")),
  jetPtAsymmetryHigherCut(iConfig.getUntrackedParameter<double>("jetPtAsymmetryHigherCut")),
  ZCandidatePtCut(iConfig.getUntrackedParameter<double>("ZCandidatePtCut")),
  HCandidatePtCut(iConfig.getUntrackedParameter<double>("HCandidatePtCut")),
  ZH_deltaPhiCut(iConfig.getUntrackedParameter<double>("ZH_deltaPhiCut")),
  minBTagging(iConfig.getUntrackedParameter<double>("minBTagging")),
  maxBTagging(iConfig.getUntrackedParameter<double>("maxBTagging")),

  //edm collection
  genpLabel_(iConfig.getUntrackedParameter<edm::InputTag>("genPart")),
  muonLabel_(iConfig.getUntrackedParameter<edm::InputTag>("muonCand")),
  electronLabel_(iConfig.getUntrackedParameter<edm::InputTag>("electronCand")),
  //  akt5pfJetsLabel_(iConfig.getUntrackedParameter<edm::InputTag>("akt5pfJets")),
  patJetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("patJets")),
  ak7patJetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("ak7patJets")),
  pfJetIdSelector_(iConfig.getParameter<edm::ParameterSet>("pfJetIDSelector") )
{

  //Initialize counters
  different_plane = 0;
  same_plane  = 0;
  n_event = 0;
  myEvents = 0;

}   

void ZeeH_channel::analyze(const edm::Event& iEvent, const edm::EventSetup& setup)
{
  ++n_event;

  //initialising each events
  higgs_pt = 0;
  vector_pt = 0;

  std::cout << "*** Analyzing " << iEvent.id() << " n_event = " << n_event << std::endl << std::endl;

//   // Get b tag information
//   edm::Handle<reco::JetTagCollection> bTagHandle;
//   //  iEvent.getByLabel("trackCountingHighEffBJetTags", bTagHandle);
//   iEvent.getByLabel("simpleSecondaryVertexHighPurBJetTags", bTagHandle);
//   const reco::JetTagCollection & bTags = *(bTagHandle.product());

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


  //pfJet
//   edm::Handle<reco::PFJetCollection> recoAKT5PFJets;
//   iEvent.getByLabel(akt5pfJetsLabel_, recoAKT5PFJets);
//   const reco::PFJetCollection &akt5pfj = *recoAKT5PFJets.product();

  //muon handle
  //  edm::Handle< edm::View< reco::Muon > > muonHandle;
  edm::Handle< reco::MuonCollection > muonHandle;
  iEvent.getByLabel(muonLabel_,muonHandle);
  //  edm::View<reco::Muon> muons = *muonHandle;
  const reco::MuonCollection &UnsortedMuons = *muonHandle.product();
  reco::MuonCollection muons = UnsortedMuons;
  std::sort( muons.begin(), muons.end(), ptComparator);

  //Electrons
  edm::Handle<pat::ElectronCollection> patElectron;
  iEvent.getByLabel(electronLabel_, patElectron);
//   if ( ! patElectron.isValid()) {
//     //std::cout << "No electrons found in this event..." << std::endl;
//       return false; // RETURN: no electrons found in this event
//   }
  const pat::ElectronCollection &UnsortedElectrons = *patElectron.product();
  pat::ElectronCollection electrons = UnsortedElectrons;
  std::sort( electrons.begin(), electrons.end(), etComparator);


  // Generated particles handle
  edm::Handle<reco::GenParticleCollection> genP;
  iEvent.getByLabel(genpLabel_,genP);
  //edm::View<reco::GenParticle> genParticles = *genP;
  const reco::GenParticleCollection &genParticles = *genP.product();

  v_motherId.clear();
  v_mother_status_background.clear();
  bHadron_general.clear();
  bHadron_signal.clear();
  bHadron_background.clear();
  v_akt5pfj.clear();
  v_akt7pfj.clear();


  // PARTON LEVEL
  TLorentzVector genHiggs;
  TVector3 genHiggsBoost;
  double genb1_higgsHelicity;
  double genb2_higgsHelicity;
  double bPtAsymmetry;
  std::vector< TLorentzVector > genb;
  genb.clear();
  TLorentzVector TLV;
  // Generated particles loop
  for( reco::GenParticleCollection::const_iterator iGenp = genParticles.begin(); 
       iGenp != genParticles.end();
       ++iGenp) 
    {
      const reco::Candidate *genCandidate = &(*iGenp);
      if( TMath::Abs( genCandidate->pdgId() ) == 5 
	  //21 = gluon; 25 = higgs
	  and ( not hasBMother(genCandidate) )
	  and ( TMath::Abs( genCandidate->eta() ) < 5 ) ){
	TLV.SetPtEtaPhiE( genCandidate->pt(),
			  genCandidate->eta(),
			  genCandidate->phi(),
			  genCandidate->energy() );
	genb.push_back( TLV );
      }
    }//END GENPARTICLEs LOOP


  std::vector<const reco::Candidate*> v_ele;
  std::vector<const reco::Candidate*> v_ele_p;
  std::vector<const reco::Candidate*> v_ele_n;
  pat::Jet *leadingJet;
  pat::Jet *secondLeadingJet;
  pat::Jet *iJet;
  pat::Jet *otherJet;

  pat::Jet *AK7leadingJet;
  pat::Jet *AK7secondLeadingJet;

  reco::CandidateCollection BhadronCollection;
  reco::CandidateCollection BhadronCollectionSignal;
  reco::CandidateCollection BhadronCollectionBackground;

  // needed for the jetId
  pat::strbitset ret = pfJetIDFunctor.getBitTemplate();

  // count the good jets
  goodJetCounter = 0;
  badJetCounter = 0;

  //store good electrons
  for( size_t ele_iter = 0; ele_iter < electrons.size(); ++ele_iter )
    if ( isInFiducial(electrons.at(ele_iter).caloPosition().eta() ) ){
      v_ele.push_back( &(electrons.at(ele_iter) ) ); 
      if( electrons.at(ele_iter).charge() > 0 ) 
	v_ele_p.push_back( &electrons.at(ele_iter) );
      if( electrons.at(ele_iter).charge() < 0 ) 
	v_ele_n.push_back( &electrons.at(ele_iter) );
    }
  
  if( v_ele_n.size() < 1
      or v_ele_p.size() < 1 )
    return void();
  
  // The jets are pt ordered
  for(size_t jetIdx = 0; jetIdx < patJet.size(); ++jetIdx){
    if( patJet.at(jetIdx).isPFJet() == true 
 	and pfJetIDFunctor( patJet.at(jetIdx), ret ) == true 
	//	and muonJetCleaning( patJet.at(jetIdx), muons, eleJetCleaningDRcut ) == false
	and eleJetCleaning( patJet.at(jetIdx), v_ele_p.at(0), eleJetCleaningDRcut ) == false 
	and eleJetCleaning( patJet.at(jetIdx), v_ele_n.at(0), eleJetCleaningDRcut ) == false )
      v_akt5pfj.push_back( new pat::Jet (patJet.at(jetIdx).correctedJet("abs")) );  
  }


  //Event selection: at least electrons with opposite sign
  if( v_akt5pfj.size() < 2 )
    return void();

  //fill the muons for the Z
  v_ele.push_back( v_ele_p.at(0) );
  v_ele.push_back( v_ele_n.at(0) );  

  // REAL BTAGGING
  //ordering jets using BTagging information
  std::sort(v_akt5pfj.begin(), v_akt5pfj.end(), btagComparator); 

  //Associate the first two AKT5 and AK7PF
  for(size_t jetIdx = 0; jetIdx < ak7patJet.size(); ++jetIdx){
    if( ak7patJet.at(jetIdx).isPFJet() == true 
 	and pfJetIDFunctor( ak7patJet.at(jetIdx), ret ) == true 
	and ak7patJet.at(jetIdx).correctedJet("abs").pt() > 20
	and eleJetCleaning( ak7patJet.at(jetIdx), v_ele_p.at(0), eleJetCleaningDRcut ) == false 
	and eleJetCleaning( ak7patJet.at(jetIdx), v_ele_n.at(0), eleJetCleaningDRcut ) == false ){
      for( size_t ak5 = 0; ak5 < 2; ak5++ ){
	if( getDeltaR( &(ak7patJet.at(jetIdx).correctedJet("abs")) , v_akt5pfj.at(ak5) ) < 0.5 )
	  v_akt7pfj.push_back( new pat::Jet (ak7patJet.at(jetIdx).correctedJet("abs")) );
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


  //Associate parton-jet
  unsigned int ref1 = 1e2;
  unsigned int ref2 = 1e2;
  for(unsigned int i = 0; i < genb.size(); ++i){
    if( getDeltaR( genb.at(i), v_akt5pfj.at(0) ) < 0.5 )
      ref1 = i;
    if( getDeltaR( genb.at(i), v_akt5pfj.at(1) ) < 0.5 )
      ref2 = i;
  }
  if( ( ref1 + ref2 ) < 99 ){
    genHiggs = genb.at(ref1) + genb.at(ref2);
    genHiggsBoost = genHiggs.BoostVector();
    genb1_higgsHelicity = getHelicity( genb.at(ref1), genHiggsBoost );
    genb2_higgsHelicity = getHelicity( genb.at(ref2), genHiggsBoost );
    bPtAsymmetry = ( genb.at(ref1).Pt() - genb.at(ref2).Pt() ) / ( genb.at(ref1).Pt() + genb.at(ref2).Pt() );
  }

  // fill the leading and second leading btagged jets
  if( v_akt5pfj.at(0)->p4().Pt() >  v_akt5pfj.at(1)->p4().Pt() ){
    leadingJet = v_akt5pfj.at(0);
    secondLeadingJet = v_akt5pfj.at(1);
  }
  else{
    leadingJet = v_akt5pfj.at(1);
    secondLeadingJet = v_akt5pfj.at(0);
  }

  //taglio sul btag
  if( ( leadingJet->bDiscriminator("combinedSecondaryVertexBJetTags") < maxBTagging and
	secondLeadingJet->bDiscriminator("combinedSecondaryVertexBJetTags") < maxBTagging )
      or ( leadingJet->bDiscriminator("combinedSecondaryVertexBJetTags") < minBTagging or
	   secondLeadingJet->bDiscriminator("combinedSecondaryVertexBJetTags") < minBTagging ) )
    return void();

  //create the higgs candidate
  reco::CompositeCandidate higgsCandidate;
  higgsCandidate.addDaughter( *v_akt5pfj.at(0) );
  higgsCandidate.addDaughter( *v_akt5pfj.at(1) );
  AddFourMomenta addp4;
  addp4.set(higgsCandidate);
  higgsCandidate_pt = higgsCandidate.p4().Pt();
  higgsCandidate_mass = higgsCandidate.p4().M();
  TLorentzVector higgsP4;
  higgsP4.SetPtEtaPhiE( higgsCandidate.pt() , 
			higgsCandidate.eta(),
			higgsCandidate.phi(),
			higgsCandidate.energy() );
  TVector3 higgsBoost;
  higgsBoost = higgsP4.BoostVector();
  leading_higgsHelicity = getHelicity( leadingJet, higgsBoost );
  secondLeading_higgsHelicity = getHelicity( secondLeadingJet, higgsBoost );

  
  reco::CompositeCandidate Zcandidate;
  Zcandidate.addDaughter( *v_ele.at(0) );
  Zcandidate.addDaughter( *v_ele.at(1) );
  AddFourMomenta addZp4;
  addZp4.set(Zcandidate);
  Zcandidate_pt = Zcandidate.p4().Pt();
  Zcandidate_mass = Zcandidate.p4().M();
  double ZH_deltaPhi = Geom::deltaPhi(higgsCandidate.p4(), Zcandidate.p4());
  TLorentzVector positiveEleP4;
  positiveEleP4.SetPtEtaPhiE( v_ele_p.at(0)->pt() , 
			       v_ele_p.at(0)->eta(),
			       v_ele_p.at(0)->phi(),
			       v_ele_p.at(0)->energy() );

  TLorentzVector Zp4;
  Zp4.SetPtEtaPhiE( Zcandidate.pt() , 
		    Zcandidate.eta(),
		    Zcandidate.phi(),
		    Zcandidate.energy() );
  TVector3 Zboost;
  Zboost = Zp4.BoostVector();  
  Zhelicity = getHelicity( positiveEleP4, Zboost );

  // order jet using pt for the jet veto
  v_akt5pfj.erase( v_akt5pfj.begin() );
  v_akt5pfj.erase( v_akt5pfj.begin() );
  if(v_akt5pfj.size() > 0){
    std::sort(v_akt5pfj.begin(), v_akt5pfj.end(), ptJetComparator);
    //JET VETO
    //no additional akt5pfjets with pt > 20 GeV
    if( v_akt5pfj.at(0)->p4().pt() > 20 )
      return void();
  }

  //Event selection
  if( Zcandidate_pt < ZCandidatePtCut
      or TMath::Abs(ZH_deltaPhi) < ZH_deltaPhiCut
      or Zcandidate.p4().M() < 75
      or Zcandidate.p4().M() > 105 
      or higgsCandidate_pt < HCandidatePtCut )
    return void();

  //HIGGS MASS CUT
  if( higgsCandidate.p4().M() < higgsMassLowerCut or
      higgsCandidate.p4().M() > higgsMassHigherCut )
    return void();
    
  // JET PT ASYMMETRY CUT
  jetPtAsymmetry = getPtAsymmetry( leadingJet, secondLeadingJet );
  if( jetPtAsymmetry > jetPtAsymmetryHigherCut )
    return void();

  // JET DR CUT
  JetDeltaR = getDeltaR( leadingJet, secondLeadingJet );
  if(JetDeltaR > jetDRcut )
    return void();

  JetDeltaEta = TMath::Abs( getDeltaEta( leadingJet, secondLeadingJet ) );
  jetDeltaPhi = getDeltaPhi( leadingJet, secondLeadingJet );

  

  if( ( ref1 + ref2 ) < 1e2 ){
    genHiggs = genb.at(ref1) + genb.at(ref2);
    genHiggsBoost = genHiggs.BoostVector();
    genbDeltaR = genb.at(ref1).DeltaR( genb.at(ref2) );
    genb1_higgsHelicity = getHelicity( genb.at(ref1), genHiggsBoost );
    genb2_higgsHelicity = getHelicity( genb.at(ref2), genHiggsBoost );
    bPtAsymmetry = ( genb.at(ref1).Pt() - genb.at(ref2).Pt() ) / ( genb.at(ref1).Pt() + genb.at(ref2).Pt() );
  }

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
    AK7leadingDeltaTheta = TMath::Abs( getDeltaTheta( AK7leadingJet , AK7secondLeadingJet ) );
    AK7secondLeadingDeltaTheta = TMath::Abs( getDeltaTheta( AK7secondLeadingJet, AK7leadingJet ) );
  }

  TVector2 secondLeadingT;
  TVector2 leadingT;
  secondLeadingT = getTvect(secondLeadingJet);
  leadingT = getTvect(leadingJet);
  if(secondLeadingT.Mod() < 1e-7 
     or leadingT.Mod() < 1e-7 )
    return void();

  TVector2 BBdir;  
  BBdir =  getBBdir( secondLeadingJet, leadingJet );
  
  //plots the leading and second leading separately
  leadingDeltaTheta = 1e10;
  secondLeadingDeltaTheta = 1e10;
  leadingDeltaTheta = TMath::Abs( getDeltaTheta( leadingJet , secondLeadingJet ) );
  secondLeadingDeltaTheta = TMath::Abs( getDeltaTheta( secondLeadingJet, leadingJet ) );
  
  // plots only the closest to the beam
  iJet = whichJet(leadingJet, secondLeadingJet);  
  otherJet = whichOtherJet( leadingJet, secondLeadingJet);
  TVector2 iT;
  iT = getTvect( iJet );
  double iTheta = 1e10;
  iDeltaTheta = 1e10;
  iTheta = iT.Phi();
  
  iDeltaTheta = TMath::Abs( getDeltaTheta( iJet , otherJet ) );

  tree_container["Zee_channel"]->Fill();

  myEvents++;
  
  v_akt5pfj.clear();
  v_akt7pfj.clear();
  
}//END EVENT LOOP



//funzione segno
inline int ZeeH_channel::getSign(double v) { return v > 0 ? 1 : (v < 0 ? -1 : 0); } 

//puliamo i pfjet dai elettroni con un deltaR
// if it is true get rid of the jet
bool ZeeH_channel::muonJetCleaning(const pat::Jet& tmpJet, const std::vector<reco::Muon>& muCol, double deltaRcut){
  bool clean = false;
  double deltaR = 1e10;
  for(size_t muIdx = 0; muIdx < muCol.size(); ++muIdx){
    deltaR = Geom::deltaR(tmpJet.p4().Vect(), muCol.at(muIdx).p4().Vect() );
    if( deltaR < deltaRcut )
      clean = true;
  }  
  return clean;
}

//puliamo i elettroni non isolati
// if it is true get rid of the electrons
bool ZeeH_channel::eleJetCleaning( const pat::Jet& patJet, const reco::Candidate* ele, double dRcut){
  bool clean = false;
  double dR = 1e10;
  dR = Geom::deltaR(ele->p4().Vect(), patJet.p4().Vect() );
  if( dR < dRcut )
    clean = true;
  return clean;
}

//metodo per guardare se ha un Higgs come antenato
bool ZeeH_channel::hasHiggsMother( const reco::Candidate * particle ){
  bool hashiggsmother = false;
  while ( particle->numberOfMothers() != 0 ){
    if( particle->mother()->pdgId() == 25 )
      hashiggsmother = true;
    particle = particle->mother();
  }
  return hashiggsmother;
}

//metodo per guardare se ha un b come antenato
bool ZeeH_channel::hasBMother( const reco::Candidate * particle ){
  bool hasBmother = false;
  while ( particle->numberOfMothers() != 0 ){
    if( TMath::Abs(particle->mother()->pdgId()) == 5 )
      hasBmother = true;
    particle = particle->mother();
  }
  return hasBmother;
}

//check if there are dbflavoured daughters
bool ZeeH_channel::hasBdaughters( const reco::Candidate * particle ){
  bool myDaughterHasBottom = false;
  for(size_t myDau = 0; myDau < particle->numberOfDaughters(); myDau++){
    HepPDT::ParticleID myDaughter( particle->daughter(myDau)->pdgId() ); 
    myDaughterHasBottom += myDaughter.hasBottom();
  }
  return myDaughterHasBottom;
}

// calcolo dell'angolo nel piano eta phi della retta conguingente due jet
double ZeeH_channel::getAnglePhiEtaPlane( pat::Jet *leadingJet , pat::Jet *secondLeadingJet ){
  double angle = 1e10;
  double deltaPhi = leadingJet->p4().Phi() - secondLeadingJet->p4().Phi();
  double deltaEta = leadingJet->p4().Eta() - secondLeadingJet->p4().Eta();
  angle = TMath::ATan2( deltaPhi, deltaEta );
  return angle;
}

// calcolo dell'angolo nel piano eta phi della retta conguingente due b hadron
double ZeeH_channel::getAnglePhiEtaPlane( const reco::Candidate *firstB , const reco::Candidate *secondB ){
  double angle = 1e10;
  double deltaPhi = firstB->phi() - secondB->phi();
  double deltaEta = firstB->eta() - secondB->eta();
  angle = TMath::ATan2( deltaPhi, deltaEta );
  return angle;
}

double ZeeH_channel::getDeltaR( pat::Jet * leadingJet, pat::Jet * secondLeadingJet ){
  double deltaR = 1e10;
  deltaR = Geom::deltaR( leadingJet->p4().Vect(), secondLeadingJet->p4().Vect() );
  return deltaR;
}

double ZeeH_channel::getDeltaR( const reco::Candidate * firstB, const reco::Candidate * secondB ){
  double deltaR = 1e10;
  deltaR = Geom::deltaR( firstB->momentum(), secondB->momentum() );
  return deltaR;
}

double ZeeH_channel::getDeltaR( TLorentzVector TLV, pat::Jet * patJet ){
  double deltaR = 1e10;
  TVector3 JetVector;
  JetVector.SetXYZ( patJet->p4().Px(), patJet->p4().Py(), patJet->p4().Pz() );
  deltaR = JetVector.DeltaR( TLV.Vect() ) ;
  return deltaR;
}

double ZeeH_channel::getDeltaR( TVector3 TLV, pat::Jet * patJet ){
  double deltaR = 1e10;
  TVector3 JetVector;
  JetVector.SetXYZ( patJet->p4().Px(), patJet->p4().Py(), patJet->p4().Pz() );
  deltaR = JetVector.DeltaR( TLV ) ;
  return deltaR;
}

double ZeeH_channel::getDeltaEta( pat::Jet * leadingJet, pat::Jet * secondLeadingJet ){
  double deltaEta = 1e10;
  deltaEta = leadingJet->p4().Eta() - secondLeadingJet->p4().Eta() ;
  return deltaEta;
}

double ZeeH_channel::getDeltaEta( const reco::Candidate * firstB, const reco::Candidate * secondB ){
  double deltaEta = 1e10;
  deltaEta = firstB->eta() - secondB->eta() ;
  return deltaEta;
}

double ZeeH_channel::getDeltaPhi( pat::Jet* leadingJet, pat::Jet* secondLeadingJet){

  double deltaPhi = 1e10;
  deltaPhi = Geom::deltaPhi( leadingJet->p4().Vect(), secondLeadingJet->p4().Vect() ) ;
  return deltaPhi;

}

double ZeeH_channel::getPtAsymmetry(pat::Jet* leadingJet, pat::Jet* secondLeadingJet ){

  double asymmetry = 1e10;
  double ptDiff = leadingJet->p4().Pt() - secondLeadingJet->p4().Pt();
  double ptSum = leadingJet->p4().Pt() + secondLeadingJet->p4().Pt();
  asymmetry = ptDiff / ptSum;
  return asymmetry;
}

unsigned int ZeeH_channel::getAssociatedB( std::vector<TLorentzVector> bHadron_vector, pat::Jet* leadingJet){

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


double ZeeH_channel::getBBavProjection( pat::Jet* j1, pat::Jet* j2 ){

  TVector2 ci;
  TVector2 r;
  TVector2 v_j1( j1->p4().Eta(), j1->p4().Phi());
  TVector2 v_j2( j2->p4().Eta(), j2->p4().Phi());
  TVector2 bb = v_j2 - v_j1;
  TVector2 bbdir = bb.Unit();
  double proj = 0;
  double totProj = 0;
  
  std::vector<reco::PFCandidatePtr>
    patJetpfc = j1->getPFConstituents();
  for(size_t idx = 0; idx < patJetpfc.size(); idx++){
    ci.Set( patJetpfc.at(idx)->eta(), patJetpfc.at(idx)->phi() );
    r  = ci - v_j1;
    totProj += (r.Proj(bbdir)).Mod();
  }
  
  for(size_t idx = 0; idx < patJetpfc.size(); idx++){
    ci.Set( patJetpfc.at(idx)->eta(), patJetpfc.at(idx)->phi() );
    r  = ci - v_j1;
    proj += (r.X()*bbdir.X()+r.Y()*bbdir.Y())/totProj;
  }
  
  return proj;
  
}


// FIXED variabile consigliata nell'articolo teorico sulla color reconnection
// with bvertex information
TVector2 ZeeH_channel::getTvect( pat::Jet* patJet, TLorentzVector b ){

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
TVector2 ZeeH_channel::getTvect( pat::Jet* patJet ){

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
double ZeeH_channel::getDeltaTheta( pat::Jet* j1, pat::Jet* j2, TLorentzVector b1, TLorentzVector b2 ){

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
double ZeeH_channel::getDeltaTheta( pat::Jet* j1, pat::Jet* j2 ){

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


double ZeeH_channel::getDeltaX( pat::Jet* j1, pat::Jet* j2, TLorentzVector b1, TLorentzVector b2 ){

  double deltaX = 1e10;
  TVector2 v_j1(j1->p4().Eta(), j1->p4().Phi());
  TVector2 v_j2(j2->p4().Eta(), j2->p4().Phi());
  TVector2 v_b1(b1.Eta(), b1.Phi());
  TVector2 v_b2(b2.Eta(), b2.Phi());

  TVector2 t = getTvect(j1, b1);

  deltaX = t.X() - v_b2.X();

  return deltaX;

}

double ZeeH_channel::getDeltaY( pat::Jet* j1, pat::Jet* j2, TLorentzVector b1, TLorentzVector b2 ){

  double deltaY = 1e10;
  TVector2 v_j1(j1->p4().Eta(), j1->p4().Phi());
  TVector2 v_j2(j2->p4().Eta(), j2->p4().Phi());
  TVector2 v_b1(b1.Eta(), b1.Phi());
  TVector2 v_b2(b2.Eta(), b2.Phi());

  TVector2 t = getTvect(j1, b1);

  deltaY = t.Y() - v_b2.Y();

  return deltaY;

}

double ZeeH_channel::getMyVar_background( pat::Jet* patJet, TVector3 Bpos ){

  TVector3 t_vect;
  double patJetTrackPt = 1e10;
  double deltaEta = 1e10;
  double myvar =  0;
  reco::TrackRefVector patJetTrack;

  //loop su tutte le tracce del jet
  patJetTrack = patJet->associatedTracks();
  for(size_t idx = 0; idx < patJetTrack.size(); idx++){
    patJetTrackPt = patJetTrack.at(idx)->pt();
    t_vect.SetXYZ(patJetTrack.at(idx)->px(),patJetTrack.at(idx)->py(),patJetTrack.at(idx)->pz());
    deltaEta = TMath::Abs( t_vect.Eta() - Bpos.Eta() );
    myvar += deltaEta / patJetTrackPt; 
  }
  return myvar;
}

double ZeeH_channel::getMyVar_signal( pat::Jet* patJet, TVector3 Bpos, double BanglePhiEtaPlane ){

  TVector3 t_vect;
  double patJetTrackPt = 1e10;
  double distPL = 1e10;
  double myvar =  0;
  double jetPhi = 1e10;
  double jetEta = 1e10;
  reco::TrackRefVector patJetTrack;

  jetPhi = patJet->p4().Phi();
  jetEta = patJet->p4().Eta();

  //loop su tutte le tracce del jet
  patJetTrack = patJet->associatedTracks();
  for(size_t idx = 0; idx < patJetTrack.size(); idx++){
    patJetTrackPt = patJetTrack.at(idx)->pt();
    t_vect.SetXYZ(patJetTrack.at(idx)->px(),patJetTrack.at(idx)->py(),patJetTrack.at(idx)->pz());
    distPL =  TMath::Abs( jetPhi - jetEta - ( Bpos.Phi() - BanglePhiEtaPlane * Bpos.Eta() ) / TMath::Sqrt( 1 + TMath::Power(BanglePhiEtaPlane,2) ) );
    myvar += 1 / ( patJetTrackPt * distPL ); 
  }
  return myvar;
}


TVector2 ZeeH_channel::getBBdir( pat::Jet* j1, pat::Jet* j2 ){

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
inline pat::Jet* ZeeH_channel::whichJet(pat::Jet *j1, pat::Jet *j2){

  if( TMath::Abs( j1->p4().Eta() ) - TMath::Abs( j2->p4().Eta() ) > 0 )
    return j1;
  else
    return j2;
}

// return the opposite of whichJet
inline pat::Jet* ZeeH_channel::whichOtherJet(pat::Jet *j1, pat::Jet *j2){

  if( TMath::Abs( j1->p4().Eta() ) - TMath::Abs( j2->p4().Eta() ) < 0 )
    return j1;
  else
    return j2;
}


double ZeeH_channel::getHelicity( pat::Jet* jet , TVector3 boost ){
  double hel = 1e10;
  TLorentzVector j;
  j.SetPtEtaPhiE( jet->pt(), jet->eta(), jet->phi(), jet->energy() );
  j.Boost( -boost );
  hel = TMath::Cos( j.Vect().Angle( boost ) );
  return hel;
}


double ZeeH_channel::getHelicity( const reco::GenJet* jet , TVector3 boost ){
  double hel = 1e10;
  TLorentzVector j;
  j.SetPtEtaPhiE( jet->pt(), jet->eta(), jet->phi(), jet->energy() );
  j.Boost( -boost );
  hel = TMath::Cos( j.Vect().Angle( boost ) );
  return hel;
}

double ZeeH_channel::getHelicity( TLorentzVector b , TVector3 boost ){
  double hel = 1e10;
  b.Boost( -boost );
  hel = TMath::Cos( b.Vect().Angle( boost ) );
  return hel;
}


bool ZeeH_channel::isInFiducial( double eta ){
  double BarrelMaxEta = 1.4442;
  double EndCapMinEta = 1.56;
  double EndCapMaxEta = 2.5;
  if ( fabs(eta) < BarrelMaxEta ) 
    return true;
  else if (fabs(eta) < EndCapMaxEta  && fabs(eta) > EndCapMinEta )
    return true;
  return false;
}




void ZeeH_channel::beginJob()
{
  
  using namespace std;  
  edm::Service<TFileService> fs;

  tree_container["Zee_channel"]=fs->make<TTree>("Zee_channel","Zee_channel");

  abis::make_branch(tree_container,"Zhelicity"                     ,Zhelicity);
  abis::make_branch(tree_container,"higgsCandidate_mass"           ,higgsCandidate_mass);
  abis::make_branch(tree_container,"jetPtAsymmetry"                ,jetPtAsymmetry);
  abis::make_branch(tree_container,"leading_higgsHelicity"         ,leading_higgsHelicity);
  abis::make_branch(tree_container,"secondLeading_higgsHelicity"   ,secondLeading_higgsHelicity);
  abis::make_branch(tree_container,"AK7leadingDeltaTheta"          ,AK7leadingDeltaTheta);
  abis::make_branch(tree_container,"AK7secondLeadingDeltaTheta"    ,AK7secondLeadingDeltaTheta);
  abis::make_branch(tree_container,"leadingDeltaTheta"             ,leadingDeltaTheta);
  abis::make_branch(tree_container,"secondLeadingDeltaTheta"       ,secondLeadingDeltaTheta);
  abis::make_branch(tree_container,"iDeltaTheta"                   ,iDeltaTheta);
  abis::make_branch(tree_container,"jetDeltaR"                     ,JetDeltaR);
  abis::make_branch(tree_container,"Zcandidate_pt"                 ,Zcandidate_pt);
  abis::make_branch(tree_container,"Zcandidate_mass"                 ,Zcandidate_mass);
  abis::make_branch(tree_container,"higgsCandidate_pt"             ,higgsCandidate_pt);
  abis::make_branch(tree_container,"genbDeltaR"                    ,genbDeltaR);


}

void ZeeH_channel::endJob() {

  std::cout << "Number of events with at least two B hadrons = " << myEvents << std::endl;
  std::cout << "JOB FINISHED" << std::endl;

}

DEFINE_FWK_MODULE(ZeeH_channel);
