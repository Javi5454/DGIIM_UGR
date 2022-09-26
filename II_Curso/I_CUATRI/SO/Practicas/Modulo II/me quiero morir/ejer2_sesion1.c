#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Syntax error\n");
        exit(EXIT_FAILURE);
    }

    int fd1, fd2;

    if((fd1 = open(argv[1], O_RDONLY, S_IRUSR | S_IXUSR)) < 0){
        perror("Error en open");
        exit(EXIT_FAILURE);
    }

    if((fd2 = open("salida.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU))<0){
        perror("Error en open");
        exit(EXIT_FAILURE);
    }

    char bloque[] = "Bloque ";
    char salto[] = "\n";

    char contador [] = '1';

    char buffer[80];

    while(read(fd1, buffer, 80) != 0){
        write(fd2, bloque, sizeof(bloque));
        write(fd2, &contador, sizeof(int));
        contador = contador + 1;

        write(fd2, salto, sizeof(salto));

        write(fd2, buffer, sizeof(buffer));
        write(fd2, salto, sizeof(salto));

        
    }

    exit(EXIT_SUCCESS);
}