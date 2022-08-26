#ifdef __CLING__
#pragma cling optimize(0)
#endif
void pQCD_NLO_pQCD_pp_5023_ratio()
{
//=========Macro generated from canvas: cc1/cc1
//=========  (Mon Mar 28 22:30:35 2022) by ROOT version 6.26/00
   TCanvas *cc1 = new TCanvas("cc1", "cc1",0,37,400,400);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cc1->Range(0,0,1,1);
   cc1->SetFillColor(0);
   cc1->SetBorderMode(0);
   cc1->SetBorderSize(2);
   cc1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: mpad1
   TPad *mpad1 = new TPad("mpad1", "mpad1",0.02,0.02,0.99,0.99);
   mpad1->Draw();
   mpad1->cd();
   mpad1->Range(-16.30137,-0.3376623,79.58904,2.25974);
   mpad1->SetFillColor(0);
   mpad1->SetBorderMode(0);
   mpad1->SetBorderSize(0);
   mpad1->SetTickx(1);
   mpad1->SetTicky(1);
   mpad1->SetLeftMargin(0.17);
   mpad1->SetBottomMargin(0.13);
   mpad1->SetFrameBorderMode(0);
   mpad1->SetFrameBorderMode(0);
   
   TH2F *htemp__1 = new TH2F("htemp__1","",10,0,70,10,0,2);
   htemp__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   htemp__1->SetLineColor(ci);
   htemp__1->SetMarkerSize(1.6);
   htemp__1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   htemp__1->GetXaxis()->SetNdivisions(505);
   htemp__1->GetXaxis()->SetLabelFont(42);
   htemp__1->GetXaxis()->SetLabelOffset(0.01);
   htemp__1->GetXaxis()->SetLabelSize(0.045);
   htemp__1->GetXaxis()->SetTitleSize(0.05);
   htemp__1->GetXaxis()->SetTitleOffset(1.2);
   htemp__1->GetXaxis()->SetTitleFont(42);
   htemp__1->GetYaxis()->SetTitle("data / NLO pQCD");
   htemp__1->GetYaxis()->SetNdivisions(505);
   htemp__1->GetYaxis()->SetLabelFont(42);
   htemp__1->GetYaxis()->SetLabelOffset(0.01);
   htemp__1->GetYaxis()->SetLabelSize(0.045);
   htemp__1->GetYaxis()->SetTitleSize(0.045);
   htemp__1->GetYaxis()->SetTitleOffset(1.6);
   htemp__1->GetYaxis()->SetTitleFont(42);
   htemp__1->GetZaxis()->SetLabelFont(42);
   htemp__1->GetZaxis()->SetTitleOffset(1);
   htemp__1->GetZaxis()->SetTitleFont(42);
   htemp__1->Draw("");
   
   Double_t Graph0_fx1001[9] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50};
   Double_t Graph0_fy1001[9] = {
   0.5682575,
   0.5651184,
   0.5531347,
   0.5609585,
   0.4843865,
   0.5657233,
   0.5538876,
   0.549103,
   0.5479445};
   Double_t Graph0_fex1001[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1001[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   TGraphErrors *gre = new TGraphErrors(9,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineStyle(3);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","Graph",100,7.1,53.9);
   Graph_Graph01001->SetMinimum(0.4759994);
   Graph_Graph01001->SetMaximum(0.5766446);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->SetMarkerSize(1.6);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1002[9] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50};
   Double_t Graph1_fy1002[9] = {
   0.5852843,
   0.5925029,
   0.5869415,
   0.5992758,
   0.521877,
   0.6147614,
   0.6064603,
   0.6052336,
   0.563471};
   Double_t Graph1_fex1002[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1002[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(9,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph11002 = new TH1F("Graph_Graph11002","Graph",100,7.1,53.9);
   Graph_Graph11002->SetMinimum(0.5125886);
   Graph_Graph11002->SetMaximum(0.6240499);
   Graph_Graph11002->SetDirectory(0);
   Graph_Graph11002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11002->SetLineColor(ci);
   Graph_Graph11002->SetMarkerSize(1.6);
   Graph_Graph11002->GetXaxis()->SetLabelFont(42);
   Graph_Graph11002->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetXaxis()->SetTitleFont(42);
   Graph_Graph11002->GetYaxis()->SetLabelFont(42);
   Graph_Graph11002->GetYaxis()->SetTitleFont(42);
   Graph_Graph11002->GetZaxis()->SetLabelFont(42);
   Graph_Graph11002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11002);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1003[9] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50};
   Double_t Graph2_fy1003[9] = {
   0.6025219,
   0.6157772,
   0.6143749,
   0.6328531,
   0.5543246,
   0.6558129,
   0.651289,
   0.6556773,
   0.6587231};
   Double_t Graph2_fex1003[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1003[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(9,Graph2_fx1003,Graph2_fy1003,Graph2_fex1003,Graph2_fey1003);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineStyle(6);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph21003 = new TH1F("Graph_Graph21003","Graph",100,7.1,53.9);
   Graph_Graph21003->SetMinimum(0.5438848);
   Graph_Graph21003->SetMaximum(0.6691629);
   Graph_Graph21003->SetDirectory(0);
   Graph_Graph21003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21003->SetLineColor(ci);
   Graph_Graph21003->SetMarkerSize(1.6);
   Graph_Graph21003->GetXaxis()->SetLabelFont(42);
   Graph_Graph21003->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetXaxis()->SetTitleFont(42);
   Graph_Graph21003->GetYaxis()->SetLabelFont(42);
   Graph_Graph21003->GetYaxis()->SetTitleFont(42);
   Graph_Graph21003->GetZaxis()->SetLabelFont(42);
   Graph_Graph21003->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21003);
   
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
   TLatex *   tex = new TLatex(0.62,0.66,"p+p 5.02 TeV");
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
   mpad1->Modified();
   cc1->cd();
   cc1->Modified();
   cc1->cd();
   cc1->SetSelected(cc1);
}
