#include <string>

std::string get_name_puhisto(std::string input){

    if (input.find("GGZHLLTT")<140) return "pua/#ggZH_HToTauTau_ZToLL_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("GGZHNNTT")<140) return "pua/#ggZH_HToTauTau_ZToNuNu_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("GGZHQQTT")<140) return "pua/#ggZH_HToTauTau_ZToQQ_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM";
    else if (input.find("ggH125")<140) return "pua/#GluGluHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2#MINIAODSIM";
    else if (input.find("ttHnonbb")<140) return "pua/#ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("DY_v2")<140) return "pua/#DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("DY2")<140) return "pua/#DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v2#MINIAODSIM";
    else if (input.find("DY1")<140) return "pua/#DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("DY3")<140) return "pua/#DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v2#MINIAODSIM";
    else if (input.find("DY_v1")<140) return "pua/#DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1#MINIAODSIM";
    else if (input.find("GGZHWW")<140) return "pua/#GluGluZH_HToWW_M125_13TeV_powheg_pythia8_TuneCP5#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("DY4_v2")<140) return "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("DY4_v1")<140) return "pua/#DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_v2_94X_mc2017_realistic_v14-v2#MINIAODSIM";
    else if (input.find("GGHWW")<140) return "pua/#GluGluHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("EWKZLL")<140) return "pua/#EWKZ2Jets_ZToLL_M-50_TuneCP5_13TeV-madgraph-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2#MINIAODSIM";
    else if (input.find("ZHWW")<140) return "pua/#HZJ_HToWW_M125_13TeV_powheg_jhugen714_pythia8_TuneCP5#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v4#MINIAODSIM";
    else if (input.find("WminusHWW")<140) return "pua/#HWminusJ_HToWW_M125_13TeV_powheg_pythia8_TuneCP5#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("WplusHWW")<140) return "pua/#HWplusJ_HToWW_M125_13TeV_powheg_pythia8_TuneCP5#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("TTToSemiLeptonic")<140) return "pua/#TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("TTToHadronic")<140) return "pua/#TTToHadronic_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2#MINIAODSIM";
    else if (input.find("ST_tW_top_v2")<140) return "pua/#ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM";
    else if (input.find("ST_t_top")<140) return "pua/#ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("ST_tW_antitop")<140) return "pua/#ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM";
    else if (input.find("ST_t_antitop_v2")<140) return "pua/#ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM";
    else if (input.find("TTTo2L2Nu")<140) return "pua/#TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("ST_tW_top_v1")<140) return "pua/#ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("ST_t_antitop_v1")<140) return "pua/#ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("ZZ2L2Q")<140) return "pua/#ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("WW1L1Nu2Q")<140) return "pua/#WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("WZ1L1Nu2Q")<140) return "pua/#WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2#MINIAODSIM";
    else if (input.find("WZ2L2Q")<140) return "pua/#WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("ZZ4L")<140) return "pua/#ZZTo4L_TuneCP5_13TeV-amcatnloFXFX-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("WZ1L3Nu")<140) return "pua/#WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("WZ3L1Nu")<140) return "pua/#WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("WZ1L1Nu2Q")<140) return "pua/#WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_old_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("ZH125")<140) return "pua/#ZHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("WplusH125")<140) return "pua/#WplusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("WminusH125")<140) return "pua/#WminusHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("VV2L2Nu")<140) return "pua/#VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("VBF125")<140) return "pua/#VBFHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else if (input.find("VBFHWW")<140) return "pua/#VBFHToWWTo2L2Nu_M125_13TeV_powheg2_JHUGenV714_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1#MINIAODSIM";
    else return "pua/#VBFHToTauTau_M125_13TeV_powheg_pythia8#RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1#MINIAODSIM";
}
