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

bool ptDepShowerShapeCut(Float_t clus_pt, Float_t lambda2){
  //bool passShowerShape = true;
  
  if(lambda2 < 0.1)
    return false;
  
  if((clus_pt > 10 && clus_pt < 12) && lambda2 > 0.40)
    return false;

  if((clus_pt > 12 && clus_pt < 14) && lambda2 > 0.35)
    return false;

  if((clus_pt > 14 && clus_pt < 16) && lambda2 > 0.32)
    return false;

  if((clus_pt > 16 && clus_pt < 60) && lambda2 > 0.30)
    return false;


  return true;
}


double purityWeights(Float_t clus_pt, TString system){
  
  if(system == "pPb"){
    if(clus_pt < 12)
      return 0.18;
    
    if(clus_pt > 12 && clus_pt < 14)
      return 0.21;
    
    if(clus_pt > 14 && clus_pt < 16)
      return 0.244;
    
    if(clus_pt > 16 && clus_pt < 18)
      return 0.349;
    
    if(clus_pt > 18 && clus_pt < 20)
      return 0.393;
    
    if(clus_pt > 20 && clus_pt < 25)
      return 0.498;
    
    if(clus_pt > 25 && clus_pt < 30)
      return 0.527;
    
    if(clus_pt > 30 && clus_pt < 40)
      return 0.527;
    
    if(clus_pt > 40 && clus_pt < 60)
      return 0.527;
  }

  
  //if(system == "pp"){
    
  //}

  return -1.0;
}

Float_t Get_Purity_ErrFunction(Float_t pT_GeV, std::string deviation = "") {

  Float_t purity_val = 0;

  //Non-platue assumption
  // Float_t par[3] = {0.548247710,
  //                   8.794543375,
  //                   12.7423900};

  //Old
//   Float_t par[3] = {0.54225742923,
//                     8.09242373515,
//                     11.8085154181};

  Float_t par[3] = {0.494981,
		    9.11279,
		    11.0498};

  if (strcmp(deviation.data(),"Plus")==0){
    par[0] = 0.60750016509;
    par[1] = 7.05184155403;
    par[2] = 13.6116163603;
  }

  if (strcmp(deviation.data(),"Minus")==0){
    par[0] = 0.479958593235;
    par[1] = 9.05392932723;
    par[2] = 10.2061359452;
  }


  purity_val = par[0]*TMath::Erf((pT_GeV-par[1])/par[2]);
  return purity_val;
}


void Run(ULong64_t TriggerBit, TString address, bool nonLinCorrOn = false, bool forRtrig = false){

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
  
  if(nonLinCorrOn){ cout << "using Nonlinearlity Correction" << endl;}
  const Int_t kMax = 5000;
  
  Double_t primary_vertex[3];
  Bool_t is_pileup_from_spd_5_08;
  Bool_t is_pileup_from_spd_3_08;
  Bool_t is_incomplete_daq;
  Float_t ue_estimate_its_const;
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

  float eg_cross_section;//
  int eg_ntrial;//
  
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
  



  auto hITSclus = new TH1F("hITSclus", "", 7, -0.5, 6.5);
  auto hITSclus_fake = new TH1F("hITSclus_fake", "", 7, -0.5, 6.5);

  auto hIso_ITS = new TH1F("hIso_ITS","", 25, -10, 40);
  auto hIso_TPC = new TH1F("hIso_TPC","", 25, -10, 40);  
  auto hIso_Truth = new TH1F("hIso_Truth","", 25, -10, 40);
  
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

  hZvertex->Sumw2();
  hZvertexAfter->Sumw2();
  hHitsITS->SetTitle(";Layers hit; counts");

  //Photon
  const int nbinscluster = 15;
  //Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning
  //Double_t clusterbins[nbinscluster+1] = {0.00, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 11.00, 12.00, 13.00, 14.00, 15.00, 16.00, 17.00, 18.00, 20.00, 22.00, 26.00, 30.00, 35.00, 40.00, 50.00, 60.00};//nbinscluster = 26, rejection factor binning
  Double_t clusterbins[nbinscluster+1] = {0.00, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 14.00, 18.00, 25.00, 40.00, 60.00};//nbinscluster = 15
  
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

  const double maxEta = 0.8;
 
  const ULong64_t one1 = 1;
  const int numTrigs = 5; 
  /*//////////////////////////////////////////////////////////////////////////////////
    17q triggers
 //////////////////////////////////////////////////////////////////////////////////*/
  ULong64_t trigMask_17q_trigs1[numTrigs] = {0};//0 = MB, 1 = DG2, 2 = EG2
  trigMask_17q_trigs1[0] = (one1 << 21);//MB calo
  trigMask_17q_trigs1[1] = (one1 << 30);//DG2 calo
  trigMask_17q_trigs1[2] = (one1 << 27);//EG2 calo

  ULong64_t trigMask_17q_trigs2[numTrigs] = {0};//0 = MB, 1 = DG2, 2 = EG2
  trigMask_17q_trigs2[0] = (one1 << 19);//MB calo
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
  ULong64_t trigMask_17p_trigs1[numTrigs] = {0};//0 = fast, 1 = cent
  trigMask_17p_trigs1[0] = (one1 << 0) | (one1 << 2);//fast | cent
  //trigMask_17p_trigs1[1] = (one1 << 2);//cent
  //trigMask_17p_trigs1[2] = (one1 << 27);//centnotrd

  ULong64_t trigMask_17p_trigs2[numTrigs] = {0};//0 = fast, 1 = cent
  trigMask_17p_trigs2[0] = (one1 << 0) | (one1 << 3);//fast | cent
  //trigMask_17p_trigs2[1] = (one1 << 3);//cent
  //trigMask_17p_trigs2[2] = (one1 << 23);//EG2 calo

  ULong64_t trigMask_17p_trigs3[numTrigs] = {0};//0 = fast, 1 = cent
  //trigMask_17p_trigs3[0] = (one1 << 0);//fast
  trigMask_17p_trigs3[1] = (one1 << 0);//cent
  //trigMask_17p_trigs2[2] = (one1 << 23);//EG2 calo
  
  ULong64_t trigMask[numTrigs] = {0};

  Long64_t totEvents = _tree_event->GetEntries();
  numEvents_tot = totEvents;
  Long64_t restrictEvents = 4035922;//4035922 --> starting of EMC good runs
  //1749493 to 2939337 --> runs 282415-282402
  Long64_t numEntries = TMath::Min(totEvents,restrictEvents);
  std::cout << numEntries << std::endl;
  double RN = 0.0;
  for (Long64_t ievent = 2939338; ievent< numEntries ;ievent++) {
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

    bool eventChange = true;
    bool isMBcalo, isDG2calo, isEG2calo, isEG2cent;
    isMBcalo = isDG2calo = isEG2calo = isEG2cent = false;
    
    
    
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
    if(run_number >= 282008 && run_number <= 282031)
      std::memcpy(trigMask, trigMask_17p_trigs1, sizeof(trigMask));
    if(run_number >= 282050 && run_number <= 282098)
      std::memcpy(trigMask, trigMask_17p_trigs1, sizeof(trigMask));
    
    //17q
    if(run_number >= 282391 && run_number <= 282441)
      std::memcpy(trigMask, trigMask_17q_trigs1, sizeof(trigMask));
    if(run_number == 282415 || run_number == 282411 || run_number == 282402)
      std::memcpy(trigMask, trigMask_17q_trigs2, sizeof(trigMask));
    if(run_number == 282367 || run_number == 282366 || run_number == 282365)//EMC good runs 
      std::memcpy(trigMask, trigMask_17q_trigs3, sizeof(trigMask));
    
    
    
    ULong64_t localTrigBit = 0;
    if(not ((trigMask[0] & trigger_mask[0]) == 0)){//MB selection
      localTrigBit |= (1 << 0);
    }
    
    if(run_number > 282098){
      if(run_number == 282367 || run_number == 282366 || run_number == 282365){
	if(not ((trigMask[2] & trigger_mask[0]) == 0)){//EG2 cent
	  localTrigBit |= (1 << 3); 
	}
	if(not ((trigMask[4] & trigger_mask[1]) == 0)){//EG2 calo
	  localTrigBit |= (1 << 2); 
	}
	//cout << "location 1" << endl;
      }
      else{
	if(not ((trigMask[2] & trigger_mask[0]) == 0)){//EG2 calo
	  localTrigBit |= (1 << 2); 
	}
      }
	
    }

    //cout << trigger_mask[0] << "\t" << trigMask[2] << endl;
    //cout << "\t" << trigger_mask[1] << "\t" << trigMask[4] << endl;
    
    //The trigger bit options. Most of 17q have min bias
    //001 = 1 = MB
    //010 = 2 = DG2
    //100 = 4 = EG2
    //110 = 6 = DG2||EG2
    //111 = 7 = MB||DG2||EG2
    if((localTrigBit & 1) != 0) {isMBcalo = true; hEventCut_MB->Fill(0);numEvents_MBcent_before++;}
    if((localTrigBit & 2) != 0) {isDG2calo = true;hEventCut_DG2->Fill(0);numEvents_DG2calo_before++;}
    if((localTrigBit & 4) != 0) {isEG2calo = true;hEventCut_EG2->Fill(0);numEvents_EG2calo_before++;}
    if((localTrigBit & 8) != 0) {isEG2cent = true;hEventCut_EG2cent->Fill(0);numEvents_EG2cent_before++;}
    
    
    if((localTrigBit & TriggerBit) == 0) {
      hEventCut->Fill(1);
      if(isMBcalo) hEventCut_MB->Fill(1);
      if(isDG2calo) hEventCut_DG2->Fill(1);
      if(isEG2calo) hEventCut_EG2->Fill(1);
      if(isEG2cent) hEventCut_EG2cent->Fill(1);
      //cout << "fail trig" << endl;
      continue;}//no emcal triggers*/
    if((localTrigBit & TriggerBit) != 0) {
      //cout << "localTrigBit\t" << localTrigBit << endl;
      //cout << "is EG calo or EG cent " << endl;
      numEvents_passTrig++;
    }
    
    if(not( TMath::Abs(primary_vertex[2])<10.0)){
      hEventCut->Fill(2);
      if(isMBcalo) hEventCut_MB->Fill(2);
      if(isDG2calo) hEventCut_DG2->Fill(2);
      if(isEG2calo) hEventCut_EG2->Fill(2);
      if(isEG2cent) hEventCut_EG2cent->Fill(2);
      
      numEvents_Zmore10++;
      continue;
    } //vertex z position
    
    if(primary_vertex[2] == 0.0000) {
      hEventCut->Fill(3);
      if(isMBcalo) hEventCut_MB->Fill(3);
      if(isDG2calo) hEventCut_DG2->Fill(3);
      if(isEG2calo) hEventCut_EG2->Fill(3);
      if(isEG2cent) hEventCut_EG2cent->Fill(3);
      
      numEvents_noZ++;
      continue;}//removes no vertex found
    
    if(is_pileup_from_spd_5_08) {
      hEventCut->Fill(4);
      if(isMBcalo) hEventCut_MB->Fill(4);
      if(isDG2calo) hEventCut_DG2->Fill(4);
      if(isEG2calo) hEventCut_EG2->Fill(4);
      if(isEG2cent) hEventCut_EG2cent->Fill(4);
      continue;
    } //removes pileup*/
    
    /*if(not(ncluster > 0)) {
      hEventCut->Fill(5);
      if(isMBcalo) hEventCut_MB->Fill(5);
      if(isDG2calo) hEventCut_DG2->Fill(5);
      if(isEG2calo) hEventCut_EG2->Fill(5);
      continue;
      } //no track*/
    //if(is_incomplete_daq){hEventCut->Fill(5); continue;}
    
    
    hEventCut->Fill(6);//all cuts
    if(isMBcalo) {hEventCut_MB->Fill(6); numEvents_MBcent++;}
    if(isDG2calo) {hEventCut_DG2->Fill(6); numEvents_DG2calo++;}
    if(isEG2calo) {hEventCut_EG2->Fill(6); numEvents_EG2calo++;}
    if(isEG2cent) {hEventCut_EG2cent->Fill(6); numEvents_EG2cent++;}
    
    
    hZvertexAfter->Fill(primary_vertex[2]);
    hMultiplicityAfter->Fill(multp_sum);
    numEvents_Zless10++;
    numEvents_passAll++;
    
    
    int eventFill = 0;    
    hEventCounts->Fill(eventFill);
    //cout << "pass event selection" << endl;

    //continue;
    
    eventChange = true;
    bool eventChange2 = true;
    //Loop over clusters
    //if(ncluster > 0)
    //cout << "Event number: " << ievent << "Num clusters: " << ncluster << endl;
    for(ULong64_t n=0; n< ncluster; n++)
      {
	double isolation = cluster_iso_its_04[n] + cluster_iso_its_04_ue[n];             //remove UE subtraction
	isolation = isolation - ue_estimate_its_const*0.4*0.4*TMath::Pi();               //Use rhoxA subtraction

	Float_t clusterPt = 0.0;
	Float_t clusterE = 0.0;
	Float_t clusterEta = 0.0;
	Float_t clusterPhi = 0.0;
	
	if(nonLinCorrOn){
	  clusterPt = cluster_pt_nonLinCorr[n];
	  clusterE = cluster_e_nonLinCorr[n];
	  clusterEta = cluster_eta_nonLinCorr[n];
	  clusterPhi = cluster_phi_nonLinCorr[n];
	}
	else{
	  clusterPt = cluster_pt[n];
	  clusterE = cluster_e[n];
	  clusterEta = cluster_eta[n];
	  clusterPhi = cluster_phi[n];
	}
	//cout << clusterPt << endl;

	
	//Photon Selection
	/*////////////////////////////////////////
	  Bit  Cut
	  0    ncell>=2
	  1    exoticity>0.03
	  2    nlocalmaxima<=2
	  3    dist2badchn >= 1
	  4    |tof| < 20 ns
	  5    isoation: E < 1.5 GeV r = 0.4
	  6    shower shape cut: 0.1 < lambda < 0.3
	  7    |eta| < 0.667
	  8    1.396 < phi < 3.28
	////////////////////////////////////////*/
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
	if( ((cluster_e_cross[n]/clusterE)>0.03)){
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

	//Isolation and shower shape selection:
	if( (isolation < 1.5)){
	  clusterCutBits |= (1 << 5); hClusterCut->Fill(6);
	} clusterCutPassed |= (1 << 5); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(6);//isolation r = 0.4 and energy < 2
	if((cluster_lambda_square[n][0] > 0.1) && (cluster_lambda_square[n][0] < 0.3)){
	  clusterCutBits |= (1 << 6); hClusterCut->Fill(7);
	} clusterCutPassed |= (1 << 6); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(7);//single-photon selection, not merged
	//cout << clusterCutBits << "\t" << clusterCutPassed << endl;

	//fiducial cut
	if((TMath::Abs(clusterEta)) < 0.67){
	  clusterCutBits |= (1 << 7); hClusterCut->Fill(8);
	} clusterCutPassed |= (1 << 7); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(8);//eta cut
	if((clusterPhi > 1.396) && (clusterPhi <3.28)){
	  clusterCutBits |= (1 << 8); hClusterCut->Fill(9);
	} clusterCutPassed |= (1 << 8); if(clusterCutBits == clusterCutPassed) hClusterCutFlow->Fill(9);//phi cut
	

	if(!forRtrig)
	  if((clusterCutBits != clusterCutPassed) || (clusterCutBits == 0))
	    continue;
	
	if(ievent%1000==0)
	  {
	    std::cout << "cluster accepted" << std::endl;
	    
	  }

	hClusterCut->Fill(10);
	hClusterCutFlow->Fill(10);
	numClustersPost++;

	//double purity = purityWeights(clusterPt, "pPb");
	double purity = Get_Purity_ErrFunction(clusterPt);
	if(forRtrig)
	  purity = 1;
	
	hReco_pt->Fill(clusterPt);
	if((localTrigBit & 1) != 0) {
	  hMB_centE->Fill(clusterPt,purity);
	  
	}
	if((localTrigBit & 2) != 0) hDG2_caloE->Fill(clusterPt, purity);
	if((localTrigBit & 4) != 0) {
	  numClusters_EG2_caloE++;
	  hEG2_caloE->Fill(clusterPt, purity);
	}
	if((localTrigBit & 8) != 0) {
	  numClusters_EG2_centE++;
	  hEG2_centE->Fill(clusterPt, purity);
	}
	hCluster_pt->Fill(clusterPt,purity);
	numClusters_clusterpt++;
	//cout << "cluster pt filling\t" << n << endl;
	hIso_ITS->Fill(cluster_iso_its_04[n]);
	hIso_TPC->Fill(cluster_iso_tpc_04[n]);
	hIso_Truth->Fill(cluster_iso_04_truth[n]);
	
      }
    
    
  }//loop over events
  std::cout << " END LOOP  " << std::endl;
  cout << "total events: " << numEvents_tot << endl;
  cout << "total/minbias/DG2/EG2calo/EG2cent events:" << endl;
  cout << "before:" << "\t" << numEvents_passTrig << "\t" << numEvents_MBcent_before << "\t" << numEvents_DG2calo_before << "\t" << numEvents_EG2calo_before << "\t" << numEvents_EG2cent_before << endl;
  cout << "after:" << "\t"  << numEvents_passAll << "\t" << numEvents_MBcent << "\t" << numEvents_DG2calo << "\t" << numEvents_EG2calo << "\t" << numEvents_EG2cent << endl;  
  cout << "cluster pt clusters: " << numClusters_clusterpt << "\tEG2_caloE clusters: " << numClusters_EG2_caloE << "\tEG2_centE clusters: " << numClusters_EG2_centE << endl;

  
  //Normalizing the bins and getting yaxsis to be 1/Nevt*dN/dptdeta
  //cout << filename(0,3) << "\tTotal Events: " << numEntries << "\tEvent selection: " << numEvents_passAll << "\tPre-Cluster selection: " << numClustersPre << "\tPostCluster selection: " << numClustersPost << endl;
  const double deltaEta = 1.334;
  const double deltaPhi = 1.884;
  double acceptanceNorm = 2*TMath::Pi()/(deltaEta*deltaPhi);

  //Adjusting event scaling for pp
  //cout << numEvents_passAll << "\t" << numEvents_Zless10 << "\t" << numEvents_Zmore10 << "\t" << numEvents_noZ << "\t";
  //numEvents_passAll = numEvents_Zless10+(numEvents_Zless10/(numEvents_Zless10 + numEvents_Zmore10))*numEvents_noZ;
  //cout << numEvents_passAll << endl;
  

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
  
  //scaling for clusters
  for(int i = 1; i <  hCluster_pt->GetNbinsX()+1; i++)
    {
      double dpt = hCluster_pt->GetBinWidth(i);
      
      double content = hCluster_pt->GetBinContent(i);
      double temp = (content*acceptanceNorm)/((double)numEvents_passAll*dpt);
      hCluster_pt->SetBinContent(i, temp);
      double error = hCluster_pt->GetBinError(i);
      double tempErr = (error*acceptanceNorm)/((double)numEvents_passAll*dpt);
      hCluster_pt->SetBinError(i, tempErr);
    }//*/
  
  for(int i = 1; i <  hReco_pt->GetNbinsX()+1; i++)
    {
      double dpt = hReco_pt->GetBinWidth(i);
      double content = hReco_pt->GetBinContent(i);
      double temp = (content*acceptanceNorm)/((double)numEvents_passAll*dpt);
      //double temp = content/((double)numEvents_passAll*dpt);
      //cout << dpt << "\t" << content << "\t" << temp << endl;
      //double temp = content/dpt;
      hReco_pt->SetBinContent(i, temp);
      
      double error = hReco_pt->GetBinError(i);
      double tempErr = (error*acceptanceNorm)/((double)numEvents_passAll*dpt);
      //double tempErr = error/dpt;
      hReco_pt->SetBinError(i, tempErr);
    }//*/
  
  
  if(forRtrig){
    acceptanceNorm = 1;
    filename += "_RtrigAnalysis";
  }
  
  for(int i = 1; i < hMB_centE->GetNbinsX()+1; i++){
    double dE = hMB_centE->GetBinWidth(i);
    
    double contentMB = hMB_centE->GetBinContent(i);
    double tempMB = (contentMB*acceptanceNorm)/((double)numEvents_MBcent*dE);
    double errorMB = hMB_centE->GetBinError(i);
    double tempErrMB = (errorMB*acceptanceNorm)/((double)numEvents_MBcent*dE);
    if(numEvents_MBcent) 
      {
	hMB_centE->SetBinContent(i,tempMB);
	hMB_centE->SetBinError(i, tempErrMB);
      }
    
    double contentDG2 = hDG2_caloE->GetBinContent(i);
    double tempDG2 = (contentDG2*acceptanceNorm);///((double)numEvents_DG2calo*dE);
    double errorDG2 = hDG2_caloE->GetBinError(i);
    double tempErrDG2 = (errorDG2*acceptanceNorm)/((double)numEvents_DG2calo*dE);
    if(numEvents_DG2calo) 
      {
	hDG2_caloE->SetBinContent(i,tempDG2);
	hDG2_caloE->SetBinError(i, tempErrDG2);
      }
    
    double contentEG2 = hEG2_caloE->GetBinContent(i);
    double tempEG2 = (contentEG2*acceptanceNorm)/((double)numEvents_EG2calo*dE);
    double errorEG2 = hEG2_caloE->GetBinError(i);
    double tempErrEG2 = (errorEG2*acceptanceNorm)/((double)numEvents_EG2calo*dE);
    if(numEvents_EG2calo) 
      {
	hEG2_caloE->SetBinContent(i,tempEG2);
	  hEG2_caloE->SetBinError(i, tempErrEG2);
      }

    double contentEG2cent = hEG2_centE->GetBinContent(i);
    double tempEG2cent = (contentEG2cent*acceptanceNorm)/((double)numEvents_EG2cent*dE);
    double errorEG2cent = hEG2_centE->GetBinError(i);
    double tempErrEG2cent = (errorEG2cent*acceptanceNorm)/((double)numEvents_EG2cent*dE);
    if(numEvents_EG2cent) 
      {
	hEG2_centE->SetBinContent(i,tempEG2cent);
	hEG2_centE->SetBinError(i, tempErrEG2cent);
      }
    
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
  //filename += "_cluster_EMCandDMCTrigOnly_1Mevent_wTripPileupSkimEGCut_MBDG2EG2seperate_purityCorr_etaPhiAcceptancenew_EG2caloOnly";
  filename += "_MB_Normalized_allEMCgoodOnly_bugFixed2_399to391";
  auto fout = new TFile(Form("isoPhotonOutput/fout_%llu_%ibins_%s.root",TriggerBit, nbinscluster, filename.Data()), "RECREATE");  


  
  //writing photon info
  hCluster_pt->Write("hCluster_pt");
  hReco_pt->Write("hReco_pt");
  hEventCounts->Write("hEventCounts");
  hMB_centE->Write("hMB_centE");
  hDG2_caloE->Write("hDG2_caloE");
  hEG2_caloE->Write("hEG2_caloE");
  hEG2_centE->Write("hEG2_centE");

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

    
void isoPhotonAnalysisData_pp(){
  auto start = std::chrono::system_clock::now();
  
  //Input to Run is as follow: Run(const int TriggerBit, TString address, bool nonLinCorrOn = false, bool forRtrig = false)
  
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
  //pp data sets
  //Run(16, "pp/17q/17q_CENT_wSDD_3run_forTrig_noEThresh.root", false, true, true);
  //Run(16, "pp/17q/17q.root", false);
  //Run(16, "pp/17q/17q_wSDD.root", false);
  //Run(16, "pp/17q/17q_CENT_wSDD_noThresh_1EMCGoodRuns.root", false);
  //Run(16, "pp/17q/17q_CENT_wSDD_noThresh.root");


  //Run(13, "pp/17q/17q_CENT_wSDD_noThresh.root", false, true);//First EMC goodrun event:4035922
  //Run(12, "pp/17q/17q_CENT_wSDD_noThresh.root", false, false);//First EMC goodrun event:4035922
  //Run(04, "pp/17q/17q_CENT_wSDD_noThresh.root", false, true);//First EMC goodrun event:4035922
  //Run(1, "pp/17p/17p_CENT_wSDD_10runs_noThresh.root", false, true);//First event with clusters: 2483971

  Run(04, "pp/17q/17q_CENT_wSDD_noThresh.root", false, true);//breaking it down in 4 groups
  //Run(04, "pp/17q/17q_CENT_wSDD_noThresh.root", false, false);//breaking it down in 4 groups
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
