/*#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <bits/stdc++.h>
#include <cstring>//*/

TH1F* makeDataBinningHists(const char* name, TH1* xsecionHist, Double_t nucleons){


  const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14


  TH1F* h1 = new TH1F(name, "", nbinscluster, clusterbins);
  xsecionHist->Scale(nucleons);
  for(int i = 1; i < h1->GetNbinsX()+1; i++){
    Double_t binWidth = h1->GetBinWidth(i);
    Double_t xlow = h1->GetBinLowEdge(i);
    Double_t xhigh = h1->GetBinLowEdge(i+1);
    
    Double_t xbinNumLow = xsecionHist->FindBin(xlow);
    Double_t xbinNumHigh = xsecionHist->FindBin(xhigh);
    Double_t xlowTheory = xsecionHist->GetBinLowEdge(xbinNumLow);
    Double_t xhighTheory = xsecionHist->GetBinLowEdge(xbinNumHigh);
    Double_t binIntegral = xsecionHist->Integral(xbinNumLow, xbinNumHigh, "width");
    Double_t content = binIntegral/binWidth;
    
    h1->SetBinContent(i, content);
    //h1->SetBinError(i, 1);
    //cout << xlow << "\t" << xlowTheory << "\t" << xhigh << "\t" << xhighTheory << endl;
  }

  return h1;
  
}

void styleHist(TH1* hist,
	       Color_t lcolor = 1, Style_t lstyle = 1, Width_t lwidth = 1,
	       Color_t mcolor = 1, Style_t mstyle = 20, Size_t msize = 2){

  hist->SetLineColor(lcolor);
  hist->SetLineStyle(lstyle);
  hist->SetLineWidth(lwidth);
  hist->SetMarkerColor(mcolor);
  hist->SetMarkerStyle(mstyle);
  hist->SetMarkerSize(msize);
  
}

TH1F* getRatio(const char *name, TH1F* dataHist, TH1F* theoryHist){

  TH1F* h1 = (TH1F*)dataHist->Clone(name);

  //cout << name << "\t" << numEvents_Data << endl;
  //Double_t numEvents_MC = mcEventsHist->GetBinContent(8);//bin 8 = with weights
  for(int i = 1; i < dataHist->GetNbinsX()+1; i++){
    Double_t dEta = dataHist->GetBinWidth(i);

    Double_t content_Data = dataHist->GetBinContent(i);
    Double_t error_Data  =  dataHist->GetBinError(i);

    Double_t content_Theory = theoryHist->GetBinContent(i);

    Double_t content_Ratio = content_Data/content_Theory;
    Double_t error_Ratio = content_Ratio*error_Data/content_Data;
    if(content_Theory != 0){
      h1->SetBinContent(i, content_Ratio);
      h1->SetBinError(i, error_Ratio);
    }

    
  }

  return h1;
    
  
}

void compareWithJETPHOX(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/";

  const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14

  TFile* file_JETPHOX_pPb = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/JETPHOX/2022_03_24_JETPHOX_NLO_5020GeV_5Mevts_NNPDF40_0_nNNPDF30_0_iso2GeVinR04.root"), "READ");
  TFile* file_JETPHOX_pp = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/JETPHOX/2022_03_24_JETPHOX_NLO_5020GeV_5Mevts_NNPDF40_0_NNPDF40_0_iso2GeVinR04.root"), "READ");
  //TFile* file_JETPHOX = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/JETPHOX/"), "READ");
  
  TH1D* xsection_nlo_TOTAL_05_pPb = (TH1D*)file_JETPHOX_pPb->Get("xsection_nlo_TOTAL_scl_05_05_05");
  TH1D* xsection_nlo_TOTAL_10_pPb = (TH1D*)file_JETPHOX_pPb->Get("xsection_nlo_TOTAL_scl_10_10_10");
  TH1D* xsection_nlo_TOTAL_20_pPb = (TH1D*)file_JETPHOX_pPb->Get("xsection_nlo_TOTAL_scl_20_20_20");
  //xsection_nlo_TOTAL_05_pPb->Scale(208.0);
  //xsection_nlo_TOTAL_10_pPb->Scale(208.0);
  //xsection_nlo_TOTAL_20_pPb->Scale(208.0);
  
  //5.02 TeV hists
  TFile* file_5pPb = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PurityFit_postQM_pPbAndpp_wPhiCorr.root"), "READ");
  TH1F* crossSection_pPb = (TH1F*)file_5pPb->Get("crossSection_pPb");
  
  //TH1F* jetphox_pPb_05 = new TH1F("jetphox_pPb_05", "", nbinscluster, clusterbins);
  //TH1F* jetphox_pPb_10 = new TH1F("jetphox_pPb_10", "", nbinscluster, clusterbins);
  //TH1F* jetphox_pPb_20 = new TH1F("jetphox_pPb_20", "", nbinscluster, clusterbins);
  TH1F* jetphox_pPb_05 = makeDataBinningHists("jetphox_pPb_05", xsection_nlo_TOTAL_05_pPb, 208.0);
  TH1F* jetphox_pPb_10 = makeDataBinningHists("jetphox_pPb_10", xsection_nlo_TOTAL_10_pPb, 208.0);
  TH1F* jetphox_pPb_20 = makeDataBinningHists("jetphox_pPb_20", xsection_nlo_TOTAL_20_pPb, 208.0);
  TH1F* jetphox_pPb_05_ratio = new TH1F("jetphox_pPb_05_ratio", ";p_{T} [GeV/c];data/NLO JETPHOX", nbinscluster, clusterbins);
  TH1F* jetphox_pPb_10_ratio = new TH1F("jetphox_pPb_10_ratio", ";p_{T} [GeV/c];data/NLO JETPHOX", nbinscluster, clusterbins);
  TH1F* jetphox_pPb_20_ratio = new TH1F("jetphox_pPb_20_ratio", ";p_{T} [GeV/c];data/NLO JETPHOX", nbinscluster, clusterbins);
  /*for(int i = 1; i < jetphox_pPb_05->GetNbinsX()+1; i++){
    Double_t binWidth = jetphox_pPb_05->GetBinWidth(i);
    Double_t xlow = jetphox_pPb_05->GetBinLowEdge(i);
    Double_t xhigh = jetphox_pPb_05->GetBinLowEdge(i+1);

    Int_t xbinNumLow_05 = xsection_nlo_TOTAL_05_pPb->FindBin(xlow);
    Int_t xbinNumHigh_05 = xsection_nlo_TOTAL_05_pPb->FindBin(xhigh);
    Double_t xlowTheory_05 = xsection_nlo_TOTAL_05_pPb->GetBinLowEdge(xbinNumLow_05);
    Double_t xhighTheory_05 = xsection_nlo_TOTAL_05_pPb->GetBinLowEdge(xbinNumHigh_05);
    Double_t binIntegral_05 = xsection_nlo_TOTAL_05_pPb->Integral(xbinNumLow_05, xbinNumHigh_05, "width");//*(xhighTheory_05-xlowTheory_05);
    Double_t content_05 = binIntegral_05/binWidth;

    jetphox_pPb_05->SetBinContent(i, content_05);
    //cout << xlow << "\t" << xlowTheory << "\t" << xhigh << "\t" << xhighTheory << endl;
    }//*/

  styleHist(xsection_nlo_TOTAL_05_pPb, kRed, kDashed, 2, kRed, kDot, 1);
  styleHist(xsection_nlo_TOTAL_10_pPb, kRed, kSolid, 2, kRed, kDot, 1);
  styleHist(xsection_nlo_TOTAL_20_pPb, kRed, kDotted, 2, kRed, kDot, 1);
  styleHist(jetphox_pPb_05, kMagenta, kDashed, 2, kMagenta, kOpenSquare, 2);
  styleHist(jetphox_pPb_10, kMagenta, kSolid, 1, kMagenta, kOpenTriangleUp, 2);
  styleHist(jetphox_pPb_20, kMagenta, kDotted, 1, kMagenta, kOpenCircle, 2);

  crossSection_pPb->GetXaxis()->SetRangeUser(12, 60);
  TCanvas* c_pPb = new TCanvas("c_pPb", "c_pPb");
  c_pPb->SetLogy();
  crossSection_pPb->Draw("e1");
  xsection_nlo_TOTAL_05_pPb->Draw("same L hist");
  xsection_nlo_TOTAL_10_pPb->Draw("same L hist");
  xsection_nlo_TOTAL_20_pPb->Draw("same L hist");
  jetphox_pPb_05->Draw("same P");
  jetphox_pPb_10->Draw("same P");
  jetphox_pPb_20->Draw("same P");

  TLegend* leg_pPb = new TLegend(0.5, 0.65, 0.85, 0.85);
  leg_pPb->SetHeader("5.02 TeV p-Pb");
  leg_pPb->AddEntry(crossSection_pPb, "data");
  leg_pPb->AddEntry(xsection_nlo_TOTAL_05_pPb, "JETPHOX #mu = 0.5p_{T}");
  leg_pPb->AddEntry(xsection_nlo_TOTAL_10_pPb, "JETPHOX #mu = 1.0p_{T}");
  leg_pPb->AddEntry(xsection_nlo_TOTAL_20_pPb, "JETPHOX #mu = 2.0p_{T}");
  leg_pPb->AddEntry(jetphox_pPb_05, "scale = 0.5p_{T}");
  leg_pPb->AddEntry(jetphox_pPb_10, "scale = 1.0p_{T}");
  leg_pPb->AddEntry(jetphox_pPb_20, "scale = 2.0p_{T}");
  leg_pPb->Draw("same");

  TH1D* xsection_nlo_TOTAL_05_pp = (TH1D*)file_JETPHOX_pp->Get("xsection_nlo_TOTAL_scl_05_05_05");
  TH1D* xsection_nlo_TOTAL_10_pp = (TH1D*)file_JETPHOX_pp->Get("xsection_nlo_TOTAL_scl_10_10_10");
  TH1D* xsection_nlo_TOTAL_20_pp = (TH1D*)file_JETPHOX_pp->Get("xsection_nlo_TOTAL_scl_20_20_20");
  TH1F* crossSection_pp = (TH1F*)file_5pPb->Get("crossSection_pp");
  TH1F* jetphox_pp_05 = makeDataBinningHists("jetphox_pp_05", xsection_nlo_TOTAL_05_pp, 1.0);
  TH1F* jetphox_pp_10 = makeDataBinningHists("jetphox_pp_10", xsection_nlo_TOTAL_10_pp, 1.0);
  TH1F* jetphox_pp_20 = makeDataBinningHists("jetphox_pp_20", xsection_nlo_TOTAL_20_pp, 1.0);
  styleHist(xsection_nlo_TOTAL_05_pp, kCyan, kDashed, 2, kCyan, kDot, 1);
  styleHist(xsection_nlo_TOTAL_10_pp, kCyan, kSolid, 2, kCyan, kDot, 1);
  styleHist(xsection_nlo_TOTAL_20_pp, kCyan, kDotted, 2, kCyan, kDot, 1);
  styleHist(jetphox_pp_05, kBlue, kDashed, 2, kBlue, kOpenSquare, 2);
  styleHist(jetphox_pp_10, kBlue, kSolid, 1, kBlue, kOpenTriangleUp, 2);
  styleHist(jetphox_pp_20, kBlue, kDotted, 1, kBlue, kOpenCircle, 2);
  crossSection_pp->GetXaxis()->SetRangeUser(12, 60);
  TCanvas* c_pp = new TCanvas("c_pp", "c_pp");
  c_pp->SetLogy();
  crossSection_pp->Draw("e1");
  xsection_nlo_TOTAL_05_pp->Draw("same L hist");
  xsection_nlo_TOTAL_10_pp->Draw("same L hist");
  xsection_nlo_TOTAL_20_pp->Draw("same L hist");
  jetphox_pp_05->Draw("same P");
  jetphox_pp_10->Draw("same P");
  jetphox_pp_20->Draw("same P");

  TLegend* leg_pp = new TLegend(0.5, 0.65, 0.85, 0.85);
  leg_pp->SetHeader("5.02 TeV p-p");
  leg_pp->AddEntry(crossSection_pp, "data");
  leg_pp->AddEntry(xsection_nlo_TOTAL_05_pp, "JETPHOX #mu = 0.5p_{T}");
  leg_pp->AddEntry(xsection_nlo_TOTAL_10_pp, "JETPHOX #mu = 1.0p_{T}");
  leg_pp->AddEntry(xsection_nlo_TOTAL_20_pp, "JETPHOX #mu = 2.0p_{T}");
  leg_pp->AddEntry(jetphox_pp_05, "scale = 0.5p_{T}");
  leg_pp->AddEntry(jetphox_pp_10, "scale = 1.0p_{T}");
  leg_pp->AddEntry(jetphox_pp_20, "scale = 2.0p_{T}");
  leg_pp->Draw("same");


  TH1F* rpa_nlo_TOTAL_05 = (TH1F*)xsection_nlo_TOTAL_05_pPb->Clone("rpa_nlo_TOTAL_05");
  rpa_nlo_TOTAL_05->Scale(1.0/208.0);
  rpa_nlo_TOTAL_05->Divide(xsection_nlo_TOTAL_05_pp);
  TH1F* rpa_nlo_TOTAL_10 = (TH1F*)xsection_nlo_TOTAL_10_pPb->Clone("rpa_nlo_TOTAL_10");
  rpa_nlo_TOTAL_10->Scale(1.0/208.0);
  rpa_nlo_TOTAL_10->Divide(xsection_nlo_TOTAL_10_pp);
  TH1F* rpa_nlo_TOTAL_20 = (TH1F*)xsection_nlo_TOTAL_20_pPb->Clone("rpa_nlo_TOTAL_20");
  rpa_nlo_TOTAL_20->Scale(1.0/208.0);
  rpa_nlo_TOTAL_20->Divide(xsection_nlo_TOTAL_20_pp);
  //TH1F* jetphox_rpa_05 = makeDataBinningHists("jetphox_rpa_05", rpa_nlo_TOTAL_05, 1.0);
  //TH1F* jetphox_rpa_10 = makeDataBinningHists("jetphox_rpa_10", rpa_nlo_TOTAL_10, 1.0);
  //TH1F* jetphox_rpa_20 = makeDataBinningHists("jetphox_rpa_20", rpa_nlo_TOTAL_20, 1.0);
  TH1F* jetphox_rpa_05 = (TH1F*)jetphox_pPb_05->Clone("jetphox_rpa_10");
  jetphox_rpa_05->Scale(1.0/208.0);
  jetphox_rpa_05->Divide(jetphox_pp_05);
  TH1F* jetphox_rpa_10 = (TH1F*)jetphox_pPb_10->Clone("jetphox_rpa_10");
  jetphox_rpa_10->Scale(1.0/208.0);
  jetphox_rpa_10->Divide(jetphox_pp_10);
  TH1F* jetphox_rpa_20 = (TH1F*)jetphox_pPb_20->Clone("jetphox_rpa_10");
  jetphox_rpa_20->Scale(1.0/208.0);
  jetphox_rpa_20->Divide(jetphox_pp_20);
  styleHist(rpa_nlo_TOTAL_05, kMagenta, kDashed, 2, kMagenta, kDot, 1);
  styleHist(rpa_nlo_TOTAL_10, kMagenta, kSolid, 2, kMagenta, kDot, 1);
  styleHist(rpa_nlo_TOTAL_20, kMagenta, kDotted, 2, kMagenta, kDot, 1);
  styleHist(jetphox_rpa_05, kViolet+3, kDashed, 2, kViolet+3, kFullSquare, 2);
  styleHist(jetphox_rpa_10, kViolet+3, kSolid, 1, kViolet+3, kFullTriangleUp, 2);
  styleHist(jetphox_rpa_20, kViolet+3, kDotted, 1, kViolet+3, kFullCircle, 2);

  Double_t epps16_x[7] = {7.5, 17.7, 27.5, 37.5, 47.5, 57.5, 67.5};
  Double_t epps16_y[7] = {0.81126, 0.90616, 0.95391, 0.98635, 1, 1.01158, 1.01745};
  TGraph* EPPS16 = new TGraph(7, epps16_x, epps16_y);
  EPPS16->SetLineColor(kBlue);
  EPPS16->SetLineWidth(6);
  EPPS16->SetLineStyle(9);
  //unity --> line at 1
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);
  line->SetLineStyle(kDashed);
  line->SetLineWidth(4);
  
  TH1F* h_RpA = (TH1F*)file_5pPb->Get("h_RpA");
  h_RpA->GetXaxis()->SetRangeUser(12, 60);
  h_RpA->GetYaxis()->SetRangeUser(0.5, 1.5);
  TCanvas* c_rpa = new TCanvas("c_rpa", "c_pp");
  h_RpA->Draw("e1");
  rpa_nlo_TOTAL_05->Draw("L hist same");
  rpa_nlo_TOTAL_10->Draw("L hist same");
  rpa_nlo_TOTAL_20->Draw("L hist same");
  jetphox_rpa_05->Draw("same hist P");
  jetphox_rpa_10->Draw("same hist P");
  jetphox_rpa_20->Draw("same hist P");//*/
  EPPS16->Draw("same");
  line->Draw("same");
  TLegend* leg_rpa = new TLegend(0.13, 0.64, 0.5, 0.88);
  leg_rpa->SetHeader("#bf{5.02 TeV R_{pPb}}");
  leg_rpa->AddEntry(h_RpA, "data");
  leg_rpa->AddEntry(rpa_nlo_TOTAL_05, "JETPHOX #mu = 0.5p_{T}");
  leg_rpa->AddEntry(rpa_nlo_TOTAL_10, "JETPHOX #mu = 1.0p_{T}");
  leg_rpa->AddEntry(rpa_nlo_TOTAL_20, "JETPHOX #mu = 2.0p_{T}");
  leg_rpa->AddEntry(jetphox_rpa_05, "scale = 0.5p_{T}");
  leg_rpa->AddEntry(jetphox_rpa_10, "scale = 1.0p_{T}");
  leg_rpa->AddEntry(jetphox_rpa_20, "scale = 2.0p_{T}");
  leg_rpa->AddEntry(EPPS16, "5.02 TeV, p-Pb-->direct photon", "l");
  leg_rpa->AddEntry((TObject*)0, "NLO pQCD parton model, PDFs: CT14, EPPS16", "");
  leg_rpa->Draw("same");

  TH1F* compare_pPb_05 = getRatio("compare_pPb_05", crossSection_pPb, jetphox_pPb_05);
  TH1F* compare_pPb_10 = getRatio("compare_pPb_10", crossSection_pPb, jetphox_pPb_10);
  TH1F* compare_pPb_20 = getRatio("compare_pPb_20", crossSection_pPb, jetphox_pPb_20);
  styleHist(compare_pPb_05, kRed, kDashed, 2, kRed, kDot, 1);
  styleHist(compare_pPb_10, kRed, kSolid, 2, kRed, kFullCircle, 1);
  styleHist(compare_pPb_20, kRed, kDotted, 2, kRed, kDot, 1);
  compare_pPb_05->SetTitle(";E_{T} (GeV/c); Data/JETPHOX");
  compare_pPb_05->GetYaxis()->SetRangeUser(0.5, 1.5);
  TCanvas* c_comparepPb = new TCanvas("c_comparepPb", "c_comparepPb");
  compare_pPb_05->Draw("L hist");
  compare_pPb_20->Draw("same L hist");
  compare_pPb_10->Draw("same e1");
  TLegend* leg_comparepPb = new TLegend(0.13, 0.64, 0.5, 0.88);
  leg_comparepPb->SetHeader("#bf{5.02 TeV p-Pb}");
  leg_comparepPb->AddEntry(compare_pPb_05, "scale = 0.5p_{T}");
  leg_comparepPb->AddEntry(compare_pPb_10, "scale = 1.0p_{T}");
  leg_comparepPb->AddEntry(compare_pPb_20, "scale = 2.0p_{T}");
  leg_comparepPb->Draw("same");

  TH1F* compare_pp_05 = getRatio("compare_pp_05", crossSection_pp, jetphox_pp_05);
  TH1F* compare_pp_10 = getRatio("compare_pp_10", crossSection_pp, jetphox_pp_10);
  TH1F* compare_pp_20 = getRatio("compare_pp_20", crossSection_pp, jetphox_pp_20);
  styleHist(compare_pp_05, kBlue, kDashed, 2, kBlue, kDot, 1);
  styleHist(compare_pp_10, kBlue, kSolid, 2, kBlue, kFullCircle, 1);
  styleHist(compare_pp_20, kBlue, kDotted, 2, kBlue, kDot, 1);
  compare_pp_05->SetTitle(";E_{T} (GeV/c); Data/JETPHOX");
  compare_pp_05->GetYaxis()->SetRangeUser(0.5, 1.5);
  TCanvas* c_comparepp = new TCanvas("c_comparepp", "c_comparepp");
  compare_pp_05->Draw("L hist");
  compare_pp_20->Draw("same L hist");
  compare_pp_10->Draw("same e1");
  TLegend* leg_comparepp = new TLegend(0.13, 0.64, 0.5, 0.88);
  leg_comparepp->SetHeader("#bf{5.02 TeV pp}");
  leg_comparepp->AddEntry(compare_pp_05, "scale = 0.5p_{T}");
  leg_comparepp->AddEntry(compare_pp_10, "scale = 1.0p_{T}");
  leg_comparepp->AddEntry(compare_pp_20, "scale = 2.0p_{T}");
  leg_comparepp->Draw("same");

  TH1F* compare_rpa_05 = getRatio("compare_rpa_05", h_RpA, jetphox_rpa_05);
  TH1F* compare_rpa_10 = getRatio("compare_rpa_10", h_RpA, jetphox_rpa_10);
  TH1F* compare_rpa_20 = getRatio("compare_rpa_20", h_RpA, jetphox_rpa_20);
  styleHist(compare_rpa_05, kViolet, kDashed, 2, kViolet, kDot, 1);
  styleHist(compare_rpa_10, kViolet, kSolid, 2, kViolet, kFullCircle, 1);
  styleHist(compare_rpa_20, kViolet, kDotted, 2, kViolet, kDot, 1);
  compare_rpa_05->SetTitle(";E_{T} (GeV/c); Data/JETPHOX");
  compare_rpa_05->GetYaxis()->SetRangeUser(0.5, 1.5);
  TCanvas* c_comparerpa = new TCanvas("c_comparerpa", "c_comparerpa");
  compare_rpa_05->Draw("L hist");
  compare_rpa_20->Draw("same L hist");
  compare_rpa_10->Draw("same e1");
  TLegend* leg_comparerpa = new TLegend(0.13, 0.64, 0.5, 0.88);
  leg_comparerpa->SetHeader("#bf{5.02 TeV R_{pPb}}");
  leg_comparerpa->AddEntry(compare_rpa_05, "scale = 0.5p_{T}");
  leg_comparerpa->AddEntry(compare_rpa_10, "scale = 1.0p_{T}");
  leg_comparerpa->AddEntry(compare_rpa_20, "scale = 2.0p_{T}");
  leg_comparerpa->Draw("same");


  /*for(int i = 1; i < jetphox_pPb_20_ratio->GetNbinsX()+1; i++){
    Double_t dataContent = crossSection_pPb->GetBinContent(i);
    Double_t dataError = crossSection_pPb->GetBinError(i);
    Double_t content_05 = jetphox_pPb_05->GetBinContent(i);
    Double_t content_10 = jetphox_pPb_10->GetBinContent(i);
    Double_t content_20 = jetphox_pPb_20->GetBinContent(i);
    
    jetphox_pPb_05_ratio->SetBinContent(i, dataContent/content_05);
    jetphox_pPb_10_ratio->SetBinContent(i, dataContent/content_10);
    jetphox_pPb_20_ratio->SetBinContent(i, dataContent/content_20);
    //jetphox_pPb_05_ratio->SetBinError(i, (dataContent/content_05)*(dataError/dataContent));
    //jetphox_pPb_10_ratio->SetBinError(i, (dataContent/content_10)*(dataError/dataContent));
    //jetphox_pPb_20_ratio->SetBinError(i, (dataContent/content_20)*(dataError/dataContent));

    //cout << content_20 << " , ";
  }
  cout << endl;

  jetphox_pPb_05_ratio->SetMarkerStyle(kOpenCircle);
  jetphox_pPb_05_ratio->SetMarkerSize(1);
  jetphox_pPb_05_ratio->SetLineWidth(2);
  jetphox_pPb_05_ratio->SetLineStyle(1);
  jetphox_pPb_05_ratio->SetLineColor(kRed);
  jetphox_pPb_10_ratio->SetMarkerStyle(kFullCircle);
  jetphox_pPb_10_ratio->SetMarkerSize(1);
  jetphox_pPb_10_ratio->SetLineWidth(2);
  jetphox_pPb_10_ratio->SetLineStyle(1);
  jetphox_pPb_10_ratio->SetLineColor(kBlue);
  jetphox_pPb_20_ratio->SetMarkerStyle(kFullSquare);
  jetphox_pPb_20_ratio->SetMarkerSize(1);
  jetphox_pPb_20_ratio->SetLineWidth(2);
  jetphox_pPb_20_ratio->SetLineStyle(1);
  jetphox_pPb_20_ratio->SetLineColor(kMagenta);

  TCanvas* cRatio = new TCanvas("cRatio", "cRatio", 600, 600);
  jetphox_pPb_05_ratio->GetYaxis()->SetRangeUser(0, 2);
  jetphox_pPb_05_ratio->GetXaxis()->SetRangeUser(12, 60);
  jetphox_pPb_05_ratio->Draw("p");
  jetphox_pPb_10_ratio->Draw("p same");
  jetphox_pPb_20_ratio->Draw("p same");
  
  TLegend* legRatio = new TLegend(0.55,0.18,0.77,0.33);
  legRatio->SetBorderSize(0);
  legRatio->SetTextSize(0.035);
  legRatio->SetFillStyle(0);
  legRatio->SetMargin(0.3); 
  legRatio->AddEntry(jetphox_pPb_05_ratio, "#mu = 0.5", "p");
  legRatio->AddEntry(jetphox_pPb_10_ratio, "#mu = 1.0", "p");
  legRatio->AddEntry(jetphox_pPb_20_ratio, "#mu = 2.0", "p");
  legRatio->Draw("same");
  
  
  TLine* line1 = new TLine(12,1,60,1);
  line1->SetLineWidth(2);
  line1->SetLineStyle(7);
  line1->Draw("same");

  TLatex* tl_pQCD = new TLatex();
  tl_pQCD->SetTextAlign(11);
  tl_pQCD->SetTextSize(0.032);
  //tl_pQCD->DrawLatexNDC(0.55,0.86,"ALICE Preliminary");//.22 diff
  tl_pQCD->DrawLatexNDC(0.55,0.82,"NLO JETPHOX 1.3.14");//.22 diff
  tl_pQCD->DrawLatexNDC(0.55,0.78,"R=0.4 ISO_{chrg+neut}<2GeV");//.18
  tl_pQCD->DrawLatexNDC(0.55,0.74,"NNPDF40 for p");//.14
  tl_pQCD->DrawLatexNDC(0.55,0.70,"nNNPDF30 for Pb");
  tl_pQCD->DrawLatexNDC(0.55,0.66,"BFG set II");

  //pp
  TH1F* crossSection_pp = (TH1F*)file_5pPb->Get("crossSection_pp");
  TH1D* xsection_nlo_TOTAL_05_pp = (TH1D*)file_JETPHOX_pp->Get("xsection_nlo_TOTAL_scl_05_05_05");
  TH1D* xsection_nlo_TOTAL_10_pp = (TH1D*)file_JETPHOX_pp->Get("xsection_nlo_TOTAL_scl_10_10_10");
  TH1D* xsection_nlo_TOTAL_20_pp = (TH1D*)file_JETPHOX_pp->Get("xsection_nlo_TOTAL_scl_20_20_20");
  //xsection_nlo_TOTAL_05_pp->Scale(1.0/208.0);
  //xsection_nlo_TOTAL_10_pp->Scale(1.0/208.0);
  //xsection_nlo_TOTAL_20_pp->Scale(1.0/208.0);

  
  TH1F* jetphox_pp_05 = new TH1F("jetphox_pp_05", "", nbinscluster, clusterbins);
  TH1F* jetphox_pp_10 = new TH1F("jetphox_pp_10", "", nbinscluster, clusterbins);
  TH1F* jetphox_pp_20 = new TH1F("jetphox_pp_20", "", nbinscluster, clusterbins);
  TH1F* jetphox_pp_05_ratio = new TH1F("jetphox_pp_05_ratio", ";p_{T} [GeV/c];data/NLO JETPHOX", nbinscluster, clusterbins);
  TH1F* jetphox_pp_10_ratio = new TH1F("jetphox_pp_10_ratio", ";p_{T} [GeV/c];data/NLO JETPHOX", nbinscluster, clusterbins);
  TH1F* jetphox_pp_20_ratio = new TH1F("jetphox_pp_20_ratio", ";p_{T} [GeV/c];data/NLO JETPHOX", nbinscluster, clusterbins);
  for(int i = 1; i < jetphox_pp_05->GetNbinsX()+1; i++){
    Double_t binWidth = jetphox_pp_05->GetBinWidth(i);
    Double_t xlow = jetphox_pp_05->GetBinLowEdge(i);
    Double_t xhigh = jetphox_pp_05->GetBinLowEdge(i+1);

    Int_t xbinNumLow_05 = xsection_nlo_TOTAL_05_pp->FindBin(xlow);
    Int_t xbinNumHigh_05 = xsection_nlo_TOTAL_05_pp->FindBin(xhigh);
    Double_t xlowTheory_05 = xsection_nlo_TOTAL_05_pp->GetBinLowEdge(xbinNumLow_05);
    Double_t xhighTheory_05 = xsection_nlo_TOTAL_05_pp->GetBinLowEdge(xbinNumHigh_05);
    Double_t binIntegral_05 = xsection_nlo_TOTAL_05_pp->Integral(xbinNumLow_05, xbinNumHigh_05, "width");//*(xhighTheory_05-xlowTheory_05);
    Double_t content_05 = binIntegral_05/binWidth;

    jetphox_pp_05->SetBinContent(i, content_05);
    //cout << xlow << "\t" << xlowTheory << "\t" << xhigh << "\t" << xhighTheory << endl;
  }

  for(int i = 1; i < jetphox_pp_10->GetNbinsX()+1; i++){
    Double_t binWidth = jetphox_pp_10->GetBinWidth(i);
    Double_t xlow = jetphox_pp_10->GetBinLowEdge(i);
    Double_t xhigh = jetphox_pp_10->GetBinLowEdge(i+1);
    
    Double_t xbinNumLow_10 = xsection_nlo_TOTAL_10_pp->FindBin(xlow);
    Double_t xbinNumHigh_10 = xsection_nlo_TOTAL_10_pp->FindBin(xhigh);
    Double_t xlowTheory_10 = xsection_nlo_TOTAL_10_pp->GetBinLowEdge(xbinNumLow_10);
    Double_t xhighTheory_10 = xsection_nlo_TOTAL_10_pp->GetBinLowEdge(xbinNumHigh_10);
    Double_t binIntegral_10 = xsection_nlo_TOTAL_10_pp->Integral(xbinNumLow_10, xbinNumHigh_10, "width");
    Double_t content_10 = binIntegral_10/binWidth;
    
    jetphox_pp_10->SetBinContent(i, content_10);
    //cout << xlow << "\t" << xlowTheory << "\t" << xhigh << "\t" << xhighTheory << endl;
  }
  
  for(int i = 1; i < jetphox_pp_20->GetNbinsX()+1; i++){
    Double_t binWidth = jetphox_pp_20->GetBinWidth(i);
    Double_t xlow = jetphox_pp_20->GetBinLowEdge(i);
    Double_t xhigh = jetphox_pp_20->GetBinLowEdge(i+1);
    
    Double_t xbinNumLow_20 = xsection_nlo_TOTAL_20_pp->FindBin(xlow);
    Double_t xbinNumHigh_20 = xsection_nlo_TOTAL_20_pp->FindBin(xhigh);
    Double_t xlowTheory_20 = xsection_nlo_TOTAL_20_pp->GetBinLowEdge(xbinNumLow_20);
    Double_t xhighTheory_20 = xsection_nlo_TOTAL_20_pp->GetBinLowEdge(xbinNumHigh_20);
    Double_t binIntegral_20 = xsection_nlo_TOTAL_20_pp->Integral(xbinNumLow_20, xbinNumHigh_20, "width");
    Double_t content_20 = binIntegral_20/binWidth;
    
    jetphox_pp_20->SetBinContent(i, content_20);
    //cout << xlow << "\t" << xlowTheory_20 << "\t" << xhigh << "\t" << xhighTheory_20 << endl;
  }
  
  jetphox_pp_05->SetLineColor(kBlack);
  jetphox_pp_05->SetMarkerColor(kBlack);
  jetphox_pp_05->SetMarkerStyle(kOpenSquare);
  jetphox_pp_05->SetMarkerSize(2);
  jetphox_pp_10->SetLineColor(kBlue);
  jetphox_pp_10->SetMarkerColor(kBlue);
  jetphox_pp_10->SetMarkerStyle(kOpenTriangleUp);
  jetphox_pp_10->SetMarkerSize(3);
  jetphox_pp_20->SetLineColor(kBlue);
  jetphox_pp_20->SetMarkerColor(kBlue);
  jetphox_pp_20->SetMarkerStyle(kOpenCircle);
  jetphox_pp_20->SetMarkerSize(2);
  
  TCanvas* c1_pp = new TCanvas("c1_pp", "c1_pp");
  c1_pp->SetLogy();
  crossSection_pp->Draw("e1");
  //crossSection_pp->Draw("e1");
  xsection_nlo_TOTAL_10_pp->Draw("same e1");
  //jetphox_pp_05->Draw("same e1");
  //jetphox_pp_10->Draw("same e1");
  //jetphox_pp_20->Draw("same e1");

  TLegend* leg_pp = new TLegend(0.5, 0.65, 0.85, 0.85);
  leg_pp->AddEntry(crossSection_pp, "data");
  leg_pp->AddEntry(xsection_nlo_TOTAL_10, "xsection_nlo_TOTAL_10");
  //leg_pp->AddEntry(jetphox_pp_05, "scale = 0.5p_{T}");
  //leg_pp->AddEntry(jetphox_pp_10, "scale = 1.0p_{T}");
  //leg_pp->AddEntry(jetphox_pp_20, "scale = 2.0p_{T}");
  leg_pp->Draw("same");
  
  for(int i = 1; i < jetphox_pp_20_ratio->GetNbinsX()+1; i++){
    Double_t dataContent = crossSection_pp->GetBinContent(i);
    Double_t dataError = crossSection_pp->GetBinError(i);
    Double_t content_05 = jetphox_pp_05->GetBinContent(i);
    Double_t content_10 = jetphox_pp_10->GetBinContent(i);
    Double_t content_20 = jetphox_pp_20->GetBinContent(i);
    
    jetphox_pp_05_ratio->SetBinContent(i, dataContent/content_05);
    jetphox_pp_10_ratio->SetBinContent(i, dataContent/content_10);
    jetphox_pp_20_ratio->SetBinContent(i, dataContent/content_20);
    //jetphox_pp_05_ratio->SetBinError(i, (dataContent/content_05)*(dataError/dataContent));
    //jetphox_pp_10_ratio->SetBinError(i, (dataContent/content_10)*(dataError/dataContent));
    //jetphox_pp_20_ratio->SetBinError(i, (dataContent/content_20)*(dataError/dataContent));

    //cout << content_20 << " , ";
  }
  cout << endl;

  jetphox_pp_05_ratio->SetMarkerStyle(kOpenCircle);
  jetphox_pp_05_ratio->SetMarkerSize(1);
  jetphox_pp_05_ratio->SetLineWidth(2);
  jetphox_pp_05_ratio->SetLineStyle(1);
  jetphox_pp_05_ratio->SetLineColor(kRed);
  jetphox_pp_10_ratio->SetMarkerStyle(kFullCircle);
  jetphox_pp_10_ratio->SetMarkerSize(1);
  jetphox_pp_10_ratio->SetLineWidth(2);
  jetphox_pp_10_ratio->SetLineStyle(1);
  jetphox_pp_10_ratio->SetLineColor(kBlue);
  jetphox_pp_20_ratio->SetMarkerStyle(kFullSquare);
  jetphox_pp_20_ratio->SetMarkerSize(1);
  jetphox_pp_20_ratio->SetLineWidth(2);
  jetphox_pp_20_ratio->SetLineStyle(1);
  jetphox_pp_20_ratio->SetLineColor(kMagenta);

  TCanvas* c_ppRatio = new TCanvas("c_ppRatio", "c_ppRatio", 600, 600);
  jetphox_pp_05_ratio->GetYaxis()->SetRangeUser(0, 2);
  jetphox_pp_05_ratio->GetXaxis()->SetRangeUser(12, 60);
  jetphox_pp_05_ratio->Draw("p");
  jetphox_pp_10_ratio->Draw("p same");
  jetphox_pp_20_ratio->Draw("p same");
  
  TLegend* leg_ppRatio = new TLegend(0.55,0.18,0.77,0.33);
  leg_ppRatio->SetBorderSize(0);
  leg_ppRatio->SetTextSize(0.035);
  leg_ppRatio->SetFillStyle(0);
  leg_ppRatio->SetMargin(0.3); 
  leg_ppRatio->AddEntry(jetphox_pp_05_ratio, "#mu = 0.5", "p");
  leg_ppRatio->AddEntry(jetphox_pp_10_ratio, "#mu = 1.0", "p");
  leg_ppRatio->AddEntry(jetphox_pp_20_ratio, "#mu = 2.0", "p");
  leg_ppRatio->Draw("same");
  
  
  TLine* line1_pp = new TLine(12,1,60,1);
  line1_pp->SetLineWidth(2);
  line1_pp->SetLineStyle(7);
  line1_pp->Draw("same");

  TLatex* tl_pQCD_pp = new TLatex();
  tl_pQCD_pp->SetTextAlign(11);
  tl_pQCD_pp->SetTextSize(0.032);
  //tl_pQCD_pp->DrawLatexNDC(0.55,0.86,"ALICE Preliminary");//.22 diff
  tl_pQCD_pp->DrawLatexNDC(0.55,0.82,"NLO JETPHOX 1.3.14");//.22 diff
  tl_pQCD_pp->DrawLatexNDC(0.55,0.78,"R=0.4 ISO_{chrg+neut}<2GeV");//.18
  tl_pQCD_pp->DrawLatexNDC(0.55,0.74,"NNPDF40 for p");//.14
  tl_pQCD_pp->DrawLatexNDC(0.55,0.70,"BFG set II");//*/
  
  
}//end makeComparisons
