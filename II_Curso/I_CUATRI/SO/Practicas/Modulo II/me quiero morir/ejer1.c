#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

void buscar(char *pathname, char *name){
    DIR *dir;

    if((dir = opendir(pathname)) == NULL){
        perror("Error al abrir el directorio de la polla");
        exit(-1);
    }

    struct dirent *current_file;
    struct stat atrib;

    while((current_file = readdir(dir)) != NULL){
        lstat(current_file->d_name, &atrib);

        if((strcmp(current_file->d_name, ".") != 0) && (strcmp(current_file->d_name, "..")) != 0){
            if(!S_ISREG(atrib.st_mode) && (atrib.st_mode & S_IXUSR) == S_IXUSR){
                if(strcmp())
            }
        }
    }
}

int main(int argc, char *argv[]){
    
    if(argc != 3){
        printf("Syntax error");
        exit(-1);
    }

    struct stat atributos;

    if(lstat(argv[1], &atributos) < 0){
        perror("Error atributos");
        exit(-1);
    }

    if(!S_ISDIR(atributos.st_mode)){
        printf("Syntax error: no introdujiste un directorio subnormal");
        exit(-1);
    }

    
    exit(0);
}