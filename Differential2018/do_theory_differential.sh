./Make.sh PrepareDifferentialTheoryHistograms.cc
./PrepareDifferentialTheoryHistograms.exe /data/ccaillol/theoryDifferential_19jun/GGHTT125.root files_theory/ggH_htt125.root ggH_htt125 ggH_htt125 0
./PrepareDifferentialTheoryHistograms.exe /data/ccaillol/theoryDifferential_19jun/VBFHTT125.root files_theory/qqH_htt125.root qqH_htt125 qqH_htt125 0
./PrepareDifferentialTheoryHistograms.exe /data/ccaillol/theoryDifferential_19jun/WplusHTT125.root files_theory/Wplus125.root WplusH125 WH_htt125 0
./PrepareDifferentialTheoryHistograms.exe /data/ccaillol/theoryDifferential_19jun/WminusHTT125.root files_theory/WminusH125.root WminusH125 WH_htt125 0
./PrepareDifferentialTheoryHistograms.exe /data/ccaillol/theoryDifferential_19jun/ZHTT125.root files_theory/ZH125.root ZH125 ZH_htt125 0
./PrepareDifferentialTheoryHistograms.exe /data/ccaillol/theoryDifferential_19jun/TTHTT125.root files_theory/TTHTT125.root ttHTT ttH_htt125 0 
./PrepareDifferentialTheoryHistograms.exe /data/ccaillol/theoryDifferential_19jun/GGZHLLTT125.root files_theory/GGZHLLTT125.root GGZHLLTT125 ggZH_lep_htt125 0
./PrepareDifferentialTheoryHistograms.exe /data/ccaillol/theoryDifferential_19jun/GGZHQQTT125.root files_theory/GGZHQQTT125.root GGZHQQTT125 ggZH_had_htt125 0
./PrepareDifferentialTheoryHistograms.exe /data/ccaillol/theoryDifferential_19jun/GGZHNNTT125.root files_theory/GGZHNNTT125.root GGZHNNTT125 ggZH_lep_htt125 0
hadd -f differential_theory.root files_theory/ggH_htt125.root files_theory/qqH_htt125.root files_theory/Wplus125.root files_theory/WminusH125.root files_theory/ZH125.root files_theory/GGZHLLTT125.root files_theory/GGZHQQTT125.root files_theory/GGZHNNTT125.root files_theory/TTHTT125.root

