#include <fstream>
#include <vector>
void purityFit(){
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);


  /*const int nbins_purity = 5;
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
  purityTest4->GetFunction("func")->SetLineColor(kBlack);//*/
  
  const int nbins = 5;
  Double_t purity_pp[nbins] = {0.201, 0.317, 0.473, 0.485, 0.485};
  Double_t statErr_pp[nbins] = {0.017, 0.020, 0.029, 0.035, 0.035};
  Double_t systErr_pp[nbins] = {0.037, 0.038, 0.042, 0.079, 0.079};
  Double_t totsErr_pp[nbins] = {0.0};
  Double_t PlusErr_pp[nbins] = {0.0};
  Double_t MinusErr_pp[nbins] = {0.0};
  
  Double_t purity_pPb[nbins] = {0.207, 0.342, 0.476, 0.546, 0.546};
  Double_t statErr_pPb[nbins] = {0.011, 0.012, 0.017, 0.018, 0.018};
  Double_t systErr_pPb[nbins] = {0.020, 0.028, 0.027, 0.039, 0.039};
  Double_t totsErr_pPb[nbins] = {0.0};
  Double_t PlusErr_pPb[nbins] = {0.0};
  Double_t MinusErr_pPb[nbins] = {0.0};

  for(int i = 0; i < nbins; i++){
    totsErr_pp[i] = TMath::Sqrt(TMath::Power(statErr_pp[i], 2) + TMath::Power(systErr_pp[i], 2));
    totsErr_pPb[i] = TMath::Sqrt(TMath::Power(statErr_pPb[i], 2) + TMath::Power(systErr_pPb[i], 2));

    PlusErr_pp[i] = purity_pp[i]+totsErr_pp[i];
    MinusErr_pp[i] = purity_pp[i]-totsErr_pp[i];
    PlusErr_pPb[i] = purity_pPb[i]+totsErr_pPb[i];
    MinusErr_pPb[i] = purity_pPb[i]-totsErr_pPb[i];

  }
  
  Double_t xBinCenters[nbins] = {13.198656, 16.903571, 22.064577, 30.107411, 45.0};
  Double_t xBinLeftErr[nbins] = {1.1986559999999997, 1.9035709999999995, 2.064577, 5.107410999999999, 5.0};
  Double_t xBinRightErr[nbins] = {1.8013440000000003, 3.0964290000000005, 2.935423, 9.892589000000001, 10.0};

  auto grPurity_pp = new TGraphAsymmErrors(nbins, xBinCenters, purity_pp, xBinLeftErr, xBinRightErr, totsErr_pp, totsErr_pp);
  grPurity_pp->SetTitle(";p_{T} [GeV/c]; purity");
  grPurity_pp->SetLineColor(kBlue);
  grPurity_pp->SetMarkerColor(kBlue);
  grPurity_pp->SetMarkerStyle(kFullCircle);

  auto grPurityPlus_pp = new TGraphAsymmErrors(nbins, xBinCenters, PlusErr_pp, xBinLeftErr, xBinRightErr);
  grPurityPlus_pp->SetTitle(";p_{T} [GeV/c]; purity");
  grPurityPlus_pp->SetLineColor(kBlue);
  grPurityPlus_pp->SetMarkerColor(kBlue);
  grPurityPlus_pp->SetMarkerStyle(kOpenTriangleDown);
  auto grPurityMinus_pp = new TGraphAsymmErrors(nbins, xBinCenters, MinusErr_pp, xBinLeftErr, xBinRightErr);
  grPurityMinus_pp->SetTitle(";p_{T} [GeV/c]; purity");
  grPurityMinus_pp->SetLineColor(kBlue);
  grPurityMinus_pp->SetMarkerColor(kBlue);
  grPurityMinus_pp->SetMarkerStyle(kOpenTriangleUp);
  
  

  auto grPurity_pPb = new TGraphAsymmErrors(nbins, xBinCenters, purity_pPb, xBinLeftErr, xBinRightErr, totsErr_pPb, totsErr_pPb);
  //grPurity_pPb->SetTitle("pPb purity");
  grPurity_pPb->SetLineColor(kRed);
  grPurity_pPb->SetMarkerColor(kRed);
  grPurity_pPb->SetMarkerStyle(kFullCircle);

  auto grPurityPlus_pPb = new TGraphAsymmErrors(nbins, xBinCenters, PlusErr_pPb, xBinLeftErr, xBinRightErr);
  grPurityPlus_pPb->SetTitle(";p_{T} [GeV/c]; purity");
  grPurityPlus_pPb->SetLineColor(kRed);
  grPurityPlus_pPb->SetMarkerColor(kRed);
  grPurityPlus_pPb->SetMarkerStyle(kOpenTriangleDown);
  auto grPurityMinus_pPb = new TGraphAsymmErrors(nbins, xBinCenters, MinusErr_pPb, xBinLeftErr, xBinRightErr);
  grPurityMinus_pPb->SetTitle(";p_{T} [GeV/c]; purity");
  grPurityMinus_pPb->SetLineColor(kRed);
  grPurityMinus_pPb->SetMarkerColor(kRed);
  grPurityMinus_pPb->SetMarkerStyle(kOpenTriangleUp);
  
  TCanvas* c1 = new TCanvas("c1", "c1");
  //c1->SetGridx();
  c1->DrawFrame(12, 0.0, 40, 0.6);

  grPurity_pp->Draw("p");
  grPurityPlus_pp->Draw("psame");
  grPurityMinus_pp->Draw("psame");
  grPurity_pp->GetXaxis()->SetRangeUser(12,40);
  grPurityPlus_pp->GetXaxis()->SetRangeUser(12,40);
  grPurityMinus_pp->GetXaxis()->SetRangeUser(12,40);
  c1->Update();
  
  
  TF1* erf = new TF1("erf","[0]*TMath::Erf((x-[1])/[2])",12,40);
  erf->SetParameter(0,0.55);
  erf->SetParameter(1,8.0);
  erf->SetParameter(2,12.0);

  grPurity_pp->Fit("erf", "S", "", 12, 55);
  grPurityPlus_pp->Fit("erf", "S", "", 12, 55);
  grPurityMinus_pp->Fit("erf", "S", "", 12, 55);
  

  TF1* erf_pp = grPurity_pp->GetFunction("erf");
  erf_pp->SetLineColor(kBlue);
  erf_pp->SetLineWidth(5);
  erf_pp->Draw("same");//*/
  TF1* erfPlus_pp = grPurityPlus_pp->GetFunction("erf");
  erfPlus_pp->SetLineColor(kBlue);
  erfPlus_pp->SetLineStyle(kDashed);
  erfPlus_pp->SetLineWidth(5);
  erfPlus_pp->Draw("same");//*/
  TF1* erfMinus_pp = grPurityMinus_pp->GetFunction("erf");
  erfMinus_pp->SetLineColor(kBlue);
  erfMinus_pp->SetLineStyle(kDashed);
  erfMinus_pp->SetLineWidth(5);
  erfMinus_pp->Draw("same");//*/

  TLegend* l1 = new TLegend(0.5, 0.2, 0.85, 0.5);
  l1->SetHeader("p-Pb purity");
  l1->AddEntry(grPurity_pp, "central value (CV)");
  l1->AddEntry(grPurityPlus_pp, "CV + #sigma");
  l1->AddEntry(grPurityMinus_pp, "CV - #sigma");
  l1->Draw("same");
  
}//end function
