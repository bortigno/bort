#dataset you want to launch
datasetname=DoubleEleIVF
cd ../python
rm -f *.pyc
for file in ${datasetname}_cfi*
  do
  namefile=`echo $file | awk -F. '{ print $1 }'`
  sed -e s#CFIFILE#$namefile#g ../bin/ntuple.py > ../bin/ntuple$file
  cd ../bin
  qsub -q all.q -N ${datasetname} Ntupler_launcher.sh ntuple$file
  cd ../python
done