#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){
    // Declaramos las variables para ambos intervalos

    int minA, minB;
    int maxA, maxB;

    int fdE1[2], fdE2[2], fdM[2];

    pid_t pid1, pid2;

    int valor;

    if (argc != 3){
        printf("Syntax error: ./ejer5 <a> <b>\n");
        exit(-1);
    }

    minA = atoi(argv[1]);
    maxB = atoi(argv[2]);

    //Creamos los cauces sin nombre

    pipe(fdE1);
    pipe(fdE2);
    pipe(fdM);

    if ((pid1 = fork()) == 0){ //hijo 1
        //Cerramos los descriptores del eslcavo 2
        close(fdE2[0]);
        close(fdE2[1]);

        //Cerramos el resto de descriptores que no necesitmaos
        close(fdE1[1]);
        close(fdM[0]);

        //Esclavo 1 --> Maestro
        dup2(fdE1[0], STDIN_FILENO);
        dup2(fdM[1], STDOUT_FILENO);

        execl("./esclavo", "esclavo", NULL);
    }
    else if ( (pid2 = fork()) == 0){ //hijo 2
        //Cerramos los descriptores del escalvo 1 
        close(fdE1[0]);
        close(fdE2[1]);

        //Cerramos los descriptores que no necesitemos
        close(fdE2[1]);
        close(fdM[0]);

        //Esclavo 2 --> Maestro

        dup2(fdE2[0], STDIN_FILENO);
        dup2(fdM[1], STDOUT_FILENO);

        execl("./esclavo", "esclavo", NULL);
    }
    else{ //Padre
        close(fdE1[0]);
        close(fdE2[0]);

        //Calculamos el intervalo

        maxA = (minA + maxB) / 2;
        minB = maxA + 1;

        //Escrivmos en el esclavo1
        write(fdE1[1], &minA, sizeof(int));
        write(fdE1[1], &maxA, sizeof(int));

        //Escribimos en el esclavo2
        write(fdE2[1], &minB, sizeof(int));
        write(fdE2[1], &maxB, sizeof(int));

        while ((read(fdM[0], &valor, sizeof(int))) != 0)
        {
            printf("%d\n", valor);
        }
        

    }

    exit(0);
}