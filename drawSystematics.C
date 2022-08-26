#include <fstream>
#include <vector>
void drawSystematics(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  gStyle->SetCanvasPreferGL(kTRUE);
  
  TLine *line = new TLine(12, 1, 54, 1);
  line->SetLineColor(kBlack);

  const int numBins = 8;
  Double_t xBinCenters[numBins] = {13, 15, 17, 19, 22.5, 27.5, 35, 50};
  Double_t xErr[numBins] = {0};
  Double_t erwannMean[numBins] = {2015.57, 1151.86, 696.985, 444.604, 233.026, 104.87, 38.5216, 7.4227};
  Double_t erwannStat[numBins] = {337.901, 71.0714, 51.475, 35.3468, 15.5412, 10.4705, 4.64552, 1.38719};
  Double_t erwannSys[numBins] = {308.501, 167.064, 96.1471, 58.8658, 29.4243, 12.7484, 4.7213, 1.11858};
  //Double_t dhruvMean_EG1_AN[numBins] = {1924.31, 1286.57, 823.076, 525.652, 284.654, 128.145, 49.117, 8.77088};
  //Double_t dhruvStat_EG1_AN[numBins] = {12.091, 11.79, 10.4942, 9.00236, 4.47992, 3.15132, 1.38649, 0.411638};
  //Double_t dhruvMean_EG2_AN[numBins] = {1959.68, 1279.23, 834.874, 538.797, 273.551, 120.628, 50.2552, 7.14272};
  //Double_t dhruvStat_EG2_AN[numBins] = {35.2533, 34.1327, 30.6301, 26.4676, 12.7417, 8.86998, 4.06296, 1.07681};

  //Double_t dhruvMean_EG1_AN[numBins] = {1619.3, 1079.79, 692.178, 442.5, 238.985, 108.409, 41.5557, 7.4575};//fixed eff
  //Double_t dhruvStat_EG1_AN[numBins] = {21.8978, 17.1048, 12.8975, 9.57457, 4.31995, 2.85161, 1.21363, 0.352928};//fixed eff
  //Double_t dhruvMean_EG2_AN[numBins] = {1649.06, 1073.63, 702.1, 453.566, 229.664, 102.05, 42.5187, 6.07314};//fixed eff
  //Double_t dhruvStat_EG2_AN[numBins] = {35.6368, 31.829, 27.4688, 23.074, 10.8907, 7.56413, 3.45221, 0.916306};//fixed eff
  Double_t dhruvMean_EG1_AN[numBins] = {1692.55, 1061.36, 662.843, 427.047, 226.446, 107.452, 40.9216, 7.88297};//post QM
  Double_t dhruvStat_EG1_AN[numBins] = {16.7649, 13.1978, 10.5944, 8.73983, 4.14647, 2.94798, 1.28672, 0.39623};//post QM
  Double_t dhruvMean_EG2_AN[numBins] = {1781.35, 1121.49, 712.64, 424.797, 230.706, 106.69, 43.2809, 6.63078};//post QM
  Double_t dhruvStat_EG2_AN[numBins] = {36.1763, 32.3901, 28.0746, 23.088, 11.4462, 8.26608, 3.77433, 1.04871};//post QM
  
  Double_t dhruvSys_pPb[numBins] = {245.187, 136.576, 79.3291, 48.2625, 25.5367, 11.8048, 4.49563, 0.386485};//no cancellation in purity
  //Double_t dhruvSys_pPb[numBins] = {244.3, 135.641, 78.439, 47.7364, 25.2224, 11.4663, 4.48855, 0.811153};//missing ssc
  //Double_t dhruvSys_pPb[numBins] = {143.937, 92.3013, 57.2218, 36.2931, 19.7558, 9.09826, 3.55007, 0.640553};//only antiIso in purity
  Double_t dhruvSys_noSig_pPb[numBins] = {198.61, 121.72, 73.6017, 45.3362, 23.7503, 10.6415, 3.89291, 0.920238};//noSig in purity

  Double_t dhruvMean_pPb[numBins] = {0};
  Double_t dhruvStat_pPb[numBins] = {0};
  for(int i = 0; i < numBins; i++){
    Double_t errorSum = dhruvStat_EG1_AN[i]+dhruvStat_EG2_AN[i];
    dhruvMean_pPb[i] = (1.0 - dhruvStat_EG1_AN[i]/errorSum)*dhruvMean_EG1_AN[i] + (1.0 - dhruvStat_EG2_AN[i]/errorSum)*dhruvMean_EG2_AN[i];

    dhruvStat_pPb[i] = TMath::Sqrt(TMath::Power(dhruvStat_EG1_AN[i],2) + TMath::Power(dhruvStat_EG2_AN[i],2));
  }
  //Double_t dhruvMean_pp[numBins] = {7.87918, 5.47635, 3.40843, 1.97586, 1.02774, 0.466082, 0.15491, 0.0284661};//fixed eff
  //Double_t dhruvStat_pp[numBins] = {0.487914, 0.225647, 0.127018, 0.0863958, 0.0396474, 0.0276789, 0.0112095, 0.00333171};//fixed eff
  Double_t dhruvMean_pp[numBins] = {8.76905, 4.84717, 2.97868, 1.69761, 0.920006, 0.440048, 0.1574, 0.030219};//post QM
  Double_t dhruvStat_pp[numBins] = {0.42378, 0.255627, 0.192896, 0.108714, 0.0489118, 0.032834, 0.013023, 0.00392297};//post QM
  //Double_t dhruvMean_pp[numBins] = {9.411, 6.56199, 4.10474, 2.36822, 1.23861, 0.55767, 0.185445, 0.0338748};
  //Double_t dhruvStat_pp[numBins] = {0.593559, 0.286304, 0.171845, 0.123759, 0.0586284, 0.0385993, 0.016245, 0.00520473}; 

  Double_t dhruvSys_pp[numBins] = {2.21589, 1.06302, 0.558792, 0.319995, 0.181809, 0.089659, 0.0327108, 0.00715269};//no cancellation in purity
  //Double_t dhruvSys_pp[numBins] = {2.19421, 1.05879, 0.553396, 0.31634, 0.179202, 0.0827268, 0.0320843, 0.00702535};//missing ssc
  //Double_t dhruvSys_pp[numBins] = {0.664871, 0.42129, 0.267968, 0.162753, 0.0939587, 0.0480947, 0.0171494, 0.00318688};//only antiIso in purity
  Double_t dhruvSys_noSig_pp[numBins] = {1.49258, 0.73587, 0.399647, 0.221229, 0.12022, 0.0673696, 0.0215894, 0.00406779};//noSig in purity
  
  TGraphErrors* csErwannStat = new TGraphErrors(8, xBinCenters, erwannMean, xErr, erwannStat);
  TGraphErrors* csErwannSys = new TGraphErrors(8, xBinCenters, erwannMean, xErr, erwannSys);
  TGraphErrors* csDhruvStat = new TGraphErrors(8, xBinCenters, dhruvMean_pPb, xErr, dhruvStat_pPb);
  TGraphErrors* csDhruvSys = new TGraphErrors(8, xBinCenters, dhruvMean_pPb, xErr, dhruvSys_pPb);
  TGraphErrors* csDhruvStat_pp = new TGraphErrors(8, xBinCenters, dhruvMean_pp, xErr, dhruvStat_pp);
  TGraphErrors* csDhruvSys_pp = new TGraphErrors(8, xBinCenters, dhruvMean_pp, xErr, dhruvSys_pp);

  csErwannStat->SetMarkerStyle(20); csErwannStat->SetMarkerColor(kBlack);
  csErwannSys->SetFillColor(kBlack); csErwannSys->SetFillStyle(3004);
  //csDhruvStat->SetMarkerStyle(20); csDhruvStat->SetMarkerColor(kRed); csDhruvStat->SetLineColor(kRed);
  //csDhruvSys->SetFillColor(kOrange);
  csDhruvStat->SetMarkerSize(1.5);
  csDhruvStat->SetMarkerStyle(20);
  csDhruvStat->SetMarkerColor(kRed);
  csDhruvStat->SetLineStyle(1);
  csDhruvStat->SetLineWidth(2);
  csDhruvStat->SetLineColor(kRed);
    
  csDhruvSys->SetLineColor(0);
  csDhruvSys->SetFillColor(kRed);
  csDhruvSys->SetFillColorAlpha(kRed, 0.3);
  csDhruvSys->SetFillStyle(1001);
  csDhruvSys->SetLineWidth(0);
  csDhruvStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csErwannStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csDhruvSys->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csErwannSys->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  TLegend* leg = new TLegend(0.4, 0.6, 0.87, 0.87);
  leg->AddEntry(csErwannStat, "Preliminary cross-section results", "PF");
  leg->AddEntry(csErwannSys, "Sys Err on Preliminary cross-section results", "PF");
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
  //c1->SaveAs("erwannCompareCS_ISO133.pdf");
  //c1->SaveAs("erwannCompareCS_ISO133.png");
    
  Double_t ratioMean[numBins] = {0};
  Double_t ratioStat[numBins] = {0};
  Double_t ratioSys[numBins] = {0};
  for(int i = 0; i < numBins; i++){
    ratioMean[i] = erwannMean[i]/dhruvMean_pPb[i];
    ratioStat[i] = ratioMean[i]*(erwannStat[i]/erwannMean[i]);//ratioMean[i]*TMath::Sqrt(TMath::Power(erwannStat[i]/erwannMean[i], 2) + TMath::Power(dhruvStat_pPb[i]/dhruvMean_pPb[i], 2));
    ratioSys[i] = ratioMean[i]*TMath::Sqrt(TMath::Power(erwannSys[i]/erwannMean[i], 2) + TMath::Power(dhruvSys_pPb[i]/dhruvMean_pPb[i], 2));
  }

  TGraphErrors* csRatioStat = new TGraphErrors(8, xBinCenters, ratioMean, xErr, ratioStat);
  TGraphErrors* csRatioSys = new TGraphErrors(8, xBinCenters, ratioMean, xErr, ratioSys);
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
  //c2->SaveAs("erwannCompareRatio_ISO133.png");
  //c2->SaveAs("erwannCompareRatio_ISO133.png");

  csDhruvStat_pp->SetMarkerSize(1.5);
  csDhruvStat_pp->SetMarkerStyle(20);
  csDhruvStat_pp->SetMarkerColor(kBlue);
  csDhruvStat_pp->SetLineStyle(1);
  csDhruvStat_pp->SetLineWidth(2);
  csDhruvStat_pp->SetLineColor(kBlue);
    
  csDhruvSys_pp->SetLineColor(0);
  csDhruvSys_pp->SetFillColor(kBlue);
  csDhruvSys_pp->SetFillColorAlpha(kBlue, 0.3);
  csDhruvSys_pp->SetFillStyle(1001);
  csDhruvSys_pp->SetLineWidth(0);
  //csDhruvStat_pp->SetMarkerStyle(20); csDhruvStat_pp->SetMarkerColor(kBlue);
  //csDhruvSys_pp->SetFillColor(kMagenta); //csDhruvSys_pp->SetFillStyle(3004);
  //csDhruvStat->SetMarkerStyle(20); csDhruvStat->SetMarkerColor(kRed); csDhruvStat->SetLineColor(kRed);
  //csDhruvSys->SetFillColor(kOrange);
  csDhruvStat_pp->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csDhruvStat->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csDhruvSys_pp->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  csDhruvSys->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  TLegend* leg2 = new TLegend(0.65, 0.7, 0.9, 0.9);
  leg2->SetHeader("ALICE");
  leg2->AddEntry(csDhruvStat_pp, "pp #sqrt{s_{NN}} = 5.02 TeV", "PE");
  leg2->AddEntry(csDhruvSys_pp, "Sys. Unc. pp", "F");
  leg2->AddEntry(csDhruvStat, "p-Pb #sqrt{s_{NN}} = 5.02 TeV", "PE");
  leg2->AddEntry(csDhruvSys, "Sys. Unc. p-Pb", "F");
  
  TCanvas* c3 = new TCanvas("c3", "c3", 1000, 800);
  c3->SetLeftMargin(0.13);
  c3->SetTopMargin(0.07);
  c3->SetRightMargin(0.04);
  c3->SetBottomMargin(0.13);
  c3->DrawFrame(12, 1e-100, 60, 3000);
  c3->SetLogy();
  csDhruvSys_pp->GetYaxis()->SetRangeUser(1e-2, 5e3);
  csDhruvSys_pp->Draw("E3 AL");//Draw("E3AL");
  csDhruvSys->Draw("E3 same");//Draw("E3 same");
  csDhruvStat_pp->Draw("PE X0 same");//Draw("PESame");
  csDhruvStat->Draw("PE X0 same");//Draw("PESame");
  leg2->Draw("same");
  //c3->SaveAs("crossSection_pPbpp.pdf");

  /*//////////////////////////////////////////////////////////////////////////////////////////////////////
  //RpPb
  //////////////////////////////////////////////////////////////////////////////////////////////////////*/
  Double_t rpaMean[numBins] = {0};
  Double_t rpaStat[numBins] = {0};
  Double_t rpaSys[numBins] = {0};
  Double_t A = 208;
  cout << "bin center \t mean \t statErr \t statErr/mean \t sysErr \t sysErr/mean"<< endl;
  for(int i = 0; i < numBins; i++){
    rpaMean[i] = dhruvMean_pPb[i]/(A*dhruvMean_pp[i]);
    rpaStat[i] = rpaMean[i]*TMath::Sqrt(TMath::Power(dhruvStat_pp[i]/dhruvMean_pp[i], 2) + TMath::Power(dhruvStat_pPb[i]/dhruvMean_pPb[i], 2));
    rpaSys[i] = rpaMean[i]*TMath::Sqrt(TMath::Power(dhruvSys_noSig_pp[i]/dhruvMean_pp[i], 2) + TMath::Power(dhruvSys_noSig_pPb[i]/dhruvMean_pPb[i], 2));

    cout << xBinCenters[i] << "\t" <<  rpaMean[i] << "\t" << rpaStat[i] << "\t" << rpaStat[i]/rpaMean[i] << "\t" << rpaSys[i] <<  "\t" << rpaSys[i]/rpaMean[i] << endl;
  }
  TGraphErrors* csRpaStat = new TGraphErrors(8, xBinCenters, rpaMean, xErr, rpaStat);
  TGraphErrors* csRpaSys = new TGraphErrors(8, xBinCenters, rpaMean, xErr, rpaSys);
  csRpaStat->SetTitle(";E_{T} [Ge];R_{pPb} = #frac{#sigma_{pPb}}{A*#sigma_{pp}}");
  csRpaSys->SetTitle(";E_{T} [GeV];R_{pPb} = #frac{#sigma_{pPb}}{A*#sigma_{pp}}");
  csRpaStat->GetXaxis()->SetRangeUser(12,60);
  csRpaSys->GetXaxis()->SetRangeUser(12,60);
  csRpaStat->GetYaxis()->SetRangeUser(0,2);
  csRpaSys->GetYaxis()->SetRangeUser(0,2);
  //csRpaStat->SetMarkerStyle(20); csRpaStat->SetMarkerColor(kBlack);
  //csRpaSys->SetFillColor(kBlack); csRpaSys->SetFillStyle(3004);
  csRpaStat->SetMarkerSize(1.5);
  csRpaStat->SetMarkerStyle(20);
  csRpaStat->SetMarkerColor(kRed);
  csRpaStat->SetLineStyle(1);
  csRpaStat->SetLineWidth(2);
  csRpaStat->SetLineColor(kRed);
    
  csRpaSys->SetLineColor(0);
  csRpaSys->SetFillColor(kRed);
  csRpaSys->SetFillColorAlpha(kRed, 0.3);
  csRpaSys->SetFillStyle(1001);
  csRpaSys->SetLineWidth(0);
  TCanvas* c4 = new TCanvas("c4", "c4", 1000, 800);
  c4->SetLeftMargin(0.13);
  c4->SetTopMargin(0.07);
  c4->SetRightMargin(0.04);
  c4->SetBottomMargin(0.13);
  c4->DrawFrame(12, 0, 60, 2);
  csRpaSys->Draw("PE2");
  csRpaStat->Draw("PE1 Same");
  line->Draw("Same");
  csRpaStat->Fit("pol0", "", "", 12, 60);

  Double_t epps16_x[7] = {7.5, 17.7, 27.5, 37.5, 47.5, 57.5, 67.5};
  Double_t epps16_y[7] = {0.81126, 0.90616, 0.95391, 0.98635, 1, 1.01158, 1.01745};
  TGraph* EPPS16 = new TGraph(7, epps16_x, epps16_y);
  EPPS16->SetLineColor(kBlue);
  EPPS16->SetLineWidth(6);
  EPPS16->SetLineStyle(9);
  EPPS16->Draw("L same");
    
  TLegend* lRpA = new TLegend(0.13, 0.13, 0.8, 0.4);
  lRpA->SetFillStyle(0);
  lRpA->AddEntry(csRpaStat->GetFunction("pol0"), Form("Constant Fit: %f #pm %f", csRpaStat->GetFunction("pol0")->GetParameter(0), csRpaStat->GetFunction("pol0")->GetParError(0)), "l");
  lRpA->AddEntry((TObject*)0, Form("#chi^{2} = %f", csRpaStat->GetFunction("pol0")->GetChisquare()), "");
  lRpA->AddEntry((TObject*)0, Form("NDF = %i", csRpaStat->GetFunction("pol0")->GetNDF()), "");
  lRpA->AddEntry(EPPS16, "5.02 TeV, p-Pb-->direct photon", "l");
  lRpA->AddEntry((TObject*)0, "NLO pQCD parton model, PDFs: CT14, EPPS16", "");
  lRpA->Draw("same");
  
  TLegend* lRpA2 = new TLegend(0.1, 0.75, 0.8, 0.9);
  lRpA2->SetNColumns(2);
  lRpA2->SetFillStyle(0);
  lRpA2->AddEntry((TObject*)0, "ALICE pp & p-Pb #sqrt{s_{NN}} = 5.02 TeV", "");
  lRpA2->AddEntry((TObject*)0, "", "");
  lRpA2->AddEntry((TObject*)0, "isolated photons, |#eta| < 0.67", "");
  lRpA2->AddEntry(csRpaStat, "Data, stat. unc.","PL");
  lRpA2->AddEntry((TObject*)0, "R = 0.4, p^{iso}_{T} < 1.5 GeV/c", "");
  lRpA2->AddEntry(csRpaSys, "Data, sys. unc.","F");

  lRpA2->Draw("same");
  //c4->SaveAs("RpPb_pPbDhruvAndppDhruv_noSig.pdf");
  //c4->SaveAs("RpPb_pPbDhruvAndppDhruv_noSig.png");

  Double_t dhruvMean_EG1_ISO133[numBins] = {1592.85, 1063.32, 679.993, 433.643, 235.956, 108.42, 41.5594, 7.52093};//ISO < 1.33
  Double_t dhruvStat_EG1_ISO133[numBins] = {21.6448, 16.9511, 12.7847, 9.49749, 4.32282, 2.88542, 1.23046, 0.359855};//ISO < 1.33
  Double_t dhruvMean_EG2_ISO133[numBins] = {1615.29, 1054.07, 680.88, 444.575, 229.141, 101.95, 40.8996, 5.97812};//ISO < 1.33
  Double_t dhruvStat_EG2_ISO133[numBins] = {35.4401, 31.7416, 27.2299, 23.01, 10.9939, 7.6596, 3.43398, 0.923162};//ISO < 1.33
  Double_t dhruvMean_EG1_ISO15[numBins] = {1619.3, 1079.79, 692.178, 442.5, 238.985, 108.409, 41.5557, 7.4575};//fixed eff
  Double_t dhruvStat_EG1_ISO15[numBins] = {21.8978, 17.1048, 12.8975, 9.57457, 4.31995, 2.85161, 1.21363, 0.352928};//fixed eff
  Double_t dhruvMean_EG2_ISO15[numBins] = {1649.06, 1073.63, 702.1, 453.566, 229.664, 102.05, 42.5187, 6.07314};//fixed eff
  Double_t dhruvStat_EG2_ISO15[numBins] = {35.6368, 31.829, 27.4688, 23.074, 10.8907, 7.56413, 3.45221, 0.916306};//fixed eff*/
  Double_t diffISO_EG1[numBins] = {0};
  for(int i = 0; i < numBins; i++){
    double weightSum_ISO133 = dhruvStat_EG1_ISO133[i] + dhruvStat_EG2_ISO133[i];
    double diff_EG1 = TMath::Abs(dhruvMean_EG1_ISO133[i] - dhruvMean_EG1_ISO15[i]);
    double diffPercent_EG1 = diff_EG1*100.0/dhruvMean_EG1_ISO15[i];
    diffISO_EG1[i] = diffPercent_EG1;
  }
  TGraph* gDiffISO = new TGraphErrors(8, xBinCenters, diffISO_EG1);
  gDiffISO->SetTitle(";E_{T} [Ge];#frac{#sigma_{iso < 1.5} - #sigma_{iso < 1.33}}{#sigma_{iso < 1.5}}*100 [%]");
  gDiffISO->GetXaxis()->SetRangeUser(12,60);
  gDiffISO->GetYaxis()->SetRangeUser(0,5);
  gDiffISO->SetLineColor(kBlack);
  gDiffISO->SetMarkerStyle(20);
  gDiffISO->SetMarkerColor(kBlack);

  TCanvas* cDiffISO = new TCanvas("cDiffISO", "cDiffISO", 600, 600);
  gDiffISO->Draw("APL");//*/

  //TH1F*


}//end makeComparisons
