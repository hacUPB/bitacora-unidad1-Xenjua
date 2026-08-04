// La variable posicion guarda la dirección de memoria
// donde se encuentra actualmente la línea.

@SCREEN
D=A
@posicion
M=D

// Dibujar inicialmente la línea de 16 píxeles
@posicion
A=M
M=-1


    // Leer el teclado
    @KBD
    D=M

    // Si no hay tecla presionada, volver a leer
    @LEER_TECLADO
    D;JEQ

    // Comprobar si se presionó la tecla d
    @100
    D=D-A
    @MOVER_DERECHA
    D;JEQ

    // Volver a leer el teclado para comprobar la tecla i
    @KBD
    D=M
    @105
    D=D-A
    @MOVER_IZQUIERDA
    D;JEQ

    @ESPERAR_SOLTAR
    0;JMP



    // Borrar la línea de la posición anterior
    @posicion
    A=M
    M=0

    // Avanzar una dirección de memoria
    @posicion
    M=M+1

    // Dibujar la línea en la nueva posición
    A=M
    M=-1

    @ESPERAR_SOLTAR
    0;JMP




    // Borrar la línea de la posición anterior
    @posicion
    A=M
    M=0

    // Retroceder una dirección de memoria
    @posicion
    M=M-1

    // Dibujar la línea en la nueva posición
    A=M
    M=-1

    @ESPERAR_SOLTAR
    0;JMP




    // Esperar hasta que el usuario suelte la tecla.
    // Esto evita que la línea se mueva muchas veces
    // por mantener presionada una tecla.

    @KBD
    D=M
    @ESPERAR_SOLTAR
    D;JNE

    @LEER_TECLADO
    0;JMP