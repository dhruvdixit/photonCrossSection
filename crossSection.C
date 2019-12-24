#include <fstream>
#include <vector>
void crossSection(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  



  //Obtain and plotting histograms from data

  //TFile* dataFile = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_cluster_emcalTrig_Allevent_wEventSelect_allClusCuts_noDownScale_2piNevdEdEtaPhi_newIsoDef.root","READ"); 
  //TFile* dataFile = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_cluster_emcalTrig_Allevent_wEventSelect_allClusCuts_noDownScale_2piNevdEdEtaPhi_newIsoDef_wPurity.root", "READ");
  //TFile* dataFile = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_cluster_emcalTrig_Allevent_wEventSelect_allClusCutsTimeCut_noDownScale_2piNevdEdEtaPhi_newIsoDef_wPurity.root", "READ");
  //TFile* dataFile = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_cluster_emcalTrig_Allevent_wEventSelect_allClusCutsTimeCutAcceptanceCut_noDownScale_2piNevdEdEtaPhi_newIsoDef_wPurity.root", "READ");
  //TFile* dataFile = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_cluster_emcalTrig_Allevent_wEventSelect_allClusCutsTimeCutAcceptanceCut_noDownScale_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction.root", "READ");
  //TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_cluster_emcalTrig_Allevent_wEventSelect_allClusCutsTimeCutAcceptanceCut_noDownScale_2piNevdEdEtaPhi_fernandoIsoDef_wPurityFitFunction.root", "READ");
  //TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_wNonLinCorr_cluster_emcalTrig_Allevent_wEventSelect_allClusCutsTimeCutAcceptanceCut_noDownScale_2piNevdEdEtaPhi_fernandoIsoDef_wPurityFitFunction_nonLinCorrTest.root", "READ");
  //TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13de_cluster_emcalTrigOnly_Allevent_wEventSelect_allClusCuts_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction.root", "READ");
  //TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13de_cluster_emcalTrigOnly_Allevent_wEventSelect_allClusCuts_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction_TrigSelComplete_FullEMCal.root", "READ");
  //TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13def_cluster_emcalTrigOnly_Allevent_wEventSelect_allClusCuts_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction_TrigSelComplete_FullEMCal_clusterCutFlow_multiplicity.root", "READ");
  //TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_cluster_emcalTrigOnly_1Mevents_eventCounts_wTrigPileUpSkimEGCut.root", "READ");
  //TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut.root", "READ");//THIS FILE WORKS!!! NORMALIZATION ISSUE SOLVED!!!!
  //TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_EG1ptCut14GeV.root", "READ");
  //TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_onlyEG1ptCut14GeV.root", "READ");
  //TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_EG1EG2seperate_useRecoptHist.root", "READ");
  //TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_new.root", "READ");
  TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "READ");


  //pp
  //TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_cluster_emcalTrig_Allevent_wEventSelect_allClusCutsTimeCutAcceptanceCut_noDownScale_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction_ZcutsFirst.root", "READ");
  //TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_cluster_emcalTrigOnly_Allevent_wEventSelect_allClusCuts_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction.root", "READ");
  //TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_cluster_emcalTrigOnly_Allevent_wEventSelect_allClusCuts_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction_TrigSelComplete.root", "READ");
  //TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_cluster_emcalTrigOnly_Allevent_wEventSelect_allClusCuts_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction_TrigSelComplete_FullEMCal.root", "READ");
  //TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_1EMCGoodRuns_cluster_EMCandDMCTrigOnly_Allevent_wTripPileupSkimEGCut_MBDG2EG2seperate_purityCorr_new.root", "READ");
  //TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_1EMCGoodRuns_cluster_EMCandDMCTrigOnly_Allevent_wTripPileupSkimEGCut_MBDG2EG2seperate_purityCorr_etaPhiAcceptancenew.root", "READ");
  //TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_cluster_EMCandDMCTrigOnly_Allevent_wTripPileupSkimEGCut_MBDG2EG2seperate_purityCorr_etaPhiAcceptancenew.root", "READ");
  //TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_cluster_EMCandDMCTrigOnly_1Mevent_wTripPileupSkimEGCut_MBDG2EG2seperate_purityCorr_etaPhiAcceptancenew_EG2caloOnly.root", "READ");
  TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_EG2_caloE_vs_cluster_pt_Normalized.root", "READ");

  TH1F* hClusterSpectra_pPb = (TH1F*)dataFile_pPb->Get("hEG1_E");
  TH1F* hClusterSpectra_pp = (TH1F*)dataFile_pp->Get("hEG2_caloE");
  TH1F* hClusterSpectra_EG2 = (TH1F*)dataFile_pPb->Get("hEG2_E");
  //TH1F* hEG2 = (TH1F*)dataFile_pPb->Get("hEG2_E");
  //hClusterSpectra_pPb->Add(hEG2);
  TH1D* hNumEvents_pPb = (TH1D*)dataFile_pPb->Get("hNormalizer");
  TH1D* hNumEvents_pp = (TH1D*)dataFile_pp->Get("hNormalizer");

  hClusterSpectra_pPb->Sumw2();
  hClusterSpectra_pPb->SetName("hClusterSpectra_pPb");
  hClusterSpectra_pPb->SetTitle(";E_{T} [GeV]; #frac{1}{N_{ev}}#frac{d^{2}N}{dE_{T}d#eta}");
  hClusterSpectra_pPb->SetLineColor(kRed);
  hClusterSpectra_pPb->SetMarkerColor(kRed);
  hClusterSpectra_pPb->SetMarkerStyle(21);
  hClusterSpectra_pPb->SetMarkerSize(2);

  hClusterSpectra_pp->Sumw2();
  hClusterSpectra_pp->SetName("hClusterSpectra_pp");
  hClusterSpectra_pp->SetTitle(";E_{T} [GeV]; #frac{1}{N_{ev}}#frac{d^{2}N}{dE_{T}d#eta}");
  hClusterSpectra_pp->SetLineColor(kBlue);
  hClusterSpectra_pp->SetMarkerColor(kBlue);
  hClusterSpectra_pp->SetMarkerStyle(20);
  hClusterSpectra_pp->SetMarkerSize(2);

  hClusterSpectra_EG2->Sumw2();
  hClusterSpectra_EG2->SetName("hClusterSpectra_EG2");
  hClusterSpectra_EG2->SetTitle(";E_{T} [GeV]; #frac{1}{N_{ev}}#frac{d^{2}N}{dE_{T}d#eta}");
  hClusterSpectra_EG2->SetLineColor(kGreen);
  hClusterSpectra_EG2->SetMarkerColor(kGreen);
  hClusterSpectra_EG2->SetMarkerStyle(21);
  hClusterSpectra_EG2->SetMarkerSize(2);

  
  TLegend* legYield = new TLegend(0.6,0.7,0.9,0.9);
  legYield->SetHeader("Photon Yield");
  legYield->AddEntry(hClusterSpectra_pPb,"pPb EG1");
  legYield->AddEntry(hClusterSpectra_pp,"pp EG2");
  legYield->AddEntry(hClusterSpectra_EG2,"pPb EG2");


  //Obtain and plotting histograms from MC
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_MKevents_erwanbinning_noNorm_newIsoDef_acceptanceCuts2.root","READ"); 
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration.root","READ"); 
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_dist2BadChn0.root","READ");
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_dist2BadChn1.root","READ");
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_dist2BadChn1_hCorr_corr.root","READ"); 
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_dist2BadChn1_hCorr_corr_ncell1.root","READ"); 
  TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_50Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_hCorr_corr_stdCuts.root","READ");
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffTogether_cutFlow_binMigration_hCorr_corr_stdCuts.root","READ");
  

  TH1D* hEff_pPb = (TH1D*)mcFile_pPb->Get("hEfficiency");
  hEff_pPb->SetName("hEff_pPb");
  hEff_pPb->SetTitle("; E_{T} [GeV]; #epsilon");
  hEff_pPb->GetYaxis()->SetRangeUser(0,1);
  hEff_pPb->SetLineColor(kRed+1);
  hEff_pPb->SetMarkerColor(kRed+1);
  hEff_pPb->SetMarkerStyle(24);
  hEff_pPb->SetMarkerSize(2);
  hEff_pPb->SetLineWidth(2);

  TH1D* hFakeRate_pPb = (TH1D*)mcFile_pPb->Get("hFakeRate");
  hFakeRate_pPb->SetName("FakeRate_pPb");
  hFakeRate_pPb->SetTitle("; E_{T} [GeV];");
  hFakeRate_pPb->GetYaxis()->SetRangeUser(0,1);
  hFakeRate_pPb->SetLineColor(kBlue);
  hFakeRate_pPb->SetMarkerColor(kBlue);
  hFakeRate_pPb->SetMarkerStyle(24);
  hFakeRate_pPb->SetMarkerSize(2);
  hFakeRate_pPb->SetLineWidth(2);
  
  TH1D* hBinMigration_pPb = (TH1D*)mcFile_pPb->Get("hMigEfficiency");
  hBinMigration_pPb->SetName("hbinMigration_pPb");
  hBinMigration_pPb->SetTitle("Bin Migration Effection = #frach{dN^{reco}/dE_{T}^{reco}}{dN^{reco}/dE_{T}^{truth}}; E_{T} [GeV]; #epsilon");
  hBinMigration_pPb->GetYaxis()->SetRangeUser(0,1);
  hBinMigration_pPb->SetLineColor(kMagenta);
  hBinMigration_pPb->SetMarkerColor(kMagenta);
  hBinMigration_pPb->SetMarkerStyle(24);
  hBinMigration_pPb->SetMarkerSize(2);
  hBinMigration_pPb->SetLineWidth(2);//*/
  
  /*TH2D* hCorrelation_pPb = (TH2D*)mcFile_pPb->Get("hCorrelation");
  hCorrelation_pPb->SetName("hCorrelation_pPb");
  TH1D* mc_truth_pPb = (TH1D*)hCorrelation_pPb->ProjectionX("mc_truth_pPb");
  TH1D* mc_reco_pPb = (TH1D*)hCorrelation_pPb->ProjectionY("mc_reco_pPb");
  TH1D* hBinMigration_pPb = (TH1D*)mc_truth_pPb->Clone();
  hBinMigration_pPb->SetName("hBinMigration_pPb");
  hBinMigration_pPb->Divide(mc_reco_pPb);
  hBinMigration_pPb->SetTitle(";E_{T} [GeV]; #frac{truth}{reco}");
  hBinMigration_pPb->SetLineColor(kMagenta);
  hBinMigration_pPb->SetMarkerColor(kMagenta);
  hBinMigration_pPb->SetMarkerStyle(24);
  hBinMigration_pPb->SetMarkerSize(3);//*/

  
  TFile* mcFile_pp = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/18b10a_Allevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_hCorr_corr_stdCuts.root","READ");
  
  TH1D* hEff_pp = (TH1D*)mcFile_pp->Get("hEfficiency");
  hEff_pp->SetName("hEff_pp");
  hEff_pp->SetTitle("; E_{T} [GeV]; #epsilon");
  hEff_pp->GetYaxis()->SetRangeUser(0,1);
  hEff_pp->SetLineColor(kRed-1);
  hEff_pp->SetMarkerColor(kRed-1);
  hEff_pp->SetMarkerStyle(21);
  hEff_pp->SetMarkerSize(1);
  hEff_pp->SetLineWidth(2);

  TH1D* hFakeRate_pp = (TH1D*)mcFile_pp->Get("hFakeRate");
  hFakeRate_pp->SetName("FakeRate_pp");
  hFakeRate_pp->SetTitle("; E_{T} [GeV];");
  hFakeRate_pp->GetYaxis()->SetRangeUser(0,1);
  hFakeRate_pp->SetLineColor(kBlue);
  hFakeRate_pp->SetMarkerColor(kBlue);
  hFakeRate_pp->SetMarkerStyle(21);
  hFakeRate_pp->SetMarkerSize(1);
  hFakeRate_pp->SetLineWidth(2);
  
  TH1D* hBinMigration_pp = (TH1D*)mcFile_pp->Get("hMigEfficiency");
  hBinMigration_pp->SetName("hbinMigration_pp");
  hBinMigration_pp->SetTitle("Bin Migration Effection = #frach{dN^{reco}/dE_{T}^{reco}}{dN^{reco}/dE_{T}^{truth}}; E_{T} [GeV]; #epsilon");
  hBinMigration_pp->GetYaxis()->SetRangeUser(0,1);
  hBinMigration_pp->SetLineColor(kMagenta);
  hBinMigration_pp->SetMarkerColor(kMagenta);
  hBinMigration_pp->SetMarkerStyle(21);
  hBinMigration_pp->SetMarkerSize(1);
  hBinMigration_pp->SetLineWidth(2);//*/
  
  TLegend* legEff = new TLegend(0.6,0.7,0.85,0.85);
  legEff->AddEntry(hEff_pPb,"p-Pb: Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso}");
  //legEff->AddEntry(hFakeRate_pPb,"p-Pb: Fake rate");
  //legEff->AddEntry(hBinMigration_pPb,"p-Pb: Bin Migration");
  legEff->AddEntry(hEff_pp,"pp: Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso}");
  //legEff->AddEntry(hFakeRate_pp,"pp: Fake rate");
  //legEff->AddEntry(hBinMigration_pp,"pp: Bin Migration");

  TCanvas* cEff = new TCanvas();
  hEff_pPb->GetXaxis()->SetRangeUser(12,60);
  hEff_pPb->Draw("e1");
  //hBinMigration_pPb->Draw("samee1");
  //hFakeRate_pPb->Draw("samee1");
  hEff_pp->Draw("samee1");
  //hBinMigration_pp->Draw("samee1");
  //hFakeRate_pp->Draw("samee1");
  legEff->Draw("same");//*/

  //Luminosity Calulation
  double Nevtot_pPb = hNumEvents_pPb->GetBinContent(12);
  double Nevtot_pp = hNumEvents_pp->GetBinContent(11);
  double Nevtot_EG2 = hNumEvents_pPb->GetBinContent(13);
  cout << Nevtot_pPb << "\t" << Nevtot_pp << "\t" << Nevtot_EG2 << endl;

  double xSectionEG2 = 2.11;

  
  const double lumi_pPb = 0.22;
  const double lumi_error_pPb = 0.02;
  double relLumiError_pPb = lumi_error_pPb/lumi_pPb;
  const double lumi_pp = 32.84;
  const double lumi_error_pp = 2.98;
  double relLumiError_pp = lumi_error_pp/lumi_pp;
  const double lumi_EG2 = 0.02;
  const double lumi_error_EG2 = 0.00;
  double relLumiError_EG2 = lumi_error_EG2/lumi_EG2;

  
  //Cross Section Calculation  
  /*////////////////////////////////////////////////////////////
    pPb cross section using EG1 trigger
  ///////////////////////////////////////////////////////////*/
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n p-Pb EG1 trigger cross section \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  TH1F* crossSection_pPb = (TH1F*)hClusterSpectra_pPb->Clone();
  crossSection_pPb->SetName("crossSection_pPb");
  crossSection_pPb->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  for(int i = 1; i < crossSection_pPb->GetNbinsX()+1;i++){
    
    double content = crossSection_pPb->GetBinContent(i);
    double error = crossSection_pPb->GetBinError(i);
    double relError = error/content;

    double eff = hEff_pPb->GetBinContent(i);
    double eff_error = hEff_pPb->GetBinError(i);
    double relEffError = eff_error/eff;
    
    /*double bm = hBinMigration_pPb->GetBinContent(i);
    double bm_error = hBinMigration_pPb->GetBinError(i);
    double relBmError = bm_error/bm;//*/

    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2)+TMath::Power(relLumiError_pPb,2));
    double xsection = (content*Nevtot_pPb)/(lumi_pPb*eff);
    double xsection_error = relXSectionError*xsection;

    //cout statement
    cout << crossSection_pPb->GetBinLowEdge(i) << "\t" << crossSection_pPb->GetBinLowEdge(i+1) << "\t" << content << "\t" << Nevtot_pPb << "\t" << lumi_pPb << "\t" << eff << "\t" << xsection << endl;

    //filling the cross section hist
    crossSection_pPb->SetBinContent(i, xsection);
    crossSection_pPb->SetBinError(i, xsection_error);
    
  }//*/
  
  /*////////////////////////////////////////////////////////////
    pPb cross section using EG2 trigger
  ///////////////////////////////////////////////////////////*/
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n pp EG2 trigger cross section \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  TH1F* crossSection_EG2 = (TH1F*)hClusterSpectra_EG2->Clone();
  crossSection_EG2->SetName("crossSection_EG2");
  crossSection_EG2->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  for(int i = 1; i < crossSection_EG2->GetNbinsX()+1;i++){
    
    double content = crossSection_EG2->GetBinContent(i);
    double error = crossSection_EG2->GetBinError(i);
    double relError = error/content;

    double eff = hEff_pPb->GetBinContent(i);
    double eff_error = hEff_pPb->GetBinError(i);
    double relEffError = eff_error/eff;

    /*double bm = hBinMigration_pPb->GetBinContent(i);
    double bm_error = hBinMigration_pPb->GetBinError(i);
    double relBmError = bm_error/bm;//*/

    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2)+TMath::Power(relLumiError_EG2,2));
    double xsection = (content*Nevtot_EG2)/(lumi_EG2*eff);
    double xsection_error = relXSectionError*xsection;

    //cout statement
    cout << crossSection_pPb->GetBinLowEdge(i) << "\t" << crossSection_pPb->GetBinLowEdge(i+1) << "\t" << content << "\t" << Nevtot_EG2 << "\t" << lumi_EG2 << "\t" << eff << "\t" << xsection << endl;

    //filling the cross section hist
    crossSection_EG2->SetBinContent(i, xsection);
    crossSection_EG2->SetBinError(i, xsection_error);
    
  }//*/

  /*////////////////////////////////////////////////////////////
    pp cross section using EG2 trigger
  ///////////////////////////////////////////////////////////*/
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n pp EG2 trigger cross section \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  TH1F* crossSection_pp = (TH1F*)hClusterSpectra_pp->Clone();
  crossSection_pp->SetName("crossSection_pp");
  crossSection_pp->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  TH1F* crossSection_ppScaled = (TH1F*)hClusterSpectra_pp->Clone();
  crossSection_ppScaled->SetName("crossSection_ppScaled");
  crossSection_ppScaled->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  const double Ncoll = 7.0;
  const double A = 208;
  for(int i = 1; i < crossSection_pp->GetNbinsX()+1;i++){
    
    double content = crossSection_pp->GetBinContent(i);
    double error = crossSection_pp->GetBinError(i);
    double relError = error/content;

    double eff = hEff_pp->GetBinContent(i);
    double eff_error = hEff_pp->GetBinError(i);
    double relEffError = eff_error/eff;
    
    /*double bm = hBinMigration_pp->GetBinContent(i);
    double bm_error = hBinMigration_pp->GetBinError(i);
    double relBmError = bm_error/bm;//*/

    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2)+TMath::Power(relLumiError_pp,2));
    double xsection = (content*Nevtot_pp)/(lumi_pp*eff);
    double xsection_error = relXSectionError*xsection;
    
    //cout statement
    cout << crossSection_pp->GetBinLowEdge(i) << "\t" << crossSection_pp->GetBinLowEdge(i+1) << "\t" << content << "\t" << Nevtot_pp << "\t" << lumi_pp << "\t" << eff << "\t" << xsection << endl;

    //filling the cross section hist
    crossSection_pp->SetBinContent(i, xsection);
    crossSection_pp->SetBinError(i, xsection_error);
    crossSection_ppScaled->SetBinContent(i, xsection*A);
    crossSection_ppScaled->SetBinError(i, xsection_error*A);
    
  }//*/


  /*////////////////////////////////////////////////////////////////////
    RpA
  ////////////////////////////////////////////////////////////////////*/
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n RpA \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
 
  TH1F* h_RpA = (TH1F*)hClusterSpectra_pPb->Clone();
  h_RpA->SetName("h_RpA");
  h_RpA->SetTitle(";E_{T} [GeV]; RpA (#sigma_{pPb}/A_{Pb}#sigma_{pp})");
  for(int i = 1; i < h_RpA->GetNbinsX()+1;i++){
    
    double content_pPb = crossSection_pPb->GetBinContent(i);
    double error_pPb = crossSection_pPb->GetBinError(i);
    double relError_pPb = error_pPb/content_pPb;

    double content_pp = crossSection_pp->GetBinContent(i);
    double error_pp = crossSection_pp->GetBinError(i);
    double relError_pp = error_pp/content_pp;

    double rpa;
    double rpa_relError;
    double rpa_error;
    
    if(content_pp != 0.0){
      rpa = content_pPb/((double)A*content_pp);
      rpa_relError = TMath::Sqrt(TMath::Power(relError_pPb,2)+TMath::Power(relError_pp,2));
      rpa_error = rpa*rpa_relError;
    }
    else{
      rpa = 0.0;
      rpa_error = 0.0;
    }

    //cout statement
    cout  << h_RpA->GetXaxis()->GetBinLowEdge(i) << "\t" << h_RpA->GetXaxis()->GetBinLowEdge(i+1) << "\t"<< content_pPb << "\t" << content_pp << "\t" << content_pPb/((double)A*content_pp) << "\t" << rpa << "\t" << rpa_error << endl;

    //Filling in the rpa
    h_RpA->SetBinContent(i, rpa);
    h_RpA->SetBinError(i, rpa_error);
  }

  

  TH1F* crossSection_erwann = (TH1F*)hClusterSpectra_pPb->Clone();
  crossSection_erwann->SetName("crossSection_erwann");
  crossSection_erwann->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  
  double erwannMean[9] = {4727.74, 2015.57, 1151.86, 696.985, 444.604, 233.026, 104.87, 38.5216, 7.4227};
  double erwannStat[9] = {604.369, 337.901, 71.0714, 51.475, 35.3468, 15.5412, 10.4705, 4.64552, 1.38719};
  double erwannSys[9] = {766.058, 308.501, 167.064, 96.1471, 58.8658, 29.4243, 12.7484, 4.7213, 1.11858};

  for(int i = 6; i < crossSection_erwann->GetNbinsX()+1;i++){
    

    crossSection_erwann->SetBinContent(i, erwannMean[i-6]);
    crossSection_erwann->SetBinError(i, erwannStat[i-6]);
    
  }

  crossSection_erwann->SetLineColor(kBlack);
  crossSection_erwann->SetMarkerStyle(21);
  crossSection_erwann->SetMarkerColor(kBlack);
  crossSection_erwann->SetMarkerSize(2);

  crossSection_pp->SetLineColor(kBlue);
  crossSection_pp->SetMarkerStyle(20);
  crossSection_pp->SetMarkerColor(kBlue);
  crossSection_pp->SetMarkerSize(2);

  crossSection_ppScaled->SetLineColor(kCyan);
  crossSection_ppScaled->SetMarkerStyle(20);
  crossSection_ppScaled->SetMarkerColor(kCyan);
  crossSection_ppScaled->SetMarkerSize(2);
  
  crossSection_pPb->SetLineColor(kRed);
  crossSection_pPb->SetMarkerStyle(21);
  crossSection_pPb->SetMarkerColor(kRed);
  crossSection_pPb->SetMarkerSize(2);
  
  crossSection_EG2->SetLineColor(kGreen);
  crossSection_EG2->SetMarkerStyle(21);
  crossSection_EG2->SetMarkerColor(kGreen);
  crossSection_EG2->SetMarkerSize(2);
  
  //unity --> line at 1
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);

  
  TLegend* leg = new TLegend(0.6,0.65,0.9,0.85);
  leg->SetHeader("p-Pb (13f 3 runs), pp (17q 12 runs)");
  leg->AddEntry(crossSection_pp,"pp");
  leg->AddEntry(crossSection_ppScaled,"pp*A(208)");
  leg->AddEntry(crossSection_pPb,"pPb_EG1");
  leg->AddEntry(crossSection_EG2,"pPb_EG2");
  leg->AddEntry(crossSection_erwann,"Erwann's pPb");


  TCanvas* cYield = new TCanvas();
  cYield->SetLogy();
  hClusterSpectra_pPb->GetXaxis()->SetRangeUser(12,60);
  hClusterSpectra_pPb->GetYaxis()->SetRangeUser(1e-8,1e-2);
  hClusterSpectra_pPb->Draw("e1");
  hClusterSpectra_EG2->Draw("samee1");
  hClusterSpectra_pp->Draw("samee1");
  legYield->Draw("same");//*/

  TCanvas* cXSection = new TCanvas();
  cXSection->SetLogy();
  crossSection_pPb->GetXaxis()->SetRangeUser(12,60);
  crossSection_pPb->GetYaxis()->SetRangeUser(1e-5,1e5);
  crossSection_pPb->Draw("e1");
  crossSection_pp->Draw("samee1");
  crossSection_ppScaled->Draw("samee1");
  crossSection_EG2->Draw("samee1");
  crossSection_erwann->Draw("samee1");
  leg->Draw("same");

  TCanvas* cRpa = new TCanvas();
  h_RpA->GetXaxis()->SetRangeUser(12,60);
  h_RpA->GetYaxis()->SetRangeUser(0,2);
  h_RpA->SetMarkerSize(2);
  h_RpA->Draw("e1");
  line->Draw("same");
  
  TH1F* crossSectionRatio_EG1 = (TH1F*)crossSection_erwann->Clone();
  crossSectionRatio_EG1->SetName("crossSectionRatio_EG1");
  crossSectionRatio_EG1->SetTitle(";E_{T};#frac{CrossSection_{Erwann}}{CrossSection_{Dhruv}}");
  crossSectionRatio_EG1->Divide(crossSection_pPb);
  crossSectionRatio_EG1->GetXaxis()->SetRangeUser(12,60);
  crossSectionRatio_EG1->GetYaxis()->SetRangeUser(0,2);
  crossSectionRatio_EG1->SetLineColor(kRed);
  crossSectionRatio_EG1->SetMarkerColor(kRed);
  
  TH1F* crossSectionRatio_EG2 = (TH1F*)crossSection_erwann->Clone();
  crossSectionRatio_EG2->SetName("crossSectionRatio_EG2");
  crossSectionRatio_EG2->SetTitle(";E_{T};#frac{CrossSection_{Erwann}}{CrossSection_{Dhruv}}");
  crossSectionRatio_EG2->Divide(crossSection_EG2);
  crossSectionRatio_EG2->GetXaxis()->SetRangeUser(12,60);
  crossSectionRatio_EG2->GetYaxis()->SetRangeUser(0,2);
  crossSectionRatio_EG2->SetLineColor(kGreen);
  crossSectionRatio_EG2->SetMarkerColor(kGreen);

  
  TLegend* legRatio = new TLegend(0.5,0.8,0.65,0.87);
  legRatio->AddEntry(crossSectionRatio_EG1,"EG1 trigger");
  legRatio->AddEntry(crossSectionRatio_EG2,"EG2 trigger");

  //Ratio with Erwann
  TCanvas* cRatio = new TCanvas();
  crossSectionRatio_EG1->Draw("e1");
  crossSectionRatio_EG2->Draw("samee1");
  legRatio->Draw("samee1");
  line->Draw("same");//*/
  
  
  

  //TFile* outputfile = TFile
  
}
