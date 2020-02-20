#include <fstream>
#include <vector>
void Run(TString pPbFile, TString ppFile,
	 Double_t pPbRf_EG1, Double_t pPbRfStatErr_EG1,
	 Double_t pPbRf_EG2, Double_t pPbRfStatErr_EG2,
	 Double_t ppRf_EG2, Double_t ppRfStatErr_EG2){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(10);
  
  



  //Obtain and plotting histograms from data
  TFile* dataFile_pPb = new TFile(Form("%s", pPbFile.Data()),"READ");
  TFile* dataFile_pp = new TFile(Form("%s", ppFile.Data()),"READ");

  TH1F* hClusterSpectra_EG1 = (TH1F*)dataFile_pPb->Get("hEG1_E");
  TH1F* hClusterSpectra_EG2 = (TH1F*)dataFile_pPb->Get("hEG2_E");
  TH1F* hClusterSpectra_pp = (TH1F*)dataFile_pp->Get("hEG2_caloE");

  hClusterSpectra_EG1->Sumw2();
  hClusterSpectra_EG1->SetName("hClusterSpectra_EG1");
  hClusterSpectra_EG1->SetTitle(";E_{T} [GeV]; #frac{1}{N_{ev}}#frac{d^{2}N}{dE_{T}d#eta}");
  hClusterSpectra_EG1->SetLineColor(kRed);
  hClusterSpectra_EG1->SetMarkerColor(kRed);
  hClusterSpectra_EG1->SetMarkerStyle(21);
  hClusterSpectra_EG1->SetMarkerSize(2);

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
  legYield->AddEntry(hClusterSpectra_EG1,"pPb EG1");
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
  TH1D* hNumEvents_pPb = (TH1D*)dataFile_pPb->Get("hNormalizer");
  TH1D* hNumEvents_pp = (TH1D*)dataFile_pp->Get("hNormalizer");

  double Nevtot_EG1 = hNumEvents_pPb->GetBinContent(12);
  double Nevtot_pp = hNumEvents_pp->GetBinContent(11);
  double Nevtot_EG2 = hNumEvents_pPb->GetBinContent(13);
  cout << "Numbers of events" << endl;
  cout << "p-Pb EG1: " << Nevtot_EG1 << endl;
  cout << "p-Pb EG2: " << Nevtot_EG2 << endl;
  cout << "pp EG2: " << Nevtot_pp << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  const double pPb_xs = 2.11E+00;
  const double pPb_xsErr = 5.50E-02;
  const double pp_xs = 5.09E-02;
  const double pp_xsErr = 4.00E-05;
    
  double lumi_EG1 = ((pPbRf_EG1*Nevtot_EG1)/pPb_xs)*1.00E-09;
  double relLumiError_EG1 = TMath::Sqrt(TMath::Power((pPbRfStatErr_EG1/pPbRf_EG1), 2)+TMath::Power((pPb_xsErr/pPb_xs), 2));
  double lumi_error_EG1 = lumi_EG1*relLumiError_EG1;
  double lumi_EG2 = ((pPbRf_EG2*Nevtot_EG2)/pPb_xs)*1.00E-09;
  double relLumiError_EG2 = TMath::Sqrt(TMath::Power((pPbRfStatErr_EG2/pPbRf_EG2), 2)+TMath::Power((pPb_xsErr/pPb_xs), 2));
  double lumi_error_EG2 = lumi_EG2*relLumiError_EG2;
  double lumi_pp = ((ppRf_EG2*Nevtot_pp)/pp_xs)*1.00E-09;
  double relLumiError_pp = TMath::Sqrt(TMath::Power((ppRfStatErr_EG2/ppRf_EG2), 2)+TMath::Power((pp_xsErr/pp_xs),2));
  double lumi_error_pp = lumi_pp*relLumiError_pp;

  cout << "Luminosity" << endl;
  cout << "p-Pb EG1:" << lumi_EG1 << " +/- " << lumi_error_EG1 << endl;
  cout << "p-Pb EG2:" << lumi_EG2 << " +/- " << lumi_error_EG2 << endl;
  cout << "pp EG2:" << lumi_pp << " +/- " << lumi_error_pp << endl;
  
  //Cross Section Calculation  
  /*////////////////////////////////////////////////////////////
    pPb cross section using EG1 trigger
  ///////////////////////////////////////////////////////////*/
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n p-Pb EG1 trigger cross section \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  TH1F* crossSection_pPb = (TH1F*)hClusterSpectra_EG1->Clone();
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

    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2)+TMath::Power(relLumiError_EG1,2));
    double xsection = (content*Nevtot_EG1)/(lumi_EG1*eff);
    double xsection_error = relXSectionError*xsection;

    //cout statement
    cout << crossSection_pPb->GetBinLowEdge(i) << "\t" << crossSection_pPb->GetBinLowEdge(i+1) << "\t" << content << "\t" << Nevtot_EG1 << "\t" << lumi_EG1 << "\t" << eff << "\t" << xsection << endl;

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
 
  TH1F* h_RpA = (TH1F*)hClusterSpectra_EG1->Clone();
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

  

  TH1F* crossSection_erwann = (TH1F*)hClusterSpectra_EG1->Clone();
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
  hClusterSpectra_EG1->GetXaxis()->SetRangeUser(12,60);
  hClusterSpectra_EG1->GetYaxis()->SetRangeUser(1e-8,1e-2);
  hClusterSpectra_EG1->Draw("e1");
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

  //Writing to file
  int startingPoint = pPbFile.Index("bins_")+5;
  int endingPoint = pPbFile.Index("cluster")-1;
  TString outputName = pPbFile(startingPoint, endingPoint-startingPoint);
  cout << "writing to file" << endl;
  TFile* fout = new TFile(Form("xSectionHists/%s_crossSectionHistos_CaloITS_367to365_540.root",outputName.Data()), "RECREATE");
  crossSection_pPb->Write("crossSection_pPb");
  crossSection_EG2->Write("crossSection_EG2");
  crossSection_pp->Write("crossSection_pp");
  h_RpA->Write("h_RpA");
  crossSectionRatio_EG1->Write("crossSectionRatio_EG1");
  crossSectionRatio_EG2->Write("crossSectionRatio_EG2");
  fout->Close();
  cout << "done writing to file" << endl;//*/



}//end Run()
void crossSection(){

  /*Run(TString pPbFile, 
    TString ppFile,
    Double_t pPb_RF_EG1, Double_t pPb_RF_statErr_EG1, 
    Double_t pPb_RF_EG2, Double_t pPb_RF_statErr_EG2, 
    Double_t pp_RF_EG2, Double_t pp_RF_statErr_EG2)//*/ 


  /*Run("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13fpart12345_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root",
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_EG2_caloE_vs_cluster_pt_Normalized.root",
      5528, 233, 1454, 35, 959, 87);//*/

  //13d
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_all10runs_noSkim_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_EG2_caloE_vs_cluster_pt_Normalized.root", 5421, 277, 1521, 43, 959, 87);//*/

  //13e
  //Run("/project/projectdirs//alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13epart12_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_EG2_caloE_vs_cluster_pt_Normalized.root", 6151, 298, 1569, 43, 959, 87);//*/
  
  //13f
  //Run("/project/projectdirs//alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13fpart12345_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_12_14bins_17q_CENT_wSDD_noThresh_MBcentEGcaloEGcent_Normalized_EMCgoodOnly.root", 5750, 279, 1505, 41, 584, 14);//*/
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part1_new_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_EG2_caloE_vs_cluster_pt_Normalized.root", 6036, 293, 1572, 44, 959, 87);//*/
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part2_new_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_EG2_caloE_vs_cluster_pt_Normalized.root", 5582, 271, 1456, 41, 959, 87);//*/
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part3_newer_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_EG2_caloE_vs_cluster_pt_Normalized.root", 5356, 260, 1396, 39, 959, 87);//*/
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part4_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_EG2_caloE_vs_cluster_pt_Normalized.root", 6122, 298, 1589, 45, 959, 87);//*/
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_part5_new_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_17q_CENT_wSDD_noThresh_EG2_caloE_vs_cluster_pt_Normalized.root", 6190, 301, 1587, 45, 959, 87);//*/




  Run("/project/projectdirs//alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13fpart12345_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_12_14bins_17q_CENT_wSDD_noThresh_MBcentEGcaloEGcent_Normalized_EMCgoodOnly_bugFixed2.root", 5750, 279, 1505, 41, 672, 6);//*/
  //Run("/project/projectdirs//alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13fpart12345_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_14bins_17q_CENT_wSDD_noThresh_MB_Normalized_allEMCgoodOnly_bugFixed2_399to391.root", 5750, 279, 1505, 41, 678, 6);//*/
  //Run("/project/projectdirs//alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13fpart12345_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_14bins_17q_CENT_wSDD_noThresh_MB_Normalized_allEMCgoodOnly_bugFixed2_415to402.root", 5750, 279, 1505, 41, 677, 6);//*/
  //Run("/project/projectdirs//alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13fpart12345_cluster_emcalTrigOnly_Allevents_wTrigPileUpSkimEGCut_MBEG1EG2seperate_purityCorr_etaPhiAcceptance_new.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_14bins_17q_CENT_wSDD_noThresh_MB_Normalized_allEMCgoodOnly_bugFixed2_441to437.root", 5750, 279, 1505, 41, 702, 6 );//*/



}//end crossSection
