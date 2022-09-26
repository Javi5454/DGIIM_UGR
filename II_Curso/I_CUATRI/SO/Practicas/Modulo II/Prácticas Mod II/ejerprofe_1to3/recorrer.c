/*
SOLEDAD RUIZ GÓMEZ
recorrer.c
Ejercicio propuesto por el profe para las sesiones 1, 2 y 3
gcc -g recorrer.c -o recorrer


// Idea inicial_ 
El programa se apoya en el ejecutable contador_reg, haceos una llamada exe
Sin embargo, no podemos entonces retornar un valor del hijo, y esto supone un problema

// Por ello, directamente ponemos el código que queremos que ejecute el hijo en ese archivo

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

static int value;


int main(int argc, char *argv[]) {

    // COMPROBACIÓN DE ARGUMENTOS

    // Número de argumentos
    if (argc != 2) {
		perror ("\nNúmero de argumentos incorrecto\n\n");
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

    printf ("\nSoy el proceso %d y mi padre es %d\n", getpid(), getppid());

    // Abrimos el directorio

    printf ("\n-> Procedo a abrir el directorio\n");

    DIR * directorio;
    if ((directorio = opendir (argv[1])) == NULL) {
        printf ("\nError al intentar abrir el directorio %s\n\n", argv[1]);
        perror("\nError en opendir\n\n");
        exit (EXIT_FAILURE);
    } else {
        printf ("\n-> Directorio abierto\n");
    }

    // Recorrido del directorio en búsqueda de los subdirectorios
    
    struct dirent * file; // aux
    struct stat atributosfile;  // para los metadatos del archivo leído en cada vuelta del bucle
    int i = 0; // para rellenar el vector

    errno = 0; //para comprobar si ha habido error o no

    printf ("\n-> Procedo a recorrer el directorio\n");

    while ((file = readdir (directorio))!= NULL) {

        // arriba hemos leido el archivo que toque y comprobado que no es NULL

        // Necesitamos la ruta al file en formato subdirectorio/file
        char path[100];
        strcpy(path, argv[1]);
        strcat(path, "/");
        strcat(path,file->d_name);

        // conseguimos los metadatos de file
        if (stat (path, &atributosfile) < 0) {
            printf ("\nError al intentar acceder a los atributos de %s\n\n", path);
            perror("\nError en stat\n\n");
            exit (EXIT_FAILURE);
        }

        // comprobamos si se trata de un directorio

        if (S_ISDIR (atributosfile.st_mode) && strcmp(file->d_name, ".") && strcmp(file->d_name, "..")) {
            
            strcpy (file->d_name, path);

            // si lo es, creamos hijo

            pid_t pid; // para ver el pid del hijo

            if ((pid = fork()) < 0) {
                perror("\nError en fork\n");
                exit(EXIT_FAILURE);
                
            } else if (pid == 0) { // estamos en el hijo
                
                printf ("\n\n-> Hijo creado con éxito\n");
                
                // Ejecutamos su parte de código

                value = 0;

                // Impresión del PID del proceso y del PID de su padre

                printf ("\nSoy el hijo %d y mi padre es %d,", getpid(), getppid());
                printf (" estoy en el directorio %s\n", file->d_name);

                // Abrimos el directorio

                DIR * subdir;
                if ((subdir = opendir (file->d_name)) == NULL) {
                    printf ("\nError al intentar abrir el directorio %s\n\n", argv[1]);
                    perror("\nError en opendir\n\n");
                    exit (EXIT_FAILURE);
                }

                // Recorrido del directorio en búsqueda de los archivos regulares
                
                int size  = 0; // para el tamaño acumulado de los archivos regulares
                struct dirent * subfile; // aux
                struct stat subatributosfile;  // para los metadatos del archivo leído en cada vuelta del bucle

                errno = 0; //para comprobar si ha habido error o no

                while ((subfile = readdir (subdir))!= NULL) {

                    // Necesitamos la ruta al file en formato subdirectorio/file
                    char subpath[200];
                    strcpy(subpath, file->d_name);
                    strcat(subpath, "/");
                    strcat(subpath,subfile->d_name);

                    // conseguimos los metadatos de file
                    if (stat (subpath, &subatributosfile) < 0) {
                        printf ("\nError al intentar acceder a los atributos de %s\n\n", subpath);
                        perror("\nError en lstat\n\n");
                        exit (EXIT_FAILURE);
                    }

                    // comprobamos si se trata de un directorio

                    if (S_ISREG (subatributosfile.st_mode)) {
                        value++;
                        size += subatributosfile.st_size;
                    }
            
                }

                // Cuando salimos del bucle, puede ser porque acabemos de recorrer el directorio o 
                // porque haya habido un error: Para saber en qué escenario estamos, consultamos errno

                if (errno) { // si es distinto de 0
                    printf ("\nError al recorrer el directorio %s con error %d\n\n", file->d_name, errno);
                    perror("\nError en readdir\n\n");
                    exit (EXIT_FAILURE);
                }

                // Imprimimos el directorio que nos han pasado como argumento y la suma de tamaños de los archivos regulares

                printf ("\nEn el directorio %s, la suma de tamaños de los archivos regulares encontrados ha sido de un total de %d bytes\n", file->d_name, size);
                return (value);

            } else { // volvemos a trabajar con el proceso padre
            
                int retorno;

                if ((pid=wait (&retorno)) == -1) {  // esperamos al hijo
                    printf ("\nError al esperar al hijo con pid %d\n", pid);
                    exit(EXIT_FAILURE);
                } else {
                    retorno >>=8;
                    printf ("\nMi hijo con PID %d ha terminado devolviendo el valor de %d archivos regulares en su subdirectorio asignado, %s\n", pid, retorno, file->d_name);
                }
            }

        }

    } 

    // Cuando salimos del bucle, puede ser porque acabemos de recorrer el directorio o 
    // porque haya habido un error: Para saber en qué escenario estamos, consultamos errno

    if (errno) { // si es distinto de 0
        printf ("\nError al recorrer el directorio %s con error %d\n\n", argv[1], errno);
        perror ("\nError en readdir\n\n");
        exit (EXIT_FAILURE);



	exit(EXIT_SUCCESS);

    }
}