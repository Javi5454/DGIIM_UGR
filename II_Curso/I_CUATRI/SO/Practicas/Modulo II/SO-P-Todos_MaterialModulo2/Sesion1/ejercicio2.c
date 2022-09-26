/*
ejercicio2.c
Programa que acepta como argumento el nombre de un archivo, lo abre y 
lo lee en bloques de tamaño 80 bytes, y crea un nuevo archivo de 
salida.text en el que aparece la información siguiente

    Bloque 1
    // Aquí van los primeros 80 bytes del archivo pasado como argumento

    Bloque 2
    // Aquí van los siguientes 80 bytes del archivo pasado como argumento

    ...

    Bloque n 
    // Aquí van los siguientes 80 bytes del archivo pasaod como argumento
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    if (argc != 2){
        printf("Error numero de argumentos \n");
        exit (-1);
    }

    char* orig = argv[1];

    int fdin, fdout;

    if ( (fdin=open(orig, O_RDONLY, S_IRUSR))<0){
        printf("\nError %d en open", errno);
        perror("\nError en open");
        exit(-1);
    }

    int longitud = lseek(fdin,0,SEEK_END);
    lseek(fdin,0,SEEK_SET);

    fdout = open("salida.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR);
    
    char bloque[]="Bloque ";

    int iteraciones=longitud/80;

    if(iteraciones == 0){
        iteraciones++;
    }

    for (int i = 0; i < iteraciones; i++)
    {
        write(fdout,bloque,8);

        char bloq[2];
        bloq[0]=i+'1';
        bloq[1]=10;

        write(fdout,bloq,2);

        char buf[81] = {' '};

        if((read(fdin, buf, 80)) < 0){
            perror("\nError en read");
            exit(-1);
        }

        buf[80]=10;
        write(fdout,buf,81);

    }

    close(fdin);
    close(fdout);

    return 0;
    
}
