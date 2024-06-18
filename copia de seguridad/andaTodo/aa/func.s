.text

.global ambulancia
ambulancia:

PUSH {R4, R5, R6, LR}

reset:
LDR R4, =ambulanciad
MOV r6, #21

loop:
LDRB R5, [R4], #1

MOV R0, R5
BL disp_binary //muestra en pantalla

MOV R0, R5
BL ledShow //muestra en lo leds

MOV R0, #2 
BL delay

SUBS R6, R6, #1
BEQ reset

CMP R0, #0
BNE loop
BL turnOff

POP {R4, R5, R6, PC}


.data
ambulanciad:
.byte 0x0
.byte 0xF
.byte 0xF
.byte 0xF0
.byte 0xF0
.byte 0x0
.byte 0x1
.byte 0x2
.byte 0x4
.byte 0x8
.byte 0x10
.byte 0x20
.byte 0x40
.byte 0x80
.byte 0x40
.byte 0x20
.byte 0x10
.byte 0x8
.byte 0x4
.byte 0x2
.byte 0x1