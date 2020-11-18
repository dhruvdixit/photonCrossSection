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

void combineAnalysisPlots_pPb(){

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
  gStyle->SetTitleBorderSize(0);//*/
  

  TString path = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/";

  TFile* file13d = new TFile(Form("%sfout_6_14bins_firstEvent0_13d_all10runs_noSkimEG1EG2only_tof20.root", path.Data()), "READ");
  TFile* file13e1 = new TFile(Form("%sfout_6_14bins_firstEvent0_13e_10runs_noSkim_part1EG1EG2only_tof20.root", path.Data()), "READ");
  TFile* file13e2 = new TFile(Form("%sfout_6_14bins_firstEvent0_13e_10runs_noSkim_part2EG1EG2only_tof20.root", path.Data()), "READ");
  TFile* file13f1 = new TFile(Form("%sfout_6_14bins_firstEvent0_13f_10runs_noSkim_part1EG1EG2only_tof20.root", path.Data()), "READ");
  TFile* file13f2 = new TFile(Form("%sfout_6_14bins_firstEvent0_13f_10runs_noSkim_part2EG1EG2only_tof20.root", path.Data()), "READ");
  TFile* file13f3 = new TFile(Form("%sfout_6_14bins_firstEvent0_13f_10runs_noSkim_part3EG1EG2only_tof20.root", path.Data()), "READ");
  TFile* file13f4 = new TFile(Form("%sfout_6_14bins_firstEvent0_13f_10runs_noSkim_part4EG1EG2only_tof20.root", path.Data()), "READ");
  TFile* file13f5 = new TFile(Form("%sfout_6_14bins_firstEvent0_13f_3runs_noSkim_part5EG1EG2only_tof20.root", path.Data()), "READ");

   
  
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

  //TH1F* n13c = (TH1F*)file13c->Get("hNormalizer");
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
  TH1F* hNormalizer = (TH1F*)n13d->Clone();
  hEG1_E->SetName("hEG1_E");
  hEG2_E->SetName("hEG2_E");
  hNormalizer->SetName("hNormalizer");

  hNormalizer->Add(n13e1);
  hNormalizer->Add(n13e2);
  hNormalizer->Add(n13f1);
  hNormalizer->Add(n13f2);
  hNormalizer->Add(n13f3);
  hNormalizer->Add(n13f4);
  hNormalizer->Add(n13f5);

  
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

 
  hEG1_E->SetLineColor(kBlue);
  hEG1_E->SetMarkerColor(kBlue);
  hEG1_E->SetMarkerStyle(kFullCircle);
  hEG2_E->SetLineColor(kRed);
  hEG2_E->SetMarkerColor(kRed);
  hEG2_E->SetMarkerStyle(kFullCircle);  
  
  TLegend* ls = new TLegend(0.6, 0.7,0.85, 0.95);
  ls->AddEntry((TObject*)0, "13def = EGA triggered data", "");
  ls->AddEntry(hEG1_E, "EG1 spectra");
  ls->AddEntry(hEG2_E, "EG2 spectra");
			    
  TCanvas* cs = new TCanvas("cs", "cs");
  cs->SetLogy();
  hEG1_E->GetYaxis()->SetRangeUser(1e-10, 1);
  hEG1_E->SetTitle(";E_{T};#frac{1}{N_{ev}}x#frac{dN}{dE_{T}} (a.u.)");
  hEG1_E->Draw("e1");
  hEG2_E->Draw("samee1");
  ls->Draw("same");


  TString filename = file13d->GetName();
  Int_t index = filename.Index("13d_all10runs");
  filename.Replace(index, 7, "pPb_all");
  if(filename.CompareTo(file13d->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hEG1_E->Write("hEG1_E");
    hEG2_E->Write("hEG2_E");
    hNormalizer->Write("hNormalizer");
    fout->Close();
  }//end filename compare*/
  
  
}//end combinePlots
