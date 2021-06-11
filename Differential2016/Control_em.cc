#include <TH2.h>
#include "btagSF.h"
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
#include "em_Tree.h"
#include "LumiReweightingStandAlone.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "ComputeWG1Unc.h"
#include "qq2Hqq_uncert_scheme.h"

using namespace std;

int main(int argc, char** argv) {

    int do_control_plots=1;//FIXME
    bool do_differential=false;
    bool do_topcontrol=false;//FIXME

    if (do_control_plots==0) do_topcontrol=false;
    if (do_differential) do_topcontrol=false;
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
    TTree *arbre = (TTree*) f_Double->Get("emu_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float ngen = nbevt->GetBinContent(2);

    float xs=1.0; float weight=1.0; float luminosity=35922.0;
    if (sample=="Z" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}
    if (sample=="DYlow"){ xs=21658.0; weight=luminosity*xs/ngen;}
    else if (sample=="TT" or sample=="TTT" or sample=="TTJ") {xs=831.76; weight=luminosity*xs/ngen;}
    else if (sample=="W") {xs=61526.7; weight=luminosity*xs/ngen;}
    else if (sample=="data_obs"){weight=1.0;}
    else if (sample=="embedded"){weight=1.0;}
    else if (sample=="ST_tW_antitop") {xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top") {xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop") {xs=26.23; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top") {xs=44.07; weight=luminosity*xs/ngen;}
    else if (sample=="ggH_htt125") {xs=48.30*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="qqH_htt125") {xs=3.770*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="ggH") {xs=48.30*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="qqH") {xs=3.770*0.06208; weight=luminosity*xs/ngen;}
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
    else if (sample=="WZ3L1Nu") {xs=4.708; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2L2Q") {xs=5.595; weight=luminosity*xs/ngen;}
    else if (sample=="WW1L1Nu2Q") {xs=49.997; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L") {xs=1.212; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q") {xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu") {xs=13.84; weight=luminosity*xs/ngen;}
    else if (sample=="WGLNu") {xs=489.0; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWminus") {xs=20.25; weight=luminosity*xs/ngen;}
    else if (sample=="EWKWplus") {xs=25.62; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZLL" or sample=="EWKZLL_TT" or sample=="EWKZLL_J" or sample=="EWKZLL_L" or sample=="EWKZLL_LL") {xs=3.987; weight=luminosity*xs/ngen;}
    else if (sample=="EWKZNuNu" or sample=="EWKZNuNu_TT" or sample=="EWKZNuNu_J" or sample=="EWKZNuNu_L" or sample=="EWKZNuNu_LL") {xs=10.01; weight=luminosity*xs/ngen;}


    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt);
    arbre->SetBranchAddress("Rivet_stage1_1_fine_cat_pTjet30GeV", & Rivet_stage1_1_fine_cat_pTjet30GeV);
    arbre->SetBranchAddress("Rivet_stage1_1_cat_pTjet30GeV", & Rivet_stage1_1_cat_pTjet30GeV);
    arbre->SetBranchAddress("Rivet_stage1_cat_pTjet30GeV", & Rivet_stage1_cat_pTjet30GeV);
    arbre->SetBranchAddress("Rivet_nJets30", & Rivet_nJets30);
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
    arbre->SetBranchAddress("lheweight_muR0p5_muF0p5", &lheweight_muR0p5_muF0p5);
    arbre->SetBranchAddress("lheweight_muR2_muF2", &lheweight_muR2_muF2);
    arbre->SetBranchAddress("lheweight_nominal", &lheweight_nominal);

    arbre->SetBranchAddress("HTTgenfinalstate", &HTTgenfinalstate);
    arbre->SetBranchAddress("gen_met_pt", &gen_met_pt);
    arbre->SetBranchAddress("gen_met_phi", &gen_met_phi);
    arbre->SetBranchAddress("gen_ele_pt", &gen_ele_pt);
    arbre->SetBranchAddress("gen_ele_eta", &gen_ele_eta);
    arbre->SetBranchAddress("gen_ele_phi", &gen_ele_phi);
    arbre->SetBranchAddress("gen_mu_pt", &gen_mu_pt);
    arbre->SetBranchAddress("gen_mu_eta", &gen_mu_eta);
    arbre->SetBranchAddress("gen_mu_phi", &gen_mu_phi);

    arbre->SetBranchAddress("passMu8E23", &passMu8E23);
    arbre->SetBranchAddress("passMu23E12", &passMu23E12);
    arbre->SetBranchAddress("matchMu8E23_1", &matchMu8E23_1);
    arbre->SetBranchAddress("matchMu23E12_1", &matchMu23E12_1);
    arbre->SetBranchAddress("filterMu8E23_1", &filterMu8E23_1);
    arbre->SetBranchAddress("filterMu23E12_1", &filterMu23E12_1);
    arbre->SetBranchAddress("matchMu8E23_2", &matchMu8E23_2);
    arbre->SetBranchAddress("matchMu23E12_2", &matchMu23E12_2);
    arbre->SetBranchAddress("filterMu8E23_2", &filterMu8E23_2);
    arbre->SetBranchAddress("filterMu23E12_2", &filterMu23E12_2);

    arbre->SetBranchAddress("passMu8E23DZ", &passMu8E23DZ);
    arbre->SetBranchAddress("passMu23E12DZ", &passMu23E12DZ);
    arbre->SetBranchAddress("matchMu8E23DZ_1", &matchMu8E23DZ_1);
    arbre->SetBranchAddress("matchMu23E12DZ_1", &matchMu23E12DZ_1);
    arbre->SetBranchAddress("filterMu8E23DZ_1", &filterMu8E23DZ_1);
    arbre->SetBranchAddress("filterMu23E12DZ_1", &filterMu23E12DZ_1);
    arbre->SetBranchAddress("matchMu8E23DZ_2", &matchMu8E23DZ_2);
    arbre->SetBranchAddress("matchMu23E12DZ_2", &matchMu23E12DZ_2);
    arbre->SetBranchAddress("filterMu8E23DZ_2", &filterMu8E23DZ_2);
    arbre->SetBranchAddress("filterMu23E12DZ_2", &filterMu23E12DZ_2);

    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("lumi", &lumi);
    arbre->SetBranchAddress("evt", &evt);
    arbre->SetBranchAddress("npv", &npv);
    arbre->SetBranchAddress("pt_1", &pt_1);
    arbre->SetBranchAddress("phi_1", &phi_1);
    arbre->SetBranchAddress("eta_1", &eta_1);
    arbre->SetBranchAddress("iso_1", &iso_1);
    arbre->SetBranchAddress("iso_2", &iso_2);
    arbre->SetBranchAddress("m_1", &m_1);
    arbre->SetBranchAddress("q_1", &q_1);
    arbre->SetBranchAddress("nbtag", &nbtag);
    arbre->SetBranchAddress("nbtagL", &nbtagL);
    arbre->SetBranchAddress("genpt_1", &genpt_1);
    arbre->SetBranchAddress("geneta_1", &geneta_1);
    arbre->SetBranchAddress("genpt_2", &genpt_2);
    arbre->SetBranchAddress("geneta_2", &geneta_2);
    arbre->SetBranchAddress("prefiring_weight", &prefiring_weight);
    arbre->SetBranchAddress("prefiring_weight_up", &prefiring_weight_up);
    arbre->SetBranchAddress("prefiring_weight_down", &prefiring_weight_down);
    arbre->SetBranchAddress("q_2", &q_2);
    arbre->SetBranchAddress("pt_2", &pt_2);
    arbre->SetBranchAddress("eta_2", &eta_2);
    arbre->SetBranchAddress("m_2", &m_2);
    arbre->SetBranchAddress("phi_2", &phi_2);

    arbre->SetBranchAddress("metcov00", &metcov00);
    arbre->SetBranchAddress("metcov11", &metcov11);
    arbre->SetBranchAddress("metcov01", &metcov01);
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

    arbre->SetBranchAddress("m_sv", &m_sv);
    arbre->SetBranchAddress("m_sv_muonESDown", &m_sv_muonESDown);
    arbre->SetBranchAddress("m_sv_muonESUp", &m_sv_muonESUp);
    arbre->SetBranchAddress("m_sv_UESUp", &m_sv_UESUp);
    arbre->SetBranchAddress("m_sv_UESDown", &m_sv_UESDown);
    arbre->SetBranchAddress("m_sv_elescaleESUp", &m_sv_elescaleESUp);
    arbre->SetBranchAddress("m_sv_elescaleESDown", &m_sv_elescaleESDown);
    arbre->SetBranchAddress("m_sv_ResponseDown", &m_sv_ResponseDown);
    arbre->SetBranchAddress("m_sv_ResponseUp", &m_sv_ResponseUp);
    arbre->SetBranchAddress("m_sv_ResolutionDown", &m_sv_ResolutionDown);
    arbre->SetBranchAddress("m_sv_ResolutionUp", &m_sv_ResolutionUp);
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
    arbre->SetBranchAddress("beta_1", &beta_1);
    arbre->SetBranchAddress("bphi_1", &bphi_1);
    arbre->SetBranchAddress("bpt_2", &bpt_2);
    arbre->SetBranchAddress("beta_2", &beta_2);
    arbre->SetBranchAddress("bphi_2", &bphi_2);
    arbre->SetBranchAddress("bflavor_1", &bflavor_1);
    arbre->SetBranchAddress("bflavor_2", &bflavor_2);
    arbre->SetBranchAddress("bcsv_1", &bcsv_1);
    arbre->SetBranchAddress("bcsv_2", &bcsv_2);

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

    arbre->SetBranchAddress("genweight", &genweight);
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

    arbre->SetBranchAddress("pt_1_ScaleUp", &pt_1_ScaleUp);
    arbre->SetBranchAddress("pt_1_ScaleDown", &pt_1_ScaleDown);

   bool is_higgs=((sample.find("ggH") < 140) or (sample.find("qqH") < 140) or (sample.find("ttH") < 140) or (sample.find("ZH") < 140) or (sample.find("WminusH") < 140) or (sample.find("WplusH") < 140) or (sample.find("ZH") < 140) or (name.find("OutsideAcceptance") < 140));
   int nbhist=1;

   std::vector<TH2F*> h0tau_OS;
   std::vector<TH2F*> h1tau_OS;
   std::vector<TH2F*> h2tau_OS;
   std::vector<TH2F*> h0tau_SS;
   std::vector<TH2F*> h1tau_SS;
   std::vector<TH2F*> h2tau_SS;
   std::vector<TH2F*> h0tau_AI;
   std::vector<TH2F*> h1tau_AI;
   std::vector<TH2F*> h2tau_AI;
   std::vector<TH2F*> h0W_AI;
   std::vector<TH2F*> h1W_AI;
   std::vector<TH2F*> h2W_AI;
   std::vector<TH2F*> h3tau_OS;
   std::vector<TH2F*> h4tau_OS;
   std::vector<TH2F*> h5tau_OS;
   std::vector<TH2F*> h6tau_OS;
   std::vector<TH2F*> h7tau_OS;
   std::vector<TH2F*> h8tau_OS;
   std::vector<TH2F*> h3tau_SS;
   std::vector<TH2F*> h4tau_SS;
   std::vector<TH2F*> h5tau_SS;
   std::vector<TH2F*> h6tau_SS;
   std::vector<TH2F*> h7tau_SS;
   std::vector<TH2F*> h8tau_SS;
   std::vector<TH2F*> h3tau_AI;
   std::vector<TH2F*> h4tau_AI;
   std::vector<TH2F*> h5tau_AI;
   std::vector<TH2F*> h6tau_AI;
   std::vector<TH2F*> h7tau_AI;
   std::vector<TH2F*> h8tau_AI;
   std::vector<TH2F*> h3W_AI;
   std::vector<TH2F*> h4W_AI;
   std::vector<TH2F*> h5W_AI;
   std::vector<TH2F*> h6W_AI;
   std::vector<TH2F*> h7W_AI;
   std::vector<TH2F*> h8W_AI;

   std::vector<TH2F*> h0ell_OS;
   std::vector<TH2F*> h1ell_OS;
   std::vector<TH2F*> h2ell_OS;
   std::vector<TH2F*> h3ell_OS;
   std::vector<TH2F*> h4ell_OS;
   std::vector<TH2F*> h5ell_OS;
   std::vector<TH2F*> h6ell_OS;
   std::vector<TH2F*> h7ell_OS;
   std::vector<TH2F*> h8ell_OS;
   std::vector<TH2F*> h0ell_SS;
   std::vector<TH2F*> h1ell_SS;
   std::vector<TH2F*> h2ell_SS;
   std::vector<TH2F*> h3ell_SS;
   std::vector<TH2F*> h4ell_SS;
   std::vector<TH2F*> h5ell_SS;
   std::vector<TH2F*> h6ell_SS;
   std::vector<TH2F*> h7ell_SS;
   std::vector<TH2F*> h8ell_SS;
   std::vector<TH2F*> h0ell_AI;
   std::vector<TH2F*> h1ell_AI;
   std::vector<TH2F*> h2ell_AI;
   std::vector<TH2F*> h3ell_AI;
   std::vector<TH2F*> h4ell_AI;
   std::vector<TH2F*> h5ell_AI;
   std::vector<TH2F*> h6ell_AI;
   std::vector<TH2F*> h7ell_AI;
   std::vector<TH2F*> h8ell_AI;

   float bins_mtt0[] = {10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70};
   float bins_mtt1[] = {10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70};
   float bins_mtt2[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150};
   float bins_mtt3[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,205,210,215,220,225,230,235,240,245,250};
   float bins_mtt4[] = {35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140};
   float bins_mtt5[] = {60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300};
   float bins_mtt6[] = {0,1,2,3,4,5,6,7};
   float bins_mtt7[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
   float bins_mtt8[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};

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

   for (int k=0; k<nbhist; ++k){
        ostringstream HNS0tauOS; HNS0tauOS << "h0tau_OS" << k;
        ostringstream HNS1tauOS; HNS1tauOS << "h1tau_OS" << k;
        ostringstream HNS2tauOS; HNS2tauOS << "h2tau_OS" << k;
        h0tau_OS.push_back(new TH2F (HNS0tauOS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_OS[k]->Sumw2();
        h1tau_OS.push_back(new TH2F (HNS1tauOS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_OS[k]->Sumw2();
        h2tau_OS.push_back(new TH2F (HNS2tauOS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_OS[k]->Sumw2();

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

        ostringstream HNS0tauSS; HNS0tauSS << "h0tau_SS" << k;
        ostringstream HNS1tauSS; HNS1tauSS << "h1tau_SS" << k;
        ostringstream HNS2tauSS; HNS2tauSS << "h2tau_SS" << k;
        h0tau_SS.push_back(new TH2F (HNS0tauSS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_SS[k]->Sumw2();
        h1tau_SS.push_back(new TH2F (HNS1tauSS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_SS[k]->Sumw2();
        h2tau_SS.push_back(new TH2F (HNS2tauSS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_SS[k]->Sumw2();

        ostringstream HNS0tauAI; HNS0tauAI << "h0tau_AI" << k;
        ostringstream HNS1tauAI; HNS1tauAI << "h1tau_AI" << k;
        ostringstream HNS2tauAI; HNS2tauAI << "h2tau_AI" << k;
        h0tau_AI.push_back(new TH2F (HNS0tauAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0tau_AI[k]->Sumw2();
        h1tau_AI.push_back(new TH2F (HNS1tauAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1tau_AI[k]->Sumw2();
        h2tau_AI.push_back(new TH2F (HNS2tauAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2tau_AI[k]->Sumw2();

        ostringstream HNS0WAI; HNS0WAI << "h0W_AI" << k;
        ostringstream HNS1WAI; HNS1WAI << "h1W_AI" << k;
        ostringstream HNS2WAI; HNS2WAI << "h2W_AI" << k;
        h0W_AI.push_back(new TH2F (HNS0WAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0W_AI[k]->Sumw2();
        h1W_AI.push_back(new TH2F (HNS1WAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1W_AI[k]->Sumw2();
        h2W_AI.push_back(new TH2F (HNS2WAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2W_AI[k]->Sumw2();

        ostringstream HNS0ellSS; HNS0ellSS << "h0ell_SS" << k;
        ostringstream HNS1ellSS; HNS1ellSS << "h1ell_SS" << k;
        ostringstream HNS2ellSS; HNS2ellSS << "h2ell_SS" << k;
        h0ell_SS.push_back(new TH2F (HNS0ellSS.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0ell_SS[k]->Sumw2();
        h1ell_SS.push_back(new TH2F (HNS1ellSS.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1ell_SS[k]->Sumw2();
        h2ell_SS.push_back(new TH2F (HNS2ellSS.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2ell_SS[k]->Sumw2();

        ostringstream HNS0ellAI; HNS0ellAI << "h0ell_AI" << k;
        ostringstream HNS1ellAI; HNS1ellAI << "h1ell_AI" << k;
        ostringstream HNS2ellAI; HNS2ellAI << "h2ell_AI" << k;
        h0ell_AI.push_back(new TH2F (HNS0ellAI.str().c_str(),"InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0)); h0ell_AI[k]->Sumw2();
        h1ell_AI.push_back(new TH2F (HNS1ellAI.str().c_str(),"InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1)); h1ell_AI[k]->Sumw2();
        h2ell_AI.push_back(new TH2F (HNS2ellAI.str().c_str(),"InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2)); h2ell_AI[k]->Sumw2();

        ostringstream HNS3tauSS; HNS3tauSS << "h3tau_SS" << k;
        ostringstream HNS4tauSS; HNS4tauSS << "h4tau_SS" << k;
        ostringstream HNS5tauSS; HNS5tauSS << "h5tau_SS" << k;
        ostringstream HNS6tauSS; HNS6tauSS << "h6tau_SS" << k;
        ostringstream HNS7tauSS; HNS7tauSS << "h7tau_SS" << k;
        ostringstream HNS8tauSS; HNS8tauSS << "h8tau_SS" << k;
        h3tau_SS.push_back(new TH2F (HNS3tauSS.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3tau_SS[k]->Sumw2();
        h4tau_SS.push_back(new TH2F (HNS4tauSS.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4tau_SS[k]->Sumw2();
        h5tau_SS.push_back(new TH2F (HNS5tauSS.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5tau_SS[k]->Sumw2();
        h6tau_SS.push_back(new TH2F (HNS6tauSS.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6tau_SS[k]->Sumw2();
        h7tau_SS.push_back(new TH2F (HNS7tauSS.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7tau_SS[k]->Sumw2();
        h8tau_SS.push_back(new TH2F (HNS8tauSS.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8tau_SS[k]->Sumw2();

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

        ostringstream HNS3WAI; HNS3WAI << "h3W_AI" << k;
        ostringstream HNS4WAI; HNS4WAI << "h4W_AI" << k;
        ostringstream HNS5WAI; HNS5WAI << "h5W_AI" << k;
        ostringstream HNS6WAI; HNS6WAI << "h6W_AI" << k;
        ostringstream HNS7WAI; HNS7WAI << "h7W_AI" << k;
        ostringstream HNS8WAI; HNS8WAI << "h8W_AI" << k;
        h3W_AI.push_back(new TH2F (HNS3WAI.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3W_AI[k]->Sumw2();
        h4W_AI.push_back(new TH2F (HNS4WAI.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4W_AI[k]->Sumw2();
        h5W_AI.push_back(new TH2F (HNS5WAI.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5W_AI[k]->Sumw2();
        h6W_AI.push_back(new TH2F (HNS6WAI.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6W_AI[k]->Sumw2();
        h7W_AI.push_back(new TH2F (HNS7WAI.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7W_AI[k]->Sumw2();
        h8W_AI.push_back(new TH2F (HNS8WAI.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8W_AI[k]->Sumw2();

        ostringstream HNS3ellSS; HNS3ellSS << "h3ell_SS" << k;
        ostringstream HNS4ellSS; HNS4ellSS << "h4ell_SS" << k;
        ostringstream HNS5ellSS; HNS5ellSS << "h5ell_SS" << k;
        ostringstream HNS6ellSS; HNS6ellSS << "h6ell_SS" << k;
        ostringstream HNS7ellSS; HNS7ellSS << "h7ell_SS" << k;
        ostringstream HNS8ellSS; HNS8ellSS << "h8ell_SS" << k;
        h3ell_SS.push_back(new TH2F (HNS3ellSS.str().c_str(),"InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3)); h3ell_SS[k]->Sumw2();
        h4ell_SS.push_back(new TH2F (HNS4ellSS.str().c_str(),"InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4)); h4ell_SS[k]->Sumw2();
        h5ell_SS.push_back(new TH2F (HNS5ellSS.str().c_str(),"InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5)); h5ell_SS[k]->Sumw2();
        h6ell_SS.push_back(new TH2F (HNS6ellSS.str().c_str(),"InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6)); h6ell_SS[k]->Sumw2();
        h7ell_SS.push_back(new TH2F (HNS7ellSS.str().c_str(),"InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7)); h7ell_SS[k]->Sumw2();
        h8ell_SS.push_back(new TH2F (HNS8ellSS.str().c_str(),"InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8)); h8ell_SS[k]->Sumw2();

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

   TH2F* h0_ttcontamination=new TH2F ("h0_ttcontamination","InvMa",binnum_taupt,bins_taupt,binnum_mtt0,bins_mtt0); h0_ttcontamination->Sumw2();
   TH2F* h1_ttcontamination=new TH2F ("h1_ttcontamination","InvMa",binnum_pth,bins_pth,binnum_mtt1,bins_mtt1); h1_ttcontamination->Sumw2();
   TH2F* h2_ttcontamination=new TH2F ("h2_ttcontamination","InvMa",binnum_mjj,bins_mjj,binnum_mtt2,bins_mtt2); h2_ttcontamination->Sumw2();
   TH2F* h3_ttcontamination=new TH2F ("h3_ttcontamination","InvMa",binnum_taupt_low,bins_taupt_low,binnum_mtt3,bins_mtt3); h3_ttcontamination->Sumw2();
   TH2F* h4_ttcontamination=new TH2F ("h4_ttcontamination","InvMa",binnum_taupt_high,bins_taupt_high,binnum_mtt4,bins_mtt4); h4_ttcontamination->Sumw2();
   TH2F* h5_ttcontamination=new TH2F ("h5_ttcontamination","InvMa",binnum_pth_1,bins_pth_1,binnum_mtt5,bins_mtt5); h5_ttcontamination->Sumw2();
   TH2F* h6_ttcontamination=new TH2F ("h6_ttcontamination","InvMa",binnum_pth_2,bins_pth_2,binnum_mtt6,bins_mtt6); h6_ttcontamination->Sumw2();
   TH2F* h7_ttcontamination=new TH2F ("h7_ttcontamination","InvMa",binnum_mjj_low,bins_mjj_low,binnum_mtt7,bins_mtt7); h7_ttcontamination->Sumw2();
   TH2F* h8_ttcontamination=new TH2F ("h8_ttcontamination","InvMa",binnum_mjj_high,bins_mjj_high,binnum_mtt8,bins_mtt8); h8_ttcontamination->Sumw2();


    TH1F* msv = new TH1F ("msv", "msv",40,0,200);
    TH1F* mvis = new TH1F ("mvis", "mvis",40,0,200);

    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("MC_Moriond17_PU25ns_V1.root", "Data_Pileup_2016_271036-284044_80bins.root", "pileup", "pileup");

   TFile ftt("toppt_correction_to_2016.root");
   TF1 *fct_tt=(TF1*) ftt.Get("toppt_ratio_to_2016");

   TFile ffrac("fractions_em.root");
   TH1F* hfrac_0jet = (TH1F*) ffrac.Get("fraction_qcd_em_0jet");
   TH1F* hfrac_1jet = (TH1F*) ffrac.Get("fraction_qcd_em_1jet");
   TH1F* hfrac_2jet = (TH1F*) ffrac.Get("fraction_qcd_em_2jet");
   TH1F* hfrac_3jet = (TH1F*) ffrac.Get("fraction_qcd_em_3jet");
   TH1F* hfrac_4jet = (TH1F*) ffrac.Get("fraction_qcd_em_4jet");

   TFile fwmc("htt_scalefactors_legacy_2016.root");
   RooWorkspace *wmc = (RooWorkspace*)fwmc.Get("w");
   fwmc.Close();

   TFile fclosure("qcdfiles_em/closure.root");
   TH2F *closure0=(TH2F*) fclosure.Get("closureOS0");
   TH2F *closure1=(TH2F*) fclosure.Get("closureOS1");
   TH2F *closure2=(TH2F*) fclosure.Get("closureOS2");
   TH2F *closureOS=(TH2F*) fclosure.Get("closureOS");
   TH2F *correction=(TH2F*) fclosure.Get("correction");

   TFile *fosss= new TFile("osss_em_2016.root","r");
   TF1 *osss_0jet=(TF1*) fosss->Get("OSSS_qcd_0jet_2016");
   TF1 *osss_0jet_unc1_up=(TF1*) fosss->Get("OSSS_qcd_0jet_2016_unc1_up");
   TF1 *osss_0jet_unc1_down=(TF1*) fosss->Get("OSSS_qcd_0jet_2016_unc1_down");
   TF1 *osss_0jet_unc2_up=(TF1*) fosss->Get("OSSS_qcd_0jet_2016_unc2_up");
   TF1 *osss_0jet_unc2_down=(TF1*) fosss->Get("OSSS_qcd_0jet_2016_unc2_down");
   TF1 *osss_1jet=(TF1*) fosss->Get("OSSS_qcd_1jet_2016");
   TF1 *osss_1jet_unc1_up=(TF1*) fosss->Get("OSSS_qcd_1jet_2016_unc1_up");
   TF1 *osss_1jet_unc1_down=(TF1*) fosss->Get("OSSS_qcd_1jet_2016_unc1_down");
   TF1 *osss_1jet_unc2_up=(TF1*) fosss->Get("OSSS_qcd_1jet_2016_unc2_up");
   TF1 *osss_1jet_unc2_down=(TF1*) fosss->Get("OSSS_qcd_1jet_2016_unc2_down");
   TF1 *osss_2jet=(TF1*) fosss->Get("OSSS_qcd_2jet_2016");
   TF1 *osss_2jet_unc1_up=(TF1*) fosss->Get("OSSS_qcd_2jet_2016_unc1_up");
   TF1 *osss_2jet_unc1_down=(TF1*) fosss->Get("OSSS_qcd_2jet_2016_unc1_down");
   TF1 *osss_2jet_unc2_up=(TF1*) fosss->Get("OSSS_qcd_2jet_2016_unc2_up");
   TF1 *osss_2jet_unc2_down=(TF1*) fosss->Get("OSSS_qcd_2jet_2016_unc2_down");

   TFile * f_NNLOPS = new TFile("NNLOPS_reweight.root");
   TGraph * g_NNLOPS_0jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_0jet");
   TGraph * g_NNLOPS_1jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_1jet");
   TGraph * g_NNLOPS_2jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_2jet");
   TGraph * g_NNLOPS_3jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_3jet");

   bool do_rivet=(name=="OutsideAcceptance" or name.find("xH") < 140 or name.find("ttH") < 140 or name.find("ggH") < 140 or name.find("qqH") < 140 or name.find("VH") < 140 or name.find("WH") < 140 or name.find("ZH") < 140);

   bool norecoil=(name.find("WH") < 140 or name.find("ZH") < 140 or sample=="TT" or name=="TT" or name=="VV" or name=="ST");

   bool is_inclusivesignal=false;
   if (name=="ggH_htt125" or name=="qqH_htt125" or name=="WH_htt125" or name=="ZH_htt125" or name=="ggH_hww125" or name=="qqH_hww125" or name=="WH_hww125" or name=="ZH_hww125") is_inclusivesignal=true;


   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

lheweight_nominal=1.0;//

	if (fabs(eta_1)>2.4) continue;
        if (fabs(eta_2)>2.4) continue;

        int nbtag20=0;
        float bMpt_1=0;
        float bMflavor_1=0;
        float bMpt_2=0;
        float bMflavor_2=0;
        if (bpt_1>20 && bcsv_1>0.6321){
           bMpt_1=bpt_1;
           bMflavor_1=bflavor_1;
           nbtag20++;
        }
        if (bpt_2>20 && bcsv_2>0.6321){
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

        bool triggerMu8E23=(passMu8E23 && matchMu8E23_1 && filterMu8E23_1 && matchMu8E23_2 && pt_1>23.5 && pt_2>9.5);
        bool triggerMu23E12=(passMu23E12 && matchMu23E12_1 && filterMu23E12_1 && matchMu23E12_2 && pt_1>12.5 && pt_2>23.5);
	if (sample=="data_obs" && run>=278820){
           triggerMu8E23=(passMu8E23DZ && matchMu8E23DZ_1 && filterMu8E23DZ_1 && matchMu8E23DZ_2 && filterMu8E23DZ_2 && pt_1>23 && pt_2>9);
           triggerMu23E12=(passMu23E12DZ && matchMu23E12DZ_1 && filterMu23E12DZ_1 && matchMu23E12DZ_2 && filterMu23E12DZ_2 && pt_1>12 && pt_2>23);
  	}
        if (!triggerMu8E23 && !triggerMu23E12) continue;

        float signalRegion=(iso_1<0.15 && iso_2<0.15);
	float wRegion=(iso_1<0.50 && iso_2<0.50 && (iso_1<0.15 or iso_2<0.15));
        float antiisoRegion=(iso_1<0.30 && iso_2>0.10 && iso_2<0.30);
        float antiisoRegionVBF=(iso_1<0.50 && iso_2>0.20 && iso_2<0.50);
	if (!signalRegion) continue;

	TLorentzVector mymu; 
	mymu.SetPtEtaPhiM(pt_2,eta_2,phi_2,m_2);
        TLorentzVector myele;
        myele.SetPtEtaPhiM(pt_1,eta_1,phi_1,m_1);

	if (mymu.DeltaR(myele)<0.3) continue;

	if (sample=="W"){ //20nov
            weight=25.42858;
            if (numGenJets==1) weight=5.7747;
            else if (numGenJets==2) weight=1.79323;
            else if (numGenJets==3) weight=0.68005;
            else if (numGenJets==4) weight=0.80296;
        }
        if (sample=="DY" or sample=="Z"){
            weight=1.4924;
            if (numGenJets==1) weight=0.47595;
            else if (numGenJets==2) weight=0.49549;
            else if (numGenJets==3) weight=0.505517;
            else if (numGenJets==4) weight=0.414664;
        }

	float aweight=genweight*weight*LumiWeights_12->weight(npu);
        if (sample=="embedded") aweight=genweight;

        bool is_includedInEmbedded=false;
        //if (sample!="ggH" and sample!="ggH_htt125" and sample!="qqH" and sample!="qqH_htt125" and sample!="WminusH125" and sample!="WplusH125" and sample!="ZH125" and sample!="ttHTT" and sample!="ttHnonbb" and sample!="GGZHLLTT" and sample!="GGZHQQTT" and sample!="GGZHNNTT" and sample!="data_obs" and sample!="embedded" and gen_match_1>2 and gen_match_1<6 and gen_match_2>2 and gen_match_2<6) is_includedInEmbedded=true; // remove overlap with embedded samples //FIXME
        if (sample!="data_obs" && (gen_match_1==6 or gen_match_2==6)) continue;//FIXME
	if (sample=="ttHnonbb" and (gen_match_1<3 or gen_match_1>5 or gen_match_2<3 or gen_match_2>5)) continue;

	//NNLOPS weights
        if (name.find("ggH")<100){
            if (Rivet_nJets30==0) aweight = aweight * g_NNLOPS_0jet->Eval(min(Rivet_higgsPt,float(125.0)));
            if (Rivet_nJets30==1) aweight = aweight * g_NNLOPS_1jet->Eval(min(Rivet_higgsPt,float(625.0)));
            if (Rivet_nJets30==2) aweight = aweight * g_NNLOPS_2jet->Eval(min(Rivet_higgsPt,float(800.0)));
            if (Rivet_nJets30>=3) aweight = aweight * g_NNLOPS_3jet->Eval(min(Rivet_higgsPt,float(925.0)));
        }
	NumV WG1unc = qcd_ggF_uncert_2017(Rivet_nJets30, Rivet_higgsPt, Rivet_stage1_cat_pTjet30GeV);

	TLorentzVector mymet;
	mymet.SetPtEtaPhiM(met,0,metphi,0);

	if (sample=="data_obs") aweight=1.0;

	// Top pT reweighting
        float topfactor=1.0;
        if (sample=="TT"){
	   float pttop1=pt_top1;
           if (pttop1>472) pttop1=472;
           float pttop2=pt_top2;
           if (pttop2>472) pttop2=472;
	   topfactor=sqrt(exp(0.088-0.00087*pttop1+0.00000092*pttop1*pttop1)*exp(0.088-0.00087*pttop2+0.00000092*pttop2*pttop2));
           topfactor=topfactor*(1.0/fct_tt->Eval(pttop1))*(1.0/fct_tt->Eval(pttop2));
           aweight*=topfactor;
        }

        float zptweight=1.0;
	if (sample!="embedded" && sample!="data_obs"){
          wmc->var("z_gen_mass")->setVal(genM);
          wmc->var("z_gen_pt")->setVal(genpT);
          zptweight=wmc->function("zptmass_weight_nom")->getVal();
          if (sample=="DY" or sample=="Z") aweight=aweight*zptweight;

          wmc->var("m_pt")->setVal(mymu.Pt());
          wmc->var("m_eta")->setVal(mymu.Eta());
          wmc->var("m_iso")->setVal(iso_2);
          wmc->var("e_pt")->setVal(myele.Pt());
          wmc->var("e_eta")->setVal(myele.Eta());
          wmc->var("e_iso")->setVal(iso_1);
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*wmc->function("e_trk_ratio")->getVal();
          aweight=aweight*wmc->function("m_idiso_ic_ratio")->getVal();
          aweight=aweight*wmc->function("e_idiso_ic_ratio")->getVal();

          float weight_btag=bTagEventWeight(nbtag20,bMpt_1,bMflavor_1,bMpt_2,bMflavor_2,1,0,0);
          aweight=aweight*weight_btag;

          aweight=aweight*prefiring_weight;

          float probData =wmc->function("m_trg_8_ic_data")->getVal()*wmc->function("e_trg_23_ic_data")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_data")->getVal()*wmc->function("e_trg_12_ic_data")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_data")->getVal()*wmc->function("m_trg_23_ic_data")->getVal()*int(triggerMu8E23 && triggerMu23E12);
          float probMC =wmc->function("m_trg_8_ic_mc")->getVal()*wmc->function("e_trg_23_ic_mc")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_mc")->getVal()*wmc->function("e_trg_12_ic_mc")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_mc")->getVal()*wmc->function("m_trg_23_ic_mc")->getVal()*int(triggerMu8E23 && triggerMu23E12);
	  float sf_trg=1.0;
          if (probMC==0) sf_trg=1.0;
	  else sf_trg=probData/probMC;
          aweight=aweight*sf_trg;
	}

        if (sample=="embedded" && sample!="data_obs"){
	  wmc->var("e_pt")->setVal(myele.Pt());
          wmc->var("e_eta")->setVal(myele.Eta());
          wmc->var("e_iso")->setVal(iso_1);
          wmc->var("m_pt")->setVal(mymu.Pt());
          wmc->var("m_eta")->setVal(mymu.Eta());
          wmc->var("m_iso")->setVal(iso_2);
          wmc->var("gt1_pt")->setVal(1.69*genpt_1);
          wmc->var("gt2_pt")->setVal(1.69*genpt_2);
          wmc->var("gt1_eta")->setVal(geneta_1);
          wmc->var("gt2_eta")->setVal(geneta_2);
          aweight=aweight*wmc->function("m_sel_trg_ic_ratio")->getVal();
          wmc->var("gt_pt")->setVal(1.69*genpt_1);
          wmc->var("gt_eta")->setVal(geneta_1);
          aweight=aweight*wmc->function("m_sel_id_ic_ratio")->getVal();
          wmc->var("gt_pt")->setVal(1.69*genpt_2);
          wmc->var("gt_eta")->setVal(geneta_2);
          aweight=aweight*wmc->function("m_sel_id_ic_ratio")->getVal();

          aweight=aweight*wmc->function("e_idiso_ic_embed_ratio")->getVal();
          aweight=aweight*wmc->function("m_idiso_ic_embed_ratio")->getVal();
          aweight=aweight*wmc->function("m_trk_ratio")->getVal();
          aweight=aweight*wmc->function("e_trk_embed_ratio")->getVal();

          float probData =wmc->function("m_trg_8_ic_data")->getVal()*wmc->function("e_trg_23_ic_data")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_data")->getVal()*wmc->function("e_trg_12_ic_data")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_data")->getVal()*wmc->function("m_trg_23_ic_data")->getVal()*int(triggerMu8E23 && triggerMu23E12);
          float probEmbedded =wmc->function("m_trg_8_ic_embed")->getVal()*wmc->function("e_trg_23_ic_embed")->getVal()*int(triggerMu8E23)+wmc->function("m_trg_23_ic_embed")->getVal()*wmc->function("e_trg_12_ic_embed")->getVal()*int(triggerMu23E12)-wmc->function("e_trg_23_ic_embed")->getVal()*wmc->function("m_trg_23_ic_embed")->getVal()*int(triggerMu8E23 && triggerMu23E12);
          float sf_trg=probData/probEmbedded;
          if (probEmbedded==0) sf_trg=1;
          aweight=aweight*sf_trg;
        }

        bool is_tau=(!is_includedInEmbedded && (sample=="data_obs" or sample=="embedded" or ((gen_match_1==3 or gen_match_1==4) and (gen_match_2==3 or gen_match_2==4))));
        bool is_ell=(!is_includedInEmbedded && !is_tau && (name!="Z" or (gen_match_1==gen_match_2)));//FIXME

	//************************* Fill histograms **********************
	float myvar=(mymu+myele).M();
	TLorentzVector myrawele=myele;
        TLorentzVector myrawmu=mymu;
        TLorentzVector myrawmet=mymet;
        float massJets=mjj;
        int numberJets=njets;
	float leadingJetPt=jpt_1;
	float mtt=m_sv;
	for (int k=0; k<nbhist; ++k){

	   float weight2=1.0;

	   // reset all variables before any systematic shift
	   massJets=mjj;
	   mtt=m_sv;
	   numberJets=njets;
	   leadingJetPt=jpt_1;
	   myele=myrawele;
           mymu=myrawmu;
	   mymet=myrawmet;
	   massJets=mjj;

	   if (mymu.Pt()<24 and myele.Pt()<24) continue;
	   if (mymu.Pt()<15) continue;
	   if (myele.Pt()<15) continue;

           triggerMu8E23=(passMu8E23 && matchMu8E23_1 && filterMu8E23_1 && matchMu8E23_2 && myele.Pt()>24 && mymu.Pt()>10);
           triggerMu23E12=(passMu23E12 && matchMu23E12_1 && filterMu23E12_1 && matchMu23E12_2 && myele.Pt()>13 && mymu.Pt()>24);
           if (sample=="data_obs" && run>=278820){
              triggerMu8E23=(passMu8E23DZ && matchMu8E23DZ_1 && filterMu8E23DZ_1 && matchMu8E23DZ_2 && filterMu8E23DZ_2 && myele.Pt()>24 && mymu.Pt()>10);
              triggerMu23E12=(passMu23E12DZ && matchMu23E12DZ_1 && filterMu23E12DZ_1 && matchMu23E12DZ_2 && filterMu23E12DZ_2 && myele.Pt()>13 && mymu.Pt()>24);
           }
           if (!triggerMu8E23 && !triggerMu23E12) continue;

           float norm_zeta=norm_F(myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt(),myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt());
           float x_zeta= (myele.Px()/myele.Pt()+mymu.Px()/mymu.Pt())/norm_zeta;
           float y_zeta= (myele.Py()/myele.Pt()+mymu.Py()/mymu.Pt())/norm_zeta;
           float p_zeta_mis=mymet.Px()*x_zeta+mymet.Py()*y_zeta;
           float pzeta_vis=(myele.Px()+mymu.Px())*x_zeta+(myele.Py()+mymu.Py())*y_zeta;
	   float dzeta=p_zeta_mis-0.85*pzeta_vis;
	   bool pass_dzeta=true;//dzeta>-30;

           float mt=TMass_F((myele+mymu).Pt(),mymet.Pt(),(myele+mymu).Px(),mymet.Px(),(myele+mymu).Py(),mymet.Py());
	   bool pass_mt=(mt<60);
	   if (do_topcontrol) pass_mt=true;
	   if (do_topcontrol && dzeta>-40) continue; 
	   if (do_topcontrol) pass_dzeta=true;

	   myvar=mtt;
	   //if (numberJets==0) myvar=(mymu+myele).M();
	   float myvar0=myele.Pt();
	   float myvar1=(mymu+myele+mymet).Pt();
	   float myvar2=massJets;
	   float mass0=myvar;
           float mass1=myvar;
           float mass2=myvar;
           float mass3=myvar;
           float mass4=myvar;
           float mass5=myvar;
           float mass6=myvar;
           float mass7=myvar;
           float mass8=myvar;

           float myvar3=myvar0;
           float myvar4=myvar0;
           float myvar5=myvar1;
           float myvar6=myvar1;
           float myvar7=myvar2;
           float myvar8=myvar2;

           if (do_control_plots>0){
                myvar0=1;myvar1=1;myvar2=1;myvar3=1;myvar4=1;myvar5=1;myvar6=1;myvar7=1;myvar8=1;
           }
	   if (do_control_plots==1){
	      mass0=mymu.Pt();
              mass1=myele.Pt();
	      mass2=mymet.Pt();
              mass3=(myele+mymu+mymet).Pt();
              mass4=(myele+mymu).M();
              mass5=m_sv;
              mass6=njets;
              mass7=myele.Eta();
              mass8=mymu.Eta();
	   }
           float ssweight=2.5;
           if (numberJets==0) ssweight=osss_0jet->Eval(myele.DeltaR(mymu));
           else if (numberJets==1) ssweight=osss_1jet->Eval(myele.DeltaR(mymu));
           else ssweight=osss_2jet->Eval(myele.DeltaR(mymu));

           float sscorr=1.0;
           float mupt=mymu.Pt();
           float ept=myele.Pt();
           if (mupt>100) mupt=99;
           if (ept>100) ept=99;
           sscorr=correction->GetBinContent(correction->GetXaxis()->FindBin(mupt),correction->GetYaxis()->FindBin(ept));

	   if (sample=="embedded" && aweight*weight2>1) aweight=0.0; //FIXME 

float frac=hfrac_0jet->GetBinContent(hfrac_0jet->GetXaxis()->FindBin(m_sv));
if (njets==1) frac=hfrac_1jet->GetBinContent(hfrac_1jet->GetXaxis()->FindBin(m_sv));
else if (njets==2) frac=hfrac_2jet->GetBinContent(hfrac_2jet->GetXaxis()->FindBin(m_sv));
else if (njets==3) frac=hfrac_3jet->GetBinContent(hfrac_3jet->GetXaxis()->FindBin(m_sv));
else if (njets>=4) frac=hfrac_4jet->GetBinContent(hfrac_4jet->GetXaxis()->FindBin(m_sv));

/*if (njets==0) frac=1.0;//FIXME
if (njets==1) frac=0.95;//FIXME
if (njets==2) frac=0.8;//FIXME
if (njets==3) frac=0.6;//FIXME
if (njets>=4) frac=0.4;//FIXME */
frac=1.0;//FIXME


float dr=myele.DeltaR(mymu);
ssweight=ssweight*sscorr*frac + (1.0-frac)*(0.4888+2.11274*dr-1.4128*dr*dr+0.329987*dr*dr*dr-0.02756*dr*dr*dr*dr);
sscorr=1.0;

if (!pass_mt) continue;

           bool category_0=true;
           if (category_0){
	       if (signalRegion && q_1*q_2<0 && is_tau) msv->Fill(m_sv,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_tau) mvis->Fill((myele+mymu).M(),aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h0tau_OS[k]->Fill(myvar0,mass0,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h0tau_SS[k]->Fill(myvar0,mass0,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_tau)
                   h0tau_AI[k]->Fill(myvar0,mass0,aweight*weight2*ssweight*sscorr);
               if (wRegion && q_1*q_2<0)
                   h0W_AI[k]->Fill(myvar0,mass0,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h0ell_OS[k]->Fill(myvar0,mass0,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h0ell_SS[k]->Fill(myvar0,mass0,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_ell)
                   h0ell_AI[k]->Fill(myvar0,mass0,aweight*weight2*ssweight*sscorr);
           }

           bool category_1=true;
           if (category_1){
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h1tau_OS[k]->Fill(myvar1,mass1,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h1tau_SS[k]->Fill(myvar1,mass1,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_tau)
                   h1tau_AI[k]->Fill(myvar1,mass1,aweight*weight2*ssweight*sscorr);
               if (wRegion && q_1*q_2<0)
                   h1W_AI[k]->Fill(myvar1,mass1,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h1ell_OS[k]->Fill(myvar1,mass1,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h1ell_SS[k]->Fill(myvar1,mass1,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_ell)
                   h1ell_AI[k]->Fill(myvar1,mass1,aweight*weight2*ssweight*sscorr);
           }

           bool category_2=true;
           if (category_2){
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h2tau_OS[k]->Fill(myvar2,mass2,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h2tau_SS[k]->Fill(myvar2,mass2,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && q_1*q_2>0 && is_tau)
                   h2tau_AI[k]->Fill(myvar2,mass2,aweight*weight2*ssweight*sscorr);
               if (wRegion && q_1*q_2<0)
                   h2W_AI[k]->Fill(myvar2,mass2,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h2ell_OS[k]->Fill(myvar2,mass2,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h2ell_SS[k]->Fill(myvar2,mass2,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && q_1*q_2>0 && is_ell)
                   h2ell_AI[k]->Fill(myvar2,mass2,aweight*weight2*ssweight*sscorr);
           }

           bool category_3=true;
           if (category_3){
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h3tau_OS[k]->Fill(myvar3,mass3,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h3tau_SS[k]->Fill(myvar3,mass3,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_tau)
                   h3tau_AI[k]->Fill(myvar3,mass3,aweight*weight2*ssweight*sscorr);
               if (wRegion && q_1*q_2<0)
                   h3W_AI[k]->Fill(myvar3,mass3,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h3ell_OS[k]->Fill(myvar3,mass3,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h3ell_SS[k]->Fill(myvar3,mass3,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_ell)
                   h3ell_AI[k]->Fill(myvar3,mass3,aweight*weight2*ssweight*sscorr);
           }

           bool category_4=true;
           if (category_4){
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h4tau_OS[k]->Fill(myvar4,mass4,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h4tau_SS[k]->Fill(myvar4,mass4,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_tau)
                   h4tau_AI[k]->Fill(myvar4,mass4,aweight*weight2*ssweight*sscorr);
               if (wRegion && q_1*q_2<0)
                   h4W_AI[k]->Fill(myvar4,mass4,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h4ell_OS[k]->Fill(myvar4,mass4,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h4ell_SS[k]->Fill(myvar4,mass4,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_ell)
                   h4ell_AI[k]->Fill(myvar4,mass4,aweight*weight2*ssweight*sscorr);
           }

           bool category_5=true;
           if (category_5){
               if (k==0 && is_includedInEmbedded && signalRegion && q_1*q_2<0)
                   h5_ttcontamination->Fill(myvar5,mass5,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h5tau_OS[k]->Fill(myvar5,mass5,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h5tau_SS[k]->Fill(myvar5,mass5,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_tau)
                   h5tau_AI[k]->Fill(myvar5,mass5,aweight*weight2*ssweight*sscorr);
               if (wRegion && q_1*q_2<0)
                   h5W_AI[k]->Fill(myvar5,mass5,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h5ell_OS[k]->Fill(myvar5,mass5,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h5ell_SS[k]->Fill(myvar5,mass5,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_ell)
                   h5ell_AI[k]->Fill(myvar5,mass5,aweight*weight2*ssweight*sscorr);
           }

           bool category_6=true;
           if (category_6){
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h6tau_OS[k]->Fill(myvar6,mass6,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h6tau_SS[k]->Fill(myvar6,mass6,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_tau)
                   h6tau_AI[k]->Fill(myvar6,mass6,aweight*weight2*ssweight*sscorr);
               if (wRegion && q_1*q_2<0)
                   h6W_AI[k]->Fill(myvar6,mass6,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h6ell_OS[k]->Fill(myvar6,mass6,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h6ell_SS[k]->Fill(myvar6,mass6,aweight*weight2*ssweight*sscorr);
               if (antiisoRegion && q_1*q_2>0 && is_ell)
                   h6ell_AI[k]->Fill(myvar6,mass6,aweight*weight2*ssweight*sscorr);
           }

           bool category_7=true;
           if (category_7){
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h7tau_OS[k]->Fill(myvar7,mass7,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h7tau_SS[k]->Fill(myvar7,mass7,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && q_1*q_2>0 && is_tau)
                   h7tau_AI[k]->Fill(myvar7,mass7,aweight*weight2*ssweight*sscorr);
               if (wRegion && q_1*q_2<0)
                   h7W_AI[k]->Fill(myvar7,mass7,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h7ell_OS[k]->Fill(myvar7,mass7,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h7ell_SS[k]->Fill(myvar7,mass7,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && q_1*q_2>0 && is_ell)
                   h7ell_AI[k]->Fill(myvar7,mass7,aweight*weight2*ssweight*sscorr);
           }

           bool category_8=true;
           if (category_8){
               if (signalRegion && q_1*q_2<0 && is_tau)
                   h8tau_OS[k]->Fill(myvar8,mass8,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_tau)
                   h8tau_SS[k]->Fill(myvar8,mass8,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && q_1*q_2>0 && is_tau)
                   h8tau_AI[k]->Fill(myvar8,mass8,aweight*weight2*ssweight*sscorr);
               if (wRegion && q_1*q_2<0)
                   h8W_AI[k]->Fill(myvar8,mass8,aweight*weight2);
               if (signalRegion && q_1*q_2<0 && is_ell)
                   h8ell_OS[k]->Fill(myvar8,mass8,aweight*weight2);
               if (signalRegion && q_1*q_2>0 && is_ell)
                   h8ell_SS[k]->Fill(myvar8,mass8,aweight*weight2*ssweight*sscorr);
               if (antiisoRegionVBF && q_1*q_2>0 && is_ell)
                   h8ell_AI[k]->Fill(myvar8,mass8,aweight*weight2*ssweight*sscorr);
           }
	} // end of loop over nbhist

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    TString postfix="";
    TString strL="L";
    TString strT="T";
    TDirectory *OS0jet =fout->mkdir("em_0jet");
    OS0jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h0tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h0tau_OS[k]->Write();
          h0ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h0ell_OS[k]->Write();
       }
       else{
	  h0tau_OS[k]->Add(h0ell_OS[k]);
          h0tau_OS[k]->SetName(name.c_str()+postfix);
	  h0tau_OS[k]->Write();
       }
    }
    TDirectory *SS0jet =fout->mkdir("SS0jet");
    SS0jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h0tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h0tau_SS[k]->Write();
          h0ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h0ell_SS[k]->Write();
       }
       else{
          h0tau_SS[k]->Add(h0ell_SS[k]);
          h0tau_SS[k]->SetName(name.c_str()+postfix);
          h0tau_SS[k]->Write();
       }
    }
    TDirectory *AI0jet =fout->mkdir("AI0jet");
    AI0jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h0tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h0tau_AI[k]->Write();
          h0ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h0ell_AI[k]->Write();
       }
       else{
          h0tau_AI[k]->Add(h0ell_AI[k]);
          h0tau_AI[k]->SetName(name.c_str()+postfix);
          h0tau_AI[k]->Write();
       }
    }
    TDirectory *AIW0jet =fout->mkdir("W0jet");
    AIW0jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="W"){
          h0W_AI[k]->SetName(name.c_str()+postfix);
          h0W_AI[k]->Write();
       }
    }


    TDirectory *OS1jet =fout->mkdir("em_boosted");
    OS1jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h1tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h1tau_OS[k]->Write();
          h1ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h1ell_OS[k]->Write();
       }
       else{
          h1tau_OS[k]->Add(h1ell_OS[k]);
          h1tau_OS[k]->SetName(name.c_str()+postfix);
          h1tau_OS[k]->Write();
       }
    }

    TDirectory *SS1jet =fout->mkdir("SSboosted");
    SS1jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h1tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h1tau_SS[k]->Write();
          h1ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h1ell_SS[k]->Write();
       }
       else{
          h1tau_SS[k]->Add(h1ell_SS[k]);
          h1tau_SS[k]->SetName(name.c_str()+postfix);
          h1tau_SS[k]->Write();
       }
    }
    TDirectory *AI1jet =fout->mkdir("AIboosted");
    AI1jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h1tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h1tau_AI[k]->Write();
          h1ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h1ell_AI[k]->Write();
       }
       else{
          h1tau_AI[k]->Add(h1ell_AI[k]);
          h1tau_AI[k]->SetName(name.c_str()+postfix);
          h1tau_AI[k]->Write();
       }
    }
    TDirectory *AIW1jet =fout->mkdir("Wboosted");
    AIW1jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="W"){
          h1W_AI[k]->SetName(name.c_str()+postfix);
          h1W_AI[k]->Write();
       }
    }

    TDirectory *OS2jet =fout->mkdir("em_vbf");
    OS2jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h2tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h2tau_OS[k]->Write();
          h2ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h2ell_OS[k]->Write();
       }
       else{
          h2tau_OS[k]->Add(h2ell_OS[k]);
          h2tau_OS[k]->SetName(name.c_str()+postfix);
          h2tau_OS[k]->Write();
       }
    }

    TDirectory *SS2jet =fout->mkdir("SSvbf");
    SS2jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h2tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h2tau_SS[k]->Write();
          h2ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h2ell_SS[k]->Write();
       }
       else{
          h2tau_SS[k]->Add(h2ell_SS[k]);
          h2tau_SS[k]->SetName(name.c_str()+postfix);
          h2tau_SS[k]->Write();
       }
    }
    TDirectory *AI2jet =fout->mkdir("AIvbf");
    AI2jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h2tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h2tau_AI[k]->Write();
          h2ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h2ell_AI[k]->Write();
       }
       else{
          h2tau_AI[k]->Add(h2ell_AI[k]);
          h2tau_AI[k]->SetName(name.c_str()+postfix);
          h2tau_AI[k]->Write();
       }
    }
    TDirectory *AIW2jet =fout->mkdir("Wvbf");
    AIW2jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="W"){
          h2W_AI[k]->SetName(name.c_str()+postfix);
          h2W_AI[k]->Write();
       }
    }

    TDirectory *OS3jet =fout->mkdir("em_0jetlow");
    OS3jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h3tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h3tau_OS[k]->Write();
          h3ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h3ell_OS[k]->Write();
       }
       else{
          h3tau_OS[k]->Add(h3ell_OS[k]);
          h3tau_OS[k]->SetName(name.c_str()+postfix);
          h3tau_OS[k]->Write();
       }
    }

    TDirectory *SS3jet =fout->mkdir("SS0jetlow");
    SS3jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h3tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h3tau_SS[k]->Write();
          h3ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h3ell_SS[k]->Write();
       }
       else{
          h3tau_SS[k]->Add(h3ell_SS[k]);
          h3tau_SS[k]->SetName(name.c_str()+postfix);
          h3tau_SS[k]->Write();
       }
    }
    TDirectory *AI3jet =fout->mkdir("AI0jetlow");
    AI3jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h3tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h3tau_AI[k]->Write();
          h3ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h3ell_AI[k]->Write();
       }
       else{
          h3tau_AI[k]->Add(h3ell_AI[k]);
          h3tau_AI[k]->SetName(name.c_str()+postfix);
          h3tau_AI[k]->Write();
       }
    }
    TDirectory *AIW3jet =fout->mkdir("W0jetlow");
    AIW3jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="W"){
          h3W_AI[k]->SetName(name.c_str()+postfix);
          h3W_AI[k]->Write();
       }
    }

    TDirectory *OS4jet =fout->mkdir("em_0jethigh");
    OS4jet->cd();
    h4_ttcontamination->SetName("ttcontamination");
    h4_ttcontamination->Write();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h4tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h4tau_OS[k]->Write();
          h4ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h4ell_OS[k]->Write();
       }
       else{
          h4tau_OS[k]->Add(h4ell_OS[k]);
          h4tau_OS[k]->SetName(name.c_str()+postfix);
          h4tau_OS[k]->Write();
       }
    }

    TDirectory *SS4jet =fout->mkdir("SS0jethigh");
    SS4jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h4tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h4tau_SS[k]->Write();
          h4ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h4ell_SS[k]->Write();
       }
       else{
          h4tau_SS[k]->Add(h4ell_SS[k]);
          h4tau_SS[k]->SetName(name.c_str()+postfix);
          h4tau_SS[k]->Write();
       }
    }
    TDirectory *AI4jet =fout->mkdir("AI0jethigh");
    AI4jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h4tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h4tau_AI[k]->Write();
          h4ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h4ell_AI[k]->Write();
       }
       else{
          h4tau_AI[k]->Add(h4ell_AI[k]);
          h4tau_AI[k]->SetName(name.c_str()+postfix);
          h4tau_AI[k]->Write();
       }
    }
    TDirectory *AIW4jet =fout->mkdir("W0jethigh");
    AIW4jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="W"){
          h4W_AI[k]->SetName(name.c_str()+postfix);
          h4W_AI[k]->Write();
       }
    }

    TDirectory *OS5jet =fout->mkdir("em_boosted1");
    OS5jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h5tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h5tau_OS[k]->Write();
          h5ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h5ell_OS[k]->Write();
       }
       else{
          h5tau_OS[k]->Add(h5ell_OS[k]);
          h5tau_OS[k]->SetName(name.c_str()+postfix);
          h5tau_OS[k]->Write();
       }
    }

    TDirectory *SS5jet =fout->mkdir("SSboosted1");
    SS5jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h5tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h5tau_SS[k]->Write();
          h5ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h5ell_SS[k]->Write();
       }
       else{
          h5tau_SS[k]->Add(h5ell_SS[k]);
          h5tau_SS[k]->SetName(name.c_str()+postfix);
          h5tau_SS[k]->Write();
       }
    }
    TDirectory *AI5jet =fout->mkdir("AIboosted1");
    AI5jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h5tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h5tau_AI[k]->Write();
          h5ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h5ell_AI[k]->Write();
       }
       else{
          h5tau_AI[k]->Add(h5ell_AI[k]);
          h5tau_AI[k]->SetName(name.c_str()+postfix);
          h5tau_AI[k]->Write();
       }
    }
    TDirectory *AIW5jet =fout->mkdir("Wboosted1");
    AIW5jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="W"){
          h5W_AI[k]->SetName(name.c_str()+postfix);
          h5W_AI[k]->Write();
       }
    }

    TDirectory *OS6jet =fout->mkdir("em_boosted2");
    OS6jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h6tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h6tau_OS[k]->Write();
          h6ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h6ell_OS[k]->Write();
       }
       else{
          h6tau_OS[k]->Add(h6ell_OS[k]);
          h6tau_OS[k]->SetName(name.c_str()+postfix);
          h6tau_OS[k]->Write();
       }
    }

    TDirectory *SS6jet =fout->mkdir("SSboosted2");
    SS6jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h6tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h6tau_SS[k]->Write();
          h6ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h6ell_SS[k]->Write();
       }
       else{
          h6tau_SS[k]->Add(h6ell_SS[k]);
          h6tau_SS[k]->SetName(name.c_str()+postfix);
          h6tau_SS[k]->Write();
       }
    }

    TDirectory *AI6jet =fout->mkdir("AIboosted2");
    AI6jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h6tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h6tau_AI[k]->Write();
          h6ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h6ell_AI[k]->Write();
       }
       else{
          h6tau_AI[k]->Add(h6ell_AI[k]);
          h6tau_AI[k]->SetName(name.c_str()+postfix);
          h6tau_AI[k]->Write();
       }
    }
    TDirectory *AIW6jet =fout->mkdir("Wboosted2");
    AIW6jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="W"){
          h6W_AI[k]->SetName(name.c_str()+postfix);
          h6W_AI[k]->Write();
       }
    }

    TDirectory *OS7jet =fout->mkdir("em_vbflow");
    OS7jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h7tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h7tau_OS[k]->Write();
          h7ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h7ell_OS[k]->Write();
       }
       else{
          h7tau_OS[k]->Add(h7ell_OS[k]);
          h7tau_OS[k]->SetName(name.c_str()+postfix);
          h7tau_OS[k]->Write();
       }
    }

    TDirectory *SS7jet =fout->mkdir("SSvbflow");
    SS7jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h7tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h7tau_SS[k]->Write();
          h7ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h7ell_SS[k]->Write();
       }
       else{
          h7tau_SS[k]->Add(h7ell_SS[k]);
          h7tau_SS[k]->SetName(name.c_str()+postfix);
          h7tau_SS[k]->Write();
       }
    }
    TDirectory *AI7jet =fout->mkdir("AIvbflow");
    AI7jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h7tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h7tau_AI[k]->Write();
          h7ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h7ell_AI[k]->Write();
       }
       else{
          h7tau_AI[k]->Add(h7ell_AI[k]);
          h7tau_AI[k]->SetName(name.c_str()+postfix);
          h7tau_AI[k]->Write();
       }
    }
    TDirectory *AIW7jet =fout->mkdir("Wvbflow");
    AIW7jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="W"){
          h7W_AI[k]->SetName(name.c_str()+postfix);
          h7W_AI[k]->Write();
       }
    }

    TDirectory *OS8jet =fout->mkdir("em_vbfhigh");
    OS8jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h8tau_OS[k]->SetName(name.c_str()+strT+postfix);
          h8tau_OS[k]->Write();
          h8ell_OS[k]->SetName(name.c_str()+strL+postfix);
          h8ell_OS[k]->Write();
       }
       else{
          h8tau_OS[k]->Add(h8ell_OS[k]);
          h8tau_OS[k]->SetName(name.c_str()+postfix);
          h8tau_OS[k]->Write();
       }
    }

    TDirectory *SS8jet =fout->mkdir("SSvbfhigh");
    SS8jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h8tau_SS[k]->SetName(name.c_str()+strT+postfix);
          h8tau_SS[k]->Write();
          h8ell_SS[k]->SetName(name.c_str()+strL+postfix);
          h8ell_SS[k]->Write();
       }
       else{
          h8tau_SS[k]->Add(h8ell_SS[k]);
          h8tau_SS[k]->SetName(name.c_str()+postfix);
          h8tau_SS[k]->Write();
       }
    }
    TDirectory *AI8jet =fout->mkdir("AIvbfhigh");
    AI8jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="DY" or name=="Z" or name=="VV" or name=="ST" or name=="TT"){
          h8tau_AI[k]->SetName(name.c_str()+strT+postfix);
          h8tau_AI[k]->Write();
          h8ell_AI[k]->SetName(name.c_str()+strL+postfix);
          h8ell_AI[k]->Write();
       }
       else{
          h8tau_AI[k]->Add(h8ell_AI[k]);
          h8tau_AI[k]->SetName(name.c_str()+postfix);
          h8tau_AI[k]->Write();
       }
    }
    TDirectory *AIW8jet =fout->mkdir("Wvbfhigh");
    AIW8jet->cd();
    for (int k=0; k<nbhist; ++k){
       postfix="";
       if (name=="W"){
          h8W_AI[k]->SetName(name.c_str()+postfix);
          h8W_AI[k]->Write();
       }
    }

    fout->Close();
    cout<<h0tau_OS[0]->Integral()<<endl;
} 


