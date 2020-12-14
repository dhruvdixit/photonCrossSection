#include <fstream>
#include <vector>
void purityFit(){
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  
  const int nbins = 5;
  //Double_t purity_pp[nbins] = {0.2032, 0.3258, 0.4758, 0.527, 0.527};//ssc < 0.26
  //Double_t statErr_pp[nbins] = {0.0148, 0.0191, 0.0248, 0.0315, 0.0315};//ssc < 0.26
  //Double_t purity_pp[nbins] = {0.2073, 0.329, 0.4688, 0.5265, 0.5265};//ssc < 0.28
  //Double_t statErr_pp[nbins] = {0.0151, 0.0192, 0.0248, 0.0323, 0.0323};//ssc < 0.28
  //Double_t purity_pp[nbins]= {0.2079, 0.3238, 0.4346, 0.4598, 0.4598};//ssc < 0.33
  //Double_t statErr_pp[nbins] = {0.0151, 0.0190, 0.0245, 0.0322, 0.0322};//ssc < 0.33
  //Double_t purity_pp[nbins] = {0.2061, 0.3149, 0.4112, 0.4415, 0.4415};//ssc < 0.35
  //Double_t statErr_pp[nbins] = {0.0150, 0.0187, 0.0247, 0.0319, 0.0319};//ssc < 0.35

  Double_t purity_pp[nbins] = {0.201, 0.317, 0.473, 0.485, 0.485};
  Double_t statErr_pp[nbins] = {0.017, 0.020, 0.029, 0.035, 0.035};
  Double_t systErr_pp[nbins] = {0.034, 0.036, 0.040, 0.078, 0.078};
  Double_t sigErr_pp[nbins] = {0.020, 0.025, 0.008, 0.058, 0.058};
  Double_t antiErr_pp[nbins] = {0.012, 0.015, 0.030, 0.040, 0.040};
  Double_t bkgErr_pp[nbins] = {0.025, 0.021, 0.026, 0.032, 0.032};
  Double_t totsErr_pp[nbins] = {0.0};
  Double_t PlusErr_pp[nbins] = {0.0};
  Double_t MinusErr_pp[nbins] = {0.0};
  
  //Double_t purity_pPb[nbins] = {0.2020, 0.3433, 0.5170, 0.6211, 0.6211};//ssc < 0.26
  //Double_t statErr_pPb[nbins] = {0.0083, 0.0125, 0.0198, 0.0248, 0.0248};//ssc < 0.26
  //Double_t purity_pPb[nbins] = {0.2055, 0.3442, 0.4951, 0.5763, 0.5763};//ssc < 0.28
  //Double_t statErr_pPb[nbins] = {0.0084, 0.0125, 0.0199, 0.0257, 0.0257};//ssc < 0.28
  //Double_t purity_pPb[nbins]= {0.2047, 0.3359, 0.4489, 0.5114, 0.5114};//ssc < 0.33
  //Double_t statErr_pPb[nbins] = {0.0083, 0.0124, 0.0197, 0.0263, 0.0263};//ssc < 0.33
  //Double_t purity_pPb[nbins]= {0.2028, 0.3282, 0.4182, 0.4852, 0.4852};//ssc < 0.35
  //Double_t statErr_pPb[nbins] = {0.0083, 0.0122, 0.0193, 0.0263, 0.0263};//ssc < 0.35
  Double_t purity_pPb[nbins] = {0.210, 0.349, 0.477, 0.557, 0.557};//iso < 1.33
  Double_t statErr_pPb[nbins] = {0.018, 0.010, 0.012, 0.015, 0.015};//iso < 1.33
  //Double_t purity_pPb[nbins] = {0.207, 0.342, 0.476, 0.546, 0.546};
  //Double_t statErr_pPb[nbins] = {0.011, 0.012, 0.017, 0.018, 0.018};
  Double_t sigErr_pPb[nbins] = {0.011, 0.020, 0.019, 0.023, 0.023};
  Double_t antiErr_pPb[nbins] = {0.008, 0.016, 0.011, 0.024, 0.024};
  Double_t bkgErr_pPb[nbins] = {0.015, 0.012, 0.027, 0.011, 0.011};
  Double_t systErr_pPb[nbins] = {0.020, 0.028, 0.027, 0.039, 0.039};
  Double_t totsErr_pPb[nbins] = {0.0};
  Double_t PlusErr_pPb[nbins] = {0.0};
  Double_t MinusErr_pPb[nbins] = {0.0};

  for(int i = 0; i < nbins; i++){
    totsErr_pp[i] = TMath::Sqrt(TMath::Power(antiErr_pp[i], 2) + TMath::Power(bkgErr_pp[i], 2));
    totsErr_pPb[i] = TMath::Sqrt(TMath::Power(antiErr_pPb[i], 2) + TMath::Power(bkgErr_pPb[i], 2));
    //totsErr_pp[i] = systErr_pp[i];
    //totsErr_pPb[i] = systErr_pPb[i];
    
    PlusErr_pp[i] = purity_pp[i]+totsErr_pp[i];
    MinusErr_pp[i] = purity_pp[i]-totsErr_pp[i];
    PlusErr_pPb[i] = purity_pPb[i]+totsErr_pPb[i];
    MinusErr_pPb[i] = purity_pPb[i]-totsErr_pPb[i];

  }
  
  Double_t xBinCenters[nbins] = {13.198656, 16.903571, 22.064577, 30.107411, 45.0};
  Double_t xBinLeftErr[nbins] = {1.1986559999999997, 1.9035709999999995, 2.064577, 5.107410999999999, 5.0};
  Double_t xBinRightErr[nbins] = {1.8013440000000003, 3.0964290000000005, 2.935423, 9.892589000000001, 10.0};

  auto grPurity_pp = new TGraphAsymmErrors(nbins, xBinCenters, purity_pp, xBinLeftErr, xBinRightErr, statErr_pp, statErr_pp);
  grPurity_pp->SetTitle(";p_{T} [GeV/c]; purity");
  grPurity_pp->SetLineColor(kBlue);
  grPurity_pp->SetMarkerColor(kBlue);
  grPurity_pp->SetMarkerStyle(kFullCircle);

  auto grPurityPlus_pp = new TGraphAsymmErrors(nbins, xBinCenters, PlusErr_pp, xBinLeftErr, xBinRightErr, statErr_pp, statErr_pp);
  grPurityPlus_pp->SetTitle(";p_{T} [GeV/c]; purity");
  grPurityPlus_pp->SetLineColor(kBlue);
  grPurityPlus_pp->SetMarkerColor(kBlue);
  grPurityPlus_pp->SetMarkerStyle(kOpenTriangleDown);
  auto grPurityMinus_pp = new TGraphAsymmErrors(nbins, xBinCenters, MinusErr_pp, xBinLeftErr, xBinRightErr, statErr_pp, statErr_pp);
  grPurityMinus_pp->SetTitle(";p_{T} [GeV/c]; purity");
  grPurityMinus_pp->SetLineColor(kBlue);
  grPurityMinus_pp->SetMarkerColor(kBlue);
  grPurityMinus_pp->SetMarkerStyle(kOpenTriangleUp);
  
  

  auto grPurity_pPb = new TGraphAsymmErrors(nbins, xBinCenters, purity_pPb, xBinLeftErr, xBinRightErr, statErr_pPb, statErr_pPb);
  //grPurity_pPb->SetTitle("pPb purity");
  grPurity_pPb->SetLineColor(kRed);
  grPurity_pPb->SetMarkerColor(kRed);
  grPurity_pPb->SetMarkerStyle(kFullCircle);

  auto grPurityPlus_pPb = new TGraphAsymmErrors(nbins, xBinCenters, PlusErr_pPb, xBinLeftErr, xBinRightErr, statErr_pPb, statErr_pPb);
  grPurityPlus_pPb->SetTitle(";p_{T} [GeV/c]; purity");
  grPurityPlus_pPb->SetLineColor(kRed);
  grPurityPlus_pPb->SetMarkerColor(kRed);
  grPurityPlus_pPb->SetMarkerStyle(kOpenTriangleDown);
  auto grPurityMinus_pPb = new TGraphAsymmErrors(nbins, xBinCenters, MinusErr_pPb, xBinLeftErr, xBinRightErr, statErr_pPb, statErr_pPb);
  grPurityMinus_pPb->SetTitle(";p_{T} [GeV/c]; purity");
  grPurityMinus_pPb->SetLineColor(kRed);
  grPurityMinus_pPb->SetMarkerColor(kRed);
  grPurityMinus_pPb->SetMarkerStyle(kOpenTriangleUp);

  TF1* erf = new TF1("erf","[0]*TMath::Erf((x-[1])/[2])",12,40);
  erf->SetParameter(0,0.55);
  erf->SetParameter(1,8.0);
  erf->SetParameter(2,12.0);

  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->DrawFrame(12, 0.0, 40, 0.6);
  grPurity_pp->Draw("p");
  grPurityPlus_pp->Draw("psame");
  grPurityMinus_pp->Draw("psame*");
  grPurity_pp->GetXaxis()->SetRangeUser(12,40);
  grPurityPlus_pp->GetXaxis()->SetRangeUser(12,40);
  grPurityMinus_pp->GetXaxis()->SetRangeUser(12,40);
  c1->Update();
 
  grPurity_pp->Fit("erf", "Q EX0", "", 12, 55);
  grPurityPlus_pp->Fit("erf", "Q EX0", "", 12, 55);
  grPurityMinus_pp->Fit("erf", "Q EX0", "", 12, 55);  
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
  l1->SetHeader("pp purity");
  l1->AddEntry(grPurity_pp, "central value (CV)");
  l1->AddEntry(grPurityPlus_pp, "CV + #sigma");
  l1->AddEntry(grPurityMinus_pp, "CV - #sigma");
  l1->Draw("same");
  //c1->SaveAs("purityFits_pp.pdf");

  cout << "pp parameters" << endl;
  cout << "CV parameters" << endl;
  cout << "#chi^{2}: " << erf_pp->GetChisquare()
       << "\tNDF" << erf_pp->GetNDF()
       << "\t#chi^{2}/NDF: " << erf_pp->GetChisquare()/erf_pp->GetNDF() << endl;
  cout << "p0: " << erf_pp->GetParameter(0) << "+/-" << erf_pp->GetParError(0)
       << "\tp1: " << erf_pp->GetParameter(1) << "+/-" << erf_pp->GetParError(1)
       << "\tp2: " << erf_pp->GetParameter(2) << "+/-" << erf_pp->GetParError(2) << endl;
  cout << "CV+#sigma parameters" << endl;
  cout << "#chi^{2}: " << erfPlus_pp->GetChisquare()
       << "\tNDF" << erfPlus_pp->GetNDF()
       << "\t#chi^{2}/NDF: " << erfPlus_pp->GetChisquare()/erfPlus_pp->GetNDF() << endl;
  cout << "p0: " << erfPlus_pp->GetParameter(0) << "+/-" << erfPlus_pp->GetParError(0)
       << "\tp1: " << erfPlus_pp->GetParameter(1) << "+/-" << erfPlus_pp->GetParError(1)
       << "\tp2: " << erfPlus_pp->GetParameter(2) << "+/-" << erfPlus_pp->GetParError(2) << endl;
  cout << "CV-#sigma parameters" << endl;
  cout << "#chi^{2}: " << erfMinus_pp->GetChisquare()
       << "\tNDF" << erfMinus_pp->GetNDF()
       << "\t#chi^{2}/NDF: " << erfMinus_pp->GetChisquare()/erfMinus_pp->GetNDF() << endl;
  cout << "p0: " << erfMinus_pp->GetParameter(0) << "+/-" << erfMinus_pp->GetParError(0)
       << "\tp1: " << erfMinus_pp->GetParameter(1) << "+/-" << erfMinus_pp->GetParError(1)
       << "\tp2: " << erfMinus_pp->GetParameter(2) << "+/-" << erfMinus_pp->GetParError(2) << endl;//*/

  TCanvas* c2 = new TCanvas("c2", "c2");
  c2->DrawFrame(12, 0.0, 40, 0.6);
  grPurity_pPb->Draw("p");
  grPurityPlus_pPb->Draw("psame");
  grPurityMinus_pPb->Draw("psame");
  grPurity_pPb->GetXaxis()->SetRangeUser(12,40);
  grPurityPlus_pPb->GetXaxis()->SetRangeUser(12,40);
  grPurityMinus_pPb->GetXaxis()->SetRangeUser(12,40);
  c2->Update();
 
  grPurity_pPb->Fit("erf", "Q EX0", "", 12, 55);
  grPurityPlus_pPb->Fit("erf", "Q EX0", "", 12, 55);
  grPurityMinus_pPb->Fit("erf", "Q EX0", "", 12, 55);  
  TF1* erf_pPb = grPurity_pPb->GetFunction("erf");
  erf_pPb->SetLineColor(kRed);
  erf_pPb->SetLineWidth(5);
  erf_pPb->Draw("same");//*/
  TF1* erfPlus_pPb = grPurityPlus_pPb->GetFunction("erf");
  erfPlus_pPb->SetLineColor(kRed);
  erfPlus_pPb->SetLineStyle(kDashed);
  erfPlus_pPb->SetLineWidth(5);
  erfPlus_pPb->Draw("same");//*/
  TF1* erfMinus_pPb = grPurityMinus_pPb->GetFunction("erf");
  erfMinus_pPb->SetLineColor(kRed);
  erfMinus_pPb->SetLineStyle(kDashed);
  erfMinus_pPb->SetLineWidth(5);
  erfMinus_pPb->Draw("same");//*/

  TLegend* l2 = new TLegend(0.5, 0.2, 0.85, 0.5);
  l2->SetHeader("p-Pb purity");
  l2->AddEntry(grPurity_pPb, "central value (CV)");
  l2->AddEntry(grPurityPlus_pPb, "CV + #sigma");
  l2->AddEntry(grPurityMinus_pPb, "CV - #sigma");
  l2->Draw("same");
  c2->SaveAs("purityFits_pPb.pdf");

  cout << "pPb parameters" << endl;
  cout << "CV parameters" << endl;
  cout << "#chi^{2}: " << erf_pPb->GetChisquare()
       << "\tNDF" << erf_pPb->GetNDF()
       << "\t#chi^{2}/NDF: " << erf_pPb->GetChisquare()/erf_pPb->GetNDF() << endl;
  cout << "p0: " << erf_pPb->GetParameter(0) << "+/-" << erf_pPb->GetParError(0)
       << "\tp1: " << erf_pPb->GetParameter(1) << "+/-" << erf_pPb->GetParError(1)
       << "\tp2: " << erf_pPb->GetParameter(2) << "+/-" << erf_pPb->GetParError(2) << endl;
  cout << "CV+#sigma parameters" << endl;
  cout << "#chi^{2}: " << erfPlus_pPb->GetChisquare()
       << "\tNDF" << erfPlus_pPb->GetNDF()
       << "\t#chi^{2}/NDF: " << erfPlus_pPb->GetChisquare()/erfPlus_pPb->GetNDF() << endl;
  cout << "p0: " << erfPlus_pPb->GetParameter(0) << "+/-" << erfPlus_pPb->GetParError(0)
       << "\tp1: " << erfPlus_pPb->GetParameter(1) << "+/-" << erfPlus_pPb->GetParError(1)
       << "\tp2: " << erfPlus_pPb->GetParameter(2) << "+/-" << erfPlus_pPb->GetParError(2) << endl;
  cout << "CV-#sigma parameters" << endl;
  cout << "#chi^{2}: " << erfMinus_pPb->GetChisquare()
       << "\tNDF" << erfMinus_pPb->GetNDF()
       << "\t#chi^{2}/NDF: " << erfMinus_pPb->GetChisquare()/erfMinus_pPb->GetNDF() << endl;
  cout << "p0: " << erfMinus_pPb->GetParameter(0) << "+/-" << erfMinus_pPb->GetParError(0)
       << "\tp1: " << erfMinus_pPb->GetParameter(1) << "+/-" << erfMinus_pPb->GetParError(1)
       << "\tp2: " << erfMinus_pPb->GetParameter(2) << "+/-" << erfMinus_pPb->GetParError(2) << endl;//*/

  
}//end function
