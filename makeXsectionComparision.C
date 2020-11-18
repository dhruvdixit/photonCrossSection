#include <fstream>
#include <vector>
void makeXsectionComparision(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  

  //Obtain and plotting histograms from data

  TFile* fileB = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_crossSectionHistos_fullList_before.root","READ");
  TFile* fileA = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/_crossSectionHistos_fullList_after.root","READ");
  
  TH1F* rpaB = (TH1F*)fileB->Get("h_RpA");rpaB->SetLineColor(kRed);rpaB->SetMarkerColor(kRed);
  TH1F* rpaA = (TH1F*)fileA->Get("h_RpA");rpaA->SetLineColor(kBlue);rpaA->SetMarkerColor(kBlue);

  TH1F* pPbcsB = (TH1F*)fileB->Get("crossSection_pPb");pPbcsB->SetLineColor(kRed);pPbcsB->SetMarkerColor(kRed);
  TH1F* ppcsB = (TH1F*)fileB->Get("crossSection_pp");ppcsB->SetLineColor(kRed);ppcsB->SetMarkerColor(kRed);
  
  TH1F* pPbcsA = (TH1F*)fileA->Get("crossSection_pPb");pPbcsA->SetLineColor(kBlue);pPbcsA->SetMarkerColor(kBlue);
  TH1F* ppcsA = (TH1F*)fileA->Get("crossSection_pp");ppcsA->SetLineColor(kBlue);ppcsA->SetMarkerColor(kBlue);

  TH1F* pPbspectraB = (TH1F*)fileB->Get("hClusterSpectra_EG1");pPbspectraB->SetLineColor(kRed);pPbspectraB->SetMarkerColor(kRed);
  TH1F* ppspectraB = (TH1F*)fileB->Get("hClusterSpectra_pp");ppspectraB->SetLineColor(kRed);ppspectraB->SetMarkerColor(kRed);
  
  TH1F* pPbspectraA = (TH1F*)fileA->Get("hClusterSpectra_EG1");pPbspectraA->SetLineColor(kBlue);pPbspectraA->SetMarkerColor(kBlue);
  TH1F* ppspectraA = (TH1F*)fileA->Get("hClusterSpectra_pp");ppspectraA->SetLineColor(kBlue);ppspectraA->SetMarkerColor(kBlue);
  
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);
  
  TCanvas* crpa = new TCanvas();
  rpaB->Draw();
  rpaA->Draw("same");
  line->Draw("same");
  
  TCanvas* cpPbcs = new TCanvas();
  cpPbcs->SetLogy();
  pPbcsB->SetTitle(";E_{T};pPb cross section");
  pPbcsB->Draw();
  pPbcsA->Draw("same");

  TCanvas* cppcs = new TCanvas();
  cppcs->SetLogy();
  ppcsB->SetTitle(";E_{T};pp cross section");
  ppcsB->Draw();
  ppcsA->Draw("same");
  
  TCanvas* cpPbspectra = new TCanvas();
  cpPbspectra->SetLogy();
  pPbspectraB->SetTitle(";E_{T};pPb spectra");
  pPbspectraB->Draw();
  pPbspectraA->Draw("same");

  TCanvas* cppspectra = new TCanvas();
  cppspectra->SetLogy();
  ppspectraB->SetTitle(";E_{T};pp spectra");
  ppspectraB->Draw();
  ppspectraA->Draw("same");


  TH1F* ratioRpA = (TH1F*)rpaB->Clone();ratioRpA->SetName("ratioRpA");ratioRpA->Divide(rpaA);
  TH1F* ratiopPbcs = (TH1F*)pPbcsB->Clone();ratiopPbcs->SetName("ratioPPbcs");ratiopPbcs->Divide(pPbcsA);
  TH1F* ratioppcs = (TH1F*)ppcsB->Clone();ratiopPbcs->SetName("ratioPPbcs");ratiopPbcs->Divide(ppcsA);
  TH1F* ratiopPbspectra = (TH1F*)pPbspectraB->Clone();ratiopPbspectra->SetName("ratioPPbspectra");ratiopPbspectra->Divide(pPbspectraA);
  TH1F* ratioppspectra = (TH1F*)ppspectraB->Clone();ratiopPbspectra->SetName("ratioPPbspectra");ratiopPbspectra->Divide(ppspectraA);

  TCanvas* cratio = new TCanvas();
  ratiopPbcs->GetYaxis()->SetRangeUser(0, 100);
  ratiopPbcs->Draw();
  //line->Draw("same");
  
}//end makeComparisons
