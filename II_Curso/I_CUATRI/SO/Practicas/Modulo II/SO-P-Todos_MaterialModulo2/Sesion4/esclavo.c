#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

int esPrimo(int num){

    for (int i = 3; i <= num/2; i++)
    {
        if(num % i == 0){
            return 0;
        }
    }

    return 1;
    
}

int main(int argc, char *argv[]){
    int min, max;

    read(STDIN_FILENO, &min, sizeof(int));
    read(STDIN_FILENO, &max, sizeof(int));

    for(int i = min; i <= max; i++){
        if(esPrimo(i)){
            write(STDOUT_FILENO, &i, sizeof(int));
        }
    }

    return EXIT_SUCCESS;
}