/*
    SOLEDAD RUIZ GÓMEZ 2ºDGIIM
    
    EXAMEN PRÁCTICAS SISTEMAS OPERATIVOS MÓDULO II

    20 DICIEMBRE 2021

    EJERCICIO 2

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
#define DEC 10

int main(int argc, char *argv[]) {

// COMPROBACIÓN DE ARGUMENTOS

    // Número de argumentos
    if (argc != 2) {
		perror ("\nNúmero de argumentos incorrecto\n\n");
		exit (EXIT_FAILURE);
	}

    // Ver que es entero positivo

    errno = 0; // para ver si ha habido error

    int N = strtol(argv[1], NULL, DEC);

    if (errno || N < 0) {
        perror("\nError: no es entero positivo\n\n");
        exit (EXIT_FAILURE);
    }

// EJECUCIÓN FUNCIONAL DEL PROGRAMA

// Creación de cauces

    int cauce1[2];  pipe (cauce1);
    int cauce2[2];  pipe (cauce2);

// Creación de los hijos consumidores

    pid_t PID1, PID2;

    if ((PID1 = fork())<0) {
		perror("fork primer hijo");
		exit(EXIT_FAILURE);
	
    } 
    
    if ((PID1 != 0) && ((PID2 = fork())<0)) {
        perror("fork primer hijo");
		exit(EXIT_FAILURE);

    }

    if (PID1 != 0 && PID2 != 0) { // padre productor - consumidor

        // Ahora que los consumidores están esperando a que algo se produzca, hacemos que el padre rellene el cauce

        // Pares al cauce 1
        for (int i=0; i<=N; i+=2) {
            
            if (write(cauce1[1],&i,sizeof(int)) != sizeof(int)) {	// escribe lo guardado en buf
                perror("\nError en escritura cauce1 padre\n");	
                exit(EXIT_FAILURE);
            }
        } 
        
        // Impares al cauce 2
        for (int i=1; i<=N; i+=2) {
            
            if (write(cauce2[1],&i,sizeof(int)) != sizeof(int)) {	// escribe lo guardado en buf
                perror("\nError en escritura cauce2 padre\n");	
                exit(EXIT_FAILURE);
            }
        } 

        // -1 para finalizar

        int fin = -1;

        if (write(cauce1[1],&fin,sizeof(int)) != sizeof(int)) {	// escribe -1
            perror("\nError en escritura fin cauce1 padre\n");	
            exit(EXIT_FAILURE);
        }

        if (write(cauce2[1],&fin,sizeof(int)) != sizeof(int)) {	// escribe -1
            perror("\nError en escritura fin cauce2 padre\n");	
            exit(EXIT_FAILURE);
        }
        
        close (cauce1[1]);
        close (cauce2[1]); // cerramos escrituras

    // Ahora ya hemos producido todos los datos, toca esperar a que los hijos cumplan su cometido y leer
    // del cauce el valor final que hayan calculado

    // Para asegurarnos de seguir un orden secuencial correcto, los esperamos
    // Mostramos los resultados:

        int resultado;

        // Hijo 1

        waitpid (PID1, NULL, 0);

        if (read (cauce1[0],&resultado,sizeof(int)) != sizeof(int) ) {
            printf("\nError %d en read cauce 1 padre\n",errno);
            perror("\nError en read\n");
            exit(EXIT_FAILURE);
        }

        printf ("\nLa suma de los pares hasta %d, calculada por el primer hijo, es %d\n", N, resultado);


        // Hijo 2

        waitpid (PID1, NULL, 0);

        if (read (cauce2[0],&resultado,sizeof(int)) != sizeof(int) ) {
            printf("\nError %d en read cauce 2 padre\n",errno);
            perror("\nError en read\n");
            exit(EXIT_FAILURE);
        }

        printf ("\nLa suma de los impares hasta %d, calculada por el segundo hijo, es %d\n", N, resultado);

    }
    
  
    
    
    if (PID1 == 0) { // primer hijo -> consumidor - productor

        int suma = 0;
        int num = 0;

        while (1) {

            // Leemos con comprobación de error

             if (read (cauce1[0],&num,sizeof(int)) != sizeof(int)) {
                printf("\nError %d en read hijo1\n",errno);
                perror("\nError en read\n");
                exit(EXIT_FAILURE);
            }

            if (num == -1)  break;          // si hemos llegado al final
            else            suma += num;    // si hemos leido un numero para sumar

        }

        close (cauce1[0]); //cerramos lectura

        if (write(cauce1[1],&suma,sizeof(int)) != sizeof(int)) {
            perror("\nError en escritura hijo1\n");	
            exit(EXIT_FAILURE);
        }

        close (cauce1[1]); // cerramos escritura

        exit (0);

	}



	if (PID2 == 0) {  // segundo hijo -> consumidor - productor

        int suma = 0;
        int num = 0;

        while (1) {

            // Leemos con comprobación de error

             if (read (cauce2[0],&num,sizeof(int)) != sizeof(int)) {
                printf("\nError %d en read hijo1\n",errno);
                perror("\nError en read\n");
                exit(EXIT_FAILURE);
            }

            if (num == -1)  break;          // si hemos llegado al final
            else            suma += num;    // si hemos leido un numero para sumar

        }

        close (cauce2[0]); //cerramos lectura

        if (write(cauce2[1],&suma,sizeof(int)) != sizeof(int)) {
            perror("\nError en escritura hijo1\n");	
            exit(EXIT_FAILURE);
        }

        close (cauce2[1]); // cerramos escritura

        exit (0);

	}

    exit (EXIT_SUCCESS);
}