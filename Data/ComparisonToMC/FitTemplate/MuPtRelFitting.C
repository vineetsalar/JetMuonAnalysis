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

#include "../CMS/tdrstyle.C"
#include "../CMS/CMS_lumi.C"



Double_t Func_MuPtRel(Double_t *x, Double_t *par);
//================== Open the MC Template file ===========================================//
//TFile *file_MCTemplate =  new TFile("OutFile_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_14Aug2019.root","R");

//Added inclusive plots for mu-pt rel
TFile *file_MCTemplate =  new TFile("OutFile_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_28Aug2019.root","R");

//PP MC (Mu+Jet Triggered)
//TFile *file_MCTemplate =  new TFile("OutFile_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_MuonJetTrigger.root","R");

//================ Get the histograms ===============================//
TH1D *hist_temp_MuPtRel_Inclusive = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_Inclusive");
TH1D *hist_temp_MuPtRel_Light = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_Light");
TH1D *hist_temp_MuPtRel_C = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_C");
TH1D *hist_temp_MuPtRel_B = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_B");

//TH1D *hist_temp_MuPtRel_Light = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVTag_Light");
//TH1D *hist_temp_MuPtRel_C = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVTag_C");
//TH1D *hist_temp_MuPtRel_B = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVTag_B");

//TH1D *hist_temp_MuPtRel_Light = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVVeto_Light");
//TH1D *hist_temp_MuPtRel_C = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVVeto_C");
//TH1D *hist_temp_MuPtRel_B = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVVeto_B");




Double_t CalcChi2(TH1D *InHist, TF1 *InFunc);

Int_t Scale_Hist_Index=0;
TH1D *Scale_Hist(TH1D *InHist, Double_t Weight, Int_t index);

Int_t Ratio_Hist_Index=0;
TH1D *Ratio_Hist(TH1D *InHistNum, TH1D *InHistDeno, Int_t index);

TLegend *MyLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2);

void MuPtRelFitting()
{

  setTDRStyle();
  gStyle->SetPadBottomMargin(0.2);
  
  cout<<" Fitting the muon pt relative "<<endl;

  // open the file with Pb+Pb data
  //TFile *file_Data =  new TFile("OutFile_PbPbData_HLT_MuonJet60_JetPtMin60_JetEtaMax2_MuEtaMax24_MuPtMin5_JetQualityOn_14Aug2019.root","R");

  // open the file with PP data 
  TFile *file_Data =  new TFile("OutFile_PP2017Data_HLT_MuonJet30_JetPtMin60_JetEtaMax2_MuEtaMax24_MuPtMin5_JetQualityOn_28Aug2019.root","R");

  // get the data histogram
  TH1D *hist_data_MuPtRel = (TH1D*)file_Data->Get("histMuonPtRel");
  hist_data_MuPtRel->SetMarkerSize(1.2);
  
  //TH1D *hist_data_MuPtRel = (TH1D*)file_Data->Get("histMuonPtRelCSVTag");
  //TH1D *hist_data_MuPtRel = (TH1D*)file_Data->Get("histMuonPtRelCSVVeto");


  //compare the mu pT relative distributions in Data and MC
  //Scale the MC to make its integral equal to data
  Double_t ScaleMC = hist_data_MuPtRel->Integral()/hist_temp_MuPtRel_Inclusive->Integral();
  hist_temp_MuPtRel_Inclusive->Scale(ScaleMC);
  hist_temp_MuPtRel_Inclusive->SetMarkerSize(1.2);

  cout<<hist_temp_MuPtRel_Inclusive->Integral()<<"   "<<hist_data_MuPtRel->Integral()<<endl;


  TLegend *lgd_MuPtRel_DataMC =MyLegend(0.57,0.72,0.73,0.86);
  lgd_MuPtRel_DataMC->AddEntry(hist_data_MuPtRel,"PP2017 Data","P");
  lgd_MuPtRel_DataMC->AddEntry(hist_temp_MuPtRel_Inclusive,"PP MC","P");
  
  // Make 2X1 Canvas
  TCanvas *Canvas_MuPtRel_DataMC = new TCanvas("Canvas_MuPtRel_DataMC","Canvas_MuPtRel_DataMC",800,400);
  Canvas_MuPtRel_DataMC->Divide(2,1);//column x row

  
  Canvas_MuPtRel_DataMC->cd(1);
  hist_temp_MuPtRel_Inclusive->Draw();
  hist_temp_MuPtRel_Inclusive->GetYaxis()->SetRangeUser(0.0,550000.0);
  hist_data_MuPtRel->Draw("same");
  lgd_MuPtRel_DataMC->Draw("same");

  
  TH1D *Ratio_MuPtRel_data_MC = Ratio_Hist(hist_data_MuPtRel, hist_temp_MuPtRel_Inclusive, Ratio_Hist_Index++);
  Canvas_MuPtRel_DataMC->cd(2);
  Ratio_MuPtRel_data_MC->GetYaxis()->SetRangeUser(0.0,2.5);
  Ratio_MuPtRel_data_MC->GetYaxis()->SetTitle("Data/MC");
  Ratio_MuPtRel_data_MC->Draw();
  Canvas_MuPtRel_DataMC->SaveAs("plots/MuPtRel_DataMC.pdf");
  Canvas_MuPtRel_DataMC->SaveAs("plots/MuPtRel_DataMC.png");






  
  // make the function from the MC templates
  TF1 *FitFunctionMuPtRel = new TF1("FitFunctionMuPtRel", Func_MuPtRel, 0.0, 4.0, 3);
  FitFunctionMuPtRel->SetLineColor(1);

  FitFunctionMuPtRel->SetParameter(0, 190.0);
  FitFunctionMuPtRel->SetParameter(1, 500.0);
  FitFunctionMuPtRel->SetParameter(2, 1500.0);


  
  hist_data_MuPtRel->Fit("FitFunctionMuPtRel","0L","",0.0,4.0);



  
  Double_t Fit_Chi2 = FitFunctionMuPtRel->GetChisquare();
  Double_t Fit_NDF =  FitFunctionMuPtRel->GetNDF();
  Double_t Fit_Prob = FitFunctionMuPtRel->GetProb();
  
  Double_t Frac_Light = FitFunctionMuPtRel->GetParameter(0);
  Double_t Frac_C = FitFunctionMuPtRel->GetParameter(1);
  Double_t Frac_B = FitFunctionMuPtRel->GetParameter(2);

  cout<<"Chi2/NDF : "<<Fit_Chi2<<"/"<<Fit_NDF<<" Prob: "<<Fit_Prob<<endl<<endl;
  //cout<<" Chi2 by hand "<<CalcChi2(hist_data_MuPtRel, FitFunctionMuPtRel)<<endl;

  cout<<"Frac_Light "<<Frac_Light<<endl;
  cout<<"Frac_C "<<Frac_C<<endl;
  cout<<"Frac_B "<<Frac_B<<endl;

  TH1D *Weighted_hist_temp_MuPtRel_Light = Scale_Hist(hist_temp_MuPtRel_Light, Frac_Light, Scale_Hist_Index++);
  TH1D *Weighted_hist_temp_MuPtRel_C = Scale_Hist(hist_temp_MuPtRel_C, Frac_C, Scale_Hist_Index++);
  TH1D *Weighted_hist_temp_MuPtRel_B = Scale_Hist(hist_temp_MuPtRel_B, Frac_B, Scale_Hist_Index++);

  THStack *hs_MuPtRel_All = new THStack("hs_MuPtRel_All","hs_MuPtRel_All");
  hs_MuPtRel_All->Add(Weighted_hist_temp_MuPtRel_Light);
  hs_MuPtRel_All->Add(Weighted_hist_temp_MuPtRel_C);
  hs_MuPtRel_All->Add(Weighted_hist_temp_MuPtRel_B);

  
  TCanvas *Canvas_data_MuPtRel_Fit = new TCanvas("Canvas_data_MuPtRel_Fit","Canvas_data_MuPtRel_Fit",1200,400);
  Canvas_data_MuPtRel_Fit->Divide(3,1);//colum x row
  
  Canvas_data_MuPtRel_Fit->cd(1);
  gPad->SetLeftMargin(0.2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_data_MuPtRel->Draw("P");
  Canvas_data_MuPtRel_Fit->Update();
  FitFunctionMuPtRel->Draw("same");

  //Weighted_hist_temp_MuPtRel_Light->Draw("same");
  //Weighted_hist_temp_MuPtRel_C->Draw("same");
  //Weighted_hist_temp_MuPtRel_B->Draw("same");

  hs_MuPtRel_All->Draw("histsame");
  hist_data_MuPtRel->Draw("Psame");
  FitFunctionMuPtRel->Draw("same");



  
  //hist_temp_MuPtRel_Light->Draw("histsame");
  //hist_temp_MuPtRel_C->Draw("histsame");
  //hist_temp_MuPtRel_B->Draw("histsame");






  


  
}



Double_t Func_MuPtRel(Double_t *x, Double_t *par)
{

 
  Double_t Frac_Light = par[0];  
  Double_t Frac_C = par[1];
  Double_t Frac_B = par[2];

  Double_t xx = x[0];
  Int_t bin = hist_temp_MuPtRel_Light->GetXaxis()->FindBin(xx);

  
  Double_t Sigma = Frac_Light*hist_temp_MuPtRel_Light->GetBinContent(bin) + Frac_C*hist_temp_MuPtRel_C->GetBinContent(bin)
    +  Frac_B*hist_temp_MuPtRel_B->GetBinContent(bin);

  //Double_t Sigma = Frac_Light*hist_temp_MuPtRel_Light->GetBinContent(bin);

  //Double_t Sigma = Frac_C*hist_temp_MuPtRel_C->GetBinContent(bin);

  //Double_t Sigma = Frac_B*hist_temp_MuPtRel_B->GetBinContent(bin);


  
  return Sigma;
  
}



Double_t CalcChi2(TH1D *InHist, TF1 *InFunc)
{
  
  const Int_t nbins = InHist->GetNbinsX();
  Int_t i;
  Double_t xx[nbins];
  Double_t yy[nbins];
  Double_t erryy[nbins];

 for (Int_t j=1;j<=nbins; j++) 
    {
      
      xx[j]=InHist->GetBinCenter(j);
      yy[j]=InHist->GetBinContent(j);
      erryy[j]= InHist->GetBinError(j);
    }

//calculate chisquare
Double_t chisq = 0;
for (i=1;i<=nbins; i++) {
  //cout<<xx[i]<<"   "<<yy[i]<<"  "<<InFunc->Eval(xx[i])<<"   "<< (yy[i] -InFunc->Eval(xx[i]))/erryy[i]<< endl;
  Double_t delta  = (yy[i]-InFunc->Eval(xx[i]))/erryy[i];
  //cout<<delta<<endl;
  chisq += delta*delta;
 }


return chisq;

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
