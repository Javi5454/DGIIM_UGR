/*
    SOLEDAD RUIZ GÓMEZ 2ºDGIIM
    
    EXAMEN PRÁCTICAS SISTEMAS OPERATIVOS MÓDULO II

    20 DICIEMBRE 2021

    EJERCICIO 1

    NOTA: de lo único q no estoy egura es del permiso de ejecución del propietario

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
#include <fcntl.h>
#include <signal.h>

#define TAM 256 


// Función recursiva para recorrer directorios como el ejercicio nos pide

void directory (char * dir, char * cad) {


    // Abrimos el directorio pasado como argumento
    DIR * directorio;
    if ((directorio = opendir (dir)) == NULL) {
        printf ("\nError al intentar abrir el directorio %s\n\n", dir);
        perror("\nError en opendir\n\n");
        exit (EXIT_FAILURE);
    }

    // Pasamos a recorrer directorio

    struct dirent * file;       // archivo leído
    struct stat metadatafile;   // para los metadatos del archivo leído en cada vuelta del bucle

    errno = 0; // para ver si ha habido error al recorrer el directorio

    while ((file = readdir (directorio))!= NULL) {
        
        // Arriba hemos leido el archivo que toque y comprobado que no es NULL

        // Necesitamos la ruta al file en formato subdirectorio/file
        char path[255];
        strcpy(path, dir);
        strcat(path, "/");
        strcat(path,file->d_name);

        // Conseguimos los metadatos de file
        if (stat (path, &metadatafile) < 0) {
            printf ("\nError al intentar acceder a los atributos de %s\n\n", path);
            perror("\nError en stat\n\n");
            exit (EXIT_FAILURE);
        }

        // Comprobamos si es regular y el usuario tiene permiso de ejecución
        if (S_ISDIR (metadatafile.st_mode) && strcmp(file->d_name, ".") && strcmp(file->d_name, "..")) {

            // Llamamos a directory (recursivamente)
            directory (path, cad);

            // path es el directorio que acabamos de encontrar y que queremos recorrer
            // cad nunca varía su valor
        }

        // Comprobamos si es archivo regular y el usuario tiene permiso de ejecución
        else if (S_ISREG (metadatafile.st_mode) && (metadatafile.st_mode & S_IXUSR) == S_IXUSR) { //
            // Miramos si su nombre comienza por cad
            int equal = 1;

            int lencad  = strlen(cad);
            int lenfile = strlen(file->d_name);

            if (lencad <= lenfile) {

                char filename [lencad];
                strncpy (filename, file->d_name, lencad);
                
                if (strcmp(filename, cad))  equal = 0;
            
            } else {
                equal = 0; //porque, desde luego, file->d_name no empieza por cad (es más corto)
            }

            // Si es el caso, sacamos a salida estándar
            if (equal)  printf ("\nEncontrado: %s\n", path);


        } 
        
    }

    // Cuando salimos del bucle, puede ser porque acabemos de recorrer el directorio o 
    // porque haya habido un error: Para saber en qué escenario estamos, consultamos errno

    if (errno) { // si es distinto de 0
        printf ("\nError al recorrer el directorio %s con error %d\n\n", dir, errno);
        perror("\nError en readdir\n\n");
        exit (EXIT_FAILURE);
    }

}

int main(int argc, char *argv[]) {

// COMPROBACIÓN DE ARGUMENTOS

    // Número de argumentos
    if (argc != 3) {
		perror ("\nNúmero de argumentos incorrecto\n\n");
		exit (EXIT_FAILURE);
	}

// Ver que el segundo arg es un directorio

    struct stat atrdir;
   
    if (lstat (argv[2], &atrdir) < 0) {
        printf ("\nError al intentar acceder a los atributos de %s\n\n", argv[2]);
        perror("\nError en lstat\n\n");
        exit (EXIT_FAILURE);
    }

    if (!S_ISDIR(atrdir.st_mode)) {
        printf ("\nIntroduzca un directorio válido como segundo argumento al ejecutable\n\n");
		exit (EXIT_FAILURE);
    }


// EJECUCIÓN FUNCIONAL DEL PROGRAMA

// Idea: para recorrer un directorio de manera recursiva, es muy útil usar la llamada al sistema nftw. Sin embargo, 
// cuando queramos comparar el nombre de los archivos con la cadena pasada como primer argumento, querremos su nombre,
// no la ruta hasta él. Desgraciadamente, nftw nos proporciona la ruta. Es por esto por lo que considero una mejor opción
// hacer nosotros mismos una función recursiva que, como nftw, recorra el directorio. De esta manera, tendremos el nombre
// del archivo, no la ruta a sí mismo.

// Llamamos, pues, a nuestra función, y dejamos que ella se encargue del resto

    directory (argv[2], argv[1]);


    exit (EXIT_SUCCESS);
}