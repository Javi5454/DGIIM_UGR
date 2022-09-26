#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>
#define ISEXECUTABLE(mode)((mode & S_IXUSR) == S_IXUSR) 

int TAM;
char cadena[100];

void buscar_arch(DIR *direct, char pathname[]) {

	DIR *subdirect;
	char aux[100];
	struct dirent *ed;
	struct stat atributos;
	
	while((ed = readdir(direct)) != NULL){
		
		// Ignoramos los directorios . y ..
		
		if(strcmp(ed->d_name,".") && strcmp(ed->d_name,"..")){
			
			// En aux construimos la ruta del archivo del directorio 
			
			strcpy(aux,pathname);
			strcat(aux,"/");
			strcat(aux,ed->d_name);
			
			// En aux2 metemos los primeros TAM caracteres del nombre del archivo
			
			lstat(aux,&atributos);
			char aux2[300];
			strncpy(aux2,ed->d_name,TAM);
			
			// Comprobamos si es directorio y en ese caso, hacemos una llamada
			// recursiva
						
			if(S_ISDIR(atributos.st_mode)){
				subdirect = opendir(aux);
				buscar_arch(subdirect,aux);
			}
			
			// Comprobamos si es regular, si tiene permiso de ejecución para usuario
			// y si los primeros TAM caracteres coinciden con la cadena pasada como
			// argumento al main
			
			else if(S_ISREG(atributos.st_mode) && ISEXECUTABLE(atributos.st_mode)
			&& !strncmp(aux2,cadena,TAM)){
				char aux3[400];
				printf("Archivo: %s Ruta: %s\n",ed->d_name,aux);
				write(STDOUT_FILENO,aux3,strlen(aux3));
			}
	         }
        }
}

int main(int argc, char *argv[]){

	DIR *dir;
	dir = opendir(argv[2]);
	TAM = strlen(argv[1]);
	strcpy(cadena,argv[1]);
	
	buscar_arch(dir,argv[2]);
	
	return 0;
}
