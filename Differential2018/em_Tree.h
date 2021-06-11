  int njets_JetAbsoluteUp, njets_JetAbsoluteyearUp, njets_JetBBEC1Up, njets_JetBBEC1yearUp, njets_JetEC2Up, njets_JetEC2yearUp, njets_JetFlavorQCDUp, njets_JetHFUp, njets_JetHFyearUp, njets_JetRelativeBalUp, njets_JetRelativeSampleUp, njets_JERUp;
  int njets_JetAbsoluteDown, njets_JetAbsoluteyearDown, njets_JetBBEC1Down, njets_JetBBEC1yearDown, njets_JetEC2Down, njets_JetEC2yearDown, njets_JetFlavorQCDDown, njets_JetHFDown, njets_JetHFyearDown, njets_JetRelativeBalDown, njets_JetRelativeSampleDown, njets_JERDown;
  float mjj_JetAbsoluteUp, mjj_JetAbsoluteyearUp, mjj_JetBBEC1Up, mjj_JetBBEC1yearUp, mjj_JetEC2Up, mjj_JetEC2yearUp, mjj_JetFlavorQCDUp, mjj_JetHFUp, mjj_JetHFyearUp, mjj_JetRelativeBalUp, mjj_JetRelativeSampleUp, mjj_JERUp;
  float mjj_JetAbsoluteDown, mjj_JetAbsoluteyearDown, mjj_JetBBEC1Down, mjj_JetBBEC1yearDown, mjj_JetEC2Down, mjj_JetEC2yearDown, mjj_JetFlavorQCDDown, mjj_JetHFDown, mjj_JetHFyearDown, mjj_JetRelativeBalDown, mjj_JetRelativeSampleDown, mjj_JERDown;
  float m_sv_JetAbsoluteUp, m_sv_JetAbsoluteyearUp, m_sv_JetBBEC1Up, m_sv_JetBBEC1yearUp, m_sv_JetEC2Up, m_sv_JetEC2yearUp, m_sv_JetFlavorQCDUp, m_sv_JetHFUp, m_sv_JetHFyearUp, m_sv_JetRelativeBalUp, m_sv_JetRelativeSampleUp, m_sv_JERUp;
  float m_sv_JetAbsoluteDown, m_sv_JetAbsoluteyearDown, m_sv_JetBBEC1Down, m_sv_JetBBEC1yearDown, m_sv_JetEC2Down, m_sv_JetEC2yearDown, m_sv_JetFlavorQCDDown, m_sv_JetHFDown, m_sv_JetHFyearDown, m_sv_JetRelativeBalDown, m_sv_JetRelativeSampleDown, m_sv_JERDown;
  float met_JetAbsoluteUp, met_JetAbsoluteyearUp, met_JetBBEC1Up, met_JetBBEC1yearUp, met_JetEC2Up, met_JetEC2yearUp, met_JetFlavorQCDUp, met_JetHFUp, met_JetHFyearUp, met_JetRelativeBalUp, met_JetRelativeSampleUp, met_JERUp;
  float met_JetAbsoluteDown, met_JetAbsoluteyearDown, met_JetBBEC1Down, met_JetBBEC1yearDown, met_JetEC2Down, met_JetEC2yearDown, met_JetFlavorQCDDown, met_JetHFDown, met_JetHFyearDown, met_JetRelativeBalDown, met_JetRelativeSampleDown, met_JERDown;
  float metphi_JetAbsoluteUp, metphi_JetAbsoluteyearUp, metphi_JetBBEC1Up, metphi_JetBBEC1yearUp, metphi_JetEC2Up, metphi_JetEC2yearUp, metphi_JetFlavorQCDUp, metphi_JetHFUp, metphi_JetHFyearUp, metphi_JetRelativeBalUp, metphi_JetRelativeSampleUp, metphi_JERUp;
  float metphi_JetAbsoluteDown, metphi_JetAbsoluteyearDown, metphi_JetBBEC1Down, metphi_JetBBEC1yearDown, metphi_JetEC2Down, metphi_JetEC2yearDown, metphi_JetFlavorQCDDown, metphi_JetHFDown, metphi_JetHFyearDown, metphi_JetRelativeBalDown, metphi_JetRelativeSampleDown, metphi_JERDown;

float bweight_central,bweight_down_cferr1,bweight_down_cferr2,bweight_down_eta,bweight_down_hf,bweight_down_hfstats1,bweight_down_hfstats2,bweight_down_jes,bweight_down_lf,bweight_down_lfstats1,bweight_down_lfstats2,bweight_up_cferr1,bweight_up_cferr2,bweight_up_eta,bweight_up_hf,bweight_up_hfstats1,bweight_up_hfstats2,bweight_up_jes,bweight_up_lf,bweight_up_lfstats1,bweight_up_lfstats2;

  float genweight,genM,genpT,pt_top1,pt_top2;
  float geneta_1, geneta_2, genpt_1, genpt_2;
  float m_sv_elescaleESUp, m_sv_elescaleESDown, m_sv_elesmearESUp, m_sv_elesmearESDown;
  float matchMu8E23_2,matchMu8E23_1,filterMu8E23_2,filterMu8E23_1;
  float matchMu23E12_2,matchMu23E12_1,filterMu23E12_2,filterMu23E12_1;
  float passMu8E23, passMu23E12;
  float photonIso_2, puIso_2, chargedIso_2, neutralIso_2,metcor,metcorphi;
  float pt_1,pt_2,px_1,px_2,py_1,py_2,pz_1,pz_2,eta_1,eta_2,phi_1,phi_2,iso_1,e_1,e_2,m_1,m_2, iso_2; 
  float pt_1_ScaleUp, pt_1_ScaleDown, pt_1_SigmaUp, pt_1_SigmaDown;
  float Flag_BadChargedCandidateFilter, Flag_BadPFMuonFilter, Flag_EcalDeadCellTriggerPrimitiveFilter, Flag_HBHENoiseFilter, Flag_HBHENoiseIsoFilter, Flag_badCloneMuon, Flag_badGlobalMuon, Flag_eeBadScFilter, Flag_goodVertices, Flag_globalSuperTightHalo2016Filter, Flag_badMuons, Flag_duplicateMuons, Flag_ecalBadCalibFilter, Flag_ecalBadCalibReducedMINIAODFilter;
  int gen_match_1, gen_match_2;
  int nbtag, nbtagL;
  float bweight;
  float numGenJets;
  int run, lumi, evt;
  float met_UESUp, met_UESDown, metphi_UESUp, metphi_UESDown;
  float met_resolutionUp, metphi_resolutionUp, met_responseUp, metphi_responseUp;
  float met_resolutionDown, metphi_resolutionDown, met_responseDown, metphi_responseDown;
  float Rivet_stage1_1_fine_cat_pTjet30GeV, Rivet_stage1_1_cat_pTjet30GeV, Rivet_higgsPt, Rivet_nJets30, Rivet_stage1_cat_pTjet30GeV, Rivet_higgsRapidity, Rivet_j1pt, Rivet_j2pt, Rivet_j1eta, Rivet_j2eta, Rivet_j1phi, Rivet_j2phi, Rivet_j1m, Rivet_j2m;
  float gentau1_pt, gentau2_pt, gentau1_eta, gentau2_eta;
  int nup,njets;
  float m_sv, m_sv_UP, m_sv_DOWN, m_sv_UESUp, m_sv_UESDown, m_sv_ResponseUp, m_sv_ResponseDown, m_sv_ResolutionUp, m_sv_ResolutionDown, m_sv_muonESUp, m_sv_muonESDown;
  float npv, jpt_1,mjj, jeta_1, jeta_2, jpt_2, jphi_1, jphi_2, jcsv_1, jcsv_2;
  float q_1,q_2;
  float met, metphi, met_px, met_py;
  float bpt_1, beta_1, bphi_1, bflavor_1, bpt_2, beta_2, bphi_2, bflavor_2, bcsv_1, bcsv_2;
  float jpt_1_JetAbsoluteUp, jpt_1_JetAbsoluteyearUp, jpt_1_JetBBEC1Up, jpt_1_JetBBEC1yearUp, jpt_1_JetEC2Up, jpt_1_JetEC2yearUp, jpt_1_JetFlavorQCDUp, jpt_1_JetHFUp, jpt_1_JetHFyearUp, jpt_1_JetRelativeBalUp, jpt_1_JetRelativeSampleUp, jpt_1_JERUp;
  float jpt_1_JetAbsoluteDown, jpt_1_JetAbsoluteyearDown, jpt_1_JetBBEC1Down, jpt_1_JetBBEC1yearDown, jpt_1_JetEC2Down, jpt_1_JetEC2yearDown, jpt_1_JetFlavorQCDDown, jpt_1_JetHFDown, jpt_1_JetHFyearDown, jpt_1_JetRelativeBalDown, jpt_1_JetRelativeSampleDown, jpt_1_JERDown;
  float HTTgenfinalstate,gen_met_pt,gen_met_phi,gen_ele_pt,gen_ele_eta,gen_ele_phi,gen_mu_pt,gen_mu_eta,gen_mu_phi;

  float l2_decayMode;
  float decayModeFinding_2;
  float puweight;
  float npu;
  int NUP;

  float PythiaWeight_isr_muR2,PythiaWeight_fsr_muR2,PythiaWeight_isr_muR0p5,PythiaWeight_fsr_muR0p5,lheweight_muR0p5_muF0p5,lheweight_muR2_muF2,lheweight_nominal;

