// PEDRO HAIMAR CASTILLO GARCÍA


#include <dirent.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include <sys/mman.h>
#include <linux/sched.h>
#include <malloc.h>
#include<sched.h>

int main(int argc, char *argv[]) {

    if (argc != 2)
    {
        printf("Número invalido de argumentos\n");
        perror("Número invalido de argumentos");
        exit(-1);
    }

    pid_t pid,ppid;

    if ((pid=getpid())<0)
    {
        printf("Error en el getpid, %d\n",errno);
        perror("Error en el getpid");
        exit(-1);
    }

    printf("El PID del proceso es %d\n",pid);

    if ((ppid=getppid())<0)
    {
        printf("Error en el getppid, %d\n",errno);
        perror("Error en el getppid");
        exit(-1);
    }

    printf("El PID del padre del proceso es %d\n",ppid);

    DIR *dir;

    if ((dir=opendir(argv[1]))==NULL)
    {
        printf("Error en el opendir, %d\n",errno);
        perror("Error en el opendir");
        exit(-1);
    }

    struct dirent *file;
    struct stat atributos;
    int childpid = 12;
    int cont = 0;
    char nombre[500];

    while (1)
    {
        if ((file=readdir(dir))==NULL)
        {
            break;
        }

        if (strcmp(file->d_name, ".") && strcmp(file->d_name, "..")) {
            strcpy(nombre, argv[1]);
            strcat(nombre, "/");
            strcat(nombre, file->d_name);

            if (lstat(nombre, &atributos) < 0) {
                printf("Error en el lstat, %d\n", errno);
                perror("Error en el lstat");
                exit(-1);
            }

            if (S_ISDIR(atributos.st_mode)) {
                cont++;
                if ((childpid = fork()) < 0) {
                    printf("Error en el fork, %d\n", errno);
                    perror("Error en el fork");
                    exit(-1);
                }
            }

            if (childpid == 0)
                break;
        }
    }

    if (childpid != 0) {
        pid_t pidhijo;

        int retorno;

        for (int i = 0; i < cont; i++) {
            pidhijo = wait(&retorno);
            retorno >>= 8;
            printf("Acaba de terminar mi hijo con PID %d y su valor devuelto es %d\n", pidhijo, retorno);
        }

        return 0;
    }
    else
    {
        int suma = 0;
        int contador = 0;
        printf("Hola, soy el hijo con PID %d del padre con PID %d\n",getpid(),getppid());

        DIR *dir2;

        if ((dir2=opendir(nombre))==NULL)
        {
            printf("Error en el opendir, %d\n",errno);
            perror("Error en el opendir");
            exit(-1);
        }

        struct dirent *file2;
        struct stat atributos2;

        while (1)
        {
            if ((file2=readdir(dir2))==NULL)
            {
                break;
            }

            char path[500];
            strcpy(path,nombre);
            strcat(path,"/");
            strcat(path,file2->d_name);

            if (lstat(path,&atributos2)<0)
            {
                printf("Error en el lstat, %d\n",errno);
                perror("Error en el lstat");
                exit(-1);
            }

            if (S_ISREG(atributos2.st_mode))
            {
                contador++;
                suma += atributos2.st_size;
            }
        }

        printf("El directorio %s tiene una suma de tamaños de %d bytes\n",nombre,suma);

        return contador;
    }
}