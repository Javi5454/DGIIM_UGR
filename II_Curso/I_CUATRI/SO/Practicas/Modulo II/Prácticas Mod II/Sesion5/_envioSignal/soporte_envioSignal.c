/*
 envio_reciboSignal.c
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

	printf("\nSoy el proceso %d\n\n", getpid());
	
	for (int i =0; i < 60; i++) {
		
		printf ("%d\n", i);
		sleep(1);
	}
	
	return 0;
	
}
