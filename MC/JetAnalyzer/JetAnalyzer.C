#define JetAnalyzer_cxx
#include "JetAnalyzer.h"
#ifndef __CINT__
#endif
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TAxis.h"
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TF1.h"
#include "TH1I.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TVector3.h"
#include "TString.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "TObjArray.h"
#include "TGaxis.h"
#include "TLine.h"
#include <iomanip>
#include "TLorentzVector.h"
#include <vector>
#include "THnSparse.h"


//#include "CMS/tdrstyle.C"
//#include "CMS/CMS_lumi.C"

Double_t getPtHatWeight(const Double_t ptHat);
Double_t MuonMass = 0.1056583745;

Double_t getDR  ( Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);
//Double_t getDPHI( Double_t phi1, Double_t phi2);
Double_t plotDPHI( Double_t phi1, Double_t phi2);

Int_t SoftMuonIDCuts(Int_t isGlobal, Int_t isTracker, Int_t isGoodMuon, Int_t nPixWMea, Int_t nTrkWMea, float D0, float DZ);
Int_t TightMuonIDCuts(Int_t isGlobal, Int_t isTracker, float muEta, float muChi2NDF, float muInnerD0, float muInnerDz, Int_t muMuonHits, Int_t muStations, Int_t muTrkLayers, Int_t muPixelHits);


double  deltaR(TLorentzVector GenMuon, TLorentzVector RecoMuon);
double  deltaPt(TLorentzVector GenMuon, TLorentzVector RecoMuon);

Double_t getPtRel(Double_t MuonPt, Double_t MuonEta, Double_t MuonPhi, Double_t JetPt, Double_t JetEta, Double_t JetPhi);



//JetAnalyzer::JetAnalyzer(TTree *tree):fChain(0) 
JetAnalyzer::JetAnalyzer(int doCrab, int jobID, int endfile):fChain(0) 
{


  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  /*
    if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("PYTHIA6.root");
    if (!f || !f->IsOpen()) {
    //f = new TFile("InputRootFiles/PYTHIA6_dijet.root");
    //f = new TFile("InputRootFiles/PYTHIA6.root");
    //f = new TFile("InputRootFiles/PYTHIA6_pthat50.root");
    //f = new TFile("InputRootFiles/PYTHIA6_10k_bjet.root");
    //f = new TFile("InputRootFiles/PYTHIA6_BJet_03Dec2018.root");
    //f = new TFile("InputRootFiles/PYTHIA6_DiJet_03Dec2018.root");
    //f = new TFile("InputRootFiles/DiJet_Pythia6Skim__FullPtHat_08Jan2019_All.root");
    f = new TFile("/Users/vineet/RootFiles/MCSkims/DiJet_Pythia6Skim__FullPtHat_08Jan2019_All.root");
    //f = new TFile("InputRootFiles/PYTHIA8_MBSkim_1-117.root");
    }
    f->GetObject("mixing_tree",tree);
    
    }
  */


  TChain *chain = new TChain("mixing_tree");

  string in_file_list; 
  if(doCrab==1){in_file_list = Form("job_input_file_list_%d.txt",jobID);} //to run on crab
  else{in_file_list = Form("FileList.txt");}
  
  cout<<" Trying a file list "<<in_file_list<<endl;

  std::ifstream instr(in_file_list.c_str(), std::ifstream::in);

  if(!instr.is_open() ) cout << "filelist not found!! Exiting..." << endl;

  std::string filename;
  int ifile=0;
  //int endfile =2;
  cout<<endfile<<" total files need to run. "<<endl;
 
  while(instr>>filename && ifile<endfile){
    
    cout<<"ifile "<<ifile<<endl;

    filename.erase(std::remove(filename.begin(), filename.end(), '"'), filename.end());
    filename.erase(std::remove(filename.begin(), filename.end(), ','), filename.end());
    filename.erase(std::remove(filename.begin(), filename.end(), '['), filename.end());
    filename.erase(std::remove(filename.begin(), filename.end(), ']'), filename.end());
    

    cout<<"File Name is "<<filename<<endl;

    if(doCrab==1){
      int pos = filename.find_first_of('s');  // find first s in file name 
      string reducedfn = filename.substr(pos-1); // this is to remove /hadoop if you have file list as /hadoop/store/ (pos-1) is to keep the /
      string xrdPrefix = "root://cmsxrootd.fnal.gov/";
      //string xrdPrefix = "root://eoscms.cern.ch/";
      cout << "local file not detected. Trying " << xrdPrefix+reducedfn<< endl;
      //chain->Add(filename.c_str());
      chain->Add((xrdPrefix+reducedfn).c_str());
    }
    else{chain->Add(filename.c_str());}
    ifile++;
  }

  //chain->Add("/tmp/kumarv/PP_2017MC_5TeV_MC_100.root");
  //chain->Add("/tmp/kumarv/PP_2017MC_5TeV_MC_101.root");
 
  Init(chain);
}


void JetAnalyzer::Loop()
{

  TH1::SetDefaultSumw2(1);

  //   In a ROOT session, you can do:
  //      Root > .L JetAnalyzer.C
  //      Root > JetAnalyzer t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //
  
  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  
  // 1. All pfJets have cut |eta| < 2 && pT > 25 GeV in skim stage
  //TFile *OutFile = new TFile("DiJet_Pythia6Skim__FullPtHat_08Jan2019_All.root","Recreate");
  //TFile *OutFile = new TFile("DiJet_Pythia6Skim__FullPtHat_20March2019_All.root","Recreate");
  //TFile *OutFile = new TFile("DiJet_Pythia6Skim__FullPtHat_MCMatchedMuon_01April2019_All.root","Recreate");
  //TFile *OutFile = new TFile("DiJet_Pythia6Skim__FullPtHat_MCMatchedMuon_RefPartonFlvForB_03April2019_All.root","Recreate");
  //TFile *OutFile = new TFile("DiJet_Pythia6Skim__FullPtHat_MCMatchedMuon_ForUnKnownJets_11April2019_All.root","Recreate");
  //TFile *OutFile = new TFile("DiJet_Pythia6Skim__FullPtHat_MCMatchedMuon_RefPartonFlvForB_ForUnKnownJets_24April2019_All.root","Recreate");
  //TFile *OutFile = new TFile("DiJet_Pythia6Skim__FullPtHat_Jet80GeV16Mu3GeV_TighestMuon_RefPartonFlvForB_05July2019_All.root","Recreate");

  //TFile *OutFile = new TFile("DiJet_Pythia6Skim__FullPtHat_Jet60GeV2Mu5GeV_TighestMuon_RefPartonFlvForB_24July2019_All.root","Recreate");
  
  // First run with pp 2017 MC
  //TFile *OutFile = new TFile("DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_31July2019.root","Recreate");
  //MC Matching applied
  //TFile *OutFile = new TFile("DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_MCMatched_01Aug2019.root","Recreate");

  TFile *OutFile = new TFile("DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_28Aug2019.root","Recreate");
  

  TH1D *histNumberOfJets = new TH1D("histNumberOfJets","histNumberOfJets",30,0.5,30.5);
  histNumberOfJets->GetXaxis()->SetTitle("Jet Multiplicity");
  histNumberOfJets->GetYaxis()->SetTitle("Entries");
  
  TH1D *histNumberOfGenJets = new TH1D("histNumberOfGenJets","histNumberOfGenJets",30,0.5,30.5);
  histNumberOfGenJets->GetXaxis()->SetTitle("Gen-Jet Multiplicity");
  histNumberOfGenJets->GetYaxis()->SetTitle("Entries");
  

  //const Int_t NBINS = 12;
  //Double_t edges[NBINS + 1] = {0.0, 30.0, 50.0, 80.0, 100.0, 120.0, 170.0, 220.0, 280.0, 370.0, 460.0, 540.0, 3000.0};
  //TH1* histPtHatBins = new TH1D("EventsPtHatBins","EventsPtHatBins", NBINS,edges);
  //const Int_t NBinsGenJetPt = 8;
  //Double_t GenJetPtEdges[NBinsGenJetPt+1] = {30.0, 50.0, 70.0, 100.0, 130.0, 170.0, 220.0, 300.0,450.0};


  Int_t NBinsGenJetPt =100;
  Double_t GenJetPtMin =0.0;
  Double_t GenJetPtMax = 450.0;

  Double_t Pi = TMath::Pi();
  Double_t GenJetPhiMin =-Pi;
  Double_t GenJetPhiMax =Pi;
  
  
  TH1D *histGenJetPt= new TH1D("histGenJetPt","histGenJetPt",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPt->Sumw2();
  histGenJetPt->GetXaxis()->SetTitle("GenJet Pt (GeV/c)");
  histGenJetPt->GetYaxis()->SetTitle("Entries");
  
  TH1D *histGenJetEta = new TH1D("histGenJetEta","histGenJetEta",100,-5,5);
  histGenJetEta->Sumw2();
  histGenJetEta->GetXaxis()->SetTitle("GenJet #eta");
  histGenJetEta->GetYaxis()->SetTitle("Entries");
  
  TH1D *histGenJetPhi = new TH1D("histGenJetPhi","histGenJetPhi",100,GenJetPhiMin,GenJetPhiMax);
  histGenJetPhi->Sumw2();
  histGenJetPhi->GetXaxis()->SetTitle("GenJet #phi");
  histGenJetPhi->GetYaxis()->SetTitle("Entries");

  
  TH1D *histGenJetPtNoRec = new TH1D("histGenJetPtNoRec","histGenJetPtNoRec",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtNoRec->Sumw2();
  histGenJetPtNoRec->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (NoRec)");
  histGenJetPtNoRec->GetYaxis()->SetTitle("Entries");

  TH1D *histGenJetPtUnknownRec = new TH1D("histGenJetPtUnknownRec","histGenJetPtUnknownRec",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtUnknownRec->Sumw2();
  histGenJetPtUnknownRec->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (UnknownRec)");
  histGenJetPtUnknownRec->GetYaxis()->SetTitle("Entries");
  
  TH1D *histGenJetPtLight = new TH1D("histGenJetPtLight","histGenJetPtLight",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtLight->Sumw2();
  histGenJetPtLight->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (u,d,s)");
  histGenJetPtLight->GetYaxis()->SetTitle("Entries");


  TH1D *histGenJetPtUp = new TH1D("histGenJetPtUp","histGenJetPtUp",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtUp->Sumw2();
  histGenJetPtUp->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (u)");
  histGenJetPtUp->GetYaxis()->SetTitle("Entries");


  TH1D *histGenJetPtDown = new TH1D("histGenJetPtDown","histGenJetPtDown",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtDown->Sumw2();
  histGenJetPtDown->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (d)");
  histGenJetPtDown->GetYaxis()->SetTitle("Entries");


  TH1D *histGenJetPtStrange = new TH1D("histGenJetPtStrange","histGenJetPtStrange",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtStrange->Sumw2();
  histGenJetPtStrange->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (s)");
  histGenJetPtStrange->GetYaxis()->SetTitle("Entries");

  TH1D *histGenJetPtCharm = new TH1D("histGenJetPtCharm","histGenJetPtCharm",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtCharm->Sumw2();
  histGenJetPtCharm->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (c)");
  histGenJetPtCharm->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histGenJetPtBeauty = new TH1D("histGenJetPtBeauty","histGenJetPtBeauty",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtBeauty->Sumw2();
  histGenJetPtBeauty->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (b)");
  histGenJetPtBeauty->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histGenJetPtGluon = new TH1D("histGenJetPtGluon","histGenJetPtGluon",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenJetPtGluon->Sumw2();
  histGenJetPtGluon->GetXaxis()->SetTitle("GenJet Pt (GeV/c) (g)");
  histGenJetPtGluon->GetYaxis()->SetTitle("Entries");

  //Int_t NFlavour =6;
  //Double_t FlavourMin =0.5;
  //Double_t FlavourMax =6.5;

  Int_t NFlavour = 9;
  Double_t FlavourMin = 0.5;
  Double_t FlavourMax = 9.5;


  TH2D *hist_GenMaster_GenJetPt_Flavour= new TH2D("hist_GenMaster_GenJetPt_Flavour","hist_GenMaster_GenJetPt_Flavour",NBinsGenJetPt,GenJetPtMin,GenJetPtMax,NFlavour,FlavourMin,FlavourMax);
  hist_GenMaster_GenJetPt_Flavour->Sumw2();
  hist_GenMaster_GenJetPt_Flavour->GetXaxis()->SetTitle("Gen Jet Pt (GeV/c)");
  hist_GenMaster_GenJetPt_Flavour->GetYaxis()->SetTitle("Jet Flavour");
  

  //==================================== Gen Muon Histograms ==================================================//

  Int_t NBinsGenMuEta = 100;
  Double_t GenMuEtaMin = -3.0;
  Double_t GenMuEtaMax = 3.0;

  Int_t NBinsGenMuPt = 100;
  Double_t GenMuPtMin = 0.0;
  Double_t GenMuPtMax = 100.0;

  Int_t NBinsGenMuPhi = 100;

  Double_t GenMuPhiMin = -Pi;
  Double_t GenMuPhiMax = Pi;
    
  // All the Gen Muons
  TH3D *hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi = new TH3D("hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi","hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi",NBinsGenMuEta,GenMuEtaMin,GenMuEtaMax,NBinsGenMuPt,GenMuPtMin,GenMuPtMax,NBinsGenMuPhi,GenMuPhiMin,GenMuPhiMax);
  hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi->Sumw2();
  hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi->GetXaxis()->SetTitle("Gen Mu #eta");
  hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi->GetYaxis()->SetTitle("Gen Mu p_{T} (GeV/c)");
  hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi->GetZaxis()->SetTitle("Gen Mu #phi");



  //Gen Muons matched to Gen Jets
  TH3D *hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi = new TH3D("hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi","hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi",NBinsGenMuEta,GenMuEtaMin,GenMuEtaMax,NBinsGenMuPt,GenMuPtMin,GenMuPtMax,NBinsGenMuPhi,GenMuPhiMin,GenMuPhiMax);
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->Sumw2();
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->GetXaxis()->SetTitle("Gen Jet Matched Gen Mu #eta");
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->GetYaxis()->SetTitle("Gen Jet Matched Gen Mu p_{T} (GeV/c)");
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->GetZaxis()->SetTitle("Gen Jet Matched Gen Mu #phi");



  //Gen Muons matched to Reco Muon
  TH3D *hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi = new TH3D("hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi","hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi",NBinsGenMuEta,GenMuEtaMin,GenMuEtaMax,NBinsGenMuPt,GenMuPtMin,GenMuPtMax,NBinsGenMuPhi,GenMuPhiMin,GenMuPhiMax);
  hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi->Sumw2();
  hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi->GetXaxis()->SetTitle("Rec Mu Matched Gen Mu #eta");
  hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi->GetYaxis()->SetTitle("Rec Mu Matched Gen Mu p_{T} (GeV/c)");
  hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi->GetZaxis()->SetTitle("Rec Mu Matched Gen Mu #phi");

  


  TH1D *histGenMuonPt = new TH1D("histGenMuonPt","histGenMuonPt",NBinsGenMuPt,GenMuPtMin,GenMuPtMax);
  histGenMuonPt->Sumw2();
  histGenMuonPt->GetXaxis()->SetTitle("GenMuon Pt (GeV/c)");
  histGenMuonPt->GetYaxis()->SetTitle("Entries");
  
  TH1D *histGenMuonEta = new TH1D("histGenMuonEta","histGenMuonEta",NBinsGenMuEta,GenMuEtaMin,GenMuEtaMax);
  histGenMuonEta->Sumw2();
  histGenMuonEta->GetXaxis()->SetTitle("GenMuon #eta (GeV/c)");
  histGenMuonEta->GetYaxis()->SetTitle("Entries");


  TH1D *histGenMuonPhi = new TH1D("histGenMuonPhi","histGenMuonPhi",NBinsGenMuPhi,GenMuPhiMin,GenMuPhiMax);
  histGenMuonPhi->Sumw2();
  histGenMuonPhi->GetXaxis()->SetTitle("GenMuon #phi (GeV/c)");
  histGenMuonPhi->GetYaxis()->SetTitle("Entries");



  TH1D *histGenDiMuonInvMass = new TH1D("histGenDiMuonInvMass","histGenDiMuonInvMass",100,0,100);
  histGenDiMuonInvMass->Sumw2();
  histGenDiMuonInvMass->GetXaxis()->SetTitle("GenDiMuon InvMass (GeV/c)");
  histGenDiMuonInvMass->GetYaxis()->SetTitle("Entries");


  TH1D *histGenDiMuonInvMassLow = new TH1D("histGenDiMuonInvMassLow","histGenDiMuonInvMassLow",200,2.0,4.5);
  histGenDiMuonInvMassLow->GetXaxis()->SetTitle("GenDiMuon InvMassLow (GeV/c)");
  histGenDiMuonInvMassLow->GetYaxis()->SetTitle("Entries");


  TH1D *histGenDiMuonInvMassInt = new TH1D("histGenDiMuonInvMassInt","histGenDiMuonInvMassInt",200,8.0,14.0);
  histGenDiMuonInvMassInt->GetXaxis()->SetTitle("GenDiMuon InvMassInt (GeV/c)");
  histGenDiMuonInvMassInt->GetYaxis()->SetTitle("Entries");
  

  TH1D *histGenDiMuonPt = new TH1D("histGenDiMuonPt","histGenDiMuonPt",100,0,100);
  histGenDiMuonPt->GetXaxis()->SetTitle("GenDiMuon Pt (GeV/c)");
  histGenDiMuonPt->GetYaxis()->SetTitle("Entries");

  TH1D *histGenDiMuonRapidity = new TH1D("histGenDiMuonRapidity","histGenDiMuonRapidity",100,-5,5);
  histGenDiMuonRapidity->GetXaxis()->SetTitle("GenDiMuon #eta (GeV/c)");
  histGenDiMuonRapidity->GetYaxis()->SetTitle("Entries");


  TH1D *histGenDiMuonPhi = new TH1D("histGenDiMuonPhi","histGenDiMuonPhi",100,-Pi,Pi);
  histGenDiMuonPhi->GetXaxis()->SetTitle("GenDiMuon #phi (GeV/c)");
  histGenDiMuonPhi->GetYaxis()->SetTitle("Entries");

  
  TH1D *histGenMuonGenJetDR = new TH1D("histGenMuonGenJetDR","histGenMuonGenJetDR",100,0,10);
  histGenMuonGenJetDR->GetXaxis()->SetTitle("GenMuon-Jet #Delta R");
  histGenMuonGenJetDR->GetYaxis()->SetTitle("Entries");



  //DeltaPhi
  const Double_t minDeltaPhiJetMuon = -TMath::Pi()/2.0;    // Minimum deltaPhi for jet-muon 
  const Double_t maxDeltaPhiJetMuon = 3.0*TMath::Pi()/2.0; // Maximum deltaPhi for jet-muon 
  const Int_t nDeltaPhiBinsJetMuon = 200;                  // Number of deltaPhi bins for jet-muon  (match the common number in UIC group)
  
  
  TH1D *histGenMuonGenJetDPhi = new TH1D("histGenMuonGenJetDPhi","histGenMuonGenJetDPhi",nDeltaPhiBinsJetMuon,minDeltaPhiJetMuon,maxDeltaPhiJetMuon);
  histGenMuonGenJetDPhi->GetXaxis()->SetTitle("GenMuon-Jet #Delta #Phi");
  histGenMuonGenJetDPhi->GetYaxis()->SetTitle("Entries");
  

  TH1D *histGenMuonGenJetPtTotal = new TH1D("histGenMuonGenJetPtTotal","histGenMuonGenJetPtTotal",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtTotal->GetXaxis()->SetTitle("GenMuonGenJet Pt (GeV/c) (u,d,s)");
  histGenMuonGenJetPtTotal->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histGenMuonGenJetPtLight = new TH1D("histGenMuonGenJetPtLight","histGenMuonGenJetPtLight",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtLight->GetXaxis()->SetTitle("GenMuonGenJet Pt (GeV/c) (u,d,s)");
  histGenMuonGenJetPtLight->GetYaxis()->SetTitle("Entries");


  
  TH1D *histGenMuonGenJetPtUp = new TH1D("histGenMuonGenJetPtUp","histGenMuonGenJetPtUp",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtUp->GetXaxis()->SetTitle("Jet Pt (GeV/c) (u)");
  histGenMuonGenJetPtUp->GetYaxis()->SetTitle("Entries");


  TH1D *histGenMuonGenJetPtDown = new TH1D("histGenMuonGenJetPtDown","histGenMuonGenJetPtDown",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtDown->GetXaxis()->SetTitle("Jet Pt (GeV/c) (d)");
  histGenMuonGenJetPtDown->GetYaxis()->SetTitle("Entries");


  TH1D *histGenMuonGenJetPtStrange = new TH1D("histGenMuonGenJetPtStrange","histGenMuonGenJetPtStrange",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtStrange->GetXaxis()->SetTitle("Jet Pt (GeV/c) (s)");
  histGenMuonGenJetPtStrange->GetYaxis()->SetTitle("Entries");


  TH1D *histGenMuonGenJetPtCharm = new TH1D("histGenMuonGenJetPtCharm","histGenMuonGenJetPtCharm",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtCharm->GetXaxis()->SetTitle("GenMuonGenJet Pt (GeV/c) (c)");
  histGenMuonGenJetPtCharm->GetYaxis()->SetTitle("Entries");


  TH1D *histGenMuonGenJetPtBeauty = new TH1D("histGenMuonGenJetPtBeauty","histGenMuonGenJetPtBeauty",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtBeauty->GetXaxis()->SetTitle("GenMuonGenJet Pt (GeV/c) (b)");
  histGenMuonGenJetPtBeauty->GetYaxis()->SetTitle("Entries");

  TH1D *histGenMuonGenJetPtGluon = new TH1D("histGenMuonGenJetPtGluon","histGenMuonGenJetPtGluon",NBinsGenJetPt,GenJetPtMin,GenJetPtMax);
  histGenMuonGenJetPtGluon->GetXaxis()->SetTitle("GenMuonGenJet Pt (GeV/c) (g)");
  histGenMuonGenJetPtGluon->GetYaxis()->SetTitle("Entries");

  
  TH3D *hist_GenMaster_GenJetPt_GenMuPt_Flavour = new TH3D("hist_GenMaster_GenJetPt_GenMuPt_Flavour","hist_GenMaster_GenJetPt_GenMuPt_Flavour",NBinsGenJetPt,GenJetPtMin,GenJetPtMax,NBinsGenMuPt,GenMuPtMin,GenMuPtMax,NFlavour,FlavourMin,FlavourMax);
  hist_GenMaster_GenJetPt_GenMuPt_Flavour->GetXaxis()->SetTitle("Gen Jet Pt (GeV/c)");
  hist_GenMaster_GenJetPt_GenMuPt_Flavour->GetYaxis()->SetTitle("Gen #mu Pt (GeV/c)");
  hist_GenMaster_GenJetPt_GenMuPt_Flavour->GetZaxis()->SetTitle("Jet Flavour");

  const Int_t NBinsMuonPtRel = 40;
  const Double_t MuonPtRelMin = 0.0;
  const Double_t MuonPtRelMax = 4.0;
    
  TH3D *hist_GenMaster_GenJetPt_GenMuPtRel_Flavour = new TH3D("hist_GenMaster_GenJetPt_GenMuPtRel_Flavour","hist_GenMaster_GenJetPt_GenMuPtRel_Flavour",NBinsGenJetPt,GenJetPtMin,GenJetPtMax,NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax,NFlavour,FlavourMin,FlavourMax);
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->GetXaxis()->SetTitle("Gen Jet p_{T} (GeV/c)");
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->GetYaxis()->SetTitle("Gen #mu p_{T}-Rel (GeV/c)");
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->GetZaxis()->SetTitle("Jet Flavour");

  //====================================================================================================//
  //=========================================== reco jet histos ========================================//
  //====================================================================================================//
  
  Int_t NBinsJetPt =100;
  Double_t JetPtMin =0.0;
  Double_t JetPtMax = 450.0;
  
  Int_t NBinsMuEta = 100;
  Double_t MuEtaMin = -3.0;
  Double_t MuEtaMax = 3.0;
  
  Int_t NBinsMuPt = 100;
  Double_t MuPtMin = 0.0;
  Double_t MuPtMax = 100.0;
  
  Int_t NBinsMuPhi = 100;
  Double_t MuPhiMin = -Pi;
  Double_t MuPhiMax = Pi;
  
  
  TH2D *hist_Master_JetPt_Flavour = new TH2D("hist_Master_JetPt_Flavour","hist_Master_JetPt_Flavour",NBinsJetPt,JetPtMin,JetPtMax,NFlavour,FlavourMin,FlavourMax);
  hist_Master_JetPt_Flavour->GetXaxis()->SetTitle(" Jet Pt (GeV/c)");
  hist_Master_JetPt_Flavour->GetYaxis()->SetTitle("Jet Flavour");
  
  
  TH3D *hist_Master_JetPt_MuPt_Flavour = new TH3D("hist_Master_JetPt_MuPt_Flavour","hist_Master_JetPt_MuPt_Flavour",NBinsJetPt,JetPtMin,JetPtMax,NBinsMuPt,MuPtMin,MuPtMax, NFlavour,FlavourMin,FlavourMax);
  hist_Master_JetPt_MuPt_Flavour->GetXaxis()->SetTitle(" Jet p_{T} (GeV/c)");
  hist_Master_JetPt_MuPt_Flavour->GetYaxis()->SetTitle(" #mu p_{T} (GeV/c)");
  hist_Master_JetPt_MuPt_Flavour->GetZaxis()->SetTitle("Jet Flavour");
  
  TH3D *hist_Master_JetPt_MuPtRel_Flavour = new TH3D("hist_Master_JetPt_MuPtRel_Flavour","hist_Master_JetPt_MuPtRel_Flavour", NBinsJetPt,JetPtMin,JetPtMax,NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax, NFlavour,FlavourMin,FlavourMax);
  hist_Master_JetPt_MuPtRel_Flavour->GetXaxis()->SetTitle(" Jet p_{T} (GeV/c)");
  hist_Master_JetPt_MuPtRel_Flavour->GetYaxis()->SetTitle(" #mu p_{T}-Rel (GeV/c)");
  hist_Master_JetPt_MuPtRel_Flavour->GetZaxis()->SetTitle("Jet Flavour");
  
  
  TH1D *histJetPt = new TH1D("histJetPt","histJetPt",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPt->GetXaxis()->SetTitle("Jet Pt (GeV/c)");
  histJetPt->GetYaxis()->SetTitle("Entries");
  
  TH1D *histJetEta = new TH1D("histJetEta","histJetEta",100,-5,5);
  histJetEta->GetXaxis()->SetTitle("Jet #eta");
  histJetEta->GetYaxis()->SetTitle("Entries");
  
  TH1D *histJetPhi = new TH1D("histJetPhi","histJetPhi",100,-Pi,Pi);
  histJetPhi->GetXaxis()->SetTitle("Jet #phi");
  histJetPhi->GetYaxis()->SetTitle("Entries");

  
  TH1D *histJetPtUnknown = new TH1D("histJetPtUnknown","histJetPtUnknown",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtUnknown->GetXaxis()->SetTitle("Jet Pt (GeV/c) (Unknown)");
  histJetPtUnknown->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histJetPtLight = new TH1D("histJetPtLight","histJetPtLight",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtLight->GetXaxis()->SetTitle("Jet Pt (GeV/c) (u,d,s)");
  histJetPtLight->GetYaxis()->SetTitle("Entries");


  TH1D *histJetPtUp = new TH1D("histJetPtUp","histJetPtUp",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtUp->GetXaxis()->SetTitle("Jet Pt (GeV/c) (u)");
  histJetPtUp->GetYaxis()->SetTitle("Entries");


  TH1D *histJetPtDown = new TH1D("histJetPtDown","histJetPtDown",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtDown->GetXaxis()->SetTitle("Jet Pt (GeV/c) (d)");
  histJetPtDown->GetYaxis()->SetTitle("Entries");


  TH1D *histJetPtStrange = new TH1D("histJetPtStrange","histJetPtStrange",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtStrange->GetXaxis()->SetTitle("Jet Pt (GeV/c) (s)");
  histJetPtStrange->GetYaxis()->SetTitle("Entries");

  TH1D *histJetPtCharm = new TH1D("histJetPtCharm","histJetPtCharm",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtCharm->GetXaxis()->SetTitle("Jet Pt (GeV/c) (c)");
  histJetPtCharm->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histJetPtBeauty = new TH1D("histJetPtBeauty","histJetPtBeauty",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtBeauty->GetXaxis()->SetTitle("Jet Pt (GeV/c) (b)");
  histJetPtBeauty->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histJetPtGluon = new TH1D("histJetPtGluon","histJetPtGluon",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPtGluon->GetXaxis()->SetTitle("Jet Pt (GeV/c) (g)");
  histJetPtGluon->GetYaxis()->SetTitle("Entries");

  /**********************************************************************************************************************/
  /**********************************************************************************************************************/
  // CSV v2 performance for the Jets in MC
  //
  //
  //
  //
  //
  /**********************************************************************************************************************/
  /**********************************************************************************************************************/
  

  const Int_t NBinsJetCSV =100;
  const Double_t JetCSVMin =0.0;
  const Double_t JetCSVMax =1.2;


  TH1D *histJetCSV = new TH1D("histJetCSV","histJetCSV",NBinsJetCSV,JetCSVMin,JetCSVMax);
  histJetCSV->GetXaxis()->SetTitle("Jet CSV v2");
  histJetCSV->GetXaxis()->SetTitle("Entries");
  
  

  
  TH3D *hist_Master_JetCSV_JetPt_Flavour = new TH3D("hist_Master_JetCSV_JetPt_Flavour","hist_Master_JetCSV_JetPt_Flavour", NBinsJetCSV, JetCSVMin, JetCSVMax, NBinsJetPt, JetPtMin, JetPtMax, NFlavour,FlavourMin,FlavourMax);
  hist_Master_JetCSV_JetPt_Flavour->GetXaxis()->SetTitle("Jet CSV v2");
  hist_Master_JetCSV_JetPt_Flavour->GetYaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->SetTitle("Jet Flavour");

  
  TH1D *histMuonJetCSV = new TH1D("histMuonJetCSV","histMuonJetCSV",NBinsJetCSV,JetCSVMin,JetCSVMax);
  histMuonJetCSV->GetXaxis()->SetTitle("Muon Jet CSV v2");
  histMuonJetCSV->GetXaxis()->SetTitle("Entries");

  
  TH3D *hist_Master_MuonJetCSV_MuonJetPt_Flavour = new TH3D("hist_Master_MuonJetCSV_MuonJetPt_Flavour","hist_Master_MuonJetCSV_MuonJetPt_Flavour", NBinsJetCSV, JetCSVMin, JetCSVMax, NBinsJetPt, JetPtMin, JetPtMax, NFlavour,FlavourMin,FlavourMax);
  hist_Master_MuonJetCSV_MuonJetPt_Flavour->GetXaxis()->SetTitle("MuonJet CSV v2");
  hist_Master_MuonJetCSV_MuonJetPt_Flavour->GetYaxis()->SetTitle("MuonJet p_{T} (GeV/c)");
  hist_Master_MuonJetCSV_MuonJetPt_Flavour->GetZaxis()->SetTitle("MuonJet Flavour");




  TH3D *hist_Master_JetCSV_MuPtRel_Flavour = new TH3D("hist_Master_JetCSV_MuPtRel_Flavour","hist_Master_JetCSV_MuPtRel_Flavour", NBinsJetCSV, JetCSVMin, JetCSVMax, NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax, NFlavour,FlavourMin,FlavourMax);
  
  hist_Master_JetCSV_MuPtRel_Flavour->SetTitle("Jet CSV v2");
  hist_Master_JetCSV_MuPtRel_Flavour->GetYaxis()->SetTitle("#mu p_{T}-Rel (GeV/c)");
  hist_Master_JetCSV_MuPtRel_Flavour->GetZaxis()->SetTitle("Jet Flavour");
  
  /*
  const Int_t NBinsJetCSV =100;
  const Double_t JetCSVMin =0.0;
  const Double_t JetCSVMax =1.2;

  const Int_t NBinsMuonPtRel = 40;
  const Double_t MuonPtRelMin = 0.0;
  const Double_t MuonPtRelMax = 4.0;


  Int_t NFlavour = 9;
  Double_t FlavourMin = 0.5;
  Double_t FlavourMax = 9.5;


  Int_t NBinsMuPt = 100;
  Double_t MuPtMin = 0.0;
  Double_t MuPtMax = 100.0;
  */
  //Adding a four dimensonal histogram
  //1.CSV
  //2.pT^Rel
  //3.Flavour
  //4.MuonPt 
  const Int_t NDimension = 4;
  const Int_t NBins[NDimension]={100,40,9,100};  
  const Double_t xmin[NDimension]={0.0,0.0,0.5,0.0};
  const Double_t xmax[NDimension]={1.2,4.0,9.5,100.0};

  THnSparseD *hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt = new THnSparseD("hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt","hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",NDimension, NBins, xmin, xmax);
  //hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->Sumw2();
  hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->GetAxis(0)->SetTitle("Jet CSV v2");
  hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->GetAxis(1)->SetTitle("#mu p_{T}-Rel (GeV/c)");
  hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->GetAxis(2)->SetTitle("Jet Flavour");
  hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->GetAxis(3)->SetTitle("#mu p_{T} (GeV/c)");
  //to fill the 4D histogram
  Double_t Fill_hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt[NDimension];



  TH1D *histMuonPtRel = new TH1D("histMuonPtRel","histMuonPtRel",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  histMuonPtRel->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  histMuonPtRel->GetYaxis()->SetTitle("Entries");

  TH1D *histMuonPtRelCSVTag = new TH1D("histMuonPtRelCSVTag","histMuonPtRelCSVTag",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  histMuonPtRelCSVTag->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  histMuonPtRelCSVTag->GetYaxis()->SetTitle("Entries");


  TH1D *histMuonPtRelCSVVeto = new TH1D("histMuonPtRelCSVVeto","histMuonPtRelCSVVeto",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  histMuonPtRelCSVVeto->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  histMuonPtRelCSVVeto->GetYaxis()->SetTitle("Entries");
  

  //===========================================================================//
  //========================== reco muon histos ===============================//


  //All the muons matched to Jet
  TH3D *hist_Master_MuEta_MuPt_MuPhi = new TH3D("hist_Master_MuEta_MuPt_MuPhi","hist_Master_MuEta_MuPt_MuPhi",NBinsMuEta,MuEtaMin,MuEtaMax,NBinsMuPt,MuPtMin,MuPtMax,NBinsMuPhi,MuPhiMin,MuPhiMax);
  hist_Master_MuEta_MuPt_MuPhi->Sumw2();
  hist_Master_MuEta_MuPt_MuPhi->GetXaxis()->SetTitle("Muon #eta");
  hist_Master_MuEta_MuPt_MuPhi->GetYaxis()->SetTitle("Muon p_{T} (GeV/c)");
  hist_Master_MuEta_MuPt_MuPhi->GetZaxis()->SetTitle("Muon #phi");


  //All the reco muons (pass the quality cuts or quality cuts + MC matching if applied) 
  TH1D *histMuonPt = new TH1D("histMuonPt","histMuonPt",NBinsMuPt,MuPtMin,MuPtMax);
  histMuonPt->Sumw2();
  histMuonPt->GetXaxis()->SetTitle("Muon Pt (GeV/c)");
  histMuonPt->GetYaxis()->SetTitle("Entries");
  
  TH1D *histMuonEta = new TH1D("histMuonEta","histMuonEta",NBinsMuEta,MuEtaMin,MuEtaMax);
  histMuonEta->Sumw2();
  histMuonEta->GetXaxis()->SetTitle("Muon #eta");
  histMuonEta->GetYaxis()->SetTitle("Entries");


  TH1D *histMuonPhi = new TH1D("histMuonPhi","histMuonPhi",NBinsMuPhi,MuPhiMin,MuPhiMax);
  histMuonPhi->Sumw2();
  histMuonPhi->GetXaxis()->SetTitle("Muon #phi");
  histMuonPhi->GetYaxis()->SetTitle("Entries");

  //Gen Muon matched reco muons (reco muon variables are filled)
  TH1D *histMatchedMuonPt = new TH1D("histMatchedMuonPt","histMatchedMuonPt",NBinsMuPt,MuPtMin,MuPtMax);
  histMatchedMuonPt->Sumw2();
  histMatchedMuonPt->GetXaxis()->SetTitle("MatchedMuon Pt (GeV/c)");
  histMatchedMuonPt->GetYaxis()->SetTitle("Entries");
  
  TH1D *histMatchedMuonEta = new TH1D("histMatchedMuonEta","histMatchedMuonEta",NBinsMuEta,MuEtaMin,MuEtaMax);
  histMatchedMuonEta->Sumw2();
  histMatchedMuonEta->GetXaxis()->SetTitle("MatchedMuon #eta");
  histMatchedMuonEta->GetYaxis()->SetTitle("Entries");


  TH1D *histMatchedMuonPhi = new TH1D("histMatchedMuonPhi","histMatchedMuonPhi",NBinsMuPhi,MuPhiMin,MuPhiMax);
  histMatchedMuonPhi->Sumw2();
  histMatchedMuonPhi->GetXaxis()->SetTitle("MatchedMuon #phi");
  histMatchedMuonPhi->GetYaxis()->SetTitle("Entries");



  //reco matched gen muons (gen muon variables are filled)
  TH1D *histRecoMatchedGenMuonPt = new TH1D("histRecoMatchedGenMuonPt","histRecoMatchedGenMuonPt",NBinsMuPt,MuPtMin,MuPtMax);
  histRecoMatchedGenMuonPt->Sumw2();
  histRecoMatchedGenMuonPt->GetXaxis()->SetTitle("RecoMatchedGenMuon Pt (GeV/c)");
  histRecoMatchedGenMuonPt->GetYaxis()->SetTitle("Entries");
  
  TH1D *histRecoMatchedGenMuonEta = new TH1D("histRecoMatchedGenMuonEta","histRecoMatchedGenMuonEta",NBinsMuEta,MuEtaMin,MuEtaMax);
  histRecoMatchedGenMuonEta->Sumw2();
  histRecoMatchedGenMuonEta->GetXaxis()->SetTitle("RecoMatchedGenMuon #eta");
  histRecoMatchedGenMuonEta->GetYaxis()->SetTitle("Entries");


  TH1D *histRecoMatchedGenMuonPhi = new TH1D("histRecoMatchedGenMuonPhi","histRecoMatchedGenMuonPhi",NBinsMuPhi,MuPhiMin,MuPhiMax);
  histRecoMatchedGenMuonPhi->Sumw2();
  histRecoMatchedGenMuonPhi->GetXaxis()->SetTitle("RecoMatchedGenMuon #phi");
  histRecoMatchedGenMuonPhi->GetYaxis()->SetTitle("Entries");

  
  TH2D *histGenMuRecMuDRVsDPt = new TH2D("histGenMuRecMuDRVsDPt","histGenMuRecMuDRVsDPt",100,0.0,10.0,100,0.0,10.0);
  histGenMuRecMuDRVsDPt->GetXaxis()->SetTitle("Muon-Gen Muon #Delta R");
  histGenMuRecMuDRVsDPt->GetYaxis()->SetTitle("Muon-Gen Muon #Delta Pt");
  

  TH2D *histGenMuRecMuDRVsPt = new TH2D("histGenMuRecMuDRVsPt","histGenMuRecMuDRVsPt",100,0,10,NBinsMuPt,MuPtMin,MuPtMax);
  histGenMuRecMuDRVsPt->GetXaxis()->SetTitle("Muon-Gen Muon #Delta R");
  histGenMuRecMuDRVsPt->GetYaxis()->SetTitle("Muon p_{T} (GeV/c)");
  

  TH2D *histGenMuRecMuDRVsEta = new TH2D("histGenMuRecMuDRVsEta","histGenMuRecMuDRVsEta",100,0,10,NBinsMuEta,MuEtaMin,MuEtaMax);
  histGenMuRecMuDRVsEta->GetXaxis()->SetTitle("Muon-Gen Muon #Delta R");
  histGenMuRecMuDRVsEta->GetYaxis()->SetTitle("Muon #eta");
  

  TH2D *histGenMuRecMuDRVsPhi = new TH2D("histGenMuRecMuDRVsPhi","histGenMuRecMuDRVsPhi",100,0,10,NBinsMuPhi,MuPhiMin,MuPhiMax);
  histGenMuRecMuDRVsPhi->GetXaxis()->SetTitle("Muon-Gen Muon #Delta R");
  histGenMuRecMuDRVsPhi->GetYaxis()->SetTitle("Muon #phi (GeV/c)");
  
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
  TH1D *histMuonIsGlobal = new TH1D("histMuonIsGlobal","histMuonIsGlobal",NBinsMuonIsGlobal,MuonIsGlobalMin,MuonIsGlobalMax);
  histMuonIsGlobal->GetXaxis()->SetTitle("Muon IsGlobal");
  histMuonIsGlobal->GetYaxis()->SetTitle("Entries"); 
  
  //NG --> No Gen Muon
  TH1D *histNGMuonIsGlobal = new TH1D("histNGMuonIsGlobal","histNGMuonIsGlobal",NBinsMuonIsGlobal,MuonIsGlobalMin,MuonIsGlobalMax);
  histNGMuonIsGlobal->GetXaxis()->SetTitle("NGMuon IsGlobal");
  histNGMuonIsGlobal->GetYaxis()->SetTitle("Entries");

  
  //2. IsTrackerMuon
  const Int_t NBinsMuonIsTracker    = 5;
  Double_t MuonIsTrackerMin = -0.5;
  Double_t MuonIsTrackerMax = 4.5;
  TH1D *histMuonIsTracker = new TH1D("histMuonIsTracker","histMuonIsTracker",NBinsMuonIsTracker,MuonIsTrackerMin,MuonIsTrackerMax);
  histMuonIsTracker->GetXaxis()->SetTitle("Muon IsTracker");
  histMuonIsTracker->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonIsTracker = new TH1D("histNGMuonIsTracker","histNGMuonIsTracker",NBinsMuonIsTracker,MuonIsTrackerMin,MuonIsTrackerMax);
  histNGMuonIsTracker->GetXaxis()->SetTitle("NGMuon IsTracker");
  histNGMuonIsTracker->GetYaxis()->SetTitle("Entries");


  //3. IsPFMuon
  const Int_t NBinsMuonIsPF    = 5;
  Double_t MuonIsPFMin = -0.5;
  Double_t MuonIsPFMax = 4.5;
  TH1D *histMuonIsPF = new TH1D("histMuonIsPF","histMuonIsPF",NBinsMuonIsPF,MuonIsPFMin,MuonIsPFMax);
  histMuonIsPF->GetXaxis()->SetTitle("Muon IsPF");
  histMuonIsPF->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonIsPF = new TH1D("histNGMuonIsPF","histNGMuonIsPF",NBinsMuonIsPF,MuonIsPFMin,MuonIsPFMax);
  histNGMuonIsPF->GetXaxis()->SetTitle("NGMuon IsPF");
  histNGMuonIsPF->GetYaxis()->SetTitle("Entries");  


  //4. IsSTAMuon
  const Int_t NBinsMuonIsSTA    = 5;
  Double_t MuonIsSTAMin = -0.5;
  Double_t MuonIsSTAMax = 4.5;
  TH1D *histMuonIsSTA = new TH1D("histMuonIsSTA","histMuonIsSTA",NBinsMuonIsSTA,MuonIsSTAMin,MuonIsSTAMax);
  histMuonIsSTA->GetXaxis()->SetTitle("Muon IsSTA");
  histMuonIsSTA->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonIsSTA = new TH1D("histNGMuonIsSTA","histNGMuonIsSTA",NBinsMuonIsSTA,MuonIsSTAMin,MuonIsSTAMax);
  histNGMuonIsSTA->GetXaxis()->SetTitle("NGMuon IsSTA");
  histNGMuonIsSTA->GetYaxis()->SetTitle("Entries");


  //5.mu_D0
  const Int_t NBinsMuonD0    = 100;
  Double_t MuonD0Min = -0.5;
  Double_t MuonD0Max =  0.5;
  TH1D *histMuonD0 = new TH1D("histMuonD0","histMuonD0",NBinsMuonD0,MuonD0Min,MuonD0Max);
  histMuonD0->GetXaxis()->SetTitle("Muon D0");
  histMuonD0->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonD0 = new TH1D("histNGMuonD0","histNGMuonD0",NBinsMuonD0,MuonD0Min,MuonD0Max);
  histNGMuonD0->GetXaxis()->SetTitle("NGMuon D0");
  histNGMuonD0->GetYaxis()->SetTitle("Entries");


  //6.mu_Dz
  const Int_t NBinsMuonDz    = 100;
  Double_t MuonDzMin = -1.0;
  Double_t MuonDzMax = 1.0;
  TH1D *histMuonDz = new TH1D("histMuonDz","histMuonDz",NBinsMuonDz,MuonDzMin,MuonDzMax);
  histMuonDz->GetXaxis()->SetTitle("Muon Dz");
  histMuonDz->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonDz = new TH1D("histNGMuonDz","histNGMuonDz",NBinsMuonDz,MuonDzMin,MuonDzMax);
  histNGMuonDz->GetXaxis()->SetTitle("NGMuon Dz");
  histNGMuonDz->GetYaxis()->SetTitle("Entries");
  
  //7.mu_chi2ndf
  const Int_t NBinsMuonChi2NDF    = 100;
  Double_t MuonChi2NDFMin = 0.0;
  Double_t MuonChi2NDFMax = 20.0;
  TH1D *histMuonChi2NDF = new TH1D("histMuonChi2NDF","histMuonChi2NDF",NBinsMuonChi2NDF,MuonChi2NDFMin,MuonChi2NDFMax);
  histMuonChi2NDF->GetXaxis()->SetTitle("Muon Chi2NDF");
  histMuonChi2NDF->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonChi2NDF = new TH1D("histNGMuonChi2NDF","histNGMuonChi2NDF",NBinsMuonChi2NDF,MuonChi2NDFMin,MuonChi2NDFMax);
  histNGMuonChi2NDF->GetXaxis()->SetTitle("NGMuon Chi2NDF");
  histNGMuonChi2NDF->GetYaxis()->SetTitle("Entries");

  
  //8.mu_innerD0
  const Int_t NBinsMuonInnerD0    = 100;
  Double_t MuonInnerD0Min = -0.5;
  Double_t MuonInnerD0Max =  0.5;
  TH1D *histMuonInnerD0 = new TH1D("histMuonInnerD0","histMuonInnerD0",NBinsMuonInnerD0,MuonInnerD0Min,MuonInnerD0Max);
  histMuonInnerD0->GetXaxis()->SetTitle("Muon InnerD0");
  histMuonInnerD0->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonInnerD0 = new TH1D("histNGMuonInnerD0","histNGMuonInnerD0",NBinsMuonInnerD0,MuonInnerD0Min,MuonInnerD0Max);
  histNGMuonInnerD0->GetXaxis()->SetTitle("NGMuon InnerD0");
  histNGMuonInnerD0->GetYaxis()->SetTitle("Entries");
  
  
  //9.mu_innerD0Err
  const Int_t NBinsMuonInnerD0Err    = 100;
  Double_t MuonInnerD0ErrMin = 0.0;
  Double_t MuonInnerD0ErrMax =  1.0;
  TH1D *histMuonInnerD0Err = new TH1D("histMuonInnerD0Err","histMuonInnerD0Err",NBinsMuonInnerD0Err,MuonInnerD0ErrMin,MuonInnerD0ErrMax);
  histMuonInnerD0Err->GetXaxis()->SetTitle("Muon InnerD0Err");
  histMuonInnerD0Err->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonInnerD0Err = new TH1D("histNGMuonInnerD0Err","histNGMuonInnerD0Err",NBinsMuonInnerD0Err,MuonInnerD0ErrMin,MuonInnerD0ErrMax);
  histNGMuonInnerD0Err->GetXaxis()->SetTitle("NGMuon InnerD0Err");
  histNGMuonInnerD0Err->GetYaxis()->SetTitle("Entries");


  //10.mu_innerDz
  const Int_t NBinsMuonInnerDz    = 100;
  Double_t MuonInnerDzMin = -1.0;
  Double_t MuonInnerDzMax =  1.0;
  TH1D *histMuonInnerDz = new TH1D("histMuonInnerDz","histMuonInnerDz",NBinsMuonInnerDz,MuonInnerDzMin,MuonInnerDzMax);
  histMuonInnerDz->GetXaxis()->SetTitle("Muon InnerDz");
  histMuonInnerDz->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonInnerDz = new TH1D("histNGMuonInnerDz","histNGMuonInnerDz",NBinsMuonInnerDz,MuonInnerDzMin,MuonInnerDzMax);
  histNGMuonInnerDz->GetXaxis()->SetTitle("NGMuon InnerDz");
  histNGMuonInnerDz->GetYaxis()->SetTitle("Entries");
  
  //11.mu_innerDzErr
  const Int_t NBinsMuonInnerDzErr    = 100;
  Double_t MuonInnerDzErrMin = 0.0;
  Double_t MuonInnerDzErrMax =  10.0;
  TH1D *histMuonInnerDzErr = new TH1D("histMuonInnerDzErr","histMuonInnerDzErr",NBinsMuonInnerDzErr,MuonInnerDzErrMin,MuonInnerDzErrMax);
  histMuonInnerDzErr->GetXaxis()->SetTitle("Muon InnerDzErr");
  histMuonInnerDzErr->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonInnerDzErr = new TH1D("histNGMuonInnerDzErr","histNGMuonInnerDzErr",NBinsMuonInnerDzErr,MuonInnerDzErrMin,MuonInnerDzErrMax);
  histNGMuonInnerDzErr->GetXaxis()->SetTitle("NGMuon InnerDzErr");
  histNGMuonInnerDzErr->GetYaxis()->SetTitle("Entries");

  
  //12.mu_innerD0/mu_innerD0Err
  const Int_t NBinsMuonInnerD0Norm    = 100;
  Double_t MuonInnerD0NormMin = -5.0;
  Double_t MuonInnerD0NormMax =  5.0;
  TH1D *histMuonInnerD0Norm = new TH1D("histMuonInnerD0Norm","histMuonInnerD0Norm",NBinsMuonInnerD0Norm,MuonInnerD0NormMin,MuonInnerD0NormMax);
  histMuonInnerD0Norm->GetXaxis()->SetTitle("Muon InnerD0Norm");
  histMuonInnerD0Norm->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonInnerD0Norm = new TH1D("histNGMuonInnerD0Norm","histNGMuonInnerD0Norm",NBinsMuonInnerD0Norm,MuonInnerD0NormMin,MuonInnerD0NormMax);
  histNGMuonInnerD0Norm->GetXaxis()->SetTitle("NGMuon InnerD0Norm");
  histNGMuonInnerD0Norm->GetYaxis()->SetTitle("Entries");

  
  //13.mu_innerDz/mu_innerDzErr
  const Int_t NBinsMuonInnerDzNorm    = 100;
  Double_t MuonInnerDzNormMin = -5.0;
  Double_t MuonInnerDzNormMax =  5.0;
  TH1D *histMuonInnerDzNorm = new TH1D("histMuonInnerDzNorm","histMuonInnerDzNorm",NBinsMuonInnerDzNorm,MuonInnerDzNormMin,MuonInnerDzNormMax);
  histMuonInnerDzNorm->GetXaxis()->SetTitle("Muon InnerDzNorm");
  histMuonInnerDzNorm->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonInnerDzNorm = new TH1D("histNGMuonInnerDzNorm","histNGMuonInnerDzNorm",NBinsMuonInnerDzNorm,MuonInnerDzNormMin,MuonInnerDzNormMax);
  histNGMuonInnerDzNorm->GetXaxis()->SetTitle("NGMuon InnerDzNorm");
  histNGMuonInnerDzNorm->GetYaxis()->SetTitle("Entries");

  //14. mu_trkLayers
  const Int_t NBinsMuonTrkLayers    = 20;
  Double_t MuonTrkLayersMin = -0.5;
  Double_t MuonTrkLayersMax = 19.5;
  TH1D *histMuonTrkLayers = new TH1D("histMuonTrkLayers","histMuonTrkLayers",NBinsMuonTrkLayers,MuonTrkLayersMin,MuonTrkLayersMax);
  histMuonTrkLayers->GetXaxis()->SetTitle("Muon TrkLayers");
  histMuonTrkLayers->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonTrkLayers = new TH1D("histNGMuonTrkLayers","histNGMuonTrkLayers",NBinsMuonTrkLayers,MuonTrkLayersMin,MuonTrkLayersMax);
  histNGMuonTrkLayers->GetXaxis()->SetTitle("NGMuon TrkLayers");
  histNGMuonTrkLayers->GetYaxis()->SetTitle("Entries");


  //15.mu_pixelLayers
  const Int_t NBinsMuonPixelLayers    = 10;
  Double_t MuonPixelLayersMin = -0.5;
  Double_t MuonPixelLayersMax = 9.5;
  TH1D *histMuonPixelLayers = new TH1D("histMuonPixelLayers","histMuonPixelLayers",NBinsMuonPixelLayers,MuonPixelLayersMin,MuonPixelLayersMax);
  histMuonPixelLayers->GetXaxis()->SetTitle("Muon PixelLayers");
  histMuonPixelLayers->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonPixelLayers = new TH1D("histNGMuonPixelLayers","histNGMuonPixelLayers",NBinsMuonPixelLayers,MuonPixelLayersMin,MuonPixelLayersMax);
  histNGMuonPixelLayers->GetXaxis()->SetTitle("NGMuon PixelLayers");
  histNGMuonPixelLayers->GetYaxis()->SetTitle("Entries");

  //16.mu_pixelHits
  const Int_t NBinsMuonPixelHits    = 15;
  Double_t MuonPixelHitsMin = -0.5;
  Double_t MuonPixelHitsMax = 14.5;
  TH1D *histMuonPixelHits = new TH1D("histMuonPixelHits","histMuonPixelHits",NBinsMuonPixelHits,MuonPixelHitsMin,MuonPixelHitsMax);
  histMuonPixelHits->GetXaxis()->SetTitle("Muon PixelHits");
  histMuonPixelHits->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonPixelHits = new TH1D("histNGMuonPixelHits","histNGMuonPixelHits",NBinsMuonPixelHits,MuonPixelHitsMin,MuonPixelHitsMax);
  histNGMuonPixelHits->GetXaxis()->SetTitle("NGMuon PixelHits");
  histNGMuonPixelHits->GetYaxis()->SetTitle("Entries");

  //17.mu_muonHits
  const Int_t NBinsMuonMuHits    = 50;
  Double_t MuonMuHitsMin = -0.5;
  Double_t MuonMuHitsMax = 49.5;
  TH1D *histMuonMuHits = new TH1D("histMuonMuHits","histMuonMuHits",NBinsMuonMuHits,MuonMuHitsMin,MuonMuHitsMax);
  histMuonMuHits->GetXaxis()->SetTitle("Muon MuHits");
  histMuonMuHits->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonMuHits = new TH1D("histNGMuonMuHits","histNGMuonMuHits",NBinsMuonMuHits,MuonMuHitsMin,MuonMuHitsMax);
  histNGMuonMuHits->GetXaxis()->SetTitle("NGMuon MuHits");
  histNGMuonMuHits->GetYaxis()->SetTitle("Entries");

  //18.mu_trkQuality
  const Int_t NBinsMuonTrkQuality = 5;
  Double_t MuonTrkQualityMin = -0.5;
  Double_t MuonTrkQualityMax = 4.5;
  TH1D *histMuonTrkQuality = new TH1D("histMuonTrkQuality","histMuonTrkQuality",NBinsMuonTrkQuality,MuonTrkQualityMin,MuonTrkQualityMax);
  histMuonTrkQuality->GetXaxis()->SetTitle("Muon TrkQuality");
  histMuonTrkQuality->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonTrkQuality = new TH1D("histNGMuonTrkQuality","histNGMuonTrkQuality",NBinsMuonTrkQuality,MuonTrkQualityMin,MuonTrkQualityMax);
  histNGMuonTrkQuality->GetXaxis()->SetTitle("NGMuon TrkQuality");
  histNGMuonTrkQuality->GetYaxis()->SetTitle("Entries");


  //19.mu_stations
  const Int_t NBinsMuonMuStations    = 10;
  Double_t MuonMuStationsMin = -0.5;
  Double_t MuonMuStationsMax = 9.5;
  TH1D *histMuonMuStations = new TH1D("histMuonMuStations","histMuonMuStations",NBinsMuonMuStations,MuonMuStationsMin,MuonMuStationsMax);
  histMuonMuStations->GetXaxis()->SetTitle("Muon MuStations");
  histMuonMuStations->GetYaxis()->SetTitle("Entries");
  //NG --> No Gen Muon
  TH1D *histNGMuonMuStations = new TH1D("histNGMuonMuStations","histNGMuonMuStations",NBinsMuonMuStations,MuonMuStationsMin,MuonMuStationsMax);
  histNGMuonMuStations->GetXaxis()->SetTitle("NGMuon MuStations");
  histNGMuonMuStations->GetYaxis()->SetTitle("Entries");
  //=======================================================================================================================================//
  //================================= Muon Quality Cut Histograms Ends ===================================================================//
  //=======================================================================================================================================//


  TH1D *histDiMuonInvMass = new TH1D("histDiMuonInvMass","histDiMuonInvMass",100,0,100);
  histDiMuonInvMass->GetXaxis()->SetTitle("DiMuon InvMass (GeV/c)");
  histDiMuonInvMass->GetYaxis()->SetTitle("Entries");


  TH1D *histDiMuonInvMassLow = new TH1D("histDiMuonInvMassLow","histDiMuonInvMassLow",200,2.0,4.5);
  histDiMuonInvMassLow->GetXaxis()->SetTitle("DiMuon InvMassLow (GeV/c)");
  histDiMuonInvMassLow->GetYaxis()->SetTitle("Entries");


  TH1D *histDiMuonInvMassInt = new TH1D("histDiMuonInvMassInt","histDiMuonInvMassInt",200,8.0,14.0);
  histDiMuonInvMassInt->GetXaxis()->SetTitle("DiMuon InvMassInt (GeV/c)");
  histDiMuonInvMassInt->GetYaxis()->SetTitle("Entries");
  

  TH1D *histDiMuonPt = new TH1D("histDiMuonPt","histDiMuonPt",100,0,100);
  //histDiMuonPt->Sumw2();
  histDiMuonPt->GetXaxis()->SetTitle("DiMuon Pt (GeV/c)");
  histDiMuonPt->GetYaxis()->SetTitle("Entries");

  TH1D *histDiMuonRapidity = new TH1D("histDiMuonRapidity","histDiMuonRapidity",100,-5,5);
  histDiMuonRapidity->GetXaxis()->SetTitle("DiMuon #eta (GeV/c)");
  histDiMuonRapidity->GetYaxis()->SetTitle("Entries");


  TH1D *histDiMuonPhi = new TH1D("histDiMuonPhi","histDiMuonPhi",100,-Pi,Pi);
  histDiMuonPhi->GetXaxis()->SetTitle("DiMuon #phi (GeV/c)");
  histDiMuonPhi->GetYaxis()->SetTitle("Entries");

  

  TH1D *histMuonJetDR = new TH1D("histMuonJetDR","histMuonJetDR",100,0,10);
  histMuonJetDR->GetXaxis()->SetTitle("Muon-Jet #Delta R");
  histMuonJetDR->GetYaxis()->SetTitle("Entries");


  TH1D *histMuonJetDPhi = new TH1D("histMuonJetDPhi","histMuonJetDPhi",nDeltaPhiBinsJetMuon,minDeltaPhiJetMuon,maxDeltaPhiJetMuon);
  histMuonJetDPhi->GetXaxis()->SetTitle("Muon-Jet #Delta #Phi");
  histMuonJetDPhi->GetYaxis()->SetTitle("Entries");


  TH1D *histMuonJetPtTotal = new TH1D("histMuonJetPtTotal","histMuonJetPtTotal",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtTotal->GetXaxis()->SetTitle("MuonJet Pt (GeV/c) (u,d,s)");
  histMuonJetPtTotal->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histMuonJetPtLight = new TH1D("histMuonJetPtLight","histMuonJetPtLight",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtLight->GetXaxis()->SetTitle("MuonJet Pt (GeV/c) (u,d,s)");
  histMuonJetPtLight->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histMuonJetPtUp = new TH1D("histMuonJetPtUp","histMuonJetPtUp",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtUp->GetXaxis()->SetTitle("Jet Pt (GeV/c) (u)");
  histMuonJetPtUp->GetYaxis()->SetTitle("Entries");


  TH1D *histMuonJetPtDown = new TH1D("histMuonJetPtDown","histMuonJetPtDown",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtDown->GetXaxis()->SetTitle("Jet Pt (GeV/c) (d)");
  histMuonJetPtDown->GetYaxis()->SetTitle("Entries");


  TH1D *histMuonJetPtStrange = new TH1D("histMuonJetPtStrange","histMuonJetPtStrange",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtStrange->GetXaxis()->SetTitle("Jet Pt (GeV/c) (s)");
  histMuonJetPtStrange->GetYaxis()->SetTitle("Entries");

  TH1D *histMuonJetPtCharm = new TH1D("histMuonJetPtCharm","histMuonJetPtCharm",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtCharm->GetXaxis()->SetTitle("MuonJet Pt (GeV/c) (c)");
  histMuonJetPtCharm->GetYaxis()->SetTitle("Entries");


  TH1D *histMuonJetPtBeauty = new TH1D("histMuonJetPtBeauty","histMuonJetPtBeauty",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtBeauty->GetXaxis()->SetTitle("MuonJet Pt (GeV/c) (b)");
  histMuonJetPtBeauty->GetYaxis()->SetTitle("Entries");

  TH1D *histMuonJetPtGluon = new TH1D("histMuonJetPtGluon","histMuonJetPtGluon",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPtGluon->GetXaxis()->SetTitle("MuonJet Pt (GeV/c) (g)");
  histMuonJetPtGluon->GetYaxis()->SetTitle("Entries");

  const Int_t NBinsMatchedMuonsDR04Size = 12;
  Double_t MatchedMuonsDR04SizeMin = 0.5;
  Double_t MatchedMuonsDR04SizeMax = 12.5;
  
  TH1D *histMatchedMuonsDR04Size = new TH1D("histMatchedMuonsDR04Size","histMatchedMuonsDR04Size", NBinsMatchedMuonsDR04Size,MatchedMuonsDR04SizeMin,MatchedMuonsDR04SizeMax);
  histMatchedMuonsDR04Size->GetXaxis()->SetTitle("MatchedMuonsDR04 Pt (GeV/c)");
  histMatchedMuonsDR04Size->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histMatchedMuonsDR04Pt = new TH1D("histMatchedMuonsDR04Pt","histMatchedMuonsDR04Pt",NBinsMuPt,MuPtMin,MuPtMax);
  histMatchedMuonsDR04Pt->GetXaxis()->SetTitle("MatchedMuonsDR04 Pt (GeV/c)");
  histMatchedMuonsDR04Pt->GetYaxis()->SetTitle("Entries");
  
  TH1D *histMatchedMuonsDR04Eta = new TH1D("histMatchedMuonsDR04Eta","histMatchedMuonsDR04Eta",NBinsMuEta,MuEtaMin,MuEtaMax);
  histMatchedMuonsDR04Eta->GetXaxis()->SetTitle("MatchedMuonsDR04 #eta (GeV/c)");
  histMatchedMuonsDR04Eta->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histMatchedMuonsDR04Phi = new TH1D("histMatchedMuonsDR04Phi","histMatchedMuonsDR04Phi",NBinsMuPhi,MuPhiMin,MuPhiMax);
  histMatchedMuonsDR04Phi->GetXaxis()->SetTitle("MatchedMuonsDR04 #phi (GeV/c)");
  histMatchedMuonsDR04Phi->GetYaxis()->SetTitle("Entries");

  const Int_t Want_RefPartonFlavorForB = 1;
  
  const Int_t NBINS = 12;
  Double_t edges[NBINS + 1] = {0.0, 30.0, 50.0, 80.0, 100.0, 120.0, 170.0, 220.0, 280.0, 370.0, 460.0, 540.0, 3000.0};
  // Bin 1 corresponds to range [0.0, 30.0]
  // Bin 2 corresponds to range [30.0, 50] etc...
  // Bin 11 corresponds to range [460.0, 540] etc...
  // Bin 12 corresponds to range [540.0, 3000] etc...
  
  TH1* histPtHatBins = new TH1D("EventsPtHatBins","EventsPtHatBins", NBINS,edges);
  histPtHatBins->Sumw2();
  TH1* histWPtHatBins = new TH1D("WEventsPtHatBins","WEventsPtHatBins", 100,0.0,600);
  histWPtHatBins->Sumw2();
  

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  //nentries=10;
  
  cout<< nentries <<" entries in "<< fChain->GetName()<<endl;
  //Double_t Temp_Entries = 1595520;
  Long64_t nbytes = 0, nb = 0;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    fChain->GetEntry(jentry); 


    // if (Cut(ientry) < 0) continue;
    
    //Double_t PtHatWeight = getPtHatWeight(pthat);
    //for pp 2017 MC
    Double_t PtHatWeight = 1.0;
    //weight factor
    Double_t EventWeight = weight; 
    
    //for min bias MC
    //EventWeight =1;
    //PtHatWeight=1.0;
    //pt hat histogram filling
     histPtHatBins->Fill(pthat);
     histWPtHatBins->Fill(pthat,PtHatWeight);
     
     //if(pthat > 460) continue; //no crosssection above 460 on wiki     

     //puting HLT same as on data
     if(HLT_HIL3Mu5_AK4PFJet30_v1==0)continue;

     if(jentry%100000==0){
       
       //((TotalEntries - i)/TotalEntries)*100
       
       //cout<<" Event "<<jentry<<" % remaining "<<((Temp_Entries-jentry)/Temp_Entries)*100.0<<endl;
       cout<<endl;
       
       cout<< " Total number of Tracks    : "<<trkPt->size()<<endl;
       cout<< " Total number of PF Jets   : "<<pf_jtpt->size()<<endl;
       cout<< " Total number of ref parton   : "<<pf_refparton_flavor->size()<<endl;
       
       cout<< " Total number of gen Jets   : "<<genpt->size()<<endl;
       cout<< " Total number of ref pt     :   "<<pf_refpt->size()<<endl;
       
       cout<<endl;
       
       cout<< " Total number of Calo Jets : "<< calo_jtpt->size()<<endl;
       cout<< " Total number of Muons     : "<<mu_pt->size()<<endl;
       cout<< " Total number of Gen Particles     : "<<pt->size()<<endl;
       
       cout<<endl<<endl;
       
     }


     //================== Some Global Cuts =============================//
     Double_t GenJetPtMinCut = 60.0; Double_t JetPtMinCut = 60.0;
     Double_t GenJetEtaMinCut = 2.0; Double_t JetEtaMinCut = 2.0;
     Double_t GenMuonPtMin = 5.0; Double_t MuonPtMin = 5.0;

     //======================== Filling all Gen Muons ================================//
     //======================== Make vector of Gen Muons ======================//
     std::vector<TLorentzVector> GenMuons;
     std::vector<TLorentzVector> PositiveGenMuons;
     std::vector<TLorentzVector> NegativeGenMuons;
     
     //Gen Particle Loop
     for(unsigned long i=0; i<pt->size();i++){
       //if Gen Muon
       //if((abs(pdg->at(i))==13) && (status->at(i)==1)){

       if((abs(pdg->at(i))==13)){

	 Double_t GenMuonPt = pt->at(i);
	 if(GenMuonPt<GenMuonPtMin)continue;
	 
	 Double_t GenMuonEta = eta->at(i);
	 Double_t GenMuonPhi = phi->at(i); 
	 TLorentzVector GenMuon;
	 GenMuon.SetPtEtaPhiM(GenMuonPt,GenMuonEta, GenMuonPhi, MuonMass); 
	 GenMuons.push_back(GenMuon);
	 if(chg->at(i)==1)PositiveGenMuons.push_back(GenMuon);
	 if(chg->at(i)==-1)NegativeGenMuons.push_back(GenMuon);
	 
	 histGenMuonPt->Fill(GenMuonPt,EventWeight);
	 histGenMuonEta->Fill(GenMuonEta,EventWeight);
	 histGenMuonPhi->Fill(GenMuonPhi,EventWeight);
	 hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi->Fill(GenMuonEta,GenMuonPt,GenMuonPhi,EventWeight);
	 	 
       }
     }
     
     //=======================================================================//
     // ================= Gen DiMuons invariant mass ===========================// 
     //=======================================================================//
     std::vector<TLorentzVector> GenDiMuons;
     for(unsigned long j=0; j < PositiveGenMuons.size();j++)
       {
	 TLorentzVector genMuonPlus = PositiveGenMuons.at(j);
	 for(unsigned long k=0; k < NegativeGenMuons.size();k++)
	   {
	     TLorentzVector genMuonMinus = NegativeGenMuons.at(k);
	     TLorentzVector genDiMuon = genMuonPlus + genMuonMinus;
	     GenDiMuons.push_back(genDiMuon);
	     
	     histGenDiMuonInvMass->Fill(genDiMuon.M(),EventWeight);
	     histGenDiMuonInvMassLow->Fill(genDiMuon.M(),EventWeight);
	     histGenDiMuonInvMassInt->Fill(genDiMuon.M(),EventWeight);
	     histGenDiMuonPt->Fill(genDiMuon.Pt(),EventWeight);
	     histGenDiMuonRapidity->Fill(genDiMuon.Rapidity(),EventWeight);
	     histGenDiMuonPhi->Fill(genDiMuon.Phi(),EventWeight);
	   }//k=0
       }//j=0

     //============================================================================//
     //============================= filling Gen Jet Variables ====================//
     //============================================================================//


     if(jentry%100000==0){cout<<" Total number of gen Jets "<<genpt->size()<<endl;}

     histNumberOfGenJets->Fill(genpt->size());

     
     for (unsigned long i=0; i<genpt->size();i++) {
       
       
       Double_t GenJetPt;
       Double_t GenJetEta;
       Double_t GenJetPhi;

       Double_t GenPartonFlavour;
       
       GenJetPt = genpt->at(i);
       GenJetEta = geneta->at(i);
       
       if(GenJetPt<GenJetPtMinCut || TMath::Abs(GenJetEta) > GenJetEtaMinCut) continue;
       
       GenJetPhi = genphi->at(i);
       //==== Filling eta, pT, phi of gen jets
       histGenJetPt->Fill(GenJetPt,EventWeight);
       histGenJetEta->Fill(GenJetEta,EventWeight);
       histGenJetPhi->Fill(GenJetPhi,EventWeight);
       //===================================================//
       //=============== finding GenJet flavour ===========//
       //===================================================//
       
       
       //i) Each reco Jet have a ref_pt and ref_partonflavour which is basically the
       //gen jet pt and gen jet flavour
       
       //=============== pf jet loop inside the gen jet
       //=============== this is to match gen jet with the parton flavour
       //=============== reconstructed jets have ref_parton_flavour but not the generated jets
       //=============== this is strange but true
       
       int smallestDPtindex =0;
       double smallestDPt = 1000.0;
       
       for (unsigned long jj=0; jj<pf_jtpt->size();jj++) {
	 Double_t JetRefPt = 0.0;
	 JetRefPt=pf_refpt->at(jj);
	 Double_t DeltaPt = TMath::Abs(GenJetPt - JetRefPt);
	 if(DeltaPt<smallestDPt)
	   {
	     smallestDPt = DeltaPt;
	     smallestDPtindex=jj;
	   }
       }
       
       Double_t DeltaMaxRefPtGenPt = 0.0001;
       if( smallestDPt <  DeltaMaxRefPtGenPt){
	 GenPartonFlavour = pf_refparton_flavor->at(smallestDPtindex);
	 if(Want_RefPartonFlavorForB ==1){GenPartonFlavour = pf_refparton_flavorForB->at(smallestDPtindex);}

	 //GenPartonFlavour = pf_refparton_flavorForB->at(smallestDPtindex);
	 //cout<<" pf jet "<<pf_jtpt->at(smallestDPtindex) << "    "<<pf_jteta->at(smallestDPtindex)<<"  "<<pf_jtphi->at(smallestDPtindex)<<"  "<<pf_refpt->at(smallestDPtindex)<<endl;
	 //cout<<" gen jet "<<genpt->at(i) << "    "<<geneta->at(i)<<"  "<<genphi->at(i)<<"  "<<GenPartonFlavour<<endl;
       }
       else{GenPartonFlavour =-10000;}

       //===================================================//
       //=============== GenJet flavour found ==============//
       //===================================================//
       //====== Filling Flavour of different type of Gen Jets =====================//

       //===== reco jet not found
       if(GenPartonFlavour == -10000)histGenJetPtNoRec->Fill(GenJetPt,EventWeight);
       //===== flv undefined
       if(GenPartonFlavour == 0 || GenPartonFlavour == -999)histGenJetPtUnknownRec->Fill(GenJetPt,EventWeight);

       //====== light jets
       if(abs(GenPartonFlavour)==1 || abs(GenPartonFlavour)==2 ||abs(GenPartonFlavour)==3) histGenJetPtLight->Fill(GenJetPt,EventWeight);

       if(abs(GenPartonFlavour)==1)histGenJetPtUp->Fill(GenJetPt,EventWeight);
       if(abs(GenPartonFlavour)==2)histGenJetPtDown->Fill(GenJetPt,EventWeight);
       if(abs(GenPartonFlavour)==3)histGenJetPtStrange->Fill(GenJetPt,EventWeight);
       if(abs(GenPartonFlavour)==4)histGenJetPtCharm->Fill(GenJetPt,EventWeight);
       if(abs(GenPartonFlavour)==5)histGenJetPtBeauty->Fill(GenJetPt,EventWeight);
       if(abs(GenPartonFlavour)==21)histGenJetPtGluon->Fill(GenJetPt,EventWeight);

       //==== to fill in the 3D histogram, to make Gluon as 6
       Int_t PartonFlavour_Local = TMath::Abs(GenPartonFlavour);
       if(GenPartonFlavour==21)PartonFlavour_Local=6;

       if(GenPartonFlavour==-999)PartonFlavour_Local=7;
       if(GenPartonFlavour==0)PartonFlavour_Local=8;
       if(GenPartonFlavour==-10000)PartonFlavour_Local=9;
       //if(jentry%100000==0) cout<<" gen jet pt "<< GenJetPt <<"  "<<GenJetEta<<"  "<<GenJetPhi<<"  "<<PartonFlavour_Local<<endl;
       hist_GenMaster_GenJetPt_Flavour->Fill(GenJetPt,PartonFlavour_Local,EventWeight);
       //if(jentry%100000==0) cout<<" GenMuons.size() "<<GenMuons.size()<<endl;
       //===================== searching muons inside the Gen Jet =================================//
       //================ Selecting the Tightest Muon ======================//
       int smallestDRindex =0;
       double smallestDR = 1000.0;
       Double_t GenMuonGenJetDR_Max = 0.4;
       TLorentzVector MatchedGenMuon;

       if(jentry%100000==0) cout<<" GenMuos Size "<<GenMuons.size()<<endl;

       for(unsigned long j=0; j<GenMuons.size();j++)
	 {
	 
	   TLorentzVector genMuon = GenMuons.at(j);

	   Double_t GenMuonPt=genMuon.Pt();
	   Double_t GenMuonEta=genMuon.Eta();
	   Double_t GenMuonPhi=genMuon.Phi();
	   
	   
	   Double_t GenMuonGenJetDR = getDR(GenMuonEta, GenMuonPhi, GenJetEta, GenJetPhi);
	   histGenMuonGenJetDR->Fill(GenMuonGenJetDR,EventWeight);
	   
	   Double_t GenMuonGenJetDPhi = plotDPHI(GenMuonPhi,GenJetPhi);
	   histGenMuonGenJetDPhi->Fill(GenMuonGenJetDPhi,EventWeight);

	   
	   //if(jentry%100000==0) cout<<" GenMuonGenJetDR "<<GenMuonGenJetDR<<endl;
	   //if(jentry%100000==0) cout<<" gen jet + muon pt "<< GenJetPt <<"  "<<GenJetEta<<"  "<<GenJetPhi<<"  "<<PartonFlavour_Local<<endl;
	   //if(jentry%100000==0) cout<<endl<<endl;  
	   
	   if(GenMuonGenJetDR<smallestDR)
	     {
	       smallestDR = GenMuonGenJetDR;
	       smallestDRindex=j;
	     }

	 }//Gen Muon Loop
	   

       if(smallestDR < GenMuonGenJetDR_Max){

	 MatchedGenMuon = GenMuons.at(smallestDRindex);
	 	 
	 histGenMuonGenJetPtTotal->Fill(GenJetPt,EventWeight);
	 if(abs(GenPartonFlavour)==1 || abs(GenPartonFlavour)==2 ||abs(GenPartonFlavour)==3) histGenMuonGenJetPtLight->Fill(GenJetPt,EventWeight);
	 if(abs(GenPartonFlavour)==1)histGenMuonGenJetPtUp->Fill(GenJetPt,EventWeight);
	 if(abs(GenPartonFlavour)==2)histGenMuonGenJetPtDown->Fill(GenJetPt,EventWeight);
	 if(abs(GenPartonFlavour)==3)histGenMuonGenJetPtStrange->Fill(GenJetPt,EventWeight);
	 if(abs(GenPartonFlavour)==4)histGenMuonGenJetPtCharm->Fill(GenJetPt,EventWeight);
	 if(abs(GenPartonFlavour)==5)histGenMuonGenJetPtBeauty->Fill(GenJetPt,EventWeight);
	 if(abs(GenPartonFlavour)==21)histGenMuonGenJetPtGluon->Fill(GenJetPt,EventWeight);
	 
	 hist_GenMaster_GenJetPt_GenMuPt_Flavour->Fill(GenJetPt,MatchedGenMuon.Pt(),PartonFlavour_Local,EventWeight);
	 
	 Double_t GenMuonPtRel = getPtRel(MatchedGenMuon.Pt(), MatchedGenMuon.Eta(), MatchedGenMuon.Phi(), GenJetPt, GenJetEta, GenJetPhi); 
	 hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->Fill(GenJetPt,GenMuonPtRel,PartonFlavour_Local,EventWeight);
	 	 
	 hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->Fill(MatchedGenMuon.Eta(),MatchedGenMuon.Pt(),MatchedGenMuon.Phi(),EventWeight);
	 
	 
       }//GenMuonGenJetDRCut
    
     }//GenJet Loop

     //continue;
     //return;
     
     //================================================================//
     //======================== reconstructed muons ===================//
     //===============================================================//
     //reco mu loop
     std::vector<TLorentzVector> MuonsForJets;
     
     std::vector<TLorentzVector> PositiveMuons;
     std::vector<TLorentzVector> NegativeMuons;

     //matched to reco muon
     TLorentzVector genMuonMatched;
     
     
      for(unsigned long i=0; i<mu_pt->size();i++){
		
	Double_t MuonPt = mu_pt->at(i);
	if(MuonPt<MuonPtMin)continue;
	
	Double_t MuonEta = mu_eta->at(i);
	Double_t MuonPhi = mu_phi->at(i); 
	
	Int_t Mu_isGlobal = mu_isGlobal->at(i);
	Int_t Mu_isTracker = mu_isTracker->at(i);
	Int_t Mu_isPF = mu_isPF->at(i);
	Int_t Mu_isSTA = mu_isSTA->at(i);
	Int_t Mu_isGood = mu_isGood->at(i);
	Int_t Mu_pixelLayers = mu_pixelLayers->at(i);
	Int_t Mu_pixelHits = mu_pixelHits->at(i);
	Int_t Mu_trkLayers = mu_trkLayers->at(i);
	float Mu_D0 = mu_D0->at(i);
	float Mu_Dz = mu_Dz->at(i);
	float Mu_chi2ndf = mu_chi2ndf->at(i);
	float Mu_innerD0 =  mu_innerD0->at(i);
	float Mu_innerDz =  mu_innerDz->at(i);
	float Mu_muonHits = mu_muonHits->at(i);
	Int_t Mu_stations = mu_stations->at(i);
	//new quality cuts added for histos	
	float Mu_innerD0Err =  mu_innerD0Err->at(i);
	float Mu_innerDzErr =  mu_innerDzErr->at(i);
	float Mu_innerD0Norm =  Mu_innerD0/Mu_innerD0Err;
	float Mu_innerDzNorm =  Mu_innerDz/Mu_innerDzErr;
	Int_t Mu_trkQuality = mu_trkQuality->at(i);
	
	//Gen Muon matching
	TLorentzVector Muon;
	Muon.SetPtEtaPhiM(MuonPt, MuonEta, MuonPhi, MuonMass); 

	int smallestDRindex =0;
	double smallestDR = 1000.0;
	Double_t GenMuRecMuDRCut = 0.3;
	for(unsigned long j=0; j<GenMuons.size();j++)
	  {
	    TLorentzVector genMuon = GenMuons.at(j);
	    
	    Double_t RecMuGenMuDR = deltaR(genMuon,Muon);
	    Double_t RecMuGenMuDPt = deltaPt(genMuon,Muon);

	    histGenMuRecMuDRVsDPt->Fill(RecMuGenMuDR,RecMuGenMuDPt,EventWeight);

	    
	    histGenMuRecMuDRVsPt->Fill(RecMuGenMuDR,Muon.Pt(),EventWeight);
	    histGenMuRecMuDRVsEta->Fill(RecMuGenMuDR,Muon.Eta(),EventWeight);
	    histGenMuRecMuDRVsPhi->Fill(RecMuGenMuDR,Muon.Phi(),EventWeight);

	    if(RecMuGenMuDR<smallestDR)
	      {
		smallestDR = RecMuGenMuDR;
		smallestDRindex=j;
	      }
	  }//gen muon loop inside rec muon
	
	Int_t MCMatch = 0;
	if(smallestDR < GenMuRecMuDRCut){
	  genMuonMatched = GenMuons.at(smallestDRindex);

	  //cout<< " Gen Muon found "<<endl;
	  //cout<<" Rec Mu "<< MuonPt <<"  "<<MuonEta<<"  "<<MuonPhi<<endl;
	  //cout<<" Gen Mu "<< genMuonMatched.Pt() <<"  "<< genMuonMatched.Eta() <<"  "<<genMuonMatched.Phi()<<endl;

	  //these are gen muon variables which are matched to reco muon
	  //these reco muons may not have passed the quality cuts
	  hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi->Fill(genMuonMatched.Eta(),genMuonMatched.Pt(),genMuonMatched.Phi(),EventWeight);
	  MCMatch = 1;
	}
	
	//Fill muon quality cut histograms (Only considering global && tracker muons) 
	Int_t BasicCuts =0;
	if(Mu_isGlobal==1 && Mu_isTracker==1){BasicCuts=1;}
	//
	if(BasicCuts==1 && MCMatch==1){
	  histMuonIsGlobal->Fill(Mu_isGlobal,EventWeight);
	  histMuonIsTracker->Fill(Mu_isTracker,EventWeight);
	  histMuonIsPF->Fill(Mu_isPF,EventWeight);
	  histMuonIsSTA->Fill(Mu_isSTA,EventWeight);
	  histMuonD0->Fill(Mu_D0,EventWeight);
	  histMuonDz->Fill(Mu_Dz,EventWeight);
	  histMuonChi2NDF->Fill(Mu_chi2ndf,EventWeight);
	  histMuonInnerD0->Fill(Mu_innerD0,EventWeight);
	  histMuonInnerD0Err->Fill(Mu_innerD0Err,EventWeight);
	  histMuonInnerDz->Fill(Mu_innerDz,EventWeight);	
	  histMuonInnerDzErr->Fill(Mu_innerDzErr,EventWeight);
	  histMuonInnerD0Norm->Fill(Mu_innerD0Norm,EventWeight);
	  histMuonInnerDzNorm->Fill(Mu_innerDzNorm,EventWeight);
	  histMuonTrkLayers->Fill(Mu_trkLayers,EventWeight);
	  histMuonPixelLayers->Fill(Mu_pixelLayers,EventWeight);
	  histMuonPixelHits->Fill(Mu_pixelHits,EventWeight);
	  histMuonMuHits->Fill(Mu_muonHits,EventWeight);
	  histMuonTrkQuality->Fill(Mu_trkQuality,EventWeight);
	  histMuonMuStations->Fill(Mu_stations,EventWeight);
	}
	
	if(BasicCuts==1 && MCMatch==0){

	  histNGMuonIsGlobal->Fill(Mu_isGlobal,EventWeight);
          histNGMuonIsTracker->Fill(Mu_isTracker,EventWeight);
          histNGMuonIsPF->Fill(Mu_isPF,EventWeight);
          histNGMuonIsSTA->Fill(Mu_isSTA,EventWeight);
          histNGMuonD0->Fill(Mu_D0,EventWeight);
          histNGMuonDz->Fill(Mu_Dz,EventWeight);
          histNGMuonChi2NDF->Fill(Mu_chi2ndf,EventWeight);
          histNGMuonInnerD0->Fill(Mu_innerD0,EventWeight);
          histNGMuonInnerD0Err->Fill(Mu_innerD0Err,EventWeight);
          histNGMuonInnerDz->Fill(Mu_innerDz,EventWeight);
          histNGMuonInnerDzErr->Fill(Mu_innerDzErr,EventWeight);
          histNGMuonInnerD0Norm->Fill(Mu_innerD0Norm,EventWeight);
          histNGMuonInnerDzNorm->Fill(Mu_innerDzNorm,EventWeight);
          histNGMuonTrkLayers->Fill(Mu_trkLayers,EventWeight);
          histNGMuonPixelLayers->Fill(Mu_pixelLayers,EventWeight);
	  histNGMuonPixelHits->Fill(Mu_pixelHits,EventWeight);
          histNGMuonMuHits->Fill(Mu_muonHits,EventWeight);
          histNGMuonTrkQuality->Fill(Mu_trkQuality,EventWeight);
          histNGMuonMuStations->Fill(Mu_stations,EventWeight);
	}




	Int_t AllCuts =0;
	
	//if(SoftMuonIDCuts(Mu_isGlobal,Mu_isTracker,Mu_isGood,Mu_pixelHits,Mu_trkLayers,Mu_D0,Mu_Dz)==1){AllCuts = 1;}else{AllCuts=0;}

	//Tight muon ID cuts 
	if(TightMuonIDCuts(Mu_isGlobal,Mu_isTracker,MuonEta,Mu_chi2ndf,Mu_D0,Mu_Dz,Mu_muonHits,Mu_stations,Mu_trkLayers,Mu_pixelHits)==1){AllCuts = 1;}else{AllCuts=0;}
	
	//Tight muon ID cuts + MC matching
	//if(TightMuonIDCuts(Mu_isGlobal,Mu_isTracker,MuonEta,Mu_chi2ndf,Mu_D0,Mu_Dz,Mu_muonHits,Mu_stations,Mu_trkLayers,Mu_pixelHits)==1 && MCMatch==1){AllCuts = 1;}else{AllCuts=0;}
		
	//muon quality cuts
	if(AllCuts==1){

	  MuonsForJets.push_back(Muon);
	  if(mu_chg->at(i)==1)PositiveMuons.push_back(Muon);
	  if(mu_chg->at(i)==-1)NegativeMuons.push_back(Muon);
	  	  
	  histMuonPt->Fill(MuonPt,EventWeight);
	  histMuonEta->Fill(MuonEta,EventWeight);
	  histMuonPhi->Fill(MuonPhi,EventWeight);

	  //Gen Muon matched reco muons (reco muon variables are filled)
	  if(MCMatch==1)histMatchedMuonPt->Fill(MuonPt,EventWeight);
	  if(MCMatch==1)histMatchedMuonEta->Fill(MuonEta,EventWeight);
	  if(MCMatch==1)histMatchedMuonPhi->Fill(MuonPhi,EventWeight);
	  
	  
	  // matched gen muon variables (here reco muons have quality cut applied)
	  if(MCMatch ==1)histRecoMatchedGenMuonPt->Fill(genMuonMatched.Pt(),EventWeight);
	  if(MCMatch ==1)histRecoMatchedGenMuonEta->Fill(genMuonMatched.Eta(),EventWeight);
	  if(MCMatch ==1)histRecoMatchedGenMuonPhi->Fill(genMuonMatched.Phi(),EventWeight);




	  
	} //rec muon quality cuts
      } // rec muon loop

      //================= reconstructed dimuons ================//
      std::vector<TLorentzVector> DiMuons;
      
      for(unsigned long j=0; j < PositiveMuons.size();j++)
	{
	  TLorentzVector MuonPlus = PositiveMuons.at(j);
	  for(unsigned long k=0; k < NegativeMuons.size();k++)
	    {
	      TLorentzVector MuonMinus = NegativeMuons.at(k);
	      TLorentzVector DiMuon = MuonPlus + MuonMinus;
	      DiMuons.push_back(DiMuon);
	      histDiMuonInvMass->Fill(DiMuon.M(),EventWeight);
	      histDiMuonInvMassLow->Fill(DiMuon.M(),EventWeight);
	      histDiMuonInvMassInt->Fill(DiMuon.M(),EventWeight);
	      histDiMuonPt->Fill(DiMuon.Pt(),EventWeight);
	      histDiMuonRapidity->Fill(DiMuon.Rapidity(),EventWeight);
	      histDiMuonPhi->Fill(DiMuon.Phi(),EventWeight);
	    }
	}

   
       
      //===========================================================//
      //=========================== pf jets ======================//
      //===========================================================//
      // Array of TLorentz vectors
      // this is used to store all the muons with Delta R < 0.4
      // As the information is required per jet array of lorentz vectors
      // is used
      const int NPFJETS = pf_jtpt->size();
      std::vector<TLorentzVector> AllMatchedMuons_DR04[NPFJETS];
      TLorentzVector MatchedMuon;
      
      histNumberOfJets->Fill(NPFJETS);
       
      // Getting PF Jet Tree variables
      for (unsigned long i=0; i<pf_jtpt->size();i++) {
	
	//cout<<" JetLoop "<<endl;
	
	Double_t JetPt = pf_jtpt->at(i); 
	Double_t JetEta = pf_jteta->at(i); 

	if(JetPt<JetPtMinCut || TMath::Abs(JetEta) > JetEtaMinCut) continue;

	Double_t JetPhi = pf_jtphi->at(i);
	
	histJetPt->Fill(JetPt,EventWeight);
	histJetEta->Fill(JetEta,EventWeight);
	histJetPhi->Fill(JetPhi,EventWeight);
	
	Double_t PartonFlavour = pf_refparton_flavor->at(i);
	if(Want_RefPartonFlavorForB ==1){PartonFlavour = pf_refparton_flavorForB->at(i);}

	Double_t JetCSVv2 = pf_discr_csvV2->at(i);
	
	//cout<<"rec pt "<<jtpt[i]<<" rec eta "<<jteta[i]<<" rec phi "<<jtphi[i]<<endl;
	//cout<<"ref pt "<<refpt[i]<<" ref eta "<<refeta[i]<<" parton flavour "<< refparton_flavor[i] <<endl;
	
	if(PartonFlavour == 0 || PartonFlavour == -999) histJetPtUnknown->Fill(JetPt,EventWeight);

	if(abs(PartonFlavour)==1 || abs(PartonFlavour)==2 ||abs(PartonFlavour)==3) histJetPtLight->Fill(JetPt,EventWeight);
	if(abs(PartonFlavour)==1)histJetPtUp->Fill(JetPt,EventWeight);
	if(abs(PartonFlavour)==2)histJetPtDown->Fill(JetPt,EventWeight);
	if(abs(PartonFlavour)==3)histJetPtStrange->Fill(JetPt,EventWeight);
	if(abs(PartonFlavour)==4)histJetPtCharm->Fill(JetPt,EventWeight);
	if(abs(PartonFlavour)==5)histJetPtBeauty->Fill(JetPt,EventWeight);
	if(abs(PartonFlavour)==21)histJetPtGluon->Fill(JetPt,EventWeight);


	Int_t PartonFlavour_Local = TMath::Abs(PartonFlavour);
	if(PartonFlavour==21)PartonFlavour_Local=6;
	if(PartonFlavour==-999)PartonFlavour_Local=7;
	if(PartonFlavour==0)PartonFlavour_Local=8;

	hist_Master_JetPt_Flavour->Fill(JetPt,PartonFlavour_Local,EventWeight);
	histJetCSV->Fill(JetCSVv2,EventWeight);
	hist_Master_JetCSV_JetPt_Flavour->Fill(JetCSVv2,JetPt,PartonFlavour_Local,EventWeight);

	
	//======================================================================//
	//==================== pf jet reco muon matching =======================//
	//======================================================================//
	//================ select the Tightest Muon ======================//

	int smallestDRindex =0;
	double smallestDR = 1000.0;
	Double_t MuonJetDR_Max = 0.4;

	//loop over all the muons inside jet

	for(unsigned long j=0; j<MuonsForJets.size();j++)
	 {
	   
	   TLorentzVector Muon = MuonsForJets.at(j);

	   Double_t MuonPt=Muon.Pt();
	   Double_t MuonEta=Muon.Eta();
	   Double_t MuonPhi=Muon.Phi();


	   Double_t MuonJetDR = getDR(MuonEta, MuonPhi, JetEta, JetPhi);
	    
	   histMuonJetDR->Fill(MuonJetDR,EventWeight);
	    
	   Double_t MuonJetDPhi = plotDPHI(MuonPhi,JetPhi);
	    
	   histMuonJetDPhi->Fill(MuonJetDPhi,EventWeight);
	   //Double_t MuonPtRel = getPtRel(MuonPt, MuonEta, MuonPhi, JetPt, JetEta, JetPhi); 
	 

	   //All the matched muons with DR < 0.4 are in this vector
	   if(MuonJetDR < MuonJetDR_Max){
	     
	     AllMatchedMuons_DR04[i].push_back(Muon);
	     
	   }
	   
	   if(MuonJetDR<smallestDR)
	     {
	       smallestDR = MuonJetDR;
	       smallestDRindex=j;
	     }
	   
	 } //MuonsForJet.size()
	
	   
	if( smallestDR < MuonJetDR_Max){

	  MatchedMuon = MuonsForJets.at(smallestDRindex);

	  //if(PartonFlavour!=0 && PartonFlavour!=-999)
	  histMuonJetPtTotal->Fill(JetPt,EventWeight);

	  if(abs(PartonFlavour)==1 || abs(PartonFlavour)==2 ||abs(PartonFlavour)==3) histMuonJetPtLight->Fill(JetPt,EventWeight);
	  if(abs(PartonFlavour)==1)histMuonJetPtUp->Fill(JetPt,EventWeight);
	  if(abs(PartonFlavour)==2)histMuonJetPtDown->Fill(JetPt,EventWeight);
	  if(abs(PartonFlavour)==3)histMuonJetPtStrange->Fill(JetPt,EventWeight);
	  
	  if(abs(PartonFlavour)==4)histMuonJetPtCharm->Fill(JetPt,EventWeight);
	  if(abs(PartonFlavour)==5)histMuonJetPtBeauty->Fill(JetPt,EventWeight);
	  if(abs(PartonFlavour)==21)histMuonJetPtGluon->Fill(JetPt,EventWeight);
     

	  hist_Master_JetPt_MuPt_Flavour->Fill(JetPt,MatchedMuon.Pt(),PartonFlavour_Local,EventWeight);

	  Double_t MuonJetPtRel = getPtRel(MatchedMuon.Pt(),MatchedMuon.Eta(),MatchedMuon.Phi(),JetPt,JetEta,JetPhi);

	  hist_Master_JetPt_MuPtRel_Flavour->Fill(JetPt,MuonJetPtRel,PartonFlavour_Local,EventWeight);

	  hist_Master_MuEta_MuPt_MuPhi->Fill(MatchedMuon.Eta(),MatchedMuon.Pt(),MatchedMuon.Phi(),EventWeight);

	  histMuonJetCSV->Fill(JetCSVv2,EventWeight);
	  
	  hist_Master_MuonJetCSV_MuonJetPt_Flavour->Fill(JetCSVv2,JetPt,PartonFlavour_Local,EventWeight);
	  hist_Master_JetCSV_MuPtRel_Flavour->Fill(JetCSVv2,MuonJetPtRel,PartonFlavour_Local,EventWeight);

	  
	  Fill_hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt[0]=JetCSVv2;
	  Fill_hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt[1]=MuonJetPtRel;
	  Fill_hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt[2]=PartonFlavour_Local;
	  Fill_hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt[3]=MatchedMuon.Pt();


	  hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->Fill(Fill_hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt,EventWeight);

	  histMuonPtRel->Fill(MuonJetPtRel,EventWeight); 

	  const Double_t CSVv2WorkingPoint = 0.9;
	     
	  if(JetCSVv2 > CSVv2WorkingPoint){histMuonPtRelCSVTag->Fill(MuonJetPtRel,EventWeight);} 
	  if(JetCSVv2 < CSVv2WorkingPoint){histMuonPtRelCSVVeto->Fill(MuonJetPtRel,EventWeight);}  
	  
	}//muon Jet DR  (Tightest matched muons)

	
      }//pf Jet Loop
      
      //============= Estimate of how many muons are inside each jet ======================// 
      /****************************************************************************************/
      // ALL THE MUONS PROPERTIES WHICH HAVE DELTA R < 0.4 WITH JETS
      //FILL HISTOGRAMS HERE
     /*************************************************************************************/
      for (int i=0; i<NPFJETS;i++) {
	
	histMatchedMuonsDR04Size->Fill(AllMatchedMuons_DR04[i].size(),EventWeight);
	
	for(unsigned long j=0; j<AllMatchedMuons_DR04[i].size();j++)
	  {
	    
	    TLorentzVector MatchedMuonDR04 = AllMatchedMuons_DR04[i].at(j);
	    
	    Double_t MatchedMuonDR04Pt=MatchedMuonDR04.Pt();
	    Double_t MatchedMuonDR04Eta=MatchedMuonDR04.Eta();
	    Double_t MatchedMuonDR04Phi=MatchedMuonDR04.Phi();
	    
	    histMatchedMuonsDR04Pt->Fill(MatchedMuonDR04Pt,EventWeight); 
	    histMatchedMuonsDR04Eta->Fill(MatchedMuonDR04Eta,EventWeight);
	    histMatchedMuonsDR04Phi->Fill(MatchedMuonDR04Phi,EventWeight);
	  }
      }
      
      
      
  }//Event Entry Loop
  
  
  //return;
  
  //=================== getting projections from histograms =============================//
  
  TH1 *hist_GenMaster_GenJetPt_Flavour_ProjX = hist_GenMaster_GenJetPt_Flavour->ProjectionX("hist_GenMaster_GenJetPt_Flavour_ProjX");
  TH1 *hist_GenMaster_GenJetPt_Flavour_ProjY = hist_GenMaster_GenJetPt_Flavour->ProjectionY("hist_GenMaster_GenJetPt_Flavour_ProjY");


  TH1 *hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjX = hist_GenMaster_GenJetPt_GenMuPt_Flavour->Project3D("hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjX");
  hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjX->SetName("hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjX");
  hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjX->SetTitle("hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjX");


  TH1 *hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY = hist_GenMaster_GenJetPt_GenMuPt_Flavour->Project3D("hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY");
  hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY->SetName("hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY");
  hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY->SetTitle("hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY");


  TH1 *hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ = hist_GenMaster_GenJetPt_GenMuPt_Flavour->Project3D("hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ");
  hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->SetName("hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ");
  hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->SetTitle("hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ");
  
  TH1 *hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjX = hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->Project3D("hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjX");
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjX->SetName("hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjX");
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjX->SetTitle("hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjX");


  TH1 *hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjY = hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->Project3D("hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjY");
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjY->SetName("hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjY");
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjY->SetTitle("hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjY");


  TH1 *hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjZ = hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->Project3D("hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjZ");
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjZ->SetName("hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjZ");
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjZ->SetTitle("hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjZ");
  

  const Int_t is_DrawGenJetPlots =0;
  if(is_DrawGenJetPlots==1){
    
    new TCanvas;
    hist_GenMaster_GenJetPt_Flavour->Draw("surf1");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_Flavour.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_Flavour.pdf");
    
    new TCanvas;
    gPad->SetLogy();
    hist_GenMaster_GenJetPt_Flavour_ProjX->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_Flavour_ProjX.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_Flavour_ProjX.pdf");
  
    new TCanvas;
    gPad->SetLogy();
    hist_GenMaster_GenJetPt_Flavour_ProjY->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_Flavour_ProjY.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_Flavour_ProjY.pdf");
      
    new TCanvas;
    hist_GenMaster_GenJetPt_GenMuPt_Flavour->Draw("surf1");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPt_Flavour.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPt_Flavour.pdf");
    
      
    new TCanvas;
    gPad->SetLogy();
    hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjX->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPt_Flavour_ProjX.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPt_Flavour_ProjX.pdf");
    
  
  
    
    new TCanvas;
    gPad->SetLogy();
    hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPt_Flavour_ProjY.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPt_Flavour_ProjY.pdf");
    
    
    new TCanvas;
    gPad->SetLogy();
    hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->Draw("B");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ.pdf");
    
  
  
    new TCanvas;
    hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->Draw("ISO");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPtRel_Flavour.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPtRel_Flavour.pdf");
    
  

    new TCanvas;
    gPad->SetLogy();
    hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjX->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjX.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjX.pdf");
    
    
  
    new TCanvas;
    gPad->SetLogy();
    hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjY->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjY.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjY.pdf");
    

    new TCanvas;
    gPad->SetLogy();
    hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjZ->Draw("B");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjZ.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjZ.pdf");
    
  }//is_DrawGenPlots

     
  cout<<endl<<endl;
  cout<<" +++++++++++++++++++++++ GEN JETS STUDY ++++++++++++++++++++++++++++++++"<<endl;
  cout<<endl<<endl;

     
  Double_t GenJetPtTotalEntries = histGenJetPt->GetEntries();
  Double_t GenJetPtTotalIntegral = histGenJetPt->Integral(0,histGenJetPt->GetNbinsX()+1);
  
  Double_t GenJetPtUpEntries = histGenJetPtUp->GetEntries();
  Double_t GenJetPtUpIntegral = histGenJetPtUp->Integral(0,histGenJetPtUp->GetNbinsX()+1);
  
  
  Double_t GenJetPtDownEntries = histGenJetPtDown->GetEntries();
  Double_t GenJetPtDownIntegral = histGenJetPtDown->Integral(0,histGenJetPtDown->GetNbinsX()+1);
  

  Double_t GenJetPtStrangeEntries = histGenJetPtStrange->GetEntries();
  Double_t GenJetPtStrangeIntegral = histGenJetPtStrange->Integral(0,histGenJetPtStrange->GetNbinsX()+1);
  

  
  Double_t GenJetPtCharmEntries = histGenJetPtCharm->GetEntries();
  Double_t GenJetPtCharmIntegral = histGenJetPtCharm->Integral(0,histGenJetPtCharm->GetNbinsX()+1);
  

     
  Double_t GenJetPtBeautyEntries = histGenJetPtBeauty->GetEntries();
  Double_t GenJetPtBeautyIntegral = histGenJetPtBeauty->Integral(0,histGenJetPtBeauty->GetNbinsX()+1);
  

  Double_t GenJetPtGluonEntries = histGenJetPtGluon->GetEntries();
  Double_t GenJetPtGluonIntegral = histGenJetPtGluon->Integral(0,histGenJetPtGluon->GetNbinsX()+1);
  


  Double_t TotalEntriesGenJetsFlavourMatched =GenJetPtUpEntries+GenJetPtDownEntries+GenJetPtStrangeEntries
       +GenJetPtCharmEntries+GenJetPtBeautyEntries+GenJetPtGluonEntries;
  
  Double_t TotalIntegralGenJetsFlavourMatched =GenJetPtUpIntegral+GenJetPtDownIntegral+GenJetPtStrangeIntegral
    +GenJetPtCharmIntegral+GenJetPtBeautyIntegral+GenJetPtGluonIntegral;
  
  
  Double_t GenJetPtNoRecEntries = histGenJetPtNoRec->GetEntries();
  Double_t GenJetPtNoRecIntegral = histGenJetPtNoRec->Integral(0,histGenJetPtNoRec->GetNbinsX()+1);


  Double_t GenJetPtUnknownRecEntries = histGenJetPtUnknownRec->GetEntries();
  Double_t GenJetPtUnknownRecIntegral = histGenJetPtUnknownRec->Integral(0,histGenJetPtUnknownRec->GetNbinsX()+1);

     
  cout<<" Jet with no reco matched "<<histGenJetPtNoRec->GetEntries()<<endl;
  cout<<" Jet with unknown matched "<<histGenJetPtUnknownRec->GetEntries()<<endl;


  
  cout<<" Total with flavour  "<<GenJetPtTotalEntries<<"     "<<GenJetPtTotalIntegral<<endl;
  cout<<"                  u "<<GenJetPtUpEntries<<"     "<<GenJetPtUpIntegral<<endl;
  cout<<"                  d "<<GenJetPtDownEntries<<"     "<<GenJetPtDownIntegral<<endl;
  cout<<"                  s "<<GenJetPtStrangeEntries<<"     "<<GenJetPtStrangeIntegral<<endl;
  cout<<"                  c "<<GenJetPtCharmEntries<<"     "<<GenJetPtCharmIntegral<<endl;
  cout<<"                  b "<<GenJetPtBeautyEntries<<"     "<<GenJetPtBeautyIntegral<<endl;
  cout<<"                  g "<<GenJetPtGluonEntries<<"     "<<GenJetPtGluonIntegral<<endl;
  

  cout<<" u+d+s+c+b+g        "<< TotalEntriesGenJetsFlavourMatched <<endl<<endl;
  cout<<endl;
  cout<<" Fractions  with Entries         "<<endl;
  cout<<" Total with flavour  "<<TotalEntriesGenJetsFlavourMatched/GenJetPtTotalEntries<<endl;
  cout<<"                  u "<<GenJetPtUpEntries/GenJetPtTotalEntries<<endl;
  cout<<"                  d "<<GenJetPtDownEntries/GenJetPtTotalEntries<<endl;
  cout<<"                  s "<<GenJetPtStrangeEntries/GenJetPtTotalEntries<<endl;
  cout<<"                  c "<<GenJetPtCharmEntries/GenJetPtTotalEntries<<endl;
  cout<<"                  b "<<GenJetPtBeautyEntries/GenJetPtTotalEntries<<endl;
  cout<<"                  g "<<GenJetPtGluonEntries/GenJetPtTotalEntries<<endl;
  cout<<endl;
  




  cout<<" u+d+s+c+b+g        "<< TotalIntegralGenJetsFlavourMatched <<endl<<endl;
  cout<<endl;
  cout<<" Fractions  with Integral         "<<endl;
  cout<<" Total with flavour  "<<TotalIntegralGenJetsFlavourMatched/GenJetPtTotalIntegral<<endl;
  cout<<"                  u "<<GenJetPtUpIntegral/GenJetPtTotalIntegral<<endl;
  cout<<"                  d "<<GenJetPtDownIntegral/GenJetPtTotalIntegral<<endl;
  cout<<"                  s "<<GenJetPtStrangeIntegral/GenJetPtTotalIntegral<<endl;
  cout<<"                  c "<<GenJetPtCharmIntegral/GenJetPtTotalIntegral<<endl;
  cout<<"                  b "<<GenJetPtBeautyIntegral/GenJetPtTotalIntegral<<endl;
  cout<<"                  g "<<GenJetPtGluonIntegral/GenJetPtTotalIntegral<<endl;

     
     
  cout<<endl<<endl;
  cout<<endl<<endl;
     

     
  Double_t GenMuonGenJetPtTotalEntries = histGenMuonGenJetPtTotal->GetEntries();
  Double_t GenMuonGenJetPtTotalIntegral = histGenMuonGenJetPtTotal->Integral(0,histGenMuonGenJetPtTotal->GetNbinsX()+1);
  
  Double_t GenMuonGenJetPtUpEntries = histGenMuonGenJetPtUp->GetEntries();
  Double_t GenMuonGenJetPtUpIntegral = histGenMuonGenJetPtUp->Integral(0,histGenMuonGenJetPtUp->GetNbinsX()+1);
  
  
  Double_t GenMuonGenJetPtDownEntries = histGenMuonGenJetPtDown->GetEntries();
  Double_t GenMuonGenJetPtDownIntegral = histGenMuonGenJetPtDown->Integral(0,histGenMuonGenJetPtDown->GetNbinsX()+1);
  

  Double_t GenMuonGenJetPtStrangeEntries = histGenMuonGenJetPtStrange->GetEntries();
  Double_t GenMuonGenJetPtStrangeIntegral = histGenMuonGenJetPtStrange->Integral(0,histGenMuonGenJetPtStrange->GetNbinsX()+1);


     
  Double_t GenMuonGenJetPtCharmEntries = histGenMuonGenJetPtCharm->GetEntries();
  Double_t GenMuonGenJetPtCharmIntegral = histGenMuonGenJetPtCharm->Integral(0,histGenMuonGenJetPtCharm->GetNbinsX()+1);
  

     
  Double_t GenMuonGenJetPtBeautyEntries = histGenMuonGenJetPtBeauty->GetEntries();
  Double_t GenMuonGenJetPtBeautyIntegral = histGenMuonGenJetPtBeauty->Integral(0,histGenMuonGenJetPtBeauty->GetNbinsX()+1);
  

  Double_t GenMuonGenJetPtGluonEntries = histGenMuonGenJetPtGluon->GetEntries();
  Double_t GenMuonGenJetPtGluonIntegral = histGenMuonGenJetPtGluon->Integral(0,histGenMuonGenJetPtGluon->GetNbinsX()+1);



  Double_t TotalEntriesGenMuonGenJetsFlavourMatched =GenMuonGenJetPtUpEntries+GenMuonGenJetPtDownEntries+GenMuonGenJetPtStrangeEntries
    +GenMuonGenJetPtCharmEntries+GenMuonGenJetPtBeautyEntries+GenMuonGenJetPtGluonEntries;
  
  Double_t TotalIntegralGenMuonGenJetsFlavourMatched =GenMuonGenJetPtUpIntegral+GenMuonGenJetPtDownIntegral+GenMuonGenJetPtStrangeIntegral
    +GenMuonGenJetPtCharmIntegral+GenMuonGenJetPtBeautyIntegral+GenMuonGenJetPtGluonIntegral;
  
       
  
     
  cout<<" Jets with muon DeltaR < 0.4 "<<endl;
  cout<<" Total with flavour  "<<GenMuonGenJetPtTotalEntries<<"     "<<GenMuonGenJetPtTotalIntegral<<endl;
  cout<<"                  u "<<GenMuonGenJetPtUpEntries<<"     "<<GenMuonGenJetPtUpIntegral<<endl;
  cout<<"                  d "<<GenMuonGenJetPtDownEntries<<"     "<<GenMuonGenJetPtDownIntegral<<endl;
  cout<<"                  s "<<GenMuonGenJetPtStrangeEntries<<"     "<<GenMuonGenJetPtStrangeIntegral<<endl;
  cout<<"                  c "<<GenMuonGenJetPtCharmEntries<<"     "<<GenMuonGenJetPtCharmIntegral<<endl;
  cout<<"                  b "<<GenMuonGenJetPtBeautyEntries<<"     "<<GenMuonGenJetPtBeautyIntegral<<endl;
  cout<<"                  g "<<GenMuonGenJetPtGluonEntries<<"     "<<GenMuonGenJetPtGluonIntegral<<endl;
  

  cout<<" u+d+s+c+b+g        "<< TotalEntriesGenMuonGenJetsFlavourMatched <<endl<<endl;
  cout<<endl;
  cout<<" Fractions  with Entries         "<<endl;
  cout<<" Total with flavour  "<<TotalEntriesGenMuonGenJetsFlavourMatched/GenMuonGenJetPtTotalEntries<<endl;
  cout<<"                  u "<<GenMuonGenJetPtUpEntries/GenMuonGenJetPtTotalEntries<<endl;
  cout<<"                  d "<<GenMuonGenJetPtDownEntries/GenMuonGenJetPtTotalEntries<<endl;
  cout<<"                  s "<<GenMuonGenJetPtStrangeEntries/GenMuonGenJetPtTotalEntries<<endl;
  cout<<"                  c "<<GenMuonGenJetPtCharmEntries/GenMuonGenJetPtTotalEntries<<endl;
  cout<<"                  b "<<GenMuonGenJetPtBeautyEntries/GenMuonGenJetPtTotalEntries<<endl;
  cout<<"                  g "<<GenMuonGenJetPtGluonEntries/GenMuonGenJetPtTotalEntries<<endl;
  cout<<endl;
    




  cout<<" u+d+s+c+b+g        "<< TotalIntegralGenMuonGenJetsFlavourMatched <<endl<<endl;
  cout<<endl;
  cout<<" Fractions  with Integral         "<<endl;
  cout<<" Total with flavour  "<<TotalIntegralGenMuonGenJetsFlavourMatched/GenMuonGenJetPtTotalIntegral<<endl;
  cout<<"                  u "<<GenMuonGenJetPtUpIntegral/GenMuonGenJetPtTotalIntegral<<endl;
  cout<<"                  d "<<GenMuonGenJetPtDownIntegral/GenMuonGenJetPtTotalIntegral<<endl;
  cout<<"                  s "<<GenMuonGenJetPtStrangeIntegral/GenMuonGenJetPtTotalIntegral<<endl;
  cout<<"                  c "<<GenMuonGenJetPtCharmIntegral/GenMuonGenJetPtTotalIntegral<<endl;
  cout<<"                  b "<<GenMuonGenJetPtBeautyIntegral/GenMuonGenJetPtTotalIntegral<<endl;
  cout<<"                  g "<<GenMuonGenJetPtGluonIntegral/GenMuonGenJetPtTotalIntegral<<endl;

     
     
  cout<<endl<<endl;
  
  
  Double_t GenXIntegral = hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjX->Integral(0,hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjX->GetNbinsX()+1);
  Double_t GenYIntegral = hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY->Integral(0,hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY->GetNbinsX()+1);
  Double_t GenZIntegral = hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->Integral(0,hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetNbinsX()+1);
  
     

  cout<<" Gen Intgrals "<<endl;
  cout<<" Gen XIntegral "<<GenXIntegral<<endl;
  cout<<" Gen YIntegral "<<GenYIntegral<<endl;
  cout<<" Gen ZIntegral "<<GenZIntegral<<endl;
  
  cout<<endl<<endl;
  
  //Int_t NBinsHisto = hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetNbinsX()+1;
  
  
  
  Int_t NBinsHisto = hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetNbinsX();
  
  const int NN = 8;
  
  Double_t ProjHistBinContent[NN]={0.0};
  
  for(int i = 0; i <=NBinsHisto+1; i++)
    {
      
      cout<<" flavour bin centre "<<hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetBinCenter(i)<<
	" bin content "<<hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetBinContent(i)<<" fraction "<<hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetBinContent(i)/GenZIntegral<<endl;
      
    }

         

  cout<<" ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ "<<endl;
  cout<<" ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ "<<endl;

  cout<<endl<<endl;
     





  cout<<endl<<endl;
  cout<<" +++++++++++++++++++++++ GEN MUONS STUDY ++++++++++++++++++++++++++++++++"<<endl;
  cout<<endl<<endl;

  TH1 *hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjX = hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->ProjectionX("hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjX");
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjX->SetName("hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjX");
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjX->SetTitle("hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjX");
  
  TH1 *hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjY = hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->ProjectionY("hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjY");
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjY->SetName("hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjY");
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjY->SetTitle("hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjY");


  TH1 *hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjZ = hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->ProjectionZ("hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjZ");
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjZ->SetName("hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjZ");
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjZ->SetTitle("hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjZ");
  


  Double_t GenMuPtIntegral_Total = histGenMuonPt->Integral(0,histGenMuonPt->GetNbinsX()+1);
  
  
  Double_t GenMuPtIntegral_WithJets = GenYIntegral;
  Double_t GenMu_RatioWithJets = GenYIntegral/GenMuPtIntegral_Total;
  

  cout<<" Absolute Number of GEN Muons Does Not Matter as we are working with weighted distributions "<<endl;
  cout<<" Integral of Histo with all GEN Muons         "<<GenMuPtIntegral_Total<<endl;
  cout<<" Integral of Histo with GEN Muons with Jets   "<<GenMuPtIntegral_WithJets<<endl;
  cout<<" Ratio of GEN Muons with Jets                 "<< GenMu_RatioWithJets <<endl;
  
  


  const Int_t is_DrawGenMuonPlots =0;

  if(is_DrawGenMuonPlots==1){
    new TCanvas;
    gPad->SetLogy();
    hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjX->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjX.png");
    gPad->SaveAs("Plots_JetAnalyzer/hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjX.pdf");
    
  
    new TCanvas;
    gPad->SetLogy();
    hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjY->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjY.png");
    gPad->SaveAs("Plots_JetAnalyzer/hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjY.pdf");
    
  
    new TCanvas;
    gPad->SetLogy();
    hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjZ->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjZ.png");
    gPad->SaveAs("Plots_JetAnalyzer/hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjZ.pdf");
  }
  
  
  
  cout<<" ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ "<<endl;
  cout<<" ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ "<<endl;
  
  cout<<endl<<endl;



  TH1 *hist_Master_JetPt_Flavour_ProjX = hist_Master_JetPt_Flavour->ProjectionX("hist_Master_JetPt_Flavour_ProjX");
  hist_Master_JetPt_Flavour_ProjX->SetName("hist_Master_JetPt_Flavour_ProjX");
  hist_Master_JetPt_Flavour_ProjX->SetTitle("hist_Master_JetPt_Flavour_ProjX");


  TH1 *hist_Master_JetPt_Flavour_ProjY = hist_Master_JetPt_Flavour->ProjectionY("hist_Master_JetPt_Flavour_ProjY");
  hist_Master_JetPt_Flavour_ProjY->SetName("hist_Master_JetPt_Flavour_ProjY");
  hist_Master_JetPt_Flavour_ProjY->SetTitle("hist_Master_JetPt_Flavour_ProjY");
   
  TH1 *hist_Master_JetPt_MuPt_Flavour_ProjX = hist_Master_JetPt_MuPt_Flavour->Project3D("hist_Master_JetPt_MuPt_Flavour_ProjX");
  hist_Master_JetPt_MuPt_Flavour_ProjX->SetName("hist_Master_JetPt_MuPt_Flavour_ProjX");
  hist_Master_JetPt_MuPt_Flavour_ProjX->SetTitle("hist_Master_JetPt_MuPt_Flavour_ProjX");
  
  TH1 *hist_Master_JetPt_MuPt_Flavour_ProjY = hist_Master_JetPt_MuPt_Flavour->Project3D("hist_Master_JetPt_MuPt_Flavour_ProjY");
  hist_Master_JetPt_MuPt_Flavour_ProjY->SetName("hist_Master_JetPt_MuPt_Flavour_ProjY");
  hist_Master_JetPt_MuPt_Flavour_ProjY->SetTitle("hist_Master_JetPt_MuPt_Flavour_ProjY");

  TH1 *hist_Master_JetPt_MuPt_Flavour_ProjZ = hist_Master_JetPt_MuPt_Flavour->Project3D("hist_Master_JetPt_MuPt_Flavour_ProjZ");
  hist_Master_JetPt_MuPt_Flavour_ProjZ->SetName("hist_Master_JetPt_MuPt_Flavour_ProjZ");
  hist_Master_JetPt_MuPt_Flavour_ProjZ->SetTitle("hist_Master_JetPt_MuPt_Flavour_ProjZ");
  

   
  TH1 *hist_Master_JetPt_MuPtRel_Flavour_ProjX = hist_Master_JetPt_MuPtRel_Flavour->Project3D("hist_Master_JetPt_MuPtRel_Flavour_ProjX");
  hist_Master_JetPt_MuPtRel_Flavour_ProjX->SetName("hist_Master_JetPt_MuPtRel_Flavour_ProjX");
  hist_Master_JetPt_MuPtRel_Flavour_ProjX->SetTitle("hist_Master_JetPt_MuPtRel_Flavour_ProjX");
  

  
  TH1 *hist_Master_JetPt_MuPtRel_Flavour_ProjY = hist_Master_JetPt_MuPtRel_Flavour->Project3D("hist_Master_JetPt_MuPtRel_Flavour_ProjY");
  hist_Master_JetPt_MuPtRel_Flavour_ProjY->SetName("hist_Master_JetPt_MuPtRel_Flavour_ProjY");
  hist_Master_JetPt_MuPtRel_Flavour_ProjY->SetTitle("hist_Master_JetPt_MuPtRel_Flavour_ProjY");



  TH1 *hist_Master_JetPt_MuPtRel_Flavour_ProjZ = hist_Master_JetPt_MuPtRel_Flavour->Project3D("hist_Master_JetPt_MuPtRel_Flavour_ProjZ");
  hist_Master_JetPt_MuPtRel_Flavour_ProjZ->SetName("hist_Master_JetPt_MuPtRel_Flavour_ProjZ");
  hist_Master_JetPt_MuPtRel_Flavour_ProjZ->SetTitle("hist_Master_JetPt_MuPtRel_Flavour_ProjZ");
  
  const Int_t is_MakeRecoJetPlots =0;

  if(is_MakeRecoJetPlots==1){

    new TCanvas;
    hist_Master_JetPt_Flavour->Draw("colz");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_Flavour.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_Flavour.pdf");
    

          
    new TCanvas;
    gPad->SetLogy();
    hist_Master_JetPt_Flavour_ProjX->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_Flavour_ProjX.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_Flavour_ProjX.pdf");
  
     

    new TCanvas;
    gPad->SetLogy();
    hist_Master_JetPt_Flavour_ProjY->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_Flavour_ProjY.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_Flavour_ProjY.pdf");
  

     
    new TCanvas;
    hist_Master_JetPt_MuPt_Flavour->Draw("ISO");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPt_Flavour.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPt_Flavour.pdf");



     
    new TCanvas;
    gPad->SetLogy();
    hist_Master_JetPt_MuPt_Flavour_ProjX->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPt_Flavour_ProjX.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPt_Flavour_ProjX.pdf");
  


    new TCanvas;
    gPad->SetLogy();
    hist_Master_JetPt_MuPt_Flavour_ProjY->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPt_Flavour_ProjY.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPt_Flavour_ProjY.pdf");
  
  
    new TCanvas;
    gPad->SetLogy();
    hist_Master_JetPt_MuPt_Flavour_ProjZ->Draw("B");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPt_Flavour_ProjZ.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPt_Flavour_ProjZ.pdf");
  
     
          
    new TCanvas;
    hist_Master_JetPt_MuPtRel_Flavour->Draw("ISO");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPtRel_Flavour.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPtRel_Flavour.pdf");
  
  

    new TCanvas;
    gPad->SetLogy();
    hist_Master_JetPt_MuPtRel_Flavour_ProjX->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPtRel_Flavour_ProjX.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPtRel_Flavour_ProjX.pdf");
  
  
    new TCanvas;
    gPad->SetLogy();
    hist_Master_JetPt_MuPtRel_Flavour_ProjY->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPtRel_Flavour_ProjY.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPtRel_Flavour_ProjY.pdf");
  

    new TCanvas;
    gPad->SetLogy();
    hist_Master_JetPt_MuPtRel_Flavour_ProjZ->Draw("B");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPtRel_Flavour_ProjZ.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_JetPt_MuPtRel_Flavour_ProjZ.pdf");
     
  }//is_MakeRecoJetPlots
    

  cout<<endl<<endl;
  cout<<" +++++++++++++++++++++++ RECO JETS STUDY ++++++++++++++++++++++++++++++++"<<endl;
  cout<<endl<<endl;
  
  
  Double_t JetPtEntries = histJetPt->GetEntries();
  Double_t JetPtIntegral = histJetPt->Integral(0,histJetPt->GetNbinsX()+1);
  
  Double_t JetPtUpEntries = histJetPtUp->GetEntries();
  Double_t JetPtUpIntegral = histJetPtUp->Integral(0,histJetPtUp->GetNbinsX()+1);
  

  Double_t JetPtDownEntries = histJetPtDown->GetEntries();
  Double_t JetPtDownIntegral = histJetPtDown->Integral(0,histJetPtDown->GetNbinsX()+1);
  

  Double_t JetPtStrangeEntries = histJetPtStrange->GetEntries();
  Double_t JetPtStrangeIntegral = histJetPtStrange->Integral(0,histJetPtStrange->GetNbinsX()+1);
  

     
  Double_t JetPtCharmEntries = histJetPtCharm->GetEntries();
  Double_t JetPtCharmIntegral = histJetPtCharm->Integral(0,histJetPtCharm->GetNbinsX()+1);
  
  
     
  Double_t JetPtBeautyEntries = histJetPtBeauty->GetEntries();
  Double_t JetPtBeautyIntegral = histJetPtBeauty->Integral(0,histJetPtBeauty->GetNbinsX()+1);
  

  Double_t JetPtGluonEntries = histJetPtGluon->GetEntries();
  Double_t JetPtGluonIntegral = histJetPtGluon->Integral(0,histJetPtGluon->GetNbinsX()+1);
  

  
  Double_t TotalEntriesJetsFlavourMatched =JetPtUpEntries+JetPtDownEntries+JetPtStrangeEntries
    +JetPtCharmEntries+JetPtBeautyEntries+JetPtGluonEntries;
  
  Double_t TotalIntegralJetsFlavourMatched =JetPtUpIntegral+JetPtDownIntegral+JetPtStrangeIntegral
    +JetPtCharmIntegral+JetPtBeautyIntegral+JetPtGluonIntegral;
  

  Double_t JetPtUnknown = histJetPtUnknown->GetEntries();
  
  
  cout<<" Total with flavour  "<<histJetPt->GetEntries()<<endl;
  cout<<"                  u "<<histJetPtUp->GetEntries()<<endl;
  cout<<"                  d "<<histJetPtDown->GetEntries()<<endl;
  cout<<"                  s "<<histJetPtStrange->GetEntries()<<endl;
  cout<<"                  c "<<histJetPtCharm->GetEntries()<<endl;
  cout<<"                  b "<<histJetPtBeauty->GetEntries()<<endl;
  cout<<"                  g "<<histJetPtGluon->GetEntries()<<endl;
  
  Double_t TotalJetsFlavourMatched = histJetPtUp->GetEntries()+histJetPtDown->GetEntries()
    +histJetPtStrange->GetEntries()+histJetPtCharm->GetEntries()+histJetPtBeauty->GetEntries()+histJetPtGluon->GetEntries();
  cout<<" u+d+s+c+b+g        "<< TotalJetsFlavourMatched <<endl<<endl;
  
  cout<<" Jet with unknown flavour "<<histJetPtUnknown->GetEntries()<<endl;
  
  
  cout<<endl<<endl;
  



  cout<<endl<<endl;
  
  
  Double_t MuonJetPtTotalEntries = histMuonJetPtTotal->GetEntries();
  Double_t MuonJetPtTotalIntegral = histMuonJetPtTotal->Integral(0,histMuonJetPtTotal->GetNbinsX()+1);
  
  Double_t MuonJetPtUpEntries = histMuonJetPtUp->GetEntries();
  Double_t MuonJetPtUpIntegral = histMuonJetPtUp->Integral(0,histMuonJetPtUp->GetNbinsX()+1);
  
  
  Double_t MuonJetPtDownEntries = histMuonJetPtDown->GetEntries();
  Double_t MuonJetPtDownIntegral = histMuonJetPtDown->Integral(0,histMuonJetPtDown->GetNbinsX()+1);
  
  
  Double_t MuonJetPtStrangeEntries = histMuonJetPtStrange->GetEntries();
  Double_t MuonJetPtStrangeIntegral = histMuonJetPtStrange->Integral(0,histMuonJetPtStrange->GetNbinsX()+1);
  
  
     
  Double_t MuonJetPtCharmEntries = histMuonJetPtCharm->GetEntries();
  Double_t MuonJetPtCharmIntegral = histMuonJetPtCharm->Integral(0,histMuonJetPtCharm->GetNbinsX()+1);
  

     
  Double_t MuonJetPtBeautyEntries = histMuonJetPtBeauty->GetEntries();
  Double_t MuonJetPtBeautyIntegral = histMuonJetPtBeauty->Integral(0,histMuonJetPtBeauty->GetNbinsX()+1);
  

  Double_t MuonJetPtGluonEntries = histMuonJetPtGluon->GetEntries();
  Double_t MuonJetPtGluonIntegral = histMuonJetPtGluon->Integral(0,histMuonJetPtGluon->GetNbinsX()+1);
  


  Double_t TotalEntriesMuonJetsFlavourMatched =MuonJetPtUpEntries+MuonJetPtDownEntries+MuonJetPtStrangeEntries
    +MuonJetPtCharmEntries+MuonJetPtBeautyEntries+MuonJetPtGluonEntries;
  
  Double_t TotalIntegralMuonJetsFlavourMatched =MuonJetPtUpIntegral+MuonJetPtDownIntegral+MuonJetPtStrangeIntegral
    +MuonJetPtCharmIntegral+MuonJetPtBeautyIntegral+MuonJetPtGluonIntegral;
  
  
  
  
  cout<<" Jets with muon DeltaR < 0.4 "<<endl;
  cout<<" u+d+s+c+b+g        "<< TotalEntriesMuonJetsFlavourMatched <<endl<<endl;
  cout<<endl;
  cout<<" Fractions  with Entries         "<<endl;
  cout<<" Total with flavour  "<<TotalEntriesMuonJetsFlavourMatched/MuonJetPtTotalEntries<<endl;
  cout<<"                  u "<<MuonJetPtUpEntries/MuonJetPtTotalEntries<<endl;
  cout<<"                  d "<<MuonJetPtDownEntries/MuonJetPtTotalEntries<<endl;
  cout<<"                  s "<<MuonJetPtStrangeEntries/MuonJetPtTotalEntries<<endl;
  cout<<"                  c "<<MuonJetPtCharmEntries/MuonJetPtTotalEntries<<endl;
  cout<<"                  b "<<MuonJetPtBeautyEntries/MuonJetPtTotalEntries<<endl;
  cout<<"                  g "<<MuonJetPtGluonEntries/MuonJetPtTotalEntries<<endl;
  cout<<endl;
  
  
  
  cout<<" u+d+s+c+b+g        "<< TotalIntegralMuonJetsFlavourMatched <<endl<<endl;
  cout<<endl;
  cout<<" Fractions  with Integral         "<<endl;
  cout<<" Total with flavour  "<<TotalIntegralMuonJetsFlavourMatched/MuonJetPtTotalIntegral<<endl;
  cout<<"                  u "<<MuonJetPtUpIntegral/MuonJetPtTotalIntegral<<endl;
  cout<<"                  d "<<MuonJetPtDownIntegral/MuonJetPtTotalIntegral<<endl;
  cout<<"                  s "<<MuonJetPtStrangeIntegral/MuonJetPtTotalIntegral<<endl;
  cout<<"                  c "<<MuonJetPtCharmIntegral/MuonJetPtTotalIntegral<<endl;
  cout<<"                  b "<<MuonJetPtBeautyIntegral/MuonJetPtTotalIntegral<<endl;
  cout<<"                  g "<<MuonJetPtGluonIntegral/MuonJetPtTotalIntegral<<endl;
  
     
  
  cout<<endl<<endl;

  Double_t XIntegral = hist_Master_JetPt_MuPt_Flavour_ProjX->Integral(0,hist_Master_JetPt_MuPt_Flavour_ProjX->GetNbinsX());
  Double_t YIntegral = hist_Master_JetPt_MuPt_Flavour_ProjY->Integral(0,hist_Master_JetPt_MuPt_Flavour_ProjY->GetNbinsX());
  Double_t ZIntegral = hist_Master_JetPt_MuPt_Flavour_ProjZ->Integral(0,hist_Master_JetPt_MuPt_Flavour_ProjZ->GetNbinsX());
  
  
  cout<<" Intgrals "<<endl;
  cout<<" XIntegral "<<XIntegral<<endl;
  cout<<" YIntegral "<<YIntegral<<endl;
  cout<<" ZIntegral "<<ZIntegral<<endl;
     
  cout<<endl<<endl;
     
  
  //Int_t NBinsHisto = hist_Master_JetPt_MuPt_Flavour_ProjZ->GetNbinsX();
  
  //const int NN = 8;
  
  Double_t RecProjHistBinContent[NN]={0.0};
  
  for(int i = 0; i <=NBinsHisto+1; i++)
    {
      
      cout<<" flavour bin centre "<<hist_Master_JetPt_MuPt_Flavour_ProjZ->GetBinCenter(i)<<" bin content "<<hist_Master_JetPt_MuPt_Flavour_ProjZ->GetBinContent(i)<<
	" fraction "<<hist_Master_JetPt_MuPt_Flavour_ProjZ->GetBinContent(i)/ZIntegral<<endl;
      
      RecProjHistBinContent[i]=hist_Master_JetPt_MuPt_Flavour_ProjZ->GetBinContent(i);
      
    }
  
  
  
  
     
     
  cout<<endl<<endl;
  cout<<" +++++++++++++++++++++++ REC MUONS STUDY ++++++++++++++++++++++++++++++++"<<endl;
  cout<<endl<<endl;
  
  
  TH1 *hist_Master_MuEta_MuPt_MuPhi_ProjX = hist_Master_MuEta_MuPt_MuPhi->ProjectionX("hist_Master_MuEta_MuPt_MuPhi_ProjX");
  hist_Master_MuEta_MuPt_MuPhi_ProjX->SetName("hist_Master_MuEta_MuPt_MuPhi_ProjX");
  hist_Master_MuEta_MuPt_MuPhi_ProjX->SetTitle("hist_Master_MuEta_MuPt_MuPhi_ProjX");
  
  
  TH1 *hist_Master_MuEta_MuPt_MuPhi_ProjY = hist_Master_MuEta_MuPt_MuPhi->ProjectionY("hist_Master_MuEta_MuPt_MuPhi_ProjY");
  hist_Master_MuEta_MuPt_MuPhi_ProjY->SetName("hist_Master_MuEta_MuPt_MuPhi_ProjY");
  hist_Master_MuEta_MuPt_MuPhi_ProjY->SetTitle("hist_Master_MuEta_MuPt_MuPhi_ProjY");


          
  TH1 *hist_Master_MuEta_MuPt_MuPhi_ProjZ = hist_Master_MuEta_MuPt_MuPhi->ProjectionZ("hist_Master_MuEta_MuPt_MuPhi_ProjZ");
  hist_Master_MuEta_MuPt_MuPhi_ProjZ->SetName("hist_Master_MuEta_MuPt_MuPhi_ProjZ");
  hist_Master_MuEta_MuPt_MuPhi_ProjZ->SetTitle("hist_Master_MuEta_MuPt_MuPhi_ProjZ");




     
  Double_t MuPtIntegral_Total = histMuonPt->Integral(0,histMuonPt->GetNbinsX()+1);
  
  
  Double_t MuPtIntegral_WithJets = YIntegral;
  Double_t Mu_RatioWithJets = YIntegral/MuPtIntegral_Total;
  
  cout<<" Absolute Number of REC Muons Does Not Matter as we are working with weighted distributions "<<endl;
  cout<<" Integral of Histo with all REC Muons         "<<MuPtIntegral_Total<<endl;
  cout<<" Integral of Histo with REC Muons with Jets   "<<MuPtIntegral_WithJets<<endl;
  cout<<" Ratio of REC Muons with Jets                 "<< Mu_RatioWithJets <<endl;
  
          
  cout<<" ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ "<<endl;
  cout<<" ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ "<<endl;
  
  cout<<endl<<endl;

  //================= stuff with the pt hat ==============//
  
  cout<<endl<<endl;
  
  TAxis* xAxis = histPtHatBins->GetXaxis();
  for(int i=1;i<=histPtHatBins->GetNbinsX();i++)
    {      
      cout<<" Number of events in bin ["<<xAxis->GetBinLowEdge(i)<<"  "<<xAxis->GetBinUpEdge(i)<<"] "<<histPtHatBins->GetBinContent(i)<<endl;
    }
  cout<<endl<<endl;
  
  const Int_t is_DrawPlots =0;
  if(is_DrawPlots==1){
    new TCanvas;
    gPad->SetLogy();
    hist_Master_MuEta_MuPt_MuPhi_ProjX->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/hist_Master_MuEta_MuPt_MuPhi_ProjX.png");
    gPad->SaveAs("Plots_JetAnalyzer/hist_Master_MuEta_MuPt_MuPhi_ProjX.pdf");
  
    
    new TCanvas;
    gPad->SetLogy();
    hist_Master_MuEta_MuPt_MuPhi_ProjY->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/hist_Master_MuEta_MuPt_MuPhi_ProjY.png");
    gPad->SaveAs("Plots_JetAnalyzer/hist_Master_MuEta_MuPt_MuPhi_ProjY.pdf");
  
  
  
    new TCanvas;
    gPad->SetLogy();
    hist_Master_MuEta_MuPt_MuPhi_ProjZ->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/hist_Master_MuEta_MuPt_MuPhi_ProjZ.png");
    gPad->SaveAs("Plots_JetAnalyzer/hist_Master_MuEta_MuPt_MuPhi_ProjZ.pdf");
  



  
    new TCanvas;
    gPad->SetLogy(1);
    histGenJetPt->Draw();
  
    new TCanvas;
    histGenJetEta->Draw();
  
  
    new TCanvas;
    histGenJetPhi->Draw();



    new TCanvas;
    gPad->SetLogy(1);
    histGenJetPtLight->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histGenJetPtUp->Draw();


    new TCanvas;
    gPad->SetLogy(1);
    histGenJetPtDown->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histGenJetPtStrange->Draw(); 

  
    new TCanvas;
    gPad->SetLogy(1);
    histGenJetPtCharm->Draw(); 

    new TCanvas;
    gPad->SetLogy(1);
    histGenJetPtBeauty->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histGenJetPtGluon->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histGenJetPtNoRec->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histGenJetPtUnknownRec->Draw(); 


    new TCanvas;
    gPad->SetLogy(1);
    histJetPt->Draw();
  
    new TCanvas;
    histJetEta->Draw();

    new TCanvas;
    histJetPhi->Draw();


    new TCanvas;
    gPad->SetLogy(1);
    histJetPtLight->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histJetPtUp->Draw();


    new TCanvas;
    gPad->SetLogy(1);
    histJetPtDown->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histJetPtStrange->Draw(); 

  
    new TCanvas;
    gPad->SetLogy(1);
    histJetPtCharm->Draw(); 

    new TCanvas;
    gPad->SetLogy(1);
    histJetPtBeauty->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histJetPtGluon->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histJetPtUnknown->Draw(); 




    new TCanvas;
    hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->Draw("surf1");
    gPad->SaveAs("Plots_JetAnalyzer/Master_GenMuonEta_GenMuonPt_GenMuPhi.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_GenMuonEta_GenMuonPt_GenMuPhi.pdf");


    //return;
  
    new TCanvas;
    gPad->SetLogy(1);
    histGenMuonPt->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenMuonPt.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMuonPt.pdf");

  
    new TCanvas;
    histGenMuonEta->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenMuonEta.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMuonEta.pdf");

    new TCanvas;
    histGenMuonPhi->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenMuonPhi.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenMuonPhi.pdf");



    new TCanvas;
    histGenDiMuonInvMass->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonInvMass.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonInvMass.pdf");


    new TCanvas;
    histGenDiMuonInvMassLow->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonInvMassLow.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonInvMassLow.pdf");



    new TCanvas;
    histGenDiMuonInvMassInt->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonInvMassInt.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonInvMassInt.pdf");
  
  
    new TCanvas;
    gPad->SetLogy(1);
    histGenDiMuonPt->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonPt.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonPt.pdf");

  
    new TCanvas;
    histGenDiMuonRapidity->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonRapidity.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonRapidity.pdf");

    new TCanvas;
    histGenDiMuonPhi->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonPhi.png");
    gPad->SaveAs("Plots_JetAnalyzer/GenDiMuonPhi.pdf");
  
 
    new TCanvas;
    histGenMuonGenJetDR->Draw();

    new TCanvas;
    histGenMuonGenJetDPhi->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histGenMuonGenJetPtTotal->Draw();
  
    new TCanvas;
    gPad->SetLogy(1);
    histGenMuonGenJetPtLight->Draw();
    new TCanvas;
    gPad->SetLogy(1);
    histGenMuonGenJetPtCharm->Draw();
    new TCanvas;
    gPad->SetLogy(1);
    histGenMuonGenJetPtBeauty->Draw();
    new TCanvas;
    gPad->SetLogy(1);
    histGenMuonGenJetPtGluon->Draw();



    new TCanvas;
    gPad->SetLogy(1);
    hist_Master_MuEta_MuPt_MuPhi->Draw("colz");
    gPad->SaveAs("Plots_JetAnalyzer/Master_MuonEta_MuonPt_MuPhi.png");
    gPad->SaveAs("Plots_JetAnalyzer/Master_MuonEta_MuonPt_MuPhi.pdf");
  
  
  
    new TCanvas;
    gPad->SetLogy(1);
    histMuonPt->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/MuonPt.png");
    gPad->SaveAs("Plots_JetAnalyzer/MuonPt.pdf");
  
    new TCanvas;
    histMuonEta->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/MuonEta.png");
    gPad->SaveAs("Plots_JetAnalyzer/MuonEta.pdf");

    new TCanvas;
    histMuonPhi->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/MuonPhi.png");
    gPad->SaveAs("Plots_JetAnalyzer/MuonPhi.pdf");



    new TCanvas;
    histDiMuonInvMass->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonInvMass.png");
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonInvMass.pdf");


    new TCanvas;
    histDiMuonInvMassLow->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonInvMassLow.png");
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonInvMassLow.pdf");



    new TCanvas;
    histDiMuonInvMassInt->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonInvMassInt.png");
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonInvMassInt.pdf");
  
  
    new TCanvas;
    gPad->SetLogy(1);
    histDiMuonPt->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonPt.png");
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonPt.pdf");

  
    new TCanvas;
    histDiMuonRapidity->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonRapidity.png");
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonRapidity.pdf");

    new TCanvas;
    histDiMuonPhi->Draw();
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonPhi.png");
    gPad->SaveAs("Plots_JetAnalyzer/DiMuonPhi.pdf");

    new TCanvas;
    histMuonJetDR->Draw();

    new TCanvas;
    histMuonJetDPhi->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histMuonJetPtTotal->Draw();
  
    new TCanvas;
    gPad->SetLogy(1);
    histMuonJetPtLight->Draw();
    new TCanvas;
    gPad->SetLogy(1);
    histMuonJetPtCharm->Draw();
    new TCanvas;
    gPad->SetLogy(1);
    histMuonJetPtBeauty->Draw();
    new TCanvas;
    gPad->SetLogy(1);
    histMuonJetPtGluon->Draw();

    new TCanvas;
    gPad->SetLogy(1);
    histPtHatBins->Draw();


    new TCanvas;
    gPad->SetLogy(1);
    histWPtHatBins->Draw();

  }//is_DrawPlots

  cout<<" Muon "<<histMuonPt->GetEntries()<<endl;
  cout<<" Gen Muon "<<histGenMuonPt->GetEntries()<<endl;
  
  // Write the histograms
  histPtHatBins->Write();
  histWPtHatBins->Write();

  histNumberOfGenJets->Write();
  histGenJetPt->Write();
  histGenJetEta->Write();
  histGenJetPhi->Write();

  histGenJetPtNoRec->Write();
  histGenJetPtUnknownRec->Write();

  histGenJetPtLight->Write();
  histGenJetPtUp->Write();
  histGenJetPtDown->Write();
  histGenJetPtStrange->Write();
  histGenJetPtCharm->Write();
  histGenJetPtBeauty->Write();
  histGenJetPtGluon->Write();


  hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi->Write();
  hist_GenMaster_RecoMuMatched_GenMuEta_GenMuPt_GenMuPhi->Write();
  histGenMuonPt->Write();
  histGenMuonEta->Write();
  histGenMuonPhi->Write();
  histGenDiMuonInvMass->Write();
  histGenDiMuonInvMassLow->Write();
  histGenDiMuonInvMassInt->Write();
  histGenDiMuonPt->Write();
  histGenDiMuonRapidity->Write();
  histGenDiMuonPhi->Write();

  histGenMuonGenJetDR->Write();
  histGenMuonGenJetDPhi->Write();
  histGenMuonGenJetPtTotal->Write();
  histGenMuonGenJetPtLight->Write();
  histGenMuonGenJetPtUp->Write();
  histGenMuonGenJetPtDown->Write();
  histGenMuonGenJetPtStrange->Write();
  histGenMuonGenJetPtCharm->Write();
  histGenMuonGenJetPtBeauty->Write();
  histGenMuonGenJetPtGluon->Write();



  hist_GenMaster_GenJetPt_Flavour->Write();
  hist_GenMaster_GenJetPt_Flavour_ProjX->Write();
  hist_GenMaster_GenJetPt_Flavour_ProjY->Write();

  hist_GenMaster_GenJetPt_GenMuPt_Flavour->Write();
  hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjX->Write();
  hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY->Write();
  hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->Write();
  
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour->Write();
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjX->Write();
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjY->Write();
  hist_GenMaster_GenJetPt_GenMuPtRel_Flavour_ProjZ->Write();

  
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi->Write();
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjX->Write();
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjY->Write();
  hist_GenMaster_GenJetMatched_GenMuEta_GenMuPt_GenMuPhi_ProjZ->Write();


  histNumberOfJets->Write();
  histJetPt->Write();
  histJetEta->Write();
  histJetPhi->Write();

  
  histJetPtUnknown->Write();
  histJetPtLight->Write();
  histJetPtUp->Write();
  histJetPtDown->Write();
  histJetPtStrange->Write();
  histJetPtCharm->Write();
  histJetPtBeauty->Write();
  histJetPtGluon->Write();


  //All the reconstructed muons passing the quality cuts
  histMuonPt->Write();
  histMuonEta->Write();
  histMuonPhi->Write();

  //matched reco muon variables (GenMu-RecMu dR < 0.4)
  histMatchedMuonPt->Write();
  histMatchedMuonEta->Write();
  histMatchedMuonPhi->Write();

  
  //matched gen muon variables (GenMu-RecMu dR < 0.4)
  histRecoMatchedGenMuonPt->Write();
  histRecoMatchedGenMuonEta->Write();
  histRecoMatchedGenMuonPhi->Write();


  histMuonIsGlobal->Write();
  histMuonIsTracker->Write();
  histMuonIsPF->Write();
  histMuonIsSTA->Write();
  histMuonD0->Write();
  histMuonDz->Write();
  histMuonChi2NDF->Write();
  histMuonInnerD0->Write();
  histMuonInnerD0Err->Write();
  histMuonInnerDz->Write();
  histMuonInnerDzErr->Write();
  histMuonInnerD0Norm->Write();
  histMuonInnerDzNorm->Write();
  histMuonTrkLayers->Write();
  histMuonPixelLayers->Write();
  histMuonPixelHits->Write();
  histMuonMuHits->Write();
  histMuonTrkQuality->Write();
  histMuonMuStations->Write();


  histNGMuonIsGlobal->Write();
  histNGMuonIsTracker->Write();
  histNGMuonIsPF->Write();
  histNGMuonIsSTA->Write();
  histNGMuonD0->Write();
  histNGMuonDz->Write();
  histNGMuonChi2NDF->Write();
  histNGMuonInnerD0->Write();
  histNGMuonInnerD0Err->Write();
  histNGMuonInnerDz->Write();
  histNGMuonInnerDzErr->Write();
  histNGMuonInnerD0Norm->Write();
  histNGMuonInnerDzNorm->Write();
  histNGMuonTrkLayers->Write();
  histNGMuonPixelLayers->Write();
  histNGMuonPixelHits->Write();
  histNGMuonMuHits->Write();
  histNGMuonTrkQuality->Write();
  histNGMuonMuStations->Write();











  histDiMuonInvMass->Write();
  histDiMuonInvMassLow->Write();
  histDiMuonInvMassInt->Write();
  histDiMuonPt->Write();
  histDiMuonRapidity->Write();
  histDiMuonPhi->Write();

  
  histGenMuRecMuDRVsDPt->Write();
  histGenMuRecMuDRVsPt->Write();
  histGenMuRecMuDRVsEta->Write();
  histGenMuRecMuDRVsPhi->Write();	  
    

  
  
  histMuonJetDR->Write();
  histMuonJetDPhi->Write();
  histMuonJetPtTotal->Write();
  histMuonJetPtLight->Write();
  histMuonJetPtUp->Write();
  histMuonJetPtDown->Write();
  histMuonJetPtStrange->Write();
  histMuonJetPtCharm->Write();
  histMuonJetPtBeauty->Write();
  histMuonJetPtGluon->Write();


  hist_Master_JetPt_Flavour->Write();
  hist_Master_JetPt_Flavour_ProjX->Write();
  hist_Master_JetPt_Flavour_ProjY->Write();

  hist_Master_JetPt_MuPt_Flavour->Write();
  hist_Master_JetPt_MuPt_Flavour_ProjX->Write();
  hist_Master_JetPt_MuPt_Flavour_ProjY->Write();
  hist_Master_JetPt_MuPt_Flavour_ProjZ->Write();



  hist_Master_JetPt_MuPtRel_Flavour->Write();
  hist_Master_JetPt_MuPtRel_Flavour_ProjX->Write();
  hist_Master_JetPt_MuPtRel_Flavour_ProjY->Write();
  hist_Master_JetPt_MuPtRel_Flavour_ProjZ->Write();


  
  hist_Master_MuEta_MuPt_MuPhi->Write();
  hist_Master_MuEta_MuPt_MuPhi_ProjX->Write();
  hist_Master_MuEta_MuPt_MuPhi_ProjY->Write();
  hist_Master_MuEta_MuPt_MuPhi_ProjZ->Write();

  
  histMatchedMuonsDR04Size->Write();
  histMatchedMuonsDR04Pt->Write();
  histMatchedMuonsDR04Eta->Write();
  histMatchedMuonsDR04Phi->Write();
  
  
   histJetCSV->Write();
   hist_Master_JetCSV_JetPt_Flavour->Write();
   
   histMuonJetCSV->Write();
   hist_Master_MuonJetCSV_MuonJetPt_Flavour->Write();
   hist_Master_JetCSV_MuPtRel_Flavour->Write();
   hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->Write();
   histMuonPtRel->Write();
   histMuonPtRelCSVTag->Write();
   histMuonPtRelCSVVeto->Write();

   
   
}//Loop



//=========================================================================//
//========== matching of generated and reconstructed muons ===============//
//=======================================================================//


double deltaR(TLorentzVector GenMuon, TLorentzVector RecoMuon)
{
  double dEta = RecoMuon.Eta() - GenMuon.Eta();
  double dPhi = TVector2::Phi_mpi_pi(RecoMuon.Phi() - GenMuon.Phi());
  return ((double) TMath::Sqrt( (dEta*dEta) + (dPhi*dPhi) ) );
};


double deltaPt(TLorentzVector GenMuon, TLorentzVector RecoMuon)
{
  double dPt = TMath::Abs(RecoMuon.Pt() - GenMuon.Pt());
  return dPt;
};




//bool isMatchedRecoDiMuon(int iRecoDiMuon, double maxDeltaR=0.03);








Double_t getDR( Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2){


  Double_t dphi = phi1 - phi2;
  
  if ( dphi > 3.141592653589 )
    dphi = dphi - 2. * 3.141592653589;
  if ( dphi <= -3.141592653589 )
    dphi = dphi + 2. * 3.141592653589;
  
  if ( TMath::Abs(dphi) > 3.141592653589 ) {
    cout << " commonUtility::getDR error!!! dphi is bigger than 3.141592653589 " << endl;
  }
  
  Double_t theDphi = dphi;
  Double_t theDeta = eta1 - eta2;

  return TMath::Sqrt ( theDphi*theDphi + theDeta*theDeta);
}

/*
Double_t getDPHI( Double_t phi1, Double_t phi2) {
  Double_t dphi = phi1 - phi2;
  
  if ( dphi > 3.141592653589 )
    dphi = dphi - 2. * 3.141592653589;
  if ( dphi <= -3.141592653589 )
    dphi = dphi + 2. * 3.141592653589;
  
  if ( TMath::Abs(dphi) > 3.141592653589 ) {
    cout << " commonUtility::getDPHI error!!! dphi is bigger than 3.141592653589 " << endl;
  }
  
  return dphi;
}
*/

Double_t plotDPHI( Double_t phi1, Double_t phi2) {


  Double_t dphi = phi1 - phi2;
  // Transform deltaPhis to interval [-pi/2,3pi/2]
  while(dphi > (1.5*TMath::Pi())){dphi += -2*TMath::Pi();}
  while(dphi < (-0.5*TMath::Pi())){dphi += 2*TMath::Pi();}

  return dphi;
}



Int_t SoftMuonIDCuts(Int_t isGlobal, Int_t isTracker, Int_t isGoodMuon, Int_t nPixWMea, Int_t nTrkWMea, float D0, float DZ){


  Int_t SelectMuon = 0;
  if( isGlobal==1 && isTracker==1 && isGoodMuon ==1 &&  nPixWMea > 0 &&  nTrkWMea > 5 && abs(D0)<0.3 && abs(DZ)<20.0){SelectMuon=1;}
  return SelectMuon;
  
  
}




Int_t TightMuonIDCuts(Int_t isGlobal, Int_t isTracker, float muEta, float muChi2NDF, float muInnerD0, float muInnerDz, Int_t muMuonHits, Int_t muStations, Int_t muTrkLayers, Int_t muPixelHits){
  Int_t SelectMuon =0;
  if( isGlobal==1 && isTracker==1 && TMath::Abs(muEta) < 2.4 &&  (muChi2NDF != -99 && muChi2NDF < 10) && TMath::Abs(muInnerD0) < 0.2 && TMath::Abs(muInnerDz) < 0.5
      && muMuonHits > 0 && muStations > 1 && muTrkLayers > 5 && muPixelHits > 0){SelectMuon =1;}
  return SelectMuon;
}



/*
 * Get the proper pT hat weighting for MC
 *
 *  Arguments:
 *   const Int_t ptHat = pT hat value in the event
 *
 *   return: Multiplicative correction factor for the given pT hat
 */

Double_t getPtHatWeight(const Double_t ptHat){
  const Int_t nBins = 12;
  Int_t correctionBinEdges[nBins] = {30, 50, 80, 100, 120, 170, 220, 280, 370, 460, 540, 3000};
  // Search the correct bin for the given pT hat value
  Int_t currentBin = -1;
  for(Int_t iBin = 0; iBin < nBins; iBin++){
    if(ptHat < correctionBinEdges[iBin]){
      currentBin = iBin;
      break;
    }
  }
 
  Double_t crossSections[nBins+1] = {5.335e-1,3.378e-2,3.778e-3,4.423e-4,1.511e-04,6.147e-5,1.018e-5,2.477e-6,6.160e-7,1.088e-7,2.537e-8, 1.001E-08,0.0}; // PYTHIA6 tune Z2
  //check for sigma 100 and 540 , currently 100 from old analysis and 540 from Pythia8
  Int_t PPMcEvents[nBins] = {  0, 444104  ,234388  ,90979  ,148860  , 216634  ,176028  ,115017  ,94247, 37777, 14413, 23073};
  return (crossSections[currentBin]-crossSections[currentBin+1])/PPMcEvents[currentBin];
}









Double_t getPtRel(Double_t MuonPt, Double_t MuonEta, Double_t MuonPhi, Double_t JetPt, Double_t JetEta, Double_t JetPhi)
{

  Double_t Muon_Px = MuonPt*TMath::Cos(MuonPhi);
  Double_t Muon_Py = MuonPt*TMath::Sin(MuonPhi);
  Double_t Muon_Pz = MuonPt*TMath::SinH(MuonEta);

  Double_t Jet_Px = JetPt*TMath::Cos(JetPhi);
  Double_t Jet_Py = JetPt*TMath::Sin(JetPhi);
  Double_t Jet_Pz = JetPt*TMath::SinH(JetEta);
  
  
  
  float lj_x = Jet_Px;
  float lj_y = Jet_Py;
  float lj_z = Jet_Pz;
  
  // absolute values squared
  float lj2  = lj_x*lj_x+lj_y*lj_y+lj_z*lj_z;
  
  //float lep2 = lep.px()*lep.px()+lep.py()*lep.py()+lep.pz()*lep.pz();
  float lep2 = Muon_Px*Muon_Px + Muon_Py*Muon_Py+Muon_Pz*Muon_Pz;
  
  
  // projection vec(mu) to lepjet axis
  float lepXlj = Muon_Px*lj_x+ Muon_Py*lj_y + Muon_Pz*lj_z;
  
  // absolute value squared and normalized
  float pLrel2 = lepXlj*lepXlj/lj2;
  float pTrel2 = lep2-pLrel2;

  return (pTrel2 > 0) ? std::sqrt(pTrel2) : 0.0;
}



