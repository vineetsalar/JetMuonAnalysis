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
#include "TH1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TF1.h"
#include "TH1I.h"
#include "THnSparse.h"




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



  //Define the histograms here
  // Centrality
  const Double_t minCentrality = -0.75;   // Minimum centrality bin, is negative since hiBin is -1 for pp
  const Double_t maxCentrality = 100.25;  // Maximum centrality bin
  const Int_t nCentralityBins = 202;      // Number of centrality bins

  //Gen Jet Binning
  const Int_t NBinsGenJetPt =500;
  const Double_t GenJetPtMin =0.0;
  const Double_t GenJetPtMax = 500.0;
  
  const Int_t NBinsGenJetEta = 200;
  const Double_t GenJetEtaMin = -3.0;
  const Double_t GenJetEtaMax = 3.0;
  
  const Double_t Pi = TMath::Pi();
  const Int_t NBinsGenJetPhi = 200;
  const Double_t GenJetPhiMin = -Pi;
  const Double_t GenJetPhiMax = Pi;


  const Int_t NFlavour = 9;
  const Double_t FlavourMin = 0.5;
  const Double_t FlavourMax = 9.5;



  const Int_t NBinsGenMuPt = 150;
  const Double_t GenMuPtMin = 0.0;
  const Double_t GenMuPtMax = 150.0;

  const Int_t NBinsGenMuEta = 200;
  const Double_t GenMuEtaMin = -3.0;
  const Double_t GenMuEtaMax = 3.0;

  const Int_t NBinsGenMuPhi = 200;
  const Double_t GenMuPhiMin = -Pi;
  const Double_t GenMuPhiMax = Pi;

  //DeltaPhi
  const Double_t minDeltaPhiJetMuon = -TMath::Pi()/2.0;    // Minimum deltaPhi for jet-muon 
  const Double_t maxDeltaPhiJetMuon = 3.0*TMath::Pi()/2.0; // Maximum deltaPhi for jet-muon 
  const Int_t nDeltaPhiBinsJetMuon = 200;                  // Number of deltaPhi bins for jet-muon  (match the common number in UIC group)

  //Muon pT-relative bins
  const Int_t NBinsMuonPtRel = 40;
  const Double_t MuonPtRelMin = 0.0;
  const Double_t MuonPtRelMax = 4.0;



  //Reconstructed Jet Binning 
  const Int_t NBinsJetPt =  500;
  const Double_t JetPtMin = 0.0;
  const Double_t JetPtMax = 500.0;

  
  const Int_t NBinsJetEta = 200;
  const Double_t JetEtaMin = -3.0;
  const Double_t JetEtaMax = 3.0;
  
  
  const Int_t NBinsJetPhi = 200;
  const Double_t JetPhiMin = -Pi;
  const Double_t JetPhiMax = Pi;

  const Int_t NBinsMuPt = 150;
  const Double_t MuPtMin = 0.0;
  const Double_t MuPtMax = 150.0;
  
  const Int_t NBinsMuEta = 200;
  const Double_t MuEtaMin = -3.0;
  const Double_t MuEtaMax = 3.0;
  
  
  const Int_t NBinsMuPhi = 200;
  const Double_t MuPhiMin = -Pi;
  const Double_t MuPhiMax = Pi;
  
  const Int_t NBinsJetCSV =100;
  const Double_t JetCSVMin =0.0;
  const Double_t JetCSVMax =1.2;



  //Adding bins for a four dimensonal histogram
  //1.CSV
  //2.pT^Rel
  //3.Flavour
  //4.MuonPt (may be we need to do it to 150)?
  static const Int_t NDimension = 4;
  const Int_t NBins[NDimension]={NBinsJetCSV,NBinsMuonPtRel,NFlavour,NBinsMuPt};  
  const Double_t xmin[NDimension]={JetCSVMin,MuonPtRelMin,FlavourMin,MuPtMin};
  const Double_t xmax[NDimension]={JetCSVMax,MuonPtRelMax,FlavourMax,MuPtMax};

  //an array to fill the 4D histogram
  Double_t Fill_hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt[NDimension];


  //Define a hsparse for JetPt, MuPt, Flv, MuChi2Ndf, MuDR, MuMCMatch
  static const Int_t NDimension_MuID = 6;

  //number of bins and min max for muon chi2/ndf
  const Int_t NBinsMuonChi2NDF = 100;
  Double_t MuonChi2NDFMin = 0.0;
  Double_t MuonChi2NDFMax = 20.0;

  //number of bins and min max for muon (dxy^2 + dz^2)^{1/2}
  const Int_t NBinsMuonDR    = 200;
  Double_t MuonDRMin = 0.0;
  Double_t MuonDRMax =  1.0;
  
  //number of bins and min max for muon-genmuon match
  const Int_t NBinsMuonMCMatch    = 5;
  Double_t MuonMCMatchMin = -0.5;
  Double_t MuonMCMatchMax =  4.5;
  
  
  const Int_t NBins_MuID[NDimension_MuID]={NBinsJetPt,NBinsMuPt,NFlavour,NBinsMuonChi2NDF,NBinsMuonDR,NBinsMuonMCMatch};  
  const Double_t xmin_MuID[NDimension_MuID]={JetPtMin,MuPtMin,FlavourMin,MuonChi2NDFMin,MuonDRMin,MuonMCMatchMin};
  const Double_t xmax_MuID[NDimension_MuID]={JetPtMax,MuPtMax,FlavourMax,MuonChi2NDFMax,MuonDRMax,MuonMCMatchMax};
  Double_t Fill_hsparse_JetPt_MuPt_Flavour_MuChi2NDF_MuDR_MuMCMatch[NDimension_MuID];


  //bins for histo with all muons inside the Jet
  static const Int_t NBinsMatchedMuonsDR04Size = 12;
  Double_t MatchedMuonsDR04SizeMin = 0.5;
  Double_t MatchedMuonsDR04SizeMax = 12.5;

  //pT hat bins for 2015 MC
  static const Int_t NBINS = 12;
  Double_t edges[NBINS + 1] = {0.0, 30.0, 50.0, 80.0, 100.0, 120.0, 170.0, 220.0, 280.0, 370.0, 460.0, 540.0, 3000.0};
 
  
  
  //Event Level Histograms
  TH1D *histCentrality;
  TH1D *histEvtVtxX;
  TH1D *histEvtVtxY;
  TH1D *histEvtVtxZ;

  TH1D *histCentrality_nw;
  TH1D *histEvtVtxX_nw;
  TH1D *histEvtVtxY_nw;
  TH1D *histEvtVtxZ_nw;

  
  //Gen Jet Histograms
  TH1D *histNumberOfGenJets;
  TH1D *histGenJetPt;
  TH1D *histGenJetEta;
  TH1D *histGenJetPhi;
  TH1D *histGenJetPtNoRec;
  TH1D *histGenJetPtUnknownRec;
  TH1D *histGenJetPtLight;
  TH1D *histGenJetPtUp;
  TH1D *histGenJetPtDown;
  TH1D *histGenJetPtStrange;
  TH1D *histGenJetPtCharm;
  TH1D *histGenJetPtBeauty;
  TH1D *histGenJetPtGluon;
  TH2D *hist_GenMaster_GenJetPt_Flavour;


  //Gen Muon Histograms
  // All the Gen Muons
  TH3D *hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi;
  //Gen Muons matched to Gen Jets
  TH3D *hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi;
  //Gen Muons matched to Reco Muon
  TH3D *hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi;

  //All the Gen Muons (can be used to test 3D histo projections)
  TH1D *histGenMuonPt;
  TH1D *histGenMuonEta;
  TH1D *histGenMuonPhi;
  //All the Gen Dimuons
  TH1D *histGenDiMuonInvMass;
  TH1D *histGenDiMuonInvMassLow;
  TH1D *histGenDiMuonInvMassInt;
  TH1D *histGenDiMuonPt;
  TH1D *histGenDiMuonRapidity;
  TH1D *histGenDiMuonPhi;

  //Histograms with Combination of Gen Muon and Gen Jet
  TH1D *histGenMuonGenJetDR;
  TH1D *histGenMuonGenJetDPhi;
  TH1D *histGenMuonGenJetPtTotal;
  TH1D *histGenMuonGenJetPtLight;
  TH1D *histGenMuonGenJetPtUp;
  TH1D *histGenMuonGenJetPtDown;
  TH1D *histGenMuonGenJetPtStrange;
  TH1D *histGenMuonGenJetPtCharm;
  TH1D *histGenMuonGenJetPtBeauty;
  TH1D *histGenMuonGenJetPtGluon;
  TH3D *hist_GenMaster_GenJetPt_GenMuPt_Flavour;
  TH3D *hist_GenMaster_GenJetPt_GenMuPtRel_Flavour;


  //Histograms for reconstructed Jets
  TH1D *histNumberOfJets;

  TH1D *histJetPt;
  TH1D *histJetEta;
  TH1D *histJetPhi;
  TH1D *histJetPtUnknown;
  TH1D *histJetPtLight;
  TH1D *histJetPtUp;
  TH1D *histJetPtDown;
  TH1D *histJetPtStrange;
  TH1D *histJetPtCharm;
  TH1D *histJetPtBeauty;
  TH1D *histJetPtGluon;
  
  TH2D *hist_Master_JetPt_Flavour;
  TH3D *hist_Master_JetPt_MuPt_Flavour;
  TH3D *hist_Master_JetPt_MuPtRel_Flavour;

  //this will be use to see the effect of
  //mu ID cuts on Jet Fractions 
  TH3D *hist_Master_JetPt_MuPt_Flavour_ModCuts;




  
  

  TH1D *histJetCSV;
  TH1D *histMuonJetCSV;

  TH3D *hist_Master_JetCSV_JetPt_Flavour;
  TH3D *hist_Master_MuonJetCSV_MuonJetPt_Flavour;
  TH3D *hist_Master_JetCSV_MuPtRel_Flavour;

  TH1D *histMuonPtRel;
  TH1D *histMuonPtRelCSVTag;
  TH1D *histMuonPtRelCSVVeto;

  //4D histo of Jet CSV, MuPtRel, JetFlv and Muon pT
  //to check the MuPt rel distribution for CSV tag and
  //CSV veto histograms with different muon pT cuts
  THnSparseD *hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt;


  //6D histo JetPt, MuPt, JetFlv, MuChi2NDF, MuDR( (d0^2+dz^2)^{1/2}) and Mu-GenMu MC Match
  //Idea is to check the effect of these ID cuts on Jet Fractions
  THnSparseD *hsparse_JetPt_MuPt_Flavour_MuChi2NDF_MuDR_MuMCMatch;

  


  
  //reconstructed muon histograms
  //All the muons matched to Jet
  TH3D *hist_Master_MuEta_MuPt_MuPhi;
  //All the reco muons (pass the quality cuts or quality cuts + MC matching if applied)
  TH1D *histMuonPt;
  TH1D *histMuonEta;
  TH1D *histMuonPhi;

  //reco muons which have a gen muon in DeltaR < 0.3
  //(reco muon variables are filled)
  TH1D *histMatchedMuonPt;
  TH1D *histMatchedMuonEta;
  TH1D *histMatchedMuonPhi;
  //reco muons which have a gen muon in DeltaR < 0.3
  //(gen muon variables are filled)
  TH1D *histRecoMatchedGenMuonPt;
  TH1D *histRecoMatchedGenMuonEta;
  TH1D *histRecoMatchedGenMuonPhi;
  //GenMu-RecMu DR and DPt
  TH2D *histGenMuRecMuDRVsDPt;
  //GenMu-RecMu DR with Pt
  TH2D *histGenMuRecMuDRVsPt;
  //GenMu-RecMu DR with Eta
  TH2D *histGenMuRecMuDRVsEta;
  //GenMu-RecMu DR with Phi
  TH2D *histGenMuRecMuDRVsPhi;

  //reco dimuon histograms
  TH1D *histDiMuonInvMass;
  TH1D *histDiMuonInvMassLow;
  TH1D *histDiMuonInvMassInt;
  TH1D *histDiMuonPt;
  TH1D *histDiMuonRapidity;
  TH1D *histDiMuonPhi;
  TH1D *histMuonJetDR;
  TH1D *histMuonJetDPhi;
  TH1D *histMuonJetPtTotal;
  TH1D *histMuonJetPtLight;
  TH1D *histMuonJetPtUp;
  TH1D *histMuonJetPtDown;
  TH1D *histMuonJetPtStrange;
  TH1D *histMuonJetPtCharm;
  TH1D *histMuonJetPtBeauty;
  TH1D *histMuonJetPtGluon;

  // histo with all muons inside the Jet
  TH1D *histMatchedMuonsDR04Size;
  TH1D *histMatchedMuonsDR04Pt;
  TH1D *histMatchedMuonsDR04Eta;
  TH1D *histMatchedMuonsDR04Phi;
  TH1 *histPtHatBins;
  TH1 *histWPtHatBins;


  //Muon ID Histo
  TH1D *histMuonIsGlobal;
  TH1D *histNGMuonIsGlobal;
  TH1D *histMuonIsTracker;
  TH1D *histNGMuonIsTracker;
  TH1D *histMuonIsPF;
  TH1D *histNGMuonIsPF;
  TH1D *histMuonIsSTA;
  TH1D *histNGMuonIsSTA;
  TH1D *histMuonD0;
  TH1D *histNGMuonD0;
  TH1D *histMuonDz;
  TH1D *histNGMuonDz;
  TH2D *histMuonDxyDz;
  TH2D *histNGMuonDxyDz;
  TH1D *histMuonDR;
  TH1D *histNGMuonDR;
  TH1D *histMuonChi2NDF;
  TH1D *histNGMuonChi2NDF;
  TH1D *histMuonInnerD0;
  TH1D *histNGMuonInnerD0;
  TH1D *histMuonInnerD0Err;
  TH1D *histNGMuonInnerD0Err;
  TH1D *histMuonInnerDz;
  TH1D *histNGMuonInnerDz;
  TH1D *histMuonInnerDzErr;
  TH1D *histNGMuonInnerDzErr;
  TH1D *histMuonInnerD0Norm;
  TH1D *histNGMuonInnerD0Norm;
  TH1D *histMuonInnerDzNorm;
  TH1D *histNGMuonInnerDzNorm;
  TH1D *histMuonTrkLayers;
  TH1D *histNGMuonTrkLayers;
  TH1D *histMuonPixelLayers;
  TH1D *histNGMuonPixelLayers;
  TH1D *histMuonPixelHits;
  TH1D *histNGMuonPixelHits;
  TH1D *histMuonMuHits;
  TH1D *histNGMuonMuHits;
  TH1D *histMuonTrkQuality;
  TH1D *histNGMuonTrkQuality;
  TH1D *histMuonMuStations;
  TH1D *histNGMuonMuStations;

  //Muon ID histo for muons Matched to Jets
  TH1D *histJetMuonIsGlobal;
  TH1D *histNGJetMuonIsGlobal;
  TH1D *histJetMuonIsTracker;
  TH1D *histNGJetMuonIsTracker;
  TH1D *histJetMuonIsPF;
  TH1D *histNGJetMuonIsPF;
  TH1D *histJetMuonIsSTA;
  TH1D *histNGJetMuonIsSTA;
  TH1D *histJetMuonD0;
  TH1D *histNGJetMuonD0;
  TH1D *histJetMuonDz;
  TH1D *histNGJetMuonDz;
  TH2D *histJetMuonDxyDz;
  TH2D *histNGJetMuonDxyDz;
  TH1D *histJetMuonDR;
  TH1D *histNGJetMuonDR;
  TH1D *histJetMuonChi2NDF;
  TH1D *histNGJetMuonChi2NDF;
  TH1D *histJetMuonInnerD0;
  TH1D *histNGJetMuonInnerD0;
  TH1D *histJetMuonInnerD0Err;
  TH1D *histNGJetMuonInnerD0Err;
  TH1D *histJetMuonInnerDz;
  TH1D *histNGJetMuonInnerDz;
  TH1D *histJetMuonInnerDzErr;
  TH1D *histNGJetMuonInnerDzErr;
  TH1D *histJetMuonInnerD0Norm;
  TH1D *histNGJetMuonInnerD0Norm;
  TH1D *histJetMuonInnerDzNorm;
  TH1D *histNGJetMuonInnerDzNorm;
  TH1D *histJetMuonTrkLayers;
  TH1D *histNGJetMuonTrkLayers;
  TH1D *histJetMuonPixelLayers;
  TH1D *histNGJetMuonPixelLayers;
  TH1D *histJetMuonPixelHits;
  TH1D *histNGJetMuonPixelHits;
  TH1D *histJetMuonMuHits;
  TH1D *histNGJetMuonMuHits;
  TH1D *histJetMuonTrkQuality;
  TH1D *histNGJetMuonTrkQuality;
  TH1D *histJetMuonMuStations;
  TH1D *histNGJetMuonMuStations;
  
  
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
  void InitHist();
  void InitMuIDHist();


  
};
#endif
#ifdef JetAnalyzer_cxx



void JetAnalyzer::InitHist()
{
  //Basic Event level histograms
  histCentrality= new TH1D("histCentrality","histCentrality", nCentralityBins,minCentrality,maxCentrality);
  histCentrality->GetXaxis()->SetTitle("Centrality");
  histCentrality->GetYaxis()->SetTitle("Entries");

  
  histEvtVtxX= new TH1D("histEvtVtxX","histEvtVtxX",200,-1.0,1.0);
  histEvtVtxX->GetXaxis()->SetTitle("EvtVtxX");
  histEvtVtxX->GetYaxis()->SetTitle("Entries");

  
  histEvtVtxY= new TH1D("histEvtVtxY","histEvtVtxY",200,-1.0,1.0);
  histEvtVtxY->GetXaxis()->SetTitle("EvtVtxY");
  histEvtVtxY->GetYaxis()->SetTitle("Entries");

  histEvtVtxZ= new TH1D("histEvtVtxZ","histEvtVtxZ",300,-30.0,30.0);
  histEvtVtxZ->GetXaxis()->SetTitle("EvtVtxZ");
  histEvtVtxZ->GetYaxis()->SetTitle("Entries");


  //Basic Event histograms to be filled without weights
  histCentrality_nw= new TH1D("histCentrality_nw","histCentrality_nw", nCentralityBins,minCentrality,maxCentrality);
  histCentrality_nw->GetXaxis()->SetTitle("Centrality");
  histCentrality_nw->GetYaxis()->SetTitle("Entries");
  
  
  histEvtVtxX_nw= new TH1D("histEvtVtxX_nw","histEvtVtxX_nw",200,-1.0,1.0);
  histEvtVtxX_nw->GetXaxis()->SetTitle("EvtVtxX");
  histEvtVtxX_nw->GetYaxis()->SetTitle("Entries");

  
  histEvtVtxY_nw= new TH1D("histEvtVtxY_nw","histEvtVtxY_nw",200,-1.0,1.0);
  histEvtVtxY_nw->GetXaxis()->SetTitle("EvtVtxY");
  histEvtVtxY_nw->GetYaxis()->SetTitle("Entries");

  histEvtVtxZ_nw= new TH1D("histEvtVtxZ_nw","histEvtVtxZ_nw",300,-30.0,30.0);
  histEvtVtxZ_nw->GetXaxis()->SetTitle("EvtVtxZ");
  histEvtVtxZ_nw->GetYaxis()->SetTitle("Entries");


  
  //============ Gen Jet Histogrms ===========================//
  histNumberOfJets = new TH1D("histNumberOfJets","histNumberOfJets",30,0.5,30.5);
  histNumberOfJets->GetXaxis()->SetTitle("Jet Multiplicity");
  histNumberOfJets->GetYaxis()->SetTitle("Entries");
  
  histNumberOfGenJets = new TH1D("histNumberOfGenJets","histNumberOfGenJets",30,0.5,30.5);
  histNumberOfGenJets->GetXaxis()->SetTitle("Gen-Jet Multiplicity");
  histNumberOfGenJets->GetYaxis()->SetTitle("Entries");
  

  
  histGenJetPt= new TH1D("histGenJetPt","histGenJetPt",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPt->Sumw2();
  histGenJetPt->GetXaxis()->SetTitle("GenJet Pt (GeV/c)");
  histGenJetPt->GetYaxis()->SetTitle("Entries");
  
  histGenJetEta = new TH1D("histGenJetEta","histGenJetEta",NBinsGenJetEta,GenJetEtaMin,GenJetEtaMax);
  histGenJetEta->Sumw2();
  histGenJetEta->GetXaxis()->SetTitle("GenJet #eta");
  histGenJetEta->GetYaxis()->SetTitle("Entries");
  
  histGenJetPhi = new TH1D("histGenJetPhi","histGenJetPhi", NBinsGenJetPhi,GenJetPhiMin,GenJetPhiMax);
  histGenJetPhi->Sumw2();
  histGenJetPhi->GetXaxis()->SetTitle("GenJet #phi");
  histGenJetPhi->GetYaxis()->SetTitle("Entries");

  
  histGenJetPtNoRec = new TH1D("histGenJetPtNoRec","histGenJetPtNoRec",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtNoRec->Sumw2();
  histGenJetPtNoRec->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (NoRec)");
  histGenJetPtNoRec->GetYaxis()->SetTitle("Entries");

  histGenJetPtUnknownRec = new TH1D("histGenJetPtUnknownRec","histGenJetPtUnknownRec",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtUnknownRec->Sumw2();
  histGenJetPtUnknownRec->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (UnknownRec)");
  histGenJetPtUnknownRec->GetYaxis()->SetTitle("Entries");
  
  histGenJetPtLight = new TH1D("histGenJetPtLight","histGenJetPtLight",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtLight->Sumw2();
  histGenJetPtLight->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (u,d,s)");
  histGenJetPtLight->GetYaxis()->SetTitle("Entries");


  histGenJetPtUp = new TH1D("histGenJetPtUp","histGenJetPtUp",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtUp->Sumw2();
  histGenJetPtUp->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (u)");
  histGenJetPtUp->GetYaxis()->SetTitle("Entries");


  histGenJetPtDown = new TH1D("histGenJetPtDown","histGenJetPtDown",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtDown->Sumw2();
  histGenJetPtDown->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (d)");
  histGenJetPtDown->GetYaxis()->SetTitle("Entries");


  histGenJetPtStrange = new TH1D("histGenJetPtStrange","histGenJetPtStrange",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtStrange->Sumw2();
  histGenJetPtStrange->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (s)");
  histGenJetPtStrange->GetYaxis()->SetTitle("Entries");

  histGenJetPtCharm = new TH1D("histGenJetPtCharm","histGenJetPtCharm",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtCharm->Sumw2();
  histGenJetPtCharm->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (c)");
  histGenJetPtCharm->GetYaxis()->SetTitle("Entries");
  
  
  histGenJetPtBeauty = new TH1D("histGenJetPtBeauty","histGenJetPtBeauty",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtBeauty->Sumw2();
  histGenJetPtBeauty->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (b)");
  histGenJetPtBeauty->GetYaxis()->SetTitle("Entries");
  
  
  histGenJetPtGluon = new TH1D("histGenJetPtGluon","histGenJetPtGluon",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtGluon->Sumw2();
  histGenJetPtGluon->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (g)");
  histGenJetPtGluon->GetYaxis()->SetTitle("Entries");
  
  hist_GenMaster_GenJetPt_Flavour= new TH2D("hist_GenMaster_GenJetPt_Flavour","hist_GenMaster_GenJetPt_Flavour",NBinsGenJetPt,GenJetPtMin,GenJetPtMax,NFlavour,FlavourMin,FlavourMax);
  hist_GenMaster_GenJetPt_Flavour->Sumw2();
  hist_GenMaster_GenJetPt_Flavour->GetXaxis()->SetTitle("Gen Jet Pt (GeV/c)");
  hist_GenMaster_GenJetPt_Flavour->GetYaxis()->SetTitle("Jet Flavour");

  
  //Gen Muon Histograms
  // All the Gen Muons
  hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi = new TH3D("hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi","hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi",NBinsGenMuEta,GenMuEtaMin,GenMuEtaMax,NBinsGenMuPt,GenMuPtMin,GenMuPtMax,NBinsGenMuPhi,GenMuPhiMin,GenMuPhiMax);
  hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi->Sumw2();
  hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi->GetXaxis()->SetTitle("Gen Mu #eta");
  hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi->GetYaxis()->SetTitle("Gen Mu p_{T} (GeV/c)");
  hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi->GetZaxis()->SetTitle("Gen Mu #phi");

  //Gen Muons matched to Gen Jets
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi = new TH3D("hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi","hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi",NBinsGenMuEta,GenMuEtaMin,GenMuEtaMax,NBinsGenMuPt,GenMuPtMin,GenMuPtMax,NBinsGenMuPhi,GenMuPhiMin,GenMuPhiMax);
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->Sumw2();
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->GetXaxis()->SetTitle("Gen Jet Matched Gen Mu #eta");
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->GetYaxis()->SetTitle("Gen Jet Matched Gen Mu p_{T} (GeV/c)");
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->GetZaxis()->SetTitle("Gen Jet Matched Gen Mu #phi");

  //Gen Muons matched to Reco Muon
  hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi = new TH3D("hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi","hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi",NBinsGenMuEta,GenMuEtaMin,GenMuEtaMax,NBinsGenMuPt,GenMuPtMin,GenMuPtMax,NBinsGenMuPhi,GenMuPhiMin,GenMuPhiMax);
  hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi->Sumw2();
  hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi->GetXaxis()->SetTitle("Rec Mu Matched Gen Mu #eta");
  hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi->GetYaxis()->SetTitle("Rec Mu Matched Gen Mu p_{T} (GeV/c)");
  hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi->GetZaxis()->SetTitle("Rec Mu Matched Gen Mu #phi");


  //All the Gen Muons (can be used to test 3D projections)

  histGenMuonPt = new TH1D("histGenMuonPt","histGenMuonPt",NBinsGenMuPt,GenMuPtMin,GenMuPtMax);
  histGenMuonPt->Sumw2();
  histGenMuonPt->GetXaxis()->SetTitle("GenMuon Pt (GeV/c)");
  histGenMuonPt->GetYaxis()->SetTitle("Entries");
  
  histGenMuonEta = new TH1D("histGenMuonEta","histGenMuonEta",NBinsGenMuEta,GenMuEtaMin,GenMuEtaMax);
  histGenMuonEta->Sumw2();
  histGenMuonEta->GetXaxis()->SetTitle("GenMuon #eta (GeV/c)");
  histGenMuonEta->GetYaxis()->SetTitle("Entries");


  histGenMuonPhi = new TH1D("histGenMuonPhi","histGenMuonPhi",NBinsGenMuPhi,GenMuPhiMin,GenMuPhiMax);
  histGenMuonPhi->Sumw2();
  histGenMuonPhi->GetXaxis()->SetTitle("GenMuon #phi (GeV/c)");
  histGenMuonPhi->GetYaxis()->SetTitle("Entries");

  //Gen Dimuon histograms
  histGenDiMuonInvMass = new TH1D("histGenDiMuonInvMass","histGenDiMuonInvMass",100,0,100);
  histGenDiMuonInvMass->Sumw2();
  histGenDiMuonInvMass->GetXaxis()->SetTitle("GenDiMuon InvMass (GeV/c)");
  histGenDiMuonInvMass->GetYaxis()->SetTitle("Entries");


  histGenDiMuonInvMassLow = new TH1D("histGenDiMuonInvMassLow","histGenDiMuonInvMassLow",200,2.0,4.5);
  histGenDiMuonInvMassLow->GetXaxis()->SetTitle("GenDiMuon InvMassLow (GeV/c)");
  histGenDiMuonInvMassLow->GetYaxis()->SetTitle("Entries");


  histGenDiMuonInvMassInt = new TH1D("histGenDiMuonInvMassInt","histGenDiMuonInvMassInt",200,8.0,14.0);
  histGenDiMuonInvMassInt->GetXaxis()->SetTitle("GenDiMuon InvMassInt (GeV/c)");
  histGenDiMuonInvMassInt->GetYaxis()->SetTitle("Entries");
  

  histGenDiMuonPt = new TH1D("histGenDiMuonPt","histGenDiMuonPt",100,0,100);
  histGenDiMuonPt->GetXaxis()->SetTitle("GenDiMuon Pt (GeV/c)");
  histGenDiMuonPt->GetYaxis()->SetTitle("Entries");

  histGenDiMuonRapidity = new TH1D("histGenDiMuonRapidity","histGenDiMuonRapidity",100,-5,5);
  histGenDiMuonRapidity->GetXaxis()->SetTitle("GenDiMuon #eta (GeV/c)");
  histGenDiMuonRapidity->GetYaxis()->SetTitle("Entries");


  histGenDiMuonPhi = new TH1D("histGenDiMuonPhi","histGenDiMuonPhi",100,-Pi,Pi);
  histGenDiMuonPhi->GetXaxis()->SetTitle("GenDiMuon #phi (GeV/c)");
  histGenDiMuonPhi->GetYaxis()->SetTitle("Entries");

  //Histograms with GenMuon + Gen Jet Combination  
  histGenMuonGenJetDR = new TH1D("histGenMuonGenJetDR","histGenMuonGenJetDR",100,0,10);
  histGenMuonGenJetDR->GetXaxis()->SetTitle("GenMuon-Jet #Delta R");
  histGenMuonGenJetDR->GetYaxis()->SetTitle("Entries");
  
  
  histGenMuonGenJetDPhi = new TH1D("histGenMuonGenJetDPhi","histGenMuonGenJetDPhi",nDeltaPhiBinsJetMuon,minDeltaPhiJetMuon,maxDeltaPhiJetMuon);
  histGenMuonGenJetDPhi->GetXaxis()->SetTitle("GenMuon-Jet #Delta #Phi");
  histGenMuonGenJetDPhi->GetYaxis()->SetTitle("Entries");
  

  histGenMuonGenJetPtTotal = new TH1D("histGenMuonGenJetPtTotal","histGenMuonGenJetPtTotal",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtTotal->GetXaxis()->SetTitle("GenMuonGenJet Pt (GeV/c) (u,d,s)");
  histGenMuonGenJetPtTotal->GetYaxis()->SetTitle("Entries");
  
  
  histGenMuonGenJetPtLight = new TH1D("histGenMuonGenJetPtLight","histGenMuonGenJetPtLight",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtLight->GetXaxis()->SetTitle("GenMuonGenJet Pt (GeV/c) (u,d,s)");
  histGenMuonGenJetPtLight->GetYaxis()->SetTitle("Entries");

  
  histGenMuonGenJetPtUp = new TH1D("histGenMuonGenJetPtUp","histGenMuonGenJetPtUp",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtUp->GetXaxis()->SetTitle("Jet Pt (GeV/c) (u)");
  histGenMuonGenJetPtUp->GetYaxis()->SetTitle("Entries");


  histGenMuonGenJetPtDown = new TH1D("histGenMuonGenJetPtDown","histGenMuonGenJetPtDown",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtDown->GetXaxis()->SetTitle("Jet Pt (GeV/c) (d)");
  histGenMuonGenJetPtDown->GetYaxis()->SetTitle("Entries");


  histGenMuonGenJetPtStrange = new TH1D("histGenMuonGenJetPtStrange","histGenMuonGenJetPtStrange",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtStrange->GetXaxis()->SetTitle("Jet Pt (GeV/c) (s)");
  histGenMuonGenJetPtStrange->GetYaxis()->SetTitle("Entries");


  histGenMuonGenJetPtCharm = new TH1D("histGenMuonGenJetPtCharm","histGenMuonGenJetPtCharm",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtCharm->GetXaxis()->SetTitle("GenMuonGenJet Pt (GeV/c) (c)");
  histGenMuonGenJetPtCharm->GetYaxis()->SetTitle("Entries");


  histGenMuonGenJetPtBeauty = new TH1D("histGenMuonGenJetPtBeauty","histGenMuonGenJetPtBeauty",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtBeauty->GetXaxis()->SetTitle("GenMuonGenJet Pt (GeV/c) (b)");
  histGenMuonGenJetPtBeauty->GetYaxis()->SetTitle("Entries");

  
  histGenMuonGenJetPtGluon = new TH1D("histGenMuonGenJetPtGluon","histGenMuonGenJetPtGluon",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtGluon->GetXaxis()->SetTitle("GenMuonGenJet Pt (GeV/c) (g)");
  histGenMuonGenJetPtGluon->GetYaxis()->SetTitle("Entries");

  // 3D histogram of Gen Jet pT, Gen Mu pT and Gen Jet Flavour
  hist_GenMaster_GenJetPt_GenMuPt_Flavour = new TH3D("hist_GenMaster_GenJetPt_GenMuPt_Flavour","hist_GenMaster_GenJetPt_GenMuPt_Flavour",NBinsGenJetPt,GenJetPtMin,GenJetPtMax,NBinsGenMuPt,GenMuPtMin,GenMuPtMax,NFlavour,FlavourMin,FlavourMax);
  hist_GenMaster_GenJetPt_GenMuPt_Flavour->GetXaxis()->SetTitle("Gen Jet Pt (GeV/c)");
  hist_GenMaster_GenJetPt_GenMuPt_Flavour->GetYaxis()->SetTitle("Gen #mu Pt (GeV/c)");
  hist_GenMaster_GenJetPt_GenMuPt_Flavour->GetZaxis()->SetTitle("Jet Flavour");


  
    //Gen Muon pT relative histogram
  //3D histogram of Gen Jet Pt, Gen Muon Pt relative, Gen Jet Flavour
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour = new TH3D("hist_GenMaster_GenJetPt_GenMuPtRel_Flavour","hist_GenMaster_GenJetPt_GenMuPtRel_Flavour",NBinsGenJetPt,GenJetPtMin,GenJetPtMax,NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax,NFlavour,FlavourMin,FlavourMax);
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->GetXaxis()->SetTitle("Gen Jet p_{T} (GeV/c)");
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->GetYaxis()->SetTitle("Gen #mu p_{T}-Rel (GeV/c)");
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->GetZaxis()->SetTitle("Jet Flavour");




  
  //========= Reconstructed Jet Histograms 
  histJetPt = new TH1D("histJetPt","histJetPt",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPt->GetXaxis()->SetTitle("Jet Pt (GeV/c)");
  histJetPt->GetYaxis()->SetTitle("Entries");
  
  histJetEta = new TH1D("histJetEta","histJetEta",NBinsJetEta,JetEtaMin,JetEtaMax);
  histJetEta->GetXaxis()->SetTitle("Jet #eta");
  histJetEta->GetYaxis()->SetTitle("Entries");
  
  histJetPhi = new TH1D("histJetPhi","histJetPhi",NBinsJetPhi,JetPhiMin,JetPhiMax);
  histJetPhi->GetXaxis()->SetTitle("Jet #phi");
  histJetPhi->GetYaxis()->SetTitle("Entries");

  
  histJetPtUnknown = new TH1D("histJetPtUnknown","histJetPtUnknown",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtUnknown->GetXaxis()->SetTitle("Jet Pt (GeV/c) (Unknown)");
  histJetPtUnknown->GetYaxis()->SetTitle("Entries");
  
  
  histJetPtLight = new TH1D("histJetPtLight","histJetPtLight",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtLight->GetXaxis()->SetTitle("Jet Pt (GeV/c) (u,d,s)");
  histJetPtLight->GetYaxis()->SetTitle("Entries");


  histJetPtUp = new TH1D("histJetPtUp","histJetPtUp",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtUp->GetXaxis()->SetTitle("Jet Pt (GeV/c) (u)");
  histJetPtUp->GetYaxis()->SetTitle("Entries");


  histJetPtDown = new TH1D("histJetPtDown","histJetPtDown",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtDown->GetXaxis()->SetTitle("Jet Pt (GeV/c) (d)");
  histJetPtDown->GetYaxis()->SetTitle("Entries");


  histJetPtStrange = new TH1D("histJetPtStrange","histJetPtStrange",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtStrange->GetXaxis()->SetTitle("Jet Pt (GeV/c) (s)");
  histJetPtStrange->GetYaxis()->SetTitle("Entries");

  histJetPtCharm = new TH1D("histJetPtCharm","histJetPtCharm",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtCharm->GetXaxis()->SetTitle("Jet Pt (GeV/c) (c)");
  histJetPtCharm->GetYaxis()->SetTitle("Entries");
  
  
  histJetPtBeauty = new TH1D("histJetPtBeauty","histJetPtBeauty",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtBeauty->GetXaxis()->SetTitle("Jet Pt (GeV/c) (b)");
  histJetPtBeauty->GetYaxis()->SetTitle("Entries");
  
  
  histJetPtGluon = new TH1D("histJetPtGluon","histJetPtGluon",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtGluon->GetXaxis()->SetTitle("Jet Pt (GeV/c) (g)");
  histJetPtGluon->GetYaxis()->SetTitle("Entries");

  
  //2D Histo of Jet Pt and Flavour
  hist_Master_JetPt_Flavour = new TH2D("hist_Master_JetPt_Flavour","hist_Master_JetPt_Flavour",NBinsJetPt,JetPtMin,JetPtMax,NFlavour,FlavourMin,FlavourMax);
  hist_Master_JetPt_Flavour->GetXaxis()->SetTitle(" Jet Pt (GeV/c)");
  hist_Master_JetPt_Flavour->GetYaxis()->SetTitle("Jet Flavour");
  
  // main analysis 3D histogram
  //Jet Pt, Muon Pt and Flavour
  hist_Master_JetPt_MuPt_Flavour = new TH3D("hist_Master_JetPt_MuPt_Flavour","hist_Master_JetPt_MuPt_Flavour",NBinsJetPt,JetPtMin,JetPtMax,NBinsMuPt,MuPtMin,MuPtMax, NFlavour,FlavourMin,FlavourMax);
  hist_Master_JetPt_MuPt_Flavour->GetXaxis()->SetTitle(" Jet p_{T} (GeV/c)");
  hist_Master_JetPt_MuPt_Flavour->GetYaxis()->SetTitle(" #mu p_{T} (GeV/c)");
  hist_Master_JetPt_MuPt_Flavour->GetZaxis()->SetTitle("Jet Flavour");
  
  //Jet Pt, Muon Pt-rel and Flavour
  hist_Master_JetPt_MuPtRel_Flavour = new TH3D("hist_Master_JetPt_MuPtRel_Flavour","hist_Master_JetPt_MuPtRel_Flavour", NBinsJetPt,JetPtMin,JetPtMax,NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax, NFlavour,FlavourMin,FlavourMax);
  hist_Master_JetPt_MuPtRel_Flavour->GetXaxis()->SetTitle(" Jet p_{T} (GeV/c)");
  hist_Master_JetPt_MuPtRel_Flavour->GetYaxis()->SetTitle(" #mu p_{T}-Rel (GeV/c)");
  hist_Master_JetPt_MuPtRel_Flavour->GetZaxis()->SetTitle("Jet Flavour");
  


  hist_Master_JetPt_MuPt_Flavour_ModCuts = new TH3D("hist_Master_JetPt_MuPt_Flavour_ModCuts","hist_Master_JetPt_MuPt_Flavour_ModCuts",NBinsJetPt,JetPtMin,JetPtMax,NBinsMuPt,MuPtMin,MuPtMax, NFlavour,FlavourMin,FlavourMax);
  hist_Master_JetPt_MuPt_Flavour_ModCuts->GetXaxis()->SetTitle(" Jet p_{T} (GeV/c)");
  hist_Master_JetPt_MuPt_Flavour_ModCuts->GetYaxis()->SetTitle(" #mu p_{T} (GeV/c)");
  hist_Master_JetPt_MuPt_Flavour_ModCuts->GetZaxis()->SetTitle("Jet Flavour");


  
  
  /**********************************************************************************************************************/
  /**********************************************************************************************************************/
  // CSV v2 performance for the Jets in MC
  /**********************************************************************************************************************/
  /**********************************************************************************************************************/

  //CSV values for all Jets
  histJetCSV = new TH1D("histJetCSV","histJetCSV",NBinsJetCSV,JetCSVMin,JetCSVMax);
  histJetCSV->GetXaxis()->SetTitle("Jet CSV v2");
  histJetCSV->GetXaxis()->SetTitle("Entries");

  //CSV values for muon Jets
  histMuonJetCSV = new TH1D("histMuonJetCSV","histMuonJetCSV",NBinsJetCSV,JetCSVMin,JetCSVMax);
  histMuonJetCSV->GetXaxis()->SetTitle("Muon Jet CSV v2");
  histMuonJetCSV->GetXaxis()->SetTitle("Entries");

  //CSV, JetPt, Flv
  hist_Master_JetCSV_JetPt_Flavour = new TH3D("hist_Master_JetCSV_JetPt_Flavour","hist_Master_JetCSV_JetPt_Flavour", NBinsJetCSV, JetCSVMin, JetCSVMax, NBinsJetPt, JetPtMin, JetPtMax, NFlavour,FlavourMin,FlavourMax);
  hist_Master_JetCSV_JetPt_Flavour->GetXaxis()->SetTitle("Jet CSV v2");
  hist_Master_JetCSV_JetPt_Flavour->GetYaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->SetTitle("Jet Flavour");

  
  //Muon Jet (CSV, JetPt, Flv)
  hist_Master_MuonJetCSV_MuonJetPt_Flavour = new TH3D("hist_Master_MuonJetCSV_MuonJetPt_Flavour","hist_Master_MuonJetCSV_MuonJetPt_Flavour", NBinsJetCSV, JetCSVMin, JetCSVMax, NBinsJetPt, JetPtMin, JetPtMax, NFlavour,FlavourMin,FlavourMax);
  hist_Master_MuonJetCSV_MuonJetPt_Flavour->GetXaxis()->SetTitle("MuonJet CSV v2");
  hist_Master_MuonJetCSV_MuonJetPt_Flavour->GetYaxis()->SetTitle("MuonJet p_{T} (GeV/c)");
  hist_Master_MuonJetCSV_MuonJetPt_Flavour->GetZaxis()->SetTitle("MuonJet Flavour");


  // Jet CSV, MuPt Rel, Flv
  hist_Master_JetCSV_MuPtRel_Flavour = new TH3D("hist_Master_JetCSV_MuPtRel_Flavour","hist_Master_JetCSV_MuPtRel_Flavour", NBinsJetCSV, JetCSVMin, JetCSVMax, NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax, NFlavour,FlavourMin,FlavourMax);
  
  hist_Master_JetCSV_MuPtRel_Flavour->SetTitle("Jet CSV v2");
  hist_Master_JetCSV_MuPtRel_Flavour->GetYaxis()->SetTitle("#mu p_{T}-Rel (GeV/c)");
  hist_Master_JetCSV_MuPtRel_Flavour->GetZaxis()->SetTitle("Jet Flavour");


  //muon pT rel
  histMuonPtRel = new TH1D("histMuonPtRel","histMuonPtRel",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  histMuonPtRel->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  histMuonPtRel->GetYaxis()->SetTitle("Entries");

  //muon pT rel (CSV Tag)
  histMuonPtRelCSVTag = new TH1D("histMuonPtRelCSVTag","histMuonPtRelCSVTag",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  histMuonPtRelCSVTag->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  histMuonPtRelCSVTag->GetYaxis()->SetTitle("Entries");
  
  //muon pT rel (CSV Veto)
  histMuonPtRelCSVVeto = new TH1D("histMuonPtRelCSVVeto","histMuonPtRelCSVVeto",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  histMuonPtRelCSVVeto->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  histMuonPtRelCSVVeto->GetYaxis()->SetTitle("Entries");
  

   //Adding bins for a four dimensonal histogram
  //1.CSV
  //2.pT^Rel
  //3.Flavour
  //4.MuonPt (may be we need to do it to 150)?
  hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt = new THnSparseD("hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt","hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",NDimension, NBins, xmin, xmax);
  //hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->Sumw2();
  hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->GetAxis(0)->SetTitle("Jet CSV v2");
  hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->GetAxis(1)->SetTitle("#mu p_{T}-Rel (GeV/c)");
  hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->GetAxis(2)->SetTitle("Jet Flavour");
  hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->GetAxis(3)->SetTitle("#mu p_{T} (GeV/c)");



  hsparse_JetPt_MuPt_Flavour_MuChi2NDF_MuDR_MuMCMatch = new THnSparseD("hsparse_JetPt_MuPt_Flavour_MuChi2NDF_MuDR_MuMCMatch","hsparse_JetPt_MuPt_Flavour_MuChi2NDF_MuDR_MuMCMatch",NDimension_MuID, NBins_MuID, xmin_MuID, xmax_MuID);
  hsparse_JetPt_MuPt_Flavour_MuChi2NDF_MuDR_MuMCMatch->GetAxis(0)->SetTitle("Jet p_{T} (GeV/c)");
  hsparse_JetPt_MuPt_Flavour_MuChi2NDF_MuDR_MuMCMatch->GetAxis(1)->SetTitle("#mu  p_{T} (GeV/c)");
  hsparse_JetPt_MuPt_Flavour_MuChi2NDF_MuDR_MuMCMatch->GetAxis(2)->SetTitle("Jet Flavour");
  hsparse_JetPt_MuPt_Flavour_MuChi2NDF_MuDR_MuMCMatch->GetAxis(3)->SetTitle("#mu #chi^{2}/NDF");
  hsparse_JetPt_MuPt_Flavour_MuChi2NDF_MuDR_MuMCMatch->GetAxis(4)->SetTitle("#mu #sqrt{(d0)^2+(dz)^2)}");
  hsparse_JetPt_MuPt_Flavour_MuChi2NDF_MuDR_MuMCMatch->GetAxis(5)->SetTitle("#mu-Gen #mu Match");

  
  //===========================================================================//
  //========================== reco muon histos ===============================//
  //===========================================================================//
  //All the muons matched to Jet
  hist_Master_MuEta_MuPt_MuPhi = new TH3D("hist_Master_MuEta_MuPt_MuPhi","hist_Master_MuEta_MuPt_MuPhi",NBinsMuEta,MuEtaMin,MuEtaMax,NBinsMuPt,MuPtMin,MuPtMax,NBinsMuPhi,MuPhiMin,MuPhiMax);
  hist_Master_MuEta_MuPt_MuPhi->Sumw2();
  hist_Master_MuEta_MuPt_MuPhi->GetXaxis()->SetTitle("Muon #eta");
  hist_Master_MuEta_MuPt_MuPhi->GetYaxis()->SetTitle("Muon p_{T} (GeV/c)");
  hist_Master_MuEta_MuPt_MuPhi->GetZaxis()->SetTitle("Muon #phi");
  
  
  //All the reco muons (pass the quality cuts or quality cuts + MC matching if applied) 
  histMuonPt = new TH1D("histMuonPt","histMuonPt",NBinsMuPt,MuPtMin,MuPtMax);
  histMuonPt->Sumw2();
  histMuonPt->GetXaxis()->SetTitle("Muon Pt (GeV/c)");
  histMuonPt->GetYaxis()->SetTitle("Entries");
  
  histMuonEta = new TH1D("histMuonEta","histMuonEta",NBinsMuEta,MuEtaMin,MuEtaMax);
  histMuonEta->Sumw2();
  histMuonEta->GetXaxis()->SetTitle("Muon #eta");
  histMuonEta->GetYaxis()->SetTitle("Entries");

  histMuonPhi = new TH1D("histMuonPhi","histMuonPhi",NBinsMuPhi,MuPhiMin,MuPhiMax);
  histMuonPhi->Sumw2();
  histMuonPhi->GetXaxis()->SetTitle("Muon #phi");
  histMuonPhi->GetYaxis()->SetTitle("Entries");


  //Gen Muon matched reco muons (reco muon variables are filled)
  histMatchedMuonPt = new TH1D("histMatchedMuonPt","histMatchedMuonPt",NBinsMuPt,MuPtMin,MuPtMax);
  histMatchedMuonPt->Sumw2();
  histMatchedMuonPt->GetXaxis()->SetTitle("MatchedMuon Pt (GeV/c)");
  histMatchedMuonPt->GetYaxis()->SetTitle("Entries");
  
  histMatchedMuonEta = new TH1D("histMatchedMuonEta","histMatchedMuonEta",NBinsMuEta,MuEtaMin,MuEtaMax);
  histMatchedMuonEta->Sumw2();
  histMatchedMuonEta->GetXaxis()->SetTitle("MatchedMuon #eta");
  histMatchedMuonEta->GetYaxis()->SetTitle("Entries");


  histMatchedMuonPhi = new TH1D("histMatchedMuonPhi","histMatchedMuonPhi",NBinsMuPhi,MuPhiMin,MuPhiMax);
  histMatchedMuonPhi->Sumw2();
  histMatchedMuonPhi->GetXaxis()->SetTitle("MatchedMuon #phi");
  histMatchedMuonPhi->GetYaxis()->SetTitle("Entries");



  //reco matched gen muons (gen muon variables are filled)
  histRecoMatchedGenMuonPt = new TH1D("histRecoMatchedGenMuonPt","histRecoMatchedGenMuonPt",NBinsMuPt,MuPtMin,MuPtMax);
  histRecoMatchedGenMuonPt->Sumw2();
  histRecoMatchedGenMuonPt->GetXaxis()->SetTitle("RecoMatchedGenMuon Pt (GeV/c)");
  histRecoMatchedGenMuonPt->GetYaxis()->SetTitle("Entries");
  
  histRecoMatchedGenMuonEta = new TH1D("histRecoMatchedGenMuonEta","histRecoMatchedGenMuonEta",NBinsMuEta,MuEtaMin,MuEtaMax);
  histRecoMatchedGenMuonEta->Sumw2();
  histRecoMatchedGenMuonEta->GetXaxis()->SetTitle("RecoMatchedGenMuon #eta");
  histRecoMatchedGenMuonEta->GetYaxis()->SetTitle("Entries");

  histRecoMatchedGenMuonPhi = new TH1D("histRecoMatchedGenMuonPhi","histRecoMatchedGenMuonPhi",NBinsMuPhi,MuPhiMin,MuPhiMax);
  histRecoMatchedGenMuonPhi->Sumw2();
  histRecoMatchedGenMuonPhi->GetXaxis()->SetTitle("RecoMatchedGenMuon #phi");
  histRecoMatchedGenMuonPhi->GetYaxis()->SetTitle("Entries");
  
  histGenMuRecMuDRVsDPt = new TH2D("histGenMuRecMuDRVsDPt","histGenMuRecMuDRVsDPt",100,0.0,10.0,100,0.0,10.0);
  histGenMuRecMuDRVsDPt->GetXaxis()->SetTitle("Muon-Gen Muon #Delta R");
  histGenMuRecMuDRVsDPt->GetYaxis()->SetTitle("Muon-Gen Muon #Delta Pt");
  
  histGenMuRecMuDRVsPt = new TH2D("histGenMuRecMuDRVsPt","histGenMuRecMuDRVsPt",100,0,10,NBinsMuPt,MuPtMin,MuPtMax);
  histGenMuRecMuDRVsPt->GetXaxis()->SetTitle("Muon-Gen Muon #Delta R");
  histGenMuRecMuDRVsPt->GetYaxis()->SetTitle("Muon p_{T} (GeV/c)");
  
  histGenMuRecMuDRVsEta = new TH2D("histGenMuRecMuDRVsEta","histGenMuRecMuDRVsEta",100,0,10,NBinsMuEta,MuEtaMin,MuEtaMax);
  histGenMuRecMuDRVsEta->GetXaxis()->SetTitle("Muon-Gen Muon #Delta R");
  histGenMuRecMuDRVsEta->GetYaxis()->SetTitle("Muon #eta");
  
  histGenMuRecMuDRVsPhi = new TH2D("histGenMuRecMuDRVsPhi","histGenMuRecMuDRVsPhi",100,0,10,NBinsMuPhi,MuPhiMin,MuPhiMax);
  histGenMuRecMuDRVsPhi->GetXaxis()->SetTitle("Muon-Gen Muon #Delta R");
  histGenMuRecMuDRVsPhi->GetYaxis()->SetTitle("Muon #phi (GeV/c)");

  // rec dimuon histograms
  histDiMuonInvMass = new TH1D("histDiMuonInvMass","histDiMuonInvMass",100,0,100);
  histDiMuonInvMass->GetXaxis()->SetTitle("DiMuon InvMass (GeV/c)");
  histDiMuonInvMass->GetYaxis()->SetTitle("Entries");


  histDiMuonInvMassLow = new TH1D("histDiMuonInvMassLow","histDiMuonInvMassLow",200,2.0,4.5);
  histDiMuonInvMassLow->GetXaxis()->SetTitle("DiMuon InvMassLow (GeV/c)");
  histDiMuonInvMassLow->GetYaxis()->SetTitle("Entries");


  histDiMuonInvMassInt = new TH1D("histDiMuonInvMassInt","histDiMuonInvMassInt",200,8.0,14.0);
  histDiMuonInvMassInt->GetXaxis()->SetTitle("DiMuon InvMassInt (GeV/c)");
  histDiMuonInvMassInt->GetYaxis()->SetTitle("Entries");
  

  histDiMuonPt = new TH1D("histDiMuonPt","histDiMuonPt",100,0,100);
  //histDiMuonPt->Sumw2();
  histDiMuonPt->GetXaxis()->SetTitle("DiMuon Pt (GeV/c)");
  histDiMuonPt->GetYaxis()->SetTitle("Entries");

  histDiMuonRapidity = new TH1D("histDiMuonRapidity","histDiMuonRapidity",100,-5,5);
  histDiMuonRapidity->GetXaxis()->SetTitle("DiMuon #eta (GeV/c)");
  histDiMuonRapidity->GetYaxis()->SetTitle("Entries");


  histDiMuonPhi = new TH1D("histDiMuonPhi","histDiMuonPhi",100,-Pi,Pi);
  histDiMuonPhi->GetXaxis()->SetTitle("DiMuon #phi (GeV/c)");
  histDiMuonPhi->GetYaxis()->SetTitle("Entries");



  //reco Jet + reco muon hsitograms 
  histMuonJetDR = new TH1D("histMuonJetDR","histMuonJetDR",100,0,10);
  histMuonJetDR->GetXaxis()->SetTitle("Muon-Jet #Delta R");
  histMuonJetDR->GetYaxis()->SetTitle("Entries");

  histMuonJetDPhi = new TH1D("histMuonJetDPhi","histMuonJetDPhi",nDeltaPhiBinsJetMuon,minDeltaPhiJetMuon,maxDeltaPhiJetMuon);
  histMuonJetDPhi->GetXaxis()->SetTitle("Muon-Jet #Delta #Phi");
  histMuonJetDPhi->GetYaxis()->SetTitle("Entries");

  histMuonJetPtTotal = new TH1D("histMuonJetPtTotal","histMuonJetPtTotal",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtTotal->GetXaxis()->SetTitle("MuonJet Pt (GeV/c) (u,d,s)");
  histMuonJetPtTotal->GetYaxis()->SetTitle("Entries");
  
  histMuonJetPtLight = new TH1D("histMuonJetPtLight","histMuonJetPtLight",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtLight->GetXaxis()->SetTitle("MuonJet Pt (GeV/c) (u,d,s)");
  histMuonJetPtLight->GetYaxis()->SetTitle("Entries");
  
  
  histMuonJetPtUp = new TH1D("histMuonJetPtUp","histMuonJetPtUp",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtUp->GetXaxis()->SetTitle("Jet Pt (GeV/c) (u)");
  histMuonJetPtUp->GetYaxis()->SetTitle("Entries");


  histMuonJetPtDown = new TH1D("histMuonJetPtDown","histMuonJetPtDown",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtDown->GetXaxis()->SetTitle("Jet Pt (GeV/c) (d)");
  histMuonJetPtDown->GetYaxis()->SetTitle("Entries");


  histMuonJetPtStrange = new TH1D("histMuonJetPtStrange","histMuonJetPtStrange",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtStrange->GetXaxis()->SetTitle("Jet Pt (GeV/c) (s)");
  histMuonJetPtStrange->GetYaxis()->SetTitle("Entries");

  histMuonJetPtCharm = new TH1D("histMuonJetPtCharm","histMuonJetPtCharm",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtCharm->GetXaxis()->SetTitle("MuonJet Pt (GeV/c) (c)");
  histMuonJetPtCharm->GetYaxis()->SetTitle("Entries");


  histMuonJetPtBeauty = new TH1D("histMuonJetPtBeauty","histMuonJetPtBeauty",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtBeauty->GetXaxis()->SetTitle("MuonJet Pt (GeV/c) (b)");
  histMuonJetPtBeauty->GetYaxis()->SetTitle("Entries");

  histMuonJetPtGluon = new TH1D("histMuonJetPtGluon","histMuonJetPtGluon",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtGluon->GetXaxis()->SetTitle("MuonJet Pt (GeV/c) (g)");
  histMuonJetPtGluon->GetYaxis()->SetTitle("Entries");

  histMatchedMuonsDR04Size = new TH1D("histMatchedMuonsDR04Size","histMatchedMuonsDR04Size", NBinsMatchedMuonsDR04Size,MatchedMuonsDR04SizeMin,MatchedMuonsDR04SizeMax);
  histMatchedMuonsDR04Size->GetXaxis()->SetTitle("MatchedMuonsDR04 Pt (GeV/c)");
  histMatchedMuonsDR04Size->GetYaxis()->SetTitle("Entries");
  
  
  histMatchedMuonsDR04Pt = new TH1D("histMatchedMuonsDR04Pt","histMatchedMuonsDR04Pt",NBinsMuPt,MuPtMin,MuPtMax);
  histMatchedMuonsDR04Pt->GetXaxis()->SetTitle("MatchedMuonsDR04 Pt (GeV/c)");
  histMatchedMuonsDR04Pt->GetYaxis()->SetTitle("Entries");
  
  histMatchedMuonsDR04Eta = new TH1D("histMatchedMuonsDR04Eta","histMatchedMuonsDR04Eta",NBinsMuEta,MuEtaMin,MuEtaMax);
  histMatchedMuonsDR04Eta->GetXaxis()->SetTitle("MatchedMuonsDR04 #eta (GeV/c)");
  histMatchedMuonsDR04Eta->GetYaxis()->SetTitle("Entries");
  
  
  histMatchedMuonsDR04Phi = new TH1D("histMatchedMuonsDR04Phi","histMatchedMuonsDR04Phi",NBinsMuPhi,MuPhiMin,MuPhiMax);
  histMatchedMuonsDR04Phi->GetXaxis()->SetTitle("MatchedMuonsDR04 #phi (GeV/c)");
  histMatchedMuonsDR04Phi->GetYaxis()->SetTitle("Entries");
  
  // Bin 1 corresponds to range [0.0, 30.0]
  // Bin 2 corresponds to range [30.0, 50] etc...
  // Bin 11 corresponds to range [460.0, 540] etc...
  // Bin 12 corresponds to range [540.0, 3000] etc...
  histPtHatBins = new TH1D("EventsPtHatBins","EventsPtHatBins", NBINS,edges);
  histPtHatBins->Sumw2();
  histWPtHatBins = new TH1D("WEventsPtHatBins","WEventsPtHatBins", 100,0.0,600);
  histWPtHatBins->Sumw2();

}


void JetAnalyzer::InitMuIDHist()
{

  //==================================================================================================//
  //==================== Adding Muon Quality Cut Histograms =========================================//  
  //====== Purpose is to match quality cuts for a muon which have a matched gen muon ===============// 
  //==== and a muon which do not have a matched gen muon, removing MC matching have a big impact ==//
  //====== on Jet Fractions and increases the light flavour contamination ========================//   
  //=============================================================================================//

  //========= There are total 22 Muon ID cuts =============================//

  //1. IsGlobalMuon
  const Int_t NBinsMuonIsGlobal = 5; 
  Double_t MuonIsGlobalMin = -0.5;
  Double_t MuonIsGlobalMax = 4.5;
  
  histMuonIsGlobal = new TH1D("histMuonIsGlobal","histMuonIsGlobal",NBinsMuonIsGlobal,MuonIsGlobalMin,MuonIsGlobalMax);
  histMuonIsGlobal->GetXaxis()->SetTitle("Muon IsGlobal");
  histMuonIsGlobal->GetYaxis()->SetTitle("Entries"); 
  
  //NG --> No Gen Muon
  histNGMuonIsGlobal = new TH1D("histNGMuonIsGlobal","histNGMuonIsGlobal",NBinsMuonIsGlobal,MuonIsGlobalMin,MuonIsGlobalMax);
  histNGMuonIsGlobal->GetXaxis()->SetTitle("NGMuon IsGlobal");
  histNGMuonIsGlobal->GetYaxis()->SetTitle("Entries");

  
  //2. IsTrackerMuon
  const Int_t NBinsMuonIsTracker    = 5;
  Double_t MuonIsTrackerMin = -0.5;
  Double_t MuonIsTrackerMax = 4.5;
  histMuonIsTracker = new TH1D("histMuonIsTracker","histMuonIsTracker",NBinsMuonIsTracker,MuonIsTrackerMin,MuonIsTrackerMax);
  histMuonIsTracker->GetXaxis()->SetTitle("Muon IsTracker");
  histMuonIsTracker->GetYaxis()->SetTitle("Entries");

  //NG --> No Gen Muon
  histNGMuonIsTracker = new TH1D("histNGMuonIsTracker","histNGMuonIsTracker",NBinsMuonIsTracker,MuonIsTrackerMin,MuonIsTrackerMax);
  histNGMuonIsTracker->GetXaxis()->SetTitle("NGMuon IsTracker");
  histNGMuonIsTracker->GetYaxis()->SetTitle("Entries");


  //3. IsPFMuon
  const Int_t NBinsMuonIsPF    = 5;
  Double_t MuonIsPFMin = -0.5;
  Double_t MuonIsPFMax = 4.5;
  histMuonIsPF = new TH1D("histMuonIsPF","histMuonIsPF",NBinsMuonIsPF,MuonIsPFMin,MuonIsPFMax);
  histMuonIsPF->GetXaxis()->SetTitle("Muon IsPF");
  histMuonIsPF->GetYaxis()->SetTitle("Entries");

  //NG --> No Gen Muon
  histNGMuonIsPF = new TH1D("histNGMuonIsPF","histNGMuonIsPF",NBinsMuonIsPF,MuonIsPFMin,MuonIsPFMax);
  histNGMuonIsPF->GetXaxis()->SetTitle("NGMuon IsPF");
  histNGMuonIsPF->GetYaxis()->SetTitle("Entries");  


  //4. IsSTAMuon
  const Int_t NBinsMuonIsSTA    = 5;
  Double_t MuonIsSTAMin = -0.5;
  Double_t MuonIsSTAMax = 4.5;
  histMuonIsSTA = new TH1D("histMuonIsSTA","histMuonIsSTA",NBinsMuonIsSTA,MuonIsSTAMin,MuonIsSTAMax);
  histMuonIsSTA->GetXaxis()->SetTitle("Muon IsSTA");
  histMuonIsSTA->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonIsSTA = new TH1D("histNGMuonIsSTA","histNGMuonIsSTA",NBinsMuonIsSTA,MuonIsSTAMin,MuonIsSTAMax);
  histNGMuonIsSTA->GetXaxis()->SetTitle("NGMuon IsSTA");
  histNGMuonIsSTA->GetYaxis()->SetTitle("Entries");


  //5.mu_D0
  const Int_t NBinsMuonD0    = 100;
  Double_t MuonD0Min = -0.5;
  Double_t MuonD0Max =  0.5;
  histMuonD0 = new TH1D("histMuonD0","histMuonD0",NBinsMuonD0,MuonD0Min,MuonD0Max);
  histMuonD0->GetXaxis()->SetTitle("Muon D0");
  histMuonD0->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonD0 = new TH1D("histNGMuonD0","histNGMuonD0",NBinsMuonD0,MuonD0Min,MuonD0Max);
  histNGMuonD0->GetXaxis()->SetTitle("NGMuon D0");
  histNGMuonD0->GetYaxis()->SetTitle("Entries");

  
  //6.mu_Dz
  const Int_t NBinsMuonDz    = 100;
  Double_t MuonDzMin = -1.0;
  Double_t MuonDzMax = 1.0;
  histMuonDz = new TH1D("histMuonDz","histMuonDz",NBinsMuonDz,MuonDzMin,MuonDzMax);
  histMuonDz->GetXaxis()->SetTitle("Muon Dz");
  histMuonDz->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonDz = new TH1D("histNGMuonDz","histNGMuonDz",NBinsMuonDz,MuonDzMin,MuonDzMax);
  histNGMuonDz->GetXaxis()->SetTitle("NGMuon Dz");
  histNGMuonDz->GetYaxis()->SetTitle("Entries");

      
  //Muon Dxy-Dz 2D Histo 
  histMuonDxyDz = new TH2D("histMuonDxyDz","histMuonDxyDz",NBinsMuonD0,MuonD0Min,MuonD0Max,NBinsMuonDz,MuonDzMin,MuonDzMax);
  histMuonDxyDz->GetXaxis()->SetTitle("Muon D0");
  histMuonDxyDz->GetYaxis()->SetTitle("Muon Dz");
  histMuonDxyDz->GetZaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonDxyDz = new TH2D("histNGMuonDxyDz","histNGMuonDxyDz",NBinsMuonD0,MuonD0Min,MuonD0Max,NBinsMuonDz,MuonDzMin,MuonDzMax);
  histNGMuonDxyDz->GetXaxis()->SetTitle("NGMuon D0");
  histNGMuonDxyDz->GetYaxis()->SetTitle("NGMuon Dz");
  histNGMuonDxyDz->GetZaxis()->SetTitle("Entries");


  
  //Muon Dxy-Dz 2D Histo 

 
  histMuonDR = new TH1D("histMuonDR","histMuonDR",NBinsMuonDR,MuonDRMin,MuonDRMax);
  histMuonDR->GetXaxis()->SetTitle("Muon DR");
  histMuonDR->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  
  histNGMuonDR = new TH1D("histNGMuonDR","histNGMuonDR",NBinsMuonDR,MuonDRMin,MuonDRMax);
  histNGMuonDR->GetXaxis()->SetTitle("NGMuon DR");
  histNGMuonDR->GetYaxis()->SetTitle("Entries");

  
  
  //7.mu_chi2ndf
  histMuonChi2NDF = new TH1D("histMuonChi2NDF","histMuonChi2NDF",NBinsMuonChi2NDF,MuonChi2NDFMin,MuonChi2NDFMax);
  histMuonChi2NDF->GetXaxis()->SetTitle("Muon Chi2NDF");
  histMuonChi2NDF->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonChi2NDF = new TH1D("histNGMuonChi2NDF","histNGMuonChi2NDF",NBinsMuonChi2NDF,MuonChi2NDFMin,MuonChi2NDFMax);
  histNGMuonChi2NDF->GetXaxis()->SetTitle("NGMuon Chi2NDF");
  histNGMuonChi2NDF->GetYaxis()->SetTitle("Entries");

  
  //8.mu_innerD0
  const Int_t NBinsMuonInnerD0    = 100;
  Double_t MuonInnerD0Min = -0.5;
  Double_t MuonInnerD0Max =  0.5;
  histMuonInnerD0 = new TH1D("histMuonInnerD0","histMuonInnerD0",NBinsMuonInnerD0,MuonInnerD0Min,MuonInnerD0Max);
  histMuonInnerD0->GetXaxis()->SetTitle("Muon InnerD0");
  histMuonInnerD0->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonInnerD0 = new TH1D("histNGMuonInnerD0","histNGMuonInnerD0",NBinsMuonInnerD0,MuonInnerD0Min,MuonInnerD0Max);
  histNGMuonInnerD0->GetXaxis()->SetTitle("NGMuon InnerD0");
  histNGMuonInnerD0->GetYaxis()->SetTitle("Entries");
  
  
  //9.mu_innerD0Err
  const Int_t NBinsMuonInnerD0Err    = 100;
  Double_t MuonInnerD0ErrMin = 0.0;
  Double_t MuonInnerD0ErrMax =  1.0;
  histMuonInnerD0Err = new TH1D("histMuonInnerD0Err","histMuonInnerD0Err",NBinsMuonInnerD0Err,MuonInnerD0ErrMin,MuonInnerD0ErrMax);
  histMuonInnerD0Err->GetXaxis()->SetTitle("Muon InnerD0Err");
  histMuonInnerD0Err->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonInnerD0Err = new TH1D("histNGMuonInnerD0Err","histNGMuonInnerD0Err",NBinsMuonInnerD0Err,MuonInnerD0ErrMin,MuonInnerD0ErrMax);
  histNGMuonInnerD0Err->GetXaxis()->SetTitle("NGMuon InnerD0Err");
  histNGMuonInnerD0Err->GetYaxis()->SetTitle("Entries");


  //10.mu_innerDz
  const Int_t NBinsMuonInnerDz    = 100;
  Double_t MuonInnerDzMin = -1.0;
  Double_t MuonInnerDzMax =  1.0;
  histMuonInnerDz = new TH1D("histMuonInnerDz","histMuonInnerDz",NBinsMuonInnerDz,MuonInnerDzMin,MuonInnerDzMax);
  histMuonInnerDz->GetXaxis()->SetTitle("Muon InnerDz");
  histMuonInnerDz->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonInnerDz = new TH1D("histNGMuonInnerDz","histNGMuonInnerDz",NBinsMuonInnerDz,MuonInnerDzMin,MuonInnerDzMax);
  histNGMuonInnerDz->GetXaxis()->SetTitle("NGMuon InnerDz");
  histNGMuonInnerDz->GetYaxis()->SetTitle("Entries");
  
  //11.mu_innerDzErr
  const Int_t NBinsMuonInnerDzErr    = 100;
  Double_t MuonInnerDzErrMin = 0.0;
  Double_t MuonInnerDzErrMax =  10.0;
  histMuonInnerDzErr = new TH1D("histMuonInnerDzErr","histMuonInnerDzErr",NBinsMuonInnerDzErr,MuonInnerDzErrMin,MuonInnerDzErrMax);
  histMuonInnerDzErr->GetXaxis()->SetTitle("Muon InnerDzErr");
  histMuonInnerDzErr->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonInnerDzErr = new TH1D("histNGMuonInnerDzErr","histNGMuonInnerDzErr",NBinsMuonInnerDzErr,MuonInnerDzErrMin,MuonInnerDzErrMax);
  histNGMuonInnerDzErr->GetXaxis()->SetTitle("NGMuon InnerDzErr");
  histNGMuonInnerDzErr->GetYaxis()->SetTitle("Entries");

  
  //12.mu_innerD0/mu_innerD0Err
  const Int_t NBinsMuonInnerD0Norm    = 100;
  Double_t MuonInnerD0NormMin = -5.0;
  Double_t MuonInnerD0NormMax =  5.0;
  histMuonInnerD0Norm = new TH1D("histMuonInnerD0Norm","histMuonInnerD0Norm",NBinsMuonInnerD0Norm,MuonInnerD0NormMin,MuonInnerD0NormMax);
  histMuonInnerD0Norm->GetXaxis()->SetTitle("Muon InnerD0Norm");
  histMuonInnerD0Norm->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonInnerD0Norm = new TH1D("histNGMuonInnerD0Norm","histNGMuonInnerD0Norm",NBinsMuonInnerD0Norm,MuonInnerD0NormMin,MuonInnerD0NormMax);
  histNGMuonInnerD0Norm->GetXaxis()->SetTitle("NGMuon InnerD0Norm");
  histNGMuonInnerD0Norm->GetYaxis()->SetTitle("Entries");

  
  //13.mu_innerDz/mu_innerDzErr
  const Int_t NBinsMuonInnerDzNorm    = 100;
  Double_t MuonInnerDzNormMin = -5.0;
  Double_t MuonInnerDzNormMax =  5.0;
  histMuonInnerDzNorm = new TH1D("histMuonInnerDzNorm","histMuonInnerDzNorm",NBinsMuonInnerDzNorm,MuonInnerDzNormMin,MuonInnerDzNormMax);
  histMuonInnerDzNorm->GetXaxis()->SetTitle("Muon InnerDzNorm");
  histMuonInnerDzNorm->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonInnerDzNorm = new TH1D("histNGMuonInnerDzNorm","histNGMuonInnerDzNorm",NBinsMuonInnerDzNorm,MuonInnerDzNormMin,MuonInnerDzNormMax);
  histNGMuonInnerDzNorm->GetXaxis()->SetTitle("NGMuon InnerDzNorm");
  histNGMuonInnerDzNorm->GetYaxis()->SetTitle("Entries");

  //14. mu_trkLayers
  const Int_t NBinsMuonTrkLayers    = 20;
  Double_t MuonTrkLayersMin = -0.5;
  Double_t MuonTrkLayersMax = 19.5;
  histMuonTrkLayers = new TH1D("histMuonTrkLayers","histMuonTrkLayers",NBinsMuonTrkLayers,MuonTrkLayersMin,MuonTrkLayersMax);
  histMuonTrkLayers->GetXaxis()->SetTitle("Muon TrkLayers");
  histMuonTrkLayers->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonTrkLayers = new TH1D("histNGMuonTrkLayers","histNGMuonTrkLayers",NBinsMuonTrkLayers,MuonTrkLayersMin,MuonTrkLayersMax);
  histNGMuonTrkLayers->GetXaxis()->SetTitle("NGMuon TrkLayers");
  histNGMuonTrkLayers->GetYaxis()->SetTitle("Entries");


  //15.mu_pixelLayers
  const Int_t NBinsMuonPixelLayers    = 10;
  Double_t MuonPixelLayersMin = -0.5;
  Double_t MuonPixelLayersMax = 9.5;
  histMuonPixelLayers = new TH1D("histMuonPixelLayers","histMuonPixelLayers",NBinsMuonPixelLayers,MuonPixelLayersMin,MuonPixelLayersMax);
  histMuonPixelLayers->GetXaxis()->SetTitle("Muon PixelLayers");
  histMuonPixelLayers->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonPixelLayers = new TH1D("histNGMuonPixelLayers","histNGMuonPixelLayers",NBinsMuonPixelLayers,MuonPixelLayersMin,MuonPixelLayersMax);
  histNGMuonPixelLayers->GetXaxis()->SetTitle("NGMuon PixelLayers");
  histNGMuonPixelLayers->GetYaxis()->SetTitle("Entries");

  //16.mu_pixelHits
  const Int_t NBinsMuonPixelHits    = 15;
  Double_t MuonPixelHitsMin = -0.5;
  Double_t MuonPixelHitsMax = 14.5;
  histMuonPixelHits = new TH1D("histMuonPixelHits","histMuonPixelHits",NBinsMuonPixelHits,MuonPixelHitsMin,MuonPixelHitsMax);
  histMuonPixelHits->GetXaxis()->SetTitle("Muon PixelHits");
  histMuonPixelHits->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonPixelHits = new TH1D("histNGMuonPixelHits","histNGMuonPixelHits",NBinsMuonPixelHits,MuonPixelHitsMin,MuonPixelHitsMax);
  histNGMuonPixelHits->GetXaxis()->SetTitle("NGMuon PixelHits");
  histNGMuonPixelHits->GetYaxis()->SetTitle("Entries");

  //17.mu_muonHits
  const Int_t NBinsMuonMuHits    = 50;
  Double_t MuonMuHitsMin = -0.5;
  Double_t MuonMuHitsMax = 49.5;
  histMuonMuHits = new TH1D("histMuonMuHits","histMuonMuHits",NBinsMuonMuHits,MuonMuHitsMin,MuonMuHitsMax);
  histMuonMuHits->GetXaxis()->SetTitle("Muon MuHits");
  histMuonMuHits->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonMuHits = new TH1D("histNGMuonMuHits","histNGMuonMuHits",NBinsMuonMuHits,MuonMuHitsMin,MuonMuHitsMax);
  histNGMuonMuHits->GetXaxis()->SetTitle("NGMuon MuHits");
  histNGMuonMuHits->GetYaxis()->SetTitle("Entries");

  //18.mu_trkQuality
  const Int_t NBinsMuonTrkQuality = 5;
  Double_t MuonTrkQualityMin = -0.5;
  Double_t MuonTrkQualityMax = 4.5;
  histMuonTrkQuality = new TH1D("histMuonTrkQuality","histMuonTrkQuality",NBinsMuonTrkQuality,MuonTrkQualityMin,MuonTrkQualityMax);
  histMuonTrkQuality->GetXaxis()->SetTitle("Muon TrkQuality");
  histMuonTrkQuality->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonTrkQuality = new TH1D("histNGMuonTrkQuality","histNGMuonTrkQuality",NBinsMuonTrkQuality,MuonTrkQualityMin,MuonTrkQualityMax);
  histNGMuonTrkQuality->GetXaxis()->SetTitle("NGMuon TrkQuality");
  histNGMuonTrkQuality->GetYaxis()->SetTitle("Entries");


  //19.mu_stations
  const Int_t NBinsMuonMuStations    = 10;
  Double_t MuonMuStationsMin = -0.5;
  Double_t MuonMuStationsMax = 9.5;
  histMuonMuStations = new TH1D("histMuonMuStations","histMuonMuStations",NBinsMuonMuStations,MuonMuStationsMin,MuonMuStationsMax);
  histMuonMuStations->GetXaxis()->SetTitle("Muon MuStations");
  histMuonMuStations->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGMuonMuStations = new TH1D("histNGMuonMuStations","histNGMuonMuStations",NBinsMuonMuStations,MuonMuStationsMin,MuonMuStationsMax);
  histNGMuonMuStations->GetXaxis()->SetTitle("NGMuon MuStations");
  histNGMuonMuStations->GetYaxis()->SetTitle("Entries");


  //===========================================================================================================//
  //=================================== Here I make histograms for Jet Matched muons ==========================//
  //===========================================================================================================//
  
  //1. IsGlobalMuon
  histJetMuonIsGlobal = new TH1D("histJetMuonIsGlobal","histJetMuonIsGlobal",NBinsMuonIsGlobal,MuonIsGlobalMin,MuonIsGlobalMax);
  histJetMuonIsGlobal->GetXaxis()->SetTitle("JetMuon IsGlobal");
  histJetMuonIsGlobal->GetYaxis()->SetTitle("Entries"); 
  //NG --> No Gen Muon
  histNGJetMuonIsGlobal = new TH1D("histNGJetMuonIsGlobal","histNGJetMuonIsGlobal",NBinsMuonIsGlobal,MuonIsGlobalMin,MuonIsGlobalMax);
  histNGJetMuonIsGlobal->GetXaxis()->SetTitle("NGJetMuon IsGlobal");
  histNGJetMuonIsGlobal->GetYaxis()->SetTitle("Entries");

  
  //2. IsTrackerMuon
  histJetMuonIsTracker = new TH1D("histJetMuonIsTracker","histJetMuonIsTracker",NBinsMuonIsTracker,MuonIsTrackerMin,MuonIsTrackerMax);
  histJetMuonIsTracker->GetXaxis()->SetTitle("JetMuon IsTracker");
  histJetMuonIsTracker->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonIsTracker = new TH1D("histNGJetMuonIsTracker","histNGJetMuonIsTracker",NBinsMuonIsTracker,MuonIsTrackerMin,MuonIsTrackerMax);
  histNGJetMuonIsTracker->GetXaxis()->SetTitle("NGJetMuon IsTracker");
  histNGJetMuonIsTracker->GetYaxis()->SetTitle("Entries");


  //3. IsPFMuon
  histJetMuonIsPF = new TH1D("histJetMuonIsPF","histJetMuonIsPF",NBinsMuonIsPF,MuonIsPFMin,MuonIsPFMax);
  histJetMuonIsPF->GetXaxis()->SetTitle("JetMuon IsPF");
  histJetMuonIsPF->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonIsPF = new TH1D("histNGJetMuonIsPF","histNGJetMuonIsPF",NBinsMuonIsPF,MuonIsPFMin,MuonIsPFMax);
  histNGJetMuonIsPF->GetXaxis()->SetTitle("NGJetMuon IsPF");
  histNGJetMuonIsPF->GetYaxis()->SetTitle("Entries");  


  //4. IsSTAMuon
  histJetMuonIsSTA = new TH1D("histJetMuonIsSTA","histJetMuonIsSTA",NBinsMuonIsSTA,MuonIsSTAMin,MuonIsSTAMax);
  histJetMuonIsSTA->GetXaxis()->SetTitle("JetMuon IsSTA");
  histJetMuonIsSTA->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonIsSTA = new TH1D("histNGJetMuonIsSTA","histNGJetMuonIsSTA",NBinsMuonIsSTA,MuonIsSTAMin,MuonIsSTAMax);
  histNGJetMuonIsSTA->GetXaxis()->SetTitle("NGJetMuon IsSTA");
  histNGJetMuonIsSTA->GetYaxis()->SetTitle("Entries");


  //5.mu_D0
  histJetMuonD0 = new TH1D("histJetMuonD0","histJetMuonD0",NBinsMuonD0,MuonD0Min,MuonD0Max);
  histJetMuonD0->GetXaxis()->SetTitle("JetMuon D0");
  histJetMuonD0->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonD0 = new TH1D("histNGJetMuonD0","histNGJetMuonD0",NBinsMuonD0,MuonD0Min,MuonD0Max);
  histNGJetMuonD0->GetXaxis()->SetTitle("NGJetMuon D0");
  histNGJetMuonD0->GetYaxis()->SetTitle("Entries");

  
  //6.mu_Dz
  histJetMuonDz = new TH1D("histJetMuonDz","histJetMuonDz",NBinsMuonDz,MuonDzMin,MuonDzMax);
  histJetMuonDz->GetXaxis()->SetTitle("JetMuon Dz");
  histJetMuonDz->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonDz = new TH1D("histNGJetMuonDz","histNGJetMuonDz",NBinsMuonDz,MuonDzMin,MuonDzMax);
  histNGJetMuonDz->GetXaxis()->SetTitle("NGJetMuon Dz");
  histNGJetMuonDz->GetYaxis()->SetTitle("Entries");

  //Muon Dxy-Dz 2D Histo 
  histJetMuonDxyDz = new TH2D("histJetMuonDxyDz","histJetMuonDxyDz",NBinsMuonD0,MuonD0Min,MuonD0Max,NBinsMuonDz,MuonDzMin,MuonDzMax);
  histJetMuonDxyDz->GetXaxis()->SetTitle("JetMuon D0");
  histJetMuonDxyDz->GetYaxis()->SetTitle("JetMuon Dz");
  histJetMuonDxyDz->GetZaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonDxyDz = new TH2D("histNGJetMuonDxyDz","histNGJetMuonDxyDz",NBinsMuonD0,MuonD0Min,MuonD0Max,NBinsMuonDz,MuonDzMin,MuonDzMax);
  histNGJetMuonDxyDz->GetXaxis()->SetTitle("NGJetMuon D0");
  histNGJetMuonDxyDz->GetYaxis()->SetTitle("NGJetMuon Dz");
  histNGJetMuonDxyDz->GetZaxis()->SetTitle("Entries");


  
  //Muon Dxy-Dz 2D Histo 
  histJetMuonDR = new TH1D("histJetMuonDR","histJetMuonDR",NBinsMuonDR,MuonDRMin,MuonDRMax);
  histJetMuonDR->GetXaxis()->SetTitle("Muon DR");
  histJetMuonDR->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonDR = new TH1D("histNGJetMuonDR","histNGJetMuonDR",NBinsMuonDR,MuonDRMin,MuonDRMax);
  histNGJetMuonDR->GetXaxis()->SetTitle("NGJetMuon DR");
  histNGJetMuonDR->GetYaxis()->SetTitle("Entries");
  
  //7.mu_chi2ndf
  histJetMuonChi2NDF = new TH1D("histJetMuonChi2NDF","histJetMuonChi2NDF",NBinsMuonChi2NDF,MuonChi2NDFMin,MuonChi2NDFMax);
  histJetMuonChi2NDF->GetXaxis()->SetTitle("JetMuon Chi2NDF");
  histJetMuonChi2NDF->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonChi2NDF = new TH1D("histNGJetMuonChi2NDF","histNGJetMuonChi2NDF",NBinsMuonChi2NDF,MuonChi2NDFMin,MuonChi2NDFMax);
  histNGJetMuonChi2NDF->GetXaxis()->SetTitle("NGJetMuon Chi2NDF");
  histNGJetMuonChi2NDF->GetYaxis()->SetTitle("Entries");

  
  //8.mu_innerD0
  histJetMuonInnerD0 = new TH1D("histJetMuonInnerD0","histJetMuonInnerD0",NBinsMuonInnerD0,MuonInnerD0Min,MuonInnerD0Max);
  histJetMuonInnerD0->GetXaxis()->SetTitle("JetMuon InnerD0");
  histJetMuonInnerD0->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonInnerD0 = new TH1D("histNGJetMuonInnerD0","histNGJetMuonInnerD0",NBinsMuonInnerD0,MuonInnerD0Min,MuonInnerD0Max);
  histNGJetMuonInnerD0->GetXaxis()->SetTitle("NGJetMuon InnerD0");
  histNGJetMuonInnerD0->GetYaxis()->SetTitle("Entries");
  
  //9.mu_innerD0Err
  histJetMuonInnerD0Err = new TH1D("histJetMuonInnerD0Err","histJetMuonInnerD0Err",NBinsMuonInnerD0Err,MuonInnerD0ErrMin,MuonInnerD0ErrMax);
  histJetMuonInnerD0Err->GetXaxis()->SetTitle("JetMuon InnerD0Err");
  histJetMuonInnerD0Err->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonInnerD0Err = new TH1D("histNGJetMuonInnerD0Err","histNGJetMuonInnerD0Err",NBinsMuonInnerD0Err,MuonInnerD0ErrMin,MuonInnerD0ErrMax);
  histNGJetMuonInnerD0Err->GetXaxis()->SetTitle("NGJetMuon InnerD0Err");
  histNGJetMuonInnerD0Err->GetYaxis()->SetTitle("Entries");

  //10.mu_innerDz
  histJetMuonInnerDz = new TH1D("histJetMuonInnerDz","histJetMuonInnerDz",NBinsMuonInnerDz,MuonInnerDzMin,MuonInnerDzMax);
  histJetMuonInnerDz->GetXaxis()->SetTitle("JetMuon InnerDz");
  histJetMuonInnerDz->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonInnerDz = new TH1D("histNGJetMuonInnerDz","histNGJetMuonInnerDz",NBinsMuonInnerDz,MuonInnerDzMin,MuonInnerDzMax);
  histNGJetMuonInnerDz->GetXaxis()->SetTitle("NGJetMuon InnerDz");
  histNGJetMuonInnerDz->GetYaxis()->SetTitle("Entries");
  
  //11.mu_innerDzErr
  histJetMuonInnerDzErr = new TH1D("histJetMuonInnerDzErr","histJetMuonInnerDzErr",NBinsMuonInnerDzErr,MuonInnerDzErrMin,MuonInnerDzErrMax);
  histJetMuonInnerDzErr->GetXaxis()->SetTitle("JetMuon InnerDzErr");
  histJetMuonInnerDzErr->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonInnerDzErr = new TH1D("histNGJetMuonInnerDzErr","histNGJetMuonInnerDzErr",NBinsMuonInnerDzErr,MuonInnerDzErrMin,MuonInnerDzErrMax);
  histNGJetMuonInnerDzErr->GetXaxis()->SetTitle("NGJetMuon InnerDzErr");
  histNGJetMuonInnerDzErr->GetYaxis()->SetTitle("Entries");

  
  //12.mu_innerD0/mu_innerD0Err
  histJetMuonInnerD0Norm = new TH1D("histJetMuonInnerD0Norm","histJetMuonInnerD0Norm",NBinsMuonInnerD0Norm,MuonInnerD0NormMin,MuonInnerD0NormMax);
  histJetMuonInnerD0Norm->GetXaxis()->SetTitle("JetMuon InnerD0Norm");
  histJetMuonInnerD0Norm->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonInnerD0Norm = new TH1D("histNGJetMuonInnerD0Norm","histNGJetMuonInnerD0Norm",NBinsMuonInnerD0Norm,MuonInnerD0NormMin,MuonInnerD0NormMax);
  histNGJetMuonInnerD0Norm->GetXaxis()->SetTitle("NGJetMuon InnerD0Norm");
  histNGJetMuonInnerD0Norm->GetYaxis()->SetTitle("Entries");
  
  //13.mu_innerDz/mu_innerDzErr
  histJetMuonInnerDzNorm = new TH1D("histJetMuonInnerDzNorm","histJetMuonInnerDzNorm",NBinsMuonInnerDzNorm,MuonInnerDzNormMin,MuonInnerDzNormMax);
  histJetMuonInnerDzNorm->GetXaxis()->SetTitle("JetMuon InnerDzNorm");
  histJetMuonInnerDzNorm->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonInnerDzNorm = new TH1D("histNGJetMuonInnerDzNorm","histNGJetMuonInnerDzNorm",NBinsMuonInnerDzNorm,MuonInnerDzNormMin,MuonInnerDzNormMax);
  histNGJetMuonInnerDzNorm->GetXaxis()->SetTitle("NGJetMuon InnerDzNorm");
  histNGJetMuonInnerDzNorm->GetYaxis()->SetTitle("Entries");

  //14. mu_trkLayers
  histJetMuonTrkLayers = new TH1D("histJetMuonTrkLayers","histJetMuonTrkLayers",NBinsMuonTrkLayers,MuonTrkLayersMin,MuonTrkLayersMax);
  histJetMuonTrkLayers->GetXaxis()->SetTitle("JetMuon TrkLayers");
  histJetMuonTrkLayers->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonTrkLayers = new TH1D("histNGJetMuonTrkLayers","histNGJetMuonTrkLayers",NBinsMuonTrkLayers,MuonTrkLayersMin,MuonTrkLayersMax);
  histNGJetMuonTrkLayers->GetXaxis()->SetTitle("NGJetMuon TrkLayers");
  histNGJetMuonTrkLayers->GetYaxis()->SetTitle("Entries");

  //15.mu_pixelLayers
  histJetMuonPixelLayers = new TH1D("histJetMuonPixelLayers","histJetMuonPixelLayers",NBinsMuonPixelLayers,MuonPixelLayersMin,MuonPixelLayersMax);
  histJetMuonPixelLayers->GetXaxis()->SetTitle("JetMuon PixelLayers");
  histJetMuonPixelLayers->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonPixelLayers = new TH1D("histNGJetMuonPixelLayers","histNGJetMuonPixelLayers",NBinsMuonPixelLayers,MuonPixelLayersMin,MuonPixelLayersMax);
  histNGJetMuonPixelLayers->GetXaxis()->SetTitle("NGJetMuon PixelLayers");
  histNGJetMuonPixelLayers->GetYaxis()->SetTitle("Entries");

  //16.mu_pixelHits
  histJetMuonPixelHits = new TH1D("histJetMuonPixelHits","histJetMuonPixelHits",NBinsMuonPixelHits,MuonPixelHitsMin,MuonPixelHitsMax);
  histJetMuonPixelHits->GetXaxis()->SetTitle("JetMuon PixelHits");
  histJetMuonPixelHits->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonPixelHits = new TH1D("histNGJetMuonPixelHits","histNGJetMuonPixelHits",NBinsMuonPixelHits,MuonPixelHitsMin,MuonPixelHitsMax);
  histNGJetMuonPixelHits->GetXaxis()->SetTitle("NGJetMuon PixelHits");
  histNGJetMuonPixelHits->GetYaxis()->SetTitle("Entries");

  //17.mu_muonHits
  histJetMuonMuHits = new TH1D("histJetMuonMuHits","histJetMuonMuHits",NBinsMuonMuHits,MuonMuHitsMin,MuonMuHitsMax);
  histJetMuonMuHits->GetXaxis()->SetTitle("JetMuon MuHits");
  histJetMuonMuHits->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonMuHits = new TH1D("histNGJetMuonMuHits","histNGJetMuonMuHits",NBinsMuonMuHits,MuonMuHitsMin,MuonMuHitsMax);
  histNGJetMuonMuHits->GetXaxis()->SetTitle("NGJetMuon MuHits");
  histNGJetMuonMuHits->GetYaxis()->SetTitle("Entries");

  //18.mu_trkQuality
  histJetMuonTrkQuality = new TH1D("histJetMuonTrkQuality","histJetMuonTrkQuality",NBinsMuonTrkQuality,MuonTrkQualityMin,MuonTrkQualityMax);
  histJetMuonTrkQuality->GetXaxis()->SetTitle("JetMuon TrkQuality");
  histJetMuonTrkQuality->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonTrkQuality = new TH1D("histNGJetMuonTrkQuality","histNGJetMuonTrkQuality",NBinsMuonTrkQuality,MuonTrkQualityMin,MuonTrkQualityMax);
  histNGJetMuonTrkQuality->GetXaxis()->SetTitle("NGJetMuon TrkQuality");
  histNGJetMuonTrkQuality->GetYaxis()->SetTitle("Entries");

  //19.mu_stations
  histJetMuonMuStations = new TH1D("histJetMuonMuStations","histJetMuonMuStations",NBinsMuonMuStations,MuonMuStationsMin,MuonMuStationsMax);
  histJetMuonMuStations->GetXaxis()->SetTitle("JetMuon MuStations");
  histJetMuonMuStations->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  histNGJetMuonMuStations = new TH1D("histNGJetMuonMuStations","histNGJetMuonMuStations",NBinsMuonMuStations,MuonMuStationsMin,MuonMuStationsMax);
  histNGJetMuonMuStations->GetXaxis()->SetTitle("NGJetMuon MuStations");
  histNGJetMuonMuStations->GetYaxis()->SetTitle("Entries");

  
  //=======================================================================================================================================//
  //================================= Muon Quality Cut Histograms Ends ===================================================================//
  //=======================================================================================================================================//




}









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


// naming convention

//i) root fMu_D0
//ii) c++ mu_D0_


//constructer and distructer
//constructer initilize all the private variables


//class inhareted from TLorentz Vector
class MyParticle : public TLorentzVector{

private:
  //add muon quality cuts as members of the class
  Int_t fMu_isGlobal, fMu_isTracker, fMu_isPF, fMu_isSTA, fMu_isGood, fMu_pixelLayers, fMu_pixelHits, fMu_trkLayers, fMu_stations, fMu_trkQuality;
  Float_t fMu_D0, fMu_Dz, fMu_chi2ndf, fMu_innerD0, fMu_innerDz, fMu_muonHits, fMu_innerD0Err, fMu_innerDzErr, fMu_innerD0Norm, fMu_innerDzNorm;
  Int_t fMu_hasGenMu;
  
public:
  //constructer
  MyParticle();
  //destructer
  ~MyParticle();
  
  void SetParticle_IntQualityCuts(Int_t,Int_t,Int_t,Int_t,Int_t,Int_t,Int_t,Int_t,Int_t,Int_t);
  void SetParticle_FloatQualityCuts(Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t,Float_t);
  void SetParticle_MCMatch(Int_t);

  
  Int_t GetParticle_isGlobal(){return fMu_isGlobal;}
  Int_t GetParticle_isTracker(){return fMu_isTracker;}
  Int_t GetParticle_isPF(){return fMu_isPF;}
  Int_t GetParticle_isSTA(){return fMu_isSTA;}
  Int_t GetParticle_isGood(){return fMu_isGood;}
  
  Int_t GetParticle_pixelLayers(){return fMu_pixelLayers;}
  Int_t GetParticle_pixelHits(){return fMu_pixelHits;}
  Int_t GetParticle_trkLayers(){return fMu_trkLayers;}
  Int_t GetParticle_stations(){return fMu_stations;}
  Int_t GetParticle_trkQuality(){return fMu_trkQuality;}



  Float_t GetParticle_D0(){return fMu_D0;}
  Float_t GetParticle_Dz(){return fMu_Dz;}
  Float_t GetParticle_chi2ndf(){return fMu_chi2ndf;}
  Float_t GetParticle_innerD0(){return fMu_innerD0;}
  Float_t GetParticle_innerDz(){return fMu_innerDz;}
  Float_t GetParticle_muonHits(){return fMu_muonHits;}
  
  Float_t GetParticle_innerD0Err(){return fMu_innerD0Err;}
  Float_t GetParticle_innerDzErr(){return fMu_innerDzErr;}

  Float_t GetParticle_innerD0Norm(){return fMu_innerD0Norm;}
  Float_t GetParticle_innerDzNorm(){return fMu_innerDzNorm;}

  Int_t GetParticle_MCMatch(){return fMu_hasGenMu;}

  
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
//: if you want to initilize the variable
//list outside {} of constructer
MyParticle::MyParticle():
  fMu_isGlobal(-999),
  fMu_isTracker(-999),
  fMu_isPF(-999),
  fMu_isSTA(-999),
  fMu_isGood(-999),
  fMu_pixelLayers(-999),
  fMu_pixelHits(-999),
  fMu_trkLayers(-999),
  fMu_stations(-999),
  fMu_trkQuality(-999),
  fMu_D0(-999),
  fMu_Dz(-999),
  fMu_chi2ndf(-999),
  fMu_innerD0(-999),
  fMu_innerDz(-999),
  fMu_muonHits(-999),
  fMu_innerD0Err(-999),
  fMu_innerDzErr(-999),
  fMu_innerD0Norm(-999),
  fMu_innerDzNorm(-999),
  fMu_hasGenMu(0)
{
}

//destructer
//if you create a object inside the class with keyword new
//you have to delete it inside the destructer
MyParticle::~MyParticle(){}



void MyParticle::SetParticle_IntQualityCuts(Int_t Mu_isGlobal, Int_t Mu_isTracker, Int_t Mu_isPF, Int_t Mu_isSTA, Int_t Mu_isGood, Int_t Mu_pixelLayers, Int_t Mu_pixelHits,
					    Int_t Mu_trkLayers, Int_t Mu_stations, Int_t Mu_trkQuality){
  fMu_isGlobal=Mu_isGlobal;
  fMu_isTracker=Mu_isTracker;
  fMu_isPF=Mu_isPF;
  fMu_isSTA=Mu_isSTA;
  fMu_isGood=Mu_isGood;
  fMu_pixelLayers=Mu_pixelLayers;
  fMu_pixelHits=Mu_pixelHits;
  fMu_trkLayers=Mu_trkLayers;
  fMu_stations=Mu_stations;
  fMu_trkQuality=Mu_trkQuality;

}



//fMu_D0, fMu_Dz, fMu_chi2ndf, fMu_innerD0, fMu_innerDz, fMu_muonHits, fMu_innerD0Err, fMu_innerDzErr, fMu_innerD0Norm, fMu_innerDzNorm

void MyParticle::SetParticle_FloatQualityCuts(Float_t Mu_D0, Float_t Mu_Dz, Float_t Mu_chi2ndf, Float_t Mu_innerD0, Float_t Mu_innerDz, Float_t Mu_muonHits,
				  Float_t Mu_innerD0Err, Float_t Mu_innerDzErr, Float_t Mu_innerD0Norm, Float_t Mu_innerDzNorm)
{
  fMu_D0 =Mu_D0;
  fMu_Dz=Mu_Dz;
  fMu_chi2ndf=Mu_chi2ndf;
  fMu_innerD0=Mu_innerD0;
  fMu_innerDz=Mu_innerDz;
  fMu_muonHits=Mu_muonHits;
  fMu_innerD0Err=Mu_innerD0Err;
  fMu_innerDzErr=Mu_innerDzErr;
  fMu_innerD0Norm=Mu_innerD0Norm;
  fMu_innerDzNorm=Mu_innerDzNorm;

}

void MyParticle::SetParticle_MCMatch(Int_t Mu_hasGenMu)
{
  fMu_hasGenMu = Mu_hasGenMu;
}


#endif // #ifdef JetAnalyzer_cxx
