#include <fstream>
#include <vector>
void Run(TString pPbFile, TString ppFile){
  
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(10);
  
  



  //Obtain and plotting histograms from data
  TFile* dataFile_pPb = new TFile(Form("%s", pPbFile.Data()),"READ");
  TFile* dataFile_pp = new TFile(Form("%s", ppFile.Data()),"READ");

  TH1F* hClusterSpectra_EG1 = (TH1F*)dataFile_pPb->Get("hEG1_E");
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

  TLegend* legYield = new TLegend(0.6,0.7,0.85,0.85);
  legYield->SetHeader("Photon Yield");
  legYield->AddEntry(hClusterSpectra_EG1,"pPb EG1");
  legYield->AddEntry(hClusterSpectra_pp,"pp EG2");


  //Obtain and plotting histograms from MC
  TFile* mcFile_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutrals.root", "READ");

  TH1D* hEff_pPb = (TH1D*)mcFile_pPb->Get("hTotalEfficiency");
  hEff_pPb->SetName("hEff_pPb");
  hEff_pPb->SetTitle("; E_{T} (GeV); #epsilon");
  hEff_pPb->GetYaxis()->SetRangeUser(0,1);
  hEff_pPb->SetLineColor(kRed+1);
  hEff_pPb->SetMarkerColor(kRed+1);
  hEff_pPb->SetMarkerStyle(24);
  hEff_pPb->SetMarkerSize(2);
  hEff_pPb->SetLineWidth(2);

  TFile* mcFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutrals.root","READ");
  
  TH1D* hEff_pp = (TH1D*)mcFile_pp->Get("hTotalEfficiency");
  hEff_pp->SetName("hEff_pp");
  hEff_pp->SetTitle("; E_{T} (GeV); #epsilon");
  hEff_pp->GetYaxis()->SetRangeUser(0,1);
  hEff_pp->SetLineColor(kRed-1);
  hEff_pp->SetMarkerColor(kRed-1);
  hEff_pp->SetMarkerStyle(21);
  hEff_pp->SetMarkerSize(1);
  hEff_pp->SetLineWidth(2);

  
  TLegend* legEff = new TLegend(0.25,0.7,0.85,0.85);
  legEff->AddEntry(hEff_pPb,"5 TeV p-Pb GJ MC 17g6a1: Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso} / bin migration");
  legEff->AddEntry(hEff_pp,"5 TeV pp GJ MC 18b10a: Efficiency = #epsilon_{reco} x #epsilon_{ssc} x #epsilon_{iso} / bin migration");

  TCanvas* cEff = new TCanvas();
  hEff_pPb->GetXaxis()->SetRangeUser(12,60);
  hEff_pPb->Draw("e1");
  hEff_pp->Draw("samee1");
  legEff->Draw("same");//*/

  //Cross Section Calculation  
  /*////////////////////////////////////////////////////////////
    pPb cross section using EG1 trigger
  ///////////////////////////////////////////////////////////*/
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n p-Pb EG1 trigger cross section \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  
  TH1F* crossSection_pPb = (TH1F*)hClusterSpectra_EG1->Clone();
  crossSection_pPb->SetName("crossSection_pPb");
  crossSection_pPb->SetTitle(";E_{T} (GeV); #frac{d^{2}#sigma}{dE_{T}d#eta} [nb/GeV]");

  for(int i = 1; i < crossSection_pPb->GetNbinsX()+1;i++){
    
    double content = crossSection_pPb->GetBinContent(i);
    double error = crossSection_pPb->GetBinError(i);
    double relError = error/content;

    double eff = hEff_pPb->GetBinContent(i);
    double eff_error = hEff_pPb->GetBinError(i);
    double relEffError = eff_error/eff;
    
    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2));
    double xsection = (content)/(eff);
    double xsection_error = relXSectionError*xsection;

    //cout statement
    cout << crossSection_pPb->GetBinLowEdge(i) << "\t" << crossSection_pPb->GetBinLowEdge(i+1) << "\t" << content << "\t" << eff << "\t" << xsection << endl;

    //filling the cross section hist
    crossSection_pPb->SetBinContent(i, xsection);
    crossSection_pPb->SetBinError(i, xsection_error);
    
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
  const double A = 137.5;//208;
  double numEvents_pp = 9.1974e+06;
  double lumi_pp = 224;
  double lumiErr_pp = 5;
  double relLumiErr_pp = lumiErr_pp/lumi_pp;
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

    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2)) + TMath::Power(relLumiErr_pp, 2);
    double xsection = (content*numEvents_pp)/(lumi_pp*eff);
    double xsection_error = relXSectionError*xsection;
    
    //cout statement
    cout << crossSection_pp->GetBinLowEdge(i) << "\t" << crossSection_pp->GetBinLowEdge(i+1) << "\t" << content << "\t" << "\t" << eff << "\t" << xsection << endl;

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
  h_RpA->SetTitle(";E_{T} (GeV); RpA (#sigma_{pPb}/A_{Pb}#sigma_{pp})");
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
      rpa = content_pPb/((double)Ncoll*content_pp);
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
  
  //unity --> line at 1
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);

  
  TLegend* leg = new TLegend(0.12,0.12,0.47,0.4);
  leg->AddEntry((TObject*)0, "ALICE Isolated Photon Cross Section", "");
  leg->AddEntry((TObject*)0, "pp and p-Pb #sqrt{s_{NN}} = 5.02 TeV", "");
  leg->AddEntry(crossSection_pp,"pp");
  leg->AddEntry(crossSection_ppScaled,"pp*A");
  leg->AddEntry(crossSection_pPb,"p-Pb_{EG1}");


  TCanvas* cYield = new TCanvas();
  cYield->SetLogy();
  hClusterSpectra_EG1->GetXaxis()->SetRangeUser(12,60);
  hClusterSpectra_EG1->GetYaxis()->SetRangeUser(1e-8,1e-2);
  hClusterSpectra_EG1->Draw("e1");
  hClusterSpectra_pp->Draw("samee1");
  legYield->Draw("same");//*/

  TCanvas* cXSection = new TCanvas();
  cXSection->SetLogy();
  crossSection_pPb->GetXaxis()->SetRangeUser(12,60);
  crossSection_pPb->GetYaxis()->SetRangeUser(1e-8,1e-2);
  crossSection_pPb->Draw("e1");
  crossSection_pp->Draw("samee1");
  crossSection_ppScaled->Draw("samee1");
  leg->Draw("same");

  TCanvas* cRpa = new TCanvas();
  h_RpA->GetXaxis()->SetRangeUser(12,60);
  //h_RpA->GetYaxis()->SetRangeUser(0,2);
  h_RpA->SetMarkerSize(2);
  h_RpA->Draw("e1");
  line->Draw("same");

  h_RpA->Fit("pol0", "", "", 12, 60);
  TF1* f_RpA = (TF1*)h_RpA->GetFunction("pol0");
  TLegend* legRpA = new TLegend(0.5,0.8,0.85,0.87);
  legRpA->AddEntry(f_RpA, "Constant fit: 1.05 #pm 0.03");
  legRpA->Draw("same");
    
  //Writing to file
  int startingPoint = pPbFile.Index("bins_")+5;
  int endingPoint = pPbFile.Index("cluster")-1;
  TString outputName = pPbFile(startingPoint, endingPoint-startingPoint);
  cout << "writing to file" << endl;
  /*TFile* fout = new TFile(Form("xSectionHists/%sAllppAnd13e_wProductRF.root",outputName.Data()), "RECREATE");
  crossSection_pPb->Write("crossSection_pPb");
  crossSection_pp->Write("crossSection_pp");
  h_RpA->Write("h_RpA");
  hEff_pPb->Write("hEff_pPb");
  hEff_pp->Write("hEff_pPb");
  hClusterSpectra_EG1->Write("hClusterSpectra_EG1");
  hClusterSpectra_pp->Write("hClusterSpectra_pp");
  fout->Close();
  cout << "done writing to file" << endl;//*/



}//end Run()
void photonSpectra(){

  /*Run(TString pPbFile, 
    TString ppFile)//*/ 

  //pp & p-Pb
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/StdEventsAndClusterCuts/fout_6_14bins_firstEvent0_13def_noSkim.root", "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/ppOutput/StdEventsAndClusterCuts/fout_4_14bins_firstEvent0_17q_all_phySel.root");//CURRENTLY USE FOR ALL TOF20 testing*/

  








}//end crossSection
