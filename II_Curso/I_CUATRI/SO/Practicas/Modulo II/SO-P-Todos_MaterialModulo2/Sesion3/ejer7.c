#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    pid_t pid;
    int status;

    if (argc < 2){
        printf("Syntax error\n");
        exit(-1);
    }

    if( (pid = fork()) < 0){
        perror("Error en el fork");
        exit(-1);
    }

    if (pid == 0){ //Proceso hijo
        if (execle(argv[1], "ejer5", NULL, "foreground") < 0){
            perror("Error en el execl");
            exit(-1);
        } 
    }

    wait(&status);

    printf("\nMi hijo %d ha finalizado con el estado %d\n", pid, status);

    exit(0);
}
