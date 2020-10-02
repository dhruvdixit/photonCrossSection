#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TGraphAsymmErrors.h"
//#include "TTreeReader.h"
//#include "TTreeReaderValue.h"
#include "TMath.h"
#include "TVector2.h"
//#include "/root/atlasstyle-00-03-05/AtlasStyle.h"
//#include "/root/atlasstyle-00-03-05/AtlasStyle.C"
//#include "/root/atlasstyle-00-03-05/AtlasUtils.h"
//#include "/root/atlasstyle-00-03-05/AtlasUtils.C"
//#include "/root/atlasstyle-00-03-05/AtlasLabels.h"
//#include "/root/atlasstyle-00-03-05/AtlasLabels.C"
#include "TDatabasePDG.h"
#include "TEfficiency.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bitset>
#include <bits/stdc++.h>
#include <cstring>

void calcNormClusterSpectraRF_pPb(){

  gStyle->SetCanvasColor(-1);
  gStyle->SetPadColor(-1);
  gStyle->SetFrameFillColor(-1);
  gStyle->SetHistFillColor(-1);
  gStyle->SetTitleFillColor(-1);
  gStyle->SetFillColor(-1);
  gStyle->SetFillStyle(4000);
  gStyle->SetStatStyle(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/";

  //13d
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/StdEventsAndClusterCuts/fout_6_26bins_forRTrigEG_13d_Allruns_noThresh_phySel_noNorm.root", path.Data()), "READ");

  //13e
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/StdEventsAndClusterCuts/fout_6_26bins_forRTrigEG_13e_Allruns_noThresh_phySel_noNorm.root", path.Data()), "READ");

  //13f
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/StdEventsAndClusterCuts/fout_6_26bins_forRTrigEG_13f_Allruns_noThresh_phySel_noNorm.root", path.Data()), "READ");

  //13def
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/StdEventsAndClusterCuts/fout_7_26bins_forRTrigMB_13def_Allruns_noThresh_phySel_noNorm.root", path.Data()), "READ");
  
  //13cdef
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/StdEventsAndClusterCuts/fout_7_26bins_forRTrigMB_13cdef_Allruns_noThresh_phySel_noNorm.root", path.Data()), "READ");

  if(!fin){
    cout << "Can't find file" << endl;
    return;
  }

  TH1F* hMB_E = (TH1F*)fin->Get("hMB_E");
  TH1F* hEG1_E = (TH1F*)fin->Get("hEG1_E");
  TH1F* hEG2_E = (TH1F*)fin->Get("hEG2_E");
  TH1F* hNormalizer = (TH1F*)fin->Get("hNormalizer");

  Double_t numEvents_MB = hNormalizer->GetBinContent(11);
  Double_t numEvents_EG1 = hNormalizer->GetBinContent(12);
  Double_t numEvents_EG2 = hNormalizer->GetBinContent(13);
  cout << "Number of MB events: " << numEvents_MB << endl;
  cout << "Number of EG1 events: " << numEvents_EG1 << endl;
  cout << "Number of EG2 events: " << numEvents_EG2 << endl;
  const double deltaEta = 1.334;
  const double deltaPhi = 1.884;
  double acceptanceNorm = 2*TMath::Pi()/(deltaEta*deltaPhi);

  //MB cluster spectra
  for(int i = 1; i < hMB_E->GetNbinsX()+1; i++){
    double dE = hMB_E->GetBinWidth(i);
    
    double contentMB = hMB_E->GetBinContent(i);
    double tempMB = (contentMB)/((double)numEvents_MB*dE);
    double errorMB = hMB_E->GetBinError(i);
    double tempErrMB = (errorMB)/((double)numEvents_MB*dE);
    if(numEvents_MB) 
      {
	hMB_E->SetBinContent(i,tempMB);
	hMB_E->SetBinError(i, tempErrMB);
      }
    
  }//*/
  
  //EG1 cluster spectra
  for(int i = 1; i < hEG1_E->GetNbinsX()+1; i++){
    double dE = hEG1_E->GetBinWidth(i);
    
    double contentEG1 = hEG1_E->GetBinContent(i);
    double tempEG1 = (contentEG1)/((double)numEvents_EG1*dE);
    double errorEG1 = hEG1_E->GetBinError(i);
    double tempErrEG1 = (errorEG1)/((double)numEvents_EG1*dE);
    if(numEvents_EG1) 
      {
	hEG1_E->SetBinContent(i,tempEG1);
	hEG1_E->SetBinError(i, tempErrEG1);
      }
    
  }//*/  

  //EG2 cluster spectra
  for(int i = 1; i < hEG2_E->GetNbinsX()+1; i++){
    double dE = hEG2_E->GetBinWidth(i);
    
    double contentEG2 = hEG2_E->GetBinContent(i);
    double tempEG2 = (contentEG2)/((double)numEvents_EG2*dE);
    double errorEG2 = hEG2_E->GetBinError(i);
    double tempErrEG2 = (errorEG2)/((double)numEvents_EG2*dE);
    if(numEvents_EG2) 
      {
	hEG2_E->SetBinContent(i,tempEG2);
	hEG2_E->SetBinError(i, tempErrEG2);
      }
    
  }//*/

  hMB_E->SetLineColor(kBlack);
  hMB_E->SetMarkerColor(kBlack);
  hMB_E->SetMarkerStyle(21);
  hMB_E->SetMarkerSize(2);
  
  hEG1_E->SetLineColor(kRed);
  hEG1_E->SetMarkerColor(kRed);
  hEG1_E->SetMarkerStyle(21);
  hEG1_E->SetMarkerSize(2);

  hEG2_E->SetLineColor(kGreen);
  hEG2_E->SetMarkerColor(kGreen);
  hEG2_E->SetMarkerStyle(21);
  hEG2_E->SetMarkerSize(2);

  TLegend* legYield = new TLegend(0.6,0.7,0.85,0.85);
  legYield->SetHeader("Photon Yield");
  legYield->AddEntry(hMB_E,"pPb MB");
  legYield->AddEntry(hEG1_E,"pPb EG1");
  legYield->AddEntry(hEG2_E,"pPb EG2");

  TCanvas* c1 = new TCanvas();
  c1->SetLogy();
  hMB_E->Draw("e1");
  hEG1_E->Draw("samee1");
  hEG2_E->Draw("samee1");
  legYield->Draw("same");

  TString filename = fin->GetName();
  Int_t index = filename.Index("_noNorm");
  filename.Replace(index, 7, "");
  if(filename.CompareTo(fin->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hMB_E->Write("hMB_E");
    hEG1_E->Write("hEG1_E");
    hEG2_E->Write("hEG2_E");
    hNormalizer->Write("hNormalizer");
    fout->Close();
  }//end filename compare
  
}
