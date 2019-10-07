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
#include "TObjArray.h"
#include "TFractionFitter.h"
#include "/Users/vineet/UICWork/CMS/tdrstyle.C"
#include "/Users/vineet/UICWork/CMS/CMS_lumi.C"

Double_t Func_MuPtRel(Double_t *x, Double_t *par);
Double_t Func_MuPtRel_Tag(Double_t *x, Double_t *par);
Double_t Func_MuPtRel_Tag_NoLight(Double_t *x, Double_t *par);
Double_t Func_MuPtRel_Veto(Double_t *x, Double_t *par);

//================== Open the MC Template file ===========================================//
//TFile *file_MCTemplate =  new TFile("OutFile_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_14Aug2019.root","R");



//Added inclusive plots for mu-pt rel
//TFile *file_MCTemplate =  new TFile("OutFile_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_28Aug2019.root","R");

//PP MC (Mu+Jet Triggered)
TFile *file_MCTemplate =  new TFile("OutFile_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_MuonJetTrigger.root","R");

//================ Get the MC histograms ===============================//
TH1D *hist_temp_MuPtRel_Inclusive = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_Inclusive");
TH1D *hist_temp_MuPtRel_Light = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_Light");
TH1D *hist_temp_MuPtRel_C = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_C");
TH1D *hist_temp_MuPtRel_B = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_B");

TH1D *hist_temp_MuPtRel_Light_Tag = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVTag_Light");
TH1D *hist_temp_MuPtRel_C_Tag = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVTag_C");
TH1D *hist_temp_MuPtRel_B_Tag = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVTag_B");

TH1D *hist_temp_MuPtRel_Light_Veto = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVVeto_Light");
TH1D *hist_temp_MuPtRel_C_Veto = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVVeto_C");
TH1D *hist_temp_MuPtRel_B_Veto = (TH1D*)file_MCTemplate->Get("hist_MuPtRel_CSVVeto_B");




Double_t CalcChi2(TH1D *InHist, TF1 *InFunc);

Int_t Scale_Hist_Index=0;
TH1D *Scale_Hist(TH1D *InHist, Double_t Weight, Int_t index);

Int_t Ratio_Hist_Index=0;
TH1D *Ratio_Hist(TH1D *InHistNum, TH1D *InHistDeno, Int_t index);

TLegend *MyLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2);

//function to fit the templates
Double_t FitTemplte(TH1D *DataHist, TF1* TempFunc, TCanvas* InCanvas);


void MuPtRelFitting()
{

  setTDRStyle();
  gStyle->SetPadBottomMargin(0.2);

  Double_t TSF = 1.0;
  hist_temp_MuPtRel_Light->Scale(TSF);
  hist_temp_MuPtRel_C->Scale(TSF);
  hist_temp_MuPtRel_B->Scale(TSF);

  
  cout<<" Fitting the muon pt relative "<<endl;

  // open the file with Pb+Pb data
  //TFile *file_Data =  new TFile("OutFile_PbPbData_HLT_MuonJet60_JetPtMin60_JetEtaMax2_MuEtaMax24_MuPtMin5_JetQualityOn_14Aug2019.root","R");

  // open the file with PP data 
  TFile *file_Data =  new TFile("OutFile_PP2017Data_HLT_MuonJet30_JetPtMin60_JetEtaMax2_MuEtaMax24_MuPtMin5_JetQualityOn_28Aug2019.root","R");


  // get the data histogram
  TH1D *hist_data_MuPtRel = (TH1D*)file_Data->Get("histMuonPtRel");
  hist_data_MuPtRel->SetMarkerSize(1.2);
  hist_data_MuPtRel->SetMarkerColor(6);
  hist_data_MuPtRel->SetLineColor(6);
    
  TH1D *hist_data_MuPtRel_Tag = (TH1D*)file_Data->Get("histMuonPtRelCSVTag");
  hist_data_MuPtRel_Tag->SetMarkerSize(1.2);
  hist_data_MuPtRel_Tag->SetMarkerColor(6);
  hist_data_MuPtRel_Tag->SetLineColor(6);
  
  TH1D *hist_data_MuPtRel_Veto = (TH1D*)file_Data->Get("histMuonPtRelCSVVeto");
  hist_data_MuPtRel_Veto->SetMarkerSize(1.2);
  hist_data_MuPtRel_Veto->SetMarkerColor(6);
  hist_data_MuPtRel_Veto->SetLineColor(6);
  
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







  
  /*================================================================================//
  //============================= Lets Try TFraction Fitter ==========================//
  //============================ Gives very large errors ============================//
  //================================================================================//
  TObjArray *mc = new TObjArray(3);
  mc->Add(hist_temp_MuPtRel_Light);
  mc->Add(hist_temp_MuPtRel_C);
  mc->Add(hist_temp_MuPtRel_B);
   
  TFractionFitter* fit = new TFractionFitter(hist_data_MuPtRel, mc,"V"); // initialise

  fit->Constrain(0,0.0,1.0);
  fit->Constrain(1,0.0,1.0);
  fit->Constrain(2,0.0,0.5); 

  Int_t status = fit->Fit();               // perform the fit
  cout<<"TFraction Fitter Results "<<endl;
  cout << "fit status: " << status << endl;
  cout<<"Chi2/NDF : "<< fit->GetChisquare() <<"/"<< fit->GetNDF() <<" Prob: "<< fit->GetProb() <<endl<<endl;



  if (status == 0) {// check on fit status
    new TCanvas;
    TH1F* result = (TH1F*) fit->GetPlot();
    hist_data_MuPtRel->Draw("p");
    result->SetLineColor(4);
    result->SetMarkerColor(4);
    result->Draw("Psame");
  }


  //Concerning the plot, when adding the MC histogram to perform their linear combination sum, you
  //need to normalise first to the data histogram and then scale by the fractions.
  //So you do
  //h0->Scale( ( h_data->Integral()/h0->Integral ) * w0 );
  ========================================================================================================*/

  
  //=====================================================================================================//
  //=====================================================================================================//
  //========================= Fitting MuPt Relative distribution ========================================//
  //==========================i) Inclusive ii) Tag iii) Veto ============================================//
  //=====================================================================================================//
  //make the function from the MC templates
  //const Int_t NN = 3;
  //TF1 *FitFunctionMuPtRel[3];
  // Array of three Data Histograms 
  // run a loop to fit all the three histograms in a loop
  
  //Fitting the inlusive (without any CSVv2 Cut)
    
  TF1 *FitFunctionMuPtRel = new TF1("FitFunctionMuPtRel", Func_MuPtRel, 0.0, 4.0, 3);
  FitFunctionMuPtRel->SetLineColor(1);
  
  FitFunctionMuPtRel->SetParameter(0, 10000.0);
  FitFunctionMuPtRel->SetParameter(1, 40000.0);
  FitFunctionMuPtRel->SetParameter(2, 50000.0);
  
  hist_data_MuPtRel->Fit("FitFunctionMuPtRel","0L","",0.0,4.0);
  FitFunctionMuPtRel->SetLineColor(1);
  
  Double_t Fit_Chi2 = FitFunctionMuPtRel->GetChisquare();
  Double_t Fit_NDF =  FitFunctionMuPtRel->GetNDF();
  Double_t Fit_Prob = FitFunctionMuPtRel->GetProb();
  
  Double_t Frac_Light = FitFunctionMuPtRel->GetParameter(0);
  Double_t Frac_C = FitFunctionMuPtRel->GetParameter(1);
  Double_t Frac_B = FitFunctionMuPtRel->GetParameter(2);

  Double_t Total = Frac_Light+Frac_C+Frac_B;
  
  cout<<"Chi2/NDF : "<<Fit_Chi2<<"/"<<Fit_NDF<<" Prob: "<<Fit_Prob<<endl<<endl;
  //cout<<" Chi2 by hand "<<CalcChi2(hist_data_MuPtRel, FitFunctionMuPtRel)<<endl;

  cout<<"Frac_Light "<<Frac_Light/Total <<endl;
  cout<<"Frac_C "<<Frac_C/Total<<endl;
  cout<<"Frac_B "<<Frac_B/Total<<endl;


  TH1D *Weighted_hist_temp_MuPtRel_Light = Scale_Hist(hist_temp_MuPtRel_Light, Frac_Light, Scale_Hist_Index++);
  TH1D *Weighted_hist_temp_MuPtRel_C = Scale_Hist(hist_temp_MuPtRel_C, Frac_C, Scale_Hist_Index++);
  TH1D *Weighted_hist_temp_MuPtRel_B = Scale_Hist(hist_temp_MuPtRel_B, Frac_B, Scale_Hist_Index++);

  THStack *hs_MuPtRel_All = new THStack("hs_MuPtRel_All","hs_MuPtRel_All");
  hs_MuPtRel_All->Add(Weighted_hist_temp_MuPtRel_Light);
  hs_MuPtRel_All->Add(Weighted_hist_temp_MuPtRel_C);
  hs_MuPtRel_All->Add(Weighted_hist_temp_MuPtRel_B);

  
  TCanvas *Canvas_data_MuPtRel_Fit = new TCanvas("Canvas_data_MuPtRel_Fit","Canvas_data_MuPtRel_Fit",800,400);
  Canvas_data_MuPtRel_Fit->Divide(2,1);//colum x row

  Canvas_data_MuPtRel_Fit->cd(1);
  hist_temp_MuPtRel_Light->SetMarkerColor(4);
  hist_temp_MuPtRel_Light->SetMarkerStyle(24);
  hist_temp_MuPtRel_Light->GetYaxis()->SetRangeUser(0.0,8.0);
  hist_temp_MuPtRel_Light->Draw();
  hist_temp_MuPtRel_C->SetMarkerColor(3);
  hist_temp_MuPtRel_C->Draw("same");
  hist_temp_MuPtRel_B->Draw("same");
  
  Canvas_data_MuPtRel_Fit->cd(2);
  gPad->SetLeftMargin(0.2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_data_MuPtRel->SetMarkerColor(6);
  hist_data_MuPtRel->SetLineColor(6);
  hist_data_MuPtRel->Draw("P");
  Canvas_data_MuPtRel_Fit->Update();
  FitFunctionMuPtRel->Draw("same");
  hs_MuPtRel_All->Draw("histsame");
  hist_data_MuPtRel->Draw("Psame");
  FitFunctionMuPtRel->Draw("same");

  Canvas_data_MuPtRel_Fit->SaveAs("plots/data_MuPtRel_Fit.pdf");
  Canvas_data_MuPtRel_Fit->SaveAs("plots/data_MuPtRel_Fit.png");

  //==============================================================================//
  //Fitting the CSVtag (CSVv2 > 0.9)
    
  TF1 *FitFunctionMuPtRel_Tag = new TF1("FitFunctionMuPtRel_Tag", Func_MuPtRel_Tag, 0.0, 4.0, 3);
  FitFunctionMuPtRel_Tag->SetLineColor(1);

  FitFunctionMuPtRel_Tag->SetParameter(0, 10000.0);
  FitFunctionMuPtRel_Tag->SetParameter(1, 40000.0);
  FitFunctionMuPtRel_Tag->SetParameter(2, 50000.0);

  
  FitFunctionMuPtRel_Tag->SetParLimits(0, 0.0,100000.0);
  FitFunctionMuPtRel_Tag->SetParLimits(1, 0.0,100000.0);
  FitFunctionMuPtRel_Tag->SetParLimits(2, 0.0001,1000000.0);
  
  
  
  hist_data_MuPtRel_Tag->Fit("FitFunctionMuPtRel_Tag","0L","",0.0,4.0);
  FitFunctionMuPtRel_Tag->SetLineColor(1);


  TCanvas *Canvas_data_MuPtRel_Fit_Tag = new TCanvas("Canvas_data_MuPtRel_Fit_Tag","Canvas_data_MuPtRel_Fit_Tag",800,400);
  Canvas_data_MuPtRel_Fit_Tag->Divide(2,1);//colum x row

  Canvas_data_MuPtRel_Fit_Tag->cd(1);
  
  hist_temp_MuPtRel_Light_Tag->SetMarkerColor(4);
  hist_temp_MuPtRel_Light_Tag->SetMarkerStyle(24);
  

  hist_temp_MuPtRel_C_Tag->SetMarkerColor(3);
  hist_temp_MuPtRel_C_Tag->SetLineColor(3);
  hist_temp_MuPtRel_B_Tag->GetYaxis()->SetRangeUser(0.0,8.0);
  hist_temp_MuPtRel_B_Tag->Draw();
  hist_temp_MuPtRel_C_Tag->Draw("same");
  hist_temp_MuPtRel_Light_Tag->Draw("same");
  
  Canvas_data_MuPtRel_Fit_Tag->cd(2);
  gPad->SetLeftMargin(0.2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_data_MuPtRel_Tag->SetMarkerColor(6);
  hist_data_MuPtRel_Tag->SetLineColor(6);
  hist_data_MuPtRel_Tag->Draw("P");
  Canvas_data_MuPtRel_Fit_Tag->Update();
  FitFunctionMuPtRel_Tag->Draw("same");
  //hs_MuPtRel_All->Draw("histsame");
  //hist_data_MuPtRel->Draw("Psame");
  //FitFunctionMuPtRel->Draw("same");

  Canvas_data_MuPtRel_Fit_Tag->SaveAs("plots/data_MuPtRel_Fit_Tag.pdf");
  Canvas_data_MuPtRel_Fit_Tag->SaveAs("plots/data_MuPtRel_Fit_Tag.png");




     
  TF1 *FitFunctionMuPtRel_Tag_NoLight = new TF1("FitFunctionMuPtRel_Tag_NoLight", Func_MuPtRel_Tag_NoLight, 0.0, 4.0, 2);
  FitFunctionMuPtRel_Tag_NoLight->SetLineColor(1);

  FitFunctionMuPtRel_Tag_NoLight->SetParameter(0, 10000.0);
  FitFunctionMuPtRel_Tag_NoLight->SetParameter(1, 40000.0);
    
  FitFunctionMuPtRel_Tag_NoLight->SetParLimits(0, 5000.0,100000.0);
  FitFunctionMuPtRel_Tag_NoLight->SetParLimits(1, 0.0,100000.0);
    
  
  hist_data_MuPtRel_Tag->Fit("FitFunctionMuPtRel_Tag_NoLight","0L","",0.0,4.0);
  FitFunctionMuPtRel_Tag_NoLight->SetLineColor(1);


  TCanvas *Canvas_data_MuPtRel_Fit_Tag_NoLight = new TCanvas("Canvas_data_MuPtRel_Fit_Tag_NoLight","Canvas_data_MuPtRel_Fit_Tag_NoLight",800,400);
  Canvas_data_MuPtRel_Fit_Tag_NoLight->Divide(2,1);//colum x row

  Canvas_data_MuPtRel_Fit_Tag_NoLight->cd(1);
  
  hist_temp_MuPtRel_Light_Tag->SetMarkerColor(4);
  hist_temp_MuPtRel_Light_Tag->SetMarkerStyle(24);
  

  hist_temp_MuPtRel_C_Tag->SetMarkerColor(3);
  hist_temp_MuPtRel_C_Tag->SetLineColor(3);
  hist_temp_MuPtRel_B_Tag->GetYaxis()->SetRangeUser(0.0,8.0);
  hist_temp_MuPtRel_B_Tag->Draw();
  hist_temp_MuPtRel_C_Tag->Draw("same");
  hist_temp_MuPtRel_Light_Tag->Draw("same");
  
  Canvas_data_MuPtRel_Fit_Tag_NoLight->cd(2);
  gPad->SetLeftMargin(0.2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_data_MuPtRel_Tag->SetMarkerColor(6);
  hist_data_MuPtRel_Tag->SetLineColor(6);
  hist_data_MuPtRel_Tag->Draw("P");
  Canvas_data_MuPtRel_Fit_Tag_NoLight->Update();
  FitFunctionMuPtRel_Tag->Draw("same");
  //hs_MuPtRel_All->Draw("histsame");
  //hist_data_MuPtRel->Draw("Psame");
  //FitFunctionMuPtRel->Draw("same");

  Canvas_data_MuPtRel_Fit_Tag_NoLight->SaveAs("plots/data_MuPtRel_Fit_Tag_NoLight.pdf");
  Canvas_data_MuPtRel_Fit_Tag_NoLight->SaveAs("plots/data_MuPtRel_Fit_Tag_NoLight.png");





  
  //==============================================================================//
  //Fitting the CSVVeto (CSVv2 < 0.9)
    
  TF1 *FitFunctionMuPtRel_Veto = new TF1("FitFunctionMuPtRel_Veto", Func_MuPtRel_Veto, 0.0, 4.0, 3);
  FitFunctionMuPtRel_Veto->SetLineColor(1);

  FitFunctionMuPtRel_Veto->SetParLimits(0, 0.0,100000.0);
  FitFunctionMuPtRel_Veto->SetParLimits(1, 0.0,100000.0);
  FitFunctionMuPtRel_Veto->SetParLimits(2, 0.0001,1000000.0);
  
  FitFunctionMuPtRel_Veto->SetParameter(0, 10000.0);
  FitFunctionMuPtRel_Veto->SetParameter(1, 10000.0);
  FitFunctionMuPtRel_Veto->SetParameter(2, 50000.0);
  
  hist_data_MuPtRel_Veto->Fit("FitFunctionMuPtRel_Veto","0L","",0.0,4.0);
  FitFunctionMuPtRel_Veto->SetLineColor(1);


  TCanvas *Canvas_data_MuPtRel_Fit_Veto = new TCanvas("Canvas_data_MuPtRel_Fit_Veto","Canvas_data_MuPtRel_Fit_Veto",800,400);
  Canvas_data_MuPtRel_Fit_Veto->Divide(2,1);//colum x row

  Canvas_data_MuPtRel_Fit_Veto->cd(1);
  
  hist_temp_MuPtRel_Light_Veto->SetMarkerColor(4);
  hist_temp_MuPtRel_Light_Veto->SetMarkerStyle(24);
  

  hist_temp_MuPtRel_C_Veto->SetMarkerColor(3);
  hist_temp_MuPtRel_C_Veto->SetLineColor(3);
  hist_temp_MuPtRel_B_Veto->GetYaxis()->SetRangeUser(0.0,8.0);
  hist_temp_MuPtRel_B_Veto->Draw();
  hist_temp_MuPtRel_C_Veto->Draw("same");
  hist_temp_MuPtRel_Light_Veto->Draw("same");
  
  Canvas_data_MuPtRel_Fit_Veto->cd(2);
  gPad->SetLeftMargin(0.2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_data_MuPtRel_Veto->SetMarkerColor(6);
  hist_data_MuPtRel_Veto->SetLineColor(6);
  hist_data_MuPtRel_Veto->Draw("P");
  Canvas_data_MuPtRel_Fit_Veto->Update();
  FitFunctionMuPtRel_Veto->Draw("same");
  //hs_MuPtRel_All->Draw("histsame");
  //hist_data_MuPtRel->Draw("Psame");
  //FitFunctionMuPtRel->Draw("same");

  Canvas_data_MuPtRel_Fit_Veto->SaveAs("plots/data_MuPtRel_Fit_Veto.pdf");
  Canvas_data_MuPtRel_Fit_Veto->SaveAs("plots/data_MuPtRel_Fit_Veto.png");
  
  

  



  


  
}




/*
Double_t FitTemplte(TH1D *DataHist, TF1* TempFunc, TCanvas* InCanvas)
{

  TF1 *FitFunctionMuPtRel = new TF1(Form("TempFunc"), TempFunc, 0.0, 4.0, 3);
  FitFunctionMuPtRel->SetLineColor(1);

  //FitFunctionMuPtRel->SetParameter(0, 10781.0);
  //FitFunctionMuPtRel->SetParameter(1, 40290.0);
  //FitFunctionMuPtRel->SetParameter(2, 58036.0);
  
  hist_data_MuPtRel->Fit("FitFunctionMuPtRel","0L","",0.0,4.0);
  FitFunctionMuPtRel->SetLineColor(4);
  
  Double_t Fit_Chi2 = FitFunctionMuPtRel->GetChisquare();
  Double_t Fit_NDF =  FitFunctionMuPtRel->GetNDF();
  Double_t Fit_Prob = FitFunctionMuPtRel->GetProb();
  
  Double_t Frac_Light = FitFunctionMuPtRel->GetParameter(0);
  Double_t Frac_C = FitFunctionMuPtRel->GetParameter(1);
  Double_t Frac_B = FitFunctionMuPtRel->GetParameter(2);

  Double_t Total = Frac_Light+Frac_C+Frac_B;
  
  cout<<"Chi2/NDF : "<<Fit_Chi2<<"/"<<Fit_NDF<<" Prob: "<<Fit_Prob<<endl<<endl;
  cout<<" Chi2 by hand "<<CalcChi2(hist_data_MuPtRel, FitFunctionMuPtRel)<<endl;

  cout<<"Frac_Light "<<Frac_Light/Total <<endl;
  cout<<"Frac_C "<<Frac_C/Total<<endl;
  cout<<"Frac_B "<<Frac_B/Total<<endl;

  TH1D *Weighted_hist_temp_MuPtRel_Light = Scale_Hist(hist_temp_MuPtRel_Light, Frac_Light, Scale_Hist_Index++);
  TH1D *Weighted_hist_temp_MuPtRel_C = Scale_Hist(hist_temp_MuPtRel_C, Frac_C, Scale_Hist_Index++);
  TH1D *Weighted_hist_temp_MuPtRel_B = Scale_Hist(hist_temp_MuPtRel_B, Frac_B, Scale_Hist_Index++);

  THStack *hs_MuPtRel_All = new THStack("hs_MuPtRel_All","hs_MuPtRel_All");
  hs_MuPtRel_All->Add(Weighted_hist_temp_MuPtRel_Light);
  hs_MuPtRel_All->Add(Weighted_hist_temp_MuPtRel_C);
  hs_MuPtRel_All->Add(Weighted_hist_temp_MuPtRel_B);

  
  TCanvas *Canvas_data_MuPtRel_Fit = new TCanvas("Canvas_data_MuPtRel_Fit","Canvas_data_MuPtRel_Fit",800,400);
  Canvas_data_MuPtRel_Fit->Divide(2,1);//colum x row


  Canvas_data_MuPtRel_Fit->cd(1);
  hist_temp_MuPtRel_Light->Draw();
  hist_temp_MuPtRel_C->SetMarkerColor(3);
  hist_temp_MuPtRel_C->Draw("same");
  hist_temp_MuPtRel_B->Draw("same");
  

  
  Canvas_data_MuPtRel_Fit->cd(2);
  gPad->SetLeftMargin(0.2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_data_MuPtRel->SetMarkerColor(6);
  hist_data_MuPtRel->SetLineColor(6);
  hist_data_MuPtRel->Draw("P");
  Canvas_data_MuPtRel_Fit->Update();
  FitFunctionMuPtRel->Draw("same");

  //Weighted_hist_temp_MuPtRel_Light->Draw("same");
  //Weighted_hist_temp_MuPtRel_C->Draw("same");
  //Weighted_hist_temp_MuPtRel_B->Draw("same");

  hs_MuPtRel_All->Draw("histsame");
  hist_data_MuPtRel->Draw("Psame");
  FitFunctionMuPtRel->Draw("same");

  Canvas_data_MuPtRel_Fit->SaveAs("plots/data_MuPtRel_Fit.pdf");
  Canvas_data_MuPtRel_Fit->SaveAs("plots/data_MuPtRel_Fit.png");





}
*/





Double_t Func_MuPtRel(Double_t *x, Double_t *par)
{
  Double_t Frac_Light = par[0];  
  Double_t Frac_C = par[1];
  Double_t Frac_B = par[2];
  Double_t xx = x[0];
  Int_t bin = hist_temp_MuPtRel_Light->GetXaxis()->FindBin(xx);
  Double_t Sigma = Frac_Light*hist_temp_MuPtRel_Light->GetBinContent(bin)
    + Frac_C*hist_temp_MuPtRel_C->GetBinContent(bin)
    + Frac_B*hist_temp_MuPtRel_B->GetBinContent(bin);
  return Sigma;
  
}



Double_t Func_MuPtRel_Tag(Double_t *x, Double_t *par)
{
  
  Double_t Frac_Light = par[0];  
  Double_t Frac_C = par[1];
  Double_t Frac_B = par[2];
  Double_t xx = x[0];
  Int_t bin = hist_temp_MuPtRel_Light_Tag->GetXaxis()->FindBin(xx);

  Double_t Sigma = Frac_Light*hist_temp_MuPtRel_Light_Tag->GetBinContent(bin)
  + Frac_C*hist_temp_MuPtRel_C_Tag->GetBinContent(bin)
  + Frac_B*hist_temp_MuPtRel_B_Tag->GetBinContent(bin);

  return Sigma;
}




Double_t Func_MuPtRel_Tag_NoLight(Double_t *x, Double_t *par)
{
  Double_t Frac_C = par[0];
  Double_t Frac_B = par[1];
  Double_t xx = x[0];
  Int_t bin = hist_temp_MuPtRel_C_Tag->GetXaxis()->FindBin(xx);
  
  Double_t Sigma = Frac_C*hist_temp_MuPtRel_C_Tag->GetBinContent(bin)
    + Frac_B*hist_temp_MuPtRel_B_Tag->GetBinContent(bin);
  
  return Sigma;
  
}





Double_t Func_MuPtRel_Veto(Double_t *x, Double_t *par)
{
  Double_t Frac_Light = par[0];  
  Double_t Frac_C = par[1];
  Double_t Frac_B = par[2];
  Double_t xx = x[0];
  Int_t bin = hist_temp_MuPtRel_Light_Veto->GetXaxis()->FindBin(xx);
  
  Double_t Sigma = Frac_Light*hist_temp_MuPtRel_Light_Veto->GetBinContent(bin)
    + Frac_C*hist_temp_MuPtRel_C_Veto->GetBinContent(bin)
    + Frac_B*hist_temp_MuPtRel_B_Veto->GetBinContent(bin);
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
  cout<<xx[i]<<"   "<<yy[i]<<"  "<<erryy[i]<<"  "<<InFunc->Eval(xx[i])<<"   "<< (yy[i] -InFunc->Eval(xx[i]))/erryy[i]<< endl;
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
