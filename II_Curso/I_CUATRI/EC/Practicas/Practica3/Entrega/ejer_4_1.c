#include <stdio.h> //printf
#include <stdlib.h> //exit
#include <sys/time.h> //gettimeofday(), struct timeval

int resultado = 0;

#ifndef TEST
#define TEST 4
#endif

/* ------------------------------------------------- */
    #if TEST==1

    #define SIZE 4
    unsigned lista[SIZE]={0x80000000, 0x00400000, 0x00000200, 0x00000001};
    #define RESULT 4
/* ------------------------------------------------- */

    #elif TEST==2

    #define SIZE 8
    unsigned lista[SIZE]={0x7fffffff, 0xffbfffff, 0xfffffdff, 0xfffffffe,
                          0x01000023, 0x00456700, 0x8900ab00, 0x00cd00ef};
    #define RESULT 156

/* ------------------------------------------------- */

    #elif TEST==3

    #define SIZE 8
    unsigned lista[SIZE]={0x0, 0x01020408, 0x35906a0c, 0x70b0d0e0,
                          0xffffffff, 0x12345678, 0x9abcdef0, 0xdeadbeef};
    
    #define RESULT 116

/* ------------------------------------------------- */

    #elif TEST==4 || TEST==0

    #define NBITS 20
    #define SIZE (1<<NBITS) // tamaño suficiente para tiempo apreciable
    unsigned lista[SIZE];
    #define RESULT ( NBITS * ( 1 << NBITS-1 ) )

/* ------------------------------------------------- */
    
    #else
        #error "Definir TEST entre 0..4"
    #endif

void crono(int (*func)(), char* msg){
    struct timeval tv1, tv2;
    long tv_usecs;

    gettimeofday(&tv1, NULL);
    resultado = func(lista,SIZE);
    gettimeofday(&tv2, NULL);

    tv_usecs = (tv2.tv_sec - tv1.tv_sec)*1E6+
               (tv2.tv_usec - tv1.tv_usec);
    
    #if TEST==0
        printf("%ld" "\n", tv_usecs);
    #else
        printf("resultado = %d\t", resultado);
        printf("%s:%9ld us \n", msg, tv_usecs);
    #endif
}

#define WSIZE 8*sizeof(long)
int popcount1(unsigned* lista, size_t len){
    int result = 0;

    for (int i = 0; i < len; i++)
    {
        unsigned x = lista[i];

        for (int j = 0; j < WSIZE; j++)
        {
            result += x & 0x1;
            x >>= 1;
        }
    }

    return result;
}

int popcount2(unsigned* lista, size_t len){
    int result = 0;

    unsigned x;

    for (int i = 0; i < len; i++)
    {
        x = lista[i];

        while(x){
            result += x & 0x1;
            x >>= 1;
        }
    }

    return result;
}

int popcount3(unsigned* lista, size_t len){
    int resultado = 0;
    unsigned x;

    for (int i = 0; i < len; i++){
        x = lista[i];

        asm("\n"
        "ini3:      \n\t"
            "shr %[x]   \n\t"
            "adc $0, %[r] \n\t"
            "test %[x], %[x]    \n\t"
            "jnz ini3   \n\t"
            :[r] "+r" (resultado)
            :[x] "r" (x));
    }

    return resultado;
}

int popcount4(unsigned* lista, size_t len){
    int resultado = 0;
    unsigned x;

    for (size_t i = 0; i < len; i++)
    {
        x = lista[i];

        asm("\n"
            "clc    \n\t"
            "ini4:  \n\t"
                "adc $0, %[r]   \n\t"
                "shr %[x]   \n\t"
                "jnz ini4   \n\t"
                "adc $0, %[r]   \n\t"
            :[r] "+r" (resultado)
            :[x] "r" (x));
    }
    
    return resultado;
}

int popcount5(unsigned* lista, size_t len){
    unsigned result = 0;
    unsigned x,val;

    for (int i = 0; i < len; i++)
    {
        x = lista[i];
        val = 0;

        for (int j = 0; j < 8; j++)
        {
            val += x & 0x01010101L;
            x >>= 1;
        }

        val += (val >> 16);
        val += (val >> 8);
        val &= 0xFF;

        result += val;
    }

    return result; 
}


//types and constants used in the functions below
//uint64_t is an unsigned 64-bit integer type 
const unsigned m1 = 0x55555555; //binary: 0101...
const unsigned m2 = 0x33333333; //binary: 00110011...
const unsigned m4 = 0x0f0f0f0f; //binary: 4 zeros, 4 ones ...
const unsigned m8 = 0x00ff00ff; //binary: 8 zeros, 8 ones ...
const unsigned m16 = 0x0000ffff; // binary: 16 zeros, 16 ones ...

int popcount6(unsigned* lista, size_t len){
    int resultado = 0;
    unsigned x;

    for (size_t i = 0; i < len; i++)
    {
        x = *(unsigned*) &lista[i];

        x = (x & m1) + ((x >> 1) & m1); //put count of each 2 bits into those 2 bits
        x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits
        x = (x & m4) + ((x >> 4) & m4); //put count of each 8 bits into those 8 bits
        x = (x & m8) + ((x >> 8) & m8); //put count of each 16 bits into those 16 bits
        x = (x & m16) + ((x >> 16) & m16); //put count of each 32 bits intho those 32 bits

        resultado += x;
    }

    return resultado;
}

//Wikipedia popcount "naive" iimplementation ***128b***
int popcount7(unsigned* lista, size_t len){
    unsigned x1, x2;
    int resultado = 0;

    if (len & 0x3) printf("leyendo 128b pero len no múltiplo de 4\n");

    for (size_t i = 0; i < len; i+=2)
    {
        x1 = *(unsigned*) &lista[i];
        x2 = *(unsigned*) &lista[i+1];

        x1 = (x1 & m1) + ((x1 >> 1) & m1); 
        x1 = (x1 & m2) + ((x1 >> 2) & m2);
        x1 = (x1 & m4) + ((x1 >> 4) & m4);
        x1 = (x1 & m8) + ((x1 >> 8) & m8);
        x1 = (x1 & m16) + ((x1 >> 16) & m16);

        x2 = (x2 & m1) + ((x2 >> 1) & m1); 
        x2 = (x2 & m2) + ((x2 >> 2) & m2);
        x2 = (x2 & m4) + ((x2 >> 4) & m4);
        x2 = (x2 & m8) + ((x2 >> 8) & m8);
        x2 = (x2 & m16) + ((x2 >> 16) & m16);

        resultado += x1 + x2;
    }
    
    return resultado;
}

//Version SSSE3 (pshufb) web http://wm.ite.pl/articles/sse-popcount.hmtl
int popcount8(unsigned* lista, size_t len){
    int val, resultado = 0;
    int SSE_mask[] = {0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f, 0x0f0f0f0f};
    int SSE_LUTb[] = {0x02010100, 0x03020201, 0x03020201, 0x04030302};

    if(len & 0x3) printf("leyendo 128b pero len no múltiplo de 4\n");
    for (size_t i = 0; i < len; i+=4)
    {
        asm("movdqu %[x], %%xmm0 \n\t"
            "movdqa %%xmm0, %%xmm1 \n\t"
            "movdqu %[m], %%xmm6 \n\t"
            "psrlw $4, %%xmm1 \n\t"
            "pand %%xmm6, %%xmm0 \n\t"
            "pand %%xmm6, %%xmm1 \n\t"
            
            "movdqu %[l], %%xmm2 \n\t"
            "movdqa %%xmm2, %%xmm3 \n\t"
            "pshufb %%xmm0, %%xmm2 \n\t"
            "pshufb %%xmm1, %%xmm3 \n\t"
            
            "paddb %%xmm2, %%xmm3 \n\t"
            "pxor %%xmm0, %%xmm0 \n\t"
            "psadbw %%xmm0, %%xmm3 \n\t"
            "movhlps %%xmm3, %%xmm0 \n\t"
            "paddd %%xmm3, %%xmm0 \n\t"
            "movd %%xmm0, %[val]"
            : [val] "=r" (val)
            : [x] "m" (lista[i]),
              [m] "m" (SSE_mask[0]),
              [l] "m" (SSE_LUTb[0])
        );

        resultado += val;
    }

    return resultado;
}

//Version SSE4.2 (popcount)
int popcount9(unsigned* lista, size_t len){
    unsigned x;
    int val, resultado = 0;

    for (size_t i = 0; i < len; i++)
    {
        x = lista[i];

        asm("popcnt %[x], %[v]"
            : [v] "=r" (val)
            : [x] "r" (x)
            );

        resultado += val;
    }

    return resultado;
}

//popcount 128 bit p/mejorar prestaciones
int popcount10(unsigned* lista, size_t len){
    unsigned x1,x2, val;
    int resultado = 0;

    if(len & 0x3) printf("leyendo 128b pero len no múltiplo de 4\n");

    for (size_t i = 0; i < len; i+=2)
    {
        x1 = *(unsigned long*) &lista[i];
        x2 = *(unsigned long*) &lista[i+1];

        asm("popcnt %[x1], %[val] \n\t"
            "popcnt %[x2], %%eax \n\t"
            "add %%eax, %[val] \n\t"
            : [val] "=&r" (val)
            : [x1] "r" (x1),
              [x2] "r" (x2)
            : "eax"
        );

        resultado += val;
    }
    
    return resultado;
}

int main(){
    #if TEST==0 || TEST==4
        size_t i;
        for (i = 0; i < SIZE; i++)
        {
            lista[i]=i;
        }
    #endif

    crono(popcount1, "popcount1 (lenguaje C - for)");
    crono(popcount2, "popcount2 (lenguaje C - while)");
    crono(popcount3, "popcount3 (leng.ASM-body - while 4i)");
    crono(popcount4, "popcount4 (leng.ASM-body - while 3i)");
    crono(popcount5, "popcount5 (CS:APP2e 3.49-group 8b)");
    crono(popcount6, "popcount6 (Wikipedia- naive - 32b)");
    crono(popcount7, "popcount7 (Wikipedia- naive - 128b)");
    crono(popcount8, "popcount8 (asm SSE3 - pshufb 128b)");
    crono(popcount9, "popcount9 (asm SSE4- popcount 32b)");
    crono(popcount10, "popcount10 (asm SSE4- popcount128b)");

    #if TEST != 0
        printf("calculado = %d\n", RESULT);
    #endif

    exit(0);  
}