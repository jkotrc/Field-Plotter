#pragma once

#include <computation/plottermath.h>

class Camera {
	private:
		float angle;
		float phi;
		glm::vec3 up;
		glm::vec3 cameraPosition;
		glm::vec3 origin;
		glm::mat4 viewMat;
	public:
	Camera();
	glm::mat4 getViewMatrix();
	glm::vec3 getPos();
	void moveLinear(float x, float y, float z);
	void scroll(float amount);
	void moveCamera(float dtheta, float dphi);
};