/*
    SOLEDAD RUIZ GÓMEZ
    SO MÓDULO II SESIÓN 6 EJERCICIO 2
    ejer2.c
    gcc -g ejer2.c -o ejer2

    NO FUNCIONA OK
*/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main (int argc, char * argv[]) {
	
    // COMPROBACIÓN DE ARGUMENTOS

    if (argc < 2) {
        printf ("\nNumero de argumentos incorrecto\n\n");
        exit(-1);
    }

    int i = 0;
    while (strcmp (argv[i], "|") != 0) {
        i++;
    }

    if (!i) { //si i==0, no se ha encontrado el cauce
        printf ("\nError: Argumento símbolo ha de ser '|'\n\n");
        exit(-1);
    }

    // LECTURA DE ARGUMENTOS


    // leemos la primera orden pasada como argumento (que puede constar de varias cadenas char*)
    char ** orden1 = (char**) malloc (sizeof(char *) * (i+1)); // tamaño hasta el cauce
    for (int j=1; j<i; j++) {
        orden1[j-1] = (char*) malloc (strlen(argv[j])+1); 
        strcpy (orden1[j-1], argv[j]);
    }
    orden1[i] = NULL; //NULL por convenio para llamar a exe

    // sabemos que el símbolo es |
    // char * simbolo = argv[i];

    // leemos la segunda orden pasada como argumento (que puede constar de varias cadenas char*)
    char ** orden2 = (char**) malloc (sizeof(char *) * (argc-i+1)); // tamaño desde el cauce
    for (int j=1; j<(argc-i); j++) {
        orden2[j-1] = (char*) malloc (strlen(argv[j+i])+1); 
        strcpy (orden2[j-1], argv[j+i]);
    }
    orden2[argc-i] = NULL; //NULL por convenio para llamar a exe
	
    // EJECUCIÓN

    // Vamos a crear un proceso hijo que ejecute la primera orden y la pase por un cauce
    // (que vamos a abrir) al proceso padre, que se encargará de la segunda orden

    int fd[2]; // entrada - salida
    pid_t pid; // para ver si estamos en el hijo o en el padre
    pipe (fd); // abrimos el cauce

    if ((pid=fork()) < 0) { 
        perror ("\nError en el fork\n");
        exit(-1);

    } else if (pid == 0) { // estamos en el hijo -> primera orden

        // el hijo va a escribir en el cauce, por lo que tenemos que cerrar el descriptor
        // de lectura (que es el fd[0])
        close (fd[0]);

        // ahora cerramos la salida estándar para que el hijo use fd[1] como salida estándar
        // como en el ejer anterior, duplicamos 
        close (STDOUT_FILENO);

        fcntl (fd[1], F_DUPFD, STDOUT_FILENO);
        if (execvp (argv[1], orden1) < 0) {
            printf ("\nError en el primer execvp\n");
            exit (-1);
       }

    } else { // estamos en el padre -> segunda orden

        // ahora nos toca cerrar la salida del cauce porque sólo vamos a leer
        close(fd[1]);

        // quitamos la entrada estándar y la cambiamos por nuestro fd, como antes
        close (STDIN_FILENO);

        fcntl (fd[0], F_DUPFD, STDIN_FILENO);
        if (execvp (argv[i+1], orden2) < 0) {
            printf ("\nError en el segundo execvp\n");
            exit (-1);
       }

    }

    // fin :)

	return 0;
}