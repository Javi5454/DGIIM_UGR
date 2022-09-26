/*
ejercicio2.c

Program that modifies the permissions of all archives in a given
directory
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>

int main (int argc, char *argv[]){

    struct dirent *pDirent;
    DIR *pDir;
    char* endPtr;

    // Ensure correct argument count
    if(argc != 3){
        printf("Error numero de argumentos \n");
        exit(-1);
    }

    // Set orig pathname and octal permission
    char *orig = argv[1];
    int permission = strtol(argv[2], &endPtr, 10);

    if((pDir = opendir(orig)) == NULL){
        printf("Error %d en opendir(pathname)\n", errno);
        perror("\nError en opendir");
        exit(-1);
    }

    // Process each entry

    while ((pDirent = readdir(pDir)) != NULL){
        struct stat *statbuf;

        stat(pDirent->d_name, statbuf);
        int mod = (int)statbuf->st_mode;
        printf ("%s:  ", pDirent->d_name);
        printf("%d\n", mod);
    }

    // Close directory and finish

    closedir(pDir);

     
    return 0;
}