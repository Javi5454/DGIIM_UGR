/*
Ejercicio: clave
Nombre: Javier Gómez López
DNI: 03949965Z
Fecha: 21/12/2021
*/

#include <sys/types.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

static void handler (int signum){
    
}

int main() {
    //Creamos un nuevo set de señales
    struct sigaction sa;
    sa.

    printf("Mi PID para enviarme señales es: %d\n", getpid());

    // vaciamos la máscara
    sigemptyset(&new_mask);

    // rellennamos la mascara
    sigfillset(&new_mask);

    // eliminamos SIGUSR1 y SIGUSR2
    sigdelset(&new_mask, SIGUSR1);
    sigdelset(&new_mask, SIGUSR2);

    int cont_1 = 0;
    int cont_2 = 0;

    while(1){ //Bucle hasta que introduzca la combinacion correcta
        sigsuspend(&new_mask);

        if sigac
    }
}
