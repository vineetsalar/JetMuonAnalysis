//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov 14 14:07:51 2018 by ROOT version 5.34/36
// from TTree mixing_tree/
// found on file: PYTHIA6.root
//////////////////////////////////////////////////////////

#ifndef JetAnalyzer_h
#define JetAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include "TLorentzVector.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class JetAnalyzer {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  
  Int_t           HLT_ak4PFJet80;
  Int_t           HLT_ak4PFJet100;
  Int_t           HLT_ak4CaloJet80_Prescale;
  Int_t           HLT_ak4CaloJet100_Prescale;

  Int_t           HLT_HIL3Mu5_AK4PFJet30_v1;
  Int_t           HLT_HIL3Mu5_AK4PFJet30_v1_Prescl;
  Int_t           HLT_HIL3Mu5_AK4PFJet40_v1;
  Int_t           HLT_HIL3Mu5_AK4PFJet40_v1_Prescl;
  Int_t           HLT_HIL3Mu5_AK4PFJet60_v1;
  Int_t           HLT_HIL3Mu5_AK4PFJet60_v1_Prescl;

  Int_t           HBHENoiseFilterResult;
  Int_t           HBHENoiseFilterResultRun1;
  Int_t           HBHENoiseFilterResultRun2Loose;
  Int_t           HBHENoiseFilterResultRun2Tight;
  Int_t           HBHEIsoNoiseFilterResult;
  Int_t           pPAprimaryVertexFilter;

  vector<float>   *trkPt;
  vector<float>   *trkEta;
  vector<float>   *trkPhi;
  vector<int>     *trkAlgo;
  vector<bool>    *highPurity;

  Float_t         hiBin;
  Float_t         vx;
  Float_t         vy;
  Float_t         vz;

  vector<float>   *pf_jteta;
  vector<float>   *pf_jtphi;
  vector<float>   *pf_jtpt;
  vector<float>   *pf_rawpt;
  vector<float>   *pf_corrpt;
  vector<float>   *pf_trackMax;

  vector<float>   *calo_jteta;
  vector<float>   *calo_jtphi;
  vector<float>   *calo_jtpt;
  vector<float>   *calo_rawpt;
  vector<float>   *calo_corrpt;
  vector<float>   *calo_trackMax;
  vector<float>   *pf_refpt;
  vector<float>   *calo_refpt;
  Float_t         pthat;
  Float_t         weight;

  Int_t           flavor_b_mode;


  // track related stuff
  vector<float>   *trkDxy;
  vector<float>   *trkDxyError;
  vector<float>   *trkDz;
  vector<float>   *trkDzError;
  vector<float>   *trkPtError;
  vector<float>   *trkChi2;
  vector<int>     *trkNdof;
  vector<int>     *trkNHit;
  vector<int>     *trkNlayer;
  vector<float>   *pfEcal;
  vector<float>   *pfHcal;
  vector<float>   *trkMVALoose;
  vector<float>   *trkMVATight;
  vector<float>   *loose;
  vector<float>   *tight;

  //gen particles
  vector<float>   *pt;
  vector<float>   *phi;
  vector<float>   *eta;
  vector<int>     *chg;
  vector<int>     *status;
  vector<int>     *sube;//collision ID
  vector<int>     *pdg;

  vector<float>   *pPt; //not filled
  vector<float>   *pPhi;//not filled
  vector<float>   *pEta;//not filled

  vector<float>   *geneta;
  vector<float>   *genphi;
  vector<float>   *genpt;
  
  Int_t           nPFpart;
  vector<int>     *nCSpart;
  vector<int>     *nCSpartGT1;
  vector<int>     *nCSpartGT2;
  vector<int>     *nCSpartGT2_id1;
  vector<int>     *nPFpartPerJet;
  vector<int>     *nPFpartGT2;
  vector<int>     *nPFpartGT2_id1;
  vector<int>     *pf_nPFpartGT2_id1;
  vector<int>     *pfId;
  vector<float>   *pfPt;
  vector<float>   *pfVsPtInitial;
  vector<float>   *pfEta;
  vector<float>   *pfPhi;
  vector<int>     *pf_refparton_flavor;
  vector<int>     *pf_refparton_flavorForB;

  vector<int>     *calo_refparton_flavor;
  vector<float>   *calo_refparton_pt;
  vector<int>     *calo_refparton_flavorForB;
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
  
  vector<float>   *mu_pt;
  vector<float>   *mu_phi;
  vector<float>   *mu_eta;

  vector<float>   *mu_D0;
  vector<float>   *mu_Dz;
  vector<float>   *mu_chi2ndf;
  
  vector<float>   *mu_innerD0;
  vector<float>   *mu_innerDz;

  vector<float>   *mu_innerD0Err;
  vector<float>   *mu_innerDzErr;
  
  vector<float>   *mu_isoTrk;
  vector<float>   *mu_pfChIso;
  vector<float>   *mu_pfPhoIso;
  vector<float>   *mu_pfNeuIso;
  vector<float>   *mu_pfPUIso;
  
  vector<int>     *mu_chg;
  
  vector<int>     *mu_type;
  vector<int>     *mu_isGlobal;
  vector<int>     *mu_isTracker;
  vector<int>     *mu_isPF;
  vector<int>     *mu_isSTA;
    
  vector<int>     *mu_isGood;
  vector<int>     *mu_trkLayers;
  
  vector<int>     *mu_pixelLayers;
  vector<int>     *mu_pixelHits;
  

  vector<int>     *mu_muonHits;
  vector<int>     *mu_trkQuality;
  vector<int>     *mu_stations;




  // List of branches
  TBranch        *b_HLT_ak4PFJet80;   //!
  TBranch        *b_HLT_ak4PFJet100;   //!
  TBranch        *b_HLT_ak4CaloJet80_Prescale;   //!
  TBranch        *b_HLT_ak4CaloJet100_Prescale;   //!
  

  TBranch        *b_HLT_HIL3Mu5_AK4PFJet30_v1;
  TBranch        *b_HLT_HIL3Mu5_AK4PFJet30_v1_Prescl;
  TBranch        *b_HLT_HIL3Mu5_AK4PFJet40_v1;
  TBranch        *b_HLT_HIL3Mu5_AK4PFJet40_v1_Prescl;
  TBranch        *b_HLT_HIL3Mu5_AK4PFJet60_v1;
  TBranch        *b_HLT_HIL3Mu5_AK4PFJet60_v1_Prescl;



  TBranch        *b_HBHENoiseFilterResult;   //!
  TBranch        *b_HBHENoiseFilterResultRun1;   //!
  TBranch        *b_HBHENoiseFilterResultRun2Loose;   //!
  TBranch        *b_HBHENoiseFilterResultRun2Tight;   //!
  TBranch        *b_HBHEIsoNoiseFilterResult;   //!
  TBranch        *b_pPAprimaryVertexFilter;   //!
  TBranch        *b_trkPt;   //!
  TBranch        *b_trkEta;   //!
  TBranch        *b_trkPhi;   //!
  TBranch        *b_trkAlgo;   //!
  TBranch        *b_highPurity;   //!

  TBranch        *b_hiBin;   //!
  TBranch        *b_vx;   //!
  TBranch        *b_vy;   //!
  TBranch        *b_vz;   //!
  
  TBranch        *b_pf_jteta;   //!
  TBranch        *b_pf_jtphi;   //!
  TBranch        *b_pf_jtpt;   //!
  TBranch        *b_pf_rawpt;   //!
  TBranch        *b_pf_corrpt;   //!
  TBranch        *b_pf_trackMax;   //!
  TBranch        *b_calo_jteta;   //!
  TBranch        *b_calo_jtphi;   //!
  TBranch        *b_calo_jtpt;   //!
  TBranch        *b_calo_rawpt;   //!
  TBranch        *b_calo_corrpt;   //!
  TBranch        *b_calo_trackMax;   //!
  TBranch        *b_pf_refpt;   //!
  TBranch        *b_calo_refpt;   //!
  TBranch        *b_pthat;   //!
  TBranch        *b_weight;   //!
  
  TBranch        *b_flavor_b_mode;   //!
  TBranch        *b_trkDxy;   //!
  TBranch        *b_trkDxyError;   //!
  TBranch        *b_trkDz;   //!
  TBranch        *b_trkDzError;   //!
  TBranch        *b_trkPtError;   //!
  TBranch        *b_trkChi2;   //!
  TBranch        *b_trkNdof;   //!
  TBranch        *b_trkNHit;   //!
  TBranch        *b_trkNlayer;   //!
  TBranch        *b_pfEcal;   //!
  TBranch        *b_pfHcal;   //!
  TBranch        *b_trkMVALoose;   //!
  TBranch        *b_trkMVATight;   //!
  TBranch        *b_loose;   //!
  TBranch        *b_tight;   //!
  TBranch        *b_pt;   //!
  TBranch        *b_phi;   //!
  TBranch        *b_eta;   //!
  TBranch        *b_chg;   //!
  TBranch        *b_status;   //!
  TBranch        *b_sube;   //!
  TBranch        *b_pdg;   //!
  TBranch        *b_pPt;   //!
  TBranch        *b_pPhi;   //!
  TBranch        *b_pEta;   //!
  TBranch        *b_geneta;   //!
  TBranch        *b_genphi;   //!
  TBranch        *b_genpt;//!

  TBranch        *b_nPFpart;   //!
  TBranch        *b_nCSpart;   //!
  TBranch        *b_nCSpartGT1;   //!
  TBranch        *b_nCSpartGT2;   //!
  TBranch        *b_nCSpartGT2_id1;   //!
  TBranch        *b_nPFpartPerJet;   //!
  TBranch        *b_nPFpartGT2;   //!
  TBranch        *b_nPFpartGT2_id1;   //!
  TBranch        *b_pf_nPFpartGT2_id1;   //!
  TBranch        *b_pfId;   //!
  TBranch        *b_pfPt;   //!
  TBranch        *b_pfVsPtInitial;   //!
  TBranch        *b_pfEta;   //!
  TBranch        *b_pfPhi;   //!
  TBranch        *b_pf_refparton_flavor;   //!
  TBranch        *b_pf_refparton_flavorForB;   //!
  TBranch        *b_calo_refparton_flavor;   //!
  TBranch        *b_calo_refparton_pt;   //!
  TBranch        *b_calo_refparton_flavorForB;   //!
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
  TBranch        *b_mu_pt;   //!
  TBranch        *b_mu_phi;   //!
  TBranch        *b_mu_eta;   //!
  TBranch        *b_mu_D0;   //!
  TBranch        *b_mu_Dz;   //!
  TBranch        *b_mu_chi2ndf;   //!
  TBranch        *b_mu_innerD0;   //!
  TBranch        *b_mu_innerDz;   //!
  TBranch        *b_mu_innerD0Err;   //!
  TBranch        *b_mu_innerDzErr;   //!
  TBranch        *b_mu_isoTrk;   //!
  TBranch        *b_mu_pfChIso;   //!
  TBranch        *b_mu_pfPhoIso;   //!
  TBranch        *b_mu_pfNeuIso;   //!
  TBranch        *b_mu_pfPUIso;   //!
  TBranch        *b_mu_chg;   //!
  TBranch        *b_mu_type;   //!

  TBranch        *b_mu_isGlobal;   //!
  TBranch        *b_mu_isTracker;   //!
  TBranch        *b_mu_isPF;   //!
  TBranch        *b_mu_isSTA;   //!

  TBranch        *b_mu_isGood;   //!
  TBranch        *b_mu_trkLayers;   //!
  TBranch        *b_mu_pixelLayers;   //!
  TBranch        *b_mu_pixelHits;   //!
  TBranch        *b_mu_muonHits;   //!
  TBranch        *b_mu_trkQuality;   //!
  TBranch        *b_mu_stations;   //!
  
  //JetAnalyzer(TTree *tree=0, int jobID=0, int endfile =4);
  JetAnalyzer(int doCrab=1, int jobID=0, int endfile =2);
  virtual ~JetAnalyzer();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef JetAnalyzer_cxx






JetAnalyzer::~JetAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t JetAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t JetAnalyzer::LoadTree(Long64_t entry)
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

void JetAnalyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   trkPt = 0;
   trkEta = 0;
   trkPhi = 0;
   trkAlgo = 0;
   highPurity = 0;
   pf_jteta = 0;
   pf_jtphi = 0;
   pf_jtpt = 0;
   pf_rawpt = 0;
   pf_corrpt = 0;
   pf_trackMax = 0;
   calo_jteta = 0;
   calo_jtphi = 0;
   calo_jtpt = 0;
   calo_rawpt = 0;
   calo_corrpt = 0;
   calo_trackMax = 0;
   pf_refpt = 0;
   calo_refpt = 0;
   trkDxy = 0;
   trkDxyError = 0;
   trkDz = 0;
   trkDzError = 0;
   trkPtError = 0;
   trkChi2 = 0;
   trkNdof = 0;
   trkNHit = 0;
   trkNlayer = 0;
   pfEcal = 0;
   pfHcal = 0;
   trkMVALoose = 0;
   trkMVATight = 0;
   loose = 0;
   tight = 0;
   pt = 0;
   phi = 0;
   eta = 0;
   chg = 0;
   status = 0;
   sube = 0;
   pdg = 0;
   pPt = 0;
   pPhi = 0;
   pEta = 0;
   geneta = 0;
   genphi = 0;
   genpt = 0;

   nCSpart = 0;
   nCSpartGT1 = 0;
   nCSpartGT2 = 0;
   nCSpartGT2_id1 = 0;
   nPFpartPerJet = 0;
   nPFpartGT2 = 0;
   nPFpartGT2_id1 = 0;
   pf_nPFpartGT2_id1 = 0;
   pfId = 0;
   pfPt = 0;
   pfVsPtInitial = 0;
   pfEta = 0;
   pfPhi = 0;
   pf_refparton_flavor = 0;
   pf_refparton_flavorForB = 0;
   calo_refparton_flavor = 0;
   calo_refparton_pt = 0;
   calo_refparton_flavorForB = 0;
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
   mu_pt = 0;
   mu_phi = 0;
   mu_eta = 0;
   mu_D0 = 0;
   mu_Dz = 0;
   mu_chi2ndf = 0;
   mu_innerD0 = 0;
   mu_innerDz = 0;
   mu_innerD0Err = 0;
   mu_innerDzErr = 0;
   mu_isoTrk = 0;
   mu_pfChIso = 0;
   mu_pfPhoIso = 0;
   mu_pfNeuIso = 0;
   mu_pfPUIso = 0;
   mu_chg = 0;
   mu_type = 0;

   mu_isGlobal = 0;
   mu_isTracker = 0;
   mu_isPF = 0;
   mu_isSTA = 0;
   

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


   const bool is_PP2017MC = 1;


   if(!is_PP2017MC)fChain->SetBranchAddress("HLT_ak4PFJet80", &HLT_ak4PFJet80, &b_HLT_ak4PFJet80);
   if(!is_PP2017MC)fChain->SetBranchAddress("HLT_ak4PFJet100", &HLT_ak4PFJet100, &b_HLT_ak4PFJet100);
   if(!is_PP2017MC)fChain->SetBranchAddress("HLT_ak4CaloJet80_Prescale", &HLT_ak4CaloJet80_Prescale, &b_HLT_ak4CaloJet80_Prescale);
   if(!is_PP2017MC)fChain->SetBranchAddress("HLT_ak4CaloJet100_Prescale", &HLT_ak4CaloJet100_Prescale, &b_HLT_ak4CaloJet100_Prescale);

   if(is_PP2017MC)fChain->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet30_v1", &HLT_HIL3Mu5_AK4PFJet30_v1, &b_HLT_HIL3Mu5_AK4PFJet30_v1);
   if(is_PP2017MC)fChain->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet30_v1_Prescl", &HLT_HIL3Mu5_AK4PFJet30_v1_Prescl, &b_HLT_HIL3Mu5_AK4PFJet30_v1_Prescl);
   if(is_PP2017MC)fChain->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet40_v1", &HLT_HIL3Mu5_AK4PFJet40_v1, &b_HLT_HIL3Mu5_AK4PFJet40_v1);
   if(is_PP2017MC)fChain->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet40_v1_Prescl", &HLT_HIL3Mu5_AK4PFJet40_v1_Prescl, &b_HLT_HIL3Mu5_AK4PFJet40_v1_Prescl);
   if(is_PP2017MC)fChain->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet60_v1", &HLT_HIL3Mu5_AK4PFJet60_v1, &b_HLT_HIL3Mu5_AK4PFJet60_v1);
   if(is_PP2017MC)fChain->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet60_v1_Prescl", &HLT_HIL3Mu5_AK4PFJet60_v1_Prescl, &b_HLT_HIL3Mu5_AK4PFJet60_v1_Prescl);



   fChain->SetBranchAddress("HBHENoiseFilterResult", &HBHENoiseFilterResult, &b_HBHENoiseFilterResult);
   fChain->SetBranchAddress("HBHENoiseFilterResultRun1", &HBHENoiseFilterResultRun1, &b_HBHENoiseFilterResultRun1);
   fChain->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseFilterResultRun2Loose, &b_HBHENoiseFilterResultRun2Loose);
   fChain->SetBranchAddress("HBHENoiseFilterResultRun2Tight", &HBHENoiseFilterResultRun2Tight, &b_HBHENoiseFilterResultRun2Tight);
   fChain->SetBranchAddress("HBHEIsoNoiseFilterResult", &HBHEIsoNoiseFilterResult, &b_HBHEIsoNoiseFilterResult);
   if(!is_PP2017MC)fChain->SetBranchAddress("pPAprimaryVertexFilter", &pPAprimaryVertexFilter, &b_pPAprimaryVertexFilter);
   fChain->SetBranchAddress("trkPt", &trkPt, &b_trkPt);
   fChain->SetBranchAddress("trkEta", &trkEta, &b_trkEta);
   fChain->SetBranchAddress("trkPhi", &trkPhi, &b_trkPhi);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkAlgo", &trkAlgo, &b_trkAlgo);
   if(!is_PP2017MC)fChain->SetBranchAddress("highPurity", &highPurity, &b_highPurity);

   fChain->SetBranchAddress("hiBin", &hiBin, &b_hiBin);
   fChain->SetBranchAddress("vx", &vx, &b_vx);
   fChain->SetBranchAddress("vy", &vy, &b_vy);
   fChain->SetBranchAddress("vz", &vz, &b_vz);


   fChain->SetBranchAddress("pf_jteta", &pf_jteta, &b_pf_jteta);
   fChain->SetBranchAddress("pf_jtphi", &pf_jtphi, &b_pf_jtphi);
   fChain->SetBranchAddress("pf_jtpt", &pf_jtpt, &b_pf_jtpt);
   fChain->SetBranchAddress("pf_rawpt", &pf_rawpt, &b_pf_rawpt);
   fChain->SetBranchAddress("pf_corrpt", &pf_corrpt, &b_pf_corrpt);
   fChain->SetBranchAddress("pf_trackMax", &pf_trackMax, &b_pf_trackMax);
   fChain->SetBranchAddress("calo_jteta", &calo_jteta, &b_calo_jteta);
   fChain->SetBranchAddress("calo_jtphi", &calo_jtphi, &b_calo_jtphi);
   fChain->SetBranchAddress("calo_jtpt", &calo_jtpt, &b_calo_jtpt);
   fChain->SetBranchAddress("calo_rawpt", &calo_rawpt, &b_calo_rawpt);
   fChain->SetBranchAddress("calo_corrpt", &calo_corrpt, &b_calo_corrpt);
   fChain->SetBranchAddress("calo_trackMax", &calo_trackMax, &b_calo_trackMax);
   fChain->SetBranchAddress("pf_refpt", &pf_refpt, &b_pf_refpt);
   fChain->SetBranchAddress("calo_refpt", &calo_refpt, &b_calo_refpt);
   
   fChain->SetBranchAddress("pf_pthat", &pthat, &b_pthat);
   fChain->SetBranchAddress("pf_weight", &weight, &b_weight);

   if(!is_PP2017MC)fChain->SetBranchAddress("flavor_b_mode", &flavor_b_mode, &b_flavor_b_mode);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkDxy", &trkDxy, &b_trkDxy);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkDxyError", &trkDxyError, &b_trkDxyError);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkDz", &trkDz, &b_trkDz);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkDzError", &trkDzError, &b_trkDzError);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkPtError", &trkPtError, &b_trkPtError);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkChi2", &trkChi2, &b_trkChi2);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkNdof", &trkNdof, &b_trkNdof);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkNHit", &trkNHit, &b_trkNHit);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkNlayer", &trkNlayer, &b_trkNlayer);
   if(!is_PP2017MC)fChain->SetBranchAddress("pfEcal", &pfEcal, &b_pfEcal);
   if(!is_PP2017MC)fChain->SetBranchAddress("pfHcal", &pfHcal, &b_pfHcal);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkMVALoose", &trkMVALoose, &b_trkMVALoose);
   if(!is_PP2017MC)fChain->SetBranchAddress("trkMVATight", &trkMVATight, &b_trkMVATight);
   if(!is_PP2017MC)fChain->SetBranchAddress("loose", &loose, &b_loose);
   if(!is_PP2017MC)fChain->SetBranchAddress("tight", &tight, &b_tight);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("phi", &phi, &b_phi);
   fChain->SetBranchAddress("eta", &eta, &b_eta);
   fChain->SetBranchAddress("chg", &chg, &b_chg);
   if(!is_PP2017MC)fChain->SetBranchAddress("status", &status, &b_status);
   fChain->SetBranchAddress("sube", &sube, &b_sube);
   fChain->SetBranchAddress("pdg", &pdg, &b_pdg);
   if(!is_PP2017MC)fChain->SetBranchAddress("pPt", &pPt, &b_pPt);
   if(!is_PP2017MC)fChain->SetBranchAddress("pPhi", &pPhi, &b_pPhi);
   if(!is_PP2017MC)fChain->SetBranchAddress("pEta", &pEta, &b_pEta);

   fChain->SetBranchAddress("pf_geneta", &geneta, &b_geneta);
   fChain->SetBranchAddress("pf_genphi", &genphi, &b_genphi);
   fChain->SetBranchAddress("pf_genpt", &genpt, &b_genpt);


   if(!is_PP2017MC)fChain->SetBranchAddress("nPFpart", &nPFpart, &b_nPFpart);
   if(!is_PP2017MC)fChain->SetBranchAddress("nCSpart", &nCSpart, &b_nCSpart);
   if(!is_PP2017MC)fChain->SetBranchAddress("nCSpartGT1", &nCSpartGT1, &b_nCSpartGT1);
   if(!is_PP2017MC)fChain->SetBranchAddress("nCSpartGT2", &nCSpartGT2, &b_nCSpartGT2);
   if(!is_PP2017MC)fChain->SetBranchAddress("nCSpartGT2_id1", &nCSpartGT2_id1, &b_nCSpartGT2_id1);
   if(!is_PP2017MC)fChain->SetBranchAddress("nPFpartPerJet", &nPFpartPerJet, &b_nPFpartPerJet);
   if(!is_PP2017MC)fChain->SetBranchAddress("nPFpartGT2", &nPFpartGT2, &b_nPFpartGT2);
   if(!is_PP2017MC)fChain->SetBranchAddress("nPFpartGT2_id1", &nPFpartGT2_id1, &b_nPFpartGT2_id1);
   if(!is_PP2017MC)fChain->SetBranchAddress("pf_nPFpartGT2_id1", &pf_nPFpartGT2_id1, &b_pf_nPFpartGT2_id1);
   if(!is_PP2017MC)fChain->SetBranchAddress("pfId", &pfId, &b_pfId);
   if(!is_PP2017MC)fChain->SetBranchAddress("pfPt", &pfPt, &b_pfPt);
   if(!is_PP2017MC)fChain->SetBranchAddress("pfVsPtInitial", &pfVsPtInitial, &b_pfVsPtInitial);
   if(!is_PP2017MC)fChain->SetBranchAddress("pfEta", &pfEta, &b_pfEta);
   if(!is_PP2017MC)fChain->SetBranchAddress("pfPhi", &pfPhi, &b_pfPhi);
   fChain->SetBranchAddress("pf_refparton_flavor", &pf_refparton_flavor, &b_pf_refparton_flavor);
   fChain->SetBranchAddress("pf_refparton_flavorForB", &pf_refparton_flavorForB, &b_pf_refparton_flavorForB);
   fChain->SetBranchAddress("calo_refparton_flavor", &calo_refparton_flavor, &b_calo_refparton_flavor);
   if(!is_PP2017MC)fChain->SetBranchAddress("calo_refparton_pt", &calo_refparton_pt, &b_calo_refparton_pt);
   fChain->SetBranchAddress("calo_refparton_flavorForB", &calo_refparton_flavorForB, &b_calo_refparton_flavorForB);
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


   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_D0", &mu_D0, &b_mu_D0);
   fChain->SetBranchAddress("mu_Dz", &mu_Dz, &b_mu_Dz);
   fChain->SetBranchAddress("mu_chi2ndf", &mu_chi2ndf, &b_mu_chi2ndf);
   fChain->SetBranchAddress("mu_innerD0", &mu_innerD0, &b_mu_innerD0);
   fChain->SetBranchAddress("mu_innerDz", &mu_innerDz, &b_mu_innerDz);
   fChain->SetBranchAddress("mu_innerD0Err", &mu_innerD0Err, &b_mu_innerD0Err);
   fChain->SetBranchAddress("mu_innerDzErr", &mu_innerDzErr, &b_mu_innerDzErr);
   
   if(!is_PP2017MC)fChain->SetBranchAddress("mu_isoTrk", &mu_isoTrk, &b_mu_isoTrk);
   if(!is_PP2017MC)fChain->SetBranchAddress("mu_pfChIso", &mu_pfChIso, &b_mu_pfChIso);
   if(!is_PP2017MC)fChain->SetBranchAddress("mu_pfPhoIso", &mu_pfPhoIso, &b_mu_pfPhoIso);
   if(!is_PP2017MC)fChain->SetBranchAddress("mu_pfNeuIso", &mu_pfNeuIso, &b_mu_pfNeuIso);
   if(!is_PP2017MC)fChain->SetBranchAddress("mu_pfPUIso", &mu_pfPUIso, &b_mu_pfPUIso);
   fChain->SetBranchAddress("mu_chg", &mu_chg, &b_mu_chg);
   fChain->SetBranchAddress("mu_type", &mu_type, &b_mu_type);
   fChain->SetBranchAddress("mu_isGlobal", &mu_isGlobal, &b_mu_isGlobal);
   fChain->SetBranchAddress("mu_isTracker", &mu_isTracker, &b_mu_isTracker);
   fChain->SetBranchAddress("mu_isPF", &mu_isPF, &b_mu_isPF);
   fChain->SetBranchAddress("mu_isSTA", &mu_isSTA, &b_mu_isSTA);
   fChain->SetBranchAddress("mu_isGood", &mu_isGood, &b_mu_isGood);
   fChain->SetBranchAddress("mu_trkLayers", &mu_trkLayers, &b_mu_trkLayers);
   fChain->SetBranchAddress("mu_pixelLayers", &mu_pixelLayers, &b_mu_pixelLayers);
   fChain->SetBranchAddress("mu_pixelHits", &mu_pixelHits, &b_mu_pixelHits);
   fChain->SetBranchAddress("mu_muonHits", &mu_muonHits, &b_mu_muonHits);
   fChain->SetBranchAddress("mu_trkQuality", &mu_trkQuality, &b_mu_trkQuality);
   fChain->SetBranchAddress("mu_stations", &mu_stations, &b_mu_stations);

   Notify();
}

Bool_t JetAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void JetAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t JetAnalyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

/*
  class Rectangle {
  int width, height;
  public:
  void set_values (int,int);
  int area() {return width*height;}
  };
  
  void Rectangle::set_values (int x, int y) {
  width = x;
  height = y;
  }
*/



//class inhareted from TLorentz Vector
class MyParticle : public TLorentzVector{

private:
  //add muon quality cuts as members of the class
  Float_t mu_D0, mu_Dz, mu_chi2ndf, mu_innerD0, mu_innerDz, mu_muonHits, mu_innerD0Err, mu_innerDzErr, mu_innerD0Norm, mu_innerDzNorm;
  Int_t mu_isGlobal, mu_isTracker, mu_isPF, mu_isSTA, mu_isGood, mu_pixelLayers, mu_pixelHits, mu_trkLayers, mu_stations, mu_trkQuality;

  Int_t mu_hasGenMu =0;


  
public:

  void SetParticle_IntQualityCuts(Int_t,Int_t,Int_t,Int_t,Int_t,Int_t,Int_t,Int_t,Int_t,Int_t);
  void SetParticle_FloatQualityCuts(Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t);
  void SetParticle_MCMatch(Int_t);

  
  Int_t GetParticle_isGlobal(){return mu_isGlobal;}
  Int_t GetParticle_isTracker(){return mu_isTracker;}
  Int_t GetParticle_isPF(){return mu_isPF;}
  Int_t GetParticle_isSTA(){return mu_isSTA;}
  Int_t GetParticle_isGood(){return mu_isGood;}
  
  Int_t GetParticle_pixelLayers(){return mu_pixelLayers;}
  Int_t GetParticle_pixelHits(){return mu_pixelHits;}
  Int_t GetParticle_trkLayers(){return mu_trkLayers;}
  Int_t GetParticle_stations(){return mu_stations;}
  Int_t GetParticle_trkQuality(){return mu_trkQuality;}



  Float_t GetParticle_D0(){return mu_D0;}
  Float_t GetParticle_Dz(){return mu_Dz;}
  Float_t GetParticle_chi2ndf(){return mu_chi2ndf;}
  Float_t GetParticle_innerD0(){return mu_innerD0;}
  Float_t GetParticle_innerDz(){return mu_innerDz;}
  Float_t GetParticle_muonHits(){return mu_muonHits;}
  
  Float_t GetParticle_innerD0Err(){return mu_innerD0Err;}
  Float_t GetParticle_innerDzErr(){return mu_innerDzErr;}

  Float_t GetParticle_innerD0Norm(){return mu_innerD0Norm;}
  Float_t GetParticle_innerDzNorm(){return mu_innerDzNorm;}

  Int_t GetParticle_MCMatch(){return mu_hasGenMu;}

  
  //Double_t GetParticle_Pt(){return Pt;}
  //Double_t GetParticle_Eta(){return Eta;}
  //Double_t GetParticle_Phi(){return Phi;}

};


/*
void MyParticle::SetParticle_Pt_Eta_Phi(Double_t pt, Double_t eta, Double_t phi){

  Pt = pt;
  Eta = eta;
  Phi = phi;
  
}
*/

void MyParticle::SetParticle_IntQualityCuts(Int_t Mu_isGlobal, Int_t Mu_isTracker, Int_t Mu_isPF, Int_t Mu_isSTA, Int_t Mu_isGood, Int_t Mu_pixelLayers, Int_t Mu_pixelHits,
					    Int_t Mu_trkLayers, Int_t Mu_stations, Int_t Mu_trkQuality){
  mu_isGlobal=Mu_isGlobal;
  mu_isTracker=Mu_isTracker;
  mu_isPF=Mu_isPF;
  mu_isSTA=Mu_isSTA;
  mu_isGood=Mu_isGood;
  mu_pixelLayers=Mu_pixelLayers;
  mu_pixelHits=Mu_pixelHits;
  mu_trkLayers=Mu_trkLayers;
  mu_stations=Mu_stations;
  mu_trkQuality=Mu_trkQuality;

}








//mu_D0, mu_Dz, mu_chi2ndf, mu_innerD0, mu_innerDz, mu_muonHits, mu_innerD0Err, mu_innerDzErr, mu_innerD0Norm, mu_innerDzNorm

void MyParticle::SetParticle_FloatQualityCuts(Float_t Mu_D0, Float_t Mu_Dz, Float_t Mu_chi2ndf, Float_t Mu_innerD0, Float_t Mu_innerDz, Float_t Mu_muonHits,
				  Float_t Mu_innerD0Err, Float_t Mu_innerDzErr, Float_t Mu_innerD0Norm, Float_t Mu_innerDzNorm)
{
  mu_D0 =Mu_D0;
  mu_Dz=Mu_Dz;
  mu_chi2ndf=Mu_chi2ndf;
  mu_innerD0=Mu_innerD0;
  mu_innerDz=Mu_innerDz;
  mu_muonHits=Mu_muonHits;
  mu_innerD0Err=Mu_innerD0Err;
  mu_innerDzErr=Mu_innerDzErr;
  mu_innerD0Norm=Mu_innerD0Norm;
  mu_innerDzNorm=Mu_innerDzNorm;

}

void MyParticle::SetParticle_MCMatch(Int_t Mu_hasGenMu)
{
  mu_hasGenMu = Mu_hasGenMu;
}










#endif // #ifdef JetAnalyzer_cxx
