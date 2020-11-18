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

void combinePlots_ppCutStudies(){

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
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/rfOutput/ppOutput/";
  
  TFile* file365 = new TFile(Form("%sfout_5_26bins_17q_CENT_wSDD_noThresh_r282365_physel_forRTrig_MBEG2exlusion_tof20_eCross5.root", path.Data()), "READ");
  TFile* file366 = new TFile(Form("%sfout_5_26bins_17q_CENT_wSDD_noThresh_r282366_physel_forRTrig_MBEG2exlusion_tof20_eCross5.root", path.Data()), "READ");
  TFile* file367 = new TFile(Form("%sfout_5_26bins_17q_CENT_wSDD_noThresh_r282367_physel_forRTrig_MBEG2exlusion_tof20_eCross5.root", path.Data()), "READ");
  
  
    
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
  
  
  TH1F* hEG2_caloE = (TH1F*)eg366->Clone();
  TH1F* hNormalizer = (TH1F*)n366->Clone();
  hEG2_caloE->SetName("hEG2_caloE");
  hNormalizer->SetName("hNormalizer");

  hNormalizer->Add(n365);
  hNormalizer->Add(n367);
  
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

    cout << egContent << "\t" << egError << endl; 
    hEG2_caloE->SetBinContent(i, egContent);
    hEG2_caloE->SetBinError(i, egError);

  }

  hEG2_caloE->SetLineColor(kOrange);
  hEG2_caloE->SetMarkerColor(kOrange);
  hEG2_caloE->SetMarkerStyle(kFullCircle);


    /*hCluster_tof
  hCluster_tof20GeV
  hExoticity
  hNcell
  hNLM
  hD2BC
  hEta
  hPhi*/

  TH1F* hCluster_tof365 = (TH1F*)file365->Get("hCluster_tof");
  TH1F* hCluster_tof366 = (TH1F*)file366->Get("hCluster_tof");
  TH1F* hCluster_tof367 = (TH1F*)file367->Get("hCluster_tof");
  hCluster_tof365->SetName("hCluster_tof365");
  hCluster_tof366->SetName("hCluster_tof366");
  hCluster_tof367->SetName("hCluster_tof367");
  TH1F* hCluster_tof = (TH1F*)hCluster_tof365->Clone();
  hCluster_tof->SetName("hCluster_tof");
  hCluster_tof->Add(hCluster_tof366);
  hCluster_tof->Add(hCluster_tof367);

  TH1F* hExoticity365 = (TH1F*)file365->Get("hExoticity");
  TH1F* hExoticity366 = (TH1F*)file366->Get("hExoticity");
  TH1F* hExoticity367 = (TH1F*)file367->Get("hExoticity");
  hExoticity365->SetName("hExoticity365");
  hExoticity366->SetName("hExoticity366");
  hExoticity367->SetName("hExoticity367");
  TH1F* hExoticity = (TH1F*)hExoticity365->Clone();
  hExoticity->SetName("hExoticity");
  hExoticity->Add(hExoticity366);
  hExoticity->Add(hExoticity367);

  TH1F* hNcell365 = (TH1F*)file365->Get("hNcell");
  TH1F* hNcell366 = (TH1F*)file366->Get("hNcell");
  TH1F* hNcell367 = (TH1F*)file367->Get("hNcell");
  hNcell365->SetName("hNcell365");
  hNcell366->SetName("hNcell366");
  hNcell367->SetName("hNcell367");
  TH1F* hNcell = (TH1F*)hNcell365->Clone();
  hNcell->SetName("hNcell");
  hNcell->Add(hNcell366);
  hNcell->Add(hNcell367);

  TH1F* hNLM365 = (TH1F*)file365->Get("hNLM");
  TH1F* hNLM366 = (TH1F*)file366->Get("hNLM");
  TH1F* hNLM367 = (TH1F*)file367->Get("hNLM");
  hNLM365->SetName("hNLM365");
  hNLM366->SetName("hNLM366");
  hNLM367->SetName("hNLM367");
  TH1F* hNLM = (TH1F*)hNLM365->Clone();
  hNLM->SetName("hNLM");
  hNLM->Add(hNLM366);
  hNLM->Add(hNLM367);

  TH1F* hD2BC365 = (TH1F*)file365->Get("hD2BC");
  TH1F* hD2BC366 = (TH1F*)file366->Get("hD2BC");
  TH1F* hD2BC367 = (TH1F*)file367->Get("hD2BC");
  hD2BC365->SetName("hD2BC365");
  hD2BC366->SetName("hD2BC366");
  hD2BC367->SetName("hD2BC367");
  TH1F* hD2BC = (TH1F*)hD2BC365->Clone();
  hD2BC->SetName("hD2BC");
  hD2BC->Add(hD2BC366);
  hD2BC->Add(hD2BC367);

  TH1F* hEta365 = (TH1F*)file365->Get("hEta");
  TH1F* hEta366 = (TH1F*)file366->Get("hEta");
  TH1F* hEta367 = (TH1F*)file367->Get("hEta");
  hEta365->SetName("hEta365");
  hEta366->SetName("hEta366");
  hEta367->SetName("hEta367");
  TH1F* hEta = (TH1F*)hEta365->Clone();
  hEta->SetName("hEta");
  hEta->Add(hEta366);
  hEta->Add(hEta367);

  TH1F* hPhi365 = (TH1F*)file365->Get("hPhi");
  TH1F* hPhi366 = (TH1F*)file366->Get("hPhi");
  TH1F* hPhi367 = (TH1F*)file367->Get("hPhi");
  hPhi365->SetName("hPhi365");
  hPhi366->SetName("hPhi366");
  hPhi367->SetName("hPhi367");
  TH1F* hPhi = (TH1F*)hPhi365->Clone();
  hPhi->SetName("hPhi");
  hPhi->Add(hPhi366);
  hPhi->Add(hPhi367);



  
  TString filename = file365->GetName();
  Int_t index = filename.Index("r282365");
  filename.Replace(index, 7, "all");
  if(filename.CompareTo(file365->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    
    hEG2_caloE->Write("hEG2_caloE");
    hNormalizer->Write("hNormalizer");

    hCluster_tof->Write("hCluster_tof");
    hExoticity->Write("hExoticity");
    hNcell->Write("hNcell");
    hNLM->Write("hNLM");
    hD2BC->Write("hD2BC");
    hEta->Write("hEta");
    hPhi->Write("hPhi");

    fout->Close();
    
  }//end filename compare

  
  
}//end combinePlots
