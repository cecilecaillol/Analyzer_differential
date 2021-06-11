./Make.sh ControlPlots_et.cc
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DataB.root files_control_et/DataB.root data_obs data_obs 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DataC.root files_control_et/DataC.root data_obs data_obs 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DataD.root files_control_et/DataD.root data_obs data_obs 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DataE.root files_control_et/DataE.root data_obs data_obs 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DataF.root files_control_et/DataF.root data_obs data_obs 0
hadd -f files_control_et/Data.root files_control_et/DataB.root files_control_et/DataC.root files_control_et/DataD.root files_control_et/DataE.root files_control_et/DataF.root 
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DY_v1.root files_control_et/DY_v1.root Z Z 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DY_v2.root files_control_et/DY_v2.root Z Z 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DY1.root files_control_et/DY1.root Z Z 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DY2.root files_control_et/DY2.root Z Z 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DY3.root files_control_et/DY3.root Z Z 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DY4_v1.root files_control_et/DY4_v1.root Z Z 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/DY4_v2.root files_control_et/DY4_v2.root Z Z 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/EWKZLL.root files_control_et/EWKZLL.root EWKZLL Z 0
hadd -f files_control_et/DY.root files_control_et/DY_v1.root files_control_et/DY_v2.root files_control_et/DY1.root files_control_et/DY2.root files_control_et/DY3.root files_control_et/DY4_v1.root files_control_et/DY4_v2.root files_control_et/EWKZLL.root
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/TTToHadronic.root files_control_et/TTToHadronic.root TTToHadronic TT 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/TTTo2L2Nu.root files_control_et/TTTo2L2Nu.root TTTo2L2Nu TT 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/TTToSemiLeptonic.root files_control_et/TTToSemiLeptonic.root TTToSemiLeptonic TT 0
hadd -f files_control_et/TT.root files_control_et/TTToHadronic.root files_control_et/TTTo2L2Nu.root files_control_et/TTToSemiLeptonic.root
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/WZ2L2Q.root files_control_et/WZ2L2Q.root WZ2L2Q VV 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/WZ3L1Nu.root files_control_et/WZ3L1Nu.root WZ3L1Nu VV 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/VV2L2Nu.root files_control_et/VV2L2Nu.root VV2L2Nu VV 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ZZ2L2Q.root files_control_et/ZZ2L2Q.root ZZ2L2Q VV 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ZZ4L.root files_control_et/ZZ4L.root ZZ4L VV 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ST_t_antitop_v1.root files_control_et/ST_t_antitop_v1.root ST_t_antitop ST 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ST_t_antitop_v2.root files_control_et/ST_t_antitop_v2.root ST_t_antitop ST 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ST_t_top.root files_control_et/ST_t_top.root ST_t_top ST 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ST_tW_antitop.root files_control_et/ST_tW_antitop.root ST_tW_antitop ST 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ST_tW_top_v1.root files_control_et/ST_tW_top_v1.root ST_tW_top ST 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ST_tW_top_v2.root files_control_et/ST_tW_top_v2.root ST_tW_top ST 0
hadd -f files_control_et/VV.root files_control_et/ST_t_antitop_v1.root files_control_et/ST_t_antitop_v2.root files_control_et/ST_t_top.root files_control_et/ST_tW_antitop.root files_control_et/ST_tW_top_v1.root files_control_et/ST_tW_top_v2.root files_control_et/WZ2L2Q.root files_control_et/WZ3L1Nu.root files_control_et/VV2L2Nu.root files_control_et/ZZ2L2Q.root files_control_et/ZZ4L.root 
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/ggH125.root files_control_et/ggH_htt125.root ggH_htt125 ggH_htt125 0
./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/VBF125.root files_control_et/qqH_htt125.root qqH_htt125 qqH_htt125 0


#./ControlPlots_et.exe /data/ccaillol/differentialet2017_svfitted_3aug/Embedded.root files_control_et/embedded.root embedded embedded 0
#python Add_embedded_shape_et.py --directory control
#python Create_fake_et_embedded.py --directory control

python Create_fake_et_mc.py --directory control

hadd -f smh_et_control_2D.root files_control_et/Data.root files_control_et/embedded.root files_control_et/embeddedShape.root files_control_et/DY.root files_control_et/TT.root files_control_et/VV.root files_control_et/Fake.root 
python Create_1D_et_control.py

