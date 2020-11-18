#include <fstream>
#include <vector>
void study13dWeirdRun(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  

  //13d
  //TFile* spectraFile_13d = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/noPurityClusterSpectra/fout_6_14bins_firstEvent0_13d_all10runs_noSkim.root","READ");
  //TFile* spectraFile_13d = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/13d/RunListCheck/fout_7_14bins_firstEvent0_13d_all10runs_noSkim_checkEventCounts_noRun195871.root","READ");
  //TFile* spectraFile_13d = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/13d/RunListCheck/fout_7_14bins_firstEvent0_13d_all10runs_noSkim_checkEventCounts_noRun195829.root","READ");
  //TFile* spectraFile_13d = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/csOutput/pPbOutput/13d/RunListCheck/fout_7_14bins_firstEvent0_13d_all10runs_noSkim_checkEventCounts_noRun195871or195829.root","READ");
  //TH1F* hcswoP_13d = (TH1F*)spectraFile_13d->Get("hEG2woPurity");hcswoP_13d->SetLineColor(kGreen);hcswoP_13d->SetMarkerColor(kGreen);hcswoP_13d->SetMarkerStyle(kFullCircle);
  
  //13d weird run comparison
  TFile* file_all13d = new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/rfOutput/pPOutput/StdEventsAndClusterCuts/fout_6_26bins_forRTrigEG_13d_Allruns_noThresh_phySel_noNorm.root","READ");
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
  
  TLegend* l13dRunCompare = new TLegend(0.35, 0.65, 0.65,0.87);
  //l13dRunCompare->AddEntry(hEG1_all13d, "all 13d runs");
  l13dRunCompare->AddEntry(hEG1_noRun195829, "no run 195829");
  l13dRunCompare->AddEntry(hEG1_noRun195871, "no run 195871");
  l13dRunCompare->AddEntry(hEG1_noRun195871or195829, "no runs 195829 or 195871");
  
  hEG1_noRun195829->Divide(hEG1_all13d);
  hEG1_noRun195871->Divide(hEG1_all13d);
  hEG1_noRun195871or195829->Divide(hEG1_all13d);
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);
  line->SetLineWidth(4);
  
  TCanvas* c13dRunCompare = new TCanvas("c13dRunCompare", "c13dRunCompare", 800, 800);
  c13dRunCompare->SetLogy();
  //hEG1_all13d->Draw("e1");
  hEG1_noRun195829->Draw("e1");
  hEG1_noRun195871->Draw("samee1");
  hEG1_noRun195871or195829->Draw("samee1");
  line->Draw("same");
  l13dRunCompare->Draw("same");//*/

  
}//end makeComparisons
