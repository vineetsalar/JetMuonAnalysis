#ifndef __CINT__
#endif
#include "TFile.h"
#include "TF1.h"
#include "TH1D.h"
#include <iostream> //cout and endl

#include "TCanvas.h"
#include "TLegend.h"
#include "TPad.h"
#include "THStack.h"

#include "CMS/tdrstyle.C"
#include "CMS/CMS_lumi.C"


#include "../../MyClass/MyMethod.h"


Int_t Scale_Hist_Index=0;
TH1D *Scale_Hist(TH1D *InHist, Double_t Weight, Int_t index);

Int_t Ratio_Hist_Index=0;
TH1D *Ratio_Hist(TH1D *InHistNum, TH1D *InHistDeno, Int_t index);

TLegend *MyLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2);



void JetBasicVariableDataMCComparison()
{

  //object of mymethod class
  MyMethod *JetVarMethod = new MyMethod();

  
  setTDRStyle();
  gStyle->SetPadBottomMargin(0.2);
  
  cout<<" comparing DiJet Data and MC Jet pT, eta and phi distributions "<<endl;

  // Open the file with PP data 
  TFile *file_Data =  new TFile("InFiles/OutFile_PP2017Data_HLT_MuonJet30_JetPtMin60_JetEtaMax2_MuEtaMax24_MuPtMin5_JetQualityOn.root","R");

  Double_t RebinFac = 4.0;
  
  //Get the Data Jet Pt, Eta, Phi histograms
  TH1D *hist_data_JetPt = (TH1D*)file_Data->Get("histJetPt");
  TH1D *hist_data_JetEta = (TH1D*)file_Data->Get("histJetEta");
  TH1D *hist_data_JetPhi = (TH1D*)file_Data->Get("histJetPhi");

  hist_data_JetPt->GetYaxis()->SetTitle("1/N_{Jets}dN/dp_{T}");
  hist_data_JetEta->GetYaxis()->SetTitle("1/N_{Jets}dN/#eta");
  hist_data_JetPhi->GetYaxis()->SetTitle("1/N_{Jets}dN/#phi");
  
  //GlamorizeHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize)
  JetVarMethod->GlamorizeHistogram(hist_data_JetPt,2,2,20,0.6);
  JetVarMethod->GlamorizeHistogram(hist_data_JetEta,2,2,20,0.6);
  JetVarMethod->GlamorizeHistogram(hist_data_JetPhi,2,2,20,0.6);
  
  hist_data_JetPt->Rebin(RebinFac);
  hist_data_JetEta->Rebin(RebinFac);
  hist_data_JetPhi->Rebin(RebinFac);

  cout<<" Data Stat. "<<hist_data_JetPt->GetEntries()<<"  "<<hist_data_JetEta->GetEntries()<<"  "<<hist_data_JetPhi->GetEntries()<<endl;

  JetVarMethod->ScaleHistByItsIntegral(hist_data_JetPt);
  JetVarMethod->ScaleHistByItsIntegral(hist_data_JetEta);
  JetVarMethod->ScaleHistByItsIntegral(hist_data_JetPhi);
  
  JetVarMethod->SetHistogramAxisRange(hist_data_JetEta,-999,-999,0.0,0.05);
  JetVarMethod->SetHistogramAxisRange(hist_data_JetPhi,-999,-999,0.0,0.05);
  
  // Open the file with PP Dijet MC 
  //TFile *file_MC =  new TFile("InFiles/JetPlotOutPut_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeVEta24_TighestMuon_RefPartonFlvForB_TriggerApplied_10Sep19_All.root","R");
  //not trigger
  TFile *file_MC =  new TFile("InFiles/JetPlotOutPut_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeVEta24_TighestMuon_RefPartonFlvForB_10Sep19_All.root","R");

  //Get the MC Jet Pt, Eta, Phi histograms
  TH1D *hist_mc_JetPt = (TH1D*)file_MC->Get("RecJetPlots/histJetPt");
  TH1D *hist_mc_JetEta = (TH1D*)file_MC->Get("RecJetPlots/histJetEta");
  TH1D *hist_mc_JetPhi = (TH1D*)file_MC->Get("RecJetPlots/histJetPhi");

  JetVarMethod->GlamorizeHistogram(hist_mc_JetPt,1,1,24,0.6);
  JetVarMethod->GlamorizeHistogram(hist_mc_JetEta,1,1,24,0.6);
  JetVarMethod->GlamorizeHistogram(hist_mc_JetPhi,1,1,24,0.6);

  
  hist_mc_JetPt->Rebin(RebinFac);
  hist_mc_JetEta->Rebin(RebinFac);
  hist_mc_JetPhi->Rebin(RebinFac);



  
  cout<<" MC Stat. "<<hist_mc_JetPt->GetEntries()<<"  "<<hist_mc_JetEta->GetEntries()<<"  "<<hist_mc_JetPhi->GetEntries()<<endl;
  cout<<" MC Stat. "<<hist_mc_JetPt->Integral()<<"  "<<hist_mc_JetEta->Integral()<<"  "<<hist_mc_JetPhi->Integral()<<endl;
  
  
  JetVarMethod->ScaleHistByItsIntegral(hist_mc_JetPt);
  JetVarMethod->ScaleHistByItsIntegral(hist_mc_JetEta);
  JetVarMethod->ScaleHistByItsIntegral(hist_mc_JetPhi);

  
  

  //cout<<hist_mc_JetPt->Integral("width")<<"  "<<hist_mc_JetEta->Integral("width")<<"  "<<hist_mc_JetPhi->Integral("width")<<endl;

  cout<<hist_mc_JetPt->Integral()<<"  "<<hist_mc_JetEta->Integral()<<"  "<<hist_mc_JetPhi->Integral()<<endl;
  

  //Data-MC ratios
  TH1D* hist_Ratio_Data_MC_JetPt = Ratio_Hist(hist_data_JetPt, hist_mc_JetPt, Ratio_Hist_Index++);
  TH1D* hist_Ratio_Data_MC_JetEta = Ratio_Hist(hist_data_JetEta, hist_mc_JetEta, Ratio_Hist_Index++);
  TH1D* hist_Ratio_Data_MC_JetPhi = Ratio_Hist(hist_data_JetPhi, hist_mc_JetPhi, Ratio_Hist_Index++);

  JetVarMethod->SetHistogramTitles(hist_Ratio_Data_MC_JetPt,"","Data/MC");
  JetVarMethod->SetHistogramTitles(hist_Ratio_Data_MC_JetEta,"","Data/MC");
  JetVarMethod->SetHistogramTitles(hist_Ratio_Data_MC_JetPhi,"","Data/MC");


  JetVarMethod->SetHistogramAxisRange(hist_Ratio_Data_MC_JetPt,-999,-999,0.0,2.2);
  JetVarMethod->SetHistogramAxisRange(hist_Ratio_Data_MC_JetEta,-999,-999,0.0,1.4);
  JetVarMethod->SetHistogramAxisRange(hist_Ratio_Data_MC_JetPhi,-999,-999,0.0,1.4);


  
  //make a 3 X 2 (coulmn x rows) canvas
  TCanvas *Canvas_DataMC_JetVar = new TCanvas("Canvas_DataMC_JetVar","Canvas_DataMC_JetVar",1200,800);
  Canvas_DataMC_JetVar->Divide(3,2);

  TLegend *lgd_DataMC_JetVar = JetVarMethod->MyLegend(0.43,0.72,0.77,0.85); 
  lgd_DataMC_JetVar->AddEntry(hist_data_JetPt,"PP 2017 Data","P");
  lgd_DataMC_JetVar->AddEntry(hist_mc_JetPt,"Pythia DiJet MC","P");

  
  Canvas_DataMC_JetVar->cd(1);
  gPad->SetLogy(1);
  hist_data_JetPt->Draw();
  hist_mc_JetPt->Draw("same");
  lgd_DataMC_JetVar->Draw("same");

  
  Canvas_DataMC_JetVar->cd(2);
  hist_data_JetEta->Draw();
  hist_mc_JetEta->Draw("same");

  Canvas_DataMC_JetVar->cd(3);
  hist_data_JetPhi->Draw();
  hist_mc_JetPhi->Draw("same");


  Canvas_DataMC_JetVar->cd(4);
  hist_Ratio_Data_MC_JetPt->Draw();

  Canvas_DataMC_JetVar->cd(5);
  hist_Ratio_Data_MC_JetEta->GetYaxis()->SetRangeUser(0.0,1.3);
  hist_Ratio_Data_MC_JetEta->Draw();


  Canvas_DataMC_JetVar->cd(6);
  hist_Ratio_Data_MC_JetPhi->GetYaxis()->SetRangeUser(0.0,1.3);
  hist_Ratio_Data_MC_JetPhi->Draw();


  
  

  Canvas_DataMC_JetVar->SaveAs("Plots/DataMC_JetVar.pdf");
  Canvas_DataMC_JetVar->SaveAs("Plots/DataMC_JetVar.png");

  

  
}

TH1D *Scale_Hist(TH1D *InHist, Double_t Weight, Int_t index)
{
  TH1D *SHist = (TH1D*)InHist->Clone(Form("temphist_%d",index)); 

  SHist->Scale(Weight);
  return SHist;
}


TH1D *Ratio_Hist(TH1D *InHistNum, TH1D *InHistDeno, Int_t index)
{
  TH1D *SHist = (TH1D*)InHistNum->Clone(Form("temphist_%d",index)); 
  SHist->Divide(InHistDeno);
  return SHist;
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
