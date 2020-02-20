#include <fstream>
#include <vector>
void Run(TString filename){
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  

  
  /*////////////////////////////////////////////////////////////////////////////
Trigger rejection factors in pp for both EMCAL and DCAL
///////////////////////////////////////////////////////////////////////////////*/

  TFile* inputFile_pp = new TFile(Form("%s",filename.Data()),"READ");//
  TFile* inputFileMB = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_1_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MB_Normalized_allEMCgoodOnly_bugFixed2_367to365.root", "READ");

  TH1F* pp_MBcent = (TH1F*)inputFileMB->Get("hMB_centE");
  pp_MBcent->SetName("pp_MBcent");
  TH1F* pp_EG2calo = (TH1F*)inputFile_pp->Get("hEG2_caloE");
  pp_EG2calo->SetName("pp_EG2calo");
  //TH1F* pp_EG2calo2 = (TH1F*)inputFile_pp2->Get("hEG2_caloE");
  //pp_EG2calo2->SetName("pp_EG2calo2");
  TH1F* pp_EG2cent = (TH1F*)inputFile_pp->Get("hEG2_centE");
  pp_EG2cent->SetName("pp_EG2cent");
  //TH1F* pp_EG2calo = (TH1F*)pp_EG2calo1->Clone();
  //pp_EG2calo->SetName("pp_EG2calo");
  
  TH1F* normalizer = (TH1F*)inputFile_pp->Get("hNormalizer");
  Double_t numCaloEvents = normalizer->GetBinContent(11);
  cout << "Number of Calo Events: " << numCaloEvents << endl;
  /*TH1F* norm1 = (TH1F*)inputFile_pp->Get("hNormalizer");
  TH1F* norm2 = (TH1F*)inputFile_pp2->Get("hNormalizer");
  Double_t numCaloEvents1 = norm1->GetBinContent(11);
  Double_t numCaloEvents2 = norm2->GetBinContent(11);
  Double_t numCaloEvents = numCaloEvents1 + numCaloEvents2;
  cout << numCaloEvents1 << "\t" << numCaloEvents2 << endl;
  for(int i = 0; i < pp_EG2calo->GetNbinsX(); i++){
    
    Double_t content1 = pp_EG2calo1->GetBinContent(i);
    //Double_t content2 = pp_EG2calo2->GetBinContent(i);
    Double_t content = content1*numCaloEvents1 + content2*numCaloEvents2;
    pp_EG2calo->SetBinContent(i, content/numCaloEvents);

    Double_t error1 = pp_EG2calo1->GetBinError(i);
    //Double_t error2 = pp_EG2calo2->GetBinError(i);
    Double_t error = TMath::Sqrt(TMath::Power(error1*numCaloEvents1,2) + TMath::Power(error2*numCaloEvents2,2));
    pp_EG2calo->SetBinError(i, error/numCaloEvents);
    }//*/
  
  pp_EG2calo->SetLineColor(kBlue);
  pp_EG2calo->SetMarkerColor(kBlue);
  pp_EG2calo->SetMarkerStyle(20);
  pp_EG2cent->SetLineColor(kCyan);
  pp_EG2cent->SetMarkerColor(kCyan);
  pp_EG2cent->SetMarkerStyle(21);
  pp_MBcent->SetLineColor(kBlack);
  pp_MBcent->SetMarkerColor(kBlack);
  pp_MBcent->SetMarkerStyle(22);

  TLegend* leg_ppSpectra = new TLegend(0.6,0.7,0.9,0.9);
  leg_ppSpectra->SetHeader("17q: EG2calo, EG2cent, MBcent triggered photon spectra");
  leg_ppSpectra->AddEntry(pp_EG2calo,"EG2calo_events");
  //leg_ppSpectra->AddEntry(pp_EG2cent,"EG2cent_events");
  leg_ppSpectra->AddEntry(pp_MBcent,"MBcent events");

  TCanvas* triggerSpectra_pp = new TCanvas();
  triggerSpectra_pp->SetLogy();
  pp_EG2calo->GetYaxis()->SetRangeUser(1e-8, 1);
  pp_EG2calo->Draw();
  //pp_EG2cent->Draw("same");
  pp_MBcent->Draw("same");
  leg_ppSpectra->Draw("same");
  
  
  TH1F* rf_EG2calo = (TH1F*)pp_EG2calo->Clone();
  rf_EG2calo->SetName("rf_EG2calo");
  rf_EG2calo->SetTitle(";E_{T} [GeV]; R_{trig}");
  rf_EG2calo->Divide(pp_MBcent);

  TH1F* rf_EG2cent = (TH1F*)pp_EG2cent->Clone();
  rf_EG2cent->SetName("rf_EG2cent");
  rf_EG2cent->SetTitle(";E_{T} [GeV]; R_{trig}");
  rf_EG2cent->Divide(pp_MBcent);

  TLegend* leg_ppRFcurves = new TLegend(0.6,0.4,0.9,0.6);
  leg_ppRFcurves->SetHeader("Trigger Rejection Factors");
  leg_ppRFcurves->AddEntry(rf_EG2calo,"EG2 calo/MB");
  leg_ppRFcurves->AddEntry(rf_EG2cent,"EG2 cent/MB");

  TCanvas* turnOnCurves_pp = new TCanvas();
  turnOnCurves_pp->SetLogy();
  rf_EG2calo->GetYaxis()->SetRangeUser(1, 1e3);
  rf_EG2calo->Draw();
  rf_EG2cent->Draw("same");
  leg_ppRFcurves->Draw("same");//*/

  
  //cout << "pol0(5,40)" << endl;
  //rf_EG2calo->Fit("pol0", "", "", 5, 40);
  //rf_EG2cent->Fit("pol0", "", "", 5, 40);

  //cout << "pol0(5,60)" << endl;
  //rf_EG2calo->Fit("pol0", "", "", 5, 60);
  //rf_EG2cent->Fit("pol0", "", "", 5, 60);

  //cout << "pol0(10,40)" << endl;
  //rf_EG2calo->Fit("pol0", "", "", 10, 40);
  //rf_EG2cent->Fit("pol0", "", "", 10, 40);

  //cout << "pol0(10,60)" << endl;
  //rf_EG2calo->Fit("pol0", "", "", 10, 60);
  //rf_EG2cent->Fit("pol0", "", "", 10, 60);

  //cout << "pol1(5,40)" << endl;
  rf_EG2calo->Fit("pol1", "RM", "", 5, 40);
  //rf_EG2cent->Fit("pol1", "", "", 5, 40);
  rf_EG2calo->GetFunction("pol1")->SetLineColor(kBlue);
  
  //cout << "pol1(5,60)" << endl;
  rf_EG2calo->Fit("pol1", "RM+", "", 5, 60);
  //rf_EG2cent->Fit("pol1", "R+", "", 5, 60);
  TF1* fit2 = rf_EG2calo->GetFunction("pol1");
  fit2->SetLineColor(kRed);
  
  //cout << "pol1(10,40)" << endl;
  rf_EG2calo->Fit("pol1", "RM+", "", 10, 40);
  //rf_EG2cent->Fit("pol1", "R+", "", 10, 40);
  rf_EG2calo->GetFunction("pol1")->SetLineColor(kGreen);
  
  //cout << "pol1(10,60)" << endl;
  rf_EG2calo->Fit("pol1", "RM+", "", 10, 60);
  //rf_EG2cent->Fit("pol1", "R+", "", 10, 60);
  rf_EG2calo->GetFunction("pol1")->SetLineColor(kMagenta);
  
}

void rejectionFactor_pp(){

  //17q
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MBcentEGcaloEGcent_Normalized_allEMCgoodOnly_bugFixed2_367to365.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MBcentEGcaloEGcent_Normalized_allButEMCgoodOnly_bugFixed2_415to402.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MBcentEGcaloEGcent_Normalized_allButEMCgoodOnly_bugFixed2_399to391.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MBcentEGcaloEGcent_Normalized_allButEMCgoodOnly_bugFixed2_441to237.root");


}
