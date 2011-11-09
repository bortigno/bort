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


countLightCCDYL = 1937.12
countTTbarCCDYL = 0.785351
countHeavyCCDYL = 13.6845
countLightCCTTbar  = 1.94897
countTTbarCCTTbar  = 161.51
countHeavyCCTTbar  = 11.4636
countLightCCDYB  = 113.185
countTTbarCCDYB  = 4.29065
countHeavyCCDYB  = 95.7915
countLightCCRest  = 2073.8
countTTbarCCRest  = 172.912
countHeavyCCRest  = 147.344
countSignal115DYL  = 2.0452
countSignal115TTbar  = 4.79828
countSignal115DYB  = 22.6904
countSignal115VV  = 0.916096
countSignal115ST  = 0.192396
(*Errors*)
errorLightCCDYL = 13.5487
errorTTbarCCDYL = 0.454865
errorHeavyCCDYL = 1.576
errorLightCCTTbar  = 0.447124
errorTTbarCCTTbar  = 3.90231
errorHeavyCCTTbar  = 0.982999
errorLightCCDYB  = 3.34908
errorTTbarCCDYB  = 0.641678
errorHeavyCCDYB  = 3.932
errorLightCCRest  = 45.8388
errorTTbarCCRest  = 13.5165
errorHeavyCCRest  = 12.289
errorSignal115DYL  = 0.567236
errorSignal115TTbar  = 0.685469
errorSignal115DYB  = 1.89747
errorSignal115VV  = 0.279913
errorSignal115ST  = 0.0896013

(*without MC uncert*)
errorLightCCDYL = 0
errorTTbarCCDYL = 0
errorHeavyCCDYL = 0
errorLightCCTTbar  = 0
errorTTbarCCTTbar  = 0
errorHeavyCCTTbar  = 0
errorLightCCDYB  = 0
errorTTbarCCDYB  = 0
errorHeavyCCDYB  = 0
errorLightCCRest  = Sqrt[2101]
errorTTbarCCRest  = Sqrt[180]
errorHeavyCCRest  = Sqrt[151]
errorSignal115DYL  = 0
errorSignal115TTbar  = 0
errorSignal115DYB  = 0
errorSignal115VV  = 0
errorSignal115ST  = 0

  Print[TraditionalForm["SFLight = "],SFLight,TraditionalForm[" +- "], errorSFLight]
  Print[TraditionalForm["SFTTbar = "],SFTTbar,TraditionalForm[" +- "], errorSFTTbar]
  Print[TraditionalForm["SFHeavy = "],SFHeavy,TraditionalForm[" +- "], errorSFHeavy]

  Print[TraditionalForm["Cov(SFLight,SFTTbar)"],Vy[[2,1]]]
  Print[TraditionalForm["Cov(SFLight,SFHeavy)"],Vy[[3,1]]]
  Print[TraditionalForm["Cov(SFTTbar,SFHeavy)"],Vy[[2,3]]]
