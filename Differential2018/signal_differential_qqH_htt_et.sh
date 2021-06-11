./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_0_20.root qqH xH_PTH_0_20 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_20_45.root qqH xH_PTH_20_45 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_0_10.root qqH xH_PTH_0_10 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_10_20.root qqH xH_PTH_10_20 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_20_30.root qqH xH_PTH_20_30 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_30_45.root qqH xH_PTH_30_45 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_45_60.root qqH xH_PTH_45_60 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_60_80.root qqH xH_PTH_60_80 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_0_45.root qqH xH_PTH_0_45 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_45_80.root qqH xH_PTH_45_80 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_80_120.root qqH xH_PTH_80_120 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_120_200.root qqH xH_PTH_120_200 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_200_350.root qqH xH_PTH_200_350 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_350_600.root qqH xH_PTH_350_600 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_350_450.root qqH xH_PTH_350_450 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_GT600.root qqH xH_PTH_GT600 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_PTH_GT450.root qqH xH_PTH_GT450 0

./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_NJ_0.root qqH xH_NJ_0 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_NJ_1.root qqH xH_NJ_1 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_NJ_2.root qqH xH_NJ_2 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_NJ_3.root qqH xH_NJ_3 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_NJ_GE4.root qqH xH_NJ_GE4 0

./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_J1PT_30_60.root qqH xH_J1PT_30_60 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_J1PT_60_120.root qqH xH_J1PT_60_120 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_J1PT_120_200.root qqH xH_J1PT_120_200 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_J1PT_200_350.root qqH xH_J1PT_200_350 0
./FinalSelection_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_diff_et/qqH_J1PT_GT350.root qqH xH_J1PT_GT350 0

hadd -f files_diff_et/diff_qqH.root files_diff_et/qqH_PTH_0_20.root files_diff_et/qqH_PTH_20_45.root files_diff_et/qqH_PTH_0_10.root files_diff_et/qqH_PTH_10_20.root files_diff_et/qqH_PTH_20_30.root files_diff_et/qqH_PTH_30_45.root files_diff_et/qqH_PTH_45_60.root files_diff_et/qqH_PTH_60_80.root files_diff_et/qqH_PTH_0_45.root files_diff_et/qqH_PTH_45_80.root files_diff_et/qqH_PTH_80_120.root files_diff_et/qqH_PTH_120_200.root files_diff_et/qqH_PTH_200_350.root files_diff_et/qqH_PTH_350_600.root files_diff_et/qqH_PTH_350_450.root files_diff_et/qqH_PTH_GT600.root files_diff_et/qqH_PTH_GT450.root files_diff_et/qqH_NJ_0.root files_diff_et/qqH_NJ_1.root files_diff_et/qqH_NJ_2.root files_diff_et/qqH_NJ_3.root files_diff_et/qqH_NJ_GE4.root files_diff_et/qqH_J1PT_30_60.root files_diff_et/qqH_J1PT_60_120.root files_diff_et/qqH_J1PT_120_200.root files_diff_et/qqH_J1PT_200_350.root files_diff_et/qqH_J1PT_GT350.root 
