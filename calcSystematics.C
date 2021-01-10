#include <fstream>
#include <vector>
void calcSystematics(){

  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetEndErrorSize(5);
  
  
  TLine *line = new TLine(12, 1, 60, 1);
  line->SetLineColor(kBlack);

  
  //Purity systematic
  TFile* file_StdPurity = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PurityFit.root","READ");
  TH1F* rpa_StdPurity = (TH1F*)file_StdPurity->Get("h_RpA");rpa_StdPurity->SetLineColor(kRed);rpa_StdPurity->SetMarkerColor(kRed);
  TH1F* hcsEG1_StdPurity = (TH1F*)file_StdPurity->Get("crossSection_pPb");hcsEG1_StdPurity->SetLineColor(kRed);hcsEG1_StdPurity->SetMarkerColor(kRed);
  TH1F* hcspp_StdPurity = (TH1F*)file_StdPurity->Get("crossSection_pp");hcspp_StdPurity->SetLineColor(kRed);hcspp_StdPurity->SetMarkerColor(kRed);

  TFile* file_PlusPurity = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PlusPurityFit_NoSigSysAllData.root","READ");
  TH1F* rpa_PlusPurity = (TH1F*)file_PlusPurity->Get("h_RpA");rpa_PlusPurity->SetLineColor(kMagenta);rpa_PlusPurity->SetMarkerColor(kMagenta);
  TH1F* hcsEG1_PlusPurity = (TH1F*)file_PlusPurity->Get("crossSection_pPb");hcsEG1_PlusPurity->SetLineColor(kMagenta);hcsEG1_PlusPurity->SetMarkerColor(kMagenta);
  TH1F* hcspp_PlusPurity = (TH1F*)file_PlusPurity->Get("crossSection_pp");hcspp_PlusPurity->SetLineColor(kMagenta);hcspp_PlusPurity->SetMarkerColor(kMagenta);

  TFile* file_MinusPurity = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0MinusPurityFit_NoSigSysAllData.root","READ");
  TH1F* rpa_MinusPurity = (TH1F*)file_MinusPurity->Get("h_RpA");rpa_MinusPurity->SetLineColor(kBlue);rpa_MinusPurity->SetMarkerColor(kBlue);
  TH1F* hcsEG1_MinusPurity = (TH1F*)file_MinusPurity->Get("crossSection_pPb");hcsEG1_MinusPurity->SetLineColor(kBlue);hcsEG1_MinusPurity->SetMarkerColor(kBlue);
  TH1F* hcspp_MinusPurity = (TH1F*)file_MinusPurity->Get("crossSection_pp");hcspp_MinusPurity->SetLineColor(kBlue);hcspp_MinusPurity->SetMarkerColor(kBlue);
  
  
  //RpA
  TLegend* lRpA_Purity = new TLegend(0.6,0.7,0.85,0.85);
  lRpA_Purity->SetHeader("R_{pPb}");
  lRpA_Purity->AddEntry(rpa_StdPurity, "Usual purity");
  lRpA_Purity->AddEntry(rpa_PlusPurity, "+#sigma purity");
  lRpA_Purity->AddEntry(rpa_MinusPurity, "-#sigma purity");
  

  TCanvas* cRpA_Purity = new TCanvas();
  rpa_StdPurity->Draw("e1");
  rpa_PlusPurity->Draw("same e1");
  rpa_MinusPurity->Draw("same e1");
  line->Draw("same");
  lRpA_Purity->Draw("same");


  //HcsEG1
  TLegend* lHcsEG1_Purity = new TLegend(0.6,0.7,0.85,0.85);
  lHcsEG1_Purity->SetHeader("p-Pb EG1 cross section");
  lHcsEG1_Purity->AddEntry(hcsEG1_StdPurity, "usual purity");
  lHcsEG1_Purity->AddEntry(hcsEG1_PlusPurity, "+#sigma purity");
  lHcsEG1_Purity->AddEntry(hcsEG1_MinusPurity, "-#sigma purity");

  TCanvas* cHcsEG1_Purity = new TCanvas();
  cHcsEG1_Purity->SetLogy();
  hcsEG1_StdPurity->GetXaxis()->SetRangeUser(12, 60);
  hcsEG1_StdPurity->GetYaxis()->SetRangeUser(1, 5e3);
  hcsEG1_StdPurity->Draw("e1");
  hcsEG1_PlusPurity->Draw("samee1");
  hcsEG1_MinusPurity->Draw("samee1");
  lHcsEG1_Purity->Draw("same");

  //Hcspp
  TLegend* lHcspp_Purity = new TLegend(0.6,0.7,0.85,0.85);
  lHcspp_Purity->SetHeader("pp cross section");
  lHcspp_Purity->AddEntry(hcspp_StdPurity, "usual purity");
  lHcspp_Purity->AddEntry(hcspp_PlusPurity, "+#sigma purity");
  lHcspp_Purity->AddEntry(hcspp_MinusPurity, "-#sigma purity");

  TCanvas* cHcspp_Purity = new TCanvas();
  cHcspp_Purity->SetLogy();
  hcspp_StdPurity->GetXaxis()->SetRangeUser(12, 60);
  hcspp_StdPurity->Draw("e1");
  hcspp_PlusPurity->Draw("samee1");
  hcspp_MinusPurity->Draw("samee1");
  lHcspp_Purity->Draw("same");


  TH1F* diff_pPb_Purity = (TH1F*)hcsEG1_PlusPurity->Clone("diffPlus_pPb_Purity");
  diff_pPb_Purity->SetTitle("Purity systematic: p-Pb;E_{T} [GeV/c]; #frac{|#sigma_{purity}^{+} - #sigma_{purity}^{-}|}{2CV_{purity}} [%]");
  diff_pPb_Purity->Add(hcsEG1_MinusPurity, -1);
  diff_pPb_Purity->Scale(0.5);
  diff_pPb_Purity->Divide(hcsEG1_StdPurity);
		   
  TCanvas* cdiff_pPb_Purity = new TCanvas("cdiff_pPb_Purity", "p-Pb systematic from purity");
  diff_pPb_Purity->GetXaxis()->SetRangeUser(12, 60);
  diff_pPb_Purity->GetYaxis()->SetRangeUser(0, 0.25);
  diff_pPb_Purity->Draw("hist");

  
  //pp
  TH1F* diff_pp_Purity = (TH1F*)hcspp_PlusPurity->Clone("diffPlus_pp_Purity");
  diff_pp_Purity->SetTitle("Purity systematic: pp;E_{T} [GeV/c]; #frac{|#sigma_{purity}^{+} - #sigma_{purity}^{-}|}{2CV_{purity}} [%]");
  diff_pp_Purity->Add(hcspp_MinusPurity, -1);
  diff_pp_Purity->Scale(0.5);
  diff_pp_Purity->Divide(hcspp_StdPurity);
		   
  TCanvas* cdiff_pp_Purity = new TCanvas("cdiff_pp_Purity", "pp systematic from purity");
  diff_pp_Purity->GetXaxis()->SetRangeUser(12, 60);
  diff_pp_Purity->GetYaxis()->SetRangeUser(0, 0.25);
  diff_pp_Purity->Draw("hist");

  
  /***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
  
  //Luminosity systematic
  TFile* file_StdLumi = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_LumiCV.root","READ");
  TH1F* rpa_StdLumi = (TH1F*)file_StdLumi->Get("h_RpA");rpa_StdLumi->SetLineColor(kRed);rpa_StdLumi->SetMarkerColor(kRed);
  TH1F* hcsEG1_StdLumi = (TH1F*)file_StdLumi->Get("crossSection_pPb");hcsEG1_StdLumi->SetLineColor(kRed);hcsEG1_StdLumi->SetMarkerColor(kRed);
  TH1F* hcspp_StdLumi = (TH1F*)file_StdLumi->Get("crossSection_pp");hcspp_StdLumi->SetLineColor(kRed);hcspp_StdLumi->SetMarkerColor(kRed);

  TFile* file_PlusLumi = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_PlusLumi.root","READ");
  TH1F* rpa_PlusLumi = (TH1F*)file_PlusLumi->Get("h_RpA");rpa_PlusLumi->SetLineColor(kMagenta);rpa_PlusLumi->SetMarkerColor(kMagenta);
  TH1F* hcsEG1_PlusLumi = (TH1F*)file_PlusLumi->Get("crossSection_pPb");hcsEG1_PlusLumi->SetLineColor(kMagenta);hcsEG1_PlusLumi->SetMarkerColor(kMagenta);
  TH1F* hcspp_PlusLumi = (TH1F*)file_PlusLumi->Get("crossSection_pp");hcspp_PlusLumi->SetLineColor(kMagenta);hcspp_PlusLumi->SetMarkerColor(kMagenta);

  TFile* file_MinusLumi = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_MinusLumi.root","READ");
  TH1F* rpa_MinusLumi = (TH1F*)file_MinusLumi->Get("h_RpA");rpa_MinusLumi->SetLineColor(kBlue);rpa_MinusLumi->SetMarkerColor(kBlue);
  TH1F* hcsEG1_MinusLumi = (TH1F*)file_MinusLumi->Get("crossSection_pPb");hcsEG1_MinusLumi->SetLineColor(kBlue);hcsEG1_MinusLumi->SetMarkerColor(kBlue);
  TH1F* hcspp_MinusLumi = (TH1F*)file_MinusLumi->Get("crossSection_pp");hcspp_MinusLumi->SetLineColor(kBlue);hcspp_MinusLumi->SetMarkerColor(kBlue);
  
  
  //RpA
  TLegend* lRpA_Lumi = new TLegend(0.6,0.7,0.85,0.85);
  lRpA_Lumi->SetHeader("R_{pPb}");
  lRpA_Lumi->AddEntry(rpa_StdLumi, "Usual lumi");
  lRpA_Lumi->AddEntry(rpa_PlusLumi, "+#sigma lumi");
  lRpA_Lumi->AddEntry(rpa_MinusLumi, "-#sigma lumi");
  

  TCanvas* cRpA_Lumi = new TCanvas();
  rpa_StdLumi->Draw("e1");
  rpa_PlusLumi->Draw("same e1");
  rpa_MinusLumi->Draw("same e1");
  line->Draw("same");
  lRpA_Lumi->Draw("same");


  //HcsEG1
  TLegend* lHcsEG1_Lumi = new TLegend(0.6,0.7,0.85,0.85);
  lHcsEG1_Lumi->SetHeader("p-Pb EG1 cross section");
  lHcsEG1_Lumi->AddEntry(hcsEG1_StdLumi, "usual lumi");
  lHcsEG1_Lumi->AddEntry(hcsEG1_PlusLumi, "+#sigma lumi");
  lHcsEG1_Lumi->AddEntry(hcsEG1_MinusLumi, "-#sigma lumi");

  TCanvas* cHcsEG1_Lumi = new TCanvas();
  cHcsEG1_Lumi->SetLogy();
  hcsEG1_StdLumi->GetXaxis()->SetRangeUser(12, 60);
  hcsEG1_StdLumi->GetYaxis()->SetRangeUser(1, 5e3);
  hcsEG1_StdLumi->Draw("e1");
  hcsEG1_PlusLumi->Draw("samee1");
  hcsEG1_MinusLumi->Draw("samee1");
  lHcsEG1_Lumi->Draw("same");

  //Hcspp
  TLegend* lHcspp_Lumi = new TLegend(0.6,0.7,0.85,0.85);
  lHcspp_Lumi->SetHeader("pp cross section");
  lHcspp_Lumi->AddEntry(hcspp_StdLumi, "usual lumi");
  lHcspp_Lumi->AddEntry(hcspp_PlusLumi, "+#sigma lumi");
  lHcspp_Lumi->AddEntry(hcspp_MinusLumi, "-#sigma lumi");

  TCanvas* cHcspp_Lumi = new TCanvas();
  cHcspp_Lumi->SetLogy();
  hcspp_StdLumi->GetXaxis()->SetRangeUser(12, 60);
  hcspp_StdLumi->Draw("e1");
  hcspp_PlusLumi->Draw("samee1");
  hcspp_MinusLumi->Draw("samee1");
  lHcspp_Lumi->Draw("same");


  TH1F* diff_pPb_Lumi = (TH1F*)hcsEG1_MinusLumi->Clone("diffPlus_pPb_Lumi");
  diff_pPb_Lumi->SetTitle("Luminosity systematic: p-Pb;E_{T} [GeV/c]; #frac{|#sigma_{lumi}^{+} - #sigma_{lumi}^{-}|}{2CV_{lumi}} [%]");
  diff_pPb_Lumi->Add(hcsEG1_PlusLumi, -1);
  diff_pPb_Lumi->Scale(0.5);
  diff_pPb_Lumi->Divide(hcsEG1_StdLumi);
		   
  TCanvas* cdiff_pPb_Lumi = new TCanvas("cdiff_pPb_Lumi", "p-Pb systematic from lumi");
  diff_pPb_Lumi->GetXaxis()->SetRangeUser(12, 60);
  diff_pPb_Lumi->GetYaxis()->SetRangeUser(0, 0.05);
  diff_pPb_Lumi->Draw("hist");

  
  //pp
  TH1F* diff_pp_Lumi = (TH1F*)hcspp_MinusLumi->Clone("diffPlus_pp_Lumi");
  diff_pp_Lumi->SetTitle("Luminosity systematic: pp;E_{T} [GeV/c]; #frac{|#sigma_{lumi}^{+} - #sigma_{lumi}^{-}|}{2CV_{lumi}} [%]");
  diff_pp_Lumi->Add(hcspp_PlusLumi, -1);
  diff_pp_Lumi->Scale(0.5);
  diff_pp_Lumi->Divide(hcspp_StdLumi);
		   
  TCanvas* cdiff_pp_Lumi = new TCanvas("cdiff_pp_Lumi", "pp systematic from lumi");
  diff_pp_Lumi->GetXaxis()->SetRangeUser(12, 60);
  diff_pp_Lumi->GetYaxis()->SetRangeUser(0, 0.05);
  //diff_pp_Lumi->Draw("hist");
  
  /***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/

  //SSC Efficiency
  TFile* file_StdSSCEff = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_LumiCV.root","READ");
  TH1F* rpa_StdSSCEff = (TH1F*)file_StdSSCEff->Get("h_RpA");rpa_StdSSCEff->SetLineColor(kRed);rpa_StdSSCEff->SetMarkerColor(kRed);
  TH1F* hcsEG1_StdSSCEff = (TH1F*)file_StdSSCEff->Get("crossSection_pPb");hcsEG1_StdSSCEff->SetLineColor(kRed);hcsEG1_StdSSCEff->SetMarkerColor(kRed);
  TH1F* hcspp_StdSSCEff = (TH1F*)file_StdSSCEff->Get("crossSection_pp");hcspp_StdSSCEff->SetLineColor(kRed);hcspp_StdSSCEff->SetMarkerColor(kRed);

  TFile* file_PlusSSCEff = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_PlusEffSSC.root","READ");
  TH1F* rpa_PlusSSCEff = (TH1F*)file_PlusSSCEff->Get("h_RpA");rpa_PlusSSCEff->SetLineColor(kMagenta);rpa_PlusSSCEff->SetMarkerColor(kMagenta);
  TH1F* hcsEG1_PlusSSCEff = (TH1F*)file_PlusSSCEff->Get("crossSection_pPb");hcsEG1_PlusSSCEff->SetLineColor(kMagenta);hcsEG1_PlusSSCEff->SetMarkerColor(kMagenta);
  TH1F* hcspp_PlusSSCEff = (TH1F*)file_PlusSSCEff->Get("crossSection_pp");hcspp_PlusSSCEff->SetLineColor(kMagenta);hcspp_PlusSSCEff->SetMarkerColor(kMagenta);

  TFile* file_MinusSSCEff = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_MinusEffSSC.root","READ");
  TH1F* rpa_MinusSSCEff = (TH1F*)file_MinusSSCEff->Get("h_RpA");rpa_MinusSSCEff->SetLineColor(kBlue);rpa_MinusSSCEff->SetMarkerColor(kBlue);
  TH1F* hcsEG1_MinusSSCEff = (TH1F*)file_MinusSSCEff->Get("crossSection_pPb");hcsEG1_MinusSSCEff->SetLineColor(kBlue);hcsEG1_MinusSSCEff->SetMarkerColor(kBlue);
  TH1F* hcspp_MinusSSCEff = (TH1F*)file_MinusSSCEff->Get("crossSection_pp");hcspp_MinusSSCEff->SetLineColor(kBlue);hcspp_MinusSSCEff->SetMarkerColor(kBlue);
  
  
  //RpA
  TLegend* lRpA_SSCEff = new TLegend(0.6,0.7,0.85,0.85);
  lRpA_SSCEff->SetHeader("R_{pPb}");
  lRpA_SSCEff->AddEntry(rpa_StdSSCEff, "Usual eff");
  lRpA_SSCEff->AddEntry(rpa_PlusSSCEff, "+#sigma eff");
  lRpA_SSCEff->AddEntry(rpa_MinusSSCEff, "-#sigma eff");
  

  TCanvas* cRpA_SSCEff = new TCanvas();
  rpa_StdSSCEff->Draw("e1");
  rpa_PlusSSCEff->Draw("same e1");
  rpa_MinusSSCEff->Draw("same e1");
  line->Draw("same");
  lRpA_SSCEff->Draw("same");


  //HcsEG1
  TLegend* lHcsEG1_SSCEff = new TLegend(0.6,0.7,0.85,0.85);
  lHcsEG1_SSCEff->SetHeader("p-Pb EG1 cross section");
  lHcsEG1_SSCEff->AddEntry(hcsEG1_StdSSCEff, "usual ssc eff");
  lHcsEG1_SSCEff->AddEntry(hcsEG1_PlusSSCEff, "+#sigma ssc eff");
  lHcsEG1_SSCEff->AddEntry(hcsEG1_MinusSSCEff, "-#sigma ssc eff");

  /*TCanvas* cHcsEG1_SSCEff = new TCanvas();
  cHcsEG1_SSCEff->SetLogy();
  hcsEG1_StdSSCEff->GetXaxis()->SetRangeUser(12, 60);
  hcsEG1_StdSSCEff->GetYaxis()->SetRangeUser(1, 5e3);
  hcsEG1_StdSSCEff->Draw("e1");
  hcsEG1_PlusSSCEff->Draw("samee1");
  hcsEG1_MinusSSCEff->Draw("samee1");
  lHcsEG1_SSCEff->Draw("same");//*/

  //Hcspp
  TLegend* lHcspp_SSCEff = new TLegend(0.6,0.7,0.85,0.85);
  lHcspp_SSCEff->SetHeader("pp cross section");
  lHcspp_SSCEff->AddEntry(hcspp_StdSSCEff, "usual ssc eff");
  lHcspp_SSCEff->AddEntry(hcspp_PlusSSCEff, "+#sigma ssc eff");
  lHcspp_SSCEff->AddEntry(hcspp_MinusSSCEff, "-#sigma ssc eff");

  /*TCanvas* cHcspp_SSCEff = new TCanvas();
  cHcspp_SSCEff->SetLogy();
  hcspp_StdSSCEff->GetXaxis()->SetRangeUser(12, 60);
  hcspp_StdSSCEff->Draw("e1");
  hcspp_PlusSSCEff->Draw("samee1");
  hcspp_MinusSSCEff->Draw("samee1");
  lHcspp_SSCEff->Draw("same");//*/


  TH1F* diff_pPb_SSCEff = (TH1F*)hcsEG1_MinusSSCEff->Clone("diffPlus_pPb_SSCEff");
  diff_pPb_SSCEff->SetTitle("SSC Efficiency systematic: p-Pb;E_{T} [GeV/c]; #frac{|#sigma_{eff}^{+} - #sigma_{eff}^{-}|}{2CV_{eff}}");
  //diff_pPb_SSCEff->Add(hcsEG1_PlusSSCEff, -1);
  //diff_pPb_SSCEff->Scale(0.5);
  Double_t sscSysValsPercents_pPb[8] = {0.0107384, 0.0123711, 0.0142432, 0.0132823, 0.0138755, 0.0214603, 0.00511661, 0.0688581};
  for(int i = 7; i < diff_pPb_SSCEff->GetNbinsX()+1; i++){
    diff_pPb_SSCEff->SetBinContent(i, sscSysValsPercents_pPb[i-7]);
  }
  //diff_pPb_SSCEff->Divide(hcsEG1_StdLumi);
  /*TCanvas* cdiff_pPb_SSCEff = new TCanvas("cdiff_pPb_SSCEff", "p-Pb systematic from shower shape variation in efficiency");
  diff_pPb_SSCEff->GetXaxis()->SetRangeUser(12, 60);
  //diff_pPb_SSCEff->GetYaxis()->SetRangeUser(0, 0.15);
  diff_pPb_SSCEff->Draw("hist");
  diff_pPb_SSCEff->Fit("pol1", "", "", 12, 30);//*/

  
  //pp
  TH1F* diff_pp_SSCEff = (TH1F*)hcspp_MinusSSCEff->Clone("diffPlus_pp_SSCEff");
  diff_pp_SSCEff->SetTitle("SSC Efficiency systematic: pp;E_{T} [GeV/c]; #frac{|#sigma_{eff}^{+} - #sigma_{eff}^{-}|}{2CV_{eff}} [%]");
  //diff_pp_SSCEff->Add(hcspp_PlusSSCEff, -1);
  //diff_pp_SSCEff->Scale(0.5);
  //diff_pp_SSCEff->Divide(hcspp_StdSSCEff);
  Double_t sscSysValsPercents_pp[8] = {0.0309739, 0.0142986, 0.0189007, 0.0197293, 0.0234826, 0.0640104, 0.0335424, 0.03235};
  for(int i = 7; i < diff_pPb_SSCEff->GetNbinsX()+1; i++){
    diff_pp_SSCEff->SetBinContent(i, sscSysValsPercents_pp[i-7]);
  }
  diff_pp_SSCEff->Fit("pol1", "", "", 16, 40);
  /*TCanvas* cdiff_pp_SSCEff = new TCanvas("cdiff_pp_SSCEff", "pp systematic from shower shape variation in efficiency");
  diff_pp_SSCEff->GetXaxis()->SetRangeUser(12, 60);
  //diff_pp_SSCEff->GetYaxis()->SetRangeUser(0, 0.15);
  diff_pp_SSCEff->Draw("hist");//*/

  /***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/

  //ISO Efficiency
  TFile* file_StdISOEff = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_LumiCV.root","READ");
  TH1F* rpa_StdISOEff = (TH1F*)file_StdISOEff->Get("h_RpA");rpa_StdISOEff->SetLineColor(kRed);rpa_StdISOEff->SetMarkerColor(kRed);
  TH1F* hcsEG1_StdISOEff = (TH1F*)file_StdISOEff->Get("crossSection_pPb");hcsEG1_StdISOEff->SetLineColor(kRed);hcsEG1_StdISOEff->SetMarkerColor(kRed);
  TH1F* hcspp_StdISOEff = (TH1F*)file_StdISOEff->Get("crossSection_pp");hcspp_StdISOEff->SetLineColor(kRed);hcspp_StdISOEff->SetMarkerColor(kRed);

  TFile* file_PlusISOEff = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_PlusEffISO.root","READ");
  TH1F* rpa_PlusISOEff = (TH1F*)file_PlusISOEff->Get("h_RpA");rpa_PlusISOEff->SetLineColor(kMagenta);rpa_PlusISOEff->SetMarkerColor(kMagenta);
  TH1F* hcsEG1_PlusISOEff = (TH1F*)file_PlusISOEff->Get("crossSection_pPb");hcsEG1_PlusISOEff->SetLineColor(kMagenta);hcsEG1_PlusISOEff->SetMarkerColor(kMagenta);
  TH1F* hcspp_PlusISOEff = (TH1F*)file_PlusISOEff->Get("crossSection_pp");hcspp_PlusISOEff->SetLineColor(kMagenta);hcspp_PlusISOEff->SetMarkerColor(kMagenta);

  TFile* file_MinusISOEff = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_MinusEffISO.root","READ");
  TH1F* rpa_MinusISOEff = (TH1F*)file_MinusISOEff->Get("h_RpA");rpa_MinusISOEff->SetLineColor(kBlue);rpa_MinusISOEff->SetMarkerColor(kBlue);
  TH1F* hcsEG1_MinusISOEff = (TH1F*)file_MinusISOEff->Get("crossSection_pPb");hcsEG1_MinusISOEff->SetLineColor(kBlue);hcsEG1_MinusISOEff->SetMarkerColor(kBlue);
  TH1F* hcspp_MinusISOEff = (TH1F*)file_MinusISOEff->Get("crossSection_pp");hcspp_MinusISOEff->SetLineColor(kBlue);hcspp_MinusISOEff->SetMarkerColor(kBlue);
  
  
  //RpA
  TLegend* lRpA_ISOEff = new TLegend(0.6,0.7,0.85,0.85);
  lRpA_ISOEff->SetHeader("R_{pPb}");
  lRpA_ISOEff->AddEntry(rpa_StdISOEff, "Usual eff");
  lRpA_ISOEff->AddEntry(rpa_PlusISOEff, "+#sigma eff");
  lRpA_ISOEff->AddEntry(rpa_MinusISOEff, "-#sigma eff");
  

  /*TCanvas* cRpA_ISOEff = new TCanvas();
  rpa_StdISOEff->Draw("e1");
  rpa_PlusISOEff->Draw("same e1");
  rpa_MinusISOEff->Draw("same e1");
  line->Draw("same");
  lRpA_ISOEff->Draw("same");//*/


  //HcsEG1
  TLegend* lHcsEG1_ISOEff = new TLegend(0.6,0.7,0.85,0.85);
  lHcsEG1_ISOEff->SetHeader("p-Pb EG1 cross section");
  lHcsEG1_ISOEff->AddEntry(hcsEG1_StdISOEff, "usual iso");
  lHcsEG1_ISOEff->AddEntry(hcsEG1_PlusISOEff, "+#sigma iso");
  lHcsEG1_ISOEff->AddEntry(hcsEG1_MinusISOEff, "-#sigma iso");

  TCanvas* cHcsEG1_ISOEff = new TCanvas();
  cHcsEG1_ISOEff->SetLogy();
  hcsEG1_StdISOEff->GetXaxis()->SetRangeUser(12, 60);
  hcsEG1_StdISOEff->GetYaxis()->SetRangeUser(1, 5e3);
  hcsEG1_StdISOEff->Draw("e1");
  hcsEG1_PlusISOEff->Draw("samee1");
  hcsEG1_MinusISOEff->Draw("samee1");
  lHcsEG1_ISOEff->Draw("same");//*/

  //for(int i = 1; i < 
  //Hcspp
  TLegend* lHcspp_ISOEff = new TLegend(0.6,0.7,0.85,0.85);
  lHcspp_ISOEff->SetHeader("pp cross section");
  lHcspp_ISOEff->AddEntry(hcspp_StdISOEff, "usual iso");
  lHcspp_ISOEff->AddEntry(hcspp_PlusISOEff, "+#sigma iso");
  lHcspp_ISOEff->AddEntry(hcspp_MinusISOEff, "-#sigma iso");

  TCanvas* cHcspp_ISOEff = new TCanvas();
  cHcspp_ISOEff->SetLogy();
  hcspp_StdISOEff->GetXaxis()->SetRangeUser(12, 60);
  hcspp_StdISOEff->Draw("e1");
  hcspp_PlusISOEff->Draw("samee1");
  hcspp_MinusISOEff->Draw("samee1");
  lHcspp_ISOEff->Draw("same");//*/


  TH1F* diff_pPb_ISOEff = (TH1F*)hcsEG1_MinusISOEff->Clone("diffPlus_pPb_ISOEff");
  diff_pPb_ISOEff->SetTitle("ISO systematic: p-Pb;E_{T} [GeV/c]; #frac{|#sigma_{iso < 1}^{+} - #sigma_{iso<2}^{-}|}{2CV_{eff}} [%]");
  diff_pPb_ISOEff->Add(hcsEG1_PlusISOEff, -1);
  diff_pPb_ISOEff->Scale(0.5);
  diff_pPb_ISOEff->Divide(hcsEG1_StdISOEff);
		   
  TCanvas* cdiff_pPb_ISOEff = new TCanvas("cdiff_pPb_ISOEff", "p-Pb systematic from isolation variation in efficiency");
  diff_pPb_ISOEff->GetXaxis()->SetRangeUser(12, 60);
  diff_pPb_ISOEff->GetYaxis()->SetRangeUser(0, 0.15);
  diff_pPb_ISOEff->Draw("hist");//*/

  
  //pp
  TH1F* diff_pp_ISOEff = (TH1F*)hcspp_MinusISOEff->Clone("diffPlus_pp_ISOEff");
  diff_pp_ISOEff->SetTitle("ISO systematic: pp;E_{T} [GeV/c]; #frac{|#sigma_{eff}^{+} - #sigma_{eff}^{-}|}{2CV_{eff}} [%]");
  diff_pp_ISOEff->Add(hcspp_PlusISOEff, -1);
  diff_pp_ISOEff->Scale(0.5);
  diff_pp_ISOEff->Divide(hcspp_StdISOEff);
		   
  TCanvas* cdiff_pp_ISOEff = new TCanvas("cdiff_pp_ISOEff", "pp systematic from sisolation variation in efficiency");
  diff_pp_ISOEff->GetXaxis()->SetRangeUser(12, 60);
  diff_pp_ISOEff->GetYaxis()->SetRangeUser(0, 0.15);
  diff_pp_ISOEff->Draw("hist");//*/

  //Double_t sscSysValues_pp[8] = {0.309172, 0.0947462, 0.0774654, 0.0482269, 0.0306748, 0.0345691, 0.00637156, 0.00134366};
  /*Double_t sscSysValues_pp[8] = {0.309172, 0.0947462, 0.0774654, 0.0482269, 0.0306748, 0.0345691, 0.00637156, 0.00134366};
  Double_t isoSysVals_pp[8] = {0};
  Double_t sscSysVals_pp[8] = {0};
  Double_t purSysVals_pp[8] = {0};
  Double_t lumSysVals_pp[8] = {0};
  Double_t xVals_pp[8] = {0};
  cout << "pp systematics" << endl;
  cout << "bin center" << "\t" << "value" << "\t" << "stat" << "\t" << "purity sys" << "\t" << "lumi sys" << "\t" << "iso sys" << "\t" << "totsys" << endl;
  for(int i = 7; i < diff_pp_ISOEff->GetNbinsX()+1; i++){
    cout << diff_pp_Purity->GetBinCenter(i) << "\t"
	 << hcspp_StdPurity->GetBinContent(i) << "\t"
	 << hcspp_StdPurity->GetBinError(i) << "\t"
	 << diff_pp_Purity->GetBinContent(i) << "\t"
	 << diff_pp_Lumi->GetBinContent(i) << "\t"
	 << diff_pp_ISOEff->GetBinContent(i) << "\t"
	 << TMath::Sqrt(TMath::Power( diff_pp_Purity->GetBinContent(i), 2) + TMath::Power(diff_pp_Lumi->GetBinContent(i), 2) + TMath::Power(diff_pp_ISOEff->GetBinContent(i), 2) + TMath::Power(sscSysValues_pp[i-7], 2)) << "\t"
	 << diff_pp_Purity->GetBinContent(i)/TMath::Sqrt(TMath::Power( diff_pp_Purity->GetBinContent(i), 2) + TMath::Power(diff_pp_Lumi->GetBinContent(i), 2) + TMath::Power(diff_pp_ISOEff->GetBinContent(i), 2)) << endl;

    isoSysVals_pp[i-7] = diff_pp_ISOEff->GetBinContent(i)*100.0;
    sscSysVals_pp[i-7] = sscSysValsPercents_pp[i-7]*100.0;
    purSysVals_pp[i-7] =  diff_pp_Purity->GetBinContent(i)*100.0;
    lumSysVals_pp[i-7] =  diff_pp_Lumi->GetBinContent(i)*100.0;
    xVals_pp[i-7] = diff_pp_Lumi->GetBinCenter(i);

  }

  TGraph* isoSysGraph_pp = new TGraph(8, xVals_pp, isoSysVals_pp);
  isoSysGraph_pp->SetLineColor(kRed); isoSysGraph_pp->SetMarkerStyle(kOpenCircle);isoSysGraph_pp->GetXaxis()->SetRangeUser(12,60); isoSysGraph_pp->GetYaxis()->SetRangeUser(0,50); isoSysGraph_pp->SetTitle(";E_{T} [GeV]; Cross section systematic uncertainty [%]");
  TGraph* sscSysGraph_pp = new TGraph(8, xVals_pp, sscSysVals_pp);
  sscSysGraph_pp->SetLineColor(kBlack); sscSysGraph_pp->SetMarkerStyle(kOpenSquare);sscSysGraph_pp->GetXaxis()->SetRangeUser(12,60); sscSysGraph_pp->GetYaxis()->SetRangeUser(0,0.5);
  TGraph* purSysGraph_pp = new TGraph(8, xVals_pp, purSysVals_pp);
  purSysGraph_pp->SetLineColor(kBlue); purSysGraph_pp->SetMarkerStyle(kOpenDiamond);purSysGraph_pp->GetXaxis()->SetRangeUser(12,60); purSysGraph_pp->GetYaxis()->SetRangeUser(0,0.5);
  TGraph* lumSysGraph_pp = new TGraph(8, xVals_pp, lumSysVals_pp);
  lumSysGraph_pp->SetLineColor(kMagenta); lumSysGraph_pp->SetMarkerStyle(kStar);lumSysGraph_pp->GetXaxis()->SetRangeUser(12,60); lumSysGraph_pp->GetYaxis()->SetRangeUser(0,0.5);
  lumSysGraph_pp->SetTitle(";E_{T} [GeV]; sys. unc.");

  TLegend* lSys_pp = new TLegend(0.12, 0.6, 0.87, 0.87);
  lSys_pp->SetHeader("ALICE, pp #sqrt{s_{NN}} = 5.02 TeV");
  lSys_pp->AddEntry(isoSysGraph_pp, "Isolation Cut");
  lSys_pp->AddEntry(sscSysGraph_pp, "Shower shape cut");
  lSys_pp->AddEntry(lumSysGraph_pp, "Luminosity");
  lSys_pp->AddEntry(purSysGraph_pp, "Purity");

  TCanvas* cSys_pp = new TCanvas("cSys_pp", "", 600, 600);
  //isoSysGraph_pp->Draw("apl");
  sscSysGraph_pp->Draw("apl");
  //purSysGraph_pp->Draw("plsame");
  //lumSysGraph_pp->Draw("plpsame");
  //lSys_pp->Draw("same");
  //cSys_pp->SaveAs("sysUnc_pp.pdf");
  
  Double_t sscSysValues_pPb[8] = {20.8317, 15.958, 11.8504, 7.1064, 3.99393, 2.80683, 0.252268, 0.605229};
  //sscSysValsPercents_pPb = {0.0107384, 0.0123711, 0.0142432, 0.0132823, 0.0138755, 0.0214603, 0.024415355, 0.033871820};
  Double_t isoSysVals_pPb[8] = {0};
  Double_t sscSysVals_pPb[8] = {0};
  Double_t purSysVals_pPb[8] = {0};
  Double_t lumSysVals_pPb[8] = {0};
  Double_t xVals_pPb[8] = {0};
  cout << "pPb systematics" << endl;
  cout << "bin center" << "\t" << "value" << "\t" << "stat" << "\t" << "purity sys" << "\t" << "lumi sys" << "\t" << "iso sys" << "\t" << "totsys" << endl;
  for(int i = 7; i < diff_pPb_ISOEff->GetNbinsX()+1; i++){
    cout << diff_pPb_Purity->GetBinCenter(i) << "\t"
	 << hcsEG1_StdPurity->GetBinContent(i) << "\t"
	 << hcsEG1_StdPurity->GetBinError(i) << "\t"
	 << diff_pPb_Purity->GetBinContent(i) << "\t"
	 << diff_pPb_Lumi->GetBinContent(i) << "\t"
	 << diff_pPb_ISOEff->GetBinContent(i) << "\t"
	 << TMath::Sqrt(TMath::Power( diff_pPb_Purity->GetBinContent(i), 2) + TMath::Power(diff_pPb_Lumi->GetBinContent(i), 2) + TMath::Power(diff_pPb_ISOEff->GetBinContent(i), 2) + TMath::Power(sscSysValues_pPb[i-7], 2)) << "\t"
	 << diff_pPb_Purity->GetBinContent(i)/TMath::Sqrt(TMath::Power( diff_pPb_Purity->GetBinContent(i), 2) + TMath::Power(diff_pPb_Lumi->GetBinContent(i), 2) + TMath::Power(diff_pPb_ISOEff->GetBinContent(i), 2)) << endl;

    isoSysVals_pPb[i-7] = diff_pPb_ISOEff->GetBinContent(i)*100.0;
    sscSysVals_pPb[i-7] = sscSysValsPercents_pPb[i-7]*100.0;
    purSysVals_pPb[i-7] =  diff_pPb_Purity->GetBinContent(i)*100.0;
    lumSysVals_pPb[i-7] =  0.060484361*100;//diff_pPb_Lumi->GetBinContent(i)*100.0;
    xVals_pPb[i-7] = diff_pPb_Lumi->GetBinCenter(i);
      
  }

  TGraph* isoSysGraph_pPb = new TGraph(8, xVals_pPb, isoSysVals_pPb);
  isoSysGraph_pPb->SetLineColor(kRed); isoSysGraph_pPb->SetMarkerStyle(kOpenCircle);isoSysGraph_pPb->GetXaxis()->SetRangeUser(12,60); isoSysGraph_pPb->GetYaxis()->SetRangeUser(0,50); isoSysGraph_pPb->SetTitle(";E_{T} [GeV]; Cross section systematic uncertainty [%]");
  TGraph* sscSysGraph_pPb = new TGraph(8, xVals_pPb, sscSysVals_pPb);
  sscSysGraph_pPb->SetLineColor(kBlack); sscSysGraph_pPb->SetMarkerStyle(kOpenSquare);sscSysGraph_pPb->GetXaxis()->SetRangeUser(12,60); sscSysGraph_pPb->GetYaxis()->SetRangeUser(0,0.5);
  TGraph* purSysGraph_pPb = new TGraph(8, xVals_pPb, purSysVals_pPb);
  purSysGraph_pPb->SetLineColor(kBlue); purSysGraph_pPb->SetMarkerStyle(kOpenDiamond);purSysGraph_pPb->GetXaxis()->SetRangeUser(12,60); purSysGraph_pPb->GetYaxis()->SetRangeUser(0,0.5);
  TGraph* lumSysGraph_pPb = new TGraph(8, xVals_pPb, lumSysVals_pPb);
  lumSysGraph_pPb->SetLineColor(kMagenta); lumSysGraph_pPb->SetMarkerStyle(kStar);lumSysGraph_pPb->GetXaxis()->SetRangeUser(12,60); lumSysGraph_pPb->GetYaxis()->SetRangeUser(0,0.5);
  lumSysGraph_pPb->SetTitle(";E_{T} [GeV]; sys. unc.");

  TLegend* lSys_pPb = new TLegend(0.12, 0.6, 0.87, 0.87);
  lSys_pPb->SetHeader("ALICE, p-Pb #sqrt{s_{NN}} = 5.02 TeV");
  lSys_pPb->AddEntry(isoSysGraph_pPb, "Isolation Cut");
  lSys_pPb->AddEntry(sscSysGraph_pPb, "Shower shape cut");
  lSys_pPb->AddEntry(lumSysGraph_pPb, "Luminosity");
  lSys_pPb->AddEntry(purSysGraph_pPb, "Purity");

  TCanvas* cSys_pPb = new TCanvas("cSys_pPb", "", 600, 600);
  isoSysGraph_pPb->Draw("apl");
  sscSysGraph_pPb->Draw("plsame");
  purSysGraph_pPb->Draw("plsame");
  lumSysGraph_pPb->Draw("plpsame");
  lSys_pPb->Draw("same");
  //cSys_pPb->SaveAs("sysUnc_pPb.pdf");

  
  /*cout << "Double_t xVals[8] = {";
  for(int i = 0; i < 8; i++){
    cout << xVals_pPb[i] << ", ";
  }
  cout << "}" << endl;
  cout << "Double_t sscSysValsPercents_pPb[8] = {";
  for(int i = 0; i < 8; i++){
    cout << sscSysValsPercents_pPb[i] << ", ";
  }
  cout << "}" << endl;

  cout << "Double_t sscSysValsPercents_pp[8] = {";
  for(int i = 0; i < 8; i++){
    cout << sscSysValsPercents_pPb[i] << ", ";
  }
  cout << "}" << endl;//*/

  //Purity systematic
  TFile* file_wCT = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PurityFit_results.root","READ");
  TH1F* rpa_wCT = (TH1F*)file_wCT->Get("h_RpA");rpa_wCT->SetLineColor(kRed);rpa_wCT->SetMarkerColor(kRed);
  TH1F* hcsEG1_wCT = (TH1F*)file_wCT->Get("crossSection_EG1");hcsEG1_wCT->SetLineColor(kRed);hcsEG1_wCT->SetMarkerColor(kRed);
  TH1F* hcspp_wCT = (TH1F*)file_wCT->Get("crossSection_pp");hcspp_wCT->SetLineColor(kRed);hcspp_wCT->SetMarkerColor(kRed);

  TFile* file_woCT = new TFile("/global/homes/d/ddixit/photonCrossSection/xSectionHists/StdCuts_EX0PurityFit_woCrossTalk.root","READ");
  TH1F* rpa_woCT = (TH1F*)file_woCT->Get("h_RpA");rpa_woCT->SetLineColor(kMagenta);rpa_woCT->SetMarkerColor(kMagenta);
  TH1F* hcsEG1_woCT = (TH1F*)file_woCT->Get("crossSection_EG1");hcsEG1_woCT->SetLineColor(kMagenta);hcsEG1_woCT->SetMarkerColor(kMagenta);
  TH1F* hcspp_woCT = (TH1F*)file_woCT->Get("crossSection_pp");hcspp_woCT->SetLineColor(kMagenta);hcspp_woCT->SetMarkerColor(kMagenta);

  TCanvas* cCT = new TCanvas("cCT", "cCT");
  cCT->SetLogy();
  hcsEG1_wCT->GetYaxis()->SetRangeUser(1, 1e4);
  hcsEG1_wCT->Draw();
  hcsEG1_woCT->Draw("same");

  TLegend* lCT = new TLegend(0.6, 0.6, 0.85, 0.85);
  lCT->AddEntry(hcsEG1_wCT, "with cross talk");
  lCT->AddEntry(hcsEG1_woCT, "without cross talk");
  lCT->Draw("same");

  TH1F* hSysCT = (TH1F*)hcsEG1_wCT->Clone("hSysCT");
  hSysCT->SetTitle(";E_{T} [GeV]; Sys Error [%]");
  hSysCT->GetYaxis()->SetRangeUser(0, 100);
  for(int i = 1; i < hSysCT->GetNbinsX()+1; i++){
    double content = TMath::Abs(hcsEG1_wCT->GetBinContent(i) - hcsEG1_woCT->GetBinContent(i));
    double sysCT = content*0.5*100/hcsEG1_wCT->GetBinContent(i);
    cout << sysCT << endl;
    hSysCT->SetBinContent(i, sysCT);
  }
  
  TCanvas* cSysCT = new TCanvas("cSysCT", "cSysCT");
  hSysCT->Draw("hist");

  
}//end makeComparisons
