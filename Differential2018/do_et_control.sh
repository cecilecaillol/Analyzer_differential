./Make.sh Control_et.cc
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/DataA.root files_control_et/DataA.root data_obs data_obs 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/DataB.root files_control_et/DataB.root data_obs data_obs 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/DataC.root files_control_et/DataC.root data_obs data_obs 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/DataD.root files_control_et/DataD.root data_obs data_obs 0
hadd -f files_control_et/Data.root files_control_et/DataA.root files_control_et/DataB.root files_control_et/DataC.root files_control_et/DataD.root
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/DY.root files_control_et/DYincl.root Z Z 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/DY1.root files_control_et/DY1.root Z Z 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/DY2.root files_control_et/DY2.root Z Z 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/DY3.root files_control_et/DY3.root Z Z 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/DY4.root files_control_et/DY4.root Z Z 0
hadd -f files_control_et/DY.root files_control_et/DYincl.root files_control_et/DY1.root files_control_et/DY2.root files_control_et/DY3.root files_control_et/DY4.root
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/Wall.root files_control_et/W.root W W 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/TTToHadronic.root files_control_et/TTToHadronic.root TTToHadronic TT 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/TTTo2L2Nu.root files_control_et/TTTo2L2Nu.root TTTo2L2Nu TT 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/TTToSemiLeptonic.root files_control_et/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_control_et/TT.root files_control_et/TTToHadronic.root files_control_et/TTTo2L2Nu.root files_control_et/TTToSemiLeptonic.root
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/WZ2L2Q.root files_control_et/WZ2L2Q.root WZ2L2Q VV 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/WZ3L1Nu.root files_control_et/WZ3L1Nu.root WZ3L1Nu VV 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VV2L2Nu.root files_control_et/VV2L2Nu.root VV2L2Nu VV 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/ZZ2L2Q.root files_control_et/ZZ2L2Q.root ZZ2L2Q VV 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/ZZ4L.root files_control_et/ZZ4L.root ZZ4L VV 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/ST_t_antitop.root files_control_et/ST_t_antitop.root ST_t_antitop ST 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/ST_t_top.root files_control_et/ST_t_top.root ST_t_top ST 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/ST_tW_antitop.root files_control_et/ST_tW_antitop.root ST_tW_antitop ST 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/ST_tW_top.root files_control_et/ST_tW_top.root ST_tW_top ST 0
hadd -f files_control_et/VV.root  files_control_et/ST_t_antitop.root files_control_et/ST_t_top.root files_control_et/ST_tW_antitop.root files_control_et/ST_tW_top.root files_control_et/WZ2L2Q.root files_control_et/WZ3L1Nu.root files_control_et/VV2L2Nu.root files_control_et/ZZ2L2Q.root files_control_et/ZZ4L.root 

./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/ggH125.root files_control_et/ggH_htt125.root ggH_htt125 ggH_htt125 0
./Control_et.exe /data/ccaillol/differentialet2018_svfitted_3aug/VBF125.root files_control_et/qqH_htt125.root qqH_htt125 qqH_htt125 0
hadd -f files_control_et/signal.root files_control_et/ggH_htt125.root files_control_et/qqH_htt125.root 

python Create_fake_et_mc.py --directory control
hadd -f smh_et_diff_2D.root files_control_et/Data.root files_control_et/DY.root files_control_et/W.root files_control_et/TT.root files_control_et/VV.root files_control_et/Fake.root files_control_et/signal.root
python Create_1D_et_differential.py
cp smh_et_diff.root smh_et_control.root

