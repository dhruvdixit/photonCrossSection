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

void combinePlots(){

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

  TFile* file365 = new TFile(Form("%sfout_5_26bins_17q_CENT_wSDD_noThresh_r282365_physel_forRTrig_noMBEG2exlusion_Foregroundcc_tof30.root", path.Data()), "READ");
  TFile* file366 = new TFile(Form("%sfout_5_26bins_17q_CENT_wSDD_noThresh_r282366_physel_forRTrig_noMBEG2exlusion_Foregroundcc_tof30.root", path.Data()), "READ");
  TFile* file367 = new TFile(Form("%sfout_5_26bins_17q_CENT_wSDD_noThresh_r282367_physel_forRTrig_noMBEG2exlusion_Foregroundcc_tof30.root", path.Data()), "READ");
  
    
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

  TH1F* mb365 = (TH1F*)file365->Get("hMB_centE");
  TH1F* mb366 = (TH1F*)file366->Get("hMB_centE");
  TH1F* mb367 = (TH1F*)file367->Get("hMB_centE");
  mb365->SetName("mb365");
  mb366->SetName("mb366");
  mb367->SetName("mb367");

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
  Double_t numMB365 = n365->GetBinContent(9);
  Double_t numEG366 = n366->GetBinContent(8);
  Double_t numMB366 = n366->GetBinContent(9);
  Double_t numEG367 = n367->GetBinContent(8);
  Double_t numMB367 = n367->GetBinContent(9);
  
  TH1F* hMB_centE = (TH1F*)eg366->Clone();
  TH1F* hEG2_caloE = (TH1F*)eg366->Clone();
  TH1F* hRF = (TH1F*)eg366->Clone();
  TH1F* hNormalizer = (TH1F*)n366->Clone();
  hMB_centE->SetName("hMB_centE");
  hEG2_caloE->SetName("hEG2_caloE");
  hRF->SetName("hRF");
  hNormalizer->SetName("hNormalizer");

  hNormalizer->Add(n365);
  hNormalizer->Add(n367);
  Double_t numMBtot = numMB365+numMB366+numMB367;
  Double_t numEGtot = numEG365+numEG366+numEG367;

  for(int i = 1; i < hMB_centE->GetNbinsX()+1; i++){

    Double_t tmpMB365 = mb365->GetBinContent(i);
    Double_t tmpMB366 = mb366->GetBinContent(i);
    Double_t tmpMB367 = mb367->GetBinContent(i);
    Double_t tmpEG365 = eg365->GetBinContent(i);
    Double_t tmpEG366 = eg366->GetBinContent(i);
    Double_t tmpEG367 = eg367->GetBinContent(i);

    Double_t errMB365 = mb365->GetBinError(i);
    Double_t errMB366 = mb366->GetBinError(i);
    Double_t errMB367 = mb367->GetBinError(i);
    Double_t errEG365 = eg365->GetBinError(i);
    Double_t errEG366 = eg366->GetBinError(i);
    Double_t errEG367 = eg367->GetBinError(i);

    Double_t mbContent = (tmpMB365*numMB365+tmpMB366*numMB366+tmpMB367*numMB367)/numMBtot;
    Double_t egContent = (tmpEG365*numEG365+tmpEG366*numEG366+tmpEG367*numEG367)/numEGtot;

    Double_t mbError = TMath::Sqrt((TMath::Power(errMB365*numMB365, 2)+TMath::Power(errMB366*numMB366,2)+TMath::Power(errMB367*numMB367,2)))/numMBtot;
    Double_t egError = TMath::Sqrt((TMath::Power(errEG365*numEG365, 2)+TMath::Power(errEG366*numEG366,2)+TMath::Power(errEG367*numEG367,2)))/numEGtot;

    hMB_centE->SetBinContent(i, mbContent);
    hMB_centE->SetBinError(i, mbError);
    hEG2_caloE->SetBinContent(i, egContent);
    hEG2_caloE->SetBinError(i, egError);

    if(mbContent != 0.0){
      Double_t rfContent = egContent/mbContent;
      Double_t rfError = rfContent*(TMath::Sqrt(TMath::Power(mbError/mbContent,2)+TMath::Power(egError/egContent,2)));
      hRF->SetBinContent(i, rfContent);
      hRF->SetBinError(i, rfError);
    }
  }

  hEG2_caloE->SetLineColor(kOrange);
  hMB_centE->SetLineColor(kViolet);
  hEG2_caloE->SetMarkerColor(kOrange);
  hMB_centE->SetMarkerColor(kViolet);
  hEG2_caloE->SetMarkerStyle(kFullCircle);
  hMB_centE->SetMarkerStyle(kFullCircle);
  
  
  TLegend* ls = new TLegend(0.6, 0.6,0.85, 0.85);
  ls->AddEntry((TObject*)0, "17q: Runs 282365-282367", "");
  ls->AddEntry((TObject*)0, "EMC Good runs, TPC+ITS acceptance", "");
  ls->AddEntry(hMB_centE, "Minimum bias spectra");
  ls->AddEntry(hEG2_caloE, "EG2 calo spectra");
			    
  TCanvas* cs = new TCanvas("cs", "cs");
  cs->SetLogy();
  hMB_centE->GetYaxis()->SetRangeUser(1e-9, 1);
  hMB_centE->Draw("e1");
  hEG2_caloE->Draw("samee1");
  ls->Draw("same");

  hRF->SetLineColor(kBlue);
  hRF->SetMarkerColor(kBlue);
  hRF->SetMarkerStyle(kFullCircle);
  hRF->SetTitle(";E_{T} (GeV); R_{trig}");
  TCanvas* cr = new TCanvas("cr", "cr");
  cr->SetLogy();
  hRF->GetXaxis()->SetRangeUser(0.0, 40.0);
  hRF->Draw("e1");

  TString filename = file365->GetName();
  Int_t index = filename.Index("r282365");
  filename.Replace(index, 7, "all");
  Int_t index2 = filename.Index("isoPhotonOutput");
  filename.Replace(index2, 15, "rfOutput");
  if(filename.CompareTo(file365->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hMB_centE->Write("hMB_centE");
    hEG2_caloE->Write("hEG2_caloE");
    hRF->Write("hRF");
    hNormalizer->Write("hNormalizer");
    fout->Close();
  }//end filename compare











  hRF->Fit("pol0", "", "", 10, 40);

  
  
}//end combinePlots
