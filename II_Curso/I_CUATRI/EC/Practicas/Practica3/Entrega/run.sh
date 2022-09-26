#!/bin/bash

#=== TESTS === ____________________________________
for i in 0 g 1 2; do
		printf "\n\n\n__OPTIM%1c__%48s\n" $i "" | tr " " "="
	for j in $(seq 1 4); do
		printf "\n__TEST%02d__%48s\n" $j "" | tr " " "-"
		rm ejer_4_1
		gcc ejer_4_1.c -o ejer_4_1 -O$i -D TEST=$j -g
		./ejer_4_1
	done
done
#=== CRONOS === ____________________________________
for i in 0 g 1 2; do
		printf "\n__OPTIM%1c__%48s\n" $i "" | tr " " "="
		rm ejer_4_1
		gcc ejer_4_1.c -o ejer_4_1 -O$i -D TEST=0
	for j in $(seq 0 10); do
		echo $j; ./ejer_4_1
	done | pr -11 -l 22 -w 80
done
#___________________________________________________
