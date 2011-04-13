/* Analyzer for the QuadJet    */

/* Version 0                  */
/* March 2011                 */
/* Bortignon Pierluigi        */
/* With BTagging              */

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
#include "VHbb/iCode/interface/linked_ptr.h"
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
//#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
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
#include "CommonTools/CandUtils/interface/AddFourMomenta.h" 

#include "CommonTools/UtilAlgos/interface/TFileService.h"
//
// class decleration
//
// using namespace reco;
using namespace std;
using namespace edm;

class QuadJet : public edm::EDAnalyzer
{
  
public:
  
  explicit QuadJet(const edm::ParameterSet&);

private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) ;
  virtual void endJob() ;

  inline int getSign(double ); 
  bool muonJetCleaning( const pat::Jet&, const std::vector<pat::Muon>&, double );
  bool jetMuonCleaning( std::vector<const pat::Jet*>, pat::Muon*, double );
  bool hasHiggsMother( const reco::Candidate* );
  bool hasBdaughters( const reco::Candidate * );
  double getAnglePhiEtaPlane( pat::Jet* , pat::Jet* );
  double getAnglePhiEtaPlane( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR( pat::Jet* , pat::Jet* );
  double getDeltaR( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR( TLorentzVector , pat::Jet* );
  double getDeltaEta( pat::Jet* , pat::Jet* );
  double getDeltaEta( const reco::Candidate* , const reco::Candidate* );
  double getDeltaPhi( pat::Jet*, pat::Jet* );
  TVector2 getTvect( pat::Jet*, TLorentzVector );
  TVector2 getTvect( pat::Jet* );
  double getDeltaTheta( pat::Jet*, pat::Jet*, TLorentzVector, TLorentzVector );
  double getDeltaTheta( pat::Jet*, pat::Jet* );
  double getPtAsymmetry(pat::Jet*, pat::Jet* );
  unsigned int getAssociatedB( std::vector<TLorentzVector> , pat::Jet* );

  TVector2 getBBdir( pat::Jet*, pat::Jet* );
  inline pat::Jet* whichJet(pat::Jet*, pat::Jet*);
  inline pat::Jet* whichOtherJet(pat::Jet*, pat::Jet*);

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
  std::map<std::string,TH1D*> histocontainer_;
  std::map<std::string,TH2D*> histocontainer_2;
  std::map<std::string,TH3D*> histocontainer_3;

  edm::InputTag akt5pfJetsLabel_;
  edm::InputTag muonLabel_;
  edm::InputTag patJetLabel_;
  edm::ParameterSet pfJetIdSelector_;

  std::vector< pat::Jet* > v_akt5pfj;
  // Member data
  unsigned int goodJetCounter;
  unsigned int badJetCounter;

  Int_t n_event;  
  Int_t myEvents;

  // parameters set
  Double_t muonJetCleaningPtcut;
  Double_t  minBTagging;
  Double_t  maxBTagging;

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
  Double_t epsilonDeltaEta;
  Double_t gammaDeltaR;
  Double_t BdeltaR;
  Double_t JetDeltaR;

  Double_t secondLeadingDeltaTheta;
  Double_t leadingDeltaTheta;

  Double_t JetDeltaPhi;
  Double_t jetPtAsymmetry;

  Double_t myVar_background;
  Double_t myVar_signal;

  bool bHadron;  

};

QuadJet::QuadJet(const edm::ParameterSet& iConfig) : 

  histocontainer_(),
  histocontainer_2(),
  histocontainer_3(),

  //cleaning cut
  muonJetCleaningPtcut(iConfig.getUntrackedParameter<double>("muonJetCleaningPtcut")),
  minBTagging(iConfig.getUntrackedParameter<double>("minBTagging")),
  maxBTagging(iConfig.getUntrackedParameter<double>("maxBTagging")),

  //edm collection
  muonLabel_(iConfig.getUntrackedParameter<edm::InputTag>("muonCand")),
  akt5pfJetsLabel_(iConfig.getUntrackedParameter<edm::InputTag>("akt5pfJets")),
  patJetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("patJets")),
  pfJetIdSelector_(iConfig.getParameter<edm::ParameterSet>("pfJetIDSelector") )
{

  //Initialize counters
  n_event = 0;
  myEvents = 0;

}   

void QuadJet::analyze(const edm::Event& iEvent, const edm::EventSetup& setup)
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

  pat::Jet *leadingJet;
  pat::Jet *secondLeadingJet;
  pat::Jet *btag1Jet;
  pat::Jet *btag2Jet;
  pat::Jet *iJet;
  pat::Jet *otherJet;

  reco::CandidateCollection BhadronCollection;
  reco::CandidateCollection BhadronCollectionSignal;
  reco::CandidateCollection BhadronCollectionBackground;

  // needed for the jetId
  pat::strbitset ret = pfJetIDFunctor.getBitTemplate();

  PFJetIDSelectionFunctor jetIDLoose( PFJetIDSelectionFunctor::FIRSTDATA, PFJetIDSelectionFunctor::LOOSE );
  pat::strbitset retLOOSE = jetIDLoose.getBitTemplate();

  // count the good jets
  goodJetCounter = 0;
  badJetCounter = 0;

  std::cout << " Start after handlying " << std::endl;

  // The jets are pt ordered. unfortunately leptons are considered as akt5pfjet -> need cleaning
  for(size_t jetIdx = 0; jetIdx < patJet.size(); ++jetIdx){
    if( patJet.at(jetIdx).isPFJet() == true 
	//       if( jetIDLoose( patJet.at(jetIdx), retLOOSE ) == true ){
	and muonJetCleaning( patJet.at(jetIdx), muons, muonJetCleaningPtcut ) == false ){
      goodJetCounter++;
      //      v_akt5pfj.push_back( &(patJet.at(jetIdx)) );
      v_akt5pfj.push_back( new pat::Jet (patJet.at(jetIdx).correctedJet("abs")) );
      //       }
    }
    else{
      badJetCounter++;
    }
  }

  std::cout << "a" << std::endl;

  if( v_akt5pfj.size() < 4 )
    return void();

  std::cout << "b" << std::endl;

  //no additional akt5pfjets with pt > 20 GeV
  if( v_akt5pfj.size() > 3
      and v_akt5pfj.at(3)->p4().pt() > 20 )
    return void();

  std::cout << "c" << std::endl;

  // REAL BTAGGING
  //ordering jets using BTagging information
  std::sort(v_akt5pfj.begin(), v_akt5pfj.end(), btagComparator);    
  histocontainer_["h_minTagger"]->Fill( v_akt5pfj.at(0)->bDiscriminator("combinedSecondaryVertexBJetTags") );
  histocontainer_["h_maxTagger"]->Fill( v_akt5pfj.at(1)->bDiscriminator("combinedSecondaryVertexBJetTags") );
  if( ( ( v_akt5pfj.at(0)->bDiscriminator("combinedSecondaryVertexBJetTags") ) < 0.9 )
      or ( ( v_akt5pfj.at(1)->bDiscriminator("combinedSecondaryVertexBJetTags") )  < 0.44 ) )
    return void();
  btag1Jet = v_akt5pfj.at(0);
  btag2Jet = v_akt5pfj.at(1);

  std::cout << "d" << std::endl;

  reco::CompositeCandidate higgsCandidate;
  higgsCandidate.addDaughter( *v_akt5pfj.at(0) );
  higgsCandidate.addDaughter( *v_akt5pfj.at(1) );
  AddFourMomenta addp4;
  addp4.set(higgsCandidate);
  higgsCandidate_pt = higgsCandidate.p4().Pt();

  std::cout << "e" << std::endl;

  //delete the most btagged and reorder with pt
  v_akt5pfj.erase( v_akt5pfj.begin() );
  v_akt5pfj.erase( v_akt5pfj.begin() );
  std::sort(v_akt5pfj.begin(), v_akt5pfj.end(), ptJetComparator);
  leadingJet = v_akt5pfj.at(0);
  secondLeadingJet = v_akt5pfj.at(1);

  std::cout << "f" << std::endl;


  // fatJet Candidate  
  reco::CompositeCandidate fatJetCandidate;
  fatJetCandidate.addDaughter( *v_akt5pfj.at(0) );
  fatJetCandidate.addDaughter( *v_akt5pfj.at(1) );
  AddFourMomenta addFatJetp4;
  addFatJetp4.set(fatJetCandidate);
  double fatJetCandidate_pt = fatJetCandidate.p4().Pt();
  double fatJetHiggs_deltaPhi = Geom::deltaPhi(higgsCandidate.p4(), fatJetCandidate.p4());

  std::cout << "g" << std::endl;

  // Event selection
  if( fatJetCandidate_pt < 155
      or TMath::Abs(fatJetHiggs_deltaPhi) < 2.75 )
    return void();  
  
  myEvents++;    

  JetDeltaR = getDeltaR( leadingJet, secondLeadingJet );
  JetDeltaEta = TMath::Abs( getDeltaEta( secondLeadingJet, leadingJet ) );
  JetDeltaPhi = getDeltaPhi( secondLeadingJet, leadingJet );
  TVector2 secondLeadingT;
  TVector2 leadingT;
  TVector2 BBdir;

//   std::vector<reco::PFCandidatePtr>
//     secondLeadingPfc = secondLeadingJet->getPFConstituents();
//   for(size_t idx = 0; idx < secondLeadingPfc.size(); idx++){
//     if( secondLeadingPfc.at(idx)->charge() != 0 ){
//       histocontainer_["h_pfcMass"]->Fill( secondLeadingPfc.at(idx)->mass() );
//       histocontainer_["h_pfcEta"]->Fill( secondLeadingPfc.at(idx)->eta() );
//       histocontainer_["h_pfcPhi"]->Fill( secondLeadingPfc.at(idx)->phi() );
//       histocontainer_2["h2_pfcEtaPhi"]->Fill( secondLeadingPfc.at(idx)->eta(), secondLeadingPfc.at(idx)->phi() );
//     }
//   }
  
  secondLeadingT = getTvect(secondLeadingJet);
  leadingT = getTvect(leadingJet);

  if( secondLeadingT.Mod() < 1e-7 
      or leadingT.Mod() < 1e-7 )
    return void();
  

  histocontainer_2["h2_higgsMass_invmassJet"]->Fill( higgsCandidate.p4().M(), fatJetCandidate.p4().M() );

  secondLeadingT = getTvect(secondLeadingJet);
  leadingT = getTvect(leadingJet);
  secondLeadingDeltaTheta = TMath::Abs( getDeltaTheta( secondLeadingJet , leadingJet ) );
  leadingDeltaTheta = TMath::Abs( getDeltaTheta( leadingJet, secondLeadingJet ) );
  histocontainer_["h_HigherDeltaTheta"]->Fill(secondLeadingDeltaTheta);
  histocontainer_["h_LowerDeltaTheta"]->Fill(leadingDeltaTheta);
  histocontainer_2["h2_HigherDeltaTheta_LowerDeltaTheta"]->Fill(TMath::Abs(secondLeadingDeltaTheta), TMath::Abs(leadingDeltaTheta));
  histocontainer_2["h2_LowerDeltaTheta_invmassJet"]->Fill(leadingDeltaTheta, fatJetCandidate.p4().M());
  histocontainer_2["h2_HigherDeltaTheta_invmassJet"]->Fill(secondLeadingDeltaTheta, fatJetCandidate.p4().M());

  histocontainer_["h_HigherTheta"]->Fill( secondLeadingT.Phi() );
  histocontainer_["h_LowerTheta"]->Fill( leadingT.Phi() );


  // plots only the closest to the beam
  iJet = whichJet(leadingJet, secondLeadingJet);  
  otherJet = whichOtherJet( leadingJet, secondLeadingJet);
  TVector2 iT;
  iT = getTvect( iJet );
  double iTheta = 1e10;
  double iDeltaTheta = 1e10;
  iTheta = iT.Phi();
  histocontainer_["h_theta"]->Fill(iTheta);

  iDeltaTheta = TMath::Abs( getDeltaTheta( iJet , otherJet ) );
    
  BBdir =  getBBdir( iJet, otherJet );
  histocontainer_["h_BBdir"]->Fill( BBdir.Phi() );
  histocontainer_2["h2_BBdirdPhi"]->Fill( BBdir.Phi() , 
					  getDeltaPhi( iJet , otherJet ) );
  histocontainer_2["h2_BBdirdEta"]->Fill( BBdir.Phi() , 
					  getDeltaEta( iJet , otherJet ) );
    
  //    histocontainer_["h_BBdir"]->Fill( BBdir.Phi() );
  histocontainer_["h_BBdEta"]->Fill( getDeltaEta( iJet, otherJet ) );
  histocontainer_["h_BBdPhi"]->Fill( getDeltaPhi( iJet, otherJet ) );
  histocontainer_2["h2_BBdEtadPhi"]->Fill( getDeltaEta( iJet , otherJet ), 
					   getDeltaPhi( iJet , otherJet ) );
  
  if(TMath::Abs(iJet->p4().Eta()) < 0.2 )
    histocontainer_["h_theta_central"]->Fill( iT.Phi() );
  if(TMath::Abs(iJet->p4().Eta()) > 0.6 and TMath::Abs(iJet->p4().Eta() < 0.8))
    histocontainer_["h_theta_forward"]->Fill( iT.Phi() );
  
  histocontainer_["h_theta"]->Fill( iT.Phi() );
  //    histocontainer_["h_theta"]->Fill( otherT.Phi() );
  histocontainer_["h_deltaTheta"]->Fill(iDeltaTheta);
  //    histocontainer_["h_deltaTheta"]->Fill(otherDeltaTheta);
  
  histocontainer_2["h2_theta_invmassJet"]->Fill(iT.Phi(), fatJetCandidate.p4().M());
  histocontainer_2["h2_theta_JetDeltaEta"]->Fill(iT.Phi(), JetDeltaEta);
  histocontainer_2["h2_theta_JetDeltaR"]->Fill(iT.Phi(), JetDeltaR);
  histocontainer_2["h2_theta_JetDeltaPhi"]->Fill(iT.Phi(), JetDeltaPhi);
  histocontainer_2["h2_theta_TvectMod"]->Fill(iT.Phi(), iT.Mod());
  
  histocontainer_2["h2_deltaTheta_invmassJet"]->Fill(iDeltaTheta, fatJetCandidate.p4().M());
  histocontainer_2["h2_deltaTheta_JetDeltaEta"]->Fill(iDeltaTheta, JetDeltaEta);
  histocontainer_2["h2_deltaTheta_JetDeltaR"]->Fill(iDeltaTheta, JetDeltaR);
  histocontainer_2["h2_deltaTheta_JetDeltaPhi"]->Fill(iDeltaTheta, JetDeltaPhi);
  histocontainer_2["h2_deltaTheta_TvectMod"]->Fill(iDeltaTheta, iT.Mod());
  
  histocontainer_2["h2_absDeltatheta_invmassJet"]->Fill(TMath::Abs(iDeltaTheta), fatJetCandidate.p4().M());
  histocontainer_2["h2_absDeltatheta_JetDeltaEta"]->Fill(TMath::Abs(iDeltaTheta), JetDeltaEta);
  histocontainer_2["h2_absDeltatheta_JetDeltaR"]->Fill(TMath::Abs(iDeltaTheta), JetDeltaR);
  histocontainer_2["h2_absDeltatheta_JetDeltaPhi"]->Fill(TMath::Abs(iDeltaTheta), JetDeltaPhi);
  
  //if I do not create the jet I must not delete it
  //   for(std::vector< pat::Jet*>::const_iterator iter = v_akt5pfj.begin(); 
  //       iter != v_akt5pfj.end();
  //       iter++ )
  //     delete *iter;
  
  v_akt5pfj.clear();
  
}//END EVENT LOOP


inline int QuadJet::getSign(double v) { return v > 0 ? 1 : (v < 0 ? -1 : 0); } 

//puliamo i pfjet dai muoni con un deltaR
// if it is true get rid of the jet
bool QuadJet::muonJetCleaning(const pat::Jet& tmpJet, const std::vector<pat::Muon>& muCol, double deltaPtcut){
  bool clean = false;
//   double deltaR = 1e10;
  double deltaPt = 1e10;
  for(size_t muIdx = 0; muIdx < muCol.size(); ++muIdx){
//     deltaR = Geom::deltaR(tmpJet.p4().Vect(), muCol.at(muIdx).p4().Vect() );
//     if( deltaR < deltaRcut )
    deltaPt = TMath::Abs(muCol.at(muIdx).p4().Pt() - tmpJet.p4().Pt());
    if( deltaPt < deltaPtcut )
      clean = true;
  }  
  return clean;
}

//puliamo i muoni non isolati
// if it is true get rid of the muon
bool QuadJet::jetMuonCleaning( std::vector< const pat::Jet*> jetCol, pat::Muon* mu, double deltaRcut){
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
bool QuadJet::hasHiggsMother( const reco::Candidate * particle ){
  bool hashiggsmother = false;
  while ( particle->numberOfMothers() != 0 ){
    if( particle->mother()->pdgId() == 25 )
      hashiggsmother = true;
    particle = particle->mother();
  }
  return hashiggsmother;
}

//check if there are dbflavoured daughters
bool QuadJet::hasBdaughters( const reco::Candidate * particle ){
  bool myDaughterHasBottom = false;
  for(size_t myDau = 0; myDau < particle->numberOfDaughters(); myDau++){
    HepPDT::ParticleID myDaughter( particle->daughter(myDau)->pdgId() ); 
    myDaughterHasBottom += myDaughter.hasBottom();
  }
  return myDaughterHasBottom;
}

// calcolo dell'angolo nel piano eta phi della retta conguingente due jet
double QuadJet::getAnglePhiEtaPlane( pat::Jet *leadingJet , pat::Jet *secondLeadingJet ){
  double angle = 1e10;
  double deltaPhi = leadingJet->p4().Phi() - secondLeadingJet->p4().Phi();
  double deltaEta = leadingJet->p4().Eta() - secondLeadingJet->p4().Eta();
  angle = TMath::ATan2( deltaPhi, deltaEta );
  return angle;
}

// calcolo dell'angolo nel piano eta phi della retta conguingente due b hadron
double QuadJet::getAnglePhiEtaPlane( const reco::Candidate *firstB , const reco::Candidate *secondB ){
  double angle = 1e10;
  double deltaPhi = firstB->phi() - secondB->phi();
  double deltaEta = firstB->eta() - secondB->eta();
  angle = TMath::ATan2( deltaPhi, deltaEta );
  return angle;
}

double QuadJet::getDeltaR( pat::Jet * leadingJet, pat::Jet * secondLeadingJet ){
  double deltaR = 1e10;
  deltaR = Geom::deltaR( leadingJet->p4().Vect(), secondLeadingJet->p4().Vect() );
  return deltaR;
}

double QuadJet::getDeltaR( const reco::Candidate * firstB, const reco::Candidate * secondB ){
  double deltaR = 1e10;
  deltaR = Geom::deltaR( firstB->momentum(), secondB->momentum() );
  return deltaR;
}

double QuadJet::getDeltaR( TLorentzVector TLV, pat::Jet * patJet ){
  double deltaR = 1e10;
  TVector3 JetVector;
  JetVector.SetXYZ( patJet->p4().Px(), patJet->p4().Py(), patJet->p4().Pz() );
  deltaR = JetVector.DeltaR( TLV.Vect() ) ;
  return deltaR;
}

double QuadJet::getDeltaEta( pat::Jet * leadingJet, pat::Jet * secondLeadingJet ){
  double deltaEta = 1e10;
  deltaEta = leadingJet->p4().Eta() - secondLeadingJet->p4().Eta() ;
  return deltaEta;
}

double QuadJet::getDeltaEta( const reco::Candidate * firstB, const reco::Candidate * secondB ){
  double deltaEta = 1e10;
  deltaEta = firstB->eta() - secondB->eta() ;
  return deltaEta;
}

double QuadJet::getDeltaPhi( pat::Jet* leadingJet, pat::Jet* secondLeadingJet){

  double deltaPhi = 1e10;
  deltaPhi = Geom::deltaPhi( leadingJet->p4().Vect(), secondLeadingJet->p4().Vect() ) ;
  return deltaPhi;

}

double QuadJet::getPtAsymmetry(pat::Jet* leadingJet, pat::Jet* secondLeadingJet ){

  double asymmetry = 1e10;
  double ptDiff = leadingJet->p4().Pt() - secondLeadingJet->p4().Pt();
  double ptSum = leadingJet->p4().Pt() + secondLeadingJet->p4().Pt();
  asymmetry = ptDiff / ptSum;
  return asymmetry;
}

unsigned int QuadJet::getAssociatedB( std::vector<TLorentzVector> bHadron_vector, pat::Jet* leadingJet){

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
TVector2 QuadJet::getTvect( pat::Jet* patJet, TLorentzVector b ){

  TVector2 t_Vect(0,0);
  TVector2 ci(0,0);
  TVector2 r(0,0);
  TVector2 v_b( b.Eta(), b.Phi());
  double patJetpfcPt = 1e10;
  double r_mag = 1e10;

  std::vector<reco::PFCandidatePtr>
    patJetpfc = patJet->getPFConstituents();
  for(size_t idx = 0; idx < patJetpfc.size(); idx++){
    if( patJetpfc.at(idx)->charge() != 0 ){
      patJetpfcPt = patJetpfc.at(idx)->pt();
      ci.Set( patJetpfc.at(idx)->eta(), patJetpfc.at(idx)->phi() );
      r.Set( ci.X() - patJet->p4().Rapidity(), Geom::deltaPhi( patJetpfc.at(idx)->phi(), patJet->p4().Phi() ) );
      r_mag = r.Mod();
      t_Vect += ( (patJetpfcPt * r_mag) / patJet->p4().Pt() ) * r;
    }
  }

  return t_Vect;
  
}

// without b vertex information
TVector2 QuadJet::getTvect( pat::Jet* patJet ){

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
      r.Set( pi.Eta() - J.Rapidity(), Geom::deltaPhi( patJetpfc.at(idx)->phi(), J.Phi() ) );
      r_mag = r.Mod();
      t_Vect += ( patJetpfcPt / J.Pt() ) * r_mag * r;
    }
  }

  return t_Vect;
  
}

// with b vertex information
double QuadJet::getDeltaTheta( pat::Jet* j1, pat::Jet* j2, TLorentzVector b1, TLorentzVector b2 ){

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
double QuadJet::getDeltaTheta( pat::Jet* j1, pat::Jet* j2 ){

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

  Double_t deltaphi = Geom::deltaPhi( v_j2.Phi(), v_j1.Phi() );
  Double_t deltaeta = v_j2.Rapidity() - v_j1.Rapidity();
  TVector2 BBdir( deltaeta, deltaphi );

  deltaTheta = t.DeltaPhi(BBdir);

  return deltaTheta;

}


TVector2 QuadJet::getBBdir( pat::Jet* j1, pat::Jet* j2){

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
inline pat::Jet* QuadJet::whichJet(pat::Jet *j1, pat::Jet *j2){

  if( TMath::Abs( j1->p4().Eta() ) - TMath::Abs( j2->p4().Eta() ) > 0 )
    return j1;
  else
    return j2;
}

// return the opposite of whichJet
inline pat::Jet* QuadJet::whichOtherJet(pat::Jet *j1, pat::Jet *j2){

  if( TMath::Abs( j1->p4().Eta() ) - TMath::Abs( j2->p4().Eta() ) < 0 )
    return j1;
  else
    return j2;
}





void QuadJet::beginJob()
{
  
  using namespace std;
  edm::Service<TFileService> fs;


  Int_t bin_angle = 300;
  Double_t min_angle = -6.3;
  Double_t max_angle = 6.3;

  Int_t bin_eta = 600;
  Double_t min_eta = -3;
  Double_t max_eta = 3;

  Int_t bin_invmass = 600;
  Double_t min_invmass = 0;
  Double_t max_invmass = 200;

  Int_t bin_mass = 100;
  Double_t min_mass = 0;
  Double_t max_mass = 1;

  Int_t bin_deltaR = 600;
  Double_t min_deltaR = -5;
  Double_t max_deltaR = 5;

  Int_t bin_Tmod = 400;
  Double_t min_Tmod = 0;
  Double_t max_Tmod = 0.1;

  histocontainer_["h_minTagger"]=fs->make<TH1D>("h_minTagger","h_minTagger", bin_mass, min_mass, max_mass);
  histocontainer_["h_maxTagger"]=fs->make<TH1D>("h_maxTagger","h_maxTagger", bin_mass, min_mass, max_mass);

  histocontainer_["h_pfcMass"]=fs->make<TH1D>("h_pfcMass","h_pfcMass", bin_mass, min_mass, max_mass);
  histocontainer_["h_pfcEta"]=fs->make<TH1D>("h_pfcEta","h_pfcEta", bin_eta, min_eta, max_eta);
  histocontainer_["h_pfcPhi"]=fs->make<TH1D>("h_pfcPhi","h_pfcPhi", bin_angle, min_angle, max_angle);
  histocontainer_2["h2_pfcEtaPhi"]=fs->make<TH2D>("h_pfcEtaPhi","h_pfcEtaPhi", bin_eta, min_eta, max_eta, bin_angle, min_angle, max_angle );

  histocontainer_["h_BBdir"]=fs->make<TH1D>("h_BBdir","h_BBdir", bin_angle, min_angle, max_angle);
  histocontainer_["h_BBdEta"]=fs->make<TH1D>("h_BBdEta","h_BBdEta", bin_eta, min_eta, max_eta);
  histocontainer_["h_BBdPhi"]=fs->make<TH1D>("h_BBdPhi","h_BBdPhi", bin_angle, min_angle, max_angle);
  histocontainer_2["h2_BBdEtadPhi"]=fs->make<TH2D>("h_BBdEtadPhi","h_BBdEtadPhi", bin_eta, min_eta, max_eta, bin_angle, min_angle, max_angle );
  histocontainer_2["h2_BBdirdPhi"]=fs->make<TH2D>("h_BBdirdPhi","h_BBdirdPhi", bin_angle, min_angle, max_angle, bin_angle, min_angle, max_angle );
  histocontainer_2["h2_BBdirdEta"]=fs->make<TH2D>("h_BBdirdEta","h_BBdirdEta", bin_angle, min_angle, max_angle, bin_eta, min_eta, max_eta );

  histocontainer_["h_theta_central"]=fs->make<TH1D>("h_theta_central","h_theta_central", bin_angle, min_angle, max_angle);
  histocontainer_["h_theta_forward"]=fs->make<TH1D>("h_theta_forward","h_theta_forward", bin_angle, min_angle, max_angle);

  histocontainer_["h_LowerTheta"]=fs->make<TH1D>("h_LowerTheta","h_LowerTheta", bin_angle, min_angle, max_angle);
  histocontainer_["h_HigherTheta"]=fs->make<TH1D>("h_HigherTheta","h_HigherTheta", bin_angle, min_angle, max_angle);
  histocontainer_["h_theta"]=fs->make<TH1D>("h_theta","h_theta", bin_angle, min_angle, max_angle);
  histocontainer_["h_LowerDeltaTheta"]=fs->make<TH1D>("h_LowerDeltaTheta","h_LowerDeltaTheta", bin_angle, min_angle, max_angle);
  histocontainer_["h_HigherDeltaTheta"]=fs->make<TH1D>("h_HigherDeltaTheta","h_HigherDeltaTheta", bin_angle, min_angle, max_angle);
  histocontainer_["h_deltaTheta"]=fs->make<TH1D>("h_deltaTheta","h_deltaTheta", bin_angle, min_angle, max_angle);


  histocontainer_2["h2_higgsMass_invmassJet"]=fs->make<TH2D>("h2_higgsMass_invmassJet","h2_higgsMass_invmassJet", bin_invmass, min_invmass, max_invmass, bin_invmass, min_invmass, max_invmass);

  histocontainer_2["h2_theta_invmassJet"]=fs->make<TH2D>("h2_theta_invmassJet","h2_theta_invmassJet", bin_angle, min_angle, max_angle, bin_invmass, min_invmass, max_invmass);
  histocontainer_2["h2_theta_JetDeltaR"]=fs->make<TH2D>("h2_theta_JetDeltaR","h2_theta_JetDeltaR", bin_angle, min_angle, max_angle, bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_2["h2_theta_JetDeltaEta"]=fs->make<TH2D>("h2_theta_JetDeltaEta","h2_theta_JetDeltaEta", bin_angle, min_angle, max_angle, bin_eta, min_eta, max_eta);
  histocontainer_2["h2_theta_JetDeltaPhi"]=fs->make<TH2D>("h2_theta_JetDeltaPhi","h2_theta_JetDeltaPhi", bin_angle, min_angle, max_angle, bin_angle, min_angle, max_angle);
  histocontainer_2["h2_theta_TvectMod"]=fs->make<TH2D>("h2_theta_TvectMod","h2_theta_TvectMod", bin_angle, min_angle, max_angle, bin_Tmod, min_Tmod, max_Tmod);

  histocontainer_2["h2_HigherDeltaTheta_LowerDeltaTheta"]=fs->make<TH2D>("h2_HigherDeltaTheta_LowerDeltaTheta","h2_HigherDeltaTheta_LowerDeltaTheta", bin_angle, min_angle, max_angle, bin_angle, min_angle, max_angle);

  histocontainer_2["h2_LowerDeltaTheta_invmassJet"]=fs->make<TH2D>("h2_LowerDeltaTheta_invmassJet","h2_LowerDeltaTheta_invmassJet", bin_angle, min_angle, max_angle, bin_invmass, min_invmass, max_invmass);
  histocontainer_2["h2_HigherDeltaTheta_invmassJet"]=fs->make<TH2D>("h2_HigherDeltaTheta_invmassJet","h2_HigherDeltaTheta_invmassJet", bin_angle, min_angle, max_angle, bin_invmass, min_invmass, max_invmass);
  histocontainer_2["h2_deltaTheta_invmassJet"]=fs->make<TH2D>("h2_deltaTheta_invmassJet","h2_deltaTheta_invmassJet", bin_angle, min_angle, max_angle, bin_invmass, min_invmass, max_invmass);
  histocontainer_2["h2_deltaTheta_JetDeltaR"]=fs->make<TH2D>("h2_deltaTheta_JetDeltaR","h2_deltaTheta_JetDeltaR", bin_angle, min_angle, max_angle, bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_2["h2_deltaTheta_JetDeltaEta"]=fs->make<TH2D>("h2_deltaTheta_JetDeltaEta","h2_deltaTheta_JetDeltaEta", bin_angle, min_angle, max_angle, bin_eta, min_eta, max_eta);
  histocontainer_2["h2_deltaTheta_JetDeltaPhi"]=fs->make<TH2D>("h2_deltaTheta_JetDeltaPhi","h2_deltaTheta_JetDeltaPhi", bin_angle, min_angle, max_angle, bin_angle, min_angle, max_angle);
  histocontainer_2["h2_deltaTheta_TvectMod"]=fs->make<TH2D>("h2_deltaTheta_TvectMod","h2_deltaTheta_TvectMod", bin_angle, min_angle, max_angle, bin_Tmod, min_Tmod, max_Tmod);

  histocontainer_2["h2_absDeltatheta_invmassJet"]=fs->make<TH2D>("h2_absDeltatheta_invmassJet","h2_absDeltatheta_invmassJet", bin_angle, min_angle, max_angle, bin_invmass, min_invmass, max_invmass);
  histocontainer_2["h2_absDeltatheta_JetDeltaR"]=fs->make<TH2D>("h2_absDeltatheta_JetDeltaR","h2_absDeltatheta_JetDeltaR", bin_angle, min_angle, max_angle, bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_2["h2_absDeltatheta_JetDeltaEta"]=fs->make<TH2D>("h2_absDeltatheta_JetDeltaEta","h2_absDeltatheta_JetDeltaEta", bin_angle, min_angle, max_angle, bin_eta, min_eta, max_eta);
  histocontainer_2["h2_absDeltatheta_JetDeltaPhi"]=fs->make<TH2D>("h2_absDeltatheta_JetDeltaPhi","h2_absDeltatheta_JetDeltaPhi", bin_angle, min_angle, max_angle, bin_angle, min_angle, max_angle);

}

void QuadJet::endJob() {

  std::cout << "Number of events with at least two B hadrons = " << myEvents << std::endl;
  std::cout << "JOB FINISHED" << std::endl;

}

DEFINE_FWK_MODULE(QuadJet);
