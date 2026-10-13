#include <iostream>
using namespace std;

// Swap por valor: no modifica las variables originales
void swapPorValor(int a, int b) {
    cout << "Dentro de swapPorValor, valores iniciales: a = " << a << ", b = " << b << endl;

    int temp = a;
    a = b;
    b = temp;

    cout << "Dentro de swapPorValor, valores intercambiados: a = " << a << ", b = " << b << endl;
}

// Swap por referencia
void swapPorReferencia(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Swap por puntero
void swapPorPuntero(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10;
    int y = 20;

    cout << "Valores originales en main: x = " << x << ", y = " << y << endl;

    cout << "\nLlamando a swapPorValor(x, y)..." << endl;
    swapPorValor(x, y);
    cout << "Después de swapPorValor, en main: x = " << x << ", y = " << y << endl;

    cout << "\nLlamando a swapPorReferencia(copiaX, copiaY)..." << endl;
    int copiaX = x;
    int copiaY = y;

    swapPorReferencia(copiaX, copiaY);

    cout << "Después de swapPorReferencia, copias: copiaX = " << copiaX << ", copiaY = " << copiaY << endl;
    cout << "Valores originales en main: x = " << x << ", y = " << y << endl;

    cout << "\nLlamando a swapPorPuntero(&copiaX2, &copiaY2)..." << endl;
    int copiaX2 = x;
    int copiaY2 = y;

    swapPorPuntero(&copiaX2, &copiaY2);

    cout << "Después de swapPorPuntero, copias: copiaX2 = " << copiaX2 << ", copiaY2 = " << copiaY2 << endl;
    cout << "Valores originales en main: x = " << x << ", y = " << y << endl;

    return 0;
}



