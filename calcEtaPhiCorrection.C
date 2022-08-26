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
    Double_t dPhi = dataHist->GetBinWidth(i);

    Double_t content_Data = dataHist->GetBinContent(i);
    Double_t temp_Data = content_Data/(dPhi*numEvents_Data);
    Double_t error_Data  =  dataHist->GetBinError(i);
    Double_t tempE_Data = error_Data/(dPhi*numEvents_Data);
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
    Double_t dPhi = dataHist->GetBinWidth(i);

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

    hRes->Fit("pol0", "Q0", "", 1, 3.5);
    Double_t par0 = (hRes->GetFunction("pol0"))->GetParameter(0);
    //cout << name << "\t" << par0 << endl;
    return hRes;
}

void printHistEntries(TH1F* printHist){

  cout << printHist->GetName() << endl;
  cout << "Bin Num\t\tLow Edge\tHigh Edge\tContent\t\t\tError" << endl;
    
  for(int i = 1; i < printHist->GetNbinsX()+1; i++){
    if(printHist->GetBinError(i) != 0)
      cout << i << "\t\t" << printHist->GetBinLowEdge(i) << "\t\t" << printHist->GetBinLowEdge(i+1) << "\t\t" << printHist->GetBinContent(i) << "\t\t" << printHist->GetBinError(i) << endl;
  }

  return;
}



TH1F* calcCorrectionFactor(const char *name, TH1F* hist, TString systemName){

  TH1F* cfHist;
  //printHistEntries(hist);
  vector<int> binNums;

  if(systemName == "pPb"){
    cout << "System is p-Pb" << endl;
    binNums.push_back(25);
  }
  else if(systemName == "pp"){
    cout << "System is pp" << endl;
    binNums.push_back(26);
  }
  else{
    cout << "Error in calcCorrectionFactor, \"systemName\" is incorrect. " << __LINE__ << endl; 
    return hist;
  }
  
  vector<Double_t> vals;
  vector<Double_t> errs;
  Double_t phiAve = 0;
  Double_t phiAveErr = 0;
  
  for (auto i = binNums.cbegin(); i != binNums.cend(); ++i){
    //cout << *i << " ";
    phiAve += hist->GetBinContent(*i);
    phiAveErr += TMath::Power(hist->GetBinError(*i), 2);
  }

  if(binNums.size() != 0){
    phiAve = phiAve/(Double_t)binNums.size();
    phiAveErr = TMath::Sqrt(phiAveErr)/(Double_t)binNums.size();
  }
  
  cout << phiAve << " +/- " << phiAveErr << endl;

  cfHist = (TH1F*)hist->Clone(name);
  for(int h = 1; h < cfHist->GetNbinsX()+1; h++){
    Double_t content = cfHist->GetBinContent(h);
    Double_t corrFactor = 1;
    if(content != 0)
      corrFactor = phiAve/content;
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


void calcEtaPhiCorrection(){

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


  //Added SM level phi binning
  TFile* f_pPbData = new TFile(Form("%scsOutput/pPbOutput/Feb20AliPhysics/postQMNtuples/wEtaCorr/SMphiBin/fout_6_14bins_firstEvent0_13def_kEMCEGA_kINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_wEtaCorr_SMphiBin_noNorm.root", path.Data()), "READ");
  TFile* f_ppData = new TFile(Form("%scsOutput/ppOutput/Feb20AliPhysics/postQMNtuples/wEtaCorr/SMphiBin/fout_4_14bins_firstEvent0_17q_runAll_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_StdCuts_EX0PurityFit_wEtaCorr_SMphiBin_noNorm.root", path.Data()), "READ");
  TFile* f_pPbMC = new TFile(Form("%sMC/17g6a1/Nonlin/QMNtuples/eta18bins/SMphiBin/etaPhiPlots/fout_14bins_firstEvent0_17g6a1_pthatAll_1run_wNL_GeMomentumFixedStdCuts_etaPhiPlots_noNorm.root", path.Data()), "READ");
  TFile* f_ppMC = new TFile(Form("%sMC/18b10a/Nonlin/QMNtuples/eta18bins/SMphiBin/etaPhiPlots/fout_14bins_firstEvent0_18b10a_pthatAll_2runs_wNL_GeMomentumFixedStdCuts_etaPhiPlots_noNorm.root", path.Data()), "READ");

  
  TH2F* h_pPbData = (TH2F*)f_pPbData->Get("hEtaPhi");
  TH2F* h_ppData = (TH2F*)f_ppData->Get("hEtaPhi");
  TH2F* h_pPbMC = (TH2F*)f_pPbMC->Get("hEtaPhi");
  TH2F* h_ppMC = (TH2F*)f_ppMC->Get("hEtaPhi");

  TH1D* hNorm_pPbData = (TH1D*)f_pPbData->Get("hNormalizer");
  TH1D* hNorm_ppData = (TH1D*)f_ppData->Get("hNormalizer");
  TH1D* hNorm_pPbMC = (TH1D*)f_pPbMC->Get("hNormalizer");
  TH1D* hNorm_ppMC = (TH1D*)f_ppMC->Get("hNormalizer");
  TH2F* r_pPb = (TH2F*)h_pPbData->Clone("r_pPb");
  TH2F* r_pp = (TH2F*)h_ppData->Clone("r_pp");
  
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

  /*for(int i = 1; i < h_pPbData->GetNbinsX()+1; i++){
    for(int j = 1; j < h_pPbData->GetNbinsY()+1; j++){
      Double_t dPhi = h_pPbData->GetYaxis()->GetBinWidth(j);
      Double_t dEta = h_pPbData->GetXaxis()->GetBinWidth(i);
      Double_t dArea = dPhi*dEta;
      
      Double_t content_pPbData = h_pPbData->GetBinContent(i, j);
      Double_t temp_pPbData = content_pPbData/(dArea*numEvents_pPbData);
      Double_t error_pPbData  =  h_pPbData->GetBinError(i, j);
      Double_t tempE_pPbData = error_pPbData/(dArea*numEvents_pPbData);
      h_pPbData->SetBinContent(i, j, temp_pPbData);
      h_pPbData->SetBinError(i, j, tempE_pPbData);
      
      Double_t content_ppData = h_ppData->GetBinContent(i, j);
      Double_t temp_ppData = content_ppData/(dArea*numEvents_ppData);
      Double_t error_ppData  =  h_ppData->GetBinError(i, j);
      Double_t tempE_ppData = error_ppData/(dArea*numEvents_pPbData);
      h_ppData->SetBinContent(i, j, temp_ppData);
      h_ppData->SetBinError(i, j, tempE_ppData);
      
      Double_t content_pPbMC = h_pPbMC->GetBinContent(i, j);
      Double_t temp_pPbMC = content_pPbMC/(dArea*numEvents_pPbMC);
      Double_t error_pPbMC  =  h_pPbMC->GetBinError(i, j);
      Double_t tempE_pPbMC = error_pPbMC/(dArea*numEvents_pPbMC);
      h_pPbMC->SetBinContent(i, j, temp_pPbMC);
      h_pPbMC->SetBinError(i, j, tempE_pPbMC);
      
      Double_t content_ppMC = h_ppMC->GetBinContent(i, j);
      Double_t temp_ppMC = content_ppMC/(dArea*numEvents_ppMC);
      Double_t error_ppMC  =  h_ppMC->GetBinError(i, j);
      Double_t tempE_ppMC = error_ppMC/(dArea*numEvents_ppMC);
      h_ppMC->SetBinContent(i, j, temp_ppMC);
      h_ppMC->SetBinError(i, j, tempE_ppMC);
      
      Double_t content_pPbRatio = temp_pPbData/temp_pPbMC;
      Double_t error_pPbRatio = (temp_pPbData/temp_pPbMC)*TMath::Sqrt(TMath::Power(tempE_pPbData/temp_pPbData, 2)+TMath::Power(tempE_pPbMC/temp_pPbMC, 2));
      if(temp_pPbMC != 0){
	r_pPb->SetBinContent(i, j, content_pPbRatio);
	r_pPb->SetBinError(i, j, error_pPbRatio);
	//cout <<  r_pPb->GetBinContent(i, j) << endl;
      }
      
      Double_t content_ppRatio = temp_ppData/temp_ppMC;
      Double_t error_ppRatio = (temp_ppData/temp_ppMC)*TMath::Sqrt(TMath::Power(tempE_ppData/temp_ppData, 2)+TMath::Power(tempE_ppMC/temp_ppMC, 2));
      if(temp_ppMC != 0){
	r_pp->SetBinContent(i, j, content_ppRatio);
	r_pp->SetBinError(i, j, error_ppRatio);
	//cout <<  r_pp->GetBinContent(i, j) << endl;
      }
    }//end loop over phi
  }//end loop over eta*/
  
  h_pPbData->Scale(1.0/h_pPbData->Integral());
  h_ppData->Scale(1.0/h_ppData->Integral());
  h_pPbMC->Scale(1.0/h_pPbMC->Integral());
  h_ppMC->Scale(1.0/h_ppMC->Integral());
  r_pPb->Scale(1.0/r_pPb->Integral());
  r_pp->Scale(1.0/r_pp->Integral());
  r_pPb->Divide(h_pPbMC);
  r_pp->Divide(h_ppMC);

  h_pPbData->GetXaxis()->SetRangeUser(-0.8, 0.8);
  h_pPbData->GetYaxis()->SetRangeUser(1, 3.5);
  h_pPbMC->GetXaxis()->SetRangeUser(-0.8, 0.8);
  h_pPbMC->GetYaxis()->SetRangeUser(1, 3.5);
  h_ppData->GetXaxis()->SetRangeUser(-0.8, 0.8);
  h_ppData->GetYaxis()->SetRangeUser(1, 3.5);
  h_ppMC->GetXaxis()->SetRangeUser(-0.8, 0.8);
  h_ppMC->GetYaxis()->SetRangeUser(1, 3.5);
  h_pPbData->SetTitle("p-Pb Data (area normalized to 1");
  h_pPbMC->SetTitle("p-Pb MC (area normalized to 1");
  h_ppData->SetTitle("pp Data (area normalized to 1");
  h_ppMC->SetTitle("pp MC (area normalized to 1");

  TCanvas* c_pPb = new TCanvas("c_pPb", "c_pPb", 1200, 600);
  c_pPb->Divide(2, 1);
  c_pPb->cd(1);
  h_pPbData->Draw("colz");
  c_pPb->cd(2);
  h_pPbMC->Draw("colz");

  TCanvas* c_pp = new TCanvas("c_pp", "c_pPb", 1200, 600);
  c_pp->Divide(2, 1);
  c_pp->cd(1);
  h_ppData->Draw("colz");
  c_pp->cd(2);
  h_ppMC->Draw("colz");

  r_pPb->GetXaxis()->SetRangeUser(-0.8, 0.8);
  r_pPb->GetYaxis()->SetRangeUser(1, 3.5);
  r_pp->GetXaxis()->SetRangeUser(-0.8, 0.8);
  r_pp->GetYaxis()->SetRangeUser(1, 3.5);
  r_pPb->SetTitle("p-Pb Data/MC_{rec} ratio (area normalized to 1");
  r_pp->SetTitle("pp Data/MC_{rec} ratio (area normalized to 1");

  TCanvas* c_ratio = new TCanvas("c_ratio", "c_ratio", 1200, 600);
  c_ratio->Divide(2, 1);
  c_ratio->cd(1);
  r_pPb->Draw("colz");
  c_ratio->cd(2);
  r_pp->Draw("colz");
  
}

