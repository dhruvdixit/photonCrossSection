#include <fstream>
#include <vector>
void purityFit(){
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);


  const int nbins_purity = 5;
  Double_t purity_bins[nbins_purity+1] = {12,15,20,25,40,55};//12,15,20,25,40,50};
  Double_t purity_binCenters[nbins_purity] = {0.0};
  Double_t purity_erX[nbins_purity] = {1.5, 2.5, 2.5, 7.5, 7.5};
  for(int i = 0; i < nbins_purity; i++){
    purity_binCenters[i] = (purity_bins[i+1]+purity_bins[i])/2.0;
  }

  //purities
  Double_t purity_std[nbins_purity]       = {0.1980,	0.3180,	0.4700,	0.4870, 0.4870};
  Double_t purity_test1[nbins_purity]     = {0.2000,	0.3370,	0.4800,	0.5360, 0.5360};
  Double_t purity_test2[nbins_purity]     = {0.1660,	0.3070,	0.4690,	0.5270, 0.5270};
  Double_t purity_test3[nbins_purity]     = {0.1660,	0.3070,	0.4690,	0.5270, 0.5270};
  Double_t purity_test4[nbins_purity]     = {0.1770,	0.3260,	0.4840,	0.5600, 0.5600};
  
  Double_t purity_std_erY[nbins_purity]   = {0.0550,	0.0410,	0.0716,	0.0895, 0.0895};
  Double_t purity_test1_erY[nbins_purity] = {0.0233,	0.0318,	0.0347,	0.0548, 0.054};
  Double_t purity_test2_erY[nbins_purity] = {0.0233,	0.0322,	0.0344,	0.0544, 0.0544};
  Double_t purity_test3_erY[nbins_purity] = {0.0233,	0.0322,	0.0347,	0.0542, 0.0542};
  Double_t purity_test4_erY[nbins_purity] = {0.0251,	0.0322,	0.0355,	0.0511, 0.0511};
  


  TGraphErrors* purityStd = new TGraphErrors(nbins_purity, purity_binCenters, purity_std, purity_erX,  purity_std_erY);
  purityStd->SetLineColor(kRed);
  purityStd->SetMarkerColor(kRed);
  purityStd->SetMarkerStyle(20);
  purityStd->GetXaxis()->SetRangeUser(12.0, 40.0);

  TGraphErrors* purityTest1 = new TGraphErrors(nbins_purity, purity_binCenters, purity_test1, purity_erX,  purity_test1_erY);
  purityTest1->SetLineColor(kCyan);
  purityTest1->SetMarkerColor(kCyan);
  purityTest1->SetMarkerStyle(20);
  purityTest1->GetXaxis()->SetRangeUser(12.0, 40.0);

  TGraphErrors* purityTest2 = new TGraphErrors(nbins_purity, purity_binCenters, purity_test2, purity_erX,  purity_test2_erY);
  purityTest2->SetLineColor(kBlue);
  purityTest2->SetMarkerColor(kBlue);
  purityTest2->SetMarkerStyle(20);

  TGraphErrors* purityTest3 = new TGraphErrors(nbins_purity, purity_binCenters, purity_test3, purity_erX,  purity_test3_erY);
  purityTest3->SetLineColor(kMagenta);
  purityTest3->SetMarkerColor(kMagenta);
  purityTest3->SetMarkerStyle(20);

  TGraphErrors* purityTest4 = new TGraphErrors(nbins_purity, purity_binCenters, purity_test4, purity_erX,  purity_test4_erY);
  purityTest4->SetLineColor(kBlack);
  purityTest4->SetMarkerColor(kBlack);
  purityTest4->SetMarkerStyle(20);


  TLegend* leg = new TLegend(0.36,0.16,0.9,0.37);
  leg->AddEntry(purityStd, "Our cuts");
  leg->AddEntry(purityTest1, "Erwann's cuts");
  leg->AddEntry(purityTest2, "Erwann's cuts with dist to BC >= 1");
  leg->AddEntry(purityTest3, "Erwann's cuts with no NLM and dist to BC >= 1");
  leg->AddEntry(purityTest4, "Our cuts with no NLM");

  
  TCanvas* c_purity = new TCanvas("c_purity", "c_purity", 800, 800);
  purityStd->Draw("ap");
  purityTest1->Draw("psame");
  purityTest2->Draw("psame");
  purityTest3->Draw("psame");
  purityTest4->Draw("psame");
  leg->Draw("same");
  
  TF1* func = new TF1("func","[0]*TMath::Erf((x-[1])/[2])",12,40);
  func->SetParameter(0,0.55);
  func->SetParameter(1,8.0);
  func->SetParameter(2,12.0);

  
  purityStd->Fit("func", "S");
  purityTest1->Fit("func", "S");
  purityTest2->Fit("func", "S");
  purityTest3->Fit("func", "S");
  purityTest4->Fit("func", "S");

  purityStd->GetFunction("func")->SetLineColor(kRed);
  purityTest1->GetFunction("func")->SetLineColor(kCyan);
  purityTest2->GetFunction("func")->SetLineColor(kBlue);
  purityTest3->GetFunction("func")->SetLineColor(kMagenta);
  purityTest4->GetFunction("func")->SetLineColor(kBlack);
}//end function
