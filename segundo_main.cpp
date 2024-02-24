#include <stdio.h>          // Incluye la biblioteca estándar de entrada y salida.
#include <string.h>         // Incluye la biblioteca para manipulación de cadenas de caracteres.
#include <glew.h>           // Incluye la biblioteca GLEW para OpenGL.
#include <glfw3.h>          // Incluye la biblioteca GLFW para manejo de ventanas y OpenGL.
#include <time.h>           // Incluye la biblioteca para manejo de tiempo.
#include <stdlib.h>         // Incluye la biblioteca estándar de funciones generales.

const int WIDTH = 800, HEIGHT = 600;    // Define constantes para el ancho y alto de la ventana.
GLuint VAO, VBO, shader;                // Declaración de variables globales para los objetos de OpenGL.

static const char* vShader = " \n\
#version 330 \n\
layout (location =0) in vec3 pos; \n\
void main() \n\
{ \n\
    gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); \n\
}";                                     // Shader de vértices en formato de cadena.

static const char* fShader = " \n\
#version 330 \n\
out vec4 color; \n\
void main() \n\
{ \n\
    color = vec4(1.0f,0.0f,0.0f,1.0f); \n\
}";                                     // Shader de fragmentos en formato de cadena.

void CrearTriangulo()                   // Función para crear un triángulo en OpenGL.
{
    GLfloat vertices[] = {              // Arreglo de coordenadas de vértices para el triángulo.
        // Coordenadas de los vértices del triángulo y la letra F y V.

            // Parte vertical de la F
            -0.9f, 0.5f, 0.0f,
            -0.7f, 0.5f, 0.0f,
            -0.9f, -0.5f, 0.0f,

            -0.7f, 0.5f, 0.0f,
            -0.9f, -0.5f, 0.0f,
            -0.7f, -0.5f, 0.0f,
            // Palito superior de la F
            -0.7f, 0.5f, 0.0f,
            -0.4f, 0.5f, 0.0f,
            -0.7f, 0.3f, 0.0f,

            -0.4f, 0.5f, 0.0f,
            -0.7f, 0.3f, 0.0f,
            -0.4f, 0.3f, 0.0f,
            // Palito inferior de la F
            -0.7f, 0.1f, 0.0f,
            -0.7f, -0.1f, 0.0f,
            -0.5f, 0.1f, 0.0f,

            -0.7f, -0.1f, 0.0f,
            -0.5f, -0.1f, 0.0f,
            -0.5f, 0.1f, 0.0f,
            // Parte vertical de la R
            -0.3f, 0.5f, 0.0f,
            -0.1f, 0.5f, 0.0f,
            -0.3f, -0.5f, 0.0f,

            -0.1f, 0.5f, 0.0f,
            -0.3f, -0.5f, 0.0f,
            -0.1f, -0.5f, 0.0f,

            -0.1f, 0.5f, 0.0f,
            -0.1f, 0.3f, 0.0f,
            0.0f, 0.5f, 0.0f,

            -0.1f, 0.3f, 0.0f,
            0.0f, 0.3f, 0.0f,
            0.0f, 0.5f, 0.0f,

            -0.1f, 0.2f, 0.0f,
            -0.1f, 0.0f, 0.0f,
            0.0f, 0.2f, 0.0f,

            -0.1f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.2f, 0.0f,

            0.0f, 0.5f, 0.0f,
            0.2f, 0.5f, 0.0f,
            0.0f, 0.1f, 0.0f,

            0.0f, 0.1f, 0.0f,
            0.2f, 0.1f, 0.0f,
            0.2f, 0.5f, 0.0f,

            0.0f, -0.5f, 0.0f,
            0.2f, -0.5f, 0.0f,
            0.0f, 0.1f, 0.0f,

            0.0f, -0.5f, 0.0f,
            0.0f, 0.0f, 0.0f,
            -0.1f, 0.0f, 0.0f,

            // Aquí va la V
            0.3f, 0.5f, 0.0f, //triángulo izquierda
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,

            0.5f, -0.3f, 0.0f, //triángulo parado derecha
            0.5f, 0.5f, 0.0f,
            0.6f, -0.3f, 0.0f,

            0.7f, 0.5f, 0.0f, //Triángulo derecha
            0.9f, 0.5f, 0.0f,
            0.7f, -0.5f, 0.0f,


            0.5f, -0.3f, 0.0f,//triángulo base arriba
            0.5f, -0.5f, 0.0f,
            0.7f, -0.3f, 0.0f,


            0.7f, 0.5f, 0.0f,
            0.7f, -0.3f, 0.0f,
            0.6f, -0.3f, 0.0f,


            0.5f, -0.5f, 0.0f,
            0.7f, -0.3f, 0.0f,
            0.7f, -0.5f, 0.0f,



    };

    glGenVertexArrays(1, &VAO);         // Genera un array de objetos de vértices.
    glBindVertexArray(VAO);             // Vincula el array de vértices.
    glGenBuffers(1, &VBO);              // Genera un buffer de objetos de vértices.
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Vincula el buffer de vértices.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Rellena el buffer de vértices.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0); // Especifica los datos del vértice.
    glEnableVertexAttribArray(0);       // Habilita el atributo de vértices.
    glBindBuffer(GL_ARRAY_BUFFER, 0);   // Desvincula el buffer de vértices.
    glBindVertexArray(0);               // Desvincula el array de vértices.
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType); // Crea un shader de OpenGL.
    const GLchar* theCode[1];           // Arreglo de cadenas para el código del shader.
    theCode[0] = shaderCode;            // Asigna el código del shader al arreglo.
    GLint codeLength[1];                // Longitud del código del shader.
    codeLength[0] = strlen(shaderCode); // Asigna la longitud del código del shader.
    glShaderSource(theShader, 1, theCode, codeLength); // Asigna el código del shader al shader de OpenGL.
    glCompileShader(theShader);         // Compila el shader.
    GLint result = 0;                   // Variable para almacenar el resultado de la compilación.
    GLchar eLog[1024] = { 0 };          // Registro de errores.
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result); // Obtiene el resultado de la compilación.
    if (!result) {                      // Si la compilación falla,
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog); // Obtiene el registro de errores.
        printf("EL error al compilar el shader %d es: %s \n", shaderType, eLog); // Imprime el mensaje de error.
        return;                         // Retorna.
    }
    glAttachShader(theProgram, theShader); // Adjunta el shader al programa de OpenGL.
}

void CompileShaders() {                // Función para compilar los shaders.
    shader = glCreateProgram();         // Crea un programa de shaders de OpenGL.
    if (!shader) {                      // Si la creación del programa falla,
        printf("Error creando el shader"); // Imprime un mensaje de error.
        return;                         // Retorna.
    }
    AddShader(shader, vShader, GL_VERTEX_SHADER);     // Agrega el shader de vértices al programa.
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);   // Agrega el shader de fragmentos al programa.
    GLint result = 0;                   // Variable para almacenar el resultado de la operación.
    GLchar eLog[1024] = { 0 };          // Registro de errores.
    glLinkProgram(shader);              // Enlaza los shaders al programa.
    glGetProgramiv(shader, GL_LINK_STATUS, &result);  // Obtiene el resultado del enlace.
    if (!result) {                      // Si el enlace falla,
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog); // Obtiene el registro de errores.
        printf("EL error al linkear es: %s \n", eLog); // Imprime un mensaje de error.
        return;                         // Retorna.
    }
    glValidateProgram(shader);          // Valida el programa de shaders.
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result); // Obtiene el resultado de la validación.
    if (!result) {                      // Si la validación falla,
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog); // Obtiene el registro de errores.
        printf("EL error al validar es: %s \n", eLog); // Imprime un mensaje de error.
        return;                         // Retorna.
    }
}

int main()                             // Función principal del programa.
{
    if (!glfwInit()) {                  // Inicializa GLFW y verifica si hay errores.
        printf("Falló inicializar GLFW"); // Imprime un mensaje de error.
        glfwTerminate();                // Termina GLFW.
        return 1;                       // Retorna.
    }

    // Configuración de la ventana GLFW.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Versión mayor de OpenGL.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Versión menor de OpenGL.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Perfil de OpenGL.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Compatibilidad con versiones anteriores.

    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL); // Crea la ventana GLFW.
    if (!mainWindow) {                  // Si la creación de la ventana falla,
        printf("Fallo en crearse la ventana con GLFW"); // Imprime un mensaje de error.
        glfwTerminate();                // Termina GLFW.
        return 1;                       // Retorna.
    }

    // Obtiene el tamaño del framebuffer de la ventana.
    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

    glfwMakeContextCurrent(mainWindow); // Establece la ventana GLFW como el contexto actual.
    glewExperimental = GL_TRUE;         // Activa las características experimentales de GLEW.
    if (glewInit() != GLEW_OK) {        // Inicializa GLEW y verifica si hay errores.
        printf("Falló inicialización de GLEW"); // Imprime un mensaje de error.
        glfwDestroyWindow(mainWindow);  // Destruye la ventana GLFW.
        glfwTerminate();                // Termina GLFW.
        return 1;                       // Retorna.
    }

    glViewport(0, 0, BufferWidth, BufferHeight); // Establece las dimensiones del viewport.
    CrearTriangulo();                   // Crea el triángulo en OpenGL.
    CompileShaders();                   // Compila los shaders.

    // Bucle principal del programa.
    double lastTime = glfwGetTime();    // Obtiene el tiempo actual.
    double currentTime;
    while (!glfwWindowShouldClose(mainWindow)) // Mientras la ventana no deba cerrarse,
    {
        // Obtener tiempo actual
        currentTime = glfwGetTime();    // Obtiene el tiempo actual.
        if (currentTime - lastTime >= 2.0) // Si ha pasado un segundo,
        {
            // Generar colores aleatorios
            float rojo = (float)rand() / RAND_MAX; // Genera un valor de color rojo aleatorio.
            float verde = (float)rand() / RAND_MAX; // Genera un valor de color verde aleatorio.
            float azul = (float)rand() / RAND_MAX; // Genera un valor de color azul aleatorio.
            // Limpiar la ventana con el color aleatorio
            glClearColor(rojo, verde, azul, 1.0f); // Establece el color de limpieza de la ventana.
            glClear(GL_COLOR_BUFFER_BIT);   // Limpia el buffer de color.
            // Intercambiar búferes
            glfwSwapBuffers(mainWindow);   // Intercambia los búferes de la ventana.
            // Actualizar el último tiempo
            lastTime = currentTime;        // Actualiza el último tiempo.
        }

        glClear(GL_COLOR_BUFFER_BIT);     // Limpia el buffer de color.
        glUseProgram(shader);             // Usa el programa de shaders.
        glBindVertexArray(VAO);           // Vincula el array de vértices.
        glDrawArrays(GL_TRIANGLES, 0, 66); // Dibuja los triángulos.
        glBindVertexArray(0);             // Desvincula el array de vértices.
        glUseProgram(0);                  // Desactiva el programa de shaders.
        glfwSwapBuffers(mainWindow);      // Intercambia los búferes de la ventana.
        glfwPollEvents();                 // Procesa los eventos de la ventana.
    }

    return 0;                           
}
