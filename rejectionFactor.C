#include <fstream>
#include <vector>
void rejectionFactor(){
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  

  /*///////////////////////////////////////////////////////
    index         dataset
    0             13c
    1             13d

//////////////////////////////////////////////////////////*/
  
  const int numDataSets = 2;

  TFile* inputFile[numDataSets];

  /*inputFile[0]= new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13c_2runs_al_cluster_emcalMBTrig_Allevent_wEventSelect_noIsoShowShap_noDownScale_noNorm.root","READ");
    inputFile[1]= new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_7runs_noThresh_cluster_emcalMBTrig_Allevent_wEventSelect_noIsoShowShap_noDownScale_noNorm.root","READ");//*/

  inputFile[0]= new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13c_2runs_al_cluster_emcalMBTrig_1Mevent_wEventSelect_noClusCuts_noDownScale_noNorm.root","READ");
  inputFile[1]= new TFile("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_16_14bins_13d_7runs_noThresh_cluster_emcalMBTrig_1Mevent_wEventSelect_noClusCuts_noDownScale_noNorm.root","READ");//*/


  //input histograms
  TH1F* hMB_in[numDataSets];                 //minbias trigger photon spectra
  TH1F* hEG1_in[numDataSets];                //emcal high trigger photon spectra
  TH1F* hEG2_in[numDataSets];                //emcal low trigger photon spectra
  TH1F* hNormalizer_in[numDataSets];         //stores number of events

  //output histograms
  TH1F* hMB;                                 //combined MB photon spectra
  TH1F* hEG1;                                //combined EG1 photon spectra
  TH1F* hEG2;                                //combined EG2 photon spectra
  TH1F* hTurnOn1;                            //EG1/MB turn-on curve
  TH1F* hTurnOn2;                            //EG2/MB turn-on curve
  TH1F* hNormalizer;                         //total event from all datasets

  //Event counts
  double numEveMB[numDataSets] = {0}; 
  double numEveEG1[numDataSets] = {0}; 
  double numEveEG2[numDataSets] ={0}; 
  double totEveMB = 0;
  double totEveEG1 = 0;
  double totEveEG2 = 0;


  for(int i = 0; i < numDataSets; i++)
    {
      hMB_in[i] = (TH1F*)inputFile[i]->Get("hMB_E");
      hEG1_in[i] = (TH1F*)inputFile[i]->Get("hEG1_E");
      hEG2_in[i] = (TH1F*)inputFile[i]->Get("hEG2_E");
      hNormalizer_in[i] = (TH1F*)inputFile[i]->Get("hNormalizer");
      numEveMB[i] = (double)hNormalizer_in[i]->GetBinContent(3);
      numEveEG1[i] = (double)hNormalizer_in[i]->GetBinContent(4);
      numEveEG2[i] = (double)hNormalizer_in[i]->GetBinContent(5);
      totEveMB += (double)hNormalizer_in[i]->GetBinContent(3);
      totEveEG1 += (double)hNormalizer_in[i]->GetBinContent(4);
      totEveEG2 += (double)hNormalizer_in[i]->GetBinContent(5);
    }

  cout << totEveMB << "\t" << totEveEG1 << "\t" << totEveEG2 << endl;
  
  hMB = (TH1F*)hMB_in[0]->Clone();//to get the axis
  hEG1 = (TH1F*)hEG1_in[0]->Clone();//to get the axis
  hEG2 = (TH1F*)hEG2_in[0]->Clone();//to get the axis
  hMB->SetName("hMB");
  hEG1->SetName("hEG1");
  hEG2->SetName("hEG2");
  hMB->SetTitle(";E_{T} (GeV);1/N_{ev}^{EG2}dN/dE_{T}");
  hEG1->SetTitle(";E_{T} (GeV);1/N_{ev}^{EG2}dN/dE_{T}");
  hEG2->SetTitle(";E_{T} (GeV);1/N_{ev}^{EG2}dN/dE_{T}");

  
  for(int i = 1; i < hMB->GetNbinsX()+1; i++){
    double dEt = hMB->GetBinWidth(i);
    //cout << dEt << "\t";
    double contentMB = 0;
    double contentEG1 = 0;
    double contentEG2 = 0;

   
    for(int j = 0; j < numDataSets; j++){
      contentMB += hMB_in[0]->GetBinContent(i);
      contentEG1 += hEG1_in[1]->GetBinContent(i);
      contentEG2 += hEG2_in[1]->GetBinContent(i);

    }
    
    hMB->SetBinContent(i, contentMB/(totEveMB*dEt));
    hEG1->SetBinContent(i, contentEG1/(totEveEG1*dEt));
    hEG2->SetBinContent(i, contentEG2/(totEveEG2*dEt)); 
    hMB->SetBinError(i, pow(contentMB,0.5)/(totEveMB*dEt));
    hEG1->SetBinError(i, pow(contentEG1,0.5)/(totEveEG1*dEt));
    hEG2->SetBinError(i, pow(contentEG2,0.5)/(totEveEG2*dEt));

    double tempCont[3] = {0.0};

    tempCont[0]=hMB_in[0]->GetBinContent(i);
    tempCont[1]=hEG1_in[0]->GetBinContent(i);
    tempCont[2]=hEG2_in[0]->GetBinContent(i);
    hMB_in[0]->SetBinContent(i, (tempCont[0]/(numEveMB[0]*dEt)));
    hEG1_in[0]->SetBinContent(i, (tempCont[1]/(numEveEG1[0]*dEt)));
    hEG2_in[0]->SetBinContent(i, (tempCont[2]/(numEveEG2[0]*dEt)));
    hMB_in[0]->SetBinError(i, pow(tempCont[0],0.5)/(numEveMB[0]*dEt));
    hEG1_in[0]->SetBinError(i, pow(tempCont[1],0.5)/(numEveEG1[0]*dEt));
    hEG2_in[0]->SetBinError(i, pow(tempCont[2],0.5)/(numEveEG2[0]*dEt));

    tempCont[0] = tempCont[1] = tempCont[2] = 0.0;
    tempCont[0]=hMB_in[1]->GetBinContent(i);
    tempCont[1]=hEG1_in[1]->GetBinContent(i);
    tempCont[2]=hEG2_in[1]->GetBinContent(i);
    hMB_in[1]->SetBinContent(i, (tempCont[0]/(numEveMB[1]*dEt)));
    hEG1_in[1]->SetBinContent(i, (tempCont[1]/(numEveEG1[1]*dEt)));
    hEG2_in[1]->SetBinContent(i, (tempCont[2]/(numEveEG2[1]*dEt)));
    hMB_in[1]->SetBinError(i, pow(tempCont[0],0.5)/(numEveMB[1]*dEt));
    hEG1_in[1]->SetBinError(i, pow(tempCont[1],0.5)/(numEveEG1[1]*dEt));
    hEG2_in[1]->SetBinError(i, pow(tempCont[2],0.5)/(numEveEG2[1]*dEt));

  }
  
  hEG1->SetLineColor(kCyan);
  hEG1->SetMarkerColor(kCyan);
  hEG1->SetMarkerStyle(20);
  hEG2->SetLineColor(kRed);
  hEG2->SetMarkerColor(kRed);
  hEG2->SetMarkerStyle(21);
  hMB->SetLineColor(kGray);
  hMB->SetMarkerColor(kGray);
  hMB->SetMarkerStyle(22);
  
  hEG1_in[0]->SetLineColor(kCyan+2);
  hEG1_in[0]->SetMarkerColor(kCyan+2);
  hEG1_in[0]->SetMarkerStyle(20);
  hEG2_in[0]->SetLineColor(kRed+1);
  hEG2_in[0]->SetMarkerColor(kRed+1);
  hEG2_in[0]->SetMarkerStyle(21);
  hMB_in[0]->SetLineColor(kGray+1);
  hMB_in[0]->SetMarkerColor(kGray+1);
  hMB_in[0]->SetMarkerStyle(22);
  
  hEG1_in[1]->SetLineColor(kCyan+4);
  hEG1_in[1]->SetMarkerColor(kCyan+4);
  hEG1_in[1]->SetMarkerStyle(20);
  hEG2_in[1]->SetLineColor(kRed+2);
  hEG2_in[1]->SetMarkerColor(kRed+2);
  hEG2_in[1]->SetMarkerStyle(21);
  hMB_in[1]->SetLineColor(kGray+2);
  hMB_in[1]->SetMarkerColor(kGray+2);
  hMB_in[1]->SetMarkerStyle(22);
  
  TLegend* leg = new TLegend(0.6,0.7,0.9,0.9);
  leg->SetHeader("EG1, EG2, MB triggered photon spectra");
  leg->AddEntry(hEG1,"EG1 events from 13cd");
  leg->AddEntry(hEG1_in[0],"EG1 events from 13c");
  leg->AddEntry(hEG1_in[1],"EG1 events from 13d");
  
  leg->AddEntry(hEG2,"EG2 events from 13cd");
  leg->AddEntry(hEG2_in[0],"EG2 events from 13c");
  leg->AddEntry(hEG2_in[1],"EG2 events from 13d");
  
  leg->AddEntry(hMB,"MB events from 13cd");
  leg->AddEntry(hMB_in[0],"MB events from 13c");
  leg->AddEntry(hMB_in[1],"MB events from 13d");
  

  TCanvas* triggerSpectra = new TCanvas();
  triggerSpectra->SetLogy();
  hEG1->GetYaxis()->SetRangeUser(1e-7, 10);
  hEG1->Draw("samee");
  hEG1_in[0]->Draw("samee");
  hEG1_in[1]->Draw("samee");
  
  hEG2->Draw("samee");
  hEG2_in[0]->Draw("samee");
  hEG2_in[1]->Draw("samee");
  
  hMB->Draw("samee");
  hMB_in[0]->Draw("samee");
  hMB_in[1]->Draw("samee");

  leg->Draw("same");

  TH1F* rejF1 = (TH1F*)hEG1->Clone();
  rejF1->SetName("rejF1");
  rejF1->Divide(hMB);
  rejF1->SetLineColor(kCyan);
  rejF1->SetMarkerColor(kCyan);
  rejF1->SetMarkerStyle(20);  



  TH1F* rejF2 = (TH1F*)hEG2->Clone();
  rejF2->SetName("rejF2");
  rejF2->Divide(hMB);
  rejF2->SetLineColor(kRed);
  rejF2->SetMarkerColor(kRed);
  rejF2->SetMarkerStyle(21);



  TH1F* rejF3 = (TH1F*)hEG1->Clone();
  rejF3->SetName("rejF3");
  rejF3->Divide(hEG2);
  rejF3->SetLineColor(kBlack);
  rejF3->SetMarkerColor(kBlack);
  rejF3->SetMarkerStyle(22);



  TCanvas* turnOnCurves = new TCanvas();
  turnOnCurves->SetLogy();
  rejF1->GetYaxis()->SetRangeUser(5*1e-2, 5*1e4);
  rejF1->Draw();
  rejF2->Draw("same");
  rejF3->Draw("same");
  
  rejF1->Fit("pol0", "", "", 14, 40);
  rejF2->Fit("pol0", "", "", 10, 40);
  rejF3->Fit("pol0", "", "", 16, 40);//*/
}
