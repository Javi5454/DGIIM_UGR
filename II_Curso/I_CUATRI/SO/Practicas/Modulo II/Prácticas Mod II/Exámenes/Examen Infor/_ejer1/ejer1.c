// SOLEDAD RUIZ GÓMEZ
// Ejercicio 1 examen infor SO MódII 2020/2021

// Se puede hacer con la llamada nftw


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

#define DEC 10

// Función recursiva para recorrer directorios como el ejercicio nos pide

void directory (char * dir, int depth, int fd, int blocks) {

    int count = depth - 1; // para llevar cuenta de cuánto tenemos que profundizar

    if (count >= 0) {

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

            // Comprobamos si es directorio (no aceptamos '.' ni '..')
            if (S_ISDIR (metadatafile.st_mode) && strcmp(file->d_name, ".") && strcmp(file->d_name, "..")) {

                // Llamamos a directory (recursivamente)
                directory (path, count, fd, blocks);

                // path es el directorio que acabamos de encontrar y que queremos recorrer
                // count es la profundidad actualizada
                // fd y blocks nunca varían su valor
            }

            // Comprobamos si es archivo regular
            else if (S_ISREG (metadatafile.st_mode)) {
        
                // Miramos el número de bloques que tiene
                if (metadatafile.st_blocks > blocks) {

                    // Si tiene más bloques, escribimos en fs (que ya está abierto)

                    // Guardamos el nombre del archivo en un búfer
                    char buf[256];
                    sprintf (buf, "%s\n", path);	// en vez de sacar a pantalla, guarda el mensaje especificado en el espacio de memoria buf

                    // Escribir en fd
                    if (write(fd, buf, strlen(buf)) != strlen(buf)) {	// escribe lo guardado en el búfer buf en el archivo fdw. el búfer se limpia tras esto
                        perror("\nError en escritura \n");	
                        exit(EXIT_FAILURE);
                    }
                }
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

}


int main(int argc, char *argv[]) {

// COMPROBACIÓN DE ARGUMENTOS

    // Número de argumentos
    if (argc != 5) {
		perror ("\nNúmero de argumentos incorrecto\n\n");
		exit (EXIT_FAILURE);
	}

    // Vemos que el segundo y quinto arg sean directorios válidos
   
    struct stat atrdir;
    struct stat atrdirdest;
   
    if (lstat (argv[1], &atrdir) < 0) {
        printf ("\nError al intentar acceder a los atributos de %s\n\n", argv[1]);
        perror("\nError en lstat\n\n");
        exit (EXIT_FAILURE);
    }

    if (!S_ISDIR(atrdir.st_mode)) {
        printf ("\nIntroduzca un directorio válido como primer argumento al ejecutable\n\n");
		exit (EXIT_FAILURE);
    }

    if (lstat (argv[4], &atrdirdest) < 0) {
        printf ("\nError al intentar acceder a los atributos de %s\n\n", argv[1]);
        perror("\nError en lstat\n\n");
        exit (EXIT_FAILURE);
    }

    if (!S_ISDIR(atrdirdest.st_mode)) {
        printf ("\nIntroduzca un directorio válido como primer argumento al ejecutable\n\n");
		exit (EXIT_FAILURE);
    }

    // Recogemos la información de los argumentos restantes

    errno = 0;

    int bloques     = strtol(argv[2], NULL, DEC);
    int profundidad = strtol(argv[3], NULL, DEC);

    if (errno || bloques < 0 || profundidad < 0) {
        perror("\nError: los argumentos 2 y 3 pasados al ejecutable han de ser enteros positivos\n\n");
        exit (EXIT_FAILURE);
    }


// EMPEZAMOS LA EJECUCIÓN FUNCIONAL DEL PROGRAMA

    // Apertura de archivo "resultado.txt" en el archivo destino

    // Necesitamos la ruta al file en formato directorio/file
    char resultado[256];
    strcpy(resultado, argv[4]);
    strcat(resultado, "/");
    strcat(resultado,"resultado.txt");

    int fd;

    if ((fd=open(resultado,O_CREAT|O_TRUNC|O_RDWR,S_IRWXU))<0) {	// archivo para escribir (lo creamos si no existe y borramos su contenido si ya existe)
        printf("\nError %d en open read file\n",errno);
        perror("\nError en open\n");
        exit(EXIT_FAILURE);
    }

    // Cabecera del archivo
    char buf[256];
    sprintf (buf, "ARCHIVOS CON MÁS DE %d BLOQUES\n\n", bloques);	// en vez de sacar a pantalla, guarda el mensaje especificado en el espacio de memoria buf

    // Escribir en fd
    if (write(fd, buf, strlen(buf)) != strlen(buf)) {	// escribe lo guardado en el búfer bufw en el archivo fdw. el búfer se limpia tras esto
        perror("\nError en escritura \n");	
        exit(EXIT_FAILURE);
    }

    // Apertura de directorios de manera recursiva con una función

    directory (argv[1], profundidad, fd, bloques);

    close (fd); //cerramos el archivo resultado

    exit(EXIT_SUCCESS);

}