#include "MyMethod.h"

void MakeEventHistos(TFile *file_in, TFile *file_out)
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

  MyMethod *EventHistMethod = new MyMethod();


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
  Int_t PRINT_BIN_CENTRE =0;
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
  
  EventHistMethod->GlamorizeHistogram(hist_EvtVtxX,1,1,20,0.6);
  EventHistMethod->GlamorizeHistogram(hist_EvtVtxY,1,1,20,0.6);
  EventHistMethod->GlamorizeHistogram(hist_EvtVtxZ,1,1,20,0.6);
  EventHistMethod->GlamorizeHistogram(hist_Centrality,1,1,20,0.6);

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

  Canvas_EvtVtx_Centrality->SaveAs("Plots/EventPlots/EventHisto.pdf");
  Canvas_EvtVtx_Centrality->SaveAs("Plots/EventPlots/EventHisto.png");


  file_out->cd();
  
  hist_EvtVtxX->Write();
  hist_EvtVtxY->Write();
  hist_EvtVtxZ->Write();
  hist_Centrality->Write();

}
