#include <fstream>
#include <vector>
void lumiEffectCompare_pp(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  

  //Obtain and plotting histograms from data

  TFile* file17qpart1 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_13fpart12345_crossSectionHistos_CaloITS_399to391_540.root", "READ");
  TFile* file17qpart2 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_13fpart12345_crossSectionHistos_CaloITS_415to402_540.root", "READ");
  TFile* file17qpart3 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_13fpart12345_crossSectionHistos_CaloITS_441to437_540.root", "READ");
  TFile* file17qpart4 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_13fpart12345_crossSectionHistos_CaloITS_367to365_540.root", "READ");
  
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
  
  TLegend* l_crossSection = new TLegend(0.125, 0.125, 0.325, 0.425);
  l_crossSection->SetHeader("Run periods", "c");
  l_crossSection->AddEntry(crossSection_pp_17qpart1, "17q part1");
  l_crossSection->AddEntry(crossSection_pp_17qpart2, "17q part2");
  l_crossSection->AddEntry(crossSection_pp_17qpart3, "17q part3");
  l_crossSection->AddEntry(crossSection_pp_17qpart4, "17q part4");


  //crossSection_pp_13d->SetTitle("Cross Section");
  TCanvas* c_crossSection = new TCanvas("c_crossSection", "c_crossSection");
  c_crossSection->SetLogy();
  crossSection_pp_17qpart1->Draw("e1");
  crossSection_pp_17qpart2->Draw("samee1");
  crossSection_pp_17qpart3->Draw("samee1");
  crossSection_pp_17qpart4->Draw("samee1");
  l_crossSection->Draw("same");

  //Cross Section Ratios
  TH1D* crossSection_pp_17qpart1_ratio = (TH1D*)crossSection_pp_17qpart1->Clone();
  TH1D* crossSection_pp_17qpart2_ratio = (TH1D*)crossSection_pp_17qpart2->Clone();
  TH1D* crossSection_pp_17qpart3_ratio = (TH1D*)crossSection_pp_17qpart3->Clone();


  crossSection_pp_17qpart1_ratio->Divide(crossSection_pp_17qpart4);
  crossSection_pp_17qpart2_ratio->Divide(crossSection_pp_17qpart4);
  crossSection_pp_17qpart3_ratio->Divide(crossSection_pp_17qpart4);
  
    
  TLegend* l_crossSectionRatio = new TLegend(0.125, 0.125, 0.325, 0.425);
  l_crossSectionRatio->SetHeader("Run periods", "c");
  l_crossSectionRatio->AddEntry(crossSection_pp_17qpart1_ratio, "17q part1");
  l_crossSectionRatio->AddEntry(crossSection_pp_17qpart2_ratio, "17q part2");
  l_crossSectionRatio->AddEntry(crossSection_pp_17qpart3_ratio, "17q part3");


  crossSection_pp_17qpart1_ratio->SetTitle(";E_{T} [GeV];ratio to 17qpart4");
  //crossSection_pp_17qpart1_ratio->GetYaxis()->SetRangeUser(0,2);
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);
  line->SetLineWidth(5);
  TCanvas* c_crossSectionRatio = new TCanvas("c_crossSectionRatio", "c_crossSectionRatio");
  crossSection_pp_17qpart1_ratio->Draw("samee1");
  crossSection_pp_17qpart2_ratio->Draw("samee1");
  crossSection_pp_17qpart3_ratio->Draw("samee1");
  line->Draw();
  l_crossSectionRatio->Draw("same");


}//end makeComparisons
