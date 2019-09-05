#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TH2F.h"
#include "TMath.h"
#include <TNtuple.h>
#include "TChain.h"
#include <TString.h>
#include <TCut.h>
#include "assert.h"
#include <fstream>
#include "TMath.h"
#include <vector>


#include "JetCorrector.h"



using namespace std;

const float trkPtCut=1.0;
const double trketamaxcut = 2.4;

bool passTrackCuts(bool ispp, bool useTightCuts, float trkPt, float trkEta, bool tightTracks, float trkChi2, int trkNdof, int trkNlayer, int trkNHit, float pfHcal, float pfEcal, float trkDzSigma, float trkDxySigma);

/* Imp comment about how many files will be processed per job
 *It is being controled by three parameters in three files
 *In the crab config file : config.Data.unitsPerJob = 10 (This will make input file lists with 10 files per job
 *SuperSlimSkimMultipleFiles(bool doCrab=1, int jobID=0, int endfile = 10) endfile will run the loop over 10 file
 *root -b -l -q $ss+\(1,$1,10\) ss is SuperSlimSkimMultipleFiles, last parameter will override the default value given in SuperSlimSkimMultipleFiles
 */

void SuperSlimSkimMultipleFiles(bool doCrab=1, int jobID=0, int endfile = 2)
{

  //**************************************************//
  // All the switches for is_data etc. will come here //
  //**************************************************//
  const bool do_PbPb = 0;
  const bool is_data = 0;
  const bool do_tracks=0;
  
  //as now we are mostly working with pf Jets
  const bool do_calojets=0;
  
  //**************************************************//
  // Set up the Jet Corrections 
  vector<string> Files;
  //MC Corrections
  //pp MC
  if(is_data==0 && do_PbPb==0)Files.push_back("Spring18_ppRef5TeV_V2_MC_L2Relative_AK4PF.txt"); //pp 2017 MC correction L2Relative Correction (V2)

  //Data Corrections
  //PbPb Data
  if(is_data==1 && do_PbPb==1)Files.push_back("Autumn18_HI_V4_DATA_L2Relative_AK4PF.txt"); //PbPb 2018 Data Relative
  //if(is_data==1 && do_PbPb==1)Files.push_back("Autumn18_HI_V4_DATA_L2Residual_AK4PF.txt"); //PbPb 2018 Data Residual
  //PP Data
  if(is_data==1 && do_PbPb==0)Files.push_back("Spring18_ppRef5TeV_V2_DATA_L2Relative_AK4PF.txt"); //PP 2017 Data Relative
  JetCorrector JEC(Files);
  //**************************************************//
  
  // put the input trees here //
  Int_t radius = 4;
  TTree *inp_tree=NULL;
  TTree *event_tree=NULL;
  TTree *pf_tree=NULL;
  TTree *muon_tree=NULL;
  TTree *track_tree=NULL;
  TTree *hlt_tree=NULL;
  TTree *skim_tree=NULL;

  TTree *gen_tree=NULL;
  
  string in_file_name;
  TString output_file_base;
  
  if(doCrab==1){in_file_name = Form("job_input_file_list_%d.txt",jobID);} //to run on crab
  //else{in_file_name = Form("tempFileList_Data.txt");}//to run locally
  //else{in_file_name = Form("tempFileList_2017PPMC.txt");}//to run locally
  else{in_file_name = Form("tempFileList_2017PPData.txt");}//to run locally
  
  output_file_base= "";
  cout << "trying a filelist named "<< in_file_name << endl;
  TString output_file_extension;
  if(is_data==1 && do_PbPb==1){output_file_extension= "PbPb_5TeV_SingleMuPD_MuJetTrigger_Skim.root";}
  else if(is_data==1 && do_PbPb==0){output_file_extension= "PP2017Data_5TeV_SingleMuPD_MuJetTrigger_Skim.root";} 
  else if(is_data==0 && do_PbPb==1){output_file_extension= "PbPb_2018MC_5TeV_Skim.root";} 
  else{output_file_extension= "PP_2017MC_5TeV_MC_Skim.root";}
  
  //cout<<" run maker calling "<<my_file<<endl;
  //run_maker(my_file, output_file_base+output_file_extension, do_PbPb, is_data, do_tracks);
  TFile *output_file = new TFile((TString)(output_file_base+output_file_extension), "RECREATE");
  cout<<"created file "<<output_file->GetName()<<endl;
  
  //}

  //void run_maker(TFile* my_file, TString name, bool do_PbPb, bool is_data, bool do_tracks){
  
  
  TTree *mixing_tree = new TTree("mixing_tree", "");
  //================== Variables for Mixing Tree =============================//

  
  //0. Event Variables
  UInt_t          run;
  ULong64_t       evt;
  UInt_t          lumi;
  
  Float_t vx, vy, vz;
  Int_t hiBin;
  
  Int_t HLT_HIPuAK4CaloJet80Eta5p1_v1, HLT_HIPuAK4CaloJet100Eta5p1_v1, HLT_HIPuAK4CaloJet120Eta5p1_v1;
  Int_t HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl,HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl,HLT_HIPuAK4CaloJet120Eta5p1_v1_Prescl; 

  Int_t HLT_HIL3Mu12_v1, HLT_HIL3Mu15_v1, HLT_HIL3Mu20_v1;
  Int_t HLT_HIL3Mu12_v1_Prescl, HLT_HIL3Mu15_v1_Prescl, HLT_HIL3Mu20_v1_Prescl;
  
  // cross - triggers (Muon+Jets)
  Int_t HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1, HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1, HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1, HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1;
  Int_t HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl, HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl, HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl, HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl;
  
  // cross - triggers (Muon+Jets) PP
  Int_t HLT_HIL3Mu5_AK4PFJet30_v1, HLT_HIL3Mu5_AK4PFJet40_v1, HLT_HIL3Mu5_AK4PFJet60_v1;
  Int_t HLT_HIL3Mu5_AK4PFJet30_v1_Prescl, HLT_HIL3Mu5_AK4PFJet40_v1_Prescl, HLT_HIL3Mu5_AK4PFJet60_v1_Prescl;

  
  Int_t pBeamScrapingFilter, collisionEventSelectionAOD, collisionEventSelectionAODv2;
  Int_t pVertexFilterCutG, pVertexFilterCutGloose, pVertexFilterCutGtight,pVertexFilterCutGplus,pVertexFilterCutE,pVertexFilterCutEandG;
  
  Int_t pHBHENoiseFilterResultProducer,HBHENoiseFilterResult,HBHENoiseFilterResultRun1,HBHENoiseFilterResultRun2Loose,HBHENoiseFilterResultRun2Tight;
  Int_t HBHEIsoNoiseFilterResult, superFilterPath;
  
  
  //1. Calo Jet Variables
  vector<float> calo_jteta, calo_jtphi, calo_jtpt, calo_rawpt, calo_corrpt, calo_trackMax, calo_jtmass;
  vector<float> calo_discr_ssvHighEff, calo_discr_ssvHighPur, calo_discr_csvV1, calo_discr_csvV2, calo_discr_prob, calo_svtxm, calo_svtxpt, calo_svtxmcorr, calo_svtxdl, calo_svtxdls;
  // MC Variables
  Float_t calo_pthat, calo_weight;
  vector<float>calo_refeta, calo_refpt, calo_refphi;
  vector<int>calo_refparton_flavor, calo_refparton_flavorForB;
  // MC Variables : Gen Jet Variables
  Int_t calo_ngen;
  vector<int>calo_genmatchindex;
  vector<float>calo_geneta, calo_genpt, calo_genphi;

  //2. PF Jet Variables
  vector<float> pf_jteta, pf_jtphi, pf_jtpt, pf_rawpt, pf_corrpt, pf_trackMax, pf_jtmass;
  vector<float> pf_discr_ssvHighEff, pf_discr_ssvHighPur, pf_discr_csvV1, pf_discr_csvV2, pf_discr_prob, pf_svtxm, pf_svtxpt, pf_svtxmcorr, pf_svtxdl, pf_svtxdls;
  // MC Variables
  Float_t pf_pthat, pf_weight;  
  vector<float>pf_refeta, pf_refpt, pf_refphi;
  vector<int>pf_refparton_flavor, pf_refparton_flavorForB, pf_matchedHadronFlavor, pf_matchedPartonFlavor;
  // MC Variables : Gen Jet Variables
  Int_t pf_ngen;
  vector<int>pf_genmatchindex;
  vector<float>pf_geneta, pf_genpt, pf_genphi;

  //3. Track Variables
  vector<float> trkEta, trkPhi, trkPt,  trkPtError;
  //vector<float> trkDxy, trkDxyError, trkDz, trkDzError, trkChi2;
  //vector<int> trkNHit, trkNlayer, trkNdof;
  //vector<bool> trktight;
  vector<bool> trkhighPurity;

  vector<int> trkpfType;
  vector<float>  trkpfEcal, trkpfHcal;
  
  //not sure about these track variables
  //vector<float> trkMVALoose, trkMVATight , trkloose;
  //vector<int> trkAlgo;
  
  //4. Muon Variables
  vector<float> *mu_pt=0, *mu_phi=0, *mu_eta=0;
  vector<int> *mu_isGlobal=0, *mu_isTracker=0, *mu_isPF=0, *mu_isSTA=0;
  vector<float> *mu_D0=0, *mu_Dz=0, *mu_chi2ndf=0, *mu_innerD0=0, *mu_innerDz=0;
  vector<float> *mu_innerD0Err=0, *mu_innerDzErr=0, *mu_innerPtErr=0, *mu_innerPt=0, *mu_innerEta = 0;
  vector<int> *mu_chg=0, *mu_type=0, *mu_isGood=0, *mu_trkLayers=0, *mu_pixelLayers=0, *mu_pixelHits=0, *mu_muonHits=0;
  vector<int> *mu_trkQuality=0, *mu_stations=0;
  
  //4. Gen Particle Variables
  vector<int> sube, chg, pdg;
  vector<float> pt, phi, eta;


  //================== Define the MixingTree ===================================//
  //mixing_tree->Branch("nTrk", &nTrk, "nTrk/I");
    
  mixing_tree->Branch("run",&run);
  mixing_tree->Branch("evt",&evt);
  mixing_tree->Branch("lumi",&lumi);

  mixing_tree->Branch("vx",&vx);
  mixing_tree->Branch("vy",&vy);
  mixing_tree->Branch("vz",&vz);
  mixing_tree->Branch("hiBin",&hiBin);

  //mixing_tree->Branch("evtPlane_HF2",&evtPlane_HF2);
  // MC Event variables
  //if(!is_data){
  //
  //
  //}

  mixing_tree->Branch("HLT_HIPuAK4CaloJet80Eta5p1_v1",&HLT_HIPuAK4CaloJet80Eta5p1_v1);
  mixing_tree->Branch("HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl",&HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl);
  mixing_tree->Branch("HLT_HIPuAK4CaloJet100Eta5p1_v1",&HLT_HIPuAK4CaloJet100Eta5p1_v1);
  mixing_tree->Branch("HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl",&HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl);
  mixing_tree->Branch("HLT_HIPuAK4CaloJet120Eta5p1_v1",&HLT_HIPuAK4CaloJet120Eta5p1_v1);
  mixing_tree->Branch("HLT_HIPuAK4CaloJet120Eta5p1_v1_Prescl",&HLT_HIPuAK4CaloJet120Eta5p1_v1_Prescl);
  
  mixing_tree->Branch("HLT_HIL3Mu12_v1",&HLT_HIL3Mu12_v1);
  mixing_tree->Branch("HLT_HIL3Mu12_v1_Prescl",&HLT_HIL3Mu12_v1_Prescl);
  mixing_tree->Branch("HLT_HIL3Mu15_v1",&HLT_HIL3Mu15_v1);
  mixing_tree->Branch("HLT_HIL3Mu15_v1_Prescl",&HLT_HIL3Mu15_v1_Prescl);
  mixing_tree->Branch("HLT_HIL3Mu20_v1",&HLT_HIL3Mu20_v1);
  mixing_tree->Branch("HLT_HIL3Mu20_v1_Prescl",&HLT_HIL3Mu20_v1_Prescl);
  
  // muon + Jet cross-triggers
  mixing_tree->Branch("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1);
  mixing_tree->Branch("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl);
  mixing_tree->Branch("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1);
  mixing_tree->Branch("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl);
  mixing_tree->Branch("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1);
  mixing_tree->Branch("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl);
  mixing_tree->Branch("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1);
  mixing_tree->Branch("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl);
  
  //These trigger are present in PPData and PP MC
 if(!do_PbPb){
    mixing_tree->Branch("HLT_HIL3Mu5_AK4PFJet30_v1",&HLT_HIL3Mu5_AK4PFJet30_v1);
    mixing_tree->Branch("HLT_HIL3Mu5_AK4PFJet30_v1_Prescl",&HLT_HIL3Mu5_AK4PFJet30_v1_Prescl);  
    mixing_tree->Branch("HLT_HIL3Mu5_AK4PFJet40_v1",&HLT_HIL3Mu5_AK4PFJet40_v1);
    mixing_tree->Branch("HLT_HIL3Mu5_AK4PFJet40_v1_Prescl",&HLT_HIL3Mu5_AK4PFJet40_v1_Prescl);  
    mixing_tree->Branch("HLT_HIL3Mu5_AK4PFJet60_v1",&HLT_HIL3Mu5_AK4PFJet60_v1);
    mixing_tree->Branch("HLT_HIL3Mu5_AK4PFJet60_v1_Prescl",&HLT_HIL3Mu5_AK4PFJet60_v1_Prescl);  
  }
  


  mixing_tree->Branch("pBeamScrapingFilter",&pBeamScrapingFilter);
  mixing_tree->Branch("collisionEventSelectionAOD",&collisionEventSelectionAOD);
  mixing_tree->Branch("collisionEventSelectionAODv2",&collisionEventSelectionAODv2);
  mixing_tree->Branch("pVertexFilterCutGloose",&pVertexFilterCutGloose);
  mixing_tree->Branch("pVertexFilterCutGtight",&pVertexFilterCutGtight);
  mixing_tree->Branch("pVertexFilterCutGplus",&pVertexFilterCutGplus);
  mixing_tree->Branch("pVertexFilterCutE",&pVertexFilterCutE);
  mixing_tree->Branch("pVertexFilterCutEandG",&pVertexFilterCutEandG);
  mixing_tree->Branch("pHBHENoiseFilterResultProducer",&pHBHENoiseFilterResultProducer);
  mixing_tree->Branch("HBHENoiseFilterResult",&HBHENoiseFilterResult);
  mixing_tree->Branch("HBHENoiseFilterResultRun1",&HBHENoiseFilterResultRun1);
  mixing_tree->Branch("HBHENoiseFilterResultRun2Loose",&HBHENoiseFilterResultRun2Loose);
  mixing_tree->Branch("HBHENoiseFilterResultRun2Tight",&HBHENoiseFilterResultRun2Tight);
  mixing_tree->Branch("HBHEIsoNoiseFilterResult",&HBHEIsoNoiseFilterResult);
  mixing_tree->Branch("superFilterPath",&superFilterPath);

  
  //========= pfjet
  mixing_tree->Branch("pf_jteta", &pf_jteta);
  mixing_tree->Branch("pf_jtphi", &pf_jtphi);
  mixing_tree->Branch("pf_jtpt", &pf_jtpt);
  mixing_tree->Branch("pf_rawpt", &pf_rawpt);
  mixing_tree->Branch("pf_corrpt", &pf_corrpt);
  mixing_tree->Branch("pf_trackMax", &pf_trackMax);
  mixing_tree->Branch("pf_discr_csvV1", &pf_discr_csvV1);
  mixing_tree->Branch("pf_discr_csvV2", &pf_discr_csvV2);
  mixing_tree->Branch("pf_discr_ssvHighEff", &pf_discr_ssvHighEff);
  mixing_tree->Branch("pf_discr_ssvHighPur", &pf_discr_ssvHighPur);
  mixing_tree->Branch("pf_discr_prob", &pf_discr_prob);
  mixing_tree->Branch("pf_svtxm", &pf_svtxm);
  mixing_tree->Branch("pf_svtxpt", &pf_svtxpt);
  mixing_tree->Branch("pf_svtxmcorr", &pf_svtxmcorr);
  mixing_tree->Branch("pf_svtxdl", &pf_svtxdl);
  mixing_tree->Branch("pf_svtxdls", &pf_svtxdls);
  
  // PF Jet MC Variables
  if(!is_data){
    
    mixing_tree->Branch("pf_pthat", &pf_pthat); // event variable
    mixing_tree->Branch("pf_weight", &pf_weight); // event variable

    mixing_tree->Branch("pf_refeta",&pf_refeta);
    mixing_tree->Branch("pf_refpt",&pf_refpt);
    mixing_tree->Branch("pf_refphi",&pf_refphi);
    mixing_tree->Branch("pf_refparton_flavor", &pf_refparton_flavor);
    mixing_tree->Branch("pf_refparton_flavorForB",&pf_refparton_flavorForB);
    mixing_tree->Branch("pf_matchedHadronFlavor", &pf_matchedHadronFlavor);
    mixing_tree->Branch("pf_matchedPartonFlavor", &pf_matchedPartonFlavor);

    // gen Jet Variables
    // number of gen Jets
    mixing_tree->Branch("pf_ngen", &pf_ngen); //Event Variable

    mixing_tree->Branch("pf_genmatchindex",&pf_genmatchindex);
    mixing_tree->Branch("pf_geneta",&pf_geneta);
    mixing_tree->Branch("pf_genpt",&pf_genpt);
    mixing_tree->Branch("pf_genphi",&pf_genphi);
    
  }

  //======== calojet
  mixing_tree->Branch("calo_jteta", &calo_jteta);
  mixing_tree->Branch("calo_jtphi", &calo_jtphi);
  mixing_tree->Branch("calo_jtpt", &calo_jtpt);
  mixing_tree->Branch("calo_rawpt", &calo_rawpt);
  mixing_tree->Branch("calo_corrpt", &calo_corrpt);
  mixing_tree->Branch("calo_trackMax", &calo_trackMax);

  mixing_tree->Branch("calo_discr_ssvHighEff", &calo_discr_ssvHighEff);
  mixing_tree->Branch("calo_discr_ssvHighPur", &calo_discr_ssvHighPur);
  mixing_tree->Branch("calo_discr_csvV1", &calo_discr_csvV1);
  mixing_tree->Branch("calo_discr_csvV2", &calo_discr_csvV2);
  mixing_tree->Branch("calo_discr_prob", &calo_discr_prob);
  mixing_tree->Branch("calo_svtxm", &calo_svtxm);
  mixing_tree->Branch("calo_svtxpt", &calo_svtxpt);
  mixing_tree->Branch("calo_svtxmcorr", &calo_svtxmcorr);
  mixing_tree->Branch("calo_svtxdl", &calo_svtxdl);
  mixing_tree->Branch("calo_svtxdls", &calo_svtxdls);

  //Calo Jet MC Variables
  if(!is_data){
    mixing_tree->Branch("calo_pthat", &calo_pthat); // event variable
    mixing_tree->Branch("calo_weight", &calo_weight); // event variable
    mixing_tree->Branch("calo_refeta",&calo_refeta);
    mixing_tree->Branch("calo_refpt",&calo_refpt);
    mixing_tree->Branch("calo_refphi",&calo_refphi);
    mixing_tree->Branch("calo_refparton_flavor", &calo_refparton_flavor);
    mixing_tree->Branch("calo_refparton_flavorForB",&calo_refparton_flavorForB);
    // gen Jet Variables
    // number of gen Jets
    mixing_tree->Branch("calo_ngen", &calo_ngen); //Event Variable
    mixing_tree->Branch("calo_genmatchindex",&calo_genmatchindex);
    mixing_tree->Branch("calo_geneta",&calo_geneta);
    mixing_tree->Branch("calo_genpt",&calo_genpt);
    mixing_tree->Branch("calo_genphi",&calo_genphi);
  }

  //======= track
  mixing_tree->Branch("trkPt", &trkPt);
  mixing_tree->Branch("trkEta", &trkEta);
  mixing_tree->Branch("trkPhi", &trkPhi);
  //mixing_tree->Branch("trkAlgo", &trkAlgo);
  //mixing_tree->Branch("trktight",&trktight);
  mixing_tree->Branch("trkhighPurity", &trkhighPurity);

  //mixing_tree->Branch("vz", &vz);
  //mixing_tree->Branch("trkDxy", &trkDxy);
  //mixing_tree->Branch("trkDxyError", &trkDxyError);
  //mixing_tree->Branch("trkDz", &trkDz);
  //mixing_tree->Branch("trkDzError", &trkDzError);

  mixing_tree->Branch("trkPtError", &trkPtError);
  //mixing_tree->Branch("trkChi2", &trkChi2);
  //mixing_tree->Branch("trkNdof", &trkNdof);
  //mixing_tree->Branch("trkNHit",&trkNHit);
  //mixing_tree->Branch("trkNlayer",&trkNlayer);
  mixing_tree->Branch("trkpfType",&trkpfType);
  //mixing_tree->Branch("trkpfEcal",&trkpfEcal);
  //mixing_tree->Branch("trkpfHcal",&trkpfHcal);
  //mixing_tree->Branch("trkMVALoose",&trkMVALoose);
  //mixing_tree->Branch("trkMVATight",&trkMVATight);
  //mixing_tree->Branch("trkloose",&trkloose);
  
  //================= Muon
  mixing_tree->Branch("mu_pt" , &mu_pt);
  mixing_tree->Branch("mu_phi", &mu_phi);
  mixing_tree->Branch("mu_eta", &mu_eta);
  mixing_tree->Branch("mu_chg",        &mu_chg);

  mixing_tree->Branch("mu_type",       &mu_type);
  mixing_tree->Branch("mu_isGlobal",     &mu_isGlobal);
  mixing_tree->Branch("mu_isTracker",     &mu_isTracker);
  mixing_tree->Branch("mu_isPF",     &mu_isPF);
  mixing_tree->Branch("mu_isSTA",     &mu_isSTA);
  mixing_tree->Branch("mu_D0" , &mu_D0);
  mixing_tree->Branch("mu_Dz" , &mu_Dz);
  mixing_tree->Branch("mu_chi2ndf", &mu_chi2ndf);
  mixing_tree->Branch("mu_innerD0", &mu_innerD0);
  mixing_tree->Branch("mu_innerDz", &mu_innerDz);
  mixing_tree->Branch("mu_innerD0Err", &mu_innerD0Err);
  mixing_tree->Branch("mu_innerDzErr", &mu_innerDzErr);
  
  mixing_tree->Branch("mu_innerPt", &mu_innerPt);
  mixing_tree->Branch("mu_innerPtError", &mu_innerPtErr);
  mixing_tree->Branch("mu_innerEta", &mu_innerEta);
  //mixing_tree->Branch("mu_innerHighPurity", &mu_innerHP);
  
  mixing_tree->Branch("mu_isGood",     &mu_isGood);
  mixing_tree->Branch("mu_trkLayers",  &mu_trkLayers);
  mixing_tree->Branch("mu_pixelLayers",&mu_pixelLayers);
  mixing_tree->Branch("mu_pixelHits",  &mu_pixelHits);
  mixing_tree->Branch("mu_muonHits",   &mu_muonHits);
  mixing_tree->Branch("mu_trkQuality", &mu_trkQuality);
  mixing_tree->Branch("mu_stations",&mu_stations);
  
  //========== Gen Variables ====================//
  if(!is_data){
    mixing_tree->Branch("eta",  &eta);
    mixing_tree->Branch("pt", &pt);
    mixing_tree->Branch("phi",  &phi);
    mixing_tree->Branch("chg", &chg);
    mixing_tree->Branch("sube", &sube);
    mixing_tree->Branch("pdg",&pdg);
    // no status branch in 2017 MC
    //mixing_tree->Branch("status", &sta);
  }


  const int MAXJETS = 250;
  Int_t calo_nref=0;
  Float_t t_calo_jtpt[MAXJETS], t_calo_jteta[MAXJETS], t_calo_jtphi[MAXJETS], t_calo_rawpt[MAXJETS], t_calo_trackMax[MAXJETS];
  Float_t t_calo_discr_ssvHighEff[MAXJETS], t_calo_discr_ssvHighPur[MAXJETS], t_calo_discr_csvV1[MAXJETS], t_calo_discr_csvV2[MAXJETS];
  Float_t t_calo_discr_prob[MAXJETS], t_calo_svtxm[MAXJETS], t_calo_svtxpt[MAXJETS], t_calo_svtxmcorr[MAXJETS], t_calo_svtxdl[MAXJETS], t_calo_svtxdls[MAXJETS];
  
  // MC Variables Calo Jets
  Float_t t_calo_pthat, t_calo_weight;
  Float_t t_calo_refpt[MAXJETS], t_calo_refeta[MAXJETS], t_calo_refphi[MAXJETS];
  Int_t t_calo_refparton_flavor[MAXJETS], t_calo_refparton_flavorForB[MAXJETS];
  // MC Variables Calo Jets : Gen Jet Variables
  Int_t t_calo_ngen;
  Int_t t_calo_genmatchindex[MAXJETS];
  Float_t t_calo_geneta[MAXJETS], t_calo_genpt[MAXJETS], t_calo_genphi[MAXJETS];
  
  
  Int_t pf_nref=0;
  Float_t t_pf_jtpt[MAXJETS], t_pf_jteta[MAXJETS], t_pf_jtphi[MAXJETS], t_pf_rawpt[MAXJETS], t_pf_trackMax[MAXJETS];
  Float_t t_pf_discr_ssvHighEff[MAXJETS], t_pf_discr_ssvHighPur[MAXJETS], t_pf_discr_csvV1[MAXJETS], t_pf_discr_csvV2[MAXJETS];
  Float_t t_pf_discr_prob[MAXJETS], t_pf_svtxm[MAXJETS], t_pf_svtxpt[MAXJETS], t_pf_svtxmcorr[MAXJETS], t_pf_svtxdl[MAXJETS], t_pf_svtxdls[MAXJETS];
  // MC Variables PF Jets
  Float_t t_pf_pthat, t_pf_weight;
  Float_t t_pf_refpt[MAXJETS], t_pf_refeta[MAXJETS], t_pf_refphi[MAXJETS];
  Int_t t_pf_refparton_flavor[MAXJETS], t_pf_refparton_flavorForB[MAXJETS];
  Int_t t_pf_matchedHadronFlavor[MAXJETS], t_pf_matchedPartonFlavor[MAXJETS];
  // MC Variables PF Jets : Gen Jet Variables
  Int_t t_pf_ngen=0;
  Int_t t_pf_genmatchindex[MAXJETS];
  Float_t t_pf_geneta[MAXJETS], t_pf_genpt[MAXJETS], t_pf_genphi[MAXJETS];


  const int MAXPARTICLES = 100000;
  
  Int_t t_nTrk=0;
  Float_t t_trkPt[MAXPARTICLES], t_trkEta[MAXPARTICLES], t_trkPhi[MAXPARTICLES];
  Float_t t_trkDxy[MAXPARTICLES], t_trkDxyError[MAXPARTICLES], t_trkDz[MAXPARTICLES], t_trkDzError[MAXPARTICLES];
  
  Int_t t_trkpfType[MAXPARTICLES];
  Float_t t_trkpfEcal[MAXPARTICLES], t_trkpfHcal[MAXPARTICLES];
  //Bool_t t_trkMVALoose[MAXPARTICLES], t_trkMVATight[MAXPARTICLES], t_trkloose[MAXPARTICLES];
  Bool_t  t_trktight[MAXPARTICLES];
  
  UChar_t t_trkNHit[MAXPARTICLES]; 
  //UChar_t t_trkAlgo[MAXPARTICLES];
  UChar_t t_trkNlayer[MAXPARTICLES];
  float t_trkChi2[MAXPARTICLES];
  UChar_t t_trkNdof[MAXPARTICLES];
  
  Float_t t_trkPtError[MAXPARTICLES];	
  Bool_t t_trkhighPurity[MAXPARTICLES];
  
  // Gen Particle Variables
  Int_t t_mult =0;
  vector<float> *t_pt=0, *t_phi=0, *t_eta=0;
  vector<int> *t_pdg=0, *t_chg=0, *t_sube=0;
  


  std::ifstream instr(in_file_name.c_str(), std::ifstream::in);

  if(!instr.is_open() ) cout << "filelist not found!! Exiting..." << endl;
  std::string filename;
  int ifile=0;
  cout<<endfile<<" total files need to run. "<<endl;
  
  while(instr>>filename && ifile<endfile){
    
    cout<< " ifile "<<ifile<<endl;
    
    filename.erase(std::remove(filename.begin(), filename.end(), '"'), filename.end());
    filename.erase(std::remove(filename.begin(), filename.end(), ','), filename.end());
    filename.erase(std::remove(filename.begin(), filename.end(), '['), filename.end());
    filename.erase(std::remove(filename.begin(), filename.end(), ']'), filename.end());
    
    cout<<"File name is "<< filename <<endl;
    
    TFile *my_file = NULL;
    
    if(doCrab ==1){
      int pos = filename.find_first_of('s');  // find first s in file name 
      string reducedfn = filename.substr(pos-1); // this is to remove /hadoop if you have file list as /hadoop/store/ (pos-1) is to keep the /
      string xrdPrefix = "root://cmsxrootd.fnal.gov/";
      //string xrdPrefix = "root://eoscms.cern.ch/";
      cout << "local file not detected. Trying " << xrdPrefix+reducedfn << endl;
      my_file = TFile::Open((xrdPrefix+reducedfn).c_str());
    }
    else{my_file = TFile::Open(filename.c_str());}
    ifile++;
    //if(!my_file){cout << "File cannot be found!!" << endl; exit(1); }	
    if(!my_file){cout << "File cannot be found!! moving to next file" << endl; continue; }	
    if(my_file->IsZombie()) { 
      cout << "Is zombie" << std::endl;
      continue;
    }
    
    
    
    if(do_PbPb){
      // be careful here, there are no calojets in skim any more
      //calojets are actually akCs4PFJetAnalyzer
      //inp_tree = (TTree*)  my_file->Get(Form("akPu%dCaloJetAnalyzer/t",radius));
      //inp_tree = (TTree*)  my_file->Get(Form("akPu%dPFJetAnalyzer/t",radius));
      inp_tree = (TTree*)  my_file->Get(Form("akCs%dPFJetAnalyzer/t",radius)); // CS Jets
      
      //pf_tree = (TTree*) my_file->Get(Form("akPu%dPFJetAnalyzer/t",radius)); // PU Jets
      //pf_tree = (TTree*) my_file->Get(Form("akCs%dPFJetAnalyzer/t",radius));   // CS Jets
      pf_tree = (TTree*) my_file->Get(Form("akFlowPuCs%dPFJetAnalyzer/t",radius));   //akFlowPuCs4PFJetAnalyzer
    }else{
      inp_tree = (TTree*)  my_file->Get(Form("ak%dCaloJetAnalyzer/t",radius));
      pf_tree = (TTree*) my_file->Get(Form("ak%dPFJetAnalyzer/t",radius));
    }
    
    if(do_calojets && !inp_tree ){cout << "Calo Jet Tree not found!! Exiting..." << endl; exit(1); }
    if(!pf_tree){cout << "PF Jet Tree not found!! Exiting..." << endl; exit(1); }
    
    track_tree = (TTree*) my_file->Get("ppTrack/trackTree");
    if(do_tracks && !track_tree){ cout << "Track Tree not found!! Exiting..." << endl; exit(1); }
    
    event_tree = (TTree*) my_file->Get("hiEvtAnalyzer/HiTree");
    if(!event_tree){ cout << "Event Tree not found!! Exiting..." << endl; exit(1); }
    
    hlt_tree = (TTree*) my_file->Get("hltanalysis/HltTree");
    if(!hlt_tree){ cout << "HLT Tree not found!! Exiting..." << endl; exit(1); }
    
    skim_tree = (TTree*) my_file->Get("skimanalysis/HltTree");
    if(!skim_tree){ cout << "SKIM Tree not found!! Exiting..." << endl; exit(1); }
    
    muon_tree = (TTree*) my_file->Get("ggHiNtuplizerGED/EventTree");
    if(!muon_tree){ cout << "Muon Tree not found!! Exiting..." << endl; exit(1); }
    
    if(!is_data){
      gen_tree = (TTree*) my_file->Get("HiGenParticleAna/hi");
      if(!gen_tree){ cout << "Gen Tree not found!! Exiting..." << endl; exit(1); }
    }
    
    event_tree->SetBranchAddress("run",&run);
    event_tree->SetBranchAddress("evt",&evt);
    event_tree->SetBranchAddress("lumi",&lumi);
    event_tree->SetBranchAddress("vx",&vx);
    event_tree->SetBranchAddress("vy",&vy);
    event_tree->SetBranchAddress("vz",&vz);
    event_tree->SetBranchAddress("hiBin",&hiBin);
    
    hlt_tree->SetBranchAddress("HLT_HIPuAK4CaloJet80Eta5p1_v1",&HLT_HIPuAK4CaloJet80Eta5p1_v1);
    hlt_tree->SetBranchAddress("HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl",&HLT_HIPuAK4CaloJet80Eta5p1_v1_Prescl);
    hlt_tree->SetBranchAddress("HLT_HIPuAK4CaloJet100Eta5p1_v1",&HLT_HIPuAK4CaloJet100Eta5p1_v1);
    hlt_tree->SetBranchAddress("HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl",&HLT_HIPuAK4CaloJet100Eta5p1_v1_Prescl);
    hlt_tree->SetBranchAddress("HLT_HIPuAK4CaloJet120Eta5p1_v1",&HLT_HIPuAK4CaloJet120Eta5p1_v1);
    hlt_tree->SetBranchAddress("HLT_HIPuAK4CaloJet120Eta5p1_v1_Prescl",&HLT_HIPuAK4CaloJet120Eta5p1_v1_Prescl);
    
    hlt_tree->SetBranchAddress("HLT_HIL3Mu12_v1",&HLT_HIL3Mu12_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu12_v1_Prescl",&HLT_HIL3Mu12_v1_Prescl);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu15_v1",&HLT_HIL3Mu15_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu15_v1_Prescl",&HLT_HIL3Mu15_v1_Prescl);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu20_v1",&HLT_HIL3Mu20_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu20_v1_Prescl",&HLT_HIL3Mu20_v1_Prescl);
    
    // Muon + Jet (Cross-Trigger)
    hlt_tree->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1_Prescl);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1_Prescl);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1_Prescl);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1);
    hlt_tree->SetBranchAddress("HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl",&HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1_Prescl);
    

    if(!do_PbPb){
      
      hlt_tree->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet30_v1",&HLT_HIL3Mu5_AK4PFJet30_v1);
      hlt_tree->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet30_v1_Prescl",&HLT_HIL3Mu5_AK4PFJet30_v1_Prescl);  
      hlt_tree->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet40_v1",&HLT_HIL3Mu5_AK4PFJet40_v1);
      hlt_tree->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet40_v1_Prescl",&HLT_HIL3Mu5_AK4PFJet40_v1_Prescl);  
      hlt_tree->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet60_v1",&HLT_HIL3Mu5_AK4PFJet60_v1);
      hlt_tree->SetBranchAddress("HLT_HIL3Mu5_AK4PFJet60_v1_Prescl",&HLT_HIL3Mu5_AK4PFJet60_v1_Prescl);  
    }

    
    skim_tree->SetBranchAddress("pBeamScrapingFilter",&pBeamScrapingFilter);
    skim_tree->SetBranchAddress("collisionEventSelectionAOD",&collisionEventSelectionAOD);
    skim_tree->SetBranchAddress("collisionEventSelectionAODv2",&collisionEventSelectionAODv2);
    skim_tree->SetBranchAddress("pVertexFilterCutG",&pVertexFilterCutG);
    skim_tree->SetBranchAddress("pVertexFilterCutG",&pVertexFilterCutG);
    skim_tree->SetBranchAddress("pVertexFilterCutGloose",&pVertexFilterCutGloose); 
    skim_tree->SetBranchAddress("pVertexFilterCutGtight",&pVertexFilterCutGtight); 
    skim_tree->SetBranchAddress("pVertexFilterCutGplus",&pVertexFilterCutGplus); 
    skim_tree->SetBranchAddress("pVertexFilterCutE",&pVertexFilterCutE); 
    skim_tree->SetBranchAddress("pVertexFilterCutEandG",&pVertexFilterCutEandG); 
    skim_tree->SetBranchAddress("pHBHENoiseFilterResultProducer",&pHBHENoiseFilterResultProducer); 
    skim_tree->SetBranchAddress("HBHENoiseFilterResult",&HBHENoiseFilterResult); 
    skim_tree->SetBranchAddress("HBHENoiseFilterResultRun1",&HBHENoiseFilterResultRun1); 
    skim_tree->SetBranchAddress("HBHENoiseFilterResultRun2Loose",&HBHENoiseFilterResultRun2Loose); 
    skim_tree->SetBranchAddress("HBHENoiseFilterResultRun2Tight",&HBHENoiseFilterResultRun2Tight); 
    skim_tree->SetBranchAddress("HBHEIsoNoiseFilterResult",&HBHEIsoNoiseFilterResult); 
    skim_tree->SetBranchAddress("superFilterPath",&superFilterPath);
  
    if(do_calojets){
      inp_tree->SetBranchAddress("nref",&calo_nref);
      inp_tree->SetBranchAddress("jtpt",t_calo_jtpt);
      inp_tree->SetBranchAddress("jteta",t_calo_jteta);
      inp_tree->SetBranchAddress("jtphi",t_calo_jtphi);
      inp_tree->SetBranchAddress("rawpt",t_calo_rawpt);
      inp_tree->SetBranchAddress("trackMax",t_calo_trackMax);
      inp_tree->SetBranchAddress("discr_ssvHighEff", t_calo_discr_ssvHighEff);
      inp_tree->SetBranchAddress("discr_ssvHighPur", t_calo_discr_ssvHighPur);
      inp_tree->SetBranchAddress("discr_csvV1", t_calo_discr_csvV1);
      inp_tree->SetBranchAddress("discr_csvV2", t_calo_discr_csvV2);
      inp_tree->SetBranchAddress("discr_prob", t_calo_discr_prob);
      inp_tree->SetBranchAddress("svtxdl", t_calo_svtxdl);
      inp_tree->SetBranchAddress("svtxdls", t_calo_svtxdls);
      inp_tree->SetBranchAddress("svtxm", t_calo_svtxm);
      inp_tree->SetBranchAddress("svtxpt", t_calo_svtxpt);
      inp_tree->SetBranchAddress("svtxmcorr", t_calo_svtxmcorr);
      // MC Variables
      if(!is_data){
	inp_tree->SetBranchAddress("pthat",&t_calo_pthat);
	inp_tree->SetBranchAddress("weight",&t_calo_weight);
	inp_tree->SetBranchAddress("refpt",  t_calo_refpt);
	inp_tree->SetBranchAddress("refeta", t_calo_refeta);
	inp_tree->SetBranchAddress("refphi", t_calo_refphi);
	inp_tree->SetBranchAddress("refparton_flavor", t_calo_refparton_flavor);
	inp_tree->SetBranchAddress("refparton_flavorForB", t_calo_refparton_flavorForB);
	// PF Jet : Gen Jet Variables
	inp_tree->SetBranchAddress("ngen",&t_calo_ngen);
	inp_tree->SetBranchAddress("genmatchindex",t_calo_genmatchindex);
	inp_tree->SetBranchAddress("geneta",t_calo_geneta);
	inp_tree->SetBranchAddress("genpt",t_calo_genpt);
	inp_tree->SetBranchAddress("genphi",t_calo_genphi);
      }
    }//do_calojets
    
    pf_tree->SetBranchAddress("nref",&pf_nref);
    pf_tree->SetBranchAddress("jtpt",t_pf_jtpt);
    pf_tree->SetBranchAddress("jteta",t_pf_jteta);
    pf_tree->SetBranchAddress("jtphi",t_pf_jtphi);
    pf_tree->SetBranchAddress("rawpt",t_pf_rawpt);
    pf_tree->SetBranchAddress("trackMax",t_pf_trackMax);
    pf_tree->SetBranchAddress("discr_ssvHighEff", t_pf_discr_ssvHighEff);
    pf_tree->SetBranchAddress("discr_ssvHighPur", t_pf_discr_ssvHighPur);
    pf_tree->SetBranchAddress("discr_csvV1", t_pf_discr_csvV1);
    pf_tree->SetBranchAddress("discr_csvV2", t_pf_discr_csvV2);
    pf_tree->SetBranchAddress("discr_prob", t_pf_discr_prob);
    pf_tree->SetBranchAddress("svtxdl", t_pf_svtxdl);
    pf_tree->SetBranchAddress("svtxdls", t_pf_svtxdls);
    pf_tree->SetBranchAddress("svtxm", t_pf_svtxm);
    pf_tree->SetBranchAddress("svtxpt", t_pf_svtxpt);
    pf_tree->SetBranchAddress("svtxmcorr", t_pf_svtxmcorr);
    // MC Variables
    if(!is_data){
      
      pf_tree->SetBranchAddress("pthat",&t_pf_pthat);
      pf_tree->SetBranchAddress("weight",&t_pf_weight);
      pf_tree->SetBranchAddress("refpt",  t_pf_refpt);
      pf_tree->SetBranchAddress("refeta", t_pf_refeta);
      pf_tree->SetBranchAddress("refphi", t_pf_refphi);
      pf_tree->SetBranchAddress("refparton_flavor", t_pf_refparton_flavor);
      pf_tree->SetBranchAddress("refparton_flavorForB", t_pf_refparton_flavorForB);
      pf_tree->SetBranchAddress("matchedHadronFlavor", t_pf_matchedHadronFlavor);
      pf_tree->SetBranchAddress("matchedPartonFlavor", t_pf_matchedPartonFlavor);
      
      // PF Jet : Gen Jet Variables
      pf_tree->SetBranchAddress("ngen",&t_pf_ngen);
      pf_tree->SetBranchAddress("genmatchindex",t_pf_genmatchindex);
      pf_tree->SetBranchAddress("geneta",t_pf_geneta);
      pf_tree->SetBranchAddress("genpt",t_pf_genpt);
      pf_tree->SetBranchAddress("genphi",t_pf_genphi);
    }  
    
  
    if(do_tracks){
      //Track Tree Event Variables
      track_tree->SetBranchAddress("nTrk",&t_nTrk);
      // Track Variables
      track_tree->SetBranchAddress("trkPt",t_trkPt);
      track_tree->SetBranchAddress("trkEta",t_trkEta);
      track_tree->SetBranchAddress("trkPhi",t_trkPhi);
      //track_tree->SetBranchAddress("trkAlgo",t_trkAlgo);
      track_tree->SetBranchAddress("tight",t_trktight);
      track_tree->SetBranchAddress("highPurity",t_trkhighPurity);
      track_tree->SetBranchAddress("trkDxy1",t_trkDxy);
      track_tree->SetBranchAddress("trkDxyError1",t_trkDxyError);
      track_tree->SetBranchAddress("trkDz1",t_trkDz);
      track_tree->SetBranchAddress("trkDzError1",t_trkDzError);
      //cout << " 2 "<<endl;
      track_tree->SetBranchAddress("trkPtError",t_trkPtError);
      track_tree->SetBranchAddress("trkNHit",t_trkNHit);
      track_tree->SetBranchAddress("trkNlayer",t_trkNlayer);
      track_tree->SetBranchAddress("trkChi2",t_trkChi2);
      track_tree->SetBranchAddress("trkNdof",t_trkNdof);
      
      track_tree->SetBranchAddress("pfType",t_trkpfType);
      track_tree->SetBranchAddress("pfEcal",t_trkpfEcal);
      track_tree->SetBranchAddress("pfHcal",t_trkpfHcal);
      
      //track_tree->SetBranchAddress("trkMVALoose",t_trkMVALoose);
      //track_tree->SetBranchAddress("trkMVATight",t_trkMVATight);
      //track_tree->SetBranchAddress("loose",t_trkloose);
    }
    
    muon_tree->SetBranchAddress("muPt" , &mu_pt);
    muon_tree->SetBranchAddress("muPhi", &mu_phi);
    muon_tree->SetBranchAddress("muEta", &mu_eta);
    muon_tree->SetBranchAddress("muCharge",        &mu_chg);
    muon_tree->SetBranchAddress("muType",       &mu_type);
    muon_tree->SetBranchAddress("muIsGlobal",     &mu_isGlobal);
    muon_tree->SetBranchAddress("muIsTracker",     &mu_isTracker);
    muon_tree->SetBranchAddress("muIsPF",     &mu_isPF);
    muon_tree->SetBranchAddress("muIsSTA",     &mu_isSTA);
    muon_tree->SetBranchAddress("muD0" , &mu_D0);
    muon_tree->SetBranchAddress("muDz" , &mu_Dz);
    muon_tree->SetBranchAddress("muChi2NDF", &mu_chi2ndf);
    muon_tree->SetBranchAddress("muInnerD0", &mu_innerD0);
    muon_tree->SetBranchAddress("muInnerDz", &mu_innerDz);
    muon_tree->SetBranchAddress("muInnerD0Err", &mu_innerD0Err);
    muon_tree->SetBranchAddress("muInnerDzErr", &mu_innerDzErr);
    muon_tree->SetBranchAddress("muInnerPt", &mu_innerPt);
    muon_tree->SetBranchAddress("muInnerPtErr", &mu_innerPtErr);
    muon_tree->SetBranchAddress("muInnerEta", &mu_innerEta);
    //muon_tree->SetBranchAddress("muInnerHP", &mu_innerHP);
    muon_tree->SetBranchAddress("muIsGood",     &mu_isGood);
    muon_tree->SetBranchAddress("muTrkLayers",  &mu_trkLayers);
    muon_tree->SetBranchAddress("muPixelLayers",&mu_pixelLayers);
    muon_tree->SetBranchAddress("muPixelHits",  &mu_pixelHits);
    muon_tree->SetBranchAddress("muMuonHits",   &mu_muonHits);
    muon_tree->SetBranchAddress("muTrkQuality", &mu_trkQuality);
    muon_tree->SetBranchAddress("muStations",&mu_stations);
    
    if(!is_data){
      gen_tree->SetBranchAddress("mult", &t_mult);
      gen_tree->SetBranchAddress("eta", &t_eta);
      gen_tree->SetBranchAddress("pt", &t_pt);
      gen_tree->SetBranchAddress("phi", &t_phi);
      gen_tree->SetBranchAddress("chg", &t_chg);
      gen_tree->SetBranchAddress("sube", &t_sube);
      gen_tree->SetBranchAddress("pdg", &t_pdg);
    }
    
    //entries for all the trees should be equal
    //if( (inp_tree->GetEntriesFast() !=  pf_tree->GetEntriesFast()) || (inp_tree->GetEntriesFast() !=  track_tree->GetEntriesFast())
    //  || (inp_tree->GetEntriesFast() !=  muon_tree->GetEntriesFast()) ) {cout<<" Tree Entries are not equal "<<endl; exit(1);}  
      
    Int_t PrintEv = 100000;
    
    int n_evt = pf_tree->GetEntriesFast();
  
    //n_evt=10;
    
    cout << "Entries: "<< n_evt << endl;
    
    for(int evi = 0; evi < n_evt; evi++) {
      
      if(evi%(PrintEv*10) == 0 ) cout<<"processing "<<evi<<"..."<<endl;
      
      if(do_calojets)inp_tree->GetEntry(evi);
      pf_tree->GetEntry(evi);
      if(do_tracks)track_tree->GetEntry(evi);
      event_tree->GetEntry(evi);
      hlt_tree->GetEntry(evi);
      skim_tree->GetEntry(evi);
      muon_tree->GetEntry(evi);
      
      if(!is_data)gen_tree->GetEntry(evi);
      
      if(evi %PrintEv == 0 ) cout<<run<<"   "<<evt<<"  "<<lumi<<endl;
      if(evi %PrintEv == 0 ) cout<<" Calo Jets "<<calo_nref<<endl;

      if(evi %PrintEv == 0 ) cout<<" HLT Muon "<< HLT_HIL3Mu12_v1 <<" Mu+Jet "<< HLT_HIL3Mu5_AK4PFJet60_v1 <<endl;
      

      //start calo jet loop
      Double_t calo_jteta_max = 2.4;
      Double_t calo_jtpt_min = 30.0;
      
      if(do_calojets && !is_data){
	calo_pthat = t_calo_pthat;
	calo_weight = t_calo_weight;
      }
      
      for(int j1 = 0; j1 < calo_nref ; j1++)
	{
	  
	  if( fabs(t_calo_jteta[j1]) > calo_jteta_max || t_calo_jtpt[j1] < calo_jtpt_min) continue;
	  
	  Float_t reco_pt = t_calo_jtpt[j1];
	  Float_t reco_phi = t_calo_jtphi[j1];
	  Float_t reco_eta = t_calo_jteta[j1];
	  Float_t raw_pt = t_calo_rawpt[j1];
	  	  
	  JEC.SetJetPT(raw_pt);
          JEC.SetJetEta(reco_eta);
          JEC.SetJetPhi(reco_phi);

          double CorrectedPT = JEC.GetCorrectedPT();
	  
	  Float_t corrected_pt = CorrectedPT; 
	  Float_t track_max = t_calo_trackMax[j1];
	  calo_jteta.push_back(reco_eta);
	  calo_jtphi.push_back(reco_phi);
	  calo_jtpt.push_back(reco_pt);
	  calo_corrpt.push_back(corrected_pt);
	  calo_rawpt.push_back(raw_pt);
	  calo_trackMax.push_back(track_max);
	  
	  //========== Tagger variables ==============//
	  calo_discr_ssvHighEff.push_back(t_calo_discr_ssvHighEff[j1]);
	  calo_discr_ssvHighPur.push_back(t_calo_discr_ssvHighPur[j1]);
	  calo_discr_csvV1.push_back(t_calo_discr_csvV1[j1]);
	  calo_discr_csvV2.push_back(t_calo_discr_csvV2[j1]);
	  calo_discr_prob.push_back(t_calo_discr_prob[j1]);
	  calo_svtxm.push_back(t_calo_svtxm[j1]);
	  calo_svtxpt.push_back(t_calo_svtxpt[j1]);
	  calo_svtxmcorr.push_back(t_calo_svtxmcorr[j1]);
	  calo_svtxdl.push_back(t_calo_svtxdl[j1]);
	  calo_svtxdls.push_back(t_calo_svtxdls[j1]);
	  //MC Variables
	  if(!is_data){
	    calo_refpt.push_back(t_calo_refpt[j1]);
	    calo_refphi.push_back(t_calo_refphi[j1]);
	    calo_refeta.push_back(t_calo_refeta[j1]);
	    calo_refparton_flavor.push_back(t_calo_refparton_flavor[j1]);
	    calo_refparton_flavorForB.push_back(t_calo_refparton_flavorForB[j1]);
	  }
	}//calo jet loop
      
      
      //MC Variables : Calo Jet Gen Jet Variables
      if(!is_data){
	//cout<<t_calo_ngen<<" t_calo_ngen "<<endl;
	calo_ngen =t_calo_ngen;
	
	for(int j1 = 0; j1 < t_calo_ngen ; j1++)
	  {
	    //cout<<t_calo_genmatchindex[0]<<endl;
	    calo_genmatchindex.push_back(t_calo_genmatchindex[j1]);
	    calo_geneta.push_back(t_calo_geneta[j1]);
	    calo_genpt.push_back(t_calo_genpt[j1]);
	    calo_genphi.push_back(t_calo_genphi[j1]);
	    
	  }
      }//!is_data
      
      
      
      //if(evi %PrintEv == 0 ) cout<<endl<<endl;
      
    
      Double_t pf_jteta_max = 2.4;
      Double_t pf_jtpt_min = 30.0;
      
      

      if(evi %PrintEv == 0 ) cout<<" PF Jets "<<pf_nref<<endl;
      
      if(!is_data){
	pf_pthat = t_pf_pthat;
	pf_weight = t_pf_weight;
      }
      for(int j1 = 0; j1 < pf_nref ; j1++)
	{
	  
	  if( fabs(t_pf_jteta[j1]) > pf_jteta_max || t_pf_jtpt[j1] < pf_jtpt_min) continue;
	  
	  Float_t reco_pt = t_pf_jtpt[j1];
	  Float_t reco_phi = t_pf_jtphi[j1];
	  Float_t reco_eta = t_pf_jteta[j1];
	  Float_t raw_pt = t_pf_rawpt[j1];

	  JEC.SetJetPT(raw_pt);
	  JEC.SetJetEta(reco_eta);
	  JEC.SetJetPhi(reco_phi);

	  
	  double CorrectedPT = JEC.GetCorrectedPT();
	  Float_t corrected_pt = CorrectedPT;
	  Float_t track_max = t_pf_trackMax[j1];
	  
	  
	  pf_jteta.push_back(reco_eta);
	  pf_jtphi.push_back(reco_phi);
	  pf_jtpt.push_back(reco_pt);
	  pf_corrpt.push_back(corrected_pt);
	  pf_rawpt.push_back(raw_pt);
	  pf_trackMax.push_back(track_max);
	  
	
	  //========== Tagger variables ==============//
	  pf_discr_ssvHighEff.push_back(t_pf_discr_ssvHighEff[j1]);
	  pf_discr_ssvHighPur.push_back(t_pf_discr_ssvHighPur[j1]);
	  pf_discr_csvV1.push_back(t_pf_discr_csvV1[j1]);
	  pf_discr_csvV2.push_back(t_pf_discr_csvV2[j1]);
	  pf_discr_prob.push_back(t_pf_discr_prob[j1]);
	  pf_svtxm.push_back(t_pf_svtxm[j1]);
	  pf_svtxpt.push_back(t_pf_svtxpt[j1]);
	  pf_svtxmcorr.push_back(t_pf_svtxmcorr[j1]);
	  pf_svtxdl.push_back(t_pf_svtxdl[j1]);
	  pf_svtxdls.push_back(t_pf_svtxdls[j1]);
	  
	  
	  //MC Variables
	  if(!is_data){
	    pf_refpt.push_back(t_pf_refpt[j1]);
	    pf_refphi.push_back(t_pf_refphi[j1]);
	    pf_refeta.push_back(t_pf_refeta[j1]);
	    pf_refparton_flavor.push_back(t_pf_refparton_flavor[j1]);
	    pf_refparton_flavorForB.push_back(t_pf_refparton_flavorForB[j1]);
	    pf_matchedHadronFlavor.push_back(t_pf_matchedHadronFlavor[j1]);
	    pf_matchedPartonFlavor.push_back(t_pf_matchedPartonFlavor[j1]);
	    
	  }
	  
	}//pf jet loop
      
    
      //MC Variables : PF Gen Jet Variables
      if(!is_data){
	
	pf_ngen =t_pf_ngen;
	
	for(int j1 = 0; j1 < t_pf_ngen ; j1++)
	  {      
	    pf_genmatchindex.push_back(t_pf_genmatchindex[j1]);
	    pf_geneta.push_back(t_pf_geneta[j1]);
	    pf_genpt.push_back(t_pf_genpt[j1]);
	    pf_genphi.push_back(t_pf_genphi[j1]);
	    
	  }
      }//!is_data
      

      //================== Track Loop =================//
      //Float_t track_eta_max = 2.4;
      //Float_t track_pt_min = 0.5;
      //Basic Track quality Cuts
      //Float_t track_pt_error_by_pt_max = 0.3;
      //Int_t track_hits_min = 8;
      //Float_t track_chi2_norm_min = 0.15;
      
      if(evi %PrintEv == 0 ) cout<<" tracks "<<t_nTrk<<endl;
      
      //// reco track loop
      for(int itrk=0;itrk<t_nTrk;itrk++){
	
	//if(TMath::Abs(t_trkEta[itrk]) > track_eta_max || t_trkPt[itrk] < track_pt_min ) continue; //acceptance of the tracker   
	//if(t_trktight[itrk]!=1)continue; // only tight tracks (highPurity is a subset of this)
	//if(t_trkhighPurity[itrk]!=1)continue; // only highPurity tracks
	//very basic track quality cuts      
	//if( (t_trkPtError[itrk]/t_trkPt[itrk] >= track_pt_error_by_pt_max) ||
	//( t_trkNHit[itrk] < track_hits_min) ||
	//(t_trkChi2[itrk]/t_trkNdof[itrk]/t_trkNlayer[itrk] > track_chi2_norm_min) )continue;
	Bool_t is_pp = !do_PbPb;
	Bool_t useTightCuts = 1;
	if(!passTrackCuts(is_pp, useTightCuts, t_trkPt[itrk], t_trkEta[itrk], t_trktight[itrk], t_trkChi2[itrk], t_trkNdof[itrk], t_trkNlayer[itrk],
			  t_trkNHit[itrk], t_trkpfHcal[itrk], t_trkpfEcal[itrk],
			  t_trkDxy[itrk]/t_trkDxyError[itrk], t_trkDz[itrk]/t_trkDzError[itrk])) continue;
	
	trkEta.push_back(t_trkEta[itrk]);
	trkPhi.push_back(t_trkPhi[itrk]);
	trkPt.push_back(t_trkPt[itrk]);
	
	//trkAlgo.push_back(t_trkAlgo[itrk]);
	//trkloose.push_back(t_trkloose[itrk]);
	//trktight.push_back(t_trktight[itrk]);
	trkhighPurity.push_back(t_trkhighPurity[itrk]);
	//trkDxy.push_back(t_trkDxy[itrk]);
	//trkDxyError.push_back(t_trkDxyError[itrk]);
	//trkDz.push_back(t_trkDz[itrk]);
	//trkDzError.push_back(t_trkDzError[itrk]);
	trkPtError.push_back(t_trkPtError[itrk]);
	//trkNHit.push_back((int)t_trkNHit[itrk]);
	//trkNlayer.push_back((int)t_trkNlayer[itrk]);
	//trkChi2.push_back(t_trkChi2[itrk]);
	//trkNdof.push_back((int)t_trkNdof[itrk]);
	trkpfType.push_back(t_trkpfType[itrk]);
	//trkpfEcal.push_back(t_trkpfEcal[itrk]);
	//trkpfHcal.push_back(t_trkpfHcal[itrk]);
	//trkMVALoose.push_back(t_trkMVALoose[itrk]);
	//trkMVATight.push_back(t_trkMVATight[itrk]);
      }
      

      //======================= Gen Particle Loop ========================//
      if(!is_data){
	for(int ipart=0;ipart<t_mult;ipart++){
	  
	  if(TMath::Abs(t_eta->at(ipart))>trketamaxcut)continue; //acceptance of the tracker
	  if(t_pt->at(ipart) < trkPtCut) continue; //acceptance of the tracker
	  
	  eta.push_back(t_eta->at(ipart));
	  pt.push_back(t_pt->at(ipart));	
	  phi.push_back(t_phi->at(ipart));
	  
	  chg.push_back(t_chg->at(ipart));
	  sube.push_back(t_sube->at(ipart));
	  pdg.push_back(t_pdg->at(ipart));
	  
	}
      }
      



      //======= Basic Event Cuts =================//
      Int_t BasicEventCuts;
      
      //Basic Cuts are not finalized yet
      //if(HLT_HIL3Mu12_v1 ==1 && collisionEventSelectionAOD==1){BasicEventCuts=1;}
      //if(collisionEventSelectionAOD==1){BasicEventCuts=1;}
      //else{BasicEventCuts=0;}
      
      mixing_tree->Fill();
      
      // clear all the vectors
      calo_jteta.clear();
      calo_jtphi.clear();
      calo_jtpt.clear();
      calo_corrpt.clear();
      calo_rawpt.clear();
      calo_trackMax.clear();
      calo_discr_ssvHighEff.clear();
      calo_discr_ssvHighPur.clear();
      calo_discr_csvV1.clear();
      calo_discr_csvV2.clear();
      calo_discr_prob.clear();
      calo_svtxm.clear();
      calo_svtxpt.clear();
      calo_svtxmcorr.clear();
      calo_svtxdl.clear();
      calo_svtxdls.clear();
      // MC Variables Calo Jet
      calo_refeta.clear();
      calo_refpt.clear();
      calo_refphi.clear();
      calo_refparton_flavor.clear();
      calo_refparton_flavorForB.clear();
      // MC Variables Calo Jet : Gen Jet Variables
      calo_genmatchindex.clear();
      calo_geneta.clear();
      calo_genpt.clear();
      calo_genphi.clear();    
      
      pf_jteta.clear();
      pf_jtphi.clear();
      pf_jtpt.clear();
      pf_corrpt.clear();
      pf_rawpt.clear();
      pf_trackMax.clear();
      pf_discr_ssvHighEff.clear();
      pf_discr_ssvHighPur.clear();
      pf_discr_csvV1.clear();
      pf_discr_csvV2.clear();
      pf_discr_prob.clear();
      pf_svtxm.clear();
      pf_svtxpt.clear();
      pf_svtxmcorr.clear();
      pf_svtxdl.clear();
      pf_svtxdls.clear();
      // MC Variables PF Jets
      pf_refeta.clear(); 
      pf_refpt.clear(); 
      pf_refphi.clear();
      pf_refparton_flavor.clear(); 
      pf_refparton_flavorForB.clear(); 
      pf_matchedHadronFlavor.clear(); 
      pf_matchedPartonFlavor.clear();
      // MC Variables PF Jets : Gen Jet Variables
      pf_genmatchindex.clear();
      pf_geneta.clear(); 
      pf_genpt.clear(); 
      pf_genphi.clear();    
      

      trkEta.clear();
      trkPhi.clear();
      trkPt.clear();
      //trkAlgo.clear();
      trkhighPurity.clear();
      //trkDxy.clear();
      //trkDxyError.clear();
      //trkDz.clear();
      //trkDzError.clear();
      
      trkPtError.clear();
      //trkNHit.clear();
      
      //trkNlayer.clear();
      //trkChi2.clear();
      //trkNdof.clear();
      
      trkpfType.clear();
      //trkpfEcal.clear();
      //trkpfHcal.clear();
      
      //trkMVALoose.clear();
      //trkMVATight.clear();
      //trkloose.clear();
      //trktight.clear();
      
      eta.clear();    
      pt.clear();    
      phi.clear();    
      
      chg.clear();
      sube.clear();
      pdg.clear();
      //if(evi %PrintEv == 0 )cout<<endl<<endl;    
      
    }//Event Loop
    my_file->Close();
  }//while loop
  cout<<"writing"<<endl;
  output_file->cd();
  mixing_tree->Write();
  output_file->Close();
  cout<<"done"<<endl;
}//run_maker
  
  

bool passTrackCuts(bool ispp, bool useTightCuts, float trkPt, float trkEta, bool tightTracks,
		   float trkChi2, int trkNdof, int trkNlayer, int trkNHit, float pfHcal, float pfEcal,
		   float trkDzSigma, float trkDxySigma){
  
  if(abs(trkEta)>=trketamaxcut) return false;
  
  if(!tightTracks) return false;
  
  if(useTightCuts && (TMath::Abs(trkDzSigma)>=3.0 ||TMath::Abs(trkDxySigma)>=3.0)) return false;
  
  if(!ispp && (float)trkChi2/(float)trkNdof/(float)trkNlayer > 0.15) return false;
  
  if(!ispp && trkNHit<11 && trkPt > 0.7) return false;
  
  float Et = (pfHcal+pfEcal)/TMath::CosH(trkEta);
  if(!(trkPt<20 || Et > 0.5*trkPt)) return false;
  
  if(trkPt<=trkPtCut || trkPt > 400) return false;
  
  return true;
}
