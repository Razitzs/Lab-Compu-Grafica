#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	articulacion4 = 0.0f;
	articulacion5 = 0.0f;
	articulacion6 = 0.0f;
	articulacion7 = 0.0f;
	articulacion8 = 0.0f;
	articulacion9 = 0.0f;
	articulacion10 = 0.0f;
	
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicializaci�n de GLFW
	if (!glfwInit())
	{
		printf("Fall� inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica XX: Nombre de la pr�ctica", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama�o de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Fall� inicializaci�n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se est� usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	
	if (key == GLFW_KEY_E)
	{
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_R)
	{
		theWindow->rotay += 10.0; //rotar sobre el eje y 10 grados
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->rotaz += 10.0;
	}
	//Estableciendo los l�mites de rotaci�n, asignando las teclas 
	if (key == GLFW_KEY_T)
	{
		if (theWindow->articulacion1 < 45.0) {
			theWindow->articulacion1 += 5.0;	//pata delantera izquierda hacia adelante 
		}
	}
	if (key == GLFW_KEY_F)
	{
		if (theWindow->articulacion1 > -10.0) {
			theWindow->articulacion1 -= 5.0;	//pata delantera izquierda hacia atr�s
		}
	}
	if (key == GLFW_KEY_Y)
	{
		if (theWindow->articulacion2 < 45.0) {
			theWindow->articulacion2 += 5.0;	//pata delantera derecha hacia adelante 
		}
	}
	if (key == GLFW_KEY_G)
	{
		if (theWindow->articulacion2 > -10.0) {
			theWindow->articulacion2 -= 5.0;	//pata delantera derecha hacia atr�s
		}
	}
	if (key == GLFW_KEY_U)
	{
		if (theWindow->articulacion3 < 45.0) {
			theWindow->articulacion3 += 5.0;	//pata trasera izquierda hacia adelante
		}
	}
	if (key == GLFW_KEY_H)
	{
		if (theWindow->articulacion3 > -10.0) {
			theWindow->articulacion3 -= 5.0;	//pata trasera izquierda hacia atr�s
		}
	}
	if (key == GLFW_KEY_I)
	{
		if (theWindow->articulacion4 < 45.0) {
			theWindow->articulacion4 += 5.0;	//pata trasera derecha hacia adelante
		}
	}
	if (key == GLFW_KEY_J)
	{
		if (theWindow->articulacion4 > -10.0) {
			theWindow->articulacion4 -= 5.0;	//pata trasera derecha hacia atr�s
		}
	}
	if (key == GLFW_KEY_O)
	{
		if (theWindow->articulacion5 < 30.0) {
			theWindow->articulacion5 += 5.0;	//cabeza hacia arriba
		}
	}
	if (key == GLFW_KEY_K)
	{
		if (theWindow->articulacion5 > -15.0) {
			theWindow->articulacion5 -= 5.0;	//cabeza hacia abajo
		}
	}
	if (key == GLFW_KEY_P)
	{
		if (theWindow->articulacion6 < 13.0) {
			theWindow->articulacion6 += 5.0;	//mand�bula hacia arriba
		}
	}
	if (key == GLFW_KEY_L)
	{
		if (theWindow->articulacion6 > -10.0) {
			theWindow->articulacion6 -= 5.0;	//mand�bula hacia abajo
		}
	}
	if (key == GLFW_KEY_V)
	{
		theWindow->articulacion7 += 10.0;
	}
	if (key == GLFW_KEY_B)
	{
		theWindow->articulacion8 += 10.0;
	}
	if (key == GLFW_KEY_N)
	{
		theWindow->articulacion9 += 10.0;
	}
	if (key == GLFW_KEY_M)
	{
		theWindow->articulacion10 += 10.0;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		//printf("se presiono la tecla: %s\n",key_name);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
