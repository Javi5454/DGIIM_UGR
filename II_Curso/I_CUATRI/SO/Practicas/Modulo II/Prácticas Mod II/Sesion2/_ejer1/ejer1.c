/*
SOLEDAD RUIZ G�MEZ
ejer1.c
Pr�ctica 2 actividad 2.2 ejercicio 2
gcc -g ejer1.c -o ejer1
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


void print_permisos (mode_t mode) {

// Users
if (mode & S_IRUSR) printf("r");
else printf("-");
if (mode & S_IWUSR) printf("w");
else printf("-");
if (mode & S_IXUSR) printf("x");
else printf("-");

// Groups
if (mode & S_IRGRP) printf("r");
else printf("-");
if (mode & S_IWGRP) printf("w");
else printf("-");
if (mode & S_IXGRP) printf("x");
else printf("-");

// Others
if (mode & S_IROTH) printf("r");
else printf("-");
if (mode & S_IWOTH) printf("w");
else printf("-");
if (mode & S_IXOTH) printf("x");
else printf("-");

printf ("\n");

}


int main(int argc, char *argv[]) {

	DIR * dirptr;
	struct stat atributos;

	//APERTURA DE DIRECTORIO

	if( (dirptr=opendir(argv[1])) == NULL ) {	// está en el primer argumento
		printf("\nError %d en opendir",errno);
		perror("\nError en open \n");
		exit(EXIT_FAILURE);
	}



	//IMPRESIÓN DE DATOS Y CÁLCULOS

	struct dirent * file;
	file = readdir (dirptr);	// primer archivo del directorio

	const int OCTAL = 8;
	long int permisos;
	permisos = strtol(argv[2], NULL, OCTAL);	// leemos el segundo argumento en octal

	while (file != NULL) {

		// Imprimimos el nombre del archivo

		printf("\n%s : \n", file->d_name);

		// Imprimimos permisos antiguos

		struct stat buf;
		mode_t mode;

		stat (file->d_name, &buf);	// paso los metadatos del archivo seleccionado al búfer
		mode = buf.st_mode;			// leo el mode del archivo

		printf ("P ant:\t\t%o  ", buf.st_mode);	// saco el número octal de permisos
		print_permisos (mode);					// saco las rwx
		
		// Cambiamos permisos
		
		//umask (permisos);
		chmod (file->d_name, permisos);
		
		// Imprimimos permisos nuevos
		
		stat (file->d_name, &buf);
		mode = buf.st_mode;

		printf ("P nuevo:\t%o  ", buf.st_mode);
		print_permisos (mode);
		

		// Leemos el siguiente archivo
		
		file = readdir (dirptr);
		
	}

	printf("\n");

	closedir(dirptr);

	return EXIT_SUCCESS;
}
