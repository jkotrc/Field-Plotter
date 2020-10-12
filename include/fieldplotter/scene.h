#pragma once
#include <fieldplotter/commonheaders.h>

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
typedef unsigned int GLuint;

class Plottable;
class Scene {
	private:
		Camera* camera;
		GLuint vao;
		
        GLuint sceneMatrices;
		glm::mat4 projectionMat;
		glm::mat4 viewMat;
		
        int width;
		int height;
        std::vector<Plottable*> plottables;
	public:
		Scene(int width, int height);
		~Scene();
		void render();
		void resizeViewport(int w, int h);
		void addPlottable(Plottable* plottable);
		GLuint getSceneMatrices();
		void moveCamera(float dx, float dy);
		void scroll(float amount);
		void moveLinear(float x, float y, float z);
};