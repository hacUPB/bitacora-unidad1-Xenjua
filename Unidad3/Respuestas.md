#¿Qué es el encapsulamiento para ti? Describe una situación en la que te haya sido útil o donde hayas visto su importancia.
Para mí, el encapsulamiento es proteger los datos internos de una clase y permitir que se acceda a ellos únicamente mediante métodos controlados. Por ejemplo, en el proyecto del hotel fue útil para evitar que cualquier parte del programa modificara directamente el precio o el estado de una habitación. En lugar de hacerlo libremente, se usaron métodos get y set que podían validar los nuevos valores. Así se reducen errores y el código queda más seguro y organizado.

#¿Qué es la herencia? ¿Por qué un programador decidiría usarla? Da un ejemplo simple.
La herencia es un principio de la programación orientada a objetos que permite crear una clase nueva a partir de otra existente. La clase hija obtiene los atributos y métodos de la clase padre.
Un programador la usaría para reutilizar código, evitar repeticiones y organizar mejor las clases que comparten características.
Por ejemplo, en un sistema de hotel:
Administrador hereda de Usuario, por lo que puede usar nombre e IniciarSesion(), además de tener su propia función GenerarReporte().

#¿Qué es el polimorfismo? Describe con tus palabras qué significa que un código sea “polimórfico”.

El polimorfismo permite que diferentes objetos utilicen un mismo método pero se comporten de manera diferente. Un código polimórfico puede trabajar con varios tipos de objetos de forma más flexible y reutilizable.
