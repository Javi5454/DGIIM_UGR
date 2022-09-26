# MODULO suma_06_SC_s.s
# ...
# 5 - entero en C
# 6 - volviendo a sacar la suma a ensamblador
#   gcc -Og -g suma_06_CS_c.c suma_06_CS_s.s -o suma_06_CS

.section .text
suma: .global suma
mov $0, %eax # acumulador
mov $0, %rdx # indice

bucle:
add (%rdi,%rdx,4), %eax # acumular i-ésimo elemento
inc %edx # incrementar índice
cmp %edx,%esi # comparar con longitud
jne bucle # si no iguales, seguir acumulando
ret