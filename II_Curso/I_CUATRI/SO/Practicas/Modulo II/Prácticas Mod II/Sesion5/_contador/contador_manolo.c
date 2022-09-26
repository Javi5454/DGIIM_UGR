#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

static int j;
static int signals[31];      // Linux soporta únicamente 32 señales.
static void handler(int signum){

    signals[signum]++;
    printf("Se ha recibido la señal %d un numero de veces %d\n", signum, signals[signum]);
}

int main(int argc, char * argv[]){

    struct sigaction sa;

    if (setvbuf(stdout, NULL, _IONBF,0)){

        perror("\nError en setvbuf");
    }

    sa.sa_handler = handler;    // Acción que se asocia a la señal signum.
    sigemptyset(&sa.sa_mask);   // Señales igualadas a 0.
    sa.sa_flags = 0;

    int signals[31];
    for (int j = 1; j < 31; j++)    signals[j] = 0;     // Inicializamos todos los contadores a 0.

    int i = 1;
    while (i < 31){

        if (i != 9 && i != 19)

            if (sigaction(i, &sa, NULL) == -1)   perror("\nError al intentar establecer el manejardor de señal");
        
        i++;
    }
    for(;;){};
}