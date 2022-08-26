#ifdef __CLING__
#pragma cling optimize(0)
#endif
void pQCD_NLO_pQCD_pp_8160_ratio()
{
//=========Macro generated from canvas: cc3/cc3
//=========  (Mon Mar 28 22:30:36 2022) by ROOT version 6.26/00
   TCanvas *cc3 = new TCanvas("cc3", "cc3",0,37,400,400);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cc3->Range(0,0,1,1);
   cc3->SetFillColor(0);
   cc3->SetBorderMode(0);
   cc3->SetBorderSize(2);
   cc3->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: mpad3
   TPad *mpad3 = new TPad("mpad3", "mpad3",0.02,0.02,0.99,0.99);
   mpad3->Draw();
   mpad3->cd();
   mpad3->Range(-16.30137,-0.3376623,79.58904,2.25974);
   mpad3->SetFillColor(0);
   mpad3->SetBorderMode(0);
   mpad3->SetBorderSize(0);
   mpad3->SetTickx(1);
   mpad3->SetTicky(1);
   mpad3->SetLeftMargin(0.17);
   mpad3->SetBottomMargin(0.13);
   mpad3->SetFrameBorderMode(0);
   mpad3->SetFrameBorderMode(0);
   
   TH2F *htemp__2 = new TH2F("htemp__2","",10,0,70,10,0,2);
   htemp__2->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   htemp__2->SetLineColor(ci);
   htemp__2->SetMarkerSize(1.6);
   htemp__2->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   htemp__2->GetXaxis()->SetNdivisions(505);
   htemp__2->GetXaxis()->SetLabelFont(42);
   htemp__2->GetXaxis()->SetLabelOffset(0.01);
   htemp__2->GetXaxis()->SetLabelSize(0.045);
   htemp__2->GetXaxis()->SetTitleSize(0.05);
   htemp__2->GetXaxis()->SetTitleOffset(1.2);
   htemp__2->GetXaxis()->SetTitleFont(42);
   htemp__2->GetYaxis()->SetTitle("data / NLO pQCD");
   htemp__2->GetYaxis()->SetNdivisions(505);
   htemp__2->GetYaxis()->SetLabelFont(42);
   htemp__2->GetYaxis()->SetLabelOffset(0.01);
   htemp__2->GetYaxis()->SetLabelSize(0.045);
   htemp__2->GetYaxis()->SetTitleSize(0.045);
   htemp__2->GetYaxis()->SetTitleOffset(1.6);
   htemp__2->GetYaxis()->SetTitleFont(42);
   htemp__2->GetZaxis()->SetLabelFont(42);
   htemp__2->GetZaxis()->SetTitleOffset(1);
   htemp__2->GetZaxis()->SetTitleFont(42);
   htemp__2->Draw("");
   
   Double_t Graph0_fx1004[11] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50,
   70,
   90};
   Double_t Graph0_fy1004[11] = {
   0.7233331,
   0.9362262,
   0.9991297,
   0.9301362,
   0.8412803,
   0.8979842,
   0.8792682,
   0.9318946,
   0.95298,
   0.6085746,
   169.9528};
   Double_t Graph0_fex1004[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1004[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   TGraphErrors *gre = new TGraphErrors(11,Graph0_fx1004,Graph0_fy1004,Graph0_fex1004,Graph0_fey1004);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineStyle(3);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph01004 = new TH1F("Graph_Graph01004","Graph",100,3.1,97.9);
   Graph_Graph01004->SetMinimum(0.5477172);
   Graph_Graph01004->SetMaximum(186.8872);
   Graph_Graph01004->SetDirectory(0);
   Graph_Graph01004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01004->SetLineColor(ci);
   Graph_Graph01004->SetMarkerSize(1.6);
   Graph_Graph01004->GetXaxis()->SetLabelFont(42);
   Graph_Graph01004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01004->GetXaxis()->SetTitleFont(42);
   Graph_Graph01004->GetYaxis()->SetLabelFont(42);
   Graph_Graph01004->GetYaxis()->SetTitleFont(42);
   Graph_Graph01004->GetZaxis()->SetLabelFont(42);
   Graph_Graph01004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01004);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1005[11] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50,
   70,
   90};
   Double_t Graph1_fy1005[11] = {
   0.7174213,
   0.9499514,
   1.026872,
   0.9652231,
   0.881549,
   0.9515301,
   0.9408019,
   1.006936,
   1.039508,
   0.6680815,
   1.02503};
   Double_t Graph1_fex1005[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1005[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(11,Graph1_fx1005,Graph1_fy1005,Graph1_fex1005,Graph1_fey1005);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph11005 = new TH1F("Graph_Graph11005","Graph",100,3.1,97.9);
   Graph_Graph11005->SetMinimum(0.6309389);
   Graph_Graph11005->SetMaximum(1.07665);
   Graph_Graph11005->SetDirectory(0);
   Graph_Graph11005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11005->SetLineColor(ci);
   Graph_Graph11005->SetMarkerSize(1.6);
   Graph_Graph11005->GetXaxis()->SetLabelFont(42);
   Graph_Graph11005->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11005->GetXaxis()->SetTitleFont(42);
   Graph_Graph11005->GetYaxis()->SetLabelFont(42);
   Graph_Graph11005->GetYaxis()->SetTitleFont(42);
   Graph_Graph11005->GetZaxis()->SetLabelFont(42);
   Graph_Graph11005->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11005);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1006[11] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50,
   70,
   90};
   Double_t Graph2_fy1006[11] = {
   0.7186487,
   0.9627592,
   1.049858,
   0.9970271,
   0.9163919,
   0.9959421,
   0.9929849,
   1.07265,
   1.057135,
   0.723863,
   1.097893};
   Double_t Graph2_fex1006[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1006[11] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(11,Graph2_fx1006,Graph2_fy1006,Graph2_fex1006,Graph2_fey1006);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineStyle(6);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph21006 = new TH1F("Graph_Graph21006","Graph",100,3.1,97.9);
   Graph_Graph21006->SetMinimum(0.6807243);
   Graph_Graph21006->SetMaximum(1.135817);
   Graph_Graph21006->SetDirectory(0);
   Graph_Graph21006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21006->SetLineColor(ci);
   Graph_Graph21006->SetMarkerSize(1.6);
   Graph_Graph21006->GetXaxis()->SetLabelFont(42);
   Graph_Graph21006->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21006->GetXaxis()->SetTitleFont(42);
   Graph_Graph21006->GetYaxis()->SetLabelFont(42);
   Graph_Graph21006->GetYaxis()->SetTitleFont(42);
   Graph_Graph21006->GetZaxis()->SetLabelFont(42);
   Graph_Graph21006->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21006);
   
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
   TLatex *   tex = new TLatex(0.62,0.66,"p+p 8.16 TeV");
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
   mpad3->Modified();
   cc3->cd();
   cc3->Modified();
   cc3->cd();
   cc3->SetSelected(cc3);
}
