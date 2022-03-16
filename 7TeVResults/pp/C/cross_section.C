{
//=========Macro generated from canvas: c_final_cross_section/
//=========  (Wed May 29 06:56:12 2019) by ROOT version5.34/30
   TCanvas *c_final_cross_section = new TCanvas("c_final_cross_section", "",0,0,800,800);
   gStyle->SetOptStat(0);
   c_final_cross_section->SetHighLightColor(2);
   c_final_cross_section->Range(0.1703107,-2.045126,62.3107,1.844271);
   c_final_cross_section->SetFillColor(0);
   c_final_cross_section->SetBorderMode(0);
   c_final_cross_section->SetBorderSize(2);
   c_final_cross_section->SetLogy();
   c_final_cross_section->SetTickx(1);
   c_final_cross_section->SetTicky(1);
   c_final_cross_section->SetLeftMargin(0.126);
   c_final_cross_section->SetRightMargin(0.005);
   c_final_cross_section->SetTopMargin(0.017);
   c_final_cross_section->SetBottomMargin(0.089);
   c_final_cross_section->SetFrameBorderMode(0);
   c_final_cross_section->SetFrameBorderMode(0);
   
   TH1F *hframe__59 = new TH1F("hframe__59","",1000,8,62);
   hframe__59->SetMinimum(0.02);
   hframe__59->SetMaximum(60);
   hframe__59->SetDirectory(0);
   hframe__59->SetStats(0);
   hframe__59->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
   hframe__59->GetXaxis()->SetNdivisions(506);
   hframe__59->GetXaxis()->SetLabelFont(43);
   hframe__59->GetXaxis()->SetLabelSize(25.84615);
   hframe__59->GetXaxis()->SetTitleSize(28);
   hframe__59->GetXaxis()->SetTitleOffset(1.1);
   hframe__59->GetXaxis()->SetTitleFont(43);
   hframe__59->GetYaxis()->SetTitle("d^{2}#sigma/d#it{p}_{T}d#it{#eta} (nb GeV^{-1}#it{c})");
   hframe__59->GetYaxis()->SetNdivisions(506);
   hframe__59->GetYaxis()->SetLabelFont(43);
   hframe__59->GetYaxis()->SetLabelSize(25.84615);
   hframe__59->GetYaxis()->SetTitleSize(28);
   hframe__59->GetYaxis()->SetTitleOffset(1.7);
   hframe__59->GetYaxis()->SetTitleFont(43);
   hframe__59->GetZaxis()->SetLabelFont(43);
   hframe__59->GetZaxis()->SetLabelSize(25.84615);
   hframe__59->GetZaxis()->SetTitleOffset(1.1);
   hframe__59->GetZaxis()->SetTitleFont(43);
   hframe__59->Draw(" ");
   
   TGraphErrors *gre = new TGraphErrors(9);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#009999");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#009999");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009999");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.1);
   gre->SetPoint(0,11,26.5973);
   gre->SetPointError(0,1,6.239352);
   gre->SetPoint(1,13,14.8794);
   gre->SetPointError(1,1,3.188882);
   gre->SetPoint(2,15,10.83385);
   gre->SetPointError(2,1,2.109399);
   gre->SetPoint(3,17,5.186947);
   gre->SetPointError(3,1,0.9127192);
   gre->SetPoint(4,19,4.486123);
   gre->SetPointError(4,1,0.7439257);
   gre->SetPoint(5,22.5,1.977373);
   gre->SetPointError(5,2.5,0.3332534);
   gre->SetPoint(6,27.5,0.726073);
   gre->SetPointError(6,2.5,0.1253797);
   gre->SetPoint(7,35,0.274376);
   gre->SetPointError(7,5,0.04919262);
   gre->SetPoint(8,50,0.06892763);
   gre->SetPointError(8,10,0.01329394);
   gre->Draw("5");
   
   gre = new TGraphErrors(9);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#009999");
   gre->SetFillColor(ci);
   gre->SetFillStyle(0);

   ci = TColor::GetColor("#009999");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009999");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.1);
   gre->SetPoint(0,11,26.5973);
   gre->SetPointError(0,0,5.312159);
   gre->SetPoint(1,13,14.8794);
   gre->SetPointError(1,0,3.073538);
   gre->SetPoint(2,15,10.83385);
   gre->SetPointError(2,0,1.320367);
   gre->SetPoint(3,17,5.186947);
   gre->SetPointError(3,0,0.8255692);
   gre->SetPoint(4,19,4.486123);
   gre->SetPointError(4,0,0.6820796);
   gre->SetPoint(5,22.5,1.977373);
   gre->SetPointError(5,0,0.2983462);
   gre->SetPoint(6,27.5,0.726073);
   gre->SetPointError(6,0,0.1828152);
   gre->SetPoint(7,35,0.274376);
   gre->SetPointError(7,0,0.08326262);
   gre->SetPoint(8,50,0.06892763);
   gre->SetPointError(8,0,0.02778974);
   gre->Draw("ep");
   
   TLegend *leg = new TLegend(-2.353437e-185,-2.353437e-185,-2.353437e-185,-2.353437e-185,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(43);
   leg->SetTextSize(23);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("Graph1","Data, stat. unc.","ep");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph0","Data, syst. unc. (#pm norm. unc. 9.5%)","f");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   TLatex *   tex = new TLatex(0.45,0.913,"ALICE, pp #sqrt{#it{s}} = 7 TeV");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(28);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TH1F *hframe__60 = new TH1F("hframe__60","",1000,8,62);
   hframe__60->SetMinimum(0.02);
   hframe__60->SetMaximum(60);
   hframe__60->SetDirectory(0);
   hframe__60->SetStats(0);
   hframe__60->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
   hframe__60->GetXaxis()->SetNdivisions(506);
   hframe__60->GetXaxis()->SetLabelFont(43);
   hframe__60->GetXaxis()->SetLabelSize(25.84615);
   hframe__60->GetXaxis()->SetTitleSize(28);
   hframe__60->GetXaxis()->SetTitleOffset(1.1);
   hframe__60->GetXaxis()->SetTitleFont(43);
   hframe__60->GetYaxis()->SetTitle("d^{2}#sigma/d#it{p}_{T}d#it{#eta} (nb GeV^{-1}#it{c})");
   hframe__60->GetYaxis()->SetNdivisions(506);
   hframe__60->GetYaxis()->SetLabelFont(43);
   hframe__60->GetYaxis()->SetLabelSize(25.84615);
   hframe__60->GetYaxis()->SetTitleSize(28);
   hframe__60->GetYaxis()->SetTitleOffset(1.7);
   hframe__60->GetYaxis()->SetTitleFont(43);
   hframe__60->GetZaxis()->SetLabelFont(43);
   hframe__60->GetZaxis()->SetLabelSize(25.84615);
   hframe__60->GetZaxis()->SetTitleOffset(1.1);
   hframe__60->GetZaxis()->SetTitleFont(43);
   hframe__60->Draw("sameaxis");
   c_final_cross_section->Modified();
   c_final_cross_section->cd();
   c_final_cross_section->SetSelected(c_final_cross_section);
}
