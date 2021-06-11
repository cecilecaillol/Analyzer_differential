./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoPTH_0_45.root qqH xH_recoPTH_0_45 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoPTH_45_80.root qqH xH_recoPTH_45_80 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoPTH_80_120.root qqH xH_recoPTH_80_120 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoPTH_120_200.root qqH xH_recoPTH_120_200 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoPTH_200_350.root qqH xH_recoPTH_200_350 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoPTH_350_450.root qqH xH_recoPTH_350_450 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoPTH_GT450.root qqH xH_recoPTH_GT450 0

./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoNJ_0.root qqH xH_recoNJ_0 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoNJ_1.root qqH xH_recoNJ_1 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoNJ_2.root qqH xH_recoNJ_2 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoNJ_3.root qqH xH_recoNJ_3 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoNJ_GE4.root qqH xH_recoNJ_GE4 0

./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoJ1PT_30_60.root qqH xH_recoJ1PT_30_60 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoJ1PT_60_120.root qqH xH_recoJ1PT_60_120 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoJ1PT_120_200.root qqH xH_recoJ1PT_120_200 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoJ1PT_200_350.root qqH xH_recoJ1PT_200_350 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_recoJ1PT_GT350.root qqH xH_recoJ1PT_GT350 0

hadd -f files_diff_em/recodiff_qqH.root files_diff_em/qqH_recoPTH_0_45.root files_diff_em/qqH_recoPTH_45_80.root files_diff_em/qqH_recoPTH_80_120.root files_diff_em/qqH_recoPTH_120_200.root files_diff_em/qqH_recoPTH_200_350.root files_diff_em/qqH_recoPTH_350_450.root files_diff_em/qqH_recoPTH_GT450.root files_diff_em/qqH_recoNJ_0.root files_diff_em/qqH_recoNJ_1.root files_diff_em/qqH_recoNJ_2.root files_diff_em/qqH_recoNJ_3.root files_diff_em/qqH_recoNJ_GE4.root files_diff_em/qqH_recoJ1PT_30_60.root files_diff_em/qqH_recoJ1PT_60_120.root files_diff_em/qqH_recoJ1PT_120_200.root files_diff_em/qqH_recoJ1PT_200_350.root files_diff_em/qqH_recoJ1PT_GT350.root 
