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
#include <cstring>
#include <chrono>
#include <ctime> //*/


Float_t GetNonLinearityEnergy(Float_t rawE) {

  Float_t nonlinE = rawE;

  Float_t    fNonLinearityParams[10];
  fNonLinearityParams[0] = 1.91897;
  fNonLinearityParams[1] = 0.0264988;
  fNonLinearityParams[2] = 0.965663;
  fNonLinearityParams[3] = -187.501;
  fNonLinearityParams[4] = 2762.51;
  nonlinE /= ( 1.0505 * (fNonLinearityParams[0] + fNonLinearityParams[1] * TMath::Log(nonlinE) ) / ( 1 + ( fNonLinearityParams[2] * TMath::Exp( ( nonlinE - fNonLinearityParams[3] ) / fNonLinearityParams[4] ) ) ) );

  return nonlinE;
}

Float_t Get_Purity_ErrFunction(Float_t pT_GeV, std::string deviation = "") {

  Float_t purity_val = 0;

  Float_t par[3] = {0.5,
		    9.13,
		    11.3};

  if (strcmp(deviation.data(),"Nonlin")==0){
    par[0] = 0.48;
    par[1] = 6.07;
    par[2] = 18.0;
  }

  if (strcmp(deviation.data(),"PlusNL")==0){
    par[0] = 0.56;
    par[1] = 5.45;
    par[2] = 19.9;
  }

  if (strcmp(deviation.data(),"MinusNL")==0){
    par[0] = 0.39;
    par[1] = 7.00;
    par[2] = 15.3;
  }

  if (strcmp(deviation.data(),"Plus")==0){
    par[0] = 0.59;
    par[1] = 8.29;
    par[2] = 13.2;
  }

  if (strcmp(deviation.data(),"Minus")==0){
    par[0] = 0.42;
    par[1] = 9.98;
    par[2] = 9.58;
  }

  if (strcmp(deviation.data(),"PlusAntiIso")==0){
    par[0] = 0.54;
    par[1] = 8.85;
    par[2] = 12.2;
  }

  if (strcmp(deviation.data(),"MinusAntiIso")==0){
    par[0] = 0.45;
    par[1] = 9.10;
    par[2] = 10.8;
  }

  if (strcmp(deviation.data(),"PlusNoSig")==0){
    par[0] = 0.55;
    par[1] = 8.44;
    par[2] = 12.6;
  }

  if (strcmp(deviation.data(),"MinusNoSig")==0){
    par[0] = 0.44;
    par[1] = 9.52;
    par[2] = 10.4;
  }

  if (strcmp(deviation.data(),"ssc0.26")==0){
    par[0] = 0.54;
    par[1] = 8.81;
    par[2] = 12.8;
  }

  if (strcmp(deviation.data(),"ssc0.28")==0){
    par[0] = 0.53;
    par[1] = 8.57;
    par[2] = 13.1;
  }

  if (strcmp(deviation.data(),"ssc0.33")==0){
    par[0] = 0.46;
    par[1] = 8.53;
    par[2] = 11.2;
  }

  if (strcmp(deviation.data(),"ssc0.35")==0){
    par[0] = 0.44;
    par[1] = 8.19;
    par[2] = 11.5;
  }
  
  
  purity_val = par[0]*TMath::Erf((pT_GeV-par[1])/par[2]);
  return purity_val;
}

Float_t getEtaCorrectionFactor(Float_t eta){
  
  if(eta < -0.7)
    return 1.0;
  if(eta >= -0.7 && eta < -0.6)
    return 1.14143;
  if(eta >= -0.6 && eta < -0.5)
    return 1.02541;
  if(eta >= -0.5 && eta < -0.4)
    return 1.23073;
  if(eta >= -0.4 && eta < -0.3)
    return 1.17069;
  if(eta >= -0.3 && eta < -0.2)
    return 1.44901;
  if(eta >= -0.2 && eta < -0.1)
    return 1.56182;
  if(eta >= -0.1 && eta < 0.0)
    return 1.25436;
  if(eta >= 0.0 && eta < 0.1)
    return 1.29079;
  if(eta >= 0.1 && eta < 0.2)
    return 1.41145;
  if(eta >= 0.2 && eta < 0.3)
    return 1.50102;
  if(eta >= 0.3 && eta < 0.4)
    return 1.46317;
  if(eta >= 0.4 && eta < 0.5)
    return 1.21436;
  if(eta >= 0.5 && eta < 0.6)
    return 0.975816;
  if(eta >= 0.6 && eta < 0.7)
    return 1.30083;
  if(eta >= 0.7)
    return 1.0;

  return 1.0;
  
    
}

Float_t getPhiCorrectionFactor(Float_t phi){

  /*if(phi < 1.32278)
    return 1.0;
  if(phi >= 1.32278 && phi < 1.48812)
    return 1.56905;
  if(phi >= 1.48812 & phi < 1.65347)
    return 1.34236;
  if(phi >= 1.65347 & phi < 1.81882)
    return 1.29744;
  if(phi >= 1.81882 & phi < 1.98416)
    return 1.30586;
  if(phi >= 1.98416 & phi < 2.14951)
    return 1.0;
  if(phi >= 2.14951 & phi < 2.31486)
    return 1.21982;
  if(phi >= 2.31486 & phi < 2.4802)
    return 1.37498;
  if(phi >= 2.4802 & phi < 2.64555)
    return 1.21487;
  if(phi >= 2.64555 & phi < 2.8109)
    return 1.20486;
  if(phi >= 2.8109 & phi < 2.97625)
    return 1.29372;
  if(phi >= 2.97625 & phi < 3.14159)
    return 1.49495;
  if(phi >= 3.14159)
  return 1.0;//*/

  if(phi < 1.32278)
    return 1.0;
  if(phi >= 1.32278 && phi < 1.65347)
    return 1.2443;
  if(phi >= 1.65347 && phi < 1.98416)
    return 1.15602;
  if(phi >= 1.98416 && phi < 2.31486)
    return 1.0;
  if(phi >= 2.31486 && phi < 2.64555)
    return 1.13288;
  if(phi >= 2.64555 && phi < 2.97625)
    return 1.1135;
  if(phi >= 2.97625 && phi < 3.30694)
    return 1.32679;
  if(phi >= 3.30694)
    return 1.0;
  
  return 1.0;
      
}

void Run(ULong64_t TriggerBit, TString address, Long64_t firstEvent = 0, Long64_t lastEvent = 1000000000000000){

  gStyle->SetOptStat(0);

  //SetAtlasStyle();
  TString filename = address(address.Last('/')+1,address.Last('.')-address.Last('/')-1);
  TFile* f;
  f = TFile::Open(Form("/project/projectdirs/alice/NTuples/%s",address.Data()),"READ");

  cout << Form("/project/projectdirs/alice/NTuples/%s",address.Data()) << endl;
  if(!f){
      printf("Error: cannot open ntuple.root");
      return;
  }
  TTree* _tree_event;
  _tree_event = (TTree*)f->Get("AliAnalysisTaskNTGJ/_tree_event");
  if(!_tree_event) _tree_event = (TTree*)f->Get("AliAnalysisTaskNTGJ_rpa/_tree_event");
  if(!_tree_event) _tree_event = (TTree*)f->Get("_tree_event");
  if(!_tree_event){ printf("Error: cannot find tree"); return;}
  
  const Int_t kMax = 5000;
  
  Double_t primary_vertex[3];
  Bool_t is_pileup_from_spd_5_08;
  Bool_t is_pileup_from_spd_3_08;
  Bool_t is_incomplete_daq;
  Float_t ue_estimate_its_const;
  Float_t ue_estimate_its_const_se;
  int npileup_vertex_spd;
  int run_number;
  unsigned int ntrack;
  Float_t multiplicity_v0[64];

  UInt_t ncluster;
  Float_t cluster_e[kMax];
  Float_t cluster_pt[kMax];
  Float_t cluster_eta[kMax];
  Float_t cluster_phi[kMax];
  Float_t cluster_e_nonLinCorr[kMax];
  Float_t cluster_pt_nonLinCorr[kMax];
  Float_t cluster_eta_nonLinCorr[kMax];
  Float_t cluster_phi_nonLinCorr[kMax];
  Float_t cluster_tof[kMax];
  Float_t cluster_e_cross[kMax];
  Float_t cluster_e_max[kMax];
  Float_t cluster_iso_tpc_04[kMax];
  Float_t cluster_iso_its_04[kMax];
  Float_t cluster_iso_its_04_ue[kMax];
  Float_t cluster_iso_04_truth[kMax];
  Float_t cluster_frixione_tpc_04_02[kMax];
  Float_t cluster_frixione_its_04_02[kMax];
  Float_t cluster_s_nphoton[kMax][4];
  UChar_t cluster_nlocal_maxima[kMax];
  Float_t cluster_distance_to_bad_channel[kMax];
  
  unsigned short cluster_mc_truth_index[kMax][32];
  Int_t cluster_ncell[kMax];
  UShort_t  cluster_cell_id_max[kMax];
  Float_t cluster_lambda_square[kMax][2];
  Float_t cell_e[17664];
    
  char track_charge[kMax];//
  unsigned short track_mc_truth_index[kMax];//
  unsigned char track_quality[kMax];//
  ULong64_t trigger_mask[2];
  
  _tree_event->SetBranchAddress("primary_vertex", primary_vertex);
  _tree_event->SetBranchAddress("is_pileup_from_spd_5_08", &is_pileup_from_spd_5_08);
  _tree_event->SetBranchAddress("is_pileup_from_spd_3_08", &is_pileup_from_spd_3_08);
  //_tree_event->SetBranchAddress("is_incomplete_daq", &is_incomplete_daq);
  _tree_event->SetBranchAddress("ue_estimate_its_const", &ue_estimate_its_const);
  _tree_event->SetBranchAddress("ue_estimate_its_const_se", &ue_estimate_its_const_se);
  _tree_event->SetBranchAddress("run_number", &run_number);
  _tree_event->SetBranchAddress("npileup_vertex_spd", &npileup_vertex_spd);
  _tree_event->SetBranchAddress("trigger_mask", trigger_mask);
  _tree_event->SetBranchAddress("ntrack", &ntrack);
  _tree_event->SetBranchAddress("multiplicity_v0", multiplicity_v0);

  _tree_event->SetBranchAddress("ncluster", &ncluster);
  _tree_event->SetBranchAddress("cluster_e", cluster_e);
  _tree_event->SetBranchAddress("cluster_pt", cluster_pt); // here
  _tree_event->SetBranchAddress("cluster_eta", cluster_eta);
  _tree_event->SetBranchAddress("cluster_phi", cluster_phi);
  _tree_event->SetBranchAddress("cluster_e_nonLinCorr", cluster_e_nonLinCorr);
  _tree_event->SetBranchAddress("cluster_pt_nonLinCorr", cluster_pt_nonLinCorr); // here
  _tree_event->SetBranchAddress("cluster_eta_nonLinCorr", cluster_eta_nonLinCorr);
  _tree_event->SetBranchAddress("cluster_phi_nonLinCorr", cluster_phi_nonLinCorr);
  _tree_event->SetBranchAddress("cluster_tof", cluster_tof);
  _tree_event->SetBranchAddress("cluster_e_cross", cluster_e_cross);
  _tree_event->SetBranchAddress("cluster_e_max", cluster_e_max);
  _tree_event->SetBranchAddress("cluster_s_nphoton", cluster_s_nphoton); // here
  _tree_event->SetBranchAddress("cluster_mc_truth_index", cluster_mc_truth_index);
  _tree_event->SetBranchAddress("cluster_lambda_square", cluster_lambda_square);
  _tree_event->SetBranchAddress("cluster_iso_tpc_04",cluster_iso_tpc_04);
  _tree_event->SetBranchAddress("cluster_iso_its_04",cluster_iso_its_04);
  _tree_event->SetBranchAddress("cluster_iso_its_04_ue",cluster_iso_its_04_ue);
  _tree_event->SetBranchAddress("cluster_iso_04_truth", cluster_iso_04_truth);
  _tree_event->SetBranchAddress("cluster_frixione_tpc_04_02",cluster_frixione_tpc_04_02);
  _tree_event->SetBranchAddress("cluster_frixione_its_04_02",cluster_frixione_its_04_02);
  _tree_event->SetBranchAddress("cluster_nlocal_maxima", cluster_nlocal_maxima);        
  _tree_event->SetBranchAddress("cluster_distance_to_bad_channel", cluster_distance_to_bad_channel);
  _tree_event->SetBranchAddress("cluster_ncell", cluster_ncell);
  _tree_event->SetBranchAddress("cluster_cell_id_max", cluster_cell_id_max);
  _tree_event->SetBranchAddress("cell_e", cell_e);
  
  const int nbinseta = 18;
  Double_t etabins[nbinseta+1] = {};
  double etamin = -0.9;
  double etamax = 0.9;
  double etastep = (etamax-etamin)/nbinseta;
  for(int i=0; i<nbinseta+1; i++){
    etabins[i] = etamin + i*etastep;
  }

  const int nbinsphi = 76;
  Double_t phibins[nbinsphi+1] = {};
  double phimin = -2.0*TMath::Pi();
  double phimax = 2.0*TMath::Pi();
  double phistep = (phimax-phimin)/nbinsphi;
  for(int i=0; i<nbinsphi+1; i++){
    phibins[i] = phimin + i*phistep;
  }
  



  auto hITSclus = new TH1F("hITSclus", "", 7, -0.5, 6.5);
  auto hITSclus_fake = new TH1F("hITSclus_fake", "", 7, -0.5, 6.5);

  auto hIso_ITS = new TH1F("hIso_ITS","", 25, -10, 40);
  auto hIso_ITSue = new TH1F("hIso_ITSue","", 25, -10, 40);  
  
  auto hTrackCut = new TH1F("hTrackCut", "", 15, -0.5, 14.5);
  auto hNumTracks = new TH1F("hNumTracks", "", 500, -0.5, 499.5);
  auto hEventCounts = new TH1F("hEventCounts","", 10, -0.5, 9.5);
  auto hEventCounts_DG2 = new TH1F("hEventCounts_DG2","", 10, -0.5, 9.5);
  auto hEventCounts_EG2 = new TH1F("hEventCounts_EG2","", 10, -0.5, 9.5);
  auto hZvertex = new TH1F("hZvertez", "", 60, -30, 30);
  auto hZvertexAfter = new TH1F("hZvertezAfter", "", 60, -30, 30);
  auto hHitsITS = new TH1F("hHitsITS", "", 10, -0.5, 9.5);
  auto hEventCut = new TH1F("hEventCut", "", 10, -0.5, 9.5);
  auto hEventCut_MB = new TH1F("hEventCut_MB", "", 10, -0.5, 9.5);
  auto hEventCut_DG2 = new TH1F("hEventCut_DG2", "", 10, -0.5, 9.5);
  auto hEventCut_EG2 = new TH1F("hEventCut_EG2", "", 10, -0.5, 9.5);
  auto hEventCut_EG2cent = new TH1F("hEventCut_EG2cent", "", 10, -0.5, 9.5);
  auto hClusterCut = new TH1F("hClusterCut", "", 20, -0.5, 19.5);
  auto hClusterCutFlow = new TH1F("hClusterCutFlow", "", 20, -0.5, 19.5);
  auto hPileUpVertex = new TH1F("hPileUpVertex", "", 20, -0.5, 19.5);
  auto hMultiplicityBefore = new TH1F("hMultiplicityBefore", "", 200, 0, 200);
  auto hMultiplicityAfter = new TH1F("hMultiplicityAfter", "", 200, 0, 200);
  auto hUE = new TH1F("hUE", "", 500 , -250, 250);
  auto hUEse = new TH1F("hUEse", "", 500 , -250, 250);

  hZvertex->Sumw2();
  hZvertexAfter->Sumw2();
  hHitsITS->SetTitle(";Layers hit; counts");
  
  //Photon
  const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning
  
  auto hReco_pt  = new TH1F("hReco_pt","", nbinscluster, clusterbins);
  auto hCluster_pt = new TH1F("hCluster_pt", "", nbinscluster, clusterbins);
  auto hDG2_caloE = new TH1F("hDG2_caloE", "", nbinscluster, clusterbins);
  auto hDG2_centE = new TH1F("hDG2_centE", "", nbinscluster, clusterbins);
  auto hEG2_caloE = new TH1F("hEG2_caloE", "", nbinscluster, clusterbins);
  auto hEG2wEtaCorr = new TH1F("hEG2wEtaCorr", "", nbinscluster, clusterbins);
  auto hEG2wPhiCorr = new TH1F("hEG2wPhiCorr", "", nbinscluster, clusterbins);
  auto hEG2woPurity = new TH1F("hEG2woPurity", "", nbinscluster, clusterbins);
  auto hEG2woPurity_nonlin = new TH1F("hEG2woPurity_nonlin", "", nbinscluster, clusterbins);
  auto hEG2_centE = new TH1F("hEG2_centE", "", nbinscluster, clusterbins);
  auto hMB_centE = new TH1F("hMB_centE", "",  nbinscluster, clusterbins);
  
  hReco_pt->Sumw2();
  hCluster_pt->Sumw2();
  hDG2_caloE->Sumw2();  
  hEG2_caloE->Sumw2();
  hEG2woPurity->Sumw2();
  hEG2woPurity_nonlin->Sumw2();  
  hDG2_centE->Sumw2();  
  hEG2_centE->Sumw2();
  hMB_centE->Sumw2();
    
  hCluster_pt->SetTitle("; E_{T} (GeV/c) ; 1/N_{ev}dN/dE_{T}");
  hReco_pt->SetTitle("; E_{T} (GeV/c) ; 1/N_{ev}dN/dE_{T}");
  hMB_centE->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{MB}dN/dE_{T}");
  hDG2_caloE->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{DG2}dN/dE_{T}");
  hEG2_caloE->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG2}dN/dE_{T}");
  hEG2woPurity->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG2}dN/dE_{T}");
  hEG2woPurity_nonlin->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG2}dN/dE_{T}");
  hDG2_centE->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{DG2}dN/dE_{T}");
  hEG2_centE->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG2}dN/dE_{T}");

  //cut flow check histograms
  auto h_YesISO = new TH1F("h_YesISO", "", nbinscluster, clusterbins);
  auto h_NoISO = new TH1F("h_NoISO", "", nbinscluster, clusterbins);
  auto h_YesSSC = new TH1F("h_YesSSC", "", nbinscluster, clusterbins);
  auto h_NoSSC = new TH1F("h_NoSSC", "", nbinscluster, clusterbins);
  auto h_YesTOF = new TH1F("h_YesTOF", "", nbinscluster, clusterbins);
  auto h_NoTOF = new TH1F("h_NoTOF", "", nbinscluster, clusterbins);
  
  h_YesISO->Sumw2();
  h_NoISO->Sumw2();
  h_YesSSC->Sumw2();
  h_NoSSC->Sumw2();
  h_YesTOF->Sumw2();
  h_NoTOF->Sumw2();

  h_YesISO->SetTitle(";p_{T}^{Reco,pt} [GeV/c];  dN/dp_{T}");
  h_NoISO->SetTitle(";p_{T}^{Reco,pt} [GeV/c];  dN/dp_{T}");
  h_YesSSC->SetTitle(";p_{T}^{Reco,pt} [GeV/c];  dN/dp_{T}");
  h_NoSSC->SetTitle(";p_{T}^{Reco,pt} [GeV/c];  dN/dp_{T}");
  h_YesTOF->SetTitle(";p_{T}^{Reco,pt} [GeV/c];  dN/dp_{T}");
  h_NoTOF->SetTitle(";p_{T}^{Reco,pt} [GeV/c];  dN/dp_{T}");

  //cluster cuts histogram
  auto hCluster_tof = new TH1F("hCluster_tof", "", 200, -100, 100);
  auto hCluster_tofB = new TH1F("hCluster_tofB", "", 200, -100, 100);
  auto hCluster_tofA = new TH1F("hCluster_tofA", "", 200, -100, 100);
  auto hCluster_tof20GeV = new TH1F("hCluster_tof20GeV", "", 200, -100, 100);
  auto hExoticity = new TH1F("hExtoticity", "", 100, 0, 1);
  auto hCellEvClusterE = new TH1F("hCellEvClusterE", "", 100, -50, 50);
  auto hNcell = new TH1F("hNcell", "", 20, 0, 20);
  auto hNLM = new TH1F("hNLM", "", 10, 0, 10);
  auto hD2BC = new TH1F("hD2BC", "", 10, 0, 10);
  auto hEta = new TH1F("hEta", "", nbinseta, etabins);
  auto hPhi = new TH1F("hPhi", "", nbinsphi, phibins);
  auto hEtaPhi = new TH2F("hEtaPhi", ";#eta; #varphi", nbinseta, etabins, nbinsphi, phibins); 
  auto hEtawEtaCorr = new TH1F("hEtawEtaCorr", "", nbinseta, etabins);
  auto hPhiwEtaCorr = new TH1F("hPhiwEtaCorr", "", nbinsphi, phibins);
  auto hEtaPhiwEtaCorr = new TH2F("hEtaPhiCorr", ";#varphi; #eta", nbinsphi, phibins, nbinseta, etabins); 

  hCluster_tof->SetTitle(";cluster_tof [ns]; counts");
  hCluster_tofB->SetTitle(";cluster_tof [ns]; counts");
  hCluster_tofA->SetTitle(";cluster_tof [ns]; counts");
  hCluster_tof20GeV->SetTitle("photons > 20 GeV;cluster_tof [ns]; counts");
  hExoticity->SetTitle(";E_{cross}/E_{max};counts");
  hCellEvClusterE->SetTitle(";E_{max} - E_{cluster};counts");
  hNcell->SetTitle(";N_{cell};counts");
  hNLM->SetTitle(";NLM;counts");
  hD2BC->SetTitle(";Distance to bad channel; counts");
  hEta->SetTitle(";#eta; counts");
  hPhi->SetTitle(";#phi; counts");

  
  int nevent = 0; 
  int numEvents_tracks = 0;
  int numClustersPost = 0;
  int numClustersPre = 0;
  int numEvents_tot = 0;
  int numEvents_passTrig = 0;
  int numEvents_passAll = 0;
  int numEvents_MBcent = 0;
  int numEvents_DG2cent = 0;
  int numEvents_EG2cent = 0;
  int numEvents_DG2calo = 0;
  int numEvents_EG2calo = 0;
  int numEvents_MBcent_before = 0;
  int numEvents_DG2cent_before = 0;
  int numEvents_EG2cent_before = 0;
  int numEvents_DG2calo_before = 0;
  int numEvents_EG2calo_before = 0;
  int numEvents_Zmore10 = 0;
  int numEvents_Zless10 = 0;
  int numEvents_noZ = 0;
  int numClusters_clusterpt = 0;
  int numClusters_EG2_caloE = 0;
  int numClusters_EG2_centE = 0;
  int numEvents_pass12GeVPhoton = 0;
 
  double maxEta = 0.4;
  
  const ULong64_t one1 = 1;
  const int numTrigs = 5; 
  /*//////////////////////////////////////////////////////////////////////////////////
    17q triggers
 //////////////////////////////////////////////////////////////////////////////////*/
  ULong64_t trigMask_17q_trigs1[numTrigs] = {0};//0 = MB, 1 = DG2, 2 = EG2
  trigMask_17q_trigs1[1] = (one1 << 30);//DG2 calo
  trigMask_17q_trigs1[2] = (one1 << 27);//EG2 calo

  ULong64_t trigMask_17q_trigs2[numTrigs] = {0};//0 = MB, 1 = DG2, 2 = EG2
  trigMask_17q_trigs2[1] = (one1 << 26);//DG2 calo
  trigMask_17q_trigs2[2] = (one1 << 23);//EG2 calo

  ULong64_t trigMask_17q_trigs3[numTrigs] = {0};//0 = MB, 1 = DG2, 2 = EG2
  trigMask_17q_trigs3[0] = (one1 << 0) | (one1 << 3);//fast and cent cint7
  trigMask_17q_trigs3[1] = (one1 << (13));//cent DG2
  trigMask_17q_trigs3[2] = (one1 << (10));//cent EG2
  trigMask_17q_trigs3[3] = (one1 << (57-50));//calo DG2
  trigMask_17q_trigs3[4] = (one1 << (54-50));//calo EG2
  
  ULong64_t trigMask[numTrigs] = {0};

  Long64_t totEvents = _tree_event->GetEntries();
  numEvents_tot = totEvents;
  Long64_t restrictEvents = lastEvent;
  Long64_t numEntries = TMath::Min(totEvents,restrictEvents);
  std::cout << numEntries << std::endl;
  for (Long64_t ievent = firstEvent; ievent< numEntries ;ievent++) {
    _tree_event->GetEntry(ievent);
    nevent += 1;
    if(ievent%100000==0)
      {
	std::cout << ievent << std::endl;
	cout << run_number << endl;
      }
    
    bool isMBcent, isDG2calo, isEG2calo, isEG2cent;
    isMBcent = isDG2calo = isEG2calo = isEG2cent = false;
    
    hPileUpVertex->Fill(npileup_vertex_spd);
    hEventCut->Fill(0);
    hZvertex->Fill(primary_vertex[2]);
    
    //Event Selection:        
    //if(run_number != 282440) continue;


    //17q
    if(run_number >= 282391 && run_number <= 282441)
      std::memcpy(trigMask, trigMask_17q_trigs1, sizeof(trigMask));
    if(run_number == 282415 || run_number == 282411 || run_number == 282402)
      std::memcpy(trigMask, trigMask_17q_trigs2, sizeof(trigMask));
    if(run_number == 282367 || run_number == 282366 || run_number == 282365)//EMC good runs 
      std::memcpy(trigMask, trigMask_17q_trigs3, sizeof(trigMask));
    
    
    
    ULong64_t localTrigBit = 0;
   
    
    if(run_number == 282367 || run_number == 282366 || run_number == 282365){
      if(not ((trigMask[0] & trigger_mask[0]) == 0)){//MB selection
	localTrigBit |= (1 << 0);
      }
      if(not ((trigMask[4] & trigger_mask[1]) == 0)){//EG2 calo
	  localTrigBit |= (1 << 2); 
      }
    }
    else{
      if(not ((trigMask[2] & trigger_mask[0]) == 0)){//EG2 calo
	localTrigBit |= (1 << 2); 
      }
    }

    
    //The trigger bit options. Most of 17q have min bias
    //001 = 1 = MB
    //010 = 2 = DG2
    //100 = 4 = EG2
    //110 = 6 = DG2||EG2
    //111 = 7 = MB||DG2||EG2
    if((localTrigBit & 1) != 0) {isMBcent = true; hEventCut_MB->Fill(0);numEvents_MBcent_before++;}
    if(((localTrigBit & 4) != 0) && (!isMBcent)) {isEG2calo = true;hEventCut_EG2->Fill(0);numEvents_EG2calo_before++;}
    
    
    //if((localTrigBit & TriggerBit) == 0) {
    if(localTrigBit != TriggerBit) {
      hEventCut->Fill(1);
      if(isEG2calo) hEventCut_EG2->Fill(1);
      continue;}//no emcal triggers*/

    if((localTrigBit & TriggerBit) != 0) {
      numEvents_passTrig++;
    }
    
    if(not( TMath::Abs(primary_vertex[2])<10.0)){
      hEventCut->Fill(2);
      if(isEG2calo) hEventCut_EG2->Fill(2);      
      numEvents_Zmore10++;
      continue;} //vertex z position
    
    if(primary_vertex[2] == 0.0000) {
      hEventCut->Fill(3);
      if(isEG2calo) hEventCut_EG2->Fill(3);
      numEvents_noZ++;
      continue;}//removes no vertex found
    
    if(is_pileup_from_spd_5_08) {
      hEventCut->Fill(4);
      if(isEG2calo) hEventCut_EG2->Fill(4);
      continue;} //removes pileup*/
    
    hEventCut->Fill(6);//all cuts
    if(isEG2calo) {hEventCut_EG2->Fill(6); numEvents_EG2calo++;}
    if(!isEG2calo) continue;
    
    hZvertexAfter->Fill(primary_vertex[2]);
    numEvents_Zless10++;
    numEvents_passAll++;

    Long64_t currentEvent = -1;
    //continue;
    int eventFill = 0;    
    hEventCounts->Fill(eventFill);
    hUE->Fill(ue_estimate_its_const);
    hUEse->Fill(ue_estimate_its_const_se);

    //Loop over clusters
    for(ULong64_t n=0; n< ncluster; n++)
      {
	hIso_ITS->Fill(cluster_iso_its_04[n]);
	hIso_ITSue->Fill(cluster_iso_its_04_ue[n]);
	
	
	double isolation = cluster_iso_its_04[n] + cluster_iso_its_04_ue[n];             //remove UE subtraction
	isolation = isolation - ue_estimate_its_const*0.4*0.4*TMath::Pi();               //Use rhoxA subtraction

	Float_t clusterPt = 0.0;
	Float_t clusterE = 0.0;
	Float_t clusterEta = 0.0;
	Float_t clusterPhi = 0.0;
	
	clusterPt = cluster_pt[n];
	clusterE = cluster_e[n];
	clusterEta = cluster_eta[n];
	clusterPhi = cluster_phi[n];
		
	//Photon Selection
	/*////////////////////////////////////////
	  Bit  Cut
	  0    ncell>=2
	  1    exoticity>0.05
	  2    nlocalmaxima<=2
	  3    dist2badchn >= 1
	  4    |tof| < 20 ns
	  5    isoation: E < 1.5 GeV r = 0.4
	  6    shower shape cut: 0.1 < lambda < 0.3
	  7    |eta| < 0.667
	  8    1.396 < phi < 3.28
	////////////////////////////////////////*/

	if(clusterPt > 20)
	  hCluster_tof20GeV->Fill(cluster_tof[n]);
	
	if((isolation < 1.5)) h_YesISO->Fill(clusterPt);
	h_NoISO->Fill(clusterPt);
	
	int numCuts = 9;

	ULong64_t clusterCutBits = 0;
	ULong64_t clusterCutPassed = 0;
	
	numClustersPre++;	
	hClusterCut->Fill(0);
	hClusterCutFlow->Fill(0);

	if(cluster_pt[n] >= 12 && currentEvent == -1){
	  currentEvent = ievent;
	  numEvents_pass12GeVPhoton++;
	}
	//if(clusterPt > 12)
	  {
	    
	    hCellEvClusterE->Fill(cluster_e_max[n]-clusterE);
	  }
	
	if(not (cluster_ncell[n]>=2)) continue;
	if(not (cluster_e_cross[n]/cluster_e_max[n]>0.05)) continue;
	if(not (cluster_nlocal_maxima[n]<= 2)) continue;
	if(not (cluster_distance_to_bad_channel[n]>=1))continue;
	if(not ((cluster_tof[n] > -20) && (cluster_tof[n] < 20))) continue;
	
	//acceptance cuts
	//if(not (TMath::Abs(cluster_eta[n]) < 0.4)) continue;
	if(not (TMath::Abs(cluster_eta[n]) < 0.67)) continue;
	if(not (1.396 < cluster_phi[n] && cluster_phi[n] < 3.28)) continue;
	
	//shower shape and isolation
	if(not (( 0.1 < cluster_lambda_square[n][0]) &&  ( 0.3 > cluster_lambda_square[n][0]))) continue;
	if(not (isolation < 1.5)) continue;

	if(clusterPt >= 12){
	  hNcell->Fill(cluster_ncell[n]);
	  hExoticity->Fill(cluster_e_cross[n]/cluster_e_max[n]);
	  hNLM->Fill(cluster_nlocal_maxima[n]);
	  hD2BC->Fill(cluster_distance_to_bad_channel[n]);
	  hCluster_tof->Fill(cluster_tof[n]);
	  hEta->Fill(clusterEta);
	  hPhi->Fill(clusterPhi);
	  hEtaPhi->Fill(clusterEta, clusterPhi);
	}

	if(ievent%1000==0)
	  {
	    std::cout << "cluster accepted" << std::endl;
	    
	  }
	

	hClusterCut->Fill(10);
	hClusterCutFlow->Fill(10);
	numClustersPost++;

	double purity = Get_Purity_ErrFunction(clusterPt, "Nonlin");
	Float_t nonlinEnergy= GetNonLinearityEnergy(clusterPt);
	double etaFactor = getEtaCorrectionFactor(clusterEta);
	double phiFactor = getPhiCorrectionFactor(clusterPhi);
	double weight = purity*phiFactor;

	if(clusterPt >= 12){
	  hEtawEtaCorr->Fill(clusterEta, etaFactor);
	  hPhiwEtaCorr->Fill(clusterPhi, etaFactor);
	  hEtaPhiwEtaCorr->Fill(clusterEta, clusterPhi, etaFactor);
	}
	
	hReco_pt->Fill(clusterPt);
	
	if(isEG2calo) {
	  numClusters_EG2_caloE++;
	  hEG2_caloE->Fill(clusterPt, weight);
	  hEG2woPurity->Fill(clusterPt, 1);
	  hEG2wEtaCorr->Fill(clusterPt, etaFactor*purity);
	  hEG2wPhiCorr->Fill(clusterPt, phiFactor*purity);
	  hEG2woPurity_nonlin->Fill(nonlinEnergy, 1);
	}
	hCluster_pt->Fill(clusterPt,purity);
	numClusters_clusterpt++;
      }
    
    
  }//loop over events
  std::cout << " END LOOP  " << std::endl;
  cout << "total events: " << numEvents_tot << endl;
  cout << "total/minbias/DG2/EG2calo/EG2cent events:" << endl;
  cout << "before:" << "\t" << numEvents_passTrig << "\t" << numEvents_MBcent_before << "\t" << numEvents_DG2calo_before << "\t" << numEvents_EG2calo_before << "\t" << numEvents_EG2cent_before << endl;
  cout << "after:" << "\t"  << numEvents_passAll << "\t" << numEvents_MBcent << "\t" << numEvents_DG2calo << "\t" << numEvents_EG2calo << "\t" << numEvents_EG2cent << endl;  
  cout << "cluster pt clusters: " << numClusters_clusterpt << "\tEG2_caloE clusters: " << numClusters_EG2_caloE << "\tEG2_centE clusters: " << numClusters_EG2_centE << endl;

  cout << "\tTotal Events: " << numEntries << "\tEvent selection: " << numEvents_passAll << "\tPre-Cluster selection: " << numClustersPre << "\tPostCluster selection: " << numClustersPost << endl;
  
  //Normalizing the bins and getting yaxsis to be 1/Nevt*dN/dptdeta
  const double deltaEta = 1.334;
  const double deltaPhi = 1.884;
  
  auto normalizer = new TH1D("normalizer", "normalizer", 20, -0.5, 19.5);
  normalizer->SetBinContent(1, deltaEta);
  normalizer->SetBinContent(2, deltaPhi);
  normalizer->SetBinContent(3, numEvents_tot);
  normalizer->SetBinContent(4, numEvents_passTrig);
  normalizer->SetBinContent(5, numEvents_passAll);
  normalizer->SetBinContent(6, numEvents_MBcent_before);
  normalizer->SetBinContent(7, numEvents_DG2calo_before);
  normalizer->SetBinContent(8, numEvents_EG2calo_before);
  normalizer->SetBinContent(9, numEvents_MBcent);
  normalizer->SetBinContent(10, numEvents_DG2calo);
  normalizer->SetBinContent(11, numEvents_EG2calo);
  normalizer->SetBinContent(12, numEvents_Zmore10);
  normalizer->SetBinContent(13, numEvents_noZ);
  normalizer->SetBinContent(14, numEvents_EG2cent_before);
  normalizer->SetBinContent(15, numEvents_EG2cent);
  normalizer->SetBinContent(16, numClusters_EG2_caloE);  
  normalizer->SetBinContent(17, numClusters_EG2_centE);
  normalizer->SetBinContent(18, numEvents_pass12GeVPhoton);
  
  normalizer->GetXaxis()->SetBinLabel(1,"deltaEta");
  normalizer->GetXaxis()->SetBinLabel(2,"deltaPhi");
  normalizer->GetXaxis()->SetBinLabel(3,"numEvents_tot");
  normalizer->GetXaxis()->SetBinLabel(4,"numEvents_passTrig");
  normalizer->GetXaxis()->SetBinLabel(5,"numEvents_passAll");
  normalizer->GetXaxis()->SetBinLabel(6,"numEvents_MBcent_before");
  normalizer->GetXaxis()->SetBinLabel(7,"numEvents_DG2calo_before");
  normalizer->GetXaxis()->SetBinLabel(8,"numEvents_EG2calo_before");
  normalizer->GetXaxis()->SetBinLabel(9,"numEvents_MBcent");
  normalizer->GetXaxis()->SetBinLabel(10,"numEvents_DG2calo");
  normalizer->GetXaxis()->SetBinLabel(11,"numEvents_EG2calo");
  normalizer->GetXaxis()->SetBinLabel(12,"numEvents_Zmore10");
  normalizer->GetXaxis()->SetBinLabel(13,"numEvents_noZ");
  normalizer->GetXaxis()->SetBinLabel(14,"numEvents_EG2cent_before");
  normalizer->GetXaxis()->SetBinLabel(15,"numEvents_EG2cent");
  normalizer->GetXaxis()->SetBinLabel(16,"numCluster_EG2calo");
  normalizer->GetXaxis()->SetBinLabel(17,"numCluster_EG2cent");  
  normalizer->GetXaxis()->SetBinLabel(18, "numEvents_pass12GeVPhoton");
   
  hClusterCut->GetXaxis()->SetBinLabel(1,"All clusters");
  hClusterCut->GetXaxis()->SetBinLabel(2,"ncell");
  hClusterCut->GetXaxis()->SetBinLabel(3,"exoticity");
  hClusterCut->GetXaxis()->SetBinLabel(4,"num local maxima");
  hClusterCut->GetXaxis()->SetBinLabel(5,"dist 2 bad chn");
  hClusterCut->GetXaxis()->SetBinLabel(6,"tof");
  hClusterCut->GetXaxis()->SetBinLabel(7,"isolation");
  hClusterCut->GetXaxis()->SetBinLabel(8,"shower shape");
  hClusterCut->GetXaxis()->SetBinLabel(9,"eta acceptance");
  hClusterCut->GetXaxis()->SetBinLabel(10,"phi aceptance");
  hClusterCut->GetXaxis()->SetBinLabel(11,"accepted clusters");

  hClusterCutFlow->GetXaxis()->SetBinLabel(1,"All clusters");
  hClusterCutFlow->GetXaxis()->SetBinLabel(2,"ncell");
  hClusterCutFlow->GetXaxis()->SetBinLabel(3,"exoticity");
  hClusterCutFlow->GetXaxis()->SetBinLabel(4,"num local maxima");
  hClusterCutFlow->GetXaxis()->SetBinLabel(5,"dist 2 bad chn");
  hClusterCutFlow->GetXaxis()->SetBinLabel(6,"tof");
  hClusterCutFlow->GetXaxis()->SetBinLabel(7,"isolation");
  hClusterCutFlow->GetXaxis()->SetBinLabel(8,"shower shape");
  hClusterCutFlow->GetXaxis()->SetBinLabel(9,"eta acceptance");
  hClusterCutFlow->GetXaxis()->SetBinLabel(10,"phi aceptance");
  hClusterCutFlow->GetXaxis()->SetBinLabel(11,"accepted clusters");

  hEventCut->GetXaxis()->SetBinLabel(1,"All events");
  hEventCut->GetXaxis()->SetBinLabel(2,"no EMCA/MB trigger");
  hEventCut->GetXaxis()->SetBinLabel(3,"primary vertex > 10");
  hEventCut->GetXaxis()->SetBinLabel(4,"primary vertex = 0");
  hEventCut->GetXaxis()->SetBinLabel(5,"pile up");
  hEventCut->GetXaxis()->SetBinLabel(6,"ntrack < 0");
  hEventCut->GetXaxis()->SetBinLabel(7,"passed");

  hEventCut_EG2->GetXaxis()->SetBinLabel(1,"All events");
  hEventCut_EG2->GetXaxis()->SetBinLabel(2,"no EMCA/MB trigger");
  hEventCut_EG2->GetXaxis()->SetBinLabel(3,"primary vertex > 10");
  hEventCut_EG2->GetXaxis()->SetBinLabel(4,"primary vertex = 0");
  hEventCut_EG2->GetXaxis()->SetBinLabel(5,"pile up");
  hEventCut_EG2->GetXaxis()->SetBinLabel(6,"ntrack < 0");
  hEventCut_EG2->GetXaxis()->SetBinLabel(7,"passed");

  hEventCounts->GetXaxis()->SetBinLabel(1, "Passing Event Selection only");
  hEventCounts->GetXaxis()->SetBinLabel(2, "Passing Track Selection");

  //Writing to file
  filename += "_StdCuts_EX0PurityFit_wPhiCorr_noNorm";
  cout << filename << endl;
  auto fout = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_%llu_%ibins_firstEvent%lld_%s.root",TriggerBit, nbinscluster, firstEvent, filename.Data()), "RECREATE");  


  
  //writing photon info
  hCluster_pt->Write("hCluster_pt");
  hReco_pt->Write("hReco_pt");
  hEventCounts->Write("hEventCounts");
  hMB_centE->Write("hMB_centE");
  //hDG2_caloE->Write("hDG2_caloE");
  hEG2_caloE->Write("hEG2_caloE");
  hEG2wEtaCorr->Write("hEG2wEtaCorr");
  hEG2wPhiCorr->Write("hEG2wPhiCorr");
  hEG2woPurity->Write("hEG2woPurity");
  hEG2woPurity_nonlin->Write("hEG2woPurity_nonlin");
  //hEG2_centE->Write("hEG2_centE");
  normalizer->Write("hNormalizer");
  
  hZvertex->Write("hZvertex");
  hZvertexAfter->Write("hZvertexAfter");
  hPileUpVertex->Write("hPileUpVertex");
  hEventCut->Write("hEventCut");
  hEventCut_MB->Write("hEventCut_MB");
  hEventCut_DG2->Write("hEventCut_DG2");
  hEventCut_EG2->Write("hEventCut_EG2");
  hClusterCut->Write("hClusterCut");
  hClusterCutFlow->Write("hClusterCutFlow");
  hIso_ITS->Write("hIso_ITS");
  hIso_ITSue->Write("hIso_ITSue");
  hUE->Write("hUE");
  hUEse->Write("hUEse");
    
  hCluster_tof->Write("hCluster_tof");
  hCluster_tofB->Write("hCluster_tofB");
  hCluster_tofA->Write("hCluster_tofA");
  hCluster_tof20GeV->Write("hCluster_tof20GeV");
  hExoticity->Write("hExoticity");
  hCellEvClusterE->Write("hCellEvClusterE");
  hNcell->Write("hNcell");
  hNLM->Write("hNLM");
  hD2BC->Write("hD2BC");
  hEta->Write("hEta");
  hPhi->Write("hPhi");
  hEtaPhi->Write("hEtaPhi");
  hEtawEtaCorr->Write("hEtawEtaCorr");
  hPhiwEtaCorr->Write("hPhiwEtaCorr");
  hEtaPhiwEtaCorr->Write("hEtaPhiwEtaCorr");

  
  h_YesISO->Write("h_YesISO");
  h_NoISO->Write("h_NoISO");
  h_YesSSC->Write("h_YesSSC");
  h_NoSSC->Write("h_NoSSC");
  h_YesTOF->Write("h_YesTOF");
  h_NoTOF->Write("h_NoTOF");
  fout->Close();  

  return;
  
}

    
void isoPhotonAnalysisData_ppCS(){
  auto start = std::chrono::system_clock::now();
  
  //Input to Run is as follow: Run(const int TriggerBit, TString address, Long64_t firstEvent = 0, Long64_t lastEvent = 1000000000000000)
  
/////////////////////////////////////////////////////////////////*/
    //The trigger bit options. Most of 17q does not have 
    //0001 = 01 = MB
    //0010 = 02 = DG2calo
    //0100 = 04 = EG2calo
    //0110 = 06 = DG2calo || EG2calo
    //0111 = 07 = MB || DG2calo || EG2calo
    //1000 = 08 = EG2cent
    //1100 = 12 = EG2calo || EG2cent
    //1101 = 13 = MB || EG2calo || EG2cent

  //pp data sets - without NL 
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh_r282365_physel.root");
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh_r282366_physel.root");
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh_r282367_physel.root");
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part000.root");//3.3 282440
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part001.root");//25 282437
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part002.root");//21 282415
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part003.root");//2.9 282411
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part004.root");//36 282402
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part005.root");//17
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part006.root");//5.6 282398
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part007.root");//2.5 282393
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part008.root");//5.0 282392
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part009.root");//15 282391
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part010.root");//15

  //EMCal framwork, latest EMCal corrections, AliPhysics Feb 20, 2022
  //Run(4, "pp/17q/17q_run282440_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName.root");
  //Run(4, "pp/17q/17q_run282437_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part1.root");
  //Run(4, "pp/17q/17q_run282437_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part2.root");
  //Run(4, "pp/17q/17q_run282415_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part1.root");
  //Run(4, "pp/17q/17q_run282415_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part2.root");
  //Run(4, "pp/17q/17q_run282411_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName.root");
  //Run(4, "pp/17q/17q_run282402_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part1.root");
  //Run(4, "pp/17q/17q_run282402_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part2.root");
  //Run(4, "pp/17q/17q_run282402_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part3.root");
  //Run(4, "pp/17q/17q_run282399_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part1.root");
  //Run(4, "pp/17q/17q_run282399_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part2.root");
  //Run(4, "pp/17q/17q_run282398_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName.root");
  //Run(4, "pp/17q/17q_run282392_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName.root");
  //Run(4, "pp/17q/17q_run282391_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part1.root");
  //Run(4, "pp/17q/17q_run282391_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part2.root");
  //Run(4, "pp/17q/17q_run282367_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part1.root");
  //Run(4, "pp/17q/17q_run282367_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part2.root");
  //Run(4, "pp/17q/17q_run282366_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part1.root");
  //Run(4, "pp/17q/17q_run282366_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part2.root");
  //Run(4, "pp/17q/17q_run282366_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part3.root");
  //Run(4, "pp/17q/17q_run282365_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part1.root");
  //Run(4, "pp/17q/17q_run282365_kMuonCalokCaloOnlykINT7_kNonLinCorr_latestEMCalCorr_rpaName_part2.root");
  
  
  //4,035,922 --> starting of EMC good runs
  //1,749,493 to 2,939,337 --> runs 282415-282402
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh.root", false, false, 0, 1749493);
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh.root", false, false, 1749493, 2939338);
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh.root", false, false, 2939338, 4035922);

  //new ntuplizer ITS only runs
  //Run(4, "pp/17q/17q_12runs_kEMCEGA_kINT7_mannualMode.root");
  //Run(4, "pp/17q/run_282440/17q_r282440_noThresh_muoncalopass1_phySel.root");
  //Run(4, "pp/17q/run_282440/17q_ITSonly_1runs_part1_kCaloOnlykINTkAny_mannualAndGreen_split10_wNL.root");
  
  //With NL dataset
  //Run(4, "pp/17q/run_282440/17q_ITSonly_1runs_part1_kMuonCalo_mannualAndGreen_split10_wNL.root");
  //Run(4, "pp/17q/17q_ITSonly_1runs_part2_kMuonCalo_mannualAndGreen_split5_wNL.root");
  //Run(4, "pp/17q/17q_ITSonly_run282402_kMuonCalo_mannualAndGreen_split5_wNL_part1.root");//1362718
  //Run(4, "pp/17q/17q_ITSonly_run282402_kMuonCalo_mannualAndGreen_split5_wNL_part2.root");//1808838
  //Run(4, "pp/17q/17q_ITSonly_run282402_kMuonCalo_mannualAndGreen_split5_wNL_part3.root");//1210443
  //Run(4, "pp/17q/17q_ITSonly_run282399_kMuonCalo_mannualAndGreen_split5_wNL.root");//1288632
  //Run(4, "pp/17q/17q_ITSonly_run282398_kMuonCalo_mannualAndGreen_split5_wNL.root");//526946
  //Run(4, "pp/17q/17q_ITSonly_run282393_kMuonCalo_mannualAndGreen_split5_wNL.root");//310278
  //Run(4, "pp/17q/17q_ITSonly_run282392_kMuonCalo_mannualAndGreen_split5_wNL.root");//490340
  //Run(4, "pp/17q/17q_ITSonly_run282391_kMuonCalo_mannualAndGreen_split5_wNL.root");//

  //Run(4, "pp/17q/17q_ITSonly_run282393_kMuonCalo_mannualAndGreen_GetMometumFixed_wNL.root");

  //Run(4, "pp/17q/17q_ITSonly_3runsPart1_kMuonCalo_kINT7_kNonLinCorr_noNLOnly.root");
  //Run(4, "pp/17q/17q_ITSonly_3runsPart1_kMuonCalo_kINT7_kNonLinCorr_noNLOnly_part2.root");
  //Run(4, "pp/17q/17q_ITSonly_3runsPart1_kMuonCalo_kINT7_kNonLinCorr_noNLOnly_part3.root");
  //Run(4, "pp/17q/17q_ITSonly_3runsPart1_kMuonCalo_kINT7_kNonLinCorr_noNLTemp_part1.root");
  //Run(4, "pp/17q/17q_ITSonly_3runsPart1_kMuonCalo_kINT7_kNonLinCorr_noNLTemp_part2.root");
  //Run(4, "pp/17q/17q_ITSonly_3runsPart2_kMuonCalo_kINT7_kNonLinCorr_noNLTemp_part1.root");
  //Run(4, "pp/17q/");
  
  
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  std::cout << "started computation at " << std::ctime(&start_time)
	    << "finished computation at " << std::ctime(&end_time)
	    << "elapsed time: " << elapsed_seconds.count() << "s\n";
  return;
}




/*///////////////////////////////////////////////////////////////
Notes:

EMCal acceptance:
-0.667 < eta < 0.667
1.396 < phi < 3.28

DCal acceptance:
-0.667 < eta < -0.2275 and 0.2275 < eta < 0.667














 *///////////////////////////////////////////////////////////////
