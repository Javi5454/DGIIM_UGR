/*
SOLEDAD RUIZ GÓMEZ
ejer1.c
Práctica 3 actividad 3.1 ejercicio 1
gcc -g ejer1.c -o ejer1
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include<errno.h>
//#include <cmath.h>

int main (int argc, char *argv[]) {

	int cifra = atoi (argv[1]);	// leemos la cifra que nos han pasado
	
	// Crear el proceso hijo
	pid_t pid = fork();
	if (pid == -1) {
	
		// Error al crear el proceso hijo
		printf("\nError %d al crear el proceso hijo",errno);
		perror("\nError al crear el proceso hijo \n");
		
	} else if (pid == 0) {
	
		// PROCESO HIJO
		printf("\nSoy el proceso hijo y mi pid es %d y el de mi padre es %d, y voy a comprobar si el numero es par o impar\n", getpid(), getppid());
		
		// Ver si es par
		if (cifra % 2 == 0) 
			printf ("-> %d es par\n\n", cifra);
		else
			printf ("-> %d es impar\n\n", cifra);
	} else {

		// PROCESO PADRE
		printf("\nSoy el proceso padre y mi pid es %d y el de mi hijo es %d, y voy a comprobar si el numero es divisible por 4 \n", getpid(), pid);
		
		// Ver si es múltiplo de 4
		if (cifra % 4 == 0)
			printf ("-> %d es divisible por 4\n", cifra);
		else
			printf ("-> %d no es divisible por 4\n", cifra);
	}

	return 0;
}
