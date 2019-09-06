#ifndef __CINT__
#endif
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TAxis.h"
#include "TH1.h"
#include "TH2.h"

#include "TH3.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
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

#include "CMS/tdrstyle.C"
#include "CMS/CMS_lumi.C"

#include <iomanip>
#include <fstream>

#include "THStack.h"
#include "TRandom3.h"





void GlamorizeHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize);

//TH1D *RatioHistogram(TH1 *InHistNum, TH1 *InHistDeno, Int_t RebinFac);

TLegend *MyLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2);

TH1D *RatioHistogram(TH1 *InHistNum, TH1 *InHistDeno, Int_t RebinFac);


void rebinAsymmetric(TH1* histogram, const int nBins, const double* binEdges);
bool checkBinBoundaries(const int nCheckedBins, const double *checkedBins, TAxis *originalAxis);

TH1D *Get_Ghost_Hist(const char *Name, const char *Title, Int_t NBins, Double_t XMin, Double_t XMax, Double_t YMin, Double_t YMax, const char *XTitle, const char *YTitle);

// Making different functions
void DrawEventHistograms(TFile *file_in, TFile *file_Out, TLatex *tb);
void FoundJetStat(TFile *file_in, TFile *file_Out, TLatex *tb, TLatex *tr);

void FoundJetStatStartMuon(TFile *file_in, TLatex *tb, TLatex *tr);

void CSVPlots(TFile *file_in,  TFile *file_Out, TLatex *tb, TLatex *tr);


void Print3DHistInfo(TH3 *InHist3D);
void Print1DHistInfoAndInt(TH1 *InHist1D, Int_t MultiWidth);

//switchs
const Int_t PRINT_BIN_CENTRE = 0;
const Int_t DEBUG_CODE = 0;



//global variables
const Double_t Pi = TMath::Pi();
const Double_t JetPtMin = 60.0;
const Double_t JetPtMax = 500.0;
  
const Double_t JetEtaMin = -2.0;
const Double_t JetEtaMax =  2.0;

const Double_t JetPhiMin = -Pi;
const Double_t JetPhiMax =  Pi;

const Double_t MuonPtMin = 5.0;
const Double_t MuonPtMax = 100.0;

const Double_t MuonEtaMin = -2.4;
const Double_t MuonEtaMax = 2.4;
  
const Int_t EvtCentMin = 0;
const Int_t EvtCentMax = 100;


//bin boundry matching with the original histogram bin boundry
//const int NBins_JetPt_VarSize=12;
//Double_t JetPtBinEdges[NBins_JetPt_VarSize]={80.0,85.0,90.0,100.0,120.0,140.0,160.0,200.0,240.0,320.0,400.0,499.0};

// if Jet pt cut is 60
const int NBins_JetPt_VarSize=16;
Double_t JetPtBinEdges[NBins_JetPt_VarSize]={60.0, 65.0, 70.0, 75.0, 80.0,85.0,90.0,100.0,120.0,140.0,160.0,200.0,240.0,320.0,400.0,499.0};

const int NBins_JetEta_VarSize=49;
Double_t JetEtaBinEdges[NBins_JetEta_VarSize]={-2.4,-2.31,-2.22,-2.1,-2.01,-1.89,-1.8,-1.71,-1.59,-1.5,
					       -1.41,-1.29, -1.2, -1.11, -0.99, -0.9, -0.81, -0.69, -0.6,
					       -0.51, -0.39, -0.3, -0.21, -0.09, 0.0, 0.09, 0.21, 0.3, 0.39,
					       0.51, 0.6, 0.69, 0.81, 0.9, 0.99, 1.11, 1.2, 1.29, 1.41, 1.5,
					       1.59,1.71,1.8,1.89,2.01,2.1,2.22,2.31,2.4};


const int NBins_JetPhi_VarSize=51;
Double_t JetPhiBinEdges[NBins_JetPhi_VarSize]={-3.14159,-3.01593,-2.89027,-2.7646,-2.63894,-2.51327,-2.38761,
					       -2.26195,-2.13628,-2.01062,-1.88496,-1.75929,-1.63363,-1.50796,
					       -1.3823,-1.25664,-1.13097,-1.00531,-0.879646,-0.753982,-0.628319,
					       -0.502655,-0.376991,-0.251327,-0.125664,4.44089e-16,0.125664, 0.251327,
					       0.376991,0.502655,0.628319,0.753982,0.879646,1.00531,1.13097,1.25664,
					       1.3823,1.50796,1.63363,1.75929,1.88496,2.01062,2.13628,2.26195,2.38761,
					       2.51327,2.63894,2.7646,2.89027,3.01593,3.11018};

const int NBins_MuonPt_VarSize=13;
const Double_t MuonPtBinEdges[NBins_MuonPt_VarSize]={1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 14.0, 18.0, 22.0, 30.0, 40.0, 60.0, 100.0};

const Int_t NCentBins = 4;
const Int_t CentBins[NCentBins+1]={0,10,30,50,100};


const Int_t NJetPtCuts =4;
const Double_t JetPtCuts[NJetPtCuts]={60.0,80.0,100.0,120.0};
const Int_t ColourPtCut[NJetPtCuts]={1,2,4,6};

const Int_t do_PbPb =0;



void MakeFineAnalysis()
{

  setTDRStyle();
  TH1::SetDefaultSumw2();
  
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.2);
  gStyle->SetOptStat(0);
  
  
  TLatex *tb = new TLatex();
  tb->SetNDC();
  tb->SetTextColor(kBlack);
  tb->SetTextSize(0.04);


  TLatex *tr = new TLatex();
  tr->SetNDC();
  tr->SetTextColor(kRed);
  tr->SetTextSize(0.04);

  
  char LatexChar[400];

  //const Double_t Pi = TMath::Pi();

  //TFile *file_in =  new TFile("InRootFile/PbPbData_HLT_HIL3Mu12_v1_JetPtMin30.root","R");
  //TFile *file_in =  new TFile("InRootFile/PbPbData_HLT_HIL3Mu12_v1_JetPtMin60.root","R");
  //TFile *file_in =  new TFile("InRootFile/PbPbData_HLT_HIL3Mu12_v1_JetPtMin30_JetEtaMax24_JetQualityOn.root","R");
  //TFile *file_in =  new TFile("InRootFile/PbPbData_HLT_HIL3Mu12_v1_JetPtMin80_JetEtaMax16_MuEtaMax24_JetQualityOn.root","R");
  //TFile *file_in =  new TFile("InRootFile/PbPbData_HLT_HIL3Mu12_v1_JetPtMin80_JetEtaMax20_MuEtaMax24_JetQualityOn.root","R");
  //TFile *file_in =  new TFile("InRootFile/PbPbData_HLT_HIL3Mu12_v1_JetPtMin80_JetEtaMax16_MuEtaMax24_JetQualityOn.root","R");

  //HiHard Probe Dataset File added on 09.July.2019
  //TFile *file_in =  new TFile("InRootFile/PbPbData_HLT_CaloJet100_JetPtMin100_JetEtaMax16_MuEtaMax24_MuPtMin5_JetQualityOn.root","R");

  //HiHard Probe Dataset (Muon+Jet Triggers) File added on 17.July.2019
  //TFile *file_in =  new TFile("InRootFile/PbPbData_HLT_MuonJet60_JetPtMin60_JetEtaMax2_MuEtaMax24_MuPtMin5_JetQualityOn.root","R");

  //Single MuPD  (Muon+Jet Triggers) File added on 21.August.2019
  //TFile *file_in =  new TFile("InRootFile/PbPbData_HLT_MuonJet60_JetPtMin60_JetEtaMax2_MuEtaMax24_MuPtMin5_JetQualityOn_SingleMuPD.root","R");

  //******** PP 2017 Data ********************//
  TFile *file_in =  new TFile("InRootFile/PP2017Data_HLT_MuonJet30_JetPtMin60_JetEtaMax2_MuEtaMax24_MuPtMin5_JetQualityOn.root","R");

  
  cout<<" Analysing file: "<<file_in->GetName()<<endl;

  TFile *file_Out =  new TFile("OutFile_PP2017Data_HLT_MuonJet30_JetPtMin60_JetEtaMax2_MuEtaMax24_MuPtMin5_JetQualityOn.root","RECREATE");
  
  DrawEventHistograms(file_in, file_Out, tb);

  FoundJetStat(file_in, file_Out, tb, tr);
  //FoundJetStatStartMuon(file_in, tb, tr);
  //CSVPlots(file_in,file_Out, tb, tr);
  
  //this closing make many histos disappear from canvases
  //file_Out->Close();

  
  return;



  
}



void CSVPlots(TFile *file_in,  TFile *file_Out, TLatex *tb, TLatex *tr)
{
  
  /***********************************************************************************/
  /***********************************************************************************/
  /***********************************************************************************/
  //CSV V2 Tagger Plots
  //
  //
  // MUON JET Pt Rel Plots
  /***********************************************************************************/
  /***********************************************************************************/
  /***********************************************************************************/
  
  Double_t CSVWorkingPoint = 0.9;
  TGraph *line1_csv;
  line1_csv= new TGraph(2);
  line1_csv->SetLineColor(1);

  
  TH1D *hist_JetCSV=(TH1D*)file_in->Get("histJetCSV");
  hist_JetCSV->GetYaxis()->SetTitle("Entries");
  hist_JetCSV->GetXaxis()->SetTitle("CSV v2");
  line1_csv->SetPoint(0,CSVWorkingPoint,0);
  line1_csv->SetPoint(1,CSVWorkingPoint,hist_JetCSV->GetMaximum());
  
  TH1D *hist_MuonJetCSV=(TH1D*)file_in->Get("histMuonJetCSV");
  hist_MuonJetCSV->GetYaxis()->SetTitle("Entries");
  hist_MuonJetCSV->GetXaxis()->SetTitle("CSV v2");
  
  Int_t Bin_CSV_Min = hist_JetCSV->GetXaxis()->FindBin(0.0);
  Int_t Bin_CSV_WorkingPoint = hist_JetCSV->GetXaxis()->FindBin(CSVWorkingPoint);
  Int_t Bin_CSV_Max = hist_JetCSV->GetXaxis()->FindBin(1.0);
  

  cout<<" hist_JetCSV Bin_CSV_Min "<< Bin_CSV_Min <<" Bin_CSV_WorkingPoint " << Bin_CSV_WorkingPoint <<" Bin_CSV_Max "<<Bin_CSV_Max<<endl;

  Double_t Number_Jets_CSV_Veto = hist_JetCSV->Integral(Bin_CSV_Min,Bin_CSV_WorkingPoint-1);    
  Double_t Number_Jets_CSV_Tag = hist_JetCSV->Integral(Bin_CSV_WorkingPoint,Bin_CSV_Max);
  Double_t Jet_CSV_Tag_Fraction = Number_Jets_CSV_Tag/(Number_Jets_CSV_Tag+Number_Jets_CSV_Veto) ;
  Double_t Jet_CSV_Veto_Fraction = Number_Jets_CSV_Veto/(Number_Jets_CSV_Tag+Number_Jets_CSV_Veto) ;
  
  Double_t Number_MuonJets_CSV_Tag = hist_MuonJetCSV->Integral(Bin_CSV_WorkingPoint,Bin_CSV_Max);
  Double_t Number_MuonJets_CSV_Veto = hist_MuonJetCSV->Integral(Bin_CSV_Min,Bin_CSV_WorkingPoint-1);
  
  Double_t MuonJet_CSV_Tag_Fraction = Number_MuonJets_CSV_Tag/(Number_MuonJets_CSV_Tag+Number_MuonJets_CSV_Veto) ;
  Double_t MuonJet_CSV_Veto_Fraction = Number_MuonJets_CSV_Veto/(Number_MuonJets_CSV_Tag+Number_MuonJets_CSV_Veto) ;
  
    
  TH1D *hist_MuonPtRel=(TH1D*)file_in->Get("histMuonPtRel");
  hist_MuonPtRel->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");

  hist_MuonPtRel->SetStats(kFALSE);
  hist_JetCSV->SetStats(kFALSE);
  
  GlamorizeHistogram(hist_JetCSV,1,1,20,0.6);
  GlamorizeHistogram(hist_MuonJetCSV,2,2,20,0.6);
  GlamorizeHistogram(hist_MuonPtRel,2,2,20,0.6);
    
  TCanvas *Canvas_JetCSV_MuonPtRel = new TCanvas("Canvas_JetCSV_MuonPtRel","Canvas_JetCSV_MuonPtRel",800,400);
  Canvas_JetCSV_MuonPtRel->Divide(2,1);
  Canvas_JetCSV_MuonPtRel->cd(1);
  

  TLegend *lgd_JetCSV_MuonPtRel = MyLegend(0.30,0.34,0.46,0.48);
  lgd_JetCSV_MuonPtRel->AddEntry(hist_JetCSV,"Jets","P");
  lgd_JetCSV_MuonPtRel->AddEntry(hist_MuonJetCSV,"Muon Jets","P");
  

  
  gPad->SetLogy(1);
  hist_JetCSV->Draw();
  hist_MuonJetCSV->Draw("same");
  line1_csv->Draw("same");
  lgd_JetCSV_MuonPtRel->Draw("same");
  
  tb->DrawLatex(0.3,0.80,Form("Jets CSVv2>0.9=%0.2f",Jet_CSV_Tag_Fraction));
  tb->DrawLatex(0.3,0.76,Form("Jets CSVv2<0.9=%0.2f",Jet_CSV_Veto_Fraction));
  tr->DrawLatex(0.3,0.30,Form("MuonJets CSVv2>0.9=%0.2f",MuonJet_CSV_Tag_Fraction));
  tr->DrawLatex(0.3,0.26,Form("MuonJets CSVv2<0.9=%0.2f",MuonJet_CSV_Veto_Fraction));
    
  Canvas_JetCSV_MuonPtRel->cd(2);
  //gPad->SetLogy(1);
  hist_MuonPtRel->Draw();
  Canvas_JetCSV_MuonPtRel->SaveAs("Figures/JetCSV_MuonPtRel.pdf");
  Canvas_JetCSV_MuonPtRel->SaveAs("Figures/JetCSV_MuonPtRel.png");
  

  TH1D *hist_MuonPtRelCSVTag=(TH1D*)file_in->Get("histMuonPtRelCSVTag");
  hist_MuonPtRelCSVTag->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  hist_MuonPtRelCSVTag->GetYaxis()->SetTitle("Entries");
  
  TH1D *hist_MuonPtRelCSVVeto=(TH1D*)file_in->Get("histMuonPtRelCSVVeto");
  hist_MuonPtRelCSVVeto->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");
  hist_MuonPtRelCSVVeto->GetYaxis()->SetTitle("Entries");
  
  GlamorizeHistogram(hist_MuonPtRelCSVTag,2,2,20,0.6);
  GlamorizeHistogram(hist_MuonPtRelCSVVeto,2,2,24,0.6);
  
  TCanvas *Canvas_MuonPtRel_CSVTag_CSVVeto = new TCanvas("Canvas_MuonPtRel_CSVTag_CSVVeto","Canvas_MuonPtRel_CSVTag_CSVVeto",800,400);
  Canvas_MuonPtRel_CSVTag_CSVVeto->Divide(2,1);
  Canvas_MuonPtRel_CSVTag_CSVVeto->cd(1);
  //gPad->SetLogy(1);
  hist_MuonPtRelCSVTag->Draw();
  tb->DrawLatex(0.5,0.80,"Jets CSVv2>0.9");
  
  Canvas_MuonPtRel_CSVTag_CSVVeto->cd(2);
  //gPad->SetLogy(1);
  hist_MuonPtRelCSVVeto->Draw();
  tb->DrawLatex(0.5,0.80,"Jets CSVv2<0.9");
  
  Canvas_MuonPtRel_CSVTag_CSVVeto->SaveAs("Figures/MuonPtRel_CSVTag_CSVVeto.pdf");
  Canvas_MuonPtRel_CSVTag_CSVVeto->SaveAs("Figures/MuonPtRel_CSVTag_CSVVeto.png");
    

  
  
  TH1 *hist_Ratio_MuonPtRelCSVTag_MuonPtRel=RatioHistogram(hist_MuonPtRelCSVTag,hist_MuonPtRel,1);
  hist_Ratio_MuonPtRelCSVTag_MuonPtRel->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  hist_Ratio_MuonPtRelCSVTag_MuonPtRel->GetYaxis()->SetTitle("MuonPtRelCSVTag/MuonPtRel");
  hist_Ratio_MuonPtRelCSVTag_MuonPtRel->GetYaxis()->SetRangeUser(0.0,1.2);
  GlamorizeHistogram(hist_Ratio_MuonPtRelCSVTag_MuonPtRel,2,2,20,0.6);
  
  
  TH1 *hist_Ratio_MuonPtRelCSVVeto_MuonPtRel=RatioHistogram(hist_MuonPtRelCSVVeto,hist_MuonPtRel,1);
  hist_Ratio_MuonPtRelCSVVeto_MuonPtRel->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  hist_Ratio_MuonPtRelCSVVeto_MuonPtRel->GetYaxis()->SetTitle("MuonPtRelCSVVeto/MuonPtRel");
  hist_Ratio_MuonPtRelCSVVeto_MuonPtRel->GetYaxis()->SetRangeUser(0.0,1.2);
  GlamorizeHistogram(hist_Ratio_MuonPtRelCSVVeto_MuonPtRel,2,2,24,0.6);
  
  
  TCanvas *Canvas_RatioMuonPtRel_CSVTag_CSVVeto = new TCanvas("Canvas_RatioMuonPtRel_CSVTag_CSVVeto","Canvas_RatioMuonPtRel_CSVTag_CSVVeto",800,400);
  Canvas_RatioMuonPtRel_CSVTag_CSVVeto->Divide(2,1);
  
  Canvas_RatioMuonPtRel_CSVTag_CSVVeto->cd(1);
  //gPad->SetLogy(1);
  hist_Ratio_MuonPtRelCSVTag_MuonPtRel->Draw();
  
  
  Canvas_RatioMuonPtRel_CSVTag_CSVVeto->cd(2);
  //gPad->SetLogy(1);
  hist_Ratio_MuonPtRelCSVVeto_MuonPtRel->Draw();
  Canvas_RatioMuonPtRel_CSVTag_CSVVeto->SaveAs("Figures/RatioMuonPtRel_CSVTag_CSVVeto.pdf");
  Canvas_RatioMuonPtRel_CSVTag_CSVVeto->SaveAs("Figures/RatioMuonPtRel_CSVTag_CSVVeto.png");
  
  /***********************************************************************************/
  /***********************************************************************************/
  /***********************************************************************************/
  //CSV V2 Tagger Performance Plots on DATA
  //i)  For all Jets
  //ii) For Jets those have muons inside them
  /***********************************************************************************/
  /***********************************************************************************/
  /***********************************************************************************/


  // GET THE 3D HISTOGRAM FOR JETS
  //Get the 3D Histogram of EventCentrality, JetCSV, JetPt
  TH3D *hist_EventCentrality_JetCSV_JetPt=(TH3D*)file_in->Get("hist_Master_EventCentrality_JetCSV_JetPt");
  //Get the 3D Histogram of EventCentrality, MuonJetCSV, MuonJetPt
  TH3D *hist_EventCentrality_MuonJetCSV_MuonJetPt=(TH3D*)file_in->Get("hist_Master_EventCentrality_MuonJetCSV_MuonJetPt");


  //Check the bin number to be used for CSV working point
  cout<<" hist_EventCentrality_JetCSV_JetPt CSV working point "<< hist_EventCentrality_JetCSV_JetPt->GetYaxis()->FindBin(CSVWorkingPoint)<<endl;
  
  //Get the Jet Pt distribution of Tag Jets by Projection on z axis with CSV v2 > 0.9
  TH1* hist_JetPt_CSVTag =  hist_EventCentrality_JetCSV_JetPt->ProjectionZ("hist_JetPt_CSVTag",0,-1,Bin_CSV_WorkingPoint,Bin_CSV_Max);
  hist_JetPt_CSVTag->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_JetPt_CSVTag->GetYaxis()->SetTitle("Entries");
  rebinAsymmetric(hist_JetPt_CSVTag, NBins_JetPt_VarSize-1, JetPtBinEdges);
  GlamorizeHistogram(hist_JetPt_CSVTag,1,1,20,0.6);

  //Get the Jet Pt distribution of Veto Jets by Projection on z axis with CSV v2 < 0.9
  TH1* hist_JetPt_CSVVeto =  hist_EventCentrality_JetCSV_JetPt->ProjectionZ("hist_JetPt_CSVVeto",0,-1,Bin_CSV_Min,Bin_CSV_WorkingPoint-1);
  hist_JetPt_CSVVeto->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_JetPt_CSVVeto->GetYaxis()->SetTitle("Entries");
  rebinAsymmetric(hist_JetPt_CSVVeto, NBins_JetPt_VarSize-1, JetPtBinEdges);
  GlamorizeHistogram(hist_JetPt_CSVVeto,1,1,24,0.6);

  //Get the Jet Pt distribution of all Jets. It is required for making the ratio
  TH1* hist_JetPt_CSVFull =  hist_EventCentrality_JetCSV_JetPt->ProjectionZ("hist_JetPt_CSVFull",0,-1,0,-1);
  hist_JetPt_CSVFull->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_JetPt_CSVFull->GetYaxis()->SetTitle("Entries");
  rebinAsymmetric(hist_JetPt_CSVFull, NBins_JetPt_VarSize-1, JetPtBinEdges);
  GlamorizeHistogram(hist_JetPt_CSVFull,1,1,24,0.6);



  //Get the ratio ( Tag Jets / All Jets) as a function of Jet pT
  TH1* hist_Ratio_JetPt_CSVTag_CSVFull = RatioHistogram(hist_JetPt_CSVTag,hist_JetPt_CSVFull,1);
  hist_Ratio_JetPt_CSVTag_CSVFull->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_Ratio_JetPt_CSVTag_CSVFull->GetYaxis()->SetTitle("CSV Tag Efficiency");
  GlamorizeHistogram(hist_Ratio_JetPt_CSVTag_CSVFull,1,1,20,0.6);
  

  //Get the ratio ( Veto Jets / All Jets) as a function of Jet pT
  TH1* hist_Ratio_JetPt_CSVVeto_CSVFull = RatioHistogram(hist_JetPt_CSVVeto,hist_JetPt_CSVFull,1);
  hist_Ratio_JetPt_CSVVeto_CSVFull->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_Ratio_JetPt_CSVVeto_CSVFull->GetYaxis()->SetTitle("CSV Veto Efficiency");
  GlamorizeHistogram(hist_Ratio_JetPt_CSVVeto_CSVFull,1,1,24,0.6);

  
  //Get the MuonJet Pt distribution of Tag Jets by Projection on z axis with CSV v2 > 0.9
  TH1* hist_MuonJetPt_CSVTag =  hist_EventCentrality_MuonJetCSV_MuonJetPt->ProjectionZ("hist_MuonJetPt_CSVTag",0,-1,Bin_CSV_WorkingPoint,Bin_CSV_Max);
  hist_MuonJetPt_CSVTag->GetXaxis()->SetTitle("MuonJet p_{T} (GeV/c)");
  hist_MuonJetPt_CSVTag->GetYaxis()->SetTitle("Entries");
  rebinAsymmetric(hist_MuonJetPt_CSVTag, NBins_JetPt_VarSize-1, JetPtBinEdges);
  GlamorizeHistogram(hist_MuonJetPt_CSVTag,2,2,20,0.6);

  //Get the MuonJet Pt distribution of Veto Jets by Projection on z axis with CSV v2 < 0.9
  TH1* hist_MuonJetPt_CSVVeto =  hist_EventCentrality_MuonJetCSV_MuonJetPt->ProjectionZ("hist_MuonJetPt_CSVVeto",0,-1,Bin_CSV_Min,Bin_CSV_WorkingPoint-1);
  hist_MuonJetPt_CSVVeto->GetXaxis()->SetTitle("MuonJet p_{T} (GeV/c)");
  hist_MuonJetPt_CSVVeto->GetYaxis()->SetTitle("Entries");
  rebinAsymmetric(hist_MuonJetPt_CSVVeto, NBins_JetPt_VarSize-1, JetPtBinEdges);
  GlamorizeHistogram(hist_MuonJetPt_CSVVeto,2,2,24,0.6);


  //Get the Jet Pt distribution of all MuonJets. It is required for making the ratio
  TH1* hist_MuonJetPt_CSVFull =  hist_EventCentrality_MuonJetCSV_MuonJetPt->ProjectionZ("hist_MuonJetPt_CSVFull",0,-1,0,-1);
  hist_MuonJetPt_CSVFull->GetXaxis()->SetTitle("MuonJet p_{T} (GeV/c)");
  hist_MuonJetPt_CSVFull->GetYaxis()->SetTitle("Entries");
  rebinAsymmetric(hist_MuonJetPt_CSVFull, NBins_JetPt_VarSize-1, JetPtBinEdges);
  GlamorizeHistogram(hist_MuonJetPt_CSVFull,2,2,24,0.6);


  //Get the ratio ( Tag MuonJets / All MuonJets) as a function of MuonJet pT
  TH1* hist_Ratio_MuonJetPt_CSVTag_CSVFull = RatioHistogram(hist_MuonJetPt_CSVTag,hist_MuonJetPt_CSVFull,1);
  hist_Ratio_MuonJetPt_CSVTag_CSVFull->GetXaxis()->SetTitle("MuonJet p_{T} (GeV/c)");
  hist_Ratio_MuonJetPt_CSVTag_CSVFull->GetYaxis()->SetTitle("CSV Tag Efficiency");
  hist_Ratio_MuonJetPt_CSVTag_CSVFull->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_Ratio_MuonJetPt_CSVTag_CSVFull->GetXaxis()->SetRangeUser(0.0,500.0);
  GlamorizeHistogram(hist_Ratio_MuonJetPt_CSVTag_CSVFull,2,2,20,0.6);


  //Get the ratio ( Veto MuonJets / All MuonJets) as a function of MuonJet pT
  TH1* hist_Ratio_MuonJetPt_CSVVeto_CSVFull = RatioHistogram(hist_MuonJetPt_CSVVeto,hist_MuonJetPt_CSVFull,1);
  hist_Ratio_MuonJetPt_CSVVeto_CSVFull->GetXaxis()->SetTitle("MuonJet p_{T} (GeV/c)");
  hist_Ratio_MuonJetPt_CSVVeto_CSVFull->GetYaxis()->SetTitle("CSV Veto Efficiency");
  hist_Ratio_MuonJetPt_CSVVeto_CSVFull->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_Ratio_MuonJetPt_CSVVeto_CSVFull->GetXaxis()->SetRangeUser(0.0,500.0);
  GlamorizeHistogram(hist_Ratio_MuonJetPt_CSVVeto_CSVFull,2,2,24,0.6);


  //Draw The pT distribution of Tag Jet and Veto Jets
  //Pad 1 --> Tag Jets (Both All Jets and Muon Jets)
  //Pad 2 --> Veto Jets (Both All Jets and Muon Jets)
  TCanvas *Canvas_JetPt_CSVTag_CSVVeto = new TCanvas("Canvas_JetPt_CSVTag_CSVVeto","Canvas_JetPt_CSVTag_CSVVeto",800,400);
  Canvas_JetPt_CSVTag_CSVVeto->Divide(2,1);

  
  TLegend *lgd_JetPt_CSVTag = MyLegend(0.63,0.58,0.80,0.72);
  lgd_JetPt_CSVTag->AddEntry(hist_JetPt_CSVTag,"All Jets","P");
  lgd_JetPt_CSVTag->AddEntry(hist_MuonJetPt_CSVTag,"Muon Jets","P");


  TLegend *lgd_JetPt_CSVVeto = MyLegend(0.63,0.58,0.80,0.72);
  lgd_JetPt_CSVVeto->AddEntry(hist_JetPt_CSVVeto,"All Jets","P");
  lgd_JetPt_CSVVeto->AddEntry(hist_MuonJetPt_CSVVeto,"Muon Jets","P");

  TH1D *hist_JetPt_Ghost_ForCSV = Get_Ghost_Hist("hist_JetPt_Ghost_ForCSV","hist_JetPt_Ghost_ForCSV",500,0.0,500,0.01,10000,"PF Jet p_{T} (GeV/c)","dN/dp_{T} (GeV/c)^{-1}");

  
  
  Canvas_JetPt_CSVTag_CSVVeto->cd(1);
  gPad->SetLogy(1);
  hist_JetPt_Ghost_ForCSV->Draw();
  hist_JetPt_CSVTag->Draw("same");
  hist_MuonJetPt_CSVTag->Draw("same");
  tb->DrawLatex(0.63,0.80,"CSV v2 > 0.9");
  lgd_JetPt_CSVTag->Draw("same");
  

  
  Canvas_JetPt_CSVTag_CSVVeto->cd(2);
  gPad->SetLogy(1);
  hist_JetPt_Ghost_ForCSV->Draw();
  hist_JetPt_CSVVeto->Draw("same");
  hist_MuonJetPt_CSVVeto->Draw("same");
  tb->DrawLatex(0.63,0.80,"CSV v2 < 0.9");
  lgd_JetPt_CSVVeto->Draw("same");
  
  Canvas_JetPt_CSVTag_CSVVeto->SaveAs("Figures/JetPt_CSVTag_CSVVeto.pdf");
  Canvas_JetPt_CSVTag_CSVVeto->SaveAs("Figures/JetPt_CSVTag_CSVVeto.png");

  
    
  //Draw The Ratio of pT distribution of Tag Jets for both all Jets and muon Jets
  //Pad 1 --> Tag Jets / All Jets 
  //Pad 2 --> Tag MuonJets / All MuonJets
  TCanvas *Canvas_Ratio_JetPt_CSVTag_CSVFull = new TCanvas("Canvas_Ratio_JetPt_CSVTag_CSVFull","Canvas_Ratio_JetPt_CSVTag_CSVFull",800,400);
  Canvas_Ratio_JetPt_CSVTag_CSVFull->Divide(2,1);


  TH1D *hist_JetPtRatio_Ghost_ForCSVTag = Get_Ghost_Hist("hist_JetPtRatio_Ghost_ForCSVTag","hist_JetPtRatio_Ghost_ForCSVTag",500,0.0,500,0.0,1.2,"PF Jet p_{T} (GeV/c)","CSV Tag Eff.");
  TH1D *hist_JetPtRatio_Ghost_ForCSVVeto = Get_Ghost_Hist("hist_JetPtRatio_Ghost_ForCSVVeto","hist_JetPtRatio_Ghost_ForCSVVeto",500,0.0,500,0.0,1.2,"PF Jet p_{T} (GeV/c)","CSV Veto Eff.");

  Canvas_Ratio_JetPt_CSVTag_CSVFull->cd(1);
  hist_JetPtRatio_Ghost_ForCSVTag->Draw();
  hist_Ratio_JetPt_CSVTag_CSVFull->Draw("same");
  tb->DrawLatex(0.30,0.80,"All Jets, CSV v2 > 0.9");
 
  Canvas_Ratio_JetPt_CSVTag_CSVFull->cd(2);
  hist_JetPtRatio_Ghost_ForCSVTag->Draw();
  hist_Ratio_MuonJetPt_CSVTag_CSVFull->Draw("same");
  tb->DrawLatex(0.30,0.80,"MuonJets, CSV v2 > 0.9");
  
  Canvas_Ratio_JetPt_CSVTag_CSVFull->SaveAs("Figures/Ratio_JetPt_CSVTag_CSVFull.pdf");
  Canvas_Ratio_JetPt_CSVTag_CSVFull->SaveAs("Figures/Ratio_JetPt_CSVTag_CSVFull.png");

  
  //Draw The Ratio of pT distribution of Veto Jets for both all Jets and Muon Jets
  //Pad 1 --> Veto Jets / All Jets 
  //Pad 2 --> Veto MuonJets / All MuonJets

  TCanvas *Canvas_Ratio_JetPt_CSVVeto_CSVFull = new TCanvas("Canvas_Ratio_JetPt_CSVVeto_CSVFull","Canvas_Ratio_JetPt_CSVVeto_CSVFull",800,400);
  Canvas_Ratio_JetPt_CSVVeto_CSVFull->Divide(2,1);

  Canvas_Ratio_JetPt_CSVVeto_CSVFull->cd(1);
  hist_JetPtRatio_Ghost_ForCSVVeto->Draw();
  hist_Ratio_JetPt_CSVVeto_CSVFull->Draw("same");
  tb->DrawLatex(0.30,0.80,"All Jets, CSV v2 < 0.9");
  
  Canvas_Ratio_JetPt_CSVVeto_CSVFull->cd(2);
  hist_JetPtRatio_Ghost_ForCSVVeto->Draw();
  hist_Ratio_MuonJetPt_CSVVeto_CSVFull->Draw("same");
  tb->DrawLatex(0.30,0.80,"MuonJets, CSV v2 < 0.9");
 
  Canvas_Ratio_JetPt_CSVVeto_CSVFull->SaveAs("Figures/Ratio_JetPt_CSVVeto_CSVFull.pdf");
  Canvas_Ratio_JetPt_CSVVeto_CSVFull->SaveAs("Figures/Ratio_JetPt_CSVVeto_CSVFull.png");
  

  //Take only tag Jets i.e. Jets with CSVv2 > 0.9
  //Calculate the ratio of Muon Jets and All Jets as a function of Jet pT
  //

  TH1* hist_Ratio_CSVTagMuonJets_CSVTagAllJets = RatioHistogram(hist_MuonJetPt_CSVTag,hist_JetPt_CSVTag,1);
  hist_Ratio_CSVTagMuonJets_CSVTagAllJets->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_Ratio_CSVTagMuonJets_CSVTagAllJets->GetYaxis()->SetTitle("#frac{MuonJets}{AllJets}");
  hist_Ratio_CSVTagMuonJets_CSVTagAllJets->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_Ratio_CSVTagMuonJets_CSVTagAllJets->GetXaxis()->SetRangeUser(0.0,500.0);
  GlamorizeHistogram(hist_Ratio_CSVTagMuonJets_CSVTagAllJets,2,2,24,0.6);

  TCanvas *Canvas_Ratio_CSVTagMuonJets_CSVTagAllJets = new TCanvas("Ratio_CSVTagMuonJets_CSVTagAllJets","Ratio_CSVTagMuonJets_CSVTagAllJets",400,400);
  Canvas_Ratio_CSVTagMuonJets_CSVTagAllJets->Divide(1,1);

  TH1D *hist_ghost_Ratio_CSVTagMuonJets_CSVTagAllJets = Get_Ghost_Hist("hist_ghost_Ratio_CSVTagMuonJets_CSVTagAllJets","hist_ghost_Ratio_CSVTagMuonJets_CSVTagAllJets",500,0.0,500,0.0,1.2,"PF Jet p_{T} (GeV/c)","#frac{MuonJets}{AllJets}");
  
  Canvas_Ratio_CSVTagMuonJets_CSVTagAllJets->cd(1);
  hist_ghost_Ratio_CSVTagMuonJets_CSVTagAllJets->Draw();
  hist_Ratio_CSVTagMuonJets_CSVTagAllJets->Draw("same");
  //hist_MuonJetPt_CSVTag->Draw("same");
  tb->DrawLatex(0.63,0.80,"CSV v2 > 0.9");
  //lgd_JetPt_CSVTag->Draw("same");

  Canvas_Ratio_CSVTagMuonJets_CSVTagAllJets->SaveAs("Figures/Ratio_CSVTagMuonJets_CSVTagAllJets.pdf");
  Canvas_Ratio_CSVTagMuonJets_CSVTagAllJets->SaveAs("Figures/Ratio_CSVTagMuonJets_CSVTagAllJets.png");
  
  file_Out->cd();
  hist_JetCSV->Write();
  hist_MuonJetCSV->Write();

  hist_MuonPtRel->Write();
  hist_MuonPtRelCSVTag->Write();
  hist_MuonPtRelCSVVeto->Write();
  
  return;

}




void DrawEventHistograms(TFile *file_in, TFile *file_Out, TLatex *tb)
{

  setTDRStyle();
  TH1::SetDefaultSumw2();

  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.2);
  gStyle->SetOptStat(0);

  char LatexChar[400];


  cout<<endl<<endl<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<" ====================== Event Level Histogram ================================== "<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<endl<<endl<<endl;


  TH1D *hist_EvtVtxX=(TH1D*)file_in->Get("histEvtVtxX");
  TH1D *hist_EvtVtxY=(TH1D*)file_in->Get("histEvtVtxY");
  TH1D *hist_EvtVtxZ=(TH1D*)file_in->Get("histEvtVtxZ");

  
  TH1D *hist_Centrality=(TH1D*)file_in->Get("histCentrality");

  //========= Centrality Bin centres =========================//
  //========= Should they matter for the projection =========//

  if(PRINT_BIN_CENTRE ==1){
    for(int i =0;i<hist_Centrality->GetNbinsX()+3;i++)
      {
	cout<<" Centrality bin centre for bin : "<<i<<"    "<<hist_Centrality->GetBinCenter(i)<<" bin content "<<hist_Centrality->GetBinContent(i)<<endl;
      }
    
  cout<<endl;
  cout<<hist_Centrality->GetBinContent(hist_Centrality->FindBin(0))<<endl;
  cout<<hist_Centrality->GetBinContent(hist_Centrality->FindBin(20))<<endl;
  }
  //return;
  
  GlamorizeHistogram(hist_EvtVtxX,1,1,20,0.6);
  GlamorizeHistogram(hist_EvtVtxY,1,1,20,0.6);
  GlamorizeHistogram(hist_EvtVtxZ,1,1,20,0.6);
  GlamorizeHistogram(hist_Centrality,1,1,20,0.6);

  cout<<" entries in event vertex histogram "<< hist_EvtVtxX->GetEntries() <<endl;
  

  TCanvas *Canvas_EvtVtx_Centrality = new TCanvas("Canvas_EvtVtx_Centrality","Canvas_EvtVtx_Centrality",800,800);
  Canvas_EvtVtx_Centrality->Divide(2,2);


  Canvas_EvtVtx_Centrality->cd(1);
  gPad->SetLogy(1);
  hist_EvtVtxX->Draw();

  sprintf(LatexChar,"Events = %.0f",hist_EvtVtxX->GetEntries());
  tb->DrawLatex(0.20,0.80,LatexChar);
  sprintf(LatexChar,"Mean = %.2f",hist_EvtVtxX->GetMean());
  tb->DrawLatex(0.20,0.76,LatexChar);

  
  Canvas_EvtVtx_Centrality->cd(2);
  gPad->SetLogy(1);
  hist_EvtVtxY->Draw();
  sprintf(LatexChar,"Mean = %.2f",hist_EvtVtxY->GetMean());
  tb->DrawLatex(0.20,0.76,LatexChar);

  Canvas_EvtVtx_Centrality->cd(3);
  gPad->SetLogy(1);
  hist_EvtVtxZ->Draw();
  sprintf(LatexChar,"Events = %.0f",hist_EvtVtxZ->GetEntries());
  tb->DrawLatex(0.50,0.50,LatexChar);
  sprintf(LatexChar,"Mean = %.2f",hist_EvtVtxZ->GetMean());
  tb->DrawLatex(0.50,0.46,LatexChar);

  Canvas_EvtVtx_Centrality->cd(4);
  gPad->SetLogy(1);
  hist_Centrality->Draw();

  Canvas_EvtVtx_Centrality->SaveAs("Figures/EventHisto.pdf");
  Canvas_EvtVtx_Centrality->SaveAs("Figures/EventHisto.png");


  file_Out->cd();
  hist_EvtVtxX->Write();
  hist_EvtVtxY->Write();
  hist_EvtVtxZ->Write();
  hist_Centrality->Write();
  
  
  

}


void FoundJetStat(TFile *file_in, TFile *file_out, TLatex *tb, TLatex *tr)
{
  
  setTDRStyle();
  TH1::SetDefaultSumw2();
  
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.2);
  gStyle->SetOptStat(0);

  char LatexChar[400];
  
  
  cout<<endl<<endl<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<" ====================== Jets ================= ================================== "<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<endl<<endl<<endl;


  TH1D *hist_JetPt=(TH1D*)file_in->Get("histJetPt");
  TH1D *hist_JetEta=(TH1D*)file_in->Get("histJetEta");
  TH1D *hist_JetPhi=(TH1D*)file_in->Get("histJetPhi");

  hist_JetPt->SetStats(kFALSE);
  hist_JetEta->SetStats(kFALSE);
  hist_JetPhi->SetStats(kFALSE);

  GlamorizeHistogram(hist_JetPt,1,1,20,0.6);
  GlamorizeHistogram(hist_JetEta,1,1,20,0.6);
  GlamorizeHistogram(hist_JetPhi,1,1,20,0.6);
  
  
  TCanvas *Canvas_JetPtEtaPhi = new TCanvas("Canvas_JetPtEtaPhi","Canvas_JetPtEtaPhi",1200,400);
  Canvas_JetPtEtaPhi->Divide(3,1);

  Canvas_JetPtEtaPhi->cd(1);
  gPad->SetLogy(1);
  hist_JetPt->Draw();

  sprintf(LatexChar,"Jets = %.0f",hist_JetPt->GetEntries());
  tb->DrawLatex(0.50,0.80,LatexChar);

  Canvas_JetPtEtaPhi->cd(2);
  //gPad->SetLogy(1);
  //hist_JetEta->GetYaxis()->SetRangeUser(0.0,20000);
  hist_JetEta->GetYaxis()->SetRangeUser(0.0,hist_JetEta->GetMaximum()*2.0);
  hist_JetEta->Draw();


  Canvas_JetPtEtaPhi->cd(3);
  //gPad->SetLogy(1);
  //hist_JetPhi->GetYaxis()->SetRangeUser(0.0,20000);
  hist_JetPhi->GetYaxis()->SetRangeUser(0.0,hist_JetPhi->GetMaximum()*2.0);
  hist_JetPhi->Draw();


  Canvas_JetPtEtaPhi->SaveAs("Figures/JetPtEtaPhi.pdf");
  Canvas_JetPtEtaPhi->SaveAs("Figures/JetPtEtaPhi.png");



  //return;
  // no overflow
  Double_t JetPtEntries = hist_JetPt->GetEntries();
  Double_t JetPtInt = hist_JetPt->Integral(0,hist_JetPt->GetNbinsX());
  Double_t DiffPt = (JetPtInt - JetPtEntries);
  cout<<" 1D Pt: Jet Histograms Entries "<< JetPtEntries << " Integral   "<< JetPtInt <<" Diff (because not considering the overflow)"<< DiffPt <<endl;


  Double_t JetEtaEntries = hist_JetEta->GetEntries();
  Double_t JetEtaInt = hist_JetEta->Integral(0,hist_JetEta->GetNbinsX());
  Double_t DiffEta = (JetEtaInt - JetEtaEntries);
  cout<<" 1D Eta: Jet Histograms Entries "<< JetEtaEntries << " Integral   "<< JetEtaInt <<" Diff (because not considering the overflow)"<< DiffEta <<endl;



  Double_t JetPhiEntries = hist_JetPhi->GetEntries();
  Double_t JetPhiInt = hist_JetPhi->Integral(0,hist_JetPhi->GetNbinsX());
  Double_t DiffPhi = (JetPhiInt - JetPhiEntries);
  cout<<" 1D Phi: Jet Histograms Entries "<< JetPhiEntries << " Integral   "<< JetPhiInt <<" Diff (because not considering the overflow)"<< DiffPhi<<endl;

  //=====================================================================================//
  //======================= Basic Jet Plots with different Jet pT Cuts ==================//
  //=====================================================================================//
  

  
  TH1 *hist_JetPtCuts_JetPt[NJetPtCuts];
  TH1 *hist_JetPtCuts_JetEta[NJetPtCuts];
  TH1 *hist_JetPtCuts_JetPhi[NJetPtCuts];

  TH1 *hist_cloned_JetPtCuts_JetPt[NJetPtCuts];

  // Get the 3D Histogram from input file
  TH3D *hist_JetEta_JetPt_JetPhi = (TH3D*)file_in->Get("hist_Master_JetEta_JetPt_JetPhi");  
  Int_t RebinFac = 1;

  
  if(PRINT_BIN_CENTRE ==1){
    Print3DHistInfo(hist_JetEta_JetPt_JetPhi);
  }
  
  for(int i=0;i<NJetPtCuts;i++)
    {
      
      
      Int_t JetEtaMinBin = hist_JetEta_JetPt_JetPhi->GetXaxis()->FindBin(JetEtaMin);
      Int_t JetEtaMaxBin = hist_JetEta_JetPt_JetPhi->GetXaxis()->FindBin(JetEtaMax);

      cout<<"JetEta: ["<<JetEtaMin<<" ,  "<<JetEtaMax<<"]"<<endl;
      cout<<"JetEtaBin "<<JetEtaMinBin<<"   "<<JetEtaMaxBin<<endl;

      
      Int_t JetPtMinBin = hist_JetEta_JetPt_JetPhi->GetYaxis()->FindBin(JetPtCuts[i]);
      Int_t JetPtMaxBin = hist_JetEta_JetPt_JetPhi->GetYaxis()->FindBin(JetPtMax);
      
      cout<<"JetPt: ["<<JetPtMin<<" ,  "<<JetPtMax<<"]"<<endl;
      cout<<"JetPtBin "<<JetPtMinBin<<"   "<<JetPtMaxBin<<endl;

      
      Int_t JetPhiMinBin = hist_JetEta_JetPt_JetPhi->GetZaxis()->FindBin(JetPhiMin);
      Int_t JetPhiMaxBin = hist_JetEta_JetPt_JetPhi->GetZaxis()->FindBin(JetPhiMax);

      cout<<"JetPhi: ["<<JetPhiMin<<" ,  "<<JetPhiMax<<"]"<<endl;
      cout<<"JetPhiBin "<<JetPhiMinBin<<"   "<<JetPhiMaxBin<<endl;
      
      
      //======== Get the projection of histogram =========//
      
      //Jet Pt Cuts
      hist_JetPtCuts_JetPt[i] = hist_JetEta_JetPt_JetPhi->ProjectionY(Form("hist_JetPtCuts_JetPt%d",i), JetEtaMinBin, JetEtaMaxBin, JetPhiMinBin, JetPhiMaxBin);
      hist_JetPtCuts_JetPt[i]->GetXaxis()->SetTitle("PF Jet p_{T} (GeV/c)");
      hist_JetPtCuts_JetPt[i]->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");

      hist_cloned_JetPtCuts_JetPt[i] = (TH1*)hist_JetPtCuts_JetPt[i]->Clone(Form("hist_cloned_JetPtCuts_JetPt_%d",i));

      rebinAsymmetric(hist_JetPtCuts_JetPt[i], NBins_JetPt_VarSize-1, JetPtBinEdges);
      GlamorizeHistogram(hist_JetPtCuts_JetPt[i],ColourPtCut[i],ColourPtCut[i],20,0.6);
      
      
      //cout<<" Eta min "<< JetEtaMin<<" Eta max "<<JetEtaMax<<endl;
      //Get Entries will always give total number of entries as there is not pT cut on pt histogram
      //cout<<" Number of Jets Above pT: "<< JetPtCuts[i]<<" by entries  "<<hist_JetPtCuts_JetPt[i]->GetEntries()<<endl;
      //cout<<" Number of Jets Above pT: "<< JetPtCuts[i]<<" by integral  "<<hist_JetPtCuts_JetPt[i]->Integral(JetPtMinBin,JetPtMaxBin)<<endl;

      cout<<" Number of Jets Above pT: "<< JetPtCuts[i]<<" by integral  "<<hist_JetPtCuts_JetPt[i]->Integral(hist_JetPtCuts_JetPt[i]->FindBin(JetPtCuts[i]),hist_JetPtCuts_JetPt[i]->FindBin(JetPtMax),"width")<<endl;


      if(DEBUG_CODE==1){
	Print1DHistInfoAndInt(hist_JetPtCuts_JetPt[i],1);
	  }

      
      hist_JetPtCuts_JetEta[i] = hist_JetEta_JetPt_JetPhi->ProjectionX(Form("hist_JetPtCuts_JetEta%d",i),JetPtMinBin,JetPtMaxBin,JetPhiMinBin,JetPhiMaxBin);
      rebinAsymmetric(hist_JetPtCuts_JetEta[i], NBins_JetEta_VarSize-1, JetEtaBinEdges);
      hist_JetPtCuts_JetEta[i]->GetXaxis()->SetTitle("PF Jet #eta");
      hist_JetPtCuts_JetEta[i]->GetYaxis()->SetTitle("dN/d#eta");
      GlamorizeHistogram(hist_JetPtCuts_JetEta[i],ColourPtCut[i],ColourPtCut[i],20,0.6);

      cout<<" Eta "<< hist_JetPtCuts_JetEta[i]->GetEntries() <<"   "<<hist_JetPtCuts_JetEta[i]->Integral(hist_JetPtCuts_JetEta[i]->FindBin(JetEtaMin),hist_JetPtCuts_JetEta[i]->FindBin(JetEtaMax),"width")<<endl;

      if(DEBUG_CODE==2){
	for(int j =0;j <=hist_JetPtCuts_JetEta[i]->GetNbinsX()+1;j++)
	  {
	    
	    cout<<" Eta Hist bin "<< j <<"    "<<hist_JetPtCuts_JetEta[i]->GetBinContent(j)<<endl;
	    
	  }
	cout<<endl<<endl;
      }

      hist_JetPtCuts_JetPhi[i] = hist_JetEta_JetPt_JetPhi->ProjectionZ(Form("hist_JetPtCuts_JetPhi%d",i),JetEtaMinBin,JetEtaMaxBin,JetPtMinBin,JetPtMaxBin);
      rebinAsymmetric(hist_JetPtCuts_JetPhi[i], NBins_JetPhi_VarSize-1, JetPhiBinEdges);
      hist_JetPtCuts_JetPhi[i]->GetXaxis()->SetTitle("PF Jet #Phi");
      hist_JetPtCuts_JetPhi[i]->GetYaxis()->SetTitle("dN/d#Phi");
      GlamorizeHistogram(hist_JetPtCuts_JetPhi[i],ColourPtCut[i],ColourPtCut[i],20,0.6);


      cout<<" Phi "<< hist_JetPtCuts_JetPhi[i]->GetEntries() <<"   "<<hist_JetPtCuts_JetPhi[i]->Integral(JetPhiMinBin,JetPhiMaxBin,"width")<<endl;
      
      if(DEBUG_CODE==2){
	for(int j =0;j <=hist_JetPtCuts_JetPhi[i]->GetNbinsX()+1;j++)
	  {
	    
	    cout<<" Phi Hist bin "<< j <<"    "<<hist_JetPtCuts_JetPhi[i]->GetBinContent(j)<<endl;
	    
	  }
	cout<<endl<<endl;
      }
      
      
    }//Jet basic variables with different Jet Pt Cuts
  


  TCanvas *Canvas_JetPtCuts_JetPt_JetEta_JetPhi[NJetPtCuts];
  
  for(int i=0;i<NJetPtCuts;i++){
    
    Canvas_JetPtCuts_JetPt_JetEta_JetPhi[i] = new TCanvas(Form("Canvas_JetPtCuts_JetPt_JetEta_JetPhi_%d",i),Form("Canvas_JetPtCuts_JetPt_JetEta_JetPhi_%d",i),1200,400);
    Canvas_JetPtCuts_JetPt_JetEta_JetPhi[i]->Divide(3,1);
    
  }

  
  TGraph *line1_ptcut[NJetPtCuts];
  TGraph *line2_ptcut[NJetPtCuts];
  TGraph *line3_ptcut[NJetPtCuts];
    
  Double_t LineForEtaMin = JetEtaMin;
  Double_t LineForEtaMax = JetEtaMax;


  // because we want to plot Jet Pt starting from 0
  
  TH1D *hist_JetPt_Ghost;
  
  if(do_PbPb==1) hist_JetPt_Ghost = Get_Ghost_Hist("hist_JetPt_Ghost","hist_JetPt_Ghost",500,0.0,500,1.0,100000,"PF Jet p_{T} (GeV/c)","dN/dp_{T} (GeV/c)^{-1}");
  if(do_PbPb==0) hist_JetPt_Ghost = Get_Ghost_Hist("hist_JetPt_Ghost","hist_JetPt_Ghost",500,0.0,500,1.0,10000000,"PF Jet p_{T} (GeV/c)","dN/dp_{T} (GeV/c)^{-1}");
  
  //========= Canvas Loop ===========//
  
  for(int i=0;i<NJetPtCuts;i++)
    {
      line1_ptcut[i]= new TGraph(2);
      line1_ptcut[i]->SetLineColor(ColourPtCut[i]);
      line1_ptcut[i]->SetPoint(0,JetPtCuts[i],0);
      line1_ptcut[i]->SetPoint(1,JetPtCuts[i],hist_JetPtCuts_JetPt[i]->GetMaximum());


      line2_ptcut[i]= new TGraph(2);
      line2_ptcut[i]->SetLineColor(ColourPtCut[i]);
      line2_ptcut[i]->SetPoint(0,LineForEtaMin,0);
      line2_ptcut[i]->SetPoint(1,LineForEtaMin,hist_JetPtCuts_JetEta[i]->GetMaximum());

      
      line3_ptcut[i]= new TGraph(2);
      line3_ptcut[i]->SetLineColor(ColourPtCut[i]);
      line3_ptcut[i]->SetPoint(0,LineForEtaMax,0);
      line3_ptcut[i]->SetPoint(1,LineForEtaMax,hist_JetPtCuts_JetEta[i]->GetMaximum());



      Canvas_JetPtCuts_JetPt_JetEta_JetPhi[i]->cd(1);
      gPad->SetLogy(1);
      hist_JetPt_Ghost->Draw();
      hist_JetPtCuts_JetPt[i]->Draw("same");      
      line1_ptcut[i]->Draw("lsame");

      sprintf(LatexChar,"(Jet p_{T} > %0.f GeV/c)",JetPtCuts[i]);
      tb->DrawLatex(0.60,0.75,LatexChar);
      sprintf(LatexChar,"(%.0f Jets)",hist_JetPtCuts_JetEta[i]->GetEntries());
      tb->DrawLatex(0.60,0.70,LatexChar);
      

      Canvas_JetPtCuts_JetPt_JetEta_JetPhi[i]->cd(2);
      hist_JetPtCuts_JetEta[i]->Draw();
      line2_ptcut[i]->Draw("lsame");
      line3_ptcut[i]->Draw("lsame");
	
      Canvas_JetPtCuts_JetPt_JetEta_JetPhi[i]->cd(3);
      hist_JetPtCuts_JetPhi[i]->GetYaxis()->SetRangeUser(0.0,hist_JetPtCuts_JetEta[i]->GetMaximum());
      hist_JetPtCuts_JetPhi[i]->Draw();


      Canvas_JetPtCuts_JetPt_JetEta_JetPhi[i]->SaveAs(Form("Figures/JetPtAbove_%0.f_JetPt_JetEta_JetPhi.pdf",JetPtCuts[i]));
      Canvas_JetPtCuts_JetPt_JetEta_JetPhi[i]->SaveAs(Form("Figures/JetPtAbove_%0.f_JetPt_JetEta_JetPhi.pdf",JetPtCuts[i]));



      
    }//canvas loop


  //return;
  /***********************************************************************************************/
  /***********************************************************************************************/
  // COMPARING THE PROJECTIONS FROM 3D HISTOS TO THE 1D HISTOS
  // THIS IS TO TEST THE ASYMATRIC REBINING
  /***********************************************************************************************/
  /***********************************************************************************************/

  /*
  new TCanvas;
  hist_JetPt->SetLineColor(2);
  hist_JetPt->SetMarkerColor(2);
  hist_JetPt->Draw();
  hist_JetPtCuts_JetPt[0]->Draw("same");


  new TCanvas;
  hist_JetEta->SetLineColor(2);
  hist_JetEta->SetMarkerColor(2);
  hist_JetEta->Scale(1.0/hist_JetEta->GetBinWidth(0));
  hist_JetEta->Draw();
  hist_JetPtCuts_JetEta[0]->Draw("same");


  new TCanvas;
  hist_JetPhi->SetLineColor(2);
  hist_JetPhi->SetMarkerColor(2);
  hist_JetPhi->Scale(1.0/hist_JetPhi->GetBinWidth(0));
  hist_JetPhi->Draw();
  hist_JetPtCuts_JetPhi[0]->Draw("same");


  cout<<endl<<endl;

  cout<<" 1D Histogram "<<hist_JetPt->GetEntries()<<"    "<<hist_JetPt->Integral(0,hist_JetPt->GetNbinsX()+1)<<endl;
  cout<<" cloned hist "<<hist_cloned_JetPtCuts_JetPt[0]->GetEntries()<<"    "<<hist_cloned_JetPtCuts_JetPt[0]->Integral(0,hist_cloned_JetPtCuts_JetPt[0]->GetNbinsX()+1,"width")<<endl;
  cout<<" rebinned hist "<<hist_JetPtCuts_JetPt[0]->GetEntries()<<"    "<<hist_JetPtCuts_JetPt[0]->Integral(0,hist_JetPtCuts_JetPt[0]->GetNbinsX()+1,"width")<<endl;
  
  */
  /***********************************************************************************************/
  /***********************************************************************************************/
  // THE ASYMATRIC REBINING SEEMS TO WORK FINE
  /***********************************************************************************************/
  /***********************************************************************************************/
  


  
  //return;

  


  cout<<endl<<endl<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<" ====================== Muons ================= ================================== "<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<endl<<endl<<endl;

  TH1D *hist_MuonPt=(TH1D*)file_in->Get("histMuonPt");
  TH1D *hist_MuonEta=(TH1D*)file_in->Get("histMuonEta");
  TH1D *hist_MuonPhi=(TH1D*)file_in->Get("histMuonPhi");


  hist_MuonPt->SetStats(kFALSE);
  hist_MuonEta->SetStats(kFALSE);
  hist_MuonPhi->SetStats(kFALSE);


  GlamorizeHistogram(hist_MuonPt,1,1,20,0.6);
  GlamorizeHistogram(hist_MuonEta,1,1,20,0.6);
  GlamorizeHistogram(hist_MuonPhi,1,1,20,0.6);
  
  
  TCanvas *Canvas_MuonPtEtaPhi = new TCanvas("Canvas_MuonPtEtaPhi","Canvas_MuonPtEtaPhi",1200,400);
  Canvas_MuonPtEtaPhi->Divide(3,1);
  
  Canvas_MuonPtEtaPhi->cd(1);
  gPad->SetLogy(1);
  hist_MuonPt->Draw();
  
  sprintf(LatexChar,"Muons = %.0f",hist_MuonPt->GetEntries());
  tb->DrawLatex(0.50,0.80,LatexChar);

  Canvas_MuonPtEtaPhi->cd(2);
  hist_MuonEta->GetYaxis()->SetRangeUser(0.0,hist_MuonEta->GetMaximum()*300.0);
  hist_MuonEta->Draw();
  

  Canvas_MuonPtEtaPhi->cd(3);
  hist_MuonPhi->GetXaxis()->SetTitle("Muon #phi");
  hist_MuonPhi->GetYaxis()->SetRangeUser(0.0,hist_MuonPhi->GetMaximum()*200.0);
  hist_MuonPhi->Draw();


  Canvas_MuonPtEtaPhi->SaveAs("Figures/MuonPtEtaPhi.pdf");
  Canvas_MuonPtEtaPhi->SaveAs("Figures/MuonPtEtaPhi.png");

  
  cout<<endl<<endl<<endl;
  cout<<" ================================================================================== "<<endl;
  cout<<" ================= Combination Plots ============================================== "<<endl;
  cout<<" ================  Starting from Jets ============================================= "<<endl;
  cout<<" ================================================================================== "<<endl;
  cout<<endl<<endl<<endl;
  
  
  TH1D *hist_JetMuonDeltaEta=(TH1D*)file_in->Get("histMuonJetDEta");
  TH1D *hist_JetMuonDeltaPhi=(TH1D*)file_in->Get("histMuonJetDPhi");
  TH1D *hist_JetMuonDeltaR=(TH1D*)file_in->Get("histMuonJetDR");


  GlamorizeHistogram(hist_JetMuonDeltaEta,2,2,20,0.6);
  GlamorizeHistogram(hist_JetMuonDeltaPhi,2,2,20,0.6);
  GlamorizeHistogram(hist_JetMuonDeltaR,2,2,20,0.6);
  
  hist_JetMuonDeltaEta->SetStats(kFALSE);
  hist_JetMuonDeltaPhi->SetStats(kFALSE);
  hist_JetMuonDeltaR->SetStats(kFALSE);

  TCanvas *Canvas_JetMuonDeltaEtaPhiR = new TCanvas("Canvas_JetMuonDeltaEtaPhiR","Canvas_JetMuonDeltaEtaPhiR",1200,400);
  Canvas_JetMuonDeltaEtaPhiR->Divide(3,1);

  Canvas_JetMuonDeltaEtaPhiR->cd(1);
  hist_JetMuonDeltaEta->Draw();

  Canvas_JetMuonDeltaEtaPhiR->cd(2);
  hist_JetMuonDeltaPhi->Draw();

  Canvas_JetMuonDeltaEtaPhiR->cd(3);
  hist_JetMuonDeltaR->Draw();



  Canvas_JetMuonDeltaEtaPhiR->SaveAs("Figures/JetMuonDeltaEtaPhiR.pdf");
  Canvas_JetMuonDeltaEtaPhiR->SaveAs("Figures/JetMuonDeltaEtaPhiR.png");

  //Name Convention
  //JetMuon --> Matching starts from Jets
  //JetPt --> This is a Jet Pt Histo

  TH1D *hist_JetMuon_JetPt=(TH1D*)file_in->Get("histMuonJetPt");
  TH1D *hist_JetMuon_PtRatio_JetsWithMuon_AllJets=(TH1D*)file_in->Get("hist_JetPtRatio_MuonJet_AllJets");
  
  GlamorizeHistogram(hist_JetMuon_JetPt,2,2,20,0.6);
  GlamorizeHistogram(hist_JetMuon_PtRatio_JetsWithMuon_AllJets,2,2,20,0.6);
 
  hist_JetMuon_JetPt->SetStats(kFALSE);
  hist_JetMuon_PtRatio_JetsWithMuon_AllJets->SetStats(kFALSE);

  
  TCanvas *Canvas_JetMuon_PtRatio_JetsWithMuon_AllJets = new TCanvas("Canvas_JetMuon_PtRatio_JetsWithMuon_AllJets","Canvas_JetMuon_PtRatio_JetsWithMuon_AllJets",800,400);
  Canvas_JetMuon_PtRatio_JetsWithMuon_AllJets->Divide(2,1);


  TLegend *lgd_JetMuon_PtRatio_JetsWithMuon_AllJets = MyLegend(0.50,0.72,0.66,0.86);

  lgd_JetMuon_PtRatio_JetsWithMuon_AllJets->AddEntry(hist_JetPt,"Jets","P");
  lgd_JetMuon_PtRatio_JetsWithMuon_AllJets->AddEntry(hist_JetMuon_JetPt,"Jets with muon","P");
  
  Canvas_JetMuon_PtRatio_JetsWithMuon_AllJets->cd(1);
  gPad->SetLogy(1);
  hist_JetPt->Draw();
  hist_JetMuon_JetPt->Draw("same");
  
  sprintf(LatexChar,"Jets = %.0f",hist_JetPt->GetEntries());
  tb->DrawLatex(0.50,0.60,LatexChar);
  sprintf(LatexChar,"Jets-Muon = %.0f",hist_JetMuon_JetPt->GetEntries());
  tr->DrawLatex(0.50,0.56,LatexChar);

  lgd_JetMuon_PtRatio_JetsWithMuon_AllJets->Draw("same");
  
  Canvas_JetMuon_PtRatio_JetsWithMuon_AllJets->cd(2);
  gPad->SetLogy(1);
  hist_JetMuon_PtRatio_JetsWithMuon_AllJets->Draw();

  Canvas_JetMuon_PtRatio_JetsWithMuon_AllJets->SaveAs("Figures/JetMuon_PtRatio_JetsWithMuon_AllJets.png");
  Canvas_JetMuon_PtRatio_JetsWithMuon_AllJets->SaveAs("Figures/JetMuon_PtRatio_JetsWithMuon_AllJets.pdf");


  
  //=======================================================================================================//
  //======================= Found Jet Statistics in different Centrality bins ==============================// 
  //======================= [0,10,30,50,100] ==============================================================//
  //=======================================================================================================//

  //All Jets
  //Get the 3D Histogram of EventCentrality, JetEta, JetPt 
  TH3D *hist_EventCentrality_JetEta_JetPt=(TH3D*)file_in->Get("hist_Master_EventCentrality_JetEta_JetPt");

  //Muon Jets
  //Get the 3D Histogram of EventCentrality, MuonJet Pt, MuonPt
  TH3D *hist_EventCentrality_JetPt_MuonPt=(TH3D*)file_in->Get("hist_Master_EventCentrality_JetPt_MuonPt");

  
  //Centrality bins
  /*******************************************************************************************/
  // Centrality are filled from 0 to 100 with bin Centres as 0, 0.5, 1.5, 2.0, 2.5 ........
  //....99.5,100. This is because hiBin is defined from 0 to 200 in Hi Cent Analyzer
  //
  /*******************************************************************************************/

  

  //========== Get the Jet pt histogram for different event centrality cuts ======================//
  //========= Array of Jet Pt
  TH1 *hist_CentBin_JetPt[NCentBins]; //Jet Pt
  TH1 *hist_JetMuon_CentBin_JetPt[NCentBins]; // Muon Jet Pt
  TH1 *hist_Ratio_CentBin_JetMuonPt_JetPt[NCentBins]; // Ratio of Muon Jet Pt and All Jet Pt

  //Loop over centrality bins
  for(int i=0;i<NCentBins;i++)
    {
      cout<< "cent bin "<< CentBins[i]<<" - "<<CentBins[i+1]<<" % "<<endl;
      
      Int_t CentBinMin = hist_EventCentrality_JetEta_JetPt->GetXaxis()->FindBin(CentBins[i]);
      Int_t CentBinMax = hist_EventCentrality_JetEta_JetPt->GetXaxis()->FindBin(CentBins[i+1]);

      cout<< "hi bin "<< CentBinMin <<" - "<<CentBinMax<<endl;
      
      Int_t JetEtaBinMin = hist_EventCentrality_JetEta_JetPt->GetYaxis()->FindBin(JetEtaMin);
      Int_t JetEtaBinMax = hist_EventCentrality_JetEta_JetPt->GetYaxis()->FindBin(JetEtaMax);
      
      Int_t MuonPtBinMin = hist_EventCentrality_JetPt_MuonPt->GetYaxis()->FindBin(MuonPtMin);
      Int_t MuonPtBinMax = hist_EventCentrality_JetPt_MuonPt->GetYaxis()->FindBin(MuonPtMax);

      //======== Get the projection of histogram =========//
      //Jet pT in different Cent Bins
      hist_CentBin_JetPt[i] =  hist_EventCentrality_JetEta_JetPt->ProjectionZ(Form("hist_CentBin_JetPt_Bin%d",i),CentBinMin,CentBinMax,JetEtaBinMin,JetEtaBinMax);
      hist_CentBin_JetPt[i]->GetYaxis()->SetTitle("Entries");
      rebinAsymmetric(hist_CentBin_JetPt[i], NBins_JetPt_VarSize-1, JetPtBinEdges);
      GlamorizeHistogram(hist_CentBin_JetPt[i],1,1,20,0.6);

      //MuonJet pT in different Cent Bins
      hist_JetMuon_CentBin_JetPt[i] =  hist_EventCentrality_JetPt_MuonPt->ProjectionY(Form("hist_JetMuon_CentBin_JetPt_Bin%d",i),CentBinMin,CentBinMax,MuonPtBinMin,MuonPtBinMax);
      hist_JetMuon_CentBin_JetPt[i]->GetYaxis()->SetTitle("Entries");
      rebinAsymmetric(hist_JetMuon_CentBin_JetPt[i], NBins_JetPt_VarSize-1, JetPtBinEdges);
      GlamorizeHistogram(hist_JetMuon_CentBin_JetPt[i],2,2,20,0.6);

      //======== ratio of Jet pT in Cent Bins and MuonJet pT Cent Bins ===========//
      hist_Ratio_CentBin_JetMuonPt_JetPt[i] = RatioHistogram(hist_JetMuon_CentBin_JetPt[i],hist_CentBin_JetPt[i],1);
      hist_Ratio_CentBin_JetMuonPt_JetPt[i]->GetYaxis()->SetTitle("Ratio");
      hist_Ratio_CentBin_JetMuonPt_JetPt[i]->SetName(Form("hist_Ratio_CentBin_JetMuonPt_JetPt_Bin%d",i));
      hist_Ratio_CentBin_JetMuonPt_JetPt[i]->SetTitle(Form("hist_Ratio_CentBin_JetMuonPt_JetPt_Bin%d",i));
      GlamorizeHistogram(hist_Ratio_CentBin_JetMuonPt_JetPt[i],2,2,21,0.6); 
      
    }

  TH1D *hist_JetPt_Ghost_ForCentBins = Get_Ghost_Hist("hist_JetPt_Ghost_ForCentBins","hist_JetPt_Ghost_ForCentBins",500,0.0,500,0.01,10000,"PF Jet p_{T} (GeV/c)","dN/dp_{T} (GeV/c)^{-1}");
  TH1D *hist_JetPtRatio_Ghost_ForCentBins = Get_Ghost_Hist("hist_JetPtRatio_Ghost_ForCentBins","hist_JetPtRatio_Ghost_ForCentBins",500,0.0,500,0.0,1.2,"PF Jet p_{T} (GeV/c)","Ratio(#frac{MuonJets}{AllJets})");


  //================== Canvas with 4 Pads =========================================================//
  //================== Jet pT and MuonJet pT are drawn in different cent. bins ====================//
  TCanvas *Canvas_CentBin_JetPt = new TCanvas("Canvas_CentBin_JetPt","Canvas_CentBin_JetPt",1600,400);
  Canvas_CentBin_JetPt->Divide(4,1);

  for(int i=0;i<NCentBins;i++)
    {
      Int_t j = NCentBins -i;
      Canvas_CentBin_JetPt->cd(j);
      gPad->SetLogy();
      hist_JetPt_Ghost_ForCentBins->Draw();
      hist_CentBin_JetPt[i]->Draw("same");
      hist_JetMuon_CentBin_JetPt[i]->Draw("same");
      sprintf(LatexChar,"(%.0f Jets)",hist_CentBin_JetPt[i]->GetEntries());
      tb->DrawLatex(0.60,0.70,LatexChar);
      sprintf(LatexChar,"(%.0f Jets)",hist_JetMuon_CentBin_JetPt[i]->GetEntries());
      tr->DrawLatex(0.60,0.64,LatexChar);
      lgd_JetMuon_PtRatio_JetsWithMuon_AllJets->Draw("same");
      
      tb->DrawLatex(0.70,0.92,Form("Cent. %0d - %0d %%",CentBins[i],CentBins[i+1]));

      cout<<hist_CentBin_JetPt[i]->GetEntries()<<"  "<<hist_JetMuon_CentBin_JetPt[i]->GetEntries()<<endl;
      
    }

    Canvas_CentBin_JetPt->SaveAs("Figures/CentBin_JetPt.png");
    Canvas_CentBin_JetPt->SaveAs("Figures/CentBin_JetPt.pdf");


    //================== Canvas with 4 Pads =========================================================//
    //================== Ratio of Jet pT and MuonJet pT are drawn in different cent. bins ====================//
    TCanvas *Canvas_CentBin_Ratio_JetMuonPt_JetPt = new TCanvas("Canvas_CentBin_Ratio_JetMuonPt_JetPt","Canvas_CentBin_Ratio_JetMuonPt_JetPt",1600,400);
    Canvas_CentBin_Ratio_JetMuonPt_JetPt->Divide(4,1);

    
    for(int i=0;i<NCentBins;i++)
    {
      Int_t j = NCentBins -i;
      Canvas_CentBin_Ratio_JetMuonPt_JetPt->cd(j);
      //gPad->SetLogy();
      hist_JetPtRatio_Ghost_ForCentBins->Draw();
      hist_Ratio_CentBin_JetMuonPt_JetPt[i]->Draw("same");
      tb->DrawLatex(0.70,0.92,Form("Cent. %0d - %0d %%",CentBins[i],CentBins[i+1]));
    }
  
    Canvas_CentBin_Ratio_JetMuonPt_JetPt->SaveAs("Figures/CentBin_Ratio_JetMuonPt_JetPt.pdf");
    Canvas_CentBin_Ratio_JetMuonPt_JetPt->SaveAs("Figures/CentBin_Ratio_JetMuonPt_JetPt.png");

    
    
    //=====================================================================================//
    //======================== Calculate uncorrected R_{CP} for muon Jets and All Jets ====//
    //======================== As a function of pT ========================================//
    //======================== Yield Cent [0-10-30-50]/Yield Cent [50-100] ================//
    //=====================================================================================//
    
    TH1 *hist_RCP_UnCorr_CentBin_JetPt[NCentBins];
    TH1 *hist_RCP_UnCorr_CentBin_MuonJetPt[NCentBins];
    
    const Double_t CentBinWidth[4] = {10.0,20.0,20.0,50.0};
    
  
    //Loop over centrality bins
    for(int i=0;i<NCentBins;i++)
      {
	
	hist_CentBin_JetPt[i]->Scale(1.0/CentBinWidth[i]);
	
	hist_RCP_UnCorr_CentBin_JetPt[i] = RatioHistogram(hist_CentBin_JetPt[i],hist_CentBin_JetPt[3],1);
	hist_RCP_UnCorr_CentBin_JetPt[i]->GetYaxis()->SetTitle("R_{CP}");
	hist_RCP_UnCorr_CentBin_JetPt[i]->SetName(Form("hist_RCP_UnCorr_CentBin_JetPt%d",i));
	hist_RCP_UnCorr_CentBin_JetPt[i]->SetTitle(Form("hist_RCP_UnCorr_CentBin_JetPt%d",i));
	GlamorizeHistogram(hist_RCP_UnCorr_CentBin_JetPt[i],1,1,21,0.6);
	
	hist_JetMuon_CentBin_JetPt[i]->Scale(1.0/CentBinWidth[i]);
	
	
	hist_RCP_UnCorr_CentBin_MuonJetPt[i] = RatioHistogram(hist_JetMuon_CentBin_JetPt[i],hist_JetMuon_CentBin_JetPt[3],1);
	hist_RCP_UnCorr_CentBin_MuonJetPt[i]->GetYaxis()->SetTitle("R_{CP}");
	hist_RCP_UnCorr_CentBin_MuonJetPt[i]->SetName(Form("hist_RCP_UnCorr_CentBin_MuonJetPt%d",i));
	hist_RCP_UnCorr_CentBin_MuonJetPt[i]->SetTitle(Form("hist_RCP_UnCorr_CentBin_MuonJetPt%d",i));
	GlamorizeHistogram(hist_RCP_UnCorr_CentBin_MuonJetPt[i],2,2,21,0.6); 
	

	
      }
    


    TCanvas *Canvas_RCP_UnCorr_CentBin_JetPt = new TCanvas("Canvas_RCP_UnCorr_CentBin_JetPt","Canvas_RCP_UnCorr_CentBin_JetPt",1600,400);
    Canvas_RCP_UnCorr_CentBin_JetPt->Divide(4,1);
    
    TH1D *hist_Ghost_RCP_UnCorr_CentBin_JetPt = Get_Ghost_Hist("hist_Ghost_RCP_UnCorr_CentBin_JetPt","hist_Ghost_RCP_UnCorr_CentBin_JetPt",500,0.0,500,0.0,1.7,"PF Jet p_{T} (GeV/c)","Uncorrected R_{CP}");
  
    for(int i=0;i<NCentBins;i++)
      {
	Int_t j = NCentBins -i;
	Canvas_RCP_UnCorr_CentBin_JetPt->cd(j);
	//gPad->SetLogy();
	hist_Ghost_RCP_UnCorr_CentBin_JetPt->Draw();
	hist_RCP_UnCorr_CentBin_JetPt[i]->Draw("same");
	hist_RCP_UnCorr_CentBin_MuonJetPt[i]->Draw("same");
	lgd_JetMuon_PtRatio_JetsWithMuon_AllJets->Draw("same");
	tb->DrawLatex(0.70,0.92,Form("Cent. %0d - %0d %%",CentBins[i],CentBins[i+1]));
      }
    
    Canvas_RCP_UnCorr_CentBin_JetPt->SaveAs("Figures/RCP_UnCorr_CentBin_JetPt.pdf");
    Canvas_RCP_UnCorr_CentBin_JetPt->SaveAs("Figures/RCP_UnCorr_CentBin_JetPt.png");






    //Write histograms in the output root file
    file_out->cd();
    hist_JetPt->Write();
    hist_JetEta->Write();
    hist_JetPhi->Write();
    

    

}




void GlamorizeHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize)
{
  InHist->SetLineColor(LineColor);
  InHist->SetMarkerColor(MarkerColor);
  InHist->SetMarkerStyle(MarkerStyle);
  InHist->SetMarkerSize(MarkerSize);
  InHist->GetXaxis()->SetNdivisions(505);
  InHist->GetXaxis()->SetLabelSize(0.06);
  InHist->GetXaxis()->SetTitleOffset(1.4);
  InHist->GetXaxis()->SetTitleSize(0.06);
  InHist->GetYaxis()->SetTitleSize(0.06);
  
}



TLegend *MyLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2)
{

  TLegend *lgd_GenMuonGenJetFrac = new TLegend(x1,y1,x2,y2,"","brNDC");
  
  lgd_GenMuonGenJetFrac->SetBorderSize(0);
  lgd_GenMuonGenJetFrac->SetTextFont(42);
  //lgd_GenMuonGenJetFrac->SetTextSize(0.042);
  lgd_GenMuonGenJetFrac->SetTextSize(0.06);
  lgd_GenMuonGenJetFrac->SetLineColor(1);
  lgd_GenMuonGenJetFrac->SetLineStyle(1);
  lgd_GenMuonGenJetFrac->SetLineWidth(1);
  lgd_GenMuonGenJetFrac->SetFillColor(19);
  lgd_GenMuonGenJetFrac->SetFillStyle(0);
  
  return lgd_GenMuonGenJetFrac;
  

}



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






/*
 * Checker that new bin boundaries correspond to old ones
 *
 *  Arguments:
 *   const int nCheckedBins = Number of new bins to be checked
 *   const double *checkedBins = Bin boundaries to be checked
 *   TAxis *originalAxis = Original axis against with the new bins are checked
 *
 *   return: True, if all the new bin boundaries can be found from the original axis. False if not.
 */
bool checkBinBoundaries(const int nCheckedBins, const double *checkedBins, TAxis *originalAxis){

  // Flag, if the current bin is a bin boundary in the histogram to be rebinned
  bool binOK = false;

  // First, check that the bin boundaries for the rebinned histogram match with the old bin boundaries
  for(int iCheckedBin = 0; iCheckedBin < nCheckedBins + 1; iCheckedBin++){
    binOK = false;
    for(int iOldBin = 1; iOldBin <= originalAxis->GetNbins()+1; iOldBin++){

      // We the bin edge is close enough to one original bin, accept the bin
      if(TMath::Abs(originalAxis->GetBinLowEdge(iOldBin)-checkedBins[iCheckedBin]) < 1e-4){
        binOK = true;
        break;
      }

    } // Loop over bins in the original axis
    if(!binOK){ // If the bin is not in original histogram, print error message and return false
      std::cout << "The bin boundary " << checkedBins[iCheckedBin] << " is not a bin boundary in the original histogram!" << std::endl;
      return false;
    }
  } // Loop over bins to be checked

  // If all is good, return true
  return true;
}

/*
 * Rebin one dimensional histogram with asymmetric bin edges
 *
 * Arguments:
 *  TH1* histogram = Histogram to be rebinned
 *  const int nBins = Number of bins for the rebinned histogram
 *  const double* binEdges = Bin edges for the rebinned histogram
 */


void rebinAsymmetric(TH1* histogram, const int nBins, const double* binEdges){



  // First, check that the new bin boundaries are also bin boundaries in the original histogram
  bool binsGood = checkBinBoundaries(nBins,binEdges,histogram->GetXaxis());
  if(!binsGood){
    cout << "Cannot rebin histogram " << histogram->GetName() << " because given bin borders do not match with the bin borders of the original histogram!" << endl;
    return;
  }

  // Clone the original histogram
  TH1D *clonedHistogram = (TH1D*) histogram->Clone("thisClone");

  // Set the new binning for histogram (destroys content in each bin)
  histogram->SetBins(nBins,binEdges);

  for(int iBin = 0; iBin <= histogram->GetNbinsX()+1; iBin++){

    histogram->SetBinContent(iBin,0.0);
    histogram->SetBinError(iBin,0.0);
  }

  
  // Add the contents back to the histogram that was rebinned
  double binContent, binError, binCenter, oldContent, oldError;
  int newBin;
  for(int iBin = 0; iBin <= clonedHistogram->GetNbinsX()+1; iBin++){

    // Read the contents from the non-rebinned histogram
    binContent = clonedHistogram->GetBinContent(iBin);
    binError = clonedHistogram->GetBinError(iBin);
    binCenter = clonedHistogram->GetBinCenter(iBin);

    // Add the contents to the rebinned histgram
    newBin = histogram->FindBin(binCenter);
    oldContent = histogram->GetBinContent(newBin);
    oldError = histogram->GetBinError(newBin);

    histogram->SetBinContent(newBin,binContent+oldContent);
    histogram->SetBinError(newBin,TMath::Sqrt(binError*binError+oldError*oldError));
  }

  // Normalize the bin contents to bin width
  double binWidth;
  for(int iBin = 0; iBin <= histogram->GetNbinsX()+1; iBin++){


    binWidth = histogram->GetBinWidth(iBin);
    binContent = histogram->GetBinContent(iBin);
    binError = histogram->GetBinError(iBin);

    //cout<<binWidth<<"  "<<binContent<<"  "<<binError<<endl;

    
    histogram->SetBinContent(iBin,binContent/binWidth);
    histogram->SetBinError(iBin,binError/binWidth);
  }

  // Delete the clone
  delete clonedHistogram;
}



TH1D *Get_Ghost_Hist(const char *Name, const char *Title, Int_t NBins, Double_t XMin, Double_t XMax, Double_t YMin, Double_t YMax, const char *XTitle, const char *YTitle)
{
  //const int NBins = 100.0;
  
  TH1D *hist_Ghost = new TH1D(Name,Title,NBins,XMin,XMax);
  hist_Ghost->GetXaxis()->SetNdivisions(505);
  hist_Ghost->GetYaxis()->SetRangeUser(YMin,YMax);
  hist_Ghost->GetYaxis()->SetTitle(YTitle);
  hist_Ghost->GetXaxis()->SetTitleOffset(1.4);
  hist_Ghost->GetXaxis()->SetTitle(XTitle);
  

  return hist_Ghost;

    

  
  }



void Print3DHistInfo(TH3 *InHist3D)
{

  cout<<" Bin info for  "<<InHist3D->GetName()<<endl;
  
  for(int i =0;i< InHist3D->GetNbinsX()+1;i++)
    {
      cout<<" XAxis: "<<i <<"    Low Edge "<<InHist3D->GetXaxis()->GetBinLowEdge(i)<<
	" Bin Centre  "<<InHist3D->GetXaxis()->GetBinCenter(i)<<endl;
    }
  
    cout<<endl;

    for(int i =0;i< InHist3D->GetNbinsY()+1;i++)
      {
	
	cout<<" YAxis: "<<i <<"    Low Edge "<<InHist3D->GetYaxis()->GetBinLowEdge(i)<<
	  " Bin Centre  "<<InHist3D->GetYaxis()->GetBinCenter(i)<<endl;
	
	//cout<<" Bin Centre 3D Pt"<<i<<"    "<<InHist3D->GetYaxis()->GetBinCenter(i)<<endl;
	
      }
    
    cout<<endl;
    

  
    for(int i =0;i< InHist3D->GetNbinsZ()+1;i++)
      {
	
	
	cout<<" ZAxis: "<<i <<"    Low Edge "<<InHist3D->GetZaxis()->GetBinLowEdge(i)<<
	  " Bin Centre  "<<InHist3D->GetZaxis()->GetBinCenter(i)<<endl;
	
	//cout<<" Bin Centre 3D Phi"<<i<<"    "<<hist_JetEta_JetPt_JetPhi->GetZaxis()->GetBinCenter(i)<<endl;
	
      }
    
    cout<<endl;
  
 


}



void Print1DHistInfoAndInt(TH1 *InHist1D, Int_t MultiWidth)
{

  cout<<" Printing hist "<<InHist1D->GetName()<<endl;

  Double_t IntPt =0.0;

  cout<<" Bin No "<<" Low Edge "<<" width "<<"  content "<<endl;
  for(int j =0;j <=InHist1D->GetNbinsX();j++)
    {
      cout<<"  Hist bin "<< j <<"    "<<InHist1D->GetBinLowEdge(j)<<"   "<<InHist1D->GetBinWidth(j)<<"   "<<InHist1D->GetBinContent(j)<<endl;

      if(MultiWidth==1){IntPt = IntPt + (InHist1D->GetBinContent(j)*InHist1D->GetBinWidth(j));}
      else{IntPt = IntPt + (InHist1D->GetBinContent(j));}
      
    }


  cout<<" Integral of histogram  "<<IntPt<<endl;
  cout<<endl<<endl;


}


void FoundJetStatStartMuon(TFile *file_in, TLatex *tb, TLatex *tr)
{


  setTDRStyle();
  TH1::SetDefaultSumw2();
  
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.2);
  gStyle->SetOptStat(0);
  
  char LatexChar[400];
  


  TH1D *hist_MuonPt=(TH1D*)file_in->Get("histMuonPt");


  cout<<endl<<endl<<endl;
  cout<<" ================================================================================== "<<endl;
  cout<<" ================= Combination Plots ============================================== "<<endl;
  cout<<" ================  Starting from Muons ============================================= "<<endl;
  cout<<" ================================================================================== "<<endl;
  cout<<endl<<endl<<endl;
  
  
  

  TH1D *hist_MuonJet_MuonPt=(TH1D*)file_in->Get("histMatchedMuonPt_StMuons");
  TH1D *hist_MuonJet_PtRatio_MuonsInsideJet_AllMuons=(TH1D*)file_in->Get("hist_MuonPtRatio_JetMuons_AllMuons");
  
  hist_MuonJet_MuonPt->SetStats(kFALSE);
  hist_MuonJet_PtRatio_MuonsInsideJet_AllMuons->SetStats(kFALSE);


  GlamorizeHistogram(hist_MuonJet_MuonPt,2,2,20,0.6);
  GlamorizeHistogram(hist_MuonJet_PtRatio_MuonsInsideJet_AllMuons,2,2,20,0.6);
 

  
  TCanvas *Canvas_MuonJet_PtRatio_MuonsInsideJet_AllMuons = new TCanvas("Canvas_MuonJet_PtRatio_MuonsInsideJet_AllMuons","Canvas_MuonJet_PtRatio_MuonsInsideJet_AllMuons",800,400);
  Canvas_MuonJet_PtRatio_MuonsInsideJet_AllMuons->Divide(2,1);


  TLegend *lgd_MuonJet_PtRatio_MuonsInsideJet_AllMuons = MyLegend(0.50,0.72,0.66,0.86);
  lgd_MuonJet_PtRatio_MuonsInsideJet_AllMuons->AddEntry(hist_MuonPt,"muons","P");
  lgd_MuonJet_PtRatio_MuonsInsideJet_AllMuons->AddEntry(hist_MuonJet_MuonPt,"muons inside Jet","P");
  
  Canvas_MuonJet_PtRatio_MuonsInsideJet_AllMuons->cd(1);
  gPad->SetLogy(1);
  hist_MuonPt->Draw();
  hist_MuonJet_MuonPt->Draw("same");
  lgd_MuonJet_PtRatio_MuonsInsideJet_AllMuons->Draw("same");
  

  sprintf(LatexChar,"Muons = %.0f",hist_MuonPt->GetEntries());
  tb->DrawLatex(0.26,0.30,LatexChar);
  sprintf(LatexChar,"Muons-Jet = %.0f",hist_MuonJet_MuonPt->GetEntries());
  tr->DrawLatex(0.26,0.26,LatexChar);

  
  Canvas_MuonJet_PtRatio_MuonsInsideJet_AllMuons->cd(2);
  gPad->SetLogy(1);
  hist_MuonJet_PtRatio_MuonsInsideJet_AllMuons->Draw();

  
  Canvas_MuonJet_PtRatio_MuonsInsideJet_AllMuons->SaveAs("Figures/MuonJet_PtRatio_MuonsInsideJet_AllMuons.pdf");
  Canvas_MuonJet_PtRatio_MuonsInsideJet_AllMuons->SaveAs("Figures/MuonJet_PtRatio_MuonsInsideJet_AllMuons.png");






  //============= 3D histogram for the Muon - Jet matching
  TH3D *hist_EventCentrality_MuonEta_MuonPt=(TH3D*)file_in->Get("hist_Master_EventCentrality_MuonEta_MuonPt");
  TH3D *hist_MuonJet_EventCentrality_MuonPt_JetPt=(TH3D*)file_in->Get("hist_Master_EventCentrality_MuonPt_JetPt");
  


  //========= Array of Jet Pt
  TH1 *hist_CentBin_MuonPt[NCentBins];
  TH1 *hist_MuonJet_CentBin_MuonPt[NCentBins];
  TH1 *hist_Ratio_CentBin_InsideJetMuonPt_AllMuonPt[NCentBins];

  
  for(int i=0;i<NCentBins;i++)
    {
      
      Int_t CentBinMin = hist_EventCentrality_MuonEta_MuonPt->GetXaxis()->FindBin(CentBins[i]);
      Int_t CentBinMax = hist_EventCentrality_MuonEta_MuonPt->GetXaxis()->FindBin(CentBins[i+1]);
      cout<< "hi bin "<< CentBinMin <<" - "<<CentBinMax<<endl;

      
      Int_t MuonEtaMinBin = hist_EventCentrality_MuonEta_MuonPt->GetYaxis()->FindBin(MuonEtaMin);
      Int_t MuonEtaMaxBin = hist_EventCentrality_MuonEta_MuonPt->GetYaxis()->FindBin(MuonEtaMax);




      Int_t JetPtMinBin = hist_MuonJet_EventCentrality_MuonPt_JetPt->GetZaxis()->FindBin(JetPtMin);
      Int_t JetPtMaxBin = hist_MuonJet_EventCentrality_MuonPt_JetPt->GetZaxis()->FindBin(JetPtMax);
      cout<<"JetPtBin "<<JetPtMinBin<<"   "<<JetPtMaxBin<<endl;
      
      //======== Get the projection of histogram =========//
      //All muon pT Cent Bins
      hist_CentBin_MuonPt[i] =  hist_EventCentrality_MuonEta_MuonPt->ProjectionZ(Form("hist_CentBin_MuonPt_Bin%d",i),CentBinMin,CentBinMax,MuonEtaMinBin,MuonEtaMaxBin);
      hist_CentBin_MuonPt[i]->GetYaxis()->SetTitle("Entries");
      GlamorizeHistogram(hist_CentBin_MuonPt[i],1,1,20,0.6);



      //muon pT (Muon Jet) Cent Bins
      hist_MuonJet_CentBin_MuonPt[i] =  hist_MuonJet_EventCentrality_MuonPt_JetPt->ProjectionY(Form("hist_MuonJet_CentBin_MuonPt_Bin%d",i),CentBinMin,CentBinMax,JetPtMinBin,JetPtMaxBin);
      hist_MuonJet_CentBin_MuonPt[i]->GetYaxis()->SetTitle("Entries");
      GlamorizeHistogram(hist_MuonJet_CentBin_MuonPt[i],2,2,20,0.6);


      //======== ratio of [ (Muon Jet) muon pt Cent Bins] and [muon pT Cent Bins] ===========//
      hist_Ratio_CentBin_InsideJetMuonPt_AllMuonPt[i] = RatioHistogram(hist_MuonJet_CentBin_MuonPt[i],hist_CentBin_MuonPt[i],1);
      hist_Ratio_CentBin_InsideJetMuonPt_AllMuonPt[i]->GetYaxis()->SetTitle("Ratio");
      hist_Ratio_CentBin_InsideJetMuonPt_AllMuonPt[i]->SetName(Form("hist_Ratio_CentBin_JetMuonPt_JetPt_Bin%d",i));
      hist_Ratio_CentBin_InsideJetMuonPt_AllMuonPt[i]->SetTitle(Form("hist_Ratio_CentBin_JetMuonPt_JetPt_Bin%d",i));

      GlamorizeHistogram(hist_Ratio_CentBin_InsideJetMuonPt_AllMuonPt[i],2,2,21,0.6); 
      
    }


  
  TCanvas *Canvas_CentBin_MuonPt = new TCanvas("Canvas_CentBin_MuonPt","Canvas_CentBin_MuonPt",1600,400);
  Canvas_CentBin_MuonPt->Divide(4,1);

  for(int i=0;i<NCentBins;i++)
    {
      Int_t j = NCentBins -i;
      Canvas_CentBin_MuonPt->cd(j);
      gPad->SetLogy();
      hist_CentBin_MuonPt[i]->Draw();
      hist_MuonJet_CentBin_MuonPt[i]->Draw("same");
      sprintf(LatexChar,"(%0.f Muons)",hist_CentBin_MuonPt[i]->GetEntries());
      tb->DrawLatex(0.60,0.70,LatexChar);
      sprintf(LatexChar,"(%0.f Muons)",hist_MuonJet_CentBin_MuonPt[i]->GetEntries());
      tr->DrawLatex(0.60,0.64,LatexChar);
      lgd_MuonJet_PtRatio_MuonsInsideJet_AllMuons->Draw("same");
      tb->DrawLatex(0.70,0.92,Form("Cent. %0d - %0d %%",CentBins[i],CentBins[i+1]));
      
    }

    Canvas_CentBin_MuonPt->SaveAs("Figures/CentBin_MuonPt.png");
    Canvas_CentBin_MuonPt->SaveAs("Figures/CentBin_MuonPt.pdf");





    TCanvas *Canvas_Ratio_CentBin_InsideJetMuonPt_AllMuonPt = new TCanvas("Ratio_CentBin_InsideJetMuonPt_AllMuonPt","Ratio_CentBin_InsideJetMuonPt_AllMuonPt",1600,400);
    Canvas_Ratio_CentBin_InsideJetMuonPt_AllMuonPt->Divide(4,1);

    
    for(int i=0;i<NCentBins;i++)
      {
	Int_t j = NCentBins -i;
	Canvas_Ratio_CentBin_InsideJetMuonPt_AllMuonPt->cd(j);
	gPad->SetLogy();
	
	hist_Ratio_CentBin_InsideJetMuonPt_AllMuonPt[i]->Draw();
	tb->DrawLatex(0.70,0.92,Form("Cent. %0d - %0d %%",CentBins[i],CentBins[i+1]));
      
      }
    
    
      Canvas_Ratio_CentBin_InsideJetMuonPt_AllMuonPt->SaveAs("Figures/CentBin_InsideJetMuonPt_AllMuonPt.pdf");
      Canvas_Ratio_CentBin_InsideJetMuonPt_AllMuonPt->SaveAs("Figures/CentBin_InsideJetMuonPt_AllMuonPt.png");

      //======================================================================================//
      //==================== Muon ratios for different Jet Pt Cuts ==========================//
      //======================================================================================//
      //const Int_t NJetPtCuts =4;
      //Double_t JetPtCuts[NJetPtCuts]={30.0,60.0,80.0,100.0};
      
      TH1 *hist_MuonJet_JetPtBin_MuonPt[NJetPtCuts];
      TH1 *hist_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt[NJetPtCuts];
      
      
      for(int i=0;i<NJetPtCuts;i++)
	{
	  
	  Int_t CentBinMin = hist_MuonJet_EventCentrality_MuonPt_JetPt->GetXaxis()->FindBin(EvtCentMin);
	  Int_t CentBinMax = hist_MuonJet_EventCentrality_MuonPt_JetPt->GetXaxis()->FindBin(EvtCentMax);
	  cout<< "hi bin "<< CentBinMin <<" - "<<CentBinMax<<endl;
	  
	  
	  Int_t JetPtMinBin = hist_MuonJet_EventCentrality_MuonPt_JetPt->GetZaxis()->FindBin(JetPtCuts[i]);
	  Int_t JetPtMaxBin = hist_MuonJet_EventCentrality_MuonPt_JetPt->GetZaxis()->FindBin(JetPtMax);
	  cout<<"JetPtBin "<<JetPtMinBin<<"   "<<JetPtMaxBin<<endl;
	  
	  
	  Int_t MuonEtaMinBin = hist_EventCentrality_MuonEta_MuonPt->GetYaxis()->FindBin(MuonEtaMin);
	  Int_t MuonEtaMaxBin = hist_EventCentrality_MuonEta_MuonPt->GetYaxis()->FindBin(MuonEtaMax);
	  
	  //======== Get the projection of histogram =========//
	  
	  //muon pT (Muon Jet) Jet Pt Bins
	  hist_MuonJet_JetPtBin_MuonPt[i] = hist_MuonJet_EventCentrality_MuonPt_JetPt->ProjectionY(Form("hist_MuonJet_JetPtBin_MuonPt_Bin%d",i),CentBinMin,CentBinMax,JetPtMinBin,JetPtMaxBin);
	  hist_MuonJet_JetPtBin_MuonPt[i]->GetYaxis()->SetTitle("Entries");
	  GlamorizeHistogram(hist_MuonJet_JetPtBin_MuonPt[i],2,2,20,0.6);
	  
	  
	  //======== ratio of [muon pT (MuonJet) Jet Pt Bins] and [All Muons] ===========//
	  hist_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt[i] = RatioHistogram(hist_MuonJet_JetPtBin_MuonPt[i],hist_MuonPt,1);
	  hist_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt[i]->GetYaxis()->SetTitle("Ratio");
	  hist_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt[i]->SetName(Form("hist_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt_Bin_%d",i));
	  hist_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt[i]->SetTitle(Form("hist_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt_Bin_%d",i));
	  GlamorizeHistogram(hist_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt[i],2,2,21,0.6); 
	  
	}



      TCanvas *Canvas_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt = new TCanvas("JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt","JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt",1600,400);
      Canvas_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt->Divide(4,1);


      TLegend *lgd_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt = MyLegend(0.22,0.24,0.38,0.38);
      lgd_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt->AddEntry(hist_MuonPt,"Muons","P");
      lgd_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt->AddEntry(hist_MuonJet_JetPtBin_MuonPt[0],"Muons in Jet","P");

  
  for(int i=0;i<NJetPtCuts;i++)
    {
      Canvas_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt->cd(i+1);
      gPad->SetLogy();
      hist_MuonPt->Draw();
      hist_MuonJet_JetPtBin_MuonPt[i]->Draw("same");

      sprintf(LatexChar,"(Jet p_{T} > %0.f GeV/c)",JetPtCuts[i]);
      tb->DrawLatex(0.60,0.75,LatexChar);
      sprintf(LatexChar,"(%0.f Muons)",hist_MuonPt->GetEntries());
      tb->DrawLatex(0.60,0.70,LatexChar);
      sprintf(LatexChar,"(%0.f Muons)",hist_MuonJet_JetPtBin_MuonPt[i]->GetEntries());
      tr->DrawLatex(0.60,0.65,LatexChar);
      lgd_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt->Draw("same");
      tb->DrawLatex(0.70,0.92,Form("Cent. %0d - %0d %%",EvtCentMin,EvtCentMax));
      
    }
  
  Canvas_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt->SaveAs("Figures/JetPtBins_MuonPt.png");
  Canvas_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt->SaveAs("Figures/JetPtBins_MuonPt.pdf");




  TCanvas *Canvas_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt = new TCanvas("Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt","Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt",1600,400);
  Canvas_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt->Divide(4,1);

  
  for(int i=0;i<NJetPtCuts;i++)
    {
      Canvas_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt->cd(i+1);
      gPad->SetLogy();
      hist_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt[i]->Draw();
      sprintf(LatexChar,"(Jet p_{T} > %0.f GeV/c)",JetPtCuts[i]);
      tb->DrawLatex(0.30,0.8,LatexChar);
      tb->DrawLatex(0.70,0.92,Form("Cent. %0d - %0d %%",EvtCentMin,EvtCentMax));
      
    }

  
      

  Canvas_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt->SaveAs("Figures/Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt.png");
  Canvas_Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt->SaveAs("Figures/Ratio_JetPtBins_MuonJet_MuonsInsideJets_AllMuons_MuonPt.pdf");




}
