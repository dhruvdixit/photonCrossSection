#include <fstream>
#include <vector>
void Run(TString filename){
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  

  /*///////////////////////////////////////////////////////
    index         dataset
    0             13c
    1             13d

//////////////////////////////////////////////////////////*/
  
  const int numDataSets = 2;

  TFile* inputFile[numDataSets];

  /*inputFile[0]= new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13c_2runs_al_cluster_emcalMBTrig_Allevent_wEventSelect_noIsoShowShap_noDownScale_noNorm.root","READ");
    inputFile[1]= new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_7runs_noThresh_cluster_emcalMBTrig_Allevent_wEventSelect_noIsoShowShap_noDownScale_noNorm.root","READ");//*/

  /*inputFile[0]= new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13c_2runs_al_cluster_emcalMBTrig_1Mevent_wEventSelect_noClusCuts_noDownScale_noNorm.root","READ");
  inputFile[1]= new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_7runs_noThresh_cluster_emcalMBTrig_1Mevent_wEventSelect_noClusCuts_noDownScale_noNorm.root","READ");//*/

  TFile* file13c = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13c_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig.root","READ");
  //TFile* file13def = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__allpPb_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig.root","READ");//
  //TFile* file13def = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_all10runs_noSkim_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root","READ");//13d only
  //TFile* file13def = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13eonly_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root","READ");//13e only
  //TFile* file13def = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root","READ");//old 13f only
  //TFile* file13def = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13fonly_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root","READ");//new 13f only

  //TString filepath = "/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/";

  cout << "///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n" << filename.Data() << endl;
  TFile* file13def = new TFile(Form("%s", filename.Data()),"READ");//quick testing
  
  //input histograms
  TH1F* hMB_13c;                 //minbias trigger photon spectra
  TH1F* hEG1_13c;                //emcal high trigger photon spectra
  TH1F* hEG2_13c;                //emcal low trigger photon spectra
  TH1F* hNormalizer_13c;         //stores number of events
  TH1F* hMB_13def;                 //minbias trigger photon spectra
  TH1F* hEG1_13def;                //emcal high trigger photon spectra
  TH1F* hEG2_13def;                //emcal low trigger photon spectra
  TH1F* hNormalizer_13def;         //stores number of events

  //output histograms
  TH1F* hMB;                                 //combined MB photon spectra
  TH1F* hEG1;                                //combined EG1 photon spectra
  TH1F* hEG2;                                //combined EG2 photon spectra
  TH1F* hTurnOn1;                            //EG1/MB turn-on curve
  TH1F* hTurnOn2;                            //EG2/MB turn-on curve
  TH1F* hNormalizer;                         //total event from all datasets

  //Event counts
  double numEveMB_13c = 0; 
  double numEveEG1_13c = 0; 
  double numEveEG2_13c = 0; 
  double numEveMB_13def = 0; 
  double numEveEG1_13def = 0; 
  double numEveEG2_13def = 0; 
  double totEveMB = 0;
  double totEveEG1 = 0;
  double totEveEG2 = 0;


  hMB_13c = (TH1F*)file13c->Get("hMB_E");
  hEG1_13c = (TH1F*)file13c->Get("hEG1_E");
  hEG2_13c = (TH1F*)file13c->Get("hEG2_E");
  hNormalizer_13c = (TH1F*)file13c->Get("hNormalizer");
  
  hMB_13def = (TH1F*)file13def->Get("hMB_E");
  hEG1_13def = (TH1F*)file13def->Get("hEG1_E");
  hEG2_13def = (TH1F*)file13def->Get("hEG2_E");
  hNormalizer_13def = (TH1F*)file13def->Get("hNormalizer");

  numEveMB_13c = hNormalizer_13c->GetBinContent(11);
  numEveEG1_13c = hNormalizer_13c->GetBinContent(12);
  numEveEG2_13c = hNormalizer_13c->GetBinContent(13);
  numEveMB_13def = hNormalizer_13def->GetBinContent(11);
  numEveEG1_13def = hNormalizer_13def->GetBinContent(12);
  numEveEG2_13def = hNormalizer_13def->GetBinContent(13);

  totEveMB = numEveMB_13c;
  totEveEG1 = numEveEG1_13def;
  totEveEG2 = numEveEG2_13def;


  cout << totEveMB << "\t" << totEveEG1 << "\t" << totEveEG2 << endl;
  
  hMB = (TH1F*)hMB_13c->Clone();//to get the axis
  hEG1 = (TH1F*)hEG1_13c->Clone();//to get the axis
  hEG2 = (TH1F*)hEG2_13c->Clone();//to get the axis
  hMB->SetName("hMB");
  hEG1->SetName("hEG1");
  hEG2->SetName("hEG2");
  hMB->SetTitle(";E_{T} (GeV);1/N_{ev}^{EG2}dN/dE_{T}");
  hEG1->SetTitle(";E_{T} (GeV);1/N_{ev}^{EG2}dN/dE_{T}");
  hEG2->SetTitle(";E_{T} (GeV);1/N_{ev}^{EG2}dN/dE_{T}");

  
  for(int i = 1; i < hMB->GetNbinsX()+1; i++){
    double dEt = hMB->GetBinWidth(i);
    //cout << dEt << "\t";
    double contentMB = 0;
    double contentEG1 = 0;
    double contentEG2 = 0;

    contentMB = (hMB_13c->GetBinContent(i))*numEveMB_13c;
    contentEG1 = (hEG1_13def->GetBinContent(i))*numEveEG1_13def;
    contentEG2 = (hEG2_13def->GetBinContent(i))*numEveEG2_13def;
    
    hMB->SetBinContent(i, contentMB/(totEveMB*dEt));
    hEG1->SetBinContent(i, contentEG1/(totEveEG1*dEt));
    hEG2->SetBinContent(i, contentEG2/(totEveEG2*dEt)); 
    hMB->SetBinError(i, pow(contentMB,0.5)/(totEveMB*dEt));
    hEG1->SetBinError(i, pow(contentEG1,0.5)/(totEveEG1*dEt));
    hEG2->SetBinError(i, pow(contentEG2,0.5)/(totEveEG2*dEt));
  }
  
  hEG1->SetLineColor(kCyan);
  hEG1->SetMarkerColor(kCyan);
  hEG1->SetMarkerStyle(20);
  hEG2->SetLineColor(kRed);
  hEG2->SetMarkerColor(kRed);
  hEG2->SetMarkerStyle(21);
  hMB->SetLineColor(kGray);
  hMB->SetMarkerColor(kGray);
  hMB->SetMarkerStyle(22);
  
  hEG1_13c->SetLineColor(kCyan+2);
  hEG1_13c->SetMarkerColor(kCyan+2);
  hEG1_13c->SetMarkerStyle(20);
  hEG2_13c->SetLineColor(kRed+1);
  hEG2_13c->SetMarkerColor(kRed+1);
  hEG2_13c->SetMarkerStyle(21);
  hMB_13c->SetLineColor(kGray+1);
  hMB_13c->SetMarkerColor(kGray+1);
  hMB_13c->SetMarkerStyle(22);
  
  hEG1_13def->SetLineColor(kCyan+4);
  hEG1_13def->SetMarkerColor(kCyan+4);
  hEG1_13def->SetMarkerStyle(20);
  hEG2_13def->SetLineColor(kRed+2);
  hEG2_13def->SetMarkerColor(kRed+2);
  hEG2_13def->SetMarkerStyle(21);
  hMB_13def->SetLineColor(kGray+2);
  hMB_13def->SetMarkerColor(kGray+2);
  hMB_13def->SetMarkerStyle(22);
  
  TLegend* leg_pPbSpectra = new TLegend(0.6,0.7,0.9,0.9);
  leg_pPbSpectra->SetHeader("EG1, EG2, MB triggered photon spectra");
  leg_pPbSpectra->AddEntry(hEG1,"EG1 events from 13cd");
  leg_pPbSpectra->AddEntry(hEG1_13c,"EG1 events from 13c");
  leg_pPbSpectra->AddEntry(hEG1_13def,"EG1 events from 13d");
  
  leg_pPbSpectra->AddEntry(hEG2,"EG2 events from 13cd");
  leg_pPbSpectra->AddEntry(hEG2_13c,"EG2 events from 13c");
  leg_pPbSpectra->AddEntry(hEG2_13def,"EG2 events from 13d");
  
  leg_pPbSpectra->AddEntry(hMB,"MB events from 13cd");
  leg_pPbSpectra->AddEntry(hMB_13c,"MB events from 13c");
  leg_pPbSpectra->AddEntry(hMB_13def,"MB events from 13d");
  

  TCanvas* triggerSpectra_pPb = new TCanvas();
  triggerSpectra_pPb->SetLogy();
  hEG1->GetYaxis()->SetRangeUser(1e-7, 10);
  hEG1->Draw("");
  hEG1_13c->Draw("samee");
  hEG1_13def->Draw("samee");
  
  hEG2->Draw("samee");
  hEG2_13c->Draw("samee");
  hEG2_13def->Draw("samee");
  
  hMB->Draw("samee");
  hMB_13c->Draw("samee");
  hMB_13def->Draw("samee");

  leg_pPbSpectra->Draw("same");//*/

  TH1F* rejF1 = (TH1F*)hEG1->Clone();
  rejF1->SetName("rejF1");
  rejF1->Divide(hMB);
  rejF1->SetLineColor(kCyan);
  rejF1->SetMarkerColor(kCyan);
  rejF1->SetMarkerStyle(20);  


  TH1F* rejF2 = (TH1F*)hEG2->Clone();
  rejF2->SetName("rejF2");
  rejF2->Divide(hMB);
  rejF2->SetLineColor(kRed);
  rejF2->SetMarkerColor(kRed);
  rejF2->SetMarkerStyle(21);

  TH1F* rejF3 = (TH1F*)hEG1->Clone();
  rejF3->SetName("rejF3");
  rejF3->Divide(hEG2);
  rejF3->SetLineColor(kBlack);
  rejF3->SetMarkerColor(kBlack);
  rejF3->SetMarkerStyle(22);


  TLegend* leg_pPbRFcurves = new TLegend(0.6,0.4,0.9,0.6);
  leg_pPbRFcurves->SetHeader("Trigger Rejection Factors");
  leg_pPbRFcurves->AddEntry(rejF1,"EG1/MB");
  leg_pPbRFcurves->AddEntry(rejF2,"EG2/MB");
  leg_pPbRFcurves->AddEntry(rejF3,"EG1/EG2");

  TCanvas* turnOnCurves_pPb = new TCanvas();
  turnOnCurves_pPb->SetLogy();
  rejF1->GetYaxis()->SetRangeUser(5*1e-2, 5*1e4);
  rejF1->SetTitle(";E_{T} [GeV];R_{trig}");
  rejF1->Draw();
  rejF2->Draw("same");
  rejF3->Draw("same");
  leg_pPbRFcurves->Draw("same");
  
  rejF1->Fit("pol0", "", "", 14, 40);
  rejF2->Fit("pol0", "", "", 10, 40);
  rejF3->Fit("pol0", "", "", 16, 40);//*/





  /*////////////////////////////////////////////////////////////////////////////
Trigger rejection factors in pp for both EMCAL and DCAL
///////////////////////////////////////////////////////////////////////////////*/
  /*TFile* inputFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_24bins_17q_CENT_wSDD_noThresh_RtrigAnalysis_MBEGDGcalo_Normalized.root","READ");//

  TH1F* pp_MBcalo = (TH1F*)inputFile_pp->Get("hMB_caloE");
  pp_MBcalo->SetName("pp_MBcalo");
  TH1F* pp_EG2calo = (TH1F*)inputFile_pp->Get("hEG2_caloE");
  pp_EG2calo->SetName("pp_EG2calo");
  TH1F* pp_DG2calo = (TH1F*)inputFile_pp->Get("hDG2_caloE");
  pp_DG2calo->SetName("pp_DG2calo");

  pp_EG2calo->SetLineColor(kBlue);
  pp_EG2calo->SetMarkerColor(kBlue);
  pp_EG2calo->SetMarkerStyle(20);
  pp_DG2calo->SetLineColor(kCyan);
  pp_DG2calo->SetMarkerColor(kCyan);
  pp_DG2calo->SetMarkerStyle(21);
  pp_MBcalo->SetLineColor(kBlack);
  pp_MBcalo->SetMarkerColor(kBlack);
  pp_MBcalo->SetMarkerStyle(22);

  TLegend* leg_ppSpectra = new TLegend(0.6,0.7,0.9,0.9);
  leg_ppSpectra->SetHeader("17q: EG2calo, DG2calo, MBcalo triggered photon spectra");
  leg_ppSpectra->AddEntry(pp_EG2calo,"EG2calo_events");
  leg_ppSpectra->AddEntry(pp_DG2calo,"DG2calo_events");
  leg_ppSpectra->AddEntry(pp_MBcalo,"MBcalo events");

  TCanvas* triggerSpectra_pp = new TCanvas();
  triggerSpectra_pp->SetLogy();
  pp_EG2calo->GetYaxis()->SetRangeUser(1e-7, 1e-2);
  pp_EG2calo->Draw();
  pp_DG2calo->Draw("same");
  pp_MBcalo->Draw("same");
  leg_ppSpectra->Draw("same");
  
  
  TH1F* rf_EG2calo = (TH1F*)pp_EG2calo->Clone();
  rf_EG2calo->SetName("rf_EG2calo");
  rf_EG2calo->SetTitle(";E_{T} [GeV]; R_{trig}");
  rf_EG2calo->Divide(pp_MBcalo);

  TH1F* rf_DG2calo = (TH1F*)pp_DG2calo->Clone();
  rf_DG2calo->SetName("rf_DG2calo");
  rf_DG2calo->SetTitle(";E_{T} [GeV]; R_{trig}");
  rf_DG2calo->Divide(pp_MBcalo);

  TLegend* leg_ppRFcurves = new TLegend(0.6,0.4,0.9,0.6);
  leg_ppRFcurves->SetHeader("Trigger Rejection Factors");
  leg_ppRFcurves->AddEntry(rf_EG2calo,"EG2/MB");
  leg_ppRFcurves->AddEntry(rf_DG2calo,"DG2/MB");

  TCanvas* turnOnCurves_pp = new TCanvas();
  turnOnCurves_pp->SetLogy();
  rf_EG2calo->GetYaxis()->SetRangeUser(1, 1e3);
  rf_EG2calo->Draw();
  rf_DG2calo->Draw("same");
  leg_ppRFcurves->Draw("same");//*/
}

void rejectionFactor(){

  //13d
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_all10runs_noSkim_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root");

  //13e
  Run("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13eonly_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/");
  //Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/");

  //13f
  Run("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/Data/fout_16_14bins__13fonly_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root");
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root");
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part1_new_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root");
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part2_new_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root");
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part3_newer_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root");
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_10runs_noSkim_part4_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root");
  Run("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13f_3runs_noSkim_part5_new_MBEG1EG2_noPurityWeights_noClusCuts_allEventCuts_forRTrig_new.root");
}
