#include <fstream>
#include <vector>
void efficencyEffectCompare(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  

  //Obtain and plotting histograms from data

  TFile* mcFile_pp = new TFile("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/18b10a_100Kevents_erwanbinning_noNorm_allCutsEff2_yesNoISOSSC_SSCPlots_allptHatBins.root","READ");
  TFile* dataFile_pp = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_4_14bins_firstEvent0_latEvent8250141_17q_ITSonly_noThresh_muonCalo_phySel_part004_CALOonly_yesNoISOSSC_SSCPlots_noNorm2.root","READ");
  

  
  TH1D* mcYesSSC = (TH1D*)mcFile_pp->Get("h_YesSSC"); mcYesSSC->SetName("mcYesSSC");
  TH1D* mcNoSSC = (TH1D*)mcFile_pp->Get("h_NoSSC"); mcYesSSC->SetName("mcYesSSC");
  TH1D* mcEff = (TH1D*)mcYesSSC->Clone("mcEff");
  mcEff->Divide(mcNoSSC);

  TH1F* dataYesSSC = (TH1F*)dataFile_pp->Get("h_YesSSC"); dataYesSSC->SetName("dataYesSSC");
  TH1F* dataNoSSC = (TH1F*)dataFile_pp->Get("h_NoSSC"); dataYesSSC->SetName("dataYesSSC");
  TH1F* dataEff = (TH1F*)dataYesSSC->Clone("dataEff");
  dataEff->Divide(dataNoSSC);


  mcYesSSC->SetLineColor(kRed); mcYesSSC->SetMarkerColor(kRed); mcYesSSC->SetMarkerStyle(kFullCircle);
  dataYesSSC->SetLineColor(kBlue); dataYesSSC->SetMarkerColor(kBlue); dataYesSSC->SetMarkerStyle(kFullCircle);
  mcNoSSC->SetLineColor(kRed); mcNoSSC->SetMarkerColor(kRed); mcNoSSC->SetMarkerStyle(kFullSquare);
  dataNoSSC->SetLineColor(kBlue); dataNoSSC->SetMarkerColor(kBlue); dataNoSSC->SetMarkerStyle(kFullSquare);
  mcEff->SetLineColor(kRed); mcEff->SetMarkerColor(kRed); mcEff->SetMarkerStyle(kFullCircle);
  dataEff->SetLineColor(kBlue); dataEff->SetMarkerColor(kBlue); dataEff->SetMarkerStyle(kFullCircle);

  TCanvas* cRT = new TCanvas();
  cRT->SetLogy();
  mcYesSSC->Scale(1/mcYesSSC->Integral());
  mcNoSSC->Scale(1/mcNoSSC->Integral());
  dataYesSSC->Scale(1/dataYesSSC->Integral());
  dataNoSSC->Scale(1/dataNoSSC->Integral());
  mcYesSSC->SetTitle(";p_{T}^{Reco} [GeV/c];N");
  mcYesSSC->GetYaxis()->SetRangeUser(1e-4,1);
  mcYesSSC->Draw("e1");
  mcNoSSC->Draw("samee1");
  dataYesSSC->Draw("samee1");
  dataNoSSC->Draw("samee1");

  TLegend* lRT = new TLegend(0.6, 0.6,0.85, 0.85);
  lRT->AddEntry(mcYesSSC, "MC photons pass SSC");
  lRT->AddEntry(mcNoSSC, "MC all photons pass SSC");
  lRT->AddEntry(dataYesSSC, "Data photons pass SSC");
  lRT->AddEntry(dataNoSSC, "Data all photons pass SSC");
  lRT->Draw("same");

  TCanvas* cEff  = new TCanvas();
  mcEff->SetTitle(";p_{T}^{Reco} [GeV/c];#epsilon");
  mcEff->GetYaxis()->SetRangeUser(0,1);
  mcEff->Draw("e1");
  dataEff->Draw("samee1");

  TLegend* lEff = new TLegend(0.6, 0.6,0.85, 0.85);
  lEff->AddEntry(mcEff, "MC shower shape efficiency");
  lEff->AddEntry(dataEff, "Data shower shape efficiency");
  lEff->Draw("same");

  TH1D* mcSSC5to20 = (TH1D*)mcFile_pp->Get("hSSC5to12");
  TH1F* dataSSC5to20 = (TH1F*)dataFile_pp->Get("hSSC5to12");
  
}//end makeComparisons
