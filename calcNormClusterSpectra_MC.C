#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TVector2.h"
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

void calcNormClusterSpectra_MC(){

  //gStyle->SetCanvasColor(-1);
  //gStyle->SetPadColor(-1);
  //gStyle->SetFrameFillColor(-1);
  //gStyle->SetHistFillColor(-1);
  //gStyle->SetTitleFillColor(-1);
  gStyle->SetFillColor(-1);
  gStyle->SetFillStyle(4000);
  gStyle->SetStatStyle(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetOptStat(0);
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/";

  
  
  //17g6a1
  TFile* fin = new TFile(Form("%s17g6a1/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutrals_noNorm.root", path.Data()), "READ");
  
  if(!fin){
    cout << "Can't find file" << endl;
    return;
  }

  TH1F* hReco = (TH1F*)fin->Get("hReco");
  TH1F* hRecoTruth = (TH1F*)fin->Get("hRecoTruth");
  TH1F* hTruth = (TH1F*)fin->Get("hTruth");
  hReco->Sumw2();
  hRecoTruth->Sumw2();
  hTruth->Sumw2();

  const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning
  TH1F* hTotalEfficiency = new TH1F("hTotalEfficiency", ";p_{T}^{rec} [GeV/c]#\epsilon^{iso}_{#gamma}", nbinscluster, clusterbins);
  TH1F* hEfficiency = new TH1F("hEfficiency", ";p_{T}^{tru} [GeV/c];#epsilon^{iso}_{#gamma}", nbinscluster, clusterbins);
  TH1F* hBinMigration = new TH1F("hBinMigration", ";p_{T}^{rec} [GeV/c]; reco/truth", nbinscluster, clusterbins);

  
  
  //Total Efficiency
  for(int i = 1; i < hTotalEfficiency->GetNbinsX()+1; i++){
    double dE = hTotalEfficiency->GetBinWidth(i);
    
    double dNdE_Reco = (hReco->GetBinContent(i))/(dE);
    double dNdE_Truth = (hTruth->GetBinContent(i))/(dE);
    double totEff = dNdE_Reco/dNdE_Truth;
    hTotalEfficiency->SetBinContent(i, totEff);
    
    double error_Reco = (hReco->GetBinError(i))/(dE);
    double error_Truth = (hTruth->GetBinError(i))/(dE);
    double totEffError = TMath::Sqrt(TMath::Power(error_Reco,2) + TMath::Power(error_Truth,2));
    hTotalEfficiency->SetBinError(i, totEffError);

    
  }//*/  

  TCanvas* c1 = new TCanvas();
  hTotalEfficiency->GetYaxis()->SetRangeUser(0,1);
  hTotalEfficiency->Draw("e1");
  TString filename = fin->GetName();
  Int_t index = filename.Index("_noNorm");
  filename.Replace(index, 7, "");
  if(filename.CompareTo(fin->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hTotalEfficiency->Write("hTotalEfficiency");

    fout->Close();
  }//end filename compare*/
  
}
