#!/bin/sh
echo "Do you want to prepare the plots mc?"
read MC
if [ "$MC" == "yes" ]
then
    echo "with which fileList?"
    read MCFILELIST
fi
echo "Do you want to prepare the plots for data?"
read DATA
if [ "$DATA" == "yes" ]
then
    echo "with which fileList?"
    read DATAFILELIST
fi

if [ $MCFILELIST ]
then
    while read line; do
	NAME=`echo $line | sed 's/.root//' | sed -e s#Test#\\/histos\\/Test#g`
	echo $NAME
	./make_histos_step2 $line $NAME mcSpli >& $NAME.log &
    done < $MCFILELIST
fi

if [ $DATAFILELIST ]
then
    while read line; do
	NAME=`echo $line | sed 's/.root//' | sed -e s#Test#\\/histos\\/Test#g`
	echo $NAME
	./make_histos_step2 $line $NAME dt >& $NAME.log &
    done < $DATAFILELIST
fi