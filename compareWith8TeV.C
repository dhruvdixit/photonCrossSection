#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <bits/stdc++.h>
#include <cstring>

void compareWith8TeV(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/";
  //TFile* file_8pPb = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/8TeVResults/pPb/simpleOutput_pPb8TeV_EMC.root"), "READ");
  TFile* file_8pPb = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/8TeVResults/pPbNew/simpleOutput_pPbEMC.root"), "READ");

  const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14
  //Double_t clusterbins[nbinscluster+1] = {12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 8

  //8.16 TeV hists
  //EG1 - threshold 8 GeV
  TH1F* rawYields_EG1 = (TH1F*)file_8pPb->Get("rawYields_EG1");//600, 0-150
  TH1F* totalEfficiency_EG1 = (TH1F*)file_8pPb->Get("totalEfficiency_EG1");
  TH1F* purityABCD_EG1 = (TH1F*)file_8pPb->Get("purityABCD_EG1");
  TH1F* rejectionFactor_EG1 = (TH1F*)file_8pPb->Get("rejectionFactor_EG1");
  TH1F* acceptedEvents_EG1 = (TH1F*)file_8pPb->Get("acceptedEvents_EG1");
  //TH1F* 
  TH1F* hEG1_8TeVRaw = new TH1F("hEG1_8TeVRaw", "", nbinscluster, clusterbins);
  TH1F* hEG1_8TeVNorm = new TH1F("hEG1_8TeVPurity", ";E_{T} (GeV);#frac{1}{N_{eve}}#frac{d^{2}N}{dp_{T}d#eta}", nbinscluster, clusterbins);
  TH1F* hEG1_8TeVPurity = new TH1F("hEG1_8TeVPurityEff", ";E_{T} (GeV);#frac{P}{N_{eve}}#frac{d^{2}N}{dp_{T}d#eta}", nbinscluster, clusterbins);
  TH1F* hEG1_8TeVPurityEff = new TH1F("hEG1_8TeVNorm", ";E_{T} (GeV);#frac{P}{#epsilon*N_{eve}}#frac{d^{2}N}{dp_{T}d#eta}", nbinscluster, clusterbins);
  TH1F* hEG1_8TeVCS = new TH1F("hEG1_8TeVCS", ";E_{T} (GeV); #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]", nbinscluster, clusterbins);

  hEG1_8TeVRaw->Sumw2();
  hEG1_8TeVNorm->Sumw2();
  hEG1_8TeVPurity->Sumw2();
  hEG1_8TeVPurityEff->Sumw2();
  hEG1_8TeVCS->Sumw2();
  
  //5.02 TeV hists
  TFile* file_5pPb = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PurityFit_nonLinPurity_correctRFpPb_woPurityHists.root"), "READ");
  TH1F* hEff_5TeV = (TH1F*)file_5pPb->Get("hEff_pPb");
  TH1F* hEG1_5TeVNorm = (TH1F*)file_5pPb->Get("hClusterSpectrawoPurity_EG1");
  TH1F* hEG2_5TeVNorm = (TH1F*)file_5pPb->Get("hClusterSpectrawoPurity_EG2");
  TH1F* hEG1_5TeVPurity = (TH1F*)file_5pPb->Get("hClusterSpectra_EG1");
  TH1F* hEG2_5TeVPurity = (TH1F*)file_5pPb->Get("hClusterSpectra_EG2");
  TH1F* hEG1_5TeVPurityEff = new TH1F("hEG1_5TeVPurityEff", ";E_{T} (GeV);#frac{P}{#epsilon*N_{eve}}#frac{d^{2}N}{dp_{T}d#eta}", nbinscluster, clusterbins);
  TH1F* hEG1_5TeVCS = (TH1F*)file_5pPb->Get("crossSection_EG1");
  TH1F* hEG2_5TeVCS = (TH1F*)file_5pPb->Get("crossSection_EG2");
  TH1F* hEGA_5TeVCS = (TH1F*)file_5pPb->Get("crossSection_pPb");
  
  TH1F* hEG1_RatioNorm = new TH1F("hEG1_RatioNorm", "Photon Yield Ratio;E_{T} (GeV); #frac{8.16 TeV}{5.02 TeV}", nbinscluster, clusterbins);
  TH1F* hEG1_RatioPurity = new TH1F("hEG1_RatioPurity", "Photon Yield * Purity Ratio;E_{T} (GeV); #frac{8.16 TeV}{5.02 TeV}", nbinscluster, clusterbins);
  TH1F* hEG1_RatioPurityEff = new TH1F("hEG1_RatioPurityEff", "Photon Yield *Purity/Eff Ratio;E_{T} (GeV); #frac{8.16 TeV}{5.02 TeV}", nbinscluster, clusterbins);
  TH1F* hEG1_RatioCS = new TH1F("hEG1_RatioCS", "Photon Cross Section Ratio;E_{T} (GeV); #frac{8.16 TeV}{5.02 TeV}", nbinscluster, clusterbins);

  TH1F* hEG2_RatioNorm = new TH1F("hEG2_RatioNorm", "Photon Yield Ratio;E_{T} (GeV); #frac{8.16 TeV}{5.02 TeV}", nbinscluster, clusterbins);
  TH1F* hEG2_RatioCS = new TH1F("hEG2_RatioCS", "Photon Cross Section Ratio;E_{T} (GeV); #frac{8.16 TeV}{5.02 TeV}", nbinscluster, clusterbins);
    
  //Scalars -- event counts, rejector factors, acceptance norm
  Double_t numEventsEG1_8TeV = acceptedEvents_EG1->GetBinContent(1);
  Double_t rfEG1_8TeV = 1557.7341; //Correct RF
  Double_t rfEG1_8TeVErr = 267.3426;
  //Double_t rfEG1_8TeV = rejectionFactor_EG1->GetBinContent(1); //Wrong RF
  //Double_t rfEG1_8TeVErr = rejectionFactor_EG1->GetBinError(1); //Wrong RF
  Double_t refCS_8TeV = 2.09;//in barns
  Double_t refCS_8TeVErr = 0.04;
  Double_t lumi_EG1 = ((rfEG1_8TeV*numEventsEG1_8TeV)/refCS_8TeV)*1.00E-09;//in nb
  Double_t lumiErr_EG1 = lumi_EG1*TMath::Sqrt(TMath::Power(refCS_8TeVErr/refCS_8TeV,2) + TMath::Power(rfEG1_8TeVErr/rfEG1_8TeV,2));
  const double deltaEta = 1.334;
  const double deltaPhi = 1.884-0.12;
  double acceptanceNorm = 2*TMath::Pi()/(deltaEta*deltaPhi);
  
  cout << "EG1 rejection factor: " << rfEG1_8TeV << "+/-" << rfEG1_8TeVErr << endl;
  cout << "Refernece CS: " << refCS_8TeV << "+/-" << refCS_8TeVErr << endl;
  cout << "EG1 luminosity: " << lumi_EG1 << "+/-" << lumiErr_EG1 <<endl;
  cout << "EG1 num events: " << numEventsEG1_8TeV << endl;
  
  //Changing the binning for the raw yields
  //EG1
  for(int i = 1; i < rawYields_EG1->GetNbinsX()+1; i++){
    Double_t clusterpt = rawYields_EG1->GetXaxis()->GetBinCenter(i);
    Double_t weight = rawYields_EG1->GetBinContent(i);
    hEG1_8TeVRaw->Fill(clusterpt, weight);
  }
  
  cout << "rebined raw yields" << endl;
  
  //raw yields --> normalized yields and ratio
  //EG1
  for(int i = 1; i < hEG1_8TeVRaw->GetNbinsX()+1; i++){
    cout << hEG1_8TeVRaw->GetBinLowEdge(i+6) << "\t" << purityABCD_EG1->GetBinLowEdge(i+1) <<  endl;
    
    double dE = hEG1_8TeVRaw->GetBinWidth(i+6);
    
    //Raw Normalized Yields
    double content8TeV = hEG1_8TeVRaw->GetBinContent(i+6);
    double temp8TeV = (content8TeV*acceptanceNorm)/((double)numEventsEG1_8TeV*dE);
    double error8TeV = hEG1_8TeVRaw->GetBinError(i+6);
    double tempErr8TeV = (error8TeV*acceptanceNorm)/((double)numEventsEG1_8TeV*dE);
    hEG1_8TeVNorm->SetBinContent(i+6,temp8TeV);
    hEG1_8TeVNorm->SetBinError(i+6, tempErr8TeV);
    //cout << temp8TeV << "\t" << content5TeV << "\t" << ratiopPb << endl;
    Double_t content5TeV = hEG1_5TeVNorm->GetBinContent(i+6);
    Double_t error5TeV = hEG1_5TeVNorm->GetBinError(i+6);
    Double_t ratiopPb = temp8TeV/content5TeV;
    Double_t errorRatiopPb = ratiopPb*(TMath::Sqrt(TMath::Power(tempErr8TeV/temp8TeV,2)+TMath::Power(error5TeV/content5TeV,2)));
    hEG1_RatioNorm->SetBinContent(i+6, ratiopPb);
    hEG1_RatioNorm->SetBinError(i+6, errorRatiopPb);

    //Purity Corrected Yields
    Double_t purity = purityABCD_EG1->GetBinContent(i+1);
    Double_t purityErr = purityABCD_EG1->GetBinError(i+1);
    Double_t purityCorr = temp8TeV*purity;
    Double_t purityCorrErr = purityCorr*(TMath::Sqrt(TMath::Power(tempErr8TeV/temp8TeV, 2) + TMath::Power(purityErr/purity, 2)));
    hEG1_8TeVPurity->SetBinContent(i+6,purityCorr);
    hEG1_8TeVPurity->SetBinError(i+6, purityCorrErr);
    Double_t purityCorr5TeV = hEG1_5TeVPurity->GetBinContent(i+6);
    Double_t purityCorrErr5TeV = hEG1_5TeVPurity->GetBinError(i+6);
    Double_t purityRatio = purityCorr/purityCorr5TeV;
    Double_t purityRatioErr = purityRatio*(TMath::Sqrt(TMath::Power(purityCorrErr/purityCorr,2)+TMath::Power(purityCorrErr5TeV/purityCorr5TeV,2)));
    hEG1_RatioPurity->SetBinContent(i+6, purityRatio);
    hEG1_RatioPurity->SetBinError(i+6, purityRatioErr);

    
    //Purity and Efficiency Corrected Yields
    Double_t eff = totalEfficiency_EG1->GetBinContent(i+1);
    Double_t effErr = totalEfficiency_EG1->GetBinError(i+1);
    Double_t purityEffCorr = purityCorr/eff;
    Double_t purityEffCorrErr = purityEffCorr*(TMath::Sqrt(TMath::Power(purityCorrErr/purityCorr, 2) + TMath::Power(effErr/eff, 2)));
    hEG1_8TeVPurityEff->SetBinContent(i+6,purityEffCorr);
    hEG1_8TeVPurityEff->SetBinError(i+6, purityEffCorrErr);
    Double_t eff5TeV = hEff_5TeV->GetBinContent(i+6);
    Double_t effErr5TeV = hEff_5TeV->GetBinError(i+6);
    Double_t purityEffCorr5TeV = purityCorr5TeV/eff5TeV;
    Double_t purityEffCorrErr5TeV = purityEffCorr5TeV*(TMath::Sqrt(TMath::Power(purityCorrErr5TeV/purityCorr5TeV, 2) + TMath::Power(effErr5TeV/eff5TeV, 2)));
    hEG1_5TeVPurityEff->SetBinContent(i+6,purityEffCorr5TeV);
    hEG1_5TeVPurityEff->SetBinError(i+6, purityEffCorrErr5TeV);
    Double_t purityEffRatio = purityEffCorr/purityEffCorr5TeV;
    Double_t purityEffRatioErr = purityEffRatio*(TMath::Sqrt(TMath::Power(purityEffCorrErr/purityEffCorr,2)+TMath::Power(purityEffCorrErr5TeV/purityEffCorr5TeV,2)));
    hEG1_RatioPurityEff->SetBinContent(i+6, purityEffRatio);
    hEG1_RatioPurityEff->SetBinError(i+6, purityEffRatioErr);
    
    //Cross section (including the luminosity)
    Double_t cs8TeV = purityEffCorr*numEventsEG1_8TeV/lumi_EG1;
    Double_t csErr8TeV = cs8TeV*(TMath::Sqrt(TMath::Power(purityEffCorrErr/purityEffCorr,2)+TMath::Power(lumiErr_EG1/lumi_EG1,2)));
    hEG1_8TeVCS->SetBinContent(i+6, cs8TeV);
    hEG1_8TeVCS->SetBinError(i+6, csErr8TeV);
    Double_t cs5TeV = (hEG1_5TeVCS->GetBinContent(i+6));
    Double_t csErr5TeV = (hEG1_5TeVCS->GetBinError(i+6));
    Double_t csRatio = cs8TeV/cs5TeV;
    Double_t csRatioErr = csRatio*(TMath::Sqrt(TMath::Power(csErr8TeV/cs8TeV,2) + TMath::Power(csErr5TeV/cs5TeV,2)));
    hEG1_RatioCS->SetBinContent(i+6, csRatio);
    hEG1_RatioCS->SetBinError(i+6, csRatioErr);

  }

  //Normazlied
  hEG1_8TeVNorm->SetLineColor(kBlue);
  hEG1_8TeVNorm->SetMarkerColor(kBlue);
  hEG1_8TeVNorm->SetMarkerStyle(kFullCircle);
  hEG1_8TeVNorm->SetMarkerSize(2);
  hEG1_5TeVNorm->SetLineColor(kGreen);
  hEG1_5TeVNorm->SetMarkerColor(kGreen);
  hEG1_5TeVNorm->SetMarkerStyle(kFullCircle);
  hEG1_5TeVNorm->SetMarkerSize(2);
  hEG1_RatioNorm->SetLineColor(kBlack);
  hEG1_RatioNorm->SetMarkerColor(kBlack);
  hEG1_RatioNorm->SetMarkerStyle(kFullCircle);
  hEG1_RatioNorm->SetMarkerSize(2);
  TLegend* legNorm_EG1 = new TLegend(0.6,0.7,0.85,0.85);
  legNorm_EG1->SetHeader("Photon Yield EG1 Trigger");
  legNorm_EG1->AddEntry(hEG1_8TeVNorm,"8.16 TeV");
  legNorm_EG1->AddEntry(hEG1_5TeVNorm,"5.02 TeV");
  TCanvas* cNorm_EG1 = new TCanvas("cNorm_EG1", "cNorm_EG1");
  cNorm_EG1->SetLogy();
  hEG1_8TeVNorm->GetXaxis()->SetRangeUser(12, 60);
  hEG1_8TeVNorm->GetYaxis()->SetRangeUser(5e-7, 0.1);
  hEG1_8TeVNorm->Draw("e1");
  hEG1_5TeVNorm->Draw("same e1");
  legNorm_EG1->Draw("same");
  TCanvas* cRatioNorm = new TCanvas("cRatioNorm", "cRatioNorm");
  hEG1_RatioNorm->GetXaxis()->SetRangeUser(12, 60);
  hEG1_RatioNorm->GetYaxis()->SetRangeUser(0, 1);
  hEG1_RatioNorm->Draw("e1");
  cout << "Normlized Yield Ratio Fit" << endl;
  hEG1_RatioNorm->Fit("pol0", "", "", 12, 60);
  TF1* fEG1_RatioNorm = (TF1*)hEG1_RatioNorm->GetFunction("pol0");
  fEG1_RatioNorm->SetName("fEG1_RatioNorm");
  double parEG1_RatioNorm  = fEG1_RatioNorm->GetParameter(0);
  double parErrEG1_RatioNorm = fEG1_RatioNorm->GetParError(0);
  TLegend* legRatioNorm = new TLegend(0.2,0.7,0.85,0.85);
  legRatioNorm->SetHeader("Photon Yield Ratio");
  legRatioNorm->AddEntry(hEG1_RatioNorm,"EG1 Trigger");
  legRatioNorm->AddEntry(fEG1_RatioNorm, Form("Constant Fit (12, 60) GeV = %.2f #pm %.2f", parEG1_RatioNorm, parErrEG1_RatioNorm));  
  legRatioNorm->Draw("same");

  
  //Normazlied+Purity
  hEG1_8TeVPurity->SetLineColor(kBlue);
  hEG1_8TeVPurity->SetMarkerColor(kBlue);
  hEG1_8TeVPurity->SetMarkerStyle(kFullCircle);
  hEG1_8TeVPurity->SetMarkerSize(2);
  hEG1_5TeVPurity->SetLineColor(kGreen);
  hEG1_5TeVPurity->SetMarkerColor(kGreen);
  hEG1_5TeVPurity->SetMarkerStyle(kFullCircle);
  hEG1_5TeVPurity->SetMarkerSize(2);
  hEG1_RatioPurity->SetLineColor(kBlack);
  hEG1_RatioPurity->SetMarkerColor(kBlack);
  hEG1_RatioPurity->SetMarkerStyle(kFullCircle);
  hEG1_RatioPurity->SetMarkerSize(2);
  TLegend* legPurity_EG1 = new TLegend(0.6,0.7,0.85,0.85);
  legPurity_EG1->SetHeader("Norm*Purity EG1 Trigger");
  legPurity_EG1->AddEntry(hEG1_8TeVPurity,"8.16 TeV");
  legPurity_EG1->AddEntry(hEG1_5TeVPurity,"5.02 TeV");
  TCanvas* cPurity_EG1 = new TCanvas("cPurity_EG1", "cPurity_EG1");
  cPurity_EG1->SetLogy();
  hEG1_8TeVPurity->GetXaxis()->SetRangeUser(12, 60);
  hEG1_8TeVPurity->GetYaxis()->SetRangeUser(5e-7, 0.1);
  hEG1_8TeVPurity->Draw("e1");
  hEG1_5TeVPurity->Draw("same e1");
  legPurity_EG1->Draw("same");
  TCanvas* cRatioPurity = new TCanvas("cRatioPurity", "cRatioPurity");
  hEG1_RatioPurity->GetXaxis()->SetRangeUser(12, 60);
  hEG1_RatioPurity->GetYaxis()->SetRangeUser(0, 1);
  hEG1_RatioPurity->Draw("e1");
  cout << "Normlized Yield*Purity Ratio Fit" << endl;
  hEG1_RatioPurity->Fit("pol0", "", "", 12, 60);
  TF1* fEG1_RatioPurity = (TF1*)hEG1_RatioPurity->GetFunction("pol0");
  fEG1_RatioPurity->SetName("fEG1_RatioPurity");
  double parEG1_RatioPurity  = fEG1_RatioPurity->GetParameter(0);
  double parErrEG1_RatioPurity = fEG1_RatioPurity->GetParError(0);
  TLegend* legRatioPurity = new TLegend(0.2,0.7,0.85,0.85);
  legRatioPurity->SetHeader("Photon Yield Ratio");
  legRatioPurity->AddEntry(hEG1_RatioPurity,"EG1 Trigger");
  legRatioPurity->AddEntry(fEG1_RatioPurity, Form("Constant Fit (12, 60) GeV = %.2f #pm %.2f", parEG1_RatioPurity, parErrEG1_RatioPurity));  
  legRatioPurity->Draw("same");
  
  //Normazlied*Purity/Eff
  hEG1_8TeVPurityEff->SetLineColor(kBlue);
  hEG1_8TeVPurityEff->SetMarkerColor(kBlue);
  hEG1_8TeVPurityEff->SetMarkerStyle(kFullCircle);
  hEG1_8TeVPurityEff->SetMarkerSize(2);
  hEG1_5TeVPurityEff->SetLineColor(kGreen);
  hEG1_5TeVPurityEff->SetMarkerColor(kGreen);
  hEG1_5TeVPurityEff->SetMarkerStyle(kFullCircle);
  hEG1_5TeVPurityEff->SetMarkerSize(2);
  hEG1_RatioPurityEff->SetLineColor(kBlack);
  hEG1_RatioPurityEff->SetMarkerColor(kBlack);
  hEG1_RatioPurityEff->SetMarkerStyle(kFullCircle);
  hEG1_RatioPurityEff->SetMarkerSize(2);
  TLegend* legPurityEff_EG1 = new TLegend(0.6,0.7,0.85,0.85);
  legPurityEff_EG1->SetHeader("Norm*Purity/Eff EG1 Trigger");
  legPurityEff_EG1->AddEntry(hEG1_8TeVPurityEff,"8.16 TeV");
  legPurityEff_EG1->AddEntry(hEG1_5TeVPurityEff,"5.02 TeV");
  TCanvas* cPurityEff_EG1 = new TCanvas("cPurityEff_EG1", "cPurityEff_EG1");
  cPurityEff_EG1->SetLogy();
  hEG1_8TeVPurityEff->GetXaxis()->SetRangeUser(12, 60);
  hEG1_8TeVPurityEff->GetYaxis()->SetRangeUser(5e-7, 0.11);
  hEG1_8TeVPurityEff->Draw("e1");
  hEG1_5TeVPurityEff->Draw("same e1");
  legPurityEff_EG1->Draw("same");
  TCanvas* cRatioPurityEff = new TCanvas("cRatioPurityEff", "cRatioPurityEff");
  hEG1_RatioPurityEff->GetXaxis()->SetRangeUser(12, 60);
  hEG1_RatioPurityEff->GetYaxis()->SetRangeUser(0, 1);
  hEG1_RatioPurityEff->Draw("e1");
  cout << "Normlized Yield*Purity/Eff  Ratio Fit" << endl;
  hEG1_RatioPurityEff->Fit("pol0", "", "", 12, 60);
  TF1* fEG1_RatioPurityEff = (TF1*)hEG1_RatioPurityEff->GetFunction("pol0");
  fEG1_RatioPurityEff->SetName("fEG1_RatioPurityEff");
  double parEG1_RatioPurityEff  = fEG1_RatioPurityEff->GetParameter(0);
  double parErrEG1_RatioPurityEff = fEG1_RatioPurityEff->GetParError(0);
  TLegend* legRatioPurityEff = new TLegend(0.2,0.7,0.85,0.85);
  legRatioPurityEff->SetHeader("Photon Yield Ratio");
  legRatioPurityEff->AddEntry(hEG1_RatioPurityEff,"EG1 Trigger");
  legRatioPurityEff->AddEntry(fEG1_RatioPurityEff, Form("Constant Fit (12, 60) GeV = %.2f #pm %.2f", parEG1_RatioPurityEff, parErrEG1_RatioPurityEff));  
  legRatioPurityEff->Draw("same");

  
  //Normazlied*Purity/Eff*lumi
  hEG1_8TeVCS->SetLineColor(kBlue);
  hEG1_8TeVCS->SetMarkerColor(kBlue);
  hEG1_8TeVCS->SetMarkerStyle(kFullCircle);
  hEG1_8TeVCS->SetMarkerSize(2);
  hEG1_5TeVCS->SetLineColor(kGreen);
  hEG1_5TeVCS->SetMarkerColor(kGreen);
  hEG1_5TeVCS->SetMarkerStyle(kFullCircle);
  hEG1_5TeVCS->SetMarkerSize(2);
  hEG1_RatioCS->SetLineColor(kBlack);
  hEG1_RatioCS->SetMarkerColor(kBlack);
  hEG1_RatioCS->SetMarkerStyle(kFullCircle);
  hEG1_RatioCS->SetMarkerSize(2);
  TLegend* legCS_EG1 = new TLegend(0.6,0.7,0.85,0.85);
  legCS_EG1->SetHeader("Norm*Purity/Eff*lumi EG1 Trigger");
  legCS_EG1->AddEntry(hEG1_8TeVCS,"8.16 TeV");
  legCS_EG1->AddEntry(hEG1_5TeVCS,"5.02 TeV");
  TCanvas* cCS_EG1 = new TCanvas("cCS_EG1", "cCS_EG1");
  cCS_EG1->SetLogy();
  hEG1_8TeVCS->GetXaxis()->SetRangeUser(12, 60);
  hEG1_8TeVCS->GetYaxis()->SetRangeUser(5, 9e3);
  hEG1_8TeVCS->Draw("e1");
  hEG1_5TeVCS->Draw("same e1");
  legCS_EG1->Draw("same");
  TCanvas* cRatioCS = new TCanvas("cRatioCS", "cRatioCS");
  hEG1_RatioCS->GetXaxis()->SetRangeUser(12, 60);
  hEG1_RatioCS->GetYaxis()->SetRangeUser(0.5, 3.5);
  hEG1_RatioCS->Draw("e1");
  cout << "Normlized Yield*Purity/Eff*Lumi  Ratio Fit" << endl;
  hEG1_RatioCS->Fit("pol0", "", "", 12, 60);
  TF1* fEG1_RatioCS = (TF1*)hEG1_RatioCS->GetFunction("pol0");
  fEG1_RatioCS->SetName("fEG1_RatioCS");
  double parEG1_RatioCS  = fEG1_RatioCS->GetParameter(0);
  double parErrEG1_RatioCS = fEG1_RatioCS->GetParError(0);
  TLegend* legRatioCS = new TLegend(0.2,0.7,0.85,0.85);
  legRatioCS->SetHeader("Photon Yield Ratio");
  legRatioCS->AddEntry(hEG1_RatioCS,"EG1 Trigger");
  legRatioCS->AddEntry(fEG1_RatioCS, Form("Constant Fit (12, 60) GeV = %.2f #pm %0.2f", parEG1_RatioCS, parErrEG1_RatioCS));  
  legRatioCS->Draw("same");
  
  //unity --> line at 1
  TLine *lineAt1 = new TLine(12, 1, 60, 1);
  lineAt1->SetLineColor(kBlack);
  lineAt1->SetLineWidth(3);
  lineAt1->SetLineStyle(kDashed);
  lineAt1->Draw("same");


  /*cout << "Calc cross section" << endl;
  
  for(int i = 1; i < hEG1_8TeVCS->GetNbinsX()+1; i++){
    Double_t yield = hEG1_8TeVNorm->GetBinContent(i+6);
    Double_t yieldErr = hEG1_8TeVNorm->GetBinError(i+6);

    //Double_t purity = purityABCD_EG1->GetBinContent(i+1);
    //Double_t purityErr = purityABCD_EG1->GetBinError(i+1);

    Double_t eff = totalEfficiency_EG1->GetBinContent(i+1);
    Double_t effErr = totalEfficiency_EG1->GetBinError(i+1);

    //Double_t crossSec_8TeV = (yield*purity*refCS_8TeV)/(eff*rfEG1_8TeV);
    Double_t crossSec_8TeV = (yield*numEventsEG1_8TeV)/(eff*lumi_EG1);
    Double_t crossSecRelErr_8TeV = TMath::Sqrt(TMath::Power(yieldErr/yield, 2)+TMath::Power(effErr/eff, 2));
    Double_t crossSecErr_8TeV = crossSec_8TeV*crossSecRelErr_8TeV;

    //cout << yield << "\t" << purity << "\t" << eff << "\t" << crossSec_8TeV << endl;;

    hEG1_8TeVCS->SetBinContent(i+5, crossSec_8TeV);
    hEG1_8TeVCS->SetBinError(i+5, crossSecErr_8TeV);

    Double_t crossSec_5TeV = hEG1_5TeVCS->GetBinContent(i+5);
    Double_t crossSecErr_5TeV = hEG1_5TeVCS->GetBinError(i+5);

    Double_t ratioCS =  crossSec_8TeV/crossSec_5TeV;
    cout <<  crossSec_8TeV << "\t" <<  crossSec_5TeV << "\t" << ratioCS << endl;
    Double_t errorRatioCS = ratioCS*(TMath::Sqrt(TMath::Power(crossSecErr_8TeV/crossSec_8TeV,2)+TMath::Power(crossSecErr_5TeV/crossSec_5TeV,2)));

    hEG1_RatioCS->SetBinContent(i+5, ratioCS);
    hEG1_RatioCS->SetBinError(i+5, errorRatioCS);//
    
  }

  hEG1_8TeVCS->SetLineColor(kBlue);
  hEG1_8TeVCS->SetMarkerColor(kBlue);
  hEG1_8TeVCS->SetMarkerStyle(kFullCircle);
  hEG1_8TeVCS->SetMarkerSize(2);
  hEG1_5TeVCS->SetLineColor(kGreen);
  hEG1_5TeVCS->SetMarkerColor(kGreen);
  hEG1_5TeVCS->SetMarkerStyle(kFullCircle);
  hEG1_5TeVCS->SetMarkerSize(2);
  hEG1_RatioCS->SetLineColor(kBlack);
  hEG1_RatioCS->SetMarkerColor(kBlack);
  hEG1_RatioCS->SetMarkerStyle(kFullCircle);
  hEG1_RatioCS->SetMarkerSize(2);

  TLegend* legCS_EG1 = new TLegend(0.6,0.7,0.85,0.85);
  legCS_EG1->SetHeader("Photon CS EG1 Trigger");
  legCS_EG1->AddEntry(hEG1_8TeVCS,"8.16 TeV");
  legCS_EG1->AddEntry(hEG1_5TeVCS,"5.02 TeV");
  TCanvas* c1_EG1CS = new TCanvas("c1_EG1CS", "c1_EG1CS");
  c1_EG1CS->SetLogy();
  hEG1_8TeVCS->GetXaxis()->SetRangeUser(12, 60);
  hEG1_8TeVCS->Draw("e1");
  hEG1_5TeVCS->Draw("same e1");
  legCS_EG1->Draw("same");//*/






  //EG2 - threshold 5.5 GeV
  TH1F* rawYields_EG2 = (TH1F*)file_8pPb->Get("rawYields_EG2");
  TH1F* totalEfficiency_EG2 = (TH1F*)file_8pPb->Get("totalEfficiency_EG2");
  TH1F* purityABCD_EG2 = (TH1F*)file_8pPb->Get("purityABCD_EG2");
  TH1F* rejectionFactor_EG2 = (TH1F*)file_8pPb->Get("rejectionFactor_EG2");
  TH1F* acceptedEvents_EG2 = (TH1F*)file_8pPb->Get("acceptedEvents_EG2");
  TH1F* hEG2_8TeVRaw = new TH1F("hEG2_8TeVRaw", "", nbinscluster, clusterbins);
  TH1F* hEG2_8TeVNorm = new TH1F("hEG2_8TeVNorm", ";E_{T} (GeV);#frac{1}{N_{eve}}#frac{d^{2}N}{dp_{T}d#eta}", nbinscluster, clusterbins);
  TH1F* hEG2_8TeVCS = new TH1F("hEG2_8TeVCS", "", nbinscluster, clusterbins);
  TH1F* hEGA_8TeVCS = new TH1F("hEGA_8TeVCS", "", nbinscluster, clusterbins);

  Double_t numEventsEG2_8TeV = acceptedEvents_EG2->GetBinContent(1);
  //EG2
  for(int i = 1; i < rawYields_EG2->GetNbinsX()+1; i++){
    Double_t clusterpt = rawYields_EG2->GetXaxis()->GetBinCenter(i);
    Double_t weight = rawYields_EG2->GetBinContent(i);
    hEG2_8TeVRaw->Fill(clusterpt, weight);
  }//*/
  
  for(int i = 1; i < hEG2_8TeVRaw->GetNbinsX()+1; i++){
    double dE = hEG2_8TeVRaw->GetBinWidth(i);
    
    double content8TeV = hEG2_8TeVRaw->GetBinContent(i);
    double temp8TeV = (content8TeV*acceptanceNorm)/((double)numEventsEG2_8TeV*dE);
    double error8TeV = hEG2_8TeVRaw->GetBinError(i);
    double tempErr8TeV = (error8TeV*acceptanceNorm)/((double)numEventsEG2_8TeV*dE);
    hEG2_8TeVNorm->SetBinContent(i,temp8TeV);
    hEG2_8TeVNorm->SetBinError(i, tempErr8TeV);
    Double_t content5TeV = hEG2_5TeVNorm->GetBinContent(i);
    Double_t error5TeV = hEG2_5TeVNorm->GetBinError(i);
    Double_t ratiopPb = temp8TeV/content5TeV;
    //cout << temp8TeV << "\t" << content5TeV << "\t" << ratiopPb << endl;
    Double_t errorRatiopPb = ratiopPb*(TMath::Sqrt(TMath::Power(tempErr8TeV/temp8TeV,2)+TMath::Power(error5TeV/content5TeV,2)));
    hEG2_RatioNorm->SetBinContent(i, ratiopPb);
    hEG2_RatioNorm->SetBinError(i, errorRatiopPb);
    }//*/

  //EG2 Norm spectra hist style
  hEG2_8TeVNorm->SetLineColor(kBlue);
  hEG2_8TeVNorm->SetMarkerColor(kBlue);
  hEG2_8TeVNorm->SetMarkerStyle(kFullSquare);
  hEG2_8TeVNorm->SetMarkerSize(2);
  hEG2_5TeVNorm->SetLineColor(kGreen);
  hEG2_5TeVNorm->SetMarkerColor(kGreen);
  hEG2_5TeVNorm->SetMarkerStyle(kFullSquare);
  hEG2_5TeVNorm->SetMarkerSize(2);
  hEG2_RatioNorm->SetLineColor(kBlack);
  hEG2_RatioNorm->SetMarkerColor(kBlack);
  hEG2_RatioNorm->SetMarkerStyle(kFullSquare);
  hEG2_RatioNorm->SetMarkerSize(2);//*/

  TLegend* legYield_EG2 = new TLegend(0.6,0.7,0.85,0.85);
  legYield_EG2->SetHeader("Photon Yield EG2 Trigger");
  legYield_EG2->AddEntry(hEG2_8TeVNorm,"8.16 TeV");
  legYield_EG2->AddEntry(hEG2_5TeVNorm,"5.02 TeV");
  TCanvas* c1_EG2 = new TCanvas("c1_EG2", "c1_EG2");
  c1_EG2->SetLogy();
  hEG2_8TeVNorm->GetXaxis()->SetRangeUser(12, 60);
  hEG2_8TeVNorm->GetYaxis()->SetRangeUser(5e-7, 1e-2);
  hEG2_8TeVNorm->Draw("e1");
  hEG2_5TeVNorm->Draw("same e1");
  legYield_EG2->Draw("same");//*/

  TCanvas* cRatioNormEG2 = new TCanvas("cRatioNormEG2", "cRatioNormEG2");
  hEG2_RatioNorm->GetXaxis()->SetRangeUser(12, 60);
  hEG2_RatioNorm->GetYaxis()->SetRangeUser(0, 1);
  hEG2_RatioNorm->Draw("e1");

  /*totalEfficiency_EG2->SetLineColor(kCyan);
  totalEfficiency_EG2->SetMarkerColor(kCyan);
  totalEfficiency_EG2->SetMarkerStyle(kFullSquare);
  totalEfficiency_EG2->SetMarkerSize(2);*/


  TFile* file_8pp = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/8TeVResults/ppNew/simpleOutput_ppEMC.root"), "READ");
  TH1F* totalEfficiency_EGA = (TH1F*)file_8pp->Get("totalEfficiency_EGA");
  TH1F* hEffpp_5TeV = (TH1F*)file_5pPb->Get("hEff_pp");
  
  totalEfficiency_EG1->SetLineColor(kBlue);
  totalEfficiency_EG1->SetMarkerColor(kBlue);
  totalEfficiency_EG1->SetMarkerStyle(kFullCircle);
  totalEfficiency_EG1->SetMarkerSize(2);
  totalEfficiency_EGA->SetLineColor(kCyan);
  totalEfficiency_EGA->SetMarkerColor(kCyan);
  totalEfficiency_EGA->SetMarkerStyle(kFullSquare);
  totalEfficiency_EGA->SetMarkerSize(2);
  hEff_5TeV->SetLineColor(kGreen);
  hEff_5TeV->SetMarkerColor(kGreen);
  hEff_5TeV->SetMarkerStyle(kFullCircle);
  hEff_5TeV->SetMarkerSize(2);
  hEffpp_5TeV->SetLineColor(kRed);
  hEffpp_5TeV->SetMarkerColor(kRed);
  hEffpp_5TeV->SetMarkerStyle(kFullSquare);
  hEffpp_5TeV->SetMarkerSize(2);

  TLegend* legEff= new TLegend(0.4,0.15,0.85,0.4);
  legEff->SetHeader("Photon Efficiency");
  legEff->AddEntry(totalEfficiency_EG1,"Run 2, p-Pb, 8.16 TeV");
  legEff->AddEntry(totalEfficiency_EGA,"Run 1, pp,  8 TeV");
  legEff->AddEntry(hEff_5TeV,"Run 1, p-Pb, 5.02 TeV");
  //legEff->AddEntry(hEffpp_5TeV,"pp 5.02 TeV");
  TCanvas* cEff = new TCanvas("cEff", "cEff");
  totalEfficiency_EG1->GetXaxis()->SetRangeUser(12, 60);
  totalEfficiency_EG1->GetYaxis()->SetRangeUser(0, 1);
  totalEfficiency_EG1->SetTitle(";E_{T} (GeV);#epsilon");
  totalEfficiency_EG1->Draw("e1");
  totalEfficiency_EGA->Draw("same e1");
  hEff_5TeV->Draw("same e1");
  //hEffpp_5TeV->Draw("same e1");
  legEff->Draw("same");

  //cross section comparison
  TFile* file_8pPbEDC = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/8TeVResults/pPbNew/simpleOutput_pPbEDC.root"), "READ");
  TH1F* xsection_EG1_8TeV = (TH1F*)file_8pPbEDC->Get("xsection_EG1");
  TH1F* xsection_EG1_ratio = new TH1F("xsection_EG1_ratio", ";E_{T} (GeV); #frac{8.16 TeV}{5.02 TeV}", nbinscluster, clusterbins);

  for(int i = 1; i < xsection_EG1_ratio->GetNbinsX()+1; i++){
    int fBinNum = i+1;
    int dBinNum = i+6;
    cout << xsection_EG1_8TeV->GetBinLowEdge(i+1) << "\t" << xsection_EG1_ratio->GetBinLowEdge(i+6) << "\t" <<  hEG1_5TeVCS->GetBinLowEdge(i+6) << endl;
    Double_t cont8TeV_EG1 = xsection_EG1_8TeV->GetBinContent(i+1);
    Double_t cont8TeVErr_EG1 = xsection_EG1_8TeV->GetBinError(i+1);
    Double_t cont5TeV_EG1 = hEG1_5TeVCS->GetBinContent(i+6);
    Double_t cont5TeVErr_EG1 = hEG1_5TeVCS->GetBinError(i+6);
    Double_t contRatio_EG1 = cont8TeV_EG1/cont5TeV_EG1;
    Double_t contRatioErr_EG1 = contRatio_EG1*(TMath::Sqrt(TMath::Power(cont5TeVErr_EG1/cont5TeV_EG1,2) + TMath::Power(cont8TeVErr_EG1/cont8TeV_EG1,2)));
    xsection_EG1_ratio->SetBinContent(i+6, contRatio_EG1);
    xsection_EG1_ratio->SetBinError(i+6, contRatioErr_EG1);
    
  }

  xsection_EG1_8TeV->SetLineColor(kMagenta);
  xsection_EG1_8TeV->SetMarkerColor(kMagenta);
  xsection_EG1_8TeV->SetMarkerStyle(kFullSquare);
  xsection_EG1_8TeV->SetMarkerSize(2);
  xsection_EG1_ratio->SetLineColor(kBlack);
  xsection_EG1_ratio->SetMarkerColor(kBlack);
  xsection_EG1_ratio->SetMarkerStyle(kFullSquare);
  xsection_EG1_ratio->SetMarkerSize(2);//*/


  TLegend* legxsection_EG1 = new TLegend(0.5,0.75,0.85,0.85);
  legxsection_EG1->SetHeader("EG1 Triggered cross section");
  legxsection_EG1->AddEntry(xsection_EG1_8TeV, "8.16 TeV, EMCal+DCal");
  //legxsection_EG1->AddEntry(hEG1_8TeVCS,Form("8.16 TeV EMC using RF = %.0f", rfEG1_8TeV));
  legxsection_EG1->AddEntry(hEG1_5TeVCS,"5.02 TeV, EMCal only");  
  TCanvas* cxsection_EG1 = new TCanvas("cxsection_EG1", "cxsection_EG1", 500, 800);
  cxsection_EG1->SetLogy();
  xsection_EG1_8TeV->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  xsection_EG1_8TeV->GetXaxis()->SetRangeUser(12, 60);
  xsection_EG1_8TeV->GetYaxis()->SetRangeUser(5, 9e3);
  xsection_EG1_8TeV->Draw("e1");
  //hEG1_8TeVCS->Draw("same e1");
  hEG1_5TeVCS->Draw("same e1");
  legxsection_EG1->Draw("same");

  
  TCanvas* cxsectionRatio_EG1 = new TCanvas("cxsectionRatio_EG1", "cxsectionRatio_EG1");
  xsection_EG1_ratio->GetXaxis()->SetRangeUser(12, 60);
  xsection_EG1_ratio->GetYaxis()->SetRangeUser(0, 5);
  xsection_EG1_ratio->Draw("e1");
  xsection_EG1_ratio->Fit("pol0", "", "", 12, 60);
  TF1* fEG1_xsectionRatio = (TF1*)xsection_EG1_ratio->GetFunction("pol0");
  fEG1_xsectionRatio->SetName("fEG1_xsectionRatio");
  double parEG1_xsectionRatio  = fEG1_xsectionRatio->GetParameter(0);
  double parErrEG1_xsectionRatio = fEG1_xsectionRatio->GetParError(0);
  TLegend* legxsectionRatio = new TLegend(0.2,0.7,0.85,0.85);
  //legxsectionRatio->SetHeader("Photon Yield Ratio");
  legxsectionRatio->AddEntry(xsection_EG1_ratio, "cross section ratio");
  legxsectionRatio->AddEntry(fEG1_xsectionRatio, Form("Constant Fit (12, 60) GeV = %.2f #pm %0.2f", parEG1_xsectionRatio, parErrEG1_xsectionRatio));  
  legxsectionRatio->Draw("same");

  /*TH1F* hEGA_8TeVCS_pp = (TH1F*)file_8pp->Get("xsection_EGA");
  TFile* fout = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/8TeVResults/compairison8TeV5TeV_RF991.root"), "RECREATE");
  xsection_EG1_8TeV->Write("xsection_EG1_8TeV");
  hEG1_8TeVCS->Write("hEG1_8TeVCS_pPb");
  hEGA_8TeVCS_pp->Write("hEG1-8TeVCS_pp");
  hEG1_5TeVCS->Write("hEG1_5TeVCS_pPb");
  fout->Close();//*/


}//end makeComparisons
