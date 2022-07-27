/*#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <bits/stdc++.h>
#include <cstring>//*/

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
  
  TH1D* xsection_nlo_TOTAL_05 = (TH1D*)file_JETPHOX_pPb->Get("xsection_nlo_TOTAL_scl_05_05_05");
  TH1D* xsection_nlo_TOTAL_10 = (TH1D*)file_JETPHOX_pPb->Get("xsection_nlo_TOTAL_scl_10_10_10");
  TH1D* xsection_nlo_TOTAL_20 = (TH1D*)file_JETPHOX_pPb->Get("xsection_nlo_TOTAL_scl_20_20_20");
  xsection_nlo_TOTAL_05->Scale(208.0);
  xsection_nlo_TOTAL_10->Scale(208.0);
  xsection_nlo_TOTAL_20->Scale(208.0);
  
  //5.02 TeV hists
  TFile* file_5pPb = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PurityFit_postQM_pPbAndpp.root"), "READ");
  TH1F* crossSection_pPb = (TH1F*)file_5pPb->Get("crossSection_pPb");
  
  TH1F* jetphox_pPb_05 = new TH1F("jetphox_pPb_05", "", nbinscluster, clusterbins);
  TH1F* jetphox_pPb_10 = new TH1F("jetphox_pPb_10", "", nbinscluster, clusterbins);
  TH1F* jetphox_pPb_20 = new TH1F("jetphox_pPb_20", "", nbinscluster, clusterbins);
  TH1F* jetphox_pPb_05_ratio = new TH1F("jetphox_pPb_05_ratio", ";p_{T} [GeV/c];data/NLO JETPHOX", nbinscluster, clusterbins);
  TH1F* jetphox_pPb_10_ratio = new TH1F("jetphox_pPb_10_ratio", ";p_{T} [GeV/c];data/NLO JETPHOX", nbinscluster, clusterbins);
  TH1F* jetphox_pPb_20_ratio = new TH1F("jetphox_pPb_20_ratio", ";p_{T} [GeV/c];data/NLO JETPHOX", nbinscluster, clusterbins);
  for(int i = 1; i < jetphox_pPb_05->GetNbinsX()+1; i++){
    Double_t binWidth = jetphox_pPb_05->GetBinWidth(i);
    Double_t xlow = jetphox_pPb_05->GetBinLowEdge(i);
    Double_t xhigh = jetphox_pPb_05->GetBinLowEdge(i+1);

    Int_t xbinNumLow_05 = xsection_nlo_TOTAL_05->FindBin(xlow);
    Int_t xbinNumHigh_05 = xsection_nlo_TOTAL_05->FindBin(xhigh);
    Double_t xlowTheory_05 = xsection_nlo_TOTAL_05->GetBinLowEdge(xbinNumLow_05);
    Double_t xhighTheory_05 = xsection_nlo_TOTAL_05->GetBinLowEdge(xbinNumHigh_05);
    Double_t binIntegral_05 = xsection_nlo_TOTAL_05->Integral(xbinNumLow_05, xbinNumHigh_05, "width");//*(xhighTheory_05-xlowTheory_05);
    Double_t content_05 = binIntegral_05/binWidth;

    jetphox_pPb_05->SetBinContent(i, content_05);
    //cout << xlow << "\t" << xlowTheory << "\t" << xhigh << "\t" << xhighTheory << endl;
  }

  for(int i = 1; i < jetphox_pPb_10->GetNbinsX()+1; i++){
    Double_t binWidth = jetphox_pPb_10->GetBinWidth(i);
    Double_t xlow = jetphox_pPb_10->GetBinLowEdge(i);
    Double_t xhigh = jetphox_pPb_10->GetBinLowEdge(i+1);
    
    Double_t xbinNumLow_10 = xsection_nlo_TOTAL_10->FindBin(xlow);
    Double_t xbinNumHigh_10 = xsection_nlo_TOTAL_10->FindBin(xhigh);
    Double_t xlowTheory_10 = xsection_nlo_TOTAL_10->GetBinLowEdge(xbinNumLow_10);
    Double_t xhighTheory_10 = xsection_nlo_TOTAL_10->GetBinLowEdge(xbinNumHigh_10);
    Double_t binIntegral_10 = xsection_nlo_TOTAL_10->Integral(xbinNumLow_10, xbinNumHigh_10, "width");
    Double_t content_10 = binIntegral_10/binWidth;
    
    jetphox_pPb_10->SetBinContent(i, content_10);
    //cout << xlow << "\t" << xlowTheory << "\t" << xhigh << "\t" << xhighTheory << endl;
  }
  
  for(int i = 1; i < jetphox_pPb_20->GetNbinsX()+1; i++){
    Double_t binWidth = jetphox_pPb_20->GetBinWidth(i);
    Double_t xlow = jetphox_pPb_20->GetBinLowEdge(i);
    Double_t xhigh = jetphox_pPb_20->GetBinLowEdge(i+1);
    
    Double_t xbinNumLow_20 = xsection_nlo_TOTAL_20->FindBin(xlow);
    Double_t xbinNumHigh_20 = xsection_nlo_TOTAL_20->FindBin(xhigh);
    Double_t xlowTheory_20 = xsection_nlo_TOTAL_20->GetBinLowEdge(xbinNumLow_20);
    Double_t xhighTheory_20 = xsection_nlo_TOTAL_20->GetBinLowEdge(xbinNumHigh_20);
    Double_t binIntegral_20 = xsection_nlo_TOTAL_20->Integral(xbinNumLow_20, xbinNumHigh_20, "width");
    Double_t content_20 = binIntegral_20/binWidth;
    
    jetphox_pPb_20->SetBinContent(i, content_20);
    //cout << xlow << "\t" << xlowTheory_20 << "\t" << xhigh << "\t" << xhighTheory_20 << endl;
  }
  
  jetphox_pPb_05->SetLineColor(kBlack);
  jetphox_pPb_05->SetMarkerColor(kBlack);
  jetphox_pPb_05->SetMarkerStyle(kOpenSquare);
  jetphox_pPb_05->SetMarkerSize(2);
  jetphox_pPb_10->SetLineColor(kBlue);
  jetphox_pPb_10->SetMarkerColor(kBlue);
  jetphox_pPb_10->SetMarkerStyle(kOpenTriangleUp);
  jetphox_pPb_10->SetMarkerSize(3);
  jetphox_pPb_20->SetLineColor(kBlue);
  jetphox_pPb_20->SetMarkerColor(kBlue);
  jetphox_pPb_20->SetMarkerStyle(kOpenCircle);
  jetphox_pPb_20->SetMarkerSize(2);
  
  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->SetLogy();
  crossSection_pPb->Draw("e1");
  //crossSection_pPb->Draw("e1");
  xsection_nlo_TOTAL_10->Draw("same e1");
  //jetphox_pPb_05->Draw("same e1");
  //jetphox_pPb_10->Draw("same e1");
  //jetphox_pPb_20->Draw("same e1");

  TLegend* leg = new TLegend(0.5, 0.65, 0.85, 0.85);
  leg->AddEntry(crossSection_pPb, "data");
  leg->AddEntry(xsection_nlo_TOTAL_10, "xsection_nlo_TOTAL_10");
  //leg->AddEntry(jetphox_pPb_05, "scale = 0.5p_{T}");
  //leg->AddEntry(jetphox_pPb_10, "scale = 1.0p_{T}");
  //leg->AddEntry(jetphox_pPb_20, "scale = 2.0p_{T}");
  leg->Draw("same");
  
  for(int i = 1; i < jetphox_pPb_20_ratio->GetNbinsX()+1; i++){
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
  tl_pQCD_pp->DrawLatexNDC(0.55,0.70,"BFG set II");
  
  
}//end makeComparisons
