#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TVector2.h"
#include "TDatabasePDG.h"
#include "TEfficiency.h"

/*#include <algorithm>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bitset>
#include <bits/stdc++.h>
#include <cstring>//*/

void calcNormClusterSpectra_MC(){

  //gStyle->SetCanvasColor(-1);
  //gStyle->SetPadColor(-1);
  //gStyle->SetFrameFillColor(-1);
  //gStyle->SetHistFillColor(-1);
  //gStyle->SetTitleFillColor(-1);
  /*gStyle->SetFillColor(-1);
  gStyle->SetFillStyle(4000);
  gStyle->SetStatStyle(0);
  gStyle->SetTitleStyle(0);//*/
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);  
  

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
  //TFile* fin = new TFile(Form("%s17g6a1/ISO133/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsISO1Point33_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/GenISO/StdCuts/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/ARCComments/PerpConeUE/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheck_ParallelUECone_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/ARCComments/PerpConeUE/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutrals_woCrossTalkStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheck_ParallelUECone_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/ARCComments/PerpConeUE/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheck_PerpUECone_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/ARCComments/ConeAcceptanceCheck/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheckMore4Eta_PerpUECone_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/ARCComments/ConeAcceptanceCheck/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheckLess4Eta_PerpUECone_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/ARCComments/ConeAcceptanceCheck/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheckLess4Eta_PerpUECone_ClusterCutHistAfterCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s17g6a1/fout_14bins_firstEvent0_18b10a_calo_pthat2_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheckMore4Eta_PerpUECone_ClusterCutHistAfterCuts_noNorm.root", path.Data()), "READ");
  TFile* fin = new TFile(Form("%s17g6a1/Nonlin/With_ElecPositron/fout_14bins_firstEvent0_17g6a1_pthatAll_1run_wNL_GeMomentumFixedStdCuts_AddedElectronPositron_100KEvents_noNorm.root", path.Data()), "READ");
  
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
  //TFile* fin = new TFile(Form("%s18b10a/GenIso/StdCuts/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/GenIso/AddedLowpTCut/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/GenIso/AddedEelectron/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheck_AddedElectron_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/ARCComments/ConeAcceptanceCheck/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheck_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/ARCComments/PerpConeUE/fout_14bins_firstEvent0_18b10a_pthatAll_wNeutrals_woCrossTalkStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheck_PerpUECone_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/ARCComments/PerpConeUE/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheck_ParallelUECone_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/ARCComments/ConeAcceptanceCheck/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheckMore4Eta_PerpUECone_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/ARCComments/ConeAcceptanceCheck/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheckLess4Eta_PerpUECone_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/ARCComments/ConeAcceptanceCheck/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheckMore4Eta_PerpUECone_ClusterCutHistAfterCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%s18b10a/Nonlin/GetMomentumFixed/fout_14bins_firstEvent0_18b10a_pthatAll_2runs_wNL_GeMomentumFixedStdCuts_OldNewReCheck100KEvents_noNorm.root", path.Data()), "READ");//wNL first look 100k events compare
  //TFile* fin = new TFile(Form("%s18b10a/Nonlin/OldNewCompare/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_OldNewReCheck100KEvents_noNorm.root", path.Data()), "READ");//old woNL 100k events compare
  //TFile* fin = new TFile(Form("%s18b10a/Nonlin/With_ElecPositron/woNL/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_AddedElectronPositron_100KEvents_noNorm.root", path.Data()), "READ");//woNL we+e-
  //TFile* fin = new TFile(Form("%s18b10a/Nonlin/With_ElecPositron/wNL/fout_14bins_firstEvent0_18b10a_pthatAll_2runs_wNL_GeMomentumFixedStdCuts_AddedElectronPositron_100KEvents_noNorm.root", path.Data()), "READ");//wNL we+e-
  
  //18g7a pp JJ
  //TFile* fin = new TFile(Form("%s18g7a/fout_14bins_firstEvent0_18g7a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_noNorm.root", path.Data()), "READ");

  
  if(!fin){
    cout << "Can't find file" << endl;
    return;
  }

  TH1F* hRecoTruth = (TH1F*)fin->Get("hRecoTruth");
  TH2F* hCorrelation = (TH2F*)fin->Get("hCorrelation");
  //TH1F* hTruth_pp = (TH1F*)fin->Get("hTruth");

  TH1F* hReco = (TH1F*)fin->Get("hReco");
  TH1F* hTruth = (TH1F*)fin->Get("hTruth");
  TH1F* hTruthIsolated = (TH1F*)fin->Get("hTruthIsolated");//*/
  /*TH1F* hReco = (TH1F*)fin->Get("hRecoLess4Eta");
  TH1F* hTruth = (TH1F*)fin->Get("hTruthLess4Eta");
  TH1F* hTruthIsolated = (TH1F*)fin->Get("hTruthIsolatedLess4Eta");//*/
  /*TH1F* hReco = (TH1F*)fin->Get("hRecoMore4Eta");
  TH1F* hTruth = (TH1F*)fin->Get("hTruthMore44Eta");
  TH1F* hTruthIsolated = (TH1F*)fin->Get("hTruthIsolatedMore4Eta");//*/
  hReco->Sumw2();
  hRecoTruth->Sumw2();
  hTruth->Sumw2();
  //hTruth_pp->Sumw2();
  hTruthIsolated->Sumw2();
  hCorrelation->Sumw2();

  const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning
  TH1F* hTotalEfficiency = new TH1F("hTotalEfficiency", ";p_{T}^{rec} [GeV/c];#varepsilon^{iso}_{#gamma}", nbinscluster, clusterbins);
  TH1F* hEfficiency = new TH1F("hEfficiency", ";p_{T}^{tru} [GeV/c];#varepsilon^{iso}_{#gamma}", nbinscluster, clusterbins);
  TH1F* hIsoEfficiency = new TH1F("hIsoEfficiency", ";p_{T}^{tru} [GeV/c];#varepsilon^{iso}_{#gamma}", nbinscluster, clusterbins);
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
  lBM->SetHeader("ALICE Simulation, 18b10a G-J, pp #sqrt{s_{NN}} = 5.02 TeV");
  lBM->AddEntry(reco, "reco");
  lBM->AddEntry(truth, "truth");

  TCanvas* cBM = new TCanvas("cBM", "cBM", 1500, 500);
  cBM->Divide(3);
  cBM->cd(1);
  gPad->SetLogz();
  hCorrelation->Draw("colz");
  cBM->cd(2);
  gPad->SetLogy();
  reco->Draw("e1");
  truth->Draw("samee1");
  lBM->Draw("same");
  cBM->cd(3);
  hBinMigration->GetYaxis()->SetRangeUser(0,1.5);
  hBinMigration->GetXaxis()->SetRangeUser(12,60);
  hBinMigration->Draw("e1");
  //cBM->SaveAs("binMigration_pp.pdf");

  //Reco Efficiency
  cout << "Reco Efficiency" << endl; 
  for(int i = 1; i < hEfficiency->GetNbinsX()+1; i++){
    double dE = hEfficiency->GetBinWidth(i);
    
    double dNdE_Reco = (hReco->GetBinContent(i))/(dE);
    double dNdE_Truth = (hTruth->GetBinContent(i))/(dE);
    double totEff = (dNdE_Reco/dNdE_Truth);
    hEfficiency->SetBinContent(i, totEff);
    
    double error_Reco = (hReco->GetBinError(i))/(dE);
    double error_Truth = (hTruth->GetBinError(i))/(dE);
    double totEffError = totEff*(TMath::Sqrt(TMath::Power(error_Reco/dNdE_Reco,2) + TMath::Power(error_Truth/dNdE_Truth,2)));
    hEfficiency->SetBinError(i, totEffError);
    
    //cout << hEfficiency->GetBinCenter(i) << "\t" << totEff << "\t" << totEffError << endl;

  }//*/  

  hEfficiency->SetLineColor(kRed+1);
  hEfficiency->SetMarkerColor(kRed+1);
  hEfficiency->SetMarkerStyle(kFullCross);
  hEfficiency->SetMarkerSize(2);
    
  //Iso Efficiency
  cout << "Iso Efficiency" << endl;
  for(int i = 1; i < hIsoEfficiency->GetNbinsX()+1; i++){
    double dE = hIsoEfficiency->GetBinWidth(i);
    
    double dNdE_TruthIsolated = (hTruthIsolated->GetBinContent(i))/(dE);
    double dNdE_Truth = (hTruth->GetBinContent(i))/(dE);
    double totEff = (dNdE_TruthIsolated/dNdE_Truth);
    hIsoEfficiency->SetBinContent(i, totEff);
    
    double error_TruthIsolated = (hTruthIsolated->GetBinError(i))/(dE);
    double error_Truth = (hTruth->GetBinError(i))/(dE);
    double totEffError = totEff*(TMath::Sqrt(TMath::Power(error_TruthIsolated/dNdE_TruthIsolated,2) + TMath::Power(error_Truth/dNdE_Truth,2)));
    hIsoEfficiency->SetBinError(i, totEffError);

    //cout << hIsoEfficiency->GetBinCenter(i) << "\t" << totEff << "\t" << totEffError << endl;
  }//*/  

  hIsoEfficiency->SetLineColor(kBlack);
  hIsoEfficiency->SetMarkerColor(kBlack);
  hIsoEfficiency->SetMarkerStyle(kFullCircle);
  hIsoEfficiency->SetMarkerSize(2);
    
  //Total Efficiency
  cout << "Total Efficiency" << endl;
  for(int i = 1; i < hTotalEfficiency->GetNbinsX()+1; i++){
    
    double effContent = hEfficiency->GetBinContent(i);
    double isoContent = hIsoEfficiency->GetBinContent(i);
    double totEff = effContent/isoContent;
    hTotalEfficiency->SetBinContent(i, totEff);
    
    double effError = hEfficiency->GetBinError(i);
    double isoError = hIsoEfficiency->GetBinError(i);
    double totEffError = totEff*(TMath::Sqrt(TMath::Power(effError/effContent,2) + TMath::Power(isoError/isoContent,2)));
    hTotalEfficiency->SetBinError(i, totEffError);

    //cout << hTotalEfficiency->GetBinCenter(i) << "\t" << totEff << "\t" << totEffError << endl;
  }//*/  

  hTotalEfficiency->SetLineColor(kBlue+1);
  hTotalEfficiency->SetMarkerColor(kBlue+1);
  hTotalEfficiency->SetMarkerStyle(kFullDiamond);
  hTotalEfficiency->SetMarkerSize(2);

  TLine *line = new TLine(12, 0.5, 60, 0.5);
  line->SetLineColor(kBlack);

  TLegend* lEff = new TLegend(0.13, 0.2, 0.5, 0.4);
  //lEff->SetNColumns(3);
  lEff->SetTextSize(0.037);
  lEff->SetFillStyle(0);
  lEff->SetMargin(0.3); 
  //lEff->SetHeader("ALICE Simluation, 18b10a, pp GJ, 5.02 TeV, p_{T}^{min} = 0.15 GeV/c, 0.4 < |#eta| < 0.67");
  //lEff->SetHeader("ALICE Simluation, 17g6a1, p-Pb GJ, 5.02 TeV, p_{T}^{min} = 0.15 GeV/c, 0.4 < |#eta| < 0.67");
  //lEff->AddEntry(hIsoEfficiency, "Iso eff = #frac{dN_{iso}(p^{gen}_{T}) }{dN_{all}(p^{gen}_{T})}");
  //lEff->AddEntry(hEfficiency, "Reco eff = #frac{dN_{iso}(p^{rec}_{T}) }{dN_{all}(p^{gen}_{T})}");
  //lEff->AddEntry(hTotalEfficiency, "Total eff = #frac{dN_{iso}(p^{rec}_{T}) }{dN_{iso}(p^{gen}_{T})}");
  lEff->SetHeader("ALICE Simluation, p-Pb #sqrt{s} = 5.02 TeV");
  lEff->AddEntry(hIsoEfficiency, "Isolated generated photon fraction (#kappa^{iso})", "lpf");
  lEff->AddEntry(hEfficiency, "Reconstruction + Identification (#varepsilon^{rec} #bullet #varepsilon^{id})");
  lEff->AddEntry(hTotalEfficiency, "Reconstruction + Identification + Isolation (#varepsilon^{rec} #bullet #varepsilon^{id} #bullet #varepsilon^{iso})");
  
  TCanvas* cEff = new TCanvas("cEFf", "cEff", 900, 700);
  cEff->SetLeftMargin(0.1);
  cEff->SetRightMargin(0.07);
  cEff->SetBottomMargin(0.15);
  hTotalEfficiency->SetTitle(";#it{p}_{T} [GeV/#it{c}];#varepsilon_{#gamma}^{iso} contributions");
  hTotalEfficiency->GetYaxis()->SetRangeUser(0,1);
  hTotalEfficiency->GetXaxis()->SetRangeUser(12,60);
  hTotalEfficiency->GetYaxis()->SetTitleOffset(1.3);
  hTotalEfficiency->GetXaxis()->SetTitleOffset(1.2);
  hTotalEfficiency->Draw("e1");
  hEfficiency->Draw("same e1");
  hIsoEfficiency->Draw("same e1");
  line->Draw("same");
  lEff->Draw("same");
  cEff->Print("QM2022_figures/efficiency_components_5020GeV_pPb.pdf");
  //cEff->SaveAs("IsoPhotonEff_pPb.pdf");
  //cEff->SaveAs("IsoPhotonEff_pPb.png");
  
  TString filename = fin->GetName();
  Int_t index = filename.Index("_noNorm");
  filename.Replace(index, 7, "");
  if(filename.CompareTo(fin->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hTotalEfficiency->Write("hTotalEfficiency");
    hEfficiency->Write("hEfficiency");
    hIsoEfficiency->Write("hIsoEfficiency");

    hCorrelation->Write("hCorrelation");
    reco->Write("reco");
    truth->Write("truth");
    hBinMigration->Write("hBinMigration");
    fout->Close();
  }//end filename compare*/
  
}
