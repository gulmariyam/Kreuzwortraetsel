#!/usr/bin/env bash

logfile=$1

if grep -E "definitely lost: [1-9][0-9,]* bytes" $logfile ; then
    echo -e -e "\tFEHLER: Speicherleck gefunden. Details in Datei $logfile."
    exit 4
else
    echo -e "\tOK: Speichertest 1"
fi

if grep -E "indirectly lost: [1-9][0-9,]* bytes" $logfile ; then
    echo -e "\tFEHLER: Speicherleck gefunden. Details in Datei $logfile."
    exit 4
else
    echo -e "\tOK: Speichertest 2"
fi

if grep -E "possibly lost: [1-9][0-9,]* bytes" $logfile ; then
    echo -e "\tFEHLER: Speicherleck gefunden. Details in Datei $logfile."
    exit 4
else
    echo -e "\tOK: Speichertest 3"
fi

if grep -E "still reachable: [1-9][0-9,]* bytes" $logfile ; then
    echo -e "\tFEHLER: Speicherleck gefunden. Details in Datei $logfile."
    exit 4
else
    echo -e "\tOK: Speichertest 4"
fi

if grep -E "in use at exit: [1-9][0-9,]* bytes" $logfile ; then
    echo -e "\tFEHLER: Speicherleck gefunden. Details in Datei $logfile."
    exit 4
else
    echo -e "\tOK: Speichertest 5"
fi

if grep -E "Invalid free" $logfile ; then
    echo -e "\tFEHLER: Invalid free gefunden. Details in Datei $logfile."
    exit 4
else
    echo -e "\tOK: Invalid free test"
fi

if grep -E "Invalid read of size" $logfile ; then
    echo -e "\tFEHLER: Invalid read gefunden. Details in Datei $logfile."
    exit 4
else
    echo -e "\tOK: Invalid read test"
fi

if grep -E "Invalid write of size" $logfile ; then
    echo -e "\tFEHLER: Invalid write gefunden. Details in Datei $logfile."
    exit 4
else
    echo -e "\tOK: Invalid write test"
fi

if grep -E "depends on uninitialised" $logfile ; then
    echo -e "\tFEHLER: Uninitialisierte Variablen verwendet. Details in Datei $logfile."
    exit 4
else
    echo -e "\tOK: Nur initialisierte Variablen verwendet"
fi
