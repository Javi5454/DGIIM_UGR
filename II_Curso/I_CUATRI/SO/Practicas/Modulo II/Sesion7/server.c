/*
Alumno: Javier Gómez López
Fecha: 26/12/2021
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CLIENTS 100
#define tam 1024
#define tam_name 50

//Signal Handler
static void signal_handler(int sigNum){
    pid_t pid;
    
    char fifoproxy[tam_name];

    //Catch child pid and delete asociated FIFO
    pid = wait(NULL);
}

int main(int argc, char *argv[]){
    int fdi, fdo, fdl, tmp_client;
    char fifo_i[tam_name];
    char fifo_o[tam_name];
    char fifoproxy[tam_name];
    int reads, proxypid;
    pid_t pid;

    //Arguments check
    if (argc != 2){
        printf("Syntax error: <fifo_name>\n");
        exit(-1);
    }

    //Signal Handler
    signal(SIGCHLD, signal_handler);

    //Create fifos name
    sprintf(fifo_i, "%si", argv[1]);
    sprintf(fifo_o, "%so", argv[1]);

    //Create FIFOs
    umask(0); //Set mask to 0 to avoid permission problems
    mkfifo(fifo_i, 0666);
    mkfifo(fifo_o, 0666);

    //Open FIFOs files
    if((fdi = open(fifo_i, O_RDWR)) < 0){
        perror("\nCannot open server FIFO");
        exit(-1);
    }

    if((fdo = open(fifo_o, O_RDWR)) < 0){
        perror("\nCannot open client FIFO");
        exit(-1);
    }

    //Create the lock file
    umask(0);

    if((fdl = open("blockfile", O_CREAT, 0666)) < 0){
        printf("Error creating lock file");
        exit(-1);
    }

    //We deploy process while we recive information from fifo client

    while ((reads = read(fdi, &tmp_client, sizeof(int))) != 0){
        pid = fork();

        if(pid == 0){ //Child process
            //PID of new process
            proxypid = getpid();

            //Create "proxy.getpid()";
            sprintf(fifoproxy, "fifo.%d", proxypid);

            umask(0);
            mkfifo(fifoproxy, 0666);

            //Write proxy's pid at fifo
            write(fdo, &proxypid, sizeof(int));

            //Open FIFO for read
            int fifo = open(fifoproxy, O_RDONLY);

            //Change standar input
            dup2(fifo, STDIN_FILENO);
            execlp("./proxy", "proxy", NULL);
            exit(0);
        }
    }

    exit(0);
    
}
