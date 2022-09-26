// Se compila con gcc -Og suma_05_C.c -o suma_05_C

#include <stdio.h> //para print f
#include <stdlib.h> //para exit()

int list[]={1,2,10, 1,2, 0b10, 1,2,0x10};
int longlista = sizeof(list)/sizeof(int);
int resultado = 0;

int suma(int* array, int len){
    int i, res = 0;

    for (i = 0; i < len; i++)
    {
        res+= array[i];
    }
    return res;
}

int main(){
    resultado = suma(list, longlista);
    printf("resultado = %d = %0x hex\n", resultado, resultado);

    exit(0);
}