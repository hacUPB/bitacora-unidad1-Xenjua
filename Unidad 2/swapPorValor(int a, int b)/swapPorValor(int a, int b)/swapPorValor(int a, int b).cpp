#include <iostream>
using namespace std;

// Función que modifica el parámetro pasado por valor
void swapPorValor(int a, int b, int z) {
    cout << "Dentro de modificarPorValor, valor inicial: " << z << endl;
    z=b;
    cout << "Dentro de modificarPorValor, valor modificado: " << b << endl;
    cout << "Dentro de modificarPorValor, valor inicial: " << b << endl;
    b = a;
    cout << "Dentro de modificarPorValor, valor modificado: " << a << endl;
    cout << "Dentro de modificarPorValor, valor inicial: " << a << endl;
    a = z;
    cout << "Dentro de modificarPorValor, valor modificado: " << z << endl;
}
}

// Función que modifica el parámetro pasado por referencia
void swapPorReferencia(int& n) {
    cout << "Dentro de modificarPorReferencia, valor inicial: " << n << endl;
    n += 5;
    cout << "Dentro de modificarPorReferencia, valor modificado: " << n << endl;
}

// Función que modifica el parámetro utilizando punteros
void swapPorPuntero(int* n) {
    cout << "Dentro de modificarPorPuntero, valor inicial: " << *n << endl;
    *n += 5;
    cout << "Dentro de modificarPorPuntero, valor modificado: " << *n << endl;
}

int main() {
    int a = 7;    int b = 5;    int c = 10; int z = 0;
    cout << "Valor inicial de a (paso por valor): " << a << endl;
    cout << "Valor inicial de b (paso por referencia): " << b << endl;
    cout << "Valor inicial de c (paso por puntero): " << c << endl;
    cout << "\nLlamando a modificarPorValor(a)..." << endl;
    swapPorValor(a, b, z);
    cout << "Después de modificarPorValor, valor de a: " << a << endl;
    cout << "\nLlamando a modificarPorReferencia(b)..." << endl;
    swapPorReferencia(b);
    cout << "Después de modificarPorReferencia, valor de b: " << b << endl;
    cout << "\nLlamando a modificarPorPuntero(&c)..." << endl;
    swapPorPuntero(&c);
    cout << "Después de modificarPorPuntero, valor de c: " << c << endl;
    return 0;
}
