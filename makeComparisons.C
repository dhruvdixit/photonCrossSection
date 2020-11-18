#include <fstream>
#include <vector>
void makeComparisons(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  

  //Obtain and plotting histograms from data

  TFile* file13f_part1 = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part1_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");
  TFile* file13f_part1_new = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part1_new_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");
  TFile* file13f_part2 = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part2_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");
  TFile* file13f_part2_new = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part2_new_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");
  TFile* file13f_part3 = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part3_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");
  TFile* file13f_part3_new = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part3_new_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");
  TFile* file13f_part3_newer = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part3_newer_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");
  TFile* file13f_part4 = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part4_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");
  TFile* file13f_part5 = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_part5_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");
  TFile* file13f_part5_new = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_part5_new_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");

  TH1F* hEG1_part1 = (TH1F*)file13f_part1->Get("hEG1_E");             
  TH1F* hEG1_part1_new = (TH1F*)file13f_part1_new->Get("hEG1_E");     
  TH1F* hEG1_part2 = (TH1F*)file13f_part2->Get("hEG1_E");             
  TH1F* hEG1_part2_new = (TH1F*)file13f_part2_new->Get("hEG1_E");     
  TH1F* hEG1_part3 = (TH1F*)file13f_part3->Get("hEG1_E");             
  TH1F* hEG1_part3_new = (TH1F*)file13f_part3_new->Get("hEG1_E");     
  TH1F* hEG1_part3_newer = (TH1F*)file13f_part3_newer->Get("hEG1_E");
  TH1F* hEG1_part4 = (TH1F*)file13f_part4->Get("hEG1_E");
  TH1F* hEG1_part5 = (TH1F*)file13f_part5->Get("hEG1_E");
  TH1F* hEG1_part5_new = (TH1F*)file13f_part5_new->Get("hEG1_E");             

  hEG1_part1->SetName("hEG1_part1");
  hEG1_part1_new->SetName("hEG1_part1_new");
  hEG1_part2->SetName("hEG1_part2");
  hEG1_part2_new->SetName("hEG1_part2_new");
  hEG1_part3->SetName("hEG1_part3");
  hEG1_part3_new->SetName("hEG1_part3_new");
  hEG1_part3_newer->SetName("hEG1_part3_newer");
  hEG1_part4->SetName("hEG1_part4");
  hEG1_part5->SetName("hEG1_part5");
  hEG1_part5_new->SetName("hEG1_part5_new");
	
  hEG1_part1->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  hEG1_part1_new->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  hEG1_part2->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  hEG1_part2_new->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  hEG1_part3->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  hEG1_part3_new->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  hEG1_part3_newer->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  hEG1_part4->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  hEG1_part5->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  hEG1_part5_new->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  
  hEG1_part1->GetXaxis()->SetRangeUser(12,60);
  hEG1_part1_new->GetXaxis()->SetRangeUser(12,60);
  hEG1_part2->GetXaxis()->SetRangeUser(12,60);
  hEG1_part2_new->GetXaxis()->SetRangeUser(12,60);
  hEG1_part3->GetXaxis()->SetRangeUser(12,60);
  hEG1_part3_new->GetXaxis()->SetRangeUser(12,60);
  hEG1_part3_newer->GetXaxis()->SetRangeUser(12,60);
  
  //part1
  hEG1_part1->SetLineColor(kRed);
  hEG1_part1->SetLineWidth(1);
  hEG1_part1->SetMarkerColor(kRed);
  hEG1_part1->SetMarkerSize(2);
  hEG1_part1->SetMarkerStyle(kOpenCircle);
  
  hEG1_part1_new->SetLineColor(kRed);
  hEG1_part1_new->SetLineWidth(1);
  hEG1_part1_new->SetMarkerColor(kRed);
  hEG1_part1_new->SetMarkerSize(2);
  hEG1_part1_new->SetMarkerStyle(kOpenDiamond);
  
  //part2
  hEG1_part2->SetLineColor(kBlue);
  hEG1_part2->SetLineWidth(1);
  hEG1_part2->SetMarkerColor(kBlue);
  hEG1_part2->SetMarkerSize(2);
  hEG1_part2->SetMarkerStyle(kOpenSquare);
  
  hEG1_part2_new->SetLineColor(kBlue);
  hEG1_part2_new->SetLineWidth(1);
  hEG1_part2_new->SetMarkerColor(kBlue);
  hEG1_part2_new->SetMarkerSize(2);
  hEG1_part2_new->SetMarkerStyle(kOpenDoubleDiamond);
  
  //part3
  hEG1_part3->SetLineColor(kMagenta);
  hEG1_part3->SetLineWidth(1);
  hEG1_part3->SetMarkerColor(kMagenta);
  hEG1_part3->SetMarkerSize(2);
  hEG1_part3->SetMarkerStyle(kStar);
  
  hEG1_part3_new->SetLineColor(kOrange);
  hEG1_part3_new->SetLineWidth(1);
  hEG1_part3_new->SetMarkerColor(kOrange);
  hEG1_part3_new->SetMarkerSize(2);
  hEG1_part3_new->SetMarkerStyle(kOpenStar);
  
  hEG1_part3_newer->SetLineColor(kBlack);
  hEG1_part3_newer->SetLineWidth(1);
  hEG1_part3_newer->SetMarkerColor(kBlack);
  hEG1_part3_newer->SetMarkerSize(2);
  hEG1_part3_newer->SetMarkerStyle(kOpenCross);

  //part4
  hEG1_part4->SetLineColor(kGreen);
  hEG1_part4->SetLineWidth(1);
  hEG1_part4->SetMarkerColor(kGreen);
  hEG1_part4->SetMarkerSize(2);
  hEG1_part4->SetMarkerStyle(kOpenCircle);
  
  //part5
  hEG1_part5->SetLineColor(kCyan);
  hEG1_part5->SetLineWidth(1);
  hEG1_part5->SetMarkerColor(kCyan);
  hEG1_part5->SetMarkerSize(2);
  hEG1_part5->SetMarkerStyle(kOpenCircle);
  
  hEG1_part5_new->SetLineColor(kCyan);
  hEG1_part5_new->SetLineWidth(1);
  hEG1_part5_new->SetMarkerColor(kCyan);
  hEG1_part5_new->SetMarkerSize(2);
  hEG1_part5_new->SetMarkerStyle(kOpenDiamond);
  
  TLegend* l_13f = new TLegend(0.5, 0.6, 0.85, 0.85);
  l_13f->SetHeader("13f ntuple EG1 photon spectra", "c");
  l_13f->AddEntry(hEG1_part1, "1st set of 10 runs");
  l_13f->AddEntry(hEG1_part1_new, "1st set of 10 runs: failed jobs resubmitted once");
  l_13f->AddEntry(hEG1_part2, "2nd set of 10 runs");
  l_13f->AddEntry(hEG1_part2_new, "2nd set of 10 runs: failed jobs resubmitted once");
  l_13f->AddEntry(hEG1_part3, "3rd set of 10 runs");
  l_13f->AddEntry(hEG1_part3_new, "3rd set of 10 runs: failed jobs resubmitted once");
  l_13f->AddEntry(hEG1_part3_newer, "3rd set of 10 runs: failed jobs resubmitted twice");
  l_13f->AddEntry(hEG1_part4, "4th set of 10 runs");
  l_13f->AddEntry(hEG1_part5, "5th set of 3 runs");
  l_13f->AddEntry(hEG1_part5_new, "5th set of 3 runs: failed jobs submmited once");
  
  TCanvas* c_13f = new TCanvas("c_13f", "c_13f");
  c_13f->SetLogy();
  hEG1_part1->Draw("e1");
  hEG1_part2->Draw("samee1");
  hEG1_part3->Draw("samee1");
  hEG1_part1_new->Draw("samee1");
  hEG1_part2_new->Draw("samee1");
  hEG1_part3_new->Draw("samee1");
  hEG1_part3_newer->Draw("samee1");
  hEG1_part4->Draw("samee1");
  hEG1_part5->Draw("samee1");
  hEG1_part5_new->Draw("samee1");
  l_13f->Draw("same");
  
  
}//end makeComparisons
