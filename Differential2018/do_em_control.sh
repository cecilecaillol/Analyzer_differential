./Make.sh Control_em.cc
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/DataA.root files_control_em/DataA.root data_obs data_obs 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/DataB.root files_control_em/DataB.root data_obs data_obs 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/DataC.root files_control_em/DataC.root data_obs data_obs 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/DataD.root files_control_em/DataD.root data_obs data_obs 0
hadd -f files_control_em/Data.root files_control_em/DataA.root files_control_em/DataB.root files_control_em/DataC.root files_control_em/DataD.root
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/DY.root files_control_em/DYincl.root Z Z 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/DY1.root files_control_em/DY1.root Z Z 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/DY2.root files_control_em/DY2.root Z Z 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/DY3.root files_control_em/DY3.root Z Z 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/DY4.root files_control_em/DY4.root Z Z 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/EWKZLL.root files_control_em/EWKZLL.root EWKZLL Z 0
hadd -f files_control_em/DY.root files_control_em/DYincl.root files_control_em/DY1.root files_control_em/DY2.root files_control_em/DY3.root files_control_em/DY4.root files_control_em/EWKZLL.root
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/Wall.root files_control_em/W.root W W 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/WG.root files_control_em/WG.root WG W 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/TTToHadronic.root files_control_em/TTToHadronic.root TTToHadronic TT 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/TTTo2L2Nu.root files_control_em/TTTo2L2Nu.root TTTo2L2Nu TT 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/TTToSemiLeptonic.root files_control_em/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_control_em/TT.root files_control_em/TTToHadronic.root files_control_em/TTTo2L2Nu.root files_control_em/TTToSemiLeptonic.root
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/WZ2L2Q.root files_control_em/WZ2L2Q.root WZ2L2Q VV 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/WZ3L1Nu.root files_control_em/WZ3L1Nu.root WZ3L1Nu VV 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/VV2L2Nu.root files_control_em/VV2L2Nu.root VV2L2Nu VV 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/ZZ2L2Q.root files_control_em/ZZ2L2Q.root ZZ2L2Q VV 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/ZZ4L.root files_control_em/ZZ4L.root ZZ4L VV 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/ST_t_antitop.root files_control_em/ST_t_antitop.root ST_t_antitop ST 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/ST_t_top.root files_control_em/ST_t_top.root ST_t_top ST 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/ST_tW_antitop.root files_control_em/ST_tW_antitop.root ST_tW_antitop ST 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/ST_tW_top.root files_control_em/ST_tW_top.root ST_tW_top ST 0
hadd -f files_control_em/VV.root files_control_em/ST_t_antitop.root files_control_em/ST_t_top.root files_control_em/ST_tW_antitop.root files_control_em/ST_tW_top.root files_control_em/WZ2L2Q.root files_control_em/WZ3L1Nu.root files_control_em/VV2L2Nu.root files_control_em/ZZ2L2Q.root files_control_em/ZZ4L.root

./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/ggH125.root files_control_em/ggH_htt125.root ggH_htt125 ggH_htt125 0
./Control_em.exe /data/ccaillol/differentialem2018_svfitted_3aug/VBF125.root files_control_em/qqH_htt125.root qqH_htt125 qqH_htt125 0
hadd -f files_control_em/signal.root files_control_em/ggH_htt125.root files_control_em/qqH_htt125.root 

python Create_fake_em_mc.py --directory control
hadd -f smh_em_control_2D.root files_control_em/Data.root files_control_em/DY.root files_control_em/W.root files_control_em/TT.root files_control_em/VV.root files_control_em/Fake.root files_control_em/signal.root 
python Create_1D_em_control.py

