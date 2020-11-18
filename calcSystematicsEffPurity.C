#include <fstream>
#include <vector>
void calcSystematicsEffPurity(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);

  
  //Purity systematic
  TFile* file_StdPurity = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PurityFit.root","READ");
  TH1F* rpa_StdPurity = (TH1F*)file_StdPurity->Get("h_RpA");rpa_StdPurity->SetLineColor(kRed);rpa_StdPurity->SetMarkerColor(kRed);
  TH1F* hcsEG1_StdPurity = (TH1F*)file_StdPurity->Get("crossSection_pPb");hcsEG1_StdPurity->SetLineColor(kRed);hcsEG1_StdPurity->SetMarkerColor(kRed);
  TH1F* hcspp_StdPurity = (TH1F*)file_StdPurity->Get("crossSection_pp");hcspp_StdPurity->SetLineColor(kRed);hcspp_StdPurity->SetMarkerColor(kRed);

  TFile* file_SSC26 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PurityFitSSC26.root","READ");
  TH1F* rpa_SSC26 = (TH1F*)file_SSC26->Get("h_RpA");rpa_SSC26->SetLineColor(kMagenta);rpa_SSC26->SetMarkerColor(kMagenta);
  TH1F* hcsEG1_SSC26 = (TH1F*)file_SSC26->Get("crossSection_pPb");hcsEG1_SSC26->SetLineColor(kMagenta);hcsEG1_SSC26->SetMarkerColor(kMagenta);
  TH1F* hcspp_SSC26 = (TH1F*)file_SSC26->Get("crossSection_pp");hcspp_SSC26->SetLineColor(kMagenta);hcspp_SSC26->SetMarkerColor(kMagenta);

  TFile* file_SSC28 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PurityFitSSC28.root","READ");
  TH1F* rpa_SSC28 = (TH1F*)file_SSC28->Get("h_RpA");rpa_SSC28->SetLineColor(kBlue);rpa_SSC28->SetMarkerColor(kBlue);
  TH1F* hcsEG1_SSC28 = (TH1F*)file_SSC28->Get("crossSection_pPb");hcsEG1_SSC28->SetLineColor(kBlue);hcsEG1_SSC28->SetMarkerColor(kBlue);
  TH1F* hcspp_SSC28 = (TH1F*)file_SSC28->Get("crossSection_pp");hcspp_SSC28->SetLineColor(kBlue);hcspp_SSC28->SetMarkerColor(kBlue);

  TFile* file_SSC33 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PurityFitSSC33.root","READ");
  TH1F* rpa_SSC33 = (TH1F*)file_SSC33->Get("h_RpA");rpa_SSC33->SetLineColor(kCyan);rpa_SSC33->SetMarkerColor(kCyan);
  TH1F* hcsEG1_SSC33 = (TH1F*)file_SSC33->Get("crossSection_pPb");hcsEG1_SSC33->SetLineColor(kCyan);hcsEG1_SSC33->SetMarkerColor(kCyan);
  TH1F* hcspp_SSC33 = (TH1F*)file_SSC33->Get("crossSection_pp");hcspp_SSC33->SetLineColor(kCyan);hcspp_SSC33->SetMarkerColor(kCyan);
  
  TFile* file_SSC35 = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PurityFitSSC35.root","READ");
  TH1F* rpa_SSC35 = (TH1F*)file_SSC35->Get("h_RpA");rpa_SSC35->SetLineColor(kGreen);rpa_SSC35->SetMarkerColor(kGreen);
  TH1F* hcsEG1_SSC35 = (TH1F*)file_SSC35->Get("crossSection_pPb");hcsEG1_SSC35->SetLineColor(kGreen);hcsEG1_SSC35->SetMarkerColor(kGreen);
  TH1F* hcspp_SSC35 = (TH1F*)file_SSC35->Get("crossSection_pp");hcspp_SSC35->SetLineColor(kGreen);hcspp_SSC35->SetMarkerColor(kGreen);

  //RpA
  TLegend* lRpA_Purity = new TLegend(0.6,0.7,0.85,0.85);
  lRpA_Purity->SetHeader("R_{pPb}");
  lRpA_Purity->AddEntry(rpa_StdPurity, "SSC 0.3");
  lRpA_Purity->AddEntry(rpa_SSC26, "SSC 0.26");
  lRpA_Purity->AddEntry(rpa_SSC28, "SSC 0.28");
  lRpA_Purity->AddEntry(rpa_SSC33, "SSC 0.33");
  lRpA_Purity->AddEntry(rpa_SSC35, "SSC 0.35");  

  TCanvas* cRpA_Purity = new TCanvas();
  rpa_StdPurity->Draw("e1");
  rpa_SSC26->Draw("same e1");
  rpa_SSC28->Draw("same e1");
  rpa_SSC33->Draw("same e1");
  rpa_SSC35->Draw("same e1");
  line->Draw("same");
  lRpA_Purity->Draw("same");


  //HcsEG1
  TLegend* lHcsEG1_Purity = new TLegend(0.6,0.7,0.85,0.85);
  lHcsEG1_Purity->SetHeader("p-Pb EG1 cross section");
  lHcsEG1_Purity->AddEntry(hcsEG1_StdPurity, "SSC 0.3");
  lHcsEG1_Purity->AddEntry(hcsEG1_SSC26, "SSC 0.26");
  lHcsEG1_Purity->AddEntry(hcsEG1_SSC28, "SSC 0.28");
  lHcsEG1_Purity->AddEntry(hcsEG1_SSC33, "SSC 0.33");
  lHcsEG1_Purity->AddEntry(hcsEG1_SSC35, "SSC 0.35");

  TCanvas* cHcsEG1_Purity = new TCanvas();
  cHcsEG1_Purity->SetLogy();
  hcsEG1_StdPurity->GetXaxis()->SetRangeUser(12, 60);
  hcsEG1_StdPurity->GetYaxis()->SetRangeUser(1, 5e3);
  hcsEG1_StdPurity->Draw("e1");
  hcsEG1_SSC26->Draw("samee1");
  hcsEG1_SSC28->Draw("samee1");
  hcsEG1_SSC33->Draw("samee1");
  hcsEG1_SSC35->Draw("samee1");
  lHcsEG1_Purity->Draw("same");

  //Hcspp
  TLegend* lHcspp_Purity = new TLegend(0.6,0.7,0.85,0.85);
  lHcspp_Purity->SetHeader("pp cross section");
  lHcspp_Purity->AddEntry(hcspp_StdPurity, "SSC 0.3");
  lHcspp_Purity->AddEntry(hcspp_SSC26, "SSC 0.26");
  lHcspp_Purity->AddEntry(hcspp_SSC28, "SSC 0.28");
  lHcspp_Purity->AddEntry(hcspp_SSC33, "SSC 0.33");
  lHcspp_Purity->AddEntry(hcspp_SSC35, "SSC 0.35");

  TCanvas* cHcspp_Purity = new TCanvas();
  cHcspp_Purity->SetLogy();
  hcspp_StdPurity->GetXaxis()->SetRangeUser(12, 60);
  hcspp_StdPurity->Draw("e1");
  hcspp_SSC26->Draw("samee1");
  hcspp_SSC28->Draw("samee1");
  hcspp_SSC33->Draw("samee1");
  hcspp_SSC35->Draw("samee1");
  lHcspp_Purity->Draw("same");

  //difference
  //hcsEG1_SSC26->Add(hcsEG1_StdPurity, -1);
  //hcsEG1_SSC28->Add(hcsEG1_StdPurity, -1);
  //hcsEG1_SSC33->Add(hcsEG1_StdPurity, -1);
  //hcsEG1_SSC35->Add(hcsEG1_StdPurity, -1);
  //hcspp_StdPurity->Add(hcspp_StdPurity, -1);

  const int nbinsSSC = 5;
  Double_t xBins[nbinsSSC] = {0.26, 0.28, 0.30, 0.33, 0.35};
  Double_t xErr[nbinsSSC] = {0};
  Double_t yPt1_pp[nbinsSSC] = {hcspp_SSC26->GetBinContent(7), hcspp_SSC28->GetBinContent(7), hcspp_StdPurity->GetBinContent(7), hcspp_SSC33->GetBinContent(7), hcspp_SSC35->GetBinContent(7)};
  Double_t yPt1_ppErr[nbinsSSC] = {hcspp_SSC26->GetBinError(7), hcspp_SSC28->GetBinError(7), hcspp_StdPurity->GetBinError(7), hcspp_SSC33->GetBinError(7), hcspp_SSC35->GetBinError(7)};
  Double_t yPt2_pp[nbinsSSC] = {hcspp_SSC26->GetBinContent(8), hcspp_SSC28->GetBinContent(8), hcspp_StdPurity->GetBinContent(8), hcspp_SSC33->GetBinContent(8), hcspp_SSC35->GetBinContent(8)};
  Double_t yPt2_ppErr[nbinsSSC] = {hcspp_SSC26->GetBinError(8), hcspp_SSC28->GetBinError(8), hcspp_StdPurity->GetBinError(8), hcspp_SSC33->GetBinError(8), hcspp_SSC35->GetBinError(8)};
  Double_t yPt3_pp[nbinsSSC] = {hcspp_SSC26->GetBinContent(9), hcspp_SSC28->GetBinContent(9), hcspp_StdPurity->GetBinContent(9), hcspp_SSC33->GetBinContent(9), hcspp_SSC35->GetBinContent(9)};
  Double_t yPt3_ppErr[nbinsSSC] = {hcspp_SSC26->GetBinError(9), hcspp_SSC28->GetBinError(9), hcspp_StdPurity->GetBinError(9), hcspp_SSC33->GetBinError(9), hcspp_SSC35->GetBinError(9)};
  Double_t yPt4_pp[nbinsSSC] = {hcspp_SSC26->GetBinContent(10), hcspp_SSC28->GetBinContent(10), hcspp_StdPurity->GetBinContent(10), hcspp_SSC33->GetBinContent(10), hcspp_SSC35->GetBinContent(10)};
  Double_t yPt4_ppErr[nbinsSSC] = {hcspp_SSC26->GetBinError(10), hcspp_SSC28->GetBinError(10), hcspp_StdPurity->GetBinError(10), hcspp_SSC33->GetBinError(10), hcspp_SSC35->GetBinError(10)};
  Double_t yPt5_pp[nbinsSSC] = {hcspp_SSC26->GetBinContent(11), hcspp_SSC28->GetBinContent(11), hcspp_StdPurity->GetBinContent(11), hcspp_SSC33->GetBinContent(11), hcspp_SSC35->GetBinContent(11)};
  Double_t yPt5_ppErr[nbinsSSC] = {hcspp_SSC26->GetBinError(11), hcspp_SSC28->GetBinError(11), hcspp_StdPurity->GetBinError(11), hcspp_SSC33->GetBinError(11), hcspp_SSC35->GetBinError(11)};
  Double_t yPt6_pp[nbinsSSC] = {hcspp_SSC26->GetBinContent(12), hcspp_SSC28->GetBinContent(12), hcspp_StdPurity->GetBinContent(12), hcspp_SSC33->GetBinContent(12), hcspp_SSC35->GetBinContent(12)};
  Double_t yPt6_ppErr[nbinsSSC] = {hcspp_SSC26->GetBinError(12), hcspp_SSC28->GetBinError(12), hcspp_StdPurity->GetBinError(12), hcspp_SSC33->GetBinError(12), hcspp_SSC35->GetBinError(12)};
  Double_t yPt7_pp[nbinsSSC] = {hcspp_SSC26->GetBinContent(13), hcspp_SSC28->GetBinContent(13), hcspp_StdPurity->GetBinContent(13), hcspp_SSC33->GetBinContent(13), hcspp_SSC35->GetBinContent(13)};
  Double_t yPt7_ppErr[nbinsSSC] = {hcspp_SSC26->GetBinError(13), hcspp_SSC28->GetBinError(13), hcspp_StdPurity->GetBinError(13), hcspp_SSC33->GetBinError(13), hcspp_SSC35->GetBinError(13)};
  Double_t yPt8_pp[nbinsSSC] = {hcspp_SSC26->GetBinContent(14), hcspp_SSC28->GetBinContent(14), hcspp_StdPurity->GetBinContent(14), hcspp_SSC33->GetBinContent(14), hcspp_SSC35->GetBinContent(14)};
  Double_t yPt8_ppErr[nbinsSSC] = {hcspp_SSC26->GetBinError(14), hcspp_SSC28->GetBinError(14), hcspp_StdPurity->GetBinError(14), hcspp_SSC33->GetBinError(14), hcspp_SSC35->GetBinError(14)};//*/
  
  
  TGraphErrors* gPt1_pp = new TGraphErrors(nbinsSSC, xBins, yPt1_pp, xErr, yPt1_ppErr); gPt1_pp->SetLineColor(kRed); gPt1_pp->SetMarkerStyle(kOpenCircle); gPt1_pp->SetMarkerColor(kRed); gPt1_pp->SetTitle("12 GeV/c < p_{T} < 14 GeV/c; SSC ; #frac{d^{2}#sigma}{dE_{T}d#eta}");
  TGraphErrors* gPt2_pp = new TGraphErrors(nbinsSSC, xBins, yPt2_pp, xErr, yPt2_ppErr); gPt2_pp->SetLineColor(kRed); gPt2_pp->SetMarkerStyle(kOpenCircle); gPt2_pp->SetMarkerColor(kRed); gPt2_pp->SetTitle("14 GeV/c < p_{T} < 16 GeV/c; SSC ; #frac{d^{2}#sigma}{dE_{T}d#eta}");
  TGraphErrors* gPt3_pp = new TGraphErrors(nbinsSSC, xBins, yPt3_pp, xErr, yPt3_ppErr); gPt3_pp->SetLineColor(kRed); gPt3_pp->SetMarkerStyle(kOpenCircle); gPt3_pp->SetMarkerColor(kRed); gPt3_pp->SetTitle("16 GeV/c < p_{T} < 18 GeV/c; SSC ; #frac{d^{2}#sigma}{dE_{T}d#eta}");
  TGraphErrors* gPt4_pp = new TGraphErrors(nbinsSSC, xBins, yPt4_pp, xErr, yPt4_ppErr); gPt4_pp->SetLineColor(kRed); gPt4_pp->SetMarkerStyle(kOpenCircle); gPt4_pp->SetMarkerColor(kRed); gPt4_pp->SetTitle("18 GeV/c < p_{T} < 20 GeV/c; SSC ; #frac{d^{2}#sigma}{dE_{T}d#eta}");
  TGraphErrors* gPt5_pp = new TGraphErrors(nbinsSSC, xBins, yPt5_pp, xErr, yPt5_ppErr); gPt5_pp->SetLineColor(kRed); gPt5_pp->SetMarkerStyle(kOpenCircle); gPt5_pp->SetMarkerColor(kRed); gPt5_pp->SetTitle("20 GeV/c < p_{T} < 25 GeV/c; SSC ; #frac{d^{2}#sigma}{dE_{T}d#eta}");
  TGraphErrors* gPt6_pp = new TGraphErrors(nbinsSSC, xBins, yPt6_pp, xErr, yPt6_ppErr); gPt6_pp->SetLineColor(kRed); gPt6_pp->SetMarkerStyle(kOpenCircle); gPt6_pp->SetMarkerColor(kRed); gPt6_pp->SetTitle("25 GeV/c < p_{T} < 30 GeV/c; SSC ; #frac{d^{2}#sigma}{dE_{T}d#eta}");
  TGraphErrors* gPt7_pp = new TGraphErrors(nbinsSSC, xBins, yPt7_pp, xErr, yPt7_ppErr); gPt7_pp->SetLineColor(kRed); gPt7_pp->SetMarkerStyle(kOpenCircle); gPt7_pp->SetMarkerColor(kRed); gPt7_pp->SetTitle("30 GeV/c < p_{T} < 40 GeV/c; SSC ; #frac{d^{2}#sigma}{dE_{T}d#eta}");
  TGraphErrors* gPt8_pp = new TGraphErrors(nbinsSSC, xBins, yPt8_pp, xErr, yPt8_ppErr); gPt8_pp->SetLineColor(kRed); gPt8_pp->SetMarkerStyle(kOpenCircle); gPt8_pp->SetMarkerColor(kRed); gPt8_pp->SetTitle("40 GeV/c < p_{T} < 60 GeV/c; SSC ; #frac{d^{2}#sigma}{dE_{T}d#eta}");

  Double_t aPt1_pp[5] = {9.98169, 9.98169, 9.98169, 9.98169, 9.98169};
  Double_t ePt1_pp[5] = {0.309172, 0.309172, 0.309172, 0.309172, 0.309172};
  Double_t aPt2_pp[5] = {6.62624, 6.62624, 6.62624, 6.62624, 6.62624};
  Double_t ePt2_pp[5] = {0.0947462, 0.0947462, 0.0947462, 0.0947462, 0.0947462};
  Double_t aPt3_pp[5] = {4.09855, 4.09855, 4.09855, 4.09855, 4.09855};
  Double_t ePt3_pp[5] = {0.0774654, 0.0774654, 0.0774654, 0.0774654, 0.0774654};
  Double_t aPt4_pp[5] = {2.44442, 2.44442, 2.44442, 2.44442, 2.44442};
  Double_t ePt4_pp[5] = {0.0482269, 0.0482269, 0.0482269, 0.0482269, 0.0482269};
  Double_t aPt5_pp[5] = {1.30628, 1.30628, 1.30628, 1.30628, 1.30628};
  Double_t ePt5_pp[5] = {0.0306748, 0.0306748, 0.0306748, 0.0306748, 0.0306748};
  Double_t aPt6_pp[5] = {0.540055, 0.540055, 0.540055, 0.540055, 0.540055};
  Double_t ePt6_pp[5] = {0.0345691, 0.0345691, 0.0345691, 0.0345691, 0.0345691};
  Double_t aPt7_pp[5] = {0.189955, 0.189955, 0.189955, 0.189955, 0.189955};
  Double_t ePt7_pp[5] = {0.00637156, 0.00637156, 0.00637156, 0.00637156, 0.00637156};
  Double_t aPt8_pp[5] = {0.0415352, 0.0415352, 0.0415352, 0.0415352, 0.0415352};
  Double_t ePt8_pp[5] = {0.00134366, 0.00134366, 0.00134366, 0.00134366, 0.00134366};

  TGraphErrors* bandPt1_pp = new TGraphErrors(nbinsSSC, xBins, aPt1_pp, xErr, ePt1_pp); bandPt1_pp->SetFillColor(kYellow); bandPt1_pp->SetFillStyle(3004);
  TGraphErrors* bandPt2_pp = new TGraphErrors(nbinsSSC, xBins, aPt2_pp, xErr, ePt2_pp); bandPt2_pp->SetFillColor(kYellow); bandPt2_pp->SetFillStyle(3004);
  TGraphErrors* bandPt3_pp = new TGraphErrors(nbinsSSC, xBins, aPt3_pp, xErr, ePt3_pp); bandPt3_pp->SetFillColor(kYellow); bandPt3_pp->SetFillStyle(3004);
  TGraphErrors* bandPt4_pp = new TGraphErrors(nbinsSSC, xBins, aPt4_pp, xErr, ePt4_pp); bandPt4_pp->SetFillColor(kYellow); bandPt4_pp->SetFillStyle(3004);
  TGraphErrors* bandPt5_pp = new TGraphErrors(nbinsSSC, xBins, aPt5_pp, xErr, ePt5_pp); bandPt5_pp->SetFillColor(kYellow); bandPt5_pp->SetFillStyle(3004);
  TGraphErrors* bandPt6_pp = new TGraphErrors(nbinsSSC, xBins, aPt6_pp, xErr, ePt6_pp); bandPt6_pp->SetFillColor(kYellow); bandPt6_pp->SetFillStyle(3004);
  TGraphErrors* bandPt7_pp = new TGraphErrors(nbinsSSC, xBins, aPt7_pp, xErr, ePt7_pp); bandPt7_pp->SetFillColor(kYellow); bandPt7_pp->SetFillStyle(3004);
  TGraphErrors* bandPt8_pp = new TGraphErrors(nbinsSSC, xBins, aPt8_pp, xErr, ePt8_pp); bandPt8_pp->SetFillColor(kYellow); bandPt8_pp->SetFillStyle(3004);
  TCanvas* cSSCPtBins = new TCanvas("cSSCPtBins", "cSSCPtBins", 1600, 800);
  cSSCPtBins->Divide(4,2);
  cSSCPtBins->cd(1);
  gPt1_pp->Draw("AP");
  bandPt1_pp->Draw("E3Lsame");
  cSSCPtBins->cd(2);
  gPt2_pp->Draw("AP");
  bandPt2_pp->Draw("E3Lsame");
  cSSCPtBins->cd(3);
  gPt3_pp->Draw("AP");
  bandPt3_pp->Draw("E3Lsame");
  cSSCPtBins->cd(4);
  gPt4_pp->Draw("AP");
  bandPt4_pp->Draw("E3Lsame");
  cSSCPtBins->cd(5);
  gPt5_pp->Draw("AP");
  bandPt5_pp->Draw("E3Lsame");
  cSSCPtBins->cd(6);
  gPt6_pp->Draw("AP");
  bandPt6_pp->Draw("E3Lsame");
  cSSCPtBins->cd(7);
  gPt7_pp->Draw("AP");
  bandPt7_pp->Draw("E3Lsame");
  cSSCPtBins->cd(8);
  gPt8_pp->Draw("AP");
  bandPt8_pp->Draw("E3Lsame");


  TH1F* crossSection12GeVBin = new TH1F("crossSection12GeVBin", "", 20, 9, 11);
  crossSection12GeVBin->SetTitle("12 < p_{T} < 14; #frac{d^{2}#sigma}{dE_{T}d#eta}; counts");
  crossSection12GeVBin->Fill(10.0283);
  crossSection12GeVBin->Fill(10.0051);
  crossSection12GeVBin->Fill(9.40155);
  crossSection12GeVBin->Fill(10.1714);
  crossSection12GeVBin->Fill(10.3021);
  cout << "12-14 GeV: " << crossSection12GeVBin->GetMean(1) << "+/-" << crossSection12GeVBin->GetStdDev(1) << "\t" << crossSection12GeVBin->GetStdDev(1)/crossSection12GeVBin->GetMean(1) << endl;//*/
  
  TH1F* crossSection14GeVBin = new TH1F("crossSection14GeVBin", "", 10, 6, 7);
  crossSection14GeVBin->SetTitle("14 < p_{T} < 16; #frac{d^{2}#sigma}{dE_{T}d#eta}; counts");
  crossSection14GeVBin->Fill(6.76661);
  crossSection14GeVBin->Fill(6.70739);
  crossSection14GeVBin->Fill(6.53446);
  crossSection14GeVBin->Fill(6.59098);
  crossSection14GeVBin->Fill(6.53175);
  cout << "14-16 GeV: " << crossSection14GeVBin->GetMean(1) << "+/-" << crossSection14GeVBin->GetStdDev(1) << "\t" << crossSection14GeVBin->GetStdDev(1)/crossSection14GeVBin->GetMean(1) << endl;
  TH1F* crossSection16GeVBin = new TH1F("crossSection16GeVBin", "", 10, 4, 5);
  crossSection16GeVBin->SetTitle("16 < p_{T} < 18; #frac{d^{2}#sigma}{dE_{T}d#eta}; counts");
  crossSection16GeVBin->Fill(4.24941);
  crossSection16GeVBin->Fill(4.04921);
  crossSection16GeVBin->Fill(4.06307);
  crossSection16GeVBin->Fill(4.09172);
  crossSection16GeVBin->Fill(4.03934);
  cout << "16-18 GeV: " << crossSection16GeVBin->GetMean(1) << "+/-" << crossSection16GeVBin->GetStdDev(1) << "\t" << crossSection16GeVBin->GetStdDev(1)/crossSection16GeVBin->GetMean(1) << endl;
  TH1F* crossSection18GeVBin = new TH1F("crossSection18GeVBin", "", 10, 2, 3);
  crossSection18GeVBin->SetTitle("18 < p_{T} < 20; #frac{d^{2}#sigma}{dE_{T}d#eta}; counts");
  crossSection18GeVBin->Fill(2.41852);
  crossSection18GeVBin->Fill(2.37147);
  crossSection18GeVBin->Fill(2.43759);
  crossSection18GeVBin->Fill(2.4959);
  crossSection18GeVBin->Fill(2.49864);
  cout << "18-20 GeV: " << crossSection18GeVBin->GetMean(1) << "+/-" << crossSection18GeVBin->GetStdDev(1) << "\t" << crossSection18GeVBin->GetStdDev(1)/crossSection18GeVBin->GetMean(1) << endl;
  TH1F* crossSection20GeVBin = new TH1F("crossSection20GeVBin", "", 10, 1, 2);
  crossSection20GeVBin->SetTitle("20 < p_{T} < 25; #frac{d^{2}#sigma}{dE_{T}d#eta}; counts");
  crossSection20GeVBin->Fill(1.28306);
  crossSection20GeVBin->Fill(1.26614);
  crossSection20GeVBin->Fill(1.31679);
  crossSection20GeVBin->Fill(1.3098);
  crossSection20GeVBin->Fill(1.35559);
  cout << "20-25 GeV: " << crossSection20GeVBin->GetMean(1) << "+/-" << crossSection20GeVBin->GetStdDev(1) << "\t" << crossSection20GeVBin->GetStdDev(1)/crossSection20GeVBin->GetMean(1) << endl;
  TH1F* crossSection25GeVBin = new TH1F("crossSection25GeVBin", "", 10, 0, 1);
  crossSection25GeVBin->SetTitle("25 < p_{T} < 30; #frac{d^{2}#sigma}{dE_{T}d#eta}; counts");
  crossSection25GeVBin->Fill(0.498572);
  crossSection25GeVBin->Fill(0.516717);
  crossSection25GeVBin->Fill(0.531757);
  crossSection25GeVBin->Fill(0.554622);
  crossSection25GeVBin->Fill(0.598609);
  cout << "25-30 GeV: " << crossSection25GeVBin->GetMean(1) << "+/-" << crossSection25GeVBin->GetStdDev(1) << "\t" << crossSection25GeVBin->GetStdDev(1)/crossSection25GeVBin->GetMean(1) << endl;
  TH1F* crossSection30GeVBin = new TH1F("crossSection30GeVBin", "", 10, 0, 1);
  crossSection30GeVBin->SetTitle("30 < p_{T} < 40; #frac{d^{2}#sigma}{dE_{T}d#eta}; counts");
  crossSection30GeVBin->Fill(0.195436);
  crossSection30GeVBin->Fill(0.197523);
  crossSection30GeVBin->Fill(0.190827);
  crossSection30GeVBin->Fill(0.179993);
  crossSection30GeVBin->Fill(0.185997);
  cout << "30-40 GeV: " << crossSection30GeVBin->GetMean(1) << "+/-" << crossSection30GeVBin->GetStdDev(1) << "\t" << crossSection30GeVBin->GetStdDev(1)/crossSection30GeVBin->GetMean(1) << endl;
  TH1F* crossSection40GeVBin = new TH1F("crossSection40GeVBin", "", 10, 0., 0.1);
  crossSection40GeVBin->SetTitle("40 < p_{T} < 60; #frac{d^{2}#sigma}{dE_{T}d#eta}; counts");
  crossSection40GeVBin->Fill(0.0434703);
  crossSection40GeVBin->Fill(0.0418159);
  crossSection40GeVBin->Fill(0.0409821);
  crossSection40GeVBin->Fill(0.0420295);
  crossSection40GeVBin->Fill(0.039378);
  cout << "40-60 GeV: " << crossSection40GeVBin->GetMean(1) << "+/-" << crossSection40GeVBin->GetStdDev(1) << "\t" << crossSection40GeVBin->GetStdDev(1)/crossSection40GeVBin->GetMean(1) << endl;

  TCanvas* c5 = new TCanvas("c5", "c5", 1600, 800);
  c5->Divide(4,2);
  c5->cd(1);
  crossSection12GeVBin->Draw();
  c5->cd(2);
  crossSection14GeVBin->Draw();
  c5->cd(3);
  crossSection16GeVBin->Draw();
  c5->cd(4);
  crossSection18GeVBin->Draw();
  c5->cd(5);
  crossSection20GeVBin->Draw();
  
  for(int i = 7; i < hcspp_StdPurity->GetNbinsX()+1; i++){
    cout
      << hcspp_StdPurity->GetBinLowEdge(i) << "< E_{T} < "
      << hcspp_StdPurity->GetBinLowEdge(i+1) << "\t" 
      << hcspp_SSC26->GetBinContent(i) << ", "
      << hcspp_SSC28->GetBinContent(i) << ", "
      << hcspp_StdPurity->GetBinContent(i) << ", "
      << hcspp_SSC33->GetBinContent(i) << ", "
      << hcspp_SSC35->GetBinContent(i) << endl;//
      }//*/
}//end makeComparisons
