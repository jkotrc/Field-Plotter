#pragma once
#include "plottermath.h"

class DynamicObject;
class Plottable;

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


class Scene {
	public:
		Scene(int width, int height);
		void render();
		void initGraphics();
		void resizeViewport(int w, int h);
		void addPlottable(Plottable* plottable);
		void removePlottable(Plottable* plottable);
		GLuint getSceneMatrices();
		Camera& getCamera();
	private:
		std::vector<Plottable*> m_plottables;
		Camera m_camera;
		GLuint m_vao;
		GLuint m_uniformbuffer;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
	
};