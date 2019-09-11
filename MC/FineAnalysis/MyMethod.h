#ifndef MYMETHOD_H
#define MYMETHOD_H
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include <iostream>
#include "THnSparse.h"

class MyMethod{
  
 public:
  MyMethod();   // Constructor
  ~MyMethod();  // Destructor


  // some common variables
  static const int NFlavour =6;
  const Int_t LineColorArray[NFlavour+1]={0,3,7,6,4,2,1};
  const Int_t MarkerColorArray[NFlavour+1]={0,3,7,6,4,2,1};
  const Int_t MarkerStyleArray[NFlavour+1]={0,46,30,38,33,21,24};
  const Float_t MarkerSizeArray[NFlavour+1]={0,1.5,1.5,1.5,1.8,1.4,1.4};

  /*
  //===== Bins for Asymmatric binning of Gen Jet pT
  static const int NBins_GenJetPt_VarSize=12;
  //bin boundry matching with the original histogram bin boundry
  const Double_t GenJetPtBinEdges[NBins_GenJetPt_VarSize]={31.5,40.5,63.0,81.0,103.5,130.5,162.0,202.5,252.0,301.5,351.0,445.5};


  //===== Bins for Asymmatric binning of muon pT
  static const int NBins_GenMuonPt_VarSize=13;
  //bin boundry matching with the original histogram bin boundry
  const Double_t GenMuonPtBinEdges[NBins_GenMuonPt_VarSize]={1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 14.0, 18.0, 22.0, 30.0, 40.0, 60.0, 100.0};
  
  
  
  //===== Bins for Asymmatric binning of Jet pT
  static const int NBins_JetPt_VarSize=12;
  //bin boundry matching with the original histogram bin boundry
  const Double_t JetPtBinEdges[NBins_JetPt_VarSize]={31.5,40.5,63.0,81.0,103.5,130.5,162.0,202.5,252.0,301.5,351.0,445.5};
  */



  /**************************************************************************/
  //changing the binning to match with data
  /*************************************************************************/
  //===== Bins for Asymmatric binning of Gen Jet pT
  static const int NBins_GenJetPt_VarSize=16;
  //bin boundry matching with the original histogram bin boundry
  const Double_t GenJetPtBinEdges[NBins_GenJetPt_VarSize]={60.0, 65.0, 70.0, 75.0, 80.0,85.0,90.0,100.0,120.0,140.0,160.0,200.0,240.0,320.0,400.0,499.0};


  //===== Bins for Asymmatric binning of muon pT
  static const int NBins_GenMuonPt_VarSize=13;
  //bin boundry matching with the original histogram bin boundry
  const Double_t GenMuonPtBinEdges[NBins_GenMuonPt_VarSize]={1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 14.0, 18.0, 22.0, 30.0, 40.0, 60.0, 100.0};
  
  
  //===== Bins for Asymmatric binning of Jet pT
  static const int NBins_JetPt_VarSize=16;
  Double_t JetPtBinEdges[NBins_JetPt_VarSize]={60.0, 65.0, 70.0, 75.0, 80.0,85.0,90.0,100.0,120.0,140.0,160.0,200.0,240.0,320.0,400.0,499.0};
  
  
  TH1D *RatioHistogram(TH1 *InHistNum, TH1 *InHistDeno, Int_t RebinFac); //make ratio of two histograms
  void ScaleHistByItsIntegral(TH1 *InHist); //scale histogram by integral
  void FlavouredHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize);//make the histograms beautiful

  Int_t Flv_Legend_Index = 0;
  void DrawFlavourLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index); // draw the horizontal flavour histogram

  Int_t Flv_Legend_Index_V=0;
  void DrawFlavourLegendUn(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index);// draw the horizontal flavour histogram unknown flv
  void DrawFlavourLegendVertical(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Int_t index);// draw the verticl flavour histogram
  TLegend *MyLegend(Double_t x1, Double_t y1, Double_t x2, Double_t y2);//return a legend with set properties
  TH1D *Get_Ghost_Hist(const char *Name, const char *Title, Double_t YMin, Double_t YMax, const char *XTitle, const char *YTitle);//ghost histo for Jet Pt
  bool checkBinBoundaries(const int nCheckedBins, const double *checkedBins, TAxis *originalAxis);//Checker that new bin boundaries correspond to old ones
  void rebinAsymmetric(TH1* histogram, const int nBins, const double* binEdges);// Rebin one dimensional histogram with asymmetric bin edges
  void PrintGraph(TGraph *GraphIn);//print graph content
  
  //Extract a histogram with given restrictions on other axes in THnSparse
  TH1D* FindHistogram(TFile *inputFile, const char *name, int xAxis, int nAxes, int *axisNumber, double *lowBinIndex, double *highBinIndex);
  
  void MakeHistogramNameToHistogramTitle(TH1 *inHist);
  void GlamorizeHistogram(TH1 *InHist, Int_t LineColor, Int_t MarkerColor, Int_t MarkerStyle, Float_t MarkerSize);

  
};

#endif
