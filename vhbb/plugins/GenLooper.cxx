#include <map>
#include <string>
#include <cmath>
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
#include <Math/GenVector/PxPyPzE4D.h>
#include <Math/GenVector/PxPyPzM4D.h>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "TrackingTools/IPTools/interface/IPTools.h"                                    
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
//
// class decleration
//
using namespace reco;
using namespace std;
using namespace edm;

class GenLooper : public edm::EDAnalyzer
{
  
public:
  
  explicit GenLooper(const edm::ParameterSet&);

private:
  
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void beginJob() ;
  virtual void endJob() ;

  //per creare dei TH1 velocemente InputTag.label
  std::map<std::string,TH1D*> histocontainer_;
  std::map<std::string,TH2D*> histocontainer_2;
  std::map<std::string,TH3D*> histocontainer_3;

  edm::InputTag genpLabel_;

  // Member data
  Int_t n_event;  
  Int_t nbs;
  Int_t myEvents;

  bool w_boost;  
};

GenLooper::GenLooper(const edm::ParameterSet& iConfig) : 

  histocontainer_(),
  histocontainer_2(),
  histocontainer_3(),

  genpLabel_(iConfig.getUntrackedParameter<edm::InputTag>("genPart"))

{

  //Initialize counters
  n_event = 0;
  nbs = 0;
  myEvents = 0;

}   

void GenLooper::analyze(const edm::Event& iEvent, const edm::EventSetup& setup)
{
  ++n_event;

  //initialising each events
  nbs = 0;
  w_boost= false;

  std::cout << "*** Analyzing " << iEvent.id() << " n_event = " << n_event << std::endl << std::endl;

  // Generated particles handle
  edm::Handle<edm::View<reco::GenParticle> > genP;
  iEvent.getByLabel(genpLabel_,genP);
  edm::View<reco::GenParticle> genParticles = *genP;

  // Generated particles loop
  for( edm::View<reco::GenParticle>::const_iterator iGenp = genParticles.begin(); 
       iGenp != genParticles.end();
       ++iGenp) 
    {
    
      HepPDT::ParticleID particleID( iGenp->pdgId() );
      
      if( particleID.hasBottom() )
	// number of bs in the events
	nbs++;
      
      if( abs(iGenp->pdgId()) == 24 
	  and iGenp->pt() > 100 )
	w_boost = true;      
      
    }//end genparticles loop
  

  //events with at least two bs and one W with pt > 100GeV
  if(w_boost == true and nbs > 1 )
    myEvents++;

}

void GenLooper::beginJob()
{
  
  using namespace std;  
  edm::Service<TFileService> fs;
  
}

void 
GenLooper::endJob() {

  std::cout << "Correction factor = " << (double)(myEvents)/n_event << std::endl;
  std::cout << "JOB FINISHED" << std::endl;

}

DEFINE_FWK_MODULE(GenLooper);
