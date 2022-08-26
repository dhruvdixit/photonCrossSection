#ifdef __CLING__
#pragma cling optimize(0)
#endif
void pQCD_NLO_pQCD_pPb_8160_ratio()
{
//=========Macro generated from canvas: cc7/cc7
//=========  (Mon Mar 28 22:30:37 2022) by ROOT version 6.26/00
   TCanvas *cc7 = new TCanvas("cc7", "cc7",0,37,400,400);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cc7->Range(0,0,1,1);
   cc7->SetFillColor(0);
   cc7->SetBorderMode(0);
   cc7->SetBorderSize(2);
   cc7->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: mpad7
   TPad *mpad7 = new TPad("mpad7", "mpad7",0.02,0.02,0.99,0.99);
   mpad7->Draw();
   mpad7->cd();
   mpad7->Range(-16.30137,-0.3376623,79.58904,2.25974);
   mpad7->SetFillColor(0);
   mpad7->SetBorderMode(0);
   mpad7->SetBorderSize(0);
   mpad7->SetTickx(1);
   mpad7->SetTicky(1);
   mpad7->SetLeftMargin(0.17);
   mpad7->SetBottomMargin(0.13);
   mpad7->SetFrameBorderMode(0);
   mpad7->SetFrameBorderMode(0);
   
   TH2F *htemp__4 = new TH2F("htemp__4","",10,0,70,10,0,2);
   htemp__4->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   htemp__4->SetLineColor(ci);
   htemp__4->SetMarkerSize(1.6);
   htemp__4->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   htemp__4->GetXaxis()->SetNdivisions(505);
   htemp__4->GetXaxis()->SetLabelFont(42);
   htemp__4->GetXaxis()->SetLabelOffset(0.01);
   htemp__4->GetXaxis()->SetLabelSize(0.045);
   htemp__4->GetXaxis()->SetTitleSize(0.05);
   htemp__4->GetXaxis()->SetTitleOffset(1.2);
   htemp__4->GetXaxis()->SetTitleFont(42);
   htemp__4->GetYaxis()->SetTitle("data / NLO pQCD");
   htemp__4->GetYaxis()->SetNdivisions(505);
   htemp__4->GetYaxis()->SetLabelFont(42);
   htemp__4->GetYaxis()->SetLabelOffset(0.01);
   htemp__4->GetYaxis()->SetLabelSize(0.045);
   htemp__4->GetYaxis()->SetTitleSize(0.045);
   htemp__4->GetYaxis()->SetTitleOffset(1.6);
   htemp__4->GetYaxis()->SetTitleFont(42);
   htemp__4->GetZaxis()->SetLabelFont(42);
   htemp__4->GetZaxis()->SetTitleOffset(1);
   htemp__4->GetZaxis()->SetTitleFont(42);
   htemp__4->Draw("");
   
   Double_t Graph0_fx1010[9] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50};
   Double_t Graph0_fy1010[9] = {
   0,
   1.027959,
   0.9838798,
   1.08045,
   1.266247,
   1.142577,
   1.180333,
   1.121583,
   0.9921701};
   Double_t Graph0_fex1010[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1010[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   TGraphErrors *gre = new TGraphErrors(9,Graph0_fx1010,Graph0_fy1010,Graph0_fex1010,Graph0_fey1010);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineStyle(3);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph01010 = new TH1F("Graph_Graph01010","Graph",100,7.1,53.9);
   Graph_Graph01010->SetMinimum(0);
   Graph_Graph01010->SetMaximum(1.392872);
   Graph_Graph01010->SetDirectory(0);
   Graph_Graph01010->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01010->SetLineColor(ci);
   Graph_Graph01010->SetMarkerSize(1.6);
   Graph_Graph01010->GetXaxis()->SetLabelFont(42);
   Graph_Graph01010->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01010->GetXaxis()->SetTitleFont(42);
   Graph_Graph01010->GetYaxis()->SetLabelFont(42);
   Graph_Graph01010->GetYaxis()->SetTitleFont(42);
   Graph_Graph01010->GetZaxis()->SetLabelFont(42);
   Graph_Graph01010->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01010);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1011[9] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50};
   Double_t Graph1_fy1011[9] = {
   0,
   1.015912,
   0.9894913,
   1.099545,
   1.304271,
   1.191993,
   1.249361,
   1.201193,
   1.076301};
   Double_t Graph1_fex1011[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1011[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(9,Graph1_fx1011,Graph1_fy1011,Graph1_fex1011,Graph1_fey1011);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph11011 = new TH1F("Graph_Graph11011","Graph",100,7.1,53.9);
   Graph_Graph11011->SetMinimum(0);
   Graph_Graph11011->SetMaximum(1.434698);
   Graph_Graph11011->SetDirectory(0);
   Graph_Graph11011->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11011->SetLineColor(ci);
   Graph_Graph11011->SetMarkerSize(1.6);
   Graph_Graph11011->GetXaxis()->SetLabelFont(42);
   Graph_Graph11011->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11011->GetXaxis()->SetTitleFont(42);
   Graph_Graph11011->GetYaxis()->SetLabelFont(42);
   Graph_Graph11011->GetYaxis()->SetTitleFont(42);
   Graph_Graph11011->GetZaxis()->SetLabelFont(42);
   Graph_Graph11011->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11011);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1012[9] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50};
   Double_t Graph2_fy1012[9] = {
   0,
   1.014086,
   0.9977072,
   1.12025,
   1.339333,
   1.234913,
   1.306013,
   1.270325,
   1.150264};
   Double_t Graph2_fex1012[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1012[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(9,Graph2_fx1012,Graph2_fy1012,Graph2_fex1012,Graph2_fey1012);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineStyle(6);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph21012 = new TH1F("Graph_Graph21012","Graph",100,7.1,53.9);
   Graph_Graph21012->SetMinimum(0);
   Graph_Graph21012->SetMaximum(1.473266);
   Graph_Graph21012->SetDirectory(0);
   Graph_Graph21012->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21012->SetLineColor(ci);
   Graph_Graph21012->SetMarkerSize(1.6);
   Graph_Graph21012->GetXaxis()->SetLabelFont(42);
   Graph_Graph21012->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21012->GetXaxis()->SetTitleFont(42);
   Graph_Graph21012->GetYaxis()->SetLabelFont(42);
   Graph_Graph21012->GetYaxis()->SetTitleFont(42);
   Graph_Graph21012->GetZaxis()->SetLabelFont(42);
   Graph_Graph21012->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21012);
   
   gre->Draw("p");
   
   TLegend *leg = new TLegend(0.62,0.18,0.85,0.33,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.035);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("Graph0","#mu = 0.5","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(0.8);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1","#mu = 1.0","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.8);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph2","#mu = 2.0","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(0.8);
   entry->SetTextFont(42);
   leg->Draw();
   TLine *line = new TLine(0,1,70,1);
   line->SetLineStyle(7);
   line->SetLineWidth(2);
   line->Draw();
   TLatex *   tex = new TLatex(0.62,0.66,"p+Pb 8.16 TeV");
tex->SetNDC();
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.62,0.86,"ALICE Preliminary");
tex->SetNDC();
   tex->SetTextSize(0.032);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.62,0.82,"NLO pQCD");
tex->SetNDC();
   tex->SetTextSize(0.032);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.62,0.78,"(by W. Vogelsang)");
tex->SetNDC();
   tex->SetTextSize(0.032);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.62,0.74,"NNPDF3.0 PDF");
tex->SetNDC();
   tex->SetTextSize(0.032);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.62,0.7,"GRV FF");
tex->SetNDC();
   tex->SetTextSize(0.032);
   tex->SetLineWidth(2);
   tex->Draw();
   mpad7->Modified();
   cc7->cd();
   cc7->Modified();
   cc7->cd();
   cc7->SetSelected(cc7);
}
