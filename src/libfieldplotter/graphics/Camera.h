#pragma once


#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_inverse.hpp>


//TODO: Make a namespace for utility functions of this sort 
//glm::vec3 toScreenCoord(double x, double y, int windowWidth, int windowHeight);

class Camera {
	private:


		float prevAngle;
		float angle;
		glm::vec2 rotAxis;
		
		glm::vec3 currentPos;
		glm::vec3 prevPos;
		glm::vec3 origin;
		
		
		glm::vec2 screenCoord;
		glm::vec2 sphericalCoord;

		//TODO: Make a container for these
		glm::mat4 viewMat;
		//glm::mat4 prevViewMat;


	public:
	Camera(int window_width, int window_height, GLfloat roll_speed);

	glm::mat4 getViewMatrix();
	glm::vec3 getPos();

	void grabCamera(int x, int y);
	void moveCamera(int x, int y);
	void releaseCamera();
};

