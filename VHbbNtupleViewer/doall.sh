#!/bin/sh
while read line; do
NAME=`echo $line | perl -pe 's/.root//' | sed -e s#Test#\\/histos\\/Test##`
echo $NAME
./make_histos_step2 $line $NAME mcSpli >& $NAME.log &
done < oct5Ntuple.fileList
