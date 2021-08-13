#!/usr/bin/env bash

mkdir -p valgrind

program="./words"

inputfile="eingabe/10.txt"
outputfile="valgrind/temporary_output.txt"
invalidreadfile="Diese_Datei_sollte_nicht_existieren.txt"
invalidwritefile="Diese_Datei_sollte_nicht_schreibar_sein.txt"
tmpfile="valgrind/tmp.txt"


echo -e "\n###\n### Teil 2: Inkorrekte Aufrufe \n###\n"


echo -e "Prüfe Behandlung von fehlender Eingabedatei"

logfile="valgrind/noinput.txt"
2>&1 valgrind --log-file=$logfile $program "$invalidreadfile" "$tmpfile" 2>/dev/null
. ./valgrind_log_pruefen.sh $logfile
$program "$invalidreadfile" "$tmpfile" 2>/dev/null
result=$?
if [ $result -eq 2 ]; then
    echo -e "\tOK: Rückgabewert ist 2.\n"
else
    echo -e "\tFEHLER: Rückgabewert ist nicht 2, sondern $result.\n"
    exit 2
fi


echo -e "Prüfe Behandlung von nicht-schreibbarer Ausgabedatei"

logfile="valgrind/cantwriteoutput.txt"
touch "$invalidwritefile"
chmod -w "$invalidwritefile"
2>&1 valgrind --log-file=$logfile $program "$inputfile" "$invalidwritefile" 2>/dev/null
. ./valgrind_log_pruefen.sh $logfile
$program "$inputfile" "$invalidwritefile" 2>/dev/null
result=$?
if [ $result -eq 2 ]; then
    echo -e "\tOK: Rückgabewert ist 2.\n"
else
    echo -e "\tFEHLER: Rückgabewert ist nicht 2, sondern $result.\n"
    exit 2
fi
rm -f "$invalidwritefile"


echo -e "Prüfe falsche Anzahl an Parametern #0"

logfile="valgrind/cantwriteoutput.txt"
2>&1 valgrind --log-file=$logfile $program 2>/dev/null
. ./valgrind_log_pruefen.sh $logfile
$program 2>/dev/null
result=$?
if [ $result -eq 1 ]; then
    echo -e "\tOK: Rückgabewert ist 1.\n"
else
    echo -e "\tFEHLER: Rückgabewert ist nicht 1, sondern $result.\n"
    exit 1
fi


echo -e "Prüfe falsche Anzahl an Parametern #1"

logfile="valgrind/cantwriteoutput.txt"
2>&1 valgrind --log-file=$logfile $program 2>/dev/null
. ./valgrind_log_pruefen.sh $logfile
$program 2>/dev/null
result=$?
if [ $result -eq 1 ]; then
    echo -e "\tOK: Rückgabewert ist 1.\n"
else
    echo -e "\tFEHLER: Rückgabewert ist nicht 1, sondern $result.\n"
    exit 1
fi


echo -e "Prüfe falsche Anzahl an Parametern #2"

logfile="valgrind/cantwriteoutput.txt"
2>&1 valgrind --log-file=$logfile $program "$invalidreadfile" 2>/dev/null
. ./valgrind_log_pruefen.sh $logfile
$program "$invalidreadfile" 2>/dev/null
result=$?
if [ $result -eq 1 ]; then
    echo -e "\tOK: Rückgabewert ist 1.\n"
else
    echo -e "\tFEHLER: Rückgabewert ist nicht 1, sondern $result.\n"
    exit 1
fi


echo -e "Prüfe falsche Anzahl an Parametern #3"

logfile="valgrind/cantwriteoutput.txt"
2>&1 valgrind --log-file=$logfile $program "$invalidreadfile" "$invalidreadfile" "$invalidreadfile" 2>/dev/null
. ./valgrind_log_pruefen.sh $logfile
$program "$invalidreadfile" "$invalidreadfile" "$invalidreadfile" 2>/dev/null
result=$?
if [ $result -eq 1 ]; then
    echo -e "\tOK: Rückgabewert ist 1.\n"
else
    echo -e "\tFEHLER: Rückgabewert ist nicht 1, sondern $result.\n"
    exit 1
fi


for i in 0 1 2 3 4 5 6 7 8 9
do
    echo -e "Prüfe Format Eingabedatei #$i"

    logfile="valgrind/invalidformat$i.txt"
    2>&1 valgrind --log-file=$logfile $program "eingabe/invalidformat$i.txt" "$tmpfile" 2>/dev/null
    . ./valgrind_log_pruefen.sh $logfile
    $program "eingabe/invalidformat$i.txt" "$tmpfile" 2>/dev/null
    result=$?
    if [ $result -eq 3 ]; then
        echo -e "\tOK: Rückgabewert ist 3.\n"
    else
        echo -e "\tFEHLER: Rückgabewert ist nicht 3, sondern $result.\n"
        exit 3
    fi
done

