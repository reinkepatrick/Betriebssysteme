#!/bin/bash

DIV=$1
MUL=1
shift

while (( $# )); do
	if [ $1 -ge 0 ]; then 
		MUL=$MUL*$1
	fi
	shift
done
RES=$((MUL/DIV))

echo "Dateiname: " $0 
echo "Ergebnis: " $RES



