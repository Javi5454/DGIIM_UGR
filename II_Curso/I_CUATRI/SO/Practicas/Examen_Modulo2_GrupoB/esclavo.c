#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){
    int result = 10;
    int current_num;

    do{
        read(STDIN_FILENO, &current_num, sizeof(int));
        
        if(current_num != -1){
            result += current_num;
        }

    }while(current_num != -1);

    write(STDOUT_FILENO, &result, sizeof(int));

    return EXIT_SUCCESS;
}