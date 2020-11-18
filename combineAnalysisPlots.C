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

void combineAnalysisPlots(){

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

  
  TFile* file365 = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_CENT_wSDD_noThresh_r282365_physel_CALOonly_tof10.root", path.Data()), "READ");
  TFile* file366 = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_CENT_wSDD_noThresh_r282366_physel_CALOonly_tof10.root", path.Data()), "READ");
  TFile* file367 = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_CENT_wSDD_noThresh_r282367_physel_CALOonly_tof10.root", path.Data()), "READ");

  
    
  if(!file365)
    {
      cout << "Run 365 file not found" << endl;
      return;
    }

  if(!file366)
    {
      cout << "Run 366 file not found" << endl;
      return;
    }
  if(!file367)
    {
      cout << "Run 367 file not found" << endl;
      return;
    }

  TH1F* eg365 = (TH1F*)file365->Get("hEG2_caloE");
  TH1F* eg366 = (TH1F*)file366->Get("hEG2_caloE");
  TH1F* eg367 = (TH1F*)file367->Get("hEG2_caloE");
  eg365->SetName("eg365");
  eg366->SetName("eg366");
  eg367->SetName("eg367");

  TH1F* n365 = (TH1F*)file365->Get("hNormalizer");
  TH1F* n366 = (TH1F*)file366->Get("hNormalizer");
  TH1F* n367 = (TH1F*)file367->Get("hNormalizer");
  n365->SetName("n365");
  n366->SetName("n366");
  n367->SetName("n367");

  Double_t numEG365 = n365->GetBinContent(8);
  Double_t numEG366 = n366->GetBinContent(8);
  Double_t numEG367 = n367->GetBinContent(8);
  

  TH1F* hEG2_caloE = (TH1F*)eg365->Clone();
  TH1F* hNormalizer = (TH1F*)n365->Clone();
  hEG2_caloE->SetName("hEG2_caloE");
  hNormalizer->SetName("hNormalizer");

  //hNormalizer->Add(n366);
  //hNormalizer->Add(n367);
  Double_t numEGtot = numEG365+numEG366+numEG367;

  for(int i = 1; i < hEG2_caloE->GetNbinsX()+1; i++){

    Double_t tmpEG365 = eg365->GetBinContent(i);
    Double_t tmpEG366 = eg366->GetBinContent(i);
    Double_t tmpEG367 = eg367->GetBinContent(i);

    Double_t errEG365 = eg365->GetBinError(i);
    Double_t errEG366 = eg366->GetBinError(i);
    Double_t errEG367 = eg367->GetBinError(i);


    Double_t egContent = (tmpEG365*numEG365+tmpEG366*numEG366+tmpEG367*numEG367)/numEGtot;

    
    Double_t egError = TMath::Sqrt((TMath::Power(errEG365*numEG365, 2)+TMath::Power(errEG366*numEG366,2)+TMath::Power(errEG367*numEG367,2)))/numEGtot;

    hEG2_caloE->SetBinContent(i, egContent);
    hEG2_caloE->SetBinError(i, egError);

    
  }

  for(int i = 1; i < hNormalizer->GetNbinsX()+1; i++){
    Double_t events = n365->GetBinContent(i)+n365->GetBinContent(i)+n365->GetBinContent(i);
    hNormalizer->SetBinContent(i, events);

  
  }
  
  TCanvas* cs = new TCanvas("cs", "cs");
  cs->SetLogy();
  hEG2_caloE->Draw("e1");

  
  TString filename = file365->GetName();
  Int_t index = filename.Index("r282365");
  filename.Replace(index, 7, "all");
  if(filename.CompareTo(file365->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hEG2_caloE->Write("hEG2_caloE");
    hNormalizer->Write("hNormalizer");
    fout->Close();
  }//end filename compare
}//end combinePlots
