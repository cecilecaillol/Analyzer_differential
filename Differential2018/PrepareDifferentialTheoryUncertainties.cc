#include <TH2.h>



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
#include "LumiReweightingStandAlone.h"
#include "tr_Tree.h"
#include "ComputeWG1Unc.h"
#include "qq2Hqq_uncert_scheme.h"

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("demo/tr_tree");
    arbre->SetBranchAddress("Rivet_higgsPt", &Rivet_higgsPt);
    arbre->SetBranchAddress("Rivet_njets", &Rivet_njets);
    arbre->SetBranchAddress("Rivet_stage1cat", &Rivet_stage1cat);
    arbre->SetBranchAddress("Rivet_stage1cat_fine", &Rivet_stage1cat_fine);
    arbre->SetBranchAddress("Rivet_jetPt", &Rivet_jetPt);
    arbre->SetBranchAddress("Rivet_mjj", &Rivet_mjj);
    arbre->SetBranchAddress("muR1muF1", &muR1muF1);
    arbre->SetBranchAddress("muR0p5muF0p5", &muR0p5muF0p5);
    arbre->SetBranchAddress("muR2muF2", &muR2muF2);
    arbre->SetBranchAddress("fulltau1phi", &fulltau1phi);
    arbre->SetBranchAddress("fulltau1eta", &fulltau1eta);
    arbre->SetBranchAddress("fulltau1pt", &fulltau1pt);
    arbre->SetBranchAddress("fulltau2phi", &fulltau2phi);
    arbre->SetBranchAddress("fulltau2eta", &fulltau2eta);
    arbre->SetBranchAddress("fulltau2pt", &fulltau2pt);
    arbre->SetBranchAddress("vistau1_phi", &vistau1_phi);
    arbre->SetBranchAddress("vistau1_eta", &vistau1_eta);
    arbre->SetBranchAddress("vistau1_pt", &vistau1_pt);
    arbre->SetBranchAddress("vistau2_phi", &vistau2_phi);
    arbre->SetBranchAddress("vistau2_eta", &vistau2_eta);
    arbre->SetBranchAddress("vistau2_pt", &vistau2_pt);
    arbre->SetBranchAddress("finalstate", &finalstate);
    arbre->SetBranchAddress("dressedElectron_pt", &dressedElectron_pt);
    arbre->SetBranchAddress("dressedElectron_eta", &dressedElectron_eta);
    arbre->SetBranchAddress("dressedElectron_phi", &dressedElectron_phi);
    arbre->SetBranchAddress("dressedMuon_pt", &dressedMuon_pt);
    arbre->SetBranchAddress("dressedMuon_eta", &dressedMuon_eta);
    arbre->SetBranchAddress("dressedMuon_phi", &dressedMuon_phi);
    arbre->SetBranchAddress("genMetPt", &genMetPt);
    arbre->SetBranchAddress("genMetPhi", &genMetPhi);

    TH1D* nbevt = (TH1D*) f_Double->Get("demo/h_count_powheg");
    float ngen = nbevt->GetBinContent(1);
    float xs=1.0; float weight=1.0;
    if (sample=="ggH_htt125") {xs=48.58*0.0627; weight=xs/ngen;}
    else if (sample=="qqH_htt125") {xs=3.782*0.0627; weight=xs/ngen;}
    else if (sample=="WplusH125") {xs=0.840*0.0627; weight=xs/ngen;}
    else if (sample=="WminusH125") {xs=0.5328*0.0627; weight=xs/ngen;}
    else if (sample=="ZH125") {xs=0.7612*0.0627; weight=xs/ngen;}
    else if (sample=="GGZH125") {xs=0.1227*0.0627; weight=xs/ngen;}
    else if (sample=="GGZHLLTT125") {xs=0.1227*0.0627*3*0.033658; weight=xs/ngen;}
    else if (sample=="GGZHNNTT125") {xs=0.1227*0.0627*0.2000; weight=xs/ngen;}
    else if (sample=="GGZHQQTT125") {xs=0.1227*0.0627*0.6991; weight=xs/ngen;}
    else if (sample=="ttHTT") {xs=0.5071*0.0627; weight=xs/ngen;}
    else if (sample=="ttHTT125") {xs=0.5071*0.0627; weight=xs/ngen;}

    TFile * f_NNLOPS = new TFile("NNLOPS_reweight.root");
    TGraph * g_NNLOPS_0jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_0jet");
    TGraph * g_NNLOPS_1jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_1jet");
    TGraph * g_NNLOPS_2jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_2jet");
    TGraph * g_NNLOPS_3jet = (TGraph*) f_NNLOPS-> Get("gr_NNLOPSratio_pt_powheg_3jet");

    TH1F* h_THUggH_pth0to45 = new TH1F("h_THUggH_pth0to45","h_THUggH_pth0to45",20,0,20);
    TH1F* h_THUqqH_pth0to45 = new TH1F("h_THUqqH_pth0to45","h_THUqqH_pth0to45",22,0,22);
    TH1F* h_scale_pth0to45 = new TH1F("h_scale_pth0to45","h_scale_pth0to45",22,0,22);
    TH1F* h_THUggH_pth0to10 = new TH1F("h_THUggH_pth0to10","h_THUggH_pth0to10",20,0,20);
    TH1F* h_THUqqH_pth0to10 = new TH1F("h_THUqqH_pth0to10","h_THUqqH_pth0to10",22,0,22);
    TH1F* h_scale_pth0to10 = new TH1F("h_scale_pth0to10","h_scale_pth0to10",22,0,22);
    TH1F* h_THUggH_pth10to20 = new TH1F("h_THUggH_pth10to20","h_THUggH_pth10to20",20,0,20);
    TH1F* h_THUqqH_pth10to20 = new TH1F("h_THUqqH_pth10to20","h_THUqqH_pth10to20",22,0,22);
    TH1F* h_scale_pth10to20 = new TH1F("h_scale_pth10to20","h_scale_pth10to20",22,0,22);
    TH1F* h_THUggH_pth20to30 = new TH1F("h_THUggH_pth20to30","h_THUggH_pth20to30",20,0,20);
    TH1F* h_THUqqH_pth20to30 = new TH1F("h_THUqqH_pth20to30","h_THUqqH_pth20to30",22,0,22);
    TH1F* h_scale_pth20to30 = new TH1F("h_scale_pth20to30","h_scale_pth20to30",22,0,22);
    TH1F* h_THUggH_pth30to45 = new TH1F("h_THUggH_pth30to45","h_THUggH_pth30to45",20,0,20);
    TH1F* h_THUqqH_pth30to45 = new TH1F("h_THUqqH_pth30to45","h_THUqqH_pth30to45",22,0,22);
    TH1F* h_scale_pth30to45 = new TH1F("h_scale_pth30to45","h_scale_pth30to45",22,0,22);
    TH1F* h_THUggH_pth45to60 = new TH1F("h_THUggH_pth45to60","h_THUggH_pth45to60",20,0,20);
    TH1F* h_THUqqH_pth45to60 = new TH1F("h_THUqqH_pth45to60","h_THUqqH_pth45to60",22,0,22);
    TH1F* h_scale_pth45to60 = new TH1F("h_scale_pth45to60","h_scale_pth45to60",22,0,22);
    TH1F* h_THUggH_pth60to80 = new TH1F("h_THUggH_pth60to80","h_THUggH_pth60to80",20,0,20);
    TH1F* h_THUqqH_pth60to80 = new TH1F("h_THUqqH_pth60to80","h_THUqqH_pth60to80",22,0,22);
    TH1F* h_scale_pth60to80 = new TH1F("h_scale_pth60to80","h_scale_pth60to80",22,0,22);
    TH1F* h_THUggH_pth45to80 = new TH1F("h_THUggH_pth45to80","h_THUggH_pth45to80",20,0,20);
    TH1F* h_THUqqH_pth45to80 = new TH1F("h_THUqqH_pth45to80","h_THUqqH_pth45to80",22,0,22);
    TH1F* h_scale_pth45to80 = new TH1F("h_scale_pth45to80","h_scale_pth45to80",22,0,22);
    TH1F* h_THUggH_pth80to120 = new TH1F("h_THUggH_pth80to120","h_THUggH_pth80to120",20,0,20);
    TH1F* h_THUqqH_pth80to120 = new TH1F("h_THUqqH_pth80to120","h_THUqqH_pth80to120",22,0,22);
    TH1F* h_scale_pth80to120 = new TH1F("h_scale_pth80to120","h_scale_pth80to120",22,0,22);
    TH1F* h_THUggH_pth120to200 = new TH1F("h_THUggH_pth120to200","h_THUggH_pth120to200",20,0,20);
    TH1F* h_THUqqH_pth120to200 = new TH1F("h_THUqqH_pth120to200","h_THUqqH_pth120to200",22,0,22);
    TH1F* h_scale_pth120to200 = new TH1F("h_scale_pth120to200","h_scale_pth120to200",22,0,22);
    TH1F* h_THUggH_pth200to350 = new TH1F("h_THUggH_pth200to350","h_THUggH_pth200to350",20,0,20);
    TH1F* h_THUqqH_pth200to350 = new TH1F("h_THUqqH_pth200to350","h_THUqqH_pth200to350",22,0,22);
    TH1F* h_scale_pth200to350 = new TH1F("h_scale_pth200to350","h_scale_pth200to350",22,0,22);
    TH1F* h_THUggH_pth350to450 = new TH1F("h_THUggH_pth350to450","h_THUggH_pth350to450",20,0,20);
    TH1F* h_THUqqH_pth350to450 = new TH1F("h_THUqqH_pth350to450","h_THUqqH_pth350to450",22,0,22);
    TH1F* h_scale_pth350to450 = new TH1F("h_scale_pth350to450","h_scale_pth350to450",22,0,22);
    TH1F* h_THUggH_pthgt450 = new TH1F("h_THUggH_pthgt450","h_THUggH_pthgt450",20,0,20);
    TH1F* h_THUqqH_pthgt450 = new TH1F("h_THUqqH_pthgt450","h_THUqqH_pthgt450",22,0,22);
    TH1F* h_scale_pthgt450 = new TH1F("h_scale_pthgt450","h_scale_pthgt450",22,0,22);

    TH1F* h_THUggH_njets0 = new TH1F("h_THUggH_njets0","h_THUggH_njets0",20,0,20);
    TH1F* h_THUqqH_njets0 = new TH1F("h_THUqqH_njets0","h_THUqqH_njets0",22,0,22);
    TH1F* h_scale_njets0 = new TH1F("h_scale_njets0","h_scale_njets0",22,0,22);
    TH1F* h_THUggH_njets1 = new TH1F("h_THUggH_njets1","h_THUggH_njets1",20,0,20);
    TH1F* h_THUqqH_njets1 = new TH1F("h_THUqqH_njets1","h_THUqqH_njets1",22,0,22);
    TH1F* h_scale_njets1 = new TH1F("h_scale_njets1","h_scale_njets1",22,0,22);
    TH1F* h_THUggH_njets2 = new TH1F("h_THUggH_njets2","h_THUggH_njets2",20,0,20);
    TH1F* h_THUqqH_njets2 = new TH1F("h_THUqqH_njets2","h_THUqqH_njets2",22,0,22);
    TH1F* h_scale_njets2 = new TH1F("h_scale_njets2","h_scale_njets2",22,0,22);
    TH1F* h_THUggH_njets3 = new TH1F("h_THUggH_njets3","h_THUggH_njets3",20,0,20);
    TH1F* h_THUqqH_njets3 = new TH1F("h_THUqqH_njets3","h_THUqqH_njets3",22,0,22);
    TH1F* h_scale_njets3 = new TH1F("h_scale_njets3","h_scale_njets3",22,0,22);
    TH1F* h_THUggH_njets4 = new TH1F("h_THUggH_njets4","h_THUggH_njets4",20,0,20);
    TH1F* h_THUqqH_njets4 = new TH1F("h_THUqqH_njets4","h_THUqqH_njets4",22,0,22);
    TH1F* h_scale_njets4 = new TH1F("h_scale_njets4","h_scale_njets4",22,0,22);

    TH1F* h_THUggH_j1pt30to60 = new TH1F("h_THUggH_j1pt30to60","h_THUggH_j1pt30to60",20,0,20);
    TH1F* h_THUqqH_j1pt30to60 = new TH1F("h_THUqqH_j1pt30to60","h_THUqqH_j1pt30to60",22,0,22);
    TH1F* h_scale_j1pt30to60 = new TH1F("h_scale_j1pt30to60","h_scale_j1pt30to60",22,0,22);
    TH1F* h_THUggH_j1pt60to120 = new TH1F("h_THUggH_j1pt60to120","h_THUggH_j1pt60to120",20,0,20);
    TH1F* h_THUqqH_j1pt60to120 = new TH1F("h_THUqqH_j1pt60to120","h_THUqqH_j1pt60to120",22,0,22);
    TH1F* h_scale_j1pt60to120 = new TH1F("h_scale_j1pt60to120","h_scale_j1pt60to120",22,0,22);
    TH1F* h_THUggH_j1pt120to200 = new TH1F("h_THUggH_j1pt120to200","h_THUggH_j1pt120to200",20,0,20);
    TH1F* h_THUqqH_j1pt120to200 = new TH1F("h_THUqqH_j1pt120to200","h_THUqqH_j1pt120to200",22,0,22);
    TH1F* h_scale_j1pt120to200 = new TH1F("h_scale_j1pt120to200","h_scale_j1pt120to200",22,0,22);
    TH1F* h_THUggH_j1pt200to350 = new TH1F("h_THUggH_j1pt200to350","h_THUggH_j1pt200to350",20,0,20);
    TH1F* h_THUqqH_j1pt200to350 = new TH1F("h_THUqqH_j1pt200to350","h_THUqqH_j1pt200to350",22,0,22);
    TH1F* h_scale_j1pt200to350 = new TH1F("h_scale_j1pt200to350","h_scale_j1pt200to350",22,0,22);
    TH1F* h_THUggH_j1ptgt350 = new TH1F("h_THUggH_j1ptgt350","h_THUggH_j1ptgt350",20,0,20);
    TH1F* h_THUqqH_j1ptgt350 = new TH1F("h_THUqqH_j1ptgt350","h_THUqqH_j1ptgt350",22,0,22);
    TH1F* h_scale_j1ptgt350 = new TH1F("h_scale_j1ptgt350","h_scale_j1ptgt350",22,0,22);

    Int_t nentries_wtn = (Int_t) arbre->GetEntries();
    for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	float nnlops_weight=1.0;
        if (name=="ggH_htt125"){
          if (Rivet_njets==0) nnlops_weight= g_NNLOPS_0jet->Eval(min(Rivet_higgsPt,float(125.0)));
          if (Rivet_njets==1) nnlops_weight= g_NNLOPS_1jet->Eval(min(Rivet_higgsPt,float(625.0)));
          if (Rivet_njets==2) nnlops_weight= g_NNLOPS_2jet->Eval(min(Rivet_higgsPt,float(800.0)));
          if (Rivet_njets>=3) nnlops_weight= g_NNLOPS_3jet->Eval(min(Rivet_higgsPt,float(925.0)));
	}
        NumV WG1unc = qcd_ggF_uncert_2017(Rivet_njets, Rivet_higgsPt, Rivet_stage1cat);

	TLorentzVector mymet;
	TLorentzVector myelectron;
	TLorentzVector mymuon;
	TLorentzVector mytau;
        TLorentzVector mytau1;
        TLorentzVector mytau2;
	mymet.SetPtEtaPhiM(genMetPt,0,genMetPhi,0);
	myelectron.SetPtEtaPhiM(dressedElectron_pt,dressedElectron_eta,dressedElectron_phi,0);
        mymuon.SetPtEtaPhiM(dressedMuon_pt,dressedMuon_eta,dressedMuon_phi,0);
        mytau.SetPtEtaPhiM(vistau1_pt,vistau1_eta,vistau1_phi,0);
        mytau1.SetPtEtaPhiM(vistau1_pt,vistau1_eta,vistau1_phi,0);
        mytau2.SetPtEtaPhiM(vistau2_pt,vistau2_eta,vistau2_phi,0);
	if (finalstate==2 and myelectron.DeltaR(mytau1)<myelectron.DeltaR(mytau2)) mytau=mytau2;
        if (finalstate==2 and myelectron.DeltaR(mytau1)>myelectron.DeltaR(mytau2)) mytau=mytau1;
        if (finalstate==3 and mymuon.DeltaR(mytau1)<mymuon.DeltaR(mytau2)) mytau=mytau2;
        if (finalstate==3 and mymuon.DeltaR(mytau1)>mymuon.DeltaR(mytau2)) mytau=mytau1;

	float mt_emu=-1;
	float mt_etau=-1;
	float mt_mutau=-1;
	if (finalstate==1) mt_emu=TMass_F((myelectron+mymuon).Pt(),mymet.Pt(),(myelectron+mymuon).Px(),mymet.Px(),(myelectron+mymuon).Py(),mymet.Py());
        if (finalstate==2) mt_etau=TMass_F(myelectron.Pt(),mymet.Pt(),myelectron.Px(),mymet.Px(),myelectron.Py(),mymet.Py());
        if (finalstate==3) mt_etau=TMass_F(mymuon.Pt(),mymet.Pt(),mymuon.Px(),mymet.Px(),mymuon.Py(),mymet.Py());

	bool is_fiducial=false; 
	if (finalstate==1 and myelectron.DeltaR(mymuon)>0.3 and mt_emu<60 and (dressedElectron_pt>24 or dressedMuon_pt>24) and dressedElectron_pt>15 and dressedMuon_pt>25 and fabs(dressedElectron_eta)<2.4 and fabs(dressedMuon_eta)<2.4) is_fiducial=true; //emu
        if (finalstate==2 and myelectron.DeltaR(mytau)>0.5 and mt_etau<50 and dressedElectron_pt>25 and vistau1_pt>30 and fabs(dressedElectron_eta)<2.1 and fabs(vistau1_eta)<2.3) is_fiducial=true; //etau
        if (finalstate==3 and mymuon.DeltaR(mytau)>0.5 and mt_mutau<50 and dressedMuon_pt>20 and vistau1_pt>30 and fabs(dressedMuon_eta)<2.1 and fabs(vistau1_eta)<2.3) is_fiducial=true; //mutau
        if (finalstate==4 and mytau1.DeltaR(mytau2)>0.5 and vistau1_pt>40 and vistau2_pt>40 and fabs(vistau1_eta)<2.1 and fabs(vistau2_eta)<2.1 and Rivet_njets>0) is_fiducial=true; //tautau
	if (!is_fiducial) continue;

	// PTH
	if (Rivet_higgsPt>=0 and Rivet_higgsPt<45){
	  h_THUggH_pth0to45->Fill(0.,nnlops_weight);
	  for (int j=0; j<9; ++j){
	     h_THUggH_pth0to45->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth0to45->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
	  }
          h_THUqqH_pth0to45->Fill(0.,1.0);
          h_scale_pth0to45->Fill(0.,nnlops_weight);
	  h_scale_pth0to45->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth0to45->Fill(2.,muR2muF2*nnlops_weight);
	}
        if (Rivet_higgsPt>=0 and Rivet_higgsPt<10){
          h_THUggH_pth0to10->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pth0to10->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth0to10->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pth0to10->Fill(0.,1.0);
          h_scale_pth0to10->Fill(0.,nnlops_weight);
          h_scale_pth0to10->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth0to10->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_higgsPt>=10 and Rivet_higgsPt<20){
          h_THUggH_pth10to20->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pth10to20->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth10to20->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pth10to20->Fill(0.,1.0);
          h_scale_pth10to20->Fill(0.,nnlops_weight);
          h_scale_pth10to20->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth10to20->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_higgsPt>=20 and Rivet_higgsPt<30){
          h_THUggH_pth20to30->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pth20to30->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth20to30->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pth20to30->Fill(0.,1.0);
          h_scale_pth20to30->Fill(0.,nnlops_weight);
          h_scale_pth20to30->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth20to30->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_higgsPt>=30 and Rivet_higgsPt<45){
          h_THUggH_pth30to45->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pth30to45->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth30to45->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pth30to45->Fill(0.,1.0);
          h_scale_pth30to45->Fill(0.,nnlops_weight);
          h_scale_pth30to45->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth30to45->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_higgsPt>=45 and Rivet_higgsPt<60){
          h_THUggH_pth45to60->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pth45to60->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth45to60->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pth45to60->Fill(0.,1.0);
          h_scale_pth45to60->Fill(0.,nnlops_weight);
          h_scale_pth45to60->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth45to60->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_higgsPt>=60 and Rivet_higgsPt<80){
          h_THUggH_pth60to80->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pth60to80->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth60to80->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pth60to80->Fill(0.,1.0);
          h_scale_pth60to80->Fill(0.,nnlops_weight);
          h_scale_pth60to80->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth60to80->Fill(2.,muR2muF2*nnlops_weight);
        }

        if (Rivet_higgsPt>=45 and Rivet_higgsPt<80){
          h_THUggH_pth45to80->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pth45to80->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth45to80->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pth45to80->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_pth45to80->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_pth45to80->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_pth45to80->Fill(0.,nnlops_weight);
          h_scale_pth45to80->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth45to80->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_higgsPt>=80 and Rivet_higgsPt<120){
          h_THUggH_pth80to120->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pth80to120->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth80to120->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pth80to120->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_pth80to120->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_pth80to120->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_pth80to120->Fill(0.,nnlops_weight);
          h_scale_pth80to120->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth80to120->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_higgsPt>=120 and Rivet_higgsPt<200){
          h_THUggH_pth120to200->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pth120to200->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth120to200->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pth120to200->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_pth120to200->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_pth120to200->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_pth120to200->Fill(0.,nnlops_weight);
          h_scale_pth120to200->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth120to200->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_higgsPt>=200 and Rivet_higgsPt<350){
          h_THUggH_pth200to350->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pth200to350->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth200to350->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pth200to350->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_pth200to350->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_pth200to350->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_pth200to350->Fill(0.,nnlops_weight);
          h_scale_pth200to350->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth200to350->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_higgsPt>=350 and Rivet_higgsPt<450){
          h_THUggH_pth350to450->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pth350to450->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pth350to450->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pth350to450->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_pth350to450->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_pth350to450->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_pth350to450->Fill(0.,nnlops_weight);
          h_scale_pth350to450->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pth350to450->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_higgsPt>=450){
          h_THUggH_pthgt450->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_pthgt450->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_pthgt450->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_pthgt450->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_pthgt450->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_pthgt450->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_pthgt450->Fill(0.,nnlops_weight);
          h_scale_pthgt450->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_pthgt450->Fill(2.,muR2muF2*nnlops_weight);
        }

        if (Rivet_njets==0){
          h_THUggH_njets0->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_njets0->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_njets0->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_njets0->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_njets0->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_njets0->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_njets0->Fill(0.,nnlops_weight);
          h_scale_njets0->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_njets0->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_njets==1){
          h_THUggH_njets1->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_njets1->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_njets1->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_njets1->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_njets1->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_njets1->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_njets1->Fill(0.,nnlops_weight);
          h_scale_njets1->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_njets1->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_njets==2){
          h_THUggH_njets2->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_njets2->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_njets2->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_njets2->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_njets2->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_njets2->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_njets2->Fill(0.,nnlops_weight);
          h_scale_njets2->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_njets2->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_njets==3){
          h_THUggH_njets3->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_njets3->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_njets3->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_njets3->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_njets3->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_njets3->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_njets3->Fill(0.,nnlops_weight);
          h_scale_njets3->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_njets3->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_njets>=4){
          h_THUggH_njets4->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_njets4->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_njets4->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_njets4->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_njets4->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_njets4->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_njets4->Fill(0.,nnlops_weight);
          h_scale_njets4->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_njets4->Fill(2.,muR2muF2*nnlops_weight);
        }


        if (Rivet_jetPt>=30 and Rivet_jetPt<60){
          h_THUggH_j1pt30to60->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_j1pt30to60->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_j1pt30to60->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_j1pt30to60->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_j1pt30to60->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_j1pt30to60->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_j1pt30to60->Fill(0.,nnlops_weight);
          h_scale_j1pt30to60->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_j1pt30to60->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_jetPt>=60 and Rivet_jetPt<120){
          h_THUggH_j1pt60to120->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_j1pt60to120->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_j1pt60to120->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_j1pt60to120->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_j1pt60to120->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_j1pt60to120->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_j1pt60to120->Fill(0.,nnlops_weight);
          h_scale_j1pt60to120->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_j1pt60to120->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_jetPt>=120 and Rivet_jetPt<200){
          h_THUggH_j1pt120to200->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_j1pt120to200->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_j1pt120to200->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_j1pt120to200->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_j1pt120to200->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_j1pt120to200->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_j1pt120to200->Fill(0.,nnlops_weight);
          h_scale_j1pt120to200->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_j1pt120to200->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_jetPt>=200 and Rivet_jetPt<350){
          h_THUggH_j1pt200to350->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_j1pt200to350->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_j1pt200to350->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_j1pt200to350->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_j1pt200to350->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_j1pt200to350->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_j1pt200to350->Fill(0.,nnlops_weight);
          h_scale_j1pt200to350->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_j1pt200to350->Fill(2.,muR2muF2*nnlops_weight);
        }
        if (Rivet_jetPt>=350){
          h_THUggH_j1ptgt350->Fill(0.,nnlops_weight);
          for (int j=0; j<9; ++j){
             h_THUggH_j1ptgt350->Fill(2*j+1.,nnlops_weight*(1+WG1unc[j]));
             h_THUggH_j1ptgt350->Fill(2*j+2.,nnlops_weight*(1-WG1unc[j]));
          }
          h_THUqqH_j1ptgt350->Fill(0.,1.0);
          /*for (int j=0; j<10; ++j){
             h_THUqqH_j1ptgt350->Fill(2*j+1.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), 1.0));
             h_THUqqH_j1ptgt350->Fill(2*j+2.,vbf_uncert_stage_1_1(j, int(Rivet_stage1cat_fine), -1.0));
          }*/
          h_scale_j1ptgt350->Fill(0.,nnlops_weight);
          h_scale_j1ptgt350->Fill(1.,muR0p5muF0p5*nnlops_weight);
          h_scale_j1ptgt350->Fill(2.,muR2muF2*nnlops_weight);
        }
    }

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    h_THUggH_pth0to10->Write();
    h_THUqqH_pth0to10->Write();
    h_scale_pth0to10->Write();
    h_THUggH_pth10to20->Write();
    h_THUqqH_pth10to20->Write();
    h_scale_pth10to20->Write();
    h_THUggH_pth20to30->Write();
    h_THUqqH_pth20to30->Write();
    h_scale_pth20to30->Write();
    h_THUggH_pth30to45->Write();
    h_THUqqH_pth30to45->Write();
    h_scale_pth30to45->Write();
    h_THUggH_pth45to60->Write();
    h_THUqqH_pth45to60->Write();
    h_scale_pth45to60->Write();
    h_THUggH_pth60to80->Write();
    h_THUqqH_pth60to80->Write();
    h_scale_pth60to80->Write();

    h_THUggH_pth0to45->Write();
    h_THUqqH_pth0to45->Write();
    h_scale_pth0to45->Write();
    h_THUggH_pth45to80->Write();
    h_THUqqH_pth45to80->Write();
    h_scale_pth45to80->Write();
    h_THUggH_pth80to120->Write();
    h_THUqqH_pth80to120->Write();
    h_scale_pth80to120->Write();
    h_THUggH_pth120to200->Write();
    h_THUqqH_pth120to200->Write();
    h_scale_pth120to200->Write();
    h_THUggH_pth200to350->Write();
    h_THUqqH_pth200to350->Write();
    h_scale_pth200to350->Write();
    h_THUggH_pth350to450->Write();
    h_THUqqH_pth350to450->Write();
    h_scale_pth350to450->Write();
    h_THUggH_pthgt450->Write();
    h_THUqqH_pthgt450->Write();
    h_scale_pthgt450->Write();

    h_THUggH_njets0->Write();
    h_THUqqH_njets0->Write();
    h_scale_njets0->Write();
    h_THUggH_njets1->Write();
    h_THUqqH_njets1->Write();
    h_scale_njets1->Write();
    h_THUggH_njets2->Write();
    h_THUqqH_njets2->Write();
    h_scale_njets2->Write();
    h_THUggH_njets3->Write();
    h_THUqqH_njets3->Write();
    h_scale_njets3->Write();
    h_THUggH_njets4->Write();
    h_THUqqH_njets4->Write();
    h_scale_njets4->Write();

    h_THUggH_j1pt30to60->Write();
    h_THUqqH_j1pt30to60->Write();
    h_scale_j1pt30to60->Write();
    h_THUggH_j1pt60to120->Write();
    h_THUqqH_j1pt60to120->Write();
    h_scale_j1pt60to120->Write();
    h_THUggH_j1pt120to200->Write();
    h_THUqqH_j1pt120to200->Write();
    h_scale_j1pt120to200->Write();
    h_THUggH_j1pt200to350->Write();
    h_THUqqH_j1pt200to350->Write();
    h_scale_j1pt200to350->Write();
    h_THUggH_j1ptgt350->Write();
    h_THUqqH_j1ptgt350->Write();
    h_scale_j1ptgt350->Write();

    fout->Close();
}
