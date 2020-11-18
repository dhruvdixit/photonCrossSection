#include <fstream>
#include <vector>
void calcSystematicsEff(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);


  //p-Pb efficiency
  TFile* file_pPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutrals.root","READ");
  TH1F* hEff_pPb = (TH1F*)file_pPb->Get("hTotalEfficiency");hEff_pPb->SetLineColor(kRed);hEff_pPb->SetMarkerColor(kRed); hEff_pPb->SetMarkerStyle(kFullCircle);

  //Shower shape efficiency 
  TFile* fileSSC_PluspPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/SystematicCheck/ShowerShape/fout_14bins_firstEvent0_17g6a1_wNeutralsShowerShapeMaxPoint33.root","READ");
  TH1F* hSSCEff_PluspPb = (TH1F*)fileSSC_PluspPb->Get("hTotalEfficiency");hSSCEff_PluspPb->SetLineColor(kMagenta);hSSCEff_PluspPb->SetMarkerColor(kMagenta);

  TFile* fileSSC_MinuspPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/SystematicCheck/ShowerShape/fout_14bins_firstEvent0_17g6a1_wNeutralsShowerShapeMaxPoint27.root","READ");
  TH1F* hSSCEff_MinuspPb = (TH1F*)fileSSC_MinuspPb->Get("hTotalEfficiency");hSSCEff_MinuspPb->SetLineColor(kBlue);hSSCEff_MinuspPb->SetMarkerColor(kBlue);
    
  
  TLegend* lSSC_pPb = new TLegend(0.6, 0.7, 0.87, 0.87);
  lSSC_pPb->AddEntry(hEff_pPb, "0.1 < #sigma^{2}_{long} < 0.3");
  lSSC_pPb->AddEntry(hSSCEff_PluspPb, "0.1 < #sigma^{2}_{long} < 0.27");
  lSSC_pPb->AddEntry(hSSCEff_MinuspPb, "0.1 < #sigma^{2}_{long} < 0.33");
  
  TCanvas* cSSC_pPb = new TCanvas("cSSC_pPb", "cSSC_pPb");
  hEff_pPb->SetTitle(";E_{T} [GeV]; #epsilon^{iso}_{#gamma}");
  hEff_pPb->GetXaxis()->SetRangeUser(12, 60);
  hEff_pPb->Draw("e1");
  hSSCEff_PluspPb->Draw("samee1");
  hSSCEff_MinuspPb->Draw("samee1");
  lSSC_pPb->Draw("same");

  TH1F* hSSCDiff_pPb = (TH1F*)hSSCEff_PluspPb->Clone("hSSCDiff_pPb");
  hSSCDiff_pPb->SetTitle(";E_{T} [GeV];#frac{Eff_{#sigma^{2}_{long} < 0.33} - Eff_{ #sigma^{2}_{long} < 0.27}}{2CV}");
  hSSCDiff_pPb->Add(hSSCEff_MinuspPb, -1);
  hSSCDiff_pPb->Scale(0.5);
  //hSSCDiff_pPb->Divide(hEff_pPb);

  TCanvas* cSSCDiff_pPb = new TCanvas("cSSCDiff_pPb", "cSSCDiff_pPb");
  hSSCDiff_pPb->GetYaxis()->SetRangeUser(0, 0.2);
  hSSCDiff_pPb->GetXaxis()->SetRangeUser(12, 60);
  hSSCDiff_pPb->Draw("hist");
  
  //Isolation efficiency 
  TFile* fileISO_PluspPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/SystematicCheck/IsoEffect/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsIso2.root","READ");
  TH1F* hISOEff_PluspPb = (TH1F*)fileISO_PluspPb->Get("hTotalEfficiency");hISOEff_PluspPb->SetLineColor(kMagenta);hISOEff_PluspPb->SetMarkerColor(kMagenta);

  TFile* fileISO_MinuspPb = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/17g6a1/SystematicCheck/IsoEffect/fout_14bins_firstEvent0_17g6a1_pthatAll_wNeutralsIso1.root","READ");
  TH1F* hISOEff_MinuspPb = (TH1F*)fileISO_MinuspPb->Get("hTotalEfficiency");hISOEff_MinuspPb->SetLineColor(kBlue);hISOEff_MinuspPb->SetMarkerColor(kBlue);
    
  
  TLegend* lISO_pPb = new TLegend(0.6, 0.7, 0.87, 0.87);
  lISO_pPb->AddEntry(hEff_pPb, "iso < 1.5 GeV/c");
  lISO_pPb->AddEntry(hISOEff_PluspPb, "iso < 1 GeV/c");
  lISO_pPb->AddEntry(hISOEff_MinuspPb, "iso < 2 GeV/c");
  
  TCanvas* cISO_pPb = new TCanvas("cISO_pPb", "cISO_pPb");
  hEff_pPb->SetTitle(";E_{T} [GeV]; #epsilon^{iso}_{#gamma}");
  hEff_pPb->GetXaxis()->SetRangeUser(12, 60);
  hEff_pPb->Draw("e1");
  hISOEff_PluspPb->Draw("samee1");
  hISOEff_MinuspPb->Draw("samee1");
  lISO_pPb->Draw("same");

  TH1F* hISODiff_pPb = (TH1F*)hISOEff_PluspPb->Clone("hISODiff_pPb");
  hISODiff_pPb->SetTitle(";E_{T} [GeV];#frac{Eff_{iso < 1} - Eff_{iso < 2}}{2CV}");
  hISODiff_pPb->Add(hISOEff_MinuspPb, -1);
  hISODiff_pPb->Scale(0.5);
  //hISODiff_pPb->Divide(hEff_pPb);

  TCanvas* cISODiff_pPb = new TCanvas("cISODiff_pPb", "cISODiff_pPb");
  hISODiff_pPb->GetYaxis()->SetRangeUser(0, 0.2);
  hISODiff_pPb->GetXaxis()->SetRangeUser(12, 60);
  hISODiff_pPb->Draw("hist");






  //pp efficiency
  TFile* file_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutrals.root","READ");
  TH1F* hEff_pp = (TH1F*)file_pp->Get("hTotalEfficiency");hEff_pp->SetLineColor(kRed);hEff_pp->SetMarkerColor(kRed); hEff_pp->SetMarkerStyle(kFullCircle);

  //Shower shape efficiency 
  TFile* fileSSC_Pluspp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/SystematicCheck/ShowerShape/fout_14bins_firstEvent0_18b10a_calo_wNeutralsShowerShapeMaxPoint33.root","READ");
  TH1F* hSSCEff_Pluspp = (TH1F*)fileSSC_Pluspp->Get("hTotalEfficiency");hSSCEff_Pluspp->SetLineColor(kMagenta);hSSCEff_Pluspp->SetMarkerColor(kMagenta);

  TFile* fileSSC_Minuspp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/SystematicCheck/ShowerShape/fout_14bins_firstEvent0_18b10a_calo_wNeutralsShowerShapeMaxPoint27.root","READ");
  TH1F* hSSCEff_Minuspp = (TH1F*)fileSSC_Minuspp->Get("hTotalEfficiency");hSSCEff_Minuspp->SetLineColor(kBlue);hSSCEff_Minuspp->SetMarkerColor(kBlue);
    
  
  TLegend* lSSC_pp = new TLegend(0.6, 0.7, 0.87, 0.87);
  lSSC_pp->AddEntry(hEff_pp, "0.1 < #sigma^{2}_{long} < 0.3");
  lSSC_pp->AddEntry(hSSCEff_Pluspp, "0.1 < #sigma^{2}_{long} < 0.27");
  lSSC_pp->AddEntry(hSSCEff_Minuspp, "0.1 < #sigma^{2}_{long} < 0.33");
  
  TCanvas* cSSC_pp = new TCanvas("cSSC_pp", "cSSC_pp");
  hEff_pp->SetTitle(";E_{T} [GeV]; #epsilon^{iso}_{#gamma}");
  hEff_pp->GetXaxis()->SetRangeUser(12, 60);
  hEff_pp->Draw("e1");
  hSSCEff_Pluspp->Draw("samee1");
  hSSCEff_Minuspp->Draw("samee1");
  lSSC_pp->Draw("same");

  TH1F* hSSCDiff_pp = (TH1F*)hSSCEff_Pluspp->Clone("hSSCDiff_pp");
  hSSCDiff_pp->SetTitle(";E_{T} [GeV];#frac{Eff_{#sigma^{2}_{long} < 0.33} - Eff_{ #sigma^{2}_{long} < 0.27}}{2CV}");
  hSSCDiff_pp->Add(hSSCEff_Minuspp, -1);
  hSSCDiff_pp->Scale(0.5);
  //hSSCDiff_pp->Divide(hEff_pp);

  TCanvas* cSSCDiff_pp = new TCanvas("cSSCDiff_pp", "cSSCDiff_pp");
  hSSCDiff_pp->GetYaxis()->SetRangeUser(0, 0.2);
  hSSCDiff_pp->GetXaxis()->SetRangeUser(12, 60);
  hSSCDiff_pp->Draw("hist");
  
  //Isolation efficiency 
  TFile* fileISO_Pluspp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/SystematicCheck/IsoEffect/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsIso2.root","READ");
  TH1F* hISOEff_Pluspp = (TH1F*)fileISO_Pluspp->Get("hTotalEfficiency");hISOEff_Pluspp->SetLineColor(kMagenta);hISOEff_Pluspp->SetMarkerColor(kMagenta);

  TFile* fileISO_Minuspp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/18b10a/SystematicCheck/IsoEffect/fout_14bins_firstEvent0_18b10a_calo_pthatAll_wNeutralsIso1.root","READ");
  TH1F* hISOEff_Minuspp = (TH1F*)fileISO_Minuspp->Get("hTotalEfficiency");hISOEff_Minuspp->SetLineColor(kBlue);hISOEff_Minuspp->SetMarkerColor(kBlue);
    
  
  TLegend* lISO_pp = new TLegend(0.6, 0.7, 0.87, 0.87);
  lISO_pp->AddEntry(hEff_pp, "iso < 1.5 GeV/c");
  lISO_pp->AddEntry(hISOEff_Pluspp, "iso < 1 GeV/c");
  lISO_pp->AddEntry(hISOEff_Minuspp, "iso < 2 GeV/c");
  
  TCanvas* cISO_pp = new TCanvas("cISO_pp", "cISO_pp");
  hEff_pp->SetTitle(";E_{T} [GeV]; #epsilon^{iso}_{#gamma}");
  hEff_pp->GetXaxis()->SetRangeUser(12, 60);
  hEff_pp->Draw("e1");
  hISOEff_Pluspp->Draw("samee1");
  hISOEff_Minuspp->Draw("samee1");
  lISO_pp->Draw("same");

  TH1F* hISODiff_pp = (TH1F*)hISOEff_Pluspp->Clone("hISODiff_pp");
  hISODiff_pp->SetTitle(";E_{T} [GeV];#frac{Eff_{iso < 1} - Eff_{iso < 2}}{2CV}");
  hISODiff_pp->Add(hISOEff_Minuspp, -1);
  hISODiff_pp->Scale(0.5);
  //hISODiff_pp->Divide(hEff_pp);

  TCanvas* cISODiff_pp = new TCanvas("cISODiff_pp", "cISODiff_pp");
  hISODiff_pp->GetYaxis()->SetRangeUser(0, 0.2);
  hISODiff_pp->GetXaxis()->SetRangeUser(12, 60);
  hISODiff_pp->Draw("hist");

  //Writing to file
  /*cout << "writing to file" << endl;
  TString outputName = "efficiencySystematics";
  TFile* fout = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/MC/%s.root",outputName.Data()), "RECREATE");
  hSSCDiff_pp->Write("hSSCDiff_pp");
  hSSCDiff_pPb->Write("hSSCDiff_pPb");
  hISODiff_pp->Write("hISODiff_pp");
  hISODiff_pPb->Write("hISODiff_pPb");
  fout->Close();
  cout << "done writing to file" << endl;//*/

}//end makeComparisons
