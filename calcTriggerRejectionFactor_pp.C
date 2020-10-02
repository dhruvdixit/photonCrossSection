#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TGraphAsymmErrors.h"
//#include "TTreeReader.h"
//#include "TTreeReaderValue.h"
#include "TMath.h"
#include "TVector2.h"
//#include "/root/atlasstyle-00-03-05/AtlasStyle.h"
//#include "/root/atlasstyle-00-03-05/AtlasStyle.C"
//#include "/root/atlasstyle-00-03-05/AtlasUtils.h"
//#include "/root/atlasstyle-00-03-05/AtlasUtils.C"
//#include "/root/atlasstyle-00-03-05/AtlasLabels.h"
//#include "/root/atlasstyle-00-03-05/AtlasLabels.C"
#include "TDatabasePDG.h"
#include "TEfficiency.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bitset>
#include <bits/stdc++.h>
#include <cstring>

void calcTriggerRejectionFactor_pp(){
  
  //gStyle->SetCanvasColor(-1);
  //gStyle->SetPadColor(-1);
  //gStyle->SetFrameFillColor(-1);
  //gStyle->SetHistFillColor(-1);
  //gStyle->SetTitleFillColor(-1);
  //gStyle->SetFillColor(-1);
  //gStyle->SetFillStyle(4000);
  //gStyle->SetStatStyle(0);
  //gStyle->SetTitleStyle(0);
  gStyle->SetCanvasPreferGL(kTRUE);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/";

  //TFile* fin = new TFile(Form("%sfout_5_26bins_17q_All_forRTrig_MBEG2exlusion_tof20_eCross5_newExoticity_noNorm.root", path.Data()), "READ");//all 17q runs
  //TFile* fin = new TFile(Form("%sfout_5_26bins_17q_CENT_wSDD_noThresh_TPC_physel_forRTrig_MBEG2exlusion_tof20_eCross5_newExoticity_noNorm.root", path.Data()), "READ");//only TPC+ITS 17q runs

  //TFile* fin = new TFile(Form("%sfout_5_26bins_17pq_All_forRTrig_MBEG2exlusion_tof20_eCross5_newExoticity_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_5_26bins_17pq_almostAll_forRTrig_MBEG2exlusion_tof20_eCross5_newExoticity_noNorm2_ISOnormal_wSSHist.root", path.Data()), "READ");//wISO < 1.5
  //TFile* fin = new TFile(Form("%sfout_5_26bins_17pq_All_forRTrig_MBEG2exlusion_tof20_eCross5_newExoticity_wISO_noNorm2.root", path.Data()), "READ");//wISO < 1
  TFile* fin = new TFile(Form("%sfout_5_26bins_17pq_almostAll17pAndAll17qITSonly_forRTrig_MBEG2exlusion_tof20_eCross5_newExoticity_wSSHist_noNorm2.root", path.Data()), "READ");

  TH1F* hMB_centE = (TH1F*)fin->Get("hMB_centE");
  TH1F* hEG2_caloE = (TH1F*)fin->Get("hEG2_caloE");
  TH1F* hNormalizer = (TH1F*)fin->Get("hNormalizer");

  Double_t numEvents_MB = hNormalizer->GetBinContent(9);
  Double_t numEvents_EG2 = hNormalizer->GetBinContent(11);

  TH1F* RTrig = (TH1F*)fin->Get("hReco_pt");
  RTrig->SetName("RTrig");
  RTrig->SetTitle(";E_{T} [GeV];R_{trig}");
  
  for(int i = 1; i < hMB_centE->GetNbinsX()+1; i++){
    double dE = hMB_centE->GetBinWidth(i);
    
    double contentMB = hMB_centE->GetBinContent(i);
    double tempMB = (contentMB)/((double)numEvents_MB*dE);
    double errorMB = hMB_centE->GetBinError(i);
    double tempErrMB = (errorMB)/((double)numEvents_MB*dE);
    if(numEvents_MB && tempErrMB/tempMB < 1.0){
      hMB_centE->SetBinContent(i,tempMB);
      hMB_centE->SetBinError(i, tempErrMB);
    }
    else {
      hMB_centE->SetBinContent(i,0);
      hMB_centE->SetBinError(i, 0);
    }
    
    double contentEG2 = hEG2_caloE->GetBinContent(i);
    double tempEG2 = (contentEG2)/((double)numEvents_EG2*dE);
    double errorEG2 = hEG2_caloE->GetBinError(i);
    double tempErrEG2 = (errorEG2)/((double)numEvents_EG2*dE);
    //if(numEvents_EG2 && tempErrEG2/tempEG2 < 1.0) 
    {
      hEG2_caloE->SetBinContent(i,tempEG2);
      hEG2_caloE->SetBinError(i, tempErrEG2);
    }
    
    //cout << tempErrEG2/tempEG2 << "\t" << tempErrMB/tempMB << endl;
    RTrig->SetBinContent(i, 0);
    RTrig->SetBinError(i, 0);
    if(tempMB){
      double contentRF = tempEG2/tempMB;
      double errorRF = TMath::Sqrt(TMath::Power(tempErrEG2,2) +TMath::Power(tempErrMB,2));
      //cout << contentRF << "\t" << errorRF << "\t" << errorRF/contentRF << endl;
      //if(errorRF/contentRF < 1.0){
      RTrig->SetBinContent(i, contentRF);
      RTrig->SetBinError(i, errorRF);
      //}
    }//*/
  }//end for
  
  hEG2_caloE->SetLineColor(kOrange);
  hMB_centE->SetLineColor(kBlack);
  hEG2_caloE->SetMarkerColor(kOrange);
  hMB_centE->SetMarkerColor(kBlack);
  hEG2_caloE->SetMarkerStyle(kFullCircle);
  hMB_centE->SetMarkerStyle(kFullCircle);

  TLegend* ls = new TLegend(0.6, 0.6,0.85, 0.85);
  ls->AddEntry((TObject*)0, "Cluster Spectra", "");
  ls->AddEntry((TObject*)0, "pp #sqrt{s_{NN}} = 5.02 TeV", "");
  ls->AddEntry(hMB_centE, "Minimum bias trigger (MB)");
  ls->AddEntry(hEG2_caloE, "EMCal L1 trigger (EG2 calo)");
  
  TCanvas* c1 = new TCanvas();
  c1->SetLogy();
  hMB_centE->GetXaxis()->SetRangeUser(0, 40);
  hMB_centE->GetYaxis()->SetRangeUser(1e-9, 1);
  hMB_centE->SetTitle(";E_{T} [GeV]; #frac{1}{N_{ev}}x#frac{dN}{dE_{T}} [a.u.]");
  hMB_centE->Draw("e1");
  hEG2_caloE->Draw("samee1");
  ls->Draw("same");

  TCanvas* c2 = new TCanvas();
  c2->SetLogy();
  TH1F* Rtrig = (TH1F*)hEG2_caloE->Clone();
  Rtrig->SetName("Rtrig");
  Rtrig->SetTitle(";E_{T} [GeV];R_{trig}");
  Rtrig->Divide(hMB_centE);
  Rtrig->SetLineColor(kBlue);
  Rtrig->SetMarkerColor(kBlue);
  Rtrig->GetXaxis()->SetRangeUser(0, 40);
  //Rtrig->GetYaxis()->SetRangeUser(2e-4, 2e4);
  Rtrig->GetYaxis()->SetRangeUser(1e-3, 2e5);
  Rtrig->Draw("e1");

  cout << "7, 40" << endl;
  Rtrig->Fit("pol0", "", "", 7, 40);
  TF1* fit7 = (TF1*)Rtrig->GetFunction("pol0");fit7->SetName("fit7");
  fit7->SetLineColorAlpha(kCyan, 0.25);
  fit7->SetLineWidth(10);
  cout << "************************************************" << endl;
  cout << "8, 40" << endl;
  Rtrig->Fit("pol0", "+", "", 8, 40);
  TF1* fit8 = (TF1*)Rtrig->GetFunction("pol0");fit8->SetName("fit8");
  fit8->SetLineColorAlpha(kBlue, 0.25);
  fit8->SetLineWidth(10);
  cout << "************************************************" << endl;
  cout << "9, 40" << endl;
  Rtrig->Fit("pol0", "+", "", 9, 40);
  TF1* fit9 = (TF1*)Rtrig->GetFunction("pol0");fit9->SetName("fit9");
  fit9->SetLineColorAlpha(kMagenta, 0.25);
  fit9->SetLineWidth(10);
  cout << "************************************************" << endl;
  cout << "10, 40" << endl;
  Rtrig->Fit("pol0", "+", "", 10, 40);
  TF1* fit10 = (TF1*)Rtrig->GetFunction("pol0");fit10->SetName("fit10");
  fit10->SetLineColorAlpha(kRed, 0.25);
  fit10->SetLineWidth(10);
  cout << "************************************************" << endl;
  cout << "11, 40" << endl;
  Rtrig->Fit("pol0", "+", "", 11, 40);
  TF1* fit11 = (TF1*)Rtrig->GetFunction("pol0");fit11->SetName("fit11");
  fit11->SetLineColorAlpha(kOrange, 0.25);
  fit11->SetLineWidth(10);
  cout << "************************************************" << endl;

  
  TLine *scalar17p = new TLine(0,1264 , 40, 1264);
  scalar17p->SetLineColorAlpha(kGray, 1.0);
  scalar17p->SetLineWidth(2);
  scalar17p->Draw("same");

  TLine *scalar17q = new TLine(0,1278 , 40, 1278);
  scalar17q->SetLineColorAlpha(kBlack, 1.0);
  scalar17q->SetLineWidth(1);
  scalar17q->Draw("same");

  /*TLine *linePlusSigma = new TLine(0, 1003, 40, 1003);
  linePlusSigma->SetLineColorAlpha(kBlue, 0.5);
  linePlusSigma->SetLineWidth(7);
  linePlusSigma->SetLineStyle(9);
  linePlusSigma->Draw("same");

  TLine *lineMinusSigma = new TLine(0, 854, 40, 854);
  lineMinusSigma->SetLineColorAlpha(kBlue, 0.5);
  lineMinusSigma->SetLineWidth(7);
  lineMinusSigma->SetLineStyle(9);
  lineMinusSigma->Draw("same");*/

  
  TLegend* lRF = new TLegend(0.12, 0.2, 0.87, 0.45);
  lRF->SetBorderSize(0);
  lRF->SetTextSize(0.025);
  lRF->SetHeader("ALICE EMCal L1 Trigger turn on curve, pp #sqrt{s_{NN}} = 5.02 TeV");
  lRF->SetNColumns(2);
  lRF->AddEntry(Rtrig, "EG2/MB", "p");
  lRF->AddEntry(fit7, "Contant Fit (7, 40) GeV, R_{trig}=1236#pm16, #frac{#chi^{2}}{NDf} = 14.5/16", "l");
  lRF->AddEntry(fit8, "Contant Fit (8, 40) GeV, R_{trig}=1270#pm23, #frac{#chi^{2}}{NDf} = 10.1/15", "l");
  lRF->AddEntry(fit9, "Contant Fit (9, 40) GeV, R_{trig}=1240#pm28, #frac{#chi^{2}}{NDf} = 7.0/14", "l");
  lRF->AddEntry(fit10, "Contant Fit (10, 40) GeV, R_{trig}=1225#pm35, #frac{#chi^{2}}{NDf} = 6.5/13", "l");
  lRF->AddEntry(fit11, "Contant Fit (11, 40) GeV, R_{trig}=1225#pm43, #frac{#chi^{2}}{NDf} = 6.5/12", "l");
  lRF->AddEntry(scalar17p, "Scalar method 17p, R_{trig}=1264#pm5", "l");
  lRF->AddEntry(scalar17q, "Scalar method 17q, R_{trig}=1278#pm5", "l");
  lRF->Draw("same");

  //TFile* fout = new TFile("/global/homes/d/ddixit/photonCrossSection/rfOutput/noNormResults_17qAll.root", "RECREATE");
  //Rtrig->Write("RTrig");
  //fout->Close();

  TCanvas* c4 = new TCanvas();
  c4->SetLogy();
  hMB_centE->GetXaxis()->SetRangeUser(0, 40);
  hMB_centE->GetYaxis()->SetRangeUser(1e-9, 1);
  hMB_centE->SetTitle(";E_{T} [GeV]; #frac{1}{N_{ev}}x#frac{dN}{dE_{T}} [a.u.]");
  hMB_centE->Draw("e1");
  hEG2_caloE->Draw("samee1");


  TH1F* scale1 = (TH1F*)hEG2_caloE->Clone(); scale1->SetName("scale1"); scale1->Scale(1.0/1278.0);scale1->SetLineColor(kRed); scale1->SetMarkerColor(kRed);scale1->Draw("samee1");
  TH1F* scale2 = (TH1F*)hEG2_caloE->Clone(); scale2->SetName("scale2"); scale2->Scale(1.0/1130.0);scale2->SetLineColor(kBlue); scale2->SetMarkerColor(kBlue);scale2->Draw("samee1");

  ls->AddEntry(scale1, "Using RF = 1278, Scalar method");
  ls->AddEntry(scale2, "Using RF = 1240, Cluster spectra method");
  ls->Draw("same");

  TH1F* ratio1 = (TH1F*)scale1->Clone(); ratio1->Divide(hMB_centE);
  TH1F* ratio2 = (TH1F*)scale2->Clone(); ratio2->Divide(hMB_centE);
  
  TLegend* lratio = new TLegend(0.15, 0.75, 0.45, 0.85);
  ratio1->SetTitle(";E_{T} [GeV]; #frac{Scaled EG2 spectra}{MB spectra}");
  lratio->SetBorderSize(0);
  lratio->SetTextSize(0.025);
  lratio->AddEntry(ratio1, "Using RF = 1278, Scalar method");
  lratio->AddEntry(ratio2, "Using RF = 1240, Cluster spectra method");
  

  TCanvas* c5 = new TCanvas();
  ratio1->GetXaxis()->SetRangeUser(0, 40);
  TLine *line2 = new TLine(0, 1, 40, 1);
  line2->SetLineColorAlpha(kBlack, 0.5);
  line2->SetLineWidth(7);

  ratio1->Draw("e1");
  ratio2->Draw("samee1");
  line2->Draw("same");
  lratio->Draw("same");//*/
  


  
}
