//The File to read the OutPut of ak4Analyzer and make plots and latex table

#ifndef __CINT__
#endif
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TSystem.h"
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

#include "TDirectory.h"
#include "THStack.h"
#include "TRandom3.h"
#include "THnSparse.h"





// These functions are now in seperate files
#include "MakeEventHistos.C"
#include "MakeGenJetPlots.C"
#include "MakeRecJetPlots.C"
#include "MakeMuonPlots.C"
#include "MakeCSVTagPlots.C"



//TH1D *RatioHistogram(TH1D *InHistNum, TH1D *InHistDeno, Int_t RebinFac);

static const int NFlavour =6;
const Int_t LineColorArray[NFlavour+1]={0,3,7,6,4,2,1};
const Int_t MarkerColorArray[NFlavour+1]={0,3,7,6,4,2,1};
const Int_t MarkerStyleArray[NFlavour+1]={0,46,30,38,33,21,24};
const Float_t MarkerSizeArray[NFlavour+1]={0,1.5,1.5,1.5,1.8,1.4,1.4};


TH1D *RatioHistogram(TH1 *InHistNum, TH1 *InHistDeno, Int_t RebinFac);
void PrintGraph(TGraph *GraphIn);
void ScaleHistByItsIntegral(TH1 *InHist);

TH1D *Get_Ghost_Hist(const char *Name, const char *Title, Double_t YMin, Double_t YMax, const char *XTitle, const char *YTitle);

void FlavouredHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize);

TLegend *MyLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2);


Int_t Flv_Legend_Index = 0;
void DrawFlavourLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index);

void DrawFlavourLegendUn(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index);
Int_t Flv_Legend_Index_V = 0;
void DrawFlavourLegendVertical(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index);


void rebinAsymmetric(TH1* histogram, const int nBins, const double* binEdges);
bool checkBinBoundaries(const int nCheckedBins, const double *checkedBins, TAxis *originalAxis);
TH1D* FindHistogram(TFile *inputFile, const char *name, int xAxis, int nAxes, int *axisNumber, double *lowBinIndex, double *highBinIndex);
void MakeHistogramNameToHistogramTitle(TH1 *inHist);





//======== Jet Kinematic Cuts =============//
const Double_t GenJetPtMin = 60.0;
const Double_t GenMuPtCut =  5.0;

const Double_t RecJetPtMin = 60.0;
const Double_t RecMuPtCut =  5.0;

/*
//===== Bins for Asymmatric binning of Gen Jet pT
const int NBins_GenJetPt_VarSize=12;
//bin boundry matching with the original histogram bin boundry
const Double_t GenJetPtBinEdges[NBins_GenJetPt_VarSize]={31.5,40.5,63.0,81.0,103.5,130.5,162.0,202.5,252.0,301.5,351.0,445.5};


//===== Bins for Asymmatric binning of muon pT
const int NBins_GenMuonPt_VarSize=13;
//bin boundry matching with the original histogram bin boundry
const Double_t GenMuonPtBinEdges[NBins_GenMuonPt_VarSize]={1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 14.0, 18.0, 22.0, 30.0, 40.0, 60.0, 100.0};
*/

void MakeGenJetPlots(TFile *file_in, Double_t GenJetPtMin,Double_t GenMuPtCut);
void MakeRecJetPlots(TFile *file_in, TFile *file_out, Double_t RecJetPtMin);

void MakeCSVTagPlots(TFile *file_in,TFile *file_out);
void MakeMuonPlots(TFile *file_in);
void MakeMuonIDVarStudy(TFile *file_in);
void MakeJetMuonIDVarStudy(TFile *file_in);

void MakeJetPlots()
{

  
  Double_t PtCut = 0.0;
  
  setTDRStyle();
  gStyle->SetPadBottomMargin(0.2);
  
  
  //
  //gStyle->SetOptStat(0);
  //gROOT->ForceStyle();

  TH1::SetDefaultSumw2();
  
  //TFile *file_in =  new TFile("DiJet_Pythia6Skim__FullPtHat_08Jan2019_All_SoftMuID.root","R");
  //TFile *file_in =  new TFile("DiJet_Pythia6Skim__FullPtHat_08Jan2019_All_TightMuID.root","R");
  //TFile *file_in =  new TFile("DiJet_Pythia6Skim__FullPtHat_08Jan2019_All_TightMuIDPlusMCMatch03.root","R");
  //TFile *file_in =  new TFile("DiJet_Pythia6Skim__FullPtHat_21Jan2019_All_TightMuID_JetPtAbove30.root","R");
  //TFile *file_in =  new TFile("DiJet_Pythia6Skim__FullPtHat_21Jan2019_All_TightMuID_JetPtAbove50.root","R");
  //TFile *file_in =  new TFile("DiJet_Pythia6Skim__FullPtHat_21Jan2019_All_TightMuID_JetPtAbove80.root","R");
  //TFile *file_in =  new TFile("DiJet_Pythia6Skim__FullPtHat_21Jan2019_All_TightMuID_JetPtAbove120.root","R");
  //TFile *file_in =  new TFile("DiJet_Pythia6Skim__FullPtHat_21Jan2019_All_TightMuID_JetPtAbove30_MuPtAbove3.root","R");
  //TFile *file_in =  new TFile("DiJet_Pythia6Skim__FullPtHat_21Jan2019_All_TightMuID_JetPtAbove30_MuPtAbove5.root","R");
  //TFile *file_in =  new TFile("DiJet_Pythia6Skim__FullPtHat_21Jan2019_All_TightMuID_JetPtAbove30_MuPtAbove10.root","R");
  //TFile *file_in =  new TFile("DiJet_Pythia6Skim__FullPtHat_21Jan2019_All_TightMuID_JetPtAbove50_MuPtAbove10.root","R");
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_19Feb2019_All.root","R");
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_20March2019_All.root","R");
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_MCMatchedMuon_01April2019_All.root","R");
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_MCMatchedMuon_RefPartonFlvForB_03April2019_All.root","R");
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_MCMatchedMuon_ForUnKnownJets_11April2019_All.root","R");
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_MCMatchedMuon_RefPartonFlvForB_ForUnKnownJets_11April2019_All.root","R");
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_MCMatchedMuon_RefPartonFlvForB_ForUnKnownJets_24April2019_All.root","R");

  //Tightest muon applied
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_DataCuts_MCMatchedMuon_TighestMuon_RefPartonFlvForB_18June2019_All.root","R");
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_Jet80GeV16Mu5GeV_MCMatchedMuon_TighestMuon_RefPartonFlvForB_18June2019_All.root","R");
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_Jet80GeV16Mu3GeV_MCMatchedMuon_TighestMuon_RefPartonFlvForB_02July2019_All.root","R");
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_Jet80GeV16Mu3GeV_TighestMuon_RefPartonFlvForB_05July2019_All.root","R");
  //TFile *file_in =  new TFile("InRootFiles/DiJet_Pythia6Skim__FullPtHat_Jet60GeV2Mu5GeV_TighestMuon_RefPartonFlvForB_24July2019_All.root","R");

  /*************************
  //PP 2017 MC Starts here:
  *************************/
  
  //TFile *file_in =  new TFile("InRootFiles/DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_31July2019_All.root","R");
  //PP 2017 MC (MC Matched muons are used)
  //TFile *file_in =  new TFile("InRootFiles/DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_MCMatched_01Aug2019_All.root","R");  

  //PP 2017 MC (Added Hspares (4D sparse)) for muon pT cut effect on Muon pT relative
  //TFile *file_in =  new TFile("InRootFiles/DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_12Aug2019_All.root","R");

  //PP 2017 MC (Added muon quality cut histograms)
  //TFile *file_in =  new TFile("InRootFiles/DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_20Aug2019_All.root","R");

  //PP 2017 MC (quality cut histograms + Mu Jet Trigger)
  //TFile *file_in =  new TFile("InRootFiles/DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_MuJetTriggerApplied_29Aug2019_All.root","R");

  //PP 2017 MC (Added reco mu-gen mu matched histo) : Run for MC muon matching test
  //TFile *file_in =  new TFile("InRootFiles/DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_All03Sep2019.root","R");

  //PP 2017 MC (Added reco mu-gen mu matched histo) : Run for MC muon matching test
  //TFile *file_in =  new TFile("InRootFiles/DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_MCMatched_04Sep19_All.root","R");

  /*************************
  //Changes the Jet pT number of bins and maximum pT to synchronize with the Data from here
  *************************/

  //1. Should check the effect of bin changes on Jet fractions (need file without trigger applied)
  //TFile *file_in =  new TFile("InRootFiles/JetAnalyzerOutPut_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeVEta24_TighestMuon_RefPartonFlvForB_10Sep19_All.root","R");
  
  //2. Should check the effect of muon+Jet trigger on Jet fractions (with trigger applied)
  // Muon+Jet trigger applied : HLT_HIL3Mu5_AK4PFJet30_v1
  //TFile *file_in =  new TFile("InRootFiles/JetAnalyzerOutPut_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeVEta24_TighestMuon_RefPartonFlvForB_TriggerApplied_10Sep19_All.root","R");
  //This file should have EventHistos + Muon DR Histo + 2D DxyDz histo
  //TFile *file_in =  new TFile("InRootFiles/JetAnalyzerOutPut_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeVEta24_TighestMuon_RefPartonFlvForB_TriggerApplied_12Sep19_All.root","R");
  //This file should have quality cut histograms added for the Jet Muons
  //TFile *file_in =  new TFile("InRootFiles/JetAnalyzerOutPut_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeVEta24_TighestMuon_RefPartonFlvForB_TriggerApplied_17Sep19_All.root","R");

  
  //This file should have added 3D histo with additional cut i) chi2/ndf < 2 and ii) 0.005 < Muon_DR < 0.3
  //also have a 6D sparse to study the dependence of fractions on muon ID cuts
  TFile *file_in =  new TFile("InRootFiles/JetAnalyzerOutPut_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeVEta24_TighestMuon_RefPartonFlvForB_TriggerApplied_18Sep19_All.root","R");

  //3. Should check the effect of mu |eta| < 1.4 (with trigger applied)
  // Muon+Jet trigger applied : HLT_HIL3Mu5_AK4PFJet30_v1
  //TFile *file_in =  new TFile("InRootFiles/JetAnalyzerOutPut_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeVEta14_TighestMuon_RefPartonFlvForB_TriggerApplied_11Sep2019_All.root","R");
  



  cout<<" Analysing file: "<<file_in->GetName()<<endl;
  

  TLatex *tb = new TLatex();
  tb->SetNDC();
  tb->SetTextColor(kBlack);
  tb->SetTextSize(0.04);


  TLatex *tr = new TLatex();
  tr->SetNDC();
  tr->SetTextColor(kRed);
  tr->SetTextSize(0.04);

  
  TFile *OutFile = new TFile("JetPlotOutPut_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeVEta14_TighestMuon_RefPartonFlvForB_TriggerApplied_11Sep19_All.root","RECREATE");

  //MakeEventHistos(file_in, OutFile);
  MakeGenJetPlots(file_in, GenJetPtMin, GenMuPtCut);
  //MakeRecJetPlots(file_in, OutFile, RecJetPtMin);
  //MakeMuonPlots(file_in);
  //MakeMuonIDVarStudy(file_in);
  //MakeJetMuonIDVarStudy(file_in);
  //MakeCSVTagPlots(file_in, OutFile);

  //OutFile->Write();
  //OutFile->Close();
  
  return;

  cout<<" ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ "<<endl;
  cout<<" ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ "<<endl;

  
  
}






/*








*/

void ScaleHistByItsIntegral(TH1 *InHist)
{
  Double_t Integral_Val = InHist->Integral(); 
  Double_t ScaleFac = 1.0/Integral_Val;
  InHist->Scale(ScaleFac);

}



TH1D *RatioHistogram(TH1 *InHistNum, TH1 *InHistDeno, Int_t RebinFac)
{

  TH1D *temp_Num = (TH1D*)InHistNum->Clone("temp_Num");
  TH1D *temp_Deno = (TH1D*)InHistDeno->Clone("temp_Deno");

  temp_Num->Rebin(RebinFac);
  temp_Deno->Rebin(RebinFac);

  temp_Num->Divide(temp_Num,temp_Deno,1.0,1.0,"B");

  return temp_Num;


}


/*
TH1D *FlavouredHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize)
{

  TH1D *temp_hist = (TH1D*)InHist->Clone("temp_hist");

  temp_hist->SetLineColor(LineColor);
  temp_hist->SetMarkerColor(MarkerColor);
  temp_hist->SetMarkerStyle(MarkerStyle);
  temp_hist->SetMarkerSize(MarkerSize);


  return temp_hist;

}
*/


void FlavouredHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize)
{
  
  InHist->SetLineColor(LineColor);
  InHist->SetMarkerColor(MarkerColor);
  InHist->SetMarkerStyle(MarkerStyle);
  InHist->SetMarkerSize(MarkerSize);

  //InHist->GetXaxis()->SetLimits(0.0,500.0);
  //InHist->GetXaxis()->SetRangeUser(40.0,445.0);
  InHist->GetXaxis()->SetNdivisions(505);
  InHist->GetXaxis()->SetLabelSize(0.06);
  InHist->GetXaxis()->SetTitleOffset(1.4);
  InHist->GetXaxis()->SetTitleSize(0.06);
  InHist->GetYaxis()->SetTitleSize(0.06);
  
}







void DrawFlavourLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index)
{
  
  /*
  const int NFlavour = 6;
  Int_t LineColorArray[NFlavour+1]={0,9,7,6,4,2,1};
  Int_t MarkerColorArray[NFlavour+1]={0,9,7,6,4,2,1};
  Int_t MarkerStyleArray[NFlavour+1]={0,47,29,34,33,21,20};
  Float_t MarkerSizeArray[NFlavour+1]={0,1.8,1.8,1.8,1.8,1.8,1.8};
  */
  
  TH1D *hist_U = new TH1D(Form("hist_U%d",index),Form("hist_U%d",index),100.0,0.0,10.0);
  TH1D *hist_D = new TH1D(Form("hist_D%d",index),Form("hist_D%d",index),100.0,0.0,10.0);
  TH1D *hist_S = new TH1D(Form("hist_S%d",index),Form("hist_S%d",index),100.0,0.0,10.0);
  TH1D *hist_C = new TH1D(Form("hist_C%d",index),Form("hist_C%d",index),100.0,0.0,10.0);
  TH1D *hist_B = new TH1D(Form("hist_B%d",index),Form("hist_B%d",index),100.0,0.0,10.0);
  TH1D *hist_G = new TH1D(Form("hist_G%d",index),Form("hist_G%d",index),100.0,0.0,10.0);

  FlavouredHistogram(hist_U, LineColorArray[1], MarkerColorArray[1], MarkerStyleArray[1],MarkerSizeArray[1]);
  FlavouredHistogram(hist_D, LineColorArray[2], MarkerColorArray[2], MarkerStyleArray[2],MarkerSizeArray[2]);
  FlavouredHistogram(hist_S, LineColorArray[3], MarkerColorArray[3], MarkerStyleArray[3],MarkerSizeArray[3]);
  FlavouredHistogram(hist_C, LineColorArray[4], MarkerColorArray[4], MarkerStyleArray[4],MarkerSizeArray[4]);
  FlavouredHistogram(hist_B, LineColorArray[5], MarkerColorArray[5], MarkerStyleArray[5],MarkerSizeArray[5]);
  FlavouredHistogram(hist_G, LineColorArray[6], MarkerColorArray[6], MarkerStyleArray[6],MarkerSizeArray[6]);

  
  Double_t xwidth = 0.12;
  //Double_t xwidth = 0.15;
  TLegend *lgd_U = MyLegend(x1,y1,x2,y2);
  
  lgd_U->AddEntry(hist_U,"u","P");
  //lgd_U->AddEntry(hist_U,"-999","P");
  TLegend *lgd_D = MyLegend(x1+xwidth,y1,x2+xwidth,y2);
  lgd_D->AddEntry(hist_D,"d","P");
  //lgd_D->AddEntry(hist_D,"0","P");
  TLegend *lgd_S = MyLegend(x1+(xwidth*2.0),y1,x2+(xwidth*2.0),y2);
  lgd_S->AddEntry(hist_S,"s","P");
  //lgd_S->AddEntry(hist_S,"no Rec","P");
  TLegend *lgd_C = MyLegend(x1+(xwidth*3.0),y1,x2+(xwidth*3.0),y2);
  lgd_C->AddEntry(hist_C,"c","P");
  TLegend *lgd_B = MyLegend(x1+(xwidth*4.0),y1,x2+(xwidth*4.0),y2);
  lgd_B->AddEntry(hist_B,"b","P");
  TLegend *lgd_G = MyLegend(x1+(xwidth*5.0),y1,x2+(xwidth*5.0),y2);
  lgd_G->AddEntry(hist_G,"g","P");
  

  lgd_U->Draw("same");
  lgd_D->Draw("same");
  lgd_S->Draw("same");
  lgd_C->Draw("same");
  lgd_B->Draw("same");
  lgd_G->Draw("same");


  //hist_U->Delete();

}






void DrawFlavourLegendUn(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index)
{
  
  /*
  const int NFlavour = 6;
  Int_t LineColorArray[NFlavour+1]={0,9,7,6,4,2,1};
  Int_t MarkerColorArray[NFlavour+1]={0,9,7,6,4,2,1};
  Int_t MarkerStyleArray[NFlavour+1]={0,47,29,34,33,21,20};
  Float_t MarkerSizeArray[NFlavour+1]={0,1.8,1.8,1.8,1.8,1.8,1.8};
  */
  
  TH1D *hist_U = new TH1D(Form("hist_U%d",index),Form("hist_U%d",index),100.0,0.0,10.0);
  TH1D *hist_D = new TH1D(Form("hist_D%d",index),Form("hist_D%d",index),100.0,0.0,10.0);
  TH1D *hist_S = new TH1D(Form("hist_S%d",index),Form("hist_S%d",index),100.0,0.0,10.0);
  
  FlavouredHistogram(hist_U, LineColorArray[1], MarkerColorArray[1], MarkerStyleArray[1],MarkerSizeArray[1]);
  FlavouredHistogram(hist_D, LineColorArray[2], MarkerColorArray[2], MarkerStyleArray[2],MarkerSizeArray[2]);
  FlavouredHistogram(hist_S, LineColorArray[3], MarkerColorArray[3], MarkerStyleArray[3],MarkerSizeArray[3]);
  

  

  Double_t xwidth = 0.15;
  TLegend *lgd_U = MyLegend(x1,y1,x2,y2);
  
  
  lgd_U->AddEntry(hist_U,"-999","P");
  TLegend *lgd_D = MyLegend(x1+xwidth,y1,x2+xwidth,y2);
  lgd_D->AddEntry(hist_D,"0","P");
  TLegend *lgd_S = MyLegend(x1+(xwidth*2.0),y1,x2+(xwidth*2.0),y2);
  lgd_S->AddEntry(hist_S,"no Rec","P");

  lgd_U->Draw();
  lgd_D->Draw();
  lgd_S->Draw();

  
  //hist_U->Delete();

}









void DrawFlavourLegendVertical(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index)
{
  
  /*
  const int NFlavour = 6;
  Int_t LineColorArray[NFlavour+1]={0,9,7,6,4,2,1};
  Int_t MarkerColorArray[NFlavour+1]={0,9,7,6,4,2,1};
  Int_t MarkerStyleArray[NFlavour+1]={0,47,29,34,33,21,20};
  Float_t MarkerSizeArray[NFlavour+1]={0,1.4,1.4,1.4,1.4,1.4,1.4};
  */
  
  TH1D *hist_U = new TH1D(Form("hist_U_V%d",index),Form("hist_U_V%d",index),100.0,0.0,10.0);
  TH1D *hist_D = new TH1D(Form("hist_D_V%d",index),Form("hist_D_V%d",index),100.0,0.0,10.0);
  TH1D *hist_S = new TH1D(Form("hist_S_V%d",index),Form("hist_S_V%d",index),100.0,0.0,10.0);
  TH1D *hist_C = new TH1D(Form("hist_C_V%d",index),Form("hist_C_V%d",index),100.0,0.0,10.0);
  TH1D *hist_B = new TH1D(Form("hist_B_V%d",index),Form("hist_B_V%d",index),100.0,0.0,10.0);
  TH1D *hist_G = new TH1D(Form("hist_G_V%d",index),Form("hist_G_V%d",index),100.0,0.0,10.0);

  FlavouredHistogram(hist_U, LineColorArray[1], MarkerColorArray[1], MarkerStyleArray[1],MarkerSizeArray[1]);
  FlavouredHistogram(hist_D, LineColorArray[2], MarkerColorArray[2], MarkerStyleArray[2],MarkerSizeArray[2]);
  FlavouredHistogram(hist_S, LineColorArray[3], MarkerColorArray[3], MarkerStyleArray[3],MarkerSizeArray[3]);
  FlavouredHistogram(hist_C, LineColorArray[4], MarkerColorArray[4], MarkerStyleArray[4],MarkerSizeArray[4]);
  FlavouredHistogram(hist_B, LineColorArray[5], MarkerColorArray[5], MarkerStyleArray[5],MarkerSizeArray[5]);
  FlavouredHistogram(hist_G, LineColorArray[6], MarkerColorArray[6], MarkerStyleArray[6],MarkerSizeArray[6]);

  
  TLegend *lgd_V = MyLegend(x1,y1,x2,y2);

  lgd_V->SetTextSize(0.08);
  
  lgd_V->AddEntry(hist_U,"u","P");
  lgd_V->AddEntry(hist_D,"d","P");
  lgd_V->AddEntry(hist_S,"s","P");
  lgd_V->AddEntry(hist_C,"c","P");
  lgd_V->AddEntry(hist_B,"b","P");
  lgd_V->AddEntry(hist_G,"g","P");
  

  lgd_V->Draw();
  

  //hist_U->Delete();

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



  TH1D *Get_Ghost_Hist(const char *Name, const char *Title, Double_t YMin, Double_t YMax, const char *XTitle, const char *YTitle)
  {

    TH1D *hist_Ghost = new TH1D(Name,Title,100,0.0,450);
    hist_Ghost->GetXaxis()->SetNdivisions(505);
    hist_Ghost->GetYaxis()->SetRangeUser(YMin,YMax);
    hist_Ghost->GetYaxis()->SetTitle(YTitle);
    hist_Ghost->GetXaxis()->SetTitleOffset(1.4);
    hist_Ghost->GetXaxis()->SetTitle(XTitle);

    return hist_Ghost;


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

for(int iBin = 1; iBin <= histogram->GetNbinsX(); iBin++){

    histogram->SetBinContent(iBin,0.0);
    histogram->SetBinError(iBin,0.0);
  }



  
  // Add the contents back to the histogram that was rebinned
  double binContent, binError, binCenter, oldContent, oldError;
  int newBin;
  for(int iBin = 1; iBin <= clonedHistogram->GetNbinsX(); iBin++){

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
  for(int iBin = 1; iBin <= histogram->GetNbinsX(); iBin++){


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



void PrintGraph(TGraph *GraphIn)
{
  cout<<endl<<endl;
  cout<<" The content of Graph "<<GraphIn->GetName()<<endl;
  cout<<"x       "<<"    y     "<<endl;
  for(int j=0; j<GraphIn->GetN();++j){
    
    Double_t x1, y1;
    
    GraphIn->GetPoint(j,x1,y1);
    cout<<x1<<"        "<<y1<<endl;
       
  }
  cout<<endl<<endl;



}


void MakeHistogramNameToHistogramTitle(TH1 *inHist)
{
  inHist->SetTitle(inHist->GetName());
}
