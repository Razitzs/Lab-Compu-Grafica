/*
Práctica 5: Optimización y Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;
//float angulocola = 0.0f;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;


Camera camera;
//cada variable es el modelo que utilizaré
Model Goddard_M, mandibula, cabeza, piernaAdelante, piernaAtras, cuerpo;
Skybox skybox;
	
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_m.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_m.frag";





void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 1.0f);

	cabeza = Model();
	cabeza.LoadModel("modelos/cabeza.obj");
	cuerpo = Model();
	cuerpo.LoadModel("modelos/cuerpo.obj");
	mandibula = Model();
	mandibula.LoadModel("modelos/mandibula.obj");
	piernaAdelante = Model();
	piernaAdelante.LoadModel("modelos/pataAdelante.obj");
	piernaAtras = Model();
	piernaAtras.LoadModel("modelos/pataAtras.obj");


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);


	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Se dibuja el Skybox
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		// INICIA DIBUJO DEL PISO
		color = glm::vec3(0.5f, 0.5f, 0.5f); //piso de color gris
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMesh();
		
		// Cuerpo
		color = glm::vec3(0.0f, 1.0f, 0.0f); // Define el color del cuerpo de Goddard como verde.
		model = glm::mat4(1.0); // Inicializa la matriz de modelo como la identidad.
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, 0.0f)); // Traslada el cuerpo a la posición deseada.
		modelaux = model; // Almacena una copia de la matriz de modelo para su posterior uso.
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); // Asigna el color al shader.
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // Asigna la matriz de modelo al shader.
		cuerpo.RenderModel(); // Renderiza el cuerpo de Goddard.

		// Pata frontal izquierda
		model = modelaux; // Reinicializa la matriz de modelo con la copia almacenada.
		model = glm::translate(model, glm::vec3(1.0f, -0.6f, -9.4f)); // Traslada la pata a la posición deseada.
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, 1.0f)); // Rota la pata según el ángulo de articulación.
		color = glm::vec3(1.0f, 1.0f, 0.0f); // Define el color de la pata de Goddard como amarillo.
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); // Asigna el color al shader.
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // Asigna la matriz de modelo al shader.
		piernaAdelante.RenderModel(); // Renderiza la pata delantera izquierda de Goddard.

		// Pata frontal derecha
		model = modelaux; // Reinicializa la matriz de modelo con la copia almacenada.
		model = glm::translate(model, glm::vec3(1.0f, -0.6f, -10.6f)); // Traslada la pata a la posición deseada.
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f)); // Rota la pata según el ángulo de articulación.
		color = glm::vec3(1.0f, 1.0f, 0.0f); // Define el color de la pata de Goddard como amarillo.
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); // Asigna el color al shader.
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // Asigna la matriz de modelo al shader.
		piernaAdelante.RenderModel(); // Renderiza la pata delantera derecha de Goddard.

		// Pata posterior izquierda
		model = modelaux; // Reinicializa la matriz de modelo con la copia almacenada.
		model = glm::translate(model, glm::vec3(-0.2f, -1.3f, -9.4f)); // Traslada la pata a la posición deseada.
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(0.0f, 0.0f, 1.0f)); // Rota la pata según el ángulo de articulación.
		color = glm::vec3(1.0f, 1.0f, 0.0f); // Define el color de la pata de Goddard como amarillo.
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); // Asigna el color al shader.
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // Asigna la matriz de modelo al shader.
		piernaAtras.RenderModel(); // Renderiza la pata posterior izquierda de Goddard.

		// Pata posterior derecha
		model = modelaux; // Reinicializa la matriz de modelo con la copia almacenada.
		model = glm::translate(model, glm::vec3(-0.2f, -1.3f, -10.6f)); // Traslada la pata a la posición deseada.
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(0.0f, 0.0f, 1.0f)); // Rota la pata según el ángulo de articulación.
		color = glm::vec3(1.0f, 1.0f, 0.0f); // Define el color de la pata de Goddard como amarillo.
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); // Asigna el color al shader.
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // Asigna la matriz de modelo al shader.
		piernaAtras.RenderModel(); // Renderiza la pata posterior derecha de Goddard.

		// Cabeza
		model = modelaux; // Reinicializa la matriz de modelo con la copia almacenada.
		model = glm::translate(model, glm::vec3(1.8f, 0.48f, -10.4f)); // Traslada la cabeza a la posición deseada.
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion5()), glm::vec3(0.0f, 0.0f, 1.0f)); // Rota la cabeza según el ángulo de articulación.
		color = glm::vec3(0.0f, 0.0f, 1.0f); // Define el color de la cabeza de Goddard como azul.
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); // Asigna el color al shader.
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // Asigna la matriz de modelo al shader.
		cabeza.RenderModel(); // Renderiza la cabeza de Goddard.

		// Mandíbula
		model = glm::translate(model, glm::vec3(1.0f, 0.2f, 0.5f)); // Traslada la mandíbula a la posición deseada.
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion6()), glm::vec3(0.0f, 0.0f, 1.0f)); // Rota la mandíbula según el ángulo de articulación.
		color = glm::vec3(1.0f, 0.0f, 1.0f); // Define el color de la mandíbula de Goddard como rosa.
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); // Asigna el color al shader.
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // Asigna la matriz de modelo al shader.
		mandibula.RenderModel(); // Renderiza la mandíbula de Goddard.
		
		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}
