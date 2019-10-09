#define ReadSlimSkimData_cxx
#include "ReadSlimSkimData.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#ifndef __CINT__
#endif

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
#include "TObjArray.h"
#include "TGaxis.h"
#include "TLine.h"
#include "TLorentzVector.h"
#include "TEfficiency.h"

#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <algorithm>
#include <vector>

const Double_t MuonMass = 0.1056583745;
const Double_t Pi = TMath::Pi();

class CalculateDR{

 public:
  Double_t getDR( Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2){
    Double_t theDphi = getDPHI( phi1, phi2);
    Double_t theDeta = eta1 - eta2;
    return TMath::Sqrt ( theDphi*theDphi + theDeta*theDeta);
  }
  
  Double_t getDPHI( Double_t phi1, Double_t phi2) {
    Double_t dphi = phi1 - phi2;
    Double_t pi = TMath::Pi();
    if ( dphi > pi )
      dphi = dphi - 2. * pi;
    if ( dphi <= -pi )
      dphi = dphi + 2. * pi;
    
    if ( TMath::Abs(dphi) > pi ) {
      cout << " commonUtility::getDPHI error!!! dphi is bigger than 3.141592653589 " << endl;
    }
    return dphi;
  }
};

bool GiveMaxPt(TLorentzVector vec1, TLorentzVector vec2); 


Double_t plotDPHI( Double_t phi1, Double_t phi2);
Double_t getPtRel(Double_t MuonPt, Double_t MuonEta, Double_t MuonPhi, Double_t JetPt, Double_t JetEta, Double_t JetPhi);

Int_t SoftMuonIDCuts(Int_t isGlobal, Int_t isTracker, Int_t isGoodMuon, Int_t nPixWMea, Int_t nTrkWMea, float D0, float DZ);
Int_t TightMuonIDCuts(Int_t isGlobal, Int_t isTracker, float muEta, float muChi2NDF, float muInnerD0, float muInnerDz, Int_t muMuonHits, Int_t muStations, Int_t muTrkLayers, Int_t muPixelHits);



void FlavouredHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize);


TH1D *RatioHistogram(TH1 *InHistNum, TH1 *InHistDeno, Int_t RebinFac);



/*
ReadSlimSkimData::ReadSlimSkimData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("InSkimFile/ReReco_PbPb_5TeV_Data_skim0000_All.root");
      if (!f || !f->IsOpen()) {
	f = new TFile("InSkimFile/ReReco_PbPb_5TeV_Data_skim0000_All.root");
      }
      f->GetObject("mixing_tree",tree);

   }
   Init(tree);
}
*/


						  
ReadSlimSkimData::ReadSlimSkimData(TTree *tree) : fChain(0) 
{


  TChain *chain = new TChain("mixing_tree");
  /*
  //These files does not have full stat.
  // file 0001 and 0002 have problem where three trees are generated 
  //per file by mistake
  chain->Add("InSkimFile/ReReco_PbPb_5TeV_Data_skim0000_All.root");
  chain->Add("InSkimFile/ReReco_PbPb_5TeV_Data_skim0001_17May19_All.root");
  chain->Add("InSkimFile/ReReco_PbPb_5TeV_Data_skim0002_17May19_All.root");
  */
  
  //************ Super Slim Skim for Single Muon Data Set (Single Muon Pt 13 Trigger) *************************//
  //chain->Add("/data/vineet/SingleMuonTrigger2018PbPbDataSkim/ReReco_PbPb_5TeV_Data_skim0000_All.root");
  //chain->Add("/data/vineet/SingleMuonTrigger2018PbPbDataSkim/ReReco_PbPb_5TeV_Data_skim0001_17May19_All.root");
  //chain->Add("/data/vineet/SingleMuonTrigger2018PbPbDataSkim/ReReco_PbPb_5TeV_Data_skim0002_17May19_All.root");

  //************ Supre Slim Skim for HardProbe Data Set ~90% Stat *************************//
  //chain->Add("/data/vineet/JetTrigger2018PbPbHPDataSkim/PbPbData_HP_SuperSlimSkim_0001_All.root");
  //chain->Add("/data/vineet/JetTrigger2018PbPbHPDataSkim/PbPbData_HP_SuperSlimSkim_0002_All.root");
  //chain->Add("/data/vineet/JetTrigger2018PbPbHPDataSkim/PbPbData_HP_SuperSlimSkim_0003_All.root");
  //chain->Add("/data/vineet/JetTrigger2018PbPbHPDataSkim/PbPbData_HP_SuperSlimSkim_0004_All.root");
  //chain->Add("/data/vineet/JetTrigger2018PbPbHPDataSkim/PbPbData_HP_SuperSlimSkim_0005_All.root");
  //chain->Add("/data/vineet/JetTrigger2018PbPbHPDataSkim/PbPbData_HP_SuperSlimSkim_0006_All.root");
  //chain->Add("/data/vineet/JetTrigger2018PbPbHPDataSkim/PbPbData_HP_SuperSlimSkim_0007_All.root");

  //************ Supre Slim Skim for HardProbe Data Set Muon+Jet Trigger **********************//
  //chain->Add("/data/vineet/MuonJetTrigger2018PbPbHPDataSkim/PbPbData_HP_MuJetTrigger_SuperSlimSkim_0000_16July2019_All.root");
  //chain->Add("/data/vineet/MuonJetTrigger2018PbPbHPDataSkim/PbPbData_HP_MuJetTrigger_SuperSlimSkim_0001_16July2019_All.root");
  //chain->Add("/data/vineet/MuonJetTrigger2018PbPbHPDataSkim/PbPbData_HP_MuJetTrigger_SuperSlimSkim_0002_16July2019_All.root");

  //************ Super Slim Skim for Single Muon Data Set Muon+Jet Trigger **********************//
  //chain->Add("/data/vineet/MuonJetTrigger2018PbPbSingleMuPDSkim/PbPb_5TeV_SingleMuPD_MuJetTrigger_SuperSlimSkim_21Aug2019.root");


  //************ PP2017 Data: Super Slim Skim for Single Muon Data Set Muon+Jet Trigger **********************//
  chain->Add("/data/vineet/MuonJetTrigger2017PPDataSingleMuPDSkim/PPData_5TeV_SingleMuPD_MuJetTrigger_SuperSlimSkim_27Aug2019.root");

  Init(chain);
}



void ReadSlimSkimData::Loop()
{

  //gStyle->SetPalette(kRainBow);
  TH1::SetDefaultSumw2(1);

  //fStyle2D("colz");
  //fStyle3D("surf1");
    
    //   In a ROOT session, you can do:
    //      root> .L ReadSlimSkimData.C
    //      root> ReadSlimSkimData t
    //      root> t.GetEntry(12); // Fill t data members with entry number 12
    //      root> t.Show();       // Show values of entry 12
    //      root> t.Show(16);     // Read and show values of entry 16
    //      root> t.Loop();       // Loop on all entries
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
    if (fChain == 0) return;
  
    const int DEBUG_MODE = 0;
    const int DO_TRACK = 0;
    const int DO_TRACK_JET_CORR = 0;
  
  TFile *OutFile = new TFile("PP2017Data_HLT_MuonJet30_JetPtMin60_JetEtaMax2_MuEtaMax24_MuPtMin5_JetQualityOn_09Oct2019.root","RECREATE");
  
  //============== Basic Event Level Histo ============================//
  // Centrality
  const Double_t minCentrality = -0.75;   // Minimum centrality bin, is negative since hiBin is -1 for pp
  const Double_t maxCentrality = 100.25;  // Maximum centrality bin
  const Int_t nCentralityBins = 202;      // Number of centrality bins

  TH1D *histCentrality= new TH1D("histCentrality","histCentrality", nCentralityBins,minCentrality,maxCentrality);
  histCentrality->GetXaxis()->SetTitle("Centrality");
  histCentrality->GetYaxis()->SetTitle("Entries");


  TH1D *histEvtVtxX= new TH1D("histEvtVtxX","histEvtVtxX",200,-1.0,1.0);
  histEvtVtxX->GetXaxis()->SetTitle("EvtVtxX");
  histEvtVtxX->GetYaxis()->SetTitle("Entries");


  TH1D *histEvtVtxY= new TH1D("histEvtVtxY","histEvtVtxY",200,-1.0,1.0);
  histEvtVtxY->GetXaxis()->SetTitle("EvtVtxY");
  histEvtVtxY->GetYaxis()->SetTitle("Entries");

  TH1D *histEvtVtxZ= new TH1D("histEvtVtxZ","histEvtVtxZ",300,-30.0,30.0);
  histEvtVtxZ->GetXaxis()->SetTitle("EvtVtxZ");
  histEvtVtxZ->GetYaxis()->SetTitle("Entries");

  //============== Jet Histogram =======================================//
  Int_t NBinsJetPt =500;
  Double_t JetPtMin =0.0;
  Double_t JetPtMax = 500.0;
    
  Int_t NBinsJetEta = 200;
  Double_t JetEtaMin = -3.0;
  Double_t JetEtaMax = 3.0;
  

  Int_t NBinsJetPhi = 200;
  Double_t JetPhiMin = -Pi;
  Double_t JetPhiMax = Pi;

  
  TH1D *histJetPt= new TH1D("histJetPt","histJetPt",NBinsJetPt,JetPtMin,JetPtMax);
  histJetPt->GetXaxis()->SetTitle("Jet Pt (GeV/c)");
  histJetPt->GetYaxis()->SetTitle("Entries");
  
  TH1D *histJetEta = new TH1D("histJetEta","histJetEta",NBinsJetEta,JetEtaMin,JetEtaMax);
  histJetEta->GetXaxis()->SetTitle("Jet #eta");
  histJetEta->GetYaxis()->SetTitle("Entries");
  
  TH1D *histJetPhi = new TH1D("histJetPhi","histJetPhi",NBinsJetPhi,JetPhiMin,JetPhiMax);
  histJetPhi->GetXaxis()->SetTitle("Jet #phi");
  histJetPhi->GetYaxis()->SetTitle("Entries");
  
   
  TH1D *histPfTrackMax_AllJets= new TH1D("histPfTrackMax_AllJets","histPfTrackMax_AllJets",100,0,2);
  histPfTrackMax_AllJets->GetXaxis()->SetTitle("Pf Track Max / Jet Pt");
  histPfTrackMax_AllJets->GetYaxis()->SetTitle("Entries");


  TH1D *histPfTrackMax= new TH1D("histPfTrackMax","histPfTrackMax",100,0,2);
  histPfTrackMax->GetXaxis()->SetTitle("Pf Track Max / Jet Pt");
  histPfTrackMax->GetYaxis()->SetTitle("Entries");

  
  TH3D *hist_Master_JetEta_JetPt_JetPhi = new TH3D("hist_Master_JetEta_JetPt_JetPhi","hist_Master_JetEta_JetPt_JetPhi",NBinsJetEta,JetEtaMin,JetEtaMax,NBinsJetPt,JetPtMin,JetPtMax,NBinsJetPhi,JetPhiMin,JetPhiMax);
  
  hist_Master_JetEta_JetPt_JetPhi->GetXaxis()->SetTitle(" Jet #eta");
  hist_Master_JetEta_JetPt_JetPhi->GetYaxis()->SetTitle(" Jet p_{T} (GeV/c)");
  hist_Master_JetEta_JetPt_JetPhi->GetZaxis()->SetTitle(" Jet #phi");


  TH3D *hist_Master_EventCentrality_JetEta_JetPt = new TH3D("hist_Master_EventCentrality_JetEta_JetPt","hist_Master_EventCentrality_JetEta_JetPt", nCentralityBins,minCentrality,maxCentrality,NBinsJetEta,JetEtaMin,JetEtaMax,NBinsJetPt,JetPtMin,JetPtMax);
  
  hist_Master_EventCentrality_JetEta_JetPt->GetXaxis()->SetTitle("Event Centrality");
  hist_Master_EventCentrality_JetEta_JetPt->GetYaxis()->SetTitle("Jet #eta");
  hist_Master_EventCentrality_JetEta_JetPt->GetZaxis()->SetTitle("Jet p_{T} (GeV/c)");


  const Int_t NBinsJetCSV =100;
  const Double_t JetCSVMin =0.0;
  const Double_t JetCSVMax =1.2;


  TH3D *hist_Master_EventCentrality_JetCSV_JetPt = new TH3D("hist_Master_EventCentrality_JetCSV_JetPt","hist_Master_EventCentrality_JetCSV_JetPt", nCentralityBins,minCentrality,maxCentrality, NBinsJetCSV, JetCSVMin, JetCSVMax, NBinsJetPt, JetPtMin, JetPtMax);
  hist_Master_EventCentrality_JetCSV_JetPt->GetXaxis()->SetTitle("Centrality (%)");
  hist_Master_EventCentrality_JetCSV_JetPt->GetYaxis()->SetTitle("Jet CSV v2");
  hist_Master_EventCentrality_JetCSV_JetPt->GetZaxis()->SetTitle("Jet p_{T} (GeV/c)");


  
  Int_t NBinsMuonPt = 150;
  Double_t MuonPtMin = 0.0;
  Double_t MuonPtMax = 150.0;
  
  Int_t NBinsMuonEta = 200;
  Double_t MuonEtaMin = -3.0;
  Double_t MuonEtaMax = 3.0;
  
  Int_t NBinsMuonPhi = 200;
  Double_t MuonPhiMin = -Pi;
  Double_t MuonPhiMax = Pi;
  

  TH1D *histMuonPt = new TH1D("histMuonPt","histMuonPt",NBinsMuonPt,MuonPtMin,MuonPtMax);
  histMuonPt->GetXaxis()->SetTitle("Muon Pt (GeV/c)");
  histMuonPt->GetYaxis()->SetTitle("Entries");


  TH1D *histMatchedMuonPt_StMuons = new TH1D("histMatchedMuonPt_StMuons","histMatchedMuonPt_StMuons",NBinsMuonPt,MuonPtMin,MuonPtMax);
  histMatchedMuonPt_StMuons->GetXaxis()->SetTitle("Matched Muon Pt (GeV/c)");
  histMatchedMuonPt_StMuons->GetYaxis()->SetTitle("Entries");
  
  
  
  TH1D *histMuonEta = new TH1D("histMuonEta","histMuonEta",NBinsMuonEta,MuonEtaMin,MuonEtaMax);
  histMuonEta->GetXaxis()->SetTitle("Muon #eta (GeV/c)");
  histMuonEta->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histMuonPhi = new TH1D("histMuonPhi","histMuonPhi",NBinsMuonPhi,MuonPhiMin,MuonPhiMax);
  histMuonPhi->GetXaxis()->SetTitle("Muon #phi (GeV/c)");
  histMuonPhi->GetYaxis()->SetTitle("Entries");
  

  TH3D *hist_Master_EventCentrality_MuonEta_MuonPt = new TH3D("hist_Master_EventCentrality_MuonEta_MuonPt","hist_Master_EventCentrality_MuonEta_MuonPt", nCentralityBins,minCentrality,maxCentrality,NBinsMuonEta,MuonEtaMin,MuonEtaMax,NBinsMuonPt,MuonPtMin,MuonPtMax);
  
  hist_Master_EventCentrality_MuonEta_MuonPt->GetXaxis()->SetTitle("Event Centrality");
  hist_Master_EventCentrality_MuonEta_MuonPt->GetYaxis()->SetTitle("Muon #eta");
  hist_Master_EventCentrality_MuonEta_MuonPt->GetZaxis()->SetTitle("Muon p_{T} (GeV/c)");



  
  TH3D *hist_Master_MuonEta_MuonPt_MuonPhi_StJet = new TH3D("hist_Master_MuonEta_MuonPt_MuonPhi_StJet","hist_Master_MuonEta_MuonPt_MuonPhi_StJet",NBinsMuonEta,MuonEtaMin,MuonEtaMax,NBinsMuonPt,MuonPtMin,MuonPtMax,NBinsMuonPhi,MuonPhiMin,MuonPhiMax);
  hist_Master_MuonEta_MuonPt_MuonPhi_StJet->GetXaxis()->SetTitle(" Muon #eta");
  hist_Master_MuonEta_MuonPt_MuonPhi_StJet->GetYaxis()->SetTitle(" Muon p_{T} (GeV/c)");
  hist_Master_MuonEta_MuonPt_MuonPhi_StJet->GetZaxis()->SetTitle(" Muon #phi");

  
  //Delta R starting from Jet
  //This gives number of Jets those have muons inside (only tightest muon)
  TH3D *hist_Master_EventCentrality_JetPt_MuonPt = new TH3D("hist_Master_EventCentrality_JetPt_MuonPt","hist_Master_EventCentrality_JetPt_MuonPt", nCentralityBins,minCentrality,maxCentrality,NBinsJetPt,JetPtMin,JetPtMax,NBinsMuonPt,MuonPtMin,MuonPtMax);
  hist_Master_EventCentrality_JetPt_MuonPt->GetXaxis()->SetTitle("Event Centrality");
  hist_Master_EventCentrality_JetPt_MuonPt->GetYaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_Master_EventCentrality_JetPt_MuonPt->GetZaxis()->SetTitle("Muon p_{T} (GeV/c)");
  

  
  //Delta R starting from muon
  //This gives number of muons those are inside jets (all the muons)
  TH3D *hist_Master_EventCentrality_MuonPt_JetPt = new TH3D("hist_Master_EventCentrality_MuonPt_JetPt","hist_Master_EventCentrality_MuonPt_JetPt", nCentralityBins,minCentrality,maxCentrality,NBinsMuonPt,MuonPtMin,MuonPtMax,NBinsJetPt,JetPtMin,JetPtMax);
  hist_Master_EventCentrality_MuonPt_JetPt->GetXaxis()->SetTitle("Event Centrality");
  hist_Master_EventCentrality_MuonPt_JetPt->GetYaxis()->SetTitle("Muon p_{T} (GeV/c)");
  hist_Master_EventCentrality_MuonPt_JetPt->GetZaxis()->SetTitle("Jet p_{T} (GeV/c)");

  
  TH1D *histMuonJetDR = new TH1D("histMuonJetDR","histMuonJetDR",100,0,10);
  histMuonJetDR->GetXaxis()->SetTitle("Muon-Jet #Delta R");
  histMuonJetDR->GetYaxis()->SetTitle("Entries");

  //const Int_t NBinsMuonPtRel = 100;
  //const Double_t MuonPtRelMin = 0.0;
  //const Double_t MuonPtRelMax = 30.0;

  const Int_t NBinsMuonPtRel = 40;
  const Double_t MuonPtRelMin = 0.0;
  const Double_t MuonPtRelMax = 4.0;

  TH3D *hist_Master_JetCSV_JetPt_MuonPtRel = new TH3D("hist_Master_JetCSV_JetPt_MuonPtRel","hist_Master_JetCSV_JetPt_MuonPtRel", NBinsJetCSV, JetCSVMin, JetCSVMax, NBinsJetPt, JetPtMin, JetPtMax,NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  hist_Master_JetCSV_JetPt_MuonPtRel->GetXaxis()->SetTitle("Jet CSV v2");
  hist_Master_JetCSV_JetPt_MuonPtRel->GetYaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_Master_JetCSV_JetPt_MuonPtRel->GetZaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");


  TH3D *hist_Master_JetCSV_JetPt_MuonPt = new TH3D("hist_Master_JetCSV_JetPt_MuonPt","hist_Master_JetCSV_JetPt_MuonPt", NBinsJetCSV, JetCSVMin, JetCSVMax, NBinsJetPt, JetPtMin, JetPtMax,NBinsMuonPt,MuonPtMin,MuonPtMax);
  hist_Master_JetCSV_JetPt_MuonPt->GetXaxis()->SetTitle("Jet CSV v2");
  hist_Master_JetCSV_JetPt_MuonPt->GetYaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_Master_JetCSV_JetPt_MuonPt->GetZaxis()->SetTitle("Muon p_{T} (GeV/c)");

  TH3D *hist_Master_EventCentrality_MuonJetCSV_MuonJetPt = new TH3D("hist_Master_EventCentrality_MuonJetCSV_MuonJetPt","hist_Master_EventCentrality_MuonJetCSV_MuonJetPt", nCentralityBins,minCentrality,maxCentrality, NBinsJetCSV, JetCSVMin, JetCSVMax, NBinsJetPt, JetPtMin, JetPtMax);
  hist_Master_EventCentrality_MuonJetCSV_MuonJetPt->GetXaxis()->SetTitle("Centrality (%)");
  hist_Master_EventCentrality_MuonJetCSV_MuonJetPt->GetYaxis()->SetTitle("Muon Jet CSV v2");
  hist_Master_EventCentrality_MuonJetCSV_MuonJetPt->GetZaxis()->SetTitle("Muon Jet p_{T} (GeV/c)");



  TH1D *histMuonPtRel = new TH1D("histMuonPtRel","histMuonPtRel",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  histMuonPtRel->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  histMuonPtRel->GetYaxis()->SetTitle("Entries");

  TH1D *histMuonPtRelCSVTag = new TH1D("histMuonPtRelCSVTag","histMuonPtRelCSVTag",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  histMuonPtRelCSVTag->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  histMuonPtRelCSVTag->GetYaxis()->SetTitle("Entries");


  TH1D *histMuonPtRelCSVVeto = new TH1D("histMuonPtRelCSVVeto","histMuonPtRelCSVVeto",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  histMuonPtRelCSVVeto->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  histMuonPtRelCSVVeto->GetYaxis()->SetTitle("Entries");


  TH1D *histJetCSV = new TH1D("histJetCSV","histJetCSV",NBinsJetCSV,JetCSVMin,JetCSVMax);
  histJetCSV->GetXaxis()->SetTitle("Jet CSV v2");
  histJetCSV->GetXaxis()->SetTitle("Entries");
  


  TH1D *histMuonJetCSV = new TH1D("histMuonJetCSV","histMuonJetCSV",NBinsJetCSV,JetCSVMin,JetCSVMax);
  histMuonJetCSV->GetXaxis()->SetTitle("Muon Jet CSV v2");
  histMuonJetCSV->GetXaxis()->SetTitle("Entries");



  //======================================================================================================================//
  //============ Dimuon Histograms  =======================================================================================//
  //============ Main purpose of these is to check Z0 mass in barrel and endcap ===========================================//
  //======================================================================================================================//

  TH1D *histDiMuonInvMass = new TH1D("histDiMuonInvMass","histDiMuonInvMass",500,0,150);
  histDiMuonInvMass->GetXaxis()->SetTitle("DiMuon InvMass (GeV/c)");
  histDiMuonInvMass->GetYaxis()->SetTitle("Entries");


  TH1D *histDiMuonInvMassLow = new TH1D("histDiMuonInvMassLow","histDiMuonInvMassLow",200,2.0,4.5);
  histDiMuonInvMassLow->GetXaxis()->SetTitle("DiMuon InvMassLow (GeV/c)");
  histDiMuonInvMassLow->GetYaxis()->SetTitle("Entries");


  TH1D *histDiMuonInvMassInt = new TH1D("histDiMuonInvMassInt","histDiMuonInvMassInt",200,8.0,14.0);
  histDiMuonInvMassInt->GetXaxis()->SetTitle("DiMuon InvMassInt (GeV/c)");
  histDiMuonInvMassInt->GetYaxis()->SetTitle("Entries");

  TH1D *histDiMuonInvMassHighMid = new TH1D("histDiMuonInvMassHighMid","histDiMuonInvMassHighMid",200,60.0,120.0);
  histDiMuonInvMassHighMid->GetXaxis()->SetTitle("DiMuon InvMassHighMid (GeV/c)");
  histDiMuonInvMassHighMid->GetYaxis()->SetTitle("Entries");

  TH1D *histDiMuonInvMassHighFwd = new TH1D("histDiMuonInvMassHighFwd","histDiMuonInvMassHighFwd",200,60.0,120.0);
  histDiMuonInvMassHighFwd->GetXaxis()->SetTitle("DiMuon InvMassHighFwd (GeV/c)");
  histDiMuonInvMassHighFwd->GetYaxis()->SetTitle("Entries");
 


  TH1D *histDiMuonInvMassHighSSMid = new TH1D("histDiMuonInvMassHighSSMid","histDiMuonInvMassHighSSMid",200,60.0,120.0);
  histDiMuonInvMassHighSSMid->GetXaxis()->SetTitle("DiMuon InvMassHighSSMid (GeV/c)");
  histDiMuonInvMassHighSSMid->GetYaxis()->SetTitle("Entries");

  TH1D *histDiMuonInvMassHighSSFwd = new TH1D("histDiMuonInvMassHighSSFwd","histDiMuonInvMassHighSSFwd",200,60.0,120.0);
  histDiMuonInvMassHighSSFwd->GetXaxis()->SetTitle("DiMuon InvMassHighSSFwd (GeV/c)");
  histDiMuonInvMassHighSSFwd->GetYaxis()->SetTitle("Entries");
 

  TH1D *histDiMuonPt = new TH1D("histDiMuonPt","histDiMuonPt",100,0,100);
  histDiMuonPt->GetXaxis()->SetTitle("DiMuon Pt (GeV/c)");
  histDiMuonPt->GetYaxis()->SetTitle("Entries");

  TH1D *histDiMuonRapidity = new TH1D("histDiMuonRapidity","histDiMuonRapidity",100,-5,5);
  histDiMuonRapidity->GetXaxis()->SetTitle("DiMuon #eta (GeV/c)");
  histDiMuonRapidity->GetYaxis()->SetTitle("Entries");


  TH1D *histDiMuonPhi = new TH1D("histDiMuonPhi","histDiMuonPhi",100,-Pi,Pi);
  histDiMuonPhi->GetXaxis()->SetTitle("DiMuon #phi (GeV/c)");
  histDiMuonPhi->GetYaxis()->SetTitle("Entries");

  
  
  //DeltaPhi
  const Double_t minDeltaPhiJetMuon = -TMath::Pi()/2.0;    // Minimum deltaPhi for jet-muon 
  const Double_t maxDeltaPhiJetMuon = 3.0*TMath::Pi()/2.0; // Maximum deltaPhi for jet-muon 
  const Int_t nDeltaPhiBinsJetMuon = 200;                  // Number of deltaPhi bins for jet-muon  (match the common number in UIC group)
  
  
  // DeltaEta
  const Double_t minDeltaEtaJetMuon = -5.0;   // Minimum deltaEta for jet-muon 
  const Double_t maxDeltaEtaJetMuon = 5.0;    // Maximum deltaEta for jet-muon 
  const Int_t nDeltaEtaBinsJetMuon = 500;     // Number of deltaEta bins for jet-muon  (match the common number in UIC group)
  


  TH1D *histMuonJetDPhi = new TH1D("histMuonJetDPhi","histMuonJetDPhi",nDeltaPhiBinsJetMuon,minDeltaPhiJetMuon,maxDeltaPhiJetMuon);
  histMuonJetDPhi->GetXaxis()->SetTitle("Muon-Jet #Delta #Phi");
  histMuonJetDPhi->GetYaxis()->SetTitle("Entries");

  
  TH1D *histMuonJetDEta = new TH1D("histMuonJetDEta","histMuonJetDEta",nDeltaEtaBinsJetMuon,minDeltaEtaJetMuon,maxDeltaEtaJetMuon);
  histMuonJetDEta->GetXaxis()->SetTitle("Muon-Jet #Delta #eta");
  histMuonJetDEta->GetYaxis()->SetTitle("Entries");



  TH2D *histMuonJetDEtaDPhi = new TH2D("histMuonJetDEtaDPhi","histMuonJetDEtaDPhi",nDeltaEtaBinsJetMuon,minDeltaEtaJetMuon,maxDeltaEtaJetMuon,nDeltaPhiBinsJetMuon,minDeltaPhiJetMuon,maxDeltaPhiJetMuon);
  histMuonJetDEtaDPhi->GetXaxis()->SetTitle("Muon-Jet #Delta #eta");
  histMuonJetDEtaDPhi->GetYaxis()->SetTitle("Muon-Jet #Delta #phi");
  histMuonJetDEtaDPhi->GetZaxis()->SetTitle("Entries");

  
  TH1D *histMuonJetPt = new TH1D("histMuonJetPt","histMuonJetPt",NBinsJetPt,JetPtMin,JetPtMax);
  histMuonJetPt->GetXaxis()->SetTitle("Muon Jet Pt (GeV/c)");
  histMuonJetPt->GetYaxis()->SetTitle("Entries");

  
  //==============================================================================================//
  //============================= Muon Quality Cut Histograms ====================================//
  //==============================================================================================//
  //================= Not required right now ====================//


  Int_t NBinsTrackEta = 100;
  Double_t TrackEtaMin = -3.0;
  Double_t TrackEtaMax = 3.0;
  
  Int_t NBinsTrackPt = 100;
  Double_t TrackPtMin = 0.0;
  Double_t TrackPtMax = 100.0;
  
  Int_t NBinsTrackPhi = 100;
  Double_t TrackPhiMin = -Pi;
  Double_t TrackPhiMax = Pi;

  
  
  TH3D *hist_Master_TrackEta_TrackPt_TrackPhi = new TH3D("hist_Master_TrackEta_TrackPt_TrackPhi","hist_Master_TrackEta_TrackPt_TrackPhi",NBinsTrackEta,TrackEtaMin,TrackEtaMax,NBinsTrackPt,TrackPtMin,TrackPtMax,NBinsTrackPhi,TrackPhiMin,TrackPhiMax);
  hist_Master_TrackEta_TrackPt_TrackPhi->GetXaxis()->SetTitle(" Track #eta");
  hist_Master_TrackEta_TrackPt_TrackPhi->GetYaxis()->SetTitle(" Track p_{T} (GeV/c)");
  hist_Master_TrackEta_TrackPt_TrackPhi->GetZaxis()->SetTitle(" Track #phi");
  

  TH1D *histTrackPt = new TH1D("histTrackPt","histTrackPt",NBinsTrackPt,TrackPtMin,TrackPtMax);
  histTrackPt->GetXaxis()->SetTitle("Track Pt (GeV/c)");
  histTrackPt->GetYaxis()->SetTitle("Entries");
  
  
  
  TH1D *histTrackEta = new TH1D("histTrackEta","histTrackEta",NBinsTrackEta,TrackEtaMin,TrackEtaMax);
  histTrackEta->GetXaxis()->SetTitle("Track #eta (GeV/c)");
  histTrackEta->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histTrackPhi = new TH1D("histTrackPhi","histTrackPhi",NBinsTrackPhi,TrackPhiMin,TrackPhiMax);
  histTrackPhi->GetXaxis()->SetTitle("Track #phi (GeV/c)");
  histTrackPhi->GetYaxis()->SetTitle("Entries");


  TH1D *histTrackJetDR = new TH1D("histTrackJetDR","histTrackJetDR",100,0,10);
  histTrackJetDR->GetXaxis()->SetTitle("Track-Jet #Delta R");
  histTrackJetDR->GetYaxis()->SetTitle("Entries");

  
  TH1D *histTrackJetDPhi = new TH1D("histTrackJetDPhi","histTrackJetDPhi",200,-Pi,Pi);
  histTrackJetDPhi->GetXaxis()->SetTitle("Track-Jet #Delta #Phi");
  histTrackJetDPhi->GetYaxis()->SetTitle("Entries");



  //DeltaPhi
  const Double_t minDeltaPhiJetTrack = -TMath::Pi()/2.0;    // Minimum deltaPhi for jet-muon 
  const Double_t maxDeltaPhiJetTrack = 3.0*TMath::Pi()/2.0; // Maximum deltaPhi for jet-muon 
  const Int_t nDeltaPhiBinsJetTrack = 200;                  // Number of deltaPhi bins for jet-muon  (match the common number in UIC group)
  
  
  // DeltaEta
  const Double_t minDeltaEtaJetTrack = -5.0;   // Minimum deltaEta for jet-muon 
  const Double_t maxDeltaEtaJetTrack = 5.0;    // Maximum deltaEta for jet-muon 
  const Int_t nDeltaEtaBinsJetTrack = 500;     // Number of deltaEta bins for jet-muon  (match the common number in UIC group)
  

  
  TH1D *histTrackJetDEta = new TH1D("histTrackJetDEta","histTrackJetDEta",nDeltaEtaBinsJetTrack,minDeltaEtaJetTrack,maxDeltaEtaJetTrack);
  histTrackJetDEta->GetXaxis()->SetTitle("Track-Jet #Delta #eta");
  histTrackJetDEta->GetYaxis()->SetTitle("Entries");



  TH2D *histTrackJetDEtaDPhi = new TH2D("histTrackJetDEtaDPhi","histTrackJetDEtaDPhi",nDeltaEtaBinsJetTrack,minDeltaEtaJetTrack,maxDeltaEtaJetTrack,nDeltaPhiBinsJetTrack,minDeltaPhiJetTrack,maxDeltaPhiJetTrack);
  histTrackJetDEtaDPhi->GetXaxis()->SetTitle("Track-Jet #Delta #eta");
  histTrackJetDEtaDPhi->GetYaxis()->SetTitle("Track-Jet #Delta #phi");
  histTrackJetDEtaDPhi->GetZaxis()->SetTitle("Entries");

  const Int_t NBinsMatchedMuonsDR04Size = 12;
  Double_t MatchedMuonsDR04SizeMin = 0.5;
  Double_t MatchedMuonsDR04SizeMax = 12.5;

  TH1D *histMatchedMuonsDR04Size = new TH1D("histMatchedMuonsDR04Size","histMatchedMuonsDR04Size", NBinsMatchedMuonsDR04Size,MatchedMuonsDR04SizeMin,MatchedMuonsDR04SizeMax);
  histMatchedMuonsDR04Size->GetXaxis()->SetTitle("MatchedMuonsDR04 Pt (GeV/c)");
  histMatchedMuonsDR04Size->GetYaxis()->SetTitle("Entries");


  TH1D *histMatchedMuonsDR04Pt = new TH1D("histMatchedMuonsDR04Pt","histMatchedMuonsDR04Pt",NBinsMuonPt,MuonPtMin,MuonPtMax);
  histMatchedMuonsDR04Pt->GetXaxis()->SetTitle("MatchedMuonsDR04 Pt (GeV/c)");
  histMatchedMuonsDR04Pt->GetYaxis()->SetTitle("Entries");
  
  TH1D *histMatchedMuonsDR04Eta = new TH1D("histMatchedMuonsDR04Eta","histMatchedMuonsDR04Eta",NBinsMuonEta,MuonEtaMin,MuonEtaMax);
  histMatchedMuonsDR04Eta->GetXaxis()->SetTitle("MatchedMuonsDR04 #eta (GeV/c)");
  histMatchedMuonsDR04Eta->GetYaxis()->SetTitle("Entries");
  
  
  TH1D *histMatchedMuonsDR04Phi = new TH1D("histMatchedMuonsDR04Phi","histMatchedMuonsDR04Phi",NBinsMuonPhi,MuonPhiMin,MuonPhiMax);
  histMatchedMuonsDR04Phi->GetXaxis()->SetTitle("MatchedMuonsDR04 #phi (GeV/c)");
  histMatchedMuonsDR04Phi->GetYaxis()->SetTitle("Entries");


  Long64_t nentries = fChain->GetEntriesFast();
  //Long64_t nentries = fChain->GetEntries();
  
  //Double_t Temp_Ent = 4879437; //to print the % of remaining events, for HISingleMuon Dataset
  //Double_t Temp_Ent = 5400655; //to print the % of remaining events, for HIHardProbe PD, CaloJet100Trigger, ~90% stat
  //Double_t Temp_Ent =   1276763; //to print the % of remaining events, for HIHardProbe PD, MuonJet Trigger

  Double_t Temp_Ent =   59200000; //to print the % of remaining events, for PP 2017 Data HISingleMu PD, MuonJet Trigger
  

  cout<< nentries <<" entries in "<< fChain->GetName()<<endl;

  //return;
  //nentries=1000;
   
  Int_t PrintEv = 200000;

  //Long64_t nbytes = 0, nb = 0;
  
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
      
     
     fChain->GetEntry(jentry);
     
     if(jentry%PrintEv ==0)
       {
	 cout<<" Event "<< jentry <<" / "<< Temp_Ent <<"    "<< (jentry/Temp_Ent)*100.0 << " % Done"<<endl;
	 
	 cout<< "  number of Tracks    : "<<trkPt->size()<<endl;
	 cout<<endl;
	 cout<< "  number of PF Jets   : "<<pf_jtpt->size()<<endl;
	 cout<<endl;
	 cout<< "  number of Calo Jets : "<< calo_jtpt->size()<<endl;
	 cout<< "  number of Muons     : "<<mu_pt->size()<<endl;
	 cout<<endl<<endl;
       }


     //================ Fill Event Level Histograms =========================//
     Double_t EventCentrality = hiBin/2.0;

     histCentrality->Fill(EventCentrality);
     histEvtVtxX->Fill(vx);
     histEvtVtxY->Fill(vy);
     histEvtVtxZ->Fill(vz);
     
     Double_t MuonPtMin =5.0;
     Double_t MuonEtaMax =2.4;
     
     //reco mu loop
     //This is a vector of lorentz vector
     std::vector<TLorentzVector> MuonsForJets;
     
     std::vector<TLorentzVector> PositiveMuons;
     std::vector<TLorentzVector> NegativeMuons;
          
     //const int NMUONS = mu_pt->size();
     //Double_t MuPtForSort[NMUONS]={0.0};
     //Int_t

     for(unsigned long i=0; i<mu_pt->size();i++){
       
       
       Double_t MuonPt = mu_pt->at(i);
       Double_t MuonEta = mu_eta->at(i);
       if(MuonPt<MuonPtMin || TMath::Abs(MuonEta) > MuonEtaMax)continue;
       
       //cout<< " MuonPt "<< MuonPt <<endl;
       
       Double_t MuonPhi = mu_phi->at(i); 
       
       Int_t Muon_isGlobal = mu_isGlobal->at(i);
       Int_t Muon_isTracker = mu_isTracker->at(i);
       Int_t Muon_isGood = mu_isGood->at(i);
       Int_t Muon_pixelLayers = mu_pixelLayers->at(i);
       Int_t Muon_pixelHits = mu_pixelHits->at(i);
       Int_t Muon_trkLayers = mu_trkLayers->at(i);
       float Muon_D0 = mu_D0->at(i);
       float Muon_Dz = mu_Dz->at(i);
       float Muon_chi2ndf = mu_chi2ndf->at(i);
       float Muon_innerD0 =  mu_innerD0->at(i);
       float Muon_innerDz =  mu_innerDz->at(i);
       float Muon_muonHits = mu_muonHits->at(i);
       Int_t Muon_stations = mu_stations->at(i);
       
       
       TLorentzVector Muon;
       Muon.SetPtEtaPhiM(MuonPt, MuonEta, MuonPhi, MuonMass); 
       
       Int_t AllCuts =0;
       
       //if(SoftMuonIDCuts(Muon_isGlobal,Muon_isTracker,Muon_isGood,Muon_pixelHits,Muon_trkLayers,Muon_D0,Muon_Dz)==1){AllCuts = 1;}else{AllCuts=0;}
       if(TightMuonIDCuts(Muon_isGlobal,Muon_isTracker,MuonEta,Muon_chi2ndf,Muon_D0,Muon_Dz,Muon_muonHits,Muon_stations,Muon_trkLayers,Muon_pixelHits)==1){AllCuts = 1;}else{AllCuts=0;}
       
       
       if(AllCuts==1){
	 
	 MuonsForJets.push_back(Muon);
	 
	 if(mu_chg->at(i)==1)PositiveMuons.push_back(Muon);
	 if(mu_chg->at(i)==-1)NegativeMuons.push_back(Muon);
	 
	 histMuonPt->Fill(MuonPt);
	 histMuonEta->Fill(MuonEta);
	 histMuonPhi->Fill(MuonPhi);

	 hist_Master_EventCentrality_MuonEta_MuonPt->Fill(EventCentrality,MuonEta,MuonPt);

	 
       } //rec muon quality cuts
     } // rec muon loop



     //Sorting the muons according to their Pt
     //MuonForJets is a vector of LorentzVectors, each LorentzVector is a muon
     //highest pT muon is now on index 0
     std::sort (MuonsForJets.begin(),  MuonsForJets.end(),  GiveMaxPt);
     std::sort (PositiveMuons.begin(), PositiveMuons.end(), GiveMaxPt);
     std::sort (NegativeMuons.begin(), NegativeMuons.end(), GiveMaxPt);


     //if(MuonsForJets.size()<2)continue;
     //cout<<endl;
     //cout<<" MuonsForJets "<<MuonsForJets.size()<<endl;
     //for(unsigned long j=0; j < MuonsForJets.size();j++){
     //TLorentzVector Muon = MuonsForJets.at(j);
     //cout<< " sorted MuonPt "<< Muon.Pt() <<endl;
     //}

     //===================================================================================================//

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
	      

	      histDiMuonInvMass->Fill(DiMuon.M());
	      histDiMuonInvMassLow->Fill(DiMuon.M());
	      histDiMuonInvMassInt->Fill(DiMuon.M());

	      if(TMath::Abs(DiMuon.Rapidity())<=1.6){histDiMuonInvMassHighMid->Fill(DiMuon.M());}
	      if(TMath::Abs(DiMuon.Rapidity())<2.4 && TMath::Abs(DiMuon.Rapidity())> 1.6){histDiMuonInvMassHighFwd->Fill(DiMuon.M());}
	      

	      histDiMuonPt->Fill(DiMuon.Pt());
	      histDiMuonRapidity->Fill(DiMuon.Rapidity());
	      histDiMuonPhi->Fill(DiMuon.Phi());
	    }
	}



      //============== Invariant mass same sign =================//
      // Dimuon with charge +2
      for(unsigned long j=0; j <  PositiveMuons.size();j++)
	{
	  TLorentzVector Muon1 =  PositiveMuons.at(j);
	  for(unsigned long k=j+1; k <  PositiveMuons.size();k++)
	    {
	      
	      TLorentzVector Muon2 =  PositiveMuons.at(k);
	      TLorentzVector DiMuon = Muon1 + Muon2;
	      

	      if(TMath::Abs(DiMuon.Rapidity())<=1.6){histDiMuonInvMassHighSSMid->Fill(DiMuon.M());}
	      if(TMath::Abs(DiMuon.Rapidity())<2.4 && TMath::Abs(DiMuon.Rapidity())> 1.6){histDiMuonInvMassHighSSFwd->Fill(DiMuon.M());}
	      
	    }
	}


      // Dimuon with charge -2
      for(unsigned long j=0; j <  NegativeMuons.size();j++)
	{
	  TLorentzVector Muon1 =  NegativeMuons.at(j);
	  for(unsigned long k=j+1; k <  NegativeMuons.size();k++)
	    {
	      
	      TLorentzVector Muon2 =  NegativeMuons.at(k);
	      TLorentzVector DiMuon = Muon1 + Muon2;
	      

	      if(TMath::Abs(DiMuon.Rapidity())<=1.6){histDiMuonInvMassHighSSMid->Fill(DiMuon.M());}
	      if(TMath::Abs(DiMuon.Rapidity())<2.4 && TMath::Abs(DiMuon.Rapidity())> 1.6){histDiMuonInvMassHighSSFwd->Fill(DiMuon.M());}
	      
	    }
	}




     //=================================== Track loop ================================//
     std::vector<TLorentzVector> TracksForJets;

     const Double_t TrackPtMin = 1.0;

     /*********************************************************/
     // This is not efficient because effectively we read the
     // tracks twise. See if the code can be modified to read the
     //tracks only once when calculating Jet - Track correlation 
     /*********************************************************/

     if(DO_TRACK==1){
     
       for(unsigned long i=0; i<trkPt->size();i++){
	 
	 Double_t TrackPt = trkPt->at(i);
	 Int_t TrackPFType = trkpfType->at(i);
	 
	 if(TrackPt<TrackPtMin || TrackPFType==3)continue;
	 
	 Double_t TrackEta = trkEta->at(i);
	 Double_t TrackPhi = trkPhi->at(i); 
	 
	 TLorentzVector Track;
	 Track.SetPtEtaPhiM(TrackPt, TrackEta, TrackPhi, 0.0); 
	 
	 Int_t AllCuts =1;
	 
	 
	 if(AllCuts==1){
	   
	   TracksForJets.push_back(Track);
	   
	   //if(mu_chg->at(i)==1)PositiveTracks.push_back(Track);
	   //if(mu_chg->at(i)==-1)NegativeTracks.push_back(Track);
	   
	   histTrackPt->Fill(TrackPt);
	   histTrackEta->Fill(TrackEta);
	   histTrackPhi->Fill(TrackPhi);
	   
	 } //track quality cuts
       } //track loop
       
       //std::sort (TracksForJets.begin(),  TracksForJets.end(), GiveMaxPt);

     }//DO_TRACK
     
     //============================================================================//
     
     const Double_t JetPtMinCut = 60.0;
     const Double_t JetEtaCut = 2.0;

     // Array of TLorentz vectors
     // this is used to store all the muons with Delta R < 0.4
     // As the information is required per jet array of lorentz vectors
     // is used
     const int NPFJETS = pf_jtpt->size();
     std::vector<TLorentzVector> AllMatchedMuons_DR04[NPFJETS];
     
     TLorentzVector MatchedMuon;

     if(DEBUG_MODE==1) cout<<" pf Jets "<<pf_jtpt->size()<<endl;

     std::vector<TLorentzVector> JetsForMuons;
     /*****************************************/
     // PF Jet Loop
     /****************************************/
     for (unsigned long i=0; i<pf_jtpt->size();i++) {
       
       Double_t JetPt = pf_jtpt->at(i);
       Double_t JetEta = pf_jteta->at(i);
       Double_t TrackPtMax =  pf_trackMax->at(i);    


       if(DEBUG_MODE==1) cout<<" Jet No "<<i<<" pt "<< JetPt <<endl;
       
       histPfTrackMax_AllJets->Fill(TrackPtMax/JetPt);
       //Jet pt and eta cuts
       if( JetPt<JetPtMinCut || TMath::Abs(JetEta) > JetEtaCut) continue;
       
       histPfTrackMax->Fill(TrackPtMax/JetPt);
       
       // Jet quality cut for the track max       
       if( (TrackPtMax/JetPt) < 0.01 || (TrackPtMax/JetPt > 0.98)) continue;

       Double_t JetPhi = pf_jtphi->at(i);
       Double_t JetCSVV2 = pf_discr_csvV2->at(i);

       histJetPt->Fill(JetPt);
       histJetEta->Fill(JetEta);
       histJetPhi->Fill(JetPhi);
       histJetCSV->Fill(JetCSVV2);

       TLorentzVector Jet;
       Jet.SetPtEtaPhiM(JetPt, JetEta, JetPhi, 0.0);
       JetsForMuons.push_back(Jet);

       hist_Master_JetEta_JetPt_JetPhi->Fill(JetEta,JetPt,JetPhi);
       hist_Master_EventCentrality_JetEta_JetPt->Fill(EventCentrality,JetEta,JetPt);
       hist_Master_EventCentrality_JetCSV_JetPt->Fill(EventCentrality,JetCSVV2,JetPt);
       
       //======================================================================//
       //==================== pf jet reco muon matching =======================//
       //======================================================================//

       //================ select the Tightest Muon ======================//
       int smallestDRindex =0;
       double smallestDR = 1000.0;
       Double_t MuonJetDR_Max = 0.4;
              
       if(DEBUG_MODE==1) cout<<" muons inside jet loop "<<MuonsForJets.size()<<endl;
       

       for(unsigned long j=0; j<MuonsForJets.size();j++)
	 {
	   
	   TLorentzVector Muon = MuonsForJets.at(j);
	   
	   Double_t MuonPt=Muon.Pt();
	   Double_t MuonEta=Muon.Eta();
	   Double_t MuonPhi=Muon.Phi();
	   
	   if(DEBUG_MODE==1) cout<<" muon no "<<j<<" pt "<<MuonPt<<endl;
	   
	   //Calculate DR is a class. It is generated so that there is 
	   //no cinfusion in phi used in DR and phi used in plots of delta phi
	   CalculateDR DR1;

	   Double_t MuonJetDR = DR1.getDR(MuonEta, MuonPhi, JetEta, JetPhi);
	   histMuonJetDR->Fill(MuonJetDR);

	   if(DEBUG_MODE==1) cout<<" DeltaR "<< MuonJetDR <<endl;
	   
	   Double_t MuonJetDPhi = plotDPHI(MuonPhi,JetPhi);
	   histMuonJetDPhi->Fill(MuonJetDPhi);
	   
	   Double_t MuonJetDEta = MuonEta - JetEta;
	   histMuonJetDEta->Fill(MuonJetDEta);
	   
	   histMuonJetDEtaDPhi->Fill(MuonJetDEta,MuonJetDPhi);
	   
	   //All the matched muons with DR < 0.4 are in this vector
	   if(MuonJetDR < MuonJetDR_Max){
	     
	     AllMatchedMuons_DR04[i].push_back(Muon);

	   }



	   if(MuonJetDR<smallestDR)
	     {
	       smallestDR = MuonJetDR;
	       smallestDRindex=j;
	     }
	   
	 }//MuonsForJet.size()  
       
       if(smallestDR < MuonJetDR_Max){

	 if(DEBUG_MODE==1) cout<<" found tight muon "<< smallestDR <<endl;
	 
	 if(DEBUG_MODE==1) cout<<" Jet pt "<<JetPt<<endl;
	 
	 MatchedMuon = MuonsForJets.at(smallestDRindex);
	 
	 histMuonJetPt->Fill(JetPt);
	 
	 hist_Master_EventCentrality_JetPt_MuonPt->Fill(EventCentrality,JetPt,MatchedMuon.Pt());
	 
	 hist_Master_MuonEta_MuonPt_MuonPhi_StJet->Fill(MatchedMuon.Eta(),MatchedMuon.Pt(),MatchedMuon.Phi());

	 if(DEBUG_MODE==1) cout<<" Matched muon pt "<<MatchedMuon.Pt()<<endl;
	 
	 Double_t MuonJetPtRel = getPtRel(MatchedMuon.Pt(),MatchedMuon.Eta(),MatchedMuon.Phi(),JetPt,JetEta,JetPhi);
	 
	 hist_Master_JetCSV_JetPt_MuonPtRel->Fill(JetCSVV2,JetPt,MuonJetPtRel);
	 hist_Master_JetCSV_JetPt_MuonPt->Fill(JetCSVV2,JetPt,MatchedMuon.Pt());
	 

	 hist_Master_EventCentrality_MuonJetCSV_MuonJetPt->Fill(EventCentrality,JetCSVV2,JetPt);

	 histMuonPtRel->Fill(MuonJetPtRel);
	 histMuonJetCSV->Fill(JetCSVV2);

	 Double_t CSVWorkingPoint = 0.9;
	 if(JetCSVV2 > CSVWorkingPoint ) {histMuonPtRelCSVTag->Fill(MuonJetPtRel);} 
	 if(JetCSVV2 > 0.0 && JetCSVV2 < CSVWorkingPoint ) {histMuonPtRelCSVVeto->Fill(MuonJetPtRel);}
  
 
	 if(DEBUG_MODE==1) cout<<" Matched muon pt rel "<< MuonJetPtRel <<endl;
	     
	     
       }//muon Jet DR (Tightest matched muons)




       /*****************************************************/
       //JET TRACT CORELATIONS LOOP 
       //TAKES LOTS OF TIME
       //(DO_TRACK ==1 && DO_TRACK_JET_CORR ==1) switchs
       /****************************************************/

       if(DO_TRACK ==1 && DO_TRACK_JET_CORR ==1){    
	 
	 for(unsigned long j=0; j<TracksForJets.size();j++)
	   {
	     
	     TLorentzVector Track = TracksForJets.at(j);
	     
	     Double_t TrackPt=Track.Pt();
	     Double_t TrackEta=Track.Eta();
	     Double_t TrackPhi=Track.Phi();
	     
	     CalculateDR DR2;
	     
	     Double_t TrackJetDR = DR2.getDR(TrackEta, TrackPhi, JetEta, JetPhi);
	     histTrackJetDR->Fill(TrackJetDR);
	     
	     
	     Double_t TrackJetDPhi = plotDPHI(TrackPhi,JetPhi);
	     histTrackJetDPhi->Fill(TrackJetDPhi);
	     
	     Double_t TrackJetDEta = TrackEta - JetEta;
	     histTrackJetDEta->Fill(TrackJetDEta);
	     
	     histTrackJetDEtaDPhi->Fill(TrackJetDEta,TrackJetDPhi);
	     
	     Double_t TrackJetPtRel = getPtRel(TrackPt,TrackEta,TrackPhi,JetPt,JetEta,JetPhi);
	   
	   
	     Double_t TrackJetDR_Max = 0.4;
	     
	     if(TrackJetDR < TrackJetDR_Max){
	       
	       //histTrackJetPt->Fill(JetPt);
	       
	       hist_Master_TrackEta_TrackPt_TrackPhi->Fill(TrackEta,TrackPt,TrackPhi);
	       
	       //histTrackPtRel->Fill(TrackJetPtRel);
	       
	       
	     }//track Jet DR
	     
	   }//TracksForJet.size()
	 
       } //DO_TRACK_JET_CORR

       
       
     }//pf Jet Loop


     if(DEBUG_MODE==1)cout<<endl<<endl;


     /*******************************************************/
     // Sort the Jets according to pT
     /*******************************************************/
     std::sort (JetsForMuons.begin(),  JetsForMuons.end(), GiveMaxPt);

     //==========================================================================================//
     //========================== This gives the number of muons which are inside Jets =========//
     //========================== Muon Jet Matching (Starting from Muons) ======================//
     //==========================================================================================//
     

     TLorentzVector MatchedJet;

     for(unsigned long i=0; i<MuonsForJets.size();i++)
       {
	 
	 TLorentzVector Muon = MuonsForJets.at(i);
	 
	 Double_t MuonPt=Muon.Pt();
	 Double_t MuonEta=Muon.Eta();
	 Double_t MuonPhi=Muon.Phi();
	 
	 
	 int smallestDRindex =0;
	 double smallestDR = 1000.0;
	 Double_t MuonJetDR_Max = 0.4;
	 
	 
	 
	 for(unsigned long j=0; j<JetsForMuons.size();j++)
	   {
	     
	     TLorentzVector Jet = JetsForMuons.at(j);
	     
	     Double_t JetPt=Jet.Pt();
	     Double_t JetEta=Jet.Eta();
	     Double_t JetPhi=Jet.Phi();
	     
	     CalculateDR DR3;   
	     Double_t MuonJetDR = DR3.getDR(MuonEta, MuonPhi, JetEta, JetPhi);
	     
	     //histTrackJetDR->Fill(TrackJetDR);
	     
	     
	     Double_t MuonJetDPhi = plotDPHI(MuonPhi,JetPhi);
	     //histTrackJetDPhi->Fill(TrackJetDPhi);
	     
	     Double_t MuonJetDEta = MuonEta - JetEta;
	     //histTrackJetDEta->Fill(TrackJetDEta);
	     //histTrackJetDEtaDPhi->Fill(TrackJetDEta,TrackJetDPhi);
	     
	     
	     if(MuonJetDR<smallestDR)
	       {
		 smallestDR = MuonJetDR;
		 smallestDRindex=j;
	       }
	     
	   }//Jets for Muons
	 
	 if( smallestDR < MuonJetDR_Max){
	   MatchedJet = JetsForMuons.at(smallestDRindex);
	   histMatchedMuonPt_StMuons->Fill(MuonPt);
	   hist_Master_EventCentrality_MuonPt_JetPt->Fill(EventCentrality,MuonPt,MatchedJet.Pt());
	   
     	   //histTrackJetPt->Fill(JetPt);
	   //hist_Master_TrackEta_TrackPt_TrackPhi->Fill(TrackEta,TrackPt,TrackPhi);
	   //histTrackPtRel->Fill(TrackJetPtRel);
	   
	   
	 }//Muon Jet DR

	
       }//MuonsForJet Loop


     /****************************************************************************************/
     // ALL THE MUONS PROPERTIES WHICH HAVE DELTA R < 0.4 WITH JETS
     //FILL HISTOGRAMS HERE
     /*************************************************************************************/


     for (int i=0; i<NPFJETS;i++) {
       
       histMatchedMuonsDR04Size->Fill(AllMatchedMuons_DR04[i].size());
     
       for(unsigned long j=0; j<AllMatchedMuons_DR04[i].size();j++)
	 {
	     
	   TLorentzVector MatchedMuonDR04 = AllMatchedMuons_DR04[i].at(j);
	 
	   Double_t MatchedMuonDR04Pt=MatchedMuonDR04.Pt();
	   Double_t MatchedMuonDR04Eta=MatchedMuonDR04.Eta();
	   Double_t MatchedMuonDR04Phi=MatchedMuonDR04.Phi();
	   
	   histMatchedMuonsDR04Pt->Fill(MatchedMuonDR04Pt); 
	   histMatchedMuonsDR04Eta->Fill(MatchedMuonDR04Eta);
	   histMatchedMuonsDR04Phi->Fill(MatchedMuonDR04Phi);
	 }
     }
   
     
     // if (Cut(ientry) < 0) continue;
   } //event entry loop



   //void FlavouredHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize)


   FlavouredHistogram(histJetPt, 1, 1, 20, 0.8);
   FlavouredHistogram(histJetEta, 1, 1, 20, 0.8);
   FlavouredHistogram(histJetPhi, 1, 1, 20, 0.8);


   FlavouredHistogram(histMuonPt, 1, 1, 20, 0.8);
   FlavouredHistogram(histMuonEta, 1, 1, 20, 0.8);
   FlavouredHistogram(histMuonPhi, 1, 1, 20, 0.8);


   FlavouredHistogram(histMuonJetDR, 1, 1, 20, 0.8);
   FlavouredHistogram(histMuonJetPt, 1, 1, 20, 0.8);

   FlavouredHistogram(histMuonJetDEta, 2, 2, 20, 0.8);
   FlavouredHistogram(histMuonPtRel, 2, 2, 20, 0.8);
   FlavouredHistogram(histMuonJetDPhi, 2, 2, 20, 0.8);
 

   FlavouredHistogram(histTrackPt, 1, 1, 20, 0.8);
   FlavouredHistogram(histTrackEta, 1, 1, 20, 0.8);
   FlavouredHistogram(histTrackPhi, 1, 1, 20, 0.8);
   

   TH1D *hist_JetPtRatio_MuonJet_AllJets = RatioHistogram(histMuonJetPt,histJetPt,1);

   hist_JetPtRatio_MuonJet_AllJets->SetName("hist_JetPtRatio_MuonJet_AllJets");
   hist_JetPtRatio_MuonJet_AllJets->SetTitle("hist_JetPtRatio_MuonJet_AllJets");

   hist_JetPtRatio_MuonJet_AllJets->GetXaxis()->SetTitle("Jet p_{T} GeV/c");
   FlavouredHistogram(hist_JetPtRatio_MuonJet_AllJets, 2, 2, 20, 0.8);




   TH1D *hist_MuonPtRatio_JetMuons_AllMuons = RatioHistogram(histMatchedMuonPt_StMuons,histMuonPt,1);
   hist_MuonPtRatio_JetMuons_AllMuons->SetName("hist_MuonPtRatio_JetMuons_AllMuons");
   hist_MuonPtRatio_JetMuons_AllMuons->SetTitle("hist_MuonPtRatio_JetMuons_AllMuons");
   hist_MuonPtRatio_JetMuons_AllMuons->GetXaxis()->SetTitle("Muon p_{T} GeV/c");
   FlavouredHistogram(hist_MuonPtRatio_JetMuons_AllMuons, 2, 2, 20, 0.8);


   TEfficiency* eff_MuonPtRatio_JetMuons_AllMuons = new TEfficiency(*histMatchedMuonPt_StMuons,*histMuonPt);

   
   new TCanvas;
   gPad->SetLogy(1);
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histJetPt->Draw();
   gPad->SaveAs("Plots/JetPt.png");
   gPad->SaveAs("Plots/JetPt.pdf");
   

  
   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   //histJetEta->GetXaxis()->SetRangeUser(-2.5,2.5);
   //histJetEta->GetYaxis()->SetRangeUser(0.0,20000.0);
   histJetEta->Draw();
   gPad->SaveAs("Plots/JetEta.png");
   gPad->SaveAs("Plots/JetEta.pdf");
   

   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   //histJetPhi->Rebin(4);
   //histJetPhi->GetYaxis()->SetRangeUser(0.0,15000.0);
   histJetPhi->Draw();
   gPad->SaveAs("Plots/JetPhi.png");
   gPad->SaveAs("Plots/JetPhi.pdf");

   histPfTrackMax_AllJets->SetMarkerColor(2);
   histPfTrackMax_AllJets->SetLineColor(2);



   new TCanvas;
   gPad->SetLogy(1);
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histPfTrackMax_AllJets->Draw();
   histPfTrackMax->Draw("same");
   gPad->SaveAs("Plots/PfTrackMax_AllJets.png");
   gPad->SaveAs("Plots/PfTrackMax_AllJets.pdf");




   new TCanvas;
   gPad->SetLogy(1);
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histPfTrackMax->Draw();
   gPad->SaveAs("Plots/PfTrackMax.png");
   gPad->SaveAs("Plots/PfTrackMax.pdf");

   




   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histMuonJetDR->Draw();
   gPad->SaveAs("Plots/JetMuonDR.png");
   gPad->SaveAs("Plots/JetMuonDR.pdf");


   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histMuonJetDPhi->Draw();
   gPad->SaveAs("Plots/JetMuonDPhi.png");
   gPad->SaveAs("Plots/JetMuonDPhi.pdf");



   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histMuonJetDEta->Draw();
   gPad->SaveAs("Plots/JetMuonDEta.png");
   gPad->SaveAs("Plots/JetMuonDEta.pdf");


   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histMuonJetDEtaDPhi->Rebin2D(16);
   histMuonJetDEtaDPhi->Draw("surf1");
   gPad->SaveAs("Plots/JetMuonDEtaDPhi.png");
   gPad->SaveAs("Plots/JetMuonDEtaDPhi.pdf");
   
   


   new TCanvas;
   gPad->SetLogy(1);
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histMuonJetPt->Draw();
   gPad->SaveAs("Plots/JetMuonJetPt.png");
   gPad->SaveAs("Plots/JetMuonJetPt.pdf");
   

  
  
   new TCanvas;
   gPad->SetLogy(1);
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histMuonPt->Draw();
   gPad->SaveAs("Plots/MuonPt.png");
   gPad->SaveAs("Plots/MuonPt.pdf");
   
   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histMuonEta->GetYaxis()->SetRangeUser(0.0,2000.0);
   histMuonEta->Draw();
   gPad->SaveAs("Plots/MuonEta.png");
   gPad->SaveAs("Plots/MuonEta.pdf");
   
   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histMuonPhi->GetYaxis()->SetRangeUser(0.0,1500.0);
   histMuonPhi->Draw();
   gPad->SaveAs("Plots/MuonPhi.png");
   gPad->SaveAs("Plots/MuonPhi.pdf");


  
   new TCanvas;
   gPad->SetLogy(1);
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histMuonPtRel->Draw();
   gPad->SaveAs("Plots/MuonPtRel.png");
   gPad->SaveAs("Plots/MuonPtRel.pdf");

   new TCanvas;
   gPad->SetLogy(1);
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   hist_JetPtRatio_MuonJet_AllJets->Draw();
   gPad->SaveAs("Plots/JetPtRatio_MuonJet_AllJets.png");
   gPad->SaveAs("Plots/JetPtRatio_MuonJet_AllJets.pdf");
   





  
   new TCanvas;
   gPad->SetLogy(1);
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   histTrackPt->Draw();
   gPad->SaveAs("Plots/TrackPt.png");
   gPad->SaveAs("Plots/TrackPt.pdf");
   
   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   //histTrackEta->GetYaxis()->SetRangeUser(0.0,2000.0);
   histTrackEta->Draw();
   gPad->SaveAs("Plots/TrackEta.png");
   gPad->SaveAs("Plots/TrackEta.pdf");
   
   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   //histTrackPhi->GetYaxis()->SetRangeUser(0.0,1500.0);
   histTrackPhi->Draw();
   gPad->SaveAs("Plots/TrackPhi.png");
   gPad->SaveAs("Plots/TrackPhi.pdf");





   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   hist_MuonPtRatio_JetMuons_AllMuons->Draw();
   gPad->SaveAs("Plots/MuonPtRatio_JetMuons_AllMuons.png");
   gPad->SaveAs("Plots/MuonPtRatio_JetMuons_AllMuons.pdf");



   new TCanvas;
   gPad->SetBottomMargin(0.2);
   gPad->SetLeftMargin(0.2);
   hist_MuonPtRatio_JetMuons_AllMuons->Draw();
   eff_MuonPtRatio_JetMuons_AllMuons->Draw("same");

   //write the histograms in output file
   
   histCentrality->Write();
   histEvtVtxX->Write();
   histEvtVtxY->Write();
   histEvtVtxZ->Write();

   histJetPt->Write();
   histJetEta->Write();
   histJetPhi->Write();

   histJetCSV->Write();

   hist_Master_JetEta_JetPt_JetPhi->Write();
   hist_Master_EventCentrality_JetEta_JetPt->Write();
   hist_Master_EventCentrality_JetCSV_JetPt->Write();
   histPfTrackMax_AllJets->Write();
   histPfTrackMax->Write();

   histMuonPt->Write();
   histMuonEta->Write();
   histMuonPhi->Write();
   
   histMuonJetDR->Write();
   histMuonPtRel->Write();
   histMuonJetCSV->Write();

   hist_Master_JetCSV_JetPt_MuonPtRel->Write();
   hist_Master_JetCSV_JetPt_MuonPt->Write();
   hist_Master_EventCentrality_MuonJetCSV_MuonJetPt->Write();

   histMuonPtRelCSVTag->Write();
   histMuonPtRelCSVVeto->Write();


   histMuonJetDPhi->Write();
   histMuonJetDEta->Write();
   
   histMuonJetPt->Write();
   hist_JetPtRatio_MuonJet_AllJets->Write();
   hist_Master_MuonEta_MuonPt_MuonPhi_StJet->Write();
   histMuonJetDEtaDPhi->Write();
   hist_Master_EventCentrality_JetPt_MuonPt->Write();



   histDiMuonInvMass->Write();
   histDiMuonInvMassLow->Write();
   histDiMuonInvMassInt->Write();
   histDiMuonInvMassHighMid->Write();
   histDiMuonInvMassHighFwd->Write();
   histDiMuonInvMassHighSSMid->Write();
   histDiMuonInvMassHighSSFwd->Write();
   histDiMuonPt->Write();
   histDiMuonRapidity->Write();
   histDiMuonPhi->Write();
   
   histTrackPt->Write();
   histTrackEta->Write();
   histTrackPhi->Write();
   histTrackJetDR->Write();
   histTrackJetDPhi->Write();
   histTrackJetDEta->Write();
   hist_Master_TrackEta_TrackPt_TrackPhi->Write();
   histTrackJetDEtaDPhi->Write();
   
   histMatchedMuonPt_StMuons->Write();
   hist_MuonPtRatio_JetMuons_AllMuons->Write();
   hist_Master_EventCentrality_MuonEta_MuonPt->Write();
   hist_Master_EventCentrality_MuonPt_JetPt->Write();
   
   histMatchedMuonsDR04Size->Write();
   histMatchedMuonsDR04Pt->Write();
   histMatchedMuonsDR04Eta->Write();
   histMatchedMuonsDR04Phi->Write();
   
   
   

}//read slim skim





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







void FlavouredHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize)
{
  
  InHist->SetLineColor(LineColor);
  InHist->SetMarkerColor(MarkerColor);
  InHist->SetMarkerStyle(MarkerStyle);
  InHist->SetMarkerSize(MarkerSize);
  //InHist->GetXaxis()->SetNdivisions(505);
  InHist->GetXaxis()->SetLabelSize(0.06);
  InHist->GetXaxis()->SetTitleOffset(1.4);
  InHist->GetXaxis()->SetTitleSize(0.06);
  InHist->GetYaxis()->SetTitleSize(0.06);

  
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







/*
double
HiInclusiveJetAnalyzer::getPtRel(const reco::PFCandidate lep, const pat::Jet& jet )
{

  float lj_x = jet.p4().px();
  float lj_y = jet.p4().py();
  float lj_z = jet.p4().pz();

  // absolute values squared
  float lj2  = lj_x*lj_x+lj_y*lj_y+lj_z*lj_z;
  float lep2 = lep.px()*lep.px()+lep.py()*lep.py()+lep.pz()*lep.pz();

  // projection vec(mu) to lepjet axis
  float lepXlj = lep.px()*lj_x+lep.py()*lj_y+lep.pz()*lj_z;

  // absolute value squared and normalized
  float pLrel2 = lepXlj*lepXlj/lj2;

  // lep2 = pTrel2 + pLrel2
  float pTrel2 = lep2-pLrel2;

  return (pTrel2 > 0) ? std::sqrt(pTrel2) : 0.0;
}
*/




TH1D *RatioHistogram(TH1 *InHistNum, TH1 *InHistDeno, Int_t RebinFac)
{

  TH1D *temp_Num = (TH1D*)InHistNum->Clone("temp_Num");

  //temp_Num->SetName("temp_Num");
  //temp_Num->SetTitle("temp_Num");
  
  TH1D *temp_Deno = (TH1D*)InHistDeno->Clone("temp_Deno");

  //temp_Deno->SetName("temp_Deno");
  //temp_Deno->SetTitle("temp_Deno");
  
  temp_Num->Rebin(RebinFac);
  temp_Deno->Rebin(RebinFac);
  
  temp_Num->Divide(temp_Num,temp_Deno,1.0,1.0,"B");
  

  return temp_Num;


}


bool GiveMaxPt(TLorentzVector vec1, TLorentzVector vec2) 
{ return (vec1.Pt()>vec2.Pt()); }
