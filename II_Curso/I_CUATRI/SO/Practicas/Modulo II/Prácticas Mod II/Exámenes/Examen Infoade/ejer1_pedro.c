#include <dirent.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include <sys/mman.h>
#include <linux/sched.h>
#include <malloc.h>
#include<sched.h>
#include <ftw.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>

void funcion(int sig)
{
    printf("Se ha recibido Ctrl-C\n");
}

int main() {

    int childpid1 = 10;
    int fd5;

    if ((childpid1=fork())<0)
    {
        printf("Error en el primer fork, %d\n",errno);
        perror("Error en el primer fork");
        exit(-1);
    }

    struct passwd *passwd;

    uid_t uid;

    uid = getuid();

    passwd = getpwuid(uid);

    chdir(passwd->pw_dir);

    if (childpid1 == 0)
    {
        mkdir("examen",S_IRWXU);

        mkdir("examen/resultados",S_IRWXU);

        int fd1,fd2;

        if ((fd1=open("examen/cinco.txt",O_RDWR|O_CREAT, S_IRWXU))<0)
        {
            printf("Error creando cinco.txt, %d\n",errno);
            perror("Error creando cinco.txt");
            exit(-1);
        }

        if ((fd2=open("examen/diez.txt",O_RDWR|O_CREAT, S_IRWXU))<0)
        {
            printf("Error creando diez.txt, %d\n",errno);
            perror("Error creando diez.txt");
            exit(-1);
        }

        char buf[]="abcde";
        char buf1[]="0123456789";

        if (write(fd1,buf, strlen(buf))<0)
        {
            printf("Error escribiendo cinco.txt, %d\n",errno);
            perror("Error escribiendo cinco.txt");
            exit(-1);
        }

        if (write(fd2,buf1, strlen(buf1))<0)
        {
            printf("Error escribiendo diez.txt, %d\n",errno);
            perror("Error escribiendo diez.txt");
            exit(-1);
        }
    }
    else
    {
        int status;
        wait(&status);

        DIR *dir;

        if ((dir=opendir("examen"))<0)
        {
            printf("Error abriendo examen, %d\n",errno);
            perror("Error abriendo examen");
            exit(-1);
        }

        struct dirent *file;
        int cont = 0;

        if (mknod("padre_hijo.fifo",S_IFIFO|0666,0)<0)
        {
            printf("Error en mknod, %d\n",errno);
            perror("Error en mknod");
            exit(-1);
        }

        int childpid2 = 10;

        if ((childpid2=fork())<0)
        {
            printf("Error en el segundo fork, %d\n",errno);
            perror("Error en el segundo fork");
            exit(-1);
        }

        if (childpid2 == 0)
        {
            char buf4[80];

            int fd4;
            if ((fd4=open("padre_hijo.fifo",O_RDONLY))<0)
            {
                printf("Error abriendo el FIFO, %d\n",errno);
                perror("Error abriendo el FIFO");
                exit(-1);
            }

            if ((fd5=open("examen/resultados.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU))<0)
            {
                printf("Error abriendo el FIFO, %d\n",errno);
                perror("Error abriendo el FIFO");
                exit(-1);
            }

            do
            {
                if (read(fd4,buf4, 80)<0)
                {
                    printf("Error leyendo el FIFO, %d\n",errno);
                    perror("Error leyendo el FIFO");
                    exit(-1);
                }

                if (write(fd5,buf4, strlen(buf4))<0)
                {
                    printf("Error escribiendo en resultados.txt, %d\n",errno);
                    perror("Error escribiendo en resultados.txt");
                    exit(-1);
                }
            } while (strcmp(buf4," ")!=0);
        }
        else
        {
            struct stat atributos;

            int fd3;
            if ((fd3=open("padre_hijo.fifo",O_WRONLY))<0)
            {
                printf("Error abriendo el FIFO, %d\n",errno);
                perror("Error abriendo el FIFO");
                exit(-1);
            }

            while (1)
            {
                if ((file = readdir(dir)) == NULL)
                {
                    break;
                }

                char nombre[256];
                strcpy(nombre,"examen");
                strcat(nombre,"/");
                strcat(nombre,file->d_name);

                if (lstat(nombre,&atributos)<0)
                {
                    printf("Error en el primer lstat, %d\n",errno);
                    perror("Error en el primer lstat");
                    exit(-1);
                }

                char buf2[246];

                sprintf(buf2, "%d\n",atributos.st_ino);

                if (write(fd3,buf2, strlen(buf2))<0)
                {
                    printf("Error escribiendo en el FIFO, %d\n",errno);
                    perror("Error escribiendo en el FIFO");
                    exit(-1);
                }

                cont++;
            }

            if (write(fd3," ", strlen("fin"))<0)
            {
                printf("Error escribiendo en el FIFO, %d\n",errno);
                perror("Error escribiendo en el FIFO");
                exit(-1);
            }

            printf("El número de entradas del directorio examen es %d\n\n", cont);

            int childpid3 = 10;

            if ((childpid3=fork())<0)
            {
                printf("Error en el tercer fork, %d\n",errno);
                perror("Error en el tercer fork");
                exit(-1);
            }

            if (childpid3 == 0)
            {
                close(1);
                dup(fd5);

                if (execlp("ls","ls","-lai","examen",NULL)<0)
                {
                    printf("Error en el exec, %d\n",errno);
                    perror("Error en el exec");
                    exit(-1);
                }
            }
            else
            {
                struct sigaction sa;

                sa.sa_handler=funcion;
                sigemptyset(&sa.sa_mask);

                if (sigaction(SIGINT,&sa,0)<0)
                {
                    printf("Error en el sigaction %d\n",errno);
                    perror("Error en el sigaction");
                    exit(-1);
                }

                for (;;)
                {
                }

            }
        }
    }

    return 0;
}
