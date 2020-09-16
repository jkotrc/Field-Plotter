#include <fieldplotter/fieldplotter.h>
#include "../Debug.h"
#include "Shaders.h"
#include <stdio.h>


using namespace glm;

const vec3 axis_colors[3] = { vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0) };
const vec4 axis_vectors[3] = { vec4(1.0,0.0,0.0,1.0),vec4(0.0,1.0,0.0,1.0), vec4(0.0,0.0,1.0,1.0) };

//TODO: Make this configurable in the preferences
#define ROLLSPEED 0.5F

/*
A scene within the Renderer may be composed of:
Vector fields
Axes/grid lines
Field lines
Equipotential surfaces
Point charges

User will: specify charges, change some sort of rendering mode

The renderer will: build and execute a rendering method based on the rendering mode
It will do so out of inline methods in: VectorFieldGraphic, EquipotentialSurfaceGraphic, FieldLineGraphic, PointChargeGraphic

Restructuring:
*/

/*
std140 specification:
layout (std140) uniform Block{
                     // base alignment  // aligned offset
    float value;     // 4               // 0 
    vec3 vector;     // 16              // 16  (offset must be multiple of 16 so 4->16)
    mat4 matrix;     // 16              // 32  (column 0)
                     // 16              // 48  (column 1)
                     // 16              // 64  (column 2)
                     // 16              // 80  (column 3)
    float values[3]; // 16              // 96  (values[0])
                     // 16              // 112 (values[1])
                     // 16              // 128 (values[2])
    bool boolean;    // 4               // 144
    int integer;     // 4               // 148
};
*/

/*
layout (std140) uniform SceneMatrices {
  mat4 projectionMat;
  mat4 viewMat;
};
*/
#define MAT4_BASE_ALIGNMENT 16
#define VEC3_BASE_ALIGNMENT 16
#define VEC3_SIZE 16
#define MAT4_SIZE 64

Scene::Scene(int width, int height) 
:height(height),
width(width),
projectionMat(glm::perspective(glm::radians(45.0f), (float)width/height, 0.1f, 100.0f)),
viewMat(rotate(mat4(1.0f), 1.0f, vec3(1.0, 0.0, 0.0))),
camera(new Camera(ROLLSPEED))
{
	DEBUGSTRING("Scene", "starting initGL()");
	this->initGL();
}

void Scene::addPlottable(Plottable* plottable) {
	plottable->setParent(this);
	plottables.push_back(plottable);
}

void Scene::resizeViewport(int w, int h) {
	width=w;
	height=h;
	projectionMat = glm::perspective(glm::radians(45.0f), (float)w / h, 0.1f, 100.0f);
	glBindBuffer(GL_UNIFORM_BUFFER, sceneMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, MAT4_SIZE, glm::value_ptr(projectionMat));
	glBindBuffer(GL_UNIFORM_BUFFER,0);
	glViewport(0, 0, width, height);
}

inline void Scene::initGL() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glClearColor(0.1, 0.1, 0.1, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	

	glGenBuffers(1, &sceneMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, sceneMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2*sizeof(mat4)+sizeof(vec3),NULL,GL_STATIC_DRAW);
	
	glBufferSubData(GL_UNIFORM_BUFFER, 0, MAT4_SIZE, glm::value_ptr(projectionMat));
	glBufferSubData(GL_UNIFORM_BUFFER, MAT4_SIZE, MAT4_SIZE, glm::value_ptr(viewMat));
	glBufferSubData(GL_UNIFORM_BUFFER, 2*MAT4_SIZE, VEC3_SIZE,glm::value_ptr(camera->getPos()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER,0,sceneMatrices);

	Debug::debugString("Scene", "GL Initialized!");
}

void Scene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	viewMat = camera->getViewMatrix();
	glBindBuffer(GL_UNIFORM_BUFFER, sceneMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, MAT4_SIZE, MAT4_SIZE, glm::value_ptr(viewMat));
	glBufferSubData(GL_UNIFORM_BUFFER, MAT4_SIZE*2,VEC3_SIZE,glm::value_ptr(camera->getPos()));
	glBindBuffer(GL_UNIFORM_BUFFER,0);
	for (const auto& element : plottables) {
		element->draw();
	}
}

Camera* Scene::getCamera() {
	return camera;
}
GLuint Scene::getSceneMatrices() {
	return sceneMatrices;
}

GLuint loadShadersFromSource(std::string vertex_source, std::string fragment_source) {
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLint Result = GL_FALSE;
	int InfoLogLength;
	char const* VertexSourcePointer = vertex_source.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("ERROR COMPILING SHADER! %s\n", &VertexShaderErrorMessage[0]);
	}

	char const* FragmentSourcePointer = fragment_source.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("ERROR COMPILING SHADER! %s\n", &FragmentShaderErrorMessage[0]);
	}

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
