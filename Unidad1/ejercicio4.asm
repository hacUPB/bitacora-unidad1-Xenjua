// Compara el valor de la RAM[5] con 10
// Si RAM[5] < 10, guarda 1 en RAM[7]
// Si RAM[5] >= 10, guarda 0 en RAM[7]

@5
D=M        // D = RAM[5]

@10
D=D-A      // D = RAM[5] - 10

@MENOR
D;JLT      // Si D < 0, entonces RAM[5] < 10

// Caso: RAM[5] >= 10
@0
D=A

@7
M=D        // RAM[7] = 0

@FIN
0;JMP

(MENOR)
@1
D=A

@7
M=D        // RAM[7] = 1
