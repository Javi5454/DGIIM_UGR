#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

const int BYTES_EN_KB = 1024;
int tam = 0; //EN bytes

void copiar(DIR *dir, char *camino, DIR *otro_dir, char * otro_camino); //Se pasa los punt a los dir y pathnames

int main(int argc, char *argv[]){

    DIR *dir; //puntero a directorio original
    DIR *otro_dir;
    
    if (argc != 3){
        printf("Número de argumentos erroneo, introduzca 3\n");
    }
    else{
        dir = opendir(argv[1]); //puntero a directorio
        if(dir == NULL){
            printf("Error al abrir el directorio pasado como primer parámetro\n");
        }
        
        otro_dir = opendir(argv[2]); //puntero al otro directorio

        if(otro_dir == NULL){
            mkdir(argv[2], 777);
            otro_dir = opendir(argv[2]);
        }

        copiar(dir, argv[1], otro_dir, argv[2]);
        
        int fd;
        if( (fd=open("copiado.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP)) <0){
            printf("\nError %d en open de copiados.txt\n",errno);
            perror("\nError en open\n");
            exit(EXIT_FAILURE);
        }

        char cadena_copiados[64];
        
        sprintf(cadena_copiados, "Tamaño total: %d\n" ,tam);
        write(fd, cadena_copiados, sizeof(cadena_copiados));
        closedir(dir); //Cerramos el directorio
        closedir(otro_dir); //Cerramos el directorio
    }
}

void copiar(DIR *dir, char *camino, DIR *otro_dir, char * otro_camino){
    struct dirent *entrada; //Devuelve la entrada a través de un puntero a la estructura dirent
    struct stat atributos; //Los metadatos de un archivo
    char pathname[512]; //Para guardar una cadena
    DIR *subdir; //puntero a sub-directorio de dir
    
    char cadena_copiados[512];
    int fd;
    
    if( (fd=open("copiado.txt",O_CREAT|O_TRUNC|O_WRONLY,777)<0) ){
        printf("\nError %d en open de copiados.txt\n",errno);
        perror("\nError en open\n");
        exit(EXIT_FAILURE);
    }

    while((entrada = readdir(dir)) != 0){ //Lee donde esta el puntero dir.
        if (strcmp(entrada->d_name, ".") && strcmp(entrada->d_name, "..")){     //Comprobamos si no son los ficheros . y ..
            sprintf(pathname, "%s/%s", camino, entrada->d_name);    //Guarda en pathname el string. LA ruta
            lstat(pathname, &atributos);    // stat examina el fichero al que apunta pathname y llena buf. lstat con enlace simbólico lo examina 
            if (S_ISREG(atributos.st_mode) && (atributos.st_size >= BYTES_EN_KB)){  //Archivo regular y que el tamaño sea mayor a 1KB
                sprintf(cadena_copiados, "%s|%i|%li",entrada->d_name,atributos.st_mode, atributos.st_ino);
                write(fd, cadena_copiados, sizeof(cadena_copiados));
                tam += atributos.st_size; //Aumentamos
                execlp("cp",pathname,otro_camino,NULL); //Copiar
            }

            else if (S_ISDIR(atributos.st_mode)){ //SI es un directorio
                subdir = opendir(pathname);     //Repetimos el proceso anterior(recursiva)
                copiar(subdir, pathname, otro_dir, otro_camino);    //Buscamos en el subdirectorio
                closedir(subdir); //Cerramos el directorio
            }
        }
    }

    close(fd);

}