/*
Ejercicio: deep
Nombre: Javier Gómez López
DNI: 03949965Z
Fecha: 21/12/2021
*/

#include <stdlib.h>     //Incluimos todas las librerias necesarias
#include <unistd.h>    
#include <stdio.h>     
#include <sys/types.h>  
#include <sys/stat.h>   
#include <sys/wait.h>   
#include <dirent.h>     
#include <ftw.h>        
#include <string.h>     
#include <fcntl.h>      
#include <signal.h>     
#include <sys/file.h>   
#include <sys/mman.h>  

int main(int argc, char *argv[]){

    int fd; //Descriptor de archivo para el cauce

    //COMPROBACION DE ARGUMENTOS

    if (argc != 2){
        printf("Error argumentos: ./divisor <N>\n");
        exit(-1);
    }

    int N = atoi(argv[1]); //Tomamos el valor N introducido

    //Creamos el cauce con nombre
    umask(0);
    mkfifo("cauce_divisor",0666);

    //Abrimos el cauce para lectura-escritura con comprobacion de errores
    if ((fd = open("cauce_divisor",O_RDWR)) < 0){
        perror("open");
        exit(-1);
    }

    //Creamos el PID del hijo
    pid_t pid;

    //Iniciamos el proceso hijo y especificamos su funcionalidad.
    //Además, también especificamos el funcionamiento del padre

    if((pid = fork()) == 0){ //Proceso hijo

        int current_number; //Numero actual del cauce
        int total = 0; //Numero total de divisores

        do{
            if(read(fd,&current_number, sizeof(int)) < 0){ //Comprobamos la lectura del cauce
                perror("Error lectura hijo");
                exit(-1);
            }

            if (current_number != -1){ //Si no es -1 comprobamos sus divisores
                if(current_number % 2 == 0){
                    total = total + 1;
                }

                if(current_number % 3 == 0){
                    total = total + 1;
                }

                if(current_number % 5 == 0){
                    total = total + 1;
                }

                if(current_number % 7 == 0){
                    total = total + 1;
                }

                if(current_number % 11 == 0){
                    total = total + 1;
                }

                if(current_number % 13 == 0){
                    total = total + 1;
                }

                if(current_number % 21 == 0){
                    total = total + 1;
                }

                if(write(fd, &total, sizeof(int)) < 0){ //Escribimos el numero total de divisores
                    perror("Error escritura hijo");
                }

                total = 0; //Reseteamos el contador
            }
        }while(current_number != -1);

        close(fd);

    }
    else{ //Padre

        int finisher = -1; //Valor para terminar el bucle del hijo
        int status; //Variable donde guardar el estado de finalizacion del proceso hijo

        for (int i = 1; i <= N; i++)
        {
            if(write(fd, &i, sizeof(int)) < 0){ //Escribimos los valores a comprobar
                perror("Error escritura padre");
                exit(-1);
            }
        }

        if(write(fd, &finisher, sizeof(int)) < 0){
            perror("Error escritura finisher padre");
            exit(-1);
        }
        
        waitpid(pid, &status, 0); //Esperamos a que el hijo termine correctamente

        int max_divisors = 0; //Variable donde almacenaramos el resultado
        int to_check, max_number = 0; //Variable donde guardamos los resultados a comprobar

        for (int i = 1; i <= N; i++) //Leemos los posibles resultados con comprobacion de errores
        {
            if (read(fd, &to_check, sizeof(int)) < 0){
                perror("Error lectura de posibles resultados"); 
                exit(-1);
            }

            if (to_check > max_divisors){ //Checkeamos si el posible resultado es mayor que el ya existente
                max_divisors = to_check;
                max_number = i;
            }
        }

        close(fd);

        printf("El numero %d es el que mas divisores tiene con un total de %d\n", max_number, max_divisors);

        //Deleteamos el cauce con nombre
        unlink("cauce_divisor");
    }

    exit(0);


}