/*
    SOLEDAD RUIZ GÓMEZ
    SO MÓDULO II SESIÓN 6 EJERCICIO 5
    ejer5.c
    gcc -g ejer5.c -o ejer5

    NO FUNCIONA OK

    Escribir un programa, similar a la orden cp, que utilice para su implementación la
    llamada al sistema mmap() y una función de C que nos permite copiar memoria, como por
    ejemplo memcpy(). Para conocer el tamaño del archivo origen podemos utilizar stat() y para
    establecer el tamaño del archivo destino se puede usar ftruncate().
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SIZE 32768

int main (int argc, char * argv[]) {
	
    // Vamos a copiar un archivo en otro

    char *p1, *p2;
    int fd1, fd2;
    struct stat atributos1, atributos2;

    // COMPROBACIÓN DE ARGUMENTOS 
    if (argc != 3) {
        printf ("\nNumero de argumentos incorrecto\n\n");
        exit(-1);
    }

    umask(0); // todos los archivos que cree tendrán UNICAMENTE los permisos especificados

    // APERTURA DE ARCHIVOS
    
    // Primer archivo -> lectura
    if ((fd1 = open(argv[1], O_RDWR, S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH)) < 0) {
        printf("\nError %d en open read file\n",errno);
        perror("\nError en open\n");
        exit(EXIT_FAILURE);
    }

    // Segundo archivo -> escritura
    if ((fd2 = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH)) < 0) {
        printf("\nError %d en open write file\n",errno);
        perror("\nError en open\n");
        exit(EXIT_FAILURE);
    }

    // LINKEAMOS METADATOS
    if (fstat(fd1, &atributos1) == -1) {
        printf ("\nError en metadatos primer archivo\n");
        exit (EXIT_FAILURE);
    }

    // Antes de linkear para el segundo archivo...

    // ARCHIVO REGULAR (lo queremos con caracteres)
    if (!S_ISREG(atributos1.st_mode)) {
        printf ("\nError: el archivo no es regular\n");
        exit (EXIT_FAILURE);
    }

    // MODIFICAR EL TAMAÑO DEL SEGUNDO ARCHIVO (NO SABEMOS SI YA EXISTÍA)
    if (ftruncate (fd2, atributos1.st_size) == -1) {
        printf ("\nError al truncar el tamaño del segundo archivo\n");
        exit(EXIT_FAILURE);
    }

    // Ahora sí, linkeamos para el segundo
    if (fstat(fd2, &atributos2) == -1) {
        printf ("\nError en metadatos segundo archivo\n");
        exit (EXIT_FAILURE);
    }

    // MAPEAMOS EL PRIMER ARCHIVO

    p1 = (char*) mmap (NULL, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd1, 0);

    if (p1 == MAP_FAILED) {
        printf ("\nError en el primer map\n");
        exit(EXIT_FAILURE);
    }

    close (fd1); //podemos cerrar el primer descriptor

    // MAPEAMOS EL SEGUNDO ARCHIVO
    p2 = (char*) mmap (NULL, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd2, 0);

    if (p2 == MAP_FAILED) {
        printf ("\nError en el segundo map\n");
        exit(EXIT_FAILURE);
    }

    close (fd2); //podemos cerrar el segundo descriptor

    // COPIAMOS DOS ESPACIOS DE MEMORIA (memcpy)
    memcpy (p2, p1, atributos2.st_size);

    // CERRAMOS LAS PROYECCIONES
    if (munmap (p1, atributos1.st_size) == -1) {
        printf("\nError al cerrar el primer mapa\n");
        exit(EXIT_FAILURE);
    }

    if (munmap (p2, atributos2.st_size) == -1) {
        printf("\nError al cerrar el segundo mapa\n");
        exit(EXIT_FAILURE);
    }

    // fin :)

	return 0;
}