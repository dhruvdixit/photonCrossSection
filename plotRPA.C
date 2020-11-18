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

void plotRPA(){

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
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/xSectionHists/";

  TFile* finMine = new TFile(Form("%s_crossSectionHistos_allpPb_allpp_cc_junk_rfpp_mine_finalpp.root", path.Data()), "READ");
  TFile* finErwann = new TFile(Form("%s_crossSectionHistos_allpPb_allpp_cc_junk_rfpp_erwann_finalpp.root", path.Data()), "READ");

  TH1F* mine = (TH1F*)finMine->Get("h_RpA");
  mine->SetName("mine");
  mine->SetLineColor(kRed);
  mine->SetMarkerColor(kRed);

  TH1F* erwann = (TH1F*)finErwann->Get("h_RpA");
  erwann->SetName("erwann");
  erwann->SetLineColor(kBlack);
  erwann->SetMarkerColor(kBlack);

  TCanvas* c1 = new TCanvas();
  mine->Draw("e1");
  erwann->Draw("samee1");

  mine->Fit("pol0", "0", "", 12, 60);
  erwann->Fit("pol0", "0", "", 12, 60);
  
  TLine* lineM = new TLine(12, 0.94, 60, 0.94);
  lineM->SetLineColorAlpha(kRed, 0.3);
  lineM->SetLineWidth(7);
  lineM->Draw("same");
  TLine* lineE = new TLine(12, 0.94, 60, 0.94);
  lineE->SetLineColorAlpha(kBlack, 0.3);
  lineE->SetLineWidth(7);
  lineE->Draw("same");
  TLine* lineU = new TLine(12, 1.0, 60, 1.0);
  lineU->SetLineColorAlpha(kBlue, 0.3);
  lineU->SetLineStyle(9);
  lineU->SetLineWidth(7);
  lineU->Draw("same");

  
  TLegend* leg = new TLegend(0.3, 0.65, 0.8, 0.9);
  leg->SetHeader("ALICE R_{pPb}, pp & p-Pb #sqrt{s_{NN}} = 5.02 TeV");
  //leg->AddEntry((TObject*)0, "ALICE R_{pPb} pp & p-Pb #sqrt{s_{NN}} = 5.02 TeV", "");
  leg->SetNColumns(2);
  leg->AddEntry(mine, "Dhruv's p-Pb");
  leg->AddEntry(lineM, "Constant Fit (12-60)GeV, R_{pPb} = 0.94#pm0.05", "l");
  leg->AddEntry(erwann, "Erwann's p-Pb");
  leg->AddEntry(lineE, "Constant Fit (12-60)GeV, R_{pPb} = 0.95#pm0.05", "l");
  leg->Draw("same");

}
