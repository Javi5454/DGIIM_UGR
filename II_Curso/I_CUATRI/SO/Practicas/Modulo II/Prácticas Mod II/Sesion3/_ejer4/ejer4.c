/*
SOLEDAD RUIZ GÓMEZ
ejer2.c
Práctica 3 actividad 3.1 ejercicio 5
gcc -g ejer4.c -o ejer4
*/

#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	const int NPROCS = 5;
	pid_t childpid;
	pid_t childpids [NPROCS];
	int status;
	
	for (int i=0; i<NPROCS; i++) {
	
		if ((childpid = fork()) == -1) {
		
			printf("\nError %d al crear el proceso hijo",errno);
			perror("\nError al crear el proceso hijo \n");
			exit(-1);
			
		} else if (childpid == 0) {	printf("Soy el hijo %d\n", getpid());	childpids[i] = getpid();	}
	}

		
	for (int i=0; i<NPROCS; i+=2) {	//esperamos a los pares
	
		waitpid (childpids[i], &status, 0);
		printf("Acaba de finalizar mi hijo con PID %d\n", childpids[i]);
		printf("Sólo me quedan %d hijos vivos\n", NPROCS-i);
	}	
	
	for (int i=1; i<NPROCS; i+=2) {	//esperamos a los impares
	
		waitpid (childpids[i], &status, 0);
		printf("Acaba de finalizar mi hijo con PID %d\n", childpids[i]);
		printf("Sólo me quedan %d hijos vivos\n", NPROCS-i);
	}	

	exit(EXIT_SUCCESS);

}
