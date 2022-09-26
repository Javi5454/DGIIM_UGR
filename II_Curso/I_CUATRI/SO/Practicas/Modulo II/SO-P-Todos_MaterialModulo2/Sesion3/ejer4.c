#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(){

    int status;
    pid_t pid;

    for (size_t i = 0; i < 5; i++)
    {
        if( (pid = fork()) < 0){
            perror("Error en el fork\n");
            exit(-1);
        }

        if(pid == 0){ //El hijo a muerto
            printf("Soy el hijo PID = %i \n", getpid());
            exit(0);
        }
    }

    //Esperamos los hijos

    for (size_t i = 0; i < 5; i++)
    {
        pid = wait(&status);

        printf("Ha finalizado mi hijo con PID = %i \n", pid);
        printf("Solo me quedan %i hijos vivos \n", 4 - i);
    }
    
    

    return 0;
}