./Make.sh PrepareDifferentialTheoryUncertainties.cc
./PrepareDifferentialTheoryUncertainties.exe /data/ccaillol/theoryDifferential_19jun/GGHTT125.root files_theory_et/ggH_htt125.root ggH_htt125 ggH_htt125 0
./PrepareDifferentialTheoryUncertainties.exe /data/ccaillol/theoryDifferential_19jun/VBFHTT125.root files_theory_et/qqH_htt125.root qqH_htt125 qqH_htt125 0
./PrepareDifferentialTheoryUncertainties.exe /data/ccaillol/theoryDifferential_19jun/WplusHTT125.root files_theory_et/Wplus125.root WplusH125 WH_htt125 0
./PrepareDifferentialTheoryUncertainties.exe /data/ccaillol/theoryDifferential_19jun/WminusHTT125.root files_theory_et/WminusH125.root WminusH125 WH_htt125 0
./PrepareDifferentialTheoryUncertainties.exe /data/ccaillol/theoryDifferential_19jun/ZHTT125.root files_theory_et/ZH125.root ZH125 ZH_htt125 0
./PrepareDifferentialTheoryUncertainties.exe /data/ccaillol/theoryDifferential_19jun/GGZHLLTT125.root files_theory_et/GGZHLLTT125.root GGZHLLTT125 ggZH_lep_htt125 0
./PrepareDifferentialTheoryUncertainties.exe /data/ccaillol/theoryDifferential_19jun/GGZHQQTT125.root files_theory_et/GGZHQQTT125.root GGZHQQTT125 ggZH_had_htt125 0
./PrepareDifferentialTheoryUncertainties.exe /data/ccaillol/theoryDifferential_19jun/GGZHNNTT125.root files_theory_et/GGZHNNTT125.root GGZHNNTT125 ggZH_lep_htt125 0
./PrepareDifferentialTheoryUncertainties.exe /data/ccaillol/theoryDifferential_19jun/TTHTT125.root files_theory_et/ttHTT125.root ttHTT ttH_htt125 0
#hadd -f differential_theory.root files_theory_et/ggH_htt125.root files_theory_et/qqH_htt125.root files_theory_et/Wplus125.root files_theory_et/WminusH125.root files_theory_et/ZH125.root files_theory_et/GGZHLLTT125.root files_theory_et/GGZHQQTT125.root files_theory_et/GGZHNNTT125.root files_theory_et/ttHTT125.root 
