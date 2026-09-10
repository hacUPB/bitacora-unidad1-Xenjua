# ¿Qué es el encapsulamiento para ti? Describe una situación en la que te haya sido útil o donde hayas visto su importancia.

Para mí, el encapsulamiento es proteger los datos internos de una clase y permitir que se acceda a ellos únicamente mediante métodos controlados. Por ejemplo, en el proyecto del hotel fue útil para evitar que cualquier parte del programa modificara directamente el precio o el estado de una habitación. En lugar de hacerlo libremente, se usaron métodos get y set que podían validar los nuevos valores. Así se reducen errores y el código queda más seguro y organizado.

# ¿Qué es la herencia? ¿Por qué un programador decidiría usarla? Da un ejemplo simple.

La herencia es un principio de la programación orientada a objetos que permite crear una clase nueva a partir de otra existente. La clase hija obtiene los atributos y métodos de la clase padre.
Un programador la usaría para reutilizar código, evitar repeticiones y organizar mejor las clases que comparten características.
Por ejemplo, en un sistema de hotel:
Administrador hereda de Usuario, por lo que puede usar nombre e IniciarSesion(), además de tener su propia función GenerarReporte().

# ¿Qué es el polimorfismo? Describe con tus palabras qué significa que un código sea “polimórfico”.

El polimorfismo permite que diferentes objetos utilicen un mismo método pero se comporten de manera diferente. Un código polimórfico puede trabajar con varios tipos de objetos de forma más flexible y reutilizable.

CODIGO:

using System;using System.Collections.Generic;
public abstract class Figura{
		private string nombre;
    public string Nombre {
		    get { return nombre;}
		    protected set { nombre = value; }
		    }
    public Figura(string nombre)    {
		    this.Nombre = nombre;
		    }
    public abstract void Dibujar();
    }
public class Circulo : Figura{
		public double Radio { get; private set; }
    public Circulo(double radio) : base("Círculo")    {
		    this.Radio = radio;
		    }
    public override void Dibujar()    {
		    Console.WriteLine($"Dibujando un {Nombre} de radio {Radio}.");
		    }
		}
public class Rectangulo : Figura{
		public double Base { get; private set; }
		public double Altura { get; private set; }
    public Rectangulo(double b, double h) : base("Rectángulo")    {
		    this.Base = b;
		    this.Altura = h;
		    }
    public override void Dibujar()    {
		    Console.WriteLine($"Dibujando un {Nombre} de {Base}x{Altura}.");
		    }
		}
public class Programa{
		public static void Main()    {
				List<Figura> misFiguras = new List<Figura>();
        misFiguras.Add(new Circulo(5.0));
        misFiguras.Add(new Rectangulo(4.0, 6.0));
        misFiguras.Add(new Circulo(10.0));
        foreach (Figura fig in misFiguras) {
		        fig.Dibujar();
		        }
		    }
		}
# Encapsulamiento
- Señala una línea de código que sea un ejemplo claro de encapsulamiento y explica por qué lo es.
- ¿Por qué crees que el campo nombre es private pero la propiedad Nombre es public? ¿Qué problema se evita con esto?

  1. Ejemplo de encapsulamiento:
   Una línea clara es:

`private string nombre;`
Es encapsulamiento porque el atributo `nombre` está protegido y no puede ser modificado directamente desde fuera de la clase `Figura`. Para acceder a él se utiliza la propiedad `Nombre`, lo que permite controlar cómo se consulta o modifica el dato.

2. ¿Por qué `nombre` es private pero `Nombre` es public?
   El campo `nombre` es `private` para evitar que otras clases lo modifiquen directamente. En cambio, la propiedad `Nombre` es `public` para permitir consultar su valor de una forma controlada.

Además, tiene `protected set`, por lo que solamente la clase `Figura` y las clases que heredan de ella pueden cambiar el nombre. Esto evita cambios incorrectos o accidentales desde otras partes del programa y mantiene los datos protegidos.
