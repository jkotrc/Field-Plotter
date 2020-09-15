#include <fieldplotter/fieldplotter.h>
#include "../Debug.h"
#include "Arrow.h"
#include "Shaders.h"
#include <stdio.h>


using namespace glm;

const vec3 axis_colors[3] = { vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0) };
const vec4 axis_vectors[3] = { vec4(1.0,0.0,0.0,1.0),vec4(0.0,1.0,0.0,1.0), vec4(0.0,0.0,1.0,1.0) };

//TODO: Make this configurable in the preferences
#define ROLLSPEED 0.5F

Renderer::Renderer(VectorField* vf, int w, int h) :
	projectionMat(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
	debugModel(mat4(1.0f)),
	viewMat(rotate(mat4(1.0f), 1.0f, vec3(1.0, 0.0, 0.0))),
	camera(new Camera(ROLLSPEED)),
	arrowModel(new Model),
	vectorfield(vf),
	height(h),
	width(w)
{
	DEBUGSTRING("Renderer", "starting constructor");
	loadArrowModel(arrowModel->vertices, arrowModel->normals, arrowModel->indices);
	this->initGL();
}

void Renderer::resizeViewport(int w, int h) {
	width=w;
	height=h;
	glViewport(0, 0, width, height);
}

inline void Renderer::initGL() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glClearColor(0.1, 0.1, 0.1, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
	//glVertexAttribDivisor(0, 0); //this is probably optional
	glBufferData(GL_ARRAY_BUFFER, arrowModel->vertices.size() * sizeof(vec3), &arrowModel->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, nullptr);
	//glVertexAttribDivisor(1, 0); //this is probably optional
	glBufferData(GL_ARRAY_BUFFER, arrowModel->normals.size() * sizeof(vec3), &arrowModel->normals[0], GL_STATIC_DRAW);

	vectorfield->getVectorPositionBuffer(&vectorfield_position_buffer, 2);
	vectorfield->getVectorComponentBuffer(&vectorfield_component_buffer, 3);

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arrowModel->indices.size() * sizeof(unsigned int), &arrowModel->indices[0], GL_STATIC_DRAW);
	
	programID = loadShadersFromSource(Shaders::ARROW_VERTEXSHADER, Shaders::ARROW_FRAGMENTSHADER);
	axisProgramID = loadShadersFromSource(Shaders::AXES_VERTEXSHADER, Shaders::AXES_FRAGMENTSHADER);
	mvpID = glGetUniformLocation(programID, "MVP");
	Debug::debugString("Renderer", "GL Initialized!");
}

void Renderer::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	drawAxes();
	glUseProgram(programID);
	viewMat = camera->getViewMatrix();
	mat4 model_view_matrix = viewMat * debugModel;
	glm::vec3 camera_position = camera->getPos();
	glm::vec4 light_position = model_view_matrix * glm::vec4(camera_position, 1.0);
	glUniformMatrix4fv(glGetUniformLocation(programID, "uProjectionMatrix"), 1, false, glm::value_ptr(projectionMat));
	glUniformMatrix4fv(glGetUniformLocation(programID, "uModelviewMatrix"), 1, false, glm::value_ptr(model_view_matrix));
	glUniform3f(glGetUniformLocation(programID, "uLightPosition"), light_position[0], light_position[1], light_position[2]);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawElementsInstanced(GL_TRIANGLES,arrowModel->indices.size(),GL_UNSIGNED_INT,(void*)0,vectorfield->getAmount());
	viewMat = camera->getViewMatrix();
}

inline void Renderer::drawAxes() {
	glUseProgram(axisProgramID);
	vec4 transformedvertices[3];
	for (int i = 0; i < 3; i++) {
		transformedvertices[i] = projectionMat * viewMat * debugModel * axis_vectors[i];
	}
	glBegin(GL_LINES);
	for (int i = 0; i < 3; i++) {
		const vec3 color = axis_colors[i];
		const vec4 vertex = axis_vectors[i];
		glColor3f(color.r, color.g, color.b);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(transformedvertices[i].x, transformedvertices[i].y, transformedvertices[i].z);
	}
	glEnd();
}

Camera* Renderer::getCamera() {
	return camera;
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
void Renderer::updateVectorField(VectorField* newVectorField) {
	delete this->vectorfield;
	this->vectorfield = newVectorField;
}