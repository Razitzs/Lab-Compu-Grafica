#include <stdio.h>          // Incluye la biblioteca est�ndar de entrada y salida.
#include <string.h>         // Incluye la biblioteca para manipulaci�n de cadenas de caracteres.
#include <glew.h>           // Incluye la biblioteca GLEW para OpenGL.
#include <glfw3.h>          // Incluye la biblioteca GLFW para manejo de ventanas y OpenGL.
#include <time.h>           // Incluye la biblioteca para manejo de tiempo.
#include <stdlib.h>         // Incluye la biblioteca est�ndar de funciones generales.

const int WIDTH = 800, HEIGHT = 600;    // Define constantes para el ancho y alto de la ventana.
GLuint VAO, VBO, shader;                // Declaraci�n de variables globales para los objetos de OpenGL.

static const char* vShader = " \n\
#version 330 \n\
layout (location =0) in vec3 pos; \n\
void main() \n\
{ \n\
    gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); \n\
}";                                     // Shader de v�rtices en formato de cadena.

static const char* fShader = " \n\
#version 330 \n\
out vec4 color; \n\
void main() \n\
{ \n\
    color = vec4(1.0f,0.0f,0.0f,1.0f); \n\
}";                                     // Shader de fragmentos en formato de cadena.

void CrearTriangulo()                   // Funci�n para crear un tri�ngulo en OpenGL.
{
    GLfloat vertices[] = {              // Arreglo de coordenadas de v�rtices para el tri�ngulo.
        // Coordenadas de los v�rtices del tri�ngulo y la letra F y V.

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

            // Aqu� va la V
            0.3f, 0.5f, 0.0f, //tri�ngulo izquierda
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,

            0.5f, -0.3f, 0.0f, //tri�ngulo parado derecha
            0.5f, 0.5f, 0.0f,
            0.6f, -0.3f, 0.0f,

            0.7f, 0.5f, 0.0f, //Tri�ngulo derecha
            0.9f, 0.5f, 0.0f,
            0.7f, -0.5f, 0.0f,


            0.5f, -0.3f, 0.0f,//tri�ngulo base arriba
            0.5f, -0.5f, 0.0f,
            0.7f, -0.3f, 0.0f,


            0.7f, 0.5f, 0.0f,
            0.7f, -0.3f, 0.0f,
            0.6f, -0.3f, 0.0f,


            0.5f, -0.5f, 0.0f,
            0.7f, -0.3f, 0.0f,
            0.7f, -0.5f, 0.0f,



    };

    glGenVertexArrays(1, &VAO);         // Genera un array de objetos de v�rtices.
    glBindVertexArray(VAO);             // Vincula el array de v�rtices.
    glGenBuffers(1, &VBO);              // Genera un buffer de objetos de v�rtices.
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Vincula el buffer de v�rtices.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Rellena el buffer de v�rtices.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0); // Especifica los datos del v�rtice.
    glEnableVertexAttribArray(0);       // Habilita el atributo de v�rtices.
    glBindBuffer(GL_ARRAY_BUFFER, 0);   // Desvincula el buffer de v�rtices.
    glBindVertexArray(0);               // Desvincula el array de v�rtices.
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType); // Crea un shader de OpenGL.
    const GLchar* theCode[1];           // Arreglo de cadenas para el c�digo del shader.
    theCode[0] = shaderCode;            // Asigna el c�digo del shader al arreglo.
    GLint codeLength[1];                // Longitud del c�digo del shader.
    codeLength[0] = strlen(shaderCode); // Asigna la longitud del c�digo del shader.
    glShaderSource(theShader, 1, theCode, codeLength); // Asigna el c�digo del shader al shader de OpenGL.
    glCompileShader(theShader);         // Compila el shader.
    GLint result = 0;                   // Variable para almacenar el resultado de la compilaci�n.
    GLchar eLog[1024] = { 0 };          // Registro de errores.
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result); // Obtiene el resultado de la compilaci�n.
    if (!result) {                      // Si la compilaci�n falla,
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog); // Obtiene el registro de errores.
        printf("EL error al compilar el shader %d es: %s \n", shaderType, eLog); // Imprime el mensaje de error.
        return;                         // Retorna.
    }
    glAttachShader(theProgram, theShader); // Adjunta el shader al programa de OpenGL.
}

void CompileShaders() {                // Funci�n para compilar los shaders.
    shader = glCreateProgram();         // Crea un programa de shaders de OpenGL.
    if (!shader) {                      // Si la creaci�n del programa falla,
        printf("Error creando el shader"); // Imprime un mensaje de error.
        return;                         // Retorna.
    }
    AddShader(shader, vShader, GL_VERTEX_SHADER);     // Agrega el shader de v�rtices al programa.
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);   // Agrega el shader de fragmentos al programa.
    GLint result = 0;                   // Variable para almacenar el resultado de la operaci�n.
    GLchar eLog[1024] = { 0 };          // Registro de errores.
    glLinkProgram(shader);              // Enlaza los shaders al programa.
    glGetProgramiv(shader, GL_LINK_STATUS, &result);  // Obtiene el resultado del enlace.
    if (!result) {                      // Si el enlace falla,
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog); // Obtiene el registro de errores.
        printf("EL error al linkear es: %s \n", eLog); // Imprime un mensaje de error.
        return;                         // Retorna.
    }
    glValidateProgram(shader);          // Valida el programa de shaders.
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result); // Obtiene el resultado de la validaci�n.
    if (!result) {                      // Si la validaci�n falla,
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog); // Obtiene el registro de errores.
        printf("EL error al validar es: %s \n", eLog); // Imprime un mensaje de error.
        return;                         // Retorna.
    }
}

int main()                             // Funci�n principal del programa.
{
    if (!glfwInit()) {                  // Inicializa GLFW y verifica si hay errores.
        printf("Fall� inicializar GLFW"); // Imprime un mensaje de error.
        glfwTerminate();                // Termina GLFW.
        return 1;                       // Retorna.
    }

    // Configuraci�n de la ventana GLFW.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Versi�n mayor de OpenGL.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Versi�n menor de OpenGL.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Perfil de OpenGL.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Compatibilidad con versiones anteriores.

    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL); // Crea la ventana GLFW.
    if (!mainWindow) {                  // Si la creaci�n de la ventana falla,
        printf("Fallo en crearse la ventana con GLFW"); // Imprime un mensaje de error.
        glfwTerminate();                // Termina GLFW.
        return 1;                       // Retorna.
    }

    // Obtiene el tama�o del framebuffer de la ventana.
    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

    glfwMakeContextCurrent(mainWindow); // Establece la ventana GLFW como el contexto actual.
    glewExperimental = GL_TRUE;         // Activa las caracter�sticas experimentales de GLEW.
    if (glewInit() != GLEW_OK) {        // Inicializa GLEW y verifica si hay errores.
        printf("Fall� inicializaci�n de GLEW"); // Imprime un mensaje de error.
        glfwDestroyWindow(mainWindow);  // Destruye la ventana GLFW.
        glfwTerminate();                // Termina GLFW.
        return 1;                       // Retorna.
    }

    glViewport(0, 0, BufferWidth, BufferHeight); // Establece las dimensiones del viewport.
    CrearTriangulo();                   // Crea el tri�ngulo en OpenGL.
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
            // Intercambiar b�feres
            glfwSwapBuffers(mainWindow);   // Intercambia los b�feres de la ventana.
            // Actualizar el �ltimo tiempo
            lastTime = currentTime;        // Actualiza el �ltimo tiempo.
        }

        glClear(GL_COLOR_BUFFER_BIT);     // Limpia el buffer de color.
        glUseProgram(shader);             // Usa el programa de shaders.
        glBindVertexArray(VAO);           // Vincula el array de v�rtices.
        glDrawArrays(GL_TRIANGLES, 0, 66); // Dibuja los tri�ngulos.
        glBindVertexArray(0);             // Desvincula el array de v�rtices.
        glUseProgram(0);                  // Desactiva el programa de shaders.
        glfwSwapBuffers(mainWindow);      // Intercambia los b�feres de la ventana.
        glfwPollEvents();                 // Procesa los eventos de la ventana.
    }

    return 0;                           
}
