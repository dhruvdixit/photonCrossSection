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
  //TFile* fin = new TFile(Form("%s17g6a1/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutrals_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/SystematicCheck/CutVariation/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsLooseCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/SystematicCheck/CutVariation/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsTightCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/SystematicCheck/IsoEffect/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsIso1_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/SystematicCheck/IsoEffect/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsIso2_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/SystematicCheck/ShowerShape/fout_14bins_firstEvent0_17g6a1_wNeutralsShowerShapeMaxPoint33_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/SystematicCheck/ShowerShape/fout_14bins_firstEvent0_17g6a1_wNeutralsShowerShapeMaxPoint27_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/FullStats/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsFullStats_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/EfficiencySystematics/35/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsSSC35_noNorm.root", path.Data()), "READ");

  //18b10a
  //TFile* fin = new TFile(Form("%s18b10a/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutrals_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/SystematicCheck/CutVariation/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsLooseCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/SystematicCheck/CutVariation/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsTightCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/SystematicCheck/IsoEffect/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsIso1_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/SystematicCheck/IsoEffect/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsIso2_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/SystematicCheck/ShowerShape/fout_14bins_firstEvent0_18b10a_calo_wNeutralsShowerShapeMaxPoint33_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/SystematicCheck/ShowerShape/fout_14bins_firstEvent0_18b10a_calo_wNeutralsShowerShapeMaxPoint27_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/FullStats/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsFullStats_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/EfficiencySystematics/26/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsSSC26_noNorm.root", path.Data()), "READ");

  
  if(!fin){
    cout << "Can't find file" << endl;
    return;
  }

  TH1F* hReco = (TH1F*)fin->Get("hReco");
  TH1F* hRecoTruth = (TH1F*)fin->Get("hRecoTruth");
  TH1F* hTruth = (TH1F*)fin->Get("hTruth");
  TH2F* hCorrelation = (TH2F*)fin->Get("hCorrelation");
  hReco->Sumw2();
  hRecoTruth->Sumw2();
  hTruth->Sumw2();
  hCorrelation->Sumw2();

  const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning
  TH1F* hTotalEfficiency = new TH1F("hTotalEfficiency", ";p_{T}^{rec} [GeV/c];#epsilon^{iso}_{#gamma}", nbinscluster, clusterbins);
  TH1F* hEfficiency = new TH1F("hEfficiency", ";p_{T}^{tru} [GeV/c];#epsilon^{iso}_{#gamma}", nbinscluster, clusterbins);
  TH1F* hBinMigration = new TH1F("hBinMigration", ";p_{T}^{rec} [GeV/c]; truth/reco", nbinscluster, clusterbins);

  TH1F* truth = (TH1F*)hCorrelation->ProjectionX("truth");
  TH1F* reco = (TH1F*)hCorrelation->ProjectionY("reco");
  truth->Sumw2();
  reco->Sumw2();
  //Bin Migration
  for(int i = 1; i < hBinMigration->GetNbinsX()+1; i++){
    double dE = hBinMigration->GetBinWidth(i);
    
    double dNdE_Reco = (reco->GetBinContent(i))/(dE);
    double dNdE_Truth = (truth->GetBinContent(i))/(dE);
    double totEff = dNdE_Truth/dNdE_Reco;
    reco->SetBinContent(i, dNdE_Reco);
    truth->SetBinContent(i, dNdE_Truth);
    hBinMigration->SetBinContent(i, totEff);
    
    double error_Reco = (reco->GetBinError(i))/(dE);
    double error_Truth = (truth->GetBinError(i))/(dE);
    double totEffError = totEff*(TMath::Sqrt(TMath::Power(error_Reco,2) + TMath::Power(error_Truth,2)));
    hBinMigration->SetBinError(i, totEffError);
  }//*/

  reco->SetLineColor(kRed);
  reco->SetMarkerColor(kRed);
  reco->SetMarkerStyle(kFullCircle);
  truth->SetLineColor(kBlue);
  truth->SetMarkerColor(kBlue);
  truth->SetMarkerStyle(kFullCircle);
  TLegend* lBM = new TLegend(0.5, 0.7, 0.9, 0.87);
  lBM->SetHeader("5 TeV p-Pb GJ MC 17g6a1");
  lBM->AddEntry(reco, "reco");
  lBM->AddEntry(truth, "truth");

  TCanvas* stuff = new TCanvas("stuff", "stuff", 500, 500);
  stuff->SetLogy();
  reco->GetXaxis()->SetRangeUser(12,60);
  reco->Draw("e1");
  truth->Draw("samee1");
  lBM->Draw("same");
  
  TCanvas* cBM = new TCanvas("cBM", "cBM", 1500, 500);
  cBM->SetLogz();
  cBM->Divide(3);
  cBM->cd(1);
  //cBM->cd(2);
  hCorrelation->Draw("colz");
  cBM->cd(3);
  hBinMigration->GetYaxis()->SetRangeUser(0,1.5);
  hBinMigration->GetXaxis()->SetRangeUser(12,60);
  hBinMigration->Draw("e1");

  //Total Efficiency
  for(int i = 1; i < hTotalEfficiency->GetNbinsX()+1; i++){
    double dE = hTotalEfficiency->GetBinWidth(i);
    
    double dNdE_Reco = (hReco->GetBinContent(i))/(dE);
    double dNdE_Truth = (hTruth->GetBinContent(i))/(dE);
    double totEff = dNdE_Reco/dNdE_Truth;
    hTotalEfficiency->SetBinContent(i, totEff);
    
    double error_Reco = (hReco->GetBinError(i))/(dE);
    double error_Truth = (hTruth->GetBinError(i))/(dE);
    double totEffError = totEff*(TMath::Sqrt(TMath::Power(error_Reco,2) + TMath::Power(error_Truth,2)));
    hTotalEfficiency->SetBinError(i, totEffError);

    
  }//*/  

  hTotalEfficiency->SetLineColor(kRed+2);
  hTotalEfficiency->SetMarkerColor(kRed+2);
  hTotalEfficiency->SetMarkerStyle(kFullCircle);

  TLine *line = new TLine(12, 0.5, 60, 0.5);
  line->SetLineColor(kBlack);
  
  TCanvas* cEff = new TCanvas();
  hTotalEfficiency->GetYaxis()->SetRangeUser(0,1);
  hTotalEfficiency->GetXaxis()->SetRangeUser(12,60);
  hTotalEfficiency->Draw("e1");
  line->Draw("same");

  TString filename = fin->GetName();
  Int_t index = filename.Index("_noNorm");
  filename.Replace(index, 7, "");
  if(filename.CompareTo(fin->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hTotalEfficiency->Write("hTotalEfficiency");
    hCorrelation->Write("hCorrelation");
    reco->Write("reco");
    truth->Write("truth");
    hBinMigration->Write("hBinMigration");
    fout->Close();
  }//end filename compare*/
  
}
