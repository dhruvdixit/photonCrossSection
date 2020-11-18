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

void combinePlots_pPb(){

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

  TFile* file13c000 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part000_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c002 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part002_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c003 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part003_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c004 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part004_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c005 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part005_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c006 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part006_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c007 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part007_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c008 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part008_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c009 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part009_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c010 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part010_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c011 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part011_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c012 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part012_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c013 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part013_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13c014 = new TFile(Form("%sfout_1_26bins_13c_14runs_noThresh_phySel_part014_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");

  if(!file13c000)
    {
      cout << "Run 13c000 file not found" << endl;
      return;
    }
  TH1F* mb13c000 = (TH1F*)file13c000->Get("hMB_E");
  mb13c000->SetName("mb13c000");
  TH1F* n13c000 = (TH1F*)file13c000->Get("hNormalizer");
  n13c000->SetName("n13c000");

  if(!file13c002)
    {
      cout << "Run 13c002 file not found" << endl;
      return;
    }
  TH1F* mb13c002 = (TH1F*)file13c002->Get("hMB_E");
  mb13c002->SetName("mb13c002");
  TH1F* n13c002 = (TH1F*)file13c002->Get("hNormalizer");
  n13c002->SetName("n13c002");

  if(!file13c003)
    {
      cout << "Run 13c003 file not found" << endl;
      return;
    }
  TH1F* mb13c003 = (TH1F*)file13c003->Get("hMB_E");
  mb13c003->SetName("mb13c003");
  TH1F* n13c003 = (TH1F*)file13c003->Get("hNormalizer");
  n13c003->SetName("n13c003");

  if(!file13c004)
    {
      cout << "Run 13c004 file not found" << endl;
      return;
    }
  TH1F* mb13c004 = (TH1F*)file13c004->Get("hMB_E");
  mb13c004->SetName("mb13c004");
  TH1F* n13c004 = (TH1F*)file13c004->Get("hNormalizer");
  n13c004->SetName("n13c004");

  if(!file13c005)
    {
      cout << "Run 13c005 file not found" << endl;
      return;
    }
  TH1F* mb13c005 = (TH1F*)file13c005->Get("hMB_E");
  mb13c005->SetName("mb13c005");
  TH1F* n13c005 = (TH1F*)file13c005->Get("hNormalizer");
  n13c005->SetName("n13c005");

  if(!file13c006)
    {
      cout << "Run 13c006 file not found" << endl;
      return;
    }
  TH1F* mb13c006 = (TH1F*)file13c006->Get("hMB_E");
  mb13c006->SetName("mb13c006");
  TH1F* n13c006 = (TH1F*)file13c006->Get("hNormalizer");
  n13c006->SetName("n13c006");

  if(!file13c007)
    {
      cout << "Run 13c007 file not found" << endl;
      return;
    }
  TH1F* mb13c007 = (TH1F*)file13c007->Get("hMB_E");
  mb13c007->SetName("mb13c007");
  TH1F* n13c007 = (TH1F*)file13c007->Get("hNormalizer");
  n13c007->SetName("n13c007");
  
  if(!file13c008)
    {
      cout << "Run 13c008 file not found" << endl;
      return;
    }
  TH1F* mb13c008 = (TH1F*)file13c008->Get("hMB_E");
  mb13c008->SetName("mb13c008");
  TH1F* n13c008 = (TH1F*)file13c008->Get("hNormalizer");
  n13c008->SetName("n13c008");

  if(!file13c009)
    {
      cout << "Run 13c009 file not found" << endl;
      return;
    }
  TH1F* mb13c009 = (TH1F*)file13c009->Get("hMB_E");
  mb13c009->SetName("mb13c009");
  TH1F* n13c009 = (TH1F*)file13c009->Get("hNormalizer");
  n13c009->SetName("n13c009");

  if(!file13c010)
    {
      cout << "Run 13c010 file not found" << endl;
      return;
    }
  TH1F* mb13c010 = (TH1F*)file13c010->Get("hMB_E");
  mb13c010->SetName("mb13c010");
  TH1F* n13c010 = (TH1F*)file13c010->Get("hNormalizer");
  n13c010->SetName("n13c010");

  if(!file13c011)
    {
      cout << "Run 13c011 file not found" << endl;
      return;
    }
  TH1F* mb13c011 = (TH1F*)file13c011->Get("hMB_E");
  mb13c011->SetName("mb13c011");
  TH1F* n13c011 = (TH1F*)file13c011->Get("hNormalizer");
  n13c011->SetName("n13c011");

  if(!file13c012)
    {
      cout << "Run 13c012 file not found" << endl;
      return;
    }
  TH1F* mb13c012 = (TH1F*)file13c012->Get("hMB_E");
  mb13c012->SetName("mb13c012");
  TH1F* n13c012 = (TH1F*)file13c012->Get("hNormalizer");
  n13c012->SetName("n13c012");

  if(!file13c013)
    {
      cout << "Run 13c013 file not found" << endl;
      return;
    }
  TH1F* mb13c013 = (TH1F*)file13c013->Get("hMB_E");
  mb13c013->SetName("mb13c013");
  TH1F* n13c013 = (TH1F*)file13c013->Get("hNormalizer");
  n13c013->SetName("n13c013");

  if(!file13c014)
    {
      cout << "Run 13c014 file not found" << endl;
      return;
    }
  TH1F* mb13c014 = (TH1F*)file13c014->Get("hMB_E");
  mb13c014->SetName("mb13c014");
  TH1F* n13c014 = (TH1F*)file13c014->Get("hNormalizer");
  n13c014->SetName("n13c014");

  
  Double_t numMB13c000 = n13c000->GetBinContent(11);
  Double_t numMB13c002 = n13c002->GetBinContent(11);
  Double_t numMB13c003 = n13c003->GetBinContent(11);
  Double_t numMB13c004 = n13c004->GetBinContent(11);
  Double_t numMB13c005 = n13c005->GetBinContent(11);
  Double_t numMB13c006 = n13c006->GetBinContent(11);
  Double_t numMB13c007 = n13c007->GetBinContent(11);
  Double_t numMB13c008 = n13c008->GetBinContent(11);
  Double_t numMB13c009 = n13c009->GetBinContent(11);
  Double_t numMB13c010 = n13c010->GetBinContent(11);
  Double_t numMB13c011 = n13c011->GetBinContent(11);
  Double_t numMB13c012 = n13c012->GetBinContent(11);
  Double_t numMB13c013 = n13c013->GetBinContent(11);
  Double_t numMB13c014 = n13c014->GetBinContent(11);

  Double_t numMBtot = numMB13c000 + numMB13c002 + numMB13c003 + numMB13c004 + numMB13c005 + numMB13c006 + numMB13c007 + numMB13c008 + numMB13c009 + numMB13c010 + numMB13c011 + numMB13c012 + numMB13c013 + numMB13c014;
  cout << "Total number of MB events: " << numMBtot << endl;
  TH1F* hMB_E = (TH1F*)mb13c000->Clone();
  hMB_E->SetName("hMB_E");
  
  for(int i = 1; i < hMB_E->GetNbinsX()+1; i++){

    
    Double_t tmpMB13c000 = mb13c000->GetBinContent(i);
    Double_t tmpMB13c002 = mb13c002->GetBinContent(i);
    Double_t tmpMB13c003 = mb13c003->GetBinContent(i);
    Double_t tmpMB13c004 = mb13c004->GetBinContent(i);
    Double_t tmpMB13c005 = mb13c005->GetBinContent(i);
    Double_t tmpMB13c006 = mb13c006->GetBinContent(i);
    Double_t tmpMB13c007 = mb13c007->GetBinContent(i);
    Double_t tmpMB13c008 = mb13c008->GetBinContent(i);
    Double_t tmpMB13c009 = mb13c009->GetBinContent(i);
    Double_t tmpMB13c010 = mb13c010->GetBinContent(i);
    Double_t tmpMB13c011 = mb13c011->GetBinContent(i);
    Double_t tmpMB13c012 = mb13c012->GetBinContent(i);
    Double_t tmpMB13c013 = mb13c013->GetBinContent(i);
    Double_t tmpMB13c014 = mb13c014->GetBinContent(i);
    

    Double_t errMB13c000 = mb13c000->GetBinError(i);
    Double_t errMB13c002 = mb13c002->GetBinError(i);
    Double_t errMB13c003 = mb13c003->GetBinError(i);
    Double_t errMB13c004 = mb13c004->GetBinError(i);
    Double_t errMB13c005 = mb13c005->GetBinError(i);
    Double_t errMB13c006 = mb13c006->GetBinError(i);
    Double_t errMB13c007 = mb13c007->GetBinError(i);
    Double_t errMB13c008 = mb13c008->GetBinError(i);
    Double_t errMB13c009 = mb13c009->GetBinError(i);
    Double_t errMB13c010 = mb13c010->GetBinError(i);
    Double_t errMB13c011 = mb13c011->GetBinError(i);
    Double_t errMB13c012 = mb13c012->GetBinError(i);
    Double_t errMB13c013 = mb13c013->GetBinError(i);
    Double_t errMB13c014 = mb13c014->GetBinError(i);
      
    Double_t mbContent = (tmpMB13c000*numMB13c000
			  +tmpMB13c002*numMB13c002
			  +tmpMB13c003*numMB13c003
			  +tmpMB13c004*numMB13c004
			  +tmpMB13c005*numMB13c005
			  +tmpMB13c006*numMB13c006
			  +tmpMB13c007*numMB13c007
			  +tmpMB13c008*numMB13c008
			  +tmpMB13c009*numMB13c009
			  +tmpMB13c010*numMB13c010
			  +tmpMB13c011*numMB13c011
			  +tmpMB13c012*numMB13c012
			  +tmpMB13c013*numMB13c013
			  +tmpMB13c014*numMB13c014
			  )/numMBtot;

    Double_t mbError = TMath::Sqrt((TMath::Power(errMB13c000*numMB13c000, 2)
				    +TMath::Power(errMB13c002*numMB13c002,2)
				    +TMath::Power(errMB13c003*numMB13c003,2)
				    +TMath::Power(errMB13c004*numMB13c004,2)
				    +TMath::Power(errMB13c005*numMB13c005,2)
				    +TMath::Power(errMB13c006*numMB13c006,2)
				    +TMath::Power(errMB13c007*numMB13c007,2)
				    +TMath::Power(errMB13c008*numMB13c008,2)
				    +TMath::Power(errMB13c009*numMB13c009,2)
				    +TMath::Power(errMB13c010*numMB13c010,2)
				    +TMath::Power(errMB13c011*numMB13c011,2)
				    +TMath::Power(errMB13c012*numMB13c012,2)
				    +TMath::Power(errMB13c013*numMB13c013,2)
				    +TMath::Power(errMB13c014*numMB13c014,2)
				    )
				   )/numMBtot;
    hMB_E->SetBinContent(i, 0);
    hMB_E->SetBinError(i, 0);
    cout << i << "\t" << mbError/mbContent << endl;
    if(mbError/mbContent < 1){
      hMB_E->SetBinContent(i, mbContent);
      hMB_E->SetBinError(i, mbError);
    }


  }


  TFile* file13d = new TFile(Form("%sfout_6_26bins_13d_all10runs_noSkim_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13e1 = new TFile(Form("%sfout_6_26bins_13e_10runs_noSkim_part1_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13e2 = new TFile(Form("%sfout_6_26bins_13e_10runs_noSkim_part2_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13f1 = new TFile(Form("%sfout_6_26bins_13f_10runs_noSkim_part1_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13f2 = new TFile(Form("%sfout_6_26bins_13f_10runs_noSkim_part2_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13f3 = new TFile(Form("%sfout_6_26bins_13f_10runs_noSkim_part3_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13f4 = new TFile(Form("%sfout_6_26bins_13f_10runs_noSkim_part4_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");
  TFile* file13f5 = new TFile(Form("%sfout_6_26bins_13f_3runs_noSkim_part5_forRTrig_noMBEG2exlusion_tof20.root", path.Data()), "READ");

    
  
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
  TH1F* hEG1RF = (TH1F*)eg113d->Clone();
  TH1F* hEG2_E = (TH1F*)eg213d->Clone();
  TH1F* hEG2RF = (TH1F*)eg213d->Clone();
  TH1F* hEGARF = (TH1F*)eg213d->Clone();
  TH1F* hNormalizer = (TH1F*)n13d->Clone();
  hEG1_E->SetName("hEG1_E");
  hEG2_E->SetName("hEG2_E");
  hEG1RF->SetName("hEG1RF");
  hEG2RF->SetName("hEG2RF");
  hEGARF->SetName("hEG2RF");
  hNormalizer->SetName("hNormalizer");

  hNormalizer->Add(n13d);
  hNormalizer->Add(n13e2);
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

    hEG1RF->SetBinContent(i, 0);
    hEG1RF->SetBinError(i, 0);
    Double_t mbContent = hMB_E->GetBinContent(i);
    Double_t mbError = hMB_E->GetBinError(i);
    if(mbContent != 0.0){
      Double_t rfContent = eg1Content/mbContent;
      Double_t rfError = rfContent*(TMath::Sqrt(TMath::Power(mbError/mbContent,2)+TMath::Power(eg1Error/eg1Content,2)));
      cout << i << "\t" << rfError/rfContent << endl;
      if(rfError/rfContent < 1){
	hEG1RF->SetBinContent(i, rfContent);
	hEG1RF->SetBinError(i, rfError);
      }
    }
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

    hEG2RF->SetBinContent(i, 0);
    hEG2RF->SetBinError(i, 0);
    Double_t mbContent = hMB_E->GetBinContent(i);
    Double_t mbError = hMB_E->GetBinError(i);
    if(mbContent != 0.0){
      Double_t rfContent = eg2Content/mbContent;
      Double_t rfError = rfContent*(TMath::Sqrt(TMath::Power(mbError/mbContent,2)+TMath::Power(eg2Error/eg2Content,2)));
      cout << i << "\t" << rfError/rfContent << endl;
      if(rfError/rfContent < 1){
	hEG2RF->SetBinContent(i, rfContent);
	hEG2RF->SetBinError(i, rfError);
      }
    }
  }//end eg2

  for(int i = 1; i < hEG2_E->GetNbinsX()+1; i++){
    
    Double_t eg1Content = hEG1_E->GetBinContent(i);
    Double_t eg1Error = hEG1_E->GetBinError(i);
    Double_t eg2Content = hEG2_E->GetBinContent(i);
    Double_t eg2Error = hEG2_E->GetBinError(i);

    hEGARF->SetBinContent(i, 0);
    hEGARF->SetBinError(i, 0);
    if(eg2Content != 0.0){
    Double_t rfContent = eg1Content/eg2Content;
    Double_t rfError = rfContent*(TMath::Sqrt(TMath::Power(eg2Error/eg2Content,2)+TMath::Power(eg1Error/eg1Content,2)));
    hEGARF->SetBinContent(i, rfContent);
    hEGARF->SetBinError(i, rfError);
    }
  }//end eg1/eg2
 
  hEG1_E->SetLineColor(kBlue);
  hEG1_E->SetMarkerColor(kBlue);
  hEG1_E->SetMarkerStyle(kFullCircle);
  hEG2_E->SetLineColor(kRed);
  hEG2_E->SetMarkerColor(kRed);
  hEG2_E->SetMarkerStyle(kFullCircle);
  hMB_E->SetLineColor(kBlack);
  hMB_E->SetMarkerColor(kBlack);
  hMB_E->SetMarkerStyle(kFullCircle);
  
  
  TLegend* ls = new TLegend(0.7, 0.7,0.9, 0.85);
  ls->AddEntry((TObject*)0, "13c = minbias data set", "");
  ls->AddEntry((TObject*)0, "13def = EGA triggered data", "");
  ls->AddEntry(hMB_E, "MB spectra");
  ls->AddEntry(hEG1_E, "EG1 spectra");
  ls->AddEntry(hEG2_E, "EG2 spectra");
			    
  TCanvas* cs = new TCanvas("cs", "cs");
  cs->SetLogy();
  hMB_E->GetYaxis()->SetRangeUser(1e-10, 1);
  hMB_E->SetTitle(";E_{T} (GeV);#frac{1}{N_{ev}}x#frac{dN}{dE_{T}} (a.u.)");
  hMB_E->Draw("e1");
  hEG1_E->Draw("samee1");
  hEG2_E->Draw("samee1");
  ls->Draw("same");

  hEG1RF->SetLineColor(kBlue);
  hEG1RF->SetMarkerColor(kBlue);
  hEG1RF->SetMarkerStyle(kFullCircle);
  hEG2RF->SetLineColor(kRed);
  hEG2RF->SetMarkerColor(kRed);
  hEG2RF->SetMarkerStyle(kFullCircle);
  hEGARF->SetLineColor(kBlack);
  hEGARF->SetMarkerColor(kBlack);
  hEGARF->SetMarkerStyle(kFullCircle);

  
  TLegend* lr = new TLegend(0.15, 0.1,0.75, 0.3);
  lr->AddEntry((TObject*)0, "ALICE #sqrt{s_{NN}} = 5.02 TeV p-Pb Trigger Rejection Factors", "");
  lr->AddEntry(hEG1RF, "EG1/MB Fit (14, 40)");
  lr->AddEntry(hEG2RF, "EG2/MB Fit (10, 40)");
  lr->AddEntry(hEGARF, "EG1/EG2 Fit (16, 40)");
  
  hEG1RF->SetTitle(";E_{T} (GeV); R_{trig}");
  TCanvas* cr = new TCanvas("cr", "cr");
  cr->SetLogy();
  hEG1RF->GetXaxis()->SetRangeUser(0.0, 40.0);
  hEG1RF->GetYaxis()->SetRangeUser(2e-4, 1e5);
  hEG1RF->Draw("e1");
  hEG2RF->Draw("samee1");
  hEGARF->Draw("samee1");
  lr->Draw("same");

  /*TString filename = file13d->GetName();
  Int_t index = filename.Index("13d_all10runs");
  filename.Replace(index, 7, "pPb_all");
  Int_t index2 = filename.Index("isoPhotonOutput");
  filename.Replace(index2, 15, "rfOutput");
  if(filename.CompareTo(file13d->GetName()) != 0){
    cout << "File names are not same. Good!" << endl;
    cout << filename << endl;
    TFile* fout = new TFile(Form("%s", filename.Data()), "RECREATE");
    hMB_E->Write("hMB_E");
    hEG1_E->Write("hEG1_E");
    hEG1RF->Write("hRF");
    hNormalizer->Write("hNormalizer");
    fout->Close();
  }//end filename compare*/






  hEG1RF->Fit("pol0", "", "", 14, 40);
  hEG1RF->GetFunction("pol0")->SetLineColorAlpha(kBlue, 0.);
  hEG1RF->GetFunction("pol0")->SetLineWidth(5);
  hEG2RF->Fit("pol0", "", "", 10, 40);
  hEG2RF->GetFunction("pol0")->SetLineColorAlpha(kRed, 0.);
  hEG2RF->GetFunction("pol0")->SetLineWidth(5);
  hEGARF->Fit("pol0", "", "", 16, 40);
  hEGARF->GetFunction("pol0")->SetLineColorAlpha(kBlack, 0.0);
  hEGARF->GetFunction("pol0")->SetLineWidth(5);
  
  
}//end combinePlots
