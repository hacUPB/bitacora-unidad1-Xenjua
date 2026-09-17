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

# Herencia
- ¿Cómo se evidencia la herencia en la clase Circulo?
- Un objeto de tipo Circulo, además de Radio, ¿Qué otros datos almacena en su interior gracias a la herencia?

1. ¿Cómo se evidencia la herencia en la clase `Circulo`?
   La herencia se evidencia en esta línea:
`public class Circulo : Figura`
Esto significa que `Circulo` hereda de la clase `Figura`. Gracias a esto, puede usar características de `Figura`, como la propiedad `Nombre` y el método `Dibujar()`, aunque en este caso `Dibujar()` se sobrescribe con `override`.
2. Un objeto de tipo `Circulo`, además de `Radio`, ¿qué otros datos almacena gracias a la herencia?
   Además de `Radio`, un objeto `Circulo` también almacena el dato `nombre` que pertenece a la clase `Figura`.
Cuando se crea un círculo con:
`new Circulo(5.0)`
se llama al constructor de `Figura` mediante:
`base("Círculo")`
Por eso, el objeto guarda tanto el valor del radio como el nombre `"Círculo"`.

# Polimorfismo

Observa el bucle foreach. La variable fig es de tipo Figura, pero a veces contiene un Circulo y otras un Rectangulo. Cuando se llama a fig.Dibujar(), el programa ejecuta la versión correcta. En tu opinión, ¿Cómo crees que funciona esto “por debajo”? No necesitas saber la respuesta correcta, solo quiero que intentes razonar cómo podría ser.


Creo que el programa revisa qué tipo de objeto está guardado realmente en `fig` en cada vuelta del `foreach`. Aunque la variable sea de tipo `Figura`, el objeto puede ser un `Circulo` o un `Rectangulo`.
Entonces, cuando se llama a `fig.Dibujar()`, el programa identifica el tipo real del objeto y ejecuta el método `Dibujar()` correspondiente. Si es un `Circulo`, usa el método de `Circulo`, y si es un `Rectangulo`, usa el de `Rectangulo`.
Pienso que esto funciona gracias a que `Dibujar()` está definido como `abstract` en `Figura` y luego cada clase lo implementa con `override`.

# Imagina que eres un diseñador de lenguajes de programación. Tienes que decidir cómo implementar estos conceptos en la memoria y en el procesador. No hay respuestas incorrectas, solo ideas. Dibuja si te ayuda.

1. Memoria y herencia: cuando creas un objeto `Rectangulo`, este tiene Base, Altura y también Nombre. ¿Cómo te imaginas que se organizan esos tres datos en la memoria del computador para formar un solo objeto?
2. El mecanismo del polimorfismo: pensemos de nuevo en la llamada `fig.Dibujar()`. El compilador solo sabe que fig es una Figura. ¿Cómo decide el programa, mientras se está ejecutando, si debe llamar al Dibujar del Circulo o al del Rectangulo? Lanza algunas ideas o hipótesis.
3. La barrera del encapsulamiento: ¿Cómo crees que el compilador logra que no puedas acceder a un miembro private desde fuera de la clase? ¿Es algo que se revisa cuando escribes el código, o es una protección que existe mientras el programa se ejecuta? ¿Por qué piensas eso?

1. **Memoria y herencia**
Yo me imagino que cuando se crea un objeto `Rectangulo`, todos sus datos quedan almacenados juntos en una zona de memoria. Aunque `Nombre` venga de la clase `Figura`, sigue formando parte del objeto `Rectangulo`.
Podría imaginarlo así:
```text
Objeto Rectangulo
-----------------
Nombre = "Rectángulo"
Base   = 4.0
Altura = 6.0
-----------------
```
Es decir, la herencia hace que el objeto tenga tanto los datos de su clase padre como los datos propios de su clase.


2. **El mecanismo del polimorfismo**
Creo que cada objeto guarda de alguna forma información sobre cuál es su tipo real. Entonces, aunque `fig` sea una referencia de tipo `Figura`, el programa puede revisar durante la ejecución si el objeto al que apunta es realmente un `Circulo` o un `Rectangulo`.
Me lo imagino así:
```text
fig
 |
 v
Objeto Rectangulo
Tipo real: Rectangulo
Dibujar() -> Rectangulo.Dibujar()
```
Entonces, cuando se ejecuta `fig.Dibujar()`, el programa consulta qué tipo de objeto hay realmente y busca la versión correcta del método `Dibujar()`.
Otra posibilidad es que cada objeto tenga algo parecido a una tabla donde se guardan las funciones que le corresponden, y el programa busque allí qué método debe ejecutar.

3. **La barrera del encapsulamiento**
Creo que principalmente el compilador revisa los modificadores como `private`, `public` o `protected` antes de ejecutar el programa.
Por ejemplo, si intento hacer esto desde una clase que no tiene permiso:
```csharp
objeto.nombre = "Nuevo nombre";
```
el compilador detectaría que `nombre` es `private` y mostraría un error, evitando que el programa compile.
Pienso que funciona de esta manera porque `private` es una regla del lenguaje que determina desde qué partes del código se puede acceder a una variable o método. Por eso, gran parte de esa protección se revisa durante la compilación, antes de que el programa empiece a ejecutarse.

# Actividad 2

<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/222d3055-f8c3-4b5e-8096-fdd820e3e892" />

Este programa funciona como una simulación de fuegos artificiales hecha en OpenFrameworks. Al iniciar, se abre una ventana donde se muestran diferentes partículas en pantalla.
Cuando el usuario hace clic con el mouse, se crea una partícula desde la parte inferior de la ventana que sube hacia arriba. Esta partícula tiene una dirección, velocidad, color y tiempo de vida. Cuando llega a cierta altura o termina su tiempo, explota y genera varias partículas nuevas.
Las explosiones pueden ser de tres tipos diferentes: circular, aleatoria o en forma de estrella. Cada una tiene un comportamiento y una forma visual distinta. Después de un tiempo, las partículas de la explosión van desapareciendo hasta que son eliminadas del programa.
También se puede presionar la barra espaciadora para generar muchas partículas al mismo tiempo y crear una gran cantidad de fuegos artificiales. Además, al presionar la tecla S se puede guardar una captura de pantalla.
En general, el programa utiliza partículas, herencia y polimorfismo para crear diferentes tipos de fuegos artificiales y controlar su comportamiento en pantalla.

# Actividad 3

 1. Observación de la clase `ofApp`

# Hipótesis antes de ejecutar

Antes de ejecutar el programa, espero encontrar en memoria un objeto de tipo `ofApp`. Dentro de este objeto se encuentra el vector
Este vector no guarda directamente los objetos de las partículas, sino punteros a objetos que se crean dinámicamente con `new`.
Por eso, inicialmente espero que el vector esté vacío y que, cuando se creen partículas, el vector empiece a almacenar direcciones de memoria que apuntan a objetos como RisingParticle, CircularExplosion, RandomExplosio o StarExplosion
También espero que estos objetos estén almacenados en el heap, ya que son creados usando `new`.

### ¿Qué puedo observar al ejecutar?

Al utilizar el depurador en las ventanas **Locals** o **Autos**, puedo observar el objeto `ofApp` y dentro de este el vector `particles`.

Antes de crear partículas, el tamaño del vector es 0. Después de hacer clic o crear partículas, puedo observar que el tamaño aumenta y aparecen diferentes direcciones de memoria dentro del vector.

El depurador permite ver información como:

* El tamaño actual del vector.
* La capacidad del vector.
* Las direcciones almacenadas en `particles`.
* El tipo de objeto al que apunta cada puntero.
* Los atributos que tiene cada partícula.
* Las direcciones donde se encuentran los objetos en memoria.

Por ejemplo, un elemento del vector puede ser un `Particle*`, pero realmente apuntar a un objeto de tipo `RisingParticle` o `CircularExplosion`.

### Conclusión

Puedo concluir que `particles` funciona como un contenedor de punteros polimórficos. Todos los elementos son tratados como `Particle*`, pero los objetos reales pueden pertenecer a diferentes clases derivadas.

Los objetos son creados dinámicamente en memoria, por lo que es importante utilizar `delete` cuando dejan de utilizarse. De lo contrario, se producirían fugas de memoria.

---

# 2. Objeto `CircularExplosion` en memoria

Para poder capturar más fácilmente un objeto `CircularExplosion`, hice una modificación temporal para evitar que el tipo de explosión fuera completamente aleatorio.

Por ejemplo, en lugar de:

```cpp
int explosionType = (int)ofRandom(3);
```

se puede colocar temporalmente:

```cpp
int explosionType = 0;
```

De esta manera todas las explosiones generadas son `CircularExplosion`.

Después se puede colocar un breakpoint cuando se crea el objeto:

```cpp
particles.push_back(
    new CircularExplosion(
        particles[i]->getPosition(),
        particles[i]->getColor()
    )
);
```

Así es más fácil detener la ejecución y observar el objeto con el depurador.

## Jerarquía de `CircularExplosion`

La jerarquía de clases es:

```text
Particle
   ↑
ExplosionParticle
   ↑
CircularExplosion
```

Esto quiere decir que un `CircularExplosion` también contiene todo lo que pertenece a `ExplosionParticle` y a `Particle`.

Al abrir el objeto con el depurador se puede observar algo parecido a:

```text
CircularExplosion
└── ExplosionParticle
    ├── Particle
    │   └── _vtable
    ├── position
    ├── velocity
    ├── color
    ├── age
    ├── lifetime
    └── size
```

`CircularExplosion` no agrega atributos propios. Principalmente modifica el comportamiento del objeto mediante su constructor y su método `draw()`.

### ¿Qué puedo observar en memoria?

En la ventana **Locals** puedo ver los atributos de la explosión de una forma más fácil de interpretar.

Por ejemplo:

```text
position
velocity
color
age
lifetime
size
```

`position` contiene las coordenadas X y Y actuales de la partícula.

`velocity` contiene la velocidad en X y Y que determina hacia dónde se está moviendo.

`color` contiene el color de la partícula.

`age` indica cuánto tiempo lleva existiendo.

`lifetime` indica cuánto tiempo puede existir antes de ser eliminada.

`size` determina el tamaño con el que se dibuja.

En la ventana **Memory 1** esta información ya no aparece organizada con nombres, sino como bytes almacenados consecutivamente en memoria.

Por ejemplo, valores como:


se pueden encontrar representados en memoria según la representación binaria de un número `float`.

Por esta razón, la ventana **Locals** facilita entender los datos, mientras que **Memory 1** permite observar cómo están almacenados físicamente.

### Conclusión

Puedo concluir que un objeto derivado contiene en memoria la información necesaria de sus clases base.
Un `CircularExplosion` no es un objeto completamente separado de `ExplosionParticle` y `Particle`. En memoria, esas clases forman parte del mismo objeto.
La herencia que vemos en el código también tiene una representación concreta en memoria.

---

# 3. Métodos virtuales y `_vtable`

Al observar nuevamente el objeto `CircularExplosion`, se puede ver que primero aparece la parte correspondiente a `ExplosionParticle`.
Dentro de `ExplosionParticle` aparece la parte correspondiente a `Particle`.
Finalmente, al abrir `Particle`, aparece un campo relacionado con la tabla virtual, como `_vtable` o un puntero similar dependiendo del compilador.
Esto aparece porque `Particle` tiene funciones virtuales, por ejemplo:
cpp
virtual void update(float dt) = 0;
virtual void draw() = 0;
virtual bool isDead() const = 0;
virtual bool shouldExplode() const;
virtual glm::vec2 getPosition() const;
virtual ofColor getColor() const;
```
La tabla virtual es una estructura que contiene direcciones hacia las funciones virtuales correspondientes al tipo real del objeto.
Esto permite que ocurra el polimorfismo.
Por ejemplo, el programa puede tener:
cpp
Particle* p;

y ese puntero puede apuntar realmente a:
cpp
CircularExplosion

Cuando se ejecuta:

```cpp
p->draw();
```

el programa necesita saber qué versión de `draw()` debe ejecutar.

### ¿Qué puedo observar en la tabla virtual?
Con el depurador se pueden observar direcciones de memoria que corresponden a diferentes funciones virtuales.
Dependiendo de Visual Studio y de la versión del compilador, los nombres pueden mostrarse de manera diferente, pero estas direcciones permiten al programa decidir qué implementación de una función debe ejecutar.



