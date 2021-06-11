./Make.sh Measure_OSSS_TT.cc
./Measure_OSSS_TT.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataB.root files_fractions/DataB.root data_obs data_obs 0
./Measure_OSSS_TT.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataC.root files_fractions/DataC.root data_obs data_obs 0
./Measure_OSSS_TT.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataD.root files_fractions/DataD.root data_obs data_obs 0
./Measure_OSSS_TT.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataE.root files_fractions/DataE.root data_obs data_obs 0
./Measure_OSSS_TT.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataF.root files_fractions/DataF.root data_obs data_obs 0
./Measure_OSSS_TT.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataG.root files_fractions/DataG.root data_obs data_obs 0
./Measure_OSSS_TT.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataH.root files_fractions/DataH.root data_obs data_obs 0 
./Measure_OSSS_TT.exe /data/ccaillol/differentialem2016_svfitted_3aug/TT.root files_fractions/TT.root TT TT 0
./Measure_OSSS_TT.exe /data/ccaillol/differentialem2016_svfitted_3aug/embedded.root files_fractions/embedded.root embedded embedded 0
hadd -f files_fractions/Data.root files_fractions/DataB.root files_fractions/DataC.root files_fractions/DataD.root files_fractions/DataE.root files_fractions/DataF.root files_fractions/DataG.root files_fractions/DataH.root


