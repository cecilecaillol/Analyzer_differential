#include <TH2.h>
#include "btagSF.h"
#include "ApplyFF_lpt.h"
#include <TStyle.h>
#include "PostProcessing.h"
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "ScaleFactor.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "myHelper.h"
#include "et_Tree.h"
#include "LumiReweightingStandAlone.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "ComputeWG1Unc.h"
#include "SFtautrigger.h"
#include "qq2Hqq_uncert_scheme.h"

using namespace std;

int main(int argc, char** argv) {

    int do_control_plots=0;
    bool do_differential=true;

    if (do_differential) do_control_plots=0;

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);

    float tes=0;
    if (argc > 1) {
        tes = atof(argv[5]);
    }

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    cout<<name.c_str()<<endl;
    TTree *arbre = (TTree*) f_Double->Get("etau_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float ngen = nbevt->GetBinContent(2);

    float xs=1.0; float weight=1.0; float luminosity=59740.0;
    if (sample=="Z" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}
    if (sample=="DYlow"){ xs=21658.0; weight=luminosity*xs/ngen;}
    else if (sample=="TT" or sample=="TTT" or sample=="TTJ") {xs=831.76; weight=luminosity*xs/ngen;}
    else if (sample=="TTTo2L2Nu") {xs=88.29; weight=luminosity*xs/ngen;}
    else if (sample=="TTToSemiLeptonic") {xs=365.35; weight=luminosity*xs/ngen;}
    else if (sample=="TTToHadronic") {xs=377.96; weight=luminosity*xs/ngen;}
    else if (sample=="W") {xs=61526.7; weight=luminosity*xs/ngen;}
    else if (sample=="data_obs"){weight=1.0;}
    else if (sample=="embedded"){weight=1.0;}
    else if (sample=="ST_tW_antitop") {xs=35.85; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top") {xs=35.85; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop") {xs=80.94; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top") {xs=136.02; weight=luminosity*xs/ngen;}
    else if (sample=="ggH_htt125") {xs=48.58*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ggH") {xs=48.58*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="qqH_htt125") {xs=3.782*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="qqH") {xs=3.782*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH125") {xs=0.840*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH125") {xs=0.5328*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.7612*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ttHTT") {xs=0.5071*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ttHTT125") {xs=0.5071*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="GGZH125") {xs=0.1227*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHLLTT125") {xs=0.1227*0.0627*3*0.033658; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHNNTT125") {xs=0.1227*0.0627*0.2000; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHQQTT125") {xs=0.1227*0.0627*0.6991; weight=luminosity*xs/ngen;}
    else if (sample=="GGHWW") {xs=48.58*0.2137*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="VBFHWW") {xs=3.782*0.2137*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="WplusHWW") {xs=0.840*0.2137; weight=luminosity*xs/ngen;}
    else if (sample=="WminusHWW") {xs=0.5328*0.2137; weight=luminosity*xs/ngen;}
    else if (sample=="ZHWW") {xs=0.7612*0.2137; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHWW") {xs=0.1227*0.2137; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ") {xs=16.523; weight=luminosity*xs/ngen;}
    else if (sample=="WZ") {xs=47.13; weight=luminosity*xs/ngen;}
    else if (sample=="WW") {xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="WZ1L1Nu2Q") {xs=10.71; weight=luminosity*xs/ngen;}
    else if (sample=="WZ1L3Nu") {xs=3.05; weight=luminosity*xs/ngen;}
    else if (sample=="WZJets") {xs=5.26; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3L1Nu") {xs=4.43; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2L2Q") {xs=5.52; weight=luminosity*xs/ngen;}
    else if (sample=="WW1L1Nu2Q") {xs=49.997; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L") {xs=1.26; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q") {xs=3.38; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu") {xs=13.84; weight=luminosity*xs/ngen;}
    else if (sample=="WGLNu") {xs=489.0; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWminus") {xs=23.24; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWplus") {xs=29.59; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZLL") {xs=4.321; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZNuNu") {xs=10.66; weight=luminosity*xs/ngen;}

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(3);

    arbre->SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt);
    arbre->SetBranchAddress("Rivet_nJets30", &Rivet_nJets30);
    arbre->SetBranchAddress("Rivet_stage1_1_fine_cat_pTjet30GeV", & Rivet_stage1_1_fine_cat_pTjet30GeV);
    arbre->SetBranchAddress("Rivet_stage1_1_cat_pTjet30GeV", & Rivet_stage1_1_cat_pTjet30GeV);
    arbre->SetBranchAddress("Rivet_stage1_cat_pTjet30GeV", & Rivet_stage1_cat_pTjet30GeV);
    arbre->SetBranchAddress("Rivet_higgsRapidity", &Rivet_higgsRapidity);
    arbre->SetBranchAddress("Rivet_j1pt", &Rivet_j1pt);
    arbre->SetBranchAddress("Rivet_j2pt", &Rivet_j2pt);
    arbre->SetBranchAddress("Rivet_j1eta", &Rivet_j1eta);
    arbre->SetBranchAddress("Rivet_j2eta", &Rivet_j2eta);
    arbre->SetBranchAddress("Rivet_j1phi", &Rivet_j1phi);
    arbre->SetBranchAddress("Rivet_j2phi", &Rivet_j2phi);
    arbre->SetBranchAddress("Rivet_j1m", &Rivet_j1m);
    arbre->SetBranchAddress("Rivet_j2m", &Rivet_j2m);
    arbre->SetBranchAddress("gentau1_eta", &gentau1_eta);
    arbre->SetBranchAddress("gentau2_eta", &gentau2_eta);
    arbre->SetBranchAddress("gentau1_pt", &gentau1_pt);
    arbre->SetBranchAddress("gentau2_pt", &gentau2_pt);

    arbre->SetBranchAddress("HTTgenfinalstate", &HTTgenfinalstate);
    arbre->SetBranchAddress("gen_met_pt", &gen_met_pt);
    arbre->SetBranchAddress("gen_met_phi", &gen_met_phi);
    arbre->SetBranchAddress("gen_ele_pt", &gen_ele_pt);
    arbre->SetBranchAddress("gen_ele_eta", &gen_ele_eta);
    arbre->SetBranchAddress("gen_ele_phi", &gen_ele_phi);
    arbre->SetBranchAddress("gen_tauh_pt", &gen_tauh_pt);
    arbre->SetBranchAddress("gen_tauh_eta", &gen_tauh_eta);
    arbre->SetBranchAddress("gen_tauh_phi", &gen_tauh_phi);

    arbre->SetBranchAddress("PythiaWeight_isr_muR2", &PythiaWeight_isr_muR2);
    arbre->SetBranchAddress("PythiaWeight_isr_muR0p5", &PythiaWeight_isr_muR0p5);
    arbre->SetBranchAddress("PythiaWeight_fsr_muR2", &PythiaWeight_fsr_muR2);
    arbre->SetBranchAddress("PythiaWeight_fsr_muR0p5", &PythiaWeight_fsr_muR0p5);
    arbre->SetBranchAddress("lheweight_muR0p5_muF0p5", &lheweight_muR0p5_muF0p5);
    arbre->SetBranchAddress("lheweight_muR2_muF2", &lheweight_muR2_muF2);
    arbre->SetBranchAddress("lheweight_nominal", &lheweight_nominal);

    arbre->SetBranchAddress("L1pt", &L1pt);
    arbre->SetBranchAddress("L1iso", &L1iso);
    arbre->SetBranchAddress("passEle32", &passEle32);
    arbre->SetBranchAddress("passEle35", &passEle35);
    arbre->SetBranchAddress("passEle24Tau30", &passEle24Tau30);
    arbre->SetBranchAddress("passEle24HPSTau30", &passEle24HPSTau30);

    arbre->SetBranchAddress("matchEle32_1", &matchEle32_1);
    arbre->SetBranchAddress("matchEle35_1", &matchEle35_1);
    arbre->SetBranchAddress("matchEle24Tau30_1", &matchEle24Tau30_1);
    arbre->SetBranchAddress("matchEle24Tau30_2", &matchEle24Tau30_2);
    arbre->SetBranchAddress("matchEle24HPSTau30_1", &matchEle24HPSTau30_1);
    arbre->SetBranchAddress("matchEle24HPSTau30_2", &matchEle24HPSTau30_2);
    arbre->SetBranchAddress("filterEle32_1", &filterEle32_1);
    arbre->SetBranchAddress("filterEle35_1", &filterEle35_1);
    arbre->SetBranchAddress("filterEle24Tau30_1", &filterEle24Tau30_1);
    arbre->SetBranchAddress("filterEle24Tau30_2", &filterEle24Tau30_2);
    arbre->SetBranchAddress("filterEle24HPSTau30_1", &filterEle24HPSTau30_1);
    arbre->SetBranchAddress("filterEle24HPSTau30_2", &filterEle24HPSTau30_2);

    arbre->SetBranchAddress("genpt_1", &genpt_1);
    arbre->SetBranchAddress("geneta_1", &geneta_1);
    arbre->SetBranchAddress("genpt_2", &genpt_2);
    arbre->SetBranchAddress("geneta_2", &geneta_2);

    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("lumi", &lumi);
    arbre->SetBranchAddress("evt", &evt);
    arbre->SetBranchAddress("npv", &npv);
    arbre->SetBranchAddress("pt_1", &pt_1);
    arbre->SetBranchAddress("phi_1", &phi_1);
    arbre->SetBranchAddress("eta_1", &eta_1);
    arbre->SetBranchAddress("iso_1", &iso_1);
    arbre->SetBranchAddress("m_1", &m_1);
    arbre->SetBranchAddress("q_1", &q_1);
    arbre->SetBranchAddress("nbtag", &nbtag);
    arbre->SetBranchAddress("nbtagL", &nbtagL);
    arbre->SetBranchAddress("q_2", &q_2);
    arbre->SetBranchAddress("pt_2", &pt_2);
    arbre->SetBranchAddress("eta_2", &eta_2);
    arbre->SetBranchAddress("m_2", &m_2);
    arbre->SetBranchAddress("phi_2", &phi_2);

    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("metphi", &metphi);
    arbre->SetBranchAddress("met_UESUp", &met_UESUp);
    arbre->SetBranchAddress("metphi_UESDown", &metphi_UESDown);
    arbre->SetBranchAddress("met_UESDown", &met_UESDown);
    arbre->SetBranchAddress("metphi_UESUp", &metphi_UESUp);
    arbre->SetBranchAddress("met_responseUp", &met_responseUp);
    arbre->SetBranchAddress("metphi_responseUp", &metphi_responseUp);
    arbre->SetBranchAddress("met_responseDown", &met_responseDown);
    arbre->SetBranchAddress("metphi_responseDown", &metphi_responseDown);
    arbre->SetBranchAddress("met_resolutionUp", &met_resolutionUp);
    arbre->SetBranchAddress("metphi_resolutionUp", &metphi_resolutionUp);
    arbre->SetBranchAddress("met_resolutionDown", &met_resolutionDown);
    arbre->SetBranchAddress("metphi_resolutionDown", &metphi_resolutionDown);
    arbre->SetBranchAddress("metphi_JetAbsoluteDown", &metphi_JetAbsoluteDown);
    arbre->SetBranchAddress("met_JetAbsoluteDown", &met_JetAbsoluteDown);
    arbre->SetBranchAddress("metphi_JetAbsoluteUp", &metphi_JetAbsoluteUp);
    arbre->SetBranchAddress("met_JetAbsoluteUp", &met_JetAbsoluteUp);
    arbre->SetBranchAddress("metphi_JetAbsoluteyearDown", &metphi_JetAbsoluteyearDown);
    arbre->SetBranchAddress("met_JetAbsoluteyearDown", &met_JetAbsoluteyearDown);
    arbre->SetBranchAddress("metphi_JetAbsoluteyearUp", &metphi_JetAbsoluteyearUp);
    arbre->SetBranchAddress("met_JetAbsoluteyearUp", &met_JetAbsoluteyearUp);
    arbre->SetBranchAddress("metphi_JetBBEC1Down", &metphi_JetBBEC1Down);
    arbre->SetBranchAddress("met_JetBBEC1Down", &met_JetBBEC1Down);
    arbre->SetBranchAddress("metphi_JetBBEC1Up", &metphi_JetBBEC1Up);
    arbre->SetBranchAddress("met_JetBBEC1Up", &met_JetBBEC1Up);
    arbre->SetBranchAddress("metphi_JetBBEC1yearDown", &metphi_JetBBEC1yearDown);
    arbre->SetBranchAddress("met_JetBBEC1yearDown", &met_JetBBEC1yearDown);
    arbre->SetBranchAddress("metphi_JetBBEC1yearUp", &metphi_JetBBEC1yearUp);
    arbre->SetBranchAddress("met_JetBBEC1yearUp", &met_JetBBEC1yearUp);
    arbre->SetBranchAddress("metphi_JetEC2Down", &metphi_JetEC2Down);
    arbre->SetBranchAddress("met_JetEC2Down", &met_JetEC2Down);
    arbre->SetBranchAddress("metphi_JetEC2Up", &metphi_JetEC2Up);
    arbre->SetBranchAddress("met_JetEC2Up", &met_JetEC2Up);
    arbre->SetBranchAddress("metphi_JetEC2yearDown", &metphi_JetEC2yearDown);
    arbre->SetBranchAddress("met_JetEC2yearDown", &met_JetEC2yearDown);
    arbre->SetBranchAddress("metphi_JetEC2yearUp", &metphi_JetEC2yearUp);
    arbre->SetBranchAddress("met_JetEC2yearUp", &met_JetEC2yearUp);
    arbre->SetBranchAddress("metphi_JetFlavorQCDDown", &metphi_JetFlavorQCDDown);
    arbre->SetBranchAddress("met_JetFlavorQCDDown", &met_JetFlavorQCDDown);
    arbre->SetBranchAddress("metphi_JetFlavorQCDUp", &metphi_JetFlavorQCDUp);
    arbre->SetBranchAddress("met_JetFlavorQCDUp", &met_JetFlavorQCDUp);
    arbre->SetBranchAddress("metphi_JetHFDown", &metphi_JetHFDown);
    arbre->SetBranchAddress("met_JetHFDown", &met_JetHFDown);
    arbre->SetBranchAddress("metphi_JetHFUp", &metphi_JetHFUp);
    arbre->SetBranchAddress("met_JetHFUp", &met_JetHFUp);
    arbre->SetBranchAddress("metphi_JetHFyearDown", &metphi_JetHFyearDown);
    arbre->SetBranchAddress("met_JetHFyearDown", &met_JetHFyearDown);
    arbre->SetBranchAddress("metphi_JetHFyearUp", &metphi_JetHFyearUp);
    arbre->SetBranchAddress("met_JetHFyearUp", &met_JetHFyearUp);
    arbre->SetBranchAddress("metphi_JetRelativeBalDown", &metphi_JetRelativeBalDown);
    arbre->SetBranchAddress("met_JetRelativeBalDown", &met_JetRelativeBalDown);
    arbre->SetBranchAddress("metphi_JetRelativeBalUp", &metphi_JetRelativeBalUp);
    arbre->SetBranchAddress("met_JetRelativeBalUp", &met_JetRelativeBalUp);
    arbre->SetBranchAddress("metphi_JetRelativeSampleDown", &metphi_JetRelativeSampleDown);
    arbre->SetBranchAddress("met_JetRelativeSampleDown", &met_JetRelativeSampleDown);
    arbre->SetBranchAddress("metphi_JetRelativeSampleUp", &metphi_JetRelativeSampleUp);
    arbre->SetBranchAddress("met_JetRelativeSampleUp", &met_JetRelativeSampleUp);
    arbre->SetBranchAddress("metphi_JERDown", &metphi_JERDown);
    arbre->SetBranchAddress("met_JERDown", &met_JERDown);
    arbre->SetBranchAddress("metphi_JERUp", &metphi_JERUp);
    arbre->SetBranchAddress("met_JERUp", &met_JERUp);

    arbre->SetBranchAddress("pt_1_ScaleUp", &pt_1_ScaleUp);
    arbre->SetBranchAddress("pt_1_ScaleDown", &pt_1_ScaleDown);

    arbre->SetBranchAddress("m_sv", &m_sv);
    arbre->SetBranchAddress("m_sv_DOWN", &m_sv_DOWN);
    arbre->SetBranchAddress("m_sv_UP", &m_sv_UP);
    arbre->SetBranchAddress("m_sv_UESUp", &m_sv_UESUp);
    arbre->SetBranchAddress("m_sv_UESDown", &m_sv_UESDown);
    arbre->SetBranchAddress("m_sv_ResponseDown", &m_sv_ResponseDown);
    arbre->SetBranchAddress("m_sv_ResponseUp", &m_sv_ResponseUp);
    arbre->SetBranchAddress("m_sv_ResolutionDown", &m_sv_ResolutionDown);
    arbre->SetBranchAddress("m_sv_ResolutionUp", &m_sv_ResolutionUp);
    arbre->SetBranchAddress("m_sv_ESCALEUP", &m_sv_ESCALEUP);
    arbre->SetBranchAddress("m_sv_ESCALEDOWN", &m_sv_ESCALEDOWN);
    arbre->SetBranchAddress("m_sv_JetAbsoluteUp", &m_sv_JetAbsoluteUp);
    arbre->SetBranchAddress("m_sv_JetAbsoluteDown", &m_sv_JetAbsoluteDown);
    arbre->SetBranchAddress("m_sv_JetAbsoluteyearUp", &m_sv_JetAbsoluteyearUp);
    arbre->SetBranchAddress("m_sv_JetAbsoluteyearDown", &m_sv_JetAbsoluteyearDown);
    arbre->SetBranchAddress("m_sv_JetBBEC1Up", &m_sv_JetBBEC1Up);
    arbre->SetBranchAddress("m_sv_JetBBEC1Down", &m_sv_JetBBEC1Down);
    arbre->SetBranchAddress("m_sv_JetBBEC1yearUp", &m_sv_JetBBEC1yearUp);
    arbre->SetBranchAddress("m_sv_JetBBEC1yearDown", &m_sv_JetBBEC1yearDown);
    arbre->SetBranchAddress("m_sv_JetEC2Up", &m_sv_JetEC2Up);
    arbre->SetBranchAddress("m_sv_JetEC2Down", &m_sv_JetEC2Down);
    arbre->SetBranchAddress("m_sv_JetEC2yearUp", &m_sv_JetEC2yearUp);
    arbre->SetBranchAddress("m_sv_JetEC2yearDown", &m_sv_JetEC2yearDown);
    arbre->SetBranchAddress("m_sv_JetFlavorQCDUp", &m_sv_JetFlavorQCDUp);
    arbre->SetBranchAddress("m_sv_JetFlavorQCDDown", &m_sv_JetFlavorQCDDown);
    arbre->SetBranchAddress("m_sv_JetHFUp", &m_sv_JetHFUp);
    arbre->SetBranchAddress("m_sv_JetHFDown", &m_sv_JetHFDown);
    arbre->SetBranchAddress("m_sv_JetHFyearUp", &m_sv_JetHFyearUp);
    arbre->SetBranchAddress("m_sv_JetHFyearDown", &m_sv_JetHFyearDown);
    arbre->SetBranchAddress("m_sv_JetRelativeBalUp", &m_sv_JetRelativeBalUp);
    arbre->SetBranchAddress("m_sv_JetRelativeBalDown", &m_sv_JetRelativeBalDown);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleUp", &m_sv_JetRelativeSampleUp);
    arbre->SetBranchAddress("m_sv_JetRelativeSampleDown", &m_sv_JetRelativeSampleDown);
    arbre->SetBranchAddress("m_sv_JERUp", &m_sv_JERUp);
    arbre->SetBranchAddress("m_sv_JERDown", &m_sv_JERDown);

    arbre->SetBranchAddress("njets", &njets);
    arbre->SetBranchAddress("njets_JetAbsoluteDown", &njets_JetAbsoluteDown);
    arbre->SetBranchAddress("njets_JetAbsoluteUp", &njets_JetAbsoluteUp);
    arbre->SetBranchAddress("njets_JetAbsoluteyearDown", &njets_JetAbsoluteyearDown);
    arbre->SetBranchAddress("njets_JetAbsoluteyearUp", &njets_JetAbsoluteyearUp);
    arbre->SetBranchAddress("njets_JetBBEC1Down", &njets_JetBBEC1Down);
    arbre->SetBranchAddress("njets_JetBBEC1Up", &njets_JetBBEC1Up);
    arbre->SetBranchAddress("njets_JetBBEC1yearDown", &njets_JetBBEC1yearDown);
    arbre->SetBranchAddress("njets_JetBBEC1yearUp", &njets_JetBBEC1yearUp);
    arbre->SetBranchAddress("njets_JetEC2Down", &njets_JetEC2Down);
    arbre->SetBranchAddress("njets_JetEC2Up", &njets_JetEC2Up);
    arbre->SetBranchAddress("njets_JetEC2yearDown", &njets_JetEC2yearDown);
    arbre->SetBranchAddress("njets_JetEC2yearUp", &njets_JetEC2yearUp);
    arbre->SetBranchAddress("njets_JetFlavorQCDDown", &njets_JetFlavorQCDDown);
    arbre->SetBranchAddress("njets_JetFlavorQCDUp", &njets_JetFlavorQCDUp);
    arbre->SetBranchAddress("njets_JetHFDown", &njets_JetHFDown);
    arbre->SetBranchAddress("njets_JetHFUp", &njets_JetHFUp);
    arbre->SetBranchAddress("njets_JetHFyearDown", &njets_JetHFyearDown);
    arbre->SetBranchAddress("njets_JetHFyearUp", &njets_JetHFyearUp);
    arbre->SetBranchAddress("njets_JetRelativeBalDown", &njets_JetRelativeBalDown);
    arbre->SetBranchAddress("njets_JetRelativeBalUp", &njets_JetRelativeBalUp);
    arbre->SetBranchAddress("njets_JetRelativeSampleDown", &njets_JetRelativeSampleDown);
    arbre->SetBranchAddress("njets_JetRelativeSampleUp", &njets_JetRelativeSampleUp);
    arbre->SetBranchAddress("njets_JERDown", &njets_JERDown);
    arbre->SetBranchAddress("njets_JERUp", &njets_JERUp);

    arbre->SetBranchAddress("jpt_1", &jpt_1);
    arbre->SetBranchAddress("jeta_1", &jeta_1);
    arbre->SetBranchAddress("jphi_1", &jphi_1);

    arbre->SetBranchAddress("jpt_1_JetAbsoluteDown", &jpt_1_JetAbsoluteDown);
    arbre->SetBranchAddress("jpt_1_JetAbsoluteUp", &jpt_1_JetAbsoluteUp);
    arbre->SetBranchAddress("jpt_1_JetAbsoluteyearDown", &jpt_1_JetAbsoluteyearDown);
    arbre->SetBranchAddress("jpt_1_JetAbsoluteyearUp", &jpt_1_JetAbsoluteyearUp);
    arbre->SetBranchAddress("jpt_1_JetBBEC1Down", &jpt_1_JetBBEC1Down);
    arbre->SetBranchAddress("jpt_1_JetBBEC1Up", &jpt_1_JetBBEC1Up);
    arbre->SetBranchAddress("jpt_1_JetBBEC1yearDown", &jpt_1_JetBBEC1yearDown);
    arbre->SetBranchAddress("jpt_1_JetBBEC1yearUp", &jpt_1_JetBBEC1yearUp);
    arbre->SetBranchAddress("jpt_1_JetEC2Down", &jpt_1_JetEC2Down);
    arbre->SetBranchAddress("jpt_1_JetEC2Up", &jpt_1_JetEC2Up);
    arbre->SetBranchAddress("jpt_1_JetEC2yearDown", &jpt_1_JetEC2yearDown);
    arbre->SetBranchAddress("jpt_1_JetEC2yearUp", &jpt_1_JetEC2yearUp);
    arbre->SetBranchAddress("jpt_1_JetFlavorQCDDown", &jpt_1_JetFlavorQCDDown);
    arbre->SetBranchAddress("jpt_1_JetFlavorQCDUp", &jpt_1_JetFlavorQCDUp);
    arbre->SetBranchAddress("jpt_1_JetHFDown", &jpt_1_JetHFDown);
    arbre->SetBranchAddress("jpt_1_JetHFUp", &jpt_1_JetHFUp);
    arbre->SetBranchAddress("jpt_1_JetHFyearDown", &jpt_1_JetHFyearDown);
    arbre->SetBranchAddress("jpt_1_JetHFyearUp", &jpt_1_JetHFyearUp);
    arbre->SetBranchAddress("jpt_1_JetRelativeBalDown", &jpt_1_JetRelativeBalDown);
    arbre->SetBranchAddress("jpt_1_JetRelativeBalUp", &jpt_1_JetRelativeBalUp);
    arbre->SetBranchAddress("jpt_1_JetRelativeSampleDown", &jpt_1_JetRelativeSampleDown);
    arbre->SetBranchAddress("jpt_1_JetRelativeSampleUp", &jpt_1_JetRelativeSampleUp);
    arbre->SetBranchAddress("jpt_1_JERDown", &jpt_1_JERDown);
    arbre->SetBranchAddress("jpt_1_JERUp", &jpt_1_JERUp);

    arbre->SetBranchAddress("jpt_2", &jpt_2);
    arbre->SetBranchAddress("jeta_2", &jeta_2);
    arbre->SetBranchAddress("jphi_2", &jphi_2);
    arbre->SetBranchAddress("bpt_1", &bpt_1);
    arbre->SetBranchAddress("bcsv_1", &bcsv_1);
    arbre->SetBranchAddress("bcsv_2", &bcsv_2);
    arbre->SetBranchAddress("beta_1", &beta_1);
    arbre->SetBranchAddress("bphi_1", &bphi_1);
    arbre->SetBranchAddress("bpt_2", &bpt_2);
    arbre->SetBranchAddress("beta_2", &beta_2);
    arbre->SetBranchAddress("bphi_2", &bphi_2);
    arbre->SetBranchAddress("bflavor_1", &bflavor_1);
    arbre->SetBranchAddress("bflavor_2", &bflavor_2);
    arbre->SetBranchAddress("genweight", &genweight);

    arbre->SetBranchAddress("mjj", &mjj);
    arbre->SetBranchAddress("mjj_JetAbsoluteDown", &mjj_JetAbsoluteDown);
    arbre->SetBranchAddress("mjj_JetAbsoluteUp", &mjj_JetAbsoluteUp);
    arbre->SetBranchAddress("mjj_JetAbsoluteyearDown", &mjj_JetAbsoluteyearDown);
    arbre->SetBranchAddress("mjj_JetAbsoluteyearUp", &mjj_JetAbsoluteyearUp);
    arbre->SetBranchAddress("mjj_JetBBEC1Down", &mjj_JetBBEC1Down);
    arbre->SetBranchAddress("mjj_JetBBEC1Up", &mjj_JetBBEC1Up);
    arbre->SetBranchAddress("mjj_JetBBEC1yearDown", &mjj_JetBBEC1yearDown);
    arbre->SetBranchAddress("mjj_JetBBEC1yearUp", &mjj_JetBBEC1yearUp);
    arbre->SetBranchAddress("mjj_JetEC2Down", &mjj_JetEC2Down);
    arbre->SetBranchAddress("mjj_JetEC2Up", &mjj_JetEC2Up);
    arbre->SetBranchAddress("mjj_JetEC2yearDown", &mjj_JetEC2yearDown);
    arbre->SetBranchAddress("mjj_JetEC2yearUp", &mjj_JetEC2yearUp);
    arbre->SetBranchAddress("mjj_JetFlavorQCDDown", &mjj_JetFlavorQCDDown);
    arbre->SetBranchAddress("mjj_JetFlavorQCDUp", &mjj_JetFlavorQCDUp);
    arbre->SetBranchAddress("mjj_JetHFDown", &mjj_JetHFDown);
    arbre->SetBranchAddress("mjj_JetHFUp", &mjj_JetHFUp);
    arbre->SetBranchAddress("mjj_JetHFyearDown", &mjj_JetHFyearDown);
    arbre->SetBranchAddress("mjj_JetHFyearUp", &mjj_JetHFyearUp);
    arbre->SetBranchAddress("mjj_JetRelativeBalDown", &mjj_JetRelativeBalDown);
    arbre->SetBranchAddress("mjj_JetRelativeBalUp", &mjj_JetRelativeBalUp);
    arbre->SetBranchAddress("mjj_JetRelativeSampleDown", &mjj_JetRelativeSampleDown);
    arbre->SetBranchAddress("mjj_JetRelativeSampleUp", &mjj_JetRelativeSampleUp);
    arbre->SetBranchAddress("mjj_JERDown", &mjj_JERDown);
    arbre->SetBranchAddress("mjj_JERUp", &mjj_JERUp);

    arbre->SetBranchAddress("l2_decayMode",&l2_decayMode);
    arbre->SetBranchAddress("byVVVLooseDeepVSjet_2",&byVVVLooseDeepVSjet_2);
    arbre->SetBranchAddress("byVVLooseDeepVSjet_2",&byVVLooseDeepVSjet_2);
    arbre->SetBranchAddress("byVLooseDeepVSjet_2",&byVLooseDeepVSjet_2);
    arbre->SetBranchAddress("byLooseDeepVSjet_2",&byLooseDeepVSjet_2);
    arbre->SetBranchAddress("byMediumDeepVSjet_2",&byMediumDeepVSjet_2);
    arbre->SetBranchAddress("byTightDeepVSjet_2",&byTightDeepVSjet_2);
    arbre->SetBranchAddress("byVTightDeepVSjet_2",&byVTightDeepVSjet_2);
    arbre->SetBranchAddress("byVLooseDeepVSmu_2",&byVLooseDeepVSmu_2);
    arbre->SetBranchAddress("byLooseDeepVSmu_2",&byLooseDeepVSmu_2);
    arbre->SetBranchAddress("byMediumDeepVSmu_2",&byMediumDeepVSmu_2);
    arbre->SetBranchAddress("byTightDeepVSmu_2",&byTightDeepVSmu_2);
    arbre->SetBranchAddress("byVTightDeepVSmu_2",&byVTightDeepVSmu_2);
    arbre->SetBranchAddress("byVVVLooseDeepVSe_2",&byVVVLooseDeepVSe_2);
    arbre->SetBranchAddress("byVVLooseDeepVSe_2",&byVVLooseDeepVSe_2);
    arbre->SetBranchAddress("byVLooseDeepVSe_2",&byVLooseDeepVSe_2);
    arbre->SetBranchAddress("byLooseDeepVSe_2",&byLooseDeepVSe_2);
    arbre->SetBranchAddress("byMediumDeepVSe_2",&byMediumDeepVSe_2);
    arbre->SetBranchAddress("byTightDeepVSe_2",&byTightDeepVSe_2);
    arbre->SetBranchAddress("byVTightDeepVSe_2",&byVTightDeepVSe_2);
    arbre->SetBranchAddress("gen_match_1",&gen_match_1);
    arbre->SetBranchAddress("gen_match_2",&gen_match_2);
    arbre->SetBranchAddress("npu",&npu);
    arbre->SetBranchAddress("genpT",&genpT);
    arbre->SetBranchAddress("genM",&genM);
    arbre->SetBranchAddress("pt_top1",&pt_top1);
    arbre->SetBranchAddress("pt_top2",&pt_top2);
    arbre->SetBranchAddress("numGenJets",&numGenJets);

    arbre->SetBranchAddress("Flag_BadChargedCandidateFilter",&Flag_BadChargedCandidateFilter);
    arbre->SetBranchAddress("Flag_BadPFMuonFilter",&Flag_BadPFMuonFilter);
    arbre->SetBranchAddress("Flag_EcalDeadCellTriggerPrimitiveFilter",&Flag_EcalDeadCellTriggerPrimitiveFilter);
    arbre->SetBranchAddress("Flag_HBHENoiseFilter",&Flag_HBHENoiseFilter);
    arbre->SetBranchAddress("Flag_HBHENoiseIsoFilter",&Flag_HBHENoiseIsoFilter);
    arbre->SetBranchAddress("Flag_eeBadScFilter",&Flag_eeBadScFilter);
    arbre->SetBranchAddress("Flag_goodVertices",&Flag_goodVertices);
    arbre->SetBranchAddress("Flag_globalSuperTightHalo2016Filter",&Flag_globalSuperTightHalo2016Filter);
    arbre->SetBranchAddress("Flag_ecalBadCalibFilter",&Flag_ecalBadCalibFilter);
    arbre->SetBranchAddress("Flag_duplicateMuons",&Flag_duplicateMuons);
    arbre->SetBranchAddress("Flag_badMuons",&Flag_badMuons);
    arbre->SetBranchAddress("Flag_ecalBadCalibReducedMINIAODFilter",&Flag_ecalBadCalibReducedMINIAODFilter);

    arbre->SetBranchAddress("matchEmbFilter_Ele24Tau30_1",&matchEmbFilter_Ele24Tau30_1);
    arbre->SetBranchAddress("matchEmbFilter_Ele32DoubleL1v1_1",&matchEmbFilter_Ele32DoubleL1v1_1);
    arbre->SetBranchAddress("matchEmbFilter_Ele32DoubleL1v2_1",&matchEmbFilter_Ele32DoubleL1v2_1);
    arbre->SetBranchAddress("matchEmbFilter_Ele32_1",&matchEmbFilter_Ele32_1);
    arbre->SetBranchAddress("matchEmbFilter_Ele35_1",&matchEmbFilter_Ele35_1);
    arbre->SetBranchAddress("matchEmbFilter_Ele24Tau30_2",&matchEmbFilter_Ele24Tau30_2);

   bool is_ggh=(sample.find("ggH") < 140);
   bool is_qqh=(sample.find("qqH") < 140);
   int nbhist=1;

   TH1F* h_pt0to45=new TH1F ("h_pt0to45","h_pt0to45",12,50,290); h_pt0to45->Sumw2();
   TH1F* h_pt45to80=new TH1F ("h_pt45to80","h_pt45to80",12,50,290); h_pt45to80->Sumw2();
   TH1F* h_pt80to120=new TH1F ("h_pt80to120","h_pt80to120",12,50,290); h_pt80to120->Sumw2();
   TH1F* h_pt120to200=new TH1F ("h_pt120to200","h_pt120to200",12,50,290); h_pt120to200->Sumw2();
   TH1F* h_pt200to350=new TH1F ("h_pt200to350","h_pt200to350",12,50,290); h_pt200to350->Sumw2();
   TH1F* h_pt350to450=new TH1F ("h_pt350to450","h_pt350to450",12,50,290); h_pt350to450->Sumw2();
   TH1F* h_ptgt450=new TH1F ("h_ptgt450","h_ptgt450",12,50,290); h_ptgt450->Sumw2();

   TH1F* h_njets0=new TH1F ("h_njets0","h_njets0",12,50,290); h_njets0->Sumw2();
   TH1F* h_njets1=new TH1F ("h_njets1","h_njets1",12,50,290); h_njets1->Sumw2();
   TH1F* h_njets2=new TH1F ("h_njets2","h_njets2",12,50,290); h_njets2->Sumw2();
   TH1F* h_njets3=new TH1F ("h_njets3","h_njets3",12,50,290); h_njets3->Sumw2();
   TH1F* h_njets4=new TH1F ("h_njets4","h_njets4",12,50,290); h_njets4->Sumw2();

   TH1F* h_j1pt30to60=new TH1F ("h_j1pt30to60","h_j1pt30to60",12,50,290); h_j1pt30to60->Sumw2();
   TH1F* h_j1pt60to120=new TH1F ("h_j1pt60to120","h_j1pt60to120",12,50,290); h_j1pt60to120->Sumw2();
   TH1F* h_j1pt120to200=new TH1F ("h_j1pt120to200","h_j1pt120to200",12,50,290); h_j1pt120to200->Sumw2();
   TH1F* h_j1pt200to350=new TH1F ("h_j1pt200to350","h_j1pt200to350",12,50,290); h_j1pt200to350->Sumw2();
   TH1F* h_j1ptgt350=new TH1F ("h_j1ptgt350","h_j1ptgt350",12,50,290); h_j1ptgt350->Sumw2();

   reweight::LumiReWeighting* LumiWeights_12;
   LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2018.root", "pu_distributions_data_2018.root", "pileup", "pileup");

   TFile *ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco.root");
   TF1 *fct_tauid= (TF1*) ftauid->Get("Medium_cent");
   TF1 *fct_tauid_up= (TF1*) ftauid->Get("Medium_up");
   TF1 *fct_tauid_down= (TF1*) ftauid->Get("Medium_down");

   TFile *ftauid_emb = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco_EMB.root");
   TF1 *fct_tauid_emb= (TF1*) ftauid_emb->Get("Medium_cent");
   TF1 *fct_tauid_emb_up= (TF1*) ftauid_emb->Get("Medium_up");
   TF1 *fct_tauid_emb_down= (TF1*) ftauid_emb->Get("Medium_down");


   TFile fw("htt_scalefactors_legacy_2018.root");
   RooWorkspace *w = (RooWorkspace*)fw.Get("w");
   fw.Close();

   TFile fwmc("htt_scalefactors_legacy_2018.root");
   RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
   fwmc.Close();

   TFile * f_NNLOPS = new TFile("NNLOPS_reweight.root");
   TGraph * g_NNLOPS_0jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_0jet");
   TGraph * g_NNLOPS_1jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_1jet");
   TGraph * g_NNLOPS_2jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_2jet");
   TGraph * g_NNLOPS_3jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_3jet");

   bool do_rivet=(name.find("xH") < 140 or name.find("ttH") < 140 or name.find("ggH") < 140 or name.find("qqH") < 140 or name.find("VH") < 140 or name.find("WH") < 140 or name.find("ZH") < 140);

   bool norecoil=(name.find("WH") < 140 or name.find("ZH") < 140 or name=="TT" or name=="VV" or name=="ST");
   bool is_inclusivesignal=false;
   if (name=="ggH_htt125" or name=="qqH_htt125" or name=="WH_htt125" or name=="ZH_htt125" or name=="ggH_hww125" or name=="qqH_hww125" or name=="WH_hww125" or name=="ZH_hww125") is_inclusivesignal=true;

   float lheweight_nominalTo2_average=1.0;
   float lheweight_nominalTo0p5_average=1.0;

   TFile *f_QCDScaleAcceptance_GGHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGHTT2018.root");
   if (sample=="GGZHQQTT125") f_QCDScaleAcceptance_GGHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGZHQQTT2018.root");
   TH1F *h_QCDScaleAcceptance_ggH = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH");
   TH1F *h_QCDScaleAcceptance_ggH_scale_0jet = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_0jet");
   TH1F *h_QCDScaleAcceptance_ggH_scale_1jet_lowpt = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_1jet_lowpt");
   TH1F *h_QCDScaleAcceptance_ggH_scale_2jet_lowpt = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_2jet_lowpt");
   TH1F *h_QCDScaleAcceptance_ggH_scale_highpt = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_highpt");
   TH1F *h_QCDScaleAcceptance_ggH_scale_very_highpt = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_very_highpt");
   TH1F *h_QCDScaleAcceptance_ggH_scale_vbf = (TH1F*) f_QCDScaleAcceptance_GGHTT->Get("demo/h_nevents_ggH_scale_vbf");

   TFile *f_QCDScaleAcceptance_VBFHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/VBFHTT2018.root");
   TH1F *h_QCDScaleAcceptance_vbf = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf");
   TH1F *h_QCDScaleAcceptance_vbf_scale_0jet = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf_scale_0jet");
   TH1F *h_QCDScaleAcceptance_vbf_scale_1jet = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf_scale_1jet");
   TH1F *h_QCDScaleAcceptance_vbf_scale_lowmjj = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf_scale_lowmjj");
   TH1F *h_QCDScaleAcceptance_vbf_scale_highmjj_lowpt = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf_scale_highmjj_lowpt");
   TH1F *h_QCDScaleAcceptance_vbf_scale_highmjj_highpt = (TH1F*) f_QCDScaleAcceptance_VBFHTT->Get("demo/h_nevents_vbf_scale_highmjj_highpt");

   TFile *f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/WplusHTT2018.root");
   if (sample=="WminusH125") f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/WminusHTT2018.root");
   if (sample=="ZH125") f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/ZHTT2018.root");
   if (sample=="GGZHLLTT125") f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGZHLLTT2018.root");
   if (sample=="GGZHNNTT125") f_QCDScaleAcceptance_VHTT = new TFile("/afs/cern.ch/work/c/ccaillol/public/QCDScaleAcceptance/GGZHNNTT2018.root");
   TH1F *h_QCDScaleAcceptance_VH = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf");
   TH1F *h_QCDScaleAcceptance_VH_scale_0jet = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_0jet");
   TH1F *h_QCDScaleAcceptance_VH_scale_1jet = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_1jet");
   TH1F *h_QCDScaleAcceptance_VH_scale_lowmjj = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_lowmjj");
   TH1F *h_QCDScaleAcceptance_VH_scale_highmjj_lowpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_highmjj_lowpt");
   TH1F *h_QCDScaleAcceptance_VH_scale_highmjj_highpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_vbf_scale_highmjj_highpt");
   TH1F *h_QCDScaleAcceptance_WH_lep = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_WH_lep");
   TH1F *h_QCDScaleAcceptance_ZH_lep = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_ZH_lep");
   TH1F *h_QCDScaleAcceptance_WH_scale_lowpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_WH_scale_lowpt");
   TH1F *h_QCDScaleAcceptance_WH_scale_highpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_WH_scale_highpt");
   TH1F *h_QCDScaleAcceptance_ZH_scale_lowpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_ZH_scale_lowpt");
   TH1F *h_QCDScaleAcceptance_ZH_scale_highpt = (TH1F*) f_QCDScaleAcceptance_VHTT->Get("demo/h_nevents_ZH_scale_highpt");

   // GGH scale (for GGH and GGZHQQTT)
   /*if (name=="ggH_htt125" or name=="ggZH_had_htt125") {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH->GetBinContent(1)/h_QCDScaleAcceptance_ggH->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH->GetBinContent(1)/h_QCDScaleAcceptance_ggH->GetBinContent(9); postfixMC[81]="_ggH_scaleDown"; postfixMC[82]="_ggH_scaleUp";}
   if (name.find("H_PTH_0_200_0J_PTH_0_10_htt1") < 140 or name.find("H_PTH_0_200_0J_PTH_10_200_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_0jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_0jet->GetBinContent(9); postfixMC[81]="_ggH_scale_0jetDown"; postfixMC[82]="_ggH_scale_0jetUp";}
   if (name.find("H_PTH_0_200_1J_PTH_0_60_htt1") < 140 or name.find("H_PTH_0_200_1J_PTH_60_120_htt1") < 140 or name.find("H_PTH_0_200_1J_PTH_120_200_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_1jet_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_1jet_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_1jet_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_1jet_lowpt->GetBinContent(9); postfixMC[81]="_ggH_scale_1jet_lowptDown"; postfixMC[82]="_ggH_scale_1jet_lowptUp";}
   if (name.find("H_PTH_0_200_GE2J_MJJ_0_350_PTH_0_60_htt1") < 140 or name.find("H_PTH_0_200_GE2J_MJJ_0_350_PTH_60_120_htt1") < 140 or name.find("H_PTH_0_200_GE2J_MJJ_0_350_PTH_120_200_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_2jet_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_2jet_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_2jet_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_2jet_lowpt->GetBinContent(9); postfixMC[81]="_ggH_scale_2jet_lowptDown"; postfixMC[82]="_ggH_scale_2jet_lowptUp";}
   if (name.find("H_PTH_200_300_htt1") < 140 or name.find("H_PTH_300_450_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_highpt->GetBinContent(9); postfixMC[81]="_ggH_scale_highptDown"; postfixMC[82]="_ggH_scale_highptUp";}
   if (name.find("H_PTH_450_650_htt1") < 140 or name.find("H_PTH_GE650_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_very_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_very_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_very_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_very_highpt->GetBinContent(9); postfixMC[81]="_ggH_scale_very_highptDown"; postfixMC[82]="_ggH_scale_very_highptUp";}
   if (name.find("H_PTH_0_200_GE2J_MJJ_350_700_PTHJJ_0_25_htt1") < 140 or name.find("H_PTH_0_200_GE2J_MJJ_350_700_PTHJJ_GE25_htt1") < 140 or name.find("H_PTH_0_200_GE2J_MJJ_GE700_PTHJJ_0_25_htt1") < 140 or name.find("H_PTH_0_200_GE2J_MJJ_GE700_PTHJJ_GE25_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ggH_scale_vbf->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_vbf->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ggH_scale_vbf->GetBinContent(1)/h_QCDScaleAcceptance_ggH_scale_vbf->GetBinContent(9); postfixMC[81]="_ggH_scale_vbfDown"; postfixMC[82]="_ggH_scale_vbfUp";}

   // VBF scale
   if (name=="qqH_htt125") {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf->GetBinContent(1)/h_QCDScaleAcceptance_vbf->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf->GetBinContent(1)/h_QCDScaleAcceptance_vbf->GetBinContent(9); postfixMC[81]="_vbf_scaleDown"; postfixMC[82]="_vbf_scaleUp";}
   if (name.find("qqH_0J_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_0jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_0jet->GetBinContent(9); postfixMC[81]="_vbf_scale_0jetDown"; postfixMC[82]="_vbf_scale_0jetUp";}
   if (name.find("qqH_1J_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf_scale_1jet->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_1jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf_scale_1jet->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_1jet->GetBinContent(9); postfixMC[81]="_vbf_scale_1jetDown"; postfixMC[82]="_vbf_scale_1jetUp";}
   if (name.find("qqH_GE2J_MJJ_0_60_htt1") < 140 or name.find("qqH_GE2J_MJJ_60_120_htt1") < 140 or name.find("qqH_GE2J_MJJ_120_350_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf_scale_lowmjj->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_lowmjj->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf_scale_lowmjj->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_lowmjj->GetBinContent(9); postfixMC[81]="_vbf_scale_lowmjjDown"; postfixMC[82]="_vbf_scale_lowmjjUp";}
   if (name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_0_25_htt1") < 140 or name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_GE25_htt1") < 140 or name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_0_25_htt1") < 140 or name.find("qqH_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_GE25_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf_scale_highmjj_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_highmjj_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf_scale_highmjj_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_highmjj_lowpt->GetBinContent(9); postfixMC[81]="_vbf_scale_highmjj_lowptDown"; postfixMC[82]="_vbf_scale_highmjj_lowptUp";}
   if (name.find("qqH_GE2J_MJJ_GE350_PTH_GE200_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf_scale_highmjj_highpt->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_highmjj_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf_scale_highmjj_highpt->GetBinContent(1)/h_QCDScaleAcceptance_vbf_scale_highmjj_highpt->GetBinContent(9); postfixMC[81]="_vbf_scale_highmjj_highptDown"; postfixMC[82]="_vbf_scale_highmjj_highptUp";}

   // VH had scale
   if (sample=="WminusH125" or sample=="WplusH125" or sample=="ZH125"){
     if (name=="WH_had_htt125" or name=="ZH_had_htt125") {lheweight_nominalTo2_average= h_QCDScaleAcceptance_vbf->GetBinContent(1)/h_QCDScaleAcceptance_vbf->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_vbf->GetBinContent(1)/h_QCDScaleAcceptance_vbf->GetBinContent(9); postfixMC[81]="_VH_scaleDown"; postfixMC[82]="_VH_scaleUp";}
     if (name.find("H_0J_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_0jet->GetBinContent(9); postfixMC[81]="_VH_scale_0jetDown"; postfixMC[82]="_VH_scale_0jetUp";}
     if (name.find("H_1J_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_1jet->GetBinContent(9); postfixMC[81]="_VH_scale_1jetDown"; postfixMC[82]="_VH_scale_1jetUp";}
     if (name.find("H_GE2J_MJJ_0_60_htt1") < 140 or name.find("H_GE2J_MJJ_60_120_htt1") < 140 or name.find("H_GE2J_MJJ_120_350_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_lowmjj->GetBinContent(9); postfixMC[81]="_VH_scale_lowmjjDown"; postfixMC[82]="_VH_scale_lowmjjUp";}
     if (name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_0_25_htt1") < 140 or name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_350_700_PTHJJ_GE25_htt1") < 140 or name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_0_25_htt1") < 140 or name.find("H_GE2J_MJJ_GE350_PTH_0_200_MJJ_GE700_PTHJJ_GE25_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_lowpt->GetBinContent(9); postfixMC[81]="_VH_scale_highmjj_lowptDown"; postfixMC[82]="_VH_scale_highmjj_lowptUp";}
     if (name.find("H_GE2J_MJJ_GE350_PTH_GE200_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(1)/h_QCDScaleAcceptance_VH_scale_highmjj_highpt->GetBinContent(9); postfixMC[81]="_VH_scale_highmjj_highptDown"; postfixMC[82]="_VH_scale_highmjj_highptUp";}
   }

   // VH lep scale
   if (sample=="WminusH125" or sample=="WplusH125" or sample=="ZH125" or sample=="GGZHLLTT125" or sample=="GGZHNNTT125"){
      if (name=="WH_lep_htt125") {lheweight_nominalTo2_average= h_QCDScaleAcceptance_WH_lep->GetBinContent(1)/h_QCDScaleAcceptance_WH_lep->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_WH_lep->GetBinContent(1)/h_QCDScaleAcceptance_WH_lep->GetBinContent(9); postfixMC[81]="_WHlep_scaleDown"; postfixMC[82]="_WHlep_scaleUp";}
      if (name=="ggZH_lep_htt125" or name=="ZH_lep_htt125") {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ZH_lep->GetBinContent(1)/h_QCDScaleAcceptance_ZH_lep->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ZH_lep->GetBinContent(1)/h_QCDScaleAcceptance_ZH_lep->GetBinContent(9); postfixMC[81]="_ZHlep_scaleDown"; postfixMC[82]="_ZHlep_scaleUp";}
      if (name.find("WH_lep_PTV_0_75_htt1") < 140 or name.find("WH_lep_PTV_75_150_htt1") < 140 or name.find("WH_lep_PTV_150_250_0J_htt1") < 140 or name.find("WH_lep_PTV_150_250_GE1J_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_lowpt->GetBinContent(9); postfixMC[81]="_WH_scale_lowptDown"; postfixMC[82]="_WH_scale_lowptUp";}
      if (name.find("WH_lep_PTV_GT250_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_WH_scale_highpt->GetBinContent(9); postfixMC[81]="_WH_scale_highptDown"; postfixMC[82]="_WH_scale_highptUp";}
      if (name.find("ZH_lep_PTV_0_75_htt1") < 140 or name.find("ZH_lep_PTV_75_150_htt1") < 140 or name.find("ZH_lep_PTV_150_250_0J_htt1") < 140 or name.find("ZH_lep_PTV_150_250_GE1J_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_lowpt->GetBinContent(9); postfixMC[81]="_ZH_scale_lowptDown"; postfixMC[82]="_ZH_scale_lowptUp";}
      if (name.find("ZH_lep_PTV_GT250_htt1") < 140) {lheweight_nominalTo2_average= h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(5);  lheweight_nominalTo0p5_average=h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(1)/h_QCDScaleAcceptance_ZH_scale_highpt->GetBinContent(9); postfixMC[81]="_ZH_scale_highptDown"; postfixMC[82]="_ZH_scale_highptUp";}
   }*/

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

lheweight_nominal=1.0;//

        TLorentzVector mygenmet;
        TLorentzVector mygenele;
        mygenmet.SetPtEtaPhiM(gen_met_pt,0,gen_met_phi,0);
        mygenele.SetPtEtaPhiM(gen_ele_pt,gen_ele_eta,gen_ele_phi,0);
        float genmt=TMass_F(mygenele.Pt(),mygenmet.Pt(),mygenele.Px(),mygenmet.Px(),mygenele.Py(),mygenmet.Py());
        bool is_fiducial=(HTTgenfinalstate==2 && fabs(gen_ele_eta)<2.1 && gen_ele_pt>25 && fabs(gen_tauh_eta)<2.3 and gen_tauh_pt>30 && genmt<50);

        TLorentzVector Rivet_jet2;
        TLorentzVector Rivet_jet1;
	float Rivet_mjj=-1;
 	if (do_rivet && do_differential && Rivet_nJets30>1){ 
	   Rivet_jet1.SetPtEtaPhiM(Rivet_j1pt,Rivet_j1eta,Rivet_j1phi,Rivet_j1m);
           Rivet_jet2.SetPtEtaPhiM(Rivet_j2pt,Rivet_j2eta,Rivet_j2phi,Rivet_j2m);
	   Rivet_mjj=(Rivet_jet1+Rivet_jet2).M();
	}

        if (sample.find("WW")<140) is_fiducial=false;
        if (name.find("OutsideAcceptance") < 140 && is_fiducial) continue;

	if (do_rivet && do_differential && !is_inclusivesignal){
           if (name.find("OutsideAcceptance") > 140 && !is_fiducial) continue;

           if (name.find("H_PTH_0_20") < 140 && !(Rivet_higgsPt>=0 && Rivet_higgsPt<20)) continue;
           if (name.find("H_PTH_20_45") < 140 && !(Rivet_higgsPt>=20 && Rivet_higgsPt<45)) continue;
           if (name.find("H_PTH_0_45") < 140 && !(Rivet_higgsPt>=0 && Rivet_higgsPt<45)) continue;
           if (name.find("H_PTH_45_80") < 140 && !(Rivet_higgsPt>=45 && Rivet_higgsPt<80)) continue;
           if (name.find("H_PTH_80_120") < 140 && !(Rivet_higgsPt>=80 && Rivet_higgsPt<120)) continue;
           if (name.find("H_PTH_120_200") < 140 && !(Rivet_higgsPt>=120 && Rivet_higgsPt<200)) continue;
           if (name.find("H_PTH_200_350") < 140 && !(Rivet_higgsPt>=200 && Rivet_higgsPt<350)) continue;
           if (name.find("H_PTH_350_600") < 140 && !(Rivet_higgsPt>=350 && Rivet_higgsPt<600)) continue;
           if (name.find("H_PTH_350_450") < 140 && !(Rivet_higgsPt>=350 && Rivet_higgsPt<450)) continue;
           if (name.find("H_PTH_GT600") < 140 && !(Rivet_higgsPt>=600)) continue;
           if (name.find("H_PTH_GT450") < 140 && !(Rivet_higgsPt>=450)) continue;

           if (name.find("H_NJ_0") < 140 && !(Rivet_nJets30==0)) continue;
           if (name.find("H_NJ_1") < 140 && !(Rivet_nJets30==1)) continue;
           if (name.find("H_NJ_2") < 140 && !(Rivet_nJets30==2)) continue;
           if (name.find("H_NJ_3") < 140 && !(Rivet_nJets30==3)) continue;
           if (name.find("H_NJ_GE4") < 140 && !(Rivet_nJets30>=4)) continue;

           if (name.find("H_J1PT_30_60") < 140 && !(Rivet_j1pt>=30 && Rivet_j1pt<60)) continue;
           if (name.find("H_J1PT_60_120") < 140 && !(Rivet_j1pt>=60 && Rivet_j1pt<120)) continue;
           if (name.find("H_J1PT_120_200") < 140 && !(Rivet_j1pt>=120 && Rivet_j1pt<200)) continue;
           if (name.find("H_J1PT_200_350") < 140 && !(Rivet_j1pt>=200 && Rivet_j1pt<350)) continue;
           if (name.find("H_J1PT_GT350") < 140 && !(Rivet_j1pt>=350)) continue;

           if (name.find("H_MJJ_0_150") < 140 && !(Rivet_mjj>=0 && Rivet_mjj<150)) continue;
           if (name.find("H_MJJ_150_300") < 140 && !(Rivet_mjj>=150 && Rivet_mjj<300)) continue;
           if (name.find("H_MJJ_300_450") < 140 && !(Rivet_mjj>=300 && Rivet_mjj<450)) continue;
           if (name.find("H_MJJ_450_600") < 140 && !(Rivet_mjj>=450 && Rivet_mjj<600)) continue;
           if (name.find("H_MJJ_600_1000") < 140 && !(Rivet_mjj>=600 && Rivet_mjj<1000)) continue;
           if (name.find("H_MJJ_1000_1400") < 140 && !(Rivet_mjj>=1000 && Rivet_mjj<1400)) continue;
           if (name.find("H_MJJ_1400_1800") < 140 && !(Rivet_mjj>=1400 && Rivet_mjj<1800)) continue;
           if (name.find("H_MJJ_GE1800") < 140 && !(Rivet_mjj>=1800 && Rivet_mjj<10000000)) continue;
	}	   

	if (fabs(eta_1)>2.1) continue;
        if (fabs(eta_2)>2.3) continue;

        int nbtag20=0;
        float bMpt_1=0;
        float bMflavor_1=0;
        float bMpt_2=0;
        float bMflavor_2=0;
        if (bpt_1>20 && bcsv_1>0.4184){
           bMpt_1=bpt_1;
           bMflavor_1=bflavor_1;
           nbtag20++;
        }
        if (bpt_2>20 && bcsv_2>0.4184){
           bMpt_2=bpt_2;
           bMflavor_2=bflavor_2;
           nbtag20++;
        }
        if ((sample=="data_obs" or sample=="embedded") && nbtag20>0) continue;

        if (Flag_goodVertices) continue;
        if (Flag_globalSuperTightHalo2016Filter) continue;
        if (Flag_HBHENoiseFilter) continue;
        if (Flag_HBHENoiseIsoFilter) continue;
        if (Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
        if (Flag_BadPFMuonFilter) continue;
        if ((sample=="data_obs" or sample=="embedded") && Flag_eeBadScFilter) continue;
        if (Flag_ecalBadCalibReducedMINIAODFilter) continue;

        bool trigger35=(passEle35 && pt_1>32.5 && matchEle35_1 && filterEle35_1);
        bool trigger32=(passEle32 && pt_1>32.5 && matchEle32_1 && filterEle32_1);
        bool trigger2430=(passEle24Tau30 && matchEle24Tau30_1 && filterEle24Tau30_1 && matchEle24Tau30_2 && filterEle24Tau30_2 && pt_1>24.5 && pt_2>34.5 && fabs(eta_2)<2.1 && pt_1<=33.5);
        bool trigger2430HPS=(passEle24HPSTau30 && matchEle24HPSTau30_1 && filterEle24HPSTau30_1 && matchEle24HPSTau30_2 && filterEle24HPSTau30_2 && pt_1>24.5 && pt_2>34.5 && fabs(eta_2)<2.1 && pt_1<=33.5);
        if (sample=="embedded"){
                 trigger2430HPS=(matchEmbFilter_Ele24Tau30_1 && matchEmbFilter_Ele24Tau30_2 && pt_1>24.5 && pt_2>34.5 && fabs(eta_2)<2.1 && pt_1<=33.5);
                 trigger35=(pt_1>32.5 && passEle35 && matchEle35_1 && filterEle35_1);
                 trigger32=(pt_1>32.5 && passEle32 && matchEle32_1 && filterEle32_1);
        }
        if (sample=="data_obs" && run<317509 && !trigger2430 && !trigger32 && !trigger35) continue;
        if (sample=="data_obs" && run>=317509 && !trigger2430HPS && !trigger32 && !trigger35) continue;
        if (sample!="data_obs" && !trigger32 && !trigger35 && !trigger2430HPS) continue;

        if (!byTightDeepVSe_2 or !byVLooseDeepVSmu_2) continue;
	if (iso_1>0.15) continue;
        float signalRegion=(byMediumDeepVSjet_2 && iso_1<0.15);
        float antiisoRegion=(byVVVLooseDeepVSjet_2 && !byMediumDeepVSjet_2 && iso_1<0.15);

	TLorentzVector mytau; 
	mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);

	if (myele.DeltaR(mytau)<0.5) continue;
        if (myele.DeltaR(mytau)<0.8) continue; //FIXME

        if (sample=="W"){
            weight=51.749;
            if (numGenJets==1) weight=10.170;
            else if (numGenJets==2) weight=4.51855;
            else if (numGenJets==3) weight=3.07747;
            else if (numGenJets==4) weight=3.2113;
        }

        if (sample=="DY" or sample=="Z"){
            weight=3.6234;
            if (numGenJets==1) weight=0.6298;
            else if (numGenJets==2) weight=0.5521;
            else if (numGenJets==3) weight=0.5995;
            else if (numGenJets==4) weight=0.8211;
	    if (njets>1 && numGenJets==0) continue;
        }

	if (sample=="embedded" && gen_match_2!=5) continue;
        bool is_includedInEmbedded=false;
        //if ((name.find("ggH")>100 && name.find("xH")>100 && name.find("125")>100 && name.find("qqH")>100 && name.find("WH")>100 && name.find("ZH")>100 && name.find("ttH")>100 && sample!="data_obs" && sample!="embedded") && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) is_includedInEmbedded=true; // remove overlap with embedded samples
        if (sample!="ggH" and sample!="ggH_htt125" and sample!="qqH" and sample!="qqH_htt125" and sample!="WminusH125" and sample!="WplusH125" and sample!="ZH125" and sample!="ttHTT" and sample!="ttHnonbb" and sample!="GGZHLLTT" and sample!="GGZHQQTT" and sample!="GGZHNNTT" and sample!="data_obs" and sample!="embedded" and gen_match_1>2 and gen_match_1<6 and gen_match_2>2 and gen_match_2<6) is_includedInEmbedded=true; // remove overlap with embedded samples
        bool isT=(!is_includedInEmbedded && gen_match_2==5);
        bool isL=(!is_includedInEmbedded && gen_match_2<5);

	float aweight=genweight*weight*LumiWeights_12->weight(npu);
        if (sample=="embedded") aweight=genweight;
	if (sample=="data_obs") aweight=1.0;

	if (byMediumDeepVSjet_2 && sample!="embedded" && sample!="data_obs" && gen_match_2==5) aweight=aweight*fct_tauid->Eval(mytau.Pt());
        if (byMediumDeepVSjet_2 && sample=="embedded" && gen_match_2==5) aweight=aweight*fct_tauid_emb->Eval(mytau.Pt());

	if (sample!="embedded" && sample!="data_obs" && (gen_match_2==1 or gen_match_2==3)){
	   if (fabs(eta_2)<1.460) aweight=aweight*1.47;
           else if (fabs(eta_2)>1.558) aweight=aweight*0.66;
	   else aweight=0.0;

	}
        if (sample!="embedded" && sample!="data_obs" && (gen_match_2==2 or gen_match_2==4)){
             if (fabs(eta_2)<0.4) aweight=aweight*0.936*1.019;
             else if (fabs(eta_2)<0.8) aweight=aweight*0.874*1.154;
             else if (fabs(eta_2)<1.2) aweight=aweight*0.912*1.128;
             else if (fabs(eta_2)<1.7) aweight=aweight*0.953*0.974;
             else aweight=aweight*0.936*5.342;
        }

	//NNLOPS weights
        /*if (name.find("ggH")<100 && name.find("NNLOPS")>100 && name.find("hww")>100){
            if (Rivet_nJets30==0) aweight = aweight * g_NNLOPS_0jet->Eval(min(Rivet_higgsPt,float(125.0)));
            if (Rivet_nJets30==1) aweight = aweight * g_NNLOPS_1jet->Eval(min(Rivet_higgsPt,float(625.0)));
            if (Rivet_nJets30==2) aweight = aweight * g_NNLOPS_2jet->Eval(min(Rivet_higgsPt,float(800.0)));
            if (Rivet_nJets30>=3) aweight = aweight * g_NNLOPS_3jet->Eval(min(Rivet_higgsPt,float(925.0)));
        }*/
	NumV WG1unc = qcd_ggF_uncert_2017(Rivet_nJets30, Rivet_higgsPt, Rivet_stage1_cat_pTjet30GeV);

	TLorentzVector mymet;
	mymet.SetPtEtaPhiM(met,0,metphi,0);

        float trg_up=1.0;
        float trg_down=1.0;

	if (sample=="data_obs") aweight=1.0;

        if (sample=="embedded"){
          wmc->var("e_pt")->setVal(myele.Pt());
          wmc->var("e_eta")->setVal(myele.Eta());
          wmc->var("e_iso")->setVal(iso_1);
          wmc->var("t_pt")->setVal(35.0);//mytau.Pt());
          wmc->var("t_eta")->setVal(mytau.Eta());
          wmc->var("t_phi")->setVal(mytau.Phi());
          wmc->var("t_dm")->setVal(l2_decayMode);
	  if (myele.Pt()<33) aweight=aweight*wmc->function("e_trg_24_ic_embed_ratio")->getVal()*wmc->function("t_trg_mediumDeepTau_etau_embed_ratio")->getVal();
          if (myele.Pt()>33)  aweight=aweight*wmc->function("e_trg_ic_embed_ratio")->getVal();

          wmc->var("gt1_pt")->setVal(1.69*genpt_1);
          wmc->var("gt2_pt")->setVal(1.47*mytau.Pt());
          wmc->var("gt1_eta")->setVal(geneta_1);
          wmc->var("gt2_eta")->setVal(mytau.Eta());
          if (l2_decayMode==0) aweight=aweight*0.975;
          else if (l2_decayMode==1) aweight=aweight*0.975*1.051;
          else aweight=aweight*0.975*0.975*0.975;
          aweight=aweight*wmc->function("m_sel_trg_ic_ratio")->getVal();
          wmc->var("gt_pt")->setVal(1.69*genpt_1);
          wmc->var("gt_eta")->setVal(geneta_1);
          aweight=aweight*wmc->function("m_sel_id_ic_ratio")->getVal();
          wmc->var("gt_pt")->setVal(1.47*mytau.Pt());
          wmc->var("gt_eta")->setVal(mytau.Eta());
          aweight=aweight*wmc->function("m_sel_id_ic_ratio")->getVal();
          aweight=aweight*wmc->function("e_trk_embed_ratio")->getVal();
          aweight=aweight*wmc->function("e_idiso_ic_embed_ratio")->getVal();

          if (genweight>1) aweight=0.0;
        }


	// Top pT reweighting
        float topfactor=1.0;
        if (name=="TT"){
           float pttop1=pt_top1;
           if (pttop1>472) pttop1=472;
           float pttop2=pt_top2;
           if (pttop2>472) pttop2=472;
           topfactor=sqrt(exp(0.088-0.00087*pttop1+0.00000092*pttop1*pttop1)*exp(0.088-0.00087*pttop2+0.00000092*pttop2*pttop2));
           aweight*=topfactor;
        }

        float zptweight=1.0;
	if (sample!="embedded" && sample!="data_obs"){
          wmc->var("z_gen_mass")->setVal(genM);
          wmc->var("z_gen_pt")->setVal(genpT);
	  zptweight=wmc->function("zptmass_weight_nom")->getVal();
	  if (sample=="DY" or sample=="Z") aweight=aweight*zptweight;
          wmc->var("e_pt")->setVal(myele.Pt());
          wmc->var("e_eta")->setVal(myele.Eta());
          wmc->var("e_iso")->setVal(iso_1);
          wmc->var("t_pt")->setVal(mytau.Pt());
          wmc->var("t_eta")->setVal(mytau.Eta());
          wmc->var("t_phi")->setVal(mytau.Phi());
          wmc->var("t_dm")->setVal(l2_decayMode);
          aweight=aweight*wmc->function("e_trk_ratio")->getVal();
          aweight=aweight*wmc->function("e_idiso_ic_ratio")->getVal();
	  float tautrgsf=wmc->function("t_trg_pog_deeptau_medium_etau_ratio")->getVal();
          if (myele.Pt()>33) aweight=aweight*wmc->function("e_trg_ic_ratio")->getVal();
	  else aweight=aweight*wmc->function("e_trg_24_ic_ratio")->getVal()*tautrgsf;
          if (tautrgsf>0) trg_up=wmc->function("t_trg_pog_deeptau_medium_etau_ratio_up")->getVal()/tautrgsf;
          if (tautrgsf>0) trg_down=wmc->function("t_trg_pog_deeptau_medium_etau_ratio_down")->getVal()/tautrgsf;


          float weight_btag=bTagEventWeight(nbtag20,bMpt_1,bMflavor_1,bMpt_2,bMflavor_2,1,0,0);
          if (nbtag20>2) weight_btag=0;
          aweight=aweight*weight_btag;

	}

	float mt=TMass_F(myele.Pt(),mymet.Pt(),myele.Px(),mymet.Px(),myele.Py(),mymet.Py());

	//************************* Fill histograms **********************
	bool is_xtrg=false;
	float pth = 1.05*(myele+mytau+mymet).Pt();
	if (myele.Pt()<33) is_xtrg=true;
	float myvar=(myele+mytau).M();
	TLorentzVector myrawtau=mytau;
        TLorentzVector myrawele=myele;
        TLorentzVector myrawmet=mymet;
        float massJets=mjj;
        int numberJets=njets;
	float leadingJetPt=jpt_1;
	float mtt=m_sv;
	float rawtaupt=mytau.Pt();
	float rawmt=mt;
	float rawmvis=(myele+mytau).M();
	float rawnjets=njets;

	   // Reapply pt cuts after shifts
           trigger35=(passEle35 && myele.Pt()>33 && matchEle35_1 && filterEle35_1);
           trigger32=(passEle32 && myele.Pt()>33 && matchEle32_1 && filterEle32_1);
           trigger2430=(passEle24Tau30 && matchEle24Tau30_1 && filterEle24Tau30_1 && matchEle24Tau30_2 && filterEle24Tau30_2 && myele.Pt()>25 && mytau.Pt()>35 && fabs(mytau.Eta())<2.1 && myele.Pt()<=33);
           trigger2430HPS=(passEle24HPSTau30 && matchEle24HPSTau30_1 && filterEle24HPSTau30_1 && matchEle24HPSTau30_2 && filterEle24HPSTau30_2 && myele.Pt()>25 && mytau.Pt()>35 && fabs(mytau.Eta())<2.1 && myele.Pt()<=33);
           if (sample=="embedded"){
		   trigger2430HPS=(matchEmbFilter_Ele24Tau30_1 && matchEmbFilter_Ele24Tau30_2 && fabs(mytau.Eta())<2.1 && myele.Pt()>25 && mytau.Pt()>35 && myele.Pt()<=33);
                   trigger35=(myele.Pt()>33 && passEle35 && matchEle35_1 && filterEle35_1);
                   trigger32=(myele.Pt()>33 && passEle32 && matchEle32_1 && filterEle32_1);
           }
           if (sample=="data_obs" && run<317509 && !trigger2430 && !trigger32 && !trigger35) continue;
           if (sample=="data_obs" && run>=317509 && !trigger2430HPS && !trigger32 && !trigger35) continue;
           if (sample!="data_obs" && !trigger32 && !trigger35 && !trigger2430HPS) continue;
           if (mytau.Pt()<30) continue;
           if (numberJets==0 and myele.DeltaR(mytau)<2.0) continue;

    	   mt=TMass_F(myele.Pt(),mymet.Pt(),myele.Px(),mymet.Px(),myele.Py(),mymet.Py());

	   if (q_1*q_2<0 && mt<50 && signalRegion){ 
	     if (pth>=0 and pth<45) h_pt0to45->Fill(m_sv,aweight);
             if (pth>=45 and pth<80) h_pt45to80->Fill(m_sv,aweight);
             if (pth>=80 and pth<120) h_pt80to120->Fill(m_sv,aweight);
             if (pth>=120 and pth<200) h_pt120to200->Fill(m_sv,aweight);
             if (pth>=200 and pth<350) h_pt200to350->Fill(m_sv,aweight);
             if (pth>=350 and pth<450) h_pt350to450->Fill(m_sv,aweight);
             if (pth>=450) h_ptgt450->Fill(m_sv,aweight);

             if (numberJets==0) h_njets0->Fill(m_sv,aweight);
             if (numberJets==1) h_njets1->Fill(m_sv,aweight);
             if (numberJets==2) h_njets2->Fill(m_sv,aweight);
             if (numberJets==3) h_njets3->Fill(m_sv,aweight);
             if (numberJets>=4) h_njets4->Fill(m_sv,aweight);

             if (jpt_1>=30 and jpt_1<60) h_j1pt30to60->Fill(m_sv,aweight);
             if (jpt_1>=60 and jpt_1<120) h_j1pt60to120->Fill(m_sv,aweight);
             if (jpt_1>=120 and jpt_1<200) h_j1pt120to200->Fill(m_sv,aweight);
             if (jpt_1>=200 and jpt_1<350) h_j1pt200to350->Fill(m_sv,aweight);
             if (jpt_1>=350) h_j1ptgt350->Fill(m_sv,aweight);

           }


    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    h_pt0to45->Write();
    h_pt45to80->Write();
    h_pt80to120->Write();
    h_pt120to200->Write();
    h_pt200to350->Write();
    h_pt350to450->Write();
    h_ptgt450->Write();

    h_njets0->Write();
    h_njets1->Write();
    h_njets2->Write();
    h_njets3->Write();
    h_njets4->Write();
   
    h_j1pt30to60->Write();
    h_j1pt60to120->Write();
    h_j1pt120to200->Write();
    h_j1pt200to350->Write();
    h_j1ptgt350->Write();

    fout->Close();
    delete wmc;
    delete w;
} 


