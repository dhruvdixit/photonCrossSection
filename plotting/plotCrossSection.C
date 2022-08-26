#include "Macro_utility_functions/StylingUtilities.h"

// Double_t power_law(Double_t *x, Double_t *par)
// {
//   return par[0]/TMath::Power(x[0], par[1]);
// }

void c3_CrossSection_ForSystematicUncertainty(Bool_t crosstalk_emulation, Double_t gamma_jet_weight, TString sigma_long_sig_shift, TString sigma_long_bkg_shift, Double_t anti_isolation, Double_t alpha_calibration_slope, Bool_t no_smearing, TString CPV, Bool_t pileup_rej, Int_t nlm, TString period, TString acceptance, Int_t UEMet) {

  cout << ">>> Inside c3_CrossSection_ForSystematicUncertainty <<<" << endl;

  TString  logo_text         = "ALICE, pp #sqrt{#it{s}} = 7 TeV

  const int nPtBins    = 9;
  Double_t  PtBound    [nPtBins+1] = {10., 12. , 14. , 16.  , 18. , 20. , 25. , 30. , 40., 60.};
  Double_t  PtBin      [nPtBins]   = {11., 13. , 15. , 17.  , 19. , 22.5, 27.5, 35. , 50.     };
  Double_t  PtBinErr   [nPtBins]   = { 1.,  1. ,  1. ,  1.  ,  1. ,  2.5,  2.5,  5. , 10.     };

  // Input

  // Output
  Double_t  cross_section_mean [nPtBins], cross_section_stat_error [nPtBins]; TGraphErrors * cross_section = new TGraphErrors(nPtBins);
  TString   output_name        = "cross_section";
  ofstream  points_mean        (Form("POINTS/%s_mean.txt"      , output_name.Data()));
  ofstream  points_stat_error  (Form("POINTS/%s_stat_error.txt", output_name.Data()));




  // **************************************************************************
  // *                                                                        *
  // *                        CROSS SECTION PLOTTING                          *
  // *                                                                        *
  // **************************************************************************

  SetGeneralStyle();

  TCanvas *c_cross_section = CreateCanvas("c_cross_section", "square", 510); //new TCanvas("c_cross_section", "SumPtUE",0,0,800,800);
  c_cross_section->SetFrameFillColor(10);
  c_cross_section->cd(); gPad->SetLogy();

  TH1* c_cross_section_frame = gPad->DrawFrame(8., 2.e-2, 62., 90., ";#it{p}_{T} (GeV/#it{c});d^{2}#sigma/d#it{p}_{T}d#it{#eta} (nb GeV^{-1}#it{c})");

  SetGraphAestheticsAndDraw(cross_section, kCyan+2, kFullCircle, 1.1, "EPsame");

  // TF1 *cross_section_power_law = new TF1("cross_section_power_law", power_law, 10., 60., 2);
  // cross_section_power_law->SetLineWidth(2);
  // // cross_section_power_law->FixParameter(0, 1.); // Double_t param[3] = {0., -0.1, 1.}; // cross_section_power_law->SetParameters(param);
  // cross_section->Fit(cross_section_power_law, "R");

  // TF1 *cross_section_expo = new TF1("cross_section_expo", "expo", 10., 40.);
  // cross_section_expo->SetLineWidth(2);
  // cross_section_expo->SetLineColor(kRed+2);
  // // cross_section_expo->FixParameter(0, 1.); // Double_t param[3] = {0., -0.1, 1.}; // cross_section_expo->SetParameters(param);
  // cross_section->Fit(cross_section_expo, "R+");

  TLegend *c_cross_section_legend = new TLegend(0.53, 0.85, 0.88, 0.89);
  c_cross_section_legend->SetTextSize(23);
  c_cross_section_legend->SetMargin(0.25);
  c_cross_section_legend->AddEntry(cross_section, "Data + statistical uncertainty", "lp");
  // c_cross_section_legend->AddEntry(cross_section_power_law, Form("#it{m}/#it{p}_{T}^{#it{n}}, #it{m} = %.3f, #it{n} = %.3f", cross_section_power_law->GetParameter(0), cross_section_power_law->GetParameter(1)), "lp");
  // c_cross_section_legend->AddEntry(cross_section_expo, Form("exp(#it{m} + #it{n} #times #it{p}_{T}), #it{m} = %.3f, #it{n} = %.3f", cross_section_expo->GetParameter(0), cross_section_expo->GetParameter(1)), "lp");
  c_cross_section_legend->Draw("same");

  DrawLogo(logo_text, 11, 0.54, 1.-gPad->GetTopMargin()-0.07, c_cross_section);

  gPad->RedrawAxis();

  // Saving canvases
  SaveCanvasInMultipleFormats(c_cross_section, output_name);

  // Closing things
  c_cross_section->Close();

  delete c_cross_section;
  delete cross_section;
  delete input;
}
