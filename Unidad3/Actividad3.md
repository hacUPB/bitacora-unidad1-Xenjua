    //@SCREEN
//D=A
//@i
//M=D

//Este código hace que el registro A apunte al inicio de la memoria de la pantalla (16384). Luego copia esa dirección al registro D y, finalmente, guarda ese valor en la variable @i.

@SCREEN
D=A
@i
M=D


(READKEYBOARD)
@KBD
D=M
@KEYPRESSED
D;JNE
@i
D=M
@SCREEN
D=D-A
@READKEYBOARD
D;JLE
@i
M=M-1
A=M
M=0
C

(KEYPRESSED)
@i
D=M
@KBD
D=D-A
@READKEYBOARD
D;JGE
@i
A=M
M=-1
@i
M=M+1
@READKEYBOARD
0;JMP


//Este programa verifica continuamente si se ha presionado una tecla. Para ello lee el contenido de la dirección del teclado (KBD) y guarda ese dato en el registro D para decidir qué acciones ejecutar.

//En este programa, la instrucción "M=M+1" corresponde a una operación realizada por la ALU, ya que incrementa en una unidad el valor almacenado en memoria.

//¿Para qué sirve el registro PC?
//El registro PC (Program Counter) almacena la dirección de memoria de la siguiente instrucción que debe ejecutar el procesador, permitiendo que el programa avance correctamente.

//¿Cuál es la diferencia entre @i y @READKEYBOARD?
//@i representa una variable utilizada para almacenar información durante la ejecución del programa, mientras que @READKEYBOARD es una etiqueta que marca una parte específica del código a la que el programa puede saltar.

//Describe qué se necesita para leer el teclado y mostrar información en la pantalla.
//Para leer el teclado se utiliza la dirección KBD, desde donde se obtiene el valor de la tecla presionada. Después, mediante las condiciones del programa y la memoria de pantalla (SCREEN), se actualizan los píxeles correspondientes para mostrar el resultado.

//Identifica un bucle en el programa y explica su funcionamiento.
//El ciclo formado por la etiqueta @READKEYBOARD y la instrucción "0;JMP" hace que el programa vuelva constantemente al mismo punto para revisar si el usuario ha presionado una tecla, manteniéndolo en ejecución de manera continua.