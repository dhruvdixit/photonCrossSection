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

void makeClusterSpectraComparison_pp(){

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


  //Effects of isolation/UE on cluster spectra
  TFile* inFile_iso = new TFile(Form("%scsOutput/ppOutput/ISOStd/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_CALOonly_tof20_newPurity_eCross5_newExoticity_UEstudyIsoGeV2.root", path.Data()), "READ");
  TFile* inFile_iso1 = new TFile(Form("%scsOutput/ppOutput/ISO1GeV/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_CALOonly_tof20_newPurity_eCross5_newExoticity_UEstudyIso1GeV.root", path.Data()), "READ");//ISO 1 GeV
  TFile* inFile_iso2 = new TFile(Form("%scsOutput/ppOutput/ISO2GeV/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_CALOonly_tof20_newPurity_eCross5_newExoticity_UEstudyIso2GeV.root", path.Data()), "READ");//ISO 2 GeV
  
  TH1F* hEG2_iso = (TH1F*)inFile_iso->Get("hEG2_caloE");
  TH1F* hEG2_iso1 = (TH1F*)inFile_iso1->Get("hEG2_caloE");
  TH1F* hEG2_iso2 = (TH1F*)inFile_iso2->Get("hEG2_caloE");

  hEG2_iso->SetLineColor(kRed); hEG2_iso->SetMarkerColor(kRed); hEG2_iso->SetMarkerStyle(kFullCircle);
  hEG2_iso1->SetLineColor(kBlue); hEG2_iso1->SetMarkerColor(kBlue); hEG2_iso1->SetMarkerStyle(kFullCircle);
  hEG2_iso2->SetLineColor(kGreen); hEG2_iso2 ->SetMarkerColor(kGreen); hEG2_iso2->SetMarkerStyle(kFullCircle); 

  TCanvas* c1 = new TCanvas();
  c1->SetLogy();
  hEG2_iso->Draw("e1");
  hEG2_iso1->Draw("samee1");
  hEG2_iso2->Draw("samee1");

  TLegend* l1 = new TLegend(0.6, 0.6, 0.85, 0.85);
  l1->SetBorderSize(0);
  l1->AddEntry(hEG2_iso, "isolation < 1.5 GeV");
  l1->AddEntry(hEG2_iso1, "isolation < 1.0 GeV");
  l1->AddEntry(hEG2_iso2, "isolation < 2.0 GeV");
  l1->Draw("same");

  TH1F* ratio_iso1 = (TH1F*)hEG2_iso1->Clone("ratio_iso1");
  ratio_iso1->Divide(hEG2_iso);
  TH1F* ratio_iso2 = (TH1F*)hEG2_iso2->Clone("ratio_iso2");
  ratio_iso2->Divide(hEG2_iso);

  TCanvas* c2 = new TCanvas();
  ratio_iso1->SetTitle(";E_{T} [GeV]; ratio to iso < 1.5");
  ratio_iso1->GetYaxis()->SetRangeUser(0.5, 1.5);
  ratio_iso1->Draw("e1");
  ratio_iso2->Draw("samee1");

  TLegend* l2 = new TLegend(0.6, 0.6, 0.85, 0.85);
  l2->SetBorderSize(0);
  l2->AddEntry(ratio_iso1, "isolation < 1.0 GeV");
  l2->AddEntry(ratio_iso2, "isolation < 2.0 GeV");
  l2->Draw("same");

}
