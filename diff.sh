#!/usr/bin/env bash

mkdir -p diff

echo -e "\nPrüfe Ausgabe.\n"

for size in 0 5 10 20 50
do
    testfile="ausgabe/$size.txt"
    logfile="diff/$size.txt"
    outputfile="erwartete_ausgabe/$size.txt"
    echo -e "Prüfe $testfile $outputfile"
    if diff $testfile $outputfile > $logfile ; then
        echo -e "\tOK: Ausgabe stimmt mit erwarteter Ausgabe überein.\n"
    else
        echo -e "\tFEHLER: Ausgabe stimmt nicht mit der erwarteten Ausgabe überein. Details in $logfile\n"
        exit 1
    fi
done
