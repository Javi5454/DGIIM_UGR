#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    char buffer[32][64];
    long int inodos[32];
    int n_buffer = 0;
    int estado;
    for (; n_buffer < 32; n_buffer++) {
        scanf("%s", buffer[n_buffer]);
        if (strcmp("fin", buffer[n_buffer]) == 0) {
            break;
        }
    }

    for (int i = 0; i < n_buffer; i++) {
        int fd;
        if (fd = open(buffer[i], O_CREAT | O_APPEND | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO) < 0) {
            perror("ERROR open() inicial");
            exit(-1);
        }
        close(fd);
    }

    int cauce1[2];
    int cauce2[2];
    if (pipe(cauce1) == 0 && pipe(cauce2) == 0) {

        int pid = fork();

        if (pid == 0) {
            for (int i = 0; i < n_buffer; i++) {
                char buffer_hijo[64] = "";
                int message = read(cauce1[0], buffer_hijo, 64);
                if (message == 0) {
                    printf("Cauce vacio");
                    exit(-1);
                } else if (message < 0) {
                    perror("ERROR read()");
                    exit(-1);
                }
                struct stat atributos;
                lstat(buffer_hijo, &atributos);
                if (atributos.st_ino % 2) {
                    printf("Soy el hijo 1 y el inodo %li es impar\n", atributos.st_ino);
                } else {
                    printf("Soy el hijo 1 y el inodo %li es par\n", atributos.st_ino);
                }
            }
            exit(0);
        } else {
            for (int i = 0; i < n_buffer; i++) {
                if (write(cauce1[1], buffer[i], 64) < 0) {
                    perror("ERROR write()");
                    exit(-1);
                }
            }
        }

        pid = fork();

        if(pid == 0) {
            for (int i = 0; i < n_buffer; i++) {
                char buffer_hijo[64] = "";
                int message = read(cauce2[0], buffer_hijo, 64);
                if (message == 0) {
                    printf("Cauce vacio");
                    exit(-1);
                } else if (message < 0) {
                    perror("ERROR read()");
                    exit(-1);
                }
                umask(0);
                if (chmod(buffer_hijo, (S_IRWXU | S_IRWXG | S_IRWXO) & ~S_IXUSR & ~S_IXGRP & ~S_IXOTH) < 0){
                    perror("ERROR chmod()");
                }
            }
            exit(0);
        } else {
            for (int i = 0; i < n_buffer; i++) {
                if (write(cauce2[1], buffer[i], 64) < 0) {
                    perror("ERROR write()");
                    exit(-1);
                }
            }
        }

    } else {
        perror("ERROR pipe()"); 
    }
}