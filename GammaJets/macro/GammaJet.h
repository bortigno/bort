//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Apr 23 21:31:37 2011 by ROOT version 5.22/00d
// from TTree GammaJet/GammaJet
// found on file: GammaJets40_100/res/GammaJet40-100.root
//////////////////////////////////////////////////////////

#ifndef GammaJet_h
#define GammaJet_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class GammaJet {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   TTree *tree;

   // Declaration of leaf types
   Double_t        leading_gluonHelicity;
   Double_t        jetPtAsymmetry;
   Double_t        AK7leadingDeltaTheta;
   Double_t        AK7secondLeadingDeltaTheta;
   Double_t        leadingDeltaTheta;
   Double_t        secondLeadingDeltaTheta;
   Double_t        iDeltaTheta;
   Double_t        jetDeltaR;
   Double_t        photonCandidate_mass;
   Double_t        gluonCandidate_mass;
   Double_t        photonCandidate_pt;
   Double_t        gluonCandidate_pt;
   Double_t        leadingBTag;
   Double_t        secondLeadingBTag;
   Bool_t          jetVeto;
   Int_t           nOfak5;

   // List of branches
   TBranch        *b_leading_gluonHelicity;   //!
   TBranch        *b_jetPtAsymmetry;   //!
   TBranch        *b_AK7leadingDeltaTheta;   //!
   TBranch        *b_AK7secondLeadingDeltaTheta;   //!
   TBranch        *b_leadingDeltaTheta;   //!
   TBranch        *b_secondLeadingDeltaTheta;   //!
   TBranch        *b_iDeltaTheta;   //!
   TBranch        *b_jetDeltaR;   //!
   TBranch        *b_photonCandidate_mass;   //!
   TBranch        *b_gluonCandidate_mass;   //!
   TBranch        *b_photonCandidate_pt;   //!
   TBranch        *b_gluonCandidate_pt;   //!
   TBranch        *b_leadingBTag;   //!
   TBranch        *b_secondLeadingBTag;   //!
   TBranch        *b_jetVeto;   //!
   TBranch        *b_nOfak5;   //!

   GammaJet(char* filein);
   virtual ~GammaJet();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef GammaJet_cxx
GammaJet::GammaJet(char* filein)
{
  tree = 0;
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filein);
      if (!f) {
         f = new TFile(filein);
	 // f->cd("GammaJets40_100/res/GammaJet40-100.root:/GammaJet");
      }
      tree = (TTree*)gDirectory->Get("GammaJet/GammaJet");

   }
   Init(tree);
}

GammaJet::~GammaJet()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t GammaJet::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GammaJet::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void GammaJet::Init(TTree *tree)
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

   fChain->SetBranchAddress("leading_gluonHelicity", &leading_gluonHelicity, &b_leading_gluonHelicity);
   fChain->SetBranchAddress("jetPtAsymmetry", &jetPtAsymmetry, &b_jetPtAsymmetry);
   fChain->SetBranchAddress("AK7leadingDeltaTheta", &AK7leadingDeltaTheta, &b_AK7leadingDeltaTheta);
   fChain->SetBranchAddress("AK7secondLeadingDeltaTheta", &AK7secondLeadingDeltaTheta, &b_AK7secondLeadingDeltaTheta);
   fChain->SetBranchAddress("leadingDeltaTheta", &leadingDeltaTheta, &b_leadingDeltaTheta);
   fChain->SetBranchAddress("secondLeadingDeltaTheta", &secondLeadingDeltaTheta, &b_secondLeadingDeltaTheta);
   fChain->SetBranchAddress("iDeltaTheta", &iDeltaTheta, &b_iDeltaTheta);
   fChain->SetBranchAddress("jetDeltaR", &jetDeltaR, &b_jetDeltaR);
   fChain->SetBranchAddress("photonCandidate_mass", &photonCandidate_mass, &b_photonCandidate_mass);
   fChain->SetBranchAddress("gluonCandidate_mass", &gluonCandidate_mass, &b_gluonCandidate_mass);
   fChain->SetBranchAddress("photonCandidate_pt", &photonCandidate_pt, &b_photonCandidate_pt);
   fChain->SetBranchAddress("gluonCandidate_pt", &gluonCandidate_pt, &b_gluonCandidate_pt);
   fChain->SetBranchAddress("leadingBTag", &leadingBTag, &b_leadingBTag);
   fChain->SetBranchAddress("secondLeadingBTag", &secondLeadingBTag, &b_secondLeadingBTag);
   fChain->SetBranchAddress("jetVeto", &jetVeto, &b_jetVeto);
   fChain->SetBranchAddress("nOfak5", &nOfak5, &b_nOfak5);
   Notify();
}

Bool_t GammaJet::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GammaJet::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GammaJet::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef GammaJet_cxx
