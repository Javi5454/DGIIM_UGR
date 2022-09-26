// 7. gcc -Og -g suma_07_Casm.c -o suma_07_Casm

#include <stdio.h> // printf()
#include <stdlib.h> // exit()

int lista[] = {1,2,10, 1,2,0b10, 1,2,0x10};
int longlista = sizeof(lista)/sizeof(int);
int resultado = 0;

int suma(int* array, int len){
    asm("mov $0, %eax   \n"
    "   mov $0, %rdx    \n"
    "bucle:             \n"
    "   add (%rdi,%rdx,4), %eax\n"
    "   inc %edx        \n"
    "   cmp %edx, %esi  \n"
    "   jne bucle         "
    );
}

int main(){
    resultado = suma(lista, longlista);
    printf("resultado = %d = %0x hex\n", resultado, resultado);

    exit(0);
}