#!/bin/bash

n=$#

if [[ n -ne 2 ]]; then
	echo "ERROR: niepoprawna liczba argumentów"
	exit 1
fi

if test -f gra.log; then
	echo "" > gra.log
fi

# uruchamianie graczy
for (( j=1; j<=$1; j++ )); do
	(./gracz.sh $j &> /dev/null) &
done	

games=0

for (( i=0; i<$2; i++ )); do
    echo start > komenda.txt
	
	index=1
	while true; do
		name="los"$index".txt"
		if test -f $name; then
			if [[ $index -eq $1 ]]; then
				break
			else
				index=$((index+1))
			fi
		fi
	done
	
	sleep 0.1
	rm komenda.txt
	

	for (( k=1; k<=$1; k++ )); do
		n1="los"$k".txt"
		l1=$(cat $n1)
		for (( l=k+1; l<=$1; l++ )); do
			n2="los"$l".txt"
			l2=$(cat $n2)
			
			result1=""
			result2=""

			case $l1 in
				"papier")
					case $l2 in
						"papier") 
							result1="remis "$l"_" 
							result2="remis "$k"_" ;;
						"kamień") 
							result1="wygrał "$k"_"
							result2="przegrał "$l"_" ;;
						"nożyce")
							result1="wygrał "$l"_"
							result2="przegrał "$k"_" ;;
						*) echo "ERROR: niepoprawny los" ;;
					esac ;;
				"kamień")
					case $l2 in
						"papier")
							result1="wygrał "$l"_"
							result2="przegrał "$k"_" ;;
						"kamień")
							result1="remis "$l"_" 
							result2="remis "$k"_" ;;
						"nożyce")
							result1="wygrał "$k"_"
							result2="przegrał "$l"_" ;;
						*) echo "ERROR: niepoprawny los" ;;
					esac ;;
				"nożyce")
					case $l2 in
						"papier")
							result1="wygrał "$k"_"
							result2="przegrał "$l"_" ;;
						"kamień")
							result1="wygrał "$l"_"
							result2="przegrał "$k"_" ;;
						"nożyce")
							result1="remis "$l"_" 
							result2="remis "$k"_" ;;
						*) echo "ERROR: niepoprawny los" ;;
					esac ;;
				*) echo "ERROR: niepoprawny los" ;;
			esac

			games=$((games+1))
			echo $result1 >> gra.log
			echo $result2 >> gra.log
		done
	done

	rm los*

done

for (( n=1; n<=$1; n++ )); do
	echo -ne "Gracz "$n" wygrał" $(cat gra.log | grep "wygrał "$n"_" | wc -l) "razy\n"
	echo -ne "Gracz "$n" zremisował" $(cat gra.log | grep "remis "$n"_" | wc -l) "razy\n"
	echo -ne "Gracz "$n" przegrał" $(cat gra.log | grep "przegrał "$n"_" | wc -l) "razy\n"
	echo ""
done

echo "Liczba gier: "$games

echo stop > komenda.txt
sleep 1
rm komenda.txt

