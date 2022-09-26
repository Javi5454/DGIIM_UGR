// SOLEDAD RUIZ GÓMEZ
// primo.c

// compilar como: gcc -g esclavo.c -o esclavo -lm
// incluimos -lm para poder usar la biblioteca math.h

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>	// para poder usar sqrt()

int primo (int num) { //en C no podemos usar bool, pero esta funci�n trabaja como una booleana

	int output = 1;
	int tope   = sqrt(num);
	
	for (int i=2; i<=tope && output; i++) 
		if (num%i == 0) output = 0;

	return output;
}

int main(int argc, char *argv[]) { // PRIMO

	// Leemos la cifra que se nos pasa como argumento
	if (argc<2) { 
		perror ("\nNúmero de argumentos incorrecto\n\n");
		exit(-1); 
	}

	int num = atoi (argv[1]); // ya se ha comprobado en el padre que es un entero positivo
	
	// Calculamos si es primo o no

    if (primo(num))	{
        printf ("El numero %d es primo\n", num);
    } else {
        int i = num+1;
        while (!primo(i)) i++;
        printf ("El numero %d no es primo: %d es el primo superior más cercano\n", num, i);
    }
        
	return EXIT_SUCCESS;
	
}