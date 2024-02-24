#include <stdio.h>          // Incluye la biblioteca estándar para entrada/salida
#include <glew.h>           // Incluye la biblioteca GLEW para manejar las extensiones de OpenGL
#include <glfw3.h>          // Incluye la biblioteca GLFW para la creación de ventanas y el manejo de contexto de OpenGL
#include <stdlib.h>         // Incluye la biblioteca estándar de C para funciones de utilidad
#include <time.h>           // Incluye la biblioteca de C para funciones relacionadas con el tiempo

// Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;

int main() {
    // Inicialización de GLFW
    if (!glfwInit()) {                                          // Verifica si la inicialización de GLFW fue exitosa
        printf("Falló inicializar GLFW");                       // Imprime un mensaje de error si la inicialización falló
        glfwTerminate();                                        // Termina GLFW
        return 1;                                               // Devuelve 1 para indicar un error
    }

    // Asignando variables de GLFW y propiedades de ventana
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);              // Establece la versión mayor del contexto de OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);              // Establece la versión menor del contexto de OpenGL
    // Para solo usar el core profile de OpenGL y no tener retrocompatibilidad
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Establece el perfil de OpenGL como núcleo (core)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);         // Permite la compatibilidad con versiones futuras de OpenGL

    // CREAR VENTANA
    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Ejercicio 1 Practica 1", NULL, NULL);  // Crea la ventana GLFW
    // En caso de que falle la ventana
    if (!mainWindow) {                                          // Verifica si la creación de la ventana fue exitosa
        printf("Fallo en crearse la ventana con GLFW");         // Imprime un mensaje de error si la creación de la ventana falló
        glfwTerminate();                                        // Termina GLFW
        return 1;                                               // Devuelve 1 para indicar un error
    }

    // Obtener tamaño de Buffer
    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);  // Obtiene el tamaño del buffer de trama de la ventana

    // Asignar el contexto
    glfwMakeContextCurrent(mainWindow);                         // Establece el contexto de OpenGL en la ventana

    // Permitir nuevas extensiones
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {                                // Inicializa GLEW para gestionar las extensiones de OpenGL
        printf("Falló inicialización de GLEW");                // Imprime un mensaje de error si la inicialización de GLEW falló
        glfwDestroyWindow(mainWindow);                          // Destruye la ventana GLFW
        glfwTerminate();                                        // Termina GLFW
        return 1;                                               // Devuelve 1 para indicar un error
    }

    // Asignar valores de la ventana y coordenadas
    // Asignar Viewport
    glViewport(0, 0, BufferWidth, BufferHeight);               // Establece el viewport de OpenGL para que coincida con el tamaño de la ventana
    printf("Version de Opengl: %s \n", glGetString(GL_VERSION));  // Imprime la versión de OpenGL
    printf("Marca: %s \n", glGetString(GL_VENDOR));            // Imprime el fabricante de la tarjeta gráfica
    printf("Renderer: %s \n", glGetString(GL_RENDERER));      // Imprime el nombre del renderizador
    printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));  // Imprime la versión del lenguaje de sombreado

    double ultimoTiempo = glfwGetTime();                        // Obtiene el tiempo actual
    double tiempo;
    int colorIndex = 0;
    // Colores predefinidos: Rojo, Verde, Azul
    float colores[3][3] = {                                     // Matriz que contiene los valores de los colores Rojo, Verde y Azul
        {1.0f, 0.0f, 0.0f}, // Rojo
        {0.0f, 1.0f, 0.0f}, // Verde
        {0.0f, 0.0f, 1.0f}  // Azul
    };

    while (!glfwWindowShouldClose(mainWindow)) {                // Bucle principal: mientras la ventana no se cierre
        tiempo = glfwGetTime();                                 // Obtiene el tiempo actual

        if (tiempo - ultimoTiempo >= 2.0) {                     // Si ha pasado al menos 2 segundos desde la última actualización
            // Obtener el color actual de la secuencia
            float R = colores[colorIndex][0];                   // Obtiene el valor de rojo del color actual
            float G = colores[colorIndex][1];                   // Obtiene el valor de verde del color actual
            float B = colores[colorIndex][2];                   // Obtiene el valor de azul del color actual

            // Limpiar la ventana con el color actual
            glClearColor(R, G, B, 1.0f);                        // Establece el color de limpieza de la ventana
            glClear(GL_COLOR_BUFFER_BIT);                        // Limpia el buffer de color con el color especificado

            glfwSwapBuffers(mainWindow);                         // Intercambia los buffers frontal y trasero de la ventana

            ultimoTiempo = tiempo;                               // Actualiza el tiempo de la última actualización

            // Avanzar al siguiente color en la secuencia
            colorIndex = (colorIndex + 1) % 3;                   // Incrementa el índice del color o vuelve al principio si es necesario
        }
        // Poll de eventos
        glfwPollEvents();                                       // Procesa todos los eventos pendientes
    }
    return 0;                                                   // Devuelve 0 para indicar una ejecución exitosa
}

