/*
    SOLEDAD RUIZ GÓMEZ 2ºDGIIM
    
    EXAMEN PRÁCTICAS SISTEMAS OPERATIVOS MÓDULO II

    INFORMÁTICA + ADE CURSO 2020/2021

    EJERCICIO 1 (10 puntos)

*/

#include <sys/types.h>	
#include <sys/stat.h>	
#include <sys/wait.h>
#include <sys/mman.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>

#define TAM 300
#define ARCHIVO_FIFO "padre_hijo.fifo"

// Función handler
static void hdlr (int sig) {

    if(sig == SIGINT)
	    printf("\nSe ha recibido ctrl-C\n\n");

}


int main(int argc, char *argv[]) {

// No se reciben argumentos


// EJECUCIÓN FUNCIONAL DEL PROGRAMA

// Cambio de directorio de trabajo (es algo que van a usar todos los hijos)

    // Usuario actual
    uid_t uid = getuid();

    // Password
    struct passwd * password = getpwuid (uid);

    // Cambio al directorio home del user
    if (chdir(password->pw_dir) == -1) {
        printf ("\nError con errno %d", errno);
        perror("\nError al cambiar de directorio\n");
        exit(EXIT_FAILURE);
    }


// Creación del primer hijo con fork -----------------------------------------------------------------------------------------------------------

    pid_t PID1;

    if ((PID1 = fork()) < 0) { // si hay error al crearlo

        perror("\nError en fork del primer hijo");
        exit(EXIT_FAILURE); 

    } else if (PID1 == 0) {  // estamos en el hijo

        // Creamos el directorio examen
        if (mkdir("examen", S_IRWXU|S_IRGRP|S_IRWXO) == -1) {
            printf ("\nError con errno %d", errno);
            perror("\nError al crear el directorio examen\n");
            exit(EXIT_FAILURE);
        }

        // Creamos el directorio examen/resultados
        if (mkdir("examen/resultados", S_IRWXU|S_IRGRP|S_IRWXO) == -1) {
            printf ("\nError con errno %d", errno);
            perror("\nError al crear el directorio examen/resultados\n");
            exit(EXIT_FAILURE);
        }

        // Creamos los archivos .txt
        int fd5, fd10;

        if ((fd5=open("examen/cinco.txt",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU|S_IRGRP|S_IRWXO))<0) {	// archivo lectura y escritura (lo creamos si no existe y borramos su contenido si ya existe)
            printf("\nError %d en open file examen/cinco.txt\n",errno);
            perror("\nError en open\n");
            exit(EXIT_FAILURE);
        }

        if ((fd10=open("examen/diez.txt",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU|S_IRGRP|S_IRWXO))<0) {	// archivo lectura y escritura (lo creamos si no existe y borramos su contenido si ya existe)
            printf("\nError %d en open file examen/diez.txt\n",errno);
            perror("\nError en open\n");
            exit(EXIT_FAILURE);
        }

        // Escribimos algo aleatorio en ellos
        if (write(fd5,"aeiou",5) != 5) {	// escribe lo guardado en el búfer bufr en el archivo fdw
            perror("\nError en escritura examen/cinco.txt\n");	
            exit(EXIT_FAILURE);
        }

        if (write(fd10,"0123456789",10) != 10) {	// escribe lo guardado en el búfer bufr en el archivo fdw
            perror("\nError en escritura examen/diez.txt\n");	
            exit(EXIT_FAILURE);
        }

        // Este hijo ya ha cumplido su cometido

        exit (0);

    }

    // Recogida del hijo para que no queden procesos zombie
    if (waitpid (PID1, NULL, 0) == -1) { 
        printf ("\nError al esperar al primer hijo\n");
        exit(EXIT_FAILURE);
    }
    

// Seguimos en el padre -------------------------------------------------------------------------------------------------------------------------------

// Vamos a recorrer el directorio examen/ contando el número de entradas y guardando en un cauce FIFO
// los números i-nodo de todas y cada una de ellas

    // Abrimos el directorio

    DIR * directorio;
    if ((directorio = opendir ("examen")) == NULL) {
        printf ("\nError al intentar abrir el directorio examen/\n\n");
        perror("\nError en opendir\n\n");
        exit (EXIT_FAILURE);
    }

    // Recorremos el directorio

    struct dirent * file;       // archivo leído
    struct stat metadatafile;   // para los metadatos del archivo leído en cada vuelta del bucle
    int contador = 0;           // para las entradas del directorio
    char ** inodos = (char**) malloc (sizeof(char *) * (TAM+1));


    errno = 0; // para ver si ha habido error al recorrer el directorio

    while ((file = readdir (directorio))!= NULL) {

        // Escribir en el cauce FIFO el mensaje introducido como argumento
        char inodo[TAM];
        sprintf(inodo, "-%s: %ld\n",file->d_name, file->d_ino);
        inodos [contador] = (char*) malloc ( strlen(inodo) +1);
        strcpy (inodos[contador], inodo); 

        // Arriba hemos leído el archivo que toque y comprobado que no es NULL
        contador++; //actualizamos el número de entradas del directorio
        
    }

    // Cuando salimos del bucle, puede ser porque acabemos de recorrer el directorio o 
    // porque haya habido un error: Para saber en qué escenario estamos, consultamos errno

    if (errno) { // si es distinto de 0
        printf ("\nError al recorrer el directorio examen/ con error %d\n\n", errno);
        perror("\nError en readdir\n\n");
        exit (EXIT_FAILURE);
    }

// Ahora que hemos recorrido el directorio, sacamos por pantalla el número de entradas que hemos encontrado
    printf ("\nEn el directorio examen/ hay un total de %d entradas\n", contador);


// Creación del segundo hijo con fork ----------------------------------------------------------------------------------------------------

    pid_t PID2;

    // Creamos el cauce FIFO con nombre

    umask(0);
    if (mknod(ARCHIVO_FIFO,S_IFIFO|0666,0) < 0) {
        printf("Error en mknod, %d\n",errno);
        perror("Error en mknod");
        exit(-1);
    }

    if ((PID2 = fork()) < 0) {   // si hay error al crearlo
        
        perror("\nError en fork del segundo hijo");
        exit(EXIT_FAILURE);
        
    } else if (PID2 == 0) {  // estamos en el hijo

    // CONSUMIDOR


        //Abrir el cauce para lectura-escritura
        int fifo[2];
        
        if ((fifo[0]=open(ARCHIVO_FIFO,O_RDONLY)) <0) {
            perror("\nError en la apertura del cauce FIFO");
            exit(EXIT_FAILURE);
        }

        if ((fifo[1]=open("examen/resultados.txt",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU))<0) {	
            printf("\nError %d en open file examen/resultados.txt\n",errno);
            perror("\nError en open\n");
            exit(EXIT_FAILURE);
        }
        
        // Ahora consumimos el cauce FIFO guardando lo que leamos en el archivo recién abierto

        int leidos = 0;
        char buffer[TAM];

        while(1) {

            // Leemos el cauce FIFO
            leidos = read(fifo[0],buffer,TAM);
            
            if (leidos == -1) {
                printf("\nError %d en read FIFO\n",errno);
                perror("\nError en read\n");
                exit(EXIT_FAILURE);
            }

            if(!strcmp ("fin", buffer)) break; // salimos del bucle cuando no haya nada más que leer

            //setvbuf(&fifo[0],NULL,_IONBF,0);

            // Escribimos en examen/resultados.txt
            if (write(fifo[1],buffer,strlen(buffer)) != strlen(buffer)) {	// escribe lo guardado en buffer en el archivo fdr
                perror("\nError en escritura de examen/resultados.txt\n");	
                exit(EXIT_FAILURE);
            }
            
            
        }

        exit (0);

    } else {
    
        // estamos en el padre
        // PRODUCTOR

        int fd;

        if ((fd=open(ARCHIVO_FIFO,O_WRONLY)) <0) {
            perror("\nError en la apertura del cauce FIFO");
            exit(EXIT_FAILURE);
        }

        // Escribimos en el FIFO los inodos        
        for (int i=0; i<contador; i++) {

            if( (write(fd,inodos[i],strlen(inodos[i]))) != strlen(inodos[i])) {
                perror("\nError al escribir en el FIFO");
                exit(EXIT_FAILURE);
            }

        }

        if( (write(fd,"fin",strlen("fin"))) != strlen("fin")) {
                perror("\nError al escribir en el FIFO");
                exit(EXIT_FAILURE);
        }


                //sleep (1);


    }


    

    /*// recogida del hijo para que no queden procesos zombie
    if (wait (NULL) == -1) { 
        printf ("\nError al esperar al segundo hijo\n");
        exit(EXIT_FAILURE);
    }*/ wait (NULL); 



// Seguimos al padre ------------------------------------------------------------------------------------------------------------------------------------

// Creación el tercer hijo ----------------------------------------------------------------------------------------------------------------------------

    pid_t PID3;

    if ((PID3 = fork()) < 0) {   // si hay error al crearlo
        
        perror("\nError en fork hijo");
        exit(EXIT_FAILURE);
        
    } else if (PID3 == 0) {  // estamos en el hijo

        // Ejecutamos `ls -lai` y guardamos el resultado en examen/resultados.txt
        // Para ello, hacemos que el proceso padre sea abuelo: el hijo PID3 tendrá otro hijo
        // Habrá un cauce sin nombre para pasar la información

        int cauce[2];
        pid_t PID33;

        pipe(cauce); // Llamada al sistema para crear un pipe

        if ( (PID33 = fork())<0) {
            perror("\nError en fork del hijo de hijo 3");
            exit(EXIT_FAILURE);
        }
        if (PID33 == 0) { // Hijo de hijo 3: ls -lai

            //Cerrar el descriptor de lectura de cauce en el proceso hijo
            close(cauce[0]);

            //Duplicar el descriptor de escritura en cauce en el descriptor
            //correspondiente a la salida estandr (stdout), cerrado previamente en
            //la misma operacion
            dup2(cauce[1],STDOUT_FILENO);
            execlp("ls","ls", "-lai", NULL);

            exit (0);
        }
        else { // Hijo 3: guardar en examen/resultados.txt

            //Cerrar el descriptor de escritura en cauce situado en el proceso padre
            close(cauce[1]);

            //Duplicar el descriptor de lectura de cauce en el descriptor
            //correspondiente a la entrada est�ndar (stdin), cerrado previamente en
            //la misma operaci�n
            dup2(cauce[0],STDIN_FILENO);

            int leidos = 0;

            while(1) {

                // Leemos el cauce
                char buffer[TAM];
                leidos = read(cauce[0],buffer,TAM);
                
                if (leidos == -1) {
                    printf("\nError %d en read FIFO\n",errno);
                    perror("\nError en read\n");
                    exit(EXIT_FAILURE);
                }

                // Abrimos examen/resultados.txt SIN truncar
                int fdr;

                if ((fdr=open("examen/resultados.txt",O_CREAT|O_RDWR,S_IRWXU))<0) {	
                    printf("\nError %d en open file examen/resultados.txt\n",errno);
                    perror("\nError en open\n");
                    exit(EXIT_FAILURE);
                }

                // Escribimos en examen/resultados.txt
                if (write(fdr,buffer,leidos) != leidos) {	// escribe lo guardado en buffer en el archivo fdr
                    perror("\nError en escritura de examen/resultados.txt\n");	
                    exit(EXIT_FAILURE);
                }
                
                if(leidos == 0) break; // salimos del bucle cuando no haya nada más que leer
                
            }

            // recogida del hijo para que no queden procesos zombie
            if (waitpid (PID33, NULL, 0) == -1) { 
                    printf ("\nError al esperar al hijo del tercer hijo\n");
                    exit(EXIT_FAILURE);
            }
        }

        exit (0);

    } else {    // estamos en el padre

        // código padre

        // recogida del hijo para que no queden procesos zombie
        if (waitpid (PID3, NULL, 0) == -1) { 
                printf ("\nError al esperar al tercer hijo\n");
                exit(EXIT_FAILURE);
        }

    }

// Cambio de actuación frente a la señal ctrl-C ---------------------------------------------------------------------------------------------------------

    struct sigaction act;
    
    act.sa_handler = hdlr;
    
    sigemptyset (&act.sa_mask);	//no bloquea ninguna
     
    act.sa_flags = SA_RESTART;

    if (sigaction (SIGINT, &act, NULL) == -1)
        printf ( "\nError en el handler\n");

    // while (1); -> lo que nos pide el enunciado

    sleep (15); // tiempo prudencial para que de tiempo a mandar la señal, pero que no haya bucle infinito y el programa pueda terminar


    exit (EXIT_SUCCESS);
}