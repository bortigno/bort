#!/bin/sh
while read line; do
NAME=`echo $line | perl -pe 's/.root//' | sed -e s#Test#\\/histos\\/Test#g`
echo $NAME
./make_histos_step2 $line $NAME mcSpli >& $NAME.log &
done < oct9Ntuple.fileList

while read line; do
NAME=`echo $line | perl -pe 's/.root//' | sed -e s#Test#\\/histos\\/Test#g`
echo $NAME
./make_histos_step2 $line $NAME dt >& $NAME.log &
done < oct7NtupleData.fileList
