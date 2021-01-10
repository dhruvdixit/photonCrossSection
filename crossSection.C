
#include <fstream>
#include <vector>
void Run(TString pPbFile, TString ppFile,
	 TString pPbFile_MC, TString ppFile_MC,
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
  hClusterSpectra_EG1->SetTitle(";E_{T} (GeV); #frac{1}{N_{ev}}#frac{d^{2}N}{dE_{T}d#eta}");
  hClusterSpectra_EG1->SetLineColor(kRed);
  hClusterSpectra_EG1->SetMarkerColor(kRed);
  hClusterSpectra_EG1->SetMarkerStyle(21);
  hClusterSpectra_EG1->SetMarkerSize(2);

  hClusterSpectra_pp->Sumw2();
  hClusterSpectra_pp->SetName("hClusterSpectra_pp");
  hClusterSpectra_pp->SetTitle(";E_{T} (GeV); #frac{1}{N_{ev}}#frac{d^{2}N}{dE_{T}d#eta}");
  hClusterSpectra_pp->SetLineColor(kBlue);
  hClusterSpectra_pp->SetMarkerColor(kBlue);
  hClusterSpectra_pp->SetMarkerStyle(20);
  hClusterSpectra_pp->SetMarkerSize(2);

  hClusterSpectra_EG2->Sumw2();
  hClusterSpectra_EG2->SetName("hClusterSpectra_EG2");
  hClusterSpectra_EG2->SetTitle(";E_{T} (GeV); #frac{1}{N_{ev}}#frac{d^{2}N}{dE_{T}d#eta}");
  hClusterSpectra_EG2->SetLineColor(kGreen);
  hClusterSpectra_EG2->SetMarkerColor(kGreen);
  hClusterSpectra_EG2->SetMarkerStyle(21);
  hClusterSpectra_EG2->SetMarkerSize(2);

  
  TLegend* legYield = new TLegend(0.6,0.7,0.85,0.85);
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
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_50Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_hCorr_corr_stdCuts.root","READ");//main use
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffTogether_cutFlow_binMigration_hCorr_corr_stdCuts.root","READ");
  //TFile* mcFile_pPb = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/17g6a1_100Kevents_erwanbinning_noNorm_allCutsEff2_yesNoISOSSC_SSCPlots_UEstudyIsoStd.root","READ");
  //TFile* mcFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutrals.root", "READ");
  TFile* mcFile_pPb = new TFile(Form("%s", pPbFile_MC.Data()),"READ");

  TH1D* hEff_pPb = (TH1D*)mcFile_pPb->Get("hTotalEfficiency");
  hEff_pPb->SetName("hEff_pPb");
  hEff_pPb->SetTitle("; E_{T} (GeV); #epsilon^{iso}_{gamma}");
  hEff_pPb->GetYaxis()->SetRangeUser(0,1);
  hEff_pPb->SetLineColor(kRed);
  hEff_pPb->SetMarkerColor(kRed);
  hEff_pPb->SetMarkerStyle(kFullCircle);
  //hEff_pPb->SetMarkerSize(2);
  //hEff_pPb->SetLineWidth(2);

  /*TH1D* hFakeRate_pPb = (TH1D*)mcFile_pPb->Get("hFakeRate");
  hFakeRate_pPb->SetName("FakeRate_pPb");
  hFakeRate_pPb->SetTitle("; E_{T} (GeV);");
  hFakeRate_pPb->GetYaxis()->SetRangeUser(0,1);
  hFakeRate_pPb->SetLineColor(kBlue);
  hFakeRate_pPb->SetMarkerColor(kBlue);
  hFakeRate_pPb->SetMarkerStyle(24);
  hFakeRate_pPb->SetMarkerSize(2);
  hFakeRate_pPb->SetLineWidth(2);
  
  TH1D* hBinMigration_pPb = (TH1D*)mcFile_pPb->Get("hMigEfficiency");
  hBinMigration_pPb->SetName("hbinMigration_pPb");
  hBinMigration_pPb->SetTitle("Bin Migration Effection = #frach{dN^{reco}/dE_{T}^{reco}}{dN^{reco}/dE_{T}^{truth}}; E_{T} (GeV); #epsilon");
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
  hBinMigration_pPb->SetTitle(";E_{T} (GeV); #frac{truth}{reco}");
  hBinMigration_pPb->SetLineColor(kMagenta);
  hBinMigration_pPb->SetMarkerColor(kMagenta);
  hBinMigration_pPb->SetMarkerStyle(24);
  hBinMigration_pPb->SetMarkerSize(3);//*/
  for(int i = 1; i < hEff_pPb->GetNbinsX()+1; i++){
    cout << hEff_pPb->GetBinLowEdge(i) << "\t" << hEff_pPb->GetBinLowEdge(i+1) << "\t" << hEff_pPb->GetBinContent(i) << "\t" << hEff_pPb->GetBinError(i) << endl;
  }
  
  //TFile* mcFile_pp = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/18b10a_Allevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_hCorr_corr_stdCuts.root","READ");
  //TFile* mcFile_pp = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/18b10a_100Kevents_erwanbinning_noNorm_allCutsEff2_yesNoISOSSC_SSCPlots_UEstudyIsoStd.root","READ");
  //TFile* mcFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutrals.root","READ");
  //TFile* mcFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/FullStats/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsFullStats.root","READ");
  TFile* mcFile_pp = new TFile(Form("%s", ppFile_MC.Data()),"READ");
  
  TH1D* hEff_pp = (TH1D*)mcFile_pp->Get("hTotalEfficiency");
  hEff_pp->SetName("hEff_pp");
  hEff_pp->SetTitle("; E_{T} (GeV); #epsilon");
  hEff_pp->GetYaxis()->SetRangeUser(0,1);
  hEff_pp->SetLineColor(kBlue);
  hEff_pp->SetMarkerColor(kBlue);
  hEff_pp->SetMarkerStyle(kFullSquare);
  //hEff_pp->SetMarkerSize(1);
  //hEff_pp->SetLineWidth(2);

  /*TH1D* hFakeRate_pp = (TH1D*)mcFile_pp->Get("hFakeRate");
  hFakeRate_pp->SetName("FakeRate_pp");
  hFakeRate_pp->SetTitle("; E_{T} (GeV);");
  hFakeRate_pp->GetYaxis()->SetRangeUser(0,1);
  hFakeRate_pp->SetLineColor(kBlue);
  hFakeRate_pp->SetMarkerColor(kBlue);
  hFakeRate_pp->SetMarkerStyle(21);
  hFakeRate_pp->SetMarkerSize(1);
  hFakeRate_pp->SetLineWidth(2);
  
  TH1D* hBinMigration_pp = (TH1D*)mcFile_pp->Get("hMigEfficiency");
  hBinMigration_pp->SetName("hbinMigration_pp");
  hBinMigration_pp->SetTitle("Bin Migration Effection = #frach{dN^{reco}/dE_{T}^{reco}}{dN^{reco}/dE_{T}^{truth}}; E_{T} (GeV); #epsilon");
  hBinMigration_pp->GetYaxis()->SetRangeUser(0,1);
  hBinMigration_pp->SetLineColor(kMagenta);
  hBinMigration_pp->SetMarkerColor(kMagenta);
  hBinMigration_pp->SetMarkerStyle(21);
  hBinMigration_pp->SetMarkerSize(1);
  hBinMigration_pp->SetLineWidth(2);//*/
  
  TLegend* legEff = new TLegend(0.25,0.13,0.85,0.45);
  //legEff->AddEntry(hEff_pPb,"5 TeV p-Pb GJ MC 17g6a1: Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso} / bin migration");
  //legEff->AddEntry(hFakeRate_pPb,"p-Pb: Fake rate");
  //legEff->AddEntry(hBinMigration_pPb,"p-Pb: Bin Migration");
  //legEff->AddEntry(hEff_pp,"5 TeV pp GJ MC 18b10a: Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso} / bin migration");
  //legEff->AddEntry(hFakeRate_pp,"pp: Fake rate");
  //legEff->AddEntry(hBinMigration_pp,"pp: Bin Migration");
  legEff->AddEntry((TObject*)0, "ALICE", "");
  legEff->AddEntry((TObject*)0, "#sqrt{s_{NN}} = 5.02 TeV", "");
  legEff->AddEntry(hEff_pPb,"p-Pb Monte Carlo: Pythia #gamma-Jet in DPMJET");
  legEff->AddEntry(hEff_pp,"pp Monte Carlo: Pythia #gamma-Jet");

  
  TCanvas* cEff = new TCanvas();
  hEff_pPb->GetXaxis()->SetRangeUser(12,60);
  hEff_pPb->Draw("e1");
  //hBinMigration_pPb->Draw("samee1");
  //hFakeRate_pPb->Draw("samee1");
  hEff_pp->Draw("samee1");
  //hBinMigration_pp->Draw("samee1");
  //hFakeRate_pp->Draw("samee1");
  legEff->Draw("same");//*/
  //cEff->SaveAs("efficiency.pdf");

  //Efficiency systematic
  TFile* effFile = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/efficiencySystematics.root","READ");
  TH1F* hSSCDiff_pPb = (TH1F*)effFile->Get("hSSCDiff_pPb");
  TH1F* hSSCDiff_pp = (TH1F*)effFile->Get("hSSCDiff_pp");
  TH1F* hISODiff_pPb = (TH1F*)effFile->Get("hISODiff_pPb");
  TH1F* hISODiff_pp = (TH1F*)effFile->Get("hISODiff_pp");
  bool calcEffSys = false;
  TString type = "ISO";
  double multiplier = 1.0;
  
  //Luminosity Calulation
  TH1D* hNumEvents_pPb = (TH1D*)dataFile_pPb->Get("hNormalizer");
  TH1D* hNumEvents_pp = (TH1D*)dataFile_pp->Get("hNormalizer");

  double Nevtot_EG1 = hNumEvents_pPb->GetBinContent(12);
  double Nevtot_pp = hNumEvents_pp->GetBinContent(11);
  double Nevtot_EG2 = hNumEvents_pPb->GetBinContent(13);
  double Nevtot_pPb = Nevtot_EG1 + Nevtot_EG2;
  
  cout << "Numbers of events" << endl;
  cout << "p-Pb EG1: " << Nevtot_EG1 << endl;
  cout << "p-Pb EG2: " << Nevtot_EG2 << endl;
  cout << "p-Pb: " << Nevtot_pPb << endl;
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
  double lumi_pPb = ((pPbRf_EG1*Nevtot_EG1 + pPbRf_EG2*Nevtot_EG2)/pPb_xs)*1.00E-09;
  double relLumiError_pPb = TMath::Sqrt(TMath::Power((pPbRfStatErr_EG1/pPbRf_EG1), 2)+TMath::Power((pPbRfStatErr_EG2/pPbRf_EG2), 2)+TMath::Power((pPb_xsErr/pPb_xs), 2));
  double lumi_error_pPb = lumi_pPb*relLumiError_pPb;
  double lumi_pp = ((ppRf_EG2*Nevtot_pp)/pp_xs)*1.00E-09;
  double relLumiError_pp = TMath::Sqrt(TMath::Power((ppRfStatErr_EG2/ppRf_EG2), 2)+TMath::Power((pp_xsErr/pp_xs),2));
  double lumi_error_pp = lumi_pp*relLumiError_pp;
  
  //lumi_EG1 = lumi_EG1-lumi_error_EG1;
  //lumi_EG2 = lumi_EG2-lumi_error_EG2;
  //lumi_pp = lumi_pp-lumi_error_pp;
  
  cout << "Luminosity" << endl;
  cout << "p-Pb EG1:" << lumi_EG1 << " +/- " << lumi_error_EG1 << endl;
  cout << "p-Pb EG2:" << lumi_EG2 << " +/- " << lumi_error_EG2 << endl;
  cout << "p-Pb:" << lumi_pPb << " +/- " << lumi_error_pPb << endl;
  cout << "pp:" << lumi_pp << " +/- " << lumi_error_pp << endl;
  
  //Cross Section Calculation
    /*////////////////////////////////////////////////////////////
    pPb cross section using EG1 and EG2 trigger
  ///////////////////////////////////////////////////////////*/
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n p-Pb cross section \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  TH1F* crossSection_pPb = (TH1F*)hClusterSpectra_EG1->Clone();
  crossSection_pPb->SetName("crossSection_pPb");
  crossSection_pPb->SetTitle(";E_{T} (GeV); #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  for(int i = 1; i < crossSection_pPb->GetNbinsX()+1;i++){

    double contentEG1 = hClusterSpectra_EG1->GetBinContent(i);
    double errorEG1 = hClusterSpectra_EG1->GetBinError(i);
    double relErrorEG1 = errorEG1/contentEG1;

    double contentEG2 = hClusterSpectra_EG2->GetBinContent(i);
    double errorEG2 = hClusterSpectra_EG2->GetBinError(i);
    double relErrorEG2 = errorEG2/contentEG2;

    double weightSum = errorEG1+errorEG2;
    double weightEG1 = 1.0-errorEG1/weightSum;
    double weightEG2 = 1.0-errorEG2/weightSum;
    double content = contentEG1*weightEG1+contentEG2*weightEG2;
    double error = TMath::Sqrt(TMath::Power(errorEG1, 2) + TMath::Power(errorEG2, 2));
    double relError = error/content;

    double eff = hEff_pPb->GetBinContent(i);
    double eff_error = hEff_pPb->GetBinError(i);
    double relEffError = eff_error/eff;

    //double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2)+TMath::Power(relLumiError_pPb,2));
    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2));
    double xsection = (content*Nevtot_pPb)/(lumi_pPb*eff);
    double xsection_error = relXSectionError*xsection;

    //cout statement
    //cout << crossSection_pPb->GetBinLowEdge(i) << "\t" << crossSection_pPb->GetBinLowEdge(i+1) << "\t" << contentEG1 << "\t" << contentEG2 << "\t" << lumi_pPb << "\t" << eff << "\t" << xsection << endl;
    cout << crossSection_pPb->GetBinLowEdge(i) << "\t" << crossSection_pPb->GetBinLowEdge(i+1) << "\t" << content << "\t" << Nevtot_pPb << "\t" << lumi_pPb << "\t" << eff << "\t" << xsection << endl;

    //filling the cross section hist
    crossSection_pPb->SetBinContent(i, xsection);
    crossSection_pPb->SetBinError(i, xsection_error);
    
  }//*/
  
  /*////////////////////////////////////////////////////////////
    pPb cross section using EG1 trigger
  ///////////////////////////////////////////////////////////*/
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n p-Pb EG1 trigger cross section \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  TH1F* crossSection_EG1 = (TH1F*)hClusterSpectra_EG1->Clone();
  crossSection_EG1->SetName("crossSection_EG1");
  crossSection_EG1->SetTitle(";E_{T} (GeV); #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  for(int i = 1; i < crossSection_EG1->GetNbinsX()+1;i++){
    
    double content = crossSection_EG1->GetBinContent(i);
    double error = crossSection_EG1->GetBinError(i);
    double relError = error/content;

    double eff = hEff_pPb->GetBinContent(i);
    double eff_error = hEff_pPb->GetBinError(i);
    double relEffError = eff_error/eff;

    if(calcEffSys){
      if(type == (TString)"SSC"){
	double effSys = hSSCDiff_pPb->GetBinContent(i);
	eff = eff + multiplier*effSys;
      }
      if(type == (TString)"ISO"){
	double effSys = hISODiff_pPb->GetBinContent(i);
	eff = eff + multiplier*effSys;
      }
    }
    //double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2)+TMath::Power(relLumiError_EG1,2));
    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2));
    double xsection = (content*Nevtot_EG1)/(lumi_EG1*eff);
    double xsection_error = relXSectionError*xsection;

    //cout statement
    cout << crossSection_EG1->GetBinLowEdge(i) << "\t" << crossSection_EG1->GetBinLowEdge(i+1) << "\t" << content << "\t" << Nevtot_EG1 << "\t" << lumi_EG1 << "\t" << eff << "\t" << xsection <<  "\t" << xsection_error << endl;

    //filling the cross section hist
    crossSection_EG1->SetBinContent(i, xsection);
    crossSection_EG1->SetBinError(i, xsection_error);
    
  }//*/
  
  /*////////////////////////////////////////////////////////////
    pPb cross section using EG2 trigger
  ///////////////////////////////////////////////////////////*/
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n pp EG2 trigger cross section \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  TH1F* crossSection_EG2 = (TH1F*)hClusterSpectra_EG2->Clone();
  crossSection_EG2->SetName("crossSection_EG2");
  crossSection_EG2->SetTitle(";E_{T} (GeV); #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  for(int i = 1; i < crossSection_EG2->GetNbinsX()+1;i++){
    
    double content = crossSection_EG2->GetBinContent(i);
    double error = crossSection_EG2->GetBinError(i);
    double relError = error/content;

    double eff = hEff_pPb->GetBinContent(i);
    double eff_error = hEff_pPb->GetBinError(i);
    double relEffError = eff_error/eff;

    if(calcEffSys){
      if(type == (TString)"SSC"){
	double effSys = hSSCDiff_pPb->GetBinContent(i);
	eff = eff + multiplier*effSys;
      }
      if(type == (TString)"ISO"){
	double effSys = hISODiff_pPb->GetBinContent(i);
	eff = eff + multiplier*effSys;
      }
    }
    
    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2));
    double xsection = (content*Nevtot_EG2)/(lumi_EG2*eff);
    double xsection_error = relXSectionError*xsection;

    //cout statement
    cout << crossSection_EG1->GetBinLowEdge(i) << "\t" << crossSection_EG1->GetBinLowEdge(i+1) << "\t" << content << "\t" << Nevtot_EG2 << "\t" << lumi_EG2 << "\t" << eff << "\t" << xsection <<  "\t" << xsection_error << endl;

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
  crossSection_pp->SetTitle(";E_{T} (GeV); #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  TH1F* crossSection_ppScaled = (TH1F*)hClusterSpectra_pp->Clone();
  crossSection_ppScaled->SetName("crossSection_ppScaled");
  crossSection_ppScaled->SetTitle(";E_{T} (GeV); #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  const double Ncoll = 7.0;
  const double A = 208;
  for(int i = 1; i < crossSection_pp->GetNbinsX()+1;i++){
    
    double content = crossSection_pp->GetBinContent(i);
    double error = crossSection_pp->GetBinError(i);
    double relError = error/content;

    double eff = hEff_pp->GetBinContent(i);
    double eff_error = hEff_pp->GetBinError(i);
    double relEffError = eff_error/eff;
    
    if(calcEffSys){
      if(type == (TString)"SSC"){
	double effSys = hSSCDiff_pp->GetBinContent(i);
	eff = eff + multiplier*effSys;
      }
      if(type == (TString)"ISO"){
	double effSys = hISODiff_pp->GetBinContent(i);
	eff = eff + multiplier*effSys;
      }
    }

    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2));
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
    Erwann's p-Pb
  ////////////////////////////////////////////////////////////////////*/
  TH1F* crossSection_erwann = (TH1F*)hClusterSpectra_EG1->Clone();
  crossSection_erwann->SetName("crossSection_erwann");
  crossSection_erwann->SetTitle(";E_{T} (GeV); #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  
  double erwannMean[9] = {4727.74, 2015.57, 1151.86, 696.985, 444.604, 233.026, 104.87, 38.5216, 7.4227};
  double erwannStat[9] = {604.369, 337.901, 71.0714, 51.475, 35.3468, 15.5412, 10.4705, 4.64552, 1.38719};
  double erwannSys[9] = {766.058, 308.501, 167.064, 96.1471, 58.8658, 29.4243, 12.7484, 4.7213, 1.11858};

  for(int i = 6; i < crossSection_erwann->GetNbinsX()+1;i++){
    
    double errorErwannTotal = TMath::Sqrt(TMath::Power(erwannStat[i-6],2)+TMath::Power(erwannSys[i-6],2));
    crossSection_erwann->SetBinContent(i, erwannMean[i-6]);
    crossSection_erwann->SetBinError(i, erwannStat[i-6]);
    //crossSection_erwann->SetBinError(i, errorErwannTotal);
    
  }
  /*////////////////////////////////////////////////////////////////////
    RpA
  ////////////////////////////////////////////////////////////////////*/
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n RpA \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
 
  TH1F* h_RpA = (TH1F*)hClusterSpectra_EG1->Clone();
  h_RpA->SetName("h_RpA");
  h_RpA->SetTitle(";E_{T} (GeV); RpA (#sigma_{pPb}/A_{Pb}#sigma_{pp})");
  for(int i = 1; i < h_RpA->GetNbinsX()+1;i++){
    
    double content_pPb = crossSection_EG1->GetBinContent(i);
    double error_pPb = crossSection_EG1->GetBinError(i);
    //double content_pPb = crossSection_erwann->GetBinContent(i);
    //double error_pPb = crossSection_erwann->GetBinError(i);
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
    //cout  << h_RpA->GetXaxis()->GetBinLowEdge(i) << "\t" << h_RpA->GetXaxis()->GetBinLowEdge(i+1) << "\t"<< content_pPb << "\t" << content_pp << "\t" << content_pPb/((double)A*content_pp) << "\t" << rpa << "\t" << rpa_error << endl;
    cout  << h_RpA->GetXaxis()->GetBinLowEdge(i) << "\t" << h_RpA->GetXaxis()->GetBinLowEdge(i+1) << "\t"<< "\t" << rpa << "\t" << rpa_error << "\t" << rpa_error/rpa << endl;

    //Filling in the rpa
    h_RpA->SetBinContent(i, rpa);
    h_RpA->SetBinError(i, rpa_error);
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
  
  crossSection_EG1->SetLineColor(kRed);
  crossSection_EG1->SetMarkerStyle(21);
  crossSection_EG1->SetMarkerColor(kRed);
  crossSection_EG1->SetMarkerSize(2);
  
  crossSection_EG2->SetLineColor(kGreen);
  crossSection_EG2->SetMarkerStyle(21);
  crossSection_EG2->SetMarkerColor(kGreen);
  crossSection_EG2->SetMarkerSize(2);

  crossSection_pPb->SetLineColor(kMagenta);
  crossSection_pPb->SetMarkerStyle(21);
  crossSection_pPb->SetMarkerColor(kMagenta);
  crossSection_pPb->SetMarkerSize(2);
  
  //unity --> line at 1
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);

  
  TLegend* leg = new TLegend(0.12,0.12,0.47,0.4);
  leg->AddEntry((TObject*)0, "ALICE Isolated Photon Cross Section", "");
  leg->AddEntry((TObject*)0, "pp and p-Pb #sqrt{s_{NN}} = 5.02 TeV", "");
  leg->AddEntry(crossSection_pp,"pp");
  leg->AddEntry(crossSection_ppScaled,"pp*A(208)");
  leg->AddEntry(crossSection_EG1,"p-Pb_{EG1}");
  leg->AddEntry(crossSection_EG2,"p-Pb_{EG2}");
  leg->AddEntry(crossSection_pPb,"p-Pb");
  leg->AddEntry(crossSection_erwann,"Erwann's p-Pb");


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
  crossSection_EG1->GetXaxis()->SetRangeUser(12,60);
  crossSection_EG1->GetYaxis()->SetRangeUser(1e-4,1e4);
  crossSection_EG1->Draw("e1");
  crossSection_pp->Draw("samee1");
  crossSection_ppScaled->Draw("samee1");
  crossSection_EG2->Draw("samee1");
  crossSection_pPb->Draw("samee1");
  crossSection_erwann->Draw("samee1");
  leg->Draw("same");

  TCanvas* cRpa = new TCanvas();
  h_RpA->GetXaxis()->SetRangeUser(12,60);
  h_RpA->GetYaxis()->SetRangeUser(0,2);
  h_RpA->SetMarkerSize(2);
  h_RpA->Draw("e1");
  line->Draw("same");

  h_RpA->Fit("pol0", "", "", 12, 60);
  TF1* f_RpA = (TF1*)h_RpA->GetFunction("pol0");
  TLegend* legRpA = new TLegend(0.5,0.8,0.85,0.87);
  legRpA->AddEntry(f_RpA, "Constant fit: 1.05 #pm 0.03");
  legRpA->Draw("same");
    
  TH1F* crossSectionRatio_EG1 = (TH1F*)crossSection_erwann->Clone();
  crossSectionRatio_EG1->SetName("crossSectionRatio_EG1");
  crossSectionRatio_EG1->SetTitle(";E_{T} (GeV);#frac{CrossSection_{Erwann}}{CrossSection_{Dhruv}}");
  crossSectionRatio_EG1->Divide(crossSection_EG1);
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

  TH1F* crossSectionRatio_pPb = (TH1F*)crossSection_erwann->Clone();
  crossSectionRatio_pPb->SetName("crossSectionRatio_pPb");
  crossSectionRatio_pPb->SetTitle(";E_{T};#frac{CrossSection_{Erwann}}{CrossSection_{Dhruv}}");
  crossSectionRatio_pPb->Divide(crossSection_pPb);
  crossSectionRatio_pPb->GetXaxis()->SetRangeUser(12,60);
  crossSectionRatio_pPb->GetYaxis()->SetRangeUser(0,2);
  crossSectionRatio_pPb->SetLineColor(kMagenta);
  crossSectionRatio_pPb->SetMarkerColor(kMagenta);

  
  TLegend* legRatio = new TLegend(0.5,0.13,0.75,0.4);
  legRatio->AddEntry(crossSectionRatio_EG1,"EG1 trigger");
  legRatio->AddEntry(crossSectionRatio_EG2,"EG2 trigger");
  //legRatio->AddEntry(crossSectionRatio_pPb,"p-Pb");

  //Ratio with Erwann
  TCanvas* cRatio = new TCanvas();
  crossSectionRatio_EG1->Draw("e1");
  crossSectionRatio_EG2->Draw("samee1");
  //crossSectionRatio_pPb->Draw("samee1");
  legRatio->Draw("samee1");
  line->Draw("same");//*/

  cout << "Cross Section EG1 = {";
  for(int i = 7; i < crossSection_EG1->GetNbinsX()+1; i++){
    cout << crossSection_EG1->GetBinContent(i) << ", ";
  }
  cout << "}" << endl;

  cout << "Cross Section Error EG1 = {";
  for(int i = 7; i < crossSection_EG1->GetNbinsX()+1; i++){
    cout << crossSection_EG1->GetBinError(i) << ", ";
  }
  cout << "}" << endl;


  cout << "Cross Section EG2 = {";
  for(int i = 7; i < crossSection_EG2->GetNbinsX()+1; i++){
    cout << crossSection_EG2->GetBinContent(i) << ", ";
  }
  cout << "}" << endl;

  cout << "Cross Section Error EG2 = {";
  for(int i = 7; i < crossSection_EG2->GetNbinsX()+1; i++){
    cout << crossSection_EG2->GetBinError(i) << ", ";
  }
  cout << "}" << endl;

  cout << "Cross Section pp = {";
  for(int i = 7; i < crossSection_pp->GetNbinsX()+1; i++){
    cout << crossSection_pp->GetBinContent(i) << ", ";
  }
  cout << "}" << endl;

  cout << "Cross Section Error pp = {";
  for(int i = 7; i < crossSection_pp->GetNbinsX()+1; i++){
    cout << crossSection_pp->GetBinError(i) << ", ";
  }
  cout << "}" << endl;

  //Writing to file
  int startingPoint = pPbFile.Index("bins_")+5;
  int endingPoint = pPbFile.Index("cluster")-1;
  TString outputName = pPbFile(startingPoint, endingPoint-startingPoint);
  cout << "writing to file" << endl;
  TFile* fout = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/xSectionHists/%sStdCuts_EX0PurityFit_results.root",outputName.Data()), "RECREATE");
  crossSection_EG1->Write("crossSection_EG1");
  crossSection_EG2->Write("crossSection_EG2");
  crossSection_pPb->Write("crossSection_pPb");
  crossSection_pp->Write("crossSection_pp");
  h_RpA->Write("h_RpA");
  crossSectionRatio_EG1->Write("crossSectionRatio_EG1");
  crossSectionRatio_EG2->Write("crossSectionRatio_EG2");
  crossSectionRatio_pPb->Write("crossSectionRatio_pPb");
  hEff_pPb->Write("hEff_pPb");
  hEff_pp->Write("hEff_pp");
  hClusterSpectra_EG1->Write("hClusterSpectra_EG1");
  hClusterSpectra_EG2->Write("hClusterSpectra_EG2");
  hClusterSpectra_pp->Write("hClusterSpectra_pp");
  fout->Close();
  cout << "done writing to file" << endl;//*/



}//end Run()
void crossSection(){

  /*Run(TString pPbFile, TString ppFile,
    TString pPbFile_MC, TString ppFile_MC,
    Double_t pPb_RF_EG1, Double_t pPb_RF_statErr_EG1, 
    Double_t pPb_RF_EG2, Double_t pPb_RF_statErr_EG2, 
    Double_t pp_RF_EG2, Double_t pp_RF_statErr_EG2)//*/ 

  //pp & p-Pb
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/CorrectPurity/StdPurity/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFit.root",
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/CorrectPurity/StdPurity/fout_4_14bins_firstEvent0_17qAll_StdCuts_EX0PurityFit.root",
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/GenISO/StdCuts/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8.root",
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/GenIso/StdCuts/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8.root",
      6917, 245, 1739, 56, 1240, 28);//StdCuts EX0Purity NOTE RESULTS*/

  /*Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/CorrectPurity/StdPurity/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFit.root",
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/CorrectPurity/StdPurity/fout_4_14bins_firstEvent0_17qAll_StdCuts_EX0PurityFit.root",
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/ARCComments/PerpConeUE/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutrals_woCrossTalkStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheck_ParallelUECone.root",
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/GenIso/StdCuts/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8.root",
      6917, 245, 1739, 56, 1240, 28);//StdCuts EX0Purity NoCrossTalk*/

  /*Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/ISO133/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFit_ISO1Point33.root",
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/CorrectPurity/StdPurity/fout_4_14bins_firstEvent0_17qAll_StdCuts_EX0PurityFit.root",
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/GenISO/StdCuts/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsISO1Point33_GenIsoFixed_ITSAcceptance8.root",
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/FullStats/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsFullStats.root",
      6917, 245, 1739, 56, 1240, 28);//EX0Purity ISO < 1.33*/
  
  /*Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/CorrectPurity/PlusPurity/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PlusPurityFit_NoSigSys.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/CorrectPurity/PlusPurity/fout_4_14bins_firstEvent0_17qAll_StdCuts_EX0PlusPurityFit_NoSigSys.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutrals.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/FullStats/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsFullStats.root", 6917, 245, 1739, 56, 1240, 28);//PLUS/Minus NOTE RESULTS*/

  /*Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/EfficiencySystematics/35/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFitSSC35.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/EfficiencySystematics/35/fout_4_14bins_firstEvent0_17q_ITSonly_StdCuts_EX0PurityFitSSC35.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/EfficiencySystematics/35/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsSSC35.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/EfficiencySystematics/35/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsSSC35.root", 6917, 245, 1739, 56, 1240, 28);//ANALYSIS NOTE RESULTS
  
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/CorrectPurity/PlusPurity/fout_6_14bins_firstEvent0_13def_StdCuts_PlusPurityFit.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/CorrectPurity/PlusPurity/fout_4_14bins_firstEvent0_17qAll_StdCuts_PlusPurityFit.root", 6917, 245, 1739, 56, 1240, 28);//Plus purity

  //ITS-only pp
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/StdEventsAndClusterCuts/fout_6_14bins_firstEvent0_13def_noSkim.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/StdEventsAndClusterCuts/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel.root", 6724, 330, 1675, 110, 1240, 28);//CURRENTLY USE FOR ALL TOF20 testing*/

   //13d
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/StdEventsAndClusterCuts/fout_6_14bins_firstEvent0_13d_all10runs_noSkim.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/StdEventsAndClusterCuts/fout_4_14bins_firstEvent0_17q_all_phySel.root", 5948.27, 0.002, 1434.22, 0.01, 1240, 28);//CURRENTLY USE FOR ALL TOF20 testing*/
 
  //13e
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/StdEventsAndClusterCuts/fout_6_14bins_firstEvent0_13e_noSkim.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/StdEventsAndClusterCuts/fout_4_14bins_firstEvent0_17q_all_phySel.root", 6761, 314, 1787, 58, 1240, 28);//CURRENTLY USE FOR ALL TOF20 testing*/
  
  //13f
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/StdEventsAndClusterCuts/fout_6_14bins_firstEvent0_13f_noSkim.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/StdEventsAndClusterCuts/fout_4_14bins_firstEvent0_17q_all_phySel.root", 5741.599, 0.001, 1402.57, 0.01, 1240, 28);//CURRENTLY USE FOR ALL TOF20 testing*/

  //other
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/13def/IsoStd/fout_6_14bins_firstEvent0_13def_allruns_noSkim_CALOonly_tof20_newPurity_eCross5_newExoticity_iso.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/ISOStd/fout_4_14bins_firstEvent0_17q_ITSonly_noThresh_muonCalo_phySel_CALOonly_tof20_newPurity_eCross5_newExoticity_UEstudyIsoGeV2.root", 6728, 320, 1677, 105, 1240, 28);//CURRENTLY USE FOR ALL TOF20 testing*/
  
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_6_14bins_firstEvent0_pPb_all10runs_noSkimEG1EG2only_tof20.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_14bins_firstEvent0_17q_allpp_CALOonly_tof20_newPurity_eCross5_newExoticity.root", 5826, 395, 1777, 67, 1240, 28);//CURRENTLY USE FOR ALL TOF20 testing*/
  












}//end crossSection
