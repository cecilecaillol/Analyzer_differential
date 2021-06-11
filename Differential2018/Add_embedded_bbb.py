import ROOT
from ROOT import *
import re
from array import array

if __name__ == "__main__":

    import ROOT
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--directory', default="diff")
    options = parser.parse_args()

    fEmbedded=ROOT.TFile("files_"+options.directory+"_em/embeddedNoBBB.root","r")
    fout=ROOT.TFile("files_"+options.directory+"_em/embedded.root","recreate")

    fEmbedded.cd()
    dirList = gDirectory.GetListOfKeys()
    for k1 in dirList:
         h1 = k1.ReadObj()
         if not "h_" in h1.GetName():
           fout.mkdir(h1.GetName())
           h1.cd()
           dirList2 = gDirectory.GetListOfKeys()
           for k2 in dirList2:
              h2 = k2.ReadObj()
              h3=h2.Clone()
              fout.cd(h1.GetName())
              for j in range(0,h3.GetSize()-2):
                 h3.SetBinError(j+1,((0.03*0.03*h3.GetBinContent(j+1)*h3.GetBinContent(j+1))+h3.GetBinError(j+1)*h3.GetBinError(j+1))**0.5)
              h3.SetName(k2.GetName())
              h3.Write()


