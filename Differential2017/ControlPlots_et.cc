#include <TH2.h>
#include "get_name_puhisto.h"
#include "btagSF.h"
#include "ApplyFF_lpt.h"
#include <TStyle.h>
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
#include "PostProcessing.h"
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

    int do_control_plots=1;
    bool do_differential=false;

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
    TTree *arbre = (TTree*) f_Double->Get("etau_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float ngen = nbevt->GetBinContent(2);

    float xs=1.0; float weight=1.0; float luminosity=41529.0;
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
    else if (sample=="qqH") {xs=3.770*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="ggH") {xs=48.30*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="qqH_htt125") {xs=3.770*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="WplusH125") {xs=0.8331*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="WminusH125") {xs=0.5272*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.7544*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="ttHTT") {xs=0.5033*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="ttHTT125") {xs=0.5033*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="ttHnonbb") {xs=0.5033*(1.0-0.5760); weight=luminosity*xs/ngen;}
    else if (sample=="ttHnonbb125") {xs=0.5033*(1.0-0.5760); weight=luminosity*xs/ngen;}
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
    else if (sample=="WGLNu") {xs=464.4; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWminus") {xs=23.24; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWplus") {xs=29.59; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZLL") {xs=4.321; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZNuNu") {xs=10.66; weight=luminosity*xs/ngen;}

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt);
    arbre->SetBranchAddress("Rivet_nJets30", &Rivet_nJets30);
    arbre->SetBranchAddress("Rivet_stage1_1_fine_cat_pTjet30GeV", & Rivet_stage1_1_fine_cat_pTjet30GeV);
    arbre->SetBranchAddress("Rivet_stage1_1_cat_pTjet30GeV", & Rivet_stage1_1_cat_pTjet30GeV);
    arbre->SetBranchAddress("Rivet_stage1_cat_pTjet30GeV", & Rivet_stage1_cat_pTjet30GeV);
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

    arbre->SetBranchAddress("passEle27", &passEle27);
    arbre->SetBranchAddress("passEle32", &passEle32);
    arbre->SetBranchAddress("passEle35", &passEle35);
    arbre->SetBranchAddress("passEle24Tau30", &passEle24Tau30);

    arbre->SetBranchAddress("matchEle27_1", &matchEle27_1);
    arbre->SetBranchAddress("matchEle32_1", &matchEle32_1);
    arbre->SetBranchAddress("matchEle35_1", &matchEle35_1);
    arbre->SetBranchAddress("matchEle24Tau30_1", &matchEle24Tau30_1);
    arbre->SetBranchAddress("matchEle24Tau30_2", &matchEle24Tau30_2);
    arbre->SetBranchAddress("filterEle27_1", &filterEle27_1);
    arbre->SetBranchAddress("filterEle32_1", &filterEle32_1);
    arbre->SetBranchAddress("filterEle35_1", &filterEle35_1);
    arbre->SetBranchAddress("filterEle24Tau30_1", &filterEle24Tau30_1);
    arbre->SetBranchAddress("filterEle24Tau30_2", &filterEle24Tau30_2);

    arbre->SetBranchAddress("HTTgenfinalstate", &HTTgenfinalstate);
    arbre->SetBranchAddress("gen_met_pt", &gen_met_pt);
    arbre->SetBranchAddress("gen_met_phi", &gen_met_phi);
    arbre->SetBranchAddress("gen_ele_pt", &gen_ele_pt);
    arbre->SetBranchAddress("gen_ele_eta", &gen_ele_eta);
    arbre->SetBranchAddress("gen_ele_phi", &gen_ele_phi);
    arbre->SetBranchAddress("gen_tauh_pt", &gen_tauh_pt);
    arbre->SetBranchAddress("gen_tauh_eta", &gen_tauh_eta);
    arbre->SetBranchAddress("gen_tauh_phi", &gen_tauh_phi);

    arbre->SetBranchAddress("genpt_1", &genpt_1);
    arbre->SetBranchAddress("geneta_1", &geneta_1);
    arbre->SetBranchAddress("genpt_2", &genpt_2);
    arbre->SetBranchAddress("geneta_2", &geneta_2);
    arbre->SetBranchAddress("bweight", &bweight);
    arbre->SetBranchAddress("nbtagL", &nbtagL);
    arbre->SetBranchAddress("prefiring_weight", &prefiring_weight);
    arbre->SetBranchAddress("prefiring_weight_up", &prefiring_weight_up);
    arbre->SetBranchAddress("prefiring_weight_down", &prefiring_weight_down);
    arbre->SetBranchAddress("lheweight_muR0p5_muF0p5", &lheweight_muR0p5_muF0p5);
    arbre->SetBranchAddress("lheweight_muR2_muF2", &lheweight_muR2_muF2);
    arbre->SetBranchAddress("lheweight_nominal", &lheweight_nominal);

    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("lumi", &lumi);
    arbre->SetBranchAddress("evt", &evt);
    arbre->SetBranchAddress("npv", &npv);
    arbre->SetBranchAddress("pt_1", &pt_1);
    arbre->SetBranchAddress("pt_1_ScaleUp", &pt_1_ScaleUp);
    arbre->SetBranchAddress("pt_1_ScaleDown", &pt_1_ScaleDown);
    arbre->SetBranchAddress("phi_1", &phi_1);
    arbre->SetBranchAddress("eta_1", &eta_1);
    arbre->SetBranchAddress("iso_1", &iso_1);
    arbre->SetBranchAddress("m_1", &m_1);
    arbre->SetBranchAddress("q_1", &q_1);
    arbre->SetBranchAddress("nbtag", &nbtag);
    arbre->SetBranchAddress("q_2", &q_2);
    arbre->SetBranchAddress("pt_2", &pt_2);
    arbre->SetBranchAddress("eta_2", &eta_2);
    arbre->SetBranchAddress("m_2", &m_2);
    arbre->SetBranchAddress("phi_2", &phi_2);

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

    arbre->SetBranchAddress("metphi", &metphi);
    arbre->SetBranchAddress("met", &met);
    arbre->SetBranchAddress("met_UESDown", &met_UESDown);
    arbre->SetBranchAddress("met_UESUp", &met_UESUp);
    arbre->SetBranchAddress("metphi_UESDown", &metphi_UESDown);
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
    arbre->SetBranchAddress("matchEmbFilter_Ele24Tau30_1",&matchEmbFilter_Ele24Tau30_1);
    arbre->SetBranchAddress("matchEmbFilter_Ele24Tau30_2",&matchEmbFilter_Ele24Tau30_2);

   bool is_higgs=((sample.find("ggH") < 140) or (sample.find("qqH") < 140) or (sample.find("ttH") < 140) or (sample.find("ZH") < 140) or (sample.find("WminusH") < 140) or (sample.find("WplusH") < 140) or (sample.find("ZH") < 140) or (name.find("OutsideAcceptance") < 140));
   int nbhist=1;

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

   // control 1
   float bins_mtt0[] = {25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100};
   float bins_mtt1[] = {30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80};
   float bins_mtt2[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
   float bins_mtt3[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250};
   float bins_mtt4[] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200};
   float bins_mtt5[] = {60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250};
   float bins_mtt6[] = {0.0,0.4,0.8,1.2,1.6,2.0,2.4,2.8,3.2,3.6,4.0};
   float bins_mtt7[] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2};
   float bins_mtt8[] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4,4.6,4.8,5.0,5.2,5.4,5.6,5.8,6.0};

   /*float bins_mtt0[] = {50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins_mtt1[] = {50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins_mtt2[] = {50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins_mtt3[] = {50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins_mtt4[] = {50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins_mtt5[] = {50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins_mtt6[] = {50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins_mtt7[] = {50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   float bins_mtt8[] = {50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};*/

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

   float bins_mjj[] = {0,100000};
   float bins_mjj_low[] = {0,100000};
   float bins_mjj_high[] = {0,100000};
   float bins_pth[] = {0,100000};
   float bins_pth_1[] = {0,100000};
   float bins_pth_2[] = {0,100000};
   float bins_taupt[] = {0,100000};
   float bins_taupt_low[] = {0,100000};
   float bins_taupt_high[] = {0,100000};

   int  binnum_mjj = sizeof(bins_mjj)/sizeof(Float_t) - 1;
   int  binnum_mjj_low = sizeof(bins_mjj_low)/sizeof(Float_t) - 1;
   int  binnum_mjj_high = sizeof(bins_mjj_high)/sizeof(Float_t) - 1;
   int  binnum_pth = sizeof(bins_pth)/sizeof(Float_t) - 1;
   int  binnum_pth_1 = sizeof(bins_pth_1)/sizeof(Float_t) - 1;
   int  binnum_pth_2 = sizeof(bins_pth_2)/sizeof(Float_t) - 1;
   int  binnum_taupt = sizeof(bins_taupt)/sizeof(Float_t) - 1;
   int  binnum_taupt_low = sizeof(bins_taupt_low)/sizeof(Float_t) - 1;
   int  binnum_taupt_high = sizeof(bins_taupt_high)/sizeof(Float_t) - 1;

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
   LumiWeights_12 = new reweight::LumiReWeighting("pu_distributions_mc_2017.root", "pu_distributions_data_2017.root",get_name_puhisto(input), "pileup");
cout<<get_name_puhisto(input)<<endl;


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

   TFile *ftauid = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2017ReReco.root");
   TF1 *fct_tauid= (TF1*) ftauid->Get("Medium_cent");
   TF1 *fct_tauid_up= (TF1*) ftauid->Get("Medium_up");
   TF1 *fct_tauid_down= (TF1*) ftauid->Get("Medium_down");

   TFile *ftauid_emb = new TFile("TauID_SF_pt_DeepTau2017v2p1VSjet_2017ReReco_EMB.root");
   TF1 *fct_tauid_emb= (TF1*) ftauid_emb->Get("Medium_cent");
   TF1 *fct_tauid_emb_up= (TF1*) ftauid_emb->Get("Medium_up");
   TF1 *fct_tauid_emb_down= (TF1*) ftauid_emb->Get("Medium_down");

   TFile fw("htt_scalefactors_legacy_2017.root");
   RooWorkspace *w = (RooWorkspace*)fw.Get("w");
   fw.Close();

   TFile fwmc("htt_scalefactors_legacy_2017.root");
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

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

lheweight_nominal=1.0;//

	if (fabs(eta_1)>2.1) continue;
        if (fabs(eta_2)>2.3) continue;

        int nbtag20=0;
        float bMpt_1=0;
        float bMflavor_1=0;
        float bMpt_2=0;
        float bMflavor_2=0;
        if (bpt_1>20 && bcsv_1>0.4941){
           bMpt_1=bpt_1;
           bMflavor_1=bflavor_1;
           nbtag20++;
        }
        if (bpt_2>20 && bcsv_2>0.4941){
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

        bool trigger32=(passEle32 && pt_1>27.5 && matchEle32_1 && filterEle32_1);
        bool trigger27=(passEle27 && pt_1>27.5 && matchEle27_1 && filterEle27_1);
        bool trigger2430=(passEle24Tau30 && matchEle24Tau30_1 && filterEle24Tau30_1 && matchEle24Tau30_2 && filterEle24Tau30_2 && pt_1>24.5 && pt_2>34.5 && pt_1<28.5 && fabs(eta_2)<2.1);
        /*if (sample=="embedded" && fabs(eta_1)<1.479) trigger2430=(passEle24Tau30 && pt_1>24.5 && pt_2>34.5 && pt_1<28.5 && fabs(eta_2)<2.1);
        if (sample=="embedded" && (fabs(eta_1)>1.479 && pt_1<40.5) && pt_1>27.5){ trigger32=true; trigger27=true;}
        if (sample=="embedded" && fabs(eta_1)>1.479 && pt_1>24.5 && pt_2>34.5 && pt_1<28.5 && fabs(eta_2)<2.1){ trigger2430=true;}
        if (sample=="embedded" && fabs(eta_1)>1.479 && pt_1<27.5){ trigger32=false; trigger27=false;}
	if (sample=="embedded" && fabs(eta_1)>1.479 && !(pt_1>24.5 && pt_2>34.5 && pt_1<28.5 && fabs(eta_2)<2.1)) { trigger2430=false;}*/
	if (sample=="embedded"){
	   if (fabs(eta_1)>1.479 && pt_1<40.5){
		trigger2430=(pt_1>24.5 && pt_2>34.5 && pt_1<28.5 && fabs(eta_2)<2.1);
		trigger27=(pt_1>27.5);
		trigger32=(pt_1>27.5);
	   }
	   else{
//cout<<(matchEmbFilter_Ele24Tau30_1 && matchEmbFilter_Ele24Tau30_2)<<" "<<passEle24Tau30<<endl;
                //trigger2430=(matchEmbFilter_Ele24Tau30_1 && matchEmbFilter_Ele24Tau30_2 && pt_1>24.5 && pt_2>34.5 && pt_1<28.5 && fabs(eta_2)<2.1);
                trigger2430=(passEle24Tau30 && pt_1>24.5 && pt_2>34.5 && pt_1<28.5 && fabs(eta_2)<2.1);
                trigger27=(passEle27 && pt_1>27.5 && matchEle27_1 && filterEle27_1);
                trigger32=(passEle32 && pt_1>27.5 && matchEle32_1 && filterEle32_1);
	   }
	}
        if (!trigger27 && !trigger32 && !trigger2430) continue;


        if (!byTightDeepVSe_2 or !byVLooseDeepVSmu_2) continue;
	if (iso_1>0.15) continue;
        float signalRegion=(byMediumDeepVSjet_2 && iso_1<0.15);
        float antiisoRegion=(byVVVLooseDeepVSjet_2 && !byMediumDeepVSjet_2 && iso_1<0.15);

	// Define leptons
	TLorentzVector mytau; 
	mytau.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);
	if (myele.DeltaR(mytau)<0.5) continue;

	// Stitching for W and DY
        if (sample=="W"){
            weight=23.8336;
            if (numGenJets==1) weight=3.1468;
            else if (numGenJets==2) weight=4.087;
            else if (numGenJets==3) weight=2.253;
            else if (numGenJets==4) weight=2.1954;
        }
        if (sample=="DY" or sample=="Z"){
            weight=2.59218;
	    //if (njets>0 && numGenJets==0) continue;
            if (numGenJets==1) weight=0.71088;
            else if (numGenJets==2) weight=0.92260;
            else if (numGenJets==3) weight=1.65556;
            else if (numGenJets==4) weight=0.21943;
        }

	if (sample=="embedded" && gen_match_2==6) continue;
        if (sample=="ttHnonbb" and (gen_match_1<3 or gen_match_1>5 or gen_match_2<3 or gen_match_2>5)) continue;
	bool is_includedInEmbedded=false;
        //if (sample!="ggH" and sample!="ggH_htt125" and sample!="qqH" and sample!="qqH_htt125" and sample!="WminusH125" and sample!="WplusH125" and sample!="ZH125" and sample!="ttHTT" and sample!="ttHnonbb" and sample!="GGZHLLTT" and sample!="GGZHQQTT" and sample!="GGZHNNTT" and sample!="data_obs" and sample!="embedded" and gen_match_1>2 and gen_match_1<6 and gen_match_2>2 and gen_match_2<6) is_includedInEmbedded=true; // remove overlap with embedded samples
	bool isT=(!is_includedInEmbedded && gen_match_2==5);
        bool isL=(!is_includedInEmbedded && gen_match_2<5);

	// Weights
	float aweight=genweight*weight*LumiWeights_12->weight(npu); 
        if (sample=="embedded") aweight=genweight;
        if (byMediumDeepVSjet_2 && sample!="embedded" && sample!="data_obs" && gen_match_2==5) aweight=aweight*fct_tauid->Eval(mytau.Pt());
        if (byMediumDeepVSjet_2 && sample=="embedded" && gen_match_2==5) aweight=aweight*fct_tauid_emb->Eval(mytau.Pt());

	if (sample!="embedded" && sample!="data_obs" && (gen_match_2==1 or gen_match_2==3)){
	   if (fabs(eta_2)<1.460) aweight=aweight*1.22;
           else if (fabs(eta_2)>1.558) aweight=aweight*0.93;
	   else aweight=0.0;
           //if (mytau.Pt()>70) aweight=aweight*0.7;
	}
        if (sample!="embedded" && sample!="data_obs" && (gen_match_2==2 or gen_match_2==4)){
             if (fabs(eta_2)<0.4) aweight=aweight*0.979*1.117;
             else if (fabs(eta_2)<0.8) aweight=aweight*0.953*0.952;
             else if (fabs(eta_2)<1.2) aweight=aweight*0.983*0.952;
             else if (fabs(eta_2)<1.7) aweight=aweight*0.988*0.744;
             else aweight=aweight*1.004*4.592;
        }

	//NNLOPS weights
        if (name.find("ggH")<100 && name.find("hww")>100){
            if (Rivet_nJets30==0) aweight = aweight * g_NNLOPS_0jet->Eval(min(Rivet_higgsPt,float(125.0)));
            if (Rivet_nJets30==1) aweight = aweight * g_NNLOPS_1jet->Eval(min(Rivet_higgsPt,float(625.0)));
            if (Rivet_nJets30==2) aweight = aweight * g_NNLOPS_2jet->Eval(min(Rivet_higgsPt,float(800.0)));
            if (Rivet_nJets30>=3) aweight = aweight * g_NNLOPS_3jet->Eval(min(Rivet_higgsPt,float(925.0)));
        }
	NumV WG1unc = qcd_ggF_uncert_2017(Rivet_nJets30, Rivet_higgsPt, Rivet_stage1_cat_pTjet30GeV);

	TLorentzVector mymet;
	mymet.SetPtEtaPhiM(met,0,metphi,0);

       float mt=TMass_F(myele.Pt(),mymet.Pt(),myele.Px(),mymet.Px(),myele.Py(),mymet.Py());
 	if (mt>50) continue;
	//if (njets>0) continue;

	if (sample=="data_obs") aweight=1.0;

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

        float trg_up=1.0;
        float trg_down=1.0;
        float zptweight=1.0;
        if (sample!="embedded" && sample!="data_obs"){
          wmc->var("e_pt")->setVal(myele.Pt());
          wmc->var("e_eta")->setVal(myele.Eta());
          wmc->var("e_iso")->setVal(iso_1);
          wmc->var("t_pt")->setVal(mytau.Pt());
          wmc->var("t_eta")->setVal(mytau.Eta());
          wmc->var("t_phi")->setVal(mytau.Phi());
          wmc->var("t_dm")->setVal(l2_decayMode);
          wmc->var("z_gen_mass")->setVal(genM);
          wmc->var("z_gen_pt")->setVal(genpT);
          aweight=aweight*wmc->function("e_trk_ratio")->getVal();
          aweight=aweight*0.991;//z vtx electron HLT
          zptweight=wmc->function("zptmass_weight_nom")->getVal();
          if (sample=="DY" or sample=="Z") aweight=aweight*zptweight;

          aweight=aweight*wmc->function("e_idiso_ic_ratio")->getVal();
          if (myele.Pt()>28) aweight=aweight*wmc->function("e_trg_ic_ratio")->getVal();
          else{
             float tautrgsf=wmc->function("t_trg_pog_deeptau_medium_etau_ratio")->getVal();
             aweight=aweight*0.93*wmc->function("e_trg_24_ic_ratio")->getVal()*tautrgsf;//FIXME
          }

          aweight=aweight*prefiring_weight;

          float weight_btag=bTagEventWeight(nbtag20,bMpt_1,bMflavor_1,bMpt_2,bMflavor_2,1,0,0);
          if (nbtag20>2) weight_btag=0;
          aweight=aweight*weight_btag;
        }

        if (sample=="embedded"){
          wmc->var("e_pt")->setVal(myele.Pt());
          wmc->var("e_eta")->setVal(fabs(myele.Eta()));
	  wmc->var("e_iso")->setVal(iso_1);
          wmc->var("t_pt")->setVal(mytau.Pt());
          wmc->var("t_eta")->setVal(mytau.Eta());
          wmc->var("t_phi")->setVal(mytau.Phi());
          wmc->var("t_dm")->setVal(l2_decayMode);
          wmc->var("gt1_pt")->setVal(1.69*genpt_1);
          wmc->var("gt2_pt")->setVal(1.47*mytau.Pt());
          wmc->var("gt1_eta")->setVal(geneta_1);
          wmc->var("gt2_eta")->setVal(mytau.Eta());
	  if (l2_decayMode==0) aweight=aweight*0.975;
	  else if (l2_decayMode==1) aweight=aweight*0.975*1.051;
	  else if (l2_decayMode==10) aweight=aweight*0.975*0.975*0.975;
	  else if (l2_decayMode==11) aweight=aweight*0.975*0.975*0.975*1.051;
	  aweight=aweight*wmc->function("m_sel_trg_ic_ratio")->getVal();
          wmc->var("gt_pt")->setVal(1.69*genpt_1);
          wmc->var("gt_eta")->setVal(geneta_1);
          aweight=aweight*wmc->function("m_sel_id_ic_ratio")->getVal();
          wmc->var("gt_pt")->setVal(1.47*mytau.Pt());
          wmc->var("gt_eta")->setVal(mytau.Eta());
          aweight=aweight*wmc->function("m_sel_id_ic_ratio")->getVal();

          aweight=aweight*wmc->function("e_trk_embed_ratio")->getVal();
	  aweight=aweight*wmc->function("e_idiso_ic_embed_ratio")->getVal();

          if ((trigger27 or trigger32) && myele.Pt()>28 && (fabs(myele.Eta())<1.479 or myele.Pt()>40)){
              aweight=aweight*wmc->function("e_trg_ic_embed_ratio")->getVal();
          }
          else if (trigger2430 && myele.Pt()<28 && fabs(myele.Eta())<1.479){
              aweight=aweight*wmc->function("e_trg_24_ic_embed_ratio")->getVal()*wmc->function("et_emb_LooseChargedIsoPFTau30_kit_ratio")->getVal();
              //aweight=aweight*wmc->function("e_trg_24_ic_embed_ratio")->getVal()*wmc->function("t_trg_mediumDeepTau_etau_embed_ratio")->getVal();//FIXME
          }
          else if ((trigger27 or trigger32) && myele.Pt()>28 && fabs(myele.Eta())>1.479 && myele.Pt()<40) aweight=aweight*wmc->function("e_trg_ic_data")->getVal();
          if (trigger2430 && myele.Pt()<28 && fabs(myele.Eta())>1.479){
             aweight=aweight*wmc->function("e_trg_24_ic_data")->getVal()*wmc->function("t_trg_mediumDeepTau_etau_data")->getVal();
          }
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

        if (mytau.Pt()>70) frac_qcd=0.0;
	float total=frac_qcd+frac_w+frac_tt;
	frac_qcd=frac_qcd/total;
        frac_w=frac_w/total;
        frac_tt=frac_tt/total;

	//************************* Fill histograms **********************
	bool is_xtrg=false;
	float pth=1.05*(myele+mytau+mymet).Pt();
	if (myele.Pt()<28) is_xtrg=true;
        double FF=1.0*get_ff(mytau.Pt(), mt, (myele+mytau).M(), m_sv, myele.Pt(), mymet.Pt(), pth, njets, is_xtrg, frac_tt, frac_qcd, frac_w, ""); // Our FF
	float myvar=(myele+mytau).M();
        TLorentzVector myrawele=myele;
	TLorentzVector myrawtau=mytau;
        TLorentzVector myrawmet=mymet;
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

	   // Reapply cuts after shift
           trigger32=(passEle32 && myele.Pt()>28 && matchEle32_1 && filterEle32_1);
           trigger27=(passEle27 && myele.Pt()>28 && matchEle27_1 && filterEle27_1);
           trigger2430=(passEle24Tau30 && matchEle24Tau30_1 && filterEle24Tau30_1 && matchEle24Tau30_2 && filterEle24Tau30_2 && myele.Pt()>25 && mytau.Pt()>35 && myele.Pt()<28 && fabs(mytau.Eta())<2.1);
           /*if (sample=="embedded" && fabs(myele.Eta())<1.479) trigger2430=(passEle24Tau30 && myele.Pt()>25 && mytau.Pt()>35 && myele.Pt()<28 && fabs(mytau.Eta())<2.1);
           if (sample=="embedded" && fabs(myele.Eta())>1.479 && myele.Pt()>28 && myele.Pt()<40 ){ trigger32=true; trigger27=true;}
           if (sample=="embedded" && fabs(myele.Eta())>1.479 && myele.Pt()<28){ trigger32=false; trigger27=false;}
           if (sample=="embedded" && fabs(myele.Eta())>1.479 && (myele.Pt()>25 && mytau.Pt()>35 && myele.Pt()<28 && fabs(mytau.Eta())<2.1)){ trigger2430=true;}
           if (sample=="embedded" && fabs(myele.Eta())>1.479 && !(myele.Pt()>25 && mytau.Pt()>35 && myele.Pt()<28 && fabs(mytau.Eta())<2.1)){ trigger2430=false;}*/
        if (sample=="embedded"){//FIXME
           if (fabs(eta_1)>1.479 && myele.Pt()<40){
                trigger2430=(myele.Pt()>25 && mytau.Pt()>35 && myele.Pt()<28 && fabs(eta_2)<2.1);
                trigger27=(myele.Pt()>28);
                trigger32=(myele.Pt()>28);
           }
           else{
                trigger2430=(passEle24Tau30 && myele.Pt()>25 && mytau.Pt()>35 && myele.Pt()<28 && fabs(eta_2)<2.1);
                trigger27=(passEle27 && myele.Pt()>28 && matchEle27_1 && filterEle27_1);
                trigger32=(passEle32 && myele.Pt()>28 && matchEle32_1 && filterEle32_1);
           }
        }

           if (!trigger27 && !trigger32 && !trigger2430) continue;

	   if (mytau.Pt()<30) continue;
           if (numberJets==0 and myele.DeltaR(mytau)<2.0) continue;

	   // Calculate mT and observables
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
              mass6=fabs(myele.Eta()-mytau.Eta());
              mass7=fabs(myele.DeltaPhi(mytau));
              mass8=fabs(myele.DeltaR(mytau));
           }
	   /*if (do_control_plots==1){
              mass0=(myele+mytau).M();
              mass1=(myele+mytau).M();
              mass2=(myele+mytau).M();
              mass3=(myele+mytau).M();
              mass4=(myele+mytau).M();
              mass5=(myele+mytau).M();
              mass6=(myele+mytau).M();
              mass7=(myele+mytau).M();
              mass8=(myele+mytau).M();
	   }*/

/*if (sample=="embedded" && 1.05*(myele+mytau+mymet).Pt()<50 or 1.05*(myele+mytau+mymet).Pt()>70) weight2=0.9;
if (sample=="embedded" && 1.05*(myele+mytau+mymet).Pt()>50 && 1.05*(myele+mytau+mymet).Pt()<60) weight2=0.8;
if (sample=="embedded" && 1.05*(myele+mytau+mymet).Pt()>60 && 1.05*(myele+mytau+mymet).Pt()<70) weight2=0.65;*/

	   // Fill SR histograms
           if (q_1*q_2<0){
//if (signalRegion && (myele+mytau+mymet).Pt()>0 && (myele+mytau+mymet).Pt()<80) cout<<(myele+mytau+mymet).Pt()<<" "<<fabs(myele.Eta()-mytau.Eta())<<" "<<fabs(myele.DeltaPhi(mytau))<<" "<<fabs(myele.DeltaR(mytau))<<" "<<(myele+mytau).M()<<endl;
	       if (k==0 && is_includedInEmbedded && signalRegion)
		   h0_ttcontamination->Fill(myvar0,mass0,aweight*weight2);
               if ((sample=="data_obs" or isT) && signalRegion)
                   h0tau_OS[k]->Fill(myvar0,mass0,aweight*weight2);
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

           if (q_1*q_2<0){
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

           if (q_1*q_2<0){
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

           if (q_1*q_2<0){
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

           if (q_1*q_2<0){
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

           if (q_1*q_2<0){
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
               if ((sample!="data_obs" && (sample=="embedded" or isT)) && antiisoRegion)
                   h5tau_AI[k]->Fill(myvar5,mass5,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && isL) && antiisoRegion)
                   h5ell_AI[k]->Fill(myvar5,mass5,aweight*weight2*FF);
               if ((sample!="data_obs" && sample!="embedded" && gen_match_2==6) && antiisoRegion)
                   h5jet_AI[k]->Fill(myvar5,mass5,aweight*weight2);

           }

           if (q_1*q_2<0){
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

           if (q_1*q_2<0){
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

           if (q_1*q_2<0){
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

    TString postfix="";
    TDirectory *OS0jet =fout->mkdir("et_0jet");
    OS0jet->cd();
    h0_ttcontamination->SetName("ttcontamination");
    h0_ttcontamination->Write();
    cout<<h0tau_OS[0]->Integral()<<endl;
    for (int k=0; k<nbhist; ++k){
       if (name!="embedded" && name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
          h0tau_OS[k]->SetName(name+"T"+postfix);
          h0ell_OS[k]->SetName(name+"L"+postfix);
          h0jet_OS[k]->SetName(name+"J"+postfix);
          h0tau_OS[k]->Write();
          h0ell_OS[k]->Write();
          h0jet_OS[k]->Write();
       }
       else{
          h0jet_OS[k]->SetName(name.c_str()+postfix);
          h0jet_OS[k]->Add(h0ell_OS[k]);
          h0jet_OS[k]->Add(h0tau_OS[k]);
          h0jet_OS[k]->Write();
       }
    }
    TDirectory *AI0jet =fout->mkdir("AI0jet");
    AI0jet->cd();
    for (int k=0; k<nbhist; ++k){
       if (name!="embedded" and name!="data_obs"){
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
       if (name!="embedded" and name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
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
       if (name!="embedded" and name!="data_obs"){
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
       if (name!="embedded" and name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
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
       if (name!="embedded" and name!="data_obs"){
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
       if (name!="embedded" and name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
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
       if (name!="embedded" and name!="data_obs"){
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
cout<<h4tau_OS[0]->Integral()<<endl;
    for (int k=0; k<nbhist; ++k){
       if (name!="embedded" and name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
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
       if (name!="embedded" and name!="data_obs"){
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
       if (name!="embedded" and name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
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
       if (name!="embedded" and name!="data_obs"){
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
       if (name!="embedded" and name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
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
       if (name!="embedded" and name!="data_obs"){
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
       if (name!="embedded" and name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
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
       if (name!="embedded" and name!="data_obs"){
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
       if (name!="embedded" and name!="data_obs" and name.find("125")>140 and name.find("hww")>140 and name.find("htt")>140 and name.find("ggH")>140 and name.find("xH")>140 and name.find("Outside")>140){
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
       if (name!="embedded" and name!="data_obs"){
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


    fout->Close();
    delete wmc;
    delete w;
cout<<h8tau_OS[0]->Integral()<<" "<<h1tau_OS[0]->Integral()<<" "<<h2tau_OS[0]->Integral()<<" "<<h3tau_OS[0]->Integral()<<" "<<h4tau_OS[0]->Integral()<<" "<<h5tau_OS[0]->Integral()<<" "<<h6tau_OS[0]->Integral()<<" "<<h7tau_OS[0]->Integral()<<" "<<h8tau_OS[0]->Integral()<<endl;
} 

