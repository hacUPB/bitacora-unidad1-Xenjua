// Dibuja una línea horizontal negra
// de lado a lado en la primera fila

// puntero = SCREEN
@SCREEN
D=A
@puntero
M=D

// contador = 32
@32
D=A
@contador
M=D

    

// Pintar 16 píxeles negros
@puntero
A=M
M=-1

// Avanzar al siguiente word
@puntero
M=M+1

// Restar una iteración
@contador
MD=M-1

// Repetir mientras contador > 0
@LOOP
D;JGT

(FIN)
@FIN
0;JMP