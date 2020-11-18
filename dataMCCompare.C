#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TGraphAsymmErrors.h"
//#include "TTreeReader.h"
//#include "TTreeReaderValue.h"
#include "TMath.h"
#include "TVector2.h"
//#include "/root/atlasstyle-00-03-05/AtlasStyle.h"
//#include "/root/atlasstyle-00-03-05/AtlasStyle.C"
//#include "/root/atlasstyle-00-03-05/AtlasUtils.h"
//#include "/root/atlasstyle-00-03-05/AtlasUtils.C"
//#include "/root/atlasstyle-00-03-05/AtlasLabels.h"
//#include "/root/atlasstyle-00-03-05/AtlasLabels.C"
#include "TDatabasePDG.h"
#include "TEfficiency.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bitset>
#include <bits/stdc++.h>
#include <cstring>

void dataMCCompare(){

  //gStyle->SetCanvasColor(-1);
  //gStyle->SetPadColor(-1);
  //gStyle->SetFrameFillColor(-1);
  //gStyle->SetHistFillColor(-1);
  //gStyle->SetTitleFillColor(-1);
  //gStyle->SetFillColor(-1);
  //gStyle->SetFillStyle(4000);
  //gStyle->SetStatStyle(0);
  //gStyle->SetTitleStyle(0);
  gStyle->SetCanvasPreferGL(kTRUE);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetStatBorderSize(0);
  gStyle->SetTitleBorderSize(0);
  


  TFile* datafile = new TFile(Form("/global/homes/d/ddixit/photonCrossSection/isoPhotonOutput/fout_5_26bins_17pq_almostAll_forRTrig_MBEG2exlusion_tof20_eCross5_newExoticity_noNorm2_ISOnormal_wSSHist.root", path.Data()), "READ");
  TFile* mcfile = new TFile(Form("/project/projectdirs/alice/ddixit/CorrelationAnalysis/NtupleAnalysis/PhotonOutput/MC/18b10a_100Kevents_erwanbinning_noNorm_newExoticity_wTOFPlot_eff2_yesNoISOSSC_allptHatBins.root", path.Data()), "READ");


  //Shower Shape cut
  


  


  
}
