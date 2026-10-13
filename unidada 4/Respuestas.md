# Actividad 1

## Captura del ejemplo funcionando
**<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/ff4c3641-16a7-43ab-a5c2-734acdb8e124" />
**
## Que preguntas me surgen?

Qué función cumplen GLFW y GLAD? 
Por qué necesitamos utilizar ambas bibliotecas para crear una ventana y dibujar un triángulo?
 Qué son los shaders y cómo funcionan? 
 Me gustaría entender por qué necesitamos un vertex shader y un fragment shader, y qué hace cada uno.
 Para qué sirven el VAO y el VBO? 
 ¿Por qué debemos almacenar los vértices del triángulo en estos objetos antes de dibujarlo? 
 Cómo funciona el sistema de coordenadas de OpenGL?
 Quisiera saber cómo se determina la posición y el tamaño del triángulo dentro de la ventana.
 Cómo podríamos modificar el código para crear figuras más complejas?
 Me gustaría investigar cómo dibujar cuadrados, círculos o incluso figuras en 3D.

 

---

# Actividad 2

## ¿Qué se necesita para que un programa OpenGL funcione en Windows?

OpenGL no es una aplicación completa, sino una API que permite enviar instrucciones gráficas a la GPU. En Windows, las piezas principales se conectan así:

- **GLFW** crea la ventana, solicita el contexto OpenGL y procesa eventos del teclado, el mouse y el cambio de tamaño. Su ventaja es que oculta buena parte de las diferencias entre Windows, Linux y macOS.
- **opengl32.lib** es la biblioteca de Windows usada durante el enlace. Permite iniciar OpenGL y acceder a sus funciones básicas, pero por sí sola solo expone directamente la interfaz antigua de OpenGL 1.1.
- **Los drivers de la GPU** contienen la implementación real de las funciones modernas de OpenGL. También traducen las órdenes de OpenGL al trabajo que ejecuta el hardware concreto.
- **GLAD** carga, durante la ejecución, las direcciones de las funciones modernas desde el driver. Para usarlo se agregan sus encabezados y `glad.c`, y se llama a `gladLoadGLLoader` después de hacer actual el contexto.
- **GLM** es una biblioteca de matemáticas. Aporta vectores, matrices y transformaciones útiles para gráficos 2D y 3D. Es de cabecera, por lo que no necesita una DLL, y no es obligatoria para iniciar OpenGL.

En pocas palabras, GLFW prepara la ventana y el contexto; `opengl32.lib` permite enlazar el inicio de OpenGL en Windows; el driver aporta la implementación moderna; GLAD encuentra y expone esas funciones; y GLM ayuda a hacer las operaciones matemáticas. Además, `glfw3.lib` se usa al enlazar y `glfw3.dll` debe estar disponible al ejecutar el programa.

---

# Actividad 3

## Experimento con `glViewport`

`glViewport(x, y, ancho, alto)` define el rectángulo del framebuffer al que se transforman las coordenadas normalizadas de OpenGL.

- Con `glViewport(0, bufferHeight / 2, bufferWidth / 2, bufferHeight / 2)`, el triángulo debe aparecer en el cuadrante superior izquierdo y ocupar solo media anchura y media altura del framebuffer.
- Al dividir el ancho o el alto por 2 o por 4, la imagen se comprime dentro de una región menor. Si se cambia solo una dimensión, el triángulo se deforma porque cambia la relación de aspecto.
- Al multiplicar las dimensiones por 2 o por 4, parte del viewport queda fuera del framebuffer; solo se ve la porción que coincide con él y el resto queda recortado.
- Cambiar `x` e `y` desplaza el área de dibujo dentro del framebuffer.

Estas son predicciones razonadas a partir del funcionamiento del viewport. No se añade una captura ni se afirma una ejecución que no esté documentada en el repositorio.

## Digestión parcial

Hasta aquí entendí que GLFW crea la ventana y el contexto, es decir, el espacio de trabajo que conserva el estado y los recursos de OpenGL. La GPU es quien realiza el dibujo; OpenGL es la API con la que el programa describe ese trabajo. El resultado de cada cuadro se escribe en el framebuffer, mientras que el viewport indica qué región de ese framebuffer recibirá la imagen. GLAD permite llamar las funciones modernas ofrecidas por el driver. Después se construye el programa de shaders, se cargan los vértices y se entra al game loop, donde se procesan eventos, se limpia el framebuffer, se dibuja y se intercambian los buffers.

Un experimento del tipo “¿qué pasaría si?” sería cambiar el viewport cada segundo entre el framebuffer completo y cada uno de sus cuatro cuadrantes. Espero que el triángulo cambie de tamaño y posición sin modificar sus vértices, porque cambia la transformación final hacia la pantalla y no la geometría almacenada.

## Experimentos con `glDrawArrays`

- `GL_TRIANGLES, 0, 3`: interpreta los tres vértices como un triángulo.
- `GL_LINES, 0, 3`: procesa una línea completa con los dos primeros vértices; el tercer vértice queda sin pareja.
- `GL_POINTS, 0, 3`: muestra tres puntos, uno por vértice, si el tamaño y la configuración permiten verlos.
- `GL_TRIANGLES, 0, 2`: no hay tres vértices suficientes para formar la primitiva, por lo que no se forma el triángulo.
- `GL_TRIANGLES, 0, 4`: se intenta leer un cuarto vértice que no existe en el arreglo configurado. Eso rebasa los datos válidos del VBO y el resultado no debe considerarse definido; no es una forma válida de crear otro triángulo.

Los resultados anteriores describen el comportamiento esperado. Queda pendiente contrastarlos con una ejecución real antes de presentarlos como evidencia experimental.

## Consolidación de conceptos

### 1. ¿Qué es el contexto OpenGL?

Es el espacio de trabajo asociado a una ventana y a un hilo. Conserva el estado de OpenGL y las referencias a recursos como programas de shaders, buffers, texturas y VAO. Las llamadas a OpenGL afectan al contexto que esté activo.

### 2. ¿Cuál es el rol de GLFW y qué ventaja tiene?

GLFW inicializa el entorno, crea la ventana y el contexto, procesa eventos y facilita el intercambio de buffers. Su ventaja es ofrecer una interfaz portable, evitando escribir una implementación distinta para cada sistema operativo.

### 3. ¿Por qué OpenGL necesita un contexto?

Porque las funciones gráficas necesitan saber con qué estado, recursos y superficie de dibujo deben trabajar. En la analogía del taller, OpenGL es el conjunto de instrucciones del artista y el contexto es el taller que contiene el lienzo y las herramientas.

### 4. ¿Qué es el framebuffer y a qué recuerda de las primeras unidades?

Es memoria donde se almacenan los resultados de color y, según la configuración, profundidad y stencil de cada cuadro. Recuerda a la idea de memoria estudiada antes: posiciones que contienen datos, pero aquí esos datos representan la imagen que después se presenta en pantalla.

### 5. ¿Qué relación existe entre viewport y framebuffer?

El framebuffer es la memoria que recibe el resultado; el viewport es el rectángulo dentro de esa memoria al que OpenGL transforma las coordenadas normalizadas. El viewport puede cubrir todo el framebuffer o solo una parte.

### 6. ¿Qué papel tienen los drivers y la GPU?

El driver implementa OpenGL para una GPU concreta y traduce las llamadas de la aplicación a órdenes compatibles con el hardware. La GPU ejecuta los shaders y procesa muchos vértices y fragmentos en paralelo hasta escribir el resultado en el framebuffer.

### 7. ¿Por qué activar VSync?

VSync coordina la presentación de cuadros con la frecuencia del monitor y ayuda a evitar el *tearing*. Sin VSync, una imagen estática puede calcularse y presentarse innecesariamente muchas veces, consumiendo recursos; en una escena dinámica, el monitor puede mostrar partes de cuadros distintos. Activarlo puede introducir algo de latencia y limitar la tasa de cuadros.

### 8. ¿Qué es OpenGL Legacy y cómo se diferencia de OpenGL moderno?

OpenGL Legacy usa el pipeline fijo y funciones antiguas como `glBegin`, `glEnd` y estados predefinidos de transformación e iluminación. OpenGL moderno, especialmente el perfil Core, elimina esas rutas obsoletas y exige shaders, buffers y configuración explícita. Es más flexible y se adapta mejor al funcionamiento de las GPU actuales.

### 9. ¿Qué es el shader program?

Es un objeto enlazado que reúne etapas como el vertex shader y el fragment shader. En OpenGL moderno es esencial porque indica cómo transformar los vértices y cómo calcular el color de los fragmentos. Se activa con `glUseProgram` antes del draw call.

### 10. ¿Qué hace `setupTriangle()`? ¿Qué son VAO y VBO?

La función define los vértices, crea el VAO y el VBO, copia los datos del arreglo al VBO y describe su formato con `glVertexAttribPointer`. El VBO guarda los datos de los vértices en la GPU; el VAO recuerda cómo interpretar esos datos y qué atributos están habilitados.

### 11. ¿Es necesario activar el programa y el VAO en cada iteración?

No, si permanecen activos y no se cambia el estado entre cuadros, se podrían activar antes del loop. Se suelen seleccionar dentro del loop porque una aplicación real dibuja varios objetos con distintos VAO y programas. Repetir la selección en el lugar de uso también hace explícito qué estado necesita cada draw call.

### 12. ¿Por qué es importante `glfwSwapBuffers(mainWindow)`?

Con doble buffering, la GPU dibuja en el buffer trasero mientras el delantero se muestra. `glfwSwapBuffers` presenta el cuadro terminado intercambiando ambos. Si no se llama, el trabajo puede quedar en el buffer trasero y la ventana no mostrar los cuadros nuevos, aunque el programa continúe ejecutando el loop.

---

# Actividad 4

## Diferencia entre CPU y GPU

La CPU tiene pocos núcleos muy versátiles, optimizados para ejecutar tareas secuenciales, tomar decisiones y manejar lógica diversa con poca latencia. La GPU tiene una gran cantidad de unidades de cálculo más simples, pensadas para aplicar operaciones parecidas a muchos datos a la vez. Por eso la CPU organiza el programa y envía trabajo, mientras la GPU resulta especialmente eficiente para transformar vértices, rasterizar primitivas y procesar fragmentos en paralelo.

## Preguntas sobre el pipeline gráfico

### 1. Tres pasos clave

1. **Procesamiento de vértices:** recibe posiciones y otros atributos, y el vertex shader calcula la posición de cada vértice en el espacio de clip.
2. **Ensamblado y rasterización:** forma primitivas con los vértices, las recorta cuando es necesario y determina qué fragmentos podrían cubrir en pantalla.
3. **Procesamiento de fragmentos y salida:** el fragment shader calcula valores como el color; después se aplican pruebas y mezclas, y el resultado aceptado se escribe en el framebuffer.

### 2. Pipeline fijo y programable

En el pipeline fijo, muchas transformaciones, luces y combinaciones estaban definidas por estados y operaciones predeterminadas. En el programable, el desarrollador escribe shaders para decidir cómo procesar los vértices y fragmentos. Esto permite crear materiales, deformaciones y efectos personalizados, aunque obliga a programar al menos el vertex shader y el fragment shader.

### 3. Rasterización

Es la etapa que toma una primitiva geométrica, por ejemplo un triángulo, y determina qué muestras de la pantalla cubre. También interpola entre los vértices los atributos que necesitará el fragment shader.

### 4. Fragmentos y píxeles

Un fragmento es un candidato a contribuir a un píxel y lleva datos como color, profundidad y atributos interpolados. No siempre termina convertido en píxel: puede descartarse por profundidad, recorte, transparencia u otras pruebas. Además, con multimuestreo puede haber varias muestras asociadas a un mismo píxel.

### 5. Z-buffer y depth test

El Z-buffer guarda una profundidad por muestra. El depth test compara la profundidad del fragmento nuevo con la almacenada y decide cuál queda visible. Así se resuelve correctamente la ocultación de superficies sin depender únicamente del orden en el que se dibujen.

### 6. Aliasing y anti-aliasing

El aliasing aparece porque una imagen continua debe representarse con una cuadrícula discreta de píxeles; los bordes diagonales o detalles finos pueden verse escalonados o parpadear. El anti-aliasing toma más muestras o filtra la señal para suavizar esas transiciones.

### 7. Iluminación y fragment shader

El fragment shader suele evaluar la iluminación para obtener variaciones de color según las luces, las normales, el material y la vista. No es obligatorio: puede devolver un color fijo, una textura, una visualización técnica o cualquier otro resultado. Sin un modelo de iluminación, un objeto puede verse plano, pero eso puede ser exactamente el efecto deseado.

### 8. Múltiples fuentes de iluminación

Cada luz adicional puede exigir más cálculos por fragmento y más datos enviados al shader. Con muchas luces, el costo crece y pueden necesitarse técnicas de selección, agrupación o renderizado diferido para no evaluar todas las luces sobre todos los fragmentos.

## Resumen: dibujar un triángulo

Primero se crea una ventana y un contexto con GLFW y se cargan las funciones con GLAD. Después se definen tres posiciones, se crea un VBO para almacenar esos datos y un VAO para recordar su formato. Se compilan y enlazan los shaders. En cada cuadro se limpia el framebuffer, se activa el programa, se enlaza el VAO, se llama a `glDrawArrays(GL_TRIANGLES, 0, 3)` y se intercambian los buffers.

## Resumen: usar un shader

Se escribe el código GLSL de cada etapa, se crea un objeto shader, se entrega el código fuente, se compila y se revisan los errores. Luego se crea un programa, se adjuntan los shaders compilados, se enlaza y se valida. Tras el enlace, los objetos shader individuales pueden eliminarse. Para dibujar se activa el programa con `glUseProgram`; los atributos del VAO deben coincidir con los `layout(location=...)`, y los uniforms se actualizan antes del draw call.

## VBO con posición, color y offset

### Predicción

Cada draw call habilita un atributo distinto y cada shader interpreta ese atributo como posición. El shader A dibuja con las posiciones originales. El shader B usa los valores RGB como coordenadas, reducidos a la mitad, así que genera una geometría en otra región. El shader C usa los offsets bidimensionales como posiciones. El resultado no son tres atributos combinados en un solo triángulo, sino tres interpretaciones distintas de los mismos registros del VBO.

### Implementación de la configuración

```cpp
float vertices[] = {
    // posición           color             offset
    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.1f, 0.5f,
     0.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 0.2f, 0.5f,
    -0.5f, -0.5f, 0.0f,  0.5f, 0.5f, 0.0f, 0.15f, 0.75f
};

glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);
glBindVertexArray(0);
```

Dentro del render, se enlaza el VAO, se activa cada programa y se habilita solo el atributo que ese programa espera antes de llamar a `glDrawArrays`.

**Evidencia pendiente:** no se encontró en el repositorio una captura verificable de esta implementación ejecutándose. Por eso no se incluye ni se afirma un resultado visual como si se hubiera probado.

---

# Actividad 5

## Triángulo interactivo

Los shaders reciben dos uniforms: `offset`, de tipo `vec2`, para desplazar los vértices, y `ourColor`, de tipo `vec4`, para definir el color. Después de enlazar el programa se consultan sus ubicaciones:

```cpp
glUseProgram(shaderProg);
int offsetLocation = glGetUniformLocation(shaderProg, "offset");
int colorLocation = glGetUniformLocation(shaderProg, "ourColor");
```

En cada cuadro se lee el mouse, se normaliza y se actualizan ambos uniforms antes de dibujar:

```cpp
double mouseX, mouseY;
glfwGetCursorPos(mainWindow, &mouseX, &mouseY);

float x01 = static_cast<float>(mouseX) / static_cast<float>(SCR_WIDTH);
float y01 = static_cast<float>(mouseY) / static_cast<float>(SCR_HEIGHT);
x01 = std::clamp(x01, 0.0f, 1.0f);
y01 = std::clamp(y01, 0.0f, 1.0f);

glUseProgram(shaderProg);
glUniform4f(colorLocation, x01, y01, 0.0f, 1.0f);
glUniform2f(offsetLocation, x01 * 2.0f - 1.0f, 1.0f - y01 * 2.0f);
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, 3);
```

### Normalización de las coordenadas del mouse

GLFW entrega la posición del cursor en píxeles, con el origen normalmente en la esquina superior izquierda. Dividir `mouseX` por el ancho y `mouseY` por el alto convierte cada componente al intervalo `[0, 1]`. Limitar el resultado evita enviar valores fuera de ese rango cuando el cursor se encuentra fuera del área útil. Estos valores sirven directamente como componentes de color.

### Conversión a NDC

Las coordenadas visibles de OpenGL después de las transformaciones usan el intervalo `[-1, 1]`. Por eso `xNdc = x01 * 2 - 1` convierte izquierda y derecha en `-1` y `1`. Para Y se usa `yNdc = 1 - y01 * 2`, porque el eje vertical del cursor crece hacia abajo mientras que en NDC crece hacia arriba. Ese par se envía en `offset` y el vertex shader lo suma a cada vértice.

**Evidencia pendiente:** no se encontró una captura verificable del triángulo interactivo ejecutándose en la máquina. La descripción y el código quedan documentados, pero no se inventa la captura solicitada.

---

# Actividad 6

## Triángulo con color cíclico según el tiempo

### Cambios en C++

Después de enlazar y activar el programa se obtiene una sola vez la ubicación del uniform:

```cpp
glUseProgram(shaderProg);
int timeLocation = glGetUniformLocation(shaderProg, "time");
```

Dentro del game loop, antes de dibujar, se consulta el tiempo transcurrido y se actualiza el uniform:

```cpp
float elapsed = static_cast<float>(glfwGetTime());
glUseProgram(shaderProg);
glUniform1f(timeLocation, elapsed);
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, 3);
```

### Fragment shader modificado

```glsl
#version 460 core

out vec4 FragColor;
uniform float time;

void main()
{
    float red   = (sin(time) + 1.0) / 2.0;
    float green = (sin(time + 2.094) + 1.0) / 2.0;
    float blue  = (sin(time + 4.189) + 1.0) / 2.0;
    FragColor = vec4(red, green, blue, 1.0);
}
```

### Uso de la función de tiempo

`sin(time)` oscila entre `-1` y `1`. Al sumarle `1` y dividir por `2`, el resultado pasa al intervalo `[0, 1]`, adecuado para una componente de color. Los desplazamientos de aproximadamente 120° entre rojo, verde y azul hacen que las componentes alcancen sus máximos en momentos distintos y producen una transición continua. El valor alfa se mantiene en `1.0`, por lo que el triángulo sigue siendo opaco.

### Otros efectos posibles

El tiempo también puede controlar un desplazamiento horizontal con `sin(time)`, un movimiento circular usando `cos(time)` para X y `sin(time)` para Y, un cambio de tamaño pulsante o una rotación periódica mediante una matriz construida con seno y coseno.

**Evidencia pendiente:** no hay en el repositorio una captura o un enlace a un video verificable del resultado. No se agrega una evidencia ficticia.

---

# Autoevaluación verificable

## Nota propuesta

**1.0 / 5.0 según la rúbrica de cantidad de actividades completas.**

## Defensa por actividad

- **Actividad 1 — completa:** contiene una captura ya existente del ejemplo funcionando y más de tres preguntas de investigación.
- **Actividad 2 — completa:** incluye el resumen solicitado y conecta GLFW, `opengl32.lib`, GLAD, GLM, el driver y la GPU.
- **Actividad 3 — incompleta como evidencia práctica:** están las respuestas conceptuales y las predicciones, pero falta documentar la ejecución real de los experimentos.
- **Actividad 4 — incompleta:** contiene las respuestas, la predicción y la configuración propuesta, pero falta la captura del resultado ejecutado.
- **Actividad 5 — incompleta:** contiene la modificación propuesta y las explicaciones de normalización, pero falta la captura del programa funcionando.
- **Actividad 6 — incompleta:** contiene los cambios y el shader propuesto, pero falta una captura o un enlace a un video verificable.

La nota se propone con criterio conservador porque la guía indica que una actividad no está completa si le faltan sus evidencias. Para aumentar la nota es necesario ejecutar los programas, comprobar los resultados y añadir únicamente capturas o videos reales hechos durante ese proceso.
