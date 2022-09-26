/*
SOLEDAD RUIZ GÓMEZ 
ejer1_2.c
Práctica 1 actividad 3.1 ejercicio 2
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

const int BYTES = 80;

int main(int argc, char *argv[]) {

int fdr, fdw;
char bufr[BYTES];

// Vemos si se puede abrir el archivo
if ((fdr=open(argv[1],O_RDONLY,S_IRUSR))<0) {	// archivo sólo de lectura. permiso al user noseq
	printf("\nError %d en open read file\n",errno);
	perror("\nError en open\n");
	exit(EXIT_FAILURE);
}

if ((fdw=open(argv[2],O_TRUNC|O_WRONLY,S_IWUSR))<0) {	// archivo de escritura, si tiene algo escrito previamente, se borrará. permiso al user noseq
	printf("\nError %d en open write file \n",errno);
	perror("\nError en open \n");
	exit(EXIT_FAILURE);
}

// Comenzamos a leer de 80 en 80 Bytes
int i = 1;
int readable;

do {
	
	readable = (read(fdr,bufr,BYTES)); // para ver si hemos leido 80B. read reposiciona el solito el puntero de lectura para la siguiente vuelta al bucle
	
	char bufw[100];
	
	sprintf (bufw, "\n\nBloque %d \n", i);	// en vez de sacar a pantalla, guarda el mensaje especificado en el espacio de memoria bufw
	
	write (fdw, bufw, strlen(bufw));	// escribe lo guardado en el búfer bufw en el archivo fdw. el búfer se limpia tras esto
	
	if(write(fdw,bufr,BYTES) != BYTES) {	// escribe lo guardado en el búfer bufr en el archivo fdw
		perror("\nError en escritura \n");	
		exit(EXIT_FAILURE);
	}
	
	
	i++;
	
} while (readable==BYTES);

close(fdr);
close(fdw);	// cerramos los archivos

return EXIT_SUCCESS;
}
