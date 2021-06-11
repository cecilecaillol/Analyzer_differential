if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    parser.add_argument('--directory', default="nominal")
    options = parser.parse_args()

    fEmbedded=ROOT.TFile("files_"+options.directory+"_em/embedded.root","r")
    fTT=ROOT.TFile("files_"+options.directory+"_em/TT.root","r")
    fout=ROOT.TFile("files_"+options.directory+"_em/embeddedShape.root","recreate")

    categories=["em_0jet","em_boosted","em_vbf","em_0jetlow","em_0jethigh","em_boosted1","em_boosted2","em_vbflow","em_vbfhigh"]
    ncat=9

    for i in range(0,ncat):
       h_nominal=fEmbedded.Get("em_0jet/embedded").Clone()
       h_tt=fTT.Get("em_0jet/ttcontamination").Clone()
       if i==1:
          h_nominal=fEmbedded.Get("em_boosted/embedded").Clone()
          h_tt=fTT.Get("em_boosted/ttcontamination").Clone()
       if i==2:
          h_nominal=fEmbedded.Get("em_vbf/embedded").Clone()
          h_tt=fTT.Get("em_vbf/ttcontamination").Clone()
       if i==3:
          h_nominal=fEmbedded.Get("em_0jetlow/embedded").Clone()
          h_tt=fTT.Get("em_0jetlow/ttcontamination").Clone()
       if i==4:
          h_nominal=fEmbedded.Get("em_0jethigh/embedded").Clone()
          h_tt=fTT.Get("em_0jethigh/ttcontamination").Clone()
       if i==5:
          h_nominal=fEmbedded.Get("em_boosted1/embedded").Clone()
          h_tt=fTT.Get("em_boosted1/ttcontamination").Clone()
       if i==6:
          h_nominal=fEmbedded.Get("em_boosted2/embedded").Clone()
          h_tt=fTT.Get("em_boosted2/ttcontamination").Clone()
       if i==7:
          h_nominal=fEmbedded.Get("em_vbflow/embedded").Clone()
          h_tt=fTT.Get("em_vbflow/ttcontamination").Clone()
       if i==8:
          h_nominal=fEmbedded.Get("em_vbfhigh/embedded").Clone()
          h_tt=fTT.Get("em_vbfhigh/ttcontamination").Clone()
       h_up=h_nominal.Clone()
       h_down=h_nominal.Clone()
       print h_tt.Integral()
       h_up.Add(h_tt,0.10)
       h_down.Add(h_tt,-0.10)

       fout.cd()
       mydir=fout.mkdir(categories[i])
       mydir.cd()
       h_up.SetName("embedded_CMS_htt_emb_ttbar_2017Up")
       h_up.Write()
       h_down.SetName("embedded_CMS_htt_emb_ttbar_2017Down")
       h_down.Write()

