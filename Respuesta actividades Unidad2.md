# Diario de la unidad 2
Actividad 4:
Experimento 1
``` js
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
		// Variable local (stack)
		int a = 10;
		int b = 20;
    /**********************************************************
    EXPERIMENTO 1
    ***********************************************************/
    void* ptr = reinterpret_cast<void*>(&main);
    cout << "Voy a modificar la memoria en la dirección: " << ptr << endl;
    *reinterpret_cast<int*>(ptr) = 0;
    /********************************************************/
    return 0;
    }



El programa obtiene la dirección de memoria de la función main() e intenta modificar los primeros bytes de su código escribiendo un 0. Esto provoca normalmente una violación de acceso, ya que el código ejecutable se encuentra en una región de memoria protegida contra escritura. Además, modificar directamente la memoria de una función produce comportamiento indefinido en C++.
```
Experimento 2
``` js
#include <iostream>
#include <cstdlib>
using namespace std;
// Constante global
const char* const mensaje_ro = "Hola, memoria de solo lectura";

int main() {
		// Variable local (stack)
		int a = 10;
		int b = 20;

    /**********************************************************
    EXPERIMENTO 2
    ***********************************************************/
    char* ptr = (char*)&mensaje_ro;
    cout << "Voy a modificar la memoria en la dirección: " << ptr << endl;
    *ptr = 0;
    /********************************************************/
    return 0;
    }

El programa intenta modificar una variable que fue declarada como constante, es decir, que en teoría no debería cambiar. Al forzar el acceso con un puntero e intentar cambiar su contenido, el programa puede generar un error porque está tratando de escribir en una parte de la memoria que está protegida. Por eso puede cerrarse o mostrar una violación de acceso.



```
Experimento 3
``` js
#include <iostream>
#include <cstdlib>
using namespace std;
// Variables globales
int global_inicializada = 42;
int global_no_inicializada;

int main() {    // Variable local (stack)
		int a = 10;
		int b = 20;

    /**********************************************************
    EXPERIMENTO 3
    ***********************************************************/
    cout << "global_inicializada: " << global_inicializada << endl;
    cout << "global_no_inicializada: " << global_no_inicializada << endl;

    global_inicializada = 69;
    global_no_inicializada = 666;
    cout << "global_inicializada: " << global_inicializada << endl;
    cout << "global_no_inicializada: " << global_no_inicializada << endl;
    /********************************************************/
    return 0;
    }

El programa muestra primero los valores iniciales de las variables globales. La que no fue inicializada toma automáticamente el valor 0. Luego ambas variables cambian de valor sin generar errores, porque las variables globales normales sí pueden modificarse durante la ejecución del programa.

```
Experimento 4
``` js

#include <iostream>
#include <cstdlib>
using namespace std;
// Función de ejemplo que muestra la dirección de su variable local estática
void funcionConStatic() {
		static int var_estatica = 100;
		cout << "Dirección de var_estatica (static): " << &var_estatica << endl;
}

int main() {    // Variable local (stack)
		int a = 10;
		int b = 20;
    /**********************************************************
    EXPERIMENTO 4
    ***********************************************************/
    var_estatica = 42;
    cout << "var_estatica: " << var_estatica << endl;
    /********************************************************/
    return 0;
    }

- ¿Qué ocurre? ¿Por qué?


- ¿Qué pasa con las variables cada que entras y sales de la función?

- En relación a la pregunta anterior ¿Qué pasa con las variables locales estáticas?

El programa da error porque var_estatica está declarada dentro de una función y no se puede acceder a ella directamente desde main. Las variables locales normales se crean cuando entramos a una función y desaparecen cuando salimos. En cambio, las variables locales estáticas conservan su valor aunque la función termine, por lo que cuando volvemos a entrar siguen teniendo el valor que tenían anteriormente.



```
Experimento 5
``` js

#include <iostream>
#include <cstdlib>
using namespace std;
// Función de ejemplo que muestra la dirección de su variable local estática
void funcionConStatic() {
		static int var_estatica = 100;
		cout << "var_estatica: " << var_estatica << endl;
		var_estatica++;
}

void funcionSinStatic() {
		int var_no_estatica = 100;
		cout << "var_no_estatica: " << var_no_estatica << endl;
		var_no_estatica++;
}

int main() {    // Variable local (stack)
		int a = 10;
		int b = 20;
    /**********************************************************
    EXPERIMENTO 5
    ***********************************************************/
    for (int i = 0; i < 5; i++) {
		    cout << "Iteración " << i << endl;
		    funcionSinStatic();
		    funcionConStatic();
		}
    /********************************************************/
    return 0;
    }

- ¿Qué ocurre? ¿Por qué?
- Ves alguna diferencia entre las variables locales estáticas y no estáticas?
- ¿Qué pasa con las variables cada que entras y sales de la función?

Se nota que la variable no estática siempre muestra 100, porque se vuelve a crear cada vez que se llama la función. En cambio, la variable estática conserva su valor y va aumentando en cada llamada. Las variables locales normales desaparecen al salir de la función, mientras que las estáticas permanecen guardadas durante toda la ejecución del programa.
```
Experimento 6
``` js
#include <iostream>
using namespace std;
int main() {    // Tamaño del arreglo dinámico
		int tam = 5;
    // Asignar memoria en el Heap para un arreglo de enteros
    int* arrayHeap = new int[tam];
    // Inicializar y mostrar los valores y direcciones de memoria
    for (int i = 0; i < tam; i++) {
		    arrayHeap[i] = (i + 1) * 10;
		    cout << "arrayHeap[" << i << "] = " << arrayHeap[i] << " en dirección " << (arrayHeap + i) << endl;
		    }
    // Liberar la memoria asignada en el Heap
    delete[] arrayHeap;
    /**********************************************************
    EXPERIMENTO 6
    ***********************************************************/
    cout << arrayHeap[0] << endl;

    /********************************************************/
    return 0;
    }

- ¿Qué ocurre? ¿Por qué?
- Comenta la línea de genera el error y analiza las siguientes preguntas:
    - ¿Qué diferencias notas entre el comportamiento y la gestión del `Heap` en comparación con el `Stack`?
    - ¿Qué consecuencias tendría no liberar la memoria reservada con `new`?
    - ¿Por qué es importante usar `delete[]` al liberar memoria asignada para un arreglo?


Después de usar delete[], la memoria del arreglo ya fue liberada, por lo que intentar acceder nuevamente a arrayHeap[0] puede dar un valor incorrecto o generar un error. A diferencia del Stack, la memoria del Heap debe manejarse manualmente. Si no se libera, se puede producir una fuga de memoria. También es importante usar delete[] porque la memoria fue reservada para un arreglo y no para una sola variable.


```

Respuestas actividad 5:
``` js

EN C++

#include <iostream>
#include <string>
using namespace std;
class Punto {
		public:   string name;
							int x;
							int y;
    // Constructor
    Punto(string _name, int _x, int _y) : name(_name),x(_x), y(_y) {
		    cout << "Constructor: Punto "<< name <<" (" << x << ", " << y << ") creado." << endl;
		    }
    // Destructor
    ~Punto() {
		    cout << "Destructor: Punto " << name << "(" << x << ", " << y << ") destruido." << endl;
		    }
    // Método para imprimir valores
    void imprimir() {
		    cout << "Punto "<< name << "(" << x << ", " << y << ")" << endl;
		    }
	};

int main() {    // Objeto original
		Punto original("original",70, 80);
		original.imprimir();
		Punto* p = &original;
    // Copia del objeto
    Punto copia = original;
    copia.name = "copia";
    copia.x = 100;
    copia.y = 200;
    copia.imprimir();
    original.imprimir();
    p->name = "p";
    p->x = 300;
    p->y = 400;
    p->imprimir();
    original.imprimir();
    return 0;
    }

EN C#
using System;
public class Punto{
		public int x;
		public int y;
		public string name;
    // Constructor
    public Punto(string _name, int _x, int _y)    {
		    name = _name;
		    x = _x;
		    y = _y;
		    Console.WriteLine($"Constructor: Punto {name}({x}, {y}) creado.");
		}
    // Método para imprimir valores
    public void Imprimir()    {
		    Console.WriteLine($"Punto {name}({x}, {y})");
		    }
		}

class Program{
				static void Main(string[] args)    {
				// Objeto original
				Punto original = new Punto("original",70, 80);
				original.Imprimir();
        Punto copia = original;
        copia.name = "copia";
        copia.x = 100;
        copia.y = 200;
        copia.Imprimir();
        original.Imprimir();
        // Coloca breakpoints en la creación de 'original' y en la línea de la copia.
        // Observa que 'copia' es una copia independiente de 'original'. ¿Lo es?
        }
    }


1. Explica qué ocurre al copiar un objeto en C++ y en C#. ¿Qué diferencias encuentras?
2. ¿Qué es `copia` en C++ y en C#? ¿Es una copia independiente de `original`?

En C++, copia es un nuevo objeto creado copiando los valores de original. Sí, es independiente. Si modificas copia, original no cambia.

En C#, copia es una segunda referencia al mismo objeto. No es independiente. Si modificas el objeto usando copia, también ves ese cambio desde original.

```
Actividad Integradora de investigacion

``` js
CODIGO:
#include <iostream>
int contador_global = 100;
void ejecutarContador() {
		static int contador_estatico = 0;
		contador_estatico++;
		std::cout << "  -> Llamada a ejecutarContador. Valor de contador_estatico: " << contador_estatico << std::endl;
}

void sumaPorValor(int a) {
		a = a + 10;
		std::cout << "  -> Dentro de sumaPorValor, 'a' ahora es: " << a << std::endl;
}
void sumaPorReferencia(int& a) {
		a = a + 10;    std::cout << "  -> Dentro de sumaPorReferencia, 'a' ahora es: " << a << std::endl;
}
void sumaPorPuntero(int* a) {
		*a = *a + 10;
		std::cout << "  -> Dentro de sumaPorPuntero, '*a' ahora es: " << *a << std::endl;
}
int main() {
		int val_A = 20;
		int val_B = 20;
		int val_C = 20;
    std::cout << "--- Experimento con paso de parámetros ---" << std::endl;
    std::cout << "Valor inicial de val_A: " << val_A << std::endl;
    sumaPorValor(val_A);
    std::cout << "Valor final de val_A: " << val_A << std::endl << std::endl;
    std::cout << "Valor inicial de val_B: " << val_B << std::endl;
    sumaPorReferencia(val_B);
    std::cout << "Valor final de val_B: " << val_B << std::endl << std::endl;
    std::cout << "Valor inicial de val_C: " << val_C << std::endl;
    sumaPorPuntero(&val_C);
    std::cout << "Valor final de val_C: " << val_C << std::endl << std::endl;
    std::cout << "--- Experimento con variables estáticas ---" << std::endl;
    ejecutarContador();
    ejecutarContador();
    ejecutarContador();
    return 0;
}
**A. Predicción (sin ejecutar el código):**

1. ¿Cuál será la salida final en la consola de este programa?
 Experimento con paso de parámetros 
Valor inicial de val_A: 20
  -> Dentro de sumaPorValor, 'a' ahora es: 30
Valor final de val_A: 20

Valor inicial de val_B: 20
  -> Dentro de sumaPorReferencia, 'a' ahora es: 30
Valor final de val_B: 30

Valor inicial de val_C: 20
  -> Dentro de sumaPorPuntero, '*a' ahora es: 30
Valor final de val_C: 30

 Experimento con variables estáticas
  -> Llamada a ejecutarContador. Valor de contador_estatico: 1
  -> Llamada a ejecutarContador. Valor de contador_estatico: 2
  -> Llamada a ejecutarContador. Valor de contador_estatico: 3

2. Escribe la salida completa que esperas.
Inicialmente:
int val_A = 20;
int val_B = 20;
int val_C = 20;
Los tres comienzan con valor 20.

val_A — paso por valor
Se llama:
sumaPorValor(val_A);
La función recibe: void sumaPorValor(int a) Aquí a es una copia de val_A. Entonces:a = a + 10; hace que:a = 30 pero val_A continúa siendo:20Por eso aparece: Dentro de sumaPorValor, 'a' ahora es: 30
Valor final de val_A: 20
val_B — paso por referencia
Se llama:
sumaPorReferencia(val_B);
y la función recibe:
void sumaPorReferencia(int& a)
El & significa que a funciona como una referencia a la misma variable val_B.
Por eso:
a = a + 10;
modifica directamente:
val_B
Entonces:
20 + 10 = 30
Al regresar a main:
val_B = 30
val_C — paso mediante puntero
La llamada es:
sumaPorPuntero(&val_C);
&val_C significa:
obtener la dirección de memoria de val_C.
La función recibe esa dirección:
void sumaPorPuntero(int* a)
Por eso a es un puntero.
Cuando hacemos:
*a
estamos accediendo al valor almacenado en la dirección apuntada.
Entonces:
*a = *a + 10;
en realidad está modificando val_C.
Por eso:
val_C = 30
3. Dibuja un mapa de memoria conceptual de este programa justo antes de que `main` finalice. Debes indicar en qué segmento de memoria (Stack, Heap, Datos Globales/Estáticos, Código) se encontraría cada una de las siguientes variables: `contador_global`, `contador_estatico`, `val_A`, `val_B`, `val_C` (dentro de main), el parámetro a de la función `sumaPorValor`, la función main misma.
**B. Verificación y análisis (usando el depurador):**
Ejecuta el programa paso a paso (F10) con un `breakpoint` al inicio de `main`.
                   MEMORIA DEL PROGRAMA
┌───────────────────────────────────────────────────────────┐
│                       CÓDIGO                              │
│                                                           │
│  main()                                                   │
│  ejecutarContador()                                       │
│  sumaPorValor()                                           │
│  sumaPorReferencia()                                      │
│  sumaPorPuntero()                                         │
│                                                           │
└───────────────────────────────────────────────────────────┘


┌───────────────────────────────────────────────────────────┐
│              DATOS GLOBALES / ESTÁTICOS                  │
│                                                           │
│  contador_global                                          │
│  valor = 100                                              │
│                                                           │
│  contador_estatico                                        │
│  valor = 3                                                │
│                                                           │
└───────────────────────────────────────────────────────────┘


┌───────────────────────────────────────────────────────────┐
│                         HEAP                              │
│                                                           │
│             No se usa explícitamente                     │
│             en este programa.                            │
│                                                           │
│       No existe ningún new / malloc / etc.                │
│                                                           │
└───────────────────────────────────────────────────────────┘


┌───────────────────────────────────────────────────────────┐
│                         STACK                             │
│                                                           │
│               Frame de main                              │
│                                                           │
│     val_A = 20                                            │
│     val_B = 30                                            │
│     val_C = 30                                            │
│                                                           │
└───────────────────────────────────────────────────────────┘

4. Compara la salida real con tu predicción. Si hubo diferencias, explica por qué ocurrieron. Evidencia clave: capturas de pantalla antes y después de los puntos de interés (¿Cuáles son esos puntos? -> tu tarea analizarlo).
5. Describe qué demuestran estas capturas sobre la diferencia entre los diferentes tipos de paso por parámetros analizados.
6. Explica con tus propias palabras el comportamiento de contador_estatico. ¿Por qué “recuerda” su valor entre llamadas a la función ejecutarContador? ¿En qué se diferencia de una variable local normal?


```

ACTIVIDAD 6 APPLY: aplicacion
``` js
CODIGO C++
#include <iostream>
using namespace std;
class Punto {
		public:   int x;
							int y;
    // Constructor
    Punto(int _x, int _y) : x(_x), y(_y) {
		    cout << "Constructor: Punto(" << x << ", " << y << ") creado." << endl;
		    }
    // Destructor
    ~Punto() {
		    cout << "Destructor: Punto(" << x << ", " << y << ") destruido." << endl;
		    }
    // Método para imprimir valores
    void imprimir() {
		    cout << "Punto(" << x << ", " << y << ")" << endl;
		    }
		};
int main() {
		// Coloca un breakpoint en la siguiente línea
		Punto p(10, 20);
    // Muestra el contenido del objeto
    p.imprimir();
    // Utiliza el depurador para inspeccionar 'p', observa la dirección de memoria y el valor de x e y.
    return 0;
    }

CODIGO C#
using System;
public class Punto{
		public int x;
		public int y;
    public Punto(int _x, int _y)    {
		    x = _x;
		    y = _y;
		    Console.WriteLine($"Constructor: Punto({x}, {y}) creado.");
		}
    ~Punto()    {
		    Console.WriteLine($"Destructor: Punto({x}, {y}) destruido.");
		}
    public void Imprimir()    {
		    Console.WriteLine($"Punto({x}, {y})");
		    }
		}
class Program{
		static void Main(string[] args)    {
		Punto p = new Punto(10, 20);
		p.Imprimir();
		}
}


1. ¿Cuál es la diferencia entre un constructor y un destructor en C++?
El constructor es un método especial que se ejecuta automáticamente cuando se crea un objeto. Sirve principalmente para inicializar sus variables.
El destructor, en cambio, se ejecuta automáticamente cuando el objeto deja de existir. Sirve para hacer limpieza o liberar recursos.

2. ¿Cuál es la diferencia entre un objeto y una clase en C++?
Una clase es como una plantilla que define qué datos y comportamientos tendrán sus objetos.
Un objeto es una instancia concreta creada a partir de esa clase.
3. ¿Qué diferencia notas entre el objeto Punto en C++ y C#?
La diferencia principal en estos dos códigos es cómo se crea y se maneja el objeto.
en c++ p es directamente el objeto.
en c# p no contiene directamente el objeto. p contiene una referencia hacia un objeto Punto creado en memoria.
4. ¿Qué es `p` en C++ y qué es `p` en C#? (en uno de ellos `p` es un objeto y en el otro es una referencia a un objeto).
en c++ es un objeto
Es decir, la variable p contiene directamente los datos
en c# es una referencia del objeto
guarda una referencia que permite acceder a él.
5. ¿En qué parte de memoria se almacena `p` en C++ y en C#?
En c++
p es una variable local de main, por lo tanto normalmente se encuentra en el Stack.
en c#
p es una referencia; el objeto Punto está en el Heap
6. ¿Qué observaste con el depurador acerca de `p`? Según lo que observaste ¿Qué es un objeto en C++?
Con el depurador observé que p contiene directamente los valores x = 10 y y = 20 y que tiene una dirección de memoria propia. Esto demuestra que en C++ p es un objeto real de la clase Punto, y no simplemente una referencia hacia otro objeto.




```
Actividad 7: Objetos en el heap: creación y observación

``` js
CODIGO:
#include <iostream>
using namespace std;
class Punto {
		public:    int x;    int y;
    // Constructor
    Punto(int _x, int _y) : x(_x), y(_y) {
		    cout << "Constructor: Punto(" << x << ", " << y << ") creado." << endl;
		    }
    // Destructor
    ~Punto() {
		    cout << "Destructor: Punto(" << x << ", " << y << ") destruido." << endl;
		    }
    // Método para imprimir valores
    void imprimir() {
		    cout << "Punto(" << x << ", " << y << ")" << endl;
		    }
		};
int main() {
		// Objeto en el stack
		Punto pStack(30, 40);
		pStack.imprimir();
    // Objeto en el heap
    Punto* pHeap = new Punto(50, 60);
    pHeap->imprimir();
    // Coloca breakpoints en la creación de pStack y pHeap
    // Inspecciona las direcciones de memoria de ambos objetos:
    // - pStack: dirección obtenida directamente.
    // - pHeap: la variable pHeap es un puntero que contiene la dirección del objeto en el heap.
    // Recuerda liberar la memoria del heap
    delete pHeap;
    return 0;
}

1. Explicación de la diferencia entre objetos creados en el stack y en el heap.
Un objeto creado en el Stack se almacena automáticamente en la memoria local de la función y se destruye cuando termina su alcance. En cambio, un objeto creado en el Heap se reserva dinámicamente con `new` y permanece en memoria hasta que se libera con `delete`. En este programa `pStack` está en el Stack y el objeto al que apunta `pHeap` está en el Heap.
2. `pStack` ¿Es un objeto o una referencia a un objeto?
`pStack` es directamente un objeto de la clase `Punto`. Contiene sus propios valores `x = 30` y `y = 40` y está almacenado en el Stack.
3. `pHeap` ¿Es un objeto o una referencia a un objeto? Si es una referencia, ¿A qué objeto hace referencia?
`pHeap` no es el objeto, sino un puntero. Este puntero almacena la dirección de memoria del objeto `Punto(50, 60)` que fue creado dinámicamente en el Heap mediante `new`.
4. Observa en Memory1 (Debug->Windows->Memory->Memory1) el contenido de la dirección de memoria de `pHeap`, recuerda escribir en la entrada de texto de Memory1 la dirección de memoria de `&pHeap` y presionar Enter. Compara el contenido de memoria con el contenido de `pHeap` en la pestaña de Locals (Debug->Windows->Locals). ¿Qué observas? ¿Qué significa esto?
Al observar &pHeap en Memory1, se puede ver que en esa posición de memoria está almacenado el valor que aparece en pHeap dentro de Locals. Esto ocurre porque pHeap es un puntero: la variable se encuentra en el Stack, pero su contenido es la dirección del objeto Punto creado en el Heap. Por lo tanto, &pHeap representa la dirección del puntero y pHeap representa la dirección del objeto al que apunta.

```
