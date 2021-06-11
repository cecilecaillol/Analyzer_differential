./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoPTH_0_45.root ggH ggH_recoPTH_0_45 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoPTH_45_80.root ggH ggH_recoPTH_45_80 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoPTH_80_120.root ggH ggH_recoPTH_80_120 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoPTH_120_200.root ggH ggH_recoPTH_120_200 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoPTH_200_350.root ggH ggH_recoPTH_200_350 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoPTH_350_450.root ggH ggH_recoPTH_350_450 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoPTH_GT450.root ggH ggH_recoPTH_GT450 0

./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoNJ_0.root ggH ggH_recoNJ_0 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoNJ_1.root ggH ggH_recoNJ_1 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoNJ_2.root ggH ggH_recoNJ_2 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoNJ_3.root ggH ggH_recoNJ_3 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoNJ_GE4.root ggH ggH_recoNJ_GE4 0

./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoJ1PT_30_60.root ggH ggH_recoJ1PT_30_60 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoJ1PT_60_120.root ggH ggH_recoJ1PT_60_120 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoJ1PT_120_200.root ggH ggH_recoJ1PT_120_200 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoJ1PT_200_350.root ggH ggH_recoJ1PT_200_350 0
./FinalSelection_em.exe /data/ccaillol/differentialem2017_svfitted_3aug/ggH125.root files_diff_em/ggH_recoJ1PT_GT350.root ggH ggH_recoJ1PT_GT350 0

hadd -f files_diff_em/recodiff_ggH.root files_diff_em/ggH_recoPTH_0_45.root files_diff_em/ggH_recoPTH_45_80.root files_diff_em/ggH_recoPTH_80_120.root files_diff_em/ggH_recoPTH_120_200.root files_diff_em/ggH_recoPTH_200_350.root files_diff_em/ggH_recoPTH_350_450.root files_diff_em/ggH_recoPTH_GT450.root files_diff_em/ggH_recoNJ_0.root files_diff_em/ggH_recoNJ_1.root files_diff_em/ggH_recoNJ_2.root files_diff_em/ggH_recoNJ_3.root files_diff_em/ggH_recoNJ_GE4.root files_diff_em/ggH_recoJ1PT_30_60.root files_diff_em/ggH_recoJ1PT_60_120.root files_diff_em/ggH_recoJ1PT_120_200.root files_diff_em/ggH_recoJ1PT_200_350.root files_diff_em/ggH_recoJ1PT_GT350.root 
