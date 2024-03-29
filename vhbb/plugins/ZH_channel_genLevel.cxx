/* ZH_channel_genLevel.cxx analyzer         */
/* v9 May 2011                   */
/* Bortignon Pierluigi             */
/* genLevel cross check            */
/* No Btagging                     */
/* No pt cut on the bosons         */
/* With also parton level          */
/* NTUPLYZER no more histos        */

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
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h" 
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/MuonReco/interface/MuonIsolation.h"

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

class ZH_channel_genLevel : public edm::EDAnalyzer
{
  
public:
  
  explicit ZH_channel_genLevel(const edm::ParameterSet&);

private:
  
  virtual void analyze(const edm::Event&, const edm::EventSetup&) ;
  virtual void beginJob() ;
  virtual void endJob() ;

  inline int getSign(double ); 
  bool muonJetCleaning( const pat::Jet&, const std::vector<reco::Muon>&, double );
  bool muonJetCleaning( const pat::Jet&, const reco::Candidate*, double );
  bool hasHiggsMother( const reco::Candidate* );
  bool hasBMother( const reco::Candidate* );
  bool hasBdaughters( const reco::Candidate * );
  double getAnglePhiEtaPlane( pat::Jet* , pat::Jet* );
  double getAnglePhiEtaPlane( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR( pat::Jet* , pat::Jet* );
  double getDeltaR( const reco::Candidate* , const reco::Candidate* );
  double getDeltaR( TLorentzVector , pat::Jet* );
  double getDeltaR( TLorentzVector , const reco::Candidate* );
  double getDeltaR( const reco::Candidate*, TLorentzVector );
  double getDeltaR( TVector3 , pat::Jet* );
  double getDeltaEta( pat::Jet* , pat::Jet* );
  double getDeltaEta( const reco::Candidate* , const reco::Candidate* );
  double getDeltaPhi( pat::Jet*, pat::Jet* );
  double getPtAsymmetry(pat::Jet*, pat::Jet* );
  double getPtAsymmetry(const reco::GenJet*, const reco::GenJet* );
  unsigned int getAssociatedB( std::vector<TLorentzVector> , pat::Jet* );
  double getBBavProjection( pat::Jet*, pat::Jet* );
  TVector2 getTvect( pat::Jet*, TLorentzVector );
  TVector2 getTvect( pat::Jet* );
  TVector2 getTvect( const reco::GenJet* );
  double getDeltaTheta( pat::Jet*, pat::Jet*, TLorentzVector, TLorentzVector );
  double getDeltaTheta( pat::Jet*, pat::Jet* );
  double getDeltaTheta( const reco::GenJet* , const reco::GenJet* );
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

  struct CompareMCmatching {
    TLorentzVector genb;
    bool operator()( pat::Jet* j1, pat::Jet* j2 ) const {
      return j1->deltaR(genb) < j2->deltaR(genb);
    }
  };


  struct CompareGenJetPt {
    bool operator()( reco::GenJet* j1, reco::GenJet* j2 ) const {
      return j1->p4().Pt() > j2->p4().Pt();
    }
  };

//   struct CompareGenBTag {
//     bool operator()( reco::GenJet* j1, reco::GenJet* j2 ) const {
//       return j1->bDiscriminator("combinedSecondaryVertexBJetTags") > j2->bDiscriminator("combinedSecondaryVertexBJetTags");
//     }
//   };


  ComparePt ptComparator;
  CompareJetPt ptJetComparator;
  CompareBTag btagComparator;
  CompareGenJetPt ptGenJetComparator;

//   CompareGenBTag genBtagComparator;

  //per creare dei TH1 velocemente InputTag.label
  std::map<std::string,TTree*> tree_container;
  std::map<std::string,TH1D*> histocontainer_;
  std::map<std::string,TH2D*> histocontainer_2;
  std::map<std::string,TH3D*> histocontainer_3;

  edm::InputTag ak5pfJetLabel_;
  edm::InputTag ak7pfJetLabel_;
  edm::InputTag muonLabel_;
  edm::InputTag genpLabel_;
  edm::InputTag genJetsLabel_;
  edm::InputTag patJetLabel_;
  edm::ParameterSet pfJetIdSelector_;

  std::vector<int> v_motherId;
  std::vector<int> v_mother_status_background;

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

  Double_t jetPtThreshold;
  Double_t muonJetCleaningDRcut;
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

  Double_t genb1_pt;
  Double_t genb1_eta;
  Double_t genb1_phi;
  Double_t genb1_energy;
  Double_t genb2_pt;
  Double_t genb2_eta;
  Double_t genb2_phi;
  Double_t genb2_energy;
  Double_t genMu1_pt;
  Double_t genMu1_eta;
  Double_t genMu1_phi;
  Double_t genMu1_energy;
  Double_t genMu2_pt;
  Double_t genMu2_eta;
  Double_t genMu2_phi;
  Double_t genMu2_energy;
  Double_t recoJet1_pt;
  Double_t recoJet1_eta;
  Double_t recoJet1_phi;
  Double_t recoJet1_energy;
  Double_t recoJet1_csv;
  Double_t recoJet2_pt;
  Double_t recoJet2_eta;
  Double_t recoJet2_phi;
  Double_t recoJet2_energy; 
  Double_t recoJet2_csv;
  Double_t genHiggs_pt;
  Double_t genHiggs_eta;
  Double_t genHiggs_phi;
  Double_t genHiggs_mass;
  Double_t genHiggs_helicity;
  Double_t recoHiggs_pt;
  Double_t recoHiggs_eta;
  Double_t recoHiggs_phi;
  Double_t recoHiggs_mass;
  Double_t recoHiggs_helicity;
  Double_t genZ_pt;
  Double_t genZ_eta;
  Double_t genZ_phi;
  Double_t genZ_mass;
  Double_t genZ_helicity;
  Double_t recoZ_pt;
  Double_t recoZ_eta;
  Double_t recoZ_phi;
  Double_t recoZ_mass;
  Double_t recoZ_helicity;
  Double_t genZH_deltaPhi;
  Double_t recoZH_deltaPhi;


  Double_t leadingDeltaTheta;
  Double_t secondLeadingDeltaTheta;

  Double_t jetDeltaPhi;
  Double_t jetPtAsymmetry;

  Double_t myVar_background;
  Double_t myVar_signal;

  bool RECO;
  bool bHadron;  
  bool ak5pfJets_flag;
  bool ak7pfJets_flag;
  bool genJets_flag;
  bool btagOrdering;
  bool ptOrdering;
  bool MCmatchingOrdering;

  unsigned int different_plane;
  unsigned int same_plane;

};

ZH_channel_genLevel::ZH_channel_genLevel(const edm::ParameterSet& iConfig) : 

  tree_container(),
  histocontainer_(),
  histocontainer_2(),
  histocontainer_3(),

  //cleaning cut
  jetDRcut(iConfig.getUntrackedParameter<double>("jetDeltaRcut")),
  jetPtThreshold(iConfig.getUntrackedParameter<double>("jetPtThreshold")),
  ak5pfJets_flag(iConfig.getUntrackedParameter<bool>("ak5pfJets_flag")),
  ak7pfJets_flag(iConfig.getUntrackedParameter<bool>("ak7pfJets_flag")),
  genJets_flag(iConfig.getUntrackedParameter<bool>("genJets_flag")),
  btagOrdering(iConfig.getUntrackedParameter<bool>("btagOrdering")),
  ptOrdering(iConfig.getUntrackedParameter<bool>("ptOrdering")),
  MCmatchingOrdering(iConfig.getUntrackedParameter<bool>("MCmatchingOrdering")),
  RECO(iConfig.getUntrackedParameter<bool>("RECO")),

  muonJetCleaningDRcut(iConfig.getUntrackedParameter<double>("muonJetCleaningDRcut")),
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
  genJetsLabel_(iConfig.getUntrackedParameter<edm::InputTag>("ak5GenJets")),
  muonLabel_(iConfig.getUntrackedParameter<edm::InputTag>("muonCand")),
  ak5pfJetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("ak5pfJets")),
  ak7pfJetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("ak7pfJets")),
  pfJetIdSelector_(iConfig.getParameter<edm::ParameterSet>("pfJetIDSelector") )
{

  //Initialize counters
  different_plane = 0;
  same_plane  = 0;
  n_event = 0;
  myEvents = 0;

}   

void ZH_channel_genLevel::analyze(const edm::Event& iEvent, const edm::EventSetup& setup)
{
  ++n_event;

  //initialising each events
  higgs_pt = 1e10;
  vector_pt = 1e10;

   genb1_pt = 1e10;
   genb1_eta = 1e10;
   genb1_phi = 1e10;
   genb1_energy = 1e10;
   genb2_pt = 1e10;
   genb2_eta = 1e10;
   genb2_phi = 1e10;
   genb2_energy = 1e10;
   genMu1_pt = 1e10;
   genMu1_eta = 1e10;
   genMu1_phi = 1e10;
   genMu1_energy = 1e10;
   genMu2_pt = 1e10;
   genMu2_eta = 1e10;
   genMu2_phi = 1e10;
   genMu2_energy = 1e10;
   recoJet1_pt = 1e10;
   recoJet1_eta = 1e10;
   recoJet1_phi = 1e10;
   recoJet1_energy = 1e10;
   recoJet1_csv = 1e10;
   recoJet2_pt = 1e10;
   recoJet2_eta = 1e10;
   recoJet2_phi = 1e10;
   recoJet2_energy = 1e10;
   recoJet2_csv = 1e10;
  genHiggs_pt = 1e10;
  genHiggs_eta = 1e10;
  genHiggs_phi = 1e10;
  genHiggs_mass = 1e10;
  genHiggs_helicity = 1e10;
  recoHiggs_pt = 1e10;
  recoHiggs_eta = 1e10;
  recoHiggs_phi = 1e10;
  recoHiggs_mass = 1e10;
  recoHiggs_helicity = 1e10;
  genZ_pt = 1e10;
  genZ_eta = 1e10;
  genZ_phi = 1e10;
  genZ_mass = 1e10;
  genZ_helicity = 1e10;
  recoZ_pt = 1e10;
  recoZ_eta = 1e10;
  recoZ_phi = 1e10;
  recoZ_mass = 1e10;
  recoZ_helicity = 1e10;
  genZH_deltaPhi = 1e10;
  recoZH_deltaPhi = 1e10;
  leadingDeltaTheta = 1e10;
  secondLeadingDeltaTheta = 1e10;

  std::cout << "*** Analyzing " << iEvent.id() << " n_event = " << n_event << std::endl << std::endl;

  //ak5patJet
  edm::Handle< pat::JetCollection > ak5patJetHandle;
  iEvent.getByLabel(ak5pfJetLabel_, ak5patJetHandle);
  const  pat::JetCollection &ak5patJet = *ak5patJetHandle.product();
  //JetID. Siggested cuts for 7TeV analysis: LOOSE. https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID 
  //  JetIDSelectionFunctor jetIDFunctor( JetIDSelectionFunctor::PURE09, JetIDSelectionFunctor::LOOSE );
  PFJetIDSelectionFunctor ak5pfJetIDFunctor( pfJetIdSelector_ );
  // needed for the jetId
  pat::strbitset ak5ret = ak5pfJetIDFunctor.getBitTemplate();

  //ak7patJet
  edm::Handle< pat::JetCollection > ak7patJetHandle;
  iEvent.getByLabel(ak7pfJetLabel_, ak7patJetHandle);
  const  pat::JetCollection &ak7patJet = *ak7patJetHandle.product();
  //JetID. Siggested cuts for 7TeV analysis: LOOSE. https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID 
  //  JetIDSelectionFunctor jetIDFunctor( JetIDSelectionFunctor::PURE09, JetIDSelectionFunctor::LOOSE );
  PFJetIDSelectionFunctor ak7pfJetIDFunctor( pfJetIdSelector_ );
  // needed for the jetId
  pat::strbitset ak7ret = ak7pfJetIDFunctor.getBitTemplate();

  //muon handle
  //  edm::Handle< edm::View< reco::Muon > > muonHandle;
  edm::Handle< reco::MuonCollection > muonHandle;
  iEvent.getByLabel(muonLabel_,muonHandle);
  //  edm::View<reco::Muon> muons = *muonHandle;
  const reco::MuonCollection &UnsortedMuons = *muonHandle.product();
  reco::MuonCollection muons = UnsortedMuons;
  std::sort( muons.begin(), muons.end(), ptComparator);

  // Generated particles handle
  edm::Handle<reco::GenParticleCollection> genP;
  iEvent.getByLabel(genpLabel_,genP);
  //edm::View<reco::GenParticle> genParticles = *genP;
  const reco::GenParticleCollection &genParticles = *genP.product();

  // GenJets
  edm::Handle<reco::GenJetCollection> genJets;
  iEvent.getByLabel(genJetsLabel_,genJets);
  const reco::GenJetCollection &genJ = *genJets.product();

  v_motherId.clear();
  v_mother_status_background.clear();
  bHadron_general.clear();
  bHadron_signal.clear();
  bHadron_background.clear();

  std::vector<const reco::Candidate*> v_muon;
  std::vector<const reco::Candidate*> v_muon_p;
  std::vector<const reco::Candidate*> v_muon_n;
  TLorentzVector genHiggs;
  TLorentzVector genZ;
  TLorentzVector genb1;
  TLorentzVector genb2;
  TLorentzVector genMu1;
  TLorentzVector genMu2;

  pat::Jet* leadingJet;
  pat::Jet* secondLeadingJet;

  unsigned int bcount = 0;
  unsigned int mucount = 0;
  int b1_mother = 0;
  int b2_mother = 0;

  // PARTON LEVEL
  // Generated particles loop
  for( reco::GenParticleCollection::const_iterator iGenp = genParticles.begin(); 
       iGenp != genParticles.end();
       ++iGenp) 
    {
      const reco::Candidate *genCandidate = &(*iGenp);

//       if( genCandidate->pdgId() == 25 )
// 	genHiggs.SetPtEtaPhiE( genCandidate->pt(),
// 			       genCandidate->eta(),
// 			       genCandidate->phi(),
// 			       genCandidate->energy() );
      if( ( genCandidate->pdgId() == 5 )
	  //21 = gluon; 25 = higgs
 	  and ( genCandidate->mother()->pdgId() == 25 )
	  and ( not hasBMother(genCandidate) ) ){
	genb1.SetPtEtaPhiE( genCandidate->pt(),
			    genCandidate->eta(),
			    genCandidate->phi(),
			    genCandidate->energy() );
	bcount++;
	b1_mother = genCandidate->mother()->pdgId();
      }
      else if( ( genCandidate->pdgId() == -5 )
	       //21 = gluon; 25 = higgs
	       and ( genCandidate->mother()->pdgId() == 25 )
	       and ( not hasBMother(genCandidate) ) ){
	genb2.SetPtEtaPhiE( genCandidate->pt(),
			    genCandidate->eta(),
			    genCandidate->phi(),
			    genCandidate->energy() );
	bcount++;
	b2_mother = genCandidate->mother()->pdgId();
      }

      else if( ( genCandidate->pdgId() == 13 )
	       and ( genCandidate->mother()->pdgId() == 23 ) ){
	genMu1.SetPtEtaPhiE( genCandidate->pt(),
			     genCandidate->eta(),
			     genCandidate->phi(),
			     genCandidate->energy() );
	mucount++;
      }
      else if( ( genCandidate->pdgId() == -13 )
	       and ( genCandidate->mother()->pdgId() == 23 ) ){
	genMu2.SetPtEtaPhiE( genCandidate->pt(),
			     genCandidate->eta(),
			     genCandidate->phi(),
			     genCandidate->energy() );
	mucount++;
      }
      
    }//END GENPARTICLEs LOOP
  
  if( bcount > 1 
      and mucount > 1 ){
    genHiggs = genb1 + genb2;
    genb1_pt =  genb1.Pt();
    genb1_phi =  genb1.Phi();
    genb1_eta =  genb1.Eta();
    genb1_energy = genb1.Energy();
    genb2_pt =  genb2.Pt();
    genb2_phi =  genb2.Phi();
    genb2_eta =  genb2.Eta();
    genb2_energy = genb2.Energy();
    genHiggs_pt =  genHiggs.Pt();
    genHiggs_phi =  genHiggs.Phi();
    genHiggs_eta =  genHiggs.Eta();
    genHiggs_mass = genHiggs.M();
    TVector3 genHiggsBoost;
    genHiggsBoost = genHiggs.BoostVector();
    if( genb1.Pt() > genb2.Pt() )
      genHiggs_helicity =  getHelicity( genb1, genHiggsBoost );
    else 
      genHiggs_helicity =  getHelicity( genb2, genHiggsBoost );

    genZ = genMu1 + genMu2;
    genMu1_pt =  genMu1.Pt();
    genMu1_phi =  genMu1.Phi();
    genMu1_eta =  genMu1.Eta();
    genMu1_energy = genMu1.Energy();
    genMu2_pt =  genMu2.Pt();
    genMu2_phi =  genMu2.Phi();
    genMu2_eta =  genMu2.Eta();
    genMu2_energy = genMu2.Energy();
    genZ_pt =  genZ.Pt();
    genZ_eta =  genZ.Eta();
    genZ_phi =  genZ.Phi();
    genZ_mass = genZ.M();
    genZH_deltaPhi = Geom::deltaPhi(genHiggs.Vect().Phi(), genZ.Vect().Phi());
    TVector3 genZBoost;
    genZBoost = genZ.BoostVector();
    if( genMu1.Pt() > genMu2.Pt() )
      genZ_helicity =  getHelicity( genMu1, genZBoost );
    else 
      genZ_helicity =  getHelicity( genMu2, genZBoost );
  }
  else
    return void();
  

  //   if( genJets_flag == true ){
  //     std::vector<reco::GenJet*> v_jets;
  //     // MC TRUTH JETS
  //     for(size_t jetIdx = 0; jetIdx < genJ.size(); ++jetIdx){
  //       if( genJ.at(jetIdx).p4().Pt() > jetPtThreshold )
  // 	v_jets.push_back( new reco::GenJet (genJ.at(jetIdx)) );
  //     }
  //   }
//   else{
//     std::cout << "No jet collection found..." << std::endl;
//     return void();
//   }
  
//   if( v_jets.size() < 2 )
//     return void();
  
  //   if( genJets_flag == true ){
  //     if( btagOrdering == true )
  //       std::sort(v_jets.begin(), v_jets.end(), genBtagComparator);
  //     else if( ptOrdering == true )
  //       std::sort(v_jets.begin(), v_jets.end(), ptGenJetComparator);
  //     //  else if( pullOrdering ) //to do
  //     else{
  //       std::cout << "No jet ordering found..." << std::endl; 
  //       return void();
  //     }
  //   }
  

  //for the reconstructed quantities
  if(RECO == true){

    //muon selection
    for( size_t muon_iter = 0; muon_iter < muons.size(); muon_iter++){
      const reco::MuonIsolation muIso = muons.at(muon_iter).isolationR03();
      if( muon::isGoodMuon( muons.at(muon_iter), muon::GlobalMuonPromptTight) and
	  muons.at(muon_iter).isGlobalMuon() == true and
	  muons.at(muon_iter).isTrackerMuon() and
	  muons.at(muon_iter).globalTrack()->pt() > 20 and
	  TMath::Abs(muons.at(muon_iter).globalTrack()->eta()) < 2.4 and
	  muons.at(muon_iter).globalTrack()->ptError()/muons.at(muon_iter).globalTrack()->pt() < 0.1 and 
	  // 	muons.at(muon_iter).  HitPatter::numberOfValidPixelHits() > 1 
	  // 	TMath::Abs(muons.at(muon_iter).globalTrack()->d0(OfflinePrimaryVertex)) < 0.02 and
	  // 	TMath::Abs(muons.at(muon_iter).globalTrack()->dz(OfflinePrimaryVertex)) < 1 and
	  muons.at(muon_iter).numberOfMatches() > 1 and
	  muons.at(muon_iter).isIsolationValid() == true and
	  muIso.sumPt < 3 ){
	if( muons.at(muon_iter).charge() == 1 )
	  v_muon_p.push_back( &( muons.at(muon_iter) ) );
	else
	  v_muon_n.push_back( &( muons.at(muon_iter) ) );
      } 
    }

    //Event selection: at least two jets and two muons with opposite sign
    if(  v_muon_n.size() < 1
	 or v_muon_p.size() < 1 )
      return void();

    v_muon.push_back( v_muon_p.at(0) );
    v_muon.push_back( v_muon_n.at(0) );  

    //    std::cout << "ak5pfJets_flag = " << ak5pfJets_flag << std::endl;
    std::vector<pat::Jet*> v_jets;
    if( ak5pfJets_flag == true ){
      //AK5PF
      for(size_t jetIdx = 0; jetIdx < ak5patJet.size(); ++jetIdx){
	if( ak5patJet.at(jetIdx).isPFJet() == true 
	    and ak5pfJetIDFunctor( ak5patJet.at(jetIdx), ak5ret ) == true 
	    and ak5patJet.at(jetIdx).correctedJet("L3Absolute").pt() > jetPtThreshold
	    and muonJetCleaning( ak5patJet.at(jetIdx), v_muon_p.at(0), muonJetCleaningDRcut ) == false 
	    and muonJetCleaning( ak5patJet.at(jetIdx), v_muon_n.at(0), muonJetCleaningDRcut ) == false )
	  v_jets.push_back( new pat::Jet (ak5patJet.at(jetIdx).correctedJet("L3Absolute")) );
      }  
    }
    else if( ak7pfJets_flag == true ){
      //AK7PF
      for(size_t jetIdx = 0; jetIdx < ak7patJet.size(); ++jetIdx){
	if( ak7patJet.at(jetIdx).isPFJet() == true 
	    and ak7pfJetIDFunctor( ak7patJet.at(jetIdx), ak7ret ) == true 
	    and ak7patJet.at(jetIdx).correctedJet("L3Absolute").pt() > jetPtThreshold
	    and muonJetCleaning( ak7patJet.at(jetIdx), v_muon_p.at(0), muonJetCleaningDRcut ) == false 
	    and muonJetCleaning( ak7patJet.at(jetIdx), v_muon_n.at(0), muonJetCleaningDRcut ) == false )
	  v_jets.push_back( new pat::Jet (ak7patJet.at(jetIdx).correctedJet("L3Absolute")) );
      }  
    }
    else{
      std::cout << "No jet collection found..." << std::endl;
      return void();
    }

    if( v_jets.size() < 2 )
      return void();

    if( btagOrdering == true )
      std::sort(v_jets.begin(), v_jets.end(), btagComparator);
    else if( ptOrdering == true )
      std::sort(v_jets.begin(), v_jets.end(), ptJetComparator);
    else if( MCmatchingOrdering == true ){
      CompareMCmatching MCmatchingComparator;
      MCmatchingComparator.genb = genb1;
      std::sort(v_jets.begin(), v_jets.end(), MCmatchingComparator );
      MCmatchingComparator.genb = genb2;
      std::sort(v_jets.begin()+1, v_jets.end(), MCmatchingComparator );
    }
    else{
      std::cout << "No jet ordering found..." << std::endl; 
      return void();
    }
    //  else if( pullOrdering ) //to do

    if( v_jets.at(0)->p4().Pt() > v_jets.at(1)->p4().Pt() ){
      leadingJet = v_jets.at(0);
      secondLeadingJet = v_jets.at(1);
    }
    else{
      leadingJet = v_jets.at(1);
      secondLeadingJet = v_jets.at(0);
    }

    //gen-reco associationA
    if( getDeltaR(v_muon_p.at(0), genMu2) > 0.5
	or getDeltaR(v_muon_n.at(0), genMu1) > 0.5
	or ( getDeltaR(v_jets.at(0), genb1) > 0.5
	     and getDeltaR(v_jets.at(1), genb1) > 0.5 )
	or ( getDeltaR(v_jets.at(0), genb2) > 0.5
	     and getDeltaR(v_jets.at(1), genb2) > 0.5 ) )
      return void();

    recoJet1_pt =  v_jets.at(0)->p4().Pt();
    recoJet1_phi =  v_jets.at(0)->p4().Phi();
    recoJet1_eta =  v_jets.at(0)->p4().Eta();
    recoJet1_energy = v_jets.at(0)->p4().E();
    recoJet1_csv = v_jets.at(0)->bDiscriminator("combinedSecondaryVertexBJetTags");
    recoJet2_pt =  v_jets.at(1)->p4().Pt();
    recoJet2_phi =  v_jets.at(1)->p4().Phi();
    recoJet2_eta =  v_jets.at(1)->p4().Eta();
    recoJet2_energy =  v_jets.at(1)->p4().E();
    recoJet2_csv = v_jets.at(1)->bDiscriminator("combinedSecondaryVertexBJetTags");

    //EWK
    reco::CompositeCandidate Zcandidate;
    Zcandidate.addDaughter( *v_muon.at(0) );
    Zcandidate.addDaughter( *v_muon.at(1) );
    AddFourMomenta addZp4;
    addZp4.set(Zcandidate);
    recoZ_pt = Zcandidate.p4().Pt();
    recoZ_eta = Zcandidate.p4().Eta();
    recoZ_phi = Zcandidate.p4().Phi();
    recoZ_mass = Zcandidate.p4().M();  
    TLorentzVector ZP4;
    ZP4.SetPtEtaPhiE( Zcandidate.pt() , 
		      Zcandidate.eta(),
		      Zcandidate.phi(),
		      Zcandidate.energy() );
    TVector3 ZBoost;
    ZBoost = ZP4.BoostVector();
    TLorentzVector Mu;
    Mu.SetPtEtaPhiE( v_muon.at(0)->p4().Pt(), 
		     v_muon.at(0)->p4().Eta(), 
		     v_muon.at(0)->p4().Phi(), 
		     v_muon.at(0)->p4().E() );
    recoZ_helicity = getHelicity( Mu , ZBoost );
    
    reco::CompositeCandidate higgsCandidate;
    higgsCandidate.addDaughter( *v_jets.at(0) );
    higgsCandidate.addDaughter( *v_jets.at(1) );
    AddFourMomenta addp4;
    addp4.set(higgsCandidate);
    recoHiggs_pt = higgsCandidate.p4().Pt();
    recoHiggs_eta = higgsCandidate.p4().Eta();
    recoHiggs_phi = higgsCandidate.p4().Phi();
    recoHiggs_mass = higgsCandidate.p4().M();
    TLorentzVector higgsP4;
    higgsP4.SetPtEtaPhiE( higgsCandidate.pt() , 
			  higgsCandidate.eta(),
			  higgsCandidate.phi(),
			  higgsCandidate.energy() );
    TVector3 higgsBoost;
    higgsBoost = higgsP4.BoostVector();
    recoHiggs_helicity = getHelicity( leadingJet, higgsBoost );

    recoZH_deltaPhi = Geom::deltaPhi(higgsCandidate.p4(), Zcandidate.p4());

    TVector2 secondLeadingT;
    TVector2 leadingT;
    secondLeadingT = getTvect(secondLeadingJet);
    leadingT = getTvect(leadingJet);
    if(secondLeadingT.Mod() < 1e-7 
       or leadingT.Mod() < 1e-7 )
      return void();
    leadingDeltaTheta = TMath::Abs( getDeltaTheta( leadingJet , secondLeadingJet ) );
    secondLeadingDeltaTheta = TMath::Abs( getDeltaTheta( secondLeadingJet, leadingJet ) );

    v_jets.clear(); 
  }


  tree_container["ZMuMu_channel"]->Fill();   
  
  myEvents++;
  
}//END EVENT LOOP



//funzione segno
inline int ZH_channel_genLevel::getSign(double v) { return v > 0 ? 1 : (v < 0 ? -1 : 0); } 

//puliamo i pfjet dai muoni con un deltaR
// if it is true get rid of the jet
bool ZH_channel_genLevel::muonJetCleaning(const pat::Jet& tmpJet, const std::vector<reco::Muon>& muCol, double deltaRcut){
  bool clean = false;
  double deltaR = 1e10;
  for(size_t muIdx = 0; muIdx < muCol.size(); ++muIdx){
    deltaR = Geom::deltaR(tmpJet.p4().Vect(), muCol.at(muIdx).p4().Vect() );
    if( deltaR < deltaRcut )
      clean = true;
  }  
  return clean;
}

//puliamo i muoni non isolati
// if it is true get rid of the muon
bool ZH_channel_genLevel::muonJetCleaning( const pat::Jet& patJet, const reco::Candidate* muCol, double drCut){
  bool clean = false;
  double dr = 1e10;
  dr = Geom::deltaR( muCol->p4().Vect(), patJet.p4().Vect() );
  if( dr < drCut )
    clean = true;
  return clean;
}

//metodo per guardare se ha un Higgs come antenato
bool ZH_channel_genLevel::hasHiggsMother( const reco::Candidate * particle ){
  bool hashiggsmother = false;
  while ( particle->numberOfMothers() != 0 ){
    if( particle->mother()->pdgId() == 25 )
      hashiggsmother = true;
    particle = particle->mother();
  }
  return hashiggsmother;
}

//metodo per guardare se ha un b come antenato
bool ZH_channel_genLevel::hasBMother( const reco::Candidate * particle ){
  bool hasBmother = false;
  while ( particle->numberOfMothers() != 0 ){
    if( TMath::Abs(particle->mother()->pdgId()) == 5 )
      hasBmother = true;
    particle = particle->mother();
  }
  return hasBmother;
}


//check if there are dbflavoured daughters
bool ZH_channel_genLevel::hasBdaughters( const reco::Candidate * particle ){
  bool myDaughterHasBottom = false;
  for(size_t myDau = 0; myDau < particle->numberOfDaughters(); myDau++){
    HepPDT::ParticleID myDaughter( particle->daughter(myDau)->pdgId() ); 
    myDaughterHasBottom += myDaughter.hasBottom();
  }
  return myDaughterHasBottom;
}

// calcolo dell'angolo nel piano eta phi della retta conguingente due jet
double ZH_channel_genLevel::getAnglePhiEtaPlane( pat::Jet *leadingJet , pat::Jet *secondLeadingJet ){
  double angle = 1e10;
  double deltaPhi = leadingJet->p4().Phi() - secondLeadingJet->p4().Phi();
  double deltaEta = leadingJet->p4().Eta() - secondLeadingJet->p4().Eta();
  angle = TMath::ATan2( deltaPhi, deltaEta );
  return angle;
}

// calcolo dell'angolo nel piano eta phi della retta conguingente due b hadron
double ZH_channel_genLevel::getAnglePhiEtaPlane( const reco::Candidate *firstB , const reco::Candidate *secondB ){
  double angle = 1e10;
  double deltaPhi = firstB->phi() - secondB->phi();
  double deltaEta = firstB->eta() - secondB->eta();
  angle = TMath::ATan2( deltaPhi, deltaEta );
  return angle;
}

double ZH_channel_genLevel::getDeltaR( pat::Jet * leadingJet, pat::Jet * secondLeadingJet ){
  double deltaR = 1e10;
  deltaR = Geom::deltaR( leadingJet->p4().Vect(), secondLeadingJet->p4().Vect() );
  return deltaR;
}

double ZH_channel_genLevel::getDeltaR( const reco::Candidate * firstB, const reco::Candidate * secondB ){
  double deltaR = 1e10;
  deltaR = Geom::deltaR( firstB->momentum(), secondB->momentum() );
  return deltaR;
}

double ZH_channel_genLevel::getDeltaR( TLorentzVector TLV, pat::Jet * patJet ){
  double deltaR = 1e10;
  TVector3 JetVector;
  JetVector.SetXYZ( patJet->p4().Px(), patJet->p4().Py(), patJet->p4().Pz() );
  deltaR = JetVector.DeltaR( TLV.Vect() ) ;
  return deltaR;
}

double ZH_channel_genLevel::getDeltaR( TLorentzVector TLV, const reco::Candidate* recoCand ){
  double deltaR = 1e10;
  TVector3 tv3;
  tv3.SetXYZ( recoCand->momentum().X(), recoCand->momentum().Y(), recoCand->momentum().Z()  );
  deltaR = tv3.DeltaR( TLV.Vect() ) ;
  return deltaR;
}
double ZH_channel_genLevel::getDeltaR( const reco::Candidate* recoCand, TLorentzVector TLV ){
  double deltaR = 1e10;
  TVector3 tv3;
  tv3.SetXYZ( recoCand->momentum().X(), recoCand->momentum().Y(), recoCand->momentum().Z()  );
  deltaR = tv3.DeltaR( TLV.Vect() ) ;
  return deltaR;
}

double ZH_channel_genLevel::getDeltaR( TVector3 TLV, pat::Jet * patJet ){
  double deltaR = 1e10;
  TVector3 JetVector;
  JetVector.SetXYZ( patJet->p4().Px(), patJet->p4().Py(), patJet->p4().Pz() );
  deltaR = JetVector.DeltaR( TLV ) ;
  return deltaR;
}

double ZH_channel_genLevel::getDeltaEta( pat::Jet * leadingJet, pat::Jet * secondLeadingJet ){
  double deltaEta = 1e10;
  deltaEta = leadingJet->p4().Eta() - secondLeadingJet->p4().Eta() ;
  return deltaEta;
}

double ZH_channel_genLevel::getDeltaEta( const reco::Candidate * firstB, const reco::Candidate * secondB ){
  double deltaEta = 1e10;
  deltaEta = firstB->eta() - secondB->eta() ;
  return deltaEta;
}

double ZH_channel_genLevel::getDeltaPhi( pat::Jet* leadingJet, pat::Jet* secondLeadingJet){

  double deltaPhi = 1e10;
  deltaPhi = Geom::deltaPhi( leadingJet->p4().Vect(), secondLeadingJet->p4().Vect() ) ;
  return deltaPhi;

}

double ZH_channel_genLevel::getPtAsymmetry(pat::Jet* leadingJet, pat::Jet* secondLeadingJet ){

  double asymmetry = 1e10;
  double ptDiff = leadingJet->p4().Pt() - secondLeadingJet->p4().Pt();
  double ptSum = leadingJet->p4().Pt() + secondLeadingJet->p4().Pt();
  asymmetry = ptDiff / ptSum;
  return asymmetry;
}

double ZH_channel_genLevel::getPtAsymmetry(const reco::GenJet* leadingJet, const reco::GenJet* secondLeadingJet ){

  double asymmetry = 1e10;
  double ptDiff = leadingJet->p4().Pt() - secondLeadingJet->p4().Pt();
  double ptSum = leadingJet->p4().Pt() + secondLeadingJet->p4().Pt();
  asymmetry = ptDiff / ptSum;
  return asymmetry;
}

unsigned int ZH_channel_genLevel::getAssociatedB( std::vector<TLorentzVector> bHadron_vector, pat::Jet* leadingJet){

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


double ZH_channel_genLevel::getBBavProjection( pat::Jet* j1, pat::Jet* j2 ){

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
TVector2 ZH_channel_genLevel::getTvect( pat::Jet* patJet, TLorentzVector b ){

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
TVector2 ZH_channel_genLevel::getTvect( pat::Jet* patJet ){

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

// Gen Jets without b vertex information
TVector2 ZH_channel_genLevel::getTvect( const reco::GenJet* genJet ){

  TVector2 t_Vect(0,0);
  TVector2 null(0,0);
  TVector2 ci(0,0);
  TLorentzVector pi(0,0,0,0);
  TLorentzVector J(0,0,0,0);
  TVector2 r(0,0);
  double genJetpfcPt = 1e10;
  double r_mag = 1e10;
  unsigned int nOfconst = 0;

  std::vector<const reco::GenParticle*>
    genJetpfc = genJet->getGenConstituents();
  for(size_t idx = 0; idx < genJetpfc.size(); idx++){
    if( genJetpfc.at(idx)->charge() != 0 and genJetpfc.at(idx)->status() == 1 ){
      pi.SetPtEtaPhiE( genJetpfc.at(idx)->pt(), genJetpfc.at(idx)->eta(), genJetpfc.at(idx)->phi(), genJetpfc.at(idx)->energy() );
//       pi.SetPtEtaPhiE( genJetpfc.at(idx)->pt(), genJetpfc.at(idx)->eta(), genJetpfc.at(idx)->phi(), genJetpfc.at(idx)->p() );
      J += pi;
      nOfconst++;
    }
  }

  if( nOfconst < 2 )
    return null;

  TVector2 v_J( J.Rapidity(), J.Phi() );

  for(size_t idx = 0; idx < genJetpfc.size(); idx++){
    if( genJetpfc.at(idx)->charge() != 0 and genJetpfc.at(idx)->status() == 1 ){
      genJetpfcPt = genJetpfc.at(idx)->pt();
      pi.SetPtEtaPhiE( genJetpfc.at(idx)->pt(), genJetpfc.at(idx)->eta(), genJetpfc.at(idx)->phi(), genJetpfc.at(idx)->energy() );
//       pi.SetPtEtaPhiE( genJetpfc.at(idx)->pt(), genJetpfc.at(idx)->eta(), genJetpfc.at(idx)->phi(), genJetpfc.at(idx)->p() );
      r.Set( pi.Rapidity() - J.Rapidity(), Geom::deltaPhi( genJetpfc.at(idx)->phi(), J.Phi() ) );
      r_mag = r.Mod();
      t_Vect += ( genJetpfcPt / J.Pt() ) * r_mag * r;
    }
  }

  return t_Vect;
  
}


// with b vertex information
double ZH_channel_genLevel::getDeltaTheta( pat::Jet* j1, pat::Jet* j2, TLorentzVector b1, TLorentzVector b2 ){

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
double ZH_channel_genLevel::getDeltaTheta( pat::Jet* j1, pat::Jet* j2 ){

  double deltaTheta = 1e10;
  TLorentzVector pi(0,0,0,0);
  TLorentzVector v_j1(0,0,0,0);
  TLorentzVector v_j2(0,0,0,0);

  std::vector<reco::PFCandidatePtr>
    j1pfc = j1->getPFConstituents();
  for(size_t idx = 0; idx < j1pfc.size(); idx++){
    if( j1pfc.at(idx)->charge() != 0 and j1pfc.at(idx)->status() == 1 ){
      pi.SetPtEtaPhiE( j1pfc.at(idx)->pt(), j1pfc.at(idx)->eta(), j1pfc.at(idx)->phi(), j1pfc.at(idx)->energy() );
      v_j1 += pi;
    }
  }

  std::vector<reco::PFCandidatePtr>
    j2pfc = j2->getPFConstituents();
  for(size_t idx = 0; idx < j2pfc.size(); idx++){
    if( j2pfc.at(idx)->charge() != 0 and j2pfc.at(idx)->status() == 1 ){
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

// Gen Jets without b vertex information
double ZH_channel_genLevel::getDeltaTheta( const reco::GenJet* j1, const reco::GenJet* j2 ){

  double deltaTheta = 1e10;
  TLorentzVector pi(0,0,0,0);
  TLorentzVector v_j1(0,0,0,0);
  TLorentzVector v_j2(0,0,0,0);

  std::vector<const reco::GenParticle* >
    j1pfc = j1->getGenConstituents();
  for(size_t idx = 0; idx < j1pfc.size(); idx++){
    if( j1pfc.at(idx)->charge() != 0 ){
      pi.SetPtEtaPhiE( j1pfc.at(idx)->pt(), j1pfc.at(idx)->eta(), j1pfc.at(idx)->phi(), j1pfc.at(idx)->energy() );
//       pi.SetPtEtaPhiE( j1pfc.at(idx)->pt(), j1pfc.at(idx)->eta(), j1pfc.at(idx)->phi(), j1pfc.at(idx)->p() );
      v_j1 += pi;
    }
  }

  std::vector<const reco::GenParticle* >
    j2pfc = j2->getGenConstituents();
  for(size_t idx = 0; idx < j2pfc.size(); idx++){
    if( j2pfc.at(idx)->charge() != 0 ){
      pi.SetPtEtaPhiE( j2pfc.at(idx)->pt(), j2pfc.at(idx)->eta(), j2pfc.at(idx)->phi(), j2pfc.at(idx)->energy() );
//       pi.SetPtEtaPhiE( j2pfc.at(idx)->pt(), j2pfc.at(idx)->eta(), j2pfc.at(idx)->phi(), j2pfc.at(idx)->p() );
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



double ZH_channel_genLevel::getDeltaX( pat::Jet* j1, pat::Jet* j2, TLorentzVector b1, TLorentzVector b2 ){

  double deltaX = 1e10;
  TVector2 v_j1(j1->p4().Eta(), j1->p4().Phi());
  TVector2 v_j2(j2->p4().Eta(), j2->p4().Phi());
  TVector2 v_b1(b1.Eta(), b1.Phi());
  TVector2 v_b2(b2.Eta(), b2.Phi());

  TVector2 t = getTvect(j1, b1);

  deltaX = t.X() - v_b2.X();

  return deltaX;

}

double ZH_channel_genLevel::getDeltaY( pat::Jet* j1, pat::Jet* j2, TLorentzVector b1, TLorentzVector b2 ){

  double deltaY = 1e10;
  TVector2 v_j1(j1->p4().Eta(), j1->p4().Phi());
  TVector2 v_j2(j2->p4().Eta(), j2->p4().Phi());
  TVector2 v_b1(b1.Eta(), b1.Phi());
  TVector2 v_b2(b2.Eta(), b2.Phi());

  TVector2 t = getTvect(j1, b1);

  deltaY = t.Y() - v_b2.Y();

  return deltaY;

}

double ZH_channel_genLevel::getMyVar_background( pat::Jet* patJet, TVector3 Bpos ){

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

double ZH_channel_genLevel::getMyVar_signal( pat::Jet* patJet, TVector3 Bpos, double BanglePhiEtaPlane ){

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


TVector2 ZH_channel_genLevel::getBBdir( pat::Jet* j1, pat::Jet* j2 ){

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
inline pat::Jet* ZH_channel_genLevel::whichJet(pat::Jet *j1, pat::Jet *j2){

  if( TMath::Abs( j1->p4().Eta() ) - TMath::Abs( j2->p4().Eta() ) > 0 )
    return j1;
  else
    return j2;
}

// return the opposite of whichJet
inline pat::Jet* ZH_channel_genLevel::whichOtherJet(pat::Jet *j1, pat::Jet *j2){

  if( TMath::Abs( j1->p4().Eta() ) - TMath::Abs( j2->p4().Eta() ) < 0 )
    return j1;
  else
    return j2;
}

double ZH_channel_genLevel::getHelicity( pat::Jet* jet , TVector3 boost ){
  double hel = 1e10;
  TLorentzVector j;
  j.SetPtEtaPhiE( jet->pt(), jet->eta(), jet->phi(), jet->energy() );
  j.Boost( -boost );
  hel = TMath::Cos( j.Vect().Angle( boost ) );
  return hel;
}


double ZH_channel_genLevel::getHelicity( const reco::GenJet* jet , TVector3 boost ){
  double hel = 1e10;
  TLorentzVector j;
  j.SetPtEtaPhiE( jet->pt(), jet->eta(), jet->phi(), jet->energy() );
  j.Boost( -boost );
  hel = TMath::Cos( j.Vect().Angle( boost ) );
  return hel;
}

double ZH_channel_genLevel::getHelicity( TLorentzVector b , TVector3 boost ){
  double hel = 1e10;
  b.Boost( -boost );
  hel = TMath::Cos( b.Vect().Angle( boost ) );
  return hel;
}


void ZH_channel_genLevel::beginJob()
{
  
  using namespace std;  
  edm::Service<TFileService> fs;


  tree_container["ZMuMu_channel"]=fs->make<TTree>("ZMuMu_channel","ZMuMu_channel");

  abis::make_branch(tree_container,"genb1_pt"                   ,genb1_pt);
  abis::make_branch(tree_container,"genb1_eta"                  ,genb1_eta);
  abis::make_branch(tree_container,"genb1_phi"                  ,genb1_phi);
  abis::make_branch(tree_container,"genb1_energy"                 ,genb1_energy);
  abis::make_branch(tree_container,"genb2_pt"                   ,genb2_pt);
  abis::make_branch(tree_container,"genb2_eta"                  ,genb2_eta);
  abis::make_branch(tree_container,"genb2_phi"                  ,genb2_phi);
  abis::make_branch(tree_container,"genb2_energy"                 ,genb2_energy);
  abis::make_branch(tree_container,"recoJet1_pt"                   ,recoJet1_pt);
  abis::make_branch(tree_container,"recoJet1_eta"                  ,recoJet1_eta);
  abis::make_branch(tree_container,"recoJet1_phi"                  ,recoJet1_phi);
  abis::make_branch(tree_container,"recoJet1_energy"                 ,recoJet1_energy);
  abis::make_branch(tree_container,"recoJet1_csv"                 ,recoJet1_csv);
  abis::make_branch(tree_container,"recoJet2_pt"                   ,recoJet2_pt);
  abis::make_branch(tree_container,"recoJet2_eta"                  ,recoJet2_eta);
  abis::make_branch(tree_container,"recoJet2_phi"                  ,recoJet2_phi);
  abis::make_branch(tree_container,"recoJet2_energy"                 ,recoJet2_energy);
  abis::make_branch(tree_container,"recoJet2_csv"                 ,recoJet2_csv);

  abis::make_branch(tree_container,"genMu1_pt"                   ,genMu1_pt);
  abis::make_branch(tree_container,"genMu1_eta"                  ,genMu1_eta);
  abis::make_branch(tree_container,"genMu1_phi"                  ,genMu1_phi);
  abis::make_branch(tree_container,"genMu1_energy"                 ,genMu1_energy);
  abis::make_branch(tree_container,"genMu2_pt"                   ,genMu2_pt);
  abis::make_branch(tree_container,"genMu2_eta"                  ,genMu2_eta);
  abis::make_branch(tree_container,"genMu2_phi"                  ,genMu2_phi);
  abis::make_branch(tree_container,"genMu2_energy"                 ,genMu2_energy);
  abis::make_branch(tree_container,"genHiggs_pt"                   ,genHiggs_pt);
  abis::make_branch(tree_container,"genHiggs_eta"                  ,genHiggs_eta);
  abis::make_branch(tree_container,"genHiggs_phi"                  ,genHiggs_phi);
  abis::make_branch(tree_container,"genHiggs_mass"                 ,genHiggs_mass);
  abis::make_branch(tree_container,"genHiggs_helicity"             ,genHiggs_helicity);
  abis::make_branch(tree_container,"recoHiggs_pt"                   ,recoHiggs_pt);
  abis::make_branch(tree_container,"recoHiggs_eta"                  ,recoHiggs_eta);
  abis::make_branch(tree_container,"recoHiggs_phi"                  ,recoHiggs_phi);
  abis::make_branch(tree_container,"recoHiggs_mass"                 ,recoHiggs_mass);
  abis::make_branch(tree_container,"recoHiggs_helicity"             ,recoHiggs_helicity);
  abis::make_branch(tree_container,"genZ_pt"                   ,genZ_pt);
  abis::make_branch(tree_container,"genZ_eta"                  ,genZ_eta);
  abis::make_branch(tree_container,"genZ_phi"                  ,genZ_phi);
  abis::make_branch(tree_container,"genZ_mass"                 ,genZ_mass);
  abis::make_branch(tree_container,"genZ_helicity"                 ,genZ_helicity);
  abis::make_branch(tree_container,"recoZ_pt"                   ,recoZ_pt);
  abis::make_branch(tree_container,"recoZ_eta"                  ,recoZ_eta);
  abis::make_branch(tree_container,"recoZ_phi"                  ,recoZ_phi);
  abis::make_branch(tree_container,"recoZ_mass"                 ,recoZ_mass);
  abis::make_branch(tree_container,"recoZ_helicity"                 ,recoZ_helicity);
  abis::make_branch(tree_container,"genZH_deltaPhi"                  ,genZH_deltaPhi);
  abis::make_branch(tree_container,"recoZH_deltaPhi"                 ,recoZH_deltaPhi);

}

void ZH_channel_genLevel::endJob() {

  std::cout << "Number of myEvents = " << myEvents << std::endl;
  std::cout << "JOB FINISHED" << std::endl;

}

DEFINE_FWK_MODULE(ZH_channel_genLevel);
