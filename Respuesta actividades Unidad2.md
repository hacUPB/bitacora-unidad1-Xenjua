# Diario de la unidad 2

Respuestas actividad 5:
``` js
1. Explica qué ocurre al copiar un objeto en C++ y en C#. ¿Qué diferencias encuentras?
2. ¿Qué es `copia` en C++ y en C#? ¿Es una copia independiente de `original`?

En C++, copia es un nuevo objeto creado copiando los valores de original. Sí, es independiente. Si modificas copia, original no cambia.

En C#, copia es una segunda referencia al mismo objeto. No es independiente. Si modificas el objeto usando copia, también ves ese cambio desde original.

```
