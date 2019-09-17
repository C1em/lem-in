#!/bin/bash

for f in lem-in_tools/maps/invalid/*
do
	echo "current file : $f"
	ERROR=$(valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file="output.txt" ./lem-in < $f | tail -n 1)
	RES=$(pcregrep -M -v " malloc .*\n.*NX" output.txt | grep -E " (malloc|free) " | wc -l)
	if [ $RES -gt 2 ]
	then
		echo "RES : $RES"
	fi
	if [ $ERROR != "ERROR" ]
	then	
		echo "last line : $ERROR"
	fi
done
