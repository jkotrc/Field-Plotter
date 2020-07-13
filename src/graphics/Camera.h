#pragma once


#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_inverse.hpp>

//Arcball implementation taken from https://github.com/subokita/Arcball
using namespace glm;
class Camera {
	//TODO: CHANGE BACK TO PRIVATE
	private:
		int windowWidth;
		int windowHeight;
		vec3 currentPos;
		vec3 prevPos;
		vec3 camAxis;
		GLfloat rollSpeed;
		GLfloat angle;
		bool xAxis;
		bool yAxis;
		void updateVars();

	public:
	Camera(int window_width, int window_height, GLfloat roll_speed, bool x_axis, bool y_axis);
	vec3 toScreenCoord(double x, double y);

	mat4 createViewRotationMatrix();
	mat4 createModelRotationMatrix(glm::mat4& view_matrix);
	void setPrevPos(vec3 prevPos);
	void setCurrentPos(vec3 currentPos);
	vec3 getCurrentPos();
};

