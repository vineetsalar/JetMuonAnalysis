#include "MyMethod.h"

/*
 *  Constructor
 */
MyMethod::MyMethod() {}


/*
 *  Destructor
 */
MyMethod::~MyMethod() {}



TH1D *MyMethod::RatioHistogram(TH1 *InHistNum, TH1 *InHistDeno, Int_t RebinFac)
{

  TH1D *temp_Num = (TH1D*)InHistNum->Clone("temp_Num");
  TH1D *temp_Deno = (TH1D*)InHistDeno->Clone("temp_Deno");

  temp_Num->Rebin(RebinFac);
  temp_Deno->Rebin(RebinFac);

  temp_Num->Divide(temp_Num,temp_Deno,1.0,1.0,"B");

  return temp_Num;


}



void MyMethod::ScaleHistByItsIntegral(TH1 *InHist)
{
  Double_t Integral_Val = InHist->Integral(); 
  Double_t ScaleFac = 1.0/Integral_Val;
  InHist->Scale(ScaleFac);

}





void MyMethod::FlavouredHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize)
{
  
  InHist->SetLineColor(LineColor);
  InHist->SetMarkerColor(MarkerColor);
  InHist->SetMarkerStyle(MarkerStyle);
  InHist->SetMarkerSize(MarkerSize);
  InHist->GetXaxis()->SetNdivisions(505);
  InHist->GetXaxis()->SetLabelSize(0.06);
  InHist->GetXaxis()->SetTitleOffset(1.4);
  InHist->GetXaxis()->SetTitleSize(0.06);
  InHist->GetYaxis()->SetTitleSize(0.06);
  
}







void MyMethod::DrawFlavourLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index)
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






void MyMethod::DrawFlavourLegendUn(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index)
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









void MyMethod::DrawFlavourLegendVertical(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index)
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



TLegend *MyMethod::MyLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2)
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



  TH1D *MyMethod::Get_Ghost_Hist(const char *Name, const char *Title, Double_t YMin, Double_t YMax, const char *XTitle, const char *YTitle)
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
bool MyMethod::checkBinBoundaries(const int nCheckedBins, const double *checkedBins, TAxis *originalAxis){

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


void MyMethod::rebinAsymmetric(TH1* histogram, const int nBins, const double* binEdges){



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



void MyMethod::PrintGraph(TGraph *GraphIn)
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






/*
 * Extract a histogram with given restrictions on other axes in THnSparse
 *
 *  Arguments:
 *   TFile *inputFile = Inputfile containing the THnSparse to be read
 *   const char *name = Name of the THnSparse that is read
 *   int xAxis = Index for the axis in THnSparse that is projected to x-axis for TH1D
 *   int nAxes = Number of axes that are restained for the projection
 *   int *axisNumber = Indices for the axes in THnSparse that are used as a restriction for the projection
 *   int *lowBinIndex = Indices of the lowest considered bins in the restriction axis
 *   int *highBinIndex = Indices of the highest considered bins in the restriction axis
 */

TH1D* MyMethod::FindHistogram(TFile *inputFile, const char *name, int xAxis, int nAxes, int *axisNumber, double *lowBinIndex, double *highBinIndex){
  
  // Read the histogram with the given name from the file
  THnSparseD *histogramArray = (THnSparseD*)inputFile->Get(name);
  
  // If cannot find histogram, inform that it could not be found and return null
  if(histogramArray == nullptr){
    cout << "Could not find " << name << ". Skipping loading this histogram." << endl;
    return NULL;
  }
  
  // Apply the restrictions in the set of axes
  for(int i = 0; i < nAxes; i++)
    {
      //histogramArray->GetAxis(axisNumber[i])->SetRange(lowBinIndex[i],highBinIndex[i]);
      //give the values directly instead of the bin number 
      histogramArray->GetAxis(axisNumber[i])->SetRange(histogramArray->GetAxis(axisNumber[i])->FindBin(lowBinIndex[i]),histogramArray->GetAxis(axisNumber[i])->FindBin(highBinIndex[i]));
    }
  
  // Create a unique name for each histogram that is read from the file
  char newName[200];
  sprintf(newName,"%s",histogramArray->GetName());
  for(int iBinIndex = 0; iBinIndex < nAxes; iBinIndex++){
    sprintf(newName,"%s_%d=%f-%f",newName,axisNumber[iBinIndex],lowBinIndex[iBinIndex],highBinIndex[iBinIndex]);
  }

  // Project out the histogram and give it the created unique name
  TH1D *projectedHistogram = NULL;
  
  // Check that we are not trying to project a non-existing axis
  if(xAxis < histogramArray->GetNdimensions()){
    projectedHistogram = (TH1D*) histogramArray->Projection(xAxis);
    projectedHistogram->SetName(newName);
  
    // Apply bin width normalization to the projected histogram
    //projectedHistogram->Scale(1.0,"width");
  }
  
  // Return the projected histogram
  return projectedHistogram;
}



void MyMethod::MakeHistogramNameToHistogramTitle(TH1 *inHist)
{
  inHist->SetTitle(inHist->GetName());


}




void MyMethod::GlamorizeHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize)
{

  InHist->SetLineColor(LineColor);
  InHist->SetMarkerColor(MarkerColor);
  InHist->SetMarkerStyle(MarkerStyle);
  InHist->SetMarkerSize(MarkerSize);
  InHist->GetXaxis()->SetNdivisions(505);
  InHist->GetXaxis()->SetLabelSize(0.06);
  InHist->GetXaxis()->SetTitleOffset(1.4);
  InHist->GetXaxis()->SetTitleSize(0.06);
  InHist->GetYaxis()->SetTitleSize(0.06);
 


}


