/*
    SOLEDAD RUIZ GÓMEZ
    SO MÓDULO II SESIÓN 6 EJERCICIO 1
    ejer1.c
    gcc -g ejer1.c -o ejer1
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

    // LECTURA DE ARGUMENTOS

    // leemos la orden pasada como argumento (que puede constar de varias cadenas char*)
    char * args[argc-1];
    for (int i=1; i<=argc-3; i++) {
        args[i-1] = (char*) malloc (strlen(argv[i])+1);
        strcpy (args[i-1], argv[i]);
    }
    args[argc-2] = NULL; //NULL por convenio para llamar a exe, ult posicion es argc-1-1=argc-2

    // leemos el símbolo (no sabemos cuántos args ha ocupado la orden)
    char * simbolo = argv[argc-2];

    // leemos el nombre del archivo
    char * file = argv[argc-1];
	
	
    // EJECUCIÓN

    // si simbolo es >, tenemos que escribir en file, si es <, tenemos que leer de file
    int fd; //file descriptor de file

    int r = (strcmp (simbolo, "<") == 0);
    int w = (strcmp (simbolo, ">") == 0);

    if (!r && !w) { // si el simbolo no está bien introducido
        printf ("\nError en el penúltimo argumento. Ha de ser '>' o '<'");
        exit (-1);
    
    } else if (r) { // leemos del archivo (redirección de entrada)

        // abrimos el archivo con opción lectura comprobando que se ha abierto correctamente

        if ((fd = open (file, O_RDONLY))<0) {
            printf("\nError %d en open read file\n",errno);
            perror("\nError en open\n");
            exit(EXIT_FAILURE);
        }

        // ceramos la entrada estándar para que ese file descriptor (ese número) esté disponible
        close (STDIN_FILENO);

        // hacemos un duplicado del descriptor fd de file
        if (fcntl (fd, F_DUPFD, STDIN_FILENO) == -1) {
            perror ("\nError en fcntl\n");
            exit (-1);
        }
        // como acabábamos de cerrar la entrada estándar, sabemos que ahora ese número está 
        // disponible y que el duplicado que acabamos de crear ha tomado ese valor
        // entonces, ahora podemos (tranquilamente) hacer un exe, que ejecutará con la entrada
        // estándar (que va a ser un file descriptor apuntando a nuestro file)

        // REPASAR ESTO CON EL PROFE

        if (execvp (argv[1], args) < 0) {
            printf ("\nError en el execvp\n");
            exit (-1);
        }
            // y hemos terminado :)

    } else { // en este caso w es true -> escribimos en el archivo

        // abrimos el archivo con opción escritura comprobando que se ha abierto correctamente
        // aquí hemos de tener en cuenta que, si no existe, hay que crearlo, y que si existe y 
        // ya está escrito, hay que sobreescribirlo

        if ((fd = open (file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) < 0) {
            printf("\nError %d en open write file\n",errno);
            perror("\nError en open\n");
            exit(EXIT_FAILURE);
        }

        // ceramos la salida estándar para que ese file descriptor (ese número) esté disponible
        close (STDOUT_FILENO);

        // hacemos un duplicado del descriptor fd de file
        if (fcntl (fd, F_DUPFD, STDOUT_FILENO) == -1) {
            perror ("\nError en fcntl\n");
            exit (-1);
        }
        // como acabábamos de cerrar la salida estándar, sabemos que ahora ese número está 
        // disponible y que el duplicado que acabamos de crear ha tomado ese valor
        // entonces, ahora podemos (tranquilamente) hacer un exe, que ejecutará con la salida
        // estándar (que va a ser un file descriptor apuntando a nuestro file)

        // REPASAR ESTO CON EL PROFE

        if (execvp (argv[1], args) < 0) {
            printf ("\nError en el execvp\n");
            exit (-1);
        }
            // fin :)

    }

	return 0;
}
