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
#include <chrono>
#include <ctime> 


void Run(ULong64_t TriggerBit, TString address,  Long64_t firstEvent = 0, Long64_t lastEvent = 10000000000000){

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
  
  //event variables
  Double_t primary_vertex[3];
  Bool_t is_pileup_from_spd_5_08;
  Bool_t is_pileup_from_spd_3_08;
  int run_number;
  int npileup_vertex_spd;
  ULong64_t trigger_mask[2];
  unsigned int ntrack;
  Float_t multiplicity_v0[64];
  Float_t ue_estimate_its_const;
  


  //cluster variables
  UInt_t ncluster;
  Float_t cluster_e[kMax];
  Float_t cluster_pt[kMax];
  Float_t cluster_eta[kMax];
  Float_t cluster_phi[kMax];
  Float_t cluster_tof[kMax];
  Float_t cluster_e_max[kMax];
  Float_t cluster_e_cross[kMax];
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
    

  _tree_event->SetBranchAddress("primary_vertex", primary_vertex);
  _tree_event->SetBranchAddress("is_pileup_from_spd_5_08", &is_pileup_from_spd_5_08);
  _tree_event->SetBranchAddress("is_pileup_from_spd_3_08", &is_pileup_from_spd_3_08);
  _tree_event->SetBranchAddress("run_number", &run_number);
  _tree_event->SetBranchAddress("npileup_vertex_spd", &npileup_vertex_spd);
  _tree_event->SetBranchAddress("trigger_mask", trigger_mask);
  _tree_event->SetBranchAddress("ntrack", &ntrack);
  _tree_event->SetBranchAddress("multiplicity_v0", multiplicity_v0);
  _tree_event->SetBranchAddress("ue_estimate_its_const", &ue_estimate_its_const);

  _tree_event->SetBranchAddress("ncluster", &ncluster);
  _tree_event->SetBranchAddress("cluster_e", cluster_e);
  _tree_event->SetBranchAddress("cluster_pt", cluster_pt); // here
  _tree_event->SetBranchAddress("cluster_eta", cluster_eta);
  _tree_event->SetBranchAddress("cluster_phi", cluster_phi);
  _tree_event->SetBranchAddress("cluster_tof", cluster_tof);
  _tree_event->SetBranchAddress("cluster_e_max", cluster_e_max);
  _tree_event->SetBranchAddress("cluster_e_cross", cluster_e_cross);
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

  
  const int nbinseta = 180;
  Double_t etabins[nbinseta+1] = {};
  double etamin = -0.9;
  double etamax = 0.9;
  double etastep = (etamax-etamin)/nbinseta;
  for(int i=0; i<nbinseta+1; i++){
    etabins[i] = etamin + i*etastep;
  }

  const int nbinsphi = 94;
  Double_t phibins[nbinsphi+1] = {};
  double phimin = -1.5*TMath::Pi();
  double phimax = 1.5*TMath::Pi();
  double phistep = (phimax-phimin)/nbinsphi;
  for(int i=0; i<nbinsphi+1; i++){
    phibins[i] = phimin + i*phistep;
  }
  



  auto hEventCounts = new TH1F("hEventCounts","", 10, -0.5, 9.5);
  auto hEventCounts_EG1 = new TH1F("hEventCounts_EG1","", 10, -0.5, 9.5);
  auto hEventCounts_EG2 = new TH1F("hEventCounts_EG2","", 10, -0.5, 9.5);
  auto hZvertex = new TH1F("hZvertez", "", 60, -30, 30);
  auto hZvertexAfter = new TH1F("hZvertezAfter", "", 60, -30, 30);
  auto hHitsITS = new TH1F("hHitsITS", "", 10, -0.5, 9.5);
  auto hEventCut = new TH1F("hEventCut", "", 10, -0.5, 9.5);
  auto hEventCut_MB = new TH1F("hEventCut_MB", "", 10, -0.5, 9.5);
  auto hEventCut_EG1 = new TH1F("hEventCut_EG1", "", 10, -0.5, 9.5);
  auto hEventCut_EG2 = new TH1F("hEventCut_EG2", "", 10, -0.5, 9.5);
  auto hClusterCut = new TH1F("hClusterCut", "", 20, -0.5, 19.5);
  auto hClusterCutFlow = new TH1F("hClusterCutFlow", "", 20, -0.5, 19.5);
  auto hPileUpVertex = new TH1F("hPileUpVertex", "", 20, -0.5, 19.5);
  auto hMultiplicityBefore = new TH1F("hMultiplicityBefore", "", 200, 0, 200);
  auto hMultiplicityAfter = new TH1F("hMultiplicityAfter", "", 200, 0, 200);
  auto normalizer = new TH1D("normalizer", "normalizer", 20, -0.5, 19.5);
  
  hZvertex->Sumw2();
  hZvertexAfter->Sumw2();
  hHitsITS->SetTitle(";Layers hit; counts");

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

  hCluster_tof->SetTitle(";cluster_tof [ns]; counts");
  hCluster_tof20GeV->SetTitle("photons > 20 GeV;cluster_tof [ns]; counts");
  hExoticity->SetTitle(";E_{cross}/E_{max};counts");
  hCellEvClusterE->SetTitle(";E_{max} - E_{cluster};counts");
  hNcell->SetTitle(";N_{cell};counts");
  hNLM->SetTitle(";NLM;counts");
  hD2BC->SetTitle(";Distance to bad channel; counts");
  hEta->SetTitle(";#eta; counts");
  hPhi->SetTitle(";#phi; counts");
  

  //Photon
  const int nbinscluster = 26;
  //Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning
  Double_t clusterbins[nbinscluster+1] = {0.00, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 11.00, 12.00, 13.00, 14.00, 15.00, 16.00, 17.00, 18.00, 20.00, 22.00, 26.00, 30.00, 35.00, 40.00, 50.00, 60.00};//nbinscluster = 26, rejection factor binning
  //Double_t clusterbins[nbinscluster+1] = {0.00, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 14.00, 18.00, 25.00, 40.00, 60.00};//nbinscluster = 15
  
  auto hReco_pt  = new TH1F("hReco_pt","", nbinscluster, clusterbins);
  auto hCluster_pt = new TH1F("hCluster_pt", "", nbinscluster, clusterbins);
  auto hEG1_E = new TH1F("hEG1_E", "", nbinscluster, clusterbins);
  auto hEG2_E = new TH1F("hEG2_E", "", nbinscluster, clusterbins);
  auto hMB_E = new TH1F("hMB_E", "", nbinscluster, clusterbins);

  hReco_pt->Sumw2();
  hCluster_pt->Sumw2();
  hEG1_E->Sumw2();  
  hEG2_E->Sumw2();
  hMB_E->Sumw2();

  hCluster_pt->SetTitle("; E_{T} (GeV/c) ; 1/N_{ev}dN/dE_{T}");
  hReco_pt->SetTitle("; E_{T} (GeV/c) ; 1/N_{ev}dN/dE_{T}");
  hMB_E->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{MB}dN/dE_{T}");
  hEG1_E->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG1}dN/dE_{T}");
  hEG2_E->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG2}dN/dE_{T}");

  int nevent = 0; 
  int numEvents_tracks = 0;
  int numClustersPost = 0;
  int numClustersPre = 0;
  int numEvents_tot = 0;
  int numEvents_passTrig = 0;
  int numEvents_passAll = 0;
  int numEvents_MB = 0;
  int numEvents_EG1 = 0;
  int numEvents_EG2 = 0;
  int numEvents_EJ1 = 0;
  int numEvents_EJ2 = 0;
  int numEvents_MB_before = 0;
  int numEvents_EG1_before = 0;
  int numEvents_EG2_before = 0;
  int numEvents_EJ1_before = 0;
  int numEvents_EJ2_before = 0;
  int numEvents_onlyEG2 = 0;
  int numEvents_Zmore10 = 0;
  int numEvents_Zless10 = 0;
  int numEvents_noZ = 0;
  int currentRunNumber = 0;
  int numClusters_clusterpt = 0;


  const double maxEta = 0.8;
 
  const ULong64_t one1 = 1;
  const int numTrigs = 5; 

  /*//////////////////////////////////////////////////////////////////////////////////
    13d triggers
  //////////////////////////////////////////////////////////////////////////////////*/
  ULong64_t trigMask_13d_trigs[5] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13d_trigs[0] = (one1 << 2);
  trigMask_13d_trigs[1] = (one1 << 18);
  trigMask_13d_trigs[2] = (one1 << 19);
  
  ULong64_t trigMask_13d_trigs2[5] = {0};//0 = MB, 1 = EG1, 2 = EG2, 3 = EJ1, 4 = EJ2
  trigMask_13d_trigs2[0] = (one1 << 1);
  trigMask_13d_trigs2[1] = (one1 << 18);//EG1
  trigMask_13d_trigs2[2] = (one1 << 19);//EG2
  
  
  /*//////////////////////////////////////////////////////////////////////////////////
    13e triggers
  //////////////////////////////////////////////////////////////////////////////////*/
  ULong64_t trigMask_13e_trigs[5] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13e_trigs[0] = (one1 << 2);
  trigMask_13e_trigs[1] = (one1 << 17);
  trigMask_13e_trigs[2] = (one1 << 18);

  ULong64_t trigMask_13e_trigs_r196208[5] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13e_trigs_r196208[0] = (one1 << 2);
  trigMask_13e_trigs_r196208[1] = (one1 << 12);
  trigMask_13e_trigs_r196208[2] = (one1 << 13);

  /*//////////////////////////////////////////////////////////////////////////////////
    13f triggers
 //////////////////////////////////////////////////////////////////////////////////*/
  ULong64_t trigMask_13f_trigs1[5] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13f_trigs1[0] = (one1 << 2);
  trigMask_13f_trigs1[1] = (one1 << 17);
  trigMask_13f_trigs1[2] = (one1 << 18);

  ULong64_t trigMask_13f_trigs2[5] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13f_trigs2[0] = (one1 << 2);
  trigMask_13f_trigs2[1] = (one1 << 12);
  trigMask_13f_trigs2[2] = (one1 << 13);
  
  ULong64_t trigMask_13f_trigs3[5] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13f_trigs3[0] = (one1 << 1);
  trigMask_13f_trigs3[1] = (one1 << 16);
  trigMask_13f_trigs3[2] = (one1 << 17);

  ULong64_t trigMask_13f_trigs4[5] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13f_trigs3[0] = (one1 << 9);
  trigMask_13f_trigs3[1] = (one1 << 13);
  trigMask_13f_trigs3[2] = (one1 << 14);

  
  /*//////////////////////////////////////////////////////////////////////////////////
    13c triggers
 //////////////////////////////////////////////////////////////////////////////////*/

  ULong64_t trigMask_13c_trigs[5] = {0};//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13c_trigs[0] = (one1 << 6);

  ULong64_t trigMask[numTrigs] = {0};

  Long64_t totEvents = _tree_event->GetEntries();
  numEvents_tot = totEvents;
  Long64_t restrictEvents = lastEvent;//1000000000000;
  //4,035,922 --> starting of EMC good runs
  //1,749,493 to 2,939,337 --> runs 282415-282402
  Long64_t numEntries = TMath::Min(totEvents,restrictEvents);
  std::cout << numEntries << std::endl;
  double RN = 0.0;
  for (Long64_t ievent = firstEvent; ievent < numEntries ;ievent++) {
    _tree_event->GetEntry(ievent);
    nevent += 1;
    if(ievent%100000==0)
      {
	std::cout << ievent << std::endl;
	cout << run_number << endl;
      }
    
    /*if(RN != run_number){
      cout << ievent << " starts run " << run_number << endl;
      RN = run_number;
							
    }
    //continue;//*/   
    
    
    hPileUpVertex->Fill(npileup_vertex_spd);
    hEventCut->Fill(0);
    hZvertex->Fill(primary_vertex[2]);
    float multp_sum = 0;
    for (int k = 0; k < 64; k++) {
      multp_sum += multiplicity_v0[k];
    }
    hMultiplicityBefore->Fill(multp_sum);
    
    //Event Selection:    
    bool isMB, isEG1, isEG2;
    isMB = isEG1 = isEG2 = false;

    //13c
    if(run_number <= 195677)
      std::memcpy(trigMask, trigMask_13c_trigs, sizeof(trigMask));
    
    //13d
    if(run_number >= 195724 && run_number <= 195872)
      std::memcpy(trigMask, trigMask_13d_trigs, sizeof(trigMask));
    if(run_number == 195724 || run_number == 195760)
      std::memcpy(trigMask, trigMask_13d_trigs2, sizeof(trigMask));

    //13e
    if(run_number >= 195935 && run_number <= 196310)
      std::memcpy(trigMask, trigMask_13e_trigs, sizeof(trigMask));
    if(run_number == 196208)
      std::memcpy(trigMask, trigMask_13e_trigs_r196208, sizeof(trigMask));

    //13f
    if(run_number >= 196433 && run_number <=197388)
      std::memcpy(trigMask, trigMask_13f_trigs1, sizeof(trigMask));
    if(run_number == 196967 ||
       run_number == 197015 ||
       run_number == 197027 ||
       run_number == 197248 ||
       run_number == 197260 ||
       run_number == 197296 ||
       run_number == 197297 ||
       run_number == 197351)
      std::memcpy(trigMask, trigMask_13f_trigs2, sizeof(trigMask));
    if(run_number == 197091 || run_number == 197092)
      std::memcpy(trigMask, trigMask_13f_trigs3, sizeof(trigMask));
    if(run_number == 196433)
      std::memcpy(trigMask, trigMask_13f_trigs4, sizeof(trigMask));
    if(run_number == 197189) continue;


    ULong64_t localTrigBit = 0;
    if(not ((trigMask[0] & trigger_mask[0]) == 0))  {
      localTrigBit |= (1 << 0);
      
    }//*/

    if(run_number > 195677){
      if(not ((trigMask[1] & trigger_mask[0]) == 0))  {
	localTrigBit |= (1 << 1);
      }//*/
      if(not ((trigMask[2] & trigger_mask[0]) == 0))  {
	localTrigBit |= (1 << 2);
	
      }//*/
    }
    //cout << localTrigBit << endl;
    //001 = 1 = MB
    //110 = 6 = EG1||EG2
    //111 = 7 = MB||EG1||EG2
    //default trigSelection set to 6;
    //if(forRTrig) then trigSelection set to 7;

    if((localTrigBit & 1) != 0) {isMB = true; hEventCut_MB->Fill(0);numEvents_MB_before++;}
    if(((localTrigBit & 4) != 0) && (!isMB) ) {isEG2 = true;hEventCut_EG2->Fill(0);numEvents_EG2_before++;}
    if(((localTrigBit & 2) != 0) && (!isMB) && (!isEG2) ) {isEG1 = true;hEventCut_EG1->Fill(0);numEvents_EG1_before++;}
    
    
    
   if((localTrigBit & TriggerBit) == 0) {
      hEventCut->Fill(1);
      if(isMB) hEventCut_MB->Fill(1);
      if(isEG1) hEventCut_EG1->Fill(1);
      if(isEG2) hEventCut_EG2->Fill(1);
      continue;
    }//no emcal gamma or jet triggers

    if((localTrigBit & TriggerBit) != 0) {
      numEvents_passTrig++;
      if(isEG2 & !isEG1)
	numEvents_onlyEG2++;
    }
    if(not( TMath::Abs(primary_vertex[2])<10.0)){
	hEventCut->Fill(2);
	if(isMB) hEventCut_MB->Fill(2);
	if(isEG1) hEventCut_EG1->Fill(2);
	if(isEG2) hEventCut_EG2->Fill(2);
	numEvents_Zmore10++;
	continue;
      } //vertex z position

    if(primary_vertex[2] == 0.0000) {
      hEventCut->Fill(3);
      if(isMB) hEventCut_MB->Fill(3);
      if(isEG1) hEventCut_EG1->Fill(3);
      if(isEG2) hEventCut_EG2->Fill(3);
      numEvents_noZ++;
      continue;}//vertex exists

    if(is_pileup_from_spd_5_08) {
      hEventCut->Fill(4);
      if(isMB) hEventCut_MB->Fill(4);
      if(isEG1) hEventCut_EG1->Fill(4);
      if(isEG2) hEventCut_EG2->Fill(4);
      continue;
    } //removes pileup*/
  
    
    hEventCut->Fill(6);//all cuts
    if(isMB) {hEventCut_MB->Fill(6); numEvents_MB++;}
    if(isEG1) {hEventCut_EG1->Fill(6); numEvents_EG1++;}
    if(isEG2) {hEventCut_EG2->Fill(6); numEvents_EG2++;}

    
    hZvertexAfter->Fill(primary_vertex[2]);
    hMultiplicityAfter->Fill(multp_sum);
    numEvents_Zless10++;
    numEvents_passAll++;
    
    
    int eventFill = 0;    
    hEventCounts->Fill(eventFill);
    //cout << "pass event selection" << endl;


    
    //Loop over clusters
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
	  1    exoticity>0.03
	  2    nlocalmaxima<=2
	  3    dist2badchn >= 1
	  4    |tof| < 20 ns
	  6    shower shape cut: 0.1 < lambda < 0.3
	  7    |eta| < 0.667
	  8    1.396 < phi < 3.28
	////////////////////////////////////////*/
	hCluster_tof->Fill(cluster_tof[n]);
	if(clusterPt > 20)
	  hCluster_tof20GeV->Fill(cluster_tof[n]);
	hExoticity->Fill(cluster_e_cross[n]/cluster_e_max[n]);
	hCellEvClusterE->Fill(cluster_e_max[n]-clusterE);
	hNcell->Fill(cluster_ncell[n]);
	hNLM->Fill(cluster_nlocal_maxima[n]);
	hD2BC->Fill(cluster_distance_to_bad_channel[n]);
	hEta->Fill(clusterEta);
	hPhi->Fill(clusterPhi);

	
	int numCuts = 9;

	ULong64_t clusterCutBits = 0;
	ULong64_t clusterCutPassed = 0;
	
	numClustersPre++;	
	hClusterCut->Fill(0);
	hClusterCutFlow->Fill(0);
	hCluster_tof->Fill(cluster_tof[n]);
	if(clusterPt > 20) hCluster_tof20GeV->Fill(cluster_tof[n]);

	//if( not(clusterPt>8)) {continue;} //select pt of photons
	if( (cluster_ncell[n]>=2)){                    
	  clusterCutBits |= (1 << 0); hClusterCut->Fill(1); 
	} clusterCutPassed |= (1 << 0); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(1); //removes clusters with 1 or 2 cells
	if( ((cluster_e_cross[n]/cluster_e_max[n])>0.05)){
	  clusterCutBits |= (1 << 1); hClusterCut->Fill(2);
	} clusterCutPassed |= (1 << 1); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(2);//removes "spiky" clusters
	if( (cluster_nlocal_maxima[n]< 3)){
	  clusterCutBits |= (1 << 2); hClusterCut->Fill(3);
	} clusterCutPassed |= (1 << 2); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(3);//require to have at most 2 local maxima.
	if( (cluster_distance_to_bad_channel[n] > 1)){                          
	  clusterCutBits |= (1 << 3); hClusterCut->Fill(4);
	} clusterCutPassed |= (1 << 3); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(4);//distnace to bad channels
	if( (cluster_tof[n] > -20) && (cluster_tof[n] < 20)){
	  clusterCutBits |= (1 << 4); hClusterCut->Fill(5);
	} clusterCutPassed |= (1 << 4); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(5);//time of flight

	//Shower shape selection:
	if((cluster_lambda_square[n][0] > 0.1) && (cluster_lambda_square[n][0] < 0.3)){
	  clusterCutBits |= (1 << 6); hClusterCut->Fill(7);
	} clusterCutPassed |= (1 << 6); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(7);//single-photon selection, not merged
	

	//fiducial cut
	if((TMath::Abs(clusterEta)) < 0.67){
	  clusterCutBits |= (1 << 7); hClusterCut->Fill(8);
	} clusterCutPassed |= (1 << 7); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(8);//eta cut
	if((clusterPhi > 1.396) && (clusterPhi <3.28)){
	  clusterCutBits |= (1 << 8); hClusterCut->Fill(9);
	} clusterCutPassed |= (1 << 8); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(9);//phi cut
	
	if((clusterCutBits != clusterCutPassed) || (clusterCutBits == 0))
	  continue;

	hClusterCut->Fill(10);
	hClusterCutFlow->Fill(10);
	numClustersPost++;
	
	if(ievent%1000==0){
	  std::cout << "cluster accepted" << std::endl;
	}
	
	hReco_pt->Fill(clusterPt);
	if(isMB) hMB_E->Fill(clusterPt);
	if(isEG1) hEG1_E->Fill(clusterPt);
	if(isEG2) hEG2_E->Fill(clusterPt);

	hCluster_pt->Fill(clusterPt);
	numClusters_clusterpt++;
      }
    
    
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

  cout << "\tTotal Events: " << numEntries << "\tEvent selection: " << numEvents_passAll << "\tPre-Cluster selection: " << numClustersPre << "\tPostCluster selection: " << numClustersPost << endl;
  
  normalizer->SetBinContent(3, numEvents_tot);
  normalizer->SetBinContent(4, numEvents_passTrig);
  normalizer->SetBinContent(5, numEvents_passAll);
  normalizer->SetBinContent(6, numEvents_MB_before);
  normalizer->SetBinContent(7, numEvents_EG1_before);
  normalizer->SetBinContent(8, numEvents_EG2_before);
  normalizer->SetBinContent(9, numEvents_EJ1_before);
  normalizer->SetBinContent(10, numEvents_EJ2_before);
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
  normalizer->GetXaxis()->SetBinLabel(9,"numEvents_EJ1_before");
  normalizer->GetXaxis()->SetBinLabel(10,"numEvents_EJ2_before");
  normalizer->GetXaxis()->SetBinLabel(11,"numEvents_MB");
  normalizer->GetXaxis()->SetBinLabel(12,"numEvents_EG1");
  normalizer->GetXaxis()->SetBinLabel(13,"numEvents_EG2");
  normalizer->GetXaxis()->SetBinLabel(16,"numEvents_Zmore10");
  normalizer->GetXaxis()->SetBinLabel(17,"numEvents_noZ");
  
  //scaling for clusters
  for(int i = 1; i <  hCluster_pt->GetNbinsX()+1; i++)
    {
      double dpt = hCluster_pt->GetBinWidth(i);
      double content = hCluster_pt->GetBinContent(i);
      double temp = (content)/((double)numEvents_passAll*dpt);
      //double temp = content/((double)numEvents_passAll*dpt);
      //cout << dpt << "\t" << content << "\t" << temp << endl;
      //double temp = content/dpt;
      hCluster_pt->SetBinContent(i, temp);
      
      double error = hCluster_pt->GetBinError(i);
      double tempErr = (error)/((double)numEvents_passAll*dpt);
      //double tempErr = error/dpt;
      hCluster_pt->SetBinError(i, tempErr);
    }//
  for(int i = 1; i <  hReco_pt->GetNbinsX()+1; i++)
    {
      double dpt = hReco_pt->GetBinWidth(i);
      double contentMB = hMB_E->GetBinContent(i);
      double contentEG1 = hEG1_E->GetBinContent(i);
      double contentEG2 = hEG2_E->GetBinContent(i);
      double tempMB = (contentMB)/((double)numEvents_MB*dpt);
      double tempEG1 = (contentEG1)/((double)numEvents_EG1*dpt);
      double tempEG2 = (contentEG2)/((double)numEvents_EG2*dpt);
      double temp = tempEG1+tempEG2;
      hReco_pt->SetBinContent(i, temp);
      hMB_E->SetBinContent(i, tempMB);
      hEG1_E->SetBinContent(i, tempEG1);
      hEG2_E->SetBinContent(i, tempEG2);

      double errorMB = hMB_E->GetBinError(i);
      double errorEG1 = hEG1_E->GetBinError(i);
      double errorEG2 = hEG2_E->GetBinError(i);
      double tempErrMB = (errorMB)/((double)numEvents_MB*dpt);
      double tempErrEG1 = (errorEG1)/((double)numEvents_EG1*dpt);
      double tempErrEG2 = (errorEG2)/((double)numEvents_EG2*dpt);
      double tempErr = TMath::Sqrt(TMath::Power(tempErrEG1,2)+TMath::Power(tempErrEG2,2));
      hReco_pt->SetBinError(i, tempErr);
      hMB_E->SetBinError(i, tempErrMB);
      hEG1_E->SetBinError(i, tempErrEG1);
      hEG2_E->SetBinError(i, tempErrEG2);
    }//*/

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

  hEventCut_MB->GetXaxis()->SetBinLabel(1,"All events");
  hEventCut_MB->GetXaxis()->SetBinLabel(2,"no EMCA/MB trigger");
  hEventCut_MB->GetXaxis()->SetBinLabel(3,"primary vertex > 10");
  hEventCut_MB->GetXaxis()->SetBinLabel(4,"primary vertex = 0");
  hEventCut_MB->GetXaxis()->SetBinLabel(5,"pile up");
  hEventCut_MB->GetXaxis()->SetBinLabel(6,"ntrack < 0");
  hEventCut_MB->GetXaxis()->SetBinLabel(7,"passed");

  hEventCut_EG1->GetXaxis()->SetBinLabel(1,"All events");
  hEventCut_EG1->GetXaxis()->SetBinLabel(2,"no EMCA/MB trigger");
  hEventCut_EG1->GetXaxis()->SetBinLabel(3,"primary vertex > 10");
  hEventCut_EG1->GetXaxis()->SetBinLabel(4,"primary vertex = 0");
  hEventCut_EG1->GetXaxis()->SetBinLabel(5,"pile up");
  hEventCut_EG1->GetXaxis()->SetBinLabel(6,"ntrack < 0");
  hEventCut_EG1->GetXaxis()->SetBinLabel(7,"passed");

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
  filename += "_forRTrig_MBEG1EG2exlusion_tof20_eCross5_newExoticity";
  cout << filename.Data() << endl;
  auto fout = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_%llu_%ibins_%s.root",TriggerBit, nbinscluster, filename.Data()), "RECREATE");  
  

  
  //writing photon info
  hCluster_pt->Write("hCluster_pt");
  hReco_pt->Write("hReco_pt");
  hEventCounts->Write("hEventCounts");
  hMB_E->Write("hMB_E");
  hEG1_E->Write("hEG1_E");
  hEG2_E->Write("hEG2_E");

  hCluster_tof->Write("hCluster_tof");
  hCluster_tof20GeV->Write("hCluster_tof20GeV");
  hExoticity->Write("hExoticity");
  hCellEvClusterE->Write("hCellEvClusterE");
  hNcell->Write("hNcell");
  hNLM->Write("hNLM");
  hD2BC->Write("hD2BC");
  hEta->Write("hEta");
  hPhi->Write("hPhi");


  hZvertex->Write("hZvertex");
  hZvertexAfter->Write("hZvertexAfter");
  hPileUpVertex->Write("hPileUpVertex");
  hEventCut->Write("hEventCut");
  hEventCut_MB->Write("hEventCut_MB");
  hEventCut_EG1->Write("hEventCut_EG1");
  hEventCut_EG2->Write("hEventCut_EG2");
  hClusterCut->Write("hClusterCut");
  hClusterCutFlow->Write("hClusterCutFlow");
  hMultiplicityBefore->Write("hMultiplicityBefore");
  hMultiplicityAfter->Write("hMultiplicityAfter");
  normalizer->Write("hNormalizer");
  fout->Close();  

  return;
  
}

    
void isoPhotonAnalysisData_pPbRF(){
  auto start = std::chrono::system_clock::now();
  
  //Input to Run is as follow: Run(const int TriggerBit, TString address, Long64_t firstEvent = 0, Long64_t lastEvent = 10000000000000)
  
/////////////////////////////////////////////////////////////////*/
  //The trigger bit options. Most of 17q does not have 
  //001 = 1 = MB
  //110 = 6 = EG1||EG2
  //111 = 7 = MB||EG1||EG2
  
  //pp data sets

  //mb spectra
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part000.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part002.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part003.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part004.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part005.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part006.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part007.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part008.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part009.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part010.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part011.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part012.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part013.root");
  //Run(1, "pPb/13c/13c_14runs_noThresh_phySel_part014.root");

  //Run(1, "pPb/13d/13d_all10runs_noSkim.root");
  //Run(1, "pPb/13e/13e_10runs_noSkim_part1.root");
  //Run(1, "pPb/13e/13e_10runs_noSkim_part2.root");
  //Run(1, "pPb/13f/13f_10runs_noSkim_part1.root");
  //Run(1, "pPb/13f/13f_10runs_noSkim_part2.root");
  //Run(1, "pPb/13f/13f_10runs_noSkim_part3.root");
  //Run(1, "pPb/13f/13f_10runs_noSkim_part4.root");
  //Run(1, "pPb/13f/13f_3runs_noSkim_part5.root");

  
  //calo spectra
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
