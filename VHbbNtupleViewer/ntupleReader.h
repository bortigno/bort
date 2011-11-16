//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov  8 17:03:59 2011 by ROOT version 5.30/02
// from TTree tree/myTree
// found on file: /Users/pier/Physics/VHbbAnalysis/HBB_EDMNtuple/V11/Nov1st/DiJetPt/DiJetPt_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola.root
//////////////////////////////////////////////////////////

#ifndef ntupleReader_h
#define ntupleReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class ntupleReader {
public :

  TTree * tree;
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         H_mass;
   Float_t         H_pt;
   Float_t         H_eta;
   Float_t         H_phi;
   Float_t         H_dR;
   Float_t         H_dPhi;
   Float_t         H_dEta;
   Float_t         V_mass;
   Float_t         V_pt;
   Float_t         V_eta;
   Float_t         V_phi;
   Int_t           nhJets;
   Int_t           naJets;
   Float_t         hJet_pt[2];   //[nhJets]
   Float_t         hJet_eta[2];   //[nhJets]
   Float_t         hJet_phi[2];   //[nhJets]
   Float_t         hJet_e[2];   //[nhJets]
   Float_t         hJet_csv[2];   //[nhJets]
   Float_t         hJet_cosTheta[2];   //[nhJets]
   Int_t           hJet_numTracksSV[2];   //[nhJets]
   Float_t         hJet_chf[2];   //[nhJets]
   Float_t         hJet_nhf[2];   //[nhJets]
   Float_t         hJet_cef[2];   //[nhJets]
   Float_t         hJet_nef[2];   //[nhJets]
   Float_t         hJet_nch[2];   //[nhJets]
   Float_t         hJet_nconstituents[2];   //[nhJets]
   Float_t         hJet_flavour[2];   //[nhJets]
   Float_t         hJet_genPt[2];   //[nhJets]
   Float_t         hJet_genEta[2];   //[nhJets]
   Float_t         hJet_genPhi[2];   //[nhJets]
   Float_t         hJet_JECUnc[2];   //[nhJets]
   Float_t         hJet_vtxMass[2];   //[nhJets]
   Float_t         hJet_vtx3dL[2];   //[nhJets]
   Float_t         hJet_vtx3deL[2];   //[nhJets]
   UChar_t         hJet_id[2];   //[nhJets]
   Float_t         aJet_pt[41];   //[naJets]
   Float_t         aJet_eta[41];   //[naJets]
   Float_t         aJet_phi[41];   //[naJets]
   Float_t         aJet_e[41];   //[naJets]
   Float_t         aJet_csv[41];   //[naJets]
   Float_t         aJet_cosTheta[41];   //[naJets]
   Int_t           aJet_numTracksSV[41];   //[naJets]
   Float_t         aJet_chf[41];   //[naJets]
   Float_t         aJet_nhf[41];   //[naJets]
   Float_t         aJet_cef[41];   //[naJets]
   Float_t         aJet_nef[41];   //[naJets]
   Float_t         aJet_nch[41];   //[naJets]
   Float_t         aJet_nconstituents[41];   //[naJets]
   Float_t         aJet_flavour[41];   //[naJets]
   Float_t         aJet_genPt[41];   //[naJets]
   Float_t         aJet_genEta[41];   //[naJets]
   Float_t         aJet_genPhi[41];   //[naJets]
   Float_t         aJet_JECUnc[41];   //[naJets]
   Float_t         aJet_vtxMass[41];   //[naJets]
   Float_t         aJet_vtx3dL[41];   //[naJets]
   Float_t         aJet_vtx3deL[41];   //[naJets]
   UChar_t         aJet_id[41];   //[naJets]
   Int_t           numJets;
   Int_t           numBJets;
   Float_t         deltaPullAngle;
   Float_t         deltaPullAngle2;
   Float_t         gendrcc;
   Float_t         gendrbb;
   Float_t         genZpt;
   Float_t         genWpt;
   Float_t         weightTrig;
   Float_t         weightTrigMay;
   Float_t         weightTrigV4;
   Float_t         weightTrigMET;
   Float_t         weightTrigOrMu30;
   Float_t         weightEleRecoAndId;
   Float_t         weightEleTrigJetMETPart;
   Float_t         weightEleTrigElePart;
   Float_t         weightEleTrigEleAugPart;
   Float_t         deltaPullAngleAK7;
   Float_t         deltaPullAngle2AK7;
   Float_t         PU0;
   Float_t         PUm1;
   Float_t         PUp1;
   Float_t         PUweight;
   Float_t         PUweight2011B;
   Int_t           eventFlav;
   Int_t           Vtype;
   Float_t         HVdPhi;
   Float_t         HVMass;
   Float_t         HMETdPhi;
   Float_t         VMt;
   Int_t           nvlep;
   Int_t           nalep;
   Float_t         vLepton_mass[2];   //[nvlep]
   Float_t         vLepton_pt[2];   //[nvlep]
   Float_t         vLepton_eta[2];   //[nvlep]
   Float_t         vLepton_phi[2];   //[nvlep]
   Float_t         vLepton_aodCombRelIso[2];   //[nvlep]
   Float_t         vLepton_pfCombRelIso[2];   //[nvlep]
   Float_t         vLepton_photonIso[2];   //[nvlep]
   Float_t         vLepton_neutralHadIso[2];   //[nvlep]
   Float_t         vLepton_chargedHadIso[2];   //[nvlep]
   Float_t         vLepton_chargedPUIso[2];   //[nvlep]
   Float_t         vLepton_particleIso[2];   //[nvlep]
   Float_t         vLepton_dxy[2];   //[nvlep]
   Float_t         vLepton_dz[2];   //[nvlep]
   Int_t           vLepton_type[2];   //[nvlep]
   Float_t         vLepton_id80[2];   //[nvlep]
   Float_t         vLepton_id95[2];   //[nvlep]
   Float_t         vLepton_vbtf[2];   //[nvlep]
   Float_t         aLepton_mass[3];   //[nalep]
   Float_t         aLepton_pt[3];   //[nalep]
   Float_t         aLepton_eta[3];   //[nalep]
   Float_t         aLepton_phi[3];   //[nalep]
   Float_t         aLepton_aodCombRelIso[3];   //[nalep]
   Float_t         aLepton_pfCombRelIso[3];   //[nalep]
   Float_t         aLepton_photonIso[3];   //[nalep]
   Float_t         aLepton_neutralHadIso[3];   //[nalep]
   Float_t         aLepton_chargedHadIso[3];   //[nalep]
   Float_t         aLepton_chargedPUIso[3];   //[nalep]
   Float_t         aLepton_particleIso[3];   //[nalep]
   Float_t         aLepton_dxy[3];   //[nalep]
   Float_t         aLepton_dz[3];   //[nalep]
   Int_t           aLepton_type[3];   //[nalep]
   Float_t         aLepton_id80[3];   //[nalep]
   Float_t         aLepton_id95[3];   //[nalep]
   Float_t         aLepton_vbtf[3];   //[nalep]
   Float_t         top_mass;
   Float_t         top_pt;
   Float_t         top_wMass;
   Int_t           WplusMode;
   Int_t           WminusMode;
   Int_t           nSvs;
   Float_t         Sv_massBCand[4];   //[nSvs]
   Float_t         Sv_massSv[4];   //[nSvs]
   Float_t         Sv_pt[4];   //[nSvs]
   Float_t         Sv_eta[4];   //[nSvs]
   Float_t         Sv_phi[4];   //[nSvs]
   Float_t         Sv_dist3D[4];   //[nSvs]
   Float_t         Sv_dist2D[4];   //[nSvs]
   Float_t         Sv_distSim2D[4];   //[nSvs]
   Float_t         Sv_distSig3D[4];   //[nSvs]
   Float_t         Sv_dist3D_norm[4];   //[nSvs]
   Float_t         SVH_mass;
   Float_t         SVH_pt;
   Float_t         SVH_eta;
   Float_t         SVH_phi;
   Float_t         SVH_dR;
   Float_t         SVH_dPhi;
   Float_t         SVH_dEta;
   Float_t         rho;
   Float_t         rho25;
   Int_t           nPVs;
   Float_t         METnoPU_et;
   Float_t         METnoPU_sumet;
   Float_t         METnoPU_sig;
   Float_t         METnoPU_phi;
   Float_t         METnoPUCh_et;
   Float_t         METnoPUCh_sumet;
   Float_t         METnoPUCh_sig;
   Float_t         METnoPUCh_phi;
   Float_t         MET_et;
   Float_t         MET_sumet;
   Float_t         MET_sig;
   Float_t         MET_phi;
   Float_t         fakeMET_et;
   Float_t         fakeMET_sumet;
   Float_t         fakeMET_sig;
   Float_t         fakeMET_phi;
   Float_t         MHT_mht;
   Float_t         MHT_ht;
   Float_t         MHT_sig;
   Float_t         MHT_phi;
   Float_t         minDeltaPhijetMET;
   Float_t         jetPt_minDeltaPhijetMET;
   UChar_t         triggerFlags[28];
   Int_t           EVENT_run;
   Int_t           EVENT_lumi;
   Int_t           EVENT_event;
   Int_t           EVENT_json;
   UChar_t         hbhe;
   UChar_t         ecalFlag;
   Float_t         btag1TSF;
   Float_t         btag2TSF;
   Float_t         btag1T2CSF;
   Float_t         btag2CSF;
   Float_t         btagA0CSF;
   Float_t         btagA0TSF;
   Float_t         btag1TA1C;

   // List of branches
   TBranch        *b_H;   //!
   TBranch        *b_V;   //!
   TBranch        *b_nhJets;   //!
   TBranch        *b_naJets;   //!
   TBranch        *b_hJet_pt;   //!
   TBranch        *b_hJet_eta;   //!
   TBranch        *b_hJet_phi;   //!
   TBranch        *b_hJet_e;   //!
   TBranch        *b_hJet_csv;   //!
   TBranch        *b_hJet_cosTheta;   //!
   TBranch        *b_hJet_numTracksSV;   //!
   TBranch        *b_hJet_chf;   //!
   TBranch        *b_hJet_nhf;   //!
   TBranch        *b_hJet_cef;   //!
   TBranch        *b_hJet_nef;   //!
   TBranch        *b_hJet_nch;   //!
   TBranch        *b_hJet_nconstituents;   //!
   TBranch        *b_hJet_flavour;   //!
   TBranch        *b_hJet_genPt;   //!
   TBranch        *b_hJet_genEta;   //!
   TBranch        *b_hJet_genPhi;   //!
   TBranch        *b_hJet_JECUnc;   //!
   TBranch        *b_hJet_vtxMass;   //!
   TBranch        *b_hJet_vtx3dL;   //!
   TBranch        *b_hJet_vtx3deL;   //!
   TBranch        *b_hJet_id;   //!
   TBranch        *b_aJet_pt;   //!
   TBranch        *b_aJet_eta;   //!
   TBranch        *b_aJet_phi;   //!
   TBranch        *b_aJet_e;   //!
   TBranch        *b_aJet_csv;   //!
   TBranch        *b_aJet_cosTheta;   //!
   TBranch        *b_aJet_numTracksSV;   //!
   TBranch        *b_aJet_chf;   //!
   TBranch        *b_aJet_nhf;   //!
   TBranch        *b_aJet_cef;   //!
   TBranch        *b_aJet_nef;   //!
   TBranch        *b_aJet_nch;   //!
   TBranch        *b_aJet_nconstituents;   //!
   TBranch        *b_aJet_flavour;   //!
   TBranch        *b_aJet_genPt;   //!
   TBranch        *b_aJet_genEta;   //!
   TBranch        *b_aJet_genPhi;   //!
   TBranch        *b_aJet_JECUnc;   //!
   TBranch        *b_aJet_vtxMass;   //!
   TBranch        *b_aJet_vtx3dL;   //!
   TBranch        *b_aJet_vtx3deL;   //!
   TBranch        *b_aJet_id;   //!
   TBranch        *b_numJets;   //!
   TBranch        *b_numBJets;   //!
   TBranch        *b_deltaPullAngle;   //!
   TBranch        *b_deltaPullAngle2;   //!
   TBranch        *b_gendrcc;   //!
   TBranch        *b_gendrbb;   //!
   TBranch        *b_genZpt;   //!
   TBranch        *b_genWpt;   //!
   TBranch        *b_weightTrig;   //!
   TBranch        *b_weightTrigMay;   //!
   TBranch        *b_weightTrigV4;   //!
   TBranch        *b_weightTrigMET;   //!
   TBranch        *b_weightTrigOrMu30;   //!
   TBranch        *b_weightEleRecoAndId;   //!
   TBranch        *b_weightEleTrigJetMETPart;   //!
   TBranch        *b_weightEleTrigElePart;   //!
   TBranch        *b_weightEleTrigEleAugPart;   //!
   TBranch        *b_deltaPullAngleAK7;   //!
   TBranch        *b_deltaPullAngle2AK7;   //!
   TBranch        *b_PU0;   //!
   TBranch        *b_PUm1;   //!
   TBranch        *b_PUp1;   //!
   TBranch        *b_PUweight;   //!
   TBranch        *b_PUweight2011B;   //!
   TBranch        *b_eventFlav;   //!
   TBranch        *b_Vtype;   //!
   TBranch        *b_HVdPhi;   //!
   TBranch        *b_HVMass;   //!
   TBranch        *b_HMETdPhi;   //!
   TBranch        *b_VMt;   //!
   TBranch        *b_nvlep;   //!
   TBranch        *b_nalep;   //!
   TBranch        *b_vLepton_mass;   //!
   TBranch        *b_vLepton_pt;   //!
   TBranch        *b_vLepton_eta;   //!
   TBranch        *b_vLepton_phi;   //!
   TBranch        *b_vLepton_aodCombRelIso;   //!
   TBranch        *b_vLepton_pfCombRelIso;   //!
   TBranch        *b_vLepton_photonIso;   //!
   TBranch        *b_vLepton_neutralHadIso;   //!
   TBranch        *b_vLepton_chargedHadIso;   //!
   TBranch        *b_vLepton_chargedPUIso;   //!
   TBranch        *b_vLepton_particleIso;   //!
   TBranch        *b_vLepton_dxy;   //!
   TBranch        *b_vLepton_dz;   //!
   TBranch        *b_vLepton_type;   //!
   TBranch        *b_vLepton_id80;   //!
   TBranch        *b_vLepton_id95;   //!
   TBranch        *b_vLepton_vbtf;   //!
   TBranch        *b_aLepton_mass;   //!
   TBranch        *b_aLepton_pt;   //!
   TBranch        *b_aLepton_eta;   //!
   TBranch        *b_aLepton_phi;   //!
   TBranch        *b_aLepton_aodCombRelIso;   //!
   TBranch        *b_aLepton_pfCombRelIso;   //!
   TBranch        *b_aLepton_photonIso;   //!
   TBranch        *b_aLepton_neutralHadIso;   //!
   TBranch        *b_aLepton_chargedHadIso;   //!
   TBranch        *b_aLepton_chargedPUIso;   //!
   TBranch        *b_aLepton_particleIso;   //!
   TBranch        *b_aLepton_dxy;   //!
   TBranch        *b_aLepton_dz;   //!
   TBranch        *b_aLepton_type;   //!
   TBranch        *b_aLepton_id80;   //!
   TBranch        *b_aLepton_id95;   //!
   TBranch        *b_aLepton_vbtf;   //!
   TBranch        *b_top;   //!
   TBranch        *b_WplusMode;   //!
   TBranch        *b_WminusMode;   //!
   TBranch        *b_nSvs;   //!
   TBranch        *b_Sv_massBCand;   //!
   TBranch        *b_Sv_massSv;   //!
   TBranch        *b_Sv_pt;   //!
   TBranch        *b_Sv_eta;   //!
   TBranch        *b_Sv_phi;   //!
   TBranch        *b_Sv_dist3D;   //!
   TBranch        *b_Sv_dist2D;   //!
   TBranch        *b_Sv_distSim2D;   //!
   TBranch        *b_Sv_distSig3D;   //!
   TBranch        *b_Sv_dist3D_norm;   //!
   TBranch        *b_SVH;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_rho25;   //!
   TBranch        *b_nPVs;   //!
   TBranch        *b_METnoPU;   //!
   TBranch        *b_METnoPUCh;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_fakeMET;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_minDeltaPhijetMET;   //!
   TBranch        *b_jetPt_minDeltaPhijetMET;   //!
   TBranch        *b_triggerFlags;   //!
   TBranch        *b_EVENT;   //!
   TBranch        *b_hbhe;   //!
   TBranch        *b_ecalFlag;   //!
   TBranch        *b_btag1TSF;   //!
   TBranch        *b_btag2TSF;   //!
   TBranch        *b_btag1T2CSF;   //!
   TBranch        *b_btag2CSF;   //!
   TBranch        *b_btagA0CSF;   //!
   TBranch        *b_btagA0TSF;   //!
   TBranch        *b_btag1TA1C;   //!

   ntupleReader(const char * infile);
   virtual ~ntupleReader();
   virtual int CountAddJets();
   virtual int CountAddLeptons();
   virtual bool TriggerBit();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

ntupleReader::ntupleReader(const char * infile)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  tree=0;
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(infile);
      if (!f) {
	f = new TFile(infile);
      }
      tree = (TTree*)gDirectory->Get("tree");

   }
   Init(tree);
}

ntupleReader::~ntupleReader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ntupleReader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ntupleReader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ntupleReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("H", &H_mass, &b_H);
   fChain->SetBranchAddress("V", &V_mass, &b_V);
   fChain->SetBranchAddress("nhJets", &nhJets, &b_nhJets);
   fChain->SetBranchAddress("naJets", &naJets, &b_naJets);
   fChain->SetBranchAddress("hJet_pt", hJet_pt, &b_hJet_pt);
   fChain->SetBranchAddress("hJet_eta", hJet_eta, &b_hJet_eta);
   fChain->SetBranchAddress("hJet_phi", hJet_phi, &b_hJet_phi);
   fChain->SetBranchAddress("hJet_e", hJet_e, &b_hJet_e);
   fChain->SetBranchAddress("hJet_csv", hJet_csv, &b_hJet_csv);
   fChain->SetBranchAddress("hJet_cosTheta", hJet_cosTheta, &b_hJet_cosTheta);
   fChain->SetBranchAddress("hJet_numTracksSV", hJet_numTracksSV, &b_hJet_numTracksSV);
   fChain->SetBranchAddress("hJet_chf", hJet_chf, &b_hJet_chf);
   fChain->SetBranchAddress("hJet_nhf", hJet_nhf, &b_hJet_nhf);
   fChain->SetBranchAddress("hJet_cef", hJet_cef, &b_hJet_cef);
   fChain->SetBranchAddress("hJet_nef", hJet_nef, &b_hJet_nef);
   fChain->SetBranchAddress("hJet_nch", hJet_nch, &b_hJet_nch);
   fChain->SetBranchAddress("hJet_nconstituents", hJet_nconstituents, &b_hJet_nconstituents);
   fChain->SetBranchAddress("hJet_flavour", hJet_flavour, &b_hJet_flavour);
   fChain->SetBranchAddress("hJet_genPt", hJet_genPt, &b_hJet_genPt);
   fChain->SetBranchAddress("hJet_genEta", hJet_genEta, &b_hJet_genEta);
   fChain->SetBranchAddress("hJet_genPhi", hJet_genPhi, &b_hJet_genPhi);
   fChain->SetBranchAddress("hJet_JECUnc", hJet_JECUnc, &b_hJet_JECUnc);
   fChain->SetBranchAddress("hJet_vtxMass", hJet_vtxMass, &b_hJet_vtxMass);
   fChain->SetBranchAddress("hJet_vtx3dL", hJet_vtx3dL, &b_hJet_vtx3dL);
   fChain->SetBranchAddress("hJet_vtx3deL", hJet_vtx3deL, &b_hJet_vtx3deL);
   fChain->SetBranchAddress("hJet_id", hJet_id, &b_hJet_id);
   fChain->SetBranchAddress("aJet_pt", aJet_pt, &b_aJet_pt);
   fChain->SetBranchAddress("aJet_eta", aJet_eta, &b_aJet_eta);
   fChain->SetBranchAddress("aJet_phi", aJet_phi, &b_aJet_phi);
   fChain->SetBranchAddress("aJet_e", aJet_e, &b_aJet_e);
   fChain->SetBranchAddress("aJet_csv", aJet_csv, &b_aJet_csv);
   fChain->SetBranchAddress("aJet_cosTheta", aJet_cosTheta, &b_aJet_cosTheta);
   fChain->SetBranchAddress("aJet_numTracksSV", aJet_numTracksSV, &b_aJet_numTracksSV);
   fChain->SetBranchAddress("aJet_chf", aJet_chf, &b_aJet_chf);
   fChain->SetBranchAddress("aJet_nhf", aJet_nhf, &b_aJet_nhf);
   fChain->SetBranchAddress("aJet_cef", aJet_cef, &b_aJet_cef);
   fChain->SetBranchAddress("aJet_nef", aJet_nef, &b_aJet_nef);
   fChain->SetBranchAddress("aJet_nch", aJet_nch, &b_aJet_nch);
   fChain->SetBranchAddress("aJet_nconstituents", aJet_nconstituents, &b_aJet_nconstituents);
   fChain->SetBranchAddress("aJet_flavour", aJet_flavour, &b_aJet_flavour);
   fChain->SetBranchAddress("aJet_genPt", aJet_genPt, &b_aJet_genPt);
   fChain->SetBranchAddress("aJet_genEta", aJet_genEta, &b_aJet_genEta);
   fChain->SetBranchAddress("aJet_genPhi", aJet_genPhi, &b_aJet_genPhi);
   fChain->SetBranchAddress("aJet_JECUnc", aJet_JECUnc, &b_aJet_JECUnc);
   fChain->SetBranchAddress("aJet_vtxMass", aJet_vtxMass, &b_aJet_vtxMass);
   fChain->SetBranchAddress("aJet_vtx3dL", aJet_vtx3dL, &b_aJet_vtx3dL);
   fChain->SetBranchAddress("aJet_vtx3deL", aJet_vtx3deL, &b_aJet_vtx3deL);
   fChain->SetBranchAddress("aJet_id", aJet_id, &b_aJet_id);
   fChain->SetBranchAddress("numJets", &numJets, &b_numJets);
   fChain->SetBranchAddress("numBJets", &numBJets, &b_numBJets);
   fChain->SetBranchAddress("deltaPullAngle", &deltaPullAngle, &b_deltaPullAngle);
   fChain->SetBranchAddress("deltaPullAngle2", &deltaPullAngle2, &b_deltaPullAngle2);
   fChain->SetBranchAddress("gendrcc", &gendrcc, &b_gendrcc);
   fChain->SetBranchAddress("gendrbb", &gendrbb, &b_gendrbb);
   fChain->SetBranchAddress("genZpt", &genZpt, &b_genZpt);
   fChain->SetBranchAddress("genWpt", &genWpt, &b_genWpt);
   fChain->SetBranchAddress("weightTrig", &weightTrig, &b_weightTrig);
   fChain->SetBranchAddress("weightTrigMay", &weightTrigMay, &b_weightTrigMay);
   fChain->SetBranchAddress("weightTrigV4", &weightTrigV4, &b_weightTrigV4);
   fChain->SetBranchAddress("weightTrigMET", &weightTrigMET, &b_weightTrigMET);
   fChain->SetBranchAddress("weightTrigOrMu30", &weightTrigOrMu30, &b_weightTrigOrMu30);
   fChain->SetBranchAddress("weightEleRecoAndId", &weightEleRecoAndId, &b_weightEleRecoAndId);
   fChain->SetBranchAddress("weightEleTrigJetMETPart", &weightEleTrigJetMETPart, &b_weightEleTrigJetMETPart);
   fChain->SetBranchAddress("weightEleTrigElePart", &weightEleTrigElePart, &b_weightEleTrigElePart);
   fChain->SetBranchAddress("weightEleTrigEleAugPart", &weightEleTrigEleAugPart, &b_weightEleTrigEleAugPart);
   fChain->SetBranchAddress("deltaPullAngleAK7", &deltaPullAngleAK7, &b_deltaPullAngleAK7);
   fChain->SetBranchAddress("deltaPullAngle2AK7", &deltaPullAngle2AK7, &b_deltaPullAngle2AK7);
   fChain->SetBranchAddress("PU0", &PU0, &b_PU0);
   fChain->SetBranchAddress("PUm1", &PUm1, &b_PUm1);
   fChain->SetBranchAddress("PUp1", &PUp1, &b_PUp1);
   fChain->SetBranchAddress("PUweight", &PUweight, &b_PUweight);
   fChain->SetBranchAddress("PUweight2011B", &PUweight2011B, &b_PUweight2011B);
   fChain->SetBranchAddress("eventFlav", &eventFlav, &b_eventFlav);
   fChain->SetBranchAddress("Vtype", &Vtype, &b_Vtype);
   fChain->SetBranchAddress("HVdPhi", &HVdPhi, &b_HVdPhi);
   fChain->SetBranchAddress("HVMass", &HVMass, &b_HVMass);
   fChain->SetBranchAddress("HMETdPhi", &HMETdPhi, &b_HMETdPhi);
   fChain->SetBranchAddress("VMt", &VMt, &b_VMt);
   fChain->SetBranchAddress("nvlep", &nvlep, &b_nvlep);
   fChain->SetBranchAddress("nalep", &nalep, &b_nalep);
   fChain->SetBranchAddress("vLepton_mass", vLepton_mass, &b_vLepton_mass);
   fChain->SetBranchAddress("vLepton_pt", vLepton_pt, &b_vLepton_pt);
   fChain->SetBranchAddress("vLepton_eta", vLepton_eta, &b_vLepton_eta);
   fChain->SetBranchAddress("vLepton_phi", vLepton_phi, &b_vLepton_phi);
   fChain->SetBranchAddress("vLepton_aodCombRelIso", vLepton_aodCombRelIso, &b_vLepton_aodCombRelIso);
   fChain->SetBranchAddress("vLepton_pfCombRelIso", vLepton_pfCombRelIso, &b_vLepton_pfCombRelIso);
   fChain->SetBranchAddress("vLepton_photonIso", vLepton_photonIso, &b_vLepton_photonIso);
   fChain->SetBranchAddress("vLepton_neutralHadIso", vLepton_neutralHadIso, &b_vLepton_neutralHadIso);
   fChain->SetBranchAddress("vLepton_chargedHadIso", vLepton_chargedHadIso, &b_vLepton_chargedHadIso);
   fChain->SetBranchAddress("vLepton_chargedPUIso", vLepton_chargedPUIso, &b_vLepton_chargedPUIso);
   fChain->SetBranchAddress("vLepton_particleIso", vLepton_particleIso, &b_vLepton_particleIso);
   fChain->SetBranchAddress("vLepton_dxy", vLepton_dxy, &b_vLepton_dxy);
   fChain->SetBranchAddress("vLepton_dz", vLepton_dz, &b_vLepton_dz);
   fChain->SetBranchAddress("vLepton_type", vLepton_type, &b_vLepton_type);
   fChain->SetBranchAddress("vLepton_id80", vLepton_id80, &b_vLepton_id80);
   fChain->SetBranchAddress("vLepton_id95", vLepton_id95, &b_vLepton_id95);
   fChain->SetBranchAddress("vLepton_vbtf", vLepton_vbtf, &b_vLepton_vbtf);
   fChain->SetBranchAddress("aLepton_mass", aLepton_mass, &b_aLepton_mass);
   fChain->SetBranchAddress("aLepton_pt", aLepton_pt, &b_aLepton_pt);
   fChain->SetBranchAddress("aLepton_eta", aLepton_eta, &b_aLepton_eta);
   fChain->SetBranchAddress("aLepton_phi", aLepton_phi, &b_aLepton_phi);
   fChain->SetBranchAddress("aLepton_aodCombRelIso", aLepton_aodCombRelIso, &b_aLepton_aodCombRelIso);
   fChain->SetBranchAddress("aLepton_pfCombRelIso", aLepton_pfCombRelIso, &b_aLepton_pfCombRelIso);
   fChain->SetBranchAddress("aLepton_photonIso", aLepton_photonIso, &b_aLepton_photonIso);
   fChain->SetBranchAddress("aLepton_neutralHadIso", aLepton_neutralHadIso, &b_aLepton_neutralHadIso);
   fChain->SetBranchAddress("aLepton_chargedHadIso", aLepton_chargedHadIso, &b_aLepton_chargedHadIso);
   fChain->SetBranchAddress("aLepton_chargedPUIso", aLepton_chargedPUIso, &b_aLepton_chargedPUIso);
   fChain->SetBranchAddress("aLepton_particleIso", aLepton_particleIso, &b_aLepton_particleIso);
   fChain->SetBranchAddress("aLepton_dxy", aLepton_dxy, &b_aLepton_dxy);
   fChain->SetBranchAddress("aLepton_dz", aLepton_dz, &b_aLepton_dz);
   fChain->SetBranchAddress("aLepton_type", aLepton_type, &b_aLepton_type);
   fChain->SetBranchAddress("aLepton_id80", aLepton_id80, &b_aLepton_id80);
   fChain->SetBranchAddress("aLepton_id95", aLepton_id95, &b_aLepton_id95);
   fChain->SetBranchAddress("aLepton_vbtf", aLepton_vbtf, &b_aLepton_vbtf);
   fChain->SetBranchAddress("top", &top_mass, &b_top);
   fChain->SetBranchAddress("WplusMode", &WplusMode, &b_WplusMode);
   fChain->SetBranchAddress("WminusMode", &WminusMode, &b_WminusMode);
   fChain->SetBranchAddress("nSvs", &nSvs, &b_nSvs);
   fChain->SetBranchAddress("Sv_massBCand", Sv_massBCand, &b_Sv_massBCand);
   fChain->SetBranchAddress("Sv_massSv", Sv_massSv, &b_Sv_massSv);
   fChain->SetBranchAddress("Sv_pt", Sv_pt, &b_Sv_pt);
   fChain->SetBranchAddress("Sv_eta", Sv_eta, &b_Sv_eta);
   fChain->SetBranchAddress("Sv_phi", Sv_phi, &b_Sv_phi);
   fChain->SetBranchAddress("Sv_dist3D", Sv_dist3D, &b_Sv_dist3D);
   fChain->SetBranchAddress("Sv_dist2D", Sv_dist2D, &b_Sv_dist2D);
   fChain->SetBranchAddress("Sv_distSim2D", Sv_distSim2D, &b_Sv_distSim2D);
   fChain->SetBranchAddress("Sv_distSig3D", Sv_distSig3D, &b_Sv_distSig3D);
   fChain->SetBranchAddress("Sv_dist3D_norm", Sv_dist3D_norm, &b_Sv_dist3D_norm);
   fChain->SetBranchAddress("SVH", &SVH_mass, &b_SVH);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("rho25", &rho25, &b_rho25);
   fChain->SetBranchAddress("nPVs", &nPVs, &b_nPVs);
   fChain->SetBranchAddress("METnoPU", &METnoPU_et, &b_METnoPU);
   fChain->SetBranchAddress("METnoPUCh", &METnoPUCh_et, &b_METnoPUCh);
   fChain->SetBranchAddress("MET", &MET_et, &b_MET);
   fChain->SetBranchAddress("fakeMET", &fakeMET_et, &b_fakeMET);
   fChain->SetBranchAddress("MHT", &MHT_mht, &b_MHT);
   fChain->SetBranchAddress("minDeltaPhijetMET", &minDeltaPhijetMET, &b_minDeltaPhijetMET);
   fChain->SetBranchAddress("jetPt_minDeltaPhijetMET", &jetPt_minDeltaPhijetMET, &b_jetPt_minDeltaPhijetMET);
   fChain->SetBranchAddress("triggerFlags", triggerFlags, &b_triggerFlags);
   fChain->SetBranchAddress("EVENT", &EVENT_run, &b_EVENT);
   fChain->SetBranchAddress("hbhe", &hbhe, &b_hbhe);
   fChain->SetBranchAddress("ecalFlag", &ecalFlag, &b_ecalFlag);
   fChain->SetBranchAddress("btag1TSF", &btag1TSF, &b_btag1TSF);
   fChain->SetBranchAddress("btag2TSF", &btag2TSF, &b_btag2TSF);
   fChain->SetBranchAddress("btag1T2CSF", &btag1T2CSF, &b_btag1T2CSF);
   fChain->SetBranchAddress("btag2CSF", &btag2CSF, &b_btag2CSF);
   fChain->SetBranchAddress("btagA0CSF", &btagA0CSF, &b_btagA0CSF);
   fChain->SetBranchAddress("btagA0TSF", &btagA0TSF, &b_btagA0TSF);
   fChain->SetBranchAddress("btag1TA1C", &btag1TA1C, &b_btag1TA1C);
   Notify();
}

Bool_t ntupleReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ntupleReader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ntupleReader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
int ntupleReader::CountAddJets(){
  int sum=0;
  for(int i=0; i<naJets; ++i)
    if( aJet_pt[i] > 20.
	&& TMath::Abs(aJet_eta[i]) < 2.4 )
      sum++;
  return sum;
}
int ntupleReader::CountAddLeptons(){
  int sum=0;
  for(int i=0; i<nalep; ++i)
    if( aLepton_pt[i] > 15.
	&& aLepton_pfCombRelIso[i] < 0.15 )
      sum++;
  return sum;
}
bool ntupleReader::TriggerBit()
{
  if(  triggerFlags[5] 
       || triggerFlags[6] )
   return false;
  else
    return true;
}
void ntupleReader::Loop()
{
  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
#endif // #ifdef ntupleReader_cxx
