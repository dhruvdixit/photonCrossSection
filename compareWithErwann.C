#include <fstream>
#include <vector>
void compareWithErwann(){{

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  
  TLine *line = new TLine(12, 1, 54, 1);
  line->SetLineColor(kBlack);

  const int numBins = 8;
  Double_t xBinCenters[numBins] = {13, 15, 17, 19, 22.5, 27.5, 35, 50};
  Double_t xErr[numBins] = {0};
  Double_t erwannCSMean[numBins] = {2015.57, 1151.86, 696.985, 444.604, 233.026, 104.87, 38.5216, 7.4227};
  Double_t erwannCSStat[numBins] = {337.901, 71.0714, 51.475, 35.3468, 15.5412, 10.4705, 4.64552, 1.38719};
  Double_t erwannCSSys[numBins] = {308.501, 167.064, 96.1471, 58.8658, 29.4243, 12.7484, 4.7213, 1.11858};
  
  Double_t dhruvCSMean[numBins] = {1924.31, 1286.57, 823.076, 525.652, 284.654, 128.145, 49.117, 8.77088};
  Double_t dhruvCSStat[numBins] = {12.091, 11.79, 10.4942, 9.00236, 4.47992, 3.15132, 1.38649, 0.411638};
  Double_t dhruvCSSys[numBins] = {244.3, 135.641, 78.439, 47.7364, 25.2224, 11.4663, 4.48855, 0.811153};
  
  TGraphErrors* csErwannStat = new TGraphErrors(8, xBinCenters, erwannCSMean, xErr, erwannCSStat);
  TGraphErrors* csErwannSys = new TGraphErrors(8, xBinCenters, erwannCSMean, xErr, erwannCSSys);
  TGraphErrors* csDhruvStat = new TGraphErrors(8, xBinCenters, dhruvCSMean, xErr, dhruvCSStat);
  TGraphErrors* csDhruvSys = new TGraphErrors(8, xBinCenters, dhruvCSMean, xErr, dhruvCSSys);

  csErwannStat->SetMarkerStyle(20); csErwannStat->SetMarkerColor(kBlack);
  csErwannSys->SetFillColor(kBlack); csErwannSys->SetFillStyle(3004);
  csDhruvStat->SetMarkerStyle(20); csDhruvStat->SetMarkerColor(kRed); csDhruvStat->SetLineColor(kRed);
  csDhruvSys->SetFillColor(kOrange);
  csDhruvStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csErwannStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csDhruvSys->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csErwannSys->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  TLegend* lCs = new TLegend(0.4, 0.6, 0.87, 0.87);
  lCs->AddEntry(csErwannStat, "Preliminiary cross-section results", "PF");
  lCs->AddEntry(csErwannSys, "Sys Err on Preliminiary cross-section results", "PF");
  lCs->AddEntry(csDhruvStat, "Dhruv's cross-section results", "PF");
  lCs->AddEntry(csDhruvSys, "Sys Err on Dhruv's cross-section results", "PF");
  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->DrawFrame(12, 1, 60, 3000);
  c1->SetLogy();
  csErwannSys->Draw("E3AL");
  csDhruvSys->Draw("E3 same");
  csErwannStat->Draw("PESame");
  csDhruvStat->Draw("PESame");
  lCs->Draw("same");
  
  Double_t ratioCSMean[numBins] = {0};
  Double_t ratioCSStat[numBins] = {0};
  Double_t ratioCSSys[numBins] = {0};
  for(int i = 0; i < numBins; i++){
    ratioCSMean[i] = erwannCSMean[i]/dhruvCSMean[i];
    ratioCSStat[i] = ratioCSMean[i]*(erwannCSStat[i]/erwannCSMean[i]);//ratioCSMean[i]*TMath::Sqrt(TMath::Power(erwannCSStat[i]/erwannCSMean[i], 2) + TMath::Power(dhruvStat[i]/dhruvCSMean[i], 2));
    ratioCSSys[i] = ratioCSMean[i]*TMath::Sqrt(TMath::Power(erwannCSSys[i]/erwannCSMean[i], 2) + TMath::Power(dhruvCSSys[i]/dhruvCSMean[i], 2));
  }

  TGraphErrors* csRatioStat = new TGraphErrors(8, xBinCenters, ratioCSMean, xErr, ratioCSStat);
  TGraphErrors* csRatioSys = new TGraphErrors(8, xBinCenters, ratioCSMean, xErr, ratioCSSys);
  csRatioStat->SetTitle(";E_{T} [GeV];#frac{cross section_{prelim}}{cross section_{dhruv}}");
  csRatioSys->SetTitle(";E_{T} [GeV];#frac{cross section_{prelim}}{cross section_{dhruv}}");
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

  //Efficiency comparison
  Double_t erwannEffMean[numBins] = {0.588658, 0.588779, 0.592832, 0.603951, 0.615985, 0.634618, 0.64918, 0.668659};
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
  lEff->AddEntry(effErwannStat, "Preliminiary efficiency results", "PF");
  lEff->AddEntry(effErwannSys, "Sys Err on Preliminiary efficiency results", "PF");
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
  effRatioStat->SetTitle(";E_{T} [GeV];#frac{eff_{prelim}}{eff_{dhruv}}");
  effRatioSys->SetTitle(";E_{T} [GeV];#frac{eff_{prelim}}{eff_{dhruv}}");
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
  Double_t erwannPrtyMean[numBins] = {0.330486, 0.427572, 0.502339, 0.590244, 0.627706, 0.653977, 0.65251, 0.673619};
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
