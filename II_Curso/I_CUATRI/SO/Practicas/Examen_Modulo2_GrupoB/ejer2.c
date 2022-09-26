#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){

    //Creamos los descriptores de los cauces sin nombre

    int fdE1[2];
    int fdE2[2]; 
    int finished = -1;

    int sum1, sum2;

    pid_t pid1, pid2;

    if (argc != 2){
        printf("Syntax error: ./ejer2 <number>\n");
        exit(-1);
    }

    int N = atoi(argv[1]);

    //Creamos los cauces

    pipe(fdE1);
    pipe(fdE2);

    if((pid1 = fork()) == 0){ //Hijo 1

        //Cerramos los descriptores de 2
        close(fdE2[0]);
        close(fdE2[1]);

        int current_num;
        int result = 0;

        do{
            read(fdE1[0],&current_num, sizeof(int));

            if (current_num != -1){
                result += current_num;
            }
        }while(current_num != -1);

        write(fdE1[1], &result, sizeof(int));

        exit(0);

    }
    else{

        int status;

        for (int i = 0; i <= N; i++){
            int buffer;

            if (i%2 == 0){
                buffer = i;
                write(fdE1[1], &buffer, sizeof(int));
            }
            else{
                write(fdE2[1], &i, sizeof(int));
            }
        }

        write(fdE1[1], &finished, sizeof(int));
        write(fdE2[1], &finished, sizeof(int));

        waitpid(pid1, &status, 0);
    
        read(fdE1[0], &sum1, sizeof(int));

        printf("Suma 1: %d\n", sum1);

    }

    

    return EXIT_SUCCESS;
}