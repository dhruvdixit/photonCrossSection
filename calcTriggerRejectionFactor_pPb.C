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

/*#include <algorithm>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bitset>
#include <bits/stdc++.h>
#include <cstring>//*/

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
  gStyle->SetOptStat(0);
  gStyle->SetCanvasPreferGL(kTRUE);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/rfOutput/pPOutput";
  
  //13d
  TFile* file_13d = new TFile(Form("%s/StdEventsAndClusterCuts/fout_6_26bins_forRTrigEG_13d_Allruns_noThresh_phySel.root", path.Data()), "READ");
  //TFile* file_13d = new TFile(Form("%s/13dOutput/GoodRunsCheck/fout_7_26bins_forRTrig_13d_all10runs_noSkimnoTrigOverlap_no195871.root", path.Data()), "READ");
  TH1F* hEG1_13d = (TH1F*)file_13d->Get("hEG1_E");
  TH1F* hEG2_13d = (TH1F*)file_13d->Get("hEG2_E");
  
  //13e
  TFile* file_13e = new TFile(Form("%s/StdEventsAndClusterCuts/fout_6_26bins_forRTrigEG_13e_Allruns_noThresh_phySel.root", path.Data()), "READ");
  TH1F* hEG1_13e = (TH1F*)file_13e->Get("hEG1_E");
  TH1F* hEG2_13e = (TH1F*)file_13e->Get("hEG2_E");

  //13f
  TFile* file_13f = new TFile(Form("%s/StdEventsAndClusterCuts/fout_6_26bins_forRTrigEG_13f_Allruns_noThresh_phySel.root", path.Data()), "READ");
  TH1F* hEG1_13f = (TH1F*)file_13f->Get("hEG1_E");
  TH1F* hEG2_13f = (TH1F*)file_13f->Get("hEG2_E");

  //13def
  //TFile* file_13def = new TFile(Form("%s/StdEventsAndClusterCuts/fout_7_26bins_forRTrigMB_13def_Allruns_noThresh_phySel.root", path.Data()), "READ");
  TFile* file_13def = new TFile(Form("%s/Nonlin/fout_7_26bins_forRTrig_13def_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorrnonlin_fixedEventCount_noNorm.root", path.Data()), "READ");
  TH1F* hEG1_13def = (TH1F*)file_13def->Get("hEG1_E");
  TH1F* hEG2_13def = (TH1F*)file_13def->Get("hEG2_E");
  TH1F* hNormalizer_13def = (TH1F*)file_13def->Get("hNormalizer");
  //TH1F* hMB_13cdef = (TH1F*)file_13def->Get("hMB_E");
  Double_t numEvents_EG1 = hNormalizer_13def->GetBinContent(12);
  Double_t numEvents_EG2 = hNormalizer_13def->GetBinContent(13);
  hEG1_13def->Scale(1.0/numEvents_EG1);
  hEG2_13def->Scale(1.0/numEvents_EG2);
    
  //13cdef
  //TFile* file_13cdef = new TFile(Form("%s/StdEventsAndClusterCuts/fout_7_26bins_forRTrigMB_13cdef_Allruns_noThresh_phySel.root", path.Data()), "READ");
  //TFile* file_13cdef = new TFile(Form("%s/Nonlin/fout_7_26bins_forRTrig_13cdef_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorrnonlin_fixedEventCount_noNorm.root", path.Data()), "READ");
  TFile* file_13cdef = new TFile(Form("%s/Nonlin/UsingCScode/wNL/13c/fout_1_26bins_firstEvent0_13c_6runs_kINT7_nonLinCorr_wClusters_onlyClusEtaPhiEPT_addCellMaxCrossOnly_emcalhContinue_EMCALCells_otherClusCuts_StdCuts_EX0PurityFit_NoISO_RFCheck_RFbinning_noNorm.root", path.Data()), "READ");
  TH1F* hMB_13cdef = (TH1F*)file_13cdef->Get("hMB_E");
  TH1F* hNormalizer_13cdef = (TH1F*)file_13cdef->Get("hNormalizer");
  Double_t numEvents_MB = hNormalizer_13cdef->GetBinContent(11);
  cout << "Num MB events: " << numEvents_MB << endl;
  cout << "Num EG1 events: " << numEvents_EG1 << endl;
  cout << "Num EG2 events: " << numEvents_EG2 << endl;
  hMB_13cdef->Scale(1/numEvents_MB);

  const int nbinscluster = 26;
  Double_t clusterbins[nbinscluster+1] = {0.00, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 11.00, 12.00, 13.00, 14.00, 15.00, 16.00, 17.00, 18.00, 20.00, 22.00, 26.00, 30.00, 35.00, 40.00, 50.00, 60.00};//nbinscluster = 26, rejection factor binning
  //Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning
  //RF_EG1 = EG1/MB, RF_EG2 = EG2/MB = RF_EGA = EG1/EG2
  TH1F* hRF_EG1_13d = new TH1F("hRF_EG1_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hRF_EG2_13d = new TH1F("hRF_EG2_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hRF_EGA_13d = new TH1F("hRF_EGA_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hRF_EG1_13e = new TH1F("hRF_EG1_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hRF_EG2_13e = new TH1F("hRF_EG2_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hRF_EGA_13e = new TH1F("hRF_EGA_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hRF_EG1_13f = new TH1F("hRF_EG1_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hRF_EG2_13f = new TH1F("hRF_EG2_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hRF_EGA_13f = new TH1F("hRF_EGA_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hRF_EG1_13def = new TH1F("hRF_EG1_13def", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hRF_EG2_13def = new TH1F("hRF_EG2_13def", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hRF_EGA_13def = new TH1F("hRF_EGA_13def", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  
  for(int i = 1; i < hMB_13cdef->GetNbinsX()+1; i++){
    double contentMB = hMB_13cdef->GetBinContent(i);
    double errorMB = hMB_13cdef->GetBinError(i);

    //13d
    double contentEG1_13d = hEG1_13d->GetBinContent(i);
    double errorEG1_13d = hEG1_13d->GetBinError(i); 
    hRF_EG1_13d->SetBinContent(i, 0);
    hRF_EG1_13d->SetBinError(i, 0);
    double contentEG2_13d = hEG2_13d->GetBinContent(i);
    double errorEG2_13d = hEG2_13d->GetBinError(i); 
    hRF_EG2_13d->SetBinContent(i, 0);
    hRF_EG2_13d->SetBinError(i, 0);
    if(contentEG2_13d){
      double contentRF_EGA_13d = contentEG1_13d/contentEG2_13d;
      double errorRF_EGA_13d = TMath::Sqrt(TMath::Power(errorEG1_13d/contentEG1_13d,2) + TMath::Power(errorEG2_13d/contentEG2_13d,2))*contentRF_EGA_13d;   
      hRF_EGA_13d->SetBinContent(i, contentRF_EGA_13d);
      hRF_EGA_13d->SetBinError(i, errorRF_EGA_13d);
    }
    
    //13e
    double contentEG1_13e = hEG1_13e->GetBinContent(i);
    double errorEG1_13e = hEG1_13e->GetBinError(i); 
    hRF_EG1_13e->SetBinContent(i, 0);
    hRF_EG1_13e->SetBinError(i, 0);
    double contentEG2_13e = hEG2_13e->GetBinContent(i);
    double errorEG2_13e = hEG2_13e->GetBinError(i); 
    hRF_EG2_13e->SetBinContent(i, 0);
    hRF_EG2_13e->SetBinError(i, 0);
    if(contentEG2_13e){
      double contentRF_EGA_13e = contentEG1_13e/contentEG2_13e;
      double errorRF_EGA_13e = TMath::Sqrt(TMath::Power(errorEG1_13e/contentEG1_13e,2) + TMath::Power(errorEG2_13e/contentEG2_13e,2))*contentRF_EGA_13e;   
      hRF_EGA_13e->SetBinContent(i, contentRF_EGA_13e);
      hRF_EGA_13e->SetBinError(i, errorRF_EGA_13e);
    }

    //13f
    double contentEG1_13f = hEG1_13f->GetBinContent(i);
    double errorEG1_13f = hEG1_13f->GetBinError(i); 
    hRF_EG1_13f->SetBinContent(i, 0);
    hRF_EG1_13f->SetBinError(i, 0);
    double contentEG2_13f = hEG2_13f->GetBinContent(i);
    double errorEG2_13f = hEG2_13f->GetBinError(i); 
    hRF_EG2_13f->SetBinContent(i, 0);
    hRF_EG2_13f->SetBinError(i, 0);
    if(contentEG2_13f){
      double contentRF_EGA_13f = contentEG1_13f/contentEG2_13f;
      double errorRF_EGA_13f = TMath::Sqrt(TMath::Power(errorEG1_13f/contentEG1_13f,2) + TMath::Power(errorEG2_13f/contentEG2_13f,2))*contentRF_EGA_13f;   
      hRF_EGA_13f->SetBinContent(i, contentRF_EGA_13f);
      hRF_EGA_13f->SetBinError(i, errorRF_EGA_13f);
    }

    //13def
    double contentEG1_13def = hEG1_13def->GetBinContent(i);
    double errorEG1_13def = hEG1_13def->GetBinError(i); 
    hRF_EG1_13def->SetBinContent(i, 0);
    hRF_EG1_13def->SetBinError(i, 0);
    double contentEG2_13def = hEG2_13def->GetBinContent(i);
    double errorEG2_13def = hEG2_13def->GetBinError(i); 
    hRF_EG2_13def->SetBinContent(i, 0);
    hRF_EG2_13def->SetBinError(i, 0);
    if(contentEG2_13def){
      double contentRF_EGA_13def = contentEG1_13def/contentEG2_13def;
      double errorRF_EGA_13def = TMath::Sqrt(TMath::Power(errorEG1_13def/contentEG1_13def,2) + TMath::Power(errorEG2_13def/contentEG2_13def,2))*contentRF_EGA_13def;   
      hRF_EGA_13def->SetBinContent(i, contentRF_EGA_13def);
      hRF_EGA_13def->SetBinError(i, errorRF_EGA_13def);
    }
    
    if(contentMB){
      //EG1 RF
      double contentRF_EG1_13d = contentEG1_13d/contentMB;
      double errorRF_EG1_13d = TMath::Sqrt(TMath::Power(errorEG1_13d/contentRF_EG1_13d,2) +TMath::Power(errorMB/contentMB,2))*contentRF_EG1_13d;   
      hRF_EG1_13d->SetBinContent(i, contentRF_EG1_13d);
      hRF_EG1_13d->SetBinError(i, errorRF_EG1_13d);

      double contentRF_EG1_13e = contentEG1_13e/contentMB;
      double errorRF_EG1_13e = TMath::Sqrt(TMath::Power(errorEG1_13e/contentRF_EG1_13e,2) +TMath::Power(errorMB/contentMB,2))*contentRF_EG1_13e;   
      hRF_EG1_13e->SetBinContent(i, contentRF_EG1_13e);
      hRF_EG1_13e->SetBinError(i, errorRF_EG1_13e);

      double contentRF_EG1_13f = contentEG1_13f/contentMB;
      double errorRF_EG1_13f = TMath::Sqrt(TMath::Power(errorEG1_13f/contentRF_EG1_13f,2) +TMath::Power(errorMB/contentMB,2))*contentRF_EG1_13f;   
      hRF_EG1_13f->SetBinContent(i, contentRF_EG1_13f);
      hRF_EG1_13f->SetBinError(i, errorRF_EG1_13f);

      double contentRF_EG1_13def = (contentEG1_13def)/(contentMB);
      double errorRF_EG1_13def = TMath::Sqrt(TMath::Power(errorEG1_13def/contentRF_EG1_13def,2) +TMath::Power(errorMB/contentMB,2))*contentRF_EG1_13def;   
      hRF_EG1_13def->SetBinContent(i, contentRF_EG1_13def);
      hRF_EG1_13def->SetBinError(i, errorRF_EG1_13def);

      //EG2 RF
      double contentRF_EG2_13d = contentEG2_13d/contentMB;
      double errorRF_EG2_13d = TMath::Sqrt(TMath::Power(errorEG2_13d/contentRF_EG2_13d,2) +TMath::Power(errorMB/contentMB,2))*contentRF_EG2_13d;   
      hRF_EG2_13d->SetBinContent(i, contentRF_EG2_13d);
      hRF_EG2_13d->SetBinError(i, errorRF_EG2_13d);

      double contentRF_EG2_13e = contentEG2_13e/contentMB;
      double errorRF_EG2_13e = TMath::Sqrt(TMath::Power(errorEG2_13e/contentRF_EG2_13e,2) +TMath::Power(errorMB/contentMB,2))*contentRF_EG2_13e;   
      hRF_EG2_13e->SetBinContent(i, contentRF_EG2_13e);
      hRF_EG2_13e->SetBinError(i, errorRF_EG2_13e);

      double contentRF_EG2_13f = contentEG2_13f/contentMB;
      double errorRF_EG2_13f = TMath::Sqrt(TMath::Power(errorEG2_13f/contentRF_EG2_13f,2) +TMath::Power(errorMB/contentMB,2))*contentRF_EG2_13f;   
      hRF_EG2_13f->SetBinContent(i, contentRF_EG2_13f);
      hRF_EG2_13f->SetBinError(i, errorRF_EG2_13f);

      double contentRF_EG2_13def = (contentEG2_13def)/(contentMB);
      double errorRF_EG2_13def = TMath::Sqrt(TMath::Power(errorEG2_13def/contentRF_EG2_13def,2) +TMath::Power(errorMB/contentMB,2))*contentRF_EG2_13def;   
      hRF_EG2_13def->SetBinContent(i, contentRF_EG2_13def);
      hRF_EG2_13def->SetBinError(i, errorRF_EG2_13def);
    }//*/
      }//end for
  
  hMB_13cdef->SetLineColor(kBlack);
  hMB_13cdef->SetMarkerColor(kBlack);
  hMB_13cdef->SetMarkerStyle(kFullCircle);
  hMB_13cdef->SetMarkerSize(1);

  hEG1_13d->SetLineColor(kGreen);
  hEG1_13d->SetMarkerColor(kGreen);
  hEG1_13d->SetMarkerStyle(kOpenCircle);
  hEG1_13d->SetMarkerSize(2);
  hEG1_13e->SetLineColor(kMagenta);
  hEG1_13e->SetMarkerColor(kMagenta);
  hEG1_13e->SetMarkerStyle(kOpenCircle);
  hEG1_13e->SetMarkerSize(2);
  hEG1_13f->SetLineColor(kCyan);
  hEG1_13f->SetMarkerColor(kCyan);
  hEG1_13f->SetMarkerStyle(kOpenCircle);
  hEG1_13f->SetMarkerSize(2);
  hEG1_13def->SetLineColor(kBlue);
  hEG1_13def->SetMarkerColor(kBlue);
  hEG1_13def->SetMarkerStyle(kFullCircle);
  hEG1_13def->SetMarkerSize(1);

  hEG2_13d->SetLineColor(kGreen);
  hEG2_13d->SetMarkerColor(kGreen);
  hEG2_13d->SetMarkerStyle(kOpenSquare);
  hEG2_13d->SetMarkerSize(2);
  hEG2_13e->SetLineColor(kMagenta);
  hEG2_13e->SetMarkerColor(kMagenta);
  hEG2_13e->SetMarkerStyle(kOpenSquare);
  hEG2_13e->SetMarkerSize(2);
  hEG2_13f->SetLineColor(kCyan);
  hEG2_13f->SetMarkerColor(kCyan);
  hEG2_13f->SetMarkerStyle(kOpenSquare);
  hEG2_13f->SetMarkerSize(2);
  hEG2_13def->SetLineColor(kRed);
  hEG2_13def->SetMarkerColor(kRed);
  hEG2_13def->SetMarkerStyle(kFullCircle);
  hEG2_13def->SetMarkerSize(1);

  

  TLegend* ls = new TLegend(0.65, 0.7,0.88, 0.88);
  ls->SetNColumns(1);
  ls->AddEntry((TObject*)0, "Raw Cluster Spectra", "");
  ls->AddEntry((TObject*)0, "p-Pb #sqrt{s_{NN}} = 5.02 TeV", "");
  ls->AddEntry(hMB_13cdef, "Minimum bias trigger (MB)");
  ls->AddEntry(hEG1_13def, "EMCal EG1 #gamma trigger");
  ls->AddEntry(hEG2_13def, "EMCal EG2 #gamma trigger");
  //ls->AddEntry(hEG1_13d, "13d (EG1)");
  //ls->AddEntry(hEG2_13d, "13d (EG2)");
  //ls->AddEntry(hEG1_13e, "13e (EG1)");
  //ls->AddEntry(hEG2_13e, "13e (EG2)");
  //ls->AddEntry(hEG1_13f, "13f (EG1)");
  //ls->AddEntry(hEG2_13f, "13f (EG2)");
  
  TCanvas* c1 = new TCanvas("c1", "c1", 1200, 600);
  c1->SetLogy();
  hMB_13cdef->GetXaxis()->SetRangeUser(0, 40);
  hMB_13cdef->GetYaxis()->SetRangeUser(1e-9, 1);
  hMB_13cdef->SetTitle(";E_{T} [GeV]; #frac{1}{N_{ev}}x#frac{dN}{dE_{T}} [a.u.]");
  hMB_13cdef->Draw("e1");
  hEG1_13def->Draw("samee1");
  hEG2_13def->Draw("samee1");
  //hEG1_13d->Draw("samee1");
  //hEG1_13e->Draw("samee1");
  //hEG1_13f->Draw("samee1");
  //hEG2_13d->Draw("samee1");
  //hEG2_13e->Draw("samee1");
  //hEG2_13f->Draw("samee1");
  ls->Draw("same");
  //c1->SaveAs("RFspectra_pPb.pdf");//Save image for p-Pb cluster spectra
  //c1->SaveAs("RFspectra_pPb.png");//Save image for p-Pb cluster spectra
  
  //RF
  /*hRF_EG1_13d->SetLineColor(kGreen);
  hRF_EG1_13d->SetMarkerColor(kGreen);
  hRF_EG1_13d->SetMarkerStyle(kOpenCircle);
  hRF_EG1_13d->SetMarkerSize(2);
  hRF_EG1_13e->SetLineColor(kMagenta);
  hRF_EG1_13e->SetMarkerColor(kMagenta);
  hRF_EG1_13e->SetMarkerStyle(kOpenCircle);
  hRF_EG1_13e->SetMarkerSize(2);
  hRF_EG1_13f->SetLineColor(kCyan);
  hRF_EG1_13f->SetMarkerColor(kCyan);
  hRF_EG1_13f->SetMarkerStyle(kOpenCircle);
  hRF_EG1_13f->SetMarkerSize(2);//*/
  hRF_EG1_13def->SetLineColor(kBlue);
  hRF_EG1_13def->SetMarkerColor(kBlue);
  hRF_EG1_13def->SetMarkerStyle(kFullCircle);
  hRF_EG1_13def->SetMarkerSize(1);
  
  /*hRF_EG2_13d->SetLineColor(kGreen);
  hRF_EG2_13d->SetMarkerColor(kGreen);
  hRF_EG2_13d->SetMarkerStyle(kOpenSquare);
  hRF_EG2_13d->SetMarkerSize(2);
  hRF_EG2_13e->SetLineColor(kMagenta);
  hRF_EG2_13e->SetMarkerColor(kMagenta);
  hRF_EG2_13e->SetMarkerStyle(kOpenSquare);
  hRF_EG2_13e->SetMarkerSize(2);
  hRF_EG2_13f->SetLineColor(kCyan);
  hRF_EG2_13f->SetMarkerColor(kCyan);
  hRF_EG2_13f->SetMarkerStyle(kOpenSquare);
  hRF_EG2_13f->SetMarkerSize(2);//*/
  hRF_EG2_13def->SetLineColor(kRed);
  hRF_EG2_13def->SetMarkerColor(kRed);
  hRF_EG2_13def->SetMarkerStyle(kFullCircle);
  hRF_EG2_13def->SetMarkerSize(1);
  
  /*hRF_EGA_13d->SetLineColor(kGreen);
  hRF_EGA_13d->SetMarkerColor(kGreen);
  hRF_EGA_13d->SetMarkerStyle(kOpenDiamond);
  hRF_EGA_13d->SetMarkerSize(2);
  hRF_EGA_13e->SetLineColor(kMagenta);
  hRF_EGA_13e->SetMarkerColor(kMagenta);
  hRF_EGA_13e->SetMarkerStyle(kOpenDiamond);
  hRF_EGA_13e->SetMarkerSize(2);
  hRF_EGA_13f->SetLineColor(kCyan);
  hRF_EGA_13f->SetMarkerColor(kCyan);
  hRF_EGA_13f->SetMarkerStyle(kOpenDiamond);
  hRF_EGA_13f->SetMarkerSize(2);//*/
  hRF_EGA_13def->SetLineColor(kBlack);
  hRF_EGA_13def->SetMarkerColor(kBlack);
  hRF_EGA_13def->SetMarkerStyle(kFullCircle);
  hRF_EGA_13def->SetMarkerSize(1);

  

  
  
  TCanvas* c2 = new TCanvas("c2", "c2", 1600, 800);
  c2->SetLogy();
  hRF_EG1_13def->GetYaxis()->SetRangeUser(5e-4, 5e4);
  hRF_EG1_13def->GetXaxis()->SetRangeUser(0, 40);
  hRF_EG1_13def->Draw("e1");
  hRF_EG2_13def->Draw("samee1");
  hRF_EGA_13def->Draw("samee1");


  hRF_EG1_13def->Fit("pol0", "0", "", 14, 40);
  hRF_EG2_13def->Fit("pol0", "0", "", 10, 40);
  hRF_EGA_13def->Fit("pol0", "0", "", 16, 40);
  TF1* fitEG1 = (TF1*)hRF_EG1_13def->GetFunction("pol0");
  fitEG1->SetName("fitEG1");
  double tmEG1_13def = fitEG1->GetParameter(0);
  double tmEG1_Er_13def = fitEG1->GetParError(0);
  TLine *lineEG1 = new TLine(0, tmEG1_13def, 40, tmEG1_13def);
  lineEG1->SetLineColorAlpha(kBlue, 0.2);
  lineEG1->SetLineWidth(8);
  lineEG1->Draw("same");
  TF1* fitEG2 = (TF1*)hRF_EG2_13def->GetFunction("pol0");
  fitEG2->SetName("fitEG2");
  double tmEG2_13def = fitEG2->GetParameter(0);
  double tmEG2_Er_13def = fitEG2->GetParError(0);
  TLine *lineEG2 = new TLine(0, tmEG2_13def, 40, tmEG2_13def);
  lineEG2->SetLineColorAlpha(kRed, 0.2);
  lineEG2->SetLineWidth(2);
  lineEG2->Draw("same");
    

  TF1* fitEGA = (TF1*)hRF_EGA_13def->GetFunction("pol0");
  fitEGA->SetName("fitEGA");
  double tmEGA_13def = fitEGA->GetParameter(0);
  double tmEGA_Er_13def = fitEGA->GetParError(0);
  TLine *lineEGA = new TLine(0, tmEGA_13def, 40, tmEGA_13def);
  lineEGA->SetLineColorAlpha(kBlack, 0.2);
  lineEGA->SetLineWidth(1);
  lineEGA->Draw("same");

  TLegend* lsRF = new TLegend(0.35, 0.13,0.85, 0.4);
  lsRF->SetHeader("ALICE Performance, p-Pb #sqrt{s_{NN}} = 5.02 TeV");
  lsRF->SetNColumns(2);
  lsRF->AddEntry(hRF_EG1_13def, "EG1/MB");
  lsRF->AddEntry(lineEG1, Form("Constant Fit (14, 40) GeV, R_{trig} = %.0f #pm %.0f", tmEG1_13def, tmEG1_Er_13def), "l");
  lsRF->AddEntry(hRF_EG2_13def, "EG2/MB");
  lsRF->AddEntry(lineEG2, Form("Constant Fit (10, 40) GeV, R_{trig} = %.0f #pm %.0f", tmEG2_13def, tmEG2_Er_13def), "l");
  lsRF->AddEntry(hRF_EGA_13def, "EG1/EG2");
  lsRF->AddEntry(lineEGA, Form("Constant Fit (16, 40) GeV, R_{trig} = %.2f #pm %.2f", tmEGA_13def, tmEGA_Er_13def), "l");
  lsRF->Draw("same");
  //c2->SaveAs("RFTurnOnCurve_pPb.pdf");//Save image for p-Pb cluster spectra
  //c2->SaveAs("RFTurnOnCurve_pPb.png");//Save image for p-Pb cluster spectra
  
  //hRF_EGA_13d->Fit("pol0", "QRM+", "", 16, 40);
  //hRF_EGA_13e->Fit("pol0", "QRM+", "", 16, 40);
  //hRF_EGA_13f->Fit("pol0", "QRM+", "", 16, 40);
  //hRF_EG1_13d->Fit("pol0", "QRM+", "", 14, 40);
  //hRF_EG1_13e->Fit("pol0", "QRM+", "", 14, 40);
  //hRF_EG1_13f->Fit("pol0", "QRM+", "", 14, 40);
  //hRF_EG2_13d->Fit("pol0", "QRM+", "", 10, 40);
  //hRF_EG2_13e->Fit("pol0", "QRM+", "", 10, 40);
  //hRF_EG2_13f->Fit("pol0", "QRM+", "", 10, 40);

  /*double tm_eg1_13d = hRF_EG1_13d->GetFunction("pol0")->GetParameter(0);
  double tm_eg1_13e = hRF_EG1_13e->GetFunction("pol0")->GetParameter(0);
  double tm_eg1_13f = hRF_EG1_13f->GetFunction("pol0")->GetParameter(0);
  double tm_eg1_13def = hRF_EG1_13def->GetFunction("pol0")->GetParameter(0);
  double tm_eg2_13d = hRF_EG2_13d->GetFunction("pol0")->GetParameter(0);
  double tm_eg2_13e = hRF_EG2_13e->GetFunction("pol0")->GetParameter(0);
  double tm_eg2_13f = hRF_EG2_13f->GetFunction("pol0")->GetParameter(0);
  double tm_eg2_13def = hRF_EG2_13def->GetFunction("pol0")->GetParameter(0);
  double tm_ega_13d = hRF_EGA_13d->GetFunction("pol0")->GetParameter(0);
  double tm_ega_13e = hRF_EGA_13e->GetFunction("pol0")->GetParameter(0);
  double tm_ega_13f = hRF_EGA_13f->GetFunction("pol0")->GetParameter(0);
  double tm_ega_13def = hRF_EGA_13def->GetFunction("pol0")->GetParameter(0);
  double tm_eg12a_13d = tm_eg2_13d*tm_ega_13d;
  double tm_eg12a_13e = tm_eg2_13e*tm_ega_13e;
  double tm_eg12a_13f = tm_eg2_13f*tm_ega_13f;
  double tm_eg12a_13def = tm_eg2_13def*tm_ega_13def;
  
  double tmEr_eg1_13d = hRF_EG1_13d->GetFunction("pol0")->GetParError(0);
  double tmEr_eg1_13e = hRF_EG1_13e->GetFunction("pol0")->GetParError(0);
  double tmEr_eg1_13f = hRF_EG1_13f->GetFunction("pol0")->GetParError(0);
  double tmEr_eg1_13def = hRF_EG1_13def->GetFunction("pol0")->GetParError(0);
  double tmEr_eg2_13d = hRF_EG2_13d->GetFunction("pol0")->GetParError(0);
  double tmEr_eg2_13e = hRF_EG2_13e->GetFunction("pol0")->GetParError(0);
  double tmEr_eg2_13f = hRF_EG2_13f->GetFunction("pol0")->GetParError(0);
  double tmEr_eg2_13def = hRF_EG2_13def->GetFunction("pol0")->GetParError(0);
  double tmEr_ega_13d = hRF_EGA_13d->GetFunction("pol0")->GetParError(0);
  double tmEr_ega_13e = hRF_EGA_13e->GetFunction("pol0")->GetParError(0);
  double tmEr_ega_13f = hRF_EGA_13f->GetFunction("pol0")->GetParError(0);
  double tmEr_ega_13def = hRF_EGA_13def->GetFunction("pol0")->GetParError(0);
  double tmEr_eg12a_13d = tm_eg12a_13d*TMath::Sqrt(TMath::Power(tmEr_eg2_13d/tm_eg2_13d,2)+TMath::Power(tmEr_ega_13d/tm_ega_13d, 2));
  double tmEr_eg12a_13e = tm_eg12a_13e*TMath::Sqrt(TMath::Power(tmEr_eg2_13e/tm_eg2_13e,2)+TMath::Power(tmEr_ega_13e/tm_ega_13e, 2));
  double tmEr_eg12a_13f = tm_eg12a_13f*TMath::Sqrt(TMath::Power(tmEr_eg2_13f/tm_eg2_13f,2)+TMath::Power(tmEr_ega_13f/tm_ega_13f, 2));
  double tmEr_eg12a_13def = tm_eg12a_13def*TMath::Sqrt(TMath::Power(tmEr_eg2_13def/tm_eg2_13def,2)+TMath::Power(tmEr_ega_13def/tm_ega_13def, 2));
    
  cout << "RF EG1 13d: " << tm_eg1_13d << " +/- " << tmEr_eg1_13d << endl; 
  cout << "RF EG1 13e: " << tm_eg1_13e << " +/- " << tmEr_eg1_13e << endl; 
  cout << "RF EG1 13f: " << tm_eg1_13f << " +/- " << tmEr_eg1_13f << endl; 
  cout << "RF EG1 13def: " << tm_eg1_13def << " +/- " << tmEr_eg1_13def << endl; 
  cout << "RF EG2 13d: " << tm_eg2_13d << " +/- " << tmEr_eg2_13d << endl; 
  cout << "RF EG2 13e: " << tm_eg2_13e << " +/- " << tmEr_eg2_13e << endl; 
  cout << "RF EG2 13f: " << tm_eg2_13f << " +/- " << tmEr_eg2_13f << endl; 
  cout << "RF EG2 13def: " << tm_eg2_13def << " +/- " << tmEr_eg2_13def << endl; 
  cout << "RF EGA 13d: " << tm_ega_13d << " +/- " << tmEr_ega_13d << endl; 
  cout << "RF EGA 13e: " << tm_ega_13e << " +/- " << tmEr_ega_13e << endl; 
  cout << "RF EGA 13f: " << tm_ega_13f << " +/- " << tmEr_ega_13f << endl; 
  cout << "RF EGA 13def: " << tm_ega_13def << " +/- " << tmEr_ega_13def << endl; 
  cout << "RF EG12A 13d: " << tm_eg12a_13d << " +/- " << tmEr_eg12a_13d << endl; 
  cout << "RF EG12A 13e: " << tm_eg12a_13e << " +/- " << tmEr_eg12a_13e << endl; 
  cout << "RF EG12A 13f: " << tm_eg12a_13f << " +/- " << tmEr_eg12a_13f << endl; 
  cout << "RF EG12A 13def: " << tm_eg12a_13def << " +/- " << tmEr_eg12a_13def << endl; 

  double sm_eg1_13d = 5948;
  double sm_eg1_13e = 6313;
  double sm_eg1_13f = 5742;
  double sm_eg2_13d = 1434;
  double sm_eg2_13e = 1532;
  double sm_eg2_13f = 1402;
  double sm_ega_13d = 4.15;
  double sm_ega_13e = 4.12;
  double sm_ega_13f = 4.10;
  
  TH1F* hTMscaledEG1_13d = new TH1F("hTMscaledEG1_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEG2_13d = new TH1F("hTMscaledEG2_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEGA_13d = new TH1F("hTMscaledEGA_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEG1_13e = new TH1F("hTMscaledEG1_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEG2_13e = new TH1F("hTMscaledEG2_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEGA_13e = new TH1F("hTMscaledEGA_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEG1_13f = new TH1F("hTMscaledEG1_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEG2_13f = new TH1F("hTMscaledEG2_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEGA_13f = new TH1F("hTMscaledEGA_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEG12A_13f = new TH1F("hTMscaledEG12A_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEG1_13def = new TH1F("hTMscaledEG1_13def", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEG2_13def = new TH1F("hTMscaledEG2_13def", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEGA_13def = new TH1F("hTMscaledEGA_13def", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMscaledEG12A_13def = new TH1F("hTMscaledEG12A_13def", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  
  hTMscaledEG1_13d->SetLineColor(kGreen);
  hTMscaledEG1_13d->SetMarkerColor(kGreen);
  hTMscaledEG1_13d->SetMarkerStyle(kOpenCircle);
  hTMscaledEG1_13d->SetMarkerSize(2);
  hTMscaledEG1_13e->SetLineColor(kMagenta);
  hTMscaledEG1_13e->SetMarkerColor(kMagenta);
  hTMscaledEG1_13e->SetMarkerStyle(kOpenCircle);
  hTMscaledEG1_13e->SetMarkerSize(2);
  hTMscaledEG1_13f->SetLineColor(kCyan);
  hTMscaledEG1_13f->SetMarkerColor(kCyan);
  hTMscaledEG1_13f->SetMarkerStyle(kOpenCircle);
  hTMscaledEG1_13f->SetMarkerSize(2);
  hTMscaledEG1_13def->SetLineColor(kRed);
  hTMscaledEG1_13def->SetMarkerColor(kRed);
  hTMscaledEG1_13def->SetMarkerStyle(kOpenCircle);
  hTMscaledEG1_13def->SetMarkerSize(2);
  
  hTMscaledEG2_13d->SetLineColor(kGreen);
  hTMscaledEG2_13d->SetMarkerColor(kGreen);
  hTMscaledEG2_13d->SetMarkerStyle(kOpenSquare);
  hTMscaledEG2_13d->SetMarkerSize(2);
  hTMscaledEG2_13e->SetLineColor(kMagenta);
  hTMscaledEG2_13e->SetMarkerColor(kMagenta);
  hTMscaledEG2_13e->SetMarkerStyle(kOpenSquare);
  hTMscaledEG2_13e->SetMarkerSize(2);
  hTMscaledEG2_13f->SetLineColor(kCyan);
  hTMscaledEG2_13f->SetMarkerColor(kCyan);
  hTMscaledEG2_13f->SetMarkerStyle(kOpenSquare);
  hTMscaledEG2_13f->SetMarkerSize(2);
  hTMscaledEG2_13def->SetLineColor(kRed);
  hTMscaledEG2_13def->SetMarkerColor(kRed);
  hTMscaledEG2_13def->SetMarkerStyle(kOpenSquare);
  hTMscaledEG2_13def->SetMarkerSize(2);

  hTMscaledEGA_13d->SetLineColor(kGreen);
  hTMscaledEGA_13d->SetMarkerColor(kGreen);
  hTMscaledEGA_13d->SetMarkerStyle(kOpenDiamond);
  hTMscaledEGA_13d->SetMarkerSize(2);
  hTMscaledEGA_13e->SetLineColor(kMagenta);
  hTMscaledEGA_13e->SetMarkerColor(kMagenta);
  hTMscaledEGA_13e->SetMarkerStyle(kOpenDiamond);
  hTMscaledEGA_13e->SetMarkerSize(2);
  hTMscaledEGA_13f->SetLineColor(kCyan);
  hTMscaledEGA_13f->SetMarkerColor(kCyan);
  hTMscaledEGA_13f->SetMarkerStyle(kOpenDiamond);
  hTMscaledEGA_13f->SetMarkerSize(2);
  hTMscaledEGA_13def->SetLineColor(kRed);
  hTMscaledEGA_13def->SetMarkerColor(kRed);
  hTMscaledEGA_13def->SetMarkerStyle(kOpenDiamond);
  hTMscaledEGA_13def->SetMarkerSize(2);

  hTMscaledEG12A_13f->SetLineColor(kCyan);
  hTMscaledEG12A_13f->SetMarkerColor(kCyan);
  hTMscaledEG12A_13f->SetMarkerStyle(kOpenStar);
  hTMscaledEG12A_13f->SetMarkerSize(2);
  hTMscaledEG12A_13def->SetLineColor(kRed);
  hTMscaledEG12A_13def->SetMarkerColor(kRed);
  hTMscaledEG12A_13def->SetMarkerStyle(kOpenStar);
  hTMscaledEG12A_13def->SetMarkerSize(2);

  TH1F* hTMratioEG1_13d = new TH1F("hTMratioEG1_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEG1_13e = new TH1F("hTMratioEG1_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEG1_13f = new TH1F("hTMratioEG1_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEG1_13def = new TH1F("hTMratioEG1_13def", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEG2_13d = new TH1F("hTMratioEG2_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEG2_13e = new TH1F("hTMratioEG2_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEG2_13f = new TH1F("hTMratioEG2_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEG2_13def = new TH1F("hTMratioEG2_13def", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEGA_13d = new TH1F("hTMratioEGA_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEGA_13e = new TH1F("hTMratioEGA_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEGA_13f = new TH1F("hTMratioEGA_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEGA_13def = new TH1F("hTMratioEGA_13def", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEG12A_13d = new TH1F("hTMratioEG12A_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEG12A_13e = new TH1F("hTMratioEG12A_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEG12A_13f = new TH1F("hTMratioEG12A_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hTMratioEG12A_13def = new TH1F("hTMratioEG12A_13def", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  
  hTMratioEG1_13d->SetLineColor(kGreen);
  hTMratioEG1_13d->SetMarkerColor(kGreen);
  hTMratioEG1_13d->SetMarkerStyle(kOpenCircle);
  hTMratioEG1_13d->SetMarkerSize(2);
  hTMratioEG1_13e->SetLineColor(kMagenta);
  hTMratioEG1_13e->SetMarkerColor(kMagenta);
  hTMratioEG1_13e->SetMarkerStyle(kOpenCircle);
  hTMratioEG1_13e->SetMarkerSize(2);
  hTMratioEG1_13f->SetLineColor(kCyan);
  hTMratioEG1_13f->SetMarkerColor(kCyan);
  hTMratioEG1_13f->SetMarkerStyle(kOpenCircle);
  hTMratioEG1_13f->SetMarkerSize(2);
  hTMratioEG1_13def->SetLineColor(kRed);
  hTMratioEG1_13def->SetMarkerColor(kRed);
  hTMratioEG1_13def->SetMarkerStyle(kOpenCircle);
  hTMratioEG1_13def->SetMarkerSize(2);
  
  hTMratioEG2_13d->SetLineColor(kGreen);
  hTMratioEG2_13d->SetMarkerColor(kGreen);
  hTMratioEG2_13d->SetMarkerStyle(kOpenSquare);
  hTMratioEG2_13d->SetMarkerSize(2);
  hTMratioEG2_13e->SetLineColor(kMagenta);
  hTMratioEG2_13e->SetMarkerColor(kMagenta);
  hTMratioEG2_13e->SetMarkerStyle(kOpenSquare);
  hTMratioEG2_13e->SetMarkerSize(2);
  hTMratioEG2_13f->SetLineColor(kCyan);
  hTMratioEG2_13f->SetMarkerColor(kCyan);
  hTMratioEG2_13f->SetMarkerStyle(kOpenSquare);
  hTMratioEG2_13f->SetMarkerSize(2);
  hTMratioEG2_13def->SetLineColor(kRed);
  hTMratioEG2_13def->SetMarkerColor(kRed);
  hTMratioEG2_13def->SetMarkerStyle(kOpenSquare);
  hTMratioEG2_13def->SetMarkerSize(2);

  hTMratioEGA_13d->SetLineColor(kGreen);
  hTMratioEGA_13d->SetMarkerColor(kGreen);
  hTMratioEGA_13d->SetMarkerStyle(kOpenDiamond);
  hTMratioEGA_13d->SetMarkerSize(2);
  hTMratioEGA_13e->SetLineColor(kMagenta);
  hTMratioEGA_13e->SetMarkerColor(kMagenta);
  hTMratioEGA_13e->SetMarkerStyle(kOpenDiamond);
  hTMratioEGA_13e->SetMarkerSize(2);
  hTMratioEGA_13f->SetLineColor(kCyan);
  hTMratioEGA_13f->SetMarkerColor(kCyan);
  hTMratioEGA_13f->SetMarkerStyle(kOpenDiamond);
  hTMratioEGA_13f->SetMarkerSize(2);
  hTMratioEGA_13def->SetLineColor(kRed);
  hTMratioEGA_13def->SetMarkerColor(kRed);
  hTMratioEGA_13def->SetMarkerStyle(kOpenDiamond);
  hTMratioEGA_13def->SetMarkerSize(2);

  hTMratioEG12A_13d->SetLineColor(kGreen);
  hTMratioEG12A_13d->SetMarkerColor(kGreen);
  hTMratioEG12A_13d->SetMarkerStyle(kOpenStar);
  hTMratioEG12A_13d->SetMarkerSize(2);
  hTMratioEG12A_13e->SetLineColor(kMagenta);
  hTMratioEG12A_13e->SetMarkerColor(kMagenta);
  hTMratioEG12A_13e->SetMarkerStyle(kOpenStar);
  hTMratioEG12A_13e->SetMarkerSize(2);
  hTMratioEG12A_13f->SetLineColor(kCyan);
  hTMratioEG12A_13f->SetMarkerColor(kCyan);
  hTMratioEG12A_13f->SetMarkerStyle(kOpenStar);
  hTMratioEG12A_13f->SetMarkerSize(2);
  hTMratioEG12A_13def->SetLineColor(kRed);
  hTMratioEG12A_13def->SetMarkerColor(kRed);
  hTMratioEG12A_13def->SetMarkerStyle(kOpenStar);
  hTMratioEG12A_13def->SetMarkerSize(2);

  TH1F* hSMscaledEG1_13d = new TH1F("hSMscaledEG1_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMscaledEG2_13d = new TH1F("hSMscaledEG2_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMscaledEGA_13d = new TH1F("hSMscaledEGA_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMscaledEG1_13e = new TH1F("hSMscaledEG1_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMscaledEG2_13e = new TH1F("hSMscaledEG2_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMscaledEGA_13e = new TH1F("hSMscaledEGA_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMscaledEG1_13f = new TH1F("hSMscaledEG1_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMscaledEG2_13f = new TH1F("hSMscaledEG2_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMscaledEGA_13f = new TH1F("hSMscaledEGA_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);

  TH1F* hSMratioEG1_13d = new TH1F("hSMratioEG1_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMratioEG2_13d = new TH1F("hSMratioEG2_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMratioEGA_13d = new TH1F("hSMratioEGA_13d", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMratioEG1_13e = new TH1F("hSMratioEG1_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMratioEG2_13e = new TH1F("hSMratioEG2_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMratioEGA_13e = new TH1F("hSMratioEGA_13e", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMratioEG1_13f = new TH1F("hSMratioEG1_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMratioEG2_13f = new TH1F("hSMratioEG2_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  TH1F* hSMratioEGA_13f = new TH1F("hSMratioEGA_13f", ";E_{T} [GeV]; R_{trig}", nbinscluster, clusterbins);
  
  hSMscaledEG1_13d->SetLineColor(kBlue);
  hSMscaledEG1_13d->SetMarkerColor(kBlue);
  hSMscaledEG1_13d->SetMarkerStyle(kOpenCircle);
  hSMscaledEG1_13d->SetMarkerSize(2);
  hSMscaledEG1_13e->SetLineColor(kYellow);
  hSMscaledEG1_13e->SetMarkerColor(kYellow);
  hSMscaledEG1_13e->SetMarkerStyle(kOpenCircle);
  hSMscaledEG1_13e->SetMarkerSize(2);
  hSMscaledEG1_13f->SetLineColor(kOrange);
  hSMscaledEG1_13f->SetMarkerColor(kOrange);
  hSMscaledEG1_13f->SetMarkerStyle(kOpenCircle);
  hSMscaledEG1_13f->SetMarkerSize(2);

  hSMratioEG1_13d->SetLineColor(kBlue);
  hSMratioEG1_13d->SetMarkerColor(kBlue);
  hSMratioEG1_13d->SetMarkerStyle(kOpenCircle);
  hSMratioEG1_13d->SetMarkerSize(2);
  hSMratioEG1_13e->SetLineColor(kViolet+1);
  hSMratioEG1_13e->SetMarkerColor(kViolet+1);
  hSMratioEG1_13e->SetMarkerStyle(kOpenCircle);
  hSMratioEG1_13e->SetMarkerSize(2);
  hSMratioEG1_13f->SetLineColor(kOrange);
  hSMratioEG1_13f->SetMarkerColor(kOrange);
  hSMratioEG1_13f->SetMarkerStyle(kOpenCircle);
  hSMratioEG1_13f->SetMarkerSize(2);

  hSMscaledEG2_13d->SetLineColor(kBlue);
  hSMscaledEG2_13d->SetMarkerColor(kBlue);
  hSMscaledEG2_13d->SetMarkerStyle(kOpenSquare);
  hSMscaledEG2_13d->SetMarkerSize(2);
  hSMscaledEG2_13e->SetLineColor(kYellow);
  hSMscaledEG2_13e->SetMarkerColor(kYellow);
  hSMscaledEG2_13e->SetMarkerStyle(kOpenSquare);
  hSMscaledEG2_13e->SetMarkerSize(2);
  hSMscaledEG2_13f->SetLineColor(kOrange);
  hSMscaledEG2_13f->SetMarkerColor(kOrange);
  hSMscaledEG2_13f->SetMarkerStyle(kOpenSquare);
  hSMscaledEG2_13f->SetMarkerSize(2);

  hSMratioEG2_13d->SetLineColor(kBlue);
  hSMratioEG2_13d->SetMarkerColor(kBlue);
  hSMratioEG2_13d->SetMarkerStyle(kOpenSquare);
  hSMratioEG2_13d->SetMarkerSize(2);
  hSMratioEG2_13e->SetLineColor(kViolet+1);
  hSMratioEG2_13e->SetMarkerColor(kViolet+1);
  hSMratioEG2_13e->SetMarkerStyle(kOpenSquare);
  hSMratioEG2_13e->SetMarkerSize(2);
  hSMratioEG2_13f->SetLineColor(kOrange);
  hSMratioEG2_13f->SetMarkerColor(kOrange);
  hSMratioEG2_13f->SetMarkerStyle(kOpenSquare);
  hSMratioEG2_13f->SetMarkerSize(2);

  hSMscaledEGA_13d->SetLineColor(kBlue);
  hSMscaledEGA_13d->SetMarkerColor(kBlue);
  hSMscaledEGA_13d->SetMarkerStyle(kOpenDiamond);
  hSMscaledEGA_13d->SetMarkerSize(2);
  hSMscaledEGA_13e->SetLineColor(kYellow);
  hSMscaledEGA_13e->SetMarkerColor(kYellow);
  hSMscaledEGA_13e->SetMarkerStyle(kOpenDiamond);
  hSMscaledEGA_13e->SetMarkerSize(2);
  hSMscaledEGA_13f->SetLineColor(kOrange);
  hSMscaledEGA_13f->SetMarkerColor(kOrange);
  hSMscaledEGA_13f->SetMarkerStyle(kOpenDiamond);
  hSMscaledEGA_13f->SetMarkerSize(2);

  hSMratioEGA_13d->SetLineColor(kBlue);
  hSMratioEGA_13d->SetMarkerColor(kBlue);
  hSMratioEGA_13d->SetMarkerStyle(kOpenStar);
  hSMratioEGA_13d->SetMarkerSize(2);
  hSMratioEGA_13e->SetLineColor(kViolet+1);
  hSMratioEGA_13e->SetMarkerColor(kViolet+1);
  hSMratioEGA_13e->SetMarkerStyle(kOpenStar);
  hSMratioEGA_13e->SetMarkerSize(2);
  hSMratioEGA_13f->SetLineColor(kOrange);
  hSMratioEGA_13f->SetMarkerColor(kOrange);
  hSMratioEGA_13f->SetMarkerStyle(kOpenStar);
  hSMratioEGA_13f->SetMarkerSize(2);

  for(int i = 1; i < hMB_13cdef->GetNbinsX()+1; i++){
    double contentMB = hMB_13cdef->GetBinContent(i);
    double errorMB = hMB_13cdef->GetBinError(i);

    //13d
    double contentEG1_13d = hEG1_13d->GetBinContent(i);
    double errorEG1_13d = hEG1_13d->GetBinError(i); 
    double contentEG2_13d = hEG2_13d->GetBinContent(i);
    double errorEG2_13d = hEG2_13d->GetBinError(i); 
    hTMscaledEG1_13d->SetBinContent(i, contentEG1_13d/tm_eg1_13d);
    hTMscaledEG1_13d->SetBinError(i, errorEG1_13d/tm_eg1_13d);
    hTMscaledEG2_13d->SetBinContent(i, contentEG2_13d/tm_eg2_13d);
    hTMscaledEG2_13d->SetBinError(i, errorEG2_13d/tm_eg2_13d);
    hSMscaledEG1_13d->SetBinContent(i, contentEG1_13d/sm_eg1_13d);
    hSMscaledEG1_13d->SetBinError(i, errorEG1_13d/sm_eg1_13d);
    hSMscaledEG2_13d->SetBinContent(i, contentEG2_13d/sm_eg2_13d);
    hSMscaledEG2_13d->SetBinError(i, errorEG2_13d/sm_eg2_13d);
    hTMscaledEGA_13d->SetBinContent(i, contentEG1_13d/tm_ega_13d);
    hTMscaledEGA_13d->SetBinError(i, errorEG1_13d/tm_ega_13d);
    hSMscaledEGA_13d->SetBinContent(i, contentEG1_13d/sm_ega_13d);
    hSMscaledEGA_13d->SetBinError(i, errorEG1_13d/sm_ega_13d);
    if(contentEG2_13d){
      double ratioTM_EGA_13d = hTMscaledEGA_13d->GetBinContent(i)/contentEG2_13d;
      double errorTM_EGA_13d = TMath::Sqrt(TMath::Power(hTMscaledEGA_13d->GetBinError(i)/hTMscaledEGA_13d->GetBinContent(i),2) +TMath::Power(errorEG2_13d/contentEG2_13d,2))*ratioTM_EGA_13d;
      hTMratioEGA_13d->SetBinContent(i, ratioTM_EGA_13d);
      hTMratioEGA_13d->SetBinError(i, errorTM_EGA_13d);
      double ratioSM_EGA_13d = hSMscaledEGA_13d->GetBinContent(i)/contentEG2_13d;
      double errorSM_EGA_13d = TMath::Sqrt(TMath::Power(hSMscaledEGA_13d->GetBinError(i)/hSMscaledEGA_13d->GetBinContent(i),2) +TMath::Power(errorEG2_13d/contentEG2_13d,2))*ratioSM_EGA_13d;
      hSMratioEGA_13d->SetBinContent(i, ratioSM_EGA_13d);
      hSMratioEGA_13d->SetBinError(i, errorSM_EGA_13d);
    }
    
    //13e
    double contentEG1_13e = hEG1_13e->GetBinContent(i);
    double errorEG1_13e = hEG1_13e->GetBinError(i); 
    double contentEG2_13e = hEG2_13e->GetBinContent(i);
    double errorEG2_13e = hEG2_13e->GetBinError(i); 
    hTMscaledEG1_13e->SetBinContent(i, contentEG1_13e/tm_eg1_13e);
    hTMscaledEG1_13e->SetBinError(i, errorEG1_13e/tm_eg1_13e);
    hTMscaledEG2_13e->SetBinContent(i, contentEG2_13e/tm_eg2_13e);
    hTMscaledEG2_13e->SetBinError(i, errorEG2_13e/tm_eg2_13e);
    hSMscaledEG1_13e->SetBinContent(i, contentEG1_13e/sm_eg1_13e);
    hSMscaledEG1_13e->SetBinError(i, errorEG1_13e/sm_eg1_13e);
    hSMscaledEG2_13e->SetBinContent(i, contentEG2_13e/sm_eg2_13e);
    hSMscaledEG2_13e->SetBinError(i, errorEG2_13e/sm_eg2_13e);
    hTMscaledEGA_13e->SetBinContent(i, contentEG1_13e/tm_ega_13e);
    hTMscaledEGA_13e->SetBinError(i, errorEG1_13e/tm_ega_13e);
    hSMscaledEGA_13e->SetBinContent(i, contentEG1_13e/sm_ega_13e);
    hSMscaledEGA_13e->SetBinError(i, errorEG1_13e/sm_ega_13e);
    if(contentEG2_13e){
      double ratioTM_EGA_13e = hTMscaledEGA_13e->GetBinContent(i)/contentEG2_13e;
      double errorTM_EGA_13e = TMath::Sqrt(TMath::Power(hTMscaledEGA_13e->GetBinError(i)/hTMscaledEGA_13e->GetBinContent(i),2) +TMath::Power(errorEG2_13e/contentEG2_13e,2))*ratioTM_EGA_13e;
      hTMratioEGA_13e->SetBinContent(i, ratioTM_EGA_13e);
      hTMratioEGA_13e->SetBinError(i, errorTM_EGA_13e);
      double ratioSM_EGA_13e = hSMscaledEGA_13e->GetBinContent(i)/contentEG2_13e;
      double errorSM_EGA_13e = TMath::Sqrt(TMath::Power(hSMscaledEGA_13e->GetBinError(i)/hSMscaledEGA_13e->GetBinContent(i),2) +TMath::Power(errorEG2_13e/contentEG2_13e,2))*ratioSM_EGA_13e;
      hSMratioEGA_13e->SetBinContent(i, ratioSM_EGA_13e);
      hSMratioEGA_13e->SetBinError(i, errorSM_EGA_13e);
    }

    //13f
    double contentEG1_13f = hEG1_13f->GetBinContent(i);
    double errorEG1_13f = hEG1_13f->GetBinError(i); 
    double contentEG2_13f = hEG2_13f->GetBinContent(i);
    double errorEG2_13f = hEG2_13f->GetBinError(i); 
    hTMscaledEG1_13f->SetBinContent(i, contentEG1_13f/tm_eg1_13f);
    hTMscaledEG1_13f->SetBinError(i, errorEG1_13f/tm_eg1_13f);
    hTMscaledEG2_13f->SetBinContent(i, contentEG2_13f/tm_eg2_13f);
    hTMscaledEG2_13f->SetBinError(i, errorEG2_13f/tm_eg2_13f);
    hSMscaledEG1_13f->SetBinContent(i, contentEG1_13f/sm_eg1_13f);
    hSMscaledEG1_13f->SetBinError(i, errorEG1_13f/sm_eg1_13f);
    hSMscaledEG2_13f->SetBinContent(i, contentEG2_13f/sm_eg2_13f);
    hSMscaledEG2_13f->SetBinError(i, errorEG2_13f/sm_eg2_13f);
    hTMscaledEGA_13f->SetBinContent(i, contentEG1_13f/tm_ega_13f);
    hTMscaledEGA_13f->SetBinError(i, errorEG1_13f/tm_ega_13f);
    hSMscaledEGA_13f->SetBinContent(i, contentEG1_13f/sm_ega_13f);
    hSMscaledEGA_13f->SetBinError(i, errorEG1_13f/sm_ega_13f);
    hTMscaledEG12A_13f->SetBinContent(i, contentEG1_13f/tm_eg12a_13f);
    hTMscaledEG12A_13f->SetBinError(i, errorEG1_13f/tm_eg12a_13f);
    if(contentEG2_13f){
      double ratioTM_EGA_13f = hTMscaledEGA_13f->GetBinContent(i)/contentEG2_13f;
      double errorTM_EGA_13f = TMath::Sqrt(TMath::Power(hTMscaledEGA_13f->GetBinError(i)/hTMscaledEGA_13f->GetBinContent(i),2) +TMath::Power(errorEG2_13f/contentEG2_13f,2))*ratioTM_EGA_13f;
      hTMratioEGA_13f->SetBinContent(i, ratioTM_EGA_13f);
      hTMratioEGA_13f->SetBinError(i, errorTM_EGA_13f);
      double ratioSM_EGA_13f = hSMscaledEGA_13f->GetBinContent(i)/contentEG2_13f;
      double errorSM_EGA_13f = TMath::Sqrt(TMath::Power(hSMscaledEGA_13f->GetBinError(i)/hSMscaledEGA_13f->GetBinContent(i),2) +TMath::Power(errorEG2_13f/contentEG2_13f,2))*ratioSM_EGA_13f;
      hSMratioEGA_13f->SetBinContent(i, ratioSM_EGA_13f);
      hSMratioEGA_13f->SetBinError(i, errorSM_EGA_13f);
    }
 
    //13def
    double contentEG1_13def = hEG1_13def->GetBinContent(i);
    double errorEG1_13def = hEG1_13def->GetBinError(i); 
    double contentEG2_13def = hEG2_13def->GetBinContent(i);
    double errorEG2_13def = hEG2_13def->GetBinError(i); 
    hTMscaledEG1_13def->SetBinContent(i, contentEG1_13def/tm_eg1_13def);
    hTMscaledEG1_13def->SetBinError(i, errorEG1_13def/tm_eg1_13def);
    hTMscaledEG2_13def->SetBinContent(i, contentEG2_13def/tm_eg2_13def);
    hTMscaledEG2_13def->SetBinError(i, errorEG2_13def/tm_eg2_13def);
    hTMscaledEGA_13def->SetBinContent(i, contentEG1_13def/tm_ega_13def);
    hTMscaledEGA_13def->SetBinError(i, errorEG1_13def/tm_ega_13def);
    hTMscaledEG12A_13def->SetBinContent(i, contentEG1_13def/tm_eg12a_13def);
    hTMscaledEG12A_13def->SetBinError(i, errorEG1_13def/tm_eg12a_13def);
    if(contentEG2_13def){
      double ratioTM_EGA_13def = hTMscaledEGA_13def->GetBinContent(i)/contentEG2_13def;
      double errorTM_EGA_13def = TMath::Sqrt(TMath::Power(hTMscaledEGA_13def->GetBinError(i)/hTMscaledEGA_13def->GetBinContent(i),2) +TMath::Power(errorEG2_13def/contentEG2_13def,2))*ratioTM_EGA_13def;
      hTMratioEGA_13def->SetBinContent(i, ratioTM_EGA_13def);
      hTMratioEGA_13def->SetBinError(i, errorTM_EGA_13def);
    }

    if(contentMB){
      //EG1
      //13d
      double ratioTM_EG1_13d = hTMscaledEG1_13d->GetBinContent(i)/contentMB;
      double errorTM_EG1_13d = TMath::Sqrt(TMath::Power(hTMscaledEG1_13d->GetBinError(i)/hTMscaledEG1_13d->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioTM_EG1_13d;
      hTMratioEG1_13d->SetBinContent(i, ratioTM_EG1_13d);
      hTMratioEG1_13d->SetBinError(i, errorTM_EG1_13d);
      double ratioSM_EG1_13d = hSMscaledEG1_13d->GetBinContent(i)/contentMB;
      double errorSM_EG1_13d = TMath::Sqrt(TMath::Power(hSMscaledEG1_13d->GetBinError(i)/hSMscaledEG1_13d->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioSM_EG1_13d;
      hSMratioEG1_13d->SetBinContent(i, ratioSM_EG1_13d);
      hSMratioEG1_13d->SetBinError(i, errorSM_EG1_13d);

      //13e
      double ratioTM_EG1_13e = hTMscaledEG1_13e->GetBinContent(i)/contentMB;
      double errorTM_EG1_13e = TMath::Sqrt(TMath::Power(hTMscaledEG1_13e->GetBinError(i)/hTMscaledEG1_13e->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioTM_EG1_13e;
      hTMratioEG1_13e->SetBinContent(i, ratioTM_EG1_13e);
      hTMratioEG1_13e->SetBinError(i, errorTM_EG1_13e);
      double ratioSM_EG1_13e = hSMscaledEG1_13e->GetBinContent(i)/contentMB;
      double errorSM_EG1_13e = TMath::Sqrt(TMath::Power(hSMscaledEG1_13e->GetBinError(i)/hSMscaledEG1_13e->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioSM_EG1_13e;
      hSMratioEG1_13e->SetBinContent(i, ratioSM_EG1_13e);
      hSMratioEG1_13e->SetBinError(i, errorSM_EG1_13e);

      //13f
      double ratioTM_EG1_13f = hTMscaledEG1_13f->GetBinContent(i)/contentMB;
      double errorTM_EG1_13f = TMath::Sqrt(TMath::Power(hTMscaledEG1_13f->GetBinError(i)/hTMscaledEG1_13f->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioTM_EG1_13f;
      hTMratioEG1_13f->SetBinContent(i, ratioTM_EG1_13f);
      hTMratioEG1_13f->SetBinError(i, errorTM_EG1_13f);
      double ratioSM_EG1_13f = hSMscaledEG1_13f->GetBinContent(i)/contentMB;
      double errorSM_EG1_13f = TMath::Sqrt(TMath::Power(hSMscaledEG1_13f->GetBinError(i)/hSMscaledEG1_13f->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioSM_EG1_13f;
      hSMratioEG1_13f->SetBinContent(i, ratioSM_EG1_13f);
      hSMratioEG1_13f->SetBinError(i, errorSM_EG1_13f);
      double ratioTM_EG12A_13f = hTMscaledEG12A_13f->GetBinContent(i)/contentMB;
      double errorTM_EG12A_13f = TMath::Sqrt(TMath::Power(hTMscaledEG12A_13f->GetBinError(i)/hTMscaledEG12A_13f->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioTM_EG12A_13f;
      hTMratioEG12A_13f->SetBinContent(i, ratioTM_EG12A_13f);
      hTMratioEG12A_13f->SetBinError(i, errorTM_EG12A_13f);
     
      //13def
      double ratioTM_EG1_13def = hTMscaledEG1_13def->GetBinContent(i)/contentMB;
      double errorTM_EG1_13def = TMath::Sqrt(TMath::Power(hTMscaledEG1_13def->GetBinError(i)/hTMscaledEG1_13def->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioTM_EG1_13def;
      hTMratioEG1_13def->SetBinContent(i, ratioTM_EG1_13def);
      hTMratioEG1_13def->SetBinError(i, errorTM_EG1_13def);
      double ratioTM_EG12A_13def = hTMscaledEG12A_13def->GetBinContent(i)/contentMB;
      double errorTM_EG12A_13def = TMath::Sqrt(TMath::Power(hTMscaledEG12A_13def->GetBinError(i)/hTMscaledEG12A_13def->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioTM_EG12A_13def;
      hTMratioEG12A_13def->SetBinContent(i, ratioTM_EG12A_13def);
      hTMratioEG12A_13def->SetBinError(i, errorTM_EG12A_13def);

      //EG2
      //13d
      double ratioTM_EG2_13d = hTMscaledEG2_13d->GetBinContent(i)/contentMB;
      double errorTM_EG2_13d = TMath::Sqrt(TMath::Power(hTMscaledEG2_13d->GetBinError(i)/hTMscaledEG2_13d->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioTM_EG2_13d;
      hTMratioEG2_13d->SetBinContent(i, ratioTM_EG2_13d);
      hTMratioEG2_13d->SetBinError(i, errorTM_EG2_13d);
      double ratioSM_EG2_13d = hSMscaledEG2_13d->GetBinContent(i)/contentMB;
      double errorSM_EG2_13d = TMath::Sqrt(TMath::Power(hSMscaledEG2_13d->GetBinError(i)/hSMscaledEG2_13d->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioSM_EG2_13d;
      hSMratioEG2_13d->SetBinContent(i, ratioSM_EG2_13d);
      hSMratioEG2_13d->SetBinError(i, errorSM_EG2_13d);

      //13e
      double ratioTM_EG2_13e = hTMscaledEG2_13e->GetBinContent(i)/contentMB;
      double errorTM_EG2_13e = TMath::Sqrt(TMath::Power(hTMscaledEG2_13e->GetBinError(i)/hTMscaledEG2_13e->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioTM_EG2_13e;
      hTMratioEG2_13e->SetBinContent(i, ratioTM_EG2_13e);
      hTMratioEG2_13e->SetBinError(i, errorTM_EG2_13e);
      double ratioSM_EG2_13e = hSMscaledEG2_13e->GetBinContent(i)/contentMB;
      double errorSM_EG2_13e = TMath::Sqrt(TMath::Power(hSMscaledEG2_13e->GetBinError(i)/hSMscaledEG2_13e->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioSM_EG2_13e;
      hSMratioEG2_13e->SetBinContent(i, ratioSM_EG2_13e);
      hSMratioEG2_13e->SetBinError(i, errorSM_EG2_13e);

      //13f
      double ratioTM_EG2_13f = hTMscaledEG2_13f->GetBinContent(i)/contentMB;
      double errorTM_EG2_13f = TMath::Sqrt(TMath::Power(hTMscaledEG2_13f->GetBinError(i)/hTMscaledEG2_13f->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioTM_EG2_13f;
      hTMratioEG2_13f->SetBinContent(i, ratioTM_EG2_13f);
      hTMratioEG2_13f->SetBinError(i, errorTM_EG2_13f);
      double ratioSM_EG2_13f = hSMscaledEG2_13f->GetBinContent(i)/contentMB;
      double errorSM_EG2_13f = TMath::Sqrt(TMath::Power(hSMscaledEG2_13f->GetBinError(i)/hSMscaledEG2_13f->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioSM_EG2_13f;
      hSMratioEG2_13f->SetBinContent(i, ratioSM_EG2_13f);
      hSMratioEG2_13f->SetBinError(i, errorSM_EG2_13f);

      //13def
      double ratioTM_EG2_13def = hTMscaledEG2_13def->GetBinContent(i)/contentMB;
      double errorTM_EG2_13def = TMath::Sqrt(TMath::Power(hTMscaledEG2_13def->GetBinError(i)/hTMscaledEG2_13def->GetBinContent(i),2) +TMath::Power(errorMB/contentMB,2))*ratioTM_EG2_13def;
      hTMratioEG2_13def->SetBinContent(i, ratioTM_EG2_13def);
      hTMratioEG2_13def->SetBinError(i, errorTM_EG2_13def);//
    }
  }//end for


  /*TLegend* lscale = new TLegend(0.65, 0.65,0.9, 0.9);
  lscale->AddEntry((TObject*)0, "Cluster Spectra", "");
  //lscale->AddEntry(hMB_13cdef, "Minimum bias trigger (MB)");
  lscale->AddEntry(hEG2_13def, "13def (EG2)");
  lscale->AddEntry(hEG2_13d, "13d (EG2)");
  lscale->AddEntry(hEG2_13e, "13e (EG2)");
  lscale->AddEntry(hEG2_13f, "13f (EG2)");
  lscale->AddEntry(hTMscaledEGA_13d, "13d cluster spectra method");
  lscale->AddEntry(hTMscaledEGA_13e, "13e cluster spectra method");
  lscale->AddEntry(hTMscaledEGA_13f, "13f cluster spectra method");
  lscale->AddEntry(hSMscaledEGA_13d, "13d scalar method");
  lscale->AddEntry(hSMscaledEGA_13e, "13e scalar method");
  lscale->AddEntry(hSMscaledEGA_13f, "13f scalar method");
  lscale->AddEntry(hTMscaledEGA_13def, "13def");

  TCanvas* c3 = new TCanvas();
  c3->SetLogy();
  //hMB_13cdef->Draw("e1");
  hEG2_13def->Draw("e1");
  hEG2_13d->Draw("samee1");
  hEG2_13e->Draw("samee1");
  hEG2_13f->Draw("samee1");
  hTMscaledEGA_13d->Draw("samee1");
  hTMscaledEGA_13e->Draw("samee1");
  hTMscaledEGA_13f->Draw("samee1");
  hSMscaledEGA_13d->Draw("samee1");
  hSMscaledEGA_13e->Draw("samee1");
  hSMscaledEGA_13f->Draw("samee1");
  hTMscaledEGA_13def->Draw("samee1");
  lscale->Draw("same");//*/
  
  TLine *line = new TLine(14, 1, 40, 1);
  line->SetLineColor(kBlack);
  
  /*TLegend* lratio = new TLegend(0.65, 0.65,0.9, 0.9);
  lratio->AddEntry((TObject*)0, "Cluster Spectra", "");
  lratio->AddEntry(hTMratioEGA_13d, "13d cluster spectra method");
  lratio->AddEntry(hTMratioEGA_13e, "13e cluster spectra method");
  lratio->AddEntry(hTMratioEGA_13f, "13f cluster spectra method");
  lratio->AddEntry(hSMratioEGA_13d, "13d scalar method");
  lratio->AddEntry(hSMratioEGA_13e, "13e scalar method");
  lratio->AddEntry(hSMratioEGA_13f, "13f scalar method");
  lratio->AddEntry(hTMratioEGA_13def, "13def cluster spectra method");

  TCanvas* cratio = new TCanvas();
  hTMratioEGA_13d->GetYaxis()->SetRangeUser(0.5,1.5);
  hTMratioEGA_13d->Draw("e1");
  hTMratioEGA_13e->Draw("samee1");
  hTMratioEGA_13f->Draw("samee1");
  hTMratioEGA_13def->Draw("samee1");
  hSMratioEGA_13d->Draw("samee1");
  hSMratioEGA_13e->Draw("samee1");
  hSMratioEGA_13f->Draw("samee1");
  lratio->Draw("same");
  line->Draw("same");//*/
  
  /*TLegend* l13d = new TLegend(0.65, 0.65,0.9, 0.9);
  l13d->AddEntry((TObject*)0, "Min bias cross section ratio", "");
  l13d->AddEntry(hTMratioEGA_13d, "13d cluster spectra method");
  l13d->AddEntry(hSMratioEGA_13d, "13d scalar method");
  l13d->AddEntry(hTMratioEGA_13def, "13def");

  TCanvas* c13d = new TCanvas();
  hTMratioEGA_13d->GetYaxis()->SetRangeUser(0.5,1.5);
  hTMratioEGA_13d->Draw("e1");
  hTMratioEGA_13def->Draw("samee1");
  hSMratioEGA_13d->Draw("samee1");
  l13d->Draw("same");
  line->Draw("same");//*/
  
  /*TLegend* l13e = new TLegend(0.65, 0.65,0.9, 0.9);
  l13e->AddEntry((TObject*)0, "Min bias cross section ratio", "");
  l13e->AddEntry(hTMratioEG1_13e, "13e cluster spectra method");
  l13e->AddEntry(hSMratioEG1_13e, "13e scalar method");
  l13e->AddEntry(hTMratioEG1_13def, "13def");

  TCanvas* c13e = new TCanvas();
  hTMratioEGA_13e->GetYaxis()->SetRangeUser(0.5,1.5);
  hTMratioEGA_13e->Draw("e1");
  hTMratioEGA_13def->Draw("samee1");
  hSMratioEGA_13e->Draw("samee1");
  l13e->Draw("same");
  line->Draw("same");//*/
  
  /*TLegend* l13f = new TLegend(0.65, 0.65,0.9, 0.9);
  l13f->AddEntry((TObject*)0, "Min bias cross section ratio", "");
  l13f->AddEntry(hTMratioEGA_13f, "13f cluster spectra method");
  l13f->AddEntry(hSMratioEGA_13f, "13f scalar method");
  l13f->AddEntry(hTMratioEGA_13def, "13def");

  TCanvas* c13f = new TCanvas();
  hTMratioEGA_13f->GetYaxis()->SetRangeUser(0.5,1.5);
  hTMratioEGA_13f->Draw("e1");
  hTMratioEGA_13def->Draw("samee1");
  hSMratioEGA_13f->Draw("samee1");
  l13f->Draw("same");
  line->Draw("same");//*/
  
  
  /*TLegend* lscale12a = new TLegend(0.65, 0.65,0.9, 0.9);
  lscale12a->AddEntry((TObject*)0, "Cluster Spectra Method", "");
  lscale12a->AddEntry(hMB_13cdef, "Minimum bias trigger (MB)");
  lscale12a->AddEntry(hEG1_13def, "13def (EG1)");
  lscale12a->AddEntry(hEG1_13f, "13f (EG1)");
  lscale12a->AddEntry(hTMscaledEG1_13f, "13f EG1/MB scaled");
  lscale12a->AddEntry(hTMscaledEG1_13def, "13def EG1/MB scaled");
  lscale12a->AddEntry(hTMscaledEG12A_13f, "13f EG1/EG2*EG2/MB scaled");
  lscale12a->AddEntry(hTMscaledEG12A_13def, "13def EG1/EG2*EG2/MB scaled");

  TCanvas* c3_12a = new TCanvas();
  c3_12a->SetLogy();
  hMB_13cdef->Draw("e1");
  hEG1_13def->Draw("samee1");
  hEG1_13f->Draw("samee1");
  hTMscaledEG1_13f->Draw("samee1");
  hTMscaledEG1_13def->Draw("samee1");
  hTMscaledEG12A_13f->Draw("samee1");
  hTMscaledEG12A_13def->Draw("samee1");
  lscale12a->Draw("same");//*/

  /*TLegend* lratio12a = new TLegend(0.65, 0.65,0.9, 0.9);
  lratio12a->AddEntry((TObject*)0, "Cluster Spectra ratio", "");
  lratio12a->AddEntry(hTMratioEG1_13f, "13f EG1/MB");
  lratio12a->AddEntry(hTMratioEG1_13def, "13def EG1/MB");
  lratio12a->AddEntry(hTMratioEG12A_13f, "13f EG1/EG2*EG2/MB");
  lratio12a->AddEntry(hTMratioEG12A_13def, "13def EG1/EG2*EG2/MB");

  TCanvas* cratio12a = new TCanvas();
  hTMratioEGA_13d->GetYaxis()->SetRangeUser(0.5,1.5);
  hTMratioEG1_13f->Draw("e1");
  hTMratioEG1_13def->Draw("samee1");
  hTMratioEG12A_13f->Draw("samee1");
  hTMratioEG12A_13def->Draw("samee1");
  lratio12a->Draw("same");
  line->Draw("same");//*/
}
