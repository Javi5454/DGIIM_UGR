//MODULO suma_06_CS_c.c
#include <stdio.h> //printf()
#include <stdlib.h> //exit()
extern int suma(int* array, int len);

int list[]={1,2,10, 1,2,0b10, 1,2,0x10};
int longlista = sizeof(list)/sizeof(int);
int resultado = -1;

int main(){
    resultado = suma(list, longlista);
    printf("resultado = %d = %0x hex\n", resultado, resultado);

    exit(0);
}