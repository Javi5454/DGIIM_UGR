// Nombre del programa: pares_impares.c
// Nombre: Manuel Vicente Bolaños Quesada
// DNI: 77688712W
// 20/12/2021

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <string.h>



int main(int argc, char *argv[])
{
    // Correcto uso del programa
    if (argc != 2){
        printf("Numero incorrecto de parametros.\n");
        printf("Sintaxis: ./pares_impares <numero>\n");
        exit(-1);
    }

    int N = strtol(argv[1], NULL, 10);

    // los descriptores de archivo para los cauces
    int fd1[2];
    int fd2[2];

    // pids de los hijos a crear
    pid_t pid1;
    pid_t pid2;

    pipe(fd1); // Llamada al sistema para crear un cauce sin nombre
    pipe(fd2); // Llamada al sistema para crear un cauce sin nombre

    if ( (pid1 = fork()) < 0){ // creamos el primer hijo y comprobamos errores
        perror("Error en la creacion del primer hijo");
        exit(-1);
    }
    if ((pid1 != 0) && ((pid2 = fork()) < 0)){ // creamos el segundo hijo y comprobamos errores
        perror("Error en la creacion del segundo hijo");
        exit(-1);
    }

    if (pid1 != 0 && pid2 != 0){ // padre
        for (int i = 0; i <= N; i++){
            // si es par, escribimos en el primer cauce y comprobamos errores
            if (i % 2 == 0){
                if ( write(fd1[1], &i, sizeof(int)) < 0){
                    perror("Error al escribir en el primer cauce");
                    exit(-1);
                }
            } else{ // si es impar, escribimos en el segundo cauce y comprobamos errores
                if ( write(fd2[1], &i, sizeof(int)) < 0){
                    perror("Error al escribir en el segundo cauce");
                    exit(-1);
                }
            }
        }


        // escribimos -1 en ambos cauces
        int terminado = -1;
        if ( write(fd1[1], &terminado, sizeof(int)) < 0){
            perror("Error al escribir en el primer cauce");
            exit(-1);
        }

        if ( write(fd2[1], &terminado, sizeof(int)) < 0){
            perror("Error al escribir en el segundo cauce");
            exit(-1);
        }

        // cerramos los descriptores de escritura
        close(fd1[1]);
        close(fd2[1]);

        int suma_impar, suma_par;

        // esperamos a que el primer hijo termine y leemos la suma
        waitpid(pid1, NULL, 0);
        if (read(fd1[0], &suma_par, sizeof(int)) != sizeof(int)){
            perror("Error al leer del primer cauce");
            exit(-1);
        }

        // esperamos a que el segundo hijo termine y leemos la suma
        waitpid(pid2, NULL, 0);
        if (read(fd2[0], &suma_impar, sizeof(int)) != sizeof(int)){
            perror("Error al leer del segundo cauce");
            exit(-1);
        }

        // imprime por pantalla la suma
        printf("Suma impar: %d\n", suma_impar);
        printf("Suma par: %d\n", suma_par);

        // cerramos la lectura de los cauces
        close(fd1[0]);
        close(fd2[0]);
    }

    if (pid1 == 0){  // primer hijo
        int suma = 0;
        int num = 0;

        // leemos los numeros que hay en el cauce mientras que no sea -1
        while(num != -1){
            if (read(fd1[0], &num, sizeof(int)) != sizeof(int)){
                perror("Error al leer del primer cauce");
                exit(-1);
            }
            if (num != -1){
                suma+=num;
            }
        }

        close(fd1[0]); // cierra lectura del cauce1
        // escribimos la suma de los numeros leidos
        if ( write(fd1[1], &suma, sizeof(int)) != sizeof(int)){
            perror("Error al escribir en el primer cauce");
            exit(-1);
        }
        close(fd1[1]); // cierra escritura del cauce1
        exit(0);
    }

    if (pid2 == 0){  // segundo hijo
        int suma = 0;
        int num = 0;

        // leemos los numeros que hay en el cauce mientras que no sea -1
        while(num != -1){
            if (read(fd2[0], &num, sizeof(int)) != sizeof(int)){
                perror("Error al leer del segundo cauce");
                exit(-1);
            }
            if (num != -1){
                suma+=num;
            }
        }
        close(fd2[0]); // cierra lectura del cauce2
        // escribimos la suma de los numeros leidos
        if ( write(fd2[1], &suma, sizeof(int)) != sizeof(int)){
            perror("Error al escribir en el segundo cauce");
            exit(-1);
        }
        close(fd2[1]); // cierra escritura del cauce2
        exit(0);
    }


    return 0;
}