// Línea horizontal interactiva de 16 píxeles.
// d = mover a la derecha.
// i = mover a la izquierda.

// La variable posicion almacena la dirección
// de memoria donde está dibujada la línea.

@SCREEN
D=A
@posicion
M=D

// Dibujar la línea inicialmente.
@posicion
A=M
M=-1


