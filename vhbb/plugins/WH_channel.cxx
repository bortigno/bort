/* WH_channel_cxx                                           */
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

  bool muonJetCleaning( const pat::Jet&, const std::vector<reco::Muon>&, double );
  bool hasHiggsMother( const reco::Candidate* );
  bool hasBdaughters( const reco::Candidate * );
  double getAnglePhiEtaPlane( const pat::Jet* , const pat::Jet* );
  double getAnglePhiEtaPlane( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR( const pat::Jet* , const pat::Jet* );
  double getDeltaR( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR( TLorentzVector , const pat::Jet* );
  double getDeltaEta( const pat::Jet* , const pat::Jet* );
  double getDeltaEta( const reco::Candidate* , const reco::Candidate* );
  unsigned int getAssociatedB( std::vector<TLorentzVector> , const pat::Jet* );
  double getTheta( const pat::Jet* );

  struct ComparePt {
    bool operator()( const reco::Muon t1, const reco::Muon t2 ) const {
      return t1.p4().pt() > t2.p4().pt();
    }
  };

  ComparePt ptComparator;

  //per creare dei TH1 velocemente InputTag.label
  std::map<std::string,TH1D*> histocontainer_;
  std::map<std::string,TH2D*> histocontainer_2;
  std::map<std::string,TH3D*> histocontainer_3;

//   edm::InputTag akt5pfJetsLabel_;
  edm::InputTag muonLabel_;
  edm::InputTag genpLabel_;
  edm::InputTag patMetLabel_;
  edm::InputTag patJetLabel_;
  edm::InputTag WMuNuLabel_;
  edm::ParameterSet pfJetIdSelector_;

  std::vector<int> v_motherId;
  std::vector<int> v_mother_status_background;

  std::vector<const pat::Jet*> v_akt5pfj;

  TLorentzVector TLV_bHadron_general;
  TLorentzVector TLV_bHadron_signal;
  TLorentzVector TLV_bHadron_background;

  std::vector<TLorentzVector> bHadron_general;
  std::vector<TLorentzVector> bHadron_signal;
  std::vector<TLorentzVector> bHadron_background;


  // Member data
  unsigned int goodJetCounter;
  unsigned int badJetCounter;
  unsigned int mypos1;
  unsigned int mypos2;

  Int_t n_event;  
  Int_t myEvents;

  Double_t muonJetCleaningDRcut;
  Double_t JetBassociationCut;
  Double_t higgsMassLowerCut;
  Double_t higgsMassHigherCut;

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

  bool bHadron;  

};

WH_channel::WH_channel(const edm::ParameterSet& iConfig) : 

  histocontainer_(),
  histocontainer_2(),
  histocontainer_3(),

  //cleaning cut
  muonJetCleaningDRcut(iConfig.getUntrackedParameter<double>("muonJetCleaningDRcut_")),
  JetBassociationCut(iConfig.getUntrackedParameter<double>("JetBassociationDRCut")),
  higgsMassLowerCut(iConfig.getUntrackedParameter<double>("hMassLowerCut")),
  higgsMassHigherCut(iConfig.getUntrackedParameter<double>("hMassHigherCut")),

  //edm collections
  genpLabel_(iConfig.getUntrackedParameter<edm::InputTag>("genPart")),
  muonLabel_(iConfig.getUntrackedParameter<edm::InputTag>("muonCand")),
//   akt5pfJetsLabel_(iConfig.getUntrackedParameter<edm::InputTag>("akt5pfJets")),
  patJetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("selectedPatJetsCand")),
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

  // Generated particles handle
  edm::Handle<reco::GenParticleCollection> genP;
  iEvent.getByLabel(genpLabel_,genP);
  const reco::GenParticleCollection &genParticles = *genP.product();

  //Wmunu
  edm::Handle< std::vector< reco::WMuNuCandidate > > WMuNuCollection;
  iEvent.getByLabel(WMuNuLabel_, WMuNuCollection);
  const reco::WMuNuCandidate& Wcandidate = WMuNuCollection->at(0);

  v_motherId.clear();
  v_mother_status_background.clear();
  bHadron_general.clear();
  bHadron_signal.clear();
  bHadron_background.clear();
  v_akt5pfj.clear();

  double deltaPhi = false;
  std::vector<const reco::Candidate*> v_muon;
  std::vector<const reco::Candidate*> v_met;
  const pat::Jet *leadingJet;
  const pat::Jet *secondLeadingJet;
  reco::CandidateCollection BhadronCollection;
  reco::CandidateCollection BhadronCollectionSignal;
  reco::CandidateCollection BhadronCollectionBackground;

  // needed for the jetId
  pat::strbitset ret = pfJetIDFunctor.getBitTemplate();

  // count the good jets
  goodJetCounter = 0;
  badJetCounter = 0;

  //jets are pt ordered
  for(size_t jetIdx = 0; jetIdx < patJet.size(); ++jetIdx){
    if( patJet.at(jetIdx).isPFJet() == true 
 	and pfJetIDFunctor( patJet.at(jetIdx), ret ) == true
	and muonJetCleaning( patJet.at(jetIdx), muons, muonJetCleaningDRcut ) == false ){
      goodJetCounter++;
      v_akt5pfj.push_back( new pat::Jet (patJet.at(jetIdx).correctedJet("abs")) );
      histocontainer_["h_goodJetEta"]->Fill( patJet.at(jetIdx).p4().Eta() );
      histocontainer_["h_goodJetPt"]->Fill( patJet.at(jetIdx).p4().Pt() );
    }
    else{
      badJetCounter++;
      histocontainer_["h_badJetPt"]->Fill( patJet.at(jetIdx).p4().Pt() );
      histocontainer_["h_badJetEta"]->Fill( patJet.at(jetIdx).p4().Eta() );
    }
  }
  
  //muons are pt ordered
  for( size_t muon_iter = 0; muon_iter < muons.size(); muon_iter++)
    if( muon::isGoodMuon( muons.at(muon_iter), muon::GlobalMuonPromptTight) == true 
	and muons.at(muon_iter).isIsolationValid() == true )
      v_muon.push_back( &( muons.at(muon_iter) ) );
    
  //Event selection: at least two jets one muon and one MET
  if( v_akt5pfj.size() < 2
      or v_muon.size() < 1
      or v_patMet.size() < 1 )
    return void();

  //no additional jets with pt > 20 Gev
  if( v_akt5pfj.size() > 2
      and v_akt5pfj.at(2)->p4().pt() > 20 )
    return void();

  //no additional isolated muons with pt > 15
  if( v_muon.size() > 1
      and v_muon.at(1)->p4().pt() > 15 )
    return void();

  leadingJet = v_akt5pfj.at(0);
  secondLeadingJet = v_akt5pfj.at(1);
  reco::CompositeCandidate higgsCandidate;
  higgsCandidate.addDaughter( *v_akt5pfj.at(0) );
  higgsCandidate.addDaughter( *v_akt5pfj.at(1) );
  AddFourMomenta addp4;
  addp4.set(higgsCandidate);
  higgsCandidate_pt = higgsCandidate.p4().Pt();

  //my WMunu candidate  
//   reco::CompositeCandidate Wcandidate;
//   Wcandidate.addDaughter( *v_muon.at(0) );
//   Wcandidate.addDaughter( v_patMet.at(0) );
//   AddFourMomenta addZp4;
//   addZp4.set(Wcandidate);

  double Wcandidate_pt = Wcandidate.p4().Pt();
  double WH_deltaPhi = Geom::deltaPhi(higgsCandidate.p4(), Wcandidate.p4());

//   histocontainer_["h_higgsCandidate_pt"]->Fill( higgsCandidate_pt );
//   histocontainer_["h_higgsCandidate_mass"]->Fill( higgsCandidate.p4().M() );
//   histocontainer_["h_Wcandidate_pt"]->Fill( Wcandidate_pt );
//   histocontainer_["h_Wcandidate_mass"]->Fill( Wcandidate.p4().M() );
//   histocontainer_["h_HW_deltaPhi"]->Fill( WH_deltaPhi );

  if( Wcandidate_pt < 150
      or TMath::Abs(WH_deltaPhi) < 2.97 )
    return void();

  histocontainer_["h_higgsCandidate_pt"]->Fill( higgsCandidate_pt );
  histocontainer_["h_higgsCandidate_mass"]->Fill( higgsCandidate.p4().M() );
  histocontainer_["h_Wcandidate_pt"]->Fill( Wcandidate_pt );
  histocontainer_["h_Wcandidate_mass"]->Fill( Wcandidate.p4().M() );
  histocontainer_["h_HW_deltaPhi"]->Fill( WH_deltaPhi );  

// taglio sulla finestra di massa dell'higgs
  if( higgsCandidate.p4().M() < higgsMassLowerCut or
      higgsCandidate.p4().M() > higgsMassHigherCut )
    return void();

  // Generated particles loop
  for( reco::GenParticleCollection::const_iterator iGenp = genParticles.begin(); 
       iGenp != genParticles.end();
       ++iGenp) 
    {

      const reco::Candidate *genCandidate = &(*iGenp);

      if( fabs(iGenp->eta()) > 2.5
	  or iGenp->pt() < 1 )
	continue;
      
      HepPDT::ParticleID particleID( iGenp->pdgId() );

      if( iGenp->numberOfDaughters() ){
	std::vector<HepPDT::ParticleID> daughterID;
	for( reco::Candidate::const_iterator iDau = iGenp->begin();
	     iDau != iGenp->end();
	     ++iDau )
	  daughterID.push_back( iDau->pdgId() );
      }
      
      histocontainer_["h_pdgId"]->Fill(iGenp->pdgId());
      histocontainer_2["h2_pdgId_status"]->Fill(iGenp->pdgId(), iGenp->status());
      histocontainer_2["h2_pdgId_particleID"]->Fill(iGenp->pdgId(), particleID.pid());
      
//       // pt of the bosons
//       // 24 e la W+ mentre 23 e la Z. h e 25 
//       if( abs(particleID.pid()) == 23 and iGenp->status() == 3 ){
// 	const reco::Candidate &ZCandidate = *iGenp;
// 	if( Geom::deltaPhi(higgsCandidate.p4(), ZCandidate.p4()) < 2.75 )
// 	  deltaPhi = true;
// 	histocontainer_["h_HW_deltaPhi"]->Fill( Geom::deltaPhi(higgsCandidate.p4(), ZCandidate.p4()) );
// 	vector_pt = iGenp->pt();
// 	histocontainer_["h_Z_pt"]->Fill(iGenp->pt());
//       }
//       if( abs(particleID.pid()) == 24 and iGenp->status() == 3 ){
// 	vector_pt = iGenp->pt();
// 	histocontainer_["h_W_pt"]->Fill(iGenp->pt());
//       }
//       if( particleID.pid() == 25 
// 	  and ( abs(iGenp->mother()->pdgId()) == 24
// 		or abs(iGenp->mother()->pdgId()) == 23 ) ){
// 	higgs_pt = iGenp->pt();
// 	histocontainer_["h_H_pt"]->Fill(iGenp->pt());
//       }
      
      // saltiamo tutto quello che non e B hadron stabile
      if( not particleID.hasBottom() 
	  or  not ( particleID.isMeson()
		    or particleID.isBaryon() )
	  or hasBdaughters( genCandidate )
	  )
	continue;

      BhadronCollection.push_back( std::auto_ptr<reco::GenParticle>(  new reco::GenParticle (*iGenp) ) );

      TLV_bHadron_general.SetPtEtaPhiE( iGenp->pt(), iGenp->eta(), iGenp->phi(), iGenp->energy() );
      bHadron_general.push_back( TLV_bHadron_general );
      
      if( iGenp->numberOfMothers() ){
	HepPDT::ParticleID motherID( iGenp->mother()->pdgId() );
	// Higgs. signal
	if( hasHiggsMother( genCandidate ) ){
	  BhadronCollectionSignal.push_back( std::auto_ptr<reco::GenParticle>(  new reco::GenParticle (*iGenp) ) );
	  TLV_bHadron_signal.SetPtEtaPhiE( iGenp->pt(), iGenp->eta(), iGenp->phi(), iGenp->energy() );
	  bHadron_signal.push_back( TLV_bHadron_signal );
	}
	// Background
	else {
	  BhadronCollectionBackground.push_back( std::auto_ptr<reco::GenParticle>(  new reco::GenParticle (*iGenp) ) );
	  v_mother_status_background.push_back(iGenp->mother()->status());
	  TLV_bHadron_background.SetPtEtaPhiE( iGenp->pt(), iGenp->eta(), iGenp->phi(), iGenp->energy() );
	  bHadron_background.push_back( TLV_bHadron_background );
	  v_motherId.push_back(motherID.pid());
	}
      }
    }//END GENPARTICLEs LOOP
  
  mypos1 = 1e2;
  mypos2 = 1e2;

  // store infos
  //all the B hadrons couples
  if( bHadron_general.size() > 1 ){
    myEvents++;

    mypos1 = getAssociatedB( bHadron_general, leadingJet );
    mypos2 = getAssociatedB( bHadron_general, secondLeadingJet );
    if( getDeltaR( bHadron_general.at(mypos1), leadingJet ) > JetBassociationCut or  
        getDeltaR( bHadron_general.at(mypos2), secondLeadingJet ) > JetBassociationCut )
      return void();
    
    std::pair< TLorentzVector, pat::Jet > bVertex_Jets_pair1 ( bHadron_general.at(mypos1), *leadingJet );
    std::pair< TLorentzVector, pat::Jet > bVertex_Jets_pair2 ( bHadron_general.at(mypos2), *secondLeadingJet );
   
    // queste sono le variabile che usa l'articolo teorico sulla color reconnection
    double leadingTheta =  getTheta( leadingJet );
    double secondLeadingTheta = getTheta( secondLeadingJet);
    double deltaTheta = leadingTheta - secondLeadingTheta;

    jetAnglePhiEtaPlane =  getAnglePhiEtaPlane( leadingJet, secondLeadingJet );
    BanglePhiEtaPlane = getAnglePhiEtaPlane( &(BhadronCollection[0]) , &(BhadronCollection[1]) );
    std::vector<double> jetDistancePerpendicularLineGeneral;
    jetDistancePerpendicularLineGeneral.push_back( TMath::Abs( leadingJet->p4().Phi() - leadingJet->p4().Eta() - ( bHadron_general.at(0).Phi() - BanglePhiEtaPlane * bHadron_general.at(0).Eta() ) / TMath::Sqrt( 1 + TMath::Power(BanglePhiEtaPlane,2) ) ) ) ;
    jetDistancePerpendicularLineGeneral.push_back( TMath::Abs( secondLeadingJet->p4().Phi() - secondLeadingJet->p4().Eta() - ( bHadron_general.at(0).Phi() - BanglePhiEtaPlane * bHadron_general.at(0).Eta() ) / TMath::Sqrt( 1 + TMath::Power(BanglePhiEtaPlane,2) ) ) );
    alphaAngle = TMath::Abs( jetAnglePhiEtaPlane - BanglePhiEtaPlane ) ;
    if ( alphaAngle > 0.5*TMath::Pi() )
      alphaAngle = TMath::Abs( TMath::Abs( alphaAngle ) - TMath::Pi() ); // it takes the inclusive angle
    BdeltaR = getDeltaR( &(BhadronCollection[0]), &(BhadronCollection[1]) );
    JetDeltaR = getDeltaR( leadingJet, secondLeadingJet );
    betaDistance = BdeltaR - JetDeltaR;
    BdeltaEta = TMath::Abs( getDeltaEta( &(BhadronCollection[0]), &(BhadronCollection[1]) ) );
    JetDeltaEta = TMath::Abs( getDeltaEta( leadingJet, secondLeadingJet ) );
    epsilonDeltaEta = BdeltaEta - JetDeltaEta;
    deltaR_general =  bHadron_general.at(0).DeltaR( bHadron_general.at(1) );
    TLorentzVector p4sum = bHadron_general.at(0) + bHadron_general.at(1);
    invmass_general = p4sum.M();
    TVector3 tmp1TV3, tmp2TV3;
    tmp1TV3.SetPtEtaPhi( leadingJet->p4().Pt(), leadingJet->p4().Eta(), leadingJet->p4().Phi() );
    tmp2TV3.SetPtEtaPhi( leadingJet->p4().Pt(), leadingJet->p4().Eta(), leadingJet->p4().Phi() );
    gammaDeltaR = 0.5 * ( p4sum.Vect().DeltaR( tmp1TV3 ) + p4sum.Vect().DeltaR( tmp2TV3 ) ) ;
    std::vector<double> ptb_general;
    ptb_general.push_back( bHadron_general.at(0).Pt() );
    ptb_general.push_back( bHadron_general.at(1).Pt() );
    std::sort(ptb_general.begin(), ptb_general.end());
    double deltaEta1General = TMath::Abs( bVertex_Jets_pair1.first.Eta() - bVertex_Jets_pair1.second.p4().Eta() ) ;
    double deltaEta2General = TMath::Abs( bVertex_Jets_pair2.first.Eta() - bVertex_Jets_pair2.second.p4().Eta() ) ;
    histocontainer_["h_deltaEtaBJetGeneral"]->Fill(deltaEta1General);
    histocontainer_["h_deltaEtaBJetGeneral"]->Fill(deltaEta2General);
    histocontainer_["h_jetDistancePerpendicularLineGeneral"]->Fill(jetDistancePerpendicularLineGeneral.at(0));
    histocontainer_["h_jetDistancePerpendicularLineGeneral"]->Fill(jetDistancePerpendicularLineGeneral.at(1));
    histocontainer_["h_alphaAngleGeneral"]->Fill(alphaAngle);
    histocontainer_["h_betaDistanceGeneral"]->Fill(betaDistance);
    histocontainer_["h_gammaDeltaRGeneral"]->Fill(gammaDeltaR);
    histocontainer_["h_epsilonDeltaEtaGeneral"]->Fill(epsilonDeltaEta);
    histocontainer_["h_digammaDeltaThetaGeneral"]->Fill(deltaTheta);
    histocontainer_3["h3_deltaR_ptB1_pt_B2_general"]->Fill(deltaR_general, ptb_general.at(0) , ptb_general.at(1));
    histocontainer_["h_jetDeltaR_general"]->Fill(JetDeltaR);
    histocontainer_["h_deltaR_general"]->Fill(deltaR_general);
    histocontainer_["h_jetDeltaEtaGeneral"]->Fill(JetDeltaEta);
    histocontainer_["h_invmass_general"]->Fill(invmass_general);
    histocontainer_["h_invmassJet_general"]->Fill(higgsCandidate.p4().M());
    
    if( bHadron_signal.size() > 1 ){ // Signal

      mypos1 = getAssociatedB( bHadron_signal, leadingJet );
      mypos2 = getAssociatedB( bHadron_signal, secondLeadingJet );
      std::pair< TLorentzVector, pat::Jet > bVertex_Jets_pair1_signal ( bHadron_signal.at(mypos1), *leadingJet );
      std::pair< TLorentzVector, pat::Jet > bVertex_Jets_pair2_signal ( bHadron_signal.at(mypos2), *secondLeadingJet );

      jetAnglePhiEtaPlane =  getAnglePhiEtaPlane( leadingJet, secondLeadingJet );
      BanglePhiEtaPlane = getAnglePhiEtaPlane( &(BhadronCollectionSignal[0]) , &(BhadronCollectionSignal[1]) );
      std::vector<double> jetDistancePerpendicularLineSignal;
      jetDistancePerpendicularLineSignal.push_back( TMath::Abs( leadingJet->p4().Phi() - leadingJet->p4().Eta() - ( bHadron_general.at(0).Phi() - BanglePhiEtaPlane * bHadron_general.at(0).Eta() ) / TMath::Sqrt( 1 + TMath::Power(BanglePhiEtaPlane,2) ) ) ) ;
      jetDistancePerpendicularLineSignal.push_back( TMath::Abs( secondLeadingJet->p4().Phi() - secondLeadingJet->p4().Eta() - ( bHadron_general.at(0).Phi() - BanglePhiEtaPlane * bHadron_general.at(0).Eta() ) / TMath::Sqrt( 1 + TMath::Power(BanglePhiEtaPlane,2) ) ) );
      alphaAngle = TMath::Abs( jetAnglePhiEtaPlane - BanglePhiEtaPlane ) ;
      if ( alphaAngle > 0.5*TMath::Pi() )
	alphaAngle = TMath::Abs( TMath::Abs( alphaAngle ) - TMath::Pi() ); // it takes the inclusive angle
      BdeltaR = getDeltaR( &(BhadronCollectionSignal[0]), &(BhadronCollectionSignal[1]) );
      JetDeltaR = getDeltaR( leadingJet, secondLeadingJet );
      betaDistance = BdeltaR - JetDeltaR;
      TLorentzVector p4sum_signal = bHadron_signal.at(0) + bHadron_signal.at(1);
      TLorentzVector TLV_Wcandidate;
      TLV_Wcandidate.SetXYZM( Wcandidate.p4().Px(), 
			      Wcandidate.p4().Py(),
			      Wcandidate.p4().Pz(),
			      Wcandidate.p4().M());
      histocontainer_["h_gen_HW_deltaPhi"]->Fill( p4sum_signal.DeltaPhi( TLV_Wcandidate ) );
      TVector3 tmp1TV3, tmp2TV3;
      tmp1TV3.SetPtEtaPhi( leadingJet->p4().Pt(), leadingJet->p4().Eta(), leadingJet->p4().Phi() );
      tmp2TV3.SetPtEtaPhi( leadingJet->p4().Pt(), leadingJet->p4().Eta(), leadingJet->p4().Phi() );
      gammaDeltaR = 0.5 * ( p4sum.Vect().DeltaR( tmp1TV3 ) + p4sum.Vect().DeltaR( tmp2TV3 ) ) ;
      BdeltaEta = TMath::Abs( getDeltaEta( &(BhadronCollectionSignal[0]), &(BhadronCollectionSignal[1]) ) );
      JetDeltaEta = TMath::Abs( getDeltaEta( leadingJet, secondLeadingJet ) );
      epsilonDeltaEta = BdeltaEta - JetDeltaEta;
      deltaR_signal =  bHadron_signal.at(0).DeltaR( bHadron_signal.at(1) );
      invmass_signal = p4sum_signal.M();
      histocontainer_2["h2_ptHiggs_deltaR_signal"]->Fill(higgs_pt, deltaR_signal);
      if( higgsCandidate_pt > 100 ){
	std::vector<double> ptb_signal;
	double deltaEta1Signal = TMath::Abs( bVertex_Jets_pair1_signal.first.Eta() - bVertex_Jets_pair1_signal.second.p4().Eta() ) ;
	double deltaEta2Signal = TMath::Abs( bVertex_Jets_pair2_signal.first.Eta() - bVertex_Jets_pair2_signal.second.p4().Eta() ) ;
	histocontainer_["h_deltaEtaBJetSignal"]->Fill(deltaEta1Signal);
	histocontainer_["h_deltaEtaBJetSignal"]->Fill(deltaEta2Signal);
	histocontainer_["h_alphaAngleSignal"]->Fill(alphaAngle);
	histocontainer_["h_jetDistancePerpendicularLineSignal"]->Fill(jetDistancePerpendicularLineSignal.at(0));
	histocontainer_["h_jetDistancePerpendicularLineSignal"]->Fill(jetDistancePerpendicularLineSignal.at(1));
	histocontainer_["h_betaDistanceSignal"]->Fill(betaDistance);
	histocontainer_["h_gammaDeltaRSignal"]->Fill(gammaDeltaR);
	histocontainer_["h_epsilonDeltaEtaSignal"]->Fill(epsilonDeltaEta);
	histocontainer_["h_digammaDeltaThetaSignal"]->Fill(deltaTheta);
	ptb_signal.push_back( bHadron_signal.at(0).Pt() );
	ptb_signal.push_back( bHadron_signal.at(1).Pt() );
	std::sort(ptb_signal.begin(), ptb_signal.end());
	histocontainer_3["h3_deltaR_ptB1_pt_B2_signal"]->Fill(deltaR_signal, ptb_signal.at(0) , ptb_signal.at(1));
	histocontainer_["h_jetDeltaR_signal"]->Fill(JetDeltaR);
	histocontainer_["h_deltaR_signal"]->Fill(deltaR_signal);
	histocontainer_["h_jetDeltaEtaSignal"]->Fill(JetDeltaEta);
	histocontainer_["h_invmass_signal"]->Fill(invmass_signal);
	histocontainer_["h_invmassJet_signal"]->Fill(higgsCandidate.p4().M());
      }
    }
    if( bHadron_background.size() > 1 ){ // Background

      mypos1 = getAssociatedB( bHadron_background, leadingJet );
      mypos2 = getAssociatedB( bHadron_background, secondLeadingJet );
      std::pair< TLorentzVector, pat::Jet > bVertex_Jets_pair1_background ( bHadron_background.at(mypos1), *leadingJet );
      std::pair< TLorentzVector, pat::Jet > bVertex_Jets_pair2_background ( bHadron_background.at(mypos2), *secondLeadingJet );

      jetAnglePhiEtaPlane =  getAnglePhiEtaPlane( leadingJet, secondLeadingJet );
      BanglePhiEtaPlane = getAnglePhiEtaPlane( &(BhadronCollectionBackground[0]) , &(BhadronCollectionBackground[1]) );
      std::vector<double> jetDistancePerpendicularLineBackground;
      jetDistancePerpendicularLineBackground.push_back( TMath::Abs( leadingJet->p4().Phi() - leadingJet->p4().Eta() - ( bHadron_general.at(0).Phi() - BanglePhiEtaPlane * bHadron_general.at(0).Eta() ) / TMath::Sqrt( 1 + TMath::Power(BanglePhiEtaPlane,2) ) ) ) ;
      jetDistancePerpendicularLineBackground.push_back( TMath::Abs( secondLeadingJet->p4().Phi() - secondLeadingJet->p4().Eta() - ( bHadron_general.at(0).Phi() - BanglePhiEtaPlane * bHadron_general.at(0).Eta() ) / TMath::Sqrt( 1 + TMath::Power(BanglePhiEtaPlane,2) ) ) );
      alphaAngle = TMath::Abs( jetAnglePhiEtaPlane - BanglePhiEtaPlane ) ;
      if ( alphaAngle > 0.5*TMath::Pi() )
	alphaAngle = TMath::Abs( TMath::Abs( alphaAngle ) - TMath::Pi() ); // it takes the inclusive angle
      BdeltaR = getDeltaR( &(BhadronCollectionBackground[0]), &(BhadronCollectionBackground[1]) );
      JetDeltaR = getDeltaR( leadingJet, secondLeadingJet );
      betaDistance = BdeltaR - JetDeltaR;
      TLorentzVector p4sum_background = bHadron_background.at(0) + bHadron_background.at(1);
      TVector3 tmp1TV3, tmp2TV3;
      tmp1TV3.SetPtEtaPhi( leadingJet->p4().Pt(), leadingJet->p4().Eta(), leadingJet->p4().Phi() );
      tmp2TV3.SetPtEtaPhi( leadingJet->p4().Pt(), leadingJet->p4().Eta(), leadingJet->p4().Phi() );
      gammaDeltaR = 0.5 * ( p4sum.Vect().DeltaR( tmp1TV3 ) + p4sum.Vect().DeltaR( tmp2TV3 ) ) ;
      BdeltaEta = TMath::Abs( getDeltaEta( &(BhadronCollectionBackground[0]), &(BhadronCollectionBackground[1]) ) );
      JetDeltaEta = TMath::Abs( getDeltaEta( leadingJet, secondLeadingJet ) );
      epsilonDeltaEta = BdeltaEta - JetDeltaEta;
      deltaR_background =  bHadron_background.at(0).DeltaR( bHadron_background.at(1) );
      invmass_background = p4sum_background.M();
      histocontainer_2["h2_ptVector_deltaR_background"]->Fill(vector_pt, deltaR_background);
      if( vector_pt > 100 ){
	double deltaEta1Background = TMath::Abs( bVertex_Jets_pair1_background.first.Eta() - bVertex_Jets_pair1_background.second.p4().Eta() ) ;
	double deltaEta2Background = TMath::Abs( bVertex_Jets_pair2_background.first.Eta() - bVertex_Jets_pair2_background.second.p4().Eta() ) ;
	histocontainer_["h_deltaEtaBJetBackground"]->Fill(deltaEta1Background);
	histocontainer_["h_deltaEtaBJetBackground"]->Fill(deltaEta2Background);
	histocontainer_["h_alphaAngleBackground"]->Fill(alphaAngle);
	histocontainer_["h_jetDistancePerpendicularLineBackground"]->Fill(jetDistancePerpendicularLineBackground.at(0));
	histocontainer_["h_jetDistancePerpendicularLineBackground"]->Fill(jetDistancePerpendicularLineBackground.at(1));
	histocontainer_["h_betaDistanceBackground"]->Fill(betaDistance);
	histocontainer_["h_gammaDeltaRBackground"]->Fill(gammaDeltaR);
	histocontainer_["h_epsilonDeltaEtaBackground"]->Fill(epsilonDeltaEta);
	histocontainer_["h_digammaDeltaThetaBackground"]->Fill(deltaTheta);
	std::vector<double> ptb_background;
	ptb_background.push_back( bHadron_background.at(0).Pt() );
	ptb_background.push_back( bHadron_background.at(1).Pt() );
	std::sort(ptb_background.begin(), ptb_background.end());
	histocontainer_3["h3_deltaR_ptB1_pt_B2_background"]->Fill(deltaR_background, ptb_background.at(0) , ptb_background.at(1));
	histocontainer_["h_jetDeltaR_background"]->Fill(JetDeltaR);
	histocontainer_["h_deltaR_background"]->Fill(deltaR_background);
	histocontainer_["h_jetDeltaEtaBackground"]->Fill(JetDeltaEta);
	histocontainer_["h_invmass_background"]->Fill(invmass_background);
	histocontainer_2["h2_motherId_background"]->Fill(v_motherId.at(0), v_motherId.at(1));
	histocontainer_["h_invmassJet_background"]->Fill(higgsCandidate.p4().M());
      }
    }

  }
  
  v_akt5pfj.clear();
  
}//END EVENT LOOP

//puliamo i pfjet dai muoni con un deltaR
// if it is true get rid of the jet
bool WH_channel::muonJetCleaning(const pat::Jet& tmpJet, const std::vector<reco::Muon>& muCol, double deltaRcut){
  bool clean = false;
  double deltaR = 1e10;
  for(size_t muIdx = 0; muIdx < muCol.size(); ++muIdx){
    deltaR = Geom::deltaR(tmpJet.p4().Vect(), muCol.at(muIdx).p4().Vect() );
    if( deltaR < deltaRcut )
      clean = true;
  }  
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




void WH_channel::beginJob()
{
  
  using namespace std;  
  edm::Service<TFileService> fs;

  Int_t bin_angle = 100;
  Double_t min_angle = -6;
  Double_t max_angle = 6;
  
  histocontainer_["h_HW_deltaPhi"]=fs->make<TH1D>("h_HW_deltaPhi","h_HW_deltaPhi",bin_angle, min_angle, max_angle);
  histocontainer_["h_gen_HW_deltaPhi"]=fs->make<TH1D>("h_gen_HW_deltaPhi","h_gen_HW_deltaPhi",bin_angle, min_angle, max_angle);

  histocontainer_["h_alphaAngleSignal"]=fs->make<TH1D>("h_alphaAngleSignal","h_alphaAngleSignal", bin_angle, min_angle, max_angle);
  histocontainer_["h_alphaAngleBackground"]=fs->make<TH1D>("h_alphaAngleBackground","h_alphaAngleBackground", bin_angle, min_angle, max_angle);
  histocontainer_["h_alphaAngleGeneral"]=fs->make<TH1D>("h_alphaAngleGeneral","h_alphaAngleGeneral", bin_angle, min_angle, max_angle);

  histocontainer_["h_digammaDeltaThetaSignal"]=fs->make<TH1D>("h_digammaDeltaThetaSignal","h_digammaDeltaThetaSignal", bin_angle, min_angle, max_angle);
  histocontainer_["h_digammaDeltaThetaBackground"]=fs->make<TH1D>("h_digammaDeltaThetaBackground","h_digammaDeltaThetaBackground", bin_angle, min_angle, max_angle);
  histocontainer_["h_digammaDeltaThetaGeneral"]=fs->make<TH1D>("h_digammaDeltaThetaGeneral","h_digammaDeltaThetaGeneral", bin_angle, min_angle, max_angle);


  Int_t bin_eta = 60;
  Double_t min_eta = -3;
  Double_t max_eta = 3;

  histocontainer_["h_goodJetEta"]=fs->make<TH1D>("h_goodJetEta","h_goodJetEta",bin_eta, min_eta, max_eta);
  histocontainer_["h_badJetEta"]=fs->make<TH1D>("h_badJetEta","h_badJetEta",bin_eta, min_eta, max_eta);

  histocontainer_["h_epsilonDeltaEtaSignal"]=fs->make<TH1D>("h_epsilonDeltaEtaSignal","deltaEta signal (H)", bin_eta, min_eta, max_eta);
  histocontainer_["h_epsilonDeltaEtaBackground"]=fs->make<TH1D>("h_epsilonDeltaEtaBackground","deltaEta background", bin_eta, min_eta, max_eta);
  histocontainer_["h_epsilonDeltaEtaGeneral"]=fs->make<TH1D>("h_epsilonDeltaEtaGeneral","deltaEta general", bin_eta, min_eta, max_eta);

  histocontainer_["h_deltaEtaBJetGeneral"]=fs->make<TH1D>("h_deltaEtaBJetGeneral","h_deltaEtaBJetGeneral", bin_eta, min_eta, max_eta);
  histocontainer_["h_deltaEtaBJetSignal"]=fs->make<TH1D>("h_deltaEtaBJetSignal","h_deltaEtaBJetSignal", bin_eta, min_eta, max_eta);
  histocontainer_["h_deltaEtaBJetBackground"]=fs->make<TH1D>("h_deltaEtaBJetBackground","h_deltaEtaBJetBackground", bin_eta, min_eta, max_eta);

  histocontainer_["h_jetDeltaEtaGeneral"]=fs->make<TH1D>("h_jetDeltaEtaGeneral","h_jetDeltaEtaGeneral", bin_eta, min_eta, max_eta);
  histocontainer_["h_jetDeltaEtaSignal"]=fs->make<TH1D>("h_jetDeltaEtaSignal","h_jetDeltaEtaSignal", bin_eta, min_eta, max_eta);
  histocontainer_["h_jetDeltaEtaBackground"]=fs->make<TH1D>("h_jetDeltaEtaBackground","h_jetDeltaEtaBackground", bin_eta, min_eta, max_eta);


  //Bool histo

  histocontainer_["h_H_dau_hasBottom"]=fs->make<TH1D>("h_H_dau_hasBottom","h_H_dau_hasBottom",2,0,1);

  Int_t bin_pt = 50;
  Double_t min_pt = 0;
  Double_t max_pt = 500;

  histocontainer_["h_goodJetPt"]=fs->make<TH1D>("h_goodJetPt","h_goodJetPt",bin_pt, min_pt, max_pt);
  histocontainer_["h_badJetPt"]=fs->make<TH1D>("h_badJetPt","h_badJetPt",bin_pt, min_pt, max_pt);

  histocontainer_["h_higgsCandidate_pt"]=fs->make<TH1D>("h_higgsCandidate_pt","p_{t} of H candidate [GeV/c]", bin_pt, min_pt, max_pt);
  histocontainer_["h_Wcandidate_pt"]=fs->make<TH1D>("h_Wcandidate_pt","h_Wcandidate_pt",bin_pt, min_pt, max_pt);
  histocontainer_["h_Z_pt"]=fs->make<TH1D>("h_Z_pt","p_{t} of Z [GeV/c]", bin_pt, min_pt, max_pt);
  histocontainer_["h_W_pt"]=fs->make<TH1D>("h_W_pt","p_{t} of W [GeV/c]", bin_pt, min_pt, max_pt);
  histocontainer_["h_H_pt"]=fs->make<TH1D>("h_H_pt","p_{t} of H [GeV/c]", bin_pt, min_pt, max_pt);

  
  Int_t bin_pdgId = 2000;
  Double_t min_pdgId = -1000;
  Double_t max_pdgId = 1000;

  histocontainer_["h_pdgId"]=fs->make<TH1D>("h_pdgId","pdgID", bin_pdgId, min_pdgId, max_pdgId);
  histocontainer_["h_H_dau_pdgId"]=fs->make<TH1D>("h_H_dau_pdgId","h_H_dau_pdgId", bin_pdgId, min_pdgId, max_pdgId);
  histocontainer_2["h2_pdgId_status"]=fs->make<TH2D>("h2_pdgId_status","pdgID vs status", bin_pdgId, min_pdgId, max_pdgId, 20 , -10 , 10);
  histocontainer_2["h2_pdgId_particleID"]=fs->make<TH2D>("h2_pdgId_particleID","pdgID vs particleID", bin_pdgId, min_pdgId, max_pdgId, bin_pdgId, min_pdgId, max_pdgId );
  histocontainer_2["h2_motherId_background"]=fs->make<TH2D>("h2_motherId_background","pdgID", bin_pdgId, min_pdgId, max_pdgId, bin_pdgId, min_pdgId, max_pdgId);

  Int_t bin_deltaR = 200;
  Double_t min_deltaR = 0;
  Double_t max_deltaR = 10;

  histocontainer_["h_deltaR_signal"]=fs->make<TH1D>("h_deltaR_signal","deltaR signal (H)", bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_["h_deltaR_background"]=fs->make<TH1D>("h_deltaR_background","deltaR background", bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_["h_deltaR_general"]=fs->make<TH1D>("h_deltaR_general","deltaR general", bin_deltaR, min_deltaR, max_deltaR);

  histocontainer_["h_jetDeltaR_signal"]=fs->make<TH1D>("h_jetDeltaR_signal","jetDeltaR signal (H)", bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_["h_jetDeltaR_background"]=fs->make<TH1D>("h_jetDeltaR_background","jetDeltaR background", bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_["h_jetDeltaR_general"]=fs->make<TH1D>("h_jetDeltaR_general","jetDeltaR general", bin_deltaR, min_deltaR, max_deltaR);

  histocontainer_["h_gammaDeltaRSignal"]=fs->make<TH1D>("h_gammaDeltaRSignal","deltaR signal (H)", bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_["h_gammaDeltaRBackground"]=fs->make<TH1D>("h_gammaDeltaRBackground","deltaR background", bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_["h_gammaDeltaRGeneral"]=fs->make<TH1D>("h_gammaDeltaRGeneral","deltaR general", bin_deltaR, min_deltaR, max_deltaR);

  histocontainer_["h_jetDistancePerpendicularLineGeneral"]=fs->make<TH1D>("h_jetDistancePerpendicularLineGeneral","h_jetDistancePerpendicularLineGeneral",bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_["h_jetDistancePerpendicularLineSignal"]=fs->make<TH1D>("h_jetDistancePerpendicularLineSignal","h_jetDistancePerpendicularLineSignal",bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_["h_jetDistancePerpendicularLineBackground"]=fs->make<TH1D>("h_jetDistancePerpendicularLineBackground","h_jetDistancePerpendicularLineBackground",bin_deltaR, min_deltaR, max_deltaR);

  bin_deltaR = 200;
  min_deltaR = -5;
  max_deltaR = 5;

  histocontainer_["h_betaDistanceSignal"]=fs->make<TH1D>("h_betaDistanceSignal","deltaR signal (H)", bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_["h_betaDistanceBackground"]=fs->make<TH1D>("h_betaDistanceBackground","deltaR background", bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_["h_betaDistanceGeneral"]=fs->make<TH1D>("h_betaDistanceGeneral","deltaR general", bin_deltaR, min_deltaR, max_deltaR);


  //redefine the binning on pt
  bin_pt=100;
  min_pt=0;
  max_pt=500;

  histocontainer_2["h2_ptHiggs_deltaR_signal"]=fs->make<TH2D>("h2_ptHiggs_deltaR_signal","h2_ptHiggs_deltaR_signal",
							      bin_pt, min_pt, max_pt,
							      bin_deltaR, min_deltaR, max_deltaR);
  histocontainer_2["h2_ptVector_deltaR_background"]=fs->make<TH2D>("h2_ptVector_deltaR_background","h2_ptVector_deltaR_background",
								   bin_pt, min_pt, max_pt,
								   bin_deltaR, min_deltaR, max_deltaR);

  histocontainer_3["h3_deltaR_ptB1_pt_B2_general"]=fs->make<TH3D>("h3_deltaR_ptB1_pt_B2_general",
								 "h3_deltaR_ptB1_pt_B2_general",
								 bin_deltaR, min_deltaR, max_deltaR,
								 bin_pt, min_pt, max_pt,
								 bin_pt, min_pt, max_pt);
  histocontainer_3["h3_deltaR_ptB1_pt_B2_signal"]=fs->make<TH3D>("h3_deltaR_ptB1_pt_B2_signal",
								 "h3_deltaR_ptB1_pt_B2_signal",
								 bin_deltaR, min_deltaR, max_deltaR,
								 bin_pt, min_pt, max_pt,
								 bin_pt, min_pt, max_pt);
  histocontainer_3["h3_deltaR_ptB1_pt_B2_background"]=fs->make<TH3D>("h3_deltaR_ptB1_pt_B2_background",
								     "h3_deltaR_ptB1_pt_B2_background",
								     bin_deltaR, min_deltaR, max_deltaR,
								     bin_pt, min_pt, max_pt,
								     bin_pt, min_pt, max_pt);  

  Int_t bin_invmass = 600;
  Double_t min_invmass = 0;
  Double_t max_invmass = 200;

  histocontainer_["h_Wcandidate_mass"]=fs->make<TH1D>("h_Wcandidate_mass","h_Wcandidate_mass", bin_invmass, min_invmass, max_invmass);
  histocontainer_["h_higgsCandidate_mass"]=fs->make<TH1D>("h_higgsCandidate_mass","h_higgsCandidate_mass", bin_invmass, min_invmass, max_invmass);

  histocontainer_["h_invmassJet_signal"]=fs->make<TH1D>("h_invmassJet_signal","invmassJet signal (H)", bin_invmass, min_invmass, max_invmass);
  histocontainer_["h_invmassJet_background"]=fs->make<TH1D>("h_invmassJet_background","invmassJet background", bin_invmass, min_invmass, max_invmass);
  histocontainer_["h_invmassJet_general"]=fs->make<TH1D>("h_invmassJet_general","invmassJet general", bin_invmass, min_invmass, max_invmass);

  histocontainer_["h_invmass_signal"]=fs->make<TH1D>("h_invmass_signal","invmass signal (H)", bin_invmass, min_invmass, max_invmass);
  histocontainer_["h_invmass_background"]=fs->make<TH1D>("h_invmass_background","invmass background", bin_invmass, min_invmass, max_invmass);
  histocontainer_["h_invmass_general"]=fs->make<TH1D>("h_invmass_general","invmass general", bin_invmass, min_invmass, max_invmass);

}

void WH_channel::endJob() {

  std::cout << "Number of events with at least two B hadrons = " << myEvents << std::endl;
  std::cout << "JOB FINISHED" << std::endl;

}

DEFINE_FWK_MODULE(WH_channel);
