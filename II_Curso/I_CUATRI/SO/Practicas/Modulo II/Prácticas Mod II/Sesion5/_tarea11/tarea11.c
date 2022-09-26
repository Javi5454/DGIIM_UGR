// tarea11.c

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h> 

int main() {

   	printf("\nSoy el proceso %d\n\n", getpid());

	sigset_t new_mask;

	/* inicializar la nueva mascara de se�ales */
	sigemptyset(&new_mask);

	sigaddset(&new_mask, SIGUSR1);

	/*esperar a cualquier se�al excepto SIGUSR1 */
	sigsuspend(&new_mask);
     
}
