
#include <fstream>
#include <vector>
void Run(TString pPbFile_mEta,
	 TString ppFile_mEta,
	 TString pPbFile_mEta_MC,
	 TString ppFile_mEta_MC,
	 TString pPbFile_lEta,
	 TString ppFile_lEta,
	 TString pPbFile_lEta_MC,
	 TString ppFile_lEta_MC,){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(10);
  
  
  //Obtain and plotting histograms from data
  TFile* dataFile_pPb_mEta = new TFile(Form("%s", pPbFile_mEta.Data()),"READ");
  TFile* dataFile_pp_mEta = new TFile(Form("%s", ppFile_mEta.Data()),"READ");

  TH1F* hClusterSpectra_EG1 = (TH1F*)dataFile_pPb_mEta->Get("hEG1_E");
  TH1F* hClusterSpectra_EG2 = (TH1F*)dataFile_pPb_mEta->Get("hEG2_E");
  TH1F* hClusterSpectra_pp = (TH1F*)dataFile_pp_mEta->Get("hEG2_caloE");

  TFile* mcFile_pPb = new TFile(Form("%s", pPbFile_mEta_MC.Data()),"READ");

  TH1D* hEff_pPb = (TH1D*)mcFile_pPb->Get("hTotalEfficiency");
  
  TFile* mcFile_pp = new TFile(Form("%s", ppFile_mEta_MC.Data()),"READ");
  
  TH1D* hEff_pp = (TH1D*)mcFile_pp->Get("hTotalEfficiency");

  
  //Cross Section Calculation
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

    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2));
    double xsection = content/eff;
    double xsection_error = relXSectionError*xsection;

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

    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2));
    double xsection = (content)/(eff);
    double xsection_error = relXSectionError*xsection;

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

  const double Ncoll = 7.0;
  const double A = 208;
  for(int i = 1; i < crossSection_pp->GetNbinsX()+1;i++){
    
    double content = crossSection_pp->GetBinContent(i);
    double error = crossSection_pp->GetBinError(i);
    double relError = error/content;

    double eff = hEff_pp->GetBinContent(i);
    double eff_error = hEff_pp->GetBinError(i);
    double relEffError = eff_error/eff;
    
    double relXSectionError = TMath::Sqrt(TMath::Power(relError,2)+TMath::Power(relEffError,2));
    double xsection = (content)/(eff);
    double xsection_error = relXSectionError*xsection;
    
    
    //filling the cross section hist
    crossSection_pp->SetBinContent(i, xsection);
    crossSection_pp->SetBinError(i, xsection_error);
        
  }//*/

  crossSection_pp->SetLineColor(kBlue);
  crossSection_pp->SetMarkerStyle(20);
  crossSection_pp->SetMarkerColor(kBlue);
  crossSection_pp->SetMarkerSize(2);
  
  crossSection_EG1->SetLineColor(kRed);
  crossSection_EG1->SetMarkerStyle(21);
  crossSection_EG1->SetMarkerColor(kRed);
  crossSection_EG1->SetMarkerSize(2);
  
  crossSection_EG2->SetLineColor(kGreen);
  crossSection_EG2->SetMarkerStyle(21);
  crossSection_EG2->SetMarkerColor(kGreen);
  crossSection_EG2->SetMarkerSize(2);
  
  //unity --> line at 1
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);

  
  TLegend* leg = new TLegend(0.12,0.12,0.47,0.4);
  leg->AddEntry((TObject*)0, "ALICE Isolated Photon Spectra Corrected by Efficiency", "");
  leg->AddEntry((TObject*)0, "pp and p-Pb #sqrt{s_{NN}} = 5.02 TeV", "");
  leg->AddEntry(crossSection_pp,"pp");
  leg->AddEntry(crossSection_EG1,"p-Pb_{EG1}");
  leg->AddEntry(crossSection_EG2,"p-Pb_{EG2}");
  

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
  TLegend* legRpA = new TLegend(0.15,0.15,0.7,0.35);
  legRpA->AddEntry(h_RpA->GetFunction("pol0"), Form("Constant Fit: %f #pm %f", h_RpA->GetFunction("pol0")->GetParameter(0), h_RpA->GetFunction("pol0")->GetParError(0)), "l");
  legRpA->AddEntry((TObject*)0, Form("#chi^{2} = %f", h_RpA->GetFunction("pol0")->GetChisquare()), "");
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
  legRatio->AddEntry(crossSectionRatio_pPb,"p-Pb");

  //Ratio with Erwann
  TCanvas* cRatio = new TCanvas();
  crossSectionRatio_EG1->Draw("e1");
  crossSectionRatio_EG2->Draw("samee1");
  crossSectionRatio_pPb->Draw("samee1");
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
  /*int startingPoint = pPbFile_mEta.Index("bins_")+5;
  int endingPoint = pPbFile_mEta.Index("cluster")-1;
  TString outputName = pPbFile_mEta(startingPoint, endingPoint-startingPoint);
  cout << "writing to file" << endl;
  TFile* fout = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/xSectionHists/%sStdCuts_EX0PurityFit_Less4Eta.root",outputName.Data()), "RECREATE");
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
void effCorrection(){

  /*Run(TString pPbFile_mEta, 
    TString pPbFile_lEta, 
    TString ppFile_mEta,
    TString pPbFile_mEta_MC, 
    TString ppFile_mEta_MC)//*/ 

  //pp & p-Pb
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/ARCComments/ConeAcceptanceCheck/fout_6_14bins_firstEvent0_13def_StdCuts_EX0PurityFit_ConeAcceptanceCheckLess4Eta_ClusterCutHistAfterCuts.root",
      "",
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/ARCComments/ConeAcceptanceCheck/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheckLess4Eta_PerpUECone_ClusterCutHistAfterCuts.root"
      "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/ARCComments/ConeAcceptanceCheck/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsStdCuts_GenIsoFixed_ITSAcceptance8_TrackPtMinCut_ConeAcceptanceCheckLess4Eta_PerpUECone_ClusterCutHistAfterCuts.root");//StdCuts EX0Purity Cone Acceptance*/  












}//end effCorrection
