/*
SOLEDAD RUIZ GÓMEZ
ejer2.c
Práctica 2 actividad 2.2 ejerecicio 3 con modificación recursiva (ejercicio 4)
gcc -g ejer2.c -o ejer2
./ejer2 <DIR (opcional) >

NOTA: Salen un par de warnings al compilar pero funciona bien
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<dirent.h>						
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<ftw.h>

int contador = 0;
int suma_bytes = 0;


int buscar (const char* path, const struct stat* stat, int flags, struct FTW* ftw) {

	mode_t mode = stat->st_mode;
	int    ino  = stat->st_ino;
	
	// Imprimimos los i-nodos con el nombre del archivo
	
	printf("\n%s : \n", path);
	printf("%d \n", ino);

	// Vemos si el archivo es regular, con permiso de ejecución para grupo y others
	
	if (mode & S_IFREG && mode & S_IXGRP && mode & S_IXOTH) { contador++; suma_bytes+=stat->st_size; }

	return 0;

}


int main(int argc, char *argv[]) {


	printf ("\nLos i-nodos son: \n");

	if (nftw(argc >= 2 ? argv[1] : ".", buscar, 10, 0) != 0) perror ("nftw");
		// recorremos recursivamente el directorio pasado como argumento (el actual si no hemos pasado ninguno)
		// llamamos a la unción buscar sobre cada archivo
		// abrimos hasta 10 archivos a la vez por directorio, y no tenemos opciones (0)
		

	printf ("\nExisten %d archivos regulares con permiso x para grupo y otros", contador);
	printf ("\nEl tamaño total ocupado por dichos archivos es de  %d bytes\n\n", suma_bytes);

	return EXIT_SUCCESS;
}
