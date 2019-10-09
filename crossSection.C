#include <fstream>
#include <vector>
void crossSection(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  
  



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
  TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_cluster_emcalTrigOnly_1Mevents_eventCounts_wTrigPileUpSkimEGCut.root", "READ");


  //pp
  //TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_cluster_emcalTrig_Allevent_wEventSelect_allClusCutsTimeCutAcceptanceCut_noDownScale_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction_ZcutsFirst.root", "READ");
  //TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_cluster_emcalTrigOnly_Allevent_wEventSelect_allClusCuts_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction.root", "READ");
  //TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_cluster_emcalTrigOnly_Allevent_wEventSelect_allClusCuts_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction_TrigSelComplete.root", "READ");
  TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_cluster_emcalTrigOnly_Allevent_wEventSelect_allClusCuts_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction_TrigSelComplete_FullEMCal.root", "READ");

  TH1F* hClusterSpectra_pp = (TH1F*)dataFile_pp->Get("hCluster_pt");
  TH1F* hClusterSpectra_pPb = (TH1F*)dataFile_pPb->Get("hCluster_pt");
  TH1D* hNumEvents_pPb = (TH1D*)dataFile_pPb->Get("hNormalizer");
  TH1D* hNumEvents_pp = (TH1D*)dataFile_pp->Get("hNormalizer");

  hClusterSpectra_pPb->Sumw2();
  hClusterSpectra_pPb->SetName("hClusterSpectra_pPb");
  hClusterSpectra_pPb->SetTitle(";E_{T} [GeV]; #frac{1}{N_{ev}}#frac{d^{2}N}{dE_{T}d#eta}");
  hClusterSpectra_pPb->SetLineColor(kRed);
  hClusterSpectra_pPb->SetMarkerColor(kRed);
  hClusterSpectra_pPb->SetMarkerStyle(20);

  hClusterSpectra_pp->Sumw2();
  hClusterSpectra_pp->SetName("hClusterSpectra_pp");
  hClusterSpectra_pp->SetTitle(";E_{T} [GeV]; #frac{1}{N_{ev}}#frac{d^{2}N}{dE_{T}d#eta}");
  hClusterSpectra_pp->SetLineColor(kBlue);
  hClusterSpectra_pp->SetMarkerColor(kBlue);
  hClusterSpectra_pp->SetMarkerStyle(20);

  TLegend* legYield = new TLegend(0.6,0.7,0.9,0.9);
  legYield->SetHeader("Photon Yield");
  legYield->AddEntry(hClusterSpectra_pPb,"pPb (13de)");
  legYield->AddEntry(hClusterSpectra_pp,"pp (17q)");


  //Obtain and plotting histograms from MC
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_MKevents_erwanbinning_noNorm_newIsoDef_acceptanceCuts2.root","READ"); 
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration.root","READ"); 
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_dist2BadChn0.root","READ");
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_dist2BadChn1.root","READ");
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_dist2BadChn1_hCorr_corr.root","READ"); 
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_dist2BadChn1_hCorr_corr_ncell1.root","READ"); 
  TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_50Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_hCorr_corr_stdCuts.root","READ"); 


  //TFile* mcFile_pp = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/18g7a_MKevents_erwanbinning_noNorm_newIsoDef_acceptanceCuts2.root","READ"); 
  

  TH1D* hEff_pPb = (TH1D*)mcFile_pPb->Get("hEfficiency");
  hEff_pPb->SetName("hEff_pPb");
  hEff_pPb->SetTitle("; E_{T} [GeV]; #epsilon");
  hEff_pPb->GetYaxis()->SetRangeUser(0,1);
  hEff_pPb->SetLineColor(kRed);
  hEff_pPb->SetMarkerColor(kRed);
  hEff_pPb->SetMarkerStyle(4);

  TH1D* hFakeRate_pPb = (TH1D*)mcFile_pPb->Get("hFakeRate");
  hFakeRate_pPb->SetName("FakeRate_pPb");
  hFakeRate_pPb->SetTitle("; E_{T} [GeV];");
  hFakeRate_pPb->GetYaxis()->SetRangeUser(0,1);
  hFakeRate_pPb->SetLineColor(kBlue);
  hFakeRate_pPb->SetMarkerColor(kBlue);
  hFakeRate_pPb->SetMarkerStyle(4);

  TH1D* hBinMigration_pPb = (TH1D*)mcFile_pPb->Get("hMigEfficiency");
  hBinMigration_pPb->SetName("hbinMigration_pPb");
  hBinMigration_pPb->SetTitle("Bin Migration Effection = #frach{dN^{reco}/dE_{T}^{reco}}{dN^{reco}/dE_{T}^{truth}}; E_{T} [GeV]; #epsilon");
  hBinMigration_pPb->GetYaxis()->SetRangeUser(0,1);
  hBinMigration_pPb->SetLineColor(kMagenta);
  hBinMigration_pPb->SetMarkerColor(kMagenta);
  hBinMigration_pPb->SetMarkerStyle(4);

  TLegend* legEff = new TLegend(0.6,0.7,0.9,0.9);
  legEff->AddEntry(hEff_pPb,"Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso}");
  legEff->AddEntry(hFakeRate_pPb,"Fake rate");
  legEff->AddEntry(hBinMigration_pPb,"Bin Migration");

  //Luminosity Calulation
  double Nevtot_pPb = hNumEvents_pPb->GetBinContent(5);
  double Nevtot_pp = hNumEvents_pp->GetBinContent(3);
  //double NevEG1 = hNumEvents->GetBinContent(5);
  //double NevEG2 = hNumEvents->GetBinContent(6);
  //cout << NevEG2 << endl;
  cout << "pPb Events (tot, EG1, EG2): \t" << hNumEvents_pPb->GetBinContent(5) << "\t" << hNumEvents_pPb->GetBinContent(12) << "\t" << hNumEvents_pPb->GetBinContent(13) << endl;
  cout << "pp Events (tot, EG1, EG2): \t" << hNumEvents_pp->GetBinContent(3) << "\t" << hNumEvents_pp->GetBinContent(5) << "\t" << hNumEvents_pp->GetBinContent(6) << endl;
  double xSectionMB = 2.11;

  //const double lumi_pPb = 4.64;
  //const double lumi_err_pPb = 0.041;
  
  const double lumi_pPb = 1.08;
  const double lumi_error_pPb = 0.10;
  double relLumiError_pPb = lumi_error_pPb/lumi_pPb;
  const double lumi_pp = 5.03;
  const double lumi_error_pp = 0.35;
  double relLumiError_pp = lumi_error_pp/lumi_pp;

  //Cross Section Calculation
  TH1F* crossSection_pp = (TH1F*)hClusterSpectra_pp->Clone();
  crossSection_pp->SetName("crossSection_pp");
  crossSection_pp->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  for(int i = 1; i < crossSection_pp->GetNbinsX()+1;i++){
    
    double content = crossSection_pp->GetBinContent(i);
    double error = crossSection_pp->GetBinError(i);
    double relError = error/content;

    double eff = 0.382;//hEff->GetBinContent(i);
    double eff_error = 0.00355;//hEff->GetBinError(i);
    double relEffError = eff_error/eff;
    
    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2)+TMath::Power(relLumiError_pp,2));
    double xsection = (content*Nevtot_pp)/(lumi_pp*eff);
    double xsection_error = relXSectionError*xsection;

    crossSection_pp->SetBinContent(i, xsection);
    crossSection_pp->SetBinError(i, xsection_error);
    
  }//*/

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
    
    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2)+TMath::Power(relLumiError_pPb,2));
    double xsection = (content*Nevtot_pPb)/(lumi_pPb*eff);
    double xsection_error = relXSectionError*xsection;

    crossSection_pPb->SetBinContent(i, xsection);
    crossSection_pPb->SetBinError(i, xsection_error);
    
  }//*/




  /*////////////////////////////////////////////////////////////////////
    RpA
  
  //////////////////////////////////////////////////////////////*/
  TH1F* h_RpA = (TH1F*)hClusterSpectra_pPb->Clone();
  h_RpA->SetName("h_RpA");
  h_RpA->SetTitle(";E_{T} [GeV]; RpA (#sigma_{pPb}/<N_{coll}#sigma_{pp}>)");
  const double Ncoll = 7.0;
  const double A = 208;
  
  for(int i = 1; i < h_RpA->GetNbinsX()+1;i++){
    
    double content_pPb = crossSection_pPb->GetBinContent(i);
    double error_pPb = crossSection_pPb->GetBinError(i);
    double relError_pPb = error_pPb/content_pPb;

    double content_pp = crossSection_pp->GetBinContent(i);
    double error_pp = crossSection_pp->GetBinError(i);
    double relError_pp = error_pp/content_pp;

    double rpa = content_pPb/(Ncoll*content_pp);
    double rpa_relError = TMath::Sqrt(TMath::Power(relError_pPb,2)+TMath::Power(relError_pp,2));
    double rpa_error = rpa*rpa_relError;
 
    cout << i << "\t" << h_RpA->GetXaxis()->GetBinLowEdge(i) << "\t" << rpa << "\t" << rpa_error << endl;
    h_RpA->SetBinContent(i, rpa);
    h_RpA->SetBinError(i, rpa_error);
  }

  

  TH1F* crossSection_erwann = (TH1F*)hClusterSpectra_pPb->Clone();
  crossSection_erwann->SetName("crossSection_erwann");
  crossSection_erwann->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  TH1F* crossSection_erwann_old = (TH1F*)hClusterSpectra_pPb->Clone();
  crossSection_erwann_old->SetName("crossSection_erwann_old");
  crossSection_erwann_old->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  double erwannMean[9] = {4727.74, 2015.57, 1151.86, 696.985, 444.604, 233.026, 104.87, 38.5216, 7.4227};
  double erwannMean_old[9] = {7754.10, 2951.72, 2018.28, 1135.31, 609.94, 338.88, 139.56, 55.48, 11.27};
  double erwannStat[9] = {604.369, 337.901, 71.0714, 51.475, 35.3468, 15.5412, 10.4705, 4.64552, 1.38719};
  double erwannSys[9] = {766.058, 308.501, 167.064, 96.1471, 58.8658, 29.4243, 12.7484, 4.7213, 1.11858};

  for(int i = 6; i < crossSection_erwann->GetNbinsX()+1;i++){
    

    crossSection_erwann->SetBinContent(i, erwannMean[i-6]);
    crossSection_erwann->SetBinError(i, erwannStat[i-6]);
    crossSection_erwann_old->SetBinContent(i, erwannMean_old[i-6]);
    crossSection_erwann_old->SetBinError(i, erwannStat[i-6]);
    
  }

  crossSection_erwann->SetLineColor(kBlack);
  crossSection_erwann->SetMarkerStyle(20);
  crossSection_erwann->SetMarkerColor(kBlack);

  crossSection_erwann_old->SetLineColor(kCyan);
  crossSection_erwann_old->SetMarkerStyle(20);
  crossSection_erwann_old->SetMarkerColor(kCyan);

  crossSection_pp->SetLineColor(kBlue);
  crossSection_pp->SetMarkerStyle(20);
  crossSection_pp->SetMarkerColor(kBlue);

  crossSection_pPb->SetLineColor(kRed);
  crossSection_pPb->SetMarkerStyle(21);
  crossSection_pPb->SetMarkerColor(kRed);
  
  TLegend* leg = new TLegend(0.6,0.7,0.9,0.9);
  leg->SetHeader("p-Pb (13de) and pp (17q)");
  //leg->AddEntry(crossSection_pp,"pp");
  leg->AddEntry(crossSection_pPb,"pPb");
  leg->AddEntry(crossSection_erwann,"Erwann's pPb");
  leg->AddEntry(crossSection_erwann_old,"Erwann's old pPb");


  TCanvas* cXSection = new TCanvas();
  cXSection->SetLogy();
  crossSection_pPb->GetXaxis()->SetRangeUser(12,60);
  crossSection_pPb->GetYaxis()->SetRangeUser(1,1e5);
  crossSection_pPb->Draw("e");
  //crossSection_pp->Draw("samee");
  crossSection_erwann->Draw("samee");
  crossSection_erwann_old->Draw("samee");
  leg->Draw("same");

  TCanvas* cYield = new TCanvas();
  cYield->SetLogy();
  hClusterSpectra_pPb->GetXaxis()->SetRangeUser(12,60);
  hClusterSpectra_pPb->Draw("e");
  hClusterSpectra_pp->Draw("samee");
  legYield->Draw("same");

  TCanvas* cEff = new TCanvas();
  hEff_pPb->GetXaxis()->SetRangeUser(12,60);
  hEff_pPb->Draw("e");
  hBinMigration_pPb->Draw("samee");
  hFakeRate_pPb->Draw("samee");
  legEff->Draw("same");
    
  TH1F* crossSectionRatio = (TH1F*)crossSection_erwann->Clone();
  crossSectionRatio->SetName("crossSectionRatio");
  crossSectionRatio->SetTitle(";E_{T};#frac{CrossSection_{Erwann}}{CrossSection_{Dhruv}}");
  crossSectionRatio->Divide(crossSection_pPb);
  crossSectionRatio->GetXaxis()->SetRangeUser(12,60);
  crossSectionRatio->GetYaxis()->SetRangeUser(0,2);

  TH1F* crossSectionRatio_old = (TH1F*)crossSection_erwann_old->Clone();
  crossSectionRatio_old->SetName("crossSectionRatio_old");
  crossSectionRatio_old->SetTitle(";E_{T};#frac{CrossSection_{Erwann}}{CrossSection_{Dhruv}}");
  crossSectionRatio_old->Divide(crossSection_pPb);
  crossSectionRatio_old->GetXaxis()->SetRangeUser(12,60);
  crossSectionRatio_old->GetYaxis()->SetRangeUser(0,2);

  
  TH1F* unity = (TH1F*)crossSection_erwann->Clone();
  unity->SetName("unity");
  unity->SetTitle(";E_{T};ratio (#frac{#sigma_{Erwann}}{#sigma_{Dhruv}}");
  unity->Divide(crossSection_erwann);
  unity->SetLineColor(kBlue);
  unity->GetXaxis()->SetRangeUser(12,60);
  unity->GetYaxis()->SetRangeUser(0,2);

  TLegend* legRatio = new TLegend(0.6,0.7,0.9,0.9);
  legRatio->AddEntry(crossSectionRatio,"Erwann's pPb");
  legRatio->AddEntry(crossSectionRatio_old,"Erwann's old pPb");


  TCanvas* cRatio = new TCanvas();
  unity->Draw("hist");
  crossSectionRatio->Draw("samee");
  crossSectionRatio_old->Draw("samee");
  legRatio->Draw("same");
  //h_RpA->GetXaxis()->SetRangeUser(12,60);
  //h_RpA->GetYaxis()->SetRangeUser(0,2);
  //h_RpA->Draw("samee");
  
  

  //TFile* outputfile = TFile
  
}
