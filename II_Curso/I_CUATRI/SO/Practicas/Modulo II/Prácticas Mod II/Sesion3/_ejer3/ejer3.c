/*
SOLEDAD RUIZ GÓMEZ
ejer2.c
Práctica 3 actividad 3.1 ejercicio 4
gcc -g ejer3.c -o ejer3
./ejer3
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
			
		} else if (childpid == 0) {	printf("Soy el hijo %d\n", getpid());	childpids[i] = getpid();	} // avisamos del hijo y lo añadimos al vector
	}

		
	for (int i=0; i<NPROCS; i++) {
	
		waitpid (childpids[i], &status, 0);	// esperamos a todos los hijos y guardamos en status el estado en el que está cada hijo
		printf("Acaba de finalizar mi hijo con PID %d\n", childpids[i]);
		printf("Sólo me quedan %d hijos vivos\n", NPROCS-i);
	}		

	exit(EXIT_SUCCESS);

}


/* 

VARIANTE DE PEDRO. FUNCIONA MEJOR

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char *argv[]) {
    int nprocs = 5;
    int childpid;

    for (int i  = 0 ; i < nprocs ; i++) {
        if ((childpid = fork()) < 0) {
            printf("Error en el fork, %d", errno);
            perror("Error en el fork");
            exit(-1);
        }

        if (childpid == 0) {
            printf("Soy el hijo %d\n", getpid());
            break;
        }
    }

    for (int i = 0 ; i < nprocs && childpid != 0 ; i++) {
        int pid = wait();
        nprocs--;
        printf("Acaba de finalizar mi hijo con PID: %d\n", pid);
        printf("Solo me quedan %d hijos vivos", nprocs);
    }

    return 0;
}

*/
