#pragma once
#include "plottable.h"
#include "plottermath.h"

class Camera {
	private:
		float angle;
		float phi;
		float radius;
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


class PhysicalObject;
class Scene : Plottable {
	private:
		Camera* camera;
		GLuint vao;
        //GLuint sceneMatrices; //this is just a buffer
		glm::mat4 projectionMat;
		glm::mat4 viewMat;
        int width;
		int height;
        std::vector<PhysicalObject*> components;		
	public:
		Scene(int width, int height);
		void initGraphics();
		void draw();
		void addComponent(PhysicalObject& object);
		void removeComponent(int index);
		void resizeViewport(int w, int h);
		GLuint getSceneMatrices();
		void moveCamera(float dx, float dy);
		void scroll(float amount);
		void moveLinear(float x, float y, float z);
};