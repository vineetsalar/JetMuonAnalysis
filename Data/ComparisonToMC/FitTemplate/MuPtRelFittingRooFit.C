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



//roofit includes
#include "RooGlobalFunc.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooHist.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"


void FitKnownFractionsMC();


Double_t Func_MuPtRel(Double_t *x, Double_t *par);
Double_t Func_MuPtRel_Tag(Double_t *x, Double_t *par);
Double_t Func_MuPtRel_Tag_NoLight(Double_t *x, Double_t *par);
Double_t Func_MuPtRel_Veto(Double_t *x, Double_t *par);

//================== Open the MC Template file ===========================================//
//TFile *file_MCTemplate =  new TFile("OutFile_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_14Aug2019.root","R");



//Added inclusive plots for mu-pt rel
//TFile *file_MCTemplate =  new TFile("OutFile_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeV_TighestMuon_RefPartonFlvForB_28Aug2019.root","R");


//PP MC (Mu+Jet Triggered) and MC pT re-weighted
TFile *file_MCTemplate =  new TFile("JetPlotOutPut_DiJet_PP2017MC_JetPt60GeVEta2MuPt5GeVEta24_TighestMuon_RefPartonFlvForB_TriggerApplied_PtReWeighted_10Oct19.root","R");
//================ Get the MC histograms ===============================//
TH1D *hist_temp_MuPtRel_Inclusive = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_Inclusive");
TH1D *hist_temp_MuPtRel_Light = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_Light");
TH1D *hist_temp_MuPtRel_C = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_C");
TH1D *hist_temp_MuPtRel_B = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_B");
//new Histogram with added charm
TH1D *hist_temp_MuPtRel_LightWithCharm = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_Light_With_C");


TH1D *hist_temp_MuPtRel_Inclusive_Tag = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_CSVTag_Inclusive");
TH1D *hist_temp_MuPtRel_Light_Tag = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_CSVTag_Light");
TH1D *hist_temp_MuPtRel_C_Tag = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_CSVTag_C");
TH1D *hist_temp_MuPtRel_B_Tag = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_CSVTag_B");
//new Histogram with added charm
TH1D *hist_temp_MuPtRel_LightWithCharm_Tag = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_CSVTag_Light_With_C");


TH1D *hist_temp_MuPtRel_Inclusive_Veto = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_CSVVeto_Inclusive");
TH1D *hist_temp_MuPtRel_Light_Veto = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_CSVVeto_Light");
TH1D *hist_temp_MuPtRel_C_Veto = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_CSVVeto_C");
TH1D *hist_temp_MuPtRel_B_Veto = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_CSVVeto_B");
//new Histogram with added charm
TH1D *hist_temp_MuPtRel_LightWithCharm_Veto = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_CSVVeto_Light_With_C");












Double_t CalcChi2(TH1D *InHist, TF1 *InFunc);

Int_t Scale_Hist_Index=0;
TH1D *Scale_Hist(TH1D *InHist, Double_t Weight, Int_t index);

Int_t Ratio_Hist_Index=0;
TH1D *Ratio_Hist(TH1D *InHistNum, TH1D *InHistDeno, Int_t index);

TLegend *MyLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2);

//function to fit the templates
Double_t FitTemplte(TH1D *DataHist, TF1* TempFunc, TCanvas* InCanvas);

using namespace RooFit;

void MuPtRelFitting()
{


  
  char LatexChar[400];
  
  TLatex *tb = new TLatex();
  tb->SetNDC();
  tb->SetTextColor(kBlack);
  tb->SetTextSize(0.04);
  
  TLatex *tr = new TLatex();
  tr->SetNDC();
  tr->SetTextColor(kRed);
  tr->SetTextSize(0.04);
  
  setTDRStyle();
  gStyle->SetPadBottomMargin(0.2);

  cout<<" ======================================= "<<endl;
  cout<<" EXAMPLE TEMPLTAE FITTING PROGRAM ROOFIT "<<endl;
  cout<<" Fitting the muon pt relative using the roofit program "<<endl;
  cout<<" ======================================= "<<endl;
  
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

  Double_t N_TotalJets_Integral = hist_data_MuPtRel->Integral(0,hist_data_MuPtRel->GetNbinsX()+1);
  Double_t N_TotalJets_Entries = hist_data_MuPtRel->GetEntries();

  Double_t N_TotalJets_Tag_Integral = hist_data_MuPtRel_Tag->Integral(0,hist_data_MuPtRel_Tag->GetNbinsX()+1);
  Double_t N_TotalJets_Tag_Entries = hist_data_MuPtRel_Tag->GetEntries();

  Double_t N_TotalJets_Veto_Integral = hist_data_MuPtRel_Veto->Integral(0,hist_data_MuPtRel_Veto->GetNbinsX()+1);
  Double_t N_TotalJets_Veto_Entries = hist_data_MuPtRel_Veto->GetEntries();

  cout<<" test the data histograms "<< N_TotalJets_Integral/(N_TotalJets_Tag_Integral+N_TotalJets_Veto_Integral)  <<"   "<<N_TotalJets_Entries/(N_TotalJets_Tag_Entries+N_TotalJets_Veto_Entries)<<endl;
  
 

  //FitKnownFractionsMC();




  // Make RooFit histograms from input root histograms
  RooRealVar MuPtRel("MuPtRel","MuPtRel",0.0,4.0);

  //import the data histogram in the roofit histogram
  RooDataHist MuPtRelData("MuPtRelData","MuPtRelData",MuPtRel,Import(*hist_data_MuPtRel));

  //import the template histograms 
  RooDataHist MuPtRelTempLight("MuPtRelTempLight","MuPtRelTempLight",MuPtRel,Import(*hist_temp_MuPtRel_LightWithCharm));
  RooDataHist MuPtRelTempBeauty("MuPtRelTempBeauty","MuPtRelTempBeauty",MuPtRel,Import(*hist_temp_MuPtRel_B));

  RooHistPdf model_light("model_light","model_light",MuPtRel,MuPtRelTempLight,0);
  RooHistPdf model_beauty("model_beauty","model_beauty",MuPtRel,MuPtRelTempBeauty,0);

  RooRealVar light_yield("light_yield","yield of light flvs",200000,0,10000000);	
  RooRealVar beauty_yield("beauty_yield","yield of beauty flv",200000,0,10000000); 	

  RooAddPdf model("model","model", RooArgList(model_light,model_beauty),RooArgList(light_yield,beauty_yield)); // Combines my MCs into one PDF model

  // Plot the imported histogram(s)
  RooPlot *dframe = MuPtRel.frame(Title("Data"));
  MuPtRelData.plotOn(dframe);

  RooPlot* mc1frame = MuPtRel.frame(Title("MC Light"));
  MuPtRelTempLight.plotOn(mc1frame);

  RooPlot* mc2frame = MuPtRel.frame(Title("MC Beauty"));
  MuPtRelTempBeauty.plotOn(mc2frame);
  
  // Make 2X1 Canvas
  TCanvas *Canvas_MuPtRel_DataMC = new TCanvas("Canvas_MuPtRel_DataMC","Canvas_MuPtRel_DataMC",1200,400);
  Canvas_MuPtRel_DataMC->Divide(3,1);//column x row
  Canvas_MuPtRel_DataMC->cd(1);
  dframe->Draw();
  
  Canvas_MuPtRel_DataMC->cd(2);
  mc1frame->Draw();

  Canvas_MuPtRel_DataMC->cd(3);
  mc2frame->Draw();
  

  RooFitResult* result = model.fitTo(MuPtRelData, RooFit::Extended(), RooFit::Minos(), RooFit::Save());

  //model.fitTo(MuPtRelData, Extended());

  result->Print();
  result->floatParsFinal().Print("s") ;

  
  //could not get the values from the roofit directly calculating fractions by hand

  Double_t LightYield = light_yield.getVal();
  Double_t BeautyYield = beauty_yield.getVal();
  Double_t TotalYield = (LightYield + BeautyYield);  
  
  Double_t LightFraction = LightYield/TotalYield;
  Double_t BeautyFraction = BeautyYield/TotalYield;

  
  RooPlot* fitFrame=MuPtRel.frame(Bins(40), Title("Fit Model"));
  //model.paramOn(fitFrame);
  MuPtRelData.plotOn(fitFrame, Name("MuPtRelData"), RooFit::LineColor(kBlack));
  model.plotOn(fitFrame, Name("model"), LineStyle(kDashed));
  model.plotOn(fitFrame, Components("model_light"),  LineColor(kBlue));
  model.plotOn(fitFrame, Components("model_beauty"), LineColor(kRed));

  Double_t Chi2NDF = fitFrame->chiSquare("model","MuPtRelData", 2); 
  //RooHist *hpull = fitFrame->pullHist("model","MuPtRelData");
  RooHist *hpull = fitFrame->pullHist();
  //RooHist *hpull = fitFrame->residHist();
  

  RooPlot* pullFrame = MuPtRel.frame(Title("pull"));
  pullFrame->addPlotable(hpull,"P") ;

  //hpull->plotOn(pullFrame,Name("hpull"), RooFit::LineColor(kBlack));

  
  //


  
  cout<<" =================================================== "<<endl;
  cout<<"chi2 "<< Chi2NDF <<endl;
  cout<<" =================================================== "<<endl;
  
  TCanvas *Canvas_data_MuPtRel_Fit = new TCanvas("Canvas_data_MuPtRel_Fit","Canvas_data_MuPtRel_Fit",800,400);
  Canvas_data_MuPtRel_Fit->Divide(2,1);//colum x row
  Canvas_data_MuPtRel_Fit->cd(1);
  fitFrame->Draw();
  
  tb->DrawLatex(0.5,0.84,Form("#chi^{2}/ndf %0.3f",Chi2NDF));
  tb->DrawLatex(0.5,0.80,Form("l %0.3f",LightFraction));
  tb->DrawLatex(0.5,0.76,Form("b %0.3f",BeautyFraction));

  Canvas_data_MuPtRel_Fit->cd(2);
  pullFrame->Draw();


  
  //===========================================================================//
  //=================== Fit the tag histogram =================================//
  //===========================================================================//


  //import the data histogram in the roofit histogram
  RooDataHist MuPtRelData_Tag("MuPtRelData_Tag","MuPtRelData_Tag",MuPtRel,Import(*hist_data_MuPtRel_Tag));

  //import the template histograms 
  RooDataHist MuPtRelTempLight_Tag("MuPtRelTempLight_Tag","MuPtRelTempLight_Tag",MuPtRel,Import(*hist_temp_MuPtRel_LightWithCharm_Tag));
  RooDataHist MuPtRelTempBeauty_Tag("MuPtRelTempBeauty_Tag","MuPtRelTempBeauty_Tag",MuPtRel,Import(*hist_temp_MuPtRel_B_Tag));

  RooHistPdf model_light_Tag("model_light_Tag","model_light_Tag",MuPtRel,MuPtRelTempLight_Tag,0);
  RooHistPdf model_beauty_Tag("model_beauty_Tag","model_beauty_Tag",MuPtRel,MuPtRelTempBeauty_Tag,0);

  RooRealVar light_yield_Tag("light_yield_Tag","yield of light flvs tag ",200000, 0,1500000);	
  RooRealVar beauty_yield_Tag("beauty_yield_Tag","yield of beauty flv tag",200000,0,2000000); 	

  RooAddPdf model_Tag("model_Tag","model_Tag", RooArgList(model_light_Tag,model_beauty_Tag),RooArgList(light_yield_Tag,beauty_yield_Tag)); // Combines my MCs into one PDF model

  // Plot the imported histogram(s)
  RooPlot *dframe_Tag = MuPtRel.frame(Title("Data Tag"));
  MuPtRelData_Tag.plotOn(dframe_Tag);

  RooPlot* mc1frame_Tag = MuPtRel.frame(Title("MC Light Tag"));
  MuPtRelTempLight_Tag.plotOn(mc1frame_Tag);

  RooPlot* mc2frame_Tag = MuPtRel.frame(Title("MC Beauty Tag"));
  MuPtRelTempBeauty_Tag.plotOn(mc2frame_Tag);
  
  // Make 2X1 Canvas
  TCanvas *Canvas_MuPtRel_DataMC_Tag = new TCanvas("Canvas_MuPtRel_DataMC_Tag","Canvas_MuPtRel_DataMC_Tag",1200,400);
  Canvas_MuPtRel_DataMC_Tag->Divide(3,1);//column x row
  Canvas_MuPtRel_DataMC_Tag->cd(1);
  dframe_Tag->Draw();
  
  Canvas_MuPtRel_DataMC_Tag->cd(2);
  mc1frame_Tag->Draw();

  Canvas_MuPtRel_DataMC_Tag->cd(3);
  mc2frame_Tag->Draw();
  
    
  RooFitResult* result_Tag = model_Tag.fitTo(MuPtRelData_Tag, RooFit::Extended(), RooFit::Minos(), RooFit::Save());

  //model.fitTo(MuPtRelData, Extended());

  result_Tag->Print();
  result_Tag->floatParsFinal().Print("s") ;


  Double_t LightYield_Tag = light_yield_Tag.getVal();
  Double_t BeautyYield_Tag = beauty_yield_Tag.getVal();
  Double_t TotalYield_Tag = (LightYield_Tag + BeautyYield_Tag);  
  
  Double_t LightFraction_Tag = LightYield_Tag/TotalYield_Tag;
  Double_t BeautyFraction_Tag = BeautyYield_Tag/TotalYield_Tag;
  
  
  RooPlot* fitFrame_Tag = MuPtRel.frame(Bins(40), Title("Fit Model Tag"));
  //model.paramOn(fitFrame);

  MuPtRelData_Tag.plotOn(fitFrame_Tag, Name("MuPtRelData_Tag"), RooFit::LineColor(kBlack));
  model_Tag.plotOn(fitFrame_Tag, Name("model_Tag"), LineStyle(kDashed));
  model_Tag.plotOn(fitFrame_Tag, Components("model_light_Tag"),  LineColor(kBlue));
  model_Tag.plotOn(fitFrame_Tag, Components("model_beauty_Tag"), LineColor(kRed));
  
  Double_t Chi2NDF_Tag = fitFrame_Tag->chiSquare("model_Tag","MuPtRelData_Tag", 2); 
  cout<<" =================================================== "<<endl;
  cout<<"chi2/NDF Tag"<< Chi2NDF_Tag <<endl;
  cout<<" =================================================== "<<endl;



  TCanvas *Canvas_data_MuPtRel_Fit_Tag = new TCanvas("Canvas_data_MuPtRel_Fit_Tag","Canvas_data_MuPtRel_Fit_Tag",800,400);
  Canvas_data_MuPtRel_Fit_Tag->Divide(2,1);//colum x row
  Canvas_data_MuPtRel_Fit_Tag->cd(1);
  fitFrame_Tag->Draw();


  tb->DrawLatex(0.5,0.84,Form("#chi^{2}/ndf %0.3f",Chi2NDF_Tag));
  tb->DrawLatex(0.5,0.80,Form("l %0.3f",LightFraction_Tag));
  tb->DrawLatex(0.5,0.76,Form("b %0.3f",BeautyFraction_Tag));



  //===========================================================================//
  //=================== Fit the veto histogram =================================//
  //===========================================================================//

  //import the data histogram in the roofit histogram
  RooDataHist MuPtRelData_Veto("MuPtRelData_Veto","MuPtRelData_Veto",MuPtRel,Import(*hist_data_MuPtRel_Veto));

  //import the template histograms 
  RooDataHist MuPtRelTempLight_Veto("MuPtRelTempLight_Veto","MuPtRelTempLight_Veto",MuPtRel,Import(*hist_temp_MuPtRel_LightWithCharm_Veto));
  RooDataHist MuPtRelTempBeauty_Veto("MuPtRelTempBeauty_Veto","MuPtRelTempBeauty_Veto",MuPtRel,Import(*hist_temp_MuPtRel_B_Veto));

  RooHistPdf model_light_Veto("model_light_Veto","model_light_Veto",MuPtRel,MuPtRelTempLight_Veto,0);
  RooHistPdf model_beauty_Veto("model_beauty_Veto","model_beauty_Veto",MuPtRel,MuPtRelTempBeauty_Veto,0);

  RooRealVar light_yield_Veto("light_yield_Veto","yield of light flvs tag ",200000,0,2500000);	
  RooRealVar beauty_yield_Veto("beauty_yield_Veto","yield of beauty flv tag",200000,0,2000000); 	

  RooAddPdf model_Veto("model_Veto","model_Veto", RooArgList(model_light_Veto,model_beauty_Veto),RooArgList(light_yield_Veto,beauty_yield_Veto)); // Combines my MCs into one PDF model

  // Plot the imported histogram(s)
  RooPlot *dframe_Veto = MuPtRel.frame(Title("Data Veto"));
  MuPtRelData_Veto.plotOn(dframe_Veto);

  RooPlot* mc1frame_Veto = MuPtRel.frame(Title("MC Light Veto"));
  MuPtRelTempLight_Veto.plotOn(mc1frame_Veto);

  RooPlot* mc2frame_Veto = MuPtRel.frame(Title("MC Beauty Veto"));
  MuPtRelTempBeauty_Veto.plotOn(mc2frame_Veto);
  
  // Make 2X1 Canvas
  TCanvas *Canvas_MuPtRel_DataMC_Veto = new TCanvas("Canvas_MuPtRel_DataMC_Veto","Canvas_MuPtRel_DataMC_Veto",1200,400);
  Canvas_MuPtRel_DataMC_Veto->Divide(3,1);//column x row
  Canvas_MuPtRel_DataMC_Veto->cd(1);
  dframe_Veto->Draw();
  
  Canvas_MuPtRel_DataMC_Veto->cd(2);
  mc1frame_Veto->Draw();

  Canvas_MuPtRel_DataMC_Veto->cd(3);
  mc2frame_Veto->Draw();
  
    
  RooFitResult* result_Veto = model_Veto.fitTo(MuPtRelData_Veto, RooFit::Extended(), RooFit::Minos(), RooFit::Save());

  //model.fitTo(MuPtRelData, Extended());

  result_Veto->Print();
  result_Veto->floatParsFinal().Print("s") ;


  Double_t LightYield_Veto = light_yield_Veto.getVal();
  Double_t BeautyYield_Veto = beauty_yield_Veto.getVal();
  Double_t TotalYield_Veto = (LightYield_Veto + BeautyYield_Veto);  
  
  Double_t LightFraction_Veto = LightYield_Veto/TotalYield_Veto;
  Double_t BeautyFraction_Veto = BeautyYield_Veto/TotalYield_Veto;
  
  RooPlot* fitFrame_Veto = MuPtRel.frame(Bins(40), Title("Fit Model Veto"));

  //model.paramOn(fitFrame);
  MuPtRelData_Veto.plotOn(fitFrame_Veto, Name("MuPtRelData_Veto"), RooFit::LineColor(kBlack));
  model_Veto.plotOn(fitFrame_Veto, Name("model_Veto"), LineStyle(kDashed));
  model_Veto.plotOn(fitFrame_Veto, Components("model_light_Veto"),  LineColor(kBlue));
  model_Veto.plotOn(fitFrame_Veto, Components("model_beauty_Veto"), LineColor(kRed));


  Double_t Chi2NDF_Veto = fitFrame_Veto->chiSquare("model_Veto","MuPtRelData_Veto", 2); 
  cout<<" =================================================== "<<endl;
  cout<<"chi2/NDF Veto "<< Chi2NDF_Veto <<endl;
  cout<<" =================================================== "<<endl;


  
  TCanvas *Canvas_data_MuPtRel_Fit_Veto = new TCanvas("Canvas_data_MuPtRel_Fit_Veto","Canvas_data_MuPtRel_Fit_Veto",800,400);
  Canvas_data_MuPtRel_Fit_Veto->Divide(2,1);//colum x row
  Canvas_data_MuPtRel_Fit_Veto->cd(1);
  fitFrame_Veto->Draw();
  
  tb->DrawLatex(0.5,0.84,Form("#chi^{2}/ndf %0.3f",Chi2NDF_Veto));
  tb->DrawLatex(0.5,0.80,Form("l %0.3f",LightFraction_Veto));
  tb->DrawLatex(0.5,0.76,Form("b %0.3f",BeautyFraction_Veto));


  
  //============================================================================================================//
  //=========================================== Fit this model to data histogram ===============================//
  //============================================================================================================//

  

  TCanvas *Canvas_data_MuPtRel_Fit_All = new TCanvas("Canvas_data_MuPtRel_Fit_All","Canvas_data_MuPtRel_Fit_All",1200,400);
  Canvas_data_MuPtRel_Fit_All->Divide(3,1);//colum x row
  Canvas_data_MuPtRel_Fit_All->cd(1);

  fitFrame->Draw();
  
  tb->DrawLatex(0.5,0.84,Form("#chi^{2}/ndf %0.3f",Chi2NDF));
  tb->DrawLatex(0.5,0.80,Form("l %0.3f",LightFraction));
  tb->DrawLatex(0.5,0.76,Form("b %0.3f",BeautyFraction));

  Canvas_data_MuPtRel_Fit_All->cd(2);
  
  fitFrame_Tag->Draw();
  
  tb->DrawLatex(0.5,0.84,Form("#chi^{2}/ndf %0.3f",Chi2NDF_Tag));
  tb->DrawLatex(0.5,0.80,Form("l %0.3f",LightFraction_Tag));
  tb->DrawLatex(0.5,0.76,Form("b %0.3f",BeautyFraction_Tag));


  Canvas_data_MuPtRel_Fit_All->cd(3);
  
  fitFrame_Veto->Draw();
  
  tb->DrawLatex(0.5,0.84,Form("#chi^{2}/ndf %0.3f",Chi2NDF_Veto));
  tb->DrawLatex(0.5,0.80,Form("l %0.3f",LightFraction_Veto));
  tb->DrawLatex(0.5,0.76,Form("b %0.3f",BeautyFraction_Veto));


 Canvas_data_MuPtRel_Fit_All->SaveAs("plots/data_MuPtRel_Fit_roofit.pdf");
 Canvas_data_MuPtRel_Fit_All->SaveAs("plots/data_MuPtRel_Fit_roofit.png");


 cout<<" B EFFICIENCY USING ROOFIT "<< BeautyYield_Tag /(BeautyYield_Tag + BeautyYield_Veto)<<endl;

 
  
}





void FitKnownFractionsMC()
{

  // Start with original MC templates
  // Get the MC template histograms from the root file
  TH1D *hist_temp_MuPtRel_Light = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_Light_With_C");
  TH1D *hist_temp_MuPtRel_B = (TH1D*)file_MCTemplate->Get("CSVTagPlots/hist_MuPtRel_B");

  // Make a temp data from the known fractions of the templates
  const Int_t NBinsMuonPtRel = 40;
  const Double_t MuonPtRelMin = 0.0;
  const Double_t MuonPtRelMax = 4.0;

  TH1D *hist_data_MuPtRel_KnownFrac = new TH1D("hist_data_MuPtRel_KnownFrac","hist_data_MuPtRel_KnownFrac",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  TH1D *hist_Temp_MuPtRel_Light = new TH1D("hist_Temp_MuPtRel_Light","hist_Temp_MuPtRel_Light",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
  TH1D *hist_Temp_MuPtRel_Beauty = new TH1D("hist_Temp_MuPtRel_Beauty","hist_Temp_MuPtRel_Beauty",NBinsMuonPtRel,MuonPtRelMin,MuonPtRelMax);
 
 

  
  for (int i=0;i<6000;i++)			// Fill 'data' with Light MC template
    {
      Double_t MuPtRel = hist_temp_MuPtRel_Light->GetRandom();
      hist_data_MuPtRel_KnownFrac->Fill(MuPtRel);
    }
  

  for (int i=0;i<3000;i++)			// Fill 'data' with Beauty MC template
    {
      Double_t MuPtRel = hist_temp_MuPtRel_B->GetRandom();
      hist_data_MuPtRel_KnownFrac->Fill(MuPtRel);
    }
  

  //Fill the mc templates
  for (int i=0;i<500000;i++)
    {

      Double_t MuPtRel_Light = hist_temp_MuPtRel_Light->GetRandom();
      hist_Temp_MuPtRel_Light->Fill(MuPtRel_Light);

      Double_t MuPtRel_B = hist_temp_MuPtRel_B->GetRandom();
      hist_Temp_MuPtRel_Beauty->Fill(MuPtRel_B);


    }

  // Make RooFit histograms from input root histograms
  RooRealVar MuPtRel("MuPtRel","MuPtRel",0.0,4.0);

  //RooDataHist dh("dh", "dh", x, Import(*hh));
  RooDataHist MuPtRelData("MuPtRelData","MuPtRelData",MuPtRel,Import(*hist_data_MuPtRel_KnownFrac));


  RooDataHist MuPtRelTempLight("MuPtRelTempLight","MuPtRelTempLight",MuPtRel,Import(*hist_Temp_MuPtRel_Light));
  RooDataHist MuPtRelTempBeauty("MuPtRelTempBeauty","MuPtRelTempBeauty",MuPtRel,Import(*hist_Temp_MuPtRel_Beauty));

  
  
  //Make PDF from MC histograms
  //RooHistPdf histpdf1("histpdf1", "histpdf1", x, *hist1, 0);

  RooHistPdf model_light("model_light","model_light",MuPtRel,MuPtRelTempLight,0);
  RooHistPdf model_beauty("model_beauty","model_beauty",MuPtRel,MuPtRelTempBeauty,0);


  RooRealVar light_yield("light_yield","yield of light flvs",2000,0,10000000);	
  RooRealVar beauty_yield("beauty_yield","yield of beauty flv",2000,0,10000000); 	

  RooAddPdf model("model","model", RooArgList(model_light,model_beauty),RooArgList(light_yield,beauty_yield)); // Combines my MCs into one PDF model

  // Plot the imported histogram(s)
  RooPlot *dframe = MuPtRel.frame(Title("Data"));
  MuPtRelData.plotOn(dframe);

  RooPlot* mc1frame = MuPtRel.frame(Title("MC Light"));
  MuPtRelTempLight.plotOn(mc1frame);

  RooPlot* mc2frame = MuPtRel.frame(Title("MC Beauty"));
  MuPtRelTempBeauty.plotOn(mc2frame);
  
  // Make 2X1 Canvas
  TCanvas *Canvas_MuPtRel_DataMC = new TCanvas("Canvas_MuPtRel_DataMC","Canvas_MuPtRel_DataMC",1200,400);
  Canvas_MuPtRel_DataMC->Divide(3,1);//column x row
  Canvas_MuPtRel_DataMC->cd(1);
  dframe->Draw();
  
  Canvas_MuPtRel_DataMC->cd(2);
  mc1frame->Draw();

  Canvas_MuPtRel_DataMC->cd(3);
  mc2frame->Draw();
  

  RooFitResult* result = model.fitTo(MuPtRelData, RooFit::Extended(), RooFit::Minos(), RooFit::Save());

  //model.fitTo(MuPtRelData, Extended());

  result->Print();
  

  RooPlot* fitFrame=MuPtRel.frame(Bins(40), Title("Fit Model"));

  model.paramOn(fitFrame);
  MuPtRelData.plotOn(fitFrame, RooFit::LineColor(kRed));
  model.plotOn(fitFrame, LineStyle(kDashed));
  model.plotOn(fitFrame, Components("model_light"),  LineColor(kBlue));
  model.plotOn(fitFrame, Components("model_beauty"), LineColor(kRed));
  
  TCanvas *Canvas_data_MuPtRel_Fit = new TCanvas("Canvas_data_MuPtRel_Fit","Canvas_data_MuPtRel_Fit",800,400);
  Canvas_data_MuPtRel_Fit->Divide(2,1);//colum x row
  Canvas_data_MuPtRel_Fit->cd(1);
  fitFrame->Draw();

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
