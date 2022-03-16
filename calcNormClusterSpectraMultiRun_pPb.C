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

void calcNormClusterSpectraMultiRun_pPb(){

  gStyle->SetCanvasColor(-1);
  gStyle->SetPadColor(-1);
  gStyle->SetFrameFillColor(-1);
  gStyle->SetHistFillColor(-1);
  gStyle->SetTitleFillColor(-1);
  gStyle->SetFillColor(-1);
  gStyle->SetFillStyle(4000);
  gStyle->SetStatStyle(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/";

  TFile* fin = new TFile(Form("%sfout_6_14bins_firstEvent0_13f_10runs_noSkim_part1_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_6_14bins_firstEvent0_13f_10runs_part1_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_noNorm.root", path.Data()), "READ");

  if(!fin){
    cout << "Can't find file" << endl;
    return;
  }

  TH1F* hEventPerRun = (TH1F*)fin->Get("hEventPerRun");
  const double deltaEta = 1.334;
  const double deltaPhi = 1.884;
  double acceptanceNorm = 2*TMath::Pi()/(deltaEta*deltaPhi);

  //Run197258 cluster spectra
  TH1F* hEG1Run197258 = (TH1F*)fin->Get("hEG1Run197258");
  Double_t numEvents_Run197258 = hEventPerRun->GetBinContent(1);
  cout << "Number of Run197258 events: " << numEvents_Run197258 << endl;
  for(int i = 1; i < hEG1Run197258->GetNbinsX()+1; i++){
    double dE = hEG1Run197258->GetBinWidth(i);
    
    double contentRun197258 = hEG1Run197258->GetBinContent(i);
    double tempRun197258 = (contentRun197258*acceptanceNorm)/((double)numEvents_Run197258*dE);
    double errorRun197258 = hEG1Run197258->GetBinError(i);
    double tempErrRun197258 = (errorRun197258*acceptanceNorm)/((double)numEvents_Run197258*dE);
    if(numEvents_Run197258) 
      {
	hEG1Run197258->SetBinContent(i,tempRun197258);
	hEG1Run197258->SetBinError(i, tempErrRun197258);
      }
    
  }//*/  
  hEG1Run197258->SetLineColor(kRed);
  hEG1Run197258->SetMarkerColor(kRed);
  hEG1Run197258->SetMarkerStyle(21);
  hEG1Run197258->SetMarkerSize(2);

  //Run197260 cluster spectra
  TH1F* hEG1Run197260 = (TH1F*)fin->Get("hEG1Run197260");
  Double_t numEvents_Run197260 = hEventPerRun->GetBinContent(2);
  cout << "Number of Run197260 events: " << numEvents_Run197260 << endl;
  for(int i = 1; i < hEG1Run197260->GetNbinsX()+1; i++){
    double dE = hEG1Run197260->GetBinWidth(i);
    
    double contentRun197260 = hEG1Run197260->GetBinContent(i);
    double tempRun197260 = (contentRun197260*acceptanceNorm)/((double)numEvents_Run197260*dE);
    double errorRun197260 = hEG1Run197260->GetBinError(i);
    double tempErrRun197260 = (errorRun197260*acceptanceNorm)/((double)numEvents_Run197260*dE);
    if(numEvents_Run197260) 
      {
	hEG1Run197260->SetBinContent(i,tempRun197260);
	hEG1Run197260->SetBinError(i, tempErrRun197260);
      }
    
  }//*/  
  hEG1Run197260->SetLineColor(kRed);
  hEG1Run197260->SetMarkerColor(kRed);
  hEG1Run197260->SetMarkerStyle(21);
  hEG1Run197260->SetMarkerSize(2);

  //Run197296 cluster spectra
  TH1F* hEG1Run197296 = (TH1F*)fin->Get("hEG1Run197296");
  Double_t numEvents_Run197296 = hEventPerRun->GetBinContent(3);
  cout << "Number of Run197296 events: " << numEvents_Run197296 << endl;
  for(int i = 1; i < hEG1Run197296->GetNbinsX()+1; i++){
    double dE = hEG1Run197296->GetBinWidth(i);
    
    double contentRun197296 = hEG1Run197296->GetBinContent(i);
    double tempRun197296 = (contentRun197296*acceptanceNorm)/((double)numEvents_Run197296*dE);
    double errorRun197296 = hEG1Run197296->GetBinError(i);
    double tempErrRun197296 = (errorRun197296*acceptanceNorm)/((double)numEvents_Run197296*dE);
    if(numEvents_Run197296) 
      {
	hEG1Run197296->SetBinContent(i,tempRun197296);
	hEG1Run197296->SetBinError(i, tempErrRun197296);
      }
    
  }//*/  
  hEG1Run197296->SetLineColor(kRed);
  hEG1Run197296->SetMarkerColor(kRed);
  hEG1Run197296->SetMarkerStyle(21);
  hEG1Run197296->SetMarkerSize(2);

  //Run197297 cluster spectra
  TH1F* hEG1Run197297 = (TH1F*)fin->Get("hEG1Run197297");
  Double_t numEvents_Run197297 = hEventPerRun->GetBinContent(4);
  cout << "Number of Run197297 events: " << numEvents_Run197297 << endl;
  for(int i = 1; i < hEG1Run197297->GetNbinsX()+1; i++){
    double dE = hEG1Run197297->GetBinWidth(i);
    
    double contentRun197297 = hEG1Run197297->GetBinContent(i);
    double tempRun197297 = (contentRun197297*acceptanceNorm)/((double)numEvents_Run197297*dE);
    double errorRun197297 = hEG1Run197297->GetBinError(i);
    double tempErrRun197297 = (errorRun197297*acceptanceNorm)/((double)numEvents_Run197297*dE);
    if(numEvents_Run197297) 
      {
	hEG1Run197297->SetBinContent(i,tempRun197297);
	hEG1Run197297->SetBinError(i, tempErrRun197297);
      }
    
  }//*/  
  hEG1Run197297->SetLineColor(kRed);
  hEG1Run197297->SetMarkerColor(kRed);
  hEG1Run197297->SetMarkerStyle(21);
  hEG1Run197297->SetMarkerSize(2);

  //Run197298 cluster spectra
  TH1F* hEG1Run197298 = (TH1F*)fin->Get("hEG1Run197298");
  Double_t numEvents_Run197298 = hEventPerRun->GetBinContent(5);
  cout << "Number of Run197298 events: " << numEvents_Run197298 << endl;
  for(int i = 1; i < hEG1Run197298->GetNbinsX()+1; i++){
    double dE = hEG1Run197298->GetBinWidth(i);
    
    double contentRun197298 = hEG1Run197298->GetBinContent(i);
    double tempRun197298 = (contentRun197298*acceptanceNorm)/((double)numEvents_Run197298*dE);
    double errorRun197298 = hEG1Run197298->GetBinError(i);
    double tempErrRun197298 = (errorRun197298*acceptanceNorm)/((double)numEvents_Run197298*dE);
    if(numEvents_Run197298) 
      {
	hEG1Run197298->SetBinContent(i,tempRun197298);
	hEG1Run197298->SetBinError(i, tempErrRun197298);
      }
    
  }//*/  
  hEG1Run197298->SetLineColor(kRed);
  hEG1Run197298->SetMarkerColor(kRed);
  hEG1Run197298->SetMarkerStyle(21);
  hEG1Run197298->SetMarkerSize(2);

  //Run197299 cluster spectra
  TH1F* hEG1Run197299 = (TH1F*)fin->Get("hEG1Run197299");
  Double_t numEvents_Run197299 = hEventPerRun->GetBinContent(6);
  cout << "Number of Run197299 events: " << numEvents_Run197299 << endl;
  for(int i = 1; i < hEG1Run197299->GetNbinsX()+1; i++){
    double dE = hEG1Run197299->GetBinWidth(i);
    
    double contentRun197299 = hEG1Run197299->GetBinContent(i);
    double tempRun197299 = (contentRun197299*acceptanceNorm)/((double)numEvents_Run197299*dE);
    double errorRun197299 = hEG1Run197299->GetBinError(i);
    double tempErrRun197299 = (errorRun197299*acceptanceNorm)/((double)numEvents_Run197299*dE);
    if(numEvents_Run197299) 
      {
	hEG1Run197299->SetBinContent(i,tempRun197299);
	hEG1Run197299->SetBinError(i, tempErrRun197299);
      }
    
  }//*/  
  hEG1Run197299->SetLineColor(kRed);
  hEG1Run197299->SetMarkerColor(kRed);
  hEG1Run197299->SetMarkerStyle(21);
  hEG1Run197299->SetMarkerSize(2);

  //Run197300 cluster spectra
  TH1F* hEG1Run197300 = (TH1F*)fin->Get("hEG1Run197300");
  Double_t numEvents_Run197300 = hEventPerRun->GetBinContent(7);
  cout << "Number of Run197300 events: " << numEvents_Run197300 << endl;
  for(int i = 1; i < hEG1Run197300->GetNbinsX()+1; i++){
    double dE = hEG1Run197300->GetBinWidth(i);
    
    double contentRun197300 = hEG1Run197300->GetBinContent(i);
    double tempRun197300 = (contentRun197300*acceptanceNorm)/((double)numEvents_Run197300*dE);
    double errorRun197300 = hEG1Run197300->GetBinError(i);
    double tempErrRun197300 = (errorRun197300*acceptanceNorm)/((double)numEvents_Run197300*dE);
    if(numEvents_Run197300) 
      {
	hEG1Run197300->SetBinContent(i,tempRun197300);
	hEG1Run197300->SetBinError(i, tempErrRun197300);
      }
    
  }//*/  
  hEG1Run197300->SetLineColor(kRed);
  hEG1Run197300->SetMarkerColor(kRed);
  hEG1Run197300->SetMarkerStyle(21);
  hEG1Run197300->SetMarkerSize(2);

  //Run197302 cluster spectra
  TH1F* hEG1Run197302 = (TH1F*)fin->Get("hEG1Run197302");
  Double_t numEvents_Run197302 = hEventPerRun->GetBinContent(8);
  cout << "Number of Run197302 events: " << numEvents_Run197302 << endl;
  for(int i = 1; i < hEG1Run197302->GetNbinsX()+1; i++){
    double dE = hEG1Run197302->GetBinWidth(i);
    
    double contentRun197302 = hEG1Run197302->GetBinContent(i);
    double tempRun197302 = (contentRun197302*acceptanceNorm)/((double)numEvents_Run197302*dE);
    double errorRun197302 = hEG1Run197302->GetBinError(i);
    double tempErrRun197302 = (errorRun197302*acceptanceNorm)/((double)numEvents_Run197302*dE);
    if(numEvents_Run197302) 
      {
	hEG1Run197302->SetBinContent(i,tempRun197302);
	hEG1Run197302->SetBinError(i, tempErrRun197302);
      }
    
  }//*/  
  hEG1Run197302->SetLineColor(kRed);
  hEG1Run197302->SetMarkerColor(kRed);
  hEG1Run197302->SetMarkerStyle(21);
  hEG1Run197302->SetMarkerSize(2);

  //Run197341 cluster spectra
  TH1F* hEG1Run197341 = (TH1F*)fin->Get("hEG1Run197341");
  Double_t numEvents_Run197341 = hEventPerRun->GetBinContent(9);
  cout << "Number of Run197341 events: " << numEvents_Run197341 << endl;
  for(int i = 1; i < hEG1Run197341->GetNbinsX()+1; i++){
    double dE = hEG1Run197341->GetBinWidth(i);
    
    double contentRun197341 = hEG1Run197341->GetBinContent(i);
    double tempRun197341 = (contentRun197341*acceptanceNorm)/((double)numEvents_Run197341*dE);
    double errorRun197341 = hEG1Run197341->GetBinError(i);
    double tempErrRun197341 = (errorRun197341*acceptanceNorm)/((double)numEvents_Run197341*dE);
    if(numEvents_Run197341) 
      {
	hEG1Run197341->SetBinContent(i,tempRun197341);
	hEG1Run197341->SetBinError(i, tempErrRun197341);
      }
    
  }//*/  
  hEG1Run197341->SetLineColor(kRed);
  hEG1Run197341->SetMarkerColor(kRed);
  hEG1Run197341->SetMarkerStyle(21);
  hEG1Run197341->SetMarkerSize(2);

  //Run197342 cluster spectra
  TH1F* hEG1Run197342 = (TH1F*)fin->Get("hEG1Run197342");
  Double_t numEvents_Run197342 = hEventPerRun->GetBinContent(10);
  cout << "Number of Run197342 events: " << numEvents_Run197342 << endl;
  for(int i = 1; i < hEG1Run197342->GetNbinsX()+1; i++){
    double dE = hEG1Run197342->GetBinWidth(i);
    
    double contentRun197342 = hEG1Run197342->GetBinContent(i);
    double tempRun197342 = (contentRun197342*acceptanceNorm)/((double)numEvents_Run197342*dE);
    double errorRun197342 = hEG1Run197342->GetBinError(i);
    double tempErrRun197342 = (errorRun197342*acceptanceNorm)/((double)numEvents_Run197342*dE);
    if(numEvents_Run197342) 
      {
	hEG1Run197342->SetBinContent(i,tempRun197342);
	hEG1Run197342->SetBinError(i, tempErrRun197342);
      }
    
  }//*/  
  hEG1Run197342->SetLineColor(kRed);
  hEG1Run197342->SetMarkerColor(kRed);
  hEG1Run197342->SetMarkerStyle(21);
  hEG1Run197342->SetMarkerSize(2);

  
  TLegend* legYield = new TLegend(0.6,0.7,0.85,0.85);
  legYield->SetHeader("Photon Yield");
  legYield->AddEntry(hEG1Run197258,"pPb Run197258");
  legYield->AddEntry(hEG1Run197260,"pPb Run197260");
  legYield->AddEntry(hEG1Run197296,"pPb Run197296");
  legYield->AddEntry(hEG1Run197297,"pPb Run197297");
  legYield->AddEntry(hEG1Run197298,"pPb Run197298");
  legYield->AddEntry(hEG1Run197299,"pPb Run197299");
  legYield->AddEntry(hEG1Run197300,"pPb Run197300");
  legYield->AddEntry(hEG1Run197302,"pPb Run197302");
  legYield->AddEntry(hEG1Run197341,"pPb Run197341");
  legYield->AddEntry(hEG1Run197342,"pPb Run197342");
      
  TCanvas* c1 = new TCanvas();
  c1->SetLogy();
  hEG1Run197258->Draw("e1");
  hEG1Run197260->Draw("same e1");
  hEG1Run197296->Draw("same e1");
  hEG1Run197297->Draw("same e1");
  hEG1Run197298->Draw("same e1");
  hEG1Run197299->Draw("same e1");
  hEG1Run197300->Draw("same e1");
  hEG1Run197302->Draw("same e1");
  hEG1Run197341->Draw("same e1");
  hEG1Run197341->Draw("same e1");

  TString filename = fin->GetName();
  Int_t index = filename.Index("_noNorm");
  filename.Replace(index, 7, "");
  if(filename.CompareTo(fin->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hEG1Run197258->Write("hEG1Run197258");
    hEG1Run197260->Write("hEG1Run197260");
    hEG1Run197296->Write("hEG1Run197296");
    hEG1Run197297->Write("hEG1Run197297");
    hEG1Run197298->Write("hEG1Run197298");
    hEG1Run197299->Write("hEG1Run197299");
    hEG1Run197300->Write("hEG1Run197300");
    hEG1Run197302->Write("hEG1Run197302");
    hEG1Run197341->Write("hEG1Run197341");
    hEG1Run197342->Write("hEG1Run197342");

    hEventPerRun->Write("hEventPerRun");
    fout->Close();
  }//end filename compare
  
}
