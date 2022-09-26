/*
SOLEDAD RUIZ GÓMEZ
 contador.c
Escribe un programa en C llamado contador, tal que cada vez que reciba una
señal que se pueda manejar, muestre por pantalla la señal y el número de veces que se ha
recibido ese tipo de señal, y un mensaje inicial indicando las señales
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static int contador [32];   // Linux soporta 32 señales
static void hdlr (int sig) {

	contador [sig]++;
	printf("\nLa señaĺ %d se ha recibido %d veces\n", sig, contador[sig]);
}

int main(int argc, char *argv[]) {

    const int sig1 = 9;
    const int sig2 = 19;

    printf("\nSoy el proceso %d\n", getpid());
    
    printf("\nNo puedo manejar la señal %d\n", sig1);
    printf("\nNo puedo manejar la señal %d\n", sig2);
    
    printf("\nEsperando envío de señales...\n");

    if (setvbuf(stdout, NULL, _IONBF,0)) {  //no guardamos la entrada en un búfer
                                            //la usamos directamente
        perror("\nError en setvbuf");
    }
    
    
    struct sigaction act;
    
    act.sa_handler= hdlr;
    
    sigemptyset (&act.sa_mask);	//no bloquea ninguna
     
    act.sa_flags = SA_RESTART;
    
    int contador [31];
    for (int i = 0; i<31; i++)
    	contador[i] = 0;	// pongo a 0 el contador de cada señal
    	
    	
    for (int i = 1; i<32; i++) {    // tiene que empezar en 1 porque a la señal 0 (term) no se le puede cambiar la acción
    	
        if (i!=9 && i!=19)
            if (sigaction (i, &act, NULL) == -1)
                printf ( "\nError en el handler\n");	
    }

    sleep (15); //aquí puedo mandarle distintas señales
    
    return 0;	
    
}