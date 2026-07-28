//@1
//D=A
//@2
//D=D+A
//@16
//M=D
//(END)
//@END
//0;JMP

//Este programa toma los valores 1 y 2, los suma y guarda el resultado obtenido en la posición 16 de la memoria RAM.


//Escribe un programa en lenguaje ensamblador que sume los números 5 y 10, y almacene el resultado en la dirección de memoria 20. Utiliza el simulador de la CPU Hack para ejecutar tu programa y verifica que el resultado es correcto.

//@5
//D=A
//@10
//D=D+A
//@20
//M=D
//(END)
//@END
//0;JMP


//¿Qué diferencia hay entre los datos almacenados en la memoria ROM y en la RAM?

//La memoria RAM almacena información de forma temporal mientras el equipo está en funcionamiento; al apagarlo, esos datos desaparecen. En cambio, la memoria ROM conserva información permanente necesaria para iniciar y operar el sistema.


//Copiar una constante al

//@1954
//D=A
//@23
//Al cargar @23, el registro A cambia a ese nuevo valor, pero el contenido que ya estaba almacenado en D permanece sin modificaciones.
//D=D+A


//@100
//M=0
//@17
//D=A
//@100
//M=D

//RAM[100] <-- RAM[200]

//@200
//D=M

//@100
//M=D

//RAM[3] <-- RAM[3]-15

//@15
//D=A
//@3
//M=M-D

//@4
//D=M+1
//@3
//M=D

//if (D == 0) goto 300
//Condicionales

//@300
//D;JEQ

// if (RAM[3] < 100) goto 12
//RAM[3] = 60
//60 - 100 = -40
//120 - 100 = 20

//@3
//D=M
//@100
//D=D-A
//@12
//D;JLT