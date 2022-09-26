/*
Alumno: Javier Gómez López
Fecha: 26/12/2021
*/

#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void block_unblock(int order, int ulock){
    struct flock lock;

    //At first, we block the entire file
    lock.l_len = 0;
    lock.l_type = order;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;

    //If the process is alredy lock, it sleeps
    if(fcntl(ulock, F_SETLKW, &lock) == -1){
        perror("Proxy error: problems locking printing");
        exit(-1);
    }
}

int main(int argc, char *argv[]){
    char buff[1024];
    int nbytes, ulock;

    FILE *tmp = tmpfile();
    char fifoproxy[256];

    //Read 1024 bytes blocks and write it at a temporary file
    while((nbytes = read(STDIN_FILENO, buff, 1024)) > 0){
        //We use fwrite to avoid problems with FILE
        fwrite(buff, sizeof(char), nbytes, tmp);
    }

    //Open lock
    if ((ulock = open("blockfile",O_RDWR)) == -1){
        perror("Error opening blockfile\n");
        exit(-1);
    }

    //Locking the lock
    block_unblock(F_WRLCK, ulock);

    //Read temp file until end of file
    while(!feof(tmp)){
        fread(buff, sizeof(char),1024,tmp);

        //Write on screen
        write(STDOUT_FILENO, buff, 1024);
    }

    //Unlock the lock
    block_unblock(F_UNLCK, ulock);

    //Delete fifo before end
    sprintf(fifoproxy, "fifo.%d", getpid());
    unlink(fifoproxy);

    exit(0);
    
}