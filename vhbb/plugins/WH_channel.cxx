/* WH_channel_cxx                                    */
/* v2 April 2011                                     */
/* Bortignon Pierluigi                               */


#include "VHbb/iCode/interface/abis_func.h"
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

class WH_channel : public edm::EDAnalyzer
{
  
public:
  
  explicit WH_channel(const edm::ParameterSet&);

private:
  
  virtual void analyze(const edm::Event&, const edm::EventSetup&) ;
  virtual void beginJob() ;
  virtual void endJob() ;

  bool muonJetCleaning( const pat::Jet&, const reco::Muon, double );
  bool hasHiggsMother( const reco::Candidate* );
  bool hasBMother( const reco::Candidate* );
  bool hasBdaughters( const reco::Candidate * );
  double getAnglePhiEtaPlane( const pat::Jet* , const pat::Jet* );
  double getAnglePhiEtaPlane( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR( const pat::Jet* , const pat::Jet* );
  double getDeltaR( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR( TLorentzVector , const pat::Jet* );
  double getDeltaR( TVector3 , pat::Jet* );
  double getDeltaEta( const pat::Jet* , const pat::Jet* );
  double getDeltaEta( const reco::Candidate* , const reco::Candidate* );
  double getDeltaPhi( pat::Jet*, pat::Jet* );
  unsigned int getAssociatedB( std::vector<TLorentzVector> , const pat::Jet* );
  double getTheta( const pat::Jet* );
  double getPtAsymmetry(pat::Jet*, pat::Jet* );
  TVector2 getTvect( pat::Jet*, TLorentzVector );
  TVector2 getTvect( pat::Jet* );
  double getDeltaTheta( pat::Jet*, pat::Jet*, TLorentzVector, TLorentzVector );
  double getDeltaTheta( pat::Jet*, pat::Jet* );
  TVector2 getBBdir( pat::Jet* , pat::Jet* );
  inline pat::Jet* whichJet(pat::Jet*, pat::Jet*);
  inline pat::Jet* whichOtherJet(pat::Jet*, pat::Jet*);
  double getHelicity( pat::Jet*, TVector3 );
  double getHelicity( const reco::GenJet*, TVector3 );
  double getHelicity( TLorentzVector, TVector3 );


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
  std::map<std::string,TTree*> tree_container;
  std::map<std::string,TH1D*> histocontainer_;
  std::map<std::string,TH2D*> histocontainer_2;
  std::map<std::string,TH3D*> histocontainer_3;

//   edm::InputTag akt5pfJetsLabel_;
  edm::InputTag muonLabel_;
  edm::InputTag genpLabel_;
  edm::InputTag patMetLabel_;
  edm::InputTag patJetLabel_;
  edm::InputTag ak7patJetLabel_;
  edm::InputTag WMuNuLabel_;
  edm::ParameterSet pfJetIdSelector_;

  std::vector<pat::Jet*> v_akt5pfj;
  std::vector<pat::Jet*> v_akt7pfj;

  // Member data
  Int_t n_event;  
  Int_t myEvents;

  Double_t muonJetCleaningDRcut;
  Double_t jetDRcut;
  Double_t jetPtAsymmetryHigherCut;
  Double_t WCandidatePtCut;
  Double_t HCandidatePtCut;
  Double_t WH_deltaPhiCut;
  Double_t minBTagging;
  Double_t maxBTagging;
  Double_t helicityCut;
  Double_t jetPtThreshold;
  Double_t WMassLowerCut;
  Double_t WMassHigherCut;
  Double_t jetVetoPtCut;

  Int_t nOfak5;
  Int_t nOfak7;

  Double_t Wcandidate_pt;
  Double_t Wcandidate_mass;
  Double_t leading_higgsHelicity;
  Double_t secondLeading_higgsHelicity;
  Double_t iDeltaTheta;
  Double_t higgs_pt;
  Double_t higgsCandidate_mass;
  Double_t vector_pt;
  Double_t higgsCandidate_pt;
  Double_t jetAnglePhiEtaPlane ;
  Double_t BanglePhiEtaPlane ;
  Double_t deltaR_signal ;
  Double_t deltaR_background ;
  Double_t invmass_background ;
  Double_t alphaAngle ;
  Double_t betaDistance ;
  Double_t deltaR_general ;
  Double_t BdeltaEta;
  Double_t JetDeltaEta;
  Double_t JetDeltaEtaSmart;
  Double_t epsilonDeltaEta;
  Double_t gammaDeltaR;
  Double_t BdeltaR;
  Double_t JetDeltaR;
  Double_t genbDeltaR;
  Double_t leadingBTag;
  Double_t secondLeadingBTag;

  Double_t Whelicity;

  Double_t leadingDeltaTheta;
  Double_t secondLeadingDeltaTheta;
  Double_t AK7leadingDeltaTheta;
  Double_t AK7secondLeadingDeltaTheta;

  Double_t jetDeltaPhi;
  Double_t jetPtAsymmetry;

  bool jetVeto;

};

WH_channel::WH_channel(const edm::ParameterSet& iConfig) : 

  tree_container(),
  histocontainer_(),
  histocontainer_2(),
  histocontainer_3(),

  //cleaning cut
  muonJetCleaningDRcut(iConfig.getUntrackedParameter<double>("muonJetCleaningDRcut_")),
  WMassLowerCut(iConfig.getUntrackedParameter<double>("WMassLowerCut")),
  WMassHigherCut(iConfig.getUntrackedParameter<double>("WMassHigherCut")),
  minBTagging(iConfig.getUntrackedParameter<double>("minBTagging")),
  maxBTagging(iConfig.getUntrackedParameter<double>("maxBTagging")),
  WCandidatePtCut(iConfig.getUntrackedParameter<double>("WCandidatePtCut")),
  HCandidatePtCut(iConfig.getUntrackedParameter<double>("HCandidatePtCut")),
  WH_deltaPhiCut(iConfig.getUntrackedParameter<double>("WH_deltaPhiCut")),
  jetVetoPtCut(iConfig.getUntrackedParameter<double>("jetVetoPtCut")),
  jetPtThreshold(iConfig.getUntrackedParameter<double>("jetPtThreshold")),

  //edm collections
  genpLabel_(iConfig.getUntrackedParameter<edm::InputTag>("genPart")),
  muonLabel_(iConfig.getUntrackedParameter<edm::InputTag>("muonCand")),
//   akt5pfJetsLabel_(iConfig.getUntrackedParameter<edm::InputTag>("akt5pfJets")),
  patJetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("selectedPatJetsCand")),
  ak7patJetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("ak7patJets")),
  pfJetIdSelector_(iConfig.getParameter<edm::ParameterSet>("pfJetIDSelector")),
  patMetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("patMetsCand")),
  WMuNuLabel_(iConfig.getUntrackedParameter<edm::InputTag>("WMuNuCand"))
{

  //Initialize counters
  n_event = 0;
  myEvents = 0;

}   

void WH_channel::analyze(const edm::Event& iEvent, const edm::EventSetup& setup)
{
  ++n_event;

  //initialising each events
  v_akt5pfj.clear();
  v_akt7pfj.clear();
  jetVeto = false;

  std::cout << "*** Analyzing " << iEvent.id() << " n_event = " << n_event << std::endl << std::endl;

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

  // Generated particles handle
  edm::Handle<reco::GenParticleCollection> genP;
  iEvent.getByLabel(genpLabel_,genP);
  const reco::GenParticleCollection &genParticles = *genP.product();

  //Wmunu
  edm::Handle< std::vector< reco::WMuNuCandidate > > WMuNuCollection;
  iEvent.getByLabel(WMuNuLabel_, WMuNuCollection);
  const reco::WMuNuCandidate& Wcandidate = WMuNuCollection->at(0);


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


  std::vector<const reco::Candidate*> v_muon;
  std::vector<const reco::Candidate*> v_met;
  pat::Jet *leadingJet;
  pat::Jet *secondLeadingJet;
  pat::Jet *AK7leadingJet;
  pat::Jet *AK7secondLeadingJet;
  pat::Jet *iJet;
  pat::Jet *otherJet;
  
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
  
  std::sort(v_akt5pfj.begin(), v_akt5pfj.end(), BTagComparator);
      
  //Event selection: at least two jets one W
  if( v_akt5pfj.size() < 2
      or  WMuNuCollection->size() < 1 )
    return void();

  //Associate the first two AKT5 and AK7PF
  for(size_t jetIdx = 0; jetIdx < ak7patJet.size(); ++jetIdx){
    if( ak7patJet.at(jetIdx).isPFJet() == true 
 	and pfJetIDFunctor( ak7patJet.at(jetIdx), ret ) == true 
	and ak7patJet.at(jetIdx).correctedJet("abs").pt() > jetPtThreshold
	and muonJetCleaning( ak7patJet.at(jetIdx), Wcandidate.getMuon(), muonJetCleaningDRcut ) == false ){
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

  nOfak5 = v_akt5pfj.size();
  nOfak7 = v_akt7pfj.size();

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

  leadingBTag = leadingJet->bDiscriminator("combinedSecondaryVertexBJetTags");
  secondLeadingBTag = secondLeadingJet->bDiscriminator("combinedSecondaryVertexBJetTags");

  //taglio sul btag
  if( ( leadingJet->bDiscriminator("combinedSecondaryVertexBJetTags") < maxBTagging and
	secondLeadingJet->bDiscriminator("combinedSecondaryVertexBJetTags") < maxBTagging )
      or ( leadingJet->bDiscriminator("combinedSecondaryVertexBJetTags") < minBTagging or
	   secondLeadingJet->bDiscriminator("combinedSecondaryVertexBJetTags") < minBTagging ) )
    return void();

  reco::CompositeCandidate higgsCandidate;
  higgsCandidate.addDaughter( *v_akt5pfj.at(0) );
  higgsCandidate.addDaughter( *v_akt5pfj.at(1) );
  AddFourMomenta addp4;
  addp4.set(higgsCandidate);
  higgsCandidate_pt = higgsCandidate.p4().Pt();
  higgsCandidate_mass = higgsCandidate.p4().M();
  Wcandidate_pt = Wcandidate.p4().Pt();
  Wcandidate_mass = Wcandidate.p4().M();
  double WH_deltaPhi = Geom::deltaPhi(higgsCandidate.p4(), Wcandidate.p4());
  TLorentzVector higgsP4;
  higgsP4.SetPtEtaPhiE( higgsCandidate.pt() , 
			higgsCandidate.eta(),
			higgsCandidate.phi(),
			higgsCandidate.energy() );
  TVector3 higgsBoost;
  higgsBoost = higgsP4.BoostVector();
  leading_higgsHelicity = getHelicity( leadingJet, higgsBoost );
  secondLeading_higgsHelicity = getHelicity( secondLeadingJet, higgsBoost );

  TLorentzVector muonP4;
  muonP4.SetPtEtaPhiE( Wcandidate.getMuon().pt(),
		       Wcandidate.getMuon().eta(),
		       Wcandidate.getMuon().phi(),
		       Wcandidate.getMuon().energy() );
  
  TLorentzVector Wp4;
  Wp4.SetPtEtaPhiE( Wcandidate.pt() , 
		    Wcandidate.eta(),
		    Wcandidate.phi(),
		    Wcandidate.energy() );
  TVector3 Wboost;
  Wboost = Wp4.BoostVector();  
  Whelicity = getHelicity( muonP4, Wboost );


  if( Wcandidate_pt < WCandidatePtCut
      or TMath::Abs(WH_deltaPhi) < WH_deltaPhiCut )
    return void();

  //Higgs pt cut
  if( higgsCandidate_pt < HCandidatePtCut )
    return void();
  
  // order jet using pt for the jet veto
  v_akt5pfj.erase( v_akt5pfj.begin() );
  v_akt5pfj.erase( v_akt5pfj.begin() );
  if(v_akt5pfj.size() > 0){
    std::sort(v_akt5pfj.begin(), v_akt5pfj.end(), ptJetComparator);
    //JET VETO
    //no additional akt5pfjets with pt > 50 GeV
    if( v_akt5pfj.at(0)->p4().pt() > jetVetoPtCut ){
      return void();
    }
  }
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

  //pull for AKT5PF jet
  TVector2 secondLeadingT;
  TVector2 leadingT;
  TVector2 BBdir;  
  secondLeadingT = getTvect(secondLeadingJet);
  leadingT = getTvect(leadingJet);
  if(secondLeadingT.Mod() < 1e-7 
     or leadingT.Mod() < 1e-7 )
    return void();
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
  
  tree_container["WMuNu_channel"]->Fill();
  
  v_akt5pfj.clear();
  v_akt7pfj.clear();
  genb.clear();  

}//END EVENT LOOP

//puliamo i pfjet dai muoni con un deltaR
// if it is true get rid of the jet
bool WH_channel::muonJetCleaning(const pat::Jet& tmpJet, const reco::Muon muCol, double deltaRcut){
  bool clean = false;
  double deltaR = 1e10;
  deltaR = Geom::deltaR(tmpJet.p4().Vect(), muCol.p4().Vect() );
  if( deltaR < deltaRcut )
    clean = true; 
  return clean;
}

//metodo per guardare se ha un Higgs come antenato
bool WH_channel::hasHiggsMother( const reco::Candidate * particle ){
  bool hashiggsmother = false;
  while ( particle->numberOfMothers() != 0 ){
    if( particle->mother()->pdgId() == 25 )
      hashiggsmother = true;
    particle = particle->mother();
  }
  return hashiggsmother;
}

//metodo per guardare se ha un b come antenato
bool WH_channel::hasBMother( const reco::Candidate * particle ){
  bool hasBmother = false;
  while ( particle->numberOfMothers() != 0 ){
    if( TMath::Abs(particle->mother()->pdgId()) == 5 )
      hasBmother = true;
    particle = particle->mother();
  }
  return hasBmother;
}

//check if there are dbflavoured daughters
bool WH_channel::hasBdaughters( const reco::Candidate * particle ){
  bool myDaughterHasBottom = false;
  for(size_t myDau = 0; myDau < particle->numberOfDaughters(); myDau++){
    HepPDT::ParticleID myDaughter( particle->daughter(myDau)->pdgId() ); 
    myDaughterHasBottom += myDaughter.hasBottom();
  }
  return myDaughterHasBottom;
}

// calcolo dell'angolo nel piano eta phi della retta conguingente due jet
double WH_channel::getAnglePhiEtaPlane( const pat::Jet *leadingJet , const pat::Jet *secondLeadingJet ){
  double angle = 1e10;
  double deltaPhi = leadingJet->p4().Phi() - secondLeadingJet->p4().Phi();
  double deltaEta = leadingJet->p4().Eta() - secondLeadingJet->p4().Eta();
  angle = TMath::ATan2( deltaPhi, deltaEta );
  return angle;
}

// calcolo dell'angolo nel piano eta phi della retta conguingente due b hadron
double WH_channel::getAnglePhiEtaPlane( const reco::Candidate *firstB , const reco::Candidate *secondB ){
  double angle = 1e10;
  double deltaPhi = firstB->phi() - secondB->phi();
  double deltaEta = firstB->eta() - secondB->eta();
  angle = TMath::ATan2( deltaPhi, deltaEta );
  return angle;
}

double WH_channel::getDeltaR( const pat::Jet * leadingJet, const pat::Jet * secondLeadingJet ){
  double deltaR = 1e10;
  deltaR = Geom::deltaR( leadingJet->p4().Vect(), secondLeadingJet->p4().Vect() );
  return deltaR;
}

double WH_channel::getDeltaR( const reco::Candidate * firstB, const reco::Candidate * secondB ){
  double deltaR = 1e10;
  deltaR = Geom::deltaR( firstB->momentum(), secondB->momentum() );
  return deltaR;
}

double WH_channel::getDeltaR( TLorentzVector TLV, const pat::Jet * patJet ){
  double deltaR = 1e10;
  TVector3 JetVector;
  JetVector.SetXYZ( patJet->p4().Px(), patJet->p4().Py(), patJet->p4().Pz() );
  deltaR = JetVector.DeltaR( TLV.Vect() ) ;
  return deltaR;
}


double WH_channel::getDeltaEta( const pat::Jet * leadingJet, const pat::Jet * secondLeadingJet ){
  double deltaEta = 1e10;
  deltaEta = leadingJet->p4().Eta() - secondLeadingJet->p4().Eta() ;
  return deltaEta;
}

double WH_channel::getDeltaEta( const reco::Candidate * firstB, const reco::Candidate * secondB ){
  double deltaEta = 1e10;
  deltaEta = firstB->eta() - secondB->eta() ;
  return deltaEta;
}

double WH_channel::getDeltaPhi( pat::Jet* leadingJet, pat::Jet* secondLeadingJet){

  double deltaPhi = 1e10;
  deltaPhi = Geom::deltaPhi( leadingJet->p4().Vect(), secondLeadingJet->p4().Vect() ) ;
  return deltaPhi;

}

unsigned int WH_channel::getAssociatedB( std::vector<TLorentzVector> bHadron_vector, const pat::Jet* leadingJet ){

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


// variabile consigliata nell'articolo teorico sulla color reconnection
double WH_channel::getTheta( const pat::Jet* patJet ){

  reco::TrackRefVector patJetTrack;
  TVector3 t_Vect;
  TVector3 ci;
  TVector3 J;
  TVector3 r;
  double patJetTrackPt = 1e10;
  double theta = 1e10;
  double r_mag = 1e10;

  //loop su tutte le tracce del primo jet
  patJetTrack = patJet->associatedTracks();
  for(size_t idx = 0; idx < patJetTrack.size(); idx++){
    patJetTrackPt = patJetTrack.at(idx)->pt();
    ci.SetXYZ(patJetTrack.at(idx)->px(),patJetTrack.at(idx)->py(),patJetTrack.at(idx)->pz());
    ci *= 1/TMath::Sqrt(patJetTrack.at(idx)->momentum().Mag2());
    J.SetXYZ( patJet->px(), patJet->py(), patJet->pz() );
    J *= 1/TMath::Sqrt(patJet->p4().Vect().Mag2());
    r  = ci - J;
    r_mag = r.Mag();
    t_Vect += ( (patJetTrackPt * r_mag) / patJet->p4().Pt() ) * r;
  }

  return theta = t_Vect.Theta();
  
}

double WH_channel::getPtAsymmetry(pat::Jet* leadingJet, pat::Jet* secondLeadingJet ){

  double asymmetry = 1e10;
  double ptDiff = leadingJet->p4().Pt() - secondLeadingJet->p4().Pt();
  double ptSum = leadingJet->p4().Pt() + secondLeadingJet->p4().Pt();
  asymmetry = ptDiff / ptSum;
  return asymmetry;
}

// FIXED variabile consigliata nell'articolo teorico sulla color reconnection
// with bvertex information
TVector2 WH_channel::getTvect( pat::Jet* patJet, TLorentzVector b ){

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
TVector2 WH_channel::getTvect( pat::Jet* patJet ){

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
double WH_channel::getDeltaTheta( pat::Jet* j1, pat::Jet* j2, TLorentzVector b1, TLorentzVector b2 ){

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
double WH_channel::getDeltaTheta( pat::Jet* j1, pat::Jet* j2 ){

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



TVector2 WH_channel::getBBdir( pat::Jet* j1, pat::Jet* j2 ){

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
inline pat::Jet* WH_channel::whichJet(pat::Jet *j1, pat::Jet *j2){

  if( TMath::Abs( j1->p4().Eta() ) - TMath::Abs( j2->p4().Eta() ) > 0 )
    return j1;
  else
    return j2;
}

// return the opposite of whichJet
inline pat::Jet* WH_channel::whichOtherJet(pat::Jet *j1, pat::Jet *j2){

  if( TMath::Abs( j1->p4().Eta() ) - TMath::Abs( j2->p4().Eta() ) < 0 )
    return j1;
  else
    return j2;
}


double WH_channel::getHelicity( pat::Jet* jet , TVector3 boost ){
  double hel = 1e10;
  TLorentzVector j;
  j.SetPtEtaPhiE( jet->pt(), jet->eta(), jet->phi(), jet->energy() );
  j.Boost( -boost );
  hel = TMath::Cos( j.Vect().Angle( boost ) );
  return hel;
}


double WH_channel::getHelicity( const reco::GenJet* jet , TVector3 boost ){
  double hel = 1e10;
  TLorentzVector j;
  j.SetPtEtaPhiE( jet->pt(), jet->eta(), jet->phi(), jet->energy() );
  j.Boost( -boost );
  hel = TMath::Cos( j.Vect().Angle( boost ) );
  return hel;
}

double WH_channel::getHelicity( TLorentzVector b , TVector3 boost ){
  double hel = 1e10;
  b.Boost( -boost );
  hel = TMath::Cos( b.Vect().Angle( boost ) );
  return hel;
}



void WH_channel::beginJob()
{
  
  using namespace std;  
  edm::Service<TFileService> fs;

  abis::make_branch(tree_container,"Whelicity"                     ,Whelicity);
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
  abis::make_branch(tree_container,"Wcandidate_pt"                 ,Wcandidate_pt);
  abis::make_branch(tree_container,"higgsCandidate_pt"             ,higgsCandidate_pt);
  abis::make_branch(tree_container,"genbDeltaR"                    ,genbDeltaR);
  abis::make_branch(tree_container,"leadingBTag"                   ,leadingBTag);
  abis::make_branch(tree_container,"secondLeadingBTag"             ,secondLeadingBTag);
  abis::make_branch(tree_container,"jetVeto"                       ,jetVeto);
  abis::make_branch(tree_container,"nOfak5"                        ,nOfak5);
  abis::make_branch(tree_container,"nOfak7"                        ,nOfak7);

}

void WH_channel::endJob() {

  std::cout << "Number of events with at least two B hadrons = " << myEvents << std::endl;
  std::cout << "JOB FINISHED" << std::endl;

}

DEFINE_FWK_MODULE(WH_channel);
