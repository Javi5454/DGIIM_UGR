#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <pwd.h>
#define ARCHIVO_FIFO "padre_hijo.fifo"

static void myhandler(int signum){
   //Lo que tenga que manejar el handler
   	printf("\n !!Se ha pulsado cnrtl-C¡¡ \n");
   	exit(0); //Lo pongo por comodidad
}



int main(int argc, char * argv[]){


	/*-------------CAMBIO DE DIRECTORIO DE TRABAJO------------*/
	//Creo y lleno el uid con el usuario actual
	uid_t uid;
	uid = getuid();
	
	//creo y lleno la estructura pwd con los datos del usuario actual
	struct passwd *pwd;
	pwd = getpwuid(uid);
	
	//Con esos datos saco el home y cambio el directorio
	if(chdir(pwd->pw_dir) != 0){
		perror("chdir");
		exit(-1);
	}
	
	int pid;
	
	/*-------------LANZAMIENTO DE HIJOS------------*/	
	//vamos a lanzar un hijo
	
		/******HIJO 1: CREA LA ESTRUCUTRA DESEADA******/
	if( (pid=fork())<0) {
		perror("\nError en el fork");
	exit(EXIT_FAILURE);
	}		
	
	if(pid == 0){
	//creo el directorio examen
		if(mkdir("examen",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0){
			perror("mkdir");
			exit(-1);
		}
		if(mkdir("examen/resultados",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0){
			perror("mkdir");
			exit(-1);
		}

		int fd;

		//Creo el primer archivo 
		if( (fd=open("examen/resultados/cinco.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
			printf("\nError %d en open",errno);
			perror("\nError en open");
			exit(-1);
		}
		
		//y lo relleno con 5 letras
		
		char buf1[]="acbde";
		if(write(fd,buf1,5) != 5) {
			perror("\nError en primer write");
			exit(-1);
		}
		
		//Creo el segundo archivo
		close(fd);
		if((fd=open("examen/resultados/diez.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0)
		{
			perror("Error opening the input file");
			exit(-1);
		}
		
		//y lo relleno con 10 digitos
		char buf2[]="0123456789";
		if(write(fd,buf2,10) != 10) {
			perror("\nError en primer write");
			exit(-1);
		}
		
		
		exit(0);
	}
	
	wait(NULL);//Esperamos para que no nos de problemas al escribir resultados
	
	/*-------------MONTAR UN FIFO------------*/
	
		/******HIJO 2 y 3: CONSUMIDOR Y PRODUCTOR FIFO******/
	//HIJO CONSUMIDOR
	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(EXIT_FAILURE);
	}		
	if(pid == 0){

		int fd[2];
		char buffer[272];
		umask(0);
  		mknod(ARCHIVO_FIFO,S_IFIFO|0666,0);
  		
  		if((fd[0]=open(ARCHIVO_FIFO,O_RDWR)) <0){
		    perror("open");
		    exit(-1);
		}
		if( (fd[1]=open("examen/resultados.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
			printf("\nError %d en open",errno);
			perror("\nError en open");
			exit(-1);
		}

	  	while(1) {
	  		memset(buffer,0,strlen(buffer));
		    	read(fd[0],buffer,272);
		    	printf("\nMensaje recibido: %s\n", buffer);
		    	if(strcmp(buffer,"fin")==0) {
		      		close(fd[0]);
      				exit(0);

		    	}
			char mensaje[300];
			sprintf(mensaje,"\nMensaje recibido: %s\n", buffer);
			
		 	if( (write(fd[1],mensaje,strlen(mensaje))) !=strlen(mensaje)) {
				perror("\nError al escribir en el resultado");
				exit(-1);
			}	
		}
		exit(0);
	}
	
	//HIJO PRODUCTOR
	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(EXIT_FAILURE);
	}		
	
	
	if(pid == 0){
		int fd;
		//Abrir el cauce para lectura-escritura
		//Intentar abrir para escritura el cauce FIFO
		if( (fd=open(ARCHIVO_FIFO,O_WRONLY)) <0) {
			perror("\nError en open");
			exit(-1);
		}

		/*-------------RECORRER EXAMEN------------*/	


		//Lo que va a hacer el padre
		
		int total=0;
		DIR * directorio = opendir("examen");
		struct dirent * elemento_dir;

		//Lo recorremos hasta que no queden elementos
		while ( (elemento_dir = readdir(directorio)) != NULL){
			//Escribo en el fifo
			char mensaje[272];
			sprintf(mensaje, "-%s: %ld \n",elemento_dir->d_name,elemento_dir->d_ino);
			
			if( (write(fd,mensaje,strlen(mensaje)+1)) !=strlen(mensaje)+1) {
				perror("\nError al escribir en el FIFO");
				exit(-1);
			}
			total+=1;
		}
		printf("\n------\n En examen hay %d elementos \n------\n", total);
		
		sleep(1);//Para evitar problemas
		
		if( (write(fd,"fin",4)) != 4) {
			perror("\nError al escribir en el FIFO");
			exit(-1);
		}
		printf("\n------\n escrito la cadena \n------\n");
		close(fd);
		exit(0);
	}
	
	
	wait(NULL); //Esperamos para que no nos de problemas al escribir en resultados
	wait(NULL);
	
	/*-------------HACER LS-LAI------------*/	
		/******HIJO 3: AÑADIR LS-LAI A RESULTADOS******/	
	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(EXIT_FAILURE);
	}		
	
	
	if(pid == 0){
		printf("listo para escribir en resultados\n");
		int fd1 = open ("examen/resultados.txt", O_WRONLY|O_APPEND);
		close(1);
		
		if (fcntl(fd1, F_DUPFD, 1) == -1) 
			perror ("Fallo en fcntl");	
				
		system("ls examen -lai"); 
		exit(0);
	
	}
	
	
	// Esperas 
	wait(NULL); //A su útlimo hijo
	
		/*-------------MANEJAR LA SEÑAL CNTRL C------------*/	
	//PARA EL MANEJADOR:
	struct sigaction sa;
	sa.sa_handler = myhandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	
	if (sigaction(SIGINT, &sa, NULL) == -1){
		printf("error en el manejador");
	}

	
	while(1);	//Para siempre T.T
	
	exit(EXIT_SUCCESS);
}
