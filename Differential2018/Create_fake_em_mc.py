if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--scale', default="nominal", choices=['nominal', 'up', 'down', 'wup', 'wdown','qcdup','qcddown','JESup','JESdown'], help="Which TES?")
    parser.add_argument('--directory', default="nominal")
    options = parser.parse_args()

    nbhist=1
    #nbhist=15
    #postfix=["","_CMS_QCD_njet0_intercept_2018Down","_CMS_QCD_njet0_intercept_2018Up","_CMS_QCD_njet0_slope_2018Down","_CMS_QCD_njet0_slope_2018Up","_CMS_QCD_njet1_intercept_2018Down","_CMS_QCD_njet1_intercept_2018Up","_CMS_QCD_njet1_slope_2018Down","_CMS_QCD_njet1_slope_2018Up","_CMS_QCD_njet2_intercept_2018Down","_CMS_QCD_njet2_intercept_2018Up","_CMS_QCD_njet2_slope_2018Down","_CMS_QCD_njet2_slope_2018Up","_CMS_QCD_antiiso_2018Down","_CMS_QCD_antiiso_2018Up"]
    nbhist=37
    if options.directory=="control": nbhist=1
    postfix=["","_CMS_QCD_njet0_intercept_2018Down","_CMS_QCD_njet0_intercept_2018Up","_CMS_QCD_njet0_slope_2018Down","_CMS_QCD_njet0_slope_2018Up","_CMS_QCD_njet1_intercept_2018Down","_CMS_QCD_njet1_intercept_2018Up","_CMS_QCD_njet1_slope_2018Down","_CMS_QCD_njet1_slope_2018Up","_CMS_QCD_njet2_intercept_2018Down","_CMS_QCD_njet2_intercept_2018Up","_CMS_QCD_njet2_slope_2018Down","_CMS_QCD_njet2_slope_2018Up","_CMS_QCD_antiiso_2018Down","_CMS_QCD_antiiso_2018Up","_CMS_QCD_stat_pte15to25_ptmu15to25_2018Down","_CMS_QCD_stat_pte15to25_ptmu15to25_2018Up","_CMS_QCD_stat_pte15to25_ptmugt25_2018Down","_CMS_QCD_stat_pte15to25_ptmugt25_2018Up","_CMS_QCD_stat_pte25to35_ptmu15to25_2018Down","_CMS_QCD_stat_pte25to35_ptmu15to25_2018Up","_CMS_QCD_stat_pte25to35_ptmugt25_2018Down","_CMS_QCD_stat_pte25to35_ptmugt25_2018Up","_CMS_QCD_stat_ptegt35_ptmu15to25_2018Down","_CMS_QCD_stat_ptegt35_ptmu15to25_2018Up","_CMS_QCD_stat_ptegt35_ptmugt25_2018Down","_CMS_QCD_stat_ptegt35_ptmugt25_2018Up","_CMS_QCD_norm_0jet_2018Down","_CMS_QCD_norm_0jet_2018Up","_CMS_QCD_norm_1jet_2018Down","_CMS_QCD_norm_1jet_2018Up","_CMS_QCD_norm_2jet_2018Down","_CMS_QCD_norm_2jet_2018Up","_CMS_QCD_norm_3jet_2018Down","_CMS_QCD_norm_3jet_2018Up","_CMS_QCD_norm_4jet_2018Down","_CMS_QCD_norm_4jet_2018Up"]

    fData=ROOT.TFile("files_"+options.directory+"_em/Data.root","r")
    fDY=ROOT.TFile("files_"+options.directory+"_em/DY.root","r")
    fEmbedded=ROOT.TFile("files_"+options.directory+"_em/DY.root","r")
    fTT=ROOT.TFile("files_"+options.directory+"_em/TT.root","r")
    fW=ROOT.TFile("files_"+options.directory+"_em/W.root","r")
    fVV=ROOT.TFile("files_"+options.directory+"_em/VV.root","r")
    fgg=ROOT.TFile("files_"+options.directory+"_em/ggH_htt125.root","r")
    fqq=ROOT.TFile("files_"+options.directory+"_em/qqH_htt125.root","r")
    fout=ROOT.TFile("files_"+options.directory+"_em/Fake.root","recreate")

    categories=["0jet","boosted","vbf","0jetlow","0jethigh","boosted1","boosted2","vbflow","vbfhigh"]
    ncat=9

    for c in range(0,ncat):

      h_0jet=[]
      h_0jetZL=[]
      h_0jetZTT=[]

      hAI_0jet=[]
      hAI_0jetZL=[]
      hAI_0jetZTT=[]

      for k in range(0,nbhist):
        h_0jet.append(fData.Get("SS"+categories[c]+"/data_obs"+postfix[k]))
        h_0jetZTT.append(fEmbedded.Get("SS"+categories[c]+"/ZT"+postfix[k]))
        h_0jetZL.append(fTT.Get("SS"+categories[c]+"/TTL"+postfix[k]))
        h_0jetZL[k].Add(fVV.Get("SS"+categories[c]+"/VVL"+postfix[k])) #FIXME
        h_0jetZL[k].Add(fDY.Get("SS"+categories[c]+"/ZL"+postfix[k])) #FIXME
        h_0jetZL[k].Add(fVV.Get("SS"+categories[c]+"/STL"+postfix[k])) #FIXME
        h_0jetZL[k].Add(fgg.Get("SS"+categories[c]+"/ggH_htt125")) # FIXME
        h_0jetZL[k].Add(fqq.Get("SS"+categories[c]+"/qqH_htt125")) # FIXME

        hAI_0jet.append(fData.Get("AI"+categories[c]+"/data_obs"+postfix[k]))
        hAI_0jetZTT.append(fEmbedded.Get("AI"+categories[c]+"/ZT"+postfix[k]))
        hAI_0jetZL.append(fDY.Get("AI"+categories[c]+"/ZL"+postfix[k]))
        hAI_0jetZL[k].Add(fTT.Get("AI"+categories[c]+"/TTL"+postfix[k]))
        hAI_0jetZL[k].Add(fVV.Get("AI"+categories[c]+"/STL"+postfix[k]))
        hAI_0jetZL[k].Add(fVV.Get("AI"+categories[c]+"/VVL"+postfix[k]))

      fout.cd()
      dir0jet=fout.mkdir("em_"+categories[c])
      dir0jet.cd()
      for k in range(0,nbhist):
        h_0jet[k].Add(h_0jetZTT[k],-1)
        h_0jet[k].Add(h_0jetZL[k],-1)
        for l in range(0,h_0jet[k].GetSize()):
          if (h_0jet[k].GetBinContent(l+1)<0):
             h_0jet[k].SetBinError(l+1,h_0jet[k].GetBinContent(l+1)+h_0jet[k].GetBinError(l+1))
             h_0jet[k].SetBinContent(l+1,0)
        #if h_0jet[k].Integral()<100 and c==8 and options.directory=="nominal": #FIXME remove QCD from VBF high
        #  for l in range(0,h_0jet[k].GetSize()):
        #    h_0jet[k].SetBinContent(l+1,0)
        #    h_0jet[k].SetBinError(l+1,0)
        h_0jet[k].SetName("QCD"+postfix[k])

        hAI_0jet[k].Add(hAI_0jetZTT[k],-1)
        hAI_0jet[k].Add(hAI_0jetZL[k],-1)
        for l in range(0,hAI_0jet[k].GetSize()):
          if (hAI_0jet[k].GetBinContent(l+1)<0):
             hAI_0jet[k].SetBinContent(l+1,0)
        hAI_0jet[k].SetName("QCD"+postfix[k])
	print k,postfix[k],h_0jet[k].Integral(),hAI_0jet[k].Integral()
	hAI_0jet[k].Scale(h_0jet[k].Integral()/(hAI_0jet[k].Integral()+0.0001))

        if c>=700:
           hAI_0jet[k].Write()
	else:
           h_0jet[k].Write()

