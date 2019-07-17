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

bool ptDepShowerShapeCut(Float_t clus_pt, Float_t lambda2)
{
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

void Run(const int TrackBit, TString address, bool isMC, bool hasAliDir, bool triggered){

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
  TTree* tree;
  if(hasAliDir)
    tree = (TTree*)f->Get("AliAnalysisTaskNTGJ/_tree_event");
  else
    tree = (TTree*)f->Get("_tree_event");
  if(!tree){ printf("Error: cannot find tree"); }
  const Int_t kMax = 5000;
  
  Double_t primary_vertex[3];
  Bool_t is_pileup_from_spd_5_08;
  Bool_t is_pileup_from_spd_3_08;
  Bool_t is_incomplete_daq;
  int npileup_vertex_spd;
  int run_number;
  unsigned int ntrack;

  UInt_t ncluster;
  Float_t cluster_e[kMax];
  Float_t cluster_e_cross[kMax];
  Float_t cluster_pt[kMax];
  Float_t cluster_eta[kMax];
  Float_t cluster_phi[kMax];
  Float_t cluster_iso_tpc_04[kMax];
  Float_t cluster_iso_its_04[kMax];
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
  
  tree->SetBranchAddress("primary_vertex", primary_vertex);
  tree->SetBranchAddress("is_pileup_from_spd_5_08", &is_pileup_from_spd_5_08);
  tree->SetBranchAddress("is_pileup_from_spd_3_08", &is_pileup_from_spd_3_08);
  //tree->SetBranchAddress("is_incomplete_daq", &is_incomplete_daq);
  tree->SetBranchAddress("run_number", &run_number);
  tree->SetBranchAddress("npileup_vertex_spd", &npileup_vertex_spd);
  tree->SetBranchAddress("trigger_mask", trigger_mask);
  tree->SetBranchAddress("ntrack", &ntrack);

  tree->SetBranchAddress("ncluster", &ncluster);
  tree->SetBranchAddress("cluster_e", cluster_e);
  tree->SetBranchAddress("cluster_e_cross", cluster_e_cross);
  tree->SetBranchAddress("cluster_pt", cluster_pt); // here
  tree->SetBranchAddress("cluster_eta", cluster_eta);
  tree->SetBranchAddress("cluster_phi", cluster_phi);
  tree->SetBranchAddress("cluster_s_nphoton", cluster_s_nphoton); // here
  tree->SetBranchAddress("cluster_mc_truth_index", cluster_mc_truth_index);
  tree->SetBranchAddress("cluster_lambda_square", cluster_lambda_square);
  tree->SetBranchAddress("cluster_iso_tpc_04",cluster_iso_tpc_04);
  tree->SetBranchAddress("cluster_iso_its_04",cluster_iso_its_04);
  tree->SetBranchAddress("cluster_iso_04_truth", cluster_iso_04_truth);
  tree->SetBranchAddress("cluster_frixione_tpc_04_02",cluster_frixione_tpc_04_02);
  tree->SetBranchAddress("cluster_frixione_its_04_02",cluster_frixione_its_04_02);
  tree->SetBranchAddress("cluster_nlocal_maxima", cluster_nlocal_maxima);        
  tree->SetBranchAddress("cluster_distance_to_bad_channel", cluster_distance_to_bad_channel);
  tree->SetBranchAddress("cluster_ncell", cluster_ncell);
  tree->SetBranchAddress("cluster_cell_id_max", cluster_cell_id_max);
  tree->SetBranchAddress("cell_e", cell_e);
  
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
  auto hZvertex = new TH1F("hZvertez", "", 60, -30, 30);
  auto hZvertexAfter = new TH1F("hZvertezAfter", "", 60, -30, 30);
  auto hHitsITS = new TH1F("hHitsITS", "", 10, -0.5, 9.5);
  auto hEventCut = new TH1F("hEventCut", "", 10, -0.5, 9.5);
  auto hPileUpVertex = new TH1F("hPileUpVertex", "", 20, -0.5, 19.5);
  
  hZvertex->Sumw2();
  hZvertexAfter->Sumw2();
  hHitsITS->SetTitle(";Layers hit; counts");

  //Photon
  const int nbinscluster = 14;
  Double_t clusterbins[nbinscluster+1] = {5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 12.00, 14.00, 16.00, 18.00, 20.00, 25.00, 30.00, 40.00, 60.00};//nbinscluster = 14, Erwann binning

  Double_t clusterbinsTrig[25] = {0.00, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 11.00, 12.00, 13.00, 14.00, 15.00, 16.00, 17.00, 18.00, 20.00, 22.00, 26.00, 30.00, 35.00, 40.00};
  auto h_Reco  = new TH1F("h_Reco","", nbinscluster, clusterbins);
  auto hCluster_pt = new TH1F("hCluster_pt", "", nbinscluster, clusterbins);
  auto hEG1_E = new TH1F("hEG1_E", "", 24, clusterbinsTrig);
  auto hEG2_E = new TH1F("hEG2_E", "", 24, clusterbinsTrig);
  auto hMB_E = new TH1F("hMB_E", "", 24, clusterbinsTrig);

  h_Reco->Sumw2();
  hCluster_pt->Sumw2();
  hEG1_E->Sumw2();  
  hEG2_E->Sumw2();
  hMB_E->Sumw2();

  hCluster_pt->SetTitle("; E_{T} (GeV/c) ; dN/dE_{T}");
  hMB_E->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{MB}dN/dE_{T}");
  hEG1_E->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG1}dN/dE_{T}");
  hEG2_E->SetTitle("; E_{T} (GeV) ; 1/N_{ev}^{EG2}dN/dE_{T}");

  int nevent = 0; 
  int numEvents_tracks = 0;
  int numEvents_clusters = 0;
  int numEvents_clusters2 = 0;
  int numEvents = 0;
  int numEvents_MB = 0;
  int numEvents_EG1 = 0;
  int numEvents_EG2 = 0;
  //const int TrackBit = 16; //ITSONLY==16; ITS--TPC with full-jet cuts

  const double maxEta = 0.8;
 
  const ULong64_t one1 = 1;
  ULong64_t trigMask_13d_trigs[3];//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13d_trigs[0] = (one1 << 2);
  trigMask_13d_trigs[1] = (one1 << 18);
  trigMask_13d_trigs[2] = (one1 << 19);

  ULong64_t trigMask_13c_trigs_r195529[3];//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13c_trigs_r195529[0] = (one1 << 6);
  trigMask_13c_trigs_r195529[1] = (one1 << 18);
  trigMask_13c_trigs_r195529[2] = (one1 << 19);

  ULong64_t trigMask_13c_trigs_r195531[3];//0 = MB, 1 = EG1, 2 = EG2
  trigMask_13c_trigs_r195531[0] = (one1 << 6);
  trigMask_13c_trigs_r195531[1] = (one1 << 17);
  trigMask_13c_trigs_r195531[2] = (one1 << 18);

  ULong64_t trigMask[3] = {0};

  Long64_t totEvents = tree->GetEntries();
  Long64_t restrictEvents = 100000000;
  Long64_t numEntries = TMath::Min(totEvents,restrictEvents);
  std::cout << numEntries << std::endl;
  for (Long64_t ievent=0;ievent< numEntries ;ievent++) {
    tree->GetEntry(ievent);
    nevent += 1;
    if(nevent%100000==0)
      {
	std::cout << nevent << std::endl;
	cout << run_number << endl;
      }
    
    bool eventChange = true;
    bool isMB, isEG1, isEG2;
    isMB = isEG1 = isEG2 = false;

    hPileUpVertex->Fill(npileup_vertex_spd);
    hEventCut->Fill(0);
    hZvertex->Fill(primary_vertex[2]);
    //Event Selection:
    if(not( TMath::Abs(primary_vertex[2])<10.0)) {hEventCut->Fill(1); continue;} //vertex z position
    //if(primary_vertex[2] == 0.000000) {hEventCut->Fill(2); continue;}
    if(is_pileup_from_spd_3_08) {hEventCut->Fill(3); continue;} //removes pileup
    if(not(ntrack > 0)) {hEventCut->Fill(4); continue;} //no track
    //if(is_incomplete_daq){hEventCut->Fill(5); continue;}
    //cout << run_number << "\t";
    hZvertexAfter->Fill(primary_vertex[2]);
    if(run_number > 195700)
      std::memcpy(trigMask, trigMask_13d_trigs, sizeof(trigMask));
    else{
      if(run_number == 195529)
	std::memcpy(trigMask, trigMask_13c_trigs_r195529, sizeof(trigMask));
      else if(run_number == 195531)
	std::memcpy(trigMask, trigMask_13c_trigs_r195531, sizeof(trigMask));
    }
    //cout << trigMask[0] << "\t";
    //cout << trigger_mask[0] << "\t";


    ULong64_t localTrigBit = 0;
    if(not ((trigMask[0] & trigger_mask[0]) == 0))  {
      localTrigBit |= (1 << 0);
      numEvents_MB++;
    }
    if(not ((trigMask[1] & trigger_mask[0]) == 0))  {
      localTrigBit |= (1 << 1);
      numEvents_EG1++;
	}
    if(not ((trigMask[2] & trigger_mask[0]) == 0))  {
      localTrigBit |= (1 << 2);
      numEvents_EG2++;
    }
    //cout << localTrigBit << endl;
    //001 = 1 = MB
    //110 = 6 = EG1||EG2
    //111 = 7 = MB||EG1||EG2
    if((localTrigBit & 6) == 0) {hEventCut->Fill(5); continue;}//no emcal triggers
    hEventCut->Fill(6);//all cuts
    numEvents++;
    
    
    int eventFill = 0;    
    hEventCounts->Fill(eventFill);
    
    eventChange = true;
    bool eventChange2 = true;
    //Loop over clusters
    for(ULong64_t n=0; n< ncluster; n++)
      {
	if (eventChange2) {numEvents_clusters2++; eventChange2 = false;}
	
	//Photon Selection
	ULong64_t clusterCutBits = 0;
	ULong64_t clusterCutPassed = 0;
	//if( not(cluster_pt[n]>8)) {continue;} //select pt of photons
	if( (cluster_ncell[n]>2))                                            clusterCutBits |= (1 << 0); clusterCutPassed |= (1 << 0);//removes clusters with 1 or 2 cells
	if( (cluster_e_cross[n]/cluster_e[n]>0.03))                          clusterCutBits |= (1 << 1); clusterCutPassed |= (1 << 1);//removes "spiky" clusters
	if( (cluster_nlocal_maxima[n]<= 2))                                  clusterCutBits |= (1 << 2); clusterCutPassed |= (1 << 0);//require to have at most 2 local maxima.
	if( (cluster_distance_to_bad_channel[n]>=2.0))                       clusterCutBits |= (1 << 3); clusterCutPassed |= (1 << 0);//distnace to bad channels
       
	//Isolation and shower shape selection:
	if( (cluster_iso_its_04[n] < 2))                                     clusterCutBits |= (1 << 4); clusterCutPassed |= (1 << 0);//isolation r = 0.4 and energy < 2
	if( (ptDepShowerShapeCut(cluster_pt[n], cluster_lambda_square[n][0])))  clusterCutBits |= (1 << 5); clusterCutPassed |= (1 << 0);//single-photon selection, not merged
	
	if(clusterCutBits != clusterCutPassed) continue;
	if (eventChange) {numEvents_clusters++; eventChange = false;}
	
	h_Reco->Fill(cluster_pt[n]);	
	hCluster_pt->Fill(cluster_pt[n]);
	if((localTrigBit & 1) != 0) hMB_E->Fill(cluster_pt[n]);
	if((localTrigBit & 2) != 0) hEG1_E->Fill(cluster_pt[n]);
	if((localTrigBit & 4) != 0) hEG2_E->Fill(cluster_pt[n]);
	hIso_ITS->Fill(cluster_iso_its_04[n]);
	hIso_TPC->Fill(cluster_iso_tpc_04[n]);
	hIso_Truth->Fill(cluster_iso_04_truth[n]);
	
      }
    
    
  }//loop over events
  std::cout << " END LOOP  " << std::endl;
  cout << "minbias/EG1/EG2 events:" << numEvents_MB << "\t" << numEvents_EG1 << "\t" << numEvents_EG2 << "\t" << endl;  
  
  //Normalizing the bins and getting yaxsis to be 1/Nevt*dN/dptdeta
  cout << numEvents_tracks << endl;
  cout << filename(0,3) << "\tTotal Events: " << numEntries << "\tEvent selection: " << numEvents << "\tPre-Cluster selection: " << numEvents_clusters2 << "\tPostCluster selection: " << numEvents_clusters << endl;
  const double deltaEta = 1.04;
  const double deltaPhi = 1.39;
  double acceptanceNorm = 2*TMath::Pi()/(deltaEta*deltaPhi);

  auto normalizer = new TH1D("normalizer", "normalizer", 10, -0.5, 9.5);
  normalizer->SetBinContent(1, deltaEta);
  normalizer->SetBinContent(2, deltaPhi);
  normalizer->SetBinContent(3, numEvents);
  normalizer->SetBinContent(4, numEvents_MB);
  normalizer->SetBinContent(5, numEvents_EG1);
  normalizer->SetBinContent(6, numEvents_EG2);
  
  //scaling for clusters
  for(int i = 1; i <  hCluster_pt->GetNbinsX()+1; i++)
    {
      double dpt = hCluster_pt->GetBinWidth(i);
      double content = hCluster_pt->GetBinContent(i);
      double temp = (content*acceptanceNorm)/((double)numEvents*dpt);
      //double temp = content/((double)numEvents*dpt);
      //cout << dpt << "\t" << content << "\t" << temp << endl;
      //double temp = content/dpt;
      hCluster_pt->SetBinContent(i, temp);
      
      double error = hCluster_pt->GetBinError(i);
      double tempErr = (error*acceptanceNorm)/((double)numEvents*dpt);
      //double tempErr = error/dpt;
      hCluster_pt->SetBinError(i, tempErr);
    }//*/

  /*for(int i = 1; i < hMB_E->GetNbinsX()+1; i++)
    {
      double dE = hMB_E->GetBinWidth(i);
      
      double contentMB = hMB_E->GetBinContent(i);
      double tempMB = contentMB/((double)numEvents_MB*dE);
      double errorMB = hMB_E->GetBinError(i);
      double tempErrMB = errorMB/((double)numEvents_MB*dE);
      if(numEvents_MB) 
	{
	  hMB_E->SetBinContent(i,tempMB);
	  hMB_E->SetBinError(i, tempErrMB);
	}

      double contentEG1 = hEG1_E->GetBinContent(i);
      double tempEG1 = contentEG1/((double)numEvents_EG1*dE);
      double errorEG1 = hEG1_E->GetBinError(i);
      double tempErrEG1 = errorEG1/((double)numEvents_EG1*dE);
      if(numEvents_EG1) 
	{
	  hEG1_E->SetBinContent(i,tempEG1);
	  hEG1_E->SetBinError(i, tempErrEG1);
	}

      double contentEG2 = hEG2_E->GetBinContent(i);
      double tempEG2 = contentEG2/((double)numEvents_EG2*dE);
      double errorEG2 = hEG2_E->GetBinError(i);
      double tempErrEG2 = errorEG2/((double)numEvents_EG2*dE);
      if(numEvents_EG2) 
	{
	  hEG2_E->SetBinContent(i,tempEG2);
	  hEG2_E->SetBinError(i, tempErrEG2);
	}
   }

  
  TH1F* rTrig1 = (TH1F*)hEG1_E->Clone();
  rTrig1->Divide(hMB_E);
  TH1F* rTrig2 = (TH1F*)hEG2_E->Clone();
  rTrig2->Divide(hMB_E);
  rTrig1->SetTitle(";E (GeV);EG1/MB");
  rTrig2->SetTitle(";E (GeV);EG2/MB");//*/


  hEventCut->GetXaxis()->SetBinLabel(1,"All events");
  hEventCut->GetXaxis()->SetBinLabel(2,"primary vertex > 10");
  hEventCut->GetXaxis()->SetBinLabel(3,"primary vertex = 0");
  hEventCut->GetXaxis()->SetBinLabel(4,"pile up");
  hEventCut->GetXaxis()->SetBinLabel(5,"ntrack < 0");
  hEventCut->GetXaxis()->SetBinLabel(6,"no EMCA/MB trigger");
  hEventCut->GetXaxis()->SetBinLabel(7,"passed");
  
  hEventCounts->GetXaxis()->SetBinLabel(1, "Passing Event Selection only");
  hEventCounts->GetXaxis()->SetBinLabel(2, "Passing Track Selection");

  normalizer->GetXaxis()->SetBinLabel(1,"deltaEta");
  normalizer->GetXaxis()->SetBinLabel(2,"deltaPhi");
  normalizer->GetXaxis()->SetBinLabel(3,"numEvents");
  normalizer->GetXaxis()->SetBinLabel(4,"numEvents_MB");
  normalizer->GetXaxis()->SetBinLabel(5,"numEvents_EG1");
  normalizer->GetXaxis()->SetBinLabel(6,"numEvents_EG2");

  //Writing to file
  filename += "_cluster_emcalTrig_Allevent_wEventSelect_allClusCuts_noDownScale_2piNevdEdEtaPhi";
  auto fout = new TFile(Form("isoPhotonOutput/fout_%i_%ibins_%s.root",TrackBit, nbinscluster, filename.Data()), "RECREATE");  


  
  //writing photon info
  hCluster_pt->Write("cluster_pt");
  hEventCounts->Write("hEventCounts");
  hMB_E->Write("hMB_E");
  hEG1_E->Write("hEG1_E");
  hEG2_E->Write("hEG2_E");
  //rTrig1->Write("rTrig1");  
  //rTrig2->Write("rTrig2");  

  hZvertex->Write("hZvertex");
  hZvertexAfter->Write("hZvertexAfter");
  hPileUpVertex->Write("hPileUpVertex");
  hEventCut->Write("hEventCut");
  normalizer->Write("hNormalizer");
  fout->Close();  
  
}

    
void isoPhotonAnalysisData(){  
  //Input to Run is as follow: Run(const int TrackBit, TString address, bool isMC, bool hasAliDir, bool triggered)
  
/*/////////////////////////////////////////////////////////////////
p-Pb data sets:
13c  : MinBias
13d,e: p-Pb emcal trigger   
13f  : Pb-p emcal trigger    
/////////////////////////////////////////////////////////////////*/
  //Run(16, "pPb/13c/13c_2runs_al.root", false, true, true);
  
  Run(16, "pPb/13d/13d.root", false, true, true);
  //Run(16, "pPb/13d/13d_3run_forTrig_noEThresh.root", false, true, true);
  //Run(16, "pPb/13d/13d_7runs_noThresh.root", false, true, true);



  //pp data sets
  //Run(16, "pp/17q/17q_CENT_wSDD_3run_forTrig_noEThresh.root", false, true, true);



  return;
}




