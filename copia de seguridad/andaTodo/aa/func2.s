.text
.global secuencia_formula1
secuencia_formula1:

PUSH {R4, R5, R6, R7, LR}

reset:
MOV R4, #0      // Inicializar output a 0
MOV R7, #7      // Inicializar contador del loop

main_loop:
MOV R5, #1
LSL R5, R5, R7  // output |= (0x1 << i)
ORR R4, R4, R5

MOV R0, R4
BL disp_binary  // Mostrar en pantalla

MOV R0, R4
BL ledShow      // Mostrar en LEDs

MOV R0, #3
BL delay
CMP R0, #0
BEQ turn_off    // Si delay retorna 0, apagar y salir

SUBS R7, R7, #1
BGE main_loop   // Repetir mientras R7 >= 0

MOV R0, #3
BL delay
CMP R0, #0
BEQ turn_off    // Si delay retorna 0, apagar y salir

MOV R4, #0
MOV R0, R4
BL ledShow      // Apagar todos los LEDs

MOV R0, R4
BL disp_binary  // Mostrar en pantalla

MOV R7, #30     // Esperar 30 ciclos
wait_loop:
MOV R0, #3
BL delay
CMP R0, #0
BEQ turn_off    // Si delay retorna 0, apagar y salir

SUBS R7, R7, #1
BNE wait_loop   // Repetir mientras R7 != 0

B reset         // Reiniciar el ciclo principal

turn_off:
BL turnOff      // Apagar LEDs

POP {R4, R5, R6, R7, PC}

.data
msg_f1:  .asciz "Carrera de Formula 1:\n"
