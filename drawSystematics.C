#include <fstream>
#include <vector>
void drawSystematics(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  
  TLine *line = new TLine(12, 1, 54, 1);
  line->SetLineColor(kBlack);

  const int numBins = 8;
  Double_t xBinCenters[numBins] = {13, 15, 17, 19, 22.5, 27.5, 35, 50};
  Double_t xErr[numBins] = {0};
  Double_t erwannMean[numBins] = {2015.57, 1151.86, 696.985, 444.604, 233.026, 104.87, 38.5216, 7.4227};
  Double_t erwannStat[numBins] = {337.901, 71.0714, 51.475, 35.3468, 15.5412, 10.4705, 4.64552, 1.38719};
  Double_t erwannSys[numBins] = {308.501, 167.064, 96.1471, 58.8658, 29.4243, 12.7484, 4.7213, 1.11858};
  Double_t dhruvMean[numBins] = {1924.31, 1286.57, 823.076, 525.652, 284.654, 128.145, 49.117, 8.77088};
  Double_t dhruvStat[numBins] = {12.091, 11.79, 10.4942, 9.00236, 4.47992, 3.15132, 1.38649, 0.411638};
  Double_t dhruvSys[numBins] = {244.3, 135.641, 78.439, 47.7364, 25.2224, 11.4663, 4.48855, 0.811153};

  Double_t dhruvMean_pp[numBins] = {9.411, 6.56199, 4.10474, 2.36822, 1.23861, 0.55767, 0.185445, 0.0338748};
  Double_t dhruvStat_pp[numBins] = {0.593559, 0.286304, 0.171845, 0.123759, 0.0586284, 0.0385993, 0.016245, 0.00520473};
  Double_t dhruvSys_pp[numBins] = {2.19421, 1.05879, 0.553396, 0.31634, 0.179202, 0.0827268, 0.0320843, 0.00702535};
  
  TGraphErrors* csErwannStat = new TGraphErrors(8, xBinCenters, erwannMean, xErr, erwannStat);
  TGraphErrors* csErwannSys = new TGraphErrors(8, xBinCenters, erwannMean, xErr, erwannSys);
  TGraphErrors* csDhruvStat = new TGraphErrors(8, xBinCenters, dhruvMean, xErr, dhruvStat);
  TGraphErrors* csDhruvSys = new TGraphErrors(8, xBinCenters, dhruvMean, xErr, dhruvSys);
  TGraphErrors* csDhruvStat_pp = new TGraphErrors(8, xBinCenters, dhruvMean_pp, xErr, dhruvStat_pp);
  TGraphErrors* csDhruvSys_pp = new TGraphErrors(8, xBinCenters, dhruvMean_pp, xErr, dhruvSys_pp);

  csErwannStat->SetMarkerStyle(20); csErwannStat->SetMarkerColor(kBlack);
  csErwannSys->SetFillColor(kBlack); csErwannSys->SetFillStyle(3004);
  csDhruvStat->SetMarkerStyle(20); csDhruvStat->SetMarkerColor(kRed); csDhruvStat->SetLineColor(kRed);
  csDhruvSys->SetFillColor(kOrange);
  csDhruvStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csErwannStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csDhruvSys->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csErwannSys->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  TLegend* leg = new TLegend(0.4, 0.6, 0.87, 0.87);
  leg->AddEntry(csErwannStat, "Erwann's cross-section results", "PF");
  leg->AddEntry(csErwannSys, "Sys Err on Erwann's cross-section results", "PF");
  leg->AddEntry(csDhruvStat, "Dhruv's cross-section results", "PF");
  leg->AddEntry(csDhruvSys, "Sys Err on Dhruv's cross-section results", "PF");
  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->DrawFrame(12, 1, 60, 3000);
  c1->SetLogy();
  csErwannSys->Draw("E3AL");
  csDhruvSys->Draw("E3 same");
  csErwannStat->Draw("PESame");
  csDhruvStat->Draw("PESame");
  leg->Draw("same");
  
  Double_t ratioMean[numBins] = {0};
  Double_t ratioStat[numBins] = {0};
  Double_t ratioSys[numBins] = {0};
  for(int i = 0; i < numBins; i++){
    ratioMean[i] = erwannMean[i]/dhruvMean[i];
    ratioStat[i] = ratioMean[i]*(erwannStat[i]/erwannMean[i]);//ratioMean[i]*TMath::Sqrt(TMath::Power(erwannStat[i]/erwannMean[i], 2) + TMath::Power(dhruvStat[i]/dhruvMean[i], 2));
    ratioSys[i] = ratioMean[i]*TMath::Sqrt(TMath::Power(erwannSys[i]/erwannMean[i], 2) + TMath::Power(dhruvSys[i]/dhruvMean[i], 2));
  }

  TGraphErrors* csRatioStat = new TGraphErrors(8, xBinCenters, ratioMean, xErr, ratioStat);
  TGraphErrors* csRatioSys = new TGraphErrors(8, xBinCenters, ratioMean, xErr, ratioSys);
  csRatioStat->SetTitle(";E_{T} [GeV];#frac{cross section_{erwann}}{cross section_{dhruv}}");
  csRatioSys->SetTitle(";E_{T} [GeV];#frac{cross section_{erwann}}{cross section_{dhruv}}");
  csRatioStat->GetXaxis()->SetRangeUser(12,60);
  csRatioSys->GetXaxis()->SetRangeUser(12,60);
  csRatioStat->GetYaxis()->SetRangeUser(0,2);
  csRatioSys->GetYaxis()->SetRangeUser(0,2);
  csRatioStat->SetMarkerStyle(20); csRatioStat->SetMarkerColor(kBlack);
  csRatioSys->SetFillColor(kBlack); csRatioSys->SetFillStyle(3004);
  TCanvas* c2 = new TCanvas("c2", "c2");
  c2->DrawFrame(12, 0, 60, 2);
  csRatioSys->Draw("E3AL");
  csRatioStat->Draw("PESame");
  line->Draw("Same");

  csDhruvStat_pp->SetMarkerStyle(20); csDhruvStat_pp->SetMarkerColor(kBlue);
  csDhruvSys_pp->SetFillColor(kMagenta); //csDhruvSys_pp->SetFillStyle(3004);
  csDhruvStat->SetMarkerStyle(20); csDhruvStat->SetMarkerColor(kRed); csDhruvStat->SetLineColor(kRed);
  csDhruvSys->SetFillColor(kOrange);
  csDhruvStat_pp->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csDhruvStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csDhruvSys_pp->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csDhruvSys->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  TLegend* leg2 = new TLegend(0.65, 0.6, 0.9, 0.87);
  leg2->AddEntry(csDhruvStat_pp, "pp", "PF");
  leg2->AddEntry(csDhruvSys_pp, "Sys Err on pp", "PF");
  leg2->AddEntry(csDhruvStat, "p-Pb", "PF");
  leg2->AddEntry(csDhruvSys, "Sys Err on p-Pb", "PF");
  TCanvas* c3 = new TCanvas("c3", "c3");
  c3->DrawFrame(12, 1e-100, 60, 3000);
  c3->SetLogy();
  csDhruvSys_pp->GetYaxis()->SetRangeUser(1e-2, 5e3);
  csDhruvSys_pp->Draw("E3AL");
  csDhruvSys->Draw("E3 same");
  csDhruvStat_pp->Draw("PESame");
  csDhruvStat->Draw("PESame");
  leg2->Draw("same");

  Double_t rpaMean[numBins] = {0};
  Double_t rpaStat[numBins] = {0};
  Double_t rpaSys[numBins] = {0};
  Double_t A = 208;
  for(int i = 0; i < numBins; i++){
    rpaMean[i] = dhruvMean[i]/(A*dhruvMean_pp[i]);
    rpaStat[i] = rpaMean[i]*TMath::Sqrt(TMath::Power(dhruvStat_pp[i]/dhruvMean_pp[i], 2) + TMath::Power(dhruvStat[i]/dhruvMean[i], 2));
    rpaSys[i] = rpaMean[i]*TMath::Sqrt(TMath::Power(dhruvSys_pp[i]/dhruvMean_pp[i], 2) + TMath::Power(dhruvSys[i]/dhruvMean[i], 2));
  }
  TGraphErrors* csRpaStat = new TGraphErrors(8, xBinCenters, rpaMean, xErr, rpaStat);
  TGraphErrors* csRpaSys = new TGraphErrors(8, xBinCenters, rpaMean, xErr, rpaSys);
  csRpaStat->SetTitle(";E_{T} [Ge];#frac{#sigma_{pPb}}{A*#sigma_{pp}}");
  csRpaSys->SetTitle(";E_{T} [GeV];#frac{#sigma_{pPb}}{A*#sigma_{pp}}");
  csRpaStat->GetXaxis()->SetRangeUser(12,60);
  csRpaSys->GetXaxis()->SetRangeUser(12,60);
  csRpaStat->GetYaxis()->SetRangeUser(0,2);
  csRpaSys->GetYaxis()->SetRangeUser(0,2);
  csRpaStat->SetMarkerStyle(20); csRpaStat->SetMarkerColor(kBlack);
  csRpaSys->SetFillColor(kBlack); csRpaSys->SetFillStyle(3004);
  TCanvas* c4 = new TCanvas("c4", "c4");
  c4->DrawFrame(12, 0, 60, 2);
  csRpaSys->Draw("E3AL");
  csRpaStat->Draw("PESame");
  line->Draw("Same");
  csRpaStat->Fit("pol0", "", "", 12, 60);



}//end makeComparisons
