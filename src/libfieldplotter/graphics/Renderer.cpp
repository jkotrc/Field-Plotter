//#include "Renderer.h"
#include "../fieldplotter.h"
#include "../Debug.h"
#include "Arrow.h"
#include "Shaders.h"

//TODO: Refactor all of this
#include <stdio.h>


using namespace glm;

const vec3 axis_colors[3] = { vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0) };
const vec4 axis_vectors[3] = { vec4(1.0,0.0,0.0,1.0),vec4(0.0,1.0,0.0,1.0), vec4(0.0,0.0,1.0,1.0) };


//TODO: Make this configurable in the preferences
#define ROLLSPEED 0.1F

Renderer::Renderer(VectorField* vf) :
	projectionMat(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
	debugModel(mat4(1.0f)),
	viewMat(rotate(mat4(1.0f), 1.0f, vec3(1.0, 0.0, 0.0))),
	camera(new Camera(ROLLSPEED)),
	arrowModel(new Model),
	vectorfield(vf)
{
	Debug::debugString("Renderer", "starting constructor");
	loadArrowModel(arrowModel->vertices, arrowModel->normals, arrowModel->indices);
	this->initGL();
}


inline void Renderer::initGL() {
	const int vertexbuffersize = arrowModel->vertices.size() * sizeof(vec3);
	const int elementbuffersize = arrowModel->indices.size() * sizeof(unsigned int);
	int vectorfieldSize = vectorfield->getDimension();
	vectorfieldSize = vectorfieldSize*vectorfieldSize*vectorfieldSize;

	glEnable(GL_POINT_SIZE);
	glPointSize(5.0);
	Debug::debugString("Renderer","point size is 5.0");
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	Debug::debugString("Renderer","non-default VAO made");

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
	//glVertexAttribDivisor(0, 0);
	glBufferData(GL_ARRAY_BUFFER, vertexbuffersize, &arrowModel->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, nullptr);
	//glVertexAttribDivisor(1, 0);
	glBufferData(GL_ARRAY_BUFFER, arrowModel->normals.size() * sizeof(vec3), &arrowModel->normals[0], GL_STATIC_DRAW);

	
	vectorfield->getVectorPositionBuffer(&vectorfield_position_buffer, 2);
	vectorfield->getVectorComponentBuffer(&vectorfield_component_buffer, 3);
	

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementbuffersize, &arrowModel->indices[0], GL_STATIC_DRAW);
	
	programID = loadShadersFromSource(Shaders::ARROW_VERTEXSHADER, Shaders::ARROW_FRAGMENTSHADER);
	//programID = loadShadersFromSource(Shaders::ARROW_VERTEXSHADER, Shaders::ARROW_FRAGMENTSHADER);
	mvpID = glGetUniformLocation(programID, "MVP");
	Debug::debugString("Renderer", "GL Initialized!");
}



void Renderer::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	glUseProgram(programID);
	
	viewMat = camera->getViewMatrix();
	mat4 model_view_matrix = viewMat * debugModel;
	glm::vec3 camera_position = camera->getPos();
	glm::vec4 light_position = model_view_matrix * glm::vec4(camera_position, 1.0);

	glUniformMatrix4fv(glGetUniformLocation(programID, "uProjectionMatrix"), 1, false, glm::value_ptr(projectionMat));
	glUniformMatrix4fv(glGetUniformLocation(programID, "uModelviewMatrix"), 1, false, glm::value_ptr(model_view_matrix));
	glUniform3f(glGetUniformLocation(programID, "uLightPosition"), light_position[0], light_position[1], light_position[2]);

	//glUniform3f(glGetUniformLocation(programID, "ivInstanceOffset"), 0.0f, 0.0f, 0.0f);
	//glUniform3f(glGetUniformLocation(programID, "ivInstanceDirection"), 0.0f,1.0f,0.0f);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glDrawElementsInstanced(GL_TRIANGLES,arrowModel->indices.size(),GL_UNSIGNED_INT,(void*)0,vectorfield->getAmount());
	viewMat = camera->getViewMatrix();
}

inline void Renderer::drawAxes() {
	glUseProgram(-1);
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

//TODO: Refactor this
GLuint loadShadersFromSource(std::string vertex_source, std::string fragment_source) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	char const* VertexSourcePointer = vertex_source.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("ERROR COMPILING SHADER! %s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	char const* FragmentSourcePointer = fragment_source.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("ERROR COMPILING SHADER! %s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	GLuint ProgramID = glCreateProgram();

	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
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