#include <fstream>
#include <vector>
void Run(TString ppFile, TString ppFileMC,
	 Double_t ppRf_EG2, Double_t ppRfStatErr_EG2){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(10);
  
  



  //Obtain and plotting histograms from data
  TFile* dataFile_pp = new TFile(Form("%s", ppFile.Data()),"READ");

  TH1F* hClusterSpectra_pp = (TH1F*)dataFile_pp->Get("hEG2_caloE");
  hClusterSpectra_pp->Sumw2();
  hClusterSpectra_pp->SetName("hClusterSpectra_pp");
  hClusterSpectra_pp->SetTitle(";E_{T} (GeV); #frac{1}{N_{ev}}#frac{d^{2}N}{dE_{T}d#eta}");
  hClusterSpectra_pp->SetLineColor(kBlue);
  hClusterSpectra_pp->SetMarkerColor(kBlue);
  hClusterSpectra_pp->SetMarkerStyle(20);
  hClusterSpectra_pp->SetMarkerSize(2);

  TLegend* legYield = new TLegend(0.6,0.7,0.85,0.85);
  legYield->SetHeader("Photon Yield");
  legYield->AddEntry(hClusterSpectra_pp,"pp EG2");

  TFile* mcFile_pp= new TFile(Form("%s", ppFileMC.Data()),"READ");
  
  TH1D* hEff_pp = (TH1D*)mcFile_pp->Get("hEfficiency");
  //hEff_pp->Divide((TH1D*)mcFile_pp->Get("hTruth"));
  hEff_pp->SetName("hEff_pp");
  hEff_pp->SetTitle("; E_{T} (GeV); #epsilon");
  hEff_pp->GetYaxis()->SetRangeUser(0,1);
  hEff_pp->SetLineColor(kRed-1);
  hEff_pp->SetMarkerColor(kRed-1);
  hEff_pp->SetMarkerStyle(21);
  hEff_pp->SetMarkerSize(1);
  hEff_pp->SetLineWidth(2);
  
  TLegend* legEff = new TLegend(0.6,0.7,0.85,0.85);
  legEff->AddEntry(hEff_pp,"pp: Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso}");
 

  TCanvas* cEff = new TCanvas();
  hEff_pp->GetXaxis()->SetRangeUser(12,60);
  hEff_pp->Draw("samee1");
  legEff->Draw("same");//*/

  //Luminosity Calulation
  TH1D* hNumEvents_pp = (TH1D*)dataFile_pp->Get("hNormalizer");

  double Nevtot_pp = hNumEvents_pp->GetBinContent(11);
  cout << "Numbers of events" << endl;
  cout << "pp EG2: " << Nevtot_pp << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  const double pp_xs = 5.09E-02;
  const double pp_xsErr = 4.00E-05;
    
  double lumi_pp = ((ppRf_EG2*Nevtot_pp)/pp_xs)*1.00E-09;
  double relLumiError_pp = TMath::Sqrt(TMath::Power((ppRfStatErr_EG2/ppRf_EG2), 2)+TMath::Power((pp_xsErr/pp_xs),2));
  double lumi_error_pp = lumi_pp*relLumiError_pp;

  cout << "Luminosity" << endl;
  cout << "pp EG2:" << lumi_pp << " +/- " << lumi_error_pp << endl;
  
  //Cross Section Calculation  
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
    Erwann's p-Pb
  ////////////////////////////////////////////////////////////////////*/
  TH1F* crossSection_erwann = (TH1F*)hClusterSpectra_pp->Clone();
  crossSection_erwann->SetName("crossSection_erwann");
  crossSection_erwann->SetTitle(";E_{T} (GeV); #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");
  
  double erwannMean[9] = {4727.74, 2015.57, 1151.86, 696.985, 444.604, 233.026, 104.87, 38.5216, 7.4227};
  double erwannStat[9] = {604.369, 337.901, 71.0714, 51.475, 35.3468, 15.5412, 10.4705, 4.64552, 1.38719};
  double erwannSys[9] = {766.058, 308.501, 167.064, 96.1471, 58.8658, 29.4243, 12.7484, 4.7213, 1.11858};

  for(int i = 6; i < crossSection_erwann->GetNbinsX()+1;i++){
    

    crossSection_erwann->SetBinContent(i, erwannMean[i-6]);
    crossSection_erwann->SetBinError(i, erwannStat[i-6]);
    
  }
  /*////////////////////////////////////////////////////////////////////
    RpA
  ////////////////////////////////////////////////////////////////////*/
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n RpA \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
 
  TH1F* h_RpA = (TH1F*)hClusterSpectra_pp->Clone();
  h_RpA->SetName("h_RpA");
  h_RpA->SetTitle(";E_{T} (GeV); RpA (#sigma_{pPb}/A_{Pb}#sigma_{pp})");
  for(int i = 1; i < h_RpA->GetNbinsX()+1;i++){
    
    double content_pPb = crossSection_erwann->GetBinContent(i);
    double error_pPb = crossSection_erwann->GetBinError(i);
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
  
  //unity --> line at 1
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);

  
  TLegend* leg = new TLegend(0.12,0.12,0.47,0.4);
  leg->AddEntry((TObject*)0, "ALICE Isolated Photon Cross Section", "");
  leg->AddEntry((TObject*)0, "pp and p-Pb #sqrt{s_{NN}} = 5.02 TeV", "");
  leg->AddEntry(crossSection_pp,"pp");
  leg->AddEntry(crossSection_ppScaled,"pp*A(208)");
  leg->AddEntry(crossSection_erwann,"Erwann's p-Pb");


  TCanvas* cYield = new TCanvas();
  cYield->SetLogy();
  hClusterSpectra_pp->GetXaxis()->SetRangeUser(12,60);
  hClusterSpectra_pp->GetYaxis()->SetRangeUser(1e-8,1e-2);
  hClusterSpectra_pp->Draw("e1");
  legYield->Draw("same");//*/

  TCanvas* cXSection = new TCanvas();
  cXSection->SetLogy();
  crossSection_pp->GetXaxis()->SetRangeUser(12,60);
  crossSection_pp->GetYaxis()->SetRangeUser(1e-4,1e4);
  crossSection_pp->Draw("e1");
  crossSection_ppScaled->Draw("samee1");
  crossSection_erwann->Draw("samee1");
  leg->Draw("same");

  TCanvas* cRpa = new TCanvas();
  h_RpA->GetXaxis()->SetRangeUser(12,60);
  h_RpA->GetYaxis()->SetRangeUser(0,2);
  h_RpA->SetMarkerSize(2);
  h_RpA->Draw("e1");
  //line->Draw("same");
  h_RpA->Fit("pol0", "0", "", 12, 60);
  
  //Writing to file
  /*int startingPoint = ppFile.Index("bins_")+5;
  int endingPoint = ppFile.Index("cluster")-1;
  TString outputName = ppFile(startingPoint, endingPoint-startingPoint);
  cout << "writing to file" << endl;
  TFile* fout = new TFile(Form("xSectionHists/17p_crossSectionHistos_allpPb_al17qruns_cc_markusRF_erwann.root"), "RECREATE");
  crossSection_pp->Write("crossSection_pp");
  h_RpA->Write("h_RpA");
  fout->Close();
  cout << "done writing to file" << endl;//*/



}//end Run()
void crossSection_pp(){

  /*Run(TString ppFile, TString ppFileMC,
    Double_t pp_RF_EG2, Double_t pp_RF_statErr_EG2)//*/ 

  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_14bins_firstEvent0_17q_allpp_CALOonly_tof20_newPurity_eCross5_newExoticity.root", "/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/18b10a_Allevents_erwanbinning_noNorm_newIsoDef_fullEMCalAcceptance_isoEffsscEffRecoEffSeperate_cutFlow_binMigration_hCorr_corr_stdCuts.root", 1278, 5);//CURRENTLY USE FOR ALL TOF20 testing*/

  



}//end crossSection
