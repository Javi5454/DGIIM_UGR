#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main(){
    sigset_t new_mask;

    printf("Mi PID es: %i\n", getpid());

    //Vaciamos la mascara
    sigemptyset(&new_mask);

    //Rellenamos la mascara con todas la seniales
    sigfillset(&new_mask);

    //Eliminamos SIGUSR1
    sigdelset(&new_mask, SIGUSR1);

    //Cuando suspendamos el programa no reaccionará a ninguna señal excepto SIGUSR1
    sigsuspend(&new_mask);
}