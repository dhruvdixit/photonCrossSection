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

void calcNormClusterSpectra_pPb(){

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

  //13d
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/StdEventsAndClusterCuts/fout_6_14bins_firstEvent0_13d_all10runs_noSkim_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/noPurityClusterSpectra/fout_6_14bins_firstEvent0_13d_all10runs_noSkim_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13d/RunListCheck/fout_7_14bins_firstEvent0_13d_all10runs_noSkim_checkEventCounts_noRun195871_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13d/RunListCheck/fout_7_14bins_firstEvent0_13d_all10runs_noSkim_checkEventCounts_noRun195871or195829_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13d/RunListCheck/fout_7_14bins_firstEvent0_13d_all10runs_noSkim_checkEventCounts_noRun195829_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13d/ntuplizerCheck/fout_6_14bins_firstEvent0_13d_all10Runs_noNonLin_kEMCEGA_isoFixTry1_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13d/ntuplizerCheck/fout_6_14bins_firstEvent0_13d_all10runs_noSkim_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_noNorm.root", path.Data()), "READ");
  
  //13e
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/StdEventsAndClusterCuts/fout_6_14bins_firstEvent0_13e_noSkim_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/noPurityClusterSpectra/fout_6_14bins_firstEvent0_13e_noNorm.root", path.Data()), "READ");
  
  //13f
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/IsoStd/fout_6_14bins_firstEvent0_13f_allruns_noSkim_CALOonly_tof20_newPurity_eCross5_newExoticity_iso_noNorm.root", path.Data()), "READ");//iso < 1.5
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/Iso1/fout_6_14bins_firstEvent0_13f_allruns_noSkim_CALOonly_tof20_newPurity_eCross5_newExoticity_iso1_noNorm.root", path.Data()), "READ");//iso < 1
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/Iso2/fout_6_14bins_firstEvent0_13f_allruns_noSkim_CALOonly_tof20_newPurity_eCross5_newExoticity_iso2_noNorm.root", path.Data()), "READ");//iso <2
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/StdEventsAndClusterCuts/fout_6_14bins_firstEvent0_13f_noSkim_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/noPurityClusterSpectra/fout_6_14bins_firstEvent0_13f_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/AOD/fout_6_14bins_firstEvent0_13f_1runs_test_wCorr_refactorNtuplizerAOD_StdCuts_EX0PurityFit_ConeAcceptanceCheck_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/AOD/fout_6_14bins_firstEvent0_13f_1runs_test_woCorr_refactorNtuplizerAOD_StdCuts_EX0PurityFit_ConeAcceptanceCheck_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/AOD/fout_6_14bins_firstEvent0_13f_allRuns_woNonLinCorr_AlwinaNtuplizer_partAll_StdCuts_EX0PurityFit_ClusterEDiff_AOD_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/ntuplizerComparison/fout_6_14bins_firstEvent0_13f_10runs_noSkim_part1R197302_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/ntuplizerComparison/fout_6_14bins_firstEvent0_13f_1runs_kEMCEGA_kINT7_mannualModeR197302_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/ntuplizerComparison/fout_6_14bins_firstEvent0_13f_1runs_kEMCEGA_kINT7_greenlightTrueR197302_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_noNorm.root  ", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/ntuplizerComparison/", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/ESD/fout_6_14bins_firstEvent0_13f_1runs_kEMCEGA_kINT7_mannualMode_greenlightR197302_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/ESD/fout_6_14bins_firstEvent0_13f_1runs_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorrR197302_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/ntuplizerComparison/fout_6_14bins_firstEvent0_13f_10runs_part1_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/ntuplizerComparison/fout_6_14bins_firstEvent0_13f_10runs_noSkim_part1_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_noNorm.root", path.Data()), "READ");

  TFile* fin = new TFile(Form("%sfout_7_26bins_firstEvent0_13fnew_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_NoISO_RFCheck_RFbinning_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_7_26bins_firstEvent0_13f_new_9runs_noSkim_StdCuts_EX0PurityFit_NoISO_RFCheck_RFbinning_noNorm.root", path.Data()), "READ");

  //13def
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13def/IsoStd/fout_6_14bins_firstEvent0_13def_allruns_noSkim_CALOonly_tof20_newPurity_eCross5_newExoticity_iso_noNorm.root", path.Data()), "READ");//iso < 1.5
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/StdEventsAndClusterCuts/fout_6_14bins_firstEvent0_13def_noSkim_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/noPurityClusterSpectra/fout_6_14bins_firstEvent0_13def_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/SystemChecks/PurityVAriation/MinusPurity/fout_6_14bins_firstEvent0_13def_MinusPurity_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/SystemChecks/PurityVAriation/PlusPurity/fout_6_14bins_firstEvent0_13def_PlusPurity_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/CorrectPurity/fout_6_14bins_firstEvent0_13def_purityNewFitValues_halfWeightForwoPurity_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/CorrectPurity/StdPurity/fout_6_14bins_firstEvent0_13def_StdCuts_CorrectPurityFit_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/CorrectPurity/StdPurity/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFit_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/CorrectPurity/PlusPurity/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PlusPurityFit_NoSigSys_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/CorrectPurity/MinusPurity/fout_6_14bins_firstEvent0_13def_StdCuts_EX0MinusPurityFit_NoSigSys_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/EfficiencySystematics/26/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFitSSC26_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/ISO133/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFit_ISO1Point33_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/ARCComments/ConeAcceptanceCheck/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFit_ConeAcceptanceCheck_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/ARCComments/ConeAcceptanceCheck/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFit_ConeAcceptanceCheckLess4Eta_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/SystemChecks/TOF30/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFit_TOF30_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/ARCComments/ConeAcceptanceCheck/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFit_ConeAcceptanceCheckMore4Eta_ClusterCutHistAfterCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13def/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13def/fout_6_14bins_firstEvent0_13def_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13def/fout_6_14bins_firstEvent0_13def_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13def/fout_6_14bins_firstEvent0_13def_noSkim_StdCuts_EX0PurityFit_ClusterCutHistBeforeCuts_wRunByRunHists_ReCheck_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13def/StdCutsPurity/fout_6_14bins_firstEvent0_13def_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_ReCheck_noNorm.root", path.Data()), "READ");//with std cuts and nonlin
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13def/StdCutsNLPurity/fout_6_14bins_firstEvent0_13def_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_NonlinPurity_noNorm.root", path.Data()), "READ");//with std cuts and nonlinPurity
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/NonLinCorr/compare/13def/StdCutsNLPlusPurity/fout_6_14bins_firstEvent0_13def_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_NonlinPurityPlusNL_noNorm.root", path.Data()), "READ");//with std cuts and nonlinPurity
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/woNL/fout_7_14bins_firstEvent0_13def_noSkim_StdCuts_EX0PurityFit_NoISO_RFCheck_noNorm.root", path.Data()), "READ");//with std cuts, no iso, and nonlinPurity
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/wNL/fout_7_14bins_firstEvent0_13def_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_NoISO_RFCheck_noNorm.root", path.Data()), "READ");//with std cuts, no iso, and nonlinPurity 
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/woNL/fout_1_14bins_firstEvent0_13c_14runs_noThresh_phySel_StdCuts_EX0PurityFit_NoISO_RFCheck_noNorm.root", path.Data()), "READ");//with std cuts, no iso and nonlinPurity
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/wNL/fout_1_14bins_firstEvent0_13c_2runs_part1_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_NoISO_RFCheck_noNorm.root", path.Data()), "READ");//with std cuts, no iso and nonlinPurity
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/woNL/13c/fout_1_14bins_firstEvent0_13c_14runs_noThresh_phySel_run195677__StdCuts_EX0PurityFit_NoISO_RFCheck_noNorm.root", path.Data()), "READ");//Run 195677 with std cuts, no iso, woNL
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/wNL/13c/fout_1_14bins_firstEvent0_13c_run195677_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_NoISO_RFCheck_noNorm.root", path.Data()), "READ");//Run 195677 with std cuts, no iso, wNL
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/run195675/fout_1_26bins_firstEvent0_13c_14runs_noThresh_phySel_part011_StdCuts_EX0PurityFit_NoISO_RFCheck_RFbinning_noNorm.root", path.Data()), "READ");//Run 195677 with std cuts, no iso, wNL
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/run195675/fout_1_26bins_firstEvent0_13c_run195675_kEMCGA_kINT7_kANY_mannualMode_greenlight_woNonLinCorr_StdCuts_EX0PurityFit_NoISO_RFCheck_RFbinning_noNorm.root", path.Data()), "READ");//Run 195677 with std cuts, no iso, wNL
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/run195675/fout_1_26bins_firstEvent0_13c_run195675_kINT7_mannualMode_greenlight_woNonLinCorr_StdCuts_EX0PurityFit_NoISO_RFCheck_RFbinning_noNorm.root", path.Data()), "READ");//Run 195677 with std cuts, no iso, wNL
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/run195675/fout_1_26bins_firstEvent0_13c_run195675_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_NoISO_RFCheck_RFbinning_noNorm.root", path.Data()), "READ");//Run 195677 with std cuts, no iso, wNL
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/Tracking/fout_1_26bins_firstEvent0_13c_14runs_noThresh_phySel_part012_StdCuts_EX0PurityFit_Tracking_RFbinning_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/Tracking/fout_1_26bins_firstEvent0_13c_run195675_kEMCGA_kINT7_kANY_mannualMode_greenlight_woNonLinCorr_StdCuts_EX0PurityFit_Tracking_RFbinning_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/Tracking/fout_1_26bins_firstEvent0_13c_run195675_kINT7_mannualMode_greenlight_nonLinCorr_StdCuts_EX0PurityFit_Tracking_RFbinning_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%srfOutput/pPOutput/Nonlin/UsingCScode/Tracking/fout_1_26bins_firstEvent0_13c_run195675_kINT7_mannualMode_greenlight_woNonLinCorr_StdCuts_EX0PurityFit_Tracking_RFbinning_noNorm.root", path.Data()), "READ");
  
  if(!fin){
    cout << "Can't find file" << endl;
    return;
  }

  //TH1F* hEG1_E = (TH1F*)fin->Get("hEG1Less4Eta");
  //TH1F* hEG2_E = (TH1F*)fin->Get("hEG2Less4Eta");
  //TH1F* hEG1_E = (TH1F*)fin->Get("hEG1More4Eta");
  //TH1F* hEG2_E = (TH1F*)fin->Get("hEG2More4Eta");
  TH1F* hMB_E = (TH1F*)fin->Get("hMB_E");
  TH1F* hEG1_E = (TH1F*)fin->Get("hEG1_E");
  TH1F* hEG2_E = (TH1F*)fin->Get("hEG2_E");
  //TH1F* hEG1woPurity = (TH1F*)fin->Get("hEG1woPurity");
  //TH1F* hEG2woPurity = (TH1F*)fin->Get("hEG2woPurity");
  TH1F* hNormalizer = (TH1F*)fin->Get("hNormalizer");

  Double_t numEvents_MB, numEvents_EG1, numEvents_EG2;
  numEvents_MB = numEvents_EG1 = numEvents_EG2 = 0;
  numEvents_MB = hNormalizer->GetBinContent(11);
  numEvents_EG1 = hNormalizer->GetBinContent(12);
  numEvents_EG2 = hNormalizer->GetBinContent(13);
  cout << "Number of MB events: " << numEvents_MB << endl;
  cout << "Number of EG1 events: " << numEvents_EG1 << endl;
  cout << "Number of EG2 events: " << numEvents_EG2 << endl;
  //const double deltaEta = 0.8;//Less4Eta
  //const double deltaEta = 0.54;//More4Eta
  const double deltaEta = 1.334;
  const double deltaPhi = 1.884;
  double acceptanceNorm = 2*TMath::Pi()/(deltaEta*deltaPhi);

  //MB cluster spectra
  for(int i = 1; i < hMB_E->GetNbinsX()+1; i++){
    double dE = hMB_E->GetBinWidth(i);
    
    double contentMB = hMB_E->GetBinContent(i);
    double tempMB = (contentMB*acceptanceNorm)/((double)numEvents_MB*dE);
    double errorMB = hMB_E->GetBinError(i);
    double tempErrMB = (errorMB*acceptanceNorm)/((double)numEvents_MB*dE);
    if(numEvents_MB) 
      {
	hMB_E->SetBinContent(i,tempMB);
	hMB_E->SetBinError(i, tempErrMB);
      }
    
  }//*/  

  //EG1 cluster spectra
  for(int i = 1; i < hEG1_E->GetNbinsX()+1; i++){
    double dE = hEG1_E->GetBinWidth(i);
    
    double contentEG1 = hEG1_E->GetBinContent(i);
    double tempEG1 = (contentEG1*acceptanceNorm)/((double)numEvents_EG1*dE);
    double errorEG1 = hEG1_E->GetBinError(i);
    double tempErrEG1 = (errorEG1*acceptanceNorm)/((double)numEvents_EG1*dE);
    if(numEvents_EG1) 
      {
	hEG1_E->SetBinContent(i,tempEG1);
	hEG1_E->SetBinError(i, tempErrEG1);
      }
    
  }//*/  

  //EG2 cluster spectra
  for(int i = 1; i < hEG2_E->GetNbinsX()+1; i++){
    double dE = hEG2_E->GetBinWidth(i);
    
    double contentEG2 = hEG2_E->GetBinContent(i);
    double tempEG2 = (contentEG2*acceptanceNorm)/((double)numEvents_EG2*dE);
    double errorEG2 = hEG2_E->GetBinError(i);
    double tempErrEG2 = (errorEG2*acceptanceNorm)/((double)numEvents_EG2*dE);
    if(numEvents_EG2) 
      {
	hEG2_E->SetBinContent(i,tempEG2);
	hEG2_E->SetBinError(i, tempErrEG2);
      }
    
  }//*/

  //EG1 cluster spectra woPurity
  /*for(int i = 1; i < hEG1woPurity->GetNbinsX()+1; i++){
    double dE = hEG1woPurity->GetBinWidth(i);
    
    double contentEG1 = hEG1woPurity->GetBinContent(i);
    double tempEG1 = (contentEG1*acceptanceNorm)/((double)numEvents_EG1*dE);
    double errorEG1 = hEG1woPurity->GetBinError(i);
    double tempErrEG1 = (errorEG1*acceptanceNorm)/((double)numEvents_EG1*dE);
    if(numEvents_EG1) 
      {
	hEG1woPurity->SetBinContent(i,tempEG1);
	hEG1woPurity->SetBinError(i, tempErrEG1);
      }
    
  }//*/  

  //EG2 cluster spectra woPurity
  /*for(int i = 1; i < hEG2woPurity->GetNbinsX()+1; i++){
    double dE = hEG2woPurity->GetBinWidth(i);
    
    double contentEG2 = hEG2woPurity->GetBinContent(i);
    double tempEG2 = (contentEG2*acceptanceNorm)/((double)numEvents_EG2*dE);
    double errorEG2 = hEG2woPurity->GetBinError(i);
    double tempErrEG2 = (errorEG2*acceptanceNorm)/((double)numEvents_EG2*dE);
    if(numEvents_EG2) 
      {
	hEG2woPurity->SetBinContent(i,tempEG2);
	hEG2woPurity->SetBinError(i, tempErrEG2);
      }
    
  }//*/

  hMB_E->SetLineColor(kBlack);
  hMB_E->SetMarkerColor(kBlack);
  hMB_E->SetMarkerStyle(21);
  hMB_E->SetMarkerSize(2);

  hEG1_E->SetLineColor(kRed);
  hEG1_E->SetMarkerColor(kRed);
  hEG1_E->SetMarkerStyle(21);
  hEG1_E->SetMarkerSize(2);

  hEG2_E->SetLineColor(kGreen);
  hEG2_E->SetMarkerColor(kGreen);
  hEG2_E->SetMarkerStyle(21);
  hEG2_E->SetMarkerSize(2);

  /*hEG1woPurity->SetLineColor(kMagenta);
  hEG1woPurity->SetMarkerColor(kMagenta);
  hEG1woPurity->SetMarkerStyle(21);
  hEG1woPurity->SetMarkerSize(2);

  hEG2woPurity->SetLineColor(kCyan);
  hEG2woPurity->SetMarkerColor(kCyan);
  hEG2woPurity->SetMarkerStyle(21);
  hEG2woPurity->SetMarkerSize(2);//*/

  TLegend* legYield = new TLegend(0.6,0.7,0.85,0.85);
  legYield->SetHeader("Photon Yield");
  legYield->AddEntry(hMB_E,"pPb MB");
  legYield->AddEntry(hEG1_E,"pPb EG1");
  legYield->AddEntry(hEG2_E,"pPb EG2");
  //legYield->AddEntry(hEG1woPurity,"pPb EG1");
  //legYield->AddEntry(hEG2woPurity,"pPb EG2");

  TCanvas* c1 = new TCanvas();
  c1->SetLogy();
  hMB_E->Draw("e1");
  hEG1_E->Draw("samee1");
  hEG2_E->Draw("samee1");
  //hEG1woPurity->Draw("samee1");
  //hEG2woPurity->Draw("samee1");
  TString filename = fin->GetName();
  Int_t index = filename.Index("_noNorm");
  filename.Replace(index, 7, "");
  if(filename.CompareTo(fin->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hMB_E->Write("hMB_E");
    hEG1_E->Write("hEG1_E");
    hEG2_E->Write("hEG2_E");
    //hEG1woPurity->Write("hEG1woPurity");
    //hEG2woPurity->Write("hEG2woPurity");
    hNormalizer->Write("hNormalizer");
    fout->Close();
  }//end filename compare
  
}
