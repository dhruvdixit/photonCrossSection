#include <fstream>
#include <vector>
void Run(TString filename){
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  

  
  /*////////////////////////////////////////////////////////////////////////////
Trigger rejection factors in pp for both EMCAL and DCAL
///////////////////////////////////////////////////////////////////////////////*/

  TFile* inputFile_pp = new TFile(Form("%s",filename.Data()),"READ");//
  //TFile* inputFileMB = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_1_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MB_Normalized_allEMCgoodOnly_bugFixed2_367to365.root", "READ");
  //TFile* inputFileMB = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_1_15bins_17p_CENT_wSDD_10runs_noThresh_part1_RtrigAnalysis_MB_Normalized_bugFixed2_008to123.root", "READ");
  //TFile* inputFileMB = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_1_15bins_17q_CENT_wSDD_noThresh_forRTrig.root", "READ");
  TFile* inputFileMB = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_1_15bins_17p_CENT_wSDD_10runs_noThresh_part1_forRTrig.root", "READ");
  
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
  leg_ppSpectra->SetHeader("17q:runs 282391-282415, 17p:runs 282008-282123");
  leg_ppSpectra->AddEntry(pp_EG2calo,"17q EG2calo triggered clusters");
  //leg_ppSpectra->AddEntry(pp_EG2cent,"EG2cent_events");
  leg_ppSpectra->AddEntry(pp_MBcent,"17p MBcent triggered clusters");

  pp_EG2calo->SetTitle("; E_{T} [GeV] ; 1/N_{ev}dN/dE_{T}");
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


  TCanvas* turnOnCurves_pp = new TCanvas();
  turnOnCurves_pp->SetLogy();
  rf_EG2calo->GetYaxis()->SetRangeUser(1, 5e3);
  rf_EG2calo->Draw();

  cout << "pol0(8,50)" << endl;
  rf_EG2calo->Fit("pol0", "", "", 8, 60);
  //rf_EG2cent->Fit("pol0", "", "", 10, 40);
  cout << "chi^{2}/dof = " << rf_EG2calo->GetFunction("pol0")->GetChisquare() << "/" << rf_EG2calo->GetFunction("pol0")->GetNDF() << " = " << (rf_EG2calo->GetFunction("pol0")->GetChisquare())/((double)rf_EG2calo->GetFunction("pol0")->GetNDF()) << endl;

  cout << "Fitting Error Function\n" << endl;
  auto myErf2Lambda = [](double* x, double* p) {return (TMath::Erf((x[0]-p[0])/p[1]) + 1)/2 * p[2]; };
  TF1* myErf2 = new TF1("myErf2", myErf2Lambda, 0, 60, 3);
  myErf2->SetParameter(0, 5.0);
  myErf2->SetParameter(1, 0.5);
  myErf2->SetParameter(2, 700.0);
  myErf2->SetLineColor(kGreen);
  //TF1 *f1 = new TF1("f1","[0]*TMath::Erf((x-[1])/[2])", 0.0, 60.0);
  //f1->SetParameters(600, 0.5, 1);
  rf_EG2calo->Fit("myErf2", "R+", "", 3, 60);
  cout << "chi^{2}/dof = " << rf_EG2calo->GetFunction("myErf2")->GetChisquare() << "/" << rf_EG2calo->GetFunction("myErf2")->GetNDF() << " = " << (rf_EG2calo->GetFunction("myErf2")->GetChisquare())/((double)rf_EG2calo->GetFunction("myErf2")->GetNDF()) << endl;
  
  TLegend* leg_ppRFcurves = new TLegend(0.6,0.4,0.9,0.6);
  leg_ppRFcurves->SetHeader("17q runs: 282391-282415");
  leg_ppRFcurves->AddEntry(rf_EG2calo,"EG2 calo/MB");
  leg_ppRFcurves->AddEntry(myErf2,"Error Function (3, 60): [0]*TMath::Erf((x-[1])/[2])");
  leg_ppRFcurves->AddEntry(rf_EG2calo->GetFunction("pol0"),"Constant Polynomial Fit (8, 60)");
  leg_ppRFcurves->Draw("same");//*/

}

void rejectionFactor_pp(){

  //17q
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_15bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MB_Normalized_allEMCgoodOnly_bugFixed2_441to437.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_15bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MB_Normalized_allEMCgoodOnly_bugFixed2_415to402.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_15bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MB_Normalized_allEMCgoodOnly_bugFixed2_399to391.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_15bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MB_Normalized_allEMCgoodOnly_bugFixed2_376to365.root");
  
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MBcentEGcaloEGcent_Normalized_allButEMCgoodOnly_bugFixed2_441to237.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MBcentEGcaloEGcent_Normalized_allButEMCgoodOnly_bugFixed2_415to402.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MBcentEGcaloEGcent_Normalized_allButEMCgoodOnly_bugFixed2_399to391.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_26bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MBcentEGcaloEGcent_Normalized_allEMCgoodOnly_bugFixed2_367to365.root");


  //plots remade
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_15bins_17q_CENT_wSDD_noThresh_r282437_forRTrig.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_15bins_17q_CENT_wSDD_noThresh_r282439_forRTrig.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_15bins_17q_CENT_wSDD_noThresh_r282440_forRTrig.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_15bins_17q_CENT_wSDD_noThresh_r282441_forRTrig.root");

  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_26bins_17q_CENT_wSDD_noThresh_forRTrig.root");

}
