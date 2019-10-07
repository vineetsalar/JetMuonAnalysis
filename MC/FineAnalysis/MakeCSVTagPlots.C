//comment to test git

#include "MyMethod.h"





void MakeCSVTagPlots(TFile *file_in,TFile *file_out)
{

  
  TLatex *tb = new TLatex();
  tb->SetNDC();
  tb->SetTextColor(kBlack);
  tb->SetTextSize(0.04);
  
  
  TLatex *tr = new TLatex();
  tr->SetNDC();
  tr->SetTextColor(kRed);
  tr->SetTextSize(0.04);

  Int_t Flv_Legend_Index_Local_V=1500;
  //object of mymethod class
  MyMethod *CSVTagMethod = new MyMethod();

  

  /***********************************************************************************/
  /***********************************************************************************/
  /***********************************************************************************/
  //CSV V2 Tagger Plots
  // PYTHIA6 DiJet Histo
  // MUON JET Pt Rel Plots
  /***********************************************************************************/
  /***********************************************************************************/
  /***********************************************************************************/
  
  Double_t CSVWorkingPoint = 0.9;
  //Line to draw at 0.9
  TGraph *line1_csv;
  line1_csv= new TGraph(2);
  line1_csv->SetLineColor(1);

  // 1D Histogram of Jet CSV
  TH1D *hist_JetCSV=(TH1D*)file_in->Get("histJetCSV");
  hist_JetCSV->GetYaxis()->SetTitle("Entries");
  hist_JetCSV->GetXaxis()->SetTitle("CSV v2");

  Double_t Intg_JetCSV = hist_JetCSV->Integral();
  hist_JetCSV->Scale(1.0/Intg_JetCSV);
  
  
  line1_csv->SetPoint(0,CSVWorkingPoint,0);
  line1_csv->SetPoint(1,CSVWorkingPoint,hist_JetCSV->GetMaximum());

  //1D Histogram of Jet CSV for muon Jets
  TH1D *hist_MuonJetCSV=(TH1D*)file_in->Get("histMuonJetCSV");
  hist_MuonJetCSV->GetYaxis()->SetTitle("Entries");
  hist_MuonJetCSV->GetXaxis()->SetTitle("CSV v2");

  Double_t Intg_MuonJetCSV = hist_MuonJetCSV->Integral();
  hist_MuonJetCSV->Scale(1.0/Intg_MuonJetCSV);
  
  // Get the bins for CSV working point
  Int_t Bin_CSV_Min = hist_JetCSV->GetXaxis()->FindBin(0.0);
  Int_t Bin_CSV_WorkingPoint = hist_JetCSV->GetXaxis()->FindBin(CSVWorkingPoint);
  Int_t Bin_CSV_Max = hist_JetCSV->GetXaxis()->FindBin(1.0);


  cout<<" hist_JetCSV Bin_CSV_Min "<< Bin_CSV_Min <<" Bin_CSV_WorkingPoint " << Bin_CSV_WorkingPoint <<" Bin_CSV_Max "<<Bin_CSV_Max<<endl;

  //Fraction of Jets above CSVV2 0.9
  Double_t Number_Jets_CSV_Veto = hist_JetCSV->Integral(Bin_CSV_Min,Bin_CSV_WorkingPoint-1);    
  Double_t Number_Jets_CSV_Tag = hist_JetCSV->Integral(Bin_CSV_WorkingPoint,Bin_CSV_Max);
  Double_t Jet_CSV_Tag_Fraction = Number_Jets_CSV_Tag/(Number_Jets_CSV_Tag+Number_Jets_CSV_Veto) ;

  cout<<endl<<endl;

  cout<<" CSV  Jet "<<Number_Jets_CSV_Tag<<"   "<<Number_Jets_CSV_Veto<<"  Frac --> "<<Jet_CSV_Tag_Fraction<<endl;

  //Fraction of Jets above CSVV2 0.9 Muon Jets
  Double_t Number_MuonJets_CSV_Tag = hist_MuonJetCSV->Integral(Bin_CSV_WorkingPoint,Bin_CSV_Max);
  Double_t Number_MuonJets_CSV_Veto = hist_MuonJetCSV->Integral(Bin_CSV_Min,Bin_CSV_WorkingPoint-1);
  Double_t MuonJet_CSV_Tag_Fraction = Number_MuonJets_CSV_Tag/(Number_MuonJets_CSV_Tag+Number_MuonJets_CSV_Veto) ;

  cout<<" CSV Muon Jet "<<Number_MuonJets_CSV_Tag<<"   "<<Number_MuonJets_CSV_Veto<<"  Frac --> "<<MuonJet_CSV_Tag_Fraction<<endl;
  cout<<endl<<endl;
  
  // 1D Histogram of Muon pT Relative
  TH1D *hist_MuonPtRel=(TH1D*)file_in->Get("histMuonPtRel");
  hist_MuonPtRel->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");
  hist_MuonPtRel->SetStats(kFALSE);
  hist_JetCSV->SetStats(kFALSE);

  //getting it from MyMethod class
  CSVTagMethod->FlavouredHistogram(hist_JetCSV,1,1,20,0.6);
  CSVTagMethod->FlavouredHistogram(hist_MuonJetCSV,2,2,20,0.6);
  CSVTagMethod->FlavouredHistogram(hist_MuonPtRel,2,2,20,0.6);

  // Drawing Jet CSV and Muon pT relative
  TCanvas *Canvas_JetCSV_MuonPtRel = new TCanvas("Canvas_JetCSV_MuonPtRel","Canvas_JetCSV_MuonPtRel",800,400);
  Canvas_JetCSV_MuonPtRel->Divide(2,1);
  Canvas_JetCSV_MuonPtRel->cd(1);
  
  
  TLegend *lgd_JetCSV_MuonPtRel = CSVTagMethod->MyLegend(0.30,0.34,0.46,0.48);
  lgd_JetCSV_MuonPtRel->AddEntry(hist_JetCSV,"Jets","P");
  lgd_JetCSV_MuonPtRel->AddEntry(hist_MuonJetCSV,"Muon Jets","P");
  
  gPad->SetLogy(1);
  hist_JetCSV->Draw();
  hist_MuonJetCSV->Draw("same");
  line1_csv->Draw("same");
  lgd_JetCSV_MuonPtRel->Draw("same");
  
  tb->DrawLatex(0.3,0.80,Form("Jets Veto %0.2f",Number_Jets_CSV_Veto));
  tb->DrawLatex(0.3,0.76,Form("Jets Tag %0.2f (%0.2f)",Number_Jets_CSV_Tag,Jet_CSV_Tag_Fraction));
  
  tr->DrawLatex(0.3,0.30,Form("MuonJets Veto %0.2f",Number_MuonJets_CSV_Veto));
  tr->DrawLatex(0.3,0.26,Form("MuonJets Tag %0.2f (%0.2f)",Number_MuonJets_CSV_Tag,MuonJet_CSV_Tag_Fraction));
  
  Canvas_JetCSV_MuonPtRel->cd(2);
  //gPad->SetLogy(1);
  hist_MuonPtRel->Draw();
  
  
  Canvas_JetCSV_MuonPtRel->SaveAs("Plots/CSVPlots/JetCSV_MuonPtRel.pdf");
  Canvas_JetCSV_MuonPtRel->SaveAs("Plots/CSVPlots/JetCSV_MuonPtRel.png");


  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX//
  //======================= Jets CSV and Muon Pt Relative drawn =======================//
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX//

  
  // muon pt relative for CSV tag Jets
  TH1D *hist_MuonPtRelCSVTag=(TH1D*)file_in->Get("histMuonPtRelCSVTag");
  hist_MuonPtRelCSVTag->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  hist_MuonPtRelCSVTag->GetYaxis()->SetTitle("Entries");
  // muon pt relative for CSV veto Jets
  TH1D *hist_MuonPtRelCSVVeto=(TH1D*)file_in->Get("histMuonPtRelCSVVeto");
  hist_MuonPtRelCSVVeto->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");
  hist_MuonPtRelCSVVeto->GetYaxis()->SetTitle("Entries");

  CSVTagMethod->FlavouredHistogram(hist_MuonPtRelCSVTag,2,2,20,0.6);
  CSVTagMethod->FlavouredHistogram(hist_MuonPtRelCSVVeto,2,2,24,0.6);
  
  TCanvas *Canvas_MuonPtRel_CSVTag_CSVVeto = new TCanvas("Canvas_MuonPtRel_CSVTag_CSVVeto","Canvas_MuonPtRel_CSVTag_CSVVeto",800,400);
  Canvas_MuonPtRel_CSVTag_CSVVeto->Divide(2,1);
  Canvas_MuonPtRel_CSVTag_CSVVeto->cd(1);
  hist_MuonPtRelCSVTag->Draw();
  
  Canvas_MuonPtRel_CSVTag_CSVVeto->cd(2);
  hist_MuonPtRelCSVVeto->Draw();
  
  Canvas_MuonPtRel_CSVTag_CSVVeto->SaveAs("Plots/CSVPlots/MuonPtRel_CSVTag_CSVVeto.pdf");
  Canvas_MuonPtRel_CSVTag_CSVVeto->SaveAs("Plots/CSVPlots/MuonPtRel_CSVTag_CSVVeto.png");

  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX//
  //======================= Muon Pt Relative for CSV Tag and Veto Drawn  ==============//
  //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX//
  
  /*
  //No usefulness of these ratio histograms can be found.
  TH1 *hist_Ratio_MuonPtRelCSVTag_MuonPtRel=RatioHistogram(hist_MuonPtRelCSVTag,hist_MuonPtRel,1);
  hist_Ratio_MuonPtRelCSVTag_MuonPtRel->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  hist_Ratio_MuonPtRelCSVTag_MuonPtRel->GetYaxis()->SetTitle("MuonPtRelCSVTag/MuonPtRel");
  hist_Ratio_MuonPtRelCSVTag_MuonPtRel->GetYaxis()->SetRangeUser(0.0,1.2);
  CSVTagMethod->FlavouredHistogram(hist_Ratio_MuonPtRelCSVTag_MuonPtRel,2,2,20,0.6);
    
  TH1 *hist_Ratio_MuonPtRelCSVVeto_MuonPtRel=RatioHistogram(hist_MuonPtRelCSVVeto,hist_MuonPtRel,1);
  hist_Ratio_MuonPtRelCSVVeto_MuonPtRel->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV)");
  hist_Ratio_MuonPtRelCSVVeto_MuonPtRel->GetYaxis()->SetTitle("MuonPtRelCSVVeto/MuonPtRel");
  hist_Ratio_MuonPtRelCSVVeto_MuonPtRel->GetYaxis()->SetRangeUser(0.0,1.2);
  CSVTagMethod->FlavouredHistogram(hist_Ratio_MuonPtRelCSVVeto_MuonPtRel,2,2,24,0.6);
  
  TCanvas *Canvas_RatioMuonPtRel_CSVTag_CSVVeto = new TCanvas("Canvas_RatioMuonPtRel_CSVTag_CSVVeto","Canvas_RatioMuonPtRel_CSVTag_CSVVeto",800,400);
  Canvas_RatioMuonPtRel_CSVTag_CSVVeto->Divide(2,1);
  
  Canvas_RatioMuonPtRel_CSVTag_CSVVeto->cd(1);
  hist_Ratio_MuonPtRelCSVTag_MuonPtRel->Draw();
  
  
  Canvas_RatioMuonPtRel_CSVTag_CSVVeto->cd(2);
  hist_Ratio_MuonPtRelCSVVeto_MuonPtRel->Draw();
  

  Canvas_RatioMuonPtRel_CSVTag_CSVVeto->SaveAs("Plots/CSVPlots/RatioMuonPtRel_CSVTag_CSVVeto.pdf");
  Canvas_RatioMuonPtRel_CSVTag_CSVVeto->SaveAs("Plots/CSVPlots/RatioMuonPtRel_CSVTag_CSVVeto.png");
  */
  //====================================================================================//
  //============================ Flavour Dependent CSV plots ===========================//
  //====================================================================================//
  //=========== Get the 3D Histo of JetPt, JetFlavour and CSVv2 ======================//
  //====================================================================================//
  
  // GET THE 3D HISTOGRAM FOR JETS
  //Get the 3D Histogram of JetCSV, JetPt, Flavour
  TH3D *hist_Master_JetCSV_JetPt_Flavour=(TH3D*)file_in->Get("hist_Master_JetCSV_JetPt_Flavour");
  
  //Get the CSV distribution of all flavour Jets
  //entries form flavour 8 should be removed (These are Jets with refparton flv = 0?)
  TH1* hist_JetCSV_Inclusive =  hist_Master_JetCSV_JetPt_Flavour->ProjectionX("hist_JetCSV_Inclusive",0,-1,0,-1);// 

  //Get the pT distribution of all flavour Jets for csv v2 > 0.9
  TH1* hist_JetPt_CSVTag_Inclusive =  hist_Master_JetCSV_JetPt_Flavour->ProjectionY("hist_JetPt_CSVTag_Inclusive",Bin_CSV_WorkingPoint,Bin_CSV_Max,0,-1);
  hist_JetPt_CSVTag_Inclusive->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist_JetPt_CSVTag_Inclusive->GetYaxis()->SetTitle("Entries");

  CSVTagMethod->rebinAsymmetric(hist_JetPt_CSVTag_Inclusive, CSVTagMethod->NBins_JetPt_VarSize-1, CSVTagMethod->JetPtBinEdges);
  
  // Get the bin corresponding to different flavours
  Int_t FlvBinMinForInc_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(1);
  Int_t FlvBinMaxForInc_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(6);

  Int_t FlvBinMinForU_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(1);
  Int_t FlvBinMaxForU_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(1);

  Int_t FlvBinMinForD_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(2);
  Int_t FlvBinMaxForD_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(2);

  Int_t FlvBinMinForS_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(3);
  Int_t FlvBinMaxForS_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(3);

  Int_t FlvBinMinForC_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(4);
  Int_t FlvBinMaxForC_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(4);

  Int_t FlvBinMinForB_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(5);
  Int_t FlvBinMaxForB_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(5);

  Int_t FlvBinMinForG_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(6);
  Int_t FlvBinMaxForG_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(6);

  Int_t FlvBinMinForLight_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(1);
  Int_t FlvBinMaxForLight_CSV = hist_Master_JetCSV_JetPt_Flavour->GetZaxis()->FindBin(3);

  //Get the CSV distribution B Jets
  TH1* hist_JetCSV_ForB =  hist_Master_JetCSV_JetPt_Flavour->ProjectionX("hist_JetCSV_ForB",0,-1,FlvBinMinForB_CSV,FlvBinMaxForB_CSV);
  

  //Get the pT distribution of B Jets for csv v2 > 0.9
  TH1* hist_JetPt_CSVTag_ForB =  hist_Master_JetCSV_JetPt_Flavour->ProjectionY("hist_JetPt_CSVTag_ForB",Bin_CSV_WorkingPoint,Bin_CSV_Max,FlvBinMinForB_CSV,FlvBinMaxForB_CSV);
  hist_JetPt_CSVTag_ForB->GetXaxis()->SetTitle("B Jet p_{T} (GeV/c)");
  hist_JetPt_CSVTag_ForB->GetYaxis()->SetTitle("Entries");
  CSVTagMethod->rebinAsymmetric(hist_JetPt_CSVTag_ForB, CSVTagMethod->NBins_JetPt_VarSize-1, CSVTagMethod->JetPtBinEdges);
  CSVTagMethod->FlavouredHistogram(hist_JetPt_CSVTag_ForB, CSVTagMethod->LineColorArray[5], CSVTagMethod->MarkerColorArray[5], CSVTagMethod->MarkerStyleArray[5],0.6);
  
  //style the histograms
  CSVTagMethod->FlavouredHistogram(hist_JetCSV_Inclusive, 1, 1, 20,0.6);
  CSVTagMethod->FlavouredHistogram(hist_JetPt_CSVTag_Inclusive, 1, 1, 20,0.6);

  CSVTagMethod->FlavouredHistogram(hist_JetCSV_ForB, CSVTagMethod->LineColorArray[5], CSVTagMethod->MarkerColorArray[5], CSVTagMethod->MarkerStyleArray[5],0.6);
  CSVTagMethod->FlavouredHistogram(hist_JetPt_CSVTag_ForB, CSVTagMethod->LineColorArray[5], CSVTagMethod->MarkerColorArray[5], CSVTagMethod->MarkerStyleArray[5],0.6);
 
  // scale histograms with their integrals
  hist_JetCSV_Inclusive->Scale(1.0/hist_JetCSV_Inclusive->Integral());
  hist_JetCSV_ForB->Scale(1.0/hist_JetCSV_ForB->Integral());


  Double_t Number_Jets_CSV_Veto_Inc = hist_JetCSV_Inclusive->Integral(Bin_CSV_Min,Bin_CSV_WorkingPoint-1);    
  Double_t Number_Jets_CSV_Tag_Inc =  hist_JetCSV_Inclusive->Integral(Bin_CSV_WorkingPoint,Bin_CSV_Max);
  Double_t Jet_CSV_Tag_Fraction_Inc = Number_Jets_CSV_Tag_Inc/(Number_Jets_CSV_Tag_Inc+Number_Jets_CSV_Veto_Inc) ;

  
  Double_t Number_Jets_CSV_Veto_ForB = hist_JetCSV_ForB->Integral(Bin_CSV_Min,Bin_CSV_WorkingPoint-1);    
  Double_t Number_Jets_CSV_Tag_ForB =  hist_JetCSV_ForB->Integral(Bin_CSV_WorkingPoint,Bin_CSV_Max);
  Double_t Jet_CSV_Tag_Fraction_ForB = Number_Jets_CSV_Tag_ForB/(Number_Jets_CSV_Tag_ForB+Number_Jets_CSV_Veto_ForB) ;

  
  cout<<endl<<endl;
  cout<<" projection for flavour dependence "<<endl;
  cout<<" CSV  Jet Inclusive "<<Number_Jets_CSV_Tag_Inc<<"   "<<Number_Jets_CSV_Veto_Inc<<"  Frac --> "<<Jet_CSV_Tag_Fraction_Inc<<endl;
  cout<<" CSV  Jet For b "<<Number_Jets_CSV_Tag_ForB<<"   "<<Number_Jets_CSV_Veto_ForB<<"  Frac --> "<<Jet_CSV_Tag_Fraction_ForB<<endl;


  /*
  Double_t Number_MuonJets_CSV_Tag = hist_MuonJetCSV->Integral(Bin_CSV_WorkingPoint,Bin_CSV_Max);
  Double_t Number_MuonJets_CSV_Veto = hist_MuonJetCSV->Integral(Bin_CSV_Min,Bin_CSV_WorkingPoint-1);
  Double_t MuonJet_CSV_Tag_Fraction = Number_MuonJets_CSV_Tag/(Number_MuonJets_CSV_Tag+Number_MuonJets_CSV_Veto) ;
  cout<<" CSV Muon Jet "<<Number_MuonJets_CSV_Tag<<"   "<<Number_MuonJets_CSV_Veto<<"  Frac --> "<<MuonJet_CSV_Tag_Fraction<<endl;
  */
  cout<<endl<<endl;
  
  
  // Bug test
  // compare the 1D histogram filled in the analyzer with the 1D histogram from the projection
  //new TCanvas;
  //hist_JetCSV->Draw();
  //hist_JetCSV_Inclusive->Draw("same");
  //Bug test passed

  TCanvas *Canvas_JetCSVAndPt_Inclusive_ForB = new TCanvas("Canvas_JetCSVAndPt_Inclusive_ForB","Canvas_JetCSVAndPt_Inclusive_ForB",800,400);
  Canvas_JetCSVAndPt_Inclusive_ForB->Divide(2,1);
  Canvas_JetCSVAndPt_Inclusive_ForB->cd(1);
  
  
  TLegend *lgd_JetCSVAndPt_Inclusive_ForB = CSVTagMethod->MyLegend(0.42,0.72,0.58,0.87);
  lgd_JetCSVAndPt_Inclusive_ForB->AddEntry(hist_JetCSV_Inclusive,"All Jets","P");
  lgd_JetCSVAndPt_Inclusive_ForB->AddEntry(hist_JetCSV_ForB,"b Jets","P");
  
  gPad->SetLogy(1);
  hist_JetCSV_Inclusive->GetYaxis()->SetRangeUser(0.0001,10.0);
  hist_JetCSV_Inclusive->Draw();
  hist_JetCSV_ForB->Draw("same");
  lgd_JetCSVAndPt_Inclusive_ForB->Draw("same");

  tb->DrawLatex(0.3,0.28,Form("Jets CSVv2>0.9=%0.2f",Jet_CSV_Tag_Fraction_Inc));
  tr->DrawLatex(0.3,0.24,Form("b-Jets CSVv2>0.9=%0.2f",Jet_CSV_Tag_Fraction_ForB));

  

  // for 2015 MC
  //TH1D *hist_JetPtCSV_Inclusive_ForB_Ghost = CSVTagMethod->Get_Ghost_Hist("hist_JetPtCSV_Inclusive_ForB_Ghost","hist_JetPtCSV_Inclusive_ForB_Ghost",0.000000000001,0.000001,"Jet p_{T} (GeV/c)","dN/dp_{T}(GeV/c)^{-1}");
  
  TH1D *hist_JetPtCSV_Inclusive_ForB_Ghost = CSVTagMethod->Get_Ghost_Hist("hist_JetPtCSV_Inclusive_ForB_Ghost","hist_JetPtCSV_Inclusive_ForB_Ghost",0.00001,100.0,"Jet p_{T} (GeV/c)","dN/dp_{T}(GeV/c)^{-1}");
  Canvas_JetCSVAndPt_Inclusive_ForB->cd(2);
  gPad->SetLogy(1);
  hist_JetPtCSV_Inclusive_ForB_Ghost->Draw();
  hist_JetPt_CSVTag_Inclusive->Draw("same");
  hist_JetPt_CSVTag_ForB->Draw("same");
  lgd_JetCSVAndPt_Inclusive_ForB->Draw("same");

  Canvas_JetCSVAndPt_Inclusive_ForB->SaveAs("Plots/CSVPlots/JetCSVAndPt_Inclusive_ForB.pdf");
  Canvas_JetCSVAndPt_Inclusive_ForB->SaveAs("Plots/CSVPlots/JetCSVAndPt_Inclusive_ForB.png");

  //return;


  //====================================================================================//
  //============================ Flavour Dependent CSV plots for MuonJets ==============//
  //====================================================================================//
  //=========== Get the 3D Histo of JetPt, JetFlavour and CSVv2 ======================//
  // GET THE 3D HISTOGRAM FOR Muon JETS
  //Get the 3D Histogram of MuonJetCSV, MuonJetPt, Flavour
  TH3D *hist_Master_MuonJetCSV_MuonJetPt_Flavour=(TH3D*)file_in->Get("hist_Master_MuonJetCSV_MuonJetPt_Flavour");
  
  //Get the CSV distribution of all flavour MuonJets
  TH1* hist_MuonJetCSV_Inclusive =  hist_Master_MuonJetCSV_MuonJetPt_Flavour->ProjectionX("hist_MuonJetCSV_Inclusive",0,-1,0,-1);
  CSVTagMethod->ScaleHistByItsIntegral(hist_MuonJetCSV_Inclusive);
  
  //Get the pT distribution of all flavour Muon Jets for csv v2 > 0.9
  TH1* hist_MuonJetPt_CSVTag_Inclusive = hist_Master_MuonJetCSV_MuonJetPt_Flavour->ProjectionY("hist_MuonJetPt_CSVTag_Inclusive",Bin_CSV_WorkingPoint,Bin_CSV_Max,0,-1);
  hist_MuonJetPt_CSVTag_Inclusive->GetXaxis()->SetTitle("Muon Jet p_{T} (GeV/c)");
  hist_MuonJetPt_CSVTag_Inclusive->GetYaxis()->SetTitle("Entries");
  CSVTagMethod->rebinAsymmetric(hist_MuonJetPt_CSVTag_Inclusive, CSVTagMethod->NBins_JetPt_VarSize-1, CSVTagMethod->JetPtBinEdges);
    
  //Get the CSV distribution for b flavour Muon Jets
  TH1* hist_MuonJetCSV_ForB =  hist_Master_MuonJetCSV_MuonJetPt_Flavour->ProjectionX("hist_MuonJetCSV_ForB",0,-1,FlvBinMinForB_CSV,FlvBinMaxForB_CSV);
  CSVTagMethod->ScaleHistByItsIntegral(hist_MuonJetCSV_ForB);
 
  //Get the pT distribution b flavour Muon Jets for csv v2 > 0.9
  TH1* hist_MuonJetPt_CSVTag_ForB =  hist_Master_MuonJetCSV_MuonJetPt_Flavour->ProjectionY("hist_MuonJetPt_CSVTag_ForB",Bin_CSV_WorkingPoint,Bin_CSV_Max,FlvBinMinForB_CSV,FlvBinMaxForB_CSV);
  hist_MuonJetPt_CSVTag_ForB->GetXaxis()->SetTitle("B Muon Jet p_{T} (GeV/c)");
  hist_MuonJetPt_CSVTag_ForB->GetYaxis()->SetTitle("Entries");
  CSVTagMethod->rebinAsymmetric(hist_MuonJetPt_CSVTag_ForB, CSVTagMethod->NBins_JetPt_VarSize-1, CSVTagMethod->JetPtBinEdges);
  

  // style the histograms
  CSVTagMethod->FlavouredHistogram(hist_MuonJetCSV_Inclusive, 1, 1, 20,0.6);
  CSVTagMethod->FlavouredHistogram(hist_MuonJetPt_CSVTag_Inclusive, 1, 1, 20,0.6);

  CSVTagMethod->FlavouredHistogram(hist_MuonJetCSV_ForB, CSVTagMethod->LineColorArray[5], CSVTagMethod->MarkerColorArray[5], CSVTagMethod->MarkerStyleArray[5],0.6);
  CSVTagMethod->FlavouredHistogram(hist_MuonJetPt_CSVTag_ForB, CSVTagMethod->LineColorArray[5], CSVTagMethod->MarkerColorArray[5], CSVTagMethod->MarkerStyleArray[5],0.6);
 
  
  TCanvas *Canvas_MuonJetCSVAndPt_Inclusive_ForB = new TCanvas("Canvas_MuonJetCSVAndPt_Inclusive_ForB","Canvas_MuonJetCSVAndPt_Inclusive_ForB",800,400);
  Canvas_MuonJetCSVAndPt_Inclusive_ForB->Divide(2,1);
  Canvas_MuonJetCSVAndPt_Inclusive_ForB->cd(1);

  TLegend *lgd_MuonJetCSVAndPt_Inclusive_ForB = CSVTagMethod->MyLegend(0.42,0.72,0.58,0.87);
  lgd_MuonJetCSVAndPt_Inclusive_ForB->AddEntry(hist_MuonJetCSV_Inclusive,"All MuonJets","P");
  lgd_MuonJetCSVAndPt_Inclusive_ForB->AddEntry(hist_MuonJetCSV_ForB,"b MuonJets","P");

  gPad->SetLogy(1);
  hist_MuonJetCSV_Inclusive->GetYaxis()->SetRangeUser(0.0001,10.0);
  hist_MuonJetCSV_Inclusive->Draw();
  hist_MuonJetCSV_ForB->Draw("same");
  lgd_MuonJetCSVAndPt_Inclusive_ForB->Draw("same");
  
  Canvas_MuonJetCSVAndPt_Inclusive_ForB->cd(2);
  gPad->SetLogy(1);
  hist_JetPtCSV_Inclusive_ForB_Ghost->Draw("same");
  hist_MuonJetPt_CSVTag_Inclusive->Draw("same");
  hist_MuonJetPt_CSVTag_ForB->Draw("same");
  lgd_MuonJetCSVAndPt_Inclusive_ForB->Draw("same");

  Canvas_MuonJetCSVAndPt_Inclusive_ForB->SaveAs("Plots/CSVPlots/MuonJetCSVAndPt_Inclusive_ForB.pdf");
  Canvas_MuonJetCSVAndPt_Inclusive_ForB->SaveAs("Plots/CSVPlots/MuonJetCSVAndPt_Inclusive_ForB.png");

  //return;

  //====================================================================================//
  //================ Muon pT-Rel Templates for different flavour MuonJets ==============//
  //====================================================================================//

  // GET THE 3D HISTOGRAM FOR Muon JETS
  //Get the 3D Histogram of MuonJetPt, Muon Pt Relative and Jet Flavour
  TH3D *hist_Master_MuonJetPt_MuPtRel_Flavour=(TH3D*)file_in->Get("hist_Master_JetPt_MuPtRel_Flavour");

  //==== Project the 3D histo to get the 1D histograms of muon pt relative for different flavours =========================================//

  Int_t MuonJetPt_BinMin = 1;
  Int_t MuonJetPt_BinMax = hist_Master_MuonJetPt_MuPtRel_Flavour->GetNbinsX();

  /*
  TH1 *hist_MuPtRel_Inclusive = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_Inclusive",0,-1,FlvBinMinForInc_CSV,FlvBinMaxForInc_CSV);
  TH1 *hist_MuPtRel_U = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_U",0,-1,FlvBinMinForU_CSV,FlvBinMaxForU_CSV);
  TH1 *hist_MuPtRel_D = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_D",0,-1,FlvBinMinForD_CSV,FlvBinMaxForD_CSV);
  TH1 *hist_MuPtRel_S = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_S",0,-1,FlvBinMinForS_CSV,FlvBinMaxForS_CSV);
  TH1 *hist_MuPtRel_C = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_C",0,-1,FlvBinMinForC_CSV,FlvBinMaxForC_CSV);
  TH1 *hist_MuPtRel_B = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_B",0,-1,FlvBinMinForB_CSV,FlvBinMaxForB_CSV);
  TH1 *hist_MuPtRel_G = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_G",0,-1,FlvBinMinForG_CSV,FlvBinMaxForG_CSV);
  */
  
  TH1 *hist_MuPtRel_Inclusive = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_Inclusive",MuonJetPt_BinMin,MuonJetPt_BinMax,FlvBinMinForInc_CSV,FlvBinMaxForInc_CSV);
  TH1 *hist_MuPtRel_U = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_U",MuonJetPt_BinMin,MuonJetPt_BinMax,FlvBinMinForU_CSV,FlvBinMaxForU_CSV);
  TH1 *hist_MuPtRel_D = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_D",MuonJetPt_BinMin,MuonJetPt_BinMax,FlvBinMinForD_CSV,FlvBinMaxForD_CSV);
  TH1 *hist_MuPtRel_S = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_S",MuonJetPt_BinMin,MuonJetPt_BinMax,FlvBinMinForS_CSV,FlvBinMaxForS_CSV);
  TH1 *hist_MuPtRel_C = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_C",MuonJetPt_BinMin,MuonJetPt_BinMax,FlvBinMinForC_CSV,FlvBinMaxForC_CSV);
  TH1 *hist_MuPtRel_B = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_B",MuonJetPt_BinMin,MuonJetPt_BinMax,FlvBinMinForB_CSV,FlvBinMaxForB_CSV);
  TH1 *hist_MuPtRel_G = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_G",MuonJetPt_BinMin,MuonJetPt_BinMax,FlvBinMinForG_CSV,FlvBinMaxForG_CSV);
  
  // Get the u,d and s
  TH1 *hist_MuPtRel_Light = hist_Master_MuonJetPt_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_Light",0,-1,FlvBinMinForLight_CSV,FlvBinMaxForLight_CSV);
  hist_MuPtRel_Light->SetTitle("hist_MuPtRel_Light");
  // Add the gluon histogram
  hist_MuPtRel_Light->Add(hist_MuPtRel_G);
  // Add the charm histogram
  //hist_MuPtRel_Light->Add(hist_MuPtRel_C);
  
  //======= Set the cosmatics of histograms ===============//
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_Inclusive, CSVTagMethod->LineColorArray[6], CSVTagMethod->MarkerColorArray[6], 20,CSVTagMethod->MarkerSizeArray[1]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_U, CSVTagMethod->LineColorArray[1], CSVTagMethod->MarkerColorArray[1], CSVTagMethod->MarkerStyleArray[1],CSVTagMethod->MarkerSizeArray[1]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_D, CSVTagMethod->LineColorArray[2], CSVTagMethod->MarkerColorArray[2], CSVTagMethod->MarkerStyleArray[2],CSVTagMethod->MarkerSizeArray[2]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_S, CSVTagMethod->LineColorArray[3], CSVTagMethod->MarkerColorArray[3], CSVTagMethod->MarkerStyleArray[3],CSVTagMethod->MarkerSizeArray[3]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_C, CSVTagMethod->LineColorArray[4], CSVTagMethod->MarkerColorArray[4], CSVTagMethod->MarkerStyleArray[4],CSVTagMethod->MarkerSizeArray[4]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_B, CSVTagMethod->LineColorArray[5], CSVTagMethod->MarkerColorArray[5], CSVTagMethod->MarkerStyleArray[5],CSVTagMethod->MarkerSizeArray[5]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_G, CSVTagMethod->LineColorArray[6], CSVTagMethod->MarkerColorArray[6], CSVTagMethod->MarkerStyleArray[6],CSVTagMethod->MarkerSizeArray[6]);
  //pp 2015 MC
  //Double_t hist_MuPtRel_YAxisRange_Min = 0.000000000001;
  //Double_t hist_MuPtRel_YAxisRange_Max =0.000001;

  Double_t hist_MuPtRel_YAxisRange_Min = 0.001;
  Double_t hist_MuPtRel_YAxisRange_Max = 20.0;
    
  hist_MuPtRel_Inclusive->GetYaxis()->SetRangeUser(hist_MuPtRel_YAxisRange_Min,hist_MuPtRel_YAxisRange_Max);
  hist_MuPtRel_U->GetYaxis()->SetRangeUser(hist_MuPtRel_YAxisRange_Min,hist_MuPtRel_YAxisRange_Max);
  hist_MuPtRel_D->GetYaxis()->SetRangeUser(hist_MuPtRel_YAxisRange_Min,hist_MuPtRel_YAxisRange_Max);
  hist_MuPtRel_S->GetYaxis()->SetRangeUser(hist_MuPtRel_YAxisRange_Min,hist_MuPtRel_YAxisRange_Max);
  hist_MuPtRel_C->GetYaxis()->SetRangeUser(hist_MuPtRel_YAxisRange_Min,hist_MuPtRel_YAxisRange_Max);
  hist_MuPtRel_B->GetYaxis()->SetRangeUser(hist_MuPtRel_YAxisRange_Min,hist_MuPtRel_YAxisRange_Max);
  hist_MuPtRel_G->GetYaxis()->SetRangeUser(hist_MuPtRel_YAxisRange_Min,hist_MuPtRel_YAxisRange_Max);


  //============ Get the integral for differnt histograms ============================//

  Double_t Int_MuPtRel_Inclusive = hist_MuPtRel_Inclusive->Integral();

  Double_t Int_MuPtRel_U = hist_MuPtRel_U->Integral();
  Double_t Int_MuPtRel_D = hist_MuPtRel_D->Integral();
  Double_t Int_MuPtRel_S = hist_MuPtRel_S->Integral();
  Double_t Int_MuPtRel_C = hist_MuPtRel_C->Integral();
  Double_t Int_MuPtRel_B = hist_MuPtRel_B->Integral();
  Double_t Int_MuPtRel_G = hist_MuPtRel_G->Integral();

  Double_t Frac_MuPtRel_Inc = Int_MuPtRel_Inclusive/Int_MuPtRel_Inclusive; 
  Double_t Frac_MuPtRel_U = Int_MuPtRel_U/Int_MuPtRel_Inclusive; 
  Double_t Frac_MuPtRel_D = Int_MuPtRel_D/Int_MuPtRel_Inclusive; 
  Double_t Frac_MuPtRel_S = Int_MuPtRel_S/Int_MuPtRel_Inclusive; 
  Double_t Frac_MuPtRel_C = Int_MuPtRel_C/Int_MuPtRel_Inclusive; 
  Double_t Frac_MuPtRel_B = Int_MuPtRel_B/Int_MuPtRel_Inclusive; 
  Double_t Frac_MuPtRel_G = Int_MuPtRel_G/Int_MuPtRel_Inclusive; 

  //Canvas muon pT-Rel for different flavours 
  TCanvas *CanvasMuPtRel_Flavour = new TCanvas("CanvasMuPtRel_Flavour","CanvasMuPtRel_Flavour",1200,1200);
  CanvasMuPtRel_Flavour->Divide(4,2);//coulm,row

  //TH1D *hist_JetPtCSV_Inclusive_ForB_Ghost = CSVTagMethod->Get_Ghost_Hist("hist_JetPtCSV_Inclusive_ForB_Ghost","hist_JetPtCSV_Inclusive_ForB_Ghost",0.000000000001,0.000001,"Jet p_{T} (GeV/c)","dN/dp_{T}(GeV/c)^{-1}");
     
  //===================================================================================================//
  //==================== ploting muon pT-Rel histograms  ==============================================//
  //===================================================================================================//
    
  CanvasMuPtRel_Flavour->cd(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_Inclusive->Draw();
  
  tb->DrawLatex(0.3,0.80,Form("Frac %0.2f",Frac_MuPtRel_Inc));
    
  CanvasMuPtRel_Flavour->cd(2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_U->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.2f",Frac_MuPtRel_U));

  CanvasMuPtRel_Flavour->cd(3);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_D->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.2f",Frac_MuPtRel_D));
  
  CanvasMuPtRel_Flavour->cd(4);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_S->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.2f",Frac_MuPtRel_S));
  
  CanvasMuPtRel_Flavour->cd(5);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_C->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.2f",Frac_MuPtRel_C));
  
  
  CanvasMuPtRel_Flavour->cd(6);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_B->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.2f",Frac_MuPtRel_B));
  
  CanvasMuPtRel_Flavour->cd(7);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_G->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.2f",Frac_MuPtRel_G));
  
  CanvasMuPtRel_Flavour->cd(8);
  
  CSVTagMethod->DrawFlavourLegendVertical(0.12,0.36,0.88,0.92, Flv_Legend_Index_Local_V++);
  
  
  CanvasMuPtRel_Flavour->SaveAs("Plots/CSVPlots/MuPtRel_Flavour.pdf");
  CanvasMuPtRel_Flavour->SaveAs("Plots/CSVPlots/MuPtRel_Flavour.png");

   
  //===================================================================================================//
  //==================== ploting muon pT-Rel histograms stacked mode ==================================//
  //==================== This is for all CSV Values ===================================================//
  //===================================================================================================//
  
  //CREATE A STACK FOR HISTOGRAMS (plot charm separately)
  THStack *hs_MuPtRel_All = new THStack("hs_MuPtRel_All","hs_MuPtRel_All");

  //Add histograms together before adding them in stack (removes the lines between them on plot)
  hist_MuPtRel_U->Add(hist_MuPtRel_D);
  hist_MuPtRel_U->Add(hist_MuPtRel_S);
  hist_MuPtRel_U->Add(hist_MuPtRel_G);

  hist_MuPtRel_U->SetFillColor(kBlue);
  //hist_MuPtRel_D->SetFillColor(kBlue);
  //hist_MuPtRel_S->SetFillColor(kBlue);
  //hist_MuPtRel_G->SetFillColor(kBlue);

  hist_MuPtRel_C->SetFillColor(kGreen);
  hist_MuPtRel_B->SetFillColor(kRed);
    

  hs_MuPtRel_All->Add(hist_MuPtRel_U);
  //hs_MuPtRel_All->Add(hist_MuPtRel_D);
  //hs_MuPtRel_All->Add(hist_MuPtRel_S);
  //hs_MuPtRel_All->Add(hist_MuPtRel_G);
  hs_MuPtRel_All->Add(hist_MuPtRel_C);
  hs_MuPtRel_All->Add(hist_MuPtRel_B);

  THStack *hs1_MuPtRel_All = new THStack("hs1_MuPtRel_All","hs1_MuPtRel_All");
  hist_MuPtRel_Light->SetFillColor(kBlue);
  hs1_MuPtRel_All->Add(hist_MuPtRel_Light); // light include udsg
  hs1_MuPtRel_All->Add(hist_MuPtRel_C);
  hs1_MuPtRel_All->Add(hist_MuPtRel_B);
  
  // Stack Histo drawn for testing
  /*
  new TCanvas;
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hs1_MuPtRel_All->Draw("hist");
  hs1_MuPtRel_All->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");
  hs1_MuPtRel_All->GetYaxis()->SetTitle("Entries");
  hist_MuPtRel_Inclusive->Draw("same");
  lgd_hs1_MuPtRel_All->Draw("same");
  */


  
  //====================================================================================//
  //================ Muon pT-Rel templates for different flavour MuonJets CSV Tagged ===//
  //====================================================================================//
  
  // GET THE 3D HISTOGRAM FOR Muon JETS
  //Get the 3D Histogram of MuonJetPt, Muon Pt Relative and Jet Flavour
  TH3D *hist_Master_JetCSV_MuPtRel_Flavour=(TH3D*)file_in->Get("hist_Master_JetCSV_MuPtRel_Flavour");
  //==== Get the 1D histograms for different flavours =========================================//
  
  TH1 *hist_MuPtRel_CSVTag_Inclusive = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVTag_Inclusive",Bin_CSV_WorkingPoint,Bin_CSV_Max,FlvBinMinForInc_CSV,FlvBinMaxForInc_CSV);
    
  TH1 *hist_MuPtRel_CSVTag_U = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVTag_U",Bin_CSV_WorkingPoint,Bin_CSV_Max,FlvBinMinForU_CSV,FlvBinMaxForU_CSV);
  TH1 *hist_MuPtRel_CSVTag_D = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVTag_D",Bin_CSV_WorkingPoint,Bin_CSV_Max,FlvBinMinForD_CSV,FlvBinMaxForD_CSV);
  TH1 *hist_MuPtRel_CSVTag_S = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVTag_S",Bin_CSV_WorkingPoint,Bin_CSV_Max,FlvBinMinForS_CSV,FlvBinMaxForS_CSV);
  TH1 *hist_MuPtRel_CSVTag_C = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVTag_C",Bin_CSV_WorkingPoint,Bin_CSV_Max,FlvBinMinForC_CSV,FlvBinMaxForC_CSV);
  TH1 *hist_MuPtRel_CSVTag_B = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVTag_B",Bin_CSV_WorkingPoint,Bin_CSV_Max,FlvBinMinForB_CSV,FlvBinMaxForB_CSV);
  TH1 *hist_MuPtRel_CSVTag_G = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVTag_G",Bin_CSV_WorkingPoint,Bin_CSV_Max,FlvBinMinForG_CSV,FlvBinMaxForG_CSV);

  // Get the u,d and s
  TH1 *hist_MuPtRel_CSVTag_Light = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVTag_Light",Bin_CSV_WorkingPoint,Bin_CSV_Max,FlvBinMinForLight_CSV,FlvBinMaxForLight_CSV);
  // Add the gluon histogram
  hist_MuPtRel_CSVTag_Light->Add(hist_MuPtRel_CSVTag_G);
  // Add the charm histogram
  //hist_MuPtRel_CSVTag_Light->Add(hist_MuPtRel_CSVTag_C);

  //====================================================================================//
  //================ Muon pT-Rel templates for different flavour MuonJets CSV Veto ===//
  //====================================================================================//
  TH1 *hist_MuPtRel_CSVVeto_Inclusive = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVVeto_Inclusive",Bin_CSV_Min,Bin_CSV_WorkingPoint-1,FlvBinMinForInc_CSV,FlvBinMaxForInc_CSV);
    
  TH1 *hist_MuPtRel_CSVVeto_U = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVVeto_U",Bin_CSV_Min,Bin_CSV_WorkingPoint-1,FlvBinMinForU_CSV,FlvBinMaxForU_CSV);
  TH1 *hist_MuPtRel_CSVVeto_D = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVVeto_D",Bin_CSV_Min,Bin_CSV_WorkingPoint-1,FlvBinMinForD_CSV,FlvBinMaxForD_CSV);
  TH1 *hist_MuPtRel_CSVVeto_S = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVVeto_S",Bin_CSV_Min,Bin_CSV_WorkingPoint-1,FlvBinMinForS_CSV,FlvBinMaxForS_CSV);
  TH1 *hist_MuPtRel_CSVVeto_C = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVVeto_C",Bin_CSV_Min,Bin_CSV_WorkingPoint-1,FlvBinMinForC_CSV,FlvBinMaxForC_CSV);
  TH1 *hist_MuPtRel_CSVVeto_B = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVVeto_B",Bin_CSV_Min,Bin_CSV_WorkingPoint-1,FlvBinMinForB_CSV,FlvBinMaxForB_CSV);
  TH1 *hist_MuPtRel_CSVVeto_G = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVVeto_G",Bin_CSV_Min,Bin_CSV_WorkingPoint-1,FlvBinMinForG_CSV,FlvBinMaxForG_CSV);

  // Get the u,d and s
  TH1 *hist_MuPtRel_CSVVeto_Light = hist_Master_JetCSV_MuPtRel_Flavour->ProjectionY("hist_MuPtRel_CSVVeto_Light",Bin_CSV_Min,Bin_CSV_WorkingPoint-1,FlvBinMinForLight_CSV,FlvBinMaxForLight_CSV);
  // Add the gluon histogram
  hist_MuPtRel_CSVVeto_Light->Add(hist_MuPtRel_CSVVeto_G);
  // Add the charm histogram
  //hist_MuPtRel_CSVVeto_Light->Add(hist_MuPtRel_CSVVeto_C);
   

  
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVTag_Inclusive, CSVTagMethod->LineColorArray[6], CSVTagMethod->MarkerColorArray[6], 20,CSVTagMethod->MarkerSizeArray[1]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVTag_U, CSVTagMethod->LineColorArray[1], CSVTagMethod->MarkerColorArray[1], CSVTagMethod->MarkerStyleArray[1],CSVTagMethod->MarkerSizeArray[1]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVTag_D, CSVTagMethod->LineColorArray[2], CSVTagMethod->MarkerColorArray[2], CSVTagMethod->MarkerStyleArray[2],CSVTagMethod->MarkerSizeArray[2]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVTag_S, CSVTagMethod->LineColorArray[3], CSVTagMethod->MarkerColorArray[3], CSVTagMethod->MarkerStyleArray[3],CSVTagMethod->MarkerSizeArray[3]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVTag_C, CSVTagMethod->LineColorArray[4], CSVTagMethod->MarkerColorArray[4], CSVTagMethod->MarkerStyleArray[4],CSVTagMethod->MarkerSizeArray[4]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVTag_B, CSVTagMethod->LineColorArray[5], CSVTagMethod->MarkerColorArray[5], CSVTagMethod->MarkerStyleArray[5],CSVTagMethod->MarkerSizeArray[5]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVTag_G, CSVTagMethod->LineColorArray[6], CSVTagMethod->MarkerColorArray[6], CSVTagMethod->MarkerStyleArray[6],CSVTagMethod->MarkerSizeArray[6]);
  
  //Double_t hist_MuPtRel_CSVTag_YAxisRange_Min = 0.000000000001;
  //Double_t hist_MuPtRel_CSVTag_YAxisRange_Max =0.000001;

  Double_t hist_MuPtRel_CSVTag_YAxisRange_Min = 0.01;
  Double_t hist_MuPtRel_CSVTag_YAxisRange_Max = 20.0;
    
  hist_MuPtRel_CSVTag_Inclusive->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVTag_YAxisRange_Min,hist_MuPtRel_CSVTag_YAxisRange_Max);
  hist_MuPtRel_CSVTag_U->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVTag_YAxisRange_Min,hist_MuPtRel_CSVTag_YAxisRange_Max);
  hist_MuPtRel_CSVTag_D->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVTag_YAxisRange_Min,hist_MuPtRel_CSVTag_YAxisRange_Max);
  hist_MuPtRel_CSVTag_S->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVTag_YAxisRange_Min,hist_MuPtRel_CSVTag_YAxisRange_Max);
  hist_MuPtRel_CSVTag_C->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVTag_YAxisRange_Min,hist_MuPtRel_CSVTag_YAxisRange_Max);
  hist_MuPtRel_CSVTag_B->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVTag_YAxisRange_Min,hist_MuPtRel_CSVTag_YAxisRange_Max);
  hist_MuPtRel_CSVTag_G->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVTag_YAxisRange_Min,hist_MuPtRel_CSVTag_YAxisRange_Max);


  
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVVeto_Inclusive, CSVTagMethod->LineColorArray[6], CSVTagMethod->MarkerColorArray[6], 20,CSVTagMethod->MarkerSizeArray[1]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVVeto_U, CSVTagMethod->LineColorArray[1], CSVTagMethod->MarkerColorArray[1], CSVTagMethod->MarkerStyleArray[1],CSVTagMethod->MarkerSizeArray[1]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVVeto_D, CSVTagMethod->LineColorArray[2], CSVTagMethod->MarkerColorArray[2], CSVTagMethod->MarkerStyleArray[2],CSVTagMethod->MarkerSizeArray[2]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVVeto_S, CSVTagMethod->LineColorArray[3], CSVTagMethod->MarkerColorArray[3], CSVTagMethod->MarkerStyleArray[3],CSVTagMethod->MarkerSizeArray[3]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVVeto_C, CSVTagMethod->LineColorArray[4], CSVTagMethod->MarkerColorArray[4], CSVTagMethod->MarkerStyleArray[4],CSVTagMethod->MarkerSizeArray[4]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVVeto_B, CSVTagMethod->LineColorArray[5], CSVTagMethod->MarkerColorArray[5], CSVTagMethod->MarkerStyleArray[5],CSVTagMethod->MarkerSizeArray[5]);
  CSVTagMethod->FlavouredHistogram(hist_MuPtRel_CSVVeto_G, CSVTagMethod->LineColorArray[6], CSVTagMethod->MarkerColorArray[6], CSVTagMethod->MarkerStyleArray[6],CSVTagMethod->MarkerSizeArray[6]);

  //Double_t hist_MuPtRel_CSVVeto_YAxisRange_Min = 0.000000000001;
  //Double_t hist_MuPtRel_CSVVeto_YAxisRange_Max =0.000001;

  Double_t hist_MuPtRel_CSVVeto_YAxisRange_Min = 0.01;
  Double_t hist_MuPtRel_CSVVeto_YAxisRange_Max = 20.0;
  
  hist_MuPtRel_CSVVeto_Inclusive->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVVeto_YAxisRange_Min,hist_MuPtRel_CSVVeto_YAxisRange_Max);
  hist_MuPtRel_CSVVeto_U->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVVeto_YAxisRange_Min,hist_MuPtRel_CSVVeto_YAxisRange_Max);
  hist_MuPtRel_CSVVeto_D->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVVeto_YAxisRange_Min,hist_MuPtRel_CSVVeto_YAxisRange_Max);
  hist_MuPtRel_CSVVeto_S->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVVeto_YAxisRange_Min,hist_MuPtRel_CSVVeto_YAxisRange_Max);
  hist_MuPtRel_CSVVeto_C->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVVeto_YAxisRange_Min,hist_MuPtRel_CSVVeto_YAxisRange_Max);
  hist_MuPtRel_CSVVeto_B->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVVeto_YAxisRange_Min,hist_MuPtRel_CSVVeto_YAxisRange_Max);
  hist_MuPtRel_CSVVeto_G->GetYaxis()->SetRangeUser(hist_MuPtRel_CSVVeto_YAxisRange_Min,hist_MuPtRel_CSVVeto_YAxisRange_Max);


  
  //============= Muon pT-Rel CSV Tag =========================================//
  //============ Get the integral for differnt histograms ====================//

  Double_t Int_MuPtRel_CSVTag_Inclusive = hist_MuPtRel_CSVTag_Inclusive->Integral();

  Double_t Int_MuPtRel_CSVTag_U = hist_MuPtRel_CSVTag_U->Integral();
  Double_t Int_MuPtRel_CSVTag_D = hist_MuPtRel_CSVTag_D->Integral();
  Double_t Int_MuPtRel_CSVTag_S = hist_MuPtRel_CSVTag_S->Integral();
  Double_t Int_MuPtRel_CSVTag_C = hist_MuPtRel_CSVTag_C->Integral();
  Double_t Int_MuPtRel_CSVTag_B = hist_MuPtRel_CSVTag_B->Integral();
  Double_t Int_MuPtRel_CSVTag_G = hist_MuPtRel_CSVTag_G->Integral();

  Double_t Frac_MuPtRel_CSVTag_Inc =Int_MuPtRel_CSVTag_Inclusive/Int_MuPtRel_CSVTag_Inclusive; 
  Double_t Frac_MuPtRel_CSVTag_U = Int_MuPtRel_CSVTag_U/Int_MuPtRel_CSVTag_Inclusive; 
  Double_t Frac_MuPtRel_CSVTag_D = Int_MuPtRel_CSVTag_D/Int_MuPtRel_CSVTag_Inclusive; 
  Double_t Frac_MuPtRel_CSVTag_S = Int_MuPtRel_CSVTag_S/Int_MuPtRel_CSVTag_Inclusive; 
  Double_t Frac_MuPtRel_CSVTag_C = Int_MuPtRel_CSVTag_C/Int_MuPtRel_CSVTag_Inclusive; 
  Double_t Frac_MuPtRel_CSVTag_B = Int_MuPtRel_CSVTag_B/Int_MuPtRel_CSVTag_Inclusive; 
  Double_t Frac_MuPtRel_CSVTag_G = Int_MuPtRel_CSVTag_G/Int_MuPtRel_CSVTag_Inclusive; 

  //======== Remaining fraction after the CSV tag cut
  
  Double_t ReFrac_MuPtRel_CSVTag_Inc =Int_MuPtRel_CSVTag_Inclusive/Int_MuPtRel_Inclusive; 
  Double_t ReFrac_MuPtRel_CSVTag_U = Int_MuPtRel_CSVTag_U/Int_MuPtRel_U; 
  Double_t ReFrac_MuPtRel_CSVTag_D = Int_MuPtRel_CSVTag_D/Int_MuPtRel_D; 
  Double_t ReFrac_MuPtRel_CSVTag_S = Int_MuPtRel_CSVTag_S/Int_MuPtRel_S; 
  Double_t ReFrac_MuPtRel_CSVTag_C = Int_MuPtRel_CSVTag_C/Int_MuPtRel_C; 
  Double_t ReFrac_MuPtRel_CSVTag_B = Int_MuPtRel_CSVTag_B/Int_MuPtRel_B; 
  Double_t ReFrac_MuPtRel_CSVTag_G = Int_MuPtRel_CSVTag_G/Int_MuPtRel_G; 
  
  //================================================================================//
  //==================== ploting CSV Tag Muon pT-Rel histograms   =================//
  //==============================================================================//

  
  //CREATE A STACK FOR HISTOGRAMS CSV Tag Muon pT-Rel histograms
  THStack *hs_MuPtRel_CSVTag_All = new THStack("hs_MuPtRel_CSVTag_All","hs_MuPtRel_CSVTag_All");
  
  //Add the histograms before adding them to stack
  hist_MuPtRel_CSVTag_U->Add(hist_MuPtRel_CSVTag_D);
  hist_MuPtRel_CSVTag_U->Add(hist_MuPtRel_CSVTag_S);
  hist_MuPtRel_CSVTag_U->Add(hist_MuPtRel_CSVTag_G);
  
  hist_MuPtRel_CSVTag_U->SetFillColor(kBlue);


  //hist_MuPtRel_CSVTag_D->SetFillColor(kBlue);
  //hist_MuPtRel_CSVTag_S->SetFillColor(kBlue);
  //hist_MuPtRel_CSVTag_G->SetFillColor(kBlue);
  
  hist_MuPtRel_CSVTag_C->SetFillColor(kGreen);
  hist_MuPtRel_CSVTag_B->SetFillColor(kRed);
  
  
  hs_MuPtRel_CSVTag_All->Add(hist_MuPtRel_CSVTag_U);
  //hs_MuPtRel_CSVTag_All->Add(hist_MuPtRel_CSVTag_D);
  //hs_MuPtRel_CSVTag_All->Add(hist_MuPtRel_CSVTag_S);
  //hs_MuPtRel_CSVTag_All->Add(hist_MuPtRel_CSVTag_G);

  hs_MuPtRel_CSVTag_All->Add(hist_MuPtRel_CSVTag_C);
  hs_MuPtRel_CSVTag_All->Add(hist_MuPtRel_CSVTag_B);

  //CREATE A STACK FOR HISTOGRAMS CSV Tag Muon pT-Rel histograms (Light {udsg} c and b}
  THStack *hs1_MuPtRel_CSVTag_All = new THStack("hs1_MuPtRel_CSVTag_All","hs1_MuPtRel_CSVTag_All");
  hist_MuPtRel_CSVTag_Light->SetFillColor(kBlue);
  hs1_MuPtRel_CSVTag_All->Add(hist_MuPtRel_CSVTag_Light);
  hs1_MuPtRel_CSVTag_All->Add(hist_MuPtRel_CSVTag_C);
  hs1_MuPtRel_CSVTag_All->Add(hist_MuPtRel_CSVTag_B);



  //CREATE A STACK FOR HISTOGRAMS CSV Veto Muon pT-Rel histograms (Light {udsg} c and b}
  THStack *hs1_MuPtRel_CSVVeto_All = new THStack("hs1_MuPtRel_CSVVeto_All","hs1_MuPtRel_CSVVeto_All");
  hist_MuPtRel_CSVVeto_Light->SetFillColor(kBlue);
  hist_MuPtRel_CSVVeto_B->SetFillColor(kRed);
  hist_MuPtRel_CSVVeto_C->SetFillColor(kGreen);

  hs1_MuPtRel_CSVVeto_All->Add(hist_MuPtRel_CSVVeto_Light);
  hs1_MuPtRel_CSVVeto_All->Add(hist_MuPtRel_CSVVeto_C);
  hs1_MuPtRel_CSVVeto_All->Add(hist_MuPtRel_CSVVeto_B);


  //============================ Drawing Histograms ======================================//
  //Canvas muon pT-Rel for different flavours 
  TCanvas *CanvasMuPtRel_CSVTag_Flavour = new TCanvas("CanvasMuPtRel_CSVTag_Flavour","CanvasMuPtRel_CSVTag_Flavour",1200,1200);
  CanvasMuPtRel_CSVTag_Flavour->Divide(4,2);//C,R


  CanvasMuPtRel_CSVTag_Flavour->cd(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_CSVTag_Inclusive->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.3f (%0.3f)",Frac_MuPtRel_CSVTag_Inc,ReFrac_MuPtRel_CSVTag_Inc));

  
  CanvasMuPtRel_CSVTag_Flavour->cd(2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_CSVTag_U->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.3f (%0.3f)",Frac_MuPtRel_CSVTag_U,ReFrac_MuPtRel_CSVTag_U));

  CanvasMuPtRel_CSVTag_Flavour->cd(3);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_CSVTag_D->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.3f (%0.3f)",Frac_MuPtRel_CSVTag_D,ReFrac_MuPtRel_CSVTag_D));
  CanvasMuPtRel_CSVTag_Flavour->cd(4);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_CSVTag_S->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.3f (%0.3f)",Frac_MuPtRel_CSVTag_S,ReFrac_MuPtRel_CSVTag_S));
    
  CanvasMuPtRel_CSVTag_Flavour->cd(5);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_CSVTag_C->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.3f (%0.3f)",Frac_MuPtRel_CSVTag_C,ReFrac_MuPtRel_CSVTag_C));
  
  CanvasMuPtRel_CSVTag_Flavour->cd(6);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_CSVTag_B->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.3f (%0.3f)",Frac_MuPtRel_CSVTag_B,ReFrac_MuPtRel_CSVTag_B));
    
  CanvasMuPtRel_CSVTag_Flavour->cd(7);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  //gPad->SetLogy(1);
  hist_MuPtRel_CSVTag_G->Draw();
  tb->DrawLatex(0.3,0.80,Form("Frac %0.3f (%0.3f)",Frac_MuPtRel_CSVTag_G,ReFrac_MuPtRel_CSVTag_G));
    
  CanvasMuPtRel_CSVTag_Flavour->cd(8);
  CSVTagMethod->DrawFlavourLegendVertical(0.12,0.36,0.88,0.92, Flv_Legend_Index_Local_V++);
  
  
  CanvasMuPtRel_CSVTag_Flavour->SaveAs("Plots/CSVPlots/MuPtRel_CSVTag_Flavour.pdf");
  CanvasMuPtRel_CSVTag_Flavour->SaveAs("Plots/CSVPlots/MuPtRel_CSVTag_Flavour.png");




  //=========== Drawing the stacked histograms =============================//
  TCanvas *Canvas_hs_MuPtRel_All = new TCanvas("Canvas_hs_MuPtRel_All","Canvas_hs_MuPtRel_All",800,400);
  Canvas_hs_MuPtRel_All->Divide(2,1);//colum x row

  TLegend *lgd_hs1_MuPtRel_All = CSVTagMethod->MyLegend(0.68,0.69,0.89,0.87);
  lgd_hs1_MuPtRel_All->AddEntry(hist_MuPtRel_Light,"udsg","F");
  lgd_hs1_MuPtRel_All->AddEntry(hist_MuPtRel_C,"c","F");
  lgd_hs1_MuPtRel_All->AddEntry(hist_MuPtRel_B,"b","F");
  

  Canvas_hs_MuPtRel_All->cd(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hs_MuPtRel_All->Draw("hist");
  Canvas_hs_MuPtRel_All->Update();
  hs_MuPtRel_All->SetTitle("Muon p_{T}^{Rel} (GeV/c)");
  hist_MuPtRel_Inclusive->Draw("same");
  lgd_hs1_MuPtRel_All->Draw("same");
  
  Canvas_hs_MuPtRel_All->cd(2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hs_MuPtRel_CSVTag_All->Draw("hist");
  hist_MuPtRel_CSVTag_Inclusive->Draw("same");
  lgd_hs1_MuPtRel_All->Draw("same");
  
  Canvas_hs_MuPtRel_All->SaveAs("Plots/CSVPlots/hs_MuPtRel_All.pdf");
  Canvas_hs_MuPtRel_All->SaveAs("Plots/CSVPlots/hs_MuPtRel_All.png");





  TCanvas *Canvas_hs1_MuPtRel_All = new TCanvas("Canvas_hs1_MuPtRel_All","Canvas_hs1_MuPtRel_All",1200,400);
  Canvas_hs1_MuPtRel_All->Divide(3,1);//colum x row
  
  Canvas_hs1_MuPtRel_All->cd(1);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hs1_MuPtRel_All->Draw("hist");
  Canvas_hs1_MuPtRel_All->Update();
  hs1_MuPtRel_All->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");
  hs1_MuPtRel_All->GetYaxis()->SetTitle("Entries");
  hist_MuPtRel_Inclusive->Draw("same");
  lgd_hs1_MuPtRel_All->Draw("same");
  
  Canvas_hs1_MuPtRel_All->cd(2);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hs1_MuPtRel_CSVTag_All->Draw("hist");
  hs1_MuPtRel_CSVTag_All->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");
  hs1_MuPtRel_CSVTag_All->GetYaxis()->SetTitle("Entries");
  hist_MuPtRel_CSVTag_Inclusive->Draw("same");
  lgd_hs1_MuPtRel_All->Draw("same");
  tb->DrawLatex(0.7,0.65,"CSVv2>0.9");

  Canvas_hs1_MuPtRel_All->cd(3);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.2);
  hs1_MuPtRel_CSVVeto_All->Draw("hist");
  hs1_MuPtRel_CSVVeto_All->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");
  hs1_MuPtRel_CSVVeto_All->GetYaxis()->SetTitle("Entries");
  hist_MuPtRel_CSVVeto_Inclusive->Draw("same");
  lgd_hs1_MuPtRel_All->Draw("same");
  tb->DrawLatex(0.7,0.65,"CSVv2<0.9");


  Canvas_hs1_MuPtRel_All->SaveAs("Plots/CSVPlots/hs1_MuPtRel_All.pdf");
  Canvas_hs1_MuPtRel_All->SaveAs("Plots/CSVPlots/hs1_MuPtRel_All.png");

  //======================================================================================//
  //============= The Goal is to make muon-pT Rel histo with different muon pt cuts =====//
  //======================================================================================//
  
  //Get the 4D Histogram of MuonJetPt, Muon Pt Relative, Jet Flavour and Muon Pt 
  THnSparseD *hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt=(THnSparseD*)file_in->Get("hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt");

  //first set the range for axis you want to project



  // Define arrays to help find the histograms
  //int nRestrictionAxes = 3;
  //int axisIndices[3] = {0};
  //int lowLimits[3] = {0};
  //int highLimits[3] = {0};
  
  //project this to get the muon pt relative distribution
  Int_t nRestrictionAxes = 3; // restricted axes are CSV, Flavour and MuonPt 
  Int_t axisIndices[3]={0,2,3}; //0 CSV, 1 pt rel, 2 Flavour, 3 muon pt
  Double_t lowLimits[3]={0.0,1,5.0}; // low limit for CSV, Flavour, MuonPt
  Double_t highLimits[3]={1.2,6,100.0}; // high limit for CSV, Flavour, MuonPt




  // Muon pT Cuts
  const Int_t NMuonPtCut = 4;
  const Double_t MuonPtCut[NMuonPtCut]={5.0,12.5,16.0,20.0};



  TH1D* hist_MuPtRel_Inclusive_FromSparse[NMuonPtCut]; // histogram for inclusive
  TH1D* hist_MuPtRel_Light_FromSparse[NMuonPtCut]; // histogram for Light flavour (u,d,s)
  TH1D* hist_MuPtRel_Gluon_FromSparse[NMuonPtCut]; // histogram for gluon
  TH1D* hist_MuPtRel_Charm_FromSparse[NMuonPtCut]; // histogram for charm
  TH1D* hist_MuPtRel_Beauty_FromSparse[NMuonPtCut]; // histogram for beauty     



  //csv tag histograms
  TH1D* hist_MuPtRel_CSVTag_Inclusive_FromSparse[NMuonPtCut]; // histogram for inclusive
  TH1D* hist_MuPtRel_CSVTag_Light_FromSparse[NMuonPtCut]; // histogram for Light flavour (u,d,s)
  TH1D* hist_MuPtRel_CSVTag_Gluon_FromSparse[NMuonPtCut]; // histogram for gluon
  TH1D* hist_MuPtRel_CSVTag_Charm_FromSparse[NMuonPtCut]; // histogram for charm
  TH1D* hist_MuPtRel_CSVTag_Beauty_FromSparse[NMuonPtCut]; // histogram for beauty     


  //csv veto histograms
  TH1D* hist_MuPtRel_CSVVeto_Inclusive_FromSparse[NMuonPtCut]; // histogram for inclusive
  TH1D* hist_MuPtRel_CSVVeto_Light_FromSparse[NMuonPtCut]; // histogram for Light flavour (u,d,s)
  TH1D* hist_MuPtRel_CSVVeto_Gluon_FromSparse[NMuonPtCut]; // histogram for gluon
  TH1D* hist_MuPtRel_CSVVeto_Charm_FromSparse[NMuonPtCut]; // histogram for charm
  TH1D* hist_MuPtRel_CSVVeto_Beauty_FromSparse[NMuonPtCut]; // histogram for beauty     


  
  
  for(int i=0;i<NMuonPtCut;i++){



    // reset the cuts to their initial values
    lowLimits[0]=0; highLimits[0]=1.2;
    lowLimits[1]=1; highLimits[1]=6;
    lowLimits[2]=0.0; highLimits[2]=100.0;
    
    //putting the muon pt min cut on sparse
    //lowLimits[CSV,Flavour,MuonPt]
    //lowLimits[0,1,2]
    lowLimits[2]= MuonPtCut[i]; 
    
        
    //four histograms of muon pt rel, no cut on csv, Light jet flavour, muon pt min cut
    //Int_t axisIndices[3]={0,2,3}; //0 CSV, 1 pt rel, 2 Flavour, 3 muon pt (so we can put cuts on CSV, Flavour, muon pt)
    
    //lowLimits[CSV,Flavour,MuonPt]
    //highLimits[CSV,Flavour,MuonPt]

    //for inclusive
    lowLimits[1]=1; highLimits[1]=6;
    hist_MuPtRel_Inclusive_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);
    
    //for light
    lowLimits[1]=1; highLimits[1]=3;
    hist_MuPtRel_Light_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //for gluons
    lowLimits[1]=6; highLimits[1]=6; 
    hist_MuPtRel_Gluon_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //for charm
    lowLimits[1]=4; highLimits[1]=4; 
    hist_MuPtRel_Charm_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //for beauty
    lowLimits[1]=5; highLimits[1]=5; 
    hist_MuPtRel_Beauty_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //Add the gluon histogram to the Light
    hist_MuPtRel_Light_FromSparse[i]->Add(hist_MuPtRel_Gluon_FromSparse[i]);
    
    hist_MuPtRel_Light_FromSparse[i]->SetFillColor(kBlue);
    hist_MuPtRel_Charm_FromSparse[i]->SetFillColor(kGreen);
    hist_MuPtRel_Beauty_FromSparse[i]->SetFillColor(kRed);


    // making the csv tag plots 
    // reset the cuts to their initial values
    lowLimits[0]=0; highLimits[0]=1.2;
    lowLimits[1]=1; highLimits[1]=6;
    lowLimits[2]=0.0; highLimits[2]=100.0;

    //set the muon pt cut
    lowLimits[2]= MuonPtCut[i];


    //set the CSVV2 cut (can be done for all)
    lowLimits[0]= CSVWorkingPoint; highLimits[0]=1.0;
    //set the flavour cut : inclusive
    lowLimits[1]=1; highLimits[1]=6;
    hist_MuPtRel_CSVTag_Inclusive_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //set the flavour cut : Light
    lowLimits[1]=1; highLimits[1]=3;
    hist_MuPtRel_CSVTag_Light_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //set the flavour cut : Gluon
    lowLimits[1]=6; highLimits[1]=6;
    hist_MuPtRel_CSVTag_Gluon_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //set the flavour cut : Charm
    lowLimits[1]=4; highLimits[1]=4;
    hist_MuPtRel_CSVTag_Charm_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //set the flavour cut : Beauty
    lowLimits[1]=5; highLimits[1]=5;
    hist_MuPtRel_CSVTag_Beauty_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    hist_MuPtRel_CSVTag_Light_FromSparse[i]->Add(hist_MuPtRel_CSVTag_Gluon_FromSparse[i]);
    
    hist_MuPtRel_CSVTag_Light_FromSparse[i]->SetFillColor(kBlue);
    hist_MuPtRel_CSVTag_Charm_FromSparse[i]->SetFillColor(kGreen);
    hist_MuPtRel_CSVTag_Beauty_FromSparse[i]->SetFillColor(kRed);






    

    // making the csv veto plots 
    // reset the cuts to their initial values
    lowLimits[0]=0; highLimits[0]=1.2;
    lowLimits[1]=1; highLimits[1]=6;
    lowLimits[2]=0.0; highLimits[2]=100.0;

    //set the muon pt cut
    lowLimits[2]= MuonPtCut[i];


    //set the CSVV2 cut (can be done for all)
    lowLimits[0]= 0.0; highLimits[0] = CSVWorkingPoint;
    //set the flavour cut : inclusive
    lowLimits[1]=1; highLimits[1]=6;
    hist_MuPtRel_CSVVeto_Inclusive_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //set the flavour cut : Light
    lowLimits[1]=1; highLimits[1]=3;
    hist_MuPtRel_CSVVeto_Light_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //set the flavour cut : Gluon
    lowLimits[1]=6; highLimits[1]=6;
    hist_MuPtRel_CSVVeto_Gluon_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //set the flavour cut : Charm
    lowLimits[1]=4; highLimits[1]=4;
    hist_MuPtRel_CSVVeto_Charm_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    //set the flavour cut : Beauty
    lowLimits[1]=5; highLimits[1]=5;
    hist_MuPtRel_CSVVeto_Beauty_FromSparse[i] =  CSVTagMethod->FindHistogram(file_in,"hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt",1, nRestrictionAxes,axisIndices,lowLimits,highLimits);

    hist_MuPtRel_CSVVeto_Light_FromSparse[i]->Add(hist_MuPtRel_CSVVeto_Gluon_FromSparse[i]);
    
    hist_MuPtRel_CSVVeto_Light_FromSparse[i]->SetFillColor(kBlue);
    hist_MuPtRel_CSVVeto_Charm_FromSparse[i]->SetFillColor(kGreen);
    hist_MuPtRel_CSVVeto_Beauty_FromSparse[i]->SetFillColor(kRed);




    
    
        
  }// muon pt cut




  
  //CREATE AN ARRAY OF STACKS FOR HISTOGRAMS WITH MUON PT CUTS (Muon pT-Rel histograms (Light {udsg} c and b})
  THStack *hs_MuPtRel_MuPtCuts[NMuonPtCut];

  // Make a Canvas to plot the muon pT relative histograms
  TCanvas *Canvas_MuPtRel_MuPtCuts = new TCanvas("Canvas_MuPtRel_MuPtCuts","Canvas_MuPtRel_MuPtCuts",800,800);
  Canvas_MuPtRel_MuPtCuts->Divide(2,2);//column x row
    
  
  for(int i=0;i<NMuonPtCut;i++)
    {

      hs_MuPtRel_MuPtCuts[i] = new THStack(Form("hs_MuPtRel_MuPtCuts_%d",i),Form("hs_MuPtRel_MuPtCuts_%d",i));
      hs_MuPtRel_MuPtCuts[i]->Add(hist_MuPtRel_Light_FromSparse[i]);
      hs_MuPtRel_MuPtCuts[i]->Add(hist_MuPtRel_Charm_FromSparse[i]);
      hs_MuPtRel_MuPtCuts[i]->Add(hist_MuPtRel_Beauty_FromSparse[i]);

      Canvas_MuPtRel_MuPtCuts->cd(i+1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      hs_MuPtRel_MuPtCuts[i]->Draw("hist");
      Canvas_MuPtRel_MuPtCuts->Update();
      hs_MuPtRel_MuPtCuts[i]->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");
      hs_MuPtRel_MuPtCuts[i]->GetYaxis()->SetTitle("Entries");
      hist_MuPtRel_Inclusive_FromSparse[i]->Draw("Psame");
      lgd_hs1_MuPtRel_All->Draw("same");
      tb->DrawLatex(0.65,0.65,Form("#mu p_{T} > %0.1f GeV",MuonPtCut[i]));

    }
  
  Canvas_MuPtRel_MuPtCuts->SaveAs("Plots/CSVPlots/MuPtRel_MuPtCuts.pdf");
  Canvas_MuPtRel_MuPtCuts->SaveAs("Plots/CSVPlots/MuPtRel_MuPtCuts.png");
  





  //CREATE AN ARRAY OF STACKS FOR CSV Tag HISTOGRAMS WITH MUON PT CUTS (Muon pT-Rel histograms (Light {udsg} c and b})

  THStack *hs_MuPtRel_CSVTag_MuPtCuts[NMuonPtCut];

  // Make a Canvas to plot the muon pT relative histograms
  TCanvas *Canvas_MuPtRel_CSVTag_MuPtCuts = new TCanvas("Canvas_MuPtRel_CSVTag_MuPtCuts","Canvas_MuPtRel_CSVTag_MuPtCuts",800,800);
  Canvas_MuPtRel_CSVTag_MuPtCuts->Divide(2,2);//column x row
    
  
  for(int i=0;i<NMuonPtCut;i++)
    {

      hs_MuPtRel_CSVTag_MuPtCuts[i] = new THStack(Form("hs_MuPtRel_CSVTag_MuPtCuts_%d",i),Form("hs_MuPtRel_CSVTag_MuPtCuts_%d",i));
      hs_MuPtRel_CSVTag_MuPtCuts[i]->Add(hist_MuPtRel_CSVTag_Light_FromSparse[i]);
      hs_MuPtRel_CSVTag_MuPtCuts[i]->Add(hist_MuPtRel_CSVTag_Charm_FromSparse[i]);
      hs_MuPtRel_CSVTag_MuPtCuts[i]->Add(hist_MuPtRel_CSVTag_Beauty_FromSparse[i]);

      Canvas_MuPtRel_CSVTag_MuPtCuts->cd(i+1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      hs_MuPtRel_CSVTag_MuPtCuts[i]->Draw("hist");
      Canvas_MuPtRel_CSVTag_MuPtCuts->Update();
      hs_MuPtRel_CSVTag_MuPtCuts[i]->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");
      hs_MuPtRel_CSVTag_MuPtCuts[i]->GetYaxis()->SetTitle("Entries");
      hist_MuPtRel_CSVTag_Inclusive_FromSparse[i]->Draw("Psame");
      lgd_hs1_MuPtRel_All->Draw("same");
      tb->DrawLatex(0.65,0.65,Form("csv v2 > %0.1f",CSVWorkingPoint));
      tb->DrawLatex(0.65,0.60,Form("#mu p_{T} > %0.1f GeV",MuonPtCut[i]));

    }
  
  Canvas_MuPtRel_CSVTag_MuPtCuts->SaveAs("Plots/CSVPlots/MuPtRel_CSVTag_MuPtCuts.pdf");
  Canvas_MuPtRel_CSVTag_MuPtCuts->SaveAs("Plots/CSVPlots/MuPtRel_CSVTag_MuPtCuts.png");
  
 


  


  
  //CREATE AN ARRAY OF STACKS FOR CSV Veto HISTOGRAMS WITH MUON PT CUTS (Muon pT-Rel histograms (Light {udsg} c and b})

  THStack *hs_MuPtRel_CSVVeto_MuPtCuts[NMuonPtCut];

  // Make a Canvas to plot the muon pT relative histograms
  TCanvas *Canvas_MuPtRel_CSVVeto_MuPtCuts = new TCanvas("Canvas_MuPtRel_CSVVeto_MuPtCuts","Canvas_MuPtRel_CSVVeto_MuPtCuts",800,800);
  Canvas_MuPtRel_CSVVeto_MuPtCuts->Divide(2,2);//column x row
    
  
  for(int i=0;i<NMuonPtCut;i++)
    {

      hs_MuPtRel_CSVVeto_MuPtCuts[i] = new THStack(Form("hs_MuPtRel_CSVVeto_MuPtCuts_%d",i),Form("hs_MuPtRel_CSVVeto_MuPtCuts_%d",i));
      hs_MuPtRel_CSVVeto_MuPtCuts[i]->Add(hist_MuPtRel_CSVVeto_Light_FromSparse[i]);
      hs_MuPtRel_CSVVeto_MuPtCuts[i]->Add(hist_MuPtRel_CSVVeto_Charm_FromSparse[i]);
      hs_MuPtRel_CSVVeto_MuPtCuts[i]->Add(hist_MuPtRel_CSVVeto_Beauty_FromSparse[i]);

      Canvas_MuPtRel_CSVVeto_MuPtCuts->cd(i+1);
      gPad->SetTopMargin(0.1);
      gPad->SetBottomMargin(0.2);
      hs_MuPtRel_CSVVeto_MuPtCuts[i]->Draw("hist");
      Canvas_MuPtRel_CSVVeto_MuPtCuts->Update();
      hs_MuPtRel_CSVVeto_MuPtCuts[i]->GetXaxis()->SetTitle("Muon p_{T}^{Rel} (GeV/c)");
      hs_MuPtRel_CSVVeto_MuPtCuts[i]->GetYaxis()->SetTitle("Entries");
      hist_MuPtRel_CSVVeto_Inclusive_FromSparse[i]->Draw("Psame");
      lgd_hs1_MuPtRel_All->Draw("same");
      tb->DrawLatex(0.65,0.65,Form("csv v2 < %0.1f",CSVWorkingPoint));
      tb->DrawLatex(0.65,0.60,Form("#mu p_{T} > %0.1f GeV",MuonPtCut[i]));

    }
  
  Canvas_MuPtRel_CSVVeto_MuPtCuts->SaveAs("Plots/CSVPlots/MuPtRel_CSVVeto_MuPtCuts.pdf");
  Canvas_MuPtRel_CSVVeto_MuPtCuts->SaveAs("Plots/CSVPlots/MuPtRel_CSVVeto_MuPtCuts.png");


  
  



  //TH2* hist_MuPtRel_MuPt_FromSparse =  (TH2*)hsparse_Master_JetCSV_MuPtRel_Flavour_MuPt->Projection(1,3);
  //new TCanvas;
  //hist_MuPtRel_MuPt_FromSparse->Draw("colz");





  //=============================================================================//
  //================= making a latex table for the Jet Fractions ===============//
  //===========================================================================//
  
  char OutTexFile[1000];
  sprintf(OutTexFile,"OutTexFile/CSVTable/CSVTable.tex");
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
  dataFile<<Str3<<"caption{Rec Jet Fraction (Muon-Jets) from muon pT relative templates}"<<endl;
  dataFile<<Str3<<"label{}"<<endl;
  
  dataFile<<Str3<<"begin{tabular}{|cc|}"<<endl;
  dataFile<<Str1<<endl;


  
  dataFile<<"Type"<<" &Fraction"<<Str2<<endl;

  dataFile<<Str1<<endl;
    
  dataFile<<" Total "<<" &"<<setprecision(4)<<fixed << Frac_MuPtRel_Inc <<Str2<<endl;

  dataFile<<"  u "<<" &"<<setprecision(4)<<fixed <<  Frac_MuPtRel_U <<Str2<<endl;
  dataFile<<"  d "<<" &"<<setprecision(4)<<fixed <<  Frac_MuPtRel_D <<Str2<<endl;
  dataFile<<"  s "<<" &"<<setprecision(4)<<fixed <<  Frac_MuPtRel_S <<Str2<<endl;
  dataFile<<"  c "<<" &"<<setprecision(4)<<fixed <<  Frac_MuPtRel_C <<Str2<<endl;
  dataFile<<"  b "<<" &"<<setprecision(4)<<fixed <<  Frac_MuPtRel_B <<Str2<<endl;
  dataFile<<"  g "<<" &"<<setprecision(4)<<fixed <<  Frac_MuPtRel_G <<Str2<<endl;
  
  dataFile<<Str1<<endl;
  dataFile<<Str3<<"end{tabular}"<<endl;
  dataFile<<Str3<<"end{center}"<<endl;
  dataFile<<Str3<<"end{table}"<<endl;
  dataFile<<endl<<endl<<endl;

  dataFile<<Str3<<"end{document}"<<endl<<endl;
  




  








  

  //=================================================================================//
  //============ write histograms in output file ===================================//
  //=================================================================================//
  
  file_out->cd();


  // create a subdirectory "CSVTagPlots" in the output root file
  TDirectory *cd_csvplots = file_out->mkdir("CSVTagPlots");
  cd_csvplots->cd();    // make the "tof" directory the current directory

  
  Canvas_hs1_MuPtRel_All->Write();

  CSVTagMethod->MakeHistogramNameToHistogramTitle(hist_MuPtRel_Light);
  CSVTagMethod->MakeHistogramNameToHistogramTitle(hist_MuPtRel_B);
  CSVTagMethod->MakeHistogramNameToHistogramTitle(hist_MuPtRel_C);

  CSVTagMethod->MakeHistogramNameToHistogramTitle(hist_MuPtRel_CSVTag_Light);
  CSVTagMethod->MakeHistogramNameToHistogramTitle(hist_MuPtRel_CSVTag_B);
  CSVTagMethod->MakeHistogramNameToHistogramTitle(hist_MuPtRel_CSVTag_C);

  
  CSVTagMethod->MakeHistogramNameToHistogramTitle(hist_MuPtRel_CSVVeto_Light);
  CSVTagMethod->MakeHistogramNameToHistogramTitle(hist_MuPtRel_CSVVeto_B);
  CSVTagMethod->MakeHistogramNameToHistogramTitle(hist_MuPtRel_CSVVeto_C);

  CSVTagMethod->MakeHistogramNameToHistogramTitle(hist_MuPtRel_Inclusive);


  hist_MuPtRel_Inclusive->Write();
  hist_MuPtRel_Light->Write();
  hist_MuPtRel_B->Write();
  hist_MuPtRel_C->Write();

  hist_MuPtRel_CSVTag_Inclusive->Write();
  hist_MuPtRel_CSVTag_Light->Write();
  hist_MuPtRel_CSVTag_B->Write();
  hist_MuPtRel_CSVTag_C->Write();

  hist_MuPtRel_CSVVeto_Inclusive->Write();
  hist_MuPtRel_CSVVeto_Light->Write();
  hist_MuPtRel_CSVVeto_B->Write();
  hist_MuPtRel_CSVVeto_C->Write();
  
  file_out->cd();
  
  return;


}
