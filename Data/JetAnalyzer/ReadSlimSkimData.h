//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May  1 18:27:31 2019 by ROOT version 6.14/06
// from TTree mixing_tree/
// found on file: PbPb_5TeV_Data.root
//////////////////////////////////////////////////////////

#ifndef ReadSlimSkimData_h
#define ReadSlimSkimData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class ReadSlimSkimData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   ULong64_t       evt;
   UInt_t          lumi;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Int_t           hiBin;
   
   Int_t           HLT_HIPuAK4CaloJet80Eta5p1_v1;
   Int_t           HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet100Eta5p1_v1;
   Int_t           HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl;
   Int_t           HLT_HIPuAK4CaloJet120Eta5p1_v1;
   Int_t           HLT_HIPuAK4CaloJet120Eta5p1_v1_Prescl;
   Int_t           HLT_HIL3Mu12_v1;
   Int_t           HLT_HIL3Mu12_v1_Prescl;
   Int_t           HLT_HIL3Mu15_v1;
   Int_t           HLT_HIL3Mu15_v1_Prescl;
   Int_t           HLT_HIL3Mu20_v1;
   Int_t           HLT_HIL3Mu20_v1_Prescl;

   Int_t           HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1;
   Int_t           HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl;
   Int_t           HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1;
   Int_t           HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl;
   Int_t           HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1;
   Int_t           HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl;
   Int_t           HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1;
   Int_t           HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl;

   Int_t           pBeamScrapingFilter;
   Int_t           collisionEventSelectionAOD;
   Int_t           collisionEventSelectionAODv2;
   Int_t           pVertexFilterCutGloose;
   Int_t           pVertexFilterCutGtight;
   Int_t           pVertexFilterCutGplus;
   Int_t           pVertexFilterCutE;
   Int_t           pVertexFilterCutEandG;
   Int_t           pHBHENoiseFilterResultProducer;
   Int_t           HBHENoiseFilterResult;
   Int_t           HBHENoiseFilterResultRun1;
   Int_t           HBHENoiseFilterResultRun2Loose;
   Int_t           HBHENoiseFilterResultRun2Tight;
   Int_t           HBHEIsoNoiseFilterResult;
   Int_t           superFilterPath;
   
   vector<float>   *pf_jteta;
   vector<float>   *pf_jtphi;
   vector<float>   *pf_jtpt;
   vector<float>   *pf_rawpt;
   vector<float>   *pf_corrpt;
   vector<float>   *pf_trackMax;
   vector<float>   *pf_discr_ssvHighEff;
   vector<float>   *pf_discr_ssvHighPur;
   vector<float>   *pf_discr_csvV1;
   vector<float>   *pf_discr_csvV2;
   vector<float>   *pf_discr_prob;
   vector<float>   *pf_svtxm;
   vector<float>   *pf_svtxpt;
   vector<float>   *pf_svtxmcorr;
   vector<float>   *pf_svtxdl;
   vector<float>   *pf_svtxdls;
   vector<float>   *calo_jteta;
   vector<float>   *calo_jtphi;
   vector<float>   *calo_jtpt;
   vector<float>   *calo_rawpt;
   vector<float>   *calo_corrpt;
   vector<float>   *calo_trackMax;
   vector<float>   *calo_discr_ssvHighEff;
   vector<float>   *calo_discr_ssvHighPur;
   vector<float>   *calo_discr_csvV1;
   vector<float>   *calo_discr_csvV2;
   vector<float>   *calo_discr_prob;
   vector<float>   *calo_svtxm;
   vector<float>   *calo_svtxpt;
   vector<float>   *calo_svtxmcorr;
   vector<float>   *calo_svtxdl;
   vector<float>   *calo_svtxdls;

  vector<float>   *trkPt;
  vector<float>   *trkEta;
  vector<float>   *trkPhi;
  vector<float>   *trkPtError;
  vector<int>     *trkpfType;


  vector<float>   *mu_pt;
   vector<float>   *mu_phi;
   vector<float>   *mu_eta;
   vector<int>     *mu_chg;
   vector<int>     *mu_type;
   vector<int>     *mu_isGlobal;
   vector<int>     *mu_isTracker;
   vector<int>     *mu_isPF;
   vector<int>     *mu_isSTA;
   vector<float>   *mu_D0;
   vector<float>   *mu_Dz;
   vector<float>   *mu_chi2ndf;
   vector<float>   *mu_innerD0;
   vector<float>   *mu_innerDz;
   vector<float>   *mu_innerD0Err;
   vector<float>   *mu_innerDzErr;
   vector<float>   *mu_innerPt;
   vector<float>   *mu_innerPtError;
   vector<float>   *mu_innerEta;
   //vector<float>   *mu_innerHighPurity;
   vector<int>     *mu_isGood;
   vector<int>     *mu_trkLayers;
   vector<int>     *mu_pixelLayers;
   vector<int>     *mu_pixelHits;
   vector<int>     *mu_muonHits;
   vector<int>     *mu_trkQuality;
   vector<int>     *mu_stations;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_evt;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_hiBin;   //!
   
   TBranch        *b_HLT_HIPuAK4CaloJet80Eta5p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100Eta5p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet120Eta5p1_v1;   //!
   TBranch        *b_HLT_HIPuAK4CaloJet120Eta5p1_v1_Prescl;   //!
   
   TBranch        *b_HLT_HIL3Mu12_v1;   //!
   TBranch        *b_HLT_HIL3Mu12_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu15_v1;   //!
   TBranch        *b_HLT_HIL3Mu15_v1_Prescl;   //!
   TBranch        *b_HLT_HIL3Mu20_v1;   //!
   TBranch        *b_HLT_HIL3Mu20_v1_Prescl;   //!

   TBranch        *b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1;   //!
   TBranch        *b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl;   //!
   
   TBranch        *b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1;   //!
   TBranch        *b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl;   //!
   
   TBranch        *b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1;   //!
   TBranch        *b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl;   //!
   
   TBranch        *b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1;   //!
   TBranch        *b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl;   //!
   
   
   TBranch        *b_pBeamScrapingFilter;   //!
   TBranch        *b_collisionEventSelectionAOD;   //!
   TBranch        *b_collisionEventSelectionAODv2;   //!
   TBranch        *b_pVertexFilterCutGloose;   //!
   TBranch        *b_pVertexFilterCutGtight;   //!
   TBranch        *b_pVertexFilterCutGplus;   //!
   TBranch        *b_pVertexFilterCutE;   //!
   TBranch        *b_pVertexFilterCutEandG;   //!
   TBranch        *b_pHBHENoiseFilterResultProducer;   //!
   TBranch        *b_HBHENoiseFilterResult;   //!
   TBranch        *b_HBHENoiseFilterResultRun1;   //!
   TBranch        *b_HBHENoiseFilterResultRun2Loose;   //!
   TBranch        *b_HBHENoiseFilterResultRun2Tight;   //!
   TBranch        *b_HBHEIsoNoiseFilterResult;   //!
   TBranch        *b_superFilterPath;   //!
   TBranch        *b_pf_jteta;   //!
   TBranch        *b_pf_jtphi;   //!
   TBranch        *b_pf_jtpt;   //!
   TBranch        *b_pf_rawpt;   //!
   TBranch        *b_pf_corrpt;   //!
   TBranch        *b_pf_trackMax;   //!
   TBranch        *b_pf_discr_ssvHighEff;   //!
   TBranch        *b_pf_discr_ssvHighPur;   //!
   TBranch        *b_pf_discr_csvV1;   //!
   TBranch        *b_pf_discr_csvV2;   //!
   TBranch        *b_pf_discr_prob;   //!
   TBranch        *b_pf_svtxm;   //!
   TBranch        *b_pf_svtxpt;   //!
   TBranch        *b_pf_svtxmcorr;   //!
   TBranch        *b_pf_svtxdl;   //!
   TBranch        *b_pf_svtxdls;   //!
   TBranch        *b_calo_jteta;   //!
   TBranch        *b_calo_jtphi;   //!
   TBranch        *b_calo_jtpt;   //!
   TBranch        *b_calo_rawpt;   //!
   TBranch        *b_calo_corrpt;   //!
   TBranch        *b_calo_trackMax;   //!
   TBranch        *b_calo_discr_ssvHighEff;   //!
   TBranch        *b_calo_discr_ssvHighPur;   //!
   TBranch        *b_calo_discr_csvV1;   //!
   TBranch        *b_calo_discr_csvV2;   //!
   TBranch        *b_calo_discr_prob;   //!
   TBranch        *b_calo_svtxm;   //!
   TBranch        *b_calo_svtxpt;   //!
   TBranch        *b_calo_svtxmcorr;   //!
   TBranch        *b_calo_svtxdl;   //!
   TBranch        *b_calo_svtxdls;   //!
   TBranch        *b_trkPt;   //!
   TBranch        *b_trkEta;   //!
   TBranch        *b_trkPhi;   //!
  TBranch        *b_trkPtError;   //!
  TBranch        *b_trkpfType;

  TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_chg;   //!
   TBranch        *b_mu_type;   //!
   TBranch        *b_mu_isGlobal;   //!
   TBranch        *b_mu_isTracker;   //!
   TBranch        *b_mu_isPF;   //!
   TBranch        *b_mu_isSTA;   //!
   TBranch        *b_mu_D0;   //!
   TBranch        *b_mu_Dz;   //!
   TBranch        *b_mu_chi2ndf;   //!
   TBranch        *b_mu_innerD0;   //!
   TBranch        *b_mu_innerDz;   //!
   TBranch        *b_mu_innerD0Err;   //!
   TBranch        *b_mu_innerDzErr;   //!
   TBranch        *b_mu_innerPt;   //!
   TBranch        *b_mu_innerPtError;   //!
   TBranch        *b_mu_innerEta;   //!
   //TBranch        *b_mu_innerHighPurity;   //!
   TBranch        *b_mu_isGood;   //!
   TBranch        *b_mu_trkLayers;   //!
   TBranch        *b_mu_pixelLayers;   //!
   TBranch        *b_mu_pixelHits;   //!
   TBranch        *b_mu_muonHits;   //!
   TBranch        *b_mu_trkQuality;   //!
   TBranch        *b_mu_stations;   //!

   ReadSlimSkimData(TTree *tree=0);
   virtual ~ReadSlimSkimData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ReadSlimSkimData_cxx
/*
ReadSlimSkimData::ReadSlimSkimData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("PbPb_5TeV_Data.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("PbPb_5TeV_Data.root");
      }
      f->GetObject("mixing_tree",tree);

   }
   Init(tree);
}
*/

ReadSlimSkimData::~ReadSlimSkimData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ReadSlimSkimData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ReadSlimSkimData::LoadTree(Long64_t entry)
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

void ReadSlimSkimData::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer (only for vector branches)
   pf_jteta = 0;
   pf_jtphi = 0;
   pf_jtpt = 0;
   pf_rawpt = 0;
   pf_corrpt = 0;
   pf_trackMax = 0;
   pf_discr_ssvHighEff = 0;
   pf_discr_ssvHighPur = 0;
   pf_discr_csvV1 = 0;
   pf_discr_csvV2 = 0;
   pf_discr_prob = 0;
   pf_svtxm = 0;
   pf_svtxpt = 0;
   pf_svtxmcorr = 0;
   pf_svtxdl = 0;
   pf_svtxdls = 0;
   calo_jteta = 0;
   calo_jtphi = 0;
   calo_jtpt = 0;
   calo_rawpt = 0;
   calo_corrpt = 0;
   calo_trackMax = 0;
   calo_discr_ssvHighEff = 0;
   calo_discr_ssvHighPur = 0;
   calo_discr_csvV1 = 0;
   calo_discr_csvV2 = 0;
   calo_discr_prob = 0;
   calo_svtxm = 0;
   calo_svtxpt = 0;
   calo_svtxmcorr = 0;
   calo_svtxdl = 0;
   calo_svtxdls = 0;
   trkPt = 0;
   trkEta = 0;
   trkPhi = 0;
   trkPtError = 0;
   trkpfType=0;

   mu_pt = 0;
   mu_phi = 0;
   mu_eta = 0;
   mu_chg = 0;
   mu_type = 0;
   mu_isGlobal = 0;
   mu_isTracker = 0;
   mu_isPF = 0;
   mu_isSTA = 0;
   mu_D0 = 0;
   mu_Dz = 0;
   mu_chi2ndf = 0;
   mu_innerD0 = 0;
   mu_innerDz = 0;
   mu_innerD0Err = 0;
   mu_innerDzErr = 0;
   mu_innerPt = 0;
   mu_innerPtError = 0;
   mu_innerEta = 0;
   //mu_innerHighPurity = 0;
   mu_isGood = 0;
   mu_trkLayers = 0;
   mu_pixelLayers = 0;
   mu_pixelHits = 0;
   mu_muonHits = 0;
   mu_trkQuality = 0;
   mu_stations = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("vx", &vx, &b_vx);
   fChain->SetBranchAddress("vy", &vy, &b_vy);
   fChain->SetBranchAddress("vz", &vz, &b_vz);
   fChain->SetBranchAddress("hiBin", &hiBin, &b_hiBin);
   
   // Jet Triggers
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80Eta5p1_v1", &HLT_HIPuAK4CaloJet80Eta5p1_v1, &b_HLT_HIPuAK4CaloJet80Eta5p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl", &HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100Eta5p1_v1", &HLT_HIPuAK4CaloJet100Eta5p1_v1, &b_HLT_HIPuAK4CaloJet100Eta5p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl", &HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet120Eta5p1_v1", &HLT_HIPuAK4CaloJet120Eta5p1_v1, &b_HLT_HIPuAK4CaloJet120Eta5p1_v1);
   fChain->SetBranchAddress("HLT_HIPuAK4CaloJet120Eta5p1_v1_Prescl", &HLT_HIPuAK4CaloJet120Eta5p1_v1_Prescl, &b_HLT_HIPuAK4CaloJet120Eta5p1_v1_Prescl);
   // Muon Triggers
   fChain->SetBranchAddress("HLT_HIL3Mu12_v1", &HLT_HIL3Mu12_v1, &b_HLT_HIL3Mu12_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu12_v1_Prescl", &HLT_HIL3Mu12_v1_Prescl, &b_HLT_HIL3Mu12_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu15_v1", &HLT_HIL3Mu15_v1, &b_HLT_HIL3Mu15_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu15_v1_Prescl", &HLT_HIL3Mu15_v1_Prescl, &b_HLT_HIL3Mu15_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu20_v1", &HLT_HIL3Mu20_v1, &b_HLT_HIL3Mu20_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu20_v1_Prescl", &HLT_HIL3Mu20_v1_Prescl, &b_HLT_HIL3Mu20_v1_Prescl);
   
   //Muon+Jet Cross-Triggers
   fChain->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1", &HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1, &b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl", & HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl, &b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1", &HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1, &b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl", &HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl, &b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1", &HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1, &b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl", &HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl, &b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl);
   fChain->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1", &HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1, &b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1);
   fChain->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl", &HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl, &b_HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl);

   fChain->SetBranchAddress("pBeamScrapingFilter", &pBeamScrapingFilter, &b_pBeamScrapingFilter);
   fChain->SetBranchAddress("collisionEventSelectionAOD", &collisionEventSelectionAOD, &b_collisionEventSelectionAOD);
   fChain->SetBranchAddress("collisionEventSelectionAODv2", &collisionEventSelectionAODv2, &b_collisionEventSelectionAODv2);
   fChain->SetBranchAddress("pVertexFilterCutGloose", &pVertexFilterCutGloose, &b_pVertexFilterCutGloose);
   fChain->SetBranchAddress("pVertexFilterCutGtight", &pVertexFilterCutGtight, &b_pVertexFilterCutGtight);
   fChain->SetBranchAddress("pVertexFilterCutGplus", &pVertexFilterCutGplus, &b_pVertexFilterCutGplus);
   fChain->SetBranchAddress("pVertexFilterCutE", &pVertexFilterCutE, &b_pVertexFilterCutE);
   fChain->SetBranchAddress("pVertexFilterCutEandG", &pVertexFilterCutEandG, &b_pVertexFilterCutEandG);
   fChain->SetBranchAddress("pHBHENoiseFilterResultProducer", &pHBHENoiseFilterResultProducer, &b_pHBHENoiseFilterResultProducer);
   fChain->SetBranchAddress("HBHENoiseFilterResult", &HBHENoiseFilterResult, &b_HBHENoiseFilterResult);
   fChain->SetBranchAddress("HBHENoiseFilterResultRun1", &HBHENoiseFilterResultRun1, &b_HBHENoiseFilterResultRun1);
   fChain->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseFilterResultRun2Loose, &b_HBHENoiseFilterResultRun2Loose);
   fChain->SetBranchAddress("HBHENoiseFilterResultRun2Tight", &HBHENoiseFilterResultRun2Tight, &b_HBHENoiseFilterResultRun2Tight);
   fChain->SetBranchAddress("HBHEIsoNoiseFilterResult", &HBHEIsoNoiseFilterResult, &b_HBHEIsoNoiseFilterResult);
   fChain->SetBranchAddress("superFilterPath", &superFilterPath, &b_superFilterPath);
   fChain->SetBranchAddress("pf_jteta", &pf_jteta, &b_pf_jteta);
   fChain->SetBranchAddress("pf_jtphi", &pf_jtphi, &b_pf_jtphi);
   fChain->SetBranchAddress("pf_jtpt", &pf_jtpt, &b_pf_jtpt);
   fChain->SetBranchAddress("pf_rawpt", &pf_rawpt, &b_pf_rawpt);
   fChain->SetBranchAddress("pf_corrpt", &pf_corrpt, &b_pf_corrpt);
   fChain->SetBranchAddress("pf_trackMax", &pf_trackMax, &b_pf_trackMax);
   fChain->SetBranchAddress("pf_discr_ssvHighEff", &pf_discr_ssvHighEff, &b_pf_discr_ssvHighEff);
   fChain->SetBranchAddress("pf_discr_ssvHighPur", &pf_discr_ssvHighPur, &b_pf_discr_ssvHighPur);
   fChain->SetBranchAddress("pf_discr_csvV1", &pf_discr_csvV1, &b_pf_discr_csvV1);
   fChain->SetBranchAddress("pf_discr_csvV2", &pf_discr_csvV2, &b_pf_discr_csvV2);
   fChain->SetBranchAddress("pf_discr_prob", &pf_discr_prob, &b_pf_discr_prob);
   fChain->SetBranchAddress("pf_svtxm", &pf_svtxm, &b_pf_svtxm);
   fChain->SetBranchAddress("pf_svtxpt", &pf_svtxpt, &b_pf_svtxpt);
   fChain->SetBranchAddress("pf_svtxmcorr", &pf_svtxmcorr, &b_pf_svtxmcorr);
   fChain->SetBranchAddress("pf_svtxdl", &pf_svtxdl, &b_pf_svtxdl);
   fChain->SetBranchAddress("pf_svtxdls", &pf_svtxdls, &b_pf_svtxdls);
   fChain->SetBranchAddress("calo_jteta", &calo_jteta, &b_calo_jteta);
   fChain->SetBranchAddress("calo_jtphi", &calo_jtphi, &b_calo_jtphi);
   fChain->SetBranchAddress("calo_jtpt", &calo_jtpt, &b_calo_jtpt);
   fChain->SetBranchAddress("calo_rawpt", &calo_rawpt, &b_calo_rawpt);
   fChain->SetBranchAddress("calo_corrpt", &calo_corrpt, &b_calo_corrpt);
   fChain->SetBranchAddress("calo_trackMax", &calo_trackMax, &b_calo_trackMax);
   fChain->SetBranchAddress("calo_discr_ssvHighEff", &calo_discr_ssvHighEff, &b_calo_discr_ssvHighEff);
   fChain->SetBranchAddress("calo_discr_ssvHighPur", &calo_discr_ssvHighPur, &b_calo_discr_ssvHighPur);
   fChain->SetBranchAddress("calo_discr_csvV1", &calo_discr_csvV1, &b_calo_discr_csvV1);
   fChain->SetBranchAddress("calo_discr_csvV2", &calo_discr_csvV2, &b_calo_discr_csvV2);
   fChain->SetBranchAddress("calo_discr_prob", &calo_discr_prob, &b_calo_discr_prob);
   fChain->SetBranchAddress("calo_svtxm", &calo_svtxm, &b_calo_svtxm);
   fChain->SetBranchAddress("calo_svtxpt", &calo_svtxpt, &b_calo_svtxpt);
   fChain->SetBranchAddress("calo_svtxmcorr", &calo_svtxmcorr, &b_calo_svtxmcorr);
   fChain->SetBranchAddress("calo_svtxdl", &calo_svtxdl, &b_calo_svtxdl);
   fChain->SetBranchAddress("calo_svtxdls", &calo_svtxdls, &b_calo_svtxdls);
   fChain->SetBranchAddress("trkPt", &trkPt, &b_trkPt);
   fChain->SetBranchAddress("trkEta", &trkEta, &b_trkEta);
   fChain->SetBranchAddress("trkPhi", &trkPhi, &b_trkPhi);
   fChain->SetBranchAddress("trkPtError", &trkPtError, &b_trkPtError);
   fChain->SetBranchAddress("trkpfType", &trkpfType, &b_trkpfType);

   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_chg", &mu_chg, &b_mu_chg);
   fChain->SetBranchAddress("mu_type", &mu_type, &b_mu_type);
   fChain->SetBranchAddress("mu_isGlobal", &mu_isGlobal, &b_mu_isGlobal);
   fChain->SetBranchAddress("mu_isTracker", &mu_isTracker, &b_mu_isTracker);
   fChain->SetBranchAddress("mu_isPF", &mu_isPF, &b_mu_isPF);
   fChain->SetBranchAddress("mu_isSTA", &mu_isSTA, &b_mu_isSTA);
   fChain->SetBranchAddress("mu_D0", &mu_D0, &b_mu_D0);
   fChain->SetBranchAddress("mu_Dz", &mu_Dz, &b_mu_Dz);
   fChain->SetBranchAddress("mu_chi2ndf", &mu_chi2ndf, &b_mu_chi2ndf);
   fChain->SetBranchAddress("mu_innerD0", &mu_innerD0, &b_mu_innerD0);
   fChain->SetBranchAddress("mu_innerDz", &mu_innerDz, &b_mu_innerDz);
   fChain->SetBranchAddress("mu_innerD0Err", &mu_innerD0Err, &b_mu_innerD0Err);
   fChain->SetBranchAddress("mu_innerDzErr", &mu_innerDzErr, &b_mu_innerDzErr);
   fChain->SetBranchAddress("mu_innerPt", &mu_innerPt, &b_mu_innerPt);
   fChain->SetBranchAddress("mu_innerPtError", &mu_innerPtError, &b_mu_innerPtError);
   fChain->SetBranchAddress("mu_innerEta", &mu_innerEta, &b_mu_innerEta);
   //fChain->SetBranchAddress("mu_innerHighPurity", &mu_innerHighPurity, &b_mu_innerHighPurity);
   fChain->SetBranchAddress("mu_isGood", &mu_isGood, &b_mu_isGood);
   fChain->SetBranchAddress("mu_trkLayers", &mu_trkLayers, &b_mu_trkLayers);
   fChain->SetBranchAddress("mu_pixelLayers", &mu_pixelLayers, &b_mu_pixelLayers);
   fChain->SetBranchAddress("mu_pixelHits", &mu_pixelHits, &b_mu_pixelHits);
   fChain->SetBranchAddress("mu_muonHits", &mu_muonHits, &b_mu_muonHits);
   fChain->SetBranchAddress("mu_trkQuality", &mu_trkQuality, &b_mu_trkQuality);
   fChain->SetBranchAddress("mu_stations", &mu_stations, &b_mu_stations);
   Notify();
}

Bool_t ReadSlimSkimData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ReadSlimSkimData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ReadSlimSkimData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ReadSlimSkimData_cxx
