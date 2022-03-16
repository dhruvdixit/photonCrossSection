Double_t fMaxPhiCutDMCwoStrip = 5.5658;
Double_t fMinEtaInnerEdge=-0.227579;
Double_t fMaxEtaInnerEdge=0.227579;
Double_t fMinEtaCut=-0.6687;
Double_t fMaxEtaCut=0.66465;
Double_t fMinPhiCut=1.39626;
Double_t fMaxPhiCut=3.15;
Double_t fMinPhiCutDMC=4.5572;
Double_t fMaxPhiCutDMC = 5.70;//DCal acceptance with stripe
//________________________________________________________________________
Bool_t ClusterIsInAcceptance(Double_t eta,  Double_t phi, Int_t clusterType){
    if ( clusterType == 4){
        //pseudorapidty range same for EMC and DMC
        if ( eta < fMinEtaCut || eta > fMaxEtaCut ) return kFALSE;
        //check if outside of EMC and DMC phi acceptance
        if ( (phi < fMinPhiCut || phi > fMaxPhiCut) && (phi < fMinPhiCutDMC || phi > fMaxPhiCutDMC) ) return kFALSE;
        //if in DMC phi range, reject clusters in hole
        if ( phi > fMinPhiCutDMC && phi < fMaxPhiCutDMCwoStrip && eta < fMaxEtaInnerEdge && eta > fMinEtaInnerEdge ) return kFALSE;
    } else {
        if ( eta < fMinEtaCut || eta > fMaxEtaCut ) return kFALSE;
        if ( phi < fMinPhiCut || phi > fMaxPhiCut ) return kFALSE;
        if ( clusterType == 3 && phi < fMaxPhiCutDMCwoStrip && eta < fMaxEtaInnerEdge && eta > fMinEtaInnerEdge ) return kFALSE;
    }
    return kTRUE;// return in case of accepted gamma
}
void calculateAcceptance(){
    Int_t fClusterType = 1;
    if(fClusterType==1){ // EMCAL only (only full SMs)
        fMinEtaCut=-0.6687;
        fMaxEtaCut=0.66465;
        fMinPhiCut=1.39626;
        fMaxPhiCut=3.15;
    } else if(fClusterType==3){ // DCAL only
        fMinEtaCut=-0.66112;
        fMinEtaInnerEdge=-0.227579;
        fMaxEtaCut=0.66112;
        fMaxEtaInnerEdge=0.227579;
        fMinPhiCut = 4.5572;//DCal acceptance
        fMaxPhiCut = 5.5658;//DCal acceptance
    } else if(fClusterType==4){ // EMCAL + DCAL
        fMinEtaCut=-0.6687;
        fMaxEtaCut=0.66465;
        fMinPhiCut=1.39626;
        fMinPhiCutDMC=4.5572;
        fMaxPhiCut = 3.28;//EMCal acceptance Run2 with stripe
        fMaxPhiCutDMC = 5.70;//DCal acceptance with stripe
    }

    TRandom3 rand;
    Double_t total = 0;
    Double_t accepted = 0;
    Double_t acceptance = 1;
    Double_t eta,phi;
    for (Int_t i = 0; i < 1000000; i++)
    {
        total+=1;
        phi = rand.Uniform(0,2* TMath::Pi());
        eta = rand.Uniform(-0.8,0.8);
        if(ClusterIsInAcceptance(eta,phi,fClusterType)) accepted+=1;
    }
    acceptance = accepted/total;
    cout << "Acceptance = " << acceptance << endl;
    
}
