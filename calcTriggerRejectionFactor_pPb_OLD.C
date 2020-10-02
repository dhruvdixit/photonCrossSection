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

void calcTriggerRejectionFactor_pPb(){
  
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

  //TFile* fin = new TFile(Form("%sfout_7_26bins_13cdef_allpPb_forRTrig_MBEG1EG2exlusion_tof20_eCross5_newExoticity_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_7_26bins_13cdef_allpPbNoNew_forRTrig_MBEG1EG2exlusion_tof20_eCross5_newExoticity_noNorm.root", path.Data()), "READ");
  TFile* fin = new TFile(Form("%srfOutput/pPOutput/fout_7_26bins_13cdef_allruns_forRTrig_MBEG1EG2exlusion_tof20_eCross5_newExoticity_noNorm.root", path.Data()), "READ");

  if(!fin){
    cout << "cannot find file" << endl;
    return;
  }

  TH1F* hMB_E = (TH1F*)fin->Get("hMB_E");
  TH1F* hEG1_E = (TH1F*)fin->Get("hEG1_E");
  TH1F* hEG2_E = (TH1F*)fin->Get("hEG2_E");
  TH1F* hNormalizer = (TH1F*)fin->Get("hNormalizer");

  if(!hMB_E){
    cout << "cannot find MB hist" << endl;
    return;
  }
  if(!hEG1_E){
    cout << "cannot find EG1 hist" << endl;
    return;
  }
  if(!hEG2_E){
    cout << "cannot find EG2 hist" << endl;
    return;
  }
  if(!hNormalizer){
    cout << "cannot find normalizer hist" << endl;
    return;
  }
  
  Double_t numEvents_MB = hNormalizer->GetBinContent(11);
  Double_t numEvents_EG1 = hNormalizer->GetBinContent(12);
     Double_t numEvents_EG2 = hNormalizer->GetBinContent(13);

  TH1F* RTrig = (TH1F*)fin->Get("hReco_pt");
  RTrig->SetName("RTrig");
  RTrig->SetTitle(";E_{T} [GeV];R_{trig}");
  
  for(int i = 1; i < hMB_E->GetNbinsX()+1; i++){
    double dE = hMB_E->GetBinWidth(i);
    
    double contentMB = hMB_E->GetBinContent(i);
    double tempMB = (contentMB)/((double)numEvents_MB*dE);
    double errorMB = hMB_E->GetBinError(i);
    double tempErrMB = (errorMB)/((double)numEvents_MB*dE);
    //if(numEvents_MB && tempErrMB/tempMB < 1.0){
      hMB_E->SetBinContent(i,tempMB);
      hMB_E->SetBinError(i, tempErrMB);
      //}
  //else {
  //  hMB_E->SetBinContent(i,0);
  //  hMB_E->SetBinError(i, 0);
  //}
    
    double contentEG1 = hEG1_E->GetBinContent(i);
    double tempEG1 = (contentEG1)/((double)numEvents_EG1*dE);
    double errorEG1 = hEG1_E->GetBinError(i);
    double tempErrEG1 = (errorEG1)/((double)numEvents_EG1*dE);
    //if(numEvents_EG1 && tempErrEG1/tempEG1 < 1.0) 
    {
      hEG1_E->SetBinContent(i,tempEG1);
      hEG1_E->SetBinError(i, tempErrEG1);
    }
    
    //cout << tempErrEG1/tempEG1 << "\t" << tempErrMB/tempMB << endl;
    RTrig->SetBinContent(i, 0);
    RTrig->SetBinError(i, 0);
    if(tempMB){
      double contentRF = tempEG1/tempMB;
      double errorRF = TMath::Sqrt(TMath::Power(tempErrEG1,2) +TMath::Power(tempErrMB,2));
      //cout << contentRF << "\t" << errorRF << "\t" << errorRF/contentRF << endl;
      //if(errorRF/contentRF < 1.0){
      RTrig->SetBinContent(i, contentRF);
      RTrig->SetBinError(i, errorRF);
      //}
    }//*/
  }//end for
  
  hEG1_E->SetLineColor(kOrange);
  hMB_E->SetLineColor(kBlack);
  hEG1_E->SetMarkerColor(kOrange);
  hMB_E->SetMarkerColor(kBlack);
  hEG1_E->SetMarkerStyle(kFullCircle);
  hMB_E->SetMarkerStyle(kFullCircle);

  TLegend* ls = new TLegend(0.6, 0.7,0.85, 0.85);
  ls->AddEntry((TObject*)0, "Cluster Spectra", "");
  ls->AddEntry((TObject*)0, "p-Pb #sqrt{s_{NN}} = 5.02 TeV", "");
  ls->AddEntry(hMB_E, "Minimum bias trigger (MB)");
  ls->AddEntry(hEG1_E, "EMCal L1 trigger (EG1)");
  
  TCanvas* c1 = new TCanvas();
  c1->SetLogy();
  hMB_E->GetXaxis()->SetRangeUser(0, 40);
  hMB_E->GetYaxis()->SetRangeUser(1e-9, 1);
  hMB_E->SetTitle(";E_{T} [GeV]; #frac{1}{N_{ev}}x#frac{dN}{dE_{T}} [a.u.]");
  hMB_E->Draw("e1");
  hEG1_E->Draw("samee1");
  ls->Draw("same");

  TCanvas* c2 = new TCanvas();
  c2->SetLogy();
  TH1F* Rtrig = (TH1F*)hEG1_E->Clone();
  Rtrig->SetName("Rtrig");
  Rtrig->SetTitle(";E_{T} [GeV];R_{trig}");
  Rtrig->Divide(hMB_E);
  Rtrig->SetLineColor(kBlue);
  Rtrig->SetMarkerColor(kBlue);
  Rtrig->GetXaxis()->SetRangeUser(0, 40);
  //Rtrig->GetYaxis()->SetRangeUser(2e-4, 2e4);
  Rtrig->GetYaxis()->SetRangeUser(1e-3, 2e5);
  Rtrig->Draw("e1");

  cout << "14, 40" << endl;
  Rtrig->Fit("pol0", "", "", 14, 40);
  TF1* fitEG1 = (TF1*)Rtrig->GetFunction("pol0");fitEG1->SetName("fitEG1");
  fitEG1->SetLineColorAlpha(kCyan, 0.25);
  fitEG1->SetLineWidth(10);
  cout << "************************************************" << endl;
  /*cout << "8, 40" << endl;
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
  cout << "************************************************" << endl;//*/

  
  TLine *scalar13d = new TLine(0, 5948.27 , 40, 5948.27);
  scalar13d->SetLineColorAlpha(kGray, 1.0);
  scalar13d->SetLineWidth(2);
  scalar13d->Draw("same");

  TLine *fitErwannEG1 = new TLine(0, 6724 , 40, 6724);
  fitErwannEG1->SetLineColorAlpha(kBlack, 1.0);
  fitErwannEG1->SetLineWidth(1);
  fitErwannEG1->Draw("same");

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
  lRF->SetHeader("ALICE EMCal L1 Trigger turn on curve, p-Pb #sqrt{s_{NN}} = 5.02 TeV");
  lRF->SetNColumns(2);
  lRF->AddEntry(Rtrig, "EG1/MB", "p");
  lRF->AddEntry(fitEG1, "Contant Fit (14, 40) GeV, R_{trig} = 5826#pm395, #frac{#chi^{2}}{NDf} = 13/9", "l");
  lRF->AddEntry(scalar13d, "Scalar method 13d, R_{trig} = 5948.27#pm0.0021", "l");
  lRF->AddEntry(fitErwannEG1, "Erwan's result, R_{trig} = 6724#pm330", "l");
  lRF->Draw("same");

  //TFile* fout = new TFile("/global/homes/d/ddixit/photonCrossSection/rfOutput/noNormResults_17qAll.root", "RECREATE");
  //Rtrig->Write("RTrig");
  //fout->Close();

  TCanvas* c4 = new TCanvas();
  c4->SetLogy();
  hMB_E->GetXaxis()->SetRangeUser(0, 40);
  hMB_E->GetYaxis()->SetRangeUser(1e-9, 1);
  hMB_E->SetTitle(";E_{T} [GeV]; #frac{1}{N_{ev}}x#frac{dN}{dE_{T}} [a.u.]");
  hMB_E->Draw("e1");
  hEG1_E->Draw("samee1");


  TH1F* scale1 = (TH1F*)hEG1_E->Clone(); scale1->SetName("scale1"); scale1->Scale(1.0/5948.0);scale1->SetLineColor(kRed); scale1->SetMarkerColor(kRed);scale1->Draw("samee1");
  TH1F* scale2 = (TH1F*)hEG1_E->Clone(); scale2->SetName("scale2"); scale2->Scale(1.0/5826.0);scale2->SetLineColor(kBlue); scale2->SetMarkerColor(kBlue);scale2->Draw("samee1");
  TH1F* scale3 = (TH1F*)hEG1_E->Clone(); scale3->SetName("scale3"); scale3->Scale(1.0/6724.0);scale3->SetLineColor(kGreen); scale3->SetMarkerColor(kGreen);scale3->Draw("samee1");
  
  TLegend* lscale = new TLegend(0.65, 0.65,0.9, 0.9);
  lscale->AddEntry((TObject*)0, "Cluster Spectra", "");
  lscale->AddEntry((TObject*)0, "p-Pb #sqrt{s_{NN}} = 5.02 TeV", "");
  lscale->AddEntry(hMB_E, "Minimum bias trigger (MB)");
  lscale->AddEntry(hEG1_E, "EMCal L1 trigger (EG1)");
  lscale->AddEntry(scale1, "Using RF = 5948, Scalar method");
  lscale->AddEntry(scale2, "Using RF = 5826, Cluster spectra method");
  lscale->AddEntry(scale3, "Using RF = 6724, Cluster spectra method Erwann's");
  lscale->Draw("same");

  TH1F* ratio1 = (TH1F*)scale1->Clone(); ratio1->Divide(hMB_E);
  TH1F* ratio2 = (TH1F*)scale2->Clone(); ratio2->Divide(hMB_E);
  TH1F* ratio3 = (TH1F*)scale3->Clone(); ratio3->Divide(hMB_E);
  
  TLegend* lratio = new TLegend(0.15, 0.75, 0.45, 0.85);
  ratio1->SetTitle(";E_{T} [GeV]; #frac{Scaled EG1 spectra}{MB spectra}");
  lratio->SetBorderSize(0);
  lratio->SetTextSize(0.025);
  lratio->AddEntry(ratio1, "Using RF = 5948, Scalar method");
  lratio->AddEntry(ratio2, "Using RF = 5826, Cluster spectra method");
  lratio->AddEntry(ratio3, "Using RF = 6724, Cluster spectra method Erwann's");

  TCanvas* c5 = new TCanvas();
  ratio1->GetXaxis()->SetRangeUser(0, 40);
  TLine *line2 = new TLine(0, 1, 40, 1);
  line2->SetLineColorAlpha(kBlack, 0.5);
  line2->SetLineWidth(7);

  ratio1->Draw("e1");
  ratio2->Draw("samee1");
  ratio3->Draw("samee1");
  line2->Draw("same");
  lratio->Draw("same");//*/
  


  
}
