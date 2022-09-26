// 7. gcc -Og -g suma_07_Casm.c -o suma_07_Casm

#include <stdio.h> // printf()
#include <stdlib.h> // exit()

int lista[] = {1,2,10, 1,2,0b10, 1,2,0x10};
int longlista = sizeof(lista)/sizeof(int);
int resultado = 0;

int suma(int* array, int len){
    int i, res=0;
    
    for (i = 0; i < len; i++)
    {
        // res+= array[i]
        asm("add (%[a], %[i],4), %[r]"
        :[r] "+r" (res) 
        :[i] "r" ((long)i),
         [a] "r" (array)
        );
    }

    return res;
    
}

int main(){
    resultado = suma(lista, longlista);
    printf("resultado = %d = %0x hex\n", resultado, resultado);

    exit(0);
}