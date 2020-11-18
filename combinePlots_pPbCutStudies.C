#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TVector2.h"
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

void combinePlots_pPbCutStudies(){
     
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
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/rfOutput/pPOutput/";
  
  TFile* file13d = new TFile(Form("%sfout_7_26bins_13d_all10runs_noSkim_forRTrig_MBEG1EG2exlusion_tof20_eCross5.root", path.Data()), "READ");
  TFile* file13e1 = new TFile(Form("%sfout_7_26bins_13e_10runs_noSkim_part1_forRTrig_MBEG1EG2exlusion_tof20_eCross5.root", path.Data()), "READ");
  TFile* file13e2 = new TFile(Form("%sfout_7_26bins_13e_10runs_noSkim_part2_forRTrig_MBEG1EG2exlusion_tof20_eCross5.root", path.Data()), "READ");
  TFile* file13f1 = new TFile(Form("%sfout_7_26bins_13f_10runs_noSkim_part1_forRTrig_MBEG1EG2exlusion_tof20_eCross5.root", path.Data()), "READ");
  TFile* file13f2 = new TFile(Form("%sfout_7_26bins_13f_10runs_noSkim_part2_forRTrig_MBEG1EG2exlusion_tof20_eCross5.root", path.Data()), "READ");
  TFile* file13f3 = new TFile(Form("%sfout_7_26bins_13f_10runs_noSkim_part3_forRTrig_MBEG1EG2exlusion_tof20_eCross5.root", path.Data()), "READ");
  TFile* file13f4 = new TFile(Form("%sfout_7_26bins_13f_10runs_noSkim_part4_forRTrig_MBEG1EG2exlusion_tof20_eCross5.root", path.Data()), "READ");
  TFile* file13f5 = new TFile(Form("%sfout_7_26bins_13f_3runs_noSkim_part5_forRTrig_MBEG1EG2exlusion_tof20_eCross5.root", path.Data()), "READ");
    
  if(!file13d)
    {
      cout << "Run 13d file not found" << endl;
      return;
    }

  if(!file13e1)
    {
      cout << "Run 13e1 file not found" << endl;
      return;
    }
  if(!file13e2)
    {
      cout << "Run 13e2 file not found" << endl;
      return;
    }

  if(!file13f1)
    {
      cout << "Run 13f1 file not found" << endl;
      return;
    }
  
  if(!file13f2)
    {
      cout << "Run 13f2 file not found" << endl;
      return;
    }
  
  if(!file13f3)
    {
      cout << "Run 13f3 file not found" << endl;
      return;
    }
  
  if(!file13f4)
    {
      cout << "Run 13f4 file not found" << endl;
      return;
    }

  if(!file13f5)
    {
      cout << "Run 13f5 file not found" << endl;
      return;
    }
  
  

  TH1F* eg113d = (TH1F*)file13d->Get("hEG1_E");
  TH1F* eg113e1 = (TH1F*)file13e1->Get("hEG1_E");
  TH1F* eg113e2 = (TH1F*)file13e2->Get("hEG1_E");
  TH1F* eg113f1 = (TH1F*)file13f1->Get("hEG1_E");
  TH1F* eg113f2 = (TH1F*)file13f2->Get("hEG1_E");
  TH1F* eg113f3 = (TH1F*)file13f3->Get("hEG1_E");
  TH1F* eg113f4 = (TH1F*)file13f4->Get("hEG1_E");
  TH1F* eg113f5 = (TH1F*)file13f5->Get("hEG1_E");
  eg113d->SetName("eg113d");
  eg113e1->SetName("eg113e1");
  eg113e2->SetName("eg113e2");
  eg113f1->SetName("eg113f1");
  eg113f2->SetName("eg113f2");
  eg113f3->SetName("eg113f3");
  eg113f4->SetName("eg113f4");
  eg113f5->SetName("eg113f5");

  TH1F* eg213d = (TH1F*)file13d->Get("hEG2_E");
  TH1F* eg213e1 = (TH1F*)file13e1->Get("hEG2_E");
  TH1F* eg213e2 = (TH1F*)file13e2->Get("hEG2_E");
  TH1F* eg213f1 = (TH1F*)file13f1->Get("hEG2_E");
  TH1F* eg213f2 = (TH1F*)file13f2->Get("hEG2_E");
  TH1F* eg213f3 = (TH1F*)file13f3->Get("hEG2_E");
  TH1F* eg213f4 = (TH1F*)file13f4->Get("hEG2_E");
  TH1F* eg213f5 = (TH1F*)file13f5->Get("hEG2_E");
  eg213d->SetName("eg213d");
  eg213e1->SetName("eg213e1");
  eg213e2->SetName("eg213e2");
  eg213f1->SetName("eg213f1");
  eg213f2->SetName("eg213f2");
  eg213f3->SetName("eg213f3");
  eg213f4->SetName("eg213f4");
  eg213f5->SetName("eg213f5");

  TH1F* n13d = (TH1F*)file13d->Get("hNormalizer");
  TH1F* n13e1 = (TH1F*)file13e1->Get("hNormalizer");
  TH1F* n13e2 = (TH1F*)file13e2->Get("hNormalizer");
  TH1F* n13f1 = (TH1F*)file13f1->Get("hNormalizer");
  TH1F* n13f2 = (TH1F*)file13f2->Get("hNormalizer");
  TH1F* n13f3 = (TH1F*)file13f3->Get("hNormalizer");
  TH1F* n13f4 = (TH1F*)file13f4->Get("hNormalizer");
  TH1F* n13f5 = (TH1F*)file13f5->Get("hNormalizer");
  n13d->SetName("n13d");
  n13e1->SetName("n13e1");
  n13e2->SetName("n13e2");
  n13f1->SetName("n13f1");
  n13f2->SetName("n13f2");
  n13f3->SetName("n13f3");
  n13f4->SetName("n13f4");
  n13f5->SetName("n13f5");

  TH1F* hNormalizer = (TH1F*)n13d->Clone();
  hNormalizer->SetName("hNormalizer");
  hNormalizer->Add(n13e1);
  hNormalizer->Add(n13e2);
  hNormalizer->Add(n13f1);
  hNormalizer->Add(n13f2);
  hNormalizer->Add(n13f3);
  hNormalizer->Add(n13f4);
  hNormalizer->Add(n13f5);

  Double_t numEG113d = n13d->GetBinContent(12);
  Double_t numEG113e1 = n13e1->GetBinContent(12);
  Double_t numEG113e2 = n13e2->GetBinContent(12);
  Double_t numEG113f1 = n13f1->GetBinContent(12);
  Double_t numEG113f2 = n13f2->GetBinContent(12);
  Double_t numEG113f3 = n13f3->GetBinContent(12);
  Double_t numEG113f4 = n13f4->GetBinContent(12);
  Double_t numEG113f5 = n13f5->GetBinContent(12);

  Double_t numEG213d = n13d->GetBinContent(13);
  Double_t numEG213e1 = n13e1->GetBinContent(13);
  Double_t numEG213e2 = n13e2->GetBinContent(13);
  Double_t numEG213f1 = n13f1->GetBinContent(13);
  Double_t numEG213f2 = n13f2->GetBinContent(13);
  Double_t numEG213f3 = n13f3->GetBinContent(13);
  Double_t numEG213f4 = n13f4->GetBinContent(13);
  Double_t numEG213f5 = n13f5->GetBinContent(13);

  TH1F* hEG1_E = (TH1F*)eg113d->Clone();
  TH1F* hEG2_E = (TH1F*)eg213d->Clone();
 
  hEG1_E->SetName("hEG1_E");
  hEG2_E->SetName("hEG2_E");

  Double_t numEG1tot = numEG113d+numEG113e1+numEG113e2+numEG113f1+numEG113f2+numEG113f3+numEG113f4+numEG113f5;
  Double_t numEG2tot = numEG213d+numEG213e1+numEG213e2+numEG213f1+numEG213f2+numEG213f3+numEG213f4+numEG213f5;

  for(int i = 1; i < hEG1_E->GetNbinsX()+1; i++){

    Double_t tmpEG113d = eg113d->GetBinContent(i);
    Double_t tmpEG113e1 = eg113e1->GetBinContent(i);
    Double_t tmpEG113e2 = eg113e2->GetBinContent(i);
    Double_t tmpEG113f1 = eg113f1->GetBinContent(i);
    Double_t tmpEG113f2 = eg113f2->GetBinContent(i);
    Double_t tmpEG113f3 = eg113f3->GetBinContent(i);
    Double_t tmpEG113f4 = eg113f4->GetBinContent(i);
    Double_t tmpEG113f5 = eg113f5->GetBinContent(i);
    

    Double_t errEG113d = eg113d->GetBinError(i);
    Double_t errEG113e1 = eg113e1->GetBinError(i);
    Double_t errEG113e2 = eg113e2->GetBinError(i);
    Double_t errEG113f1 = eg113f1->GetBinError(i);
    Double_t errEG113f2 = eg113f2->GetBinError(i);
    Double_t errEG113f3 = eg113f3->GetBinError(i);
    Double_t errEG113f4 = eg113f4->GetBinError(i);
    Double_t errEG113f5 = eg113f5->GetBinError(i);

    Double_t eg1Content = (tmpEG113d*numEG113d
			   +tmpEG113e1*numEG113e1
			   +tmpEG113e2*numEG113e2
			   +tmpEG113f1*numEG113f1
			   +tmpEG113f2*numEG113f2
			   +tmpEG113f3*numEG113f3
			   +tmpEG113f4*numEG113f4
			   +tmpEG113f5*numEG113f5
			   )/numEG1tot;

    Double_t eg1Error = TMath::Sqrt((TMath::Power(errEG113d*numEG113d, 2)
				     +TMath::Power(errEG113e1*numEG113e1,2)
				     +TMath::Power(errEG113e2*numEG113e2,2)
				     +TMath::Power(errEG113f1*numEG113f1,2)
				     +TMath::Power(errEG113f2*numEG113f2,2)
				     +TMath::Power(errEG113f3*numEG113f3,2)
				     +TMath::Power(errEG113f4*numEG113f4,2)
				     +TMath::Power(errEG113f5*numEG113f5,2)
				     )
				    )/numEG1tot;

    hEG1_E->SetBinContent(i, eg1Content);
    hEG1_E->SetBinError(i, eg1Error);

  }//end eg1

  for(int i = 1; i < hEG2_E->GetNbinsX()+1; i++){

    Double_t tmpEG213d = eg213d->GetBinContent(i);
    Double_t tmpEG213e1 = eg213e1->GetBinContent(i);
    Double_t tmpEG213e2 = eg213e2->GetBinContent(i);
    Double_t tmpEG213f1 = eg213f1->GetBinContent(i);
    Double_t tmpEG213f2 = eg213f2->GetBinContent(i);
    Double_t tmpEG213f3 = eg213f3->GetBinContent(i);
    Double_t tmpEG213f4 = eg213f4->GetBinContent(i);
    Double_t tmpEG213f5 = eg213f5->GetBinContent(i);
    

    Double_t errEG213d = eg213d->GetBinError(i);
    Double_t errEG213e1 = eg213e1->GetBinError(i);
    Double_t errEG213e2 = eg213e2->GetBinError(i);
    Double_t errEG213f1 = eg213f1->GetBinError(i);
    Double_t errEG213f2 = eg213f2->GetBinError(i);
    Double_t errEG213f3 = eg213f3->GetBinError(i);
    Double_t errEG213f4 = eg213f4->GetBinError(i);
    Double_t errEG213f5 = eg213f5->GetBinError(i);

    Double_t eg2Content = (tmpEG213d*numEG213d
			   +tmpEG213e1*numEG213e1
			   +tmpEG213e2*numEG213e2
			   +tmpEG213f1*numEG213f1
			   +tmpEG213f2*numEG213f2
			   +tmpEG213f3*numEG213f3
			   +tmpEG213f4*numEG213f4
			   +tmpEG213f5*numEG213f5
			   )/numEG2tot;

    Double_t eg2Error = TMath::Sqrt((TMath::Power(errEG213d*numEG213d, 2)
				     +TMath::Power(errEG213e1*numEG213e1,2)
				     +TMath::Power(errEG213e2*numEG213e2,2)
				     +TMath::Power(errEG213f1*numEG213f1,2)
				     +TMath::Power(errEG213f2*numEG213f2,2)
				     +TMath::Power(errEG213f3*numEG213f3,2)
				     +TMath::Power(errEG213f4*numEG213f4,2)
				     +TMath::Power(errEG213f5*numEG213f5,2)
				     )
				    )/numEG2tot;

    hEG2_E->SetBinContent(i, eg2Content);
    hEG2_E->SetBinError(i, eg2Error);

  }//end eg2

  /*hCluster_tof
  hCluster_tof20GeV
  hExoticity
  hNcell
  hNLM
  hD2BC
  hEta
  hPhi*/

  TH1F* hCluster_tof13d = (TH1F*)file13d->Get("hCluster_tof");
  TH1F* hCluster_tof13e1 = (TH1F*)file13e1->Get("hCluster_tof");
  TH1F* hCluster_tof13e2 = (TH1F*)file13e2->Get("hCluster_tof");
  TH1F* hCluster_tof13f1 = (TH1F*)file13f1->Get("hCluster_tof");
  TH1F* hCluster_tof13f2 = (TH1F*)file13f2->Get("hCluster_tof");
  TH1F* hCluster_tof13f3 = (TH1F*)file13f3->Get("hCluster_tof");
  TH1F* hCluster_tof13f4 = (TH1F*)file13f4->Get("hCluster_tof");
  TH1F* hCluster_tof13f5 = (TH1F*)file13f5->Get("hCluster_tof");
  hCluster_tof13d->SetName("hCluster_tof13d");
  hCluster_tof13e1->SetName("hCluster_tof13e1");
  hCluster_tof13e2->SetName("hCluster_tof13e2");
  hCluster_tof13f1->SetName("hCluster_tof13f1");
  hCluster_tof13f2->SetName("hCluster_tof13f2");
  hCluster_tof13f3->SetName("hCluster_tof13f3");
  hCluster_tof13f4->SetName("hCluster_tof13f4");
  hCluster_tof13f5->SetName("hCluster_tof13f5");
  TH1F* hCluster_tof = (TH1F*)hCluster_tof13d->Clone();
  hCluster_tof->SetName("hCluster_tof");
  hCluster_tof->Add(hCluster_tof13e1);
  hCluster_tof->Add(hCluster_tof13e2);
  hCluster_tof->Add(hCluster_tof13f1);
  hCluster_tof->Add(hCluster_tof13f2);
  hCluster_tof->Add(hCluster_tof13f3);
  hCluster_tof->Add(hCluster_tof13f4);
  hCluster_tof->Add(hCluster_tof13f5);

  TH1F* hExoticity13d = (TH1F*)file13d->Get("hExoticity");
  TH1F* hExoticity13e1 = (TH1F*)file13e1->Get("hExoticity");
  TH1F* hExoticity13e2 = (TH1F*)file13e2->Get("hExoticity");
  TH1F* hExoticity13f1 = (TH1F*)file13f1->Get("hExoticity");
  TH1F* hExoticity13f2 = (TH1F*)file13f2->Get("hExoticity");
  TH1F* hExoticity13f3 = (TH1F*)file13f3->Get("hExoticity");
  TH1F* hExoticity13f4 = (TH1F*)file13f4->Get("hExoticity");
  TH1F* hExoticity13f5 = (TH1F*)file13f5->Get("hExoticity");
  hExoticity13d->SetName("hExoticity13d");
  hExoticity13e1->SetName("hExoticity13e1");
  hExoticity13e2->SetName("hExoticity13e2");
  hExoticity13f1->SetName("hExoticity13f1");
  hExoticity13f2->SetName("hExoticity13f2");
  hExoticity13f3->SetName("hExoticity13f3");
  hExoticity13f4->SetName("hExoticity13f4");
  hExoticity13f5->SetName("hExoticity13f5");
  TH1F* hExoticity = (TH1F*)hExoticity13d->Clone();
  hExoticity->SetName("hExoticity");
  hExoticity->Add(hExoticity13e1);
  hExoticity->Add(hExoticity13e2);
  hExoticity->Add(hExoticity13f1);
  hExoticity->Add(hExoticity13f2);
  hExoticity->Add(hExoticity13f3);
  hExoticity->Add(hExoticity13f4);
  hExoticity->Add(hExoticity13f5);

  
  TString filename = file13d->GetName();
  Int_t index = filename.Index("13d_all10runs");
  filename.Replace(index, 7, "pPbAll");
  if(filename.CompareTo(file13d->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");

    hEG1_E->Write("hEG1_E");
    hEG2_E->Write("hEG2_E");
    hNormalizer->Write("hNormalizer");

    hCluster_tof->Write("hCluster_tof");
    hExoticity->Write("hExoticity");
    //hNcell->Write("hNcell");
    //hNLM->Write("hNLM");
    //hD2BC->Write("hD2BC");
    //hEta->Write("hEta");
    //hPhi->Write("hPhi");

    fout->Close();
    
  }//end filename compare

  
  
}//end combinePlots
