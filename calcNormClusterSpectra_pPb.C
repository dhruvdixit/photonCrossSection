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

  
  
  //13f
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/IsoStd/fout_6_14bins_firstEvent0_13f_allruns_noSkim_CALOonly_tof20_newPurity_eCross5_newExoticity_iso_noNorm.root", path.Data()), "READ");//iso < 1.5
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/Iso1/fout_6_14bins_firstEvent0_13f_allruns_noSkim_CALOonly_tof20_newPurity_eCross5_newExoticity_iso1_noNorm.root", path.Data()), "READ");//iso < 1
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13f/Iso2/fout_6_14bins_firstEvent0_13f_allruns_noSkim_CALOonly_tof20_newPurity_eCross5_newExoticity_iso2_noNorm.root", path.Data()), "READ");//iso <2

  //13def
  //TFile* fin = new TFile(Form("%scsOutput/pPbOutput/13def/IsoStd/fout_6_14bins_firstEvent0_13def_allruns_noSkim_CALOonly_tof20_newPurity_eCross5_newExoticity_iso_noNorm.root", path.Data()), "READ");//iso < 1.5
  TFile* fin = new TFile(Form("%scsOutput/pPbOutput/StdEventsAndClusterCuts/fout_6_14bins_firstEvent0_13def_noSkim_noNorm.root", path.Data()), "READ");
  if(!fin){
    cout << "Can't find file" << endl;
    return;
  }

  TH1F* hEG1_E = (TH1F*)fin->Get("hEG1_E");
  TH1F* hEG2_E = (TH1F*)fin->Get("hEG2_E");
  TH1F* hNormalizer = (TH1F*)fin->Get("hNormalizer");

  Double_t numEvents_EG1 = hNormalizer->GetBinContent(12);
  Double_t numEvents_EG2 = hNormalizer->GetBinContent(13);
  cout << "Number of EG1 events: " << numEvents_EG1 << endl;
  cout << "Number of EG2 events: " << numEvents_EG2 << endl;
  const double deltaEta = 1.334;
  const double deltaPhi = 1.884;
  double acceptanceNorm = 2*TMath::Pi()/(deltaEta*deltaPhi);

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
  
  TCanvas* c1 = new TCanvas();
  c1->SetLogy();
  hEG1_E->Draw("e1");
  hEG2_E->Draw("samee1");
  TString filename = fin->GetName();
  Int_t index = filename.Index("_noNorm");
  filename.Replace(index, 7, "");
  if(filename.CompareTo(fin->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hEG1_E->Write("hEG1_E");
    hEG2_E->Write("hEG2_E");
    hNormalizer->Write("hNormalizer");
    fout->Close();
  }//end filename compare
  
}
