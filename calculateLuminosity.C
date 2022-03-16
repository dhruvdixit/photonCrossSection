void calculateLuminosity() {
  //std::unique_ptr<TFile*> reader(TFile::Open("/global/homes/d/ddixit/AnalysisResults_scalar2_decTrain.root", "READ"));
  TFile* reader = new TFile("/global/homes/d/ddixit/AnalysisResults_scalar2_decTrain.root", "READ"));
  
  reader->cd("EmcalTriggerNormtask");
  auto histlist = static_cast<TKey *>(gDirectory->GetListOfKeys()->At(0))->ReadObject<TList>();
  
  //histlist->ls();
  auto clusterCounterEMC7 = static_cast<TH1 *>(histlist->FindObject("hClusterCounterEMC7")),		// for CENTNOPMD correction
    clusterCounterEG1 = static_cast<TH1 *>(histlist->FindObject("hClusterCounterEG1"));		// for CENTNOTRD correction
  auto rawluminosities = static_cast<TH2 *>(histlist->FindObject("hTriggerLuminosity"));
  
  // Evaluate CENTNOPMD correction
  int binCENTEMC7 = clusterCounterEMC7->GetXaxis()->FindBin("CENT"),
    binCENTNOPMDEMC7 = clusterCounterEMC7->GetXaxis()->FindBin("CENTNOPMD");
  int binCENTNOPMDEG1 = clusterCounterEG1->GetXaxis()->FindBin("CENTNOPMD"),
    binCENTNOTRDEG1 = clusterCounterEG1->GetXaxis()->FindBin("CENTNOTRD");
  double corrCENTNOPMD = clusterCounterEMC7->GetBinContent(binCENTNOPMDEMC7)/clusterCounterEMC7->GetBinContent(binCENTEMC7);
  double corrCENTNOTRD = clusterCounterEG1->GetBinContent(binCENTNOTRDEG1)/clusterCounterEG1->GetBinContent(binCENTNOPMDEG1);
  
  std::cout << "Correction CENTNOPMD: " << corrCENTNOPMD << std::endl;
  std::cout << "Correction CENTNOTRD: " << corrCENTNOTRD << std::endl;
  
  int binlumieg1 = rawluminosities->GetXaxis()->FindBin("EG1"),
    binlumieg2 = rawluminosities->GetXaxis()->FindBin("EG2");
  std::unique_ptr<TH1> sliceEG1(rawluminosities->ProjectionY("rawEG1", binlumieg1, binlumieg1));
  std::unique_ptr<TH1> sliceEG2(rawluminosities->ProjectionY("rawEG2", binlumieg2, binlumieg2));
  double rawCountsEG1 = sliceEG1->Integral(),
    rawCountsEG2 = sliceEG2->Integral();
  std::cout << "Using raw inspected events EG1: " << rawCountsEG1 << std::endl;
  std::cout << "Using raw inspected events EG2: " << rawCountsEG2 << std::endl;
  
  // Raw inspected events are determined in the CENT cluster, needs to be corrected to the CENTNOPMD and CENTNOTRD cluster
  double corrCountsEG2 = rawCountsEG2 * corrCENTNOPMD,
    corrCountsEG1 = rawCountsEG1 * corrCENTNOPMD * corrCENTNOTRD;
  std::cout << "Raw inspected events after correction for cluster luminosity EG1: " << corrCountsEG1 << std::endl;
  std::cout << "Raw inspected events after correction for cluster luminosity EG2: " << corrCountsEG2 << std::endl;
  
  // normalize by reference cross section
  double xrefBarn = 2.09,
    barnToNB = 1e9,
    xrefNB = xrefBarn * barnToNB;
  double lumiEG1 = corrCountsEG1 / xrefNB,
    lumiEG2 = corrCountsEG2 / xrefNB;
  std::cout << "Inspected luminosity EG1: " << lumiEG1 << std::endl;
  std::cout << "Inspected luminosity EG2: " << lumiEG2 << std::endl;
}
