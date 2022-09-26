// SOLEDAD RUIZ GÓMEZ
// Ejercicio 2 examen infor SO MódII 2020/2021

// Se me ocurren otras maneras de hacer el ejercicio, quizás más correctas
// pero, sinceramente, me da pereza. bss


#include <sys/types.h>	
#include <sys/stat.h>	
#include <sys/wait.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

#define DEC 10


int main(int argc, char *argv[]) {

// EMPEZAMOS LA EJECUCIÓN FUNCIONAL DEL PROGRAMA

    char cadena [256];
    int num = 0;

    // Creamos el archivo que va a usar el hijo escritor

    int fd;

    if ((fd=open("resultado.txt",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU))<0) {	// archivo para escribir (lo creamos si no existe y borramos su contenido si ya existe)
        printf("\nError %d en open resultado\n",errno);
        perror("\nError en open\n");
        exit(EXIT_FAILURE);
    }

    char filedescriptor [256];
    sprintf(filedescriptor, "%d", fd);

    // Leemos 
    if (scanf("%s",cadena) == EOF) {
        perror ("\nError en la entrada\n");
        exit(EXIT_FAILURE);
    }

    while (strcmp(cadena, "fin")) { // mientras que la entrada estándar sea distinta de "fin"
        
        // Si la cadena no es "fin", ha de ser un número entero positivo
        errno = 0; // para ver si ha habido error

        num = strtol(cadena, NULL, DEC);

        if (errno || num < 0) {
            perror("\nError: las entradas han de ser enteros positivos o la cadena \"fin\"\n\n");
            exit (EXIT_FAILURE);
        }


        // CREACIÓN DE LOS HIJOS

        pid_t PID1, PID2;
        char cifra [256];

        // Creamos el primer hijo

        if ((PID1= fork())<0) {
        
            perror("\nError en fork hijo primo");
            exit(EXIT_FAILURE);
            
        } else if (PID1 == 0) { // Hijo primo
        
            sprintf(cifra, "%d", num);  //pasamos de entero a *char para poder pasar como argumentos al ejecutable
                                        //la funcion sprintf nos permite cambiar el formato de un char*
            
            // Llamamos al ejecutable del primer hijo
            if(execl("./primo", "primo", cifra, NULL) < 0) {
                perror("\nError en el execl primo");
                exit(EXIT_FAILURE);
            }
            
        }
        else { // Volvemos a trabajar con el proceso padre porque PID1>0
        

            // Creamos el siguiente hijo

            if ((PID2= fork())<0) {
        
            perror("\nError en fork hijo primo");
            exit(EXIT_FAILURE);
            
            } else if (PID2 == 0) { // Hijo escritor
            
                sprintf(cifra, "%d", num);  //pasamos de entero a *char para poder pasar como argumentos al ejecutable
                                            //la funcion sprintf nos permite cambiar el formato de un char*
                
                // Llamamos al ejecutable del primer hijo
                if(execl("./escritor", "escritor", cifra, filedescriptor, NULL) < 0) {
                    perror("\nError en el execl escritor");
                    exit(EXIT_FAILURE);
                }
                
            }
            else { // Volvemos a trabajar con el proceso padre porque PID2>0
            
                // Esperamos a sendos hijos

                if (waitpid (PID1, NULL, WNOHANG) == -1) {  // esperamos al hijo primo
                        printf ("\nError al esperar al hijo primo\n");
                        exit(EXIT_FAILURE);
                }

                if (waitpid (PID2, NULL, WNOHANG) == -1) {  // esperamos al hijo escritor
                        printf ("\nError al esperar al hijo escritor\n");
                        exit(EXIT_FAILURE);
                }            
            }
        }
        
        // Volvemos a leer
        if (scanf("%s",cadena) == EOF) {
            perror ("\nError en la entrada\n");
            exit(EXIT_FAILURE);
        }
            
    }

    // Salimos del bucle cuando la entrada es "fin", llamamos al programa escritor

    sprintf(filedescriptor, "%d", fd);
    
    // Llamamos al ejecutable del primer hijo
    if(execl("./escritor", "escritor", cadena, filedescriptor, NULL) < 0) {
        perror("\nError en el execl escritor");
        exit(EXIT_FAILURE);
    }

    close (fd); //cerramos el archivo resultado

    exit(EXIT_SUCCESS);

}