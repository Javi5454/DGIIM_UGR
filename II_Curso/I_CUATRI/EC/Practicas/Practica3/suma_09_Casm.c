#include <stdio.h> //printf
#include <stdlib.h> //exit
#include <sys/time.h> //gettimeofday(), struct timeval

#define SIZE (1 << 10) //tamaño suficiente para tiempo apreciable
int list[SIZE];
int resultado = 0;

int suma1(int* array, int len){
    int i, res=0;
    for (i = 0; i < len; i++)
    {
        res += array[i];
    }

    return res;
    
}

int suma2(int* array, int len){
    int i, res = 0;

    for (i = 0; i < len; i++)
    {
        asm("add (%[a],%[i],4), %[r]"
        : [r] "+r" (res)
        : [i] "r" ((long)i),
          [a] "r" (array)
          );
    }
    return res;
}

int suma3(int* array, int len){
    asm("mov $0, %%eax   \n"
    "   mov $0, %%rdx    \n"
    "bucle:             \n"
    "   add (%%rdi,%%rdx,4), %%eax\n"
    "   inc %%edx        \n"
    "   cmp %%edx, %%esi  \n"
    "   jne bucle         "
    :
    :
    : "cc",
      "eax", "rdx"
    );
}

void crono(int (*func)(), char* msg){
    struct timeval tv1, tv2;
    long tv_usecs;

    gettimeofday(&tv1, NULL);
    resultado = func(list,SIZE);
    gettimeofday(&tv2, NULL);

    tv_usecs = (tv2.tv_sec - tv1.tv_sec)*1E6+
               (tv2.tv_usec - tv1.tv_usec);
    printf("resultado = %d\t", resultado);
    printf("%s:%9ld us\n", msg, tv_usecs);
}

int main(){
    int i;
    for(i = 1; i<=SIZE;i++){
        list[i-1]=i;
    }

    crono(suma1, "suma1 (en lenguage C  )");
    crono(suma2, "suma2 (1 instrucción asm)");
    crono(suma3, "suma3 (bloque asm entero)");
    printf("N*(N+1)/2=%d\n", (SIZE+1)*(SIZE/2));

    exit(0);
}