/*
SOLEDAD RUIZ GÓMEZ
recorrer.c
Ejercicio propuesto por el profe para las sesiones 1, 2 y 3
gcc -g recorrer.c -o recorrer

El programa se apoya en el ejecutable contador_reg

*/

#include <sys/types.h>
#include <sys/stat.h>	
#include <sys/wait.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


int main(int argc, char *argv[]) {

    // COMPROBACIÓN DE ARGUMENTOS

    // Número de argumentos
    if (argc != 2) {
		printf ("\nNúmero de argumentos incorrecto\n\n");
		exit (EXIT_FAILURE);
	}

    // Vemos que el segundo arg sea un directorio válido
   
    struct stat atributosdir;
   
    if (lstat (argv[1], &atributosdir) < 0) {
        printf ("\nError al intentar acceder a los atributos de %s\n\n", argv[1]);
        perror("\nError en lstat\n\n");
        exit (EXIT_FAILURE);
    }

    if (!S_ISDIR(atributosdir.st_mode)) {
        printf ("\nIntroduzca un directorio válido como primer argumento al ejecutable\n\n");
		exit (EXIT_FAILURE);
    }


    // EMPEZAMOS LA EJECUCIÓN FUNCIONAL DEL PROGRAMA

    // Impresión del PID del proceso y del PID de su padre

    printf ("\nSoy el hijo %d y mi padre es %d\n", getpid(), getppid());
    printf ("\nEstoy en el directorio %s\n", argv[1]);

    // Abrimos el directorio

    DIR * directorio;
    if ((directorio = opendir (argv[1])) == NULL) {
        printf ("\nError al intentar abrir el directorio %s\n\n", argv[1]);
        perror("\nError en opendir\n\n");
        exit (EXIT_FAILURE);
    }

    // Recorrido del directorio en búsqueda de los archivos regulares
    
    int value = 0; // para la cantidad de archivos regulares
    int size  = 0; // para el tamaño acumulado de los archivos regulares
    struct dirent * file; // aux
    struct stat atributosfile;  // para los metadatos del archivo leído en cada vuelta del bucle

    errno = 0; //para comprobar si ha habido error o no

    while ((file = readdir (directorio))!= NULL) {

        // Necesitamos la ruta al file en formato subdirectorio/file
        char path[200];
        strcpy(path, argv[1]);
        strcat(path, "/");
        strcat(path,file->d_name);

        // conseguimos los metadatos de file
        if (stat (path, &atributosfile) < 0) {
            printf ("\nError al intentar acceder a los atributos de %s\n\n", path);
            perror("\nError en lstat\n\n");
            exit (EXIT_FAILURE);
        }

        // comprobamos si se trata de un directorio

        if (S_ISREG (atributosfile.st_mode)) {
            value++;
            size += atributosfile.st_size;
        }
    
    }

    // Cuando salimos del bucle, puede ser porque acabemos de recorrer el directorio o 
    // porque haya habido un error: Para saber en qué escenario estamos, consultamos errno

    if (errno) { // si es distinto de 0
        printf ("\nError al recorrer el directorio %s con error %d\n\n", argv[1], errno);
        perror("\nError en readdir\n\n");
        exit (EXIT_FAILURE);
    }

    // Imprimimos el directorio que nos han pasado como argumento y la suma de tamaños de los archivos regulares

    printf ("\nEn el directorio %s, la suma de tamaños de los archivos regulares encontrados ha sido de un total de %d bytes\n", argv[1], size);

    // Devolvemos el número de archivos regulares encontrado
printf ("valur %d", value);
	return value;

}