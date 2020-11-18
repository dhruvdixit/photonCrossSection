#include <fstream>
#include <vector>
void lumiEffectCompare_pp(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  

  //Obtain and plotting histograms from data

  TFile* file17qpart1 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_allpPb_crossSectionHistos_allpPb_399to391.root", "READ");
  TFile* file17qpart2 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_allpPb_crossSectionHistos_allpPb_415to402.root", "READ");
  TFile* file17qpart3 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_allpPb_crossSectionHistos_allpPb_441to437.root", "READ");
  TFile* file17qpart4 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_allpPb_crossSectionHistos_allpPb_365to367.root", "READ");
  TFile* file17q_r437 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_allpPb_crossSectionHistos_allpPb_r282437.root", "READ");
  TFile* file17q_r439 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_allpPb_crossSectionHistos_allpPb_r282439.root", "READ");
  TFile* file17q_r440 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_allpPb_crossSectionHistos_allpPb_r282440.root", "READ");
  TFile* file17q_r441 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_allpPb_crossSectionHistos_allpPb_r282441.root", "READ");
  
  
  TH1F* crossSection_pp_17qpart1 = (TH1F*)file17qpart1->Get("crossSection_pp");
  TH1F* crossSection_pp_17qpart2 = (TH1F*)file17qpart2->Get("crossSection_pp");
  TH1F* crossSection_pp_17qpart3 = (TH1F*)file17qpart3->Get("crossSection_pp");
  TH1F* crossSection_pp_17qpart4 = (TH1F*)file17qpart4->Get("crossSection_pp");
  
  crossSection_pp_17qpart1->SetName("crossSection_pp_17qpart1");
  crossSection_pp_17qpart2->SetName("crossSection_pp_17qpart2");
  crossSection_pp_17qpart3->SetName("crossSection_pp_17qpart3");
  crossSection_pp_17qpart4->SetName("crossSection_pp_17qpart4");
  
  crossSection_pp_17qpart1->SetLineColor(kRed);
  crossSection_pp_17qpart1->SetLineWidth(1);
  crossSection_pp_17qpart1->SetMarkerColor(kRed);
  crossSection_pp_17qpart1->SetMarkerSize(2);
  crossSection_pp_17qpart1->SetMarkerStyle(kOpenSquare);
  
  crossSection_pp_17qpart2->SetLineColor(kBlue);
  crossSection_pp_17qpart2->SetLineWidth(1);
  crossSection_pp_17qpart2->SetMarkerColor(kBlue);
  crossSection_pp_17qpart2->SetMarkerSize(2);
  crossSection_pp_17qpart2->SetMarkerStyle(kOpenCircle);

  crossSection_pp_17qpart3->SetLineColor(kCyan);
  crossSection_pp_17qpart3->SetLineWidth(1);
  crossSection_pp_17qpart3->SetMarkerColor(kCyan);
  crossSection_pp_17qpart3->SetMarkerSize(2);
  crossSection_pp_17qpart3->SetMarkerStyle(kStar);

  crossSection_pp_17qpart4->SetLineColor(kMagenta);
  crossSection_pp_17qpart4->SetLineWidth(1);
  crossSection_pp_17qpart4->SetMarkerColor(kMagenta);
  crossSection_pp_17qpart4->SetMarkerSize(3);
  crossSection_pp_17qpart4->SetMarkerStyle(kOpenDiamond);

  TH1F* crossSection_pp_17q_r437 = (TH1F*)file17q_r437->Get("crossSection_pp");
  crossSection_pp_17q_r437->SetName("crossSection_pp_17q_r437");
  crossSection_pp_17q_r437->SetLineColor(kMagenta);
  crossSection_pp_17q_r437->SetLineWidth(1);
  crossSection_pp_17q_r437->SetMarkerColor(kMagenta);
  crossSection_pp_17q_r437->SetMarkerStyle(kFullDiamond);
  TH1F* crossSection_pp_17q_r439 = (TH1F*)file17q_r439->Get("crossSection_pp");
  crossSection_pp_17q_r439->SetName("crossSection_pp_17q_r439");
  crossSection_pp_17q_r439->SetLineColor(kGreen);
  crossSection_pp_17q_r439->SetLineWidth(1);
  crossSection_pp_17q_r439->SetMarkerColor(kGreen);
  crossSection_pp_17q_r439->SetMarkerStyle(kFullDiamond);
  TH1F* crossSection_pp_17q_r440 = (TH1F*)file17q_r440->Get("crossSection_pp");
  crossSection_pp_17q_r440->SetName("crossSection_pp_17q_r440");
  crossSection_pp_17q_r440->SetLineColor(kBlack);
  crossSection_pp_17q_r440->SetLineWidth(1);
  crossSection_pp_17q_r440->SetMarkerColor(kBlack);
  crossSection_pp_17q_r440->SetMarkerStyle(kFullDiamond);
  TH1F* crossSection_pp_17q_r441 = (TH1F*)file17q_r441->Get("crossSection_pp");
  crossSection_pp_17q_r441->SetName("crossSection_pp_17q_r441");
  crossSection_pp_17q_r441->SetLineColor(kYellow);
  crossSection_pp_17q_r441->SetLineWidth(1);
  crossSection_pp_17q_r441->SetMarkerColor(kYellow);
  crossSection_pp_17q_r441->SetMarkerStyle(kFullDiamond);
  
  TLegend* l_crossSection = new TLegend(0.125, 0.125, 0.325, 0.425);
  l_crossSection->SetHeader("Run periods", "c");
  l_crossSection->AddEntry(crossSection_pp_17qpart1, "17q part1");
  l_crossSection->AddEntry(crossSection_pp_17qpart2, "17q part2");
  l_crossSection->AddEntry(crossSection_pp_17qpart3, "17q part3");
  l_crossSection->AddEntry(crossSection_pp_17q_r437, "17q r282437");
  l_crossSection->AddEntry(crossSection_pp_17q_r439, "17q r282439");
  l_crossSection->AddEntry(crossSection_pp_17q_r440, "17q r282440");
  l_crossSection->AddEntry(crossSection_pp_17q_r441, "17q r282441");


  //crossSection_pp_13d->SetTitle("Cross Section");
  TCanvas* c_crossSection = new TCanvas("c_crossSection", "c_crossSection");
  c_crossSection->SetLogy();
  crossSection_pp_17qpart1->GetXaxis()->SetRangeUser(12,60);
  crossSection_pp_17qpart1->Draw("e1");
  crossSection_pp_17qpart2->Draw("samee1");
  crossSection_pp_17qpart3->Draw("samee1");
  crossSection_pp_17q_r437->Draw("samee1");
  crossSection_pp_17q_r439->Draw("samee1");
  crossSection_pp_17q_r440->Draw("samee1");
  crossSection_pp_17q_r441->Draw("samee1");
  l_crossSection->Draw("same");

  //Cross Section Ratios
  TH1D* crossSection_pp_17qpart1_ratio = (TH1D*)crossSection_pp_17qpart1->Clone();
  TH1D* crossSection_pp_17qpart3_ratio = (TH1D*)crossSection_pp_17qpart3->Clone();
  TH1D* crossSection_pp_17q_r437_ratio = (TH1D*)crossSection_pp_17q_r437->Clone();
  TH1D* crossSection_pp_17q_r439_ratio = (TH1D*)crossSection_pp_17q_r439->Clone(); 
  TH1D* crossSection_pp_17q_r440_ratio = (TH1D*)crossSection_pp_17q_r440->Clone();
  TH1D* crossSection_pp_17q_r441_ratio = (TH1D*)crossSection_pp_17q_r441->Clone();
  
  crossSection_pp_17qpart1_ratio->Divide(crossSection_pp_17qpart2);
  crossSection_pp_17qpart3_ratio->Divide(crossSection_pp_17qpart2);
  crossSection_pp_17q_r437_ratio->Divide(crossSection_pp_17qpart2);
  crossSection_pp_17q_r439_ratio->Divide(crossSection_pp_17qpart2);
  crossSection_pp_17q_r440_ratio->Divide(crossSection_pp_17qpart2);
  crossSection_pp_17q_r441_ratio->Divide(crossSection_pp_17qpart2);
  
    
  TLegend* l_crossSectionRatio = new TLegend(0.125, 0.125, 0.325, 0.425);
  l_crossSectionRatio->SetHeader("Run periods", "c");
  l_crossSectionRatio->AddEntry(crossSection_pp_17qpart1_ratio, "17q part1");
  l_crossSectionRatio->AddEntry(crossSection_pp_17qpart3_ratio, "17q part3");
  l_crossSectionRatio->AddEntry(crossSection_pp_17q_r437_ratio, "17q r282437");
  l_crossSectionRatio->AddEntry(crossSection_pp_17q_r439_ratio, "17q r282439");
  l_crossSectionRatio->AddEntry(crossSection_pp_17q_r440_ratio, "17q r282440");
  l_crossSectionRatio->AddEntry(crossSection_pp_17q_r441_ratio, "17q r282441");

  crossSection_pp_17qpart1_ratio->SetTitle(";E_{T} [GeV];ratio to 17qpart2");
  crossSection_pp_17qpart1_ratio->GetYaxis()->SetRangeUser(0,2);
  crossSection_pp_17qpart1_ratio->GetXaxis()->SetRangeUser(12,60);
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);
  line->SetLineWidth(5);
  TCanvas* c_crossSectionRatio = new TCanvas("c_crossSectionRatio", "c_crossSectionRatio");
  crossSection_pp_17qpart1_ratio->Draw("samee1");
  crossSection_pp_17qpart3_ratio->Draw("samee1");
  crossSection_pp_17q_r437_ratio->Draw("samee1");
  crossSection_pp_17q_r439_ratio->Draw("samee1");
  crossSection_pp_17q_r440_ratio->Draw("samee1");
  crossSection_pp_17q_r441_ratio->Draw("samee1");
  line->Draw();
  l_crossSectionRatio->Draw("same");


}//end makeComparisons
