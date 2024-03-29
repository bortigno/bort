countExpDYL=SFLight*countSignalCCDYL;
countExpTTbar=SFTTbar*countSignalCCTTbar;
countExpDYB=SFHeavy*countSignalCCDYB;

errorExpDYL=Sqrt[ D[countExpDYL, SFLight]^2 * errorSFLight + D[countExpDYL,countSignalCCDYL]^2 * errorSignalCCDYL ];
errorExpTTbar=Sqrt[ D[countExpTTbar, SFTTbar]^2 * errorSFTTbar + D[countExpTTbar,countSignalCCTTbar]^2 * errorSignalCCTTbar ];
errorExpDYB=Sqrt[ D[countExpDYB, SFHeavy]^2 * errorSFHeavy + D[countExpDYB,countSignalCCDYB]^2 * errorSignalCCDYB ];

countBackExp=SFLight*countSignalCCDYL + SFTTbar*countSignalCCTTbar + SFHeavy*countSignalCCDYB + countSignalCCVV + countSignalCCST;

errorBackExp= Sqrt[( D[countBackExp,SFLight]^2 * errorSFLight^2 +
		     D[countBackExp,countSignalCCDYL]^2 * errorSignalCCDYL^2 +
		     D[countBackExp,SFTTbar]^2 * errorSFTTbar^2 +
		     D[countBackExp,countSignalCCTTbar]^2 * errorSignalCCTTbar^2 +
		     D[countBackExp,SFHeavy]^2 * errorSFHeavy^2 +
		     D[countBackExp,countSignalCCDYB]^2 * errorSignalCCDYB^2 +
		     D[countBackExp,countSignalCCVV]^2 * errorSignalCCVV^2 +
		     D[countBackExp,countSignalCCST]^2 * errorSignalCCST^2 +
		     2*D[countBackExp,SFLight]*D[countBackExp,SFTTbar]*covSFLightSFTTbar +
		     2*D[countBackExp,SFLight]*D[countBackExp,SFHeavy]*covSFLightSFHeavy +
		     2*D[countBackExp,SFHeavy]*D[countBackExp,SFTTbar]*covSFHeavySFTTbar ) ];

errorBackExpNoCorr= Sqrt[( D[countBackExp,SFLight]^2 * errorSFLight^2 +
			   D[countBackExp,countSignalCCDYL]^2 * errorSignalCCDYL^2 +
			   D[countBackExp,SFTTbar]^2 * errorSFTTbar^2 +
			   D[countBackExp,countSignalCCTTbar]^2 * errorSignalCCTTbar^2 +
			   D[countBackExp,SFHeavy]^2 * errorSFHeavy^2 +
			   D[countBackExp,countSignalCCDYB]^2 * errorSignalCCDYB^2 +
			   D[countBackExp,countSignalCCVV]^2 * errorSignalCCVV^2 +
			   D[countBackExp,countSignalCCST]^2 * errorSignalCCST^2 ) ];


m = { { countLightCCDYL   , countLightCCTTbar   , countLightCCDYB   },
      { countTTbarCCDYL   , countTTbarCCTTbar   , countTTbarCCDYB   },
      { countHeavyCCDYL   , countHeavyCCTTbar   , countHeavyCCDYB   } };

r = {  countLightCCRest ,
       countTTbarCCRest ,
       countHeavyCCRest  };

SFLight = LinearSolve[m, r][[1]];
SFTTbar = LinearSolve[m, r][[2]];
SFHeavy = LinearSolve[m, r][[3]];

A={{  D[SFLight, countLightCCDYL]   ,
       D[SFLight, countLightCCTTbar] ,
       D[SFLight, countLightCCDYB]   ,
       D[SFLight, countTTbarCCDYL]   ,
       D[SFLight, countTTbarCCTTbar] ,
       D[SFLight, countTTbarCCDYB]   ,
       D[SFLight, countHeavyCCDYL]   ,
       D[SFLight, countHeavyCCTTbar] ,
       D[SFLight, countHeavyCCDYB]   ,
       D[SFLight, countLightCCRest]  ,
       D[SFLight, countTTbarCCRest]  ,
       D[SFLight, countHeavyCCRest]  } ,
    {  D[SFTTbar, countLightCCDYL]   ,
       D[SFTTbar, countLightCCTTbar] ,
       D[SFTTbar, countLightCCDYB]   ,
       D[SFTTbar, countTTbarCCDYL]   ,
       D[SFTTbar, countTTbarCCTTbar] ,
       D[SFTTbar, countTTbarCCDYB]   ,
       D[SFTTbar, countHeavyCCDYL]   ,
       D[SFTTbar, countHeavyCCTTbar] ,
       D[SFTTbar, countHeavyCCDYB]   ,
       D[SFTTbar, countLightCCRest]  ,
       D[SFTTbar, countTTbarCCRest]  ,
       D[SFTTbar, countHeavyCCRest]  } ,
    {  D[SFHeavy, countLightCCDYL]   ,
       D[SFHeavy, countLightCCTTbar] ,
       D[SFHeavy, countLightCCDYB]   ,
       D[SFHeavy, countTTbarCCDYL]   ,
       D[SFHeavy, countTTbarCCTTbar] ,
       D[SFHeavy, countTTbarCCDYB]   ,
       D[SFHeavy, countHeavyCCDYL]   ,
       D[SFHeavy, countHeavyCCTTbar] ,
       D[SFHeavy, countHeavyCCDYB]   ,
       D[SFHeavy, countLightCCRest]  ,
       D[SFHeavy, countTTbarCCRest]  ,
       D[SFHeavy, countHeavyCCRest]  }}
Vx=DiagonalMatrix[ { errorLightCCDYL^2   ,
                     errorLightCCTTbar^2 ,
                     errorLightCCDYB^2   ,
                     errorTTbarCCDYL^2   ,
                     errorTTbarCCTTbar^2 ,
                     errorTTbarCCDYB^2   ,
                     errorHeavyCCDYL^2   ,
                     errorHeavyCCTTbar^2 ,
                     errorHeavyCCDYB^2   ,
                     errorLightCCRest^2  ,
                     errorTTbarCCRest^2  ,
                     errorHeavyCCRest^2  } ]

Vy=A.Vx.Transpose[A]

covSFLightSFTTbar = Vy[[2,1]]
covSFLightSFHeavy = Vy[[3,1]]
covSFHeavySFTTbar = Vy[[2,3]]

errorSFLight = Sqrt[Vy[[1,1]]]
errorSFTTbar = Sqrt[Vy[[2,2]]]
errorSFHeavy = Sqrt[Vy[[3,3]]]


countLightCCDYL = 3433.12
countTTbarCCDYL = 0.795455
countHeavyCCDYL = 17.2483
countLightCCTTbar  = 4.71095
countTTbarCCTTbar  = 171.167
countHeavyCCTTbar  = 14.3554
countLightCCDYB  = 207.448
countTTbarCCDYB  = 6.26514
countHeavyCCDYB  = 125.035
countLightCCRest  = 3804.04
countTTbarCCRest  = 187.843
countHeavyCCRest  = 170.494

errorLightCCDYL = 22.7827
errorTTbarCCDYL = 0.561444
errorHeavyCCDYL = 2.22851
errorLightCCTTbar  = 0.807921
errorTTbarCCTTbar  = 5.16322
errorHeavyCCTTbar  = 1.48064
errorLightCCDYB  = 5.56675
errorTTbarCCDYB  = 1.06172
errorHeavyCCDYB  = 5.75329
errorLightCCRest  = 63.9936
errorTTbarCCRest  = 14.045
errorHeavyCCRest  = 13.2863

  (* For signal region *)
countSignalCCDYL = 0
countSignalCCTTbar  = 0.01
countSignalCCDYB  = 1.5
countSignalCCST  = 0.03
countSignalCCVV  = 0.27
errorSignalCCDYL = 0
errorSignalCCTTbar  = 0.06
errorSignalCCDYB  = 0.56
errorSignalCCST  = 0.1
errorSignalCCVV  = 0.05
 
  Print[TraditionalForm["SFLight = "],SFLight,TraditionalForm[" +- "], errorSFLight]
  Print[TraditionalForm["SFTTbar = "],SFTTbar,TraditionalForm[" +- "], errorSFTTbar]
  Print[TraditionalForm["SFHeavy = "],SFHeavy,TraditionalForm[" +- "], errorSFHeavy]

  Print[TraditionalForm["Cov(SFLight,SFTTbar)"],Vy[[2,1]]]
  Print[TraditionalForm["Cov(SFLight,SFHeavy)"],Vy[[3,1]]]
  Print[TraditionalForm["Cov(SFTTbar,SFHeavy)"],Vy[[2,3]]]

  Print[TraditionalForm["ZLight = "], countExpDYL ,TraditionalForm[" +- "], errorExpDYL ]
  Print[TraditionalForm["TTbar = "], countExpTTbar ,TraditionalForm[" +- "], errorExpTTbar ]
  Print[TraditionalForm["ZHeavy = "], countExpDYB ,TraditionalForm[" +- "], errorExpDYB ]
  Print[TraditionalForm["ST = "], countSignalCCST ,TraditionalForm[" +- "], errorSignalCCST ]
  Print[TraditionalForm["VV = "], countSignalCCVV ,TraditionalForm[" +- "], errorSignalCCVV ]
  Print[TraditionalForm["MCtotal = "],countBackExp,TraditionalForm[" +- "], errorBackExp]

  Print[TraditionalForm["MCtotal without correlation = "],countBackExp,TraditionalForm[" +- "], errorBackExpNoCorr]

