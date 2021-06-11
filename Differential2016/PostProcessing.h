void EmptyBins(TH2F* hist){
    float average_weight=hist->Integral()/hist->GetEntries();
    for (int nn=1; nn<hist->GetSize()-1; ++nn){
        if (hist->GetBinContent(nn)<0){
            hist->SetBinContent(nn,0.0);
            //if (hist->GetEntries()>0 && (hist->GetBinContent(nn-1)>0.0001 or hist->GetBinContent(nn+1)>0.0001)) hist->SetBinError(nn,1.8*average_weight);
        }
    }
    hist->SetBinContent(0,0);
    hist->SetBinContent(hist->GetSize()-1,0);
    hist->SetBinError(0,0);
    hist->SetBinError(hist->GetSize()-1,0);
}

