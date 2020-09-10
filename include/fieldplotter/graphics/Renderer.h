#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shaders.h"
#include "Camera.h"
#include "../computation/vectorfield.h"
#include <vector>
#include "Assets.h"




class Renderer {
	private:
		Camera* camera;
		GLuint vertexbuffer;
		GLuint elementbuffer;
		GLuint normalbuffer;
		
		GLuint vao;
		GLuint programID;
		GLuint mvpID;

		bool glInitialized;
		bool drawFieldLines;
		bool drawEquipotentials;

		glm::mat4 projectionMat;
		glm::mat4 debugModel;
		glm::mat4 viewMat;

		Model* arrowModel;

		inline void initGL();
		inline void drawAxes();
		inline void drawArrow(Vector v);

	public:
		Renderer();
		void render();
		Camera* getCamera();
};