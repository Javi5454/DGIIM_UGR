#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>

char *dest_path;

int ProcesarArchivo(const char *file_path, const struct stat *statbuf, int typeflag) {
    char buff[1024];
    if (statbuf->st_size >= 1024 && S_ISREG(statbuf->st_mode)) {
        int pid = fork();
        if (pid == 0) {
            execlp("cp", "cp", file_path, dest_path, NULL);
            exit(0);
        }
        mode_t mask = S_IRWXU | S_IRWXG | S_IRWXO;
        printf("%s|%o|%li\n", file_path, (statbuf->st_mode & mask), statbuf->st_ino);
    }
    return 0;
}

int main(int argc, char **argv) {
    dest_path = argv[2];
    mkdir(argv[2],S_IRWXU | S_IRWXG | S_IRWXO);
    ftw(argv[1], ProcesarArchivo, 0);
}