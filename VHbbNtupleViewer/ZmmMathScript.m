countBackExp=SFLight*countSignal115DYL + SFTTbar*countSignal115TTbar + SFHeavy*countSignal115DYB + countSignal115VV + countSignal115ST

errorBackExp= ( D[countBackExp,SFLight]^2 * errorSFLight^2 +
                D[countBackExp,countSignal115DYL]^2 * errorSignal115DYL^2 +

						    D[countBackExp,SFTTbar]^2 * errorSFTTbar^2 +
                D[countBackExp,countSignal115TTbar]^2 * errorSignal115TTbar^2 +

                D[countBackExp,SFHeavy]^2 * errorSFHeavy^2 +
                D[countBackExp,countSignal115DYB]^2 * errorSignal115DYB^2 +

                D[countBackExp,countSignal115VV]^2 * errorSignal115VV^2 +
                D[countBackExp,countSignal115ST]^2 * errorSignal115ST^2 +

                2*D[countBackExp,SFLight]*D[countBackExp,SFTTbar]*covSFLightSFTTbar +
                2*D[countBackExp,SFLight]*D[countBackExp,SFHeavy]*covSFLightSFHeavy +
                2*D[countBackExp,SFHeavy]*D[countBackExp,SFTTbar]*covSFHeavySFTTbar )

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


(*updated 3.5*)
countLightCCDYL = 4320.93
countTTbarCCDYL = 0.48
countHeavyCCDYL = 17.94
countLightCCTTbar  = 1.84
countTTbarCCTTbar  = 189.73
countHeavyCCTTbar  = 19.02
countLightCCDYB  = 246.59
countTTbarCCDYB  = 4.92
countHeavyCCDYB  = 162.61
countLightCCRest  = 4323 - ( 0.87 + 38.87 + 23.59 + 0.44 )
countTTbarCCRest  = 231 - ( 7.41 + 0.33 )
countHeavyCCRest  =  190 - ( 0.58 + 0.04 + 0.09 + 4.99 )
  (*Errors*)
errorLightCCDYL = 25.35
errorTTbarCCDYL = 0.36
errorHeavyCCDYL = 2.22
errorLightCCTTbar  = 0.54
errorTTbarCCTTbar  = 5.43
errorHeavyCCTTbar  = 1.72
errorLightCCDYB  = 6.06
errorTTbarCCDYB  = 0.95
errorHeavyCCDYB  = 6.60
errorLightCCRest  = Sqrt[ (Sqrt[4323])^2 + 0.17^2 + 0.75^2 + 0.34^2 + 0.12^2 ]
errorTTbarCCRest  = Sqrt[ (Sqrt[231])^2 + 0.5^2 + 0.04^2 ]
errorHeavyCCRest  = Sqrt[ (Sqrt[190])^2 + 1.72^2 + 0.04^2 + 0.04^2 + 0.15^2 ]

 
  Print[TraditionalForm["SFLight = "],SFLight,TraditionalForm[" +- "], errorSFLight]
  Print[TraditionalForm["SFTTbar = "],SFTTbar,TraditionalForm[" +- "], errorSFTTbar]
  Print[TraditionalForm["SFHeavy = "],SFHeavy,TraditionalForm[" +- "], errorSFHeavy]

  Print[TraditionalForm["Cov(SFLight,SFTTbar)"],Vy[[2,1]]]
  Print[TraditionalForm["Cov(SFLight,SFHeavy)"],Vy[[3,1]]]
  Print[TraditionalForm["Cov(SFTTbar,SFHeavy)"],Vy[[2,3]]]
