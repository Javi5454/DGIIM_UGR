/*
 soporte_reciboSignal.c
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h> 
//Incluye <bits/posix1_lim.h> POSIX Standard: 2.9.2 //Minimum    //Values Added to <limits.h> y <bits/posix2_lim.h>


int main(int argc, char *argv[]) {

	long int pid;
	int signal;
	
	if(argc<2) {
		printf("\nSintaxis de ejecucion: reciboSignal <PID> [12]\n\n");
		exit(EXIT_FAILURE);
	}
	
	pid = strtol(argv[1],NULL,10);
	
	if(pid == LONG_MIN || pid == LONG_MAX) {
		if(pid == LONG_MIN)
			printf("\nError por desbordamiento inferior LONG_MIN %ld",pid);
		else
			printf("\nError por desbordamiento superior LONG_MAX %ld",pid);
		perror("\nError en strtol");
		exit(EXIT_FAILURE);
	}
	
	signal=atoi(argv[2]);
	
	if (signal == 1)	
		kill (pid, SIGUSR1);
	else if (signal == 2)
		kill (pid, SIGUSR2);
		
	return 0;
	
}
