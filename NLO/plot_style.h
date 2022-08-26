void mc(int number = 0, int xp = 0, int yp = 0, int x = 400, int y = 400, double pleft = 0.17, double pright = 0.1, double ptop = 0.1, double pbot = 0.13){
  char name[100];
  sprintf(name,"cc%d",number);
  TPad *mpad;
  if(gROOT->GetListOfCanvases()->FindObject(name)==NULL){
    TCanvas* c = new TCanvas(name,name, xp, yp, x, y);
    gStyle->SetOptStat(0); gStyle->SetOptTitle(0);
    gStyle->SetMarkerSize(1.6);
    c->cd();
    sprintf(name,"mpad%d",number);  
    mpad = new TPad(name,name,0.02,0.02,0.99,0.99,0,0,0);
    mpad->SetTickx();
    mpad->SetTicky();
    mpad->SetTopMargin(ptop);
    mpad->SetBottomMargin(pbot);
    mpad->SetLeftMargin(pleft);
    mpad->SetRightMargin(pright);
    mpad->SetLogy(1);
    mpad->Draw();
    mpad->cd();
  c->Modified();
  c->Update();
  }
  else {
    TCanvas *tmp = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name);
    tmp->cd();
    mpad->cd();
  tmp->Modified();
  tmp->Update();  
  }
  gSystem->ProcessEvents();
}

void mcs(int number = 0, int xp = 0, int yp = 0, int x = 400, int y = 400, double pleft = 0.17, double pright = 0.1, double ptop = 0.1, double pbot = 0.13){
  char name[100];
  sprintf(name,"cc%d",number);
  TPad *mpad;
  if(gROOT->GetListOfCanvases()->FindObject(name)==NULL){
    TCanvas* c = new TCanvas(name,name, xp, yp, x, y);
    gStyle->SetOptStat(0); gStyle->SetOptTitle(0);
    gStyle->SetMarkerSize(1.6);
    c->cd();
    sprintf(name,"mpad%d",number);  
    mpad = new TPad(name,name,0.02,0.02,0.99,0.99,0,0,0);
    mpad->SetTickx();
    mpad->SetTicky();
    mpad->SetTopMargin(ptop);
    mpad->SetBottomMargin(pbot);
    mpad->SetLeftMargin(pleft);
    mpad->SetRightMargin(pright);
    mpad->Draw();
    mpad->cd();
  c->Modified();
  c->Update();
  }
  else {
    TCanvas *tmp = (TCanvas*)gROOT->GetListOfCanvases()->FindObject(name);
    tmp->cd();
    mpad->cd();
  tmp->Modified();
  tmp->Update();  
  }
  gSystem->ProcessEvents();
}

void myhset(TH1F *href, double xtitoff = 1.0,  double ytitoff = 1., double xtitsize = 0.06,  double ytitsize = 0.07){
  href->GetXaxis()->CenterTitle(1);
  href->GetYaxis()->CenterTitle(1);
  href->GetXaxis()->SetTitleOffset(xtitoff);
  href->GetYaxis()->SetTitleOffset(ytitoff);
  href->GetXaxis()->SetTitleSize(xtitsize);
  href->GetYaxis()->SetTitleSize(ytitsize);
  href->GetXaxis()->SetLabelOffset(0.01);
  href->GetYaxis()->SetLabelOffset(0.001);
  href->GetXaxis()->SetLabelSize(0.5);
  href->GetYaxis()->SetLabelSize(0.5);
  href->GetXaxis()->SetNdivisions(505);
  href->GetYaxis()->SetNdivisions(505);
}
void myhset(TH1D *href, double xtitoff = 1.0,  double ytitoff = 1., double xtitsize = 0.06,  double ytitsize = 0.07){
  href->GetXaxis()->CenterTitle(1);
  href->GetYaxis()->CenterTitle(1);
  href->GetXaxis()->SetTitleOffset(xtitoff);
  href->GetYaxis()->SetTitleOffset(ytitoff);
  href->GetXaxis()->SetTitleSize(xtitsize);
  href->GetYaxis()->SetTitleSize(ytitsize);
  href->GetXaxis()->SetLabelOffset(0.01);
  href->GetYaxis()->SetLabelOffset(0.001);
  href->GetXaxis()->SetLabelSize(0.045);
  href->GetYaxis()->SetLabelSize(0.045);
  href->GetXaxis()->SetNdivisions(505);
  href->GetYaxis()->SetNdivisions(505);
}

void myhset(TH2F *href, double xtitoff = 1.0,  double ytitoff = 1.4, double xtitsize = 0.06,  double ytitsize = 0.06){
  // href->GetXaxis()->CenterTitle(1);
  // href->GetYaxis()->CenterTitle(1);
  href->GetXaxis()->SetTitleOffset(xtitoff);
  href->GetYaxis()->SetTitleOffset(ytitoff);
  href->GetXaxis()->SetTitleSize(xtitsize);
  href->GetYaxis()->SetTitleSize(ytitsize);
  href->GetXaxis()->SetLabelOffset(0.01);
  href->GetYaxis()->SetLabelOffset(0.01);
  href->GetXaxis()->SetLabelSize(0.045);
  href->GetYaxis()->SetLabelSize(0.045);
  href->GetXaxis()->SetNdivisions(505);
  href->GetYaxis()->SetNdivisions(505);
}

void myhset(TH2D *href, double xtitoff = 1.0,  double ytitoff = 1., double xtitsize = 0.06,  double ytitsize = 0.07){
  href->GetXaxis()->CenterTitle(1);
  href->GetYaxis()->CenterTitle(1);
  href->GetXaxis()->SetTitleOffset(xtitoff);
  href->GetYaxis()->SetTitleOffset(ytitoff);
  href->GetXaxis()->SetTitleSize(xtitsize);
  href->GetYaxis()->SetTitleSize(ytitsize);
  href->GetXaxis()->SetLabelOffset(0.01);
  href->GetYaxis()->SetLabelOffset(0.01);
  href->GetXaxis()->SetLabelSize(0.045);
  href->GetYaxis()->SetLabelSize(0.045);
  href->GetXaxis()->SetNdivisions(505);
  href->GetYaxis()->SetNdivisions(505);
}

void myhset(TH3F *href, double xtitoff = 1.6,  double ytitoff = 1.6, double ztitoff = 1.4, double xtitsize = 0.06, double ytitsize = 0.06, double ztitsize = 0.06){
  href->GetXaxis()->SetTitleOffset(xtitoff);
  href->GetYaxis()->SetTitleOffset(ytitoff);
  href->GetZaxis()->SetTitleOffset(ztitoff);
  href->GetXaxis()->SetTitleSize(xtitsize);
  href->GetYaxis()->SetTitleSize(ytitsize);
  href->GetZaxis()->SetTitleSize(ztitsize);
  href->GetXaxis()->SetLabelOffset(0.01);
  href->GetYaxis()->SetLabelOffset(0.01);
  href->GetZaxis()->SetLabelOffset(0.01);
  href->GetXaxis()->SetLabelSize(0.045);
  href->GetYaxis()->SetLabelSize(0.045);
  href->GetZaxis()->SetLabelSize(0.045);
  href->GetXaxis()->SetNdivisions(505);
  href->GetYaxis()->SetNdivisions(505);
  href->GetZaxis()->SetNdivisions(505);
}