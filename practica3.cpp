////pr�ctica 3: Modelado Geom�trico y C�mara Sint�tica.
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include <gtc\random.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Sphere.h"
#include"Window.h"
#include"Camera.h"
//tecla E: Rotar sobre el eje X
//tecla R: Rotar sobre el eje Y
//tecla T: Rotar sobre el eje Z


using std::vector;

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
const float PI = 3.14159265f;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;
Camera camera;
Window mainWindow;
vector<Mesh*> meshList;
vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
Sphere sp = Sphere(0.5, 20, 20); //recibe radio, slices, stacks

void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

// Pir�mide triangular regular
void CrearPiramideTriangular()
{
	const float sen60 = glm::sin(glm::radians(60.f));
	const float tan30entre2 = glm::tan(glm::radians(30.f)) * 0.5f;

	vector<unsigned int> indices_piramide_triangular = {
	  0,1,2,
	  0,3,2,
	  0,3,2,
	  0,2,3,
	  1,2,3,
	};

	vector<GLfloat> vertices_piramide_triangular = {
	  0.f, tan30entre2 - sen60 * 0.5f, 0.f,
	  0, 0.5f * sen60, -tan30entre2,
	  -0.5f, -0.5f * sen60, -tan30entre2,
	  0.5f, -0.5f * sen60, -tan30entre2,
	};

	Mesh* piramide = new Mesh();
	piramide->CreateMeshGeometry(vertices_piramide_triangular, indices_piramide_triangular, 12, 15);
	meshList.push_back(piramide);

}
/*
Crear cilindro, cono y esferas con arreglos din�micos vector creados en el Semestre 2023 - 1 : por S�nchez P�rez Omar Alejandro
*/
void CrearCilindro(int res, float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//c�lculo del paso interno en la circunferencia y variables que almacenar�n cada coordenada de cada v�rtice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;

	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//ciclo for para crear los v�rtices de las paredes del cilindro
	for (n = 0; n <= (res); n++) {
		if (n != res) {
			x = R * cos((n)*dt);
			z = R * sin((n)*dt);
		}
		//caso para terminar el c�rculo
		else {
			x = R * cos((0)*dt);
			z = R * sin((0)*dt);
		}
		for (i = 0; i < 6; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			case 3:
				vertices.push_back(x);
				break;
			case 4:
				vertices.push_back(0.5);
				break;
			case 5:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia inferior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(-0.5f);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia superior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(0.5);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//Se generan los indices de los v�rtices
	for (i = 0; i < vertices.size(); i++) indices.push_back(i);

	//se genera el mesh del cilindro
	Mesh *cilindro = new Mesh();
	cilindro->CreateMeshGeometry(vertices, indices, vertices.size(), indices.size());
	meshList.push_back(cilindro);
}

//funci�n para crear un cono
void CrearCono(int res,float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//c�lculo del paso interno en la circunferencia y variables que almacenar�n cada coordenada de cada v�rtice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;
	
	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//caso inicial para crear el cono
	vertices.push_back(0.0);
	vertices.push_back(0.5);
	vertices.push_back(0.0);
	
	//ciclo for para crear los v�rtices de la circunferencia del cono
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}
	vertices.push_back(R * cos(0) * dt);
	vertices.push_back(-0.5);
	vertices.push_back(R * sin(0) * dt);


	for (i = 0; i < res+2; i++) indices.push_back(i);

	//se genera el mesh del cono
	Mesh *cono = new Mesh();
	cono->CreateMeshGeometry(vertices, indices, vertices.size(), res + 2);
	meshList.push_back(cono);
}

//funci�n para crear pir�mide cuadrangular unitaria
void CrearPiramideCuadrangular()
{
	vector<unsigned int> piramidecuadrangular_indices = {
		0,3,4,
		3,2,4,
		2,1,4,
		1,0,4,
		0,1,2,
		0,2,4

	};
	vector<GLfloat> piramidecuadrangular_vertices = {
		0.5f,-0.5f,0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		0.0f,0.5f,0.0f,
	};
	Mesh *piramide = new Mesh();
	piramide->CreateMeshGeometry(piramidecuadrangular_vertices, piramidecuadrangular_indices, 15, 18);
	meshList.push_back(piramide);
}



void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(vShaderColor, fShader);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	//Cilindro y cono reciben resoluci�n (slices, rebanadas) y Radio de circunferencia de la base y tapa

	CrearCubo();//�ndice 0 en MeshList
	CrearPiramideTriangular();//�ndice 1 en MeshList
	CrearCilindro(5, 1.0f);//�ndice 2 en MeshList
	CrearCono(25, 2.0f);//�ndice 3 en MeshList
	CrearPiramideCuadrangular();//�ndice 4 en MeshList
	CreateShaders();
	
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.1f, 0.3f);

	
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);
	
	//Loop mientras no se cierra la ventana
	sp.init(); //inicializar esfera
	sp.load();//enviar la esfera al shader

	glm::mat4 model(1.0);//Inicializar matriz de Modelo 4x4

	glm::vec3 color = glm::vec3(0.0f,0.0f,0.0f); //inicializar Color para enviar a variable Uniform;
	float rotacion = 60.f;
	while (!mainWindow.getShouldClose())
	{


		const int indices[] = {
							  2, 2,
							  1, 1,
							  2, 1,
							  3, 1,
							  0, 0,
							  1, 0,
							  2, 0,
							  3, 0,
							  4, 0,
								};



		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();
		//C�mara
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));


		// Pir�mide blanca
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::rotate(glm::mat4(1.0), glm::radians(rotacion), glm::vec3(1, 1, 1));
		model = glm::translate(model, glm::vec3(1.f, 0.95f, 2.65f));
		model = glm::scale(model, glm::vec3(3.2f, 3.3f, 9.f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[1]->RenderMesh();


		//Cara verde
		color = glm::vec3(0.f, 7.0f, 0.f);
		for (int i = 0; i < 18; i += 2) {
			
			model = glm::rotate(glm::mat4(1.0), glm::radians(rotacion), glm::vec3(1, 1, 1)); // Bucle para iterar sobre los �ndices que definen la posici�n de la cara.
			model = glm::rotate(model, glm::radians(-60.f), glm::vec3(0, 0, 1));    // Operaciones de transformaci�n de la matriz de modelo para posicionar y orientar la cara.
			model = glm::rotate(model, glm::radians(110.f), glm::vec3(1, 0, 0));
			model = glm::translate(model, glm::vec3(indices[i] * 0.5f, indices[i + 1] * 0.86f, 0.0f));
			model = glm::translate(model, glm::vec3(-0.95f, -0.15f, -1.9f));
			model = glm::scale(model, glm::vec3(0.9f, 0.9f, -0.1f));

			if ((indices[i] + indices[i + 1]) % 2 == 1)
				model = glm::rotate(model, glm::radians(180.f), glm::vec3(0, 0, 1));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			meshList[1]->RenderMesh();
		}



		//Cara roja
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		for (int i = 0; i < 18; i += 2) {

			model = glm::rotate(glm::mat4(1.0), glm::radians(rotacion), glm::vec3(1, 1, 1));
			model = glm::translate(model, glm::vec3(indices[i] * 0.5f, indices[i + 1] * 0.85f, 0.0f));

			if ((indices[i] + indices[i + 1]) % 2 == 1)
				model = glm::rotate(model, glm::radians(180.f), glm::vec3(0, 0, 1));

			model = glm::scale(model, glm::vec3(0.9f, 0.9f, -0.1f));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			meshList[1]->RenderMesh();
		}

		//Cara azul
		color = glm::vec3(0.0f, 0.f, 1.0f);
		for (int i = 0; i < 18; i += 2) {

			model = glm::rotate(glm::mat4(1.0), glm::radians(rotacion), glm::vec3(1, 1, 1));
			model = glm::rotate(model, glm::radians(70.f), glm::vec3(1, 0, 0));
			model = glm::translate(model, glm::vec3(indices[i] * 0.5f, indices[i + 1] * 0.86f, 0.0f));
			model = glm::translate(model, glm::vec3(0.f, 0.40f, 0.47f));
			model = glm::scale(model, glm::vec3(0.9f, 0.9f, -0.1f));

			if ((indices[i] + indices[i + 1]) % 2 == 1)
				model = glm::rotate(model, glm::radians(180.f), glm::vec3(0, 0, 1));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			meshList[1]->RenderMesh();
		}

		//Cara rosa
		color = glm::vec3(0.9f, 0.4f, 3.f);
		for (int i = 0; i < 18; i += 2) {

			model = glm::rotate(glm::mat4(1.0), glm::radians(rotacion), glm::vec3(1, 1, 1));
			model = glm::rotate(model, glm::radians(61.f), glm::vec3(0, 0, 1));
			model = glm::rotate(model, glm::radians(110.f), glm::vec3(1, 0, 0));
			model = glm::translate(model, glm::vec3(indices[i] * 0.5f, indices[i + 1] * 0.86f, 0.0f));
			model = glm::translate(model, glm::vec3(-0.1f, 0.45f, -0.35f));
			model = glm::scale(model, glm::vec3(0.9f, 0.9f, -0.1f));

			if ((indices[i] + indices[i + 1]) % 2 == 1)
				model = glm::rotate(model, glm::radians(180.f), glm::vec3(0, 0, 1));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			meshList[1]->RenderMesh();
		}

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}

