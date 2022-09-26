#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char * argv[]){

    if (argc != 2){
        perror("\nError parametros: <ejer1> <numero a comprobar>");
        exit(-1);
    }

    pid_t pid;

    pid = fork();

    if (pid < 0){
        perror("\nError en el fork");
        exit(-1);
    }
    

    if (pid == 0){ //Proceso hijo
        printf("Soy el proceso hijo, mi pid es: %d y el de mi padre es %d \n", getpid(), getppid());

        int num = atoi(argv[1]);

        if (num % 2 == 1){
            printf("El numero %d es impar \n", num);
        }
        else{
            printf("El numero %d es par \n", num);
        }
    }
    else{
        printf("Soy el proceso padre, mi pid es %d y el de mi hijo es %d \n", getpid(), pid);

        int num = atoi(argv[1]);

        if(num % 4 == 0){
            printf("El numero %d es divisible entre 4 \n", num);
        }
        else{
            printf("El numero %d no es divisible entre 4 \n", num);
        }
    }


    return 0;
}