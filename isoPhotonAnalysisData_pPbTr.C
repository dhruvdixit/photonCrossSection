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
  if(!_tree_event) _tree_event = (TTree*)f->Get("_tree_event");
  if(!_tree_event){ printf("Error: cannot find tree"); return;}
  
  const Int_t kMax = 5000;
  
  Double_t primary_vertex[3];
  Bool_t is_pileup_from_spd_5_08;
  Bool_t is_pileup_from_spd_3_08;
  Bool_t is_incomplete_daq;
  Float_t ue_estimate_its_const;
  int npileup_vertex_spd;
  int run_number;
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

  UInt_t ntrack;
  Float_t track_pt[kMax];
  Float_t track_eta[kMax];
  Float_t track_phi[kMax];
    
  char track_charge[kMax];//
  unsigned short track_mc_truth_index[kMax];//
  unsigned char track_quality[kMax];//
  ULong64_t trigger_mask[2];

  
  _tree_event->SetBranchAddress("primary_vertex", primary_vertex);
  _tree_event->SetBranchAddress("is_pileup_from_spd_5_08", &is_pileup_from_spd_5_08);
  _tree_event->SetBranchAddress("is_pileup_from_spd_3_08", &is_pileup_from_spd_3_08);
  //_tree_event->SetBranchAddress("is_incomplete_daq", &is_incomplete_daq);
  _tree_event->SetBranchAddress("ue_estimate_its_const", &ue_estimate_its_const);
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
  
  _tree_event->SetBranchAddress("ntrack", &ntrack);
  _tree_event->SetBranchAddress("track_pt",track_pt);
  _tree_event->SetBranchAddress("track_eta",track_eta);
  _tree_event->SetBranchAddress("track_phi",track_phi);

  const int nbinseta = 10;
  Double_t etabins[nbinseta+1] = {};
  double etamin = -0.9;
  double etamax = 0.9;
  double etastep = (etamax-etamin)/nbinseta;
  for(int i=0; i<nbinseta+1; i++){
    etabins[i] = etamin + i*etastep;
  }

  const int nbinsphi = 80;
  Double_t phibins[nbinsphi+1] = {};
  double phimin = -1.0*TMath::Pi();
  double phimax = 1.0*TMath::Pi();
  double phistep = (phimax-phimin)/nbinsphi;
  for(int i=0; i<nbinsphi+1; i++){
    phibins[i] = phimin + i*phistep;
  }
  




  auto hIso_ITS = new TH1F("hIso_ITS","", 25, -10, 40);
  auto hIso_ITSue = new TH1F("hIso_ITSue","", 25, -10, 40);
  auto hIso_TPC = new TH1F("hIso_TPC","", 25, -10, 40);  
  
  auto hZvertex = new TH1F("hZvertez", "", 60, -30, 30);
  auto hZvertexAfter = new TH1F("hZvertezAfter", "", 60, -30, 30);
  auto hEventCut = new TH1F("hEventCut", "", 10, -0.5, 9.5);
  auto hEventCut_MB = new TH1F("hEventCut_MB", "", 10, -0.5, 9.5);
  auto hEventCut_EG1 = new TH1F("hEventCut_EG1", "", 10, -0.5, 9.5);
  auto hEventCut_EG2 = new TH1F("hEventCut_EG2", "", 10, -0.5, 9.5);
  auto hEventCut_EJ1 = new TH1F("hEventCut_EJ1", "", 10, -0.5, 9.5);
  auto hEventCut_EJ2 = new TH1F("hEventCut_EJ2", "", 10, -0.5, 9.5);
  auto hClusterCut = new TH1F("hClusterCut", "", 20, -0.5, 19.5);
  auto hClusterCutFlow = new TH1F("hClusterCutFlow", "", 20, -0.5, 19.5);
  auto hPileUpVertex = new TH1F("hPileUpVertex", "", 20, -0.5, 19.5);
  auto hMultiplicityBefore = new TH1F("hMultiplicityBefore", "", 1000, 0, 1000);
  auto hMultiplicityAfter = new TH1F("hMultiplicityAfter", "", 1000, 0, 1000);
  auto hUE = new TH1F("hUE", "", 500 , -250, 250);
  auto hUEse = new TH1F("hUEse", "", 500 , -250, 250);
  auto hTrigClass = new TH1F("hTrigClass", ";Trig ID; counts", 45 , 0, 45);
  
  hZvertex->Sumw2();
  hZvertexAfter->Sumw2();

  //cluster cuts histogram
  auto hCluster_tof = new TH1F("hCluster_tof", "", 200, -100, 100);
  auto hCluster_tof20GeV = new TH1F("hCluster_tof20GeV", "", 200, -100, 100);
  auto hExoticity = new TH1F("hExtoticity", "", 100, 0, 1);
  auto hCellEvClusterE = new TH1F("hCellEvClusterE", "", 100, -50, 50);
  auto hNcell = new TH1F("hNcell", "", 20, 0, 20);
  auto hNLM = new TH1F("hNLM", "", 10, 0, 10);
  auto hD2BC = new TH1F("hD2BC", "", 10, 0, 10);
  auto hEta = new TH1F("hEta", "", nbinseta, etabins);
  auto hPhi = new TH1F("hPhi", "", nbinsphi, phibins);
  auto hIsolation = new TH1F("hIsolation", "", 1000, -500, 500);

  hCluster_tof->SetTitle(";cluster_tof [ns]; counts");
  hCluster_tof20GeV->SetTitle("photons > 20 GeV;cluster_tof [ns]; counts");
  hExoticity->SetTitle(";E_{cross}/E_{max};counts");
  hCellEvClusterE->SetTitle(";E_{max} - E_{cluster};counts");
  hNcell->SetTitle(";N_{cell};counts");
  hNLM->SetTitle(";NLM;counts");
  hD2BC->SetTitle(";Distance to bad channel; counts");
  hIsolation->SetTitle(";isolation [GeV/c]; counts");
  hEta->SetTitle(";#eta; counts");
  hPhi->SetTitle(";#phi; counts");

  //Photon
  const int nbinscluster = 26;
  //Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning
  Double_t clusterbins[nbinscluster+1] = {0.00, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 11.00, 12.00, 13.00, 14.00, 15.00, 16.00, 17.00, 18.00, 20.00, 22.00, 26.00, 30.00, 35.00, 40.00, 50.00, 60.00};//nbinscluster = 26, rejection factor binning

  const int numRuns = 9;
  auto hTrack_pt  = new TH1F("hTrack_pt","", nbinscluster, clusterbins);
  auto hReco_pt  = new TH1F("hReco_pt","", nbinscluster, clusterbins);
  auto hCluster_pt = new TH1F("hCluster_pt", "", nbinscluster, clusterbins);
  auto hRecoNorm_pt  = new TH1F("hRecoNorm_pt","", nbinscluster, clusterbins);
  auto hClusterNorm_pt = new TH1F("hClusterNorm_pt", "", nbinscluster, clusterbins);
  auto hMB_E = new TH1F("hMB_E", "", nbinscluster, clusterbins);
  auto hEG1_E = new TH1F("hEG1_E", "", nbinscluster, clusterbins);
  auto hEG2_E = new TH1F("hEG2_E", "", nbinscluster, clusterbins);

  
  hTrack_pt->Sumw2();
  hReco_pt->Sumw2();
  hCluster_pt->Sumw2();
  hRecoNorm_pt->Sumw2();
  hClusterNorm_pt->Sumw2();
  hEG1_E->Sumw2();  
  hEG2_E->Sumw2();
  hMB_E->Sumw2();

  hTrack_pt->SetTitle("; p_{T} (GeV/c) ; 1/N_{ev}dN/dp_{T}");
  hCluster_pt->SetTitle("; E_{T} (GeV) ; counts");
  hReco_pt->SetTitle("; E_{T} (GeV) ; counts");
  hClusterNorm_pt->SetTitle("; E_{T} (GeV) ; counts/N_{ev}");
  hRecoNorm_pt->SetTitle("; E_{T} (GeV) ; counts/N_{ev}");
  hMB_E->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{MB}dN/dE_{T}");
  hEG1_E->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG1}dN/dE_{T}");
  hEG2_E->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG2}dN/dE_{T}");
  	
  int nevent = 0; 
  int numEvents_tracks = 0;
  int numClustersPost = 0;
  int numClustersPre = 0;
  int numClusterMoreThan5GeV = 0;
  int numEvents_tot = 0;
  int numEvents_passTrig = 0;
  int numEvents_passAll = 0;
  int numEvents_MB = 0;
  int numEvents_EG1 = 0;
  int numEvents_EG2 = 0;
  int numEvents_MB_before = 0;
  int numEvents_EG1_before = 0;
  int numEvents_EG2_before = 0;
  int numEvents_onlyEG2 = 0;
  int numEvents_Zmore10 = 0;
  int numEvents_Zless10 = 0;
  int numEvents_noZ = 0;
  int currentRunNumber = 0;

  const double maxEta = 0.4;
  const double timeCut = 20;
  const double badChnCut = 1;
  const ULong64_t one1 = 1;
  
  /*//////////////////////////////////////////////////////////////////////////////////
    13c triggers
 //////////////////////////////////////////////////////////////////////////////////*/

  ULong64_t trigMask_13c_trigs[3] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13c_trigs[0] = (one1 << 6);

  /*//////////////////////////////////////////////////////////////////////////////////
    13d triggers
  //////////////////////////////////////////////////////////////////////////////////*/
  ULong64_t trigMask_13d_trigs[3] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13d_trigs[0] = (one1 << 2);
  trigMask_13d_trigs[1] = (one1 << 18);
  trigMask_13d_trigs[2] = (one1 << 19);
  
  ULong64_t trigMask_13d_trigs2[3] = {0};//0 = MB, 1 = EG1, 2 = EG2, 3 = EJ1, 4 = EJ2
  trigMask_13d_trigs2[0] = (one1 << 1);
  trigMask_13d_trigs2[1] = (one1 << 18);//EG1
  trigMask_13d_trigs2[2] = (one1 << 19);//EG2
  
  
  /*//////////////////////////////////////////////////////////////////////////////////
    13e triggers
  //////////////////////////////////////////////////////////////////////////////////*/
  ULong64_t trigMask_13e_trigs[3] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13e_trigs[0] = (one1 << 2);
  trigMask_13e_trigs[1] = (one1 << 17);
  trigMask_13e_trigs[2] = (one1 << 18);

  ULong64_t trigMask_13e_trigs_r196208[3] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13e_trigs_r196208[0] = (one1 << 2);
  trigMask_13e_trigs_r196208[1] = (one1 << 12);
  trigMask_13e_trigs_r196208[2] = (one1 << 13);


  /*//////////////////////////////////////////////////////////////////////////////////
    13f triggers
 //////////////////////////////////////////////////////////////////////////////////*/
  ULong64_t trigMask_13f_trigs1[3] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13f_trigs1[0] = (one1 << 2);
  trigMask_13f_trigs1[1] = (one1 << 17);
  trigMask_13f_trigs1[2] = (one1 << 18);
 
  ULong64_t trigMask_13f_trigs2[3] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13f_trigs2[0] = (one1 << 2);
  trigMask_13f_trigs2[1] = (one1 << 12);
  trigMask_13f_trigs2[2] = (one1 << 13);
  
  ULong64_t trigMask_13f_trigs3[3] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13f_trigs3[0] = (one1 << 1);
  trigMask_13f_trigs3[1] = (one1 << 16);
  trigMask_13f_trigs3[2] = (one1 << 17);

  ULong64_t trigMask_13f_trigs4[3] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13f_trigs3[0] = (one1 << 9);
  trigMask_13f_trigs3[1] = (one1 << 13);
  trigMask_13f_trigs3[2] = (one1 << 14);

  ULong64_t trigMask[3] = {0};


  Long64_t totEvents = _tree_event->GetEntries();
  numEvents_tot = totEvents;
  Long64_t restrictEvents = lastEvent;
  Long64_t numEntries = TMath::Min(totEvents,restrictEvents);
  std::cout << numEntries << std::endl;
  
  //start event loop
  for (Long64_t ievent= firstEvent;ievent< numEntries ;ievent++) {
    _tree_event->GetEntry(ievent);
    nevent += 1;
    if(ievent%100000==0)
      {
	cout << ievent << "\t" << run_number << endl;
      }
    
    hPileUpVertex->Fill(npileup_vertex_spd);
    hEventCut->Fill(0);
    hZvertex->Fill(primary_vertex[2]);
    float multp_sum = 0;
    for (int k = 0; k < 64; k++) {
        multp_sum += multiplicity_v0[k];
      }
    hMultiplicityBefore->Fill(multp_sum);

    for(int trig_id = 0; trig_id < 41; trig_id++){
      if(not(((one1 << trig_id) & trigger_mask[0]) == 0))
	hTrigClass->Fill(trig_id);
      }

    //Looop over tracks
    for (int ntrac = 0; ntrac< ntrack; ntrac++){
      hTrack_pt->Fill(track_pt[ntrac]);
      
    }
    //Loop over cluster
    for(ULong64_t nclus = 0; nclus< ncluster; nclus++){
      hCluster_pt->Fill(cluster_pt[nclus]);
      hClusterNorm_pt->Fill(cluster_pt[nclus]);
    }

    //Loop over clusters with cuts
    for(ULong64_t n=0; n< ncluster; n++)
      {
	
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
	  3    dist2badchn >= 2
	  4    |tof| < 30 ns
	  5    isoation: E < 2 GeV r = 0.4
	  6    shower shape cut
	  7    |eta| < 0.667
	  8    1.396 < phi < 3.28
	////////////////////////////////////////*/
	if(not (cluster_ncell[n]>=2)) {hClusterCutFlow->Fill(1); continue;}
	//if(not (cluster_e_cross[n]/cluster_e_max[n]>0.05)) continue;
	if(not (cluster_nlocal_maxima[n]<= 2)) continue;
	if(not (cluster_distance_to_bad_channel[n]>=1))continue;
	if(not ((cluster_tof[n] > -20 ) && (cluster_tof[n] < 20))) continue;
	//acceptance cuts
	if(not (TMath::Abs(cluster_eta[n]) < 0.67)) continue;
	if(not (1.396 < cluster_phi[n] && cluster_phi[n] < 3.28)) continue;
	//shower shape and isolation
	if(not (( 0.1 < cluster_lambda_square[n][0]) &&  ( 0.3 > cluster_lambda_square[n][0]))) continue;
	//if(not (isolation < 1.5)) continue;

	if(ievent%1000==0){
 	  std::cout << "cluster accepted" << std::endl;
	}
	hReco_pt->Fill(clusterPt);
	hRecoNorm_pt->Fill(clusterPt);
	
      }//end cluster

    
    
  }//loop over events
  std::cout << " END LOOP  " << std::endl;
  cout << "total events: " << numEvents_tot << endl;
  cout << "total/minbias/EG1/EG2 events:" << endl;
  cout << "before:" << "\t" <<
    numEvents_passTrig << "\t" << numEvents_MB_before << "\t" <<
    numEvents_EG1_before << "\t" << numEvents_EG2_before << "\t" <<
    endl;
  cout << "after:" << "\t"  <<
    numEvents_passAll << "\t" << numEvents_MB << "\t" <<
    numEvents_EG1 << "\t" << numEvents_EG2 << "\t" <<
    endl;  

  //if(numEvents_passAll == 0) return;
  
  cout << "NUMBER OF CLUSTER WITH e > 5 GeV: "  << numClusterMoreThan5GeV << endl;
  //Normalizing the bins and getting yaxsis to be 1/Nevt*dN/dptdeta
  cout << numEvents_tracks << endl;
  cout << filename(0,3) << "\tTotal Events: " << numEntries << "\tEvent selection: " << numEvents_passAll << "\tPre-Cluster selection: " << numClustersPre << "\tPostCluster selection: " << numClustersPost << endl;
  const double deltaEta = 1.334;
  const double deltaPhi = 1.884;
  double acceptanceNorm = 2*TMath::Pi()/(deltaEta*deltaPhi);
  

  auto normalizer = new TH1D("normalizer", "normalizer", 20, -0.5, 19.5);
  normalizer->SetBinContent(1, deltaEta);
  normalizer->SetBinContent(2, deltaPhi);
  normalizer->SetBinContent(3, numEvents_tot);
  normalizer->SetBinContent(4, numEvents_passTrig);
  normalizer->SetBinContent(5, numEvents_passAll);
  normalizer->SetBinContent(6, numEvents_MB_before);
  normalizer->SetBinContent(7, numEvents_EG1_before);
  normalizer->SetBinContent(8, numEvents_EG2_before);
  normalizer->SetBinContent(11, numEvents_MB);
  normalizer->SetBinContent(12, numEvents_EG1);
  normalizer->SetBinContent(13, numEvents_EG2);
  normalizer->SetBinContent(16, numEvents_Zmore10);
  normalizer->SetBinContent(17, numEvents_noZ);

  
  normalizer->GetXaxis()->SetBinLabel(1,"deltaEta");
  normalizer->GetXaxis()->SetBinLabel(2,"deltaPhi");
  normalizer->GetXaxis()->SetBinLabel(3,"numEvents_tot");
  normalizer->GetXaxis()->SetBinLabel(4,"numEvents_passTrig");
  normalizer->GetXaxis()->SetBinLabel(5,"numEvents_passAll");
  normalizer->GetXaxis()->SetBinLabel(6,"numEvents_MB_before");
  normalizer->GetXaxis()->SetBinLabel(7,"numEvents_EG1_before");
  normalizer->GetXaxis()->SetBinLabel(8,"numEvents_EG2_before");
  normalizer->GetXaxis()->SetBinLabel(11,"numEvents_MB");
  normalizer->GetXaxis()->SetBinLabel(12,"numEvents_EG1");
  normalizer->GetXaxis()->SetBinLabel(13,"numEvents_EG2");
  normalizer->GetXaxis()->SetBinLabel(16,"numEvents_Zmore10");
  normalizer->GetXaxis()->SetBinLabel(17,"numEvents_noZ");

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
  hEventCut->GetXaxis()->SetBinLabel(2,"no GA/GJ trigger");
  hEventCut->GetXaxis()->SetBinLabel(3,"primary vertex > 10");
  hEventCut->GetXaxis()->SetBinLabel(4,"primary vertex = 0");
  hEventCut->GetXaxis()->SetBinLabel(5,"pile up");
  hEventCut->GetXaxis()->SetBinLabel(6,"skimming");
  hEventCut->GetXaxis()->SetBinLabel(7,"passed");

  hEventCut_EG1->GetXaxis()->SetBinLabel(1,"All events");
  hEventCut_EG1->GetXaxis()->SetBinLabel(2,"no GA/GJ trigger");
  hEventCut_EG1->GetXaxis()->SetBinLabel(3,"primary vertex > 10");
  hEventCut_EG1->GetXaxis()->SetBinLabel(4,"primary vertex = 0");
  hEventCut_EG1->GetXaxis()->SetBinLabel(5,"pile up");
  hEventCut_EG1->GetXaxis()->SetBinLabel(6,"ntrack < 0");
  hEventCut_EG1->GetXaxis()->SetBinLabel(7,"passed");

  hEventCut_EG2->GetXaxis()->SetBinLabel(1,"All events");
  hEventCut_EG2->GetXaxis()->SetBinLabel(2,"no GA/GJ trigger");
  hEventCut_EG2->GetXaxis()->SetBinLabel(3,"primary vertex > 10");
  hEventCut_EG2->GetXaxis()->SetBinLabel(4,"primary vertex = 0");
  hEventCut_EG2->GetXaxis()->SetBinLabel(5,"pile up");
  hEventCut_EG2->GetXaxis()->SetBinLabel(6,"ntrack < 0");
  hEventCut_EG2->GetXaxis()->SetBinLabel(7,"passed");

  hEventCut_MB->GetXaxis()->SetBinLabel(1,"All events");
  hEventCut_MB->GetXaxis()->SetBinLabel(2,"no MB trigger");
  hEventCut_MB->GetXaxis()->SetBinLabel(3,"primary vertex > 10");
  hEventCut_MB->GetXaxis()->SetBinLabel(4,"primary vertex = 0");
  hEventCut_MB->GetXaxis()->SetBinLabel(5,"pile up");
  hEventCut_MB->GetXaxis()->SetBinLabel(6,"ntrack < 0");
  hEventCut_MB->GetXaxis()->SetBinLabel(7,"passed");

  
  hTrack_pt->Scale(1.0/hEventCut->GetBinContent(1));
  hCluster_pt->Scale(1.0/hEventCut->GetBinContent(1));

  //Writing to file
  filename += "_Tracking_Clusters_ClusterCuts_RFbinnig_noNorm";
  cout << filename << endl;
  auto fout = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_%llu_%ibins_firstEvent%lld_%s.root",TriggerBit, nbinscluster, firstEvent, filename.Data()), "RECREATE");  


  
  //writing photon info
  hMB_E->Write("hMB_E");
  hEG1_E->Write("hEG1_E");
  hEG2_E->Write("hEG2_E");
  normalizer->Write("hNormalizer");
  hTrack_pt->Write("hTrack_pt");
  hCluster_pt->Write("hCluster_pt");
  hReco_pt->Write("hReco_pt");
  hZvertex->Write("hZvertex");
  hZvertexAfter->Write("hZvertexAfter");
  hPileUpVertex->Write("hPileUpVertex");
  hEventCut->Write("hEventCut");
  hEventCut_MB->Write("hEventCut_MB");
  hEventCut_EG1->Write("hEventCut_EG1");
  hEventCut_EG2->Write("hEventCut_EG2");
  hMultiplicityBefore->Write("hMultiplicityBefore");
  hMultiplicityAfter->Write("hMultiplicityAfter");
  hTrigClass->Write("hTrigClass");
  fout->Close();  

  return;
  
}

    
void isoPhotonAnalysisData_pPbTr(){
  auto start = std::chrono::system_clock::now();
  
  //Input to Run is as follow: Run(const int TriggerBit, TString address, Long64_t firstEvent = 0, Long64_t lastEvent = 1000000000000000)
  
/*/////////////////////////////////////////////////////////////////
p-Pb data sets:
13d,e: p-Pb emcal trigger   
13f  : Pb-p emcal trigger    
/////////////////////////////////////////////////////////////////*/
  //The trigger bit options. Most of 17q does not have 
  //0010 = 02 = EG1
  //0100 = 04 = EG2
  //0110 = 06 = EG1||EG2

  //Run(6, "pPb/13d/13d_all10runs_noSkim.root");
  //Run(6, "pPb/13e/13e_10runs_noSkim_part1.root");
  //Run(6, "pPb/13e/13e_10runs_noSkim_part2.root");
  //Run(6, "pPb/13f/13f_10runs_noSkim_part1.root");
  //Run(6, "pPb/13f/13f_10runs_noSkim_part2.root");
  //Run(6, "pPb/13f/13f_10runs_noSkim_part3.root");
  //Run(6, "pPb/13f/13f_10runs_noSkim_part4.root");
  //Run(6, "pPb/13f/13f_3runs_noSkim_part5.root");
  //Run(6, "pPb/13f/13f_new_9runs_noSkim_part1.root");
  //Run(6, "pPb/13f/13f_new_9runs_noSkim_part2.root");
  //Run(6, "pPb/13f/13f_new_9runs_noSkim_part3.root");

  //Using EMCal Framework
  //Run(6, "pPb/13d/13d_all10Runs_noNonLin_kEMCEGA.root");
  //Run(6, "pPb/13d/13d_all10Runs_noNonLin_kEMCEGA_isoFixTry1.root");
  //Run(6, "pPb/13f/13f_1runs_kEMCEGA_isoFix.root");
  //Run(6, "pPb/13f/13f_1runs_kEMCEGA_KINT7_isoFix.root");
  //Run(6, "pPb/13f/13f_1runs_kAny_isoFix.root");
  //Run(6, "pPb/13f/13f_1runs_kEMCEGA_greenlightTrue.root");
  //Run(6, "pPb/13f/13f_1runs_kEMCEGA_kINT7_greenlightTrue.root");
  //Run(6, "pPb/13f/13f_1runs_kEMCEGA_kINT7_mannualMode.root");
  //Run(6, "pPb/13f/13f_1runs_kEMCEGA_kINT7_mannualMode_greenlight.root ");
  //Run(6, "pPb/13f/13f_1runs_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(6, "pPb/13f/13f_1runs_kEMCEGA_kINT7_kANy_mannualMode_greenlight_nonLinCorrFixed.root");

  //Run(6, "pPb/13d/13d_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(6, "pPb/13e/13e_part1_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(6, "pPb/13e/13e_part2_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(6, "pPb/13f/13f_part1_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(6, "pPb/13f/13f_part2_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(6, "pPb/13f/13f_part3_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(6, "pPb/13f/13f_part4_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(6, "pPb/13f/13f_part5_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(6, "pPb/13f/13fnew_part1_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(6, "pPb/13f/13fnew_part2_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(6, "pPb/13f/13fnew_part3_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");

  //For RF check
  //mb spectra
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part000.root");//run 195529
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part002.root");//run 195566
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part003.root");//run 195567
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part004.root");//run 195568
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part005.root");//run 195592
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part006.root");//run 195596
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part007.root");//run 195633
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part008.root");//run 195635
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part009.root");//run 195644
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part010.root");//run 195673
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part011.root");//run 195673
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part012.root");//run 195675
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part013.root");//run 195677
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part014.root");//run 195677
  //Run(1, "pPb/13c/13c_run195675_kEMCGA_kINT7_kANY_mannualMode_greenlight_woNonLinCorr.root");//
  //Run(1, "pPb/13c/13c_run195675_kINT7_mannualMode_greenlight_woNonLinCorr.root");//
  //Run(1, "pPb/13c/13c_run195675_kINT7_mannualMode_greenlight_woNonLinCorr_noPhySel_yesTrig.root");//
  //Run(1, "pPb/13c/13c_run195675_kINT7_mannualMode_greenlight_woNonLinCorr_noPhySel_noTrig.root");//
  //Run(1, "pPb/13c/13c_run195675_kINT7_mannualMode_greenlight_woNonLinCorr_noPhySel_yesTrig_builtInFalse.root");
  //Run(1, "pPb/13c/13c_run195675_kAny_mannualMode_greenlight_woNonLinCorr_noPhySel_yesTrig_builtInFalse.root");
  //Run(1, "pPb/13c/13c_run195675_kINT7_mannualMode_greenlight_woNonLinCorr_noPhySel_yesTrig_builtInFalse_OverrideTrue.root");

  
  //Run(7, "pPb/13d/13d_all10runs_noSkim.root");
  //Run(7, "pPb/13e/13e_10runs_noSkim_part1.root");
  //Run(7, "pPb/13e/13e_10runs_noSkim_part2.root");
  //Run(7, "pPb/13f/13f_10runs_noSkim_part1.root");
  //Run(7, "pPb/13f/13f_10runs_noSkim_part2.root");
  //Run(7, "pPb/13f/13f_10runs_noSkim_part3.root");
  //Run(7, "pPb/13f/13f_10runs_noSkim_part4.root");
  //Run(7, "pPb/13f/13f_3runs_noSkim_part5.root");
  //Run(7, "pPb/13f/13f_new_9runs_noSkim_part1.root");
  //Run(7, "pPb/13f/13f_new_9runs_noSkim_part2.root");
  //Run(7, "pPb/13f/13f_new_9runs_noSkim_part3.root");

  //Run(7, "pPb/13d/13d_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(7, "pPb/13e/13e_part1_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(7, "pPb/13e/13e_part2_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(7, "pPb/13f/13f_part1_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(7, "pPb/13f/13f_part2_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(7, "pPb/13f/13f_part3_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(7, "pPb/13f/13f_part4_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(7, "pPb/13f/13f_part5_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(7, "pPb/13f/13fnew_part1_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(7, "pPb/13f/13fnew_part2_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  //Run(7, "pPb/13f/13fnew_part3_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");

  //13f tests
  //Run(7, "pPb/13f/13f_run197302_kEMCEGA_kINT7_kANy_mannualMode_greenlight_nonLinCorrFixed.root");
  //Run(7, "pPb/13f/13f_run197302_kINT7_nonLinCorr_wClusters_onlyClusEtaPhiEPT_addCellMaxCrossOnly_emcalhContinue_EMCALCells_otherClusCuts.root");

  
  //Run(1, "pPb/13c/13c_2runs_part1_kINT7_mannualMode_greenlight_nonLinCorr_part1.root");//Run 195529 and 195531
  //Run(1, "pPb/13c/13c_2runs_part1_kINT7_mannualMode_greenlight_nonLinCorr_part2.root");//Run 195529 and 195531
  //Run(1, "pPb/13c/13c_2runs_part1_kINT7_mannualMode_greenlight_nonLinCorr_part3.root");//Run 195529 and 195531
  //Run(1, "pPb/13c/13c_2runs_part1_kINT7_mannualMode_greenlight_nonLinCorr_part4.root");//Run 195531
  //Run(1, "pPb/13c/13c_2runs_part1_kINT7_mannualMode_greenlight_nonLinCorr_part5.root");//Run 195531
  //Run(1, "pPb/13c/13c_run195566_kINT7_mannualMode_greenlight_nonLinCorr_part1.root");//
  //Run(1, "pPb/13c/13c_run195566_kINT7_mannualMode_greenlight_nonLinCorr_part2.root");//
  //Run(1, "pPb/13c/13c_run195567_kINT7_mannualMode_greenlight_nonLinCorr.root");//
  //Run(1, "pPb/13c/13c_run195568_kINT7_mannualMode_greenlight_nonLinCorr_part1.root");//
  //Run(1, "pPb/13c/13c_run195568_kINT7_mannualMode_greenlight_nonLinCorr_part2.root");//
  //Run(1, "pPb/13c/13c_run195592_kINT7_mannualMode_greenlight_nonLinCorr.root");//
  //Run(1, "pPb/13c/13c_run195593_kINT7_mannualMode_greenlight_nonLinCorr_part1.root");//
  //Run(1, "pPb/13c/13c_run195593_kINT7_mannualMode_greenlight_nonLinCorr_part2.root");//
  //Run(1, "pPb/13c/13c_run195596_kINT7_mannualMode_greenlight_nonLinCorr.root");//
  //Run(1, "pPb/13c/13c_run195644_kINT7_mannualMode_greenlight_nonLinCorr_part1.root");//
  //Run(1, "pPb/13c/13c_run195644_kINT7_mannualMode_greenlight_nonLinCorr_part2.root");//
  //Run(1, "pPb/13c/13c_run195673_kINT7_mannualMode_greenlight_nonLinCorr_part1.root");//
  //Run(1, "pPb/13c/13c_run195673_kINT7_mannualMode_greenlight_nonLinCorr_part2.root");//
  //Run(1, "pPb/13c/13c_run195675_kINT7_mannualMode_greenlight_nonLinCorr.root");//
  //Run(1, "pPb/13c/13c_run195677_kINT7_mannualMode_greenlight_nonLinCorr.root");//
  //Run(1, "pPb/13c/13c_1runs_kINT7_nonLinCorr_wClusters_removeCells_onlyClusEtaPhiEPT.root");

  //Run(1, "pp/17p/17p_run282343_kINT7_mannualAndGreen_split5_woNL_builtInFlase_noPhySel.root");
  //Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part1_001.root");
  //Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part1_002.root");
  //Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part1_003.root");
  //Run(1, "pp/17p/17p_CENT_wSDD_10runs_noThresh_part1.root");
  //Run(1, "pp/17p/17p_run282342_kINT7_mannualAndGreen_split5_woNL_builtInFlase_noPhySel_part0.root");
  //Run(1, "pp/17p/");

  //Run number 282393
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part007.root");//
  //Run(4, "pp/17q/17q_ITSonly_run282393_kMuonCalo_mannualAndGreen_split5_wNL.root");//310278
  //Run(4, "pp/17q/17q_ITSonly_run282393_kMuonCalo_mannualAndGreen_split5_woNL.root");//435706
  //Run(4, "pp/17q/17q_ITSonly_run282391_kMuonCalo_kINT7_mannualAndGreen_split5_SENtuplizer_woNL.root");//435706
  //Run(4, "pp/17q/17q_ITSonly_run282391_kMuonCalo_kINT7_mannualAndGreen_split5_SENtuplizer_wNL.root");//435706
  //Run(4, "pp/17q/17q_ITSonly_run282391_kMuonCalo_kINT7_mannualAndGreen_split5_SENtuplizer_woNL_NLFalse.root");//435706
  //Run(4, "pp/17q/17q_ITSonly_run282391_kMuonCalo_kINT7_mannualAndGreen_split5_SENtuplizerSetForcedClusterEFalse.root");//435706
  //Run(4, "pp/17q/17q_ITSonly_run282391_kMuonCalo_kINT7_mannualAndGreen_split5_SENtuplizer_TimeCalibOnlyFalse.root");//435706
  //Run(4, "pp/17q/17q_ITSonly_run282391_kMuonCalo_kINT7_mannualAndGreen_split5_SENtuplizer_TimeCalibFalse.root");//435706
  
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
