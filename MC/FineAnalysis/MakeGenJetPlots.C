#include "MyMethod.h"





void MakeGenJetPlots(TFile *file_in, Double_t GenJetPtMin, Double_t GenMuPtCut)
{
  
  
  
  
  setTDRStyle();
  gStyle->SetPadBottomMargin(0.2);
  TH1::SetDefaultSumw2();
  

  TLatex *tb = new TLatex();
  tb->SetNDC();
  tb->SetTextColor(kBlack);
  tb->SetTextSize(0.04);
  
  
  TLatex *tr = new TLatex();
  tr->SetNDC();
  tr->SetTextColor(kRed);
  tr->SetTextSize(0.04);
  
  
  
  
  //==============================================================//
  //====== object of class MyMethod for common functions =========//
  //==============================================================//
  int Flv_Legend_Index_Local = 0;
  int Flv_Legend_Index_Local_V = 0;
  const int NFlvLocal = 6;
  
  MyMethod *GenJetMethod = new MyMethod();
  
  
  
  
  

  // ============================================================================================== //
  // ============================================================================================== //
  // ====================== GEN JET ANALYSIS ====================================================== //
  // ====================== 1D HISTO GEN JET PT AND JET FLAVOUR =================================== //
  // ============================================================================================== //
  
  
  cout<<endl<<endl<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<" ====================== GEN JET ANALYSIS ======================================= "<<endl;
  cout<<" ====================== 1D HISTO GEN JET PT AND JET FLAVOUR ==================== "<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<endl<<endl<<endl;



  //===== Get the 1D graphs for GenJets from file for all flavours
  TH1D *hist_GenJetPt=(TH1D*)file_in->Get("histGenJetPt");
  TH1D *hist_GenJetEta=(TH1D*)file_in->Get("histGenJetEta");
  TH1D *hist_GenJetPhi=(TH1D*)file_in->Get("histGenJetPhi");

  new TCanvas;
  gPad->SetLogy(1);
  hist_GenJetPt->Draw();
  gPad->SaveAs("Plots/GenJets/GenJetPt.png");
  gPad->SaveAs("Plots/GenJets/GenJetPt.pdf");


  new TCanvas;
  hist_GenJetEta->Draw();
  gPad->SaveAs("Plots/GenJets/GenJetEta.png");
  gPad->SaveAs("Plots/GenJets/GenJetEta.pdf");


  new TCanvas;
  hist_GenJetPhi->Draw();
  gPad->SaveAs("Plots/GenJets/GenJetPhi.png");
  gPad->SaveAs("Plots/GenJets/GenJetPhi.pdf");




  //====== graph for light flavour ================//
  TH1D *hist_GenJetPtLight=(TH1D*)file_in->Get("histGenJetPtLight");
  new TCanvas;
  gPad->SetLogy(1);
  hist_GenJetPtLight->Draw();
  gPad->SaveAs("Plots/GenJets/GenJetPtLight.png");
  gPad->SaveAs("Plots/GenJets/GenJetPtLight.pdf");



  TH1D *hist_GenJetPtUp=(TH1D*)file_in->Get("histGenJetPtUp");
  TH1D *hist_GenJetPtDown=(TH1D*)file_in->Get("histGenJetPtDown");
  TH1D *hist_GenJetPtStrange=(TH1D*)file_in->Get("histGenJetPtStrange");
  TH1D *hist_GenJetPtCharm=(TH1D*)file_in->Get("histGenJetPtCharm");
  
  new TCanvas;
  gPad->SetLogy(1);
  hist_GenJetPtCharm->Draw();
  gPad->SaveAs("Plots/GenJets/GenJetPtCharm.png");
  gPad->SaveAs("Plots/GenJets/GenJetPtCharm.pdf");


  TH1D *hist_GenJetPtBeauty=(TH1D*)file_in->Get("histGenJetPtBeauty");
  new TCanvas;
  gPad->SetLogy(1);
  hist_GenJetPtBeauty->Draw();
  gPad->SaveAs("Plots/GenJets/GenJetPtBeauty.png");
  gPad->SaveAs("Plots/GenJets/GenJetPtBeauty.pdf");


  
  TH1D *hist_GenJetPtGluon=(TH1D*)file_in->Get("histGenJetPtGluon");
  new TCanvas;
  gPad->SetLogy(1);
  hist_GenJetPtGluon->Draw();
  gPad->SaveAs("Plots/GenJets/GenJetPtGluon.png");
  gPad->SaveAs("Plots/GenJets/GenJetPtGluon.pdf");



  Double_t TotalIntegralOfGenJets = hist_GenJetPt->Integral(0,hist_GenJetPt->GetNbinsX());
  
  Double_t TotalIntegralOfLightGenJets =  hist_GenJetPtLight->Integral(0,hist_GenJetPtLight->GetNbinsX());

  Double_t TotalIntegralOfUpGenJets = hist_GenJetPtUp->Integral(0,hist_GenJetPtUp->GetNbinsX());
  Double_t TotalIntegralOfDownGenJets = hist_GenJetPtDown->Integral(0,hist_GenJetPtDown->GetNbinsX());
  Double_t TotalIntegralOfStrangeGenJets = hist_GenJetPtStrange->Integral(0,hist_GenJetPtStrange->GetNbinsX());
  Double_t TotalIntegralOfCharmGenJets = hist_GenJetPtCharm->Integral(0,hist_GenJetPtCharm->GetNbinsX());
  Double_t TotalIntegralOfBeautyGenJets = hist_GenJetPtBeauty->Integral(0,hist_GenJetPtBeauty->GetNbinsX());
  Double_t TotalIntegralOfGluonGenJets = hist_GenJetPtGluon->Integral(0,hist_GenJetPtGluon->GetNbinsX());


  Double_t TotalGenJetFraction = TotalIntegralOfGenJets/TotalIntegralOfGenJets;
  Double_t LightGenJetFraction = TotalIntegralOfLightGenJets/TotalIntegralOfGenJets;

  Double_t UpGenJetFraction = TotalIntegralOfUpGenJets/TotalIntegralOfGenJets;
  Double_t DownGenJetFraction = TotalIntegralOfDownGenJets/TotalIntegralOfGenJets;
  Double_t StrangeGenJetFraction = TotalIntegralOfStrangeGenJets/TotalIntegralOfGenJets;
  Double_t CharmGenJetFraction = TotalIntegralOfCharmGenJets/TotalIntegralOfGenJets;
  Double_t BeautyGenJetFraction = TotalIntegralOfBeautyGenJets/TotalIntegralOfGenJets;
  Double_t GluonGenJetFraction = TotalIntegralOfGluonGenJets/TotalIntegralOfGenJets;
  
  cout<<endl<<endl;
  cout<<" Total Integral of GenJets above "<< GenJetPtMin<< " GeV/c pT "<< TotalIntegralOfGenJets <<" fraction " <<TotalGenJetFraction<<endl;
  cout<<" Total Integral of Up GenJets (u) above "<< GenJetPtMin<< " GeV/c pT "<< TotalIntegralOfUpGenJets <<" fraction  "<<UpGenJetFraction<<endl;
  cout<<" Total Integral of Down GenJets (d) above "<< GenJetPtMin<< " GeV/c pT "<< TotalIntegralOfDownGenJets<<" fraction  "<<DownGenJetFraction<<endl;
  cout<<" Total Integral of Strange GenJets (s) above "<< GenJetPtMin<< " GeV/c pT "<< TotalIntegralOfStrangeGenJets<<" fraction  "<<StrangeGenJetFraction<<endl;
  cout<<" Total Integral of Charm GenJets (c) above "<< GenJetPtMin<< " GeV/c pT "<< TotalIntegralOfCharmGenJets<<" fraction  "<<CharmGenJetFraction<<endl;
  cout<<" Total Integral of Beauty GenJets (b) above "<< GenJetPtMin<< " GeV/c pT "<< TotalIntegralOfBeautyGenJets<<" fraction  "<<BeautyGenJetFraction<<endl;
  cout<<" Total Integral of Gluon GenJets (g) above "<< GenJetPtMin<< " GeV/c pT "<< TotalIntegralOfGluonGenJets<<" fraction  "<<GluonGenJetFraction<<endl;
  cout<<endl<<endl;
  
  
  // making a test histogram with flavour tags as X axis labels 
  const char *ABC[NFlvLocal] = {"u","d","s","c","b","g"};
  
  TH1D *h = new TH1D("h","test",6,0,6);
  for (int i=1;i<=6;i++) h->GetXaxis()->SetBinLabel(i,ABC[i-1]);
  h->GetYaxis()->SetTitle("fraction");
  h->SetMaximum(1);

  // making a graph for Gen Jet Fractions
  Double_t GenJetFrac[NFlvLocal]={UpGenJetFraction,DownGenJetFraction,StrangeGenJetFraction,CharmGenJetFraction,BeautyGenJetFraction,GluonGenJetFraction};
  Double_t GenJetType[NFlvLocal]={0.5,1.5,2.5,3.5,4.5,5.5};

  TGraph *graph_GenJetFracGraph = new TGraph (6,GenJetType,GenJetFrac);
  graph_GenJetFracGraph->GetYaxis()->SetRangeUser(0,1);
  new TCanvas;
  h->Draw();
  graph_GenJetFracGraph->SetFillColorAlpha(kBlue,0.8);
  graph_GenJetFracGraph->Draw("Bsame");

  gPad->SaveAs("Plots/GenJets/GenJetFrac.png");
  gPad->SaveAs("Plots/GenJets/GenJetFrac.pdf");


 //  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  // ============================================================================================== //
  // ====================== GEN JET ANALYSIS ENDS ================================================ //
  // ====================== 1D HISTO GEN JET PT AND JET FLAVOUR ENDS ============================= //
  // ============================================================================================== //
  //  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //



  cout<<endl<<endl<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<" ====================== GEN JET ANALYSIS WITH MUONS ============================ "<<endl;
  cout<<" ====================== 1D HISTO GEN JET PT AND JET FLAVOUR ==================== "<<endl;
  cout<<" ====================== 1D HISTO GEN MUON PT INSIDE JET ======================== "<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<endl<<endl<<endl;

  //========== Get the Gen Muon Graphs ======================================//
  TH1D *hist_GenMuonPt=(TH1D*)file_in->Get("histGenMuonPt");
  //======== Making a clone to be used in the efficiency calculations ======//
  TH1D *hist_GenMuonPt_ForEff=(TH1D*)hist_GenMuonPt->Clone();
  TH1D *hist_GenMuonEta=(TH1D*)file_in->Get("histGenMuonEta");
  TH1D *hist_GenMuonPhi=(TH1D*)file_in->Get("histGenMuonPhi");

  GenJetMethod->rebinAsymmetric(hist_GenMuonPt, GenJetMethod->NBins_GenMuonPt_VarSize-1, GenJetMethod->GenMuonPtBinEdges);
  hist_GenMuonPt->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");


  //cout<<" Total Number of GenMuons above "<< GenMuPtCut<< " GeV/c pT "<<hist_GenMuonPt->GetEntries()<<endl;
  
  new TCanvas;
  gPad->SetLogy(1);
  hist_GenMuonPt->Draw();
  
  gPad->SaveAs("Plots/GenJets/GenMuonPt.png");
  gPad->SaveAs("Plots/GenJets/GenMuonPt.pdf");
  
  
  new TCanvas;
  hist_GenMuonEta->Draw();
  
  gPad->SaveAs("Plots/GenJets/GenMuonEta.png");
  gPad->SaveAs("Plots/GenJets/GenMuonEta.pdf");
  
  
  new TCanvas;
  hist_GenMuonPhi->Draw();
  
  gPad->SaveAs("Plots/GenJets/GenMuonPhi.png");
  gPad->SaveAs("Plots/GenJets/GenMuonPhi.pdf");


  TH1D *hist_GenMuonGenJetDR=(TH1D*)file_in->Get("histGenMuonGenJetDR");
  new TCanvas;
  gPad->SetLogy(1);
  hist_GenMuonGenJetDR->Draw();
  gPad->SaveAs("Plots/GenJets/GenMuonGenJetDR.png");
  gPad->SaveAs("Plots/GenJets/GenMuonGenJetDR.pdf");

  
  TH1D *hist_GenMuonGenJetDPhi=(TH1D*)file_in->Get("histGenMuonGenJetDPhi");

  
  new TCanvas;
  gPad->SetLogy(1);
  hist_GenMuonGenJetDPhi->Draw();

  gPad->SaveAs("Plots/GenJets/GenMuonGenJetDPhi.png");
  gPad->SaveAs("Plots/GenJets/GenMuonGenJetDPhi.pdf");




  TH1D *hist_GenMuonGenJetPtTotal=(TH1D*)file_in->Get("histGenMuonGenJetPtTotal");
  TH1D *hist_GenMuonGenJetPtLight=(TH1D*)file_in->Get("histGenMuonGenJetPtLight");
  
  new TCanvas;
  gPad->SetLogy(1);
  hist_GenMuonGenJetPtLight->Draw();
  gPad->SaveAs("Plots/GenJets/GenMuonGenJetPtLight.png");
  gPad->SaveAs("Plots/GenJets/GenMuonGenJetPtLight.pdf");



  TH1D *hist_GenMuonGenJetPtUp=(TH1D*)file_in->Get("histGenMuonGenJetPtUp");
  TH1D *hist_GenMuonGenJetPtDown=(TH1D*)file_in->Get("histGenMuonGenJetPtDown");
  TH1D *hist_GenMuonGenJetPtStrange=(TH1D*)file_in->Get("histGenMuonGenJetPtStrange");
  TH1D *hist_GenMuonGenJetPtCharm=(TH1D*)file_in->Get("histGenMuonGenJetPtCharm");
  
  
  new TCanvas;
  gPad->SetLogy(1);
  hist_GenMuonGenJetPtCharm->Draw();

  gPad->SaveAs("Plots/GenJets/GenMuonGenJetPtCharm.png");
  gPad->SaveAs("Plots/GenJets/GenMuonGenJetPtCharm.pdf");


  TH1D *hist_GenMuonGenJetPtBeauty=(TH1D*)file_in->Get("histGenMuonGenJetPtBeauty");
  
  new TCanvas;
  gPad->SetLogy(1);
  hist_GenMuonGenJetPtBeauty->Draw();

  gPad->SaveAs("Plots/GenJets/GenMuonGenJetPtBeauty.png");
  gPad->SaveAs("Plots/GenJets/GenMuonGenJetPtBeauty.pdf");


  

  TH1D *hist_GenMuonGenJetPtGluon=(TH1D*)file_in->Get("histGenMuonGenJetPtGluon");

  new TCanvas;
  gPad->SetLogy(1);
  hist_GenMuonGenJetPtGluon->Draw();

  gPad->SaveAs("Plots/GenJets/GenMuonGenJetPtGluon.png");
  gPad->SaveAs("Plots/GenJets/GenMuonGenJetPtGluon.pdf");

  
  Double_t TotalIntegralOfGenMuonGenJets = hist_GenMuonGenJetPtTotal->Integral(0,hist_GenMuonGenJetPtTotal->GetNbinsX());
  Double_t TotalIntegralOfLightGenMuonGenJets = hist_GenMuonGenJetPtLight->Integral(0,hist_GenMuonGenJetPtLight->GetNbinsX());
  Double_t TotalIntegralOfUpGenMuonGenJets = hist_GenMuonGenJetPtUp->Integral(0,hist_GenMuonGenJetPtUp->GetNbinsX());
  Double_t TotalIntegralOfDownGenMuonGenJets = hist_GenMuonGenJetPtDown->Integral(0,hist_GenMuonGenJetPtDown->GetNbinsX());
  Double_t TotalIntegralOfStrangeGenMuonGenJets = hist_GenMuonGenJetPtStrange->Integral(0,hist_GenMuonGenJetPtStrange->GetNbinsX());
  Double_t TotalIntegralOfCharmGenMuonGenJets = hist_GenMuonGenJetPtCharm->Integral(0,hist_GenMuonGenJetPtCharm->GetNbinsX());
  Double_t TotalIntegralOfBeautyGenMuonGenJets = hist_GenMuonGenJetPtBeauty->Integral(0,hist_GenMuonGenJetPtBeauty->GetNbinsX());
  Double_t TotalIntegralOfGluonGenMuonGenJets = hist_GenMuonGenJetPtGluon->Integral(0,hist_GenMuonGenJetPtGluon->GetNbinsX());

  
  
  Double_t TotalGenMuonGenJetFraction = TotalIntegralOfGenMuonGenJets/TotalIntegralOfGenMuonGenJets;
  Double_t LightGenMuonGenJetFraction = TotalIntegralOfLightGenMuonGenJets/TotalIntegralOfGenMuonGenJets;
  Double_t UpGenMuonGenJetFraction = TotalIntegralOfUpGenMuonGenJets/TotalIntegralOfGenMuonGenJets;
  Double_t DownGenMuonGenJetFraction = TotalIntegralOfDownGenMuonGenJets/TotalIntegralOfGenMuonGenJets;
  Double_t StrangeGenMuonGenJetFraction = TotalIntegralOfStrangeGenMuonGenJets/TotalIntegralOfGenMuonGenJets;
  Double_t CharmGenMuonGenJetFraction = TotalIntegralOfCharmGenMuonGenJets/TotalIntegralOfGenMuonGenJets;
  Double_t BeautyGenMuonGenJetFraction = TotalIntegralOfBeautyGenMuonGenJets/TotalIntegralOfGenMuonGenJets;
  Double_t GluonGenMuonGenJetFraction = TotalIntegralOfGluonGenMuonGenJets/TotalIntegralOfGenMuonGenJets;

  cout<<endl<<endl;
  
  cout<<" Total Integral of GenMuonGenJets above "<< GenMuPtCut<< " GeV/c pT "<< TotalIntegralOfGenMuonGenJets <<" fraction  "<< TotalGenMuonGenJetFraction <<endl;
  cout<<" Total Integral of Light GenMuonGenJets (u,d,s) above "<< GenMuPtCut<< " GeV/c pT "<< TotalIntegralOfLightGenMuonGenJets <<" fraction  "<<LightGenMuonGenJetFraction<<endl;
  cout<<" Total Integral of Up GenMuonGenJets (u) above "<< GenMuPtCut<< " GeV/c pT "<< TotalIntegralOfUpGenMuonGenJets <<" fraction  "<<UpGenMuonGenJetFraction<<endl;
  cout<<" Total Integral of Down GenMuonGenJets (u) above "<< GenMuPtCut<< " GeV/c pT "<< TotalIntegralOfDownGenMuonGenJets <<" fraction  "<<DownGenMuonGenJetFraction<<endl;
  cout<<" Total Integral of Strange GenMuonGenJets (u) above "<< GenMuPtCut<< " GeV/c pT "<< TotalIntegralOfStrangeGenMuonGenJets <<" fraction  "<<StrangeGenMuonGenJetFraction<<endl;
  cout<<" Total Integral of Charm GenMuonGenJets (c) above "<< GenMuPtCut<< " GeV/c pT "<< TotalIntegralOfCharmGenMuonGenJets <<" fraction  "<<CharmGenMuonGenJetFraction<<endl;
  cout<<" Total Integral of Beauty GenMuonGenJets (b) above "<< GenMuPtCut<< " GeV/c pT "<< TotalIntegralOfBeautyGenMuonGenJets <<" fraction  "<<BeautyGenMuonGenJetFraction<<endl;
  cout<<" Total Integral of Gluon GenMuonGenJets (g) above "<< GenMuPtCut<< " GeV/c pT "<< TotalIntegralOfGluonGenMuonGenJets <<" fraction  "<<GluonGenMuonGenJetFraction<<endl;
  
  cout<<endl<<endl;
  
  Double_t GenMuonGenJetFrac[NFlvLocal]={UpGenMuonGenJetFraction,DownGenMuonGenJetFraction,StrangeGenMuonGenJetFraction,CharmGenMuonGenJetFraction,BeautyGenMuonGenJetFraction,GluonGenMuonGenJetFraction};
  Double_t GenMuonGenJetType[NFlvLocal]={0.5,1.5,2.5,3.5,4.5,5.5};
  
  TGraph *graph_GenMuonGenJetFracGraph = new TGraph (6,GenMuonGenJetType,GenMuonGenJetFrac);
  

  graph_GenMuonGenJetFracGraph->GetXaxis()->SetTitle("JetType");
  graph_GenMuonGenJetFracGraph->GetYaxis()->SetTitle("Jet Fraction");

  graph_GenMuonGenJetFracGraph->SetMarkerStyle(21);
  graph_GenMuonGenJetFracGraph->SetMarkerColor(2);
  graph_GenMuonGenJetFracGraph->GetYaxis()->SetRangeUser(0,1);

  
  TLegend *lgd_GenMuonGenJetFrac = new TLegend(0.25,0.75,0.59,0.85,"","brNDC");
  lgd_GenMuonGenJetFrac->SetBorderSize(0);
  lgd_GenMuonGenJetFrac->SetTextFont(42);
  lgd_GenMuonGenJetFrac->SetLineColor(1);
  lgd_GenMuonGenJetFrac->SetLineStyle(1);
  lgd_GenMuonGenJetFrac->SetLineWidth(1);
  lgd_GenMuonGenJetFrac->SetFillColor(19);
  lgd_GenMuonGenJetFrac->SetFillStyle(0);

  lgd_GenMuonGenJetFrac->AddEntry(graph_GenJetFracGraph,"All Gen Jets","f");
  lgd_GenMuonGenJetFrac->AddEntry(graph_GenMuonGenJetFracGraph,"Gen Jets with Muons","f");

  new TCanvas;
  h->Draw();
  graph_GenMuonGenJetFracGraph->SetFillColorAlpha(kRed,0.6);
  graph_GenMuonGenJetFracGraph->Draw("Bsame");
  

  new TCanvas;
  h->Draw();
  graph_GenJetFracGraph->Draw("Bsame");
  graph_GenMuonGenJetFracGraph->Draw("Bsame");
  lgd_GenMuonGenJetFrac->Draw("same");
  gPad->SaveAs("Plots/GenJets/GenMuonGenJetFrac.png");
  gPad->SaveAs("Plots/GenJets/GenMuonGenJetFrac.pdf");

  cout<<endl<<endl;

  
  //  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  // =============================================================================== //
  // ====================== 1D  GEN JET ANALYSIS WITH MUONS ENDS ============================ //
  // =============================================================================== //
  //  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  

  cout<<endl<<endl<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<" ====================== GEN JET ANALYSIS ======================================= "<<endl;
  cout<<" ====================== 2D HISTO GEN JET PT AND JET FLAVOUR ==================== "<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<endl<<endl<<endl;

  
  //================================================================================================================//
  //==================================== pT dependence of  Jet Fractions for different flavours =====================//
  //===============================================================================================================//
  
  //Get the 2D Histo of JetPt, Flavour
  TH2D *hist_GenMaster_GenJetPt_Flavour = (TH2D*)file_in->Get("hist_GenMaster_GenJetPt_Flavour");
  
  //================= Get the bins numbers for different flavours ================//
  Int_t FlavourBinMinForU = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(1);
  Int_t FlavourBinMaxForU = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(1);
  
  Int_t FlavourBinMinForD = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(2);
  Int_t FlavourBinMaxForD = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(2);
  
  Int_t FlavourBinMinForS = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(3);
  Int_t FlavourBinMaxForS = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(3);
    
  Int_t FlavourBinMinForC = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(4);
  Int_t FlavourBinMaxForC = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(4);
      
  Int_t FlavourBinMinForB = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(5);
  Int_t FlavourBinMaxForB = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(5);
  
  Int_t FlavourBinMinForG = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(6);
  Int_t FlavourBinMaxForG = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(6);

  //-999  //===== unknown flavour
  Int_t FlavourBinMinForUn = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(7);
  Int_t FlavourBinMaxForUn = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(7);
  //0
  Int_t FlavourBinMinForZe = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(8);
  Int_t FlavourBinMaxForZe = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(8);
  //-10000  //====== Reco Jet not found
  Int_t FlavourBinMinForNR = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(9);
  Int_t FlavourBinMaxForNR = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(9);

  //============ Total Jets =======================//
  Int_t FlavourBinMinForInc = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(1);
  Int_t FlavourBinMaxForInc = hist_GenMaster_GenJetPt_Flavour->GetYaxis()->FindBin(9);


  //======== Get the pT distribution for all Jets (Inclusive) ============================//
  TH1 *hist_GenJetPt_Inclusive = hist_GenMaster_GenJetPt_Flavour->ProjectionX("hist_GenJetPt_Inclusive",FlavourBinMinForInc,FlavourBinMaxForInc);
  hist_GenJetPt_Inclusive->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_GenJetPt_Inclusive->GetXaxis()->SetTitle("p_{T}(GeV/c)");
  
    
  TH1 *hist_GenJetPt_U = hist_GenMaster_GenJetPt_Flavour->ProjectionX("hist_GenJetPt_U",FlavourBinMinForU,FlavourBinMaxForU);
  TH1 *hist_GenJetPt_D = hist_GenMaster_GenJetPt_Flavour->ProjectionX("hist_GenJetPt_D",FlavourBinMinForD,FlavourBinMaxForD);
  TH1 *hist_GenJetPt_S = hist_GenMaster_GenJetPt_Flavour->ProjectionX("hist_GenJetPt_S",FlavourBinMinForS,FlavourBinMaxForS);
  TH1 *hist_GenJetPt_C = hist_GenMaster_GenJetPt_Flavour->ProjectionX("hist_GenJetPt_C",FlavourBinMinForC,FlavourBinMaxForC);
  TH1 *hist_GenJetPt_B = hist_GenMaster_GenJetPt_Flavour->ProjectionX("hist_GenJetPt_B",FlavourBinMinForB,FlavourBinMaxForB);
  TH1 *hist_GenJetPt_G = hist_GenMaster_GenJetPt_Flavour->ProjectionX("hist_GenJetPt_G",FlavourBinMinForG,FlavourBinMaxForG);

  TH1 *hist_GenJetPt_Un = hist_GenMaster_GenJetPt_Flavour->ProjectionX("hist_GenJetPt_Un",FlavourBinMinForUn,FlavourBinMaxForUn);
  TH1 *hist_GenJetPt_Ze = hist_GenMaster_GenJetPt_Flavour->ProjectionX("hist_GenJetPt_Ze",FlavourBinMinForZe,FlavourBinMaxForZe);
  TH1 *hist_GenJetPt_NR = hist_GenMaster_GenJetPt_Flavour->ProjectionX("hist_GenJetPt_NR",FlavourBinMinForNR,FlavourBinMaxForNR);
  
  
  //==================================================================//
  //========= ASYMATRIC REBINNING GEN JETS ===========================//
  //==================================================================//
    
  GenJetMethod->rebinAsymmetric(hist_GenJetPt_Inclusive, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenJetPt_U, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenJetPt_D, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenJetPt_S, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenJetPt_C, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenJetPt_B, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenJetPt_G, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);

  GenJetMethod->rebinAsymmetric(hist_GenJetPt_Un, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenJetPt_Ze, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenJetPt_NR, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);

  
  //============= Calculate Ratios for Flv Jets / all Jets ==========================//

  TH1D *hist_Ratio_GenJetPt_U_GenJetPt_Inclusive = GenJetMethod->RatioHistogram(hist_GenJetPt_U,hist_GenJetPt_Inclusive,1);
  TH1D *hist_Ratio_GenJetPt_D_GenJetPt_Inclusive = GenJetMethod->RatioHistogram(hist_GenJetPt_D,hist_GenJetPt_Inclusive,1);
  TH1D *hist_Ratio_GenJetPt_S_GenJetPt_Inclusive = GenJetMethod->RatioHistogram(hist_GenJetPt_S,hist_GenJetPt_Inclusive,1);
  TH1D *hist_Ratio_GenJetPt_C_GenJetPt_Inclusive = GenJetMethod->RatioHistogram(hist_GenJetPt_C,hist_GenJetPt_Inclusive,1);
  TH1D *hist_Ratio_GenJetPt_B_GenJetPt_Inclusive = GenJetMethod->RatioHistogram(hist_GenJetPt_B,hist_GenJetPt_Inclusive,1);
  TH1D *hist_Ratio_GenJetPt_G_GenJetPt_Inclusive = GenJetMethod->RatioHistogram(hist_GenJetPt_G,hist_GenJetPt_Inclusive,1);

  TH1D *hist_Ratio_GenJetPt_Un_GenJetPt_Inclusive = GenJetMethod->RatioHistogram(hist_GenJetPt_Un,hist_GenJetPt_Inclusive,1);
  TH1D *hist_Ratio_GenJetPt_Ze_GenJetPt_Inclusive = GenJetMethod->RatioHistogram(hist_GenJetPt_Ze,hist_GenJetPt_Inclusive,1);
  TH1D *hist_Ratio_GenJetPt_NR_GenJetPt_Inclusive = GenJetMethod->RatioHistogram(hist_GenJetPt_NR,hist_GenJetPt_Inclusive,1);
  
  
  //============= Set the Marker Size, Marker Color etc. ======================//
  GenJetMethod->FlavouredHistogram(hist_Ratio_GenJetPt_U_GenJetPt_Inclusive, GenJetMethod->LineColorArray[1], GenJetMethod->MarkerColorArray[1], GenJetMethod->MarkerStyleArray[1],GenJetMethod->MarkerSizeArray[1]);
  GenJetMethod->FlavouredHistogram(hist_Ratio_GenJetPt_D_GenJetPt_Inclusive, GenJetMethod->LineColorArray[2], GenJetMethod->MarkerColorArray[2], GenJetMethod->MarkerStyleArray[2],GenJetMethod->MarkerSizeArray[2]);
  GenJetMethod->FlavouredHistogram(hist_Ratio_GenJetPt_S_GenJetPt_Inclusive, GenJetMethod->LineColorArray[3], GenJetMethod->MarkerColorArray[3], GenJetMethod->MarkerStyleArray[3],GenJetMethod->MarkerSizeArray[3]);
  GenJetMethod->FlavouredHistogram(hist_Ratio_GenJetPt_C_GenJetPt_Inclusive, GenJetMethod->LineColorArray[4], GenJetMethod->MarkerColorArray[4], GenJetMethod->MarkerStyleArray[4],GenJetMethod->MarkerSizeArray[4]);
  GenJetMethod->FlavouredHistogram(hist_Ratio_GenJetPt_B_GenJetPt_Inclusive, GenJetMethod->LineColorArray[5], GenJetMethod->MarkerColorArray[5], GenJetMethod->MarkerStyleArray[5],GenJetMethod->MarkerSizeArray[5]);
  GenJetMethod->FlavouredHistogram(hist_Ratio_GenJetPt_G_GenJetPt_Inclusive, GenJetMethod->LineColorArray[6], GenJetMethod->MarkerColorArray[6], GenJetMethod->MarkerStyleArray[6],GenJetMethod->MarkerSizeArray[6]);


  GenJetMethod->FlavouredHistogram(hist_Ratio_GenJetPt_Un_GenJetPt_Inclusive, GenJetMethod->LineColorArray[1], GenJetMethod->MarkerColorArray[1], GenJetMethod->MarkerStyleArray[1],GenJetMethod->MarkerSizeArray[1]);
  GenJetMethod->FlavouredHistogram(hist_Ratio_GenJetPt_Ze_GenJetPt_Inclusive, GenJetMethod->LineColorArray[2], GenJetMethod->MarkerColorArray[2], GenJetMethod->MarkerStyleArray[2],GenJetMethod->MarkerSizeArray[2]);
  GenJetMethod->FlavouredHistogram(hist_Ratio_GenJetPt_NR_GenJetPt_Inclusive, GenJetMethod->LineColorArray[3], GenJetMethod->MarkerColorArray[3], GenJetMethod->MarkerStyleArray[3],GenJetMethod->MarkerSizeArray[3]);



  //========= Define a Canvas for the Ratio histograms ============================//
  TCanvas *Canvas_Ratio_GenJetPt_Flv_GenJetPt_Inclusive = new TCanvas("Canvas_Ratio_GenJetPt_Flv_GenJetPt_Inclusive","Canvas_Ratio_GenJetPt_Flv_GenJetPt_Inclusive",800,800);
  Canvas_Ratio_GenJetPt_Flv_GenJetPt_Inclusive->cd(1);
  gPad->SetLogy(1);
  gPad->SetBottomMargin(0.2);

  //============== Get a Ghost histogram, because we want X axis to start from 0
  TH1D *hist_GenJetPt_Ghost = GenJetMethod->Get_Ghost_Hist("hist_GenJetPt_Ghost","hist_GenJetPt_Ghost",0.005,1.5,"gen Jet p_{T} (GeV/c)","gen Jet Fraction");
  hist_GenJetPt_Ghost->Draw();

  hist_Ratio_GenJetPt_U_GenJetPt_Inclusive->Draw("same");
  hist_Ratio_GenJetPt_D_GenJetPt_Inclusive->Draw("same");
  hist_Ratio_GenJetPt_S_GenJetPt_Inclusive->Draw("same");
  hist_Ratio_GenJetPt_C_GenJetPt_Inclusive->Draw("same");
  hist_Ratio_GenJetPt_B_GenJetPt_Inclusive->Draw("same");
  hist_Ratio_GenJetPt_G_GenJetPt_Inclusive->Draw("same");

  //Draw the Legend
  GenJetMethod->DrawFlavourLegend(0.20,0.76,0.32,0.96, Flv_Legend_Index_Local++);

  // Save the picture
  gPad->SaveAs("Plots/GenJets/Ratio_GenJetPt_Flv_GenJetPt_Inclusive.png");
  gPad->SaveAs("Plots/GenJets/Ratio_GenJetPt_Flv_GenJetPt_Inclusive.pdf");


  // =========== Canvas for three Unknown Flvs
  TCanvas *Canvas_Ratio_GenJetPt_FlvUn_GenJetPt_Inclusive = new TCanvas("Canvas_Ratio_GenJetPt_FlvUn_GenJetPt_Inclusive","Canvas_Ratio_GenJetPt_FlvUn_GenJetPt_Inclusive",800,800);
  Canvas_Ratio_GenJetPt_FlvUn_GenJetPt_Inclusive->cd(1);
  gPad->SetBottomMargin(0.2);

  // =========== Ghost Histo for three Unknown Flvs
  TH1D *hist_GenJetPt_Un_Ghost = GenJetMethod->Get_Ghost_Hist("hist_GenJetPt_Un_Ghost","hist_GenJetPt_Un_Ghost",0.0,0.5,"gen Jet p_{T} (GeV/c)","gen Jet Fraction");
  hist_GenJetPt_Un_Ghost->Draw();
  hist_Ratio_GenJetPt_Un_GenJetPt_Inclusive->Draw("same");
  hist_Ratio_GenJetPt_Ze_GenJetPt_Inclusive->Draw("same");
  hist_Ratio_GenJetPt_NR_GenJetPt_Inclusive->Draw("same");
  GenJetMethod->DrawFlavourLegendUn(0.20,0.76,0.32,0.96, Flv_Legend_Index_Local++);
  
  gPad->SaveAs("Plots/GenJets/Ratio_GenJetPt_FlvUn_GenJetPt_Inclusive.png");
  gPad->SaveAs("Plots/GenJets/Ratio_GenJetPt_FlvUn_GenJetPt_Inclusive.pdf");


  //================================================================================================================//
  //==================================== Integrated  Gen Jet Fractions with different Gen Jet pT Cuts =====================//
  //===============================================================================================================//
  
  const int NJetPtCut =4;
  Double_t JetPtCut[NJetPtCut]={0.0,80.0,100.0,120.0};
  
  //These events are taken from the Jet Trigger Table
  //Events are above 40 (prescaled), 80 (prescaled), 100, 120 GeV Jet triggers
  Double_t TotalJetTriggerEvents[NJetPtCut] = {1050052.0, 5893687.0, 11416148.0, 2546890};

  //Array of graphs
  TGraph *graph_GenJetPtCut_GenJetFrac[NJetPtCut];

  // Array to Store the Jet Fraction for different flavours
  Double_t  GenJetPtCut_Flavour_Fraction[NJetPtCut][NFlvLocal+1]={0.0};
  

  char LatexChar[400];
  // Canvas defined outside of the Jet Pt Cut loop
  TCanvas *CanvasGenJetFractionJetPtCut = new TCanvas("CanvasGenJetFractionJetPtCut","CanvasGenJetFractionJetPtCut",800,800);
  CanvasGenJetFractionJetPtCut->Divide(2,2);

  //Loop for the Jet pT Cuts
  for(int i =0;i<NJetPtCut;i++){

    Int_t JetPtBinMin = hist_GenMaster_GenJetPt_Flavour->GetXaxis()->FindBin(JetPtCut[i]);
    Int_t JetPtBinMax = hist_GenMaster_GenJetPt_Flavour->GetXaxis()->GetNbins()+1;
    
    cout<<" Jet Pt Bin Min "<< JetPtBinMin <<" Jet Pt Bin Max "<< JetPtBinMax <<endl; 

    //Get the Flavour Histgram after putting the cut on Jet pT
    TH1 *hist_GenMaster_GenJetPt_Flavour_ProjY = hist_GenMaster_GenJetPt_Flavour->ProjectionY(Form("hist_GenMaster_GenJetPt_Flavour_ProjY_%d",i),JetPtBinMin,JetPtBinMax);

    
    Double_t  GenMaster_GenJetPt_Flavour_IntegralY = hist_GenMaster_GenJetPt_Flavour_ProjY->Integral(0,hist_GenMaster_GenJetPt_Flavour_ProjY->GetNbinsX());// no overflow
    
    Int_t NBinsHisto = hist_GenMaster_GenJetPt_Flavour_ProjY->GetNbinsX(); // number of bins in Y (flavour axis)
    
    cout<<" Number of flavours NBinsHisto "<<NBinsHisto<<endl;
     
    cout<<endl;
    cout<<" Jet Fractions with Jet Pt Cut "<< JetPtCut[i] <<endl;


    //====== Flavour Loop inside the Jet Pt Cut Loop
    for(int j = 1; j <=NBinsHisto; j++)
      
      {
	TH1 *hist_GenMaster_GenJetPt_Flavour_ProjY = hist_GenMaster_GenJetPt_Flavour->ProjectionY("hist_GenMaster_GenJetPt_Flavour_ProjY",JetPtBinMin,JetPtBinMax);
	
	Double_t JetFraction = hist_GenMaster_GenJetPt_Flavour_ProjY->GetBinContent(j)/GenMaster_GenJetPt_Flavour_IntegralY;
	
	GenJetPtCut_Flavour_Fraction[i][j] = JetFraction; 
	
	cout<<"  flavour bin centre "<<hist_GenMaster_GenJetPt_Flavour_ProjY->GetBinCenter(j)<<
	  " bin content "<<hist_GenMaster_GenJetPt_Flavour_ProjY->GetBinContent(j)<<
	  " fraction    "<<hist_GenMaster_GenJetPt_Flavour_ProjY->GetBinContent(j)/GenMaster_GenJetPt_Flavour_IntegralY<<endl;
      }
    cout<<endl<<endl;
    
    
    Double_t t_GenJetFrac[NFlvLocal]={GenJetPtCut_Flavour_Fraction[i][1], GenJetPtCut_Flavour_Fraction[i][2], GenJetPtCut_Flavour_Fraction[i][3],
				     GenJetPtCut_Flavour_Fraction[i][4],GenJetPtCut_Flavour_Fraction[i][5],GenJetPtCut_Flavour_Fraction[i][6]};
    
    graph_GenJetPtCut_GenJetFrac[i] = new TGraph ( NFlvLocal, GenMuonGenJetType, t_GenJetFrac);
    graph_GenJetPtCut_GenJetFrac[i]->SetFillColor(kBlue);
    
    

    char Ch_JetPtCutPlot[100];
    sprintf(Ch_JetPtCutPlot,"%1.2f",JetPtCut[i]);
    TString JetPtCutPlot = TString(Ch_JetPtCutPlot);
    
    
    
    CanvasGenJetFractionJetPtCut->cd(i+1);
    gPad->SetTopMargin(0.1);
    gPad->SetBottomMargin(0.2);
    
    h->Draw();
    graph_GenJetPtCut_GenJetFrac[i]->Draw("Bsame");
    
    sprintf(LatexChar,"Jet p_{T} > %.1f GeV/c",JetPtCut[i]);
    
    tb->DrawLatex(0.28,0.68,LatexChar);
    
    CanvasGenJetFractionJetPtCut->SaveAs("Plots/GenJets/GenJetFrac_JetPtCut_All.png");
    CanvasGenJetFractionJetPtCut->SaveAs("Plots/GenJets/GenJetFrac_JetPtCut_All.pdf");
    
    
    

  }//JetPt Cut loop
  cout<<endl<<endl;
  
  cout<<" =============================================================================== "<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<endl<<endl<<endl;
  cout<<endl<<endl<<endl;
  //  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  //================================================================================================================//
  //==================================== Integrated  Jet Fractions with different Jet pT Cuts ENDS ===============//
  //===============================================================================================================//
   //  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //





  //====================================================================================================//
  //===================== Calculating GenFraction, Tagging Efficiency, GenFraction Double Ratios =======//
  //====================== and effect of differnt muon pT cut on them ==================================//
  //====================================================================================================//
  const int NMuonPtCut =4;
  const Double_t MuonPtCut[NMuonPtCut]={5.0,12.5,16.0,20.0};
  
  cout<<endl<<endl<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<" ====================== GEN JET ANALYSIS ======================================= "<<endl;
  cout<<" ============= 3D HISTO GEN JET PT, MUON PT AND JET FLAVOUR ==================== "<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<endl<<endl<<endl;
  
  //========================================================================================================//
  //========================== Get the 3D Histo of JetPt, MuonPt, Flavour ==================================//
  //========================================================================================================//
  TH3D *hist_GenMaster_GenJetPt_GenMuPt_Flavour=(TH3D*)file_in->Get("hist_GenMaster_GenJetPt_GenMuPt_Flavour");

  // This is integrated Jet fractions, for different flavours, with different muon pt cuts
  Double_t  GenMuPtCut_Flavour_Fraction[NMuonPtCut][NFlvLocal+1]={0.0};

  // this is used in latex table to get the events for differnt Jet flavours
  // above a pT thershold how many muons come with a particular flavour
  // if you know the muon trigger events you can estimate the events with differnt
  // flavours
  Double_t  GenMuPtCut_Flavour_GenMuonFraction[NMuonPtCut][NFlvLocal+1]={0.0};
  
  //Array of graphs
  // integrated Jet fraction graph array, with differnt muon pt cuts
  TGraph *graph_GenMuonPtCut_GenJetFrac[NMuonPtCut];

  //==========================================================================================//
  //================== Tagging Efficiency ====================================================//
  //is defined as Jets with muon for a particular flavour / all Jets of that particular flavour
  //==========================================================================================//
  //=========================================================================================//

  TH1 *hist_GenTaggingEff_ForU[NMuonPtCut];
  TH1 *hist_GenTaggingEff_ForD[NMuonPtCut];
  TH1 *hist_GenTaggingEff_ForS[NMuonPtCut];
  TH1 *hist_GenTaggingEff_ForC[NMuonPtCut];
  TH1 *hist_GenTaggingEff_ForB[NMuonPtCut];
  TH1 *hist_GenTaggingEff_ForG[NMuonPtCut];
  TH1 *hist_GenTaggingEff_ForUn[NMuonPtCut];
  TH1 *hist_GenTaggingEff_ForZe[NMuonPtCut];
  TH1 *hist_GenTaggingEff_ForNR[NMuonPtCut];



  //==========================================================================================//
  //================== Purity is defined as ====================================================//
  // Jets with muon for a particular flavour / all Jets with muons
  // this is kind of Jet fractions when we have muon requirements for both numerator and deno //
  //=========================================================================================//
  
  TH1 *hist_GenPurity_ForU[NMuonPtCut];
  TH1 *hist_GenPurity_ForD[NMuonPtCut];
  TH1 *hist_GenPurity_ForS[NMuonPtCut];
  TH1 *hist_GenPurity_ForC[NMuonPtCut];
  TH1 *hist_GenPurity_ForB[NMuonPtCut];
  TH1 *hist_GenPurity_ForG[NMuonPtCut];
  TH1 *hist_GenPurity_ForUn[NMuonPtCut];
  TH1 *hist_GenPurity_ForZe[NMuonPtCut];
  TH1 *hist_GenPurity_ForNR[NMuonPtCut];


  //============================================================================================//
  //==================== Gen Jet Fraction Double Ratios =========================================//
  //=========== Jet Fraction (with muon) / Gen Jet Fraction (no muon requirement) ==============//
  //============================================================================================//
    
  TH1 *hist_GenPurity_DR_ForU[NMuonPtCut];
  TH1 *hist_GenPurity_DR_ForD[NMuonPtCut];
  TH1 *hist_GenPurity_DR_ForS[NMuonPtCut];
  TH1 *hist_GenPurity_DR_ForC[NMuonPtCut];
  TH1 *hist_GenPurity_DR_ForB[NMuonPtCut];
  TH1 *hist_GenPurity_DR_ForG[NMuonPtCut];
  
  TH1 *hist_GenPurity_DR_ForUn[NMuonPtCut];
  TH1 *hist_GenPurity_DR_ForZe[NMuonPtCut];
  TH1 *hist_GenPurity_DR_ForNR[NMuonPtCut];



  //====== Jet Pt Bins ===============================================================//
  
  Int_t JetPtBinMin = hist_GenMaster_GenJetPt_GenMuPt_Flavour->GetXaxis()->FindBin(GenJetPtMin); // Minimum pT cut for gen Jets
  Int_t JetPtBinMax = hist_GenMaster_GenJetPt_GenMuPt_Flavour->GetXaxis()->GetNbins(); // no overflow
    
  cout<<" Jet Pt Bin Min "<< JetPtBinMin <<" Jet Pt Bin Max "<< JetPtBinMax <<endl; 

  // This is coming from up
  cout<<" FlavourBinMinForInc "<< FlavourBinMinForInc <<"  FlavourBinMaxForInc "<<FlavourBinMaxForInc <<endl;
  

  
  // ====== muon pT cuts loop
  for(int i =0;i<NMuonPtCut;i++){
    
    Int_t MuonPtBinMin = hist_GenMaster_GenJetPt_GenMuPt_Flavour->GetYaxis()->FindBin(MuonPtCut[i]);
    Int_t MuonPtBinMax = hist_GenMaster_GenJetPt_GenMuPt_Flavour->GetYaxis()->GetNbins(); // no overflow
    
    //================== calculating Tagging eff (Jets with muon for flv x / all jets of flv x) and purity (Gen Fraction with muons)for the GenJets with muon =============================================//


    //Gen Jets with muon for different muon pT cuts
    TH1 *hist_GenJetPt_WithMuon_Inclusive = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionX(Form("hist_GenJetPt_WithMuon_Inclusive_%d",i), MuonPtBinMin,MuonPtBinMax,FlavourBinMinForInc,FlavourBinMaxForInc);
    
    TH1 *hist_GenJetPt_WithMuon_U_Jets = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionX(Form("hist_GenJetPt_WithMuon_U_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForU,FlavourBinMaxForU);
    TH1 *hist_GenJetPt_WithMuon_D_Jets = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionX(Form("hist_GenJetPt_WithMuon_D_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForD,FlavourBinMaxForD);
    TH1 *hist_GenJetPt_WithMuon_S_Jets = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionX(Form("hist_GenJetPt_WithMuon_S_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForS,FlavourBinMaxForS);
    TH1 *hist_GenJetPt_WithMuon_C_Jets = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionX(Form("hist_GenJetPt_WithMuon_C_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForC,FlavourBinMaxForC);
    TH1 *hist_GenJetPt_WithMuon_B_Jets = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionX(Form("hist_GenJetPt_WithMuon_B_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForB,FlavourBinMaxForB);
    TH1 *hist_GenJetPt_WithMuon_G_Jets = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionX(Form("hist_GenJetPt_WithMuon_G_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForG,FlavourBinMaxForG);

    TH1 *hist_GenJetPt_WithMuon_Un_Jets = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionX(Form("hist_GenJetPt_WithMuon_Un_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForUn,FlavourBinMaxForUn);
    TH1 *hist_GenJetPt_WithMuon_Ze_Jets = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionX(Form("hist_GenJetPt_WithMuon_Ze_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForZe,FlavourBinMaxForZe);
    TH1 *hist_GenJetPt_WithMuon_NR_Jets = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionX(Form("hist_GenJetPt_WithMuon_NR_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForNR,FlavourBinMaxForNR);
    
    
    //Asymmatric binning for gen Jets with muon for different muon pT cuts
    GenJetMethod->rebinAsymmetric(hist_GenJetPt_WithMuon_Inclusive, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
    GenJetMethod->rebinAsymmetric(hist_GenJetPt_WithMuon_U_Jets, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
    GenJetMethod->rebinAsymmetric(hist_GenJetPt_WithMuon_D_Jets, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
    GenJetMethod->rebinAsymmetric(hist_GenJetPt_WithMuon_S_Jets, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
    GenJetMethod->rebinAsymmetric(hist_GenJetPt_WithMuon_C_Jets, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
    GenJetMethod->rebinAsymmetric(hist_GenJetPt_WithMuon_B_Jets, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
    GenJetMethod->rebinAsymmetric(hist_GenJetPt_WithMuon_G_Jets, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
    GenJetMethod->rebinAsymmetric(hist_GenJetPt_WithMuon_Un_Jets, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
    GenJetMethod->rebinAsymmetric(hist_GenJetPt_WithMuon_Ze_Jets, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);
    GenJetMethod->rebinAsymmetric(hist_GenJetPt_WithMuon_NR_Jets, GenJetMethod->NBins_GenJetPt_VarSize-1, GenJetMethod->GenJetPtBinEdges);


    //Tagging eff (Jets with muon for flv x / all jets of flv x)
    hist_GenTaggingEff_ForU[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_U_Jets,hist_GenJetPt_U,1);
    
    hist_GenTaggingEff_ForD[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_D_Jets,hist_GenJetPt_D,1);
    hist_GenTaggingEff_ForS[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_S_Jets,hist_GenJetPt_S,1);
    hist_GenTaggingEff_ForC[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_C_Jets,hist_GenJetPt_C,1);
    hist_GenTaggingEff_ForB[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_B_Jets,hist_GenJetPt_B,1);
    hist_GenTaggingEff_ForG[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_G_Jets,hist_GenJetPt_G,1);
    hist_GenTaggingEff_ForUn[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_Un_Jets,hist_GenJetPt_Un,1);
    hist_GenTaggingEff_ForZe[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_Ze_Jets,hist_GenJetPt_Ze,1);
    hist_GenTaggingEff_ForNR[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_NR_Jets,hist_GenJetPt_NR,1);

    //========== changing histograms's style     
    GenJetMethod->FlavouredHistogram(hist_GenTaggingEff_ForU[i], GenJetMethod->LineColorArray[1], GenJetMethod->MarkerColorArray[1], GenJetMethod->MarkerStyleArray[1],GenJetMethod->MarkerSizeArray[1]);
    GenJetMethod->FlavouredHistogram(hist_GenTaggingEff_ForD[i], GenJetMethod->LineColorArray[2], GenJetMethod->MarkerColorArray[2], GenJetMethod->MarkerStyleArray[2],GenJetMethod->MarkerSizeArray[2]);
    GenJetMethod->FlavouredHistogram(hist_GenTaggingEff_ForS[i], GenJetMethod->LineColorArray[3], GenJetMethod->MarkerColorArray[3], GenJetMethod->MarkerStyleArray[3],GenJetMethod->MarkerSizeArray[3]);
    GenJetMethod->FlavouredHistogram(hist_GenTaggingEff_ForC[i], GenJetMethod->LineColorArray[4], GenJetMethod->MarkerColorArray[4], GenJetMethod->MarkerStyleArray[4],GenJetMethod->MarkerSizeArray[4]);
    GenJetMethod->FlavouredHistogram(hist_GenTaggingEff_ForB[i], GenJetMethod->LineColorArray[5], GenJetMethod->MarkerColorArray[5], GenJetMethod->MarkerStyleArray[5],GenJetMethod->MarkerSizeArray[5]);
    GenJetMethod->FlavouredHistogram(hist_GenTaggingEff_ForG[i], GenJetMethod->LineColorArray[6], GenJetMethod->MarkerColorArray[6], GenJetMethod->MarkerStyleArray[6],GenJetMethod->MarkerSizeArray[6]);
    GenJetMethod->FlavouredHistogram(hist_GenTaggingEff_ForUn[i], GenJetMethod->LineColorArray[1], GenJetMethod->MarkerColorArray[1], GenJetMethod->MarkerStyleArray[1],GenJetMethod->MarkerSizeArray[1]);
    GenJetMethod->FlavouredHistogram(hist_GenTaggingEff_ForZe[i], GenJetMethod->LineColorArray[2], GenJetMethod->MarkerColorArray[2], GenJetMethod->MarkerStyleArray[2],GenJetMethod->MarkerSizeArray[2]);
    GenJetMethod->FlavouredHistogram(hist_GenTaggingEff_ForNR[i], GenJetMethod->LineColorArray[3], GenJetMethod->MarkerColorArray[3], GenJetMethod->MarkerStyleArray[3],GenJetMethod->MarkerSizeArray[3]);

    
         
    //Purity (Gen Fraction with muons)
    hist_GenPurity_ForU[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_U_Jets,hist_GenJetPt_WithMuon_Inclusive,1);
    hist_GenPurity_ForD[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_D_Jets,hist_GenJetPt_WithMuon_Inclusive,1);
    hist_GenPurity_ForS[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_S_Jets,hist_GenJetPt_WithMuon_Inclusive,1);
    hist_GenPurity_ForC[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_C_Jets,hist_GenJetPt_WithMuon_Inclusive,1);
    hist_GenPurity_ForB[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_B_Jets,hist_GenJetPt_WithMuon_Inclusive,1);
    hist_GenPurity_ForG[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_G_Jets,hist_GenJetPt_WithMuon_Inclusive,1);
    hist_GenPurity_ForUn[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_Un_Jets,hist_GenJetPt_WithMuon_Inclusive,1);
    hist_GenPurity_ForZe[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_Ze_Jets,hist_GenJetPt_WithMuon_Inclusive,1);
    hist_GenPurity_ForNR[i] = GenJetMethod->RatioHistogram(hist_GenJetPt_WithMuon_NR_Jets,hist_GenJetPt_WithMuon_Inclusive,1);

    //========== changing histograms's style     
    GenJetMethod->FlavouredHistogram(hist_GenPurity_ForU[i], GenJetMethod->LineColorArray[1], GenJetMethod->MarkerColorArray[1], GenJetMethod->MarkerStyleArray[1],GenJetMethod->MarkerSizeArray[1]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_ForD[i], GenJetMethod->LineColorArray[2], GenJetMethod->MarkerColorArray[2], GenJetMethod->MarkerStyleArray[2],GenJetMethod->MarkerSizeArray[2]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_ForS[i], GenJetMethod->LineColorArray[3], GenJetMethod->MarkerColorArray[3], GenJetMethod->MarkerStyleArray[3],GenJetMethod->MarkerSizeArray[3]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_ForC[i], GenJetMethod->LineColorArray[4], GenJetMethod->MarkerColorArray[4], GenJetMethod->MarkerStyleArray[4],GenJetMethod->MarkerSizeArray[4]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_ForB[i], GenJetMethod->LineColorArray[5], GenJetMethod->MarkerColorArray[5], GenJetMethod->MarkerStyleArray[5],GenJetMethod->MarkerSizeArray[5]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_ForG[i], GenJetMethod->LineColorArray[6], GenJetMethod->MarkerColorArray[6], GenJetMethod->MarkerStyleArray[6],GenJetMethod->MarkerSizeArray[6]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_ForUn[i], GenJetMethod->LineColorArray[1], GenJetMethod->MarkerColorArray[1], GenJetMethod->MarkerStyleArray[1],GenJetMethod->MarkerSizeArray[1]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_ForZe[i], GenJetMethod->LineColorArray[2], GenJetMethod->MarkerColorArray[2], GenJetMethod->MarkerStyleArray[2],GenJetMethod->MarkerSizeArray[2]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_ForNR[i], GenJetMethod->LineColorArray[3], GenJetMethod->MarkerColorArray[3], GenJetMethod->MarkerStyleArray[3],GenJetMethod->MarkerSizeArray[3]);
    
    //============================================================================================//
    //==================== Gen Jet Fraction Double Ratios ========================================//
    //=========== Gen Jet Fraction (with muon) / Gen Jet Fraction (no muon requirement) ==========//
    //============================================================================================//
    
    hist_GenPurity_DR_ForU[i] = GenJetMethod->RatioHistogram(hist_GenPurity_ForU[i],hist_Ratio_GenJetPt_U_GenJetPt_Inclusive,1);
    hist_GenPurity_DR_ForD[i] = GenJetMethod->RatioHistogram(hist_GenPurity_ForD[i],hist_Ratio_GenJetPt_D_GenJetPt_Inclusive,1);
    hist_GenPurity_DR_ForS[i] = GenJetMethod->RatioHistogram(hist_GenPurity_ForS[i],hist_Ratio_GenJetPt_S_GenJetPt_Inclusive,1);
    hist_GenPurity_DR_ForC[i] = GenJetMethod->RatioHistogram(hist_GenPurity_ForC[i],hist_Ratio_GenJetPt_C_GenJetPt_Inclusive,1);
    hist_GenPurity_DR_ForB[i] = GenJetMethod->RatioHistogram(hist_GenPurity_ForB[i],hist_Ratio_GenJetPt_B_GenJetPt_Inclusive,1);
    hist_GenPurity_DR_ForG[i] = GenJetMethod->RatioHistogram(hist_GenPurity_ForG[i],hist_Ratio_GenJetPt_G_GenJetPt_Inclusive,1);
    hist_GenPurity_DR_ForUn[i] = GenJetMethod->RatioHistogram(hist_GenPurity_ForUn[i],hist_Ratio_GenJetPt_Un_GenJetPt_Inclusive,1);
    hist_GenPurity_DR_ForZe[i] = GenJetMethod->RatioHistogram(hist_GenPurity_ForZe[i],hist_Ratio_GenJetPt_Ze_GenJetPt_Inclusive,1);
    hist_GenPurity_DR_ForNR[i] = GenJetMethod->RatioHistogram(hist_GenPurity_ForNR[i],hist_Ratio_GenJetPt_NR_GenJetPt_Inclusive,1);
    
    // make double ratio plots beautiful
    GenJetMethod->FlavouredHistogram(hist_GenPurity_DR_ForU[i], GenJetMethod->LineColorArray[1], GenJetMethod->MarkerColorArray[1], GenJetMethod->MarkerStyleArray[1],GenJetMethod->MarkerSizeArray[1]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_DR_ForD[i], GenJetMethod->LineColorArray[2], GenJetMethod->MarkerColorArray[2], GenJetMethod->MarkerStyleArray[2],GenJetMethod->MarkerSizeArray[2]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_DR_ForS[i], GenJetMethod->LineColorArray[3], GenJetMethod->MarkerColorArray[3], GenJetMethod->MarkerStyleArray[3],GenJetMethod->MarkerSizeArray[3]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_DR_ForC[i], GenJetMethod->LineColorArray[4], GenJetMethod->MarkerColorArray[4], GenJetMethod->MarkerStyleArray[4],GenJetMethod->MarkerSizeArray[4]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_DR_ForB[i], GenJetMethod->LineColorArray[5], GenJetMethod->MarkerColorArray[5], GenJetMethod->MarkerStyleArray[5],GenJetMethod->MarkerSizeArray[5]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_DR_ForG[i], GenJetMethod->LineColorArray[6], GenJetMethod->MarkerColorArray[6], GenJetMethod->MarkerStyleArray[6],GenJetMethod->MarkerSizeArray[6]);

    GenJetMethod->FlavouredHistogram(hist_GenPurity_DR_ForUn[i], GenJetMethod->LineColorArray[1], GenJetMethod->MarkerColorArray[1], GenJetMethod->MarkerStyleArray[1],GenJetMethod->MarkerSizeArray[1]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_DR_ForZe[i], GenJetMethod->LineColorArray[2], GenJetMethod->MarkerColorArray[2], GenJetMethod->MarkerStyleArray[2],GenJetMethod->MarkerSizeArray[2]);
    GenJetMethod->FlavouredHistogram(hist_GenPurity_DR_ForNR[i], GenJetMethod->LineColorArray[3], GenJetMethod->MarkerColorArray[3], GenJetMethod->MarkerStyleArray[3],GenJetMethod->MarkerSizeArray[3]);



    //Integrated fractions with muon pT cuts
    // get the flavour histogram with each flavour in one bin
    TH1 *hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionZ(Form("hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ_%d",i),JetPtBinMin,JetPtBinMax,MuonPtBinMin,MuonPtBinMax);

    // get integral of this for the denominator
    Double_t  GenMaster_GenJetPt_GenMuPt_Flavour_IntegralZ = hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->Integral(0,hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetNbinsX()+1);

    //======= these bins will be equal to the number of flavours
    Int_t NBinsHisto = hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetNbinsX();

    cout<<"NBinsHisto "<<NBinsHisto<<endl;
    
    
    //for(int j = 0; j <=NBinsHisto+1; j++)
    // there is nothing in zero, u is in 1
    for(int j = 1; j <=NBinsHisto; j++)
       {

	 //====== this get bin content should be checked some time
	 Double_t JetFraction = hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetBinContent(j)/GenMaster_GenJetPt_GenMuPt_Flavour_IntegralZ;

	 // put the integrated fractions in a 2D array
	 // i --> muon cut
	 // j --> flavour
	 GenMuPtCut_Flavour_Fraction[i][j] = JetFraction; 
	 
	 cout<<" flavour bin centre "<<hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetBinCenter(j)<<
	   " bin content "<<hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetBinContent(j)<<
	   " fraction    "<<hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->GetBinContent(j)/GenMaster_GenJetPt_GenMuPt_Flavour_IntegralZ<<endl;
	 
	 
       }// flavour loop ends
    cout<<endl;

    // this will draw the flavour histo for differnt muon pT cuts
    new TCanvas;
    gPad->SetLogy(1);
    hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjZ->Draw();


    //making 1D array for flavours
    // content of this array will change with differnt muon pt cuts
    // we will get a array of graphs, according to muon pt cuts
    Double_t t_GenMuonGenJetFrac[NFlvLocal]={GenMuPtCut_Flavour_Fraction[i][1], GenMuPtCut_Flavour_Fraction[i][2], GenMuPtCut_Flavour_Fraction[i][3],
					    GenMuPtCut_Flavour_Fraction[i][4],GenMuPtCut_Flavour_Fraction[i][5],GenMuPtCut_Flavour_Fraction[i][6]};

    //array of graphs, x axis is N flavour and Y changes with muon pt cuts
    graph_GenMuonPtCut_GenJetFrac[i] = new TGraph ( NFlvLocal, GenMuonGenJetType, t_GenMuonGenJetFrac);
    graph_GenMuonPtCut_GenJetFrac[i]->SetFillColorAlpha(kRed,0.6);
    
  }//nMuon pT Cut
  cout<<endl<<endl;

  //=========================================================================================================================//
  //=========================================================================================================================//
  //==================================== Gen Muon Probabilities coming with different flavours =============================//
  //======================================== muon pt distribution inside a jet with a particular flv divided by ===========//
  //                                          all muons pt distribution (no requirement for jets) ============//
  //=======================================================================================================================//

  //get the gen muon distribution inside jets
  TH1 *hist_GenMuPt_WithGenJets_Inclusive = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionY("hist_GenMuPt_WithGenJets_Inclusive",JetPtBinMin,JetPtBinMax,FlavourBinMinForInc,FlavourBinMaxForInc);
  TH1 *hist_GenMuPt_WithGenJets_U = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionY("hist_GenMuPt_WithGenJets_U",JetPtBinMin,JetPtBinMax,FlavourBinMinForU,FlavourBinMaxForU);
  TH1 *hist_GenMuPt_WithGenJets_D = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionY("hist_GenMuPt_WithGenJets_D",JetPtBinMin,JetPtBinMax,FlavourBinMinForD,FlavourBinMaxForD);
  TH1 *hist_GenMuPt_WithGenJets_S = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionY("hist_GenMuPt_WithGenJets_S",JetPtBinMin,JetPtBinMax,FlavourBinMinForS,FlavourBinMaxForS);
  TH1 *hist_GenMuPt_WithGenJets_C = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionY("hist_GenMuPt_WithGenJets_C",JetPtBinMin,JetPtBinMax,FlavourBinMinForC,FlavourBinMaxForC);
  TH1 *hist_GenMuPt_WithGenJets_B = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionY("hist_GenMuPt_WithGenJets_B",JetPtBinMin,JetPtBinMax,FlavourBinMinForB,FlavourBinMaxForB);
  TH1 *hist_GenMuPt_WithGenJets_G = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionY("hist_GenMuPt_WithGenJets_G",JetPtBinMin,JetPtBinMax,FlavourBinMinForG,FlavourBinMaxForG);

  TH1 *hist_GenMuPt_WithGenJets_Un = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionY("hist_GenMuPt_WithGenJets_Un",JetPtBinMin,JetPtBinMax,FlavourBinMinForUn,FlavourBinMaxForUn);
  TH1 *hist_GenMuPt_WithGenJets_Ze = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionY("hist_GenMuPt_WithGenJets_Ze",JetPtBinMin,JetPtBinMax,FlavourBinMinForZe,FlavourBinMaxForZe);
  TH1 *hist_GenMuPt_WithGenJets_NR = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionY("hist_GenMuPt_WithGenJets_NR",JetPtBinMin,JetPtBinMax,FlavourBinMinForNR,FlavourBinMaxForNR);
  
  

  //========== Asymmatic Re Binning gen muon pT inside gen jets ================================//
  
  GenJetMethod->rebinAsymmetric(hist_GenMuPt_WithGenJets_Inclusive, GenJetMethod->NBins_GenMuonPt_VarSize-1, GenJetMethod->GenMuonPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenMuPt_WithGenJets_U, GenJetMethod->NBins_GenMuonPt_VarSize-1, GenJetMethod->GenMuonPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenMuPt_WithGenJets_D, GenJetMethod->NBins_GenMuonPt_VarSize-1, GenJetMethod->GenMuonPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenMuPt_WithGenJets_S, GenJetMethod->NBins_GenMuonPt_VarSize-1, GenJetMethod->GenMuonPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenMuPt_WithGenJets_C, GenJetMethod->NBins_GenMuonPt_VarSize-1, GenJetMethod->GenMuonPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenMuPt_WithGenJets_B, GenJetMethod->NBins_GenMuonPt_VarSize-1, GenJetMethod->GenMuonPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenMuPt_WithGenJets_G, GenJetMethod->NBins_GenMuonPt_VarSize-1, GenJetMethod->GenMuonPtBinEdges);

  GenJetMethod->rebinAsymmetric(hist_GenMuPt_WithGenJets_Un, GenJetMethod->NBins_GenMuonPt_VarSize-1, GenJetMethod->GenMuonPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenMuPt_WithGenJets_Ze, GenJetMethod->NBins_GenMuonPt_VarSize-1, GenJetMethod->GenMuonPtBinEdges);
  GenJetMethod->rebinAsymmetric(hist_GenMuPt_WithGenJets_NR, GenJetMethod->NBins_GenMuonPt_VarSize-1, GenJetMethod->GenMuonPtBinEdges);
  
  // set titles
  hist_GenMuPt_WithGenJets_Inclusive->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_GenMuPt_WithGenJets_U->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_GenMuPt_WithGenJets_D->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_GenMuPt_WithGenJets_S->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_GenMuPt_WithGenJets_C->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_GenMuPt_WithGenJets_B->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_GenMuPt_WithGenJets_G->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");

  hist_GenMuPt_WithGenJets_Un->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_GenMuPt_WithGenJets_Ze->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_GenMuPt_WithGenJets_NR->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");

  
  // divide the gen muons inside jets with all gen muons
  TH1D *hist_GenMuonRatio_Inclusive = GenJetMethod->RatioHistogram(hist_GenMuPt_WithGenJets_Inclusive,hist_GenMuonPt,1);
  TH1D *hist_GenMuonRatio_U = GenJetMethod->RatioHistogram(hist_GenMuPt_WithGenJets_U,hist_GenMuonPt,1);
  TH1D *hist_GenMuonRatio_D = GenJetMethod->RatioHistogram(hist_GenMuPt_WithGenJets_D,hist_GenMuonPt,1);
  TH1D *hist_GenMuonRatio_S = GenJetMethod->RatioHistogram(hist_GenMuPt_WithGenJets_S,hist_GenMuonPt,1);
  TH1D *hist_GenMuonRatio_C = GenJetMethod->RatioHistogram(hist_GenMuPt_WithGenJets_C,hist_GenMuonPt,1);
  TH1D *hist_GenMuonRatio_B = GenJetMethod->RatioHistogram(hist_GenMuPt_WithGenJets_B,hist_GenMuonPt,1);
  TH1D *hist_GenMuonRatio_G = GenJetMethod->RatioHistogram(hist_GenMuPt_WithGenJets_G,hist_GenMuonPt,1);
  TH1D *hist_GenMuonRatio_Un = GenJetMethod->RatioHistogram(hist_GenMuPt_WithGenJets_Un,hist_GenMuonPt,1);
  TH1D *hist_GenMuonRatio_Ze = GenJetMethod->RatioHistogram(hist_GenMuPt_WithGenJets_Ze,hist_GenMuonPt,1);
  TH1D *hist_GenMuonRatio_NR = GenJetMethod->RatioHistogram(hist_GenMuPt_WithGenJets_NR,hist_GenMuonPt,1);
  

  //======== change the histograms style
  GenJetMethod->FlavouredHistogram(hist_GenMuonRatio_Inclusive, GenJetMethod->LineColorArray[6], GenJetMethod->MarkerColorArray[6], 20,GenJetMethod->MarkerSizeArray[1]);
  
  GenJetMethod->FlavouredHistogram(hist_GenMuonRatio_U, GenJetMethod->LineColorArray[1], GenJetMethod->MarkerColorArray[1], GenJetMethod->MarkerStyleArray[1],GenJetMethod->MarkerSizeArray[1]);
  GenJetMethod->FlavouredHistogram(hist_GenMuonRatio_D, GenJetMethod->LineColorArray[2], GenJetMethod->MarkerColorArray[2], GenJetMethod->MarkerStyleArray[2],GenJetMethod->MarkerSizeArray[2]);
  GenJetMethod->FlavouredHistogram(hist_GenMuonRatio_S, GenJetMethod->LineColorArray[3], GenJetMethod->MarkerColorArray[3], GenJetMethod->MarkerStyleArray[3],GenJetMethod->MarkerSizeArray[3]);
  GenJetMethod->FlavouredHistogram(hist_GenMuonRatio_C, GenJetMethod->LineColorArray[4], GenJetMethod->MarkerColorArray[4], GenJetMethod->MarkerStyleArray[4],GenJetMethod->MarkerSizeArray[4]);
  GenJetMethod->FlavouredHistogram(hist_GenMuonRatio_B, GenJetMethod->LineColorArray[5], GenJetMethod->MarkerColorArray[5], GenJetMethod->MarkerStyleArray[5],GenJetMethod->MarkerSizeArray[5]);
  GenJetMethod->FlavouredHistogram(hist_GenMuonRatio_G, GenJetMethod->LineColorArray[6], GenJetMethod->MarkerColorArray[6], GenJetMethod->MarkerStyleArray[6],GenJetMethod->MarkerSizeArray[6]);
  GenJetMethod->FlavouredHistogram(hist_GenMuonRatio_Un, GenJetMethod->LineColorArray[1], GenJetMethod->MarkerColorArray[1], GenJetMethod->MarkerStyleArray[1],GenJetMethod->MarkerSizeArray[1]);
  GenJetMethod->FlavouredHistogram(hist_GenMuonRatio_Ze, GenJetMethod->LineColorArray[2], GenJetMethod->MarkerColorArray[2], GenJetMethod->MarkerStyleArray[2],GenJetMethod->MarkerSizeArray[2]);
  GenJetMethod->FlavouredHistogram(hist_GenMuonRatio_NR, GenJetMethod->LineColorArray[3], GenJetMethod->MarkerColorArray[3], GenJetMethod->MarkerStyleArray[3],GenJetMethod->MarkerSizeArray[3]);
    
  
  // set title for the gen muon ratio histograms 
  hist_GenMuonRatio_Inclusive->GetYaxis()->SetTitle("gen #mu in gen Jets (inclusive)/ all gen #mu");
  hist_GenMuonRatio_U->GetYaxis()->SetTitle("gen #mu in gen Jets (u)/ all gen #mu");
  hist_GenMuonRatio_D->GetYaxis()->SetTitle("gen #mu in gen Jets (d)/ all gen #mu");
  hist_GenMuonRatio_S->GetYaxis()->SetTitle("gen #mu in gen Jets (s)/ all gen #mu");
  hist_GenMuonRatio_C->GetYaxis()->SetTitle("gen #mu in gen Jets (c)/ all gen #mu");
  hist_GenMuonRatio_B->GetYaxis()->SetTitle("gen #mu in gen Jets (b)/ all gen #mu");
  hist_GenMuonRatio_G->GetYaxis()->SetTitle("gen #mu in gen Jets (g)/ all gen #mu");

  hist_GenMuonRatio_Un->GetYaxis()->SetTitle("gen #mu in gen Jets (-999)/ all gen #mu");
  hist_GenMuonRatio_Ze->GetYaxis()->SetTitle("gen #mu in gen Jets (0)/ all gen #mu");
  hist_GenMuonRatio_NR->GetYaxis()->SetTitle("gen #mu in gen Jets (NR)/ all gen #mu");
  
  

  // 
  // numrator = integral of muon pT distribution, inside a jet, above the muon pT cut
  // denominator = integral of muon pT distribution, All muons , above the muon pT cut
  // to estimate the events with differnt flavours, using the muon triggerd events
  for(int i =0;i<NMuonPtCut;i++){
    
    Double_t Num_GenMuonFractionInclusive = hist_GenMuPt_WithGenJets_Inclusive->Integral(hist_GenMuPt_WithGenJets_Inclusive->GetXaxis()->FindBin(MuonPtCut[i]),hist_GenMuPt_WithGenJets_Inclusive->GetXaxis()->GetNbins());
    Double_t Num_GenMuonFraction_U = hist_GenMuPt_WithGenJets_U->Integral(hist_GenMuPt_WithGenJets_U->GetXaxis()->FindBin(MuonPtCut[i]),hist_GenMuPt_WithGenJets_U->GetXaxis()->GetNbins());
    Double_t Num_GenMuonFraction_D = hist_GenMuPt_WithGenJets_D->Integral(hist_GenMuPt_WithGenJets_D->GetXaxis()->FindBin(MuonPtCut[i]),hist_GenMuPt_WithGenJets_D->GetXaxis()->GetNbins());
    Double_t Num_GenMuonFraction_S = hist_GenMuPt_WithGenJets_S->Integral(hist_GenMuPt_WithGenJets_S->GetXaxis()->FindBin(MuonPtCut[i]),hist_GenMuPt_WithGenJets_S->GetXaxis()->GetNbins());
    Double_t Num_GenMuonFraction_C = hist_GenMuPt_WithGenJets_C->Integral(hist_GenMuPt_WithGenJets_C->GetXaxis()->FindBin(MuonPtCut[i]),hist_GenMuPt_WithGenJets_C->GetXaxis()->GetNbins());
    Double_t Num_GenMuonFraction_B = hist_GenMuPt_WithGenJets_B->Integral(hist_GenMuPt_WithGenJets_B->GetXaxis()->FindBin(MuonPtCut[i]),hist_GenMuPt_WithGenJets_B->GetXaxis()->GetNbins());
    Double_t Num_GenMuonFraction_G = hist_GenMuPt_WithGenJets_G->Integral(hist_GenMuPt_WithGenJets_G->GetXaxis()->FindBin(MuonPtCut[i]),hist_GenMuPt_WithGenJets_G->GetXaxis()->GetNbins());
    Double_t Num_GenMuonFraction_Un = hist_GenMuPt_WithGenJets_Un->Integral(hist_GenMuPt_WithGenJets_Un->GetXaxis()->FindBin(MuonPtCut[i]),hist_GenMuPt_WithGenJets_Un->GetXaxis()->GetNbins());
    Double_t Num_GenMuonFraction_Ze = hist_GenMuPt_WithGenJets_Ze->Integral(hist_GenMuPt_WithGenJets_Ze->GetXaxis()->FindBin(MuonPtCut[i]),hist_GenMuPt_WithGenJets_Ze->GetXaxis()->GetNbins());
    Double_t Num_GenMuonFraction_NR = hist_GenMuPt_WithGenJets_NR->Integral(hist_GenMuPt_WithGenJets_NR->GetXaxis()->FindBin(MuonPtCut[i]),hist_GenMuPt_WithGenJets_NR->GetXaxis()->GetNbins());



    Double_t Deno_GenMuonFraction =     hist_GenMuonPt->Integral(hist_GenMuonPt->GetXaxis()->FindBin(MuonPtCut[i]),hist_GenMuonPt->GetXaxis()->GetNbins());



    Double_t GenMuonFractionInclusive =  Num_GenMuonFractionInclusive/Deno_GenMuonFraction;
       
    Double_t GenMuonFraction_U =  Num_GenMuonFraction_U/Deno_GenMuonFraction;
    Double_t GenMuonFraction_D =  Num_GenMuonFraction_D/Deno_GenMuonFraction;
    Double_t GenMuonFraction_S =  Num_GenMuonFraction_S/Deno_GenMuonFraction;
    Double_t GenMuonFraction_C =  Num_GenMuonFraction_C/Deno_GenMuonFraction;
    Double_t GenMuonFraction_B =  Num_GenMuonFraction_B/Deno_GenMuonFraction;
    Double_t GenMuonFraction_G =  Num_GenMuonFraction_G/Deno_GenMuonFraction;
    
    Double_t GenMuonFraction_Un =  Num_GenMuonFraction_Un/Deno_GenMuonFraction;
    Double_t GenMuonFraction_Ze =  Num_GenMuonFraction_Ze/Deno_GenMuonFraction;
    Double_t GenMuonFraction_NR =  Num_GenMuonFraction_NR/Deno_GenMuonFraction;  
    
    
       
    GenMuPtCut_Flavour_GenMuonFraction[i][0]=GenMuonFractionInclusive;
    GenMuPtCut_Flavour_GenMuonFraction[i][1]=GenMuonFraction_U;
    GenMuPtCut_Flavour_GenMuonFraction[i][2]=GenMuonFraction_D;
    GenMuPtCut_Flavour_GenMuonFraction[i][3]=GenMuonFraction_S;
    GenMuPtCut_Flavour_GenMuonFraction[i][4]=GenMuonFraction_C;
    GenMuPtCut_Flavour_GenMuonFraction[i][5]=GenMuonFraction_B;
    GenMuPtCut_Flavour_GenMuonFraction[i][6]=GenMuonFraction_G;
  }
  
  

  
  
  
  //================== Muon Pt Bin Centre test ===================//
  //TH1 *hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY = hist_GenMaster_GenJetPt_GenMuPt_Flavour->ProjectionY("y");
  //cout<<endl;
  //for(int j = 0; j <=hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY->GetNbinsX()+1; j++)
  // {
  
  // cout<<" mu pt bin lower edge "<<hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY->GetBinLowEdge(j)<<"      "<<
  // hist_GenMaster_GenJetPt_GenMuPt_Flavour_ProjY->GetBinCenter(j)<<"    "<<endl;
  
	 
  // }
  //cout<<endl;
     

  Double_t CanvasX = 800.0;
  Double_t CanvasY = 800.0;

  //=========== canvas for the integrated fractions
  TCanvas *CanvasGenFractionMuonCut = new TCanvas("CanvasGenFractionMuonCut","CanvasGenFractionMuonCut",CanvasX,CanvasY);
  CanvasGenFractionMuonCut->Divide(2,2);
     
  //========= canvas for tagging with different muon pt cuts   (Jets with muon for flv x / all jets of flv x) 
  TCanvas *CanvasGenBTaggingMuonCut = new TCanvas("CanvasGenBTaggingMuonCut","CanvasGenBTaggingMuonCut",CanvasX,CanvasY);
  CanvasGenBTaggingMuonCut->Divide(2,2);
     
  //======= canvas for purity with differnt muon pt cut (Jets with muon for flv x / all jets with muons)
  TCanvas *CanvasGenBPurityMuonCut = new TCanvas("CanvasGenBPurityMuonCut","CanvasGenBPurityMuonCut",CanvasX,CanvasY);
  CanvasGenBPurityMuonCut->Divide(2,2);

  //====== canvas for unknown flv fractions
  TCanvas *CanvasGenBPurityUnMuonCut = new TCanvas("CanvasGenBPurityUnMuonCut","CanvasGenBPurityUnMuonCut",CanvasX,CanvasY);
  CanvasGenBPurityUnMuonCut->Divide(2,2);
  
  //============ canvas for double ratios of fractions
  TCanvas *CanvasGenBPurityDRMuonCut = new TCanvas("CanvasGenBPurityDRMuonCut","CanvasGenBPurityDRMuonCut",CanvasX,CanvasY);
  CanvasGenBPurityDRMuonCut->Divide(2,2);

   
  //================ Drawing Gen Graphs for different muon pT cuts ===============//
  
  for(int i =0 ;i<NMuonPtCut; i++)
    {
      
      char Ch_MuPtCutPlot[100];
      sprintf(Ch_MuPtCutPlot,"%1.2f",MuonPtCut[i]);
      TString MuPtCutPlot = TString(Ch_MuPtCutPlot);

      //integarted gen fractions
      CanvasGenFractionMuonCut->cd(i+1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      
      h->Draw();
      graph_GenJetFracGraph->Draw("Bsame");
      graph_GenMuonPtCut_GenJetFrac[i]->Draw("Bsame");  
      lgd_GenMuonGenJetFrac->Draw("same");
      
      sprintf(LatexChar,"#mu p_{T} > %.1f GeV/c",MuonPtCut[i]);
      tb->DrawLatex(0.28,0.68,LatexChar);
      
      
      CanvasGenFractionMuonCut->SaveAs("Plots/GenJets/GenJetFrac_GenMuPtCut_All.png");
      CanvasGenFractionMuonCut->SaveAs("Plots/GenJets/GenJetFrac_GenMuPtCut_All.pdf");

      // canvas tagging (Jets with muon for flv x / all jets of flv x)
      CanvasGenBTaggingMuonCut->cd(i+1);
      gPad->SetLogy(1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      
      hist_GenTaggingEff_ForB[i]->GetYaxis()->SetRangeUser(0.001,1.2);
      hist_GenTaggingEff_ForB[i]->GetYaxis()->SetTitle("gen Tagging Efficiency");
      
      hist_GenTaggingEff_ForB[i]->Draw();
      hist_GenTaggingEff_ForU[i]->Draw("same");
      hist_GenTaggingEff_ForD[i]->Draw("same");
      hist_GenTaggingEff_ForS[i]->Draw("same");
      hist_GenTaggingEff_ForC[i]->Draw("same");
      hist_GenTaggingEff_ForG[i]->Draw("same");
      
      
      sprintf(LatexChar,"#mu p_{T} > %.1f GeV/c",MuonPtCut[i]);
      tb->DrawLatex(0.64,0.80,LatexChar);
      GenJetMethod->DrawFlavourLegend(0.20,0.87,0.32,0.995, Flv_Legend_Index_Local++);
      CanvasGenBTaggingMuonCut->SaveAs("Plots/GenJets/GenTaggingEff_ForB_GenMuPtCut_All.png");
      CanvasGenBTaggingMuonCut->SaveAs("Plots/GenJets/GenTaggingEff_ForB_GenMuPtCut_All.pdf");
      
      //canvas purity (Jets with muon for flv x / all jets with muons)
      CanvasGenBPurityMuonCut->cd(i+1);
      gPad->SetLogy(1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      hist_GenPurity_ForB[i]->GetYaxis()->SetRangeUser(0.005,1.2);
      hist_GenPurity_ForB[i]->GetYaxis()->SetTitle("gen Jet Fractions");
      //hist_GenPurity_ForB[i]->GetXaxis()->SetNdivisions(310);
      hist_GenPurity_ForB[i]->GetXaxis()->SetLabelSize(0.06);
      hist_GenPurity_ForB[i]->GetXaxis()->SetTitle("gen Jet p_{T} (GeV/c)");
      hist_GenPurity_ForB[i]->GetXaxis()->SetTitleOffset(1.4);
      hist_GenPurity_ForB[i]->GetXaxis()->SetTitleSize(0.06);
      hist_GenPurity_ForB[i]->Draw();
      hist_GenPurity_ForU[i]->Draw("same");
      hist_GenPurity_ForD[i]->Draw("same");
      hist_GenPurity_ForS[i]->Draw("same");
      hist_GenPurity_ForC[i]->Draw("same");
      hist_GenPurity_ForG[i]->Draw("same");
      sprintf(LatexChar,"#mu p_{T} > %.1f GeV/c",MuonPtCut[i]);
      tb->DrawLatex(0.64,0.84,LatexChar);
      GenJetMethod->DrawFlavourLegend(0.20,0.87,0.32,0.995, Flv_Legend_Index_Local++);
      CanvasGenBPurityMuonCut->SaveAs("Plots/GenJets/GenPurity_ForB_GenMuPtCut_All.png");
      CanvasGenBPurityMuonCut->SaveAs("Plots/GenJets/GenPurity_ForB_GenMuPtCut_All.pdf");
      

      //canvas purity unknown fractions (Jets with muon for flv x / all jets with muons)
      CanvasGenBPurityUnMuonCut->cd(i+1);
      //gPad->SetLogy(1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      hist_GenPurity_ForUn[i]->GetYaxis()->SetRangeUser(0.0,0.2);
      hist_GenPurity_ForUn[i]->GetYaxis()->SetTitle("gen Fraction ");
      hist_GenPurity_ForUn[i]->GetXaxis()->SetTitle("gen Jet p_{T} (GeV/c)");
      hist_GenPurity_ForUn[i]->GetXaxis()->SetTitleOffset(1.4);
      hist_GenPurity_ForUn[i]->GetXaxis()->SetTitleSize(0.06);
      hist_GenPurity_ForUn[i]->Draw();
      hist_GenPurity_ForZe[i]->Draw("same");
      hist_GenPurity_ForNR[i]->Draw("same");
      sprintf(LatexChar,"#mu p_{T} > %.1f GeV/c",MuonPtCut[i]);
      tb->DrawLatex(0.64,0.84,LatexChar);
      GenJetMethod->DrawFlavourLegendUn(0.20,0.87,0.32,0.995, Flv_Legend_Index_Local++);
      CanvasGenBPurityUnMuonCut->SaveAs("Plots/GenJets/GenPurity_Un_GenMuPtCut_All.png");
      CanvasGenBPurityUnMuonCut->SaveAs("Plots/GenJets/GenPurity_Un_GenMuPtCut_All.pdf");
      
      

      //canvas double ratio (Jets fractions with muon / Jet fractions no muon requirement)
      CanvasGenBPurityDRMuonCut->cd(i+1);
      //gPad->SetLogy(1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      
      hist_GenPurity_DR_ForB[i]->GetYaxis()->SetRangeUser(0.01,50.0);
      hist_GenPurity_DR_ForB[i]->GetYaxis()->SetTitle("gen Jet Frac. Double Ratio");

      hist_GenPurity_DR_ForB[i]->Draw();
      
      hist_GenPurity_DR_ForU[i]->Draw("same");
      hist_GenPurity_DR_ForD[i]->Draw("same");
      hist_GenPurity_DR_ForS[i]->Draw("same");
      hist_GenPurity_DR_ForC[i]->Draw("same");
      hist_GenPurity_DR_ForG[i]->Draw("same");
      sprintf(LatexChar,"#mu p_{T} > %.1f GeV/c",MuonPtCut[i]);
      tb->DrawLatex(0.64,0.84,LatexChar);
      GenJetMethod->DrawFlavourLegend(0.20,0.87,0.32,0.995, Flv_Legend_Index_Local++);
      CanvasGenBPurityDRMuonCut->SaveAs("Plots/GenJets/GenPurity_DR_ForB_GenMuPtCut_All.png");
      CanvasGenBPurityDRMuonCut->SaveAs("Plots/GenJets/GenPurity_DR_ForB_GenMuPtCut_All.pdf");

    }//muon pT cut


  //return;

//


  //=========================================================================================================================//
  //==================================== plotting Gen Muon Probabilities coming with different flavours ====================//
  //======================================== muon pt distribution inside a jet with a particular flv divided by ===========//
  //                                          all muons pt distribution (no requirement for jets) ============//
  //=======================================================================================================================//

  
  //Canvas muon probability coming with jets 
  TCanvas *CanvasGenMuonProbFlavour = new TCanvas("CanvasGenMuonProbFlavour","CanvasGenMuonProbFlavour",1800,1800);;
  CanvasGenMuonProbFlavour->Divide(4,2);
  
  
  // inclusive  
  CanvasGenMuonProbFlavour->cd(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_GenMuonRatio_Inclusive->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_GenMuonRatio_Inclusive->Draw();
  
  // u
  CanvasGenMuonProbFlavour->cd(2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_GenMuonRatio_U->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_GenMuonRatio_U->Draw();

  
  // d
  CanvasGenMuonProbFlavour->cd(3);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_GenMuonRatio_D->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_GenMuonRatio_D->Draw();
  
  // s
  CanvasGenMuonProbFlavour->cd(4);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_GenMuonRatio_S->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_GenMuonRatio_S->Draw();
  
  // c
  CanvasGenMuonProbFlavour->cd(5);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_GenMuonRatio_C->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_GenMuonRatio_C->Draw();
  
  // b
  CanvasGenMuonProbFlavour->cd(6);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_GenMuonRatio_B->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_GenMuonRatio_B->Draw();
  
  // g
  CanvasGenMuonProbFlavour->cd(7);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_GenMuonRatio_G->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_GenMuonRatio_G->Draw();
  
  CanvasGenMuonProbFlavour->cd(8);
  GenJetMethod->DrawFlavourLegendVertical(0.12,0.36,0.88,0.92, Flv_Legend_Index_Local_V++);
  
  CanvasGenMuonProbFlavour->SaveAs("Plots/GenJets/GenMuonsInJet_AllGenMuons_Ratio_Flavour_All.png");
  CanvasGenMuonProbFlavour->SaveAs("Plots/GenJets/GenMuonsInJet_AllGenMuons_Ratio_Flavour_All.pdf");
  

  
  cout<<endl;

  // these are histos of muon pt distributions
  // numrator is muon coming inside a particular flv jet
  // denominator is all muons pt distribution
  
  for(int j = 0; j <= hist_GenMuonRatio_Inclusive->GetNbinsX()+1; j++)
    {


      Double_t BinContent_Inclusive = hist_GenMuonRatio_Inclusive->GetBinContent(j);
      
      Double_t BinContent_U = hist_GenMuonRatio_U->GetBinContent(j);
      Double_t BinContent_D = hist_GenMuonRatio_D->GetBinContent(j);
      Double_t BinContent_S = hist_GenMuonRatio_S->GetBinContent(j);
      Double_t BinContent_C = hist_GenMuonRatio_C->GetBinContent(j);
      Double_t BinContent_B = hist_GenMuonRatio_B->GetBinContent(j);
      Double_t BinContent_G = hist_GenMuonRatio_G->GetBinContent(j);

      Double_t BinContent_Un = hist_GenMuonRatio_Un->GetBinContent(j);
      Double_t BinContent_Ze = hist_GenMuonRatio_Ze->GetBinContent(j);
      Double_t BinContent_NR = hist_GenMuonRatio_NR->GetBinContent(j);
      
      Double_t BinContent_Total = BinContent_U + BinContent_D + BinContent_S + BinContent_C + BinContent_B + BinContent_G +
	BinContent_Un + BinContent_Ze + BinContent_NR;
      
      Double_t BinContent_Ratio =  BinContent_Inclusive/BinContent_Total;
      
      cout<<" mu pt ratio bin content "<< hist_GenMuonRatio_Inclusive->GetBinCenter(j)<<"    "<<BinContent_Ratio<<endl;
      
      
    }
  cout<<endl;
  
  

  

  cout<<" =============================================================================== "<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<endl<<endl<<endl;
  cout<<endl<<endl<<endl;
  
  //=============================================================================//
  //============================ making a latex table ==========================//
  //===========================================================================//
  
  char OutTexFile[1000];
  sprintf(OutTexFile,"OutTexFile/GenTable/GenJetTable.tex");
  ofstream dataFile(Form("%s",OutTexFile));
  
  char Str1[100],Str2[100],Str3[100];
  sprintf(Str1,"\\hline");
  sprintf(Str2,"\\\\");
  sprintf(Str3,"\\");
  
  dataFile<<Str3<<"documentclass[12 pt]{article}"<<endl;
  dataFile<<Str3<<"usepackage{graphicx}"<<endl;
  dataFile<<Str3<<"usepackage{multirow}"<<endl;
  dataFile<<Str3<<"begin{document}"<<endl<<endl;
  
  dataFile<<Str3<<"begin{table}[htb]"<<endl;
  dataFile<<Str3<<"begin{center}"<<endl;
  dataFile<<Str3<<"caption{Gen Jet Fraction in all Events}"<<endl;
  dataFile<<Str3<<"label{}"<<endl;
  
  dataFile<<Str3<<"begin{tabular}{|cc|}"<<endl;
  dataFile<<Str1<<endl;
  
  dataFile<<"Type"<<" &Fraction"<<Str2<<endl;

  dataFile<<Str1<<endl;
    
  dataFile<<" Total "<<" &"<<setprecision(4)<<fixed <<TotalGenJetFraction<<Str2<<endl;

  dataFile<<"  u "<<" &"<<setprecision(4)<<fixed << UpGenJetFraction <<Str2<<endl;
  dataFile<<"  d "<<" &"<<setprecision(4)<<fixed << DownGenJetFraction <<Str2<<endl;
  dataFile<<"  s "<<" &"<<setprecision(4)<<fixed << StrangeGenJetFraction <<Str2<<endl;
  dataFile<<"  c "<<" &"<<setprecision(4)<<fixed << CharmGenJetFraction <<Str2<<endl;
  dataFile<<"  b "<<" &"<<setprecision(4)<<fixed << BeautyGenJetFraction <<Str2<<endl;
  dataFile<<"  g "<<" &"<<setprecision(4)<<fixed << GluonGenJetFraction <<Str2<<endl;
  
  dataFile<<Str1<<endl;
  dataFile<<Str3<<"end{tabular}"<<endl;
  dataFile<<Str3<<"end{center}"<<endl;
  dataFile<<Str3<<"end{table}"<<endl;
  dataFile<<endl<<endl<<endl;



  
  for(int i =0;i<NJetPtCut;i++){
  


    dataFile<<Str3<<"begin{table}[htb]"<<endl;
    dataFile<<Str3<<"begin{center}"<<endl;
    dataFile<<Str3<<"caption{Gen Jet Fraction  above Jet p$_{T}$ "<< setprecision(1)<<fixed << JetPtCut[i] <<" GeV/c }"<<endl;
    dataFile<<Str3<<"label{}"<<endl;
    
    dataFile<<Str3<<"begin{tabular}{|cc|}"<<endl;
    dataFile<<Str1<<endl;
    
    dataFile<<"Type"<<" &Fraction"<<Str2<<endl;
    
    dataFile<<Str1<<endl;
    
  
    dataFile<<" Total "<<" &"<<setprecision(4)<<fixed <<TotalGenJetFraction<<Str2<<endl;
    
    dataFile<<"  u "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][1] <<Str2<<endl;
    dataFile<<"  d "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][2] <<Str2<<endl;
    dataFile<<"  s "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][3] <<Str2<<endl;
    dataFile<<"  c "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][4] <<Str2<<endl;
    dataFile<<"  b "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][5] <<Str2<<endl;
    dataFile<<"  g "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][6] <<Str2<<endl;
    
    dataFile<<Str1<<endl;
    dataFile<<Str3<<"end{tabular}"<<endl;
    dataFile<<Str3<<"end{center}"<<endl;
    dataFile<<Str3<<"end{table}"<<endl;
    dataFile<<endl<<endl<<endl;



     dataFile<<Str3<<"begin{table}[htb]"<<endl;
     dataFile<<Str3<<"begin{center}"<<endl;
     dataFile<<Str3<<"caption{Gen Jet Fraction and number of Jet s above Jet p$_{T}$ "<< setprecision(1)<<fixed << JetPtCut[i] <<" GeV/c }"<<endl;
     dataFile<<Str3<<"label{}"<<endl;
     
     dataFile<<Str3<<"begin{tabular}{|ccc|}"<<endl;
     dataFile<<Str1<<endl;
    
     dataFile<<"   Type   "<<"   &Fraction   "<< "   &Number   "<< Str2<<endl;
     
     dataFile<<Str1<<endl;
    
  
     dataFile<<" Total "<<" &"<<setprecision(4)<<fixed <<TotalGenJetFraction<<" & "<<setprecision(1)<<fixed<<TotalJetTriggerEvents[i]<<Str2<<endl;
    
     dataFile<<"  u "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][1] <<" &"<<setprecision(1)<<fixed << TotalJetTriggerEvents[i]*GenJetPtCut_Flavour_Fraction[i][1] <<Str2<<endl;
     dataFile<<"  d "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][2] <<" &"<<setprecision(1)<<fixed << TotalJetTriggerEvents[i]*GenJetPtCut_Flavour_Fraction[i][2] <<Str2<<endl;
     dataFile<<"  s "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][3] <<" &"<<setprecision(1)<<fixed << TotalJetTriggerEvents[i]*GenJetPtCut_Flavour_Fraction[i][3] <<Str2<<endl;
     dataFile<<"  c "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][4] <<" &"<<setprecision(1)<<fixed << TotalJetTriggerEvents[i]*GenJetPtCut_Flavour_Fraction[i][4] <<Str2<<endl;
     dataFile<<"  b "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][5] <<" &"<<setprecision(1)<<fixed << TotalJetTriggerEvents[i]*GenJetPtCut_Flavour_Fraction[i][5] <<Str2<<endl;
     dataFile<<"  g "<<" &"<<setprecision(4)<<fixed << GenJetPtCut_Flavour_Fraction[i][6] <<" &"<<setprecision(1)<<fixed << TotalJetTriggerEvents[i]*GenJetPtCut_Flavour_Fraction[i][6] <<Str2<<endl;
     
     dataFile<<Str1<<endl;
     dataFile<<Str3<<"end{tabular}"<<endl;
     dataFile<<Str3<<"end{center}"<<endl;
     dataFile<<Str3<<"end{table}"<<endl;
     dataFile<<endl<<endl<<endl;
     
          
  }//Jet pT cut
  cout<<endl<<endl;


  
  dataFile<<Str3<<"begin{table}[htb]"<<endl;
  dataFile<<Str3<<"begin{center}"<<endl;
  dataFile<<Str3<<"caption{Gen Jet Fraction with muons}"<<endl;
  dataFile<<Str3<<"label{}"<<endl;
  
  dataFile<<Str3<<"begin{tabular}{|cc|}"<<endl;
  dataFile<<Str1<<endl;
  
  dataFile<<"Type"<<" &Fraction"<<Str2<<endl;

  dataFile<<Str1<<endl;
  
  
  dataFile<<" Total "<<" &"<<setprecision(4)<<fixed <<TotalGenMuonGenJetFraction<<Str2<<endl;

  dataFile<<"  u "<<" &"<<setprecision(4)<<fixed << UpGenMuonGenJetFraction <<Str2<<endl;
  dataFile<<"  d "<<" &"<<setprecision(4)<<fixed << DownGenMuonGenJetFraction <<Str2<<endl;
  dataFile<<"  s "<<" &"<<setprecision(4)<<fixed << StrangeGenMuonGenJetFraction <<Str2<<endl;
  dataFile<<"  c "<<" &"<<setprecision(4)<<fixed << CharmGenMuonGenJetFraction <<Str2<<endl;
  dataFile<<"  b "<<" &"<<setprecision(4)<<fixed << BeautyGenMuonGenJetFraction <<Str2<<endl;
  dataFile<<"  g "<<" &"<<setprecision(4)<<fixed << GluonGenMuonGenJetFraction <<Str2<<endl;
  
  dataFile<<Str1<<endl;
  dataFile<<Str3<<"end{tabular}"<<endl;
  dataFile<<Str3<<"end{center}"<<endl;
  dataFile<<Str3<<"end{table}"<<endl;
  dataFile<<endl<<endl<<endl;



  //GenMuPtCut_Flavour_Fraction[NMuonPtCut][NFlvLocal]
  //These events are taken from the Muon Trigger Table
  //HLT_HIL3Mu0_L2Mu0_v1  1240488 HLT HIL3Mu12 v1       4033337  HLT HIL3Mu15 v1       2214246 HLT HIL3Mu20 v1       1193276
  Double_t TotalMuTriggerEvents[NMuonPtCut] = {1240488, 4033337, 2214246, 1193276};
  
  for(int i =0;i<NMuonPtCut;i++){
  

    dataFile<<Str3<<"begin{table}[htb]"<<endl;
    dataFile<<Str3<<"begin{center}"<<endl;
    dataFile<<Str3<<"caption{Gen Jet Fraction with gen muons above p$_{T}$ "<< setprecision(1)<<fixed << MuonPtCut[i] <<" GeV/c }"<<endl;
    dataFile<<Str3<<"label{}"<<endl;
    
    dataFile<<Str3<<"begin{tabular}{|cc|}"<<endl;
    dataFile<<Str1<<endl;
    
    dataFile<<"Type"<<" &Fraction"<<Str2<<endl;
    
    dataFile<<Str1<<endl;
    
  
    dataFile<<" Total "<<" &"<<setprecision(4)<<fixed <<TotalGenMuonGenJetFraction<<Str2<<endl;
    
    dataFile<<"  u "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_Fraction[i][1] <<Str2<<endl;
    dataFile<<"  d "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_Fraction[i][2] <<Str2<<endl;
    dataFile<<"  s "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_Fraction[i][3] <<Str2<<endl;
    dataFile<<"  c "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_Fraction[i][4] <<Str2<<endl;
    dataFile<<"  b "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_Fraction[i][5] <<Str2<<endl;
    dataFile<<"  g "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_Fraction[i][6] <<Str2<<endl;
    
    dataFile<<Str1<<endl;
    dataFile<<Str3<<"end{tabular}"<<endl;
    dataFile<<Str3<<"end{center}"<<endl;
    dataFile<<Str3<<"end{table}"<<endl;
    dataFile<<endl<<endl<<endl;





    dataFile<<Str3<<"begin{table}[htb]"<<endl;
    dataFile<<Str3<<"begin{center}"<<endl;
    dataFile<<Str3<<"caption{Probability of Gen Muons coming with different flavours above p$_{T}$ "<< setprecision(1)<<fixed << MuonPtCut[i] <<" GeV/c }"<<endl;
    dataFile<<Str3<<"label{}"<<endl;
    


    dataFile<<Str3<<"begin{tabular}{|ccc|}"<<endl;
    dataFile<<Str1<<endl;
    
    dataFile<<"   Type   "<<"   &Prob.   "<< "   &Number   "<< Str2<<endl;
     
     dataFile<<Str1<<endl;
    
  
     dataFile<<" Total "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][0] <<" & "<<setprecision(1)<<fixed<<TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][0]<<Str2<<endl;
    
     dataFile<<"  u "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][1] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][1] <<Str2<<endl;
     dataFile<<"  d "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][2] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][2] <<Str2<<endl;
     dataFile<<"  s "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][3] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][3] <<Str2<<endl;
     dataFile<<"  c "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][4] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][4] <<Str2<<endl;
     dataFile<<"  b "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][5] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][5] <<Str2<<endl;
     dataFile<<"  g "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][6] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][6] <<Str2<<endl;


    dataFile<<Str1<<endl;
    dataFile<<Str3<<"end{tabular}"<<endl;
    dataFile<<Str3<<"end{center}"<<endl;
    dataFile<<Str3<<"end{table}"<<endl;
    dataFile<<endl<<endl<<endl;

    
    
    dataFile<<Str3<<"begin{table}[htb]"<<endl;
    dataFile<<Str3<<"begin{center}"<<endl;
    dataFile<<Str3<<"caption{Probability of Muons coming with Jets and estimated Jet Events, muons above p$_{T}$ "<< setprecision(1)<<fixed << MuonPtCut[i] <<" GeV/c }"<<endl;
    dataFile<<Str3<<"label{}"<<endl;
    


    dataFile<<Str3<<"begin{tabular}{|ccc|}"<<endl;
    dataFile<<Str1<<endl;
    
    dataFile<<"   Type   "<<"   &Prob.   "<< "   &Number   "<< Str2<<endl;
     
     dataFile<<Str1<<endl;
    
  
     dataFile<<" Total "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][0] <<" & "<<setprecision(1)<<fixed<<TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][0]<<Str2<<endl;
    
     dataFile<<"  u "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][1] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][1] <<Str2<<endl;
     dataFile<<"  d "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][2] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][2] <<Str2<<endl;
     dataFile<<"  s "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][3] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][3] <<Str2<<endl;
     dataFile<<"  c "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][4] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][4] <<Str2<<endl;
     dataFile<<"  b "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][5] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][5] <<Str2<<endl;
     dataFile<<"  g "<<" &"<<setprecision(4)<<fixed << GenMuPtCut_Flavour_GenMuonFraction[i][6] <<" &"<<setprecision(1)<<fixed << TotalMuTriggerEvents[i]*GenMuPtCut_Flavour_GenMuonFraction[i][6] <<Str2<<endl;


    dataFile<<Str1<<endl;
    dataFile<<Str3<<"end{tabular}"<<endl;
    dataFile<<Str3<<"end{center}"<<endl;
    dataFile<<Str3<<"end{table}"<<endl;
    dataFile<<endl<<endl<<endl;


  }// muon pT cut
  cout<<endl<<endl;

  
  
dataFile<<Str3<<"end{document}"<<endl<<endl;







  
  return;


  
  

}

