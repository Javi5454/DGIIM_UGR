/*
Ejercicio: deep
Nombre: Javier Gómez López
DNI: 03949965Z
Fecha: 21/12/2021
*/

#include <sys/types.h>	
#include <sys/stat.h>	
#include <sys/wait.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>

//Funcion recursiva para recorrer directorios como el ejercicio nos pide
int directory(char *dir, int deepth){

    //Abrimos el directorio pasado como argumento
    DIR *directorio;
    if((directorio = opendir(dir)) == NULL){
        perror("Error en opendir");
        exit(-1);
    }

    //Pasamos a recorrer el directorio

    struct dirent *file; //Archivo leido
    struct stat metadata; //Metadatos del archivo

    char path[255];

    errno = 0; //Para ver si ha habido error al recorrer el directorio

    while((file = readdir(directorio)) != NULL){
        //Arriba hemos leido el archivo que toque y comprobado que no es NULL

        //Necesitamos la ruta en un formato adecuado
        strcpy(path, dir);
        strcat(path, "/");
        strcat(path, file->d_name);

        int counter = 0;

        for (size_t i = 0; i < sizeof(path); i++)
        {
            if(path[i] == '/'){
                counter++;
            }
        }

        deepth = counter;
        


        //Conseguimos los metadatos de file
        if(stat(path, &metadata) < 0){
            perror("Error en stat");
            exit(-1);
        }

        //Comprobamos si es directorio y si el grupo tiene permiso para leer
        if(S_ISDIR(metadata.st_mode) && strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0){
            printf("Directorio %s cumple los requisitos en la profundidad %d\n", path, deepth);
            deepth = directory(path, deepth);
        }
    }

    return deepth;

}

int main(int argc, char *argv[]){

    //Comprobamos los argumentos
    if(argc != 2){
        printf("Error argumentos: ./deep <ruta directorio>\n");
        exit(-1);
    }

    //Vemos que el segundo arg es un directorio

    struct stat atridir;

    if(lstat(argv[1], &atridir) < 0){
        printf("\nError al intentar acceder a los atributos de %s\n\n", argv[1]);
        perror("\nError en lstat\n");
        exit(-1);
    }

    if(!S_ISDIR(atridir.st_mode)){
        printf("Introduzca un directorio valido como primer argumento\n");
        exit(-1);
    }

    

    int deepth = 0;
    char *path = argv[1];  

    deepth = directory(path, deepth);

    printf("\nMayor profundidad es: %d ",deepth);
}