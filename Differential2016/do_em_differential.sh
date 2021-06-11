./Make.sh FinalSelection_em.cc
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataB.root files_diff_em/DataB.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataC.root files_diff_em/DataC.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataD.root files_diff_em/DataD.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataE.root files_diff_em/DataE.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataF.root files_diff_em/DataF.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataG.root files_diff_em/DataG.root data_obs data_obs 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DataH.root files_diff_em/DataH.root data_obs data_obs 0
hadd -f files_diff_em/Data.root files_diff_em/DataB.root files_diff_em/DataC.root files_diff_em/DataD.root files_diff_em/DataE.root files_diff_em/DataF.root files_diff_em/DataG.root files_diff_em/DataH.root
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DY.root files_diff_em/DYincl.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DY1.root files_diff_em/DY1.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DY2.root files_diff_em/DY2.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DY3.root files_diff_em/DY3.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/DY4.root files_diff_em/DY4.root Z Z 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/EWKZLL.root files_diff_em/EWKZLL.root EWKZLL Z 0
hadd -f files_diff_em/DY.root files_diff_em/DYincl.root files_diff_em/DY1.root files_diff_em/DY2.root files_diff_em/DY3.root files_diff_em/DY4.root files_diff_em/EWKZLL.root
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/Wall.root files_diff_em/W.root W W 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/TT.root files_diff_em/TT.root TT TT 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/WZ2L2Q.root files_diff_em/WZ2L2Q.root WZ2L2Q VV 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/WZ3L1Nu.root files_diff_em/WZ3L1Nu.root WZ3L1Nu VV 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VV2L2Nu.root files_diff_em/VV2L2Nu.root VV2L2Nu VV 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ZZ2L2Q.root files_diff_em/ZZ2L2Q.root ZZ2L2Q VV 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ZZ4L.root files_diff_em/ZZ4L.root ZZ4L VV 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ST_t_antitop.root files_diff_em/ST_t_antitop.root ST_t_antitop ST 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ST_t_top.root files_diff_em/ST_t_top.root ST_t_top ST 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ST_tW_antitop.root files_diff_em/ST_tW_antitop.root ST_tW_antitop ST 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ST_tW_top.root files_diff_em/ST_tW_top.root ST_tW_top ST 0
hadd -f files_diff_em/VV.root files_diff_em/ST_t_antitop.root files_diff_em/ST_t_top.root files_diff_em/ST_tW_antitop.root files_diff_em/ST_tW_top.root files_diff_em/WZ2L2Q.root files_diff_em/WZ3L1Nu.root files_diff_em/VV2L2Nu.root files_diff_em/ZZ2L2Q.root files_diff_em/ZZ4L.root 

./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ggH125.root files_diff_em/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/WplusH125.root files_diff_em/Wplus125.root WplusH125 WH_htt125 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/WminusH125.root files_diff_em/WminusH125.root WminusH125 WH_htt125 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ZH125.root files_diff_em/ZH125.root ZH125 ZH_htt125 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ttHnonbb.root files_diff_em/ttHnonbb125.root ttHnonbb ttH_htt125 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/GGZHLLTT.root files_diff_em/GGZHLLTT.root GGZHLLTT125 ZH_htt125 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/GGZHNNTT.root files_diff_em/GGZHNNTT.root GGZHNNTT125 ZH_htt125 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/GGZHQQTT.root files_diff_em/GGZHQQTT.root GGZHQQTT125 ZH_htt125 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/GGHWW.root files_diff_em/GGHWW.root GGHWW OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBFHWW.root files_diff_em/VBFHWW.root VBFHWW OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/WplusHWW.root files_diff_em/WplusHWW.root WplusHWW OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/WminusHWW.root files_diff_em/WminusHWW.root WminusHWW OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ZHWW.root files_diff_em/ZHWW.root ZHWW OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/GGZHWW.root files_diff_em/GGZHWW.root GGZHWW OutsideAcceptance 0
hadd -f files_diff_em/signal.root files_diff_em/ggH_htt125.root files_diff_em/qqH_htt125.root files_diff_em/Wplus125.root files_diff_em/WminusH125.root files_diff_em/ZH125.root files_diff_em/ttHnonbb125.root files_diff_em/GGZHLLTT.root files_diff_em/GGZHNNTT.root files_diff_em/GGZHQQTT.root files_diff_em/GGHWW.root files_diff_em/VBFHWW.root files_diff_em/WplusHWW.root files_diff_em/WminusHWW.root files_diff_em/ZHWW.root files_diff_em/GGZHWW.root 

./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ggH125.root files_diff_em/ggH_htt125_nonfid.root ggH_htt125 OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/VBF125.root files_diff_em/qqH_htt125_nonfid.root qqH_htt125 OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/WplusH125.root files_diff_em/Wplus125_nonfid.root WplusH125 OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/WminusH125.root files_diff_em/WminusH125_nonfid.root WminusH125 OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ZH125.root files_diff_em/ZH125_nonfid.root ZH125 OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/ttHnonbb.root files_diff_em/ttHnonbb125_nonfid.root ttHnonbb OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/GGZHLLTT.root files_diff_em/GGZHLLTT_nonfid.root GGZHLLTT125 OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/GGZHNNTT.root files_diff_em/GGZHNNTT_nonfid.root GGZHNNTT125 OutsideAcceptance 0
./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/GGZHQQTT.root files_diff_em/GGZHQQTT_nonfid.root GGZHQQTT125 OutsideAcceptance 0
hadd -f files_diff_em/signal_nonfid.root files_diff_em/ggH_htt125_nonfid.root files_diff_em/qqH_htt125_nonfid.root files_diff_em/Wplus125_nonfid.root files_diff_em/WminusH125_nonfid.root files_diff_em/ZH125_nonfid.root files_diff_em/ttHnonbb125_nonfid.root files_diff_em/GGZHLLTT_nonfid.root files_diff_em/GGZHQQTT_nonfid.root files_diff_em/GGZHNNTT_nonfid.root 

sh signal_differential_ggH_htt_em.sh
sh signal_differential_qqH_htt_em.sh
sh signal_differential_WplusH_htt_em.sh
sh signal_differential_WminusH_htt_em.sh
sh signal_differential_ZH_htt_em.sh
sh signal_differential_GGZHLLTT_htt_em.sh
sh signal_differential_GGZHNNTT_htt_em.sh
sh signal_differential_GGZHQQTT_htt_em.sh
sh signal_differential_ttH_htt_em.sh

sh signal_recodifferential_ggH_htt_em.sh
sh signal_recodifferential_qqH_htt_em.sh

./FinalSelection_em.exe /data/ccaillol/differentialem2016_svfitted_3aug/embedded.root files_diff_em/embeddedNoBBB.root embedded embedded 0
python Create_fake_em_embedded.py --directory diff 
python Add_embedded_shape_em.py --directory diff 
python Add_embedded_bbb.py --directory diff
hadd -f smh_em_diff_2D.root files_diff_em/Data.root files_diff_em/embedded.root files_diff_em/DY.root files_diff_em/W.root files_diff_em/TT.root files_diff_em/VV.root files_diff_em/Fake.root files_diff_em/signal.root files_diff_em/signal_nonfid.root files_diff_em/embeddedShape.root files_diff_em/diff_ggH.root files_diff_em/diff_qqH.root files_diff_em/diff_WplusH.root files_diff_em/diff_WminusH.root files_diff_em/diff_ZH.root files_diff_em/diff_GGZHLLTT.root files_diff_em/diff_GGZHNNTT.root files_diff_em/diff_GGZHQQTT.root files_diff_em/diff_ttH.root files_diff_em/recodiff_ggH.root files_diff_em/recodiff_qqH.root
python Create_1D_em_differential.py
cp smh_em_diff.root smh_em_diff_embedded.root

#python Create_fake_em_mc.py --directory diff
#hadd -f smh_em_diff_2D.root files_diff_em/Data.root files_diff_em/DY.root files_diff_em/W.root files_diff_em/TT.root files_diff_em/VV.root files_diff_em/Fake.root files_diff_em/signal.root files_diff_em/signal_nonfid.root files_diff_em/diff_ggH.root files_diff_em/diff_qqH.root files_diff_em/diff_WplusH.root files_diff_em/diff_WminusH.root files_diff_em/diff_ZH.root files_diff_em/diff_GGZHLLTT.root files_diff_em/diff_GGZHNNTT.root files_diff_em/diff_GGZHQQTT.root files_diff_em/diff_ttH.root #files_diff_em/recodiff_ggH.root files_diff_em/recodiff_qqH.root
#python Create_1D_em_differential.py
#cp smh_em_diff.root smh_em_diff_mc.root


