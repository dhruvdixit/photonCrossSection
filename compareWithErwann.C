#include <fstream>
#include <vector>
#include "NLO/pQCD_iso2GeV_Werner.h"
#include "NLO/plot_style.h"

const int beamE_color[nbeamE] = {kRed, kBlue};
const int scale_lstyle[nscale] = {3, 1, 6};
const int scale_mstyle[nscale] = {24, 20, 21};

static int cno = 0;

const bool flag_use_average = true;

void set_pQCD_Werner()
{
    for (int ibeamE = 0; ibeamE < 1; ++ibeamE)
    {
        for (int iscale = 0; iscale < nscale; ++iscale)
        {
            //==========================================
            //                   pp
            //==========================================
            g_pQCD_frag_pp[ibeamE][iscale] = new TGraphErrors(npt,pQCD_pt,pQCD_frag_pp[ibeamE][iscale],0,0);
            g_pQCD_direct_pp[ibeamE][iscale] = new TGraphErrors(npt,pQCD_pt,pQCD_direct_pp[ibeamE][iscale],0,0);
            g_pQCD_sum_pp[ibeamE][iscale] = new TGraphErrors(npt,pQCD_pt,pQCD_sum_pp[ibeamE][iscale],0,0);
            g_pQCD_frag_pp[ibeamE][iscale]->SetLineWidth(2);
            g_pQCD_direct_pp[ibeamE][iscale]->SetLineWidth(2);
            g_pQCD_sum_pp[ibeamE][iscale]->SetLineWidth(2);

            //==========================================
            //                   pPb
            //==========================================
            g_pQCD_nPDF_frag_pPb[ibeamE][iscale] = new TGraphErrors(npt,pQCD_pt,pQCD_nPDF_frag_pPb[ibeamE][iscale],0,0);
            g_pQCD_nPDF_direct_pPb[ibeamE][iscale] = new TGraphErrors(npt,pQCD_pt,pQCD_nPDF_direct_pPb[ibeamE][iscale],0,0);
            g_pQCD_nPDF_sum_pPb[ibeamE][iscale] = new TGraphErrors(npt,pQCD_pt,pQCD_nPDF_sum_pPb[ibeamE][iscale],0,0);

            g_pQCD_nPDF_frag_pPb[ibeamE][iscale]->SetLineWidth(2);
            g_pQCD_nPDF_direct_pPb[ibeamE][iscale]->SetLineWidth(2);
            g_pQCD_nPDF_sum_pPb[ibeamE][iscale]->SetLineWidth(2);
        }
    }
}

void compareWithErwann(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);
  line->SetLineStyle(kDashed);

  const int numBins = 8;
  Double_t xBinCenters[numBins] = {13, 15, 17, 19, 22.5, 27.5, 35, 50};
  Double_t xErr[numBins] = {0};
  Double_t xErrSys[numBins] = {1, 1, 1, 1, 2.5, 2.5, 5, 10};
  Double_t erwannCSMean[numBins] = {2015.57, 1151.86, 696.985, 444.604, 233.026, 104.87, 38.5216, 7.4227};
  Double_t erwannCSStat[numBins] = {337.901, 71.0714, 51.475, 35.3468, 15.5412, 10.4705, 4.64552, 1.38719};
  Double_t erwannCSSys[numBins] = {308.501, 167.064, 96.1471, 58.8658, 29.4243, 12.7484, 4.7213, 1.11858};
  
  //Double_t dhruvCSMean[numBins] = {1924.31, 1286.57, 823.076, 525.652, 284.654, 128.145, 49.117, 8.77088};//without nonlin
  //Double_t dhruvCSStat[numBins] = {12.091, 11.79, 10.4942, 9.00236, 4.47992, 3.15132, 1.38649, 0.411638};//without nonlin
  Double_t dhruvCSMean[numBins] = {1945.6, 1217.8, 775.414, 489.758, 253.291, 119.494, 46.5479, 8.74711};//With nonlin
  Double_t dhruvCSStat[numBins] = {25.942, 21.281, 17.6124, 14.5384, 6.87522, 4.91365, 2.17788, 0.663041};//With nonlin
  //Double_t dhruvCSMean[numBins] = {1914.6, 1193.4, 756.802, 475.074, 250.298, 117.458, 46.9281, 8.33274};//with nonlin iso < 1.33
  //Double_t dhruvCSStat[numBins] = {33.1473, 26.0302, 20.3962, 15.7399, 7.28663, 5.1006, 2.27237, 0.665333};//with nonlin iso < 1.33
  Double_t dhruvCSSys[numBins] = {244.3, 135.641, 78.439, 47.7364, 25.2224, 11.4663, 4.48855, 0.811153};
  

  TGraphErrors* csErwannStat = new TGraphErrors(8, xBinCenters, erwannCSMean, xErr, erwannCSStat);
  TGraphErrors* csErwannSys = new TGraphErrors(8, xBinCenters, erwannCSMean, xErrSys, erwannCSSys);
  csErwannStat->SetMarkerStyle(20);
  csErwannStat->SetMarkerColor(kBlue);
  csErwannStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csErwannSys->SetLineColor(kBlue);
  csErwannSys->SetLineWidth(2);
  csErwannSys->SetFillStyle(3001);
  csErwannSys->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
    
  TGraphErrors* csDhruvStat = new TGraphErrors(8, xBinCenters, dhruvCSMean, xErr, dhruvCSStat);
  TGraphErrors* csDhruvSys = new TGraphErrors(8, xBinCenters, dhruvCSMean, xErrSys, dhruvCSSys);
  csDhruvStat->SetMarkerStyle(20);
  csDhruvStat->SetMarkerColor(kRed);
  csDhruvStat->SetLineColor(kRed);
  csDhruvStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");  
  csDhruvSys->SetLineColor(kRed);
  csDhruvSys->SetLineWidth(2);
  csDhruvSys->SetFillStyle(3001);
  csDhruvSys->GetXaxis()->SetRangeUser(12, 60);
  csDhruvSys->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");


  
  TLegend* lDhruvCSTitle = new TLegend(0.45, 0.77, 0.82, 0.88);
  lDhruvCSTitle->SetTextSize(0.035);
  lDhruvCSTitle->SetFillStyle(0);
  lDhruvCSTitle->SetMargin(0.3); 
  lDhruvCSTitle->AddEntry((TObject*)0, "ALICE Preliminary", "");
  lDhruvCSTitle->AddEntry((TObject*)0, "p-Pb #sqrt{s_{NN}} = 5.02 TeV", "");
  lDhruvCSTitle->AddEntry((TObject*)0, "#it{L}_{int} = 4.96 nb^{-1}, |#it{#eta}_{#gamma}| < 0.67", "");
  TLegend* lDhruvCS = new TLegend(0.53, 0.66, 0.82, 0.77);
  lDhruvCS->SetTextSize(0.035);
  lDhruvCS->SetFillStyle(0);
  lDhruvCS->SetMargin(0.3); 
  lDhruvCS->AddEntry(csDhruvStat, "Data and stat. unc.", "EP");
  lDhruvCS->AddEntry(csDhruvSys, "Systematic unc.", "PF");
  TCanvas* cDhruvCS = new TCanvas("cDhruvCS", "cDhruvCS", 750, 900);
  cDhruvCS->DrawFrame(12, 1, 60, 3000);
  cDhruvCS->SetLogy();
  cDhruvCS->SetLeftMargin(0.15);
  cDhruvCS->SetRightMargin(0.07);
  csDhruvSys->Draw("AE5");
  csDhruvStat->Draw("PESame");
  lDhruvCSTitle->Draw("same");
  lDhruvCS->Draw("same");
  csDhruvSys->GetYaxis()->SetTitleOffset(1.7);

  //Drawing theory predictions
  set_pQCD_Werner();
  TLegend* leg = new TLegend(0.53,0.51,0.82,0.66);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetMargin(0.3); 

  for (int ibeamE = 0; ibeamE < 1; ++ibeamE){
    for (int iscale = 0; iscale < nscale; ++iscale){
      g_pQCD_nPDF_sum_pPb[ibeamE][iscale]->SetLineStyle(scale_lstyle[iscale]);
      g_pQCD_nPDF_sum_pPb[ibeamE][iscale]->Draw("csame");
      leg->AddEntry(g_pQCD_nPDF_sum_pPb[ibeamE][iscale],Form("#mu = %.1f",scale[iscale]),"l");
    }
  }
  leg->Draw("same");
  TLatex* tl_pQCD = new TLatex();
  tl_pQCD->SetTextAlign(11);
  tl_pQCD->SetTextSize(0.032);
  tl_pQCD->DrawLatexNDC(0.19,0.27,"NLO pQCD");//.22 diff
  tl_pQCD->DrawLatexNDC(0.19,0.23,"(by W. Vogelsang)");//.18
  tl_pQCD->DrawLatexNDC(0.19,0.19,"pPb: nCTEQ & pp: CT18 PDF");//.14
  tl_pQCD->DrawLatexNDC(0.19,0.15,"GRV FF");//.1*/
  /*TFile* fout = new TFile("crossSection_pPb_FinalPlotOutput.root", "RECREATE");
  csDhruvSys->Write("csDhruvSys");
  csDhruvStat->Write("csDhruvStat");
  cDhruvCS->Write("cDhruvCS");
  fout->Close();*/

  //Drawing JETPHOX
  /*TFile* file_JETPHOX = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/JETPHOX/2022_03_24_JETPHOX_NLO_5020GeV_5Mevts_NNPDF40_0_NNPDF40_0_iso2GeVinR04.root"), "READ");
  TH1D* xsection_nlo_TOTAL_05 = (TH1D*)file_JETPHOX->Get("xsection_nlo_TOTAL_scl_05_05_05");
  TH1D* xsection_nlo_TOTAL_10 = (TH1D*)file_JETPHOX->Get("xsection_nlo_TOTAL_scl_10_10_10");
  TH1D* xsection_nlo_TOTAL_20 = (TH1D*)file_JETPHOX->Get("xsection_nlo_TOTAL_scl_20_20_20");
  xsection_nlo_TOTAL_05->Scale(208.0);
  xsection_nlo_TOTAL_10->Scale(208.0);
  xsection_nlo_TOTAL_20->Scale(208.0);
  xsection_nlo_TOTAL_05->Rebin(10);
  xsection_nlo_TOTAL_05->Scale(1.0/10.0);
  xsection_nlo_TOTAL_10->Rebin(10);
  xsection_nlo_TOTAL_10->Scale(1.0/10.0);
  xsection_nlo_TOTAL_20->Rebin(10);
  xsection_nlo_TOTAL_20->Scale(1.0/10.0);
  //xsection_nlo_TOTAL_05->SetMarkerStyle(kPlus);
  //xsection_nlo_TOTAL_10->SetMarkerStyle(kStar);
  //xsection_nlo_TOTAL_20->SetMarkerStyle(kMultiply);
  xsection_nlo_TOTAL_05->SetLineColor(kBlack);
  xsection_nlo_TOTAL_10->SetLineColor(kBlack);
  xsection_nlo_TOTAL_20->SetLineColor(kBlack);
  xsection_nlo_TOTAL_05->SetLineWidth(2);
  xsection_nlo_TOTAL_10->SetLineWidth(2);
  xsection_nlo_TOTAL_20->SetLineWidth(2);
  xsection_nlo_TOTAL_05->SetLineStyle(3);
  xsection_nlo_TOTAL_10->SetLineStyle(1);
  xsection_nlo_TOTAL_20->SetLineStyle(6);
  //xsection_nlo_TOTAL_05->SetFillColor(kMagenta);
  //xsection_nlo_TOTAL_10->SetFillColor(kOrange);
  //xsection_nlo_TOTAL_20->SetFillColor(kCyan);
  xsection_nlo_TOTAL_05->Draw("hist l same");
  xsection_nlo_TOTAL_10->Draw("hist c l same");
  xsection_nlo_TOTAL_20->Draw("hist c same");
  leg->AddEntry(xsection_nlo_TOTAL_05, "#mu = 0.5","l");
  leg->AddEntry(xsection_nlo_TOTAL_10, "#mu = 1.0","l");
  leg->AddEntry(xsection_nlo_TOTAL_20, "#mu = 2.0","l");
  leg->Draw("same");

  tl_pQCD->DrawLatexNDC(0.19,0.29,"NLO JETPHOX 1.3.14");//.22 diff
  tl_pQCD->DrawLatexNDC(0.19,0.25,"R=0.4 ISO_{chrg+neut}<2GeV");//.18
  tl_pQCD->DrawLatexNDC(0.19,0.21,"NNPDF40 for p");//.14
  tl_pQCD->DrawLatexNDC(0.19,0.17,"nNNPDF30 for Pb");
  tl_pQCD->DrawLatexNDC(0.19,0.13,"BFG set II");//*/
  
  
  Double_t jtphx_pPb_05_Mean[numBins] = {2658.95 , 1541.91 , 953.757 , 621.343 , 309.171 , 132.519 , 49.7375 , 11.4203};
  Double_t jtphx_pPb_10_Mean[numBins] = {2595.82 , 1493.53 , 920.695 , 587.754 , 287.807 , 121.858 , 45.6963 , 10.3567};
  Double_t jtphx_pPb_20_Mean[numBins] = {2563.78 , 1435.65 , 880.959 , 553.534 , 272.244 , 114.785 , 42.5438 , 9.53536};
    
  Double_t jtphx_pPb_05_ratio_Mean[numBins] = {0};
  Double_t jtphx_pPb_05_ratio_Stat[numBins] = {0};
  Double_t jtphx_pPb_05_ratio_Sys[numBins] = {0};
  Double_t jtphx_pPb_10_ratio_Mean[numBins] = {0};
  Double_t jtphx_pPb_10_ratio_Stat[numBins] = {0};
  Double_t jtphx_pPb_10_ratio_Sys[numBins] = {0};
  Double_t jtphx_pPb_20_ratio_Mean[numBins] = {0};
  Double_t jtphx_pPb_20_ratio_Stat[numBins] = {0};
  Double_t jtphx_pPb_20_ratio_Sys[numBins] = {0};
  for(int i = 0; i < numBins; i++){
    Double_t contentRatio_05_Mean = dhruvCSMean[i]/jtphx_pPb_05_Mean[i];
    Double_t contentRatio_05_Stat = contentRatio_05_Mean*dhruvCSStat[i]/dhruvCSMean[i];
    Double_t contentRatio_05_Sys = contentRatio_05_Mean*dhruvCSSys[i]/dhruvCSMean[i];
    jtphx_pPb_05_ratio_Mean[i] = contentRatio_05_Mean;
    jtphx_pPb_05_ratio_Stat[i] = contentRatio_05_Stat;
    jtphx_pPb_05_ratio_Sys[i] = contentRatio_05_Sys;
	
    Double_t contentRatio_10_Mean = dhruvCSMean[i]/jtphx_pPb_10_Mean[i];
    Double_t contentRatio_10_Stat = contentRatio_10_Mean*dhruvCSStat[i]/dhruvCSMean[i];
    Double_t contentRatio_10_Sys = contentRatio_10_Mean*dhruvCSSys[i]/dhruvCSMean[i];
    jtphx_pPb_10_ratio_Mean[i] = contentRatio_10_Mean;
    jtphx_pPb_10_ratio_Stat[i] = contentRatio_10_Stat;
    jtphx_pPb_10_ratio_Sys[i] = contentRatio_10_Sys;

    Double_t contentRatio_20_Mean = dhruvCSMean[i]/jtphx_pPb_20_Mean[i];
    Double_t contentRatio_20_Stat = contentRatio_20_Mean*dhruvCSStat[i]/dhruvCSMean[i];
    Double_t contentRatio_20_Sys = contentRatio_20_Mean*dhruvCSSys[i]/dhruvCSMean[i];
    jtphx_pPb_20_ratio_Mean[i] = contentRatio_20_Mean;
    jtphx_pPb_20_ratio_Stat[i] = contentRatio_20_Stat;
    jtphx_pPb_20_ratio_Sys[i] = contentRatio_20_Sys;

  }
  
  TGraphErrors* jetphox_pPb_05_ratioStat = new TGraphErrors(8, xBinCenters,  jtphx_pPb_05_ratio_Mean, xErr, jtphx_pPb_05_ratio_Stat);
  TGraphErrors* jetphox_pPb_05_ratioSys = new TGraphErrors(8, xBinCenters,  jtphx_pPb_05_ratio_Mean, xErrSys, jtphx_pPb_05_ratio_Sys);
  jetphox_pPb_05_ratioStat->SetMarkerStyle(20);
  jetphox_pPb_05_ratioStat->SetMarkerColor(kBlack);
  jetphox_pPb_05_ratioStat->SetLineColor(kBlack);
  jetphox_pPb_05_ratioStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");  
  jetphox_pPb_05_ratioSys->SetLineColor(kBlack);
  jetphox_pPb_05_ratioSys->SetLineWidth(2);
  jetphox_pPb_05_ratioSys->SetFillStyle(3001);
  jetphox_pPb_05_ratioSys->GetXaxis()->SetRangeUser(12, 60);
  jetphox_pPb_05_ratioSys->SetTitle("#mu = 0.5;E_{T} [GeV]; data/NLO JETPHOX");
  TCanvas* cjetphoxpPb05Ratio = new TCanvas("cjetphoxpPb05Ratio",  "cjetphoxpPb05Ratio", 1500, 900);
  cjetphoxpPb05Ratio->Divide(3, 1);
  cjetphoxpPb05Ratio->cd(1);
  cjetphoxpPb05Ratio->DrawFrame(12, 1, 60, 3000);
  cjetphoxpPb05Ratio->SetLeftMargin(0.15);
  cjetphoxpPb05Ratio->SetRightMargin(0.07);
  jetphox_pPb_05_ratioSys->GetYaxis()->SetRangeUser(0, 2);
  jetphox_pPb_05_ratioSys->Draw("AE5");
  jetphox_pPb_05_ratioStat->Draw("PEsame");
  line->Draw("same");

  TGraphErrors* jetphox_pPb_10_ratioStat = new TGraphErrors(8, xBinCenters,  jtphx_pPb_10_ratio_Mean, xErr, jtphx_pPb_10_ratio_Stat);
  TGraphErrors* jetphox_pPb_10_ratioSys = new TGraphErrors(8, xBinCenters,  jtphx_pPb_10_ratio_Mean, xErrSys, jtphx_pPb_10_ratio_Sys);
  jetphox_pPb_10_ratioStat->SetMarkerStyle(20);
  jetphox_pPb_10_ratioStat->SetMarkerColor(kBlack);
  jetphox_pPb_10_ratioStat->SetLineColor(kBlack);
  jetphox_pPb_10_ratioStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");  
  jetphox_pPb_10_ratioSys->SetLineColor(kBlack);
  jetphox_pPb_10_ratioSys->SetLineWidth(2);
  jetphox_pPb_10_ratioSys->SetFillStyle(3001);
  jetphox_pPb_10_ratioSys->GetXaxis()->SetRangeUser(12, 60);
  jetphox_pPb_10_ratioSys->SetTitle("#mu = 1.0;E_{T} [GeV]; data/NLO JETPHOX");
  //TCanvas* cjetphoxpPb10Ratio = new TCanvas("cjetphoxpPb10Ratio",  "cjetphoxpPb10Ratio", 750, 900);
  cjetphoxpPb05Ratio->cd(2);
  cjetphoxpPb05Ratio->DrawFrame(12, 1, 60, 3000);
  //cjetphoxpPb05Ratio->SetLeftMargin(0.15);
  cjetphoxpPb05Ratio->SetRightMargin(0.07);
  jetphox_pPb_10_ratioSys->GetYaxis()->SetRangeUser(0, 2);
  jetphox_pPb_10_ratioSys->Draw("AE5");
  jetphox_pPb_10_ratioStat->Draw("PEsame");
  line->Draw("same");

   TGraphErrors* jetphox_pPb_20_ratioStat = new TGraphErrors(8, xBinCenters,  jtphx_pPb_20_ratio_Mean, xErr, jtphx_pPb_20_ratio_Stat);
  TGraphErrors* jetphox_pPb_20_ratioSys = new TGraphErrors(8, xBinCenters,  jtphx_pPb_20_ratio_Mean, xErrSys, jtphx_pPb_20_ratio_Sys);
  jetphox_pPb_20_ratioStat->SetMarkerStyle(20);
  jetphox_pPb_20_ratioStat->SetMarkerColor(kBlack);
  jetphox_pPb_20_ratioStat->SetLineColor(kBlack);
  jetphox_pPb_20_ratioStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");  
  jetphox_pPb_20_ratioSys->SetLineColor(kBlack);
  jetphox_pPb_20_ratioSys->SetLineWidth(2);
  jetphox_pPb_20_ratioSys->SetFillStyle(3001);
  jetphox_pPb_20_ratioSys->GetXaxis()->SetRangeUser(12, 60);
  jetphox_pPb_20_ratioSys->SetTitle("#mu = 2.0;E_{T} [GeV]; data/NLO JETPHOX");
  //TCanvas* cjetphoxpPb20Ratio = new TCanvas("cjetphoxpPb20Ratio",  "cjetphoxpPb20Ratio", 750, 900);
  cjetphoxpPb05Ratio->cd(3);
  cjetphoxpPb05Ratio->DrawFrame(12, 1, 60, 3000);
  //cjetphoxpPb05Ratio->SetLeftMargin(0.15);
  cjetphoxpPb05Ratio->SetRightMargin(0.07);
  jetphox_pPb_20_ratioSys->GetYaxis()->SetRangeUser(0, 2);
  jetphox_pPb_20_ratioSys->Draw("AE5");
  jetphox_pPb_20_ratioStat->Draw("PEsame");
  line->Draw("same");

  
  //Compare with Erwann
  /*TLegend* lCs = new TLegend(0.35, 0.7, 0.77, 0.87);
  lCs->SetTextSize(0.035);
  lCs->SetFillStyle(0);
  lCs->SetMargin(0.3); 
  lCs->AddEntry(csErwannStat, "Erwann's cross-section results", "EP");
  lCs->AddEntry(csErwannSys, "Sys unc on Erwann;'s results", "PF");
  lCs->AddEntry(csDhruvStat, "Dhruv's cross-section results", "EP");
  lCs->AddEntry(csDhruvSys, "Sys unc on Dhruv's results", "PF");
  TCanvas* c1 = new TCanvas("c1", "c1", 750, 900);
  c1->DrawFrame(12, 1, 60, 3000);
  c1->SetLogy();
  c1->SetLeftMargin(0.15);
  c1->SetRightMargin(0.07);
  csDhruvSys->Draw("AE5");
  csErwannSys->Draw("E5 same");
  //csDhruvSys->Draw("E3 same");
  csErwannStat->Draw("PESame");
  csDhruvStat->Draw("PESame");
  lCs->Draw("same");
  csDhruvSys->GetYaxis()->SetTitleOffset(1.7);
    
  Double_t ratioCSMean[numBins] = {0};
  Double_t ratioCSStat[numBins] = {0};
  Double_t ratioCSSys[numBins] = {0};
  for(int i = 0; i < numBins; i++){
    ratioCSMean[i] = erwannCSMean[i]/dhruvCSMean[i];
    //ratioCSStat[i] = ratioCSMean[i]*(erwannCSStat[i]/erwannCSMean[i]);//
    ratioCSStat[i] = ratioCSMean[i]*TMath::Sqrt(TMath::Power(erwannCSStat[i]/erwannCSMean[i], 2) + TMath::Power(dhruvCSStat[i]/dhruvCSMean[i], 2));
    ratioCSSys[i] = ratioCSMean[i]*TMath::Sqrt(TMath::Power(erwannCSSys[i]/erwannCSMean[i], 2) + TMath::Power(dhruvCSSys[i]/dhruvCSMean[i], 2));
  }

  TGraphErrors* csRatioStat = new TGraphErrors(8, xBinCenters, ratioCSMean, xErr, ratioCSStat);
  TGraphErrors* csRatioSys = new TGraphErrors(8, xBinCenters, ratioCSMean, xErrSys, ratioCSSys);
  csRatioStat->SetTitle(";E_{T} [GeV];#frac{cross section_{Erwann}}{cross section_{dhruv}}");
  csRatioSys->SetTitle(";E_{T} [GeV];#frac{cross section_{Erwann}}{cross section_{dhruv}}");
  csRatioStat->GetXaxis()->SetRangeUser(12,60);
  csRatioSys->GetXaxis()->SetRangeUser(12,60);
  csRatioStat->GetYaxis()->SetRangeUser(0,2);
  csRatioSys->GetYaxis()->SetRangeUser(0,2);
  csRatioStat->SetMarkerStyle(20);
  csRatioStat->SetMarkerColor(kBlack);
  //csRatioSys->SetFillColor(kBlack);
  csRatioSys->SetFillStyle(3001);
  TCanvas* c2 = new TCanvas("c2", "c2", 750, 900);
  c2->DrawFrame(12, 0, 60, 2);
  c2->SetLeftMargin(0.15);
  c2->SetRightMargin(0.07);
  csRatioSys->Draw("AE5");
  csRatioStat->Draw("PESame");
  line->Draw("Same");

  //Efficiency comparison
  /*Double_t erwannEffMean[numBins] = {0.588658, 0.588779, 0.592832, 0.603951, 0.615985, 0.634618, 0.64918, 0.668659};
  Double_t erwannEffStat[numBins] = {0.000818115, 0.00086052, 0.000887487, 0.000912674, 0.000614389, 0.000638404, 0.000507488, 0.00038763};
  Double_t erwannEffSys[numBins] = {0.0950227, 0.0471217, 0.0383073, 0.0370981, 0.0328842, 0.027495, 0.0276957, 0.023399};
  Double_t dhruvEffMean[numBins] = {0.593997, 0.595344, 0.603961, 0.610833, 0.622483, 0.628033, 0.645673, 0.655699};
  Double_t dhruvEffStat[numBins] = {0.00711286, 0.00769254, 0.00820661, 0.00807768, 0.00553489, 0.00586276, 0.00483549, 0.00399029};
  Double_t dhruvEffSys[numBins] = {0};

  TGraphErrors* effErwannStat = new TGraphErrors(8, xBinCenters, erwannEffMean, xErr, erwannEffStat);
  TGraphErrors* effErwannSys = new TGraphErrors(8, xBinCenters, erwannEffMean, xErr, erwannEffSys);
  TGraphErrors* effDhruvStat = new TGraphErrors(8, xBinCenters, dhruvEffMean, xErr, dhruvEffStat);
  TGraphErrors* effDhruvSys = new TGraphErrors(8, xBinCenters, dhruvEffMean, xErr, dhruvEffSys);

  effErwannStat->SetMarkerStyle(20); effErwannStat->SetMarkerColor(kBlack);
  effErwannSys->SetFillColor(kBlack); effErwannSys->SetFillStyle(3004);
  effDhruvStat->SetMarkerStyle(20); effDhruvStat->SetMarkerColor(kRed); effDhruvStat->SetLineColor(kRed);
  effDhruvSys->SetFillColor(kOrange);
  effDhruvStat->SetTitle(";E_{T} [GeV];#epsilon_{#gamma}^{iso}");
  effErwannStat->SetTitle(";E_{T} [GeV];#epsilon_{#gamma}^{iso}");
  effDhruvSys->SetTitle(";E_{T} [GeV];#epsilon_{#gamma}^{iso}");
  effErwannSys->SetTitle(";E_{T} [GeV];#epsilon_{#gamma}^{iso}");

  TLegend* lEff = new TLegend(0.15, 0.1, 0.6, 0.4);
  lEff->AddEntry(effErwannStat, "Erwann efficiency results", "PF");
  lEff->AddEntry(effErwannSys, "Sys Err on Erwann efficiency results", "PF");
  lEff->AddEntry(effDhruvStat, "Dhruv's efficiency results", "PF");
  //lEff->AddEntry(effDhruvSys, "Sys Err on Dhruv's efficiency results", "PF");
  TCanvas* cEff = new TCanvas("cEff", "cEff");
  cEff->DrawFrame(12, 0, 60, 2);
  effErwannSys->GetYaxis()->SetRangeUser(0,1);
  effErwannSys->Draw("E3AL");
  //effDhruvSys->Draw("E3 same");
  effErwannStat->Draw("PESame");
  effDhruvStat->Draw("PELSame");
  lEff->Draw("same");
  
  Double_t ratioEffMean[numBins] = {0};
  Double_t ratioEffStat[numBins] = {0};
  Double_t ratioEffSys[numBins] = {0};
  for(int i = 0; i < numBins; i++){
    ratioEffMean[i] = erwannEffMean[i]/dhruvEffMean[i];
    ratioEffStat[i] = ratioEffMean[i]*(erwannEffStat[i]/erwannEffMean[i]);//ratioEffMean[i]*TMath::Sqrt(TMath::Power(erwannEffStat[i]/erwannEffMean[i], 2) + TMath::Power(dhruvStat[i]/dhruvEffMean[i], 2));
    ratioEffSys[i] = ratioEffMean[i]*(erwannEffSys[i]/erwannEffMean[i]);//ratioEffMean[i]*TMath::Sqrt(TMath::Power(erwannEffSys[i]/erwannEffMean[i], 2) + TMath::Power(dhruvEffSys[i]/dhruvEffMean[i], 2));
  }

  TGraphErrors* effRatioStat = new TGraphErrors(8, xBinCenters, ratioEffMean, xErr, ratioEffStat);
  TGraphErrors* effRatioSys = new TGraphErrors(8, xBinCenters, ratioEffMean, xErr, ratioEffSys);
  effRatioStat->SetTitle(";E_{T} [GeV];#frac{eff_{Erwann}}{eff_{dhruv}}");
  effRatioSys->SetTitle(";E_{T} [GeV];#frac{eff_{Erwann}}{eff_{dhruv}}");
  effRatioStat->GetXaxis()->SetRangeUser(12,60);
  effRatioSys->GetXaxis()->SetRangeUser(12,60);
  effRatioStat->GetYaxis()->SetRangeUser(0,2);
  effRatioSys->GetYaxis()->SetRangeUser(0,2);
  effRatioStat->SetMarkerStyle(20); effRatioStat->SetMarkerColor(kBlack);
  effRatioSys->SetFillColor(kBlack); effRatioSys->SetFillStyle(3004);
  TCanvas* cEffRatio = new TCanvas("cEffRatio", "cEffRatio");
  cEffRatio->DrawFrame(12, 0, 60, 2);
  effRatioSys->Draw("E3AL");
  effRatioStat->Draw("PESame");
  line->Draw("Same");//*/

  //Purity
  /*Double_t erwannPrtyMean[numBins] = {0.330486, 0.427572, 0.502339, 0.590244, 0.627706, 0.653977, 0.65251, 0.673619};
  Double_t erwannPrtyStat[numBins] = {0.0308763, 0.0130233, 0.0171051, 0.018815, 0.016112, 0.0255705, 0.0324564, 0.0514761};
  Double_t erwannPrtySys[numBins] = {0.0389282, 0.0620852, 0.0736194, 0.0793521, 0.079274, 0.0984856, 0.0948469, 0.0736746};
  Double_t purity_pPb[5] = {0.207, 0.342, 0.476, 0.546, 0.546};
  Double_t statErr_pPb[5] = {0.011, 0.012, 0.017, 0.018, 0.018};
  Double_t systErr_pPb[5] = {0.020, 0.028, 0.027, 0.039, 0.039};
  Double_t xBinPurity[5] = {13.198656, 16.903571, 22.064577, 30.107411, 45.0};
  Double_t xBinLeftErr[5] = {1.1986559999999997, 1.9035709999999995, 2.064577, 
5.107410999999999, 5.0};
  Double_t xBinRightErr[5] = {1.8013440000000003, 3.0964290000000005, 2.935423,
 9.892589000000001, 10.0};

  TGraphErrors* prtyErwannStat = new TGraphErrors(8, xBinCenters, erwannPrtyMean, xErr, erwannPrtyStat);
  TGraphErrors* prtyErwannSys = new TGraphErrors(8, xBinCenters, erwannPrtyMean, xErr, erwannPrtySys);
  auto prtyDhruvStat = new TGraphAsymmErrors(5, xBinPurity, purity_pPb, xBinLeftErr, xBinRightErr, statErr_pPb, statErr_pPb);
  auto prtyDhruvSys = new TGraphAsymmErrors(5, xBinPurity, purity_pPb, xBinLeftErr, xBinRightErr, systErr_pPb, systErr_pPb);

  prtyErwannStat->SetMarkerStyle(20); prtyErwannStat->SetMarkerColor(kBlack);
  prtyErwannSys->SetFillColor(kBlack); prtyErwannSys->SetFillStyle(3004);
  prtyDhruvStat->SetMarkerStyle(20); prtyDhruvStat->SetMarkerColor(kRed); prtyDhruvStat->SetLineColor(kRed);
  prtyDhruvSys->SetFillColor(kOrange);
  prtyDhruvStat->SetTitle(";E_{T} [GeV];purity");
  prtyErwannStat->SetTitle(";E_{T} [GeV];purity");
  prtyDhruvSys->SetTitle(";E_{T} [GeV];purity");
  prtyErwannSys->SetTitle(";E_{T} [GeV];purity");

  TLegend* lPrty = new TLegend(0.15, 0.1, 0.6, 0.4);
  lPrty->AddEntry(prtyErwannStat, "ABCD method", "PF");
  lPrty->AddEntry(prtyErwannSys, "Sys Err on ABCD method", "PF");
  lPrty->AddEntry(prtyDhruvStat, "Template fit method", "PF");
  lPrty->AddEntry(prtyDhruvSys, "Sys Err on template fit", "PF");
  TCanvas* cPrty = new TCanvas("cPrty", "cPrty");
  cPrty->DrawFrame(12, 0, 60, 2);
  prtyErwannSys->GetYaxis()->SetRangeUser(0,1);
  prtyErwannSys->Draw("E3AL");
  prtyDhruvSys->Draw("E3 same");
  prtyErwannStat->Draw("PESame");
  prtyDhruvStat->Draw("PELSame");
  lPrty->Draw("same");//*/

}//end makeComparisons
