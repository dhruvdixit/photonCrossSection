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
  TFile* fin = new TFile(Form("%scsOutput/ppOutput/CorrectPurity/PlusPurity/fout_4_14bins_firstEvent0_17qAll_StdCuts_EX0PlusPurityFit_NoSigSys_noNorm.root", path.Data()), "READ");
  
  TH1F* hEG2_caloE = (TH1F*)fin->Get("hEG2_caloE");
  TH1F* hNormalizer = (TH1F*)fin->Get("hNormalizer");

  Double_t numEvents_EG2calo = hNormalizer->GetBinContent(11);
  cout << "Number of EG2 events: " << numEvents_EG2calo << endl;
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
  
  TCanvas* c1 = new TCanvas();
  c1->SetLogy();
  hEG2_caloE->Draw("e1");
  TString filename = fin->GetName();
  Int_t index = filename.Index("_noNorm");
  filename.Replace(index, 7, "");
  if(filename.CompareTo(fin->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hEG2_caloE->Write("hEG2_caloE");
    hNormalizer->Write("hNormalizer");
    fout->Close();
  }//end filename compare
  
}
