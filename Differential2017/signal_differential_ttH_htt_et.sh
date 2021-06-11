./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_0_20.root ttHnonbb xH_PTH_0_20 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_20_45.root ttHnonbb xH_PTH_20_45 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_0_10.root ttHnonbb xH_PTH_0_10 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_10_20.root ttHnonbb xH_PTH_10_20 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_20_30.root ttHnonbb xH_PTH_20_30 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_30_45.root ttHnonbb xH_PTH_30_45 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_45_60.root ttHnonbb xH_PTH_45_60 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_60_80.root ttHnonbb xH_PTH_60_80 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_0_45.root ttHnonbb xH_PTH_0_45 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_45_80.root ttHnonbb xH_PTH_45_80 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_80_120.root ttHnonbb xH_PTH_80_120 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_120_200.root ttHnonbb xH_PTH_120_200 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_200_350.root ttHnonbb xH_PTH_200_350 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_350_600.root ttHnonbb xH_PTH_350_600 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_350_450.root ttHnonbb xH_PTH_350_450 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_GT600.root ttHnonbb xH_PTH_GT600 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_PTH_GT450.root ttHnonbb xH_PTH_GT450 0

./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_NJ_0.root ttHnonbb xH_NJ_0 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_NJ_1.root ttHnonbb xH_NJ_1 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_NJ_2.root ttHnonbb xH_NJ_2 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_NJ_3.root ttHnonbb xH_NJ_3 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_NJ_GE4.root ttHnonbb xH_NJ_GE4 0

./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_J1PT_30_60.root ttHnonbb xH_J1PT_30_60 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_J1PT_60_120.root ttHnonbb xH_J1PT_60_120 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_J1PT_120_200.root ttHnonbb xH_J1PT_120_200 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_J1PT_200_350.root ttHnonbb xH_J1PT_200_350 0
./FinalSelection_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ttHnonbb.root files_diff_et/ttH_J1PT_GT350.root ttHnonbb xH_J1PT_GT350 0

hadd -f files_diff_et/diff_ttH.root files_diff_et/ttH_PTH_0_20.root files_diff_et/ttH_PTH_20_45.root files_diff_et/ttH_PTH_0_10.root files_diff_et/ttH_PTH_10_20.root files_diff_et/ttH_PTH_20_30.root files_diff_et/ttH_PTH_30_45.root files_diff_et/ttH_PTH_45_60.root files_diff_et/ttH_PTH_60_80.root files_diff_et/ttH_PTH_0_45.root files_diff_et/ttH_PTH_45_80.root files_diff_et/ttH_PTH_80_120.root files_diff_et/ttH_PTH_120_200.root files_diff_et/ttH_PTH_200_350.root files_diff_et/ttH_PTH_350_600.root files_diff_et/ttH_PTH_350_450.root files_diff_et/ttH_PTH_GT600.root files_diff_et/ttH_PTH_GT450.root files_diff_et/ttH_NJ_0.root files_diff_et/ttH_NJ_1.root files_diff_et/ttH_NJ_2.root files_diff_et/ttH_NJ_3.root files_diff_et/ttH_NJ_GE4.root files_diff_et/ttH_J1PT_30_60.root files_diff_et/ttH_J1PT_60_120.root files_diff_et/ttH_J1PT_120_200.root files_diff_et/ttH_J1PT_200_350.root files_diff_et/ttH_J1PT_GT350.root 
