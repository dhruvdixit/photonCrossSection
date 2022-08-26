#ifndef StylingUtilities
#define StylingUtilities

#include "TLatex.h"

/*
 * AdjustPaletteSize: reduce the palette width in 2D histograms
 */
void AdjustPaletteSize (
			 TH2     * histogram/*,
					      Float_t   label_offset*/
			) {

  gPad->Update();
  TPaletteAxis *palette = (TPaletteAxis*)histogram->GetListOfFunctions()->FindObject("palette");
  palette->SetX1NDC(1-gPad->GetRightMargin()+0.005);
  palette->SetX2NDC(1-gPad->GetRightMargin()+0.04);
  palette->SetY1NDC(gPad->GetBottomMargin());
  palette->SetY2NDC(1-gPad->GetTopMargin());
  /* palette->SetLabelOffset(label_offset); */
  gPad->Modified();

}

/*
 * AutoZoomY: set a y-axis autozoom for one graph
 */
void AutoZoomGraphY (
		      TH1      * frame,
		      TGraph   * graph,
		      Double_t   scale_factor
		     ) {

  Double_t min    = TMath::MinElement(graph->GetN(), graph->GetY());
  Double_t max    = TMath::MaxElement(graph->GetN(), graph->GetY());
  Double_t offset = 30.*((max - min)/(100.*scale_factor));

  if(min != -max){
    frame->SetMinimum(TMath::Max(0., min-offset));
    frame->SetMaximum(max + 2.*offset);
    // frame->GetYaxis()->SetRangeUser(TMath::Max(0., min-offset), max + 2.*offset);
  }

}

/*
 * AutoZoomGraphYMax: compute a y-axis autozoom max for one graph
 */
Double_t AutoZoomGraphYMax (
			     TH1      * frame,
			     TGraph   * graph,
			     Double_t   scale_factor
			    ) {

  Double_t min    = TMath::MinElement(graph->GetN(), graph->GetY());
  Double_t max    = TMath::MaxElement(graph->GetN(), graph->GetY());
  Double_t offset = 30.*((max - min)/(100.*scale_factor));

  return max + 2.*offset;

}

/*
 * AutoZoomGraphYMin: compute a y-axis autozoom min for one graph
 */
Double_t AutoZoomGraphYMin (
			     TH1      * frame,
			     TGraph   * graph,
			     Double_t   scale_factor
			    ) {

  Double_t min    = TMath::MinElement(graph->GetN(), graph->GetY());
  Double_t max    = TMath::MaxElement(graph->GetN(), graph->GetY());
  Double_t offset = 30.*((max - min)/(100.*scale_factor));

  if(min != -max){
    // frame->SetMinimum(TMath::Max(0., min-offset));
    // frame->SetMaximum(max + 2.*offset);
    frame->GetYaxis()->SetRangeUser(TMath::Max(0., min-offset), max + 2.*offset);
  }

  return TMath::Max(0., min-offset);

}

/*
 * AutoZoomY: set a y-axis autozoom for one histogram
 */
void AutoZoomHistogramY (
			  TH1      * frame,
			  TH1      * histo,
			  Double_t   scale_factor
			 ) {

  Double_t min    = histo->GetMinimum();
  Double_t max    = histo->GetMaximum();
  Double_t offset = 30.*((max - min)/(100.*scale_factor));

  if(min != -max){
    frame->SetMinimum(TMath::Max(0., min-offset));
    frame->SetMaximum(max + 2.*offset);
  }

}

/*
 * CentredYBoundary: returns the maximal value to set a y-axis range optimally
 */
Double_t CentredYBoundary (
			    TH1 * histo1,
			    TH1 * histo2,
			    TH1 * histo3
			   ) {

  Double_t min = 0., max = 0.;

  min = TMath::Max(TMath::Max(TMath::Abs(histo1->GetMinimum()), TMath::Abs(histo2->GetMinimum())), TMath::Abs(histo3->GetMinimum()));
  max = TMath::Max(TMath::Max(TMath::Abs(histo1->GetMaximum()), TMath::Abs(histo2->GetMaximum())), TMath::Abs(histo3->GetMaximum()));

  return TMath::Max(min, max)*1.25;

}

/*
 * ComputeCumulativeDistribution: compute the cumulative distribution of an histogram
 */
TH1 * ComputeCumulativeDistribution (
				      TH1 * histo
				     ) {

  TH1F * histo_cumulative = (TH1F *)histo->Clone("histo_cumulative"); histo_cumulative->Reset();

  for ( Int_t bin = 0; bin < histo->GetNbinsX(); bin ++ ) {
    histo_cumulative->SetBinContent(bin, histo->Integral(0, bin));
  }

  histo_cumulative->Scale(1./histo_cumulative->GetMaximum());

  return histo_cumulative;

}

/*
 * ComputeRatio: compute the ratio of two graphs
 */
void ComputeRatio (
		    TGraph * var_graph,
		    TGraph * std_graph,
		    TH1    * rel_diff,
		    Double_t mean [],
		    Double_t stat []
		   ) {

  TH1F * var_histo = rel_diff->Clone("var_histo");
  TH1F * std_histo = rel_diff->Clone("std_histo");

  TransformGraphIntoHistogram(std_graph, std_histo); std_histo->Sumw2();
  TransformGraphIntoHistogram(var_graph, var_histo); var_histo->Sumw2();

  rel_diff->Divide(var_histo, std_histo, 1., 1., "B"); rel_diff->Sumw2();

  for ( Int_t bin = 0; bin < rel_diff->GetNbinsX(); bin ++ ) {
    mean[bin] = rel_diff->GetBinContent(bin+1);
    stat[bin] = rel_diff->GetBinError(bin+1);
  }

  delete std_histo; delete var_histo;

}

/*
 * ComputeRelativeDifference: compute the relative difference between two graphs
 */
void ComputeRelativeDifference (
				 TGraph * var_graph,
				 TGraph * std_graph,
				 TH1    * rel_diff,
				 Double_t mean [],
				 Double_t stat []
				) {

  TH1F * var_histo = rel_diff->Clone("var_histo");
  TH1F * std_histo = rel_diff->Clone("std_histo");
  TF1  * cst       = new TF1 ("cst", "pol0", 10., 60.); cst->SetParameter(0, 1.);

  TransformGraphIntoHistogram(std_graph, std_histo); std_histo->Sumw2();
  TransformGraphIntoHistogram(var_graph, var_histo); var_histo->Sumw2();

  rel_diff->Divide(var_histo, std_histo, 1., 1., "B"); rel_diff->Sumw2();
  rel_diff->Add(cst, -1.);                             rel_diff->Sumw2();
  rel_diff->Multiply(cst, 100.);                       rel_diff->Sumw2();

  for ( Int_t bin = 0; bin < rel_diff->GetNbinsX(); bin ++ ) {
    mean[bin] = rel_diff->GetBinContent(bin+1);
    stat[bin] = rel_diff->GetBinError(bin+1);
  }

  delete std_histo; delete var_histo; delete cst;

}

/*
 * CreateCanvas: set the appropriate size, margins and title offset according to the chosen format
 */
TCanvas * CreateCanvas (
			 TString name,
			 TString format,
			 Int_t   yndiv
			) {

  Int_t width = 0, height = 0;

  if ( format == "square" ) {
    gStyle->SetPadLeftMargin(0.126);   // 0.14
    gStyle->SetPadRightMargin(0.005);  // 0.018
    gStyle->SetPadBottomMargin(0.089); // 0.11
    gStyle->SetPadTopMargin(0.017);    // 0.022
    gStyle->SetTitleOffset(1.1, "x");  // 1.4
    gStyle->SetTitleOffset(1.7, "y");  // 1.9
    width = 800; height = width;
  }
  else if ( format == "landscape" ) {
    gStyle->SetPadLeftMargin(0.126);   // 0.14
    gStyle->SetPadRightMargin(0.005);  // 0.018
    gStyle->SetPadBottomMargin(0.121); // 0.15
    gStyle->SetPadTopMargin(0.022);    // 0.029
    gStyle->SetTitleOffset(1.1, "x");  // 1.1
    gStyle->SetTitleOffset(1.26, "y"); // 1.9
    width = 800; height = 600;
  }
  else if ( format == "portrait" ) {
    gStyle->SetPadLeftMargin(0.165);
    gStyle->SetPadRightMargin(0.005);
    gStyle->SetPadBottomMargin(0.089);
    gStyle->SetPadTopMargin(0.017);
    gStyle->SetTitleOffset(1.1, "x");
    gStyle->SetTitleOffset(2.22, "y"); //2.6
    width = 600; height = 800;
  }

  gStyle->SetNdivisions(yndiv, "y");

  TCanvas * canvas = new TCanvas(name, "", 0, 0, width, height);

  return canvas;

}

/*
 * CreateSplitCanvas: create a canvas with two pads according to the chosen split Y
 */
TCanvas * CreateSplitCanvas (
			      TString     name,
			      TString     format,
			      TPad     ** pad,
			      Double_t    split,
			      Int_t       yndiv_top,
			      Int_t       yndiv_bottom
			     ) {

  TCanvas * canvas = CreateCanvas(name, format, yndiv_top);

  gStyle->SetPadTopMargin(0.025);
  gStyle->SetTitleOffset(3.6,"x");

  pad[0] = new TPad(Form("%s_top", name.Data()), "", 0., split, 1., 1.);
  pad[0]->SetBottomMargin(0.025);

  pad[1] = new TPad(Form("%s_bottom", name.Data()), "", 0., 0., 1., split);
  pad[1]->SetTopMargin(0.035); pad[1]->SetBottomMargin(0.29);

  return canvas;

}

/*
 * DrawHorizontalLine: draw a horizontal line from bottom to top of a frame
 */
void DrawHorizontalLine (
			  Double_t y,
			  Color_t  colour,
			  Width_t  width,
			  Style_t  style
			 ) {

  gPad->Update();

  TLine l; Double_t lm = gPad->GetLeftMargin(), rm = 1.-gPad->GetRightMargin(), tm = 1.-gPad->GetTopMargin(), bm = gPad->GetBottomMargin(), yndc = (tm-bm)*((y-gPad->GetUymin())/(gPad->GetUymax()-gPad->GetUymin()))+bm;
  l.SetLineColor(colour); l.SetLineStyle(style); l.SetLineWidth(width); l.DrawLineNDC(lm,yndc,rm,yndc);

}

/*
 * DrawLogo: draw a logo
 */
void DrawLogo (
	        TString    text,
		Short_t    align,
		Double_t   xmin,
		Double_t   ymin,
		TCanvas  * canvas,
		Short_t    size = 28 // Last argument for backward compatibility
	       ) {

  UInt_t width  = canvas->GetWindowWidth();
  UInt_t height = canvas->GetWindowHeight();

  if(width > height)
    Double_t factor = ((Double_t) width)/((Double_t) height);
  else
    Double_t factor = ((Double_t) height)/((Double_t) width);

  TLatex * tex = new TLatex(xmin, ymin, Form("%s", text.Data()));
  tex->SetNDC();
  tex->SetTextAlign(align);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->Draw();

}

/*
 * DrawLogoTwoLines: draw a logo
 */
void DrawLogoTwoLines (
		        TString    text1,
			TString    text2,
			Float_t    size2,
			Short_t    align,
			Double_t   xmin,
			Double_t   ymin,
			Double_t   ysep,
			TCanvas  * canvas
		       ) {

  UInt_t width  = canvas->GetWindowWidth();
  UInt_t height = canvas->GetWindowHeight();

  if(width > height)
    Double_t factor = ((Double_t) width)/((Double_t) height);
  else
    Double_t factor = ((Double_t) height)/((Double_t) width);

  TLatex * tex1 = new TLatex(xmin, ymin, Form("%s", text1.Data()));
  tex1->SetNDC();
  tex1->SetTextAlign(align);
  tex1->SetTextFont(43);
  tex1->SetTextSize(28);
  tex1->Draw();

  TLatex * tex2 = new TLatex(xmin, ymin-ysep, Form("%s", text2.Data()));
  tex2->SetNDC();
  tex2->SetTextAlign(align);
  tex2->SetTextFont(43);
  tex2->SetTextSize(size2);
  tex2->Draw();

}

/*
 * DrawVerticalLine: draw a vertical line from bottom to top of a frame
 */
void DrawVerticalLine (
		        Double_t x,
			Color_t  colour,
			Width_t  width,
			Style_t  style
		       ) {

  gPad->Update();

  TLine l; Double_t lm = gPad->GetLeftMargin(), rm = 1.-gPad->GetRightMargin(), tm = 1.-gPad->GetTopMargin(), bm = gPad->GetBottomMargin(), xndc = (rm-lm)*((x-gPad->GetUxmin())/(gPad->GetUxmax()-gPad->GetUxmin()))+lm;
  l.SetLineColor(colour); l.SetLineStyle(style); l.SetLineWidth(width); l.DrawLineNDC(xndc,bm,xndc,tm);

}

/*
 * MaxYaxisRatio: returns the maximal value to set a y-axis range optimally
 */
Double_t MaxYaxisRatio (
		 	 TH1 * histo1,
			 TH1 * histo2,
			 TH1 * histo3
			) {

  return CentredYBoundary(histo1, histo2, histo3);

}

/*
 * MinYaxisRatio: returns the minimal value to set a y-axis range optimally
 */
Double_t MinYaxisRatio (
			 TH1 * histo1,
			 TH1 * histo2,
			 TH1 * histo3
			) {

  return -CentredYBoundary(histo1, histo2, histo3);
  // return -TMath::Min(1., CentredYBoundary(histo1, histo2, histo3));

}

/*
 * SaveCanvasInMultipleFormats: save a canvas in different formats in different sub-directories
 */
void SaveCanvasInMultipleFormats (
				   TCanvas * canvas,
				   TString   name,
				   TString   dir = ""
				  ) {

  if ( !dir.IsNull() ) dir += "/";

  gSystem->Exec(Form("mkdir -p %sC", dir.Data()));    canvas->SaveAs(Form("%sC/%s.C"      , dir.Data(), name.Data()));
  gSystem->Exec(Form("mkdir -p %sEPS", dir.Data()));  canvas->SaveAs(Form("%sEPS/%s.eps"  , dir.Data(), name.Data()));
  gSystem->Exec(Form("mkdir -p %sPDF", dir.Data()));  canvas->SaveAs(Form("%sPDF/%s.pdf"  , dir.Data(), name.Data()));
  gSystem->Exec(Form("mkdir -p %sROOT", dir.Data())); canvas->SaveAs(Form("%sROOT/%s.root", dir.Data(), name.Data()));

}

/*
 * SetGeneralStyle: set the main style properties
 */
void SetGeneralStyle ( ) {

  ////////////// General //////////////
  gROOT->SetStyle("Plain");
  gStyle->SetFillColor(0); gStyle->SetFrameFillColor(0); gStyle->SetFillStyle(0);
  /* canvas->SetFillColor(0); canvas->SetFrameFillColor(0); */

  gStyle->SetPadLeftMargin(0.126); gStyle->SetPadRightMargin(0.005); gStyle->SetPadBottomMargin(0.089); gStyle->SetPadTopMargin(0.017);

  Style_t font             = 43; // Helvetica regular
  Float_t font_size_prim   = 28;
  Float_t font_size_labels = (.06/.065)*font_size_prim; // Values from PCG soft
  Width_t line_width       = 1;

  ///////// Plot title /////////
  gStyle->SetTitleFont(font, "t"); gStyle->SetTitleFontSize(font_size_prim); gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleW(0.75); gStyle->SetTitleH(0.05);
  gStyle->SetTitleX(0.1f); gStyle->SetTitleY(0.985f);

  ////////// Axis titles //////////
  gStyle->SetTitleFont(font, "xyz");
  gStyle->SetTitleXSize(font_size_prim); gStyle->SetTitleYSize(font_size_prim);
  gStyle->SetTitleOffset(1.1, "xz"); gStyle->SetTitleOffset(1.7, "y");

  ///////// Labels/ticks /////////
  TGaxis::SetMaxDigits(3); TGaxis::SetExponentOffset(0, 0.005, "y");
  gStyle->SetLabelFont(font, "xyz"); gStyle->SetLabelSize(font_size_labels, "xyz"); gStyle->SetLabelOffset(0.005, "xyz");

  gStyle->SetNdivisions(506, "x"); gStyle->SetNdivisions(505, "y");
  gStyle->SetPadTickX(1); gStyle->SetPadTickY(1); gStyle->SetTickLength(0.03, "xyz");

  ////////////////// Stats/fit //////////////////
  gStyle->SetStatFont(font); gStyle->SetStatFontSize(24);
  gStyle->SetStatX(1-gStyle->GetPadRightMargin()); gStyle->SetStatY(1-gStyle->GetPadTopMargin());

  ///// STATS
  gStyle->SetStatW(0.22); gStyle->SetStatH(0.075);
  gStyle->SetOptStat(0);         // Entries, mean and RMS with errors, integral
  gStyle->SetStatFormat("4.3f"); // 4 numbers and 4 digits in float mode
  ///// FIT
  gStyle->SetStatW(0.17); gStyle->SetStatH(0.1);
  gStyle->SetOptFit(0);
  gStyle->SetFitFormat("4.3f");

  ////////// Drawing options //////////
  gStyle->SetLineWidth(line_width); gStyle->SetFuncWidth(line_width);
  gStyle->SetHistLineWidth(line_width); gStyle->SetHistLineColor(kBlack);
  gStyle->SetEndErrorSize(0); // gStyle->SetErrorX(0.);

  ////////// Legend //////////
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(0);
  gStyle->SetLegendFont(font);

  gROOT->ForceStyle(kTRUE);

  ////////// 2D histograms //////////
  const Int_t NRGBs = 5, NCont = 255;

  Double_t stops [NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red   [NRGBs] = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green [NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue  [NRGBs] = { 0.51, 1.00, 0.12, 0.00, 0.00 };

  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

}

/*
 * SetGraphAestheticsAndDraw: set graph aesthetics properties
 */
void SetGraphAestheticsAndDraw (
				 TGraph   * graph,
				 Color_t    color,
				 Style_t    marker,
				 Size_t     size,
				 Option_t * draw_option,
				 Width_t    width = 1.,    // Second-to-last argument for backward compatibility
				 Style_t    fill = 0       // Last argument for backward compatibility
				) {

  if      ( marker == 27 || marker == 33 || marker == 29 ) // 27 = open diamond, 33 = full diamond, 29 = full star
    size *= 1.4;
  else if ( marker == 28 || marker == 34 || marker == 30 ) // 28 = open cross, 34 = full cross, 30 = open star
    size *= 1.2;

  graph->SetMarkerStyle(marker);
  graph->SetMarkerSize(size);
  graph->SetMarkerColor(color);
  graph->SetFillStyle(fill);
  graph->SetFillColor(color);
  graph->SetLineWidth(width);
  graph->SetLineColor(color);
  graph->Draw(draw_option);

}

/*
 * SetHistogramAestheticsAndDraw: set histogram aesthetics properties
 */
void SetHistogramAestheticsAndDraw (
				     TH1      * histo,
				     Color_t    color,
				     Style_t    marker,
				     Size_t     size,
				     Option_t * draw_option,
				     Width_t    width = 1., // Second-to-last argument for backward compatibility
				     Style_t    fill = 0    // Last argument for backward compatibility
				    ) {

  if      ( marker == 27 || marker == 33 || marker == 29 )  // 27 = open diamond, 33 = full diamond, 29 = full star
    size *= 1.4;
  else if ( marker == 28 || marker == 34 || marker == 30 )  // 28 = open cross, 34 = full cross, 30 = open star
    size *= 1.2;

  histo->SetMarkerStyle(marker);
  histo->SetMarkerSize(size);
  histo->SetMarkerColor(color);
  histo->SetFillStyle(fill);
  histo->SetFillColor(color);
  histo->SetLineWidth(width);
  histo->SetLineColor(color);
  histo->Draw(draw_option);

}

/*
 * TransformGraphIntoHistogram: transform a graph in a histogram
 */
void TransformGraphIntoHistogram (
				   TGraph * graph,
				   TH1 * histo
				  ) {

  Double_t energy = 0., mean = 0., error = 0.;

  for ( Int_t bin = 0; bin < graph->GetN(); bin ++ ) {
    graph->GetPoint(bin, energy, mean);
    error = graph->GetErrorY(bin);
    histo->SetBinContent(bin+1, mean);
    histo->SetBinError(bin+1, error);
  }

}

/*
 * TransformHistogramIntoGraph: transform a graph in a histogram
 */
void TransformHistogramIntoGraph (
				   TH1          * histo,
				   TGraphErrors * graph
				  ) {

  Double_t energy = 0., width = 0., mean = 0., error = 0.;

  for ( Int_t bin = 1; bin <= histo->GetNbinsX(); bin ++ ) {
    energy = histo->GetBinCenter(bin);
    width  = (histo->GetBinWidth(bin))/2.;
    mean   = histo->GetBinContent(bin);
    error  = histo->GetBinError(bin);
    graph->SetPoint     (bin, energy, mean);
    graph->SetPointError(bin, width , error);
  }

}

#endif
