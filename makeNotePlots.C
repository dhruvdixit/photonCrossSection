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

void makeNotePlots(){

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
  

  TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_50Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_hCorr_corr_stdCuts.root","READ");

  TFile* mcFile_pp = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/18b10a_Allevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_hCorr_corr_stdCuts.root","READ");

  TH1D* hEfficiency_pPb = (TH1D*)mcFile_pPb->Get("hEfficiency");
  hEfficiency_pPb->SetName("hEfficiency_pPb");
  hEfficiency_pPb->SetTitle(";E_{T} [GeV]; #epsilon");
  hEfficiency_pPb->SetLineColor(kRed);
  hEfficiency_pPb->SetMarkerColor(kRed);
  hEfficiency_pPb->SetMarkerStyle(kFullCircle);
  hEfficiency_pPb->GetYaxis()->SetRangeUser(0,1);
  hEfficiency_pPb->GetXaxis()->SetRangeUser(12,60);
  
  TH1D* hRecoEfficiency_pPb = (TH1D*)mcFile_pPb->Get("hRecoEfficiency");
  hRecoEfficiency_pPb->SetName("hRecoEfficiency_pPb");
  hRecoEfficiency_pPb->SetTitle(";E_{T} [GeV]; #epsilon");
  hRecoEfficiency_pPb->SetLineColor(kOrange);
  hRecoEfficiency_pPb->SetMarkerColor(kOrange);
  hRecoEfficiency_pPb->SetMarkerStyle(kFullCircle);
    
  TH1D* hISOEfficiency_pPb = (TH1D*)mcFile_pPb->Get("hISOEfficiency");
  hISOEfficiency_pPb->SetName("hISOEfficiency_pPb");
  hISOEfficiency_pPb->SetTitle(";E_{T} [GeV]; #epsilon");
  hISOEfficiency_pPb->SetLineColor(kCyan);
  hISOEfficiency_pPb->SetMarkerColor(kCyan);
  hISOEfficiency_pPb->SetMarkerStyle(kFullCircle);

  TH1D* hSSCEfficiency_pPb = (TH1D*)mcFile_pPb->Get("hSSCEfficiency");
  hSSCEfficiency_pPb->SetName("hSSCEfficiency_pPb");
  hSSCEfficiency_pPb->SetTitle(";E_{T} [GeV]; #epsilon");
  hSSCEfficiency_pPb->SetLineColor(kGreen);
  hSSCEfficiency_pPb->SetMarkerColor(kGreen);
  hSSCEfficiency_pPb->SetMarkerStyle(kFullCircle);


  TLegend* lpPb = new TLegend(0.2, 0.2, 0.8, 0.5);
  lpPb->SetBorderSize(0);
  lpPb->AddEntry((TObject*)0, "ALICE Simulation, p-Pb #sqrt{s_{NN}} = 5.02", "");
  lpPb->AddEntry(hEfficiency_pPb, "Isolated Photon Efficiency = #epsilon_{reco} x #epsilon_{iso} x #epsilon_{ssc}");
  lpPb->AddEntry(hRecoEfficiency_pPb, "Reconstruction Efficiency (#epsilon_{reco})");
  lpPb->AddEntry(hISOEfficiency_pPb, "Isolation  Efficiency (#epsilon_{iso})");
  lpPb->AddEntry(hSSCEfficiency_pPb, "Shower Shape Efficiency (#epsilon_{ssc})");
  
  TCanvas* cpPb = new TCanvas();
  hEfficiency_pPb->Draw("e1");
  hRecoEfficiency_pPb->Draw("samee1");
  hISOEfficiency_pPb->Draw("samee1");
  hSSCEfficiency_pPb->Draw("samee1");
  lpPb->Draw("same");


  /*****************************************************************************


  pp efficiency


   ***************************************************************************/
  
  TH1D* hEfficiency_pp = (TH1D*)mcFile_pp->Get("hEfficiency");
  hEfficiency_pp->SetName("hEfficiency_pp");
  hEfficiency_pp->SetTitle(";E_{T} [GeV]; #epsilon");
  hEfficiency_pp->SetLineColor(kBlue);
  hEfficiency_pp->SetMarkerColor(kBlue);
  hEfficiency_pp->SetMarkerStyle(kFullCircle);
  hEfficiency_pp->GetYaxis()->SetRangeUser(0,1);
  hEfficiency_pp->GetXaxis()->SetRangeUser(12,60);
  
  TH1D* hRecoEfficiency_pp = (TH1D*)mcFile_pp->Get("hRecoEfficiency");
  hRecoEfficiency_pp->SetName("hRecoEfficiency_pp");
  hRecoEfficiency_pp->SetTitle(";E_{T} [GeV]; #epsilon");
  hRecoEfficiency_pp->SetLineColor(kOrange);
  hRecoEfficiency_pp->SetMarkerColor(kOrange);
  hRecoEfficiency_pp->SetMarkerStyle(kFullCircle);
    
  TH1D* hISOEfficiency_pp = (TH1D*)mcFile_pp->Get("hISOEfficiency");
  hISOEfficiency_pp->SetName("hISOEfficiency_pp");
  hISOEfficiency_pp->SetTitle(";E_{T} [GeV]; #epsilon");
  hISOEfficiency_pp->SetLineColor(kCyan);
  hISOEfficiency_pp->SetMarkerColor(kCyan);
  hISOEfficiency_pp->SetMarkerStyle(kFullCircle);

  TH1D* hSSCEfficiency_pp = (TH1D*)mcFile_pp->Get("hSSCEfficiency");
  hSSCEfficiency_pp->SetName("hSSCEfficiency_pp");
  hSSCEfficiency_pp->SetTitle(";E_{T} [GeV]; #epsilon");
  hSSCEfficiency_pp->SetLineColor(kGreen);
  hSSCEfficiency_pp->SetMarkerColor(kGreen);
  hSSCEfficiency_pp->SetMarkerStyle(kFullCircle);


  TLegend* lpp = new TLegend(0.2, 0.2, 0.8, 0.5);
  lpp->SetBorderSize(0);
  lpp->AddEntry((TObject*)0, "ALICE Simulation, pp #sqrt{s_{NN}} = 5.02", "");
  lpp->AddEntry(hEfficiency_pp, "Isolated Photon Efficiency = #epsilon_{reco} x #epsilon_{iso} x #epsilon_{ssc}");
  lpp->AddEntry(hRecoEfficiency_pp, "Reconstruction Efficiency (#epsilon_{reco})");
  lpp->AddEntry(hISOEfficiency_pp, "Isolation  Efficiency (#epsilon_{iso})");
  lpp->AddEntry(hSSCEfficiency_pp, "Shower Shape Efficiency (#epsilon_{ssc})");
  
  TCanvas* cpp = new TCanvas();
  hEfficiency_pp->Draw("e1");
  hRecoEfficiency_pp->Draw("samee1");
  hISOEfficiency_pp->Draw("samee1");
  hSSCEfficiency_pp->Draw("samee1");
  lpp->Draw("same");

  TLegend* lComp = new TLegend(0.2, 0.2, 0.8, 0.5);
  lComp->SetBorderSize(0);
  lComp->AddEntry((TObject*)0, "ALICE Simulation, #sqrt{s_{NN}} = 5.02", "");
  lComp->AddEntry((TObject*)0, "Isolated Photon Efficiency = #epsilon_{reco} x #epsilon_{iso} x #epsilon_{ssc}", "");
  lComp->AddEntry(hEfficiency_pp, "pp");
  lComp->AddEntry(hEfficiency_pPb, "p-Pb");

  TCanvas* cComp = new TCanvas();
  hEfficiency_pp->Draw("e1");
  hEfficiency_pPb->Draw("samee1");
  lComp->Draw("same");





}//end macro
