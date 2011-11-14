m = { { countZLightCCDYL , countZLightCCWL , countZLightCCTTbar   , countZLightCCDYB , countZLightCCWB   },
      { countWLightCCDYL , countWLightCCWL , countWLightCCTTbar   , countWLightCCDYB , countWLightCCWB   },
      { countTTbarCCDYL , countTTbarCCWL , countTTbarCCTTbar   , countTTbarCCDYB , countTTbarCCWB   },
      { countZHeavyCCDYL , countZHeavyCCWL , countZHeavyCCTTbar   , countZHeavyCCDYB , countZHeavyCCWB   },
      { countWHeavyCCDYL , countWHeavyCCWL , countWHeavyCCTTbar   , countWHeavyCCDYB , countWHeavyCCWB   } };
  
r = {  countZLightCCRest ,
       countWLightCCRest ,
       countTTbarCCRest ,
       countZHeavyCCRest,
       countWHeavyCCRest  };

SFZLight = LinearSolve[m, r][[1]];
SFWLight = LinearSolve[m, r][[2]];
SFTTbar = LinearSolve[m, r][[3]];
SFZHeavy = LinearSolve[m, r][[4]];
SFWHeavy = LinearSolve[m, r][[5]];


A={{  D[SFZLight, countZLightCCDYL]   ,
      D[SFZLight, countZLightCCWL]   ,
      D[SFZLight, countZLightCCTTbar] ,
      D[SFZLight, countZLightCCDYB]   ,
      D[SFZLight, countZLightCCWB]   ,
      D[SFZLight, countWLightCCDYL]   ,
      D[SFZLight, countWLightCCWL]   ,
      D[SFZLight, countWLightCCTTbar] ,
      D[SFZLight, countWLightCCDYB]   ,
      D[SFZLight, countWLightCCWB]   ,
      D[SFZLight, countTTbarCCDYL]   ,
      D[SFZLight, countTTbarCCWL]   ,
      D[SFZLight, countTTbarCCTTbar] ,
      D[SFZLight, countTTbarCCDYB]   ,
      D[SFZLight, countTTbarCCWB]   ,
      D[SFZLight, countZHeavyCCDYL]   ,
      D[SFZLight, countZHeavyCCWL]   ,
      D[SFZLight, countZHeavyCCTTbar] ,
      D[SFZLight, countZHeavyCCDYB]   ,
      D[SFZLight, countZHeavyCCWB]   ,
      D[SFZLight, countWHeavyCCDYL]   ,
      D[SFZLight, countWHeavyCCWL]   ,
      D[SFZLight, countWHeavyCCTTbar] ,
      D[SFZLight, countWHeavyCCDYB]   ,
      D[SFZLight, countWHeavyCCWB]  } ,
   {  D[SFWLight, countZLightCCDYL]   ,
      D[SFWLight, countZLightCCWL]   ,
      D[SFWLight, countZLightCCTTbar] ,
      D[SFWLight, countZLightCCDYB]   ,
      D[SFWLight, countZLightCCWB]   ,
      D[SFWLight, countWLightCCDYL]   ,
      D[SFWLight, countWLightCCWL]   ,
      D[SFWLight, countWLightCCTTbar] ,
      D[SFWLight, countWLightCCDYB]   ,
      D[SFWLight, countWLightCCWB]   ,
      D[SFWLight, countTTbarCCDYL]   ,
      D[SFWLight, countTTbarCCWL]   ,
      D[SFWLight, countTTbarCCTTbar] ,
      D[SFWLight, countTTbarCCDYB]   ,
      D[SFWLight, countTTbarCCWB]   ,
      D[SFWLight, countZHeavyCCDYL]   ,
      D[SFWLight, countZHeavyCCWL]   ,
      D[SFWLight, countZHeavyCCTTbar] ,
      D[SFWLight, countZHeavyCCDYB]   ,
      D[SFWLight, countZHeavyCCWB]   ,
      D[SFWLight, countWHeavyCCDYL]   ,
      D[SFWLight, countWHeavyCCWL]   ,
      D[SFWLight, countWHeavyCCTTbar] ,
      D[SFWLight, countWHeavyCCDYB]   ,
      D[SFWLight, countWHeavyCCWB]  } ,
   {  D[SFTTbar, countZLightCCDYL]   ,
      D[SFTTbar, countZLightCCWL]   ,
      D[SFTTbar, countZLightCCTTbar] ,
      D[SFTTbar, countZLightCCDYB]   ,
      D[SFTTbar, countZLightCCWB]   ,
      D[SFTTbar, countWLightCCDYL]   ,
      D[SFTTbar, countWLightCCWL]   ,
      D[SFTTbar, countWLightCCTTbar] ,
      D[SFTTbar, countWLightCCDYB]   ,
      D[SFTTbar, countWLightCCWB]   ,
      D[SFTTbar, countTTbarCCDYL]   ,
      D[SFTTbar, countTTbarCCWL]   ,
      D[SFTTbar, countTTbarCCTTbar] ,
      D[SFTTbar, countTTbarCCDYB]   ,
      D[SFTTbar, countTTbarCCWB]   ,
      D[SFTTbar, countZHeavyCCDYL]   ,
      D[SFTTbar, countZHeavyCCWL]   ,
      D[SFTTbar, countZHeavyCCTTbar] ,
      D[SFTTbar, countZHeavyCCDYB]   ,
      D[SFTTbar, countZHeavyCCWB]   ,
      D[SFTTbar, countWHeavyCCDYL]   ,
      D[SFTTbar, countWHeavyCCWL]   ,
      D[SFTTbar, countWHeavyCCTTbar] ,
      D[SFTTbar, countWHeavyCCDYB]   ,
      D[SFTTbar, countWHeavyCCWB]  } ,
   {  D[SFZHeavy, countZLightCCDYL]   ,
      D[SFZHeavy, countZLightCCWL]   ,
      D[SFZHeavy, countZLightCCTTbar] ,
      D[SFZHeavy, countZLightCCDYB]   ,
      D[SFZHeavy, countZLightCCWB]   ,
      D[SFZHeavy, countWLightCCDYL]   ,
      D[SFZHeavy, countWLightCCWL]   ,
      D[SFZHeavy, countWLightCCTTbar] ,
      D[SFZHeavy, countWLightCCDYB]   ,
      D[SFZHeavy, countWLightCCWB]   ,
      D[SFZHeavy, countTTbarCCDYL]   ,
      D[SFZHeavy, countTTbarCCWL]   ,
      D[SFZHeavy, countTTbarCCTTbar] ,
      D[SFZHeavy, countTTbarCCDYB]   ,
      D[SFZHeavy, countTTbarCCWB]   ,
      D[SFZHeavy, countZHeavyCCDYL]   ,
      D[SFZHeavy, countZHeavyCCWL]   ,
      D[SFZHeavy, countZHeavyCCTTbar] ,
      D[SFZHeavy, countZHeavyCCDYB]   ,
      D[SFZHeavy, countZHeavyCCWB]   ,
      D[SFZHeavy, countWHeavyCCDYL]   ,
      D[SFZHeavy, countWHeavyCCWL]   ,
      D[SFZHeavy, countWHeavyCCTTbar] ,
      D[SFZHeavy, countWHeavyCCDYB]   ,
      D[SFZHeavy, countWHeavyCCWB]  } ,
   {  D[SFWHeavy, countZLightCCDYL]   ,
      D[SFWHeavy, countZLightCCWL]   ,
      D[SFWHeavy, countZLightCCTTbar] ,
      D[SFWHeavy, countZLightCCDYB]   ,
      D[SFWHeavy, countZLightCCWB]   ,
      D[SFWHeavy, countWLightCCDYL]   ,
      D[SFWHeavy, countWLightCCWL]   ,
      D[SFWHeavy, countWLightCCTTbar] ,
      D[SFWHeavy, countWLightCCDYB]   ,
      D[SFWHeavy, countWLightCCWB]   ,
      D[SFWHeavy, countTTbarCCDYL]   ,
      D[SFWHeavy, countTTbarCCWL]   ,
      D[SFWHeavy, countTTbarCCTTbar] ,
      D[SFWHeavy, countTTbarCCDYB]   ,
      D[SFWHeavy, countTTbarCCWB]   ,
      D[SFWHeavy, countZHeavyCCDYL]   ,
      D[SFWHeavy, countZHeavyCCWL]   ,
      D[SFWHeavy, countZHeavyCCTTbar] ,
      D[SFWHeavy, countZHeavyCCDYB]   ,
      D[SFWHeavy, countZHeavyCCWB]   ,
      D[SFWHeavy, countWHeavyCCDYL]   ,
      D[SFWHeavy, countWHeavyCCWL]   ,
      D[SFWHeavy, countWHeavyCCTTbar] ,
      D[SFWHeavy, countWHeavyCCDYB]   ,
      D[SFWHeavy, countWHeavyCCWB]  } };


 
Vx=DiagonalMatrix[ { errorZLightCCDYL^2   ,
		     errorZLightCCWL^2   ,
		     errorZLightCCTTbar^2 ,
		     errorZLightCCDYB^2   ,
		     errorZLightCCWB^2   ,
		     errorWLightCCDYL^2   ,
		     errorWLightCCWL^2   ,
		     errorWLightCCTTbar^2 ,
		     errorWLightCCDYB^2   ,
		     errorWLightCCWB^2   ,
		     errorTTbarCCDYL^2   ,
		     errorTTbarCCWL^2   ,
		     errorTTbarCCTTbar^2 ,
		     errorTTbarCCDYB^2   ,
		     errorTTbarCCWB^2   ,
		     errorZHeavyCCDYL^2   ,
		     errorZHeavyCCWL^2   ,
		     errorZHeavyCCTTbar^2 ,
		     errorZHeavyCCDYB^2   ,
		     errorZHeavyCCWB^2   ,
		     errorWHeavyCCDYL^2   ,
		     errorWHeavyCCWL^2   ,
		     errorWHeavyCCTTbar^2 ,
		     errorWHeavyCCDYB^2   ,
		     errorWHeavyCCWB^2    } ];
 
Vy=A.Vx.Transpose[A];
 
covSFZLightSFWLight = Vy[[1,2]];
covSFZLightSFTTbar  = Vy[[1,3]];
covSFZLightSFZHeavy = Vy[[1,4]];
covSFZLightSFWHeavy = Vy[[1,5]];

covSFWLightSFZLight = Vy[[2,1]];
covSFWLightSFTTbar  = Vy[[2,3]];
covSFWLightSFZHeavy = Vy[[2,4]];
covSFWLightSFWHeavy = Vy[[2,5]];

covSFTTbarSFZLight = Vy[[3,1]];
covSFTTbarSFWLight = Vy[[3,2]];
covSFTTbarSFZHeavy = Vy[[3,4]];
covSFTTbarSFWHeavy = Vy[[3,5]];

covSFZHeavySFZLight = Vy[[4,1]];
covSFZHeavySFWLight = Vy[[4,2]];
covSFZHeavySFTTbar  = Vy[[4,3]];
covSFZHeavySFWHeavy = Vy[[4,5]];

covSFWHeavySFZLight = Vy[[5,1]];
covSFWHeavySFWLight = Vy[[5,2]];
covSFWHeavySFTTbar  = Vy[[5,3]];
covSFWHeavySFZHeavy = Vy[[5,4]];

errorSFZLight = Sqrt[Vy[[1,1]]];
errorSFWLight = Sqrt[Vy[[2,2]]];
errorSFTTbar = Sqrt[Vy[[3,3]]];
errorSFZHeavy = Sqrt[Vy[[4,4]]];
errorSFWHeavy = Sqrt[Vy[[5,5]]];



countZLightCCDYL = 1452.23;
countZLightCCDYB = 148.42;
countZLightCCTTbar = 16.35;
countZLightCCWL = 0;
countZLightCCWB = 0;
countZLightCCRest  = 1517.33;
errorZLightCCDYL = 13.54;
errorZLightCCDYB = 1.60;
errorZLightCCTTbar = 1.65;
errorZLightCCWL = 0;
errorZLightCCWB = 0;
errorZLightCCRest = 41.41;
countZHeavyCCDYL = 10.61;
countZHeavyCCDYB = 36.31;
countZHeavyCCTTbar = 5.20;
countZHeavyCCWL = 0;
countZHeavyCCWB = 0;
countZHeavyCCRest  = 91.78;
errorZHeavyCCDYL = 0.33;
errorZHeavyCCDYB = 0.41;
errorZHeavyCCTTbar = 0.93;
errorZHeavyCCWL = 0;
errorZHeavyCCWB = 0;
errorZHeavyCCRest = 10.41;
countWLightCCDYL = 2.11;
countWLightCCDYB = 0.05;
countWLightCCTTbar = 503.16;
countWLightCCWL = 3558.32;
countWLightCCWB = 159.21;
countWLightCCRest  = 3562.63;
errorWLightCCDYL = 0.09;
errorWLightCCDYB = 0.03;
errorWLightCCTTbar = 9.1;
errorWLightCCWL = 0;
errorWLightCCWB = 0;
errorWLightCCRest = 69.41;
countWHeavyCCDYL = 0;
countWHeavyCCDYB = 0;
countWHeavyCCTTbar = 98.12;
countWHeavyCCWL = 26.92;
countWHeavyCCWB = 44.97;
countWHeavyCCRest  = 197.31;
errorWHeavyCCDYL = 0.33;
errorWHeavyCCDYB = 0.41;
errorWHeavyCCTTbar = 0.93;
errorWHeavyCCWL = 0;
errorWHeavyCCWB = 0;
errorWHeavyCCRest = 15.01;
countTTbarCCDYL = 0;
countTTbarCCDYB = 0;
countTTbarCCTTbar = 465.89;
countTTbarCCWL = 17.44;
countTTbarCCWB = 41.38;
countTTbarCCRest  = 471.04;
errorTTbarCCDYL = 0;
errorTTbarCCDYB = 0;
errorTTbarCCTTbar = 8.78;
errorTTbarCCWL = 1.45;
errorTTbarCCWB = 2.12;
errorTTbarCCRest = 23.71;


Print[TraditionalForm["SFZLight = "],SFZLight,TraditionalForm[" +- "], errorSFZLight];
Print[TraditionalForm["SFWLight = "],SFWLight,TraditionalForm[" +- "], errorSFZLight];
Print[TraditionalForm["SFTTbar = "],SFTTbar,TraditionalForm[" +- "], errorSFTTbar];
Print[TraditionalForm["SFZHeavy = "],SFZHeavy,TraditionalForm[" +- "], errorSFZHeavy];
Print[TraditionalForm["SFWHeavy = "],SFWHeavy,TraditionalForm[" +- "], errorSFZHeavy];

Print[TraditionalForm["Cov(SFZLight,SFZHeavy)"],Vy[[1,2]]];
Print[TraditionalForm["Cov(SFZLight,SFTTbar)"],Vy[[1,3]]];
Print[TraditionalForm["Cov(SFZLight,SFWLight)"],Vy[[1,4]]];
Print[TraditionalForm["Cov(SFZLight,SFWHeavy)"],Vy[[1,5]]];
  
Print[TraditionalForm["Cov(SFZHeavy,SFZLight)"],Vy[[2,1]]];
Print[TraditionalForm["Cov(SFZHeavy,SFTTbar)"],Vy[[2,3]]];
Print[TraditionalForm["Cov(SFZHeavy,SFWLight)"],Vy[[2,4]]];
Print[TraditionalForm["Cov(SFZHeavy,SFWHeavy)"],Vy[[2,5]]];

Print[TraditionalForm["Cov(SFTTbar,SFZLight)"],Vy[[3,1]]];
Print[TraditionalForm["Cov(SFTTbar,SFZHeavy)"],Vy[[3,2]]];
Print[TraditionalForm["Cov(SFTTbar,SFWLight)"],Vy[[3,4]]];
Print[TraditionalForm["Cov(SFTTbar,SFWHeavy)"],Vy[[3,5]]];

Print[TraditionalForm["Cov(SFWLight,SFZLight)"],Vy[[4,1]]];
Print[TraditionalForm["Cov(SFWLight,SFZHeavy)"],Vy[[4,2]]];
Print[TraditionalForm["Cov(SFWLight,SFTTbar)"],Vy[[4,3]]];
Print[TraditionalForm["Cov(SFWLight,SFWHeavy)"],Vy[[4,5]]];

Print[TraditionalForm["Cov(SFWHeavy,SFZLight)"],Vy[[5,1]]];
Print[TraditionalForm["Cov(SFWHeavy,SFZHeavy)"],Vy[[5,2]]];
Print[TraditionalForm["Cov(SFWHeavy,SFTTbar)"],Vy[[5,3]]];
Print[TraditionalForm["Cov(SFWHeavy,SFWLight)"],Vy[[5,4]]];
