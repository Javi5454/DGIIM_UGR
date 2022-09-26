/*
SOLEDAD RUIZ G�MEZ
maestro.c
Pr�ctica 3 actividad 4.2 ejercicio 5
gcc -g maestro.c -o maestro
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>


int main(int argc, char *argv[]) { // PROGRAMA PRINCIPAL - MAESTRO
	
	// Comprobación de argumentos
	if (argc<3) { 
		printf("Error en la llamada a maestro. Introduzca un intervalo num�rico [n1, n2]\n") ; 
		exit(-1); 
	}

	// Leemos el intervalo y generamos los subintervalos
	int a = atoi (argv[1]);
	int d = atoi (argv[2]);
	int b = a + (d-a)/2;
	int c = b + 1;

	char ini [10];
	char fin [10]; // variables para que servirán como argumento a los esclavos
	
	// Creamos los cauces
	int fd1[2];
	pid_t PID1;
	pipe(fd1); // Llamada al sistema para crear el pipe de esclavo1
	
	int fd2[2];
	pid_t PID2;
	pipe(fd2); // Llamada al sistema para crear el pipe de esclavo2
	
	
	// ---------------------------------------------------------------------------------------


	// Creaci�n, llamada y lectura con esclavo1
	if ( (PID1= fork())<0) {
	
		perror("\nError en fork esclavo1");
		exit(EXIT_FAILURE);
		
	} else if (PID1 == 0) { // ESCLAVO1
	
		//Cerrar el descriptor de lectura de cauce en el proceso hijo
		close(fd1[0]);

		//Duplicar el descriptor de escritura en cauce en el descriptor
		//correspondiente a la salida estandar (stdout), cerrado previamente en
		//la misma operacion
		dup2(fd1[1],STDOUT_FILENO);
		
		sprintf(ini, "%d", a);
		sprintf(fin, "%d", b); //pasamos de entero a *char para poder pasar como argumentos a la funci�n esclavo
							   //la funcion sprintf nos permite cambiar el formato de un char*
		
		// Llamamos por primera vez al esclavo, que calcular� los primos del primer intervalo
		if(execl("./esclavo", "esclavo", ini, fin, NULL) < 0) {
			perror("\nError en el execl esclavo1");
			exit(EXIT_FAILURE);
		}	
	}
	else { // Volvemos a trabajar con el proceso padre (MAESTRO) porque PID1>0
	
		//Cerrar el descriptor de escritura en cauce situado en el proceso padre
		close(fd1[1]);
		
		// Leemos el cauce (cada vez un entero)
		printf ("Primos calculados por el primer esclavo: ");
		int primo;
		
		while (read(fd1[0], &primo, sizeof(int)) > 0) {  
			printf ("%d ", primo);  
		}
	
		// Cerramos el descriptor de lectura porque hemos terminado con este cauce
		close(fd1[0]);
		
		printf("\n");
	}
	
	
	// ---------------------------------------------------------------------------------------
	
	
	// Creaci�n, llamada y lectura con esclavo2
	if ( (PID2 = fork())<0) {
	
		perror("\nError en fork esclavo2");
		exit(EXIT_FAILURE);
		
	} else if (PID2 == 0) { // ESCLAVO2
		
		//Cerrar el descriptor de lectura de cauce en el proceso hijo
		close(fd2[0]);

		//Duplicar el descriptor de escritura en cauce en el descriptor
		//correspondiente a la salida estandr (stdout), cerrado previamente en
		//la misma operacion
		dup2(fd2[1],STDOUT_FILENO);
		
		sprintf(ini, "%d", c);
		sprintf(fin, "%d", d); //pasamos de entero a *char para poder pasar como argumentos a la funci�n esclavo
		
		// Llamamos por segunda vez vez al esclavo, que calcular� los primos del segundo intervalo
		if(execl("./esclavo", "esclavo", ini, fin, NULL) < 0) {
			perror("\nError en el execl esclavo2");
			exit(EXIT_FAILURE);
		}	
	}
	else { // Volvemos a trabajar con el proceso padre (MAESTRO) porque PID2>0
	
		//Cerrar el descriptor de escritura en cauce situado en el proceso padre
		close(fd2[1]);
		
		// Leemos el cauce (cada vez un entero)
		printf ("Primos calculados por el segundo esclavo: ");
		int primo;
		
		while (read(fd2[0], &primo, sizeof(int)) > 0) {  
			printf ("%d ", primo);  
		}
	
		// Cerramos el descriptor de lectura porque hemos terminado con este cauce
		close(fd2[0]);
		
		printf("\n");
	}

	return EXIT_SUCCESS;
	
}



