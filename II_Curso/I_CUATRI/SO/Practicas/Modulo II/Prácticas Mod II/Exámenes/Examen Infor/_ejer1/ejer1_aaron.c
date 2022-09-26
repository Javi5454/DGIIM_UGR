#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

#define _XOPEN_SOURCE 500
#include<ftw.h>

const int TAM = 50;
int bloques, depth, fd;
int profundidad = 0;

struct FTW {
	int base;
	int level;
};

	
int escribir(const char * pathname, const struct stat *atrib, int flags, struct FTW *ftw) {
	if (ftw->level <= depth) {
		if (atrib->st_blocks > bloques) {
			write(fd, pathname, strlen(pathname));
			write(fd, "\n", 1);
		}
	}
	
	return 0;
}

int main (int argc, char *argv[]) {

	char destino[TAM], pathname[TAM];;
	sprintf(pathname,"%s",argv[1]);
	bloques = atoi(argv[2]);
	depth = atoi(argv[3]);
	sprintf(destino,"%s/%s",argv[4],"salida.txt");
	
	if ((fd=open(destino, O_CREAT | O_TRUNC | O_RDWR, 0777)) < 0) {
		printf("error en open\n");
		exit(-1);
	}
	
	if (nftw(pathname,escribir,depth,0)<0) {
		printf("nftw\n");
		exit(-1);
	}
	
	return EXIT_SUCCESS;
}
