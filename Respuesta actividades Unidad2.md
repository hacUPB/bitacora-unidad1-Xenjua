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
