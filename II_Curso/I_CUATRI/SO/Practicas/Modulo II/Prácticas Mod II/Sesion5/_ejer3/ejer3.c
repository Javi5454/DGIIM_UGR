/* SOLEDAD RUIZ GÓMEZ
    SO PRÁCTICAS MÓDULO II SESIÓN 5 EJERCICIO 3
    ejer3.c
*/

#include <stdio.h>
#include <signal.h>

int main() {
    
    sigset_t new_mask;

    /* inicializar la nueva mascara de señales con todas las señales menos SIGUSR1*/
    sigfillset(&new_mask);

    sigdelset(&new_mask, SIGUSR1);

    /*esperar a SIGUSR1 */
    sigsuspend(&new_mask);

    // no puedo usar el raise pq se suspende el programa y no la ejecuta

}
