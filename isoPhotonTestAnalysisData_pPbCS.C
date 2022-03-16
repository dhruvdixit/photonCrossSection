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
  auto hMultiplicityBefore = new TH1F("hMultiplicityBefore", "", 200, 0, 200);
  auto hMultiplicityAfter = new TH1F("hMultiplicityAfter", "", 200, 0, 200);
  auto hUE = new TH1F("hUE", "", 500 , -250, 250);
  auto hUEse = new TH1F("hUEse", "", 500 , -250, 250);
  
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
  const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning
  const int numRuns = 9;
  Double_t runListbins[numRuns+1] = {197258, 197260, 197296, 197297, 197298, 197299, 197300, 197302, 197341, 197342};
  auto hReco_pt  = new TH1F("hReco_pt","", nbinscluster, clusterbins);
  auto hCluster_pt = new TH1F("hCluster_pt", "", nbinscluster, clusterbins);
  auto hEG1_E = new TH1F("hEG1_E", "", nbinscluster, clusterbins);
  auto hEG2_E = new TH1F("hEG2_E", "", nbinscluster, clusterbins);
  auto hMB_E = new TH1F("hMB_E", "", nbinscluster, clusterbins);

  auto hEG1woPurity = new TH1F("hEG1woPurity", "", nbinscluster, clusterbins);
  auto hEG2woPurity = new TH1F("hEG2woPurity", "", nbinscluster, clusterbins);

  auto hEG1Less4Eta = new TH1F("hEG1Less4Eta", "", nbinscluster, clusterbins);
  auto hEG1More4Eta = new TH1F("hEG1More4Eta", "", nbinscluster, clusterbins);
  auto hEG2Less4Eta = new TH1F("hEG2Less4Eta", "", nbinscluster, clusterbins);
  auto hEG2More4Eta = new TH1F("hEG2More4Eta", "", nbinscluster, clusterbins);

  auto hEG1Run197342 = new TH1F("hEG1Run197342", "Run197342", nbinscluster, clusterbins);
  auto hEG1Run197341 = new TH1F("hEG1Run197341", "Run197341", nbinscluster, clusterbins);
  auto hEG1Run197302 = new TH1F("hEG1Run197302", "Run197302", nbinscluster, clusterbins);
  auto hEG1Run197300 = new TH1F("hEG1Run197300", "Run197300", nbinscluster, clusterbins);
  auto hEG1Run197299 = new TH1F("hEG1Run197299", "Run197299", nbinscluster, clusterbins);
  auto hEG1Run197298 = new TH1F("hEG1Run197298", "Run197298", nbinscluster, clusterbins);
  auto hEG1Run197297 = new TH1F("hEG1Run197297", "Run197297", nbinscluster, clusterbins);
  auto hEG1Run197296 = new TH1F("hEG1Run197296", "Run197296", nbinscluster, clusterbins);
  auto hEG1Run197260 = new TH1F("hEG1Run197260", "Run197260", nbinscluster, clusterbins);
  auto hEG1Run197258 = new TH1F("hEG1Run197258", "Run197258", nbinscluster, clusterbins);
  auto hEventPerRun = new TH1F("hEventPerRun", "", numRuns, runListbins);
  auto hEG1woPvsRuns = new TH2F("hEG1woPvsRuns", "", nbinscluster, clusterbins, numRuns, runListbins);

  std::vector<TH1F*> histByRuns;
  std::vector<int> vecRunNumbers;
    
  hEG1Run197258->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG1}dN/dE_{T}");

  for(int i = 1; i < hEventPerRun->GetNbinsX()+1; i++){
    hEventPerRun->GetXaxis()->SetBinLabel(i,Form("%f", runListbins[i-1]));
  }
	
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
  auto foutFly = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/testingHistSave_%llu_%ibins_firstEvent%lld_%s.root",TriggerBit, nbinscluster, firstEvent, filename.Data()), "RECREATE");  

  for (Long64_t ievent= firstEvent;ievent< numEntries ;ievent++) {
    _tree_event->GetEntry(ievent);
    nevent += 1;
    if(ievent%100000==0)
      {
	cout << ievent << "\t" << run_number << endl;
      }

    if(run_number != currentRunNumber){
      if(histByRuns.size() != 0)
	histByRuns.back()->Write(histByRuns.back()->GetName());
      //TH1F* h1 = new TH1F(Form("hEG1_%i", run_number), "Form();E_{T} [GeV];1/N_{ev}^{EG1}dN/dE_{T}", nbinscluster, clusterbins);
      histByRuns.push_back(new TH1F(Form("hEG1_%i", run_number), Form("Run %i;E_{T} [GeV];1/N_{ev}^{EG1}dN/dE_{T}", run_number), nbinscluster, clusterbins));
      cout << histByRuns.back()->GetName() << endl;
      currentRunNumber = run_number;
    }

    for(ULong64_t n=0; n< ncluster; n++){
      histByRuns.back()->Fill(cluster_pt[n]);
    }//end cluster loop
    
  }//loop over events
  foutFly->Close();

  std::vector<Double_t> xx;
  //Writing to file
  filename += "_wRunByRunHists_tests";
  cout << filename << endl;
  TFile* fout = TFile::Open(Form("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_%llu_%ibins_firstEvent%lld_%s.root",TriggerBit, nbinscluster, firstEvent, filename.Data()), "RECREATE");  


  
  //writing photon info
  fout->WriteObject(&xx, "xx");
  //fout->WriteObject(&histByRuns, "histByRuns");
  fout->Close();
  return;
  
}

    
void isoPhotonTestAnalysisData_pPbCS(){
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
  Run(6, "pPb/13f/13f_part1_kEMCEGA_kINT7_mannualMode_greenlight_nonLinCorr.root");
  
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
