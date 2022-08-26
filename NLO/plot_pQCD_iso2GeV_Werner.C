#include "pQCD_iso2GeV_Werner.h"
#include "plot_style.h"

using namespace std;

TH1F* h_8TeV_pPb = NULL;
TH1F* h_8TeV_pp = NULL;
TH1F* h_5TeV_pp = NULL;
TH1F* h_5TeV_pPb = NULL;
TH1F* h_5TeV_wNL_pp = NULL;
TH1F* h_5TeV_wNL_pPb = NULL;

const int beamE_color[nbeamE] = {kRed, kBlue};
const int scale_lstyle[nscale] = {3, 1, 6};
const int scale_mstyle[nscale] = {24, 20, 21};

static int cno = 0;

const bool flag_use_average = false;

void set_pQCD_Werner()
{
    for (int ibeamE = 0; ibeamE < nbeamE; ++ibeamE)
    {
        for (int iscale = 0; iscale < nscale; ++iscale)
        {
            //==========================================
            //                   pp
            //==========================================
            g_pQCD_frag_pp[ibeamE][iscale] = new TGraphErrors(npt,pQCD_pt,pQCD_frag_pp[ibeamE][iscale],0,0);
            g_pQCD_direct_pp[ibeamE][iscale] = new TGraphErrors(npt,pQCD_pt,pQCD_direct_pp[ibeamE][iscale],0,0);
            g_pQCD_sum_pp[ibeamE][iscale] = new TGraphErrors(npt,pQCD_pt,pQCD_sum_pp[ibeamE][iscale],0,0);
            cout << "diag: " << pQCD_sum_pp[0][1][10] << " " << pQCD_sum_pp[1][1][10] << endl;
            g_pQCD_frag_pp[ibeamE][iscale]->SetLineWidth(2);
            g_pQCD_direct_pp[ibeamE][iscale]->SetLineWidth(2);
            g_pQCD_sum_pp[ibeamE][iscale]->SetLineWidth(2);
        }
    }
}

double average_pQCD_calculation(double range_lo, double range_hi, TGraphErrors* g_pQCD)
{ // return integral over a bin range / bin width
    TF1 fit_func("fit_func","[0]/(pow(exp(-[1]*x)+x/[2],[3]))",0.0,100);
    fit_func.SetParameter(0,1E3);
    fit_func.SetParameter(1,0.5);
    fit_func.SetParameter(2,0.5);
    fit_func.SetParameter(3,8);

    double* g_pQCD_x = (double*)g_pQCD->GetX();
    double* g_pQCD_y = (double*)g_pQCD->GetY();
    double g_pQCD_fit_x[npt] = {0};
    double g_pQCD_fit_y[npt] = {0};
    double g_pQCD_fit_yerr[npt] = {0};
    for (int ipt = 0; ipt < npt; ++ipt)
    {
        g_pQCD_fit_x[ipt] = g_pQCD_x[ipt];
        g_pQCD_fit_y[ipt] = g_pQCD_y[ipt];
        g_pQCD_fit_yerr[ipt] = g_pQCD_y[ipt]*0.01;
    }
    TGraphErrors* g_pQCD_fit = new TGraphErrors(npt,g_pQCD_fit_x,g_pQCD_fit_y,0,g_pQCD_fit_yerr); // add artifial yerr just to make the fitting produre easier

    double range_center = 0.5*(range_lo+range_hi);
    double range_width = range_hi-range_lo;
    double fit_range_lo = range_center - 0.5*range_width; // currently using the bin width as fitting range
    double fit_range_hi = range_center + 0.5*range_width;
    if (fit_range_lo<6) fit_range_lo = 6;
    if (fit_range_hi>70) fit_range_hi = 70;
    g_pQCD_fit->Fit(&fit_func,"0R","",fit_range_lo,fit_range_hi);

    double integral = fit_func.Integral(range_lo,range_hi);
    cout << "range " << range_lo << "-" << range_hi << " integral/bin width " << integral/range_width << " compare to " << g_pQCD->Eval(range_center) << endl;
    return integral/(range_hi-range_lo);
}

void compare_scale()
{
    for (int isys = 0; isys < nsys; ++isys)
    {
        for (int ibeamE = 0; ibeamE < nbeamE; ++ibeamE)
        {
            mc(cno++);
            {
                float plot_xrange_lo = 0;
                float plot_xrange_hi = 70;

                float plot_yrange_lo = 0.5*nucleon[isys]*TMath::MinElement(npt,pQCD_sum_pp[ibeamE][0]);
                float plot_yrange_hi = 1.5*nucleon[isys]*TMath::MaxElement(npt,pQCD_sum_pp[ibeamE][0]);

                TH2F* htemp = new TH2F("htemp","",10,plot_xrange_lo,plot_xrange_hi,10,plot_yrange_lo,plot_yrange_hi);
                htemp->Draw();
                htemp->GetYaxis()->SetTitle("d^{2}#sigma/dp_{T}dy [nb(GeV/c)^{-1}]");
                htemp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
                myhset(htemp,1.2,1.6,0.05,0.045);

                TLegend* leg = new TLegend(0.62,0.56,0.85,0.71);
                leg->SetBorderSize(0);
                leg->SetTextSize(0.035);
                leg->SetFillStyle(0);
                leg->SetMargin(0.3); 

                TLegend* leg_data = new TLegend(0.62,0.38,0.85,0.49);
                leg_data->SetBorderSize(0);
                leg_data->SetTextSize(0.035);
                leg_data->SetFillStyle(0);
                leg_data->SetMargin(0.3); 

                if (isys==0 && ibeamE==0)
                {
                    h_5TeV_pp->SetMarkerSize(1);
                    h_5TeV_pp->SetMarkerStyle(24);
                    h_5TeV_pp->SetMarkerColor(kGreen+2);
                    h_5TeV_pp->SetLineColor(kGreen+2);
                    h_5TeV_pp->Draw("psame");
                    leg_data->AddEntry(h_5TeV_pp,"w/o NL","p");

                    h_5TeV_wNL_pp->SetMarkerSize(1);
                    h_5TeV_wNL_pp->SetMarkerStyle(20);
                    h_5TeV_wNL_pp->SetMarkerColor(kGreen+2);
                    h_5TeV_wNL_pp->SetLineColor(kGreen+2);
                    h_5TeV_wNL_pp->Draw("psame");
                    leg_data->AddEntry(h_5TeV_wNL_pp,"w/ NL","p");
                }
                if (isys==0 && ibeamE==1)
                {
                    h_8TeV_pp->SetMarkerSize(1);
                    h_8TeV_pp->SetMarkerStyle(20);
                    h_8TeV_pp->SetMarkerColor(kViolet);
                    h_8TeV_pp->Draw("psame");
                }

                for (int iscale = 0; iscale < nscale; ++iscale)
                {
                    if (isys==0)
                    {
                        g_pQCD_sum_pp[ibeamE][iscale]->SetLineStyle(scale_lstyle[iscale]);
                        g_pQCD_sum_pp[ibeamE][iscale]->Draw("csame");
                        leg->AddEntry(g_pQCD_sum_pp[ibeamE][iscale],Form("#mu = %.1f",scale[iscale]),"l");
                    }
                }
                leg->Draw("same");
                leg_data->Draw("same");

                TLatex* tl = new TLatex();
                tl->SetTextAlign(11);
                tl->SetTextSize(0.04);
                tl->DrawLatexNDC(0.2,0.83,Form("%s %.2f TeV",sys_name[isys],beamE[ibeamE]));

                TLatex* tl_pQCD = new TLatex();
                tl_pQCD->SetTextAlign(11);
                tl_pQCD->SetTextSize(0.032);
                tl_pQCD->DrawLatexNDC(0.62,0.84,"NLO pQCD");
                tl_pQCD->DrawLatexNDC(0.62,0.80,"(by W. Vogelsang)");
                tl_pQCD->DrawLatexNDC(0.62,0.76,"NNPDF3.0 PDF");
                tl_pQCD->DrawLatexNDC(0.62,0.72,"GRV FF");

                gROOT->ProcessLine( Form("cc%d->Print(\"pQCD_NLO_iso2GeV_%s_%s_scale_comparison.pdf\")", cno-1, sys_abbr[isys], beamE_abbr[ibeamE]) );
            }
            
            TGraphErrors* g_pQCD_data_ratio[nscale] = {0};
            for (int iscale = 0; iscale < nscale; ++iscale)
            {
                double ratio_pt[100] = {0};
                double ratio_scale[100] = {0};
                int ratio_npt = 0;

                int nbins = h_5TeV_pPb->GetNbinsX();
                if (isys==0 && ibeamE==0) nbins = h_5TeV_pp->GetNbinsX();
                if (isys==0 && ibeamE==1) nbins = h_8TeV_pp->GetNbinsX();
                for (int ibin = 1; ibin < nbins+1; ++ibin)
                {
                    double temp_center = h_5TeV_pp->GetXaxis()->GetBinCenter(ibin);
                    double temp_width = h_5TeV_pp->GetXaxis()->GetBinWidth(ibin);
                    if (ibeamE==1) 
                    {
                        temp_center = h_8TeV_pp->GetXaxis()->GetBinCenter(ibin);
                        temp_width = h_8TeV_pp->GetXaxis()->GetBinWidth(ibin);
                    }
                    if (temp_center<11) continue;

                    ratio_pt[ratio_npt] = temp_center;

                    double bin_edge_left = temp_center-0.5*temp_width;
                    double bin_edge_right = temp_center+0.5*temp_width;
                    double average_calculation = 9999;
                    if (isys==0) average_calculation = average_pQCD_calculation(bin_edge_left,bin_edge_right,g_pQCD_sum_pp[ibeamE][iscale]);
                    
                    if (flag_use_average)
                    {
                        if (isys==0 && ibeamE==0) ratio_scale[ratio_npt] = h_5TeV_wNL_pp->GetBinContent(ibin)/average_calculation;
                        if (isys==0 && ibeamE==1) ratio_scale[ratio_npt] = h_8TeV_pp->GetBinContent(ibin)/average_calculation;
                    }
                    else
                    {
                        if (isys==0 && ibeamE==0) ratio_scale[ratio_npt] = h_5TeV_wNL_pp->GetBinContent(ibin)/g_pQCD_sum_pp[ibeamE][iscale]->Eval(ratio_pt[ratio_npt]);
                        if (isys==0 && ibeamE==1) ratio_scale[ratio_npt] = h_8TeV_pp->GetBinContent(ibin)/g_pQCD_sum_pp[ibeamE][iscale]->Eval(ratio_pt[ratio_npt]);
                    }

                    cout << "ipt " << ratio_npt << " " << ratio_pt[ratio_npt] << " " << ratio_scale[ratio_npt] << endl;
                    ratio_npt++;
                }

                g_pQCD_data_ratio[iscale] = new TGraphErrors(ratio_npt,ratio_pt,ratio_scale,0,0);
                g_pQCD_data_ratio[iscale]->SetMarkerStyle(scale_mstyle[iscale]);
                g_pQCD_data_ratio[iscale]->SetMarkerSize(0.8);
                g_pQCD_data_ratio[iscale]->SetLineWidth(2);
                g_pQCD_data_ratio[iscale]->SetLineStyle(scale_lstyle[iscale]);
                g_pQCD_data_ratio[iscale]->SetLineColor(kBlack);
            }

            mcs(cno++);
            {
                float plot_xrange_lo = 0;
                float plot_xrange_hi = 70;

                float plot_yrange_lo = 0.0;
                float plot_yrange_hi = 2.0;

                TH2F* htemp = new TH2F("htemp","",10,plot_xrange_lo,plot_xrange_hi,10,plot_yrange_lo,plot_yrange_hi);
                htemp->Draw();
                htemp->GetYaxis()->SetTitle("data / NLO pQCD");
                htemp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
                myhset(htemp,1.2,1.6,0.05,0.045);

                TLegend* leg = new TLegend(0.62,0.18,0.85,0.33);
                leg->SetBorderSize(0);
                leg->SetTextSize(0.035);
                leg->SetFillStyle(0);
                leg->SetMargin(0.3); 

                for (int iscale = 0; iscale < nscale; ++iscale)
                {
                    g_pQCD_data_ratio[iscale]->Draw("psame");
                    leg->AddEntry(g_pQCD_data_ratio[iscale],Form("#mu = %.1f",scale[iscale]),"p");
                }
                leg->Draw("same");

                TLine* line1 = new TLine(plot_xrange_lo,1,plot_xrange_hi,1);
                line1->SetLineWidth(2);
                line1->SetLineStyle(7);
                line1->Draw("same");

                TLatex* tl = new TLatex();
                tl->SetTextAlign(11);
                tl->SetTextSize(0.04);
                tl->DrawLatexNDC(0.2,0.83,Form("%s %.2f TeV",sys_name[isys],beamE[ibeamE]));

                gROOT->ProcessLine( Form("cc%d->Print(\"pQCD_NLO_iso2GeV_%s_%s_ratio.pdf\")", cno-1, sys_abbr[isys], beamE_abbr[ibeamE]) );
            }
        }
    }
}

void compare_component()
{
    for (int isys = 0; isys < nsys; ++isys)
    {
        for (int ibeamE = 0; ibeamE < nbeamE; ++ibeamE)
        {
            int iscale = 1;
            mc(cno++);
            {
                float plot_xrange_lo = 0;
                float plot_xrange_hi = 70;

                float plot_yrange_lo = 0.5*TMath::MinElement(npt,pQCD_direct_pp[ibeamE][iscale]);
                float plot_yrange_hi = 1.5*TMath::MaxElement(npt,pQCD_direct_pp[ibeamE][iscale]);

                TH2F* htemp = new TH2F("htemp","",10,plot_xrange_lo,plot_xrange_hi,10,plot_yrange_lo,plot_yrange_hi);
                htemp->Draw();
                htemp->GetYaxis()->SetTitle("Cross section");
                htemp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
                myhset(htemp,1.2,1.6,0.05,0.045);

                TLegend* leg = new TLegend(0.62,0.68,0.85,0.83);
                leg->SetBorderSize(0);
                leg->SetTextSize(0.035);
                leg->SetFillStyle(0);
                leg->SetMargin(0.3); 

                if (isys==0)
                {
                    g_pQCD_frag_pp[ibeamE][iscale]->SetLineColor(kRed);
                    g_pQCD_direct_pp[ibeamE][iscale]->SetLineColor(kBlue);
                    g_pQCD_sum_pp[ibeamE][iscale]->SetLineColor(kBlack);
                    g_pQCD_frag_pp[ibeamE][iscale]->Draw("csame");
                    g_pQCD_direct_pp[ibeamE][iscale]->Draw("csame");
                    g_pQCD_sum_pp[ibeamE][iscale]->Draw("csame");
                    leg->AddEntry(g_pQCD_sum_pp[ibeamE][iscale],"Isolated #gamma","l");
                    leg->AddEntry(g_pQCD_direct_pp[ibeamE][iscale],"Direct #gamma","l");
                    leg->AddEntry(g_pQCD_frag_pp[ibeamE][iscale],"Frag #gamma","l");
                }
                leg->Draw("same");

                TLatex* tl = new TLatex();
                tl->SetTextAlign(11);
                tl->SetTextSize(0.04);
                tl->DrawLatexNDC(0.2,0.83,Form("%s %.2f TeV",sys_name[isys],beamE[ibeamE]));

                gROOT->ProcessLine( Form("cc%d->Print(\"pQCD_NLO_iso2GeV_%s_%s_component_comparison.pdf\")", cno-1, sys_abbr[isys], beamE_abbr[ibeamE]) );
            }
        }
    }


    int isys = 0;
    int ibeamE = 0;
    int iscale = 1;
    double ratio_frag[npt] = {0};
    double ratio_direct[npt] = {0};
    for (int ipt = 0; ipt < npt; ++ipt)
    {
        if (isys==0)
        {
          ratio_frag[ipt] = pQCD_frag_pp[ibeamE][iscale][ipt]/pQCD_sum_pp[ibeamE][iscale][ipt];  
          ratio_direct[ipt] = pQCD_direct_pp[ibeamE][iscale][ipt]/pQCD_sum_pp[ibeamE][iscale][ipt];  
        }
    }
    TGraphErrors* g_pQCD_frag_ratio = new TGraphErrors(npt,pQCD_pt,ratio_frag,0,0);
    g_pQCD_frag_ratio->SetLineWidth(2);
    g_pQCD_frag_ratio->SetLineColor(kRed);
    TGraphErrors* g_pQCD_direct_ratio = new TGraphErrors(npt,pQCD_pt,ratio_direct,0,0);
    g_pQCD_direct_ratio->SetLineWidth(2);
    g_pQCD_direct_ratio->SetLineColor(kBlue);

    mcs(cno++);
    {
        float plot_xrange_lo = 0;
        float plot_xrange_hi = 70;

        float plot_yrange_lo = 0.0;
        float plot_yrange_hi = 1.0;

        TH2F* htemp = new TH2F("htemp","",10,plot_xrange_lo,plot_xrange_hi,10,plot_yrange_lo,plot_yrange_hi);
        htemp->Draw();
        htemp->GetYaxis()->SetTitle("Direct (Frag) #gamma / Isolated #gamma");
        htemp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
        myhset(htemp,1.2,1.6,0.05,0.045);

        TLegend* leg = new TLegend(0.62,0.68,0.85,0.83);
        leg->SetBorderSize(0);
        leg->SetTextSize(0.035);
        leg->SetFillStyle(0);
        leg->SetMargin(0.3); 

        g_pQCD_frag_ratio->Draw("csame");
        g_pQCD_direct_ratio->Draw("csame");

        leg->AddEntry(g_pQCD_direct_ratio,"Direct #gamma","l");
        leg->AddEntry(g_pQCD_frag_ratio,"Frag #gamma","l");
        leg->Draw("same");

        TLatex* tl = new TLatex();
        tl->SetTextAlign(11);
        tl->SetTextSize(0.04);
        tl->DrawLatexNDC(0.2,0.83,Form("%s",sys_name[isys]));

        gROOT->ProcessLine( Form("cc%d->Print(\"pQCD_NLO_iso2GeV_%s_%s_component_ratio.pdf\")", cno-1, sys_abbr[isys], beamE_abbr[ibeamE]) );
    }
}

void compare_beamE()
{
    int isys = 0;
    int ibeamE = 0;
    int iscale = 1;
    mc(cno++);
    {
        float plot_xrange_lo = 0;
        float plot_xrange_hi = 70;

        float plot_yrange_lo = 0.5*TMath::MinElement(npt,pQCD_sum_pp[ibeamE][iscale]);
        float plot_yrange_hi = 1.5*TMath::MaxElement(npt,pQCD_sum_pp[ibeamE][iscale]);

        TH2F* htemp = new TH2F("htemp","",10,plot_xrange_lo,plot_xrange_hi,10,plot_yrange_lo,plot_yrange_hi);
        htemp->Draw();
        htemp->GetYaxis()->SetTitle("Cross section");
        htemp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
        myhset(htemp,1.2,1.6,0.05,0.045);

        TLegend* leg = new TLegend(0.62,0.68,0.85,0.83);
        leg->SetBorderSize(0);
        leg->SetTextSize(0.035);
        leg->SetFillStyle(0);
        leg->SetMargin(0.3); 

        for (int ibeamE = 0; ibeamE < nbeamE; ++ibeamE)
        {
            if (isys==0)
            {
                g_pQCD_sum_pp[ibeamE][iscale]->SetLineColor(beamE_color[ibeamE]);
                g_pQCD_sum_pp[ibeamE][iscale]->Draw("csame");
                leg->AddEntry(g_pQCD_sum_pp[ibeamE][iscale],Form("%.2f TeV",beamE[ibeamE]),"l");
            }
        }
        leg->Draw("same");

        TLatex* tl = new TLatex();
        tl->SetTextAlign(11);
        tl->SetTextSize(0.04);
        tl->DrawLatexNDC(0.2,0.83,Form("%s",sys_name[isys]));

        gROOT->ProcessLine( Form("cc%d->Print(\"pQCD_NLO_iso2GeV_%s_beamE_comparison.pdf\")", cno-1, sys_abbr[isys]) );
    }

    double ratio_beamE[npt] = {0};
    for (int ipt = 0; ipt < npt; ++ipt)
    {
        if (isys==0) ratio_beamE[ipt] = pQCD_sum_pp[1][iscale][ipt]/pQCD_sum_pp[0][iscale][ipt];
    }
    TGraphErrors* g_pQCD_sum_ratio = new TGraphErrors(npt,pQCD_pt,ratio_beamE,0,0);
    g_pQCD_sum_ratio->SetLineWidth(2);
    g_pQCD_sum_ratio->SetLineColor(kBlack);

    mcs(cno++);
    {
        float plot_xrange_lo = 0;
        float plot_xrange_hi = 70;

        float plot_yrange_lo = 0.5;
        float plot_yrange_hi = 2.5;

        TH2F* htemp = new TH2F("htemp","",10,plot_xrange_lo,plot_xrange_hi,10,plot_yrange_lo,plot_yrange_hi);
        htemp->Draw();
        htemp->GetYaxis()->SetTitle(Form("%.2f TeV / %.2f TeV",beamE[1],beamE[0]));
        htemp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
        myhset(htemp,1.2,1.6,0.05,0.045);

        g_pQCD_sum_ratio->Draw("csame");

        TLatex* tl = new TLatex();
        tl->SetTextAlign(11);
        tl->SetTextSize(0.04);
        tl->DrawLatexNDC(0.2,0.83,Form("%s",sys_name[isys]));

        gROOT->ProcessLine( Form("cc%d->Print(\"pQCD_NLO_iso2GeV_%s_beamE_ratio.pdf\")", cno-1, sys_abbr[isys]) );
    }
}

void set_real_data()
{
  TFile* fin1 = new TFile("/project/projectdirs/alice/ddixit/isoPhotonRootFiles/compairison8TeV5TeV_RF991.root");
  TFile* fin2 = new TFile("/project/projectdirs/alice/ddixit/isoPhotonRootFiles/StdCuts_EX0PurityFit.root");
  TFile* fin3 = new TFile("/project/projectdirs/alice/ddixit/isoPhotonRootFiles/StdCuts_EX0PurityFit_nonLinPurity_ppNonLin.root");
  h_8TeV_pPb = (TH1F*)fin1->Get("hEG1_8TeVCS_pPb");
  h_8TeV_pp = (TH1F*)fin1->Get("hEG1-8TeVCS_pp");
  h_5TeV_pp = (TH1F*)fin2->Get("crossSection_pp");
  h_5TeV_pPb = (TH1F*)fin2->Get("crossSection_pPb");
  h_5TeV_wNL_pp = (TH1F*)fin3->Get("crossSection_pp");
  h_5TeV_wNL_pPb = (TH1F*)fin3->Get("crossSection_pPb");
}

void plot_pQCD_iso2GeV_Werner()
{
  set_real_data();
  
  set_pQCD_Werner();
  
  compare_scale();
  
  // compare_component();
  
  compare_beamE();
}
    
