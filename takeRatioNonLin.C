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

void takeRatioNonLin(){

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
  gStyle->SetOptStat(0);
  
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/";

  /*TFile* fin_woNL = new TFile(Form("%sfout_6_14bins_firstEvent0_13f_10runs_noSkim_part1_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists.root", path.Data()), "READ");
  TFile* fin_wNL = new TFile(Form("%sfout_6_14bins_firstEvent0_13f_10runs_part1_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists.root", path.Data()), "READ");

  //if(!fin){
  //  cout << "Can't find file" << endl;
  //  return;
  //}
  
  TH1F* hEG1Run197258_woNL = (TH1F*)fin_woNL->Get("hEG1Run197258");
  TH1F* hEG1Run197260_woNL = (TH1F*)fin_woNL->Get("hEG1Run197260");
  TH1F* hEG1Run197296_woNL = (TH1F*)fin_woNL->Get("hEG1Run197296");
  TH1F* hEG1Run197297_woNL = (TH1F*)fin_woNL->Get("hEG1Run197297");
  TH1F* hEG1Run197298_woNL = (TH1F*)fin_woNL->Get("hEG1Run197298");
  TH1F* hEG1Run197299_woNL = (TH1F*)fin_woNL->Get("hEG1Run197299");
  TH1F* hEG1Run197300_woNL = (TH1F*)fin_woNL->Get("hEG1Run197300");
  TH1F* hEG1Run197302_woNL = (TH1F*)fin_woNL->Get("hEG1Run197302");
  TH1F* hEG1Run197341_woNL = (TH1F*)fin_woNL->Get("hEG1Run197341");
  TH1F* hEG1Run197342_woNL = (TH1F*)fin_woNL->Get("hEG1Run197342");

  TH1F* hEG1Run197258_wNL = (TH1F*)fin_wNL->Get("hEG1Run197258");
  TH1F* hEG1Run197260_wNL = (TH1F*)fin_wNL->Get("hEG1Run197260");
  TH1F* hEG1Run197296_wNL = (TH1F*)fin_wNL->Get("hEG1Run197296");
  TH1F* hEG1Run197297_wNL = (TH1F*)fin_wNL->Get("hEG1Run197297");
  TH1F* hEG1Run197298_wNL = (TH1F*)fin_wNL->Get("hEG1Run197298");
  TH1F* hEG1Run197299_wNL = (TH1F*)fin_wNL->Get("hEG1Run197299");
  TH1F* hEG1Run197300_wNL = (TH1F*)fin_wNL->Get("hEG1Run197300");
  TH1F* hEG1Run197302_wNL = (TH1F*)fin_wNL->Get("hEG1Run197302");
  TH1F* hEG1Run197341_wNL = (TH1F*)fin_wNL->Get("hEG1Run197341");
  TH1F* hEG1Run197342_wNL = (TH1F*)fin_wNL->Get("hEG1Run197342");

  hEG1Run197258_woNL->Divide(hEG1Run197258_wNL);
  hEG1Run197258_woNL->Fit("pol0","Q", "", 12, 60);
  cout << "Run 197258: " << hEG1Run197258_woNL->GetFunction("pol0")->GetParameter(0) << endl;
  //nlChange->Fill(hEG1Run197258_woNL->GetFunction("pol0")->GetParameter(0));

  hEG1Run197260_woNL->Divide(hEG1Run197260_wNL);
  hEG1Run197260_woNL->Fit("pol0","Q", "", 12, 60);
  cout << "Run 197260: " << hEG1Run197260_woNL->GetFunction("pol0")->GetParameter(0) << endl;
  //nlChange->Fill(hEG1Run197260_woNL->GetFunction("pol0")->GetParameter(0));

  hEG1Run197296_woNL->Divide(hEG1Run197296_wNL);
  hEG1Run197296_woNL->Fit("pol0","Q", "", 12, 60);
  cout << "Run 197296: " << hEG1Run197296_woNL->GetFunction("pol0")->GetParameter(0) << endl;
  //nlChange->Fill(hEG1Run197296_woNL->GetFunction("pol0")->GetParameter(0));

  hEG1Run197297_woNL->Divide(hEG1Run197297_wNL);
  hEG1Run197297_woNL->Fit("pol0","Q", "", 12, 60);
  cout << "Run 197297: " << hEG1Run197297_woNL->GetFunction("pol0")->GetParameter(0) << endl;
  //nlChange->Fill(hEG1Run197297_woNL->GetFunction("pol0")->GetParameter(0));

  hEG1Run197298_woNL->Divide(hEG1Run197298_wNL);
  hEG1Run197298_woNL->Fit("pol0","Q", "", 12, 60);
  cout << "Run 197298: " << hEG1Run197298_woNL->GetFunction("pol0")->GetParameter(0) << endl;
  //nlChange->Fill(hEG1Run197298_woNL->GetFunction("pol0")->GetParameter(0));

  hEG1Run197299_woNL->Divide(hEG1Run197299_wNL);
  hEG1Run197299_woNL->Fit("pol0","Q", "", 12, 60);
  cout << "Run 197299: " << hEG1Run197299_woNL->GetFunction("pol0")->GetParameter(0) << endl;
  //nlChange->Fill(hEG1Run197299_woNL->GetFunction("pol0")->GetParameter(0));

  hEG1Run197300_woNL->Divide(hEG1Run197300_wNL);
  hEG1Run197300_woNL->Fit("pol0","Q", "", 12, 60);
  cout << "Run 197300: " << hEG1Run197300_woNL->GetFunction("pol0")->GetParameter(0) << endl;
  //nlChange->Fill(hEG1Run197300_woNL->GetFunction("pol0")->GetParameter(0));

  hEG1Run197302_woNL->Divide(hEG1Run197302_wNL);
  hEG1Run197302_woNL->Fit("pol0","Q", "", 12, 60);
  cout << "Run 197302: " << hEG1Run197302_woNL->GetFunction("pol0")->GetParameter(0) << endl;
  //nlChange->Fill(hEG1Run197302_woNL->GetFunction("pol0")->GetParameter(0));

  hEG1Run197341_woNL->Divide(hEG1Run197341_wNL);
  hEG1Run197341_woNL->Fit("pol0","Q", "", 12, 60);
  cout << "Run 197341: " << hEG1Run197341_woNL->GetFunction("pol0")->GetParameter(0) << endl;
  //nlChange->Fill(hEG1Run197341_woNL->GetFunction("pol0")->GetParameter(0));

  hEG1Run197342_woNL->Divide(hEG1Run197342_wNL);
  hEG1Run197342_woNL->Fit("pol0","Q", "", 12, 60);
  cout << "Run 197342: " << hEG1Run197342_woNL->GetFunction("pol0")->GetParameter(0) << endl;
  //nlChange->Fill(hEG1Run197342_woNL->GetFunction("pol0")->GetParameter(0));
  //

  TH1F* nlChange = new TH1F("nLChange", ";const fit woNL/wNL;counts", 10, 0.5, 1.);
  nlChange->Fill(0.81065);
  nlChange->Fill(0.779638);
  nlChange->Fill(0.835595);
  nlChange->Fill(0.866956);
  nlChange->Fill(0.844647);
  nlChange->Fill(0.793397);
  nlChange->Fill(0.589396);
  nlChange->Fill(0.843814);
  nlChange->Fill(0.833905);
  nlChange->Fill(0.844362);

  hEG1Run197300_woNL->Divide(hEG1Run197300_wNL);

  
  TCanvas* cChange = new TCanvas("cChange", "cChange", 1000, 800);
  hEG1Run197300_woNL->Draw("e1");
  hEG1Run197300_woNL->Fit("pol0","", "", 12, 60);
    //nlChange->Draw();
  
  //fin_woNL->Close();
  //fin_wNL->Close();//*/

  //13d
  //TFile* fin_woNL13d = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13d/fout_13d_all10runs_noSkim_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_noNorm.root", path.Data()), "READ");
  //TFile* fin_wNL13d = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13d/fout_13d_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_noNorm.root", path.Data()), "READ");

  //13e
  //TFile* fin_woNL13d = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13e/fout_13e_10runs_noSkim_part2_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_noNorm.root", path.Data()), "READ");
  //TFile* fin_wNL13d = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13e/fout_13e_part2_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_noNorm.root", path.Data()), "READ");

  //13f
  /*TFile* fin_woNL13d = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13f/fout_13f_10runs_noSkim_part4_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_noNorm.root", path.Data()), "READ");
  TFile* fin_wNL13d = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13f/fout_13f_part4_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_noNorm.root", path.Data()), "READ");

  
  TH1F* hEG1_wo = (TH1F*)fin_woNL13d->Get("hEG1_196648");
  TH1F* hEG1_w = (TH1F*)fin_wNL13d->Get("hEG1_196648");
  double norm = 0.9681463477;
  hEG1_wo->Divide(hEG1_w);
  hEG1_wo->Scale(norm);
  hEG1_wo->GetYaxis()->SetTitle("#frac{woNL}{wNL}");
  hEG1_wo->GetXaxis()->SetRangeUser(12,60);
  hEG1_wo->Fit("pol0","", "", 12, 60);
  cout << "Run 196309: " << hEG1_wo->GetFunction("pol0")->GetParameter(0) << endl;//*/



  TH1F* nlChange = new TH1F("nLChange", ";const fit woNL/wNL;counts", 20, 0.5, 1.5);
  const Double_t ratios[52] = {0.836508, 0.823993, 0.823361, 0.571614, 0.776631, 0.832744, 0.856271, 0.826504, 0.754017, 0.835742,
			       0.822453, 0.854806, 0.824851, 0.83798,  0.82009,  0.77957,  0.958345, 0.824469, 0.804411, 0.856903,
			       0.827281, 0.81399,  0.844625, 0.833722, 0.88855,  0.873748, 0.8959,   0.798655, 0.862689, 0.729866,
			       0.784498, 0.773724, 0.863088, 0.85996,  0.878823, 0.787246, 0.794626, 0.836623, 0.838062, 0.86492,
			       0.799628, 0.814708, 0.882442, 0.799416, 0.834812, 0.830728, 0.805143, 0.838944, 0.850707, 0.785211,
			       0.853226, 0.8393};
  for(int i = 0; i < 52; i++){
    nlChange->Fill(ratios[i]);
  }

  TCanvas* cChange = new TCanvas("cChange", "cChange", 1000, 800);
  nlChange->Draw();


  
}
