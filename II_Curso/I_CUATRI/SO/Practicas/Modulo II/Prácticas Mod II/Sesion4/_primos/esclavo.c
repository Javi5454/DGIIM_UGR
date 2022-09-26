/*
SOLEDAD RUIZ G�MEZ
esclavo.c
Pr�ctica 3 actividad 4.2 ejercicio 5
gcc -g esclavo.c -o esclavo -lm
nota: incluimos -lm para poder usar la biblioteca math.h
*/

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>	// para poder usar sqrt()

int primo (int num) { //en C no podemos usar bool, pero esta funci�n trabaja como una booleana

	int output = 1;
	int tope   = sqrt(num);
	
	for (int i=2; i<=tope && output; i++) 
		if (num%i == 0) output = 0;

	return output;
}


int main(int argc, char *argv[]) { // PROGRAMA PRINCIPAL - ESCLAVO
	
	// Leemos el intervalo que se nos pasa por argumentos
	if (argc<2) { 
		printf("Error en la llamada a esclavo. No se ha detectado ning�n intervalo num�rico.\n"); 
		exit(-1); 
	}

	int a = atoi (argv[1]);
	int b = atoi (argv[2]);
	
	// Calculamos si los n�meros comprendidos en el intervalo son primos o no
	for (int i=a; i<=b; i++) 
		if (primo(i))	
			write (STDOUT_FILENO, &i, sizeof(int)); 
		// si es primo, lo metemos en el cauce de salida est�ndar (como es un proceso hijo que llamamos desde maestro, hereda los descriptores
		// de salida y entrada, por lo que se hace referencia al mismo cauce)

	return EXIT_SUCCESS;
	
}



