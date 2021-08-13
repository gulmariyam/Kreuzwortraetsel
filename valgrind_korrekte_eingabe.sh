#!/usr/bin/env bash

# Für mehr Informationen zu valgrind:
# https://valgrind.org/docs/manual/mc-manual.html

program="./words"

echo -e "\n###\n### Teil 1: Korrekte Aufrufe \n###\n"

mkdir -p valgrind

outputfile="valgrind/temporary_output.txt"

if sha256sum -c pruefsummen.txt ; then
    echo -e "\tOK: Testdateien wurden nicht modifiziert."
else
    echo -e "\tWARNUNG: Der Inhalt von Testdateien scheint modifiziert worden zu sein oder das Programm sha256sum ist nicht installiert.\n"
fi

for size in 0 5 10 20 50
do
    inputfile="eingabe/$size.txt"
    logfile="valgrind/$size.txt"
    echo -e "Prüfe $inputfile"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$logfile $program $inputfile $outputfile
    result=$?
    if [ $result -eq 0 ]; then
        echo -e "\tOK: Rückgabewert ist 0."
    else
        echo -e "\tFEHLER: Rückgabewert ist nicht 0, sondern $result."
        exit 5
    fi

    . ./valgrind_log_pruefen.sh $logfile

    rm $outputfile
done
