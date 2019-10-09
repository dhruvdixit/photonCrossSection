#include <fstream>
#include <vector>
void cutVariation(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  
  //Obtain and plotting histograms from MC
  TFile* mcFile_pPb_std = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_hCorr_corr.root","READ");
  TFile* mcFile_pPb_bc0 = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_dist2BadChn0_hCorr_corr.root","READ");
  TFile* mcFile_pPb_bc1 = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_dist2BadChn1_hCorr_corr.root","READ");
  TFile* mcFile_pPb_nc1_bc1 = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_dist2BadChn1_hCorr_corr_ncell1.root","READ"); 
  
  //Standard
  TH1D* hEff_pPb_std = (TH1D*)mcFile_pPb_std->Get("hEfficiency");
  hEff_pPb_std->SetName("hEff_pPb_std");
  hEff_pPb_std->SetTitle("Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso}; E_{T} [GeV]; #epsilon");
  hEff_pPb_std->GetYaxis()->SetRangeUser(0,1);
  hEff_pPb_std->SetLineColor(kRed);
  hEff_pPb_std->SetMarkerColor(kRed);
  hEff_pPb_std->SetMarkerStyle(24);

  TH1D* hRecoEff_pPb_std = (TH1D*)mcFile_pPb_std->Get("hRecoEfficiency");
  hRecoEff_pPb_std->SetName("hRecoEff_pPb_std");
  hRecoEff_pPb_std->SetTitle("Reconstruction Efficiency; E_{T} [GeV]; #epsilon_{reco}");
  hRecoEff_pPb_std->GetYaxis()->SetRangeUser(0,1);
  hRecoEff_pPb_std->SetLineColor(kRed);
  hRecoEff_pPb_std->SetMarkerColor(kRed);
  hRecoEff_pPb_std->SetMarkerStyle(24);

  TH1D* hFakeRate_pPb_std = (TH1D*)mcFile_pPb_std->Get("hFakeRate");
  hFakeRate_pPb_std->SetName("FakeRate_pPb_std");
  hFakeRate_pPb_std->SetTitle("Fake rate; E_{T} [GeV];");
  hFakeRate_pPb_std->GetYaxis()->SetRangeUser(0,1);
  hFakeRate_pPb_std->SetLineColor(kRed);
  hFakeRate_pPb_std->SetMarkerColor(kRed);
  hFakeRate_pPb_std->SetMarkerStyle(24);

  TH1D* hBinMigration_pPb_std = (TH1D*)mcFile_pPb_std->Get("hMigEfficiency");
  hBinMigration_pPb_std->SetName("hbinMigration_pPb_std");
  hBinMigration_pPb_std->SetTitle("Bin Migration Effection; E_{T} [GeV]; #epsilon");
  hBinMigration_pPb_std->GetYaxis()->SetRangeUser(0,1);
  hBinMigration_pPb_std->SetLineColor(kRed);
  hBinMigration_pPb_std->SetMarkerColor(kRed);
  hBinMigration_pPb_std->SetMarkerStyle(24);

  TH1D* hISOEff_pPb_std = (TH1D*)mcFile_pPb_std->Get("hISOEfficiency");
  hISOEff_pPb_std->SetName("hISOEff_pPb_std");
  hISOEff_pPb_std->SetTitle("Isolation efficiency; E_{T}^{reco} [GeV]; #epsilon_{iso}");
  hISOEff_pPb_std->GetYaxis()->SetRangeUser(0,1);
  hISOEff_pPb_std->SetLineColor(kRed);
  hISOEff_pPb_std->SetMarkerColor(kRed);
  hISOEff_pPb_std->SetMarkerStyle(24);

  TH1D* hSSCEff_pPb_std = (TH1D*)mcFile_pPb_std->Get("hSSCEfficiency");
  hSSCEff_pPb_std->SetName("hSSCEff_pPb_std");
  hSSCEff_pPb_std->SetTitle("Shower Shape efficiency; E_{T}^{reco} [GeV]; #epsilon_{iso}");
  hSSCEff_pPb_std->GetYaxis()->SetRangeUser(0,1);
  hSSCEff_pPb_std->SetLineColor(kRed);
  hSSCEff_pPb_std->SetMarkerColor(kRed);
  hSSCEff_pPb_std->SetMarkerStyle(24);
  
  //Bad Chn 0
  TH1D* hEff_pPb_bc0 = (TH1D*)mcFile_pPb_bc0->Get("hEfficiency");
  hEff_pPb_bc0->SetName("hEff_pPb_bc0");
  hEff_pPb_bc0->SetTitle("Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso}; E_{T} [GeV]; #epsilon");
  hEff_pPb_bc0->GetYaxis()->SetRangeUser(0,1);
  hEff_pPb_bc0->SetLineColor(kBlue);
  hEff_pPb_bc0->SetMarkerColor(kBlue);
  hEff_pPb_bc0->SetMarkerStyle(25);

  TH1D* hRecoEff_pPb_bc0 = (TH1D*)mcFile_pPb_bc0->Get("hRecoEfficiency");
  hRecoEff_pPb_bc0->SetName("hRecoEff_pPb_bc0");
  hRecoEff_pPb_bc0->SetTitle("Reconstruction Efficiency; E_{T} [GeV]; #epsilon_{reco}");
  hRecoEff_pPb_bc0->GetYaxis()->SetRangeUser(0,1);
  hRecoEff_pPb_bc0->SetLineColor(kBlue);
  hRecoEff_pPb_bc0->SetMarkerColor(kBlue);
  hRecoEff_pPb_bc0->SetMarkerStyle(25);

  TH1D* hFakeRate_pPb_bc0 = (TH1D*)mcFile_pPb_bc0->Get("hFakeRate");
  hFakeRate_pPb_bc0->SetName("FakeRate_pPb_bc0");
  hFakeRate_pPb_bc0->SetTitle("Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso}; E_{T} [GeV];");
  hFakeRate_pPb_bc0->GetYaxis()->SetRangeUser(0,1);
  hFakeRate_pPb_bc0->SetLineColor(kBlue);
  hFakeRate_pPb_bc0->SetMarkerColor(kBlue);
  hFakeRate_pPb_bc0->SetMarkerStyle(25);

  TH1D* hBinMigration_pPb_bc0 = (TH1D*)mcFile_pPb_bc0->Get("hMigEfficiency");
  hBinMigration_pPb_bc0->SetName("hbinMigration_pPb_bc0");
  hBinMigration_pPb_bc0->SetTitle("Bin Migration Effection = #frach{dN^{reco}/dE_{T}^{reco}}{dN^{reco}/dE_{T}^{truth}}; E_{T} [GeV]; #epsilon");
  hBinMigration_pPb_bc0->GetYaxis()->SetRangeUser(0,1);
  hBinMigration_pPb_bc0->SetLineColor(kBlue);
  hBinMigration_pPb_bc0->SetMarkerColor(kBlue);
  hBinMigration_pPb_bc0->SetMarkerStyle(25);

  TH1D* hISOEff_pPb_bc0 = (TH1D*)mcFile_pPb_bc0->Get("hISOEfficiency");
  hISOEff_pPb_bc0->SetName("hISOEff_pPb_bc0");
  hISOEff_pPb_bc0->SetTitle("Isolation efficiency; E_{T}^{reco} [GeV]; #epsilon_{iso}");
  hISOEff_pPb_bc0->GetYaxis()->SetRangeUser(0,1);
  hISOEff_pPb_bc0->SetLineColor(kBlue);
  hISOEff_pPb_bc0->SetMarkerColor(kBlue);
  hISOEff_pPb_bc0->SetMarkerStyle(25);

  TH1D* hSSCEff_pPb_bc0 = (TH1D*)mcFile_pPb_bc0->Get("hSSCEfficiency");
  hSSCEff_pPb_bc0->SetName("hSSCEff_pPb_bc0");
  hSSCEff_pPb_bc0->SetTitle("Isolation efficiency; E_{T}^{reco} [GeV]; #epsilon_{iso}");
  hSSCEff_pPb_bc0->GetYaxis()->SetRangeUser(0,1);
  hSSCEff_pPb_bc0->SetLineColor(kBlue);
  hSSCEff_pPb_bc0->SetMarkerColor(kBlue);
  hSSCEff_pPb_bc0->SetMarkerStyle(25);

  //Bad Chn 1
  TH1D* hEff_pPb_bc1 = (TH1D*)mcFile_pPb_bc1->Get("hEfficiency");
  hEff_pPb_bc1->SetName("hEff_pPb_bc1");
  hEff_pPb_bc1->SetTitle("Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso}; E_{T} [GeV]; #epsilon");
  hEff_pPb_bc1->GetYaxis()->SetRangeUser(0,1);
  hEff_pPb_bc1->SetLineColor(kMagenta);
  hEff_pPb_bc1->SetMarkerColor(kMagenta);
  hEff_pPb_bc1->SetMarkerStyle(26);

  TH1D* hRecoEff_pPb_bc1 = (TH1D*)mcFile_pPb_bc1->Get("hRecoEfficiency");
  hRecoEff_pPb_bc1->SetName("hRecoEff_pPb_bc1");
  hRecoEff_pPb_bc1->SetTitle("Reconstruction Efficiency; E_{T} [GeV]; #epsilon_{reco}");
  hRecoEff_pPb_bc1->GetYaxis()->SetRangeUser(0,1);
  hRecoEff_pPb_bc1->SetLineColor(kMagenta);
  hRecoEff_pPb_bc1->SetMarkerColor(kMagenta);
  hRecoEff_pPb_bc1->SetMarkerStyle(26);
  
  TH1D* hFakeRate_pPb_bc1 = (TH1D*)mcFile_pPb_bc1->Get("hFakeRate");
  hFakeRate_pPb_bc1->SetName("FakeRate_pPb_bc1");
  hFakeRate_pPb_bc1->SetTitle("Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso}; E_{T} [GeV];");
  hFakeRate_pPb_bc1->GetYaxis()->SetRangeUser(0,1);
  hFakeRate_pPb_bc1->SetLineColor(kMagenta);
  hFakeRate_pPb_bc1->SetMarkerColor(kMagenta);
  hFakeRate_pPb_bc1->SetMarkerStyle(26);

  TH1D* hBinMigration_pPb_bc1 = (TH1D*)mcFile_pPb_bc1->Get("hMigEfficiency");
  hBinMigration_pPb_bc1->SetName("hbinMigration_pPb_bc1");
  hBinMigration_pPb_bc1->SetTitle("Bin Migration Effection; E_{T} [GeV]; #epsilon");
  hBinMigration_pPb_bc1->GetYaxis()->SetRangeUser(0,1);
  hBinMigration_pPb_bc1->SetLineColor(kMagenta);
  hBinMigration_pPb_bc1->SetMarkerColor(kMagenta);
  hBinMigration_pPb_bc1->SetMarkerStyle(26);

  TH1D* hISOEff_pPb_bc1 = (TH1D*)mcFile_pPb_bc1->Get("hISOEfficiency");
  hISOEff_pPb_bc1->SetName("hISOEff_pPb_bc1");
  hISOEff_pPb_bc1->SetTitle("Isolation efficiency; E_{T}^{reco} [GeV]; #epsilon_{iso}");
  hISOEff_pPb_bc1->GetYaxis()->SetRangeUser(0,1);
  hISOEff_pPb_bc1->SetLineColor(kMagenta);
  hISOEff_pPb_bc1->SetMarkerColor(kMagenta);
  hISOEff_pPb_bc1->SetMarkerStyle(26);

  TH1D* hSSCEff_pPb_bc1 = (TH1D*)mcFile_pPb_bc1->Get("hSSCEfficiency");
  hSSCEff_pPb_bc1->SetName("hSSCEff_pPb_bc1");
  hSSCEff_pPb_bc1->SetTitle("Isolation efficiency; E_{T}^{reco} [GeV]; #epsilon_{iso}");
  hSSCEff_pPb_bc1->GetYaxis()->SetRangeUser(0,1);
  hSSCEff_pPb_bc1->SetLineColor(kMagenta);
  hSSCEff_pPb_bc1->SetMarkerColor(kMagenta);
  hSSCEff_pPb_bc1->SetMarkerStyle(26);
  
  //Bad Chn 1,  ncell 1
  TH1D* hEff_pPb_nc1_bc1 = (TH1D*)mcFile_pPb_nc1_bc1->Get("hEfficiency");
  hEff_pPb_nc1_bc1->SetName("hEff_pPb_nc1_bc1");
  hEff_pPb_nc1_bc1->SetTitle("Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso}; E_{T} [GeV]; #epsilon");
  hEff_pPb_nc1_bc1->GetYaxis()->SetRangeUser(0,1);
  hEff_pPb_nc1_bc1->SetLineColor(kGreen);
  hEff_pPb_nc1_bc1->SetMarkerColor(kGreen);
  hEff_pPb_nc1_bc1->SetMarkerStyle(27);

  TH1D* hRecoEff_pPb_nc1_bc1 = (TH1D*)mcFile_pPb_nc1_bc1->Get("hRecoEfficiency");
  hRecoEff_pPb_nc1_bc1->SetName("hRecoEff_pPb_nc1_bc1");
  hRecoEff_pPb_nc1_bc1->SetTitle("Reconstruction Efficiency; E_{T} [GeV]; #epsilon_{reco}");
  hRecoEff_pPb_nc1_bc1->GetYaxis()->SetRangeUser(0,1);
  hRecoEff_pPb_nc1_bc1->SetLineColor(kGreen);
  hRecoEff_pPb_nc1_bc1->SetMarkerColor(kGreen);
  hRecoEff_pPb_nc1_bc1->SetMarkerStyle(27);
  
  TH1D* hFakeRate_pPb_nc1_bc1 = (TH1D*)mcFile_pPb_nc1_bc1->Get("hFakeRate");
  hFakeRate_pPb_nc1_bc1->SetName("FakeRate_pPb_nc1_bc1");
  hFakeRate_pPb_nc1_bc1->SetTitle("Fake rate; E_{T} [GeV];");
  hFakeRate_pPb_nc1_bc1->GetYaxis()->SetRangeUser(0,1);
  hFakeRate_pPb_nc1_bc1->SetLineColor(kGreen);
  hFakeRate_pPb_nc1_bc1->SetMarkerColor(kGreen);
  hFakeRate_pPb_nc1_bc1->SetMarkerStyle(27);

  TH1D* hBinMigration_pPb_nc1_bc1 = (TH1D*)mcFile_pPb_nc1_bc1->Get("hMigEfficiency");
  hBinMigration_pPb_nc1_bc1->SetName("hbinMigration_pPb_nc1_bc1");
  hBinMigration_pPb_nc1_bc1->SetTitle("Bin Migration Effection = #frach{dN^{reco}/dE_{T}^{reco}}{dN^{reco}/dE_{T}^{truth}}; E_{T} [GeV]; #epsilon");
  hBinMigration_pPb_nc1_bc1->GetYaxis()->SetRangeUser(0,1);
  hBinMigration_pPb_nc1_bc1->SetLineColor(kGreen);
  hBinMigration_pPb_nc1_bc1->SetMarkerColor(kGreen);
  hBinMigration_pPb_nc1_bc1->SetMarkerStyle(27);

  TH1D* hISOEff_pPb_nc1_bc1 = (TH1D*)mcFile_pPb_nc1_bc1->Get("hISOEfficiency");
  hISOEff_pPb_nc1_bc1->SetName("hISOEff_pPb_nc1_bc1");
  hISOEff_pPb_nc1_bc1->SetTitle("Isolation efficiency; E_{T}^{reco} [GeV]; #epsilon_{iso}");
  hISOEff_pPb_nc1_bc1->GetYaxis()->SetRangeUser(0,1);
  hISOEff_pPb_nc1_bc1->SetLineColor(kGreen);
  hISOEff_pPb_nc1_bc1->SetMarkerColor(kGreen);
  hISOEff_pPb_nc1_bc1->SetMarkerStyle(27);

  TH1D* hSSCEff_pPb_nc1_bc1 = (TH1D*)mcFile_pPb_nc1_bc1->Get("hSSCEfficiency");
  hSSCEff_pPb_nc1_bc1->SetName("hSSCEff_pPb_nc1_bc1");
  hSSCEff_pPb_nc1_bc1->SetTitle("Shower Shape efficiency; E_{T}^{reco} [GeV]; #epsilon_{ssc}");
  hSSCEff_pPb_nc1_bc1->GetYaxis()->SetRangeUser(0,1);
  hSSCEff_pPb_nc1_bc1->SetLineColor(kGreen);
  hSSCEff_pPb_nc1_bc1->SetMarkerColor(kGreen);
  hSSCEff_pPb_nc1_bc1->SetMarkerStyle(27);


  TLegend* leg = new TLegend(0.6, 0.15, 0.9, 0.45);
  leg->AddEntry(hEff_pPb_std, "Current Cuts (in back up)");
  leg->AddEntry(hEff_pPb_bc0, "Distance to bad channel >= 0");
  leg->AddEntry(hEff_pPb_bc1, "Distance to bad channel >= 1");
  leg->AddEntry(hEff_pPb_nc1_bc1, "Distance to bad channel >= 1 & ncell >=1");
  
  TCanvas* cEff = new TCanvas("cEff", "cEff");
  hEff_pPb_std->Draw();
  hEff_pPb_bc0->Draw("samee");
  hEff_pPb_bc1->Draw("samee");
  hEff_pPb_nc1_bc1->Draw("samee");
  leg->Draw();

  TCanvas* cRecoEff = new TCanvas("cRecoEff", "cRecoEff");
  hRecoEff_pPb_std->Draw();
  hRecoEff_pPb_bc0->Draw("samee");
  hRecoEff_pPb_bc1->Draw("samee");
  hRecoEff_pPb_nc1_bc1->Draw("samee");
  leg->Draw();

  
  TCanvas* cFakeRate = new TCanvas("cFakeRate", "cFakeRate");
  hFakeRate_pPb_std->Draw();
  hFakeRate_pPb_bc0->Draw("samee");
  hFakeRate_pPb_bc1->Draw("samee");
  hFakeRate_pPb_nc1_bc1->Draw("samee");
  leg->Draw();

  TCanvas* cBinMigration = new TCanvas("cBinMigration", "cBinMigration");
  hBinMigration_pPb_std->Draw();
  hBinMigration_pPb_bc0->Draw("samee");
  hBinMigration_pPb_bc1->Draw("samee");
  hBinMigration_pPb_nc1_bc1->Draw("samee");
  leg->Draw();

  TCanvas* cISOEff = new TCanvas("cISOEff", "cISOEff");
  hISOEff_pPb_std->Draw();
  hISOEff_pPb_bc0->Draw("samee");
  hISOEff_pPb_bc1->Draw("samee");
  hISOEff_pPb_nc1_bc1->Draw("samee");
  leg->Draw();

  TCanvas* cSSCEff = new TCanvas("cSSCEff", "cSSCEff");
  hSSCEff_pPb_std->Draw();
  hSSCEff_pPb_bc0->Draw("samee");
  hSSCEff_pPb_bc1->Draw("samee");
  hSSCEff_pPb_nc1_bc1->Draw("samee");
  leg->Draw();

}
