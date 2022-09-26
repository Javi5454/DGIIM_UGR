#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

int TAM;
char buffer[100];

void find_archive (DIR *direct, char pathname[]){
    DIR *subdirect;
    char aux_buffer[100];

    struct dirent *ed;
    struct stat stats;

    while ( (ed = readdir(direct)) != NULL){
        //Ignore . and ..

        if (strcmp(ed->d_name,".") && strcmp(ed->d_name, "..")){
            strcpy(aux_buffer, pathname);
            strcat(aux_buffer, "/");
            strcat(aux_buffer, ed->d_name);


            // En aux2 metemeos los primeros TAM caracteres del nombre
            // del archivo
            lstat(aux_buffer, &stats);
            char aux2[300];
            strncpy(aux2, ed->d_name, TAM);

            if(S_ISDIR(stats.st_mode)){
                subdirect = opendir(aux_buffer);
                find_archive(subdirect, aux_buffer);
            }

            //Comprobamos que es regular, que tiene permisos de ejecucion
            //y si los primeros TAM caracteres coinciden

            else if(S_ISREG(stats.st_mode) && (stats.st_mode & S_IXUSR) == S_IXUSR &&
            !strncmp(aux2, buffer, TAM)){
                char aux3[400];

                printf("Archivo: %s \t Ruta: %s\n", ed->d_name, aux_buffer);
                write(STDOUT_FILENO, aux3, strlen(aux3));
            }



        }
    }
}

int main(int argc, char *argv[]){
    DIR *dir;
    dir = opendir(argv[2]);
    TAM = strlen(argv[1]);

    strcpy(buffer, argv[1]);

    return EXIT_SUCCESS;
}