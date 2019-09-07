#include "MyMethod.h"



//object of mymethod class
MyMethod *MuPlotMethod = new MyMethod();

Double_t FractionInsideCut(TH1D *InHist, Double_t CutValueMin, Double_t CutValueMax);

void MakeMuonPlots(TFile *file_in)
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

  TLatex *tbl = new TLatex();
  tbl->SetNDC();
  tbl->SetTextColor(kRed);
  tbl->SetTextSize(0.04);


  
  char LatexChar[400];
 
    
  
  //=============================================================================================//
  //==================================== ALL RECONSTRUCTED MUONS ================================//
  //==================== Qulaity Cuts or (Quality Cuts + MC Matching if applied) ===============//
  //=============================================================================================//
  TH1D *hist_MuonPt=(TH1D*)file_in->Get("histMuonPt");
  TH1D *hist_MuonEta=(TH1D*)file_in->Get("histMuonEta");
  TH1D *hist_MuonPhi=(TH1D*)file_in->Get("histMuonPhi");

  hist_MuonPt->GetXaxis()->SetTitle("Muon Pt (GeV/c)");
  hist_MuonEta->GetXaxis()->SetTitle("Muon #eta");
  hist_MuonPhi->GetXaxis()->SetTitle("Muon #phi");

  MuPlotMethod->GlamorizeHistogram(hist_MuonPt,1,1,24,0.6);
  MuPlotMethod->GlamorizeHistogram(hist_MuonEta,1,1,24,0.6);
  MuPlotMethod->GlamorizeHistogram(hist_MuonPhi,1,1,24,0.6);
  
  
  
  //hist_MuonPt->SetStats(kFALSE);
  //hist_MuonEta->SetStats(kFALSE);
  //hist_MuonPhi->SetStats(kFALSE);



  //Reco muons inside the Jets
  // Get the 3D histo of Muon Eta, Muon Pt and Muon phi
  // This have variables where muon is inside Jet
  TH3D *hist_Master_MuEta_MuPt_MuPhi=(TH3D*)file_in->Get("hist_Master_MuEta_MuPt_MuPhi");

  TH1 *hist_MuonEta_InJet = hist_Master_MuEta_MuPt_MuPhi->ProjectionX("hist_MuonEta_InJet", 0,-1,0,-1);
  MuPlotMethod->GlamorizeHistogram(hist_MuonEta_InJet,4,4,28,0.6);

  TH1 *hist_MuonPt_InJet = hist_Master_MuEta_MuPt_MuPhi->ProjectionY("hist_MuonPt_InJet", 0,-1,0,-1);
  MuPlotMethod->GlamorizeHistogram(hist_MuonPt_InJet,4,4,28,0.6);

  TH1 *hist_MuonPhi_InJet = hist_Master_MuEta_MuPt_MuPhi->ProjectionZ("hist_MuonPhi_InJet", 0,-1,0,-1);
  MuPlotMethod->GlamorizeHistogram(hist_MuonPhi_InJet,4,4,28,0.6);
  
  

  //Gen Muon matched reco muons (reco muon variables are filled)
  TH1D *hist_MatchedMuonPt  =(TH1D*)file_in->Get("histMatchedMuonPt");
  TH1D *hist_MatchedMuonEta =(TH1D*)file_in->Get("histMatchedMuonEta");
  TH1D *hist_MatchedMuonPhi =(TH1D*)file_in->Get("histMatchedMuonPhi");

  hist_MatchedMuonPt->GetXaxis()->SetTitle("Muon Pt (GeV/c)");
  hist_MatchedMuonEta->GetXaxis()->SetTitle("Muon #eta");
  hist_MatchedMuonPhi->GetXaxis()->SetTitle("Muon #phi");
  
  MuPlotMethod->GlamorizeHistogram(hist_MatchedMuonPt,2,2,20,0.6);
  MuPlotMethod->GlamorizeHistogram(hist_MatchedMuonEta,2,2,20,0.6);
  MuPlotMethod->GlamorizeHistogram(hist_MatchedMuonPhi,2,2,20,0.6);

  
  //Ratios (Gen Muon matched reco muons)/All reco muons
  TH1D *hist_Ratio_GenMatchedRecMuons_RecMuons_Pt = MuPlotMethod->RatioHistogram(hist_MatchedMuonPt,hist_MuonPt,1);
  TH1D *hist_Ratio_GenMatchedRecMuons_RecMuons_Eta = MuPlotMethod->RatioHistogram(hist_MatchedMuonEta,hist_MuonEta,1);
  TH1D *hist_Ratio_GenMatchedRecMuons_RecMuons_Phi = MuPlotMethod->RatioHistogram(hist_MatchedMuonPhi,hist_MuonPhi,1);

  MuPlotMethod->GlamorizeHistogram(hist_Ratio_GenMatchedRecMuons_RecMuons_Pt,1,1,24,0.6);
  MuPlotMethod->GlamorizeHistogram(hist_Ratio_GenMatchedRecMuons_RecMuons_Eta,1,1,24,0.6);
  MuPlotMethod->GlamorizeHistogram(hist_Ratio_GenMatchedRecMuons_RecMuons_Phi,1,1,24,0.6);

  hist_Ratio_GenMatchedRecMuons_RecMuons_Pt->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_Ratio_GenMatchedRecMuons_RecMuons_Eta->GetYaxis()->SetRangeUser(0.0,1.2);
  hist_Ratio_GenMatchedRecMuons_RecMuons_Phi->GetYaxis()->SetRangeUser(0.0,1.2);
  
  hist_Ratio_GenMatchedRecMuons_RecMuons_Pt->GetYaxis()->SetTitle("Ratio");
  hist_Ratio_GenMatchedRecMuons_RecMuons_Eta->GetYaxis()->SetTitle("Ratio");
  hist_Ratio_GenMatchedRecMuons_RecMuons_Phi->GetYaxis()->SetTitle("Ratio");
  
  // make a canvas (1X3) coulams
  TCanvas *Canvas_AllRecMuon_GenMatchedRecMuons = new TCanvas("Canvas_AllRecMuon_GenMatchedRecMuons","Canvas_AllRecMuon_GenMatchedRecMuons",1200,800);
  Canvas_AllRecMuon_GenMatchedRecMuons->Divide(3,2);

  TLegend *lgd_AllRecMuon_GenMatchedRecMuons = MuPlotMethod->MyLegend(0.22,0.24,0.38,0.38);
  lgd_AllRecMuon_GenMatchedRecMuons->AddEntry(hist_MuonPt,"Muons","P");
  lgd_AllRecMuon_GenMatchedRecMuons->AddEntry(hist_MatchedMuonPt,"GenMatchedRecMuons","P");
  
  Canvas_AllRecMuon_GenMatchedRecMuons->cd(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  gPad->SetLogy(1);
  
  hist_MuonPt->Draw();
  hist_MatchedMuonPt->Draw("same");
  hist_MuonPt_InJet->Draw("same");
  lgd_AllRecMuon_GenMatchedRecMuons->Draw("same");
  
  sprintf(LatexChar,"Int. %0.3f",hist_MuonPt->Integral());
  tb->DrawLatex(0.58,0.7,LatexChar);

  sprintf(LatexChar,"Int. %0.3f",hist_MatchedMuonPt->Integral());
  tr->DrawLatex(0.58,0.65,LatexChar);

  
  sprintf(LatexChar,"Int. %0.3f",hist_MuonPt_InJet->Integral());
  tbl->DrawLatex(0.58,0.60,LatexChar);



  sprintf(LatexChar,"Ratio %0.3f",hist_MatchedMuonPt->Integral()/hist_MuonPt->Integral());
  tb->DrawLatex(0.58,0.55,LatexChar);

  
  sprintf(LatexChar,"Ratio %0.3f",hist_MuonPt_InJet->Integral()/hist_MuonPt->Integral());
  tbl->DrawLatex(0.58,0.50,LatexChar);


  
  Canvas_AllRecMuon_GenMatchedRecMuons->cd(2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_MuonEta->Draw();
  hist_MatchedMuonEta->Draw("same");
  hist_MuonEta_InJet->Draw("same");
  lgd_AllRecMuon_GenMatchedRecMuons->Draw("same");
  
  Canvas_AllRecMuon_GenMatchedRecMuons->cd(3);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_MuonPhi->GetYaxis()->SetRangeUser(0.0,200.0);
  hist_MuonPhi->Draw();
  hist_MatchedMuonPhi->Draw("same");
  hist_MuonPhi_InJet->Draw("same");
  lgd_AllRecMuon_GenMatchedRecMuons->Draw("same");


  
  Canvas_AllRecMuon_GenMatchedRecMuons->cd(4);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_Ratio_GenMatchedRecMuons_RecMuons_Pt->Draw();

  //sprintf(LatexChar,"Int. %0.3f",hist_Ratio_GenMatchedRecMuons_RecMuons_Pt->Integral());
  //tb->DrawLatex(0.58,0.6,LatexChar);
  
  
  Canvas_AllRecMuon_GenMatchedRecMuons->cd(5);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_Ratio_GenMatchedRecMuons_RecMuons_Eta->Draw();

  
  Canvas_AllRecMuon_GenMatchedRecMuons->cd(6);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_Ratio_GenMatchedRecMuons_RecMuons_Phi->Draw();

  Canvas_AllRecMuon_GenMatchedRecMuons->SaveAs("Plots/MuonPlots/AllRecMuon_GenMatchedRecMuons.pdf");
  Canvas_AllRecMuon_GenMatchedRecMuons->SaveAs("Plots/MuonPlots/AllRecMuon_GenMatchedRecMuons.png");



  //==================================================//
  //=============== Muon DR and DPt plots ============// 
  //==================================================//

  TH2D *hist_GenMuRecMuDRVsDPt=(TH2D*)file_in->Get("histGenMuRecMuDRVsDPt");

  TH1* hist_GenMuRecMuDR =  hist_GenMuRecMuDRVsDPt->ProjectionX("hist_GenMuRecMuDR",0,-1);

  TH1* hist_GenMuRecMuDPt =  hist_GenMuRecMuDRVsDPt->ProjectionY("hist_GenMuRecMuDPt",0,-1);

  TH1* hist_GenMuRecMuDPt_DRLT03 =  hist_GenMuRecMuDRVsDPt->ProjectionY("hist_GenMuRecMuDPt_DRLT03",hist_GenMuRecMuDRVsDPt->GetXaxis()->FindBin(0.0),hist_GenMuRecMuDRVsDPt->GetXaxis()->FindBin(0.3));

  
  TCanvas *Canvas_GenMuRecMuDRVsDPt = new TCanvas("Canvas_GenMuRecMuDRVsDPt","Canvas_GenMuRecMuDRVsDPt",1600,400);
  Canvas_GenMuRecMuDRVsDPt->Divide(4,1);//coulmn x row

  Canvas_GenMuRecMuDRVsDPt->cd(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  gPad->SetRightMargin(0.12);
  
  //gPad->SetLogz(1);
  //TH2D *h_z = new TH2D(*hist_GenMuRecMuDRVsDPt);
  //h_z->Draw("z");
  //hist_GenMuRecMuDRVsDPt->GetXaxis()->SetRangeUser(0.0,1.0);
  hist_GenMuRecMuDRVsDPt->GetYaxis()->SetRangeUser(0.0,1.0);
  hist_GenMuRecMuDRVsDPt->Draw("colz");

  Canvas_GenMuRecMuDRVsDPt->cd(2);
  gPad->SetLogy(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  MuPlotMethod->GlamorizeHistogram(hist_GenMuRecMuDR,1,1,24,0.6);
  hist_GenMuRecMuDR->Draw();

  
  Canvas_GenMuRecMuDRVsDPt->cd(3);
  gPad->SetLogy(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  MuPlotMethod->GlamorizeHistogram(hist_GenMuRecMuDPt,1,1,24,0.6);
  hist_GenMuRecMuDPt->Draw();


  Canvas_GenMuRecMuDRVsDPt->cd(4);
  gPad->SetLogy(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  MuPlotMethod->GlamorizeHistogram(hist_GenMuRecMuDPt_DRLT03,1,1,24,0.6);

  hist_GenMuRecMuDPt_DRLT03->Draw();
  tb->DrawLatex(0.58,0.6,"#Delta R < 0.3");

  Canvas_GenMuRecMuDRVsDPt->SaveAs("Plots/MuonPlots/GenMuRecMuDRVsDPt.pdf");
  Canvas_GenMuRecMuDRVsDPt->SaveAs("Plots/MuonPlots/GenMuRecMuDRVsDPt.png");




  //=====================================================================//
  //=============== Muon Efficiency (reco muons / Gen Muons) ============// 
  //=====================================================================//
  
  //========== Get the Gen Muon histograms ======================================//
  TH1D *hist_GenMuonPt=(TH1D*)file_in->Get("histGenMuonPt");
  //======== Making a clone to be used in the efficiency calculations ======//
  TH1D *hist_GenMuonPt_ForEff=(TH1D*)hist_GenMuonPt->Clone();
  TH1D *hist_GenMuonEta=(TH1D*)file_in->Get("histGenMuonEta");
  TH1D *hist_GenMuonPhi=(TH1D*)file_in->Get("histGenMuonPhi");



  MuPlotMethod->GlamorizeHistogram(hist_GenMuonPt,2,2,20,0.6);
  MuPlotMethod->GlamorizeHistogram(hist_GenMuonEta,2,2,20,0.6);
  MuPlotMethod->GlamorizeHistogram(hist_GenMuonPhi,2,2,20,0.6);



  //Ratios All reco muons / All gen muons
  
  TH1D *hist_Ratio_GenMuons_RecMuons_Pt = MuPlotMethod->RatioHistogram(hist_MuonPt,hist_GenMuonPt,1);
  TH1D *hist_Ratio_GenMuons_RecMuons_Eta = MuPlotMethod->RatioHistogram(hist_MuonEta,hist_GenMuonEta,1);
  TH1D *hist_Ratio_GenMuons_RecMuons_Phi = MuPlotMethod->RatioHistogram(hist_MuonPhi,hist_GenMuonPhi,1);

  MuPlotMethod->GlamorizeHistogram(hist_Ratio_GenMuons_RecMuons_Pt,1,1,24,0.6);
  MuPlotMethod->GlamorizeHistogram(hist_Ratio_GenMuons_RecMuons_Eta,1,1,24,0.6);
  MuPlotMethod->GlamorizeHistogram(hist_Ratio_GenMuons_RecMuons_Phi,1,1,24,0.6);

  hist_Ratio_GenMuons_RecMuons_Pt->GetYaxis()->SetRangeUser(0.0,1.6);
  hist_Ratio_GenMuons_RecMuons_Eta->GetYaxis()->SetRangeUser(0.0,1.6);
  hist_Ratio_GenMuons_RecMuons_Phi->GetYaxis()->SetRangeUser(0.0,1.6);
  
  hist_Ratio_GenMuons_RecMuons_Pt->GetYaxis()->SetTitle("Ratio");
  hist_Ratio_GenMuons_RecMuons_Eta->GetYaxis()->SetTitle("Ratio");
  hist_Ratio_GenMuons_RecMuons_Phi->GetYaxis()->SetTitle("Ratio");
  
  // make a canvas (1X3) coulams
  TCanvas *Canvas_AllRecMuon_GenMuons = new TCanvas("Canvas_AllRecMuon_GenMuons","Canvas_AllRecMuon_GenMuons",1200,800);
  Canvas_AllRecMuon_GenMuons->Divide(3,2);

  TLegend *lgd_AllRecMuon_GenMuons = MuPlotMethod->MyLegend(0.22,0.24,0.38,0.38);
  lgd_AllRecMuon_GenMuons->AddEntry(hist_MuonPt,"Muons","P");
  lgd_AllRecMuon_GenMuons->AddEntry(hist_GenMuonPt,"GenMuons","P");
  
  Canvas_AllRecMuon_GenMuons->cd(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  gPad->SetLogy(1);
  
  hist_MuonPt->Draw();
  hist_GenMuonPt->Draw("same");
  lgd_AllRecMuon_GenMuons->Draw("same");
  
  sprintf(LatexChar,"Int. %0.3f",hist_MuonPt->Integral());
  tb->DrawLatex(0.58,0.7,LatexChar);

  sprintf(LatexChar,"Int. %0.3f",hist_GenMuonPt->Integral());
  tr->DrawLatex(0.58,0.65,LatexChar);

  sprintf(LatexChar,"Ratio %0.3f",hist_MuonPt->Integral()/hist_GenMuonPt->Integral());
  tb->DrawLatex(0.58,0.60,LatexChar);



  
  Canvas_AllRecMuon_GenMuons->cd(2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_MuonEta->Draw();
  hist_GenMuonEta->Draw("same");
  lgd_AllRecMuon_GenMuons->Draw("same");
  
  Canvas_AllRecMuon_GenMuons->cd(3);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_MuonPhi->GetYaxis()->SetRangeUser(0.0,200.0);
  hist_MuonPhi->Draw();
  hist_GenMuonPhi->Draw("same");
  lgd_AllRecMuon_GenMuons->Draw("same");


  
  Canvas_AllRecMuon_GenMuons->cd(4);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_Ratio_GenMuons_RecMuons_Pt->Draw();

  //sprintf(LatexChar,"Int. %0.3f",hist_Ratio_GenMuons_RecMuons_Pt->Integral());
  //tb->DrawLatex(0.58,0.6,LatexChar);
  
  
  Canvas_AllRecMuon_GenMuons->cd(5);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_Ratio_GenMuons_RecMuons_Eta->Draw();

  
  Canvas_AllRecMuon_GenMuons->cd(6);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_Ratio_GenMuons_RecMuons_Phi->Draw();

  Canvas_AllRecMuon_GenMuons->SaveAs("Plots/MuonPlots/AllRecMuon_GenMuons.pdf");
  Canvas_AllRecMuon_GenMuons->SaveAs("Plots/MuonPlots/AllRecMuon_GenMuons.png");



  


  


  
  return;























  
  TLegend *lgd_GenMuonRecMuon = new TLegend(0.25,0.75,0.59,0.85,"","brNDC");
  lgd_GenMuonRecMuon->SetBorderSize(0);
  lgd_GenMuonRecMuon->SetTextFont(42);
  lgd_GenMuonRecMuon->SetLineColor(1);
  lgd_GenMuonRecMuon->SetLineStyle(1);
  lgd_GenMuonRecMuon->SetLineWidth(1);
  lgd_GenMuonRecMuon->SetFillColor(19);
  lgd_GenMuonRecMuon->SetFillStyle(0);

  
  hist_GenMuonPt_ForEff->SetLineColor(2);
  hist_GenMuonEta->SetLineColor(2);
  hist_GenMuonPhi->SetLineColor(2);

  hist_GenMuonPt_ForEff->SetMarkerColor(2);
  hist_GenMuonEta->SetMarkerColor(2);
  hist_GenMuonPhi->SetMarkerColor(2);


  hist_GenMuonPt_ForEff->SetMarkerStyle(21);
  hist_GenMuonEta->SetMarkerStyle(21);
  hist_GenMuonPhi->SetMarkerStyle(21);


  hist_GenMuonPt->SetMarkerStyle(24);
  hist_GenMuonEta->SetMarkerStyle(24);
  hist_MatchedMuonPhi->SetMarkerStyle(24);
    

  lgd_GenMuonRecMuon->AddEntry(hist_MatchedMuonPt,"Muons (matched)","p");
  lgd_GenMuonRecMuon->AddEntry(hist_GenMuonPt_ForEff,"gen Muons","p");


  //===============================================================//
  //========================= Calculate Ratios ===================//
  //=============================================================//

  TH1D *hist_Ratio_RecMuPt_GenMuPt = MuPlotMethod->RatioHistogram(hist_MatchedMuonPt,hist_GenMuonPt_ForEff,4);
  hist_Ratio_RecMuPt_GenMuPt->GetYaxis()->SetTitle("Rec/Gen");
  hist_Ratio_RecMuPt_GenMuPt->GetYaxis()->SetRangeUser(-1.0,3.0);

  TH1D *hist_Ratio_RecMuEta_GenMuEta = MuPlotMethod->RatioHistogram(hist_MatchedMuonEta,hist_GenMuonEta,4);
  hist_Ratio_RecMuEta_GenMuEta->GetYaxis()->SetTitle("Rec/Gen");
  hist_Ratio_RecMuEta_GenMuEta->GetYaxis()->SetRangeUser(-1.0,3.0);

  TH1D *hist_Ratio_RecMuPhi_GenMuPhi = MuPlotMethod->RatioHistogram(hist_MatchedMuonPhi,hist_GenMuonPhi,4);
  hist_Ratio_RecMuPhi_GenMuPhi->GetYaxis()->SetTitle("Rec/Gen");
  hist_Ratio_RecMuPhi_GenMuPhi->GetYaxis()->SetRangeUser(-1.0,3.0);
  
  
  //new TCanvas;
  //gPad->SetLogy(1);
  //hist_MuonPt->Draw();
  //new TCanvas;
  //hist_MuonEta->Draw();
  //new TCanvas;
  //hist_MuonPhi->Draw();
  
  //new TCanvas;
  //gPad->SetLogy(1);
  //hist_GenMuonPt->Draw();
  //hist_MuonPt->Draw("same");
  //hist_MuonPt->Draw();
  //lgd_GenMuonRecMuon->Draw("same");

  //gPad->SaveAs("Plots/MuonPlots/MuonPt.png");
  //gPad->SaveAs("Plots/MuonPlots/MuonPt.pdf");


  //new TCanvas;
  //hist_GenMuonEta->Draw();
  //hist_MuonEta->Draw("same");
  //lgd_GenMuonRecMuon->Draw("same");
  //gPad->SaveAs("Plots/MuonPlots/MuonEta.png");
  //gPad->SaveAs("Plots/MuonPlots/MuonEta.pdf");


  //new TCanvas;
  //hist_GenMuonPhi->Draw();
  //hist_MuonPhi->Draw("same");
  //lgd_GenMuonRecMuon->Draw("same");

  //gPad->SaveAs("Plots/MuonPlots/MuonPhi.png");
  //gPad->SaveAs("Plots/MuonPlots/MuonPhi.pdf");
  

  //=====================================================================================//
  //============================= MUONS ON SAME CANVAS AND THEIR RATIOS =================//
  //=====================================================================================//


  TCanvas *CanvasGenMuonRecMuon = new TCanvas("CanvasGenMuonRecMuon","CanvasGenMuonRecMuon",1000,1000);;
  CanvasGenMuonRecMuon->Divide(3,2);

  CanvasGenMuonRecMuon->cd(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  gPad->SetLogy(1);
  hist_GenMuonPt_ForEff->Draw();
  //hist_MuonPt->Draw("same");
  hist_MatchedMuonPt->Draw("same");
  lgd_GenMuonRecMuon->Draw("same");


  CanvasGenMuonRecMuon->cd(2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_GenMuonEta->Draw();
  //hist_MuonEta->Draw("same");
  hist_MatchedMuonEta->Draw("same");
  lgd_GenMuonRecMuon->Draw("same");


  CanvasGenMuonRecMuon->cd(3);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_GenMuonPhi->Draw();
  //hist_MuonPhi->Draw("same");
  hist_MatchedMuonPhi->Draw("same");
  lgd_GenMuonRecMuon->Draw("same");



  CanvasGenMuonRecMuon->cd(4);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_Ratio_RecMuPt_GenMuPt->Draw();


  CanvasGenMuonRecMuon->cd(5);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_Ratio_RecMuEta_GenMuEta->Draw();


  CanvasGenMuonRecMuon->cd(6);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hist_Ratio_RecMuPhi_GenMuPhi->Draw();




  CanvasGenMuonRecMuon->SaveAs("Plots/MuonPlots/Ratio_RecMu_GenMu.png");
  CanvasGenMuonRecMuon->SaveAs("Plots/MuonPlots/Ratio_RecMu_GenMu.pdf");
  

  
  //=====================================================================================================//
  //==================================== ALL RECONSTRUCTED MUONS WITH JETS =============================//
  //===================================================================================================//
  
  TH1D *hist_GenMuonPt_InsideGenJet=(TH1D*)file_in->Get("hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi_ProjY");
  TH1D *hist_GenMuonEta_InsideGenJet=(TH1D*)file_in->Get("hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi_ProjX");
  TH1D *hist_GenMuonPhi_InsideGenJet=(TH1D*)file_in->Get("hist_GenMaster_GenMuEta_GenMuPt_GenMuPhi_ProjZ");

  hist_GenMuonPt_InsideGenJet->SetLineColor(2);
  hist_GenMuonEta_InsideGenJet->SetLineColor(2);
  hist_GenMuonPhi_InsideGenJet->SetLineColor(2);
  
  hist_GenMuonPt_InsideGenJet->SetMarkerColor(2);
  hist_GenMuonEta_InsideGenJet->SetMarkerColor(2);
  hist_GenMuonPhi_InsideGenJet->SetMarkerColor(2);


  hist_GenMuonPt_InsideGenJet->SetMarkerStyle(24);
  hist_GenMuonEta_InsideGenJet->SetMarkerStyle(24);
  hist_GenMuonPhi_InsideGenJet->SetMarkerStyle(24);
  



  // reco muons with Jets
  
  TH1D *hist_MuonPt_InsideJet=(TH1D*)file_in->Get("hist_Master_MuEta_MuPt_MuPhi_ProjY");
  TH1D *hist_MuonEta_InsideJet=(TH1D*)file_in->Get("hist_Master_MuEta_MuPt_MuPhi_ProjX");
  TH1D *hist_MuonPhi_InsideJet=(TH1D*)file_in->Get("hist_Master_MuEta_MuPt_MuPhi_ProjZ");

  hist_MuonPt_InsideJet->SetMarkerStyle(24);
  hist_MuonEta_InsideJet->SetMarkerStyle(24);
  hist_MuonPhi_InsideJet->SetMarkerStyle(24);
  
  


  //===============================================================//
  //========================= Calculate Ratios ===================//
  //=============================================================//

  TH1D *hist_Ratio_RecMuPt_GenMuPt_InsideJet = MuPlotMethod->RatioHistogram(hist_MuonPt_InsideJet,hist_GenMuonPt_InsideGenJet,2);
  hist_Ratio_RecMuPt_GenMuPt_InsideJet->GetYaxis()->SetTitle("Rec/Gen");
  hist_Ratio_RecMuPt_GenMuPt_InsideJet->GetYaxis()->SetRangeUser(-1.0,3.0);

  TH1D *hist_Ratio_RecMuEta_GenMuEta_InsideJet = MuPlotMethod->RatioHistogram(hist_MuonEta_InsideJet,hist_GenMuonEta_InsideGenJet,2);
  hist_Ratio_RecMuEta_GenMuEta_InsideJet->GetYaxis()->SetTitle("Rec/Gen");
  hist_Ratio_RecMuEta_GenMuEta_InsideJet->GetYaxis()->SetRangeUser(-1.0,3.0);

  TH1D *hist_Ratio_RecMuPhi_GenMuPhi_InsideJet = MuPlotMethod->RatioHistogram(hist_MuonPhi_InsideJet,hist_GenMuonPhi_InsideGenJet,2);
  hist_Ratio_RecMuPhi_GenMuPhi_InsideJet->GetYaxis()->SetTitle("Rec/Gen");
  hist_Ratio_RecMuPhi_GenMuPhi_InsideJet->GetYaxis()->SetRangeUser(-1.0,3.0);
  
  
  //=====================================================================================//
  //============================= MUONS ON SAME CANVAS AND THEIR RATIOS =================//
  //=====================================================================================//


  TCanvas *CanvasGenMuonRecMuon_InsideJet = new TCanvas("CanvasGenMuonRecMuon_InsideJet","CanvasGenMuonRecMuon_InsideJet",1000,1000);;
  CanvasGenMuonRecMuon_InsideJet->Divide(3,2);

  CanvasGenMuonRecMuon_InsideJet->cd(1);
  gPad->SetLogy(1);
  hist_GenMuonPt_InsideGenJet->Draw();
  hist_MuonPt_InsideJet->Draw("same");
  lgd_GenMuonRecMuon->Draw("same");


  CanvasGenMuonRecMuon_InsideJet->cd(2);
  hist_MuonEta_InsideJet->Draw();
  hist_GenMuonEta_InsideGenJet->Draw("same");
  lgd_GenMuonRecMuon->Draw("same");


  CanvasGenMuonRecMuon_InsideJet->cd(3);
  hist_GenMuonPhi_InsideGenJet->Draw();
  hist_MuonPhi_InsideJet->Draw("same");
  lgd_GenMuonRecMuon->Draw("same");



  CanvasGenMuonRecMuon_InsideJet->cd(4);
  hist_Ratio_RecMuPt_GenMuPt_InsideJet->Draw();


  CanvasGenMuonRecMuon_InsideJet->cd(5);
  hist_Ratio_RecMuEta_GenMuEta_InsideJet->Draw();


  CanvasGenMuonRecMuon_InsideJet->cd(6);
  hist_Ratio_RecMuPhi_GenMuPhi_InsideJet->Draw();

  CanvasGenMuonRecMuon_InsideJet->SaveAs("Plots/MuonPlots/Ratio_RecMu_GenMu_InJets.png");
  CanvasGenMuonRecMuon_InsideJet->SaveAs("Plots/MuonPlots/Ratio_RecMu_GenMu_InJets.pdf");


  return;



  
}





void MakeMuonIDVarStudy(TFile *file_in)
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

  char LatexChar[400];
  
  //===================================================================================//
  //================== Get the histograms for MC Matched Muons ========================//
  //===================================================================================//


  const int NIDCuts = 15;
  TH1D *AMuIDCuts[NIDCuts];
  TH1D *ANGMuIDCuts[NIDCuts];
  
  //Array of Histogram Names
  const char NameMuIDCuts[NIDCuts][100]={"histMuonD0","histMuonDz","histMuonChi2NDF","histMuonInnerD0","histMuonInnerD0Err",
					 "histMuonInnerDz","histMuonInnerDzErr","histMuonInnerD0Norm","histMuonInnerDzNorm",
					 "histMuonTrkLayers","histMuonPixelLayers","histMuonPixelHits","histMuonMuHits",
					 "histMuonTrkQuality","histMuonMuStations"};


  //Array of Histogram Names For Unmatched Muons
  const char NameNGMuIDCuts[NIDCuts][100]={"histNGMuonD0","histNGMuonDz","histNGMuonChi2NDF","histNGMuonInnerD0","histNGMuonInnerD0Err",
					   "histNGMuonInnerDz","histNGMuonInnerDzErr","histNGMuonInnerD0Norm","histNGMuonInnerDzNorm",
					   "histNGMuonTrkLayers","histNGMuonPixelLayers","histNGMuonPixelHits","histNGMuonMuHits",
					   "histNGMuonTrkQuality","histNGMuonMuStations"};


  //Array of Names For saving the plots
  const char PlotNamesMuIDCuts[NIDCuts][100]={"MuonD0","MuonDz","MuonChi2NDF","MuonInnerD0","MuonInnerD0Err",
					   "MuonInnerDz","MuonInnerDzErr","MuonInnerD0Norm","MuonInnerDzNorm",
					   "MuonTrkLayers","MuonPixelLayers","MuonPixelHits","MuonMuHits",
					   "MuonTrkQuality","MuonMuStations"};



  
  
  
  //Int_t TightMuonIDCuts(Int_t isGlobal, Int_t isTracker, float muEta, float muChi2NDF, float muInnerD0, float muInnerDz, Int_t muMuonHits, Int_t muStations, Int_t muTrkLayers, Int_t muPixelHits){
  //Int_t SelectMuon =0;
  //if( isGlobal==1 && isTracker==1 && TMath::Abs(muEta) < 2.4 &&  (muChi2NDF != -99 && muChi2NDF < 10) && TMath::Abs(muInnerD0) < 0.2 && TMath::Abs(muInnerDz) < 0.5
  //  && muMuonHits > 0 && muStations > 1 && muTrkLayers > 5 && muPixelHits > 0){SelectMuon =1;}
  //return SelectMuon;
  //}

  //Mu ID Cut Values (edges included)
  Double_t MuIDCutValueMin[NIDCuts]={0.0};
  Double_t MuIDCutValueMax[NIDCuts]={0.0}; 

  //Muon Dz (cut is abs(d0)<0.2)
   MuIDCutValueMin[0]=-0.2;
   MuIDCutValueMax[0]=0.2;

  
  //Muon D0 (cut is abs(dz)<0.5)
   MuIDCutValueMin[1]=-0.5;
   MuIDCutValueMax[1]=0.5;
 


  //Muon Chi2ByNDF (cut is Chi2NDF < 10)
   MuIDCutValueMin[2]=0.0;
   MuIDCutValueMax[2]=10.0;

  
  //Muon Inner D0 (cut is abs(d0)<0.2)
   MuIDCutValueMin[3]=-0.2;
   MuIDCutValueMax[3]=0.2;
  

  //Muon Inner D0 Error(no cut)
   MuIDCutValueMin[4]=-999;
   MuIDCutValueMax[4]=999;

  
  //Muon Inner Dz (cut is abs(dz)<0.5)
   MuIDCutValueMin[5]=-0.5;
   MuIDCutValueMax[5]=0.5;


  //Muon Inner Dz Error(no cut)
   MuIDCutValueMin[6]=-999;
   MuIDCutValueMax[6]=999;
  

  //Muon Inner D0 Norm (we use no cut for this)
   MuIDCutValueMin[7]=-3.0;
   MuIDCutValueMax[7]=3.0;
  

  //Muon Inner Dz Norm (we use no cut for this)
   MuIDCutValueMin[8]=-3.0;
   MuIDCutValueMax[8]=3.0;
  
  //Muon Track Layers (cut is > 5)
   MuIDCutValueMin[9]=6;
   MuIDCutValueMax[9]=18;

  

  //Muon Pixel Layers (We use no cut for this)
   MuIDCutValueMin[10]=-999;
   MuIDCutValueMax[10]=999;

  

  //Muon Pixel Hits (cut is PixelHits >0)
   MuIDCutValueMin[11]=1;
   MuIDCutValueMax[11]=10;

  
  //Muon MuHits (cut is MuHits >0)
   MuIDCutValueMin[12]=1;
   MuIDCutValueMax[12]=49;

  //Muon Trk Quality (We use no cut for this)
   MuIDCutValueMin[13]=-999;
   MuIDCutValueMax[13]=999;
  
  //MuonMuStations (cuts is MuStations >1) 
   MuIDCutValueMin[14]=2;
   MuIDCutValueMax[14]=5;

  
  //Define graphs to plot lines on the plots for the cut values
  TGraph *line1_MuIDCut[NIDCuts];
  TGraph *line2_MuIDCut[NIDCuts];

  
  TLegend *lgd_MuIDVar[NIDCuts];

  
  for(int i=0;i<NIDCuts;i++)
    {
      cout<<"Getting histo "<<NameMuIDCuts[i]<<endl;
      AMuIDCuts[i]=(TH1D*)file_in->Get(NameMuIDCuts[i]);
      //Scalling histograms with their intgrals
      MuPlotMethod->ScaleHistByItsIntegral(AMuIDCuts[i]);
      AMuIDCuts[i]->SetMarkerStyle(20);
      AMuIDCuts[i]->SetMarkerColor(2);
      AMuIDCuts[i]->SetLineColor(2);
    
      cout<<"Getting histo NG"<<NameNGMuIDCuts[i]<<endl<<endl;
      
      ANGMuIDCuts[i]=(TH1D*)file_in->Get(NameNGMuIDCuts[i]);
      //Scalling histograms with their intgrals
      MuPlotMethod->ScaleHistByItsIntegral(ANGMuIDCuts[i]);
      ANGMuIDCuts[i]->SetMarkerStyle(24);
      ANGMuIDCuts[i]->SetMarkerColor(1);
      ANGMuIDCuts[i]->SetLineColor(1);


      lgd_MuIDVar[i] = MuPlotMethod->MyLegend(0.657,0.772,0.996,0.871);
      if(i==9){lgd_MuIDVar[i] = MuPlotMethod->MyLegend(0.185,0.770,0.525,0.870);}
      lgd_MuIDVar[i]->SetTextSize(0.04);
      lgd_MuIDVar[i]->AddEntry(AMuIDCuts[i],"Matched","P");
      lgd_MuIDVar[i]->AddEntry(ANGMuIDCuts[i],"NoMatch","P");


      line1_MuIDCut[i]= new TGraph(2);
      line1_MuIDCut[i]->SetLineColor(2);
      line1_MuIDCut[i]->SetPoint(0,MuIDCutValueMin[i],0);
      line1_MuIDCut[i]->SetPoint(1,MuIDCutValueMin[i],TMath::Max((AMuIDCuts[i]->GetMaximum()),(ANGMuIDCuts[i]->GetMaximum())));

      line2_MuIDCut[i] = new TGraph(2);
      line2_MuIDCut[i]->SetLineColor(2);
      line2_MuIDCut[i]->SetPoint(0,MuIDCutValueMax[i],0);
      line2_MuIDCut[i]->SetPoint(1,MuIDCutValueMax[i],TMath::Max((AMuIDCuts[i]->GetMaximum()),(ANGMuIDCuts[i]->GetMaximum())));

      Double_t Frac_MuID = FractionInsideCut(AMuIDCuts[i],MuIDCutValueMin[i],MuIDCutValueMax[i]);
      Double_t Frac_NGMuID = FractionInsideCut(ANGMuIDCuts[i],MuIDCutValueMin[i],MuIDCutValueMax[i]);


      

      
      new TCanvas;
      if(i==3 || i==5)gPad->SetLogy(1);
      AMuIDCuts[i]->Draw();
      ANGMuIDCuts[i]->Draw("same");
      line1_MuIDCut[i]->Draw("lsame");
      line2_MuIDCut[i]->Draw("lsame");
      lgd_MuIDVar[i]->Draw("Psame");

      sprintf(LatexChar,"In Frac. %0.3f",Frac_MuID);
      
      if(i==9){tr->DrawLatex(0.18,0.7,LatexChar);}
      else{tr->DrawLatex(0.70,0.7,LatexChar);}

      sprintf(LatexChar,"In Frac. %0.3f",Frac_NGMuID);
      if(i==9){tb->DrawLatex(0.18,0.65,LatexChar);}
      else{tb->DrawLatex(0.70,0.65,LatexChar);}
      
      
      
      gPad->SaveAs(Form("Plots/MuonPlots/IDPlots/%s.pdf",PlotNamesMuIDCuts[i]));
      gPad->SaveAs(Form("Plots/MuonPlots/IDPlots/%s.png",PlotNamesMuIDCuts[i]));


      
    }




}


Double_t FractionInsideCut(TH1D *InHist, Double_t CutValueMin, Double_t CutValueMax)
{
  

  Int_t BinMin = InHist->GetXaxis()->FindBin(CutValueMin);
  Int_t BinMax = InHist->GetXaxis()->FindBin(CutValueMax);

  Double_t Deno = InHist->Integral();
  Double_t Num = InHist->Integral(BinMin,BinMax);
  

  //cout<<" underflow "<<
  cout<<" Bin Min "<<BinMin<<" Bin Max  "<<BinMax<<endl;
  cout<<" Deno "<<Deno<<" Num "<<Num<<endl;
  
  Double_t Frac = Num/Deno; 
  
  return Frac;
  
}
