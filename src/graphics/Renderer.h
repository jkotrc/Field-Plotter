#pragma once


//class Simulation;
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>

#include "../computation/vectorfield.h"
//#include "computation/vectorfield.h"

using namespace glm;

//Model of the arrow's cone
typedef struct Model {
	std::vector<vec3> vertices;
	std::vector<unsigned int> indices;
} Model;

mat4 vectorToModelMatrix(Vector v);


//The renderer's render function may only be used if a valid OpenGL context already exists!
class Renderer {
	private:
		GLuint vertexbuffer;
		GLuint elementbuffer;
		
		GLuint programID;
		GLuint mvpID;

		bool glInitialized;
		bool drawFieldLines;
		bool drawEquipotentials;

		mat4 projectionMat;
		mat4 modelMat;
		mat4 viewMat;

		Model* arrowModel;
		void drawAxes();
		void drawArrow(Vector v);
		


	public:
		

		Renderer();
		void tempRender();
		
		void initGL();

		void multModel(mat4 matrix, bool fromRight);
		void multView(mat4 view, bool fromRight);
		mat4* getModel();
		mat4* getView();
		void setModel(mat4 model);
		void setView(mat4 view);
};