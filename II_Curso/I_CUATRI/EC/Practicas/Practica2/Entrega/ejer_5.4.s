# suma.s: Sumar los elementos de una lista
# llamando a función, pasando argumentos mediante registros
# comprobar con "./suma; echo $?" o con depurador gdb/ddd
# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
#ifndef TEST
#define TEST 20
#endif
    .macro linea
    #if   TEST==1
                .int 1, 2, 1, 2
    #elif TEST==2
                .int -1, -2, -1, -2
    #elif TEST==3
                .int 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF
    #elif TEST==4
                .int 0x80000000, 0x80000000, 0x80000000, 0x80000000,
    #elif TEST==5
                .int 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
    #elif TEST==6
                .int 2000000000, 2000000000, 2000000000, 2000000000
    #elif TEST==7
                .int 3000000000, 3000000000, 3000000000, 3000000000
    #elif TEST==8
                .int -2000000000, -2000000000, -2000000000, -2000000000
    #elif TEST==9
                .int -3000000000, -3000000000, -3000000000, -3000000000
    #elif TEST>=10 && TEST<=14
                .int 1,1,1,1
    #elif TEST>=15 && TEST<=19
                .int -1,-1,-1,1
    #else 
                .error "Definir TEST entre 1..19"
    #endif
                .endm

    .macro linea0
    #if TEST>=1 && TEST<=9
                linea
    #elif TEST==10
                .int 0,2,1,1
    #elif TEST==11
                .int 1,2,1,1
    #elif TEST==12
                .int 8,2,1,1
    #elif TEST==13
                .int 15,2,1,1
    #elif TEST==14
                .int 16,2,1,1
    #elif TEST==15
                .int 0,-2,-1,-1
    #elif TEST==16
                .int -1,-2,-1,1
    #elif TEST==17
                .int -8,-2,-1,-1
    #elif TEST==18
                .int -15,-2,-1,-1
    #elif TEST==19
                .int -16,-2,-1,-1
    #else 
                .error "Definir TEST entre 1..19"
    #endif
                .endm
lista: linea0
.irpc i,123
linea
.endr

longlista: .int (.-lista)/4 # . = contador posiciones. Aritm.etiq.
media: .int 0
resto: .int 0
formato: .ascii "media \t= %11d \t resto \t= %11d \n" # fmt para printf() libC
# el string "formato" sirve como argumento a la llamada printf opcional
# opción: 1) no usar printf, 2)3) usar printf/fmt/exit, 4) usar tb main
# 1) as suma.s -o suma.o
# ld suma.o -o suma 1232 B
# 2) as suma.s -o suma.o 6520 B
# ld suma.o -o suma -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
# 3) gcc suma.s -o suma –no-pie –nostartfiles 6544 B
# 4) gcc suma.s -o suma –no-pie 8664 B
# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
.section .text # PROGRAMA PRINCIPAL
# _start: .global _start # se puede abreviar de esta forma
main: .global main # Programa principal si se usa C runtime
call trabajar # subrutina de usuario
call imprim_C # printf() de libC
# call acabar_L # exit() del kernel Linux
call acabar_C # exit() de libC
ret
trabajar:
mov $lista, %rbx # dirección del array lista
mov longlista, %rcx # número de elementos a sumar
call suma # llamar suma(&lista, longlista);
call division
mov %eax, media # salvar resultado menos significativo
mov %edx, resto # salvar el resultado más significativo 4 posiciones
ret

division:
idiv %esi # Calculamos la media diviendo entre la longitud
ret
# SUBRUTINA: int suma(int* lista, int longlista);
# entrada: 1) %rbx = dirección inicio array
# 2) %ecx = número de elementos a sumar
# salida: %eax = resultado de la suma
suma:
mov $0, %rax # donde tenemos la suma
mov $0, %rsi # iterador del bucle
mov $0, %rbp # LSB
mov $0, %rdi # MSB


bucle:
mov (%rbx,%rsi,4), %eax # acumular i-ésimo elemento
cltd # extensión de signo de eax a edx
add %eax, %ebp  # sumamos LSB
adc %edx, %edi # sumamos MSB
inc %rsi # incrementar índice
cmp %rsi,%rcx # comparar con longitud
jne bucle # si no iguales, seguir acumulando
mov %ebp, %eax
mov %edi, %edx

xor %ebp, %ebp
xor %edi, %edi
ret

imprim_C:
# si se usa esta subrutina, usar también la línea que define formato
# se puede linkar con ld –lc –dyn ó gcc –nostartfiles, o usar main
mov $formato, %rdi # traduce resultado a decimal/hex
mov media, %esi # versión libC de syscall __NR_write
mov resto, %rcx # ventaja: printf() con fmt "%u" / "%x"
mov %rax, %rcx
mov %edx, %ebp
mov $0, %eax # varargin sin xmm
call printf # == printf(formato,resultado,resultado)
ret

acabar_L: # void _exit(int status);
mov $60, %rax # exit: servicio 60 kernel Linux
mov media, %edi # status: código a retornar (la suma)
syscall # == _exit(resultado);
ret
acabar_C: # void exit(int status);
 mov media, %edi # status: código a retornar (la suma)
 call exit # == exit(resultado)
 ret