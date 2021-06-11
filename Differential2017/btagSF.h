double GetSF(int WP, float x, int flavour, int syst){

   if (WP==1){
      if (fabs(flavour)==4 or fabs(flavour)==5){
        if (syst==0 or syst==2 or syst==-2){
	   return 1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18)))))));
        }
	if (fabs(flavour)==4 and syst==1){
	   if (x>=20 and x<30) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.085154704749584198;
           if (x>=30 and x<50) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.034145798534154892;
           if (x>=50 and x<70) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.034354850649833679;
           if (x>=70 and x<100) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.031172541901469231;
           if (x>=100 and x<140) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.03231281042098999;
           if (x>=140 and x<200) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.03636125847697258;
           if (x>=200 and x<300) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.060606949031352997;
           if (x>=300 and x<600) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.10067618638277054;
           if (x>=600) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.15710783004760742;
	}
        if (fabs(flavour)==4 and syst==-1){
           if (x>=20 and x<30) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.085154704749584198;
           if (x>=30 and x<50) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.034145798534154892;
           if (x>=50 and x<70) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.034354850649833679;
           if (x>=70 and x<100) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.031172541901469231;
           if (x>=100 and x<140) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.03231281042098999;
           if (x>=140 and x<200) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.03636125847697258;
           if (x>=200 and x<300) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.060606949031352997;
           if (x>=300 and x<600) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.10067618638277054;
           if (x>=600) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.15710783004760742;
        }
        if (fabs(flavour)==5 and syst==1){
           if (x>=20 and x<30) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.034061882644891739;
           if (x>=30 and x<50) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.013658319599926472;
           if (x>=50 and x<70) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.013741940259933472;
           if (x>=70 and x<100) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.012469016946852207;
           if (x>=100 and x<140) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.012925124727189541;
           if (x>=140 and x<200) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.014544503763318062;
           if (x>=200 and x<300) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.024242779240012169;
           if (x>=300 and x<600) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.040270473808050156;
           if (x>=600) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))+0.06284312903881073;
        }
        if (fabs(flavour)==5 and syst==-1){
           if (x>=20 and x<30) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.034061882644891739;
           if (x>=30 and x<50) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.013658319599926472;
           if (x>=50 and x<70) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.013741940259933472;
           if (x>=70 and x<100) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.012469016946852207;
           if (x>=100 and x<140) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.012925124727189541;
           if (x>=140 and x<200) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.014544503763318062;
           if (x>=200 and x<300) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.024242779240012169;
           if (x>=300 and x<600) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.040270473808050156;
           if (x>=600) return (1.0942+(-(0.00468151*(log(x+19)*(log(x+18)*(3-(0.365115*log(x+18))))))))-0.06284312903881073;
        }

      }
      else {
        if (syst==0 or syst==1 or syst==-1) return 1.07073+0.000128481*x+6.16477e-07*x*x+-5.65803e-10*x*x*x;
	if (syst==-2) return (1.07073+0.000128481*x+6.16477e-07*x*x+-5.65803e-10*x*x*x)*(1-(0.0485052+3.93839e-05*x+-4.90281e-08*x*x));
	if (syst==2) return (1.07073+0.000128481*x+6.16477e-07*x*x+-5.65803e-10*x*x*x)*(1+(0.0485052+3.93839e-05*x+-4.90281e-08*x*x));
     }
   }
   else return 0;
}


double bTagEventWeight(int nBtaggedJets, float bjetpt_1, int bjetflavour_1, float bjetpt_2, int bjetflavour_2, int WP, int syst, int nBTags)
{
  if (nBtaggedJets > 2) return -10000;
  if( nBTags > 2 ) return -10000;

  /*
    ##################################################################
    Event weight matrix:
    ------------------------------------------------------------------
    nBTags\b-tagged jets  |    0        1             2
    ------------------------------------------------------------------
      0                   |    1      1-SF      (1-SF1)(1-SF2)
                          |
      1                   |    0       SF    SF1(1-SF2)+(1-SF1)SF2
                          |
      2                   |    0        0           SF1SF2
    ##################################################################
  */
  
  if( nBTags > nBtaggedJets) return 0;
  if( nBTags==0 && nBtaggedJets==0) return 1;

  double weight = 0;
  if(nBtaggedJets==1){
    double SF = GetSF(WP,bjetpt_1,bjetflavour_1,syst);
    for( unsigned int i=0; i<=1; ++i ){
      if( i != nBTags ) continue;
      weight += pow(SF,i)*pow(1-SF,1-i);
    }
  }
  else if(nBtaggedJets==2 ){
    double SF1 = GetSF(WP,bjetpt_1,bjetflavour_1,syst);
    double SF2 = GetSF(WP,bjetpt_2,bjetflavour_2,syst);
    
    for( unsigned int i=0; i<=1; ++i ){
      for( unsigned int j=0; j<=1; ++j ){
        if( (i+j) != nBTags ) continue;
        weight += pow(SF1,i)*pow(1-SF1,1-i)*pow(SF2,j)*pow(1-SF2,1-j);
      }
    }
  }
  return weight;
}
