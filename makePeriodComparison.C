#include <fstream>
#include <vector>
void makePeriodComparison(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  

  //Obtain and plotting histograms from data

  TFile* file_allppAndpPb = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/AllppAndpPb.root","READ");
  TH1F* rpa_allppAndpPb = (TH1F*)file_allppAndpPb->Get("h_RpA");rpa_allppAndpPb->SetLineColor(kRed);rpa_allppAndpPb->SetMarkerColor(kRed);
  TH1F* hcsratioEG1_allppAndpPb = (TH1F*)file_allppAndpPb->Get("crossSectionRatio_EG1");hcsratioEG1_allppAndpPb->SetLineColor(kRed);hcsratioEG1_allppAndpPb->SetMarkerColor(kRed);
  TH1F* hcsratioEG2_allppAndpPb = (TH1F*)file_allppAndpPb->Get("crossSectionRatio_EG2");hcsratioEG2_allppAndpPb->SetLineColor(kRed);hcsratioEG2_allppAndpPb->SetMarkerColor(kRed);
  TH1F* hcsEG1_allppAndpPb = (TH1F*)file_allppAndpPb->Get("crossSection_pPb");hcsEG1_allppAndpPb->SetLineColor(kRed);hcsEG1_allppAndpPb->SetMarkerColor(kRed);
  TH1F* hcsEG2_allppAndpPb = (TH1F*)file_allppAndpPb->Get("crossSection_EG2");hcsEG2_allppAndpPb->SetLineColor(kRed);hcsEG2_allppAndpPb->SetMarkerColor(kRed);
  TH1F* hcspp_allppAndpPb = (TH1F*)file_allppAndpPb->Get("crossSection_pp");hcspp_allppAndpPb->SetLineColor(kRed);hcspp_allppAndpPb->SetMarkerColor(kRed);

  
  TFile* file_ITSonlyppAndpPb = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/ITSonlyppAndpPb.root","READ");
  TH1F* rpa_ITSonlyppAndpPb = (TH1F*)file_ITSonlyppAndpPb->Get("h_RpA");rpa_ITSonlyppAndpPb->SetLineColor(kBlue);rpa_ITSonlyppAndpPb->SetMarkerColor(kBlue);
  TH1F* hcspp_ITSonlyppAndpPb = (TH1F*)file_ITSonlyppAndpPb->Get("crossSection_pp");hcspp_ITSonlyppAndpPb->SetLineColor(kBlue);hcspp_ITSonlyppAndpPb->SetMarkerColor(kRed);

  //13d
  TFile* file_allppAnd13d = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/AllppAnd13d.root","READ");
  TH1F* rpa_allppAnd13d = (TH1F*)file_allppAnd13d->Get("h_RpA");rpa_allppAnd13d->SetLineColor(kGreen);rpa_allppAnd13d->SetMarkerColor(kGreen);
  TH1F* hcsratioEG1_allppAnd13d = (TH1F*)file_allppAnd13d->Get("crossSectionRatio_EG1");hcsratioEG1_allppAnd13d->SetLineColor(kGreen);hcsratioEG1_allppAnd13d->SetMarkerColor(kGreen);
  TH1F* hcsratioEG2_allppAnd13d = (TH1F*)file_allppAnd13d->Get("crossSectionRatio_EG2");hcsratioEG2_allppAnd13d->SetLineColor(kGreen);hcsratioEG2_allppAnd13d->SetMarkerColor(kGreen);
  TH1F* hcsEG1_allppAnd13d = (TH1F*)file_allppAnd13d->Get("crossSection_pPb");hcsEG1_allppAnd13d->SetLineColor(kGreen);hcsEG1_allppAnd13d->SetMarkerColor(kGreen);
  TH1F* hcsEG2_allppAnd13d = (TH1F*)file_allppAnd13d->Get("crossSection_EG2");hcsEG2_allppAnd13d->SetLineColor(kGreen);hcsEG2_allppAnd13d->SetMarkerColor(kGreen);

  //13e
  TFile* file_allppAnd13e = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/AllppAnd13e.root","READ");
  TH1F* rpa_allppAnd13e = (TH1F*)file_allppAnd13e->Get("h_RpA");rpa_allppAnd13e->SetLineColor(kMagenta);rpa_allppAnd13e->SetMarkerColor(kMagenta);
  TH1F* hcsratioEG1_allppAnd13e = (TH1F*)file_allppAnd13e->Get("crossSectionRatio_EG1");hcsratioEG1_allppAnd13e->SetLineColor(kMagenta);hcsratioEG1_allppAnd13e->SetMarkerColor(kMagenta);
  TH1F* hcsratioEG2_allppAnd13e = (TH1F*)file_allppAnd13e->Get("crossSectionRatio_EG2");hcsratioEG2_allppAnd13e->SetLineColor(kMagenta);hcsratioEG2_allppAnd13e->SetMarkerColor(kMagenta);
  TH1F* hcsEG1_allppAnd13e = (TH1F*)file_allppAnd13e->Get("crossSection_pPb");hcsEG1_allppAnd13e->SetLineColor(kMagenta);hcsEG1_allppAnd13e->SetMarkerColor(kMagenta);
  TH1F* hcsEG2_allppAnd13e = (TH1F*)file_allppAnd13e->Get("crossSection_EG2");hcsEG2_allppAnd13e->SetLineColor(kMagenta);hcsEG2_allppAnd13e->SetMarkerColor(kMagenta);

  //13f
  TFile* file_allppAnd13f = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/AllppAnd13f.root","READ");
  TH1F* rpa_allppAnd13f = (TH1F*)file_allppAnd13f->Get("h_RpA");rpa_allppAnd13f->SetLineColor(kCyan);rpa_allppAnd13f->SetMarkerColor(kCyan);
  TH1F* hcsratioEG1_allppAnd13f = (TH1F*)file_allppAnd13f->Get("crossSectionRatio_EG1");hcsratioEG1_allppAnd13f->SetLineColor(kCyan);hcsratioEG1_allppAnd13f->SetMarkerColor(kCyan);
  TH1F* hcsratioEG2_allppAnd13f = (TH1F*)file_allppAnd13f->Get("crossSectionRatio_EG2");hcsratioEG2_allppAnd13f->SetLineColor(kCyan);hcsratioEG2_allppAnd13f->SetMarkerColor(kCyan);
  TH1F* hcsEG1_allppAnd13f = (TH1F*)file_allppAnd13f->Get("crossSection_pPb");hcsEG1_allppAnd13f->SetLineColor(kCyan);hcsEG1_allppAnd13f->SetMarkerColor(kCyan);
  TH1F* hcsEG2_allppAnd13f = (TH1F*)file_allppAnd13f->Get("crossSection_EG2");hcsEG2_allppAnd13f->SetLineColor(kCyan);hcsEG2_allppAnd13f->SetMarkerColor(kCyan);

  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);

  //RpA
  TLegend* lRpA = new TLegend(0.6,0.7,0.85,0.85);
  lRpA->SetHeader("R_{pPb}");
  lRpA->AddEntry(rpa_allppAndpPb, "all pp and p-Pb runs");
  lRpA->AddEntry(rpa_ITSonlyppAndpPb, "ITS-only pp and all p-Pb runs");
  lRpA->AddEntry(rpa_allppAnd13d, "all pp and 13d runs");
  lRpA->AddEntry(rpa_allppAnd13e, "all pp and 13e runs");
  lRpA->AddEntry(rpa_allppAnd13f, "all pp and 13f runs");

  TCanvas* cRpA = new TCanvas();
  rpa_allppAndpPb->Draw("e1");
  rpa_ITSonlyppAndpPb->Draw("samee1");
  rpa_allppAnd13d->Draw("samee1");
  rpa_allppAnd13e->Draw("samee1");
  rpa_allppAnd13f->Draw("samee1");
  line->Draw("same");
  lRpA->Draw("same");


  //HcsEG1
  TLegend* lHcsEG1 = new TLegend(0.6,0.7,0.85,0.85);
  lHcsEG1->SetHeader("EG1 cross section");
  lHcsEG1->AddEntry(hcsEG1_allppAndpPb, "all p-Pb");
  lHcsEG1->AddEntry(hcsEG1_allppAnd13d, "13d");
  lHcsEG1->AddEntry(hcsEG1_allppAnd13e, "13e");
  lHcsEG1->AddEntry(hcsEG1_allppAnd13f, "13f");

  TCanvas* cHcsEG1 = new TCanvas();
  cHcsEG1->SetLogy();
  hcsEG1_allppAndpPb->Draw("e1");
  hcsEG1_allppAnd13d->Draw("samee1");
  hcsEG1_allppAnd13e->Draw("samee1");
  hcsEG1_allppAnd13f->Draw("samee1");
  lHcsEG1->Draw("same");

  //HcsEG2
  TLegend* lHcsEG2 = new TLegend(0.6,0.7,0.85,0.85);
  lHcsEG2->SetHeader("EG2 cross section");
  lHcsEG2->AddEntry(hcsEG2_allppAndpPb, "all p-Pb");
  lHcsEG2->AddEntry(hcsEG2_allppAnd13d, "13d");
  lHcsEG2->AddEntry(hcsEG2_allppAnd13e, "13e");
  lHcsEG2->AddEntry(hcsEG2_allppAnd13f, "13f");

  TCanvas* cHcsEG2 = new TCanvas();
  cHcsEG2->SetLogy();
  hcsEG2_allppAndpPb->Draw("e1");
  hcsEG2_allppAnd13d->Draw("samee1");
  hcsEG2_allppAnd13e->Draw("samee1");
  hcsEG2_allppAnd13f->Draw("samee1");
  lHcsEG2->Draw("same");

  //HcsEG1
  TLegend* lHcsratioEG1 = new TLegend(0.6,0.7,0.85,0.85);
  lHcsratioEG1->SetHeader("EG1 cross section ratio");
  lHcsratioEG1->AddEntry(hcsratioEG1_allppAndpPb, "all p-Pb");
  lHcsratioEG1->AddEntry(hcsratioEG1_allppAnd13d, "13d");
  lHcsratioEG1->AddEntry(hcsratioEG1_allppAnd13e, "13e");
  lHcsratioEG1->AddEntry(hcsratioEG1_allppAnd13f, "13f");

  TCanvas* cHcsratioEG1 = new TCanvas();
  hcsratioEG1_allppAndpPb->Draw("e1");
  hcsratioEG1_allppAnd13d->Draw("samee1");
  hcsratioEG1_allppAnd13e->Draw("samee1");
  hcsratioEG1_allppAnd13f->Draw("samee1");
  line->Draw("same");
  lHcsratioEG1->Draw("same");

  //HcsratioEG2
  TLegend* lHcsratioEG2 = new TLegend(0.6,0.7,0.85,0.85);
  lHcsratioEG2->SetHeader("EG2 cross section ratio");
  lHcsratioEG2->AddEntry(hcsratioEG2_allppAndpPb, "all p-Pb");
  lHcsratioEG2->AddEntry(hcsratioEG2_allppAnd13d, "13d");
  lHcsratioEG2->AddEntry(hcsratioEG2_allppAnd13e, "13e");
  lHcsratioEG2->AddEntry(hcsratioEG2_allppAnd13f, "13f");

  TCanvas* cHcsratioEG2 = new TCanvas();
  hcsratioEG2_allppAndpPb->Draw("e1");
  hcsratioEG2_allppAnd13d->Draw("samee1");
  hcsratioEG2_allppAnd13e->Draw("samee1");
  hcsratioEG2_allppAnd13f->Draw("samee1");
  line->Draw("same");
  lHcsratioEG2->Draw("same");//*/




  




  //13def
  TFile* spectraFile_13def = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/noPurityClusterSpectra/fout_6_14bins_firstEvent0_13def.root","READ");
  TH1F* hcswoP_13def = (TH1F*)spectraFile_13def->Get("hEG2woPurity");hcswoP_13def->SetLineColor(kRed);hcswoP_13def->SetMarkerColor(kRed);hcswoP_13def->SetMarkerStyle(kFullCircle);

  //13d
  TFile* spectraFile_13d = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/noPurityClusterSpectra/fout_6_14bins_firstEvent0_13d_all10runs_noSkim.root","READ");
  //TFile* spectraFile_13d = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/13d/RunListCheck/fout_7_14bins_firstEvent0_13d_all10runs_noSkim_checkEventCounts_noRun195871.root","READ");
  //TFile* spectraFile_13d = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/13d/RunListCheck/fout_7_14bins_firstEvent0_13d_all10runs_noSkim_checkEventCounts_noRun195829.root","READ");
  //TFile* spectraFile_13d = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/13d/RunListCheck/fout_7_14bins_firstEvent0_13d_all10runs_noSkim_checkEventCounts_noRun195871or195829.root","READ");
  TH1F* hcswoP_13d = (TH1F*)spectraFile_13d->Get("hEG2woPurity");hcswoP_13d->SetLineColor(kGreen);hcswoP_13d->SetMarkerColor(kGreen);hcswoP_13d->SetMarkerStyle(kFullCircle);

  //13e
  TFile* spectraFile_13e = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/noPurityClusterSpectra/fout_6_14bins_firstEvent0_13e.root","READ");
  TH1F* hcswoP_13e = (TH1F*)spectraFile_13e->Get("hEG2woPurity");hcswoP_13e->SetLineColor(kMagenta);hcswoP_13e->SetMarkerColor(kMagenta);hcswoP_13e->SetMarkerStyle(kFullCircle);

  TFile* spectraFile_13f = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/noPurityClusterSpectra/fout_6_14bins_firstEvent0_13f.root","READ");
  TH1F* hcswoP_13f = (TH1F*)spectraFile_13f->Get("hEG2woPurity");hcswoP_13f->SetLineColor(kCyan);hcswoP_13f->SetMarkerColor(kCyan);hcswoP_13f->SetMarkerStyle(kFullCircle);


  //Hcswop
  TLegend* lHcswoP = new TLegend(0.5,0.7,0.85,0.85);
  lHcswoP->SetHeader("All 13d");
  lHcswoP->AddEntry(hcswoP_13d, "13d");
  lHcswoP->AddEntry(hcswoP_13e, "13e");
  //lHcswoP->AddEntry(hcswoP_13f, "13f");
  //lHcswoP->AddEntry(hcswoP_13def, "all p-Pb");

  hcswoP_13d->Divide(hcswoP_13f);
  hcswoP_13e->Divide(hcswoP_13f);
  
  TCanvas* cHcswoP = new TCanvas();
  //cHcswoP->SetLogy();
  hcswoP_13d->SetTitle(";E_{T} [GeV]; ratio to 13f");
  hcswoP_13d->Draw("e1");
  hcswoP_13e->Draw("samee1");
  //hcswoP_13f->Draw("samee1");
  //hcswoP_13def->Draw("samee1");
  lHcswoP->Draw("same");
  line->Draw("same");//*/
  

  






  //13d weird run comparison
  /*TFile* file_all13d = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/rfOutput/pPOutput/StdEventsAndClusterCuts/fout_6_26bins_forRTrigEG_13d_Allruns_noThresh_phySel_noNorm.root","READ");
  TH1F* hEG1_all13d = (TH1F*)file_all13d->Get("hEG1_E");
  hEG1_all13d->SetLineColor(kRed); hEG1_all13d->SetMarkerColor(kRed); hEG1_all13d->SetMarkerStyle(kOpenCircle); hEG1_all13d->SetMarkerSize(3);

  TFile* file_noRun195829 = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/rfOutput/pPOutput/13dOutput/GoodRunsCheck/fout_7_26bins_forRTrig_13d_all10runs_noSkimnoTrigOverlap_no195829_noNorm.root","READ");
  TH1F* hEG1_noRun195829 = (TH1F*)file_noRun195829->Get("hEG1_E");
  hEG1_noRun195829->SetLineColor(kBlue); hEG1_noRun195829->SetMarkerColor(kBlue); hEG1_noRun195829->SetMarkerStyle(kOpenSquare); hEG1_noRun195829->SetMarkerSize(3);

  TFile* file_noRun195871 = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/rfOutput/pPOutput/13dOutput/GoodRunsCheck/fout_7_26bins_forRTrig_13d_all10runs_noSkimnoTrigOverlap_no195871_noNorm.root","READ");
  TH1F* hEG1_noRun195871 = (TH1F*)file_noRun195871->Get("hEG1_E");
  hEG1_noRun195871->SetLineColor(kBlack); hEG1_noRun195871->SetMarkerColor(kBlack); hEG1_noRun195871->SetMarkerStyle(kOpenDiamond); hEG1_noRun195871->SetMarkerSize(3);

  TFile* file_noRun195871or195829 = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/rfOutput/pPOutput/13dOutput/GoodRunsCheck/fout_7_26bins_forRTrig_13d_all10runs_noSkimnoTrigOverlap_no195829or195871_noNorm.root","READ");
  TH1F* hEG1_noRun195871or195829 = (TH1F*)file_noRun195871or195829->Get("hEG1_E");
  hEG1_noRun195871or195829->SetLineColor(kGreen); hEG1_noRun195871or195829->SetMarkerColor(kGreen); hEG1_noRun195871or195829->SetMarkerStyle(kStar); hEG1_noRun195871or195829->SetMarkerSize(3);

  const double deltaEta = 1.334;
  const double deltaPhi = 1.884;
  double acceptanceNorm = 2*TMath::Pi()/(deltaEta*deltaPhi);
  for(int i = 1; i < hEG1_all13d->GetNbinsX()+1; i++){
    double dE = hEG1_all13d->GetBinWidth(i);

    double contenthEG1_all13, temphEG1_all13, errorhEG1_all13, tempErrhEG1_all13;


    //all13d
    contenthEG1_all13 = temphEG1_all13 = errorhEG1_all13 = tempErrhEG1_all13 = 0.0;
    contenthEG1_all13 = hEG1_all13d->GetBinContent(i);
    temphEG1_all13 = (contenthEG1_all13*acceptanceNorm)/(280764.0*dE);
    errorhEG1_all13 = hEG1_all13d->GetBinError(i);
    tempErrhEG1_all13 = (errorhEG1_all13*acceptanceNorm)/(280764.0*dE);
    hEG1_all13d->SetBinContent(i,temphEG1_all13);
    hEG1_all13d->SetBinError(i, tempErrhEG1_all13);
    
    //noRun195829
    contenthEG1_all13 = temphEG1_all13 = errorhEG1_all13 = tempErrhEG1_all13 = 0.0;
    contenthEG1_all13 = hEG1_noRun195829->GetBinContent(i);
    temphEG1_all13 = (contenthEG1_all13*acceptanceNorm)/(278988.0*dE);
    errorhEG1_all13 = hEG1_noRun195829->GetBinError(i);
    tempErrhEG1_all13 = (errorhEG1_all13*acceptanceNorm)/(278988.0*dE);
    hEG1_noRun195829->SetBinContent(i,temphEG1_all13);
    hEG1_noRun195829->SetBinError(i, tempErrhEG1_all13);

    //noRun195871
    contenthEG1_all13 = temphEG1_all13 = errorhEG1_all13 = tempErrhEG1_all13 = 0.0;
    contenthEG1_all13 = hEG1_noRun195871->GetBinContent(i);
    temphEG1_all13 = (contenthEG1_all13*acceptanceNorm)/(198971.0*dE);
    errorhEG1_all13 = hEG1_noRun195871->GetBinError(i);
    tempErrhEG1_all13 = (errorhEG1_all13*acceptanceNorm)/(198971.0*dE);
    hEG1_noRun195871->SetBinContent(i,temphEG1_all13);
    hEG1_noRun195871->SetBinError(i, tempErrhEG1_all13);

    //noRun195871or195829
    contenthEG1_all13 = temphEG1_all13 = errorhEG1_all13 = tempErrhEG1_all13 = 0.0;
    contenthEG1_all13 = hEG1_noRun195871or195829->GetBinContent(i);
    temphEG1_all13 = (contenthEG1_all13*acceptanceNorm)/(197195.0*dE);
    errorhEG1_all13 = hEG1_noRun195871or195829->GetBinError(i);
    tempErrhEG1_all13 = (errorhEG1_all13*acceptanceNorm)/(197195.0*dE);
    hEG1_noRun195871or195829->SetBinContent(i,temphEG1_all13);
    hEG1_noRun195871or195829->SetBinError(i, tempErrhEG1_all13);

  }
  
  TLegend* l13dRunCompare = new TLegend(0.5, 0.6, 0.87,0.87);
  l13dRunCompare->AddEntry(hEG1_all13d, "all 13d runs");
  l13dRunCompare->AddEntry(hEG1_noRun195829, "no run 195829");
  l13dRunCompare->AddEntry(hEG1_noRun195871, "no run 195871");
  l13dRunCompare->AddEntry(hEG1_noRun195871or195829, "no runs 195829 or 195871");
  TCanvas* c13dRunCompare = new TCanvas("c13dRunCompare", "c13dRunCompare", 800, 800);
  c13dRunCompare->SetLogy();
  hEG1_all13d->Draw("e1");
  hEG1_noRun195829->Draw("samee1");
  hEG1_noRun195871->Draw("samee1");
  hEG1_noRun195871or195829->Draw("samee1");
  l13dRunCompare->Draw("same");//*/



  
}//end makeComparisons
