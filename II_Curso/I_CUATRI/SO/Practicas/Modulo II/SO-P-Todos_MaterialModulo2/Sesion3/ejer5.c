#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(){

    int status;
    pid_t PIDs[5];

    for (size_t i = 0; i < 5; i++)
    {
        if ((PIDs[i] = fork()) < 0){
            perror("\n Error en el fork");
            exit(-1);
        }
        else if (PIDs[i] == 0){
            printf("Soy el hijo PID = %d \n", getpid());
            exit(0);
        }
    }

    //Esperamos los hijos impares
    int hijos = 4;


    for (size_t i = 0; i < 5; i = i + 2){
        waitpid(PIDs[i], &status, 0);

        printf("Acaba de finalizar mi hijo con PID = %d y estado %d\n", PIDs[i], status);
        printf("Solo me quedan %d hijos vivos, este es el hijo numero %d\n", hijos--, i+1);
    }

    for (size_t i = 1; i < 5; i = i+2)
    {
        waitpid(PIDs[i], &status,0);

        printf("Acaba de finalizar mi hijo con PID = %d y estado %d\n", PIDs[i], status);
        printf("Solo me quedan %d hijos vivos, este es el hijo numero %d\n", hijos--, i+1);
    }

    exit(0);
}