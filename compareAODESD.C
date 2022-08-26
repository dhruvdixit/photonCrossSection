#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TVector2.h"
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

void compareAODESD(){
  
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
  
  
  TString path = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/NonLinCorr/AOD/ITSvHybrid/";
  
  TFile* file1 = new TFile(Form("%sfout_6_14bins_firstEvent0_13f_new_9runs_noSkim_part1_StdCuts_EX0PurityFit_HybridISO_clusterpTMore12GeV_clusterCutsFlowAfter_noNorm.root", path.Data()), "READ");
  TFile* file3 = new TFile(Form("%sfout_6_14bins_firstEvent0_13fnew_9runs_AOD210_apr10AliPhysics_ghCorr_kEMCGAkINT7_StdCuts_EX0PurityFit_HybridISO_clusterpTMore12GeV_clusterCutsFlowAfter_noNorm.root", path.Data()), "READ");

  //Event count histogram
  TH1F* hNormalizer1 = (TH1F*)file1->Get("hNormalizer");
  TH1F* hNormalizer3 = (TH1F*)file3->Get("hNormalizer");
  Double_t passAll1 = hNormalizer1->GetBinContent(5);
  Double_t passAll3 = hNormalizer3->GetBinContent(5);
  Double_t numEG11 = hNormalizer1->GetBinContent(12);
  Double_t numEG13 = hNormalizer3->GetBinContent(12);
  cout << "Event count old ESD: " << passAll1 << ", " << numEG11 << endl;
  cout << "Event count AOD: " << passAll3 << ", " << numEG13 << endl;
  
  //Cluster cut histograms
  TH1F* hCluster_tof1 = (TH1F*)file1->Get("hCluster_tof");
  TH1F* hExoticity1 = (TH1F*)file1->Get("hExoticity");
  TH1F* hNcell1 = (TH1F*)file1->Get("hNcell");
  TH1F* hNLM1 = (TH1F*)file1->Get("hNLM");
  TH1F* hD2BC1 = (TH1F*)file1->Get("hD2BC");
  TH1F* hEta1 = (TH1F*)file1->Get("hEta");
  TH1F* hPhi1 = (TH1F*)file1->Get("hPhi");
  TH1F* hShowerShape1 = (TH1F*)file1->Get("hShowerShape");
  TH1F* hIsolation1 = (TH1F*)file1->Get("hIsolation");
  hCluster_tof1->Scale(1.0/passAll1);
  hExoticity1->Scale(1.0/passAll1);
  hNcell1->Scale(1.0/passAll1);
  hNLM1->Scale(1.0/passAll1);
  hD2BC1->Scale(1.0/passAll1);
  hEta1->Scale(1.0/passAll1);
  hPhi1->Scale(1.0/passAll1);
  hShowerShape1->Scale(1.0/passAll1);
  hIsolation1->Scale(1.0/passAll1);
  hCluster_tof1->SetTitle("cluster tof; cluster_tof (ns); counts/Num_{eve}");
  hExoticity1->SetTitle("Exoticity; exoticity; counts/Num_{eve}");
  hNcell1->SetTitle("N cell; N cell; counts/Num_{eve}");
  hNLM1->SetTitle("Number of local maxima; NLM; counts/Num_{eve}");
  hD2BC1->SetTitle("Distance to bad channels; dist bc; counts/Num_{eve}");
  hEta1->SetTitle("cluster eta; #eta; counts/Num_{eve}");
  hPhi1->SetTitle("cluster phi; #varphi; counts/Num_{eve}");
  hShowerShape1->SetTitle("Shower Shape; #sigma^{2}_{long}; counts/Num_{eve}");
  hIsolation1->SetTitle("Hybrid tracking isolation; isolation (GeV/c); counts/Num_{eve}");
  hIsolation1->GetXaxis()->SetRangeUser(-50, 500);
  TH1F* hCluster_tof1_ctflw = (TH1F*)file1->Get("hCluster_tof_ctflw");
  TH1F* hExoticity1_ctflw = (TH1F*)file1->Get("hExoticity_ctflw");
  TH1F* hNcell1_ctflw = (TH1F*)file1->Get("hNcell_ctflw");
  TH1F* hNLM1_ctflw = (TH1F*)file1->Get("hNLM_ctflw");
  TH1F* hD2BC1_ctflw = (TH1F*)file1->Get("hD2BC_ctflw");
  TH1F* hEta1_ctflw = (TH1F*)file1->Get("hEta_ctflw");
  TH1F* hPhi1_ctflw = (TH1F*)file1->Get("hPhi_ctflw");
  TH1F* hShowerShape1_ctflw = (TH1F*)file1->Get("hShowerShape_ctflw");
  TH1F* hIsolation1_ctflw = (TH1F*)file1->Get("hIsolation_ctflw");
  hCluster_tof1_ctflw->Scale(1.0/passAll1);
  hExoticity1_ctflw->Scale(1.0/passAll1);
  hNcell1_ctflw->Scale(1.0/passAll1);
  hNLM1_ctflw->Scale(1.0/passAll1);
  hD2BC1_ctflw->Scale(1.0/passAll1);
  hEta1_ctflw->Scale(1.0/passAll1);
  hPhi1_ctflw->Scale(1.0/passAll1);
  hShowerShape1_ctflw->Scale(1.0/passAll1);
  hIsolation1_ctflw->Scale(1.0/passAll1);
  hCluster_tof1_ctflw->SetTitle("cluster tof; cluster_tof (ns); counts/Num_{eve}");
  hExoticity1_ctflw->SetTitle("Exoticity; exoticity; counts/Num_{eve}");
  hNcell1_ctflw->SetTitle("N cell; N cell; counts/Num_{eve}");
  hNLM1_ctflw->SetTitle("Number of local maxima; NLM; counts/Num_{eve}");
  hD2BC1_ctflw->SetTitle("Distance to bad channels; dist bc; counts/Num_{eve}");
  hEta1_ctflw->SetTitle("cluster eta; #eta; counts/Num_{eve}");
  hPhi1_ctflw->SetTitle("cluster phi; #varphi; counts/Num_{eve}");
  hShowerShape1_ctflw->SetTitle("Shower Shape; #sigma^{2}_{long}; counts/Num_{eve}");
  hIsolation1_ctflw->SetTitle("Hybrid tracking isolation; isolation (GeV/c); counts/Num_{eve}");
  hIsolation1_ctflw->GetXaxis()->SetRangeUser(-50, 500);
  
  TH1F* hCluster_tof3 = (TH1F*)file3->Get("hCluster_tof");
  TH1F* hExoticity3 = (TH1F*)file3->Get("hExoticity");
  TH1F* hNcell3 = (TH1F*)file3->Get("hNcell");
  TH1F* hNLM3 = (TH1F*)file3->Get("hNLM");
  TH1F* hD2BC3 = (TH1F*)file3->Get("hD2BC");
  TH1F* hEta3 = (TH1F*)file3->Get("hEta");
  TH1F* hPhi3 = (TH1F*)file3->Get("hPhi");
  TH1F* hShowerShape3 = (TH1F*)file3->Get("hShowerShape");
  TH1F* hIsolation3 = (TH1F*)file3->Get("hIsolation");
  hCluster_tof3->Scale(1.0/passAll3);
  hExoticity3->Scale(1.0/passAll3);
  hNcell3->Scale(1.0/passAll3);
  hNLM3->Scale(1.0/passAll3);
  hD2BC3->Scale(1.0/passAll3);
  hEta3->Scale(1.0/passAll3);
  hPhi3->Scale(1.0/passAll3);
  hShowerShape3->Scale(1.0/passAll3);
  hIsolation3->Scale(1.0/passAll3);
  hCluster_tof3->SetLineColor(kRed);
  hExoticity3->SetLineColor(kRed);
  hNcell3->SetLineColor(kRed);
  hNLM3->SetLineColor(kRed);
  hD2BC3->SetLineColor(kRed);
  hEta3->SetLineColor(kRed);
  hPhi3->SetLineColor(kRed);
  hShowerShape3->SetLineColor(kRed);
  hIsolation3->SetLineColor(kRed);
  hCluster_tof3->SetTitle("cluster tof; cluster_tof (ns); counts/Num_{eve}");
  hExoticity3->SetTitle("Exoticity; exoticity; counts/Num_{eve}");
  hNcell3->SetTitle("N cell; N cell; counts/Num_{eve}");
  hNLM3->SetTitle("Number of local maxima; NLM; counts/Num_{eve}");
  hD2BC3->SetTitle("Distance to bad channels; dist bc; counts/Num_{eve}");
  hEta3->SetTitle("cluster eta; #eta; counts/Num_{eve}");
  hPhi3->SetTitle("cluster phi; #varphi; counts/Num_{eve}");
  hShowerShape3->SetTitle("Shower Shape; #sigma^{2}_{long}; counts/Num_{eve}");
  hIsolation3->SetTitle("Hybrid tracking isolation; isolation (GeV/c); counts/Num_{eve}");
  hIsolation3->GetXaxis()->SetRangeUser(-5, 25);
  TH1F* hCluster_tof3_ctflw = (TH1F*)file3->Get("hCluster_tof_ctflw");
  TH1F* hExoticity3_ctflw = (TH1F*)file3->Get("hExoticity_ctflw");
  TH1F* hNcell3_ctflw = (TH1F*)file3->Get("hNcell_ctflw");
  TH1F* hNLM3_ctflw = (TH1F*)file3->Get("hNLM_ctflw");
  TH1F* hD2BC3_ctflw = (TH1F*)file3->Get("hD2BC_ctflw");
  TH1F* hEta3_ctflw = (TH1F*)file3->Get("hEta_ctflw");
  TH1F* hPhi3_ctflw = (TH1F*)file3->Get("hPhi_ctflw");
  TH1F* hShowerShape3_ctflw = (TH1F*)file3->Get("hShowerShape_ctflw");
  TH1F* hIsolation3_ctflw = (TH1F*)file3->Get("hIsolation_ctflw");
  hCluster_tof3_ctflw->Scale(1.0/passAll3);
  hExoticity3_ctflw->Scale(1.0/passAll3);
  hNcell3_ctflw->Scale(1.0/passAll3);
  hNLM3_ctflw->Scale(1.0/passAll3);
  hD2BC3_ctflw->Scale(1.0/passAll3);
  hEta3_ctflw->Scale(1.0/passAll3);
  hPhi3_ctflw->Scale(1.0/passAll3);
  hShowerShape3_ctflw->Scale(1.0/passAll3);
  hIsolation3_ctflw->Scale(1.0/passAll3);
  hCluster_tof3_ctflw->SetLineColor(kRed);
  hExoticity3_ctflw->SetLineColor(kRed);
  hNcell3_ctflw->SetLineColor(kRed);
  hNLM3_ctflw->SetLineColor(kRed);
  hD2BC3_ctflw->SetLineColor(kRed);
  hEta3_ctflw->SetLineColor(kRed);
  hPhi3_ctflw->SetLineColor(kRed);
  hShowerShape3_ctflw->SetLineColor(kRed);
  hIsolation3_ctflw->SetLineColor(kRed);
  hCluster_tof3_ctflw->SetTitle("cluster tof; cluster_tof (ns); counts/Num_{eve}");
  hExoticity3_ctflw->SetTitle("Exoticity; exoticity; counts/Num_{eve}");
  hNcell3_ctflw->SetTitle("N cell; N cell; counts/Num_{eve}");
  hNLM3_ctflw->SetTitle("Number of local maxima; NLM; counts/Num_{eve}");
  hD2BC3_ctflw->SetTitle("Distance to bad channels; dist bc; counts/Num_{eve}");
  hEta3_ctflw->SetTitle("cluster eta; #eta; counts/Num_{eve}");
  hPhi3_ctflw->SetTitle("cluster phi; #varphi; counts/Num_{eve}");
  hShowerShape3_ctflw->SetTitle("Shower Shape; #sigma^{2}_{long}; counts/Num_{eve}");
  hIsolation3_ctflw->SetTitle("Hybrid tracking isolation; isolation (GeV/c); counts/Num_{eve}");
  hIsolation3_ctflw->GetXaxis()->SetRangeUser(-5, 25);
  
  TCanvas* clusCuts3 = new TCanvas("clusCuts3", "clusCuts3", 1800, 1800);
  clusCuts3->Divide(3, 3);
  clusCuts3->cd(1); hCluster_tof3->Draw("e1"); hCluster_tof1->Draw("same e1");
  clusCuts3->cd(2); hExoticity3->Draw("e1"); hExoticity1->Draw("same e1");
  clusCuts3->cd(3); hNcell3->Draw("e1"); hNcell1->Draw("same e1");
  clusCuts3->cd(4); hNLM3->Draw("e1"); hNLM1->Draw("same e1");
  clusCuts3->cd(5); hD2BC3->Draw("e1"); hD2BC1->Draw("same e1");
  clusCuts3->cd(6); hEta3->Draw("e1"); hEta1->Draw("same e1");
  clusCuts3->cd(7); hPhi3->Draw("e1"); hPhi1->Draw("same e1");
  clusCuts3->cd(8); hShowerShape3->Draw("e1"); hShowerShape1->Draw("same e1");
  clusCuts3->cd(9); hIsolation3->Draw("e1");  hIsolation1->Draw("same e1");

  TCanvas* clusCuts3_ctflw = new TCanvas("clusCuts3_ctflw", "clusCuts3_ctflw", 1800, 1800);
  clusCuts3_ctflw->Divide(3, 3);
  clusCuts3_ctflw->cd(1); hCluster_tof3_ctflw->Draw("e1"); hCluster_tof1_ctflw->Draw("same e1");
  clusCuts3_ctflw->cd(2); hExoticity3_ctflw->Draw("e1"); hExoticity1_ctflw->Draw("same e1");
  clusCuts3_ctflw->cd(3); hNcell3_ctflw->Draw("e1"); hNcell1_ctflw->Draw("same e1");
  clusCuts3_ctflw->cd(4); hNLM3_ctflw->Draw("e1"); hNLM1_ctflw->Draw("same e1");
  clusCuts3_ctflw->cd(5); hD2BC3_ctflw->Draw("e1"); hD2BC1_ctflw->Draw("same e1");
  clusCuts3_ctflw->cd(6); hEta3_ctflw->Draw("e1"); hEta1_ctflw->Draw("same e1");
  clusCuts3_ctflw->cd(7); hPhi3_ctflw->Draw("e1"); hPhi1_ctflw->Draw("same e1");
  clusCuts3_ctflw->cd(8); hShowerShape3_ctflw->Draw("e1"); hShowerShape1_ctflw->Draw("same e1");
  clusCuts3_ctflw->cd(9); hIsolation3_ctflw->Draw("e1");  hIsolation1_ctflw->Draw("same e1");

  TH1F* hCluster_tof_ratio = (TH1F*)hCluster_tof1->Clone("hCluster_tof_ratio");
  TH1F* hExoticity_ratio = (TH1F*)hExoticity1->Clone("hExoticity_ratio");
  TH1F* hNcell_ratio = (TH1F*)hNcell1->Clone("hNcell_ratio");
  TH1F* hNLM_ratio = (TH1F*)hNLM1->Clone("hNLM_ratio");
  TH1F* hD2BC_ratio = (TH1F*)hD2BC1->Clone("hD2BC_ratio");
  TH1F* hEta_ratio = (TH1F*)hEta1->Clone("hEta_ratio");
  TH1F* hPhi_ratio = (TH1F*)hPhi1->Clone("hPhi_ratio");
  TH1F* hShowerShape_ratio = (TH1F*)hShowerShape1->Clone("hShowerShape_ratio");
  TH1F* hIsolation_ratio = (TH1F*)hIsolation1->Clone("hIsolation_ratio");
  hCluster_tof_ratio->SetTitle("cluster tof; cluster_tof (ns); ESD/AOD");
  hExoticity_ratio->SetTitle("Exoticity; exoticity; ESD/AOD");
  hNcell_ratio->SetTitle("N cell; N cell; ESD/AOD");
  hNLM_ratio->SetTitle("Number of local maxima; NLM; ESD/AOD");
  hD2BC_ratio->SetTitle("Distance to bad channels; dist bc; ESD/AOD");
  hEta_ratio->SetTitle("cluster eta; #eta; ESD/AOD");
  hPhi_ratio->SetTitle("cluster phi; #varphi; ESD/AOD");
  hShowerShape_ratio->SetTitle("Shower Shape; #sigma^{2}_{long}; ESD/AOD");
  hIsolation_ratio->SetTitle("Hybrid tracking isolation; isolation (GeV/c); ESD/AOD");
  hCluster_tof_ratio->Divide(hCluster_tof3);
  hExoticity_ratio->Divide(hExoticity3);
  hNcell_ratio->Divide(hNcell3);
  hNLM_ratio->Divide(hNLM3);
  hD2BC_ratio->Divide(hD2BC3);
  hEta_ratio->Divide(hEta3);
  hPhi_ratio->Divide(hPhi3);
  hShowerShape_ratio->Divide(hShowerShape3);
  hIsolation_ratio->Divide(hIsolation3);
  hIsolation_ratio->GetXaxis()->SetRangeUser(-5, 25);
  TCanvas* clusCuts_ratio = new TCanvas("clusCuts_ratio", "clusCuts_ratio", 1800, 1800);
  clusCuts_ratio->Divide(3, 3);
  clusCuts_ratio->cd(1); hCluster_tof_ratio->Draw("e1");
  clusCuts_ratio->cd(2); hExoticity_ratio->Draw("e1");
  clusCuts_ratio->cd(3); hNcell_ratio->Draw("e1");
  clusCuts_ratio->cd(4); hNLM_ratio->Draw("e1");
  clusCuts_ratio->cd(5); hD2BC_ratio->Draw("e1");
  clusCuts_ratio->cd(6); hEta_ratio->Draw("e1"); 
  clusCuts_ratio->cd(7); hPhi_ratio->Draw("e1"); 
  clusCuts_ratio->cd(8); hShowerShape_ratio->Draw("e1");
  clusCuts_ratio->cd(9); hIsolation_ratio->Draw("e1");  
  

  //Cluster spectra hists
  TH1F* hRaw1 = (TH1F*)file1->Get("hRaw_pt");
  TH1F* hNOISO1 = (TH1F*)file1->Get("hCluster_pt_noISO");
  TH1F* hCluster1 = (TH1F*)file1->Get("hCluster_pt");
  TH1F* hRaw3 = (TH1F*)file3->Get("hRaw_pt");
  TH1F* hNOISO3 = (TH1F*)file3->Get("hCluster_pt_noISO");
  TH1F* hCluster3 = (TH1F*)file3->Get("hCluster_pt");

  for(int i = 1; i < hRaw3->GetNbinsX()+1; i++){
    double dE = hRaw3->GetBinWidth(i);
    
    //Raw hists
    double contentRaw1 = hRaw1->GetBinContent(i);
    double tempRaw1 = (contentRaw1)/((double)passAll1*dE);
    double errorRaw1 = hRaw1->GetBinError(i);
    double tempErrRaw1 = (errorRaw1)/((double)passAll1*dE);
    if(passAll1) 
      {
	hRaw1->SetBinContent(i,tempRaw1);
	hRaw1->SetBinError(i, tempErrRaw1);
      }
    double contentRaw3 = hRaw3->GetBinContent(i);
    double tempRaw3 = (contentRaw3)/((double)passAll3*dE);
    double errorRaw3 = hRaw3->GetBinError(i);
    double tempErrRaw3 = (errorRaw3)/((double)passAll3*dE);
    if(passAll3) 
      {
	hRaw3->SetBinContent(i,tempRaw3);
	hRaw3->SetBinError(i, tempErrRaw3);
      }

    //No iso hist
    double contentNOISO1 = hNOISO1->GetBinContent(i);
    double tempNOISO1 = (contentNOISO1)/((double)passAll1*dE);
    double errorNOISO1 = hNOISO1->GetBinError(i);
    double tempErrNOISO1 = (errorNOISO1)/((double)passAll1*dE);
    if(passAll1) 
      {
	hNOISO1->SetBinContent(i,tempNOISO1);
	hNOISO1->SetBinError(i, tempErrNOISO1);
      }
    double contentNOISO3 = hNOISO3->GetBinContent(i);
    double tempNOISO3 = (contentNOISO3)/((double)passAll3*dE);
    double errorNOISO3 = hNOISO3->GetBinError(i);
    double tempErrNOISO3 = (errorNOISO3)/((double)passAll3*dE);
    if(passAll3) 
      {
	hNOISO3->SetBinContent(i,tempNOISO3);
	hNOISO3->SetBinError(i, tempErrNOISO3);
      }

    //cluster spectra
    double contentCluster1 = hCluster1->GetBinContent(i);
    double tempCluster1 = (contentCluster1)/((double)passAll1*dE);
    double errorCluster1 = hCluster1->GetBinError(i);
    double tempErrCluster1 = (errorCluster1)/((double)passAll1*dE);
    if(passAll1) 
      {
	hCluster1->SetBinContent(i,tempCluster1);
	hCluster1->SetBinError(i, tempErrCluster1);
      }
    double contentCluster3 = hCluster3->GetBinContent(i);
    double tempCluster3 = (contentCluster3)/((double)passAll3*dE);
    double errorCluster3 = hCluster3->GetBinError(i);
    double tempErrCluster3 = (errorCluster3)/((double)passAll3*dE);
    if(passAll3) 
      {
	hCluster3->SetBinContent(i,tempCluster3);
	hCluster3->SetBinError(i, tempErrCluster3);
      }
  }//*/

  TLegend* leg = new TLegend(0.6, 0.7, 0.85, 0.85);
  leg->SetBorderSize(0);
  leg->AddEntry(hRaw1, "ESD");
  leg->AddEntry(hRaw3, "AOD");

  /*TCanvas* canR = new TCanvas("canR", "canR", 1000, 800);
  canR->SetLogy();
  hRaw1->SetTitle("Raw cluster spectra (no cuts); E_{T} (GeV); 1/Num_{eve} dN/dp_{T}");
  hRaw1->SetLineColor(kBlue);
  hRaw1->SetMarkerColor(kBlue);
  hRaw1->SetMarkerStyle(kFullSquare);
  hRaw3->SetTitle("Raw cluster spectra (no cuts); E_{T} (GeV); 1/Num_{eve} dN/dp_{T}");
  hRaw3->SetLineColor(kRed);
  hRaw3->SetMarkerColor(kRed);
  hRaw3->SetMarkerStyle(kFullSquare);
  hRaw1->Draw("e1");
  hRaw3->Draw("same e1");
  leg->Draw("same");

  TCanvas* canN = new TCanvas("canN", "canN", 1000, 800);
  canN->SetLogy();
  hNOISO1->SetTitle("Cluster spectra w. cuts (no iso cut); E_{T} (GeV); 1/Num_{eve} dN/dp_{T}");
  hNOISO1->SetLineColor(kBlue);
  hNOISO1->SetMarkerColor(kBlue);
  hNOISO1->SetMarkerStyle(kFullSquare);
  hNOISO3->SetTitle("Cluster spectra w. cuts (no iso cuts); E_{T} (GeV); 1/Num_{eve} dN/dp_{T}");
  hNOISO3->SetLineColor(kRed);
  hNOISO3->SetMarkerColor(kRed);
  hNOISO3->SetMarkerStyle(kFullSquare);
  hNOISO1->Draw("e1");
  hNOISO3->Draw("same e1");
  leg->Draw("same");

  TCanvas* canC = new TCanvas("canC", "canC", 1000, 800);
  canC->SetLogy();
  hCluster1->SetTitle("Cluster spectra (all cuts); E_{T} (GeV); 1/Num_{eve} dN/dp_{T}");
  hCluster1->SetLineColor(kBlue);
  hCluster1->SetMarkerColor(kBlue);
  hCluster1->SetMarkerStyle(kFullSquare);
  hCluster3->SetTitle("Cluster spectra (all cuts); E_{T} (GeV); 1/Num_{eve} dN/dp_{T}");
  hCluster3->SetLineColor(kRed);
  hCluster3->SetMarkerColor(kRed);
  hCluster3->SetMarkerStyle(kFullSquare);
  hCluster1->Draw("e1");
  hCluster3->Draw("same e1");
  leg->Draw("same");//*/


  hRaw1->Divide(hRaw3);
  hNOISO1->Divide(hNOISO3);
  hCluster1->Divide(hCluster3);
  hRaw1->SetLineColor(kCyan);
  hNOISO1->SetLineColor(kOrange);
  hCluster1->SetLineColor(kMagenta);
  hRaw1->SetMarkerColor(kCyan);
  hNOISO1->SetMarkerColor(kOrange);
  hCluster1->SetMarkerColor(kMagenta);

  TCanvas* cRatio = new TCanvas("cRatio", "cRatio", 1000, 800);
  hRaw1->SetTitle("; E_{T} (GeV); ESD/AOD");
  hRaw1->Draw("e1");
  hNOISO1->Draw("same e1");
  hCluster1->Draw("same e1");
  TLegend* leg2 = new TLegend(0.6, 0.7, 0.85, 0.85);
  leg2->SetBorderSize(0);
  leg2->AddEntry(hRaw1, "raw");
  leg2->AddEntry(hNOISO1, "no iso cut");
  leg2->AddEntry(hCluster1, "all cuts");
  leg2->Draw("Same");
  hRaw1->Fit("pol0", "", "", 16, 60);
  hNOISO1->Fit("pol0", "", "", 16, 60);
  hCluster1->Fit("pol0", "", "", 16, 60);
  
}//end compageAODESD
