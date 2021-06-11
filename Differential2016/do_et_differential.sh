./Make.sh FinalSelection_et.cc
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DataB.root files_diff_et/DataB.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DataC.root files_diff_et/DataC.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DataD.root files_diff_et/DataD.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DataE.root files_diff_et/DataE.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DataF.root files_diff_et/DataF.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DataG.root files_diff_et/DataG.root data_obs data_obs 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DataH.root files_diff_et/DataH.root data_obs data_obs 0
hadd -f files_diff_et/Data.root files_diff_et/DataB.root files_diff_et/DataC.root files_diff_et/DataD.root files_diff_et/DataE.root files_diff_et/DataF.root files_diff_et/DataG.root files_diff_et/DataH.root
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DY.root files_diff_et/DYincl.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DY1.root files_diff_et/DY1.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DY2.root files_diff_et/DY2.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DY3.root files_diff_et/DY3.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/DY4.root files_diff_et/DY4.root Z Z 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/EWKZLL.root files_diff_et/EWKZLL.root EWKZLL Z 0
hadd -f files_diff_et/DY.root files_diff_et/DYincl.root files_diff_et/DY1.root files_diff_et/DY2.root files_diff_et/DY3.root files_diff_et/DY4.root files_diff_et/EWKZLL.root
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/W.root files_diff_et/Wincl.root W W 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/W1.root files_diff_et/W1.root W W 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/W2.root files_diff_et/W2.root W W 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/W3.root files_diff_et/W3.root W W 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/W4.root files_diff_et/W4.root W W 0
hadd -f files_diff_et/W.root files_diff_et/Wincl.root files_diff_et/W1.root files_diff_et/W2.root files_diff_et/W3.root files_diff_et/W4.root
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/TT.root files_diff_et/TT.root TT TT 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/WZ2L2Q.root files_diff_et/WZ2L2Q.root WZ2L2Q VV 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/WZ3L1Nu.root files_diff_et/WZ3L1Nu.root WZ3L1Nu VV 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/VV2L2Nu.root files_diff_et/VV2L2Nu.root VV2L2Nu VV 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ZZ2L2Q.root files_diff_et/ZZ2L2Q.root ZZ2L2Q VV 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ZZ4L.root files_diff_et/ZZ4L.root ZZ4L VV 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ST_t_antitop.root files_diff_et/ST_t_antitop.root ST_t_antitop ST 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ST_t_top.root files_diff_et/ST_t_top.root ST_t_top ST 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ST_tW_antitop.root files_diff_et/ST_tW_antitop.root ST_tW_antitop ST 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ST_tW_top.root files_diff_et/ST_tW_top.root ST_tW_top ST 0
hadd -f files_diff_et/VV.root files_diff_et/ST_t_antitop.root files_diff_et/ST_t_top.root files_diff_et/ST_tW_antitop.root files_diff_et/ST_tW_top.root files_diff_et/WZ2L2Q.root files_diff_et/WZ3L1Nu.root files_diff_et/VV2L2Nu.root files_diff_et/ZZ2L2Q.root files_diff_et/ZZ4L.root

./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ggH125.root files_diff_et/ggH_htt125.root ggH_htt125 ggH_htt125 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/VBF125.root files_diff_et/qqH_htt125.root qqH_htt125 qqH_htt125 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/WplusH125.root files_diff_et/Wplus125.root WplusH125 WH_htt125 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/WminusH125.root files_diff_et/WminusH125.root WminusH125 WH_htt125 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ZH125.root files_diff_et/ZH125.root ZH125 ZH_htt125 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ttHnonbb.root files_diff_et/ttHnonbb125.root ttHnonbb ttH_htt125 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/GGZHLLTT.root files_diff_et/GGZHLLTT.root GGZHLLTT125 ZH_htt125 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/GGZHNNTT.root files_diff_et/GGZHNNTT.root GGZHNNTT125 ZH_htt125 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/GGZHQQTT.root files_diff_et/GGZHQQTT.root GGZHQQTT125 ZH_htt125 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/GGHWW.root files_diff_et/GGHWW.root GGHWW OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/VBFHWW.root files_diff_et/VBFHWW.root VBFHWW OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/WplusHWW.root files_diff_et/WplusHWW.root WplusHWW OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/WminusHWW.root files_diff_et/WminusHWW.root WminusHWW OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ZHWW.root files_diff_et/ZHWW.root ZHWW OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/GGZHWW.root files_diff_et/GGZHWW.root GGZHWW OutsideAcceptance 0
hadd -f files_diff_et/signal.root files_diff_et/ggH_htt125.root files_diff_et/qqH_htt125.root files_diff_et/Wplus125.root files_diff_et/WminusH125.root files_diff_et/ZH125.root files_diff_et/ttHnonbb125.root files_diff_et/GGZHLLTT.root files_diff_et/GGZHQQTT.root files_diff_et/GGZHNNTT.root files_diff_et/GGHWW.root files_diff_et/VBFHWW.root files_diff_et/WplusHWW.root files_diff_et/WminusHWW.root files_diff_et/ZHWW.root files_diff_et/GGZHWW.root

./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ggH125.root files_diff_et/ggH_htt125_nonfid.root ggH_htt125 OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/VBF125.root files_diff_et/qqH_htt125_nonfid.root qqH_htt125 OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/WplusH125.root files_diff_et/Wplus125_nonfid.root WplusH125 OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/WminusH125.root files_diff_et/WminusH125_nonfid.root WminusH125 OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ZH125.root files_diff_et/ZH125_nonfid.root ZH125 OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/ttHnonbb.root files_diff_et/ttHnonbb125_nonfid.root ttHnonbb OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/GGZHLLTT.root files_diff_et/GGZHLLTT_nonfid.root GGZHLLTT125 OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/GGZHLLTT.root files_diff_et/GGZHNNTT_nonfid.root GGZHNNTT125 OutsideAcceptance 0
./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/GGZHQQTT.root files_diff_et/GGZHQQTT_nonfid.root GGZHQQTT125 OutsideAcceptance 0
hadd -f files_diff_et/signal_nonfid.root files_diff_et/ggH_htt125_nonfid.root files_diff_et/qqH_htt125_nonfid.root files_diff_et/Wplus125_nonfid.root files_diff_et/WminusH125_nonfid.root files_diff_et/ZH125_nonfid.root files_diff_et/ttHnonbb125_nonfid.root files_diff_et/GGZHLLTT_nonfid.root files_diff_et/GGZHQQTT_nonfid.root files_diff_et/GGZHNNTT_nonfid.root 

sh signal_differential_ggH_htt_et.sh
sh signal_differential_qqH_htt_et.sh
sh signal_differential_WplusH_htt_et.sh
sh signal_differential_WminusH_htt_et.sh
sh signal_differential_ZH_htt_et.sh
sh signal_differential_GGZHLLTT_htt_et.sh
sh signal_differential_GGZHNNTT_htt_et.sh
sh signal_differential_GGZHQQTT_htt_et.sh
sh signal_differential_ttH_htt_et.sh

sh signal_recodifferential_ggH_htt_et.sh
sh signal_recodifferential_qqH_htt_et.sh

./FinalSelection_et.exe /data/ccaillol/differentialet2016_svfitted_3aug/embedded.root files_diff_et/embedded.root embedded embedded 0
python Add_embedded_shape_et.py --directory diff
python Create_fake_et_embedded.py --directory diff
hadd -f smh_et_diff_2D.root files_diff_et/Data.root files_diff_et/embedded.root files_diff_et/DY.root files_diff_et/W.root files_diff_et/TT.root files_diff_et/VV.root files_diff_et/Fake.root files_diff_et/signal.root files_diff_et/signal_nonfid.root files_diff_et/embeddedShape.root files_diff_et/diff_ggH.root files_diff_et/diff_qqH.root files_diff_et/diff_WplusH.root files_diff_et/diff_WminusH.root files_diff_et/diff_ZH.root files_diff_et/diff_GGZHLLTT.root files_diff_et/diff_GGZHNNTT.root files_diff_et/diff_GGZHQQTT.root files_diff_et/diff_ttH.root files_diff_et/recodiff_ggH.root files_diff_et/recodiff_qqH.root
python Create_1D_et_differential.py
cp smh_et_diff.root smh_et_diff_embedded.root

##python Create_fake_et_mc.py --directory diff 
##hadd -f smh_et_diff_2D.root files_diff_et/Data.root files_diff_et/DY.root files_diff_et/W.root files_diff_et/TT.root files_diff_et/VV.root files_diff_et/Fake.root files_diff_et/signal.root files_diff_et/signal_nonfid.root files_diff_et/diff_ggH.root files_diff_et/diff_qqH.root files_diff_et/diff_WplusH.root files_diff_et/diff_WminusH.root files_diff_et/diff_ZH.root files_diff_et/diff_GGZHLLTT.root files_diff_et/diff_GGZHNNTT.root files_diff_et/diff_GGZHQQTT.root files_diff_et/diff_ttH.root #files_diff_et/recodiff_ggH.root files_diff_et/recodiff_qqH.root
##python Create_1D_et_differential.py
##cp smh_et_diff.root smh_et_diff_mc.root

