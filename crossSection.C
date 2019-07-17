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
  TFile* dataFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_wNonLinCorr_cluster_emcalTrig_Allevent_wEventSelect_allClusCutsTimeCutAcceptanceCut_noDownScale_2piNevdEdEtaPhi_fernandoIsoDef_wPurityFitFunction_nonLinCorrTest.root", "READ");


  //pp
  TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_cluster_emcalTrig_Allevent_wEventSelect_allClusCutsTimeCutAcceptanceCut_noDownScale_2piNevdEdEtaPhi_newIsoDef_wPurityFitFunction_ZcutsFirst.root", "READ");


  TH1F* hClusterSpectra_pp = (TH1F*)dataFile_pp->Get("hCluster_pt");
  TH1F* hClusterSpectra_pPb = (TH1F*)dataFile_pPb->Get("hCluster_pt");
  TH1D* hNumEvents = (TH1D*)dataFile_pPb->Get("hNormalizer");

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
  legYield->AddEntry(hClusterSpectra_pPb,"pPb (13d)");
  legYield->AddEntry(hClusterSpectra_pp,"pp (17q)");


  //Obtain and plotting histograms from MC
  TFile* mcFile = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_MKevents_erwanbinning_noNorm_newIsoDef_acceptanceCuts2.root","READ"); 
  //TFile* mcFile = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/18g7a_MKevents_erwanbinning_noNorm_newIsoDef_acceptanceCuts2.root","READ"); 
  

  TH1D* hEff = (TH1D*)mcFile->Get("hEfficiency");
  hEff->SetName("hEff");
  hEff->SetTitle("Global Isolation Efficiency; E_{T} [GeV]; #epsilon");
  hEff->GetYaxis()->SetRangeUser(0,1);
  hEff->SetLineColor(kBlack);
  hEff->SetMarkerColor(kBlack);
  hEff->SetMarkerStyle(4);

  //Luminosity Calulation
  double Nevtot = hNumEvents->GetBinContent(3);
  double NevEG1 = hNumEvents->GetBinContent(5);
  double NevEG2 = hNumEvents->GetBinContent(6);
  cout << NevEG2 << endl;
  double xSectionMB = 2.11;

  //const double lumi_pPb = 4.64;
  //const double lumi_err_pPb = 0.041;
  
  const double lumi_pPb = 0.531;
  const double lumi_error_pPb = .006;
  double relLumiError_pPb = lumi_error_pPb/lumi_pPb;
  const double lumi_pp = 3.97;//0.531;
  const double lumi_error_pp = 0.27;//.006;
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
    double xsection = (content*Nevtot)/(lumi_pp*eff);
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

    double eff = hEff->GetBinContent(i);
    double eff_error = hEff->GetBinError(i);
    double relEffError = eff_error/eff;
    
    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2)+TMath::Power(relLumiError_pPb,2));
    double xsection = (content*Nevtot)/(lumi_pPb*eff);
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
 
    h_RpA->SetBinContent(i, rpa);
    h_RpA->SetBinError(i, rpa_error);
  }

  

  TH1F* crossSection_erwann = (TH1F*)hClusterSpectra_pPb->Clone();
  crossSection_erwann->SetName("crossSection_erwann");
  crossSection_erwann->SetTitle(";E_{T} [GeV]; #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  double erwannMean[9] = {4727.74, 2015.57, 1151.86, 696.985, 444.604, 233.026, 104.87, 38.5216, 7.4227};
  //double erwannMean[9] = {7754.10, 2951.72, 2018.28, 1135.31, 609.94, 338.88, 139.56, 55.48, 11.27};
  double erwannStat[9] = {604.369, 337.901, 71.0714, 51.475, 35.3468, 15.5412, 10.4705, 4.64552, 1.38719};
  double erwannSys[9] = {766.058, 308.501, 167.064, 96.1471, 58.8658, 29.4243, 12.7484, 4.7213, 1.11858};

  for(int i = 6; i < crossSection_erwann->GetNbinsX()+1;i++){
    

    crossSection_erwann->SetBinContent(i, erwannMean[i-6]);
    crossSection_erwann->SetBinError(i, erwannStat[i-6]);
    
  }

  crossSection_erwann->SetLineColor(kBlack);
  crossSection_erwann->SetMarkerStyle(20);
  crossSection_erwann->SetMarkerColor(kBlack);

  crossSection_pp->SetLineColor(kBlue);
  crossSection_pp->SetMarkerStyle(20);
  crossSection_pp->SetMarkerColor(kBlue);

  crossSection_pPb->SetLineColor(kRed);
  crossSection_pPb->SetMarkerStyle(21);
  crossSection_pPb->SetMarkerColor(kRed);
  
  TLegend* leg = new TLegend(0.6,0.7,0.9,0.9);
  leg->SetHeader("p-Pb (13d) and pp (17q)");
  leg->AddEntry(crossSection_pp,"pp");
  leg->AddEntry(crossSection_pPb,"pPb");
  leg->AddEntry(crossSection_erwann,"Erwann's pPb");



  TCanvas* cXSection = new TCanvas();
  cXSection->SetLogy();
  crossSection_pPb->GetXaxis()->SetRangeUser(12,60);
  crossSection_pPb->GetYaxis()->SetRangeUser(1,1e5);
  crossSection_pPb->Draw("e");
  crossSection_pp->Draw("samee");
  crossSection_erwann->Draw("samee");
  leg->Draw("same");

  TCanvas* cYield = new TCanvas();
  cYield->SetLogy();
  hClusterSpectra_pPb->GetXaxis()->SetRangeUser(12,60);
  hClusterSpectra_pPb->Draw("e");
  hClusterSpectra_pp->Draw("samee");
  legYield->Draw("same");

  TCanvas* cEff = new TCanvas();
  hEff->GetXaxis()->SetRangeUser(12,60);
  hEff->Draw("e");


  TH1F* crossSectionRatio = (TH1F*)crossSection_erwann->Clone();
  crossSectionRatio->SetName("crossSectionRatio");
  crossSectionRatio->SetTitle(";E_{T};#frac{CrossSection_{Erwann}}{CrossSection_{Dhruv}}");
  crossSectionRatio->Divide(crossSection_pPb);
  crossSectionRatio->GetXaxis()->SetRangeUser(12,60);
  crossSectionRatio->GetYaxis()->SetRangeUser(0,2);

  TH1F* unity = (TH1F*)crossSection_erwann->Clone();
  unity->SetName("unity");
  unity->Divide(crossSection_erwann);
  unity->SetLineColor(kBlue);

  TCanvas* cRatio = new TCanvas();
  //crossSectionRatio->Draw("e");
  h_RpA->GetXaxis()->SetRangeUser(12,60);
  h_RpA->GetYaxis()->SetRangeUser(0,2);
  h_RpA->Draw("e");
  unity->Draw("histsame");
  
  /*for(int i = 6; i < crossSection_erwann->GetNbinsX()+1;i++){
    
    crossSection_erwann->SetBinContent(i, erwannMean_old[i-6]);
    crossSection_erwann->SetBinError(i, erwannStat[i-6]);
    
    }*/

  
}
