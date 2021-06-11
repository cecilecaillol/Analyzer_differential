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
    else if (sample=="ggH_htt125") {xs=48.30*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="ggH") {xs=48.30*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="qqH_htt125") {xs=3.770*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="qqH") {xs=3.770*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH125") {xs=0.8331*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH125") {xs=0.5272*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.7544*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="ttHTT") {xs=0.5033*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="ttHTT125") {xs=0.5033*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="GGZH125") {xs=0.1223*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHLLTT125") {xs=0.1223*0.06208*3*0.033658; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHNNTT125") {xs=0.1223*0.06208*0.2000; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHQQTT125") {xs=0.1223*0.06208*0.6991; weight=luminosity*xs/ngen;}
    else if (sample=="GGHWW") {xs=48.30*0.2203*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="VBFHWW") {xs=3.770*0.2203*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="WplusHWW") {xs=0.8331*0.2203; weight=luminosity*xs/ngen;}
    else if (sample=="WminusHWW") {xs=0.5272*0.2203; weight=luminosity*xs/ngen;}
    else if (sample=="ZHWW") {xs=0.7544*0.2203; weight=luminosity*xs/ngen;}
    else if (sample=="GGZHWW") {xs=0.1223*0.2203; weight=luminosity*xs/ngen;}
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

   bool is_higgs=((sample.find("ggH") < 140) or (sample.find("qqH") < 140) or (sample.find("ttH") < 140) or (sample.find("ZH") < 140) or (sample.find("WminusH") < 140) or (sample.find("WplusH") < 140) or (sample.find("ZH") < 140) or (name.find("OutsideAcceptance") < 140));
   int nbhist=1;
   if (sample=="data_obs") nbhist=1+88;
   else if (is_higgs) nbhist=1+82+18+8; 
   else if (name=="embedded") nbhist=1+32+88;
   else nbhist=1+82+88;

   std::vector<TH2F*> h0tau_OS;
   std::vector<TH2F*> h1tau_OS;
   std::vector<TH2F*> h2tau_OS;
   std::vector<TH2F*> h0ell_OS;
   std::vector<TH2F*> h1ell_OS;
   std::vector<TH2F*> h2ell_OS;
   std::vector<TH2F*> h0jet_OS;
   std::vector<TH2F*> h1jet_OS;
   std::vector<TH2F*> h2jet_OS;

   std::vector<TH2F*> h0tau_AI;
   std::vector<TH2F*> h1tau_AI;
   std::vector<TH2F*> h2tau_AI;
   std::vector<TH2F*> h0ell_AI;
   std::vector<TH2F*> h1ell_AI;
   std::vector<TH2F*> h2ell_AI;
   std::vector<TH2F*> h0jet_AI;
   std::vector<TH2F*> h1jet_AI;
   std::vector<TH2F*> h2jet_AI;

   std::vector<TH2F*> h3tau_OS;
   std::vector<TH2F*> h4tau_OS;
   std::vector<TH2F*> h5tau_OS;
   std::vector<TH2F*> h6tau_OS;
   std::vector<TH2F*> h7tau_OS;
   std::vector<TH2F*> h8tau_OS;
   std::vector<TH2F*> h3ell_OS;
   std::vector<TH2F*> h4ell_OS;
   std::vector<TH2F*> h5ell_OS;
   std::vector<TH2F*> h6ell_OS;
   std::vector<TH2F*> h7ell_OS;
   std::vector<TH2F*> h8ell_OS;
   std::vector<TH2F*> h3jet_OS;
   std::vector<TH2F*> h4jet_OS;
   std::vector<TH2F*> h5jet_OS;
   std::vector<TH2F*> h6jet_OS;
   std::vector<TH2F*> h7jet_OS;
   std::vector<TH2F*> h8jet_OS;
   std::vector<TH2F*> h3tau_AI;
   std::vector<TH2F*> h4tau_AI;
   std::vector<TH2F*> h5tau_AI;
   std::vector<TH2F*> h6tau_AI;
   std::vector<TH2F*> h7tau_AI;
   std::vector<TH2F*> h8tau_AI;
   std::vector<TH2F*> h3ell_AI;
   std::vector<TH2F*> h4ell_AI;
   std::vector<TH2F*> h5ell_AI;
   std::vector<TH2F*> h6ell_AI;
   std::vector<TH2F*> h7ell_AI;
   std::vector<TH2F*> h8ell_AI;
   std::vector<TH2F*> h3jet_AI;
   std::vector<TH2F*> h4jet_AI;
   std::vector<TH2F*> h5jet_AI;
   std::vector<TH2F*> h6jet_AI;
   std::vector<TH2F*> h7jet_AI;
   std::vector<TH2F*> h8jet_AI;

   // differential
   float bins_mtt0[] = {50,70,90,110,130,150,170,210,250,290}; //0 jet
   float bins_mtt1[] = {50,70,90,110,130,150,170,210,250,290}; // 1 jet
   float bins_mtt2[] = {50,70,90,110,130,150,170,210,250,290}; // 2 jets low mjj
   float bins_mtt3[] = {50,70,90,110,130,150,170,210,250,290}; // 2 jets high mjj
   float bins_mtt4[] = {50,70,90,110,130,150,170,210,250,290}; // 3 jets low mjj
   float bins_mtt5[] = {50,70,90,110,130,150,170,210,250,290}; // 3 jets high mjj
   float bins_mtt6[] = {50,70,90,110,130,150,170,210,250,290}; // ge 2jets
   float bins_mtt7[] = {50,70,90,110,130,150,170,210,250,290}; // rien 
   float bins_mtt8[] = {50,70,90,110,130,150,170,210,250,290}; // rien

   // control 1
   /*float bins_mtt0[] = {24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
   float bins_mtt1[] = {30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80};
   float bins_mtt2[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
   float bins_mtt3[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250};
   float bins_mtt4[] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200};
   float bins_mtt5[] = {60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250};
   float bins_mtt6[] = {0,1,2,3,4,5,6,7,8};
   float bins_mtt7[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
   float bins_mtt8[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};*/

   // control 2
   /*float bins_mtt0[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140};
   float bins_mtt1[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500};
   float bins_mtt2[] = {0,0.005,0.01,0.015,0.02,0.025,0.03,0.035,0.04,0.045,0.05,0.055,0.06,0.065,0.07,0.075,0.08,0.085,0.09,0.095,0.10};
   float bins_mtt3[] = {30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150};
   float bins_mtt4[] = {-4.7,-4.5,-4.3,-4.1,-3.9,-3.7,-3.5,-3.3,-3.1,-2.9,-2.7,-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9,3.1,3.3,3.5,3.7,3.9,4.1,4.3,4.5,4.7};
   float bins_mtt5[] = {30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120};
   float bins_mtt6[] = {-4.7,-4.5,-4.3,-4.1,-3.9,-3.7,-3.5,-3.3,-3.1,-2.9,-2.7,-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9,3.1,3.3,3.5,3.7,3.9,4.1,4.3,4.5,4.7};
   float bins_mtt7[] = {0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4,4.6,4.8,5.0,5.2,5.4,5.6,5.8,6.0,6.2,6.4,6.6,6.8,7.0};
   float bins_mtt8[] = {0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4,4.6,4.8,5.0,5.2,5.4,5.6,5.8,6.0,6.2,6.4,6.6,6.8,7.0};*/

   float bins_pthreso[] = {0,10,20,30,40,50,60,70,80,90,100,120,140,160,180,200,250,300,350,500,650};
   int  binnum_pthreso = sizeof(bins_pthreso)/sizeof(Float_t) - 1;

   int  binnum_mtt0 = sizeof(bins_mtt0)/sizeof(Float_t) - 1;
   int  binnum_mtt1 = sizeof(bins_mtt1)/sizeof(Float_t) - 1;
   int  binnum_mtt2 = sizeof(bins_mtt2)/sizeof(Float_t) - 1;
   int  binnum_mtt3 = sizeof(bins_mtt3)/sizeof(Float_t) - 1;
   int  binnum_mtt4 = sizeof(bins_mtt4)/sizeof(Float_t) - 1;
   int  binnum_mtt5 = sizeof(bins_mtt5)/sizeof(Float_t) - 1;
   int  binnum_mtt6 = sizeof(bins_mtt6)/sizeof(Float_t) - 1;
   int  binnum_mtt7 = sizeof(bins_mtt7)/sizeof(Float_t) - 1;
   int  binnum_mtt8 = sizeof(bins_mtt8)/sizeof(Float_t) - 1;

   float bins_mtt[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250};
   int  binnum_mtt = sizeof(bins_mtt)/sizeof(Float_t) - 1;

   /*float bins_mjj[] = {350,700,1000,1500,9000};
   float bins_mjj_low[] = {350,700,1000,1500,1800,9000}; // VBF ptH < 200
   float bins_mjj_high[] = {350,700,1200,9000}; // VBF ptH > 200
   float bins_pth[] = {0,60,120,200,250,9000};
   float bins_pth_1[] = {0,60,120,200,250,9000}; // Boosted 1
   float bins_pth_2[] = {0,60,120,200,250,9000}; // Boosted 2
   float bins_taupt[] = {30,40,50,9000};
   float bins_taupt_low[] = {30,40,50,9000}; // 0 jet ptH < 10
   float bins_taupt_high[] = {30,40,50,9000}; // 0 jet ptH > 10*/

   // differential
   float bins_mjj[] = {0,45,80,120,200,350,450,10000}; // 1 jet
   float bins_mjj_low[] = {0,30,60,120,200,350,100000}; // >2jets mjj
   float bins_mjj_high[] = {0,30,60,120,200,350,100000}; // rien
   float bins_pth[] = {0,45,80,120,200,350,10000}; // 0jet high
   float bins_pth_1[] = {0,1,2,3,4,10}; // 3 jets
   float bins_pth_2[] = {0,30,60,120,200,350,100000}; // 4 jets
   float bins_taupt[] = {0,45,80,120,200,350,10000}; // 0 jet low
   float bins_taupt_low[] = {0,1,2,3,4,10}; // 2 jets low
   float bins_taupt_high[] = {0,1,2,3,4,10}; // 2 jets high

   /*float bins_mjj[] = {0,100000};
   float bins_mjj_low[] = {0,100000};
   float bins_mjj_high[] = {0,100000};
   float bins_pth[] = {0,100000};
   float bins_pth_1[] = {0,100000};
   float bins_pth_2[] = {0,100000};
   float bins_taupt[] = {0,100000};
   float bins_taupt_low[] = {0,100000};
   float bins_taupt_high[] = {0,100000};*/

   int  binnum_mjj = sizeof(bins_mjj)/sizeof(Float_t) - 1;
   int  binnum_mjj_low = sizeof(bins_mjj_low)/sizeof(Float_t) - 1;
   int  binnum_mjj_high = sizeof(bins_mjj_high)/sizeof(Float_t) - 1;
   int  binnum_pth = sizeof(bins_pth)/sizeof(Float_t) - 1;
   int  binnum_pth_1 = sizeof(bins_pth_1)/sizeof(Float_t) - 1;
   int  binnum_pth_2 = sizeof(bins_pth_2)/sizeof(Float_t) - 1;
   int  binnum_taupt = sizeof(bins_taupt)/sizeof(Float_t) - 1;
   int  binnum_taupt_low = sizeof(bins_taupt_low)/sizeof(Float_t) - 1;
   int  binnum_taupt_high = sizeof(bins_taupt_high)/sizeof(Float_t) - 1;


   /*float bins_mtt3[] = {0,5,10,15,20,25,30,35,40,45,50,60,70,80,90,100,120,140,160,180,200};
   int  binnum_mtt3 = sizeof(bins_mtt3)/sizeof(Float_t) - 1;
   float bins_mtt4[] = {0,5,10,15,20,25,30,35,40,45,50,60,70,80,90,100,120,140,160,180,200};
   int  binnum_mtt4 = sizeof(bins_mtt4)/sizeof(Float_t) - 1;
   float bins_mtt5[] = {-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
   int  binnum_mtt5 = sizeof(bins_mtt5)/sizeof(Float_t) - 1;
   float bins_mtt6[] = {-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
   int  binnum_mtt6 = sizeof(bins_mtt6)/sizeof(Float_t) - 1;*/

   /*float bins_mtt3[] = {0,5,10,15,20,25,30,35,40,45,50,60,70,80,90,100,120,140,160,180,200,250};
   int  binnum_mtt3 = sizeof(bins_mtt3)/sizeof(Float_t) - 1;
   //float bins_mtt4[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins_mtt4[] = {-4.0,-3.8,-3.6,-3.4,-3.2,-3.0,-2.8,-2.6,-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0};
   int  binnum_mtt4 = sizeof(bins_mtt4)/sizeof(Float_t) - 1;
   //float bins_mtt5[] = {-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
   float bins_mtt5[] = {-200,-180,-160,-140,-120,-100,-80,-60,-40,-20,0,20,40,60,80};
   int  binnum_mtt5 = sizeof(bins_mtt5)/sizeof(Float_t) - 1;
   //float bins_mtt6[] = {-2.4,-2.2,-2.0,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
   float bins_mtt6[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   int  binnum_mtt6 = sizeof(bins_mtt6)/sizeof(Float_t) - 1;*/


   TH1F* f0real=new TH1F ("f0real","f0real",binnum_mtt0,bins_mtt0); f0real->Sumw2();
   TH1F* f0jet=new TH1F ("f0jet","f0jet",binnum_mtt0,bins_mtt0); f0jet->Sumw2();
   TH1F* f1real=new TH1F ("f1real","f1real",binnum_mtt1,bins_mtt1); f1real->Sumw2();
   TH1F* f1jet=new TH1F ("f1jet","f1jet",binnum_mtt1,bins_mtt1); f1jet->Sumw2();
   TH1F* f2real=new TH1F ("f2real","f2real",binnum_mtt2,bins_mtt2); f2real->Sumw2();
   TH1F* f2jet=new TH1F ("f2jet","f2jet",binnum_mtt2,bins_mtt2); f2jet->Sumw2();
   TH1F* f3real=new TH1F ("f3real","f3real",binnum_mtt3,bins_mtt3); f3real->Sumw2();
   TH1F* f3jet=new TH1F ("f3jet","f3jet",binnum_mtt3,bins_mtt3); f3jet->Sumw2();
   TH1F* f4real=new TH1F ("f4real","f4real",binnum_mtt4,bins_mtt4); f4real->Sumw2();
   TH1F* f4jet=new TH1F ("f4jet","f4jet",binnum_mtt4,bins_mtt4); f4jet->Sumw2();

   TH2F* h0_ttcontamination=new TH2F ("h0_ttcontamination","InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0); h0_ttcontamination->Sumw2();
   TH2F* h1_ttcontamination=new TH2F ("h1_ttcontamination","InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1); h1_ttcontamination->Sumw2();
   TH2F* h2_ttcontamination=new TH2F ("h2_ttcontamination","InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2); h2_ttcontamination->Sumw2();
   TH2F* h3_ttcontamination=new TH2F ("h3_ttcontamination","InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3); h3_ttcontamination->Sumw2();
   TH2F* h4_ttcontamination=new TH2F ("h4_ttcontamination","InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4); h4_ttcontamination->Sumw2();
   TH2F* h5_ttcontamination=new TH2F ("h5_ttcontamination","InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5); h5_ttcontamination->Sumw2();
   TH2F* h6_ttcontamination=new TH2F ("h6_ttcontamination","InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6); h6_ttcontamination->Sumw2();
   TH2F* h7_ttcontamination=new TH2F ("h7_ttcontamination","InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7); h7_ttcontamination->Sumw2();
   TH2F* h8_ttcontamination=new TH2F ("h8_ttcontamination","InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8); h8_ttcontamination->Sumw2();

   for (int k=0; k<nbhist; ++k){
        ostringstream HNS0tauOS; HNS0tauOS << "h0tau_OS" << k;
        ostringstream HNS1tauOS; HNS1tauOS << "h1tau_OS" << k;
        ostringstream HNS2tauOS; HNS2tauOS << "h2tau_OS" << k;
        h0tau_OS.push_back(new TH2F (HNS0tauOS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_OS[k]->Sumw2();
        h1tau_OS.push_back(new TH2F (HNS1tauOS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_OS[k]->Sumw2();
        h2tau_OS.push_back(new TH2F (HNS2tauOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_OS[k]->Sumw2();
        ostringstream HNS0jetOS; HNS0jetOS << "h0jet_OS" << k;
        ostringstream HNS1jetOS; HNS1jetOS << "h1jet_OS" << k;
        ostringstream HNS2jetOS; HNS2jetOS << "h2jet_OS" << k;
        h0jet_OS.push_back(new TH2F (HNS0jetOS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0jet_OS[k]->Sumw2();
        h1jet_OS.push_back(new TH2F (HNS1jetOS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1jet_OS[k]->Sumw2();
        h2jet_OS.push_back(new TH2F (HNS2jetOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2jet_OS[k]->Sumw2();
        ostringstream HNS0ellOS; HNS0ellOS << "h0ell_OS" << k;
        ostringstream HNS1ellOS; HNS1ellOS << "h1ell_OS" << k;
        ostringstream HNS2ellOS; HNS2ellOS << "h2ell_OS" << k;
        h0ell_OS.push_back(new TH2F (HNS0ellOS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0ell_OS[k]->Sumw2();
        h1ell_OS.push_back(new TH2F (HNS1ellOS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1ell_OS[k]->Sumw2();
        h2ell_OS.push_back(new TH2F (HNS2ellOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2ell_OS[k]->Sumw2();

        ostringstream HNS3tauOS; HNS3tauOS << "h3tau_OS" << k;
        ostringstream HNS4tauOS; HNS4tauOS << "h4tau_OS" << k;
        ostringstream HNS5tauOS; HNS5tauOS << "h5tau_OS" << k;
        ostringstream HNS6tauOS; HNS6tauOS << "h6tau_OS" << k;
        ostringstream HNS7tauOS; HNS7tauOS << "h7tau_OS" << k;
        ostringstream HNS8tauOS; HNS8tauOS << "h8tau_OS" << k;
        h3tau_OS.push_back(new TH2F (HNS3tauOS.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3tau_OS[k]->Sumw2();
        h4tau_OS.push_back(new TH2F (HNS4tauOS.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4tau_OS[k]->Sumw2();
        h5tau_OS.push_back(new TH2F (HNS5tauOS.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5tau_OS[k]->Sumw2();
        h6tau_OS.push_back(new TH2F (HNS6tauOS.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6tau_OS[k]->Sumw2();
        h7tau_OS.push_back(new TH2F (HNS7tauOS.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7tau_OS[k]->Sumw2();
        h8tau_OS.push_back(new TH2F (HNS8tauOS.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8tau_OS[k]->Sumw2();
        ostringstream HNS3jetOS; HNS3jetOS << "h3jet_OS" << k;
        ostringstream HNS4jetOS; HNS4jetOS << "h4jet_OS" << k;
        ostringstream HNS5jetOS; HNS5jetOS << "h5jet_OS" << k;
        ostringstream HNS6jetOS; HNS6jetOS << "h6jet_OS" << k;
        ostringstream HNS7jetOS; HNS7jetOS << "h7jet_OS" << k;
        ostringstream HNS8jetOS; HNS8jetOS << "h8jet_OS" << k;
        h3jet_OS.push_back(new TH2F (HNS3jetOS.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3jet_OS[k]->Sumw2();
        h4jet_OS.push_back(new TH2F (HNS4jetOS.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4jet_OS[k]->Sumw2();
        h5jet_OS.push_back(new TH2F (HNS5jetOS.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5jet_OS[k]->Sumw2();
        h6jet_OS.push_back(new TH2F (HNS6jetOS.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6jet_OS[k]->Sumw2();
        h7jet_OS.push_back(new TH2F (HNS7jetOS.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7jet_OS[k]->Sumw2();
        h8jet_OS.push_back(new TH2F (HNS8jetOS.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8jet_OS[k]->Sumw2();
        ostringstream HNS3ellOS; HNS3ellOS << "h3ell_OS" << k;
        ostringstream HNS4ellOS; HNS4ellOS << "h4ell_OS" << k;
        ostringstream HNS5ellOS; HNS5ellOS << "h5ell_OS" << k;
        ostringstream HNS6ellOS; HNS6ellOS << "h6ell_OS" << k;
        ostringstream HNS7ellOS; HNS7ellOS << "h7ell_OS" << k;
        ostringstream HNS8ellOS; HNS8ellOS << "h8ell_OS" << k;
        h3ell_OS.push_back(new TH2F (HNS3ellOS.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3ell_OS[k]->Sumw2();
        h4ell_OS.push_back(new TH2F (HNS4ellOS.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4ell_OS[k]->Sumw2();
        h5ell_OS.push_back(new TH2F (HNS5ellOS.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5ell_OS[k]->Sumw2();
        h6ell_OS.push_back(new TH2F (HNS6ellOS.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6ell_OS[k]->Sumw2();
        h7ell_OS.push_back(new TH2F (HNS7ellOS.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7ell_OS[k]->Sumw2();
        h8ell_OS.push_back(new TH2F (HNS8ellOS.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8ell_OS[k]->Sumw2();

        ostringstream HNS0tauAI; HNS0tauAI << "h0tau_AI" << k;
        ostringstream HNS1tauAI; HNS1tauAI << "h1tau_AI" << k;
        ostringstream HNS2tauAI; HNS2tauAI << "h2tau_AI" << k;
        h0tau_AI.push_back(new TH2F (HNS0tauAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_AI[k]->Sumw2();
        h1tau_AI.push_back(new TH2F (HNS1tauAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_AI[k]->Sumw2();
        h2tau_AI.push_back(new TH2F (HNS2tauAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_AI[k]->Sumw2();
        ostringstream HNS0jetAI; HNS0jetAI << "h0jet_AI" << k;
        ostringstream HNS1jetAI; HNS1jetAI << "h1jet_AI" << k;
        ostringstream HNS2jetAI; HNS2jetAI << "h2jet_AI" << k;
        h0jet_AI.push_back(new TH2F (HNS0jetAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0jet_AI[k]->Sumw2();
        h1jet_AI.push_back(new TH2F (HNS1jetAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1jet_AI[k]->Sumw2();
        h2jet_AI.push_back(new TH2F (HNS2jetAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2jet_AI[k]->Sumw2();
        ostringstream HNS0ellAI; HNS0ellAI << "h0ell_AI" << k;
        ostringstream HNS1ellAI; HNS1ellAI << "h1ell_AI" << k;
        ostringstream HNS2ellAI; HNS2ellAI << "h2ell_AI" << k;
        h0ell_AI.push_back(new TH2F (HNS0ellAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0ell_AI[k]->Sumw2();
        h1ell_AI.push_back(new TH2F (HNS1ellAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1ell_AI[k]->Sumw2();
        h2ell_AI.push_back(new TH2F (HNS2ellAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2ell_AI[k]->Sumw2();

        ostringstream HNS3tauAI; HNS3tauAI << "h3tau_AI" << k;
        ostringstream HNS4tauAI; HNS4tauAI << "h4tau_AI" << k;
        ostringstream HNS5tauAI; HNS5tauAI << "h5tau_AI" << k;
        ostringstream HNS6tauAI; HNS6tauAI << "h6tau_AI" << k;
        ostringstream HNS7tauAI; HNS7tauAI << "h7tau_AI" << k;
        ostringstream HNS8tauAI; HNS8tauAI << "h8tau_AI" << k;
        h3tau_AI.push_back(new TH2F (HNS3tauAI.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3tau_AI[k]->Sumw2();
        h4tau_AI.push_back(new TH2F (HNS4tauAI.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4tau_AI[k]->Sumw2();
        h5tau_AI.push_back(new TH2F (HNS5tauAI.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5tau_AI[k]->Sumw2();
        h6tau_AI.push_back(new TH2F (HNS6tauAI.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6tau_AI[k]->Sumw2();
        h7tau_AI.push_back(new TH2F (HNS7tauAI.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7tau_AI[k]->Sumw2();
        h8tau_AI.push_back(new TH2F (HNS8tauAI.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8tau_AI[k]->Sumw2();
        ostringstream HNS3jetAI; HNS3jetAI << "h3jet_AI" << k;
        ostringstream HNS4jetAI; HNS4jetAI << "h4jet_AI" << k;
        ostringstream HNS5jetAI; HNS5jetAI << "h5jet_AI" << k;
        ostringstream HNS6jetAI; HNS6jetAI << "h6jet_AI" << k;
        ostringstream HNS7jetAI; HNS7jetAI << "h7jet_AI" << k;
        ostringstream HNS8jetAI; HNS8jetAI << "h8jet_AI" << k;
        h3jet_AI.push_back(new TH2F (HNS3jetAI.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3jet_AI[k]->Sumw2();
        h4jet_AI.push_back(new TH2F (HNS4jetAI.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4jet_AI[k]->Sumw2();
        h5jet_AI.push_back(new TH2F (HNS5jetAI.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5jet_AI[k]->Sumw2();
        h6jet_AI.push_back(new TH2F (HNS6jetAI.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6jet_AI[k]->Sumw2();
        h7jet_AI.push_back(new TH2F (HNS7jetAI.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7jet_AI[k]->Sumw2();
        h8jet_AI.push_back(new TH2F (HNS8jetAI.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8jet_AI[k]->Sumw2();
        ostringstream HNS3ellAI; HNS3ellAI << "h3ell_AI" << k;
        ostringstream HNS4ellAI; HNS4ellAI << "h4ell_AI" << k;
        ostringstream HNS5ellAI; HNS5ellAI << "h5ell_AI" << k;
        ostringstream HNS6ellAI; HNS6ellAI << "h6ell_AI" << k;
        ostringstream HNS7ellAI; HNS7ellAI << "h7ell_AI" << k;
        ostringstream HNS8ellAI; HNS8ellAI << "h8ell_AI" << k;
        h3ell_AI.push_back(new TH2F (HNS3ellAI.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3ell_AI[k]->Sumw2();
        h4ell_AI.push_back(new TH2F (HNS4ellAI.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4ell_AI[k]->Sumw2();
        h5ell_AI.push_back(new TH2F (HNS5ellAI.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5ell_AI[k]->Sumw2();
        h6ell_AI.push_back(new TH2F (HNS6ellAI.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6ell_AI[k]->Sumw2();
        h7ell_AI.push_back(new TH2F (HNS7ellAI.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7ell_AI[k]->Sumw2();
        h8ell_AI.push_back(new TH2F (HNS8ellAI.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8ell_AI[k]->Sumw2();
     }

   reweight::LumiReWeighting* LumiWeights_12;
   LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2018.root", "pu_distributions_data_2018.root", "pileup", "pileup");

   TFile f_pthcorrection("pthcorrection_et.root");
   TF1 *fit_pthcorrection=(TF1*) f_pthcorrection.Get("pth_correction");

   TFile *ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco.root");
   TF1 *fct_tauid= (TF1*) ftauid->Get("Medium_cent");
   TF1 *fct_tauid_up= (TF1*) ftauid->Get("Medium_up");
   TF1 *fct_tauid_down= (TF1*) ftauid->Get("Medium_down");

   TFile *ftauid_emb = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2018ReReco_EMB.root");
   TF1 *fct_tauid_emb= (TF1*) ftauid_emb->Get("Medium_cent");
   TF1 *fct_tauid_emb_up= (TF1*) ftauid_emb->Get("Medium_up");
   TF1 *fct_tauid_emb_down= (TF1*) ftauid_emb->Get("Medium_down");

   float tes_dm0_do=0.991;
   float tes_dm1_do=0.994;
   float tes_dm10_do=0.993;
   float tes_dm11_do=0.988;
   float tes_dm0_up=1.009;
   float tes_dm1_up=1.006;
   float tes_dm10_up=1.007;
   float tes_dm11_up=1.012;
   /*if (year==2016){
    tes_dm0_do=0.992;
    tes_dm1_do=0.994;
    tes_dm10_do=0.992;
    tes_dm11_do=0.989;
    tes_dm0_up=1.008;
    tes_dm1_up=1.006;
    tes_dm10_up=1.008;
    tes_dm11_up=1.011;
   }
   if (year==2017){
    tes_dm0_do=0.990;
    tes_dm1_do=0.994;
    tes_dm10_do=0.993;
    tes_dm11_do=0.986;
    tes_dm0_up=1.010;
    tes_dm1_up=1.006;
    tes_dm10_up=1.007;
    tes_dm11_up=1.014;
   }*/

   TFile *ffrac=new TFile("files_diff_et/fractions.root");
   TH1F* frac_w_pth0to45=(TH1F*) ffrac->Get("frac_w_pth0to45");
   TH1F* frac_tt_pth0to45=(TH1F*) ffrac->Get("frac_tt_pth0to45");
   TH1F* frac_qcd_pth0to45=(TH1F*) ffrac->Get("frac_qcd_pth0to45");
   TH1F* frac_data_pth0to45=(TH1F*) ffrac->Get("frac_data_pth0to45");
   TH1F* frac_w_pth45to80=(TH1F*) ffrac->Get("frac_w_pth45to80");
   TH1F* frac_tt_pth45to80=(TH1F*) ffrac->Get("frac_tt_pth45to80");
   TH1F* frac_qcd_pth45to80=(TH1F*) ffrac->Get("frac_qcd_pth45to80");
   TH1F* frac_data_pth45to80=(TH1F*) ffrac->Get("frac_data_pth45to80");
   TH1F* frac_w_pth80to120=(TH1F*) ffrac->Get("frac_w_pth80to120");
   TH1F* frac_tt_pth80to120=(TH1F*) ffrac->Get("frac_tt_pth80to120");
   TH1F* frac_qcd_pth80to120=(TH1F*) ffrac->Get("frac_qcd_pth80to120");
   TH1F* frac_data_pth80to120=(TH1F*) ffrac->Get("frac_data_pth80to120");
   TH1F* frac_w_pth120to200=(TH1F*) ffrac->Get("frac_w_pth120to200");
   TH1F* frac_tt_pth120to200=(TH1F*) ffrac->Get("frac_tt_pth120to200");
   TH1F* frac_qcd_pth120to200=(TH1F*) ffrac->Get("frac_qcd_pth120to200");
   TH1F* frac_data_pth120to200=(TH1F*) ffrac->Get("frac_data_pth120to200");
   TH1F* frac_w_pthgt200=(TH1F*) ffrac->Get("frac_w_pthgt200");
   TH1F* frac_tt_pthgt200=(TH1F*) ffrac->Get("frac_tt_pthgt200");
   TH1F* frac_qcd_pthgt200=(TH1F*) ffrac->Get("frac_qcd_pthgt200");
   TH1F* frac_data_pthgt200=(TH1F*) ffrac->Get("frac_data_pthgt200");

   TFile fw("htt_scalefactors_legacy_2018.root");
   RooWorkspace *w = (RooWorkspace*)fw.Get("w");
   fw.Close();

   TFile fwmc("htt_scalefactors_legacy_2018.root");
   RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
   fwmc.Close();

   TString postfixMC[83]={"","_CMS_scale_t_1prong_2018Down","_CMS_scale_t_1prong_2018Up","_CMS_scale_t_1prong1pizero_2018Down","_CMS_scale_t_1prong1pizero_2018Up","_CMS_scale_t_3prong_2018Down","_CMS_scale_t_3prong_2018Up","_CMS_scale_t_3prong1pizero_2018Down","_CMS_scale_t_3prong1pizero_2018Up","_CMS_tauideff_pt30to35_2018Down","_CMS_tauideff_pt30to35_2018Up","_CMS_tauideff_pt35to40_2018Down","_CMS_tauideff_pt35to40_2018Up","_CMS_tauideff_ptgt40_2018Down","_CMS_tauideff_ptgt40_2018Up","_CMS_scale_j_AbsoluteDown","_CMS_scale_j_AbsoluteUp","_CMS_scale_j_Absolute_2018Down","_CMS_scale_j_Absolute_2018Up","_CMS_scale_j_BBEC1Down","_CMS_scale_j_BBEC1Up","_CMS_scale_j_BBEC1_2018Down","_CMS_scale_j_BBEC1_2018Up","_CMS_scale_j_EC2Down","_CMS_scale_j_EC2Up","_CMS_scale_j_EC2_2018Down","_CMS_scale_j_EC2_2018Up","_CMS_scale_j_FlavorQCDDown","_CMS_scale_j_FlavorQCDUp","_CMS_scale_j_HFDown","_CMS_scale_j_HFUp","_CMS_scale_j_HF_2018Down","_CMS_scale_j_HF_2018Up","_CMS_scale_j_RelativeBalDown","_CMS_scale_j_RelativeBalUp","_CMS_scale_j_RelativeSample_2018Down","_CMS_scale_j_RelativeSample_2018Up","_CMS_res_j_2018Down","_CMS_res_j_2018Up","_CMS_scale_efaket_1prong_barrel_2018Down","_CMS_scale_efaket_1prong_barrel_2018Up","_CMS_scale_efaket_1prong1pizero_barrel_2018Down","_CMS_scale_efaket_1prong1pizero_barrel_2018Up","_CMS_scale_efaket_1prong_endcap_2018Down","_CMS_scale_efaket_1prong_endcap_2018Up","_CMS_scale_efaket_1prong1pizero_endcap_2018Down","_CMS_scale_efaket_1prong1pizero_endcap_2018Up","_CMS_scale_met_unclustered_2018Down","_CMS_scale_met_unclustered_2018Up","_CMS_htt_boson_reso_met_0jet_2018Down","_CMS_htt_boson_reso_met_0jet_2018Up","_CMS_htt_boson_scale_met_0jet_2018Down","_CMS_htt_boson_scale_met_0jet_2018Up","_CMS_htt_boson_reso_met_1jet_2018Down","_CMS_htt_boson_reso_met_1jet_2018Up","_CMS_htt_boson_scale_met_1jet_2018Down","_CMS_htt_boson_scale_met_1jet_2018Up","_CMS_htt_boson_reso_met_2jet_2018Down","_CMS_htt_boson_reso_met_2jet_2018Up","_CMS_htt_boson_scale_met_2jet_2018Down","_CMS_htt_boson_scale_met_2jet_2018Up","_CMS_htt_ttbarShapeDown","_CMS_htt_ttbarShapeUp","_CMS_htt_dyShapeDown","_CMS_htt_dyShapeUp","_CMS_scale_e_2018Down","_CMS_scale_e_2018Up","_CMS_singleeletrg_2018Down","_CMS_singleeletrg_2018Up","_CMS_eletautrg_2018Down","_CMS_eletautrg_2018Up","_CMS_efaket_norm_pt30to50_2018Down","_CMS_efaket_norm_pt30to50_2018Up","_CMS_efaket_norm_pt50to70_2018Down","_CMS_efaket_norm_pt50to70_2018Up","_CMS_efaket_norm_ptgt70_2018Down","_CMS_efaket_norm_ptgt70_2018Up","_CMS_etauFR_barrel_2018Down","_CMS_etauFR_barrel_2018Up","_CMS_etauFR_endcap_2018Down","_CMS_etauFR_endcap_2018Up","_CMS_looser_lep_wp_etau_2018Down","_CMS_looser_lep_wp_etau_2018Up"};


   TString postfixTheo[27]={"","_QCDscale_qqHUp","_QCDscale_qqHDown","_QCDscale_VHUp","_QCDscale_VHDown","_QCDscale_ggZHUp","_QCDscale_ggZHDown","_QCDscale_ttHUp","_QCDscale_ttHDown","_THU_ggH_MuUp","_THU_ggH_MuDown","_THU_ggH_ResUp","_THU_ggH_ResDown","_THU_ggH_Mig01Up","_THU_ggH_Mig01Down","_THU_ggH_Mig12Up","_THU_ggH_Mig12Down","_THU_ggH_VBF2jUp","_THU_ggH_VBF2jDown","_THU_ggH_VBF3jUp","_THU_ggH_VBF3jDown","_THU_ggH_PT60Up","_THU_ggH_PT60Down","_THU_ggH_PT120Up","_THU_ggH_PT120Down","_THU_ggH_qmtopUp","_THU_ggH_qmtopDown"};

   TString postfixEmbedded[33]={"","_CMS_scale_emb_t_1prong_2018Down","_CMS_scale_emb_t_1prong_2018Up","_CMS_scale_emb_t_1prong1pizero_2018Down","_CMS_scale_emb_t_1prong1pizero_2018Up","_CMS_scale_emb_t_3prong_2018Down","_CMS_scale_emb_t_3prong_2018Up","_CMS_scale_emb_t_3prong1pizero_2018Down","_CMS_scale_emb_t_3prong1pizero_2018Up","_CMS_scale_emb_e_barrel_2018Down","_CMS_scale_emb_e_barrel_2018Up","_CMS_scale_emb_e_endcap_2018Down","_CMS_scale_emb_e_endcap_2018Up","_CMS_singleeletrg_emb_2018Down","_CMS_singleeletrg_emb_2018Up","_CMS_eletautrg_emb_2018Down","_CMS_eletautrg_emb_2018Up","_CMS_eff_t_embedded_pt30to35_2018Down","_CMS_eff_t_embedded_pt30to35_2018Up","_CMS_eff_t_embedded_pt35to40_2018Down","_CMS_eff_t_embedded_pt35to40_2018Up","_CMS_eff_t_embedded_ptgt40_2018Down","_CMS_eff_t_embedded_ptgt40_2018Up","_CMS_eff_prong_emb_2018Down","_CMS_eff_prong_emb_2018Up","_CMS_eff_1prong1pizero_emb_2018Down","_CMS_eff_1prong1pizero_emb_2018Up","_CMS_eff_3prong1pizero_emb_2018Down","_CMS_eff_3prong1pizero_emb_2018Up","_CMS_EmbeddedZeroJet_2018Down","_CMS_EmbeddedZeroJet_2018Up","_CMS_looser_lep_wp_etau_2018Down","_CMS_looser_lep_wp_etau_2018Up"};


   TString FFsys[88]={"ff_qcd_up1_0Bjet","ff_qcd_up2_0Bjet","ff_qcd_down1_0Bjet","ff_qcd_down2_0Bjet","ff_qcd_up1_1Bjet","ff_qcd_up2_1Bjet","ff_qcd_down1_1Bjet","ff_qcd_down2_1Bjet","ff_qcd_up1_2Bjet","ff_qcd_up2_2Bjet","ff_qcd_down1_2Bjet","ff_qcd_down2_2Bjet","ff_w_up1_0Bjet","ff_w_up2_0Bjet","ff_w_down1_0Bjet","ff_w_down2_0Bjet","ff_w_up1_1Bjet","ff_w_up2_1Bjet","ff_w_down1_1Bjet","ff_w_down2_1Bjet","ff_w_up1_2Bjet","ff_w_up2_2Bjet","ff_w_down1_2Bjet","ff_w_down2_2Bjet","ff_qcd_up1_0Ejet","ff_qcd_up2_0Ejet","ff_qcd_down1_0Ejet","ff_qcd_down2_0Ejet","ff_qcd_up1_1Ejet","ff_qcd_up2_1Ejet","ff_qcd_down1_1Ejet","ff_qcd_down2_1Ejet","ff_qcd_up1_2Ejet","ff_qcd_up2_2Ejet","ff_qcd_down1_2Ejet","ff_qcd_down2_2Ejet","ff_w_up1_0Ejet","ff_w_up2_0Ejet","ff_w_down1_0Ejet","ff_w_down2_0Ejet","ff_w_up1_1Ejet","ff_w_up2_1Ejet","ff_w_down1_1Ejet","ff_w_down2_1Ejet","ff_w_up1_2Ejet","ff_w_up2_2Ejet","ff_w_down1_2Ejet","ff_w_down2_2Ejet","ff_tt_up1","ff_tt_up2","ff_tt_down1","ff_tt_down2","lptclosure_qcd_up","lptclosure_qcd_down","lptclosure_xtrg_qcd_up","lptclosure_xtrg_qcd_down","lptclosure_w_up","lptclosure_w_down","lptclosure_xtrg_w_up","lptclosure_xtrg_w_down","lptclosure_tt_up","lptclosure_tt_down","lptclosure_xtrg_tt_up","lptclosure_xtrg_tt_down","osssclosure_qcd_up","osssclosure_qcd_down","closure_pth_0jet_w_up","closure_pth_0jet_w_down","closure_ljpt_pth0to45_w_up","closure_ljpt_pth0to45_w_down","closure_ljpt_pth45to80_w_up","closure_ljpt_pth45to80_w_down","closure_ljpt_pth80to120_w_up","closure_ljpt_pth80to120_w_down","closure_ljpt_pth120to200_w_up","closure_ljpt_pth120to200_w_down","closure_ljpt_pthgt200_w_up","closure_ljpt_pthgt200_w_down","norm_0jet_up","norm_0jet_down","norm_1jet_up","norm_1jet_down","norm_2jet_up","norm_2jet_down","norm_3jet_up","norm_3jet_down","norm_4jet_up","norm_4jet_down"};
   TString postfixFF[89]={"","_CMS_rawFF_et_qcd_0jet_barrel_unc1_2018Up","_CMS_rawFF_et_qcd_0jet_barrel_unc2_2018Up","_CMS_rawFF_et_qcd_0jet_barrel_unc1_2018Down","_CMS_rawFF_et_qcd_0jet_barrel_unc2_2018Down","_CMS_rawFF_et_qcd_1jet_barrel_unc1_2018Up","_CMS_rawFF_et_qcd_1jet_barrel_unc2_2018Up","_CMS_rawFF_et_qcd_1jet_barrel_unc1_2018Down","_CMS_rawFF_et_qcd_1jet_barrel_unc2_2018Down","_CMS_rawFF_et_qcd_2jet_barrel_unc1_2018Up","_CMS_rawFF_et_qcd_2jet_barrel_unc2_2018Up","_CMS_rawFF_et_qcd_2jet_barrel_unc1_2018Down","_CMS_rawFF_et_qcd_2jet_barrel_unc2_2018Down","_CMS_rawFF_et_w_0jet_barrel_unc1_2018Up","_CMS_rawFF_et_w_0jet_barrel_unc2_2018Up","_CMS_rawFF_et_w_0jet_barrel_unc1_2018Down","_CMS_rawFF_et_w_0jet_barrel_unc2_2018Down","_CMS_rawFF_et_w_1jet_barrel_unc1_2018Up","_CMS_rawFF_et_w_1jet_barrel_unc2_2018Up","_CMS_rawFF_et_w_1jet_barrel_unc1_2018Down","_CMS_rawFF_et_w_1jet_barrel_unc2_2018Down","_CMS_rawFF_et_w_2jet_barrel_unc1_2018Up","_CMS_rawFF_et_w_2jet_barrel_unc2_2018Up","_CMS_rawFF_et_w_2jet_barrel_unc1_2018Down","_CMS_rawFF_et_w_2jet_barrel_unc2_2018Down","_CMS_rawFF_et_qcd_0jet_endcap_unc1_2018Up","_CMS_rawFF_et_qcd_0jet_endcap_unc2_2018Up","_CMS_rawFF_et_qcd_0jet_endcap_unc1_2018Down","_CMS_rawFF_et_qcd_0jet_endcap_unc2_2018Down","_CMS_rawFF_et_qcd_1jet_endcap_unc1_2018Up","_CMS_rawFF_et_qcd_1jet_endcap_unc2_2018Up","_CMS_rawFF_et_qcd_1jet_endcap_unc1_2018Down","_CMS_rawFF_et_qcd_1jet_endcap_unc2_2018Down","_CMS_rawFF_et_qcd_2jet_endcap_unc1_2018Up","_CMS_rawFF_et_qcd_2jet_endcap_unc2_2018Up","_CMS_rawFF_et_qcd_2jet_endcap_unc1_2018Down","_CMS_rawFF_et_qcd_2jet_endcap_unc2_2018Down","_CMS_rawFF_et_w_0jet_endcap_unc1_2018Up","_CMS_rawFF_et_w_0jet_endcap_unc2_2018Up","_CMS_rawFF_et_w_0jet_endcap_unc1_2018Down","_CMS_rawFF_et_w_0jet_endcap_unc2_2018Down","_CMS_rawFF_et_w_1jet_endcap_unc1_2018Up","_CMS_rawFF_et_w_1jet_endcap_unc2_2018Up","_CMS_rawFF_et_w_1jet_endcap_unc1_2018Down","_CMS_rawFF_et_w_1jet_endcap_unc2_2018Down","_CMS_rawFF_et_w_2jet_endcap_unc1_2018Up","_CMS_rawFF_et_w_2jet_endcap_unc2_2018Up","_CMS_rawFF_et_w_2jet_endcap_unc1_2018Down","_CMS_rawFF_et_w_2jet_endcap_unc2_2018Down","_CMS_rawFF_et_tt_unc1_2018Up","_CMS_rawFF_et_tt_unc2_2018Up","_CMS_rawFF_et_tt_unc1_2018Down","_CMS_rawFF_et_tt_unc2_2018Down","_CMS_FF_closure_lpt_et_qcd_2018Up","_CMS_FF_closure_lpt_et_qcd_2018Down","_CMS_FF_closure_lpt_xtrg_et_qcd_2018Up","_CMS_FF_closure_lpt_xtrg_et_qcd_2018Down","_CMS_FF_closure_lpt_et_w_2018Up","_CMS_FF_closure_lpt_et_w_2018Down","_CMS_FF_closure_lpt_xtrg_et_w_2018Up","_CMS_FF_closure_lpt_xtrg_et_w_2018Down","_CMS_FF_closure_lpt_et_tt_2018Up","_CMS_FF_closure_lpt_et_tt_2018Down","_CMS_FF_closure_lpt_xtrg_et_tt_2018Up","_CMS_FF_closure_lpt_xtrg_et_tt_2018Down","_CMS_FF_closure_OSSS_mvis_et_qcd_2018Up","_CMS_FF_closure_OSSS_mvis_et_qcd_2018Down","_CMS_FF_closure_pth_0jet_et_w_2018Up","_CMS_FF_closure_pth_0jet_et_w_2018Down","_CMS_FF_closure_ljpt_pth0to45_et_w_2018Up","_CMS_FF_closure_ljpt_pth0to45_et_w_2018Down","_CMS_FF_closure_ljpt_pth45to80_et_w_2018Up","_CMS_FF_closure_ljpt_pth45to80_et_w_2018Down","_CMS_FF_closure_ljpt_pth80to120_et_w_2018Up","_CMS_FF_closure_ljpt_pth80to120_et_w_2018Down","_CMS_FF_closure_ljpt_pth120to200_et_w_2018Up","_CMS_FF_closure_ljpt_pth120to200_et_w_2018Down","_CMS_FF_closure_ljpt_pthgt200_et_w_2018Up","_CMS_FF_closure_ljpt_pthgt200_et_w_2018Down","_CMS_FF_norm_et_0jet_2018Up","_CMS_FF_norm_et_0jet_2018Down","_CMS_FF_norm_et_1jet_2018Up","_CMS_FF_norm_et_1jet_2018Down","_CMS_FF_norm_et_2jet_2018Up","_CMS_FF_norm_et_2jet_2018Down","_CMS_FF_norm_et_3jet_2018Up","_CMS_FF_norm_et_3jet_2018Down","_CMS_FF_norm_et_4jet_2018Up","_CMS_FF_norm_et_4jet_2018Down"};

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
   float WG1unc_average[18]={1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};

   TFile *f_QCDScale = new TFile("/afs/cern.ch/work/c/ccaillol/public/theory_uncertainties_differential_finerBinning/ggH_htt125.root");
   if (sample=="qqH" or sample=="qqH_htt125") f_QCDScale = new TFile("/afs/cern.ch/work/c/ccaillol/public/theory_uncertainties_differential_finerBinning/qqH_htt125.root");
   if (sample=="WplusH" or sample=="WplusH125") f_QCDScale = new TFile("/afs/cern.ch/work/c/ccaillol/public/theory_uncertainties_differential_finerBinning/Wplus125.root");
   if (sample=="WminusH" or sample=="WminusH125") f_QCDScale = new TFile("/afs/cern.ch/work/c/ccaillol/public/theory_uncertainties_differential_finerBinning/WminusH125.root");
   if (sample=="ZH" or sample=="ZH125" or sample=="ZHTT" or sample=="ZHTT125") f_QCDScale = new TFile("/afs/cern.ch/work/c/ccaillol/public/theory_uncertainties_differential_finerBinning/ZH125.root");
   if (sample=="GGZHNNTT125") f_QCDScale = new TFile("/afs/cern.ch/work/c/ccaillol/public/theory_uncertainties_differential_finerBinning/GGZHNNTT125.root");
   if (sample=="GGZHLLTT125") f_QCDScale = new TFile("/afs/cern.ch/work/c/ccaillol/public/theory_uncertainties_differential_finerBinning/GGZHLLTT125.root");
   if (sample=="GGZHQQTT125") f_QCDScale = new TFile("/afs/cern.ch/work/c/ccaillol/public/theory_uncertainties_differential_finerBinning/GGZHQQTT125.root");
   if (sample=="ttHTT") f_QCDScale = new TFile("/afs/cern.ch/work/c/ccaillol/public/theory_uncertainties_differential_finerBinning/ttHTT125.root");
   TH1F *h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth0to45");
   if (name.find("H_PTH_0_45") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth0to45");
   if (name.find("H_PTH_0_10") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth0to10");
   if (name.find("H_PTH_10_20") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth10to20");
   if (name.find("H_PTH_20_30") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth20to30");
   if (name.find("H_PTH_30_45") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth30to45");
   if (name.find("H_PTH_45_60") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth45to60");
   if (name.find("H_PTH_60_80") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth60to80");
   if (name.find("H_PTH_0_20") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth0to45");
   if (name.find("H_PTH_20_45") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth0to45");
   if (name.find("H_PTH_45_80") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth45to80");
   if (name.find("H_PTH_80_120") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth80to120");
   if (name.find("H_PTH_120_200") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth120to200");
   if (name.find("H_PTH_200_350") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth200to350");
   if (name.find("H_PTH_350_450") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pth350to450");
   if (name.find("H_PTH_GT450") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pthgt450");
   if (name.find("H_PTH_GT650") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_pthgt450");
   if (name.find("H_NJ_0") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_njets0");
   if (name.find("H_NJ_1") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_njets1");
   if (name.find("H_NJ_2") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_njets2");
   if (name.find("H_NJ_3") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_njets3");
   if (name.find("H_NJ_GE4") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_njets4");
   if (name.find("H_J1PT_30_60") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_j1pt30to60");
   if (name.find("H_J1PT_60_120") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_j1pt60to120");
   if (name.find("H_J1PT_120_200") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_j1pt120to200");
   if (name.find("H_J1PT_200_350") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_j1pt200to350");
   if (name.find("H_J1PT_GT350") < 140) h_QCDScale = (TH1F*) f_QCDScale->Get("h_scale_j1ptgt350");

   TH1F *h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth0to45");
   if (name.find("H_PTH_0_20") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth0to45");
   if (name.find("H_PTH_20_45") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth0to45");
   if (name.find("H_PTH_0_45") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth0to45");
   if (name.find("H_PTH_0_10") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth0to10");
   if (name.find("H_PTH_10_20") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth10to20");
   if (name.find("H_PTH_20_30") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth20to30");
   if (name.find("H_PTH_30_45") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth30to45");
   if (name.find("H_PTH_45_60") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth45to60");
   if (name.find("H_PTH_60_80") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth60to80");
   if (name.find("H_PTH_45_80") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth45to80");
   if (name.find("H_PTH_80_120") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth80to120");
   if (name.find("H_PTH_120_200") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth120to200");
   if (name.find("H_PTH_200_350") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth200to350");
   if (name.find("H_PTH_350_450") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pth350to450");
   if (name.find("H_PTH_GT450") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pthgt450");
   if (name.find("H_PTH_GT650") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_pthgt450");
   if (name.find("H_NJ_0") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_njets0");
   if (name.find("H_NJ_1") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_njets1");
   if (name.find("H_NJ_2") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_njets2");
   if (name.find("H_NJ_3") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_njets3");
   if (name.find("H_NJ_GE4") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_njets4");
   if (name.find("H_J1PT_30_60") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_j1pt30to60");
   if (name.find("H_J1PT_60_120") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_j1pt60to120");
   if (name.find("H_J1PT_120_200") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_j1pt120to200");
   if (name.find("H_J1PT_200_350") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_j1pt200to350");
   if (name.find("H_J1PT_GT350") < 140) h_THUggH = (TH1F*) f_QCDScale->Get("h_THUggH_j1ptgt350");

   lheweight_nominalTo2_average= h_QCDScale->GetBinContent(1)/h_QCDScale->GetBinContent(3);  
   lheweight_nominalTo0p5_average=h_QCDScale->GetBinContent(1)/h_QCDScale->GetBinContent(2); 
   for (int k=0; k<18; ++k){
      WG1unc_average[k]=h_THUggH->GetBinContent(1)/h_THUggH->GetBinContent(k+2); 
   }

   if (name=="OutsideAcceptance"){
      lheweight_nominalTo2_average= 1.0;
      lheweight_nominalTo0p5_average=1.0;
      for (int k=0; k<18; ++k){
         WG1unc_average[k]=1.0;
      }
   }

   TH1F* h_fiducial=new TH1F("h_fiducial","h_fiducial",2,0.,2.);

   TH2F* h_pth_resolution = new TH2F("pth_resolution_2D","pth_resolution_2D",binnum_pthreso,bins_pthreso,binnum_pthreso,bins_pthreso);
   TH1F* h_pth_resolution_0_45=new TH1F("h_pth_resolution_0_45","h_pth_resolution_0_45",100,0.,3.);
   TH1F* h_pth_resolution_45_80=new TH1F("h_pth_resolution_45_80","h_pth_resolution_45_80",100,0.,3.);
   TH1F* h_pth_resolution_0_80=new TH1F("h_pth_resolution_0_80","h_pth_resolution_0_80",100,-1,1.);
   TH1F* h_pth_resolution_80_200=new TH1F("h_pth_resolution_80_200","h_pth_resolution_80_200",100,-1.,1.);
   TH1F* h_pth_resolution_80_120=new TH1F("h_pth_resolution_80_120","h_pth_resolution_80_120",100,0.,2.);
   TH1F* h_pth_resolution_120_200=new TH1F("h_pth_resolution_120_200","h_pth_resolution_120_200",100,0.,2.);
   TH1F* h_pth_resolution_200_350=new TH1F("h_pth_resolution_200_350","h_pth_resolution_200_350",100,0.5,1.5);
   TH1F* h_pth_resolution_gt200=new TH1F("h_pth_resolution_gt200","h_pth_resolution_gt200",100,-1.,1.);
   TH1F* h_pth_resolution_gt350=new TH1F("h_pth_resolution_gt350","h_pth_resolution_gt350",100,0.5,1.5);

   TH1F* h_pth_resolution_0_45_pt30to50=new TH1F("h_pth_resolution_0_45_pt30to50","h_pth_resolution_0_45_pt30to50",100,0.,3.);
   TH1F* h_pth_resolution_45_80_pt30to50=new TH1F("h_pth_resolution_45_80_pt30to50","h_pth_resolution_45_80_pt30to50",100,0.,3.);
   TH1F* h_pth_resolution_80_120_pt30to50=new TH1F("h_pth_resolution_80_120_pt30to50","h_pth_resolution_80_120_pt30to50",100,0.,2.);
   TH1F* h_pth_resolution_120_200_pt30to50=new TH1F("h_pth_resolution_120_200_pt30to50","h_pth_resolution_120_200_pt30to50",100,0.,2.);
   TH1F* h_pth_resolution_200_350_pt30to50=new TH1F("h_pth_resolution_200_350_pt30to50","h_pth_resolution_200_350_pt30to50",100,0.5,1.5);
   TH1F* h_pth_resolution_gt350_pt30to50=new TH1F("h_pth_resolution_gt350_pt30to50","h_pth_resolution_gt350_pt30to50",100,0.5,1.5);

   TH1F* h_pth_resolution_0_45_pt50to70=new TH1F("h_pth_resolution_0_45_pt50to70","h_pth_resolution_0_45_pt50to70",100,0.,3.);
   TH1F* h_pth_resolution_45_80_pt50to70=new TH1F("h_pth_resolution_45_80_pt50to70","h_pth_resolution_45_80_pt50to70",100,0.,3.);
   TH1F* h_pth_resolution_80_120_pt50to70=new TH1F("h_pth_resolution_80_120_pt50to70","h_pth_resolution_80_120_pt50to70",100,0.,2.);
   TH1F* h_pth_resolution_120_200_pt50to70=new TH1F("h_pth_resolution_120_200_pt50to70","h_pth_resolution_120_200_pt50to70",100,0.,2.);
   TH1F* h_pth_resolution_200_350_pt50to70=new TH1F("h_pth_resolution_200_350_pt50to70","h_pth_resolution_200_350_pt50to70",100,0.5,1.5);
   TH1F* h_pth_resolution_gt350_pt50to70=new TH1F("h_pth_resolution_gt350_pt50to70","h_pth_resolution_gt350_pt50to70",100,0.5,1.5);

   TH1F* h_pth_resolution_0_45_ptgt70=new TH1F("h_pth_resolution_0_45_ptgt70","h_pth_resolution_0_45_ptgt70",50,0.,3.);
   TH1F* h_pth_resolution_45_80_ptgt70=new TH1F("h_pth_resolution_45_80_ptgt70","h_pth_resolution_45_80_ptgt70",50,0.,3.);
   TH1F* h_pth_resolution_80_120_ptgt70=new TH1F("h_pth_resolution_80_120_ptgt70","h_pth_resolution_80_120_ptgt70",50,0.,2.);
   TH1F* h_pth_resolution_120_200_ptgt70=new TH1F("h_pth_resolution_120_200_ptgt70","h_pth_resolution_120_200_ptgt70",50,0.,2.);
   TH1F* h_pth_resolution_200_350_ptgt70=new TH1F("h_pth_resolution_200_350_ptgt70","h_pth_resolution_200_350_ptgt70",50,0.5,1.5);
   TH1F* h_pth_resolution_gt350_ptgt70=new TH1F("h_pth_resolution_gt350_ptgt70","h_pth_resolution_gt350_ptgt70",50,0.5,1.5);

   TH2F* h_taupt_vs_hpt = new TH2F("h_taupt_vs_hpt","h_taupt_vs_hpt",10,30,130,15,0,500); 

   TH1F* h_energy_ele=new TH1F("h_energy_ele","h_energy_ele",50,0.,100.);
   TH1F* h_energy_tau=new TH1F("h_energy_tau","h_energy_tau",50,0.,100.);

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
           if (name.find("H_PTH_0_10") < 140 && !(Rivet_higgsPt>=0 && Rivet_higgsPt<10)) continue;
           if (name.find("H_PTH_10_20") < 140 && !(Rivet_higgsPt>=10 && Rivet_higgsPt<20)) continue;
           if (name.find("H_PTH_20_30") < 140 && !(Rivet_higgsPt>=20 && Rivet_higgsPt<30)) continue;
           if (name.find("H_PTH_30_45") < 140 && !(Rivet_higgsPt>=30 && Rivet_higgsPt<45)) continue;
           if (name.find("H_PTH_45_60") < 140 && !(Rivet_higgsPt>=45 && Rivet_higgsPt<60)) continue;
           if (name.find("H_PTH_60_80") < 140 && !(Rivet_higgsPt>=60 && Rivet_higgsPt<80)) continue;
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
	    //if (njets>1 && numGenJets==0) continue;//FIXME
        }

	if (sample=="embedded" && gen_match_2!=5) continue;
        bool is_includedInEmbedded=false;
        ////if ((name.find("ggH")>100 && name.find("xH")>100 && name.find("125")>100 && name.find("qqH")>100 && name.find("WH")>100 && name.find("ZH")>100 && name.find("ttH")>100 && sample!="data_obs" && sample!="embedded") && gen_match_1>2 && gen_match_1<6 && gen_match_2>2 && gen_match_2<6) is_includedInEmbedded=true; // remove overlap with embedded samples
        if (sample!="ggH" and sample!="ggH_htt125" and sample!="qqH" and sample!="qqH_htt125" and sample!="WminusH125" and sample!="WplusH125" and sample!="ZH125" and sample!="ttHTT" and sample!="ttHnonbb" and sample!="GGZHLLTT" and sample!="GGZHQQTT" and sample!="GGZHNNTT" and sample!="data_obs" and sample!="embedded" and gen_match_1>2 and gen_match_1<6 and gen_match_2>2 and gen_match_2<6) is_includedInEmbedded=true; // remove overlap with embedded samples//FIXME
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
	   else aweight=0.0; //FIXME
	   //if (mytau.Pt()>70) aweight=aweight*0.7;//FIXME
	}
        if (sample!="embedded" && sample!="data_obs" && (gen_match_2==2 or gen_match_2==4)){
             if (fabs(eta_2)<0.4) aweight=aweight*0.936*1.019;
             else if (fabs(eta_2)<0.8) aweight=aweight*0.874*1.154;
             else if (fabs(eta_2)<1.2) aweight=aweight*0.912*1.128;
             else if (fabs(eta_2)<1.7) aweight=aweight*0.953*0.974;
             else aweight=aweight*0.936*5.342;
        }

	//NNLOPS weights
        if (name.find("ggH")<100 && name.find("NNLOPS")>100 && name.find("hww")>100){
            if (Rivet_nJets30==0) aweight = aweight * g_NNLOPS_0jet->Eval(min(Rivet_higgsPt,float(125.0)));
            if (Rivet_nJets30==1) aweight = aweight * g_NNLOPS_1jet->Eval(min(Rivet_higgsPt,float(625.0)));
            if (Rivet_nJets30==2) aweight = aweight * g_NNLOPS_2jet->Eval(min(Rivet_higgsPt,float(800.0)));
            if (Rivet_nJets30>=3) aweight = aweight * g_NNLOPS_3jet->Eval(min(Rivet_higgsPt,float(925.0)));
        }
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
	  float tautrgsf=0.85*wmc->function("t_trg_pog_deeptau_medium_etau_ratio")->getVal();//FIXME
          if (myele.Pt()>33) aweight=aweight*wmc->function("e_trg_ic_ratio")->getVal();
	  else aweight=aweight*wmc->function("e_trg_24_ic_ratio")->getVal()*tautrgsf;
          if (tautrgsf>0) trg_up=wmc->function("t_trg_pog_deeptau_medium_etau_ratio_up")->getVal()/tautrgsf;
          if (tautrgsf>0) trg_down=wmc->function("t_trg_pog_deeptau_medium_etau_ratio_down")->getVal()/tautrgsf;


          float weight_btag=bTagEventWeight(nbtag20,bMpt_1,bMflavor_1,bMpt_2,bMflavor_2,1,0,0);
          if (nbtag20>2) weight_btag=0;
          aweight=aweight*weight_btag;

	}

	//************************ Compute fake factors ******************
	float frac_qcd=0.2;
	float frac_w=0.7;
	float frac_tt=0.1;

        if ((myele+mytau+mymet).Pt()>=0 && (myele+mytau+mymet).Pt()<45){
            frac_qcd=frac_qcd_pth0to45->GetBinContent(frac_qcd_pth0to45->GetXaxis()->FindBin(m_sv))/frac_data_pth0to45->GetBinContent(frac_data_pth0to45->GetXaxis()->FindBin(m_sv));
            frac_w=frac_w_pth0to45->GetBinContent(frac_w_pth0to45->GetXaxis()->FindBin(m_sv))/frac_data_pth0to45->GetBinContent(frac_data_pth0to45->GetXaxis()->FindBin(m_sv));
            frac_tt=frac_tt_pth0to45->GetBinContent(frac_tt_pth0to45->GetXaxis()->FindBin(m_sv))/frac_data_pth0to45->GetBinContent(frac_data_pth0to45->GetXaxis()->FindBin(m_sv));
        }
        else if ((myele+mytau+mymet).Pt()>=45 && (myele+mytau+mymet).Pt()<80){
            frac_qcd=frac_qcd_pth45to80->GetBinContent(frac_qcd_pth45to80->GetXaxis()->FindBin(m_sv))/frac_data_pth45to80->GetBinContent(frac_data_pth45to80->GetXaxis()->FindBin(m_sv));
            frac_w=frac_w_pth45to80->GetBinContent(frac_w_pth45to80->GetXaxis()->FindBin(m_sv))/frac_data_pth45to80->GetBinContent(frac_data_pth45to80->GetXaxis()->FindBin(m_sv));
            frac_tt=frac_tt_pth45to80->GetBinContent(frac_tt_pth45to80->GetXaxis()->FindBin(m_sv))/frac_data_pth45to80->GetBinContent(frac_data_pth45to80->GetXaxis()->FindBin(m_sv));
        }
        else if ((myele+mytau+mymet).Pt()>=80 && (myele+mytau+mymet).Pt()<120){
            frac_qcd=frac_qcd_pth80to120->GetBinContent(frac_qcd_pth80to120->GetXaxis()->FindBin(m_sv))/frac_data_pth80to120->GetBinContent(frac_data_pth80to120->GetXaxis()->FindBin(m_sv));
            frac_w=frac_w_pth80to120->GetBinContent(frac_w_pth80to120->GetXaxis()->FindBin(m_sv))/frac_data_pth80to120->GetBinContent(frac_data_pth80to120->GetXaxis()->FindBin(m_sv));
            frac_tt=frac_tt_pth80to120->GetBinContent(frac_tt_pth80to120->GetXaxis()->FindBin(m_sv))/frac_data_pth80to120->GetBinContent(frac_data_pth80to120->GetXaxis()->FindBin(m_sv));
        }
        else if ((myele+mytau+mymet).Pt()>=120 && (myele+mytau+mymet).Pt()<200){
            frac_qcd=frac_qcd_pth120to200->GetBinContent(frac_qcd_pth120to200->GetXaxis()->FindBin(m_sv))/frac_data_pth120to200->GetBinContent(frac_data_pth120to200->GetXaxis()->FindBin(m_sv));
            frac_w=frac_w_pth120to200->GetBinContent(frac_w_pth120to200->GetXaxis()->FindBin(m_sv))/frac_data_pth120to200->GetBinContent(frac_data_pth120to200->GetXaxis()->FindBin(m_sv));
            frac_tt=frac_tt_pth120to200->GetBinContent(frac_tt_pth120to200->GetXaxis()->FindBin(m_sv))/frac_data_pth120to200->GetBinContent(frac_data_pth120to200->GetXaxis()->FindBin(m_sv));
        }
        else if ((myele+mytau+mymet).Pt()>=200){
            frac_qcd=frac_qcd_pthgt200->GetBinContent(frac_qcd_pthgt200->GetXaxis()->FindBin(m_sv))/frac_data_pthgt200->GetBinContent(frac_data_pthgt200->GetXaxis()->FindBin(m_sv));
            frac_w=frac_w_pthgt200->GetBinContent(frac_w_pthgt200->GetXaxis()->FindBin(m_sv))/frac_data_pthgt200->GetBinContent(frac_data_pthgt200->GetXaxis()->FindBin(m_sv));
            frac_tt=frac_tt_pthgt200->GetBinContent(frac_tt_pthgt200->GetXaxis()->FindBin(m_sv))/frac_data_pthgt200->GetBinContent(frac_data_pthgt200->GetXaxis()->FindBin(m_sv));
        }
	if (frac_qcd<0) frac_qcd=0;

	float total=frac_qcd+frac_w+frac_tt;
	frac_qcd=frac_qcd/total;
        frac_w=frac_w/total;
        frac_tt=frac_tt/total;

if (mytau.Pt()>70) {frac_qcd=0.0; frac_w=1.0; frac_tt=0.0;}

	float mt=TMass_F(myele.Pt(),mymet.Pt(),myele.Px(),mymet.Px(),myele.Py(),mymet.Py());

        if (!norecoil){ m_sv_JetAbsoluteUp=m_sv; m_sv_JetAbsoluteyearUp=m_sv; m_sv_JetBBEC1Up=m_sv; m_sv_JetBBEC1yearUp=m_sv; m_sv_JetEC2Up=m_sv; m_sv_JetEC2yearUp=m_sv; m_sv_JetFlavorQCDUp=m_sv; m_sv_JetHFUp=m_sv; m_sv_JetHFyearUp=m_sv; m_sv_JetRelativeBalUp=m_sv; m_sv_JetRelativeSampleUp=m_sv; m_sv_JERUp=m_sv; m_sv_JetAbsoluteDown=m_sv; m_sv_JetAbsoluteyearDown=m_sv; m_sv_JetBBEC1Down=m_sv; m_sv_JetBBEC1yearDown=m_sv; m_sv_JetEC2Down=m_sv; m_sv_JetEC2yearDown=m_sv; m_sv_JetFlavorQCDDown=m_sv; m_sv_JetHFDown=m_sv; m_sv_JetHFyearDown=m_sv; m_sv_JetRelativeBalDown=m_sv; m_sv_JetRelativeSampleDown=m_sv; m_sv_JERDown=m_sv;}

	//************************* Fill histograms **********************
	bool is_xtrg=false;
        float uncorrected_pth=(myele+mytau+mymet).Pt();
        float pth=uncorrected_pth*fit_pthcorrection->Eval(uncorrected_pth);
        if (pth<0) pth=0.5;

	if (myele.Pt()<33) is_xtrg=true;
	double FF=1.0*get_ff(mytau.Pt(), mytau.Eta(), mt, (myele+mytau).M(), m_sv, myele.Pt(), mymet.Pt(), pth, jpt_1, njets, is_xtrg, frac_tt, frac_qcd, frac_w, ""); // Our FF
//cout<<myele.Pt()<<" "<<mytau.Pt()<<" "<<get_ff(mytau.Pt(), mt, (myele+mytau).M(), m_sv, myele.Pt(), mymet.Pt(), pth, njets, is_xtrg, 0,1,0, "")<<" "<<get_ff(mytau.Pt(), mt, (myele+mytau).M(), m_sv, myele.Pt(), mymet.Pt(), pth, njets, is_xtrg, 0,0,1, "")<<" "<<get_ff(mytau.Pt(), mt, (myele+mytau).M(), m_sv, myele.Pt(), mymet.Pt(), pth, njets, is_xtrg, 1,0,0, "")<<" "<<frac_qcd<<" "<<frac_w<<" "<<frac_tt<<endl;
	float myvar=(myele+mytau).M();
	TLorentzVector myrawtau=mytau;
        TLorentzVector myrawele=myele;
        TLorentzVector myrawmet=mymet;
	float myrawpth=pth;
        float massJets=mjj;
        int numberJets=njets;
	float leadingJetPt=jpt_1;
	float mtt=m_sv;
	float rawtaupt=mytau.Pt();
	float rawmt=mt;
	float rawmvis=(myele+mytau).M();
	float rawnjets=njets;

	for (int k=0; k<nbhist; ++k){

	   float weight2=1.0;

	   // reset all variables before any systematic shift
	   massJets=mjj;
	   mtt=m_sv;
	   numberJets=njets;
	   leadingJetPt=jpt_1;
	   mytau=myrawtau;
           myele=myrawele;
	   mymet=myrawmet;
	   massJets=mjj;

	   if (sample=="embedded"){
              if (k>0 && k<9 && gen_match_2==5){ // TES x 8
                if (k==1 && l2_decayMode==0){mytau*=0.9961; mymet=mymet+(0.0039/0.9961)*mytau; mtt=m_sv_DOWN;}
                else if (k==2 && l2_decayMode==0){mytau*=1.0039; mymet=mymet-(0.0039/1.0039)*mytau; mtt=m_sv_UP;}
                else if (k==3 && l2_decayMode==1){mytau*=0.9969; mymet=mymet+(0.0031/0.9969)*mytau; mtt=m_sv_DOWN;}
                else if (k==4 && l2_decayMode==1){mytau*=1.0037; mymet=mymet-(0.0037/1.0037)*mytau; mtt=m_sv_UP;}
                else if (k==5 && l2_decayMode==10){mytau*=0.9968; mymet=mymet+(0.0032/0.9968)*mytau; mtt=m_sv_DOWN;}
                else if (k==6 && l2_decayMode==10){mytau*=1.0032; mymet=mymet-(0.0032/1.0032)*mytau; mtt=m_sv_UP;}
                else if (k==7 && l2_decayMode==11){mytau*=0.9968; mymet=mymet+(0.0032/0.9968)*mytau; mtt=m_sv_DOWN;}
                else if (k==8 && l2_decayMode==11){mytau*=1.0032; mymet=mymet-(0.0032/1.0032)*mytau; mtt=m_sv_UP;}
              }
              if (k>8 && k<13){ // EES x 2 
                if (k==9 && fabs(myele.Eta())<1.479) {myele*=0.9950; mymet=mymet+(0.0050/0.9950)*myele; mtt=m_sv_ESCALEDOWN;}
                else if (k==10 && fabs(myele.Eta())<1.479) {myele*=1.0050; mymet=mymet-(0.0050/1.0050)*myele; mtt=m_sv_ESCALEUP;}
                else if (k==11 && fabs(myele.Eta())>=1.479) {myele*=0.9875; mymet=mymet+(0.0125/0.9875)*myele; mtt=m_sv_ESCALEDOWN;}
                else if (k==12 && fabs(myele.Eta())>=1.479) {myele*=1.0125; mymet=mymet-(0.0125/1.0125)*myele; mtt=m_sv_ESCALEUP;}
              }
              else if (k>12 && k<17){ // TRG x 4 
                if (k==13 && myele.Pt()>33){weight2=0.98;}
                else if (k==14 && myele.Pt()>33){weight2=1.02;}
                else if (k==15 && myele.Pt()<33){weight2=0.99*trg_down;}
                else if (k==16 && myele.Pt()<33){weight2=1.01*trg_up;}
              }
              else if (k>16 && k<23){ // Tau ID x 6
                if (k==17 && mytau.Pt()>=30 && mytau.Pt()<35) weight2=fct_tauid_emb_down->Eval(myrawtau.Pt())/fct_tauid_emb->Eval(myrawtau.Pt());
                else if (k==18 && mytau.Pt()>=30 && mytau.Pt()<35) weight2=fct_tauid_emb_up->Eval(myrawtau.Pt())/fct_tauid_emb->Eval(myrawtau.Pt());
                else if (k==19 && mytau.Pt()>=35 && mytau.Pt()<40) weight2=fct_tauid_emb_down->Eval(myrawtau.Pt())/fct_tauid_emb->Eval(myrawtau.Pt());
                else if (k==20 && mytau.Pt()>=35 && mytau.Pt()<40) weight2=fct_tauid_emb_up->Eval(myrawtau.Pt())/fct_tauid_emb->Eval(myrawtau.Pt());
                else if (k==21 && mytau.Pt()>=40) weight2=fct_tauid_emb_down->Eval(myrawtau.Pt())/fct_tauid_emb->Eval(myrawtau.Pt());
                else if (k==22 && mytau.Pt()>=40) weight2=fct_tauid_emb_up->Eval(myrawtau.Pt())/fct_tauid_emb->Eval(myrawtau.Pt());
	      }
              else if (k>22 && k<29 && gen_match_2==5){ // embedded tracking
                if (k==23 && l2_decayMode==0) weight2=0.99;
                else if (k==23 && l2_decayMode==10) weight2=0.97;
                else if (k==24 && l2_decayMode==0) weight2=1.01;
                else if (k==24 && l2_decayMode==10) weight2=1.03;
                else if (k==25 && l2_decayMode==1) weight2=0.975;
                else if (k==26 && l2_decayMode==1) weight2=1.025;
                else if (k==27 && l2_decayMode==11) weight2=0.94;
                else if (k==28 && l2_decayMode==11) weight2=1.06;
              }
              else if (k>28 && k<31 && numberJets==0){ // embedded 0jet
                if (k==29) weight2=0.85;
                else if (k==30) weight2=1.15;
	      }
              else if (k>30 && k<33){ // looser lep
                if (k==31 and mytau.Pt()<100 and gen_match_2==5) weight2=0.95;
                else if (k==31 and mytau.Pt()>=100 and gen_match_2==5) weight2=0.85;
                else if (k==32 and mytau.Pt()<100 and gen_match_2==5) weight2=1.05;
                else if (k==32 and mytau.Pt()>=100 and gen_match_2==5) weight2=1.15;
	      }
	   }

           if (sample!="data_obs" && sample!="embedded"){
              if (k>0 && k<9 && gen_match_2==5){ // TES x 8
                if (k==1 && l2_decayMode==0){mytau*=0.989; mymet=mymet+(0.011/0.989)*mytau; mtt=m_sv_DOWN;}
                else if (k==2 && l2_decayMode==0){mytau*=1.011; mymet=mymet-(0.011/1.011)*mytau; mtt=m_sv_UP;}
                else if (k==3 && l2_decayMode==1){mytau*=0.992; mymet=mymet+(0.008/0.992)*mytau; mtt=m_sv_DOWN;}
                else if (k==4 && l2_decayMode==1){mytau*=1.008; mymet=mymet-(0.008/1.008)*mytau; mtt=m_sv_UP;}
                else if (k==5 && l2_decayMode==10){mytau*=0.991; mymet=mymet+(0.009/0.991)*mytau; mtt=m_sv_DOWN;}
                else if (k==6 && l2_decayMode==10){mytau*=1.009; mymet=mymet-(0.009/1.009)*mytau; mtt=m_sv_UP;}
                else if (k==7 && l2_decayMode==11){mytau*=0.991; mymet=mymet+(0.009/0.991)*mytau; mtt=m_sv_DOWN;}
                else if (k==8 && l2_decayMode==11){mytau*=1.009; mymet=mymet-(0.009/1.009)*mytau; mtt=m_sv_UP;}
              }
	      else if (k>8 && k<15 && byMediumDeepVSjet_2 && gen_match_2==5){
		if (k==9 && mytau.Pt()>=30 && mytau.Pt()<35) weight2=fct_tauid_down->Eval(myrawtau.Pt())/fct_tauid->Eval(myrawtau.Pt());
                else if (k==10 && mytau.Pt()>=30 && mytau.Pt()<35) weight2=fct_tauid_up->Eval(myrawtau.Pt())/fct_tauid->Eval(myrawtau.Pt());
                else if (k==11 && mytau.Pt()>=35 && mytau.Pt()<40) weight2=fct_tauid_down->Eval(myrawtau.Pt())/fct_tauid->Eval(myrawtau.Pt());
                else if (k==12 && mytau.Pt()>=35 && mytau.Pt()<40) weight2=fct_tauid_up->Eval(myrawtau.Pt())/fct_tauid->Eval(myrawtau.Pt());
                else if (k==13 && mytau.Pt()>=40) weight2=fct_tauid_down->Eval(myrawtau.Pt())/fct_tauid->Eval(myrawtau.Pt());
                else if (k==14 && mytau.Pt()>=40) weight2=fct_tauid_up->Eval(myrawtau.Pt())/fct_tauid->Eval(myrawtau.Pt());
	      }
              else if (k>14 && k<39){ // JES x 24
                if (k==15){numberJets=njets_JetAbsoluteDown; massJets=mjj_JetAbsoluteDown; mymet.SetPtEtaPhiM(met_JetAbsoluteDown,0,metphi_JetAbsoluteDown,0); mtt=m_sv_JetAbsoluteDown; leadingJetPt=jpt_1_JetAbsoluteDown;}
                else if (k==16){numberJets=njets_JetAbsoluteUp; massJets=mjj_JetAbsoluteUp; mymet.SetPtEtaPhiM(met_JetAbsoluteUp,0,metphi_JetAbsoluteUp,0); mtt=m_sv_JetAbsoluteUp; leadingJetPt=jpt_1_JetAbsoluteUp;}
                else if (k==17){numberJets=njets_JetAbsoluteyearDown; massJets=mjj_JetAbsoluteyearDown; mymet.SetPtEtaPhiM(met_JetAbsoluteyearDown,0,metphi_JetAbsoluteyearDown,0); mtt=m_sv_JetAbsoluteyearDown; leadingJetPt=jpt_1_JetAbsoluteyearDown;}
                else if (k==18){numberJets=njets_JetAbsoluteyearUp; massJets=mjj_JetAbsoluteyearUp; mymet.SetPtEtaPhiM(met_JetAbsoluteyearUp,0,metphi_JetAbsoluteyearUp,0); mtt=m_sv_JetAbsoluteyearUp; leadingJetPt=jpt_1_JetAbsoluteyearUp;}
                else if (k==19){numberJets=njets_JetBBEC1Down; massJets=mjj_JetBBEC1Down; mymet.SetPtEtaPhiM(met_JetBBEC1Down,0,metphi_JetBBEC1Down,0); mtt=m_sv_JetBBEC1Down; leadingJetPt=jpt_1_JetBBEC1Down;}
                else if (k==20){numberJets=njets_JetBBEC1Up; massJets=mjj_JetBBEC1Up; mymet.SetPtEtaPhiM(met_JetBBEC1Up,0,metphi_JetBBEC1Up,0); mtt=m_sv_JetBBEC1Up; leadingJetPt=jpt_1_JetBBEC1Up;}
                else if (k==21){numberJets=njets_JetBBEC1yearDown; massJets=mjj_JetBBEC1yearDown; mymet.SetPtEtaPhiM(met_JetBBEC1yearDown,0,metphi_JetBBEC1yearDown,0); mtt=m_sv_JetBBEC1yearDown; leadingJetPt=jpt_1_JetBBEC1yearDown;}
                else if (k==22){numberJets=njets_JetBBEC1yearUp; massJets=mjj_JetBBEC1yearUp; mymet.SetPtEtaPhiM(met_JetBBEC1yearUp,0,metphi_JetBBEC1yearUp,0); mtt=m_sv_JetBBEC1yearUp; leadingJetPt=jpt_1_JetBBEC1yearUp;}
                else if (k==23){numberJets=njets_JetEC2Down; massJets=mjj_JetEC2Down; mymet.SetPtEtaPhiM(met_JetEC2Down,0,metphi_JetEC2Down,0); mtt=m_sv_JetEC2Down; leadingJetPt=jpt_1_JetEC2Down;}
                else if (k==24){numberJets=njets_JetEC2Up; massJets=mjj_JetEC2Up; mymet.SetPtEtaPhiM(met_JetEC2Up,0,metphi_JetEC2Up,0); mtt=m_sv_JetEC2Up; leadingJetPt=jpt_1_JetEC2Up;}
                else if (k==25){numberJets=njets_JetEC2yearDown; massJets=mjj_JetEC2yearDown; mymet.SetPtEtaPhiM(met_JetEC2yearDown,0,metphi_JetEC2yearDown,0); mtt=m_sv_JetEC2yearDown; leadingJetPt=jpt_1_JetEC2yearDown;}
                else if (k==26){numberJets=njets_JetEC2yearUp; massJets=mjj_JetEC2yearUp; mymet.SetPtEtaPhiM(met_JetEC2yearUp,0,metphi_JetEC2yearUp,0); mtt=m_sv_JetEC2yearUp; leadingJetPt=jpt_1_JetEC2yearUp;}
                else if (k==27){numberJets=njets_JetFlavorQCDDown; massJets=mjj_JetFlavorQCDDown; mymet.SetPtEtaPhiM(met_JetFlavorQCDDown,0,metphi_JetFlavorQCDDown,0); mtt=m_sv_JetFlavorQCDDown; leadingJetPt=jpt_1_JetFlavorQCDDown;}
                else if (k==28){numberJets=njets_JetFlavorQCDUp; massJets=mjj_JetFlavorQCDUp; mymet.SetPtEtaPhiM(met_JetFlavorQCDUp,0,metphi_JetFlavorQCDUp,0); mtt=m_sv_JetFlavorQCDUp; leadingJetPt=jpt_1_JetFlavorQCDUp;}
                else if (k==29){numberJets=njets_JetHFDown; massJets=mjj_JetHFDown; mymet.SetPtEtaPhiM(met_JetHFDown,0,metphi_JetHFDown,0); mtt=m_sv_JetHFDown; leadingJetPt=jpt_1_JetHFDown;}
                else if (k==30){numberJets=njets_JetHFUp; massJets=mjj_JetHFUp; mymet.SetPtEtaPhiM(met_JetHFUp,0,metphi_JetHFUp,0); mtt=m_sv_JetHFUp; leadingJetPt=jpt_1_JetHFUp;}
                else if (k==31){numberJets=njets_JetHFyearDown; massJets=mjj_JetHFyearDown; mymet.SetPtEtaPhiM(met_JetHFyearDown,0,metphi_JetHFyearDown,0); mtt=m_sv_JetHFyearDown; leadingJetPt=jpt_1_JetHFyearDown;}
                else if (k==32){numberJets=njets_JetHFyearUp; massJets=mjj_JetHFyearUp; mymet.SetPtEtaPhiM(met_JetHFyearUp,0,metphi_JetHFyearUp,0); mtt=m_sv_JetHFyearUp; leadingJetPt=jpt_1_JetHFyearUp;}
                else if (k==33){numberJets=njets_JetRelativeBalDown; massJets=mjj_JetRelativeBalDown; mymet.SetPtEtaPhiM(met_JetRelativeBalDown,0,metphi_JetRelativeBalDown,0); mtt=m_sv_JetRelativeBalDown; leadingJetPt=jpt_1_JetRelativeBalDown;}
                else if (k==34){numberJets=njets_JetRelativeBalUp; massJets=mjj_JetRelativeBalUp; mymet.SetPtEtaPhiM(met_JetRelativeBalUp,0,metphi_JetRelativeBalUp,0); mtt=m_sv_JetRelativeBalUp; leadingJetPt=jpt_1_JetRelativeBalUp;}
                else if (k==35){numberJets=njets_JetRelativeSampleDown; massJets=mjj_JetRelativeSampleDown; mymet.SetPtEtaPhiM(met_JetRelativeSampleDown,0,metphi_JetRelativeSampleDown,0); mtt=m_sv_JetRelativeSampleDown; leadingJetPt=jpt_1_JetRelativeSampleDown;}
                else if (k==36){numberJets=njets_JetRelativeSampleUp; massJets=mjj_JetRelativeSampleUp; mymet.SetPtEtaPhiM(met_JetRelativeSampleUp,0,metphi_JetRelativeSampleUp,0); mtt=m_sv_JetRelativeSampleUp; leadingJetPt=jpt_1_JetRelativeSampleUp;}
                else if (k==37){numberJets=njets_JERDown; massJets=mjj_JERDown; mymet.SetPtEtaPhiM(met_JERDown,0,metphi_JERDown,0); mtt=m_sv_JERDown; leadingJetPt=jpt_1_JERDown;}
                else if (k==38){numberJets=njets_JERUp; massJets=mjj_JERUp; mymet.SetPtEtaPhiM(met_JERUp,0,metphi_JERUp,0); mtt=m_sv_JERUp; leadingJetPt=jpt_1_JERUp;}
              }
              else if (k>38 && k<47 && (gen_match_2<5)){ // e->tau fake ES x 4
                if (k==39 && l2_decayMode==0 && fabs(mytau.Eta())<1.5){mytau*=0.99526; mymet=mymet+(0.00474/0.99526)*mytau; mtt=m_sv_DOWN;}
                else if (k==40 && l2_decayMode==0 && fabs(mytau.Eta())<1.5){mytau*=1.00904; mymet=mymet-(0.00904/1.00904)*mytau; mtt=m_sv_UP;}
                else if (k==41 && l2_decayMode==1 && fabs(mytau.Eta())<1.5){mytau*=0.98402; mymet=mymet+(0.01598/0.98402)*mytau; mtt=m_sv_DOWN;}
                else if (k==42 && l2_decayMode==1 && fabs(mytau.Eta())<1.5){mytau*=1.01226; mymet=mymet-(0.01226/1.01226)*mytau; mtt=m_sv_UP;}
                else if (k==43 && l2_decayMode==0 && fabs(mytau.Eta())>1.5){mytau*=0.98750; mymet=mymet+(0.01250/0.98750)*mytau; mtt=m_sv_DOWN;}
                else if (k==44 && l2_decayMode==0 && fabs(mytau.Eta())>1.5){mytau*=1.03404; mymet=mymet-(0.03404/1.03404)*mytau; mtt=m_sv_UP;}
                else if (k==45 && l2_decayMode==1 && fabs(mytau.Eta())>1.5){mytau*=0.95961; mymet=mymet+(0.04309/0.95691)*mytau; mtt=m_sv_DOWN;}
                else if (k==46 && l2_decayMode==1 && fabs(mytau.Eta())>1.5){mytau*=1.05499; mymet=mymet-(0.05499/1.05499)*mytau; mtt=m_sv_UP;}
              }
              else if ((name=="TT" or name=="VV" or name=="ST") && k>46 && k<49){ // UES x 2
                if (k==47){mymet=myrawmet; mymet.SetPtEtaPhiM(met_UESDown, 0, metphi_UESDown, 0); mtt=m_sv_UESDown;}
                else if (k==48){mymet=myrawmet; mymet.SetPtEtaPhiM(met_UESUp, 0, metphi_UESUp, 0); mtt=m_sv_UESUp;}
	      }
              else if (!(name=="TT" or name=="VV" or name=="ST") && k>48 && k<61){ // recoil x 12
                if (k==49 && numberJets==0){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionDown, 0, metphi_resolutionDown, 0); mtt=m_sv_ResolutionDown;}
                else if (k==50 && numberJets==0){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionUp, 0, metphi_resolutionUp, 0); mtt=m_sv_ResolutionUp;}
                else if (k==51 && numberJets==0){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseDown, 0, metphi_responseDown, 0); mtt=m_sv_ResponseDown;}
                else if (k==52 && numberJets==0){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseUp, 0, metphi_responseUp, 0); mtt=m_sv_ResponseUp;}
                else if (k==53 && numberJets==1){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionDown, 0, metphi_resolutionDown, 0); mtt=m_sv_ResolutionDown;}
                else if (k==54 && numberJets==1){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionUp, 0, metphi_resolutionUp, 0); mtt=m_sv_ResolutionUp;}
                else if (k==55 && numberJets==1){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseDown, 0, metphi_responseDown, 0); mtt=m_sv_ResponseDown;}
                else if (k==56 && numberJets==1){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseUp, 0, metphi_responseUp, 0); mtt=m_sv_ResponseUp;}
                else if (k==57 && numberJets>1){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionDown, 0, metphi_resolutionDown, 0); mtt=m_sv_ResolutionDown;}
                else if (k==58 && numberJets>1){mymet=myrawmet; mymet.SetPtEtaPhiM(met_resolutionUp, 0, metphi_resolutionUp, 0); mtt=m_sv_ResolutionUp;}
                else if (k==59 && numberJets>1){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseDown, 0, metphi_responseDown, 0); mtt=m_sv_ResponseDown;}
                else if (k==60 && numberJets>1){mymet=myrawmet; mymet.SetPtEtaPhiM(met_responseUp, 0, metphi_responseUp, 0); mtt=m_sv_ResponseUp;}
              }
              else if (k>60 && k<63 && (sample=="TTToHadronic" or sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic")){ //Top pt reweighting x 2
                if (k==61) weight2=1.0/topfactor;
                else if (k==62) weight2=topfactor;
              }
              else if (k>62 && k<65 && (sample=="DY" or sample=="Z")){ //Z pt reweighting x 2
                if (k==63) weight2=(zptweight-0.10*(zptweight-1))/zptweight;
                else if (k==64) weight2=(zptweight+0.10*(zptweight-1))/zptweight;
              }
              else if (k>64 && k<67){ // EES x 2 
                if (k==65){myele*=(pt_1_ScaleDown/myele.Pt()); mymet=mymet-myele+myrawele; mtt=m_sv_ESCALEDOWN;}
                else if (k==66){myele*=(pt_1_ScaleUp/myele.Pt()); mymet=mymet-myele+myrawele; mtt=m_sv_ESCALEUP;}
              }
              else if (k>66 && k<71){ // TRG x 4 
                if (k==67 && myele.Pt()>33){weight2=0.98;}
                else if (k==68 && myele.Pt()>33){weight2=1.02;}
                else if (k==69 && myele.Pt()<33){weight2=0.99*trg_down;}
                else if (k==70 && myele.Pt()<33){weight2=1.01*trg_up;}
              }
              if (k>70 && k<81){
                if (k==71 && (gen_match_2==1 or gen_match_2==3) && mytau.Pt()>=30 && mytau.Pt()<50) {weight2=0.90;}
                else if (k==72 && (gen_match_2==1 or gen_match_2==3) && mytau.Pt()>=30 && mytau.Pt()<50) {weight2=1.10;}
                else if (k==73 && (gen_match_2==1 or gen_match_2==3) && mytau.Pt()>=50 && mytau.Pt()<70) {weight2=0.90;}
                else if (k==74 && (gen_match_2==1 or gen_match_2==3) && mytau.Pt()>=50 && mytau.Pt()<70) {weight2=1.10;}
                else if (k==75 && (gen_match_2==1 or gen_match_2==3) && mytau.Pt()>=70) {weight2=0.70;}
                else if (k==76 && (gen_match_2==1 or gen_match_2==3) && mytau.Pt()>=70) {weight2=1.30;}
                else if (k==77 && (gen_match_2==1 or gen_match_2==3) && fabs(mytau.Eta())<1.460) {weight2=1.27;}
                else if (k==78 && (gen_match_2==1 or gen_match_2==3) && fabs(mytau.Eta())<1.460) {weight2=0.73;}
                else if (k==79 && (gen_match_2==1 or gen_match_2==3) && fabs(mytau.Eta())>1.460) {weight2=1.20;}
                else if (k==80 && (gen_match_2==1 or gen_match_2==3) && fabs(mytau.Eta())>1.460) {weight2=0.80;}
	      }
              else if (k>80 && k<83){ // looser lep
                if (k==81 and mytau.Pt()<100 and gen_match_2==5) weight2=0.97;
                else if (k==81 and mytau.Pt()>=100 and gen_match_2==5) weight2=0.85;
                else if (k==82 and mytau.Pt()<100 and gen_match_2==5) weight2=1.03;
                else if (k==82 and mytau.Pt()>=100 and gen_match_2==5) weight2=1.15;
              }
	      else if (is_higgs && (k>82 && k<91)){ // muR muF scale x 2 x 4
		if (k==83 and (sample=="qqH" or sample=="qqH_htt125" or sample=="VBFHWW")) weight2=lheweight_nominalTo0p5_average*(lheweight_muR0p5_muF0p5/lheweight_nominal);
		else if (k==84 and (sample=="qqH" or sample=="qqH_htt125" or sample=="VBFHWW")) weight2=lheweight_nominalTo2_average*(lheweight_muR2_muF2/lheweight_nominal);
                if (k==85 and (sample=="WplusH125" or sample=="WminusH125" or sample=="ZH125" or sample=="WminusHWW" or sample=="WplusHWW" or sample=="ZHWW")) weight2=lheweight_nominalTo0p5_average*(lheweight_muR0p5_muF0p5/lheweight_nominal);
                else if (k==86 and (sample=="WplusH125" or sample=="WminusH125" or sample=="ZH125" or sample=="WminusHWW" or sample=="WplusHWW" or sample=="ZHWW")) weight2=lheweight_nominalTo2_average*(lheweight_muR2_muF2/lheweight_nominal);
                if (k==87 and (sample=="GGZHLLTT125" or sample=="GGZHNNTT125" or sample=="GGZHQQTT125" or sample=="GGZHWW")) weight2=lheweight_nominalTo0p5_average*(lheweight_muR0p5_muF0p5/lheweight_nominal);
                else if (k==88 and (sample=="GGZHLLTT125" or sample=="GGZHNNTT125" or sample=="GGZHQQTT125" or sample=="GGZHWW")) weight2=lheweight_nominalTo2_average*(lheweight_muR2_muF2/lheweight_nominal);
                if (k==89 and (sample=="ttHTT")) weight2=lheweight_nominalTo0p5_average*(lheweight_muR0p5_muF0p5/lheweight_nominal);
                else if (k==90 and (sample=="ttHTT")) weight2=lheweight_nominalTo2_average*(lheweight_muR2_muF2/lheweight_nominal);
	      }
              else if (is_higgs && (sample=="ggH_htt125" or sample=="ggH" or sample=="GGHWW") && k>90 && k<109){ // WG1 x 18
                if (k==91) weight2=WG1unc_average[0]*(1+WG1unc[0]);
                else if (k==92) weight2=WG1unc_average[1]*(1-WG1unc[0]);
                else if (k==93) weight2=WG1unc_average[2]*(1+WG1unc[1]);
                else if (k==94) weight2=WG1unc_average[3]*(1-WG1unc[1]);
                else if (k==95) weight2=WG1unc_average[4]*(1+WG1unc[2]);
                else if (k==96) weight2=WG1unc_average[5]*(1-WG1unc[2]);
                else if (k==97) weight2=WG1unc_average[6]*(1+WG1unc[3]);
                else if (k==98) weight2=WG1unc_average[7]*(1-WG1unc[3]);
                else if (k==99) weight2=WG1unc_average[8]*(1+WG1unc[4]);
                else if (k==100) weight2=WG1unc_average[9]*(1-WG1unc[4]);
                else if (k==101) weight2=WG1unc_average[10]*(1+WG1unc[5]);
                else if (k==102) weight2=WG1unc_average[11]*(1-WG1unc[5]);
                else if (k==103) weight2=WG1unc_average[12]*(1+WG1unc[6]);
                else if (k==104) weight2=WG1unc_average[13]*(1-WG1unc[6]);
                else if (k==105) weight2=WG1unc_average[14]*(1+WG1unc[7]);
                else if (k==106) weight2=WG1unc_average[15]*(1-WG1unc[7]);
                else if (k==107) weight2=WG1unc_average[16]*(1+WG1unc[8]);
                else if (k==108) weight2=WG1unc_average[17]*(1-WG1unc[8]);
              }
           }
	   if (name=="ST" or name=="VV" or name=="DY" or name=="Z" or name=="TT"){
              if (k>82 && k<171){ // FF 
	   	FF=1.0*get_ff(rawtaupt, mytau.Eta(), rawmt, rawmvis, m_sv, myrawele.Pt(), myrawmet.Pt(), myrawpth, jpt_1, rawnjets, is_xtrg, frac_tt, frac_qcd, frac_w,FFsys[k-1-82]);
              }
           }
           if (sample=="data_obs"){
              if (k>0 && k<89){ // FF 
		FF=1.0*get_ff(rawtaupt, mytau.Eta(), rawmt, rawmvis, m_sv, myrawele.Pt(), myrawmet.Pt(), myrawpth, jpt_1, rawnjets, is_xtrg, frac_tt, frac_qcd, frac_w,FFsys[k-1]);
              }
           }
	   if (sample=="embedded"){
              if (k>32 && k<121){ // FF 
                FF=1.0*get_ff(rawtaupt, mytau.Eta(), rawmt, rawmvis, m_sv, myrawele.Pt(), myrawmet.Pt(), myrawpth, jpt_1, rawnjets, is_xtrg, frac_tt, frac_qcd, frac_w,FFsys[k-32-1]);
              }
           }

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

           float uncorrected_pth=(myele+mytau+mymet).Pt();
           float pth=uncorrected_pth*fit_pthcorrection->Eval(uncorrected_pth);
           if (pth<0) pth=0.5;

           if (name.find("H_recoPTH_0_45") < 140 && !(pth>=0 && pth<45)) continue;
           if (name.find("H_recoPTH_45_80") < 140 && !(pth>=45 && pth<80)) continue;
           if (name.find("H_recoPTH_80_120") < 140 && !(pth>=80 && pth<120)) continue;
           if (name.find("H_recoPTH_120_200") < 140 && !(pth>=120 && pth<200)) continue;
           if (name.find("H_recoPTH_200_350") < 140 && !(pth>=200 && pth<350)) continue;
           if (name.find("H_recoPTH_350_450") < 140 && !(pth>=350 && pth<450)) continue;
           if (name.find("H_recoPTH_GT450") < 140 && !(pth>=450)) continue;
           if (name.find("H_recoNJ_0") < 140 && !(numberJets==0)) continue;
           if (name.find("H_recoNJ_1") < 140 && !(numberJets==1)) continue;
           if (name.find("H_recoNJ_2") < 140 && !(numberJets==2)) continue;
           if (name.find("H_recoNJ_3") < 140 && !(numberJets==3)) continue;
           if (name.find("H_recoNJ_GE4") < 140 && !(numberJets>=4)) continue;
           if (name.find("H_recoJ1PT_30_60") < 140 && !(leadingJetPt>=30 && leadingJetPt<60)) continue;
           if (name.find("H_recoJ1PT_60_120") < 140 && !(leadingJetPt>=60 && leadingJetPt<120)) continue;
           if (name.find("H_recoJ1PT_120_200") < 140 && !(leadingJetPt>=120 && leadingJetPt<200)) continue;
           if (name.find("H_recoJ1PT_200_350") < 140 && !(leadingJetPt>=200 && leadingJetPt<350)) continue;
           if (name.find("H_recoJ1PT_GT350") < 140 && !(leadingJetPt>=350)) continue;


    	   mt=TMass_F(myele.Pt(),mymet.Pt(),myele.Px(),mymet.Px(),myele.Py(),mymet.Py());
	   myvar=mtt;
	   float myvar0=mytau.Pt();
	   float myvar1=(myele+mytau+mymet).Pt();
	   float myvar2=massJets;
           float myvar3=myvar0;
           float myvar4=myvar0;
           float myvar5=myvar1;
           float myvar6=myvar1;
           float myvar7=myvar2;
           float myvar8=myvar2;

           float mass0=myvar;
           float mass1=myvar;
           float mass2=myvar;
           float mass3=myvar;
           float mass4=myvar;
           float mass5=myvar;
           float mass6=myvar;
           float mass7=myvar;
           float mass8=myvar;

	   if (do_differential){
              myvar0=pth;
              myvar1=pth;
              myvar2=pth;
              myvar3=numberJets;
              myvar4=numberJets;
              myvar5=numberJets;
              myvar6=leadingJetPt;
              myvar7=leadingJetPt;
              myvar8=leadingJetPt;
              if (numberJets==0){
                myvar6=10.;
                myvar7=10.;
                myvar8=10.;
              }
	   }
           if (do_control_plots>0){
                myvar0=1;myvar1=1;myvar2=1;myvar3=1;myvar4=1;myvar5=1;myvar6=1;myvar7=1;myvar8=1;
           }
           if (do_control_plots==1){
              mass0=myele.Pt();
              mass1=mytau.Pt();
              mass2=mymet.Pt();
              mass3=(myele+mytau+mymet).Pt();
              mass4=(myele+mytau).M();
              mass5=m_sv;
              mass6=njets;
              mass7=myele.Eta();
              mass8=mytau.Eta();
           }
           if (do_control_plots==2){
              mass0=mt;
              if (numberJets<2) mass1=-1;
              else mass1=mjj;
              mass2=iso_1;
              if (numberJets<1) mass3=-1;
              else mass3=leadingJetPt;
              if (numberJets<1) mass4=-10;
              else mass4=jeta_1;
              if (numberJets<2) mass5=-1;
              else mass5=jpt_2;
              if (numberJets<2) mass6=-10;
              else mass6=jeta_2;
              if (numberJets<2) mass7=-10;
              else mass7=fabs(jeta_1-jeta_2);
              mass8=myele.DeltaR(mytau);
           }

	   if (k==0 && q_1*q_2<0 && mt<50 && signalRegion){ 
	     h_fiducial->Fill(is_fiducial);
	     h_energy_ele->Fill(myele.E());
             h_energy_tau->Fill(mytau.E());
	     h_taupt_vs_hpt->Fill(mytau.Pt(),1.05*(myele+mytau+mymet).Pt(),aweight*weight2);
 	     h_pth_resolution->Fill(Rivet_higgsPt,(myele+mytau+mymet).Pt());
	     if (Rivet_higgsPt<80) h_pth_resolution_0_80->Fill((Rivet_higgsPt-(myele+mytau+mymet).Pt())/(myele+mytau+mymet).Pt());
             else if (Rivet_higgsPt<200) h_pth_resolution_80_200->Fill((Rivet_higgsPt-(myele+mytau+mymet).Pt())/(myele+mytau+mymet).Pt());
             else h_pth_resolution_gt200->Fill((Rivet_higgsPt-(myele+mytau+mymet).Pt())/(myele+mytau+mymet).Pt());
	     if (Rivet_higgsPt>=0 && Rivet_higgsPt<45) h_pth_resolution_0_45->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
             if (Rivet_higgsPt>=45 && Rivet_higgsPt<80) h_pth_resolution_45_80->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
             if (Rivet_higgsPt>=80 && Rivet_higgsPt<120) h_pth_resolution_80_120->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
             if (Rivet_higgsPt>=120 && Rivet_higgsPt<200) h_pth_resolution_120_200->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
             if (Rivet_higgsPt>=200 && Rivet_higgsPt<350) h_pth_resolution_200_350->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
             if (Rivet_higgsPt>=350) h_pth_resolution_gt350->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());

	     if (mytau.Pt()>=30 && mytau.Pt()<50){
                if (Rivet_higgsPt>=0 && Rivet_higgsPt<45) h_pth_resolution_0_45_pt30to50->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=45 && Rivet_higgsPt<80) h_pth_resolution_45_80_pt30to50->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=80 && Rivet_higgsPt<120) h_pth_resolution_80_120_pt30to50->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=120 && Rivet_higgsPt<200) h_pth_resolution_120_200_pt30to50->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=200 && Rivet_higgsPt<350) h_pth_resolution_200_350_pt30to50->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=350) h_pth_resolution_gt350_pt30to50->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
	     }

             if (mytau.Pt()>=50 && mytau.Pt()<70){
                if (Rivet_higgsPt>=0 && Rivet_higgsPt<45) h_pth_resolution_0_45_pt50to70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=45 && Rivet_higgsPt<80) h_pth_resolution_45_80_pt50to70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=80 && Rivet_higgsPt<120) h_pth_resolution_80_120_pt50to70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=120 && Rivet_higgsPt<200) h_pth_resolution_120_200_pt50to70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=200 && Rivet_higgsPt<350) h_pth_resolution_200_350_pt50to70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=350) h_pth_resolution_gt350_pt50to70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
             }

             if (mytau.Pt()>=70){
                if (Rivet_higgsPt>=0 && Rivet_higgsPt<45) h_pth_resolution_0_45_ptgt70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=45 && Rivet_higgsPt<80) h_pth_resolution_45_80_ptgt70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=80 && Rivet_higgsPt<120) h_pth_resolution_80_120_ptgt70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=120 && Rivet_higgsPt<200) h_pth_resolution_120_200_ptgt70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=200 && Rivet_higgsPt<350) h_pth_resolution_200_350_ptgt70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
                if (Rivet_higgsPt>=350) h_pth_resolution_gt350_ptgt70->Fill(Rivet_higgsPt/(myele+mytau+mymet).Pt());
             }

	   }

           if (k==0 && mytau.Pt()>=30 && mt<50 && q_1*q_2<0){ // fractions
              if ((sample=="data_obs" or (sample=="embedded" or isT or isL)) && antiisoRegion){
                  if ((myele+mytau+mymet).Pt()>=0 && (myele+mytau+mymet).Pt()<45) f0real->Fill(mass0,aweight*weight2);
                  if ((myele+mytau+mymet).Pt()>=45 && (myele+mytau+mymet).Pt()<80) f1real->Fill(mass0,aweight*weight2);
                  if ((myele+mytau+mymet).Pt()>=80 && (myele+mytau+mymet).Pt()<120) f2real->Fill(mass0,aweight*weight2);
                  if ((myele+mytau+mymet).Pt()>=120 && (myele+mytau+mymet).Pt()<200) f3real->Fill(mass0,aweight*weight2);
                  if ((myele+mytau+mymet).Pt()>=200) f4real->Fill(mass0,aweight*weight2);
              }
              if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion){
                  if ((myele+mytau+mymet).Pt()>=0 && (myele+mytau+mymet).Pt()<45) f0jet->Fill(mass0,aweight*weight2);
                  if ((myele+mytau+mymet).Pt()>=45 && (myele+mytau+mymet).Pt()<80) f1jet->Fill(mass0,aweight*weight2);
                  if ((myele+mytau+mymet).Pt()>=80 && (myele+mytau+mymet).Pt()<120) f2jet->Fill(mass0,aweight*weight2);
                  if ((myele+mytau+mymet).Pt()>=120 && (myele+mytau+mymet).Pt()<200) f3jet->Fill(mass0,aweight*weight2);
                  if ((myele+mytau+mymet).Pt()>=200) f4jet->Fill(mass0,aweight*weight2);
              }
           }

if (FF!=FF) FF=0.0;

	   
	   bool category_0=false;
	   if (!do_differential && do_control_plots==0 && numberJets==0 && myele.DeltaR(mytau)>2.0 && mt<50) category_0=true;
	   if (!do_differential && do_control_plots==1 && mt<50) category_0=true;
           if (!do_differential && do_control_plots==2) category_0=true;
	   if (do_differential && mytau.Pt()>=30 && mytau.Pt()<50 && mt<50) category_0=true;
           if (category_0 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h0_ttcontamination->Fill(myvar0,mass0,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion){
                   h0tau_OS[k]->Fill(myvar0,mass0,aweight*weight2);
	       }
               if ((sample!="data_obs" && isL) && signalRegion)
                   h0ell_OS[k]->Fill(myvar0,mass0,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h0jet_OS[k]->Fill(myvar0,mass0,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h0tau_AI[k]->Fill(myvar0,mass0,FF);
                   h0jet_AI[k]->Fill(myvar0,mass0);
	       }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h0tau_AI[k]->Fill(myvar0,mass0,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h0ell_AI[k]->Fill(myvar0,mass0,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h0jet_AI[k]->Fill(myvar0,mass0,aweight*weight2);

           }

           bool category_1=false;
           if (!do_differential && do_control_plots==0 && numberJets==1 && mt<50) category_1=true;
           if (!do_differential && do_control_plots>=1 && mt<50) category_1=true;
           if (do_differential && mytau.Pt()>=50 && mytau.Pt()<70 && mt<50) category_1=true;
           if (category_1 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h1_ttcontamination->Fill(myvar1,mass1,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h1tau_OS[k]->Fill(myvar1,mass1,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h1ell_OS[k]->Fill(myvar1,mass1,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h1jet_OS[k]->Fill(myvar1,mass1,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h1tau_AI[k]->Fill(myvar1,mass1,FF);
                   h1jet_AI[k]->Fill(myvar1,mass1);
	       }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h1tau_AI[k]->Fill(myvar1,mass1,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h1ell_AI[k]->Fill(myvar1,mass1,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h1jet_AI[k]->Fill(myvar1,mass1,aweight*weight2);

           }

           bool category_2=false;
           if (!do_differential && do_control_plots==0 && numberJets>1 && mt<50) category_2=true;
           if (!do_differential && do_control_plots>=1 && mt<50) category_2=true;
           if (do_differential && mytau.Pt()>=70 && mt<50) category_2=true;
           if (category_2 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h2_ttcontamination->Fill(myvar2,mass2,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h2tau_OS[k]->Fill(myvar2,mass2,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h2ell_OS[k]->Fill(myvar2,mass2,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h2jet_OS[k]->Fill(myvar2,mass2,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h2tau_AI[k]->Fill(myvar2,mass2,FF);
                   h2jet_AI[k]->Fill(myvar2,mass2);
	       }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h2tau_AI[k]->Fill(myvar2,mass2,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h2ell_AI[k]->Fill(myvar2,mass2,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h2jet_AI[k]->Fill(myvar2,mass2,aweight*weight2);

           }

           bool category_3=false;
           if (!do_differential && do_control_plots==0 && numberJets==0 && myele.DeltaR(mytau)>3 && mt<50) category_3=true;
           if (!do_differential && do_control_plots>=1 && mt<50) category_3=true;
           if (do_differential && mytau.Pt()>=30 && mytau.Pt()<50 && mt<50) category_3=true;
           if (category_3 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h3_ttcontamination->Fill(myvar3,mass3,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h3tau_OS[k]->Fill(myvar3,mass3,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h3ell_OS[k]->Fill(myvar3,mass3,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h3jet_OS[k]->Fill(myvar3,mass3,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h3tau_AI[k]->Fill(myvar3,mass3,FF);
                   h3jet_AI[k]->Fill(myvar3,mass3);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h3tau_AI[k]->Fill(myvar3,mass3,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h3ell_AI[k]->Fill(myvar3,mass3,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h3jet_AI[k]->Fill(myvar3,mass3,aweight*weight2);

           }

           bool category_4=false;
           if (!do_differential && do_control_plots==0 && numberJets==0 && myele.DeltaR(mytau)>2.0 && myele.DeltaR(mytau)<=3.0 && mt<50) category_4=true;
           if (!do_differential && do_control_plots>=1 && mt<50) category_4=true;
           if (do_differential && mytau.Pt()>=50 && mytau.Pt()<70 && mt<50) category_4=true;
           if (category_4 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h4_ttcontamination->Fill(myvar4,mass4,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h4tau_OS[k]->Fill(myvar4,mass4,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h4ell_OS[k]->Fill(myvar4,mass4,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h4jet_OS[k]->Fill(myvar4,mass4,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h4tau_AI[k]->Fill(myvar4,mass4,FF);
                   h4jet_AI[k]->Fill(myvar4,mass4);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h4tau_AI[k]->Fill(myvar4,mass4,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h4ell_AI[k]->Fill(myvar4,mass4,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h4jet_AI[k]->Fill(myvar4,mass4,aweight*weight2);

           }

           bool category_5=false;
           if (!do_differential && do_control_plots==0 && numberJets==1 && mt<50) category_5=true;
           if (!do_differential && do_control_plots>=1 && mt<50) category_5=true;
           if (do_differential && mytau.Pt()>=70 && mt<50) category_5=true;
           if (category_5 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h5_ttcontamination->Fill(myvar5,mass5,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h5tau_OS[k]->Fill(myvar5,mass5,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h5ell_OS[k]->Fill(myvar5,mass5,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h5jet_OS[k]->Fill(myvar5,mass5,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h5tau_AI[k]->Fill(myvar5,mass5,FF);
                   h5jet_AI[k]->Fill(myvar5,mass5);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion){
                   h5tau_AI[k]->Fill(myvar5,mass5,aweight*weight2*FF);
	       }
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h5ell_AI[k]->Fill(myvar5,mass5,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h5jet_AI[k]->Fill(myvar5,mass5,aweight*weight2);

           }

           bool category_6=false;
           if (!do_differential && do_control_plots==0 && numberJets>1 && massJets<350 && mt<50) category_6=true;
           if (!do_differential && do_control_plots>=1 && mt<50) category_6=true;
           if (do_differential && mytau.Pt()>=30 && mytau.Pt()<50 && mt<50) category_6=true;
           if (category_6 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h6_ttcontamination->Fill(myvar6,mass6,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h6tau_OS[k]->Fill(myvar6,mass6,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h6ell_OS[k]->Fill(myvar6,mass6,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h6jet_OS[k]->Fill(myvar6,mass6,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h6tau_AI[k]->Fill(myvar6,mass6,FF);
                   h6jet_AI[k]->Fill(myvar6,mass6);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h6tau_AI[k]->Fill(myvar6,mass6,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h6ell_AI[k]->Fill(myvar6,mass6,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h6jet_AI[k]->Fill(myvar6,mass6,aweight*weight2);

           }

           bool category_7=false;
           if (!do_differential && do_control_plots==0 && numberJets>=2 && massJets>=350 && (myele+mytau+mymet).Pt()<200 && mt<50) category_7=true;
           if (!do_differential && do_control_plots>=1 && mt<50) category_7=true;
           if (do_differential && mytau.Pt()>=50 && mytau.Pt()<70 && mt<50) category_7=true;
           if (category_7 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h7_ttcontamination->Fill(myvar7,mass7,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h7tau_OS[k]->Fill(myvar7,mass7,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h7ell_OS[k]->Fill(myvar7,mass7,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h7jet_OS[k]->Fill(myvar7,mass7,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h7tau_AI[k]->Fill(myvar7,mass7,FF);
                   h7jet_AI[k]->Fill(myvar7,mass7);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h7tau_AI[k]->Fill(myvar7,mass7,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h7ell_AI[k]->Fill(myvar7,mass7,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h7jet_AI[k]->Fill(myvar7,mass7,aweight*weight2);

           }

           bool category_8=false;
           if (!do_differential && do_control_plots==0 && numberJets>=2 && massJets>=350 && (myele+mytau+mymet).Pt()>=200 && mt<50) category_8=true;
           if (!do_differential && do_control_plots>=1 && mt<50) category_8=true;
           if (do_differential && mytau.Pt()>=70 && mt<50) category_8=true;
           if (category_8 && q_1*q_2<0){
               if (k==0 && is_includedInEmbedded && signalRegion)
                   h8_ttcontamination->Fill(myvar8,mass8,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h8tau_OS[k]->Fill(myvar8,mass8,aweight*weight2);
               if ((sample!="data_obs" && isL) && signalRegion)
                   h8ell_OS[k]->Fill(myvar8,mass8,aweight*weight2);
               if ((sample!="data_obs" && gen_match_2==6) && signalRegion)
                   h8jet_OS[k]->Fill(myvar8,mass8,aweight*weight2);
               if (antiisoRegion && sample=="data_obs"){
                   h8tau_AI[k]->Fill(myvar8,mass8,FF);
                   h8jet_AI[k]->Fill(myvar8,mass8);
               }
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h8tau_AI[k]->Fill(myvar8,mass8,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h8ell_AI[k]->Fill(myvar8,mass8,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h8jet_AI[k]->Fill(myvar8,mass8,aweight*weight2);


           }
	} // end of loop over nbhist

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    h_fiducial->Write();
    h_energy_ele->Write();
    h_energy_tau->Write();

    h_taupt_vs_hpt->Write();

    h_pth_resolution->Write();

    h_pth_resolution_0_80->Write();
    h_pth_resolution_80_200->Write();
    h_pth_resolution_gt200->Write();

    h_pth_resolution_0_45->Write();
    h_pth_resolution_45_80->Write();
    h_pth_resolution_80_120->Write();
    h_pth_resolution_120_200->Write();
    h_pth_resolution_200_350->Write();
    h_pth_resolution_gt350->Write();

    h_pth_resolution_0_45_pt30to50->Write();
    h_pth_resolution_45_80_pt30to50->Write();
    h_pth_resolution_80_120_pt30to50->Write();
    h_pth_resolution_120_200_pt30to50->Write();
    h_pth_resolution_200_350_pt30to50->Write();
    h_pth_resolution_gt350_pt30to50->Write();

    h_pth_resolution_0_45_pt50to70->Write();
    h_pth_resolution_45_80_pt50to70->Write();
    h_pth_resolution_80_120_pt50to70->Write();
    h_pth_resolution_120_200_pt50to70->Write();
    h_pth_resolution_200_350_pt50to70->Write();
    h_pth_resolution_gt350_pt50to70->Write();

    h_pth_resolution_0_45_ptgt70->Write();
    h_pth_resolution_45_80_ptgt70->Write();
    h_pth_resolution_80_120_ptgt70->Write();
    h_pth_resolution_120_200_ptgt70->Write();
    h_pth_resolution_200_350_ptgt70->Write();
    h_pth_resolution_gt350_ptgt70->Write();


cout<<h0tau_OS[0]->Integral()<<" "<<h5tau_OS[0]->Integral()<<" "<<h6tau_OS[0]->Integral()<<" "<<h7tau_OS[0]->Integral()<<" "<<h8tau_OS[0]->Integral()<<" "<<endl;
    if (sample!="data_obs"){
       EmptyBins(h0tau_OS[0]); EmptyBins(h0ell_OS[0]); EmptyBins(h0jet_OS[0]); EmptyBins(h0tau_AI[0]); EmptyBins(h0ell_AI[0]); EmptyBins(h0jet_AI[0]);
       EmptyBins(h1tau_OS[0]); EmptyBins(h1ell_OS[0]); EmptyBins(h1jet_OS[0]); EmptyBins(h1tau_AI[0]); EmptyBins(h1ell_AI[0]); EmptyBins(h1jet_AI[0]);
       EmptyBins(h2tau_OS[0]); EmptyBins(h2ell_OS[0]); EmptyBins(h2jet_OS[0]); EmptyBins(h2tau_AI[0]); EmptyBins(h2ell_AI[0]); EmptyBins(h2jet_AI[0]);
       EmptyBins(h3tau_OS[0]); EmptyBins(h3ell_OS[0]); EmptyBins(h3jet_OS[0]); EmptyBins(h3tau_AI[0]); EmptyBins(h3ell_AI[0]); EmptyBins(h3jet_AI[0]);
       EmptyBins(h4tau_OS[0]); EmptyBins(h4ell_OS[0]); EmptyBins(h4jet_OS[0]); EmptyBins(h4tau_AI[0]); EmptyBins(h4ell_AI[0]); EmptyBins(h4jet_AI[0]);
       EmptyBins(h5tau_OS[0]); EmptyBins(h5ell_OS[0]); EmptyBins(h5jet_OS[0]); EmptyBins(h5tau_AI[0]); EmptyBins(h5ell_AI[0]); EmptyBins(h5jet_AI[0]);
       EmptyBins(h6tau_OS[0]); EmptyBins(h6ell_OS[0]); EmptyBins(h6jet_OS[0]); EmptyBins(h6tau_AI[0]); EmptyBins(h6ell_AI[0]); EmptyBins(h6jet_AI[0]);
       EmptyBins(h7tau_OS[0]); EmptyBins(h7ell_OS[0]); EmptyBins(h7jet_OS[0]); EmptyBins(h7tau_AI[0]); EmptyBins(h7ell_AI[0]); EmptyBins(h7jet_AI[0]);
       EmptyBins(h8tau_OS[0]); EmptyBins(h8ell_OS[0]); EmptyBins(h8jet_OS[0]); EmptyBins(h8tau_AI[0]); EmptyBins(h8ell_AI[0]); EmptyBins(h8jet_AI[0]);
    }

    f0real->Write();
    f0jet->Write();
    f1real->Write();
    f1jet->Write();
    f2real->Write();
    f2jet->Write();
    f3real->Write();
    f3jet->Write();
    f4real->Write();
    f4jet->Write();

    TString postfix=postfixFF[0];

    TDirectory *OS0jet =fout->mkdir("et_0jet");
    OS0jet->cd();
    h0_ttcontamination->SetName("ttcontamination");
    h0_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
cout<<k<<" "<<postfix<<endl;
       if (name!="embedded" && name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
          h0tau_OS[k]->SetName(name+"T"+postfix);
          h0ell_OS[k]->SetName(name+"L"+postfix);
          h0jet_OS[k]->SetName(name+"J"+postfix);
          h0tau_OS[k]->Write();
          h0ell_OS[k]->Write();
          h0jet_OS[k]->Write();
       }
       else{
          h0tau_OS[k]->SetName(name.c_str()+postfix);
          h0tau_OS[k]->Add(h0ell_OS[k]);
          h0tau_OS[k]->Add(h0jet_OS[k]);
          h0tau_OS[k]->Write();
       }
    }
    TDirectory *AI0jet =fout->mkdir("AI0jet");
    AI0jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h0tau_AI[k]->SetName(name+"T"+postfix);
          h0ell_AI[k]->SetName(name+"L"+postfix);
          h0jet_AI[k]->SetName(name+"J"+postfix);
          h0tau_AI[k]->Write();
          h0ell_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
       else {
          h0tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h0jet_AI[k]->SetName("data_obs"+postfix);
          h0tau_AI[k]->Write();
          h0jet_AI[k]->Write();
       }
    }

    TDirectory *OS1jet =fout->mkdir("et_boosted");
    OS1jet->cd();
    h1_ttcontamination->SetName("ttcontamination");
    h1_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
          h1tau_OS[k]->SetName(name+"T"+postfix);
          h1ell_OS[k]->SetName(name+"L"+postfix);
          h1jet_OS[k]->SetName(name+"J"+postfix);
          h1tau_OS[k]->Write();
          h1ell_OS[k]->Write();
          h1jet_OS[k]->Write();
       }
       else{
          h1tau_OS[k]->SetName(name.c_str()+postfix);
          h1tau_OS[k]->Add(h1ell_OS[k]);
          h1tau_OS[k]->Add(h1jet_OS[k]);
          h1tau_OS[k]->Write();
       }
    }

    TDirectory *AI1jet =fout->mkdir("AIboosted");
    AI1jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h1tau_AI[k]->SetName(name+"T"+postfix);
          h1ell_AI[k]->SetName(name+"L"+postfix);
          h1jet_AI[k]->SetName(name+"J"+postfix);
          h1tau_AI[k]->Write();
          h1ell_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
       else {
          h1tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h1jet_AI[k]->SetName("data_obs"+postfix);
          h1tau_AI[k]->Write();
          h1jet_AI[k]->Write();
       }
    }

    TDirectory *OS2jet =fout->mkdir("et_vbf");
    OS2jet->cd();
    h2_ttcontamination->SetName("ttcontamination");
    h2_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
          h2tau_OS[k]->SetName(name+"T"+postfix);
          h2ell_OS[k]->SetName(name+"L"+postfix);
          h2jet_OS[k]->SetName(name+"J"+postfix);
          h2tau_OS[k]->Write();
          h2ell_OS[k]->Write();
          h2jet_OS[k]->Write();
       }
       else{
          h2tau_OS[k]->SetName(name.c_str()+postfix);
          h2tau_OS[k]->Add(h2ell_OS[k]);
          h2tau_OS[k]->Add(h2jet_OS[k]);
          h2tau_OS[k]->Write();
       }
    }

    TDirectory *AI2jet =fout->mkdir("AIvbf");
    AI2jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h2tau_AI[k]->SetName(name+"T"+postfix);
          h2ell_AI[k]->SetName(name+"L"+postfix);
          h2jet_AI[k]->SetName(name+"J"+postfix);
          h2tau_AI[k]->Write();
          h2ell_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
       else {
          h2tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h2jet_AI[k]->SetName("data_obs"+postfix);
          h2tau_AI[k]->Write();
          h2jet_AI[k]->Write();
       }
    }

    TDirectory *OS3jet =fout->mkdir("et_0jetlow");
    OS3jet->cd();
    h3_ttcontamination->SetName("ttcontamination");
    h3_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
          h3tau_OS[k]->SetName(name+"T"+postfix);
          h3ell_OS[k]->SetName(name+"L"+postfix);
          h3jet_OS[k]->SetName(name+"J"+postfix);
          h3tau_OS[k]->Write();
          h3ell_OS[k]->Write();
          h3jet_OS[k]->Write();
       }
       else{
          h3tau_OS[k]->SetName(name.c_str()+postfix);
          h3tau_OS[k]->Add(h3ell_OS[k]);
          h3tau_OS[k]->Add(h3jet_OS[k]);
          h3tau_OS[k]->Write();
       }
    }

    TDirectory *AI3jet =fout->mkdir("AI0jetlow");
    AI3jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h3tau_AI[k]->SetName(name+"T"+postfix);
          h3ell_AI[k]->SetName(name+"L"+postfix);
          h3jet_AI[k]->SetName(name+"J"+postfix);
          h3tau_AI[k]->Write();
          h3ell_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
       else {
          h3tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h3jet_AI[k]->SetName("data_obs"+postfix);
          h3tau_AI[k]->Write();
          h3jet_AI[k]->Write();
       }
    }

    TDirectory *OS4jet =fout->mkdir("et_0jethigh");
    OS4jet->cd();
    h4_ttcontamination->SetName("ttcontamination");
    h4_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
          h4tau_OS[k]->SetName(name+"T"+postfix);
          h4ell_OS[k]->SetName(name+"L"+postfix);
          h4jet_OS[k]->SetName(name+"J"+postfix);
          h4tau_OS[k]->Write();
          h4ell_OS[k]->Write();
          h4jet_OS[k]->Write();
       }
       else{
          h4tau_OS[k]->SetName(name.c_str()+postfix);
          h4tau_OS[k]->Add(h4ell_OS[k]);
          h4tau_OS[k]->Add(h4jet_OS[k]);
          h4tau_OS[k]->Write();
       }
    }

    TDirectory *AI4jet =fout->mkdir("AI0jethigh");
    AI4jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h4tau_AI[k]->SetName(name+"T"+postfix);
          h4ell_AI[k]->SetName(name+"L"+postfix);
          h4jet_AI[k]->SetName(name+"J"+postfix);
          h4tau_AI[k]->Write();
          h4ell_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
       else {
          h4tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h4jet_AI[k]->SetName("data_obs"+postfix);
          h4tau_AI[k]->Write();
          h4jet_AI[k]->Write();
       }
    }

    TDirectory *OS5jet =fout->mkdir("et_boosted1");
    OS5jet->cd();
    h5_ttcontamination->SetName("ttcontamination");
    h5_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
          h5tau_OS[k]->SetName(name+"T"+postfix);
          h5ell_OS[k]->SetName(name+"L"+postfix);
          h5jet_OS[k]->SetName(name+"J"+postfix);
          h5tau_OS[k]->Write();
          h5ell_OS[k]->Write();
          h5jet_OS[k]->Write();
       }
       else{
          h5tau_OS[k]->SetName(name.c_str()+postfix);
          h5tau_OS[k]->Add(h5ell_OS[k]);
          h5tau_OS[k]->Add(h5jet_OS[k]);
          h5tau_OS[k]->Write();
       }
    }

    TDirectory *AI5jet =fout->mkdir("AIboosted1");
    AI5jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h5tau_AI[k]->SetName(name+"T"+postfix);
          h5ell_AI[k]->SetName(name+"L"+postfix);
          h5jet_AI[k]->SetName(name+"J"+postfix);
          h5tau_AI[k]->Write();
          h5ell_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
       else {
          h5tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h5jet_AI[k]->SetName("data_obs"+postfix);
          h5tau_AI[k]->Write();
          h5jet_AI[k]->Write();
       }
    }

    TDirectory *OS6jet =fout->mkdir("et_boosted2");
    OS6jet->cd();
    h6_ttcontamination->SetName("ttcontamination");
    h6_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
          h6tau_OS[k]->SetName(name+"T"+postfix);
          h6ell_OS[k]->SetName(name+"L"+postfix);
          h6jet_OS[k]->SetName(name+"J"+postfix);
          h6tau_OS[k]->Write();
          h6ell_OS[k]->Write();
          h6jet_OS[k]->Write();
       }
       else{
          h6tau_OS[k]->SetName(name.c_str()+postfix);
          h6tau_OS[k]->Add(h6ell_OS[k]);
          h6tau_OS[k]->Add(h6jet_OS[k]);
          h6tau_OS[k]->Write();
       }
    }

    TDirectory *AI6jet =fout->mkdir("AIboosted2");
    AI6jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h6tau_AI[k]->SetName(name+"T"+postfix);
          h6ell_AI[k]->SetName(name+"L"+postfix);
          h6jet_AI[k]->SetName(name+"J"+postfix);
          h6tau_AI[k]->Write();
          h6ell_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
       else {
          h6tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h6jet_AI[k]->SetName("data_obs"+postfix);
          h6tau_AI[k]->Write();
          h6jet_AI[k]->Write();
       }
    }

    TDirectory *OS7jet =fout->mkdir("et_vbflow");
    OS7jet->cd();
    h7_ttcontamination->SetName("ttcontamination");
    h7_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
          h7tau_OS[k]->SetName(name+"T"+postfix);
          h7ell_OS[k]->SetName(name+"L"+postfix);
          h7jet_OS[k]->SetName(name+"J"+postfix);
          h7tau_OS[k]->Write();
          h7ell_OS[k]->Write();
          h7jet_OS[k]->Write();
       }
       else{
          h7tau_OS[k]->SetName(name.c_str()+postfix);
          h7tau_OS[k]->Add(h7ell_OS[k]);
          h7tau_OS[k]->Add(h7jet_OS[k]);
          h7tau_OS[k]->Write();
       }
    }

    TDirectory *AI7jet =fout->mkdir("AIvbflow");
    AI7jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h7tau_AI[k]->SetName(name+"T"+postfix);
          h7ell_AI[k]->SetName(name+"L"+postfix);
          h7jet_AI[k]->SetName(name+"J"+postfix);
          h7tau_AI[k]->Write();
          h7ell_AI[k]->Write();
          h7jet_AI[k]->Write();
       }
       else {
          h7tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h7jet_AI[k]->SetName("data_obs"+postfix);
          h7tau_AI[k]->Write();
          h7jet_AI[k]->Write();
       }
    }

    TDirectory *OS8jet =fout->mkdir("et_vbfhigh");
    OS8jet->cd();
    h8_ttcontamination->SetName("ttcontamination");
    h8_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs" && k>0 ) continue;
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs" and name.find("125")>140  and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
          h8tau_OS[k]->SetName(name+"T"+postfix);
          h8ell_OS[k]->SetName(name+"L"+postfix);
          h8jet_OS[k]->SetName(name+"J"+postfix);
          h8tau_OS[k]->Write();
          h8ell_OS[k]->Write();
          h8jet_OS[k]->Write();
       }
       else{
          h8tau_OS[k]->SetName(name.c_str()+postfix);
          h8tau_OS[k]->Add(h8ell_OS[k]);
          h8tau_OS[k]->Add(h8jet_OS[k]);
          h8tau_OS[k]->Write();
       }
    }

    TDirectory *AI8jet =fout->mkdir("AIvbfhigh");
    AI8jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (sample=="data_obs") postfix=postfixFF[k];
       else if (sample!="data_obs" and name!="embedded" and !is_higgs and k>82) postfix=postfixFF[k-82];
       else if (is_higgs and k>82) postfix=postfixTheo[k-82];
       else if ((name=="embedded") and k>32) postfix=postfixFF[k-32];
       else if (name=="embedded" and k<33) postfix=postfixEmbedded[k];
       else postfix=postfixMC[k];
       if (name!="embedded" && name!="data_obs"){
          h8tau_AI[k]->SetName(name+"T"+postfix);
          h8ell_AI[k]->SetName(name+"L"+postfix);
          h8jet_AI[k]->SetName(name+"J"+postfix);
          h8tau_AI[k]->Write();
          h8ell_AI[k]->Write();
          h8jet_AI[k]->Write();
       }
       else {
          h8tau_AI[k]->SetName("reweighted_data_obs"+postfix);
          h8jet_AI[k]->SetName("data_obs"+postfix);
          h8tau_AI[k]->Write();
          h8jet_AI[k]->Write();
       }
    }

    cout<<h0tau_OS[0]->Integral()<<endl;
    fout->Close();
    delete wmc;
    delete w;
} 


