# suma.s: Sumar los elementos de una lista
# llamando a función, pasando argumentos mediante registros
# comprobar con "./suma; echo $?" o con depurador gdb/ddd
# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
lista: .int 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 # ejs. binario 0b / hex 0x
longlista: .int (.-lista)/4 # . = contador posiciones. Aritm.etiq.
resultado: .int 0

.global lista, longlista, resultado, formato

formato:    .asciz "resultado = %d = 0x%x hex\n"
# formato: .asciz "suma = %u = 0x%x hex\n" # fmt para printf() libC
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
_start: .global _start # se puede abreviar de esta forma
# main: .global main # Programa principal si se usa C runtime
jmp suma