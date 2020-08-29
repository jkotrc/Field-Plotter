#include "Renderer.h"

#include "../Debug.h"

#include "Arrow.h"


using namespace glm;

const vec3 axis_colors[3] = { vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0) };
const vec4 axis_vectors[3] = { vec4(1.0,0.0,0.0,1.0),vec4(0.0,1.0,0.0,1.0), vec4(0.0,0.0,1.0,1.0) };


//last time 800 by 500 worked
//later set this in preferences
#define DEBUGWIDTH 1000
#define DEBUGHEIGHT 1000
#define ROLLSPEED 0.1F



//TODO: Just for debugging purposes
VectorField* debugVectorField;

Renderer::Renderer() :
	projectionMat(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
	debugModel(mat4(1.0f)),
	viewMat(rotate(mat4(1.0f), 1.0f, vec3(1.0, 0.0, 0.0))),
	camera(new Camera(DEBUGWIDTH, DEBUGHEIGHT, ROLLSPEED)),
	arrowModel(new Model)
{
	//TODO: REMOVE
	debugVectorField = new VectorField(0.1, 4, 0.1);
	

	loadArrowModel(arrowModel->vertices, arrowModel->normals, arrowModel->indices);
	Debug::printModel("[Renderer]", arrowModel);


	this->initGL();
}

//#define NOATTRIB

inline void Renderer::initGL() {
	const int vertexbuffersize = arrowModel->vertices.size() * sizeof(vec3);
	const int elementbuffersize = arrowModel->indices.size() * sizeof(unsigned int);

	glEnable(GL_POINT_SIZE);
	glPointSize(5.0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_DEPTH_TEST);
#ifndef NOATTRIB
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


#else
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexbuffersize, &arrowModel->vertices[0], GL_STATIC_DRAW);
#endif

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementbuffersize, &arrowModel->indices[0], GL_STATIC_DRAW);
	
	programID = loadShadersFromSource(Shaders::ARROW_VERTEXSHADER, Shaders::ARROW_FRAGMENTSHADER);
	//programID = loadShadersFromSource(Shaders::ARROW_VERTEXSHADER, Shaders::ARROW_FRAGMENTSHADER);
	mvpID = glGetUniformLocation(programID, "MVP");
}



inline void Renderer::drawArrow(Vector v) {
	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, glm::value_ptr(projectionMat * viewMat * debugModel));
	


	/*glBegin(GL_POINTS);

	for (auto i : arrowModel->vertices) {
		vec4 a = vec4(i.x, i.y, i.z, 1);
		a = projectionMat * viewMat * sceneMat * a;
		glVertex3f(a.x, a.y, a.z);
	}

	glEnd();*/
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

	glUniform3f(glGetUniformLocation(programID, "ivInstanceOffset"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(programID, "ivInstanceDirection"), 0.0f,1.0f,0.0f);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	glDrawElements(GL_TRIANGLES, arrowModel->indices.size(), GL_UNSIGNED_INT, (void*)0);


	//drawArrow(Vector(0,0,0,0,0,0));
	viewMat = camera->getViewMatrix();
	
	this->drawAxes();
}




inline void Renderer::drawAxes() {
	glUseProgram(0);
	glBindVertexArray(0);
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