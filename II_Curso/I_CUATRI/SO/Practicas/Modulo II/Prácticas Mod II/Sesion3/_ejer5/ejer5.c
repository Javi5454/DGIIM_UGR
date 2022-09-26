/*
SOLEDAD RUIZ GÓMEZ
ejer5.c
Práctica 3 actividad 3.3 ejercicio 7
gcc -g ejer5.c -o ejer5

*/

#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include<string.h>


int main(int argc, char *argv[]) {

	pid_t pid;
	int estado;

	if (argc < 2) {
		printf ("\nNúmero de argumentos incorrecto\n\n");
		exit (-1);
	}

	// para ver si ejecutamos en segundo plano
	int bg = 0;
	if (strcmp (argv[argc-1], "bg")==0)	bg = 1;

	// ahora recogemos los argumentos para el ejecutable
	int nargs = argc - 1; 	//porque el primero es el nombre del ejecutable
	if (bg)	nargs--; 		//porque si bg es true, el ult argumento no es un argumento apra el ejecutable
	char * args[nargs+1];		//aqui concatenaremos os argumentos

	for (int i=1; i<=nargs;i++) {
		args[i-1] = (char*) malloc(strlen(argv[i])+1); //reservamos el espacio necesario
		strcpy (args[i-1], argv[i]); //copiamos 
	}
	args[nargs+1] = NULL; //por convenio, el último tiene que ser puntero NULL


	if (bg) {	// ejecutamos en background

		if( (pid=fork())<0) {
			perror("\nError en el fork");
			exit(EXIT_FAILURE);

		} else if (pid==0) {	//si estamos en el hijo, le damos el ejecutable a él, y entonces se ejecuta en bg
			if( (execv(argv[0],args)<0)) {
				printf ("No se puede ejecutar en background\n");
				perror("\nError en el execv");
				exit(EXIT_FAILURE);
			}
		}
	} else {	// nos quedamos en el padre, entonces estamos en foreground
		if( (execv(argv[0],args)<0)) {
			printf ("No se puede ejecutar en foreground\n");
			perror("\nError en el execv");
			exit(EXIT_FAILURE);
		}
	}

	// Opcional: liberar memoria

	for (int i=0; i<nargs; i++) {
		free (args[i]);
	}

	exit(EXIT_SUCCESS);

}
