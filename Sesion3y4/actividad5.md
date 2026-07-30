// Inicio i = 1
@1
D=A
@i
M=D

// incio suma = 0
@0
D=A
@suma
M=D


// Verificar si i > 5
@i
D=M
@5
D=D-A
@FIN
D;JGT


@i
D=M
@suma
M=M+D


@i
M=M+1

// Volver al inicio del ciclo
@LOOP
0;JMP


// Guardar suma en RAM[12]
@suma
D=M
@12
M=D

// Detener el programa
(FINPROGRAMA)
@FINPROGRAMA
0;JMP