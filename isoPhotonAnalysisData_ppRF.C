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
  auto hShowerShape = new TH1F("hShowerShape", "", 100, 0, 1);

  hCluster_tof->SetTitle(";cluster_tof [ns]; counts");
  hCluster_tof20GeV->SetTitle("photons > 20 GeV;cluster_tof [ns]; counts");
  hExoticity->SetTitle(";E_{cross}/E_{max};counts");
  hCellEvClusterE->SetTitle(";E_{max} - E_{cluster};counts");
  hNcell->SetTitle(";N_{cell};counts");
  hNLM->SetTitle(";NLM;counts");
  hD2BC->SetTitle(";Distance to bad channel; counts");
  hEta->SetTitle(";#eta; counts");
  hPhi->SetTitle(";#phi; counts");
  hShowerShape->SetTitle(";#sigma^{2}_{long}; counts");
  
  
  //Photon
  const int nbinscluster = 26;
  //Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning
  Double_t clusterbins[nbinscluster+1] = {0.00, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 11.00, 12.00, 13.00, 14.00, 15.00, 16.00, 17.00, 18.00, 20.00, 22.00, 26.00, 30.00, 35.00, 40.00, 50.00, 60.00};//nbinscluster = 26, rejection factor binning
  //Double_t clusterbins[nbinscluster+1] = {0.00, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 14.00, 18.00, 25.00, 40.00, 60.00};//nbinscluster = 15
  
  auto hReco_pt  = new TH1F("hReco_pt","", nbinscluster, clusterbins);
  auto hCluster_pt = new TH1F("hCluster_pt", "", nbinscluster, clusterbins);
  auto hDG2_caloE = new TH1F("hDG2_caloE", "", nbinscluster, clusterbins);
  auto hDG2_centE = new TH1F("hDG2_centE", "", nbinscluster, clusterbins);
  auto hEG2_caloE = new TH1F("hEG2_caloE", "", nbinscluster, clusterbins);
  auto hEG2_centE = new TH1F("hEG2_centE", "", nbinscluster, clusterbins);
  auto hMB_centE = new TH1F("hMB_centE", "",  nbinscluster, clusterbins);

  hReco_pt->Sumw2();
  hCluster_pt->Sumw2();
  hDG2_caloE->Sumw2();  
  hEG2_caloE->Sumw2();
  hDG2_centE->Sumw2();  
  hEG2_centE->Sumw2();
  hMB_centE->Sumw2();

  hCluster_pt->SetTitle("; E_{T} (GeV/c) ; 1/N_{ev}dN/dE_{T}");
  hReco_pt->SetTitle("; E_{T} (GeV/c) ; 1/N_{ev}dN/dE_{T}");
  hMB_centE->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{MB}dN/dE_{T}");
  hDG2_caloE->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{DG2}dN/dE_{T}");
  hEG2_caloE->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG2}dN/dE_{T}");
  hDG2_centE->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{DG2}dN/dE_{T}");
  hEG2_centE->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG2}dN/dE_{T}");

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
  
  /*//////////////////////////////////////////////////////////////////////////////////
    17p triggers
 //////////////////////////////////////////////////////////////////////////////////*/
  ULong64_t trigMask_17p_trigs1[numTrigs] = {0};
  trigMask_17p_trigs1[0] = (one1 << 0) | (one1 << 3);//fast | cent

  ULong64_t trigMask_17p_trigs2[numTrigs] = {0};
  trigMask_17p_trigs2[0] = (one1 << 0) | (one1 << 2);//fast | cent

  ULong64_t trigMask_17p_trigs3[numTrigs] = {0};
  trigMask_17p_trigs3[0] = (one1 << 0);//cent
  
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

    bool isMBcent, isDG2calo, isEG2calo, isEG2cent;
    isMBcent = isDG2calo = isEG2calo = isEG2cent = false;
    
    
    
    hPileUpVertex->Fill(npileup_vertex_spd);
    hEventCut->Fill(0);
    hZvertex->Fill(primary_vertex[2]);
    float multp_sum = 0;
    for (int k = 0; k < 64; k++) {
      multp_sum += multiplicity_v0[k];
    }
    hMultiplicityBefore->Fill(multp_sum);
    
    //Event Selection:    
    
    
    //17p
    /*if(run_number >= 282008 && run_number <= 282031)
      std::memcpy(trigMask, trigMask_17p_trigs1, sizeof(trigMask));
    if(run_number >= 282051 && run_number <= 282123)
      std::memcpy(trigMask, trigMask_17p_trigs1, sizeof(trigMask));
    if(run_number == 282030)
      std::memcpy(trigMask, trigMask_17p_trigs3, sizeof(trigMask));
    if(run_number == 282008 ||
       run_number == 282016 ||
       run_number == 282021 ||
       run_number == 282050 ||
       run_number == 282120)
       continue;//*/
    
    if(run_number >= 282051 && run_number <= 282343)
      std::memcpy(trigMask, trigMask_17p_trigs1, sizeof(trigMask));
    if(run_number == 282031 ||
       run_number == 282025)
      std::memcpy(trigMask, trigMask_17p_trigs2, sizeof(trigMask));
    if(run_number == 282030)
      std::memcpy(trigMask, trigMask_17p_trigs3, sizeof(trigMask));

    
    //17q
    if(run_number >= 282391 && run_number <= 282441)
      std::memcpy(trigMask, trigMask_17q_trigs1, sizeof(trigMask));
    if(run_number == 282415 || run_number == 282411 || run_number == 282402)
      std::memcpy(trigMask, trigMask_17q_trigs2, sizeof(trigMask));
    if(run_number == 282367 || run_number == 282366 || run_number == 282365)//EMC good runs 
      std::memcpy(trigMask, trigMask_17q_trigs3, sizeof(trigMask));
    
    
    
    ULong64_t localTrigBit = 0;
    if(run_number <= 282367){
      if(not ((trigMask[0] & trigger_mask[0]) == 0)){//MB selection
	localTrigBit |= (1 << 0);
      }
    }//end if TPC or 17p run
    
    if(run_number >= 282365){
      if(run_number == 282367 || run_number == 282366 || run_number == 282365){
	if(not ((trigMask[4] & trigger_mask[1]) == 0)){//EG2 calo
	  localTrigBit |= (1 << 2); 
	}
      }//end if TPC run
      else{
	if(not ((trigMask[2] & trigger_mask[0]) == 0)){//EG2 calo
	  localTrigBit |= (1 << 2); 
	}
      }//end else
	
    }//if 17p check

    
    //The trigger bit options. Most of 17q have min bias
    //001 = 1 = MB
    //010 = 2 = DG2
    //100 = 4 = EG2
    //101 = 5 = MB || EG2
    //110 = 6 = DG2|| EG2
    //111 = 7 = MB || DG2 || EG2
    if((localTrigBit & 1) != 0) {isMBcent = true; hEventCut_MB->Fill(0);numEvents_MBcent_before++;}
    if(((localTrigBit & 4) != 0) && (!isMBcent)) {isEG2calo = true;hEventCut_EG2->Fill(0);numEvents_EG2calo_before++;}
    //if(((localTrigBit & 2) != 0) && (!isMB) ) {isDG2calo = true;hEventCut_DG2->Fill(0);numEvents_DG2calo_before++;}
    //if(((localTrigBit & 4) != 0) && (!isMBcent)) {isEG2calo = true;hEventCut_EG2->Fill(0);numEvents_EG2calo_before++;}
    //if((localTrigBit & 8) != 0) {isEG2cent = true;hEventCut_EG2cent->Fill(0);numEvents_EG2cent_before++;}
    
    
    
    if((localTrigBit & TriggerBit) == 0) {
      hEventCut->Fill(1);
      if(isMBcent) hEventCut_MB->Fill(1);
      //if(isDG2calo) hEventCut_DG2->Fill(1);
      if(isEG2calo) hEventCut_EG2->Fill(1);
      //if(isEG2cent) hEventCut_EG2cent->Fill(1);
      continue;}//no emcal triggers*/
    if((localTrigBit & TriggerBit) != 0) {
      numEvents_passTrig++;
    }
    
    if(not( TMath::Abs(primary_vertex[2])<10.0)){
      hEventCut->Fill(2);
      if(isMBcent) hEventCut_MB->Fill(2);
      if(isEG2calo) hEventCut_EG2->Fill(2);
      //if(isDG2calo) hEventCut_DG2->Fill(2);
      //if(isEG2cent) hEventCut_EG2cent->Fill(2);
      
      numEvents_Zmore10++;
      continue;
    } //vertex z position
    
    if(primary_vertex[2] == 0.0000) {
      hEventCut->Fill(3);
      if(isMBcent) hEventCut_MB->Fill(3);
      if(isEG2calo) hEventCut_EG2->Fill(3);
      //if(isDG2calo) hEventCut_DG2->Fill(3);
      //if(isEG2cent) hEventCut_EG2cent->Fill(3);
      
      numEvents_noZ++;
      continue;}//removes no vertex found
    
    if(is_pileup_from_spd_5_08) {
      hEventCut->Fill(4);
      if(isMBcent) hEventCut_MB->Fill(4);
      if(isEG2calo) hEventCut_EG2->Fill(4);
      //if(isDG2calo) hEventCut_DG2->Fill(4);
      //if(isEG2cent) hEventCut_EG2cent->Fill(4);
      continue;
    } //removes pileup*/
    
    
    hEventCut->Fill(6);//all cuts
    if(isMBcent) {hEventCut_MB->Fill(6); numEvents_MBcent++;}
    if(isEG2calo) {hEventCut_EG2->Fill(6); numEvents_EG2calo++;}
    //if(isDG2calo) {hEventCut_DG2->Fill(6); numEvents_DG2calo++;}
    //if(isEG2cent) {hEventCut_EG2cent->Fill(6); numEvents_EG2cent++;}
    
    
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
	double isolation = cluster_iso_its_04[n] + cluster_iso_its_04_ue[n];//remove UE subtraction
	isolation = isolation - ue_estimate_its_const*0.4*0.4*TMath::Pi();//Use rhoxA subtraction
	
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
	hShowerShape->Fill(cluster_lambda_square[n][0]);
	
	int numCuts = 9;

	ULong64_t clusterCutBits = 0;
	ULong64_t clusterCutPassed = 0;
	
	numClustersPre++;	
	hClusterCut->Fill(0);
	hClusterCutFlow->Fill(0);

	//if( not(clusterPt>8)) {continue;} //select pt of photons
	if( (cluster_ncell[n]>=2)){                    
	  clusterCutBits |= (1 << 0); hClusterCut->Fill(1); 
	} clusterCutPassed |= (1 << 0); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(1); //removes clusters with 1 or 2 cells
	if( ((cluster_e_cross[n]/cluster_e_max[n])>0.05)){
	  clusterCutBits |= (1 << 1); hClusterCut->Fill(2);
	} clusterCutPassed |= (1 << 1); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(2);//removes "spiky" clusters
	if( (cluster_nlocal_maxima[n] <= 2)){
	  clusterCutBits |= (1 << 2); hClusterCut->Fill(3);
	} clusterCutPassed |= (1 << 2); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(3);//require to have at most 2 local maxima.
	if( (cluster_distance_to_bad_channel[n] >= 1)){                          
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
	if(isMBcent) hMB_centE->Fill(clusterPt);
	if(isEG2calo) hEG2_caloE->Fill(clusterPt);
	//if((localTrigBit & 4) != 0) hDG2_caloE->Fill(clusterPt);
	//if((localTrigBit & 8) != 0) hEG2_centE->Fill(clusterPt);

	hCluster_pt->Fill(clusterPt);
	numClusters_clusterpt++;	
      }
    
    
  }//loop over events
  std::cout << " END LOOP  " << std::endl;
  cout << "total events: " << numEvents_tot << endl;
  cout << "total/minbias/DG2/EG2calo/EG2cent events:" << endl;
  cout << "before:" << "\t" << numEvents_passTrig << "\t" << numEvents_MBcent_before << "\t" << numEvents_DG2calo_before << "\t" << numEvents_EG2calo_before << "\t" << numEvents_EG2cent_before << endl;
  cout << "after:" << "\t"  << numEvents_passAll << "\t" << numEvents_MBcent << "\t" << numEvents_DG2calo << "\t" << numEvents_EG2calo << "\t" << numEvents_EG2cent << endl;  

  cout << "\tTotal Events: " << numEntries << "\tEvent selection: " << numEvents_passAll << "\tPre-Cluster selection: " << numClustersPre << "\tPostCluster selection: " << numClustersPost << endl;
  
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

  hEventCut_DG2->GetXaxis()->SetBinLabel(1,"All events");
  hEventCut_DG2->GetXaxis()->SetBinLabel(2,"no EMCA/MB trigger");
  hEventCut_DG2->GetXaxis()->SetBinLabel(3,"primary vertex > 10");
  hEventCut_DG2->GetXaxis()->SetBinLabel(4,"primary vertex = 0");
  hEventCut_DG2->GetXaxis()->SetBinLabel(5,"pile up");
  hEventCut_DG2->GetXaxis()->SetBinLabel(6,"ntrack < 0");
  hEventCut_DG2->GetXaxis()->SetBinLabel(7,"passed");

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
  filename += "_forRTrig_MBEG2exlusion_tof20_eCross5_newExoticity_wSSHist_noNorm2";
  cout << filename << endl;
  auto fout = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_%llu_%ibins_%s.root",TriggerBit, nbinscluster, filename.Data()), "RECREATE");  


  
  //writing photon info
  hCluster_pt->Write("hCluster_pt");
  hReco_pt->Write("hReco_pt");
  hEventCounts->Write("hEventCounts");
  hMB_centE->Write("hMB_centE");
  hEG2_caloE->Write("hEG2_caloE");
  //hDG2_caloE->Write("hDG2_caloE");
  //hEG2_centE->Write("hEG2_centE");

  hCluster_tof->Write("hCluster_tof");
  hCluster_tof20GeV->Write("hCluster_tof20GeV");
  hExoticity->Write("hExoticity");
  hCellEvClusterE->Write("hCellEvClusterE");
  hNcell->Write("hNcell");
  hNLM->Write("hNLM");
  hD2BC->Write("hD2BC");
  hEta->Write("hEta");
  hPhi->Write("hPhi");
  hShowerShape->Write("hShowerShape");
  
  hZvertex->Write("hZvertex");
  hZvertexAfter->Write("hZvertexAfter");
  hPileUpVertex->Write("hPileUpVertex");
  hEventCut->Write("hEventCut");
  hEventCut_MB->Write("hEventCut_MB");
  hEventCut_DG2->Write("hEventCut_DG2");
  hEventCut_EG2->Write("hEventCut_EG2");
  hClusterCut->Write("hClusterCut");
  hClusterCutFlow->Write("hClusterCutFlow");
  hMultiplicityBefore->Write("hMultiplicityBefore");
  hMultiplicityAfter->Write("hMultiplicityAfter");
  normalizer->Write("hNormalizer");
  fout->Close();  

  return;
  
}

    
void isoPhotonAnalysisData_ppRF(){
  auto start = std::chrono::system_clock::now();
  
  //Input to Run is as follow: Run(const int TriggerBit, TString address, Long64_t firstEvent = 0, Long64_t lastEvent = 10000000000000)
  
/////////////////////////////////////////////////////////////////*/
    //The trigger bit options. Most of 17q does not have 
    //0001 = 01 = MB
    //0010 = 02 = DG2calo
    //0100 = 04 = EG2calo
    //0101 = 05 = MB || EG2calo
    //0110 = 06 = DG2calo || EG2calo
    //0111 = 07 = MB || DG2calo || EG2calo
    //1000 = 08 = EG2cent
    //1100 = 12 = EG2calo || EG2cent
    //1101 = 13 = MB || EG2calo || EG2cent
  //pp data sets

  //calo spectra
  //Run(5, "pp/17q/17q_CENT_wSDD_noThresh_r282365_physel.root");
  //Run(5, "pp/17q/17q_CENT_wSDD_noThresh_r282366_physel.root");
  //Run(5, "pp/17q/17q_CENT_wSDD_noThresh_r282367_physel.root");

  //************************17q ITS-only muon calo runs********************//
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part000.root");//3.3
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part001.root");//25
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part002.root");//21
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part003.root");//2.9
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part004.root");//36
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part005.root");//17
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part006.root");//5.6
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part007.root");//2.5
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part008.root");//5.0
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part009.root");//15
  //Run(4, "pp/17q/17q_ITSonly_noThresh_muonCalo_phySel_part010.root");//15
  
  //Run(1, "pp/17p/17p_CENT_wSDD_10runs_noThresh_part1.root");
  //Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_part2.root");
  
  
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh_r282437.root", false, true);
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh_r282439.root", false, true);
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh_r282440.root", false, true);
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh_r282441.root", false, true);
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh_r282365.root", false, true);
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh_r282365_physel.root", false, true);
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh_r282366_physel.root", false, true);
  //Run(4, "pp/17q/17q_CENT_wSDD_noThresh.root", false, true, 1749493, 4035922);

  //4,035,922 --> starting of EMC good runs
  //1,749,493 to 2,939,337 --> runs 282415-282402
  //Run(1, "pp/17q/17q_CENT_wSDD_noThresh_r282365.root", false, true);
  //Run(1, "pp/17q/17q_CENT_wSDD_noThresh_r282365_physel.root", false, true);
  //Run(1, "pp/17q/17q_CENT_wSDD_noThresh_r282366_physel.root", false, true);
  //Run(1, "pp/17q/17q_CENT_wSDD_noThresh.root", false, true, 4035922);
  

  //***********************17p new list with good runs***************//
  /*Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part1_000.root");
  Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part1_001.root");
  Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part1_002.root");
  Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part1_003.root");
  Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part1_004.root");
  Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part1_005.root");//*/
  
  /*Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part2_000.root");
  Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part2_001.root");
  Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part2_002.root");
  Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part2_003.root");
  Run(1, "pp/17p/17p_CENT_wSDD_5runs_noThresh_phySel_part2_004.root");//*/
  
  /*Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part3_000.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part3_001.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part3_002.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part3_003.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part3_004.root");//*/
  
  /*Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part4_000.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part4_001.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part4_002.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part4_003.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part4_004.root");//*/
  
  /*Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part5_000.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part5_001.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part5_002.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part5_003.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part5_004.root");//*/

  /*Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part6_000.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part6_001.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part6_002.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part6_003.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part6_004.root");//*/

  /*Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part7_000.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part7_001.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part7_002.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part7_003.root");
  Run(1, "pp/17p/17p_CENT_wSDD_4runs_noThresh_phySel_part7_004.root");//*/
  




























  
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
