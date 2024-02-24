//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp> //las variables uniform sirven para no va a recibir por medio de vértices sino recibe el dato tal cual
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/trianguloAzul.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
static const char* vCuboRojo = "shaders/cuboRojo.vert";
static const char* fCuboRojo = "shaders/cuboRojo.frag";
static const char* vVerde = "shaders/verde.vert";
static const char* fVerde = "shaders/verde.frag";
static const char* vVerdeOscuro = "shaders/verdeOscuro.vert";
static const char* fVerdeOscuro = "shaders/verdeOscuro.frag";
static const char* vCafe = "shaders/cafe.vert";
static const char* fCafe = "shaders/cafe.frag";
float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
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

void CrearLetrasyFiguras()
{
	GLfloat vertices_F[] = {
		//X			Y			Z		   R	G	B
		// Parte vertical de la F
		-0.9f, 0.5f, 0.0f,				1.0f,0.0f,0.0f,
		-0.7f, 0.5f, 0.0f,				1.0f,0.0f,0.0f,
		-0.9f, -0.5f, 0.0f,				1.0f,0.0f,0.0f,

		-0.7f, 0.5f, 0.0f,				1.0f,0.0f,0.0f,
		-0.9f, -0.5f, 0.0f,				1.0f,0.0f,0.0f,
		-0.7f, -0.5f, 0.0f,				1.0f,0.0f,0.0f,
		// Palito superior de la F
		-0.7f, 0.5f, 0.0f,				1.0f,0.0f,0.0f,
		-0.4f, 0.5f, 0.0f,				1.0f,0.0f,0.0f,
		-0.7f, 0.3f, 0.0f,				1.0f,0.0f,0.0f,

		-0.4f, 0.5f, 0.0f,				1.0f,0.0f,0.0f,
		-0.7f, 0.3f, 0.0f,				1.0f,0.0f,0.0f,
		-0.4f, 0.3f, 0.0f,				1.0f,0.0f,0.0f,
		// Palito inferior de la F
		-0.7f, 0.1f, 0.0f,				1.0f,0.0f,0.0f,
		-0.7f, -0.1f, 0.0f,				1.0f,0.0f,0.0f,
		-0.5f, 0.1f, 0.0f,				1.0f,0.0f,0.0f,

		-0.7f, -0.1f, 0.0f,				1.0f,0.0f,0.0f,
		-0.5f, -0.1f, 0.0f,				1.0f,0.0f,0.0f,
		-0.5f, 0.1f, 0.0f,				1.0f,0.0f,0.0f,
	};
	MeshColor* F = new MeshColor();
	F->CreateMeshColor(vertices_F, 150);
	meshColorList.push_back(F);

	GLfloat vertices_R[] = {
		//X			Y			Z		   R	G	B
		// Parte vertical de la F
			-0.3f, 0.5f, 0.0f,				0.0f,1.0f,0.0f,
			-0.1f, 0.5f, 0.0f,				0.0f,1.0f,0.0f,
			-0.3f, -0.5f, 0.0f,				0.0f,1.0f,0.0f,

			-0.1f, 0.5f, 0.0f,				0.0f,1.0f,0.0f,
			-0.3f, -0.5f, 0.0f,				0.0f,1.0f,0.0f,
			-0.1f, -0.5f, 0.0f,				0.0f,1.0f,0.0f,

			-0.1f, 0.5f, 0.0f,				0.0f,1.0f,0.0f,
			-0.1f, 0.3f, 0.0f,				0.0f,1.0f,0.0f,
			0.0f, 0.5f, 0.0f,				0.0f,1.0f,0.0f,

			-0.1f, 0.3f, 0.0f,				0.0f,1.0f,0.0f,
			0.0f, 0.3f, 0.0f,				0.0f,1.0f,0.0f,
			0.0f, 0.5f, 0.0f,				0.0f,1.0f,0.0f,

			-0.1f, 0.2f, 0.0f,				0.0f,1.0f,0.0f,
			-0.1f, 0.0f, 0.0f,				0.0f,1.0f,0.0f,
			0.0f, 0.2f, 0.0f,				0.0f,1.0f,0.0f,

			-0.1f, 0.0f, 0.0f,				0.0f,1.0f,0.0f,
			0.0f, 0.0f, 0.0f,				0.0f,1.0f,0.0f,
			0.0f, 0.2f, 0.0f,				0.0f,1.0f,0.0f,

			0.0f, 0.5f, 0.0f,				0.0f,1.0f,0.0f,
			0.2f, 0.5f, 0.0f,				0.0f,1.0f,0.0f,
			0.0f, 0.1f, 0.0f,				0.0f,1.0f,0.0f,

			0.0f, 0.1f, 0.0f,				0.0f,1.0f,0.0f,
			0.2f, 0.1f, 0.0f,				0.0f,1.0f,0.0f,
			0.2f, 0.5f, 0.0f,				0.0f,1.0f,0.0f,

			0.0f, -0.5f, 0.0f,				0.0f,1.0f,0.0f,
			0.2f, -0.5f, 0.0f,				0.0f,1.0f,0.0f,
			0.0f, 0.1f, 0.0f,				0.0f,1.0f,0.0f,

			0.0f, -0.5f, 0.0f,				0.0f,1.0f,0.0f,
			0.0f, 0.0f, 0.0f,				0.0f,1.0f,0.0f,
			-0.1f, 0.0f, 0.0f,				0.0f,1.0f,0.0f,
	};
	MeshColor* R = new MeshColor();
	R->CreateMeshColor(vertices_R, 200);
	meshColorList.push_back(R);

	GLfloat vertices_V[] = {
		//X			Y			Z		   R	G	B
		// Aquí va la V
			0.3f, 0.5f, 0.0f, 			   0.0f,0.0f,0.5f,//triángulo izquierda
			0.5f, 0.5f, 0.0f, 			   0.0f,0.0f,0.5f,
			0.5f, -0.5f, 0.0f, 			   0.0f,0.0f,0.5f,

			0.5f, -0.3f, 0.0f, 			   0.0f,0.0f,0.5f, //triángulo parado derecha
			0.5f, 0.5f, 0.0f, 			   0.0f,0.0f,0.5f,
			0.6f, -0.3f, 0.0f, 			   0.0f,0.0f,0.5f,

			0.7f, 0.5f, 0.0f, 			   0.0f,0.0f,0.5f, //Triángulo derecha
			0.9f, 0.5f, 0.0f, 			   0.0f,0.0f,0.5f,
			0.7f, -0.5f, 0.0f, 			   0.0f,0.0f,0.5f,


			0.5f, -0.3f, 0.0f, 			   0.0f,0.0f,0.5f,//triángulo base arriba
			0.5f, -0.5f, 0.0f, 			   0.0f,0.0f,0.5f,
			0.7f, -0.3f, 0.0f, 			   0.0f,0.0f,0.5f,


			0.7f, 0.5f, 0.0f, 			   0.0f,0.0f,0.5f,
			0.7f, -0.3f, 0.0f, 			   0.0f,0.0f,0.5f,
			0.6f, -0.3f, 0.0f, 			   0.0f,0.0f,0.5f,


			0.5f, -0.5f, 0.0f, 			   0.0f,0.0f,0.5f,
			0.7f, -0.3f, 0.0f, 			   0.0f,0.0f,0.5f,
			0.7f, -0.5f, 0.0f, 			   0.0f,0.0f,0.5f,

	};
	MeshColor* V = new MeshColor();
	V->CreateMeshColor(vertices_V, 110);
	meshColorList.push_back(V);


	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	};
	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);


	GLfloat verticesTrianguloAzul[] = {	//0 TRIANGULO AZUL
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f

	};
	MeshColor* trianguloAzul = new MeshColor();
	trianguloAzul->CreateMeshColor(verticesTrianguloAzul, 18);
	meshColorList.push_back(trianguloAzul);

	GLfloat vertices_trianguloverde[] = { //2 TRIANGULO BLANCO
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	};
	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);


	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};
	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);


	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};
	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);



	GLfloat vertices_cuadradoCafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478, 0.255, 0.067,
		0.5f,	-0.5f,		0.5f,			0.478, 0.255, 0.067,
		0.5f,	0.5f,		0.5f,			0.478, 0.255, 0.067,
		-0.5f,	-0.5f,		0.5f,			0.478, 0.255, 0.067,
		0.5f,	0.5f,		0.5f,			0.478, 0.255, 0.067,
		-0.5f,	0.5f,		0.5f,			0.478, 0.255, 0.067,

	};

	MeshColor* cuadradoCafe = new MeshColor();
	cuadradoCafe->CreateMeshColor(vertices_cuadradoCafe, 36);
	meshColorList.push_back(cuadradoCafe);


}


void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader();
	shader3->CreateFromFiles(vCuboRojo, fCuboRojo);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(vVerde, fVerde);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader(); 
	shader5->CreateFromFiles(vVerdeOscuro, fVerdeOscuro);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader();
	shader6->CreateFromFiles(vCafe, fCafe);
	shaderList.push_back(*shader6);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		//F
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.1f, -0.1f, -4.0f));//Coordenadas de la figura
		model = glm::scale(model, glm::vec3(0.8));// Hacer la forma más pequeña (escalarla)
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshColorList[0]->RenderMeshColor();

		//R
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.0f, -0.1f, -4.0f));//Coordenadas de la figura
		model = glm::scale(model, glm::vec3(0.8)); // Hacer la forma más pequeña (escalarla)
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshColorList[1]->RenderMeshColor();

		//V
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.1f, -0.1f, -4.0f));//Coordenadas de la figura
		model = glm::scale(model, glm::vec3(0.8)); // Hacer la forma más pequeña (escalarla)
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshColorList[2]->RenderMeshColor();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		
		////techo
		//shaderList[0].useShader();
		//uniformModel = shaderList[2].getModelLocation();
		//uniformProjection = shaderList[2].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.55f, -4.0f));//Coordenadas de la figura
		//model = glm::scale(model, glm::vec3(1.2f, 0.6f, 1.0f));// Hacer la forma más pequeña (escalarla)
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[0]->RenderMesh();

		//////Cuadrado verde- ventana derecha
		//shaderList[3].useShader();
		//uniformModel = shaderList[3].getModelLocation();
		//uniformProjection = shaderList[3].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.25f, -0.1f, -4.0f));//Coordenadas de la figura
		//model = glm::scale(model, glm::vec3(0.35f, 0.45f, 1.0f)); // Hacer la forma más pequeña (escalarla)
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();

		//////Cuadrado verde- ventana izquierda
		//shaderList[3].useShader();
		//uniformModel = shaderList[3].getModelLocation();
		//uniformProjection = shaderList[3].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.25f, -0.1f, -4.0f));//Coordenadas de la figura
		//model = glm::scale(model, glm::vec3(0.35f, 0.45f, 1.0f)); // Hacer la forma más pequeña (escalarla)
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();


		//////Cuadrado verde - puerta
		//shaderList[3].useShader();
		//uniformModel = shaderList[3].getModelLocation();
		//uniformProjection = shaderList[3].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -0.8f, -4.0f));//Coordenadas de la figura
		//model = glm::scale(model, glm::vec3(0.35f, 0.45f, 1.0f)); // Hacer la forma más pequeña (escalarla)
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();


		//////Cuadro rojo-pared
		//shaderList[2].useShader();
		//uniformModel = shaderList[2].getModelLocation();
		//uniformProjection = shaderList[2].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, -0.5f, -4.5f));//Coordenadas de la figura
		//model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f)); // Hacer la forma más pequeña (escalarla)
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();

		//////Arbol izquierda
		//shaderList[5].useShader();
		//uniformModel = shaderList[5].getModelLocation();
		//uniformProjection = shaderList[5].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.75f, -0.85f, -4.0f));//Coordenadas de la figura
		//model = glm::scale(model, glm::vec3(0.25f, 0.35f, 1.0f)); // Hacer la forma más pequeña (escalarla)
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();

		//shaderList[4].useShader();
		//uniformModel = shaderList[4].getModelLocation();
		//uniformProjection = shaderList[4].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-0.75f, -0.375f, -4.0f));//Coordenadas de la figura
		//model = glm::scale(model, glm::vec3(0.45f, 0.6f, 1.0f)); // Hacer la forma más pequeña (escalarla)
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[0]->RenderMesh();



		//////Arbol derecha
		//shaderList[5].useShader();
		//uniformModel = shaderList[5].getModelLocation();
		//uniformProjection = shaderList[5].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.75f, -0.85f, -4.0f));//Coordenadas de la figura
		//model = glm::scale(model, glm::vec3(0.25f, 0.35f, 1.0f)); // Hacer la forma más pequeña (escalarla)
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[1]->RenderMesh();

		//shaderList[4].useShader();
		//uniformModel = shaderList[4].getModelLocation();
		//uniformProjection = shaderList[4].getProjectLocation();
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.75f, -0.375f, -4.0f));//Coordenadas de la figura
		//model = glm::scale(model, glm::vec3(0.45f, 0.6f, 1.0f)); // Hacer la forma más pequeña (escalarla)
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshList[0]->RenderMesh();
		
		
		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}