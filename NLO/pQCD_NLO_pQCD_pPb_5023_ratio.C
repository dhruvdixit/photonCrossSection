#ifdef __CLING__
#pragma cling optimize(0)
#endif
void pQCD_NLO_pQCD_pPb_5023_ratio()
{
//=========Macro generated from canvas: cc5/cc5
//=========  (Mon Mar 28 22:30:37 2022) by ROOT version 6.26/00
   TCanvas *cc5 = new TCanvas("cc5", "cc5",0,37,400,400);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cc5->Range(0,0,1,1);
   cc5->SetFillColor(0);
   cc5->SetBorderMode(0);
   cc5->SetBorderSize(2);
   cc5->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: mpad5
   TPad *mpad5 = new TPad("mpad5", "mpad5",0.02,0.02,0.99,0.99);
   mpad5->Draw();
   mpad5->cd();
   mpad5->Range(-16.30137,-0.3376623,79.58904,2.25974);
   mpad5->SetFillColor(0);
   mpad5->SetBorderMode(0);
   mpad5->SetBorderSize(0);
   mpad5->SetTickx(1);
   mpad5->SetTicky(1);
   mpad5->SetLeftMargin(0.17);
   mpad5->SetBottomMargin(0.13);
   mpad5->SetFrameBorderMode(0);
   mpad5->SetFrameBorderMode(0);
   
   TH2F *htemp__3 = new TH2F("htemp__3","",10,0,70,10,0,2);
   htemp__3->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   htemp__3->SetLineColor(ci);
   htemp__3->SetMarkerSize(1.6);
   htemp__3->GetXaxis()->SetTitle("p_{T} [GeV/c]");
   htemp__3->GetXaxis()->SetNdivisions(505);
   htemp__3->GetXaxis()->SetLabelFont(42);
   htemp__3->GetXaxis()->SetLabelOffset(0.01);
   htemp__3->GetXaxis()->SetLabelSize(0.045);
   htemp__3->GetXaxis()->SetTitleSize(0.05);
   htemp__3->GetXaxis()->SetTitleOffset(1.2);
   htemp__3->GetXaxis()->SetTitleFont(42);
   htemp__3->GetYaxis()->SetTitle("data / NLO pQCD");
   htemp__3->GetYaxis()->SetNdivisions(505);
   htemp__3->GetYaxis()->SetLabelFont(42);
   htemp__3->GetYaxis()->SetLabelOffset(0.01);
   htemp__3->GetYaxis()->SetLabelSize(0.045);
   htemp__3->GetYaxis()->SetTitleSize(0.045);
   htemp__3->GetYaxis()->SetTitleOffset(1.6);
   htemp__3->GetYaxis()->SetTitleFont(42);
   htemp__3->GetZaxis()->SetLabelFont(42);
   htemp__3->GetZaxis()->SetTitleOffset(1);
   htemp__3->GetZaxis()->SetTitleFont(42);
   htemp__3->Draw("");
   
   Double_t Graph0_fx1007[9] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50};
   Double_t Graph0_fy1007[9] = {
   0.5396923,
   0.7983618,
   0.8623587,
   0.8926863,
   0.8735952,
   0.8591275,
   0.9302803,
   0.9485138,
   0.7672786};
   Double_t Graph0_fex1007[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1007[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   TGraphErrors *gre = new TGraphErrors(9,Graph0_fx1007,Graph0_fy1007,Graph0_fex1007,Graph0_fey1007);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineStyle(3);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph01007 = new TH1F("Graph_Graph01007","Graph",100,7.1,53.9);
   Graph_Graph01007->SetMinimum(0.4988101);
   Graph_Graph01007->SetMaximum(0.989396);
   Graph_Graph01007->SetDirectory(0);
   Graph_Graph01007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01007->SetLineColor(ci);
   Graph_Graph01007->SetMarkerSize(1.6);
   Graph_Graph01007->GetXaxis()->SetLabelFont(42);
   Graph_Graph01007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01007->GetXaxis()->SetTitleFont(42);
   Graph_Graph01007->GetYaxis()->SetLabelFont(42);
   Graph_Graph01007->GetYaxis()->SetTitleFont(42);
   Graph_Graph01007->GetZaxis()->SetLabelFont(42);
   Graph_Graph01007->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01007);
   
   gre->Draw("p");
   
   Double_t Graph1_fx1008[9] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50};
   Double_t Graph1_fy1008[9] = {
   0.5409403,
   2.465812,
   0.8989234,
   0.9397403,
   0.9280643,
   0.9236256,
   1.010717,
   1.039886,
   0.8478949};
   Double_t Graph1_fex1008[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1008[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(9,Graph1_fx1008,Graph1_fy1008,Graph1_fex1008,Graph1_fey1008);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph11008 = new TH1F("Graph_Graph11008","Graph",100,7.1,53.9);
   Graph_Graph11008->SetMinimum(0.3484531);
   Graph_Graph11008->SetMaximum(2.658299);
   Graph_Graph11008->SetDirectory(0);
   Graph_Graph11008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11008->SetLineColor(ci);
   Graph_Graph11008->SetMarkerSize(1.6);
   Graph_Graph11008->GetXaxis()->SetLabelFont(42);
   Graph_Graph11008->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11008->GetXaxis()->SetTitleFont(42);
   Graph_Graph11008->GetYaxis()->SetLabelFont(42);
   Graph_Graph11008->GetYaxis()->SetTitleFont(42);
   Graph_Graph11008->GetZaxis()->SetLabelFont(42);
   Graph_Graph11008->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11008);
   
   gre->Draw("p");
   
   Double_t Graph2_fx1009[9] = {
   11,
   13,
   15,
   17,
   19,
   22.5,
   27.5,
   35,
   50};
   Double_t Graph2_fy1009[9] = {
   0.5476614,
   0.8395959,
   0.9289761,
   0.9804231,
   0.9755344,
   0.9767378,
   1.078445,
   1.120273,
   0.921511};
   Double_t Graph2_fex1009[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph2_fey1009[9] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(9,Graph2_fx1009,Graph2_fy1009,Graph2_fex1009,Graph2_fey1009);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineStyle(6);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.8);
   
   TH1F *Graph_Graph21009 = new TH1F("Graph_Graph21009","Graph",100,7.1,53.9);
   Graph_Graph21009->SetMinimum(0.4904002);
   Graph_Graph21009->SetMaximum(1.177535);
   Graph_Graph21009->SetDirectory(0);
   Graph_Graph21009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21009->SetLineColor(ci);
   Graph_Graph21009->SetMarkerSize(1.6);
   Graph_Graph21009->GetXaxis()->SetLabelFont(42);
   Graph_Graph21009->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21009->GetXaxis()->SetTitleFont(42);
   Graph_Graph21009->GetYaxis()->SetLabelFont(42);
   Graph_Graph21009->GetYaxis()->SetTitleFont(42);
   Graph_Graph21009->GetZaxis()->SetLabelFont(42);
   Graph_Graph21009->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21009);
   
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
   TLatex *   tex = new TLatex(0.62,0.66,"p+Pb 5.02 TeV");
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
   mpad5->Modified();
   cc5->cd();
   cc5->Modified();
   cc5->cd();
   cc5->SetSelected(cc5);
}
