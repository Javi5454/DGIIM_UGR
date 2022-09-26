/*
    SOLEDAD RUIZ GÓMEZ
    SO MÓDULO II SESIÓN 6 EJERCICIO 4
    ejer4.c
    gcc -g ejer4.c -o ejer4

    NO FUNCIONA OK
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main (int argc, char * argv[]) {
	
    // Vamos a crear un archivo en tmp y lo vamos a bloquear al inicio del programa
    // Justo antes de terminar la ejecución, lo desbloquearemos. Si se quiere hacer 
    // otra instancia simultánea del mismo programa, como no se podrá bloquear el archivo,
    // la nueva ejecución tendrá que esperar

    char file[] = "/tmp/bloqueadoo";
    struct flock cerrojo;
    int fd;

    umask (777); // ponemos los permisos por defecto
               // esto es necesario porque si no hay permiso de lectura en file, no podremos
               // ejecutar el programa una vez creado el archivo (habrá error en el open con permission denied)
            

    // creamos el archivo
    if ((fd = open (file, O_CREAT | O_RDWR | O_TRUNC)) < 0) {
        printf("\nError %d en open read file\n",errno);
        perror("\nError en open\n");
        exit(EXIT_FAILURE);
    }

    // seteamos el cerrojo
    cerrojo.l_type = F_WRLCK; // de escritura
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0; // todo el archivo

    // ponemos el cerrojo
    if (fcntl(fd, F_SETLKW, &cerrojo) == -1) {
        if (errno & (EACCES | EAGAIN)) {    // si el cerrojo no se puede poner pq ya hay uno
                                            // (esto es, si hay otra instancia del programa)
            printf("\nError al poner el cerrojo -> Ya hay otra instancia del programa\n");
            exit(EXIT_FAILURE);
        }
    }

    printf ("\nSoy la instancia del programa\n\n");
    sleep (10); // aquí podemos intentar ejecutar el programa de nuevo

    // fin :)

	return 0;
}