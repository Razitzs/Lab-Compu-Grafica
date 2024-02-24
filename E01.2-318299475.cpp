#include <stdio.h>     // Incluye la biblioteca estándar de entrada/salida.
#include <string.h>    // Incluye la biblioteca para manipulación de cadenas de caracteres.
#include <glew.h>      // Incluye la biblioteca GLEW para OpenGL.
#include <glfw3.h>     // Incluye la biblioteca GLFW para la creación de ventanas y el manejo de contextos OpenGL.

const int WIDTH = 800, HEIGHT = 600;  // Define las constantes para el ancho y alto de la ventana.
GLuint VAO, VBO, shader;              // Declara variables globales para los identificadores de VAO, VBO y shader.

static const char* vShader = " \n\
#version 330 \n\
layout (location =0) in vec3 pos; \n\
void main() \n\
{ \n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); \n\
}";  // Define el código del shader de vértices como una cadena de caracteres.

static const char* fShader = " \n\
#version 330 \n\
out vec4 color; \n\
void main() \n\
{ \n\
color = vec4(1.0f,0.0f,0.0f,1.0f); // Rojo \n\
}";  // Define el código del shader de fragmentos como una cadena de caracteres.

void CrearTriangulo()
{
    GLfloat vertices[] = {
        // Coordenadas del rombo
        -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f,

        // Coordenadas del cuadrado
        0.6f, 0.5f, 0.0f,
        1.6f, 0.5f, 0.0f,
        1.6f, -0.5f, 0.0f,
        0.6f, 0.5f, 0.0f,
        1.6f, -0.5f, 0.0f,
        0.6f, -0.5f, 0.0f
    };  // Define las coordenadas de los vértices del triángulo y el cuadrado.

    // Genera y enlaza el Vertex Array Object (VAO) y el Vertex Buffer Object (VBO).
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Especifica los atributos de los vértices.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    // Crea un nuevo shader.
    GLuint theShader = glCreateShader(shaderType);
    const GLchar* theCode[1];
    theCode[0] = shaderCode;
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);
    // Asocia el código del shader con el shader creado.
    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        // Si hay errores al compilar, imprime el mensaje de error.
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("EL error al compilar el shader %d es: %s \n", shaderType, eLog);
        return;
    }

    // Adjunta el shader al programa.
    glAttachShader(theProgram, theShader);
}

void CompileShaders() {
    // Crea un nuevo programa de shaders.
    shader = glCreateProgram();
    if (!shader)
    {
        printf("Error creando el shader");
        return;
    }
    // Adjunta el shader de vértices y el shader de fragmentos al programa.
    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        // Si hay errores al linkear, imprime el mensaje de error.
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("EL error al linkear es: %s \n", eLog);
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        // Si hay errores al validar, imprime el mensaje de error.
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("EL error al validar es: %s \n", eLog);
        return;
    }
}

int main()
{
    // Inicializa GLFW.
    if (!glfwInit())
    {
        printf("Falló inicializar GLFW");
        glfwTerminate();
        return 1;
    }

    // Configura las opciones de la ventana GLFW.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Crea una ventana GLFW.
    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);
    if (!mainWindow)
    {
        printf("Fallo en crearse la ventana con GLFW");
        glfwTerminate();
        return 1;
    }

    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

    // Hace que el contexto de la ventana actual sea el principal en GLFW.
    glfwMakeContextCurrent(mainWindow);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        printf("Falló inicialización de GLEW");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Establece el tamaño de la ventana de OpenGL.
    glViewport(0, 0, BufferWidth, BufferHeight);
    // Crea el triángulo.
    CrearTriangulo();
    // Compila y enlaza los shaders.
    CompileShaders();

    while (!glfwWindowShouldClose(mainWindow))
    {
        glfwPollEvents();

        // Limpia el búfer de color de la ventana.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Utiliza el shader.
        glUseProgram(shader);
        // Enlaza el VAO.
        glBindVertexArray(VAO);
        // Dibuja el rombo.
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Dibuja el cuadrado.
        glDrawArrays(GL_TRIANGLES, 6, 6);
        // Desenlaza el VAO.
        glBindVertexArray(0);
        // Desactiva el shader.
        glUseProgram(0);

        // Intercambia los búferes de la ventana.
        glfwSwapBuffers(mainWindow);
    }

    return 0;
}
