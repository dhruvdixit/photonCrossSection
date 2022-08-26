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

#include<vector>
/*#include <algorithm>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bitset>
#include <bits/stdc++.h>
#include <cstring>//*/


//void SetHistStyle(Color_t lcolor = 1, Color_t mcolor = 1, Size_t lsize = 2, 

TH1F* getRatio(const char *name, TH1F* dataHist, TH1F* mcHist, TH1D* dataEventsHist){

  TH1F* h1 = (TH1F*)dataHist->Clone(name);
  Double_t numEvents_Data = dataEventsHist->GetBinContent(18);

  //cout << name << "\t" << numEvents_Data << endl;
  //Double_t numEvents_MC = mcEventsHist->GetBinContent(8);//bin 8 = with weights
  for(int i = 1; i < dataHist->GetNbinsX()+1; i++){
    Double_t dEta = dataHist->GetBinWidth(i);

    Double_t content_Data = dataHist->GetBinContent(i);
    Double_t temp_Data = content_Data/(dEta*numEvents_Data);
    Double_t error_Data  =  dataHist->GetBinError(i);
    Double_t tempE_Data = error_Data/(dEta*numEvents_Data);
    dataHist->SetBinContent(i, temp_Data);
    dataHist->SetBinError(i, tempE_Data);

    Double_t temp_MC = mcHist->GetBinContent(i);
    Double_t tempE_MC  =  mcHist->GetBinError(i);

    Double_t content_Ratio = temp_Data/temp_MC;
    Double_t error_Ratio = (temp_Data/temp_MC)*TMath::Sqrt(TMath::Power(tempE_Data/temp_Data, 2)+TMath::Power(tempE_MC/temp_MC, 2));
    if(temp_MC != 0){
      h1->SetBinContent(i, content_Ratio);
      h1->SetBinError(i, error_Ratio);
    }

    
  }

  return h1;
    
  
}


/*////////////////////////////////////////////////////////////
 * Both data and MC histograms should be event normalized prior
 to sending them as inputs for this function
///////////////////////////////////////////////////////////*/
TH1F* getRatio(const char *name, TH1F* dataHist, TH1F* mcHist){

  TH1F* h1 = (TH1F*)dataHist->Clone(name);
  h1->GetYaxis()->SetTitle("Data/MC_{rec}");

  //cout << name << "\t" << numEvents_Data << endl;
  //Double_t numEvents_MC = mcEventsHist->GetBinContent(8);//bin 8 = with weights
  for(int i = 1; i < dataHist->GetNbinsX()+1; i++){
    Double_t dEta = dataHist->GetBinWidth(i);

    Double_t content_Data = dataHist->GetBinContent(i);
    Double_t error_Data  =  dataHist->GetBinError(i);

    Double_t content_MC = mcHist->GetBinContent(i);
    Double_t error_MC  =  mcHist->GetBinError(i);

    Double_t content_Ratio = content_Data/content_MC;
    Double_t error_Ratio = (content_Data/content_MC)*TMath::Sqrt(TMath::Power(error_Data/content_Data, 2)+TMath::Power(error_MC/content_MC, 2));
    if(content_MC != 0){
      h1->SetBinContent(i, content_Ratio);
      h1->SetBinError(i, error_Ratio);
    }

    
  }

  return h1;
    
  
}



TH1F* calcResiduals(const char *name, TH1F* h1, TH1F* h2){

    TH1F* hRes = (TH1F*)h2->Clone(name);
    
    for(int i = 1; i < hRes->GetNbinsX()+1; i++){
      Double_t a = h1->GetBinContent(i);
      Double_t b = h2->GetBinContent(i);

      Double_t aError = h1->GetBinError(i);
      Double_t bError = h2->GetBinError(i);
      Double_t subError = TMath::Sqrt(aError*aError + bError*bError);

      if(a != 0){
	Double_t temp = (a-b)/a;
	hRes->SetBinContent(i, temp);
	//Double_t relSubError = subError/(a-b);
	Double_t tempE = TMath::Abs(temp*TMath::Sqrt(TMath::Power(subError/(a-b), 2) + TMath::Power(aError/a, 2)));
	hRes->SetBinError(i, tempE);
	//cout << temp << "\t" << tempE << endl;
      }
    }

    hRes->Fit("pol0", "Q0", "", -0.7, 0.7);
    Double_t par0 = (hRes->GetFunction("pol0"))->GetParameter(0);
    //cout << name << "\t" << par0 << endl;
    return hRes;
}

void printHistEntries(TH1F* h1){

  cout << "Bin Num\tLow Edge\tHigh Edge\tContent\t\tError" << endl;
    
  for(int i = 1; i < h1->GetNbinsX()+1; i++){
    cout << i << "\t\t" << h1->GetBinLowEdge(i) << "\t\t" << h1->GetBinLowEdge(i+1) << "\t" << h1->GetBinContent(i) << "\t" << h1->GetBinError(i) << endl;
  }
}



TH1F* calcCorrectionFactor(const char *name, TH1F* hist, TString systemName){

  TH1F* cfHist;
  //printHistEntries(hist);
  vector<int> binNums;

  if(systemName == "pPb"){
    cout << "System is p-Pb" << endl;
    binNums.push_back(12);
    binNums.push_back(13);
    binNums.push_back(14);
    binNums.push_back(15);
  }
  else if(systemName == "pp"){
    cout << "System is pp" << endl;
    binNums.push_back(4);
    binNums.push_back(15);
  }
  else{
    cout << "Error in calcCorrectionFactor, \"systemName\" is incorrect. " << __LINE__ << endl; 
    return hist;
  }
  
  vector<Double_t> vals;
  vector<Double_t> errs;
  Double_t etaAve = 0;
  Double_t etaAveErr = 0;
  
  for (auto i = binNums.cbegin(); i != binNums.cend(); ++i){
    //cout << *i << " ";
    etaAve += hist->GetBinContent(*i);
    etaAveErr += TMath::Power(hist->GetBinError(*i), 2);
  }

  if(binNums.size() != 0){
    etaAve = etaAve/(Double_t)binNums.size();
    etaAveErr = TMath::Sqrt(etaAveErr)/(Double_t)binNums.size();
  }
  
  cout << etaAve << " +/- " << etaAveErr << endl;

  cfHist = (TH1F*)hist->Clone(name);
  for(int h = 1; h < cfHist->GetNbinsX()+1; h++){
    Double_t content = cfHist->GetBinContent(h);
    Double_t corrFactor = 1;
    if(content != 0)
      corrFactor = etaAve/content;
    cfHist->SetBinContent(h, corrFactor);

    //cout << hist->GetBinContent(h) << "\t" << cfHist->GetBinContent(h) << "\t" << (hist->GetBinContent(h))*(cfHist->GetBinContent(h)) << endl;
  }
	
  return cfHist;

}

void normalize(TH1F* hist, Double_t numEvents){

  for(int i = 1; i < hist->GetNbinsX()+1; i++){
    Double_t dw = hist->GetBinWidth(i);

    Double_t content = hist->GetBinContent(i);
    Double_t temp = content/(dw*numEvents);
    Double_t error  =  hist->GetBinError(i);
    Double_t tempE = error/(dw*numEvents);
    hist->SetBinContent(i, temp);
    hist->SetBinError(i, tempE);
  }
}


void calcEtaCorrection(){

  //gStyle->SetCanvasColor(-1);
  //gStyle->SetPadColor(-1);
  /*gStyle->SetFrameFillColor(-1);
  gStyle->SetHistFillColor(-1);
  gStyle->SetTitleFillColor(-1);
  gStyle->SetFillColor(-1);
  gStyle->SetFillStyle(4000);
  gStyle->SetStatStyle(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderSize(0);
  //gStyle->SetLegendBorderSize(0);
  //gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);//*/
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/";


  /*TFile* f_pPbData = new TFile(Form("%scsOutput/pPbOutput/Feb20AliPhysics/postQMNtuples/eta18bins/fout_6_14bins_firstEvent0_13def_kEMCEGA_kINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_eta18bins_noNorm.root", path.Data()), "READ");
  TFile* f_ppData = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/fout_4_14bins_firstEvent0_17q_runAll_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_eta18bins_noNorm.root", path.Data()), "READ");
  TFile* f_pPbMC = new TFile(Form("%sMC/17g6a1/Nonlin/QMNtuples/eta18bins/fout_14bins_firstEvent0_17g6a1_pthatAll_1run_wNL_GeMomentumFixedStdCuts_eta18bins_noNorm.root", path.Data()), "READ");
  TFile* f_ppMC = new TFile(Form("%sMC/18b10a/Nonlin/QMNtuples/eta18bins/fout_14bins_firstEvent0_18b10a_pthatAll_2runs_wNL_GeMomentumFixedStdCuts_eta18bins_noNorm.root", path.Data()), "READ");//*/

  //photon pT > 13 GeV/c
  /*TFile* f_pPbData = new TFile(Form("%scsOutput/pPbOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptCut/fout_6_14bins_firstEvent0_13def_kEMCEGA_kINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptCut_noNorm.root", path.Data()), "READ");
  TFile* f_ppData = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptCut/fout_4_14bins_firstEvent0_17q_runAll_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptCut_noNorm.root", path.Data()), "READ");
  TFile* f_pPbMC = new TFile(Form("%sMC/17g6a1/Nonlin/QMNtuples/eta18bins/12GeVptCut/fout_14bins_firstEvent0_17g6a1_pthatAll_1run_wNL_GeMomentumFixedStdCuts_12GeVptCut_pileUpCut_noNorm.root", path.Data()), "READ");
  TFile* f_ppMC = new TFile(Form("%sMC/18b10a/Nonlin/QMNtuples/eta18bins/12GeVptCut/fout_14bins_firstEvent0_18b10a_pthatAll_2runs_wNL_GeMomentumFixedStdCuts_12GeVptCut_pileUpCut_noNorm.root", path.Data()), "READ");//*/

  //Events with at one photon with pT > 12 GeV/c
  /*TFile* f_pPbData = new TFile(Form("%scsOutput/pPbOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/fout_6_14bins_firstEvent0_13def_kEMCEGA_kINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");//used for the correction
  //TFile* f_pPbData = new TFile(Form("%scsOutput/pPbOutput/Feb20AliPhysics/postQMNtuples/wEtaCorr/fout_6_14bins_firstEvent0_13def_kEMCEGA_kINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_wEtaCorr_noNorm.root", path.Data()), "READ");//with eta corr applied
  //TFile* f_ppData = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/fout_4_14bins_firstEvent0_17q_runAll_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TFile* f_ppData = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/fout_4_14bins_firstEvent0_17q_allRunsNo365And440_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");//used for the correction
  TFile* f_pPbMC = new TFile(Form("%sMC/17g6a1/Nonlin/QMNtuples/eta18bins/12GeVptEventCut/fout_14bins_firstEvent0_17g6a1_pthatAll_1run_wNL_GeMomentumFixedStdCuts_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TFile* f_ppMC = new TFile(Form("%sMC/18b10a/Nonlin/QMNtuples/eta18bins/12GeVptEventCut/fout_14bins_firstEvent0_18b10a_pthatAll_2runs_wNL_GeMomentumFixedStdCuts_12GeVptEventCut_noNorm.root", path.Data()), "READ");//*/

  //Added SM level phi binning
  TFile* f_pPbData = new TFile(Form("%scsOutput/pPbOutput/Feb20AliPhysics/postQMNtuples/wEtaCorr/SMphiBin/fout_6_14bins_firstEvent0_13def_kEMCEGA_kINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_wEtaCorr_SMphiBin_noNorm.root", path.Data()), "READ");
  TFile* f_ppData = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/wEtaCorr/SMphiBin/fout_4_14bins_firstEvent0_17q_runAll_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_wEtaCorr_SMphiBin_noNorm.root", path.Data()), "READ");
  TFile* f_pPbMC = new TFile(Form("%sMC/17g6a1/Nonlin/QMNtuples/eta18bins/SMphiBin/fout_14bins_firstEvent0_17g6a1_pthatAll_1run_wNL_GeMomentumFixedStdCuts_SMphiBin_noNorm.root", path.Data()), "READ");
  TFile* f_ppMC = new TFile(Form("%sMC/18b10a/Nonlin/QMNtuples/eta18bins/SMphiBin/fout_14bins_firstEvent0_18b10a_pthatAll_2runs_wNL_GeMomentumFixedStdCuts_SMphiBin_noNorm.root", path.Data()), "READ");

  
  TH1F* h_pPbData = (TH1F*)f_pPbData->Get("hEtawEtaCorr");
  TH1F* h_ppData = (TH1F*)f_ppData->Get("hEtawEtaCorr");
  TH1F* h_pPbMC = (TH1F*)f_pPbMC->Get("hEtaW");
  TH1F* h_ppMC = (TH1F*)f_ppMC->Get("hEtaW");
  TH1D* hNorm_pPbData = (TH1D*)f_pPbData->Get("hNormalizer");
  TH1D* hNorm_ppData = (TH1D*)f_ppData->Get("hNormalizer");
  TH1D* hNorm_pPbMC = (TH1D*)f_pPbMC->Get("hNormalizer");
  TH1D* hNorm_ppMC = (TH1D*)f_ppMC->Get("hNormalizer");
  TH1F* r_pPb = (TH1F*)h_pPbData->Clone("r_pPb");
  TH1F* r_pp = (TH1F*)h_ppData->Clone("r_pp");
  
  //Normal event count
  /*Double_t numEvents_pPbData = hNorm_pPbData->GetBinContent(5);
  Double_t numEvents_ppData = hNorm_ppData->GetBinContent(5);
  Double_t numEvents_pPbMC = hNorm_pPbMC->GetBinContent(6);//bin 4 = regular, bin 6 with weights
  Double_t numEvents_ppMC = hNorm_ppMC->GetBinContent(6);//*/

  //Event count include pT > 12 GeV/c cut
  Double_t numEvents_pPbData = hNorm_pPbData->GetBinContent(18);
  Double_t numEvents_ppData = hNorm_ppData->GetBinContent(18);
  Double_t numEvents_pPbMC = hNorm_pPbMC->GetBinContent(8);//bin 8 = with weights
  Double_t numEvents_ppMC = hNorm_ppMC->GetBinContent(8);//*/

  cout << "Event counts:" << endl;
  cout << "p-Pb data:" << "\t" << numEvents_pPbData << endl;
  cout << "pp data:" << "\t" << numEvents_ppData << endl;
  cout << "p-Pb MC:" << "\t" << numEvents_pPbMC << endl;
  cout << "pp MC:" << "\t" << numEvents_ppMC << endl;

  for(int i = 1; i < h_pPbData->GetNbinsX()+1; i++){
    Double_t dEta = h_pPbData->GetBinWidth(i);

    Double_t content_pPbData = h_pPbData->GetBinContent(i);
    Double_t temp_pPbData = content_pPbData/(dEta*numEvents_pPbData);
    Double_t error_pPbData  =  h_pPbData->GetBinError(i);
    Double_t tempE_pPbData = error_pPbData/(dEta*numEvents_pPbData);
    h_pPbData->SetBinContent(i, temp_pPbData);
    h_pPbData->SetBinError(i, tempE_pPbData);
    
    Double_t content_ppData = h_ppData->GetBinContent(i);
    Double_t temp_ppData = content_ppData/(dEta*numEvents_ppData);
    Double_t error_ppData  =  h_ppData->GetBinError(i);
    Double_t tempE_ppData = error_ppData/(dEta*numEvents_pPbData);
    h_ppData->SetBinContent(i, temp_ppData);
    h_ppData->SetBinError(i, tempE_ppData);
    
    Double_t content_pPbMC = h_pPbMC->GetBinContent(i);
    Double_t temp_pPbMC = content_pPbMC/(dEta*numEvents_pPbMC);
    Double_t error_pPbMC  =  h_pPbMC->GetBinError(i);
    Double_t tempE_pPbMC = error_pPbMC/(dEta*numEvents_pPbMC);
    h_pPbMC->SetBinContent(i, temp_pPbMC);
    h_pPbMC->SetBinError(i, tempE_pPbMC);

    Double_t content_ppMC = h_ppMC->GetBinContent(i);
    Double_t temp_ppMC = content_ppMC/(dEta*numEvents_ppMC);
    Double_t error_ppMC  =  h_ppMC->GetBinError(i);
    Double_t tempE_ppMC = error_ppMC/(dEta*numEvents_ppMC);
    h_ppMC->SetBinContent(i, temp_ppMC);
    h_ppMC->SetBinError(i, tempE_ppMC);

    Double_t content_pPbRatio = temp_pPbData/temp_pPbMC;
    Double_t error_pPbRatio = (temp_pPbData/temp_pPbMC)*TMath::Sqrt(TMath::Power(tempE_pPbData/temp_pPbData, 2)+TMath::Power(tempE_pPbMC/temp_pPbMC, 2));
    if(temp_pPbMC != 0){
      r_pPb->SetBinContent(i, content_pPbRatio);
      r_pPb->SetBinError(i, error_pPbRatio);
      //cout <<  r_pPb->GetBinContent(i) << endl;
    }

    Double_t content_ppRatio = temp_ppData/temp_ppMC;
    Double_t error_ppRatio = (temp_ppData/temp_ppMC)*TMath::Sqrt(TMath::Power(tempE_ppData/temp_ppData, 2)+TMath::Power(tempE_ppMC/temp_ppMC, 2));
    if(temp_ppMC != 0){
      r_pp->SetBinContent(i, content_ppRatio);
      r_pp->SetBinError(i, error_ppRatio);
      //cout <<  r_pp->GetBinContent(i) << endl;
    }
    
  }//*/
  
  /*h_pPbData->Scale(1.0/h_pPbData->Integral());
  h_ppData->Scale(1.0/h_ppData->Integral());
  h_pPbMC->Scale(1.0/h_pPbMC->Integral());
  h_ppMC->Scale(1.0/h_ppMC->Integral());//*/
  
  h_pPbData->GetYaxis()->SetRangeUser(0, 0.7);
  h_pPbData->SetTitle("p-Pb;#eta;1/N_{eve} dN/d#eta");
  h_pPbData->SetLineColor(kBlue);
  h_pPbData->SetLineWidth(2);
  h_pPbMC->SetLineColor(kRed);
  h_pPbMC->SetLineWidth(2);

  TLegend* l_pPb = new TLegend(0.4, 0.3, 0.6, 0.45);
  l_pPb->SetBorderSize(0);
  l_pPb->AddEntry(h_pPbData, "p-Pb data");
  l_pPb->AddEntry(h_pPbMC, "p-Pb MC");

  //TH1F* r_pPb = (TH1F*)h_pPbData->Clone("r_pPb");
  //r_pPb->Divide(h_pPbMC);
  r_pPb->SetTitle("p-Pb;#eta;ratio (data/MC)");
  r_pPb->SetLineColor(kBlack);
  r_pPb->SetLineWidth(2);
		  
  /*TCanvas* c_pPb = new TCanvas("c_pPb", "c_pPb", 1200, 600);
  c_pPb->Divide(2, 1);
  c_pPb->cd(1);
  h_pPbData->Draw("e1");
  h_pPbMC->Draw("e1 same");
  l_pPb->Draw("same");
  c_pPb->cd(2);
  r_pPb->Draw("e1");//*/
  
  h_ppData->GetYaxis()->SetRangeUser(0, 0.7);
  h_ppData->SetTitle("pp;#eta;1/N_{eve} dN/d#eta");
  h_ppData->SetLineColor(kBlue);
  h_ppData->SetLineWidth(2);
  h_ppMC->SetLineColor(kRed);
  h_ppMC->SetLineWidth(2);

  TLegend* l_pp = new TLegend(0.4, 0.3, 0.6, 0.45);
  l_pp->SetBorderSize(0);
  l_pp->AddEntry(h_ppData, "p-Pb data");
  l_pp->AddEntry(h_ppMC, "p-Pb MC");

  //TH1F* r_pp = (TH1F*)h_ppData->Clone("r_pp");
  //r_pp->Divide(h_ppMC);
  r_pp->SetTitle("pp;#eta;ratio (data/MC)");
  r_pp->SetLineColor(kBlack);
  r_pp->SetLineWidth(2);
  
  /*TCanvas* c_pp = new TCanvas("c_pp", "c_pp", 1200, 600);
  c_pp->Divide(2, 1);
  c_pp->cd(1);
  h_ppData->Draw("e1");
  h_ppMC->Draw("e1 same");
  l_pp->Draw("same");
  c_pp->cd(2);
  r_pp->Draw("e1");//*/
  

  
  TFile* f_ppRun282365 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282365_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282365 = (TH1F*)f_ppRun282365->Get("hEta");
  TH1D* n_ppRun282365 = (TH1D*)f_ppRun282365->Get("hNormalizer");
  TH1F* r_ppRun282365 = getRatio("r_ppRun282365", h_ppRun282365, h_ppMC, n_ppRun282365);

  TFile* f_ppRun282366 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282366_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282366 = (TH1F*)f_ppRun282366->Get("hEta");
  TH1D* n_ppRun282366 = (TH1D*)f_ppRun282366->Get("hNormalizer");
  TH1F* r_ppRun282366 = getRatio("r_ppRun282366", h_ppRun282366, h_ppMC, n_ppRun282366);

  TFile* f_ppRun282367 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282367_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282367 = (TH1F*)f_ppRun282367->Get("hEta");
  TH1D* n_ppRun282367 = (TH1D*)f_ppRun282367->Get("hNormalizer");
  TH1F* r_ppRun282367 = getRatio("r_ppRun282367", h_ppRun282367, h_ppMC, n_ppRun282367);

  TFile* f_ppRun282391 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282391_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282391 = (TH1F*)f_ppRun282391->Get("hEta");
  TH1D* n_ppRun282391 = (TH1D*)f_ppRun282391->Get("hNormalizer");
  TH1F* r_ppRun282391 = getRatio("r_ppRun282391", h_ppRun282391, h_ppMC, n_ppRun282391);

  TFile* f_ppRun282392 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282392_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282392 = (TH1F*)f_ppRun282392->Get("hEta");
  TH1D* n_ppRun282392 = (TH1D*)f_ppRun282392->Get("hNormalizer");
  TH1F* r_ppRun282392 = getRatio("r_ppRun282392", h_ppRun282392, h_ppMC, n_ppRun282392);

  TFile* f_ppRun282398 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282398_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282398 = (TH1F*)f_ppRun282398->Get("hEta");
  TH1D* n_ppRun282398 = (TH1D*)f_ppRun282398->Get("hNormalizer");
  TH1F* r_ppRun282398 = getRatio("r_ppRun282398", h_ppRun282398, h_ppMC, n_ppRun282398);

  TFile* f_ppRun282399 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282399_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282399 = (TH1F*)f_ppRun282399->Get("hEta");
  TH1D* n_ppRun282399 = (TH1D*)f_ppRun282399->Get("hNormalizer");
  TH1F* r_ppRun282399 = getRatio("r_ppRun282399", h_ppRun282399, h_ppMC, n_ppRun282399);

  TFile* f_ppRun282402 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282402_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282402 = (TH1F*)f_ppRun282402->Get("hEta");
  TH1D* n_ppRun282402 = (TH1D*)f_ppRun282402->Get("hNormalizer");
  TH1F* r_ppRun282402 = getRatio("r_ppRun282402", h_ppRun282402, h_ppMC, n_ppRun282402);

  TFile* f_ppRun282411 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282411_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282411 = (TH1F*)f_ppRun282411->Get("hEta");
  TH1D* n_ppRun282411 = (TH1D*)f_ppRun282411->Get("hNormalizer");
  TH1F* r_ppRun282411 = getRatio("r_ppRun282411", h_ppRun282411, h_ppMC, n_ppRun282411);

  TFile* f_ppRun282415 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282415_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282415 = (TH1F*)f_ppRun282415->Get("hEta");
  TH1D* n_ppRun282415 = (TH1D*)f_ppRun282415->Get("hNormalizer");
  TH1F* r_ppRun282415 = getRatio("r_ppRun282415", h_ppRun282415, h_ppMC, n_ppRun282415);

  TFile* f_ppRun282437 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282437_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282437 = (TH1F*)f_ppRun282437->Get("hEta");
  TH1D* n_ppRun282437 = (TH1D*)f_ppRun282437->Get("hNormalizer");
  TH1F* r_ppRun282437 = getRatio("r_ppRun282437", h_ppRun282437, h_ppMC, n_ppRun282437);

  TFile* f_ppRun282440 = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/RunByRun/fout_4_14bins_firstEvent0_17q_run282440_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppRun282440 = (TH1F*)f_ppRun282440->Get("hEta");
  TH1D* n_ppRun282440 = (TH1D*)f_ppRun282440->Get("hNormalizer");
  TH1F* r_ppRun282440 = getRatio("r_ppRun282440", h_ppRun282440, h_ppMC, n_ppRun282440);

  TFile* f_ppFull = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/fout_4_14bins_firstEvent0_17q_runAll_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_ppFull = (TH1F*)f_ppFull->Get("hEta");
  TH1D* n_ppFull = (TH1D*)f_ppFull->Get("hNormalizer");
  TH1F* r_ppFull = getRatio("r_ppFull", h_ppFull, h_ppMC, n_ppFull);


  r_pp->GetYaxis()->SetRangeUser(0, 0.22);
  r_pp->GetXaxis()->SetRangeUser(-0.75, 0.75);
  r_pp->SetLineColor(kBlack);
  r_pp->SetLineWidth(4);
  r_pp->SetLineStyle(kSolid);
  r_pp->SetMarkerStyle(kFullCircle);
  r_pp->SetMarkerSize(2);

  r_ppFull->SetLineColor(kBlack);
  r_ppFull->SetLineWidth(2);
  r_ppFull->SetLineStyle(kDashed);
  r_ppFull->SetMarkerStyle(kFullSquare);
  r_ppFull->SetMarkerColor(kBlack);
  r_ppFull->SetMarkerSize(2);

  r_ppRun282365->SetLineColor(kRed);
  r_ppRun282365->SetLineWidth(2);
  r_ppRun282365->SetLineStyle(kSolid);
  r_ppRun282365->SetMarkerStyle(kFullCircle);
  r_ppRun282365->SetMarkerColor(kRed);
  r_ppRun282365->SetMarkerSize(2);

  r_ppRun282366->SetLineColor(kRed);
  r_ppRun282366->SetLineWidth(2);
  r_ppRun282366->SetLineStyle(kDashed);
  r_ppRun282366->SetMarkerStyle(kFullSquare);
  r_ppRun282366->SetMarkerColor(kRed);
  r_ppRun282366->SetMarkerSize(2);

  r_ppRun282367->SetLineColor(kRed);
  r_ppRun282367->SetLineWidth(3);
  r_ppRun282367->SetLineStyle(kDotted);
  r_ppRun282367->SetMarkerStyle(kFullDiamond);
  r_ppRun282367->SetMarkerColor(kRed);
  r_ppRun282367->SetMarkerSize(3);

  r_ppRun282391->SetLineColor(kCyan);
  r_ppRun282391->SetLineWidth(2);
  r_ppRun282391->SetLineStyle(kSolid);
  r_ppRun282391->SetMarkerStyle(kFullCircle);
  r_ppRun282391->SetMarkerColor(kCyan);
  r_ppRun282391->SetMarkerSize(2);

  r_ppRun282392->SetLineColor(kCyan);
  r_ppRun282392->SetLineWidth(2);
  r_ppRun282392->SetLineStyle(kDashed);
  r_ppRun282392->SetMarkerStyle(kFullSquare);
  r_ppRun282392->SetMarkerColor(kCyan);
  r_ppRun282392->SetMarkerSize(2);

  r_ppRun282398->SetLineColor(kCyan);
  r_ppRun282398->SetLineWidth(2);
  r_ppRun282398->SetLineStyle(kDotted);
  r_ppRun282398->SetMarkerStyle(kFullDiamond);
  r_ppRun282398->SetMarkerColor(kCyan);
  r_ppRun282398->SetMarkerSize(3);

  r_ppRun282399->SetLineColor(kGreen);
  r_ppRun282399->SetLineWidth(2);
  r_ppRun282399->SetLineStyle(kSolid);
  r_ppRun282399->SetMarkerStyle(kFullCircle);
  r_ppRun282399->SetMarkerColor(kGreen);
  r_ppRun282399->SetMarkerSize(2);

  r_ppRun282402->SetLineColor(kGreen);
  r_ppRun282402->SetLineWidth(2);
  r_ppRun282402->SetLineStyle(kDashed);
  r_ppRun282402->SetMarkerStyle(kFullSquare);
  r_ppRun282402->SetMarkerColor(kGreen);
  r_ppRun282402->SetMarkerSize(2);

  r_ppRun282411->SetLineColor(kGreen);
  r_ppRun282411->SetLineWidth(2);
  r_ppRun282411->SetLineStyle(kDotted);
  r_ppRun282411->SetMarkerStyle(kFullDiamond);
  r_ppRun282411->SetMarkerColor(kGreen);
  r_ppRun282411->SetMarkerSize(3);

  r_ppRun282415->SetLineColor(kMagenta);
  r_ppRun282415->SetLineWidth(2);
  r_ppRun282415->SetLineStyle(kSolid);
  r_ppRun282415->SetMarkerStyle(kFullCircle);
  r_ppRun282415->SetMarkerColor(kMagenta);
  r_ppRun282415->SetMarkerSize(2);

  r_ppRun282437->SetLineColor(kMagenta);
  r_ppRun282437->SetLineWidth(2);
  r_ppRun282437->SetLineStyle(kDashed);
  r_ppRun282437->SetMarkerStyle(kFullSquare);
  r_ppRun282437->SetMarkerColor(kMagenta);
  r_ppRun282437->SetMarkerSize(2);

  r_ppRun282440->SetLineColor(kMagenta);
  r_ppRun282440->SetLineWidth(2);
  r_ppRun282440->SetLineStyle(kDotted);
  r_ppRun282440->SetMarkerStyle(kFullDiamond);
  r_ppRun282440->SetMarkerColor(kMagenta);
  r_ppRun282440->SetMarkerSize(3);
  
  TCanvas* c_rbr = new TCanvas("c_rbr", "c_rbr", 600, 600);
  r_pp->Draw("L hist p");
  /*r_ppFull->Draw("same L hist p");
  r_ppRun282365->Draw("same L hist p");
  r_ppRun282366->Draw("same L hist p");
  r_ppRun282367->Draw("same L hist p");
  r_ppRun282391->Draw("same L hist p");
  r_ppRun282392->Draw("same L hist p");  
  r_ppRun282398->Draw("same L hist p");
  r_ppRun282399->Draw("same L hist p");
  r_ppRun282402->Draw("same L hist p");
  r_ppRun282411->Draw("same L hist p");
  r_ppRun282415->Draw("same L hist p");
  r_ppRun282437->Draw("same L hist p");
  r_ppRun282440->Draw("same L hist p");//*/
  r_pp->Draw("same e1");
  /*r_ppFull->Draw("same e1");
  r_ppRun282365->Draw("same e1");
  r_ppRun282366->Draw("same e1");
  r_ppRun282367->Draw("same e1");
  r_ppRun282391->Draw("same e1");
  r_ppRun282392->Draw("same e1");
  r_ppRun282398->Draw("same e1");
  r_ppRun282399->Draw("same e1");
  r_ppRun282402->Draw("same e1");
  r_ppRun282411->Draw("same e1");
  r_ppRun282415->Draw("same e1");  
  r_ppRun282437->Draw("same e1");
  r_ppRun282440->Draw("same e1");//*/
  
  /*TLegend* l_rbr = new TLegend(0.15, 0.7, 0.6, 0.89);
  l_rbr->SetBorderSize(0);
  l_rbr->SetNColumns(3);
  l_rbr->AddEntry(r_ppRun282365, "Run 282365");
  l_rbr->AddEntry(r_ppRun282366, "Run 282366");
  l_rbr->AddEntry(r_ppRun282367, "Run 282367");
  l_rbr->AddEntry(r_ppRun282391, "Run 282391");
  l_rbr->AddEntry(r_ppRun282392, "Run 282392");
  l_rbr->AddEntry(r_ppRun282398, "Run 282398");
  l_rbr->AddEntry(r_ppRun282399, "Run 282399");
  l_rbr->AddEntry(r_ppRun282402, "Run 282402");
  l_rbr->AddEntry(r_ppRun282411, "Run 282411");
  l_rbr->AddEntry(r_ppRun282415, "Run 282415");
  l_rbr->AddEntry(r_ppRun282437, "Run 282437");
  l_rbr->AddEntry(r_ppRun282440, "Run 282440");
  l_rbr->AddEntry(r_pp, "Good pp");
  l_rbr->AddEntry(r_ppFull, "All pp");
  l_rbr->Draw("same");//*/


  TH1F* res_ppRun282365 = calcResiduals("res_ppRun282365", r_pp, r_ppRun282365);
  TH1F* res_ppRun282366 = calcResiduals("res_ppRun282366", r_pp, r_ppRun282366);
  TH1F* res_ppRun282367 = calcResiduals("res_ppRun282367", r_pp, r_ppRun282367);
  TH1F* res_ppRun282391 = calcResiduals("res_ppRun282391", r_pp, r_ppRun282391);
  TH1F* res_ppRun282392 = calcResiduals("res_ppRun282392", r_pp, r_ppRun282392);
  TH1F* res_ppRun282398 = calcResiduals("res_ppRun282398", r_pp, r_ppRun282398);
  TH1F* res_ppRun282399 = calcResiduals("res_ppRun282399", r_pp, r_ppRun282399);
  TH1F* res_ppRun282402 = calcResiduals("res_ppRun282402", r_pp, r_ppRun282402);
  TH1F* res_ppRun282411 = calcResiduals("res_ppRun282411", r_pp, r_ppRun282411);
  TH1F* res_ppRun282415 = calcResiduals("res_ppRun282415", r_pp, r_ppRun282415);
  TH1F* res_ppRun282437 = calcResiduals("res_ppRun282437", r_pp, r_ppRun282437);
  TH1F* res_ppRun282440 = calcResiduals("res_ppRun282440", r_pp, r_ppRun282440);
  TH1F* res_ppFull = calcResiduals("res_ppFull", r_pp, r_ppFull);

  res_ppFull->SetTitle(";#eta;#frac{good pp - 1 run}{good pp}");
  res_ppFull->GetYaxis()->SetRangeUser(-1, 1);
  /*TCanvas* c_ppRes = new TCanvas("c_ppRes", "c_ppRes", 600, 600);
  res_ppFull->Draw("e1");
  res_ppRun282365->Draw("same e1");
  res_ppRun282366->Draw("same e1");
  res_ppRun282367->Draw("same e1");
  res_ppRun282391->Draw("same e1");
  res_ppRun282392->Draw("same e1");
  res_ppRun282398->Draw("same e1");
  res_ppRun282399->Draw("same e1");
  res_ppRun282402->Draw("same e1");
  res_ppRun282411->Draw("same e1");
  res_ppRun282415->Draw("same e1");
  res_ppRun282437->Draw("same e1");
  res_ppRun282440->Draw("same e1");//*/
  /*res_ppFull->Draw("same L hist p");
  res_ppRun282365->Draw("same L hist p");
  res_ppRun282366->Draw("same L hist p");
  res_ppRun282367->Draw("same L hist p");
  res_ppRun282391->Draw("same L hist p");
  res_ppRun282392->Draw("same L hist p");
  res_ppRun282398->Draw("same L hist p");
  res_ppRun282399->Draw("same L hist p");
  res_ppRun282402->Draw("same L hist p");
  res_ppRun282411->Draw("same L hist p");
  res_ppRun282415->Draw("same L hist p");
  res_ppRun282437->Draw("same L hist p");
  res_ppRun282440->Draw("same L hist p");
  l_rbr->Draw("same");//*/

  
  //TCanvas* c_ppResIndiv = new TCanvas("c_ppResIndiv", "c_ppResIndiv", 3000, 1200);
  

  

  TFile* f_pPb13d = new TFile(Form("%scsOutput/pPbOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/PeriodByPeriod/fout_6_14bins_firstEvent0_13d_kEMCEGA_kINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_pPb13d = (TH1F*)f_pPb13d->Get("hEta");
  TH1D* n_pPb13d = (TH1D*)f_pPb13d->Get("hNormalizer");
  TH1F* r_pPb13d = getRatio("r_pPb13d", h_pPb13d, h_pPbMC, n_pPb13d);

  TFile* f_pPb13e = new TFile(Form("%scsOutput/pPbOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/PeriodByPeriod/fout_6_14bins_firstEvent0_13e_kEMCEGA_kINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_pPb13e = (TH1F*)f_pPb13e->Get("hEta");
  TH1D* n_pPb13e = (TH1D*)f_pPb13e->Get("hNormalizer");
  TH1F* r_pPb13e = getRatio("r_pPb13e", h_pPb13e, h_pPbMC, n_pPb13e);

  TFile* f_pPb13f = new TFile(Form("%scsOutput/pPbOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/PeriodByPeriod/fout_6_14bins_firstEvent0_13f_kEMCEGA_kINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_pPb13f = (TH1F*)f_pPb13f->Get("hEta");
  TH1D* n_pPb13f = (TH1D*)f_pPb13f->Get("hNormalizer");
  TH1F* r_pPb13f = getRatio("r_pPb13f", h_pPb13f, h_pPbMC, n_pPb13f);

  TFile* f_pPb13fnew = new TFile(Form("%scsOutput/pPbOutput/Feb20AliPhysics/postQMNtuples/eta18bins/12GeVptEventCut/PeriodByPeriod/fout_6_14bins_firstEvent0_13fnew_kEMCEGA_kINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_12GeVptEventCut_noNorm.root", path.Data()), "READ");
  TH1F* h_pPb13fnew = (TH1F*)f_pPb13fnew->Get("hEta");
  TH1D* n_pPb13fnew = (TH1D*)f_pPb13fnew->Get("hNormalizer");
  TH1F* r_pPb13fnew = getRatio("r_pPb13fnew", h_pPb13fnew, h_pPbMC, n_pPb13fnew);

  r_pPb->GetYaxis()->SetRangeUser(0, 0.15);
  r_pPb->GetXaxis()->SetRangeUser(-0.75, 0.75);
  r_pPb->SetLineColor(kBlack);
  r_pPb->SetLineWidth(4);
  r_pPb->SetMarkerStyle(kFullCircle);
  r_pPb->SetMarkerSize(2);

  r_pPb13d->SetLineColor(kCyan);
  r_pPb13d->SetLineWidth(2);
  r_pPb13d->SetLineStyle(kSolid);
  r_pPb13d->SetMarkerStyle(kFullCircle);
  r_pPb13d->SetMarkerColor(kCyan);
  r_pPb13d->SetMarkerSize(2);

  r_pPb13e->SetLineColor(kGreen);
  r_pPb13e->SetLineWidth(2);
  r_pPb13e->SetLineStyle(kSolid);
  r_pPb13e->SetMarkerStyle(kFullCircle);
  r_pPb13e->SetMarkerColor(kGreen);
  r_pPb13e->SetMarkerSize(2);

  r_pPb13f->SetLineColor(kRed);
  r_pPb13f->SetLineWidth(2);
  r_pPb13f->SetLineStyle(kSolid);
  r_pPb13f->SetMarkerStyle(kFullCircle);
  r_pPb13f->SetMarkerColor(kRed);
  r_pPb13f->SetMarkerSize(2);
  
  r_pPb13fnew->SetLineColor(kMagenta);
  r_pPb13fnew->SetLineWidth(2);
  r_pPb13fnew->SetLineStyle(kSolid);
  r_pPb13fnew->SetMarkerStyle(kFullCircle);
  r_pPb13fnew->SetMarkerColor(kMagenta);
  r_pPb13fnew->SetMarkerSize(2);

  TCanvas* c_pbp = new TCanvas("c_pbp", "c_pbp", 600, 600);
  r_pPb->Draw("L hist p");
  /*r_pPb13d->Draw("same L hist p");
  r_pPb13e->Draw("same L hist p");
  r_pPb13f->Draw("same L hist p");
  r_pPb13fnew->Draw("same L hist p");//*/
  r_pPb->Draw("same e1");
  /*r_pPb13d->Draw("same e1");
  r_pPb13e->Draw("same e1");
  r_pPb13f->Draw("same e1");
  r_pPb13fnew->Draw("same e1");//*/
  

  /*TLegend* l_pbp = new TLegend(0.25, 0.15, 0.6, 0.3);
  l_pbp->SetBorderSize(0);
  l_pbp->SetNColumns(2);
  l_pbp->AddEntry(r_pPb, "Full p-Pb");
  l_pbp->AddEntry(r_pPb13d, "13d");
  l_pbp->AddEntry(r_pPb13e, "13e");
  l_pbp->AddEntry(r_pPb13f, "13f");
  l_pbp->AddEntry(r_pPb13fnew, "13f reco later");
  l_pbp->Draw("same");//*/

  TH1F* res_pPb13d = calcResiduals("res_pPb13d", r_pPb, r_pPb13d);
  TH1F* res_pPb13e = calcResiduals("res_pPb13e", r_pPb, r_pPb13e);
  TH1F* res_pPb13f = calcResiduals("res_pPb13f", r_pPb, r_pPb13f);
  TH1F* res_pPb13fnew = calcResiduals("res_pPb13fnew", r_pPb, r_pPb13fnew);

  res_pPb13d->GetYaxis()->SetRangeUser(-0.5, 0.5);
  res_pPb13d->SetTitle(";#eta;#frac{all pPb - 1 period}{all pPb}");
  /*TCanvas* c_pPbRes = new TCanvas("c_pPbRes", "c_pPbRes", 600, 600);
  res_pPb13d->GetYaxis()->SetRangeUser(-0.5, 0.5);
  res_pPb13d->Draw("e1");
  res_pPb13e->Draw("same e1");
  res_pPb13f->Draw("same e1");
  res_pPb13fnew->Draw("same e1");    
  res_pPb13d->Draw("same L hist p");
  res_pPb13e->Draw("same L hist p");
  res_pPb13f->Draw("same L hist p");
  res_pPb13fnew->Draw("same L hist p");
  l_pbp->Draw("same");//*/


  TH1F* etaFactors_pPb = calcCorrectionFactor("etaFactors_pPb", r_pPb, "pPb");
  TH1F* etaFactors_pp = calcCorrectionFactor("etaFactors_pp", r_pp, "pp"); 
  /*TFile* fout = new TFile("etaCorrectionFactors.root", "RECREATE");
  etaFactors_pPb->Write("etaFactors_pPb");
  etaFactors_pp->Write("etaFactors_pp");
  fout->Close();//*/
  //printHistEntries(etaFactors_pp);

  //p-Pb average
  TLine* line_pPb = new TLine(-0.7, 0.0942147, 0.7, 0.0942147);
  line_pPb->SetLineColor(kBlack);
  line_pPb->SetLineStyle(kDashed);
  line_pPb->SetLineWidth(2);

  //pp average
  TLine* line_pp = new TLine(-0.7, 0.11313, 0.7, 0.11313);
  line_pp->SetLineColor(kBlack);
  line_pp->SetLineStyle(kDashed);
  line_pp->SetLineWidth(2);

  TCanvas* c_ave = new TCanvas("c_ave", "c_ave", 1200, 600);
  c_ave->Divide(2, 1);
  c_ave->cd(1);
  r_pPb->Draw("L hist p");
  r_pPb->Draw("same e1");
  line_pPb->Draw("same");
  c_ave->cd(2);
  r_pp->Draw("L hist p");
  r_pp->Draw("same e1");
  line_pp->Draw("same");//*/



    
  //p-Pb
  TH1F* hReco_pt = (TH1F*)f_pPbData->Get("hReco_pt");//p-Pb
  TH1F* hRecoPure = (TH1F*)f_pPbMC->Get("hRecoPure");//p-Pb
  Double_t numEvents_pPbData_pt = hNorm_pPbData->GetBinContent(18);//bin 5 = regular, bin 18 = with pT > 12 event cut
  Double_t numEvents_pPbMC_pt = hNorm_pPbMC->GetBinContent(8);//bin 4 = regular, bin 6 with weights, bin 8 = weights+pT > 12//*/
  
  /*TH1F* hReco_pt= (TH1F*)f_ppData->Get("hReco_pt");//pp
  TH1F* hRecoPure = (TH1F*)f_ppMC->Get("hRecoPure");//pp
  Double_t numEvents_pPbData_pt = hNorm_ppData->GetBinContent(18);//bin 5 = regular, bin 18 = with pT > 12 event cut
  Double_t numEvents_pPbMC_pt = hNorm_ppMC->GetBinContent(8);//bin 4 = regular, bin 6 with weights, bin 8 = weights+pT > 12//*/

  TH1F* hReco_pt_ratio = (TH1F*)hReco_pt->Clone("hReco_pt_ratio");

  /*for(int i = 1; i < hReco_pt->GetNbinsX()+1; i++){
    Double_t dEta = hReco_pt->GetBinWidth(i);

    //Double_t content_pPbDataEG1 = hReco_pt->GetBinContent(i);
    //Double_t content_pPbDataEG2 = hEG2woPurity->GetBinContent(i);
    Double_t content_pPbData = hReco_pt->GetBinContent(i);//content_pPbDataEG1 + content_pPbDataEG2;
    Double_t temp_pPbData = content_pPbData/(dEta*numEvents_pPbData_pt);
    Double_t error_pPbData  =  hReco_pt->GetBinError(i);//hReco_pt->GetBinError(i);
    Double_t tempE_pPbData = error_pPbData/(dEta*numEvents_pPbData_pt);
    hReco_pt->SetBinContent(i, temp_pPbData);
    hReco_pt ->SetBinError(i, tempE_pPbData);
    
    Double_t content_pPbMC = hRecoPure->GetBinContent(i);
    Double_t temp_pPbMC = content_pPbMC/(dEta*numEvents_pPbMC_pt);
    Double_t error_pPbMC  =  hRecoPure->GetBinError(i);
    Double_t tempE_pPbMC = error_pPbMC/(dEta*numEvents_pPbMC_pt);
    hRecoPure->SetBinContent(i, temp_pPbMC);
    hRecoPure->SetBinError(i, tempE_pPbMC);

    Double_t content_ratio = temp_pPbData/temp_pPbMC;//(hReco_pt->GetBinContent(i))/(hRecoPure->GetBinContent(i));
    Double_t error_ratio = content_ratio*TMath::Sqrt(TMath::Power(hReco_pt->GetBinError(i)/hReco_pt->GetBinContent(i), 2)+TMath::Power(hRecoPure->GetBinError(i)/hRecoPure->GetBinContent(i),2));
    hReco_pt_ratio->SetBinContent(i, content_ratio);
    hReco_pt_ratio->SetBinError(i, error_ratio);


  }//*/
  
  hReco_pt_ratio->Scale(1.0/hReco_pt_ratio->Integral());
  hRecoPure->Scale(1.0/hRecoPure->Integral());
  hReco_pt_ratio->Divide(hRecoPure);//*/

  hReco_pt_ratio->GetXaxis()->SetRangeUser(12, 60);
  hReco_pt_ratio->SetTitle(";E_{T};data/MC_{rec}");
  //TCanvas* c_ptRatio = new TCanvas("c_ptRatio", "c_ptRatio", 600, 600);
  /*hReco_pt_ratio->Draw("L hist p");
    hReco_pt_ratio->Draw("same e1");//*/
  //hReco_pt->("L hist p e1");


  TH1F* phi_pPbData = (TH1F*)f_pPbData->Get("hPhiwEtaCorr");
  TH1F* phi_ppData = (TH1F*)f_ppData->Get("hPhiwEtaCorr");
  TH1F* phi_pPbMC = (TH1F*)f_pPbMC->Get("hPhiW");
  TH1F* phi_ppMC = (TH1F*)f_ppMC->Get("hPhiW");
  phi_pPbData->Rebin(2);
  phi_ppData->Rebin(2);
  phi_pPbMC->Rebin(2);
  phi_ppMC->Rebin(2);
  normalize(phi_pPbData, numEvents_pPbData);
  normalize(phi_ppData, numEvents_ppData);
  normalize(phi_pPbMC, numEvents_pPbMC);
  normalize(phi_ppMC, numEvents_ppMC);
  
  TH1F* phi_pPb = getRatio("phi_pPb", phi_pPbData, phi_pPbMC);
  TH1F* phi_pp = getRatio("phi_pp", phi_ppData, phi_ppMC);
  //phi_pPb->Rebin(2);
  //phi_pPb->Rebin(2);
  phi_pPb->SetTitle("p-Pb");
  phi_pp->SetTitle("pp");
  phi_pPb->GetXaxis()->SetRangeUser(1, 3.5);
  phi_pp->GetXaxis()->SetRangeUser(1, 3.5);
  TCanvas* c_phi = new TCanvas("c_phi", "c_phi", 1200, 600);
  c_phi->Divide(2, 1);
  c_phi->cd(1);
  phi_pPb->Draw("L hist p");
  phi_pPb->Draw("same e1");
  c_phi->cd(2);
  phi_pp->Draw("L hist p");
  phi_pp->Draw("same e1");

  
}

