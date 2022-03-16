void Trigger_norm()
{
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  gStyle->SetFillColor(10);
  gStyle->SetCanvasColor(10);
  gStyle->SetFrameFillColor(10);
  gStyle->SetLabelSize(0.05,"x"); 
  gStyle->SetTitleSize(0.05,"x"); 
  gStyle->SetLabelSize(0.05,"y"); 
  gStyle->SetTitleSize(0.05,"y"); 
  gStyle->SetTitleOffset(1.0,"x"); 
  gStyle->SetStatBorderSize(0);
  gStyle->SetStatColor(10);
  gStyle->SetOptTitle(1);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetCanvasColor(10);
  gStyle->SetTitleSize(0.05,"Y");
  gStyle->SetTitleOffset(0.9);
  gStyle->UseCurrentStyle(); 
  
  
  
  TFile *f = new TFile("/global/homes/d/ddixit/AnalysisResults_scalar1.root");
  TDirectoryFile *ld = (TDirectoryFile*) f->Get(Form("EmcalTriggerNormtask"));
  ld->Print();
  TList *l = (TList*) ld->Get(Form("EmcalNormalizationHistograms"));
  
  l->Print();
  
  TH2F * hTriggerNorm = (TH2F*) l->FindObject("hTriggerNorm");
  
  //TH2F * hTriggerNorm = (TH2F*) l->FindObject("fHistTriggerClasses");
  
  printf("Number of bins X = %d\n", hTriggerNorm->GetNbinsX());
  printf("Number of bins Y = %d\n", hTriggerNorm->GetNbinsY());
  
  
  Double_t Nbin1 = hTriggerNorm->GetBinContent(1,100); //weighted values 
  Double_t Nbin2 = hTriggerNorm->GetBinContent(2,100);
  Double_t Nbin3 = hTriggerNorm->GetBinContent(3,100);
  Double_t Nbin4 = hTriggerNorm->GetBinContent(4,100);
  Double_t Nbin5 = hTriggerNorm->GetBinContent(5,100);
  Double_t Nbin6 = hTriggerNorm->GetBinContent(6,100);
  Double_t Nbin7 = hTriggerNorm->GetBinContent(7,100);
  Double_t Nbin8 = hTriggerNorm->GetBinContent(8,100);
  
  printf("%f, %f, %f, %f, %f, %f, %f, %f\n", Nbin1, Nbin2, Nbin3, Nbin4, Nbin5, Nbin6, Nbin7, Nbin8);
  
  printf("RF: %f, %f, %f, %f, %f, %f, %f\n", Nbin1/Nbin2, Nbin1/Nbin3, Nbin1/Nbin4, Nbin1/Nbin5, Nbin1/Nbin6, Nbin1/Nbin7, Nbin1/Nbin8);
  
  Double_t RF_rel_error_EG1 = TMath::Sqrt(1./Nbin1 + 1./Nbin2);
  Double_t RF_rel_error_EG2 = TMath::Sqrt(1./Nbin1 + 1./Nbin3);
  
  printf("err EG1 = %f, err EG2 = %f \n", RF_rel_error_EG1, RF_rel_error_EG2);
  
  
  
  
}
