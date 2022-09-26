// SOLEDAD RUIZ GÓMEZ
// escritor.c


#include <sys/types.h>	
#include <sys/stat.h>	
#include <sys/wait.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

#define PERMISOS 444


int main(int argc, char *argv[]) { // ESCRITOR

	// Los argumentos ya están comprobados por el padre
    // Cogemos el file descriptor

	int fd = atoi (argv[2]); 

    if (!strcmp (argv[1], "fin")) {
        fchmod (fd, PERMISOS); // cambiamos los permisos al file 
    
    } else { // entonces el primer arg es un entero

        // Guardamos el número en un búfer 
        char buf[256];
        sprintf (buf, "%s\n", argv[1]);	// en vez de sacar a pantalla, guarda el mensaje especificado en el espacio de memoria buf

        // Escribir en fd
        if (write(fd, buf, strlen(buf)) != strlen(buf)) {	// escribe lo guardado en el búfer buf en el archivo fdw. el búfer se limpia tras esto
            perror("\nError en escritura \n");	
            exit(EXIT_FAILURE);
        }

    }

	exit (EXIT_SUCCESS);
	
}