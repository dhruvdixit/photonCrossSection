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
#include <chrono>
#include <ctime> 

double SetPthatWeights(TString MCname, double Xsection, double ntrial)
{

  //General purpose MC need no weights
  if(MCname(0,4) == "13b2" || MCname(0,4) == "17l4" || MCname(0,4) == "17l3" || MCname(0,4) == "16k5")
    return 1;
   
  //17g6a3 weights
  if(MCname == "17g6a3_pthat1")
    return 4.47e-11;
  if(MCname == "17g6a3_pthat2")
    return 9.83e-11;
  if(MCname == "17g6a3_pthat3")
    return 1.04e-10;
  if(MCname == "17g6a3_pthat4")
    return 1.01e-10;
  if(MCname == "17g6a3_pthat5")
    return 6.93e-11;
  if(MCname == "17g6a3_pthat6")
    return 5.13e-11;
  if(MCname == "17g6a3_pthat7")
    return 3.03e-11;
  if(MCname == "17g6a3_pthat8")
    return 1.89e-11;
  
  //17g6a1 weights
  if(MCname == "17g6a1_pthat1")
    return 1.60e-11;
  if(MCname == "17g6a1_pthat2")
    return 2.72e-12;
  if(MCname == "17g6a1_pthat3")
    return 3.69e-13;
  if(MCname == "17g6a1_pthat4")
    return 6.14e-14;
  if(MCname == "17g6a1_pthat5")
    return 1.27e-14;
  

  //18b10ab, 18g7a
  if(MCname(0,2) == "18" || MCname(0,2) == "16")
    return Xsection/ntrial;
 
  return 0.0;
  
}

void Run(TString address, Long64_t firstEvent = 0, Long64_t lastEvent = 1000000000000000){

  gStyle->SetOptStat(0);

  //SetAtlasStyle();
  TString filename = address(address.Last('/')+1,address.Last('.')-address.Last('/')-1);
  TString ntupleName = address(address.Last('/')+1,address.First('_')-address.Last('/')+6);
  
  TFile* f;
  f = TFile::Open(Form("/project/projectdirs/alice/NTuples/MC/%s",address.Data()),"READ");

  cout << Form("/project/projectdirs/alice/NTuples/MC/%s",address.Data()) << endl;

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
  Float_t ue_estimate_its_const_se;
  int npileup_vertex_spd;
  int run_number;
  unsigned int ntrack;
  Float_t multiplicity_v0[64];
  Float_t eg_cross_section;
  Int_t   eg_ntrial;

  UInt_t ncluster;
  Float_t cluster_e[kMax];
  Float_t cluster_pt[kMax];
  Float_t cluster_eta[kMax];
  Float_t cluster_phi[kMax];
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

  //MC
  unsigned int nmc_truth;
  Float_t mc_truth_pt[kMax];
  Float_t mc_truth_eta[kMax];
  Float_t mc_truth_phi[kMax];
  short mc_truth_pdg_code[kMax];
  short mc_truth_first_parent_pdg_code[kMax];
  char mc_truth_charge[kMax];
  UChar_t mc_truth_status[kMax];
  
  Float_t mc_truth_first_parent_e[kMax];
  Float_t mc_truth_first_parent_pt[kMax];
  Float_t mc_truth_first_parent_eta[kMax];
  Float_t mc_truth_first_parent_phi[kMax];
  
  _tree_event->SetBranchAddress("primary_vertex", primary_vertex);
  _tree_event->SetBranchAddress("is_pileup_from_spd_5_08", &is_pileup_from_spd_5_08);
  _tree_event->SetBranchAddress("is_pileup_from_spd_3_08", &is_pileup_from_spd_3_08);
  _tree_event->SetBranchAddress("ue_estimate_its_const", &ue_estimate_its_const);
  _tree_event->SetBranchAddress("ue_estimate_its_const_se", &ue_estimate_its_const_se);
  _tree_event->SetBranchAddress("run_number", &run_number);
  _tree_event->SetBranchAddress("npileup_vertex_spd", &npileup_vertex_spd);
  _tree_event->SetBranchAddress("ntrack", &ntrack);
  _tree_event->SetBranchAddress("multiplicity_v0", multiplicity_v0);
  _tree_event->SetBranchAddress("eg_cross_section",&eg_cross_section);
  _tree_event->SetBranchAddress("eg_ntrial",&eg_ntrial);
    
  _tree_event->SetBranchAddress("ncluster", &ncluster);
  _tree_event->SetBranchAddress("cluster_e", cluster_e);
  _tree_event->SetBranchAddress("cluster_pt", cluster_pt); // here
  _tree_event->SetBranchAddress("cluster_eta", cluster_eta);
  _tree_event->SetBranchAddress("cluster_phi", cluster_phi);
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

  //MC
  _tree_event->SetBranchAddress("nmc_truth", &nmc_truth);
  _tree_event->SetBranchAddress("mc_truth_pdg_code", mc_truth_pdg_code);
  _tree_event->SetBranchAddress("mc_truth_pt", mc_truth_pt);
  _tree_event->SetBranchAddress("mc_truth_phi", mc_truth_phi);
  _tree_event->SetBranchAddress("mc_truth_eta", mc_truth_eta);
  _tree_event->SetBranchAddress("mc_truth_status", mc_truth_status);        
  _tree_event->SetBranchAddress("mc_truth_first_parent_pdg_code",mc_truth_first_parent_pdg_code);
    
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

  const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning

  //Results histograms
  TH1F* hRecoPure = new TH1F("hRecoPure", ";p_{T}^{rec} [GeV/c];dN^{rec}_{#gamma_{iso}}/dp_{T}^{rec}", nbinscluster, clusterbins);
  TH1F* hReco = new TH1F("hReco", ";p_{T}^{rec} [GeV/c];dN^{rec}_{#gamma_{iso}}/dp_{T}^{rec}", nbinscluster, clusterbins);
  TH1F* hTruth = new TH1F("hTruth", ";p_{T}^{tru} [GeV/c];dN^{gen}_{#gamma_{iso}}/dp_{T}^{tru}", nbinscluster, clusterbins);
  TH1F* hRecoTruth = new TH1F("hRecoTruth", ";p_{T}^{rectru} [GeV/c];dN^{rectru}_{#gamma_{iso}}/dp_{T}^{rectru}", nbinscluster, clusterbins);
  TH1F* hTotalEfficiency = new TH1F("hTotalEfficiency", ";p_{T}^{rec} [GeV/c];\epsilon^{iso}_{#gamma}", nbinscluster, clusterbins);
  TH1F* hEfficiency = new TH1F("hEfficiency", ";p_{T}^{tru} [GeV/c];#epsilon^{iso}_{#gamma}", nbinscluster, clusterbins);
  TH1F* hBinMigration = new TH1F("hBinMigration", ";p_{T}^{rec} [GeV/c]; reco/truth", nbinscluster, clusterbins);
  TH1F* hSpectra = new TH1F("hSpectra", ";p_{T}^{rec} [GeV/c]; 1/N_{evt} dN/dE_{T}", nbinscluster, clusterbins);
  
  TH2F* hCorrelation = new TH2F("hCorrelation", ";p_{T}^{rectru}; p_{T}^{rec}", nbinscluster, clusterbins, nbinscluster, clusterbins);

  //Variable distribution histograms
  TH1F* hZvertex = new TH1F("hZvertex", ";z_{v} [cm]; counts", 60, -30, -30);

  //Counting varibales
  int numEvents = 0;
  int numEvents_tot = 0;
  
  Long64_t totEvents = _tree_event->GetEntries();
  numEvents_tot = totEvents;
  Long64_t restrictEvents = lastEvent;
  Long64_t numEntries = TMath::Min(totEvents,restrictEvents);
  std::cout << numEntries << std::endl;
  for (Long64_t ievent = firstEvent; ievent< numEntries ;ievent++) {
    _tree_event->GetEntry(ievent);
      if(ievent%100000==0)
      {
	std::cout << ievent << std::endl;
	cout << run_number << endl;
      }

    //Event selection
    if(not(TMath::Abs(primary_vertex[2])<10.0)) continue; //vertex z position
    if(primary_vertex[2] == 0.000000) continue;
    hZvertex->Fill(primary_vertex[2]);
    numEvents++;
    
    //Obtainging pthat bin weights
    double weight = SetPthatWeights(ntupleName, (double)eg_cross_section, (double)eg_ntrial);
    if(ievent%10000 == 0)
      {
	cout << weight << endl;
	cout << ntupleName.Data() << endl;
	cout << ievent << endl;
      }

    for (ULong64_t n = 0; n < ncluster; n++) {
      //Photon Selection
      double isolation = cluster_iso_its_04[n] + cluster_iso_its_04_ue[n];             //remove UE subtraction
      isolation = isolation - ue_estimate_its_const*0.4*0.4*TMath::Pi();               //Use rhoxA subtraction
      bool isoPassed = false;
      
      //cluster cuts
      if(not (cluster_ncell[n]>=2)) continue;
      if(not (cluster_e_cross[n]/cluster_e_max[n]>0.05)) continue;
      if(not (cluster_nlocal_maxima[n]<= 2)) continue;
      if(not (cluster_distance_to_bad_channel[n]>=1))continue;
      //if(not ((cluster_tof[n] > -20) && (cluster_tof[n] < 20))) continue;

      //acceptance cuts
      if(not (TMath::Abs(cluster_eta[n] < 0.67))) continue;
      if(not (1.396 < cluster_phi[n] && cluster_phi[n] < 3.28)) continue;

      //shower shape and isolation
      if(not (( 0.1 < cluster_lambda_square[n][0]) &&  ( 0.3 > cluster_lambda_square[n][0]))) continue;
      if(not (isolation < 1.5)) continue;

      hRecoPure->Fill(cluster_pt[n]);
      // Access the corresonding mc_truth particle; skip if index is 65535, which is invalid, or the truth particle pT is less than 10, or the mc_truth_pdg_code is not 22 (it's not a photon)
      Bool_t isTruePhoton = false;
      Float_t truth_pt = -999.0;
      Float_t truth_eta = -999.0;
      Float_t truth_phi = -999.0;
      
      for(int counter = 0 ; counter<32; counter++){
	unsigned short index = cluster_mc_truth_index[n][counter];                   
	if(isTruePhoton) break;
	if(index==65535) continue;
	if(mc_truth_pdg_code[index]!=22) continue;
	if(mc_truth_first_parent_pdg_code[index]!=22) continue;
	if( not (mc_truth_status[index] >0)) continue;        
	isTruePhoton = true;
	truth_pt     = mc_truth_pt[index];
	truth_phi    = mc_truth_phi[index];
	truth_eta    = mc_truth_eta[index];
      }//end loop over indices
      
      if(isTruePhoton){
	hReco->Fill(cluster_pt[n], weight);
	hRecoTruth->Fill(truth_pt, weight);
	hCorrelation->Fill(truth_pt, cluster_pt[n], weight);
      }//end isTruePhoton 
    }//end loop on clusters

    //loop over truth particles for clusters
    for (ULong64_t nmc = 0; nmc < nmc_truth; nmc++) {

      //acceptance cuts
      if(not (TMath::Abs(mc_truth_eta[nmc] < 0.67))) continue;
      if(not (1.396 < mc_truth_phi[nmc] && mc_truth_phi[nmc] < 3.28)) continue;

      //real photon cuts
      if(mc_truth_pdg_code[nmc]!=22) continue;
      if(mc_truth_first_parent_pdg_code[nmc]!=22) continue;
      if(not (mc_truth_status[nmc] >0)) continue; 
      {
	hTruth->Fill(mc_truth_pt[nmc],weight);		
      }
    }//end loop over mc truth particle
    
  }//loop over events
  
  //Writing to file
  filename += "_noNorm";
  cout << filename << endl;
  auto fout = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/fout_%ibins_firstEvent%lld_%s.root", nbinscluster, firstEvent, filename.Data()), "RECREATE");  

  hReco->Write("hReco");
  hRecoPure->Write("hRecoPure");
  hRecoTruth->Write("hRecoTruth");
  hTruth->Write("hTruth");
  hCorrelation->Write("hCorrelation");
  
  //writing photon info
  

  return;
  
}

    
void isoPhotonAnalysisMC(){
  auto start = std::chrono::system_clock::now();
  
  //Input to Run is as follow: Run(TString address, Long64_t firstEvent = 0, Long64_t lastEvent = 1000000000000000)

  //pPb
  /*Run("17g6a1/17g6a1_pthat1_wNeutrals.root", 0, 1000000);
  Run("17g6a1/17g6a1_pthat2_wNeutrals.root", 0, 1000000);
  Run("17g6a1/17g6a1_pthat3_wNeutrals.root", 0, 1000000);
  Run("17g6a1/17g6a1_pthat4_wNeutrals.root", 0, 1000000);
  Run("17g6a1/17g6a1_pthat5_wNeutrals.root", 0, 1000000);//*/

  Run("18b10a/18b10a_calo_pthat1_wNeutrals.root", 0, 1000000);
  Run("18b10a/18b10a_calo_pthat2_wNeutrals.root", 0, 1000000);
  Run("18b10a/18b10a_calo_pthat3_wNeutrals.root", 0, 1000000);
  Run("18b10a/18b10a_calo_pthat4_wNeutrals.root", 0, 1000000);
  Run("18b10a/18b10a_calo_pthat5_wNeutrals.root", 0, 1000000);
  Run("18b10a/18b10a_calo_pthat6_wNeutrals.root", 0, 1000000);

  
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
