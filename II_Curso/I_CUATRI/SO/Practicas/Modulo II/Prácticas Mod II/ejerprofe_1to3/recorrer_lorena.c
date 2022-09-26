// recorrer_lorena.c
// ejercicio profe hecho por lorena cáceres


#include<sys/types.h>	
#include<sys/wait.h>	
#include<dirent.h>
#include<unistd.h>		
#include<sys/stat.h>
#include<fcntl.h>		
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

/*

Ralizar un programa recorrer.c que reciba como único argumento una ruta a un directorio. De 
esta manera, la invocación se hará de la siguiente manera: 
./recorrer <ruta_directorio> 

Al  comenzar  deberá  mostrar  si  PID  y  el  PID  de  su  padre.  A  continuación  deberá  recorrer  las  entradas del directorio y para cada entrada de tipo directorio (que no sea . ni ..) deberá crear un hijo. Cuando haya recorrido todas las entradas, se quedará esperando a que terminen sus hijos. 
Para cada uno, indicará su PID y el valor que ha devuelto.
*/
int main(int argc, char *argv[]) {
	if(argc != 2){
		perror("\n Numero invalido de argumentos");
		exit(EXIT_FAILURE);
	}
	
	//Mostrar PID y PID del padre
	pid_t pid = getpid();
	printf("Mi PID es %d y el de mi padre es %d \n", pid, getppid());
	
	//Vamos a abrir el directorio
	printf("\n-Vamos a abrir el directorio\n");
	DIR * directorio;
	if ( (directorio = opendir(argv[1])) == NULL ){
    	    	printf("No se ha podido abrir el directorio");
		perror( "opendir");
   	     	exit(EXIT_FAILURE);
    	}
    	printf("\n-directorio abierto\n");
    	struct dirent * elemento_dir;
    	struct stat atributos;
    	
	//Empezamos a crear hijos
	printf("\n-Empezamos a crear hijos\n");
	int n_hijos=0;

	while ( (elemento_dir = readdir(directorio))!= NULL){

	
	//Miramos solo los directorios 
	if (strcmp(elemento_dir->d_name, ".")  != 0 &&  strcmp(elemento_dir->d_name, "..") != 0) { 
	
	        //Ruta de la forma elemento/directorio
	        char cadena[500];
            	strcpy(cadena, argv[1]);
            	strcat(cadena, "/");
            	strcat(cadena,elemento_dir->d_name);

            	// El nombre del archivo está contenido en cadena => comprobamos sus permisos
            	if ( stat(cadena, &atributos) < 0){
                	printf("No se ha podido comprobar los permisos");
                	exit (-1);
            	}
            	
            	if (S_ISDIR(atributos.st_mode)){
			if( (pid=fork())<0) {
				perror("\nError en el fork");
			exit(EXIT_FAILURE);
			}		
			
			if(pid == 0){
				int num_regs=0;
				int total_size=0;
				//Lo que tiene que hacer solo el hijo
			
				printf("Soy el hijo %d. Mi PID es %d y el de mi padre es %d \n",n_hijos, 						getpid(), getppid());
				printf("Estoy en el directorio  [%s]\n", cadena);
				
				
				struct dirent * elemento_dir_Sub;
    				struct stat atributos_Sub;
    				
    				DIR * directorio_Sub;
				if ( (directorio_Sub = opendir(cadena)) == NULL ){
			    	    	printf("No se ha podido abrir el directorio");
					perror( "opendir");
			   	     	exit(EXIT_FAILURE);
			    	}
				while ( (elemento_dir_Sub = readdir(directorio_Sub))!= NULL){
				
					char cadena_Sub[500];
			    		strcpy(cadena_Sub, cadena);
			    		strcat(cadena_Sub, "/");
			    		strcat(cadena_Sub,elemento_dir_Sub->d_name);
			    		
	    		            	if ( stat(cadena_Sub, &atributos_Sub) < 0){
                				printf("No se ha podido comprobar los permisos");
                				exit (-1);
            				}
            				if (S_ISREG(atributos_Sub.st_mode)){
            					
            					num_regs=num_regs+1;
            					total_size += (int) atributos_Sub.st_size;
            				}
				}
				printf("\n - \n HIJO %d: He encontrado %d archivos regulares que suman un tamaño de %d \n - \n ", n_hijos, num_regs, total_size);
				exit(0);
			}
			else
				n_hijos = n_hijos+1;
			}
	}
	
	}
	int estado;
	for(int i=n_hijos-1; i>=0; i--){ 
		pid = wait(&estado); 
		//Lo que va a hacer el padre
		printf("Ya han terminado mis hijos \n");
	}	

	exit(EXIT_SUCCESS);
}
