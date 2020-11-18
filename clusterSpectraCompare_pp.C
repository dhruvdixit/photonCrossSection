#include <fstream>
#include <vector>
void clusterSpectraCompare_pp(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  gStyle->SetErrorX(0);

  
  TString filePath = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/";
  //Input files

  //minimum bias triggers
  //TFile* file17p_mb_old = new TFile(Form("%sfout_1_15bins_17p_CENT_wSDD_10runs_noThresh_part1_RtrigAnalysis_MB_Normalized_bugFixed2_008to123_testing.root", filePath.Data()), "READ");
  //TFile* file17p_mb = new TFile(Form("%sfout_1_15bins_17p_CENT_wSDD_10runs_noThresh_part1_forRTrig.root", filePath.Data()), "READ");
  //TFile* file17q_mb = new TFile(Form("%sfout_1_15bins_17q_CENT_wSDD_noThresh_forRTrig.root", filePath.Data()), "READ");
  
  TFile* file17p_mb_old = new TFile(Form("%sfout_1_26bins_17p_CENT_wSDD_10runs_noThresh_part1_RtrigAnalysis_MB_Normalized_bugFixed2_008to123.root", filePath.Data()), "READ");
  TFile* file17p_mb = new TFile(Form("%sfout_1_26bins_17p_CENT_wSDD_10runs_noThresh_part1_forRTrig.root", filePath.Data()), "READ");
  TFile* file17q_mb = new TFile(Form("%sfout_1_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MB_Normalized_allEMCgoodOnly_bugFixed2_367to365.root", filePath.Data()), "READ");

  //eg2 calo trigger
  TFile* file17q_r282437 = new TFile(Form("%sfout_4_26bins_17q_CENT_wSDD_noThresh_r282437_forRTrig.root", filePath.Data()), "READ");
  TFile* file17q_r282439 = new TFile(Form("%sfout_4_26bins_17q_CENT_wSDD_noThresh_r282439_forRTrig.root", filePath.Data()), "READ");
  TFile* file17q_r282440 = new TFile(Form("%sfout_4_26bins_17q_CENT_wSDD_noThresh_r282440_forRTrig.root", filePath.Data()), "READ");
  TFile* file17q_r282441 = new TFile(Form("%sfout_4_26bins_17q_CENT_wSDD_noThresh_r282441_forRTrig.root", filePath.Data()), "READ");

  TFile* file17q_part3_new = new TFile(Form("%sfout_4_15bins_17q_CENT_wSDD_noThresh_forRTrig.root",filePath.Data()), "READ");
  TFile* file17q_part3_old = new TFile(Form("%sfout_4_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MBcentEGcaloEGcent_Normalized_allButEMCgoodOnly_bugFixed2_441to237.root",filePath.Data()), "READ");
  TFile* file17q_part1 = new TFile(Form("%sfout_4_15bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MB_Normalized_allEMCgoodOnly_bugFixed2_399to391.root",filePath.Data()), "READ");
  TFile* file17q_part2 = new TFile(Form("%sfout_4_15bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MB_Normalized_allEMCgoodOnly_bugFixed2_415to402.root",filePath.Data()), "READ");



  //mb hists
  TH1F* hist17p_mb_old = (TH1F*)file17p_mb_old->Get("hMB_centE");
  hist17p_mb_old->SetName("hist17p_mb_old"); hist17p_mb_old->SetMarkerStyle(kFullSquare); hist17p_mb_old->SetMarkerColor(kRed);
  TH1F* hist17p_mb = (TH1F*)file17p_mb->Get("hMB_centE");
  hist17p_mb->SetName("hist17p_mb"); hist17p_mb->SetMarkerStyle(kFullDiamond); hist17p_mb->SetMarkerColor(kBlue);hist17p_mb->SetMarkerSize(2);
  TH1F* hist17q_mb = (TH1F*)file17q_mb->Get("hMB_centE");
  hist17q_mb->SetName("hist17q_mb"); hist17q_mb->SetMarkerStyle(kOpenCircle);

  TLegend* leg_mb = new TLegend(0.65, 0.65, 0.85, 0.85);
  leg_mb->AddEntry(hist17p_mb, "17p");
  leg_mb->AddEntry(hist17q_mb, "17q");
    
  TCanvas* c_mb = new TCanvas("c_mb", "c_mb");
  c_mb->SetLogy();
  hist17p_mb->Draw("e1");
  //hist17p_mb_old->Draw("samee1");
  hist17q_mb->Draw("samee1");
  leg_mb->Draw("same");

  
  TH1F* ratio17p = (TH1F*)hist17p_mb_old->Clone();
  ratio17p->SetName("ratio17p");
  ratio17p->Divide(hist17p_mb);
  ratio17p->GetYaxis()->SetRangeUser(0.5,1.5);
  TCanvas* c_rmb = new TCanvas("c_rmb", "c_rmb");
  ratio17p->Draw("hist p");


  //calo hists
  TH1F* hist17q_calo_part3_old = (TH1F*)file17q_part3_old->Get("hEG2_caloE");
  hist17q_calo_part3_old->SetName("hist17q_calo_part3_old");
  hist17q_calo_part3_old->SetMarkerStyle(kOpenSquare);
  hist17q_calo_part3_old->SetMarkerSize(2);
  hist17q_calo_part3_old->SetMarkerColor(kRed);
  hist17q_calo_part3_old->SetLineColor(kRed);

  TH1F* hist17q_calo_part3_new = (TH1F*)file17q_part3_old->Get("hEG2_caloE");
  hist17q_calo_part3_new->SetName("hist17q_calo_part3_new");
  hist17q_calo_part3_new->SetMarkerStyle(kOpenDiamond);
  hist17q_calo_part3_new->SetMarkerColor(kBlue);
  hist17q_calo_part3_new->SetLineColor(kBlue);
  
  TH1F* hist17q_calo_r282437 = (TH1F*)file17q_r282437->Get("hEG2_caloE");
  hist17q_calo_r282437->SetName("hist17q_calo_r282437");
  hist17q_calo_r282437->SetMarkerStyle(kOpenDiamond);
  hist17q_calo_r282437->SetMarkerSize(2);
  hist17q_calo_r282437->SetMarkerColor(kMagenta);
  hist17q_calo_r282437->SetLineColor(kMagenta);
  TH1F* hist17q_calo_r282439 = (TH1F*)file17q_r282439->Get("hEG2_caloE");
  hist17q_calo_r282439->SetName("hist17q_calo_r282439");
  hist17q_calo_r282439->SetMarkerStyle(kOpenDiamond);
  hist17q_calo_r282439->SetMarkerSize(2);
  hist17q_calo_r282439->SetMarkerColor(kGreen);
  hist17q_calo_r282439->SetLineColor(kGreen);
  TH1F* hist17q_calo_r282440 = (TH1F*)file17q_r282440->Get("hEG2_caloE");
  hist17q_calo_r282440->SetName("hist17q_calo_r282440");
  hist17q_calo_r282440->SetMarkerStyle(kOpenDiamond);
  hist17q_calo_r282440->SetMarkerColor(kCyan);
  hist17q_calo_r282440->SetMarkerSize(2);
  hist17q_calo_r282440->SetLineColor(kCyan);
  TH1F* hist17q_calo_r282441 = (TH1F*)file17q_r282441->Get("hEG2_caloE");
  hist17q_calo_r282441->SetName("hist17q_calo_r282441");
  hist17q_calo_r282441->SetMarkerStyle(kOpenDiamond);
  hist17q_calo_r282441->SetMarkerColor(kBlack);
  hist17q_calo_r282441->SetMarkerSize(2);
  hist17q_calo_r282441->SetLineColor(kBlack);

  TLegend* leg_calo = new TLegend(0.5, 0.5, 0.85, 0.85);
  //leg_calo->AddEntry(hist17q_calo_part3_new, "17q part 3 clearner code");
  leg_calo->AddEntry(hist17q_calo_part3_old, "17q part 3 all runs");
  leg_calo->AddEntry(hist17q_calo_r282437, "17q r282437");
  leg_calo->AddEntry(hist17q_calo_r282439, "17q r282439");
  leg_calo->AddEntry(hist17q_calo_r282440, "17q r282440");
  leg_calo->AddEntry(hist17q_calo_r282441, "17q r282441");
 
		   
  TCanvas* c_calo = new TCanvas("c_calo", "c_calo");
  c_calo->SetLogy();
  //hist17q_calo_part3_new->Draw("e1");
  hist17q_calo_part3_old->Draw("e1");
  hist17q_calo_r282437->Draw("same e1");
  hist17q_calo_r282439->Draw("same e1");
  hist17q_calo_r282440->Draw("same e1");
  hist17q_calo_r282441->Draw("same e1");
  leg_calo->Draw("same");
  
  
  TH1F* ratio17q_part3 = (TH1F*)hist17q_calo_part3_old->Clone();
  ratio17q_part3->SetName("ratio17q_part3");
  ratio17q_part3->Divide(hist17q_calo_part3_new);
  ratio17q_part3->GetYaxis()->SetRangeUser(0.5,1.5);
  //ratio17q_part3->Draw("hist p");


  


}//end macro
