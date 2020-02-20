#include <fstream>
#include <vector>
void lumiEffectCompare(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  

  //Obtain and plotting histograms from data

  TFile* file13d = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/13d_all10runs_noSkim_crossSectionHistos.root", "READ");
  TFile* file13e = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_13epart12_crossSectionHistos.root", "READ");
  TFile* file13fOld = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/13fOld_crossSectionHistos.root", "READ");
  TFile* file13fNew = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_13fpart12345_crossSectionHistos.root", "READ");
  TFile* file13fpart1 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/13f_10runs_noSkim_part1_new_crossSectionHistos.root", "READ");
   TFile* file13fpart2 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/13f_10runs_noSkim_part2_new_crossSectionHistos.root", "READ");
   TFile* file13fpart3 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/13f_10runs_noSkim_part3_newer_crossSectionHistos.root", "READ");
   TFile* file13fpart4 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/13f_10runs_noSkim_part4_crossSectionHistos.root", "READ");
   TFile* file13fpart5 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/13f_3runs_noSkim_part5_new_crossSectionHistos.root", "READ");

  TH1F* crossSection_pPb_13d = (TH1F*)file13d->Get("crossSection_pPb");
  TH1F* crossSection_pPb_13e = (TH1F*)file13e->Get("crossSection_pPb");
  TH1F* crossSection_pPb_13fOld = (TH1F*)file13fOld->Get("crossSection_pPb");
  TH1F* crossSection_pPb_13fNew = (TH1F*)file13fNew->Get("crossSection_pPb");
  TH1F* crossSection_pPb_13fpart1 = (TH1F*)file13fpart1->Get("crossSection_pPb");
  TH1F* crossSection_pPb_13fpart2 = (TH1F*)file13fpart2->Get("crossSection_pPb");
  TH1F* crossSection_pPb_13fpart3 = (TH1F*)file13fpart3->Get("crossSection_pPb");
  TH1F* crossSection_pPb_13fpart4 = (TH1F*)file13fpart4->Get("crossSection_pPb");
  TH1F* crossSection_pPb_13fpart5 = (TH1F*)file13fpart5->Get("crossSection_pPb");
  crossSection_pPb_13d->SetName("crossSection_pPb_13d");
  crossSection_pPb_13e->SetName("crossSection_pPb_13e");
  crossSection_pPb_13fOld->SetName("crossSection_pPb_13fOld");
  crossSection_pPb_13fNew->SetName("crossSection_pPb_13fNew");
  crossSection_pPb_13fpart1->SetName("crossSection_pPb_13fpart1");
  crossSection_pPb_13fpart2->SetName("crossSection_pPb_13fpart2");
  crossSection_pPb_13fpart3->SetName("crossSection_pPb_13fpart3");
  crossSection_pPb_13fpart4->SetName("crossSection_pPb_13fpart4");
  crossSection_pPb_13fpart5->SetName("crossSection_pPb_13fpart5");
    
  crossSection_pPb_13d->SetLineColor(kRed);
  crossSection_pPb_13d->SetLineWidth(1);
  crossSection_pPb_13d->SetMarkerColor(kRed);
  crossSection_pPb_13d->SetMarkerSize(2);
  crossSection_pPb_13d->SetMarkerStyle(kOpenCircle);

  crossSection_pPb_13e->SetLineColor(kBlue);
  crossSection_pPb_13e->SetLineWidth(1);
  crossSection_pPb_13e->SetMarkerColor(kBlue);
  crossSection_pPb_13e->SetMarkerSize(2);
  crossSection_pPb_13e->SetMarkerStyle(kOpenSquare);

  crossSection_pPb_13fOld->SetLineColor(kMagenta);
  crossSection_pPb_13fOld->SetLineWidth(1);
  crossSection_pPb_13fOld->SetMarkerColor(kMagenta);
  crossSection_pPb_13fOld->SetMarkerSize(2);
  crossSection_pPb_13fOld->SetMarkerStyle(kStar);

  crossSection_pPb_13fNew->SetLineColor(kBlack);
  crossSection_pPb_13fNew->SetLineWidth(1);
  crossSection_pPb_13fNew->SetMarkerColor(kBlack);
  crossSection_pPb_13fNew->SetMarkerSize(2);
  crossSection_pPb_13fNew->SetMarkerStyle(kOpenDiamond);

  crossSection_pPb_13fpart1->SetLineColor(kCyan);
  crossSection_pPb_13fpart1->SetLineWidth(1);
  crossSection_pPb_13fpart1->SetMarkerColor(kCyan);
  crossSection_pPb_13fpart1->SetMarkerSize(2);
  crossSection_pPb_13fpart1->SetMarkerStyle(kOpenSquare);
  
  crossSection_pPb_13fpart2->SetLineColor(kCyan);
  crossSection_pPb_13fpart2->SetLineWidth(1);
  crossSection_pPb_13fpart2->SetMarkerColor(kCyan);
  crossSection_pPb_13fpart2->SetMarkerSize(2);
  crossSection_pPb_13fpart2->SetMarkerStyle(kOpenCircle);

  crossSection_pPb_13fpart3->SetLineColor(kCyan);
  crossSection_pPb_13fpart3->SetLineWidth(1);
  crossSection_pPb_13fpart3->SetMarkerColor(kCyan);
  crossSection_pPb_13fpart3->SetMarkerSize(2);
  crossSection_pPb_13fpart3->SetMarkerStyle(kStar);

  crossSection_pPb_13fpart4->SetLineColor(kCyan);
  crossSection_pPb_13fpart4->SetLineWidth(1);
  crossSection_pPb_13fpart4->SetMarkerColor(kCyan);
  crossSection_pPb_13fpart4->SetMarkerSize(2);
  crossSection_pPb_13fpart4->SetMarkerStyle(kOpenCross);

  crossSection_pPb_13fpart5->SetLineColor(kCyan);
  crossSection_pPb_13fpart5->SetLineWidth(1);
  crossSection_pPb_13fpart5->SetMarkerColor(kCyan);
  crossSection_pPb_13fpart5->SetMarkerSize(2);
  crossSection_pPb_13fpart5->SetMarkerStyle(kOpenTriangleUp);

  
  TLegend* l_crossSection = new TLegend(0.125, 0.125, 0.325, 0.425);
  l_crossSection->SetHeader("Run periods", "c");
  l_crossSection->AddEntry(crossSection_pPb_13d, "13d");
  l_crossSection->AddEntry(crossSection_pPb_13e, "13e");
  l_crossSection->AddEntry(crossSection_pPb_13fOld, "13f Old");
  l_crossSection->AddEntry(crossSection_pPb_13fNew, "13f New");
  l_crossSection->AddEntry(crossSection_pPb_13fpart1, "13f part1");
  l_crossSection->AddEntry(crossSection_pPb_13fpart2, "13f part2");
  l_crossSection->AddEntry(crossSection_pPb_13fpart3, "13f part3");
  l_crossSection->AddEntry(crossSection_pPb_13fpart4, "13f part4");
  //l_crossSection->AddEntry(crossSection_pPb_13fpart5, "13f part5");

  //crossSection_pPb_13d->SetTitle("Cross Section");
  crossSection_pPb_13d->GetYaxis()->SetRangeUser(1, 1e4);
  TCanvas* c_crossSection = new TCanvas("c_crossSection", "c_crossSection");
  c_crossSection->SetLogy();
  crossSection_pPb_13d->Draw("e1");
  crossSection_pPb_13e->Draw("samee1");
  crossSection_pPb_13fOld->Draw("samee1");
  crossSection_pPb_13fNew->Draw("samee1");
  crossSection_pPb_13fpart1->Draw("samee1");
  crossSection_pPb_13fpart2->Draw("samee1");
  crossSection_pPb_13fpart3->Draw("samee1");
  crossSection_pPb_13fpart4->Draw("samee1");
  //crossSection_pPb_13fpart5->Draw("samee1");
  l_crossSection->Draw("same");

  //Cross Section Ratios
  TH1D* crossSection_pPb_13d_ratio = (TH1D*)crossSection_pPb_13d->Clone();
  TH1D* crossSection_pPb_13e_ratio = (TH1D*)crossSection_pPb_13e->Clone();
  TH1D* crossSection_pPb_13fOld_ratio = (TH1D*)crossSection_pPb_13fOld->Clone();
  TH1D* crossSection_pPb_13fNew_ratio = (TH1D*)crossSection_pPb_13fNew->Clone();
  TH1D* crossSection_pPb_13fpart1_ratio = (TH1D*)crossSection_pPb_13fpart1->Clone();
  TH1D* crossSection_pPb_13fpart2_ratio = (TH1D*)crossSection_pPb_13fpart2->Clone();
  TH1D* crossSection_pPb_13fpart3_ratio = (TH1D*)crossSection_pPb_13fpart3->Clone();
  TH1D* crossSection_pPb_13fpart4_ratio = (TH1D*)crossSection_pPb_13fpart4->Clone();
  TH1D* crossSection_pPb_13fpart5_ratio = (TH1D*)crossSection_pPb_13fpart5->Clone();

  crossSection_pPb_13d_ratio->Divide(crossSection_pPb_13fNew_ratio);
  crossSection_pPb_13e_ratio->Divide(crossSection_pPb_13fNew_ratio);
  crossSection_pPb_13fOld_ratio->Divide(crossSection_pPb_13fNew_ratio);
  crossSection_pPb_13fpart1_ratio->Divide(crossSection_pPb_13fNew_ratio);
  crossSection_pPb_13fpart2_ratio->Divide(crossSection_pPb_13fNew_ratio);
  crossSection_pPb_13fpart3_ratio->Divide(crossSection_pPb_13fNew_ratio);
  crossSection_pPb_13fpart4_ratio->Divide(crossSection_pPb_13fNew_ratio);
  crossSection_pPb_13fpart5_ratio->Divide(crossSection_pPb_13fNew_ratio);
  crossSection_pPb_13fNew_ratio->Divide(crossSection_pPb_13fNew_ratio);
    
  TLegend* l_crossSectionRatio = new TLegend(0.125, 0.125, 0.325, 0.425);
  l_crossSectionRatio->SetHeader("Run periods", "c");
  l_crossSectionRatio->AddEntry(crossSection_pPb_13d_ratio, "13d");
  l_crossSectionRatio->AddEntry(crossSection_pPb_13e_ratio, "13e");
  l_crossSectionRatio->AddEntry(crossSection_pPb_13fOld_ratio, "13f Old");
  //l_crossSectionRatio->AddEntry(crossSection_pPb_13fNew_ratio, "13f New");
  l_crossSectionRatio->AddEntry(crossSection_pPb_13fpart1_ratio, "13f part1");
  l_crossSectionRatio->AddEntry(crossSection_pPb_13fpart2_ratio, "13f part2");
  l_crossSectionRatio->AddEntry(crossSection_pPb_13fpart3_ratio, "13f part3");
  l_crossSectionRatio->AddEntry(crossSection_pPb_13fpart4_ratio, "13f part4");
  //l_crossSectionRatio->AddEntry(crossSection_pPb_13fpart5_ratio, "13f part5");

  crossSection_pPb_13d_ratio->SetTitle(";E_{T} [GeV];ratio to 13fNew");
  crossSection_pPb_13d_ratio->GetYaxis()->SetRangeUser(0,2);
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);
  line->SetLineWidth(5);
  TCanvas* c_crossSectionRatio = new TCanvas("c_crossSectionRatio", "c_crossSectionRatio");
  //c_crossSectionRatio->SetLogy();
  //crossSection_pPb_13fNew_ratio->Draw("");
  crossSection_pPb_13d_ratio->Draw("e1");
  crossSection_pPb_13e_ratio->Draw("samee1");
  crossSection_pPb_13fOld_ratio->Draw("samee1");
  crossSection_pPb_13fpart1_ratio->Draw("samee1");
  crossSection_pPb_13fpart2_ratio->Draw("samee1");
  crossSection_pPb_13fpart3_ratio->Draw("samee1");
  crossSection_pPb_13fpart4_ratio->Draw("samee1");
  //crossSection_pPb_13fpart5_ratio->Draw("samee1");
  line->Draw();
  l_crossSectionRatio->Draw("same");

  


  /*TFile* file13e_part1_new = new TFile("/global/homes/d/ddixit/photonCrossSection/13epart1_crossSectionHistos.root", "READ");
  TFile* file13e_part2_new = new TFile("/global/homes/d/ddixit/photonCrossSection/13epart2_crossSectionHistos.root","READ");  
  TFile* file13f_part1_new = new TFile("/global/homes/d/ddixit/photonCrossSection/13fpart1_crossSectionHistos.root", "READ");
  TFile* file13f_part2_new = new TFile("/global/homes/d/ddixit/photonCrossSection/13fpart2_crossSectionHistos.root","READ");
  TFile* file13f_part3_newer = new TFile("/global/homes/d/ddixit/photonCrossSection/13fpart3_crossSectionHistos.root","READ");
  TFile* file13f_part4 = new TFile("/global/homes/d/ddixit/photonCrossSection/13fpart4_crossSectionHistos.root","READ");
  TFile* file13f_part5_new = new TFile("/global/homes/d/ddixit/photonCrossSection/13fpart5_crossSectionHistos.root ","READ");

  

  
  TH1F* crossSection_pPb_13epart1_new = (TH1F*)file13e_part1_new->Get("crossSection_pPb");     
  TH1F* crossSection_pPb_13epart2_new = (TH1F*)file13e_part2_new->Get("crossSection_pPb");     
  TH1F* crossSection_pPb_part1_new = (TH1F*)file13f_part1_new->Get("crossSection_pPb");     
  TH1F* crossSection_pPb_part2_new = (TH1F*)file13f_part2_new->Get("crossSection_pPb");     
  TH1F* crossSection_pPb_part3_newer = (TH1F*)file13f_part3_newer->Get("crossSection_pPb");
  TH1F* crossSection_pPb_part4 = (TH1F*)file13f_part4->Get("crossSection_pPb");
  TH1F* crossSection_pPb_part5_new = (TH1F*)file13f_part5_new->Get("crossSection_pPb");             

  
  
  
  crossSection_pPb_13epart1_new->SetName("crossSection_pPb_13epart1_new");
  crossSection_pPb_13epart2_new->SetName("crossSection_pPb_13epart2_new");
  crossSection_pPb_part1_new->SetName("crossSection_pPb_part1_new");
  crossSection_pPb_part2_new->SetName("crossSection_pPb_part2_new");
  crossSection_pPb_part3_newer->SetName("crossSection_pPb_part3_newer");
  crossSection_pPb_part4->SetName("crossSection_pPb_part4");
  crossSection_pPb_part5_new->SetName("crossSection_pPb_part5_new");
	

  /*crossSection_pPb_part1_new->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  crossSection_pPb_part2_new->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  crossSection_pPb_part3_newer->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  crossSection_pPb_part4->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");
  crossSection_pPb_part5_new->SetTitle(";E_{T} [GeV];#frac{1}{N_{ev}}#frac{dN}{dE_{T}}");//
  

  crossSection_pPb_part1_new->GetXaxis()->SetRangeUser(12,60);
  crossSection_pPb_part2_new->GetXaxis()->SetRangeUser(12,60);
  crossSection_pPb_part3_newer->GetXaxis()->SetRangeUser(12,60);

  
  //part1
  crossSection_pPb_part1->SetLineColor(kRed);
  crossSection_pPb_part1->SetLineWidth(1);
  crossSection_pPb_part1->SetMarkerColor(kRed);
  crossSection_pPb_part1->SetMarkerSize(2);
  crossSection_pPb_part1->SetMarkerStyle(kOpenCircle);
  
  crossSection_pPb_part1_new->SetLineColor(kRed);
  crossSection_pPb_part1_new->SetLineWidth(1);
  crossSection_pPb_part1_new->SetMarkerColor(kRed);
  crossSection_pPb_part1_new->SetMarkerSize(2);
  crossSection_pPb_part1_new->SetMarkerStyle(kOpenDiamond);
  
  //part2
  crossSection_pPb_part2->SetLineColor(kBlue);
  crossSection_pPb_part2->SetLineWidth(1);
  crossSection_pPb_part2->SetMarkerColor(kBlue);
  crossSection_pPb_part2->SetMarkerSize(2);
  crossSection_pPb_part2->SetMarkerStyle(kOpenSquare);
  
  crossSection_pPb_part2_new->SetLineColor(kBlue);
  crossSection_pPb_part2_new->SetLineWidth(1);
  crossSection_pPb_part2_new->SetMarkerColor(kBlue);
  crossSection_pPb_part2_new->SetMarkerSize(2);
  crossSection_pPb_part2_new->SetMarkerStyle(kOpenDoubleDiamond);
  
  //part3
  crossSection_pPb_part3->SetLineColor(kMagenta);
  crossSection_pPb_part3->SetLineWidth(1);
  crossSection_pPb_part3->SetMarkerColor(kMagenta);
  crossSection_pPb_part3->SetMarkerSize(2);
  crossSection_pPb_part3->SetMarkerStyle(kStar);
  
  crossSection_pPb_part3_new->SetLineColor(kOrange);
  crossSection_pPb_part3_new->SetLineWidth(1);
  crossSection_pPb_part3_new->SetMarkerColor(kOrange);
  crossSection_pPb_part3_new->SetMarkerSize(2);
  crossSection_pPb_part3_new->SetMarkerStyle(kOpenStar);
  
  crossSection_pPb_part3_newer->SetLineColor(kBlack);
  crossSection_pPb_part3_newer->SetLineWidth(1);
  crossSection_pPb_part3_newer->SetMarkerColor(kBlack);
  crossSection_pPb_part3_newer->SetMarkerSize(2);
  crossSection_pPb_part3_newer->SetMarkerStyle(kOpenCross);

  //part4
  crossSection_pPb_part4->SetLineColor(kGreen);
  crossSection_pPb_part4->SetLineWidth(1);
  crossSection_pPb_part4->SetMarkerColor(kGreen);
  crossSection_pPb_part4->SetMarkerSize(2);
  crossSection_pPb_part4->SetMarkerStyle(kOpenCircle);
  
  //part5
  crossSection_pPb_part5->SetLineColor(kCyan);
  crossSection_pPb_part5->SetLineWidth(1);
  crossSection_pPb_part5->SetMarkerColor(kCyan);
  crossSection_pPb_part5->SetMarkerSize(2);
  crossSection_pPb_part5->SetMarkerStyle(kOpenCircle);
  
  crossSection_pPb_part5_new->SetLineColor(kCyan);
  crossSection_pPb_part5_new->SetLineWidth(1);
  crossSection_pPb_part5_new->SetMarkerColor(kCyan);
  crossSection_pPb_part5_new->SetMarkerSize(2);
  crossSection_pPb_part5_new->SetMarkerStyle(kOpenDiamond);
  
  TLegend* l_13f = new TLegend(0.5, 0.6, 0.85, 0.85);
  l_13f->SetHeader("13f ntuple EG1 photon spectra", "c");
  l_13f->AddEntry(crossSection_pPb_part1, "1st set of 10 runs");
  l_13f->AddEntry(crossSection_pPb_part1_new, "1st set of 10 runs: failed jobs resubmitted once");
  l_13f->AddEntry(crossSection_pPb_part2, "2nd set of 10 runs");
  l_13f->AddEntry(crossSection_pPb_part2_new, "2nd set of 10 runs: failed jobs resubmitted once");
  l_13f->AddEntry(crossSection_pPb_part3, "3rd set of 10 runs");
  l_13f->AddEntry(crossSection_pPb_part3_new, "3rd set of 10 runs: failed jobs resubmitted once");
  l_13f->AddEntry(crossSection_pPb_part3_newer, "3rd set of 10 runs: failed jobs resubmitted twice");
  l_13f->AddEntry(crossSection_pPb_part4, "4th set of 10 runs");
  l_13f->AddEntry(crossSection_pPb_part5, "5th set of 3 runs");
  l_13f->AddEntry(crossSection_pPb_part5_new, "5th set of 3 runs: failed jobs submmited once");
  
  TCanvas* c_13f = new TCanvas("c_13f", "c_13f");
  c_13f->SetLogy();
  crossSection_pPb_part1->Draw("e1");
  crossSection_pPb_part2->Draw("samee1");
  crossSection_pPb_part3->Draw("samee1");
  crossSection_pPb_part1_new->Draw("samee1");
  crossSection_pPb_part2_new->Draw("samee1");
  crossSection_pPb_part3_new->Draw("samee1");
  crossSection_pPb_part3_newer->Draw("samee1");
  crossSection_pPb_part4->Draw("samee1");
  crossSection_pPb_part5->Draw("samee1");
  crossSection_pPb_part5_new->Draw("samee1");
  l_13f->Draw("same");//*/
  






  
  /////////////////////////////RpA//////////////////////////////
  TH1F* h_RpA_13d = (TH1F*)file13d->Get("h_RpA");
  TH1F* h_RpA_13e = (TH1F*)file13e->Get("h_RpA");
  TH1F* h_RpA_13fOld = (TH1F*)file13fOld->Get("h_RpA");
  TH1F* h_RpA_13fNew = (TH1F*)file13fNew->Get("h_RpA");
  
  h_RpA_13d->SetName("h_RpA_13d");
  h_RpA_13e->SetName("h_RpA_13e");
  h_RpA_13fOld->SetName("h_RpA_13fOld");
  h_RpA_13fNew->SetName("h_RpA_13fNew");
  
  h_RpA_13d->SetLineColor(kRed);
  h_RpA_13d->SetLineWidth(1);
  h_RpA_13d->SetMarkerColor(kRed);
  h_RpA_13d->SetMarkerSize(2);
  h_RpA_13d->SetMarkerStyle(kOpenCircle);

  h_RpA_13e->SetLineColor(kBlue);
  h_RpA_13e->SetLineWidth(1);
  h_RpA_13e->SetMarkerColor(kBlue);
  h_RpA_13e->SetMarkerSize(2);
  h_RpA_13e->SetMarkerStyle(kOpenSquare);

  h_RpA_13fOld->SetLineColor(kMagenta);
  h_RpA_13fOld->SetLineWidth(1);
  h_RpA_13fOld->SetMarkerColor(kMagenta);
  h_RpA_13fOld->SetMarkerSize(2);
  h_RpA_13fOld->SetMarkerStyle(kStar);

  h_RpA_13fNew->SetLineColor(kCyan);
  h_RpA_13fNew->SetLineWidth(1);
  h_RpA_13fNew->SetMarkerColor(kCyan);
  h_RpA_13fNew->SetMarkerSize(2);
  h_RpA_13fNew->SetMarkerStyle(kOpenDiamond);

  
  TLegend* l_h_RpA = new TLegend(0.6, 0.7, 0.9, 0.85);
  l_h_RpA->SetHeader("RpA for different run periods", "c");
  l_h_RpA->AddEntry(h_RpA_13d, "13d");
  l_h_RpA->AddEntry(h_RpA_13e, "13e");
  l_h_RpA->AddEntry(h_RpA_13fOld, "13df Old");
  l_h_RpA->AddEntry(h_RpA_13fNew, "13f New");

  /*TCanvas* c_h_RpA = new TCanvas("c_h_RpA", "c_h_RpA");
  h_RpA_13d->Draw("e1");
  h_RpA_13e->Draw("samee1");
  h_RpA_13fOld->Draw("samee1");
  h_RpA_13fNew->Draw("samee1");
  l_h_RpA->Draw("same");
  line->Draw("same");//*/



  /////////////////////////////Erwann Compare//////////////////////////////
  TH1F* crossSectionRatio_EG1_13d = (TH1F*)file13d->Get("crossSectionRatio_EG1");
  TH1F* crossSectionRatio_EG1_13e = (TH1F*)file13e->Get("crossSectionRatio_EG1");
  TH1F* crossSectionRatio_EG1_13fOld = (TH1F*)file13fOld->Get("crossSectionRatio_EG1");
  TH1F* crossSectionRatio_EG1_13fNew = (TH1F*)file13fNew->Get("crossSectionRatio_EG1");
  
  crossSectionRatio_EG1_13d->SetName("crossSectionRatio_EG1_13d");
  crossSectionRatio_EG1_13e->SetName("crossSectionRatio_EG1_13e");
  crossSectionRatio_EG1_13fOld->SetName("crossSectionRatio_EG1_13fOld");
  crossSectionRatio_EG1_13fNew->SetName("crossSectionRatio_EG1_13fNew");
  
  crossSectionRatio_EG1_13d->SetLineColor(kRed);
  crossSectionRatio_EG1_13d->SetLineWidth(1);
  crossSectionRatio_EG1_13d->SetMarkerColor(kRed);
  crossSectionRatio_EG1_13d->SetMarkerSize(2);
  crossSectionRatio_EG1_13d->SetMarkerStyle(kOpenCircle);

  crossSectionRatio_EG1_13e->SetLineColor(kBlue);
  crossSectionRatio_EG1_13e->SetLineWidth(1);
  crossSectionRatio_EG1_13e->SetMarkerColor(kBlue);
  crossSectionRatio_EG1_13e->SetMarkerSize(2);
  crossSectionRatio_EG1_13e->SetMarkerStyle(kOpenSquare);

  crossSectionRatio_EG1_13fOld->SetLineColor(kMagenta);
  crossSectionRatio_EG1_13fOld->SetLineWidth(1);
  crossSectionRatio_EG1_13fOld->SetMarkerColor(kMagenta);
  crossSectionRatio_EG1_13fOld->SetMarkerSize(2);
  crossSectionRatio_EG1_13fOld->SetMarkerStyle(kStar);

  crossSectionRatio_EG1_13fNew->SetLineColor(kCyan);
  crossSectionRatio_EG1_13fNew->SetLineWidth(1);
  crossSectionRatio_EG1_13fNew->SetMarkerColor(kCyan);
  crossSectionRatio_EG1_13fNew->SetMarkerSize(2);
  crossSectionRatio_EG1_13fNew->SetMarkerStyle(kOpenDiamond);

  
  TLegend* l_crossSectionRatio_EG1 = new TLegend(0.6, 0.7, 0.9, 0.85);
  l_crossSectionRatio_EG1->SetHeader("RpA for different run periods", "c");
  l_crossSectionRatio_EG1->AddEntry(crossSectionRatio_EG1_13d, "13d");
  l_crossSectionRatio_EG1->AddEntry(crossSectionRatio_EG1_13e, "13e");
  l_crossSectionRatio_EG1->AddEntry(crossSectionRatio_EG1_13fOld, "13df Old");
  l_crossSectionRatio_EG1->AddEntry(crossSectionRatio_EG1_13fNew, "13f New");

  /*TCanvas* c_crossSectionRatio_EG1 = new TCanvas("c_crossSectionRatio_EG1", "c_crossSectionRatio_EG1");
  crossSectionRatio_EG1_13d->Draw("e1");
  crossSectionRatio_EG1_13e->Draw("samee1");
  crossSectionRatio_EG1_13fOld->Draw("samee1");
  crossSectionRatio_EG1_13fNew->Draw("samee1");
  l_crossSectionRatio_EG1->Draw("same");
  line->Draw("same");//*/

  TFile* fileErwannNico = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_13fpart12345_crossSectionHistos_newppRFErwannNico.root", "READ");
  TFile* file560all = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_13fpart12345_crossSectionHistos_newppRF560all.root", "READ");
  TFile* file1060all = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_13fpart12345_crossSectionHistos_newppRF1060all.root", "READ");

  TH1F* crossSection_ppEN = (TH1F*)fileErwannNico->Get("crossSection_pp");
  crossSection_ppEN->SetName("crossSection_ppEN");
  TH1F* crossSection_pp5 = (TH1F*)file560all->Get("crossSection_pp");
  crossSection_pp5->SetName("crossSection_pp5");
  TH1F* crossSection_pp10 = (TH1F*)file1060all->Get("crossSection_pp");
  crossSection_pp10->SetName("crossSection_pp10");

  
  crossSection_ppEN->SetLineColor(kBlue);
  crossSection_ppEN->SetLineWidth(1);
  crossSection_ppEN->SetMarkerColor(kBlue);
  crossSection_ppEN->SetMarkerSize(2);
  crossSection_ppEN->SetMarkerStyle(kOpenSquare);

  crossSection_pp5->SetLineColor(kCyan);
  crossSection_pp5->SetLineWidth(1);
  crossSection_pp5->SetMarkerColor(kCyan);
  crossSection_pp5->SetMarkerSize(2);
  crossSection_pp5->SetMarkerStyle(kStar);

  crossSection_pp10->SetLineColor(kRed);
  crossSection_pp10->SetLineWidth(1);
  crossSection_pp10->SetMarkerColor(kRed);
  crossSection_pp10->SetMarkerSize(2);
  crossSection_pp10->SetMarkerStyle(kOpenDiamond);

  TLegend* l_crossSection_pp = new TLegend(0.6, 0.7, 0.9, 0.85);
  l_crossSection_pp->SetHeader("Cross Section using different RF", "c");
  l_crossSection_pp->AddEntry(crossSection_ppEN, "Nico");
  l_crossSection_pp->AddEntry(crossSection_pp5, "5-60 GeV Fit");
  l_crossSection_pp->AddEntry(crossSection_pp10, "10-60 GeV Fit");

  crossSection_ppEN->GetXaxis()->SetRangeUser(12,60);
  TCanvas* c_crossSection_pp = new TCanvas("c_crossSection_pp","c_crossSection_pp");
  c_crossSection_pp->SetLogy();
  crossSection_ppEN->Draw("e1");
  crossSection_pp5->Draw("samee1");
  crossSection_pp10->Draw("samee1");
  l_crossSection_pp->Draw("same");

  TH1F* crossSectionRatio_pp5 = (TH1F*)crossSection_pp5->Clone();
  TH1F* crossSectionRatio_pp10 = (TH1F*)crossSection_pp10->Clone();
  TH1F* crossSectionRatio_ppEN = (TH1F*)crossSection_ppEN->Clone();
  crossSectionRatio_pp5->Divide(crossSection_ppEN);
  crossSectionRatio_pp10->Divide(crossSection_ppEN);
  crossSectionRatio_ppEN->Divide(crossSection_ppEN);

  TLegend* l_crossSectionRatio_pp = new TLegend(0.6, 0.7, 0.9, 0.85);
  l_crossSectionRatio_pp->SetHeader("Ratio using different RF", "c");
  l_crossSectionRatio_pp->AddEntry(crossSection_pp5, "5-60 GeV Fit");
  l_crossSectionRatio_pp->AddEntry(crossSection_pp10, "10-60 GeV Fit");

  crossSectionRatio_ppEN->GetXaxis()->SetRangeUser(0,2);
  TCanvas* c_crossSectionRatio_pp = new TCanvas("c_crossSectionRatio_pp","c_crossSectionRatio_pp");
  c_crossSectionRatio_pp->SetLogy();
  crossSectionRatio_ppEN->Draw("");
  crossSectionRatio_pp5->Draw("samee1");
  crossSectionRatio_pp10->Draw("samee1");
  l_crossSectionRatio_pp->Draw("same");
}//end makeComparisons
