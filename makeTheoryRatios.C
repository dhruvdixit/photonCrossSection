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
  for(int i = 0; i < npt; i++){
    pQCD_xErr[i] = 0.5;
  }

  double pQCD_nPDF_sum_pPb_ScaleDiffHigh[nbeamE][npt] = {0};
  double pQCD_nPDF_sum_pPb_ScaleDiffLow[nbeamE][npt] = {0};
  for (int ibeamE = 0; ibeamE < 1; ++ibeamE){
    for (int iscale = 0; iscale < nscale; ++iscale){
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
      g_pQCD_nPDF_sum_pPb[ibeamE][iscale] = new TGraphErrors(npt,pQCD_pt,pQCD_nPDF_sum_pPb[ibeamE][iscale],pQCD_xErr,0);
      g_pQCD_nPDF_frag_pPb[ibeamE][iscale]->SetLineWidth(2);
      g_pQCD_nPDF_direct_pPb[ibeamE][iscale]->SetLineWidth(2);
      g_pQCD_nPDF_sum_pPb[ibeamE][iscale]->SetLineWidth(2);
    }
    for(int ipt = 0; ipt < npt; ipt++){
      double contentScale[nscale] = {0};
      for (int iscale = 0; iscale < nscale; ++iscale){
	contentScale[iscale] = pQCD_nPDF_sum_pPb[ibeamE][iscale][ipt];
      }//end iscale
      pQCD_nPDF_sum_pPb_ScaleDiffHigh[ibeamE][ipt] = TMath::Abs(contentScale[0] - contentScale[1]);
      pQCD_nPDF_sum_pPb_ScaleDiffLow[ibeamE][ipt] = TMath::Abs(contentScale[1] - contentScale[2]);
    }//end ipt
    g_pQCD_nPDF_sum_pPb_Scale[ibeamE] = new TGraphAsymmErrors(npt, pQCD_pt, pQCD_nPDF_sum_pPb[ibeamE][1] , pQCD_xErr, pQCD_xErr, pQCD_nPDF_sum_pPb_ScaleDiffLow[ibeamE], pQCD_nPDF_sum_pPb_ScaleDiffHigh[ibeamE]);
  }//end ibeam

}

void makeTheoryRatios(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);  
  
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);
  line->SetLineStyle(kDashed);

  const int numBins = 8;
  Double_t xBinCenters[numBins] = {13, 15, 17, 19, 22.5, 27.5, 35, 50};
  Double_t xErr[numBins] = {0};
  Double_t xOnes[numBins] = {  1, 1, 1, 1, 1,   1,   1, 1};
  Double_t xErrSys[numBins] = {1, 1, 1, 1, 2.5, 2.5, 5, 10};

  //Double_t dhruvCSMean_pPb[numBins] = {1945.6, 1217.8, 775.414, 489.758, 253.291, 119.494, 46.5479, 8.74711};//With nonlin
  //Double_t dhruvCSStat_pPb[numBins] = {25.942, 21.281, 17.6124, 14.5384, 6.87522, 4.91365, 2.17788, 0.663041};//With nonlin
  //Double_t dhruvCSMean_pPb[numBins] = {1796.23, 1128.1, 705.132, 446.36, 238.349, 112.394, 43.5192, 7.89217};//With latest EMCal corr
  //Double_t dhruvCSStat_pPb[numBins] = {23.9179, 19.6117, 16.1032, 13.2724, 6.37573, 4.55258, 2.0155, 0.602057};//With latest EMCal corr
  Double_t dhruvCSMean_pPb[numBins] = {1855.69, 1162.59, 730.899, 460.33, 245.395, 115.95, 44.6992, 8.06541};//With latest EMCal corr and eta correction
  Double_t dhruvCSStat_pPb[numBins] = {24.7755, 20.2713, 16.6766, 13.7369, 6.59183, 4.7181, 2.07481, 0.61793};//With latest EMCal corr and eta correction
  Double_t dhruvCSSys_pPb[numBins] = {244.3, 135.641, 78.439, 47.7364, 25.2224, 11.4663, 4.48855, 0.811153};
  Double_t dhruvCSMean_pp[numBins] = {};//With latest EMCal corr
  Double_t dhruvCSStat_pp[numBins] = {0.42378, 0.255627, 0.192896, 0.108714, 0.0489118, 0.032834, 0.013023, 0.00392297};//With latest EMCal corr
  Double_t dhruvCSSys_pp[numBins] = {244.3, 135.641, 78.439, 47.7364, 25.2224, 11.4663, 4.48855, 0.811153};
  

  TGraphErrors* csDhruvStat_pPb = new TGraphErrors(8, xBinCenters, dhruvCSMean_pPb, xErr, dhruvCSStat_pPb);
  TGraphErrors* csDhruvSys_pPb = new TGraphErrors(8, xBinCenters, dhruvCSMean_pPb, xErrSys, dhruvCSSys_pPb);
  csDhruvStat_pPb->SetMarkerStyle(20);
  csDhruvStat_pPb->SetMarkerColor(kBlack);
  csDhruvStat_pPb->SetLineColor(kBlack);
  csDhruvStat_pPb->SetFillStyle(3001);
  csDhruvStat_pPb->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");  
  csDhruvSys_pPb->SetLineColor(kBlack);
  csDhruvSys_pPb->SetLineWidth(2);
  csDhruvSys_pPb->SetFillStyle(3001);
  csDhruvSys_pPb->GetXaxis()->SetRangeUser(12, 60);
  csDhruvSys_pPb->GetYaxis()->SetRangeUser(6, 3e3);
  csDhruvSys_pPb->SetTitle(";#it{p}_{T}^{#gamma} [GeV/#it{c}]; d^{2}#sigma/d#it{p}_{T}^{#gamma}d#eta [nb #it{c}/GeV]");


  
  /*TLegend* lDhruvCSTitle = new TLegend(0.45, 0.77, 0.82, 0.88);
  lDhruvCSTitle->SetTextSize(0.035);
  lDhruvCSTitle->SetFillStyle(0);
  lDhruvCSTitle->SetMargin(0.3); 
  lDhruvCSTitle->AddEntry((TObject*)0, "ALICE Preliminary", "");
  lDhruvCSTitle->AddEntry((TObject*)0, "p-Pb #sqrt{s_{NN}} = 5.02 TeV", "");
  lDhruvCSTitle->AddEntry((TObject*)0, "#it{L}_{int} = 4.96 nb^{-1}, |#it{#eta}_{#gamma}| < 0.67", "");//*/
  TCanvas* cDhruvCS = new TCanvas("cDhruvCS", "cDhruvCS", 900, 750);
  //cDhruvCS->DrawFrame(12, 1, 60, 3000);
  cDhruvCS->SetLogy();
  cDhruvCS->SetLeftMargin(0.15);
  cDhruvCS->SetRightMargin(0.07);
  csDhruvSys_pPb->Draw("AE5");
  csDhruvStat_pPb->Draw("PESame");
  //lDhruvCSTitle->Draw("same");
  csDhruvSys_pPb->GetYaxis()->SetTitleOffset(1.7);
  TLatex* tl_data = new TLatex();
  tl_data->SetTextAlign(11);
  tl_data->SetTextSize(0.035);
  tl_data->DrawLatexNDC(0.55,0.83,"#bf{#scale[1.2]{ALICE Preliminary}}");
  tl_data->DrawLatexNDC(0.55,0.79,"#bf{p-Pb #sqrt{s} = 5.02 TeV}");
  //tl_data->DrawLatexNDC(0.55,0.75,"#bf{#it{L}_{int} = 4.96 nb^{-1}}");//for QM prelim results
  tl_data->DrawLatexNDC(0.55,0.75,"#bf{#it{L}_{int} = 5.47 nb^{-1}}");
  tl_data->DrawLatexNDC(0.55,0.71,"#bf{|#it{#eta}_{#gamma}| < 0.67}");
  tl_data->DrawLatexNDC(0.55,0.67,"#bf{#it{R} = 0.4, #it{p}_{T}^{iso,ch} < 1.5 GeV/#it{c}}");
  TLegend* lDhruvCS = new TLegend(0.54, 0.57, 0.7, 0.66);
  lDhruvCS->SetTextSize(0.035);
  lDhruvCS->SetFillStyle(0);
  lDhruvCS->SetMargin(0.3); 
  lDhruvCS->AddEntry(csDhruvStat_pPb, "Data and stat. unc.", "EP");
  lDhruvCS->AddEntry(csDhruvSys_pPb, "Systematic unc.", "PF");
  lDhruvCS->Draw("same");
  //cDhruvCS->Print("QM2022_figures/pPbData_crossSection.pdf");
    
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
      //g_pQCD_nPDF_sum_pPb[ibeamE][iscale]->Draw("csame");
      //leg->AddEntry(g_pQCD_nPDF_sum_pPb[ibeamE][iscale],Form("#mu = %.1f",scale[iscale]),"l");
    }
  }
  //leg->Draw("same");
  //tl_pQCD->DrawLatexNDC(0.19,0.27,"NLO pQCD");//.22 diff
  //tl_pQCD->DrawLatexNDC(0.19,0.23,"(by W. Vogelsang)");//.18
  //tl_pQCD->DrawLatexNDC(0.19,0.19,"pPb: nCTEQ15 & pp: CT18 PDF");//.14
  //tl_pQCD->DrawLatexNDC(0.19,0.15,"GRV FF");//.1*/
  /*TFile* fout = new TFile("crossSection_pPb_FinalPlotOutput.root", "RECREATE");
  csDhruvSys_pPb->Write("csDhruvSys_pPb");
  csDhruvStat_pPb->Write("csDhruvStat_pPb");
  cDhruvCS->Write("cDhruvCS");
  fout->Close();*/

  //Drawing JETPHOX
  /*const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14
  TFile* file_JETPHOX = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/JETPHOX/2022_03_24_JETPHOX_NLO_5020GeV_5Mevts_NNPDF40_0_nNNPDF30_0_iso2GeVinR04.root"), "READ");
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
  //xsection_nlo_TOTAL_20->SetMarkerStyle(kMultiply);//
  xsection_nlo_TOTAL_05->SetLineColor(kBlack);
  xsection_nlo_TOTAL_10->SetLineColor(kBlack);
  xsection_nlo_TOTAL_20->SetLineColor(kBlack);
  xsection_nlo_TOTAL_05->SetLineWidth(2);
  xsection_nlo_TOTAL_10->SetLineWidth(2);
  xsection_nlo_TOTAL_20->SetLineWidth(2);
  xsection_nlo_TOTAL_05->SetLineStyle(3);
  xsection_nlo_TOTAL_10->SetLineStyle(1);
  xsection_nlo_TOTAL_20->SetLineStyle(6);
  TH1F* jetphox_pPb_05 = new TH1F("jetphox_pPb_05", "", nbinscluster, clusterbins);
  TH1F* jetphox_pPb_10 = new TH1F("jetphox_pPb_10", "", nbinscluster, clusterbins);
  TH1F* jetphox_pPb_20 = new TH1F("jetphox_pPb_20", "", nbinscluster, clusterbins);//*/

  
  Double_t jtphx_pPb_05_Mean[numBins] = {2658.95 , 1541.91 , 953.757 , 621.343 , 309.171 , 132.519 , 49.7375 , 11.4203};
  Double_t jtphx_pPb_10_Mean[numBins] = {2595.82 , 1493.53 , 920.695 , 587.754 , 287.807 , 121.858 , 45.6963 , 10.3567};
  Double_t jtphx_pPb_20_Mean[numBins] = {2563.78 , 1435.65 , 880.959 , 553.534 , 272.244 , 114.785 , 42.5438 , 9.53536};
  Double_t isoEff[numBins] = {0.896561, 0.893282, 0.893309, 0.895817, 0.893182, 0.891356, 0.888251, 0.888483};
  Double_t isoEffErr[numBins] = {0.00433508, 0.0044735, 0.00478074, 0.00521943, 0.00373858, 0.00411032, 0.00317399, 0.00225039};
  //Double_t jtphx_pPb_10_MeanIsoEff[numBins] = {0}
  Double_t jtphx_pPb_05_Error[numBins] = {0};
  Double_t jtphx_pPb_20_Error[numBins] = {0};
  for(int i = 0; i < numBins; i++){
    Double_t content05 = jtphx_pPb_05_Mean[i]*isoEff[i];
    Double_t content10 = jtphx_pPb_10_Mean[i]*isoEff[i];
    Double_t content20 = jtphx_pPb_20_Mean[i]*isoEff[i];
    jtphx_pPb_05_Mean[i] = content05;
    jtphx_pPb_10_Mean[i] = content10;
    jtphx_pPb_20_Mean[i] = content20;
    jtphx_pPb_05_Error[i] = jtphx_pPb_05_Mean[i] - jtphx_pPb_10_Mean[i];
    jtphx_pPb_20_Error[i] = jtphx_pPb_10_Mean[i] - jtphx_pPb_20_Mean[i];
  }
  TGraphAsymmErrors* jetphox_pPb_10_ScaleSys = new TGraphAsymmErrors(8, xBinCenters,jtphx_pPb_10_Mean , xErrSys, xErrSys, jtphx_pPb_20_Error, jtphx_pPb_05_Error);
  jetphox_pPb_10_ScaleSys->SetLineColor(kGreen+1);
  jetphox_pPb_10_ScaleSys->SetLineWidth(0);
  jetphox_pPb_10_ScaleSys->SetFillColorAlpha(kGreen+1,0.7);
  //jetphox_pPb_10_ScaleSys->SetFillStyle(3001);
  g_pQCD_nPDF_sum_pPb_Scale[0]->SetLineColor(kAzure);
  g_pQCD_nPDF_sum_pPb_Scale[0]->SetLineWidth(0);
  g_pQCD_nPDF_sum_pPb_Scale[0]->SetFillColorAlpha(kAzure-2, 0.7);
  //g_pQCD_nPDF_sum_pPb_Scale[0]->SetFillStyle(3001);
  g_pQCD_nPDF_sum_pPb[0][1]->SetLineColor(kAzure-2);
  TCanvas* cJetphoxCompare = new TCanvas("cJetphoxCompare", "cJetphoxCompare", 1200, 1000);
  //cJetphoxCompare->DrawFrame(12, 1, 60, 3000);
  cJetphoxCompare->SetLogy();
  cJetphoxCompare->SetLeftMargin(0.15);
  cJetphoxCompare->SetRightMargin(0.07);
  csDhruvSys_pPb->Draw("A E5");
  csDhruvStat_pPb->Draw("P E same");
  //csDhruvStat_pPb->Draw("A E5");
  jetphox_pPb_10_ScaleSys->Draw("E2 same");
  g_pQCD_nPDF_sum_pPb[0][1]->Draw("CPZ same");
  g_pQCD_nPDF_sum_pPb_Scale[0]->Draw("E2 same");
  csDhruvSys_pPb->GetYaxis()->SetTitleOffset(1.7);

  TLatex* tl_data2 = new TLatex();
  tl_data2->SetTextAlign(11);
  tl_data2->SetTextSize(0.032);
  tl_data2->DrawLatexNDC(0.55,0.83,"#bf{#scale[1.2]{ALICE Preliminary}}");
  tl_data2->DrawLatexNDC(0.55,0.79,"#bf{p-Pb #sqrt{s} = 5.02 TeV}");
  //tl_data2->DrawLatexNDC(0.55,0.75,"#bf{#it{L}_{int} = 4.96 nb^{-1},} #bf{|#it{#eta}_{#gamma}| < 0.67}");//QM prelim
  tl_data2->DrawLatexNDC(0.55,0.75,"#bf{#it{L}_{int} = 5.47 nb^{-1},} #bf{|#it{#eta}_{#gamma}| < 0.67}");
  tl_data2->DrawLatexNDC(0.55,0.70,"#bf{#it{R} = 0.4, #it{p}_{T}^{iso,ch} < 1.5 GeV/#it{c}}");
  TLatex* tl_pQCD = new TLatex();
  tl_pQCD->SetTextAlign(11);
  tl_pQCD->SetTextSize(0.032);
  tl_pQCD->DrawLatexNDC(0.18,0.38,"#bf{#it{R} = 0.4, #it{p}_{T}^{iso} < 2 GeV/#it{c}}");//.18
  tl_pQCD->DrawLatexNDC(0.18,0.34,"#bf{W. Vogelsang(NLO)}");//.22 diff
  tl_pQCD->DrawLatexNDC(0.18,0.30,"#bf{CT18 PDF, nCTEQ15 nPDF}");//.14
  tl_pQCD->DrawLatexNDC(0.18,0.26,"#bf{GRV FF}");
  tl_pQCD->DrawLatexNDC(0.18,0.22,"#bf{NLO JETPHOX #times #kappa^{iso}}");
  tl_pQCD->DrawLatexNDC(0.18,0.18,"#bf{NNPDF40 PDF, nNNPDF30 nPDF}");//.14
  tl_pQCD->DrawLatexNDC(0.18,0.14,"#bf{BFG II FF}");//*/
  TLegend* lJetphoxCompare = new TLegend(0.54, 0.46, 0.7, 0.69);
  lJetphoxCompare->SetTextSize(0.033);
  lJetphoxCompare->SetFillStyle(0);
  lJetphoxCompare->SetMargin(0.3); 
  lJetphoxCompare->AddEntry(csDhruvStat_pPb, "Data and stat. unc.", "EP");
  lJetphoxCompare->AddEntry(csDhruvSys_pPb, "Systematic unc.", "PF");
  lJetphoxCompare->AddEntry(g_pQCD_nPDF_sum_pPb[0][1], "W. Vogelsang(NLO)", "L");
  lJetphoxCompare->AddEntry(g_pQCD_nPDF_sum_pPb_Scale[0], "Theory scale uncertainty", "F");
  lJetphoxCompare->AddEntry(jetphox_pPb_10_ScaleSys, "JETPHOX scale uncertainty", "F");
  lJetphoxCompare->AddEntry((TObject*)0, "#it{p}_{T}^{#gamma}/2 < #mu < 2x #it{p}_{T}^{#gamma}", "");  
  lJetphoxCompare->Draw("same");
  //cJetphoxCompare->Print("QM2022_figures/pPbData_pPbJETPHOXKappa_Vogelsang_postQM_wEta.pdf");
    
  //Ratio with JETPHOX
  Double_t jtphx_pPb_05_ratio_Mean[numBins] = {0};
  Double_t jtphx_pPb_05_ratio_Stat[numBins] = {0};
  Double_t jtphx_pPb_05_ratio_Sys[numBins] = {0};
  Double_t jtphx_pPb_10_ratio_Mean[numBins] = {0};
  Double_t jtphx_pPb_10_ratio_Stat[numBins] = {0};
  Double_t jtphx_pPb_10_ratio_Sys[numBins] = {0};
  Double_t jtphx_pPb_20_ratio_Mean[numBins] = {0};
  Double_t jtphx_pPb_20_ratio_Stat[numBins] = {0};
  Double_t jtphx_pPb_20_ratio_Sys[numBins] = {0};
  Double_t jtphx_pPb_diff_20_10_ratio[numBins] = {0};
  Double_t jtphx_pPb_diff_10_05_ratio[numBins] = {0};
  for(int i = 0; i < numBins; i++){
    Double_t contentRatio_05_Mean = dhruvCSMean_pPb[i]/jtphx_pPb_05_Mean[i];
    Double_t contentRatio_05_Stat = contentRatio_05_Mean*dhruvCSStat_pPb[i]/dhruvCSMean_pPb[i];
    Double_t contentRatio_05_Sys = contentRatio_05_Mean*dhruvCSSys_pPb[i]/dhruvCSMean_pPb[i];
    jtphx_pPb_05_ratio_Mean[i] = contentRatio_05_Mean;
    jtphx_pPb_05_ratio_Stat[i] = contentRatio_05_Stat;
    jtphx_pPb_05_ratio_Sys[i] = contentRatio_05_Sys;
    
    Double_t contentRatio_10_Mean = dhruvCSMean_pPb[i]/jtphx_pPb_10_Mean[i];
    Double_t contentRatio_10_Stat = contentRatio_10_Mean*dhruvCSStat_pPb[i]/dhruvCSMean_pPb[i];
    Double_t contentRatio_10_Sys = contentRatio_10_Mean*dhruvCSSys_pPb[i]/dhruvCSMean_pPb[i];
    jtphx_pPb_10_ratio_Mean[i] = contentRatio_10_Mean;
    jtphx_pPb_10_ratio_Stat[i] = contentRatio_10_Stat;
    jtphx_pPb_10_ratio_Sys[i] = contentRatio_10_Sys;
    
    Double_t contentRatio_20_Mean = dhruvCSMean_pPb[i]/jtphx_pPb_20_Mean[i];
    Double_t contentRatio_20_Stat = contentRatio_20_Mean*dhruvCSStat_pPb[i]/dhruvCSMean_pPb[i];
    Double_t contentRatio_20_Sys = contentRatio_20_Mean*dhruvCSSys_pPb[i]/dhruvCSMean_pPb[i];
    jtphx_pPb_20_ratio_Mean[i] = contentRatio_20_Mean;
    jtphx_pPb_20_ratio_Stat[i] = contentRatio_20_Stat;
    jtphx_pPb_20_ratio_Sys[i] = contentRatio_20_Sys;
    
    jtphx_pPb_diff_20_10_ratio[i] = contentRatio_20_Mean - contentRatio_10_Mean;
    jtphx_pPb_diff_10_05_ratio[i] = contentRatio_10_Mean - contentRatio_05_Mean;
    //cout << contentRatio_20_Mean << "\t" <<  contentRatio_10_Mean << "\t" << contentRatio_05_Mean << "\t" << contentRatio_20_Mean - contentRatio_10_Mean << "\t" << contentRatio_10_Mean - contentRatio_05_Mean << endl;
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
  /*TCanvas* cjetphoxpPb05Ratio = new TCanvas("cjetphoxpPb05Ratio",  "cjetphoxpPb05Ratio", 1500, 900);
  cjetphoxpPb05Ratio->Divide(3, 1);
  cjetphoxpPb05Ratio->cd(1);
  //cjetphoxpPb05Ratio->DrawFrame(12, 1, 60, 3000);
  cjetphoxpPb05Ratio->SetLeftMargin(0.15);
  cjetphoxpPb05Ratio->SetRightMargin(0.07);
  jetphox_pPb_05_ratioSys->GetYaxis()->SetRangeUser(0, 2);
  jetphox_pPb_05_ratioSys->Draw("AE5");
  jetphox_pPb_05_ratioStat->Draw("PEsame");
  line->Draw("same");//*/

  TGraphErrors* jetphox_pPb_10_ratioStat = new TGraphErrors(8, xBinCenters,  jtphx_pPb_10_ratio_Mean, xErr, jtphx_pPb_10_ratio_Stat);
  TGraphErrors* jetphox_pPb_10_ratioSys = new TGraphErrors(8, xBinCenters,  jtphx_pPb_10_ratio_Mean, xErrSys, jtphx_pPb_10_ratio_Sys);
  jetphox_pPb_10_ratioStat->SetMarkerStyle(kFullCircle);
  jetphox_pPb_10_ratioStat->SetMarkerSize(2);
  jetphox_pPb_10_ratioStat->SetMarkerColor(kBlack);
  jetphox_pPb_10_ratioStat->SetLineColor(kBlack);
  jetphox_pPb_10_ratioStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");  
  jetphox_pPb_10_ratioSys->SetLineColor(kBlack);
  jetphox_pPb_10_ratioSys->SetLineWidth(2);
  jetphox_pPb_10_ratioSys->SetFillStyle(3001);
  jetphox_pPb_10_ratioSys->GetXaxis()->SetRangeUser(12, 60);
  jetphox_pPb_10_ratioSys->SetTitle("#mu = 1.0;E_{T} [GeV]; data/NLO JETPHOX");
  /*cjetphoxpPb05Ratio->cd(2);
  //cjetphoxpPb05Ratio->DrawFrame(12, 1, 60, 3000);
  cjetphoxpPb05Ratio->SetRightMargin(0.07);
  jetphox_pPb_10_ratioSys->GetYaxis()->SetRangeUser(0, 2);
  jetphox_pPb_10_ratioSys->Draw("AE5");
  jetphox_pPb_10_ratioStat->Draw("PEsame");
  line->Draw("same");//*/

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
  /*cjetphoxpPb05Ratio->cd(3);
  //cjetphoxpPb05Ratio->DrawFrame(12, 1, 60, 3000);
  cjetphoxpPb05Ratio->SetRightMargin(0.07);
  jetphox_pPb_20_ratioSys->GetYaxis()->SetRangeUser(0, 2);
  jetphox_pPb_20_ratioSys->Draw("AE5");
  jetphox_pPb_20_ratioStat->Draw("PEsame");
  line->Draw("same");//*/
  
  
  TGraphAsymmErrors* jetphox_pPb_10_ratioScaleSys = new TGraphAsymmErrors(8, xBinCenters, xOnes, xErrSys, xErrSys, jtphx_pPb_diff_10_05_ratio, jtphx_pPb_diff_20_10_ratio);
  jetphox_pPb_10_ratioScaleSys->SetLineColor(kGreen);
  jetphox_pPb_10_ratioScaleSys->SetLineWidth(0);
  //jetphox_pPb_10_ratioScaleSys->SetFillStyle(3001);
  jetphox_pPb_10_ratioScaleSys->SetFillColorAlpha(kGreen+1,0.7);
  jetphox_pPb_10_ratioSys->GetXaxis()->SetRangeUser(12, 60);
  jetphox_pPb_10_ratioSys->GetYaxis()->SetRangeUser(0.6, 2.0);
  jetphox_pPb_10_ratioSys->SetTitle(";#it{p}_{T}^{#gamma} [GeV/#it{c}]; Data/JETPHOX");
  jetphox_pPb_10_ratioSys->GetYaxis()->SetTitleOffset(1.1);
  jetphox_pPb_10_ratioSys->GetXaxis()->SetTitleOffset(1.2);
  jetphox_pPb_10_ratioSys->SetMarkerSize(0);
  TCanvas* cJetphoxpPbRatio = new TCanvas("cJetphoxpPbRatio",  "cJetphoxpPbRatio", 1200, 900);
  cJetphoxpPbRatio->SetLeftMargin(0.15);
  cJetphoxpPbRatio->SetRightMargin(0.07);
  cJetphoxpPbRatio->SetBottomMargin(0.15);
  jetphox_pPb_10_ratioSys->Draw("AE5");
  jetphox_pPb_10_ratioStat->Draw("PE same");
  jetphox_pPb_10_ratioScaleSys->Draw("samee2");
  line->Draw("same");
  TLatex* tJetphoxpPbRatio = new TLatex();
  tJetphoxpPbRatio->SetTextAlign(11);
  tJetphoxpPbRatio->SetTextSize(0.035);
  tJetphoxpPbRatio->DrawLatexNDC(0.19,0.84,"#bf{#scale[1.2]{ALICE Preliminary}}");
  tJetphoxpPbRatio->DrawLatexNDC(0.19,0.80,"#bf{p-Pb #sqrt{s} = 5.02 TeV}");
  //tJetphoxpPbRatio->DrawLatexNDC(0.19,0.76,"#bf{#it{L}_{int} = 4.96 nb^{-1}, |#it{#eta}_{#gamma}| < 0.67}");//QM preim
  tJetphoxpPbRatio->DrawLatexNDC(0.19,0.76,"#bf{#it{L}_{int} = 5.47 nb^{-1}, |#it{#eta}_{#gamma}| < 0.67}");
  tJetphoxpPbRatio->DrawLatexNDC(0.19,0.71,"#bf{#it{R} = 0.4, #it{p}_{T}^{iso,ch} < 1.5 GeV/#it{c}}");
  tJetphoxpPbRatio->DrawLatexNDC(0.19,0.66,"#bf{NLO JETPHOX #times #kappa^{iso}}");
  tJetphoxpPbRatio->DrawLatexNDC(0.19,0.62,"#bf{NNPDF40 PDF, nNNPDF30 nPDF}");
  tJetphoxpPbRatio->DrawLatexNDC(0.19,0.58,"#bf{BFG II FF}");
  tJetphoxpPbRatio->DrawLatexNDC(0.19,0.54,"#bf{#it{R} = 0.4, #it{p}_{T}^{iso} < 2 GeV/#it{c}}");//*/

  TLegend* lJetphoxpPbRatio = new TLegend(0.53, 0.70, 0.82, 0.86);
  lJetphoxpPbRatio->SetTextSize(0.035);
  lJetphoxpPbRatio->SetFillStyle(0);
  lJetphoxpPbRatio->SetMargin(0.3); 
  lJetphoxpPbRatio->AddEntry(jetphox_pPb_10_ratioStat, "Ratio with stat. unc.", "EP");
  lJetphoxpPbRatio->AddEntry(jetphox_pPb_10_ratioSys, "Systematic uncertainty", "F");
  lJetphoxpPbRatio->AddEntry(jetphox_pPb_10_ratioScaleSys, "JETPHOX scale uncertainty", "F");
  lJetphoxpPbRatio->AddEntry((TObject*)0, "#it{p}_{T}^{#gamma}/2 < #mu < 2x #it{p}_{T}^{#gamma}", "");
  lJetphoxpPbRatio->Draw("same");
  
  //cJetphoxpPbRatio->Print("QM2022_figures/pPbData_pPbJETPHOXKappa_ratio_postQM_wEta.pdf");
}//end makeComparisons
