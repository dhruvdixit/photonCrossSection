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

void calcNormClusterSpectra_pp(){

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

  //TFile* fin = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_ITSonly_CALOonly_tof20_newPurity_eCross5_newExoticity_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_allpp_CALOonly_tof20_newPurity_eCross5_newExoticity_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/ISO1GeV/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_CALOonly_tof20_newPurity_eCross5_newExoticity_UEstudyIso1GeV_noNorm2.root", path.Data()), "READ");//ISO 1 GeV
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/ISOStd/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_CALOonly_tof20_newPurity_eCross5_newExoticity_UEstudyIsoGeV_noNorm2.root", path.Data()), "READ");//ISO 1.5 GeV
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/ISO2GeV/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_CALOonly_tof20_newPurity_eCross5_newExoticity_UEstudyIso2GeV_noNorm2.root", path.Data()), "READ");//ISO 2 GeV
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/StdEventsAndClusterCuts/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/StdEventsAndClusterCuts/fout_4_14bins_firstEvent0_17q_all_phySel_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/SystemChecks/PurityVAriation/MinusPurity/fout_4_14bins_firstEvent0_17q_All_MinusPurity_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/SystemChecks/PurityVAriation/PlusPurity/fout_4_14bins_firstEvent0_17q_All_PlusPurity_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/CorrectPurity/StdPurity/fout_4_14bins_firstEvent0_17qAll_StdCuts_CorrectPurityFit_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/CorrectPurity/PlusPurity/fout_4_14bins_firstEvent0_17qAll_StdCuts_EX0PlusPurityFit_AntiIsoSysOnly_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/CorrectPurity/MinusPurity/fout_4_14bins_firstEvent0_17qAll_StdCuts_EX0MinusPurityFit_AntiIsoSysOnly_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/CorrectPurity/StdPurity/fout_4_14bins_firstEvent0_17q_ITSonly_StdCuts_EX0PurityFit_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/EfficiencySystematics/26/fout_4_14bins_firstEvent0_17q_ITSonly_StdCuts_EX0PurityFitSSC26_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/CorrectPurity/PlusPurity/fout_4_14bins_firstEvent0_17qAll_StdCuts_EX0PlusPurityFit_NoSigSys_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/SystemChecks/TOF30/fout_4_14bins_firstEvent0_17qAll_StdCuts_EX0PurityFit_TOF30_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/ARCComments/ConeAcceptanceCheck/fout_4_14bins_firstEvent0_17All_StdCuts_EX0PurityFit_ConeAcceptanceCheckLess4Eta_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/ARCComments/ConeAcceptanceCheck/fout_4_14bins_firstEvent0_17qAll_StdCuts_EX0PurityFit_ConeAcceptanceCheckMore4Eta_ClusterCutHistAfterCuts_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_r282440_noThresh_muoncalopass1_phySel_StdCuts_EX0PurityFit_onlyRun282440_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_part000_StdCuts_EX0PurityFit_onlyRun282440_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_ITSonly_1runs_part1_kCaloOnlykINTkAny_mannualAndGreen_split10_wNL_StdCuts_EX0PurityFit_onlyRun282440_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_ITSonly_1runs_part1_kMuonCalo_mannualAndGreen_split10_wNL_StdCuts_EX0PurityFit_onlyRun282440_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_ITSonly_1runs_part2_kMuonCalo_mannualAndGreen_split5_wNL_StdCuts_EX0PurityFit_run282437_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_part001_StdCuts_EX0PurityFit_run282437_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/NonLin/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_partAll_StdCuts_EX0PurityFit_ReCheck_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/NonLin/fout_4_14bins_firstEvent0_17q_ITSonly_runAll_kMuonCalo_mannualAndGreen_split5_wNL_StdCuts_EX0PurityFit_ReCheck_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_part007_StdCuts_EX0PurityFit_run282393_ReCheck_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%sfout_4_14bins_firstEvent0_17q_ITSonly_run282393_kMuonCalo_mannualAndGreen_split5_wNL_StdCuts_EX0PurityFit_run282402_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/NonLin/StdCutsNLPurity/fout_4_14bins_firstEvent0_17q_ITSonly_allRuns_kMuonCalo_mannualAndGreen_split10_wNL_StdCuts_EX0PurityFit_NonlinPurity_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/NonLin/StdCutsNLMinusPurity/fout_4_14bins_firstEvent0_17q_ITSonly_runsAll_kMuonCalo_mannualAndGreen_split5_wNL_StdCuts_EX0PurityFit_NonlinPurityMinusNL_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/NonLin/EmcalCorrectionCompare/fout_4_14bins_firstEvent0_17q_noCorrections_nonlinFunction_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/NonLin/EmcalCorrectionCompare/fout_4_14bins_firstEvent0_17q_allCorrections_nonlinFunction_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/NonLin/EmcalCorrectionCompare/fout_4_14bins_firstEvent0_17q_noNLTemp_nonlinFunction_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/NonLin/EmcalCorrectionCompare/fout_4_14bins_firstEvent0_17q_noNLOnly_nonlinFunction_noNorm.root", path.Data()), "READ");
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/17q/ntuplizerComparison/Feb20AliPhysics/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_part000_StdCuts_EX0PurityFit_run282440_noNorm.root", path.Data()), "READ");//Using Feb 20,2022 AliPhysics gh ntuple
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/17q/ntuplizerComparison/Feb20AliPhysics/fout_4_14bins_firstEvent0_17q_run282440_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_run282440_noNorm.root", path.Data()), "READ");//post QM ntuple, feb 20, 2022 AliPhysics
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/fout_4_14bins_firstEvent0_17q_3runs_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_postQM_noNorm.root", path.Data()), "READ");//post QM ntuple, feb 20, 2022 AliPhysics
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/ghNtuplpes/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_part0001234_StdCuts_EX0PurityFit_postQM_noNorm.root", path.Data()), "READ");//using gh ntuples to compare with post QM ntuples
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/CutFlowAfterCuts/fout_4_14bins_firstEvent0_17q_runAll_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit__CutFlowAfterCuts_noNorm.root", path.Data()), "READ");//using gh ntuples to compare with post QM ntuples - all runs
  //TFile* fin = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/wEtaCorr/fout_4_14bins_firstEvent0_17q_runAll_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_wEtaCorr_noNorm.root", path.Data()), "READ");//post QM ntuples wEtaCorr and no runs 282440 and 282365
   TFile* fin = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/wPhiCorr/fout_4_14bins_firstEvent0_17q_runAll_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_wPhiCorr_noNorm.root", path.Data()), "READ");//post QM ntuples wPhiCorr and no runs 282440 and 282365
   
  
  TH1F* hEG2_caloE = (TH1F*)fin->Get("hEG2_caloE");
  TH1F* hEG2woPurity = (TH1F*)fin->Get("hEG2woPurity");  
  TH1F* hNormalizer = (TH1F*)fin->Get("hNormalizer");

  Double_t numEvents_EG2calo = hNormalizer->GetBinContent(11);
  cout << "Number of EG2 events: " << numEvents_EG2calo << endl;
  //const double deltaEta = 0.8;//Less4Eta
  //const double deltaEta = 0.54;//More4Eta
  const double deltaEta = 1.334;
  const double deltaPhi = 1.884;
  double acceptanceNorm = 2*TMath::Pi()/(deltaEta*deltaPhi);

  for(int i = 1; i < hEG2_caloE->GetNbinsX()+1; i++){
    double dE = hEG2_caloE->GetBinWidth(i);
    
    double contentEG2 = hEG2_caloE->GetBinContent(i);
    double tempEG2 = (contentEG2*acceptanceNorm)/((double)numEvents_EG2calo*dE);
    double errorEG2 = hEG2_caloE->GetBinError(i);
    double tempErrEG2 = (errorEG2*acceptanceNorm)/((double)numEvents_EG2calo*dE);
    if(numEvents_EG2calo) 
      {
	hEG2_caloE->SetBinContent(i,tempEG2);
	hEG2_caloE->SetBinError(i, tempErrEG2);
      }
    
  }//*/  

  for(int i = 1; i < hEG2woPurity->GetNbinsX()+1; i++){
    double dE = hEG2woPurity->GetBinWidth(i);
    
    double contentEG2 = hEG2woPurity->GetBinContent(i);
    double tempEG2 = (contentEG2*acceptanceNorm)/((double)numEvents_EG2calo*dE);
    double errorEG2 = hEG2woPurity->GetBinError(i);
    double tempErrEG2 = (errorEG2*acceptanceNorm)/((double)numEvents_EG2calo*dE);
    if(numEvents_EG2calo) 
      {
	hEG2woPurity->SetBinContent(i,tempEG2);
	hEG2woPurity->SetBinError(i, tempErrEG2);
      }
    
  }//*/  

  hEG2_caloE->SetLineColor(kGreen);
  hEG2_caloE->SetMarkerColor(kGreen);
  hEG2_caloE->SetMarkerStyle(21);
  hEG2_caloE->SetMarkerSize(2);

  hEG2woPurity->SetLineColor(kCyan);
  hEG2woPurity->SetMarkerColor(kCyan);
  hEG2woPurity->SetMarkerStyle(21);
  hEG2woPurity->SetMarkerSize(2);//*/
  
  TCanvas* c1 = new TCanvas();
  c1->SetLogy();
  hEG2_caloE->Draw("e1");
  hEG2woPurity->Draw("same e1");
  TString filename = fin->GetName();
  Int_t index = filename.Index("_noNorm");
  filename.Replace(index, 7, "");
  if(filename.CompareTo(fin->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hEG2_caloE->Write("hEG2_caloE");
    hEG2woPurity->Write("hEG2woPurity");    
    hNormalizer->Write("hNormalizer");
    fout->Close();
  }//end filename compare
  
}
