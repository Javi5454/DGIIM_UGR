/*
    SOLEDAD RUIZ GÓMEZ
    SO MÓDULO II SESIÓN 6 EJERCICIO 3
    ejer3.c
    gcc -g ejer3.c -o ejer3
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main (int argc, char * argv[]) {
	
    // COMPROBACIÓN DE ARGUMENTOS

    if (argc != 2) {
        printf ("\nNumero de argumentos incorrecto\n\n");
        exit(-1);
    }

    struct flock cerrojo1, cerrojo2;
    int fd;
    pid_t pid;

    // abrimos el archivo que nos han pasado como argumento para leer y escribir comprobando la acción
    if ((fd = open (argv[1], O_RDWR))<0) {
        printf("\nError %d en open read file\n",errno);
        perror("\nError en open\n");
        exit(EXIT_FAILURE);
    }

    // jugando con el tipo de cerrojo y su longitud conseguimos distintas ejecuciones (probar)

    // ponemos los cerrojos
    cerrojo1.l_type = F_WRLCK; // de escritura
    cerrojo1.l_whence = SEEK_SET;
    cerrojo1.l_start = 0;
    cerrojo1.l_len = 9; // todo el archivo

    // no hacer esto: cerrojo2 = cerrojo1; (cuidado con las asignaciones entre estructuras)
    cerrojo2.l_type = F_WRLCK; // de escritura
    cerrojo2.l_whence = SEEK_SET;
    cerrojo2.l_start = 10;// ponemos el cerrojo 2 igual que el 1 pero más desplaazdo
    cerrojo2.l_len = 0; 


    // Ponemos el cerrojo 1 a fd
    if (fcntl(fd, F_SETLK, &cerrojo1) == -1) {  //F_SETLK hace q pase del cerrojo si n lo he conseguido a la primera
        printf("\nError al poner el cerrojo 1\n");
        exit(EXIT_FAILURE);
    } else {
        printf ("\nSoy el padre y he colocado el cerrojo1\n");  // el fork NO duplica este cerrojo puesto (el hijo no lo hereda)
    }

    // creamos un hijo (lo anterior se ha ejecutado en padre)
    if ((pid=fork()) < 0) {
        printf("\nError al crear el hijo con fork()\n");
        exit(EXIT_FAILURE);
    
    } else if (pid==0) { // estamos en el hijo, tratamos de poner otro cerrojo

        if (fcntl(fd, F_SETLK, &cerrojo2) == -1) {
            printf("\nError al poner el cerrojo 2 (hijo)\n");
            exit(EXIT_FAILURE);
        } else {
            printf ("\nSoy el hijo y he colocado el cerrojo2\n");
        }

        sleep (1);

        if (fcntl(fd, F_SETLK, &cerrojo1) == -1) { // tratamos de poner el cerrojo 1 desde el hijo
            printf("\nError al poner el cerrojo 1 (hijo)\n");
        } else {
            printf ("\nSoy el hijo y he colocado el cerrojo1\n"); // no hay problema pq lo ha heredado del padre y se superpone
        }

        return 0;
    
    } else {    // estamos en el padre

        sleep (2);

        if (fcntl(fd, F_SETLK, &cerrojo2) == -1) {
            printf("\nError al poner el cerrojo 2 (padre)\n");
            exit(EXIT_FAILURE);
        } else {
            printf ("\nSoy el padre y he colocado el cerrojo2\n");
        }

        waitpid (-1, NULL, WNOHANG); // recojo la info de todos mis niños que hayan terminado, pero mientras el padre 
                                 // sigue haciendo cosas (WNOHANG)

    }


    // fin :)

	return 0;
}