/*
SOLEDAD RUIZ GÓMEZ
ejer2.c
Práctica 3 actividad 3.1 ejerecicio 3
gcc -g ejer2.c -o ejer2

WARNING: EL ORDENADOR SE PILLA SI LO EJECUTAS

*/

#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

	// WARNING: EL ORDENADOR SE PILLA SI LO EJECUTAS

	const int NPROCS = 20;
	pid_t childpid;
	
	for (int i=0; i<NPROCS; i++) {
	
		if ((childpid = fork()) == -1) {
		
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
			
		} else if (childpid == 0) {
		
			printf("Soy el proceso hijo y mi pid es %d y el de mi padre es %d\n", getpid(), getppid());
		
		} else if (childpid) {
		
			printf("Soy el proceso padre y mi pid es %d y el de mi hijo es %d\n", getpid(), childpid);
		
		}
		
	// WARNING: EL ORDENADOR SE PILLA SI LO EJECUTAS	
	}

	exit(EXIT_SUCCESS);

}
