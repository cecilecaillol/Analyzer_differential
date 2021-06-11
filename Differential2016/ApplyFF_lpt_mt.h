#include "TF1.h"
#include "TFile.h"
#include "TString.h"

using namespace std;

TFile frawff("ff_files_mt_2016/uncorrected_fakefactors_mt.root");
TF1* ff_qcd_0jet=(TF1*) frawff.Get("rawFF_mt_qcd_0jet");
TF1* ff_qcd_1jet=(TF1*) frawff.Get("rawFF_mt_qcd_1jet");
TF1* ff_qcd_2jet=(TF1*) frawff.Get("rawFF_mt_qcd_2jet");
TF1* ff_w_0jet=(TF1*) frawff.Get("rawFF_mt_w_0jet");
TF1* ff_w_1jet=(TF1*) frawff.Get("rawFF_mt_w_1jet");
TF1* ff_w_2jet=(TF1*) frawff.Get("rawFF_mt_w_2jet");
TF1* ff_w_3jet=(TF1*) frawff.Get("rawFF_mt_w_3jet");
TF1* ff_tt_0jet=(TF1*) frawff.Get("mc_rawFF_mt_tt");

TF1* ff_qcd_0jet_up1=(TF1*) frawff.Get("rawFF_mt_qcd_0jet_unc1_up");
TF1* ff_qcd_1jet_up1=(TF1*) frawff.Get("rawFF_mt_qcd_1jet_unc1_up");
TF1* ff_qcd_2jet_up1=(TF1*) frawff.Get("rawFF_mt_qcd_2jet_unc1_up");
TF1* ff_w_0jet_up1=(TF1*) frawff.Get("rawFF_mt_w_0jet_unc1_up");
TF1* ff_w_1jet_up1=(TF1*) frawff.Get("rawFF_mt_w_1jet_unc1_up");
TF1* ff_w_2jet_up1=(TF1*) frawff.Get("rawFF_mt_w_2jet_unc1_up");
TF1* ff_tt_0jet_up1=(TF1*) frawff.Get("mc_rawFF_mt_tt_unc1_up");
TF1* ff_qcd_0jet_up2=(TF1*) frawff.Get("rawFF_mt_qcd_0jet_unc2_up");
TF1* ff_qcd_1jet_up2=(TF1*) frawff.Get("rawFF_mt_qcd_1jet_unc2_up");
TF1* ff_qcd_2jet_up2=(TF1*) frawff.Get("rawFF_mt_qcd_2jet_unc2_up");
TF1* ff_w_0jet_up2=(TF1*) frawff.Get("rawFF_mt_w_0jet_unc2_up");
TF1* ff_w_1jet_up2=(TF1*) frawff.Get("rawFF_mt_w_1jet_unc2_up");
TF1* ff_w_2jet_up2=(TF1*) frawff.Get("rawFF_mt_w_2jet_unc2_up");
TF1* ff_tt_0jet_up2=(TF1*) frawff.Get("mc_rawFF_mt_tt_unc2_up");
TF1* ff_qcd_0jet_down1=(TF1*) frawff.Get("rawFF_mt_qcd_0jet_unc1_down");
TF1* ff_qcd_1jet_down1=(TF1*) frawff.Get("rawFF_mt_qcd_1jet_unc1_down");
TF1* ff_qcd_2jet_down1=(TF1*) frawff.Get("rawFF_mt_qcd_2jet_unc1_down");
TF1* ff_w_0jet_down1=(TF1*) frawff.Get("rawFF_mt_w_0jet_unc1_down");
TF1* ff_w_1jet_down1=(TF1*) frawff.Get("rawFF_mt_w_1jet_unc1_down");
TF1* ff_w_2jet_down1=(TF1*) frawff.Get("rawFF_mt_w_2jet_unc1_down");
TF1* ff_tt_0jet_down1=(TF1*) frawff.Get("mc_rawFF_mt_tt_unc1_down");
TF1* ff_qcd_0jet_down2=(TF1*) frawff.Get("rawFF_mt_qcd_0jet_unc2_down");
TF1* ff_qcd_1jet_down2=(TF1*) frawff.Get("rawFF_mt_qcd_1jet_unc2_down");
TF1* ff_qcd_2jet_down2=(TF1*) frawff.Get("rawFF_mt_qcd_2jet_unc2_down");
TF1* ff_w_0jet_down2=(TF1*) frawff.Get("rawFF_mt_w_0jet_unc2_down");
TF1* ff_w_1jet_down2=(TF1*) frawff.Get("rawFF_mt_w_1jet_unc2_down");
TF1* ff_w_2jet_down2=(TF1*) frawff.Get("rawFF_mt_w_2jet_unc2_down");
TF1* ff_tt_0jet_down2=(TF1*) frawff.Get("mc_rawFF_mt_tt_unc2_down");

TFile fmvisclosure ("ff_files_mt_2016/FF_corrections_1.root");
TF1* lptclosure_w_taupt30to50=(TF1*) fmvisclosure.Get("closure_lpt_taupt30to50_mt_w");
TF1* lptclosure_w_taupt50to70=(TF1*) fmvisclosure.Get("closure_lpt_taupt50to70_mt_w");
TF1* lptclosure_w_tauptgt70=(TF1*) fmvisclosure.Get("closure_lpt_tauptgt70_mt_w");
TF1* lptclosure_qcd_taupt30to50=(TF1*) fmvisclosure.Get("closure_lpt_taupt30to50_mt_qcd");
TF1* lptclosure_qcd_taupt50to70=(TF1*) fmvisclosure.Get("closure_lpt_taupt50to70_mt_qcd");
TF1* lptclosure_qcd_tauptgt70=(TF1*) fmvisclosure.Get("closure_lpt_tauptgt70_mt_qcd");
TF1* lptclosure_tt_taupt30to50=(TF1*) fmvisclosure.Get("closure_lpt_taupt30to50_mt_ttmc");
TF1* lptclosure_tt_taupt50to70=(TF1*) fmvisclosure.Get("closure_lpt_taupt50to70_mt_ttmc");
TF1* lptclosure_tt_tauptgt70=(TF1*) fmvisclosure.Get("closure_lpt_tauptgt70_mt_ttmc");
TF1* lptclosure_w_xtrg_taupt30to50=(TF1*) fmvisclosure.Get("closure_lpt_taupt30to50_xtrg_mt_w");
TF1* lptclosure_w_xtrg_taupt50to70=(TF1*) fmvisclosure.Get("closure_lpt_taupt50to70_xtrg_mt_w");
TF1* lptclosure_w_xtrg_tauptgt70=(TF1*) fmvisclosure.Get("closure_lpt_tauptgt70_xtrg_mt_w");
TF1* lptclosure_qcd_xtrg_taupt30to50=(TF1*) fmvisclosure.Get("closure_lpt_taupt30to50_xtrg_mt_qcd");
TF1* lptclosure_qcd_xtrg_taupt50to70=(TF1*) fmvisclosure.Get("closure_lpt_taupt50to70_xtrg_mt_qcd");
TF1* lptclosure_qcd_xtrg_tauptgt70=(TF1*) fmvisclosure.Get("closure_lpt_tauptgt70_xtrg_mt_qcd");
TF1* lptclosure_tt_xtrg_taupt30to50=(TF1*) fmvisclosure.Get("closure_lpt_taupt30to50_xtrg_mt_ttmc");
TF1* lptclosure_tt_xtrg_taupt50to70=(TF1*) fmvisclosure.Get("closure_lpt_taupt50to70_xtrg_mt_ttmc");
TF1* lptclosure_tt_xtrg_tauptgt70=(TF1*) fmvisclosure.Get("closure_lpt_tauptgt70_xtrg_mt_ttmc");


TFile fosssclosure ("ff_files_mt_2016/FF_QCDcorrectionOSSS.root");
TF1* osssclosure_qcd=(TF1*) fosssclosure.Get("closure_OSSS_dr_flat_mt_qcd");
TF1* mtclosure_w=(TF1*) fosssclosure.Get("closure_mt_mt_w");
TF1* mtpthclosure_w=(TF1*) fosssclosure.Get("closure_mt_mtpth_w");

TF1* osssclosure_qcd_up1=(TF1*) fosssclosure.Get("closure_OSSS_mvis_mt_qcd_unc1_up");
TF1* mtclosure_w_up1=(TF1*) fosssclosure.Get("closure_mt_mt_w_unc1_up");
TF1* osssclosure_qcd_up2=(TF1*) fosssclosure.Get("closure_OSSS_mvis_mt_qcd_unc2_up");
TF1* mtclosure_w_up2=(TF1*) fosssclosure.Get("closure_mt_mt_w_unc2_up");
TF1* osssclosure_qcd_down1=(TF1*) fosssclosure.Get("closure_OSSS_mvis_mt_qcd_unc1_down");
TF1* mtclosure_w_down1=(TF1*) fosssclosure.Get("closure_mt_mt_w_unc1_down");
TF1* osssclosure_qcd_down2=(TF1*) fosssclosure.Get("closure_OSSS_mvis_mt_qcd_unc2_down");
TF1* mtclosure_w_down2=(TF1*) fosssclosure.Get("closure_mt_mt_w_unc2_down");


float get_raw_FF(float pt, TF1* fct){
  float ff=1.0;
  ff=fct->Eval(pt);
  if (ff<0) ff=0;
  //if (pt>100) ff=fct->Eval(100);
  return ff;
  //if (ff<0) return 0.0;
  //else if (ff>2) return 2.0;
  //else return ff;
}

float get_mvis_closure(float mvis, TF1* fct){
  float corr=1.0;
  corr=fct->Eval(mvis);
  if (mvis>250) corr=fct->Eval(250);
  return corr;
  //if (corr<0 or corr>2) return 1.0;
  //else return corr;
}

float get_lpt_closure(float lpt, TF1* fct){
  float corr=1.0;
  corr=fct->Eval(lpt);
  if (lpt>150) corr=fct->Eval(150);
  if (corr<0 or corr>2) return 1.0;
  else return corr;
}

float get_mt_closure(float mt, TF1* fct){
  float corr=1.0;
  corr=fct->Eval(mt);
  if (corr<0 or corr>2) return 1.0;
  else return corr;
}

float get_mtpth_closure(float pth, TF1* fct){
  float corr=1.0;
  corr=fct->Eval(pth);
  if (pth>200) corr=fct->Eval(200.0);
  return corr;
}

float get_ff(float pt, float mt, float mvis, float msv, float lpt, float met, float pth, int njets, bool xtrg, float frac_tt, float frac_qcd, float frac_w, TString shift){
   float ff_qcd=1.0;
   float ff_w=0;
   float ff_tt=1.0;

   // Raw FF
   if (njets==0){
	ff_qcd=get_raw_FF(pt,ff_qcd_0jet);
	if (shift=="ff_qcd_up1" or shift=="ff_qcd_up1_0jet") ff_qcd=get_raw_FF(pt,ff_qcd_0jet_up1);
        else if (shift=="ff_qcd_up2" or shift=="ff_qcd_up2_0jet") ff_qcd=get_raw_FF(pt,ff_qcd_0jet_up2);
        else if (shift=="ff_qcd_down1" or shift=="ff_qcd_down1_0jet") ff_qcd=get_raw_FF(pt,ff_qcd_0jet_down1);
        else if (shift=="ff_qcd_down2" or shift=="ff_qcd_down2_0jet") ff_qcd=get_raw_FF(pt,ff_qcd_0jet_down2);
	ff_w=get_raw_FF(pt,ff_w_0jet);
        if (shift=="ff_w_up1" or shift=="ff_w_up1_0jet") ff_w=get_raw_FF(pt,ff_w_0jet_up1);
        else if (shift=="ff_w_up2" or shift=="ff_w_up2_0jet") ff_w=get_raw_FF(pt,ff_w_0jet_up2);
        else if (shift=="ff_w_down1" or shift=="ff_w_down1_0jet") ff_w=get_raw_FF(pt,ff_w_0jet_down1);
        else if (shift=="ff_w_down2" or shift=="ff_w_down2_0jet") ff_w=get_raw_FF(pt,ff_w_0jet_down2);
   }
   else if (njets==1){
        ff_qcd=get_raw_FF(pt,ff_qcd_1jet);
        if (shift=="ff_qcd_up1" or shift=="ff_qcd_up1_1jet") ff_qcd=get_raw_FF(pt,ff_qcd_1jet_up1);
        else if (shift=="ff_qcd_up2" or shift=="ff_qcd_up2_1jet") ff_qcd=get_raw_FF(pt,ff_qcd_1jet_up2);
        else if (shift=="ff_qcd_down1" or shift=="ff_qcd_down1_1jet") ff_qcd=get_raw_FF(pt,ff_qcd_1jet_down1);
        else if (shift=="ff_qcd_down2" or shift=="ff_qcd_down2_1jet") ff_qcd=get_raw_FF(pt,ff_qcd_1jet_down2);
        ff_w=get_raw_FF(pt,ff_w_1jet);
        if (shift=="ff_w_up1" or shift=="ff_w_up1_1jet") ff_w=get_raw_FF(pt,ff_w_1jet_up1);
        else if (shift=="ff_w_up2" or shift=="ff_w_up2_1jet") ff_w=get_raw_FF(pt,ff_w_1jet_up2);
        else if (shift=="ff_w_down1" or shift=="ff_w_down1_1jet") ff_w=get_raw_FF(pt,ff_w_1jet_down1);
        else if (shift=="ff_w_down2" or shift=="ff_w_down2_1jet") ff_w=get_raw_FF(pt,ff_w_1jet_down2);
   }
   else{
        ff_qcd=get_raw_FF(pt,ff_qcd_2jet);
        if (shift=="ff_qcd_up1" or shift=="ff_qcd_up1_2jet") ff_qcd=get_raw_FF(pt,ff_qcd_2jet_up1);
        else if (shift=="ff_qcd_up2" or shift=="ff_qcd_up2_2jet") ff_qcd=get_raw_FF(pt,ff_qcd_2jet_up2);
        else if (shift=="ff_qcd_down1" or shift=="ff_qcd_down1_2jet") ff_qcd=get_raw_FF(pt,ff_qcd_2jet_down1);
        else if (shift=="ff_qcd_down2" or shift=="ff_qcd_down2_2jet") ff_qcd=get_raw_FF(pt,ff_qcd_2jet_down2);
	if (njets==2){
          ff_w=get_raw_FF(pt,ff_w_2jet);
          if (shift=="ff_w_up1" or shift=="ff_w_up1_2jet") ff_w=get_raw_FF(pt,ff_w_2jet_up1);
          else if (shift=="ff_w_up2" or shift=="ff_w_up2_2jet") ff_w=get_raw_FF(pt,ff_w_2jet_up2);
          else if (shift=="ff_w_down1" or shift=="ff_w_down1_2jet") ff_w=get_raw_FF(pt,ff_w_2jet_down1);
          else if (shift=="ff_w_down2" or shift=="ff_w_down2_2jet") ff_w=get_raw_FF(pt,ff_w_2jet_down2);
	}
	else{
          ff_w=get_raw_FF(pt,ff_w_3jet);
	}
   }
   ff_tt=get_raw_FF(pt,ff_tt_0jet);
   if (shift=="ff_tt_up1") ff_tt=get_raw_FF(pt,ff_tt_0jet_up1);
   else if (shift=="ff_tt_up2") ff_tt=get_raw_FF(pt,ff_tt_0jet_up2);
   else if (shift=="ff_tt_down1") ff_tt=get_raw_FF(pt,ff_tt_0jet_down1);
   else if (shift=="ff_tt_down2") ff_tt=get_raw_FF(pt,ff_tt_0jet_down2);

   // L pT closure
   if (xtrg){
     if (pt<50){
      if (shift=="lptclosure_xtrg_qcd_up") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_xtrg_taupt30to50)*1.10;
      else if (shift=="lptclosure_xtrg_qcd_down") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_xtrg_taupt30to50)*0.90;
      else ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_xtrg_taupt30to50);
      if (shift=="lptclosure_xtrg_w_up") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_xtrg_taupt30to50)*1.10;
      else if (shift=="lptclosure_xtrg_w_down") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_xtrg_taupt30to50)*0.90;
      else ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_xtrg_taupt30to50);
      if (shift=="lptclosure_xtrg_tt_up") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_xtrg_taupt30to50)*1.10;
      else if (shift=="lptclosure_xtrg_tt_down") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_xtrg_taupt30to50)*0.90;
      else ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_xtrg_taupt30to50);
     }
     else if (pt<70){
      if (shift=="lptclosure_xtrg_qcd_up") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_xtrg_taupt50to70)*1.10;
      else if (shift=="lptclosure_xtrg_qcd_down") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_xtrg_taupt50to70)*0.90;
      else ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_xtrg_taupt50to70);
      if (shift=="lptclosure_xtrg_w_up") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_xtrg_taupt50to70)*1.10;
      else if (shift=="lptclosure_xtrg_w_down") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_xtrg_taupt50to70)*0.90;
      else ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_xtrg_taupt50to70);
      if (shift=="lptclosure_xtrg_tt_up") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_xtrg_taupt50to70)*1.10;
      else if (shift=="lptclosure_xtrg_tt_down") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_xtrg_taupt50to70)*0.90;
      else ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_xtrg_taupt50to70);
     }
     else{
      if (shift=="lptclosure_xtrg_qcd_up") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_xtrg_tauptgt70)*1.10;
      else if (shift=="lptclosure_xtrg_qcd_down") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_xtrg_tauptgt70)*0.90;
      else ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_xtrg_tauptgt70);
      if (shift=="lptclosure_xtrg_w_up") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_xtrg_tauptgt70)*1.10;
      else if (shift=="lptclosure_xtrg_w_down") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_xtrg_tauptgt70)*0.90;
      else ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_xtrg_tauptgt70);
      if (shift=="lptclosure_xtrg_tt_up") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_xtrg_tauptgt70)*1.10;
      else if (shift=="lptclosure_xtrg_tt_down") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_xtrg_tauptgt70)*0.90;
      else ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_xtrg_tauptgt70);
     }
   }
   else{
     if (pt<50){
      if (shift=="lptclosure_qcd_up") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_taupt30to50)*1.10;
      else if (shift=="lptclosure_qcd_down") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_taupt30to50)*0.90;
      else ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_taupt30to50);
      if (shift=="lptclosure_w_up") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_taupt30to50)*1.10;
      else if (shift=="lptclosure_w_down") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_taupt30to50)*0.90;
      else ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_taupt30to50);
      if (shift=="lptclosure_tt_up") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_taupt30to50)*1.10;
      else if (shift=="lptclosure_tt_down") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_taupt30to50)*0.90;
      else ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_taupt30to50);
     }
     else if (pt<70){
      if (shift=="lptclosure_qcd_up") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_taupt50to70)*1.10;
      else if (shift=="lptclosure_qcd_down") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_taupt50to70)*0.90;
      else ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_taupt50to70);
      if (shift=="lptclosure_w_up") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_taupt50to70)*1.10;
      else if (shift=="lptclosure_w_down") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_taupt50to70)*0.90;
      else ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_taupt50to70);
      if (shift=="lptclosure_tt_up") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_taupt50to70)*1.10;
      else if (shift=="lptclosure_tt_down") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_taupt50to70)*0.90;
      else ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_taupt50to70);
     }
     else{
      if (shift=="lptclosure_qcd_up") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_tauptgt70)*1.10;
      else if (shift=="lptclosure_qcd_down") ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_tauptgt70)*0.90;
      else ff_qcd = ff_qcd*get_lpt_closure(lpt, lptclosure_qcd_tauptgt70);
      if (shift=="lptclosure_w_up") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_tauptgt70)*1.10;
      else if (shift=="lptclosure_w_down") ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_tauptgt70)*0.90;
      else ff_w = ff_w*get_lpt_closure(lpt, lptclosure_w_tauptgt70);
      if (shift=="lptclosure_tt_up") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_tauptgt70)*1.10;
      else if (shift=="lptclosure_tt_down") ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_tauptgt70)*0.90;
      else ff_tt = ff_tt*get_lpt_closure(lpt, lptclosure_tt_tauptgt70);
     }
   }

   // MT and OSSS corrections
   /*if (shift=="mtclosure_w_up1") ff_w = ff_w*get_mt_closure(mt,mtclosure_w_up1);
   else if (shift=="mtclosure_w_up2") ff_w = ff_w*get_mt_closure(mt,mtclosure_w_up2);
   else if (shift=="mtclosure_w_down1") ff_w = ff_w*get_mt_closure(mt,mtclosure_w_down1);
   else if (shift=="mtclosure_w_down2") ff_w = ff_w*get_mt_closure(mt,mtclosure_w_down2);
   else ff_w = ff_w*get_mt_closure(mt,mtclosure_w);*/

   if (shift=="mtclosure_w_up1") ff_w = ff_w*get_mtpth_closure(mt,mtpthclosure_w)*get_mtpth_closure(pth,mtpthclosure_w);
   else if (shift=="mtclosure_w_down1") ff_w = ff_w*1.0;
   else ff_w = ff_w*get_mtpth_closure(pth,mtpthclosure_w);

   if (shift=="osssclosure_qcd_down") ff_qcd = ff_qcd*get_mvis_closure(3.0, osssclosure_qcd)*0.90;
   else if (shift=="osssclosure_qcd_up") ff_qcd = ff_qcd*get_mvis_closure(3.0, osssclosure_qcd)*1.10;
   else ff_qcd = ff_qcd*get_mvis_closure(3.0, osssclosure_qcd);
   /*if (shift=="osssclosure_qcd_up") ff_qcd = ff_qcd*1.3;
   else if (shift=="osssclosure_qcd_down") ff_qcd = ff_qcd;
   else ff_qcd = ff_qcd*1.15;*/ //FIXME

   /*if (pth<45) ff_w=1.03*1.08*ff_w;
   else if (pth<80) ff_w=0.95*0.93*ff_w;
   else if (pth<120) ff_w=0.95*0.88*ff_w;
   else if (pth<200) ff_w=1.00*0.95*ff_w;
   else ff_w=1.00*0.95*ff_w;*/

   float ff_cmb=frac_tt*ff_tt + frac_qcd*ff_qcd + frac_w*ff_w;

   if (shift=="norm_0jet_up" and njets==0) ff_cmb=1.05*ff_cmb;
   if (shift=="norm_0jet_down" and njets==0) ff_cmb=0.95*ff_cmb;
   if (shift=="norm_1jet_up" and njets==1) ff_cmb=1.05*ff_cmb;
   if (shift=="norm_1jet_down" and njets==1) ff_cmb=0.95*ff_cmb;
   if (shift=="norm_2jet_up" and njets==2) ff_cmb=1.05*ff_cmb;
   if (shift=="norm_2jet_down" and njets==2) ff_cmb=0.95*ff_cmb;
   if (shift=="norm_3jet_up" and njets==3) ff_cmb=1.05*ff_cmb;
   if (shift=="norm_3jet_down" and njets==3) ff_cmb=0.95*ff_cmb;
   if (shift=="norm_4jet_up" and njets>=4) ff_cmb=1.05*ff_cmb;
   if (shift=="norm_4jet_down" and njets>=4) ff_cmb=0.95*ff_cmb;

   if (shift=="norm_pth0to45_up" and pth>=0 and pth<45) ff_cmb=1.05*ff_cmb;
   if (shift=="norm_pth0to45_down" and pth>=0 and pth<45) ff_cmb=0.95*ff_cmb;
   if (shift=="norm_pth45to80_up" and pth>=45 and pth<120) ff_cmb=1.10*ff_cmb;
   if (shift=="norm_pth45to80_down" and pth>=45 and pth<120) ff_cmb=0.90*ff_cmb;
   if (shift=="norm_pth80to120_up" and pth>=80 and pth<120) ff_cmb=1.00*ff_cmb;
   if (shift=="norm_pth80to120_down" and pth>=80 and pth<120) ff_cmb=1.00*ff_cmb;
   if (shift=="norm_pth120to200_up" and pth>=120 and pth<200) ff_cmb=1.10*ff_cmb;
   if (shift=="norm_pth120to200_down" and pth>=120 and pth<200) ff_cmb=0.90*ff_cmb;
   if (shift=="norm_pthgt200_up" and pth>=200) ff_cmb=1.15*ff_cmb;
   if (shift=="norm_pthgt200_down" and pth>=200) ff_cmb=0.85*ff_cmb;

   return ff_cmb;
} 

