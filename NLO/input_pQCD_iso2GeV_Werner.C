// FIX ME: the 13TeV data is not here because the pt binning is different
using namespace std;

const int nscale = 3;
const float scale[nscale] = {0.5, 1.0, 2.0};
const char* scale_abbr[nscale] = {"05", "1", "2"};
const int nbeamE = 2;
const float beamE[nbeamE] = {5.02, 8.16};
const char* beamE_abbr[nbeamE] = {"5023", "8160"};
const int nsys = 1;
const char* sys_abbr[nsys] = {"pp"};
const float nucleon[nsys] = {1};

const int npt = 65;
double pQCD_pt[npt] = {0};
double pQCD_direct[nsys][nbeamE][nscale][npt] = {0};
double pQCD_frag[nsys][nbeamE][nscale][npt] = {0};
double pQCD_sum[nsys][nbeamE][nscale][npt] = {0};

void input_pQCD_iso2GeV_Werner()
{
    for (int isys = 0; isys < nsys; ++isys)
    {
        for (int ibeamE = 0; ibeamE < nbeamE; ++ibeamE)
        {
            for (int iscale = 0; iscale < nscale; ++iscale)
            {
                ifstream fin(Form("/global/homes/d/ddixit/photonCrossSection/NLO/alice_%s_sc%s_%s_2GeV.dat",beamE_abbr[ibeamE],scale_abbr[iscale],sys_abbr[isys]));

                for (int ipt = 0; ipt < npt; ++ipt)
                {
                    fin>>pQCD_pt[ipt]>>pQCD_direct[isys][ibeamE][iscale][ipt]>>pQCD_frag[isys][ibeamE][iscale][ipt]>>pQCD_sum[isys][ibeamE][iscale][ipt];
                    // cout << pQCD_pt[ipt] << " " << pQCD_direct[isys][ibeamE][iscale][ipt] << " " << pQCD_frag[isys][ibeamE][iscale][ipt] << " " << pQCD_sum[isys][ibeamE][iscale][ipt] << endl;
                }
            }
        }
    }

    ofstream fout("pQCD_iso2GeV_Werner.h");

    // print output
    fout << "const int nscale = 3;" << endl;
    fout << "const float scale[nscale] = {0.5, 1.0, 2.0};" << endl;
    fout << "const char* scale_abbr[nscale] = {\"05\", \"1\", \"2\"};" << endl;
    fout << "const int nbeamE = 2;" << endl;
    fout << "const float beamE[nbeamE] = {5.02, 8.16};" << endl;
    fout << "const char* beamE_abbr[nbeamE] = {\"5023\", \"8160\"};" << endl;
    fout << "const int nsys = 1;" << endl;
    fout << "const char* sys_name[nsys] = {\"p+p\"};" << endl;
    fout << "const char* sys_abbr[nsys] = {\"pp\"};" << endl;
    fout << "const float nucleon[nsys] = {1};" << endl;
    fout << endl;
    fout << "const int npt = 65;" << endl;
    fout << "double pQCD_pt[npt] = {";
    for (int ipt = 0; ipt < npt; ++ipt)
    {
        if (ipt!=npt-1) fout << pQCD_pt[ipt] << ", ";
        else fout << pQCD_pt[ipt] << "}; " << endl;
    }
    fout << endl;

    for (int isys = 0; isys < nsys; ++isys)
    {
        fout << "double pQCD_frag_" << sys_abbr[isys] << "[nbeamE][nscale][npt] = {" << endl;
        for (int ibeamE = 0; ibeamE < nbeamE; ++ibeamE)
        {
            fout << "  {";
            for (int iscale = 0; iscale < nscale; ++iscale)
            {
                fout << "  {";
                for (int ipt = 0; ipt < npt; ++ipt)
                {
                    if (ipt!=npt-1) fout << nucleon[isys]*1E-3*2*TMath::Pi()*pQCD_pt[ipt]*pQCD_frag[isys][ibeamE][iscale][ipt] << ", ";
                    else fout << nucleon[isys]*1E-3*2*TMath::Pi()*pQCD_pt[ipt]*pQCD_frag[isys][ibeamE][iscale][ipt];
                }
                if (iscale!=nscale-1) fout << "}, /* scale is " << scale_abbr[iscale] << " */" << endl;
                else fout << "} /* scale is " << scale_abbr[iscale] << " */";
            }
            if (ibeamE!=nbeamE-1) fout << "  }, // beamE is " << beamE_abbr[ibeamE] << endl;
            else fout << "  } // beamE is " << beamE_abbr[ibeamE] << endl;
        }
        fout << "};" << endl;
        fout << endl;

        fout << "double pQCD_direct_" << sys_abbr[isys] << "[nbeamE][nscale][npt] = {" << endl;
        for (int ibeamE = 0; ibeamE < nbeamE; ++ibeamE)
        {
            fout << "  {";
            for (int iscale = 0; iscale < nscale; ++iscale)
            {
                fout << "  {";
                for (int ipt = 0; ipt < npt; ++ipt)
                {
                    if (ipt!=npt-1) fout << nucleon[isys]*1E-3*2*TMath::Pi()*pQCD_pt[ipt]*pQCD_direct[isys][ibeamE][iscale][ipt] << ", ";
                    else fout << nucleon[isys]*1E-3*2*TMath::Pi()*pQCD_pt[ipt]*pQCD_direct[isys][ibeamE][iscale][ipt];
                }
                if (iscale!=nscale-1) fout << "}, /* scale is " << scale_abbr[iscale] << " */" << endl;
                else fout << "} /* scale is " << scale_abbr[iscale] << " */";
            }
            if (ibeamE!=nbeamE-1) fout << "  }, // beamE is " << beamE_abbr[ibeamE] << endl;
            else fout << "  } // beamE is " << beamE_abbr[ibeamE] << endl;
        }
        fout << "};" << endl;
        
        fout << endl;

        fout << "double pQCD_sum_" << sys_abbr[isys] << "[nbeamE][nscale][npt] = {" << endl;
        for (int ibeamE = 0; ibeamE < nbeamE; ++ibeamE)
        {
            fout << "  {";
            for (int iscale = 0; iscale < nscale; ++iscale)
            {
                fout << "  {";
                for (int ipt = 0; ipt < npt; ++ipt)
                {
                    if (ipt!=npt-1) fout << nucleon[isys]*1E-3*2*TMath::Pi()*pQCD_pt[ipt]*pQCD_sum[isys][ibeamE][iscale][ipt] << ", ";
                    else fout << nucleon[isys]*1E-3*2*TMath::Pi()*pQCD_pt[ipt]*pQCD_sum[isys][ibeamE][iscale][ipt];
                }
                if (iscale!=nscale-1) fout << "}, /* scale is " << scale_abbr[iscale] << " */" << endl;
                else fout << "} /* scale is " << scale_abbr[iscale] << " */";
            }
            if (ibeamE!=nbeamE-1) fout << "  }, // beamE is " << beamE_abbr[ibeamE] << endl;
            else fout << "  } // beamE is " << beamE_abbr[ibeamE] << endl;
        }
        fout << "};" << endl;
        fout << endl;

        fout << "TGraphErrors* g_pQCD_frag_" << sys_abbr[isys] << "[nbeamE][nscale] = {0};" << endl;
        fout << "TGraphErrors* g_pQCD_direct_" << sys_abbr[isys] << "[nbeamE][nscale] = {0};" << endl;
        fout << "TGraphErrors* g_pQCD_sum_" << sys_abbr[isys] << "[nbeamE][nscale] = {0};" << endl;
        fout << endl;
    }
}
