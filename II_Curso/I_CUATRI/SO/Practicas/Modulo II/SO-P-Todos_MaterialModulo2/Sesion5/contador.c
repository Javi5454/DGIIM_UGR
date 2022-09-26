#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static int seniales[31];

void sig_USR_hdlr (int i){
    seniales[i]++;
    printf("La senial %i ha sido recibia %i veces\n", i, seniales[i]);
}

int main(int argc,char *argv[]){
    struct sigaction sig_USR_nact;

    if (setvbuf(stdout, NULL, _IONBF, 0)){
        perror("\nError en setvbuf");
    }

    printf("Mi PID es: %d\n", getpid());

    //Inicializamos la estrucuta sig_USR_na para especificar la nueva accion para la señal

    sig_USR_nact.sa_handler = sig_USR_hdlr;

    //Iniciamos al conjunto de señales dado como vacio
    sigemptyset(&sig_USR_nact.sa_mask);
    sig_USR_nact.sa_flags = 0;

    for (size_t i = 0; i < 31; i++)
    {
        seniales[i] = 0; //Inicializamos el contador a 0
    }

    for (size_t i = 1; i < 31 && i != SIGSTOP && i != SIGKILL; i++)
    {
        if (sigaction(i, &sig_USR_nact, NULL) == -1){
            printf("No se puede manejar %i\n", i);
        }
    }

    while(1);
    
    
}