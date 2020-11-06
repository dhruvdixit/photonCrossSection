#include <fstream>
#include <vector>
void calcSystematics(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  

  //Obtain and plotting histograms from data

  TFile* file_Std = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_CorrectPurityFit.root","READ");
  TH1F* rpa_Std = (TH1F*)file_Std->Get("h_RpA");rpa_Std->SetLineColor(kRed);rpa_Std->SetMarkerColor(kRed);
  TH1F* hcsEG1_Std = (TH1F*)file_Std->Get("crossSection_pPb");hcsEG1_Std->SetLineColor(kRed);hcsEG1_Std->SetMarkerColor(kRed);
  TH1F* hcspp_Std = (TH1F*)file_Std->Get("crossSection_pp");hcspp_Std->SetLineColor(kRed);hcspp_Std->SetMarkerColor(kRed);

  TFile* file_Plus = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_PlusPurityFit.root","READ");
  TH1F* rpa_Plus = (TH1F*)file_Plus->Get("h_RpA");rpa_Plus->SetLineColor(kMagenta);rpa_Plus->SetMarkerColor(kMagenta);
  TH1F* hcsEG1_Plus = (TH1F*)file_Plus->Get("crossSection_pPb");hcsEG1_Plus->SetLineColor(kMagenta);hcsEG1_Plus->SetMarkerColor(kMagenta);
  TH1F* hcspp_Plus = (TH1F*)file_Plus->Get("crossSection_pp");hcspp_Plus->SetLineColor(kMagenta);hcspp_Plus->SetMarkerColor(kMagenta);

  TFile* file_Minus = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_MinusPurityFit.root","READ");
  TH1F* rpa_Minus = (TH1F*)file_Minus->Get("h_RpA");rpa_Minus->SetLineColor(kBlue);rpa_Minus->SetMarkerColor(kBlue);
  TH1F* hcsEG1_Minus = (TH1F*)file_Minus->Get("crossSection_pPb");hcsEG1_Minus->SetLineColor(kBlue);hcsEG1_Minus->SetMarkerColor(kBlue);
  TH1F* hcspp_Minus = (TH1F*)file_Minus->Get("crossSection_pp");hcspp_Minus->SetLineColor(kBlue);hcspp_Minus->SetMarkerColor(kBlue);
  
  
  
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);

  //RpA
  TLegend* lRpA = new TLegend(0.6,0.7,0.85,0.85);
  lRpA->SetHeader("R_{pPb}");
  lRpA->AddEntry(rpa_Std, "Usual purity");


  TCanvas* cRpA = new TCanvas();
  rpa_Std->Draw("e1");
  line->Draw("same");
  lRpA->Draw("same");


  //HcsEG1
  TLegend* lHcsEG1 = new TLegend(0.6,0.7,0.85,0.85);
  lHcsEG1->SetHeader("p-Pb EG1 cross section");
  lHcsEG1->AddEntry(hcsEG1_Std, "usual purity");
  lHcsEG1->AddEntry(hcsEG1_Plus, "+#sigma purity");
  lHcsEG1->AddEntry(hcsEG1_Minus, "-#sigma purity");

  TCanvas* cHcsEG1 = new TCanvas();
  cHcsEG1->SetLogy();
  hcsEG1_Std->GetXaxis()->SetRangeUser(12, 60);
  hcsEG1_Std->Draw("e1");
  hcsEG1_Plus->Draw("samee1");
  hcsEG1_Minus->Draw("samee1");
  lHcsEG1->Draw("same");

  //Hcspp
  TLegend* lHcspp = new TLegend(0.6,0.7,0.85,0.85);
  lHcspp->SetHeader("pp cross section");
  lHcspp->AddEntry(hcspp_Std, "usual purity");
  lHcspp->AddEntry(hcspp_Plus, "+#sigma purity");
  lHcspp->AddEntry(hcspp_Minus, "-#sigma purity");

  TCanvas* cHcspp = new TCanvas();
  cHcspp->SetLogy();
  hcspp_Std->GetXaxis()->SetRangeUser(12, 60);
  hcspp_Std->Draw("e1");
  hcspp_Plus->Draw("samee1");
  hcspp_Minus->Draw("samee1");
  lHcspp->Draw("same");


  const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning
  TH1F* diffPlus_pPb = (TH1F*)hcsEG1_Plus->Clone("diffPlus_pPb");
  diffPlus_pPb->SetTitle(";E_{T} [GeV/c]; #frac{|+#sigma_{purity} - CV_{purity}|}{CV_{purity}} [%]");
  diffPlus_pPb->Add(hcsEG1_Std, -1);
  //diffPlus_pPb->Scale(0.5);
  diffPlus_pPb->Divide(hcsEG1_Std);

  TH1F* diffMinus_pPb = (TH1F*)hcsEG1_Std->Clone("diffMinus_pPb");
  diffMinus_pPb->SetTitle(";E_{T} [GeV/c]; #frac{|-#sigma_{purity} - CV_{purity}|}{CV_{purity}} [%]");
  diffMinus_pPb->Add(hcsEG1_Minus, -1);
  //diffMinus_pPb->Scale(0.5);
  diffMinus_pPb->Divide(hcsEG1_Std);

  TCanvas* cdiffPlus_pPb = new TCanvas("cdiffPlus_pPb", "", 1600, 800);
  cdiffPlus_pPb->Divide(2);
  cdiffPlus_pPb->cd(1);
  cdiffPlus_pPb->SetLeftMargin(0.15);
  cdiffPlus_pPb->SetRightMargin(0.05);
  diffPlus_pPb->GetXaxis()->SetRangeUser(12, 60);
  diffPlus_pPb->GetYaxis()->SetRangeUser(0, 0.25);
  diffPlus_pPb->GetYaxis()->SetTitleOffset(2);
  diffPlus_pPb->Draw("hist");

  
  //TCanvas* cdiffMinus_pPb = new TCanvas();
  cdiffPlus_pPb->cd(2);
  cdiffPlus_pPb->SetLeftMargin(0.15);
  cdiffPlus_pPb->SetRightMargin(0.05);
  diffMinus_pPb->GetXaxis()->SetRangeUser(12, 60);
  diffMinus_pPb->GetYaxis()->SetRangeUser(0, 0.25);
  diffMinus_pPb->GetYaxis()->SetTitleOffset(2);
  diffMinus_pPb->Draw("hist");

  //pp
  TH1F* diffPlus_pp = (TH1F*)hcspp_Plus->Clone("diffPlus_pp");
  diffPlus_pp->SetTitle(";E_{T} [GeV/c]; #frac{|+#sigma_{purity} - CV_{purity}|}{CV_{purity}} [%]");
  diffPlus_pp->Add(hcspp_Std, -1);
  //diffPlus_pp->Scale(0.5);
  diffPlus_pp->Divide(hcspp_Std);

  TH1F* diffMinus_pp = (TH1F*)hcspp_Std->Clone("diffMinus_pp");
  diffMinus_pp->SetTitle(";E_{T} [GeV/c]; #frac{|-#sigma_{purity} - CV_{purity}|}{CV_{purity}} [%]");
  diffMinus_pp->Add(hcspp_Minus, -1);
  //diffMinus_pp->Scale(0.5);
  diffMinus_pp->Divide(hcspp_Std);

  TCanvas* cdiffPlus_pp = new TCanvas("cdiffPlus_pp", "", 1600, 800);
  cdiffPlus_pp->Divide(2);
  cdiffPlus_pp->cd(1);
  cdiffPlus_pp->SetLeftMargin(0.15);
  cdiffPlus_pp->SetRightMargin(0.05);
  diffPlus_pp->GetXaxis()->SetRangeUser(12, 60);
  diffPlus_pp->GetYaxis()->SetRangeUser(0, 0.25);
  diffPlus_pp->GetYaxis()->SetTitleOffset(2);
  diffPlus_pp->Draw("hist");

  
  //TCanvas* cdiffMinus_pp = new TCanvas();
  cdiffPlus_pp->cd(2);
  cdiffPlus_pp->SetLeftMargin(0.15);
  cdiffPlus_pp->SetRightMargin(0.05);
  diffMinus_pp->GetXaxis()->SetRangeUser(12, 60);
  diffMinus_pp->GetYaxis()->SetRangeUser(0, 0.25);
  diffMinus_pp->GetYaxis()->SetTitleOffset(2);
  diffMinus_pp->Draw("hist");
  
  
  



 


  
}//end makeComparisons
