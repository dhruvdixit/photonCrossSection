#include <fstream>
#include <vector>
void makeNtupleComparisons(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  

  //Obtain and plotting histograms from data

  TFile* file13f_part1 = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part1_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");
  TFile* file13f_part1_new = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part1_new_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root","READ");
  
  TH1F* hEG1_part1 = (TH1F*)file13f_part1->Get("hEG1_E");             
  TH1F* hEG1_part1_new = (TH1F*)file13f_part1_new->Get("hEG1_E");     
  hEG1_part1->SetName("hEG1_part1");
  hEG1_part1_new->SetName("hEG1_part1_new");
  hEG1_part1->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  hEG1_part1_new->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  hEG1_part1->GetXaxis()->SetRangeUser(12,60);
  hEG1_part1_new->GetXaxis()->SetRangeUser(12,60);
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
  
  TLegend* l_13f = new TLegend(0.5, 0.6, 0.85, 0.85);
  l_13f->SetHeader("13f ntuple EG1 photon spectra", "c");
  l_13f->AddEntry(hEG1_part1, "1st set of 10 runs");
  l_13f->AddEntry(hEG1_part1_new, "1st set of 10 runs: failed jobs resubmitted once");
  
  TCanvas* c_13f = new TCanvas("c_13f", "c_13f");
  c_13f->SetLogy();
  hEG1_part1->Draw("e1");
  hEG1_part1_new->Draw("samee1");
  l_13f->Draw("same");
  
  
}//end makeNtupleComparisons
