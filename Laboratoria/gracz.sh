#!/bin/bash

if [[ $# -ne 1 ]]; then
        echo "ERROR: niepoprawna liczba argumentów"
        exit 1
fi

moves[0]="kamień"
moves[1]="papier"
moves[2]="nożyce"

file_name="los"$1".txt"

while true; do
	if test -f "komenda.txt"; then
		comm=$(cat komenda.txt)
		case $comm in
			"start")
				if ! test -f $file_name; then
					index=$(($RANDOM % 3))
					echo ${moves[$index]} > $file_name
				fi ;;
			"stop")
				exit 0 ;;
			*) echo 1 >> /dev/null ;;
		esac			
		
	fi
	sleep 0.1
done
