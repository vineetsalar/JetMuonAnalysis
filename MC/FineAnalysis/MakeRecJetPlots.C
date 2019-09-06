#include "MyMethod.h"

void MakeRecJetPlots(TFile *file_in, TFile *file_out, Double_t RecJetPtMin)
{

  setTDRStyle();
  gStyle->SetPadBottomMargin(0.2);
  TH1::SetDefaultSumw2();

  char LatexChar[400];
  
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
  int Flv_Legend_Index_Local = 1000;
  int Flv_Legend_Index_Local_V = 1000;
  const int NFlvLocal = 6;
  
  MyMethod *RecJetMethod = new MyMethod();

  
  // ============================================================================================== //
  // ============================================================================================== //
  // ====================== REC JET ANALYSIS ====================================================== //
  // ====================== 1D HISTO REC JET PT AND JET FLAVOUR =================================== //
  // ============================================================================================== //
  // ============================================================================================== //
  
  cout<<" +++++++++++++++++++++++ RECO JETS STUDY ++++++++++++++++++++++++++++++++"<<endl;



  // Get the 1D histograms of Jet variables 

  // Jet histograms for all flavours
  TH1D *hist_JetPt=(TH1D*)file_in->Get("histJetPt");
  TH1D *hist_JetEta=(TH1D*)file_in->Get("histJetEta");
  TH1D *hist_JetPhi=(TH1D*)file_in->Get("histJetPhi");
  
  new TCanvas;
  gPad->SetLogy(1);
  hist_JetPt->Draw();
  gPad->SaveAs("Plots/PFJets/JetPt.png");
  gPad->SaveAs("Plots/PFJets/JetPt.pdf");
  
  
  new TCanvas;
  hist_JetEta->Draw();
  gPad->SaveAs("Plots/PFJets/JetEta.png");
  gPad->SaveAs("Plots/PFJets/JetEta.pdf");
  
  
  new TCanvas;
  hist_JetPhi->Draw();
  gPad->SaveAs("Plots/PFJets/JetPhi.png");
  gPad->SaveAs("Plots/PFJets/JetPhi.pdf");



  // Jet pt histo for u,d,s
  TH1D *hist_JetPtLight=(TH1D*)file_in->Get("histJetPtLight");
  new TCanvas;
  gPad->SetLogy(1);
  hist_JetPtLight->Draw();
  gPad->SaveAs("Plots/PFJets/JetPtLight.png");
  gPad->SaveAs("Plots/PFJets/JetPtLight.pdf");


  TH1D *hist_JetPtUp=(TH1D*)file_in->Get("histJetPtUp");
  TH1D *hist_JetPtDown=(TH1D*)file_in->Get("histJetPtDown");
  TH1D *hist_JetPtStrange=(TH1D*)file_in->Get("histJetPtStrange");


  TH1D *hist_JetPtCharm=(TH1D*)file_in->Get("histJetPtCharm");
  
  new TCanvas;
  gPad->SetLogy(1);
  hist_JetPtCharm->Draw();
  gPad->SaveAs("Plots/PFJets/JetPtCharm.png");
  gPad->SaveAs("Plots/PFJets/JetPtCharm.pdf");


  TH1D *hist_JetPtBeauty=(TH1D*)file_in->Get("histJetPtBeauty");
  new TCanvas;
  gPad->SetLogy(1);
  hist_JetPtBeauty->Draw();
  gPad->SaveAs("Plots/PFJets/JetPtBeauty.png");
  gPad->SaveAs("Plots/PFJets/JetPtBeauty.pdf");


  
  TH1D *hist_JetPtGluon=(TH1D*)file_in->Get("histJetPtGluon");
  new TCanvas;
  gPad->SetLogy(1);
  hist_JetPtGluon->Draw();
  gPad->SaveAs("Plots/PFJets/JetPtGluon.png");
  gPad->SaveAs("Plots/PFJets/JetPtGluon.pdf");


  
  Double_t TotalIntegralOfJets = hist_JetPt->Integral(0,hist_JetPt->GetNbinsX());
  Double_t TotalIntegralOfLightJets =  hist_JetPtLight->Integral(0,hist_JetPtLight->GetNbinsX());
  Double_t TotalIntegralOfUpJets = hist_JetPtUp->Integral(0,hist_JetPtUp->GetNbinsX());
  Double_t TotalIntegralOfDownJets = hist_JetPtDown->Integral(0,hist_JetPtDown->GetNbinsX());
  Double_t TotalIntegralOfStrangeJets = hist_JetPtStrange->Integral(0,hist_JetPtStrange->GetNbinsX());
  Double_t TotalIntegralOfCharmJets = hist_JetPtCharm->Integral(0,hist_JetPtCharm->GetNbinsX());
  Double_t TotalIntegralOfBeautyJets = hist_JetPtBeauty->Integral(0,hist_JetPtBeauty->GetNbinsX());
  Double_t TotalIntegralOfGluonJets = hist_JetPtGluon->Integral(0,hist_JetPtGluon->GetNbinsX());



  Double_t TotalJetFraction = TotalIntegralOfJets/TotalIntegralOfJets;
  Double_t LightJetFraction = TotalIntegralOfLightJets/TotalIntegralOfJets;

  Double_t UpJetFraction = TotalIntegralOfUpJets/TotalIntegralOfJets;
  Double_t DownJetFraction = TotalIntegralOfDownJets/TotalIntegralOfJets;
  Double_t StrangeJetFraction = TotalIntegralOfStrangeJets/TotalIntegralOfJets;
  Double_t CharmJetFraction = TotalIntegralOfCharmJets/TotalIntegralOfJets;
  Double_t BeautyJetFraction = TotalIntegralOfBeautyJets/TotalIntegralOfJets;
  Double_t GluonJetFraction = TotalIntegralOfGluonJets/TotalIntegralOfJets;
  
  cout<<endl<<endl;
  cout<<" Total Integral of Jets above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfJets <<" fraction " <<TotalJetFraction<<endl;
  cout<<" Total Integral of Up Jets (u) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfUpJets <<" fraction  "<<UpJetFraction<<endl;
  cout<<" Total Integral of Down Jets (d) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfDownJets<<" fraction  "<<DownJetFraction<<endl;
  cout<<" Total Integral of Strange Jets (s) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfStrangeJets<<" fraction  "<<StrangeJetFraction<<endl;
  cout<<" Total Integral of Charm Jets (c) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfCharmJets<<" fraction  "<<CharmJetFraction<<endl;
  cout<<" Total Integral of Beauty Jets (b) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfBeautyJets<<" fraction  "<<BeautyJetFraction<<endl;
  cout<<" Total Integral of Gluon Jets (g) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfGluonJets<<" fraction  "<<GluonJetFraction<<endl;
  cout<<endl<<endl;



  
  
  const char *ABC[NFlvLocal] = {"u","d","s","c","b","g"};
  
  //const char *ABC[6] = {"u","d","s","c","b","g"};

  TH1D *h = new TH1D("hr","test",6,0,6);
  for (int i=1;i<=6;i++) h->GetXaxis()->SetBinLabel(i,ABC[i-1]);
  h->GetYaxis()->SetTitle("fraction");
  h->SetMaximum(1);

  Double_t JetFrac[NFlvLocal]={UpJetFraction,DownJetFraction,StrangeJetFraction,CharmJetFraction,BeautyJetFraction,GluonJetFraction};
  Double_t JetType[NFlvLocal]={0.5,1.5,2.5,3.5,4.5,5.5};

  TLegend *lgd_JetFrac = new TLegend(0.25,0.75,0.59,0.85,"","brNDC");
  lgd_JetFrac->SetBorderSize(0);
  lgd_JetFrac->SetTextFont(42);
  lgd_JetFrac->SetLineColor(1);
  lgd_JetFrac->SetLineStyle(1);
  lgd_JetFrac->SetLineWidth(1);
  lgd_JetFrac->SetFillColor(19);
  lgd_JetFrac->SetFillStyle(0);

    
  TGraph *graph_JetFracGraph = new TGraph (6,JetType,JetFrac);
  graph_JetFracGraph->GetYaxis()->SetRangeUser(0,1);

  lgd_JetFrac->AddEntry(graph_JetFracGraph,"All pf Jets","f");
  

  new TCanvas;
  h->Draw();
  graph_JetFracGraph->SetFillColorAlpha(kBlue,0.8);
  graph_JetFracGraph->Draw("Bsame");
  lgd_JetFrac->Draw("same");

  gPad->SaveAs("Plots/PFJets/JetFrac.png");
  gPad->SaveAs("Plots/PFJets/JetFrac.pdf");



  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  // ====================== 1D HISTO REC JET PT AND JET FLAVOUR ENDS ============================== //
  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  



  // ============================================================================================== //
  // ============================================================================================== //
  // ====================== REC JET ANALYSIS ====================================================== //
  // ====================== 1D HISTO REC Muon-JET PT AND JET FLAVOUR ============================= //
  // ============================================================================================== //
  // ============================================================================================== //



  
  TH1D *hist_MuonJetDR=(TH1D*)file_in->Get("histMuonJetDR");
  new TCanvas;
  gPad->SetLogy(1);
  hist_MuonJetDR->Draw();
  gPad->SaveAs("Plots/PFJets/MuonJetDR.png");
  gPad->SaveAs("Plots/PFJets/MuonJetDR.pdf");



  
  TH1D *hist_MuonJetDPhi=(TH1D*)file_in->Get("histMuonJetDPhi");
  new TCanvas;
  gPad->SetLogy(1);
  hist_MuonJetDPhi->Draw();
  gPad->SaveAs("Plots/PFJets/MuonJetDPhi.png");
  gPad->SaveAs("Plots/PFJets/MuonJetDPhi.pdf");



  TH1D *hist_MuonJetPtTotal=(TH1D*)file_in->Get("histMuonJetPtTotal");
  TH1D *hist_MuonJetPtLight=(TH1D*)file_in->Get("histMuonJetPtLight");
  new TCanvas;
  gPad->SetLogy(1);
  hist_MuonJetPtLight->Draw();
  gPad->SaveAs("Plots/PFJets/MuonJetPtLight.png");
  gPad->SaveAs("Plots/PFJets/MuonJetPtLight.pdf");



  TH1D *hist_MuonJetPtUp=(TH1D*)file_in->Get("histMuonJetPtUp");
  TH1D *hist_MuonJetPtDown=(TH1D*)file_in->Get("histMuonJetPtDown");
  TH1D *hist_MuonJetPtStrange=(TH1D*)file_in->Get("histMuonJetPtStrange");
  TH1D *hist_MuonJetPtCharm=(TH1D*)file_in->Get("histMuonJetPtCharm");
  
  
  new TCanvas;
  gPad->SetLogy(1);
  hist_MuonJetPtCharm->Draw();
  gPad->SaveAs("Plots/PFJets/MuonJetPtCharm.png");
  gPad->SaveAs("Plots/PFJets/MuonJetPtCharm.pdf");


  TH1D *hist_MuonJetPtBeauty=(TH1D*)file_in->Get("histMuonJetPtBeauty");
  new TCanvas;
  gPad->SetLogy(1);
  hist_MuonJetPtBeauty->Draw();
  gPad->SaveAs("Plots/PFJets/MuonJetPtBeauty.png");
  gPad->SaveAs("Plots/PFJets/MuonJetPtBeauty.pdf");


  

  TH1D *hist_MuonJetPtGluon=(TH1D*)file_in->Get("histMuonJetPtGluon");
  new TCanvas;
  gPad->SetLogy(1);
  hist_MuonJetPtGluon->Draw();
  gPad->SaveAs("Plots/PFJets/MuonJetPtGluon.png");
  gPad->SaveAs("Plots/PFJets/MuonJetPtGluon.pdf");


  //no overflow

  Double_t TotalIntegralOfMuonJets = hist_MuonJetPtTotal->Integral(0,hist_MuonJetPtTotal->GetNbinsX());
  //Double_t TotalIntegralOfMuonJets = hist_MuonJetPtTotal->GetEntries();
  Double_t TotalIntegralOfLightMuonJets = hist_MuonJetPtLight->Integral(0,hist_MuonJetPtLight->GetNbinsX());
  Double_t TotalIntegralOfUpMuonJets = hist_MuonJetPtUp->Integral(0,hist_MuonJetPtUp->GetNbinsX());
  Double_t TotalIntegralOfDownMuonJets = hist_MuonJetPtDown->Integral(0,hist_MuonJetPtDown->GetNbinsX());
  Double_t TotalIntegralOfStrangeMuonJets = hist_MuonJetPtStrange->Integral(0,hist_MuonJetPtStrange->GetNbinsX());
  Double_t TotalIntegralOfCharmMuonJets = hist_MuonJetPtCharm->Integral(0,hist_MuonJetPtCharm->GetNbinsX());
  Double_t TotalIntegralOfBeautyMuonJets = hist_MuonJetPtBeauty->Integral(0,hist_MuonJetPtBeauty->GetNbinsX());
  Double_t TotalIntegralOfGluonMuonJets = hist_MuonJetPtGluon->Integral(0,hist_MuonJetPtGluon->GetNbinsX());


  
  
  Double_t TotalMuonJetFraction = TotalIntegralOfMuonJets/TotalIntegralOfMuonJets;
  Double_t LightMuonJetFraction = TotalIntegralOfLightMuonJets/TotalIntegralOfMuonJets;
  Double_t UpMuonJetFraction = TotalIntegralOfUpMuonJets/TotalIntegralOfMuonJets;
  Double_t DownMuonJetFraction = TotalIntegralOfDownMuonJets/TotalIntegralOfMuonJets;
  Double_t StrangeMuonJetFraction = TotalIntegralOfStrangeMuonJets/TotalIntegralOfMuonJets;
  Double_t CharmMuonJetFraction = TotalIntegralOfCharmMuonJets/TotalIntegralOfMuonJets;
  Double_t BeautyMuonJetFraction = TotalIntegralOfBeautyMuonJets/TotalIntegralOfMuonJets;
  Double_t GluonMuonJetFraction = TotalIntegralOfGluonMuonJets/TotalIntegralOfMuonJets;

  cout<<endl<<endl;
  
  cout<<" Total Integral of MuonJets above "<< RecJetPtMin << " GeV/c pT "<< TotalIntegralOfMuonJets <<" fraction  "<< TotalMuonJetFraction <<endl;
  cout<<" Total Integral of Light MuonJets (u,d,s) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfLightMuonJets <<" fraction  "<<LightMuonJetFraction<<endl;
  cout<<" Total Integral of Up MuonJets (u) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfUpMuonJets <<" fraction  "<<UpMuonJetFraction<<endl;
  cout<<" Total Integral of Down MuonJets (u) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfDownMuonJets <<" fraction  "<<DownMuonJetFraction<<endl;
  cout<<" Total Integral of Strange MuonJets (u) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfStrangeMuonJets <<" fraction  "<<StrangeMuonJetFraction<<endl;
  cout<<" Total Integral of Charm MuonJets (c) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfCharmMuonJets <<" fraction  "<<CharmMuonJetFraction<<endl;
  cout<<" Total Integral of Beauty MuonJets (b) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfBeautyMuonJets <<" fraction  "<<BeautyMuonJetFraction<<endl;
  cout<<" Total Integral of Gluon MuonJets (g) above "<< RecJetPtMin<< " GeV/c pT "<< TotalIntegralOfGluonMuonJets <<" fraction  "<<GluonMuonJetFraction<<endl;
  
  cout<<endl<<endl;
  
      
  Double_t MuonJetFrac[NFlvLocal]={UpMuonJetFraction,DownMuonJetFraction,StrangeMuonJetFraction,CharmMuonJetFraction,BeautyMuonJetFraction,GluonMuonJetFraction};
  const Double_t MuonJetType[NFlvLocal]={0.5,1.5,2.5,3.5,4.5,5.5};
  
  
  TGraph *graph_MuonJetFracGraph = new TGraph (6,MuonJetType,MuonJetFrac);
  

  graph_MuonJetFracGraph->GetXaxis()->SetTitle("JetType");
  graph_MuonJetFracGraph->GetYaxis()->SetTitle("Jet Fraction");

  graph_MuonJetFracGraph->SetMarkerStyle(21);
  graph_MuonJetFracGraph->SetMarkerColor(2);
  graph_MuonJetFracGraph->GetYaxis()->SetRangeUser(0,1);

  
  
  TLegend *lgd_MuonJetFrac = new TLegend(0.25,0.75,0.59,0.85,"","brNDC");
  lgd_MuonJetFrac->SetBorderSize(0);
  lgd_MuonJetFrac->SetTextFont(42);
  //lgd_MuonJetFrac->SetTextSize(1.8);
  lgd_MuonJetFrac->SetLineColor(1);
  lgd_MuonJetFrac->SetLineStyle(1);
  lgd_MuonJetFrac->SetLineWidth(1);
  lgd_MuonJetFrac->SetFillColor(19);
  lgd_MuonJetFrac->SetFillStyle(0);

  lgd_MuonJetFrac->AddEntry(graph_JetFracGraph,"All pf Jets","f");
  lgd_MuonJetFrac->AddEntry(graph_MuonJetFracGraph,"pf Jets with Muons","f");

  new TCanvas;
  h->Draw();
  graph_MuonJetFracGraph->SetFillColorAlpha(kRed,0.6);
  graph_MuonJetFracGraph->Draw("Bsame");
  

  new TCanvas;
  h->Draw();
  graph_JetFracGraph->Draw("Bsame");
  graph_MuonJetFracGraph->Draw("Bsame");
  lgd_MuonJetFrac->Draw("same");


  //tb->DrawLatex(0.24,0.76,"JetType = 1 (u,d,s)");
  //tb->DrawLatex(0.24,0.70,"JetType = 2 (c)");
  //tb->DrawLatex(0.24,0.64,"JetType = 3 (b)");
  //tb->DrawLatex(0.24,0.58,"JetType = 4 (gluon)");

  gPad->SaveAs("Plots/PFJets/MuonJetFrac.png");
  gPad->SaveAs("Plots/PFJets/MuonJetFrac.pdf");

 
  

  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  // ====================== 1D REC Muon-JET PT AND JET FLAVOUR ANALYSIS ENDS ====================== //
  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //



  // =============================================================================== //
  // ====================== PF JET ANALYSIS ======================================== //
  // ====================== 2D HISTO PF JET PT AND JET FLAVOUR ===================== //
  // =============================================================================== //

  cout<<endl<<endl<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<" ====================== PF JET ANALYSIS ======================================= "<<endl;
  cout<<" ====================== 2D HISTO PF JET PT AND JET FLAVOUR ==================== "<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<endl<<endl<<endl;
  
  
  
  //Get the 2D Histo of JetPt, Flavour
  TH2D *hist_Master_JetPt_Flavour = (TH2D*)file_in->Get("hist_Master_JetPt_Flavour");

  // test to see if there is anything on flv 9 (nothing found)
  //TH1 *hist_JetFlv_Inclusive = hist_Master_JetPt_Flavour->ProjectionY("hist_JetFlv_Inclusive",0,-1);
  //new TCanvas;
  //hist_JetFlv_Inclusive->Draw();
    
  

  //================= Get the bins numbers for different flavours ================//
  Int_t FlavourBinMinForU = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(1);
  Int_t FlavourBinMaxForU = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(1);
  
  Int_t FlavourBinMinForD = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(2);
  Int_t FlavourBinMaxForD = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(2);
  
  Int_t FlavourBinMinForS = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(3);
  Int_t FlavourBinMaxForS = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(3);
    
  Int_t FlavourBinMinForC = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(4);
  Int_t FlavourBinMaxForC = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(4);
      
  Int_t FlavourBinMinForB = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(5);
  Int_t FlavourBinMaxForB = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(5);
  
  Int_t FlavourBinMinForG = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(6);
  Int_t FlavourBinMaxForG = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(6);

  //-999  //===== unknown flavour
  Int_t FlavourBinMinForUn = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(7);
  Int_t FlavourBinMaxForUn = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(7);
  //0
  Int_t FlavourBinMinForZe = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(8);
  Int_t FlavourBinMaxForZe = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(8);

  //============ Total Jets =======================//
  Int_t FlavourBinMinForInc = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(1);
  Int_t FlavourBinMaxForInc = hist_Master_JetPt_Flavour->GetYaxis()->FindBin(9);


  //================ PF Jet Fractions as a function of pT =====================//
  // get the projection on pT axis
  TH1 *hist_JetPt_Inclusive = hist_Master_JetPt_Flavour->ProjectionX("hist_JetPt_Inclusive",FlavourBinMinForInc,FlavourBinMaxForInc);
  hist_JetPt_Inclusive->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_JetPt_Inclusive->GetXaxis()->SetTitle("p_{T}(GeV/c)");
  
    
  TH1 *hist_JetPt_U = hist_Master_JetPt_Flavour->ProjectionX("hist_JetPt_U",FlavourBinMinForU,FlavourBinMaxForU);
  TH1 *hist_JetPt_D = hist_Master_JetPt_Flavour->ProjectionX("hist_JetPt_D",FlavourBinMinForD,FlavourBinMaxForD);
  TH1 *hist_JetPt_S = hist_Master_JetPt_Flavour->ProjectionX("hist_JetPt_S",FlavourBinMinForS,FlavourBinMaxForS);
  TH1 *hist_JetPt_C = hist_Master_JetPt_Flavour->ProjectionX("hist_JetPt_C",FlavourBinMinForC,FlavourBinMaxForC);
  TH1 *hist_JetPt_B = hist_Master_JetPt_Flavour->ProjectionX("hist_JetPt_B",FlavourBinMinForB,FlavourBinMaxForB);
  TH1 *hist_JetPt_G = hist_Master_JetPt_Flavour->ProjectionX("hist_JetPt_G",FlavourBinMinForG,FlavourBinMaxForG);
  //unknown -999
  TH1 *hist_JetPt_Un = hist_Master_JetPt_Flavour->ProjectionX("hist_JetPt_Un",FlavourBinMinForUn,FlavourBinMaxForUn);
  //0
  TH1 *hist_JetPt_Ze = hist_Master_JetPt_Flavour->ProjectionX("hist_JetPt_Ze",FlavourBinMinForZe,FlavourBinMaxForZe);

  //==================================================================//
  //========= ASYMATRIC REBINNING PF JETS ===========================//
  //==================================================================//
  RecJetMethod->rebinAsymmetric(hist_JetPt_Inclusive, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
  RecJetMethod->rebinAsymmetric(hist_JetPt_U, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
  RecJetMethod->rebinAsymmetric(hist_JetPt_D, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
  RecJetMethod->rebinAsymmetric(hist_JetPt_S, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
  RecJetMethod->rebinAsymmetric(hist_JetPt_C, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
  RecJetMethod->rebinAsymmetric(hist_JetPt_B, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
  RecJetMethod->rebinAsymmetric(hist_JetPt_G, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);

  RecJetMethod->rebinAsymmetric(hist_JetPt_Un, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
  RecJetMethod->rebinAsymmetric(hist_JetPt_Ze, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
  
  // Setting Histograms marker style and marker colors
  RecJetMethod->FlavouredHistogram(hist_JetPt_Inclusive, 1, 1, 20,RecJetMethod->MarkerSizeArray[1]);
  RecJetMethod->FlavouredHistogram(hist_JetPt_U, RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
  RecJetMethod->FlavouredHistogram(hist_JetPt_D, RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
  RecJetMethod->FlavouredHistogram(hist_JetPt_S, RecJetMethod->LineColorArray[3], RecJetMethod->MarkerColorArray[3], RecJetMethod->MarkerStyleArray[3],RecJetMethod->MarkerSizeArray[3]);
  RecJetMethod->FlavouredHistogram(hist_JetPt_C, RecJetMethod->LineColorArray[4], RecJetMethod->MarkerColorArray[4], RecJetMethod->MarkerStyleArray[4],RecJetMethod->MarkerSizeArray[4]);
  RecJetMethod->FlavouredHistogram(hist_JetPt_B, RecJetMethod->LineColorArray[5], RecJetMethod->MarkerColorArray[5], RecJetMethod->MarkerStyleArray[5],RecJetMethod->MarkerSizeArray[5]);
  RecJetMethod->FlavouredHistogram(hist_JetPt_G, RecJetMethod->LineColorArray[6], RecJetMethod->MarkerColorArray[6], RecJetMethod->MarkerStyleArray[6],RecJetMethod->MarkerSizeArray[6]);

  RecJetMethod->FlavouredHistogram(hist_JetPt_Un, RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
  RecJetMethod->FlavouredHistogram(hist_JetPt_Ze, RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
  
  // Canvas to Draw the Jet Pt Histograms 
  TCanvas *Canvas_JetPt_Flv_All = new TCanvas("Canvas_JetPt_Flv_All","Canvas_JetPt_Flv_All",800,800);
  Canvas_JetPt_Flv_All->cd(1);
  gPad->SetBottomMargin(0.2);
  gPad->SetLogy(1);
  // Ghost histogram because we want X axis to start from zero
  Double_t JetPt_Flv_GhostMin = 0.0001;
  Double_t JetPt_Flv_GhostMax = 10000.0;
  TH1D *hist_JetPt_Flv_Ghost = RecJetMethod->Get_Ghost_Hist("hist_JetPt_Flv_Ghost","hist_JetPt_Flv_Ghost",JetPt_Flv_GhostMin,JetPt_Flv_GhostMax,"PF Jet p_{T} (GeV/c)","dN/dp_{T} (GeV/c)^{-1}");
  hist_JetPt_Flv_Ghost->Draw();
  hist_JetPt_Inclusive->Draw("same");
  hist_JetPt_U->Draw("same");
  hist_JetPt_D->Draw("same");
  hist_JetPt_S->Draw("same");
  hist_JetPt_C->Draw("same");
  hist_JetPt_B->Draw("same");
  hist_JetPt_G->Draw("same");
  // draw flv legend
  RecJetMethod->DrawFlavourLegend(0.20,0.76,0.32,0.96, Flv_Legend_Index_Local++);
  gPad->SaveAs("Plots/PFJets/JetPt_Flv.png");
  gPad->SaveAs("Plots/PFJets/JetPt_Flv.pdf");
  
  // Canvas to Draw the Jet Pt Histograms (unknown and zero flv)
  TCanvas *Canvas_JetPt_FlvUn_All = new TCanvas("Canvas_JetPt_FlvUn_All","Canvas_JetPt_FlvUn_All",800,800);
  Canvas_JetPt_FlvUn_All->cd(1);
  gPad->SetBottomMargin(0.2);
  gPad->SetLogy(1);

  hist_JetPt_Flv_Ghost->Draw();
  hist_JetPt_Un->Draw("same");
  hist_JetPt_Ze->Draw("same");
  //Draw Flv legend unknown
  RecJetMethod->DrawFlavourLegendUn(0.20,0.76,0.32,0.96, Flv_Legend_Index_Local++);
  gPad->SaveAs("Plots/PFJets/JetPt_FlvUn.png");
  gPad->SaveAs("Plots/PFJets/JetPt_FlvUn.pdf");


  // Calculate the Jet fractions as a function of Jet pT
  TH1D *hist_Ratio_JetPt_U_JetPt_Inclusive = RecJetMethod->RatioHistogram(hist_JetPt_U,hist_JetPt_Inclusive,1);
  TH1D *hist_Ratio_JetPt_D_JetPt_Inclusive = RecJetMethod->RatioHistogram(hist_JetPt_D,hist_JetPt_Inclusive,1);
  TH1D *hist_Ratio_JetPt_S_JetPt_Inclusive = RecJetMethod->RatioHistogram(hist_JetPt_S,hist_JetPt_Inclusive,1);
  TH1D *hist_Ratio_JetPt_C_JetPt_Inclusive = RecJetMethod->RatioHistogram(hist_JetPt_C,hist_JetPt_Inclusive,1);
  TH1D *hist_Ratio_JetPt_B_JetPt_Inclusive = RecJetMethod->RatioHistogram(hist_JetPt_B,hist_JetPt_Inclusive,1);
  TH1D *hist_Ratio_JetPt_G_JetPt_Inclusive = RecJetMethod->RatioHistogram(hist_JetPt_G,hist_JetPt_Inclusive,1);

  TH1D *hist_Ratio_JetPt_Un_JetPt_Inclusive = RecJetMethod->RatioHistogram(hist_JetPt_Un,hist_JetPt_Inclusive,1);
  TH1D *hist_Ratio_JetPt_Ze_JetPt_Inclusive = RecJetMethod->RatioHistogram(hist_JetPt_Ze,hist_JetPt_Inclusive,1);
    
  // Setting the Marker Style, Marker color etc for the Histograms
  RecJetMethod->FlavouredHistogram(hist_Ratio_JetPt_U_JetPt_Inclusive, RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
  RecJetMethod->FlavouredHistogram(hist_Ratio_JetPt_D_JetPt_Inclusive, RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
  RecJetMethod->FlavouredHistogram(hist_Ratio_JetPt_S_JetPt_Inclusive, RecJetMethod->LineColorArray[3], RecJetMethod->MarkerColorArray[3], RecJetMethod->MarkerStyleArray[3],RecJetMethod->MarkerSizeArray[3]);
  RecJetMethod->FlavouredHistogram(hist_Ratio_JetPt_C_JetPt_Inclusive, RecJetMethod->LineColorArray[4], RecJetMethod->MarkerColorArray[4], RecJetMethod->MarkerStyleArray[4],RecJetMethod->MarkerSizeArray[4]);
  RecJetMethod->FlavouredHistogram(hist_Ratio_JetPt_B_JetPt_Inclusive, RecJetMethod->LineColorArray[5], RecJetMethod->MarkerColorArray[5], RecJetMethod->MarkerStyleArray[5],RecJetMethod->MarkerSizeArray[5]);
  RecJetMethod->FlavouredHistogram(hist_Ratio_JetPt_G_JetPt_Inclusive, RecJetMethod->LineColorArray[6], RecJetMethod->MarkerColorArray[6], RecJetMethod->MarkerStyleArray[6],RecJetMethod->MarkerSizeArray[6]);

  RecJetMethod->FlavouredHistogram(hist_Ratio_JetPt_Un_JetPt_Inclusive, RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
  RecJetMethod->FlavouredHistogram(hist_Ratio_JetPt_Ze_JetPt_Inclusive, RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
  
  // Canvas to draw the Jet Fractions as a function of pT  
  TCanvas *Canvas_Ratio_JetPt_Flv_JetPt_Inclusive = new TCanvas("Canvas_Ratio_JetPt_Flv_JetPt_Inclusive","Canvas_Ratio_JetPt_Flv_JetPt_Inclusive",800,800);
  Canvas_Ratio_JetPt_Flv_JetPt_Inclusive->cd(1);
  gPad->SetLogy(1);
  gPad->SetBottomMargin(0.2);

  // Ghost histogram for the Jet Fractions 
  TH1D *hist_PFJetFrac_JetPt_Ghost = RecJetMethod->Get_Ghost_Hist("hist_PFJetFrac_JetPt_Ghost","hist_PFJetFrac_JetPt_Ghost",0.005,1.5,"PF Jet p_{T} (GeV/c)","PF Jet Fraction");
  hist_PFJetFrac_JetPt_Ghost->Draw();

  hist_Ratio_JetPt_U_JetPt_Inclusive->Draw("same");
  hist_Ratio_JetPt_D_JetPt_Inclusive->Draw("same");
  hist_Ratio_JetPt_S_JetPt_Inclusive->Draw("same");
  hist_Ratio_JetPt_C_JetPt_Inclusive->Draw("same");
  hist_Ratio_JetPt_B_JetPt_Inclusive->Draw("same");
  hist_Ratio_JetPt_G_JetPt_Inclusive->Draw("same");

  RecJetMethod->DrawFlavourLegend(0.20,0.76,0.32,0.96, Flv_Legend_Index_Local++);
 
  gPad->SaveAs("Plots/PFJets/Ratio_JetPt_Flv_JetPt_Inclusive.png");
  gPad->SaveAs("Plots/PFJets/Ratio_JetPt_Flv_JetPt_Inclusive.pdf");


  // Canvas to draw the Jet Fractions as a function of pT (unknown flv)
  TCanvas *Canvas_Ratio_JetPt_FlvUn_JetPt_Inclusive = new TCanvas("Canvas_Ratio_JetPt_FlvUn_JetPt_Inclusive","Canvas_Ratio_JetPt_FlvUn_JetPt_Inclusive",800,800);
  Canvas_Ratio_JetPt_FlvUn_JetPt_Inclusive->cd(1);
  gPad->SetBottomMargin(0.2);

  TH1D *hist_PFJetFrac_JetPt_Un_Ghost = RecJetMethod->Get_Ghost_Hist("hist_PFJetFrac_JetPt_Un_Ghost","hist_PFJetFrac_JetPt_Un_Ghost",0.0,0.5,"PF Jet p_{T} (GeV/c)","PF Jet Fraction");
  hist_PFJetFrac_JetPt_Un_Ghost->Draw();

  hist_Ratio_JetPt_Un_JetPt_Inclusive->Draw("same");
  hist_Ratio_JetPt_Ze_JetPt_Inclusive->Draw("same");
  RecJetMethod->DrawFlavourLegendUn(0.20,0.76,0.32,0.96, Flv_Legend_Index_Local++);

  gPad->SaveAs("Plots/PFJets/Ratio_JetPt_FlvUn_JetPt_Inclusive.png");
  gPad->SaveAs("Plots/PFJets/Ratio_JetPt_FlvUn_JetPt_Inclusive.pdf");





  // =================== Inegrated Jet Fractions with different Jet pT cuts =======================================//
  
  const int NJetPtCut =4;
  const Double_t JetPtCut[NJetPtCut]={60.0,80.0,100.0,120.0};

  Double_t  JetPtCut_Flavour_Fraction[NJetPtCut][NFlvLocal+1]={0.0};

  //Array of graphs, each graph for one pT cut
  TGraph *graph_JetPtCut_JetFrac[NJetPtCut];
  
  // Canvas for Jet fractions as a function of Jet pt cut
  TCanvas *CanvasRecJetFractionJetPtCut = new TCanvas("CanvasRecJetFractionJetPtCut","CanvasRecJetFractionJetPtCut",800,800);;
  CanvasRecJetFractionJetPtCut->Divide(2,2);
  
  for(int i =0;i<NJetPtCut;i++){
    
    Int_t JetPtBinMin = hist_Master_JetPt_Flavour->GetXaxis()->FindBin(JetPtCut[i]);
    Int_t JetPtBinMax = hist_Master_JetPt_Flavour->GetXaxis()->GetNbins();// no overflow

    cout<<" Jet Pt Bin Min "<< JetPtBinMin <<" Jet Pt Bin Max "<< JetPtBinMax <<endl; 

    // projection on flv axis
    TH1 *hist_Master_JetPt_Flavour_ProjY = hist_Master_JetPt_Flavour->ProjectionY(Form("hist_Master_JetPt_Flavour_ProjY_%d",i),JetPtBinMin,JetPtBinMax);
    // integral for the denominator
    Double_t  Master_JetPt_Flavour_IntegralY = hist_Master_JetPt_Flavour_ProjY->Integral(0,hist_Master_JetPt_Flavour_ProjY->GetNbinsX());

    // These are the number of flavours
    Int_t NBinsHisto = hist_Master_JetPt_Flavour_ProjY->GetNbinsX();

    cout<<"NBinsHisto "<<NBinsHisto<<endl;
     
    cout<<endl;
    cout<<" Reco Jet Fractions with Jet Pt Cut "<< JetPtCut[i] <<endl;

    // u is at 1 
    for(int j = 1; j <=NBinsHisto; j++)
       {

	 // bin content should be checked
	 Double_t JetFraction = hist_Master_JetPt_Flavour_ProjY->GetBinContent(j)/Master_JetPt_Flavour_IntegralY;
	 JetPtCut_Flavour_Fraction[i][j] = JetFraction; 

	 cout<<"  flavour bin centre "<<hist_Master_JetPt_Flavour_ProjY->GetBinCenter(j)<<
	   " bin content "<<hist_Master_JetPt_Flavour_ProjY->GetBinContent(j)<<
           " Total Integral "<<Master_JetPt_Flavour_IntegralY<<
	   " fraction    "<<hist_Master_JetPt_Flavour_ProjY->GetBinContent(j)/Master_JetPt_Flavour_IntegralY<<endl;
	 
       }
    cout<<endl<<endl;
    
    
    //new TCanvas;
    //gPad->SetLogy(1);
    //hist_Master_JetPt_Flavour_ProjY->Draw();
     
    Double_t t_JetFrac[NFlvLocal]={JetPtCut_Flavour_Fraction[i][1], JetPtCut_Flavour_Fraction[i][2], JetPtCut_Flavour_Fraction[i][3],
					    JetPtCut_Flavour_Fraction[i][4],JetPtCut_Flavour_Fraction[i][5],JetPtCut_Flavour_Fraction[i][6]};
     
    graph_JetPtCut_JetFrac[i] = new TGraph(NFlvLocal, MuonJetType, t_JetFrac);
    graph_JetPtCut_JetFrac[i]->SetFillColor(kBlue);
    
    
    //cout<<MuonJetType[0]<<"  "<<MuonJetType[1]<<"  "<<MuonJetType[2]<<"  "<<MuonJetType[3]<<"  "<<MuonJetType[4]<<"  "<<MuonJetType[5]<<endl;
    //PrintGraph(graph_JetPtCut_JetFrac[i]);     
     
    char Ch_JetPtCutPlot[100];
    sprintf(Ch_JetPtCutPlot,"%1.2f",JetPtCut[i]);
    TString JetPtCutPlot = TString(Ch_JetPtCutPlot);
     
          
    CanvasRecJetFractionJetPtCut->cd(i+1);
    gPad->SetTopMargin(0.1);
    gPad->SetBottomMargin(0.2);
    h->Draw();
    graph_JetPtCut_JetFrac[i]->Draw("Bsame");
    sprintf(LatexChar,"Jet p_{T} > %.1f GeV/c",JetPtCut[i]);
    tb->DrawLatex(0.28,0.62,"PF Jets, no #mu req.");
    tb->DrawLatex(0.28,0.68,LatexChar);
    
     
  }//nJetPt Cut
  
  // save the Jet pT fraction with different Jet pT cuts
  CanvasRecJetFractionJetPtCut->SaveAs("Plots/PFJets/PFJetFrac_JetPtCut_All.png");
  CanvasRecJetFractionJetPtCut->SaveAs("Plots/PFJets/PFJetFrac_JetPtCut_All.pdf");
  
  cout<<endl<<endl;
    
  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  // ====================== 2D HISTO PF JET PT AND JET FLAVOUR ANALYSIS ENDS ===================== //
  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX //
  





  
  // =============================================================================== //
  // ====================== PF JET ANALYSIS ======================================= //
  // ============= 3D HISTO PF JET PT, MUON PT AND JET FLAVOUR ==================== //
  // =============================================================================== //

  
  const int NMuonPtCut =4;
  const Double_t MuonPtCut[NMuonPtCut]={5.0,12.5,16.0,20.0};
  //const Double_t MuonPtCut[NMuonPtCut]={5.0,7.5,9.5,12.5};
  //const Double_t MuonPtCut[NMuonPtCut]={5.0,7.0,9.0,12.0};

  
  cout<<endl<<endl<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<" ====================== PF JET ANALYSIS ======================================= "<<endl;
  cout<<" ============= 3D HISTO PF JET PT, MUON PT AND JET FLAVOUR ==================== "<<endl;
  cout<<" =============================================================================== "<<endl;
  cout<<endl<<endl<<endl;
  
  // Get the 3D histo of Jet Pt, Muon Pt and Flavour
  TH3D *hist_Master_JetPt_MuPt_Flavour=(TH3D*)file_in->Get("hist_Master_JetPt_MuPt_Flavour");
  //take a clone to use for muon probability
  TH3D *hist_Clone_JetPt_MuPt_Flavour=(TH3D*)hist_Master_JetPt_MuPt_Flavour->Clone();
  
  
  // Integrated 
  //Double_t  MuPtCut_Flavour_MuonFraction[NMuonPtCut][RecJetMethod->NFlavour+1]={0.0};

  Double_t MuPtCut_Inclusive_Integral[NMuonPtCut]={0.0};

  Double_t MuPtCut_Flavour_Integral[NMuonPtCut][NFlvLocal+1]={0.0};
  Double_t  MuPtCut_Flavour_Fraction[NMuonPtCut][NFlvLocal+1]={0.0};
  
  //Array of graphs
  //Graphs for Jet Fractions with different muon pT cuts
  TGraph *graph_MuonPtCut_JetFrac[NMuonPtCut];
  
  
  // Tagging Eff as a function of Jet Pt
  // Numerator is Jet with muon for flv x
  // Denominator is all Jets of that flv
  
  TH1 *hist_TaggingEff_ForU[NMuonPtCut];
  TH1 *hist_TaggingEff_ForD[NMuonPtCut];
  TH1 *hist_TaggingEff_ForS[NMuonPtCut];
  TH1 *hist_TaggingEff_ForC[NMuonPtCut];
  TH1 *hist_TaggingEff_ForB[NMuonPtCut];
  TH1 *hist_TaggingEff_ForG[NMuonPtCut];
  TH1 *hist_TaggingEff_ForUn[NMuonPtCut];
  TH1 *hist_TaggingEff_ForZe[NMuonPtCut];

  
  // Purity as a function of Jet Pt
  // Numerator is Jet with muon for flv x
  // Denominator is all Jets (inclusive) with muon

  TH1 *hist_Purity_ForU[NMuonPtCut];
  TH1 *hist_Purity_ForD[NMuonPtCut];
  TH1 *hist_Purity_ForS[NMuonPtCut];
  TH1 *hist_Purity_ForC[NMuonPtCut];
  TH1 *hist_Purity_ForB[NMuonPtCut];
  TH1 *hist_Purity_ForG[NMuonPtCut];
  TH1 *hist_Purity_ForUn[NMuonPtCut];
  TH1 *hist_Purity_ForZe[NMuonPtCut];
  TH1 *hist_Purity_ForNR[NMuonPtCut];


  // Jet fraction with muon / Jet fractions without any muon requirement
  TH1 *hist_Purity_DR_ForU[NMuonPtCut];
  TH1 *hist_Purity_DR_ForD[NMuonPtCut];
  TH1 *hist_Purity_DR_ForS[NMuonPtCut];
  TH1 *hist_Purity_DR_ForC[NMuonPtCut];
  TH1 *hist_Purity_DR_ForB[NMuonPtCut];
  TH1 *hist_Purity_DR_ForG[NMuonPtCut];

  TH1 *hist_Purity_DR_ForUn[NMuonPtCut];
  TH1 *hist_Purity_DR_ForZe[NMuonPtCut];
  TH1 *hist_Purity_DR_ForNR[NMuonPtCut];


  Int_t JetPtBinMin = hist_Master_JetPt_MuPt_Flavour->GetXaxis()->FindBin(RecJetPtMin); // Minimum pT cut for Rec Jets
  Int_t JetPtBinMax = hist_Master_JetPt_MuPt_Flavour->GetXaxis()->GetNbins(); // no overflow
  cout<<" Jet Pt Bin Min "<< JetPtBinMin <<" Jet Pt Bin Max "<< JetPtBinMax <<endl; 


  cout<<" FlavourBinMinForInc "<< FlavourBinMinForInc <<"  FlavourBinMaxForInc "<<FlavourBinMaxForInc <<endl;
  
  
  for(int i =0;i<NMuonPtCut;i++){
    
    Int_t MuonPtBinMin = hist_Master_JetPt_MuPt_Flavour->GetYaxis()->FindBin(MuonPtCut[i]);
    Int_t MuonPtBinMax = hist_Master_JetPt_MuPt_Flavour->GetYaxis()->GetNbins();
    
    cout<<" Muon Pt Bin Min "<< MuonPtBinMin <<" Muon Pt Bin Max "<< MuonPtBinMax <<endl; 
    
    //============================================================================================================//
    //====== Tagging = pT distribution of flv x Jets with muon / pT distribution of all  jets of flv x ===========//
    //=============================================================================================================//
    
    // Get the Jet Pt Distribution for different Flavours
    TH1 *hist_JetPt_WithMuon_Inclusive = hist_Master_JetPt_MuPt_Flavour->ProjectionX(Form("hist_JetPt_WithMuon_Inclusive_%d",i), MuonPtBinMin,MuonPtBinMax,FlavourBinMinForInc,FlavourBinMaxForInc);
    
    TH1 *hist_JetPt_WithMuon_U_Jets = hist_Master_JetPt_MuPt_Flavour->ProjectionX(Form("hist_JetPt_WithMuon_U_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForU,FlavourBinMaxForU);
    TH1 *hist_JetPt_WithMuon_D_Jets = hist_Master_JetPt_MuPt_Flavour->ProjectionX(Form("hist_JetPt_WithMuon_D_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForD,FlavourBinMaxForD);
    TH1 *hist_JetPt_WithMuon_S_Jets = hist_Master_JetPt_MuPt_Flavour->ProjectionX(Form("hist_JetPt_WithMuon_S_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForS,FlavourBinMaxForS);
    TH1 *hist_JetPt_WithMuon_C_Jets = hist_Master_JetPt_MuPt_Flavour->ProjectionX(Form("hist_JetPt_WithMuon_C_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForC,FlavourBinMaxForC);
    TH1 *hist_JetPt_WithMuon_B_Jets = hist_Master_JetPt_MuPt_Flavour->ProjectionX(Form("hist_JetPt_WithMuon_B_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForB,FlavourBinMaxForB);
    TH1 *hist_JetPt_WithMuon_G_Jets = hist_Master_JetPt_MuPt_Flavour->ProjectionX(Form("hist_JetPt_WithMuon_G_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForG,FlavourBinMaxForG);

    TH1 *hist_JetPt_WithMuon_Un_Jets = hist_Master_JetPt_MuPt_Flavour->ProjectionX(Form("hist_JetPt_WithMuon_Un_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForUn,FlavourBinMaxForUn);
    TH1 *hist_JetPt_WithMuon_Ze_Jets = hist_Master_JetPt_MuPt_Flavour->ProjectionX(Form("hist_JetPt_WithMuon_Ze_Jets_%d",i),MuonPtBinMin,MuonPtBinMax,FlavourBinMinForZe,FlavourBinMaxForZe);
        
    // Jets with muon
    //Asymmatric rebinning
    RecJetMethod->rebinAsymmetric(hist_JetPt_WithMuon_Inclusive, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
    RecJetMethod->rebinAsymmetric(hist_JetPt_WithMuon_U_Jets, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
    RecJetMethod->rebinAsymmetric(hist_JetPt_WithMuon_D_Jets, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
    RecJetMethod->rebinAsymmetric(hist_JetPt_WithMuon_S_Jets, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
    RecJetMethod->rebinAsymmetric(hist_JetPt_WithMuon_C_Jets, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
    RecJetMethod->rebinAsymmetric(hist_JetPt_WithMuon_B_Jets, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
    RecJetMethod->rebinAsymmetric(hist_JetPt_WithMuon_G_Jets, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
    RecJetMethod->rebinAsymmetric(hist_JetPt_WithMuon_Un_Jets, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);
    RecJetMethod->rebinAsymmetric(hist_JetPt_WithMuon_Ze_Jets, RecJetMethod->NBins_JetPt_VarSize-1, RecJetMethod->JetPtBinEdges);

    // Jet of flv x (with muon)/ All Jets of flv x
    hist_TaggingEff_ForU[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_U_Jets,hist_JetPt_U,1);
    hist_TaggingEff_ForD[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_D_Jets,hist_JetPt_D,1);
    hist_TaggingEff_ForS[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_S_Jets,hist_JetPt_S,1);
    hist_TaggingEff_ForC[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_C_Jets,hist_JetPt_C,1);
    hist_TaggingEff_ForB[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_B_Jets,hist_JetPt_B,1);
    hist_TaggingEff_ForG[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_G_Jets,hist_JetPt_G,1);

    hist_TaggingEff_ForUn[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_Un_Jets,hist_JetPt_Un,1);
    hist_TaggingEff_ForZe[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_Ze_Jets,hist_JetPt_Ze,1);

    // changing jets marker style, marker color etc.
    RecJetMethod->FlavouredHistogram(hist_TaggingEff_ForU[i], RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
    RecJetMethod->FlavouredHistogram(hist_TaggingEff_ForD[i], RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
    RecJetMethod->FlavouredHistogram(hist_TaggingEff_ForS[i], RecJetMethod->LineColorArray[3], RecJetMethod->MarkerColorArray[3], RecJetMethod->MarkerStyleArray[3],RecJetMethod->MarkerSizeArray[3]);
    RecJetMethod->FlavouredHistogram(hist_TaggingEff_ForC[i], RecJetMethod->LineColorArray[4], RecJetMethod->MarkerColorArray[4], RecJetMethod->MarkerStyleArray[4],RecJetMethod->MarkerSizeArray[4]);
    RecJetMethod->FlavouredHistogram(hist_TaggingEff_ForB[i], RecJetMethod->LineColorArray[5], RecJetMethod->MarkerColorArray[5], RecJetMethod->MarkerStyleArray[5],RecJetMethod->MarkerSizeArray[5]);
    RecJetMethod->FlavouredHistogram(hist_TaggingEff_ForG[i], RecJetMethod->LineColorArray[6], RecJetMethod->MarkerColorArray[6], RecJetMethod->MarkerStyleArray[6],RecJetMethod->MarkerSizeArray[6]);
    RecJetMethod->FlavouredHistogram(hist_TaggingEff_ForUn[i], RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
    RecJetMethod->FlavouredHistogram(hist_TaggingEff_ForZe[i], RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
    
    //============================================================================================================//
    //==== Purity = pT distribution of flv x Jets with muon / pT distribution of inclusive jets with muon =======//
    //=============================================================================================================//

    hist_Purity_ForU[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_U_Jets,hist_JetPt_WithMuon_Inclusive,1);
    hist_Purity_ForD[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_D_Jets,hist_JetPt_WithMuon_Inclusive,1);
    hist_Purity_ForS[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_S_Jets,hist_JetPt_WithMuon_Inclusive,1);
    hist_Purity_ForC[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_C_Jets,hist_JetPt_WithMuon_Inclusive,1);
    hist_Purity_ForB[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_B_Jets,hist_JetPt_WithMuon_Inclusive,1);
    hist_Purity_ForG[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_G_Jets,hist_JetPt_WithMuon_Inclusive,1);
    hist_Purity_ForUn[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_Un_Jets,hist_JetPt_WithMuon_Inclusive,1);
    hist_Purity_ForZe[i] = RecJetMethod->RatioHistogram(hist_JetPt_WithMuon_Ze_Jets,hist_JetPt_WithMuon_Inclusive,1);
    
    // changing the histogram marker style, marker color etc.
    RecJetMethod->FlavouredHistogram(hist_Purity_ForU[i], RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
    RecJetMethod->FlavouredHistogram(hist_Purity_ForD[i], RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
    RecJetMethod->FlavouredHistogram(hist_Purity_ForS[i], RecJetMethod->LineColorArray[3], RecJetMethod->MarkerColorArray[3], RecJetMethod->MarkerStyleArray[3],RecJetMethod->MarkerSizeArray[3]);
    RecJetMethod->FlavouredHistogram(hist_Purity_ForC[i], RecJetMethod->LineColorArray[4], RecJetMethod->MarkerColorArray[4], RecJetMethod->MarkerStyleArray[4],RecJetMethod->MarkerSizeArray[4]);
    RecJetMethod->FlavouredHistogram(hist_Purity_ForB[i], RecJetMethod->LineColorArray[5], RecJetMethod->MarkerColorArray[5], RecJetMethod->MarkerStyleArray[5],RecJetMethod->MarkerSizeArray[5]);
    RecJetMethod->FlavouredHistogram(hist_Purity_ForG[i], RecJetMethod->LineColorArray[6], RecJetMethod->MarkerColorArray[6], RecJetMethod->MarkerStyleArray[6],RecJetMethod->MarkerSizeArray[6]);
    RecJetMethod->FlavouredHistogram(hist_Purity_ForUn[i], RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
    RecJetMethod->FlavouredHistogram(hist_Purity_ForZe[i], RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
    
    //====================  Jet Fraction Double Ratios =========================================//
    //=========== Jet Fraction (with muon) /  Jet Fraction (no muon requirement) ==============//
    //============================================================================================//
    
    hist_Purity_DR_ForU[i] = RecJetMethod->RatioHistogram(hist_Purity_ForU[i],hist_Ratio_JetPt_U_JetPt_Inclusive,1);
    hist_Purity_DR_ForD[i] = RecJetMethod->RatioHistogram(hist_Purity_ForD[i],hist_Ratio_JetPt_D_JetPt_Inclusive,1);
    hist_Purity_DR_ForS[i] = RecJetMethod->RatioHistogram(hist_Purity_ForS[i],hist_Ratio_JetPt_S_JetPt_Inclusive,1);
    hist_Purity_DR_ForC[i] = RecJetMethod->RatioHistogram(hist_Purity_ForC[i],hist_Ratio_JetPt_C_JetPt_Inclusive,1);
    hist_Purity_DR_ForB[i] = RecJetMethod->RatioHistogram(hist_Purity_ForB[i],hist_Ratio_JetPt_B_JetPt_Inclusive,1);
    hist_Purity_DR_ForG[i] = RecJetMethod->RatioHistogram(hist_Purity_ForG[i],hist_Ratio_JetPt_G_JetPt_Inclusive,1);
    hist_Purity_DR_ForUn[i] = RecJetMethod->RatioHistogram(hist_Purity_ForUn[i],hist_Ratio_JetPt_Un_JetPt_Inclusive,1);
    hist_Purity_DR_ForZe[i] = RecJetMethod->RatioHistogram(hist_Purity_ForZe[i],hist_Ratio_JetPt_Ze_JetPt_Inclusive,1);
    
    RecJetMethod->FlavouredHistogram(hist_Purity_DR_ForU[i], RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
    RecJetMethod->FlavouredHistogram(hist_Purity_DR_ForD[i], RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
    RecJetMethod->FlavouredHistogram(hist_Purity_DR_ForS[i], RecJetMethod->LineColorArray[3], RecJetMethod->MarkerColorArray[3], RecJetMethod->MarkerStyleArray[3],RecJetMethod->MarkerSizeArray[3]);
    RecJetMethod->FlavouredHistogram(hist_Purity_DR_ForC[i], RecJetMethod->LineColorArray[4], RecJetMethod->MarkerColorArray[4], RecJetMethod->MarkerStyleArray[4],RecJetMethod->MarkerSizeArray[4]);
    RecJetMethod->FlavouredHistogram(hist_Purity_DR_ForB[i], RecJetMethod->LineColorArray[5], RecJetMethod->MarkerColorArray[5], RecJetMethod->MarkerStyleArray[5],RecJetMethod->MarkerSizeArray[5]);
    RecJetMethod->FlavouredHistogram(hist_Purity_DR_ForG[i], RecJetMethod->LineColorArray[6], RecJetMethod->MarkerColorArray[6], RecJetMethod->MarkerStyleArray[6],RecJetMethod->MarkerSizeArray[6]);

    RecJetMethod->FlavouredHistogram(hist_Purity_DR_ForUn[i], RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
    RecJetMethod->FlavouredHistogram(hist_Purity_DR_ForZe[i], RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
    
    //================================================================================================//
    //=========== Jet Fractions with muon, with several muon pT cuts ==================================//
    //============ Num = Number of jets (with a particular flavour) with muons above a particular muon pT ==//
    //============ Deno = Number of jets (all flavours) with muons above a particular muon pT =============//
    //================================================================================================//
    
    
    TH1 *hist_Master_JetPt_MuPt_Flavour_ProjZ = hist_Master_JetPt_MuPt_Flavour->ProjectionZ(Form("hist_Master_JetPt_MuPt_Flavour_ProjZ_%d",i),JetPtBinMin,JetPtBinMax,MuonPtBinMin,MuonPtBinMax);
    
    const Double_t  Master_JetPt_MuPt_Flavour_IntegralZ = hist_Master_JetPt_MuPt_Flavour_ProjZ->Integral(0,hist_Master_JetPt_MuPt_Flavour_ProjZ->GetNbinsX()+1);

    MuPtCut_Inclusive_Integral[i] = Master_JetPt_MuPt_Flavour_IntegralZ;

    
    Int_t NBinsHisto = hist_Master_JetPt_MuPt_Flavour_ProjZ->GetNbinsX();
    
    cout<<"NBinsHisto "<<NBinsHisto<<" inclusive integral "<<Master_JetPt_MuPt_Flavour_IntegralZ<<endl;

    
    //for(int j = 0; j <=NBinsHisto+1; j++) // to insure u =1, d =2 etc.
    //for(int j = 1; j <=NBinsHisto; j++) //putting more values in array than the array size
    //NFlvLocal=6
    for(int j = 1; j <=NFlvLocal; j++)
      {

	Double_t JetIntegral = hist_Master_JetPt_MuPt_Flavour_ProjZ->GetBinContent(j);
	Double_t JetFraction = JetIntegral/Master_JetPt_MuPt_Flavour_IntegralZ;
	

	MuPtCut_Flavour_Integral[i][j] = JetIntegral; 
	MuPtCut_Flavour_Fraction[i][j] = JetFraction; 

	cout<<" flavour bin centre "<<hist_Master_JetPt_MuPt_Flavour_ProjZ->GetBinCenter(j)<<
	  " bin content "<<hist_Master_JetPt_MuPt_Flavour_ProjZ->GetBinContent(j)<<
	  " fraction    "<<hist_Master_JetPt_MuPt_Flavour_ProjZ->GetBinContent(j)/Master_JetPt_MuPt_Flavour_IntegralZ<<endl;
	
      }
    cout<<endl;
     
    
    Double_t t_MuonJetFrac[NFlvLocal]={MuPtCut_Flavour_Fraction[i][1], MuPtCut_Flavour_Fraction[i][2], MuPtCut_Flavour_Fraction[i][3],
				      MuPtCut_Flavour_Fraction[i][4],MuPtCut_Flavour_Fraction[i][5],MuPtCut_Flavour_Fraction[i][6]};
    
    graph_MuonPtCut_JetFrac[i] = new TGraph (NFlvLocal, MuonJetType, t_MuonJetFrac);
     graph_MuonPtCut_JetFrac[i]->SetFillColorAlpha(kRed,0.6);


     //cout<<MuPtCut_Flavour_Integral[i][1]<<"  "<<MuPtCut_Flavour_Integral[i][2]<<"  "<<MuPtCut_Flavour_Integral[i][3]<<"  "<<MuPtCut_Flavour_Integral[i][4]<<"  "<<
     //MuPtCut_Flavour_Integral[i][5]<<"  "<<MuPtCut_Flavour_Integral[i][6]<<endl;
     
  }//muon pT cut
  cout<<endl<<endl;
  
          



  Double_t CanvasX = 800.0;
  Double_t CanvasY = 800.0;

  TCanvas *CanvasFractionMuonCut = new TCanvas("CanvasFractionMuonCut","CanvasFractionMuonCut",CanvasX,CanvasY);
  CanvasFractionMuonCut->Divide(2,2);
     
     
  TCanvas *CanvasBTaggingMuonCut = new TCanvas("CanvasBTaggingMuonCut","CanvasBTaggingMuonCut",CanvasX,CanvasY);
  CanvasBTaggingMuonCut->Divide(2,2);
     
     
  TCanvas *CanvasBPurityMuonCut = new TCanvas("CanvasBPurityMuonCut","CanvasBPurityMuonCut",CanvasX,CanvasY);
  CanvasBPurityMuonCut->Divide(2,2);
     
  TCanvas *CanvasBPurityUnMuonCut = new TCanvas("CanvasBPurityUnMuonCut","CanvasBPurityUnMuonCut",CanvasX,CanvasY);
  CanvasBPurityUnMuonCut->Divide(2,2);
     

  TCanvas *CanvasBPurityDRMuonCut = new TCanvas("CanvasBPurityDRMuonCut","CanvasBPurityDRMuonCut",CanvasX,CanvasY);
  CanvasBPurityDRMuonCut->Divide(2,2);
     
  
  //================ Drawing  Graphs for different muon pT cuts ===============//
  
  for(int i =0 ;i<NMuonPtCut; i++)
    {
      
      char Ch_MuPtCutPlot[100];
      sprintf(Ch_MuPtCutPlot,"%1.2f",MuonPtCut[i]);
      TString MuPtCutPlot = TString(Ch_MuPtCutPlot);
      
      CanvasFractionMuonCut->cd(i+1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      
      h->Draw();
      graph_JetFracGraph->Draw("Bsame");
      graph_MuonPtCut_JetFrac[i]->Draw("Bsame");  
      lgd_MuonJetFrac->Draw("same");
      
      sprintf(LatexChar,"#mu p_{T} > %.1f GeV/c",MuonPtCut[i]);
      tb->DrawLatex(0.28,0.68,LatexChar);
      
      
      CanvasFractionMuonCut->SaveAs("Plots/PFJets/JetFrac_MuPtCut_All.png");
      CanvasFractionMuonCut->SaveAs("Plots/PFJets/JetFrac_MuPtCut_All.pdf");
      
      
      CanvasBTaggingMuonCut->cd(i+1);
      gPad->SetLogy(1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      
      hist_TaggingEff_ForB[i]->GetYaxis()->SetRangeUser(0.001,1.2);
      hist_TaggingEff_ForB[i]->GetYaxis()->SetTitle("Tagging Efficiency");
      
      hist_TaggingEff_ForB[i]->Draw();
      hist_TaggingEff_ForU[i]->Draw("same");
      hist_TaggingEff_ForD[i]->Draw("same");
      hist_TaggingEff_ForS[i]->Draw("same");
      hist_TaggingEff_ForC[i]->Draw("same");
      hist_TaggingEff_ForG[i]->Draw("same");
      
      
      sprintf(LatexChar,"#mu p_{T} > %.1f GeV/c",MuonPtCut[i]);
      tb->DrawLatex(0.64,0.80,LatexChar);
      RecJetMethod->DrawFlavourLegend(0.20,0.87,0.32,0.995, Flv_Legend_Index_Local++);
      CanvasBTaggingMuonCut->SaveAs("Plots/PFJets/TaggingEff_ForB_MuPtCut_All.png");
      CanvasBTaggingMuonCut->SaveAs("Plots/PFJets/TaggingEff_ForB_MuPtCut_All.pdf");
      
      
      
      CanvasBPurityMuonCut->cd(i+1);
      gPad->SetLogy(1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      hist_Purity_ForB[i]->GetYaxis()->SetRangeUser(0.01,1.2);
      hist_Purity_ForB[i]->GetYaxis()->SetTitle(" Jet Fractions");
      hist_Purity_ForB[i]->GetXaxis()->SetLabelSize(0.06);
      
      hist_Purity_ForB[i]->GetXaxis()->SetTitle(" Jet p_{T} (GeV/c)");
      hist_Purity_ForB[i]->GetXaxis()->SetTitleOffset(1.4);
      hist_Purity_ForB[i]->GetXaxis()->SetTitleSize(0.06);
      
      hist_Purity_ForB[i]->Draw();
      
      hist_Purity_ForU[i]->Draw("same");
      hist_Purity_ForD[i]->Draw("same");
      hist_Purity_ForS[i]->Draw("same");
      hist_Purity_ForC[i]->Draw("same");
      hist_Purity_ForG[i]->Draw("same");


      
      sprintf(LatexChar,"#mu p_{T} > %.1f GeV/c",MuonPtCut[i]);
      tb->DrawLatex(0.64,0.84,LatexChar);
      RecJetMethod->DrawFlavourLegend(0.20,0.87,0.32,0.995, Flv_Legend_Index_Local++);
      

      CanvasBPurityMuonCut->SaveAs("Plots/PFJets/Purity_ForB_MuPtCut_All.png");
      CanvasBPurityMuonCut->SaveAs("Plots/PFJets/Purity_ForB_MuPtCut_All.pdf");

      



      CanvasBPurityUnMuonCut->cd(i+1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      
      hist_Purity_ForUn[i]->GetYaxis()->SetRangeUser(0.0,0.2);
      hist_Purity_ForUn[i]->GetYaxis()->SetTitle(" Fraction ");
      hist_Purity_ForUn[i]->GetXaxis()->SetTitle(" Jet p_{T} (GeV/c)");
      hist_Purity_ForUn[i]->GetXaxis()->SetTitleOffset(1.4);
      hist_Purity_ForUn[i]->GetXaxis()->SetTitleSize(0.06);
      hist_Purity_ForUn[i]->Draw();
      hist_Purity_ForZe[i]->Draw("same");
      sprintf(LatexChar,"#mu p_{T} > %.1f GeV/c",MuonPtCut[i]);
      tb->DrawLatex(0.64,0.84,LatexChar);
      RecJetMethod->DrawFlavourLegendUn(0.20,0.87,0.32,0.995, Flv_Legend_Index_Local++);
      CanvasBPurityUnMuonCut->SaveAs("Plots/PFJets/Purity_Un_MuPtCut_All.png");
      CanvasBPurityUnMuonCut->SaveAs("Plots/PFJets/Purity_Un_MuPtCut_All.pdf");
      
      
      CanvasBPurityDRMuonCut->cd(i+1);
      //gPad->SetLogy(1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      
      hist_Purity_DR_ForB[i]->GetYaxis()->SetRangeUser(0.01,50.0);
      hist_Purity_DR_ForB[i]->GetYaxis()->SetTitle(" Jet Frac. Double Ratio");

      hist_Purity_DR_ForB[i]->Draw();

      hist_Purity_DR_ForU[i]->Draw("same");
      hist_Purity_DR_ForD[i]->Draw("same");
      hist_Purity_DR_ForS[i]->Draw("same");
      hist_Purity_DR_ForC[i]->Draw("same");
      hist_Purity_DR_ForG[i]->Draw("same");
      

      
      sprintf(LatexChar,"#mu p_{T} > %.1f GeV/c",MuonPtCut[i]);
      tb->DrawLatex(0.64,0.84,LatexChar);
      RecJetMethod->DrawFlavourLegend(0.20,0.87,0.32,0.995, Flv_Legend_Index_Local++);
      
      
      CanvasBPurityDRMuonCut->SaveAs("Plots/PFJets/Purity_DR_ForB_MuPtCut_All.png");
      CanvasBPurityDRMuonCut->SaveAs("Plots/PFJets/Purity_DR_ForB_MuPtCut_All.pdf");
      
      

      
      
    }//muon pT cut
  
  
  cout<<" Muon Prob. "<<endl;
  
  
  //=========================================================================================================================//
  //=========================================================================================================================//
  //====================================  Muon Probabilities coming with different flavours =============================//
  //=======================================================================================================================//
  //=======================================================================================================================//

  // All reconstructed muons
  TH1D *hist_MuonPt=(TH1D*)file_in->Get("histMuonPt"); //checked and found not MC matched
  
  const int NBins_MuonPt_VarSize=13;
  const Double_t MuonPtBinEdges[NBins_MuonPt_VarSize]={1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 14.0, 18.0, 22.0, 30.0, 40.0, 60.0, 100.0};

  //hist_Clone_JetPt_MuPt_Flavour
  
  TH1 *hist_MuPt_WithJets_Inclusive = hist_Clone_JetPt_MuPt_Flavour->ProjectionY("hist_MuPt_WithJets_Inclusive",JetPtBinMin,JetPtBinMax,FlavourBinMinForInc,FlavourBinMaxForInc);

  TH1 *hist_MuPt_WithJets_U = hist_Clone_JetPt_MuPt_Flavour->ProjectionY("hist_MuPt_WithJets_U",JetPtBinMin,JetPtBinMax,FlavourBinMinForU,FlavourBinMaxForU);
  TH1 *hist_MuPt_WithJets_D = hist_Clone_JetPt_MuPt_Flavour->ProjectionY("hist_MuPt_WithJets_D",JetPtBinMin,JetPtBinMax,FlavourBinMinForD,FlavourBinMaxForD);
  TH1 *hist_MuPt_WithJets_S = hist_Clone_JetPt_MuPt_Flavour->ProjectionY("hist_MuPt_WithJets_S",JetPtBinMin,JetPtBinMax,FlavourBinMinForS,FlavourBinMaxForS);
  TH1 *hist_MuPt_WithJets_C = hist_Clone_JetPt_MuPt_Flavour->ProjectionY("hist_MuPt_WithJets_C",JetPtBinMin,JetPtBinMax,FlavourBinMinForC,FlavourBinMaxForC);
  TH1 *hist_MuPt_WithJets_B = hist_Clone_JetPt_MuPt_Flavour->ProjectionY("hist_MuPt_WithJets_B",JetPtBinMin,JetPtBinMax,FlavourBinMinForB,FlavourBinMaxForB);
  TH1 *hist_MuPt_WithJets_G = hist_Clone_JetPt_MuPt_Flavour->ProjectionY("hist_MuPt_WithJets_G",JetPtBinMin,JetPtBinMax,FlavourBinMinForG,FlavourBinMaxForG);

  TH1 *hist_MuPt_WithJets_Un = hist_Clone_JetPt_MuPt_Flavour->ProjectionY("hist_MuPt_WithJets_Un",JetPtBinMin,JetPtBinMax,FlavourBinMinForUn,FlavourBinMaxForUn);
  TH1 *hist_MuPt_WithJets_Ze = hist_Clone_JetPt_MuPt_Flavour->ProjectionY("hist_MuPt_WithJets_Ze",JetPtBinMin,JetPtBinMax,FlavourBinMinForZe,FlavourBinMaxForZe);







  
  //========== Asymmatic Re Binning muon pT with  jets ================================//
  
  //RecJetMethod->rebinAsymmetric(hist_MuonPt, NBins_MuonPt_VarSize-1, MuonPtBinEdges);
  //RecJetMethod->rebinAsymmetric(hist_MuPt_WithJets_Inclusive, NBins_MuonPt_VarSize-1, MuonPtBinEdges);
  //RecJetMethod->rebinAsymmetric(hist_MuPt_WithJets_U, NBins_MuonPt_VarSize-1, MuonPtBinEdges);
  //RecJetMethod->rebinAsymmetric(hist_MuPt_WithJets_D, NBins_MuonPt_VarSize-1, MuonPtBinEdges);
  //RecJetMethod->rebinAsymmetric(hist_MuPt_WithJets_S, NBins_MuonPt_VarSize-1, MuonPtBinEdges);
  //RecJetMethod->rebinAsymmetric(hist_MuPt_WithJets_C, NBins_MuonPt_VarSize-1, MuonPtBinEdges);
  //RecJetMethod->rebinAsymmetric(hist_MuPt_WithJets_B, NBins_MuonPt_VarSize-1, MuonPtBinEdges);
  //RecJetMethod->rebinAsymmetric(hist_MuPt_WithJets_G, NBins_MuonPt_VarSize-1, MuonPtBinEdges);
  //RecJetMethod->rebinAsymmetric(hist_MuPt_WithJets_Un, NBins_MuonPt_VarSize-1, MuonPtBinEdges);
  //RecJetMethod->rebinAsymmetric(hist_MuPt_WithJets_Ze, NBins_MuonPt_VarSize-1, MuonPtBinEdges);
  

  hist_MuPt_WithJets_Inclusive->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_MuPt_WithJets_U->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_MuPt_WithJets_D->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_MuPt_WithJets_S->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_MuPt_WithJets_C->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_MuPt_WithJets_B->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_MuPt_WithJets_G->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_MuPt_WithJets_Un->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  hist_MuPt_WithJets_Ze->GetYaxis()->SetTitle("dN/dp_{T} (GeV/c)^{-1}");
  

  // ratio of muon pt with flv x / all muon pt
  TH1D *hist_MuonRatio_Inclusive = RecJetMethod->RatioHistogram(hist_MuPt_WithJets_Inclusive,hist_MuonPt,1);
  TH1D *hist_MuonRatio_U = RecJetMethod->RatioHistogram(hist_MuPt_WithJets_U,hist_MuonPt,1);
  TH1D *hist_MuonRatio_D = RecJetMethod->RatioHistogram(hist_MuPt_WithJets_D,hist_MuonPt,1);
  TH1D *hist_MuonRatio_S = RecJetMethod->RatioHistogram(hist_MuPt_WithJets_S,hist_MuonPt,1);
  TH1D *hist_MuonRatio_C = RecJetMethod->RatioHistogram(hist_MuPt_WithJets_C,hist_MuonPt,1);
  TH1D *hist_MuonRatio_B = RecJetMethod->RatioHistogram(hist_MuPt_WithJets_B,hist_MuonPt,1);
  TH1D *hist_MuonRatio_G = RecJetMethod->RatioHistogram(hist_MuPt_WithJets_G,hist_MuonPt,1);

  TH1D *hist_MuonRatio_Un = RecJetMethod->RatioHistogram(hist_MuPt_WithJets_Un,hist_MuonPt,1);
  TH1D *hist_MuonRatio_Ze = RecJetMethod->RatioHistogram(hist_MuPt_WithJets_Ze,hist_MuonPt,1);


  

  RecJetMethod->FlavouredHistogram(hist_MuonRatio_Inclusive, RecJetMethod->LineColorArray[6], RecJetMethod->MarkerColorArray[6], 20,RecJetMethod->MarkerSizeArray[1]);
  RecJetMethod->FlavouredHistogram(hist_MuonRatio_U, RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
  RecJetMethod->FlavouredHistogram(hist_MuonRatio_D, RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
  RecJetMethod->FlavouredHistogram(hist_MuonRatio_S, RecJetMethod->LineColorArray[3], RecJetMethod->MarkerColorArray[3], RecJetMethod->MarkerStyleArray[3],RecJetMethod->MarkerSizeArray[3]);
  RecJetMethod->FlavouredHistogram(hist_MuonRatio_C, RecJetMethod->LineColorArray[4], RecJetMethod->MarkerColorArray[4], RecJetMethod->MarkerStyleArray[4],RecJetMethod->MarkerSizeArray[4]);
  RecJetMethod->FlavouredHistogram(hist_MuonRatio_B, RecJetMethod->LineColorArray[5], RecJetMethod->MarkerColorArray[5], RecJetMethod->MarkerStyleArray[5],RecJetMethod->MarkerSizeArray[5]);
  RecJetMethod->FlavouredHistogram(hist_MuonRatio_G, RecJetMethod->LineColorArray[6], RecJetMethod->MarkerColorArray[6], RecJetMethod->MarkerStyleArray[6],RecJetMethod->MarkerSizeArray[6]);

  RecJetMethod->FlavouredHistogram(hist_MuonRatio_Un, RecJetMethod->LineColorArray[1], RecJetMethod->MarkerColorArray[1], RecJetMethod->MarkerStyleArray[1],RecJetMethod->MarkerSizeArray[1]);
  RecJetMethod->FlavouredHistogram(hist_MuonRatio_Ze, RecJetMethod->LineColorArray[2], RecJetMethod->MarkerColorArray[2], RecJetMethod->MarkerStyleArray[2],RecJetMethod->MarkerSizeArray[2]);
  
  hist_MuonRatio_Inclusive->GetYaxis()->SetTitle(" #mu in  Jets (inclusive)/ all  #mu");
  hist_MuonRatio_U->GetYaxis()->SetTitle(" #mu in  Jets (u)/ all  #mu");
  hist_MuonRatio_D->GetYaxis()->SetTitle(" #mu in  Jets (d)/ all  #mu");
  hist_MuonRatio_S->GetYaxis()->SetTitle(" #mu in  Jets (s)/ all  #mu");
  hist_MuonRatio_C->GetYaxis()->SetTitle(" #mu in  Jets (c)/ all  #mu");
  hist_MuonRatio_B->GetYaxis()->SetTitle(" #mu in  Jets (b)/ all  #mu");
  hist_MuonRatio_G->GetYaxis()->SetTitle(" #mu in  Jets (g)/ all  #mu");

  hist_MuonRatio_Un->GetYaxis()->SetTitle(" #mu in  Jets (-999)/ all  #mu");
  hist_MuonRatio_Ze->GetYaxis()->SetTitle(" #mu in  Jets (0)/ all  #mu");




  
  //making arry for muon probability numrator to draw them in a loop
  TH1 *Array_hist_MuonRatioNum[7]={hist_MuPt_WithJets_Inclusive,hist_MuPt_WithJets_U,hist_MuPt_WithJets_D,hist_MuPt_WithJets_S,hist_MuPt_WithJets_C,hist_MuPt_WithJets_B,hist_MuPt_WithJets_G};
  //making arry for muon probability histograms to draw them in a loop
  TH1D *Array_hist_MuonRatio[7]={hist_MuonRatio_Inclusive,hist_MuonRatio_U,hist_MuonRatio_D,hist_MuonRatio_S,hist_MuonRatio_C,hist_MuonRatio_B,hist_MuonRatio_G};

  
  
  //for(int i =0;i<NMuonPtCut;i++){
       
    //Double_t Num_MuonFractionInclusive = hist_MuPt_WithJets_Inclusive->Integral(hist_MuPt_WithJets_Inclusive->GetXaxis()->FindBin(MuonPtCut[i]),hist_MuPt_WithJets_Inclusive->GetXaxis()->GetNbins()+1);
    //Double_t Num_MuonFraction_U = hist_MuPt_WithJets_U->Integral(hist_MuPt_WithJets_U->GetXaxis()->FindBin(MuonPtCut[i]),hist_MuPt_WithJets_U->GetXaxis()->GetNbins()+1);
    //Double_t Num_MuonFraction_D = hist_MuPt_WithJets_D->Integral(hist_MuPt_WithJets_D->GetXaxis()->FindBin(MuonPtCut[i]),hist_MuPt_WithJets_D->GetXaxis()->GetNbins()+1);
    //Double_t Num_MuonFraction_S = hist_MuPt_WithJets_S->Integral(hist_MuPt_WithJets_S->GetXaxis()->FindBin(MuonPtCut[i]),hist_MuPt_WithJets_S->GetXaxis()->GetNbins()+1);
    //Double_t Num_MuonFraction_C = hist_MuPt_WithJets_C->Integral(hist_MuPt_WithJets_C->GetXaxis()->FindBin(MuonPtCut[i]),hist_MuPt_WithJets_C->GetXaxis()->GetNbins()+1);
    //Double_t Num_MuonFraction_B = hist_MuPt_WithJets_B->Integral(hist_MuPt_WithJets_B->GetXaxis()->FindBin(MuonPtCut[i]),hist_MuPt_WithJets_B->GetXaxis()->GetNbins()+1);
    //Double_t Num_MuonFraction_G = hist_MuPt_WithJets_G->Integral(hist_MuPt_WithJets_G->GetXaxis()->FindBin(MuonPtCut[i]),hist_MuPt_WithJets_G->GetXaxis()->GetNbins()+1);
    //Double_t Num_MuonFraction_Un = hist_MuPt_WithJets_Un->Integral(hist_MuPt_WithJets_Un->GetXaxis()->FindBin(MuonPtCut[i]),hist_MuPt_WithJets_Un->GetXaxis()->GetNbins()+1);
    //Double_t Num_MuonFraction_Ze = hist_MuPt_WithJets_Ze->Integral(hist_MuPt_WithJets_Ze->GetXaxis()->FindBin(MuonPtCut[i]),hist_MuPt_WithJets_Ze->GetXaxis()->GetNbins()+1);
    ////Double_t Num_MuonFraction_NR = hist_MuPt_WithJets_NR->Integral(hist_MuPt_WithJets_NR->GetXaxis()->FindBin(MuonPtCut[i]),hist_MuPt_WithJets_NR->GetXaxis()->GetNbins()+1);
    
    
    
    //Double_t Deno_MuonFraction =     hist_MuonPt->Integral(hist_MuonPt->GetXaxis()->FindBin(MuonPtCut[i]),hist_MuonPt->GetXaxis()->GetNbins()+1);
       
       

    //Double_t MuonFractionInclusive =  Num_MuonFractionInclusive/Deno_MuonFraction;
       
    //Double_t MuonFraction_U =  Num_MuonFraction_U/Deno_MuonFraction;
    //Double_t MuonFraction_D =  Num_MuonFraction_D/Deno_MuonFraction;
    //Double_t MuonFraction_S =  Num_MuonFraction_S/Deno_MuonFraction;
    //Double_t MuonFraction_C =  Num_MuonFraction_C/Deno_MuonFraction;
    //Double_t MuonFraction_B =  Num_MuonFraction_B/Deno_MuonFraction;
    //Double_t MuonFraction_G =  Num_MuonFraction_G/Deno_MuonFraction;
    
    //Double_t MuonFraction_Un =  Num_MuonFraction_Un/Deno_MuonFraction;
    //Double_t MuonFraction_Ze =  Num_MuonFraction_Ze/Deno_MuonFraction;
    
    //MuPtCut_Flavour_MuonFraction[i][0]=MuonFractionInclusive;
    //MuPtCut_Flavour_MuonFraction[i][1]=MuonFraction_U;
    //MuPtCut_Flavour_MuonFraction[i][2]=MuonFraction_D;
    //MuPtCut_Flavour_MuonFraction[i][3]=MuonFraction_S;
    //MuPtCut_Flavour_MuonFraction[i][4]=MuonFraction_C;
    //MuPtCut_Flavour_MuonFraction[i][5]=MuonFraction_B;
    //MuPtCut_Flavour_MuonFraction[i][6]=MuonFraction_G;
  //}
   

  
  //Canvas muon probability coming with jets 
  TCanvas *CanvasRecMuonProbFlavour = new TCanvas("CanvasRecMuonProbFlavour","CanvasRecMuonProbFlavour",1800,1800);
  CanvasRecMuonProbFlavour->Divide(4,2);

  
  //=======================================================================================//
  //==================== ploting muon probabilities as a function of muon pT =============//
  //=====================================================================================//
  for(int i=0;i<7;i++){

    CanvasRecMuonProbFlavour->cd(i+1);
    gPad->SetTopMargin(0.1);
    gPad->SetBottomMargin(0.2);
    Array_hist_MuonRatio[i]->GetYaxis()->SetRangeUser(0.0,1.2);
    Array_hist_MuonRatio[i]->Draw();
    
  }
    
  CanvasRecMuonProbFlavour->cd(8);
  RecJetMethod->DrawFlavourLegendVertical(0.12,0.36,0.88,0.92, Flv_Legend_Index_Local_V++);
  
  
  CanvasRecMuonProbFlavour->SaveAs("Plots/PFJets/MuonsInJet_AllMuons_Ratio_Flavour_All.png");
  CanvasRecMuonProbFlavour->SaveAs("Plots/PFJets/MuonsInJet_AllMuons_Ratio_Flavour_All.pdf");


  //Canvas to plot the numerator and denomenator of muon probabilities
  TCanvas *CanvasRecMuonProbNum = new TCanvas("CanvasRecMuonProbNum","CanvasRecMuonProbNum",1800,1800);;
  CanvasRecMuonProbNum->Divide(4,2);

  for(int i=0;i<7;i++){
    
    CanvasRecMuonProbNum->cd(i+1);
    gPad->SetLogy(1);
    gPad->SetTopMargin(0.1);
    gPad->SetBottomMargin(0.2);

    if(i==0){RecJetMethod->FlavouredHistogram(Array_hist_MuonRatioNum[i],RecJetMethod->LineColorArray[6], RecJetMethod->MarkerColorArray[6], 20,RecJetMethod->MarkerSizeArray[6]);}
    else{RecJetMethod->FlavouredHistogram(Array_hist_MuonRatioNum[i],RecJetMethod->LineColorArray[i], RecJetMethod->MarkerColorArray[i], RecJetMethod->MarkerStyleArray[i],RecJetMethod->MarkerSizeArray[i]);}
    
    

    Array_hist_MuonRatioNum[i]->GetYaxis()->SetRangeUser(0.0001,50);

    Double_t MuonFrac = Array_hist_MuonRatioNum[i]->Integral()/ Array_hist_MuonRatioNum[0]->Integral();
    sprintf(LatexChar,"#mu frac %.4f",MuonFrac);

    
    Array_hist_MuonRatioNum[i]->Draw();
    tb->DrawLatex(0.64,0.84,LatexChar);
    
  }

 CanvasRecMuonProbNum->cd(8);
 RecJetMethod->DrawFlavourLegendVertical(0.12,0.36,0.88,0.92, Flv_Legend_Index_Local_V++);

 CanvasRecMuonProbNum->SaveAs("Plots/PFJets/MuonsInJetPtDiss_AllFlavour.png");
 CanvasRecMuonProbNum->SaveAs("Plots/PFJets/MuonsInJetPtDiss_AllFlavour.pdf");


  char OutTexFile[1000];
  sprintf(OutTexFile,"OutTexFile/RecTable/RecJetTable.tex");
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
  dataFile<<Str3<<"caption{ PF Jet Fraction in all Events}"<<endl;
  dataFile<<Str3<<"label{}"<<endl;
  
  dataFile<<Str3<<"begin{tabular}{|ccc|}"<<endl;
  dataFile<<Str1<<endl;
  
  dataFile<<"Type "<<" & Integral "<< " &Fraction"<<Str2<<endl;
  
  dataFile<<Str1<<endl;

  dataFile<<" Total "<<" &"<<setprecision(4)<<fixed <<TotalIntegralOfJets<<" &"<<setprecision(4)<<fixed <<TotalJetFraction<<Str2<<endl;
  dataFile<<"  u "<<" &"<<setprecision(4)<<fixed <<TotalIntegralOfUpJets<<" &"<<setprecision(4)<<fixed << UpJetFraction <<Str2<<endl;
  dataFile<<"  d "<<" &"<<setprecision(4)<<fixed <<TotalIntegralOfDownJets<<" &"<<setprecision(4)<<fixed << DownJetFraction <<Str2<<endl;
  dataFile<<"  s "<<" &"<<setprecision(4)<<fixed <<TotalIntegralOfStrangeJets<<" &"<<setprecision(4)<<fixed << StrangeJetFraction <<Str2<<endl;
  dataFile<<"  c "<<" &"<<setprecision(4)<<fixed <<TotalIntegralOfCharmJets<<" &"<<setprecision(4)<<fixed << CharmJetFraction <<Str2<<endl;
  dataFile<<"  b "<<" &"<<setprecision(4)<<fixed <<TotalIntegralOfBeautyJets<<" &"<<setprecision(4)<<fixed << BeautyJetFraction <<Str2<<endl;
  dataFile<<"  g "<<" &"<<setprecision(4)<<fixed <<TotalIntegralOfGluonJets<<" &"<<setprecision(4)<<fixed << GluonJetFraction <<Str2<<endl;
  
  dataFile<<Str1<<endl;
  dataFile<<Str3<<"end{tabular}"<<endl;
  dataFile<<Str3<<"end{center}"<<endl;
  dataFile<<Str3<<"end{table}"<<endl;
  dataFile<<endl<<endl<<endl;


  
  dataFile<<Str3<<"begin{table}[htb]"<<endl;
  dataFile<<Str3<<"begin{center}"<<endl;
  dataFile<<Str3<<"caption{ PF Jet Fraction with muons}"<<endl;
  dataFile<<Str3<<"label{}"<<endl;
  
  dataFile<<Str3<<"begin{tabular}{|ccc|}"<<endl;
  dataFile<<Str1<<endl;
  
  dataFile<<" Type "<<" &Integral "<<" &Fraction "<<Str2<<endl;

  dataFile<<Str1<<endl;
  
  dataFile<<" Total "<<" &"<<setprecision(4)<<fixed << TotalIntegralOfMuonJets <<" &"<<setprecision(4)<<fixed <<TotalMuonJetFraction<<Str2<<endl;
  dataFile<<"  u "<<" &"<<setprecision(4)<<fixed <<  TotalIntegralOfUpMuonJets <<" &"<<setprecision(4)<<fixed << UpMuonJetFraction <<Str2<<endl;
  dataFile<<"  d "<<" &"<<setprecision(4)<<fixed <<  TotalIntegralOfDownMuonJets <<" &"<<setprecision(4)<<fixed << DownMuonJetFraction <<Str2<<endl;
  dataFile<<"  s "<<" &"<<setprecision(4)<<fixed <<  TotalIntegralOfStrangeMuonJets <<" &"<<setprecision(4)<<fixed << StrangeMuonJetFraction <<Str2<<endl;
  dataFile<<"  c "<<" &"<<setprecision(4)<<fixed <<  TotalIntegralOfCharmMuonJets <<" &"<<setprecision(4)<<fixed << CharmMuonJetFraction <<Str2<<endl;
  dataFile<<"  b "<<" &"<<setprecision(4)<<fixed <<  TotalIntegralOfBeautyMuonJets<<" &"<<setprecision(4)<<fixed << BeautyMuonJetFraction <<Str2<<endl;
  dataFile<<"  g "<<" &"<<setprecision(4)<<fixed <<  TotalIntegralOfGluonMuonJets <<" &"<<setprecision(4)<<fixed << GluonMuonJetFraction <<Str2<<endl;
  
  dataFile<<Str1<<endl;
  dataFile<<Str3<<"end{tabular}"<<endl;
  dataFile<<Str3<<"end{center}"<<endl;
  dataFile<<Str3<<"end{table}"<<endl;
  dataFile<<endl<<endl<<endl;





  
  for(int i =0;i<NMuonPtCut;i++){
    
    dataFile<<Str3<<"begin{table}[htb]"<<endl;
    dataFile<<Str3<<"begin{center}"<<endl;
    dataFile<<Str3<<"caption{ PF Jet Fraction with muons above p$_{T}$ "<< setprecision(1)<<fixed << MuonPtCut[i] <<" GeV/c }"<<endl;
    dataFile<<Str3<<"label{}"<<endl;
    
    dataFile<<Str3<<"begin{tabular}{|ccc|}"<<endl;
    dataFile<<Str1<<endl;
    
    dataFile<<"Type"<<" &Integral "<<" &Fraction"<<Str2<<endl;
    
    dataFile<<Str1<<endl;
    

    dataFile<<" Total "<<" &"<<setprecision(4)<<fixed << MuPtCut_Inclusive_Integral[i] <<" &"<<setprecision(4)<<fixed <<TotalMuonJetFraction<<Str2<<endl;
    dataFile<<"  u "<<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Integral[i][1] <<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Fraction[i][1] <<Str2<<endl;
    dataFile<<"  d "<<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Integral[i][2] <<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Fraction[i][2] <<Str2<<endl;
    dataFile<<"  s "<<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Integral[i][3] <<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Fraction[i][3] <<Str2<<endl;
    dataFile<<"  c "<<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Integral[i][4] <<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Fraction[i][4] <<Str2<<endl;
    dataFile<<"  b "<<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Integral[i][5] <<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Fraction[i][5] <<Str2<<endl;
    dataFile<<"  g "<<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Integral[i][6] <<" &"<<setprecision(4)<<fixed << MuPtCut_Flavour_Fraction[i][6] <<Str2<<endl;
    
    dataFile<<Str1<<endl;
    dataFile<<Str3<<"end{tabular}"<<endl;
    dataFile<<Str3<<"end{center}"<<endl;
    dataFile<<Str3<<"end{table}"<<endl;
    dataFile<<endl<<endl<<endl;
    }
  cout<<endl<<endl;
  
  dataFile<<Str3<<"end{document}"<<endl<<endl;

  //===================================================================================//
  //============== write histograms inside the output file ============================//
  //==================================================================================//
  file_out->cd();

  // create a subdirectory "RecJetPlots" in this file
  TDirectory *cd_recplots = file_out->mkdir("RecJetPlots");
  cd_recplots->cd();    // make the "tof" directory the current directory

   
  hist_JetPt->Write();
  hist_JetEta->Write();
  hist_JetPhi->Write();

  file_out->cd();



  return;



}

